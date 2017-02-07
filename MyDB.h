/***********************************************
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Created Time: 2017-01-22 14:11
 **********************************************/
#ifndef _MYBD_H_
#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;

class MyDB
{
	public:
		MyDB();
		~MyDB();
		bool initDB(string host,string user,string pwd,
					string db_name,int port);
		bool exeSQL(string sql);
	private:
		MYSQL *connection;
		MYSQL_RES *result;
		MYSQL_ROW row;
};

#endif


