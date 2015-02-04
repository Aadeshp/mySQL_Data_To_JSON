#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/*
 * @param   server      Server the mySQL Database is Hosted On (Ex: localhost)
 * @param   user        Username to Access the mySQL Database
 * @param   password    Password of the User Account Provided
 * @param   database    Name of the Specific mySQL Database
 *
 * return   Connection with the mySQL Database
 */
MYSQL *init_mysql(
        char *server,
        char *user,
        char *password,
        char *database);

/*
 * @param   query   mySQL Query such as "SELECT * FROM TABLE_NAME"
 *
 * return   Array of Hashtables, where each Hashtable represents a row in the mySQL Database
 */
hash_table **query(MYSQL *conn, char *query);

/*
 * @param   result  Results returned from mySQL
 *
 * return   Array of the Name of Each Column in the mySQL Database
 */
char **get_fields(MYSQL_RES *result);

/*
 * @param   result  Results returned from mySQL
 *
 * return   Number of Columns in the Specified mySQL Database's Table
 */
unsigned long get_num_cols(MYSQL_RES *result);
