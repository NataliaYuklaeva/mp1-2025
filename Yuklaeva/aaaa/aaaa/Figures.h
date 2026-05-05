#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Базовый класс Фигуры
class Figure {
protected:
    string name;
public:
    Figure(const string& n = "Figure") : name(n) {}
    virtual ~Figure() {}

    // Чисто виртуальные функции для объема и площади
    virtual double getVolume() const = 0;
    virtual double getSurfaceArea() const = 0;

    // Функция для вывода информации о фигуре
    virtual void printInfo() const {
        cout << "Фигура: " << name << endl;
        cout << "Объем: " << getVolume() << endl;
        cout << "Площадь полной поверхности: " << getSurfaceArea() << endl;
        cout << "------------------------" << endl;
    }

    string getName() const { return name; }
};

// Класс Куб
class Cube : public Figure {
private:
    double side; // длина ребра
public:
    Cube(double s = 1.0);
    virtual double getVolume() const override;
    virtual double getSurfaceArea() const override;
    virtual void printInfo() const override;
    double getSide() const { return side; }
    void setSide(double s) { side = s; }
};

// Класс Параллелепипед
class Parallelepiped : public Figure {
private:
    double length, width, height; //Длина, высота, ширина
public:
    Parallelepiped(double l = 1.0, double w = 1.0, double h = 1.0);
    virtual double getVolume() const override;
    virtual double getSurfaceArea() const override;
    virtual void printInfo() const override;
    double getLength() const { return length; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setDimensions(double l, double w, double h) {
        length = l; width = w; height = h;
    }
};

// Класс Правильная треугольная призма
class Prism : public Figure {
private:
    double baseSide;   // сторона основания
    double height;     // высота призмы
public:
    Prism(double b = 1.0, double h = 1.0);
    virtual double getVolume() const override;
    virtual double getSurfaceArea() const override;
    virtual void printInfo() const override;
    double getBaseSide() const { return baseSide; }
    double getHeight() const { return height; }
    void setParameters(double b, double h) { baseSide = b; height = h; }
};

// Класс Правильная четырехугольная пирамида
class Pyramid : public Figure {
private:
    double baseSide;   // сторона квадратного основания
    double height;     // высота пирамиды
public:
    Pyramid(double b = 1.0, double h = 1.0);
    virtual double getVolume() const override;
    virtual double getSurfaceArea() const override;
    virtual void printInfo() const override;
    double getBaseSide() const { return baseSide; }
    double getHeight() const { return height; }
    void setParameters(double b, double h) { baseSide = b; height = h; }
};

#endif
