//////////////////////////////////////////////////////////////////////////
//
//	:gen_excel_file类，excel操作类
//	by leo9909@csdn.net	
//
//////////////////////////////////////////////////////////////////////////

#include "gen_excel_file.h"

using namespace generate_excel;

//--------------------------------------
gen_excel_file::gen_excel_file(void)
{
	m_xls = NULL;
}

gen_excel_file::~gen_excel_file(void)
{
	release();
}
gen_excel_file::gen_excel_file(const gen_excel_file &r)
{
}
gen_excel_file &gen_excel_file::operator=(const gen_excel_file &r)
{
	return *this;
}
//----------------

void gen_excel_file::release()
{
	if (m_xls)
	{
		fclose(m_xls);
		m_xls = NULL;
	}
}

//--------------------------------------
int gen_excel_file::create_file(const char * file_name)
{
	release();
	m_xls = fopen(file_name, "w+");

	if (!m_xls)
		return ERR_OPEN_FAILED;

	//1.
	fprintf(m_xls, FILE_HTML_TITLE);

	//2.
	if (load_xls_head())
		return ERR_WRITE_HEAD_FAILED;
	

	//3.
	fprintf(m_xls, FILE_BODY_TITLE);
	fprintf(m_xls, FILE_TABLE_TITLE);

	return SUCCESS;
}

int gen_excel_file::load_xls_head()
{
	CHECK_BUFFER_WITH_RETURN;
	FILE *p_head = fopen(HEAD_TEXT_FILE, "r");

	if (!p_head)
		return ERR_WRITE_HEAD_FAILED;

	copy_text(p_head, m_xls);
	fclose(p_head);

	return SUCCESS;
}

int gen_excel_file::end_file()
{
	CHECK_BUFFER_WITH_RETURN;
	fprintf(m_xls, "</table>\n");
	fprintf(m_xls, "</body>\n");
	fprintf(m_xls, "</html>\n");

	release();
	return SUCCESS;
}

//-------------------------------

void gen_excel_file::set_column_width(int span_cols, int width_pels)
{
	CHECK_BUFFER;

	if (span_cols>1)
		fprintf(m_xls, " <col width=%d span=%d style=\'mso-width-source:userset;mso-width-alt:%d\'>\n", width_pels, span_cols, width_pels*32);
	else
		fprintf(m_xls, " <col width=%d style=\'mso-width-source:userset;mso-width-alt:%d\'>\n", width_pels, width_pels*32);		
}

//----------------------------------------
void gen_excel_file::start_new_line(float height)
{
	CHECK_BUFFER;
	fprintf(m_xls, " <tr style=\'mso-height-source:userset;height:%.2fpt\'>\n", height);
}

void gen_excel_file::end_curr_line()
{
	CHECK_BUFFER;	
	fprintf(m_xls, " </tr>\n");	
}

//------------------------------------------
void gen_excel_file::fill_cell(const char* cell_tag, int val)
{
	CHECK_BUFFER;
	fprintf(m_xls, "%s%d</td>\n", cell_tag, val);
}
void gen_excel_file::fill_cell(const char* cell_tag, float val)
{
	CHECK_BUFFER;
	fprintf(m_xls, "%s%f</td>\n", cell_tag, val);
}
void gen_excel_file::fill_cell(const char* cell_tag, const char* val)
{
	CHECK_BUFFER;
	fprintf(m_xls, "%s%s</td>\n", cell_tag, val);
}

//-----------------------------------------
int gen_excel_file::copy_text(FILE *pSource, FILE *pDest)
{
	if (!pSource && !pDest)
		return FAILED;

	char c;	
	while (!feof(pSource))
	{
		c = fgetc(pSource);
		fputc(c, pDest);
	}

	if(c == -1)	//去掉来自源文件尾的文件结束符
	{
		fseek(pDest, -1L, SEEK_CUR );	
		fputc('\n', pDest);
	}

	return SUCCESS;
}






