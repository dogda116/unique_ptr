# unique_ptr
C++ unique_ptr base implementation as std::tuple<T * , Deleter>.

**Features:**
  * Template type of pointer's element
  * Constructs unique pointer with nullptr by default
  * Copy-constructor and move-constructor
  * Assignment operator and Move assignment operator
  * Destructor
  * Operators * and ->
  * Functions *release*, *reset*, *swap*, *get*, *get_deleter*
  * Operator bool() checks whether pointer is null
