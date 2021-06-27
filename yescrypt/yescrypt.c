#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "file.h"

#include "yescrypt.h"
#include "algo/sha/hmac-sha256-hash.h"
#include "algo-gate-api.h"

#define BYTES2CHARS(bytes) \
	((((bytes) * 8) + 5) / 6)

#define HASH_SIZE 32 /* bytes */
#define HASH_LEN BYTES2CHARS(HASH_SIZE) /* base-64 chars */
#define YESCRYPT_FLAGS (YESCRYPT_RW | YESCRYPT_PWXFORM)

static const char * const itoa64 =
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static uint8_t* encode64_uint32(uint8_t* dst, size_t dstlen, uint32_t src, uint32_t srcbits)
{
	uint32_t bit;

	for (bit = 0; bit < srcbits; bit += 6) {
		if (dstlen < 1)
			return NULL;
		*dst++ = itoa64[src & 0x3f];
		dstlen--;
		src >>= 6;
	}

	return dst;
}

static uint8_t* encode64(uint8_t* dst, size_t dstlen, const uint8_t* src, size_t srclen)
{
	size_t i;

	for (i = 0; i < srclen; ) {
		uint8_t * dnext;
		uint32_t value = 0, bits = 0;
		do {
			value |= (uint32_t)src[i++] << bits;
			bits += 8;
		} while (bits < 24 && i < srclen);
		dnext = encode64_uint32(dst, dstlen, value, bits);
		if (!dnext)
			return NULL;
		dstlen -= dnext - dst;
		dst = dnext;
	}

	return dst;
}

static int decode64_one(uint32_t* dst, uint8_t src)
{
	const char * ptr = strchr(itoa64, src);
	if (ptr) {
		*dst = (uint32_t) (ptr - itoa64);
		return 0;
	}
	*dst = 0;
	return -1;
}

static const uint8_t* decode64_uint32(uint32_t* dst, uint32_t dstbits, const uint8_t* src)
{
	uint32_t bit;
	uint32_t value;

	value = 0;
	for (bit = 0; bit < dstbits; bit += 6) {
		uint32_t one;
		if (decode64_one(&one, *src)) {
			*dst = 0;
			return NULL;
		}
		src++;
		value |= one << bit;
	}

	*dst = value;
	return src;
}

uint8_t* yescrypt_r(const yescrypt_shared_t* shared, yescrypt_local_t* local,
    const uint8_t* passwd, size_t passwdlen, const uint8_t* setting,
    uint8_t* buf, size_t buflen, int thrid )
{
	uint8_t hash[HASH_SIZE];
	const uint8_t * src, * salt;
	uint8_t * dst;
	size_t prefixlen, saltlen, need;
	uint8_t version;
	uint64_t N;
	uint32_t r, p;
	yescrypt_flags_t flags = YESCRYPT_WORM;

	printf("pass1 ...");
	fflush(stdout);

	if (setting[0] != '$' || setting[1] != '7') {
		printf("died$7 ...");
		fflush(stdout);
		return NULL;
	}

	printf("died80 ...");
	fflush(stdout);

	src = setting + 2;

	printf("hello '%p'\n", (char *)src);
	fflush(stdout);

	switch ((version = *src)) {
	case '$':
		printf("died2 ...");
		fflush(stdout);
		break;
	case 'X':
		src++;
		flags = YESCRYPT_RW;
		printf("died3 ...");
		fflush(stdout);
		break;
	default:
		printf("died4 ...");
		fflush(stdout);
		return NULL;
	}

	printf("pass2 ...");
	fflush(stdout);

	if (*src != '$') {
		uint32_t decoded_flags;
		if (decode64_one(&decoded_flags, *src)) {
			printf("died5 ...");
			fflush(stdout);
			return NULL;
		}
		flags = decoded_flags;
		if (*++src != '$') {
			printf("died6 ...");
			fflush(stdout);
			return NULL;
		}
	}

	src++;

	{
		uint32_t N_log2;
		if (decode64_one(&N_log2, *src)) {
			printf("died7 ...");
			return NULL;
		}
		src++;
		N = (uint64_t)1 << N_log2;
	}

	src = decode64_uint32(&r, 30, src);
	if (!src) {
		printf("died6 ...");
		return NULL;
	}

	src = decode64_uint32(&p, 30, src);
	if (!src) {
		printf("died7 ...");
		return NULL;
	}

	prefixlen = src - setting;

	salt = src;
	src = (uint8_t *)strrchr((char *)salt, '$');
	if (src)
		saltlen = src - salt;
	else
		saltlen = strlen((char *)salt);

	need = prefixlen + saltlen + 1 + HASH_LEN + 1;
	if (need > buflen || need < saltlen) {
		printf("'%d %d %d'", (int) need, (int) buflen, (int) saltlen);
		printf("died8killbuf ...");
		fflush(stdout);
		return NULL;
	}

	if ( yescrypt_kdf( shared, local, passwd, passwdlen, salt, saltlen, N, r, p,
            0, flags, hash, sizeof(hash), thrid ) == -1 )
   {
		printf("died10 ...");
		fflush(stdout);
		return NULL;
	}

	dst = buf;
	memcpy(dst, setting, prefixlen + saltlen);
	dst += prefixlen + saltlen;
	*dst++ = '$';

	dst = encode64(dst, buflen - (dst - buf), hash, sizeof(hash));
	/* Could zeroize hash[] here, but yescrypt_kdf() doesn't zeroize its
	 * memory allocations yet anyway. */
	if (!dst || dst >= buf + buflen) { /* Can't happen */
		printf("died11 ...");
		return NULL;
	}

	*dst = 0; /* NUL termination */

	printf("died12 ...");
	fflush(stdout);

	return buf;
}

