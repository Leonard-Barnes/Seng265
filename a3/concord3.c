/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"
#include <ctype.h>
/*
void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}


#ifdef DEBUG


 Just showing the use of the linked-list routines.


void _demo() {
printf("DEBUG: in _demo\n");
    char *words_german[] = {"Der", "Kater", "mit", "Hut."};
    int   words_german_len = 4;

    char *words_english[] = {"The", "cat", "in", "the", "hat."};
    int   words_english_len = 5;

    node_t *temp_node = NULL;
    node_t *head = NULL;

    int i;

    //Add the words in German, at the front.
    for (i = 0; i < words_german_len; i++) {
        temp_node = new_node(words_german[i]);
        head = add_front(head, temp_node);
    }

    //Add the words in English, at the end.
    for (i = 0; i < words_english_len; i++) {
        temp_node = new_node(words_english[i]);
        head = add_end(head, temp_node);
    }

    //Print the list of words.

    apply(head, print_word, "--> %s\n");

    //Free up the memory. This is done rather deliberately
    //and manually.  Asserts are liberally used here as they
    //express state that *must* be true if all of the code is
    //correctly working.

    temp_node = head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        head = remove_front(head);
        free(temp_node);
        temp_node = head;
    }
   
    assert(head == NULL); 
}

#endif
*/

#define KEYWORD_LEN 40
#define LINE_LEN 101

//create list of all ex_words
node_t* ex_word_creation(){
	node_t *ex_words_head = NULL;
	char temp[KEYWORD_LEN];
	fgets(temp, KEYWORD_LEN, stdin);
	ex_words_head = add_end(ex_words_head, new_node(temp));
	node_t *cur = ex_words_head;
	while(strncmp(cur->text, "\"\"\"\"\n", KEYWORD_LEN) != 0){
		char cur_word[KEYWORD_LEN];
		fgets(cur_word, KEYWORD_LEN , stdin);
		add_end(ex_words_head, new_node(cur_word));
		cur = cur->next;
	}
	return ex_words_head;
}

//free all the elements of a list
void free_list(node_t* a){
	node_t *cur = a;
	while(a != NULL){
		cur = a;
		a = a->next;
		free(cur);	
	}
}

//creates a linked list with a node for each line
node_t* all_lines_creation(){
	node_t *all_lines_head = NULL;
	char temp[LINE_LEN];
	fgets(temp, LINE_LEN, stdin);
	all_lines_head = add_end(all_lines_head, new_node(temp));
	node_t *cur = all_lines_head;
	while(fgets(temp, LINE_LEN, stdin)){
		add_end(all_lines_head, new_node(temp));
		cur = cur->next;			
	}
	return all_lines_head;
}

//creates a linked list of every word
node_t* create_list_of_words(node_t* A, node_t* E){
	node_t *all_words_head = NULL;
	char temp[LINE_LEN];
	node_t* cur = A;
	int check = 1;
	while(cur != NULL){
		strncpy(temp, cur->text, LINE_LEN);
		char *Q;
		Q = strtok(temp, " ");
		while(Q){
			if(check == 1){
				all_words_head = add_end(all_words_head, new_node(Q));
				check--;
			}else{
				add_end(all_words_head, new_node(Q));
			}
			Q = strtok(NULL, " ");	
		}
		cur = cur->next;
	}
	return all_words_head;
}

//Code mainly influence from Lab 8
node_t *clean_and_order(node_t * list, node_t *new, node_t *E) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    node_t *currE = E;
    while(currE){	
	if(strcasecmp(new->text, currE->text) == 0){
	    free_list(new);
	    return list;
	}
	currE = currE->next;
    }	

    if (list == NULL) {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        if(strcasecmp(new->text, curr->text) == 0){
		free(new);
		return list;
	}else if (strcasecmp(new->text, curr->text) > 0) {
            prev = curr;
        } else {
            break;
        }
    }
    new->next = curr;

    if (prev == NULL) {
	return (new);
    } else {
        prev->next = new;
        return list;
    }
}

//checks to see if line contains the word
int in_line(char* word, node_t* line){
	int in_line_check = 0;
	node_t* words_in_line = NULL;
	char temp[LINE_LEN];
	strncpy(temp, line->text, LINE_LEN);
	char *Q;
	Q = strtok(temp, " ");
	int one_time = 1;
	while(Q){
		if(one_time == 1){
			words_in_line = add_end(words_in_line, new_node(Q));
			one_time--;
		}else{
			add_end(words_in_line, new_node(Q));
		}
		Q = strtok(NULL, " ");
	}

	node_t* cur = words_in_line;
	while(cur){
		if(strcasecmp(word,cur->text)==0){
			in_line_check++;
		}
		cur = cur->next;
	}	
	free_list(words_in_line);
	free_list(line);
	return in_line_check;
}

