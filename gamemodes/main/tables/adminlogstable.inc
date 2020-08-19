#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS adminlogs\
        ( \
        `ID` int(11) NOT NULL AUTO_INCREMENT, \
        `AdminName` varchar(24) DEFAULT NULL, \
        `Action` text DEFAULT NULL, \
        `Date` datetime DEFAULT current_timestamp(), \
        PRIMARY KEY (ID), \
        FOREIGN KEY (id) REFERENCES players(ID) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
        )";
    
    mysql_tquery(Database, query);

    print("Setting up 'adminlogs' table...");
    return 1;
}