#include "UInt32Consumer.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>
#include <sstream>

namespace
{

TEST(UInt32ConsumerTests, ValidatesUnsigned32BitDecimalValues)
{
    for (const std::string& buffer : {"0", "42", "4294967295"})
    {
        postfix::UInt32Consumer consumer("uint32-test", buffer);
        EXPECT_TRUE(consumer.validate()) << "buffer: " << buffer;
    }
}

TEST(UInt32ConsumerTests, RejectsEmptyMalformedAndOutOfRangeBuffers)
{
    for (const std::string& buffer : {
             "", "-1", "+1", "4294967296", "12x", " 12", "12 ",
             "18446744073709551616"})
    {
        postfix::UInt32Consumer consumer("uint32-test", buffer);
        EXPECT_FALSE(consumer.validate()) << "buffer: " << buffer;
    }
}

TEST(UInt32ConsumerTests, ProcessBufferStoresParsedValue)
{
    postfix::UInt32Consumer consumer("uint32-test", "4294967295");

    ASSERT_TRUE(consumer.processBuffer());
    EXPECT_EQ(consumer.getItem(), std::numeric_limits<std::uint32_t>::max());
}

TEST(UInt32ConsumerTests, ProcessBufferRejectsInvalidInput)
{
    postfix::UInt32Consumer consumer("uint32-test", "4294967296");

    EXPECT_FALSE(consumer.processBuffer());
}

TEST(UInt32ConsumerTests, ConsumeParsesAndStoresInternalBuffer)
{
    postfix::UInt32Consumer consumer("uint32-test", "1234");

    consumer.consume();

    EXPECT_EQ(consumer.getItem(), 1234U);
}

TEST(UInt32ConsumerTests, StreamInsertionProcessWorks)
{
    postfix::UInt32Consumer consumer("uint32-test", "1723");
    std::ostringstream oss1, oss2;

    consumer.consume();
    oss1 << postfix::value << consumer;
    oss2 << postfix::detail << consumer;

    EXPECT_EQ(oss1.str(), std::string("1723"));
    EXPECT_EQ(oss2.str(), std::string("ItemConsumer Name: uint32-test, Buffer: 1723, Item: 1723"));
}

} // namespace
