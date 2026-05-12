#include "shablon.h"
#include <iostream>

using namespace std;

int main() {
	Vector<char> C(1, 'm');
	Matrix<Vector<char>> A(5, 5, C);

	cout << A << endl;
}