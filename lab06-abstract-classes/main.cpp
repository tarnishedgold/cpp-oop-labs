#include <iostream>
#include <cmath>
#include <clocale>

class Figure {
protected:
    double centerX, centerY;
public:
    Figure(double x, double y) : centerX(x), centerY(y) {}
    virtual ~Figure() {}

    virtual double lateralSurfaceArea() const = 0;
    virtual double volume() const = 0;
    virtual void scale(double factor) = 0;
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
};

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.print(os);
    return os;
}

class TriangularPrism : public Figure {
private:
    double baseSide;
    double height;
public:
    TriangularPrism(double x, double y, double side, double h)
        : Figure(x, y), baseSide(side), height(h) {
    }

    double lateralSurfaceArea() const override {
        return 3 * baseSide * height;
    }

    double volume() const override {
        double baseArea = (std::sqrt(3) / 4) * baseSide * baseSide;
        return baseArea * height;
    }

    void scale(double factor) override {
        baseSide *= factor;
        height *= factor;
    }

    void print(std::ostream& os) const override {
        os << "Треугольная призма:\n";
        os << "  Построена вокруг центра: (" << centerX << ", " << centerY << ")\n";
        os << "  Сторона основания: " << baseSide << "\n";
        os << "  Высота: " << height << "\n";
        os << "  Вершины основания:\n";

        double R = baseSide / std::sqrt(3);  // расстояние от центра до вершин

        os << "    Вершина 1: (" << centerX << ", " << centerY + R << ")\n";
        os << "    Вершина 2: (" << centerX - baseSide / 2 << ", " << centerY - R / 2 << ")\n";
        os << "    Вершина 3: (" << centerX + baseSide / 2 << ", " << centerY - R / 2 << ")\n";

        os << "  Площадь боковой поверхности: " << lateralSurfaceArea() << "\n";
        os << "  Объем: " << volume() << "\n";
    }
};

class QuadrangularPyramid : public Figure {
private:
    double baseSide;
    double height;
public:
    QuadrangularPyramid(double x, double y, double side, double h)
        : Figure(x, y), baseSide(side), height(h) {
    }

    double lateralSurfaceArea() const override {
        double apothem = std::sqrt(height * height + (baseSide / 2) * (baseSide / 2));
        double triangleArea = 0.5 * baseSide * apothem;
        return 4 * triangleArea;
    }

    double volume() const override {
        double baseArea = baseSide * baseSide;
        return (1.0 / 3.0) * baseArea * height;
    }

    void scale(double factor) override {
        baseSide *= factor;
        height *= factor;
    }

    void print(std::ostream& os) const override {
        os << "Четырехугольная пирамида:\n";
        os << "  Построена вокруг центра: (" << centerX << ", " << centerY << ")\n";
        os << "  Сторона основания: " << baseSide << "\n";
        os << "  Высота: " << height << "\n";
        os << "  Вершины основания:\n";

        double halfSide = baseSide / 2;
        os << "    Вершина 1: (" << centerX - halfSide << ", " << centerY - halfSide << ")\n";
        os << "    Вершина 2: (" << centerX + halfSide << ", " << centerY - halfSide << ")\n";
        os << "    Вершина 3: (" << centerX + halfSide << ", " << centerY + halfSide << ")\n";
        os << "    Вершина 4: (" << centerX - halfSide << ", " << centerY + halfSide << ")\n";
        os << "    Вершина пирамиды: прямо над центром на высоте " << height << "\n";

        os << "  Площадь боковой поверхности: " << lateralSurfaceArea() << "\n";
        os << "  Объем: " << volume() << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    // Ввод центра и параметров треугольной призмы
    double x1, y1, side1, height1;
    std::cout << "Введите данные для треугольной призмы:\n";
    std::cout << "Центр основания (x y): ";
    std::cin >> x1 >> y1;
    std::cout << "Сторона треугольника: ";
    std::cin >> side1;
    std::cout << "Высота призмы: ";
    std::cin >> height1;

    // Ввод центра и параметров пирамиды
    double x2, y2, side2, height2;
    std::cout << "\nВведите данные для четырехугольной пирамиды:\n";
    std::cout << "Центр основания (x y): ";
    std::cin >> x2 >> y2;
    std::cout << "Сторона квадрата: ";
    std::cin >> side2;
    std::cout << "Высота пирамиды: ";
    std::cin >> height2;

    // Масштабирование
    double scaleFactor;
    std::cout << "\nКоэффициент масштабирования: ";
    std::cin >> scaleFactor;

    // Создание фигур
    Figure* figures[2];
    figures[0] = new TriangularPrism(x1, y1, side1, height1);
    figures[1] = new QuadrangularPyramid(x2, y2, side2, height2);

    // Вывод
    std::cout << "\n=== ПОСТРОЕНИЕ ФИГУР ===\n";
    for (int i = 0; i < 2; i++) {
        std::cout << *figures[i] << "\n";
    }

    // Масштабирование
    for (int i = 0; i < 2; i++) {
        figures[i]->scale(scaleFactor);
    }

    std::cout << "=== ПОСЛЕ МАСШТАБИРОВАНИЯ ===\n";
    for (int i = 0; i < 2; i++) {
        std::cout << *figures[i] << "\n";
    }

    for (int i = 0; i < 2; i++) {
        delete figures[i];
    }

    return 0;
}
