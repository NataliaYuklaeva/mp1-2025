#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <iostream>
#include <random>

class Vector {
private:
    double* data;
    size_t size;

public:
    // Constructors
    Vector();
    Vector(size_t n);
    Vector(size_t n, double value);
    Vector(const Vector& other);  // Copy constructor

    // Destructor
    ~Vector();

    // Assignment operator
    Vector& operator=(const Vector& other);

    // Element access
    double& operator[](size_t index);
    const double& operator[](size_t index) const;
    double& operator()(size_t index);
    const double& operator()(size_t index) const;

    // Arithmetic operators
    Vector& operator+=(const Vector& other);
    Vector operator+(const Vector& other) const;
    Vector& operator-=(const Vector& other);
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    friend Vector operator*(double scalar, const Vector& vec);

    // Increment operators
    Vector& operator++();  // Prefix
    Vector operator++(int);  // Postfix

    // Scalar product
    double dot(const Vector& other) const;

    // Equality
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    // Utility functions
    size_t getSize() const;
    void generateRandom(std::mt19937& rng);

    // Friend operator for output
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};

class Matrix {
private:
    Vector* rows;
    size_t rowsCount;
    size_t colsCount;

public:
    // Constructors
    Matrix();
    Matrix(size_t m, size_t n);
    Matrix(size_t m, size_t n, double value);
    Matrix(const Matrix& other);  // Copy constructor

    // Destructor
    ~Matrix();

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    // Element access
    Vector& operator[](size_t index);
    const Vector& operator[](size_t index) const;
    Vector& operator()(size_t index);
    const Vector& operator()(size_t index) const;
    double& operator()(size_t i, size_t j);
    const double& operator()(size_t i, size_t j) const;

    // Arithmetic operators
    Matrix& operator+=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix& operator-=(const Matrix& other);
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& vec) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& mat);

    // Increment operators
    Matrix& operator++();  // Prefix
    Matrix operator++(int);  // Postfix

    // Equality
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    // Utility functions
    size_t getRows() const;
    size_t getCols() const;
    void generateRandom(std::mt19937& rng);

    // Friend operator for output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};

#endif