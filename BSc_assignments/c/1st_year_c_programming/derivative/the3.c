/******type declarations*******/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void *malloc(size_t size);

typedef struct opstack{
	char oper;
	struct opstack *next;
} opstack, *stackpoint;

typedef union atomic{
	char *str;
	char unop;
} atomic;

typedef struct outstack{
	atomic value;

	struct outstack *right;
}outstack, *outpointer;

typedef struct derstack{
	char * normal;
	char *result;
	struct derstack *other;
}derstack, *derp;

#define OPER(opstack) ((opstack)->oper)
#define NEXT(opstack) ((opstack)->next)
#define VALUE(outstack) ((outstack)->value) 
#define RIGHT(outstack) ((outstack)->right)
#define NOR(derstack) ((derstack)->normal)
#define DER(derstack) ((derstack)->result)
#define OTHER(derstack) ((derstack)->other)

/******end of type declarations*********/
/********global variables**********/
stackpoint First_of_Stack, Next_Stack;
outpointer Last_Queue,New_Output,First_Queue;
derp first_of_der=NULL,derbuff;
char ch,*tmpstr,*optemp;
/*******end of global variables********/

/***********helper functions***********/
int isoper(int x){  /*if ch is an operator, returns 1*/
	return x=='+'||x=='*'||x=='^'||x=='-'||x=='/';
}
int prevalue(int z){	/*returns precedence value of character*/
	if (z=='(')
		return 0;
	else if (z=='+'||z=='-')
		return 1;
	else if (z=='*'||z=='/')
		return 2;
	else if (z=='^')
		return 3;
	else return 4;
}
int precedence(int x, int y){  /*if x is less returns 1, if equal 0, if x is greater -1*/
	if (prevalue(x)<prevalue(y))
		return 1;
	else if (prevalue(x)==prevalue(y))
		return 0;
	else return -1;
}
void labcopy(char *x){ /*copying the label to output queue*/
	New_Output=(outpointer)malloc(sizeof(outstack)); 
	RIGHT(Last_Queue)=New_Output;
	RIGHT(New_Output)=NULL;
	VALUE(New_Output).str=strdup(x);
	Last_Queue=New_Output;
}
void reg_op_output(){ /*registering operator to output queue*/
	New_Output=(outpointer)malloc(sizeof(outstack)); 
	RIGHT(Last_Queue)=New_Output;
	RIGHT(New_Output)=NULL;
	VALUE(New_Output).unop=OPER(First_of_Stack);
	Last_Queue=New_Output;
}
void push_on_stack(){/*pushing op onto stack*/
	Next_Stack=(stackpoint)malloc(sizeof(opstack));
	OPER(Next_Stack)=ch;
	NEXT(Next_Stack)=First_of_Stack;
	First_of_Stack=Next_Stack;
}
void pop_stack(){ /*popping an element from stack*/
	Next_Stack=NEXT(First_of_Stack);
	free(First_of_Stack);
	First_of_Stack=Next_Stack;
}
int clean_first(){
	New_Output=RIGHT(First_Queue);
	free(First_Queue);
	First_Queue=New_Output;
	return 0;
}
char * der(char *x){
	if(!strcmp(x,"X"))
		return "1";
	else if(!strcmp(x,"sin"))
		return "cos";
	else if(!strcmp(x,"tan"))
		return "1+tan^2";
	else if(!strcmp(x,"sh"))
		return "ch";
	else if(!strcmp(x,"ch"))
		return "sh";
	else if(!strcmp(x,"ln"))
		return "1/X";
	else if(*x>=48&&*x<=57)
		return "0";
}
void trans_str(char * x){
	while(*x)
		*(tmpstr++)=*(x++);
}

int need_par_multi(char *x){
	int para=0;	
	for(;*x;x++)
		if(*x=='+'||*x=='-')
			{if(!para)
				return 1;}
		else if(*x=='(')
			para++;
		
		else if(*x==')')
			para--;
	
	return 0;
}

int need_par_quo(char *x){
	int para=0;
	for(;*x;x++)
		if(*x=='+'||*x=='-'||*x=='*'||*x=='/')
			{if(!para)
				return 1;}
		else if(*x=='(')
			para++;
		
		else if(*x==')')
			para--;
	return 0;

}

int convert(char *x){
	int t=0;
	while(*x)
		t=10*t+*(x++)-48;

	return t;
}

char* make_str(int x){
	char a[4]={'\0'},i=1,*p,*r;	
	r=p=malloc(sizeof(char)*4);	
	while(x){
		a[i]=x%10+48;
		x/=10;
		i++;
		
	}i--;
	for(;a[i];p++,i--)
		*p=a[i];
	*p='\0';
	return r;
}

