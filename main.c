#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXINSIZE 1000
#define MAXTOKSIZE 1000
#define MAXNUMSIZE 100
int k = 0 , u = 0; // the indexes of tokens on the function "tokenize"
int indop = 0 , indval = 0;
float valstack[MAXTOKSIZE];
char opstack[MAXTOKSIZE];
char tokens[MAXTOKSIZE][MAXNUMSIZE];
void space_eliminator( char str1[] ,char str2[]);
int previous(char str[] ,int i);
int next(char str[] , int i);
void tokenize(char nsinput[]);
void pushval(float num);
float popnum();
char popopr();
void pushop(char c);
void evaluate();
void error1();
void runpro();
char thingup();
int isoperator(char c);
int precedence(char c);
char nextop();
int main()
{
	while(1){
    char input[MAXINSIZE];
	fgets(input , MAXINSIZE , stdin);
	if(strcmp(input , "quit") || input[0] == '\0'){
		k = 0 , indval=0 , indop = 0 , u=0;
	input[strlen(input) - 1] = '\0';
	char nsinput[MAXINSIZE];                                    //for storing the eliminated space string
    space_eliminator(input , nsinput);
	
	
    //char tokens[MAXTOKSIZE][MAXNUMSIZE];                        //for getting tokens
    
    tokenize(nsinput);
	runpro();
	}
	else
		break;
		
	}
}
void space_eliminator(char str1[] ,char str2[]){ //to eliminate spaces
    int i = 0,j = 0;
while(str1[i] != '\0'){
    if(str1[i] != ' '){
       str2[j++] = str1[i++];
         }
       else{
        if(!next(str1 , i) || !previous(str1,i))
       i++;
       else{
        puts("input error : mistaken numbers!!!!");
           exit(0);                             //incomplete part
        }
        }
}
str2[j] = '\0';       //to make str2 to a string
}
int next(char str[] , int i){
while(str[i] != '\0'){
    if(str[i] != ' '){
        if(isdigit(str[i]) || str[i] == '.')
        return 1;
    else
        return 0;
        }
        i++;
}
return 0;
}
int previous(char str[] ,int i){
while(i >= 0){
    if(str[i] != ' ' || str[i] == '.'){
        if(isdigit(str[i]))
        return 1;
    else
        return 0;
    }
    i--;
}
return 0;
}
void tokenize(char nsinput[]){
//int i=0, k=0;                               	i think this variables should be global ones but i'm not sure.
while(nsinput[u] != '\0'){
        if(isdigit(nsinput[u]) || nsinput[u]  == '.'){
                int m=0;
            for( ; nsinput[u] != '\0' ; u++ , m++){
                if(isdigit(nsinput[u]) || nsinput[u]== '.')
                    tokens[k][m] = nsinput[u];
				else
					break;
            }
            k++;
			tokens[k-1][m] = '\0';
        }
        else{
    switch(nsinput[u]){
    case '+':
    case '-':
    case '*':
    case '/':
	case '(':
	case ')':
        tokens[k][0] = nsinput[u];
        tokens[k][1] = '\0';
        u++;
        k++;
        break;
    default:
        error1();
        break;
    }
        }
}
}
void pushval(float num){ //from this poinnt to the end the program is'n complete
	valstack[indval++] = num;
	//printf("<-  %f ( v:%d )\n", valstack[indval - 1], indval - 1);
}
float popnum(){
	//printf("----> %f ( v:%d )\n", valstack[indval - 1], indval - 1);
	return valstack[--indval];
}
char popopr(){
	//printf("----> %c ( p:%d )\n", opstack[indop - 1], indop - 1);
	return opstack[--indop];
	
}
void pushop(char c){
	//opstack[indop++] = tokens[tokindex][0];
	//strcpy(opstack + indop , tokens[tokindex]);
	opstack[indop++] = c;
	//printf("<-- %c ( p:%d )\n", opstack[indop - 1], indop - 1);
}
void evaluate(){
	float op1 , op2;
	op1 = popnum();
	op2 = popnum();
	char operator1 = popopr();
	switch(operator1){
		case '+':
		pushval(op1 + op2);break;
		case '-':
		pushval(op2 - op1);break;
		case '*':
		pushval(op1 * op2);break;
		case '/':
		pushval(op2 / op1);break;
		//default:
		//error1();break;
	}
}
void error1(){
	puts("wrong input detected!!!!!!");
exit(0);
}
void runpro(){
	int calc = 0;
	while( calc < k){
		char ntok[MAXNUMSIZE];
		strcpy(ntok , tokens[calc++]);
		if(isdigit(ntok[0]))
			pushval(strtod(ntok , NULL));
		else if(ntok[0] == '(')
			pushop('(');
		else if(ntok[0] == ')'){
			while( thingup() != '('){
			evaluate();	
	}
		popopr();}
		else if(isoperator(ntok[0])){
			while(indop > 0 && precedence(nextop()) >= precedence(ntok[0])){
			evaluate();}
		pushop(ntok[0]);}
	}
	while(indop>0)
		evaluate();
printf(" The result is = %f\n",popnum());
}
char thingup(){
return opstack[indop  - 1];
}
int isoperator(char c){
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		return 1;break;
		default:
	return 0;}
}
int precedence(char c){
		switch(c){
			case '*':
			case '/':
			return 2;break;
			case '+':
			case '-':
			return 1;
			case '(':
			return -1;
		}
	}
char nextop(){
		return opstack[indop - 1];
		}
			