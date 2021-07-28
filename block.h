#ifndef BLOCK_H
# define BLOCK_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "sha256.h"

typedef struct s_block
{
	char		prevHash[32];
	char		Hash[32];
	int32_t		version;
	time_t		time;
	uint32_t	nBits;
	uint32_t	nonce;
	t_block		next;
}				t_block;
