#include <YSI_Coding\y_hooks>
#include <timestamp>

#define MAX_BAN_REASON_LENGTH 64
#define KICK_TIMER_DELAY 150

#define CIDR_BAN_MASK \
	(-1<<(32-(26)))

#define MAX_PLAYER_IP 18

enum E_BAN_DATA {
	BAN_CMD_TIMESTAMP,
	BAN_TARGET_ID,
	BAN_TARGET_NAME[MAX_PLAYER_NAME],
	BAN_TARGET_IP[MAX_PLAYER_IP],
	BAN_DAYS,
	BAN_REASON[MAX_BAN_REASON_LENGTH],
};

enum E_UNBAN_DATA {
	UNBAN_CMD_TIMESTAMP,
	UNBAN_TARGET_ID,
	UNBAN_TARGET_NAME[MAX_PLAYER_NAME]
};

new adminBanData[MAX_PLAYERS][E_BAN_DATA];
new adminUnBanData[MAX_PLAYERS][E_UNBAN_DATA];


hook OnPlayerConnect(playerid) 
{
	adminBanData[playerid][BAN_TARGET_ID] = INVALID_PLAYER_ID;
	adminUnBanData[playerid][UNBAN_TARGET_ID] = -1;

    new name[MAX_PLAYER_NAME];
    new ip[MAX_PLAYER_IP];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
	GetPlayerIp(playerid, ip, MAX_PLAYER_IP);

	new string[MAX_PLAYER_NAME + 256];
	mysql_format(Database, string, sizeof(string),
		"SELECT * FROM bans WHERE (name = '%e') OR (ip = '%e') OR (longip & %i = %i) LIMIT 1",
		name, ip, CIDR_BAN_MASK, (IpToLong(ip) & CIDR_BAN_MASK)
	);

	mysql_tquery(Database, string, "OnUserBanDataLoad", "i", playerid);
	return 1;
}

forward OnUserBanDataLoad(playerid);
public OnUserBanDataLoad(playerid) 
{
	if (cache_num_rows() == 1) 
	{
		new string[144];
		new ban_id;
		new ban_expire_timestamp;
   		cache_get_value_name_int(0, "id", ban_id);
   		cache_get_value_name_int(0, "ban_expire_timestamp", ban_expire_timestamp);

   		if (ban_expire_timestamp != 0 && gettime() >= ban_expire_timestamp) 
   		{
            mysql_format(Database, string, sizeof(string),
                "DELETE FROM bans WHERE id = %i",
                ban_id);

			mysql_tquery(Database, string);
			mysql_tquery(Database, "ALTER TABLE bans AUTO_INCREMENT = 1");
			return;
		}

		new ban_timestamp;
		new ban_admin[MAX_PLAYER_NAME];
		new ban_reason[MAX_BAN_REASON_LENGTH];
		new banip[24];

   		cache_get_value_name_int(0, "ban_timestamp", ban_timestamp);
   		cache_get_value_name(0, "ban_admin", ban_admin, sizeof(ban_admin));
   		cache_get_value_name(0, "ban_reason", ban_reason, sizeof(ban_reason));
   		cache_get_value_name(0, "ip", banip, sizeof(banip));

	    for (new i = 0; i < 100; i++) 
	    {
			SendClientMessage(playerid, -1, "");
	    }

		format(string, sizeof(string), "[MNLCNR]: {F9DC5C}This account is banned on this server! Banned on %s (%s ago) by admin %s!", ReturnDate(ban_timestamp), ReturnTimelapse(ban_timestamp, gettime()), ban_admin);
	    SendClientMessage(playerid, COLOR_BLUE, string);
		format(string, sizeof(string), "[MNLCNR]: {F9DC5C}IP: %s Reason: %s", banip, ban_reason);
	    SendClientMessage(playerid, COLOR_BLUE, string);
	    if (ban_expire_timestamp != 0) 
	    {
			format(string, sizeof(string), "[MNLCNR]: {F9DC5C}Your ban will be lifted on: %s (%s)", ReturnDate(ban_expire_timestamp), ReturnTimelapse(gettime(), ban_expire_timestamp));
		    SendClientMessage(playerid, COLOR_BLUE, string);
		}
		else
		{
			SendServerMessage(playerid, " You are banned permanently.");
		}
		SendServerMessage(playerid, "If you think this is a mistake, kindly submit a appeal ticket at "SERVER_DISCORD"");
		defer KickBannedPlayer(playerid);
	}
	
	return;
}

