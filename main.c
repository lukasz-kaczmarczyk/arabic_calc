#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ROMAN[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define SIZE_BUFFER 20
#define ROMAN_QUANTITY 7

char buffer1[SIZE_BUFFER];
char buffer2[SIZE_BUFFER];
char l1[] = "CCCLVII"; //357 CCC

char l2[] = "CLII"; //152		DIX

void modify(char *value, char *buffer);
void concatenate(char *val1, char *val2);
void sort(char *in);

int main(int argc, char *argv[]) {
	
	printf("l1: %s\n", l1);
	printf("l2: %s\n", l2);
	modify(l1, buffer1);
	modify(l2, buffer2);
	printf("buffer1: %s\n", buffer1);
	printf("buffer2: %s\n", buffer2);
	
	concatenate(buffer1, buffer2);
	printf("concatenate: %s\n", buffer1);
	
	sort(buffer1);
	printf("sorted: %s\n", buffer1);
	
	compute(buffer1);
	printf("computed: %s\n", buffer1);
	return 0;
}


/*
	modification:
	IV to IIII
	IX to VIIII
	XL to XXXX
	XC to LXXXX
	CD to CCCC
	CM to DCCCC
*/
void modify(char *value, char *buffer)
{
	char res[20];
	char *it = value;
	int i = 0, j, k = 0;

	while ('M' == *it) { //put M, segmentation fault possible???
		buffer[k] = ROMAN[0];
		++k;
		++it;
	}
	++i;
	
	
	while (i < ROMAN_QUANTITY) { 
		

		while (ROMAN[i] == *it) {
			
			if (i % 2) {
				while (ROMAN[i] == *it) { //put M, segmentation fault possible???
					buffer[k] = ROMAN[i];
					++k;
					++it;
					
				}
			} else {
				
		
				if (ROMAN[i-1] == *(it+1)) { //check next
					for(j = 0; j < 4; j++) { //put 4x the same letter
						buffer[k] = ROMAN[i];
						++k;
						
						
					}
					++it;
				} else if (ROMAN[i-2] == *(it+1)) { //check next
					buffer[k] = ROMAN[i-1];
					
					
					++k;
					for(j = 0; j < 4; j++) { //put 4x the same letter
						buffer[k] = ROMAN[i];
						
						++k;
					}
					it = it+2;	
				} else {
					buffer[k] = ROMAN[i];					
					++k;
					++it;
				}
			}

		}
		++i;
		
	}
	
	//buffer[k] = '0';
	
	
}

void concatenate(char *val1, char *val2)
{
	char i, j;
	
	for(i = 0; val1[i] != '\0'; ++i);

    	for(j = 0; val2[j] != '\0'; ++j, ++i)
    	{
        	val1[i] = val2[j];
    	}

    	val1[i] = '\0';
    //printf("After concatenation: %s", val1);
}

void sort(char *in)
{
	printf("sort in\n");
	char tmp[20];
	char *it = tmp;
	int i = 0, j = 0;
	while (i < ROMAN_QUANTITY) {
		
		while ('\0' != in[j]) {

			if(ROMAN[i] == in[j]) {
				*it = ROMAN[i];
				++it;
			}
			++j;
		}
		j = 0;
		++i;
	}
	*it = '\0';
	memcpy(in,tmp, 20);
}

void compute(char *in) {
	char tmp[20] = {0};
	char *it = tmp; //iterator to put in new buffer
	int i = 0, j = 0;
	int repeat = 0;
	int k = 0;
	
	
	while ('\0' != in[j]) { 
		while (ROMAN[i] == in[j]) { 			//check by roman letter from list, j iterator
			if (i % 2) {				//D,L,V occured
				if (in[j] == in[j+1]) {		//double time, swap 
					*it = ROMAN[i-1];	//put proper symbol
					printf("added: %c\n", *it);
					++it;
					j += 2;
				} else {			//D,L,V single occured
					*it = ROMAN[i];
					printf("added: %c\n", *it);
					++it;
					++j;
				}
			} else {				//M,C,X,I occured
					*it = ROMAN[i];
					printf("added: %c\n", *it);
					printf("it point to addr: %p\n", it);
					++it;
					++j;
					++repeat;
			}
		}
		//printf("iterator: %c\n", *(it+2));
		printf("it at the end point to addr: %p\n", it);
		
		if(4 == repeat) {
			for (k = 0; k < 3; ++k) { //delete redundant symbol
				--it;
				//--j;
				printf("delete from addr: %p\n", it);
				*it = ' ';
			}
			*it = ROMAN[i-1];
			printf("swapped to: %c\n", *it);
			++it;
		} else if (5 == repeat) {
				for (k = 0; k < 5; ++k) { //delete redundant symbol
				--it;
				//--j;
				*it = ' ';
			}
			*it = ROMAN[i-1];
			++it;
		}
		++i;
		
		repeat = 0;
	}
	
	memcpy(in,tmp, 20);
	
}
