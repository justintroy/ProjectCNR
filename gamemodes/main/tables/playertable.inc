#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players \
        ( \
        `ID` int(12) NOT NULL AUTO_INCREMENT, \
        `Username` varchar(24) NOT NULL, \
        `Password` varchar(129) NOT NULL, \
        `IPAddress` varchar(17) NOT NULL, \
        `RegistrationDate` date NOT NULL, \
        `Tutorial` int(1) NOT NULL DEFAULT 0, \
        `Class` int(1) NOT NULL DEFAULT 0, \
        `Skin` int(10) NOT NULL DEFAULT 0, \
        `AdminLevel` int(10) NOT NULL DEFAULT 0, \
        `PlayTime` int(24) DEFAULT 0, \
        `VID` int(10) NOT NULL DEFAULT 100000, \
        PRIMARY KEY (ID, VID), \
        UNIQUE KEY Username (Username) \
        )";
    
    mysql_tquery(Database, query);

    print("Setting up 'players' table...");
    return 1;
}