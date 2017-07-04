/*
 * =====================================================================================
 *
 *        Filename:  BASE64
 *
 *     Description:  :
 *
 *         Version:  1.0
 *         Created:  03/24/2011 08:26:24 PM CST
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  Thomas Young (Sir)
 *         Company:  
 *           Email:  yangliushun@movnow.com
 *
 * =====================================================================================
 */



// =====================================================================================
//        Class:  Base64
//  Description:
// =====================================================================================

#ifndef _Base64_H_
#define _Base64_H_
#include <string>
using namespace std;
class Base64
{

public:

	// ====================  LIFECYCLE   =========================================

	Base64 ();                    // constructor
	Base64 ( const Base64 &other );  // copy constructor
	virtual ~Base64 ();                   // destructor

	// ====================  OPERATORS   =========================================

	const Base64& operator = ( const Base64 &other );  // assignemnt operator

	virtual const char * class_name() const
	{
		return "Base64";
	};

	static string Encode(char *buf, int len);
	static string Decode(char *buf);
	// ====================  OPERATIONS  =========================================
	// ====================  ACCESS      =========================================
	// ====================  INQUIRY     =========================================

protected:

private:

};  // -----  end of class  Base64  -----
#endif // _Base64_H_
