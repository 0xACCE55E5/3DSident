#include "3DSident.h"

void	firm_info()
{
	u32					os_ver = osGetKernelVersion(),
						firm_ver = osGetKernelVersion();
	OS_VersionBin		*nver = (OS_VersionBin *)malloc(sizeof(OS_VersionBin)),
						*cver = (OS_VersionBin *)malloc(sizeof(OS_VersionBin));
	s32					ret;

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
				nver->mainver);
	free(nver);
	free(cver);
}

void	sys_info()
{
	u32	nnidNum = 0xFFFFFFFF;

	printf("\x1b[31;1m*\x1b[0m Model: \x1b[31;1m%s %s\n\x1b[0m", getModel(), getRegion());
	getScreenType();
	printf("\x1b[31;1m*\x1b[0m Language: \x1b[31;1m%s\x1b[0m \n", getLang());
	nnidNum = 0xFFFFFFFF;
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
}

void	battery_info()
{
	u8					batteryPercent,
						batteryVolt;

	printf("\x1b[18;0H");
	mcuGetBatteryLevel(&batteryPercent);
	printf("\x1b[34;1m*\x1b[0m Battery percentage: \x1b[34;1m%3d%%\x1b[0m (\x1b[34;1m%s\x1b[0m)      \n\x1b[0m", batteryPercent, get_battery_status());
	printf("\x1b[19;0H");
	mcuGetBatteryVoltage(&batteryVolt);
	printf("\x1b[34;1m*\x1b[0m Battery voltage: \x1b[34;1m%d\x1b[0m\n \n", batteryVolt);//,(Estimated: %0.1lf V) estimatedVolt);
}

void	misc_info()
{
	FS_ArchiveResource	resource = {0};
	u8					volume;
	double				wifiPercent,
						volPercent,
						_3dSliderPercent;
	u32					installedTitles = titleCount(MEDIATYPE_SD);
	
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
}

void	misc_info_refresh()
{
	double				wifiPercent,
						volPercent,
						_3dSliderPercent;
	u8					volume;

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
}

