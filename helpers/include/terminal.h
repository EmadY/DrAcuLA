#include <stdexcept>
#include <stdio.h>
#include <string>
#include <unistd.h>


class Terminal {
    public:
        static std::string Exec(std::string cmd);
};
