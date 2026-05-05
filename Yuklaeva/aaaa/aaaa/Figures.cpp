#include "Figures.h"

// Реализация методов класса Cube
Cube::Cube(double s) : Figure("Cube"), side(s) {
    if (side <= 0) side = 1.0;
}

double Cube::getVolume() const {
    return side * side * side;
}

double Cube::getSurfaceArea() const {
    return 6 * side * side;
}

void Cube::printInfo() const {
    cout << "Фигура: " << name << endl;
    cout << "Длина ребра: " << side << endl;
    cout << "Объем: " << getVolume() << endl;
    cout << "Площадь полной поверхности: " << getSurfaceArea() << endl;
    cout << "------------------------" << endl;
}

// Реализация методов класса Parallelepiped
Parallelepiped::Parallelepiped(double l, double w, double h)
    : Figure("Parallelepiped"), length(l), width(w), height(h) {
    if (length <= 0) length = 1.0;
    if (width <= 0) width = 1.0;
    if (height <= 0) height = 1.0;
}

double Parallelepiped::getVolume() const {
    return length * width * height;
}

double Parallelepiped::getSurfaceArea() const {
    return 2 * (length * width + length * height + width * height);
}

void Parallelepiped::printInfo() const {
    cout << "Фигура: " << name << endl;
    cout << "Длина: " << length << ", Ширина: " << width
        << ", Высота: " << height << endl;
    cout << "Объем: " << getVolume() << endl;
    cout << "Площадь полной поверхности: " << getSurfaceArea() << endl;
    cout << "------------------------" << endl;
}

// Реализация методов класса Prism
Prism::Prism(double b, double h) : Figure("Triangular Prism"), baseSide(b), height(h) {
    if (baseSide <= 0) baseSide = 1.0;
    if (height <= 0) height = 1.0;
}

double Prism::getVolume() const {
    // Площадь равностороннего треугольника
    double baseArea = (sqrt(3.0) / 4.0) * baseSide * baseSide;
    return baseArea * height;
}

double Prism::getSurfaceArea() const {
    // Площадь двух оснований + площадь трех боковых граней
    double baseArea = (sqrt(3.0) / 4.0) * baseSide * baseSide;
    double lateralArea = 3 * baseSide * height;
    return 2 * baseArea + lateralArea;
}

void Prism::printInfo() const {
    cout << "Фигура: " << name << endl;
    cout << "Сторона основания: " << baseSide << ", Высота призмы: " << height << endl;
    cout << "Объем: " << getVolume() << endl;
    cout << "Площадь полной поверхности: " << getSurfaceArea() << endl;
    cout << "------------------------" << endl;
}

// Реализация методов класса Pyramid
Pyramid::Pyramid(double b, double h) : Figure("Square Pyramid"), baseSide(b), height(h) {
    if (baseSide <= 0) baseSide = 1.0;
    if (height <= 0) height = 1.0;
}

double Pyramid::getVolume() const {
    double baseArea = baseSide * baseSide;
    return (baseArea * height) / 3.0;
}

double Pyramid::getSurfaceArea() const {
    double baseArea = baseSide * baseSide;
    // Апофема (высота боковой грани)
    double slantHeight = sqrt(height * height + (baseSide / 2.0) * (baseSide / 2.0));
    double lateralArea = 4 * (0.5 * baseSide * slantHeight);
    return baseArea + lateralArea;
}

void Pyramid::printInfo() const {
    cout << "Фигура: " << name << endl;
    cout << "Сторона основания: " << baseSide << ", Высота пирамиды: " << height << endl;
    cout << "Объем: " << getVolume() << endl;
    cout << "Площадь полной поверхности: " << getSurfaceArea() << endl;
    cout << "------------------------" << endl;
}