#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <clocale>

class Vector {
private:
    int size;
    double* data;

public:
    // Конструктор по умолчанию
    Vector() : size(0), data(nullptr) {}

    // Конструктор с заданным размером (инициализация нулями)
    explicit Vector(int n) : size(n) {
        data = new double[size]();
    }

    // Конструктор копирования
    Vector(const Vector& other) : size(other.size) {
        data = new double[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Оператор присваивания копированием
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new double[size];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
        }
        return *this;
    }

    void generateRandom(int n, std::mt19937& gen, double min = 1.0, double max = 10.0) {
        delete[] data;
        size = n;
        data = new double[size];
        std::uniform_real_distribution<> dis(min, max);
        for (int i = 0; i < size; ++i)
            data[i] = dis(gen);
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "\n";
    }
};

class Matrix {
private:
    int rows, cols;
    double** data;

public:
    // Конструктор по умолчанию
    Matrix() : rows(0), cols(0), data(nullptr) {}

    // Конструктор с заданным размером (инициализация нулями)
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols]();
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
        }
    }

    // Конструктор перемещения
    Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(other.data) {
        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            data = new double* [rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; ++j)
                    data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            data = other.data;

            other.rows = 0;
            other.cols = 0;
            other.data = nullptr;
        }
        return *this;
    }

    void generateRandom(int r, int c, std::mt19937& gen, double min = 1.0, double max = 10.0) {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;

        rows = r;
        cols = c;
        data = new double* [rows];
        std::uniform_real_distribution<> dis(min, max);
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j)
                data[i][j] = dis(gen);
        }
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                std::cout << data[i][j]      << " ";
            std::cout << "\n";
        }
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

    Vector v1(5);
    v1.generateRandom(5, gen);
    std::cout << "Вектор:\n";
    v1.print();

    Matrix m1(3, 4);
    m1.generateRandom(3, 4, gen);
    std::cout << "Матрица:\n";
    m1.print();

    return 0;
}