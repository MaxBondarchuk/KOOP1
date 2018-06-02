#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class function
{
public:
	int a = 1;
	int b = 4;

	double dx = 0.1;
	double x1 = -1.5;
	double x2 = 1.5;

	function();
	~function();

	void Tab() const
	{
		cout << "----------------------------------------------------" << endl;
		auto n = 1;
		for (auto x = x1; x < x2; x += dx, n++)
		{
			tab_row(x, n);
		}
		tab_row(x2, n);
		cout << "----------------------------------------------------" << endl;
	}

private:
	void tab_row(const double x, const int n) const
	{
		double fx;
		if (x <= 0)
			fx = -a * x * x + b * b * x;
		else
			fx = x - a / (x - b);

		cout << "|" << setw(16) << setprecision(2) << x << "|"
			<< setw(16) << setprecision(0) << n << "|"
			<< setw(16) << setprecision(4) << fx << "|" << endl;
	}
};


inline function::function() = default;


inline function::~function() = default;
