#include <napi.h>
#include <string>
#include "AnomalyReportDLL.h"

// native C++ function that is assigned to `algoSimple` property on `exports` object
Napi::String algoRegression(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	// call `CreateAnomalyReportSimple` function from `AnomalyReportDLL.cpp` file
	std::string inputTrainPath = (std::string)info[0].ToString();
	std::string inputTestPath = (std::string)info[1].ToString();
	std::string outputPath = (std::string)info[2].ToString();
	std::string result = CreateAnomalyReportSimple(inputTrainPath, inputTestPath, outputPath);

	// return new `Napi::String` value
	return Napi::String::New(env, result);
}

// native C++ function that is assigned to `algoHybrid` property on `exports` object
Napi::String algoHybrid(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	// call `CreateAnomalyReportHybrid` function from `AnomalyReportDLL.cpp` file
	std::string inputTrainPath = (std::string)info[0].ToString();
	std::string inputTestPath = (std::string)info[1].ToString();
	std::string outputPath = (std::string)info[2].ToString();
	std::string result = CreateAnomalyReportHybrid(inputTrainPath, inputTestPath, outputPath);

	// return new `Napi::String` value
	return Napi::String::New(env, result);
}

// callback method when module is registered with Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {

	// set a key on `exports` object
	exports.Set(
		Napi::String::New(env, "algoRegression"), // property name => "algoRegression"
		Napi::Function::New(env, algoRegression) // property value => `algoRegression` function
	);

	exports.Set(
		Napi::String::New(env, "algoHybrid"), // property name => "algoHybrid"
		Napi::Function::New(env, algoHybrid) // property value => `algoHybrid` function
	);

	// return `exports` object (always)
	return exports;
}

// register `greet` module which calls `Init` method
NODE_API_MODULE(greet, Init)