#ifndef SPH_RIPEMD_H__
#define SPH_RIPEMD_H__

#include <stddef.h>
#include "sph_types.h"

/**
 * Output size (in bits) for RIPEMD.
 */
#define SPH_SIZE_ripemd   128

/**
 * Output size (in bits) for RIPEMD-128.
 */
#define SPH_SIZE_ripemd128   128

/**
 * Output size (in bits) for RIPEMD-160.
 */
#define SPH_SIZE_ripemd160   160

/**
 * This structure is a context for RIPEMD computations: it contains the
 * intermediate values and some data from the last entered block. Once
 * a RIPEMD computation has been performed, the context can be reused for
 * another computation.
 *
 * The contents of this structure are private. A running RIPEMD computation
 * can be cloned by copying the context (e.g. with a simple
 * <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[64];    /* first field, for alignment */
	sph_u32 val[4];
#if SPH_64
	sph_u64 count;
#else
	sph_u32 count_high, count_low;
#endif
#endif
} sph_ripemd_context;

/**
 * Initialize a RIPEMD context. This process performs no memory allocation.
 *
 * @param cc   the RIPEMD context (pointer to
 *             a <code>sph_ripemd_context</code>)
 */
void sph_ripemd_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the RIPEMD context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_ripemd(void *cc, const void *data, size_t len);

/**
 * Terminate the current RIPEMD computation and output the result into the
 * provided buffer. The destination buffer must be wide enough to
 * accomodate the result (16 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the RIPEMD context
 * @param dst   the destination buffer
 */
void sph_ripemd_close(void *cc, void *dst);

/**
 * Apply the RIPEMD compression function on the provided data. The
 * <code>msg</code> parameter contains the 16 32-bit input blocks,
 * as numerical values (hence after the little-endian decoding). The
 * <code>val</code> parameter contains the 5 32-bit input blocks for
 * the compression function; the output is written in place in this
 * array.
 *
 * @param msg   the message block (16 values)
 * @param val   the function 128-bit input and output
 */
void sph_ripemd_comp(const sph_u32 msg[16], sph_u32 val[4]);

/* ===================================================================== */ 

/**
 * This structure is a context for RIPEMD-128 computations: it contains the
 * intermediate values and some data from the last entered block. Once
 * a RIPEMD-128 computation has been performed, the context can be reused for
 * another computation.
 *
 * The contents of this structure are private. A running RIPEMD-128 computation
 * can be cloned by copying the context (e.g. with a simple
 * <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[64];    /* first field, for alignment */
	sph_u32 val[4];
#if SPH_64
	sph_u64 count;
#else
	sph_u32 count_high, count_low;
#endif
#endif
} sph_ripemd128_context;

/**
 * Initialize a RIPEMD-128 context. This process performs no memory allocation.
 *
 * @param cc   the RIPEMD-128 context (pointer to
 *             a <code>sph_ripemd128_context</code>)
 */
void sph_ripemd128_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the RIPEMD-128 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_ripemd128(void *cc, const void *data, size_t len);

/**
 * Terminate the current RIPEMD-128 computation and output the result into the
 * provided buffer. The destination buffer must be wide enough to
 * accomodate the result (16 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the RIPEMD-128 context
 * @param dst   the destination buffer
 */
void sph_ripemd128_close(void *cc, void *dst);

/**
 * Apply the RIPEMD-128 compression function on the provided data. The
 * <code>msg</code> parameter contains the 16 32-bit input blocks,
 * as numerical values (hence after the little-endian decoding). The
 * <code>val</code> parameter contains the 5 32-bit input blocks for
 * the compression function; the output is written in place in this
 * array.
 *
 * @param msg   the message block (16 values)
 * @param val   the function 128-bit input and output
 */
void sph_ripemd128_comp(const sph_u32 msg[16], sph_u32 val[4]);

/* ===================================================================== */ 

/**
 * This structure is a context for RIPEMD-160 computations: it contains the
 * intermediate values and some data from the last entered block. Once
 * a RIPEMD-160 computation has been performed, the context can be reused for
 * another computation.
 *
 * The contents of this structure are private. A running RIPEMD-160 computation
 * can be cloned by copying the context (e.g. with a simple
 * <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[64];    /* first field, for alignment */
	sph_u32 val[5];
#if SPH_64
	sph_u64 count;
#else
	sph_u32 count_high, count_low;
#endif
#endif
} sph_ripemd160_context;

/**
 * Initialize a RIPEMD-160 context. This process performs no memory allocation.
 *
 * @param cc   the RIPEMD-160 context (pointer to
 *             a <code>sph_ripemd160_context</code>)
 */
void sph_ripemd160_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the RIPEMD-160 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_ripemd160(void *cc, const void *data, size_t len);

/**
 * Terminate the current RIPEMD-160 computation and output the result into the
 * provided buffer. The destination buffer must be wide enough to
 * accomodate the result (20 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the RIPEMD-160 context
 * @param dst   the destination buffer
 */
void sph_ripemd160_close(void *cc, void *dst);

/**
 * Apply the RIPEMD-160 compression function on the provided data. The
 * <code>msg</code> parameter contains the 16 32-bit input blocks,
 * as numerical values (hence after the little-endian decoding). The
 * <code>val</code> parameter contains the 5 32-bit input blocks for
 * the compression function; the output is written in place in this
 * array.
 *
 * @param msg   the message block (16 values)
 * @param val   the function 160-bit input and output
 */
void sph_ripemd160_comp(const sph_u32 msg[16], sph_u32 val[5]);

#endif
