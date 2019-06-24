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

// Структура, где хранятся исходные данные из файла
typedef struct list_data {
	char operation;
	char calculator;
	int size;
	float *number_1;
	float *number_2;
	struct list_data *next;
} list_data;

// Структура, где хранится результат выполнения калькулятора
typedef struct list_result {
	float* result;
	struct list_result *next;
} list_result;


// Функция получения последнего элемента списка
list_data* getLastData(list_data* element){
	if(element == NULL){
		return NULL;
	}
	while(element->next){
		element = element->next;
	}
	return element;
}

list_result* getLastResult(list_result* element){
	if(element == NULL){
		return NULL;
	}
	while(element->next){
		element = element->next;
	}
	return element;
}

// Функция добавления первого элемента
void addHeadData(list_data** head, FILE* read_file){
	// Выделяем память для временного елемента списка
	list_data* tmp = (list_data*)malloc(sizeof(list_data));
	// Читаем первые два символа из файла и записываем их в элемент списока
	fscanf(read_file, "%c %c", &tmp->operation, &tmp->calculator);
	// Если "v", то читаем размерность векторов
	if(tmp->calculator == 'v'){
		fscanf(read_file, "%d", &tmp->size);
	} else {  // Иначе размерность векторов = 1 => обычные числа
		tmp->size = 1;
	}
	// Выделяем память для двух переменных, хранящие наши числа
	tmp->number_1 = malloc(tmp->size * sizeof(float));
	tmp->number_2 = malloc(tmp->size * sizeof(float));
	// Считываем сначала все числа в первую переменную...
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->number_1[i]);
	}
	// ...затем во вторую
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->number_2[i]);
	}
	// Кидаем указатель в NULL
	tmp->next = (*head);
	(*head) = tmp;
}

void numberCalculator(list_data* data, list_result* result);
void vectorCalculator(list_data* data, list_result* result);

//Функция добавления первого результата в другой присок
void addHeadResult(list_data* data, list_result** head){
	// Выделяем память для временного елемента списка с результатами
	list_result* tmp = (list_result*)malloc(sizeof(list_result));
	if(data->calculator == 'v')
		vectorCalculator(data, tmp);
	else
		numberCalculator(data, tmp);
	tmp->next = (*head);
	(*head) = tmp;
}

// Функция добавления элемента в конец списка
void addData(list_data* head, FILE* read_file){
	// Получаем последний элемент списка с данными
	list_data* last = getLastData(head);
	// Создаём временный элемент
	list_data* tmp = (list_data*)malloc(sizeof(list_data));
	// Читаем первые два символа из файла и записываем их в элемент списока
	fscanf(read_file, " %c %c", &tmp->operation, &tmp->calculator);
	// Если "v", то читаем размерность векторов
	if(tmp->calculator == 'v'){
		fscanf(read_file, "%d", &tmp->size);
	} else {  // Иначе размерность векторов = 1 => обычные числа
		tmp->size = 1;
	}
	// Выделяем память для двух переменных, хранящие наши числа
	tmp->number_1 = malloc(tmp->size * sizeof(float));
	tmp->number_2 = malloc(tmp->size * sizeof(float));
	// Считываем сначала все числа в первую переменную...
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->number_1[i]);
	}
	// ...затем во вторую
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->number_2[i]);
	}
	tmp->next = NULL;
	last->next = tmp;
}

// Функция добавления результата в другой список
void addResult(list_data* data, list_result* head){
	// Получаем последний элемент списка с результатами
	list_result* last = getLastResult(head);
	// Создаём временный элемент
	list_result* tmp = (list_result*)malloc(sizeof(list_result));
	if(data->calculator == 'v')
		vectorCalculator(data, tmp);
	else
		numberCalculator(data, tmp);
	tmp->next = NULL;
	last->next = tmp;
}

void numberCalculator (list_data* data, list_result* result) {
	result->result = malloc(sizeof(float));
	switch(data->operation){
	case '+':
		result->result[0] = data->number_1[0] + data->number_2[0];
		break;
	case '-':
		result->result[0] = data->number_1[0] - data->number_2[0];
		break;
	case '*':
		result->result[0] = data->number_1[0] * data->number_2[0];
		break;
	case '/':
		result->result[0] = data->number_1[0] / data->number_2[0];
		break;
	case '^':
		result->result[0] = data->number_1[0];
		if (data->number_2[0] != 0) {
			for (int i = 1;i < data->number_2[0]; i++) {
				result->result[0] = result->result[0] * data->number_1[0];
			}
		} else
		result->result[0] = 1;
		break;
	case '!':
		result->result[0] = 1;
		for (int i = 1; i <= data->number_1[0]; i++) {
			result->result[0] = result->result[0] * i;
		}
		break;
	}
}

void vectorCalculator (list_data* data, list_result* result) {
	result->result = malloc(data->size * sizeof(float));
	switch(data->operation){
	case '+':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->number_1[i] + data->number_2[i];
		}
		break;
	case '-':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->number_1[i] - data->number_2[i];
		}
		break;
	case '*':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->number_1[i] * data->number_2[i];
		}
		break;
	}
}

// Функция записи результата в файл
void writeInFile(list_data* data, list_result* result, FILE* write_file){
	if(data->calculator == 'v' && data->operation != '*'){
		fprintf(write_file, "(");
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", data->number_1[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ") %c (", data->operation);
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", data->number_2[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ") = (");
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", result->result[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ")");
	} else {
		if (data->calculator == 'v') {
			fprintf(write_file, "(a, b) = ");
		} else if (data->operation != '!') {
			fprintf(write_file, "%.0f %c %.0f = ", data->number_1[0], data->operation, data->number_2[0]);
		} else {
			fprintf(write_file, "%.0f! = ", data->number_1[0]);
		}
		fprintf(write_file, "%.0f", result->result[0]);
	}
	fprintf(write_file, "\n");
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *read_file, *write_file;
	// Открываем файлы на чтение и на запись
	read_file = fopen("read_file.txt", "r");
	write_file = fopen("write_file.txt", "w");

	// Создаём начало списка с данными из файла
	list_data* head_data = NULL;

	// Записываем данные первого калькулятора в начало списка
	addHeadData(&head_data, read_file);

	// Читаем все остальные калькуляторы, если они есть в файле
	do{
		addData(head_data, read_file);
	}while(!feof(read_file));

	// Создаём current_data, чтобы не потерять начало списка
	list_data* current_data = head_data;
	list_result* head_result = NULL;

	// Записываем первый результат в другой список
	addHeadResult(current_data, &head_result);

	current_data = current_data->next;
	// Записываем оставшиеся результаты в другой список, если они имеются
	while(current_data){
		addResult(current_data, head_result);
		current_data = current_data->next;
	}

	list_result* current_result = head_result;
	current_data = head_data;
	// Записываем всё в файл
	while(current_data){
		writeInFile(current_data , current_result, write_file);
		current_data = current_data->next;
		current_result = current_result->next;
	}

	// Закрываем файлы
	fclose(read_file);
	fclose(write_file);

	return EXIT_SUCCESS;
}
