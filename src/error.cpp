#include "error.hpp"

Error::Error(std::string type, std::string message, std::string file, int line) {
    this->type = type;
    this->message = message;
    this->file = file;
    this->line = line;
}
