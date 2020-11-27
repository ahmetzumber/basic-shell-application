#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>

#define LENGTH 500 // bir satirda alabilecegimiz max karakter uzunlugu

int length(char *);
int input(char*);
void split(char*,char**);
int splitByPipe(char*,char**);
int hasPipe(char *);
void executeCommands(char **);

int main() {
    // girilen komut ve argumanlarinin atanacagi dizi
    char entered_command[500], *parsed_commands[LENGTH], *piped_commands[LENGTH];
    char *command0, *command1;
    while(1) {
        input(entered_command);                             // input methodu ile girilen argumanları al
        if (strcmp(entered_command,"exit") == 0) break;     // eger arguman exit ise bitir
        if (hasPipe(entered_command) == 0){                    
            splitByPipe(entered_command,parsed_commands);
            // first piped command row
            split(parsed_commands[0],piped_commands);       // pipedan onceki ilk komut 
            executeCommands(piped_commands);
            // second piped command row
            split(parsed_commands[1],piped_commands);       // pipedan sonraki komut
            executeCommands(piped_commands);                   
        }else{
            split(entered_command,parsed_commands);         // split methodu ile argumanları bosluga göre ayır ve tek tek 2.parametreye ata
            executeCommands(parsed_commands);
        }     
    }
    return 0;
}

int length(char *string){
    int i = 0;
    while(string[i] != '\0') i++;
    return i;
}

int input(char *text){
    wait(NULL); // input almadan duzgun bir sirada yazmasi icin beklet
    char* row;
    // readline ile komut alıyoruz
    row = readline("myshell>> "); 
    if (strlen(row) != 0) {
        // aldıgımız komutu fonksiyonun parametresine kopyalıyoruz
        strcpy(text, row);
        return 0;
    } else return 1;
}

void split(char* text, char** words){
    // ilk parametrede alinan string
    int i;
    for (i = 0; i < LENGTH; i++) {
        // strsep fonksiyonu ile parcalanıp words arrayine atanir
        words[i] = strsep(&text, " ");
        if (words[i] == NULL)
            break;
        if (strlen(words[i]) == 0)
            i--;
    }
}

int splitByPipe(char* commands, char** rows){
    int i;
    // 2 tane calistirilacak komut 
    for (i = 0; i < 2; i++) {
        rows[i] = strsep(&commands,"|");
        if (rows[i] == NULL) break;
    }

    if(rows[1] == NULL) 
        return 0;
    else 
        return 1;

}

int hasPipe(char *commands){
    // Verilen stringde | (pipe) var mi kontrolu
    int i;
    for (i = 0; i < LENGTH; i++){
        if (commands[i] == '|')
            return 0;
    }
    return 1;
}

void executeCommands(char **commands){
    wait(NULL); // input almadan duzgun bir sirada yazmasi icin beklet
    char *arguments[4];
    // max 4 arguman alacak
    arguments[0] = commands[1];
    arguments[1] = commands[2];
    arguments[2] = commands[3];
    arguments[3] = NULL; 
    int exe;
    pid_t f = fork();
    if (f < 0)                      // fork islemi gerceklesmediyse 
    	exit(EXIT_FAILURE);	
    else if (f == 0){
        // gelen parametrelerin clear ve cat komutlarına göre kontrolu
        if (strcmp(commands[0],"clear") == 0){    
            exe = execvp("clear", (char *const[]){"clear", NULL});
            perror("Eksik veya yanlis bir komut girdiniz. Tekrar deneyin.. \n"); 
        }else if (strcmp(commands[0],"cat") == 0){
            char *catArgs[2];           // cat icin verilen arguman dizisi 
            catArgs[0] = "/bin/cat";    // cat komutunun dosya yolu
            catArgs[1] = commands[1];   // yazdirilacak arguman
            catArgs[2] = NULL;
            printf("\n");
            exe = execv("/bin/cat",catArgs); 
            perror("Eksik veya yanlis bir komut girdiniz. Tekrar deneyin.. \n");
        }else{
            exe = execv(commands[0],arguments);   
            perror("Eksik veya yanlis bir komut girdiniz. Tekrar deneyin.. \n");
        } 
    }
}
