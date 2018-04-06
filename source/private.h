
// purpose of this define:
// if we are in DEBUG mode, remove the static keyword so
// we can access the method from the test code.
#ifdef DEBUG
#define private
#else
#define private static
#endif
