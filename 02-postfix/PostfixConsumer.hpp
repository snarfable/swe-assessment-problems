#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <jsoncpp/json/json.h>
#include <spdlog/spdlog.h>

namespace postfix
{

/**
 * @brief The PostfixConsumer class is responsible for consuming and processing postfix expressions.
 * 
 * The class utilizes a JSON configuration object to manage various settings and
 * parameters required for the postfix evaluation process. It also maintains a
 * queue of postfix expressions for processing. The specific implementation
 * details and member functions of the PostfixConsumer class will be defined in
 * the corresponding source file (PostfixConsumer.cpp).
 */
class PostfixConsumer
{
private:

    /**
     * _config is a JSON object that holds the configuration for the
     * PostfixConsumer. It is used to store various settings and parameters that
     * may be needed for the postfix evaluation process. The specific structure
     * and contents of this JSON object will depend on the requirements of the
     * application and how it is intended to be used.
     */
    Json::Value _config;

    /**
     * The buffer from whence we get the values read from input.
     */
    std::string _buffer;

    /**
     * The string stream used to extract words separated by whitespace.
     */
    std::istringstream _stream;

    std::vector<std::string> _words;

    /**
     * _postfixQueue is the buffer used to story numerical values as they come
     * in and serves as temporary storage for products which emerge from
     * operations as they show up in the buffer.
     */
    std::queue<std::uint32_t> _postfixQueue;

public:

    /**
     * @brief Constructs a new PostfixConsumer object with the given configuration.
     *
     * @param config A JSON object containing the configuration settings for the
     * PostfixConsumer. This configuration may include various parameters and
     * options that influence the behavior of the postfix evaluation process.
     */
    PostfixConsumer(const std::string& buffer_, Json::Value config_);

    /**
     * @brief Constructs a new PostfixConsumer object by copying the given configuration string.
     * 
     * @param configString_ A string representation of the configuration for the
     * PostfixConsumer. This string will be parsed into a JSON object to initialize
     * the configuration settings for the postfix evaluation process.
     * 
     * The specific format and contents of the configuration string will depend on
     * the requirements of the application and how it is intended to be used.
     */
    PostfixConsumer(const std::string& buffer_, const std::string& configString_);

    /**
     * @brief Destroys the PostfixConsumer object and performs any necessary cleanup.
     *
     * The destructor ensures that any resources allocated by the PostfixConsumer
     * are properly released. This may include clearing the postfix queue and
     * performing any other cleanup tasks required for the proper functioning of
     * the class.
     */
    ~PostfixConsumer();
};

}