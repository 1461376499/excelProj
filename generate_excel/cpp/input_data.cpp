//////////////////////////////////////////////////////////////////////////
//
//	:随便写的一些数据
//	by leo9909@csdn.net	
//
//////////////////////////////////////////////////////////////////////////

#include <list>

#include "input_data.h"

void FormSimuData(std::list<person_attend_data>& lst_person_attend_data)
{
	person_attend_data person_attend;
	daily_attend daily_data;

	person_attend.depart_name = "部门X";
	person_attend.person_name = "卡咯";
	person_attend.person_sn = "SF67PK35";
	person_attend.class_type = "24小时";



	for (int i=0; i<7; i++)
	{
		daily_data.on_duty_time = 480;
		daily_data.off_duty_time = 1200;
		person_attend.lst_daily_attend.push_back(daily_data);
	}

	lst_person_attend_data.push_back(person_attend);

//-----
	person_attend.depart_name = "部门Q";
	person_attend.person_name = "乎东";
	person_attend.person_sn = "GT54BE96";
	person_attend.class_type = "24小时";

	person_attend.lst_daily_attend.clear();
	for (int i=0; i<7; i++)
	{
		daily_data.on_duty_time = 420;
		daily_data.off_duty_time = 1150;
		person_attend.lst_daily_attend.push_back(daily_data);
	}

	lst_person_attend_data.push_back(person_attend);

}