/*
 * Nashi Operating System
 * Copyright (C) 2022 Saullo Bretas Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <St/Types.hpp>

namespace Kernel
{
    class Io
    {
    public:
        static inline void outb(St::Types::uint16 port, St::Types::uint8 value)
        {
            asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
        }

        static inline void outw(St::Types::uint16 port, St::Types::uint16 value)
        {
            asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
        }

        static inline void outl(St::Types::uint16 port, St::Types::uint32 value)
        {
            asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
        }

        static inline auto inb(St::Types::uint16 port)
        {
            St::Types::uint8 result;
            asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
            return result;
        }

        static inline auto inw(St::Types::uint16 port)
        {
            St::Types::uint16 result;
            asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
            return result;
        }

        static inline auto inl(St::Types::uint16 port)
        {
            St::Types::uint32 result;
            asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
            return result;
        }
    };
} // namespace Kernel
