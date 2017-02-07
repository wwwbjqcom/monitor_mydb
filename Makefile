monitor_mydb:Main.cpp MyDB.cpp 
	g++ -L/usr/lib64/mysql -lmysqlclient -o monitor_mydb Main.cpp MyDB.cpp 
