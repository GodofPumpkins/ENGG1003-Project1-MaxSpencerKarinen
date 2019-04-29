/*
Coding Project 1 for UON ENGG1003
Written by Max Spencer Karinen - c3264546 - spencerkarinen@gmail.com - c3264546@uon.edu.au
Performs a variety of encryption and decryption algorithms, from both console and file IO
Last Updated 29/04/2019
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LIBRARIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> //standard library for input and output
#include <stdlib.h> //a bunch of useful functions, put in more out of habit than anything else
#include <math.h> //standard library for a variety of mathematical functions
#include <string.h> //standard library for a variety of string functions
#include <ctype.h> //library with character parsing functions


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FUNCTION DECLARATIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//a function to encrypt an array given a rotation amount
void rotationEncrypt(char *x, int n, int k);

//a function to decrypt an array given a rotation amount
void rotationDecryptKey(char *x, int n, int k);

//a function to decrypt an array without knowing the rotation amount, spell checks to find legible words
//returns key value
int rotationDecryptForce(char *x, int n);

//a function to decrypt an array without knowing the rotation amount, assumes most common letter is e
//returns key value
int rotationDecryptNoKey(char *x, int n);

//a function to encrypt an array with a given substitution cipher
void subEncrypt(char *x, int n, char *k);

//a function to decrypt an array with a given substitution cipher
void subDecrypt(char *x, int n, char *k);

//a function to find the largest element of an array
int findLargest(int *x, int n);

//a function to check if a file exists
int fileExists(char *filename);

//a function that checks how many words in a file are in the dictionary
int spellCheck(char *x, int n);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
Main function, essentially contains an interface for the various encryption and decryption algorithms used in the project


Last Updated 29/04/2019
*/
int main()
{
	//arrays to hold text
	char encryptArray[10000]; //Array to hold text that is then encrypted, size is hard coded but can be changed //TODO make array size user defined?
	char decryptArray[10000]; //Same as above but to hold decrypted text
	
	//file pointers that will be specified by the user
	FILE *cipherKeyRead; //file IO pointer to read cipher keys
	FILE *cipherKeyWrite; //file IO pointer to write cipher keys
	FILE *userText; //file IO pointer for reading files from the user
	FILE *keyFile; //file IO pointer for reading substitution keys
	
	//file pointers for writing encrypted/decrypted text
	FILE *decrypted; //file IO pointer to write decrypted messages
	decrypted = fopen("decrypted.txt", "w"); //the file 'decrypted.txt' is used to store decrypted text
	
	FILE *encrypted; //file IO pointer to write encrypted messages
	encrypted = fopen("encrypted.txt", "w"); //the file 'encrypted.txt' is used to store encrypted text
	
	//variables/arrays used later in the program
	int fileSize; //int used when the program has to find the size of a file given by the user
	
	char subKey[27]; //an array that will be used to hold a substitution key later
	char fileName[256]; //array to hold file names - size is set to 256, could be probably be lower
	char subKeyFile[256]; //array to hold the name of the file containing a substitution cipher key
	
	int rotKey = 0; //int to hold a user-inputted rotation key
	int count = 0; //counter, reused many times

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
		if(choice != 7)//skips the second choice if the user wants to exit the program
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
		
		switch((choice * 10) + inputMethod)
		{
			case 70:

			case 71: //70, 71 and 72 are if they want to exit the program

			case 72:

				exit(0); //exits the program
				break;

			case 11: //rotation cipher encryption from file
				printf("What is the name of the file you wish to encrypt? Include the filetype (eg .txt) at the end, and place the file in the same directory as this code\n\n");
				scanf("%s", fileName); //scan for file name

				while(fileExists(fileName) == 0) //check if the file exists, and if it doesn't, continually asks for a new file name
				{
					printf("File does not exist, try again\n");
					scanf("%s", fileName); //scan for file name again
				}

				userText = fopen(fileName, "r");
				printf("What is the rotation key for encrypting this file?\n\n");
				scanf("%d", &rotKey);

				//find size of file to use in array
				fseek(userText, 0, SEEK_END); //seek to the end of the array
				fileSize = ftell(userText); //set file size to the position of the IO stream at the end of the file, ie the size of the file
				fseek(userText, 0, SEEK_SET); //seek back to the start of the file

				fgets(encryptArray, fileSize + 1, (FILE*)userText); //read the file into an array
				rotationEncrypt(encryptArray, fileSize, rotKey); //encrypt the array
				fprintf(encrypted, "%s", encryptArray); //print the encrypted array to the file encrypted.txt
				printf("The encrypted string is %s\n\n successfully written to encrypted.txt\n\n", encryptArray); //print the encrypted array to console
				fclose(userText); //close the file stream from the user in case they try to read the same file again
				break;
			
			case 12: //rotation cipher encryption from console input
			//TODO fix reading whitespace from console with strlen() implementation
				printf("\nPlease enter the encryption key\n\n");
				scanf("%d", &rotKey);

				printf("\nPlease enter the text to be encrypted\n\n");
				scanf("%s", encryptArray); //save to an array the text from the console

				rotationEncrypt(encryptArray, strlen(encryptArray), rotKey); //encrypt the array
				fprintf(encrypted, "%s", encryptArray); //print to a file the encrypted array
				printf("The encrypted string is %s\n\n successfully written to encrypted.txt\n\n", encryptArray);
				break;
			
			case 21: //rotation cipher decryption from file input
			//FINISHED
				printf("What is the name of the file you wish to decrypt? Include the filetype (eg .txt) at the end\n\n");
				scanf("%s", fileName); //scan for file name

				while(fileExists(fileName) == 0) //check if the file exists, and if it doesn't, continually asks for a new file name
				{
					printf("File does not exist, try again\n");
					scanf("%s", fileName); //scan for file name again
				}

				printf("%s will be decrypted to the file decrypted.txt\n\n");

				userText = fopen(fileName, "r"); //open the file stream to the user's file
				printf("What is the rotation key to decrypt this file?\n\n");
				scanf("%d", &rotKey);

				//find size of file to use in array
				fseek(userText, 0, SEEK_END);
				fileSize = ftell(userText);
				fseek(userText, 0, SEEK_SET);

				fgets(decryptArray, fileSize + 1, userText); //read the file to an array
				rotationDecryptKey(decryptArray, fileSize, rotKey); //decrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the array to the file
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray);
				fclose(userText); //close the file stream from the user in case they try to read the same file again
				break;
			
			case 22: //rotation cipher decryption from console input
			//TODO fix reading whitespace from console with strlen() implementation
			//FINISHED
				printf("Please enter the text to be decrypted\n\n");
				scanf("%s", decryptArray); //scan for file name

				printf("What is the rotation key to decrypt this file?\n\n");
				scanf("%d", &rotKey);

				rotationDecryptKey(decryptArray, strlen(decryptArray), rotKey); //decrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the array to the file
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray);
				break;
			
			case 31: //substitution cipher encryption from file
				printf("What is the name of the file you wish to encrypt? Include the filetype (eg .txt) at the end, and place the file in the same directory as this code\n\n");
				scanf("%s", fileName); //scan for file name

				while(fileExists(fileName) == 0) //check if the file exists, and if it doesn't, continually asks for a new file name
				{
					printf("File does not exist, try again\n");
					scanf("%s", fileName); //scan for file name again
				}

				userText = fopen(fileName, "r");
				printf("What is the name of the file with the substitution key for encrypting this file?\n\nIt should be formatted like \n#QWERTYUIOPASDFGHJKLZXCVBNM\nwhere the position of each letter tells you which letter is being replaced, with a # at the start.\nAn example key is included, called key.txt\n\n");
				scanf("%s", subKeyFile);

				keyFile = fopen(subKeyFile, "r"); //open the file stream to the key file
				fgets(subKey, 27, (FILE*)keyFile); //copy the file to the array with the key
				fclose(keyFile); //close the file

				//find size of file to use in array
				fseek(userText, 0, SEEK_END); //seek to the end of the array
				fileSize = ftell(userText); //set file size to the position of the end of the file, ie the size of the file
				fseek(userText, 0, SEEK_SET); //seek back to the start of the file

				fgets(encryptArray, fileSize + 1, (FILE*)userText); //read the file into an array
				subEncrypt(encryptArray, fileSize, subKey); //encrypt the array
				fprintf(encrypted, "%s", encryptArray); //print the encrypted array to the file encrypted.txt
				printf("The encrypted string is %s\n\n successfully written to encrypted.txt\n\n", encryptArray); //print the encrypted array to console
				fclose(userText); //close the file stream from the user in case they try to read the same file again
				break;
			
			case 32: //substitution cipher encryption from console input
				printf("\nPlease enter the encryption key\n\n");
				scanf("%s", subKey);

				printf("\nPlease enter the text to be encrypted\n\n");
				scanf("%s", encryptArray); //save to an array the text from the console

				subEncrypt(encryptArray, strlen(encryptArray), subKey); //encrypt the array
				fprintf(encrypted, "%s", encryptArray); //print to a file the encrypted array
				printf("The encrypted string is %s\n\n successfully written to encrypted.txt\n\n", encryptArray);
				break;
			
			case 41: //substitution cipher decryption from file
				printf("What is the name of the file you wish to decrypt? Include the filetype (eg .txt) at the end, and place the file in the same directory as this code\n\n");
				scanf("%s", fileName); //scan for file name

				while(fileExists(fileName) == 0) //check if the file exists, and if it doesn't, continually asks for a new file name
				{
					printf("File does not exist, try again\n");
					scanf("%s", fileName); //scan for file name again
				}

				userText = fopen(fileName, "r");
				printf("What is the name of the file with the substitution key for decrypting this file?\n\nIt should be formatted like \n#QWERTYUIOPASDFGHJKLZXCVBNM\nwhere the position of each letter tells you which letter is being replaced, with a # at the start.\nAn example key is included, called key.txt\n\n");
				scanf("%s", subKeyFile);

				keyFile = fopen(subKeyFile, "r"); //open the file stream to the key file
				fgets(subKey, 27, (FILE*)keyFile); //copy the file to the array with the key
				fclose(keyFile); //close the file

				//find size of file to use in array
				fseek(userText, 0, SEEK_END); //seek to the end of the array
				fileSize = ftell(userText); //set file size to the position of the end of the file, ie the size of the file
				fseek(userText, 0, SEEK_SET); //seek back to the start of the file

				fgets(decryptArray, fileSize + 1, (FILE*)userText); //read the file into an array
				subDecrypt(decryptArray, fileSize, subKey); //encrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the encrypted array to the file encrypted.txt
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray); //print the encrypted array to console
				fclose(userText); //close the file stream from the user in case they try to read the same file again
				break;
			
			case 42: //substitution cipher decryption from console input
				printf("Please enter the text to be decrypted\n\n");
				scanf("%s", decryptArray); //scan for text input

				printf("What is the substitution key to decrypt this file? It should be all uppercase, starting with a # symbol\n\n");
				scanf("%s", subKey);

				subDecrypt(decryptArray, strlen(decryptArray), subKey); //decrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the array to the file
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray);
				break;
			
			case 51: //rotation cipher decryption without a key, from file 
				printf("What is the name of the file you wish to decrypt? Include the filetype (eg .txt) at the end\n\n");
				scanf("%s", fileName); //scan for file name

				while(fileExists(fileName) == 0) //check if the file exists, and if it doesn't, continually asks for a new file name
				{
					printf("File does not exist, try again\n");
					scanf("%s", fileName); //scan for file name again
				}

				printf("%s will be decrypted to the file decrypted.txt\n\n");

				userText = fopen(fileName, "r"); //open the file stream to the user's file

				//find size of file to use in array
				fseek(userText, 0, SEEK_END);
				fileSize = ftell(userText);
				fseek(userText, 0, SEEK_SET);

				fgets(decryptArray, fileSize + 1, userText); //read the file to an array
				rotationDecryptNoKey(decryptArray, fileSize); //decrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the array to the file
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray);
				fclose(userText); //close the file stream from the user in case they try to read the same file again
				break;
			
			case 52: //rotation cipher decryption without a key, from console input 
				printf("Please enter the text to be decrypted\n\n");
				scanf("%s", decryptArray); //scan for file name

				rotationDecryptNoKey(decryptArray, strlen(decryptArray)); //decrypt the array
				fprintf(decrypted, "%s", decryptArray); //print the array to the file
				printf("The decrypted string is %s\n\n successfully written to decrypted.txt\n\n", decryptArray);
				break;
			
			case 61: //substitution cipher decryption with a key, from file
				printf("\n\nUnfinished\n\n");
				break;
			
			case 62: //substitution cipher decryption with a key, from console input
				printf("\n\nUnfinished\n\n");
				break;
			
			default:
				printf("\nYou should not be here\n"); //debugging, there should be no way for the flow of the program to allow this option
				break;
		}
	}

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
This function is very similar to rotationEncrypt(), except it subtracts k instead of adding k

