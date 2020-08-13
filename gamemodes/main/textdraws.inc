buildTD()
{
	GM[LoadingTD][0] = TextDrawCreate(320.000000, 180.000000, "_");
	TextDrawFont(GM[LoadingTD][0], 1);
	TextDrawLetterSize(GM[LoadingTD][0], 0.600000, 9.750000);
	TextDrawTextSize(GM[LoadingTD][0], 305.500000, 140.000000);
	TextDrawSetOutline(GM[LoadingTD][0], 1);
	TextDrawSetShadow(GM[LoadingTD][0], 0);
	TextDrawAlignment(GM[LoadingTD][0], 2);
	TextDrawColor(GM[LoadingTD][0], -1);
	TextDrawBackgroundColor(GM[LoadingTD][0], 255);
	TextDrawBoxColor(GM[LoadingTD][0], 1077890228);
	TextDrawUseBox(GM[LoadingTD][0], 1);
	TextDrawSetProportional(GM[LoadingTD][0], 1);
	TextDrawSetSelectable(GM[LoadingTD][0], 0);

	GM[LoadingTD][1] = TextDrawCreate(243.000000, 180.000000, "_");
	TextDrawFont(GM[LoadingTD][1], 1);
	TextDrawLetterSize(GM[LoadingTD][1], 0.570833, 9.699999);
	TextDrawTextSize(GM[LoadingTD][1], 294.000000, 1.500000);
	TextDrawSetOutline(GM[LoadingTD][1], 1);
	TextDrawSetShadow(GM[LoadingTD][1], 0);
	TextDrawAlignment(GM[LoadingTD][1], 2);
	TextDrawColor(GM[LoadingTD][1], -256);
	TextDrawBackgroundColor(GM[LoadingTD][1], 830864384);
	TextDrawBoxColor(GM[LoadingTD][1], 830864484);
	TextDrawUseBox(GM[LoadingTD][1], 1);
	TextDrawSetProportional(GM[LoadingTD][1], 1);
	TextDrawSetSelectable(GM[LoadingTD][1], 0);

	GM[LoadingTD][2] = TextDrawCreate(320.000000, 191.000000, "MNL: CNR");
	TextDrawFont(GM[LoadingTD][2], 3);
	TextDrawLetterSize(GM[LoadingTD][2], 0.720833, 2.449999);
	TextDrawTextSize(GM[LoadingTD][2], 400.000000, 114.500000);
	TextDrawSetOutline(GM[LoadingTD][2], 1);
	TextDrawSetShadow(GM[LoadingTD][2], 0);
	TextDrawAlignment(GM[LoadingTD][2], 2);
	TextDrawColor(GM[LoadingTD][2], 830864639);
	TextDrawBackgroundColor(GM[LoadingTD][2], 40);
	TextDrawBoxColor(GM[LoadingTD][2], 50);
	TextDrawUseBox(GM[LoadingTD][2], 0);
	TextDrawSetProportional(GM[LoadingTD][2], 1);
	TextDrawSetSelectable(GM[LoadingTD][2], 0);

	GM[LoadingTD][3] = TextDrawCreate(320.000000, 217.000000, SERVER_DISCORD);
	TextDrawFont(GM[LoadingTD][3], 1);
	TextDrawLetterSize(GM[LoadingTD][3], 0.233333, 1.050000);
	TextDrawTextSize(GM[LoadingTD][3], 400.000000, 114.500000);
	TextDrawSetOutline(GM[LoadingTD][3], 1);
	TextDrawSetShadow(GM[LoadingTD][3], 0);
	TextDrawAlignment(GM[LoadingTD][3], 2);
	TextDrawColor(GM[LoadingTD][3], -102998785);
	TextDrawBackgroundColor(GM[LoadingTD][3], 40);
	TextDrawBoxColor(GM[LoadingTD][3], 50);
	TextDrawUseBox(GM[LoadingTD][3], 0);
	TextDrawSetProportional(GM[LoadingTD][3], 1);
	TextDrawSetSelectable(GM[LoadingTD][3], 0);

	GM[LoadingTD][4] = TextDrawCreate(321.000000, 252.000000, "Loading... Please wait");
	TextDrawFont(GM[LoadingTD][4], 2);
	TextDrawLetterSize(GM[LoadingTD][4], 0.233333, 1.050000);
	TextDrawTextSize(GM[LoadingTD][4], 401.500000, 131.000000);
	TextDrawSetOutline(GM[LoadingTD][4], 0);
	TextDrawSetShadow(GM[LoadingTD][4], 0);
	TextDrawAlignment(GM[LoadingTD][4], 2);
	TextDrawColor(GM[LoadingTD][4], -102998785);
	TextDrawBackgroundColor(GM[LoadingTD][4], 255);
	TextDrawBoxColor(GM[LoadingTD][4], 50);
	TextDrawUseBox(GM[LoadingTD][4], 0);
	TextDrawSetProportional(GM[LoadingTD][4], 1);
	TextDrawSetSelectable(GM[LoadingTD][4], 0);
}

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

