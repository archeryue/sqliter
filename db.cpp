#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "statement.h"
#include "table.h"

enum CommandResult {
    COMMAND_SUCCESS,
    COMMAND_UNRECOGNIZED
};

std::vector<Table> tables;

void PrintPrompt() {
    std::cout << "sqliter> ";
}

void ReadInput(std::string& input) {
    std::getline(std::cin, input);
}

void PrintTables() {
    std::for_each(tables.begin(), tables.end(), [](auto& e) {std::cout << e.Name() << " ";});
    std::cout << std::endl;
}

CommandResult DoCommand(std::string& input) {
    if (input == ".exit") {
        exit(0);
    } else if (input == ".table") {
        PrintTables();
    } else {
        return COMMAND_UNRECOGNIZED;
    }
    return COMMAND_SUCCESS;   
}

void ExecuteStatement(Statement& stmt) {
    switch (stmt.Type()) {
        case CREATE: {
            std::cout << "create " << stmt._Table()->Name() << " ";
            const std::vector<Column>& columns = stmt._Table()->Columns();
            std::for_each(columns.cbegin(), columns.cend(),
                          [](auto& e) { std::cout << e.Name() << " "; });
            std::cout << std::endl;
            AddTable(stmt._Table());
        } break;
        case INSERT: {
            std::cout << "insert " << stmt._Table()->Name() << " ";
            const std::vector<std::string>& values = stmt.Values();
            std::for_each(values.cbegin(), values.cend(),
                          [](auto& e) { std::cout << e << " "; });
            std::cout << std::endl;
        } break;
        case SELECT: {
            std::cout << "select " << stmt._Table()->Name() << " ";
            const std::vector<Condition>& conditions = stmt.Conditions();
            std::for_each(conditions.cbegin(), conditions.cend(),
                          [](auto& e) { std::cout << e.GetColumnName() << " " 
                          << e.GetCmpType() << " " << e.GetCmpVal() << " " << e.GetLogic() << " "; });
            std::cout << std::endl;
        } break;
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
