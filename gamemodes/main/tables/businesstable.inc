#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS business \
        ( \
        `ID` int(10) NOT NULL AUTO_INCREMENT,  \
        `x` varchar(10) NOT NULL, \
        `y` varchar(10) NOT NULL, \
        `z` varchar(10) NOT NULL, \
        `type` int(10) NOT NULL, \
        `price` int(10) NOT NULL DEFAULT 500000, \
        `owned` int(1) NOT NULL DEFAULT 0, \
        `owner` int(10) NOT NULL DEFAULT -1, \
        PRIMARY KEY (ID), \
        FOREIGN KEY (ID) REFERENCES players(ID) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
        )";
    
    mysql_tquery(Database, query);

    print("Setting up 'business' table...");
    return 1;
}