// File:calculate.c
//FULL NAME:EMIL BANTAK 
//sdi:sdi1800122
#include <stdio.h>
int sum=0,g=0,f=0,T=0,P=0;//THE VARIABLE sum HOLDS THE NUMBER OF '(',WHILE g HOLDS THE NUMBER OF ')',f BECOMES ONE WHEN THERE IS AN ERROR INSIDE THE EXPRESSION 
  //T IS USED TO KNOW IF THERE WERE NUMBERS IN THE EXPRESSION AND P HOLDS EACH TIME THE PENULTIMATE CHARACTER UNLESS IT IS ' ' OR '\t'
int s3(int *x);
int s4(int s,int symbol1,int symbol2,int val);
int s5(int s,int symbol1,int symbol2,int val2);
int s6(int *x,int *d4);
int s7(int *x);
  
int s1(int x)    
{                                                                                           //WE CHECK EACH TIME IF THE CHARACTER THAT IS ASSIGNED TO input OR TO *x IS ACCEPTABLE
        if((x<'0'|| x>'9') && x!=' ' && x!='\n' && x!='+' && x!='-' && x!='*' && x!='(' && x!=')' && x!='\t')  //IF x IS NOT AN ACCEPTABLE CHARACTER THEN RETURN -1 
        {			                                                                                  //OTHERWISE IF IT CONTAINS ACCEPTABLE CHARACTERS RETURN 1
                return -1;							 
        }
        else
        {
                return 1;
        }
}
int s2(int *x) //THIS FUNCTION IS USED WHEN THERE ARE PARENTHESES INSIDE THE EXPRESSION 
{
	int result,result2,result3,result4,symbol1,symbol2,val1,val2,val3,d2,d3,d4,flag,flag2,flag3,s,k;
	result=0; //result IS THE FINAL VALUE OF THE PARENTHESIS 
	result2=1; //result2 HOLDS THE RESULT OF THE MULTIPLICATION EACH TIME 
	result3=0; //result3 HOLDS THE RESULT OF THE ADDITION AND THE SUBTRACTION EACH TIME 
	result4=0;
	symbol1=1; //symbol1 AND symbol2 HOLD THE OPERATORS '+' OR '-'
	symbol2=1;
	val1=0; //val1 WILL HOLD THE DECIMAL VALUE FROM THE ascii CHARACTERS 
	val2=0; //val2 WILL HOLD THE VALUE FROM THE RECURSIVE CALL OF THE FUNCTION
	val3=0;//val3 WILL HOLD THE VALUE OF THE MULTIPLICATION FROM THE FUNCTION s3
	d2=0;//d2 IS USED TO KNOW IF THE MULTIPLICATION OPERATION HAPPENED 
	d3=0;//d3 IS USED SO THAT WE DO NOT SKIP THE CONSECUTIVE OPERATORS '+' OR '-'
	d4=0;//d4 IS USED TO KNOW THAT THE CONVERSION FROM ascii CHARACTERS TO DECIMAL FORM HAPPENED 
	s=0;//s HOLDS THE NUMBER OF CONSECUTIVE '+' AND '-'
	k=0;
	flag=0;//flag TELLS US IF THERE WAS RECURSION 
	flag2=0;//flag2 TELLS US THAT THERE WAS AN ADDITION OR SUBTRACTION OPERATION
	flag3=0;//flag3 IS USED SO THAT NO CHARACTER OF THE EXPRESSION IS SKIPPED 
	while(*x!=')')
	{
		if(flag3==0)//IF NO NEW CHARACTER HAS BEEN READ INSIDE THE FUNCTION READ THE NEXT ONE
		{
			P=*x;
		   *x=getchar();
	    }
	    flag3=0;
	    if(*x=='\n' && T==0) //IF *x IS EQUAL TO '\n' AND WE HAVE NOT READ A NUMBER THEN PRINT THE MESSAGE,RESET THE VARIABLES THAT HOLD THE NUMBER OF '(' AND ')'
		{                                //AND ASSIGN ONE TO f SO THAT IT IS DECLARED THAT THIS EXPRESSION IS WRONG 
			printf("Missing numders\n");
			sum=0;
			g=0;
			f=1;
			return -1;		
		}
	    k=s1(*x);
	    if(k==-1)                                //IF k IS EQUAL TO -1 THEN *x CONTAINS A CHARACTER THAT IS NOT ACCEPTABLE OTHERWISE IT CONTAINS A CORRECT CHARACTER
	    {
	    	printf("Wrong character\n");
	    	f=1;
	    	sum=0;
	    	g=0;
	    	return -1;
		}
		*x=s7(&*x);   //WHILE *x IS EQUAL TO ' ' OR '\t' READ THE NEXT CHARACTER THIS IS WHAT s7 DOES
		if(*x=='+') //IF THE CHARACTER WE READ IS '+' OR '-' THEN INCREASE s BY ONE 
		{
			s++; //THIS DECLARES THAT IF s IS EQUAL TO 1 WE ARE AT THE FIRST POSSIBLE CONSECUTIVE OPERATOR '+' OR '-' WHILE IF IT IS EQUAL TO 2 WE ARE AT THE SECOND CONSECUTIVE OPERATOR 
			d3=1;//WE ASSIGN 1 TO d3 SO THAT WE DO NOT SKIP READING THE NEXT '+' OR '-'
			if(s==1)
			{//IF *x CONTAINS THE ADDITION OPERATOR THEN ASSIGN 1 TO symbol1 OR TO symbol2 DEPENDING ON THE VALUE OF s OTHERWISE IF IT CONTAINS THE SUBTRACTION OPERATOR ASSIGN -1
				symbol1=1;
			}
			else if(s==2)
			{
				symbol2=1;
			}
		}
		else if(*x=='-')
		{
			s++;
			d3=1;
			if(s==1)
			{
				symbol1=-1;
			}
			else if(s==2)
			{
				symbol2=-1;
			}
		}
		while (*x=='(')  //WHILE *x IS EQUAL TO '(' CALL s2 RECURSIVELY AND ASSIGN 1 TO flag SO THAT WE KNOW AFTERWARDS THAT THERE WAS RECURSION 
		{
			sum++;
			flag=1;
			val2=s2(&*x);
			while(*x==')')//WHILE *x IS ')' READ THE NEXT CHARACTER 
			{
				g++;
				*x=getchar();
			}
	    }
		*x=s7(&*x);
		while(*x>='0' && *x<='9') //WHILE *x CONTAINS NUMBERS THAT CORRESPOND TO ascii CHARACTERS GO TO s6 AND CONVERT THEM TO DECIMAL FORM
		{
			val1=s6(&*x,&d4);
			if(f==1)   //IF AN ERROR WAS DETECTED INSIDE THE FUNCTION THEN THE VARIABLE f IS EQUAL TO 1 THEN RETURN TO WHERE YOU WERE CALLED FROM 
			{
				return -1;
			}
		}
		*x=s7(&*x);
		while(*x=='*' )
		{
			d2=1;//d2 BECOMES 1 WHICH MEANS THAT THERE WAS A MULTIPLICATION OPERATION 
			if(d4==1)//IF A CONVERSION FROM ascii CHARACTERS TO DECIMAL FORM HAPPENED BEFORE THEN d4 IS EQUAL TO 1 AND NOW THERE IS THE MULTIPLICATION OPERATION 
			{                    //THEN ASSIGN TO result2 ITS OLD VALUE TIMES THIS NUMBER
				result2=result2*val1;
				d4=0;
			}
			if(flag==1) //IF THERE WAS RECURSION BEFORE AND NOW THERE IS THE MULTIPLICATION OPERATION THEN ASSIGN TO result2 ITS OLD VALUE TIMES THE RESULT OF THE RECURSION 
			{
				result2=result2*val2;
				val2=0;
				flag=0;
			}
			val3=s3(&*x);  //WE CALL THE FUNCTION s3 WHICH IS RESPONSIBLE FOR THE MULTIPLICATION OPERATION AND WE ASSIGN THIS RESULT TO val3 
			if(f==1)//IF AN ERROR WAS DETECTED IN s3 THEN RETURN TO WHERE YOU WERE CALLED FROM  
			{
				return -1;
			}
			result4=s5(s,symbol1,symbol2,val3);//IF A NUMBER HAS BEEN ASSIGNED TO val3 THEN CALL THE FUNCTION s5 TO FIND THIS RESULT AND THEN ASSIGN TO result2 ITS  
			result2=result2*result4;  //OLD VALUE TIMES THE NEW ONE
			result4=0;
			s=0;
			symbol1=1;
			symbol2=1;
			if(*x=='(')//IF INSIDE THE MULTIPLICATION THERE IS A PARENTHESIS EXPRESSION THEN CALCULATE THAT FIRST AND THEN ASSIGN TO result ITS OLD VALUE PLUS
			{          //THE PRODUCT OF result2 TIMES THE VALUE OF THE PARENTHESIS 
				sum++;
				flag=1;
				val2=s2(&*x);
				while(*x==')')//WHILE *x IS ')' READ THE NEXT CHARACTER 
			    {
			    	g++;
				   *x=getchar();
			    }
			}
			if(flag==1)
			{
				result=result+result2*val2;
				flag=0;
				val2=0;
				result2=1;
			}
		}
	    if( d2==1)//IF A MULTIPLICATION OPERATION HAPPENED BEFORE THEN ASSIGN TO result ITS OLD VALUE PLUS THE RESULT OF THE MULTIPLICATION PLUS IF THERE WAS EARLIER THE RESULT FROM THE ADDITION OR SUBTRACTION OPERATIONS 
		{
	     	result=result+result2+result3;
		    result3=0;
			result2=1;
			val1=0;
			val3=0;
			val2=0;
			d2=0;	
		}
		if(val1!=0 )//IF A CONVERSION FROM ascii CHARACTERS TO DECIMAL FORM HAPPENED BEFORE CALL THE FUNCTION s4 TO CALCULATE THIS VALUE 
		{
			flag2=1;
			result4=s4(s,symbol1,symbol2,val1);
			result3=result3+result4;//ASSIGN TO result3 ITS OLD VALUE PLUS THE RESULT result4
			result4=0;
			val1=0;
			s=0;
			d3=0;
			symbol1=1;
			symbol2=1;
			d4=0;
		}
		if(flag==1)//IF RECURSION HAPPENED BEFORE THEN CALL THE FUNCTION s4 TO CALCULATE THIS VALUE AND ASSIGN TO result3 ITS OLD VALUE PLUS THE RESULT OF THE RECURSION 
		{
		 flag2=1;	
		 result4=s4(s,symbol1,symbol2,val2);
		 result3=result3+result4;
		 result4=0;
		 s=0;
		 symbol1=1;
		 symbol2=1;
		 flag=0;
		 val2=0;
		 d4=0;
	    }
		if(d3==0)//IF THE SYMBOL '+' OR '-' THAT YOU READ IS NOT CONSECUTIVE THEN THE COMMANDS BELOW CAN BE EXECUTED THIS IS DONE SO THAT THE '+' OR THE '-' ARE NOT LOST
		{
		    if(*x=='+')
		    {
		    	s++;
			    symbol1=1;
		    }
		    else if(*x=='-')
		    {
		    	s++;
			    symbol1=-1;
		    }
	    } 
		if(sum==g)//IF THE NUMBER OF '(' IS EQUAL TO THE NUMBER OF ')' AND BEFORE THE LAST ')' THERE WAS A PARENTHESIS OR A NUMBER OPERATION THEN ASSIGN TO result ITS OLD VALUE 
		{    //PLUS THE RESULT OF THE PARENTHESIS OR OF THE NUMBER AND RETURN CONTROL TO WHERE YOU WERE CALLED FROM 
			sum=0;
			g=0;
			if(flag2==1)
        	{
	        	result=result+result3;
        	}
			return result;
		} 
		if(*x=='\n' && sum!=g)//IF NOW *x IS EQUAL TO '\n' BUT THE NUMBER OF '(' IS NOT EQUAL TO THE NUMBER OF ')' DISPLAY AN ERROR MESSAGE AND RETURN CONTROL TO WHERE YOU WERE CALLED FROM 
	    {
	    	sum=0;
	    	g=0;
	    	f=1;
	    	printf("Missing closing parenthesis\n");
	    	return -1;
		}
	}
	if(flag2==1)//IF BEFORE THE LAST ')' THERE WAS A PARENTHESIS OR A NUMBER OPERATION THEN ASSIGN TO result ITS OLD VALUE 
	{           //PLUS THE RESULT OF THE PARENTHESIS OR OF THE NUMBER AND RETURN CONTROL TO WHERE YOU WERE CALLED FROM 
		result=result+result3;
	}
	return result;
}

