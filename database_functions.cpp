#include "database_functions.hpp"
#include "misc.hpp"

/**
 * @brief Creates a new SQLite database file at the given path, and creates
 *        tables within it according to TABLE_CREATION_SQL.
 *
 * @details This function will also delete any existing data within the
 *          database, if it already exists.
 *
 * @param[in] db_path The path to the database file to be created.
 *
 * @return 0 on success, -1 on failure.
 */
int createDatabase(const char *db_path) {
    sqlite3 *db;
    int rc;
    
    rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        log("Can't open database %s: %s\n", db_path, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // The following code is to fully delete the data within the database, if anything exists.
    sqlite3_db_config(db, SQLITE_DBCONFIG_RESET_DATABASE, 1, 0);
    sqlite3_exec(db, "VACUUM", 0, 0, 0);
    sqlite3_db_config(db, SQLITE_DBCONFIG_RESET_DATABASE, 0, 0);

    // Creating tables
    if (createTables(db) != 0) {
        log("Unable to create tables for new database @ %s\n", db_path);
        sqlite3_close(db);
        return -1;
    }
    log("Database with tables created successfully @ %s\n", db_path);
    sqlite3_close(db);
    return 0;
}

int createTables(sqlite3 *db) {
    int rc;
    char *error_message;
    rc = sqlite3_exec(db, CREATE_ALBUMS, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        log("Unable to create Albums table: %s\n", error_message);
        sqlite3_free(error_message);
        return -1;
    }

    rc = sqlite3_exec(db, CREATE_SONGS, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        log("Unable to create Songs table: %s\n", error_message);
        sqlite3_free(error_message);
        return -1;
    }

    rc = sqlite3_exec(db, CREATE_ARTISTS, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        log("Unable to create Artists table: %s\n", error_message);        
        sqlite3_free(error_message);
        return -1;
    }

    rc = sqlite3_exec(db, CREATE_CONTRIBUTING_ARTISTS, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        log("Unable to create ContributingArtists table: %s\n", error_message);
        sqlite3_free(error_message);
        return -1;
    }

    rc = sqlite3_exec(db, CREATE_ALBUM_ARTISTS, NULL, NULL, &error_message);
    if (rc != SQLITE_OK) {
        log("Unable to create AlbumArtists table: %s\n", error_message);        
        sqlite3_free(error_message);
        return -1;
    }

    return 0;
}

/**
 * @brief Retrieves the ID of an artist from the database, creating a new entry if the artist does not exist.
 *
 * @details This function queries the Artists table in the provided SQLite database to find the ID of the artist
 *          with the specified name. If the artist is not found, a new entry is created, and the ID of the newly
 *          created artist is returned. In case of any database operation errors, the function logs the error
 *          message and returns -1.
 *
 * @param[in] db A pointer to the SQLite database connection.
 * @param[in] artist_name The name of the artist to retrieve or create.
 *
 * @return The ID of the artist, or -1 if an error occurs.
 */
int getEntityId(sqlite3 *db, EntityType entity_type, const std::string &entity_name) {
    int entity_id = 0, rc;
    char *sql_stmt, *error_message;
    const char *table_name, *column_name;

    switch (entity_type) {
        case EntityType::Album:
            table_name = "Albums";
            column_name = "title";
            break;
        case EntityType::Artist:
            table_name = "Artists";
            column_name = "artist_name";
            break;
        case EntityType::Genre:
            table_name = "Genres";
            column_name = "genre";
            break;
        default:            
            return -1;
    }

    // Try to find entity id
    sql_stmt = sqlite3_mprintf("SELECT id FROM %s WHERE %s = \"%s\";", table_name, column_name, entity_name.c_str());
    rc = sqlite3_exec(db, sql_stmt, &__getArtistIdInternalCallback, &entity_id, &error_message);
    if (rc != SQLITE_OK) {
        log("Error while executing query to get %s id of %s: %s\n", table_name, entity_name.c_str(), error_message);
        sqlite3_free(sql_stmt);
        sqlite3_free(error_message);
        return -1;
    }
    sqlite3_free(sql_stmt);

    // If entity does not exist, create it
    if (entity_id == 0) {
        // Creating the entity
        sql_stmt = sqlite3_mprintf("INSERT INTO %s (id, %s) VALUES (NULL, \"%s\");", table_name, column_name, entity_name.c_str());
        rc = sqlite3_exec(db, sql_stmt, NULL, NULL, &error_message);
        if (rc != SQLITE_OK) {
            log("Error while executing query to create %s %s: %s\n",table_name, entity_name.c_str(), error_message);
            sqlite3_free(sql_stmt);
            sqlite3_free(error_message);
            return -1;
        }
        sqlite3_free(sql_stmt);
        // Getting the entity id, after it has been created
        sql_stmt = sqlite3_mprintf("SELECT id FROM %s WHERE %s = \"%s\";", table_name, column_name, entity_name.c_str());
        rc = sqlite3_exec(db, sql_stmt, &__getArtistIdInternalCallback, &entity_id, &error_message);
        if (rc != SQLITE_OK) {
            log("Error while executing query to get %s id (after creating) of %s: %s\n", table_name, entity_name.c_str(), error_message);
            sqlite3_free(sql_stmt);
            sqlite3_free(error_message);
            return -1;
        }
        sqlite3_free(sql_stmt);
    }

    return entity_id;
}

/**
 * Internal callback for getArtistId.
 *
 * This function is used as a callback for a SQLite query. It takes the result
 * of the query and stores it in the id parameter, which is a pointer to an int.
 *
 * \param id The id to store the result in.
 * \param argc The number of columns in the result.
 * \param argv The result of the query.
 * \param column_names The names of the columns.
 *
 * \return 0
 */
int __getArtistIdInternalCallback(void *id, int argc, char **argv, char **column_names) {
    if (argc > 0)
        *(int *)id = atoi(argv[0]);
    return 0;
}