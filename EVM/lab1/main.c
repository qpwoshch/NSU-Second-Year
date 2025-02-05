/*для очистки буфера записи на диск можно или в командной строке ввести команду fsutil volume dismount D:
или открыть окно "Выполнить", ввести команду devmgmt.msc и в политике выбрать нужную функцию*/
/*-DCMAKE_C_FLAGS=-O3
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <time.h>

double Calculating_Pi(double n) {
	double pi = 0;
	for (double i = 0; i <= n; i++) {
		pi += pow(-1, i) / (2 * i + 1);
	}
	pi *= 4;
	return pi;
}


int main() {
	setlocale(LC_ALL, "Rus");
	do {
		printf("Введите значение пременной n\n");
		double n;
		if (scanf("%lf", &n) != 1) {
			printf("Ошибка ввода.\n");
			continue;
		}
		while (getchar() != '\n');
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		double pi = 0;
		pi = Calculating_Pi(n);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		printf("Значение числа пи: %lf\n", pi);
		printf("Время выполнения: %lf sec.\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
		printf("Хотите закончить выполнение программы? Если да, то введите yes, иначе введите no\n");
		char quit[4];
		if (fgets(quit, sizeof(quit), stdin) == NULL) {
			printf("Ошибка ввода.\n");
			continue;
		}
		size_t length = strlen(quit);
		if (length > 0 && quit[length - 1] == '\n') {
			quit[length - 1] = '\0';
		}
		if (strcmp(quit, "yes") == 0) {
			return 0;
		}
	}while(1);
}
