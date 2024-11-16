#include <iostream>
#include <string>
#include <vector>

#include "database_functions.hpp"

int main(int argc, char **argv) {
    sqlite3 *db;
    createDatabase("test.sqlite");
    sqlite3_open("test.sqlite", &db);
    std::cout << getEntityId(db, EntityType::Artist, "Kendrick Lamar") << std::endl;
    std::cout << getEntityId(db, EntityType::Artist, "Shreya Ghoshal") << std::endl;
    sqlite3_close(db);
    return 0;
}