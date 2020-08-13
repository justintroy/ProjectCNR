
YCMD:enter(playerid, params[], help) 
{
	OnPlayerEnter(playerid);
	return 1;
}

YCMD:exit(playerid, params[], help) 
{
	OnPlayerEnter(playerid);
	return 1;
}


YCMD:myid(playerid, params[], help)
{
	new string[1024];
	if (help) return SCM(playerid, COLOR_RED, "Shows your playerid");

	
	format( string, sizeof( string ),"Your id is: %i. Log: %i. Registered IP: %s. PlayTime: %d", 
		Player[playerid][ID], Player[playerid][IsLoggedIn], Player[playerid][IP], Player[playerid][PlayTime]);
	SCM(playerid, COLOR_RED, string);
	return 1;
}

YCMD:help(playerid, params[], help)
{
    if (help) return SendClientMessage(playerid, -1, "Displays help about commands");
    if (isnull(params)) return SendClientMessage(playerid, -1, "Syntax Error: /help [Command]");
    Command_ReProcess(playerid, params, true);

    return 1;
}

YCMD:tp(playerid, params[], help) 
{
	new Float:x, Float:y, Float: z, interior, world;
	if (help) return SCM(playerid, COLOR_RED, "Teleport to coordinates. /tp <x, y, z, interiorid, world>");
	if(sscanf(params, "fffdd", x, y, z, interior, world))	return SendClientMessage(playerid, COLOR_RED, "[USAGE] /tp <x, y, z, interiorid, world>");
	
	SetPlayerVirtualWorld(playerid, world);
	SetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(playerid, interior);
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

/*YCMD:spawnveh(playerid, params[], help) 
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
}*/