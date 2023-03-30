#include <iostream>
using namespace std;
//базовый абстрактный класс фигура
class Shape {
private:

protected:
	string color{"black"};

public:
	Shape(){
		cout << "Shape() object #" << (int)this % 1000 << endl;
	}
	Shape(string color) {
		cout << "Shape(string color) object #" << (int)this % 1000 << endl;
		this->color = color;

	}
	Shape(const Shape& sh) : color(sh.color){
		cout << "Shape(const shape& sh) object #" << (int)this % 1000 << " from object #" << (int)this % 1000 << endl;
	}
	virtual ~Shape() {
		cout << "~Shape() object #" << (int)this % 1000 << endl;
	}
	void setColor(string c) {
		color = c;
	}
	void print() {
		cout << color << endl;
	}
	virtual float getArea() = 0;
};
//класс-потомок точка
class Point : public Shape {
private:
	int x;
	int y;
public:
	
	Point():x(0),y(0) {
		cout << "Point() object #" << (int)this % 1000 << endl;
	}
	Point(int x, int y) {
		cout << "Point(int x, int y) object #" << (int)this % 1000 << endl;
		this->x = x;
		this->y = y;
	}
	Point(int x, int y, string c) : Shape(c) {
		cout << "Point(int x,int y, string c) object #" << (int)this % 1000 << endl;
		this->x = x;
		this->y = y;
		
	}
	Point(const Point& p) : Shape(p),x(p.x),y(p.y) {
		cout << "Point(const Point& p) object #" << (int)this % 1000 << " from object #" << (int)&p % 1000 << endl;
	}
	~Point() {
		cout << "~Point() object #" << (int)this % 1000 << endl;
	}

	void print() {
		Shape::print();
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
	}
	float getArea() override {
		return 0;
	}
};
//класс-потомок прямоугольник
class Rectangle : protected Shape {
	int len{ 1 };
	int wid{ 1 };
	Point p1;
	Point p2;
	Point p3;
	Point p4;
public:
	Rectangle():p1(0,7), p2(0,1),p3(1,1), p4(1,0) {
		cout << "Rectangle() object #" << (int)this % 1000 << endl;
		
	}
	Rectangle(int l, int w, string c) : Shape(c), len(l), wid(w), p1(0, 7), p2(0, 1), p3(1, 1), p4(1, 0) {
		cout << "Rectangle(int length, int width, string color) object #" << (int)this % 1000 << endl;
	}
	Rectangle(const Rectangle& r) : Shape(r), len(r.len), wid(r.wid), p1(r.p1),p2(r.p2),p3(r.p3),p4(r.p4) {
		cout << "Rectangle(const Rectangle& r) object #" << (int)this % 1000 << " from object #" << (int)this % 1000 << endl;
	}
	~Rectangle() {
		cout << "~Rectangle() object #" << (int)this % 1000 << endl;
	}
	void print() {
		Shape::print();
	}
	float getArea() override {
		return wid * len;
	}
};

//класс-потомок треугольник
class Circle: private Shape {
private:
	int radius{ 1 };
	Point* loc;
public:
	Circle(): Shape() {
		cout << "Circle() object #" << (int)this % 1000 << endl;
		loc = new Point(0, 0);
	}
	Circle(int rad, Point* p, string c):Shape(c),radius(rad),loc(p) {
		cout << "Circle(int rad, Point* p, string c) object #" << (int)this % 1000 << endl;
	}
	Circle(const Circle& circl):Shape(circl),radius(circl.radius) {
		cout << "Circle(const Circle& circl) object #" << (int)this % 1000 << " from object #" << (int)&circl % 1000 << endl;
		loc = new Point(*circl.loc);
	}
	~Circle() {
		cout << "~Circle() object #" << (int)this % 1000 << endl;
		delete loc;
	}
	float getArea() {
		return 3, 14 * radius * radius;
	}
	void print() {
		Shape::print();
		cout << "radius = " << radius << endl;

	}
};
int main() {
	setlocale(LC_ALL, "ru");
	cout << "статическое создание объектов" << endl;
	{
		Point p1;
		Point p2(1, 2);
		Point p3(1, 4, "red");
		Point p4(p2);
		cout << "area p3 = " << p3.getArea() << endl;
	}
	cout << "--------------\n";
	cout << "динамическое создание объектов; композиция: атрибутом класса Rectangle является другой объект класса Point" << endl;
	Rectangle* r1 = new Rectangle();
	cout  << endl;
	Rectangle* r2 = new Rectangle(1, 5, "yellow");
	cout << endl;
	Rectangle* r3 = new Rectangle(*r1);
	cout << endl;
	cout << "area r3 = " << r3->getArea() << endl << endl;
	cout << "delete r1" << endl;
	delete r1;
	cout << endl;
	cout << "delete r2" << endl;
	delete r2;
	cout << endl;
	cout << "delete r3" << endl;
	delete r3;
	cout << "---------------\n";
	cout << "помещение объектов в переменные различных типов" << endl;
	const int size = 5;
	Shape* shapes[size];
	for (int i = 0; i < size; i++)
		shapes[i] = new Point();
	for (int i = 0; i < size; i++)
		delete shapes[i];
	cout << "---------------\n";
	cout << "композиция объектов: атрибутом класса Circle является указатель на другой объект класса Point\n";
	Circle c1;
	cout << endl;
	Point* ptrp = new Point(2, 2);
	Circle c2(10, ptrp, "blue");
	cout << endl;
	Circle c3{ c2 };
	cout << endl;
	return 0;
}