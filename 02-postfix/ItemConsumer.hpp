#include <iostream>
#include <string>
#include <limits>
#include <numeric>
#include <jsoncpp/json/json.h>
#include <spdlog/spdlog.h>

namespace postfix
{

/**
 * ItemConsumer is an abstract class which defines the interface for consuming
 * items from a queue. It is designed to be inherited by concrete classes that
 * implement specific item consumption logic. The class provides a virtual
 * destructor to ensure proper cleanup of derived classes and may include
 * additional member functions and data members as needed for the specific
 * consumption behavior.
 */

namespace
{
    std::ostream& operator<<(std::ostream& os, const postfix::ItemConsumer<std::uint32_t>& consumer);
}

template <typename T>
class ItemConsumer
{
private:
    // Private data members and member functions can be defined here as needed.
    std::string _consumerName;
    std::string _buffer;
    T _item;

public:
    /**
     * @brief Constructs a new ItemConsumer object with the given name.
     *
     * @param consumerName The name of the consumer, used for identification and logging purposes.
     */
    ItemConsumer(const std::string& consumerName_) : _consumerName{consumerName_}, _buffer{}
    {
        spdlog::info("ItemConsumer '{}' initialized", _consumerName);
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
        spdlog::info("ItemConsumer '{}' initialized", _consumerName);
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

    const std::string& getBuffer() const
    {
        return _buffer;
    }

    const T& getItem() const
    {
        return _item;
    }

    /**
     * @brief Validates the given item for consumption.
     * 
     * @param item_ The item to be validated.
     * @return true if the item is valid for consumption, false otherwise.
     * 
     * The validate function is a pure virtual function that must be implemented
     * by derived classes. It is responsible for checking whether the provided
     * item meets the criteria for consumption. The specific validation logic
     * will depend on the requirements of the derived class and the type of
     * items being consumed.
     */
    virtual bool validate(const T& item_) = 0;

    virtual void consume(const T& item_) = 0;

    /**
     * @brief Virtual destructor for the ItemConsumer class.
     * The virtual destructor ensures that derived classes can be properly
     * cleaned up when an object of a derived class is deleted through a pointer to the base class. This is
     * important for preventing resource leaks and ensuring that any resources allocated by derived classes are released correctly.
     */
    virtual ~ItemConsumer() = default;

    friend std::ostream& operator<<(std::ostream& os, const ItemConsumer<std::uint32_t>& consumer)
    {
        os << "ItemConsumer Name: " << consumer._consumerName << ", Buffer: " << consumer._buffer;
        return os;
    }
};

}