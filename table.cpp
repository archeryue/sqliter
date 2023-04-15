#include "table.h"
#include <string>
#include <string_view>
#include <vector>

std::string_view Column::Name() const {
    return this->name;
}

DataType Column::Type() const {
    return this->type;
}

DataType Str2Type(std::string_view str) {
    return str == "int" ? INT : str == "double" ? DOUBLE : CHAR32;
}

std::vector<Column> ParseColumn(std::string_view column_def) {
    std::vector<std::string_view> col_str;
    std::size_t start = 0;
    while (start < column_def.size()) {
        auto end = column_def.find_first_of(',', start);
        if (start != end) col_str.emplace_back(column_def.substr(start, end-start));
        if (end == std::string_view::npos) break;
        start = end + 1;
    }
    std::vector<Column> columns;
    for (auto& str : col_str) {
        int idx = str.find(':');
        std::string name(str.substr(0, idx));
        DataType type = Str2Type(str.substr(idx+1, str.size()+1));
        Column col(name, type);
        columns.push_back(col);
    }
    return columns;
}

std::string_view Table::Name() {
    return std::string_view(this->name);
}

const std::vector<Column>& Table::Columns() {
    return this->columns;
}
