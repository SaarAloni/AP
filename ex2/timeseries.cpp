#include <iostream>

class TimeSeries{
// Create a vector of <string, int vector> pairs to store the result
char std::vector<std::pair<std::string, std::vector<int>>> result;
int colLength;
int rowLength;

public:

	TimeSeries(const char* CSVfileName) : colLength = 0, rowLength = 0, result ={} {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

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
						rowLength++;

            // Initialize and add <colname, int vector> pairs to result
            this->result.push_back({colname, std::vector<int> {}});
        }
    }

    // Read data, line by line
    while(std::getline(myFile, line))
    {
				//editing the number of columns
				colLength++;

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
	}
	// returns numbers of columns
  int getColumnLength() {
    return this->colLength;
  }


	// returns numbers of rowa
	int getRowLength() {
		return this->rowLength;
	}

	// returns spacific column by index
  const std::pair<std::string, std::vector<int>> getColumnByIndex(int index) {
		   return this->result.at(index);
  }

	// returns spacific column by name
	const std::vector<int> getColumnByName(std::string name) {
		for (std::vector<int>::iterator it = this->result.begin() ; it != this->result.end(); ++it) {
			if (it.first.compare(name) == 0)
			{
				return it.second;
			}
		}
		return std::vector<int> v = {};
	}

	// returns spacific column by row and column
  const int getColumnByIndex(int column, ind row) {
		   if(row > this->colLength || column > this->rowLength || column < 0 || row < 0) {
				 std::runtime_error("column or row not ok please choose other values");
			 }
			 return this->result.at(column).second.at(row);
  }
}
