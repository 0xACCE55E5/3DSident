#include "3DSident.h"

PrintConsole	*init_console(void)
{
	gfxInitDefault();
	cfguInit();
	cfgsInit();
	fsInit();
	sdmcInit();
	ptmuInit();
	mcuInit();
	amInit();
	psInit();
	aptInit();
	hidInit();
	acInit();
	gspLcdInit();
	return(consoleInit(GFX_TOP, NULL));
}
