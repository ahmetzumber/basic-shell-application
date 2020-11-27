#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNumber(char *text){
    int j;
    j = strlen(text);
    while(j--){
        // girilen textin her karakteri tek tek kontrol ediliyor sayi mi diye
        if(text[j] >= '0' && text[j] <= '9')
            continue;
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
    // islem komutu haric 3 arguman daha alacak
    char *arguments[3];
    int i;
    // eger topla ya da cikardan sonraki parametreler sayi mi kontrolu
    if (isNumber(argv[1]) == 0 || isNumber(argv[2]) == 0){
        perror("Lutfen bu islem icin sayi giriniz !\n"); 
    }else {
        arguments[0] = argv[1];
        arguments[1] = argv[2];
        arguments[2] = NULL;
        
        pid_t f = fork();

        if (f < 0)  // fork islemi gerceklesmediyse
            exit(EXIT_FAILURE);	
        else if (f == 0){   
            i = execv(argv[0],arguments);
            perror("Gecersiz bir parametre girdiniz.. Tekrar deneyin..\n");
        }
        wait(&i); 
    }   
    return 0;
}
