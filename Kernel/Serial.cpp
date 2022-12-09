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
#include <Kernel/Io.hpp>
#include <Kernel/Serial.hpp>

namespace Kernel
{
    Serial::Port Serial::m_port = Serial::invalid;

    void Serial::init(Port port)
    {
        if (port == Port::invalid)
            return;
        m_port = port;

        Io::outb(m_port + 1, 0x00);
        Io::outb(m_port + 3, 0x80);
        Io::outb(m_port + 0, 0x03);
        Io::outb(m_port + 1, 0x00);
        Io::outb(m_port + 3, 0x03);
        Io::outb(m_port + 2, 0xC7);
        Io::outb(m_port + 4, 0x0B);
        Io::outb(m_port + 4, 0x1E);
        Io::outb(m_port + 0, 0xAE);

        if (Io::inb(m_port + 0) != 0xAE)
            return;

        Io::outb(m_port + 4, 0x0F);
    }

    void Serial::write(char ch)
    {
        if (m_port == Port::invalid)
            return;

        while ((Io::inb(m_port + 5) & 0x20) == 0)
            ;

        Io::outb(m_port, ch);
    }

    void Serial::write(const char *characters, St::Types::size length)
    {
        for (St::Types::size i = 0; i < length; i++)
        {
            write(characters[i]);
        }
    }

} // namespace Kernel
