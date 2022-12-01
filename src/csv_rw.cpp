// VC aka aschiuta aka VA3FOD
#include "CSVreader.h"
#include <string>

const char *filename = "Test2.csv";

int main(void)
{
	fpos_t pos = 0;
		
	// start the csv processing HERE
	// open the csv file and initializations
	CCSVreader csvfile(filename);
	
	if (!csvfile.err)
	{
		// get the header data
		csvfile.get_header(1);

		// read the numerical data from line xxx to line yyy (use get_no_lines to read to the end of the file)
		// it will read the WHOLE csv file, and store it in the memory like a table (matrix)
		csvfile.read_data(2, csvfile.get_no_lines());

		cout << "number of lines read "<< csvfile.get_no_lines() << endl;

		// print the header of the csv file
		csvfile.print_header();
		
		// and display the data
		for (int i = 0; i < csvfile.get_no_data_rows(); i++)
		{
			for (int j = 0; j < csvfile.get_no_columns(); j++)
			{
				cout << csvfile.pdata[i][j] << "\t";
			}
			cout << endl;
		}

		// print another line to say the string "end of file"
		cout << "end of file" << endl;
		

	} // end if err for open file


	return true;
}

