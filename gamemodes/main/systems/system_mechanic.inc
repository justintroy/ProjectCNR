/*
    Created By XomoX#8227
*/

#include <YSI_Coding\y_hooks>
#include <mechfunctions>

static 
    Text3D:Textlabel[MAX_PLAYERS],
    Timer:AcceptTimer[MAX_PLAYERS],
    Ramp1CP,
    Ramp2CP,
    ToolCP,
    PlayerSelectedRamp[MAX_PLAYERS],
    bool:Ramp1IsBeingUsed,
    bool:Ramp2IsBeingUsed,
    bool:ToolsIsBeingUsed
;

static
    PlayerLastVehicle[MAX_PLAYERS],
    ClientId[MAX_PLAYERS],
    ServiceType[MAX_PLAYERS],
    AssistedBy[MAX_PLAYERS],
    bool:PlayerHasBeenOffered[MAX_PLAYERS],
    bool:PlayerCantEnterVehicle[MAX_PLAYERS],
    bool:IsPlayerFinishedAssisting[MAX_PLAYERS],
    bool:IsPlayerAllowedToTakeAction[MAX_PLAYERS],
    bool:HasTheComponent[MAX_PLAYERS],
    bool:PlayerIsMechanic[MAX_PLAYERS]
;

static
    PlayerSelectedTire[MAX_PLAYERS]
;

enum {
    TIRE_NONE = 0,
    TIRE_SHADOW = 1,
    TIRE_MEGA,
    TIRE_RIMSHINE,
    TIRE_WIRES,
    TIRE_CLASSIC,
    TIRE_TWIST,
    TIRE_CUTTER,
    TIRE_SWITCH,
    TIRE_GROVE,
    TIRE_IMPORT,
    TIRE_DOLLAR,
    TIRE_TRANS,
    TIRE_ATOMIC
} 

enum {
    TYPE_INVALID_SELECTION = -1,
    TYPE_REPAIR = 0,
    TYPE_NITROUS,
    TYPE_HYDRAULICS,
    TYPE_TIRE
}
SetPlayerSelectedTire(playerid, tireid)
{
    PlayerSelectedTire[playerid] = tireid;
}

GetPlayerSelectedTire(playerid)
{
    return PlayerSelectedTire[playerid];
}
//-----------------------Check if player has been offered an service-----------------
SetPlayerOfferedService(playerid, bool:bool)
{
    PlayerHasBeenOffered[playerid] = bool;
}

GetPlayerOfferedService(playerid)
{
    return PlayerHasBeenOffered[playerid];
}
//---------------------SelectedRamp-----------------
SetPlayerSelectedRamp(playerid, ramp)
{
    PlayerSelectedRamp[playerid] = ramp;
}

GetPlayerSelectedRamp(playerid)
{
    return PlayerSelectedRamp[playerid];
}
//---------------------Toggle to true to prevent player from entering a vehicle------
SetPlayerCantEnterVehicle(playerid, bool:bool)
{
    PlayerCantEnterVehicle[playerid] = bool;
}

IsPlayerCantEnterVehicle(playerid)
{
    return PlayerCantEnterVehicle[playerid];
}
//-----------------------Toggle to true after the player got the Component-----------
SetPlayerHasTheComponent(playerid, bool:bool)
{
    HasTheComponent[playerid] = bool;
}

IsPlayerHasTheComponent(playerid)
{
    return HasTheComponent[playerid];
}
//-----------------------------Variale if player has bought something from the Mech----
SetPlayerAssisted(playerid, bool:bool)
{
    IsPlayerFinishedAssisting[playerid] = bool;
}

IsPlayerFinishedAssisted(playerid)
{
    return IsPlayerFinishedAssisting[playerid];
}
//-------------------------To check if the car is parked to his place------------
TogglePlayerAllowedToTakeAction(playerid, bool:bool)
{
    IsPlayerAllowedToTakeAction[playerid] = bool;
}

bool:PlayerAllowedTotakeAction(playerid)
{
    if(IsPlayerAllowedToTakeAction[playerid])
    {
        return true;
    }
    return false;
}
//------------------------To get mechanic's playerid for Costumer------------------
SetPlayerAssistedby(playerid, id)
{
    AssistedBy[playerid] = id;
}

GetPlayerAssistant(playerid)
{
    return AssistedBy[playerid];
}
//-----------------------Name says it itself to get the Service Type--------------
SetServiceType(playerid, type)
{
    ServiceType[playerid] = type;
}

GetServiceType(playerid)
{
    return ServiceType[playerid];
}
//--------------------To get Costumer's playerid For Mech---------------------------
SetPlayerClientID(playerid, id)
{
    ClientId[playerid] = id;
}

