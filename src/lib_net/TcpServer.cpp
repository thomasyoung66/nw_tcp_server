/*
 * =====================================================================================
 * 
 *        Filename:  TCPSERVER
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/04/2017 12:31:27 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

// =====================================================================================
//        Class:  TcpServer
//  Description:  
// =====================================================================================

#ifndef _TcpServer_CPP_
#define _TcpServer_CPP_


#include "TcpServer.h"
#include "../lib_app/Application.h"
#include <map>
#include <list>
extern "C"{
#include "EventState.h"
}

static LoggerPtr logger ;

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

static std::map<EventState *,EventState *> allEventState;

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
	uv_stream_t * handle;
}queue_data;

static void work_cb(uv_work_t* req) 
{
	msg_debug(logger,__FUNCTION__);
	EventState * state=(EventState *)req->data;

	write_req_t * wr = (write_req_t*) malloc(sizeof *wr);
	ASSERT(wr != NULL);

	wr->buf = uv_buf_init(strdup("ok\r\n"), 4);

	if (uv_write(&wr->req,state->client, &wr->buf, 1, after_write)) {
		FATAL("uv_write failed");
	}
}


static void after_work_cb(uv_work_t* req, int status) 
{
	msg_info(logger,"after_work_cb....");
	//free(req->data);
	free(req);
}


int send_work_queue(EventState * es)
{
	uv_work_t * queue=(uv_work_t *)malloc(sizeof(uv_work_t));
	msg_info(logger,"send work queue...");
	queue->data=es;
	uv_queue_work(uv_default_loop(), queue, work_cb, after_work_cb);
	return 0;
}
static void after_write(uv_write_t* req, int status) 
{
	write_req_t* wr;

	/* Free the read/write buffer and the request */
	wr = (write_req_t*) req;
	free(wr->buf.base);
	free(wr);

	if (status == 0)
		return;

	msg_error(logger, Util::format("uv_write error: %s - %s\n",
			uv_err_name(status),
			uv_strerror(status)).c_str());
}


static void after_shutdown(uv_shutdown_t* req, int status) 
{
	printf("shutdown....%p\n",req->handle);
	uv_close((uv_handle_t*) req->handle, on_close);
	free(req);
}


static void after_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) 
{
	int i;
	write_req_t *wr;
	uv_shutdown_t* sreq;

	msg_debug(logger,Util::format("read.....%p\n",handle));
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
	if (strncmp(buf->base,"quit",4)==0){
		free(buf->base);
		uv_close((uv_handle_t*)handle, on_close);
		return ;
	}
	send_work_queue((EventState *)handle->data);
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


static void on_close(uv_handle_t* peer) 
{
	msg_debug(logger,Util::format("on close...%p\n",peer));
	free(peer);
}


static void echo_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) 
{
	buf->base = (char *)malloc(suggested_size);
	buf->len = suggested_size;
}




static void on_connection(uv_stream_t* server, int status) {
	uv_stream_t* stream;
	int r;

	msg_debug(logger,"begin connection...\n");
	if (status != 0) {
		msg_error(logger,Util::format( "Connect error %s\n", uv_err_name(status)));
	}
	ASSERT(status == 0);
	switch (serverType) {
		case TCP:
			stream = (uv_stream_t *)malloc(sizeof(uv_tcp_t));
			ASSERT(stream != NULL);
			r = uv_tcp_init(loop, (uv_tcp_t*)stream);
			ASSERT(r == 0);
			break;

		default:
			ASSERT(0 && "Bad serverType");
			abort();
	}

	EventState * state=alloc_init_event_state();
	state->server=server;
	state->client=stream;
	state->lastHeartTime=time(NULL);
	allEventState[state]=state;
	/* associate server with stream */
	stream->data = state;

	r = uv_accept(server, stream);
	ASSERT(r == 0);
	r = uv_read_start(stream, echo_alloc, after_read);


	msg_info(logger,"end connection...\n");
	ASSERT(r == 0);
}


static void on_server_close(uv_handle_t* handle) {
	msg_info(logger,"server socket error");
	ASSERT(handle == server);
}




static int tcp4_echo_start(int port) 
{
	struct sockaddr_in addr;
	int r;

	ASSERT(0 == uv_ip4_addr("0.0.0.0", port, &addr));

	server = (uv_handle_t*)&tcpServer;
	serverType = TCP;

	r = uv_tcp_init(loop, &tcpServer);
	if (r) {
		/* TODO: Error codes */
		msg_error(logger, "Socket creation error\n");
		return 1;
	}

	r = uv_tcp_bind(&tcpServer, (const struct sockaddr*) &addr, 0);
	if (r) {
		/* TODO: Error codes */
		msg_error(logger, "Bind error\n");
		return 1;
	}

	r = uv_listen((uv_stream_t*)&tcpServer, SOMAXCONN, on_connection);
	if (r) {
		/* TODO: Error codes */
		msg_error(logger, Util::format("Listen error %s\n", uv_err_name(r)));
		return 1;
	}

	return 0;
}


static uv_timer_t timer_handle;

static void timer_cb(uv_timer_t* handle) {
	uv_timer_stop(&timer_handle);
	uv_timer_start(&timer_handle, timer_cb, 1000, 0);
}

#if 0
static uv_idle_t idle_handle;
uv_prepare_t uv_prepare_sleep;

static void idle_cb_main(uv_idle_t* handle)
{

  //static int idle_cb_called = 0;
	usleep(0);
}
#endif


int TcpServer::init()
{
	return 0;
}

int TcpServer::startService(int port)
{
	logger=Logger::getLogger("TcpServer");
	msg_info(logger,Util::format("listen port=%d",port).c_str());
	loop = uv_default_loop();

	if (tcp4_echo_start(port))
		return 1;
	return 0;
}
int TcpServer::run()
{

	msg_info(logger,"run....begin....");

	uv_timer_init(loop, &timer_handle);
	uv_timer_start(&timer_handle, timer_cb, 1000, 0);
	uv_run(loop, UV_RUN_DEFAULT);

	return 0;
}
//--------------------------------------------------------------------------------------
//       Class:  TcpServer
//      Method:  TcpServer
// Description:  constructor
//--------------------------------------------------------------------------------------
TcpServer::TcpServer ()
{

}  // -----  end of method TcpServer::TcpServer  (constructor)  ----- 


//--------------------------------------------------------------------------------------
//       Class:  TcpServer
//      Method:  ~TcpServer
// Description:  destructor
//--------------------------------------------------------------------------------------
TcpServer::~TcpServer ()
{
}  // -----  end of method TcpServer::~TcpServer  (destructor)  ----- 


#endif // _TcpServer_CPP_
