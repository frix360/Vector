#include <iostream>
#include "Vector.h"
#include <vector>
#include <ctime>
#include <chrono>
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}

    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        return std::chrono::duration<double>
                (std::chrono::high_resolution_clock::now() - start).count();
    }
};

void testBuiltInVector() {
    std::vector<int> testSizes {10000, 100000, 1000000, 10000000, 100000000};

    unsigned int reallocationCount = 0;
    std::cout << "Testuojame std::vector" << std::endl << "------------------------------------------------" << std::endl << std::endl;

    Timer timer;

    for (auto size : testSizes) {
        std::cout << size << " skaiciu:" << std::endl;
        std::vector<int> testVec;

        for (int i = 1; i <= size; ++i) {
            testVec.push_back(i);
            if (testVec.size() == testVec.capacity()) {
                reallocationCount++;
            }

        }

        std::cout << size << " skaiciu irasymas uztruko " << timer.elapsed() << std::endl;
        std::cout << "Perskirstymas buvo atliktas " << reallocationCount << " kartu" << std::endl;
        timer.reset();
    }
};

void testCustomVector() {
    std::vector<int> testSizes {10000, 100000, 1000000, 10000000, 100000000};

    unsigned int reallocationCount = 0;

    std::cout << "Testuojame Vector" << std::endl << "------------------------------------------------" << std::endl << std::endl;

    Timer timer;

    for (auto size : testSizes) {
        std::cout << size << " skaiciu:" << std::endl;
        Vector<int> testVec;

        for (int i = 1; i <= size; ++i) {
            testVec.push_back(i);
            if (testVec.size() == testVec.capacity()) {
                reallocationCount++;
            }
        }

        std::cout << size << " skaiciu irasymas uztruko " << timer.elapsed() << std::endl;
        std::cout << "Perskirstymas buvo atliktas " << reallocationCount << " kartu" << std::endl;
        timer.reset();
    }
};

int main() {
    testBuiltInVector();
    testCustomVector();

    return 0;
}
