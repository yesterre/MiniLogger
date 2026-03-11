#include "Logger.hpp"

int main(){
    //逻辑：通过类名直接访问静态成员函数
    Logger& logger = Logger::getInstance();

    logger.log(Logclass::INFO, "系统启用成功");
    logger.log(Logclass::WARN, "网络延迟波动:50ms");
    logger.log(Logclass::ERROR, "无法连接到数据库服务器");

    return 0;
}