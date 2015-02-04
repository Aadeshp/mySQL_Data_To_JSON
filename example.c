#include "mysql_query.h"

int main() {
    MYSQL *sql = init_mysql(/* DATABASE INFO HERE */);
    hash_table **json = query(sql, /* mySQL QUERY HERE */);

    //Do What You Want Here
    return 0;
}
