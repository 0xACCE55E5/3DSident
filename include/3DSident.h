//#ifndef 3DSIDENT_H
//#define 3DSIDENT_H

#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <unistd.h>
//#include <png.h>
#include <zlib.h>
#include <sfil.h>
#include <sf2d.h>
#include <sftd.h>
/*
** modifier le .h par le nom d'un autre font pour changer le font (et aussi dans
** la fonction sftd_load_font_mem)
*/
#include "FreeSans_ttf.h"

#define WIDTH_TOP 400
#define HEIGHT_TOP 240
#define WIDTH_BOT 320
#define HEIGHT_BOT 240

#pragma once

#define NUM_LEVELS (Z_BEST_COMPRESSION - Z_NO_COMPRESSION + 1)
#define screenshotPath "/3ds/3DSident/screenshots/3DSident.png"

typedef struct
{
	u32 principalId;
	u64 localFriendCode;
}	FriendKey;

typedef struct		button
{
	u16				x1;
	u16				y1;
	u16				width;
	u16				height;
	touchPosition	touch;
	sf2d_texture	*tex_button;
}					s_button;

FS_Archive					sdmcArchive;
int							level, screenCapture;
unsigned int				format_choice;
GSPGPU_FramebufferFormats	format; // = GSP_RGBA8_OES
/*
 **	actu.c
 */
Result		actInit(void);
Result		actExit(void);
Result		ACTU_Initialize(u32 sdkVersion, u32 unknown, Handle handle);
Result		ACTU_GetAccountDataBlock(u32 unknown, u32 size, u32 blockId, void* output);
/*
 **	am.c
 */
Handle		amHandle;
Result		AMNet_GetDeviceCert(u8 *buffer);
/*
 **	cfgs.c
 */
Handle		cfgHandle;
Result		cfgsInit();
Result		cfgsExit();
Result		cfgsSecureInfoGetSerialNo(char *serial);
/*
 **	frd.c
 */
Handle		frdHandle;
Result		frdInit();
Result		frdExit();
Result		frdSetClientSdkVersion(u32 sdkVer);
u64			frdPrincipalIdToFriendCode(u64 *fc, u64 pid);
Result		frdGetMyFriendKey(FriendKey *key);
/*
 **	fs.c
 */
void		openSdArchive();
void		closeSdArchive();
int			makeDir(const char * path);
bool		fileExists(char * path);
bool		dirExists(const char * path);
bool		deleteFile(const char *path);
/*
 **	mcu.c
 */
Handle		mcuhwcHandle;
Result		mcuInit();
Result		mcuExit();
Result		mcuGetBatteryLevel(u8* out);
Result		mcuGetBatteryVoltage(u8* out);
Result		mcuGetVolume(u8* out);
/*
 ** screenshot.c
 */
void		captureScreenshot();

/*
 ** quitconsole.c
 */
int			quit_console(void);

/*
 ** init_console.c
 */
PrintConsole	*init_console(void);

/*
 ** get_info.c
 */
const char	*get_battery_status();
const char	*getModel();
const char	*getRegion();
const char	*getLang();
char		*get_nand_cid(void);
char		*get_sdmc_cid(void);
char		*getMacAddress();
char		*getSerialNum(void);
u32			getDeviceId(void);
u64			getSoapId(void);
FriendKey	getMyFriendKey(void);
void		getScreenType();

/*
 ** other.c
 */
u32			titleCount(FS_MediaType mediaType);
int			vaPrint(char *format, ...);

/*
 ** other.c
 */
void	firm_info();
void	sys_info();
void	battery_info();
void	misc_info();
void	misc_info_refresh();

/*
 ** gui_function.c
 */
void	init_button(s_button *button,
					sf2d_texture *tex_button,
					u16 x1,
					u16 y1);

void	draw_button(s_button *button);

bool	touch_button(s_button *button, touchPosition *touch, u32 kDown);


void	draw_hitbox_button(	u16 x1,
							u16 y1,
							u16 width,
							u16 height);


//#endif
