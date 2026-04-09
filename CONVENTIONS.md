# C++ Conventions and Best Practices (from learncpp.com)

Comprehensive extraction from all chapters (0-28, O, F).

---

## Naming

- Variable names should begin with lowercase letters
- Multi-word identifiers should use `snake_case` or `camelCase` — pick one and be consistent
- Name program-defined types (classes, structs, enums, type aliases) starting with a capital letter, no suffix
- Avoid starting identifiers with underscores (reserved for OS/library/compiler use)
- Choose descriptive names proportional to scope and specificity
- Avoid abbreviations except for common, unambiguous ones
- Name trivial type template parameters with single capital letters starting with `T` (e.g. `T`, `U`, `V`)
- Use descriptive names for non-obvious template parameters (e.g. `Allocator`, `TAllocator`)
- Use `N` as the name of an `int` non-type template parameter
- Name your enumerators starting with a lower case letter
- Consider using a `g` or `g_` prefix for global variables
- Consider using an `m_` prefix for private data members
- Use `s_` prefix for static (static duration) local variables
- Macro names should be all uppercase with underscores separating words

## Variables and Initialization

- Define each variable in a separate statement on its own line
- Always initialize your variables upon creation
- Prefer direct-list-initialization (braces `{}`) or value-initialization to initialize variables
- Define local variables as close to their first use as reasonable
- Variables used only inside a loop should be defined inside the loop scope
- Don't confuse assignment (`=`) with equality (`==`)

## Constants

- Make variables `const` whenever possible
- Place `const` before the type (`const int x`, not `int const x`)
- Don't use `const` for value parameters or by-value return types
- Prefer constant variables over object-like macros (`#define`)
- Any constant variable whose initializer is a constant expression should be `constexpr`
- Any constant variable whose initializer is NOT a constant expression should be `const`
- Prefer literal suffix `L` (uppercase) over `l` (lowercase)
- Avoid magic numbers — use `constexpr` variables instead

## Constexpr Functions

- A function that can be evaluated at compile-time should be made `constexpr` unless you have a reason not to
- A function that cannot be evaluated at compile-time should NOT be marked `constexpr`
- Use `consteval` when a function must evaluate at compile-time
- All constexpr functions should be evaluatable at compile-time
- Always test constexpr functions in a context that requires a constant expression
- Constexpr/consteval functions used in one source file: define in that file above first use
- Constexpr/consteval functions used in multiple files: define in a header file
- Compile-time evaluation of constexpr functions is only guaranteed when a constant expression is required

## Functions

- Don't forget parentheses `()` when calling a function
- Use function overloading to make your program simpler
- Keep nesting level of functions to 3 or less — refactor into sub-functions if deeper
- `main` should return `0` if the program ran normally
- Make sure functions with non-void return types return a value in all cases
- Do not put a `return` statement at the end of a non-value returning function
- Follow DRY: "Don't repeat yourself"
- When a function parameter exists but is unused, do not give it a name (optionally comment it)
- Prefer explicit return types over return type deduction
- If a function has a forward declaration, put default arguments there; otherwise in the definition
- Generally favor iteration over recursion
- When addressing compilation errors, resolve the first issue and recompile
- Keep forward declaration parameter names

## Function Parameters and Passing

- Pass fundamental types by value, class types by const reference
- Favor passing by const reference over non-const reference unless modification is needed
- Prefer `std::string_view` (by value) over `const std::string&` for string parameters
- Prefer pass by reference over pass by address unless you need null
- Prefer pointer-to-const parameters over pointer-to-non-const
- Favor references over pointers unless pointer capabilities are needed
- Avoid out-parameters; prefer return values
- Avoid ellipsis — use alternatives for stronger type checking

## Types and Casting

- Avoid C-style casts — always use C++ named casts
- Favor `static_cast` when converting between types
- Prefer `static_cast` over initializing a temporary object for conversions
- Avoid `const_cast` and `reinterpret_cast` unless you have a very good reason
- Avoid narrowing conversions whenever possible; use `static_cast` when needed
- Prefer type aliases (`using`) over `typedef`
- Use type deduction (`auto`) when the type doesn't matter; use explicit types when a specific type is required

