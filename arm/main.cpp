#include <iostream>
#include "matrix.h"
#include "DH.h"

using namespace std;



int main() try
{
	/*Kinetic k;
	auto a = k.Fk(10.5, 1, 2.0, 0);
	cout << a << endl;*/

	DH* arms = new DH[6]();

	arms[0] = { PI / 2, 0, 0.43, 0 };
	arms[1] = { 0, 0, 0.43, 0 };
	arms[2] = { 0, 0, 0.43, 0 };
	arms[3] = { PI / 2, 0, 0.43, 0 };
	arms[4] = {-PI / 2, 0, 0.43, 0 };
	arms[5] = { 0, 0, 0.43, 0 };
	int aaa[10];
	cout << getArraySize(aaa);
	matrix::Matrix<double> a(4, 4);
	a.at(2, 2) = 6;
	matrix::Matrix b = a;

	matrix::TMatrix t1;
	matrix::TMatrix t2 = t1;
}	
catch (const char* msg)
{
	cout << msg << endl;
}