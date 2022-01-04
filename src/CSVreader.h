#pragma once

// VA3FOD
// simple and basic csv reader class

#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include <iostream>
//#include <list>
#include <vector>

using std::cout;
using std::wcout;
using std::endl;
using std::cin;
using std::vector;
//using std::string;
//using std::list;
//using std::wstring;

class CCSVreader
{
	//#define EndOfLine	(10) 
	//#define CarriageReturn (13)

	static const int EndOfLine = 10;
	static const int CarriageReturn = 13;
	//\\ - Backslash
	//\' - Single Quotation Mark
	//\" - Double Quatation Mark
	//\n - New line
	//\r - Carriage Return
	//\t - Horizontal Tab
	//\b - Backspace
	//\f - Formfeed
	//\a - Bell(beep) sound

public:
	CCSVreader(wchar_t *filename);
	~CCSVreader();

public:
	// public functions
	int get_header(int line_no);
	int read_data(int line_start, int line_end);
	int get_no_lines();

private:
	// private functions
	int get_header_tokens(wchar_t *p_line_cur_w, wchar_t **p_h);
	int read_line(wchar_t **p_line_out, wchar_t **p_line_2out, int line_no);
	int read_word(int line_no, double **pd,int index);
	bool isNumber(const wchar_t* str);
	fpos_t get_pos_begining_line(int line_no);
	int clean_mess();// close all the opened files and deallocate the memory, delete pointes

public:
	wchar_t **p_header;
	double **p_data;
	errno_t err;

private:
	wchar_t		*m_filename;
	const wchar_t *seps_w;	//see constructor for initialization = L" \t,;";
	FILE		*p_file;
	wchar_t		*p_line_w;
	wchar_t		*pline_w_copy;
	int			no_lines;
	int			no_tokens;
	int			numclosed;
	vector<fpos_t>lineEndMap;
	bool linesMapped = false;

};

