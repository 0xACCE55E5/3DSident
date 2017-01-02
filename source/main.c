#include "3DSident.h"

int		main(int argc, char *argv[])
{
	if (!init_console())
		return (EXIT_FAILURE);

	printf("\x1b[0;18H");
	printf("\x1b[32;1m3DSident 0.7\x1b[0m\n\n");
	firm_info();
	sys_info();
	battery_info();
	misc_info();
	printf("\n\x1b[32;1m             Press any key to exit =)\x1b[0m\n");

	while (aptMainLoop()) //loop for refreshing info
	{
		battery_info();
		misc_info_refresh();
		gspWaitForVBlank();
		hidScanInput();
		if (hidKeysDown())
			break;
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	return (quit_console());
}