GetPlayerClientID(playerid)
{
    return ClientId[playerid];
}
//-------------------When a player enters a vehicle gets the vehicle id---------------
SetPlayerLastVehicle(playerid, vehicleid)
{
    PlayerLastVehicle[playerid] = vehicleid;
}

GetPlayerLastVehicle(playerid)
{
    return PlayerLastVehicle[playerid];
}
//----------------------To set player mechanic-----------------------
SetPlayerMechanic(playerid, bool:mech)
{
    PlayerIsMechanic[playerid] = mech;
}

bool:IsPlayerMechanic(playerid)
{
    if(PlayerIsMechanic[playerid])
    {
        return true;
    }
    return false;
}
//------------------------------NITRO---------------------------------------
static
    NitroLevel[MAX_PLAYERS]
;

SetNitroRequest(playerid, type)
{
    NitroLevel[playerid] = type;
}

GetNitroRequest(playerid)
{
    return NitroLevel[playerid];
}

ResetMechanicVars(playerid, targetid)
{
    SetPlayerClientID(playerid, -1);
    SetPlayerClientID(targetid, -1);
    SetServiceType(playerid, -1);
    SetServiceType(targetid, -1);
    SetPlayerAssistedby(playerid, -1);
    SetPlayerAssistedby(targetid, -1);
    SetPlayerSelectedTire(playerid, 0);
    SetPlayerSelectedTire(targetid, 0);
    TogglePlayerAllowedToTakeAction(playerid, false);
    TogglePlayerAllowedToTakeAction(targetid, false);
    SetPlayerAssisted(playerid, false);
    SetPlayerAssisted(playerid, false);
    SetPlayerHasTheComponent(playerid, false);
    SetPlayerHasTheComponent(targetid, false);
    SetNitroRequest(playerid, 0);
    SetNitroRequest(targetid, 0);
    if(GetPlayerSelectedRamp(playerid) == 1 || GetPlayerSelectedRamp(targetid) == 1) {
        Ramp1IsBeingUsed = false;
    }
    else if(GetPlayerSelectedRamp(playerid) == 2 || GetPlayerSelectedRamp(targetid) == 2) {
        Ramp2IsBeingUsed = false;
    }
    else if(GetPlayerSelectedRamp(playerid) == 3 || GetPlayerSelectedRamp(targetid) == 3) {
        ToolsIsBeingUsed = false;
    }
    SetPlayerSelectedRamp(playerid, 0);
    SetPlayerSelectedRamp(targetid, 0);
    SetPlayerCantEnterVehicle(playerid, false);
    SetPlayerCantEnterVehicle(targetid, false);
}

//------------------------------MENUS---------------------------------------
ShowPlayerRampSelection(playerid)
{
    static const text1[] = "\
    Ramp 1 (Status: Not in Use)\n \
    Ramp 2 (Status: Not in Use)\n \
    ";
    static const text2[] = "\
    Ramp 1 (Status: In Use)\n \
    Ramp 2 (Status: Not in Use)\n \
    ";
    static const text3[] = "\
    Ramp 1 (Status: Not in Use)\n \
    Ramp 2 (Status: In Use)\n \
    ";
    static const text4[] = "\
    Ramp 1 (Status: In Use)\n \
    Ramp 2 (Status: In Use)\n \
    ";
    if(!Ramp1IsBeingUsed && !Ramp2IsBeingUsed)
    {
        ShowPlayerDialog(playerid, DIALOGID_RAMPSELMENU, DIALOG_STYLE_LIST, "Ramp Selection", text1, "Select", "Cancel");
    }
    else if(Ramp1IsBeingUsed && !Ramp2IsBeingUsed)
    {
        ShowPlayerDialog(playerid, DIALOGID_RAMPSELMENU, DIALOG_STYLE_LIST, "Ramp Selection", text2, "Select", "Cancel");
    }
    else if(!Ramp1IsBeingUsed && Ramp2IsBeingUsed)
    {
        ShowPlayerDialog(playerid, DIALOGID_RAMPSELMENU, DIALOG_STYLE_LIST, "Ramp Selection", text3, "Select", "Cancel");
    }
    else if(Ramp1IsBeingUsed && Ramp2IsBeingUsed)
    {
        ShowPlayerDialog(playerid, DIALOGID_RAMPSELMENU, DIALOG_STYLE_LIST, "Ramp Selection", text4, "Select", "Cancel");
    }
}

ShowPlayerMechMenu(playerid)
{
    static const text[] = "\
        Fix Vehicle\n\
        Hydraulics\n\
        Nitros\n\
        Tires\
    ";
    ShowPlayerDialog(playerid, DIALOGID_MECHMENU, DIALOG_STYLE_LIST, "Mechanic Services", text, "Select", "Cancel");
}

