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
	plr_t *winner;
} game_t;

void resetboard();
void testprinting(game_t *game);
game_t *populate();
void refresh(game_t *game);
void printfarwards(int *pits, int pitnum, int gap);
void printbackwards(int *pits, int pitnum, int gap);
int localgap(int input);
int findgap(game_t *game);
int findspace(int a, int b, int gap);
int *findstartplaces(int top, int bot, int gap);
int intlen(int input);
void inputmode(game_t *game);
void distribute(game_t *game, int number);
void switchplayers(game_t *game);

int main() {
	resetboard();
}
void resetboard() {
	game_t *game = populate(6, 4);
	// testprinting(game);
	refresh(game);
}
void testprinting(game_t *game) {
	game->curplr->pits[1] = 2222222;
	game->curplr->pits[2] = 2222;
	game->curplr->pits[3] = 2222222;
	game->curplr->pits[4] = 22;
	game->curplr->pits[5] = 2;
	game->curplr->pits[6] = 22;
	game->othplr->pits[2] = 222222;
	game->othplr->pits[3] = 22;
	game->othplr->pits[4] = 222;
	game->othplr->pits[5] = 2;
	game->othplr->pits[6] = 2;

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
	game->winner = 0;

	return game;
}

void refresh(game_t *game) {

	for (int i = 0; i < 100; i++) printf("\n"); 

	int gap = findgap(game);

	int *startspaces;
	startspaces = findstartplaces(game->othplr->pits[game->pitnum], game->curplr->pits[1], gap);

	// Top section
	printf("%s:    ", game->othplr->title);
	for (int i = 1; i < *(startspaces + 1); i++) printf(" ");
	printbackwards(game->othplr->pits, game->pitnum, gap);
	printf("\n");

	// Middle section
	int localgap;
	printf("            %d", game->othplr->home);
	for (int i = 0; i < (gap - (ceil(intlen(game->othplr->home)/2))); i++) printf(" ");
	for (int i = 1; i <= game->pitnum; i++) {
		printf("%d", i);
		localgap = gap - (ceil(intlen(i)/2));
		for (int r = 0; r < localgap; r++) printf(" "); 
	}
	printf("%d", game->curplr->home);
	printf("\n");

	
	// Bottom section
	printf("%s:    ", game->curplr->title);
	for (int i = 1; i < *(startspaces + 2); i++) printf(" ");
	printfarwards(game->curplr->pits, game->pitnum, gap);
	printf("\n\n");	

	inputmode(game);
}


void printfarwards(int *pits, int pitnum, int gap) {

	for (int i = 1; i <= pitnum; i++) {
		printf("[%d]", pits[i]);
		for (int p = 0; p < findspace(pits[i], pits[i + 1], gap); p++) printf(" ");
	}
}

void printbackwards(int *pits, int pitnum, int gap) {

	for (int i = pitnum; i >= 1; i--) {
		printf("[%d]", pits[i]);
		for (int p = 0; p < findspace(pits[i], pits[i - 1], gap); p++) printf(" ");
	}
}


int findgap(game_t *game) {

	int gap = 4;

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

int *findstartplaces(int top, int bot, int gap) {

	static int r[3];

	r[1] = gap - (ceil(intlen(top)/2));
	r[2] = gap - (ceil(intlen(bot)/2));


	return r;

}

int intlen(int integer){

	if (integer == 0) return 1;

	return floor(log10(abs(integer))) + 1;
}

void inputmode(game_t *game){

	int input;

	if (game->winner == 0)
		printf("%s >  ", game->curplr->title);

	else {
		printf("%s won the game", game->winner->title);
		while(1) {}
	}


    scanf("%d", &input);
    if (input > game->pitnum)
        refresh(game);
    else if (input == 0)
        resetboard();
    else
        distribute(game, input);
}

void distribute(game_t *game, int number) {


	if (game->curplr->pits[number] == 0) refresh(game);


	int marbles = game->curplr->pits[number];
	int hand = marbles;
	
	game->curplr->pits[number] = 0;

	int beginpos  = number + 1;

	int movement = number + 1;

	while (hand) {

		// curplr board
		if (hand) {
			for (; (movement <= game->pitnum) && (hand); movement++, hand--)
				game->curplr->pits[movement]++;
		}



		if (!hand) {
			if (game->curplr->pits[movement] == 1) {
				game->curplr->pits[movement] += game->othplr->pits[game->pitnum - movement + 1];
				game->othplr->pits[game->pitnum - movement + 1] = 0;
			}
			switchplayers(game);
			refresh(game);
		}
			
		movement = 1;


		// curplr home
		if (hand) { 
			game->curplr->home++;
			hand--;
			movement = 0;
		}



		if ((!hand) && (movement == 0)) refresh(game);
		movement = 1;

		
		// othplr board
		for (int i = 1; (i <= game->pitnum) && (hand); i++, hand--)
			game->othplr->pits[i]++;

	}
	
	int clean = 1;

	for (int i = 0; i < game->pitnum; i++)
		if ((game->curplr->pits[i] > 1) || (game->othplr->pits[i] > 1)) clean = 0;

	if (clean == 1) {

		for (int i = 1; i < game->pitnum; i++) {
			game->curplr->home += game->curplr->pits[i];
			game->curplr->pits[i] = 0;
			game->othplr->home += game->othplr->pits[i];
			game->othplr->pits[i] = 0;
		}

		if (game->curplr->home > game->othplr->home) game->winner = game->curplr;


		// winner
		printf("win");

		
	}

	switchplayers(game);

	refresh(game);

}

void switchplayers(game_t *game) {

	plr_t *tmp;

	tmp = (*game).curplr;

	(*game).curplr = (*game).othplr;
	(*game).othplr = tmp;

}
