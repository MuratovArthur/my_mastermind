#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);     
    char* code;
    int attempts=10;
    int code_passed_flag=0;
    for(int i=1; i<argc; i++){
        if (strcmp(argv[i], "-c") == 0){
            if(i+1<argc){
                code = argv[i+1];
                code_passed_flag=1;
            }else{
                return 0;
            }
        }
        if (strcmp(argv[i], "-t") == 0 && i+1<=argc){
             if(i+1<argc){
                attempts = atoi(argv[i+1]);
             }else{
                 return 0;
             }
            
        }
    }
    if(argc<=1||code_passed_flag==0){
        return 0;
    }
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    int rounds=0;
    printf("---\n");
    printf("Round %d\n>", rounds);
    char guess[100];
    char ch;
    int flag_digit=0;
    while(rounds<attempts){
        int n=0;
        while(read(0, &ch, 1)>0&&ch!='\n'){
            guess[n] = ch;
            n++;
        }
        guess[n]='\0';
        for(int i=0;i<strlen(guess)-1;i++){
            if(isdigit(guess[i])==0){
                flag_digit=0;
                break;
            }else{
                flag_digit=1;
            } 
        }
        if(flag_digit==0||strlen(guess)!=4){
            printf("Wrong input!\n");
            printf(">");
        }else{
            rounds++;
            if(strcmp(guess, code)==0){
                printf("Congratz! You did it!\n");
                return 0;
            }else{
                int correctly_placed=0;
                int misplaced=0;
                for(int i=0; i<strlen(guess);i++){
                    for(int j=0; j<strlen(code); j++){
                        if(guess[i]==code[j]){
                            if(i==j){
                                correctly_placed++;
                            }else{
                                misplaced++;
                            }
                        }
                    }
                }
                printf("Well placed pieces: %d\n", correctly_placed);
                printf("Misplaced pieces: %d\n", misplaced);
                if(rounds<attempts){
                    printf("---\n");
                    printf("Round %d\n>", rounds);
                }
            }
        }
    }
}