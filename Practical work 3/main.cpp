#include <iostream>

class MyClass {
public:
    void mathod(int x) {
        std::cout << "int:\n"
                  <<"x = " << x << "\n\n";
    }

    void mathod(double x) {
        std::cout << "double:\n"
                  << "x = " << x << "\n\n";
    }

    void mathod(int x, double y) {
        std::cout << "int and double:\n"
                  << "x(" << x << ") + y(" << y << ") = " << x + y << "\n\n";
    }

    void mathod(int x, int y) {
        std::cout << "int and int:\n"
                  << "x(" << x << ") - y(" << y << ") = " << x - y << "\n\n"; }
};

int main() {
    MyClass reboot;
    reboot.mathod(1);
    reboot.mathod(3.14);
    reboot.mathod(5, 7.19);
    reboot.mathod(10, 7);
    return 0;
}