YCMD:ban(playerid, params[], help) 
{
    if (Player[playerid][pAdmin] < 2) return SendErrorMessage(playerid, "You are not authorized to use that command.");

	if (!strcmp(params, "yes", true)) 
	{
		if (adminBanData[playerid][BAN_TARGET_ID] != INVALID_PLAYER_ID) 
		{
		    if (gettime() > (adminBanData[playerid][BAN_CMD_TIMESTAMP] + 60)) 
		    {
		        adminBanData[playerid][BAN_TARGET_ID] = INVALID_PLAYER_ID;
   				return SendErrorMessage(playerid, "/ban command timeout, you have to respond to confirmation within a minute!");
			}

		    new name[MAX_PLAYER_NAME];
		    GetPlayerName(playerid, name, MAX_PLAYER_NAME);

			new ban_expire_timestamp = (adminBanData[playerid][BAN_DAYS] == 0) ? (0) : (gettime() + (adminBanData[playerid][BAN_DAYS] * 86400));

 			new string[1024];
			mysql_format(Database, string, sizeof(string),
				"INSERT INTO bans(name, ip, longip, ban_timestamp, ban_expire_timestamp, ban_admin, ban_reason) \
					VALUES ('%e', '%e', %i, %i, %i, '%e', '%e')",
				adminBanData[playerid][BAN_TARGET_NAME], adminBanData[playerid][BAN_TARGET_IP], IpToLong(adminBanData[playerid][BAN_TARGET_IP]), gettime(), ban_expire_timestamp, name, adminBanData[playerid][BAN_REASON]);

			mysql_tquery(Database, string);

			if (adminBanData[playerid][BAN_DAYS] != 0) 
			{
				format(string, sizeof(string), "[ADMIN]: {F9DC5C} %s has banned %s for %i days (will be unbanned on %s) || Today's Date: %s || Reason: %s", name, adminBanData[playerid][BAN_TARGET_NAME], adminBanData[playerid][BAN_DAYS], ReturnDate(ban_expire_timestamp), ReturnDate(gettime()), adminBanData[playerid][BAN_REASON]);
			} 
			else 
			{
				format(string, sizeof(string), "*[ADMIN]: {F9DC5C} %s has banned %s permanently || Today's Date: %s || Reason: %s", name, adminBanData[playerid][BAN_TARGET_NAME], ReturnDate(gettime()), adminBanData[playerid][BAN_REASON]);
			}
			SendClientMessageToAll(COLOR_LIGHTBLUE, string);

		    GetPlayerName(adminBanData[playerid][BAN_TARGET_ID], name, MAX_PLAYER_NAME);
		    if (!strcmp(name, adminBanData[playerid][BAN_TARGET_NAME])) 
		    {
				/*for (new i = 0; i < sizeof(banTextDraw); i++) 
				{
					TextDrawShowForPlayer(adminBanData[playerid][BAN_TARGET_ID], banTextDraw[i]);
				}*/

			    for (new i = 0; i < 100; i++) 
			    {
					SendClientMessage(adminBanData[playerid][BAN_TARGET_ID], COLOR_LIGHTBLUE, "");
			    }

		    	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
		        format(string, sizeof(string), "[ADMIN]: {F9DC5C}Your account has been banned on this server, by admin %s! [Today's Date: %s]", name, ReturnDate(gettime()));
			    SendClientMessage(adminBanData[playerid][BAN_TARGET_ID], COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "[ADMIN]: {F9DC5C}Reason: %s", adminBanData[playerid][BAN_REASON]);
			    SendClientMessage(adminBanData[playerid][BAN_TARGET_ID], COLOR_LIGHTBLUE, string);
			    if (ban_expire_timestamp != 0) 
			    {
					format(string, sizeof(string), "[ADMIN]: {F9DC5C}Your ban will be lifted on: %s (%s later)", ReturnDate(ban_expire_timestamp), ReturnTimelapse(gettime(), ban_expire_timestamp));
				    SendClientMessage(adminBanData[playerid][BAN_TARGET_ID], COLOR_LIGHTBLUE, string);
				}

				new stringz[256];
				format(stringz, sizeof(stringz), "Used /ban to %s. Days: %d Reason: %s ", GetName(adminBanData[playerid][BAN_TARGET_ID]), adminBanData[playerid][BAN_DAYS], adminBanData[playerid][BAN_REASON]);
			   	AdminLogEx(playerid, stringz);

                SetTimerEx("_KickPlayerDelayed", KICK_TIMER_DELAY, 0, "i", adminBanData[playerid][BAN_TARGET_ID]);
			}
			else 
			{
			    format(string, sizeof(string), "[ADMIN]: {F9DC5C}%s was banned, even he went offline but ban was successfull!", adminBanData[playerid][BAN_TARGET_NAME]);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			}

            adminBanData[playerid][BAN_TARGET_ID] = INVALID_PLAYER_ID;
		}
		return 1;
	}
	else if (!strcmp(params, "no", true)) 
	{
		if (adminBanData[playerid][BAN_TARGET_ID] != INVALID_PLAYER_ID) 
		{
		    if (gettime() > (adminBanData[playerid][BAN_CMD_TIMESTAMP] + 60)) 
		    {
		        adminBanData[playerid][BAN_TARGET_ID] = INVALID_PLAYER_ID;
   				return SendErrorMessage(playerid, "/ban command timeout, you have to respond to confirmation within a minute!");
			}

		    adminBanData[playerid][BAN_TARGET_ID] = INVALID_PLAYER_ID;

		    SendErrorMessage(playerid, "Ban was canceled.");
		}
		return 1;
	}

	new targetid, reason[MAX_BAN_REASON_LENGTH], days;
	if (sscanf(params, "uis["#MAX_BAN_REASON_LENGTH"]", targetid, days, reason)) 
	{
		SendUsageMessage(playerid, "/ban [id/name] [days] [reason]");
	    SendUsageMessage(playerid, "Note: 0 days means a permanent ban from server.");
	    return 1;
	}

	if (!IsPlayerConnected(targetid)) 
	{
	    return SendErrorMessage(playerid, "Target player isn't online.");
	}

	if (days < 0 || days > 365) 
	{
	    return SendErrorMessage(playerid, "Number of days cannot be negative or greater than 365 days! [0 = permanent ban]");
	}

	if (strlen(reason) < 4) 
	{
	    return SendErrorMessage(playerid, "Invalid reason entered.");
	}

	adminBanData[playerid][BAN_CMD_TIMESTAMP] = gettime();
	adminBanData[playerid][BAN_TARGET_ID] = targetid;
	adminBanData[playerid][BAN_DAYS] = days;
	GetPlayerName(targetid, adminBanData[playerid][BAN_TARGET_NAME], MAX_PLAYER_NAME);
	GetPlayerIp(targetid, adminBanData[playerid][BAN_TARGET_IP], 18);
	format(adminBanData[playerid][BAN_REASON], MAX_BAN_REASON_LENGTH, reason);

	new string[1024];
	if (days != 0) 
	{
		format(string, sizeof(string),
		    "[MNLCNR]:{F9DC5C}You are about to ban \"%s\" for %i days || Reason: %s || Today's date: %s",
		    adminBanData[playerid][BAN_TARGET_NAME], days, reason, ReturnDate(gettime()));
	} 
	else 
	{
		format(string, sizeof(string),
		    "[MNLCNR]:{F9DC5C}You are about to ban \"%s\" permanently || Reason: %s || Today's date: %s",
		    adminBanData[playerid][BAN_TARGET_NAME], reason, ReturnDate(gettime()));
	}
	SendClientMessage(playerid, COLOR_BLUE, "");
	SendClientMessage(playerid, COLOR_BLUE, string);
	SendClientMessage(playerid, COLOR_BLUE, "[MNLCNR]:{F9DC5C}Please confirm by typing \"/ban yes\" to ban the player, or \"/ban no\" to cancel");
	return 1;
}

YCMD:findban(playerid, params[], help) 
{
    if (Player[playerid][pAdmin] < 1) return SendErrorMessage(playerid, "You are not authorized to use that command.");

	new match[32];
	if (sscanf(params, "s[32]", match)) 
	{
		return SendUsageMessage(playerid, "/findban [name/ip]");
	}

	new string[MAX_PLAYER_NAME + 256];
	mysql_format(Database, string, sizeof(string),
		"SELECT * FROM bans WHERE (name = '%e') OR (ip = '%e') OR (longip & %i = %i) LIMIT 1",
		match, match, CIDR_BAN_MASK, (IpToLong(match) & CIDR_BAN_MASK)
	);

	new stringz[256];
	format(stringz, sizeof(stringz), "Used /findban to find %s. ", match);
    AdminLogEx(playerid, stringz);

    return mysql_tquery(Database, string, "OnFindBanSearchDataLoad", "is", playerid, match);
}

forward OnFindBanSearchDataLoad(playerid, const match[]);
public OnFindBanSearchDataLoad(playerid, const match[]) 
{
    if (cache_num_rows() == 0) 
    {
	    SendErrorMessage(playerid, "User not found in ban database!");
	    return;
	}

	new string[512];

	new ban_id;
	new ban_expire_timestamp;
	cache_get_value_name_int(0, "id", ban_id);
	cache_get_value_name_int(0, "ban_expire_timestamp", ban_expire_timestamp);

   	if (ban_expire_timestamp != 0 && gettime() >= ban_expire_timestamp) {
    	mysql_format(Database, string, sizeof(string),
     		"DELETE FROM bans WHERE id = %i",
			 ban_id
		);

		mysql_tquery(Database, string);
		mysql_tquery(Database, "ALTER TABLE bans AUTO_INCREMENT = 1");

	    SendErrorMessage(playerid, "User not found in ban database or the ban has been lifted.");
	    return;
	}

	new name[MAX_PLAYER_NAME];
    new ip[MAX_PLAYER_IP];
    new date;
    new unban_date;
	new admin[MAX_PLAYER_NAME];
	new reason[MAX_BAN_REASON_LENGTH];

	cache_get_value_name(0, "name", name, MAX_PLAYER_NAME);
	cache_get_value_name(0, "ip", ip, MAX_PLAYER_IP);
   	cache_get_value_name_int(0, "ban_timestamp", date);
   	cache_get_value_name_int(0, "ban_expire_timestamp", unban_date);
	cache_get_value_name(0, "ban_admin", admin, MAX_PLAYER_NAME);
	cache_get_value_name(0, "ban_reason", reason, MAX_BAN_REASON_LENGTH);

	if (unban_date == 0) 
	{
		format(string, sizeof(string),
			COL_YELLOW "/findban search result for \"%s\":\n\n"COL_BLUE"* UserName: "COL_RED"%s\n"COL_BLUE"* IP. Address: "COL_RED"%s\n"COL_BLUE"* Banned By Admin: "COL_RED"%s\n"COL_BLUE"* Banned On Date: "COL_RED"%s (%s ago)\n"COL_BLUE"* Ban Type: "COL_RED"Permanent\n"COL_BLUE"* Reason: "COL_RED"%s\n\n"COL_YELLOW"Today's Date: %s!\nTo unban a player, type /unban <name/ip>!",
			match, name, ip, admin, ReturnDate(date), ReturnTimelapse(date, gettime()), reason, ReturnDate(gettime())
		);
	} else {
		format(string, sizeof(string),
			COL_YELLOW "/findban search result for \"%s\":\n\n"COL_BLUE"* UserName: "COL_RED"%s\n"COL_BLUE"* IP. Address: "COL_RED"%s\n"COL_BLUE"* Banned By Admin: "COL_RED"%s\n"COL_BLUE"* Banned On Date: "COL_RED"%s (%s ago)\n"COL_BLUE"* UnBan On: "COL_RED"%s (%s)\n"COL_BLUE"* Reason: "COL_RED"%s\n\n"COL_YELLOW"Today's Date: %s!\nTo unban a player, type /unban <name/ip>!",
			match, name, ip, admin, ReturnDate(date), ReturnTimelapse(date, gettime()), ReturnDate(unban_date), ReturnTimelapse(gettime(), unban_date), reason, ReturnDate(gettime())
		);
	}

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "[MNL:CNR] Ban info:", string, "Close", "");
}

YCMD:unban(playerid, params[], help) 
{
    if (Player[playerid][pAdmin] < 2) return SendErrorMessage(playerid, "You are not authorized to use that command.");

	if (!strcmp(params, "yes", true)) 
	{
	    if (adminUnBanData[playerid][UNBAN_TARGET_ID] != -1) 
	    {
		    if (gettime() > (adminUnBanData[playerid][UNBAN_CMD_TIMESTAMP] + 60)) 
		    {
		        adminUnBanData[playerid][UNBAN_TARGET_ID] = -1;
   				return SendErrorMessage(playerid, "/unban command timeout, you have to respond to confirmation within a minute!");
			}

			new string[144];

			new name[MAX_PLAYER_NAME];
		    GetPlayerName(playerid, name, MAX_PLAYER_NAME);

			mysql_format(Database, string, sizeof(string),
	     		"DELETE FROM bans WHERE id = %i",
				 adminUnBanData[playerid][UNBAN_TARGET_ID]
			);

			mysql_tquery(Database, string);
			mysql_tquery(Database, "ALTER TABLE bans AUTO_INCREMENT = 1");

			format(string, sizeof(string), "[ADMIN]: {F9DC5C}Admin %s has unbanned %s || Today's Date: %s", name, adminUnBanData[playerid][UNBAN_TARGET_NAME], ReturnDate(gettime()));
			SendClientMessageToAll(COLOR_LIGHTBLUE, string);

			new stringz[256];
			format(stringz, sizeof(stringz), "Used /unban to unban %s. ", adminUnBanData[playerid][UNBAN_TARGET_NAME]);
		    AdminLogEx(playerid, stringz);

			adminUnBanData[playerid][UNBAN_TARGET_ID] = -1;
		}
  		return 1;
	}
	else if (!strcmp(params, "no", true)) {
	    if (adminUnBanData[playerid][UNBAN_TARGET_ID] != -1) {
		    if (gettime() > (adminUnBanData[playerid][UNBAN_CMD_TIMESTAMP] + 60)) {
		        adminUnBanData[playerid][UNBAN_TARGET_ID] = -1;
   				return SendErrorMessage(playerid, "/unban command timeout, you have to respond to confirmation within a minute!");
			}

		    adminUnBanData[playerid][UNBAN_TARGET_ID] = -1;

		    SendErrorMessage(playerid, "UnBan was canceled.");
		}
		return 1;
	}

	new match[32];
	if (sscanf(params, "s[32]", match)) {
		return SendUsageMessage(playerid, "/unban [name/ip]");
	}

	new string[MAX_PLAYER_NAME + 256];
	mysql_format(Database, string, sizeof(string),
		"SELECT * FROM bans WHERE (name = '%e') OR (ip = '%e') OR (longip & %i = %i) LIMIT 1",
		match, match, CIDR_BAN_MASK, (IpToLong(match) & CIDR_BAN_MASK));

    return mysql_tquery(Database, string, "OnUnBanSearchDataLoad", "i", playerid);
}

forward OnUnBanSearchDataLoad(playerid);
public OnUnBanSearchDataLoad(playerid) 
{
    if (cache_num_rows() == 0) 
    {
	    SendErrorMessage(playerid, "User not found in ban database!");
	    return;
	}

	new string[144];

	new ban_expire_timestamp;
	cache_get_value_name_int(0, "id", adminUnBanData[playerid][UNBAN_TARGET_ID]);
	cache_get_value_name_int(0, "ban_expire_timestamp", ban_expire_timestamp);

   	if (ban_expire_timestamp != 0 && gettime() >= ban_expire_timestamp) 
   	{
    	mysql_format(Database, string, sizeof(string),
     		"DELETE FROM bans WHERE id = %i",
			 adminUnBanData[playerid][UNBAN_TARGET_ID]
		);

		mysql_tquery(Database, string);
		mysql_tquery(Database, "ALTER TABLE bans AUTO_INCREMENT = 1");

	    SendErrorMessage(playerid, "User not found in ban database or the ban has been lifted.");
	    return;
	}

    new ip[MAX_PLAYER_IP];
    new date;
    new unban_date;
	new admin[MAX_PLAYER_NAME];
	new reason[MAX_BAN_REASON_LENGTH];

	cache_get_value_name(0, "name", adminUnBanData[playerid][UNBAN_TARGET_NAME], MAX_PLAYER_NAME);
	cache_get_value_name(0, "ip", ip, MAX_PLAYER_IP);
   	cache_get_value_name_int(0, "ban_timestamp", date);
   	cache_get_value_name_int(0, "ban_expire_timestamp", unban_date);
	cache_get_value_name(0, "ban_admin", admin, MAX_PLAYER_NAME);
	cache_get_value_name(0, "ban_reason", reason, MAX_BAN_REASON_LENGTH);

	SendClientMessage(playerid, -1, "");

	format(string, sizeof(string), "[ADMIN]:{F9DC5C} Are you sure you want to unban \"%s\" (ip: %s)?", adminUnBanData[playerid][UNBAN_TARGET_NAME], ip);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	if (unban_date == 0) {
		format(string, sizeof(string),
			"[ADMIN]:{F9DC5C} %s was banned by admin %s, on %s (%s ago) || Unban On: %s || Reason: %s",
			adminUnBanData[playerid][UNBAN_TARGET_NAME], admin, ReturnDate(date), ReturnTimelapse(date, gettime()), ReturnDate(unban_date), reason
		);
	} else {
		format(string, sizeof(string),
			"[ADMIN]:{F9DC5C} %s was banned by admin %s, on %s (%s ago) || Ban Type: Permanent || Reason: %s",
			adminUnBanData[playerid][UNBAN_TARGET_NAME], admin, ReturnDate(date), ReturnTimelapse(date, gettime()), reason
		);
	}
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C} Type \"/unban yes\" to unban this player, or type \"/unban no\" to cancel");

	adminUnBanData[playerid][UNBAN_CMD_TIMESTAMP] = gettime();
}

