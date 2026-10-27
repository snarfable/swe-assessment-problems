#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <numeric>
#include <jsoncpp/json/json.h>
#include <spdlog/spdlog.h>

/** @brief Index for storing output format state for ItemConsumer in std::ios_base. */
static const int item_output_index = std::ios_base::xalloc();

namespace postfix
{
    template<typename T>
    class ItemConsumer;
    enum class ItemConsumerFormat : long
    {
        Value = 0,
        Detail = 1
    };

    /**
     * @brief Stream manipulator to set ItemConsumer output mode.
     * @param os The output stream.
     * @return Reference to the output stream.
     */
    inline std::ostream &value(std::ostream &os)
    {
        os.iword(item_output_index) = static_cast<long>(postfix::ItemConsumerFormat::Value);
        return os;
    }

    /**
     * @brief Stream manipulator to set Point output format to Spherical coordinates.
     * @param os The output stream.
     * @return Reference to the output stream.
     */
    inline std::ostream &detail(std::ostream &os)
    {
        os.iword(item_output_index) = static_cast<long>(postfix::ItemConsumerFormat::Detail);
        return os;
    }
}

/**
 * @brief Stream manipulator to set ItemConsumer output format to value or detail.
 * @param os The output stream.
 * @return Reference to the output stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const postfix::ItemConsumer<T>& consumer)
{
    // Determine the current output format for ItemConsumer
    postfix::ItemConsumerFormat fmt = static_cast<postfix::ItemConsumerFormat>(os.iword(item_output_index));

    // Output the processed value alone if consumer format is set to Value,
    // otherwise output the consumer name and buffer if format is set to Detail
    if (fmt == postfix::ItemConsumerFormat::Value)
    {
        os << consumer.getItem();
    }
    else if (fmt == postfix::ItemConsumerFormat::Detail)
    {
        os << "ItemConsumer Name: " << consumer.getConsumerName() << ", Buffer: " << consumer.getBuffer() << ", Item: " << consumer.getItem();
    }
    else
    {
        spdlog::warn("Unknown ItemConsumer format, defaulting to Value output");
    }

    return os;
}

namespace postfix
{

/**
 * ItemConsumer is an abstract class which defines the interface for consuming
 * items from a queue. It is designed to be inherited by concrete classes that
 * implement specific item consumption logic. The class provides a virtual
 * destructor to ensure proper cleanup of derived classes and may include
 * additional member functions and data members as needed for the specific
 * consumption behavior.
 * 
 * @template T The type of item to be consumed.
 * 
 * This allows for flexibility in the types of items that can be processed by
 * different implementations of the ItemConsumer class.
 */
template <typename T>
class ItemConsumer
{
private:
    // Private data members and member functions can be defined here as needed.
    std::string _consumerName;
    std::string _buffer;
    T _item;

protected:
    void setItem(const T& item_)
    {
        _item = item_;
    }

public:
    /**
     * @brief Constructs a new ItemConsumer object with the given name.
     *
     * @param consumerName The name of the consumer, used for identification and logging purposes.
     */
    ItemConsumer(const std::string& consumerName_) : _consumerName{consumerName_}, _buffer{}
    {
        spdlog::debug("ItemConsumer '{}' initialized", _consumerName);
        spdlog::debug("ItemConsumer '{}' buffer initialized to empty string", _consumerName);
    }

    /**
     * @brief Overloaded constructor which initializes the ItemConsumer with a name and a buffer.
     *
     * @param consumerName The name of the consumer, used for identification and logging purposes.
     * @param buffer The initial buffer content.
     * 
     * This constructor allows for the initialization of the ItemConsumer with a
     * specific buffer content, which can be useful for scenarios where the
     * consumer needs to start with predefined data.
     */
    ItemConsumer(const std::string& consumerName_, const std::string& buffer_) : _consumerName{consumerName_}, _buffer{buffer_}
    {
        spdlog::debug("ItemConsumer '{}' initialized", _consumerName);
        spdlog::debug("ItemConsumer '{}' buffer initialized to '{}'", _consumerName, _buffer);
    }

    /**
     * @brief Returns the name of the consumer.
     * 
     * @return The name of the consumer as a string.
     * 
     * This function provides access to the name of the consumer, which can be
     * useful for logging, debugging, and identification purposes. The name is
     * set during the construction of the ItemConsumer object and remains
     * constant throughout its lifetime.
     */
    const std::string& getConsumerName() const
    {
        return _consumerName;
    }

    /**
     * @brief Returns the current buffer content of the consumer.
     * 
     * @return The buffer content as a string.
     * 
     * This function provides access to the buffer content of the consumer,
     * which can be useful for logging, debugging, and identification purposes.
     * The buffer content is set during the construction of the ItemConsumer
     * object and can be modified through other member functions.
     */
    const std::string& getBuffer() const
    {
        return _buffer;
    }

    /**
     * @brief Returns the current item being consumed.
     * 
     * @return The current item of type T.
     * 
     * This function provides access to the current item being consumed by the
     * consumer. The item is of type T, which allows for flexibility in the
     * types of items that can be processed by different implementations of the
     * ItemConsumer class. The item can be set and modified through other member
     * functions, and this function allows for retrieval of the current state of
     * the item.
     */
    virtual const T& getItem() const
    {
        return _item;
    }

    /**
     * @brief Validates the consumer's internal buffer.
     * @return true if the buffer contains a valid item, false otherwise.
     */
    virtual bool validate() = 0;

    /**
     * @brief Consumes the consumer's internal buffer.
     */
    virtual void consume() = 0;

    /**
     * @brief Virtual destructor for the ItemConsumer class.
     * 
     * The virtual destructor ensures that derived classes can be properly
     * cleaned up when an object of a derived class is deleted through a pointer
     * to the base class. This is important for preventing resource leaks and
     * ensuring that any resources allocated by derived classes are released
     * correctly.
     */
    virtual ~ItemConsumer() = default;

};

}