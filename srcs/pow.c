#include "block.h"

BYTE	*Get_target(uint32_t bits)
{
	int i, count;
	int exponent;
	BYTE *coef;
	static BYTE target[32] = {0, };

	i = 0;
	count = 0;
	exponent = bits >> 24;
	coef = ft_itoa_base(bits, "0123456789abcdef");
	while (i < 32 - (exponent + 1))
		i++;
	while (count < 3)
	{
		if (coef == NULL)
			break;
		coef += 2;
		if (strcmp(ft_substr(coef, 0, 2), "00") == 0)
			coef += 2;
		sscanf((char *)coef, "%2hhx", &target[i]);
		i++;
		count++;
	}
	return (target);
}

BYTE	*Conv_sha256(BYTE *seed)
{
	static BYTE dest[32];
	BYTE		tmp[32];
	SHA256_CTX	ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, seed, 40);
	sha256_final(&ctx, tmp);

	sha256_init(&ctx);
	sha256_update(&ctx, tmp, 32);
	sha256_final(&ctx, dest);

	return (dest);
}

BYTE	*Get_hash(uint32_t nonce)
{
	uint32_t	seed[2];
	uint32_t	x;
	uint32_t	y;
	BYTE		*src;
	static BYTE	*ret;

	srand(time(NULL));
	seed[0] = rand() + nonce;
	srand(time(NULL));
	seed[1] = rand() * nonce + 4;

	x = seed[0];
	y = seed[1];
	seed[0] = y;
	x ^= x << 23;
	seed[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	src = ft_itoa_base(seed[1] - y, "0123456789abcdef");
	ret = Conv_sha256(src);
	return (ret);
}

void	Mining(t_block *block)
{
	t_block		nBlock;
	BYTE		*target;
	BYTE		*hash;
	int i;

	i = 0;
	nBlock = (t_block){0};
	target = Get_target(block->bits);
	hash = Get_hash(block->nonce);
	printf("target = ");
	while (i < 32)
	{
		printf("%x", target[i]);
		i++;
	}
	printf("\n");
	while (sha256_compare(hash, target) != -1)
		hash = Get_hash(block->nonce);
	i = 0;
	printf("hash = ");
	while (i < 32)
	{
		printf("%x", hash[i]);
		i++;
	}
	printf("\n");
	memcpy(&nBlock, block, sizeof(t_block));
	memcpy(nBlock.prevHash, block->hash, 33);
	memcpy(nBlock.hash, hash, 33);
	block->next = &nBlock;
	block = block->next;
}

int 	main()
{
	t_block		block;
	int			num_block;
	int			start_time;
	int			end_time;
	int			speding_time;

	num_block = 1;
	Genesis_block(&block);
	while (num_block < 11)
	{
		start_time = time(0);
		printf("block is %d\n", num_block);
		Mining(&block);
		block.nonce++;
		printf("block has been mining\n");
		end_time = time(0);
		speding_time = end_time - start_time;
		block.bits = block.bits * (1 * speding_time + block.nonce);
		num_block++;
		printf("\n");
	}
	return (0);
}
