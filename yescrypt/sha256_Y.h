#ifndef _SHA256_H_
#define _SHA256_H_

#include <sys/types.h>

#include <stdint.h>

typedef struct SHA256Context {
	uint32_t state[8];
	uint32_t count[2];
	unsigned char buf[64];
} SHA256_CTX_Y;

typedef struct HMAC_SHA256Context {
	SHA256_CTX_Y ictx;
	SHA256_CTX_Y octx;
} HMAC_SHA256_CTX_Y;

void	SHA256_Init_Y(SHA256_CTX_Y *);
void	SHA256_Update_Y(SHA256_CTX_Y *, const void *, size_t);
void	SHA256_Final_Y(unsigned char [32], SHA256_CTX_Y *);
void	HMAC_SHA256_Init_Y(HMAC_SHA256_CTX_Y *, const void *, size_t);
void	HMAC_SHA256_Update_Y(HMAC_SHA256_CTX_Y *, const void *, size_t);
void	HMAC_SHA256_Final_Y(unsigned char [32], HMAC_SHA256_CTX_Y *);

/**
 * PBKDF2_SHA256(passwd, passwdlen, salt, saltlen, c, buf, dkLen):
 * Compute PBKDF2(passwd, salt, c, dkLen) using HMAC-SHA256 as the PRF, and
 * write the output to buf.  The value dkLen must be at most 32 * (2^32 - 1).
 */
void	PBKDF2_SHA256(const uint8_t *, size_t, const uint8_t *, size_t,
    uint64_t, uint8_t *, size_t);

#endif /* !_SHA256_H_ */
