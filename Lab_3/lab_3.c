/* Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
·        ввод записи таблицы с клавиатуры;
·        загрузка и сохранение  таблицы в текстовом файле;
·        просмотр таблицы;
·        сортировка таблицы в порядке возрастания заданного поля;
·        поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
·        удаление записи;
·        изменение (редактирование) записи;
·        вычисление с проверкой и использованием всех записей по заданному условию и формуле (например, общая сумма на всех счетах).
 Перечень полей структурированной переменной:
2. Номер страницы, номер строки, текст изменения строки, дата изменения. */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
	char *ElemNumber;
    char *PageNumber;
    char *StringNumber;
    char *StringEdit;
    char *DateEdit;
    struct Book *head, *next;
} Book_t;

void Input(struct Book *book){
	char *Number;
	Number = (char*)malloc(sizeof(char)*20);
	char *PageNumber;
	PageNumber = (char*)malloc(sizeof(char)*20);
	char *StringNumber;
	StringNumber = (char*)malloc(sizeof(char)*20);
	char *StringEdit;
	StringEdit = (char*)malloc(sizeof(char)*20);
    char *DateEdit;
	DateEdit = (char*)malloc(sizeof(char)*20);

	printf ("Input ElemNumber: ");
	scanf("%20s", Number);
	printf ("Input PageNumber: ");
	scanf("%20s", PageNumber);
	printf ("Input StringNumber: ");
	scanf("%20s", StringNumber);
	printf ("Input StringEdit: ");
	scanf("%20s", StringEdit);
    printf ("Input DateEdit: ");
	scanf("%20s", DateEdit);

    Book_t *temp = NULL;
    temp = (struct Book *)malloc(sizeof(struct Book));
	temp -> ElemNumber = Number;
	temp -> PageNumber = PageNumber;
	temp -> StringNumber = StringNumber;
	temp -> StringEdit = StringEdit;
    temp -> DateEdit = DateEdit;
	temp -> next = book -> head;
	book -> head = temp;
}

void Output(struct Book *book) {
    struct Book *List = book -> head;
	while (List != NULL){
		printf("\nElemNumber: %s\n", List -> ElemNumber);
		printf("PageNumber: %s\n", List -> PageNumber);
		printf("StringNumber: %s\n", List -> StringNumber);
		printf("StringEdit: %s\n", List -> StringEdit);
        printf("DateEdit: %s\n\n", List -> DateEdit);
		List = List -> next;
	}
	if (book -> head == NULL) {
		system("clear");
		printf("Книга пуста\n\n");
	}
}

int SaveBook(char *filename, struct Book *book) {
	    struct Book *List = book -> head;
		FILE *fp;
		fp = fopen("./book.txt", "a+");
		while (List != NULL){
			fprintf(fp,"ElemNumber: ");
			fwrite(List->ElemNumber, strlen(List->ElemNumber), 1, fp); // запись содержимого указателя.
			fprintf(fp,"\n");
			fprintf(fp,"StringNumber: ");
			fwrite(List->StringNumber, strlen(List->StringNumber), 1, fp); // запись содержимого указателя.
			fprintf(fp,"\n");
			fprintf(fp,"String Edit: ");
			fwrite(List->StringEdit, strlen(List->StringEdit), 1, fp); // запись содержимого указателя.
			fprintf(fp,"\n");
			fprintf(fp,"DateEdit: ");
			fwrite(List->DateEdit, strlen(List->DateEdit), 1, fp); // запись содержимого указателя.
			fprintf(fp,"\n\n");
			List = List -> next;
		}
		if (book -> head == NULL) {
			system("clear");
			printf("Книга пуста\n\n");
		}
    	fclose(fp);
		return 0;
	}

int comp(const void * p1, const void * p2)
{
	struct Book * m1 = *(struct Book **)p1;
	struct Book * m2 = *(struct Book **)p2;
	return strcmp(m1->StringEdit, m2->StringEdit);
}

// int LoadBook(char* filename) {
// 	FILE *fp;
// 	char *c;
// 	int i;
// 	int size = sizeof(struct Book);
// 	struct Book *ptr = (struct Book*)malloc(size);

