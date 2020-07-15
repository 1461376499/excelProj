//////////////////////////////////////////////////////////////////////////
//
//	:随便写的一些数据
//	by leo9909@csdn.net	
//
//////////////////////////////////////////////////////////////////////////
#include <list>

using namespace std;

struct daily_attend
{
	int on_duty_time;
	int off_duty_time;
};

struct person_attend_data
{
	string depart_name;
	string person_name;
	string person_sn;	
	std::list<daily_attend> lst_daily_attend;
	string class_type;
};


void FormSimuData(std::list<person_attend_data>& lst_person_attend_data);

