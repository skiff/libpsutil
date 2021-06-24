#include "system/imports.hpp"

void* operator new(size_t size) { return _sys_malloc(size); }
void* operator new[](size_t size) { return _sys_malloc(size); }
void* operator new(unsigned int size, unsigned int) { return _sys_malloc(size); }
void operator delete(void* ptr) { _sys_free(ptr); }
void operator delete[](void* ptr) { _sys_free(ptr); }