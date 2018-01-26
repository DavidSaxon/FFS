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
 *
 * \file
 * \author David Saxon
 * \brief Single header to include FFS functionality.
 */
#ifndef FFS_DEFINITIONS_H_
#define FFS_DEFINITIONS_H_

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
    extern "C"
    {
#endif
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//                                     TYPES
//------------------------------------------------------------------------------

/*!
 * \brief The data type used by FFS to represent string sizes.
 */
typedef size_t FFS_size_t;

/*!
 * \brief The data type used by FFS to represent error codes.
 */
typedef int32_t FFS_error_t;

/*!
 * \brief TODO:
 */
typedef char FFS_byte_t;

/*!
 * \brief TODO:
 */
typedef size_t FFS_word_t;

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

/*!
 * \brief String size value that represents a null position in a string.
 */
extern const FFS_size_t kFFS_npos;

/*!
 * \brief Signifies that no error occurred - execution successful.
 */
extern const FFS_error_t kFFS_error_none;

/*!
 * \brief TODO:
 */
extern const FFS_size_t kFFS_word_size;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

//---------------------------------L E N G T H----------------------------------

// TODO: doc ffs_length

/*!
 * \brief TODO:
 */
FFS_size_t ffs_length__naive(const char* s);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_length__word(const char* s);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_length__simd(const char* s);


#ifdef FFS_USE_GLIBC
    #define ffs_length strlen
#elif defined(FFS_USE_NAIVE)
    #define ffs_length ffs_length__naive
#elif defined(FFS_USE_WORD)
    #define ffs_length ffs_length__word
#else
    #define ffs_length ffs_length__simd
#endif

//----------------------------S T A R T S    W I T H----------------------------

// TODO: doc ffs_starts_with

/*!
 * \brief TODO:
 */
FFS_size_t ffs_starts_with__glibc(
        const char* a,
        const char* b,
        FFS_size_t a_length = kFFS_npos,
        FFS_size_t b_length = kFFS_npos);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_starts_with__naive(
        const char* a,
        const char* b,
        FFS_size_t a_length = kFFS_npos,
        FFS_size_t b_length = kFFS_npos);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_starts_with__word(
        const char* a,
        const char* b,
        FFS_size_t a_length = kFFS_npos,
        FFS_size_t b_length = kFFS_npos);

/*!
 * \brief TODO:
 */
FFS_size_t ffs_starts_with__simd(
        const char* a,
        const char* b,
        FFS_size_t a_length = kFFS_npos,
        FFS_size_t b_length = kFFS_npos);


#ifdef FFS_USE_GLIBC
    // TODO: glibc implementation
    #define ffs_starts_with ffs_starts_with__glibc
#elif defined(FFS_USE_NAIVE)
    #define ffs_starts_with ffs_starts_with__naive
#elif defined(FFS_USE_WORD)
    #define ffs_starts_with ffs_starts_with__word
#else
    #define ffs_starts_with ffs_starts_with__simd
#endif

//------------------------------------------------------------------------------
#ifdef __cplusplus
    } // extern "C"
#endif

#endif
