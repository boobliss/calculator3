/*
 ============================================================================
 Name        : calculator3.c
 Author      : stasya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

void number_calculator (FILE* read_file, FILE *write_file, char operation) {
	// Числа с которыми работаем
	float number_1, number_2;
	float result;
	// Если "!", то считываем одно число
	if (operation == '!')
		fscanf(read_file, "%f", &number_1);
	else
		fscanf(read_file, "%f %f", &number_1, &number_2);
	switch (operation) {
	case '+':
		fprintf(write_file, "%.0f + %.0f = %.0f\n", number_1, number_2, number_1 + number_2);
		break;
	case '-':
		fprintf(write_file, "%.0f - %.0f = %.0f\n", number_1, number_2, number_1 - number_2);
		break;
	case '*':
		fprintf(write_file, "%.0f * %.0f = %.0f\n", number_1, number_2, number_1 * number_2);
		break;
	case '/':
		fprintf(write_file, "%.0f / %.0f = %.0f\n", number_1, number_2, number_1 / number_2);
		break;
	case '!':
		result = 1;
		for(int i = 1; i <= number_1; i++) result = result * i;
		fprintf(write_file, "%.0f ! = %.0f\n", number_1, result);
		break;
	case '^':
		result = number_1;
		if(number_2 != 0){
			for(int i = 1; i < number_2; i++) {
				result = result * number_1;
			}
		}
		else {
			result = 1;
		}
		printf("%.0f ^ %.0f = %.0f", number_1, number_2, result);
		break;
	default:
		printf("%c: такой операции нет\n", operation);
	}
}

void vector_calculator (FILE* read_file, FILE *write_file, char operation) {
	// Вектора, с которыми удем работать
	float *vector_1, *vector_2, result = 0;
	// Размерность векторов
	int size;
	// Читаем размерность векторов
	fscanf(read_file, "%d", &size);
	// Выдкляем память для векторов
	vector_1 = malloc(size*sizeof(float));
	vector_2 = malloc(size*sizeof(float));
	// Читаем координаты vector_1
	for (int i = 0; i < size; i++) {
		fscanf(read_file, "%f", &vector_1[i]);
	}
	// Читаем координаты vector_2
	for (int i = 0; i < size; i++) {
		fscanf(read_file, "%f", &vector_2[i]);
	}
	switch (operation) {
	case '+':
		fprintf(write_file, "(");
		for (int i = 0; i < size; i++) // Выводим координаты vector_1
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_1[i]);
			else fprintf(write_file, "%.0f", vector_1[i]);
		fprintf(write_file, ") + (");
		for (int i = 0; i < size; i++) // Выводим координаты vector_2
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_2[i]);
			else fprintf(write_file, "%.0f", vector_2[i]);
		fprintf(write_file, ") = (");
		for (int i = 0; i < size; i++) // Выводим координаты результирующего вектора
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_1[i] + vector_2[i]);
			else fprintf(write_file, "%.0f", vector_1[i] + vector_2[i]);
		fprintf(write_file, ")\n");
		break;
	case '-':
		fprintf(write_file, "(");
		for (int i = 0; i < size; i++) // Выводим координаты vector_1
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_1[i]);
			else fprintf(write_file, "%.0f", vector_1[i]);
		fprintf(write_file, ") + (");
		for (int i = 0; i < size; i++) // Выводим координаты vector_2
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_1[i]);
			else fprintf(write_file, "%.0f", vector_2[i]);
		fprintf(write_file, ") = (");
		for (int i = 0; i < size; i++) // Выводим координаты результирующего вектора
			if (i != size - 1) fprintf(write_file, "%.0f ", vector_1[i] - vector_2[i]);
			else fprintf(write_file, "%.0f", vector_1[i] - vector_2[i]);
		fprintf(write_file, ")\n");
		break;
	case '*':
		for (int i = 0; i < size; i++) {
			result += vector_1[i] * vector_2[i];
		}
		fprintf(write_file, "<a, b> = %.0f\n", result);
		break;
	default:
		printf("%c: такой операции нет\n", operation);
	}
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *read_file, *write_file;
	// Открываем файлы на чтение и на запись
	read_file = fopen("read_file.txt", "r");
	write_file = fopen("write_file.txt", "w");
	// Операция, которая определяет, что делать с числами (или выход из калькулятора)
	char exit_calc, operation, calc;
	do {
		printf("Для работы калькулятора нужен файл read_file.txt, в котором будут храниться исходные данные.\nДля выхода из калькулятора введите \"q\", а для продолжения введите любую букву: ");
		scanf("%c", &exit_calc);
		// Если продолжаем заботать
		if (exit_calc != 'q') {
			fscanf(read_file, "%c %c ", &operation, &calc);
			while (!feof(read_file)) {
				switch (calc) {
				case 's':
					number_calculator(read_file, write_file, operation);
					break;
				case 'v':
					vector_calculator(read_file, write_file, operation);
					break;
				default:
					printf("%c: символ калькулятора введён неверно!\n", calc);
				}
				fscanf(read_file, " %c %c", &operation, &calc);
			}
		}
		// Закрываем файлы
		fclose(read_file);
		fclose(write_file);
	} while (exit_calc != 'q');

	return EXIT_SUCCESS;
}
