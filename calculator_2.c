#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXINSIZE 1000
#define MAXTOKSIZE 1000
#define MAXNUMSIZE 100
float runpro2();
void write_bitmap(char *plot, int width, int height, const char *filename) {
  FILE *f;
  unsigned char *img = NULL;
  int filesize = 54 + 3 * width * height;

  img = (unsigned char *) malloc(3 * width * height);
  memset(img, 0, 3 * width * height);

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      int x = i, y = j;
      int r = plot[i * width + j] * 255;
      int g = r;
      int b = r;
      if (x == height / 2 || y == width / 2)  // axis lines
        b = g = 255;
      if (r > 255) r = 255;
      if (g > 255) g = 255;
      if (b > 255) b = 255;
      img[(x + y * width) * 3 + 2] = (unsigned char)(r);
      img[(x + y * width) * 3 + 1] = (unsigned char)(g);
      img[(x + y * width) * 3 + 0] = (unsigned char)(b);
    }
  }

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(    width    );
  bmpinfoheader[ 5] = (unsigned char)(    width>> 8);
  bmpinfoheader[ 6] = (unsigned char)(    width>>16);
  bmpinfoheader[ 7] = (unsigned char)(    width>>24);
  bmpinfoheader[ 8] = (unsigned char)(   height    );
  bmpinfoheader[ 9] = (unsigned char)(   height>> 8);
  bmpinfoheader[10] = (unsigned char)(   height>>16);
  bmpinfoheader[11] = (unsigned char)(   height>>24);

  f = fopen(filename, "wb");
  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for(int i = 0; i < height; i++) {
    fwrite(img + (width * i * 3), 3, width, f);
    fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
  }

  free(img);
  fclose(f);

}

