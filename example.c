#include "mysql_query.h"

int main() {
    MYSQL *sql = init_mysql(/* DATABASE INFO HERE */);
    JSON *json = query(sql, /*mySQL Raw Query Here*/);
    
    int i;
    for (i = 0; i < json->size; i++)
        printf("%s\n", ht_get(json->arr_ht[i], /*Column Name Here*/));

    return 0;
}
