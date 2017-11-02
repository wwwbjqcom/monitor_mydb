# monitor_mydb
监控mysql及cpu的status，对故障排查提供帮助，编译依赖：
centos/rehat:
        yum install make gcc gcc-c++ mysql-devel -y

ubuntu/debian:
        apt-get install make g++ libmysqld-dev -y

cd monitor_mydb && make;

在centos7系统make时有可能发生如下错误：
        MyDB.cpp:(.text+0xa5): undefined reference to `mysql_init'
        .......................................................
如果报错把Makefile删除用Makefile2替代再进行编译
