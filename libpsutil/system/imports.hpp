#pragma once

#include <stdarg.h>
#include <sys/prx.h>

extern "C"
{
	int	_sys_printf(const char* format, ...);
	int	_sys_sprintf(char* s, const char* format, ...);
	int	_sys_vsprintf(char* s, const char* format, va_list arg);

	void* _sys_malloc(size_t n);
	void _sys_free(void* ptr);
}

#define printf			_sys_printf
#define sprintf			_sys_sprintf
#define vsprintf		_sys_vsprintf