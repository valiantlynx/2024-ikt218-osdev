#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list;

#define va_start(ap, v) (ap = (va_list) & v + sizeof(v))
#define va_arg(ap, type) (*(type *)((ap += sizeof(type)) - sizeof(type)))
#define va_end(ap) (ap = (va_list)0)

#endif // _STDARG_H
