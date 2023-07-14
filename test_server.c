#include "export.h"
#include <stdio.h>

int main(void){
    printf("start creating taiwu pipe.\n");
    HANDLE handle = pipe_create("taiwu", 5);
    if(handle == NULL) return 0;

    printf("finish creating taiwu pipe.\n");
    if(pipe_wait(handle)){
        printf("connected.");
    }

    pipe_close(handle);

    return 0;
}