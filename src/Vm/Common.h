#pragma once

#include <cstdio>
#include <cstdlib>

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


#define forceinline __forceinline