#define MAX_INVENTORYSLOT       10
#define MAX_ITEMS               4

#define ITEM_INVALID            0
#define ITEM_COLA               1
#define ITEM_MEDKIT             2
#define ITEM_BURGER             3

#define ITEM_NAME(%0,%1)         \
    ItemArray[PlayerInventory[(%0)][(%1)][InvItemType]][1]


enum E_INVENTORY
{
    InvItemType,
    InvItemAmount
}
new PlayerInventory[MAX_PLAYERS][MAX_INVENTORYSLOT][E_INVENTORY];

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        PlayerInventory[playerid][i][InvItemType] = 0;
        PlayerInventory[playerid][i][InvItemAmount] = 0;
    }
    return 1;
}

new ItemArray [MAX_ITEMS] [] =
{
    {1, "Empty"},
    {2, "Cola"},
    {3, "Medkit"},
    {4, "Burger"}
};

YCMD:giveitem(playerid, params[], help) 
{
    new targetid, itemid;
    if(sscanf(params, "ud", targetid, itemid)) return SendUsageMessage(playerid, "/giveitem [playername/playerid] [itemid]");
    if(itemid >= MAX_ITEMS || itemid < 1) return va_SendClientMessage(playerid, COLOR_BLUE, "[USAGE] {F9DC5C}items <1- %d>", MAX_ITEMS-1);
    if((!IsPlayerHasEmptySlot(playerid)) && !IsPlayerHasItem(playerid, itemid)) return SendErrorMessage(playerid, "Your inventory is full! You can buy additional slots at businesses.");
    va_SendClientMessage(playerid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C} You gave %s an %s.", GetName(targetid), GetItemName(itemid));
    va_SendClientMessage(targetid, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C} Admin %s gave you an %s.", GetName(playerid), GetItemName(itemid));
    GivePlayerItem(targetid, itemid, 1);
    return 1;
}

YCMD:inventorylist(playerid, params[], help) 
{
    new listmsg[254];

    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        format(listmsg, sizeof(listmsg), "[DEBUG] Slot: %d\t ITEMID: %d\t ITEM NAME: %s\t ITEM AMOUNT: %d",
            i,
            PlayerInventory[playerid][i][InvItemType],
            ITEM_NAME(playerid, i),
            PlayerInventory[playerid][i][InvItemAmount]
            );

        SendClientMessage(playerid, -1, listmsg);
    }
    return 1;
}

YCMD:inventory(playerid, params[], help) 
{
    new listmsg[1024], bool:found = false;

    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        if(PlayerInventory[playerid][i][InvItemType] == ITEM_INVALID) continue;

        format(listmsg, sizeof(listmsg), "%s%s \t x%d\n",
            listmsg,
            ITEM_NAME(playerid, i),
            PlayerInventory[playerid][i][InvItemAmount]
            );

        found = true;
    }

    inline ShowInventoryDialog(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, inputtext
        if(response)
        {
            if(PlayerInventory[playerid][listitem][InvItemType] != 0)
            {
                va_SendClientMessage(playerid, COLOR_BLUE, "[MNLCNR]:{F9DC5C} You used %s.", GetItemName(PlayerInventory[playerid][listitem][InvItemType]));
                RemovePlayerItem(playerid, PlayerInventory[playerid][listitem][InvItemType], 1);
            }
            else SendErrorMessage(playerid, "You dont have that shit!");
        }
    }
    if(found)
        Dialog_ShowCallback(playerid, using inline ShowInventoryDialog, DIALOG_STYLE_LIST, "Inventory", listmsg, "Use", "Cancel");
    else
        SendErrorMessage(playerid, "Your inventory is empty. You can buy items in businesses.");
    return 1;
}

GivePlayerItem(playerid, itemid, amount)
{
    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        if(PlayerInventory[playerid][i][InvItemType] == ITEM_INVALID && PlayerInventory[playerid][i][InvItemType] != itemid)
        {
            PlayerInventory[playerid][i][InvItemType] = itemid;
            PlayerInventory[playerid][i][InvItemAmount] = amount;
            AddItemToDB(playerid, itemid, amount);
            break;
        }
        else if(PlayerInventory[playerid][i][InvItemType] == itemid)
        { 
            PlayerInventory[playerid][i][InvItemAmount] += amount;
            UpdateItemAmountToDB(playerid, itemid, PlayerInventory[playerid][i][InvItemAmount]);
            break;
        }
    }
}

