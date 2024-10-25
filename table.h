#ifndef __TABLE__
#define __TABLE__

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

enum DataType {
    INT, DOUBLE, CHAR32
};

enum CmpType {
    EQ, GT, LT
};

enum CondLogic {
    AND, OR
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
public:
    Condition(Table* table, const std::string& column_name, CmpType cmp_type, const std::string& cmp_val, CondLogic logic)
        : table(table), column_name(column_name), cmp_type(cmp_type), cmp_val(cmp_val), logic(logic) {}

    // Add getters if needed
    std::string GetColumnName() const;
    CmpType GetCmpType() const;
    std::string GetCmpVal() const;
    CondLogic GetLogic() const;

private:
    Table* table;
    std::string column_name;
    CmpType cmp_type;
    std::string cmp_val;
    CondLogic logic;
};

void LoadTables();
Table* GetTable(const std::string& name);
void AddTable(Table* table);

#endif
