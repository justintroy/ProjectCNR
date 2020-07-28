#include <YSI\y_hooks>

#include "saveplayerdata"
#include "setplayerdata"

hook public OnPlayerConnect(playerid)
{
	g_MysqlRaceCheck[playerid]++;

	static const empty_player[E_PLAYERS];
	Player[playerid] = empty_player;
	

	playerTD(playerid);

	GetPlayerName(playerid, Player[playerid][user_name], MAX_PLAYER_NAME);

	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][0]);
 	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][1]);
 	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][2]);
 	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][3]);
 	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][4]);
 	PlayerTextDrawShow(playerid, Connecting_TD_Message[playerid][5]);

 	defer ConnectingMessages(playerid);
	
	return 1;
}

hook public OnPlayerDisconnect(playerid, reason)
{
	g_MysqlRaceCheck[playerid]++;

	UpdatePlayerData(playerid, reason);

	if (cache_is_valid(Player[playerid][Cache_ID]))
	{
		cache_delete(Player[playerid][Cache_ID]);
		Player[playerid][Cache_ID] = MYSQL_INVALID_CACHE;
	}

	if (Player[playerid][LoginTimer])
	{
		KillTimer(Player[playerid][LoginTimer]);
		Player[playerid][LoginTimer] = 0;
	}

	Player[playerid][IsLoggedIn] = false;
	
	return 1;
}


timer ConnectingMessages[5000](playerid)
{
	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][0]);
 	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][1]);
 	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][2]);
 	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][3]);
 	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][4]);
 	PlayerTextDrawHide(playerid, Connecting_TD_Message[playerid][5]);


 	InterpolateCameraPos(playerid, 1701.193115, -711.747436, 59.379413, 1656.080566, -1017.064941, 92.189880, 80000);
	InterpolateCameraLookAt(playerid, 1700.526611, -716.660766, 60.023361, 1655.303100, -1021.985656, 92.616355, 80000);
	SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPos(playerid, 1652.2787,-992.9540,50.2806);

	new query[103];
	mysql_format(Database, query, sizeof query, "SELECT * FROM `players` WHERE `Username` = '%e' LIMIT 1", Player[playerid][user_name]);
	mysql_tquery(Database, query, "OnPlayerDataLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
	return 1;
}


forward OnPlayerDataLoaded(playerid, race_check);
public OnPlayerDataLoaded(playerid, race_check)
{
	if (race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);

	new string[125];
	if(cache_num_rows() > 0)
	{
		Player[playerid][Cache_ID] = cache_save();

		format(string, sizeof string, "{F9DC5C}This account {009FB7}(%s) {F9DC5C}is registered. Please login by entering your password in the field below:", Player[playerid][user_name]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR {F9DC5C}- Login", string, "Login", "Abort");
		SendClientMessage(playerid, -1, "{3185FC}[MNL:CNR] {F9DC5C}You have 30 seconds to login.");
		Player[playerid][LoginTimer] = SetTimerEx("OnLoginTimeout", SECONDS_TO_LOGIN * 1000, false, "d", playerid);
	}
	else
	{
		format(string, sizeof string, "{F9DC5C} Welcome {009FB7}%s{F9DC5C}, you can register by entering your password in the field below:", Player[playerid][user_name]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR{F9DC5C} - Registration", string, "Register", "Abort");
	}
	return 1;
}


forward OnLoginTimeout(playerid);
public OnLoginTimeout(playerid)
{
	Player[playerid][LoginTimer] = 0;

	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "{3185FC}MNL:CNR{F9DC5C} - Login", "{F9DC5C}You have been kicked for taking too long to login successfully to your account.", "Okay", "");
	Kick(playerid);
	return 1;
}

forward OnPlayerRegister(playerid);
public OnPlayerRegister(playerid)
{
	Player[playerid][user_id] = cache_insert_id();

	ShowPlayerDialog(playerid, DIALOG_PRETUTORIAL, DIALOG_STYLE_MSGBOX, "{3185FC}MNL:CNR{F9DC5C} - Registration", "{F9DC5C}Account successfully registered, you will proceed to the tutorial.", "Okay", "");

	//Player[playerid][IsLoggedIn] = true;

	/*Player[playerid][X_Pos] = DEFAULT_POS_X;
	Player[playerid][Y_Pos] = DEFAULT_POS_Y;
	Player[playerid][Z_Pos] = DEFAULT_POS_Z;
	Player[playerid][A_Pos] = DEFAULT_POS_A;

	SetSpawnInfo(playerid, NO_TEAM, 0, Player[playerid][X_Pos], Player[playerid][Y_Pos], Player[playerid][Z_Pos], Player[playerid][A_Pos], 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);*/
	return 1;
}

forward _KickPlayerDelayed(playerid);
public _KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPasswordHashed(playerid);
public OnPasswordHashed(playerid)
{
	new hash[BCRYPT_HASH_LENGTH], query[300];
	bcrypt_get_hash(hash);
	mysql_format(Database, query, sizeof(query), "INSERT INTO `players` (`Username`, `Password`, `IPAddress`, `RegistrationDate`, `Tutorial`) VALUES ('%e', '%e', '%e', NOW(), 0)", Player[playerid][user_name], hash, ReturnIP(playerid));
	mysql_tquery(Database, query, "OnPlayerRegister", "d", playerid);
	return 1;
}
forward OnPasswordChecked(playerid);
public OnPasswordChecked(playerid)
{
	new bool:match = bcrypt_is_equal();
	if(match)
	{
		TogglePlayerSpectating(playerid, false);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "{3185FC}MNL:CNR{F9DC5C} - Login", "{F9DC5C}You have been successfully logged in.", "Okay", "");

		// sets the specified cache as the active cache so we can retrieve the rest player data
		cache_set_active(Player[playerid][Cache_ID]);

		AssignPlayerData(playerid);

		// remove the active cache from memory and unsets the active cache as well
		cache_delete(Player[playerid][Cache_ID]);
		Player[playerid][Cache_ID] = MYSQL_INVALID_CACHE;

		KillTimer(Player[playerid][LoginTimer]);
		Player[playerid][LoginTimer] = 0;
		Player[playerid][IsLoggedIn] = true;

		// spawn the player to their last saved position after login
		//SetSpawnInfo(playerid, NO_TEAM, 0, Player[playerid][X_Pos], Player[playerid][Y_Pos], Player[playerid][Z_Pos], Player[playerid][A_Pos], 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
		StopAudioStreamForPlayer(playerid);
	}
	else
	{
		Player[playerid][LoginAttempts]++;

		if (Player[playerid][LoginAttempts] >= 3)
		{
			ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "{3185FC}MNL:CNR{F9DC5C} - Login", "{F9DC5C}You have mistyped your password too often (3 times). ", "Okay", "");
			Kick(playerid);
		}
		else ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR{F9DC5C} - Login", "{F9DC5C}Wrong password!\nPlease enter your password in the field below:", "Login", "Abort");

	}
	return 1;
}

ReturnIP(playerid)
{
	new PlayerIP[17];
	GetPlayerIp(playerid, PlayerIP, sizeof(PlayerIP));
	return PlayerIP;
}

////////////////GET THE PLAYER DATA

