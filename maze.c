#include <stdio.h>
#include <string.h>

#define SIZE 5

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./maze <input>\n");
        return 1;
    }

    char *input = argv[1];

    char maze[SIZE][SIZE] = {
        {'#', '#', '#', '#', '#'},
        {'#', 'S', ' ', '#', 'E'},
        {'#', '#', ' ', '#', ' '},
        {'#', '#', ' ', '#', ' '},
        {'#', '#', ' ', ' ', ' '},
    };
    int x = 1, y = 1;

    for (int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
            case 'U':
                if (maze[x - 1][y] != '#') x--;
                break;
            case 'D':
                if (maze[x + 1][y] != '#') x++;
                break;
            case 'L':
                if (maze[x][y - 1] != '#') y--;
                break;
            case 'R':
                if (maze[x][y + 1] != '#') y++;
                break;
            default:
                printf("Invalid direction\n");
                return 1;
        }
    }

    if (maze[x][y] == 'E') {
        printf("Congratulations, you solved the maze!\n");
    } else {
        printf("Try again\n");
    }

    return 0;
}