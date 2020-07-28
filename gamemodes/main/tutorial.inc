StartTutorial(playerid)
{
	ClearChatbox(playerid, 8);
    TogglePlayerControllable(playerid, false);
    SetPlayerFacingAngle(playerid, 0.0);
    SetPlayerVirtualWorld(playerid, playerid+1);
    SetPlayerCameraPos(playerid, 1553.6644, -1721.0361, 29.2602);
	SetPlayerCameraLookAt(playerid, 1552.6925, -1721.2865, 29.1550);
    SetPlayerPos(playerid, 1553.6644, -1721.0361, 20.2602);
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
    strcat(msg, "We \n\n");
    strcat(msg, string);
    strcat(msg, "Pois ele sera a base de todo seu conhecimento aqui no servidor.\n\n");
    strcat(msg, string);
    ShowPlayerDialog(playerid, DIALOG_TUTORIAL0, DIALOG_STYLE_MSGBOX, MNLTAG" - TUTORIAL", msg, "YES", "");
    PlayerPlaySound(playerid, 1131, 0.0, 0.0, 0.0);
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
}