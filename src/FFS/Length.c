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

FFS_size_t ffs_length_naive(const char* s)
{
    for(FFS_size_t i = 0; i < kFFS_npos; ++i)
    {
        if(s[i] == '\0')
        {
            return i;
        }
    }

    return kFFS_npos;
}

FFS_size_t ffs_length(const char* s)
{
    // TODO: can this be assigned early?
    const FFS_byte_t* byte_ptr;

    //TODO: store kFFS_word_size - 1 ?
    // TODO: naive check the first bits until we're word aligned
    for(byte_ptr = s;
        ((FFS_size_t) byte_ptr & (kFFS_word_size - 1)) != 0;
        ++byte_ptr)
    {
        if(*byte_ptr == 0)
        {
            return byte_ptr - s;
        }
    }

    const FFS_word_t* word_ptr = (FFS_word_t*) byte_ptr;

    // TODO: sort out
    FFS_word_t high_magic = 0x80808080UL;
    FFS_word_t low_magic  = 0x01010101UL;
    if(kFFS_word_size > 4)
    {
        high_magic = 0x8080808080808080L;
        low_magic  = 0x0101010101010101L;
    }

    union SimdInt64 simd_high_magic;
    simd_high_magic.integral[0] = 0x8080808080808080L;
    simd_high_magic.integral[1] = 0x8080808080808080L;

    union SimdInt64 simd_low_magic;
    simd_low_magic.integral[0] = 0x0101010101010101L;
    simd_low_magic.integral[1] = 0x0101010101010101L;

    // TODO: DOC
    for(;;)
    {

        // TODO: aggregate
        union SimdInt64 simd_word;
        simd_word.integral[0] = *word_ptr++;
        simd_word.integral[1] = *word_ptr++;

        __m128i s0 = _mm_sub_epi64(simd_word.simd, simd_low_magic.simd);
        if(_mm_test_all_zeros(s0, simd_high_magic.simd) == 0)
        {
            // TODO: could narrow this down where to check faster
            const FFS_byte_t* check = (const FFS_byte_t*) (word_ptr - 2);

            if(check[0] == 0)
            {
                return (check - s) + 0;
            }
            if(check[1] == 0)
            {
                return (check - s) + 1;
            }
            if(check[2] == 0)
            {
                return (check - s) + 2;
            }
            if(check[3] == 0)
            {
                return (check - s) + 3;
            }
            if(check[4] == 0)
            {
                return (check - s) + 4;
            }
            if(check[5] == 0)
            {
                return (check - s) + 5;
            }
            if(check[6] == 0)
            {
                return (check - s) + 6;
            }
            if(check[7] == 0)
            {
                return (check - s) + 7;
            }
            if(check[8] == 0)
            {
                return (check - s) + 8;
            }
            if(check[9] == 0)
            {
                return (check - s) + 9;
            }
            if(check[10] == 0)
            {
                return (check - s) + 10;
            }
            if(check[11] == 0)
            {
                return (check - s) + 11;
            }
            if(check[12] == 0)
            {
                return (check - s) + 12;
            }
            if(check[13] == 0)
            {
                return (check - s) + 13;
            }
            if(check[14] == 0)
            {
                return (check - s) + 14;
            }
            if(check[15] == 0)
            {
                return (check - s) + 15;
            }
        }

        // FFS_word_t word = *word_ptr++;

        // if(((word - low_magic) & high_magic) != 0)
        // {
        //     const FFS_byte_t* check = (const FFS_byte_t*) (word_ptr - 1);

        //     if(check[0] == 0)
        //     {
        //         return check - s;
        //     }
        //     if(check[1] == 0)
        //     {
        //         return (check - s) + 1;
        //     }
        //     if(check[2] == 0)
        //     {
        //         return (check - s) + 2;
        //     }
        //     if(check[3] == 0)
        //     {
        //         return (check - s) + 3;
        //     }
        //     if(kFFS_word_size > 4)
        //     {
        //         if(check[4] == 0)
        //         {
        //             return (check - s) + 4;
        //         }
        //         if(check[5] == 0)
        //         {
        //             return (check - s) + 5;
        //         }
        //         if(check[6] == 0)
        //         {
        //             return (check - s) + 6;
        //         }
        //         if(check[7] == 0)
        //         {
        //             return (check - s) + 7;
        //         }
        //     }

        //     // misfire - continue
        // }
    }

    return kFFS_npos;
}
