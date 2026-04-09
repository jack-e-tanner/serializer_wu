#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <vector>

/*
Classes should generally make member variables private (or protected), and
member functions public.

Structs should generally avoid using access specifiers (all members will default
to public).

A class defaults its members to private, whereas a struct defaults its members
to public.
*/
class Serializer {
 public:
  /*
   * Like generics in rust, T is type
   * const means you won't edit the data in it
   * T& means pass by reference (no copying)
   * Whether T& or T, data acts as the whole struct and &data gets its address
   * The difference: T& points to the original, T copies it — bytes are the same
   * Function to serialize whatever is given to it
   */
  template <typename T>
  void serialize(const T& data) {
    m_bytes.resize(sizeof(T));
    const uint8_t* raw_data = reinterpret_cast<const uint8_t*>(&data);

    std::copy(raw_data, raw_data + sizeof(T), m_bytes.begin());
  }

  /*
   * Function to deserialize m_bytes into data
   */
  template <typename T>
  T deserialize() {
    T data{};

    std::copy(m_bytes.begin(), m_bytes.end(),
              reinterpret_cast<uint8_t*>(&data));

    return data;
  }

  // const means it won't modify the object at all

  void print_bytes() const {
    for (size_t i = 0; i < m_bytes.size(); i++) {
      printf("%02x", m_bytes[i]);
    }

    printf("\n");
  }

  const std::vector<uint8_t>& getBytes() const { return m_bytes; }

 private:
  std::vector<uint8_t> m_bytes{};
};

#endif