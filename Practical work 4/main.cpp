#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Schedule {
private:
    int start;
    int end;
    double step;
public:
    Schedule(int start, int end, double step) {
        this->start = start;
        this->end = end;
        this->step = step;
    }

    void graphOutput() {
        std::cout << "Graph:\n";
        for (double i = start; i < end; i += step) {
            std::cout << i << ' ';
            if (i + step >= end) { break; }
            else { std::cout << "| "; }
        }
        std::cout << '\n';
    }
};

int main() {
    int start;
    int end;
    double step;

    std::ifstream file("example.txt");

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        
        std::stringstream ss(line);
        std::vector<int> numbers;
        std::string numberStr;
        
        while (std::getline(ss, numberStr, ',')) {
            int number = std::stoi(numberStr);
            numbers.push_back(number);
        }
        start = numbers[0];
        end = numbers[1];
        step = numbers[2];

        std::cout << "Read numbers: ";
        for (int number : numbers) { std::cout << number << " "; }
        std::cout << '\n';

        file.close();
        std::cout << "File can read.\n";
    } else { std::cout << "File can't read.\n"; }

    Schedule schedule(start, end, step);

    schedule.graphOutput();
    return 0;
}