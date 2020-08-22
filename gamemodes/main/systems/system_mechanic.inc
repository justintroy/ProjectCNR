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
    bool:Ramp2IsBeingUsed
    //bool:ToolsIsBeingUsed
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

enum {
    TYPE_INVALID_SELECTION = -1,
    TYPE_REPAIR = 0,
    TYPE_NITROUS
}
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
    SetPlayerSelectedRamp(playerid, 0);
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
        Fix Vehicle\n \
        Nitros \
    ";
    ShowPlayerDialog(playerid, DIALOGID_MECHMENU, DIALOG_STYLE_LIST, "Mechanic Services", text, "Select", "Cancel");
}

ShowPlayerNirtoMenu(playerid)
{
    static const text[] = "\
        Nitro x2\n \
        Nitro x5\n \
        Nitro x10 \
    ";
    ShowPlayerDialog(playerid, DIALOGID_NITROMENU, DIALOG_STYLE_LIST, "Nitro", text, "Select", "Back");
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
        }
        else if(GetPlayerSelectedRamp(playerid) == 2) {
            if(GetServiceType(playerid) == TYPE_REPAIR && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
            {
                Ramp2CP = CreateDynamicRaceCP(2, -1657.5564, 444.3009, 7.1797, -1657.5564, 444.3009, 7.1797, 3.0, -1, -1, playerid, .streamdistance = 300.0);
            }
        }
        if(GetServiceType(playerid) == TYPE_NITROUS && GetPlayerLastVehicle(GetPlayerClientID(playerid)) == GetPlayerVehicleID(playerid))
        {
            ToolCP = CreateDynamicRaceCP(2, -1678.919555, 439.157318, 6.859688, -1678.919555, 439.157318, 6.859688, 3.0, -1, -1, playerid, .streamdistance = 300.0);
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
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, checkpointid)
{
    if(checkpointid == Ramp1CP)
    {
        if(GetServiceType(playerid) == TYPE_REPAIR) {
            Textlabel[playerid] = CreateDynamic3DTextLabel("Type /vehfix to fix the vehicle", -1, -1662.113037, 454.551239, 6.187244, 50.0, .playerid = playerid);
            TogglePlayerAllowedToTakeAction(playerid, true);
            RemovePlayerFromVehicle(playerid);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1658.5066, 456.4714, 8.8089);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.1429);
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
            RemovePlayerFromVehicle(playerid);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1663.8922, 451.4243, 8.8086);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.7540);
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
            RemovePlayerFromVehicle(playerid);
            SetVehiclePos(GetPlayerLastVehicle(playerid), -1678.7200, 432.2533, 6.9068);
            SetVehicleZAngle(GetPlayerLastVehicle(playerid), 224.4441);
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

CMD:nrg(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    GetXYInFrontOfPlayer(playerid, x, y, 5.0);
    CreateVehicle(522, x, y, z, 90, 0, 0, -1);
    return 1;
}

CMD:toggleramp(playerid, params[])
{
    if(Ramp1IsBeingUsed)
    {
        Ramp1IsBeingUsed = false;
        SendServerMessage(playerid, "Ramp 1 has been toggled off");
    }
    else if(!Ramp1IsBeingUsed)
    {
        Ramp1IsBeingUsed = true;
        SendServerMessage(playerid, "Ramp 1 has been toggled on");
    }
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

CMD:getnitro(playerid, params[])
{
    if(!IsPlayerMechanic(playerid)) {
        return SendErrorMessage(playerid, "You're not a mechanic!");
    }
    if(GetServiceType(playerid) != TYPE_NITROUS) {
        return SendErrorMessage(playerid, "You can't place a Nitro on the vehicle you're not serving anyone!");
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
                ShowPlayerNirtoMenu(playerid);
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
    }
}