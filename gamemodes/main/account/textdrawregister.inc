new PlayerText:Register_Box[MAX_PLAYERS];
new PlayerText:Register_Header[MAX_PLAYERS];
new PlayerText:Register_PrevTag1[MAX_PLAYERS];
new PlayerText:Register_PrevTag2[MAX_PLAYERS];
new PlayerText:Register_Welcome[MAX_PLAYERS];
new PlayerText:Register_PasswordHeader[MAX_PLAYERS];
new PlayerText:Register_PasswordInput[MAX_PLAYERS];
new PlayerText:Register_RuleHeader[MAX_PLAYERS];
new PlayerText:Register_Rule1[MAX_PLAYERS];
new PlayerText:Register_Proceed[MAX_PLAYERS];
new PlayerText:Register_Rule2[MAX_PLAYERS];
new PlayerText:Register_Rule3[MAX_PLAYERS];
new PlayerText:Register_Rule4[MAX_PLAYERS];
new PlayerText:Register_Model1[MAX_PLAYERS];
new PlayerText:Register_Model2[MAX_PLAYERS];

/*YCMD:registertd(playerid, params[], help) 
{
    RegisterTextDrawCreate(playerid);
    RegisterTextDrawShow(playerid);
    return 1;
}*/

RegisterTextDrawCreate(playerid)
{
	Register_Box[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 123.000000, "_");
	PlayerTextDrawFont(playerid, Register_Box[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Register_Box[playerid], 0.316666, 26.899997);
	PlayerTextDrawTextSize(playerid, Register_Box[playerid], 191.000000, 268.500000);
	PlayerTextDrawSetOutline(playerid, Register_Box[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_Box[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Box[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Box[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_Box[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Box[playerid], 1077890148);
	PlayerTextDrawUseBox(playerid, Register_Box[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Register_Box[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Box[playerid], 0);

	Register_Header[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 101.000000, "Registration");
	PlayerTextDrawFont(playerid, Register_Header[playerid], 0);
	PlayerTextDrawLetterSize(playerid, Register_Header[playerid], 0.745831, 3.399996);
	PlayerTextDrawTextSize(playerid, Register_Header[playerid], 405.000000, 159.500000);
	PlayerTextDrawSetOutline(playerid, Register_Header[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_Header[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Header[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Header[playerid], 383827455);
	PlayerTextDrawBackgroundColor(playerid, Register_Header[playerid], 70);
	PlayerTextDrawBoxColor(playerid, Register_Header[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Header[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Header[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Header[playerid], 0);

	Register_PrevTag1[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 361.000000, "Manila: Cops n' Robbers");
	PlayerTextDrawFont(playerid, Register_PrevTag1[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Register_PrevTag1[playerid], 0.245829, 1.450000);
	PlayerTextDrawTextSize(playerid, Register_PrevTag1[playerid], 568.500000, 181.000000);
	PlayerTextDrawSetOutline(playerid, Register_PrevTag1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_PrevTag1[playerid], 1);
	PlayerTextDrawAlignment(playerid, Register_PrevTag1[playerid], 2);
	PlayerTextDrawColor(playerid, Register_PrevTag1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_PrevTag1[playerid], 59);
	PlayerTextDrawBoxColor(playerid, Register_PrevTag1[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_PrevTag1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_PrevTag1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_PrevTag1[playerid], 0);

	Register_PrevTag2[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 374.000000, SERVER_DISCORD);
	PlayerTextDrawFont(playerid, Register_PrevTag2[playerid], 2);
	PlayerTextDrawLetterSize(playerid, Register_PrevTag2[playerid], 0.141662, 0.750000);
	PlayerTextDrawTextSize(playerid, Register_PrevTag2[playerid], 443.500000, 127.500000);
	PlayerTextDrawSetOutline(playerid, Register_PrevTag2[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_PrevTag2[playerid], 1);
	PlayerTextDrawAlignment(playerid, Register_PrevTag2[playerid], 2);
	PlayerTextDrawColor(playerid, Register_PrevTag2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_PrevTag2[playerid], 50);
	PlayerTextDrawBoxColor(playerid, Register_PrevTag2[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_PrevTag2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_PrevTag2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_PrevTag2[playerid], 0);

	Register_Welcome[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 144.000000, "Welcome Lorem Ipsum!");
	PlayerTextDrawFont(playerid, Register_Welcome[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Register_Welcome[playerid], 0.483332, 2.099999);
	PlayerTextDrawTextSize(playerid, Register_Welcome[playerid], 403.500000, 343.500000);
	PlayerTextDrawSetOutline(playerid, Register_Welcome[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_Welcome[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Welcome[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Welcome[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_Welcome[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Welcome[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Welcome[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Welcome[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Welcome[playerid], 0);

	Register_PasswordHeader[playerid] = CreatePlayerTextDraw(playerid, 217.000000, 184.000000, "Password:");
	PlayerTextDrawFont(playerid, Register_PasswordHeader[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Register_PasswordHeader[playerid], 0.458332, 1.549998);
	PlayerTextDrawTextSize(playerid, Register_PasswordHeader[playerid], 298.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Register_PasswordHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_PasswordHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_PasswordHeader[playerid], 1);
	PlayerTextDrawColor(playerid, Register_PasswordHeader[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_PasswordHeader[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_PasswordHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_PasswordHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_PasswordHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_PasswordHeader[playerid], 0);

	Register_PasswordInput[playerid] = CreatePlayerTextDraw(playerid, 309.000000, 184.000000, "type here");
	PlayerTextDrawFont(playerid, Register_PasswordInput[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Register_PasswordInput[playerid], 0.374998, 1.449998);
	PlayerTextDrawTextSize(playerid, Register_PasswordInput[playerid], 417.000000, 20.500000);
	PlayerTextDrawSetOutline(playerid, Register_PasswordInput[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_PasswordInput[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_PasswordInput[playerid], 1);
	PlayerTextDrawColor(playerid, Register_PasswordInput[playerid], 255);
	PlayerTextDrawBackgroundColor(playerid, Register_PasswordInput[playerid], -236);
	PlayerTextDrawBoxColor(playerid, Register_PasswordInput[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_PasswordInput[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Register_PasswordInput[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_PasswordInput[playerid], 1);

	Register_RuleHeader[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 213.000000, "Rules:");
	PlayerTextDrawFont(playerid, Register_RuleHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, Register_RuleHeader[playerid], 0.458330, 1.899996);
	PlayerTextDrawTextSize(playerid, Register_RuleHeader[playerid], 400.500000, 44.500000);
	PlayerTextDrawSetOutline(playerid, Register_RuleHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_RuleHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_RuleHeader[playerid], 2);
	PlayerTextDrawColor(playerid, Register_RuleHeader[playerid], -741092353);
	PlayerTextDrawBackgroundColor(playerid, Register_RuleHeader[playerid], 70);
	PlayerTextDrawBoxColor(playerid, Register_RuleHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_RuleHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_RuleHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_RuleHeader[playerid], 0);

	Register_Rule1[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 235.000000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	PlayerTextDrawFont(playerid, Register_Rule1[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Register_Rule1[playerid], 0.183329, 1.250000);
	PlayerTextDrawTextSize(playerid, Register_Rule1[playerid], 451.000000, 200.500000);
	PlayerTextDrawSetOutline(playerid, Register_Rule1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Rule1[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Rule1[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Rule1[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Register_Rule1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Rule1[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Rule1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Rule1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Rule1[playerid], 0);

	Register_Proceed[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 334.000000, "Register!");
	PlayerTextDrawFont(playerid, Register_Proceed[playerid], 3);
	PlayerTextDrawLetterSize(playerid, Register_Proceed[playerid], 0.462498, 1.750000);
	PlayerTextDrawTextSize(playerid, Register_Proceed[playerid], 28.000000, 159.000000);
	PlayerTextDrawSetOutline(playerid, Register_Proceed[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Register_Proceed[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Proceed[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Proceed[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_Proceed[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Proceed[playerid], 830864639);
	PlayerTextDrawUseBox(playerid, Register_Proceed[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Register_Proceed[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Proceed[playerid], 1);

	Register_Rule2[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 258.000000, "Fusce facilisis erat vel sapien sollicitudin porttitor.");
	PlayerTextDrawFont(playerid, Register_Rule2[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Register_Rule2[playerid], 0.183329, 1.250000);
	PlayerTextDrawTextSize(playerid, Register_Rule2[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Register_Rule2[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Rule2[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Rule2[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Rule2[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Register_Rule2[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Rule2[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Rule2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Rule2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Rule2[playerid], 0);

	Register_Rule3[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 280.000000, "Quisque venenatis urna quis sapien elementum commodo.");
	PlayerTextDrawFont(playerid, Register_Rule3[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Register_Rule3[playerid], 0.183329, 1.250000);
	PlayerTextDrawTextSize(playerid, Register_Rule3[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Register_Rule3[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Rule3[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Rule3[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Rule3[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Register_Rule3[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Rule3[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Rule3[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Rule3[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Rule3[playerid], 0);

	Register_Rule4[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 301.000000, "Aenean blandit enim id lorem semper, eget blandit libero consectetur.");
	PlayerTextDrawFont(playerid, Register_Rule4[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Register_Rule4[playerid], 0.183329, 1.250000);
	PlayerTextDrawTextSize(playerid, Register_Rule4[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, Register_Rule4[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Rule4[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Rule4[playerid], 2);
	PlayerTextDrawColor(playerid, Register_Rule4[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, Register_Rule4[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Register_Rule4[playerid], 50);
	PlayerTextDrawUseBox(playerid, Register_Rule4[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Rule4[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Rule4[playerid], 0);

	Register_Model1[playerid] = CreatePlayerTextDraw(playerid, 25.000000, 124.000000, "356");
	PlayerTextDrawFont(playerid, Register_Model1[playerid], 5);
	PlayerTextDrawLetterSize(playerid, Register_Model1[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Register_Model1[playerid], 270.000000, 260.000000);
	PlayerTextDrawSetOutline(playerid, Register_Model1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Model1[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Model1[playerid], 1);
	PlayerTextDrawColor(playerid, Register_Model1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_Model1[playerid], 0);
	PlayerTextDrawBoxColor(playerid, Register_Model1[playerid], 255);
	PlayerTextDrawUseBox(playerid, Register_Model1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Model1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Model1[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, Register_Model1[playerid], 1585);
	PlayerTextDrawSetPreviewRot(playerid, Register_Model1[playerid], -8.000000, 0.000000, 1.000000, 0.949998);
	PlayerTextDrawSetPreviewVehCol(playerid, Register_Model1[playerid], 1, 1);

	Register_Model2[playerid] = CreatePlayerTextDraw(playerid, 336.000000, 126.000000, "356");
	PlayerTextDrawFont(playerid, Register_Model2[playerid], 5);
	PlayerTextDrawLetterSize(playerid, Register_Model2[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Register_Model2[playerid], 270.000000, 260.000000);
	PlayerTextDrawSetOutline(playerid, Register_Model2[playerid], 0);
	PlayerTextDrawSetShadow(playerid, Register_Model2[playerid], 0);
	PlayerTextDrawAlignment(playerid, Register_Model2[playerid], 1);
	PlayerTextDrawColor(playerid, Register_Model2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Register_Model2[playerid], 0);
	PlayerTextDrawBoxColor(playerid, Register_Model2[playerid], 255);
	PlayerTextDrawUseBox(playerid, Register_Model2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Register_Model2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Register_Model2[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, Register_Model2[playerid], 1583);
	PlayerTextDrawSetPreviewRot(playerid, Register_Model2[playerid], -8.000000, 0.000000, 1.000000, 0.949998);
	PlayerTextDrawSetPreviewVehCol(playerid, Register_Model2[playerid], 1, 1);
}

RegisterTextDrawDestroy(playerid)
{
	PlayerTextDrawDestroy(playerid, Register_Box[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Header[playerid]);
	PlayerTextDrawDestroy(playerid, Register_PrevTag1[playerid]);
	PlayerTextDrawDestroy(playerid, Register_PrevTag2[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Welcome[playerid]);
	PlayerTextDrawDestroy(playerid, Register_PasswordHeader[playerid]);
	PlayerTextDrawDestroy(playerid, Register_PasswordInput[playerid]);
	PlayerTextDrawDestroy(playerid, Register_RuleHeader[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Rule1[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Proceed[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Rule2[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Rule3[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Rule4[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Model1[playerid]);
	PlayerTextDrawDestroy(playerid, Register_Model2[playerid]);
}

RegisterTextDrawShow(playerid)
{
	new newtext[41];
    format(newtext, sizeof(newtext), "Welcome %s!", Player[playerid][Username]);
    PlayerTextDrawSetString(playerid, Register_Welcome[playerid], newtext);
	PlayerTextDrawShow(playerid, Register_Box[playerid]);
	PlayerTextDrawShow(playerid, Register_Header[playerid]);
	PlayerTextDrawShow(playerid, Register_PrevTag1[playerid]);
	PlayerTextDrawShow(playerid, Register_PrevTag2[playerid]);
	PlayerTextDrawShow(playerid, Register_Welcome[playerid]);
	PlayerTextDrawShow(playerid, Register_PasswordHeader[playerid]);
	PlayerTextDrawShow(playerid, Register_PasswordInput[playerid]);
	PlayerTextDrawShow(playerid, Register_RuleHeader[playerid]);
	PlayerTextDrawShow(playerid, Register_Rule1[playerid]);
	PlayerTextDrawShow(playerid, Register_Proceed[playerid]);
	PlayerTextDrawShow(playerid, Register_Rule2[playerid]);
	PlayerTextDrawShow(playerid, Register_Rule3[playerid]);
	PlayerTextDrawShow(playerid, Register_Rule4[playerid]);
	PlayerTextDrawShow(playerid, Register_Model1[playerid]);
	PlayerTextDrawShow(playerid, Register_Model2[playerid]);
	SelectTextDraw(playerid, 0xFF0000FF);
}

RegisterTextDrawHide(playerid)
{
	PlayerTextDrawHide(playerid, Register_Box[playerid]);
	PlayerTextDrawHide(playerid, Register_Header[playerid]);
	PlayerTextDrawHide(playerid, Register_PrevTag1[playerid]);
	PlayerTextDrawHide(playerid, Register_PrevTag2[playerid]);
	PlayerTextDrawHide(playerid, Register_Welcome[playerid]);
	PlayerTextDrawHide(playerid, Register_PasswordHeader[playerid]);
	PlayerTextDrawHide(playerid, Register_PasswordInput[playerid]);
	PlayerTextDrawHide(playerid, Register_RuleHeader[playerid]);
	PlayerTextDrawHide(playerid, Register_Rule1[playerid]);
	PlayerTextDrawHide(playerid, Register_Proceed[playerid]);
	PlayerTextDrawHide(playerid, Register_Rule2[playerid]);
	PlayerTextDrawHide(playerid, Register_Rule3[playerid]);
	PlayerTextDrawHide(playerid, Register_Rule4[playerid]);
	PlayerTextDrawHide(playerid, Register_Model1[playerid]);
	PlayerTextDrawHide(playerid, Register_Model2[playerid]);
	CancelSelectTextDraw(playerid);
}