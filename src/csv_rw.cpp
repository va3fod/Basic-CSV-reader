// VC aka aschiuta aka VA3FOD
#include "CSVreader.h"
#include <string>

#define _USE_MATH_DEFINES // for C++
#include <math.h>

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

		// create a column array of 2 elements and initialiaze it with random data from 0 to 9
		cout << "xarray" << endl;
		double xarray[2] = { 0, 1 };
		// print the array
		for (int i = 0; i < 2; i++)
		{
			cout << xarray[i] << "\t";
		}
		
		cout << endl;
		
		
		// create a 2x2 rotation matrix using vector type for 45 degrees
		vector<vector<double>> rotmat = { { cos(M_PI / 4), -sin(M_PI / 4) }, { sin(M_PI / 4), cos(M_PI / 4) } };
		
		// create a new vector y2 and assign the result of the rotation matrix to "xarray"
		vector<double> y2 = { rotmat[0][0] * xarray[0] + rotmat[0][1] * xarray[1], rotmat[1][0] * xarray[0] + rotmat[1][1] * xarray[1] };
		
		
		// print the result
		cout << "y2 = " << y2[0] << " " << y2[1] << endl;
		
		// create a new vector y3 and assign the result of the rotation matrix applied to "xarray"
		vector<double> y3 = { rotmat[0][0] * y2[0] + rotmat[0][1] * y2[1], rotmat[1][0] * y2[0] + rotmat[1][1] * y2[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] };
		y3 = { rotmat[0][0] * y3[0] + rotmat[0][1] * y3[1], rotmat[1][0] * y3[0] + rotmat[1][1] * y3[1] }; // back to original array rotation
		// print the result
		cout << "y3 = " << y3[0] << " " << y3[1] << endl;
		
		
		
	
		
		
		
		
		
	
		
		
		
		
		
			
		
		
		
		
		
		
		
		
	
		
		
		
		
	
		
		

				
		
		
		
		
		
		

	} // end if err for open file


	return true;
}