int s3(int *x)//THIS FUNCTION IS USED WHEN WE HAVE MULTIPLICATION INSIDE THE EXPRESSION
{
        int result2,result3,result4,flag,symbol1,symbol2,d3,d4,s,s8,val;
        result2=1;//HOLDS THE VALUE OF THE MULTIPLICATION EACH TIME 
        result3=0;//IF INSIDE THE MULTIPLICATION THERE IS A PARENTHESIS EXPRESSION IT HOLDS THE VALUE OF THE PARENTHESIS 
        result4=0;
        flag=0;//TELLS US IF THERE WAS A PARENTHESIS EXPRESSION 
        symbol1=1;//symbol1 AND symbol2 HOLD THE OPERATOR '+' OR '-'
        symbol2=1;
        val=0;//WILL HOLD THE DECIMAL VALUE FROM THE ascii CHARACTERS 
        d3=0;//IS USED SO THAT WE DO NOT SKIP THE CONSECUTIVE CHARACTERS '+' OR '-'
        d4=0;//IS USED TO KNOW THAT THE CONVERSION FROM ascii CHARACTERS TO DECIMAL VALUE HAPPENED  
        s=0;//HOLDS THE NUMBER OF CONSECUTIVE '+' OR '-'
        s8=1;//HOLDS IF WE READ THE SYMBOL '*' CONSECUTIVELY
        while(*x=='*')
        {
           P=*x;	
		  *x=getchar();
		   *x=s7(&*x);
		   if(*x=='*')//IF *x IS EQUAL TO '*' AND s>1 THEN IT MEANS THAT WE HAVE READ CONSECUTIVE MULTIPLICATION SIGNS THEN DISPLAY AN ERROR MESSAGE AND RETURN CONTROL TO WHERE YOU WERE CALLED FROM 
		   {
		   	s8++;
		   	if (s8!=1)
		   	{
		   		printf("Unexpected character\n");
		   		f=1;
		   		sum=0;
		   		g=0;
		   		return -1;
			}
		   }
		   else 
		   {
		   	s8==0;
		   }
	       if(*x=='\n' && T==0)//IF *x IS EQUAL TO '\n' AND WE HAVE NOT READ ANY NUMBER DISPLAY AN ERROR MESSAGE 
		   {
			  printf("Missing numders\n");
			  f=1;
              return -1;		
		   }
			while (*x=='(')//IF THE CHARACTER WE READ IS '(' CALL s2 AND ASSIGN THE RESULT INSIDE THE PARENTHESIS TO result3 
			{
				sum++;
				flag=1;
				result3=s2(&*x);
				while(*x==')')
				{
					g++;
					*x=getchar();
				}
				if(f==1)
				{
					return -1;
				}	
			}
			if(flag==1)//IF THERE WAS A PARENTHESIS THEN ASSIGN TO result2 ITS OLD VALUE TIMES THE RESULT OF THE PARENTHESIS AND RETURN result2 TO WHERE YOU WERE CALLED FROM 
			{          //THIS return IS DONE SO THAT THERE IS NO CONFUSION IN THE OPERATIONS BETWEEN THE PARENTHESES
				result2=result3*result2;
				flag=0;
				result3=0;
				return result2;
			}
			*x=s7(&*x);
			while (*x=='+' || *x=='-')//WHILE *x IS '+' OR '-' CONTINUE READING 
			{
			   if(*x=='+')//IF THE CHARACTER WE READ IS '+' OR '-' THEN INCREASE s BY ONE 
			   {   //THIS DECLARES THAT IF s IS EQUAL TO 1 WE ARE AT THE FIRST POSSIBLE CONSECUTIVE OPERATOR '+' OR '-' WHILE IF IT IS EQUAL TO 2 WE ARE AT THE SECOND CONSECUTIVE OPERATOR 
				  s++;
				  d3=1;//WE ASSIGN 1 TO d3 SO THAT WE DO NOT SKIP READING THE NEXT '+' OR '-' LATER 
				  if(s==1)
				  {//IF *x CONTAINS THE ADDITION OPERATOR THEN ASSIGN 1 TO symbol1 OR TO symbol2 DEPENDING ON THE VALUE OF s OTHERWISE IF IT CONTAINS THE SUBTRACTION OPERATOR ASSIGN -1
					symbol1=1;
				  }
			  	  else if (s==2)
				  {
					symbol2=1;
				  }
				  P=*x;
			   }
			   else if (*x=='-')
			   {
				  s++;
				  d3=1;
				  if(s==1)
				  {
					symbol1=-1;
			      }
				  else if(s==2)
				  {
					symbol2=-1;
				  }
				  P=*x;
			    }
			 *x=getchar();
			 *x=s7(&*x);
		    }
		    while (*x>='0' && *x<='9')//WHILE *x CONTAINS NUMBERS THAT CORRESPOND TO ascii CHARACTERS CALL s6 AND ASSIGN THE RESULT TO val 
			{
				val=s6(&*x,&d4);
				if(f==1) //IF AN ERROR WAS DETECTED INSIDE THE FUNCTION THEN THE VARIABLE f IS EQUAL TO 1 THEN RETURN TO WHERE YOU WERE CALLED FROM 
				{
					return -1;
				}
			}
			if(val!=0 && d4==1)//IF A NUMBER HAS BEEN ASSIGNED TO val THEN CALL THE FUNCTION s5 TO CALCULATE THE VALUE  
        	{                                //AND THEN ASSIGN TO result2 ITS OLD VALUE TIMES THE RESULT OF s5
        		result4=s5(s,symbol1,symbol2,val);
        		result2=result2*result4;
        		result4=0;
				val=0;
				s=0;
				s8=0;
				d3=0;
				d4=0;
				symbol1=1;
				symbol2=1;
			}
	        if(d3==0)//IF THE CHARACTER '+' OR '-' IS NOT CONSECUTIVE THEN THE COMMANDS BELOW ARE EXECUTED 
	        {
	        	if(*x=='+')
	        	{
	        		s++;
	        		symbol1=1;
				}
				else if (*x=='-')
				{
					s++;
					symbol1=-1;
				}
			}
			if(*x=='*')//IF THE CHARACTER '*' IS CONSECUTIVE THEN PRINT AN ERROR MESSAGE AND RETURN CONTROL TO WHERE YOU WERE CALLED FROM  
		   {
		   	s8++;
		   	if (s8==2)
		   	{
		   		printf("Unexpected character\n");
		   		f=1;
		   		sum=0;
		   		g=0;
		   		return -1;
			}
		   }
		   else 
		   {
		   	s8==0;
		   }
			*x=s7(&*x);
        }
        return result2;//RETURN THE RESULT OF THE MULTIPLICATION 
}

