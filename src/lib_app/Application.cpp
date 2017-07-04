/*
 * =====================================================================================
 * 
 *        Filename:  APPLICATION
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/04/2017 12:26:15 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

// =====================================================================================
//        Class:  Application
//  Description:  
// =====================================================================================

#ifndef _Application_CPP_
#define _Application_CPP_

#include "Application.h"


//--------------------------------------------------------------------------------------
//       Class:  Application
//      Method:  Application
// Description:  constructor
//--------------------------------------------------------------------------------------
Application::Application ()
{
}  // -----  end of method Application::Application  (constructor)  ----- 

//--------------------------------------------------------------------------------------
//       Class:  Application
//      Method:  Application
// Description:  copy constructor
//--------------------------------------------------------------------------------------
Application::Application ( const Application &other )
{
}  // -----  end of method Application::Application  (copy constructor)  ----- 

//--------------------------------------------------------------------------------------
//       Class:  Application
//      Method:  ~Application
// Description:  destructor
//--------------------------------------------------------------------------------------
Application::~Application ()
{
}  // -----  end of method Application::~Application  (destructor)  ----- 

//--------------------------------------------------------------------------------------
//       Class:  Application
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
const Application&
Application::operator = ( const Application &other )
{
  if(this!=&other)
  {
  }
  return *this;
}  // -----  end of method Application::operator =  (assignment operator)  ----- 

#endif // _Application_CPP_
