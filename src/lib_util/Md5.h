/*
 * =====================================================================================
 *
 *        Filename:  MD5
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  03/24/2011 08:25:11 PM CST
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  Thomas Young (Sir)
 *         Company:  yangliushun@movnow.com
 *           Email:  yangliushun@movnow.com
 *
 * =====================================================================================
 */



// =====================================================================================
//        Class:  Md5
//  Description:
// =====================================================================================

#ifndef _Md5_H_
#define _Md5_H_


#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

#include <string>
#include <stdint.h>
using namespace std;
/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;


#if !defined(INTEGRITY)
/* UINT2 defines a two byte word */
typedef uint16_t UINT2;
//typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef   uint32_t UINT4;
//typedef unsigned long int UINT4;
//typedef  int32_t UINT4
#endif

#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

typedef struct
{
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
}
MD5_CTX;

class Md5
{

public:

	// ====================  LIFECYCLE   =========================================

	Md5 ();                    // constructor
	Md5 ( const Md5 &other );  // copy constructor
	virtual ~Md5 ();                   // destructor

	int file_md5sum(const char * filename, char * md5_value, int md5_value_length);
	int mem_md5sum ( const char *apcBuffer, char *apcMd5, int aiSize ) ;
	// ====================  OPERATORS   =========================================

	 string fileMd5Sum(const char * filename);
	 string memMd5Sum(const char *apcBuffer);
	const Md5& operator = ( const Md5 &other );  // assignemnt operator

	virtual const char * class_name() const
	{
		return "Md5";
	};

	// ====================  OPERATIONS  =========================================

	// ====================  ACCESS      =========================================

	// ====================  INQUIRY     =========================================

protected:

private:
	/* void MD5Init PROTO_LIST ((MD5_CTX *)); */
	void MD5Init (MD5_CTX *context);
	/* void MD5Update PROTO_LIST */
	/*  ((MD5_CTX *, unsigned char *, unsigned int)); */
	void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
	/* void MD5Final PROTO_LIST ((unsigned char [16], MD5_CTX *)); */
	void MD5Final (unsigned char digest[16], MD5_CTX *context);
};  // -----  end of class  Md5  -----
#endif // _Md5_H_
