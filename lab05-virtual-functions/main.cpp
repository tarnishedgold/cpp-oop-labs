#include <iostream>
#include <cmath>
#include <string>
#include <clocale>

//родительский класс - равносторонний треугольник
class eqTriangle {
protected:
    double side;
    std::string name;

public:
    eqTriangle() : side(0), name("Равносторонний треугольник") {}
    eqTriangle(double s) : side(s), name("Равносторонний треугольник") {}

    virtual ~eqTriangle() {}

    virtual bool exists() { return side > 0; }

    virtual double get_side() { return side; }

    virtual double calculate_perimeter() {
        if (exists()) {
            return side * 3;
        }
        return 0;
    }

    virtual double calculate_area() {
        if (exists()) {
            return (std::sqrt(3) * side * side) / 4.0;
        }
        return 0;
    }

    virtual double calculate_volume() { return 0; }

    virtual std::string get_name() { return name; }

    virtual void print() {
        if (exists()) {
            std::cout << "\n----- " << name << " -----";
            std::cout << "\nСторона: " << get_side();
            std::cout << "\nПериметр: " << calculate_perimeter();
            std::cout << "\nПлощадь: " << calculate_area();
        }
        else {
            std::cout << "Фигура не существует";
        }
    }
};

// Класс тетраэдр (пирамида с треугольным основанием)
class Tetrahedron : public eqTriangle {
public:
    Tetrahedron() : eqTriangle() {
        name = "Тетраэдр";
    }

    Tetrahedron(double s) : eqTriangle(s) {
        name = "Тетраэдр";
    }

    double calculate_area() override {
        if (exists()) {
            return std::sqrt(3) * side * side;
        }
        return 0;
    }

    double calculate_volume() override {
        if (exists()) {
            return (side * side * side) / (6.0 * std::sqrt(2));
        }
        return 0;
    }

    void print() override {
        if (exists()) {
            std::cout << "\n----- " << name << " -----";
            std::cout << "\nРебро: " << get_side();
            std::cout << "\nПлощадь поверхности: " << calculate_area();
            std::cout << "\nОбъем: " << calculate_volume();
        }
        else {
            std::cout << "Тетраэдр не существует";
        }
    }
};

// Класс правильная треугольная призма
class TriangularPrism : public eqTriangle {
private:
    double height;

public:
    TriangularPrism() : eqTriangle(), height(0) {
        name = "Правильная треугольная призма";
    }

    TriangularPrism(double s, double h) : eqTriangle(s), height(h) {
        name = "Правильная треугольная призма";
    }

    double calculate_area() override {
        if (exists()) {
            double base_area = (std::sqrt(3) * side * side) / 4.0;
            double lateral_area = 3 * side * height;
            return 2 * base_area + lateral_area;
        }
        return 0;
    }

    double calculate_volume() override {
        if (exists()) {
            double base_area = (std::sqrt(3) * side * side) / 4.0;
            return base_area * height;
        }
        return 0;
    }

    void print() override {
        if (exists()) {
            std::cout << "\n----- " << name << " -----";
            std::cout << "\nСторона основания: " << get_side();
            std::cout << "\nВысота: " << height;
            std::cout << "\nПлощадь поверхности: " << calculate_area();
            std::cout << "\nОбъем: " << calculate_volume();
        }
        else {
            std::cout << "Призма не существует";
        }
    }
};

// Класс треугольная бипирамида (две пирамиды сложенные основаниями)
class TriangularBipyramid : public eqTriangle {
private:
    double pyramid_height;  // высота каждой пирамиды от основания до вершины

public:
    TriangularBipyramid() : eqTriangle(), pyramid_height(0) {
        name = "Треугольная бипирамида";
    }

    TriangularBipyramid(double s, double h) : eqTriangle(s), pyramid_height(h) {
        name = "Треугольная бипирамида";
    }

    double calculate_area() override {
        if (exists()) {
            // У бипирамиды 6 треугольных граней одинаковой площади
            // Высота треугольника = sqrt(pyramid_height^2 + (сторона/2√3)^2)
            double triangle_height = std::sqrt(pyramid_height * pyramid_height +
                (side / (2 * std::sqrt(3))) * (side / (2 * std::sqrt(3))));
            double one_triangle_area = (side * triangle_height) / 2.0;
            return 6 * one_triangle_area;
        }
        return 0;
    }

