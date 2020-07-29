//#include <YSI\y_hooks>

new PlayerText:CS_PrevBox[MAX_PLAYERS];
new PlayerText:CS_PrevHeader[MAX_PLAYERS];
new PlayerText:CS_PrevTag1[MAX_PLAYERS];
new PlayerText:CS_PrevTag2[MAX_PLAYERS];
new PlayerText:CS_PreviewClass[MAX_PLAYERS];
new PlayerText:CS_PreviewName[MAX_PLAYERS];
new PlayerText:CS_PrevClass[MAX_PLAYERS];
new PlayerText:CS_PrevNameInput[MAX_PLAYERS];
new PlayerText:CS_PrevClassInput[MAX_PLAYERS];
new PlayerText:CS_PrevRulesHeader[MAX_PLAYERS];
new PlayerText:CS_PrevRule1[MAX_PLAYERS];
new PlayerText:CS_PrevRule2[MAX_PLAYERS];
new PlayerText:CS_PrevRule3[MAX_PLAYERS];
new PlayerText:CS_PrevRule4[MAX_PLAYERS];
new PlayerText:CS_PrevBack[MAX_PLAYERS];
new PlayerText:CS_PrevProceed[MAX_PLAYERS];


SetPrevClassInput(playerid, class)
{
	switch(class)
	{
		case 1: PlayerTextDrawSetString(playerid, CS_PrevClassInput[playerid], "Civilian");
		case 2: PlayerTextDrawSetString(playerid, CS_PrevClassInput[playerid], "Police");
		case 3: PlayerTextDrawSetString(playerid, CS_PrevClassInput[playerid], "FBI");
		case 4: PlayerTextDrawSetString(playerid, CS_PrevClassInput[playerid], "Armed Forces");
		default: PlayerTextDrawSetString(playerid, CS_PrevClassInput[playerid], "Relog ka boy");
	}

}


