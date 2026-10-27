/**
 * @file OperatorConsumer.cpp
 * 
 * This file houses the implementation of the OperatorConsumer which generates
 * Operator values from string input.
 */

#include <iostream>
#include <iomanip>
#include <string>

#include <spdlog/spdlog.h>

// Local header files only (OperatorConsumer.hpp pulls in ItemConsumer.hpp)
#include "OperatorConsumer.hpp"

namespace postfix
{

namespace
{

/**
 * @brief Maps a single-character operator token to its Operator enum value.
 *
 * @param buffer_ The buffer holding the candidate operator token.
 * @param operator_ Receives the parsed Operator when the token is recognized.
 * @return true if the buffer holds a recognized operator, otherwise false.
 */
bool parseOperator(const std::string& buffer_, Operator& operator_)
{
    if (buffer_.size() != 1)
    {
        return false;
    }

    switch (buffer_.front())
    {
        case '+': operator_ = Operator::Add;      return true;
        case '-': operator_ = Operator::Subtract; return true;
        case '*': operator_ = Operator::Multiply; return true;
        case '/': operator_ = Operator::Divide;   return true;
        default:  return false;
    }
}

} // namespace

OperatorConsumer::OperatorConsumer(const std::string& name_)
    : ItemConsumer<std::string>{name_}
{
}

OperatorConsumer::OperatorConsumer(const std::string& consumerName_, const std::string& buffer_)
    : ItemConsumer<std::string>{consumerName_, buffer_}
{
}

bool OperatorConsumer::validate()
{
    Operator parsed{};
    const bool valid = parseOperator(getBuffer(), parsed);
    if (!valid)
    {
        spdlog::error("OperatorConsumer '{}' rejected invalid operator buffer '{}'",
                      getConsumerName(), getBuffer());
    }

    return valid;
}

void OperatorConsumer::consume()
{
    Operator parsed{};
    if (!parseOperator(getBuffer(), parsed))
    {
        spdlog::error("OperatorConsumer '{}' cannot consume invalid operator buffer '{}'",
                      getConsumerName(), getBuffer());
        return;
    }

    // Store the validated operator token in the base item so it is available
    // for streaming, and retain the parsed enum value in the derived item.
    setItem(getBuffer());
    _item = parsed;

    spdlog::debug("OperatorConsumer '{}' consumed operator '{}' (enum {})",
                  getConsumerName(), getBuffer(), static_cast<long>(_item));
}

const Operator& OperatorConsumer::getItem()
{
    return _item;
}

}
