/*
algorithm:
1. modify num1
2. modify num2
3. concateanate num1 and num2
4. sort
5. compute result
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_BUFFER 20
#define ROMAN_QUANTITY 7
#define NR_OF_DATA	4

const char ROMAN[] = {'M','D','C','L','X','V','I'};
char tmp[SIZE_BUFFER] = "MMMLL ";


char buffer1[SIZE_BUFFER];
char buffer2[SIZE_BUFFER];

char *l1 = "CCCLVII";
char *l2 = "CLII"; 

char *l3 = "I";
char *l4 = "I"; 

char l5[] = "V";
char l6[] = "V"; 

char l7[] = "V";
char l8[] = "X"; 

char l9[] = "IV";
char l10[] = "IX"; 


char *data[2][NR_OF_DATA] = {0};

void modify(char *value, char *buffer);
void concatenate(char *val1, char *val2);
void sort(char *in);
void compute(char *in);
void rev(char *in);

int main(int argc, char *argv[]) {
   
   	//data set 1
   	data[0][0] = l1;
   	data[1][0] = l2;
   	
   	//data set 2
   	data[0][1] = l3;
   	data[1][1] = l4;
   	
	//data set 3
   	data[0][2] = l5;
   	data[1][2] = l6;
   	
   	//data set 4
   	data[0][3] = l7;
   	data[1][3] = l8;
   	
   	int i;
   	for (i = 0; i < NR_OF_DATA; i++) {
   		printf("number 1: %s\n", data[0][i]);
		printf("number 2: %s\n", data[1][i]);
		
		modify(data[0][i], buffer1);
		modify(data[1][i], buffer2);
		
		concatenate(buffer1, buffer2);
		sort(buffer1);	   
		compute(buffer1);
		
		printf(" %s + %s = %s\n\n", data[0][i], data[1][i], buffer1);
		memset(buffer1,0,strlen(buffer1));
		memset(buffer2,0,strlen(buffer2));
   		
	}

	
	/*
	   	printf("number 1: %s\n", data[0][3]);
		printf("number 2: %s\n", data[1][3]);
		
		modify(data[0][3], buffer1);
		modify(data[1][3], buffer2);
		
		concatenate(buffer1, buffer2);
		sort(buffer1);	  
		printf("after sort operation: %s\n", buffer1); 
		compute(buffer1);
		
		printf(" %s + %s = %s\n\n", data[0][3], data[1][3], buffer1);

	*/


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

    while ('M' == *it) { 				//put M, segmentation fault possible???
        buffer[k] = ROMAN[0];
        ++k;
        ++it;
    }
    ++i;
   
   
    while (i < ROMAN_QUANTITY) {
       

        while (ROMAN[i] == *it) {
           
            if (i % 2) {
                while (ROMAN[i] == *it) { 		//put M, segmentation fault possible???
                    buffer[k] = ROMAN[i];
                    ++k;
                    ++it;
                   
                }
            } else {
               
       
                if (ROMAN[i-1] == *(it+1)) { 		//check next symbol
                    for(j = 0; j < 4; j++) { 		//put 4x the same letter
                        buffer[k] = ROMAN[i];
                        ++k;
                       
                       
                    }
                    ++it;
                } else if (ROMAN[i-2] == *(it+1)) { 	//check next
                    buffer[k] = ROMAN[i-1];
                   
                   
                    ++k;
                    for(j = 0; j < 4; j++) { 		//put 4x the same letter
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
	int i = 6, j = 1, k = 0, count = 0; 	
	  

	   

	
	while (i >= 0) {
		
		for (;'\0' != *it; ++it);            		//go to the last symbol        
		--it;
	
       
        	while ((ROMAN[i] != *it)&&(it != in)) 		//find symbol in number
        		--it;
		
		if (ROMAN[i] == *it)				//found symbol, count
			++count;
		
//-------------------------------------------------------       

   
    		while (*it == *(it-1)) {    			//count the same symbol
        		count += 1;
        		--it;
			              
        		if (it == in)            		//break if it first value in number
            			break;
            		
    		}   
       
       
    		if (!(i%2) && (i > 0)) {			//I, X, C handling
	        	switch (count) {
			        case 4:                    	
			        
			        	if (ROMAN[i-1] == *(it-1)) {		//put XI or CX or MC	
			                	*it_res = ROMAN[i-2];
			                	++it_res;
			                	*it_res = ROMAN[i];
			                	++it_res;
			                	--it;
			                	*it = ' ';
			                	
			                	
					} else {				
						*it_res = ROMAN[i-1];		//put VI or LX or DC
			                	++it_res;
			                	*it_res = ROMAN[i];
			                	++it_res;
						
					}

			                
			        break;
			        case 5:                    	//put V or L or D
					
			                *it_res = ROMAN[i-1];
			                ++it_res;   
					
			        break;
			        case 6:                    	//put IV or XL or CD
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i-1];
			                ++it_res;
			        break;
			        case 7:                    	//put IIV or XXL or CCD
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i-1];
			                ++it_res;
			               
			        break;
			        case 8:                    	//put IIIV or XXXL or CCCD
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i];
			                ++it_res;
			                *it_res = ROMAN[i-1];
			                ++it_res;
			        break;

			        default:                	//single, double or triple symbol
			                for (k = 0; k < count; ++k) {
			                	*it_res = ROMAN[i];
			                	++it_res;   
			                }
			        }
		} else if ((i%2) && i > 0) {			//V L D handling
			
			if (2 == count) {
				
				*it = ROMAN[i-1];
			} else if (1 == count){
				*it_res = ROMAN[i];
		               	++it_res;   
			}
			
		} else if (0 == i) {				//M handling
			for (k = 0; k < count; ++k) {
		               	*it_res = ROMAN[i];
		               	++it_res;   
		        }
		}				
		--i;
		
		
		//it = in;
		count = 0;
               
        }
	*it_res = ' ';						//last symbol put: " "
	rev(res);						//reverse score
	memcpy(in,res, 20);
}

/*							*
 *	last of character must be: " " symbol		*
 *							*/			
void rev(char *in) {
	char *pos2 = in;
	char *pos1 = in;
	char tmp;
	
	while (' ' != *pos2) 					//find last symbol
		++pos2;
	--pos2;
	
	while (pos2 > pos1) {
		tmp = *pos1;
		*pos1 = *pos2;
		*pos2 = tmp;
		
		++pos1;
		--pos2;
	}
	
}
