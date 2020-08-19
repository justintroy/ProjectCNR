#define YSI_NO_HEAP_MALLOC
#define YSI_NO_OPTIMISATION_MESSAGE

#include <a_samp>
#include <a_mysql>
#include <streamer>
#include <sscanf2>
#include <samp_bcrypt>
//#include <android-check>

#define SETUP_TABLE			(true) //set to true if tables not set yet

#include <YSI_Coding\y_inline>
#include <YSI_Data\y_iterate>
#include <YSI_Visual\y_commands>
#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_stringhash>
#include <formatex>
//#include "main\anticheat"

#include <defines>
#include <variables>
#include <cfunctions>
#include <functions>
#include <timers>
#include <cmds>
#include <adminsys>
#include <account>
#include <textdraws>
#include <OnPlayerClickTextDraw>
#include <dialogs>
#include <map>

#include <inventory>

#include <biz>

#if SETUP_TABLE
	#include <setuptable>
#endif

main()
{	
	printf("\n-----------------------------------");
	printf("---GROUNDBREAKING COPS N ROBBERS----");
	printf("-----------------------------------\n");
	return 1;
}

public OnGameModeInit()
{
	AddPlayerClass(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); //fix
	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	Database = mysql_connect(MYSQL_HOSTNAME, MYSQL_USERNAME, "", MYSQL_DATABASE);
	if(Database == MYSQL_INVALID_HANDLE || mysql_errno(Database) != 0)
	{
		print("SERVER: MySQL Connection failed, shutting the server down!");
		SendRconCommand("exit");
		return 1;
	}
	print("SERVER: MySQL Connection was successful.");
	CallLocalFunction("OnMySQLConnected", "");

	LoadStaticVehiclesFromFile("vehicles/sf_airport.txt");
	LoadStaticVehiclesFromFile("vehicles/sf_gen.txt");
	LoadStaticVehiclesFromFile("vehicles/sf_law.txt");

	SetGameModeText("Blank Script");

	buildTD();
	LoadBiz();
	return 1;
}


public OnGameModeExit()
{
	for (new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if (IsPlayerConnected(i))
		{
			OnPlayerDisconnect(i, 1);
		}
	}

	mysql_close(Database);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(Player[playerid][IsLoggedIn] == false)
	{
        SendClientMessage(playerid, COLOR_YELLOW, "Welcome to Manila: Cops N Robbers RPG!");
	}
	else
    {
        return false;
	}
	return true;
}

public OnPlayerRequestSpawn(playerid)
{
	if(Player[playerid][IsLoggedIn] == false)
		return false;

	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(Player[playerid][IsLoggedIn])
	{
		defer StopPlayerSound(playerid);
		SetPlayerSkin(playerid, Player[playerid][Skin]);
		SetPlayerPos(playerid, -1984.7754, 660.3203, 46.5683);
	    SetPlayerFacingAngle(playerid, 180.0);
	    GivePlayerWeapon(playerid, 24, 999);
	    LoadObject(playerid);
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(gettime() - Player[playerid][Tick][1] > 5)
		Player[playerid][Tick][1] = gettime();
	else
	{
		SendErrorMessage(playerid, "Slow down at chatting.");
		return 0;
	}
	if(!Player[playerid][IsLoggedIn]) return 0;
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success)
{
    if(success != COMMAND_OK)
    {
        SendErrorMessage(playerid, "Command doesn't exist ! Type /help to view more info or /cmds to view the list of commands."); 
        return COMMAND_OK;
    }

	if(gettime() - Player[playerid][Tick][0] > 1)
	{
		Player[playerid][Tick][0] = gettime();
	}
	else
	{
		SendErrorMessage(playerid, "Please wait a moment before executing another command.");
		return COMMAND_DENIED;
	}

    if(!Player[playerid][IsLoggedIn]) return COMMAND_DENIED;

    Command_SetDeniedReturn(true);
    return COMMAND_OK;
}

/*forward OnCheatDetected(playerid, ip_address[], type, code);
public OnCheatDetected(playerid, ip_address[], type, code)
{
    if(type) BlockIpAddress(ip_address, 0);
    else
    {
        switch(code)
        {
            case 5, 6, 11, 22: return 1;
            case 14:
            {
                new a = GetPlayerMoney(playerid);
                ResetPlayerMoney(playerid);
                GivePlayerMoney(playerid, a);
                return 1;
            }
            case 32:
            {
                new Float:x, Float:y, Float:z;
                AntiCheatGetPos(playerid, x, y, z);
                SetPlayerPos(playerid, x, y, z);
                return 1;
            }
            case 40: SendClientMessage(playerid, -1, MAX_CONNECTS_MSG);
            case 41: SendClientMessage(playerid, -1, UNKNOWN_CLIENT_MSG);
            case 50: SendClientMessageToAll(-1, "May nagchecheat");
            default:
            {
                new strtmp[sizeof KICK_MSG];
                format(strtmp, sizeof strtmp, KICK_MSG, code);
                SendClientMessage(playerid, -1, strtmp);
            }
        }
        AntiCheatKickWithDesync(playerid, code);
    }
    return 1;
}*/