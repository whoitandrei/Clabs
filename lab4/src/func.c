#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE_STACK 1000
#define STACK_UNDEFLOW -1

typedef struct stack_tag {
	int data[MAX_SIZE_STACK];
	int size;
} stack_t;


static void push(stack_t* stack, int element) {
	stack->data[stack->size] = element;
	stack->size++;
}

static int pop(stack_t* stack) {
	if (stack->size <= 0) {
		return STACK_UNDEFLOW;
	}
	stack->size--;
	int result = stack->data[stack->size];
	stack->data[stack->size] = 0;

	return result;
}

static void cleanArray(char* arr, int index) {
	for (int i = 0; i < index; i++) {
		arr[i] = 0;
	}
}

static int isEmpty(stack_t* stack) {
	return stack->size <= 0;
}

static int isOperation(int s) {
	return (s == '+' || s == '-' || s == '/' || s == '*' || s == '^');
}

static int top(stack_t* stack) {
	if (stack->size > 0) {
		return stack->data[stack->size - 1];
	}
	return 0;
}

static int operationPriority(int s) {
	switch (s)
	{
	case '^':
		return 4;
		break;
	case '*':
	case '/':
		return 3;
		break;
	case '+':
	case '-':
		return 2;
		break;
	case ')':
	case '(':
		return 1;
		break;
	}
	return 0;
}

static int calc(stack_t* expression, int op) {
	if (op == '(') {
		printf("syntax error");
		return 1;
	}
	int a1, a2;
	if (isEmpty(expression)) {
		printf("syntax error");
		return 1;
	}
	a1 = pop(expression);
	if (isEmpty(expression)) {
		printf("syntax error");
		return 1;
	}
	a2 = pop(expression);
	switch (op)
	{
	case '^':
		push(expression, (int)pow(a1, a2));
	case '+':
		push(expression, a1 + a2);
		break;
	case '-':
		push(expression, a2 - a1);
		break;
	case '*':
		push(expression, a1 * a2);
		break;
	case '/':
		if (!a1) {
			printf("division by zero");
			return 1;
		}
		push(expression, a2 / a1);
		break;
	}
	return 0;
}


int calculate(char* str) {
	stack_t expression,
		    operations;
	expression.size = 0;
	operations.size = 0;

	int i = 0,
		numberIndex = 0;

	int brackets = 0;
	while (str[i] != '\0' && str[i] != '\n' ) {
		if (isdigit(str[i])) {
			char number[999];
			number[numberIndex] = str[i];
			i++;
			numberIndex++;
			while (isdigit(str[i])) {
				number[numberIndex] = str[i];
				numberIndex++;
				i++;
			}
			--i;

			push(&expression, atoi(number));
			cleanArray(number, numberIndex);
			numberIndex = 0;
		}
		else if (str[i] == '(') {
			if (str[i + 1] == ')') {
				printf("syntax error");
				return 0;
			}
			push(&operations, str[i]);
			brackets++;
		}
		else if (str[i] == ')') {
			brackets--;
			if (brackets >= 0) {
				int op;
				while ((op = pop(&operations)) != '(') {
					if (operations.size == 0) {
						printf("syntax error");
						return 0;
					}
					else if (calc(&expression, op)) {
						return 0;
					}
				}
			}
			else {
				printf("syntax error");
				return 0;
			}
		}
		else if (isOperation(str[i])) {
			while (operationPriority(top(&operations)) >= operationPriority(str[i])) {
				if (calc(&expression, pop(&operations))) {
					return 0;
				}
			}
			push(&operations, str[i]);
		}
		else {
			printf("syntax error");
			return 0;
		}
		i++;
	}

	if (brackets) {
		printf("syntax error");
		return 0;
	}

	while (operations.size > 0) {
		calc(&expression, pop(&operations));
	}

	if (i == 0) {
		printf("syntax error");
		return 0;
	}
	if (expression.size == 1) {
		printf("%d", expression.data[expression.size - 1]);
	}
	else {
		printf("syntax error");
	}
	return 0;

}


