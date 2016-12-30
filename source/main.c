
#include "3DSident.h"


#define SDK(a,b,c,d) ((a<<24)|(b<<16)|(c<<8)|d)

int vaPrint(char *format, ...)
{
    va_list args;
    va_start(args, format);
	int ret = vprintf(format, args);
    va_end(args);
	gfxFlushBuffers();
	gfxSwapBuffers();
	return ret;
}

const char * getModel()
{
    const char *models[] = 
	{
        "O3DS",
        "O3DS XL",
        "N3DS",
        "2DS",
        "N3DS XL",
        "Unknown"
    };
    u8 model = 0;

    CFGU_GetSystemModel(&model);
    if (model < 5)
        return models[model];
    else
        return models[5];
}

const char * getRegion()
{
    const char *regions[] = 
	{
        "JPN",
        "USA",
        "EUR",
        "AUS",
        "CHN",
        "KOR",
        "TWN",
        "Unknown"
    };
    u8 region = 0;

    CFGU_SecureInfoGetRegion(&region);
    if (region < 7)
        return regions[region];
    else
        return regions[7];
}

const char * getLang()
{
    const char *languages[] = 
	{
        "Japanese",
        "English",
        "French",
        "German",
        "Italian",
        "Spanish",
        "Simplified Chinese",
        "Korean",
        "Dutch",
        "Portugese",
        "Russian",
        "Traditional Chinese"
    };
    u8 language;

    CFGU_GetSystemLanguage(&language);
    if (language < 11)
        return languages[language];
    else
        return languages[11];
}

bool detectSD()
{
    bool isSD;
    FSUSER_IsSdmcDetected(&isSD);
    return isSD;
}

u32 titleCount(FS_MediaType mediaType)
{
	u32 count = 0;
	
	AM_GetTitleCount(mediaType, &count);

    return count;
}

void getScreenType()
{
	bool isNew3DS = 0;
    APT_CheckNew3DS(&isNew3DS);
	
	printf("\x1b[31;1m*\x1b[0m Screen Info: ");
	
    if (isNew3DS)
    {
        u8 screens = 0;
        GSPLCD_GetVendors(&screens);
        switch ((screens >> 4) & 0xF)
        {
            case 1:
				printf("Upper: \x1b[31;1mIPS\x1b[0m ");
                break;
            case 0xC:
                printf("Upper: \x1b[31;1mTN\x1b[0m ");
                break;
            default:
                printf("Upper: \x1b[31;1mUnknown \x1b[0m");
                break;
        }
        switch (screens & 0xF)
        {
            case 1:
                printf("| Lower: \x1b[31;1mIPS\x1b[0m\n");
                break;
            case 0xC:
                printf("| Lower: \x1b[31;1mTN\x1b[0m\n");
                break;
            default:
                printf("| Lower: \x1b[31;1mUnknown\x1b[0m\n");
                break;
        }
    }
	
    else
    {
        printf("Upper: \x1b[31;1mTN\x1b[0m | Lower: \x1b[31;1mTN\n");
    }
}

u64 principalIdToFriendCode(u64 pid)
{
	u64 fc = 0;
	
    frdPrincipalIdToFriendCode(&fc, pid);
    
	return fc;
}