ShowPlayerNirtoMenu(playerid)
{
    static const text[] = "\
        Nitro x2\n\
        Nitro x5\n\
        Nitro x10\
    ";
    ShowPlayerDialog(playerid, DIALOGID_NITROMENU, DIALOG_STYLE_LIST, "Nitro", text, "Select", "Back");
}

ShowPlayerTireMenu(playerid)
{
    static const text[] = "\
        Shadow\n\
        Mega\n\
        Rimshine\n\
        Wires\n\
        Classic\n\
        Twist\n\
        Cutter\n\
        Switch\n\
        Grove\n\
        Import\n\
        Dollar\n\
        Trance\n\
        Atomic\
    ";
    ShowPlayerDialog(playerid, DIALOGID_TIREMENU, DIALOG_STYLE_LIST, "Tires", text, "Select", "Back");
}
//--------------------------------------------------------------------------------------------

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        if(GetPlayerClientID(playerid) != -1 && IsPlayerCantEnterVehicle(playerid)) {
            RemovePlayerFromVehicle(playerid);
            SendErrorMessage(playerid, "You can't enter another vehicle while assisting");
            return 1;
        }
        new vehid = GetPlayerVehicleID(playerid);
        SetPlayerLastVehicle(playerid, vehid);
    }
    if(newstate == PLAYER_STATE_DRIVER && GetPlayerClientID(playerid) != -1)
    {
        if(GetPlayerSelectedRamp(playerid) == 1) {
            if(GetServiceType(playerid) == TYPE_REPAIR && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                Ramp1CP = CreateDynamicRaceCP(2, -1651.9893, 449.2363, 7.1797, -1651.9893, 449.2363, 7.1797, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
            else if(GetServiceType(playerid) == TYPE_HYDRAULICS && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid)) 
            {
                Ramp1CP = CreateDynamicRaceCP(2, -1651.9893, 449.2363, 7.1797, -1651.9893, 449.2363, 7.1797, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
        }
        else if(GetPlayerSelectedRamp(playerid) == 2) {
            if(GetServiceType(playerid) == TYPE_REPAIR && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                Ramp2CP = CreateDynamicRaceCP(2, -1657.5564, 444.3009, 7.1797, -1657.5564, 444.3009, 7.1797, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
            else if(GetServiceType(playerid) == TYPE_HYDRAULICS && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                Ramp2CP = CreateDynamicRaceCP(2, -1657.5564, 444.3009, 7.1797, -1657.5564, 444.3009, 7.1797, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
        }
        else if(GetPlayerSelectedRamp(playerid) == 3) {
            if(GetServiceType(playerid) == TYPE_NITROUS && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                ToolCP = CreateDynamicRaceCP(2, -1678.919555, 439.157318, 6.859688, -1678.919555, 439.157318, 6.859688, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
            else if(GetServiceType(playerid) == TYPE_TIRE && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                ToolCP = CreateDynamicRaceCP(2, -1678.919555, 439.157318, 6.859688, -1678.919555, 439.157318, 6.859688, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    SetPlayerLastVehicle(playerid, -1);
    SetPlayerMechanic(playerid, false);
    ApplyAnimation(playerid, "ped", "null", 4.0, 0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "BOMBER", "null", 4.0, 0, 0, 0, 0, 0, 0);
    ResetMechanicVars(playerid, playerid);
    return 1;
}

hook OnGameModeInit()
{
    CreateVehicle(411, -1695.0503, 380.6482, 6.9261, 72.5674, 0, 0, -1);
    Ramp1IsBeingUsed = false;
    Ramp2IsBeingUsed = false;
    ToolsIsBeingUsed = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(GetPlayerClientID(playerid) != -1)
    {
        ResetMechanicVars(playerid, GetPlayerClientID(playerid));
    }
    if(GetPlayerAssistant(playerid) != -1)
    {
        ResetMechanicVars(playerid, GetPlayerAssistant(playerid));
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, checkpointid)
{
    if(checkpointid == Ramp1CP)
    {
        if(GetServiceType(playerid) == TYPE_REPAIR) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /vehfix to fix the vehicle", -1, -1662.113037, 454.551239, 6.187244, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1658.5066, 456.4714, 8.8089);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.1429);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(Ramp1CP)) {
                DestroyDynamicRaceCP(Ramp1CP);
            }
        }
        else if(GetServiceType(playerid) == TYPE_HYDRAULICS) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /installhydraulics to fix the vehicle", -1, -1662.113037, 454.551239, 6.187244, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1658.5066, 456.4714, 8.8089);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.1429);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(Ramp1CP)) {
                DestroyDynamicRaceCP(Ramp1CP);
            }
        }
    }
    if(checkpointid == Ramp2CP)
    {
        if(GetServiceType(playerid) == TYPE_REPAIR) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /vehfix to fix the vehicle", -1, -1667.213378, 450.031311, 6.187244, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1663.8922, 451.4243, 8.8086);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.7540);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(Ramp2CP)) {
                DestroyDynamicRaceCP(Ramp2CP);
            }
        }
        else if(GetServiceType(playerid) == TYPE_HYDRAULICS) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /installhydraulics to fix the vehicle", -1, -1667.213378, 450.031311, 6.187244, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1663.8922, 451.4243, 8.8086);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.7540);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(Ramp2CP)) {
                DestroyDynamicRaceCP(Ramp2CP);
            }
        }
    }
    if(checkpointid == ToolCP)
    {
        if(GetServiceType(playerid) == TYPE_NITROUS) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /getnitro to get a nitro", -1, -1678.919555, 439.157318, 6.859688, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1678.7200, 432.2533, 6.9068);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.4441);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(ToolCP)) {
                DestroyDynamicRaceCP(ToolCP);
            }
        }
        else if(GetServiceType(playerid) == TYPE_TIRE) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /gettire to get a nitro", -1, -1678.919555, 439.157318, 6.859688, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1678.7200, 432.2533, 6.9068);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.4441);
            RemovePlayerFromVehicle(playerid);
            SetPlayerCantEnterVehicle(playerid, true);
            if(IsValidDynamicRaceCP(ToolCP)) {
                DestroyDynamicRaceCP(ToolCP);
            }
        }
    }
    return 1;
}
//-----------------------------------------------------------------------------------------------
CMD:goto(playerid, params[])
{
    SetPlayerPos(playerid, -1709.9238, 404.4724, 7.1797);
    return 1;
}

CMD:showmenu(playerid, params[])
{
    SetPlayerAssistedby(playerid, playerid);
    SetPlayerClientID(playerid, playerid);
    ShowPlayerMechMenu(playerid);
    return 1;
}

CMD:nrg(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    GetXYInFrontOfPlayer(playerid, x, y, 5.0);
    CreateVehicle(522, x, y, z, 90, 0, 0, -1);
    return 1;
}

CMD:mechduty(playerid, params[])
{
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1709.9238, 404.4724, 7.1797)) {
        return SendErrorMessage(playerid, "You're not near the mech bot");
    }
    if(!IsPlayerMechanic(playerid)) {
        SetPlayerMechanic(playerid, true);
        SendServerMessage(playerid, "You're now on duty wait for a player request.");
        SendServerMessageToAllF("%p (%d) is now Mechanic On duty", playerid, playerid);
    }
    else if(IsPlayerMechanic(playerid)) {
        SetPlayerMechanic(playerid, false);
        SendServerMessage(playerid, "You're now off duty.");
        SendServerMessageToAllF("%p (%d) is now Mechanic Off duty", playerid, playerid);
    }
    return 1;
}

