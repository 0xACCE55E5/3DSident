#include "3DSident.h"

/*void	bottom_screen(sftd_font *font)*/
/*{*/
	/*sf2d_start_frame(GFX_BOTTOM, GFX_RIGHT);*/
		/*sftd_draw_text(font, 10, 10,RGBA8(255, 0, 0, 255), 20, "Hello world");*/
	/*[>sf2d_end_frame;<]*/
	/*sf2d_swapbuffers();*/
/*}*/

int		main()
{
	/*sf2d_init();*/
	/*sftd_init();*/
	if (!init_console())
		return (EXIT_FAILURE);

	u32	kDown;
	/*sftd_font *font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);*/

	printf("\x1b[0;18H");
	printf("\x1b[32;1m3DSident 0.7\x1b[0m\n\n");
	firm_info();
	sys_info();
	battery_info();
	misc_info();
	printf("\n\x1b[32;1m             Press start to exit =)\x1b[0m\n");
	while (43){}

	/*sf2d_texture *texture = sfil_load_PNG_buffer("../resources/gui/bottom_background.jpg", SF2D_PLACE_RAM);*/
	while (aptMainLoop()) //loop for refreshing info
	{

		battery_info();
		misc_info_refresh();
		gspWaitForVBlank();
		hidScanInput();
		kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;
		gfxFlushBuffers();
		gfxSwapBuffers();
		/*bottom_screen(font);*/
	}
	return (quit_console());
}
