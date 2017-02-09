/***********************************************
 * Author: xiaozhong
 * E-mail: xiaojiezhong991@163.com
 * Created Time: 2017-02-07 11:11
 **********************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

//system
typedef struct
{
	char name[4];
	long long user;
	long long nice;
	long long system;
	long long idle;
	long long iowait;
	long long irq;
	long long softirq;
	long long steal;
	long long guest;
	long long ctxt;
}Cpu_info;


//mysql
typedef struct
{
    uint old_data;
	uint current_data;
	double cpu_data;
}data_current;


typedef struct
{
    string name;
}HEAD_NAME;
HEAD_NAME head_name[30]={"ins","upd","del","sel","qus","wai","tim","cdt","ctt"," pr"," rr",
	"hrf","hrk","hrn","hrp","hrr","rrn","p_f","p_w","wai","con","run","us","sy","id","wa","si","cs","sen","rec"};


typedef struct
{
	string point_name;
	data_current *point_dic;
}point_list;



inline void save_value(uint *data,point_list *pl,int index);
inline void print_head();
inline string obtain_time();
inline void obtain_sys_cpu(point_list *pl,Cpu_info *cf,Cpu_info *old_cf);


//print halving line
void halving_line(int num)
{
	if(num>0) halving_line(num-1);
	cout << "\033[32m-\033[0m";
}

//save point for every struct point
inline void value_point(point_list *pl)
{
	for(int i=0;i<30;i++)
	{
		data_current *dc = new data_current;
		pl[i].point_dic = dc;

	}
}

//print value
inline void cout_value(point_list *pl)
{
	cout <<  left << "\033[33m" << obtain_time() << setw(1) << "\033[32m|\033[0m";
	//qps
	cout <<  right << setw(5) << pl[0].point_dic->current_data << setw(1) << " ";
	cout <<  right <<setw(5) << pl[1].point_dic->current_data << setw(1) << " ";
	cout <<  right <<setw(5) << pl[2].point_dic->current_data << setw(1) << " ";
							     
	cout <<  right <<setw(5) << pl[3].point_dic->current_data << setw(1) << " ";
	cout <<  right <<setw(5) << pl[4].point_dic->current_data << "\033[33m" << setw(1) << "|" << "\033[0m";
	//locks
	cout <<  right <<setw(3) << pl[5].point_dic->current_data << setw(1) << " ";
	cout <<  right <<setw(5) << pl[6].point_dic->current_data << "\033[33m" << setw(1) << "|"<<"\033[0m";
	//tmp_tables
	cout <<  right << setw(4) << pl[7].point_dic->current_data << setw(1) << " ";
	cout << right << setw(4) << pl[8].point_dic->current_data << "\033[33m" << setw(2) << "|"<<"\033[0m";
	//innodb_buffer
	cout << right << setw(6) << pl[9].point_dic->current_data << setw(1) << " ";
	cout << right << setw(8) << pl[10].point_dic->current_data << "\033[33m" << setw(1) << "|"<<"\033[0m";
	//handler
	cout << right << setw(7) << pl[11].point_dic->current_data << setw(1) << " ";
	cout << right << setw(7) << pl[12].point_dic->current_data << setw(1) << " ";
	cout << right << setw(7) << pl[13].point_dic->current_data << setw(1) << " ";
	cout << right << setw(7) << pl[14].point_dic->current_data << setw(1) << " ";
	cout << right << setw(7) << pl[15].point_dic->current_data << setw(1) << " ";
	cout << right << setw(7) << pl[16].point_dic->current_data << "\033[33m" << setw(1) << "|"<<"\033[0m";
	//innodb log
	cout << right << setw(3) << pl[17].point_dic->current_data << setw(1) << " ";
	cout << right << setw(3) << pl[18].point_dic->current_data << setw(1) << " ";
	cout << right << setw(3) << pl[19].point_dic->current_data << "\033[33m" << setw(1) << "|"<<"\033[0m";

	//thread
	cout << right << setw(4) << pl[20].point_dic->current_data << setw(1) << " ";
	cout << right << setw(3) << pl[21].point_dic->current_data << "\033[33m" << setw(1) << "|"<<"\033[0m";

	//cpu
	cout.setf(ios::fixed);
	cout.precision(0);
	cout << right << setw(3) << pl[22].point_dic->cpu_data << setw(1) << " ";
	cout << right << setw(3) << pl[23].point_dic->cpu_data << setw(1) << " ";
	cout << right << setw(3) << pl[24].point_dic->cpu_data << setw(1) << " ";
	cout << right << setw(3) << pl[25].point_dic->cpu_data << setw(1) << " ";
	cout << right << setw(3) << pl[26].point_dic->cpu_data << setw(1) << " ";
	cout << right << setw(5) << pl[27].point_dic->current_data << "\033[33m" << setw(1) << "|" << "\033[0m";

	//NET
	cout.precision(1);
	cout << right << setw(4) << float(float(pl[28].point_dic->current_data)/1024/1024) << "m" << setw(1) << " ";
	cout << right << setw(4) << float(float(pl[29].point_dic->current_data)/1024/1024) << "m";
	cout << "\033[32m"<< "|" <<"\033[0m" << endl;
}

inline string obtain_time()
{
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	char   current_time[20];
	strftime(current_time, 10, "%X", localtime(&rawtime));
	return current_time;
}


//print head
inline void print_head()
{
	cout << "\033[42m" << setw(39) << "QPS|" << "\033[0m" ;
	cout << "\033[31m" << setw(9) << "lock" << "\033[32m|\033[0m" ;
	cout << "\033[31m" << setw(10) << "tmp_table" << "\033[32m|\033[0m" ;
	cout << "\033[31m" << setw(15) << "innodb_buf"<< "\033[32m|\033[0m" ;
	cout << "\033[42m" << setw(47) << "Handler" << "\033[32m|\033[0m" ;
	cout << "\033[31m" << setw(11) << "innodb_log" << "\033[32m|\033[0m";
	cout << "\033[31m" << setw(8) << "thread" << "\033[32m|\033[0m";
	cout << "\033[42m" << setw(25) << "CPU" << "\033[32m|\033[0m" ;
	cout << "\033[31m" << setw(11) << "NET" << "\033[32m|\033[0m" << endl;

	halving_line(182);
	cout << endl;
	cout << left << setw(9) <<"\033[32m" << "time" << "|";

	for(int i=0;i<5;i++)
	{

		if(i==3)
		{   
			cout << right << "\033[32m" << setw(5) << head_name[i].name << setw(1) << " ";
		}   
		else if(i==4)
		{   
			cout << right << "\033[32m" << setw(5) << head_name[i].name << setw(1) << "|";
		}   
		else
		{   
			cout << right << "\033[32m" << setw(5) << head_name[i].name << setw(1) << " ";
		}   
	}   
	//lock
	cout << right << "\033[32m" << setw(3) << head_name[5].name << setw(1) << "";
	cout << right << "\033[32m" << setw(5) << head_name[6].name << setw(1) << "|";
	//tmp_table
	cout << right << "\033[32m" << setw(4) << head_name[7].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(4) << head_name[8].name << setw(2) << "|";

	//buffer
	cout << right << "\033[32m" << setw(6) << head_name[9].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(8) << head_name[10].name << setw(1) << "|";

	//Handler head
	for(int i=11;i<17;i++)
	{
		if(i==16)
		{
			cout << right << "\033[32m" << setw(7) << head_name[i].name << setw(1) << "|";
		}
		else
		{
			cout << right << "\033[32m" << setw(7) << head_name[i].name << setw(1) << " ";
		}
	}
	//innodb_log
	cout << right << "\033[32m" << setw(3) << head_name[17].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[18].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[19].name << setw(1) << "|";

	//thread
	cout << right << "\033[32m" << setw(4) << head_name[20].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[21].name << setw(1) << "|";

	//cpu
	cout << right << "\033[32m" << setw(3) << head_name[22].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[23].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[24].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[25].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(3) << head_name[26].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(5) << head_name[27].name << setw(1) << "|";

	//NET
	cout << right << "\033[32m" << setw(5) << head_name[28].name << setw(1) << " ";
	cout << right << "\033[32m" << setw(5) << head_name[29].name;
	cout << "|"<< endl << "\033[0m";

	halving_line(182);
	cout << endl;
}

//save value for every variable
inline void save_value(uint *data,point_list *pl,int index)
{
	if(!pl[index].point_dic->old_data)
	{
			pl[index].point_dic->old_data = *data;
			pl[index].point_dic->current_data = *data;
	}
	else
	{
		if(index == 17 || index == 18 || index == 19 || index == 20 || index == 21)
		{
			pl[index].point_dic->current_data = *data;
		}
		else
		{
			pl[index].point_dic->current_data = *data - pl[index].point_dic->old_data;
			pl[index].point_dic->old_data = *data;
		}
	}
}

inline void obtain_sys_cpu(point_list *pl,Cpu_info *cf,Cpu_info *old_cf)
{
	//Cpu_info *cf = new Cpu_info;

	string _data;
	string data;
	string ctxt_data;
	ifstream infile;
	infile.open("/proc/stat");
	int i = 1;
	while(getline(infile, _data))
	{
		if(i==1)
			data = _data;
		if(_data.find("ctxt") != string::npos)
			ctxt_data = _data;
		i++;
	}
	stringstream ss;
	ss.str(data);

	ss >> cf->name >> cf->user >> cf->nice >> cf->system >> cf->idle >> cf->iowait >> cf->irq >> cf->softirq
		>> cf->steal >> cf->guest ;

	string _tmp;
	string abb;
	stringstream css;
	css.str(ctxt_data);
	css >> _tmp >> cf->ctxt;
	
	if(!old_cf->idle)
	{
			old_cf->user = cf->user;
        	old_cf->nice = cf->nice;
        	old_cf->system = cf->system;
        	old_cf->idle = cf->idle;
        	old_cf->iowait = cf->iowait;
        	old_cf->irq = cf->irq;
        	old_cf->softirq = cf->softirq;
        	old_cf->steal = cf->steal;
        	old_cf->guest = cf->guest;
			old_cf->ctxt = cf->ctxt;
	}
	else
	{
		long long total_new = cf->user +cf->nice +cf->system +cf->idle +cf->iowait +cf->irq +cf->softirq +cf->steal +cf->guest;
		long long total_old = old_cf->user +old_cf->nice +old_cf->system +old_cf->idle +old_cf->iowait +old_cf->irq 
			+old_cf->softirq +old_cf->steal +old_cf->guest;
		long long total_time = total_new - total_old;

		pl[22].point_dic->cpu_data = double(cf->user - old_cf->user)/double(total_time)*100;
		pl[23].point_dic->cpu_data = double(cf->system - old_cf->system)/double(total_time)*100;
		pl[24].point_dic->cpu_data = double(cf->idle - old_cf->idle)/double(total_time)*100;
		pl[25].point_dic->cpu_data = double(cf->iowait - old_cf->iowait)/double(total_time)*100;
		pl[26].point_dic->cpu_data = double(cf->softirq - old_cf->softirq)/double(total_time)*100;	
	    pl[27].point_dic->current_data = cf->ctxt - old_cf->ctxt;

		old_cf->user = cf->user;
		old_cf->nice = cf->nice;
		old_cf->system = cf->system;
		old_cf->idle = cf->idle;
		old_cf->iowait = cf->iowait;
		old_cf->irq = cf->irq;
		old_cf->softirq = cf->softirq;
		old_cf->steal = cf->steal;
		old_cf->guest = cf->guest;
		old_cf->ctxt = cf->ctxt;
	}
	infile.close();
}
