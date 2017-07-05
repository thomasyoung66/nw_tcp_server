/*
 * =====================================================================================
 *
 *        Filename:  UTIL
 *
 *     Description:  :
 *
 *         Version:  1.0
 *         Created:  05/14/2015 05:05:20 PM CST
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  YangLiuShun (Thomas Young), yangliushun@movnow.com
 *         Company:  www.movnow.com
 * =====================================================================================
 */

// =====================================================================================
//        Class:  Util
//  Description:
// =====================================================================================

#ifndef _Util_CPP_
#define _Util_CPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <netdb.h>
#include "Util.h"
#include "Md5.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>



//--------------------------------------------------------------------------------------
//       Class:  Util
//      Method:  Util
// Description:  constructor
//--------------------------------------------------------------------------------------
Util::Util ()
{
}  // -----  end of method Util::Util  (constructor)  -----


//--------------------------------------------------------------------------------------
//       Class:  Util
//      Method:  ~Util
// Description:  destructor
//--------------------------------------------------------------------------------------
Util::~Util ()
{
}  // -----  end of method Util::~Util  (destructor)  -----

string Util::format(const char * fmt,...)
{
    char buffer[4096];
    va_list ap;
    memset(buffer,0x00,sizeof(buffer));
    va_start(ap, fmt);
    vsnprintf(buffer,sizeof(buffer),fmt,ap);
    va_end(ap);
    return buffer;
}
int Util::mkdirs(const char * path){
	char fullPath[512];
	strcpy(fullPath, path);
	bool lastSep = 0;
	int len = strlen(path);
	for(int i = 0;i < len;i++){
		if(fullPath[i] == '/'){
			if(!lastSep){
				fullPath[i] = '\0';
				//printf("check dir:%s", fullPath);
				if (access(fullPath, F_OK)){
        			if(mkdir(fullPath, 0777)){
						return 1;
					}
				//	printf("create dir:%s", fullPath);
				}
				fullPath[i] = '/';
				lastSep = 1;
			}
		}else if(i == len - 1){
			//printf("check dir:%s", fullPath);
			if (access(fullPath, F_OK)){
        		if(mkdir(fullPath, 0777)){
					return 1;
				}
			//	printf("create dir:%s", fullPath);
			}
		}else{
			lastSep = 0;
		}
	}
	return 0;
}
/*
char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/pet/", gss->root_path);
    if (access(fullPath, F_OK))
        mkdir(fullPath, 0777);
    snprintf(fullPath, sizeof(fullPath), "%s/pet/%s/", gss->root_path, pid);
    if (access(fullPath, F_OK))
        mkdir(fullPath, 0777);
    return fullPath;
 * */
char * Util::strdup(const char * src)
{
	int length = 0;
	if (src == NULL || (length = strlen(src)) == 0)
		return NULL;
	char * res = (char *)malloc(length + 1);
	if (res == NULL)
		return NULL;
	strcpy(res, src);
	*(res + length) = '\0';
	return res;
}
map<int, string> Util::strToMap(const char * str, const char * split)
{
	map<int, string> res;
	if (str == NULL || split == NULL) {
		return res;
	}
	char * src = Util::strdup(str);
	if (src == NULL) {
		return res;
	}
	char * token = NULL;
	token = strtok(src, split);
	while(token) {
		res[res.size()] = token;
		token = strtok(NULL, split);
	}
	free(src);
	return res;
}

char * Util::LoadFileToMemory(const char * filename)
{
	char * lpcRet = NULL ;
	struct stat ltStat ;
	char * apcBuffer = NULL;
	int aiSize = 0;
	if ( stat ( filename, &ltStat ) == 0 ) {
		FILE * fp = fopen ( filename, "r" ) ;
		if ( fp != NULL ) {
			if ( apcBuffer == NULL ) {
				apcBuffer = (char *)malloc ( ltStat.st_size + 1 ) ;
				aiSize = ltStat.st_size + 1 ;
			}
			if ( apcBuffer != NULL && aiSize > 0 ) {
				fread ( apcBuffer, 1, aiSize, fp ) ;
				apcBuffer[aiSize - 1] = '\0' ;
				lpcRet = apcBuffer ;
			}
			fclose ( fp ) ;
		}
	}
	return lpcRet ;
}

unsigned int  Util::getSeq( const char * mac_addr )
{
	unsigned int h = 0;
	const unsigned char *k;
	if (mac_addr == NULL)
		return 0;

	for (k = (const unsigned char *)mac_addr; *k != '\0'; k++) {
		h *= 21257619;
		h ^= *k;
	}
	return h;
}

