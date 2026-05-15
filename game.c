#include <stdlib.h>
#include <unistd.h>
#include <curses.h> // il faut taper gcc -o map.exe map.c -lncursesw pour compiler
#include <stdbool.h>
#include <time.h>
#include <locale.h>

typedef struct{
    int x;
    int y;
}vecteur;

#define WIDTH 24
#define HEIGHT 12

char map[HEIGHT][WIDTH+1]={
    "########################",
    "#                      #",
    "#                      #",
    "#                  #   #",
    "#                  #   #",
    "#                  #   #",
    "#                      #",
    "####   ###  ####  #### #",
    "#                      #",
    "#                      #",
    "#                      #",
    "########################"
};

int main(){

	setlocale(LC_ALL, "");

    WINDOW *win=initscr(); //Initialise la bibliotheque ncurses et cree la fenetre principale
    keypad(win, true);	//Active la detection des touches speciales (fleches,F1,etc.)
    nodelay(win, true);   
    curs_set(0);

    vecteur head={5, 5};//Initialise le vecteur head aux coordonnées (5,5)
    time_t start=time(NULL); //Enregistre lheure actuelle au debut du programme

    while(true){
    	// mouvements
        int pressed=wgetch(win); //Lit la touche presse

        if(pressed==KEY_LEFT){ //Si la fleche gauche est presse
            if(map[head.y][head.x-1]!='#'){//Si la cellule à gauche nest pas un mur
            	head.x--; //Deplace le joueur dune case vers la gauche
            }
        }
        if(pressed==KEY_RIGHT){
            if(map[head.y][head.x+1]!='#'){
            	head.x++;
            }
        }
        if(pressed==KEY_UP){
            if(map[head.y-1][head.x]!= '#') {
            	head.y--;
            }
        }
        if(pressed==KEY_DOWN){
            if(map[head.y+1][head.x]!= '#'){
            	head.y++;
            }
        }
        if(pressed=='\e') {//Si la touche echap est presse ('\e' = code ESC)
       		break;//Quitte la boucle de jeu
        };

        int elapsed  = (int)(time(NULL) - start);
        int minutes  = elapsed / 60;
        int secondes = elapsed % 60;

        // draw
        erase();//efface tout le contenu affiche precdemment
        for(int y=0; y<HEIGHT; y++){// Parcourt chaque ligne de la carte
            for(int x=0;x< WIDTH;x++){ // Parcourt chaque colonne de la carte
                if(map[y][x]=='#'){  // Si la cellule est un mur
                    mvprintw(y,x*2,"██");// Affiche "##" à cette position (x*2 : chaque cellule = 2 colonnes)
                } 
            }
            }
        
        mvprintw(head.y,head.x*2,"😀"); //Affiche le joueur 'O' a sa position ,ici j ai multiplier la vitesse horizontal parceque elle est lente par rappor ala vitess verticale

        // timer a cote de la carte
        mvprintw(1,WIDTH*2+2, "+------------+");
        mvprintw(2,WIDTH*2+2, "|   TIMER    |");
        mvprintw(3,WIDTH*2+2, "|   %02d:%02d    |", minutes,secondes);
        mvprintw(4,WIDTH*2+2, "+------------+");
        
        for(int i = 0; i<66; i++){
        	mvprintw(12,i, "_");
        }
        for(int j = 0; j<40; j++){
        	mvprintw(j,WIDTH*2 + 17, "|");
        }
        
        mvprintw(14, 0, "légende: ");
        mvprintw(15, 4, "emoji : ustensil ");
        mvprintw(16, 4, "emoji : ustensil ");
        mvprintw(17, 4, "emoji : ustensil ");
        mvprintw(18, 4, "emoji : ustensil ");
        mvprintw(19, 4, "emoji : ustensil ");
        mvprintw(20, 4, "emoji : ustensil ");
        mvprintw(21, 4, "emoji : ustensil ");
        mvprintw(22, 4, "emoji : ustensil ");
        
        mvprintw(0, WIDTH*2 + 18, "Inventaire : ");
        
        mvprintw(2, WIDTH*2 + 20, "Player :");
		mvprintw(1, WIDTH*2 + 30, "+-+");
		mvprintw(2, WIDTH*2 + 30, "|0|"); // 0 peut être remplacé par un variable qui représente 1 emoji
		mvprintw(3, WIDTH*2 + 30, "+-+");
		
		mvprintw(1, WIDTH*2 + 34, "+-+");
		mvprintw(2, WIDTH*2 + 34, "|0|"); // 0 peut être remplacé par un variable qui représente 1 emoji
		mvprintw(3, WIDTH*2 + 34, "+-+");
		
        refresh();
        usleep(100000);//100ms=0.1s
    }

    endwin();
    return 0;
}
