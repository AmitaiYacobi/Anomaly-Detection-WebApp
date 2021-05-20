// 313301764 Omer Schloss
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnHelper(const TimeSeries& ts, float p, string f1, string f2, Point** ps)
{
	if ((0.5 < p) && (p < threshold)) {
		size_t len = ts.getSizeOfVector(f1);
		correlatedFeatures c;
		c.feature1 = f1;
		c.feature2 = f2;
		c.corrlation = p;
		Circle min = findMinCircle(ps, static_cast<int>(len));
		c.centerCircle = new Point(min.center.x, min.center.y);
		c.threshold = min.radius * (float)1.1; // 10% increase
		cf.push_back(c);
		return;
	}
	SimpleAnomalyDetector::learnHelper(ts, p, f1, f2, ps);
}

bool HybridAnomalyDetector::isAnomalous(float x, float y, correlatedFeatures c)
{
	if (c.corrlation < threshold) {
		return (dist(*c.centerCircle, Point(x, y)) > c.threshold);
	}
	return SimpleAnomalyDetector::isAnomalous(x, y, c);
}

