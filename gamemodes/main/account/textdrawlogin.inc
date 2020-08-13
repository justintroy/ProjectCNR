new PlayerText:Login_Box[MAX_PLAYERS];
new PlayerText:Login_Header[MAX_PLAYERS];
new PlayerText:Login_PrevTag1[MAX_PLAYERS];
new PlayerText:Login_PrevTag2[MAX_PLAYERS];
new PlayerText:Login_Welcome[MAX_PLAYERS];
new PlayerText:Login_PasswordHeader[MAX_PLAYERS];
new PlayerText:Login_Model2[MAX_PLAYERS];
new PlayerText:Login_PasswordInput[MAX_PLAYERS];
new PlayerText:Login_RuleHeader[MAX_PLAYERS];
new PlayerText:Login_Model1[MAX_PLAYERS];
new PlayerText:Login_Rule1[MAX_PLAYERS];
new PlayerText:Login_Rule2[MAX_PLAYERS];
new PlayerText:Login_Rule3[MAX_PLAYERS];
new PlayerText:Login_Rule4[MAX_PLAYERS];
new PlayerText:Login_Proceed[MAX_PLAYERS];

/*YCMD:logintd(playerid, params[], help) 
{
    LoginTextDrawCreate(playerid);
    LoginTextDrawShow(playerid);
    return 1;
}*/


