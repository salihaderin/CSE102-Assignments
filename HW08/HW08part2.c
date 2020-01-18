#include <stdio.h>
#include <stdlib.h>

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int
current);

int main(int argc, char const *argv[])
{
	int i;
	int arr[6] = {25, 12, 6, 10, 32, 8};
	char operations[5];
	char *bi;
	bi = find_operations(arr, 44, operations, 6, 0, 0);
	if(bi != NULL){
		for(i = 0; i < 5; ++i){
			printf("%c ", bi[i]);
		}
	}
	printf("\n");
	return 0;
}

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int
current)
{
	int bi, i;
	/*char * empty = malloc(sizeof(char) * (arr_len - 1));
	for(i = 0; i < arr_len - 1; ++i){
		empty[i] = ' ';
	}*/
	if(cursor == arr_len - 1 && current == expected_val){
		return operations;
	}
	else if(cursor == arr_len - 1 && current != expected_val){
		return NULL;
		//return empty;
	}
	
	if(current == 0){
		bi = arr[cursor] + arr[cursor + 1];
	}
	else{
		bi = arr[cursor + 1] + current;
	}
	operations[cursor] = '+';
	if(find_operations(arr, expected_val, operations, arr_len, cursor + 1, bi) != NULL){
		return operations;
	}

	if(current == 0){
		bi = arr[cursor] - arr[cursor + 1];
	}
	else{
		bi = current - arr[cursor + 1];
	}
	operations[cursor] = '-';
	if(find_operations(arr, expected_val, operations, arr_len, cursor + 1, bi) != NULL){
		return operations;
	}	

	if(current == 0){
		bi = arr[cursor] * arr[cursor + 1];
	}
	else{
		bi = arr[cursor + 1] * current;
	}
	operations[cursor] = '*';
	if(find_operations(arr, expected_val, operations, arr_len, cursor + 1, bi) != NULL){
		return operations;
	}

	return NULL;
	//return empty;
}