    double calculate_volume() override {
        if (exists()) {
            double base_area = (std::sqrt(3) * side * side) / 4.0;
            // Объем = 2 * объем одной пирамиды
            return 2 * ((base_area * pyramid_height) / 3.0);
        }
        return 0;
    }

    void print() override {
        if (exists()) {
            std::cout << "\n----- " << name << " -----";
            std::cout << "\nСторона основания: " << get_side();
            std::cout << "\nВысота пирамиды: " << pyramid_height;
            std::cout << "\nПлощадь поверхности: " << calculate_area();
            std::cout << "\nОбъем: " << calculate_volume();
        }
        else {
            std::cout << "Бипирамида не существует";
        }
    }
};

// Функция для вычисления средней площади только равносторонних треугольников
double calculate_average_triangle_area(eqTriangle** figures, int total_count, int triangle_count) {
    if (triangle_count == 0) return 0;

    double total_triangle_area = 0;
    int count = 0;

    for (int i = 0; i < total_count; i++) {
        // Проверяем, является ли фигура простым треугольником (не объемной фигурой)
        if (figures[i]->get_name() == "Равносторонний треугольник") {
            total_triangle_area += figures[i]->calculate_area();
            count++;
        }
    }

    return total_triangle_area / count;
}

// Функция для поиска фигуры с максимальной площадью
void find_max_area_figure(eqTriangle** figures, int total_count) {
    if (total_count == 0) {
        std::cout << "\nНет фигур для поиска максимальной площади";
        return;
    }

    int max_index = 0;
    double max_area = figures[0]->calculate_area();

    for (int i = 1; i < total_count; i++) {
        double current_area = figures[i]->calculate_area();
        if (current_area > max_area) {
            max_area = current_area;
            max_index = i;
        }
    }

    std::cout << "\n\n=== ФИГУРА С МАКСИМАЛЬНОЙ ПЛОЩАДЬЮ ===";
    std::cout << "\nТип фигуры: " << figures[max_index]->get_name();
    std::cout << "\nМаксимальная площадь: " << max_area;
    std::cout << "\nПодробная информация о фигуре:";
    figures[max_index]->print();
}

int main() {
    std::setlocale(LC_ALL, "ru");

    std::cout << "Введите количество треугольников: ";
    int K;
    std::cin >> K;

    std::cout << "Введите количество тетраэдров: ";
    int L;
    std::cin >> L;

    std::cout << "Введите количество треугольных призм: ";
    int M;
    std::cin >> M;

    std::cout << "Введите количество треугольных бипирамид: ";
    int N;
    std::cin >> N;

    // общий массив указателей на базовый/родительский класс
    int total_figures = K + L + M + N;
    eqTriangle** all_figures = new eqTriangle * [total_figures];
    int index = 0;

    for (int i = 0; i < K; i++) {
        double side;
        std::cout << "\nВведите длину стороны треугольника №" << i + 1 << ": ";
        std::cin >> side;
        all_figures[index++] = new eqTriangle(side);
    }

    for (int i = 0; i < L; i++) {
        double side;
        std::cout << "\nВведите длину ребра тетраэдра №" << i + 1 << ": ";
        std::cin >> side;
        all_figures[index++] = new Tetrahedron(side);
    }

    for (int i = 0; i < M; i++) {
        double side, height;
        std::cout << "\nВведите сторону основания и высоту призмы №" << i + 1 << ": ";
        std::cin >> side >> height;
        all_figures[index++] = new TriangularPrism(side, height);
    }

    for (int i = 0; i < N; i++) {
        double side, height;
        std::cout << "\nВведите сторону основания и высоту пирамиды для бипирамиды №" << i + 1 << ": ";
        std::cin >> side >> height;
        all_figures[index++] = new TriangularBipyramid(side, height);
    }

    // Вывод информации
    std::cout << "\n\n ----- все фигуры -----";
    for (int i = 0; i < total_figures; i++) {
        all_figures[i]->print();
    }

    // Вычисление и вывод средней площади треугольников
    double avg_triangle_area = calculate_average_triangle_area(all_figures, total_figures, K);
    std::cout << "\n\n=== СРЕДНЯЯ ПЛОЩАДЬ ТРЕУГОЛЬНИКОВ ===";
    std::cout << "\nКоличество треугольников: " << K;
    std::cout << "\nСредняя площадь: " << avg_triangle_area;

    find_max_area_figure(all_figures, total_figures);

    for (int i = 0; i < total_figures; i++) {
        delete all_figures[i];
    }
    delete[] all_figures;

    return 0;
}
