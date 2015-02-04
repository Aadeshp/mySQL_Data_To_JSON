#include "mysql_query.h"

MYSQL *init_mysql(
        char *server, 
        char *user, 
        char *password, 
        char *database) {
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
        fprintf(stderr, "%s\n", mysql_error(conn));

    return conn;
}

JSON *query(MYSQL *conn, char *query) {
    if (mysql_query(conn, query))
        fprintf(stderr, "%s\n", mysql_error(conn));

    MYSQL_RES *result = mysql_store_result(conn);
    char **fields = get_fields(result);
    
    size_t rows = mysql_num_rows(result);
    JSON *json = malloc(sizeof(JSON *));
    json->size = rows;
    json->arr_ht = malloc(sizeof(hash_table *) * rows);

    unsigned long numOfCols = get_num_cols(result);
    unsigned long index = 0;
    MYSQL_ROW row;
    hash_table *ht;

    while ((row = mysql_fetch_row(result))) {
        ht = init_hashtable(numOfCols);
       
        size_t col;
        for (col = 0; col < numOfCols; col++)
            ht_add(ht, fields[col], row[col]);
    
        json->arr_ht[index++] = ht;
    }

    return json;
}

char **get_fields(MYSQL_RES *result) {
    char **fields = malloc(sizeof(char *) * get_num_cols(result));

    MYSQL_FIELD *field;
    unsigned long index = 0;
    while ((field = mysql_fetch_field(result)))
        fields[index++] = field->name;

    free(field);
    
    return fields;
}

unsigned long get_num_cols(MYSQL_RES *res) {
    return (unsigned long)mysql_num_fields(res);
}

