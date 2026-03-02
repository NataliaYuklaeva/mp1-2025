#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <clocale>

template<typename hehe>
hehe Taylor_e(hehe x, int k) {
	hehe sum = 1; hehe elem = 1;
	for (int i = 1; i < k; i++) {
		elem = elem * (x / k);
		sum += elem;
	}
	return sum;
}
template<typename khkh>
khkh normalize(khkh x) {
	return fmod(x, 2 * M_PI);
}
template<typename knkn>
knkn sgn(knkn x) {
	return (x >= 0 ? 1 : -1);
}
template<typename kiki>
void check_and_transform(kiki& x) {
	if (fabs(x) > 1) {
		x = normalize(x);

		while (fabs(x) > 1) { 
			x -= sgn(x);
		}
	}
}

template<typename hmhm>
hmhm Taylor_sin(hmhm x, int k) {
	hmhm sum = x; hmhm elem = x;
	for (int i = 1; i < (k / 2); i++) {
		elem = (-1 * elem * x * x) / (2 * i) / (2 * (i + 1));
		sum += elem;
	}
	return sum;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double x;
	int n;

	std::cout << "Введите значение х: ";
	std::cin >> x;
	std::cout << "Введите количество членов разложения для формулы Тейлора: ";
	std::cin >> n;
	double x2 = x;
	double approx_e = Taylor_e<double>(x, n);
	check_and_transform<double>(x2);
	double approx_sin = Taylor_sin<double>(x2, n);

	std::cout << "\nСумма первых " << n << " членов ряда Тейлора для e(" << x << ") равна: " << approx_e << std::endl;
	std::cout << "Сумма первых " << n << " членов ряда Тейлора для sin(" << x << ") равна: " << approx_sin << std::endl;

	return 0;
}