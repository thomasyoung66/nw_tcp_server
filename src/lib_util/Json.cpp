/*
 * =====================================================================================
 * 
 *        Filename:  JSON
 * 
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  07/06/2017 09:20:49 PM PDT
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  YangLiuShun (Thomas Young), 65619882@qq.com
 *         Company:  no name company
 * =====================================================================================
 */

// =====================================================================================
//        Class:  JsonParse
//  Description:  
// =====================================================================================

#ifndef _JsonParse_CPP_
#define _JsonParse_CPP_

#include "Json.h"

#include <fstream>
using namespace std;
/*
Json::Value myjson = getJsonFromFile(“test.json”);//利用上面的函数生成一个json。

Json::Value::Members members(myjson.getMemberNames());

for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)  {
const std::string &key = *it;
}
*/
//--------------------------------------------------------------------------------------
//       Class:  JsonParse
//      Method:  JsonParse
// Description:  constructor
//--------------------------------------------------------------------------------------
JsonParse::JsonParse ()
{
}  // -----  end of method JsonParse::JsonParse  (constructor)  ----- 



int JsonParse::getJsonFromFile(const char* fileName){  
    ifstream file(fileName);  
    if(!reader.parse(file, root, false )) 
	{  
		return -1;
    }  
	return 0;
}
int JsonParse::parse(const char * jsonString)
{
	reader.parse(jsonString, root);
	return 0;
}

//--------------------------------------------------------------------------------------
//       Class:  JsonParse
//      Method:  ~JsonParse
// Description:  destructor
//--------------------------------------------------------------------------------------
JsonParse::~JsonParse ()
{
}  // -----  end of method JsonParse::~JsonParse  (destructor)  ----- 


#endif // _JsonParse_CPP_
