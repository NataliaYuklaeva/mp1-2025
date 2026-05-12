#ifndef SHABLON_H
#define SHABLON_H

#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

template<typename miumiu>
class Vector {
private:
    miumiu* data;
    size_t size;

public:
    Vector() : data(nullptr), size(0) {}

    Vector(size_t n) : size(n) {
        data = new miumiu[n]();
    }

    Vector(size_t n, miumiu value) : size(n) {
        data = new miumiu[n];
        for (size_t i = 0; i < n; ++i) {
            data[i] = value;
        }
    }

    Vector(const Vector& other) : size(other.size) {
        data = new miumiu[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new miumiu[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    miumiu& operator[](size_t index) {
        return data[index];
    }

    const miumiu& operator[](size_t index) const {
        return data[index];
    }

    miumiu& operator()(size_t index) {
        return data[index];
    }

    const miumiu& operator()(size_t index) const {
        return data[index];
    }

    Vector& operator+=(const Vector& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    Vector operator+(const Vector& other) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector& operator-=(const Vector& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    Vector operator-(const Vector& other) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    Vector operator*(double scalar) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    friend Vector operator*(miumiu scalar, const Vector& vec) {
        return vec * scalar;
    }

    Vector& operator++() {
        for (size_t i = 0; i < size; ++i) {
            data[i] += 1.0;
        }
        return *this;
    }

    Vector operator++(int) {
        Vector temp(*this);
        ++(*this);
        return temp;
    }

    miumiu dot(const Vector& other) const {
        miumiu result = 0.0;
        for (size_t i = 0; i < size; ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (std::abs(data[i] - other.data[i]) > 1e-9) return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    size_t getSize() const {
        return size;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            os << std::fixed << std::setprecision(4) << vec.data[i];
            if (i < vec.size - 1) {
                os << "  ";
            }
        }
        return os;
    }
};

template<typename miumiu>
class Matrix {
private:
    Vector<miumiu>* rows;
    size_t rowsCount;
    size_t colsCount;

public:
    Matrix() : rows(nullptr), rowsCount(0), colsCount(0) {}

    Matrix(size_t m, size_t n) : rowsCount(m), colsCount(n) {
        rows = new Vector<miumiu>[rowsCount];
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] = Vector<miumiu>(colsCount);
        }
    }

    Matrix(size_t m, size_t n, miumiu value) : rowsCount(m), colsCount(n) {
        rows = new Vector<miumiu>[rowsCount];
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] = Vector<miumiu>(colsCount, value);
        }
    }

    Matrix(const Matrix& other) : rowsCount(other.rowsCount), colsCount(other.colsCount) {
        rows = new Vector<miumiu>[rowsCount];
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] = other.rows[i];
        }
    }

    Matrix(Matrix&& other) noexcept : rows(other.rows), rowsCount(other.rowsCount), colsCount(other.colsCount) {
        other.rows = nullptr;
        other.rowsCount = 0;
        other.colsCount = 0;
    }

    ~Matrix() {
        delete[] rows;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] rows;
            rowsCount = other.rowsCount;
            colsCount = other.colsCount;
            rows = new Vector<miumiu>[rowsCount];
            for (size_t i = 0; i < rowsCount; ++i) {
                rows[i] = other.rows[i];
            }
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) noexcept {
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

    Vector<miumiu>& operator[](size_t index) {
        return rows[index];
    }

    const Vector<miumiu>& operator[](size_t index) const {
        return rows[index];
    }

    Vector<miumiu>& operator()(size_t index) {
        return rows[index];
    }

    const Vector<miumiu>& operator()(size_t index) const {
        return rows[index];
    }

    miumiu& operator()(size_t i, size_t j) {
        return rows[i][j];
    }

    const miumiu& operator()(size_t i, size_t j) const {
        return rows[i][j];
    }

    Matrix& operator+=(const Matrix& other) {
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] += other.rows[i];
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < rowsCount; ++i) {
            result.rows[i] = rows[i] + other.rows[i];
        }
        return result;
    }

    Matrix& operator-=(const Matrix& other) {
        for (size_t i = 0; i < rowsCount; ++i) {
            rows[i] -= other.rows[i];
        }
        return *this;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < rowsCount; ++i) {
            result.rows[i] = rows[i] - other.rows[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rowsCount, other.colsCount);
        for (size_t i = 0; i < rowsCount; ++i) {
            for (size_t j = 0; j < other.colsCount; ++j) {
                miumiu sum = 0;
                for (size_t k = 0; k < colsCount; ++k) {
                    sum += rows[i][k] * other.rows[k][j];
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Vector<miumiu> operator*(const Vector<miumiu>& vec) const {
        Vector<miumiu> result(rowsCount);
        for (size_t i = 0; i < rowsCount; ++i) {
            result[i] = rows[i].dot(vec);
        }
        return result;
    }

    Matrix operator*(miumiu scalar) const {
        Matrix result(rowsCount, colsCount);
        for (size_t i = 0; i < rowsCount; ++i) {
            result.rows[i] = rows[i] * scalar;
        }
        return result;
    }

    friend Matrix operator*(miumiu scalar, const Matrix& mat) {
        return mat * scalar;
    }

    Matrix& operator++() {
        for (size_t i = 0; i < rowsCount; ++i) {
            ++rows[i];
        }
        return *this;
    }

    Matrix operator++(int) {
        Matrix temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const Matrix& other) const {
        if (rowsCount != other.rowsCount || colsCount != other.colsCount) return false;
        for (size_t i = 0; i < rowsCount; ++i) {
            if (rows[i] != other.rows[i]) return false;
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    size_t getRows() const {
        return rowsCount;
    }

    size_t getCols() const {
        return colsCount;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (size_t i = 0; i < mat.rowsCount; ++i) {
            os << mat.rows[i];
            if (i < mat.rowsCount - 1) {
                os << std::endl;
            }
        }
        return os;
    }
};

#endif