

#include "classPreview"

new PlayerText:CSbox[MAX_PLAYERS];
new PlayerText:CSheader[MAX_PLAYERS];
new PlayerText:CStag1[MAX_PLAYERS];
new PlayerText:CStag2[MAX_PLAYERS];
new PlayerText:CS_CivModel[MAX_PLAYERS];
new PlayerText:CS_PoliceModel[MAX_PLAYERS];
new PlayerText:CS_FbiModel[MAX_PLAYERS];
new PlayerText:CS_ArmyModel[MAX_PLAYERS];
new PlayerText:CS_CivLeft[MAX_PLAYERS];
new PlayerText:CS_CivRight[MAX_PLAYERS];
new PlayerText:CS_PoliceLeft[MAX_PLAYERS];
new PlayerText:CS_PoliceRight[MAX_PLAYERS];
new PlayerText:CS_FbiLeft[MAX_PLAYERS];
new PlayerText:CS_FbiRight[MAX_PLAYERS];
new PlayerText:CS_ArmyLeft[MAX_PLAYERS];
new PlayerText:CS_ArmyRight[MAX_PLAYERS];
new PlayerText:CS_CivHeader[MAX_PLAYERS];
new PlayerText:CS_PoliceHeader[MAX_PLAYERS];
new PlayerText:CS_FbiHeader[MAX_PLAYERS];
new PlayerText:CS_ArmyHeader[MAX_PLAYERS];

new skinModelSeletected[MAX_PLAYERS];

new currentCivSkinSelected[MAX_PLAYERS];
new currentPoliceSkinSelected[MAX_PLAYERS];
new currentFbiSkinSelected[MAX_PLAYERS];
new currentArmySkinSelected[MAX_PLAYERS];

new skinSelectionCivModels[] = {
    250, 223, 204, 206,
    243, 192, 193, 194

};

new skinSelectionPoliceModels[] = {
    280, 281, 282, 283,
    284, 288, 306, 307, 308
};

new skinSelectionFbiModels[] = {
    286, 285, 93, 165, 166, 
    163, 164
};

new skinSelectionArmyModels[] = {
    287, 191, 179
};

GetNextModel(playerid, const class[])
{
    switch(YHash(class))
    {
        case _H<CLASS_CIVILIAN>:
        {
            currentCivSkinSelected[playerid]++;
            if(currentCivSkinSelected[playerid] == sizeof(skinSelectionCivModels)) currentCivSkinSelected[playerid] = 0;
            return skinSelectionCivModels[currentCivSkinSelected[playerid]];
        }
        case _H<CLASS_POLICE>:
        {
            currentPoliceSkinSelected[playerid]++;
            if(currentPoliceSkinSelected[playerid] == sizeof(skinSelectionPoliceModels)) currentPoliceSkinSelected[playerid] = 0;
            return skinSelectionPoliceModels[currentPoliceSkinSelected[playerid]];
        }
        case _H<CLASS_FBI>:
        {
            currentFbiSkinSelected[playerid]++;
            if(currentFbiSkinSelected[playerid] == sizeof(skinSelectionFbiModels)) currentFbiSkinSelected[playerid] = 0;
            return skinSelectionFbiModels[currentFbiSkinSelected[playerid]];
        }
        case _H<CLASS_ARMY>:
        {
            currentArmySkinSelected[playerid]++;
            if(currentArmySkinSelected[playerid] == sizeof(skinSelectionArmyModels)) currentArmySkinSelected[playerid] = 0;
            return skinSelectionArmyModels[currentArmySkinSelected[playerid]];        
        }
    }
    return 0;
}

