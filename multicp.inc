#if defined _multicp_included
	#endinput
#endif

#define _multicp_included

#if !defined _samp_included
    #error could not find a_samp.inc, please check your server includes.
#endif

#if !defined _INC_y_iterate
    #tryinclude <YSI_Data\y_iterate>
#endif

#if !defined _INC_y_iterate
    #error Cannot find y_iterate library
#endif

#if !defined _INC_y_hooks
    #tryinclude <YSI_Coding\y_hooks>
#endif

#if !defined _INC_y_iterate
    #error Cannot find y_hooks library
#endif

#if !defined _streamer_included
    #tryinclude <streamer>
#endif
#if !defined _streamer_included
    #error could not find streamer.inc, install streamer library at (github.com/samp-incognito/samp-streamer-plugin)
#endif

#define                 MAX_MULTICP                         100
#define                 INVALID_MULTICP                     -1
#define                 MULTICP_DEFAULT_COL                 0xAA00000FF

forward OnPlayerEnterMultiCP(playerid, cpid);
forward OnPlayerLeaveMultiCP(playerid, cpid);


static
    STREAMER_TAG_AREA:g_cpArea[MAX_PLAYERS][MAX_MULTICP],
    bool:g_cpAutoDisable[MAX_PLAYERS][MAX_MULTICP],
    Iterator:MultiCP<MAX_MULTICP>;


stock SetPlayerMultiCP(playerid, Float:x, Float:y, Float:z, bool:autodisable = false) {

    new index = INVALID_ITERATOR_SLOT;
    if((index = Iter_Alloc(MultiCP)) != INVALID_ITERATOR_SLOT) {
        SetPlayerMapIcon(playerid, index, x, y, z, 0, MULTICP_DEFAULT_COL, MAPICON_GLOBAL_CHECKPOINT);
        g_cpArea[playerid][index] = CreateDynamicCylinder(x, y, z - 0.5, z + 0.5, 1.3, _, _, playerid);
        g_cpAutoDisable[playerid][index] = autodisable;

        Streamer_SetIntData(STREAMER_TYPE_AREA, g_cpArea[playerid][index], E_STREAMER_EXTRA_ID, index);
    }
    else {
        print("(error multicp) unable to create more checkpoint.");
    }
    return index;
}

stock DisablePlayerMultiCP(playerid, cpidx) {

    if(!IsPlayerConnected(playerid))
        return 0;

    if(!Iter_Contains(MultiCP, cpidx))
        return 0;

    if(IsValidDynamicArea(g_cpArea[playerid][cpidx]))
        DestroyDynamicArea(g_cpArea[playerid][cpidx]);

    g_cpAutoDisable[playerid][cpidx] = false;

    RemovePlayerMapIcon(playerid, cpidx);
    Iter_Remove(MultiCP, cpidx);
    return 1; 
}

stock bool:IsPlayerInMultiCP(playerid, cpidx) {

    if(!IsPlayerConnected(playerid))
        return false;

    if(!Iter_Contains(MultiCP, cpidx))
        return false;

    return (IsPlayerInDynamicArea(playerid, g_cpArea[playerid][cpidx]));
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid) {

    new cpidx = INVALID_MULTICP;
    cpidx = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(Iter_Contains(MultiCP, cpidx))
    {
        if(g_cpAutoDisable[playerid][cpidx]) {
            DisablePlayerMultiCP(playerid, cpidx); }

        CallLocalFunction(#OnPlayerEnterMultiCP, "dd", playerid, cpidx);
    }
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid) {

    new cpidx = INVALID_MULTICP;
    cpidx = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

    if(Iter_Contains(MultiCP, cpidx))
    {
        CallLocalFunction(#OnPlayerLeaveMultiCP, "dd", playerid, cpidx);
    }
}
