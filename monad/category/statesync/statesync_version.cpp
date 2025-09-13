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

#include <category/statesync/statesync_version.h>

// Modify when there are changes to the protocol

constexpr uint32_t MONAD_STATESYNC_VERSION = 1;

uint32_t monad_statesync_version()
{
    return MONAD_STATESYNC_VERSION;
}

bool monad_statesync_client_compatible(uint32_t const version)
{
    return version <= MONAD_STATESYNC_VERSION && version >= 1;
}
