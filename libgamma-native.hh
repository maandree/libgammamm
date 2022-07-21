/* See LICENSE file for copyright and license details. */
#ifndef LIBGAMMA_NATIVE_HH
#define LIBGAMMA_NATIVE_HH

extern "C"
{
# ifdef __GNUC__
#  define restrict __restrict__
# else
#  define restrict /* remove */
# endif
# define this self
# include <libgamma.h>
# undef this
# undef restrict
# ifndef __GNUC__
#  ifdef __attribute__
#   undef __attribute__
#  endif
# endif
}

#endif
