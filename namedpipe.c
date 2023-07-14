#include <stdio.h> 
#include <tchar.h>
#include "namedpipe.h"
#define MAX_PIPE_NAME_LENGTH 400
#define PIPE_NAME_BUFFER_SIZE 500
#define BUFFER_SIZE 1024 * 1024

void parse_pipe_name(const char* name, int name_length, char* dst_path){
    // check pipe name
    if(name_length > MAX_PIPE_NAME_LENGTH){
        printf("Pipe name should not be longer than 400 chars.");
        return;
    }

    strcpy(dst_path, "\\\\.\\pipe\\");
    int curr_length = strlen(dst_path);
    for(int i = 0; i < name_length; i++){
        int target_index = curr_length + i;
        dst_path[target_index] = name[i];
    }
    dst_path[curr_length + name_length] = '\0';
}

HANDLE create(char* name, int length){
    char pipe_name[PIPE_NAME_BUFFER_SIZE];
    parse_pipe_name(name, length, pipe_name);

    HANDLE handle = CreateNamedPipe(
        pipe_name, 
        PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE,// | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_BYTE,
        1,
        BUFFER_SIZE,
        BUFFER_SIZE,
        0,
        NULL);

    if(handle == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed, GLE=%d.\n", GetLastError()); 
        return NULL;
    }

    return handle;
}

HANDLE connect_as_client(char* name, int length){
    char pipe_name[PIPE_NAME_BUFFER_SIZE];
    parse_pipe_name(name, length, pipe_name);

    HANDLE handle = CreateFile(
        pipe_name,
        FILE_GENERIC_READ | FILE_GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0, //FILE_FLAG_OVERLAPPED,
        NULL);

    if(handle == INVALID_HANDLE_VALUE) {
        printf("Connect as client failed, GLE=%d.\n", GetLastError()); 
        return NULL;
    }

    return handle;
}

BOOL connect_as_server(HANDLE handle){
    //OVERLAPPED overlapped;
    int result = ConnectNamedPipe(handle, NULL);

    // Connection succeed
    if (result) 
    {
        return TRUE;
    }

    DWORD error = GetLastError();
    switch(error){
        // Client is already connected
        case ERROR_PIPE_CONNECTED:
            return TRUE;
        // The overlapped connection in progress
        case ERROR_IO_PENDING:
            DWORD num_of_bytes = 0;
            result = GetOverlappedResult(handle, NULL, &num_of_bytes, TRUE);
            if(result == 0){
                printf("GetOverlappedResult failed with %d.\n", GetLastError()); 
            }
            return result;
        default:
            printf("ConnectNamedPipe failed with %d.\n", error); 
            return FALSE;
    }
}

int write(HANDLE pipe_handle, void* ptr, int length){
    DWORD num_of_bytes = 0;
    //OVERLAPPED overlapped;
    BOOL succeed = WriteFile(pipe_handle, ptr, length, &num_of_bytes, NULL);
    if(!succeed){
        return -1;
    }
    return num_of_bytes;
}

int read(HANDLE pipe_handle, void* ptr, int length){
    DWORD num_of_bytes = 0;
    //OVERLAPPED overlapped;
    
    BOOL succeed = ReadFile(pipe_handle, ptr, length, &num_of_bytes, NULL);
    if(!succeed){
        return -1;
    }
    return num_of_bytes;
}
