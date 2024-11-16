#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int main() {
	int rc;
	sqlite3 *db_handle;
	sqlite3_stmt *statement;
	int project_id, department_id, budget;
	char *project_name;

	rc = sqlite3_open("test.sqlite", &db_handle);
	sqlite3_prepare_v2(db_handle, "SELECT * FROM Projects;", -1, &statement, NULL);
	while (sqlite3_step(statement) == SQLITE_ROW) {
		project_id = sqlite3_column_int(statement, 0);
		project_name = sqlite3_column_text(statement, 1);
		department_id = sqlite3_column_int(statement, 2);
		budget = sqlite3_column_int(statement, 3);
		printf("%d, %s, %d, %d\n", project_id, project_name, department_id, budget);
	}
	sqlite3_finalize(statement);
	sqlite3_close(db_handle);
	return 0;
}
