/*
Coding Project 1 for ENGG1003
Written by Max Spencer Karinen - c3264546 - spencerkarinen@gmail.com
Performs a variety of encryption and decryption algorithms
Last Updated 10/04/2019
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LIBRARIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> //standard library for input and output
#include <stdlib.h> //a bunch of useful functions, put in more out of habit than anything else
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


Last Updated 10/04/2019
*/
int main()
{
	char subEncryptArray[100];
	char subDecryptArray[100];
	FILE *cipherKeyRead; //file IO pointer to read cipher keys
	FILE *cipherKeyWrite; //file IO pointer to write cipher keys
	FILE *userText; //file IO pointer for reading files from the user
	FILE *decrypted; //file IO pointer to write decrypted messages
	decrypted = fopen("decrypted.txt", "w");
	FILE *encrypted; //file IO pointer to write encrypted messages
	encrypted = fopen("encrypted.txt", "w");
	int fileSize;
	char subKey[27]; //an array that will be used to hold a substitution key later
	char fileName[256]; //array to hold file names
	int rotKey; //int to hold a user - inputted rotation key
	int count = 0; //counter, reused many times
	int bigChoice;

	int choice = 0; //integer to store the user's choice
	int inputMethod = 0; //integer to store the input method the user wants to use
	while(choice != 7) //this loop will continue until the user enters 7 - not really required as 7 should exit the program anyways
	{
		printf("\nPlease select what you want to do:\n"); //essentially a menu
		printf("1: Encryption with a rotation cipher\n\n");
		printf("2: Decryption of a rotation cipher, you supply the key\n\n");
		printf("3: Encryption with a substitution cipher, you supply the key\n\n");
		printf("4: Decryption of a substitution cipher, you supply the key\n\n");
		printf("5: Decryption of a rotation cipher, we figure out the key\n\n");
		printf("6: Decryption of a substitution cipher, we figure out the key\n\n");
		printf("7: Exit program\n\n");
		scanf("%d", &choice); //wait for the user to input their choice
		while(choice < 1 || choice > 7) //checks if the input is valid
		{
			printf("\nInvalid input, please try again\n");
			printf("\nPlease select what you want to do:\n"); //essentially a menu
			printf("1: Encryption with a rotation cipher\n\n");
			printf("2: Decryption of a rotation cipher, you supply the key\n\n");
			printf("3: Encryption with a substitution cipher, you supply the key\n\n");
			printf("4: Decryption of a substitution cipher, you supply the key\n\n");
			printf("5: Decryption of a rotation cipher, we figure out the key\n\n");
			printf("6: Decryption of a substitution cipher, we figure out the key\n\n");
			printf("7: Exit program\n\n");
			scanf("%d", &choice); //wait for the user to input their choice
		}
		if(choice != 7)
		{
			printf("\nWould you like to enter text \n1: from a file or \n2: through manual input?\n\n");//####TODO sanitize input
			scanf("%d", &inputMethod);
			while(inputMethod < 1 || inputMethod > 2)
			{
				printf("\nInvalid input, please try again\n");
				printf("\nWould you like to enter text \n1: from a file or \n2: through manual input?\n\n");//####TODO sanitize input
				scanf("%d", &inputMethod);
			}
		}
		//consolidates the two choices from the user into one integer, first digit is what they want to do and second digit is the input method they want to use
		bigChoice = ((choice * 10) + inputMethod);
		switch(bigChoice)
		{
			case 70:

			case 71: //70, 71 and 72 are if they want to exit the program

			case 72:

				exit(0); //exits the program
				break;

			case 11: //rotation cipher encryption from file
				printf("\n11\n");
				printf("What is the name of the file you wish to encrypt? Include the filetype (eg .txt) at the end\n\n");
				scanf("%s", fileName);

				printf("%s will be encrypted to the file encrypted.txt\n\n");

				userText = fopen(fileName, "r");
				printf("What is the rotation key for encrypting this file?\n\n");
				scanf("%d", rotKey);

				//find size of file to use in array
				fseek(userText, 0, SEEK_END);
				fileSize = ftell(userText);
				fseek(userText, 0, SEEK_SET);
				fgets(subEncryptArray, fileSize + 1, userText);
				rotationEncrypt(subEncryptArray, fileSize, rotKey);
				fprintf(encrypted, "%s", subEncryptArray);
				printf("The encrypted string is %s\n\n successfully written to encrypted.txt\n\n", subEncryptArray, fileName);
				break;
			
			case 12: //rotation cipher encryption from console input
				printf("\n12");
				break;
			
			case 21: //rotation cipher decryption from file input
				printf("\n21");
				printf("\n11\n");
				printf("What is the name of the file you wish to decrypt? Include the filetype (eg .txt) at the end\n\n");
				scanf("%s", fileName);

				printf("%s will be decrypted to the file decrypted.txt\n\n");

				userText = fopen(fileName, "r");
				printf("What is the rotation key to decrypt this file?\n\n");
				scanf("%d", rotKey);

				//find size of file to use in array
				fseek(userText, 0, SEEK_END);
				fileSize = ftell(userText);
				fseek(userText, 0, SEEK_SET);
				fgets(subDecryptArray, fileSize + 1, userText);
				printf("%d\n", fileSize);
				rotationDecryptKey(subDecryptArray, fileSize, rotKey);
				fprintf(decrypted, "%s", subDecryptArray);
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", subDecryptArray, fileName);
				break;
			
			case 22: //rotation cipher decryption from console input
				printf("\n22");
				break;
			
			case 31: //substitution cipher encryption from file
				printf("\n31");
				break;
			
			case 32: //substitution cipher encryption from console input
				printf("\n32");
				break;
			
			case 41: //substitution cipher decryption from file
				printf("\n41");
				break;
			
			case 42: //substitution cipher decryption from console input
				printf("\n42");
				break;
			
			case 51: //rotation cipher decryption without a key, from file 
				printf("\n51");
				break;
			
			case 52: //rotation cipher decryption without a key, from console input 
				printf("\n52");
				break;
			
			case 61: //substitution cipher decryption with a key, from file
				printf("\n61");
				break;
			
			case 62: //substitution cipher decryption with a key, from console input
				printf("\n62");
				break;
			
			default:
				printf("\nYou should not be here\n");
				break;
		}
	}
/*
//hard code an array of letters to test ciphers
	int k = 22; //rotation cipher amount
	char test[] = "SJSFMPCRM WG O USBWIG. PIH WT MCI XIRUS O TWGV PM WHG OPWZWHM HC QZWAP O HFSS, WH KWZZ ZWJS WHG KVCZS ZWTS PSZWSJWBU HVOH WH WG GHIDWR. - OZPSFH SWBGHSWB";
	char subsKey[] = "#QWERTYUIOPASDFGHJKLZXCVBNM";
	int testLength = strlen(test);
	rotationDecryptNoKeyStatistical(test, testLength);
	printf("%s\n", test);
	/*subEncrypt(test, testLength, subKey);
	printf("substitution cipher encrypt: %s\n\n", test);
	subDecrypt(test, testLength, subKey);
	printf("substitution cipher decrypt: %s\n\n", test);
	*/


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
	//rotate the values of x using the key k
	for (int i = 0; i < n; i++)
	{
		//the following if statement determines if x[i] is a lowercase or capital letter based off the the ASCII value - if it is neither, the value is not changed
		if(x[i] >= 65 && x[i] <= 90) //if the value of x at position i is a capital letter
		{
			x[i] = 65 + (((x[i] - 65) + k) % 26); //converts x to a number between 1 and 26, adds k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
		}
		else if(x[i] >= 97 && x[i] <= 122) //if the value of x at position i is a lower case letter
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
	//rotate the values of x using the key k
	for (int i = 0; i < n; i++)
	{
		//the following if statement determines if x[i] is a lowercase or capital letter based off the the ASCII value - if it is neither, the value is not changed
		if(x[i] >= 65 && x[i] <= 90) //if the value of x at position i is a capital letter
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
		else if(x[i] >= 97 && x[i] <= 122) //if the value of x at position i is a lower case leter
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
	char temp[n]; //array to hold copies of x to test possible keys
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
	char temp[n]; //create a temporary array to store the values of the array x, so that x can be decrypted later
	//initialise all the values of temp to the values of x
	for(int i = 0; i < n; i++)
	{
		temp[i] = x[i];
	}
	int k; //integer to hold value of key
	int largestPos; //integer to hold position of most common letter
	int tally[26]; //array to hold copies of x to test possible keys
	for(int i = 0; i < 26; i++)
	{
		tally[i] = 0;
	}

	//the following for loop cycles through each position in the array x,
	for (int i = 0; i < n; i++)
	{
		//convert the ASCII value of each character to a number (a = 1, b = 2 etc) then tallies each letter
		if(temp[i] >= 65 && temp[i] <= 90) //if the value of x at position i is a capital letter
		{
			temp[i] -= 65; //converts x to a number between 0 and 25
		}
		else if(temp[i] >= 97 && temp[i] <= 122) //if the value of x at position i is a lower case leter
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

The substitution key should be formatted such that k is an array of 27 characters, starting with a #, the position corresponding to the letter that each
element in x should be replaced with eg if the fourth element (position 4, k[3]) of k is e, then every c (3rd letter) should be replaced by e

assumes the substition key is all upper case 
Tsk 3

Last Updated 10/04/2019
*/
void subEncrypt(char *x, int n, char *k)
{
	//convert letters of x to values from 0 to 25, then substitutes
	//if block does capital letters, else if does lower case  oher ASCII characters are unchanged
	for(int i = 0; i < n; i++)
	{
		if(x[i] >= 65 && x[i] <= 90) //if the value of x at position i is a capital letter
		{
			x[i] -= 64;	
			x[i] = k[x[i]]; //sets the value to the substitution value
		}
		else if(x[i] >= 97 && x[i] <= 122) //if the value of x at position i is a lower case leter
		{
			x[i] -= 96;
			x[i] = (k[x[i]] + 32); //sets the value to the substitution value, correcting for all elements of k being uppercase
		} 		

	}

}


/*
A function that takes an array of characters from a pointer 'x' of size 'n' and decrypts it using a substitution cipher, with key 'k'

The substitution key should be formatted such that k is an array of 27 characters, starting with a #, the position corresponding to the letter that each element in x should be replaced with
eg if the third element of k is e, then every b (2nd letter) should be replaced by e

assumes the substition key is all upper case 
Tsk 4

Last Updated 10/04/2019
*/

void subDecrypt(char *x, int n, char *k)
{
	int position = 1; //variable to hold values ouside of for loops
	for(int i = 0; i < n; i++) //go through every element of the array x
	{
		position = 0; //by default the position is 1, so if the loop checking for a character fails on the first try the position is already 1
		if(x[i] >= 65 && x[i] <= 90) //if the value of x at position i is a capital letter
		{
			for(char j = 1; x[i] != k[j]; j++) //go through the characters in the substitution cipher until you find the one that matches the character in x
			{
				position = j; //store the index in 'position'
			}
			x[i] = position + 65; //sets the value to the letter corresponding to the substitution value
		}
		else if(x[i] >= 97 && x[i] <= 122) //if the value of x at position i is a lower case leter
		{
			x[i] -= 32; //convert lower case leters to uppercase 
			for(char j = 1; x[i] != k[j]; j++)//go through the characters in the substitution cipher until you find the one that matches the character in x
			{
				position = j;//store the index in 'position'
			}
			x[i] = position + 97; //sets the value to the letter corresponding to the substitution value, correcting for all elements of k being uppercase 
		}

	}
}


/*
	template for a temp array

	char temp[n]; //create a temporary array to store the values of the array x
	//initialise all the values of temp to the values of x
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