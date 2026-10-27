/**
 * @file UInt32Consumer.cpp
 * @brief Implementation of the UInt32Consumer class.
 * 
 * This file contains the implementation of the UInt32Consumer class, which is
 * responsible for logging unsigned 32-bit integer values. The class provides
 * functionality to log these values to the console or to a file, depending on
 * the configuration. The specific implementation details and member functions
 * of the UInt32Consumer class are defined in this source file.
 */

#include "UInt32Consumer.hpp"

#include <charconv>
#include <limits>
#include <spdlog/spdlog.h>
#include <system_error>

namespace postfix
{

static_assert(std::numeric_limits<std::uint32_t>::digits == 32,
              "UInt32Consumer requires an exact 32-bit unsigned integer type");

UInt32Consumer::UInt32Consumer(const std::string& name_)
    : ItemConsumer<std::uint32_t>(name_)
{
}

UInt32Consumer::UInt32Consumer(const std::string& name_, const std::string& buffer_)
    : ItemConsumer<std::uint32_t>(name_, buffer_)
{
    consume();
}

bool UInt32Consumer::processBuffer()
{
    if (!validate())
    {
        return false;
    }

    consume();
    return true;
}

bool UInt32Consumer::parseBuffer(std::uint32_t& item_) const
{
    const std::string& buffer = getBuffer();
    const char* const begin = buffer.data();
    const char* const end = begin + buffer.size();
    const auto result = std::from_chars(begin, end, item_, 10);

    return !buffer.empty() &&
           result.ec == std::errc{} &&
           result.ptr == end;
}

bool UInt32Consumer::validate()
{
    std::uint32_t item{};
    const bool valid = parseBuffer(item);
    if (!valid)
    {
        spdlog::error("UInt32Consumer '{}' rejected invalid 32-bit unsigned integer buffer '{}'",
                      getName(), getBuffer());
    }

    return valid;
}

void UInt32Consumer::consume()
{
    std::uint32_t item{};
    if (!parseBuffer(item))
    {
        spdlog::error("UInt32Consumer '{}' cannot consume invalid 32-bit unsigned integer buffer '{}'",
                      getName(), getBuffer());
        return;
    }

    setItem(item);
    spdlog::debug("UInt32Consumer '{}' consumed value '{}'", getName(), item);
}

} // namespace postfix