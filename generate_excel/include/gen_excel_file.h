//////////////////////////////////////////////////////////////////////////
//
//	:gen_excel_fileÀà£¬excel²Ù×÷Àà
//	by leo9909@csdn.net	
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdio.h>

namespace generate_excel
{

#define GENERATE_SUCCESS 0
#define ERR_OPEN_FAILED 1
#define ERR_WRITE_HEAD_FAILED 2
#define ERR_CLOSE_FILE_ERROR 3
#define ERR_BUFFER_INVALID 4

#define CHECK_BUFFER if(!m_xls)\
	return

#define CHECK_BUFFER_WITH_RETURN if(!m_xls)\
	return ERR_BUFFER_INVALID

#define SUCCESS 0
#define FAILED 1

#define FILE_HTML_TITLE "<html xmlns:v=\"urn:schemas-microsoft-com:vml\"\n\
xmlns:o=\"urn:schemas-microsoft-com:office:office\"\n\
xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n\
xmlns=\"http://www.w3.org/TR/REC-html40\">\n"

#define HEAD_TEXT_FILE "iofiles/head.txt"
#define FILE_BODY_TITLE "\n\n<body link=blue vlink=purple>\n\n"
#define FILE_TABLE_TITLE "<table x:str border=0 cellpadding=0 cellspacing=0 width=1296 style=\'border-collapse:collapse;table-layout:fixed;width:972pt\'>\n"

#define CELL_NORMAL(font,border,prop) "  <td class=xl"#font"  style=\'"##border"\' "##prop">\n"
#define CELL_COLSPAN(col,font,border,prop) "  <td colspan="#col" class=xl"#font"  style=\'"##border"\' "##prop">\n"
#define CELL_ROWSPAN(row,font,border,prop) "  <td rowspan="#row" class=xl"#font"  style=\'"##border"\' "##prop">\n"
#define CELL_SPAN(col,row,font,border,prop) "  <td colspan="#col" rowspan="#row" class=xl"#font" style=\'"##border"\' "##prop">\n"

#define BDR_SOLID(weight) "border-bottom:"#weight"pt solid black;border-top:none;"
#define BDR_DOUBLE(weight) "border-bottom:"#weight"pt double black;border-top:none;"


//--------------------------------------

class gen_excel_file
{
public:
	gen_excel_file(void);
	~gen_excel_file(void);

private:
	gen_excel_file(const gen_excel_file &c);
	gen_excel_file &operator=(const gen_excel_file &c);

protected:
	FILE* m_xls;
	void release();	

public:
	int create_file(const char * file_name);
	int end_file();

	int load_xls_head();
	int copy_text(FILE *pSource, FILE *pDest);

	void set_column_width(int span_cols, int width_pels);

	void start_new_line(float height);
	void end_curr_line();

	void fill_cell(const char* cell_tag, int val);
	void fill_cell(const char* cell_tag, float val);
	void fill_cell(const char* cell_tag, const char* val);	
};

}

