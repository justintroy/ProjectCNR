#include <YSI_Coding\y_va>

static
    chat_msgOut[144];

stock SendErrorMessage(playerid, const string[]) {
    return SendMsgF(playerid, COLOR_RED, "[ERROR]: "C_WHITE"%s", string);
}

stock SendUsageMessage(playerid, const string[]) {
    return SendMsgF(playerid, COLOR_BLUE, "[USAGE]: "C_WHITE"%s", string);
}

stock SendServerMessage(playerid, const string[]) {
    return SendMsgF(playerid, COLOR_BLUE, "[MNLCNR]: "C_WHITE"%s", string);
}

stock SendAdminAction(playerid, const string[]) {
    return SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: "C_WHITE" %s", string);
}

stock SendErrorMessageF(playerid, const fmat[], {Float,_}:...) {
    formatex(chat_msgOut, sizeof(chat_msgOut), fmat, ___(2));
    return SendErrorMessage(playerid, chat_msgOut);
}

stock SendServerMessageF(playerid, const fmat[], {Float,_}:...) {
    formatex(chat_msgOut, sizeof(chat_msgOut), fmat, ___(2));
    return SendServerMessage(playerid, chat_msgOut);
}

stock SendAdminActionF(playerid, const fmat[], {Float,_}:...) {
    formatex(chat_msgOut, sizeof(chat_msgOut), fmat, ___(2));
    return SendAdminAction(playerid, chat_msgOut);
}

stock SendMsgF(playerid, colour, const fmat[], {Float,_}:...) {
    formatex(chat_msgOut, sizeof(chat_msgOut), fmat, ___(3));
    return SendClientMessage(playerid, colour, chat_msgOut);
}

stock SendMsgAllF(colour, const fmat[], {Float,_}:...) {
    formatex(chat_msgOut, sizeof(chat_msgOut), fmat, ___(2));
    return SendClientMessageToAll(colour, chat_msgOut);
}

