/*#include "class_Vector_Matrix.h"
#include <iostream>
#include <random>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 rng(rd());

    std::cout << "=== ТЕСТЫ ВЕКТОРОВ ===" << std::endl;

    // Тест конструкторов векторов
    Vector v1(4);
    Vector v2(4);
    v1.generateRandom(rng);
    v2.generateRandom(rng);

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    // Тест сложения векторов
    Vector v3 = v1 + v2;
    std::cout << "v1 + v2: " << v3 << std::endl;

    // Тест умножения вектора на скаляр
    Vector v4 = v1 * 2.5;
    std::cout << "v1 * 2.5: " << v4 << std::endl;

    // Тест скалярного произведения
    double dotProduct = v1.dot(v2);
    std::cout << "v1 · v2: " << dotProduct << std::endl;

    // Тест префиксного инкремента
    ++v1;
    std::cout << "После ++v1: " << v1 << std::endl;

    // Тест постфиксного инкремента
    Vector v5 = v2++;
    std::cout << "v2++ (оригинальное значение): " << v5 << std::endl;
    std::cout << "v2 после инкремента: " << v2 << std::endl;

    // Тест оператора сравнения
    std::cout << "v1 == v2? " << (v1 == v2 ? "true" : "false") << std::endl;

    // ТЕСТЫ СЕМАНТИКИ ПЕРЕМЕЩЕНИЯ ДЛЯ ВЕКТОРОВ
        std::cout << "\n=== ТЕСТЫ ПЕРЕМЕЩЕНИЯ ДЛЯ ВЕКТОРОВ ===" << std::endl;

    Vector v6(5, 3.14);
    std::cout << "v6 (исходный): " << v6 << std::endl;
    std::cout << "Размер v6: " << v6.getSize() << std::endl;

    // Тест конструктора перемещения
    Vector v7 = std::move(v6);
    std::cout << "v7 (после перемещения из v6): " << v7 << std::endl;
    std::cout << "Размер v6 после перемещения: " << v6.getSize() << std::endl;
    std::cout << "v6 (должен быть пустым): " << v6 << std::endl;

    // Тест перемещающего присваивания
    Vector v8(3, 1.0);
    Vector v9(4, 2.0);
    std::cout << "\nv8 до перемещения: " << v8 << std::endl;
    std::cout << "v9 до перемещения: " << v9 << std::endl;

    v8 = std::move(v9);
    std::cout << "v8 после перемещения из v9: " << v8 << std::endl;
    std::cout << "v9 после перемещения: " << v9 << std::endl;

    std::cout << "\n=== ТЕСТЫ МАТРИЦ ===" << std::endl;

    // Тест конструкторов матриц
    Matrix m1(3, 4);
    Matrix m2(3, 4);
    m1.generateRandom(rng);
    m2.generateRandom(rng);

    std::cout << "Матрица m1 (3x4):" << std::endl;
    std::cout << m1 << std::endl;

    std::cout << "Матрица m2 (3x4):" << std::endl;
    std::cout << m2 << std::endl;

    // Тест сложения матриц
    Matrix m3 = m1 + m2;
    std::cout << "m1 + m2:" << std::endl;
    std::cout << m3 << std::endl;

    // Тест умножения матриц
    Matrix m4(4, 2);
    Matrix m5(2, 3);
    m4.generateRandom(rng);
    m5.generateRandom(rng);

    std::cout << "Матрица m4 (4x2):" << std::endl;
    std::cout << m4 << std::endl;
    std::cout << "Матрица m5 (2x3):" << std::endl;
    std::cout << m5 << std::endl;

    Matrix m6 = m4 * m5;
    std::cout << "m4 * m5 (4x3):" << std::endl;
    std::cout << m6 << std::endl;

    // Тест умножения матрицы на вектор
    Vector vec(4);
    vec.generateRandom(rng);
    std::cout << "Вектор vec: " << vec << std::endl;

    Vector result = m4 * vec;
    std::cout << "m4 * vec: " << result << std::endl;

    // Тест умножения матрицы на скаляр
    Matrix m7 = m1 * 2.0;
    std::cout << "m1 * 2.0:" << std::endl;
    std::cout << m7 << std::endl;

    // Тест префиксного инкремента матрицы
    ++m1;
    std::cout << "После ++m1:" << std::endl;
    std::cout << m1 << std::endl;

    // Тест постфиксного инкремента матрицы
    Matrix m8 = m2++;
    std::cout << "m2++ (оригинальное значение):" << std::endl;
    std::cout << m8 << std::endl;
    std::cout << "m2 после инкремента:" << std::endl;
    std::cout << m2 << std::endl;

    // Тест доступа к элементам через круглые скобки
    std::cout << "Элемент m1(0,0) = " << m1(0, 0) << std::endl;
    m1(0, 0) = 99.99;
    std::cout << "После m1(0,0) = 99.99: " << m1(0, 0) << std::endl;

    // Тест оператора сравнения матриц
    Matrix m9(3, 4, 5.0);
    Matrix m10(3, 4, 5.0);
    std::cout << "m9 == m10? " << (m9 == m10 ? "true" : "false") << std::endl;

    // ТЕСТЫ СЕМАНТИКИ ПЕРЕМЕЩЕНИЯ ДЛЯ МАТРИЦ
    std::cout << "\n=== ТЕСТЫ ПЕРЕМЕЩЕНИЯ ДЛЯ МАТРИЦ ===" << std::endl;

    Matrix m11(2, 2, 7.77);
    std::cout << "m11 (исходная):" << std::endl;
    std::cout << m11 << std::endl;

    // Тест конструктора перемещения для матрицы
    Matrix m12 = std::move(m11);
    std::cout << "m12 (после перемещения из m11):" << std::endl;
    std::cout << m12 << std::endl;
    std::cout << "Размеры m11 после перемещения: " << m11.getRows() << "x" << m11.getCols() << std::endl;

    // Тест перемещающего присваивания для матрицы
    Matrix m13(3, 3, 1.0);
    Matrix m14(2, 2, 2.0);
    std::cout << "\nm13 до перемещения:" << std::endl;
    std::cout << m13 << std::endl;
    std::cout << "m14 до перемещения:" << std::endl;
    std::cout << m14 << std::endl;

    m13 = std::move(m14);
    std::cout << "m13 после перемещения из m14:" << std::endl;
    std::cout << m13 << std::endl;
    std::cout << "Размеры m14 после перемещения: " << m14.getRows() << "x" << m14.getCols() << std::endl;

    return 0;
}*/