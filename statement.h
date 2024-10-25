#ifndef __STATEMENT__
#define __STATEMENT__

#include <string>
#include <string_view>

#include "table.h"

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED,
    PREPARE_SYNTAX_ERROR,
    PREPARE_TABLE_NOT_FOUND
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
    const std::vector<std::string>& Values() const;
    const std::vector<Condition>& Conditions() const;
private:
    std::string src;
    StatementType type;
    Table* table;
    std::vector<std::string> values;
    std::vector<Condition> conditions;
    std::vector<std::string> ParseValues(const std::string& values_str);
    std::vector<Condition> ParseWhereClause(const std::string& where_clause);
};

#endif
