public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(_:playertextid != INVALID_TEXT_DRAW)
    {
        if(playertextid == Register_PasswordInput[playerid])
        {
            Player[playerid][TempLoginText] = 0;
            new string[125];
            format(string, sizeof string, "{F9DC5C} Welcome {009FB7}%s{F9DC5C}, you can register by entering your password in the field below:", Player[playerid][user_name]);
            ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR - Registration", string, "Register", "Abort");
            
            return 1;
        }
        else if(playertextid == Register_Proceed[playerid])
        {
            if (strlen(Player[playerid][TempLoginText]) <= 5) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR - Registration", "Your password must be longer than 5 characters!\nPlease enter your password in the field below:", "Register", "Abort");

            bcrypt_hash(Player[playerid][TempLoginText], BCRYPT_COST, "OnPasswordHashed", "d", playerid);
            
            return 1;
        }
        else if(playertextid == Login_PasswordInput[playerid])
        {
            Player[playerid][TempLoginText] = 0;
            new string[125];
            format(string, sizeof string, "{F9DC5C}This account {009FB7}(%s) {F9DC5C}is registered. Please login by entering your password in the field below:", Player[playerid][user_name]);
            ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{3185FC}MNL:CNR - Login", string, "Login", "Abort");
            
            return 1;
        }
        else if(playertextid == Login_Proceed[playerid])
        {
            new query[300], Password[BCRYPT_HASH_LENGTH];
            mysql_format(Database, query, sizeof(query), "SELECT `Password` FROM `players` WHERE `Username` = '%e'", Player[playerid][user_name]);
            mysql_query(Database, query);
            cache_get_value_name(0, "Password", Password, BCRYPT_HASH_LENGTH);
            bcrypt_check(Player[playerid][TempLoginText], Password, "OnPasswordChecked", "d", playerid);
            return 1;
        }
        /////////////////////////PREVIEW MENU(CONFIRMATION) TEXTDRAW
        else if(playertextid == CS_PrevBack[playerid])
        {
            HidePlayerClassPreview(playerid);
            ShowPlayerClassSelect(playerid);
            
            return 1;
        }
        else if(playertextid == CS_PrevProceed[playerid])
        {
            HidePlayerClassPreview(playerid);
            CancelSelectTextDraw(playerid);
            csPrevTextDrawDestroy(playerid);
            csTextDrawDestroy(playerid);
            ShowPlayerDialog(playerid, DIALOG_PRETUTORIAL, DIALOG_STYLE_MSGBOX, "{3185FC}MNL:CNR - Registration", "{F9DC5C}Account successfully registered, you will proceed to the tutorial.", "Okay", "");
            return 1;
        }
        ////////////////////////////CIVILIAN MODELSSSS
        else if(playertextid == CS_CivModel[playerid])
        {
            skinModelSeletected[playerid] = skinSelectionCivModels[currentCivSkinSelected[playerid]];
            Player[playerid][user_skin] = skinModelSeletected[playerid];
            Player[playerid][user_class] = CLASS_CIVILIAN;
            SetPrevClassInput(playerid, CLASS_CIVILIAN);
            PlayerTextDrawSetPreviewModel(playerid, CS_PreviewClass[playerid], Player[playerid][user_skin]);
            HidePlayerClassSelect(playerid);
            ShowPlayerClassPreview(playerid);
            return 1;
        }
        else if(playertextid == CS_CivLeft[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_CivModel[playerid], GetPrevModel(playerid, "CLASS_CIVILIAN"));
            ShowPlayerClassSelect(playerid);
            
            return 1;
        }
        else if(playertextid == CS_CivRight[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_CivModel[playerid], GetNextModel(playerid, "CLASS_CIVILIAN"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        //////////////////////////////////POLICE MODELSSSSS
        else if(playertextid == CS_PoliceModel[playerid])
        {
            skinModelSeletected[playerid] = skinSelectionPoliceModels[currentPoliceSkinSelected[playerid]];
            Player[playerid][user_skin] = skinModelSeletected[playerid];
            Player[playerid][user_class] = CLASS_POLICE;
            PlayerTextDrawSetPreviewModel(playerid, CS_PreviewClass[playerid], Player[playerid][user_skin]);
            SetPrevClassInput(playerid, CLASS_POLICE);
            HidePlayerClassSelect(playerid);
            ShowPlayerClassPreview(playerid);
            return 1;
        }
        else if(playertextid == CS_PoliceLeft[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_PoliceModel[playerid], GetPrevModel(playerid, "CLASS_POLICE"));
            ShowPlayerClassSelect(playerid);
            
            return 1;
        }
        else if(playertextid == CS_PoliceRight[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_PoliceModel[playerid], GetNextModel(playerid, "CLASS_POLICE"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        //////////////////////////////////////FBI MODELS
        else if(playertextid == CS_FbiModel[playerid])
        {
            skinModelSeletected[playerid] = skinSelectionFbiModels[currentFbiSkinSelected[playerid]];
            Player[playerid][user_skin] = skinModelSeletected[playerid];
            Player[playerid][user_class] = CLASS_FBI;
            PlayerTextDrawSetPreviewModel(playerid, CS_PreviewClass[playerid], Player[playerid][user_skin]);
            SetPrevClassInput(playerid, CLASS_FBI);
            HidePlayerClassSelect(playerid);
            ShowPlayerClassPreview(playerid);
            return 1;
        }
        else if(playertextid == CS_FbiLeft[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_FbiModel[playerid], GetPrevModel(playerid, "CLASS_FBI"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        else if(playertextid == CS_FbiRight[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_FbiModel[playerid], GetNextModel(playerid, "CLASS_FBI"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        ///////////////////////////////////ARMED FORCES MODELS
        else if(playertextid == CS_ArmyModel[playerid])
        {
            skinModelSeletected[playerid] = skinSelectionArmyModels[currentArmySkinSelected[playerid]];
            Player[playerid][user_skin] = skinModelSeletected[playerid];
            Player[playerid][user_class] = CLASS_ARMY;
            PlayerTextDrawSetPreviewModel(playerid, CS_PreviewClass[playerid], Player[playerid][user_skin]);
            SetPrevClassInput(playerid, CLASS_ARMY);
            HidePlayerClassSelect(playerid);
            ShowPlayerClassPreview(playerid);
            return 1;
        }
        else if(playertextid == CS_ArmyLeft[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_ArmyModel[playerid], GetPrevModel(playerid, "CLASS_ARMY"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        else if(playertextid == CS_ArmyRight[playerid])
        {
            PlayerTextDrawSetPreviewModel(playerid, CS_ArmyModel[playerid], GetNextModel(playerid, "CLASS_ARMY"));
            ShowPlayerClassSelect(playerid);
            return 1;
        }
        HidePlayerClassSelect(playerid);
        HidePlayerClassPreview(playerid);
        CancelSelectTextDraw(playerid); 
    }
    return 0;
}