CMD:vehfix(playerid, params[])
{
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a Mechanic!");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1662.113037, 454.551239, 6.187244) && GetPlayerSelectedRamp(playerid) == 1) {
        return SendErrorMessage(playerid, "You're not close the the Tuning Computer");
    }
    else if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1667.213378, 450.031311, 6.187244) && GetPlayerSelectedRamp(playerid) == 2) {
        return SendErrorMessage(playerid, "You're not close the the Tuning Computer");
    }
    if(GetServiceType(playerid) != TYPE_REPAIR) {
        return SendErrorMessage(playerid, "You can't repair a vehicle you're not serving anyone!");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "You need to get the vehicle to the ramp");
    }
    defer RepairTimer(playerid, GetPlayerClientID(playerid));
    ApplyAnimation(playerid, "ped", "ATM", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:installhydraulics(playerid, params[]) {
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a Mechanic!");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1662.113037, 454.551239, 6.187244) && GetPlayerSelectedRamp(playerid) == 1) {
        return SendErrorMessage(playerid, "You're not close the the Tuning Computer");
    }
    else if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1667.213378, 450.031311, 6.187244) && GetPlayerSelectedRamp(playerid) == 2) {
        return SendErrorMessage(playerid, "You're not close the the Tuning Computer");
    }
    if(GetServiceType(playerid) != TYPE_HYDRAULICS) {
        return SendErrorMessage(playerid, "You can't add a hydraulics because its not requested");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "You need to get the vehicle to the ramp"); 
    }
    defer installHydraulicsTime(playerid, GetPlayerClientID(playerid));
    ApplyAnimation(playerid, "ped", "ATM", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:getnitro(playerid, params[])
{
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a mechanic!");
    }
    if(GetServiceType(playerid) != TYPE_NITROUS) {
        return SendErrorMessage(playerid, "You can't get a Nitro on the vehicle you're not serving anyone!");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "Park the car near the tools");
    }
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
    defer GetComp(playerid, 1);
    return 1;
}

