#ifndef LOGGER_SINGLETON_H
#define LOGGER_SINGLETON_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>
#include <fstream>

using namespace std;

class LoggerSingleton
{
protected:
    static LoggerSingleton *_instance;
    vector<string> LogMessages;

    // Constructor
    LoggerSingleton();

    // Destructor
    ~LoggerSingleton();

public:
    // Retrieve the single instance of the logger created
    // (Only one logger is created to record all actions in the system, both successful and failed)
    // (Save the logger to a log file)
    static LoggerSingleton &GetInstance();

    void AddMessage(string message);

    void WriteLogFile();
};
#endif