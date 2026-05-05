#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define WIDTH 10
#define HEIGHT 6

// ===== STRUCT =====
typedef struct {
    int x;
    int y;
} Player;

// ===== MAP =====
char map[HEIGHT][WIDTH] = {
    {' ', ' ', 'C', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' '},
    {'B', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' '},
    {' ', ' ', 'G', ' ', 'I', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'I', ' '},
    {' ', ' ', ' ', 'B', ' ', 'C', ' ', ' ', ' ', ' '}
};

// ===== INPUT SANS ENTREE =====
char getch() {
    struct termios oldt, newt;
    char c;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

// ===== DEPLACEMENT =====
void movePlayer(Player *p, char input) {
    int newX = p->x;
    int newY = p->y;

    if (input == 'z') newY--;
    if (input == 's') newY++;
    if (input == 'q') newX--;
    if (input == 'd') newX++;

    if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
        p->x = newX;
        p->y = newY;
    }
}

// ===== AFFICHAGE =====
void printMap(Player p) {
    printf("┌");
    for (int i = 0; i < WIDTH * 2; i++) printf("─");
    printf("┐\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("│");

        for (int j = 0; j < WIDTH; j++) {

            if (i == p.y && j == p.x) {
                printf("😷 ");
            } else {
                char c = map[i][j];

                switch(c) {
                    case 'C': printf("🪑 "); break;
                    case 'I': printf("🧰 "); break;
                    case 'G': printf("🧤 "); break;
                    case 'B': printf("🗑️ "); break;
                    default: printf("  ");
                }
            }
        }

        printf("│\n");
    }

    printf("└");
    for (int i = 0; i < WIDTH * 2; i++) printf("─");
    printf("┘\n");

    printf("ZQSD pour bouger | X pour quitter\n");
}

// ===== MAIN =====
int main() {
    Player player = {0, 0};
    char input;

    while (1) {
        // Clear écran
        printf("\033[H\033[J");

        printMap(player);

        input = getch();

        if (input == 'x') break;

        movePlayer(&player, input);

        usleep(50000); // petit délai (optionnel)
    }

    return 0;
}