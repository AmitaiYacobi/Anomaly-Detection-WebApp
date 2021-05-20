// 313301764 Omer Schloss
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <map>
#include <vector>
#include <string>
using namespace std;

class TimeSeries
{
	// A map with feature string as key and vector for values.
	map<string, vector<float>> _data;
	map<string, string> _translate;

public:
	/*
	 TimeSeries - Constructor -
	 The countructor open the file and copy all the feature and their values from
	 the cvs file to a map with features as keys and vecotor for the values.
	*/
	TimeSeries(const char *CSVfileName);

	// The function gets a string with a new line and adding their values to the feature in order.
	void addLineToTimeSeries(string line);

	// The function return a vector with all the feature names.
	vector<string> getVectorFeatures() const;

	// The function check if the feature is The Time Series
	bool isFeatureInTimeSeries(string feature) const;

	// THe funtion return a vector of all the values of the chosen features
	vector<float> getVectorByFeature(string f) const;

	// The function return the size of the chosen vector.
	size_t getSizeOfVector(string f) const;

	string trans(string f) const;
};

#endif /* TIMESERIES_H_ */