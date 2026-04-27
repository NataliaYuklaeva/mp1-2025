#include "Rectangle.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <clocale>

using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Функция для вывода разделителя
void printSeparator() {
    cout << string(70, '=') << endl;
}

// Функция для демонстрации различных примеров
void demonstrateStaticMethod() {
    cout << "\n--- ДЕМОНСТРАЦИЯ СТАТИЧЕСКОГО МЕТОДА ---" << endl;

    // Пример 1: Интегрирование x^2 от 0 до 1 (точное значение: 1/3 ≈ 0.3333333)
    auto func1 = [](double x) { return x * x; };
    double result1 = RectangleIntegrator::integrate(func1, 0.0, 1.0, 1000, RectangleType::MIDDLE);
    cout << "| x^2 dx от 0 до 1 = " << fixed << setprecision(8) << result1 << endl;
    cout << "Точное значение: 0.33333333" << endl;

    // Пример 2: Интегрирование sin(x) от 0 до π (точное значение: 2)
    auto func2 = [](double x) { return sin(x); };
    double result2 = RectangleIntegrator::integrate(func2, 0.0, M_PI, 1000, RectangleType::MIDDLE);
    cout << "| sin(x) dx от 0 до pi = " << fixed << setprecision(8) << result2 << endl;
    cout << "Точное значение: 2.00000000" << endl;

    // Пример 3: Интегрирование exp(x) от 0 до 1 (точное значение: e - 1 ≈ 1.7182818)
    auto func3 = [](double x) { return exp(x); };
    double result3 = RectangleIntegrator::integrate(func3, 0.0, 1.0, 1000, RectangleType::MIDDLE);
    cout << "| e^x dx от 0 до 1 = " << fixed << setprecision(8) << result3 << endl;
    cout << "Точное значение: 1.71828183" << endl;
}

// Демонстрация различных методов
void demonstrateDifferentMethods() {
    cout << "\n--- СРАВНЕНИЕ МЕТОДОВ ПРЯМОУГОЛЬНИКОВ ---" << endl;

    auto func = [](double x) { return x * x * x; };
    RectangleIntegrator integrator(func, 0.0, 2.0, 100);

    cout << "Функция: f(x) = x^3 на интервале [0, 2]" << endl;
    cout << "Точное значение интеграла: 4.00000000" << endl << endl;

    cout << left << setw(20) << "Метод"
        << setw(20) << "Результат"
        << setw(20) << "Погрешность" << endl;
    printSeparator();

    double exact = 4.0;

    double left = integrator.integrate(RectangleType::LEFT);
    double right = integrator.integrate(RectangleType::RIGHT);
    double middle = integrator.integrate(RectangleType::MIDDLE);

    cout << left << setw(20) << "Левые"
        << setw(20) << fixed << setprecision(8) << left
        << setw(20) << scientific << abs(left - exact) << endl;

    cout << left << setw(20) << "Правые"
        << setw(20) << fixed << setprecision(8) << right
        << setw(20) << scientific << abs(right - exact) << endl;

    cout << left << setw(20) << "Средние"
        << setw(20) << fixed << setprecision(8) << middle
        << setw(20) << scientific << abs(middle - exact) << endl;
}

// Демонстрация сходимости
void demonstrateConvergence() {
    cout << "\n--- АНАЛИЗ СХОДИМОСТИ ---" << endl;

    auto func = [](double x) { return 1.0 / (1.0 + x * x); }; // ∫ dx/(1+x^2) от 0 до 1 = π/4 ≈ 0.785398
    RectangleIntegrator integrator(func, 0.0, 1.0, 10);

    cout << "Функция: f(x) = 1/(1+x^2) на интервале [0, 1]" << endl;
    cout << "Точное значение: pi/4 = 0.7853981634" << endl << endl;

    cout << left << setw(15) << "Разбиения"
        << setw(20) << "Результат"
        << setw(20) << "Погрешность" << endl;
    printSeparator();

    double exact = M_PI / 4.0;
    auto history = integrator.getConvergenceHistory(1280, RectangleType::MIDDLE);

    for (size_t i = 0; i < history.size(); ++i) {
        int n = history[i].first;
        double result = history[i].second;
        cout << left << setw(15) << n
            << setw(20) << fixed << setprecision(8) << result
            << setw(20) << scientific << abs(result - exact) << endl;
    }
}

