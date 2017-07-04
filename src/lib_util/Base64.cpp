/*
 * =====================================================================================
 *
 *        Filename:  BASE64
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  03/24/2011 08:26:06 PM CST
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  Thomas Young (Sir), yangliushun@movnow.com
 *         Company:  www.movnow.com
 * =====================================================================================
 */

// =====================================================================================
//        Class:  Base64
//  Description:
// =====================================================================================

#ifndef _Base64_CPP_
#define _Base64_CPP_

#include "Base64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int base64decode_len(const char *bufcoded, int buflen);
static int base64decode(char *bufplain, const char *bufcoded, int buflen);
static int base64decode_binary(unsigned char *bufplain, const char *bufcoded, int buflen);
static int base64encode_len(int len);
static int base64encode(char *encoded, const char *string, int len);
static int base64encode_binary(char *encoded, const unsigned char *string, int len);
static const unsigned char asctable[256] = {
	/* ASCII table */
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

int base64decode_len(const char *bufcoded, int buflen)
{
	int nbytesdecoded;
	const unsigned char *bufin;
	int nprbytes;

	bufin = (const unsigned char *) bufcoded;

	while ((asctable[*bufin] <= 63) && (buflen != 0)) {
		bufin++;
		buflen--;
	}

	nprbytes = bufin - (const unsigned char *) bufcoded;

	nbytesdecoded = (nprbytes * 3) / 4;

	return nbytesdecoded;
}

int base64decode(char *bufplain, const char *bufcoded, int buflen)
{
	int len;

	len = base64decode_binary((unsigned char *) bufplain, bufcoded, buflen);
	bufplain[len] = '\0';
	return len;
}

int base64decode_binary(unsigned char *bufplain,
                        const char *bufcoded, int buflen)
{
	int nbytesdecoded;
	const unsigned char *bufin;
	unsigned char *bufout;
	int nprbytes;

	bufin = (const unsigned char *) bufcoded;

	while ((asctable[*bufin] <= 63) && (buflen != 0)) {
		bufin++;
		buflen--;
	}

	nprbytes = bufin - (const unsigned char *) bufcoded;

	nbytesdecoded = ((nprbytes + 3) / 4) * 3;

	bufout = (unsigned char *) bufplain;
	bufin = (const unsigned char *) bufcoded;

	while (nprbytes > 4) {
		*(bufout++) =
		    (unsigned char) (asctable[*bufin] << 2 | asctable[bufin[1]] >> 4);
		*(bufout++) =
		    (unsigned char) (asctable[bufin[1]] << 4 | asctable[bufin[2]] >> 2);
		*(bufout++) =
		    (unsigned char) (asctable[bufin[2]] << 6 | asctable[bufin[3]]);
		bufin += 4;
		nprbytes -= 4;
	}

	if (nprbytes > 1) {
		*(bufout++) =
		    (unsigned char) (asctable[*bufin] << 2 | asctable[bufin[1]] >> 4);
	}

	if (nprbytes > 2) {
		*(bufout++) =
		    (unsigned char) (asctable[bufin[1]] << 4 | asctable[bufin[2]] >> 2);
	}

	if (nprbytes > 3) {
		*(bufout++) =
		    (unsigned char) (asctable[bufin[2]] << 6 | asctable[bufin[3]]);
	}

	nbytesdecoded -= (4 - nprbytes) & 3;

	return nbytesdecoded;
}


static const char basis_64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int base64encode_len(int len)
{
	return ((len + 2) / 3 * 4) + 1;
}


int base64encode(char *encoded, const char *str, int len)
{
	return base64encode_binary(encoded, (const unsigned char *) str, len);
}

int base64encode_binary(char *encoded,
                        const unsigned char *str, int len)
{
	int i;
	char *p;

	p = encoded;

	for (i = 0; i < len - 2; i += 3) {
		*p++ = basis_64[(str[i] >> 2) & 0x3F];
		*p++ = basis_64[((str[i] & 0x3) << 4) |
		                ((int) (str[i + 1] & 0xF0) >> 4)];
		*p++ = basis_64[((str[i + 1] & 0xF) << 2) |
		                ((int) (str[i + 2] & 0xC0) >> 6)];
		*p++ = basis_64[str[i + 2] & 0x3F];
	}

	if (i < len) {
		*p++ = basis_64[(str[i] >> 2) & 0x3F];

		if (i == (len - 1)) {
			*p++ = basis_64[((str[i] & 0x3) << 4)];
			*p++ = '=';
		}
		else {
			*p++ = basis_64[((str[i] & 0x3) << 4) |
			                ((int) (str[i + 1] & 0xF0) >> 4)];
			*p++ = basis_64[((str[i + 1] & 0xF) << 2)];
		}

		*p++ = '=';
	}

	*p++ = '\0';

	return p - encoded;
}

/* convenience functions for j2 */
string Base64::Encode(char *buf, int len)
{
	int elen;
	char *out;

	if (len == 0)
		len = strlen(buf);

	elen = base64encode_len(len);

	out = (char *)malloc(elen + 1);
	memset(out,0x00,elen+1);
	base64encode(out, buf, len);
	string str = out;
	free(out);
	return str;
}

string Base64::Decode(char *buf)
{
	if (buf==NULL || strlen(buf)<=0)
		return "";
	int elen;
	char *out;
	elen = base64decode_len(buf, -1);
	if (elen==0){
		return buf;
	}
	
	out = (char *)malloc(elen+1);
	memset(out,0x00,elen+1);

	base64decode(out, buf, -1);
	string input=Encode(out,elen);
	if (strcmp(input.c_str(),buf)){
		free(out);
		return buf;
	}
	string str =out;
	free(out);
	return str;
}

//--------------------------------------------------------------------------------------
//       Class:  Base64
//      Method:  Base64
// Description:  constructor
//--------------------------------------------------------------------------------------
Base64::Base64 ()
{
}  // -----  end of method Base64::Base64  (constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Base64
//      Method:  Base64
// Description:  copy constructor
//--------------------------------------------------------------------------------------
Base64::Base64 ( const Base64 &other )
{
}  // -----  end of method Base64::Base64  (copy constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Base64
//      Method:  ~Base64
// Description:  destructor
//--------------------------------------------------------------------------------------
Base64::~Base64 ()
{
}  // -----  end of method Base64::~Base64  (destructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Base64
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
const Base64&
Base64::operator = ( const Base64 &other )
{
	if(this != &other) {
	}
	return *this;
}  // -----  end of method Base64::operator =  (assignment operator)  -----

#endif // _Base64_CPP_
