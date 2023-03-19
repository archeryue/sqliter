#include <iostream>
#include <string_view>
#include <string>

enum CommandResult {
    COMMAND_SUCCESS,
    COMMAND_UNRECOGNIZED
};

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED
};

enum StatementType {
    NONE, INSERT, SELECT, UPDATE, DELETE
};

class Statement {
 public:
    StatementType type;
    Statement(const std::string& input) : src(input) {}
    std::string_view Source();
 private:
    std::string src;
};

std::string_view Statement::Source() {
    return std::string_view(this->src);
}

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

PrepareResult PrepareStatement(Statement& statement) {
    if (statement.Source().starts_with("insert")) {
        statement.type = INSERT;
    } else if (statement.Source().starts_with("select")) {
        statement.type = SELECT;
    } else if (statement.Source().starts_with("update")) {
        statement.type = UPDATE;
    } else if (statement.Source().starts_with("delete")) {
        statement.type = DELETE;
    } else {
        statement.type = NONE;
        return PREPARE_UNRECOGNIZED;
    }
    return PREPARE_SUCCESS;
}

void ExecuteStatement(Statement& statement) {
    switch (statement.type) {
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
            Statement statement(input);
            switch (PrepareStatement(statement)) {
                case PREPARE_SUCCESS:
                    ExecuteStatement(statement);
                    break;
                case PREPARE_UNRECOGNIZED:
                    std::cout << "unrecognized statement" << std::endl;
                    break;
            }
        }
        input.clear();
    }
}
