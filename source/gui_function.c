#include "3DSident.h"

void	draw_hitbox_button(u16 x1, u16 y1, u16 width, u16 height)
{
	sf2d_draw_rectangle(x1, y1, width, height, RGBA8(255, 0, 0, 50));
}

void	draw_button(s_button *button)
{
	sf2d_draw_texture(button->tex_button, button->x1, button->y1);
}

bool	touch_button(s_button *button, touchPosition *touch, u32 kDown)
{
	draw_hitbox_button(button->x1, button->y1, button->width, button->height);
	if (kDown & KEY_TOUCH)
	{
		if (touch->px >= button->x1 && touch->px <= (button->x1 + button->width) &&
			touch->py >= button->y1 && touch->py <= (button->y1 + button->height))
			return (true);
	}
	return (false);
}

void	init_button(s_button *button,
					sf2d_texture *tex_button,
					u16 x1,
					u16 y1)
{
	button->tex_button = tex_button;
	button->x1 = x1;
	button->y1 = y1;
	button->width = tex_button->width;
	button->height = tex_button->height;
}
