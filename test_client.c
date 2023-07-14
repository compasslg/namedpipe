#include "export.h"
#include <stdio.h>

int main(void){
    printf("start connecting taiwu pipe.\n");
    HANDLE handle = pipe_connect("taiwu", 5);
    if(handle != NULL){
        printf("finish connecting taiwu pipe.\n");
        printf("connected.");
        pipe_close(handle);
    }
    return 0;
}