## Data Types

- Use an empty parameter list instead of `void` to indicate no parameters
- Prefer shorthand integer types without `int` suffix or `signed` prefix
- Favor signed numbers over unsigned for quantities and math — avoid mixing signed/unsigned
- Use fixed-width integers (`std::int32_t`, etc.) when you need a guaranteed range
- Prefer `int` when size doesn't matter
- Avoid fast/least integral types, 8-bit fixed-width integers, and compiler-specific types
- `std::int8_t` and `std::uint8_t` may behave like chars — be careful
- Favor `double` over `float` unless space is at a premium
- Avoid division by `0.0`
- Always match literal types to variable types (`1.0f` for float, `1.0` for double)
- Single characters should be single-quoted (`'t'`), not double-quoted (`"t"`)
- Avoid multicharacter literals (e.g. `'56'`)
- If using `std::size_t` explicitly, `#include <cstddef>`

## Strings

- Prefer `std::string_view` over `std::string` for read-only strings
- Do not pass `std::string` by value (expensive copy)
- Use `std::cin >> std::ws` before `std::getline()` to ignore leading whitespace
- A `std::string_view` is dependent on the object being viewed — don't let the viewed object be destroyed while the view is in use
- Do not initialize `std::string_view` with a `std::string` literal (dangling)
- Don't assume `std::string_view` is null-terminated

## Header Files

- Use `.h` suffix for header files
- Paired header and source files should share the same base name (`add.h` / `add.cpp`)
- Do not put function or variable definitions in header files (except templates)
- Source files should `#include` their paired header file
- Never `#include` `.cpp` files
- Use double quotes `""` for your own headers, angle brackets `<>` for system/library headers
- Use standard library headers without `.h` extension (e.g. `<cstdint>` not `<stdint.h>`)
- Each file should explicitly `#include` everything it needs — don't rely on transitive includes
- Include order: (1) paired header, (2) project headers, (3) third-party headers, (4) standard library
- Give new code files a `.cpp` extension

## Header Guards

- All header files should have header guards
- Name guards using full filename in uppercase with underscores (e.g. `SQUARE_H`)
- For large projects, use `PROJECT_PATH_FILE_H` to avoid collisions
- Traditional `#ifndef`/`#define`/`#endif` guards are the most portable approach
- `#pragma once` is not defined by the C++ standard

## Namespaces and Scope

- Use explicit namespace prefixes to access identifiers
- Avoid `using namespace std;` (using-directives) at the top of programs or in headers
- Don't add custom functionality to the `std` namespace
- Define variables in the most limited existing scope
- Prefer unnamed namespaces to give identifiers internal linkage
- Avoid unnamed namespaces in header files
- Give identifiers internal linkage when you want to disallow access from other files
- Only use `extern` for global variable forward declarations or const global variable definitions
- Avoid non-const global variables — use local variables instead
- If you need global constants (C++17+), prefer inline constexpr in a header file
- Prefer explicit namespace qualifiers over using-statements (except `using namespace std::literals`)

## Inline

- Do not use the `inline` keyword to request inline expansion
- Avoid `inline` unless you have a specific reason (e.g. definitions in headers)
- Modern compilers decide inlining automatically

## Static Local Variables

- Initialize static local variables — they're only initialized on first execution
- Const static local variables are okay; non-const static local variables should generally be avoided

## Control Flow

