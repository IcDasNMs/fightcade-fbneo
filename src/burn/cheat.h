#define CHEAT_MAX_ADDRESS (512)
#define CHEAT_MAX_OPTIONS (512)
#define CHEAT_MAX_NAME	  (128)

extern bool bCheatsAllowed;

struct CheatAddressInfo {
	INT32 nCPU;
	INT32 nAddress;
	UINT32 nValue;
	UINT32 nOriginalValue;
};

struct CheatOption {
	TCHAR szOptionName[CHEAT_MAX_NAME];
	struct CheatAddressInfo AddressInfo[CHEAT_MAX_ADDRESS + 1];
};

struct CheatInfo {
	struct CheatInfo* pNext;
	struct CheatInfo* pPrevious;
	INT32 nType;								// Cheat type
	INT32 nStatus;								// 0 = Inactive
	INT32 nCurrent;								// Currently selected option
	INT32 nDefault;								// Default option
	INT32 bOneShot;                             // For one-shot cheats, also acts as a frame counter for them.
	INT32 bRestoreOnDisable;                    // Restore previous value on disable
	INT32 bWatchMode;                           // Display value on screen
	INT32 bWaitForModification;                 // Wait for Modification before changing
	INT32 bModified;                            // Wrote cheat?
	TCHAR szCheatName[CHEAT_MAX_NAME];
	struct CheatOption* pOption[CHEAT_MAX_OPTIONS];
};

extern CheatInfo* pCheatInfo;

INT32 CheatUpdate();
INT32 CheatEnable(INT32 nCheat, INT32 nOption);
INT32 CheatApply();
INT32 CheatInit();
void CheatExit();

#define CHEATSEARCH_SHOWRESULTS		3
extern UINT32 CheatSearchShowResultAddresses[CHEATSEARCH_SHOWRESULTS];
extern UINT32 CheatSearchShowResultValues[CHEATSEARCH_SHOWRESULTS];

INT32 CheatSearchInit();
void CheatSearchExit();
void CheatSearchStart();
UINT32 CheatSearchValueNoChange();
UINT32 CheatSearchValueChange();
UINT32 CheatSearchValueDecreased();
UINT32 CheatSearchValueIncreased();
void CheatSearchDumptoFile();

typedef void (*CheatSearchInitCallback)();
extern CheatSearchInitCallback CheatSearchInitCallbackFunction;
void CheatSearchExcludeAddressRange(UINT32 nStart, UINT32 nEnd);

typedef UINT32 HWAddressType;

unsigned int ReadValueAtHardwareAddress(HWAddressType address, unsigned int size, int isLittleEndian);
unsigned int ReadValueAtHardwareAddress_audio(HWAddressType address, unsigned int size, int isLittleEndian);

bool WriteValueAtHardwareAddress(HWAddressType address, unsigned int value, unsigned int size, int isLittleEndian);
bool WriteValueAtHardwareAddress_audio(HWAddressType address, unsigned int value, unsigned int size, int isLittleEndian);

bool IsHardwareAddressValid(HWAddressType address);
