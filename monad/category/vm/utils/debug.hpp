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

namespace monad::vm::utils
{
#ifdef MONAD_COMPILER_TESTING
    extern bool is_fuzzing_monad_vm;
#else
    static constexpr bool is_fuzzing_monad_vm = false;
#endif

#ifdef MONAD_COMPILER_STATS
    static constexpr bool collect_monad_compiler_stats = true;
#else
    static constexpr bool collect_monad_compiler_stats = false;
#endif

#ifdef MONAD_COMPILER_HOT_PATH_STATS
    static constexpr bool collect_monad_compiler_hot_path_stats = true;
#else
    static constexpr bool collect_monad_compiler_hot_path_stats = false;
#endif
}
