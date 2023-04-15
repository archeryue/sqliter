#include "statement.h"

PrepareResult Statement::Prepare(const std::string& input) {
    this->src = input;
    std::string_view sv = Source();
    if (sv.starts_with("create")) {
        this->type = CREATE;
    } else if (sv.starts_with("insert")) {
        this->type = INSERT;
    } else if (sv.starts_with("select")) {
        this->type = SELECT;
    } else if (sv.starts_with("update")) {
        this->type = UPDATE;
    } else if (sv.starts_with("delete")) {
        this->type = DELETE;
    } else {
        this->type = NONE;
        return PREPARE_UNRECOGNIZED;
    }
    return PREPARE_SUCCESS;
}

std::string_view Statement::Source() {
    return std::string_view(this->src);
}

StatementType Statement::Type() {
    return this->type;
}
