#ifndef __STATEMENT__
#define __STATEMENT__

#include <string>
#include <string_view>

#include "table.h"

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED
};

enum StatementType {
    NONE, CREATE, INSERT, SELECT, UPDATE, DELETE
};

class Statement {
public:
    Statement() : src(), type(NONE), table(nullptr) {}
    std::string_view Source();
    StatementType Type();
    Table* _Table();
    PrepareResult Prepare(const std::string& input);
private:
    std::string src;
    StatementType type;
    Table* table;
};

#endif
