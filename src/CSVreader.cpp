#include "CSVreader.h"

// VA3FOD
// simple and basic csv reader class

CCSVreader::CCSVreader(const char *filename)
{
	//m_filename = filename;

	seps_w = L" \t,;";
	p_file = NULL;
	p_header = NULL;
	p_data = NULL;
	p_line_w = NULL;
	pline_w_copy = NULL;
	no_lines = 0;
	no_tokens = 0;
	numclosed = 0;
	err = fopen_s(&p_file, filename, "r");

	lineEndMap.reserve(100);
	// get the total no of line of the csv file
	if (!err)
	{
		no_lines = get_no_lines();
		p_data = new float *[no_lines];

		for (int jj = 0; jj < no_lines; jj++)
		{
			p_data[jj] = NULL;
		}
	}
	
}
//============================================================================
CCSVreader::~CCSVreader()
{
	clean_mess();

	cout << "astalavista baby -> destructor called here." << endl;
}
//============================================================================
int CCSVreader::get_header(int line_no)
{
	if (read_line(&p_line_w, &pline_w_copy, line_no))
		wprintf(L"fgets error\n");
	else
	{
		//wprintf(L"%s\n", p_line_w);

		// process the line that was read. break it down in tokens based on specified delimiters
		wprintf(L"Tokens from header line:\n");

		no_tokens = get_header_tokens(p_line_w, p_header);
		p_header = new wchar_t *[no_tokens];
		get_header_tokens(pline_w_copy, p_header);

	}

	return 0;
}
//============================================================================
int CCSVreader::get_header_tokens(wchar_t *p_line_cur_w, wchar_t **p_h)
{
	int ii = 0;
	size_t header_length = 0;
	//size_t header_remained = 0;
	wchar_t *token_w = NULL;
	wchar_t *contextStr_w = NULL;

	// Establish string and get the first token:
	token_w = wcstok_s(p_line_cur_w, seps_w, &contextStr_w); // C4996

	if (token_w != NULL)
	{
		header_length = wcslen(token_w);
		//header_remained = wcslen(contextStr_w);

		if (p_h != NULL)
		{
			p_h[0] = new wchar_t[header_length + 1];
			wcscpy_s(p_h[0], header_length + 1, token_w);
		}
	}

	while (token_w != NULL)
	{
		// While there are tokens in "string"
		if (p_h != NULL)
		{
			wprintf(L"%s\n", token_w);
		}


		// Get next token: 
		token_w = wcstok_s(NULL, seps_w, &contextStr_w); // C4996

		ii++;
		if (token_w != NULL)
		{
			header_length = wcslen(token_w);
			//header_remained = wcslen(contextStr_w);

			if (p_h != NULL)
			{
				p_h[ii] = new wchar_t[header_length + 1];
				wcscpy_s(p_h[ii], header_length + 1, token_w);
			}
		}
	}

	// return the no. of tokens in the header of the csv file. usualy the first raw.
	return ii;
}
//============================================================================
int CCSVreader::read_line(wchar_t **p_line_out, wchar_t **p_line_2out, int line_no)
{
	int i_line = 0;
	int pos_err = 0;
	fpos_t pos = 0, pos_end_line = 0;
	int lungime_line = 0;
	wchar_t *p_line = NULL;
	wchar_t ch_w = NULL;// L'';
	errno_t err_cpy = 0;

	// file is open lets get to work
	/*pos = 0;
	pos_err = fsetpos(p_file, &pos);

	ch_w = fgetc(p_file);

	while ((ch_w != CarriageReturn && ch_w != EndOfLine && ch_w != WEOF) || i_line<line_no)
	{
		ch_w = fgetc(p_file);
		
		if (ch_w == CarriageReturn || ch_w == EndOfLine || ch_w == WEOF)
		{
			i_line++;
		}

		if (((ch_w == CarriageReturn || ch_w == EndOfLine || ch_w == WEOF) && i_line == line_no - 1))
		{
			pos_err = fgetpos(p_file, &pos);
		}
	}

	pos_err = fgetpos(p_file, &pos_end_line);
	if (ch_w == WEOF)
	{
		lungime_line = int(pos_end_line - pos+1);
	}
	else
	{
		lungime_line = int(pos_end_line - pos - 1);
	}*/
	
	if (line_no > 1)
	// new code
	{
		lungime_line = int(lineEndMap[line_no - 1] - lineEndMap[line_no - 2]-1);
	}
	else
	{
		lungime_line =  (int)(lineEndMap[line_no - 1] - 1);
	}
	
	if (*p_line_out == NULL)
	{
		*p_line_out = new wchar_t[lungime_line];
	}
	else
	{
		delete[] *p_line_out;
		*p_line_out = NULL;

		*p_line_out = new wchar_t[lungime_line];
	}

	//pos_err = fsetpos(p_file, &pos);
	if (line_no > 1)
		// new code
	{
		pos = lineEndMap[line_no - 2];
		pos_err = fsetpos(p_file, &pos); // new code
	}
	else
	{
		pos = 0;
		pos_err = fsetpos(p_file, &pos); // new code
	}

	p_line = fgetws(*p_line_out, lungime_line, p_file);

	//pos = 0;// back to the begining of the file  // not sure about this ??? if we need this line at all
	//pos_err = fsetpos(p_file, &pos);  // ?? not sure about this, if we need this line at all
	//p_line_out[lungime_line - 1] = 0; // BUG mare ascuns aici....  2 zile am pierdut

	if (*p_line_2out == NULL)
	{
		*p_line_2out = new wchar_t[lungime_line];
	}
	else
	{
		delete[] * p_line_2out;
		*p_line_2out = NULL;
		*p_line_2out = new wchar_t[lungime_line];
	}

	err_cpy = wcscpy_s(*p_line_2out, lungime_line, *p_line_out);

	if (p_line == NULL)
	{
		wprintf(L"fgets error\n");
		return 1;
	}

	return 0;
}
//============================================================================
int CCSVreader::read_word(int line_no,float **pd,int index)
{
	wchar_t ch_w;
	fpos_t pos = 0;
	fpos_t pos_end_word = 0;
	fpos_t pos_start_word = 0;
	int pos_delimiter = 0;
	float *p_words = NULL;
	int word_len = 0;
	int ii = 0;
	int jj = 0;
	int iword = 0;
	wchar_t *ptemp = NULL;

	pos = get_pos_begining_line(line_no);
	fsetpos(p_file, &pos);

	ch_w = fgetc(p_file);
	while (ch_w != CarriageReturn && ch_w != EndOfLine && ch_w != WEOF)
	{
		ch_w = fgetc(p_file);
		if (ch_w == seps_w[0] || ch_w == seps_w[1] || ch_w == seps_w[2] || ch_w == seps_w[3] )
		{
			pos_delimiter++;
		}
	}

	p_words = new float[pos_delimiter + 1];
	for ( jj = 0; jj < pos_delimiter+1; jj++)
	{
		p_words[jj] = NULL;
	}

	pos = get_pos_begining_line(line_no);
	fsetpos(p_file, &pos);
	pos_start_word = 0;

	ch_w = p_line_w[0];
	while (ii <= (int)wcslen(p_line_w))
	{
		if (ch_w == seps_w[0] || ch_w == seps_w[1] || ch_w == seps_w[2] || ch_w == seps_w[3] || ii == (int)wcslen(p_line_w))
		{
			pos_end_word = ii;
			word_len = int(pos_end_word - pos_start_word);
			ptemp = new wchar_t[word_len + 1];
			wcsncpy_s(ptemp, word_len + 1, &p_line_w[pos_start_word], word_len);
			pos_start_word = pos_end_word + 1;
			if (iword <= pos_delimiter)
			{
				// check here it the string is something can be converted as number or not.
				// if not, write 99999999
				if (isNumber(ptemp))
				{
					p_words[iword] =(float) _wtof(ptemp);
				}
				else
				{
					p_words[iword] = -999999999.0f;
				}
			}

			delete[] ptemp;
			ptemp = NULL;
			iword++;

		}
		ii++;
		if (ii < (int)wcslen(p_line_w))
		{
			ch_w = p_line_w[ii];
		}
		
	}// end while

	if (p_words)
	{
		
		if (index <= 0)
		{
			pd[index] = new float[pos_delimiter + 1];
		}
		else
		{
			pd[index] = new float[pos_delimiter + 1];
			
		}
		for (jj = 0; jj <= pos_delimiter; jj++)
		{
			pd[index][jj] = p_words[jj];
		}
	}

	if (p_words)
	{
		delete[] p_words;
		p_words = NULL;
		return 0;
	}

	return 1;
}
//============================================================================
int CCSVreader::read_data( int line_start, int line_end)
{
	int line = 0;
	int jj = 0;
	//int no_lines = 0;

	// read new data from the csv file, so fill with NULLs the previous data in the p_data
	//no_lines = get_no_lines(); // ??? do we really needs this call  again here ?????

	for ( jj = 0; jj < no_lines; jj++)
	{
		p_data[jj] = NULL;
	}

	line = line_start;

	// THIS LOOP consumes TOOOOOOOO MUCH TIME
	// TO BE FIXED
	for (jj = 0; (jj <= line_end - line_start) && jj < no_lines; jj++)
	{
		read_line(&p_line_w, &pline_w_copy, line); // abc
		
		read_word(line, p_data,jj);

		++line;
	}
	
	return 0;
}
//============================================================================
int CCSVreader::get_no_lines()
{
	wchar_t ch_w;
	int i_line = 0;
	fpos_t pos = 0;

	fsetpos(p_file, &pos);
	ch_w = fgetc(p_file);

	while (ch_w != EOF && ch_w != WEOF)
	{
		ch_w = fgetc(p_file);

		//if (ch_w == EndOfLine || ch_w == WEOF)
		if (ch_w == EndOfLine)
		{
			i_line++;

			if (!linesMapped)
			{
				fgetpos(p_file, &pos);
				lineEndMap.push_back(pos);
				
			}
			
		}
	}
	if (!linesMapped)
	{
		linesMapped = true;
	}

	fsetpos(p_file, &pos);

	return i_line;
}
//============================================================================
fpos_t CCSVreader::get_pos_begining_line(int line_no)
{
	fpos_t pos = 0;
	wchar_t ch_w;
	int i_line = 1;

	pos = 0;// back to the begining of the file
	fsetpos(p_file, &pos);
	ch_w = fgetc(p_file);

	while (ch_w != EOF && ch_w != 65535 && i_line < line_no)
	{
		ch_w = fgetc(p_file);

		if (ch_w == EndOfLine)
		{
			i_line++;
			fgetpos(p_file, &pos);
		}
	}

	return pos;
}
//============================================================================
// close all the opened files and deallocate the memory, delete pointers
int CCSVreader::clean_mess()
{
//	int no_lines = get_no_lines();

	if (!err)
	{
		numclosed = _fcloseall();

		if (p_line_w != NULL)
		{
			delete[] p_line_w;
			p_line_w = NULL;

			delete[] pline_w_copy;
			pline_w_copy = NULL;


			// that is wrong, this is a double pointer
			// to be fixed.
			delete[] p_header;
			p_header = { NULL };
		}


		// fix the delete of double pointer allocation
		if (p_data != NULL)
		{
			
			for (int jj = 0; jj < no_lines; jj++)
			{
				delete[] p_data[jj];
			}
			delete[] p_data;
			p_data = NULL;
		}
	}

	return 0;
}
//============================================================================
bool CCSVreader::isNumber(const wchar_t* str)
{
	wchar_t *endptr = 0;
	double ret = 0;
	ret = wcstod(str, &endptr);

	if (*endptr != '\0' || endptr == str)
		return false;
	return true;
}
