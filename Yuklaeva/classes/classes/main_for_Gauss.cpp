#include "class_Vector_Matrix.h"
#include "GaussSolver.h"
#include <iostream>
#include <random>
#include <locale>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Функции для ввода данных
void manualInput(GaussSolver& solver);
void randomInput(GaussSolver& solver);
void fileInput(GaussSolver& solver);

int main() {
    setlocale(LC_ALL, "Russian");

    random_device rd;
    mt19937 rng(rd());

    cout << "========================================" << endl;
    cout << "   РЕШЕНИЕ СИСТЕМ ЛИНЕЙНЫХ УРАВНЕНИЙ" << endl;
    cout << "         МЕТОДОМ ГАУССА" << endl;
    cout << "========================================" << endl;

    GaussSolver solver;
    int choice;

    do {
        cout << "\nВыберите способ ввода данных:" << endl;
        cout << "1. Ручной ввод" << endl;
        cout << "2. Генерация случайной системы" << endl;
        cout << "3. Чтение из файла" << endl;
        cout << "4. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manualInput(solver);
            break;
        case 2:
            randomInput(solver);
            break;
        case 3:
            fileInput(solver);
            break;
        case 4:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }

        if (choice >= 1 && choice <= 3) {
            cout << "\n--- Решение системы ---" << endl;
            solver.printSystem();

            if (solver.solve()) {
                solver.printSolution();
                solver.printVerification();
            }
            else {
                cout << "Не удалось решить систему!" << endl;
            }
        }

    } while (choice != 4);

    return 0;
}

void manualInput(GaussSolver& solver) {
    size_t n;
    cout << "\n--- РУЧНОЙ ВВОД ---" << endl;
    cout << "Введите размерность системы (n): ";
    cin >> n;

    Matrix A(n, n);
    Vector b(n);

    cout << "\nВведите матрицу коэффициентов A (" << n << "x" << n << "):" << endl;
    for (size_t i = 0; i < n; ++i) {
        cout << "Строка " << i + 1 << ": ";
        for (size_t j = 0; j < n; ++j) {
            cin >> A(i, j);
        }
    }

    cout << "\nВведите вектор правой части b (" << n << " элементов):" << endl;
    cout << "b: ";
    for (size_t i = 0; i < n; ++i) {
        cin >> b(i);
    }

    solver.setSystem(A, b);
}

void randomInput(GaussSolver& solver) {
    cout << "\n--- ГЕНЕРАЦИЯ СЛУЧАЙНОЙ СИСТЕМЫ ---" << endl;

    size_t n;
    int type;

    cout << "Введите размерность системы (n): ";
    cin >> n;

    cout << "Выберите тип генерации:" << endl;
    cout << "1. Полностью случайная система" << endl;
    cout << "2. Система с известным решением" << endl;
    cout << "Ваш выбор: ";
    cin >> type;

    random_device rd;
    mt19937 rng(rd());

    if (type == 1) {
        solver = GaussSolver::createRandomSystem(n, rng);
    }
    else {
        Vector knownSolution(n);
        cout << "Введите известное решение (через пробел): ";
        for (size_t i = 0; i < n; ++i) {
            cin >> knownSolution(i);
        }
        solver = GaussSolver::createSystemWithKnownSolution(knownSolution, rng);
    }

    cout << "\nСлучайная система сгенерирована!" << endl;
}

void fileInput(GaussSolver& solver) {
    cout << "\n--- ЧТЕНИЕ ИЗ ФАЙЛА ---" << endl;

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    size_t n;
    file >> n;

    if (file.fail() || n == 0) {
        cout << "Ошибка: неверный формат файла!" << endl;
        file.close();
        return;
    }

    Matrix A(n, n);
    Vector b(n);

    // Чтение матрицы
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            file >> A(i, j);
            if (file.fail()) {
                cout << "Ошибка: неверный формат матрицы в файле!" << endl;
                file.close();
                return;
            }
        }
    }

    // Чтение вектора правой части
    for (size_t i = 0; i < n; ++i) {
        file >> b(i);
        if (file.fail()) {
            cout << "Ошибка: неверный формат вектора в файле!" << endl;
            file.close();
            return;
        }
    }

    file.close();

    cout << "\nДанные успешно загружены из файла!" << endl;
    cout << "Размерность системы: " << n << endl;

    solver.setSystem(A, b);
}