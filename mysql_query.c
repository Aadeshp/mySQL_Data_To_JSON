#include "mysql_query.h"

MYSQL *init_mysql(
        const char *server, 
        const char *user, 
        const char *password, 
        const char *database) {
    MYSQL *conn;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
        fprintf(stderr, "%s\n", mysql_error(conn));

    return conn;
}

hash_table **query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query))
        fprintf(stderr, "%s\n", mysql_error(conn));

    MYSQL_RES *result = mysql_use_result(conn);
    char **fields = get_fields(result);

    hash_table **json = malloc(sizeof(hash_table *) * mysql_num_rows(result));

    unsigned long numOfCols = get_num_cols(result);
    unsigned long index = 0;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        hash_table *ht = init_hashtable(numOfCols);

        size_t col;
        for (col = 0; col < numOfCols; col++) {
            ht_add(ht, fields[col], row[col]);
        }

        json[index++] = ht;
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

