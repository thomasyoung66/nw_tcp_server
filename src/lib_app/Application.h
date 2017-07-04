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

class Application
{

  public:

    // ====================  LIFECYCLE   ========================================= 

    Application ();                    // constructor 
    Application ( const Application &other );  // copy constructor 
    ~Application ();                   // destructor 

    // ====================  OPERATORS   ========================================= 

    const Application& operator = ( const Application &other );  // assignemnt operator 

	virtual const char * class_name() const { return "Application"; };
    
	// ====================  OPERATIONS  ========================================= 

    // ====================  ACCESS      ========================================= 

    // ====================  INQUIRY     ========================================= 

  protected:

  private:

};  // -----  end of class  Application  ----- 
#endif // _Application_H_