Task 2

Last Updated 28/04/2019
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
			x[i] = x[i] - 65 - k; //converts x to a number between 1 and 26, subtracts k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
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
			x[i] = x[i] - 97 - k; //converts x to a number between 1 and 26, subtracts k, and finds x % 26 so as to 'loop back around', then converts it back to the correct ASCII values
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

Supercedes rotationDecryptNoKey, which simplay assumes E is the most common letter

UNFINISHED, spellCheck() not working

Task 5

Last Updated 28/04/2019
*/
int rotationDecryptForce(char *x, int n)
{
	char temp[n]; //array to hold copies of x to test possible keys
	int bestK = 0; //int to hold the 
	int check = 0; //int to hold the highest number of matching words
	//the following for loop cycles through each possible key, ie 'k' is the cipher key
	for(int k = 0; k < 26; k++)
	{
		for(int j = 0; j < n; j++) //resets the temp array to be the same as the array x
		{
			temp[j] = x[j];
		}
		rotationDecryptKey(temp, n, k);
		if(check < spellCheck(temp, n))
		{
			check = spellCheck(temp, n);
			bestK = k;
		}
	}

	rotationDecryptKey(x, n, bestK);

	return bestK;
}


/*

A function that assumes the most common character to be e, then determines the key from that assumption

Returns an integer that is assumed to be the key

Decrypts the array given the calculated key

Task 5

Last Updated 03/04/2019
*/
int rotationDecryptNoKey(char *x, int n)
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

