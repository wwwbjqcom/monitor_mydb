/***********************************************
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Created Time: 2017-01-23 14:11
 **********************************************/
#include <iostream>

void screen(string variable_name, uint *value,point_list *pl)
{
	if(variable_name == "Com_insert")
	   save_value(value,pl,0);
	else if(variable_name =="Com_update")
	  save_value(value,pl,1);
	else if(variable_name == "Com_delete")
	  save_value(value,pl,2);
	else if(variable_name == "Com_select")
	  save_value(value,pl,3);
	else if(variable_name == "Questions")
	  save_value(value,pl,4);
	else if(variable_name == "Innodb_row_lock_current_waits")
	  save_value(value,pl,5);
	else if(variable_name == "Created_tmp_disk_tables")
	  save_value(value,pl,6);
	else if(variable_name == "Created_tmp_tables")
	  save_value(value,pl,7);
	else if(variable_name == "Innodb_buffer_pool_reads")
	  save_value(value,pl,8);
	else if(variable_name == "Innodb_buffer_pool_read_requests")
	  save_value(value,pl,9);
	else if(variable_name == "Handler_read_first")
	  save_value(value,pl,10);
	else if(variable_name == "Handler_read_key")
	  save_value(value,pl,11);
	else if(variable_name == "Handler_read_next")
	  save_value(value,pl,12);
	else if(variable_name == "Handler_read_prev")
	  save_value(value,pl,13);
	else if(variable_name == "Handler_read_rnd")
	  save_value(value,pl,14);
	else if(variable_name == "Handler_read_rnd_next")
	  save_value(value,pl,15);
	else if(variable_name == "Innodb_os_log_pending_fsyncs")
	  save_value(value,pl,16);
	else if(variable_name == "Innodb_os_log_pending_writes")
	  save_value(value,pl,17);
	else if(variable_name == "Innodb_log_waits")
	  save_value(value,pl,18);
	else if(variable_name == "Threads_connected")
	  save_value(value,pl,19);
	else if(variable_name == "Threads_running")
	  save_value(value,pl,20);
	else if(variable_name == "Bytes_sent")
	  save_value(value,pl,27);
	else if(variable_name == "Bytes_received")
	  save_value(value,pl,28);
}


