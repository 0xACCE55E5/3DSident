#include "3DSident.h"

void	draw_hitbox_button(u16 x1, u16 y1, u16 width, u16 height)
{
	sf2d_draw_rectangle(x1, y1, width, height, RGBA8(255, 0, 0, 50));
}

void	place_button(sf2d_texture *tex_button, u16 x1, u16 y1)
{
	sf2d_draw_texture(tex_button, x1, y1);
}

void	place_button_test(s_button *button)
{
	sf2d_draw_texture(button->tex_button, button->x1, button->y1);
}

bool	touch_button(u16 x1, u16 y1, u16 width, u16 height, touchPosition *touch, u32 kDown)
{
	/*draw_hitbox_button(x1, y1, width, height);*/
	if (kDown & KEY_TOUCH)
	{
		if (touch->px >= x1 && touch->px <= (x1 + width) && touch->py >= y1 && touch->py <= (y1 + height))
			return (true);
	}
	return (false);
}

void	init_button(s_button *button,
					sf2d_texture *tex_button,
					u16 x1,
					u16 y1,
					u16 width,
					u16 height)
{
	button->tex_button = tex_button;
	button->x1 = x1;
	button->y1 = y1;
	button->width = width;
	button->height = height;
}
