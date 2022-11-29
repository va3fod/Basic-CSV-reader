#include "CSVreader.h"

// VA3FOD
// simple and basic csv reader class

CCSVreader::CCSVreader(const char *filename)
{
	//seps_w = " \t,;";
	seps_w = "\t,;";
	
	p_file = NULL;
	pheader = NULL;
	pdata = NULL;
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
		pdata = new float *[no_lines];

		for (int jj = 0; jj < no_lines; jj++)
		{
			pdata[jj] = NULL;
		}
	}
	
}
//============================================================================
CCSVreader::~CCSVreader()
{
	clean_mess();

	//cout << "astalavista baby -> destructor called here." << endl;
}
//============================================================================
int CCSVreader::get_header(int line_no)
{
	if (read_line(&p_line_w, &pline_w_copy, line_no))
		wprintf(L"fgets error\n");
	else
	{
		// process the line that was read. break it down in tokens based on specified delimiters
		cout << "Tokens from header line:" << endl;
		

		no_tokens = get_header_tokens(p_line_w, pheader);
		pheader = new char *[no_tokens];
		get_header_tokens(pline_w_copy, pheader);

	}

	return 0;
}
//============================================================================
int CCSVreader::get_header_tokens(char *p_line_cur_w, char **p_h)
{
	int ii = 0;
	size_t header_length = 0;
	char *token_w = NULL;
	char *contextStr_w = NULL;

	// Establish string and get the first token:
	token_w = strtok_s(p_line_cur_w, seps_w, &contextStr_w); // C4996

	if (token_w != NULL)
	{
		header_length = strlen(token_w);

		if (p_h != NULL)
		{
			p_h[0] = new char[header_length + 1];
			strcpy_s(p_h[0], header_length + 1, token_w);
		}
	}

	while (token_w != NULL)
	{
		// While there are tokens in "string"
		if (p_h != NULL)
		{
			printf("%s\n", token_w);
		}

		// Get next token: 
		token_w = strtok_s(NULL, seps_w, &contextStr_w); // C4996

		ii++;
		if (token_w != NULL)
		{
			header_length = strlen(token_w);

			if (p_h != NULL)
			{
				p_h[ii] = new char[header_length + 1];
				strcpy_s(p_h[ii], header_length + 1, token_w);
			}
		}
	}

	// return the no. of tokens in the header of the csv file. usualy the first raw.
	return ii;
}
//============================================================================
int CCSVreader::read_line(char **p_line_out, char **p_line_2out, int line_no)
{
	int i_line = 0;
	int pos_err = 0;
	fpos_t pos = 0, pos_end_line = 0;
	int lungime_line = 0;
	char *p_line = NULL;
	char ch_w = NULL;// L'';
	errno_t err_cpy = 0;
	
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
		*p_line_out = new char[lungime_line];
	}
	else
	{
		delete[] *p_line_out;
		*p_line_out = NULL;

		*p_line_out = new char[lungime_line];
	}

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

	p_line = fgets(*p_line_out, lungime_line, p_file);

	if (*p_line_2out == NULL)
	{
		*p_line_2out = new char[lungime_line];
	}
	else
	{
		delete[] * p_line_2out;
		*p_line_2out = NULL;
		*p_line_2out = new char[lungime_line];
	}

	err_cpy = strcpy_s(*p_line_2out, lungime_line, *p_line_out);

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
	char ch_w;
	fpos_t pos = 0;
	fpos_t pos_end_word = 0;
	fpos_t pos_start_word = 0;
	int pos_delimiter = 0;
	float *p_words = NULL;
	int word_len = 0;
	int ii = 0;
	int jj = 0;
	int iword = 0;
	char *ptemp = NULL;

	if (line_no == 1)
	{
		pos = 0;
	}
	else
	{
		pos = lineEndMap[line_no - 2] ;
	}

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

	if (line_no == 1)
	{
		pos = 0;
	}
	else
	{
		pos = lineEndMap[line_no - 2];
	}
	
	fsetpos(p_file, &pos);
	pos_start_word = 0;

	ch_w = p_line_w[0];
	while (ii <= (int)strlen(p_line_w))
	{
		if (ch_w == seps_w[0] || ch_w == seps_w[1] || ch_w == seps_w[2] || ch_w == seps_w[3] || ii == (int)strlen(p_line_w))
		{
			pos_end_word = ii;
			word_len = int(pos_end_word - pos_start_word);
			ptemp = new char[word_len + 1];
			strncpy_s(ptemp, word_len + 1, &p_line_w[pos_start_word], word_len);
			pos_start_word = pos_end_word + 1;
			if (iword <= pos_delimiter)
			{
				// check here it the string is something can be converted as number or not.
				// if not, write 99999999
				if (isNumber(ptemp))
				{
					p_words[iword] =(float)atof(ptemp);
				}
				else
				{
					if (pd[index-1] && index>0)
					{
						p_words[iword] = pd[index-1][iword];
					}
					else
					{
						p_words[iword] = -999999999.0f;
					}
					
				}
			}

			delete[] ptemp;
			ptemp = NULL;
			iword++;

		}
		ii++;
		if (ii < (int)strlen(p_line_w))
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

	// read new data from the csv file, so fill with NULLs the previous data in the pdata

	for ( jj = 0; jj < no_lines; jj++)
	{
		pdata[jj] = NULL;
	}

	line = line_start;

	for (jj = 0; (jj <= line_end - line_start) && jj < no_lines; jj++)
	{
		read_line(&p_line_w, &pline_w_copy, line); // abc
		
		read_word(line, pdata,jj);

		++line;
	}
	
	// copy the pdata matrix to the matrix type of vector , for easy access to the user.
	//y.insert(y.end(), pdata, pdata + 10);

	return 0;
}
//============================================================================
int CCSVreader::get_no_lines()
{
	char ch_w;
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
/*
fpos_t CCSVreader::get_pos_begining_line(int line_no)
{
	fpos_t pos = 0;
	char ch_w;
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
}*/
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

			delete[] pheader;
			pheader = { NULL };
		}


		// fix the delete of double pointer allocation
		if (pdata != NULL)
		{
			
			for (int jj = 0; jj < no_lines; jj++)
			{
				delete[] pdata[jj];
			}
			delete[] pdata;
			pdata = NULL;
		}
	}

	return 0;
}
//============================================================================
bool CCSVreader::isNumber(const char* str)
{
	char *endptr = 0;
	double ret = 0;
	ret = strtod(str, &endptr);

	if (*endptr != '\0' || endptr == str)
		return false;
	return true;
}
//============================================================================
void CCSVreader::print_header(void)
{
	// print pheader of the csv file to the console output
	for (int i = 0; i < no_tokens; i++)
	{
		cout<<" "<<pheader[i]<<" ";
	}
}