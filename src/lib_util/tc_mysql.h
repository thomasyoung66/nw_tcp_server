#ifndef __TC_MYSQL_H
#define __TC_MYSQL_H
#include <map>
#include <vector>
#include <stdlib.h>
#include <string>
#ifdef WIN32
#include <winsock.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif
//#include "util/tc_ex.h"
#include <stdarg.h>
using namespace std;
namespace taf
{

/**
* ���ݿ��쳣��
*/
#if 0
struct TC_Mysql_Exception : public TC_Exception {
	TC_Mysql_Exception(const string &sBuffer) : TC_Exception(sBuffer) {};
	~TC_Mysql_Exception() throw() {};
};
#endif

/**
* ���ݿ����ýӿ�
*/
struct TC_DBConf {
	/**
	* ������ַ
	*/
	string _host;

	/**
	* �û���
	*/
	string _user;

	/**
	* ����
	*/
	string _password;

	/**
	* ���ݿ�
	*/
	string _database;

	/**
	 * �ַ���
	 */
	string _charset;

	/**
	* �˿�
	*/
	int _port;

	/**
	* �ͻ��˱�ʶ
	*/
	int _flag;

	/**
	* ���캯��
	*/
	TC_DBConf()
		: _port(0)
		, _flag(0)
	{
	}

	/**
	* ��ȡ���ݿ�����
	* ������ַ
	* dbhost=
	* dbuser=
	* dbpass=
	* dbname=
	* dbport=
	* @param mpParam
	*/
	void loadFromMap(const map<string, string> &mpParam)
	{
		map<string, string> mpTmp = mpParam;

		_host        = mpTmp["dbhost"];
		_user        = mpTmp["dbuser"];
		_password    = mpTmp["dbpass"];
		_database    = mpTmp["dbname"];
		_charset     = mpTmp["charset"];
		_port        = atoi(mpTmp["dbport"].c_str());
		_flag        = 0;

		if(mpTmp["dbport"] == "") {
			_port = 3306;
		}
	}

};

/**
* Mysql���ݿ������
*/
class TC_Mysql
{
public:
	/**
	* contructor
	*/
	TC_Mysql();

	/**
	* contructor
	* @param sHost : ����IP
	* @param sUser : �û�
	* @param sPasswd : ����
	* @param sDatebase : ���ݿ�
	* @param port : �˿�
	* @param iUnixSocket : socket
	* @param iFlag : �ͻ��˱�ʶ
	*/
	TC_Mysql(const string& sHost, const string& sUser = "", const string& sPasswd = "", const string& sDatabase = "", const string &sCharSet = "", int port = 0, int iFlag = 0);

	/**
	* contructor
	* @param tcDBConf : ���ݿ�����
	*/
	TC_Mysql(const TC_DBConf& tcDBConf);

	/**
	* decontructor
	*/
	~TC_Mysql();

	/**
	* init ��ʼ��
	* @param sHost : ����IP
	* @param sUser : �û�
	* @param sPasswd : ����
	* @param sDatebase : ���ݿ�
	* @param port : �˿�
	* @param iUnixSocket : socket
	* @param iFlag : �ͻ��˱�ʶ
	* @return ��
	*/
	void init(const string& sHost, const string& sUser  = "", const string& sPasswd  = "", const string& sDatabase = "", const string &sCharSet = "", int port = 0, int iFlag = 0);

	/**
	* contructor
	* @param tcDBConf : ���ݿ�����
	*/
	void init(const TC_DBConf& tcDBConf);

	/**
	* connect �������ݿ�
	* @throws TC_Mysql_Exception
	* @return ��
	*/
	void connect();

	/**
	* DisConnect �Ͽ����ݿ�����
	* @return ��
	*/
	void disconnect();

	/**
	 * ��ȡ���ݿ����
	 *
	 * @return string
	 */
	string getVariables(const string &sName);

	/**
	* DisConnect ֱ�ӻ�ȡ���ݿ�ָ��
	* @return MYSQL* ��ȡ���ݿ�ָ��
	*/
	MYSQL *getMysql();

	/**
	* �ַ�ת��
	* @param sFrom : Դ�ַ���
	* @param sTo : ����ַ���
	* @return string ����ַ���
	*/
	string escapeString(const string& sFrom);

	/**
	* Update or insert ...
	* @param sSql : sql���
	* @throws TC_Mysql_Exception
	* @return void
	*/
	void execute(const string& sSql);

	/**
	 * mysql��һ����¼
	 */
	class MysqlRecord
	{
	public:
		/**
		 * ���캯��
		 * @param record
		 */
		MysqlRecord(const map<string, string> &record);
#if 0
		string toJsonString()
		{
			string res = "{";
			map<string, string>::const_iterator it;
			int n = 0;
			for(it = _record.begin(); it != _record.end(); it++) {
				res = res + "\"" + it->first + "\":\"" + it->second + (n == _record.size() ? "\"" : "\",");
				n++;
			}
			res = res + "}";
			return res;
		}
#endif
		/**
		 * ��ȡ����
		 * @param s
		 *
		 * @return string
		 */

