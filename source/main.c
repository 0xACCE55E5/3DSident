#include "3DSident.h"

// put .png file in ~/.local/share/citra-emu/sdmc/3ds/3DSident/


void	bottom_screen(sf2d_texture *tex_bottom, sf2d_texture *tex_button)
{
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(tex_bottom, 0, 0);
	/*sf2d_end_frame;*/
}
// Ajouter cur_x et cur_y dans une structure
// fix lorsque quon appuie sur le bouton en dehors de la zone et quon relache le stylet dans la zone du bouton
bool	gui3ds_touch_button_test(s_button *button, touchPosition *touch, u32 kDown, u32 kUp)
{
	static u16	cur_x = 0;
	static u16	cur_y = 0;
	/*sftd_font		*font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);*/

	/*sftd_draw_textf(font, 0, 0, RGBA8(0, 255, 0, 255), 15, "touch.px = %d", cur_x);*/
	/*sftd_draw_textf(font, 0, 20, RGBA8(0, 255, 0, 255), 15, "touch.py = %d", cur_y);*/
	/*if (kDown & KEY_TOUCH)*/
	/*{*/
		/*if (touch->px >= button->x1 && touch->px <= (button->x1 + button->width) &&*/
			/*touch->py >= button->y1 && touch->py <= (button->y1 + button->height))*/
		/*{*/
			if (touch->px && touch->py != 0)
			{
				cur_x = touch->px;
				cur_y = touch->py;
			}
			if (kUp & KEY_TOUCH)
			{
				if (cur_x >= button->x1 && cur_x <= (button->x1 + button->width) &&
					cur_y >= button->y1 && cur_y <= (button->y1 + button->height))
					return (true);
			}
			/*sftd_free_font(font);*/
		/*}*/
	/*}*/
	return (false);
	(void)kUp;
}

void	initialisation_screen()
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	printf("\e[15;17H");
	printf("Initialising ...");
	gfxExit();
}

int		main()
{
	initialisation_screen();

	sf2d_init();
	sftd_init();
	/*if (!init_console())*/
		/*return (EXIT_FAILURE);*/

	u32				kDown;
	/*u32				kHeld;*/
	u32				kUp;
	touchPosition	touch;
	/*sftd_font		*font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);*/
	sf2d_texture	*tex_top = sfil_load_PNG_file("3ds/3DSident/assets/top_background.png", SF2D_PLACE_RAM);
	sf2d_texture	*tex_bottom = sfil_load_PNG_file("3ds/3DSident/assets/bottom_background.png", SF2D_PLACE_RAM);
	sf2d_texture	*tex_button = sfil_load_PNG_file("3ds/3DSident/assets/button.png", SF2D_PLACE_RAM);
	s_button		button_1;
	gui3ds_init_button_texture(&button_1, tex_button, 90, 190);
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
		kUp = hidKeysUp();
		kDown = hidKeysDown();
		/*kHeld = hidKeysHeld();*/
		/*kUp = hidKeysUp();*/
		if (kDown & KEY_START)
			break;
		bottom_screen(tex_bottom, tex_button);
		gui3ds_draw_button_texture(&button_1);
		if (gui3ds_touch_button_test(&button_1, &touch, kDown, kUp) == true)
			break ;
		/*if (kDown & KEY_TOUCH)*/
		/*{*/
			/*if (touch.px >= 90 && touch.px <= (90 + tex_button->width) && touch.py >= 90 && touch.py <= (90 + tex_button->height))*/
			/*{*/
				/*break;*/
			/*}*/
		/*}*/
		sf2d_swapbuffers();
	}
	/*sftd_free_font(font);*/
	sf2d_free_texture(tex_bottom);
	sf2d_free_texture(tex_top);
	sf2d_free_texture(tex_button);
	sf2d_fini();
	sftd_fini();
	return (0);
}
