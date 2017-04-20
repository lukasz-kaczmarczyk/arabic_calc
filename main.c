/*
issues: 'M' not added
to do:
V,L,D handling
reverse computing result
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ROMAN[] = {'M','D','C','L','X','V','I'};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define SIZE_BUFFER 20
#define ROMAN_QUANTITY 7

char tmp[20] = "MMCCCXIIII";

char buffer1[SIZE_BUFFER];
char buffer2[SIZE_BUFFER];
char l1[] = "CCCLVII"; //357 CCC

char l2[] = "CLII"; //152        DIX


void modify(char *value, char *buffer);
void concatenate(char *val1, char *val2);
void sort(char *in);
void compute(char *in);

int main(int argc, char *argv[]) {
   
   /*
    printf("l1: %s\n", l1);
    printf("l2: %s\n", l2);
    modify(l1, buffer1);
    modify(l2, buffer2);
    printf("buffer1: %s\n", buffer1);
    printf("buffer2: %s\n", buffer2);
   
    concatenate(buffer1, buffer2);
   
    sort(buffer1);
    printf("after sort %s\n", buffer1);
    */
   
    compute(tmp);
    printf("after sum operation: %s\n", tmp);
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
}

void sort(char *in)
{
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


void compute(char * const in) {
	char res[20] = {0};
	int found = 0;
	char *it = in, *it_res = res;
	int i = 6, j = 1, k = 0, count = 0; //count -1 becouse it helps if not found
	  

	   
	    //printf("----*it: %c\n ", *it);
	
	while (i >= 0) {
		
		for (;'\0' != *it; ++it);            //go to the last symbol        
		--it;
	
       
        	while ((ROMAN[i] != *it)&&(it != in)) {		//find symbol in number
        	
        		--it;
        		printf("while ((ROMAN[i] != *it)&&(it != in)) \n");
		}  
		
		if (ROMAN[i] == *it)				//found symbol
		{
			++count;
			printf("-------found: %c\n", *it);
		}
			//++count;
//-------------------------------------------------------       
    		printf("====found -> ROMAN[i]: %c, i: %d, *it: %c\n", ROMAN[i], i, *it);
   
    		while (*it == *(it-1)) {    			//count the same symbol
        		count += 1;
        		--it;
        		printf("count: %d\n", count);
              
        		if (it == in) {           //break if it first symbol
        			printf("!!!it == in, break\n");
            			break;
            		}
       			printf("not break in counting\n");
    		}         //the last segmentation fault???
       
       
        	printf("count: %d of symbol: %c\n", count, ROMAN[i]);                        //put in reverse way
    		if (!(i%2) && (i > 0)) {
    	
        	switch (count) {
		        case 4:                    //put VI or LX or DC
		        	*it_res = ROMAN[i-1];
		                ++it_res;
		                *it_res = ROMAN[i];
		                ++it_res;
		        break;
		        case 5:                    //put V or L or D
		                *it_res = ROMAN[i-1];
		                ++it_res;   
		        break;
		        case 6:                    //put IV or XL or CD
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i-1];
		                ++it_res;
		        break;
		        case 7:                    //put IIV or XXL or CCD
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i-1];
		                ++it_res;
		               
		        break;
		        case 8:                    //put IIIV or XXXL or CCCD
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i];
		                ++it_res;
		                *it_res = ROMAN[i-1];
		                ++it_res;
		        break;
		        case 9:
		                //NOT POSSIBLE?
		        break;
		           
		        default:                //single, double or triple symbol
		                for (k = 0; k < count; ++k) {
		                	*it_res = ROMAN[i];
		                	printf("default statement\n");
		                	++it_res;   
		                }
		        }
		}
		--i;
		it = in;
		count = 0;
               
        }
	
	printf("next loop\n");
	memcpy(in,res, 20);
}