int s4(int s,int symbol1,int symbol2,int val)//THIS FUNCTION IS USED FOR CALCULATING NUMBERS THAT HAVE ADDITIONS OR SUBTRACTIONS IN THEIR EXPRESSION
{
	int result;
	result=0;
	if(s==1 || s==0)//IF THE NUMBER OF CONSECUTIVE SYMBOLS IS ONE OR NONE THEN ASSIGN TO result THIS NUMBER DEPENDING ON ITS SYMBOL
    {
        if(symbol1==1)//IF THE SYMBOL IS +
        {
            result=result+val;
		}
		else if(symbol1==-1)//IF THE SYMBOL IS -
		{
			result=result-val;
		}
	}
	else if (s==2)//OTHERWISE IF THE NUMBER OF CONSECUTIVE SYMBOLS IS EQUAL TO 2 THEN ASSIGN TO result THIS NUMBER DEPENDING ON ITS SYMBOLS  
	{
		if(symbol1==1 && symbol2==1)//IF THE FIRST SYMBOL IS + AND THE SECOND SYMBOL IS +
	    {
			result=result+val;
		}
	    else if (symbol1==-1 && symbol2==1)//IF THE FIRST SYMBOL IS - AND THE SECOND SYMBOL IS +
		{
			result=result-val;
		}
		else if(symbol1==1 && symbol2==-1)//IF THE FIRST SYMBOL IS + AND THE SECOND SYMBOL IS -
		{
			result=result-val;
		}
		else if (symbol1==-1 && symbol2==-1)//IF THE FIRST SYMBOL IS - AND THE SECOND SYMBOL IS -
		{
			result=result+val;
		}
	}
	return result;//RETURN THE RESULT 
}

