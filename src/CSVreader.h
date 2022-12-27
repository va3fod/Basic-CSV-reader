#pragma once

// VA3FOD
// simple and basic csv reader class

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::wcout;
using std::endl;
using std::cin;
using std::vector;

class CCSVreader
{
public:
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

	CCSVreader(const char *filename);
	~CCSVreader();

	char** pheader;
	float** pdata; // [row][col] indexing starts from 0
	errno_t err;

	int get_header(int line_no);
	int read_data(int line_start, int line_end);
	int get_no_lines();
	const int get_no_data_rows(void);
	const int get_no_columns(void);
	void print_header(void);
	void GetVecData(int col, vector<float>& vecoutp);
	vector<float>& GetVecData(int col);
	vector<float>& GetVecData(std::string colname);

	friend std::ostream& operator<<(std::ostream& out, const CCSVreader& csvf)
	{
		for (int i = 0; i < csvf.no_lines-1; i++)
		{
			for (int j = 0; j < csvf.no_tokens; j++)
			{
				out << csvf.pdata[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

private:
	int get_header_tokens(char *p_line_cur_w, char **p_h);
	int read_line(char **p_line_out, char **p_line_2out, int line_no);
	int read_word(int line_no, float **pd,int index);
	bool isNumber(const char* str);
	int clean_mess();// close all the opened files and deallocate and clean up the memory

	const char *seps_w;	//see constructor for initialization = L" \t,;";
	FILE *p_file;
	char *p_line_w;
	char *pline_w_copy;
	int	no_lines;
	int	no_tokens;
	int	numclosed;
	vector<fpos_t>lineEndMap;
	bool linesMapped = false;
};