CMD:placenitro(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetVehicleRelativePos(GetPlayerLastVehicle(playerid), x, y, z, 0.0, -3.0, 0.0);
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a mechanic!");
    }
    if(GetServiceType(playerid) != TYPE_NITROUS) {
        return SendErrorMessage(playerid, "You can't place a Nitro on the vehicle you're not serving anyone!");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "Park the car near the tools");
    }
    if(!IsPlayerHasTheComponent(playerid)) {
        return SendErrorMessage(playerid, "You don't have the component left");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) {
        return SendErrorMessage(playerid, "You're not on the Rear of the vehicle");
    }
    defer PlaceNiro(playerid, GetNitroRequest(playerid));
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:gettire(playerid, params[])
{
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a mechanic!");
    }
    if(GetServiceType(playerid) != TYPE_TIRE) {
        return SendErrorMessage(playerid, "You can't get a Nitro on the vehicle you're not serving anyone!");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "Park the car near the tools");
    }
    defer GetComp(playerid, 2);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:placetire(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetVehicleRelativePos(GetPlayerLastVehicle(playerid), x, y, z, 1.0, 1.0, 0.0);
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a mechanic!");
    }
    if(GetServiceType(playerid) != TYPE_TIRE) {
        return SendErrorMessage(playerid, "You can't place a Tire on the vehicle you're not serving anyone!");
    }
    if(!PlayerAllowedTotakeAction(playerid)) {
        return SendErrorMessage(playerid, "Park the car near the tools");
    }
    if(!IsPlayerHasTheComponent(playerid)) {
        return SendErrorMessage(playerid, "You don't have the component left");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) {
        return SendErrorMessage(playerid, "You're not on the Rear of the vehicle");
    }
    defer PlaceTire(playerid, GetPlayerSelectedTire(playerid));
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

/*CMD:mech(playerid, params[])
{
    new onlinemechs = 0;
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    foreach(new i : Player)
    {
        if(IsPlayerMechanic(i))
        {
            onlinemechs++;
            SendServerMessageF(i, "%p (%d) request mechanic.", playerid, playerid);
            CreateDynamicRaceCP(1, x, y, z, x, y, z, 3.0, -1, -1, i, .streamdistance = 300.0);
        }
    }
    if(onlinemechs == 0) 
    {
        SendServerMessage(playerid, "No active mechanics today");
    }
    else if(onlinemechs > 0)
    {
        SendServerMessage(playerid, "Called a mechanic");
    }
    return 1;
}
*/

