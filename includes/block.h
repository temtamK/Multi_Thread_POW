#ifndef BLOCK_H
# define BLOCK_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

typedef struct		s_block
{
	BYTE			prevHash[32];
	BYTE			hash[32];
	int32_t			version;
	time_t			time;
	uint32_t		bits;
	uint32_t		nonce;
	struct s_block	*next;
}					t_block;

BYTE		*ft_itoa_base(unsigned long long int n, char *base);
void		Genesis_block(t_block *block);
uint32_t	ft_atoi(unsigned char *s);
char		*ft_substr(unsigned char const *s, unsigned int start, size_t len);
uint32_t	ft_strtoui(unsigned char *hash);

#endif
