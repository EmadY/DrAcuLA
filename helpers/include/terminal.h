#ifndef HELPERS_TERMINAL
#define HELPERS_TERMINAL

#include <stdexcept>
#include <stdio.h>
#include <string>
#include <unistd.h>


class Terminal {
    public:
        // runs cmd on the terminal and returns the result
        static std::string Exec(std::string cmd);

        // does as above, except it prints the command as well for
        // debugging purposes.
        static std::string dExec(std::string cmd);
};

#endif
