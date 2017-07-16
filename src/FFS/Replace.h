/*!
 * Copyright 2017 David Saxon.
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
 *
 * \file
 * \author David Saxon
 * \brief Implementation of find and replace functionality.
 */
#ifndef FFS_REPLACE_H_
#define FFS_REPLACE_H_

#include "FFS/Definitions.h"


FFS_NO_MANGLE_BEGIN
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

inline FFS_error_t ffs_replace_single_naive(
        char* s,
        char to_replace,
        char replace_with,
        FFS_size_t length = kFFS_npos)
{
    for(FFS_size_t i = 0; i < length; ++i)
    {
        // is this a null terminator and we're not using an explicit length
        if(s[i] == '\0' && length != kFFS_npos)
        {
            return kFFS_error_none;
        }
        // is this the character to replace?
        if(s[i] == to_replace)
        {
            s[i] = replace_with;
        }
    }

    return kFFS_error_none;
}

/*!
 * \brief TODO:
 */
inline FFS_error_t ffs_replace_single(
        char* s,
        char to_replace,
        char replace_with,
        FFS_size_t length = kFFS_npos)
{
    // TODO: fast string length

    // for(FFS_size_t i = 0; i < length)

    return kFFS_error_none;
}

// TODO: ffs_replace_each

//------------------------------------------------------------------------------
FFS_NO_MANGLE_END

#endif
