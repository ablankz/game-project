#include <stdio.h>
#include <string.h>

void label(int x) {
	int tit_mrg = (int)x / 5 - strlen("title") - 2;
	int des_mrg = (int)x / 5 + 7;
	int a_x = x - strlen("description") - 1;
	for (int koaq = 0; koaq < x; ++koaq) {
		printf("+");
	}
	printf("\n");
	printf("+ title");
	for (int local = 0; local < tit_mrg; ++local) {
		printf(" ");
	}
	printf("+ key+ description");
	for (int loc = des_mrg; loc < a_x; ++loc) {
		printf(" ");
	}
	printf("+\n");
}
/**
* 表一行分の関数
*
* {int} x 横の行数
* {int} y 縦の行数
* {char*} title タイトル
* {char} key キーコード
* {char*} description 説明文
*/
void description(int x, int y, char* title, char key, char* description) {
	int i, j, token = 0, ale = 0, ab_o = 0, load_c = 0;
	int tit_size = strlen(title) - 1;
	int des_size = strlen(description) - 1;
	int tit_x = (int)x * 1 / 5;
	int des_x = tit_x + 5;
	int delt = tit_size % (tit_x - 3);
	int alf = (tit_size / (tit_x - 4));
	int alf2 = (tit_size % (tit_x - 4));
	int alf3 = (des_size % (x - des_x - 5));
	if (alf2 == tit_x - 5) alf2 = tit_x - 4;
	if (alf3 == x - des_x - 6) alf3 = x - des_x - 5;
	for (i = 0; i < y; ++i) {
		for (j = 0; j < x; ++j) {
			if (j == 0 || j == x - 1 || i == 0 || i == y - 1) {
				if ((ab_o == 0 || j == 0) && (load_c == 0)) {
					printf("+");
					ab_o = 0;
				}
				else {
					ab_o = 0;
					load_c = 0;
				}
			}
			else if (j == tit_x || j == des_x) {
				printf("+");
			}
			else if (j == tit_x + 2 && i == 2) {
				printf("%c", key);
			}
			/*説明文*/
			else if (j == des_x + 2 && i == 2) {
				int coo = x - des_x - 5;
				int koal = coo * (y - 2);
				int q_key = 0;
				for (int ol = 0; ol < koal; ol += coo) {
					if (*(description + ol) == '\0' || q_key > 0) {
						if (alf3 == coo) {
							load_c++;
						}
						break;
					}
					for (int o = ol; o < ol + coo; ++o) {
						if (*(description + o) == '\0') {
							for (int q_i = 0; q_i < coo - alf3 - 1; ++q_i) {
								printf(" ");
								++ab_o;
							}
							++q_key;
							break;
						}
						printf("%c", *(description + o));
						++j;
					}
					printf("  +\n+");
					for (int lol = 0; lol < tit_x - 1; ++lol) {
						printf(" ");
					}
					printf("+    + ");
				}
				for (int z_i = 0; z_i <= coo; ++z_i) {
					printf(" ");
				}
				printf(" + ");
			}
			/*タイトル*/
			else if (j == 2 && i == 2) {
				if (tit_size <= tit_x - 4) {
					printf("%s", title);
					j += tit_size;
				}
				else {
					for (int al = 0; al <= tit_size; ++al) {
						printf("%c", *(title + al));
						if (al == tit_size) {
							if (alf2 == tit_x - 4) {
								ale = 1;
							}
							else {
								j += alf2;
							}
						}
						if ((al + 1) % (tit_x - 4) == 0) {
							++token;
							printf("  +");
							for (int l = 0; l < 4; ++l) {
								printf(" ");
							}
							printf("+");
							for (int k = 0; k < x - des_x - 2; ++k) {
								printf(" ");
							}
							printf("+");
							printf("\n+ ");
							if (ale == 1) {
								printf(" ");
								--ale;
							}
							y++;
						}
					}
				}
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}