CMD:acceptmech(playerid, params[])
{
    if(!GetPlayerOfferedService(playerid)) {
        return SendErrorMessage(playerid, "You didn't recieved an offer yet!");
    }
    ShowPlayerMechMenu(playerid);
    SetPlayerOfferedService(playerid, false);
    stop AcceptTimer[playerid];
    return 1;
}
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_WALK)
    {
        if(IsPlayerMechanic(playerid))
        {
            new targetid = GetClosestPlayer(playerid, 2.0);
            if(GetPlayerAssistant(targetid) != -1) {
                SendErrorMessage(playerid, "Player is already getting assisted");
                return 1;
            }
            if(GetPlayerLastVehicle(targetid) == -1) {
                SendErrorMessage(playerid, "Player has no Vehicle entered recently");
                return 1;
            }
            if(GetPlayerOfferedService(playerid)) {
                SendErrorMessage(playerid, "Someone offered an Mech Service to the player");
                return 1;
            }
            AcceptTimer[targetid] = defer MechAcceptTimer(targetid);
            SendServerMessageF(playerid, "Offered Mechanic to %p (%d)", targetid, targetid);
            SendServerMessage(targetid, "You have been offered Mechanic Services use /acceptmech");
            SetPlayerAssistedby(targetid, playerid);
            SetPlayerClientID(playerid, targetid);
            SetPlayerOfferedService(targetid, true);
            
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOGID_MECHMENU)
    {
        if(response == 1)
        {
            if(listitem == 0)
            {
                ShowPlayerRampSelection(GetPlayerAssistant(playerid));
                SetServiceType(GetPlayerAssistant(playerid), TYPE_REPAIR);
            }
            if(listitem == 1)
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1087)) {
                    SendErrorMessage(playerid, "You can't add a Hydraulics in this vehicle");
                    ResetMechanicVars(playerid, GetPlayerAssistant(playerid));
                    return 1;
                }
                ShowPlayerRampSelection(GetPlayerAssistant(playerid));
                SetServiceType(GetPlayerAssistant(playerid), TYPE_HYDRAULICS);
            }
            if(listitem == 2)
            {
                if(ToolsIsBeingUsed) {
                    new targetid = GetPlayerAssistant(playerid);
                    SendErrorMessage(targetid, "Player selected nitro but Tools is being used");
                    SendErrorMessage(playerid, "Tools is being used by another player");
                    return 1;
                }
                ToolsIsBeingUsed = true;
                SetPlayerSelectedRamp(GetPlayerAssistant(playerid), 3);
                ShowPlayerNirtoMenu(playerid);
            }
            if(listitem == 3)
            {
                if(ToolsIsBeingUsed) {
                    new targetid = GetPlayerAssistant(playerid);
                    SendErrorMessage(targetid, "Player selected nitro but Tools is being used");
                    SendErrorMessage(playerid, "Tools is being used by another player");
                    return 1;
                }
                ToolsIsBeingUsed = true;
                SetPlayerSelectedRamp(GetPlayerAssistant(playerid), 3);
                ShowPlayerTireMenu(playerid);
            }
        }
        else if(response == 0)
        {
            new targetid = GetPlayerAssistant(playerid);
            SendServerMessage(targetid, "Client has closed the Menu");
            if(IsPlayerFinishedAssisted(playerid)) 
            {
                SetVehiclePos(GetPlayerLastVehicle(targetid), -1695.0503, 380.6482, 6.9261);
                SetVehicleZAngle(GetPlayerLastVehicle(targetid), 72.5674);
                SendServerMessage(playerid, "Finished your car Enjoy!");
            }
            ResetMechanicVars(playerid, targetid);
        }
    }
    if(dialogid == DIALOGID_NITROMENU)
    {
        if(response == 1)
        {
            if(listitem == 0)
            {
                new mechid = GetPlayerAssistant(playerid);
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1009)) {
                    SendErrorMessage(playerid, "You can't add a Nitrous in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetNitroRequest(mechid, 1);
                SetServiceType(mechid, TYPE_NITROUS);
            }
            if(listitem == 1)
            {
                new mechid = GetPlayerAssistant(playerid);
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1009)) {
                    SendErrorMessage(playerid, "You can't add a Nitrous in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetNitroRequest(mechid, 2);
                SetServiceType(mechid, TYPE_NITROUS);
            }
            if(listitem == 2)
            {
                new mechid = GetPlayerAssistant(playerid);
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1009)) {
                    SendErrorMessage(playerid, "You can't add a Nitrous in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetNitroRequest(mechid, 3);
                SetServiceType(mechid, TYPE_NITROUS);
            }
        }
        else if(response == 0)
        {
            ShowPlayerMechMenu(playerid);
        }
    }
    if(dialogid == DIALOGID_RAMPSELMENU)
    {
        if(response == 1)
        {
            if(listitem == 0)
            {
                if(Ramp1IsBeingUsed) {
                    SendErrorMessage(playerid, "Ramp 1 is Being used by another Mechanic");
                    ResetMechanicVars(playerid, GetPlayerClientID(playerid));
                    return 1;
                }
                Ramp1IsBeingUsed = true;
                SetPlayerSelectedRamp(playerid, 1);
                SendServerMessage(playerid, "Enter the Client's vehicle");
            }
            if(listitem == 1) 
            {
                if(Ramp2IsBeingUsed) {
                    SendErrorMessage(playerid, "Ramp 2 is Being used by another Mechanic");
                    ResetMechanicVars(playerid, GetPlayerClientID(playerid));
                    return 1;
                }
                Ramp2IsBeingUsed = true;
                SetPlayerSelectedRamp(playerid, 2);
                SendServerMessage(playerid, "Enter the Client's vehicle");
            }
        }
        else if(response == 0) 
        {
            ResetMechanicVars(playerid, GetPlayerClientID(playerid));
        }
    }
    if(dialogid == DIALOGID_TIREMENU)
    {
        new mechid = GetPlayerAssistant(playerid);
        if(response == 1)
        {
            if(listitem == 0) //shadow
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1073)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 1);
            }
            if(listitem == 1) //mega
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1074)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 2);
            }
            if(listitem == 2) //Rimshine
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1075)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 3);
            }
            if(listitem == 3) //wires
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1076)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 4);
            }
            if(listitem == 4) //classic
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1077)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 5);
            }
            if(listitem == 5) //twist
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1078)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 6);
            }
            if(listitem == 6) //Cutter
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1079)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 7);
            }
            if(listitem == 7) //Switch
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1080)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 8);
            }
            if(listitem == 8) //Grove
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1081)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 9);
            }
            if(listitem == 9) //Import
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1082)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 10);
            }
            if(listitem == 10) //Dollar
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1083)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 11);
            }
            if(listitem == 11) //Trance
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1084)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 12);
            }
            if(listitem == 12) //Import
            {
                if(!IsValidComponentForVehicle(GetPlayerLastVehicle(playerid), 1085)) {
                    SendErrorMessage(playerid, "You can't add this tire in this vehicle");
                    ResetMechanicVars(playerid, mechid);
                    return 1;
                }
                SendServerMessage(mechid, "Enter the Client's car");
                SetServiceType(mechid, TYPE_TIRE);
                SetPlayerSelectedTire(mechid, 13);
            }
        }
        else if(response == 0)
        {
            ShowPlayerMechMenu(playerid);
        }
    }
    return 1;
}

