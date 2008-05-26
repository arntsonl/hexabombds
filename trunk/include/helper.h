#pragma once

#define FIXED_16(x) (x*0xFFFF)

#define UINT_16(x) (x>>16)

#define MAX_NODE_CONNECTIONS 16
#define MAX_STATE_NODES		 128
#define MAX_NAME_LENGTH		 64

#define DEFAULT_FRICTION	 0.2

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;

typedef signed char	s8;
typedef signed short	s16;
typedef signed long	s32;

