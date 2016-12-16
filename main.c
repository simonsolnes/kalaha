#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct plr {
	
	char title[30];
	int home;
	int pits[1000];

} plr_t;

typedef struct game {
	int pitnum;
	plr_t *curplr;
	plr_t *othplr;
	
} game_t;


game_t *populate();
void refresh(game_t *game);
void printpits(int *pits, int pitnum, int gap, int reverse);
int findgap(game_t *game);
int findspace(int a, int b, int gap);
int intlen(int input);
int findlongest(game_t *game);

int main() {

	game_t *rep = populate(6, 4);

	rep->curplr->pits[1] = 4444444;
	rep->curplr->pits[2] = 44444444;
	rep->curplr->pits[4] = 444;


	refresh(rep);
	
	printf("Gap: %d", findgap(rep));

}

game_t *populate(int pitnum, int marbles) {

	plr_t *plr1;
	plr_t *plr2;

	plr1 = malloc(sizeof(plr_t));
	plr2 = malloc(sizeof(plr_t));


	char tmp_title1[] = "Player 1";
	char tmp_title2[]= "Player 2";

	strcpy(plr1->title, tmp_title1);
	strcpy(plr2->title, tmp_title2);


	plr1->home = 0;
	plr2->home = 0;


	for (int i = 1; i <= pitnum; i++) {
		plr1->pits[i] = marbles;
		plr2->pits[i] = marbles;
	}

	game_t *game;

	game = malloc(sizeof(game_t));

	game->pitnum = pitnum;
	game->curplr = plr1;
	game->othplr = plr2;

	return game;
}

void refresh(game_t *game) {

	// TODO print othplr backwards
	for (int i = 0; i < 100; i++) printf("\n"); 

	int gap = findgap(game);

	// Top section
	printf("%s:    ", game->othplr->title);
	printpits(game->othplr->pits, game->pitnum, gap,  1);
	printf("\n");

	// Middle section
	printf("          %d   ", game->othplr->home);
	for (int i = 1; i <= game->pitnum; i++) {
		printf("%d", i);
		for (int i = 0; i < gap; i++) printf(" "); 
	}
	printf("%d", game->curplr->home);
	printf("\n");

	
	printf("%s:  ", game->curplr->title);
	printpits(game->curplr->pits, game->pitnum, gap, 0);
	printf("\n");	

	return;

}


void printpits(int *pits, int pitnum, int gap, int reverse) {
	
	if (reverse == 0) {
		for (int i = 1; i <= pitnum; i++) {
			printf("[%d]", pits[i]);
			for (int p = 0; p < findspace(pits[i], pits[i + 1], gap); p++) printf(" ");
		}

	}

	else if (reverse == 1)
		for (int i = pitnum; i >= 1; i--)
			printf("[%d]  ", pits[i]);
	return;
}

int findgap(game_t *game) {

	int gap = 0;

	for (int i = 1; i <= game->pitnum; i++) {
		if (((int)(ceil(((float)(intlen(game->curplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->curplr->pits[i])))/ 2) + 2)) > gap)
			gap = (int)(ceil(((float)(intlen(game->curplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->curplr->pits[i])))/ 2) + 2);
		if (((int)(ceil(((float)(intlen(game->othplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->othplr->pits[i])))/ 2) + 2)) > gap)
			gap = (int)(ceil(((float)(intlen(game->othplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->othplr->pits[i])))/ 2) + 2);
	}

	return gap;
	
}

int findspace(int a, int b, int gap) {

	int space = (int)(gap - 2 - (floor((float)(intlen(a)) / 2) + ceil(((float)(intlen(b))) / 2) - 1));
	return space;

}

int intlen(int integer){
	if (integer == 0) return 1;
	return floor(log10(abs(integer))) + 1;
}

int findlongest(game_t *game) {
	int output = 0;
	for (int i = 1; i <= game->pitnum; i++) {
		if (intlen(game->curplr->pits[i]) > output)
			output = intlen(game->curplr->pits[i]);

		if (intlen(game->othplr->pits[i]) > output)
			output = intlen(game->othplr->pits[i]);
	}
	return output;
}
