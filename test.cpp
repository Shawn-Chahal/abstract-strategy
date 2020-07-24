#include <iostream>


int main() {

    int x = 5;
    int y = 10;
    double z = (y - x + 0.0) / (x + y + 0.0);

    std::cout << (y - x + 0.0) / (x + y + 0.0) << std::endl; 

    return 0;
}