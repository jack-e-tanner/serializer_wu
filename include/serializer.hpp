#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <type_traits>
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