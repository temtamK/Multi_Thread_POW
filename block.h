#ifndef BLOCK_H
# define BLOCK_H

#include <stdint.h>
#include <stdio.h>
#include <ctime>
#include "sha256.h"

typedef struct s_block
{
	char		prevHash[32];
	int32_t		version;
	time_t		time;
	uint32_t	nBits;
	uint32_t	nonce;
}				t_block;
