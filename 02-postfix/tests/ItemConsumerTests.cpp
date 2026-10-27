#include "ItemConsumer.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

namespace
{

class TestItemConsumer final : public postfix::ItemConsumer<std::uint32_t>
{
public:
    using ItemConsumer::ItemConsumer;

    bool validate() override
    {
        return !getBuffer().empty();
    }

    void consume() override
    {
        setItem(42);
    }
};

TEST(ItemConsumerTests, IsAbstract)
{
    static_assert(std::is_abstract<postfix::ItemConsumer<std::uint32_t>>::value,
                  "ItemConsumer should require concrete validate and consume methods");
}

TEST(ItemConsumerTests, ExposesConstructorStateAndRunsDerivedMethods)
{
    TestItemConsumer consumer("test-consumer", "buffer");

    EXPECT_EQ(consumer.getConsumerName(), "test-consumer");
    EXPECT_EQ(consumer.getBuffer(), "buffer");
    EXPECT_TRUE(consumer.validate());

    consumer.consume();
    EXPECT_EQ(consumer.getItem(), 42U);
}

TEST(ItemConsumerTests, DefaultBufferCanBeValidatedByDerivedConsumer)
{
    TestItemConsumer consumer("test-consumer");

    EXPECT_TRUE(consumer.getBuffer().empty());
    EXPECT_FALSE(consumer.validate());
}

} // namespace
