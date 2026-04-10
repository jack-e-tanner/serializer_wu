#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <vector>

/*
Classes should generally make member variables private (or protected), and
member functions public.

Structs should generally avoid using access specifiers (all members will default
to public).

A class defaults its members to private, whereas a struct defaults its members
to public.

Prefer implementing functions as non-members when possible (especially functions
that contain application specific data or logic).

Declare public members first, protected members next, and private members last.
This spotlights the public interface and de-emphasizes implementation details.
*/
class Serializer {
 public:
  // constructor, member-initialization list for initializing members after :
  // Member variables in a member initializer list should be listed in order
  // that they are defined in the class.
  Serializer(size_t initial_size = m_default_size) : m_bytes(initial_size) {}

  /*
   * Like generics in rust, T is type
   * const means you won't edit the data in it
   * T& means pass by reference (no copying)
   * Whether T& or T, data acts as the whole struct and &data gets its address
   * The difference: T& points to the original, T copies it — bytes are the
   * same Function to serialize whatever is given to it
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
    if (m_bytes.size() != sizeof(T)) {
      throw std::runtime_error(
          "Can't deserialize, buffer size doesn't match type size");
    }

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

  void clear_bytes() { m_bytes.clear(); }

  size_t size() { return m_bytes.size(); }

 private:
  // static so this var is shared across all objects (not copied) and constexpr
  // so known at compile-time
  static constexpr size_t m_default_size{0};

  std::vector<uint8_t> m_bytes{};
};

#endif

/* THINGS TO ADD
Operator overloading — overload << so you can do std::cout <<
serializer to print the bytes
Multiple fields — serialize more than one object into the same buffer (append
instead of overwrite) Inheritance — base Serializer class, derived
FileSerializer that writes/reads bytes to/from a file Rule of Five — custom
destructor, copy constructor, copy assignment, move constructor, move assignment
static method — a factory like Serializer::fromBytes(std::vector<uint8_t>) that
constructs a Serializer from existing data friend functions — give the <<
overload access to private members
*/