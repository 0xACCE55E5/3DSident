#include "3DSident.h"


Result frdInit(u32 sdkVer)
{
	srvGetServiceHandle(&frdHandle, "frd:u");
	srvGetServiceHandle(&frdHandle, "frd:n");
	srvGetServiceHandle(&frdHandle, "frd:a");
	return frdSetClientSdkVersion(sdkVer);
}

Result frdExit()
{
	return svcCloseHandle(frdHandle);
}

Result frdSetClientSdkVersion(u32 sdkVer)
{
	Result ret=0;
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x32,1,2); // 0x00320042
	cmdbuf[1] = sdkVer;
	cmdbuf[2] = 0x20;
	if(R_FAILED(ret = svcSendSyncRequest(frdHandle)))
		return ret;
	return (Result)cmdbuf[1];
}

u64 frdPrincipalIdToFriendCode(u64 *fc, u64 pid)
{
	Result ret=0;
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(0x24,1,0); // 0x00240040
	cmdbuf[1] = pid;
	if(R_FAILED(ret = svcSendSyncRequest(frdHandle)))
		return ret;
	*fc = (u64)cmdbuf[2];
	return (Result)cmdbuf[1];
}

Result frdGetMyFriendKey(FriendKey *key)
{
	Result ret=0;
	u32 *cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(5,0,0); // 0x00050000
	if(R_FAILED(ret = svcSendSyncRequest(frdHandle)))
		return ret;
	memcpy(key, &cmdbuf[2], 0x10);
	return (Result)cmdbuf[1];
}