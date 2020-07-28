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
	new time = GetTickCount();
	
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
	printf("Loaded %d vehicles from: %s (%d ms)",vehicles_loaded,filename,GetTickCount() - time);
	return vehicles_loaded;
}