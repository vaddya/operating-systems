#include <csignal>
#include <string>
#include <memory.h>
#include <iostream>
#include <sstream>

void generateSigfpe();

void generateSigill();

__sighandler_t signalHandler(int sig, __sighandler_t handler);

__sighandler_t sigactionHandler(int sig, __sighandler_t handler);

void printingHandler(int sig);

std::string toString(int sig);