- Favor `constexpr if` over non-constexpr if when the conditional is a constant expression
- Consider putting single statements after `if`/`else` in blocks (especially while learning)
- Don't terminate `if` statements with a semicolon accidentally
- Place the default case last in switch blocks
- Each case should end with `break` or `return`
- Use `[[fallthrough]]` attribute for intentional fallthrough
- If defining variables in a case, use a block inside the case
- Prefer not to indent switch labels
- Prefer `switch` over `if-else` when testing equality against a set of values
- Avoid `goto` unless alternatives are significantly worse
- Favor `while(true)` for intentional infinite loops
- Loop variables should be signed integral types
- Favor `while` loops over `do-while` when given equal choice
- Prefer `for` loops when there's an obvious loop variable, `while` otherwise
- Use `operator<` or `operator<=` in for-loop conditions, not `operator!=`
- Use `break` and `continue` when they simplify loop logic
- Use early returns when they simplify function logic

## Operators

- Use parentheses to clarify non-trivial compound expressions
- Parenthesize everything except `+`, `-`, `*`, `/`
- Don't depend on operand evaluation order
- Favor prefix `++`/`--` over postfix (more performant, fewer surprises)
- Don't use a variable with side effects more than once in a given statement
- Avoid the comma operator except in `for` loops
- Parenthesize the entire conditional operator when in compound expressions
- Don't add unnecessary `==` or `!=` to conditions
- Avoid `operator==`/`!=` on floating point values that have been calculated
- When mixing logical AND and OR, explicitly parenthesize each operation
- Avoid expressions with side effects in short-circuit evaluation

## Pointers

- Place the asterisk next to the type name when declaring pointers
- Always initialize your pointers
- Value-initialize pointers to null (`nullptr`) if not initializing with a valid address
- Use `nullptr` for null pointer literals
- A pointer should either hold a valid address or be `nullptr`
- When an object is destroyed, any pointers to it are left dangling — set them to `nullptr`
- Be extra careful not to dereference null or dangling pointers (undefined behavior)
- Set deleted pointers to `nullptr` unless going out of scope immediately
- Deleting a null pointer is okay — no need to conditionalize deletes

## References

- Place the ampersand next to the type when defining references
- Favor lvalue references to const over non-const unless modification is needed

## Return Values

- Avoid returning references to non-const local static variables
- Never return a local variable or temporary by reference (dangling reference)
- Prefer return by reference over return by address unless returning "no object" is needed
- Reference lifetime extension does not work across function boundaries

## Classes and OOP

- If a class has no data members, prefer a namespace instead
- Data members are initialized in order of declaration — don't depend on later members during initialization
- Structs should avoid defining constructors (makes them non-aggregate)
- Classes should make member variables private (or protected), functions public
- Structs should avoid using access specifiers (default to public)
- Declare public members first, protected next, private last
- A member function that does not modify the object should be `const`
- Getters should return by value (cheap copies) or const lvalue reference (expensive copies)
- Prefer implementing functions as non-members when possible
- Use member functions when you must (constructors, destructors, virtual functions, certain operators)
- Prefer member initializer lists over assignment in constructor bodies
- Member variables in initializer lists should match declaration order
- Prefer value initialization over default initialization for class types
- Prefer explicitly defaulted default constructor (`= default`) over empty body
- Use delegating constructors to reduce duplicate code
- Members the user must initialize: define first (leftmost constructor params). Optional: define second (rightmost)
- Make single-argument constructors `explicit` by default
- Do not make copy or move constructors explicit
- Copy constructors should have no side effects beyond copying; prefer implicit copy constructors
- If writing your own copy constructor, the parameter should be `const` lvalue reference
- Prefer `static_cast` for fundamental type conversions, list-initialized temporary for class type conversions
- If your class can be evaluated at compile-time, make member functions and constructors `constexpr`

## Classes and Header Files

- Put class definitions in a header with the same name as the class
- Define trivial member functions inside the class; non-trivial ones in a `.cpp` file
- Put default arguments for member functions inside the class definition
- Define nested types at the top of your class
- Member function templates defined outside the class should be just below the class in the same file

## Static Members

- Access static members using the class name and `::`
- Make static members `inline` or `constexpr` for in-class initialization

## Friends

- A friend function should prefer the class interface over direct member access
- Prefer non-friend functions when possible

## Destructors

