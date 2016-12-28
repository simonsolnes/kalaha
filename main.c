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
void testprinting(game_t *game, int mode);
game_t *populate(int pitnum, int marbles);
void refresh(game_t *game);
int localgap(int input);
int findspace(int a, int b, int gap);
int intlen(int input);
void inputmode(game_t *game);
void distribute(game_t *game, int number);
void switchplayers(game_t *game);

int main() {
	resetboard();
}
void resetboard() {
	game_t *game = populate(10, 7);
	// testprinting(game, 2);
	refresh(game);
}
void testprinting(game_t *game, int mode) {
	if (mode == 1) {
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
	else if (mode == 2) {

		game->curplr->pits[1] = 1;
		game->curplr->pits[2] = 0;

	}
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

	int gap = 4;
	for (int i = 1; i <= game->pitnum; i++) {
		if (((int)(ceil(((float)(intlen(game->curplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->curplr->pits[i])))/ 2) + 2)) > gap)
			gap = (int)(ceil(((float)(intlen(game->curplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->curplr->pits[i])))/ 2) + 2);

		if (((int)(ceil(((float)(intlen(game->othplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->othplr->pits[i])))/ 2) + 2)) > gap)
			gap = (int)(ceil(((float)(intlen(game->othplr->pits[i + 1])) / 2) - 1) +  floor(((float)(intlen(game->othplr->pits[i])))/ 2) + 2);
	}

	int startspaces[3];

	startspaces[1] = gap - (ceil(intlen(game->othplr->pits[game->pitnum])/2));
	startspaces[2] = gap - (ceil(intlen(game->curplr->pits[1])/2));

	// Top section
	printf("%s:    ", game->othplr->title);
	for (int i = 1; i < *(startspaces + 1); i++) printf(" ");
	for (int i = game->pitnum; i >= 1; i--) {
		printf("[%d]", game->othplr->pits[i]);
		for (int p = 0; p < findspace(game->othplr->pits[i], game->othplr->pits[i - 1], gap); p++) printf(" ");
	}
	printf("\n");

	// Middle section
	int localgap;
	printf("           %d", game->othplr->home);
	for (int i = 0; i < (gap - (ceil(intlen(game->othplr->home)/2))); i++) printf(" ");
	for (int i = game->pitnum; i >= 1; i--) {
		printf("%d", i);
		localgap = gap - (ceil(intlen(i)/2));
		for (int r = 0; r < localgap; r++) printf(" "); 
	}
	printf("%d", game->curplr->home);
	printf("\n");
	
	// Bottom section
	printf("%s:    ", game->curplr->title);
	for (int i = 1; i < *(startspaces + 2); i++) printf(" ");
	for (int i = 1; i <= game->pitnum; i++) {
		printf("[%d]", game->curplr->pits[i]);
		for (int p = 0; p < findspace(game->curplr->pits[i], game->curplr->pits[i + 1], gap); p++) printf(" ");
	}
	printf("\n\n");	

	inputmode(game);
}

int findspace(int a, int b, int gap) {
	return (int)(gap - 2 - (floor((float)(intlen(a)) / 2) + ceil(((float)(intlen(b))) / 2) - 1));
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
		input = game->pitnum + 1 - input;
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

		/*
		if (!hand) {
			if (game->curplr->pits[movement] == 1) {
				game->curplr->home += game->othplr->pits[game->pitnum - movement + 1];
				game->othplr->pits[game->pitnum - movement + 1] = 0;
			}
			switchplayers(game);
			refresh(game);
		}
		*/
			
		movement = 1;


		// curplr home
		if (hand) { 
			game->curplr->home++;
			hand--;
			if (!hand) refresh(game);
		}


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

	//switchplayers(game);

	refresh(game);

}

void switchplayers(game_t *game) {

	plr_t *tmp;

	tmp = (*game).curplr;

	(*game).curplr = (*game).othplr;
	(*game).othplr = tmp;

}
