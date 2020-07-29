UpdatePlayerData(playerid, reason)
{
	if (Player[playerid][IsLoggedIn] == false) return 0;

	// if the client crashed, it's not possible to get the player's position in OnPlayerDisconnect callback
	// so we will use the last saved position (in case of a player who registered and crashed/kicked, the position will be the default spawn point)


	/*if (reason == 1)    --------------------    warning 203: symbol is never used: "reason"
	{
		GetPlayerPos(playerid, Player[playerid][X_Pos], Player[playerid][Y_Pos], Player[playerid][Z_Pos]);
		GetPlayerFacingAngle(playerid, Player[playerid][A_Pos]);
	}*/



	new query[145];
	mysql_format(Database, query, sizeof query, "UPDATE `players` SET \
		`Tutorial` = %d, \
		`Class` = %d, \
		`Skin` = %d \
		WHERE `id` = %d LIMIT 1",
		Player[playerid][Tutorial],
		Player[playerid][user_class],
		Player[playerid][user_skin],
		Player[playerid][user_id]);
	mysql_tquery(Database, query);
	return 1;
}