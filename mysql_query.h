#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

MYSQL *init_mysql(
        const char *server,
        const char *user,
        const char *password,
        const char *database);

hash_table **query(MYSQL *conn, const char *query);

char **get_fields(MYSQL_RES *result);

unsigned long get_num_cols(MYSQL_RES *result);