int s5(int s,int symbol1,int symbol2,int val2)//THIS FUNCTION IS USED FOR CALCULATING NUMBERS THAT HAVE MULTIPLICATIONS IN THEIR EXPRESSION 
{
	int result2;
	result2=1;
	if(s==1 || s==0)//IF THE NUMBER OF CONSECUTIVE SYMBOLS IS ONE OR NONE THEN ASSIGN TO result THIS NUMBER DEPENDING ON ITS SYMBOL 
	{
		if(symbol1==1)//IF THE SYMBOL IS +
		{
			result2=result2*val2;
		}
		else if (symbol1==-1)//IF THE SYMBOL IS -
		{
			result2=-(result2*val2);
		}
	}
	else if (s==2)//OTHERWISE IF THE NUMBER OF CONSECUTIVE SYMBOLS IS EQUAL TO 2 THEN ASSIGN TO result THIS NUMBER DEPENDING ON ITS SYMBOLS
	{
		if(symbol1==1 && symbol2==1)//IF THE FIRST SYMBOL IS + AND THE SECOND SYMBOL IS +
		{
			result2=result2*val2;
		}
		else if (symbol1==-1 && symbol2==1)//IF THE FIRST SYMBOL IS - AND THE SECOND SYMBOL IS +
		{
			result2=-(result2*val2);
		}
		else if (symbol1==1 && symbol2==-1 )//IF THE FIRST SYMBOL IS + AND THE SECOND SYMBOL IS -
		{
			result2=-(result2*val2);
		}
		else if (symbol1==-1 && symbol2==-1)//IF THE FIRST SYMBOL IS - AND THE SECOND SYMBOL IS -
		{
			result2=result2*val2;
		}
	}
	return result2;//RETURN THE RESULT OF THE MULTIPLICATION 
}

