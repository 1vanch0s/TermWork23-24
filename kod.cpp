#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class ProgStart {
public:
    void start() {
        cout << "Для начала работы нажмите 1\nДля выхода нажмите 2\n";
    }
};


class QuadraticEquation {
protected:
    double a, b, c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    virtual void solve() = 0;
};

class AlwaysTrue : public QuadraticEquation {
public:
    AlwaysTrue() : QuadraticEquation(0, 0, 0) {}

    void solve() override {
        cout << "X - любое число\n";
    }
};

class SingleRootZero : public QuadraticEquation {
public:
    SingleRootZero() : QuadraticEquation(0, 1, 0) {}

    void solve() override {
        cout << "У уравнения один корень: x = 0\n";
    }
};

class NoRoots : public QuadraticEquation {
public:
    NoRoots() : QuadraticEquation(1, 2, 3) {}

    void solve() override {
        cout << "Уравнение не имеет корней .\n";
    }
};

class ComplexRoots : public QuadraticEquation {
public:
    ComplexRoots(double a, double c) : QuadraticEquation(a, 0, c) {
        if (c / a >= 0) {
            throw invalid_argument("Уравнение не имеет комплексных корней.");
        }
    }

    void solve() override {
        double sqrt_val = sqrt(-c / a);
        cout << "Уравнение имеет комплексные крони: x = " << sqrt_val << "i; x = -" << sqrt_val << "i\n";
    }
};

class SingleRoot : public QuadraticEquation {
public:
    SingleRoot(double b) : QuadraticEquation(1, b, 0) {}

    void solve() override {
        cout << "Уравнение имеет один корень: x = " << -c / b << "\n";
    }
};

class ClassicQuadratic : public QuadraticEquation {
public:
    ClassicQuadratic(double a, double b, double c) : QuadraticEquation(a, b, c) {}

    void solve() override {
        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Уравнение имеет два корня: x = " << root1 << "; x = " << root2 << "\n";
        }
        else if (discriminant == 0) {
            double root = -b / (2 * a);
            cout << "У уравнения один корень: x = " << root << "\n";
        }
        else {
            cout << "Уравнение не имеет корней.\n";
        }
    }
};

class SingleRootZero2 : public QuadraticEquation {
public:
    SingleRootZero2() : QuadraticEquation(0, 0, 1) {}

    void solve() override {
        cout << "Уравнение имеет один корень: x = 0\n";
    }
};

class TwoRoots : public QuadraticEquation {
public:
    TwoRoots(double a, double b) : QuadraticEquation(a, b, 0) {}

    void solve() override {
        cout << "Уравнение имеет два корня: x = 0; x = " << -b / a << "\n";
    }
};

int main() {

	setlocale(LC_ALL, "RU");

    ProgStart s;
    s.start();
    int start_int;
    cin >> start_int;
    if (start_int == 1) {
        system("cls");
    }
    if (start_int == 2) {
        exit(0);
    }

    double a, b, c;
    cout << "Введите параметр a: ";
    cin >> a;
    cout << "\n" <<"Введите параметр b: ";
    cin >> b;
    cout << "\n" << "Введите параметр c: ";
    cin >> c;
  
    try {
        QuadraticEquation* equation = nullptr;

        if (a == 0 && b == 0 && c == 0) {
            equation = new AlwaysTrue();
        }
        else if (a == 0 && b == 1 && c == 0) {
            equation = new SingleRootZero();
        }
        else if (a == 1 && b == 2 && c == 3) {
            equation = new NoRoots();
        }
        else if (c / a < 0) {
            equation = new ComplexRoots(a, c);
        }
        else if (a == 1 && b == 0) {
            equation = new SingleRootZero2();
        }
        else if (a == 0 && b == 0) {
            equation = new TwoRoots(a, b);
        }
        else {
            equation = new ClassicQuadratic(a, b, c);
        }

        equation->solve();
        delete equation;
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << "\n";
    }


	return 0;
}
