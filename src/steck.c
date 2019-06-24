/*
 ============================================================================
 Name        : steck.c
 Author      : stasya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//очередь для хранения всех цисел и символов операции
typedef struct turn {
	int size;
	char *element;
	struct turn *next;
} turn;

//список, коротый храник каждую цифру числа
typedef struct number {
	char value;
	struct number *next;
} number;

//стек для хранения всех результатов
typedef struct stack {
	float result;
	struct stack *next;
} stack;

//функция добавления последнего эклемента в очереди
turn* addElement(FILE* file, char c) {
	// объявили первый элемент списка с цифрами
	number* head_number;
	// чтобы не потерять первый элемент
	number* last_number;
	//выделение памяти под голову и конец списка
	head_number = (number*) malloc(sizeof(number));
	last_number = (number*) malloc(sizeof(number));
	//чтобы не потерять начало
	last_number = head_number;

	//инициализируем и выделяем память для временного элемента очереди
	turn* tmp = (turn*) malloc(sizeof(turn));

	//размер массива с числами или операциями
	int size = 0;
	//читаем символы пока не пробел => это или число или операция
	while (c != ' ') {
		size = size + 1;
		//если size = 1, то начало списка символами
		if (size == 1) {
			head_number->value = c;
			head_number->next = NULL;
			last_number = head_number;
		} else {
			number* tmp_number = (number*) malloc(sizeof(number));
			tmp_number->value = c;
			tmp->next = NULL;
			last_number->next = tmp_number;
			last_number = last_number->next;
		}
		//если конец файла, то выходим из цикла
		if (feof(file) != 0)
			break;
		else
			//иначе продолжаем читать символы
			if(c != '$')
				fscanf(file, "%c", &c);
			else
				break;
	}
	//возвражаемся в начало списка с числами или операциями
	last_number = head_number;
	tmp->size = size;
	tmp->element = malloc(size * sizeof(char));
	//заполняем очередь с массивами
	for (int i = 0; i < size; i++) {
		tmp->element[i] = last_number->value;
		if (last_number->next)
			last_number = last_number->next;
	}
	return tmp;
}

//добавление чисел в стэк
stack* addElementStack(char *number, stack* head_stack) {
	stack* tmp = (stack*) malloc(sizeof(stack));
	tmp->next = head_stack;
	tmp->result = atof(number);
	return tmp;
}

//ф-я, которая выполняет операции
stack* operation(char oper, stack* element) {
	switch (oper) {
	case '+':
		element->next->result = element->next->result + element->result;
		break;
	case '-':
		element->next->result = element->next->result - element->result;
		break;
	case '*':
		element->next->result = element->next->result * element->result;
		break;
	case '/':
		element->next->result = element->next->result / element->result;
		break;
	}
	free(element);
	return element->next;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *read_file, *write_file;
	read_file = fopen("read_file.txt", "r");
	char c;

	// создаём первый элемент очереди
	turn* head_turn;
	head_turn = (turn*) malloc(sizeof(turn));
	fscanf(read_file, "%c", &c);
	head_turn = addElement(read_file, c);

	//инициализируем еткущий элемент очереди с числами или операциями
	turn* current;
	current = (turn*) malloc(sizeof(turn));
	//чтобы не потерять начало
	current = head_turn;

	//читаем числа и операции пока не конец файла
	while (!feof(read_file)) {
		fscanf(read_file, "%c", &c);
		current->next = addElement(read_file, c);
		current = current->next;
	}
	fclose(read_file);

	//возвращаемся в начало очереди
	current = head_turn;

	write_file = fopen("result.txt", "w");

	stack* head_stack = (stack*)malloc(sizeof(stack));
	head_stack = addElementStack(current->element, head_stack);

	current = current->next;

	while (current->next) {
		if (current->element[0] != '$') {
			if (current->element[0] == '+'
				|| (current->element[0] == '-' && current->size == 1)
				|| current->element[0] == '*' || current->element[0] == '/') {
				head_stack = operation(current->element[0], head_stack);
			} else {
				head_stack = addElementStack(current->element, head_stack);
			}
			current = current->next;
		} else {
			fprintf(write_file, "%.0f\n", head_stack->result);
			head_stack = head_stack->next;
			current = current->next;
		}
	}

	fclose(write_file);

	return EXIT_SUCCESS;
}
