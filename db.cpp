#include <iostream>
#include <string>

void PrintPrompt() {
    std::cout << "sqliter> ";
}

void ReadInput(std::string& input) {
    std::getline(std::cin, input);
}

int main() {
    std::string input;
    while (true) {
        PrintPrompt();
        ReadInput(input);
        if (input == ".exit") {
            return 0;
        } else {
            std::cout << "unrecognized command" << std::endl;
        }
        input.clear();
    }
}
