#include <iostream>
#include <string>

#include "statement.h"

enum CommandResult {
    COMMAND_SUCCESS,
    COMMAND_UNRECOGNIZED
};

void PrintPrompt() {
    std::cout << "sqliter> ";
}

void ReadInput(std::string& input) {
    std::getline(std::cin, input);
}

CommandResult DoCommand(std::string& input) {
    if (input == ".exit") {
        exit(0);
    } else {
        return COMMAND_UNRECOGNIZED;
    }
    return COMMAND_SUCCESS;   
}

void ExecuteStatement(Statement& stmt) {
    switch (stmt.Type()) {
    case INSERT:
        std::cout << "insert xxx" << std::endl;
        break;
    case SELECT:
        std::cout << "select xxx" << std::endl;
        break;
    case UPDATE:
        std::cout << "update xxx" << std::endl;
        break;
    case DELETE:
        std::cout << "delete xxx" << std::endl;
        break;
    default:
        std::cout << "error." << std::endl;
    }
}

int main() {
    std::string input;
    while (true) {
        PrintPrompt();
        ReadInput(input);
        if (input[0] == '.') {
            switch (DoCommand(input)) {
            case COMMAND_SUCCESS:
                break;
            case COMMAND_UNRECOGNIZED:
                std::cout << "unrecognized command" << std::endl;
                break;
            }
        } else {
            Statement stmt;
            switch (stmt.Prepare(input)) {
            case PREPARE_SUCCESS:
                ExecuteStatement(stmt);
                break;
            case PREPARE_UNRECOGNIZED:
                std::cout << "unrecognized statement" << std::endl;
                break;
            }
        }
        input.clear();
    }
}
