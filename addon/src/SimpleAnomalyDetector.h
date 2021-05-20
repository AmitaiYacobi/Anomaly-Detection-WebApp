// 313301764 Omer Schloss
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

struct correlatedFeatures
{
	string feature1, feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	Point* centerCircle;
	float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector
{
	protected:
	// The vector hold all the correlated features
	vector<correlatedFeatures> cf;
	float threshold;
public:
	// Constructor - Default constructor.
	SimpleAnomalyDetector();

	// Destructor.
	virtual ~SimpleAnomalyDetector();

	/*
	The function gets timeseries database as features and vectors and find the most
	 correlated features, their linear regression , threshold and
	 discover their normal pattern.
	*/
	virtual void learnNormal(const TimeSeries &ts);

	/*
	The function gets timeseries database and read line by line and report if there is
	 any anomaly found in the line in the anomaly report, by the vector of the correlated feature
	*/
	virtual vector<AnomalyReport> detect(const TimeSeries &ts);

	vector<correlatedFeatures> getNormalModel()
	{
		return cf;
	}
	float getCorrelationThreshold() {
		return this->threshold;
	}
	void setCorrelationThreshold(float threshold) {
		this->threshold = threshold;
	}

	protected:
	virtual void learnHelper(const TimeSeries& ts, float p/*pearson*/, string f1, string f2, Point** ps);
	virtual bool isAnomalous(float x, float y, correlatedFeatures c);

	float findThreshold(Point** ps, size_t len, Line rl);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
