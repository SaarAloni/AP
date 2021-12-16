#include <vector>
#include <string>

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{

	std::vector<std::pair<std::string, std::vector<float>>> result = {};
	int colLength = 0;
	int rowLength = 0;

public:

	TimeSeries(const char* CSVfileName);
	TimeSeries(std::vector<float> x, string xName, std::vector<float> y, string yname);
	int getRowLength() const;
	int getColumnLength() const;
	std::pair<std::string, std::vector<float>> getColumnByIndex(int index) const;
	std::vector<float> getColumnByName(std::string name) const;
	float getColumnByIndex(int column, int row) const;

};



#endif /* TIMESERIES_H_ */
