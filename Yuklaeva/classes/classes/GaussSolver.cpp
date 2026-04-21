#include "GaussSolver.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>

GaussSolver::GaussSolver() : A(), b(), x(), solutionFound(false) {}

GaussSolver::GaussSolver(const Matrix& matrix, const Vector& vector)
    : A(matrix), b(vector), solutionFound(false) {
    x = Vector(b.getSize());
}

void GaussSolver::setSystem(const Matrix& matrix, const Vector& vector) {
    A = matrix;
    b = vector;
    x = Vector(b.getSize());
    solutionFound = false;
}

void GaussSolver::swapRows(size_t row1, size_t row2) {
    if (row1 == row2) return;
    std::swap(A[row1], A[row2]);
//    for (size_t j = 0; j < A.getCols(); ++j) {
//        std::swap(A(row1, j), A(row2, j));
//    }
    std::swap(b(row1), b(row2));
}

bool GaussSolver::forwardElimination() {
    size_t n = A.getRows();

    for (size_t i = 0; i < n; ++i) {
        // Поиск главного элемента (частичный выбор)
        size_t maxRow = i;
        double maxVal = std::abs(A(i, i));

        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(A(k, i)) > maxVal) {
                maxVal = std::abs(A(k, i));
                maxRow = k;
            }
        }

        // Проверка на вырожденность
        if (maxVal < 1e-12) {
            std::cerr << "Ошибка: Матрица вырождена! Решение невозможно." << std::endl;
            return false;
        }

        // Перестановка строк
        if (maxRow != i) {
            swapRows(i, maxRow);
        }

        // Нормализация строки i
        double pivot = A(i, i);
        //for (size_t j = i; j < n; ++j) {
        //    A(i, j) /= pivot;
        //}
        //b(i) /= pivot;

        // Исключение переменной из остальных строк
        for (size_t k = i + 1; k < n; ++k) {
            double factor = A(k, i);
            for (size_t j = i; j < n; ++j) {
                A(k, j) -= factor / pivot * A(i, j);
            }
            b(k) -= factor / pivot * b(i);
        }
    }

    return true;
}

void GaussSolver::backwardSubstitution() {
    size_t n = A.getRows();
    x = Vector(n);

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += A(i, j) * x(j);
        }
        x(i) = (b(i) - sum) / A(i, i);
    }
}

bool GaussSolver::solve() {
    // Сохраняем копии для вычислений
    Matrix A_copy = A;
    Vector b_copy = b;

    // Прямой ход
    if (!forwardElimination()) {
        solutionFound = false;
        return false;
    }

    // Обратный ход
    backwardSubstitution();
    solutionFound = true;
    return true;
}

Vector GaussSolver::getSolution() const {
    return x;
}

Matrix GaussSolver::getMatrix() const {
    return A;
}

Vector GaussSolver::getRightHandSide() const {
    return b;
}

bool GaussSolver::isSolutionFound() const {
    return solutionFound;
}

double GaussSolver::getResidualNorm() const {
    if (!solutionFound) return -1.0;

    Vector residual = A * x;
    residual = residual - b;

    double norm = 0.0;
    for (size_t i = 0; i < residual.getSize(); ++i) {
        norm += residual(i) * residual(i);
    }

    return std::sqrt(norm);
}

bool GaussSolver::verifySolution(double tolerance) const {
    if (!solutionFound) return false;

    Vector Ax = A * x;
    double maxError = 0.0;

    for (size_t i = 0; i < Ax.getSize(); ++i) {
        double error = std::abs(Ax(i) - b(i));
        if (error > maxError) {
            maxError = error;
        }
    }

    return maxError < tolerance;
}

void GaussSolver::printSolution() const {
    if (!solutionFound) {
        std::cout << "Решение не найдено!" << std::endl;
        return;
    }

    std::cout << "\n=== РЕШЕНИЕ СИСТЕМЫ ===" << std::endl;
    for (size_t i = 0; i < x.getSize(); ++i) {
        std::cout << "x[" << i + 1 << "] = " << std::fixed
            << std::setprecision(6) << x(i) << std::endl;
    }
}

void GaussSolver::printSystem() const {
    std::cout << "\n=== СИСТЕМА УРАВНЕНИЙ ===" << std::endl;
    size_t n = A.getRows();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << std::setw(10) << std::setprecision(4)
                << A(i, j) << " * x" << j + 1;
            if (j < n - 1) std::cout << " + ";
        }
        std::cout << " = " << std::setw(10) << std::setprecision(4) << b(i) << std::endl;
    }
}

void GaussSolver::printVerification() const {
    if (!solutionFound) {
        std::cout << "Невозможно выполнить проверку - решение не найдено!" << std::endl;
        return;
    }

    std::cout << "\n=== ПРОВЕРКА РЕШЕНИЯ ===" << std::endl;

    Vector Ax = A * x;
    double maxError = 0.0;

    std::cout << "A*x = [";
    for (size_t i = 0; i < Ax.getSize(); ++i) {
        std::cout << std::fixed << std::setprecision(6) << Ax(i);
        if (i < Ax.getSize() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "b   = [" << b << "]" << std::endl;

    std::cout << "\nПогрешности:" << std::endl;
    for (size_t i = 0; i < Ax.getSize(); ++i) {
        double error = std::abs(Ax(i) - b(i));
        maxError = std::max(maxError, error);
        std::cout << "|(A*x)[" << i + 1 << "] - b[" << i + 1 << "]| = "
            << std::scientific << std::setprecision(6) << error << std::endl;
    }

    std::cout << "\nМаксимальная погрешность: " << std::scientific
        << std::setprecision(6) << maxError << std::endl;

    if (verifySolution()) {
        std::cout << "✓ Решение найдено верно!" << std::endl;
    }
    else {
        std::cout << "✗ Погрешность превышает допустимую!" << std::endl;
    }

    std::cout << "Норма невязки: " << std::scientific
        << std::setprecision(6) << getResidualNorm() << std::endl;
}

GaussSolver GaussSolver::createRandomSystem(size_t n, std::mt19937& rng) {
    Matrix A(n, n);
    Vector b(n);

    A.generateRandom(rng);

    // Генерируем случайное решение и вычисляем правую часть
    Vector x_solution(n);
    x_solution.generateRandom(rng);

    // Вычисляем b = A * x
    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < n; ++j) {
            sum += A(i, j) * x_solution(j);
        }
        b(i) = sum;
    }

    GaussSolver solver(A, b);
    return solver;
}

GaussSolver GaussSolver::createSystemWithKnownSolution(const Vector& knownSolution, std::mt19937& rng) {
    size_t n = knownSolution.getSize();
    Matrix A(n, n);

    // Генерируем невырожденную матрицу
    bool nonSingular = false;
    while (!nonSingular) {
        A.generateRandom(rng);

        // Простая проверка на вырожденность (можно улучшить)
        nonSingular = true;
        for (size_t i = 0; i < n; ++i) {
            if (std::abs(A(i, i)) < 1e-6) {
                nonSingular = false;
                break;
            }
        }
    }

    // Вычисляем правую часть
    Vector b = A * knownSolution;

    return GaussSolver(A, b);
}