# monitor_mydb
监控mysql及cpu的status，对故障排查提供帮助，编译依赖：
centos/rehat:
        yum install make gcc gcc-c++ mysql-devel -y

ubuntu/debian:
        apt-get install make g++ libmysqld-dev -y

cd monitor_mydb && make;
