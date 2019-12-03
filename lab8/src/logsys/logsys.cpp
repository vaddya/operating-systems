#include "utils.h"
#include <syslog.h>

void sysLogHandler(int sig) {
    syslog(LOG_INFO, "Handling signal %s", toString(sig).c_str());
    signal(sig, SIG_DFL);
}

int main() {
    openlog("logsys", 0, LOG_USER);
    signalHandler(SIGFPE, sysLogHandler);
    generateSigfpe();
    closelog();
    return 0;
}