		int getInt(const string &s);
		const string& operator[](const string &s);
	protected:
		const map<string, string> &_record;
	};

	/**
	 * ��ѯ������mysql����
	 */
	class MysqlData
	{
	public:
		/**
		 * ��������
		 *
		 * @return vector<map<string,string>>&
		 */
		vector<map<string, string> >& data();

		/**
		 * ���ݵļ�¼����
		 *
		 * @return size_t
		 */
		size_t size();
		string toJsonString();
		/**
		 * ��ȡĪһ����¼
		 * @param i
		 *
		 * @return MysqlRecord
		 */
		MysqlRecord operator[](size_t i);

	protected:
		vector<map<string, string> > _data;
	};

	/**
	* Query Record
	* @param sSql : sql���
	* @throws TC_Mysql_Exception
	* @return MysqlData
	*/
	MysqlData queryRecordFmt(const char * fmt,...);
	MysqlData queryRecord(const string& sSql);
	MysqlData queryRecord1(string sSql)
	{
		return queryRecord(sSql);
	}

	/**
	 * �����ֶ�����
	 */
	enum FT {
		DB_INT,     //��������
		DB_STR,     //�ַ�������
	};

	//���ݼ�¼
	typedef map<string, pair<FT, string> > RECORD_DATA;

	/**
	* Update Record
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @param sCondition : where�����,����:where A = B
	* @throws TC_Mysql_Exception
	* @return size_t Ӱ�������
	*/
	size_t updateRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns, const string &sCondition);

	/**
	* insert Record
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @throws TC_Mysql_Exception
	* @return size_t Ӱ�������
	*/
	size_t insertRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);

	/**
	* replace Record
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @throws TC_Mysql_Exception
	* @return size_t Ӱ�������
	*/
	size_t replaceRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);

	/**
	* Delete Record
	* @param sTableName : ����
	* @param sCondition : where�����,����:where A = B
	* @throws TC_Mysql_Exception
	* @return size_t Ӱ�������
	*/
	size_t deleteRecord(const string &sTableName, const string &sCondition = "");

	/**
	* ��ȡTable��ѯ�������Ŀ
	* @param sTableName : ���ڲ�ѯ�ı���
	* @param sCondition : where�����,����:where A = B
	* @throws TC_Mysql_Exception
	* @return size_t ��ѯ�ļ�¼��Ŀ
	*/
	size_t getRecordCount(const string& sTableName, const string &sCondition = "");

	/**
	* ��ȡSql���ؽ�����ĸ���
	* @param sCondition : where�����,����:where A = B
	* @throws TC_Mysql_Exception
	* @return ��ѯ�ļ�¼��Ŀ
	*/
	size_t getSqlCount(const string &sCondition = "");

	/**
	 * ���ڼ�¼
	 * @param sql
	 * @throws TC_Mysql_Exception
	 * @return bool
	 */
	bool existRecord(const string& sql);

	/**
	* ��ȡ�ֶ����ֵ
	* @param sTableName : ���ڲ�ѯ�ı���
	* @param sFieldName : ���ڲ�ѯ���ֶ�
	* @param sCondition : where�����,����:where A = B
	* @throws TC_Mysql_Exception
	* @return ��ѯ�ļ�¼��Ŀ
	*/
	int getMaxValue(const string& sTableName, const string& sFieldName, const string &sCondition = "");

	/**
	* ��ȡauto_increment�������ID
	* @return IDֵ
	*/
	long lastInsertID();

	/**
	* ����Insert-SQL���
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @return string insert-SQL���
	*/
	string buildInsertSQL(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);

	/**
	* ����Replace-SQL���
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @return string insert-SQL���
	*/
	string buildReplaceSQL(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);

	/**
	* ����Update-SQL���
	* @param sTableName : ����
	* @param mpColumns : ����/ֵ��
	* @param sCondition : where�����
	* @return string Update-SQL���
	*/
	string buildUpdateSQL(const string &sTableName, const map<string, pair<FT, string> > &mpColumns, const string &sCondition);

	/**
	 * ��ȡ���ִ�е�SQL���
	 *
	 * @return string
	 */
	string getLastSQL()
	{
		return _sLastSql;
	}

protected:
	/**
	* copy contructor
	* ֻ����,������,��֤����ʹ��
	*/
	TC_Mysql(const TC_Mysql &tcMysql);

	/**
	* =
	* ֻ����,������,��֤����ʹ��
	*/
	TC_Mysql &operator=(const TC_Mysql &tcMysql);


private:

	/**
	* ���ݿ�ָ��
	*/
	MYSQL 		*_pstMql;

	/**
	* ���ݿ�����
	*/
	TC_DBConf   _dbConf;

	/**
	* �Ƿ��Ѿ�����
	*/
	bool		_bConnected;

	/**
	 * ���ִ�е�sql
	 */
	string      _sLastSql;

};

}
#endif //_TC_MYSQL_H
