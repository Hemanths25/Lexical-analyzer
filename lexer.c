#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//all the keywords
static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"
};

static const char* operators = "+-*/%=!<>|&";
static const char* specialCharacters = ",;{}()[]";

FILE* fptr;

//opening the file
Status initializeLexer(const char* filename){
    fptr = fopen(filename,"r");
    if(fptr == NULL){
        printf("ERROR: File not found!\n");
        return e_failure;
    }
}

//checking for special char
int isSpecialCharacter(char ch){
    if(strchr(specialCharacters,ch)){
        printf("Special Char\t: %c\n",ch);
    }
}

//checking for operator
int isOperator(const char* str,int* i){
    int count=0;

    while(strchr(operators,str[count])){
        count++;
    }

    if(count){
    char copy[count+1];
    copy[count]='\0';
    strncpy(copy,str,count);
    printf("Operator\t: %s\n",copy);
    *i=*i+count-1;
    }
}

//checking for keywords
int isKeyword(const char* str,int* i){
    int k=0;
    while(str[k] != ' '){
        k++;
    }

    int m=0;
    while(keywords[m]){
    if(strncmp(str,keywords[m],k)==0){
        printf("Keyword\t\t: %s\n",keywords[m]);
        *i=*i+k;
        return 1;
        break;
    }
    m++;
  }
}

//checking for constants
int isConstant(const char* str,int* i){
    int m=0;

    if(str[m] == '"' || isdigit(str[m]) || str[m] == 39){
    //for string constants
    if(str[m] == '"'){
        m++;
        while(str[m]!='"'){
            m++;
        }
        m++;
    }
    //for number constants
    else if(isdigit(str[m])){
        while(isdigit(str[m]) || str[m]=='.'){
            m++;
        }
    }
    //for character constants
    else if(str[m] == 39){
        m=3;
    }

    char copy[m+1];
    copy[m]='\0';
    strncpy(copy,str,m);
    printf("Constant\t: %s\n",copy);
    *i=*i+m-1;    
    }
}

//checking for identifier
int isIdentifier(const char* str,int* i){
    int m=0;

   if(!isalpha(str[m]) && str[m] != '_') {
        return 0;
    }
    m++;

    while(isalnum(str[m]) || str[m] == '_') {
        m++;
    }

    char copy[m+1];
    copy[m]='\0';
    strncpy(copy,str,m);
    printf("Identifier\t: %s\n",copy);
    *i=*i+m-1;
}

// making file data into tokens bashed on next line
void tokens(){
    char line[256];  
    const char *delimiters = "\n";
    // Read each line from the file
    while (fgets(line, sizeof(line), fptr)) {
        // Get the first token in the line
        char *token = strtok(line, delimiters);
        int i=0;
        while(token[i]){
            //skip preprocessor lines
            if(token[i]=='#'){
                break;
            }
            //special char
            if(!isalpha(token[i])){
            isSpecialCharacter(token[i]);         
            }
            //operator
            if(!isalpha(token[i])){
            isOperator(&token[i],&i);         
            }
            //keyword
            if(isalpha(token[i])){
                isKeyword(&token[i],&i);
            }
            //constant
            isConstant(&token[i],&i);
            //identifier
            if(isalpha(token[i])){
                isIdentifier(&token[i],&i);
            }
            i++;
        }
        while (token != NULL) {    
            token = strtok(NULL, delimiters);
        }
    }
}
