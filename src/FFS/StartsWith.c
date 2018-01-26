/*!
 * Copyright 2017 The Arcane Initiative.
 *
 * This file is part of FFS.
 *
 * FFS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * FFS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FFS.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "FFS/FFS.h"

// TODO: support sse3
// only SSE3 for now for compatibility reasons
// #include <pmmintrin.h>
// #include <xmmintrin.h>
#include <smmintrin.h>
#include <xmmintrin.h>


//------------------------------------------------------------------------------
//                                      SIMD
//------------------------------------------------------------------------------

union SimdInt64
{
    FFS_word_t integral[2];
    __m128i simd;
};

// TODO: int32

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

int ffs_starts_with__glibc(
        const char* a,
        const char* b,
        FFS_size_t a_length,
        FFS_size_t b_length)
{
    FFS_size_t a_len = static_cast<FFS_size_t>(strlen(a));
    FFS_size_t b_len = static_cast<FFS_size_t>(strlen(b));

    if(a_len == kFFS_npos)
    {
        a_len = static_cast<FFS_size_t>(strlen(a));
    }
    if(b_len == kFFS_npos)
    {
        b_len = static_cast<FFS_size_t>(strlen(b));
    }

    // early out if the substring is longer
    if(b_length > a_length)
    {
        return -1;
    }

    // do a mem compare
    return memcmp(a, b, b_length);
}

int ffs_starts_with__naive(
        const char* a,
        const char* b,
        FFS_size_t a_length,
        FFS_size_t b_length);
{

}
