/*
Copyright © 2015 Kean Mariotti <kean.mariotti@gmail.com>
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
*/

#ifndef _SSTL_ALIGNED_STORAGE__
#define _SSTL_ALIGNED_STORAGE__

#include <cstddef>
#include <type_traits>

#include "preprocessor.h"

namespace sstl
{
#if !IS_MSVC()
   template<size_t Len, size_t Align>
   struct aligned_storage
   {
      using type = typename std::aligned_storage<Len, Align>::type;
   };
#else
   namespace detail
   {
      template<size_t Align>
      struct invalid_alignment_value
      {
         static const bool error = false;
      };
   };

   template<size_t Len, size_t Align>
   struct aligned_storage
   {
      static_assert(detail::invalid_alignment_value<Align>::error, "specified alignment is not valid");
   };

   #define define_aligned_storage(Align) \
      template<size_t Len> \
      struct aligned_storage<Len, Align> \
      { \
         static_assert(Len <= Align, "cannot have a type with size greater than alignment requirement") \
         __declspec(align(Align)) struct type \
         { \
            uint8_t _data[Len]; \
         }; \
      };

   define_aligned_storage(1)
   define_aligned_storage(2)
   define_aligned_storage(4)
   define_aligned_storage(8)
   define_aligned_storage(16)
   define_aligned_storage(32)
   define_aligned_storage(64)
   define_aligned_storage(128)
   define_aligned_storage(258)
   define_aligned_storage(512)
   define_aligned_storage(1024)
   define_aligned_storage(2048)
   define_aligned_storage(4096)
   define_aligned_storage(8192)

#endif
}

#endif // _SSTL_ALIGNED_STORAGE__
