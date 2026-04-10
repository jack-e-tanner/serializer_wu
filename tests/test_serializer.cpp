#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>
#include <vector>

// These headers do not exist yet. You must write them.
#include "../include/BufferReader.hpp"
#include "../include/BufferWriter.hpp"

// ---------------------------------------------------------
// Phase 1: Primitive Round-Trip Tests
// ---------------------------------------------------------

TEST(SerializerTest, RoundTripUint32) {
  BufferWriter writer;
  uint32_t original_value = 402834;

  writer.WriteUint32(original_value);
  std::vector<uint8_t> buffer = writer.GetBuffer();

  // A uint32_t must be exactly 4 bytes.
  ASSERT_EQ(buffer.size(), 4) << "Buffer size is incorrect for uint32_t.";

  BufferReader reader(buffer);
  uint32_t deserialized_value = reader.ReadUint32();

  EXPECT_EQ(original_value, deserialized_value)
      << "Data corruption during uint32_t round-trip.";
}

TEST(SerializerTest, RoundTripFloat) {
  BufferWriter writer;
  float original_value = -134.567f;

  writer.WriteFloat(original_value);
  std::vector<uint8_t> buffer = writer.GetBuffer();

  ASSERT_EQ(buffer.size(), 4) << "Buffer size is incorrect for float.";

  BufferReader reader(buffer);
  float deserialized_value = reader.ReadFloat();

  EXPECT_FLOAT_EQ(original_value, deserialized_value)
      << "Floating point corruption detected.";
}

// ---------------------------------------------------------
// Phase 2: Boundary and Limit Tests
// ---------------------------------------------------------

TEST(SerializerTest, NumericLimits) {
  BufferWriter writer;
  uint32_t max_int = std::numeric_limits<uint32_t>::max();

  writer.WriteUint32(max_int);

  BufferReader reader(writer.GetBuffer());
  uint32_t result = reader.ReadUint32();

  EXPECT_EQ(max_int, result) << "Failed to round-trip maximum uint32_t value.";
}

// ---------------------------------------------------------
// Phase 3: Defensive Programming (Exception Handling)
// ---------------------------------------------------------

TEST(SerializerTest, ReadPastBufferThrowsException) {
  BufferWriter writer;
  writer.WriteUint32(100);  // Writes 4 bytes

  BufferReader reader(writer.GetBuffer());
  reader.ReadUint32();  // Consumes the 4 bytes. Write head is at the end.

  // Attempting to read another float (4 bytes) when empty MUST throw.
  EXPECT_THROW(
      { reader.ReadFloat(); }, std::out_of_range)
      << "BufferReader failed to throw std::out_of_range on buffer overflow.";
}