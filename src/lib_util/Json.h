/*
 * =====================================================================================
 * 
 *        Filename:  JSON
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/06/2017 09:21:11 PM PDT
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
//        Class:  JsonParse
//  Description:  
// =====================================================================================

#ifndef _JsonParse_H_
#define _JsonParse_H_

#include "json/json.h"
class JsonParse
{

  public:

    // ====================  LIFECYCLE   ========================================= 

    JsonParse ();                    // constructor 
    ~JsonParse ();                   // destructor 

    // ====================  OPERATORS   ========================================= 


	virtual const char * class_name() const { return "JsonParse"; };
    
	// ====================  OPERATIONS  ========================================= 

    // ====================  ACCESS      ========================================= 

    // ====================  INQUIRY     ========================================= 
	Json::Value root;
	Json::Reader reader;

	int getJsonFromFile(const char* fileName);
	int parse(const char * jsonString);
  protected:

  private:

};  // -----  end of class  JsonParse  ----- 
#endif // _JsonParse_H_
