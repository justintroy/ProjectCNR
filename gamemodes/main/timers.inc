timer StopPlayerSound[8000](playerid)
{
	PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	return 1;
}