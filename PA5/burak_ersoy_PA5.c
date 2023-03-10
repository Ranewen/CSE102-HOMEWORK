#include <stdio.h>	/* Defines fopen, fclose, fscanf, fprintf and EOF */
#define NUM_OF_LETTERS 27	/* 'a' 'b' 'c' 'd' 'e' 'f' 'g' 'h' 'i' 'j' 'k' 'l' 'm' 'n' 'o' 'p' 'q' 'r' 's' 't' 'u' 'v' 'w' 'x' 'y' 'z' ' ' */

/* Global arrays of language files */
int language_1[NUM_OF_LETTERS][NUM_OF_LETTERS],
	language_2[NUM_OF_LETTERS][NUM_OF_LETTERS],
	language_3[NUM_OF_LETTERS][NUM_OF_LETTERS],
	language_4[NUM_OF_LETTERS][NUM_OF_LETTERS],
	language_5[NUM_OF_LETTERS][NUM_OF_LETTERS],
	language_x[NUM_OF_LETTERS][NUM_OF_LETTERS];

/* This function assigns 0 to array elements */
void fill_to_zero (int lang[][NUM_OF_LETTERS])
{
	int i, j; /* For loops variables */
	
    for (i=0; i<NUM_OF_LETTERS; i++)
    {
    	for(j=0; j<NUM_OF_LETTERS; j++)
    	{
    		lang[i][j] = 0;
		}
    }
}

/* This function reads file and finds all bi-grams in the file.*/
int find_bigram (char * file_lang, int lang[][NUM_OF_LETTERS] )
{	
	FILE *inp = fopen(file_lang, "r"); /* Access to file.txt is provided for reading. */
	
	fill_to_zero(lang);  /* Zero is assingned to lang array */
	int ch1, ch2; 	/* Variables that hold the ascii value of characters */
	
	/* File Check operation */
	if(inp == NULL) 
	{
		printf("File not found");
		return -1;
	}
	
	ch1=fgetc(inp); /* Getting first character of the file. */
	
	if (ch1<97 || ch1>122) /* If the first character is a whitespace, then 123 assign to ch1 */
	{
		ch1=123;
	}
	
	while(1) /* This loop reads each character until the end of the file and read the bi-grams. */
	{
		ch2=fgetc(inp); /* Getting other characters of the file. */
		
		if(feof(inp))  /* When the end of the file is reached, if the last character is not a space, it increases the number of bi grams. */
		{
			if( ch1!=123 )
				lang[ch1-97][26]++; /* Count the bi-gram */
			break;
		}
		if (ch2<97 || ch2>122) /* If character is whitespace then 123 assign to ch2. */
		{
			ch2=123;
		}
		if (ch1==123 && ch2==123) /* Double space characters do not create a bigram */
		{
			continue;
		}
		lang[ch1-97][ch2-97]++; /* Count the bi-gram */

		ch1=ch2;	/* Assign ch2 to ch1. */
	}

	fclose(inp); /* Closing the file. */
	return 0;
}

/* This function calculate total number of all bi-grams in language file. */
double calculate_total_bigram (int lang_bigram[][NUM_OF_LETTERS])
{
	int i, j;  /* For loop variables */
	double sum_bigram = 0.0; /* Total number of all bi-grams */
	
	for (i=0; i<NUM_OF_LETTERS; i++)
	{
		for (j=0; j<NUM_OF_LETTERS; j++)
		{
			sum_bigram += lang_bigram[i][j]; 
		}
	}
	return sum_bigram; /* Return total bi-grams */ 
}

/* This function calculates the frequency of a particular bigram and then prints the dissimilarity value. */
void dissimilarity (int lang_x[][NUM_OF_LETTERS], int lang_other[][NUM_OF_LETTERS])
{
	int i, j; /* For loops variables */
	double dissimilarity_score = 0.0, 	/* Dissimilarity value variable */
		   frequency_bigram,			/* Frequency of bi-gram for the language */
		   totalbigram_x,				/* Total number of all bi-gram in a language_x file */
		   totalbigram_other;			/* Total number of all bi-gram in a language_x file */
	
	totalbigram_x = calculate_total_bigram(lang_x);
	totalbigram_other = calculate_total_bigram(lang_other);
	
	for (i=0; i<NUM_OF_LETTERS; i++)  /* This loop calculates the frequency differences and finds the dissimilarity value. */
	{
		for (j=0; j<NUM_OF_LETTERS; j++)
		{
			frequency_bigram = (lang_x[i][j] / totalbigram_x)  - (lang_other[i][j] / totalbigram_other);  /* Calculating the frequency difference of a particular bi-gram.*/
			
			if (frequency_bigram > 0)
			{
				dissimilarity_score += frequency_bigram; 
			}
			else
			{
				dissimilarity_score -= frequency_bigram; /* Dissimilarity must be positive. */
			}
		}
	}
	printf("%lf\n", dissimilarity_score);
}

int main()
{
	/* Reading files and finds all bi-grams in the files.*/
	find_bigram("language_1.txt", language_1);
	find_bigram("language_2.txt", language_2);
	find_bigram("language_3.txt", language_3);
	find_bigram("language_4.txt", language_4);
	find_bigram("language_5.txt", language_5);
	find_bigram("language_x.txt", language_x);
	
	/* Calculate the dissimilarity of language x and language 1, 2, 3, 4 and 5. */ 
	dissimilarity(language_x, language_1);			
	dissimilarity(language_x, language_2);			
	dissimilarity(language_x, language_3);			
	dissimilarity(language_x, language_4);		
	dissimilarity(language_x, language_5);			

	return 0;
}
