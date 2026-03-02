//#include <iostream>
//#include <cmath>

//long long factorial(int n) {
  //  if (n <= 1)
    //    return 1;
    //else
      //  return n * factorial(n - 1);
//}

//double taylor_e(double x, int N) {
  //  double result = 0.0;
    //for (int k = 0; k < N; ++k) {
      //  result += pow(x, k) / factorial(k);
    //}
    //return result;
//}

//double taylor_sin(double x, int N) {
  //  double result = 0.0;
    //for (int k = 0; k < N; ++k) {
      //  int power = 2 * k + 1;
        //int sign = ((k % 2 == 0) ? 1 : -1);
        //result += sign * pow(x, power) / factorial(power);
    //}
    //return result;
//}

//int main() {
    //double x;
    //int N;

    //std::cout << "Введите значение х: ";
    //std::cin >> x;
    //std::cout << "Введите количество членов разложения для формулы Тейлора: ";
    //std::cin >> N;

    //double approx_e = taylor_e(x, N);
    //double approx_sin = taylor_sin(x, N);

    //std::cout << "\nСумма первых " << N << " членов ряда Тейлора для e(" << x << ") равна: " << approx_e << std::endl;
    //std::cout << "Сумма первых " << N << " членов ряда Тейлора для sin(" << x << ") равна: " << approx_sin << std::endl;

    //return 0;
//}