int s6(int *x,int *d4)//THIS FUNCTION IS USED FOR THE CONVERSION OF ascii CHARACTERS TO DECIMAL FORM 
{
	T=1; //T IS USED TO KNOW IF THERE WERE NUMBERS IN THE EXPRESSION
	int d5,val;
	d5=0;
	val=0;
	while(*x>='0' && *x<='9')    //WHILE *x CONTAINS NUMBERS THAT CORRESPOND TO ascii CHARACTERS CONVERT THEM TO DECIMAL FORM   
    {                                  //AND CONTINUE WITH THE NEXT ONE IF IT IS A NUMBER THAT CORRESPONDS TO AN ascii CHARACTER 
                val=val*10+(*x-'0');   //"FORMULA" FOR CONVERTING ascii CHARACTERS TO DECIMAL FORM
				P=*x;      //P HOLDS THE PENULTIMATE CHARACTER UNLESS IT IS ' ' OR '\t'
                *x=getchar();
                *d4=1;
                while(*x==' ' || *x=='\t')     //IF NOW WE READ A NUMBER AND THEN WE READ THE SPACE OR '\t' AND AFTER THAT THERE IS A NUMBER THEN PRINT AN ERROR MESSAGE         
                {	                             //OTHERWISE RETURN THE VALUE OF THE NUMBER 
				   d5=1;						 
                   *x=getchar();
                }
                if(d5==1)
                {
                	if(*x>='0' && *x<='9')
                	{
					  f=1;                   
                	  printf("Unexpected character\n");
                	  val=0;
					  sum=0;
					  g=0;
					  return -1;
				    }
			    }	    
    }
    if(*x=='\n' && sum!=g) //IF NOW *x IS EQUAL TO '\n' AND THE NUMBER OF '(' IS DIFFERENT FROM THE NUMBER OF ')' THEN PRINT AN ERROR MESSAGE 
	{
	    	sum=0;
	    	g=0;
	    	f=1;
	    	val=0;
	    	printf("Missing closing parenthesis\n");
	    	return -1;
	}
    return val;
}

