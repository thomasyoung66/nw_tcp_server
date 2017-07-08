/*
 * =====================================================================================
 *
 *        Filename:  APPLICATION
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  07/04/2017 12:26:40 AM PDT
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
//        Class:  Application
//  Description:
// =====================================================================================

#ifndef _Application_H_
#define _Application_H_

#include "Global.h"
extern "C" {
#include "../lib_util/iniparser.h"
}
#include "../lib_util/Log.h"
#include "../lib_util/Util.h"
#include "../lib_net/TcpServer.h"
#include "../lib_net/EventHandler.h"
class Application
{

public:

	// ====================  LIFECYCLE   =========================================

	Application (int argc, char * argv[]);                   // constructor
	Application ( const Application &other );  // copy constructor
	~Application ();                   // destructor

	// ====================  OPERATORS   =========================================

	const Application& operator = ( const Application &other );  // assignemnt operator

	virtual const char * class_name() const
	{
		return "Application";
	};

	Global g;
	int run();
	int init();
	void registerEventHandler(int cmdType,EventHandler * event);
	// ====================  OPERATIONS  =========================================

	// ====================  ACCESS      =========================================

	// ====================  INQUIRY     =========================================
	int initConfig(const char * path);
	Log * getLog()
	{
		return &log;
	}
protected:

private:
	Log log;
	TcpServer tcpServer;
	dictionary  *   ini ;
	LoggerPtr logger ;
};  // -----  end of class  Application  -----
extern Application * app;
#endif // _Application_H_