int Util::connectServer(const char * ip, int port, int timeout)
{
	int sockfd;
	struct sockaddr_in server_addr;
	static  struct hostent *host = NULL;
	if((host = gethostbyname(ip)) == NULL) {
		return -1;
	}
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return -1;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	if(Util::connect_nonb(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr), timeout) == -1) {
		return -1;
	}
	return sockfd;
}

int Util::connect_nonb(int sockfd, struct sockaddr *saptr, socklen_t salen, int nsec)
{
	int				flags, n, error;
	socklen_t		len;
	fd_set			rset, wset;
	struct timeval	tval;

	flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	error = 0;
	if ( (n = connect(sockfd, (struct sockaddr *) saptr, salen)) < 0)
		if (errno != EINPROGRESS)
			return(-1);

	/* Do whatever we want while the connect is taking place. */

	if (n == 0)
		goto done;	/* connect completed immediately */

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;
	tval.tv_sec = nsec;
	tval.tv_usec = 0;

	if ( (n = select(sockfd + 1, &rset, &wset, NULL,
	                 nsec ? &tval : NULL)) == 0) {
		close(sockfd);		/* timeout */
		errno = ETIMEDOUT;
		return(-1);
	}

	if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
		len = sizeof(error);
		if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			return(-1);			/* Solaris pending error */
	}
	else
		//err_quit("select error: sockfd not set");
		return (-1);

done:
	fcntl(sockfd, F_SETFL, flags);	/* restore file status flags */

	if (error) {
		close(sockfd);		/* just in case */
		errno = error;
		return(-1);
	}
	return(0);
}

string Util::getTime()
{
	char t[32];
    struct tm*stm;
    struct timeval tp;
    gettimeofday(&tp, NULL);
    stm = localtime( &tp.tv_sec );
    snprintf(t, sizeof(t), "%4d-%02d-%02d %02d:%02d:%02d",
             stm->tm_year + 1900, stm->tm_mon + 1, stm->tm_mday,
             stm->tm_hour, stm->tm_min, stm->tm_sec );
	return t;
}

int Util::readable_timeo(int fd, int sec, int usec)
{
	fd_set rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);
	tv.tv_sec = sec;
	tv.tv_usec = 0;
	return (select(fd + 1, &rset, NULL, NULL, &tv));
}

void Util::writeInt32(unsigned char * _pfree, int pos, uint32_t n)
{
	_pfree[pos + 3] = (unsigned char)n;
	n >>= 8;
	_pfree[pos + 2] = (unsigned char)n;
	n >>= 8;
	_pfree[pos + 1] = (unsigned char)n;
	n >>= 8;
	_pfree[pos + 0] = (unsigned char)n;
}

uint32_t Util::readInt32(unsigned char * _pdata, int pos)
{
	uint32_t n = _pdata[pos + 0];
	n <<= 8;
	n |= _pdata[pos + 1];
	n <<= 8;
	n |= _pdata[pos + 2];
	n <<= 8;
	n |= _pdata[pos + 3];
	_pdata += 4;
	return n;
}

ssize_t Util::writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = (const char *)vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
ssize_t	Util::readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = (char *)vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		}
		else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}
string Util::getUserPath(const char * rootPath,const char * uId)
{
	char fullPath[256];
	Md5 md;
	string 	md5=md.memMd5Sum(uId);
	//msglog(DEBUG,"====md5=%s=====uid=(%s)====",md5.c_str(),uId);
	memset(fullPath,0x00,sizeof(fullPath));
	snprintf(fullPath,sizeof(fullPath),"%s/%.*s",rootPath,2,md5.c_str());
	if (access(fullPath,F_OK))
		mkdir(fullPath,0777);
	snprintf(fullPath+strlen(fullPath),sizeof(fullPath)-strlen(fullPath),"/%.*s",2,md5.c_str()+2);
	if (access(fullPath,F_OK))
		mkdir(fullPath,0777);
	snprintf(fullPath+strlen(fullPath),sizeof(fullPath)-strlen(fullPath),"/%s",uId);
	if (access(fullPath,F_OK))
		mkdir(fullPath,0777);
	return fullPath;
}



void Util::hexdump(const void *_data, size_t size)
{
    const uint8_t *data = (const uint8_t *)_data;
    size_t offset = 0;


    while (offset < size) {
        printf("0x%02x  ", (int)offset);
        size_t n = size - offset;
        if (n > 16) {
            n = 16;
        }

        for (size_t i = 0; i < 16; ++i) {
            if (i == 8) {
                printf(" ");
            }
            if (offset + i < size) {
                printf("%02x ", data[offset + i]);

            } else {
                printf("   ");
            }
        }
        printf(" ");
        for (size_t i = 0; i < n; ++i) {
            if (isprint(data[offset + i])) {
                printf("%c", data[offset + i]);
            } else {
                printf(".");
            }
        }
        printf("\n");
        offset += 16;
    }

}

#endif

