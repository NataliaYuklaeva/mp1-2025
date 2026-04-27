#include "Rectangle.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// Конструктор по умолчанию
RectangleIntegrator::RectangleIntegrator()
    : func([](double x) { return 0.0; }), a(0.0), b(1.0), n(100) {
}

// Конструктор с параметрами
RectangleIntegrator::RectangleIntegrator(const std::function<double(double)>& f,
    double lower, double upper, int partitions)
    : func(f), a(lower), b(upper), n(partitions) {
    if (n <= 0) n = 100;
    if (a > b) std::swap(a, b);
}

// Методы установки параметров
void RectangleIntegrator::setFunction(const std::function<double(double)>& f) {
    func = f;
}

void RectangleIntegrator::setLimits(double lower, double upper) {
    a = lower;
    b = upper;
    if (a > b) std::swap(a, b);
}

void RectangleIntegrator::setPartitions(int partitions) {
    if (partitions > 0) {
        n = partitions;
    }
}

// Интегрирование левыми прямоугольниками
double RectangleIntegrator::integrateLeft() const {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

// Интегрирование правыми прямоугольниками
double RectangleIntegrator::integrateRight() const {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 1; i <= n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

// Интегрирование средними прямоугольниками
double RectangleIntegrator::integrateMiddle() const {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = a + (i + 0.5) * h;
        sum += func(x);
    }

    return sum * h;
}

// Статический метод интегрирования
double RectangleIntegrator::integrate(const std::function<double(double)>& func,
    double a, double b,
    int n,
    RectangleType type) {
    RectangleIntegrator integrator(func, a, b, n);
    return integrator.integrate(type);
}

// Нестатический метод интегрирования
double RectangleIntegrator::integrate(RectangleType type) const {
    switch (type) {
    case RectangleType::LEFT:
        return integrateLeft();
    case RectangleType::RIGHT:
        return integrateRight();
    case RectangleType::MIDDLE:
        return integrateMiddle();
    default:
        return integrateMiddle();
    }
}

// Оценка погрешности методом Рунге
double RectangleIntegrator::estimateError(double tolerance, RectangleType type) const {
    double I1 = integrate(type);

    // Удваиваем количество разбиений
    RectangleIntegrator integrator2(func, a, b, n * 2);
    double I2 = integrator2.integrate(type);

    // Оценка погрешности по Рунге
    // Для метода прямоугольников порядок точности p = 1 (для левых и правых) и p = 2 (для средних)
    int p = (type == RectangleType::MIDDLE) ? 2 : 1;
    double error = std::abs(I2 - I1) / (std::pow(2, p) - 1);

    return error;
}

// Вывод информации об интегрировании
void RectangleIntegrator::printInfo(RectangleType type) const {
    std::cout << "\n=== ИНФОРМАЦИЯ ОБ ИНТЕГРИРОВАНИИ ===" << std::endl;
    std::cout << "Нижний предел: " << a << std::endl;
    std::cout << "Верхний предел: " << b << std::endl;
    std::cout << "Количество разбиений: " << n << std::endl;
    std::cout << "Шаг интегрирования: " << (b - a) / n << std::endl;

    std::cout << "\nРезультаты разными методами:" << std::endl;
    std::cout << "Левые прямоугольники: " << std::fixed << std::setprecision(8) << integrate(RectangleType::LEFT) << std::endl;
    std::cout << "Правые прямоугольники: " << std::fixed << std::setprecision(8) << integrate(RectangleType::RIGHT) << std::endl;
    std::cout << "Средние прямоугольники: " << std::fixed << std::setprecision(8) << integrate(RectangleType::MIDDLE) << std::endl;

    double error = estimateError(1e-6, type);
    std::cout << "\nОценка погрешности (метод Рунге): " << std::scientific << error << std::endl;
}

// Получение истории сходимости
std::vector<std::pair<int, double>> RectangleIntegrator::getConvergenceHistory(int maxPartitions, RectangleType type) const {
    std::vector<std::pair<int, double>> history;

    for (int partitions = 10; partitions <= maxPartitions; partitions *= 2) {
        RectangleIntegrator integrator(func, a, b, partitions);
        double result = integrator.integrate(type);
        history.push_back({ partitions, result });
    }

    return history;
}

// Геттеры
std::function<double(double)> RectangleIntegrator::getFunction() const {
    return func;
}

double RectangleIntegrator::getLowerLimit() const {
    return a;
}

double RectangleIntegrator::getUpperLimit() const {
    return b;
}

int RectangleIntegrator::getPartitions() const {
    return n;
}