/*
a function to check if a file exists

Last Updated 28/04/2019
*/
int fileExists(char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}


/*
This function goes through an array, find how many words match with words in the dictionary provided, then returns that integer.
It should be used to compare how likely different decryptions of the same array are correct, as it only returns an integer

Does not work, I'm pretty sure I'm using the isspace() function incorrectly as it doesn't seem to break words up correctly, but the flow should be correct

Last Updated 29/04/2018
*/
int spellCheck(char *x, int n)
{
	FILE *dict; //file IO pointer to read the dictionary
	dict = fopen("google-10000-english.txt", "r"); //the file 'google-10000-english.txt' contains the 10000 most common words

	int exitLoop = 0;
	int position = 0; //integer to store position of the array so that the program basically reads left to right
	int spellCount = 0;
	int counter = 0;
	char word[20]; //what sort of nerd uses words over 20 letters long
	//also the dictionary used in this file has no words over that length
	char dictWord[20];

	while(position < n) //this loop will run until the position counter has reached the end of the array x
	{
		//printf("%c", x[position]);
		//the following loop fills the word array with the next word from x - if the word is too long, it will be split into chunks
		for(int i = 0; ((i < 20) && (isspace(x[position] == 0))); i++) //this loop will run until the word array is full or whitespace is reached
		{
			word[i] = x[position];
			position++;
			//printf("%c", word[i]);
		}
		position++;
		//the following loop goes through each word in the dictionary and checks it against the word stored in the word array
		while(getc(dict) != EOF && exitLoop == 0) //loop continues until the end of the dictionary file is reached
		{
			fseek(dict, -1, SEEK_CUR); //move the counter back 1, as checking for EOF moves it forward 1
			for(int i = 0; i < strlen(word) && (isspace(getc(dict)) != 8); i ++) //this loop will run until the dictWord array is the same length as the word array or whitespace is reached
			{
				dictWord[i] = getc(dict);
			}
			while((counter < strlen(word)) && ((dictWord[counter] == word[counter]) || (dictWord[counter] == word[counter] + 32))) //this loop continues until the word doesn't match, 32 is added in case the message is upper case
			{
				counter++;
			}
			if(counter == strlen(word)) //ie if a word is the same as a word from the dictionary
			{
				spellCount++;
				exitLoop = 1;
			}
			counter = 0;
		}
		exitLoop = 0;
		//set all characters to \0 so that strlen can be used
		for(int i = 0; i < 20; i++)
		{
			word[i] = '\0';
		}
		fseek(dict, 0, SEEK_SET);
	}
	fclose(dict); //close the dictionary stream
	return spellCount; //return the count of correct words
}
