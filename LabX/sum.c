#include <stdio.h>
#include <stdlib.h>

int  add(int *a , int *b , int*c ){
return *a + *b + *c ;
}


int main(){
int a , b , c , sum ; 

printf("Enter three integers: " );
scanf(" %d %d %d" , &a , &b , &c );

sum=add(&a,&b,&c);
printf("The sum is %d\n",sum);
 
return 0 ;
}
