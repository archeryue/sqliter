#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

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
    } else if (sv.starts_with("select")) {
        // select * from xxx where age > 30;
        // select * from xxx where id > 1 and age > 30;
        this->type = SELECT;
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
