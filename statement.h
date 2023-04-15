#ifndef __STATEMENT__
#define __STATEMENT__

#include <string>
#include <string_view>

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED
};

enum StatementType {
    NONE, INSERT, SELECT, UPDATE, DELETE
};

class Statement {
public:
    Statement() : src(), type(NONE) {}
    std::string_view Source();
    StatementType Type();
    PrepareResult Prepare(const std::string& input);
private:
    std::string src;
    StatementType type;
};

#endif
