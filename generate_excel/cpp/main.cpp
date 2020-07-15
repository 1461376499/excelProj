//////////////////////////////////////////////////////////////////////////
//main.cpp
//	:使用class gen_excel_file示例
//	by leo9909@csdn.net	
//
//////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "input_data.h"
#include "gen_excel_file.h"


using namespace std;
using namespace generate_excel;

// #include "boost/filesystem/operations.hpp"
// #include "boost/filesystem/path.hpp"
// #include "boost/progress.hpp"
// 
// 
// namespace bfs = boost::filesystem;

// string GetCurrentPath()
// {
//  	bfs::path full_path( bfs::initial_path<bfs::path>() );
//  	return full_path.native_directory_string();
// }

string GetTimeStr(int nMin);
void GenerateFile(string szFileName);
void WriteData(gen_excel_file & xls);


int main(int argc, char * argv[])
{
	string szFilePath("表格.xls");
//	szFilePath = GetCurrentPath() + "\\" + szFilePath;

	GenerateFile(szFilePath);

	return 0;
}

string GetTimeStr(int nMin)
{
	char str[16] = {0};
	int nDays = 0;
	nDays = nMin/1440;

	if (nDays == 0)
		sprintf(str, "%d:%02d", nMin/60, nMin%60);
	else
		sprintf(str, "%d:%02d(第%d天)", nMin/60, nMin%60, nDays+1);

	string sz(str);
	return sz;
}

void GenerateFile(string szFileName)
{
	gen_excel_file xls;

	if (ERR_WRITE_HEAD_FAILED == xls.create_file(szFileName.c_str()))
	{
		cout<<"找不到 head.txt文件"<<endl;
		return;
	}	

	xls.set_column_width(3, 70);
	xls.set_column_width(1, 100);
	xls.set_column_width(8, 70);
	xls.set_column_width(2, 50);
	xls.set_column_width(1, 70);

	//Line 1:
	xls.start_new_line(30);
	xls.fill_cell(CELL_COLSPAN(15,30,BDR_SOLID(.5),""), "每周考勤明细表");
	xls.end_curr_line();

	//Line 2:
	xls.start_new_line(15);
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "序号");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "单位");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "姓名");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "人员编号");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "上班<br>下班");
	xls.fill_cell(CELL_COLSPAN(7,32,BDR_SOLID(.5),""), "星期");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "正常<br>出勤");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "异常<br>出勤");
	xls.fill_cell(CELL_ROWSPAN(2,32,BDR_SOLID(.5),""), "班制");
	xls.end_curr_line();

	//Line 3:
	//xls.start_new_line(14.25);
	//for (int i=1; i<7; i++)
	//	xls.fill_cell(CELL_NORMAL(24, BDR_SOLID(.5), "x:num"), i);

	//xls.fill_cell(CELL_NORMAL(24, BDR_SOLID(.5), "x:num"), "日");
	//xls.end_curr_line();

	////Data :
	//WriteData(xls);

	////End :
	//xls.end_file();

	return ;	
}


void WriteData(gen_excel_file & xls)
{
	list<person_attend_data> lst_data;
	FormSimuData(lst_data);

	list<person_attend_data>::iterator it_data;
	list<daily_attend>::iterator it_daily;

	int j, i=0;

	for (it_data=lst_data.begin(); it_data!=lst_data.end(); it_data++)
	{
		const person_attend_data & attend_data = *it_data;

		xls.start_new_line(14.25);
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),"x:num"), i+1);
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), attend_data.depart_name.c_str());
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), attend_data.person_name.c_str());
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), attend_data.person_sn.c_str());	

		xls.fill_cell(CELL_NORMAL(25, BDR_SOLID(.5), "x:str"), "上班");

		j=1;
		it_daily=it_data->lst_daily_attend.begin();		
		for (; it_daily!=attend_data.lst_daily_attend.end(); it_daily++ )
		{	
			if (j==7)
				xls.fill_cell(CELL_NORMAL(27, BDR_SOLID(.5),"x:str"), GetTimeStr(it_daily->on_duty_time).c_str());	
			else
				xls.fill_cell(CELL_NORMAL(26, BDR_SOLID(.5),"x:str"), GetTimeStr(it_daily->on_duty_time).c_str());	

			j++;
		}

		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), "");	
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), "");	
		xls.fill_cell(CELL_ROWSPAN(3,38,BDR_DOUBLE(2.0),""), attend_data.class_type.c_str());

		xls.end_curr_line();

		xls.start_new_line(14.25);
		xls.fill_cell(CELL_NORMAL(25,BDR_SOLID(.5),"x:str"), "下班");

		j=1;
		it_daily=it_data->lst_daily_attend.begin();	
		for (; it_daily!=attend_data.lst_daily_attend.end(); it_daily++ )
		{
			if (j==7)
				xls.fill_cell(CELL_NORMAL(27,BDR_SOLID(.5),"x:str"), GetTimeStr(it_daily->off_duty_time).c_str());	
			else
				xls.fill_cell(CELL_NORMAL(26,BDR_SOLID(.5),"x:str"), GetTimeStr(it_daily->off_duty_time).c_str());	

			j++;
		}
		xls.end_curr_line();

		xls.start_new_line(14.25);
		xls.fill_cell(CELL_NORMAL(25,BDR_DOUBLE(2.0), "x:str"), "工时");

		j=0;
		it_daily=it_data->lst_daily_attend.begin();	
		for (; it_daily!=attend_data.lst_daily_attend.end(); it_daily++ )
		{
			xls.fill_cell(CELL_NORMAL(29, BDR_DOUBLE(4.0), "x:str"), GetTimeStr(it_daily->off_duty_time-it_daily->on_duty_time).c_str() );	
		}
		xls.end_curr_line();

		i++;
	}

}
