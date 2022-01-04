// VC aka aschiuta aka VA3FOD
#include "CSVreader.h"

wchar_t filename[] = L"tabtest2.csv";

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
		
	//	csvfile.read_data(2, csvfile.get_no_lines());

		csvfile.read_data(1, csvfile.get_no_lines());

	//	csvfile.read_data(2, csvfile.get_no_lines());
		//cout << "all data read from the csv file = " << (wchar_t)filename[2] << endl;
	
	} // end if err for open file


	return true;
}
