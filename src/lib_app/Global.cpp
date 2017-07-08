/*
 * =====================================================================================
 *
 *        Filename:  GLOBAL
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  07/04/2017 12:29:34 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

// =====================================================================================
//        Class:  Global
//  Description:
// =====================================================================================

#ifndef _Global_CPP_
#define _Global_CPP_

#include "Global.h"


//--------------------------------------------------------------------------------------
//       Class:  Global
//      Method:  Global
// Description:  constructor
//--------------------------------------------------------------------------------------
Global::Global ()
{
}  // -----  end of method Global::Global  (constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Global
//      Method:  Global
// Description:  copy constructor
//--------------------------------------------------------------------------------------
Global::Global ( const Global &other )
{
}  // -----  end of method Global::Global  (copy constructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Global
//      Method:  ~Global
// Description:  destructor
//--------------------------------------------------------------------------------------
Global::~Global ()
{
}  // -----  end of method Global::~Global  (destructor)  -----

//--------------------------------------------------------------------------------------
//       Class:  Global
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
const Global&
Global::operator = ( const Global &other )
{
	if(this != &other) {
	}
	return *this;
}  // -----  end of method Global::operator =  (assignment operator)  -----

#endif // _Global_CPP_
