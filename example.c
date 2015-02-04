#include "mysql_query.h"

int main() {
    MYSQL *sql = init_mysql("localhost", "root", "@patelindustries990", "codearchive_db");
    JSON *json = query(sql, "SELECT * FROM CodeArchiveSite_syntaxminipost");
    
    int i;
    for (i = 0; i < json->size; i++)
        printf("%s\n", ht_get(json->arr_ht[i], "name"));

    return 0;
}
