#include "namedpipe.h"
#define EXPORT __declspec(dllexport)

EXPORT void* pipe_create(char* name, int length);
EXPORT BOOL pipe_wait(void* pipe_handle);
EXPORT void* pipe_connect(char* name, int length);
EXPORT int pipe_close(void* pipe_handle);
EXPORT int pipe_write(void* pipe_handle, void* ptr, int length);
EXPORT int pipe_read(void* pipe_handle, void* ptr, int length);
EXPORT int pipe_flush(void* pipe_handle);
