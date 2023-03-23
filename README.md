# BasicCSVreader

Project Name: VA3FOD - CSV Reader and Plotter
This project is a simple demonstration of how to use the CSVreader class to read and plot data from a CSV file. The project is written in C++ and uses the sciplot library to plot the data.

Usage
To use this project, you need to have the following libraries installed:

sciplot
C++ standard library
Clone this repository to your local machine and compile the project. To compile the project, run the following command:

c
Copy code
g++ -std=c++11 main.cpp CSVreader.cpp -o va3fod
The compiled program takes no arguments, and the CSV file to be processed is hard-coded in the main.cpp file as Test2.csv. The program reads the CSV file, prints the header of the file, and plots the data for specific columns.

CSV File Format
The CSV file to be read by this program should have a header on the first line of the file. The header should contain the names of the columns in the file, separated by commas. The data in the file should be separated by commas, and the data types are determined by the header.

CSVreader Class
The CSVreader class is a simple class that reads a CSV file and stores it in memory as a table (matrix). The class provides methods to get the header of the file, read specific rows of data, and get specific columns of data as vectors.

sciplot Library
The sciplot library is a C++ library for creating beautiful and publication-quality scientific plots. The library provides a simple and intuitive API for creating plots, legends, axes, and other plot elements.

License
This project is licensed under the MIT License. See the LICENSE file for more information.
