cmake_minimum_required(VERSION 3.10)
project(MiniLogger)

# 1. 设置 C++ 标准（工业级项目建议显式指定）
set(CMAKE_CXX_STANDARD 11)

# 2. 声明头文件位置
# 目的：让编译器知道在 include 文件夹里寻找 Logger.hpp
include_directories(include)

# 3. 创建库目标 (Library)
# 目的：将 Logger.cpp 编译为静态库，便于以后其他项目复用。
add_library(logger_lib src/Logger.cpp)

# 4. 创建可执行程序目标 (Executable)
# 目的：将 main.cpp 编译为最终能运行的 logger_test 程序。
add_executable(logger_test examples/main.cpp)

# 5. 建立链接关系 (Linking)
# 目的：告诉链接器，logger_test 需要用到 logger_lib 里的实现逻辑。
target_link_libraries(logger_test logger_lib)