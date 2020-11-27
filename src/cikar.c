#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num1, num2, result;
    num1 = atoi(argv[0]);
    num2 = atoi(argv[1]);

    // Girilen 2 parametreden hangisi buyukse cıkarma islemi ona göre yapılır
    if(num2 > num1){
        result = num2 - num1;
        printf("%d - %d = %d \n",num2,num1,result);
    }else{
        result = num1 - num2;
        printf("%d - %d = %d \n",num1,num2,result);
    }
    return 0;
}
