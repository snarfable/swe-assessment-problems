add_executable(02-postfix-tests
    ItemConsumerTests.cpp
    UInt32ConsumerTests.cpp
    OperatorConsumerTests.cpp
    ../UInt32Consumer.cpp
    ../OperatorConsumer.cpp
)
target_include_directories(02-postfix-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(02-postfix-tests PRIVATE
    GTest::gtest_main
    jsoncpp
    spdlog::spdlog
)

include(GoogleTest)
gtest_discover_tests(02-postfix-tests)
