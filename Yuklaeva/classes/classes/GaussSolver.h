#ifndef GAUSS_SOLVER_H
#define GAUSS_SOLVER_H

#include "class_Vector_Matrix.h"
#include <vector>
#include <string>

class GaussSolver {
private:
    Matrix A;           // Матрица коэффициентов
    Vector b;           // Вектор правой части
    Vector x;           // Вектор решения
    bool solutionFound; // Флаг успешности решения

    // Вспомогательные методы
    void swapRows(size_t row1, size_t row2);
    bool forwardElimination();
    void backwardSubstitution();
    bool checkSolution() const;

public:
    // Конструкторы
    GaussSolver();
    GaussSolver(const Matrix& matrix, const Vector& vector);

    // Установка данных
    void setSystem(const Matrix& matrix, const Vector& vector);

    // Решение системы
    bool solve();

    // Получение результатов
    Vector getSolution() const;
    Matrix getMatrix() const;
    Vector getRightHandSide() const;
    bool isSolutionFound() const;

    // Проверка решения
    double getResidualNorm() const;
    bool verifySolution(double tolerance = 1e-6) const;

    // Вывод решения
    void printSolution() const;
    void printSystem() const;
    void printVerification() const;

    // Статический метод для создания случайной системы
    static GaussSolver createRandomSystem(size_t n, std::mt19937& rng);

    // Статический метод для создания системы с заданным решением
    static GaussSolver createSystemWithKnownSolution(const Vector& knownSolution, std::mt19937& rng);
};

#endif
