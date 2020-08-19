public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_UNUSED: return 1; // Useful for dialogs that contain only information and we do nothing depending on whether they responded or not

		case DIALOG_LOGIN:
		{
			if (!response) return Kick(playerid);

			new newtext[41];
		    format(newtext, sizeof(newtext), "xxxxxxx");
		    PlayerTextDrawSetString(playerid, Login_PasswordInput[playerid], newtext);
		    strcat(Player[playerid][TempLoginText], inputtext); 
		}
		case DIALOG_REGISTER:
		{

			if (!response) return Kick(playerid);

			if (((strlen(inputtext) <= 5) || (strlen(inputtext) >= 26))) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Registration", "Your password must be longer than 5 and less than 26 characters!\nPlease enter your password in the field below:", "Register", "Abort");

			new newtext[41];
		    format(newtext, sizeof(newtext), "xxxxxxx");
		    PlayerTextDrawSetString(playerid, Register_PasswordInput[playerid], newtext);
		    strcat(Player[playerid][TempLoginText], inputtext);

		}
		case DIALOG_PRETUTORIAL:
		{
			StartTutorial(playerid);
		}
		case DIALOG_TUTORIAL0:
		{
			SetPlayerCameraPos(playerid, 2330.0710, -2159.4934, 27.1264);
			SetPlayerCameraLookAt(playerid, 2330.9819, -2159.9258, 27.2262);
		    SetPlayerPos(playerid, 2330.0710, -2159.4934, 20.1264);
		    SetPlayerVirtualWorld(playerid, 0);
		    new msg[256]; new string[128];
		    strcat(msg, "\t\tWelcome to {f9dc5c}Manila: {3185fc}Cops {F9DC5C}N {e84855}Robbers!\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text-----\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text------\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text------\n\n");
		    strcat(msg, string);
		    strcat(msg, "Desejamos há voce um belo tutorial e preste bem atençao\n\n");
		    strcat(msg, string);
		    strcat(msg, "Pois ele sera a base de todo seu conhecimento aqui no servidor.\n\n");
		    strcat(msg, string);
		    ShowPlayerDialog(playerid, DIALOG_TUTORIAL1, DIALOG_STYLE_MSGBOX, MNLTAG" - TUTORIAL PAGE 2", msg, "YES", "");
		    PlayerPlaySound(playerid, 1131, 0.0, 0.0, 0.0);
   			PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
		}
		case DIALOG_TUTORIAL1:
		{
			SetPlayerCameraPos(playerid, 2330.0710, -2159.4934, 27.1264);
			SetPlayerCameraLookAt(playerid, 2330.9819, -2159.9258, 27.2262);
		    SetPlayerPos(playerid, 2330.0710, -2159.4934, 20.1264);
		    SetPlayerVirtualWorld(playerid, 0);
		    new msg[256]; new string[128];
		    strcat(msg, "\t\tWelcome to {f9dc5c}Manila: {3185fc}Cops {F9DC5C}N {e84855}Robbers!\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text-----\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text------\n\n");
		    strcat(msg, string);
		    strcat(msg, "----Add Text------\n\n");
		    strcat(msg, string);
		    strcat(msg, "Desejamos há voce um belo tutorial e preste bem atençao\n\n");
		    strcat(msg, string);
		    strcat(msg, "Pois ele sera a base de todo seu conhecimento aqui no servidor.\n\n");
		    strcat(msg, string);
		    ShowPlayerDialog(playerid, DIALOG_TUTORIAL5, DIALOG_STYLE_MSGBOX, MNLTAG" - TUTORIAL PAGE 3", msg, "YES", "");
		    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
		}
		case DIALOG_TUTORIAL5:
		{
			RegisterTextDrawCreate(playerid);
            RegisterTextDrawShow(playerid);
            SendClientMessage(playerid, -1, "{3185FC}[MNL:CNR] {F9DC5C}Click on the password field to enter your password and click Register!");
			PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
		}

		case DIALOG_ADMINLOG:
		{
	        if(!response)
        	{
        		DeletePVar(playerid, "pReport_Start");
        		return 1;
        	}
        	if(!strcmp(inputtext, "Next Page"))
            {
            	GM[AdminLogStartPage] += 10;
				new string[256];
				mysql_format(Database, string, sizeof(string),
					"SELECT * FROM `adminlogs` LIMIT %d,%d",
					AdminLogStartPage, AdminLogEndPage);
				mysql_tquery(Database, string, "AdminLog", "i", playerid); 
				SetPVarInt(playerid, "pReport_Start", GM[AdminLogStartPage]+1);
            }
            else
            {
	        	new szQuery[96];
	            format(szQuery, sizeof(szQuery), "SELECT * FROM `adminlogs` WHERE `ID` = %d LIMIT 1", GetPVarInt(playerid, "pReport_Start") + listitem);
	            mysql_tquery(Database, szQuery, "AdminLogInfo", "i", playerid);
	        }
		}
		default: return 0; // dialog ID was not found, search in other scripts
	}
	
#if defined Fix_OnDialogResponse
	return Fix_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#else
	return 1;
#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse Fix_OnDialogResponse
#if defined Fix_OnDialogResponse
	forward Fix_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif
