/*buildTD()
{

}*/

playerTD(playerid)
{
	Connecting_TD_Message[playerid][0] = CreatePlayerTextDraw(playerid, 313.125000, 69.833412, "Welcome_to");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][0], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][0], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][0], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][0], -7169);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][0], 255);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][0], 0);

	Connecting_TD_Message[playerid][1] = CreatePlayerTextDraw(playerid, 313.349975, 89.216621, "MANILA: COPS N ROBBERS");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][1], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][1], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][1], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][1], 1097466111);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][1], 255);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][1], 3);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][1], 0);

	Connecting_TD_Message[playerid][2] = CreatePlayerTextDraw(playerid, 313.349975, 108.416328, "Visit_our_forums_at");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][2], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][2], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][2], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][2], 225748223);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][2], 255);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][2], 0);

	Connecting_TD_Message[playerid][3] = CreatePlayerTextDraw(playerid, 313.349975, 127.916038, "TBA");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][3], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][3], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][3], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][3], -1400962817);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][3], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][3], 255);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][3], 0);

	Connecting_TD_Message[playerid][4] = CreatePlayerTextDraw(playerid, 313.349975, 147.217208, "~n~Please,_make_sure_to_read_the_rules_and~n~follow_them,_neglecting_them_might_lead~n~you_into_harsh_punishments,~n~If_you_have_any_questions,_do_not_hesitate~n~to_ask_helpers_and_the_staff_team.~n~For more information check up:~n~~g~/help /rules /cmds /info~n~~n~");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][4], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][4], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][4], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][4], -941103617);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][4], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][4], 41983);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][4], 0);

	Connecting_TD_Message[playerid][5] = CreatePlayerTextDraw(playerid, 313.125000, 267.466400, "Have_Fun");
	PlayerTextDrawLetterSize(playerid, Connecting_TD_Message[playerid][5], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Connecting_TD_Message[playerid][5], 0.000000, 318.000000);
	PlayerTextDrawAlignment(playerid, Connecting_TD_Message[playerid][5], 2);
	PlayerTextDrawColor(playerid, Connecting_TD_Message[playerid][5], -1291869441);
	PlayerTextDrawUseBox(playerid, Connecting_TD_Message[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, Connecting_TD_Message[playerid][5], 255);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, Connecting_TD_Message[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, Connecting_TD_Message[playerid][5], 255);
	PlayerTextDrawFont(playerid, Connecting_TD_Message[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, Connecting_TD_Message[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, Connecting_TD_Message[playerid][5], 0);
}

