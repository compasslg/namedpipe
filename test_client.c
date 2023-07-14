#include "export.h"
#include <stdio.h>

int reader(HANDLE handle){
    char buffer[1024];
    while(read(handle, buffer, 1024) >= 0){
    }
}

int main(void){
    printf("start connecting taiwu pipe.\n");
    HANDLE handle = pipe_connect("taiwu", 5);
    printf("finish connecting taiwu pipe.\n");
    printf("connected.");

    pipe_close(handle);

    return 0;
}