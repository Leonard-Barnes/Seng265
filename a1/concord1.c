#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EX_WORDS 21
#define MAX_WORD_LEN 21
#define MAX_LINES 101
#define MAX_LINE_LEN 71
#define MAX_DIS_WORDS 101
int num_words = 0;

void final_print(char*, char*, int);

void to_upper(char*, int);

void tokenize_line(char *);

int compare_str_backwards(const void *, const void *);

int compare_str(const void *, const void *);

char All_Words[MAX_DIS_WORDS+MAX_EX_WORDS][MAX_WORD_LEN];

int main(){

        char start[MAX_LINE_LEN];
        fgets(start, MAX_LINE_LEN, stdin); //Removes first two lines
	fgets(start, MAX_LINE_LEN, stdin);
	
	char Ex_Words[MAX_EX_WORDS][MAX_WORD_LEN];

        int Ex_Lines_num = 0;
	fgets(Ex_Words[Ex_Lines_num], MAX_EX_WORDS, stdin);
        while(strncmp(Ex_Words[Ex_Lines_num], "\"\"\"\"\n", MAX_WORD_LEN)!= 0 && (Ex_Lines_num < MAX_EX_WORDS)){
            	 //Fills Ex_Words with all exclusion words
            	Ex_Lines_num++;
            	fgets(Ex_Words[Ex_Lines_num], MAX_EX_WORDS, stdin);
        }

	char Input_Lines[MAX_LINES][MAX_LINE_LEN];

	int Lines_num = 0;

	char Safe_Input_Lines[MAX_LINES][MAX_LINE_LEN];
	
	char Extra_Safe_Input_Lines[MAX_LINES][MAX_LINE_LEN];
	//creates an array of all the lines, and some copies
	//int counter = 0;
	while(fgets(Input_Lines[Lines_num], MAX_LINE_LEN, stdin)){
		/*
		counter = 0;
		while(All_Words[Lines_num][counter] != '\n' && All_Words[Lines_num][counter] != '\0'){
			counter++;
		}
		All_Words[Lines_num][counter] = '\0';
		*/
		strncpy(Safe_Input_Lines[Lines_num], Input_Lines[Lines_num], MAX_LINE_LEN);
		strncpy(Extra_Safe_Input_Lines[Lines_num], Input_Lines[Lines_num], MAX_LINE_LEN);
		Lines_num++;
	}
	//creates an array of all words	
	for(int i = 0; i < Lines_num; i++){
		tokenize_line(Input_Lines[i]);
	}
	// removes Exclusion words from the list
 	char temp[MAX_WORD_LEN];
	int Ex_Words_C = 0;
	for(int i = 0; i < num_words; i++){
		strncpy(temp, All_Words[i], MAX_WORD_LEN);
		
		if(temp[strlen(temp)-1] == '\n'){
			temp[strlen(temp)-1] = '\0';
		}

		strncat(temp, "\n", MAX_WORD_LEN);
		
		for(int j = 0; j < Ex_Lines_num; j++){
			if(strncmp(temp, Ex_Words[j], MAX_WORD_LEN)== 0){
				strncpy(All_Words[i], "\0",  MAX_WORD_LEN); 
				Ex_Words_C++;
			}
		}
	}
	
	//organized the words
	
	qsort(All_Words, num_words, sizeof(char)*MAX_WORD_LEN, compare_str_backwards);
	for( int i = 0; i < Ex_Words_C; i++){
		num_words--;
	}
	
	qsort(All_Words, num_words, sizeof(char)*MAX_WORD_LEN, compare_str);	
	
	//removes duplicate words
	
	int doubles = 0;
	for(int j = 1; j < num_words; j++){
		
        	if(strncmp(All_Words[j], All_Words[j-1], MAX_WORD_LEN)== 0){
                	strncpy(All_Words[j-1], "\0",  MAX_WORD_LEN);
			doubles++;
                }		
        }

	qsort(All_Words, num_words, sizeof(char)*MAX_WORD_LEN, compare_str_backwards);

        for( int i = 0; i < doubles; i++){
                num_words--;
        }

        qsort(All_Words, num_words, sizeof(char)*MAX_WORD_LEN, compare_str);
	
	for(int j = 0; j < num_words; j++){
	
		char temp[MAX_WORD_LEN];

        	strncpy(temp, All_Words[j], MAX_WORD_LEN);

        	temp[strlen(temp)-1] = '\0';

        	if(strncmp(temp, All_Words[j-1], MAX_WORD_LEN) == 0){

			strncpy(All_Words[j-1], All_Words[j], MAX_WORD_LEN);	
			strncpy(All_Words[j], temp, MAX_WORD_LEN);
        	}
	}
	
	//Does the rest of the project	
	
	for(int l = 0; l < num_words; l++){
	    for(int i = 0; i < Lines_num; i++){
		char Active_Line[MAX_WORD_LEN][MAX_LINE_LEN];
	
		for(int h = 0; h < Lines_num; h++){
			strncpy(Safe_Input_Lines[h], Extra_Safe_Input_Lines[h], MAX_LINE_LEN);
		} 
		int Words_In_Active_Line = 0;

		char *Q;

		Q = strtok (Safe_Input_Lines[i], " ");
		while (Q && Words_In_Active_Line < MAX_DIS_WORDS){
                	strncpy (Active_Line[Words_In_Active_Line], Q, MAX_WORD_LEN);
                	Words_In_Active_Line++;
                	Q = strtok (NULL, " ");
       		 }	
		int index = 0;
		for(int j = 0; j < Words_In_Active_Line; j++){
				
			if(strncmp(All_Words[l], Active_Line[j], MAX_WORD_LEN)==0){
				final_print(Extra_Safe_Input_Lines[i], Active_Line[j], index);
			}else{
				index += strlen(Active_Line[j]);
				index++;
			}
		} 
	
	    }
	}
}

 
int compare_str_backwards(const void *a, const void *b){
	const char* ia = (char *)a;
	const char* ib = (char *)b;
	return strncmp(ia, ib, MAX_WORD_LEN)*-1;
}

int compare_str(const void *a, const void *b){
        const char* ia = (char *)a;
        const char* ib = (char *)b;
        return strncmp(ia, ib, MAX_WORD_LEN);
}

void tokenize_line (char *line){
        char *Q;

        Q = strtok (line, " ");
        while (Q && num_words < MAX_DIS_WORDS){
                strncpy (All_Words[num_words], Q, MAX_WORD_LEN);
                num_words++;
                Q = strtok (NULL, " ");
        }
        return;
}

void final_print(char *line, char *word, int index){
	int Word_Chars = 0;
	char ch = word[0];
	int i = 1;
	while(ch != '\0' && ch != '\n'){
		ch = word[i];
		i++;
		Word_Chars++;
	}
	
	for(int i = 0; i < Word_Chars; i++){
                line[index + i] = toupper(line[index + i]);
        }	
	printf("%s", line);

	for(int i = 0; i < Word_Chars; i++){
                line[index+i] = tolower(line[index+i]);
        }
}













