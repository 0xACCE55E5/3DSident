#include "3DSident.h"

int				quit_console(void)
{
	gspLcdExit();
	acExit();
	hidExit();
	aptExit();
	psExit();
	amExit();
	mcuExit();
	ptmuExit();
	sdmcExit();
	fsExit();
	cfgsExit();
	cfguExit();
	gfxExit();
	return(0);
}	