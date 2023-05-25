#include <iostream>

template <class T>
void foo(T words, int number, int value) {
    for (int i = 0; i < number; ++i) {
        value = words(value);
        std::cout << "value = " << value << '\n';
    }
}

int foo2(int number) {
    return number * 2;
}

int main() {
    int number = 3;
    int value = 5;
    foo(foo2, number, value);
    return 0;
}