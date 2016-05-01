#ifndef JADE_H
#define JADE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned char* jade_compile(unsigned char *src, unsigned *len);

#ifdef __cplusplus
}
#endif

#endif
