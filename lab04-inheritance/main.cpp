#include <iostream>
#include <cmath>
#include <clocale>

class eqTriangle { //треугольник равносторонний
private:
	double side; // длина одной стороны, по сути длина всех сторон

public:
	// конструктор по умолчанию
	eqTriangle() : side(0) {};

	//конструктор с параметрами
	eqTriangle(double s) : side(s) {};

	bool triangle_exists() { return side > 0; };

	double calculate_sides() { return side; };
	double calculate_corners() { return 60; };
	double calculate_perimeter() { if (triangle_exists()) { return side * 3; } return 0; };
	double calculate_square() { if (triangle_exists()) { return (sqrt(3) * (side * side)) / 4; } return 0; };

	void print() {
		if (triangle_exists()) {
			std::cout << "\n-----Сведения равностороннего треугольника-----";
			std::cout << "\nСторона = " << calculate_sides();
			std::cout << "\nУгол = " << calculate_corners();
			std::cout << "\nПериметр = " << calculate_perimeter();
			std::cout << "\nПлощадь = " << calculate_square();

		}
		else { std::cout << "Треугольник не существует"; }
	};
};

class Tetrahedron : public eqTriangle { //тетраэдр, построенный на основе треугольника
public:

	// Конструктор - передача сторон в класс
	Tetrahedron(double s) : eqTriangle(s) {}

	double calculate_volume() { if (triangle_exists()) { return (calculate_sides() * calculate_sides() * calculate_sides()) / (6 * sqrt(2)); } return 0; };

	double calculate_square() { if (triangle_exists()) { return sqrt(3) * calculate_sides() * calculate_sides(); }return 0; };

	void print() {
		if (triangle_exists()) {
			std::cout << "\n-----Сведения о тетраэдре-----";
			std::cout << "\nРебро = " << calculate_sides();
			std::cout << "\nОбъём = " << calculate_volume();
			std::cout << "\nПлощадь поверхности = " << calculate_square();

		}
		else { std::cout << "Тетраэдр не существует"; }
	};
};

double average_area_triangle(eqTriangle** triagles, int K);
int find_maximum_area(Tetrahedron** tetrahedrons, int L);

int main() {
	setlocale(LC_ALL, "ru");

	std::cout << "\nВведите количество треугольников: ";
	int K;
	std::cin >> K;
	std::cout << "\nВведите количество тетраэдров: ";
	int L;
	std::cin >> L;

	eqTriangle** triangles = new eqTriangle * [K];
	Tetrahedron** tetrahedrons = new Tetrahedron * [L];

	for (int i = 0; i < K; i++) {
		double side;
		std::cout << "\nВведите длину стороны равностороннего треугольника №" << i + 1 << ": ";
		std::cin >> side;
		triangles[i] = new eqTriangle(side);
	}

	for (int i = 0; i < L; i++) {
		double side;
		std::cout << "\nВведите длину ребра тетраэдра №" << i + 1 << ": ";
		std::cin >> side;
		tetrahedrons[i] = new Tetrahedron(side);
	}

	std::cout << "\nСредняя площадь для " << K << " треугольников = " << average_area_triangle(triangles, K);
	std::cout << "\nСведения о тетраэдре с максимальной площадью: ";
	tetrahedrons[find_maximum_area(tetrahedrons, L)]->print();

	for (int i = 0; i < K; i++) {
		delete triangles[i];
	}
	for (int i = 0; i < L; i++) {
		delete tetrahedrons[i];
	}

	delete[] triangles;
	delete[] tetrahedrons;

	return 0;
};

double average_area_triangle(eqTriangle** triangles, int K) {
	double x = 0;
	for (int i = 0; i < K; i++) {
		x += triangles[i]->calculate_square();
	}
	return x / K;
};
int find_maximum_area(Tetrahedron** tetrahedrons, int L) {
	int max_index = 0;

	double max_sq = tetrahedrons[0]->calculate_square();

	for (int i = 0 + 1; i < L; i++) {
		double current_sq = tetrahedrons[i]->calculate_square();
		if (current_sq > max_sq) {
			max_sq = current_sq;
			max_index = i;
		}
	}
	return max_index;
};
