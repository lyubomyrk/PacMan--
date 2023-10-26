/*
 * Created on Wed Oct 25 2023
 *
 * Copyright (C) 2023 Lyubomyr Kryshtanovskyi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "Timer.hpp"

Timer::Timer()
{
    _lifetime = 0;
}

void Timer::Start(float lifetime)
{
    _lifetime = lifetime;
}

void Timer::Update()
{
    if (_lifetime > 0)
    {
        _lifetime -= GetFrameTime();
    }
}

bool Timer::IsFinished()
{
    return _lifetime <= 0;
}