// 	if ((fp = fopen(filename, "rb")) == NULL) {
// 		perror("Ошибка чтения файла");
// 		return 1;
// 	}

// 	c = (char *)ptr;
// 	while ((i = getc(fp)) != EOF) {
// 		*c = i;
// 		c++;
// 	}

// 	fclose(fp);
// 	printf("%-20s %5d \n", ptr -> PageNumber, ptr -> StringNumber);
// 	free(ptr);
// 	return 0;
// }

void Search(struct Book *book) {
	struct Book *List = book -> head;
	char *SearchName;
	int del;
	int n;
	printf("Введите количество символов для сравнения: ");
	scanf("%d", &n);

	SearchName = (char*)malloc(sizeof(char)*n);
	printf("Введите символы: ");
	scanf("%10s", SearchName);

	while (List != NULL){
		if (memcmp (List -> StringEdit, SearchName, n) == 0) {
			printf("PageNumber: %s\n", List -> PageNumber);
			printf("StringNumber: %s\n", List -> StringNumber);
			printf("StringEdit: %s\n", List -> StringEdit);
			printf("DateEdit: %s\n", List -> DateEdit);
		}
		else {
			printf("Такого элемента нет!");
		}
		List = List -> next;
	}

	if (book -> head == NULL) {
		printf("В книге пусто\n\n");
		return;
	}
}

void Del(struct Book *book) {
	struct Book *List = book -> head;

	if (book -> head == NULL) {
		printf("В книге пусто\n\n");
		return;
	}
	else {
		struct Book *List = book -> head -> next;
		book -> head = NULL;

		book -> head = List;
		printf("Последний введенный элемент удален\n");
		return;
	}

}

 void Edit(struct Book *book) {
 	struct Book *List = book -> head;
	char *PageNumber;
	PageNumber = (char*)malloc(sizeof(char)*20);
	char *StringNumber;
	StringNumber = (char*)malloc(sizeof(char)*20);
	char *StringEdit;
	StringEdit = (char*)malloc(sizeof(char)*20);
    char *DateEdit;
	DateEdit = (char*)malloc(sizeof(char)*20);
	char num[10];
	//num = (char*)malloc(sizeof(char));
	printf("Введите номер элемента для изменения: ");
	scanf("%s", &num);
	int n;
	n = strlen(num);
	while (List != NULL){
		if (memcmp (List -> ElemNumber, num, n) == 0) {
			printf("Введите новые данные: ");
			printf ("\nInput PageNumber: ");
			scanf("%20s", PageNumber);
			printf ("Input StringNumber: ");
			scanf("%20s", StringNumber);
			printf ("Input StringEdit: ");
			scanf("%20s", StringEdit);
    		printf ("Input DateEdit: ");
			scanf("%20s", DateEdit);
			List -> PageNumber = PageNumber;
			List -> StringNumber = StringNumber;
			List -> StringEdit = StringEdit;
			List -> DateEdit = DateEdit;
		}
		else {
			printf("\nТакого элемента нет");
		}
		List = List -> next;
	}
	return;
 }

void Menu(){
    printf("\n\n1 - Ввод данных с клавиатуры\n"
        "2 - Загрузить таблицу в текстовый файл\n"
        "3 - Посмотреть таблицу\n"
        "4 - Поиск в таблице\n"
        "5 - Удаление записи\n"
        "6 - Редактирование записи\n"
        "0 - Выход\n\n");
}
int main() {
    setlocale(LC_ALL, "Rus");


    Book_t *book = NULL;
    int key;
	int count = 0;
	char *filename = "book.dat";
    book = (struct Book *)malloc(sizeof(struct Book));
    book->head = NULL;
	



    while (1){
		Menu();
		scanf("%d", &key);
		switch(key){
			case 1:
				Input(book);
				count++;
				break;
			case 2:
				SaveBook(filename, book);
				break;
			case 3:
				Output(book);
				break;
            case 4:
				Search(book);
				break;
            case 5:
				Del(book);
				break;
            case 6:
				Edit(book);
				break;
            case 0:
				exit(0);
				break;
			default:
				exit(0);
		}

        
    }

    

    return 0;
}