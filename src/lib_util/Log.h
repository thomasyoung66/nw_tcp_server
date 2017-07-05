/*
 * =====================================================================================
 * 
 *        Filename:  LOG
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/04/2017 12:03:37 AM PDT
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
//        Class:  Log
//  Description:  
// =====================================================================================

#ifndef _Log_H_
#define _Log_H_

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/xml/domconfigurator.h>
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
#define msg_info	LOG4CXX_INFO
#define msg_debug	LOG4CXX_DEBUG
#define	msg_warn    LOG4CXX_WARN
#define msg_error	LOG4CXX_ERROR

class Log
{

  public:

    // ====================  LIFECYCLE   ========================================= 

    Log ();                    // constructor 
    Log ( const Log &other );  // copy constructor 
    ~Log ();                   // destructor 

    // ====================  OPERATORS   ========================================= 
	int init(const char * xmlFilename);
    const Log& operator = ( const Log &other );  // assignemnt operator 

	virtual const char * class_name() const { return "Log"; };
    
	// ====================  OPERATIONS  ========================================= 

    // ====================  ACCESS      ========================================= 

    // ====================  INQUIRY     ========================================= 

  protected:

  private:

};  // -----  end of class  Log  ----- 
#endif // _Log_H_
