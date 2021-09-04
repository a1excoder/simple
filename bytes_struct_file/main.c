#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	char name[25];
	int8_t age;
} user;

#define SZU sizeof(user)

void view_user(user *up);
void insert(char *fname, user *up);
void get_user(char *fname, int id);
void remove_file(char *fname);

int main(void)
{

	char *fname = "users.dat";

	user u1 = {"Vlad Mirgorodov", 17};
	user u2 = {"Nastya Crack", 16};

	insert(fname, &u1);
	insert(fname, &u2);

	get_user(fname, 2);
	get_user(fname, 1);

	return 0;
}

void view_user(user *up) { printf("name: %s\nage: %d\n", up->name, up->age); }

void insert(char *fname, user *up)
{
	FILE *file = fopen(fname, "r+b");
	int count, szt = sizeof(int);
	char *cym;

	if (file != NULL) {
		// read count from file
		cym = (char*)&count;
		for (size_t inx = 0; inx < szt; inx++) {
			*cym = fgetc(file);
			cym++;
		}
		count++;

		// write new count in file
		rewind(file);
		cym = (char*)&count;
		for (size_t inx = 0; inx < szt; inx++) {
			fputc(*cym, file);
			cym++;
		}

		// add user
		fseek(file, SZU * count, 1);
		cym = (char*)up;
		for (size_t inx = 0; inx <= SZU; inx++) {
			fputc(*cym, file);
			cym++;
		}



		fclose(file);
	}
	else {
		file = fopen(fname, "wb");
		int first = 0;

		// write count in file
		cym = (char*)&first;
		for (size_t inx = 0; inx < szt; inx++) {
			fputc(*cym, file);
			cym++;
		}

		// write first user in file
		cym = (char*)up;
		for (size_t inx = 0; inx < SZU; inx++) {
			fputc(*cym, file);
			cym++;
		}

		fclose(file);
	}
}


void get_user(char *fname, int id)
{
	FILE *file = fopen(fname, "rb");
	int count, szt = sizeof(int);
	char *cym;

	user *up = (user*)malloc(SZU);

	if (file == NULL) {
		printf("[ERROR] - file <%s> not found.\n", fname);
	}
	else {
		// read count from file
		cym = (char*)&count;
		for (size_t inx = 0; inx < szt; inx++) {
			*cym = fgetc(file);
			cym++;
		}


		// get user
		cym = (char*)up;
		fseek(file, SZU * (id-1), SEEK_CUR);
		for (size_t inx = 0; inx <= SZU; inx++) {
			*cym = fgetc(file);
			cym++;
		}

		view_user(up);

		free(up);
		fclose(file);
	}
}

void remove_file(char *fname)
{
	if (!remove(fname))
		puts("[SUCCESS] -files was deleted.");
	else
		puts("[ERROR] - file not found.");
}

// not works
void delete_user(char *fname, int id)
{
	FILE *file = fopen(fname, "wb");
	int szt = sizeof(int);
	char *p;
	size_t sz = 0;

	if (file == NULL) {
		printf("[ERROR] - file <%s> not found.\n", fname);
	}
	else {
		fseek(file, szt + SZU * (id-1), 0);
		for (size_t i = 0; i <= SZU; i++) {
			//
		}

		fclose(file);
	}
}
