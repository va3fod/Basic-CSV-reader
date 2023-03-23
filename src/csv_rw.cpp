// VA3FOD
#pragma once
#include "CSVreader.h"
#include <string>
#include <sciplot\sciplot.hpp>
#include <cmath>

using namespace sciplot;

const char *filename = "Test2.csv";

// this project is testing the csv reader class and plotting the data using sciplot
// the csv file is a simple csv file with header and data
// the header is the first line of the csv file
// the data is the rest of the lines of the csv file
// the data is separated by comma (,)
// the data can be any type of data, but the data type is determined by the header
// the header is a string of words separated by comma (,)

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
		//cout << csvfile << endl; // print the whole csv file
		
		// create a vectors for specific data columns to be easier to be plot.
		vector<float> time;
		time = csvfile.GetVecData("time");
		
		vector<float> y1 = csvfile.GetVecData("y1");
		vector<float> y2 = csvfile.GetVecData("speed");
		vector<float> y3 = csvfile.GetVecData("H");
		

		// using sciplot, plot the data for "x" and "y1"
		sciplot::Plot2D plot,plot2,plot3;
		
		plot.xlabel("time");
		plot.ylabel("y1");
		plot.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot3.xlabel("time");
		plot3.ylabel("y2");
		plot3.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot3.xlabel("time");
		plot3.ylabel("y3");
		plot3.legend()
			.atTop()
			.fontSize(10)
			.displayHorizontal()
			.displayExpandWidthBy(2);

		plot.drawCurve(time, y1).label("y1");
		plot2.drawCurve(time, y2).label("y2");
		plot3.drawCurve(time, y3).label("y3");

		// Create figure to hold plot
		Figure fig = { {plot} ,{plot2} ,{plot3} };
		// Create canvas to hold figure
		Canvas canvas = { {fig} };
		canvas.size(1048, 800);

		// Show the plot in a pop-up window
		canvas.show();

		// Save the plot to a SVG file
		canvas.save("plot csv read data.svg");
		

	} // end if err for open file


	return true;
}

