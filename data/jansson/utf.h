#ifndef UTF_H
#define UTF_H

#include <config.h>

#ifdef HAVE_INTTYPES_H
/* inttypes.h includes stdint.h in a standard environment, so there's
no need to include stdint.h separately. If inttypes.h doesn't define
int32_t, it's defined in config.h. */
#include <inttypes.h>
#endif

int utf8_encode(int codepoint, char *buffer, int *size);

int utf8_check_first(char byte);
int utf8_check_full(const char *buffer, int size, int32_t *codepoint);
const char *utf8_iterate(const char *buffer, int32_t *codepoint);

int utf8_check_string(const char *string, int length);

#endif
