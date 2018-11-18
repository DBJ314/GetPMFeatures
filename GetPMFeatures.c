#include <MacTypes.h>
#include <CodeFragments.h>
#include <stdio.h>

int (*PMPrimInfo)(int index);//0 is whole array, any other is 1-based index into prim-info
int (*PMFeatures)();
int (*PMPrivateFeatures)();

int main();
void decodePublicPMFeatures(int features);
void decodePrivatePMFeatures(int features);

Str63 libName = "\pNativePowerMgrLib";
CFragConnectionID pmLibConnID;
Ptr pmLibMainAddr;
Str255 errName = "\pNativePowerMgrLib";

Str255 pmpi = "\pPMPrimInfo";
Str255 pmf = "\pPMFeatures";
Str255 pmprivf = "\pPMPrivateFeatures";

CFragSymbolClass resultClass;

int main(){
	int features;
	int privFeatures;
	int pIndex;
	OSErr err;
	printf("GetPMFeatures 1.2 starting up\n");
	
	err = GetSharedLibrary(libName, kPowerPCCFragArch, kReferenceCFrag, &pmLibConnID, &pmLibMainAddr, (unsigned char*)errName);
	
	if(err){
		printf("error loading GetPMFeatures\n");
		return -1;
	}
	
	err = FindSymbol(pmLibConnID, pmpi, (Ptr*)(&PMPrimInfo), &resultClass);
	if(err || resultClass != kTVectorCFragSymbol){
		printf("error loading PMPrimInfo\n");
		CloseConnection(&pmLibConnID);
		return -2;
	}
	
	err = FindSymbol(pmLibConnID, pmf, (Ptr*)(&PMFeatures), &resultClass);
	if(err || resultClass != kTVectorCFragSymbol){
		printf("error loading PMFeatures\n");
		CloseConnection(&pmLibConnID);
		return -2;
	}
	
	err = FindSymbol(pmLibConnID, pmprivf, (Ptr*)(&PMPrivateFeatures), &resultClass);
	if(err || resultClass != kTVectorCFragSymbol){
		printf("error loading PMPrivateFeatures\n");
		CloseConnection(&pmLibConnID);
		return -2;
	}
	
	features = PMFeatures();
	printf("PMFeatures() returned 0x%08x\n\n", features);
	decodePublicPMFeatures(features);
	
	privFeatures = PMPrivateFeatures();
	printf("PMPrivateFeatures() returned 0x%08x\n\n", privFeatures);
	decodePrivatePMFeatures(privFeatures);
	
	printf("PMPrimInfo() array: [");
	for (pIndex = 1; pIndex <= 10 /* actual number of entries is unknown */; pIndex++){
		if(pIndex>1){
			printf(", ");
		}
		printf("0x%08x", PMPrimInfo(pIndex));
	}
	printf(" ]\nScrolling horizontally doesn't work. Resize the window until the ']' is visible.");
		
	CloseConnection(&pmLibConnID);
	return 0;
}

void decodePublicPMFeatures(int features){
	int si = 0;//just to make my life easier copying and pasting
	printf("kPMHasWakeupTimer        = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasSharedModemPort    = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasProcessorCycling   = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMMustProcessorCycle    = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasReducedSpeed       = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMDynamicSpeedChange    = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasSCSIDiskMode       = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMCanGetBatteryTime     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMCanWakeupOnRing       = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasDimmingSupport     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasStartupTimer       = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasChargeNotification = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasDimSuspendSupport  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasWakeOnNetActivity  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasWakeOnLid          = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMCanPowerOffPCIBus     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasDeepSleep          = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasSleep              = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMSupportsServerModeAPI = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasUPSIntegration     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	
	if((features>>si)!=0){
		printf("Additional unknown features at mask 0x%08x\n\n", -1<<si);
	}
}

void decodePrivatePMFeatures(int features){
	int si = 0;//just to make my life easier copying and pasting
	printf("kPMHasExtdBattInfo       = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasBatteryID          = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMCanSwitchPower        = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasCelsiusCycling     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasBatteryPrediction  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasPowerLevel         = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasSleepCPUSpeed      = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasBtnIntHandler      = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasSCSITermPower      = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasADBButtonHandlers  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasICTControl         = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasLegacyDesktopSleep = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasDeepIdle           = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMOpenLidPreventsSleep  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMClosedLidCausesSleep  = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasFanControl         = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasThermalControl     = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMHasVStepSpeedChange   = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	printf("kPMEnvironEventsPolled   = %d (0x%08x)\n",(features>>si)&1, (1<<si));si++;
	
	if((features>>si)!=0){
		printf("Additional unknown features at mask 0x%08x\n\n", -1<<si);
	}
}