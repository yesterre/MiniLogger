#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>

//日志级别枚举：强类型枚举增加安全性
enum class Logclass {
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    //获取单例实例的唯一入口
    static Logger& getInstance();

    //禁用拷贝构造和赋值运算符，防止单例被破坏
    Logger(const Logger&) = delete;   //= delete 表示显式禁止某个函数被调用
    Logger& operator=(const Logger&) = delete;

    //核心接口：写入日志
    void log(Logclass level, const std::string& message);
    //&：按引用传递，避免复制大对象，性能更好
    //const：承诺函数内不修改传入字符串

private:
    Logger();   //私有构造，初始化文件流
    ~Logger();  //析构，确保文件流正常关闭

    std::ofstream m_logFile;
    std::string getCurrentTime();  //私有辅助函数：生成时间戳
};

#endif  //