csPrevTextDrawCreate(playerid)
{
	CS_PrevBox[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 123.000000, "_");
	PlayerTextDrawFont(playerid, CS_PrevBox[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CS_PrevBox[playerid], 0.316666, 26.899997);
	PlayerTextDrawTextSize(playerid, CS_PrevBox[playerid], 191.000000, 268.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevBox[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevBox[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevBox[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevBox[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevBox[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevBox[playerid], 1077890148);
	PlayerTextDrawUseBox(playerid, CS_PrevBox[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CS_PrevBox[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevBox[playerid], 0);

	CS_PrevHeader[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 101.000000, "Class Select");
	PlayerTextDrawFont(playerid, CS_PrevHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, CS_PrevHeader[playerid], 0.745831, 3.399996);
	PlayerTextDrawTextSize(playerid, CS_PrevHeader[playerid], 405.000000, 159.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevHeader[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevHeader[playerid], 383827455);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevHeader[playerid], 70);
	PlayerTextDrawBoxColor(playerid, CS_PrevHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevHeader[playerid], 0);

	CS_PrevTag1[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 361.000000, "Manila: Cops n' Robbers");
	PlayerTextDrawFont(playerid, CS_PrevTag1[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevTag1[playerid], 0.245829, 1.450000);
	PlayerTextDrawTextSize(playerid, CS_PrevTag1[playerid], 568.500000, 181.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevTag1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevTag1[playerid], 1);
	PlayerTextDrawAlignment(playerid, CS_PrevTag1[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevTag1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevTag1[playerid], 59);
	PlayerTextDrawBoxColor(playerid, CS_PrevTag1[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevTag1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevTag1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevTag1[playerid], 0);

	CS_PrevTag2[playerid] = CreatePlayerTextDraw(playerid, 401.000000, 374.000000, "discord.com/invite/En2QDFZ");
	PlayerTextDrawFont(playerid, CS_PrevTag2[playerid], 2);
	PlayerTextDrawLetterSize(playerid, CS_PrevTag2[playerid], 0.141662, 0.750000);
	PlayerTextDrawTextSize(playerid, CS_PrevTag2[playerid], 443.500000, 127.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevTag2[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevTag2[playerid], 1);
	PlayerTextDrawAlignment(playerid, CS_PrevTag2[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevTag2[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevTag2[playerid], 50);
	PlayerTextDrawBoxColor(playerid, CS_PrevTag2[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevTag2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevTag2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevTag2[playerid], 0);

	CS_PreviewClass[playerid] = CreatePlayerTextDraw(playerid, 62.000000, 81.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, CS_PreviewClass[playerid], 5);
	PlayerTextDrawLetterSize(playerid, CS_PreviewClass[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, CS_PreviewClass[playerid], 226.000000, 314.000000);
	PlayerTextDrawSetOutline(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PreviewClass[playerid], 1);
	PlayerTextDrawColor(playerid, CS_PreviewClass[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawBoxColor(playerid, CS_PreviewClass[playerid], 255);
	PlayerTextDrawUseBox(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PreviewClass[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, CS_PreviewClass[playerid], 0);
	PlayerTextDrawSetPreviewRot(playerid, CS_PreviewClass[playerid], -10.000000, 0.000000, 3.000000, 0.949999);
	PlayerTextDrawSetPreviewVehCol(playerid, CS_PreviewClass[playerid], 1, 1);

	CS_PreviewName[playerid] = CreatePlayerTextDraw(playerid, 224.000000, 152.000000, "Name:");
	PlayerTextDrawFont(playerid, CS_PreviewName[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PreviewName[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, CS_PreviewName[playerid], 298.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CS_PreviewName[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PreviewName[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PreviewName[playerid], 1);
	PlayerTextDrawColor(playerid, CS_PreviewName[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PreviewName[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PreviewName[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PreviewName[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PreviewName[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PreviewName[playerid], 0);

	CS_PrevClass[playerid] = CreatePlayerTextDraw(playerid, 224.000000, 187.000000, "Class:");
	PlayerTextDrawFont(playerid, CS_PrevClass[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevClass[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, CS_PrevClass[playerid], 298.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevClass[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevClass[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevClass[playerid], 1);
	PlayerTextDrawColor(playerid, CS_PrevClass[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevClass[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevClass[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevClass[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevClass[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevClass[playerid], 0);

	CS_PrevNameInput[playerid] = CreatePlayerTextDraw(playerid, 304.000000, 154.000000, Player[playerid][user_name]);
	PlayerTextDrawFont(playerid, CS_PrevNameInput[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevNameInput[playerid], 0.404166, 1.649999);
	PlayerTextDrawTextSize(playerid, CS_PrevNameInput[playerid], 440.500000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevNameInput[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevNameInput[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevNameInput[playerid], 1);
	PlayerTextDrawColor(playerid, CS_PrevNameInput[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevNameInput[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevNameInput[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevNameInput[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CS_PrevNameInput[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevNameInput[playerid], 0);

	CS_PrevClassInput[playerid] = CreatePlayerTextDraw(playerid, 304.000000, 189.000000, "Lorem ipsum");
	PlayerTextDrawFont(playerid, CS_PrevClassInput[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevClassInput[playerid], 0.404166, 1.649999);
	PlayerTextDrawTextSize(playerid, CS_PrevClassInput[playerid], 440.500000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevClassInput[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevClassInput[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevClassInput[playerid], 1);
	PlayerTextDrawColor(playerid, CS_PrevClassInput[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevClassInput[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevClassInput[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevClassInput[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CS_PrevClassInput[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevClassInput[playerid], 0);

	CS_PrevRulesHeader[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 213.000000, "Rules:");
	PlayerTextDrawFont(playerid, CS_PrevRulesHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, CS_PrevRulesHeader[playerid], 0.458330, 1.899996);
	PlayerTextDrawTextSize(playerid, CS_PrevRulesHeader[playerid], 400.500000, 44.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevRulesHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevRulesHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevRulesHeader[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevRulesHeader[playerid], -741092353);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevRulesHeader[playerid], 70);
	PlayerTextDrawBoxColor(playerid, CS_PrevRulesHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevRulesHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevRulesHeader[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevRulesHeader[playerid], 0);

	CS_PrevRule1[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 235.000000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	PlayerTextDrawFont(playerid, CS_PrevRule1[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CS_PrevRule1[playerid], 0.183332, 1.250000);
	PlayerTextDrawTextSize(playerid, CS_PrevRule1[playerid], 451.000000, 200.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevRule1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CS_PrevRule1[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevRule1[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevRule1[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevRule1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevRule1[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevRule1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevRule1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevRule1[playerid], 0);

	CS_PrevRule2[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 258.000000, "Fusce facilisis erat vel sapien sollicitudin porttitor.");
	PlayerTextDrawFont(playerid, CS_PrevRule2[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CS_PrevRule2[playerid], 0.183332, 1.250000);
	PlayerTextDrawTextSize(playerid, CS_PrevRule2[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevRule2[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CS_PrevRule2[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevRule2[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevRule2[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevRule2[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevRule2[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevRule2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevRule2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevRule2[playerid], 0);

	CS_PrevRule3[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 280.000000, "Quisque venenatis urna quis sapien elementum commodo.");
	PlayerTextDrawFont(playerid, CS_PrevRule3[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CS_PrevRule3[playerid], 0.183332, 1.250000);
	PlayerTextDrawTextSize(playerid, CS_PrevRule3[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevRule3[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CS_PrevRule3[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevRule3[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevRule3[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevRule3[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevRule3[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevRule3[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevRule3[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevRule3[playerid], 0);

	CS_PrevRule4[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 301.000000, "Aenean blandit enim id lorem semper, eget blandit libero consectetur.");
	PlayerTextDrawFont(playerid, CS_PrevRule4[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CS_PrevRule4[playerid], 0.183332, 1.250000);
	PlayerTextDrawTextSize(playerid, CS_PrevRule4[playerid], 448.500000, 203.000000);
	PlayerTextDrawSetOutline(playerid, CS_PrevRule4[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CS_PrevRule4[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevRule4[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevRule4[playerid], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevRule4[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevRule4[playerid], 50);
	PlayerTextDrawUseBox(playerid, CS_PrevRule4[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CS_PrevRule4[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevRule4[playerid], 0);

	CS_PrevBack[playerid] = CreatePlayerTextDraw(playerid, 260.000000, 338.000000, "BACK");
	PlayerTextDrawFont(playerid, CS_PrevBack[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevBack[playerid], 0.462498, 1.750000);
	PlayerTextDrawTextSize(playerid, CS_PrevBack[playerid], 16.500000, 90.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevBack[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevBack[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevBack[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevBack[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevBack[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevBack[playerid], -397912577);
	PlayerTextDrawUseBox(playerid, CS_PrevBack[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CS_PrevBack[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevBack[playerid], 1);

	CS_PrevProceed[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 338.000000, "Proceed");
	PlayerTextDrawFont(playerid, CS_PrevProceed[playerid], 3);
	PlayerTextDrawLetterSize(playerid, CS_PrevProceed[playerid], 0.462498, 1.750000);
	PlayerTextDrawTextSize(playerid, CS_PrevProceed[playerid], 16.500000, 90.500000);
	PlayerTextDrawSetOutline(playerid, CS_PrevProceed[playerid], 1);
	PlayerTextDrawSetShadow(playerid, CS_PrevProceed[playerid], 0);
	PlayerTextDrawAlignment(playerid, CS_PrevProceed[playerid], 2);
	PlayerTextDrawColor(playerid, CS_PrevProceed[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CS_PrevProceed[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CS_PrevProceed[playerid], 830864639);
	PlayerTextDrawUseBox(playerid, CS_PrevProceed[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CS_PrevProceed[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CS_PrevProceed[playerid], 1);
}

csPrevTextDrawDestroy(playerid)
{
	PlayerTextDrawDestroy(playerid, CS_PrevBox[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevHeader[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevTag1[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevTag2[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PreviewClass[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PreviewName[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevClass[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevNameInput[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevClassInput[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevRulesHeader[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevRule1[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevRule2[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevRule3[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevRule4[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevBack[playerid]);
	PlayerTextDrawDestroy(playerid, CS_PrevProceed[playerid]);
}

ShowPlayerClassPreview(playerid)
{
	PlayerTextDrawShow(playerid, CS_PrevBox[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevHeader[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevTag1[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevTag2[playerid]);
	PlayerTextDrawShow(playerid, CS_PreviewClass[playerid]);
	PlayerTextDrawShow(playerid, CS_PreviewName[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevClass[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevNameInput[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevClassInput[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevRulesHeader[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevRule1[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevRule2[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevRule3[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevRule4[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevBack[playerid]);
	PlayerTextDrawShow(playerid, CS_PrevProceed[playerid]);
	SelectTextDraw(playerid, 0xFF0000FF);
}

HidePlayerClassPreview(playerid)
{
	PlayerTextDrawHide(playerid, CS_PrevBox[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevHeader[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevTag1[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevTag2[playerid]);
	PlayerTextDrawHide(playerid, CS_PreviewClass[playerid]);
	PlayerTextDrawHide(playerid, CS_PreviewName[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevClass[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevNameInput[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevClassInput[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevRulesHeader[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevRule1[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevRule2[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevRule3[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevRule4[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevBack[playerid]);
	PlayerTextDrawHide(playerid, CS_PrevProceed[playerid]);
}