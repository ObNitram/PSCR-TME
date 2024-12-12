#pragma once

#ifdef NDEBUG
template <typename T>
constexpr void assert_message_template(T condition, const char *condition_str, const char *message,
                                       const char *file = __FILE__, const char *function = __FUNCTION__,
                                       const int line = __LINE__) noexcept
{
    (void)condition;
    (void)condition_str;
    (void)message;
    (void)file;
    (void)function;
    (void)line;
}
#else

#include <cstdlib>
#include <iostream>

template <typename T>
void assert_message_template(T condition, const char *condition_str, const char *message, const char *file = __FILE__,
                             const char *function = __FUNCTION__, int line = __LINE__)
{
    if (!condition)
    {
        std::cerr << "Assertion failed:(" << condition_str << ")->(" << condition << "), "
                  << "function " << function << ", file " << file << ", line " << line << "." << std::endl;
        std::cerr << "Message: " << message << std::endl;
        std::abort();
    }
}
#endif

#define assert_message(condition, message)                                                                             \
    assert_message_template(condition, #condition, message, __FILE__, __FUNCTION__, __LINE__)
