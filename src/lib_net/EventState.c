/*
 * =====================================================================================
 * 
 *        Filename:  EVENTSTATE
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/05/2017 02:03:30 AM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */


#ifndef _EventState_CPP_
#define _EventState_CPP_
#include "EventState.h"
EventState * alloc_init_event_state()
{
	EventState * state=(EventState *)malloc(sizeof(EventState));
	if (state==NULL)
		return NULL;
	state->lastHeartTime=0;
	state->isWork=0;
	return state;	
}
void free_event_state(EventState * state)
{
	if (state!=NULL)
		free(state);
}
#endif // _EventState_H_