- `std::exit()` does not call destructors for local variables — be wary
- Use parentheses-based initialization for array/container classes with a length parameter

## Data Hiding and Encapsulation

- Prefer non-member functions for application-specific logic
- Use member functions only when needed (access to private data, constructors, virtual functions)

## Operator Overloading

- Overloaded operators should operate on at least one program-defined type
- Keep overloaded operator behavior close to the original intent
- If the meaning isn't clear and intuitive, use a named function instead
- Operators that don't modify operands (e.g. `+`) should return by value
- Operators that modify the left operand (e.g. `+=`) should return by reference
- Prefer overloading as normal functions instead of friends when possible
- Only define overloaded operators that make intuitive sense for your class
- Mark typecasts as `explicit` except for synonymous types
- Prefer converting constructors over overloaded typecasts
- Use self-assignment guard (`if (this == &source)`) in assignment operators
- Assignment operators should return `*this`
- Consider copy-and-swap idiom for robust assignment
- Don't overload `operator()` beyond indexing or functors

## Subscript Operator

- Don't try to call `operator[]` on a pointer to an object

## Rule of Three

- If a class needs a custom destructor, copy constructor, or copy assignment, it probably needs all three
- Favor `std::string` and `std::vector` over manual memory management

## Templates

- Template definitions must be in header files (compiler needs full definition)
- Templates needed in multiple files should be defined in a header
- Favor normal function call syntax over explicit template arguments when possible
- Use function templates for generic code that works with many types
- Feel free to use abbreviated function templates with `auto` (C++20+)
- Full template specializations are not implicitly inline — mark them `inline` in headers
- Avoid function template specializations in favor of non-template functions when possible

## Enumerations

- Favor scoped enumerations (`enum class`) over unscoped enumerations
- Prefer putting enumerations inside a named scope (namespace or class)
- Avoid assigning explicit values unless you have a compelling reason
- Make enumerator `0` the best default; if none exists, add an "invalid"/"unknown" enumerator
- Specify the enum base type only when necessary
- Avoid unnamed enumerations in modern C++

## Structs

- Prefer braced list initialization for aggregates
- When adding members to an aggregate, add to the bottom to avoid shifting initializers
- Provide default values for all members
- Prefer value initialization (empty braces `{}`) over default initialization (no braces) for aggregates
- Structs should prefer to be owners (use owning types, not viewers/pointers/references)
- Minimize struct padding by defining members in decreasing order of size
- Use `->` (not `.`) when accessing members through a pointer

## Arrays and Containers

- Use `std::array` for constexpr arrays, `std::vector` for non-constexpr arrays
- Define `std::array` as `constexpr` whenever possible
- Use CTAD to deduce `std::array` type and length from initializers
- Avoid array indexing with integral values whenever possible
- Favor range-based for loops over regular for-loops for containers
- Use `auto` for element type deduction in range-based for: `auto` (modify copies), `auto&` (modify originals), `const auto&` (read-only)
- Prefer `emplace_back()` when creating temporaries to add; `push_back()` otherwise
- Favor `constexpr std::bitset`, `std::vector<char>`, or 3rd party over `std::vector<bool>`
- Use `static_assert` for constexpr array lengths, `assert` for non-constexpr
- Use standard enum inside namespace rather than enum class for frequent integral conversions
- Prefer omitting length of C-style arrays when explicitly initializing every element
- Avoid C-style arrays whenever practical — prefer `std::array`, `std::vector`, `std::string`, `std::string_view`
- Favor `std::array` or `std::vector` over smart pointers for managing arrays

## Iterators and Algorithms

- With iterators, use `operator!=` (not `<`) to test for end
- Favor standard library algorithms over writing your own
- Check an algorithm's performance and execution order guarantees before using

## Lambdas

- Prefer lambdas for trivial, one-off functions passed as arguments
- Store lambdas in variables using `auto`
- Use regular functions for non-trivial, reusable cases
- Be careful capturing variables by reference — they must outlive the lambda
- Try to avoid mutable lambdas
- Only initialize capture variables when their value is short and type is obvious

