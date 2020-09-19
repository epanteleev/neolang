#pragma once


#include <cstdio>
#include <string>

#define ASSERT(condition, message)                                             \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          fprintf(stderr, "[%s:%d] Assert failed in %s(): %s\n",               \
              __FILE__, __LINE__, __func__, message);                          \
          abort();                                                             \
        }                                                                      \
      } while (false)


#define UNREACHABLE()                                                        \
    do                                                                       \
    {                                                                        \
    fprintf(stderr, "[%s:%d] This code should not be reached in %s()\n",   \
        __FILE__, __LINE__, __func__);                                     \
    abort();                                                               \
    } while (false)

constexpr void assertion(bool condition, const std::string& message) {
    if (condition) return;
    fprintf(stderr, "[%s:%d] Assert failed in %s(): %s\n",
            __FILE__, __LINE__, __func__, message.data());
    std::terminate();
}

using ObjStringLiteral = std::string;