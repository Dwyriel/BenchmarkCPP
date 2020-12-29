#include "Utility.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
using namespace std;
using namespace Utility;

class Vector2 {
public:
	float x;
	float y;
	static Vector2 up() { return Vector2(0, 1); }
	static Vector2 down() { return Vector2(0, -1); }
	static Vector2 right() { return Vector2(1, 0); }
	static Vector2 left() { return Vector2(-1, 0); }

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2() {
		this->x = 0;
		this->y = 0;
	}
	operator string() const { return "x: " + toString(x) + " y: " + toString(y); }
};

Vector2 ifelseTest(float angle) {
	Vector2 instPlace = Vector2(0, 0);
	if (abs(angle) > 22.5f && abs(angle) <= 67.5f)
		instPlace = (angle > 0) ? Vector2(-.7f, .7f) : Vector2(.7f, .7f);
	else if (abs(angle) > 67.5f && abs(angle) <= 112.5f)
		instPlace = (angle > 0) ? Vector2::left() : Vector2::right();
	else if (abs(angle) > 112.5f && abs(angle) <= 157.5f)
		instPlace = (angle > 0) ? Vector2(-.7f, -.7f) : Vector2(.7f, -.7f);
	else
		instPlace = (abs(angle) > 90) ? Vector2::down() : Vector2::up();
	return instPlace;
}

Vector2 ternaryTest(float signedAngle) {

	return (signedAngle > 0) ? (abs(signedAngle) < 22.5f) ? Vector2::up() : (abs(signedAngle) < 67.5f) ? Vector2(-.7f, .7f) : (abs(signedAngle) < 112.5f) ? Vector2::left() : (abs(signedAngle) < 157.5f) ? Vector2(-.7f, -.7f) : Vector2::down() : (abs(signedAngle) < 22.5f) ? Vector2::up() : (abs(signedAngle) < 67.5f) ? Vector2(.7f, .7f) : (abs(signedAngle) < 112.5f) ? Vector2::right() : (abs(signedAngle) < 157.5f) ? Vector2(.7f, -.7f) : Vector2::down();
}

int main()
{
	//const int numOfThreads = thread::hardware_concurrency();
	//cout << "number of threads: " << numOfThreads << "\n";
	cout << "Disclaimer: this application is single threaded until further learning.\n";
	cout << fixed;
	cout.precision(2);
	default_random_engine generator;
	uniform_real_distribution<float> distribution(-180, 180);
	auto randAngle = bind(distribution, generator);
	vector<double> ternary, ifelse;
	long long iterations = 1000, iterationsPerTest = 1000000, totalIterations = 0;
	float signedAngle = 0;
	string sInput;
	Vector2 returnedV2 = Vector2(0, 0);
	cout << "\nPress enter to begin\n";
	getline(cin, sInput, '\n');
	cout << "Starting";
	this_thread::sleep_for(1500ms);
	for (long long i = 0; i < iterations; i++) {
		double tern = 0, ifel = 0;
		auto start = chrono::high_resolution_clock::now();
		signedAngle = randAngle();
		for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
			signedAngle = randAngle();
			Vector2 returnedV2 = ifelseTest(signedAngle);
			totalIterations++;
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> elapsed = end - start;
		ifel = elapsed.count();
		elapsed.zero();
		ifelse.push_back(ifel);
		start = chrono::high_resolution_clock::now();
		for (int i2 = 0; i2 < iterationsPerTest; i2++) {
			signedAngle = randAngle();
			Vector2 returnedV2 = ternaryTest(signedAngle);
			totalIterations++;
		}
		end = chrono::high_resolution_clock::now();
		elapsed = end - start;
		tern = elapsed.count();
		ternary.push_back(tern);
		cout << "\nIteration " << i << ":" << endl << "ifelse - " << toString(ifel) << endl << "ternary - " << toString(tern) << endl;
	}
	cout << "\nInverting\n";
	this_thread::sleep_for(500ms);
	for (int i = 0; i < iterations; i++) {
		double tern = 0, ifel = 0;
		auto start = chrono::high_resolution_clock::now();
		for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
			signedAngle = randAngle();
			Vector2 returnedV2 = ternaryTest(signedAngle);
			totalIterations++;
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, std::milli> elapsed = end - start;
		tern = elapsed.count();
		elapsed.zero();
		ternary.push_back(tern);
		start = chrono::high_resolution_clock::now();
		for (long long i2 = 0; i2 < iterationsPerTest; i2++) {
			signedAngle = randAngle();
			Vector2 returnedV2 = ifelseTest(signedAngle);
			totalIterations++;
		}
		end = chrono::high_resolution_clock::now();
		elapsed = end - start;
		ifel = elapsed.count();
		ifelse.push_back(ifel);
		cout << "\nIteration " << i << ":" << endl << "ifelse - " << toString(ifel) << endl << "ternary - " << toString(tern) << endl;
	}
	double totalTime = 0;
	for (double time : ifelse) {
		totalTime += time;
	}
	cout << "\nAvg ifelse: " << toString(totalTime / ifelse.size());
	totalTime = 0;
	for (double time : ternary) {
		totalTime += time;
	}
	cout << "\nAvg ternary: " << toString(totalTime / ternary.size());
	cout << "\ntotal iterations: " << totalIterations << "\n";
	getline(cin, sInput, '\n');
}


/*
		vector<thread> threads;
	vector<int> counting;


for (int i = 0; i < numOfThreads; i++) {
			thread thread([](vector<int>& c) {
				this_thread::sleep_for(1000ms);
				c.push_back(1);
				}, ref(counting));
			threads.push_back(move(thread));
			string s = "Thread " + toString(i) + " - Starting.\n";
			cout << s;
		}

		for (thread& th : threads) {
			th.join();
		}	*/