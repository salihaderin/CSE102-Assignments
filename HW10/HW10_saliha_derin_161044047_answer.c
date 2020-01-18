#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int number;
	struct node * next;
};

int read_line(FILE * file_name);
double absolute(double number);
double square(double number);
int is_prime(int number);
void record_ll(FILE * file_name, struct node * list);
void record_array(FILE * file_name, int * arr);
double time_ll(FILE * file_name, struct node * list, int boundary);
double time_arr(FILE * file_name, int * arr, int boundary);
double time_file(FILE * file_name, double number);
void free_list(struct node * list);

int main(int argc, char const *argv[])
{
	FILE * fp, * lp, * ap;
	fp = fopen("data.txt", "r");
	double ll1, ll2, ll3, ll4, arr1, arr2, arr3, arr4;
	struct node * root;
	int * arr;
	arr = (int *)calloc(1000000, sizeof(int));
	root = (struct node *)malloc(sizeof(struct node));
	record_ll(fp, root); 	//2. soru a kismi
	fclose(fp);
	fp = fopen("data.txt", "r");
	record_array(fp, arr); 	//2. soru b kismi
	fclose(fp);
	//3. soru
	lp = fopen("output_prime_LinkedList.txt", "w");
	ll1 = time_ll(lp, root, 500000);
	ll2 = time_ll(lp, root, 750000);
	ll3 = time_ll(lp, root, 1000000);
	ap = fopen("output_prime_dynamic_array.txt", "w");
	arr1 = time_arr(ap, arr, 500000);
	arr2 = time_arr(ap, arr, 750000);
	arr3 = time_arr(ap, arr, 1000000);
	fprintf(ap, "%lf\n%lf\n%lf", arr1, arr2, arr3);
	fprintf(lp, "%lf\n%lf\n%lf", ll1, ll2, ll3);
	//4. soru?
	//ll4 = time_file(lp, ll3);
	//printf("File written time for 3.3(linked list): %lf\n", ll4);
	//arr4 = time_file(ap, arr3);
	//printf("File written time for 3.3(array): %lf\n", arr4);
	fclose(lp);
	fclose(ap);
	free_list(root);
	free(arr);
	return 0;
}

int read_line(FILE * file_name)
{
	int number, num;
	char ch;
	fscanf(file_name, "%d", &number);
	fscanf(file_name, "%c", &ch);
	fscanf(file_name, "%d", &num);
	return number;
}

double absolute(double number)
{
    if(number < 0)
        number = -number;
    return number;
}

double square(double number)
{
    double sth = 1;
	while(absolute(sth * sth - number) >= 0.0001){
		sth = ((number / sth) + sth) / 2;
	}
    return sth;
}

int is_prime(int number)
{
	int i;
	double j = square(number);
	for(i = 2; i < j; i++)
	{
		if(number % i == 0)
			return 0;
	}
	return 1;
}

void record_ll(FILE * file_name, struct node * list)
{
	int x;
	struct node * iter;
	list->number = read_line(file_name);
	iter = list;
	while(!feof(file_name)){
		iter->next = (struct node *)malloc(sizeof(struct node));
		iter->number = read_line(file_name);
		x = is_prime(iter->number);
		if(x == 1){
			printf("%d\n", iter->number);
		}
		if(iter->number == 1000000){
			iter->next = NULL;
			break;
		}
		else{
			iter = iter->next;
		}
	}
}

void record_array(FILE * file_name, int * arr)
{
	int i, x;
	for(i = 0; i < 1000000; ++i){
		arr[i] = read_line(file_name);
		x = is_prime(arr[i]);
		if(x == 1){
			printf("%d\n", arr[i]);
		}
	}
}

double time_ll(FILE * file_name, struct node * list, int boundary)
{
	double time;
	clock_t start = clock();
	int x;
	struct node * iter;
	iter = list;
	while(iter->number < boundary){
		x = is_prime(iter->number);
		if(x == 1 && boundary == 1000000){
			fprintf(file_name, "%d\n", iter->number);
		}
		iter = iter->next;
	}
	clock_t stop = clock();
	time = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	return time;
}

double time_arr(FILE * file_name, int * arr, int boundary)
{
	double time;
	clock_t start = clock();
	int i = 0, x;
	while(arr[i] < boundary){
		x = is_prime(arr[i]);
		if(x == 1 && boundary == 1000000){
			fprintf(file_name, "%d\n", arr[i]);
		}
		i++;
	}
	clock_t stop = clock();
	time = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	return time;
}

/*double time_file(FILE * file_name, double number)
{
	double time;
	clock_t start = clock();
	fprintf(file_name, "%lf\n", number);
	clock_t stop = clock();
	time = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	return time;
}*/

void free_list(struct node * list)
{
	struct node * temp;
	while(temp != NULL){
		temp = list->next;
  		free(list);
  		list = temp;
	}
}
