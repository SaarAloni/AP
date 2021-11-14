#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "timeseries.h"

// Create a vector of <string, int vector> pairs to store the result

	TimeSeries::TimeSeries(const char* CSVfileName) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create an input filestream
    std::ifstream myFile(CSVfileName);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    float val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
						//editing the number of columns
						this->rowLength++;

            // Initialize and add <colname, int vector> pairs to result
            this->result.push_back({colname, std::vector<float> {}});
        }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
				//editing the number of columns
				this->colLength++;

        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while(ss >> val){

            // Add the current integer to the 'colIdx' column's values vector
            this->result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();
	}
	// // returns numbers of columns
  int TimeSeries::getColumnLength() const{
    return this->colLength;
  }


	// returns numbers of rows
	 int TimeSeries::getRowLength() const{
		return this->rowLength;
	}

	// returns spacific column by index
  std::pair<std::string, std::vector<float>> TimeSeries::getColumnByIndex(int index) const{
		   return this->result.at(index);
  }

	// returns spacific column by name
	std::vector<float> TimeSeries::getColumnByName(std::string name) const{
		for(int i = 0; i < getRowLength();i++) {
			if(this->result.at(i).first.compare(name) == 0) {
				return result.at(i).second;
			}
		}
		const std::vector<float> v = {};
		return v;
	}

	// returns spacific column by row and column
  float TimeSeries::getColumnByIndex(int column, int row) const{
		   if(row > this->colLength || column > this->rowLength || column < 0 || row < 0) {
				 std::cout << this->colLength << "\n";
				 std::cout << this->rowLength << "\n";
				 throw invalid_argument("column or row not ok please choose other values");
			 }
			 return this->result.at(column).second.at(row);
			 return 0;
  }
