#ifndef __FILE_H__
#define __FILE_H__

#ifdef WIN32

#include <windows.h>

#define sleep(secs) Sleep((secs) * 1000)

enum {
	PRIO_PROCESS		= 0,
};

static inline int setpriority(int which, int who, int prio)
{
	return -!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
}

#endif /* WIN32 */

#endif /* __FILE_H__ */
