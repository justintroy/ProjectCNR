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

			/*new query[300], Password[BCRYPT_HASH_LENGTH];
			mysql_format(Database, query, sizeof(query), "SELECT `Password` FROM `players` WHERE `Username` = '%e'", Player[playerid][user_name]);
			mysql_query(Database, query);
			cache_get_value_name(0, "Password", Password, BCRYPT_HASH_LENGTH);
			bcrypt_check(inputtext, Password, "OnPasswordChecked", "d", playerid);*/

			
		}
		case DIALOG_REGISTER:
		{

			if (!response) return Kick(playerid);

			if (strlen(inputtext) <= 5) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Registration", "Your password must be longer than 5 characters!\nPlease enter your password in the field below:", "Register", "Abort");

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
		}
		case DIALOG_TUTORIAL5:
		{
			Player[playerid][IsLoggedIn] = true;
			Player[playerid][Tutorial] = 1;
			SpawnPlayer(playerid);
		}

		default: return 0; // dialog ID was not found, search in other scripts
	}
	return 1;
}