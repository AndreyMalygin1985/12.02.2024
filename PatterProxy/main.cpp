#include <iostream>
#include <Windows.h>
#include <map>
#include <unordered_map>

using namespace std;

class IMath {
public:
	virtual double Add(double x, double y) = 0;
	virtual double Sub(double x, double y) = 0;
	virtual double Mult(double x, double y) = 0;
	virtual double Div(double x, double y) = 0;
};

class Math : public IMath {
public:
	double Add(double x, double y) { return x + y; }
	double Sub(double x, double y) { return x - y; }
	double Mult(double x, double y) { return x * y; }
	double Div(double x, double y) { return x / y; }
};

class MathProxy : public IMath {
private:
	Math* math;
public:
	MathProxy() {
		math = new Math();
	}
	~MathProxy() { delete math; }
	double Add(double x, double y) { return math->Add(x, y); }
	double Sub(double x, double y) { return math->Sub(x, y);}
	double Mult(double x, double y) { return math->Mult(x, y);}
	double Div(double x, double y) {
		if (y != 0.0)
		{
			return math->Div(x, y);
		}
		else
		{
			throw ("На ноль делить нельзя!");
		}
	}
};

int main()
{
	SetConsoleOutputCP(1251);

	MathProxy* proxy = new MathProxy();

	cout << "7 + 11 = "<<proxy->Add(7,11) << endl;
	cout << "6 - 8 = "<<proxy->Sub(6,8) << endl;
	cout << "7 * 11 = "<<proxy->Mult(7,11) << endl;
	cout << "7 / 11 = "<<proxy->Div(7,11) << endl;

	delete proxy;

	return 777;
}