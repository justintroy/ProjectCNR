#define BIZ_VIRTUAL_WORLD	100
#define MAX_BIZ				1000
new Iterator:Businesses<MAX_BIZ>;

enum _biz
{
	BizID,
	BizOwner,
	BizPrice,
	BizInterior,
	Float:BizInteriorLocation[3],
	BizTitle[56],
	BizLocation[28],
	BizMoney,
	BizPickup[2],
	Text3D:BizLabel,
	Float:BizPosition[3],
	bool:BizOwned,
	BizRobCP,
	Text3D:BizRobText,
	BizLastRob,
	bool:BizBeingRobbed,
	BizIcon
}
new Biz[MAX_BIZ][_biz];

FUNCTION:LoadBiz()
{
	new Cache:BizCache, time = GetTickCount();
	BizCache = mysql_query(connection, "SELECT * FROM `business`", true);
	new count = cache_num_rows(), tempString[56];
	if(count > 0)
	{
		for(new z = 0; z < count; z++)
		{
			new i = Iter_Free(Businesses), msg[256];
			cache_get_value_int(z, "id", Biz[i][BizID]);
			cache_get_value_bool(z, "owned", Biz[i][BizOwned]);
			Biz[i][BizOwned] = (Biz[i][BizOwned] == 1) ? true : false;
			cache_get_value_int(z, "owner", Biz[i][BizOwner]);
			cache_get_value_float(z, "x", Biz[i][BizPosition][0]);
			cache_get_value_float(z, "y", Biz[i][BizPosition][1]);
			cache_get_value_float(z, "z", Biz[i][BizPosition][2]);
			cache_get_value_int(z, "price", Biz[i][BizPrice]);
			cache_get_value_int(z, "intid", Biz[i][BizInterior]);
			cache_get_value_int(z, "money", Biz[i][BizMoney]);
			cache_get_value_float(z, "intx", Biz[i][BizInteriorLocation][0]);
			cache_get_value_float(z, "inty", Biz[i][BizInteriorLocation][1]);
			cache_get_value_float(z, "intz", Biz[i][BizInteriorLocation][2]);
			cache_get_value(z, "title", tempString);
			format(Biz[i][BizTitle], 56, "%s", tempString);
			format(Biz[i][BizLocation], 28, "%s", GetXY2DZone(Biz[i][BizPosition][0], Biz[i][BizPosition][1]));
			Biz[i][BizPickup][0] = CreateDynamicPickup(1274, 1, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2], 0, 0);
			Biz[i][BizPickup][1] = CreateDynamicPickup(1318, 1, Biz[i][BizInteriorLocation][0], Biz[i][BizInteriorLocation][1], Biz[i][BizInteriorLocation][2], Biz[i][BizID] + BIZ_VIRTUAL_WORLD, Biz[i][BizInterior]);
			Biz[i][BizRobCP] = CreateDynamicCP(-22.0518,-138.6259,1003.5469, 1.0, Biz[i][BizID] + BIZ_VIRTUAL_WORLD, Biz[i][BizInterior]);
			Biz[i][BizRobText] = CreateDynamic3DTextLabel(COL_LIGHTBLUE"BUSINESS ROBBERY\n{F9DC5C}Press "COL_YELLOW"ALT"COL_YELLOW" to start robbery.\n"COL_LIGHTBLUE"SHOP: \n {F9DC5C}Type /shop to buy items.", -1, -22.0518,-138.6259,1003.5469 + 0.2, 5.0, .worldid = Biz[i][BizID] + BIZ_VIRTUAL_WORLD, .interiorid = Biz[i][BizInterior]);
			Biz[i][BizLastRob] = 0;
			Biz[i][BizBeingRobbed] = false;
			if(!Biz[i][BizOwned])
			{
				format(msg, sizeof(msg), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"Business ID : %d\nLocation : %s\nPrice : $%s\n"COL_YELLOW"/buybiz %d", Biz[i][BizID], Biz[i][BizLocation], FormatNumber(Biz[i][BizPrice]), Biz[i][BizID]);
				Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
				Biz[i][BizIcon] = CreateDynamicMapIcon(Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2], 17, -1, 0, 0, -1, 50.0);
			}
			else
			{
				new msg2[512];
				format(msg2, sizeof(msg2), COLOR_VIOLET"[BUSINESS]\n"COL_YELLOW"Biz ID : %d\nLocation : %s\nOwner : %s\nTitle : %s\n"COL_YELLOW"Press ALT to enter", Biz[i][BizID], Biz[i][BizLocation], GetPlayerNameFromId(Biz[i][BizOwner]), Biz[i][BizTitle]);
				Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
				Biz[i][BizIcon] = CreateDynamicMapIcon(Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2], 17, -1, 0, 0, -1, 50.0);
			}

			Iter_Add(Businesses, i);
			
		}
	}
	printf("%d Business(es) Succesfully Loaded!!! (%d ms)", count, (GetTickCount() - time));
	cache_delete(BizCache);
}

