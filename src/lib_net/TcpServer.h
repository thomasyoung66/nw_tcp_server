/*
 * =====================================================================================
 * 
 *        Filename:  TCPSERVER
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/04/2017 12:31:45 AM PDT
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
//        Class:  TcpServer
//  Description:  
// =====================================================================================

#ifndef _TcpServer_H_
#define _TcpServer_H_

#include "../lib_util/Log.h"
class TcpServer
{

  public:

    // ====================  LIFECYCLE   ========================================= 

    TcpServer ();                    // constructor 
    ~TcpServer ();                   // destructor 

    // ====================  OPERATORS   ========================================= 


	virtual const char * class_name() const { return "TcpServer"; };
	int init();
	int startService(int port);    
	int run();
	int workThreads;//最大工作线程
	int tcpIdleSeconds;//tcp最大空闲时间
	// ====================  OPERATIONS  ========================================= 

    // ====================  ACCESS      ========================================= 

    // ====================  INQUIRY     ========================================= 

  protected:

  private:
};  // -----  end of class  TcpServer  ----- 
#endif // _TcpServer_H_
