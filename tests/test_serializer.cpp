#include <gtest/gtest.h>

#include "../include/BufferReader.hpp"
#include "../include/BufferWriter.hpp"

// Test 1: The Single Primitive
TEST(SerializationEngine, SingleInteger) {
  BufferWriter writer;
  uint32_t original = 0xDEADBEEF;

  writer.Write(original);

  BufferReader reader(writer.GetBytes());
  uint32_t extracted = reader.Read<uint32_t>();

  EXPECT_EQ(original, extracted);
}

// Test 2: The Sequential Payload
TEST(SerializationEngine, MultiTypePayload) {
  BufferWriter writer;
  int32_t id = 42;
  float velocity = 3.14f;
  char status = 'A';

  writer.Write(id);
  writer.Write(velocity);
  writer.Write(status);

  BufferReader reader(writer.GetBytes());

  EXPECT_EQ(reader.Read<int32_t>(), id);
  EXPECT_FLOAT_EQ(reader.Read<float>(), velocity);
  EXPECT_EQ(reader.Read<char>(), status);
}

// Test 3: The Malicious Packet
TEST(SerializationEngine, BufferUnderflowPrevention) {
  BufferWriter writer;
  uint16_t short_data = 0xFFFF;
  writer.Write(short_data);  // Writes exactly 2 bytes

  BufferReader reader(writer.GetBytes());

  // Attempting to read 4 bytes from a 2-byte buffer MUST throw
  EXPECT_THROW(reader.Read<uint32_t>(), std::out_of_range);
}