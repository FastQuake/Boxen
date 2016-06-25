#ifndef ERROR_HPP
#define ERROR_HPP
#include <string>

#define ErrMsg(type, msg) Error(type, msg, __FILE__, __LINE__)

class Error {
    public:
        std::string type, message, file;
        int line;

        Error(std::string type, std::string message, std::string file, int line);
};

#endif
