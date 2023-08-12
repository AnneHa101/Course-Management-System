#include "LoggerSingleton.h"

// Constructor
LoggerSingleton::LoggerSingleton()
{
    cout << "Logger was created" << endl;
}

// Destructor
LoggerSingleton::~LoggerSingleton()
{
    cout << "Logger was deleted" << endl;
}

// Retrieve the single instance of the logger created
// (Only one logger is created to record all actions in the system, both successful and failed)
// (Save the logger to a log file)
LoggerSingleton &LoggerSingleton::GetInstance()
{
    static LoggerSingleton *_instance = new LoggerSingleton;
    return *_instance;
}

void LoggerSingleton::AddMessage(string message)
{
    LogMessages.push_back(message);
}

void LoggerSingleton::WriteLogFile()
{
    cout << "Accessing the log..." << endl;
    ofstream LogFile("LogFile.txt", ios_base::out | ios_base::app);
    for (string e : LogMessages)

        LogFile << e << endl;
}
