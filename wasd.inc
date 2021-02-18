#if defined __WASD_INC_INCLUDED__
#endinput
#endif
#define __WASD_INC_INCLUDED__

// ------------------------------------------------------------ 

/*

WASD Callback Include by NaS

Adds OnPlayerWASDStateChange which works similar to OnPlayerKeyStateChange

*/

// ------------------------------------------------------------ 

// Timer Interval in ms, 0 or negative value => use OnPlayerUpdate (smoothest)

#if !defined WASD_TIMER_INTERVAL
#define WASD_TIMER_INTERVAL 0
#endif

// States

#define WASD_STATE_LEFT		1
#define WASD_STATE_RIGHT	2
#define WASD_STATE_UP 		4
#define WASD_STATE_DOWN 	8

// ------------------------------------------------------------ 

forward OnPlayerWASDStateChange(playerid, newstate, oldstate);

#if WASD_TIMER_INTERVAL > 0
forward WASD_Update();
#endif

// ------------------------------------------------------------ 

static 
	bool:gWASDInit = false,

	#if WASD_TIMER_INTERVAL > 0
	gWASDTimerID = -1,
	#endif

	gPlayerWASDState[MAX_PLAYERS];

// ------------------------------------------------------------ 

public OnGameModeInit()
{
	WASD_Init();

	#if defined WASDINC_OnGameModeInit
		return WASDINC_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit WASDINC_OnGameModeInit
#if defined WASDINC_OnGameModeInit
	forward WASDINC_OnGameModeInit();
#endif

// ------------------------------------------------------------ 

public OnGameModeExit()
{
	WASD_Exit();

	#if defined WASDINC_OnGameModeExit
		return WASDINC_OnGameModeExit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit WASDINC_OnGameModeExit
#if defined WASDINC_OnGameModeExit
	forward WASDINC_OnGameModeExit();
#endif

// ------------------------------------------------------------ 

public OnFilterScriptInit()
{
	WASD_Init();

	#if defined WASDINC_OnFilterScriptInit
		return WASDINC_OnFilterScriptInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit WASDINC_OnFilterScriptInit
#if defined WASDINC_OnFilterScriptInit
	forward WASDINC_OnFilterScriptInit();
#endif

// ------------------------------------------------------------ 

public OnFilterScriptExit()
{
	WASD_Exit();

	#if defined WASDINC_OnFilterScriptExit
		return WASDINC_OnFilterScriptExit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit WASDINC_OnFilterScriptExit
#if defined WASDINC_OnFilterScriptExit
	forward WASDINC_OnFilterScriptExit();
#endif

// ------------------------------------------------------------ 

WASD_Init()
{
	if(gWASDInit)
		return;

	gWASDInit = true;

	// ---

	for(new i = 0; i < MAX_PLAYERS; ++i)
		gPlayerWASDState[i] = 0;

	#if WASD_TIMER_INTERVAL > 0

	gWASDTimerID = SetTimer("WASD_Update", WASD_TIMER_INTERVAL, 1);

	#endif
}

WASD_Exit()
{
	if(!gWASDInit)
		return;

	gWASDInit = false;

	// ---

	#if WASD_TIMER_INTERVAL > 0

	KillTimer(gWASDTimerID);

	#endif
}

// ------------------------------------------------------------ 

WASD_UpdatePlayer(playerid)
{
	new keys, ud, lr;

	GetPlayerKeys(playerid, keys, ud, lr);

	keys = 0;

	if(ud > 0)
		keys |= WASD_STATE_DOWN;
	else if(ud < 0)
		keys |= WASD_STATE_UP;

	if(lr > 0)
		keys |= WASD_STATE_RIGHT;
	else if(lr < 0)
		keys |= WASD_STATE_LEFT;

	if(keys != gPlayerWASDState[playerid])
	{
		CallLocalFunction("OnPlayerWASDStateChange", "iii", playerid, keys, gPlayerWASDState[playerid]);

		gPlayerWASDState[playerid] = keys;
	}
}

#if WASD_TIMER_INTERVAL > 0 // Timer

public WASD_Update()
{
	if(!gWASDInit)
		return;

	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		if(IsPlayerConnected(playerid))
			WASD_UpdatePlayer(playerid);
	}
}

#else // OPU

public OnPlayerUpdate(playerid)
{
	if(gWASDInit)
		WASD_UpdatePlayer(playerid);

	#if defined WASDINC_OnPlayerUpdate
		return WASDINC_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate WASDINC_OnPlayerUpdate
#if defined WASDINC_OnPlayerUpdate
	forward WASDINC_OnPlayerUpdate(playerid);
#endif

#endif // OPU - End

// ------------------------------------------------------------ 

stock GetPlayerWASDState(playerid)
{
	return gPlayerWASDState[playerid];
}

// ------------------------------------------------------------ 
