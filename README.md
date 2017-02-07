# monitor_mydb
centos/rehat:
        yum install gcc gcc-c++ mysql-devel -y

ubuntu/debian:
        apt-get install g++ libmysqld-dev -y

cd monitor_mydb && make;
