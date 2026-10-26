/**
 * @file PostfixConsumer.cpp
 * @brief Implementation of the PostfixConsumer class.
 *
 * This file contains the implementation of the PostfixConsumer class, which is
 * responsible for consuming and processing postfix expressions. The class
 * utilizes a JSON configuration object to manage various settings and
 * parameters required for the postfix evaluation process. It also maintains a
 * queue of postfix expressions for processing. The implementation details of
 * the member functions and the overall functionality of the PostfixConsumer
 * class are defined in this source file.
 */

#include <iostream>
#include <string>
#include <queue>

/**
 * Private header file for the PostfixConsumer class. This file contains the necessary
 * includes and declarations for the PostfixConsumer class, which is responsible for
 * consuming and processing postfix expressions. The class utilizes the JSON library
 * for configuration and logging capabilities provided by the spdlog library. The
 * PostfixConsumer class is designed to handle the evaluation of postfix expressions
 * and manage a queue of postfix expressions for processing. The specific implementation
 * details and member functions of the PostfixConsumer class will be defined in the
 * corresponding source file (PostfixConsumer.cpp).
 */
#include "PostfixConsumer.hpp"

namespace postfix
{
    PostfixConsumer::PostfixConsumer(const Json::Value &config) : _config(config)
    {
        spdlog::info("PostfixConsumer initialized with configuration: {}", _config.toStyledString());
    }

    PostfixConsumer::PostfixConsumer(const std::string& configString_) : _config{configString_}
    {
        spdlog::info("PostfixConsumer copy constructed");
    }

    PostfixConsumer::~PostfixConsumer()
    {
        spdlog::info("PostfixConsumer destroyed");
    }

} // namespace postfix