GetPrevModel(playerid, const class[])
{
    switch(YHash(class))
    {
        case _H<CLASS_CIVILIAN>:
        {
            if(currentCivSkinSelected[playerid] == 0) currentCivSkinSelected[playerid] = sizeof(skinSelectionCivModels);
            currentCivSkinSelected[playerid]--;
            return skinSelectionCivModels[currentCivSkinSelected[playerid]];
        }
        case _H<CLASS_POLICE>:
        {
            if(currentPoliceSkinSelected[playerid] == 0) currentPoliceSkinSelected[playerid] = sizeof(skinSelectionPoliceModels);
            currentPoliceSkinSelected[playerid]--;
            return skinSelectionPoliceModels[currentPoliceSkinSelected[playerid]];
        }
        case _H<CLASS_FBI>:
        {
            if(currentFbiSkinSelected[playerid] == 0) currentFbiSkinSelected[playerid] = sizeof(skinSelectionFbiModels);
            currentFbiSkinSelected[playerid]--;
            return skinSelectionFbiModels[currentFbiSkinSelected[playerid]];
        }
        case _H<CLASS_ARMY>:
        {
            if(currentArmySkinSelected[playerid] == 0) currentArmySkinSelected[playerid] = sizeof(skinSelectionArmyModels);
            currentArmySkinSelected[playerid]--;
            return skinSelectionArmyModels[currentArmySkinSelected[playerid]];
        }
    }
    return 0;
}

resetSkinSelect(playerid)
{
    skinModelSeletected[playerid] = 0;
    currentCivSkinSelected[playerid] = 0;
    currentPoliceSkinSelected[playerid] = 0;
    currentFbiSkinSelected[playerid] = 0;
    currentArmySkinSelected[playerid] = 0;
}

YCMD:myclass(playerid, params[], help) 
{
    new string[60];
    format( string, sizeof( string ),"Your current class is: %i, skin id: %i", Player[playerid][Class], Player[playerid][Skin]);
    SCM(playerid, COLOR_RED, string);
    return 1;
}


