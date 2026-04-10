#include <cstring>

class BufferReader {
 public:
  /* constructor, member-initialization list for initializing members after :
   *  Member variables in a member initializer list should be listed in order
   * that they are defined in the class.
   */
  BufferReader(const std::vector<uint8_t>& bytes)
      : m_bytes(bytes), m_offset{0} {}

  template <typename T>
  T Read() {
    static_assert(std::is_trivially_copyable_v<T>, "Can't read type");

    // check if enough space to read the type in the bytes
    if (m_offset + sizeof(T) > m_bytes.size()) {
      throw std::out_of_range("Buffer underflow");
    }

    T data{};
    memcpy(&data, &m_bytes[m_offset], sizeof(T));

    m_offset += sizeof(T);

    return data;
  }

 private:
  size_t m_offset;
  const std::vector<uint8_t>& m_bytes;
};