#include "3DSident.h"

char	*get_nand_cid(void)
{
	static char nand[30];
	u8 buf[16];

	FSUSER_GetNandCid(buf, 0x10);
	sprintf(nand, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5],
			buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], 
			buf[12], buf[13], buf[14], buf[15]);
	return(nand);
}

char	*get_sdmc_cid(void)
{
	static char sdmc[30];
	u8 buf[16];

	FSUSER_GetSdmcCid(buf, 0x10);
	sprintf(sdmc, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\x1b",
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5],
			buf[6], buf[7], buf[8], buf[9], buf[10], buf[11],
			buf[12], buf[13], buf[14], buf[15]);
    return (sdmc);
}

const char * get_battery_status()
{
    u8 batteryStateBool;
    PTMU_GetBatteryChargeState(&batteryStateBool);

    if (!batteryStateBool) 
        return "Not charging";
    else 
        return "Charging";
}

char * getMacAddress()
{
    u8* macByte = (u8*)0x1FF81060; 
    static char macAddress[18];

    //sprintf automatically zero-terminates the string
    sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", *macByte, *(macByte + 1), *(macByte + 2), *(macByte + 3), *(macByte + 4), *(macByte + 5));

    return macAddress;
}


FriendKey getMyFriendKey(void)
{
    FriendKey fk;
    
	frdGetMyFriendKey(&fk);
    
	return fk;
}

char	*getSerialNum(void)
{
	static char str[32];
    char serial[0x10];
	
    cfgsSecureInfoGetSerialNo(serial);
    strcpy(str, serial);
    
	return (str);
}

u32 getDeviceId(void)
{
    u32 tmp = 0;
    AM_GetDeviceId(&tmp);
    return (tmp);
}

u64 getSoapId(void)
{
    u32 tmp = 0;
    AM_GetDeviceId(&tmp);
    return (tmp | (((u64) 4) << 32));
}
