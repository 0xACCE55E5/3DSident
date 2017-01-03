#include "3DSident.h"

void	bottom_screen(sf2d_texture *texture)
{
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(texture, 0, 0);
	/*sf2d_end_frame;*/
	sf2d_swapbuffers();
}

int		main()
{
	sf2d_init();
	sftd_init();
	/*if (!init_console())*/
		/*return (EXIT_FAILURE);*/

	u32	kDown;
	sftd_font *font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);
	sf2d_texture *texture = sfil_load_PNG_file("3ds/3DSident/bottom_background.png", SF2D_PLACE_RAM); // put .png file in ~/.local/share/citra-emu/sdmc/3ds/3DSident/

	/*printf("\x1b[0;18H");*/
	/*printf("\x1b[32;1m3DSident 0.7\x1b[0m\n\n");*/
	/*firm_info();*/
	/*sys_info();*/
	/*battery_info();*/
	/*misc_info();*/
	/*printf("\n\x1b[32;1m             Press start to exit =)\x1b[0m\n");*/
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sftd_draw_text(font, 320/2 +10, 0, RGBA8(0, 255, 0, 255), 15, "3DSident");
	/*sf2d_end_frame;*/


	while (aptMainLoop()) //loop for refreshing info
	{

		/*battery_info();*/
		/*misc_info_refresh();*/
		/*gspWaitForVBlank();*/
		hidScanInput();
		kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;
		/*gfxFlushBuffers();*/
		/*gfxSwapBuffers();*/
		bottom_screen(texture);
	}
	sftd_free_font(font);
	return (quit_console());
}
