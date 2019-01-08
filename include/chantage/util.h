#ifndef CHANTAGE_UTIL_H
#define CHANTAGE_UTIL_H

/*
 * GCC is the only supported compiler,
 * this is mostly to fix static analysis.
 */
#if defined(__GNUC__)
# define PACKED         __attribute__ ((packed))
# define BREAKPOINT     __asm__ __volatile__ ("break\r\n")
#else
# define PACKED
# define BREAKPOINT
#endif

#endif
