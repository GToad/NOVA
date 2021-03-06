/*
 * Utility Functions
 *
 * Copyright (C) 2009-2011 Udo Steinberg <udo@hypervisor.org>
 * Economic rights: Technische Universitaet Dresden (Germany)
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#pragma once

#include "compiler.hpp"

template <typename T>
ALWAYS_INLINE
static inline T min (T v1, T v2)
{
    return v1 < v2 ? v1 : v2;
}

template <typename T>
ALWAYS_INLINE
static inline T max (T v1, T v2)
{
    return v1 > v2 ? v1 : v2;
}

template <typename T>
ALWAYS_INLINE
static inline T gcd (T v1, T v2)
{
    while (v2) {
        T r = v1 % v2;
        v1  = v2;
        v2  = r;
    }

    return v1;
}

/*
 * Converts from a pointer to some outer storage to a pointer
 * to some inner storage that is contained in the outer storage
 *
 * See std::launder (http://eel.is/c++draft/ptr.launder)
 */
template <typename T>
constexpr T *launder (T *p) noexcept
{
    return __builtin_launder (p);
}