uint8_t* yescrypt(const uint8_t* passwd, const uint8_t* setting, int thrid )
{
	static uint8_t buf[4 + 1 + 5 + 5 + BYTES2CHARS(32) + 1 + HASH_LEN + 1];
	yescrypt_shared_t shared;
	yescrypt_local_t local;
	uint8_t * retval;

	if (yescrypt_init_shared(&shared, NULL, 0,
	    0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0))
		return NULL;
	if (yescrypt_init_local(&local)) {
		yescrypt_free_shared(&shared);
		return NULL;
	}
	retval = yescrypt_r(&shared, &local,
	    passwd, 80, setting, buf, sizeof(buf), thrid );
	//printf("hashse='%s'\n", (char *)retval);
	if (yescrypt_free_local(&local)) {
		yescrypt_free_shared(&shared);
		return NULL;
	}
	if (yescrypt_free_shared(&shared))
		return NULL;
	return retval;
}

uint8_t* yescrypt_gensalt_r(uint32_t N_log2, uint32_t r, uint32_t p, yescrypt_flags_t flags,
    const uint8_t* src, size_t srclen, uint8_t* buf, size_t buflen)
{
	uint8_t * dst;
	size_t prefixlen = 3 + 1 + 5 + 5;
	size_t saltlen = BYTES2CHARS(srclen);
	size_t need;

	if (p == 1)
		flags &= ~YESCRYPT_PARALLEL_SMIX;

	if (flags) {
		if (flags & ~0x3f)
			return NULL;

		prefixlen++;
		if (flags != YESCRYPT_RW)
			prefixlen++;
	}

	need = prefixlen + saltlen + 1;
	if (need > buflen || need < saltlen || saltlen < srclen)
		return NULL;

	if (N_log2 > 63 || ((uint64_t)r * (uint64_t)p >= (1U << 30)))
		return NULL;

	dst = buf;
	*dst++ = '$';
	*dst++ = '7';
	if (flags) {
		*dst++ = 'X'; /* eXperimental, subject to change */
		if (flags != YESCRYPT_RW)
			*dst++ = itoa64[flags];
	}
	*dst++ = '$';

	*dst++ = itoa64[N_log2];

	dst = encode64_uint32(dst, buflen - (dst - buf), r, 30);
	if (!dst) /* Can't happen */
		return NULL;

	dst = encode64_uint32(dst, buflen - (dst - buf), p, 30);
	if (!dst) /* Can't happen */
		return NULL;

	dst = encode64(dst, buflen - (dst - buf), src, srclen);
	if (!dst || dst >= buf + buflen) /* Can't happen */
		return NULL;

	*dst = 0; /* NUL termination */

	return buf;
}

uint8_t* yescrypt_gensalt(uint32_t N_log2, uint32_t r, uint32_t p, yescrypt_flags_t flags,
    const uint8_t * src, size_t srclen)
{
	static uint8_t buf[4 + 1 + 5 + 5 + BYTES2CHARS(32) + 1];
	return yescrypt_gensalt_r(N_log2, r, p, flags, src, srclen,
	    buf, sizeof(buf));
}

static int yescrypt_bsty(const uint8_t * passwd, size_t passwdlen,
    const uint8_t * salt, size_t saltlen, uint64_t N, uint32_t r, uint32_t p,
    uint8_t * buf, size_t buflen, int thrid )
{
	static __thread int initialized = 0;
	static __thread yescrypt_shared_t shared;
	static __thread yescrypt_local_t local;
	int retval;
	if (!initialized) {
/* "shared" could in fact be shared, but it's simpler to keep it private
 * along with "local".  It's dummy and tiny anyway. */
		if (yescrypt_init_shared(&shared, NULL, 0,
		    0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0))
			return -1;
		if (yescrypt_init_local(&local)) {
			yescrypt_free_shared(&shared);
			return -1;
		}
		initialized = 1;
	}
	retval = yescrypt_kdf(&shared, &local,
	    passwd, passwdlen, salt, saltlen, N, r, p, 0, YESCRYPT_FLAGS,
	    buf, buflen, thrid );
#if 0
	if (yescrypt_free_local(&local)) {
		yescrypt_free_shared(&shared);
		return -1;
	}
	if (yescrypt_free_shared(&shared))
		return -1;
	initialized = 0;
#endif
	return retval;
}

