/*
 * =====================================================================================
 *
 *        Filename:  GLOBAL
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  07/04/2017 12:29:59 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  YangLiuShun (Thomas Young)
 *         Company:  no name company
 *           Email:  65619882@qq.com
 *
 * =====================================================================================
 */



// =====================================================================================
//        Class:  Global
//  Description:
// =====================================================================================

#ifndef _Global_H_
#define _Global_H_

class Global
{

public:

	// ====================  LIFECYCLE   =========================================

	Global ();                    // constructor
	Global ( const Global &other );  // copy constructor
	~Global ();                   // destructor

	// ====================  OPERATORS   =========================================

	const Global& operator = ( const Global &other );  // assignemnt operator

	virtual const char * class_name() const
	{
		return "Global";
	};

	// ====================  OPERATIONS  =========================================

	// ====================  ACCESS      =========================================

	// ====================  INQUIRY     =========================================

protected:

private:

};  // -----  end of class  Global  -----
#endif // _Global_H_
