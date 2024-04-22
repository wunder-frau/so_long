#include <stdbool.h>
#include <stdio.h>

#define ROWS 5 
#define COLS 5 

bool check_map_walls(char map[ROWS][COLS]) {
    int i = 0;
    char *firstRow = map[0];
    char *lastRow = map[ROWS - 1];
    while (i < COLS) {
        if (firstRow[i] != '1' || lastRow[i] != '1') {
            return false;
        }
        i++;
    }
    int j = 1;
    while (j < ROWS - 1) {
        if (map[j][0] != '1' || map[j][COLS - 1] != '1') {
            return false;
        }
        j++;
    }
    return true;
}

int main() {
    char map[ROWS][COLS] = {
        "11111",
        "100E1",
        "10010",
        "1P1C1",
        "11111"
    };
    
    if (check_map_walls(map)) {
        printf("The map has proper walls.\n");
    } else {
        printf("The map does not have proper walls.\n");
    }
    
    return 0;
}
