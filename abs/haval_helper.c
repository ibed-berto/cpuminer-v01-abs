#undef SPH_XCAT
#define SPH_XCAT(a, b)    SPH_XCAT_(a, b)
#undef SPH_XCAT_
#define SPH_XCAT_(a, b)   a ## b

static void
#ifdef SPH_UPTR
SPH_XCAT(SPH_XCAT(haval, PASSES), _short)
#else
SPH_XCAT(haval, PASSES)
#endif
(sph_haval_context *sc, const void *data, size_t len)
{
	unsigned current;

#if SPH_64
	current = (unsigned)sc->count & 127U;
#else
	current = (unsigned)sc->count_low & 127U;
#endif
	while (len > 0) {
		unsigned clen;
#if !SPH_64
		sph_u32 clow, clow2;
#endif

		clen = 128U - current;
		if (clen > len)
			clen = len;
		memcpy(sc->buf + current, data, clen);
		data = (const unsigned char *)data + clen;
		current += clen;
		len -= clen;
		if (current == 128U) {
			DSTATE;
			IN_PREPARE(sc->buf);

			RSTATE;
			SPH_XCAT(CORE, PASSES)(INW);
			WSTATE;
			current = 0;
		}
#if SPH_64
		sc->count += clen;
#else
		clow = sc->count_low;
		clow2 = SPH_T32(clow + clen);
		sc->count_low = clow2;
		if (clow2 < clow)
			sc->count_high ++;
#endif
	}
}

#ifdef SPH_UPTR
static void
SPH_XCAT(haval, PASSES)(sph_haval_context *sc, const void *data, size_t len)
{
	unsigned current;
	size_t orig_len;
#if !SPH_64
	sph_u32 clow, clow2;
#endif
	DSTATE;

	if (len < 256U) {
		SPH_XCAT(SPH_XCAT(haval, PASSES), _short)(sc, data, len);
		return;
	}
#if SPH_64
	current = (unsigned)sc->count & 127U;
#else
	current = (unsigned)sc->count_low & 127U;
#endif
	if (current > 0) {
		unsigned clen;

		clen = 128U - current;
		SPH_XCAT(SPH_XCAT(haval, PASSES), _short)(sc, data, clen);
		data = (const unsigned char *)data + clen;
		len -= clen;
	}
#if !SPH_UNALIGNED
	if (((SPH_UPTR)data & 3U) != 0) {
		SPH_XCAT(SPH_XCAT(haval, PASSES), _short)(sc, data, len);
		return;
	}
#endif
	orig_len = len;
	RSTATE;
	while (len >= 128U) {
		IN_PREPARE(data);

		SPH_XCAT(CORE, PASSES)(INW);
		data = (const unsigned char *)data + 128U;
		len -= 128U;
	}
	WSTATE;
	if (len > 0)
		memcpy(sc->buf, data, len);
#if SPH_64
	sc->count += (sph_u64)orig_len;
#else
	clow = sc->count_low;
	clow2 = SPH_T32(clow + orig_len);
	sc->count_low = clow2;
	if (clow2 < clow)
		sc->count_high ++;
	orig_len >>= 12;
	orig_len >>= 10;
	orig_len >>= 10;
	sc->count_high += orig_len;
#endif
}
#endif

static void
SPH_XCAT(SPH_XCAT(haval, PASSES), _close)(sph_haval_context *sc,
	unsigned ub, unsigned n, void *dst)
{
	unsigned current;
	DSTATE;

#if SPH_64
	current = (unsigned)sc->count & 127U;
#else
	current = (unsigned)sc->count_low & 127U;
#endif
	sc->buf[current ++] = (0x01 << n) | ((ub & 0xFF) >> (8 - n));
	RSTATE;
	if (current > 118U) {
		memset(sc->buf + current, 0, 128U - current);

		do {
			IN_PREPARE(sc->buf);

			SPH_XCAT(CORE, PASSES)(INW);
		} while (0);
		current = 0;
	}
	memset(sc->buf + current, 0, 118U - current);
	sc->buf[118] = 0x01 | (PASSES << 3);
	sc->buf[119] = sc->olen << 3;
#if SPH_64
	sph_enc64le_aligned(sc->buf + 120, SPH_T64(sc->count << 3));
#else
	sph_enc32le_aligned(sc->buf + 120, SPH_T32(sc->count_low << 3));
	sph_enc32le_aligned(sc->buf + 124,
		SPH_T32((sc->count_high << 3) | (sc->count_low >> 29)));
#endif
	do {
		IN_PREPARE(sc->buf);

		SPH_XCAT(CORE, PASSES)(INW);
	} while (0);

	WSTATE;
	haval_out(sc, dst);
	haval_init(sc, sc->olen, sc->passes);
}
