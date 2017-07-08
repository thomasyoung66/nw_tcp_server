/*
 * =====================================================================================
 *
 *        Filename:  EVENTHANDLER
 *
 *     Description:
 *
 *         Version:  1.0
 *         Created:  07/05/2017 02:50:36 AM PDT
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
//        Class:  EventHandler
//  Description:
// =====================================================================================

#ifndef _EventHandler_H_
#define _EventHandler_H_
extern "C" {
#include "EventState.h"
}
class EventHandler
{

public:

	// ====================  LIFECYCLE   =========================================

	EventHandler ();                    // constructor
	~EventHandler ();                   // destructor

	// ====================  OPERATORS   =========================================


	virtual const char * class_name() const
	{
		return "EventHandler";
	};
	int executeHandler(EventState * state);

	// ====================  OPERATIONS  =========================================

	// ====================  ACCESS      =========================================

	// ====================  INQUIRY     =========================================

protected:

private:

};  // -----  end of class  EventHandler  -----
#endif // _EventHandler_H_
