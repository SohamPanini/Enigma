#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define r1   "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define r2   "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define r3   "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define r4   "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define r5   "VZBRGITYUPSDNHLXAWMJQOFECK"
#define refA "EJMZALYXVBWFCRQUONTSPIKHGD"
#define refB "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define MAX_LEN 100

FILE *fptr;
char alpha[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotor1[27] = "";
char rotor2[27] = "";
char rotor3[27] = "";
char ref[27]    = "";
int offset1;
int offset2;
int offset3;
int offset=0;
char plugBoardConnection[5][3];

char passThroughRotors(char);
char plugBoardEncryption(char ch);
void writeInFile(char*);
void readFile();


int convertAlphaToNumeric(char ch)
{
    int ascii_val = (int)ch;
    return ascii_val-65;
}

void setupEnigma()
{
    //choose rotors out of  1 2 3 4 5
    int choice;
    printf("\nEnter the order or rotors you want to use from right to left ! ");

    //setup for rotor 3
    printf("\nPlease enter rotor 3: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        strcpy(rotor3,r1);
        break;
    case 2:
        strcpy(rotor3,r2);
        break;
    case 3:
        strcpy(rotor3,r3);
        break;
    case 4:
        strcpy(rotor3,r4);
        break;
    case 5:
        strcpy(rotor3,r5);
        break;
    default:
        strcpy(rotor3,r3);

    }


    //setup for rotor 2

    //setup for rotor 1
    printf("\nPlease enter rotor 2: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        strcpy(rotor2,r1);
        break;
    case 2:
        strcpy(rotor2,r2);
        break;
    case 3:
        strcpy(rotor2,r3);
        break;
    case 4:
        strcpy(rotor2,r4);
        break;
    case 5:
        strcpy(rotor2,r5);
        break;
    default:
        strcpy(rotor2,r2);

    }

    //setup for rotor 1

    //setup for rotor 1
    printf("\nPlease enter rotor 1: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        strcpy(rotor1,r1);
        break;
    case 2:
        strcpy(rotor1,r2);
        break;
    case 3:
        strcpy(rotor1,r3);
        break;
    case 4:
        strcpy(rotor1,r4);
        break;
    case 5:
        strcpy(rotor1,r5);
        break;
    default:
        strcpy(rotor1,r1);

    }

    //setup for reflector

    printf("\nPlease enter reflector (1=A , 2=B): ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        strcpy(ref,refA);
        break;
    case 2:
        strcpy(ref,refB);
        break;
    default:
        strcpy(ref,refB);
    }
    fflush(stdin);
    //Enter the ring starting positions:

    //for rotor 3
    printf("\nEnter the ring position for rotor 3: ");
    char startingPos;
    startingPos = getchar();
    fflush(stdin);
    offset3 = convertAlphaToNumeric(startingPos);
    printf("offset for rotor 3 is %d",offset3);

    //for rotor 2
    printf("\nEnter the ring position for rotor 2: ");
    startingPos = getchar();
    fflush(stdin);
    offset2 = convertAlphaToNumeric(startingPos);

    //for rotor 1
    printf("\nEnter the ring position for rotor 1: ");
    startingPos = getchar();
    fflush(stdin);
    offset1 = convertAlphaToNumeric(startingPos);

    //for plug board

}

void getPlugBoardEncryptions()
{
    for(int i=0; i<5; i++)
    {
        char plugBoardConnections[3]="";
        printf("\nEnter plug board connection (In the format char1char2 [Eg - QA])%d: ",(i+1));
        scanf("%s",plugBoardConnections);
        fflush(stdin);
        plugBoardConnection[i][0] = plugBoardConnections[0];
        plugBoardConnection[i][1] = plugBoardConnections[1];
    }
    //printf("\nThe plug board encryptions are %s%s",plugBoardConnection[0],plugBoardConnection[1]);
}

char rotorEncryption(char ch,int rotorNumber,bool encrypt)
{
    //printf("The offset of rotor 3 is : %d",offset3);
    //printf("\nCharacter to be encrypted is %c",ch);

    char rotor[27]="";
    switch(rotorNumber)
    {
    case 1:
        strcpy(rotor,rotor1);
        offset = offset1;
        break;
    case 2:
        strcpy(rotor,rotor2);
        if((offset2==4)&&encrypt==true)
        {
            offset2+=1;
            offset1+=1;
        }
        else if(offset3==22 && encrypt==true)
        {
            offset2+=1;
        }
        offset = offset2;
        break;
    case 3:
        strcpy(rotor,rotor3);
        if(encrypt==true)
        {
            offset3+=1;
        }
        offset = offset3;
        break;
    }

    if(offset>25)
    {
        offset = offset-26;
    }

    //printf("The offset for the third rotor is : %d",offset3);
    printf("\nRotor positions %d %d %d",offset1,offset2,offset3);
    int inputSignal = convertAlphaToNumeric(ch);
    int inputContact = inputSignal+offset;
    if(inputContact>25)
    {
        inputContact = inputContact-26;
    }
    int outputContact;
    if(encrypt==true)
    {
        outputContact = convertAlphaToNumeric(rotor[inputContact]);
    }
    else
    {
        //printf("\nThe rotor wiring is %s",rotor);
        char inverse = (char)(inputContact+65);
        for(int i = 0; i<26; i++)
        {
            //printf("\n%c",rotor[i]);
            if(inverse==rotor[i])
            {
                outputContact = i;
                break;
            }
        }
    }
    //printf("\nThe value of int output contact is %d ",outputContact);
    int outPutSignal = outputContact-offset;
    if(outPutSignal<0)
    {
        outPutSignal=outPutSignal+26;
    }
    char encryptedByRotor = (char)(outPutSignal+65);
    printf("\nAfter encryption by rotor %c",encryptedByRotor);
    printf("\n");
    printf("\n");
    return encryptedByRotor;
}

char reflection(char input)
{
    int inputSignal = convertAlphaToNumeric(input);
    return ref[inputSignal];
}

char plugBoardEncryption(char ch)
{
    for(int i =0; i<5; i++)
    {
        if(ch==plugBoardConnection[i][0])
        {
            return plugBoardConnection[i][1];
        }
        else if(ch==plugBoardConnection[i][1])
        {
            return plugBoardConnection[i][0];
        }
    }
    return ch;
}







char* encryptString(char line[])
{
    char encrypted[MAX_LEN] = "";
    for(int i = 0; line[i]!='\0'; i++)
    {
        if(isalpha(line[i])==1)
        {
            encrypted[i] = passThroughRotors(line[i]);
        }
        else
        {
            encrypted[i] = "-";
        }
    }
    printf("The encrypted string is %s",encrypted);
    return *encrypted;
}

char passThroughRotors(char ch)
{
    char plugBoardencrypt = plugBoardEncryption(ch);
    char rotor3encryption = rotorEncryption(plugBoardencrypt,3,true);
    char rotor2encryption = rotorEncryption(rotor3encryption,2,true);
    char rotor1encryption = rotorEncryption(rotor2encryption,1,true);
    char refEncryption    = reflection     (rotor1encryption       );

    rotor1encryption = rotorEncryption(refEncryption,   1,false);
    rotor2encryption = rotorEncryption(rotor1encryption,2,false);
    rotor3encryption = rotorEncryption(rotor2encryption,3,false);
    plugBoardencrypt = plugBoardEncryption(rotor3encryption);
    //printf("\nEncryption after passing through all rotors is %c",rotor3encryption);

    return plugBoardencrypt;
}





void readFile()
{
    int num;
    fptr = fopen("file1.txt","r");

    char string[MAX_LEN + 1]; // One extra byte needed
    // for the null character

    while(fgets(string, sizeof string, fptr) != NULL)
    {
        encryptString(string);
    }


//EncryptionFunction(string); // Daaal function yahan pe
    fclose(fptr);

}


int main()
{
    setupEnigma();
    getPlugBoardEncryptions();
    readFile();
    //rotorEncryption('A',3,true);
    //passThroughRotors('A');
    //printf("%s",encryptString("HELLOWORLD"));

    return 0;
}
