#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS inventory \
        (  \
        `OwnerID` int(12) NOT NULL AUTO_INCREMENT, \
        `ItemID` smallint(5) UNSIGNED NOT NULL DEFAULT 0, \
        `Amount` int(10) UNSIGNED NOT NULL DEFAULT 0, \
        PRIMARY KEY (OwnerID), \
        FOREIGN KEY (OwnerID) REFERENCES players(ID) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
        )";
    
    mysql_tquery(Database, query);

    print("Setting up 'inventory' table...");
    return 1;
}