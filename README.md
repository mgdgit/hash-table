# Hash Table

A simple key-value data structure implemented from scratch over a raw array, without using C++ native map collections. It also implements an automatic mechanism that resizes the underlying array when a certain Load Factor is reached.

## Tech Used
- **Language:** C++ (C++17)
- **Tools/Libraries:** GNU Make, G++ Compiler, and C++ Standard Library (`<iostream>`, `<string>`, `<optional>`, `<stdexcept>`). No external dependencies.

## How to Run
```bash
# build (compiles the project using the Makefile)
make

# run (executes the compiled program)
make run
```

## How It Works (Simple)

1. **Hashing & Mapping:** When you insert a `PlanetCard`, the program takes the planet's name (the key), applies a polynomial hash algorithm to convert the text into a numeric value, and uses the modulo operator (`%`) to map it to a specific index within the array's current bounds.
2. **Collision Resolution:** If two planet names map to the exact same index (a collision), the hash table uses **Linear Probing** to find the next available empty slot. When a card is deleted, it uses **Lazy Deletion** (marking the slot as `DELETED` instead of emptying it completely) to ensure that future searches for cards that collided in that area don't break prematurely.
3. **Dynamic Resizing (Rehashing):** Upon every insertion, the table calculates its **Load Factor** (current elements / total size). If the array becomes more than 70% full (`> 0.7`), it automatically allocates a new array double the size, re-calculates the positions (rehashes) of all active cards, and deletes the old array to maintain O(1) fast lookups.

## Next Improvements

- **Decouple I/O from Data Structure:** Currently, the `HashTable` methods (like `insertCard` or `searchCard`) use `std::cout` to print messages directly. A good practice is to return booleans, values, or throw exceptions, and let the `main.cpp` (the UI layer) handle all the console printing.
- **Implement Generic Templates:** Refactor the class to use C++ templates (e.g., `HashTable<KeyType, ValueType>`). Right now, it is hardcoded strictly to handle `PlanetCard` structs, but making it generic would allow it to store any kind of data.
- **Dynamic Shrinking:** The table currently doubles in size when it gets full, but it never shrinks. Implementing a shrink-on-delete feature (e.g., halving the size if the load factor drops below 20%) would optimize memory usage after massive deletions.

## What I Learned

### Core
- A **hash function** is a mathematical algorithm that receives a set of data (bytes) and returns an integer. That number can be represented in base 2, 10, 16, etc., depending on what's needed.
- There are different types of hash functions, and each one is chosen depending on the task at hand. The one implemented in this program is the **Polynomial Rolling Hash** variant.
  - This variant takes a string and returns an integer that, in this context, will serve as an array index. Iteratively, a counter is multiplied by a number like 31 or 53, and then the ASCII value of the current letter of the string is added. After iterating through the entire string, the modulo operator is applied using the array's size to get an index within the available range.
  - Multiplying by a prime number like 31 greatly helps reduce collisions (though not entirely). For example, two strings with the same letters (`"amor"` and `"roma"`) could end up with the same index if the multiplication is omitted.
- Using this variant is highly convenient because it improves the speed of inserting and searching for elements within the array. Instead of iterating through everything (`O(n)`), the retrieved index is accessed directly in an average time complexity of `O(1)`.
- **Linear Probing** is a very simple technique used to resolve **collisions**. When the hash function calculates an index for a new element, but that position in the array is already occupied, the algorithm simply searches linearly (adding 1 to the index) until it finds the next available slot and inserts it there.
- The **Load Factor** is an indicator that measures how full our array is. It is calculated by dividing the number of inserted elements by the total capacity. If this value crosses a set threshold (for example, `0.7` or 70% occupancy), it warns us that the array is getting too full and the risk of collisions is too high.
- **Rehashing** is the rescue process that occurs when the Load Factor is exceeded. It consists of creating a new array, usually double the size of the original one, to get more space and return to normal operation.
  - **How does it work?** It's not enough to simply copy the elements over to the new array. By increasing the array's size, the number we use for the "modulo" operation in our hash function changes. Therefore, the **rehashing function** takes each element from the old array, recalculates its new index (using the new capacity), and relocates it into the new array.

### Secondaries
- **File separation**: In C++, it is a great practice to split the structure into two parts. Header files (`.h` or `.hpp`) are used only to "declare" what classes, variables, and functions will exist, while source files (`.cpp`) contain the actual "implementation" or logic of those functions. This keeps the code organized and speeds up compilation time.
- **Structs**: A `struct` (structure) is a way to bundle variables of different types under a single name. For example, a `struct Person` could contain a text (name) and a number (age). In C++, they are almost identical to classes, with the main difference being that their members are public by default.
- **Naming conventions**: To keep the code readable, `camelCase` or `snake_case` is commonly used for variables and functions. For **global variables** (those accessible from anywhere in the code), it is customary to use the `g_` prefix (e.g., `g_counter`) to identify them immediately and avoid modifying them by accident.
- **Exception handling**: To prevent the program from crashing due to an error, `try...catch` blocks are used. The risky code is placed inside the `try` block, and if something goes wrong, the program "throws" (`throw`) an error that is peacefully caught and handled inside the `catch` block.
- **The `&` symbol (References)**: It is used to pass a variable to a function by "reference" rather than by "copy". Meaning, instead of creating a clone of the variable, we give the function direct access to the original one. This saves memory and allows any changes made inside the function to be reflected outside.
- **Pointers and `new`**: A pointer is a special variable that, instead of storing standard data, stores the "memory address" of other data. The `new` keyword is used alongside pointers to dynamically request memory from the operating system while the program is running. Any memory requested with `new` must be manually freed later (using `delete`).
- **`static_cast`**: This is the safe and modern way in C++ to convert one data type to another (for example, from a decimal number to an integer). It is preferred because the compiler checks that the conversion makes sense before running the program.
- **Validating numeric inputs**: When asking the user for numbers using `std::cin`, they might type letters by mistake. To handle this, we check if the input is not a number. If it's not, we clear the console's error state (`std::cin.clear()`) and ignore the garbage the user typed (`std::cin.ignore()`), allowing us to safely ask for the number again.
