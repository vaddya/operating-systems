#include <csignal>
#include <memory.h>
#include <iostream>

class Exception {
public:
    Exception(int sig, std::string label) : sig(sig), label(label) {}

    friend std::ostream &operator<<(std::ostream &out, const Exception &e);

private:
    int sig;
    std::string label;
};

void throwException(int sig, std::string label);
