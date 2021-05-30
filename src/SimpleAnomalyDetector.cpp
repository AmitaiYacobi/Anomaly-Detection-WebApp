// 313301764 Omer Schloss
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
	threshold = (float)0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
}

float SimpleAnomalyDetector::findThreshold(Point **p, size_t len, Line rl)
{
	float max = 0;
	for (size_t i = 0; i < len; i++)
	{
		float d = abs(p[i]->y - rl.f(p[i]->x));
		if (d > max)
			max = d;
	}
	return max;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{

	vector<string> feature = ts.getVectorFeatures();

	for (vector<string>::iterator iterA = feature.begin(); iterA != feature.end(); iterA++)
	{
		correlatedFeatures corFeatures;
		corFeatures.corrlation = 0;
		// check for the most correlated features.
		for (vector<string>::iterator iterB = iterA + 1; iterB != feature.end(); iterB++)
		{
			// check for pearson between the features and save the max correlated features.
			float pears = abs(pearson(ts.getVectorByFeature(*iterA).data(), ts.getVectorByFeature(*iterB).data(), static_cast<int>(ts.getSizeOfVector(*iterA))));
			if (pears > corFeatures.corrlation)
			{
				corFeatures.corrlation = pears;
				corFeatures.feature1 = *iterA;
				corFeatures.feature2 = *iterB;
			}
		}
		if (corFeatures.corrlation > 0)
		{
			size_t size = min(ts.getSizeOfVector(corFeatures.feature1), ts.getSizeOfVector(corFeatures.feature2));
			// create an array of points with the vector of feature1 as x and vector of feature2 as y.
			Point **p = new Point *[size];
			vector<float> FeatureA = ts.getVectorByFeature(corFeatures.feature1);
			vector<float> FeatureB = ts.getVectorByFeature(corFeatures.feature2);
			for (size_t i = 0; i < size; i++)
			{
				p[i] = new Point(FeatureA.at(i), FeatureB.at(i));
			}

			learnHelper(ts, corFeatures.corrlation, corFeatures.feature1, corFeatures.feature2, p);
			// at the end delete all the points.
			for (size_t i = 0; i < size; i++)
			{
				delete p[i];
			}
			delete[] p;
		}
	}
}

void SimpleAnomalyDetector::learnHelper(const TimeSeries &ts, float p /*Pearson*/, string f1, string f2, Point **ps)
{
	if (p >= threshold)
	{
		size_t len = ts.getSizeOfVector(f1);
		correlatedFeatures c;
		c.feature1 = f1;
		c.feature2 = f2;
		c.corrlation = p;
		c.lin_reg = linear_reg(ps, static_cast<int>(len));
		c.threshold = findThreshold(ps, len, c.lin_reg) * (float)1.1; // 10% increase
		cf.push_back(c);
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	vector<AnomalyReport> report;
	// Itterate over the correlated features on the line/
	for_each(cf.begin(), cf.end(), [&report, &ts, this](correlatedFeatures c) {
		// find the minimal size of vector for the correlated feature, safe for mistake in fle.
		vector<correlatedFeatures>::iterator iter = cf.begin();
		size_t size = min(ts.getSizeOfVector(iter->feature1), ts.getSizeOfVector(iter->feature2));
		iter++;
		for (; iter != cf.end(); iter++)
		{
			size = min(size, ts.getSizeOfVector(iter->feature1));
			size = min(size, ts.getSizeOfVector(iter->feature2));
		}
		// Go over every line of ts a report the anomalies
		for (long timeStep = 0; timeStep < size; timeStep++)
		{
			if (ts.isFeatureInTimeSeries(c.feature1) && ts.isFeatureInTimeSeries(c.feature2))
			{
				if (isAnomalous(ts.getVectorByFeature(c.feature1).at(timeStep), ts.getVectorByFeature(c.feature2).at(timeStep), c))
				{
					string desc = ts.trans(c.feature1) + " - " + ts.trans(c.feature2);
					report.push_back(AnomalyReport(desc, timeStep + 1));
				}
			}
		}
	});

	return report;
}

bool SimpleAnomalyDetector::isAnomalous(float x, float y, correlatedFeatures c)
{

	return (abs(y - c.lin_reg.f(x)) > c.threshold);
}
