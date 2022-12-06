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
		
		
		// create a vector y1 and assign first column from pdata to it
		vector<double> y1;
		
		// and display the data
		for (int i = 0; i < csvfile.get_no_data_rows(); i++)
		{
			for (int j = 0; j < csvfile.get_no_columns(); j++)
			{
				cout << csvfile.pdata[i][j] << "\t";
				
			}
			cout << endl;

			y1.push_back(csvfile.pdata[i][1]);
		}

		// print another line to say the string "end of file"
		cout << "end of file" << endl;

		//y1.insert(y1.end(), csvfile.pdata[0], csvfile.pdata[0] + csvfile.get_no_columns());
		
		
		// iterate through the vector and print the values
		for (int i = 0; i < y1.size(); i++)
		{
			cout << y1[i] << endl;
		}
		
		
		

	} // end if err for open file


	return true;
}

