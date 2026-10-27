/**
 * @file UInt32Consumer.hpp
 * @brief Header file for the UInt32Consumer class.
 * 
 * This header file defines the UInt32Consumer class, which is responsible for
 * logging unsigned 32-bit integer values. The class provides functionality to
 * log these values to the console or to a file, depending on the configuration.
 * The specific implementation details and member functions of the UInt32Consumer
 * class will be defined in the corresponding source file (UInt32Consumer.cpp).
 */

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

/**
 * Header files local to this project. These headers contain the necessary
 * includes and declarations for the UInt32Consumer class, which is responsible
 * for logging unsigned 32-bit integer values. The class provides functionality
 * to log these values to the console or to a file, depending on the
 * configuration
 */
#include "ItemConsumer.hpp"

namespace postfix
{

/**
 * @brief The UInt32Consumer class is responsible for logging unsigned 32-bit integer values.
 * 
 * The class provides functionality to log these values to the console or to a file,
 * depending on the configuration. It inherits from the ItemConsumer class, which
 * provides a base interface for consuming and processing items of type uint32_t.
 */
class UInt32Consumer : public ItemConsumer<std::uint32_t>
{
private:
    bool parseBuffer(std::uint32_t& item_) const;

public:
    /**
     * @brief Constructs a new UInt32Consumer object with the given name.
     * @param name The name of the logger.
     */
    UInt32Consumer(const std::string& name);

    /**
     * @brief Constructs a consumer with an initial buffer to process.
     * @param name The name of the consumer.
     * @param buffer The decimal unsigned integer to process.
     */
    UInt32Consumer(const std::string& name_, const std::string& buffer_);

    /**
     * @brief Parses and consumes the unsigned 32-bit integer in the buffer.
     * @return true if the buffer contains a valid integer, otherwise false.
     */
    bool processBuffer();

    bool validate() override;
    void consume() override;

    /**
     * @brief Destroys the UInt32Consumer object and performs any necessary cleanup.
     * 
     * The destructor ensures that any resources allocated by the UInt32Consumer
     * are properly released. Since the class does not manage any dynamic
     * resources, the default destructor is sufficient for cleanup.
     */
    ~UInt32Consumer() = default;
};

} // namespace postfix
