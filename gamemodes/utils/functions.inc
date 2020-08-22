#include <YSI_Coding\y_hooks>

LoadObject(playerid)
{
	TextDrawShowForPlayer(playerid, GM[LoadingTD][0]);
	TextDrawShowForPlayer(playerid, GM[LoadingTD][1]);
	TextDrawShowForPlayer(playerid, GM[LoadingTD][2]);
	TextDrawShowForPlayer(playerid, GM[LoadingTD][3]);
	TextDrawShowForPlayer(playerid, GM[LoadingTD][4]);
	TogglePlayerControllable(playerid, false);
	/*Player[playerid][Spawned] = false;
	Player[playerid][LoadWorld] = false;*/
	defer ObjectLoaded(playerid);
	return 1;
}

GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
	return name;
}

stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) // By Gabriel "Larcius" Cordes
{
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(x1,x2),2)),floatsqroot(floatpower(floatsub(y1,y2),2))),floatsqroot(floatpower(floatsub(z1,z2),2)));
}

stock Float:GetDistanceToPoint(playerid, Float:x1, Float:y1, Float:z1) // By Gabriel "Larcius" Cordes
{
	if(IsPlayerConnected(playerid))
	{
		new Float:x2, Float:y2, Float:z2;
		GetPlayerPos(playerid, x2, y2, z2);
		return GetDistanceBetweenPoints(x1, y1, z1, x2, y2, z2);
	}
	return FLOAT_INFINITY;
}

stock GetPlayerNameFromId(id)
{
	new name[MAX_PLAYER_NAME], query[256], Cache:result;
	mysql_format(Database, query, sizeof(query), "SELECT `Username` FROM `players` WHERE `ID` = %d", id);
	result = mysql_query(Database, query, true);
	if(cache_num_rows() > 0)
		cache_get_value(0, "Username", name);
	else
		format(name, sizeof(name), "NAME NOT FOUND");
	cache_delete(result);
	return name;
}

forward  ClearChatbox(playerid, lines);
public ClearChatbox(playerid, lines) 
{
    if (IsPlayerConnected(playerid)) 
    {
        for (new i = 0; i < lines; i++) 
        {
            SendClientMessage(playerid, COLOR_DARK, " ");
        }
    }
    return true;
}

stock token_by_delim(const string[], return_str[], delim, start_index) // gl_common.inc
{
	new x=0;
	while(string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}

stock LoadStaticVehiclesFromFile(const filename[]) // gl_common.inc
{
	new File:file_ptr;
	new line[256];
	new var_from_line[64];
	new vehicletype;
	new Float:SpawnX;
	new Float:SpawnY;
	new Float:SpawnZ;
	new Float:SpawnRot;
    new Color1, Color2;
	new index;
	new vid;
	new vehicles_loaded;
	new time = gettime();
	
	file_ptr = fopen(filename,filemode:io_read);
	if(!file_ptr) return 0;

	vehicles_loaded = 0;

	while(fread(file_ptr,line,256) > 0)
	{
	    index = 0;

	    // Read type
  		index = token_by_delim(line,var_from_line,',',index);
  		if(index == (-1)) continue;
  		vehicletype = strval(var_from_line);
   		if(vehicletype < 400 || vehicletype > 611) continue;

  		// Read X, Y, Z, Rotation
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnX = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnY = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnZ = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnRot = floatstr(var_from_line);

  		// Read Color1, Color2
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		Color1 = strval(var_from_line);

  		index = token_by_delim(line,var_from_line,';',index+1);
  		Color2 = strval(var_from_line);
  		
  		//printf("%d,%.2f,%.2f,%.2f,%.4f,%d,%d",vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
  		
  		vid = AddStaticVehicleEx(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2,(30*60),1); // respawn 30 minutes
		
		new numplate_test[32+1];
		format(numplate_test,32,"C5{FF0000}%dMNL",vid+87);
		SetVehicleNumberPlate(vid, numplate_test);
		//VehicleFuel[vid] = 50 + random(25);
		vehicles_loaded++;
	}

	fclose(file_ptr);
	printf("Loaded %d vehicles from: %s (%d ms)",vehicles_loaded,filename,gettime() - time);
	return vehicles_loaded;
}

stock SendAdminMessage(color, const string[])
{
	foreach(new i : Player)
	{
		if(Player[i][pAdmin] >= 1)
		{
		    SendClientMessage(i, color, string);
		}
	}
}

stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
	static
	    args,
	    str[144];
	if ((args = numargs()) == 3)
	{
	    SendClientMessage(playerid, color, text);
	}
	else
	{
		while (--args >= 3)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		SendClientMessage(playerid, color, str);

		#emit RETN
	}
	return 1;
}

stock SendClientMessageToAllEx(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.pri args
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format

        #emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) {
			SendClientMessage(i, color, string);
		}
		return 1;
	}
	return SendClientMessageToAll(color, str);
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, x, y, a);
    GetPlayerFacingAngle(playerid, a);
    if (GetPlayerVehicleID(playerid))
    {
      GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    }
    x += (distance * floatsin(-a, degrees));
    y += (distance * floatcos(-a, degrees));
}

stock PlayerIsNearPlayer(playerid, targetid, Float:radius)
{
	new
        Float:x,
        Float:y,
        Float:z;

	GetPlayerPos(playerid, x, y, z);

    new
        matchingVW = GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid),
        matchingInt = GetPlayerInterior(playerid) == GetPlayerInterior(targetid),
        inRange = IsPlayerInRangeOfPoint(targetid, radius, x, y, z);

	return matchingVW && matchingInt && inRange;
}

stock GetClosestPlayer(playerid, Float:range = 10000.0)
{
    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    return GetClosestPlayerFromPoint(x, y, z, range, playerid);
}

stock Float:Distance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
    return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

GetClosestPlayerFromPoint(Float:x, Float:y, Float:z, &Float:lowestdistance = 10000.0, exceptionid = INVALID_PLAYER_ID)
{
    new
        Float:px,
        Float:py,
        Float:pz,
        Float:distance,
        closestplayer = -1;

    foreach(new i : Player)
    {
        if (i == exceptionid)
            continue;

        GetPlayerPos(i, px, py, pz);

        distance = Distance(px, py, pz, x, y, z);

        if (distance < lowestdistance)
        {
            lowestdistance = distance;
            closestplayer = i;
        }
    }
    return closestplayer;
}

stock GetVehicleRelativePos(vehicleid, &Float:x, &Float:y, &Float:z, Float:xoff= 0.0, Float:yoff= 0.0, Float:zoff= 0.0)
{
    new Float:rot;
    GetVehicleZAngle(vehicleid, rot);
    rot = 360 - rot;
    GetVehiclePos(vehicleid, x, y, z);
    x = floatsin(rot, degrees) * yoff + floatcos(rot, degrees) * xoff + x;
    y = floatcos(rot, degrees) * yoff - floatsin(rot, degrees) * xoff + y;
    z = zoff + z;
}