LoginTextDrawCreate(playerid)
{
	Login_Box[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 123.000000, "_");
	PlayerTextDrawFont(playerid, Login_Box[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Login_Box[playerid], 0.316666, 26.899997);
	PlayerTextDrawTextSize(playerid, Login_Box[playerid], 191.000000, 268.500000);
	PlayerTextDrawSetOutline(playerid, Login_Box[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_Box[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Box[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Box[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_Box[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Box[playerid], 1077890148);
	PlayerTextDrawUseBox(playerid, Login_Box[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Login_Box[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Box[playerid], 0);

	Login_Header[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 101.000000, "Login");
	PlayerTextDrawFont(playerid, Login_Header[playerid], 0);
	PlayerTextDrawLetterSize(playerid, Login_Header[playerid], 0.745831, 3.399996);
	PlayerTextDrawTextSize(playerid, Login_Header[playerid], 405.000000, 159.500000);
	PlayerTextDrawSetOutline(playerid, Login_Header[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_Header[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Header[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Header[playerid], 383827455);
	PlayerTextDrawBackgroundColor(playerid, Login_Header[playerid], 70);
	PlayerTextDrawBoxColor(playerid, Login_Header[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Header[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Header[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Header[playerid], 0);

	Login_PrevTag1[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 361.000000, "Manila: Cops n' Robbers");
	PlayerTextDrawFont(playerid, Login_PrevTag1[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Login_PrevTag1[playerid], 0.245829, 1.450000);
	PlayerTextDrawTextSize(playerid, Login_PrevTag1[playerid], 568.500000, 181.000000);
	PlayerTextDrawSetOutline(playerid, Login_PrevTag1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_PrevTag1[playerid], 1);
	PlayerTextDrawAlignment(playerid, Login_PrevTag1[playerid], 2);
	PlayerTextDrawColor(playerid, Login_PrevTag1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_PrevTag1[playerid], 59);
	PlayerTextDrawBoxColor(playerid, Login_PrevTag1[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_PrevTag1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_PrevTag1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_PrevTag1[playerid], 0);

	Login_PrevTag2[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 374.000000, SERVER_DISCORD);
	PlayerTextDrawFont(playerid, Login_PrevTag2[playerid], 2);
	PlayerTextDrawLetterSize(playerid, Login_PrevTag2[playerid], 0.141662, 0.750000);
	PlayerTextDrawTextSize(playerid, Login_PrevTag2[playerid], 443.500000, 127.500000);
	PlayerTextDrawSetOutline(playerid, Login_PrevTag2[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_PrevTag2[playerid], 1);
	PlayerTextDrawAlignment(playerid, Login_PrevTag2[playerid], 2);
	PlayerTextDrawColor(playerid, Login_PrevTag2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_PrevTag2[playerid], 50);
	PlayerTextDrawBoxColor(playerid, Login_PrevTag2[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_PrevTag2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_PrevTag2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_PrevTag2[playerid], 0);

	Login_Welcome[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 144.000000, "Welcome back, Lorem Ipsum!");
	PlayerTextDrawFont(playerid, Login_Welcome[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Login_Welcome[playerid], 0.391666, 1.750000);
	PlayerTextDrawTextSize(playerid, Login_Welcome[playerid], 403.500000, 343.500000);
	PlayerTextDrawSetOutline(playerid, Login_Welcome[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_Welcome[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Welcome[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Welcome[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_Welcome[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Welcome[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Welcome[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Welcome[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Welcome[playerid], 0);
	
	Login_PasswordHeader[playerid] = CreatePlayerTextDraw(playerid, 217.000000, 184.000000, "Password:");
	PlayerTextDrawFont(playerid, Login_PasswordHeader[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Login_PasswordHeader[playerid], 0.458332, 1.549999);
	PlayerTextDrawTextSize(playerid, Login_PasswordHeader[playerid], 298.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Login_PasswordHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_PasswordHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_PasswordHeader[playerid], 1);
	PlayerTextDrawColor(playerid, Login_PasswordHeader[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_PasswordHeader[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_PasswordHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_PasswordHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_PasswordHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_PasswordHeader[playerid], 0);

	Login_Model2[playerid] = CreatePlayerTextDraw(playerid, 8.000000, 7.000000, "356");
	PlayerTextDrawFont(playerid, Login_Model2[playerid], 5);
	PlayerTextDrawLetterSize(playerid, Login_Model2[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Login_Model2[playerid], 270.000000, 260.000000);
	PlayerTextDrawSetOutline(playerid, Login_Model2[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Model2[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Model2[playerid], 1);
	PlayerTextDrawColor(playerid, Login_Model2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_Model2[playerid], 0);
	PlayerTextDrawBoxColor(playerid, Login_Model2[playerid], 255);
	PlayerTextDrawUseBox(playerid, Login_Model2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Model2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Model2[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, Login_Model2[playerid], 355);
	PlayerTextDrawSetPreviewRot(playerid, Login_Model2[playerid], -61.000000, -60.000000, 136.000000, 2.579998);
	PlayerTextDrawSetPreviewVehCol(playerid, Login_Model2[playerid], 1, 1);

	Login_PasswordInput[playerid] = CreatePlayerTextDraw(playerid, 309.000000, 184.000000, "type here");
	PlayerTextDrawFont(playerid, Login_PasswordInput[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Login_PasswordInput[playerid], 0.374998, 1.449998);
	PlayerTextDrawTextSize(playerid, Login_PasswordInput[playerid], 417.000000, 20.500000);
	PlayerTextDrawSetOutline(playerid, Login_PasswordInput[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_PasswordInput[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_PasswordInput[playerid], 1);
	PlayerTextDrawColor(playerid, Login_PasswordInput[playerid], 255);
	PlayerTextDrawBackgroundColor(playerid, Login_PasswordInput[playerid], -236);
	PlayerTextDrawBoxColor(playerid, Login_PasswordInput[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_PasswordInput[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Login_PasswordInput[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_PasswordInput[playerid], 1);

	Login_RuleHeader[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 213.000000, "Rules:");
	PlayerTextDrawFont(playerid, Login_RuleHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, Login_RuleHeader[playerid], 0.458330, 1.899996);
	PlayerTextDrawTextSize(playerid, Login_RuleHeader[playerid], 400.500000, 44.500000);
	PlayerTextDrawSetOutline(playerid, Login_RuleHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_RuleHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_RuleHeader[playerid], 2);
	PlayerTextDrawColor(playerid, Login_RuleHeader[playerid], -741092353);
	PlayerTextDrawBackgroundColor(playerid, Login_RuleHeader[playerid], 70);
	PlayerTextDrawBoxColor(playerid, Login_RuleHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_RuleHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_RuleHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_RuleHeader[playerid], 0);

	Login_Model1[playerid] = CreatePlayerTextDraw(playerid, 42.000000, 130.000000, "356");
	PlayerTextDrawFont(playerid, Login_Model1[playerid], 5);
	PlayerTextDrawLetterSize(playerid, Login_Model1[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Login_Model1[playerid], 270.000000, 260.000000);
	PlayerTextDrawSetOutline(playerid, Login_Model1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Model1[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Model1[playerid], 1);
	PlayerTextDrawColor(playerid, Login_Model1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_Model1[playerid], 0);
	PlayerTextDrawBoxColor(playerid, Login_Model1[playerid], 255);
	PlayerTextDrawUseBox(playerid, Login_Model1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Model1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Model1[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, Login_Model1[playerid], 7073);
	PlayerTextDrawSetPreviewRot(playerid, Login_Model1[playerid], -10.000000, 0.000000, 90.000000, 0.949998);
	PlayerTextDrawSetPreviewVehCol(playerid, Login_Model1[playerid], 1, 1);

	Login_Rule1[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 235.000000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	PlayerTextDrawFont(playerid, Login_Rule1[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Login_Rule1[playerid], 0.183330, 1.250000);
	PlayerTextDrawTextSize(playerid, Login_Rule1[playerid], 451.000000, 200.500000);
	PlayerTextDrawSetOutline(playerid, Login_Rule1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Rule1[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Rule1[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Rule1[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Login_Rule1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Rule1[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Rule1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Rule1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Rule1[playerid], 0);

	Login_Rule2[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 258.000000, "Fusce facilisis erat vel sapien sollicitudin porttitor.");
	PlayerTextDrawFont(playerid, Login_Rule2[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Login_Rule2[playerid], 0.183330, 1.250000);
	PlayerTextDrawTextSize(playerid, Login_Rule2[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Login_Rule2[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Rule2[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Rule2[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Rule2[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Login_Rule2[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Rule2[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Rule2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Rule2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Rule2[playerid], 0);

	Login_Rule3[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 280.000000, "Quisque venenatis urna quis sapien elementum commodo.");
	PlayerTextDrawFont(playerid, Login_Rule3[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Login_Rule3[playerid], 0.183330, 1.250000);
	PlayerTextDrawTextSize(playerid, Login_Rule3[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Login_Rule3[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Rule3[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Rule3[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Rule3[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Login_Rule3[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Rule3[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Rule3[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Rule3[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Rule3[playerid], 0);

	Login_Rule4[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 301.000000, "Aenean blandit enim id lorem semper, eget blandit libero consectetur.");
	PlayerTextDrawFont(playerid, Login_Rule4[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Login_Rule4[playerid], 0.183330, 1.250000);
	PlayerTextDrawTextSize(playerid, Login_Rule4[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Login_Rule4[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Login_Rule4[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Rule4[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Rule4[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Login_Rule4[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Rule4[playerid], 50);
	PlayerTextDrawUseBox(playerid, Login_Rule4[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Login_Rule4[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Rule4[playerid], 0);

	Login_Proceed[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 334.000000, "Proceed");
	PlayerTextDrawFont(playerid, Login_Proceed[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Login_Proceed[playerid], 0.462498, 1.750000);
	PlayerTextDrawTextSize(playerid, Login_Proceed[playerid], 30.500000, 220.000000);
	PlayerTextDrawSetOutline(playerid, Login_Proceed[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Login_Proceed[playerid], 0);
	PlayerTextDrawAlignment(playerid, Login_Proceed[playerid], 2);
	PlayerTextDrawColor(playerid, Login_Proceed[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Login_Proceed[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Login_Proceed[playerid], 830864639);
	PlayerTextDrawUseBox(playerid, Login_Proceed[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Login_Proceed[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Login_Proceed[playerid], 1);
}

LoginTextDrawDestroy(playerid)
{
	PlayerTextDrawDestroy(playerid, Login_Box[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Header[playerid]);
	PlayerTextDrawDestroy(playerid, Login_PrevTag1[playerid]);
	PlayerTextDrawDestroy(playerid, Login_PrevTag2[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Welcome[playerid]);
	PlayerTextDrawDestroy(playerid, Login_PasswordHeader[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Model2[playerid]);
	PlayerTextDrawDestroy(playerid, Login_PasswordInput[playerid]);
	PlayerTextDrawDestroy(playerid, Login_RuleHeader[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Model1[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Rule1[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Rule2[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Rule3[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Rule4[playerid]);
	PlayerTextDrawDestroy(playerid, Login_Proceed[playerid]);
}

LoginTextDrawShow(playerid)
{
	new newtext[41];
    format(newtext, sizeof(newtext), "Welcome back, %s!", Player[playerid][Username]);
    PlayerTextDrawSetString(playerid, Login_Welcome[playerid], newtext);

	PlayerTextDrawShow(playerid, Login_Box[playerid]);
	PlayerTextDrawShow(playerid, Login_Header[playerid]);
	PlayerTextDrawShow(playerid, Login_PrevTag1[playerid]);
	PlayerTextDrawShow(playerid, Login_PrevTag2[playerid]);
	PlayerTextDrawShow(playerid, Login_Welcome[playerid]);
	PlayerTextDrawShow(playerid, Login_PasswordHeader[playerid]);
	PlayerTextDrawShow(playerid, Login_Model2[playerid]);
	PlayerTextDrawShow(playerid, Login_PasswordInput[playerid]);
	PlayerTextDrawShow(playerid, Login_RuleHeader[playerid]);
	PlayerTextDrawShow(playerid, Login_Model1[playerid]);
	PlayerTextDrawShow(playerid, Login_Rule1[playerid]);
	PlayerTextDrawShow(playerid, Login_Rule2[playerid]);
	PlayerTextDrawShow(playerid, Login_Rule3[playerid]);
	PlayerTextDrawShow(playerid, Login_Rule4[playerid]);
	PlayerTextDrawShow(playerid, Login_Proceed[playerid]);
	SelectTextDraw(playerid, 0xFF0000FF);
}

LoginTextDrawHide(playerid)
{
	PlayerTextDrawHide(playerid, Login_Box[playerid]);
	PlayerTextDrawHide(playerid, Login_Header[playerid]);
	PlayerTextDrawHide(playerid, Login_PrevTag1[playerid]);
	PlayerTextDrawHide(playerid, Login_PrevTag2[playerid]);
	PlayerTextDrawHide(playerid, Login_Welcome[playerid]);
	PlayerTextDrawHide(playerid, Login_PasswordHeader[playerid]);
	PlayerTextDrawHide(playerid, Login_Model2[playerid]);
	PlayerTextDrawHide(playerid, Login_PasswordInput[playerid]);
	PlayerTextDrawHide(playerid, Login_RuleHeader[playerid]);
	PlayerTextDrawHide(playerid, Login_Model1[playerid]);
	PlayerTextDrawHide(playerid, Login_Rule1[playerid]);
	PlayerTextDrawHide(playerid, Login_Rule2[playerid]);
	PlayerTextDrawHide(playerid, Login_Rule3[playerid]);
	PlayerTextDrawHide(playerid, Login_Rule4[playerid]);
	PlayerTextDrawHide(playerid, Login_Proceed[playerid]);
	CancelSelectTextDraw(playerid);
}