#include <stdio.h>

void menu();
void encrypt_open_msg();
void decrypt_secret_msg();
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);

int main(int argc, char const *argv[])
{
	menu();
	return 0;
}

void menu()
{
	int choice;
	do{
		printf("1. Encrypt\n2. Decrypt\n0. Exit\nChoice:");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				encrypt_open_msg();
				break;
			case 2:
				decrypt_secret_msg();
				break;
			case 0:
				return;
				break;
		}
	}while(choice != 0);
}

void encrypt_open_msg()
{
	FILE *rp;
	FILE *wp;
	int i = 0, key, lenght, sth, temp;
	char msg[1024];
	printf("Enter the key:");
	scanf("%d", &key);
	rp = fopen("open_msg.txt", "r");
	wp = fopen("secret_msg.txt", "w");
	while(fgets(msg, 1024, rp) != NULL){
		lenght = find_size_of_line(msg);
		/*if(msg[lenght-1] == 13){ 	//burada satirin sonunda carriage return varsa karakterleri kaydiriyorum.
			for(i = 0; i < lenght - 1; ++i){
				msg[i] = msg[i + 1];
			}
			lenght--;
		}*/
		reverse_line(msg, lenght);
		for(i = 0; i < lenght+1; ++i){
			if(msg[i] == ' '){
				msg[i] = '_';
			}
			else if(msg[i] == '.'){
				msg[i] = '*';
			}
			else if(msg[i] - key < 97){
				sth = 97 - (msg[i] - key);
				msg[i] = 122 - sth + 1;
			}
			else
				msg[i] = msg[i] - key;
		}
		printf("%s", msg);
		fputs(msg, wp);
	}
	fclose(rp);
	fclose(wp);
}

void decrypt_secret_msg()
{
	FILE *rp;
	FILE *wp;
	char msg[1024];
	int i = 0, key, sth, lenght;
	printf("Key:");
	scanf("%d", &key);
	rp = fopen("secret_msg.txt", "r");
	wp = fopen("open_msg.txt", "w");
	while(fgets(msg, 1024, rp) != NULL){
		lenght = find_size_of_line(msg);
		/*if(msg[lenght-1] == 13){
			for(i = 0; i < lenght - 1; ++i){
				msg[i] = msg[i + 1];
			}
			lenght--;
		}*/
		reverse_line(msg, lenght);
		for(i = 0; i < lenght+1; ++i){
			if(msg[i] == '_'){
				msg[i] = ' ';
			}
			else if(msg[i] == '*'){
				msg[i] = '.';
			}
			else if(msg[i] + key > 122){
				sth = (msg[i] + key) - 122;
				msg[i] = 97 + sth - 1;
			}
			else
				msg[i] = msg[i] + key;
		}
		printf("%s", msg);
		fputs(msg, wp);
	}
	fclose(rp);
	fclose(wp);
}

int find_size_of_line(char line[])
{
	int lenght = 0, i = 0;
	while(line[i] != '\n' && line[i] != '\r'){
		lenght++;
		i++;
	}
	if(line[i] == '\r' || line[i] == '\n'){
		lenght--;
	}
	return lenght;
}

void reverse_line(char line[], int line_lenght)
{
	int i = 0, j = line_lenght;
	char temp;
	while(i < j){
		temp = line[i];
		line[i] = line[j];
		line[j] = temp;
		i++;
		j--;
	}
}
