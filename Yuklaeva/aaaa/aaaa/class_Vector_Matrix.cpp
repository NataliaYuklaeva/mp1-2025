#include "class_Vector_Matrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// ==================== РЕАЛИЗАЦИЯ КЛАССА ВЕКТОР ====================

// Конструктор по умолчанию
Vector::Vector() : data(nullptr), size(0) {}

// Конструктор с размером
Vector::Vector(size_t n) : size(n) {
    data = new double[n]();
}

// Конструктор с размером и значением
Vector::Vector(size_t n, double value) : size(n) {
    data = new double[n];
    for (size_t i = 0; i < n; ++i) {
        data[i] = value;
    }
}

// Конструктор копирования
Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

// Деструктор
Vector::~Vector() {
    delete[] data;
}

// Оператор присваивания
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new double[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

// Оператор доступа по индексу (квадратные скобки)
double& Vector::operator[](size_t index) {
    return data[index];
}

const double& Vector::operator[](size_t index) const {
    return data[index];
}

// Оператор доступа (круглые скобки)
double& Vector::operator()(size_t index) {
    return data[index];
}

const double& Vector::operator()(size_t index) const {
    return data[index];
}

// Оператор сложения с присваиванием
Vector& Vector::operator+=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

// Оператор сложения
Vector Vector::operator+(const Vector& other) const {
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Оператор вычитания с присваиванием
Vector& Vector::operator-=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

// Оператор вычитания
Vector Vector::operator-(const Vector& other) const {
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// Умножение вектора на скаляр
Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

// Дружественная функция для умножения скаляра на вектор
Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
}

// Префиксный инкремент (++x)
Vector& Vector::operator++() {
    for (size_t i = 0; i < size; ++i) {
        data[i] += 1.0;
    }
    return *this;
}

// Постфиксный инкремент (x++)
Vector Vector::operator++(int) {
    Vector temp(*this);
    ++(*this);
    return temp;
}

// Скалярное произведение
double Vector::dot(const Vector& other) const {
    double result = 0.0;
    for (size_t i = 0; i < size; ++i) {
        result += data[i] * other.data[i];
    }
    return result;
}

// Оператор сравнения на равенство
bool Vector::operator==(const Vector& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (std::abs(data[i] - other.data[i]) > 1e-9) return false;
    }
    return true;
}

// Оператор неравенства
bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

// Получение размера
size_t Vector::getSize() const {
    return size;
}

// Генерация случайных элементов
void Vector::generateRandom(std::mt19937& rng) {
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (size_t i = 0; i < size; ++i) {
        data[i] = dist(rng);
    }
}

// Оператор вывода для вектора (ручная реализация)
std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size; ++i) {
        os << std::fixed << std::setprecision(4) << vec.data[i];
        if (i < vec.size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

// ==================== РЕАЛИЗАЦИЯ КЛАССА МАТРИЦА ====================

// Конструктор по умолчанию
Matrix::Matrix() : rows(nullptr), rowsCount(0), colsCount(0) {}

// Конструктор с размерами
Matrix::Matrix(size_t m, size_t n) : rowsCount(m), colsCount(n) {
    rows = new Vector[rowsCount];
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i] = Vector(colsCount);
    }
}

// Конструктор с размерами и значением
Matrix::Matrix(size_t m, size_t n, double value) : rowsCount(m), colsCount(n) {
    rows = new Vector[rowsCount];
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i] = Vector(colsCount, value);
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rowsCount(other.rowsCount), colsCount(other.colsCount) {
    rows = new Vector[rowsCount];
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i] = other.rows[i];
    }
}

Matrix::Matrix(Matrix&& other) noexcept : rows(other.rows), rowsCount(other.rowsCount), colsCount(other.colsCount) {
    other.rows = nullptr;
    other.rowsCount = 0;
    other.colsCount = 0;
}

// Деструктор
Matrix::~Matrix() {
    delete[] rows;
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        delete[] rows;
        rowsCount = other.rowsCount;
        colsCount = other.colsCount;
        rows = new Vector[rowsCount];
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] = other.rows[i];
        }
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        delete[] rows;
        rows = other.rows;
        rowsCount = other.rowsCount;
        colsCount = other.colsCount;
        other.rows = nullptr;
        other.rowsCount = 0;
        other.colsCount = 0;
    }
    return *this;
}

// Доступ к строке через оператор []
Vector& Matrix::operator[](size_t index) {
    return rows[index];
}

const Vector& Matrix::operator[](size_t index) const {
    return rows[index];
}

// Доступ к строке через оператор ()
Vector& Matrix::operator()(size_t index) {
    return rows[index];
}

const Vector& Matrix::operator()(size_t index) const {
    return rows[index];
}

// Доступ к элементу по двум индексам
double& Matrix::operator()(size_t i, size_t j) {
    return rows[i][j];
}

const double& Matrix::operator()(size_t i, size_t j) const {
    return rows[i][j];
}

// Сложение с присваиванием
Matrix& Matrix::operator+=(const Matrix& other) {
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i] += other.rows[i];
    }
    return *this;
}

// Сложение матриц
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rowsCount, colsCount);
    for (size_t i = 0; i < rowsCount; ++i) {
        result.rows[i] = rows[i] + other.rows[i];
    }
    return result;
}

// Вычитание с присваиванием
Matrix& Matrix::operator-=(const Matrix& other) {
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i] -= other.rows[i];
    }
    return *this;
}

// Вычитание матриц
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rowsCount, colsCount);
    for (size_t i = 0; i < rowsCount; ++i) {
        result.rows[i] = rows[i] - other.rows[i];
    }
    return result;
}

// Умножение матриц
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(rowsCount, other.colsCount);
    for (size_t i = 0; i < rowsCount; ++i) {
        for (size_t j = 0; j < other.colsCount; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < colsCount; ++k) {
                sum += rows[i][k] * other.rows[k][j];
            }
            result(i, j) = sum;
        }
    }
    return result;
}

// Умножение матрицы на вектор
Vector Matrix::operator*(const Vector& vec) const {
    Vector result(rowsCount);
    for (size_t i = 0; i < rowsCount; ++i) {
        result[i] = rows[i].dot(vec);
    }
    return result;
}

// Умножение матрицы на скаляр
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rowsCount, colsCount);
    for (size_t i = 0; i < rowsCount; ++i) {
        result.rows[i] = rows[i] * scalar;
    }
    return result;
}

// Дружественная функция для умножения скаляра на матрицу
Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}

// Префиксный инкремент матрицы
Matrix& Matrix::operator++() {
    for (size_t i = 0; i < rowsCount; ++i) {
        ++rows[i];
    }
    return *this;
}

// Постфиксный инкремент матрицы
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}

// Сравнение матриц
bool Matrix::operator==(const Matrix& other) const {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount) return false;
    for (size_t i = 0; i < rowsCount; ++i) {
        if (rows[i] != other.rows[i]) return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

size_t Matrix::getRows() const {
    return rowsCount;
}

size_t Matrix::getCols() const {
    return colsCount;
}

void Matrix::generateRandom(std::mt19937& rng) {
    for (size_t i = 0; i < rowsCount; ++i) {
        rows[i].generateRandom(rng);
    }
}

// Оператор вывода для матрицы (ручная реализация)
std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (size_t i = 0; i < mat.rowsCount; ++i) {
        os << mat.rows[i];
        if (i < mat.rowsCount - 1) {
            os << std::endl;
        }
    }
    return os;
}