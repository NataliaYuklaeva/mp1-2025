#include "Figures.h"
#include <vector>

int main() {
    setlocale(LC_ALL, "Russian");

    // Создание различных фигур
    Cube cube(5.0);
    Parallelepiped parallelepiped(4.0, 5.0, 6.0);
    Prism prism(3.0, 10.0);
    Pyramid pyramid(4.0, 7.0);

    // Использование полиморфизма(добавила после лекции)
    vector<Figure*> figures;
    figures.push_back(&cube);
    figures.push_back(&parallelepiped);
    figures.push_back(&prism);
    figures.push_back(&pyramid);

    cout << "========== ИНФОРМАЦИЯ О ФИГУРАХ ==========" << endl;

    // Вывод информации о каждой фигуре
    for (const auto& fig : figures) {
        fig->printInfo();
    }

    cout << "\n========== ДОПОЛНИТЕЛЬНЫЕ РАСЧЕТЫ ==========" << endl;

    // Изменения параметров куба
    cout << "Изменяем куб с ребром 5 на куб с ребром 3:" << endl;
    cube.setSide(3.0);
    cube.printInfo();

    // Изменения параметров параллелепипеда
    cout << "Изменяем параллелепипед:" << endl;
    parallelepiped.setDimensions(2.0, 3.0, 4.0);
    parallelepiped.printInfo();

    cout << "\n========== МАССИВ ФИГУР РАЗНЫХ ТИПОВ ==========" << endl;
    Figure* figureArray[] = {
        new Cube(2.0),
        new Parallelepiped(1.5, 2.5, 3.5),
        new Prism(2.0, 5.0),
        new Pyramid(3.0, 6.0)
    };

    for (int i = 0; i < 4; i++) {
        cout << "Фигура " << i + 1 << ":" << endl;
        cout << "Название: " << figureArray[i]->getName() << endl;
        cout << "Объем: " << figureArray[i]->getVolume() << endl;
        cout << "Площадь поверхности: " << figureArray[i]->getSurfaceArea() << endl;
        cout << "---" << endl;
        delete figureArray[i];
    }

    cout << "\nПрограмма завершена!" << endl;

    return 0;
}