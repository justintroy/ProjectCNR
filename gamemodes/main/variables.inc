new MySQL: Database;

enum E_PLAYERS
{
	ID,
	Username[MAX_PLAYER_NAME],
	IP,
	PlayTime,
	Tutorial,
	Class,
	Skin,
	pAdmin,

	Cache: Cache_ID,
	bool: IsLoggedIn,
	LoginAttempts,
	LoginTimer,
	TempLoginText[128],

	LastCPEntered,

	Tick[2] //anti cmd and chat spam
};
new Player[MAX_PLAYERS][E_PLAYERS];

enum
{
	DIALOG_UNUSED,

	DIALOG_LOGIN,
	DIALOG_REGISTER,
	DIALOG_PRETUTORIAL,
	DIALOG_TUTORIAL0,
	DIALOG_TUTORIAL1,
	/*.......*/
	DIALOG_TUTORIAL5,

	DIALOG_ADMINLOG
};

enum _server
{
	Text:LoadingTD[5],
	AdminLogStartPage, //command YCMD:adminlogs
	AdminLogEndPage
}
new GM[_server];


new g_MysqlRaceCheck[MAX_PLAYERS];

new PlayerText:Connecting_TD_Message[MAX_PLAYERS][6];