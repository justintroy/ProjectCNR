AssignPlayerData(playerid)
{
	cache_get_value_int(0, "ID", Player[playerid][ID]);
	cache_get_value_int(0, "Tutorial", Player[playerid][Tutorial]);
	cache_get_value_int(0, "Class", Player[playerid][Class]);
	cache_get_value_int(0, "Skin", Player[playerid][Skin]);
	cache_get_value_int(0, "AdminLevel", Player[playerid][pAdmin]);
	cache_get_value_name(0, "IPAddress", Player[playerid][IP]);
	cache_get_value_int(0, "PlayTime", Player[playerid][PlayTime]);
	/*cache_get_value_int(0, "kills", Player[playerid][Kills]);
	cache_get_value_int(0, "deaths", Player[playerid][Deaths]);

	cache_get_value_float(0, "x", Player[playerid][X_Pos]);
	cache_get_value_float(0, "y", Player[playerid][Y_Pos]);
	cache_get_value_float(0, "z", Player[playerid][Z_Pos]);
	cache_get_value_float(0, "angle", Player[playerid][A_Pos]);
	cache_get_value_int(0, "interior", Player[playerid][Interior]);*/
	return 1;
}

AssignPlayerInventory(playerid);
