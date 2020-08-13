//-----------------------------------------------------MY COLOR SCHEME
#define COLOR_DARK 							0x403F4CFF
#define COLOR_RED 							0xE84855FF
#define COLOR_YELLOW 						0xF9DC5CFF
#define COLOR_BLUE 							0x3185FCFF
#define COLOR_LIGHTBLUE 					0x16E0BDFF

#define COL_DARK 							"{403F4C}"
#define COL_RED 							"{E84855}"
#define COL_YELLOW 							"{F9DC5C}"
#define COL_BLUE 							"{3185FC}"
#define COL_LIGHTBLUE 						"{16E0BD}"

//------------------------------------------------------OTHER DEFINES



#define MYSQL_HOSTNAME						"localhost"
#define MYSQL_USERNAME						"scratch"
#define MYSQL_PASSWORD						"mypassword"
#define MYSQL_DATABASE						"scratch_cnr"

#define	BCRYPT_COST							12
#define	SECONDS_TO_LOGIN 					60

#undef	  	MAX_PLAYERS
#define	 	MAX_PLAYERS						50


#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_BLUE, "[MNLCNR]:{F9DC5C} "%1)

#define SendUsageMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_BLUE, "[USAGE]:{F9DC5C} "%1)

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_RED, "[ERROR]:{F9DC5C} "%1)

#define SendAdminAction(%0,%1) \
	SendClientMessageEx(%0, COLOR_LIGHTBLUE, "[ADMIN]:{F9DC5C} "%1)


#define SCM 								SendClientMessage
#define MNLTAG								"{3185FC}MNL:CNR{F9DC5C}"
#define SERVER_DISCORD						"(discord.gg/enWJtgJ)"

#define INVALIDCLASS						0
#define CLASS_CIVILIAN						1
#define CLASS_POLICE						2
#define CLASS_FBI							3
#define CLASS_ARMY							4

#define OS_TYPE_ANDROID 					0
#define OS_TYPE_PC 							1
