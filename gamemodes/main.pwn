

#include <a_samp>
#include <a_mysql>
#include <streamer>
#include <sscanf2>
#include <bcrypt>

#include <YSI\y_commands>
#include <YSI\y_timers>
#include <YSI\y_hooks>
#include <YSI\y_stringhash>
#include <3dspeed>



#include "main\defines"
#include "main\variables"
#include "main\functions"
#include "main\timers"
#include "main\dialogs"
#include "main\cmds"
#include "main\account\account"
#include "main\textdraws"
#include "main\tutorial"
#include "main\classSelection"

#include "main\maps\objects"




main()
{
	printf("\n-----------------------------------");
	printf("---GROUNDBREAKING COPS N ROBBERS----");
	printf("-----------------------------------\n");

}

public OnGameModeInit()
{
	Database = mysql_connect(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);
	if(Database == MYSQL_INVALID_HANDLE || mysql_errno(Database) != 0)
	{
		print("SERVER: MySQL Connection failed, shutting the server down!");
		SendRconCommand("exit");
		return 1;
	}
	print("SERVER: MySQL Connection was successful.");

	LoadStaticVehiclesFromFile("vehicles/ls_airport.txt");
	LoadStaticVehiclesFromFile("vehicles/ls_gen_inner.txt");
	LoadStaticVehiclesFromFile("vehicles/ls_gen_outer.txt");
	loadMaps();

	SetGameModeText("Blank Script");

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

public OnPlayerRequestClass(playerid, classid)
{
	
	if(Player[playerid][IsLoggedIn] == false)
	{
		
        ClearChatbox(playerid, 10);
        SendClientMessage(playerid, COLOR_YELLOW, "Welcome to Manila: Cops N Robbers RPG!");
	}
	else
    {
        return false;
	}
	return true;
}

public OnPlayerConnect(playerid)
{
	classSelectionTD(playerid);
	resetSkinSelect(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{

	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(Player[playerid][IsLoggedIn])
	{
		defer StopPlayerSound(playerid);
		SetPlayerSkin(playerid, Player[playerid][user_skin]);
		SetPlayerPos(playerid, 2231.7708, -1262.3362, 23.9275);
	    SetPlayerFacingAngle(playerid, 180.0);
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

public OnPlayerRequestSpawn(playerid)
{
	if(Player[playerid][IsLoggedIn] == false)
		return false;

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
