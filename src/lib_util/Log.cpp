/*
 * =====================================================================================
 * 
 *        Filename:  LOG
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/04/2017 12:02:54 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

// =====================================================================================
//        Class:  Log
//  Description:  
// =====================================================================================

#ifndef _Log_CPP_
#define _Log_CPP_

#include "Log.h"



//--------------------------------------------------------------------------------------
//       Class:  Log
//      Method:  Log
// Description:  constructor
//--------------------------------------------------------------------------------------
Log::Log ()
{
}  // -----  end of method Log::Log  (constructor)  ----- 

int Log::init(const char * xmlFilename)
{
	DOMConfigurator::configure(xmlFilename);

	LoggerPtr logger = Logger::getLogger("Application");
	msg_info(logger,"Appliction is start....");
//	LOG4CXX_DEBUG(logger,"<DEBUG-message>");
//	LOG4CXX_WARN(logger,"<WARN-message>");
//	LOG4CXX_ERROR(logger,"<ERROR-message>");

	return 0;
}
//--------------------------------------------------------------------------------------
//       Class:  Log
//      Method:  Log
// Description:  copy constructor
//--------------------------------------------------------------------------------------
Log::Log ( const Log &other )
{
}  // -----  end of method Log::Log  (copy constructor)  ----- 

//--------------------------------------------------------------------------------------
//       Class:  Log
//      Method:  ~Log
// Description:  destructor
//--------------------------------------------------------------------------------------
Log::~Log ()
{
}  // -----  end of method Log::~Log  (destructor)  ----- 

//--------------------------------------------------------------------------------------
//       Class:  Log
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
	const Log&
Log::operator = ( const Log &other )
{
	if(this!=&other)
	{
	}
	return *this;
}  // -----  end of method Log::operator =  (assignment operator)  ----- 

#endif // _Log_CPP_