COMMAND:createbiz(playerid, params[])
{
	new price;
	if(sscanf(params, "d", price))
	{
		SendUsageMessage(playerid, "createbiz <business price>");
	}
	else
	{
		new i = Iter_Free(Businesses), Float:x, Float:y, Float:z, msg[256], query[512];
		GetPlayerPos(playerid, x, y, z);
		mysql_format(connection, query, sizeof(query), "INSERT INTO `business`(`price`, `x`, `y`, `z`) VALUES(%d, '%f', '%f', '%f')", price, x, y, z);
		mysql_tquery(connection, query);
		Biz[i][BizPosition][0] = x;
		Biz[i][BizPosition][1] = y;
		Biz[i][BizPosition][2] = z;
		Biz[i][BizInterior] = 16;
		Biz[i][BizInteriorLocation][0] = -25.840473;
		Biz[i][BizInteriorLocation][1] = -141.193313;
		Biz[i][BizInteriorLocation][2] = 1003.54687;
		format(Biz[i][BizLocation], 28, "%s", GetXY2DZone(x, y));
		Biz[i][BizID] = cache_insert_id();
		Biz[i][BizOwned] = false;
		Biz[i][BizOwner] = -1;
		Biz[i][BizPickup][0] = CreateDynamicPickup(1274, 1, x, y, z, 0, 0);
		Biz[i][BizPickup][1] = CreateDynamicPickup(1318, 1, Biz[i][BizInteriorLocation][0], Biz[i][BizInteriorLocation][1], Biz[i][BizInteriorLocation][2], Biz[i][BizID] + BIZ_VIRTUAL_WORLD, Biz[i][BizInterior]);
		Biz[i][BizPrice] = price;
		Biz[i][BizRobCP] = CreateDynamicCP(-22.0518,-138.6259,1003.5469, 1.0, Biz[i][BizID] + BIZ_VIRTUAL_WORLD, Biz[i][BizInterior]);
		Biz[i][BizRobText] = CreateDynamic3DTextLabel(COL_LIGHTBLUE"BUSINESS ROBBERY\n{F9DC5C}Press "COL_YELLOW"ALT"COL_YELLOW" to start robbery\n"COL_LIGHTBLUE"SHOP: \n {F9DC5C}Type /shop to buy items.", -1, -22.0518,-138.6259,1003.5469 + 0.2, 5.0, .worldid = Biz[i][BizID] + BIZ_VIRTUAL_WORLD, .interiorid = Biz[i][BizInterior]);
		format(Biz[i][BizTitle], 28, "MNL:CnR");
		format(msg, sizeof(msg), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"Business ID : %d\nLocation : %s\nPrice : $%s\n"COL_YELLOW"/buybiz %d", Biz[i][BizID], Biz[i][BizLocation], FormatNumber(Biz[i][BizPrice]), Biz[i][BizID]);
		Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, x, y, z + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		Biz[i][BizIcon] = CreateDynamicMapIcon(x, y, z, 17, -1, 0, 0, -1, 50.0);
		Biz[i][BizMoney] = 0;
		Biz[i][BizLastRob] = 0;
		Biz[i][BizBeingRobbed] = false;
		Iter_Add(Businesses, i);
	}
	return 1;
}

