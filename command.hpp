#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <cstdlib>


class command{
    private:
        std::string buf;
    public:
        command();
        std::string open_firefox();
        std::string open_terminal();
        std::string open_calculator();

};
#endif