#define SIZE 1000
float x;char mode ; //strat and end change
int k = 0 , u = 0; // the indexes of tokens on the function "tokenize"
int indop = 0 , indval = 0; //the indexes of the value and operator stacks
int m=0; //when we found a digit in the input string,for m = 0 to somewhere which the character is not a digit,copy this part of input in the valuestack
float valstack[MAXTOKSIZE]; //a stack for storing the numbers
char opstack[MAXTOKSIZE]; //a stack for storing the operators
char tokens[MAXTOKSIZE][MAXNUMSIZE]; //a 2D array for tokenizing the nsinput string
void space_eliminator( char str1[] ,char str2[]); //a function for eliminating the spaces from the input stirng
int previous(char str[] ,int i); //checks that the previous char which is not a space,is a digit or not
int next(char str[] , int i); //do the same thing as previous function(i found something interesting when i was writing this sentence.The word previous                            
void tokenize(char nsinput[]);//in this sentece opacity.Because previous can be the "previous" function or a function which it's name is "previous" like 
void pushval(float num);	  //int previous.(Really i didn't understand what i said,but i hope you do!!!) :) 
float popnum();
char popopr();
void pushop(char c);
void evaluate(); //applies the operator to operands and pushes the result in value stack
void error1(); //i don't have any explanation for this one!
void runpro(); //no explanation
char thingup();//returns the last pushed operator(it doesn't pop just returns it) 
int isoperator(char c); //no explanation
int precedence(char c); //compares the precedence of two operators
char nextop();
int match_Parentheses(char str[]); //checks that the parenthesses are match or not
int isnotpa(char opera);//checks that a string is / or * or - or + or sth else
int main()
{
	printf("Hi!welcome to my calculator!!!you can enter your expression below using operators '+' , '-' , '*' , '/':\n(enter <<quit>> for end)\n");
	char quit[] = "quit";
	while(1){
    char input[MAXINSIZE];
	fgets(input , MAXINSIZE , stdin);
	input[strlen(input) - 1] = '\0'; 
	if(strcmp(input , quit) || input[0] == '\0'){
		k = 0 , indval=0 , indop = 0 , u=0;
	char nsinput[MAXINSIZE];                                    //for storing the eliminated space string
    space_eliminator(input , nsinput);
	if(match_Parentheses(nsinput)){
		printf("error : Parentheses aren't match!!!(odd number of Parentheses detected!!)\n");
	exit(0);}
                  
    
    tokenize(nsinput);
	//start change
	printf("Enter the mode :( 'a' for calculate and 'b' for rasm nemoodar)\n");
	scanf("%c" , &mode);
	if(mode == 'a')
	runpro();
	if(mode == 'b'){
		
		char plot[SIZE][SIZE] = {0};
  float w = 2.0, step = 2 * w / SIZE;
  for ( x = -w; x < w; x += step) {
    float y =  runpro2();     ; //x * x;
    int i = (x + w) / step;
    //if (i > SIZE - 1) i = SIZE - 1;
    //if (i < 0) i = 0;
    int j = (y + w) / step;
    if (j > SIZE - 1 || j < 0) continue;

    plot[i][j] = 1;
  }
  write_bitmap((char *)plot, SIZE, SIZE, "sine.bmp");

  return 0;
	}
		
	}
	else{
		printf("bye!!!see you soon!!");
	return 0;
	}
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
           exit(0);                             
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
                               	
while(nsinput[u] != '\0'){
        if(isdigit(nsinput[u]) || nsinput[u]  == '.'){
			m = 0;
            for( ; nsinput[u] != '\0' ; u++ , m++){
                if(isdigit(nsinput[u]) || nsinput[u]== '.' )
                    tokens[k][m] = nsinput[u];
				else
					break;
            }
            k++;
			tokens[k-1][m] = '\0';
        }
		else if(nsinput[u] == 'x'){
			tokens[k][0] = 'x';
			tokens[k++][1] = '\0';
			u++;
		}
        else{
    switch(nsinput[u]){
		case '(':
	if(isdigit(nsinput[u-1])){
		printf("error : enter the operator between parenthes and number\n");
	exit(0);}
	case '-':
		
    case '+':
    case '*':
    case '/':
	
	case ')':
	
	if(u == 0 && nsinput[u] != '('){
		printf("error : an operator at the beggining!!!!\n");
	exit(0);
	}
	if(isnotpa(nsinput[u]) && isnotpa(nsinput[u-1]) ){ 
		printf("error : two operators collided!!!!\n");
	exit(0);}
	if(isnotpa(nsinput[u]) && isnotpa(nsinput[u+1]) ){ 
		printf("error : two operators collided!!!!\n");
	exit(0);}
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
void pushval(float num){ 
	valstack[indval++] = num;
}
float popnum(){
	return valstack[--indval];
}
char popopr(){
	return opstack[--indop];
	
}
void pushop(char c){
	opstack[indop++] = c;
	
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
		if(op1){
		pushval(op2 / op1);break;}
		else{
			printf("divided by zero!!!!");
		exit(0);}
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
			pushval(strtod(ntok , NULL));     //start change
		if(ntok[0] == 'x') {
			pushval(x);
		}									//end change
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
printf(" = %f\n",popnum());
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
int match_Parentheses(char str[]){
	int numpa = 0;
	for(int indexpa = 0 ;str[indexpa] != '\0' ; indexpa++){
		if(str[indexpa] == '(')
			numpa++;
		else if(str[indexpa] == ')')
			numpa--;
	}
	if(numpa){
		return 1;
	}
	return 0;
}
int isnotpa(char opera){
	switch(opera){
		return 2;break;
		case '+':
		case '-':
		case '*':
		case '/':
		return 1;break;
		default:
		return 0;break;
	}
}

float runpro2(){
	int calc = 0;
	while( calc < k){
		char ntok[MAXNUMSIZE];
		strcpy(ntok , tokens[calc++]);
		if(isdigit(ntok[0]))
			pushval(strtod(ntok , NULL));     //start change
		if(ntok[0] == 'x') {
			pushval(x);
		}									//end change
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
return popnum();
}
			