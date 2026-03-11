#include "Logger.hpp"
#include <ctime>
#include <iomanip>
#include <sstream> // 必须添加这一行

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

//4.时间戳函数
std::string Logger::getCurrentTime(){
    //1.获取系统当前时间点（自1970年以来的秒数）
    std::time_t now = std::time(nullptr);

    //2.将秒数转换为本地时间结构体（包含年月日时分秒）
    //注意：localtime在工业级多线程中不安全，后续我们会优化
    std::tm* localTime = std::localtime(&now);

    //3.格式化输出：利用流对象将结构体转换为字符串
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S"); //格式化时间字符串

    return oss.str();
}

//5.核心日志写入函数
// 目的：将级别、时间、内容拼接成一行标准的工业日志。
// 架构逻辑：
// 为什么用 switch？因为 Logclass 是枚举，switch 可以让编译器检查是否漏掉了某个等级。
// 为什么最后要加 flush？为了保证日志实时写入，而不是卡在内存缓冲区里。
void Logger::log(Logclass level, const std::string& message){
    std::string levelStr;
    switch (level){
        case Logclass::INFO: levelStr = "INFO"; break;
        case Logclass::WARN: levelStr = "WARN"; break;
        case Logclass::ERROR: levelStr = "ERROR"; break;
    }

    if(m_logFile.is_open()){
        m_logFile << "[" << getCurrentTime() << "]"
                  << "[" << levelStr << "] "
                  << message << std::endl; //写入日志并换行
        m_logFile.flush();//立即将缓冲区内容写入磁盘，确保日志不丢失
    }
}