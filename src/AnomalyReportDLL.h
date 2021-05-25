#ifndef ANOMALYDREPORTDLL_H_
#define ANOMALYDREPORTDLL_H_


#include <iostream>
#include <fstream>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"

using namespace std;

class STDtest {
	ofstream out;
public:
	STDtest(string outputFile) {
		out.open(outputFile);
	}

	virtual void write(string text) {
		out << text;
	}

	virtual void write(float f) {
		out << f;
	}

	void close() {
		if (out.is_open())
			out.close();
	}
	~STDtest() {
		close();
	}
};

string CreateAnomalyReportSimple(string inputTrainPath, string inputTestPath, string output);
string CreateAnomalyReportHybrid(string inputTrainPath, string inputTestPath, string output);

#endif /* ANOMALYDREPORTDLL_H_ */