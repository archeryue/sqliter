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
    CHAR32
};

enum CmpType {
    EQ,
    GT,
    LT
};

class Column {
public:
    Column(std::string name, DataType type) : name(name), type(type) {}
    std::string_view Name() const;
    DataType Type() const;
private:
    std::string name;
    DataType type;
};

std::vector<Column> ParseColumn(std::string_view column_def);

class Table {
public:
    Table(std::string name, std::vector<Column>& columns) : name(name), columns(columns) {}
    std::string_view Name();
    const std::vector<Column>& Columns();
private:
    std::string name;
    std::vector<Column> columns;
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
    std::size_t column_idx;
    CmpType cmp_type;
    std::string cmp_val;
};

#endif