//break down a line into a list of words
node_t* break_line(node_t* line){
	node_t* A = NULL;
	char temp[LINE_LEN];
	strncpy(temp, line->text, LINE_LEN);
	char *Q;
	Q = strtok(temp, " ");
	int one_time = 1;
	while(Q){
		if(one_time == 1){
			A = add_end(A, new_node(Q));
			one_time--;
		}else{
			add_end(A, new_node(Q));
		}
		Q = strtok(NULL, " ");
	}
	return A;
}

//cuts the extra off the front of the line
node_t* crop_line_front(node_t* line, char* word){
	node_t* final = line;
	node_t* cur = line;
	int len = 0;
	while (strcasecmp(cur->text, word)){
		len = len + strlen(cur->text) + 1;
		cur = cur->next;
	}
	while(len>20){
		len = len - 1 - strlen(final->text);
		final = final->next;
	}
	return final;
}

//cuts the extra off the back of the line
node_t* crop_line_back(node_t* line, char* word){
	node_t* final = line;
	node_t* cur = line;
	int len = 0;
	while(strcasecmp(cur->text, word)){
		cur = cur->next;
	}

	node_t* cur1 = cur;
	while(cur){
		len = len + strlen(cur->text) + 1;
		cur = cur->next;
	}
	len--;
	len--;
	cur = cur1;
	node_t* cur2 = cur;
	while(len>30){
		
		while(cur1->next != NULL){
			cur1 = cur1->next;
		}
		
		len = len - 1 - strlen(cur1->text);
		
		while(cur2->next != cur1){
			cur2 = cur2->next;	
		}
		free_list(cur2->next);
		cur2->next = NULL;
		cur2 = cur;
		
		cur1 = cur;
	}
	return final;
}

//prints and capializes the line
void print_line(node_t* line, char* word){
	node_t* broken_line = break_line(line);
	node_t* cur = broken_line;
	cur = crop_line_front(cur, word);
	cur = crop_line_back(cur, word);
	node_t* len = cur;
	int len_before = 0;
	while(strcasecmp(len->text, word)){
		len_before = len_before + 1 + strlen(len->text);
		len = len->next;
	}
	for(int i = 0; i < (29 - len_before); i++){
		printf(" ");
	}
	while(cur){
		if(strcasecmp(cur->text, word)==0){
			for(int i = 0; i < strlen(cur->text); i++){
				printf("%c",toupper(cur->text[i]));
			}
		}else{
			printf("%s", cur->text);
		}
		if(cur->next){
			printf(" ");
		}
		cur = cur->next;	
	}
	printf("\n");
	free_list(broken_line);
	free_list(line);
}
//prints all the lines in order
void print_all_lines(node_t* words, node_t* lines){
	node_t* cur_words = words;
	node_t* cur_lines = lines;
	while(cur_words){
		char word[KEYWORD_LEN];
		strncpy(word, cur_words->text, KEYWORD_LEN);
		while(cur_lines){
			if(in_line(word, new_node(cur_lines->text))){
				print_line(new_node(cur_lines->text), word);
			}
			cur_lines = cur_lines->next; 
		}
		cur_lines = lines;
		cur_words = cur_words->next;
	}
	return;
}

int main(int argc, char *argv[])
{ 

	char JUNK[LINE_LEN]; //create junk array for first 2 lines
	fgets(JUNK, LINE_LEN, stdin);
	if(JUNK[0] == '1'){ //version check
		printf("Input is version 1, concord3 expected version 2");
		exit(1);
	}

	fgets(JUNK,LINE_LEN,stdin);//remove the '''' from the input
	node_t *ex_words = ex_word_creation();
	node_t *cur = ex_words;
	int ex_words_count = 0;
	while(cur->next != NULL){
		ex_words_count++;
		cur->text[strlen(cur->text)-1] = '\0';
		cur = cur->next;
	}
	node_t *all_lines = all_lines_creation();	
	cur = all_lines;
	int all_lines_count = 0;

	while(cur != NULL){
		all_lines_count++;
		cur->text[strlen(cur->text)-1] = '\0';
		cur = cur->next;
	}

	node_t *all_words = create_list_of_words(all_lines,ex_words);
	node_t *clean_words = NULL;
	cur = all_words;
	while(cur){
		clean_words = clean_and_order(clean_words, new_node(cur->text), ex_words);
		cur = cur->next;
	}

	print_all_lines(clean_words, all_lines);

	//memory free
	free_list(ex_words);
	free_list(all_lines);
	free_list(all_words);
	free_list(clean_words);
}
