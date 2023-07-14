#include <windows.h>

HANDLE create(char* name, int length);
HANDLE connect_as_client(char* name, int length);
BOOL connect_as_server(HANDLE handle);

int read(HANDLE pipe_handle, void* ptr, int length);
int write(HANDLE pipe_handle, void* ptr, int length);
