/***********************************************
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Created Time: 2017-01-23 14:11
 **********************************************/
#include <iostream>

string variable_list[30] = {"Com_insert","Com_update","Com_delete","Com_select","Questions","Innodb_row_lock_current_waits","Innodb_row_lock_time",
	"Created_tmp_disk_tables","Created_tmp_tables","Innodb_buffer_pool_reads","Innodb_buffer_pool_read_requests","Handler_read_first",
	"Handler_read_key","Handler_read_next","Handler_read_prev","Handler_read_rnd","Handler_read_rnd_next","Innodb_os_log_pending_fsyncs",
	"Innodb_os_log_pending_writes","Innodb_log_waits",
	"Threads_connected","Threads_running","us","sy","id","wa","si","cs","Bytes_sent","Bytes_received"};
void screen(string variable_name, uint *value,point_list *pl)
{
	/*
	 * this for c++11
	int i=0;
	for(string name : variable_list)
	{
		if(strcmp(variable_name,name))
		  save_value(value,pl,i);
		i++;
	}
	
	*/
	for(int i=0;i<30;i++)
	{
		if(variable_name == variable_list[i])
		  save_value(value,pl,i);
	}
	
}


