#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <png.h>
#include <zlib.h>

#pragma once
#define NUM_LEVELS (Z_BEST_COMPRESSION - Z_NO_COMPRESSION + 1)
#define screenshotPath "/3ds/3DSident/screenshots/3DSident.png"

typedef struct
{
   u32 principalId;
   u64 localFriendCode;
} FriendKey;

FS_Archive sdmcArchive;
int level, screenCapture;
unsigned int format_choice;
GSPGPU_FramebufferFormats format; // = GSP_RGBA8_OES
/*
**	actu.c
*/
Result	actInit(void);
Result	actExit(void);
Result	ACTU_Initialize(u32 sdkVersion, u32 unknown, Handle handle);
Result	ACTU_GetAccountDataBlock(u32 unknown, u32 size, u32 blockId, void* output);
/*
**	am.c
*/
Handle	amHandle;
Result	AMNet_GetDeviceCert(u8 *buffer);
/*
**	cfgs.c
*/
Handle	cfgHandle;
Result	cfgsInit();
Result	cfgsExit();
Result	cfgsSecureInfoGetSerialNo(char *serial);
/*
**	frd.c
*/
Handle	frdHandle;
Result	frdInit();
Result	frdExit();
Result	frdSetClientSdkVersion(u32 sdkVer);
u64		frdPrincipalIdToFriendCode(u64 *fc, u64 pid);
Result	frdGetMyFriendKey(FriendKey *key);
/*
**	fs.c
*/
void	openSdArchive();
void	closeSdArchive();
int		makeDir(const char * path);
bool	fileExists(char * path);
bool	dirExists(const char * path);
bool	deleteFile(const char *path);
/*
**	mcu.c
*/
Handle	mcuhwcHandle;
Result	mcuInit();
Result	mcuExit();
Result	mcuGetBatteryLevel(u8* out);
Result	mcuGetBatteryVoltage(u8* out);
Result	mcuGetVolume(u8* out);
/*
** screenshot.c
*/
void	captureScreenshot();