// Демонстрация работы с разными функциями через лямбда-выражения
void demonstrateLambdaFunctions() {
    cout << "\n--- РАЗЛИЧНЫЕ ФУНКЦИИ ЧЕРЕЗ ЛЯМБДА-ВЫРАЖЕНИЯ ---" << endl;

    vector<pair<string, function<double(double)>>> functions = {
        {"f(x) = x^2 - 2x + 1", [](double x) { return x * x - 2 * x + 1; }},
        {"f(x) = e^(-x^2)", [](double x) { return exp(-x * x); }},
        {"f(x) = ln(x+1)", [](double x) { return log(x + 1); }},
        {"f(x) = sqrt(x)", [](double x) { return sqrt(x); }},
        {"f(x) = cos(x)", [](double x) { return cos(x); }}
    };

    vector<pair<double, double>> intervals = { {0, 1}, {0, 2}, {0, 1}, {0, 4}, {0, M_PI / 2} };
    vector<double> exact_values = { 0.333333, 0.882081, 0.386294, 5.333333, 1.000000 };

    for (size_t i = 0; i < functions.size(); ++i) {
        cout << "\n" << i + 1 << ". " << functions[i].first << endl;
        cout << "   Интервал: [" << intervals[i].first << ", " << intervals[i].second << "]" << endl;

        double result = RectangleIntegrator::integrate(functions[i].second,
            intervals[i].first,
            intervals[i].second,
            1000,
            RectangleType::MIDDLE);

        cout << "   Приближенное значение: " << fixed << setprecision(6) << result << endl;
        cout << "   Точное значение (приблиз.): " << exact_values[i] << endl;
        cout << "   Относительная погрешность: " << scientific << abs(result - exact_values[i]) / exact_values[i] * 100 << "%" << endl;
    }
}

// Интерактивный режим
void interactiveMode() {
    cout << "\n--- ИНТЕРАКТИВНЫЙ РЕЖИМ ---" << endl;

    int choice;
    cout << "Выберите функцию для интегрирования:" << endl;
    cout << "1. f(x) = x^2" << endl;
    cout << "2. f(x) = sin(x)" << endl;
    cout << "3. f(x) = cos(x)" << endl;
    cout << "4. f(x) = exp(x)" << endl;
    cout << "5. f(x) = 1/x" << endl;
    cout << "6. Пользовательская функция" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    function<double(double)> func;
    string funcName;

    switch (choice) {
    case 1:
        func = [](double x) { return x * x; };
        funcName = "x^2";
        break;
    case 2:
        func = [](double x) { return sin(x); };
        funcName = "sin(x)";
        break;
    case 3:
        func = [](double x) { return cos(x); };
        funcName = "cos(x)";
        break;
    case 4:
        func = [](double x) { return exp(x); };
        funcName = "exp(x)";
        break;
    case 5:
        func = [](double x) { return 1.0 / x; };
        funcName = "1/x";
        break;
    case 6: {
        cout << "Введите лямбда-выражение (используйте x как переменную): ";
        string lambdaStr;
        cin.ignore();
        getline(cin, lambdaStr);
        // Простой парсинг не реализован, используем предопределенную
        cout << "Используется f(x) = x^2 для демонстрации" << endl;
        func = [](double x) { return x * x; };
        funcName = "x^2 (пользовательская)";
        break;
    }
    default:
        func = [](double x) { return x * x; };
        funcName = "x^2";
    }

    double a, b;
    cout << "Введите нижний предел: ";
    cin >> a;
    cout << "Введите верхний предел: ";
    cin >> b;

    int n;
    cout << "Введите количество разбиений: ";
    cin >> n;

    RectangleIntegrator integrator(func, a, b, n);
    integrator.printInfo(RectangleType::MIDDLE);
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "========================================" << endl;
    cout << "   ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ" << endl;
    cout << "   МЕТОД ПРЯМОУГОЛЬНИКОВ" << endl;
    cout << "========================================" << endl;

    demonstrateStaticMethod();
    printSeparator();

    demonstrateDifferentMethods();
    printSeparator();

    demonstrateConvergence();
    printSeparator();

    demonstrateLambdaFunctions();
    printSeparator();

    int mode;
    cout << "\nВыберите режим работы:" << endl;
    cout << "1. Интерактивный режим" << endl;
    cout << "2. Выход" << endl;
    cout << "Ваш выбор: ";
    cin >> mode;

    if (mode == 1) {
        interactiveMode();
    }

    cout << "\nПрограмма завершена!" << endl;
    return 0;
}