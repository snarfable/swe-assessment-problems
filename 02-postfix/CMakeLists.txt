find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(02-postfix 02-postfix.cpp PostfixConsumer.cpp)
target_compile_options(02-postfix PRIVATE -std=c++20)
target_link_libraries(02-postfix PRIVATE jsoncpp spdlog::spdlog Boost::program_options)
