/*********************************************
 * File Name: MyDB.cpp
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Create Time: 2017-01-27 11:44
 * impact: Operation mysql db
 * ******************************************/
#include <typeinfo>
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>
#include "MyDB.h"
#include "ExPo.h"
#include "Variable.h"

ulong while_num=0;



MyDB::MyDB()
{
	connection = mysql_init(NULL); //Initialize the DB
	if(connection == NULL)
	{
		cout << "Initialize Error:" << mysql_error(connection) <<endl;
		exit(1);
	}
}


MyDB::~MyDB()
{
	if(connection != NULL)
	{
		mysql_close(connection);
	}
}


bool MyDB::initDB(string host,string user,string pwd,string db_name,int port)
{
	//function mysql_real_connect create db connnection
	//if successful retrun MYSQL *point,else retrun NULL
	connection = mysql_real_connect(connection,host.c_str(),user.c_str(),
				pwd.c_str(),db_name.c_str(),port,NULL,0);
	if(connection == NULL)
	{
		cout << "Connection Error:" << mysql_error(connection) << endl;
		exit(1);
	}
	return true;
}

bool MyDB::exeSQL(string sql)
{
	Cpu_info *cf = new Cpu_info;
	Cpu_info *old_cf = new Cpu_info;
	point_list *pl = new point_list[29];
	for(int i=0;i<29;i++)
	{
		pl[i].point_name = head_name[i].name;
	}
	value_point(pl);


	for(;;)
	{
		
		//if mysql_query() successful then retrun 0,else return !0
		if(mysql_query(connection,sql.c_str()))
		{
			cout << "Query Error:" << mysql_error(connection) << endl;
			exit(1);
		}
		else
		{
			result = mysql_store_result(connection); // obtain result
			// mysql_fild_count() return for connection selectd the number of columns
			int rows = mysql_num_rows(result);
			
			// print head
			if(while_num == 0 || while_num%30 == 0)
			{
				print_head();
			}
		
			for(int i=0;i <= rows;i++)
			{	
				uint value;
				row = mysql_fetch_row(result);
				if(row <=0)
				{
					break;
				}
			
				string variable_name = string(row[0]);

				//Determine whether is -1
				string _value = string(row[1]);
				if(_value != "-1" )
				{
					value = atoi(row[1]);
				}
				else
				{
					value = 0;
				}

				screen(variable_name,&value,pl);

			}
			//cpu info
			obtain_sys_cpu(pl,cf,old_cf);
				
			// print values
			if(while_num>0)
			{
				cout_value(pl);
			}
			mysql_free_result(result);
		}
		while_num++;
		sleep(1);
	}
	return true;
}


