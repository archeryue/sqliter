#ifndef __TABLE__
#define __TABLE__

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

enum DataType {
    INT,
    DOUBLE,
    CHAR32,
    TEXT
};

enum CmpType {
    EQ,
    GT,
    LT,
    GE,
    LE
};

class Table {
public:
    Table(std::string name, std::vector<DataType> def) : name(name), def(def) {}
    std::string_view Name();
    const std::vector<DataType>& Def();
private:
    std::string name;
    std::vector<DataType> def;
    std::string file;
};

class Row {
private:
    Table* table;
    std::int64_t key;
    std::vector<std::string> data;
};

class Condition {
private:
    Table* table;
    std::size_t def_idx;
    CmpType cmp_type;
    std::string cmp_val;
};

#endif
