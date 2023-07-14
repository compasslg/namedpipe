#include "export.h"

EXPORT void* pipe_create(char* name, int length){
    HANDLE handle = create(name, length);
    return handle;
}

EXPORT BOOL pipe_wait(void* pipe_handle){
    return connect_as_server(pipe_handle);
}

EXPORT void* pipe_connect(char* name, int length){
    HANDLE handle = connect_as_client(name, length);
    return handle;
}

EXPORT int pipe_close(void* pipe_handle){
    return CloseHandle(pipe_handle);
}

EXPORT int pipe_write(void* pipe_handle, void* ptr, int length){
    return write(pipe_handle, ptr, length);
}

EXPORT int pipe_read(void* pipe_handle, void* ptr, int length){
    return read(pipe_handle, ptr, length);
}

EXPORT int pipe_flush(void* pipe_handle){
    return FlushFileBuffers(pipe_handle);
}