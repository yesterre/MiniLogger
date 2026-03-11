#include "Logger.hpp"
#include <ctime>
#include <iomanip>

//1.实现 Meyers' Singleton：线程安全且唯一
/**
 * 目的：实现单例入口
 * 逻辑：利用 C++11 局部静态变量特性。
 * 为什么：这是最优雅的线程安全单例实现（Meyers' Singleton）。
 * 只有在第一次调用时才会创建 instance，程序退出时自动销毁。
 */
Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}

//2.构造函数：追加模式并打开日志文件
/**
 * 目的：私有构造函数
 * 逻辑：在对象出生时打开文件。
 * 为什么：打开文件是昂贵的系统调用。放在构造函数里只做一次，
 * 避免了每次写日志都重新打开文件的性能损耗。
 */
Logger::Logger(){
    m_logFile.open("latest.log",std::ios::app);  //以追加模式打开，写入会追加到文件末尾
}

//3.析构函数：安全关闭日志文件
/**
 * 目的：析构函数
 * 逻辑：在对象销毁（程序关闭）前关闭文件流。
 * 为什么：防止“文件句柄泄露”。如果程序崩溃且未关闭文件，
 * 可能会导致最后几条日志没写入磁盘（仍在缓冲区）。
 */
Logger::~Logger(){
    if (m_logFile.is_open()){
        m_logFile.close();
    }
}