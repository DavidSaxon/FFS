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
 * \brief Implementation of string length functionality.
 */
#ifndef FFS_LEGNTH_H_
#define FFS_LEGNTH_H_

#include "FFS/FFS.h"


FFS_NO_MANGLE_BEGIN
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief TODO:
 */
FFS_size_t ffs_length_naive(const char* s);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_length(const char* s);

//------------------------------------------------------------------------------
FFS_NO_MANGLE_END

#endif
