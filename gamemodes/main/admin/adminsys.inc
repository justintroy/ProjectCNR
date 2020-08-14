#include <YSI_Coding\y_hooks>

#include "bansys"

forward OnCheckOperatingSystem(playerid, OSType);
public OnCheckOperatingSystem(playerid, OSType) 
{
    if (OSType == OS_TYPE_PC)  
    {
        print("Kicking player!");
    }
    else 
    {
        print("Safe!");
    }
    return 1;
}

hook OnGameModeInit()
{
	Command_AddAltNamed("admin", "a"); 
	Command_AddAltNamed("adminlogs", "alogs"); 
}

YCMD:setadmin(playerid, params[], help)
{
    if(Player[playerid][pAdmin] >= 4 || IsPlayerAdmin(playerid))
    {
		new targetid, level, string[300];
		if(sscanf(params, "ud", targetid, level)) return SendUsageMessage(playerid, "/setadmin [playername/playerid] [level]");
		if(!IsPlayerConnected(targetid)) return SendErrorMessage(playerid, "That player is not connected.");
		if(level < 0 || level > 4) return SendErrorMessage(playerid, "Admin Level must be between 0 and 4.");
		Player[targetid][pAdmin] = level;
		format(string, sizeof(string), "{16E0BD}You have been set as a Level %d Administrator by %s(%d)", level, GetName(playerid), playerid);
		SendAdminMessage(targetid, string);
		format(string, sizeof(string), "{16E0BD}You have set %s(%d) as a Level %d Administrator.", GetName(targetid), targetid, level);
		SendAdminMessage(playerid, string);
		
	    format(string, sizeof(string), "Used /setadmin to set %s as a Level %d Administrator.", GetName(targetid), level);
	    AdminLogEx(playerid, string);
	}
	//if(Player[playerid][pAdmin] < 4) return SendErrorMessage(playerid, "You are not authorized to use that command.");
	return 1;
}

YCMD:setweather(playerid, params[], help)
{
    if(Player[playerid][pAdmin] < 4) return SendErrorMessage(playerid, "You are not authorized to use that command.");
	new weather;
	if(sscanf(params, "d", weather)) return SendUsageMessage(playerid, "/setweather [weather]");
	if(weather < 0 || weather > 24) return SendErrorMessage(playerid, "Invalid weather" );
	SendClientMessageEx(playerid, COLOR_RED, "You have changed the server weather to %d", weather);
	foreach(new i : Player)
	{
		SetPlayerWeather(i, weather);
	}
	new string[256];
	format(string, sizeof(string), "Used /setweather to %d", weather);
    AdminLogEx(playerid, string);
	return 1;
}

CMD:freeze(playerid, params[])
{
    if(Player[playerid][pAdmin] < 3) return SendErrorMessage(playerid, "You are not authorized to use that command.");
    new targetid;
    if(sscanf(params, "u", targetid)) return SendUsageMessage(playerid, "/freeze [playername/playerid]");
    if(!IsPlayerConnected(targetid)) return SendErrorMessage(playerid, "That player is not connected.");
    TogglePlayerControllable(targetid, 0);
    SendClientMessageEx(playerid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C}You have frozen %s(%d)", GetName(targetid), targetid);
    SendClientMessageEx(targetid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C}You have frozen by %s(%d)", GetName(playerid), playerid);

    new string[256];
    format(string, sizeof(string), "Used /freeze to %s", GetName(targetid));
    AdminLogEx(playerid, string);
	return 1;
}

CMD:unfreeze(playerid, params[])
{
    if(Player[playerid][pAdmin] < 3) return SendErrorMessage(playerid, "You are not authorized to use that command.");
    new targetid;
    if(sscanf(params, "u", targetid)) return SendUsageMessage(playerid, "/unfreeze [playername/playerid]");
    if(!IsPlayerConnected(targetid)) return SendErrorMessage(playerid, "That player is not connected.");
    TogglePlayerControllable(targetid, 1);
    SendClientMessageEx(playerid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C}You have unfrozen %s(%d)", GetName(targetid), targetid);
    SendClientMessageEx(targetid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C}You have unfrozen by %s(%d)", GetName(playerid), playerid);

    new string[256];
    format(string, sizeof(string), "Used /unfreeze to %s", GetName(targetid));
    AdminLogEx(playerid, string);
	return 1;
}

YCMD:jetpack(playerid, params[], help)
{
	if(Player[playerid][pAdmin] < 2) return SendErrorMessage(playerid, "You are not authorized to use that command.");
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
    SendClientMessage(playerid, COLOR_RED, "You gave yourself a jetpack.");

    AdminLogEx(playerid, "Used /jetpack");
	return 1;
}

YCMD:kick(playerid, params[], help)
{
	if(Player[playerid][pAdmin] < 1) return SendErrorMessage(playerid, "You are not authorized to use that command.");
	new targetid, reason[128], string[200];
	if(sscanf(params, "us[128]", targetid, reason)) return SendUsageMessage(playerid, "/kick [playername/playerid] [reason]");
	if(!IsPlayerConnected(targetid)) return SendErrorMessage(playerid, "That player is not connected.");
	
	format(string, sizeof(string), "[ADMIN]:{F9DC5C} %s(%d) has been kicked by Admin %s(%d), Reason: %s", GetName(targetid), targetid, GetName(playerid), playerid, reason);
	SendClientMessageToAll(COLOR_LIGHTBLUE, string);

    format(string, sizeof(string), "Used /kick to %s. Reason: %s", GetName(targetid), reason);
    AdminLogEx(playerid, string);
	DelayedKick(targetid);
	return 1;
}

