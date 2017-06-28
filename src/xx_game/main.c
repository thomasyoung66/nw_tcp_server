/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "uv.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

uv_buf_t uv_buf_malloc(char* base, unsigned int len) {
  uv_buf_t buf;
  buf.base = base;
  buf.len = len;
  return buf;
}


static uv_loop_t* loop;

static int server_closed;
static stream_type serverType;
static uv_tcp_t tcpServer;
static uv_handle_t* server;

static void after_write(uv_write_t* req, int status);
static void after_read(uv_stream_t*, ssize_t nread, const uv_buf_t* buf);
static void on_close(uv_handle_t* peer);
static void on_server_close(uv_handle_t* handle);
static void on_connection(uv_stream_t*, int status);


typedef struct _queue_data{
	char buffer[128];
	uv_stream_t * handle;
}queue_data;

static void work_cb(uv_work_t* req) {
	printf("%ld %s ....\n",pthread_self(),__FUNCTION__);
	queue_data * qd=(queue_data *)req->data;

	write_req_t * wr = (write_req_t*) malloc(sizeof *wr);
	ASSERT(wr != NULL);
	
	wr->buf = uv_buf_init(strdup("ok\r\n"), 4);

	if (uv_write(&wr->req, qd->handle, &wr->buf, 1, after_write)) {
		FATAL("uv_write failed");
	}
}


static void after_work_cb(uv_work_t* req, int status) {
	printf("%ld %s ....\n",pthread_self(),__FUNCTION__);
	free(req->data);
	free(req);
}


int send_work_queue(queue_data * qd)
{
	printf("%ld %s ....\n",pthread_self(),__FUNCTION__);
	uv_work_t * queue=(uv_work_t *)malloc(sizeof(uv_work_t));
	queue->data=qd;
	uv_queue_work(uv_default_loop(), queue, work_cb, after_work_cb);
}
static void after_write(uv_write_t* req, int status) {
	write_req_t* wr;

	/* Free the read/write buffer and the request */
	wr = (write_req_t*) req;
	free(wr->buf.base);
	free(wr);

	if (status == 0)
		return;

	fprintf(stderr,
			"uv_write error: %s - %s\n",
			uv_err_name(status),
			uv_strerror(status));
}


static void after_shutdown(uv_shutdown_t* req, int status) {
	uv_close((uv_handle_t*) req->handle, on_close);
	free(req);
}


static void after_read(uv_stream_t* handle,
		ssize_t nread,
		const uv_buf_t* buf) {
	int i;
	write_req_t *wr;
	uv_shutdown_t* sreq;

	if (nread < 0) {
		/* Error or EOF */
		ASSERT(nread == UV_EOF);

		free(buf->base);
		sreq = (uv_shutdown_t *)malloc(sizeof* sreq);
		ASSERT(0 == uv_shutdown(sreq, handle, after_shutdown));
		return;
	}

	if (nread == 0) {
		/* Everything OK, but nothing read. */
		free(buf->base);
		return;
	}
	printf("thread=%ld length=%d buffer=%s\n",pthread_self(),buf->len,buf->base);
	queue_data * qd=(queue_data *) malloc(sizeof(queue_data));
	qd->handle=handle;
	send_work_queue(qd);
	return ;
	/*
	 * Scan for the letter Q which signals that we should quit the server.
	 * If we get QS it means close the stream.
	 */
	if (!server_closed) {
		for (i = 0; i < nread; i++) {
			if (buf->base[i] == 'Q') {
				if (i + 1 < nread && buf->base[i + 1] == 'S') {
					free(buf->base);
					uv_close((uv_handle_t*)handle, on_close);
					return;
				} else {
					uv_close(server, on_server_close);
					server_closed = 1;
				}
			}
		}
	}

	wr = (write_req_t*) malloc(sizeof *wr);
	ASSERT(wr != NULL);
	wr->buf = uv_buf_init(buf->base, nread);

	if (uv_write(&wr->req, handle, &wr->buf, 1, after_write)) {
		FATAL("uv_write failed");
	}
}


static void on_close(uv_handle_t* peer) {
	free(peer);
}


static void echo_alloc(uv_handle_t* handle,
		size_t suggested_size,
		uv_buf_t* buf) {
	buf->base = (char *)malloc(suggested_size);
	buf->len = suggested_size;
}


static void on_connection(uv_stream_t* server, int status) {
	uv_stream_t* stream;
	int r;

	printf("begin connection...\n");
	if (status != 0) {
		fprintf(stderr, "Connect error %s\n", uv_err_name(status));
	}
	ASSERT(status == 0);

	switch (serverType) {
		case TCP:
			stream = (uv_stream_t *)malloc(sizeof(uv_tcp_t));
			ASSERT(stream != NULL);
			r = uv_tcp_init(loop, (uv_tcp_t*)stream);
			ASSERT(r == 0);
			break;

		case PIPE:
			stream = (uv_stream_t *)malloc(sizeof(uv_pipe_t));
			ASSERT(stream != NULL);
			r = uv_pipe_init(loop, (uv_pipe_t*)stream, 0);
			ASSERT(r == 0);
			break;

		default:
			ASSERT(0 && "Bad serverType");
			abort();
	}

	/* associate server with stream */
	stream->data = server;

	r = uv_accept(server, stream);
	ASSERT(r == 0);

	r = uv_read_start(stream, echo_alloc, after_read);
	printf("end connection...\n");
	ASSERT(r == 0);
}


static void on_server_close(uv_handle_t* handle) {
	ASSERT(handle == server);
}


static void on_send(uv_udp_send_t* req, int status);


static void on_recv(uv_udp_t* handle,
		ssize_t nread,
		const uv_buf_t* rcvbuf,
		const struct sockaddr* addr,
		unsigned flags) {
	uv_udp_send_t* req;
	uv_buf_t sndbuf;

	ASSERT(nread > 0);
	ASSERT(addr->sa_family == AF_INET);

	req = (uv_udp_send_t *)malloc(sizeof(*req));
	ASSERT(req != NULL);

	sndbuf = *rcvbuf;
	ASSERT(0 == uv_udp_send(req, handle, &sndbuf, 1, addr, on_send));
}


static void on_send(uv_udp_send_t* req, int status) {
	ASSERT(status == 0);
	free(req);
}


static int tcp4_echo_start(int port) {
	struct sockaddr_in addr;
	int r;

	ASSERT(0 == uv_ip4_addr("0.0.0.0", port, &addr));

	server = (uv_handle_t*)&tcpServer;
	serverType = TCP;

	r = uv_tcp_init(loop, &tcpServer);
	if (r) {
		/* TODO: Error codes */
		fprintf(stderr, "Socket creation error\n");
		return 1;
	}

	r = uv_tcp_bind(&tcpServer, (const struct sockaddr*) &addr, 0);
	if (r) {
		/* TODO: Error codes */
		fprintf(stderr, "Bind error\n");
		return 1;
	}

	r = uv_listen((uv_stream_t*)&tcpServer, SOMAXCONN, on_connection);
	if (r) {
		/* TODO: Error codes */
		fprintf(stderr, "Listen error %s\n", uv_err_name(r));
		return 1;
	}

	return 0;
}





int main(int argc,char * argv[])
{
	loop = uv_default_loop();

	if (tcp4_echo_start(TEST_PORT))
		return 1;

	uv_run(loop, UV_RUN_DEFAULT);
	return 0;
}

