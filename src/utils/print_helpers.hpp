#define SHOW(...) (std::cout << #__VA_ARGS__ << " // ", __VA_ARGS__, std::cout << std::endl)

#ifdef PRINT_PRETTY_FUNCTION
#define PPF(out) (out << "\n\033[7m/*" << __PRETTY_FUNCTION__ << " */\033[0m\n")
#else
#define PPF(out)
#endif