csTextDrawCreate(playerid)
{
    resetSkinSelect(playerid);

    CSbox[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 123.000000, "_");
    PlayerTextDrawFont(playerid, CSbox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, CSbox[playerid], 0.741666, 26.949996);
    PlayerTextDrawTextSize(playerid, CSbox[playerid], 244.500000, 445.000000);
    PlayerTextDrawSetOutline(playerid, CSbox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CSbox[playerid], 0);
    PlayerTextDrawAlignment(playerid, CSbox[playerid], 2);
    PlayerTextDrawColor(playerid, CSbox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CSbox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CSbox[playerid], 1077890148);
    PlayerTextDrawUseBox(playerid, CSbox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, CSbox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CSbox[playerid], 0);

    CSheader[playerid] = CreatePlayerTextDraw(playerid, 310.000000, 101.000000, "Class Select");
    PlayerTextDrawFont(playerid, CSheader[playerid], 0);
    PlayerTextDrawLetterSize(playerid, CSheader[playerid], 0.745831, 3.399996);
    PlayerTextDrawTextSize(playerid, CSheader[playerid], 405.000000, 159.500000);
    PlayerTextDrawSetOutline(playerid, CSheader[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CSheader[playerid], 0);
    PlayerTextDrawAlignment(playerid, CSheader[playerid], 2);
    PlayerTextDrawColor(playerid, CSheader[playerid], 383827455);
    PlayerTextDrawBackgroundColor(playerid, CSheader[playerid], 70);
    PlayerTextDrawBoxColor(playerid, CSheader[playerid], 50);
    PlayerTextDrawUseBox(playerid, CSheader[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CSheader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CSheader[playerid], 0);

    CStag1[playerid] = CreatePlayerTextDraw(playerid, 488.000000, 361.000000, "Manila: Cops n' Robbers");
    PlayerTextDrawFont(playerid, CStag1[playerid], 3);
    PlayerTextDrawLetterSize(playerid, CStag1[playerid], 0.245830, 1.450000);
    PlayerTextDrawTextSize(playerid, CStag1[playerid], 568.500000, 181.000000);
    PlayerTextDrawSetOutline(playerid, CStag1[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CStag1[playerid], 1);
    PlayerTextDrawAlignment(playerid, CStag1[playerid], 2);
    PlayerTextDrawColor(playerid, CStag1[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CStag1[playerid], 59);
    PlayerTextDrawBoxColor(playerid, CStag1[playerid], 50);
    PlayerTextDrawUseBox(playerid, CStag1[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CStag1[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CStag1[playerid], 0);

    CStag2[playerid] = CreatePlayerTextDraw(playerid, 488.000000, 374.000000, SERVER_DISCORD);
    PlayerTextDrawFont(playerid, CStag2[playerid], 2);
    PlayerTextDrawLetterSize(playerid, CStag2[playerid], 0.141663, 0.750000);
    PlayerTextDrawTextSize(playerid, CStag2[playerid], 443.500000, 127.500000);
    PlayerTextDrawSetOutline(playerid, CStag2[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CStag2[playerid], 1);
    PlayerTextDrawAlignment(playerid, CStag2[playerid], 2);
    PlayerTextDrawColor(playerid, CStag2[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CStag2[playerid], 50);
    PlayerTextDrawBoxColor(playerid, CStag2[playerid], 50);
    PlayerTextDrawUseBox(playerid, CStag2[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CStag2[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CStag2[playerid], 0);

    CS_CivModel[playerid] = CreatePlayerTextDraw(playerid, 107.000000, 176.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CS_CivModel[playerid], 5);
    PlayerTextDrawLetterSize(playerid, CS_CivModel[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CS_CivModel[playerid], 99.500000, 127.500000);
    PlayerTextDrawSetOutline(playerid, CS_CivModel[playerid], 0);
    PlayerTextDrawSetShadow(playerid, CS_CivModel[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_CivModel[playerid], 1);
    PlayerTextDrawColor(playerid, CS_CivModel[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_CivModel[playerid], 0);
    PlayerTextDrawBoxColor(playerid, CS_CivModel[playerid], 42);
    PlayerTextDrawUseBox(playerid, CS_CivModel[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_CivModel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_CivModel[playerid], 1);
    PlayerTextDrawSetPreviewModel(playerid, CS_CivModel[playerid], 250);
    PlayerTextDrawSetPreviewRot(playerid, CS_CivModel[playerid], -10.000000, 0.000000, -12.000000, 0.910000);
    PlayerTextDrawSetPreviewVehCol(playerid, CS_CivModel[playerid], 1, 1);

    CS_PoliceModel[playerid] = CreatePlayerTextDraw(playerid, 214.000000, 176.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CS_PoliceModel[playerid], 5);
    PlayerTextDrawLetterSize(playerid, CS_PoliceModel[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CS_PoliceModel[playerid], 99.500000, 127.500000);
    PlayerTextDrawSetOutline(playerid, CS_PoliceModel[playerid], 0);
    PlayerTextDrawSetShadow(playerid, CS_PoliceModel[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_PoliceModel[playerid], 1);
    PlayerTextDrawColor(playerid, CS_PoliceModel[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_PoliceModel[playerid], 0);
    PlayerTextDrawBoxColor(playerid, CS_PoliceModel[playerid], 0);
    PlayerTextDrawUseBox(playerid, CS_PoliceModel[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_PoliceModel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_PoliceModel[playerid], 1);
    PlayerTextDrawSetPreviewModel(playerid, CS_PoliceModel[playerid], 280);
    PlayerTextDrawSetPreviewRot(playerid, CS_PoliceModel[playerid], -10.000000, 0.000000, -12.000000, 0.910000);
    PlayerTextDrawSetPreviewVehCol(playerid, CS_PoliceModel[playerid], 1, 1);

    CS_FbiModel[playerid] = CreatePlayerTextDraw(playerid, 322.000000, 176.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CS_FbiModel[playerid], 5);
    PlayerTextDrawLetterSize(playerid, CS_FbiModel[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CS_FbiModel[playerid], 99.500000, 127.500000);
    PlayerTextDrawSetOutline(playerid, CS_FbiModel[playerid], 0);
    PlayerTextDrawSetShadow(playerid, CS_FbiModel[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_FbiModel[playerid], 1);
    PlayerTextDrawColor(playerid, CS_FbiModel[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_FbiModel[playerid], 0);
    PlayerTextDrawBoxColor(playerid, CS_FbiModel[playerid], 42);
    PlayerTextDrawUseBox(playerid, CS_FbiModel[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_FbiModel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_FbiModel[playerid], 1);
    PlayerTextDrawSetPreviewModel(playerid, CS_FbiModel[playerid], 286);
    PlayerTextDrawSetPreviewRot(playerid, CS_FbiModel[playerid], -10.000000, 0.000000, -12.000000, 0.910000);
    PlayerTextDrawSetPreviewVehCol(playerid, CS_FbiModel[playerid], 1, 1);

    CS_ArmyModel[playerid] = CreatePlayerTextDraw(playerid, 430.000000, 176.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, CS_ArmyModel[playerid], 5);
    PlayerTextDrawLetterSize(playerid, CS_ArmyModel[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, CS_ArmyModel[playerid], 99.500000, 127.500000);
    PlayerTextDrawSetOutline(playerid, CS_ArmyModel[playerid], 0);
    PlayerTextDrawSetShadow(playerid, CS_ArmyModel[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_ArmyModel[playerid], 1);
    PlayerTextDrawColor(playerid, CS_ArmyModel[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_ArmyModel[playerid], 0);
    PlayerTextDrawBoxColor(playerid, CS_ArmyModel[playerid], 42);
    PlayerTextDrawUseBox(playerid, CS_ArmyModel[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_ArmyModel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_ArmyModel[playerid], 1);
    PlayerTextDrawSetPreviewModel(playerid, CS_ArmyModel[playerid], 287);
    PlayerTextDrawSetPreviewRot(playerid, CS_ArmyModel[playerid], -10.000000, 0.000000, -12.000000, 0.910000);
    PlayerTextDrawSetPreviewVehCol(playerid, CS_ArmyModel[playerid], 1, 1);

    CS_CivLeft[playerid] = CreatePlayerTextDraw(playerid, 124.000000, 303.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, CS_CivLeft[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_CivLeft[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_CivLeft[playerid], 31.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, CS_CivLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_CivLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_CivLeft[playerid], 1);
    PlayerTextDrawColor(playerid, CS_CivLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_CivLeft[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_CivLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_CivLeft[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_CivLeft[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_CivLeft[playerid], 1);

    CS_CivRight[playerid] = CreatePlayerTextDraw(playerid, 162.000000, 303.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, CS_CivRight[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_CivRight[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_CivRight[playerid], 31.500000, 35.000000);
    PlayerTextDrawSetOutline(playerid, CS_CivRight[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_CivRight[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_CivRight[playerid], 1);
    PlayerTextDrawColor(playerid, CS_CivRight[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_CivRight[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_CivRight[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_CivRight[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_CivRight[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_CivRight[playerid], 1);

    CS_PoliceLeft[playerid] = CreatePlayerTextDraw(playerid, 232.000000, 303.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, CS_PoliceLeft[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_PoliceLeft[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_PoliceLeft[playerid], 31.000000, 33.000000);
    PlayerTextDrawSetOutline(playerid, CS_PoliceLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_PoliceLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_PoliceLeft[playerid], 1);
    PlayerTextDrawColor(playerid, CS_PoliceLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_PoliceLeft[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_PoliceLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_PoliceLeft[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_PoliceLeft[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_PoliceLeft[playerid], 1);

    CS_PoliceRight[playerid] = CreatePlayerTextDraw(playerid, 267.000000, 303.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, CS_PoliceRight[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_PoliceRight[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_PoliceRight[playerid], 32.000000, 33.500000);
    PlayerTextDrawSetOutline(playerid, CS_PoliceRight[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_PoliceRight[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_PoliceRight[playerid], 1);
    PlayerTextDrawColor(playerid, CS_PoliceRight[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_PoliceRight[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_PoliceRight[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_PoliceRight[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_PoliceRight[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_PoliceRight[playerid], 1);

    CS_FbiLeft[playerid] = CreatePlayerTextDraw(playerid, 343.000000, 303.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, CS_FbiLeft[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_FbiLeft[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_FbiLeft[playerid], 32.500000, 32.000000);
    PlayerTextDrawSetOutline(playerid, CS_FbiLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_FbiLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_FbiLeft[playerid], 1);
    PlayerTextDrawColor(playerid, CS_FbiLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_FbiLeft[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_FbiLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_FbiLeft[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_FbiLeft[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_FbiLeft[playerid], 1);

    CS_FbiRight[playerid] = CreatePlayerTextDraw(playerid, 379.000000, 303.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, CS_FbiRight[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_FbiRight[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_FbiRight[playerid], 33.000000, 32.000000);
    PlayerTextDrawSetOutline(playerid, CS_FbiRight[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_FbiRight[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_FbiRight[playerid], 1);
    PlayerTextDrawColor(playerid, CS_FbiRight[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_FbiRight[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_FbiRight[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_FbiRight[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_FbiRight[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_FbiRight[playerid], 1);

    CS_ArmyLeft[playerid] = CreatePlayerTextDraw(playerid, 452.000000, 303.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, CS_ArmyLeft[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_ArmyLeft[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_ArmyLeft[playerid], 31.500000, 32.500000);
    PlayerTextDrawSetOutline(playerid, CS_ArmyLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_ArmyLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_ArmyLeft[playerid], 1);
    PlayerTextDrawColor(playerid, CS_ArmyLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_ArmyLeft[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_ArmyLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_ArmyLeft[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_ArmyLeft[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_ArmyLeft[playerid], 1);

    CS_ArmyRight[playerid] = CreatePlayerTextDraw(playerid, 487.000000, 303.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, CS_ArmyRight[playerid], 4);
    PlayerTextDrawLetterSize(playerid, CS_ArmyRight[playerid], 0.554166, 2.849997);
    PlayerTextDrawTextSize(playerid, CS_ArmyRight[playerid], 34.500000, 32.500000);
    PlayerTextDrawSetOutline(playerid, CS_ArmyRight[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_ArmyRight[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_ArmyRight[playerid], 1);
    PlayerTextDrawColor(playerid, CS_ArmyRight[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_ArmyRight[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_ArmyRight[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_ArmyRight[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_ArmyRight[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_ArmyRight[playerid], 1);

    CS_CivHeader[playerid] = CreatePlayerTextDraw(playerid, 158.000000, 150.000000, "Civilian");
    PlayerTextDrawFont(playerid, CS_CivHeader[playerid], 3);
    PlayerTextDrawLetterSize(playerid, CS_CivHeader[playerid], 0.466666, 1.700000);
    PlayerTextDrawTextSize(playerid, CS_CivHeader[playerid], 446.500000, 87.500000);
    PlayerTextDrawSetOutline(playerid, CS_CivHeader[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_CivHeader[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_CivHeader[playerid], 2);
    PlayerTextDrawColor(playerid, CS_CivHeader[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_CivHeader[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_CivHeader[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_CivHeader[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_CivHeader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_CivHeader[playerid], 0);

    CS_PoliceHeader[playerid] = CreatePlayerTextDraw(playerid, 263.000000, 150.000000, "Police");
    PlayerTextDrawFont(playerid, CS_PoliceHeader[playerid], 3);
    PlayerTextDrawLetterSize(playerid, CS_PoliceHeader[playerid], 0.466666, 1.700000);
    PlayerTextDrawTextSize(playerid, CS_PoliceHeader[playerid], 446.500000, 87.500000);
    PlayerTextDrawSetOutline(playerid, CS_PoliceHeader[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_PoliceHeader[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_PoliceHeader[playerid], 2);
    PlayerTextDrawColor(playerid, CS_PoliceHeader[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_PoliceHeader[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_PoliceHeader[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_PoliceHeader[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_PoliceHeader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_PoliceHeader[playerid], 0);

    CS_FbiHeader[playerid] = CreatePlayerTextDraw(playerid, 372.000000, 150.000000, "FBI");
    PlayerTextDrawFont(playerid, CS_FbiHeader[playerid], 3);
    PlayerTextDrawLetterSize(playerid, CS_FbiHeader[playerid], 0.466666, 1.700000);
    PlayerTextDrawTextSize(playerid, CS_FbiHeader[playerid], 446.500000, 87.500000);
    PlayerTextDrawSetOutline(playerid, CS_FbiHeader[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_FbiHeader[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_FbiHeader[playerid], 2);
    PlayerTextDrawColor(playerid, CS_FbiHeader[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_FbiHeader[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_FbiHeader[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_FbiHeader[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_FbiHeader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_FbiHeader[playerid], 0);

    CS_ArmyHeader[playerid] = CreatePlayerTextDraw(playerid, 481.000000, 151.000000, "Armed Forces");
    PlayerTextDrawFont(playerid, CS_ArmyHeader[playerid], 3);
    PlayerTextDrawLetterSize(playerid, CS_ArmyHeader[playerid], 0.312500, 1.450000);
    PlayerTextDrawTextSize(playerid, CS_ArmyHeader[playerid], 448.500000, 136.000000);
    PlayerTextDrawSetOutline(playerid, CS_ArmyHeader[playerid], 1);
    PlayerTextDrawSetShadow(playerid, CS_ArmyHeader[playerid], 0);
    PlayerTextDrawAlignment(playerid, CS_ArmyHeader[playerid], 2);
    PlayerTextDrawColor(playerid, CS_ArmyHeader[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, CS_ArmyHeader[playerid], 255);
    PlayerTextDrawBoxColor(playerid, CS_ArmyHeader[playerid], 50);
    PlayerTextDrawUseBox(playerid, CS_ArmyHeader[playerid], 0);
    PlayerTextDrawSetProportional(playerid, CS_ArmyHeader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CS_ArmyHeader[playerid], 0);
}

csTextDrawDestroy(playerid)
{
    PlayerTextDrawDestroy(playerid, CSbox[playerid]);
    PlayerTextDrawDestroy(playerid, CSheader[playerid]);
    PlayerTextDrawDestroy(playerid, CStag1[playerid]);
    PlayerTextDrawDestroy(playerid, CStag2[playerid]);
    PlayerTextDrawDestroy(playerid, CS_CivModel[playerid]);
    PlayerTextDrawDestroy(playerid, CS_PoliceModel[playerid]);
    PlayerTextDrawDestroy(playerid, CS_FbiModel[playerid]);
    PlayerTextDrawDestroy(playerid, CS_ArmyModel[playerid]);
    PlayerTextDrawDestroy(playerid, CS_CivLeft[playerid]);
    PlayerTextDrawDestroy(playerid, CS_CivRight[playerid]);
    PlayerTextDrawDestroy(playerid, CS_PoliceLeft[playerid]);
    PlayerTextDrawDestroy(playerid, CS_PoliceRight[playerid]);
    PlayerTextDrawDestroy(playerid, CS_FbiLeft[playerid]);
    PlayerTextDrawDestroy(playerid, CS_FbiRight[playerid]);
    PlayerTextDrawDestroy(playerid, CS_ArmyLeft[playerid]);
    PlayerTextDrawDestroy(playerid, CS_ArmyRight[playerid]);
    PlayerTextDrawDestroy(playerid, CS_CivHeader[playerid]);
    PlayerTextDrawDestroy(playerid, CS_PoliceHeader[playerid]);
    PlayerTextDrawDestroy(playerid, CS_FbiHeader[playerid]);
    PlayerTextDrawDestroy(playerid, CS_ArmyHeader[playerid]);
}


HidePlayerClassSelect(playerid)
{
    PlayerTextDrawHide(playerid, CSbox[playerid]);
    PlayerTextDrawHide(playerid, CSheader[playerid]);
    PlayerTextDrawHide(playerid, CStag1[playerid]);
    PlayerTextDrawHide(playerid, CStag2[playerid]);
    PlayerTextDrawHide(playerid, CS_CivModel[playerid]);
    PlayerTextDrawHide(playerid, CS_PoliceModel[playerid]);
    PlayerTextDrawHide(playerid, CS_FbiModel[playerid]);
    PlayerTextDrawHide(playerid, CS_ArmyModel[playerid]);
    PlayerTextDrawHide(playerid, CS_CivLeft[playerid]);
    PlayerTextDrawHide(playerid, CS_CivRight[playerid]);
    PlayerTextDrawHide(playerid, CS_PoliceLeft[playerid]);
    PlayerTextDrawHide(playerid, CS_PoliceRight[playerid]);
    PlayerTextDrawHide(playerid, CS_FbiLeft[playerid]);
    PlayerTextDrawHide(playerid, CS_FbiRight[playerid]);
    PlayerTextDrawHide(playerid, CS_ArmyLeft[playerid]);
    PlayerTextDrawHide(playerid, CS_ArmyRight[playerid]);
    PlayerTextDrawHide(playerid, CS_CivHeader[playerid]);
    PlayerTextDrawHide(playerid, CS_PoliceHeader[playerid]);
    PlayerTextDrawHide(playerid, CS_FbiHeader[playerid]);
    PlayerTextDrawHide(playerid, CS_ArmyHeader[playerid]);
}

ShowPlayerClassSelect(playerid)
{
    HidePlayerClassSelect(playerid);
    PlayerTextDrawShow(playerid, CSbox[playerid]);
    PlayerTextDrawShow(playerid, CSheader[playerid]);
    PlayerTextDrawShow(playerid, CStag1[playerid]);
    PlayerTextDrawShow(playerid, CStag2[playerid]);
    PlayerTextDrawShow(playerid, CS_CivModel[playerid]);
    PlayerTextDrawShow(playerid, CS_PoliceModel[playerid]);
    PlayerTextDrawShow(playerid, CS_FbiModel[playerid]);
    PlayerTextDrawShow(playerid, CS_ArmyModel[playerid]);
    PlayerTextDrawShow(playerid, CS_CivLeft[playerid]);
    PlayerTextDrawShow(playerid, CS_CivRight[playerid]);
    PlayerTextDrawShow(playerid, CS_PoliceLeft[playerid]);
    PlayerTextDrawShow(playerid, CS_PoliceRight[playerid]);
    PlayerTextDrawShow(playerid, CS_FbiLeft[playerid]);
    PlayerTextDrawShow(playerid, CS_FbiRight[playerid]);
    PlayerTextDrawShow(playerid, CS_ArmyLeft[playerid]);
    PlayerTextDrawShow(playerid, CS_ArmyRight[playerid]);
    PlayerTextDrawShow(playerid, CS_CivHeader[playerid]);
    PlayerTextDrawShow(playerid, CS_PoliceHeader[playerid]);
    PlayerTextDrawShow(playerid, CS_FbiHeader[playerid]);
    PlayerTextDrawShow(playerid, CS_ArmyHeader[playerid]);
    SelectTextDraw(playerid, 0xA3B4C5FF);
}