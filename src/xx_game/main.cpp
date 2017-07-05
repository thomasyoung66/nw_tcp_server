/*
 * =====================================================================================
 * 
 *        Filename:  MAIN
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/03/2017 11:50:10 PM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>

#include "../lib_app/Application.h"

int main(int argc,char * argv[])
{
	Application app(argc,argv);
	app.run();
	return 0;
}

#endif  

