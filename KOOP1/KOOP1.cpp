// KOOP1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "function.h"

#include <iostream>

using namespace std;

int main()
{
	auto f = function();

	f.transform_to_a();
	f.Tab();
	cout << endl;

	f.Tab_S();
	cout << endl;

	f.Print();

    return 0;
}

