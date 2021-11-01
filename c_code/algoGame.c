#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 4

double eq_calc(double a, int key, double b);
int eq_calc_g(int a, int key, int b);

int Equation(void)
{
	int num[NUMBER * 2], counter = 0, counter_d = 0, chane[NUMBER], low_count = 0, tool = 0, local = 0, value[NUMBER], l_key;
	int all_key = 0, g_count = 0, point = 0, p = 0, ans = 0, g_tmp[NUMBER], p_ag[NUMBER], q_key = 0;
	double tmp_a, tmp_b, tmp[NUMBER];
	char que[NUMBER - 1];
	while (all_key == 0) {
		for (int i = 0; i < NUMBER; ++i) {
			srand((unsigned int)time(NULL) * (i + 40) * 9123);
			num[i] = rand() % 9 + 1;
		}
		for (int j = NUMBER; j < NUMBER * 2 - 1; ++j) {
			srand((unsigned int)time(NULL) * (j + 20) * 12345);
			num[j] = rand() % 4 + 10;
			if ((num[j] == 10 || num[j] == 11) && low_count > 0) {
				chane[tool] = low_count;
				++tool;
				low_count = 0;
			}
			else if (num[j] == 12 || num[j] == 13) {
				++low_count;
				++counter;
			}
			if ((j == NUMBER * 2 - 2) && (num[j] == 12 || num[j] == 13)) {
				chane[tool] = low_count;
				++tool;
				low_count = 0;
			}
		}
		while (counter_d != counter) {
			for (int k = NUMBER; k < NUMBER * 2 - 1; ++k) {
				if (num[k] == 12 || num[k] == 13) {
					/*k‚©‚çchane[local]ŒÂAŠ|‚¯ŽZEŠ„‚èŽZ‚ª‘±‚­*/
					for (int koo = 1; koo <= chane[local]; ++koo) {
						l_key = k + koo - 1;
						if (koo > 1) {
							tmp_a = tmp[g_count];
						}
						else {
							tmp_a = num[l_key - NUMBER];
						}
						tmp_b = num[l_key - NUMBER + 1];
						tmp[g_count] = eq_calc(tmp_a, num[l_key], tmp_b);
						value[g_count] = (int)tmp[g_count];
					}
					++g_count;
					k += chane[local] - 1;
					counter -= chane[local];
					++local;
				}
			}
		}
		for (int ki = 0; ki < g_count; ++ki) {
			if (tmp[ki] == value[ki]) {
				++point;
			}
		}
		if (point == g_count) {
			break;
		}
		counter = 0, counter_d = 0, low_count = 0, tool = 0, local = 0, g_count = 0, point = 0;
	}
	int on = 0;
	for (int loc = 0; loc < NUMBER; ++loc) {
		if (num[loc + NUMBER] == 12 || num[loc + NUMBER] == 13) {
			g_tmp[on] = value[p];
			p_ag[on] = num[loc + NUMBER - 1];
			loc += chane[p];
			++p;
			++on;
		}
		else {
			g_tmp[on] = num[loc];
			p_ag[on] = num[loc + NUMBER - 1];
			++on;
		}
	}
	ans += g_tmp[0];
	for (int ag = 1; ag < on; ++ag) {
		ans = eq_calc_g(ans, p_ag[ag], g_tmp[ag]);
	}
	printf("If you want to add, input '+'. If you want to subtract, input '-'.\nIf you want to multiply, input '*'.If you want to divid, input '/'.\n");
	printf(" ");
	for (int result = 0; result < NUMBER; ++result) {
		printf("%d", num[result]);
		if (result < NUMBER - 1) {
			printf("¡");
		}
	}
	printf(" = %d\n\n", ans);
	for (int use = 0; use < NUMBER; ++use) {
		for (int sorse = 0; sorse < use; ++sorse) {
			printf("%d", num[sorse]);
			if (sorse < NUMBER - 1) {
				if (sorse == use - 1) printf("¡");
				else printf("%c", que[sorse]);
			}
		}
		if (use == 0) {
			printf("It cannot be re-entered. Please be careful!\n");
		}
		else {
			printf("  << Please enter the key that will be entered in naxt '¡'.\n =>");
			scanf_s(" %c", &que[use - 1], 1);
		}
		printf("\n");
	}
	printf("======your answer======\n\n ");
	for (int cast = 0; cast < NUMBER; ++cast) {
		printf("%d", num[cast]);
		if (cast != NUMBER - 1) {
			printf("%c", que[cast]);
		}
	}
	printf("\n\n=======================\n");
	char lort;
	printf("=====example answer=====\n\n ");
	for (int cast2 = 0; cast2 < NUMBER; ++cast2) {
		printf("%d", num[cast2]);
		if (cast2 != NUMBER - 1) {
			switch (num[NUMBER + cast2])
			{
			case 10:
				lort = '+';
				break;
			case 11:
				lort = '-';
				break;
			case 12:
				lort = '*';
				break;
			case 13:
				lort = '/';
				break;
			default:
				break;
			}
			printf("%c", lort);
		}
	}
	printf("\n\n========================\n");
	/*‚±‚±‚©‚çŒŸØ*/
	int con[NUMBER - 1];
	for (int cal = 0; cal < NUMBER - 1; ++cal) {
		switch (que[cal])
		{
		case '+':
			con[cal] = 10;
			break;
		case '-':
			con[cal] = 11;
			break;
		case '*':
			con[cal] = 12;
			break;
		case '/':
			con[cal] = 13;
			break;
		default:
			printf("input error!!\n");
			return 0;
			break;
		}
		if (con[cal] == num[cal + NUMBER]) {
			++q_key;
		}
	}
	if (q_key == NUMBER - 1) {
		printf("game clear\n\n");
		return 7;
	}
	return 0;
}

double eq_calc(double a, int key, double b) {
	switch (key)
	{
	case 10:
		return a + b;
		break;
	case 11:
		return a - b;
		break;
	case 12:
		return a * b;
		break;
	case 13:
		return a / b;
		break;
	default:
		return 0;
		break;
	}
}

int eq_calc_g(int a, int key, int b) {
	switch (key)
	{
	case 10:
		return a + b;
		break;
	case 11:
		return a - b;
		break;
	default:
		return 0;
		break;
	}
}