YCMD:admin(playerid, params[], help)
{
	if(Player[playerid][pAdmin] < 1) return SendErrorMessage(playerid, "You are not authorized to use that command.");
	//if(AChatToggle) return SendErrorMessage(playerid, "Admin chat is currently disabled, tell a level 4+ to enable it.");
	new text[130], string[300];
	if(sscanf(params, "s[130]", text)) return SendUsageMessage(playerid, "/(a)dmin [text]");
	
	if(Player[playerid][pAdmin] == 1)
	{
		format(string, sizeof(string), "Helper %s: %s", GetName(playerid), text);
		SendAdminMessage(COLOR_LIGHTBLUE, string);
		AdminLogEx(playerid, string);
	}
 	else if(Player[playerid][pAdmin] == 2)
	{
		format(string, sizeof(string), "Junior Administrator %s: {FFFFFF}%s", GetName(playerid), text);
		SendAdminMessage(COLOR_LIGHTBLUE, string);
		AdminLogEx(playerid, string);
	}
 	else if(Player[playerid][pAdmin] == 3)
	{
		format(string, sizeof(string), "Senior Administrator %s: {FFFFFF}%s", GetName(playerid), text);
		SendAdminMessage(COLOR_LIGHTBLUE, string);
		AdminLogEx(playerid, string);
	}
	else if(Player[playerid][pAdmin] == 4)
	{
		format(string, sizeof(string), "Lead Administrator %s: {FFFFFF}%s", GetName(playerid), text);
  		SendAdminMessage(COLOR_LIGHTBLUE, string);
  		AdminLogEx(playerid, string);
	}
	return 1;
}

stock AdminLogEx(adminid, const action[])
{ 
    new query[2048];
	mysql_format(Database, query, sizeof query, "INSERT INTO `adminlogs` \
		(`AdminName`, \
		`Action`) \
		VALUES \
		('%e', \
		'%e')",
		GetName(adminid),
		action);
	mysql_tquery(Database, query);
}

YCMD:adminlogs(playerid, params[], help)
{
	if(Player[playerid][pAdmin] < 4) return SendErrorMessage(playerid, "You are not authorized to use that command.");

	GM[AdminLogStartPage] = 0, GM[AdminLogEndPage] = 10;
	new string[256];
	mysql_format(Database, string, sizeof(string),
		"SELECT * FROM `adminlogs` LIMIT %d,%d",
		//"SELECT * FROM `adminlogs` ORDER BY `Date` DESC LIMIT %d,%d",
		AdminLogStartPage, AdminLogEndPage);
	mysql_tquery(Database, string, "AdminLog", "i", playerid); 
	SetPVarInt(playerid, "pReport_Start", GM[AdminLogStartPage]+1);
    if(!sscanf(params, "d", AdminLogStartPage))
    {
    	GM[AdminLogEndPage] = 10;
		new stringx[256];
		mysql_format(Database, stringx, sizeof(stringx),
			"SELECT * FROM `adminlogs` LIMIT %d,%d",
			AdminLogStartPage, AdminLogEndPage);
		mysql_tquery(Database, stringx, "AdminLog", "i", playerid); 
		SetPVarInt(playerid, "pReport_Start", GM[AdminLogStartPage]+1);
    }
    //AdminLogEx(playerid, "Used /adminlogs");
	return 1;
}

forward AdminLog(playerid);
public AdminLog(playerid)
{   
    new id, adminname[24], action[256], date[256] , info[1024];
    new count = cache_num_rows();
    if(count > 0)
    {
	    for (new z; z < count; z++)
	    {
	    	cache_get_value_int(z, "ID", id);
	        cache_get_value_name(z, "AdminName", adminname);
	        cache_get_value_name(z, "Action", action);
	        cache_get_value_name(z, "Date", date);

	        format(info, sizeof(info), "%sID: %i  \
	        	Date: %s  \
	        	Admin: %s  \
	        	Log: %s\n", info, id, date, adminname, action);
	    }
	}
	else
	{
		DeletePVar(playerid, "pReport_Start");
		SendErrorMessage(playerid, "End of the page or no logs available at the moment");
		
		return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", " ");
	}
	strcat(info, "\nNext Page");
    ShowPlayerDialog(playerid, DIALOG_ADMINLOG, DIALOG_STYLE_LIST, "Logs", info, "Select", "Close");
    return 1;
}


forward AdminLogInfo(playerid);
public AdminLogInfo(playerid)
{
	new id, adminname[24], action[256], date[256] , info[1500];
	cache_get_value_int(0, "ID", id);
    cache_get_value_name(0, "AdminName", adminname);
    cache_get_value_name(0, "Action", action);
    cache_get_value_name(0, "Date", date);

    format(info, sizeof(info), "ID: %i \n\
	Date: %s \n\
	Admin: %s \n\
	Log:\n %s", id, date, adminname, action);

    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Logs", info, "Close", "");

}