// 313301764 Omer Schloss
#include "timeseries.h"
#include <fstream>

TimeSeries::TimeSeries(const char *CSVfileName)
{
	ifstream myFile;
	string line;
	int index = 0;
	size_t pos = 0;
	// open the file by its name.
	myFile.open(CSVfileName);
	if (myFile.is_open())
	{
		// get the first line with all features.
		getline(myFile, line);
		map<string, vector<float>>::iterator iter = _data.begin();
		vector<string> v;
		// parse the line as feature an set them as keys in the map.
		while ((pos = line.find(',')) != string::npos)
		{
			_data.insert(iter, pair<string, vector<float>>(line.substr(0, pos), vector<float>()));
			v.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		_data.insert(iter, pair<string, vector<float>>(line, vector<float>()));
		while (getline(myFile, line))
		{
			addLineToTimeSeries(line);
		}
		// close the file at the end.
		myFile.close();

		vector<string>::iterator itt = v.begin();
		iter = _data.begin();
		for (; iter !=_data.end(); iter++)
		{
			_translate[iter->first] =*itt;
			itt++;
		}
	}
}

bool TimeSeries::isFeatureInTimeSeries(string feature) const
{
	// return true if the string is a feature, false otherwise.
	return _data.count(feature);
}

void TimeSeries::addLineToTimeSeries(string line)
{
	map<string, vector<float>>::iterator iter;
	size_t pos = 0;
	// parse the line as float numbers and adding them to their vectors by order.
	for (iter = _data.begin(); iter != _data.end(); iter++)
	{
		if ((pos = line.find(',')) != string::npos)
		{
			iter->second.push_back(stof(line.substr(0, pos)));
			line.erase(0, pos + 1);
		}
		else
		{
			// add the last number to his vector
			iter->second.push_back(stof(line));
		}
	}
}

vector<float> TimeSeries::getVectorByFeature(string f) const
{
	map<string, vector<float>>::const_iterator iter = _data.find(f);
	// return the vector of feature.
	return iter->second;
}

size_t TimeSeries::getSizeOfVector(string f) const
{
	map<string, vector<float>>::const_iterator iter = _data.find(f);
	// return the size of vector.
	return iter->second.size();
}

string TimeSeries::trans(string f) const
{
	return _translate.find(f)->second;
}

vector<string> TimeSeries::getVectorFeatures() const
{
	vector<string> feature;
	// add all features keys to a new vector.
	for (map<string, vector<float>>::const_iterator iter = _data.begin(); iter != _data.end(); iter++)
	{
		feature.push_back(iter->first);
	}
	return feature;
}