#include "3DSident.h"

// put .png file in ~/.local/share/citra-emu/sdmc/3ds/3DSident/


void	bottom_screen(sf2d_texture *tex_bottom, sf2d_texture *tex_button)
{
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(tex_bottom, 0, 0);
		place_button(tex_button, 90, 90);
	/*sf2d_end_frame;*/
}

int		main()
{
	sf2d_init();
	sftd_init();
	/*if (!init_console())*/
		/*return (EXIT_FAILURE);*/

	u32				kDown;
	/*u32				kHeld;*/
	/*u32				kUp;*/
	touchPosition	touch;
	sftd_font		*font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);
	sf2d_texture	*tex_top = sfil_load_PNG_file("3ds/3DSident/assets/top_background.png", SF2D_PLACE_RAM);
	sf2d_texture	*tex_bottom = sfil_load_PNG_file("3ds/3DSident/assets/bottom_background.png", SF2D_PLACE_RAM);
	sf2d_texture	*tex_button = sfil_load_PNG_file("3ds/3DSident/assets/button.png", SF2D_PLACE_RAM);
	s_button		button_1;
	init_button(&button_1, tex_button, 0, 0, tex_button->width, tex_button->height);
	/*firm_info();*/
	/*sys_info();*/
	/*battery_info();*/
	/*misc_info();*/
	/*printf("\n\x1b[32;1m             Press start to exit =)\x1b[0m\n");*/
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(tex_top, 0, 0);
	/*sf2d_end_frame;*/
	/*sf2d_start_frame(GFX_TOP, GFX_LEFT);*/
		/*sftd_draw_text(font, 320/2 +10, 0, RGBA8(0, 255, 0, 255), 15, "3DSident");*/
	/*[>sf2d_end_frame;<]*/

	while (aptMainLoop()) //loop for refreshing info
	{
		/*battery_info();*/
		/*misc_info_refresh();*/
		/*gspWaitForVBlank();*/
		/*gfxFlushBuffers();*/
		/*gfxSwapBuffers();*/
		hidScanInput();
		hidTouchRead(&touch);
		kDown = hidKeysDown();
		/*kHeld = hidKeysHeld();*/
		/*kUp = hidKeysUp();*/
		if (kDown & KEY_START)
			break;
		bottom_screen(tex_bottom, tex_button);
		place_button_test(&button_1);
		if (touch_button(90, 90, tex_button->width, tex_button->height, &touch, kDown) == true)
			break ;
		/*if (kDown & KEY_TOUCH)*/
		/*{*/
			/*if (touch.px >= 90 && touch.px <= (90 + tex_button->width) && touch.py >= 90 && touch.py <= (90 + tex_button->height))*/
			/*{*/
				/*break;*/
			/*}*/
		/*}*/
		sftd_draw_textf(font, 0, 0, RGBA8(0, 255, 0, 255), 15, "touch.px = %d", touch.px);
		sftd_draw_textf(font, 0, 20, RGBA8(0, 255, 0, 255), 15, "touch.py = %d", touch.py);
		sf2d_swapbuffers();
	}
	sftd_free_font(font);
	sf2d_free_texture(tex_bottom);
	sf2d_free_texture(tex_top);
	sf2d_free_texture(tex_button);
	sf2d_fini();
	sftd_fini();
	return (0);
}
