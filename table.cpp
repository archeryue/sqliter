#include "table.h"

std::string_view Table::Name() {
    return std::string_view(this->name);
}

const std::vector<DataType>& Table::Def() {
    return this->def;
}