IpToLong(const address[]) 
{
	new parts[4];
	sscanf(address, "p<.>a<i>[4]", parts);
	return ((parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3]);
}

ReturnDate(timestamp) 
{
	static const MONTH_NAMES[12][] = {
		"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};

	new year, month, day, hour, minute, second;
	stamp2datetime(timestamp, year, month, day, hour, minute, second);

	new ret[32];
	format(ret, sizeof(ret),
		"%i %s, %i",
		day-1, MONTH_NAMES[month - 1], year
	);
	return ret;
}

ReturnTimelapse(start, till) 
{
    new ret[32];
	new seconds = (till - start);

	const
		MINUTE = (60),
		HOUR = (60 * MINUTE),
		DAY = (24 * HOUR),
		MONTH = (30 * DAY);

	if (seconds == 1) {
		format(ret, sizeof(ret), "a second");
	} else if (seconds < (1 * MINUTE)) {
		format(ret, sizeof(ret), "%i seconds", seconds);
	} else if (seconds < (2 * MINUTE)) {
		format(ret, sizeof(ret), "a minute");
	} else if (seconds < (45 * MINUTE)) {
		format(ret, sizeof(ret), "%i minutes", (seconds / MINUTE));
	} else if (seconds < (90 * MINUTE)) {
		format(ret, sizeof(ret), "an hour");
	} else if (seconds < (24 * HOUR)) {
		format(ret, sizeof(ret), "%i hours", (seconds / HOUR));
	} else if (seconds < (48 * HOUR)) {
		format(ret, sizeof(ret), "a day");
	} else if (seconds < (30 * DAY)) {
		format(ret, sizeof(ret), "%i days", (seconds / DAY));
	} else if (seconds < (12 * MONTH)) {
		new months = floatround(seconds / DAY / 30);
      	if (months <= 1) {
			format(ret, sizeof(ret), "a month");
      	} else {
			format(ret, sizeof(ret), "%i months", months);
		}
	} else {
      	new years = floatround(seconds / DAY / 365);
      	if (years <= 1) {
			format(ret, sizeof(ret), "a year");
      	} else {
			format(ret, sizeof(ret), "%i years", years);
		}
	}

	return ret;
}

timer KickBannedPlayer[4000](playerid)
{
	Kick(playerid);
	return 1;
}