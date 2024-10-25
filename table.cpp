#include "table.h"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

std::string_view Column::Name() const {
    return this->name;
}

DataType Column::Type() const {
    return this->type;
}

DataType str2Type(std::string_view str) {
    return str == "int" ? INT : str == "double" ? DOUBLE : CHAR32;
}

std::vector<std::string_view> split(std::string_view str, char delim) {
    std::vector<std::string_view> res;
    std::size_t start = 0;
    while (start < str.size()) {
        auto end = str.find_first_of(delim, start);
        if (start != end) res.emplace_back(str.substr(start, end-start));
        if (end == std::string_view::npos) break;
        start = end + 1;
    }
    return res;
}

// extract column name and type from string
// e.g. "id:int,name:char32,age:int"
Column str2Column(std::string_view column_def) {
    int idx = column_def.find(':');
    std::string name(column_def.substr(0, idx));
    DataType type = str2Type(column_def.substr(idx+1, column_def.size()+1));
    Column col(name, type);
    return col;
}

std::vector<Column> ParseColumn(std::string_view column_def) {
    std::vector<std::string_view> col_str = split(column_def, ',');
    std::vector<Column> columns;
    for (auto& str : col_str) {
        columns.push_back(str2Column(str));
    }
    return columns;
}

std::string_view Table::Name() {
    return std::string_view(this->name);
}

const std::vector<Column>& Table::Columns() {
    return this->columns;
}

// Add this static member to store tables
static std::unordered_map<std::string, std::unique_ptr<Table>> tables;

void LoadTables() {
    // TODO: load tables from disk
    // After loading each table, call AddTable to add it to memory
}

Table* GetTable(const std::string& name) {
    auto it = tables.find(name);
    if (it != tables.end()) {
        return it->second.get();
    }
    return nullptr;
}

void AddTable(Table* table) {
    if (table) {
        tables[std::string(table->Name())] = std::unique_ptr<Table>(table);
    }
}

std::string Condition::GetColumnName() const {
    return this->column_name;
}

CmpType Condition::GetCmpType() const {
    return this->cmp_type;
}

std::string Condition::GetCmpVal() const {
    return this->cmp_val;
}

CondLogic Condition::GetLogic() const {
    return this->logic;
}