#include <stdio.h>
#include <stdlib.h>

struct customers
{
	char *surname;
	char *name;
	int age;
	char *gender;
	struct customers *next;
};

struct rooms
{
	int number;
	int capacity;
	int floor;
	struct customers *head;
	struct rooms *next;
};

struct rooms * add_room_to_end(struct rooms *root, struct rooms room);
void add_room_after_room_number(struct rooms *root, struct rooms room, int room_number);
void add_customer_to_end(struct customers *root, struct customers customer);
struct rooms * remove_room(struct rooms *root, int room_number);
void show_vacancy(struct rooms *root);
void get_by_floor(struct rooms *root, int floor_number);
void print_list(struct rooms *root);
void free_customers_list(struct customers *root);
void free_rooms_list(struct rooms *root);
struct rooms get_room(FILE * file_name);

int main(int argc, char const *argv[])
{
	struct rooms *root = NULL;
	FILE * fp;
	fp = fopen("rooms.txt", "r");
	while(!feof(fp)){
		root = add_room_to_end(root, get_room(fp));
	}
	print_list(root);
	return 0;
}

struct rooms * add_room_to_end(struct rooms *root, struct rooms room)
{
	struct rooms *iter = root;
	if(root == NULL){
		root = &room;
		root->next = NULL;
	}
	else{
		while(iter->next != NULL){
			iter = iter->next;
		}
		iter->next = (struct rooms *)malloc(sizeof(struct rooms));
		iter->next = &room;
		iter->next->next = NULL;
	}
	return root;
}

void add_room_after_room_number(struct rooms *root, struct rooms room, int room_number)
{
	struct rooms *iter = root;
	while(iter != NULL && iter->number != room_number)
		iter = iter->next;
	struct rooms *temp = (struct rooms *)malloc(sizeof(struct rooms));
	temp = &room;
	temp->next = iter->next;
	iter->next = temp;
}

void add_customer_to_end(struct customers *root, struct customers customer)
{
	struct customers *iter = root;
	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = (struct customers *)malloc(sizeof(struct customers));
	iter->next = &customer;
	iter->next->next = NULL;
}

struct rooms * remove_room(struct rooms *root, int room_number)
{
	struct rooms *temp;
	struct rooms *iter = root;
	while(iter->next != NULL && iter->next->number != room_number){
		iter = iter->next;
	}
	temp = iter->next;
	iter->next = iter->next->next;
	free_customers_list(temp->head);
	free(temp);
}

void show_vacancy(struct rooms *root)
{
	struct rooms *iter = root;
	while(iter != NULL){
		if(iter->head != NULL){
			printf("Room No:%d, Room Capacity:%d, Floor:%d\n", iter->number, iter->capacity, iter->floor);
		}
		iter = iter->next;
	}
}

void free_customers_list(struct customers *root)
{
	struct customers * temp;
	while(temp != NULL){
		temp = root->next;
  		free(root);
  		root = temp;
	}
}

void free_rooms_list(struct rooms *root)
{
	struct rooms * temp;
	while(temp != NULL){
		temp = root->next;
  		free(root);
  		root = temp;
	}
}

void get_by_floor(struct rooms *root, int floor_number)
{
	struct rooms *iter = root;
	while(iter != NULL){
		if(iter->floor == floor_number){
			printf("%d\n", iter->number);
		}
		iter = iter->next;
	}
}

void print_list(struct rooms *root)
{
	struct rooms *iter_room = root;
	struct customers *iter_customer;
	while(iter_room != NULL){
		printf("Room %d(Floor %d - Capacity %dx\n", iter_room->number, iter_room->floor, iter_room->capacity);
		iter_customer = iter_room->head;
		if(iter_customer == NULL)
			printf("Empty\n");
		while(iter_customer != NULL){
			printf("-> %s %s(%d - %s)\n", iter_customer->name, iter_customer->surname, iter_customer->age, iter_customer->gender);
			iter_customer = iter_customer->next;
		}
		iter_room = iter_room->next;
	}
}

struct rooms get_room(FILE * file_name)
{
	struct rooms room;
	char ch;
	fscanf(file_name, "%d%c%d%c%d", &room.number, &ch, &room.capacity, &ch, &room.floor);
	return room;
}
