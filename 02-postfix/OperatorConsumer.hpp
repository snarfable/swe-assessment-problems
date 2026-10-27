/**
 * @file OperatorConsumer.hpp
 * 
 * This file houses the ItemConsumer which parses mathematical operators as they
 * arise.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>

/**
 * Local includes; specifically for this project go here
 */
#include "ItemConsumer.hpp"

namespace postfix
{

/**
 * @brief OperatorConsumer class which parses operators
 */
enum class Operator : long
{
    Add = 0,
    Subtract = 1,
    Multiply = 2,
    Divide = 3
};

class OperatorConsumer : public ItemConsumer<std::string>
{
private:

    Operator _item;

public:

    OperatorConsumer(const std::string& consumerName_);
    OperatorConsumer(const std::string& consumerName_, const std::string& buffer_);
    ~OperatorConsumer() = default;

    bool validate() override;
    void consume() override;

    const Operator& getItem();
};

}