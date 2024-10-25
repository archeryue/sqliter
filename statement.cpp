#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

#include "statement.h"
#include "table.h"

const std::int64_t SQL_TOKEN_LEN = 64;

PrepareResult Statement::Prepare(const std::string& input) {
    this->src = input;
    std::string_view sv = Source();
    if (sv.starts_with("create")) {
        // create table xxx column id:int,name:char32,age:int;
        this->type = CREATE;
        char tb_char[SQL_TOKEN_LEN] {};
        char def_char[SQL_TOKEN_LEN] {};
        std::sscanf(input.c_str(), "create table %s column %s", tb_char, def_char);
        std::vector<Column> columns = ParseColumn(def_char);
        Table* t = new Table(tb_char, columns);
        this->table = t;
    } else if (sv.starts_with("insert")) {
        // insert into xxx values(1,"archer",30);
        this->type = INSERT;
        char tb_name[SQL_TOKEN_LEN] {};
        char values[SQL_TOKEN_LEN * 2] {}; // Increased size to accommodate more values
        if (std::sscanf(input.c_str(), "insert into %s values(%[^)])", tb_name, values) == 2) {
            // Check if the table exists
            Table* existing_table = GetTable(tb_name);
            if (existing_table == nullptr) {
                return PREPARE_TABLE_NOT_FOUND;
            }
            this->table = existing_table;
            // TODO: check value types with table columns
            this->values = ParseValues(values);
        } else {
            return PREPARE_SYNTAX_ERROR;
        }
    } else if (sv.starts_with("select")) {
        // select * from xxx where age > 30;
        // select * from xxx where id > 1 and age > 30;
        this->type = SELECT;
        
        char table_name[SQL_TOKEN_LEN] {};
        char where_clause[SQL_TOKEN_LEN * 2] {}; // Increased size to accommodate more complex conditions
        
        int parsed = std::sscanf(input.c_str(), "select * from %s where %[^\n]", table_name, where_clause);
        
        if (parsed >= 1) {
            // Check if the table exists
            Table* existing_table = GetTable(table_name);
            if (existing_table == nullptr) {
                return PREPARE_TABLE_NOT_FOUND;
            }
            this->table = existing_table;
            
            if (parsed == 2) {
                // Parse the where clause
                this->conditions = ParseWhereClause(where_clause);
            }
        } else {
            return PREPARE_SYNTAX_ERROR;
        }
    } else if (sv.starts_with("update")) {
        // update xxx set age = 31 where name = "archer";
        // update xxx set age = 31, name = "alex" where id = 1;
        this->type = UPDATE;
    } else if (sv.starts_with("delete")) {
        // delete from xxx where id = 1;
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

Table* Statement::_Table() {
    return this->table;
}

std::vector<std::string> Statement::ParseValues(const std::string& values_str) {
    std::vector<std::string> result;
    std::string current_value;
    bool in_quotes = false;
    
    for (char c : values_str) {
        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            result.push_back(current_value);
            current_value.clear();
        } else {
            current_value += c;
        }
    }
    
    if (!current_value.empty()) {
        result.push_back(current_value);
    }
    
    return result;
}

const std::vector<std::string>& Statement::Values() const {
    return this->values;
}

std::vector<Condition> Statement::ParseWhereClause(const std::string& where_clause) {
    std::vector<Condition> conditions;
    std::istringstream iss(where_clause);
    std::string token;
    
    std::string column_name;
    CmpType cmp_type;
    std::string value;
    CondLogic logic = AND; // Default to AND
    
    while (iss >> token) {
        if (token == "and" || token == "or") {
            logic = (token == "and") ? AND : OR;
        } else {
            if (column_name.empty()) {
                column_name = token;
            } else if (token == "=" || token == ">" || token == "<") {
                cmp_type = (token == "=") ? EQ : (token == ">") ? GT : LT;
            } else {
                value = token;
                // Remove quotes if present
                if (value.front() == '"' && value.back() == '"') {
                    value = value.substr(1, value.length() - 2);
                }
                
                // Create and add the condition
                conditions.emplace_back(this->table, column_name, cmp_type, value, logic);
                
                // Reset for next condition
                column_name.clear();
                value.clear();
            }
        }
    }
    
    return conditions;
}

const std::vector<Condition>& Statement::Conditions() const {
    return this->conditions;
}
