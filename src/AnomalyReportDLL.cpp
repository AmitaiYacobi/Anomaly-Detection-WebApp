#include "AnomalyReportDLL.h"

string CreateAnomalyReportSimple(string inputTrainPath, string inputTestPath, string output)
{
	STDtest std(output);
	TimeSeries ts(inputTrainPath.c_str());
	size_t numOfLines = ts.getSizeOfVector(ts.getVectorFeatures().at(0));
	SimpleAnomalyDetector ad;
	ad.learnNormal(ts);

	TimeSeries ts2(inputTestPath.c_str());
	vector<AnomalyReport> reports = ad.detect(ts2);
	
	std.write("Time (row),Correlated Features\n");
	vector<AnomalyReport>::iterator it = reports.begin();
	for (; it != reports.end(); it++)
	{
		std.write(to_string(it->timeStep));
		std.write(",");
		std.write(it->description);
		std.write("\n");
	}
	std.close();
	return "done!";
}
string CreateAnomalyReportHybrid(string inputTrainPath, string inputTestPath, string output)
{
	STDtest std(output);
	TimeSeries ts(inputTrainPath.c_str());
	size_t numOfLines = ts.getSizeOfVector(ts.getVectorFeatures().at(0));
	HybridAnomalyDetector ad;
	ad.learnNormal(ts);
	
	TimeSeries ts2(inputTestPath.c_str());

	vector<AnomalyReport> reports = ad.detect(ts2);
	std.write("Time_(row),Correlated_Features\n");
	
	vector<AnomalyReport>::iterator it = reports.begin();
	for (; it != reports.end(); it++)
	{
		std.write(to_string(it->timeStep));
		std.write(",");
		std.write(it->description);
		std.write("\n");
	}

	std.close();
	return "done!";
}