int main(int argc, char *argv[])
{

	if (!init_console())
		return (EXIT_FAILURE);
	/*
	**------------------------Variable Declaration-------------------------**
	*/
	FS_ArchiveResource	resource = {0};

	OS_VersionBin		*nver = (OS_VersionBin *)malloc(sizeof(OS_VersionBin)),
						*cver = (OS_VersionBin *)malloc(sizeof(OS_VersionBin));

	double				wifiPercent,
						volPercent,
						_3dSliderPercent;

	u32					os_ver = osGetKernelVersion(),
						firm_ver = osGetKernelVersion(),
						installedTitles = titleCount(MEDIATYPE_SD),
						nnidNum = 0xFFFFFFFF;

	u8					batteryPercent,
						batteryVolt,
						volume;

	s32					ret;

	consoleClear();
	printf("\x1b[0;0H"); //Move the cursor to the top left corner of the screen
	printf("\x1b[32;1m3DSident 0.7\x1b[0m\n\n");
	/*
	**------------------------------Firm Info------------------------------
	*/
	printf("\x1b[33;1m*\x1b[0m Kernel version: \x1b[33;1m%lu.%lu-%lu\n*\x1b[0m FIRM version is: \x1b[33;1m%lu.%lu-%lu\x1b[0m \n",
			GET_VERSION_MAJOR(os_ver),
			GET_VERSION_MINOR(os_ver),
			GET_VERSION_REVISION(os_ver),
			GET_VERSION_MAJOR(firm_ver),
			GET_VERSION_MINOR(firm_ver),
			GET_VERSION_REVISION(firm_ver));

	memset(nver, 0, sizeof(OS_VersionBin));
	memset(cver, 0, sizeof(OS_VersionBin));
	ret = osGetSystemVersionData(nver, cver);

	if (ret)
		printf("\x1b[33;1m*\x1b[0m osGetSystemVersionData returned 0x%08liX\n\n", ret);
	else
		printf("\x1b[33;1m*\x1b[0m Current system version: \x1b[33;1m%d.%d.%d-%d\x1b[0m\n\n",
			cver->mainver,
			cver->minor,
			cver->build,
			nver->mainver
			);
	/*
	**-----------------------------System Info-----------------------------**
	*/
	printf("\x1b[31;1m*\x1b[0m Model: \x1b[31;1m%s %s\n\x1b[0m", getModel(), getRegion());
	getScreenType();
	printf("\x1b[31;1m*\x1b[0m Language: \x1b[31;1m%s\x1b[0m \n", getLang());
	nnidNum = 0xFFFFFFFF;
	ret = actInit();
	ret = ACTU_Initialize(0xB0002C8, 0, 0);
	ret = ACTU_GetAccountDataBlock(0xFE, 4, 12, &nnidNum);
	ret = actExit();

	if (nnidNum != 0xFFFFFFFF)
		vaPrint("\x1b[31;1m*\x1b[0m NNID number: \x1b[31;1m%08X\x1b[0m \n", (int) nnidNum);
	else
		vaPrint("\x1b[31;1m*\x1b[0m NNID number: \x1b[31;1mError could not retrieve NNID\x1b[0m \n");

	printf("\x1b[31;1m*\x1b[0m Device ID: \x1b[31;1m%lu \n", getDeviceId());
	printf("\x1b[31;1m*\x1b[0m ECS Device ID: \x1b[31;1m%llu \n", getSoapId());
	printf("\x1b[31;1m*\x1b[0m MAC Address: \x1b[31;1m%s\x1b[0m \n", getMacAddress());
	printf("\x1b[31;1m*\x1b[0m Serial number: \x1b[31;1m%s\x1b[0m \n", getSerialNum());
	printf("\x1b[31;1m*\x1b[0m SDMC CID: \x1b[31;1m%s\x1b[0m \n", get_sdmc_cid());
	printf("\x1b[31;1m*\x1b[0m NAND CID: \x1b[31;1m%s\x1b[0m\n \n",get_nand_cid());
	/*
	** ----------------------------Battery Info-----------------------------**
	*/
	mcuGetBatteryLevel(&batteryPercent);
	printf("\x1b[34;1m*\x1b[0m Battery percentage: \x1b[34;1m%3d%%\x1b[0m (\x1b[34;1m%s\x1b[0m) \n\x1b[0m", batteryPercent, get_battery_status());
	mcuGetBatteryVoltage(&batteryVolt);
	printf("\x1b[34;1m*\x1b[0m Battery voltage: \x1b[34;1m%d\x1b[0m\n \n", batteryVolt);//,(Estimated: %0.1lf V) estimatedVolt);
	/*
	**------------------------------Misc Info------------------------------**
	*/
	FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_SD);
	printf("\x1b[32;1m*\x1b[0m SD Size: \x1b[32;1m%.1f \x1b[0mMB / \x1b[32;1m%.1f\x1b[0m MB \n",
			(((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0),
			(((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0));
	FSUSER_GetArchiveResource(&resource, SYSTEM_MEDIATYPE_CTR_NAND);
	printf("\x1b[32;1m*\x1b[0m CTR Size: \x1b[32;1m%.1f\x1b[0m MB / \x1b[32;1m%.1f\x1b[0m MB \n",
			(((u64) resource.freeClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0),
			(((u64) resource.totalClusters * (u64) resource.clusterSize) / 1024.0 / 1024.0));
	printf("\x1b[32;1m*\x1b[0m Installed titles: \x1b[32;1m%i\x1b[0m\n", (int)installedTitles);
	wifiPercent = (osGetWifiStrength() * 33.3333333333);
	printf("\x1b[32;1m*\x1b[0m WiFi signal strength: \x1b[32;1m%d\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m) \n", osGetWifiStrength(), wifiPercent);
	mcuGetVolume(&volume);
	volPercent = (volume * 1.5873015873);
	printf("\x1b[32;1m*\x1b[0m Volume slider state: \x1b[32;1m%d\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m) \n", volume, volPercent);
	_3dSliderPercent = (osGet3DSliderState() * 100.0);
	printf("\x1b[32;1m*\x1b[0m 3D slider state: \x1b[32;1m%.1lf\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m)   \n", osGet3DSliderState(), _3dSliderPercent);
	printf("\n\x1b[32;1m> Press any key to exit =)\x1b[0m\n");

	while (aptMainLoop())
	{
		//=====================================================================//
		//----------------------------Battery Info-----------------------------//
		//=====================================================================//
		
		printf("\x1b[18;0H"); //Move the cursor to the top left corner of the screen
		mcuGetBatteryLevel(&batteryPercent);
		printf("\x1b[34;1m*\x1b[0m Battery percentage: \x1b[34;1m%3d%%\x1b[0m (\x1b[34;1m%s\x1b[0m)     \n\x1b[0m", batteryPercent, get_battery_status());

		printf("\x1b[19;0H"); //Move the cursor to the top left corner of the screen
		mcuGetBatteryVoltage(&batteryVolt);
		printf("\x1b[34;1m*\x1b[0m Battery voltage: \x1b[34;1m%d\x1b[0m\n \n", batteryVolt);//,(Estimated: %0.1lf V) estimatedVolt);

		//=====================================================================//
		//------------------------------Misc Info------------------------------//
		//=====================================================================//

		printf("\x1b[24;0H"); //Move the cursor to the top left corner of the screen
		wifiPercent = (osGetWifiStrength() * 33.3333333333);
		printf("\x1b[32;1m*\x1b[0m WiFi signal strength: \x1b[32;1m%d\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m) \n", osGetWifiStrength(), wifiPercent);

		printf("\x1b[25;0H"); //Move the cursor to the top left corner of the screen
		mcuGetVolume(&volume);
		volPercent = (volume * 1.5873015873);
		printf("\x1b[32;1m*\x1b[0m Volume slider state: \x1b[32;1m%d\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m)  \n", volume, volPercent);

		printf("\x1b[26;0H"); //Move the cursor to the top left corner of the screen
		_3dSliderPercent = (osGet3DSliderState() * 100.0);
		printf("\x1b[32;1m*\x1b[0m 3D slider state: \x1b[32;1m%.1lf\x1b[0m  (\x1b[32;1m%.0lf%%\x1b[0m)   \n", osGet3DSliderState(), _3dSliderPercent);

		gspWaitForVBlank();

		hidScanInput();

		if (hidKeysDown())
			break;
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	free(nver);
	free(cver);
	return (quit_console());
}
