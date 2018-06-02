#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class function
{
public:
	int a = 1;
	int b = 4;

	double dx = 0.1;
	double x1 = -1.5;
	double x2 = 1.5;

	double delta = .06;

	const int A = 80;

	function();
	~function();

	void Tab() const
	{
		cout << "----------------------------------------------------" << endl;
		cout << "|" << setw(16) << "X" << "|"
			<< setw(16) << "N" << "|"
			<< setw(16) << "f(x)" << "|" << endl;
		cout << "----------------------------------------------------" << endl;
		for (auto i = 1; i < x_.size(); i++)
		{
			cout << "|" << setw(16) << setprecision(2) << x_[i] << "|"
				<< setw(16) << setprecision(0) << n_[i] << "|"
				<< setw(16) << setprecision(4) << fx_[i] << "|" << endl;
		}
		cout << "----------------------------------------------------" << endl;
	}

	void Tab_S()
	{
		cout << "----------------------------------------------------" << endl;
		cout << "|" << setw(25) << "S1" << "|" << setw(24) << get_s1() << "|" << endl
			<< "|" << setw(25) << "S2" << "|" << setw(24) << get_s2() << "|" << endl;
		cout << "----------------------------------------------------" << endl;
		auto rnd = generate_randoms();
		for (auto i = 0; i < rnd.size(); i++)
			cout << "|" << setw(48 + 2) << rnd[i] << "|" << endl;
		cout << "----------------------------------------------------" << endl;
	}

	double get_s1()
	{
		double sum = 0;
		auto count = 0;
		for (auto i = 0; i < fx_.size(); i++)
			if (fx_[i] < 0)
			{
				sum += fx_[i];
				count++;
			}

		return sum / static_cast<double>(count);
	}

	double get_s2()
	{
		double sum = 0;
		auto count = 0;
		for (auto i = 0; i < fx_.size(); i++)
			if (n_[i] % 2 == 0)
			{
				sum += fx_[i];
				count++;
			}

		return sum / static_cast<double>(count);
	}

	vector<double> generate_randoms()
	{
		//auto rnd = vector<double>(x_.size());
		auto rnd = vector<double>();

		const auto s1 = get_s1();
		const auto s2 = get_s2();

		auto smin = min(s1, s2);
		auto smax = max(s1, s2);

		const auto s = (s1 + s2) / 2;

		srand(s * delta);
		//srand(time(nullptr));
		for (auto i = 0; i < x_.size(); i++)
		{
			const auto f = static_cast<double>(rand()) / RAND_MAX;
			rnd.push_back(s1 + f * (s2 - s1));
		}

		return rnd;
	}

	void Print() const
	{
		for (auto a = A; 0 <= a; a--)
		{
			for (auto i = 0; i < fx_.size(); i++)
				cout << (toa_[i] == a ? "▀" : " ");
			cout << endl;
		}
	}

	vector<int> transform_to_a()
	{
		auto a_vector = vector<int>();

		const auto minmax = minmax_element(fx_.begin(), fx_.end());
		const auto fx_min = *minmax.first;
		const auto fx_max = *minmax.second;

		const auto fx_delta = fx_max - fx_min;

		for (auto i = 0; i < fx_.size(); i++)
		{
			a_vector.push_back((fx_[i] - fx_min) * A / fx_delta);
			toa_.push_back((fx_[i] - fx_min) * A / fx_delta);
		}

		return a_vector;
	}

private:
	vector<double> x_;
	vector<int> n_;
	vector<double> fx_;
	vector<int> toa_;

	double calculate(const double x) const
	{
		return x <= 0 ? -a * x * x + b * b * x : x - a / (x - b);
	}

	void fill_row(const double x, const int n)
	{
		x_.push_back(x);
		n_.push_back(n);
		fx_.push_back(calculate(x));
	}
};


inline function::function()
{
	auto n = 0;
	for (auto x = x1; x < x2; x += dx, n++)
	{
		fill_row(x, n);
	}
	fill_row(x2, n);
};


inline function::~function() = default;
