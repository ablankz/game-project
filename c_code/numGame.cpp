#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NumerOn(void) {
	int limittime = 10;
	/* n ”+ˆÊ’u‚ªˆê’v  m ”‚ªˆê’v*/
	int ans, num, x, y, z, a, b, c, n = 0, m = 0;

	srand((unsigned int)time(NULL));
	ans = rand() % 10;
	y = (x = ans);
	while (y == x)
	{
		srand((unsigned int)time(NULL) * 1234);
		y = rand() % 10;
	}
	z = y;
	while (z == x || z == y) {
		srand((unsigned int)time(NULL) * 5678);
		z = rand() % 10;
	}

	for (; limittime > 0; --limittime) {
		printf("LIMIT TIME %d\n3Œ…‚Ì”Žš‚ð“ü—Í‚µ‚Ä‰º‚³‚¢B>", limittime);
		scanf_s(" %d", &num);
		a = num / 100;
		b = num % 100 / 10;
		c = num % 10;

		if (a == x) ++n;
		else if (a == y || a == z) ++m;
		if (b == y) ++n;
		else if (b == x || b == z) ++m;
		if (c == z) ++n;
		else if (c == x || c == y) ++m;

		if (n == 3) {
			printf("game clear\n");
			return limittime;
		}
		else {
			printf("EAT %d\nBITE %d\n\n", n, m);
			n = 0;
			m = 0;
		}
	}
	printf("game over\n");
	return 0;
}