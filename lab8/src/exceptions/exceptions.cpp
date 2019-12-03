#include "exceptions.h"

std::ostream &operator<<(std::ostream &out, const Exception &e) {
    return out << "Exception #" << e.label << ": " << e.sig << " " << strsignal(e.sig) << std::endl;
}

void throwException(int sig, std::string label) {
    throw Exception(sig, label);
}