COMMAND:buybiz(playerid, params[])
{
	new id, bool:found = false;
	if(sscanf(params, "d", id))
	{
		SendUsageMessage(playerid, "buybiz <biz id>");
	}
	else
	{
		new limit = MAX_PLAYER_BIZ + Player[playerid][VIPLevel], total = 0;
		foreach(new i : Businesses)
		{
			if(Biz[i][BizOwner] == Player[playerid][ID])
				total++;
		}
		if(total >= limit)
		{
			SendErrorMessage(playerid, "You've too many biz, sell a biz first");
			return 1;
		}
		foreach(new i : Businesses)
		{
			if(Biz[i][BizID] == id)
			{
				if(!Biz[i][BizOwned])
				{
					if(GetDistanceToPoint(playerid, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2]) < 2.0)
					{
						if(GetPlayerMoney(playerid) >= Biz[i][BizPrice])
						{
							new msg2[512], msg[128], query[128], alog[128];
							mysql_format(connection, query, sizeof(query), "UPDATE `business` SET `owner` = %d, `owned` = 1 WHERE `id` = %d", Player[playerid][ID], Biz[i][BizID]);
							mysql_tquery(connection, query);
							Biz[i][BizOwned] = true;
							Biz[i][BizOwner] = Player[playerid][ID];
							Biz[i][BizLastRob] = 0;
							if(IsValidDynamic3DTextLabel(Biz[i][BizLabel]))
							{
								format(msg2, sizeof(msg2), COLOR_VIOLET"[BUSINESS]\n"COL_YELLOW"Biz ID : %d\nLocation : %s\nOwner : %s\nTitle : %s\n"COL_YELLOW"Press ALT to enter", Biz[i][BizID], Biz[i][BizLocation], Player[playerid][Name], Biz[i][BizTitle]);
								UpdateDynamic3DTextLabelText(Biz[i][BizLabel], 0xFFFFFFFF, msg2);
							}
							else
							{
								format(msg2, sizeof(msg2), COLOR_VIOLET"[BUSINESS]\n"COL_YELLOW"Biz ID : %d\nLocation : %s\nOwner : %s\nTitle : %s\n"COL_YELLOW"Press ALT to enter", Biz[i][BizID], Biz[i][BizLocation], Player[playerid][Name], Biz[i][BizTitle]);
								Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
							}
							GivePlayerMoney(playerid, - Biz[i][BizPrice]);
							format(msg, sizeof(msg), "~b~~h~Succesfully buy biz for ~r~~r~$%s", FormatNumber(Biz[i][BizPrice]));
							GameTextForPlayer(playerid, msg, 3000, 3);
							format(msg, sizeof(msg), "Succesfully buy business store for $%s", FormatNumber(Biz[i][BizPrice]));
							SCM(playerid, msg, "BUSINESS");
							PlayerPlaySound(playerid, 1097, 0.0, 0.0, 0.0);
							format(alog, sizeof(alog), "%s buy biz ID : %d", pName(playerid), Biz[i][BizID]);
							ActionLog(alog);
						}
						else
							GameTextForPlayer(playerid, "~r~~r~Not Enough Money To Buy This Business Store!!!", 3000, 3);
					}
					else
						GameTextForPlayer(playerid, "~b~~b~You Must Near Biz Pickup To Buy Business Store!!!", 3000, 3);
				}
				else
					GameTextForPlayer(playerid, "~r~~r~This Store Is Not For Sale!!!", 3000, 3);
				found = true;
				break;
			}
		}
		if(!found)
			SendErrorMessage(playerid, "Invalid biz ID");
	}
	return 1;
}

