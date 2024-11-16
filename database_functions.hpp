#include <string>
#include <sqlite3.h>

#define CREATE_ALBUMS "CREATE TABLE Albums ( id INTEGER PRIMARY KEY, title VARCHAR(512), release_year INT );"
#define CREATE_SONGS "CREATE TABLE Songs ( id INTEGER PRIMARY KEY, title VARCHAR(512), track_number INT, disc_number INT, album_id INT, rating SMALLINT DEFAULT -1, location VARCHAR(1024), FOREIGN KEY (album_id) REFERENCES Albums(id) );"
#define CREATE_ARTISTS "CREATE TABLE Artists ( id INTEGER PRIMARY KEY, artist_name VARCHAR(256), about VARCHAR(10240) );"
#define CREATE_CONTRIBUTING_ARTISTS "CREATE TABLE ContributingArtists ( song_id INT NOT NULL, artist_id INT NOT NULL, PRIMARY KEY (song_id, artist_id), FOREIGN KEY (song_id) REFERENCES Songs(id), FOREIGN KEY (artist_id) REFERENCES Artists(id) );"
#define CREATE_ALBUM_ARTISTS "CREATE TABLE AlbumArtists ( album_id INT NOT NULL, artist_id INT NOT NULL, PRIMARY KEY (album_id, artist_id), FOREIGN KEY (album_id) REFERENCES Albums(id), FOREIGN KEY (artist_id) REFERENCES Artists(id) );"

enum EntityType {
    Album,
    Artist,
    Genre
};

int createDatabase(const char *db_path);
int createTables(sqlite3 *db);
int getEntityId(sqlite3 *db, EntityType entity_type, const std::string &artist_name);
int __getArtistIdInternalCallback(void *id, int argc, char **argv, char **column_names);

