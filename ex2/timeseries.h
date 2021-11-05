#include <vector>
#include <string>

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{

	std::vector<std::pair<std::string, std::vector<double>>> result = {};
	int colLength = 0;
	int rowLength = 0;

public:

	TimeSeries(const char* CSVfileName);
	int getRowLength();
	int getColumnLength();
	const std::pair<std::string, std::vector<double>> getColumnByIndex(int index);
	const std::vector<double> getColumnByName(std::string name);
	const double getColumnByIndex(int column, int row);

};



#endif /* TIMESERIES_H_ */
