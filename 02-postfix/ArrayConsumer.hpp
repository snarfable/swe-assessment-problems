/**
 * @file ArrayConsumer.hpp
 * 
 * The header file for a consumer which knows how to iterate through an array
 * and use the appropriate ItemConsumer subtype for each substring encountered.
 */

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <variant>

#include "ItemConsumer.hpp"

namespace postfix
{

template <typename ...T>
class ArrayConsumer
{

private:

    std::string _buffer;
    const std::string& _nextToken();

public:

    ArrayConsumer(const std::string& buffer_);
    ~ArrayConsumer() = default;

};

} // namespace postfix
