/***********************************************
 * File Name: entr.cpp
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Created Time: 2017-01-22 14:11
 **********************************************/
#include <iostream>
#include <cstdlib>
#include "MyDB.h"
#include <string>
#include "Help.h"
using namespace std;

int main(int argc, char ** argv)
{
	if(argc > 1)
	{
		for(int i=1;i<argc;i++)
		{
			if(string(argv[i]) == "-h")
			  show_help();
			else if(string(argv[i]) == "-run")
			{
				if(argc < 6)
				{
					cout << "Usage: [-h] [-run -u username -p passwd] " << endl;
					break;
				}
				else
				{
					MyDB db;
					db.initDB("127.0.0.1",argv[i+2],argv[i+4],"",atoi(argv[i+6]));
					db.exeSQL("show global status");
				}
			}
			else cout << "Usage: [-h] [-run -u username -p passwd] " << endl;
		}
	}
	else
	{
		cout << "Usage: [-h] [-run -u username -p passwd -P port] " << endl;
		
	}
	return 0;
}