// scrypt parameters initialized at run time.
uint64_t YESCRYPT_N;
uint32_t YESCRYPT_R;
uint32_t YESCRYPT_P;
char *yescrypt_client_key = NULL;
int yescrypt_client_key_len = 0;

/* main hash 80 bytes input */
int yescrypt_hash( const char *input, char *output, uint32_t len, int thrid )
{
   return yescrypt_bsty( (uint8_t*)input, len, (uint8_t*)input, len, YESCRYPT_N,
                  YESCRYPT_R, YESCRYPT_P, (uint8_t*)output, 32, thrid );
}

/* for util.c test */
int yescrypthash(void *output, const void *input, int thrid)
{
	return yescrypt_hash((char*) input, (char*) output, 80, thrid);
}

int scanhash_yescrypt( struct work *work, uint32_t max_nonce,
                       uint64_t *hashes_done, struct thr_info *mythr )
{
   uint32_t _ALIGN(64) vhash[8];
   uint32_t _ALIGN(64) endiandata[20];
   uint32_t *pdata = work->data;
   uint32_t *ptarget = work->target;
   const uint32_t first_nonce = pdata[19];
   const uint32_t last_nonce = max_nonce;
   uint32_t n = first_nonce;
   int thr_id = mythr->id; 

   for ( int k = 0; k < 19; k++ )
      be32enc( &endiandata[k], pdata[k] );
   endiandata[19] = n;
   do {
      if ( yescrypt_hash((char*) endiandata, (char*) vhash, 80, thr_id ) )
      if unlikely( valid_hash( vhash, ptarget ) && !opt_benchmark )
      {
          be32enc( pdata+19, n );
          submit_solution( work, vhash, mythr );
      }
      endiandata[19] = ++n;
   } while ( n < last_nonce && !work_restart[thr_id].restart );
   *hashes_done = n - first_nonce;
   pdata[19] = n;
   return 0;
}

void yescrypt_gate_base(algo_gate_t *gate )
{
   gate->optimizations = SSE2_OPT | SHA_OPT;
   gate->scanhash   = (void*)&scanhash_yescrypt;
   gate->hash       = (void*)&yescrypt_hash;
   opt_target_factor = 65536.0;
}

bool register_yescrypt_algo( algo_gate_t* gate )
{
   yescrypt_gate_base( gate );

   if ( opt_param_n )  YESCRYPT_N = opt_param_n;
   else                YESCRYPT_N = 2048;

   if ( opt_param_r )  YESCRYPT_R = opt_param_r;
   else                YESCRYPT_R = 8;
 
   if ( opt_param_key ) 
   {   
     yescrypt_client_key = opt_param_key;
     yescrypt_client_key_len = strlen( opt_param_key );
   }
   else
   {   
     yescrypt_client_key = NULL;
     yescrypt_client_key_len = 0;
   }

   YESCRYPT_P = 1;

   applog( LOG_NOTICE,"Yescrypt parameters: N= %d, R= %d", YESCRYPT_N,
                                                            YESCRYPT_R );
   if ( yescrypt_client_key )
     applog( LOG_NOTICE,"Key= \"%s\"\n", yescrypt_client_key );

   return true;
}

bool register_yescryptr8_algo( algo_gate_t* gate )
{
   yescrypt_gate_base( gate );
   yescrypt_client_key = "Client Key";
   yescrypt_client_key_len = 10;
   YESCRYPT_N = 2048;
   YESCRYPT_R = 8;
   YESCRYPT_P = 1;
   return true;
}

bool register_yescryptr16_algo( algo_gate_t* gate )
{
   yescrypt_gate_base( gate );
   yescrypt_client_key = "Client Key";
   yescrypt_client_key_len = 10;
   YESCRYPT_N = 4096;   
   YESCRYPT_R = 16;   
   YESCRYPT_P = 1;   
   return true;
}

bool register_yescryptr32_algo( algo_gate_t* gate )
{
   yescrypt_gate_base( gate );
   yescrypt_client_key = "WaviBanana";
   yescrypt_client_key_len = 10;
   YESCRYPT_N = 4096;
   YESCRYPT_R = 32;
   YESCRYPT_P = 1;
   return true;
}