int look_up_for_ex(char * x){
	int para=0;
	for(;*x;x++)
		if(*x=='^')
			{if(!para)
				{optemp=x; *(optemp++)='\0'; return 1;}}
		else if(*x=='(')
			para++;
		
		else if(*x==')')
			para--;
	return 0;


}


/**********end of helper functions**********/
/**********main derivative side*************/

void get_input(){/*1) DIJKSTRA'S ALGORITHM*/   /*getting input and parsing*/ 
	int pretemp,i=0;
	char labbuffer[4];	

	First_of_Stack=(stackpoint)malloc(sizeof(opstack));
	NEXT(First_of_Stack)=NULL;
	OPER(First_of_Stack)==0;

	Last_Queue=(outpointer)malloc(sizeof(outstack)); /*start values for output stack*/
	RIGHT(Last_Queue)=NULL;
	First_Queue=Last_Queue; /*saving the place of first queue pointer*/

	ch=getchar();
	while(ch!=EOF){
		if(isspace(ch)){
			ch=getchar();
			continue;
		}		
		else if(isoper(ch)){
			pretemp=precedence(ch,OPER(First_of_Stack));
			
			if(pretemp==1||pretemp==0){/*if precedence status is ok, reg to output*/
				if(OPER(First_of_Stack)=='^'){
					if(NEXT(First_of_Stack)){
						pretemp=precedence(ch,OPER(NEXT(First_of_Stack)));	
						if(pretemp==1||pretemp==0){
							reg_op_output();
							pop_stack();
							reg_op_output();
							OPER(First_of_Stack)=ch; /*replacing with the input and assignment */
						}	
						else {
							reg_op_output();
							OPER(First_of_Stack)=ch; /*replacing with the input and assignment */
						}

					}			
					else {
						reg_op_output();
						OPER(First_of_Stack)=ch; /*replacing with the input and assignment */
					}
				}				
				else if(OPER(First_of_Stack)==0)
					OPER(First_of_Stack)=ch;
				else{											
					reg_op_output();
					OPER(First_of_Stack)=ch; /*replacing with the input and assignment */
				}					
			}	
			else push_on_stack();
			
		}
		else if(ch=='(')
			push_on_stack();
		
		else if(ch==')'){
			while(OPER(First_of_Stack)!='('){
				reg_op_output();
				pop_stack();
			}
			pop_stack();
		}
		else {
			for(i=0;!(isspace(ch)||isoper(ch)||ch==')'||ch==EOF);i++){ /*getting the label*/
				labbuffer[i]=ch;	
				ch=getchar();
			}
			labbuffer[i]='\0';
			labcopy(labbuffer);
			continue; /*do not get new character*//*pass this step*/
		}
		ch=getchar(); /*get new character*/
	}
	while(First_of_Stack){ /*test if first of stack is null or not*/
		if(OPER(First_of_Stack))
			reg_op_output();/*register character to output and pop an element from stack*/
		pop_stack();
	}

	clean_first(); /*cleaning the irrelevant output queue*/
}
/**********end of input part***********/
void get_derivative(){
	char *tmpstr2, *no1,*no2,*expotemp,*optemp2,*tmpstr3;
	int parant=0,a,b,r;
	
	while(First_Queue){
		switch(VALUE(First_Queue).unop){
		
		case '+':
			derbuff=OTHER(first_of_der);/*choosing the first operand*/
			
			/*derivative side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(DER(first_of_der))+2)); 
			tmpstr2=tmpstr;			
			
			if(strcmp(DER(derbuff),"0")){
				trans_str(DER(derbuff));
				if(strcmp(DER(first_of_der),"0")){
					*(tmpstr++)='+';
					trans_str(DER(first_of_der));
				}
			}
			else trans_str(DER(first_of_der));
			
			*tmpstr='\0';
			DER(derbuff)=tmpstr2;
			
			/*normal side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+strlen(NOR(first_of_der))+2)); 
			tmpstr2=tmpstr;	
			

			trans_str(NOR(derbuff));
			*(tmpstr++)='+';
			trans_str(NOR(first_of_der));	
			*tmpstr='\0';
			NOR(derbuff)=tmpstr2;

			free(first_of_der);  /*freeing second operand*/
			first_of_der=derbuff;
								
			break;
		case '-':
			derbuff=OTHER(first_of_der);/*choosing the first operand*/
			 
			/*derivative side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(DER(first_of_der))+2));
			tmpstr2=tmpstr;
			
			trans_str(DER(derbuff));
			
			optemp2=strdup(DER(first_of_der));
			for(optemp=optemp2;*optemp;optemp++){
				if(*optemp=='+'){
					if(!parant)
						*optemp='-';}
				else if(*optemp=='-'){
					if(!parant)
						*optemp='+';}
				else if(*optemp=='(')
					parant++;
				else if(*optemp==')')
					parant--;
			}
			if(strcmp(optemp2,"0")){				
				*(tmpstr++)='-';					
				trans_str(optemp2);
			}


			*tmpstr='\0';
			DER(derbuff)=tmpstr2;
			
			/*normal side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+strlen(NOR(first_of_der))+2));
			tmpstr2=tmpstr;
			
			trans_str(NOR(derbuff));
			*(tmpstr++)='-';

			optemp2=strdup(NOR(first_of_der));
			for(optemp=optemp2;*optemp;optemp++){
				if(*optemp=='+'){
					if(!parant)
						*optemp='-';}
				else if(*optemp=='-'){
					if(!parant)
						*optemp='+';}
				else if(*optemp=='(')
					parant++;
				else if(*optemp==')')
					parant--;
			}
			trans_str(optemp2);
			*tmpstr='\0';
			NOR(derbuff)=tmpstr2;
			


			free(first_of_der);  /*freeing second operand*/
			first_of_der=derbuff;
			
			break;	
		
		case '*':
			derbuff=OTHER(first_of_der);/*choosing the first operand*/
			 
			/*derivative side*/
		tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(NOR(derbuff))+strlen(DER(first_of_der))+strlen(NOR(first_of_der))+12));
			tmpstr2=tmpstr;
			a=strcmp(DER(derbuff),"0")&&strcmp(NOR(first_of_der),"0");
			b=strcmp(DER(first_of_der),"0")&&strcmp(NOR(derbuff),"0");
			
			if(a){
				if(strcmp(DER(derbuff),"1")){
					
					if(need_par_multi(DER(derbuff))){ 
						*(tmpstr++)='(';
						trans_str(DER(derbuff));
						*(tmpstr++)=')';
					}			
					else trans_str(DER(derbuff));
					
					if(strcmp(NOR(first_of_der),"1")){
						*(tmpstr++)='*';	
						if(need_par_multi(NOR(first_of_der))){  
							*(tmpstr++)='(';
							trans_str(NOR(first_of_der));
							*(tmpstr++)=')';
						}
						else trans_str(NOR(first_of_der));
					}
				}
				else trans_str(NOR(first_of_der));
			}
			if(a&&b)			
				*(tmpstr++)='+';
			
			if(b){
				if(strcmp(DER(first_of_der),"1")){
					
					if(need_par_multi(DER(first_of_der))){
						*(tmpstr++)='(';
						trans_str(DER(first_of_der));
						*(tmpstr++)=')';
					}
					else trans_str(DER(first_of_der));
					
					if(strcmp(NOR(first_of_der),"1")){
						*(tmpstr++)='*';	
						if(need_par_multi(NOR(derbuff))){ 
							*(tmpstr++)='(';
							trans_str(NOR(derbuff));
							*(tmpstr++)=')';
						}
						else trans_str(NOR(derbuff));
					}
				}
				
				else trans_str(NOR(derbuff));
				
			}
			if(!(a||b))
				tmpstr2="0";

			*tmpstr='\0';

			DER(derbuff)=tmpstr2;
						
			/*normal side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+strlen(NOR(first_of_der))+6));
			tmpstr2=tmpstr;
		
			if(need_par_multi(NOR(derbuff))){ 
				*(tmpstr++)='(';
				trans_str(NOR(derbuff));
				*(tmpstr++)=')';
			}
			else trans_str(NOR(derbuff));
			*(tmpstr++)='*';

			if(need_par_multi(NOR(first_of_der))){  
				*(tmpstr++)='(';
				trans_str(NOR(first_of_der));
				*(tmpstr++)=')';
			}
			else trans_str(NOR(first_of_der));
			*tmpstr='\0';		
			
			
			NOR(derbuff)=tmpstr2;
			free(first_of_der);  /*freeing second operand*/
			first_of_der=derbuff;
			break;
		
		case '/':
			derbuff=OTHER(first_of_der);/*choosing the first operand*/
						 
			/*derivative side*/
		tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(NOR(derbuff))+strlen(DER(first_of_der))+2*strlen(NOR(first_of_der))+17));
			tmpstr2=tmpstr;

			a=strcmp(DER(derbuff),"0")&&strcmp(NOR(first_of_der),"0");
			b=strcmp(DER(first_of_der),"0")&&strcmp(NOR(derbuff),"0");
			
			if(a){
				if(strcmp(DER(derbuff),"1")){
					
					if(need_par_multi(DER(derbuff))){ 
						*(tmpstr++)='(';
						trans_str(DER(derbuff));
						*(tmpstr++)=')';
					}			
					else trans_str(DER(derbuff));
					
					if(strcmp(NOR(first_of_der),"1")){
						*(tmpstr++)='*';	
						if(need_par_multi(NOR(first_of_der))){ 
							*(tmpstr++)='(';
							trans_str(NOR(first_of_der));
							*(tmpstr++)=')';
						}
						else trans_str(NOR(first_of_der));
					}
				}
				
				else trans_str(NOR(first_of_der));
			}
			else *(tmpstr++)='0';
				
			optemp=NULL;
			if(b){
				*(tmpstr++)='-';
				optemp=tmpstr;
				if(strcmp(DER(first_of_der),"1")){
					
					if(need_par_multi(DER(first_of_der))){
						*(tmpstr++)='(';
						trans_str(DER(first_of_der));
						*(tmpstr++)=')';
					}
					else trans_str(DER(first_of_der));
					
					if(strcmp(NOR(derbuff),"1")){
						*(tmpstr++)='*';	
						if(need_par_multi(NOR(derbuff))){  
							*(tmpstr++)='(';
							trans_str(NOR(derbuff));
							*(tmpstr++)=')';
						}
						else trans_str(NOR(derbuff));
					}
				}
				else if(need_par_multi(NOR(derbuff))){
						*(tmpstr++)='(';
						trans_str(NOR(derbuff));
						*(tmpstr++)=')';
				}
				else trans_str(NOR(derbuff));
				
			}

			*tmpstr='\0';
			tmpstr3=tmpstr2; /*mark for quotient*/
		tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(NOR(derbuff))+strlen(DER(first_of_der))+2*strlen(NOR(first_of_der))+20));
			tmpstr2=tmpstr;
			
		if(optemp){
			for(;*optemp;optemp++){
				if(*optemp=='+'){
					if(!parant)
						*optemp='-';}
				else if(*optemp=='-'){
					if(!parant)
						*optemp='+';}
				else if(*optemp=='(')
					parant++;
				else if(*optemp==')')
					parant--;
			}
		}
			
			if(strcmp(tmpstr3,"0")){
				if(need_par_multi(tmpstr3)){ 
					*(tmpstr++)='(';
					trans_str(tmpstr3);
					*(tmpstr++)=')';
				}
				else trans_str(tmpstr3);
				
				if(strcmp(NOR(first_of_der),"1")){
					*(tmpstr++)='/';
					if(need_par_quo(NOR(first_of_der))){  
						*(tmpstr++)='(';
						trans_str(NOR(first_of_der));
						*(tmpstr++)=')';
						*(tmpstr++)='^';
						*(tmpstr++)='2';

					}
					else if(look_up_for_ex(NOR(first_of_der))){
						trans_str(NOR(first_of_der));
						*(tmpstr++)='^';
				
						no2=no1=(char *)malloc(sizeof(char)*4);
						while(*optemp)
							*(no1++)=*(optemp++);
						*no1='\0';

						trans_str(make_str(convert(no2)*2));
					}				
					else{
						trans_str(NOR(first_of_der));
						*(tmpstr++)='^';
						*(tmpstr++)='2';

					}
				}
			}
			
			else tmpstr2="0";

			*tmpstr='\0';			
			DER(derbuff)=tmpstr2;

			/*normal side*/
			tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+strlen(NOR(first_of_der))+6));
			tmpstr2=tmpstr;
		
			if(need_par_multi(NOR(derbuff))){ 
				*(tmpstr++)='(';
				trans_str(NOR(derbuff));
				*(tmpstr++)=')';
			}
			else trans_str(NOR(derbuff));
			*(tmpstr++)='/';
			
			if(need_par_quo(NOR(first_of_der))){  
				*(tmpstr++)='(';
				trans_str(NOR(first_of_der));
				*(tmpstr++)=')';
			}
			else trans_str(NOR(first_of_der));
			*tmpstr='\0';			


			NOR(derbuff)=tmpstr2;
			free(first_of_der);  /*freeing second operand*/
			first_of_der=derbuff;
			break;
		
		case '^':
			derbuff=OTHER(first_of_der);  /*choosing the first operand*/

			if(need_par_quo(NOR(derbuff))){
				tmpstr=(char *)malloc(sizeof(char)*(strlen(DER(derbuff))+strlen(NOR(derbuff))+20));
				tmpstr2=tmpstr;	
	
				*(tmpstr++)='(';
				trans_str(NOR(derbuff));
				*(tmpstr++)=')';
				if((r=convert(NOR(first_of_der)))>2){
					*(tmpstr++)='^';
					trans_str(make_str(r-1));
				}
				*(tmpstr++)='*';
				trans_str(NOR(first_of_der));
				
				
				if(!strcmp(DER(derbuff),"0"))
					tmpstr2="0";
				else if(!strcmp(DER(derbuff),"1"))
					;
				else{
					*(tmpstr++)='*';
					if(need_par_multi(DER(derbuff))){ 
						*(tmpstr++)='(';
						trans_str(DER(derbuff));
						*(tmpstr++)=')';
					}
					else trans_str(DER(derbuff));
				}				
				*tmpstr='\0';
				

				expotemp=DER(derbuff);				
				DER(derbuff)=tmpstr2;
								

				/*for normal*/
				tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(first_of_der))+strlen(NOR(derbuff))+4));
				tmpstr2=tmpstr;
				
				*(tmpstr++)='(';
				trans_str(NOR(derbuff));
				*(tmpstr++)=')';
				*(tmpstr++)='^';
				trans_str(NOR(first_of_der));
				*tmpstr='\0';
				NOR(derbuff)=tmpstr2;
			}
			else if(look_up_for_ex(NOR(derbuff))){
				
				/*derivative side*/
				tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+15+strlen(expotemp)));
				tmpstr2=tmpstr;	
				trans_str(NOR(derbuff));
				
				
				no2=no1=(char *)malloc(sizeof(char)*4);
				while(*optemp)
					*(no1++)=*(optemp++);
				*no1='\0';
				
				
				if((r=convert(no2)*convert(NOR(first_of_der)))>2){
					*(tmpstr++)='^';
					trans_str(make_str(r-1));
				}
				
				*(tmpstr++)='*';
				trans_str(make_str(r));
				
				if(!strcmp(expotemp,"0"))
					tmpstr2="0";
				else if(!strcmp(expotemp,"1"))
					;
				else{
					*(tmpstr++)='*';
					if(need_par_multi(expotemp)){ 
						*(tmpstr++)='(';
						trans_str(expotemp);
						*(tmpstr++)=')';
					}
					else trans_str(expotemp);
				}				
				*tmpstr='\0';
				DER(derbuff)=tmpstr2;

				/*normal side*/
				tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+3));
				tmpstr2=tmpstr;
				trans_str(NOR(derbuff));
				*(tmpstr++)='^';
				trans_str(make_str(convert(no2)*convert(NOR(first_of_der))));
				*tmpstr='\0';
				NOR(derbuff)=tmpstr2;	
				
			}
			else {
				/*derivative side*/
				tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(derbuff))+15+strlen(DER(derbuff))));
				tmpstr2=tmpstr;	
								
				trans_str(NOR(derbuff));
				if((r=convert(NOR(first_of_der)))>2){
					*(tmpstr++)='^';
					trans_str(make_str(r-1));
				}
				
				*(tmpstr++)='*';
				trans_str(make_str(r));
				
				if(!strcmp(DER(derbuff),"0"))
					tmpstr2="0";
				else if(!strcmp(DER(derbuff),"1"))
					;
				else{
					*(tmpstr++)='*';
					if(need_par_multi(DER(derbuff))){ 
						*(tmpstr++)='(';
						trans_str(DER(derbuff));
						*(tmpstr++)=')';
					}
					else trans_str(DER(derbuff));
				}			
				
				*tmpstr='\0';
				expotemp=DER(derbuff);				
				DER(derbuff)=tmpstr2;

				/*normal side*/
				tmpstr=(char *)malloc(sizeof(char)*(strlen(NOR(first_of_der))+strlen(NOR(derbuff))+2));
				tmpstr2=tmpstr;
				
				trans_str(NOR(derbuff));
				*(tmpstr++)='^';
				trans_str(NOR(first_of_der));
				*tmpstr='\0';
				NOR(derbuff)=tmpstr2;
				
			}
			free(first_of_der);  /*freeing second operand*/
			first_of_der=derbuff;
			break;
		default:
			derbuff=(derp)malloc(sizeof (derstack)); /*new derivative queue*/
			OTHER(derbuff)=first_of_der;
			NOR(derbuff)=strdup(VALUE(First_Queue).str);
			DER(derbuff)=der(NOR(derbuff));	
			first_of_der=derbuff;	
		}
		clean_first(); /*cleaning the first output queue*/
	}
	printf("%s",DER(first_of_der));
}
int main(){
	get_input();
	get_derivative();
		
	return 0;
}


