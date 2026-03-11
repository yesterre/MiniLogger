#include "Logger.hpp"
#include <ctime>
#include <iomanip>

//1.实现 Meyers' Singleton：线程安全且唯一
Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

//2.构造函数：追加模式并打开日志文件
Logger::Logger(){
    m_logFile.open("latest.log",std::ios::app);
}

//3.析构函数：安全关闭日志文件
Logger::~Logger(){
    if (m_logFile.is_open()){
        m_logFile.close();
    }
}