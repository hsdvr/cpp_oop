#include <iostream>
using namespace std;
//базовый класс фигура
class Shape {
protected:

	int x{ 0 };
	int y{ 0 };

public:
	Shape() {
		cout << "Shape() object #" << (int)this % 1000 << endl;
	}
	Shape(int x, int y) {
		cout << "Shape(int x, int y) object #" << (int)this % 1000 << endl;
		this->x = x;
		this->y = y;

	}
	Shape(const Shape& sh) : x(sh.x), y(sh.y) {
		cout << "Shape(const shape& sh) object #" << (int)this % 1000 << endl;
	}
	virtual ~Shape() {
		cout << "~Shape() object #" << (int)this % 1000 << endl;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	virtual double getArea() = 0;
};
//класс-наследник точка
class Point : public Shape {

public:
	Point() {
		cout << "Point() object #" << (int)this % 1000 << endl;
	}
	Point(int x, int y) : Shape(x, y) {
		cout << "Point(int x,int y) object #" << (int)this % 1000 << endl;


	}
	Point(const Point& p) : Shape(p) {
		cout << "Point(const Point& p) object #" << (int)this % 1000 << " from object #" << (int)&p % 1000 << endl;
	}
	~Point() {
		cout << "~Point() object #" << (int)this % 1000 << endl;
	}

	double getArea() override {
		return 0;
	}
};
//класс-наследник прямоугольник
class Rectangle : protected Shape {
	int len{ 1 };
	int wid{ 1 };
public:
	Rectangle() : Shape() {
		cout << "Rectangle() object #" << (int)this % 1000 << endl;
	}
	Rectangle(int x, int y, int l, int w) : Shape(x, y), len(l), wid(w) {
		cout << "Rectangle(int x, int y, int l, int w) object #" << (int)this % 1000 << endl;
	}
	Rectangle(const Rectangle& r) : Shape(r), len(r.len), wid(r.wid) {
		cout << "Rectangle(const Rectangle& r) object #" << (int)this % 1000 << "from object #" << (int)this % 1000 << endl;
	}
	~Rectangle() {
		cout << "~Rectangle() object #" << (int)this % 1000 << endl;
	}
	double getArea() override {
		return wid * len;
	}
};
int main() {
	//статическое создание объектов
	{
		Point p1;
		Point p2(1, 2);
		Point p3(p2);
		cout << "area p3 = " << p3.getArea() << endl;
	}
	cout << "--------------\n";
	//динамическое создание объектов
	Rectangle* r1 = new Rectangle();
	Rectangle* r2 = new Rectangle(1, 1, 5, 5);
	Rectangle* r3 = new Rectangle(*r1);
	cout << "area r3 = " << r3->getArea() << endl;
	delete r1;
	delete r2;
	delete r3;
	cout << "---------------\n";
	//помещение объектов в переменные различных типов
	const int size = 10;
	Shape* shapes[size];
	for (int i = 0; i < size; i++)
		shapes[i] = new Point();
	for (int i = 0; i < size; i++)
		delete shapes[i];


	return 0;
}