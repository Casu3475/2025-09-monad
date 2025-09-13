// Copyright (C) 2025 Category Labs, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <category/core/likely.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

[[noreturn]] void monad_assertion_failed(
    char const *expr, char const *function, char const *file, long line,
    char const *msg);

#define MONAD_ASSERTION_FAILED_WITH_MSG(expr, msg)                             \
    /* Ensure msg is a static string at a fixed address; we do this because */ \
    /* we don't want a fault occurring if dereferencing an unknown pointer */  \
    /* could cause a nested error, e.g., SIGSEGV raised by reading *msg */     \
    /* while we're reporting assertion failure */                              \
    static_assert(__builtin_constant_p(msg));                                  \
    monad_assertion_failed(                                                    \
        #expr, __extension__ __PRETTY_FUNCTION__, __FILE__, __LINE__, msg);

/// Assert, with backtrace upon failure; accepts an optional message, which
/// must be a compile-time-constant string
#define MONAD_ASSERT(expr, ...)                                                \
    if (MONAD_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        __VA_OPT__(MONAD_ASSERTION_FAILED_WITH_MSG(#expr, __VA_ARGS__);)       \
        __VA_OPT__(__builtin_unreachable();)                                   \
        monad_assertion_failed(                                                \
            #expr,                                                             \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            nullptr);                                                          \
    }

/// Similar to MONAD_ASSERT, but accepts a printf style message; this may not
/// be async signal safe
#define MONAD_ASSERT_PRINTF(expr, format, ...)                                 \
    if (MONAD_LIKELY(expr)) { /* likeliest */                                  \
    }                                                                          \
    else {                                                                     \
        char buf[1 << 14]; /* 16 KiB */                                        \
        int written;                                                           \
        char *const buf_end = buf + sizeof(buf);                               \
        char *p = stpcpy(buf, "assertion failure message: ");                  \
        written = snprintf(                                                    \
            p, (size_t)(buf_end - p), (format)__VA_OPT__(, ) __VA_ARGS__);     \
        /* If snprintf fails (written < 0) we're not sure what state buf */    \
        /* is in; write as much as possible so we don't lose info, but */      \
        /* leave room for "\n\0" */                                            \
        p = written < 0 ? buf_end - 2 : p + written;                           \
        if (p < buf_end) {                                                     \
            strncpy(p, "\n", (size_t)(buf_end - p));                           \
        }                                                                      \
        buf_end[-1] = '\0';                                                    \
        monad_assertion_failed(                                                \
            #expr,                                                             \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            buf);                                                              \
    }

/// Abort with a backtrace; accepts an optional message, which must be a
/// compile-time-constant string
#define MONAD_ABORT(...)                                                       \
    __VA_OPT__(MONAD_ASSERTION_FAILED_WITH_MSG(nullptr, __VA_ARGS__);)         \
    __VA_OPT__(__builtin_unreachable();)                                       \
    monad_assertion_failed(                                                    \
        nullptr,                                                               \
        __extension__ __PRETTY_FUNCTION__,                                     \
        __FILE__,                                                              \
        __LINE__,                                                              \
        nullptr);

/// Similar to MONAD_ASSERT_PRINTF, but for aborts
#define MONAD_ABORT_PRINTF(format, ...)                                        \
    {                                                                          \
        char buf[1 << 14]; /* 16 KiB */                                        \
        int written;                                                           \
        char *const buf_end = buf + sizeof(buf);                               \
        char *p = stpcpy(buf, "abort message: ");                              \
        written = snprintf(                                                    \
            p, (size_t)(buf_end - p), (format)__VA_OPT__(, ) __VA_ARGS__);     \
        /* See comment in MONAD_ASSERT_PRINTF */                               \
        p = written < 0 ? buf_end - 2 : p + written;                           \
        if (p < buf_end) {                                                     \
            strncpy(p, "\n", (size_t)(buf_end - p));                           \
        }                                                                      \
        buf_end[-1] = '\0';                                                    \
        monad_assertion_failed(                                                \
            nullptr,                                                           \
            __extension__ __PRETTY_FUNCTION__,                                 \
            __FILE__,                                                          \
            __LINE__,                                                          \
            buf);                                                              \
    }

#ifdef NDEBUG
    #define MONAD_DEBUG_ASSERT(x)                                              \
        do {                                                                   \
            (void)sizeof(x);                                                   \
        }                                                                      \
        while (0)
#else
    #define MONAD_DEBUG_ASSERT(x) MONAD_ASSERT(x)
#endif

#ifdef __cplusplus
}
#endif