## Smart Pointers

- Avoid `std::auto_ptr` (removed in C++17)
- Use `std::unique_ptr`, `std::shared_ptr`, or `std::weak_ptr`
- Use `std::make_unique()` instead of `new` with `std::unique_ptr`
- Use `std::make_shared()` for shared pointers
- Return `std::unique_ptr` by value, not by pointer or reference
- Pass raw pointers or references to functions, not `std::unique_ptr`
- Always copy an existing `std::shared_ptr` if you need another one pointing to the same resource

## Move Semantics

- Move constructors and move assignment should be `noexcept`
- Make copy constructors and copy assignment `noexcept` when you can

## Inheritance

- Favor private members over protected members
- Use public inheritance unless you have a reason not to
- Avoid multiple inheritance unless alternatives are more complex
- If your base class has virtual functions, the destructor should be virtual
- Never call virtual functions from constructors or destructors
- Use `virtual` on base class functions, `override` (not `virtual`) on derived class overrides
- All virtual overrides should use the `override` specifier
- Make explicit destructors virtual when dealing with inheritance
- A base class destructor should be either public+virtual or protected+non-virtual
- If a class isn't meant to be inherited from, mark it `final`
- Any class with pure virtual functions should have a virtual destructor
- Always check for null after `dynamic_cast`

## Exceptions

- Favor `static_assert` over `assert()` whenever possible
- Catch class-type exceptions by (const) reference, fundamental types by value
- List handlers for derived exceptions before base exceptions
- When rethrowing, use `throw;` (not `throw e;`)
- Use function try blocks for constructor member initializer list exceptions
- If an exception is thrown from a destructor during stack unwinding, the program halts
- Always make move constructors, move assignment, and swap `noexcept`
- Use `noexcept` to express no-fail/no-throw guarantees
- If uncertain about no-throw guarantee, don't mark `noexcept`
- Consider a catch-all handler in main for unhandled exceptions
- Only use halts if no safe way to return from main; prefer exceptions for error handling
- `std::exit()` does not clean up local variables

## Testing

- Write in small, well-defined units; compile often; test as you go
- Aim for 100% branch coverage
- Use the 0, 1, 2 test for loops
- Test different categories of input values
- Use assertions for programming errors; error handling for expected issues

## Bit Manipulation

- Bit manipulation is one of the few times to use unsigned integers or `std::bitset`
- Use bitwise operators with unsigned integral operands or `std::bitset`
- Avoid bit shifting on types smaller than `int`

## I/O

- Prefer `\n` over `std::endl`
- Output a newline whenever a line of output is complete
- Output manipulators are sticky — once set, they remain

## File I/O

- In text files, seeking to positions other than the beginning may produce unexpected behavior
- Do not write memory addresses to files
- `fstream` may fail with `std::ios::in` if the file doesn't exist — use `std::ios::out` only for new files

## Formatting and Style

- Keep lines to 80 characters or less
- Be consistent with existing project style
- Use automatic formatting tools
- When working in an existing program, follow its conventions even if not modern best practice

## Program Design

- Plan structure before coding
- Define your goal in one or two sentences
- Implement and test one function at a time
- Start simple, add features incrementally
- Optimize for maintainability over premature performance
- Use version control
- Add one piece at a time, compile, and test — don't write everything at once
- Comment your code as if speaking to someone who has no idea what the code does

## Object Relationships

- Implement the simplest relationship type that meets your needs
- Each class should accomplish a single task
- Use standard library containers instead of writing your own when possible
- When providing list construction, also provide list assignment
- Adding a list constructor to an existing class may silently change existing behavior

## Miscellaneous Warnings

- `std::exit()` causes immediate termination without local cleanup
- Be careful with `static` duration objects depending on each other across translation units
- Avoid `std::auto_ptr`
- `operator~` and `operator<<` are width-sensitive — `static_cast` results back to narrower types
