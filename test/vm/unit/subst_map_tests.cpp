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

#include <category/vm/compiler/ir/poly_typed/kind.hpp>
#include <category/vm/compiler/ir/poly_typed/subst_map.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace monad::vm::compiler;
using namespace monad::vm::compiler::poly_typed;

TEST(subst_map, test_1)
{
    SubstMap su{};
    su.insert_cont(0, cont_kind({}));
    su.insert_kind(0, any);
    ASSERT_TRUE(weak_equal(su.subst_or_throw(word), word));
    ASSERT_TRUE(weak_equal(su.subst_or_throw(kind_var(0)), any));
    ASSERT_TRUE(weak_equal(
        su.subst_or_throw(cont(cont_kind({kind_var(0), kind_var(1)}, 0))),
        cont(cont_kind({any, kind_var(1)}))));
}

TEST(subst_map, test_2)
{
    SubstMap su{};
    su.insert_cont(0, cont_kind({kind_var(3), any}, 1));
    su.insert_kind(0, cont(cont_kind({kind_var(1), kind_var(2)}, 0)));
    su.insert_kind(3, kind_var(1));
    ASSERT_TRUE(weak_equal(
        su.subst_or_throw(cont_kind({kind_var(0), word, kind_var(3)}, 0)),
        cont_kind(
            {cont(cont_kind({kind_var(1), kind_var(2), kind_var(1), any}, 1)),
             word,
             kind_var(1),
             kind_var(1),
             any},
            1)));
}

TEST(subst_map, test_3)
{
    ContKind const literal_kind1 = cont_kind({kind_var(3)});
    ContKind const literal_kind4 =
        cont_kind({literal_var(5, cont_kind({}, 1))});

    SubstMap su{};

    su.link_literal_vars(1, 2);
    su.insert_literal_type(1, LiteralType::Cont);
    su.insert_literal_type(3, LiteralType::Word);
    su.insert_cont(
        0,
        cont_kind(
            {literal_var(1, literal_kind1),
             literal_var(2, literal_kind1),
             literal_var(3, literal_kind1),
             literal_var(4, literal_kind4)}));
    su.insert_kind(
        0,
        cont(cont_kind(
            {literal_var(1, literal_kind1), literal_var(2, literal_kind1)},
            0)));
    su.insert_kind(3, literal_var(3, literal_kind1));
    ASSERT_TRUE(weak_equal(
        su.subst_or_throw(kind_var(0)),
        cont(cont_kind(
            {cont(cont_kind({word})),
             cont(cont_kind({word})),
             cont(cont_kind({word})),
             cont(cont_kind({word})),
             word,
             literal_var(4, literal_kind4)}))));
}
