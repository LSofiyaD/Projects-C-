#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 50000
#include <stdlib.h>
#include <string.h>
#include <time.h> 

FILE* rezultfile;   
FILE* characteristicsfile;
FILE* logfile; 


//Пузырьковая сортировка 

void bublesort(int *inputarray,const int size) {

	fprintf(logfile, "1.Buble sort started!\n");
	int* array = 0;
	array = (int*)malloc(sizeof(int) * size);// определяем сколко памяти необходимо для массива  
	memset(array, 0, size);//для того, чтобы мусор опять не вылез в массиве 
	memcpy(array, inputarray, sizeof(int) * size);
	int srav = 0; 
	int replace = 0;
	long double starttime;
	long double stoptime;
	starttime = clock(); 
	for (int i = 0; i < size - 1; i++) {
		srav++;
		for (int j = 0; j < size - i - 1; j++) {
			srav++;
			if (array[j] > array[j + 1]) {
				replace++;
				int memory = array[j];
				array[j] = array[j + 1];
				array[j + 1] = memory;
			}
		}
	}
	stoptime = clock();
	fprintf(logfile, " The array is sorted!\n"); 
	printf("Bubble sort:\n");
	fprintf(rezultfile, "%d", array[0]);
	printf("%d", array[0]);
	for (int i = 1; i < size; i++) { 
		fprintf(rezultfile, ", %d", array[i]); 
		printf(", %d", array[i]);
	}
	printf("\n");
	fprintf(rezultfile, "\n"); 
	fprintf(logfile, " The result is written to a file!\n");
	fprintf(characteristicsfile,"Bubble sort: %d, %d, %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC);
	printf("Comparisons: %d, Movements: %d, Time: %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC);
	fprintf(logfile, " Characteristics are recorded in a file!\n");
	free(array);
}

//Быстрая сортировка 

void qs(int* array, int start, int end, unsigned long* srav, unsigned long* replace) {
	(*srav)++; 
	if (start < end) {
		int left = start;
		int right = end;
		int middle = array[(left + right) / 2]; // Центр сравнения

		while (left <= right) {
			(*srav)++; 
			while (array[left] < middle) {
				(*srav)++; 
				left++;
			}
			(*srav)++; 
			while (array[right] > middle) {
				(*srav)++; 
				right--;
			}
			if (left <= right) {
				int temp = array[left];
				array[left] = array[right];
				array[right] = temp;
				*replace += 3; 
				left++;
				right--;
			}
		}
		qs(array, start, right, srav, replace); 
		qs(array, left, end, srav, replace);
	}
}

void quicksort(int* inputarray, int size) {
	fprintf(logfile, "2.Quick sort started!\n");
	int* array = 0;
	array = (int*)malloc(sizeof(int) * size); 
	memset(array, 0, size); 
	memcpy(array, inputarray, sizeof(int) * size);
	int srav  = 0;
	int replace  = 0;
	long double starttime;
	long double stoptime;
	starttime = clock(); 
	qs(array, 0, size - 1,&srav,&replace);   
	stoptime = clock();
	fprintf(logfile, " The array is sorted!\n"); 
	printf("Quick sort:\n");
	fprintf(rezultfile, "%d", array[0]); 
	printf("%d", array[0]); 
	for (int i = 1; i < size; i++) { 
		fprintf(rezultfile, ", %d", array[i]); 
		printf(", %d", array[i]); 
	}
	printf("\n"); 
	fprintf(rezultfile, "\n"); 
	fprintf(logfile, " The result is written to a file!\n"); 
	fprintf(characteristicsfile,"Quick sort: %d, %d, %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC);
	printf("Comparisons: %d, Movements: %d, Time: %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC); 
	fprintf(logfile, " Characteristics are recorded in a file!\n"); 
	free(array);
}

//Сортировка вставками

void inputsort(int* inputarray, int size) {
	fprintf(logfile, "3.Insertion sort started!\n");
	int* array = 0; 
	array = (int*)malloc(sizeof(int) * size); 
	memset(array, 0, size); 
	memcpy(array, inputarray, sizeof(int) * size); 
	int srav = 0;  
	int replace = 0; 
	long double starttime; 
	long double stoptime; 
	starttime = clock(); 
	int memory = 0; 
	int middle = 0; 
	for (int i = 1; i < size; i++) {
		memory = array[i];
		int left = 0; 
		int right = i - 1; 
		while (left <= right) {  
			middle = left + (right - left) / 2;  
			srav++; 
			if (array[middle]  > memory) { 
				right = middle-1; 
 			}
			else { 
				left = middle + 1;  
			} 
		}
		for (int j = i; j > left; j--) {
			array[j] = array[j - 1];
			replace ++;
		}
		array[left] = memory;  
		replace++;
	}
	stoptime = clock(); 
	fprintf(logfile, " The array is sorted!\n");
	printf("Insertion sort:\n");
	fprintf(rezultfile, "%d", array[0]); 
	printf("%d", array[0]); 
	for (int i = 1; i < size; i++) {
		fprintf(rezultfile, ", %d", array[i]); 
		printf(", %d", array[i]);
	}
	fprintf(rezultfile, "\n");
	printf("\n");
	fprintf(logfile, " The result is written to a file!\n"); 
	fprintf(characteristicsfile,"Insertion sort: %d, %d, %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC); 
	printf("Comparisons: %d, Movements: %d, Time: %Lf\n", srav, replace, (stoptime - starttime) / CLOCKS_PER_SEC);
	fprintf(logfile, " Characteristics are recorded in a file!\n");
	free(array);
}



int main() {
	
	time_t mytime = time(NULL); 
	struct tm* now = localtime(&mytime); 

	char rezname[200];
	sprintf(rezname, "rezult_%02d_%02d_%02d_%02d_%02d.txt", now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900); 
	rezultfile = fopen(rezname, "a"); 
	
	char chname[200];
	sprintf(chname, "characteristics_%02d_%02d_%02d_%02d_%02d.txt",now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900); 
	characteristicsfile = fopen(chname, "a");  

	char logname[200];
	sprintf(logname, "log_%02d_%02d_%02d_%02d_%02d.txt",now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900); 
	logfile = fopen(logname, "a"); 


	int way = 0; 
	printf("Choose way of work:\n1 - Random array\n2 - Own file\n");
	scanf("%d", &way); 

	if (way == 1) { 
		int random_array[SIZE];
		srand(time(0));
		for (int i = 0; i < SIZE; i++) {
			random_array[i] = rand() % 100000;
		}
		printf("Array:\n");
		for (int i = 0; i < SIZE; i++) {
			printf("%d ", random_array[i]);
		}
		printf("\n");
		fprintf(logfile, "Created a random array!\n"); 
		bublesort(random_array, SIZE);
		quicksort(random_array, SIZE);
		inputsort(random_array, SIZE);
		
	}

	else if (way == 2) {
		int *array;
		array = (int*)malloc(sizeof(int) * SIZE);
		char nameoffile[100]; 
		int i = 0;
		int size=0; 
		printf("Print name of file with extension:");
		scanf("%s", &nameoffile); 
		FILE* workfile = fopen(nameoffile, "r"); 
		if (workfile == NULL) {
			printf("Error.\n");
		}
		else {
			for (i = 0; i < SIZE && !feof(workfile); i++) {
				fscanf(workfile, "%d", &array[i]);
			}
			size = i; 
		}
		fclose(workfile);
		fprintf(logfile, "Converted users file!\n"); 
		bublesort(array, size);  
		quicksort(array, size);  
		inputsort(array, size); 

	}
	else {
		printf("Restart a program and write a correct way of work!");
	}
	fprintf(logfile, "The array is sorted in three ways!\n"); 
	return 0;
}