#include <YSI_Coding\y_hooks>

#define BIZ_VIRTUAL_WORLD	100
#define MAX_BIZ				1000
new Iterator:Businesses<MAX_BIZ>;


enum _biz
{
	BizID,
	BizType,
	Float:BizPos[3],
	BizPrice,
	BizInterior,
	Float:BizIntLoc[3], 
	BizTitle[56],
	BizMoney, //unused
	BizPickup[2],
	Text3D:BizLabel[2],
	bool:BizOwned,
	BizOwner,
	BizIcon,

	//biz cash register
	BizRegObj,
	bool:BizBeingRobbed, //unused
	Text3D:BizRegLabel,
	Float:BizRegLoc[4],
	BizLastRob, //unused

	//biz shop and items
	BizShopCP[2], // 1 - 24/7, 2 - Ammunation, 3 - Restaurant
	Text3D:BizShopLabel,
	BizFoodSupply
}
new Biz[MAX_BIZ][_biz];

new CurrentBizID;

LoadBiz()
{
	new Cache:result;
	new rows, tempid;
	result = mysql_query(Database, "SELECT * FROM `business`");
	if(cache_get_row_count(rows))
	{
		for(new z = 0; z < rows && z < MAX_BIZ; z++)
		{
			
			cache_set_active(result);
			cache_get_value_int(z, "ID", tempid);
			Biz[tempid][BizID] = CurrentBizID = tempid;
			cache_get_value_float(z, "x", Biz[tempid][BizPos][0]);
			cache_get_value_float(z, "y", Biz[tempid][BizPos][1]);
			cache_get_value_float(z, "z", Biz[tempid][BizPos][2]);
			cache_get_value_int(z, "type", Biz[tempid][BizType]);
			cache_get_value_int(z, "price", Biz[tempid][BizPrice]);
			cache_get_value_bool(z, "owned", Biz[tempid][BizOwned]);
			cache_get_value_int(z, "owner", Biz[tempid][BizOwner]);
			

			GenerateBizIntCoords(Biz[tempid][BizType], Biz[tempid][BizIntLoc][0], Biz[tempid][BizIntLoc][1], Biz[tempid][BizIntLoc][2], Biz[tempid][BizInterior]);
			Biz[tempid][BizPickup][0]		= CreateDynamicPickup(1274, 1, Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2], 0, 0);
			Biz[tempid][BizPickup][1] 		= CreateDynamicPickup(1318, 1, Biz[tempid][BizIntLoc][0], Biz[tempid][BizIntLoc][1], Biz[tempid][BizIntLoc][2], Biz[tempid][BizID] + BIZ_VIRTUAL_WORLD, Biz[tempid][BizInterior]);

			GenerateBizRegister(tempid,Biz[tempid][BizType], Biz[tempid][BizRegLoc][0], Biz[tempid][BizRegLoc][1], Biz[tempid][BizRegLoc][2], Biz[tempid][BizRegLoc][3]);
			GenerateBizOwnershipLabel(tempid, Biz[tempid][BizOwned]);
			GenerateBizShop(tempid, Biz[tempid][BizType]);
			
			printf("ID: %d LOADED Z: %d ROW: %d BIZID: %d X: %f Y: %f Z: %f", tempid, z, rows, Biz[tempid][BizID], Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2]);
			Iter_Add(Businesses, tempid);
		}
	}
	printf("[MNL:CNR] %i businesses loaded (max ID: %i)", rows, CurrentBizID);
	cache_delete(result);
	return 1;
}

GenerateBizRegister(tempid, type, &Float: X, &Float: Y, &Float: Z, &Float:A)
{
	switch(type)
	{
		case 1:
		{
			new msg[256];
			X = -10.670728;
			Y = -179.161773;
			Z = 1003.696350;
			A = -178.700210;

			format(msg, sizeof(msg), "{F9DC5C}Shoot or Press {16E0BD}~k~~CONVERSATION_NO~ {F9DC5C}to rob.\n{16E0BD}Robbable");
			Biz[tempid][BizRegLabel] = CreateDynamic3DTextLabel(msg, 0xF1C40FFF, Biz[tempid][BizRegLoc][0], Biz[tempid][BizRegLoc][1], Biz[tempid][BizRegLoc][2] + 0.25, 5.0, .testlos = 1);
			Biz[tempid][BizRegObj] = CreateDynamicObject(2941, Biz[tempid][BizRegLoc][0], Biz[tempid][BizRegLoc][1], Biz[tempid][BizRegLoc][2], 0.0, 0.0, Biz[tempid][BizRegLoc][3], Biz[tempid][BizID] + BIZ_VIRTUAL_WORLD, Biz[tempid][BizInterior]);
		}
	}
	return 1;
}

