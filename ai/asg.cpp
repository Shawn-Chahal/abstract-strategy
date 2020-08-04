#include "asg.h"

#include <iostream>

void asg::line_break(int length) {
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = 0; i < length; i++) {
        std::cout << "-";
    }  
    std::cout << std::endl << std::endl;
}

int asg::menu_input (int size) {

    int index = -1;

    while (index == -1) {
        if (!(std::cin >> index)){
            std::cout << "\t" << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            index = -1;
        } else if (index < 1 || index > size) {
            std::cout << "\t" << "Index unavailable. Please enter a number between 1 and " << size << ": ";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            index = -1;
        }
    }        

    return index;
}
