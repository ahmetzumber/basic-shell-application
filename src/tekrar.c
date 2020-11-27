#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // gelen ilk parametre ekrana yazdirilacak 
    // ikinci parametre ise tekrar adedi
    int i;
    for (i = 0; i < atoi(argv[1]); i++) {
        printf("%s \n",argv[0]);
    }
    return 0;
}