int s7(int *x)
{
	while(*x==' ' || *x=='\t')   //WHILE *x CONTAINS SPACE OR '\t' CHARACTERS READ THE NEXT CHARACTER EACH TIME UNTIL YOU FIND A CHARACTER DIFFERENT FROM THE SPACE OR THE '\t'
	{
		*x=getchar();
	}
}

int s8(int x)
{
	if(x=='\n')//IF NOW *x IS '\n' BUT THE PENULTIMATE CHARACTER IS '-' OR '+' OR '*' THEN DISPLAY AN ERROR MESSAGE   
	{
		if(P=='-' || P=='+' || P=='*')
		{
			printf("Unexpected end of input\n");
			P=0;
			f=1;
			return -1;
		}
	}
}

int main()
{
  int input,x,result,result2,result3,result4,val,val2,symbol1,symbol2,d1,d2,d3,d4,s,flag,flag2;       
  result=0;//result WILL HOLD THE VALUE OF THE EXPRESSION EACH TIME
  result2=1;//HOLDS THE RESULT OF THE MULTIPLICATION EACH TIME 							
  result3=0;//HOLDS THE RESULT OF THE PARENTHESIS IF THERE IS ONE 
  result4=0;
  val=0;//WILL HOLD THE DECIMAL VALUE FROM THE ascii CHARACTERS 									
  val2=0;//HOLDS THE VALUE OF THE MULTIPLICATION FROM THE CALL OF THE FUNCTION s3                            
  symbol1=1;//symbol1 AND symbol2 HOLD THE OPERATOR '+' OR '-'									
  symbol2=1;
  d1=0;//IS USED TO KNOW IF ACCEPTABLE CHARACTERS WERE USED IN THE EXPRESSION 
  d2=-1;//IS USED TO KNOW IF THERE WAS A MULTIPLICATION OPERATION IN THE EXPRESSION 
  d3=0;//IS USED SO THAT WE DO NOT SKIP THE CONSECUTIVE OPERATORS 
  d4=0;//IS USED TO KNOW THAT THE CONVERSION FROM ascii CHARACTERS TO DECIMAL VALUE HAPPENED 
  s=0;//HOLDS THE NUMBER OF CONSECUTIVE '+' OR '-'
  flag=0;//TELLS US IF THERE WAS A PARENTHESIS EXPRESSION 
  flag2=0;//IS USED SO THAT THE MESSAGE "Wrong character" IS PRINTED ONCE                 			
  input=getchar();									//A CHARACTER WILL BE ASSIGNED TO input EACH TIME 
  while (input!=EOF)
  {
  	    x=s1(input);                             //IF x IS EQUAL TO -1 THEN input CONTAINS A CHARACTER THAT IS NOT ACCEPTABLE OTHERWISE IT CONTAINS A  
        if(x==-1 && f==0)								//CORRECT CHARACTER 
        {		
           printf("Wrong character\n");					//IF x IS EQUAL TO -1 THEN PRINT THE MESSAGE ASSIGN -1 TO THE VARIABLE d1 WHICH WILL MEAN THAT THIS EXPRESSION 
           d1=-1;                               //CONTAINS UNACCEPTABLE CHARACTERS                    
           val=0;
		   flag2=1;							  
        }
		if(input=='(')//IF input IS EQUAL TO '(' THEN CALL s2 AND ASSIGN THE RESULT TO result3 
		{
			sum++;
		    flag=1;
			result3=s2(&input);
			while( input==')')//WHILE input IS EQUAL TO ')' READ THE NEXT CHARACTER 
			{
				g++;
				input=getchar();
			}
			if(d1==-1)//IF AN UNACCEPTABLE CHARACTER WAS READ READ ALL THE CHARACTERS UNTIL '\n'
			{
				
				while(input!='\n')
				{
				   input=getchar();
			    }
			    result3=0;
			    flag2=1;
			    sum=0;
			}	
		}
		input=s7(&input);
		if(input=='\n' && T==0)//IF input IS EQUAL TO '\n' AND NO NUMBER HAS BEEN READ THEN PRINT THE MESSAGE 
		{
			printf("Missing numders\n");
			f=1;
            symbol1=1;
			symbol2=1;		
		}	 	
        input=s7(&input);
        if (input=='+')         //IF THE CHARACTER WE READ IS '+' OR '-' THEN INCREASE s BY ONE 
		{   //THIS DECLARES THAT IF s IS EQUAL TO 1 WE ARE AT THE FIRST POSSIBLE CONSECUTIVE OPERATOR '+' OR '-' WHILE IF IT IS EQUAL TO 2 WE ARE AT THE SECOND CONSECUTIVE OPERATOR 
                s++;
                d3=1;//WE ASSIGN 1 TO d3 SO THAT WE DO NOT SKIP READING THE NEXT '+' OR '-'
                if(s==1)
                {//IF input CONTAINS THE ADDITION OPERATOR THEN ASSIGN 1 TO symbol1 OR TO symbol2 DEPENDING ON THE VALUE OF s OTHERWISE IF IT CONTAINS THE SUBTRACTION OPERATOR ASSIGN -1
                	symbol1=1;
				}
				else if(s==2)
				{
					symbol2=1;
				}
        }
        else if (input=='-')
        {
                s++;
                d3=1;
                if(s==1)
                {
                	symbol1=-1;
				}
				else if(s==2)
				{
					symbol2=-1;
				}
        }
        if(input>='0' && input<='9')//WHILE input CONTAINS NUMBERS THAT CORRESPOND TO ascii CHARACTERS CALL s6 AND ASSIGN THE RESULT TO val 
        {
        	val=s6(&input,&d4);
		}
        input=s7(&input);
        while  (input=='*')//IF input IS EQUAL TO '*' THEN ASSIGN 1 TO d2 AND CALL s3 TO CALCULATE THE RESULT OF THE MULTIPLICATION  
        {
        	d2=1;
        	val2=s3(&input);
        	if(d4==1)//IF WE READ A NUMBER BEFORE THEN MULTIPLY result2 BY THIS NUMBER 
        	{
        		result2=result2*val;
        		d4=0;
			}
			if(flag==1)//IF WE CALCULATED A PARENTHESIS EXPRESSION BEFORE THEN MULTIPLY result2 BY THIS EXPRESSION   
			{
				result2=result2*result3;
				result3=0;
				flag=0;
			}
			result4=s5(s,symbol1,symbol2,val2);//CALL s5 TO CALCULATE val2 AND MULTIPLY WITH result2
			result2=result2*result4;
			result4=0;
			s=0;
			symbol1=1;
			symbol2=1; 
        //	if(input=='(')//IF input IS EQUAL TO '(' CALL s2 AND ASSIGN THE RESULT OF THE PARENTHESIS TO result3
        //	{
        	//	sum++;
        	//	flag=1;
        	//	result3=s2(&input);
        	//	while(input==')')
        	//	{
        	//		g++;
        	//		input=getchar();
			//	}
		//	}
			if(flag==1)//IF WE CALCULATED A PARENTHESIS EXPRESSION BEFORE THEN MULTIPLY result2 BY THIS EXPRESSION AND ASSIGN TO result ITS OLD VALUE PLUS THE RESULT OF THE PRODUCT
			{
				result=result+result3*result2; 
				flag=0;
				result3=0;
				result2=1;
			}
		}
		if(d2==1)
		{
		   val=0;
		   s=0;
	    }
		if(d2==1 && d1==0)    		//THIS if WILL HAPPEN ONLY IF THIS EXPRESSION HAS MULTIPLICATION OPERATIONS AND THE CHARACTERS THAT WERE GIVEN WERE CORRECT 
		{                            
			result=result+result2;//ASSIGN TO THE VARIABLE result ITS OLD VALUE PLUS THE RESULT OF THE MULTIPLICATION THAT HAPPENED ABOVE 
			d2=-1;					//ASSIGN AGAIN THE VALUE -1 TO d1 AND AGAIN THE VALUE 1 TO result2 SO THAT NO ERROR HAPPENS IF WE HAVE AGAIN 
			result2=1;            //A MULTIPLICATION OPERATION
		}
		if(flag==1)//IF WE HAD A PARENTHESIS EXPRESSION THEN ASSIGN TO result ITS OLD VALUE PLUS THE RESULT OF THE PARENTHESIS 
     	{
			result=result+result3;
			flag=0;
			result3=0;	
		}
        if (val!=0 && d1==0)//IF A CONVERSION FROM ascii CHARACTERS TO DECIMAL FORM HAPPENED BEFORE CALL THE FUNCTION s4 TO CALCULATE THIS VALUE AND AS LONG AS THE CHARACTERS THAT WERE GIVEN WERE CORRECT 
        {
        	result4=s4(s,symbol1,symbol2,val);
        	result=result+result4;//ASSIGN TO result ITS OLD VALUE PLUS THE RESULT OF s4
        	result4=0;
			val=0;
			s=0;
			d3=0;
        }
        s8(input);//FUNCTION WHOSE ROLE IS TO DISPLAY ONE CATEGORY OF ERROR IF IT EXISTS INSIDE THE EXPRESSION 
        if (input=='\n'  && d1==0  && f==0 )    //IF input IS EQUAL TO enter AND THERE ARE NO ERRORS IN THE EXPRESSION DISPLAY THE RESULT OF THE EXPRESSION
        {
        	    sum=0;
        	    g=0;
                printf("result is %d\n",result); 
                result=0; 						
                symbol1=1;
				symbol2=1;
				s=0;
				d3=0;         
        }
        if(input=='\n')//IF AN ERROR WAS DETECTED IN THE EXPRESSION THEN TO PROCEED WITH THE NEW EXPRESSION WE MUST RESET ALL THESE VARIABLES 
        {	
           sum=0;
           g=0;
		   symbol1=1;
		   symbol2=1;					    
           val=0;
           d1=0;
           d4=0;
           flag2=0;
           f=0;
           result=0;
           T=0;
        }
        if(d3==0)//IF THE CHARACTER '+' OR '-' IS NOT CONSECUTIVE THEN THE COMMANDS BELOW ARE EXECUTED
        {
        	if(input=='+')
        	{
        		s++;
        		symbol1=1;
			}
			else if (input=='-')
			{
				s++;
				symbol1=-1;
			}
		}
        x=s1(input);       //CALL THE FUNCTION s1 TO SEE IF THE CHARACTER THAT WAS GIVEN IS ACCEPTABLE  
        if(x==-1 && flag2==0 && f==0 )         //IF IT IS NOT PRINT "Wrong character" AND ASSIGN -1 TO THE VARIABLE d1 WHICH WILL MEAN THAT THIS EXPRESSION CONTAINS UNACCEPTABLE CHARACTERS 
        {                    //ASSIGN ZERO TO result BECAUSE IT MAY CONTAIN VARIOUS RESULTS BEFORE THIS UNACCEPTABLE CHARACTER IS GIVEN 
                printf("Wrong character\n");//AND RESET val WHICH COULD HOLD THE VALUE OF A NUMBER BEFORE THE ASSIGNMENT OF THIS UNACCEPTABLE CHARACTER 
                d1=-1;
                result=0;
                val=0;      
        }
        P=input;
        input=getchar();   //ASSIGN THE NEW CHARACTER TO input 
   }
}

