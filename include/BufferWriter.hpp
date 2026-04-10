#include <cstdint>
#include <vector>

class BufferWriter {
 public:
  /*
   * const means you won't edit the data in it
   * T& means pass by reference (no copying) so it's an alias of it
   * Whether T& or T, data acts as the whole struct and &data gets its address
   * The difference: T& points to the original, T copies it — bytes are the
   * same
   *
   * Function to serialize whatever is given to it
   */
  template <typename T>
  void Write(const T& data) {
    static_assert(std::is_trivially_copyable_v<T>, "Type can't be written");

    const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&data);

    m_bytes.insert(m_bytes.end(), ptr, ptr + sizeof(T));
  }

  const std::vector<uint8_t>& GetBytes() const { return m_bytes; }

 private:
  std::vector<uint8_t> m_bytes{};
};