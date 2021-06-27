
#ifndef HMAC_SHA256_H__
#define HMAC_SHA256_H__

//#define HMAC_SSL_SHA 1
#define HMAC_SPH_SHA 1

#include <sys/types.h>
#include <stdint.h>
#include "sph_sha2.h"
#include <openssl/sha.h>


typedef struct HMAC_SHA256Context
{
#if defined(HMAC_SPH_SHA)
   sph_sha256_context ictx;
   sph_sha256_context octx;
#else
   SHA256_CTX ictx;
   SHA256_CTX octx;
#endif
} HMAC_SHA256_CTX;

void SHA256_Buf( const void *, size_t len, uint8_t digest[32] );
void HMAC_SHA256_Init( HMAC_SHA256_CTX *, const void *, size_t );
void HMAC_SHA256_Update( HMAC_SHA256_CTX *, const void *, size_t );
void HMAC_SHA256_Final( unsigned char [32], HMAC_SHA256_CTX * );
void HMAC_SHA256_Buf( const void *, size_t Klen, const void *,
                      size_t len, uint8_t digest[32] );

/**
 * PBKDF2_SHA256(passwd, passwdlen, salt, saltlen, c, buf, dkLen):
 * Compute PBKDF2(passwd, salt, c, dkLen) using HMAC-SHA256 as the PRF, and
 * write the output to buf.  The value dkLen must be at most 32 * (2^32 - 1).
 */
void PBKDF2_SHA256( const uint8_t *, size_t, const uint8_t *, size_t,
                    uint64_t, uint8_t *, size_t);

#endif // HMAC_SHA256_H__
