#include "3DSident.h"

int vaPrint(char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	gfxFlushBuffers();
	gfxSwapBuffers();
	return ret;
}

bool detectSD()
{
	bool	isSD;

FSUSER_IsSdmcDetected(&isSD);
	return isSD;
}

u32 titleCount(FS_MediaType mediaType)
{
	u32	count = 0;

	AM_GetTitleCount(mediaType, &count);
	return count;
}

u64 principalIdToFriendCode(u64 pid)
{
	u64	fc = 0;

	frdPrincipalIdToFriendCode(&fc, pid);
	return fc;
}
