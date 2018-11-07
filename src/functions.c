#include "functions.h"

typedef struct book
{
	int isbn;
	char author_name[50];
	char book_title[50];
	char publisher[25];
	char category[20];
} book;

int compareString(char *string_1, char *string_2)
{
	char compare_1[50];
	strcpy(compare_1,string_1);
	char compare_2[50];
	strcpy(compare_2,string_2);

	int i;
	for (int i = 0; i < 50; ++i)
	{
		compare_1[i] = tolower(compare_1[i]);
		compare_2[i] = tolower(compare_2[i]);
	}

	compare_1[strlen(compare_1)-1] = '\0';	

	if (strstr(compare_2,compare_1) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int getCommand(int select)
{

	int command;

	if (select == 1)
	{
		printf("-> ");
		scanf("%d", &command);
		getchar();
		
		while(command != 1 && command != 2 && command != 3)
		{
			printf("Comando invalido! Digite novamente -> ");
			scanf("%d", &command);
			getchar();
		}
	}
	else if (select == 2)
	{	
		printf("Digite o comando desejado -> ");
		scanf("%d", &command);
		getchar();
	
		while(command != 1 && command != 2 && command != 3 && command && command !=  4 && command != 5)
		{
			printf("Comando invalido! Digite novamente -> ");
			scanf("%d", &command);
			getchar();
		}
	}

	return command;
}

char getAnswer(int select)
{
	if (select == 0)
	{
		printf("Livro adicionado com sucesso! Deseja adicionar outro?");
	}
	else if (select == 1)
	{
		printf("Deseja consultar novamente?");		
	}
	
	printf(" (s/n) -> ");

	char answer;
	scanf("%c", &answer);
	getchar();
	answer = tolower(answer);
	
	while(answer != 's' && answer != 'n')
	{
		printf("\nComando invalido! Digite novamente -> ");
		scanf("%c", &answer);
		getchar();
		answer = tolower(answer);		
	}

	if (answer == 's')
	{
		return 1;
	}
	else if(answer == 'n')
	{
		return 0;
	}
}

void setCategory(char *new_book_category)
{
	printf("\n0 - Generalidades\n");
	printf("1 - Filosofia\n");
	printf("2 - Religiao\n");
	printf("3 - Ciencias sociais\n");
	printf("4 - Linguas\n");
	printf("5 - Ciencias Puras\n");
	printf("6 - Ciencias Aplicadas\n");
	printf("7 - Artes\n");
	printf("8 - Literatura\n");
	printf("9 - Historia e Geografia\n\n");

	printf("Digite o número -> ");

	int category;
	scanf("%d", &category);
	getchar();

	while (category != 0 && category != 1 && category != 2 && category != 3 && category != 4 && 
		category != 5 && category != 6 && category != 7 && category != 8 && category != 9)
	{
		printf("Numero invalido, digite novamente -> ");
		scanf("%d", &category);
		getchar();
	}

	switch(category)
	{
		case 0:
		strcpy(new_book_category,"Generalidades");
		break;	

		case 1:
		strcpy(new_book_category,"Filosofia");
		break;	

		case 2:
		strcpy(new_book_category,"Religiao");
		break;

		case 3:
		strcpy(new_book_category,"Ciencias Sociais");
		break;	

		case 4:
		strcpy(new_book_category,"Linguas");
		break;	

		case 5:
		strcpy(new_book_category,"Ciencias Puras");
		break;	

		case 6:
		strcpy(new_book_category,"Ciencias Aplicadas");
		break;	

		case 7:
		strcpy(new_book_category,"Artes");
		break;	

		case 8:
		strcpy(new_book_category,"Literatura");		
		break;	

		case 9:
		strcpy(new_book_category,"Historia e Geografia");
		break;		
	}
}

void addBook()
{
	system("clear");

	book new_book;
	printf("Digite o nome do livro: ");
	fgets(new_book.book_title,50,stdin);
	printf("Digite o nome do autor: ");
	fgets(new_book.author_name,50,stdin);
	printf("Digite o nome da editora: ");
	fgets(new_book.publisher,25,stdin);
	printf("Digite o número de ISBN: ");
	scanf("%d", &new_book.isbn);
	getchar();
	printf("Escolha a categoria\n");
	setCategory(new_book.category);

	FILE *f = fopen("books//data.txt","a+");
	fprintf(f,"\n%s",new_book.book_title);
	fprintf(f,"%s",new_book.author_name);
	fprintf(f,"%s",new_book.publisher);
	fprintf(f,"%d\n",new_book.isbn);
	fprintf(f,"%s",new_book.category);
	fclose(f);

	if (getAnswer(0))
	{
		addBook();
	}
	else
	{
		showMenu();
	}
}

void showAllBooks()
{
	system("clear");

	int count = 0;
	char line[50];
	FILE *f = fopen("books//data.txt","r");

	while(fgets(line,50,f) != NULL)
	{
		if (count == 1)
		{
			printf("Título: %s", line);
		}
		else if (count == 2)
		{
			printf("Autor(a): %s", line);
		}
		else if (count == 3)
		{
			printf("Editora: %s", line);
		}
		else if(count == 4)
		{
			printf("ISBN: %s", line);
		}
		else if(count == 5)
		{
			printf("Categoria: %s\n\n", line);
			count = - 1;
		}

		count++;
	}
	if (getAnswer(1))
	{
		showAllBooks();
	}
	else
	{
		showMenu();
	}
}

void checkTitle()
{
	system("clear");

	char book_title[50];
	char author_name[50];
	char publisher[50];
	char isbn[50];
	char category[20];
	char line[50];
	int count = 0;
	
	char searched_title[50];
	printf("Digite o título que deseja buscar: ");
	fgets(searched_title,50,stdin);
	printf("\n");

	FILE *f = fopen("books//data.txt","r");

	while(fgets(line,50,f) != NULL)
	{
		fgets(book_title,50,f);

		if (compareString(searched_title,book_title))
		{
			count = 1;

			fgets(author_name,50,f);
			fgets(publisher,50,f);
			fgets(isbn,50,f);
			fgets(category,50,f);

			printf("Título: %s", book_title);
			printf("Autor: %s", author_name);
			printf("Editora: %s",publisher);
			printf("ISBN: %s", isbn);
			printf("Categoria: %s\n\n", category);
		}
		else
		{
			fgets(line,50,f);
			fgets(line,50,f);
			fgets(line,50,f);
			fgets(line,50,f);
		}
	}

	if (count == 0)
	{
		printf("Não foi possível encontrar resultados para essa pesquisa.\n");
	}

	if (getAnswer(1))
	{
		checkTitle();
	}
	else
	{
		showMenu();
	}	
}

void checkAuthor()
{
	system("clear");

	char book_title[50];
	char author_name[50];
	char publisher[50];
	char isbn[50];
	char category[20];
	char line[50];
	int count = 0;
	
	char searched_author[50];
	printf("Digite o nome do autor que deseja buscar: ");
	fgets(searched_author,50,stdin);
	printf("\n");

	FILE *f = fopen("books//data.txt","r");

	while(fgets(line,50,f) != NULL)
	{
		fgets(book_title,50,f);
		fgets(author_name,50,f);
			
		if (compareString(searched_author,author_name))
		{
			count = 1;

			fgets(publisher,50,f);
			fgets(isbn,50,f);
			fgets(category,20,f);

			printf("Título: %s", book_title);
			printf("Autor: %s", author_name);
			printf("Editora: %s",publisher);
			printf("ISBN: %s", isbn);
			printf("Categoria: %s\n\n", category);
		}
		else
		{
			fgets(line,50,f);
			fgets(line,50,f);
			fgets(line,50,f);
		}
	}

	if (count == 0)
	{
		printf("Não foi possível encontrar resultados para essa pesquisa.\n");
	}

	if (getAnswer(1))
	{
		checkAuthor();
	}
	else
	{
		showMenu();
	}	
}

void checkPublisher()
{
	system("clear");

	char book_title[50];
	char author_name[50];
	char publisher[50];
	char isbn[50];
	char category[20];
	char line[50];
	int count = 0;

	char searched_publisher[50];
	printf("Digite o nome da editora que deseja buscar: ");
	fgets(searched_publisher,50,stdin);
	printf("\n");

	FILE *f = fopen("books//data.txt","r");

	while(fgets(line,50,f) != NULL)
	{
		fgets(book_title,50,f);
		fgets(author_name,50,f);
		fgets(publisher,50,f);	
		
		if (compareString(searched_publisher,publisher))
		{
			fgets(isbn,50,f);
			fgets(category,20,f);

			count = 1;
			printf("Título: %s", book_title);
			printf("Autor: %s", author_name);
			printf("Editora: %s",publisher);
			printf("ISBN: %s", isbn);
			printf("Categoria: %s\n\n", category);
		}
		else
		{
			fgets(line,50,f);
			fgets(line,50,f);
		}
	}

	if (count == 0)
	{
		printf("Não foi possível encontrar resultados para essa pesquisa.\n");
	}

	if (getAnswer(1))
	{
		checkPublisher();
	}
	else
	{
		showMenu();
	}	
}

void checkCategory()
{
	system("clear");

	char book_title[50];
	char author_name[50];
	char publisher[50];
	char isbn[50];
	char category[20];
	char line[50];
	int count = 0;

	char searched_category[20];
	printf("Digite o nome da categoria que deseja buscar: ");
	fgets(searched_category,20,stdin);
	searched_category[strlen(searched_category)-1] = '\0';	

	FILE *f = fopen("books//data.txt","r");

	while(fgets(line,50,f) != NULL)
	{
		fgets(book_title,50,f);
		fgets(author_name,50,f);
		fgets(publisher,50,f);	
		fgets(isbn,50,f);
		fgets(category,20,f);

		if (compareString(searched_category,category))
		{
			count = 1;
			printf("\nTítulo: %s", book_title);
			printf("Autor: %s", author_name);
			printf("Editora: %s",publisher);
			printf("ISBN: %s", isbn);
			printf("Categoria: %s\n\n", category);
		}
	}

	if (count == 0)
	{
		printf("Não foi possível encontrar resultados para essa pesquisa.\n");
	}

	if (getAnswer(1))
	{
		checkCategory();
	}
	else
	{
		showMenu();
	}	
}

void showMenu()
{ 
	system("clear");

	printf("Sistema de Livraria\n\n");
	printf("1 - Adicionar Livro\n");
	printf("2 - Checar Livro\n");
	printf("3 - Sair\n\n");
	printf("O que deseja? ");
	
	int command;
	command = getCommand(1);

	switch(command)
	{
		case 1:
		addBook();
		break;

		case 2:
		showCheckMenu();
		break;

		case 3:
		system("clear");
		return;
	}
}

void showCheckMenu()
{
	system("clear");
	printf("Deseja consultar por...\n");
	printf("1 - Título\n");
	printf("2 - Autor\n");
	printf("3 - Editora\n");
	printf("4 - Categoria\n");
	printf("5 - Todos os livros\n");

	int command;
	command = getCommand(2);

	switch(command)
	{
		case 1:
		checkTitle();
		break;

		case 2:
		checkAuthor();
		break;

		case 3:
		checkPublisher();
		break;

		case 4:
		checkCategory();
		break;

		case 5:
		showAllBooks();
		break;
	}
}

// melhorar tela