YCMD:jetpack(playerid, params[], help)
{
	if (help) return SCM(playerid, COLOR_RED, "Gives player a jetpack.");
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	return 1;
}

YCMD:myid(playerid, params[], help)
{
	new string[60];
	if (help) return SCM(playerid, COLOR_RED, "Shows your playerid");

	
	format( string, sizeof( string ),"Your id is: %i", Player[playerid][user_id]);
	SCM(playerid, COLOR_RED, string);
	return 1;
}

YCMD:help(playerid, params[], help)
{
    if (help) return SendClientMessage(playerid, -1, "Displays help about commands");
    // If help system occured, "/help help" the player will get the message above.
    if (isnull(params)) return SendClientMessage(playerid, -1, "Syntax Error: /help [Command]");
    // If the parameters are null "/help" the player will get the syntax message above ( COLOR = -1 wich is some sort of black )
    Command_ReProcess(playerid, params, true);
    // Call to put text through the command processor, with the help functions enabled or disabled.
    return 1;
}

YCMD:tp(playerid, params[], help) 
{
	new Float:x, Float:y, Float: z;
	if (help) return SCM(playerid, COLOR_RED, "Teleport to coordinates. /tp <x, y, z>");
	if(sscanf(params, "fff", x, y, z))	return SendClientMessage(playerid, COLOR_RED, "[USAGE] /tp <x, y, z>");
	
	SetPlayerPos(playerid, x, y, z);

	return 1;
}

YCMD:audio(playerid, params[], help) 
{
	PlayAudioStreamForPlayer(playerid, "http://striiming.trio.ee/dfm64.mp3");
	return 1;
}


YCMD:audio2(playerid, params[], help) 
{
	PlayAudioStreamForPlayer(playerid, "http://uc89302be8dd3538a5118da93a96.dl.dropboxusercontent.com/cd/0/inline/A8MpFQhvtGM9IKBtnDltS_n_3wPNcKdMNj2jUjySyfTXQZHLAasM9_HfTK0LPSXf-s2_My9qdgiE_hBFw5L_pqWatNVQXnweP9J5baoi7NG7Vu8sdSQJ2QnyAa8MTsWCe_Y/file#");	
	return 1;
}


YCMD:attest(playerid, params[], help) 
{
	SetPlayerAttachedObject( playerid, 9, 371, 1, 0.048503, -0.112052, -0.021527, 356.659484, 85.123565, 0.000000, 0.919283, 1.000000, 1.000000 );
	SetPlayerAttachedObject( playerid, 8, 19078, 3, -0.025633, 0.071474, -0.042353, 152.483703, 170.041259, 353.874603, 1.000000, 1.000000, 1.000000 );
	return 1;
}

YCMD:neontest(playerid, params[], help) 
{
	new vid = GetPlayerVehicleID(playerid);
	new neon1 = CreateObject(18648,0,0,0,0,0,0);
	new neon2 = CreateObject(18648,0,0,0,0,0,0);
	AttachObjectToVehicle(neon1, vid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	AttachObjectToVehicle(neon2, vid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	return 1;
}

YCMD:cargo(playerid, params[], help) 
{
	new g_Object = CreateObject(2932, 2271.4665, -1253.1188, 25.5979, 0.1899, 0.2399, 176.7069); 
	new vid = GetPlayerVehicleID(playerid);
	AttachObjectToVehicle(g_Object, vid, 0.0299, -1.5399, 1.0999, 0.1899, 0.2399, 0.2800);
	return 1;
}

YCMD:spawn(playerid, params[], help) 
{
	new car;
	new string[128];
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, Float:X, Float:Y, Float:Z);
	if(sscanf(params,"i", car)) return SendClientMessage(playerid,0xff0000ff,"USAGE: /spawn <Vehicle ID 400 - 611>");
	else if(car < 400 || car >611) return SendClientMessage(playerid, 0xff0000ff, "ERROR: Cannot go under 400 or above 611.");
	{
		if(Vehicle[playerid] != 0)
	    {
	        DestroyVehicle(Vehicle[playerid]);
	    }
	    Vehicle[playerid] = CreateVehicle(car, X, Y, Z + 2.0, 0, -1, -1, 1);
	    format(string,sizeof(string),"You Have Spawned Vehicle ID %i",car);
	    SendClientMessage(playerid, 0xffffffff, string);
	    PutPlayerInVehicle(playerid, Vehicle[playerid], 0);
	}
	return 1;
}