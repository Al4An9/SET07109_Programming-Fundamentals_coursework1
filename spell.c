/*	Title: "Spell Checker"
	Author: Alexandros Anastasiou
	Date: 26/02/2017 	
	Description: gets words from dictionary saves them in an array. Gets test files and checks if they have spelling mistakes
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>


//this function reads the dictionary and writes it in an array
//it also get the number of lines of the file
void read_dictionary (char ***data , int *dic_line_counter)
{

	FILE *file = fopen ("dictionary.txt", "r");
	
	char read[100];
	
	int lines_length = 0;
	
	int counter = 1;
	
	//reads every line of the input 
	while (fgets(read , 100 , file))
	{
		lines_length++;
	}
	
	rewind(file);
	//allocates memory for every line
	(*data) = (char**)malloc(lines_length * sizeof(char *));

	for (int m = 1; m < lines_length; m++)
	{
		fgets(read , 100 , file);
		//allocates memory for every character of every word + 1 for null terminator
		(*data)[m] = (char*)malloc(strlen(read) * sizeof(char) + 1);
		//copies every line to the array 
		strcpy((*data)[m] , read);
		//printf("%s\n", (*data)[m]);		
	}
	//counter for every line of the dictionary
	while (counter < lines_length)
	{
		counter++;
	}	
	(*dic_line_counter) = counter;
	//printf("%d\n", (*dic_line_counter));
			
	fclose(file);
}

///this function reads the input file(single words) and writes it in an array 
//it also gets the number of lines of the file
void read_single_words (char ***data , int *inp_line_counter)
{

	FILE *file1 = fopen ("single_words_test.txt", "r");
	
	char inp_read_lines[100];
	
	int inp_lines = 0;
	
	int counter = 1;
	
	//reads every line of the input 
	while (fgets(inp_read_lines , 100 , file1))
	{	
		inp_lines++;
	}
	
	rewind(file1);
	//allocates memory for every line 
	(*data) = (char**)malloc(inp_lines * sizeof(char *));
	
	for (int i=1; i < inp_lines; i++) 
	{
		fgets(inp_read_lines , 100 , file1);
		//allocates memory for every character of every word + 1 for null terminator
		(*data)[i] = (char*)malloc(strlen(inp_read_lines) * sizeof(char) + 1);
		//copies every line to the array 
		strcpy((*data)[i] , inp_read_lines);
		//printf ("%s\n", (*data)[i]);
	}
	//counter for every line of the input
	while (counter < inp_lines)
	{
		counter++;
	}
	(*inp_line_counter) = counter;
	//printf ("%d\n", (*inp_line_counter));
		
	fclose(file1);
}


//search for the input words in the dictionary	
void binary_search(char **input , int dic_line_counter , int inp_line_counter  , char **dictionary)
{
	//printf("Dictionary line counter %d", dic_line_counter);
	//printf ("Dictionary %s" , dictionary[1]);
	read_single_words (&input , &inp_line_counter);
	
	read_dictionary (&dictionary , &dic_line_counter);
	
	int first_line = 1;
	
	int last_line = dic_line_counter - 1;
	
	int middle_line;

	
	while (first_line <= last_line)
	{	
			middle_line = (first_line + last_line) / 2;
			if (strcmp(input[1], dictionary[middle_line]) == 0)
			{
				printf("%sWORD FOUND AT LINE %d.\n", input[1], middle_line);
				return;

			}
			else if (strcmp(input[1], dictionary[middle_line]) > 0)
			{
				first_line = middle_line + 1;
				//printf("word not found\n");
			}
			else if (strcmp(input[1], dictionary[middle_line]) < 0)
			{
				last_line = middle_line - 1;
				//printf("WORD NOT FOUND\n");
			}	
		
	}	
	
}

/*//this function reads the input file(sentences) and writes it in an array 
//it splits the sentences in lines for every space tab "," "?" "." "\n"
void read_sentences()
{
	FILE *file2 = fopen ("sentences_test.txt", "r");

	char inp_sentences[10000];
	
	char *spliter_token;
	
	fgets(inp_sentences , 10000 , file2);
	
	printf ("%s" , inp_sentences);
	
	spliter_token = strtok(inp_sentences , DELIM);
	
	//while (fgets(inp_sentences , 10000 , file2) !=NULL)
	for (spliter_token = strtok (inp_sentences , DELIM); spliter_token != NULL; spliter_token = strtok(NULL, DELIM))
	{
		while (inp_sentences !=NULL) // while there is more string 
		{
			//printf("%s\n", spliter_token); //print what we got 
			spliter_token = strtok (NULL , DELIM); //keep splitting
		}
	}
	
	fclose(file2);
}*/

//main contains the main application code (calling functions, menu , free memory)
int main (int argc , char **argv)
{	
	//where my input is saved so it can be used in my mian method
	char **input;
	//holds the number of the counter (number of lines) transfered from read_single_words function
	int inp_line_counter;
	//calling function read_single_words (what i transfered out of the function)
	read_single_words (&input , &inp_line_counter); 
	
	//where my dictionary is saved so it can be used in my main method
	char **dictionary;
	//holds the number of the counter (number of lines) transfered from read_single_words function
	int dic_line_counter;
	//calling function read_dictionary (what i transfered out of the function)
	read_dictionary (&dictionary , &dic_line_counter); 
	
	//calls function binary search
	binary_search(input , dic_line_counter , inp_line_counter , dictionary);
	
	//should call function to read sentences but its not working 
	//read sentences ();
	
	/* loop to run the binary search x times for the number of lines of input
	for (int x = 0; x<inp_line_counter -1; x++)
	{
		if (input[x] !=NULL)
		{
			printf("Looking at %d\n", input[x]);
			
		}
		return 0;
	}*/
	
	/*tests
	printf ("Input %s" , input[1]);
	printf ("Dictionary %s" , dictionary[1]);
	printf ("Lines in dictionary: %d \n" , dic_line_counter);
	printf ("Lines in input: %d\n" , inp_line_counter);
	*/
	
	//free memory allocated 
	free (input);
	free (dictionary);
}