RemovePlayerItem(playerid, itemid, amount)
{
    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        if(PlayerInventory[playerid][i][InvItemType] == itemid)
        {
            PlayerInventory[playerid][i][InvItemAmount] -= amount;
            if(PlayerInventory[playerid][i][InvItemAmount] == 0)
            {
                PlayerInventory[playerid][i][InvItemType] = 0;
                RemoveItemAmountToDB(playerid, itemid);
            }
            UpdateItemAmountToDB(playerid, itemid, PlayerInventory[playerid][i][InvItemAmount]);
            break;
        }
    }
    SortPlayerInventory(playerid);
}

SortPlayerInventory(playerid)
{
    for(new z = 0; z < (MAX_INVENTORYSLOT - 1); z++)
    {
        if(PlayerInventory[playerid][z][InvItemType] != 0) continue;
        if((z < (MAX_INVENTORYSLOT)) && (PlayerInventory[playerid][z+1][InvItemType] != 0))
        {
            PlayerInventory[playerid][z][InvItemType] = PlayerInventory[playerid][z+1][InvItemType];
            PlayerInventory[playerid][z][InvItemAmount] = PlayerInventory[playerid][z+1][InvItemAmount];
            PlayerInventory[playerid][z+1][InvItemType] = 0;
            PlayerInventory[playerid][z+1][InvItemAmount] = 0;
        }
    }
}

IsPlayerHasEmptySlot(playerid)
{
    new bool:check;
    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        if(PlayerInventory[playerid][i][InvItemType] == 0)
        {
            check = true;
            break;
        }
        else check = false;
    }
    return check;
}

IsPlayerHasItem(playerid, itemid)
{
    new bool:check = false;
    for(new i = 0; i < MAX_INVENTORYSLOT; i++)
    {
        if(PlayerInventory[playerid][i][InvItemType] == itemid)
        {
            check = true;
            break;
        }
    }
    return check;
}

GetItemName(itemid)
{
    new itemname[125];
    switch(itemid)
    {
        case 0: itemname = "INVALID ITEM";
        case 1: itemname = "Cola";
        case 2: itemname = "Medkit";
        case 3: itemname = "Burger";
    }
    return itemname;
}

AddItemToDB(playerid, itemid, amount)
{
    new query[254];
    mysql_format(Database, query, sizeof(query), "INSERT INTO `inventory` \
        (`OwnerID`, `ItemID`, `Amount`) VALUES ('%d', '%d', '%d')", Player[playerid][ID], itemid, amount);
    mysql_tquery(Database, query);
}

UpdateItemAmountToDB(playerid, itemid, amount)
{
    new query[254];
    mysql_format(Database, query, sizeof(query), "UPDATE `inventory` SET `Amount` = '%d' WHERE (`OwnerID` = '%d' AND `ItemID` = '%d')", amount, Player[playerid][ID], itemid);
    mysql_tquery(Database, query);
}

RemoveItemAmountToDB(playerid, itemid)
{
    new query[254];
    mysql_format(Database, query, sizeof(query), "DELETE FROM `inventory` WHERE (`OwnerID` = '%d' AND `ItemID` = '%d')", Player[playerid][ID], itemid);
    mysql_tquery(Database, query);
}

AssignPlayerInventory(playerid)
{
    inline AssignInventory()
    {
        new rows;
        if(cache_get_row_count(rows))
        {
            for(new i = 0; i < MAX_INVENTORYSLOT && i < rows; i++)
            {
                cache_get_value_int(i, "ItemID", PlayerInventory[playerid][i][InvItemType]);
                cache_get_value_int(i, "Amount", PlayerInventory[playerid][i][InvItemAmount]);
                printf("[MNL:CNR] Loaded %d rows. Slot: %d. Item: %s. Amount: %d. (Player: %s)", rows, i, 
                    GetItemName(PlayerInventory[playerid][i][InvItemType]), 
                    PlayerInventory[playerid][i][InvItemAmount], 
                    GetName(playerid));
            }
        }

    }
    MySQL_TQueryInline(Database, using inline AssignInventory, "SELECT * FROM `inventory` WHERE `OwnerID` = '%d'", Player[playerid][ID]);
    return 1;
}

