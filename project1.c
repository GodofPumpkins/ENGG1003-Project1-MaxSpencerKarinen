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
void rotationDecryptNoKeyCheck(char *x, int n);

//a function to decrypt an array without knowing the rotation amount, assumes most common letter is e
int rotationDecryptNoKeyStatistical(char *x, int n)


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
Main function, essentially contains an interface for the various encryption and decryption algorithms used in the project


Last Updated 03/04/2019
*/
int main()
{
	//hard code an array of letters to test cyphers
	int k = 97; //rotation cypher amount
	char test[] = "Hello world, this is a test to see if you can break the code";
	int testLength = strlen(test);
	rotationEncrypt(test, testLength, k);
	printf("%d rotation cypher encrypt: %s\n", k, test);
	rotationDecryptNoKey(test, testLength, k);
	printf("%d rotation cypher decrypt: %s\n", k, test);



	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
A function that takes an array of characters from a pointer 'x' of size 'n' and encrypts it using a rotation cypher, with key 'k'

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
A function that takes an array of characters from a pointer 'x' of size 'n' and decrypts it using a rotation cypher, with key 'k'
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
A function that brute forces a solution for a rotation cypher, by trying all possible combinations and checking each combination for known words

Returns an integer that is assumed to be the key

Task 5

Last Updated 03/04/2019
*/
int rotationDecryptNoKeyCheck(char *x, int n)
{
	int k = 0;
	char temp[n]; // array to hold copies of x to test possible keys
	//the following for loop cycles through each possible key, ie 'i' is the cypher key
	for(int i; i < 26, i++)
	{
		for (int i = 0; i < n; i++)
		{
			
		}
	}

	return k;
}


/*
A function that assumes the most common character to be e, then determines the key from that assumption

Returns an integer that is assumed to be the key

Task 5

Last Updated 03/04/2019
*/
int rotationDecryptNoKeyStatistical(char *x, int n)
{
	char temp[26]; // array to hold copies of x to test possible keys
	//the following for loop cycles through each possible key, ie 'i' is the cypher key
	for (int i = 0; i < n; i++)
	{
		//convert the ASCII value of each character to a number (a = 1, b = 2 etc) then tallies each letter
		if(x[i] >= 65 && x[i] <= 90) // if the value of x at position i is a capital letter
		{
			x[i] -= 65; //converts x to a number between 1 and 26
		}
		else if(x[i] >= 97 && x[i] <= 122) // if the value of x at position i is a lower case letter
		{
			x[i] -= 97;//converts x to a number between 1 and 26
		}
	}

	return k;
}



/*
A function that takes an array of characters from a pointer 'x' of size 'n' and encrypts it using a substitution cypher, with key 'k'

Task 3

Last Updated 03/04/2019
*/
void substitutionEncrypt(char *x, int n, char *k)
{

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
