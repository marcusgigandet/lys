/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

#pragma once

#if defined(__clang__) || defined(__GNUC__)
#	define LYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#	define LYS_INLINE __forceinline
#else
#	define LYS_INLINE inline
#endif
