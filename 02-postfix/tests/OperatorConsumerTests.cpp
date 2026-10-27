#include "OperatorConsumer.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

namespace
{

TEST(OperatorConsumerTests, ValidatesSupportedSingleCharacterOperators)
{
    for (const std::string& buffer : {"+", "-", "*", "/"})
    {
        postfix::OperatorConsumer consumer("operator-test", buffer);
        EXPECT_TRUE(consumer.validate()) << "buffer: " << buffer;
    }
}

TEST(OperatorConsumerTests, RejectsUnsupportedBuffers)
{
    for (const std::string& buffer : {
             "",
             "++",
             "add",
             "x",
             "-1",
             "1",
             " +",
             "+ ",
             " ",
         })
    {
        postfix::OperatorConsumer consumer("operator-test", buffer);
        EXPECT_FALSE(consumer.validate()) << "buffer: " << buffer;
    }
}

TEST(OperatorConsumerTests, ConsumeParsesOperatorAndTracksEnumValue)
{
    postfix::OperatorConsumer consumer("operator-test", "/");

    ASSERT_TRUE(consumer.validate());
    consumer.consume();

    EXPECT_EQ(consumer.getBuffer(), "/");
    EXPECT_EQ(consumer.getItem(), postfix::Operator::Divide);
}

TEST(OperatorConsumerTests, StreamInsertionEmitsOperatorSymbolInValueMode)
{
    postfix::OperatorConsumer consumer("operator-test", "*");
    std::ostringstream oss;

    consumer.consume();
    oss << postfix::value << consumer;

    EXPECT_EQ(oss.str(), "*");
}

} // namespace
