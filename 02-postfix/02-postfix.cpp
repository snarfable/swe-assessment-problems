/**
 * @file 02-postfix.cpp
 * @brief Main entry point for the postfix evaluation application.
 * 
 * This file serves as the main entry point for the postfix evaluation
 * application. It includes the necessary headers and libraries required for the
 * application to function correctly. The main function initializes the
 * application, sets up logging, and prepares for the evaluation of postfix
 * expressions. The specific implementation details and functionality of the
 * postfix evaluation process will be defined in other source files, such as
 * PostfixConsumer.cpp.
 */

#include <iostream>
#include <string>
#include <queue>
#include <jsoncpp/json/json.h>
#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

/**
 * Private header files internal to the project. These headers contain the
 * necessary includes and declarations for the PostfixConsumer class, which is
 * responsible for consuming and processing postfix expressions. The class
 * utilizes the JSON library for configuration and logging capabilities provided
 * by the spdlog library. The PostfixConsumer class is designed to handle the
 * evaluation of postfix expressions and manage a queue of postfix expressions
 * for processing.  The specific implementation details and member functions of
 * the PostfixConsumer class will be defined in the corresponding source file
 * (PostfixConsumer.cpp).
 */
#include "ItemConsumer.hpp"
#include "PostfixConsumer.hpp"
#include "UInt32Consumer.hpp"
#include "OperatorConsumer.hpp"

int main(int argc, char **argv)
{
    // Parse command line options with boost
    std::string configFile;
    bool showHelp = false;
    boost::program_options::options_description desc("Options for parsing postfix expressions");
    desc.add_options()
        ("help,h", boost::program_options::bool_switch(&showHelp)->notifier([](bool value) {
                    if (value)
                    {
                        std::cout << "Usage: 02-postfix [options]" << std::endl;
                    }
                }),
         "Show help")
        ("config,c", boost::program_options::value<std::string>(&configFile)->notifier([](const std::string& value) {
                    std::cout << "Configuration file set to: " << value << '\n';
                }
            ),
        "Set configuration file");
    
    boost::program_options::variables_map vm;
    try
    {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
        if (showHelp)
        {
            std::cout << desc << '\n';
            return 0;
        }
        spdlog::info("Command line options parsed successfully");
    }
    catch (const boost::program_options::error &e)
    {
        std::cerr << "Error parsing command line options: " << e.what() << std::endl;
        return 1;
    }

    // Log policy: Set the log level to info
    spdlog::info("Starting postfix evaluation");

    // Create the primary PostfixConsumer object with a default configuration 
    postfix::UInt32Consumer intConsumer("int_parser", "23");
    intConsumer.consume();
    std::cout << postfix::detail << intConsumer << std::endl;
    postfix::PostfixConsumer consumer(std::string("{}"));

    return 0;
}
