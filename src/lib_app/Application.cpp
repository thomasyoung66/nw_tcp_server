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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Application.h"
#include "../lib_util/Log.h"

Application * app;
int Application::initConfig(const char * path)
{
	return 0;
}

//--------------------------------------------------------------------------------------
//       Class:  Application
//      Method:  Application
// Description:  constructor
//--------------------------------------------------------------------------------------
Application::Application (int argc,char * argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "c:")) != -1) {
		switch (opt) {
			case 'c':
				ini=iniparser_load(optarg);	
				break;
			case 't':
				//nsecs = atoi(optarg);
				break;
			default: /* '?' */
				fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if (ini==NULL){
		fprintf(stderr,"Open appliaction ini filename error\n");
		exit(0);
	}
	//init the log4cxx 
	log.init(iniparser_getstring(ini,"log4cxx:log4cxx_path",""));
	logger=Logger::getLogger("Application");

	app=this;
}  // -----  end of method Application::Application  (constructor)  ----- 

int Application::init()
{
	tcpServer.init();
	return 0;

}
int Application::run()
{
	int port=iniparser_getint(ini,"tcp_server:listen_port",0);
	tcpServer.workThreads=iniparser_getint(ini,"tcp_server:work_thread",4);
	tcpServer.tcpIdleSeconds=iniparser_getint(ini,"tcp_server:tcp_idle_time",0);
	LOG4CXX_INFO(logger,Util::format("tcp listen port=%d max work thread=%d idle=%d",
			port,tcpServer.workThreads,tcpServer.tcpIdleSeconds).c_str());	
	tcpServer.startService(port);
	tcpServer.run();
	return 0;
}
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
