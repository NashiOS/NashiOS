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
    class Serial
    {
    public:
        enum Port : St::Types::uint16
        {
            invalid,
            com1 = 0x3F8
        };

        static void init(Port port);
        static void write(char ch);
        static void write(const char *characters, St::Types::size length);

    private:
        static Port m_port;
    };
} // namespace Kernel