//----------------------------------TIMERS--------------------------
timer MechAcceptTimer[7000](playerid)
{
    new mechid = GetPlayerAssistant(playerid);
    SetPlayerClientID(mechid, -1);
    SetPlayerAssistedby(playerid, -1);
    SetPlayerOfferedService(playerid, false);
}

timer RepairTimer[5000](playerid, targetid)
{
    new vehid = GetPlayerLastVehicle(playerid);
    RepairVehicle(vehid);
    ClearAnimations(playerid, 1);
    GivePlayerMoney(targetid, -500);
    GivePlayerMoney(playerid, 500);
    SetPlayerAssisted(targetid, true);
    if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
        DestroyDynamic3DTextLabel(Textlabel[playerid]);
    }
    SendServerMessage(playerid, "Finished Fixing the Vehicle");
    SendServerMessage(targetid, "Finished Fixing the Vehicle");
    SetPlayerCantEnterVehicle(playerid, false);
    ShowPlayerMechMenu(targetid);
}

timer installHydraulicsTime[5000](playerid, targetid)
{
    new vehid = GetPlayerLastVehicle(playerid);
    AddVehicleComponent(vehid, 1087);
    GivePlayerMoney(targetid, -1500);
    GivePlayerMoney(playerid, 1500);
    SetPlayerAssisted(targetid, true);
    if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
        DestroyDynamic3DTextLabel(Textlabel[playerid]);
    }
    SendServerMessage(playerid, "Finished Adding Hydraulics to the Vehicle");
    SendServerMessage(targetid, "Finished Adding Hydraulics to the Vehicle");
    SetPlayerCantEnterVehicle(playerid, false);
    ShowPlayerMechMenu(targetid);
}

timer PlaceTire[5000](playerid, tire)
{
    new vehid = GetPlayerLastVehicle(playerid);
    new targetid = GetPlayerClientID(playerid);
    ClearAnimations(playerid, 1);
    if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
        DestroyDynamic3DTextLabel(Textlabel[playerid]);
    }
    RemovePlayerAttachedObject(playerid, 6);
    SetPlayerCantEnterVehicle(playerid, false);
    switch(tire)
    {
        case 1:
        {
            AddVehicleComponent(vehid, 1073);
            GivePlayerMoney(targetid, -1100);
            GivePlayerMoney(playerid, 1100);
            SendServerMessage(targetid, "Your car has been installed Shadow Tires");
        }
        case 2:
        {
            AddVehicleComponent(vehid, 1074);
            GivePlayerMoney(targetid, -1030);
            GivePlayerMoney(playerid, 1030);
            SendServerMessage(targetid, "Your car has been installed Mega Tires");
        }
        case 3:
        {
            AddVehicleComponent(vehid, 1075);
            GivePlayerMoney(targetid, -980);
            GivePlayerMoney(playerid, 980);
            SendServerMessage(targetid, "Your car has been installed Rimshine Tires");
        }
        case 4:
        {
            AddVehicleComponent(vehid, 1076);
            GivePlayerMoney(targetid, -1560);
            GivePlayerMoney(playerid, 1560);
            SendServerMessage(targetid, "Your car has been installed Wires Tires");
        }
        case 5:
        {
            AddVehicleComponent(vehid, 1077);
            GivePlayerMoney(targetid, -1620);
            GivePlayerMoney(playerid, 1620);
            SendServerMessage(targetid, "Your car has been installed Classic Tires");
        }
        case 6:
        {
            AddVehicleComponent(vehid, 1078);
            GivePlayerMoney(targetid, -1200);
            GivePlayerMoney(playerid, 1200);
            SendServerMessage(targetid, "Your car has been installed Twist Tires");
        }
        case 7:
        {
            AddVehicleComponent(vehid, 1079);
            GivePlayerMoney(targetid, -1030);
            GivePlayerMoney(playerid, 1030);
            SendServerMessage(targetid, "Your car has been installed Cutter Tires");
        }
        case 8:
        {
            AddVehicleComponent(vehid, 1080);
            GivePlayerMoney(targetid, -900);
            GivePlayerMoney(playerid, 900);
            SendServerMessage(targetid, "Your car has been installed Switch Tires");
        }
        case 9:
        {
            AddVehicleComponent(vehid, 1081);
            GivePlayerMoney(targetid, -1230);
            GivePlayerMoney(playerid, 1230);
            SendServerMessage(targetid, "Your car has been installed Grove Tires");
        }
        case 10:
        {
            AddVehicleComponent(vehid, 1082);
            GivePlayerMoney(targetid, -820);
            GivePlayerMoney(playerid, 820);
            SendServerMessage(targetid, "Your car has been installed Import Tires");
        }
        case 11:
        {
            AddVehicleComponent(vehid, 1083);
            GivePlayerMoney(targetid, -1560);
            GivePlayerMoney(playerid, 1560);
            SendServerMessage(targetid, "Your car has been installed Dollar Tires");
        }
        case 12:
        {
            AddVehicleComponent(vehid, 1084);
            GivePlayerMoney(targetid, -1350);
            GivePlayerMoney(playerid, 1350);
            SendServerMessage(targetid, "Your car has been installed Trance Tires");
        }
        case 13:
        {
            AddVehicleComponent(vehid, 1085);
            GivePlayerMoney(targetid, -770);
            GivePlayerMoney(playerid, 770);
            SendServerMessage(targetid, "Your car has been installed Atomic Tires");
        }
    }
    SetPlayerAssisted(targetid, true);
    ShowPlayerMechMenu(GetPlayerClientID(playerid));
}

