/*
 * =====================================================================================
 *
 *        Filename:  EVENTSTATE
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  07/05/2017 02:03:28 AM PDT
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
//        Class:  EventState
//  Description:
// =====================================================================================

#ifndef _EventState_H_
#define _EventState_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "uv.h"
#include "task.h"

typedef struct PackHeader{
	unsigned int  falg; //0x816e4566
	unsigned int  cmd; //command type
	unsigned int  type;
	unsigned int bodyLength;	
}PackHeader;
typedef struct EventState {
	time_t lastHeartTime;
	unsigned char  isWork;
	uv_stream_t  * client;
	uv_stream_t* server;
} EventState;
EventState * alloc_init_event_state();
void free_event_state(EventState * state);


typedef struct NwInputStream{
	unsigned char * buffer;
	int bufferSize;
}NwInputStream;
void initNwInputStream(NwInputStream * stream);
void freeNwInputStream(NwInputStream * stream);
#endif // _EventState_H_
