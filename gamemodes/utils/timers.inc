timer StopPlayerSound[1000](playerid)
{
	PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	return 1;
}

timer ObjectLoaded[2000](playerid)
{
	TextDrawHideForPlayer(playerid, GM[LoadingTD][0]);
	TextDrawHideForPlayer(playerid, GM[LoadingTD][1]);
	TextDrawHideForPlayer(playerid, GM[LoadingTD][2]);
	TextDrawHideForPlayer(playerid, GM[LoadingTD][3]);
	TextDrawHideForPlayer(playerid, GM[LoadingTD][4]);
	TogglePlayerControllable(playerid, true);
	return 1;
}