timer PlaceNiro[5000](playerid, level)
{
    new vehid = GetPlayerLastVehicle(playerid);
    new targetid = GetPlayerClientID(playerid);
    ClearAnimations(playerid, 1);
    if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
        DestroyDynamic3DTextLabel(Textlabel[playerid]);
    }
    RemovePlayerAttachedObject(playerid, 6);
    SetPlayerCantEnterVehicle(playerid, false);
    switch(level)
    {
        case 1:
        {
            AddVehicleComponent(vehid, 1009);
            GivePlayerMoney(targetid, -200);
            GivePlayerMoney(playerid, 200);
            SendServerMessage(targetid, "Your car has been installed 2x Nitrous");
        }
        case 2:
        {
            AddVehicleComponent(vehid, 1009);
            GivePlayerMoney(targetid, -500);
            GivePlayerMoney(playerid, 500);
            SendServerMessage(targetid, "Your car has been installed 5x Nitrous");
        }
        case 3:
        {
            AddVehicleComponent(vehid, 1010);
            GivePlayerMoney(targetid, -1000);
            GivePlayerMoney(playerid, 1000);
            SendServerMessage(targetid, "Your car has been installed 10x Nitrous");
        }
    }
    SetPlayerAssisted(targetid, true);
    ShowPlayerMechMenu(GetPlayerClientID(playerid));
}

timer GetComp[3000](playerid, type)
{
    new Float:x, Float:y, Float:z;
    ClearAnimations(playerid, 1);
    switch(type)
    {
        case 1: //Nitro
        {
            GetVehicleRelativePos(GetPlayerLastVehicle(playerid), x, y, z, 0.0, -3.0, 0.0);
            SetPlayerAttachedObject(playerid, 6, 19816, 6, 0.1929, 0.0140, -0.1019, 0.0000, -55.5999, 0.0000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);
            ClearAnimations(playerid, 1);
            SetPlayerHasTheComponent(playerid, true);
            if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
                DestroyDynamic3DTextLabel(Textlabel[playerid]);
            }
            Textlabel[playerid] = CreateDynamic3DTextLabel("type /placenitro to place the nitro", -1, x, y, z, 50.0, .playerid = playerid);
        }
        case 2: //Tire
        {
            GetVehicleRelativePos(GetPlayerLastVehicle(playerid), x, y, z, 1.0, 1.0, 0.0);
            SetPlayerAttachedObject(playerid, 6, 1076, 6, 0.2569, 0.0260, 0.0350, -175.3999, -90.1000, 87.6999, 0.6020, 0.5869, 0.6400, 0xFFFFFFFF, 0xFFFFFFFF);
            ClearAnimations(playerid, 1);
            SetPlayerHasTheComponent(playerid, true);
            if(IsValidDynamic3DTextLabel(Textlabel[playerid])) {
                DestroyDynamic3DTextLabel(Textlabel[playerid]);
            }
            Textlabel[playerid] = CreateDynamic3DTextLabel("type /placetire to place the nitro", -1, x, y, z, 50.0, .playerid = playerid);
        }
    }
}