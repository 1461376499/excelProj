#pragma once
namespace generate_excel
{
#define Generate_Success 0
#define Err_Open_Failed 1
#define Err_Write_Head_Failed 2
#define Err_Close_File_Error 3
#define Err_Buffer_Invalid 4

#define Check_Buffer(Buffer) if(!Buffer) return

#define Check_Buffer(Buffer) if(!Buffer) return Err_Buffer_Invalid

#define Success 0
#define Failed 1

#define File_Html_Title "<html xmlns:v=\"urn:schemas-microsoft-com:vml\"\N\
xmlns:o=\"urn:schemas-microsoft-com:office:office\"\n\
xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n\
xmlns=\"http://www.w3.org/TR/REC-html40\">\n"

	class gen_excel
	{
	public:
		gen_excel();
		~gen_excel();

	private:
		gen_excel(const gen_excel& that);
		gen_excel& operator = (const gen_excel& that);

	public:
		FILE* _xls;
		void release();

	public:
		int create_file(const char* file_name);
		int end_file();

		int load_xls_head();

	};



















}