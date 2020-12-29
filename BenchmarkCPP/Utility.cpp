#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

namespace Utility {
	static string toString(int x) {
		stringstream s;
		s << fixed << x;
		return s.str();
	}

	static string toString(float x) {
		stringstream s;
		s << fixed << setprecision(2) << x;
		return s.str();
	}

	static string toString(double x) {
		stringstream s;
		s << fixed << setprecision(2) << x;
		return s.str();
	}

	static string toString(float x, int precision) {
		stringstream s;
		s << fixed << setprecision(precision) << x;
		return s.str();
	}
}