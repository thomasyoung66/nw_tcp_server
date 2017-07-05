/*
 * =====================================================================================
 *
 *        Filename:  UTIL
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  05/14/2015 05:06:52 PM CST
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  YangLiuShun (Thomas Young)
 *         Company:  www.movnow.com
 *           Email:  yangliushun@movnow.com
 *
 * =====================================================================================
 */



// =====================================================================================
//        Class:  Util
//  Description:  :w
//
// =====================================================================================

#ifndef _Util_H_
#define _Util_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#define MN_OK 0
#define MN_FAIL -1
#ifndef MAX_PATH
#define MAX_PATH 256
#endif
using namespace std;


class Util
{

public:

	// ====================  LIFECYCLE   =========================================

	Util ();                    // constructor
	~Util ();                   // destructor

	// ====================  OPERATORS   =========================================

	const Util& operator = ( const Util &other );  // assignemnt operator

	virtual const char * class_name() const
	{
		return "Util";
	};
	static string format(const char * fmt,...);
	static int mkdirs(const char * path);
	static string getTime();
	static char * LoadFileToMemory(const char * filename);
	static char * strdup(const char * src);
	static map<int, std::string> strToMap(const char * str, const char * split);
	static unsigned int  getSeq( const char * mac_addr );
	static int connect_nonb(int sockfd,  struct sockaddr *saptr, socklen_t salen, int nsec);

	static int connectServer(const char * ip, int port, int timeout);
	static int readable_timeo(int fd, int sec, int usec);
	static void writeInt32(unsigned char * _pfree, int pos, uint32_t n);
	static uint32_t readInt32(unsigned char * _pdata, int pos);
	static ssize_t	readn(int fd, void *vptr, size_t n);
	static ssize_t writen(int fd, const void *vptr, size_t n);
	static string getUserPath(const char * rootPath,const char * uId);
	static void hexdump(const void *_data, size_t size);
	static int sendUdp(const char * host, int port, const char * content);
	// ====================  OPERATIONS  =========================================
	// ====================  ACCESS      =========================================
	// ====================  INQUIRY     =========================================

protected:

private:

};  // -----  end of class  Util  -----
#endif // _Util_H_