GenerateBizShop(tempid, type)
{
	switch(type)
	{
		case 1:
		{
			Biz[tempid][BizShopCP][0] = CreateDynamicCP(-10.6053,-177.6121,1003.5469, 1.0, Biz[tempid][BizID] + BIZ_VIRTUAL_WORLD, Biz[tempid][BizInterior]);
		}
	}
}

GenerateBizIntCoords(type, &Float: X, &Float: Y, &Float: Z, &interior) 
{
	switch(type)
	{
		case 1:
		{
			X = -25.9123;
			Y = -187.9238;
			Z = 1003.5469;
			interior = 17;
		}
	}
	return 1;
}

GenerateBizOwnershipLabel(tempid, owncheck)
{
	new msg[256], msg2[256];
	if(!owncheck)
	{
		format(msg, sizeof(msg), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"ID : %d\nPrice : $%s\n"COL_LIGHTBLUE"/buybiz %d", 
		Biz[tempid][BizID], convertNumber(Biz[tempid][BizPrice]), Biz[tempid][BizID]);

		format(msg2, sizeof(msg2), COL_YELLOW"%d\nThank you for visiting\n"COL_LIGHTBLUE"%s's %s\n\n"COL_YELLOW"Please come again!\n/exit", 
		Biz[tempid][BizID], GetPlayerNameFromId(Biz[tempid][BizOwner]), Biz[tempid][BizTitle]);
		Biz[tempid][BizLabel][0]		= CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		Biz[tempid][BizLabel][1]		= CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[tempid][BizIntLoc][0], Biz[tempid][BizIntLoc][1], Biz[tempid][BizIntLoc][2] + 0.3, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Biz[tempid][BizID] + BIZ_VIRTUAL_WORLD, Biz[tempid][BizInterior]);
		Biz[tempid][BizIcon]			= CreateDynamicMapIcon(Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2], 17, -1, 0, 0, -1, 50.0);
	}
	else
	{
		format(msg, sizeof(msg), COL_LIGHTBLUE"[BUSINESS]\n"COL_YELLOW"ID : %d\n"COL_LIGHTBLUE"%s's %s", 
		Biz[tempid][BizID], GetPlayerNameFromId(Biz[tempid][BizOwner]), Biz[tempid][BizTitle]);

		format(msg2, sizeof(msg2), COL_YELLOW"%d\nThank you for visiting\n"COL_LIGHTBLUE"%s's %s\n\n"COL_YELLOW"Please come again!\n/exit", 
		Biz[tempid][BizID], GetPlayerNameFromId(Biz[tempid][BizOwner]), Biz[tempid][BizTitle]);
		Biz[tempid][BizLabel][0]		= CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2] + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);
		Biz[tempid][BizLabel][1]		= CreateDynamic3DTextLabel(msg2, 0xFFFFFFFF, Biz[tempid][BizIntLoc][0], Biz[tempid][BizIntLoc][1], Biz[tempid][BizIntLoc][2] + 0.3, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Biz[tempid][BizID] + BIZ_VIRTUAL_WORLD, Biz[tempid][BizInterior]);
		Biz[tempid][BizIcon]			= CreateDynamicMapIcon(Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2], 17, -1, 0, 0, -1, 50.0);
	}
	return 1;
}

