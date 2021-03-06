/*
 * Memory Buffer Console
 *
 * Copyright (C) 2019-2020 Udo Steinberg, BedRock Systems, Inc.
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

#include "buddy.hpp"
#include "console.hpp"
#include "kmem.hpp"
#include "macros.hpp"

class Sm;

class Console_mbuf_mmio
{
    public:
        uint32 r_ptr { 0 };
        uint32 w_ptr { 0 };

        static constexpr unsigned ord = 0;
        static constexpr unsigned size = BIT (ord + PAGE_BITS);
        static constexpr unsigned entries = size - sizeof (r_ptr) - sizeof (w_ptr);

        char buffer[entries];

        static inline void *operator new (size_t) noexcept
        {
            return Buddy::alloc (ord);
        }
};

class Console_mbuf final : private Console
{
    private:
        Console_mbuf_mmio *regs { nullptr };
        Sm *sm                  { nullptr };

        static Console_mbuf singleton;

        bool fini() override final { return false; }
        void outc (char) override final;

        Console_mbuf();

    public:
        static auto addr() { return Kmem::ptr_to_phys (singleton.regs); }
        static auto size() { return singleton.regs->size; }
};
