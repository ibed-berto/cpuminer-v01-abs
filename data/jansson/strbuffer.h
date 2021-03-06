#ifndef STRBUFFER_H
#define STRBUFFER_H

typedef struct {
    char *value;
    int length;   /* bytes used */
    int size;     /* bytes allocated */
} strbuffer_t;

int strbuffer_init(strbuffer_t *strbuff);
void strbuffer_close(strbuffer_t *strbuff);

void strbuffer_clear(strbuffer_t *strbuff);

const char *strbuffer_value(const strbuffer_t *strbuff);
char *strbuffer_steal_value(strbuffer_t *strbuff);

int strbuffer_append(strbuffer_t *strbuff, const char *string);
int strbuffer_append_byte(strbuffer_t *strbuff, char byte);
int strbuffer_append_bytes(strbuffer_t *strbuff, const char *data, int size);

char strbuffer_pop(strbuffer_t *strbuff);

#endif