YCMD:createbiz(playerid, params[], help) 
{
	new Float:x, Float:y, Float:z, price, type;
	if(sscanf(params, "dd", price, type)) return SendUsageMessage(playerid, "createbiz <price> <type>");
	if(type < 1 || type > 6) return SendUsageMessage(playerid, "Biz Types: 1 - 24/7");
	if(price < 1000 || price > 100000000) return SendUsageMessage(playerid, "Price cant go lower than $1,000 nor higher than 100mil");

	GetPlayerPos(playerid, x, y, z);
	new query[250];
	mysql_format(Database, query, sizeof(query), 
		"INSERT INTO `business` \
		(`x`, `y`, `z`, `type`, `price`) \
		VALUES ('%f', '%f', '%f', '%d', '%d')", 
		x, y, z, type, price);

	mysql_tquery(Database, query, "CreateBizCallBack", "ifffii", playerid, x, y, z, type, price);
	return 1;
}

forward CreateBizCallBack(playerid, Float:x, Float:y, Float:z, type, price);
public CreateBizCallBack(playerid, Float:x, Float:y, Float:z, type, price)
{
	new msg[256];
	CurrentBizID = cache_insert_id();
	Biz[CurrentBizID][BizID] 						= CurrentBizID;

	GenerateBizIntCoords(type, Biz[CurrentBizID][BizIntLoc][0], Biz[CurrentBizID][BizIntLoc][1], Biz[CurrentBizID][BizIntLoc][2], Biz[CurrentBizID][BizInterior]);

	Biz[CurrentBizID][BizType]						= type;
	Biz[CurrentBizID][BizOwned]						= false;
	Biz[CurrentBizID][BizOwner]						= -1;
	Biz[CurrentBizID][BizPrice]						= price;
	Biz[CurrentBizID][BizPos][0] 					= x;
	Biz[CurrentBizID][BizPos][1] 					= y;
	Biz[CurrentBizID][BizPos][2] 					= z;
	Biz[CurrentBizID][BizPickup][0]					= CreateDynamicPickup(1274, 1, x, y, z, 0, 0);
	Biz[CurrentBizID][BizPickup][1] 				= CreateDynamicPickup(1318, 1, Biz[CurrentBizID][BizIntLoc][0], Biz[CurrentBizID][BizIntLoc][1], Biz[CurrentBizID][BizIntLoc][2], Biz[CurrentBizID][BizID] + BIZ_VIRTUAL_WORLD, Biz[CurrentBizID][BizInterior]);

	
	format(msg, sizeof(msg), COL_LIGHTBLUE"[BUSINESS FOR SALE]\n"COL_YELLOW"Business ID : %d\nPrice : $%s\n"COL_LIGHTBLUE"/buybiz %d", 
		Biz[CurrentBizID][BizID], convertNumber(Biz[CurrentBizID][BizPrice]), Biz[CurrentBizID][BizID]);
	Biz[CurrentBizID][BizLabel] = CreateDynamic3DTextLabel(msg, 0xFFFFFFFF, x, y, z + 0.3, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);


	new string[256];
	format(string, sizeof(string), "ID: %d TYPE: %d X: %f Y:%f Z:%f Interior: %d World: %d", 
		Biz[CurrentBizID][BizID], type, Biz[CurrentBizID][BizIntLoc][0], Biz[CurrentBizID][BizIntLoc][1], Biz[CurrentBizID][BizIntLoc][2], Biz[CurrentBizID][BizInterior], Biz[CurrentBizID][BizID] + BIZ_VIRTUAL_WORLD);
	SendClientMessage(playerid, -1, string);

	Iter_Add(Businesses, CurrentBizID);
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	new tick = gettime() - Player[playerid][LastCPEntered];
	if(!IsPlayerInAnyVehicle(playerid) && tick > 5)
	{
		foreach(new i : Businesses)
		{
			if(checkpointid == Biz[i][BizShopCP][0])
			{
				new tempid = Biz[i][BizID], titlemsg[128], listmsg[512];
				Player[playerid][LastCPEntered] = gettime();

				format(titlemsg, sizeof(titlemsg), "Welcome to %s's %s! Shop ID: %d", GetPlayerNameFromId(Biz[tempid][BizOwner]), Biz[tempid][BizTitle], Biz[i][BizID]);
				/*if(Biz[tempid][BizFoodSupply] >= 1)
				{
					
				}*/
				format(listmsg, sizeof(listmsg), "Cola P50\nBurger P100\nMedkit P500");

				inline ShowShopDialog(pid, dialogid, response, listitem, string:inputtext[])
			    {
			        #pragma unused pid, dialogid, inputtext
			        if(response)
			        {
			        	switch(listitem)
			        	{
			        		case 0:
			        		{
			        			if((!IsPlayerHasEmptySlot(playerid)) && !IsPlayerHasItem(playerid, ITEM_COLA)) return SendErrorMessage(playerid, "Your inventory is full! You can buy additional slots at businesses.");
			        			GivePlayerItem(playerid, ITEM_COLA, 1);
			        			va_SendClientMessage(playerid, COLOR_BLUE, "[MNLCNR]:{F9DC5C} You bought %s for P50.", GetItemName(ITEM_COLA));
			        			Dialog_ShowCallback(playerid, using inline ShowShopDialog, DIALOG_STYLE_LIST, titlemsg, listmsg, "Buy", "Cancel");
			        		}
			        		case 1:
			        		{
			        			if((!IsPlayerHasEmptySlot(playerid)) && !IsPlayerHasItem(playerid, ITEM_BURGER)) return SendErrorMessage(playerid, "Your inventory is full! You can buy additional slots at businesses.");
			        			GivePlayerItem(playerid, ITEM_BURGER, 1);
			        			va_SendClientMessage(playerid, COLOR_BLUE, "[MNLCNR]:{F9DC5C} You bought %s for P100.", GetItemName(ITEM_BURGER));
			        			Dialog_ShowCallback(playerid, using inline ShowShopDialog, DIALOG_STYLE_LIST, titlemsg, listmsg, "Buy", "Cancel");
			        		}
			        		case 2:
			        		{
			        			if((!IsPlayerHasEmptySlot(playerid)) && !IsPlayerHasItem(playerid, ITEM_MEDKIT)) return SendErrorMessage(playerid, "Your inventory is full! You can buy additional slots at businesses.");
			        			GivePlayerItem(playerid, ITEM_MEDKIT, 1);
			        			va_SendClientMessage(playerid, COLOR_BLUE, "[MNLCNR]:{F9DC5C} You bought %s for P500.", GetItemName(ITEM_MEDKIT));
			        			Dialog_ShowCallback(playerid, using inline ShowShopDialog, DIALOG_STYLE_LIST, titlemsg, listmsg, "Buy", "Cancel");
			        		}
			        	}
			        }
			    }
			    Dialog_ShowCallback(playerid, using inline ShowShopDialog, DIALOG_STYLE_LIST, titlemsg, listmsg, "Buy", "Cancel");
				va_SendClientMessage(playerid, -1, "BizCPID: %d  ID: %d ", Biz[i][BizShopCP][0], i);
				return 1;
			}
		}
	}
	return 1;
}

