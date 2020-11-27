#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num1, num2;
    num1 = atoi(argv[0]);
    num2 = atoi(argv[1]);
    int result = num1 + num2;
    printf("%d + %d = %d \n",num1,num2,result);
    return 0;
}


