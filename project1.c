/*
Coding Project 1 for ENGG1003
Written by Max Spencer Karinen - c3264546 - spencerkarinen@gmail.com
Performs a variety of encryption and decryption algorithms
Last Updated 03/04/2019
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LIBRARIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> //standard library for input and output
#include <stdlib.h>
#include <math.h> //standard library for a variety of mathematical functions
#include <string.h> //standard library for a variety of string functions


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTION DECLARATIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//a function to encrypt an array given a rotation amount
void rotationEncrypt(char *x, int n, int k);

//a function to decrypt an array given a rotation amount
void rotationDecryptKey(char *x, int n, int k);

//a function to decrypt an array without knowing the rotation amount, spell checks to find legible words
//returns key value
int rotationDecryptNoKeyCheck(char *x, int n);

//a function to decrypt an array without knowing the rotation amount, assumes most common letter is e
//returns key value
int rotationDecryptNoKeyStatistical(char *x, int n);

//a function to encrypt an array with a given substitution cipher
void subEncrypt(char *x, int n, char *k);

//a function to decrypt an array with a given substitution cipher
void subDecrypt(char *x, int n, char *k);


//a function to find the largest element of an array
int findLargest(int *x, int n);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
Main function, essentially contains an interface for the various encryption and decryption algorithms used in the project


Last Updated 03/04/2019
*/
int main()
{
	//hard code an array of letters to test ciphers
	int k = 22; //rotation cipher amount
	char test[] = "Fourscore and seven years ago our fathers brought forth, on this continent, a new nation, conceived in liberty, and dedicated to the proposition that all men are created equal. Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived, and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting-place for those who here gave their lives, that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we cannot dedicate, we cannot consecrate—we cannot hallow—this ground. The brave men, living and dead, who struggled here, have consecrated it far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us—that from these honored dead we take increased devotion to that cause for which they here gave the last full measure of devotion—that we here highly resolve that these dead shall not have died in vain—that this nation, under God, shall have a new birth of freedom, and that government of the people, by the people, for the people, shall not perish from the earth.";
	char subKey[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	int testLength = strlen(test);
	subEncrypt(test, testLength, subKey);
	printf("substitution cipher encrypt: %s\n\n", test);
	subDecrypt(test, testLength, subKey);
	printf("substitution cipher decrypt: %s\n\n", test);



	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ENCRYPTION/DECRYPTION FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
A function that takes an array of characters from a pointer 'x' of size 'n' and encrypts it using a rotation cipher, with key 'k'

Task 1

Last Updated 03/04/2019
*/
void rotationEncrypt(char *x, int n, int k)
{
	//the following two lines sanitize the input of k - make it positive, and between 1 and 26
	k = abs(k);
	k = (k % 26);
	// rotate the values of x using the key k
	for (int i = 0; i < n; i++)
	{
		//the following if statement determines if x[i] is a lowercase or capital letter based off the the ASCII value - if it is neither, the value is not changed
		if(x[i] >= 65 && x[i] <= 90) // if the value of x at position i is a capital letter
		{
			x[i] = 65 + (((x[i] - 65) + k) % 26); //converts x to a number between 1 and 26, adds k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
		}
		else if(x[i] >= 97 && x[i] <= 122) // if the value of x at position i is a lower case letter
		{
			x[i] = 97 + (((x[i] - 97) + k) % 26);//converts x to a number between 1 and 26, adds k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
		}
	}
}



/*
A function that takes an array of characters from a pointer 'x' of size 'n' and decrypts it using a rotation cipher, with key 'k'
This function is very similar to rotationEncrypt(), except it takes away a value of k

Task 2

Last Updated 03/04/2019
*/
void rotationDecryptKey(char *x, int n, int k)
{
	//the following two lines sanitize the input of k - make it positive, and between 1 and 26
	k = abs(k);
	k = (k % 26);
	// rotate the values of x using the key k
	for (int i = 0; i < n; i++)
	{
		//the following if statement determines if x[i] is a lowercase or capital letter based off the the ASCII value - if it is neither, the value is not changed
		if(x[i] >= 65 && x[i] <= 90) // if the value of x at position i is a capital letter
		{
			x[i] = x[i] - 65 - k; //converts x to a number between 1 and 26, adds k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
			if(x[i] < 0)
			{
				x[i] = 26 + x[i];
				x[i] = 65 + ((x[i]) % 26);

			}
			else
			{
				x[i] = 65 + ((x[i]) % 26);
			}
		}
		else if(x[i] >= 97 && x[i] <= 122) // if the value of x at position i is a lower case letter
		{
			x[i] = x[i] - 97 - k; //converts x to a number between 1 and 26, adds k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
			if(x[i] < 0)
			{
				x[i] = 26 + x[i];
				x[i] = 97 + ((x[i]) % 26);

			}
			else
			{
				x[i] = 97 + ((x[i]) % 26);
			}
		}
	}
}


/*
A function that brute forces a solution for a rotation cipher, by trying all possible combinations and checking each combination for known words

Returns an integer that is assumed to be the key



########################################### IMPORTANT complete when file io is done, implement common word checker

Task 5

Last Updated 03/04/2019
*/
int rotationDecryptNoKeyCheck(char *x, int n)
{
	int k = 0;
	char temp[n]; // array to hold copies of x to test possible keys
	//the following for loop cycles through each possible key, ie 'i' is the cipher key
	for(int i; i < 26; i++)
	{
		for(int j = 0; j < n; j++)
		{
			
		}
	}



	return k;
}


/*
A function that assumes the most common character to be e, then determines the key from that assumption

Returns an integer that is assumed to be the key

Decrypts the array given the calculated key

Task 5

Last Updated 03/04/2019
*/
int rotationDecryptNoKeyStatistical(char *x, int n)
{
	char temp[n]; // create a temporary array to store the values of the array x, so that x can be decrypted later
	// initialise all the values of temp to the values of x
	for(int i = 0; i < n; i++)
	{
		temp[i] = x[i];
	}
	int k; //integer to hold value of key
	int largestPos; //integer to hold position of most common letter
	int tally[26]; // array to hold copies of x to test possible keys
	for(int i = 0; i < 26; i++)
	{
		tally[i] = 0;
	}

	//the following for loop cycles through each position in the array x,
	for (int i = 0; i < n; i++)
	{
		//convert the ASCII value of each character to a number (a = 1, b = 2 etc) then tallies each letter
		if(temp[i] >= 65 && temp[i] <= 90) // if the value of x at position i is a capital letter
		{
			temp[i] -= 65; //converts x to a number between 0 and 25
		}
		else if(temp[i] >= 97 && temp[i] <= 122) // if the value of x at position i is a lower case letter
		{
			temp[i] -= 97; //converts x to a number between 0 and 25
		}

		tally[temp[i]]++;
	}
	largestPos = findLargest(tally, 26);
	//the rotation cipher is centred around e, the 5th letter, so the 
	if(largestPos < 4)
	{
		k = 22 + largestPos;
	}
	else
	{
		k = largestPos - 4;
	}
	/*for(int i = 0; i < 26; i++)
	{
		printf("%c %d\n", tally[i] + 97, tally[i]);
		//printf("%d\n", tally[i]);
	}*/

	rotationDecryptKey(x, n, k); //decrypt 


	k += 1; //converts the array-friendly k value to one that corresponds to a cipher key, then returns it
	return k; 
}



/*
A function that takes an array of characters from a pointer 'x' of size 'n' and encrypts it using a substitution cipher, with key 'k'

The substitution key should be formatted such that k is an array of 26 characters, the position corresponding to the letter that each element in x should be replaced with
eg if the third element of k is e, then every c (3rd letter) should be replaced by e

assumes the substition key is all upper case

Task 3

Last Updated 03/04/2019
*/
void subEncrypt(char *x, int n, char *k)
{
	//convert letters of x to values from 0 to 25, then substitutes
	//if block does capital letters, else if does lower case, other ASCII characters are unchanged
	for(int i = 0; i < n; i++)
	{
		if(x[i] >= 65 && x[i] <= 90) // if the value of x at position i is a capital letter
		{
			x[i] -= 65;
			x[i] = k[x[i]]; //sets the value to the substitution value
		}
		else if(x[i] >= 97 && x[i] <= 122) // if the value of x at position i is a lower case letter
		{
			x[i] -= 97;
			x[i] = k[x[i]] + 32; //sets the value to the substitution value, correcting for all elements of k being uppercase
		}

	}

}


/*
A function that takes an array of characters from a pointer 'x' of size 'n' and decrypts it using a substitution cipher, with key 'k'

The substitution key should be formatted such that k is an array of 26 characters, the position corresponding to the letter that each element in x should be replaced with
eg if the third element of k is e, then every c (3rd letter) should be replaced by e

assumes the substition key is all upper case

Task 4

Last Updated 03/04/2019
*/

void subDecrypt(char *x, int n, char *k)
{
	char position = 0; // variable to hold values ouside of for loops
	for(int i = 0; i < n; i++) // go through every element of the array x
	{
		if(x[i] >= 65 && x[i] <= 90) // if the value of x at position i is a capital letter
		{
			for(char j = 0; x[i] != k[j]; j++) // go through the characters in the substitution cypher until you find the one that matches the character in x
			{
				position = j; //store the index in 'position'
			}
			x[i] = position + 66; //sets the value to the letter corresponding to the substitution value
		}
		else if(x[i] >= 97 && x[i] <= 122) // if the value of x at position i is a lower case letter
		{
			x[i] -= 32; // convert lower case letters to uppercase
			for(char j = 0; x[i] != k[j]; j++)// go through the characters in the substitution cypher until you find the one that matches the character in x
			{
				position = j;//store the index in 'position'
				if(position == 0)
				{
					printf("%d %d  ", k[j], position);
				}
			}
			x[i] = position + 98; //sets the value to the letter corresponding to the substitution value, correcting for all elements of k being uppercase
		}

	}
}


/*
	template for a temp array

	char temp[n]; // create a temporary array to store the values of the array x
	// initialise all the values of temp to the values of x
	for(int i = 0; i < n; i++)
	{
		temp[i] = x[i];
	}
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GENERAL FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Basic function to find the position of the largest element of an array

Last Updated 03/04/2019
*/
int findLargest(int *x, int n)
{
	int largestPos = 0;
	for(int i = 0; i < n; i++)
	{
		if(x[i] > x[largestPos])
		{
			largestPos = i;
		}
	}
	return largestPos;
}