// VC aka aschiuta aka VA3FOD
#include "CSVreader.h"
#include <string>
#include <sciplot\sciplot.hpp>

#define _USE_MATH_DEFINES // for C++
#include <math.h>

using namespace sciplot;

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
		cout << endl;
		cout << "------------------------------------" << endl;

		// and display the data
		for (int i = 0; i < csvfile.get_no_data_rows(); i++)
		{
			for (int j = 0; j < csvfile.get_no_columns(); j++)
			{
				cout << csvfile.pdata[i][j] << "\t";
				
			}
			cout << endl;
		}
		cout << endl;
		
		// create a vector y1 and assign a column from pdata to it
		vector<float> x;
		csvfile.GetVecData(0, x);
		
		vector<float> y1,y2,y3;
		y1 = csvfile.GetVecData("y1");
		y2 = csvfile.GetVecData("speed");
		y3 = csvfile.GetVecData("H");
		
		//y4 = GetVecData(4);
		
		// using for auto iterator to print vector elements
		cout << "column nth" << endl;
		for (auto i : x)
		{
			//cout << i << endl;
		}

		// using sciplot, plot the data for "x" and "y1"
		sciplot::Plot2D plot,plot2,plot3;
		
		plot.xlabel("x");
		plot.ylabel("y1");
		plot.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot3.xlabel("x");
		plot3.ylabel("y2");
		plot3.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot3.xlabel("x");
		plot3.ylabel("y3");
		plot3.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot.drawCurve(x, y1).label("y1");
		plot2.drawCurve(x, y2).label("y2");
		plot3.drawCurve(x, y3).label("y3");

		// Create figure to hold plot
		Figure fig = { {plot} ,{plot2} ,{plot3} };
		// Create canvas to hold figure
		Canvas canvas = { {fig} };
		canvas.size(1048, 800);

		// Show the plot in a pop-up window
		canvas.show();

		// Save the plot to a SVG file
		canvas.save("val plot output.svg");
		

	} // end if err for open file


	return true;
}

