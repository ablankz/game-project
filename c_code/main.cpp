#include <stdio.h>
#include <string.h>
#include "numGame.h"
#include "algoGame.h"
#include "table.h"
#include "numbers.h"

#define GENRE_NUM 4
#define NUM_GAME 4
#define CARD_GAME 4
#define BOA_GAME 4
#define ALGO_GAME 4

typedef struct {
	int no;
	char* title;
	char key;
	char* description;
}genre_t;

int genreSelect(genre_t list[]);
int gameSelect(genre_t list[],int no);

int main(void) {
	genre_t genre[GENRE_NUM] = 
	{	{1,"numberGame",'w',"It is a logical thinking game using numbers."},
		{2,"cardGame",'a',"It is a logical thinking game using card."},
		{3,"boardGame",'s',"It is a logical thinking game using board."},
		{4,"algolism  Game",'d',"It is a logical thinking game using algolism."} 
	};
	genre_t numberGame[NUM_GAME] = {
		{1,"numeron",'q',"It is a game."},
		{2,"numeron",'a',"It is a game."},
		{3,"numeron",'z',"It is a game."},
		{4,"numeron",'x',"It is a game."}
	};
	genre_t cardGame[CARD_GAME] = {
		{1,"numeron",'q',"It is a game."},
		{2,"numeron",'a',"It is a game."},
		{3,"numeron",'z',"It is a game."},
		{4,"numeron",'x',"It is a game."}
	};
	genre_t boardGame[BOA_GAME] = {
		{1,"numeron",'q',"It is a game."},
		{2,"numeron",'a',"It is a game."},
		{3,"numeron",'z',"It is a game."},
		{4,"numeron",'x',"It is a game."}
	};
	genre_t algolismGame[ALGO_GAME] = {
		{1,"equation",'q',"It is a game."},
		{2,"numeron",'a',"It is a game."},
		{3,"numeron",'z',"It is a game."},
		{4,"numeron",'x',"It is a game."}
	};
	int point = 0;
	int n=2,num=0,tab=0,local=0,les;
	char key;
	for (;;) {
		if (num == 0) {
			while (tab == 0) {
				tab= genreSelect(genre);
			}
			switch (tab)
			{
			case 1:
				while (local == 0) {
					local=gameSelect(numberGame,NUM_GAME);
				}
				switch (local)
				{
				case 1:
					les = NumerOn();
					numbers(les);
					point += les;
					break;
				default:
					break;
				}
				break;
			case 2:
				while (local == 0) {
					local = gameSelect(cardGame, CARD_GAME);
				}
				switch (local)
				{
				case 1:
					point += NumerOn();
					break;
				default:
					break;
				}
				break;
			case 3:
				while (local == 0) {
					local = gameSelect(boardGame, BOA_GAME);
				}
				switch (local)
				{
				case 1:
					point += NumerOn();
					break;
				default:
					break;
				}
				break;
			case 4:
				while (local == 0) {
					local = gameSelect(algolismGame, ALGO_GAME);
				}
				switch (local)
				{
				case 1:
					les = Equation();
					numbers(les);
					point += les;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			++num;
			tab = 0;
			local = 0;
		}
		else {
			printf("\nIf you want to continue, please write 'c'.If you want to quit, please write 'q'.\n >>>");
			scanf_s(" %c", &key,4);
			if (key == 'q') {
				n = 0;
			}
			else if (key == 'c') {
				n = 1;
			}
			switch (n)
			{
			case 0:
				return point;
			case 1:
				while (tab == 0) {
					tab = genreSelect(genre);
				}
				switch (tab)
				{
				case 1:
					while (local == 0) {
						local = gameSelect(numberGame, NUM_GAME);
					}
					switch (local)
					{
					case 1:
						les = NumerOn();
						numbers(les);
						point += les;
						break;
					default:
						break;
					}
					break;
				case 2:
					while (local == 0) {
						local = gameSelect(cardGame, CARD_GAME);
					}
					switch (local)
					{
					case 1:
						point += NumerOn();
						break;
					default:
						break;
					}
					break;
				case 3:
					while (local == 0) {
						local = gameSelect(boardGame, BOA_GAME);
					}
					switch (local)
					{
					case 1:
						point += NumerOn();
						break;
					default:
						break;
					}
					break;
				case 4:
					while (local == 0) {
						local = gameSelect(algolismGame, ALGO_GAME);
					}
					switch (local)
					{
					case 1:
						les = Equation();
						numbers(les);
						point += les;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			tab = 0;
			local = 0;
		}
	}
	return point;
}


int genreSelect(genre_t list[]) {
	genre_t target;
	char key, p_key;
	int x = 73, y = 5;
	int length;
	int num = 0,low=0;
		printf("=============================Select game!!===============================\n\n");
		label(x);
		for (int loaq = 0; loaq < GENRE_NUM; ++loaq) {
			description(x, y, list[loaq].title, list[loaq].key, list[loaq].description);
		}
		printf("Please select the game genre you want to play next.Then please enter the selected key.\n =>");
		while (num == 0) {
			++num;
			scanf_s(" %c", &key, 1);
			for (int loq = 0; loq < GENRE_NUM; ++loq) {
				if (key == list[loq].key) {
					num=2;
					target = list[loq];
				}
			}
			if (num == 2) {
				break;
			}
			printf("There is an error in the key input.Please enter an existing key.\n =>");
			num = 0;
		}
		length = (int)strlen(target.description) / 60;
		printf("==========================confirmation==========================\n・Entered key:%c\n・gamegenre:%s\n・description:\n　 ", key, target.title);
		for (unsigned int call = 0; call <= strlen(target.description); ++call) {
			printf("%c", *(target.description+call));
			if ((call+1) % 60 == 0) {
				printf("\n 　");
			}
		}
		printf("\n================================================================\n");
		printf("Please make sure your game of choice is correct.If this is OK please enter 'y'.If you want to choose again please enter 'n'.[y/n]\n =>");
		while (1) {
			scanf_s(" %c", &p_key, 1);
			switch (p_key)
			{
				case 'y':
					printf("\n");
					return target.no;
					break;
				break;
				case 'n':
					printf("\n");
					return 0;
					break;
				default:
					printf("There is an error in the key input.Please enter 'y' or 'n'.\n =>");
					break;
			}
		}

	return 0;
}
int gameSelect(genre_t list[],int no) {
	genre_t target;
	char key, p_key;
	int x = 73, y = 5;
	int length;
	int num = 0, low = 0;
	printf("=============================Select game!!===============================\n\n");
	label(x);
	for (int loaq = 0; loaq < no; ++loaq) {
		description(x, y, list[loaq].title, list[loaq].key, list[loaq].description);
	}
	printf("Please select the game you want to play next.Then please enter the selected key.\n =>");
	while (num == 0) {
		++num;
		scanf_s(" %c", &key, 1);
		for (int loq = 0; loq < no; ++loq) {
			if (key == list[loq].key) {
				num = 2;
				target = list[loq];
			}
		}
		if (num == 2) {
			break;
		}
		printf("There is an error in the key input.Please enter an existing key.\n =>");
		num = 0;
	}
	length = (int)strlen(target.description) / 60;
	printf("==========================confirmation==========================\n・Entered key:%c\n・game:%s\n・description:\n　 ", key, target.title);
	for (unsigned int call = 0; call <= strlen(target.description); ++call) {
		printf("%c", *(target.description + call));
		if ((call + 1) % 60 == 0) {
			printf("\n 　");
		}
	}
	printf("\n================================================================\n");
	printf("Please make sure your game of choice is correct.If this is OK please enter 'y'.If you want to choose again please enter 'n'.[y/n]\n =>");
	while (1) {
		scanf_s(" %c", &p_key, 1);
		switch (p_key)
		{
		case 'y':
			printf("\n");
			return target.no;
			break;
			break;
		case 'n':
			printf("\n");
			return 0;
			break;
		default:
			printf("There is an error in the key input.Please enter 'y' or 'n'.\n =>");
			break;
		}
	}

	return 0;
}
