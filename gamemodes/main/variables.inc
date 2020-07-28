new
	MySQL: Database
;

enum E_PLAYERS
{
	user_id,
	user_name[MAX_PLAYER_NAME],
	user_ip,
	user_playhours,
	Tutorial,
	user_class,
	user_skin,


	Cache: Cache_ID,
	bool: IsLoggedIn,
	LoginAttempts,
	LoginTimer
};

enum
{
	DIALOG_UNUSED,

	DIALOG_LOGIN,
	DIALOG_REGISTER,
	DIALOG_PRETUTORIAL,
	DIALOG_TUTORIAL0,
	DIALOG_TUTORIAL1,
	/*.......*/
	DIALOG_TUTORIAL5
};

new Player[MAX_PLAYERS][E_PLAYERS];

new g_MysqlRaceCheck[MAX_PLAYERS];

new
	PlayerText:Connecting_TD_Message[MAX_PLAYERS][6],
	Text:PublicTD[4];

new Vehicle[MAX_PLAYERS];