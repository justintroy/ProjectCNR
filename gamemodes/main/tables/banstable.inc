#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS bans\
        ( \
            `id` int(11) NOT NULL AUTO_INCREMENT, \
            `name` varchar(24) DEFAULT NULL, \
            `ip` varchar(24) DEFAULT NULL, \
            `longip` int(11) DEFAULT NULL, \
            `ban_timestamp` int(11) DEFAULT NULL, \
            `ban_expire_timestamp` int(11) DEFAULT NULL, \
            `ban_admin` varchar(24) DEFAULT NULL, \
            `ban_reason` varchar(64) DEFAULT NULL, \
            PRIMARY KEY (id), \
            FOREIGN KEY (id) REFERENCES players(ID) \
            ON DELETE CASCADE \
            ON UPDATE RESTRICT \
        )";
    
    mysql_tquery(Database, query);

    print("Setting up 'bans' table...");
    return 1;
}