OnPlayerEnter(playerid)
{
	foreach(new i : Businesses)
	{
		if(GetPlayerInterior(playerid) == 0)
		{
			if(GetDistanceToPoint(playerid, Biz[i][BizPos][0], Biz[i][BizPos][1], Biz[i][BizPos][2]) < 2.0)
			{
				LoadObject(playerid);
				SetPlayerPos(playerid, Biz[i][BizIntLoc][0], Biz[i][BizIntLoc][1], Biz[i][BizIntLoc][2]);
				SetPlayerInterior(playerid, Biz[i][BizInterior]);
				SetPlayerVirtualWorld(playerid, Biz[i][BizID] + BIZ_VIRTUAL_WORLD);
			}
		}
	}
	if(GetPlayerInterior(playerid) != 0)
	{
		new tempid = GetPlayerVirtualWorld(playerid);
		tempid -= 100;
		if(GetDistanceToPoint(playerid, Biz[tempid][BizIntLoc][0], Biz[tempid][BizIntLoc][1], Biz[tempid][BizIntLoc][2]) < 2.0)
		{
			LoadObject(playerid);
			SetPlayerPos(playerid, Biz[tempid][BizPos][0], Biz[tempid][BizPos][1], Biz[tempid][BizPos][2]);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}
}

convertNumber(value)
{
    // http://forum.sa-mp.com/showthread.ph...781#post843781
    new string[24];
    format(string, sizeof(string), "%d", value);
    for(new i = (strlen(string) - 3); i > (value < 0 ? 1 : 0) ; i -= 3)
    {
        strins(string[i], ",", 0);
    }
    return string;
}