COMMAND:gotobiz(playerid, params[])
{
	new i;
	if(sscanf(params, "d", i))
	{
		SendUsageMessage(playerid, "gotobiz <business id>");
	}
	else
	{
		new z = -1;
		foreach(new x : Businesses)
		{
			if(Biz[x][BizID] == i)
			{
				z = x;
				break;
			}
		}
		if(Iter_Contains(Businesses, z))
		{
			SetPlayerPos(playerid, Biz[z][BizPosition][0], Biz[z][BizPosition][1], Biz[z][BizPosition][2]);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
		else
			SendErrorMessage(playerid, "Invalid business ID");
	}
	return 1;
}

COMMAND:reloadbiz(playerid, params[])
{
	foreach(new i : Businesses)
	{
		if(IsValidDynamicPickup(Biz[i][BizPickup][0]))
			DestroyDynamicPickup(Biz[i][BizPickup][0]);
		if(IsValidDynamicPickup(Biz[i][BizPickup][1]))
			DestroyDynamicPickup(Biz[i][BizPickup][1]);
		if(IsValidDynamic3DTextLabel(Biz[i][BizLabel]))
			DestroyDynamic3DTextLabel(Biz[i][BizLabel]);
		if(IsValidDynamicMapIcon(Biz[i][BizIcon]))
			DestroyDynamicMapIcon(Biz[i][BizIcon]);
	}
	Iter_Clear(Businesses);
	LoadBiz();
	SCM(playerid, "Business system has been reloaded", "BUSINESS");
	return 1;
}

COMMAND:storemenu(playerid, params[])
{
	if(GetPlayerInterior(playerid) != 0)
	{
		new z = GetPlayerVirtualWorld(playerid) - BIZ_VIRTUAL_WORLD, i = -1;
		foreach(new x : Businesses)
		{
			if(Biz[x][BizID] == z)
			{
				i = x;
				break;
			}
		}
		if(i != -1)
		{
			if(Biz[i][BizOwner] == Player[playerid][ID] && Biz[i][BizOwned])
			{
				new msg2[512];
				Player[playerid][BizMenuID] = i;
				format(msg2, sizeof(msg2), COL_YELLOW"Biz Title : %s\n", Biz[i][BizTitle]);
				format(msg2, sizeof(msg2), "%sBiz Money : $%s\n", msg2, FormatNumber(Biz[i][BizMoney]));
				format(msg2, sizeof(msg2), "%s"COLOR_RED"Sell This Store", msg2);
				ShowPlayerDialog(playerid, DIALOG_BIZ, DIALOG_STYLE_LIST, "Store Menu", msg2, "Choose", "Close");
			}
			else
				GameTextForPlayer(playerid, "~r~~r~You're not owner of this store!!!", 3000, 3);
		}
		else
			GameTextForPlayer(playerid, "~r~~r~You're not inside any business store!!!", 3000, 3);
	}
	else
		GameTextForPlayer(playerid, "~r~~r~You're not inside any business store!!!", 3000, 3);
	return 1;
}

COMMAND:setbizowner(playerid, params[])
{
	new z, msg2[512], msg[128], otherID;
	if(sscanf(params, "du", z, otherID))
	{
		Usage(playerid, "setbizowner <biz id> <playerid>");
	}
	else
	{
		new i = -1;
		foreach(new x : Businesses)
		{
			if(Biz[x][BizID] == z)
			{
				i = x;
				break;
			}
		}
		if(Iter_Contains(Businesses, i))
		{
			if(IsPlayerConnected(otherID))
			{
				new query[128], alog[128];
				mysql_format(connection, query, sizeof(query), "UPDATE `business` SET `owner` = %d, `owned` = 1 WHERE `id` = %d", Player[otherID][ID], Biz[i][BizID]);
				mysql_tquery(connection, query);
				Biz[i][BizOwned] = true;
				Biz[i][BizOwner] = Player[otherID][ID];
				if(IsValidDynamic3DTextLabel(Biz[i][BizLabel]))
				{
					format(msg2, sizeof(msg2), COLOR_VIOLET"[BUSINESS]\n"COL_YELLOW"Biz ID : %d\nLocation : %s\nOwner : %s\nTitle : %s\n"COL_YELLOW"Press ALT to enter", Biz[i][BizID], Biz[i][BizLocation], Player[otherID][Name], Biz[i][BizTitle]);
					UpdateDynamic3DTextLabelText(Biz[i][BizLabel], 0xFFFFFFFF, msg2);
				}
				else
				{
					format(msg2, sizeof(msg2), COLOR_VIOLET"[BUSINESS]\n"COL_YELLOW"Biz ID : %d\nLocation : %s\nOwner : %s\nTitle : %s\n"COL_YELLOW"Press ALT to enter", Biz[i][BizID], Biz[i][BizLocation], Player[otherID][Name], Biz[i][BizTitle]);
					Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
				}
				PlayerPlaySound(otherID, 1097, 0.0, 0.0, 0.0);
				format(msg, sizeof(msg), "Succesfully give business store to "COL_YELLOW"%s", pName(otherID));
				SCM(playerid, msg, "BUSINESS");
				SCM(otherID, "An administrator has given you a business store, congratulation!", "REWARD");
				format(alog, sizeof(alog), "%s set %s as owner of biz id : %d", pName(playerid), pName(otherID), Biz[i][BizID]);
				ActionLog(alog);
			}
			else
				SEM(playerid, "That player is not connected", "ERROR");
		}
		else
			SEM(playerid, "Invalid biz ID", "BUSINESS");
	}
	return 1;
}

COMMAND:deletebiz(playerid, params[])
{
	new i;
	if(sscanf(params, "d", i))
	{
		Usage(playerid, "deletebiz <business id>");
	}
	else
	{
		new z = -1;
		foreach(new x : Businesses)
		{
			if(Biz[x][BizID] == i)
			{
				z = x;
				break;
			}
		}
		if(Iter_Contains(Businesses, z))
		{
			new msg[128], query[128], alog[128];
			mysql_format(connection, query, sizeof(query), "DELETE FROM `business` WHERE `id` = %d", Biz[z][BizID]);
			mysql_tquery(connection, query);
			if(IsValidDynamicPickup(Biz[z][BizPickup][0]))
				DestroyDynamicPickup(Biz[z][BizPickup][0]);
			if(IsValidDynamicPickup(Biz[z][BizPickup][1]))
				DestroyDynamicPickup(Biz[z][BizPickup][1]);
			if(IsValidDynamic3DTextLabel(Biz[z][BizLabel]))
				DestroyDynamic3DTextLabel(Biz[z][BizLabel]);
			if(IsValidDynamicMapIcon(Biz[i][BizIcon]))
				DestroyDynamicMapIcon(Biz[i][BizIcon]);
			Biz[z][BizOwned] = false;
			Biz[z][BizOwner] = -1;
			Biz[z][BizPrice] = 99999999;
			format(msg, sizeof(msg), "Succesfully removed biz id : "COL_YELLOW"%d", i);
			SCM(playerid, msg, "BUSINESS");
			Iter_Remove(Houses, z);
			format(alog, sizeof(alog), "%s deleted biz id : %d", pName(playerid), Biz[i][BizID]);
			ActionLog(alog);
		}
		else
			SEM(playerid, "Invalid biz ID", "BUSINESS");
	}
	return 1;
}

YCMD:removebizowner(playerid, params[], help)
{
	new id, bool:found = false, msg2[512], msg[128];
	if(sscanf(params, "d", id))
	{
		Usage(playerid, "removebizowner <business id>");
	}
	else
	{
		foreach(new i : Businesses)
		{
			if(Biz[i][BizID] == id)
			{
				if(Biz[i][BizOwned])
				{
					new query[128], alog[128];
					mysql_format(connection, query, sizeof(query), "UPDATE `business` SET `owner` = -1, `title` = 'LSF-CNR Business', `money` = 0, `owned` = 0 WHERE `id` = %d", Biz[i][BizID]);
					mysql_tquery(connection, query);
					format(Biz[i][BizTitle], 28, "MNLCNR Business");
					Biz[i][BizOwner] = -1;
					Biz[i][BizOwned] = false;
					if(IsValidDynamic3DTextLabel(Biz[i][BizLabel]))
					{
						format(msg2, sizeof(msg2), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"Business ID : %d\nLocation : %s\nPrice : $%s\n"COL_YELLOW"/buybiz %d", Biz[i][BizID], Biz[i][BizLocation], FormatNumber(Biz[i][BizPrice]), Biz[i][BizID]);
						UpdateDynamic3DTextLabelText(Biz[i][BizLabel], 0xFFFFFFFF, msg2);
					}
					else
					{
						format(msg2, sizeof(msg2), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"Business ID : %d\nLocation : %s\nPrice : $%s\n"COL_YELLOW"/buybiz %d", Biz[i][BizID], Biz[i][BizLocation], FormatNumber(Biz[i][BizPrice]), Biz[i][BizID]);
						Biz[i][BizLabel] = CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
					}
					foreach(new x : Player)
					{
						if(GetPlayerInterior(x) == Biz[i][BizID])
						{
							if(GetPlayerVirtualWorld(x) == (Biz[i][BizID] + BIZ_VIRTUAL_WORLD))
							{
								SetPlayerPos(x, Biz[i][BizPosition][0], Biz[i][BizPosition][1], Biz[i][BizPosition][2]);
								SetPlayerInterior(x, 0);
								SetPlayerVirtualWorld(x, 0);
							}
						}
					}
					format(msg, sizeof(msg), "~b~~h~Succesfully remove owner of biz id %d", id);
					GameTextForPlayer(playerid, msg, 3000, 3);
					format(alog, sizeof(alog), "%s removed owner of biz id : %d", pName(playerid), Biz[i][BizID]);
					ActionLog(alog);
				}
				else
					GameTextForPlayer(playerid, "~r~~r~This biz is currently unowned!!!", 3000, 3);
				found = true;
			}
		}
		if(!found)
			GameTextForPlayer(playerid, "~r~~r~Invalid biz ID!!!", 3000, 3);
	}
	return 1;
}

COMMAND:mybiz(playerid, params[])
{
	new bool:found = false, msg2[512];
	format(msg2, sizeof(msg2), "Biz ID\tTitle\tValue\n");
	foreach(new i : Businesses)
	{
		if(Biz[i][BizOwned])
		{
			if(Biz[i][BizOwner] == Player[playerid][ID])
			{
				format(msg2, sizeof(msg2), "%s%d\t%s\t$%s\n", msg2, Biz[i][BizID], Biz[i][BizTitle], FormatNumber(Biz[i][BizMoney]));
				found = true;
			}
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_MYBIZ, DIALOG_STYLE_TABLIST_HEADERS, "My Business Stores", msg2, "Choose", "Close");
	else
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Oops...", "You currently don't own any business store", "Close", "");
	return 1;
}

COMMAND:bizforsale(playerid, params[])
{
	new msg2[512], bool:found = false;
	format(msg2, sizeof(msg2), "Business Store ID\tPrice\tLocation\n");
	foreach(new i : Houses)
	{
		if(!Biz[i][BizOwned])
		{
			format(msg2, sizeof(msg2), "%s%d\t$%s\t%s\n", msg2, Biz[i][BizID], FormatNumber(Biz[i][BizPrice]), Biz[i][BizLocation]);
			found = true;
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_BUSINESSESFORSALE, DIALOG_STYLE_TABLIST_HEADERS, "Businesses For Sale", msg2, "Locate", "Close");
	else
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Oops...", "There's no any unowned business store yet, you can ask administrator to make it", "Close", "");
	return 1;
}
