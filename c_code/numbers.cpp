#include <stdio.h>

#define MATH 9

int numbers(int number) {

	int lock = (int)MATH / 2;

	switch (number)
	{
	case 0:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if ((j == MATH - 1) || i == 0 || i == MATH - 1 || j == 0) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 1:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (j == lock) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 2:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (i == 0||i==lock||i==MATH-1) {
					printf("��");
				}
				else if ((i < lock && j == MATH - 1)||(i>lock&&j==0)) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 3:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if ((j == MATH-1)||i==0||i==MATH-1||i==lock) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 4:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (j == lock||i==lock|| (i < lock && j == 0) ) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 5:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (i == 0 || i == lock || i == MATH - 1) {
					printf("��");
				}
				else if ((i > lock && j == MATH - 1) || (i < lock && j == 0)) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 6:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (i == 0 || i == lock || i == MATH - 1) {
					printf("��");
				}
				else if ((i > lock && (j == MATH - 1||j==0)) || (i < lock && j == 0)) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 7:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if (i == 0 || j == MATH - 1) {
					printf("��");
				}
				else if (i < lock && j == 0) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	case 8:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if ((j == MATH - 1) || i == 0 || i == MATH - 1 || i == lock||j==0) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
	case 9:
		for (int i = 0; i < MATH; ++i) {
			for (int j = 0; j < MATH; ++j) {
				if ((j == MATH - 1) || i == 0 || (i<lock&&j==0) || i == lock) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			printf("\n");
		}
		break;
	default:
		break;
	}
	return 0;
}