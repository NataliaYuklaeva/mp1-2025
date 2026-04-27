#ifndef RECTANGLE
#define RECTANGLE
#include <functional>
#include <vector>
#include <string>

// Перечисление для типов метода прямоугольников
enum class RectangleType {
    LEFT,      // Левые прямоугольники
    RIGHT,     // Правые прямоугольники
    MIDDLE     // Средние прямоугольники
};

class RectangleIntegrator {
private:
    std::function<double(double)> func;  // Интегрируемая функция
    double a;                             // Нижний предел
    double b;                             // Верхний предел
    int n;                                // Количество разбиений

    // Вспомогательные методы
    double integrateLeft() const;
    double integrateRight() const;
    double integrateMiddle() const;

public:
    // Конструкторы
    RectangleIntegrator();
    RectangleIntegrator(const std::function<double(double)>& f, double lower, double upper, int partitions);

    // Методы установки параметров
    void setFunction(const std::function<double(double)>& f);
    void setLimits(double lower, double upper);
    void setPartitions(int partitions);

    // Основной метод интегрирования (статический)
    static double integrate(const std::function<double(double)>& func,
        double a, double b,
        int n,
        RectangleType type = RectangleType::MIDDLE);

    // Нестатический метод интегрирования
    double integrate(RectangleType type = RectangleType::MIDDLE) const;

    // Метод для оценки погрешности (метод Рунге)
    double estimateError(double tolerance = 1e-6, RectangleType type = RectangleType::MIDDLE) const;

    // Метод для получения информации об интегрировании
    void printInfo(RectangleType type = RectangleType::MIDDLE) const;

    // Метод для получения промежуточных результатов (для анализа сходимости)
    std::vector<std::pair<int, double>> getConvergenceHistory(int maxPartitions = 1000,
        RectangleType type = RectangleType::MIDDLE) const;

    // Геттеры
    std::function<double(double)> getFunction() const;
    double getLowerLimit() const;
    double getUpperLimit() const;
    int getPartitions() const;
};

#endif