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

#include <category/core/config.hpp>

#include <chrono>

MONAD_NAMESPACE_BEGIN

class BlockMetrics
{
    uint32_t n_retries_{0};
    std::chrono::microseconds tx_exec_time_{1};

public:
    void inc_retries()
    {
        ++n_retries_;
    }

    uint32_t num_retries() const
    {
        return n_retries_;
    }

    void set_tx_exec_time(std::chrono::microseconds const exec_time)
    {
        tx_exec_time_ = exec_time;
    }

    std::chrono::microseconds tx_exec_time() const
    {
        return tx_exec_time_;
    }
};

MONAD_NAMESPACE_END
