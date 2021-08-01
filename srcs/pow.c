#include "block.h"

BYTE	*Get_target(uint32_t bits)
{
	int			i, count;
	int 		exponent;
	BYTE 		*coef;
	static BYTE target[32] = {0, };

	i = 0;
	count = 0;
	/*
	** 타겟값을 찾을 때는 bits를 이용합니다.
	** bits를 이용해서 지수와 계수로 나뉘게 됩니다.
	** ex) bits = 0x1d00ffff
	** 지수 = 0x1d, 계수 = 00ffff
	*/

	// 쉬프트 연산을 통해 지수를 구합니다.
	exponent = bits >> 24;
	coef = ft_itoa_base(bits, "0123456789abcdef");
	// 유효값 앞에 0을 얼마나 넣을지 정합니다.
	// 0을 적게 넣을 수록 난이도가 쉬워집니다.
	while (i < 32 - (exponent + 1))
		i++;
	while (count < 3)
	{
		if (coef == NULL)
			break;
		coef += 2;
		if (strcmp(ft_substr(coef, 0, 2), "00") == 0)
			coef += 2;
		// 8bit씩 끊어서 타겟값에 넣습니다.
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

	// 시드값을 이용하여 sha256 해시값을 구합니다.
	sha256_init(&ctx);
	sha256_update(&ctx, seed, 40);
	sha256_final(&ctx, tmp);

	// 위에서 얻은 해시값을 한번 더 변환합니다.
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

	// 랜덤 값을 찾기 위한 시드값을 설정합니다.
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
	// 랜덤 값을 sha256 해시값으로 변환합니다.
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
	// 타겟 해시값을 구하는 함수입니다.
	target = Get_target(block->bits);
	// 타겟보다 작은 해시값을 구하는 함수입니다.
	hash = Get_hash(block->nonce);
	printf("target = ");
	while (i < 32)
	{
		printf("%x", target[i]);
		i++;
	}
	printf("\n");
	// 찾은 해시값이 타겟값보다 작은지 비교합니다.
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

	// 해시값을 찾으면 그 값을 새로운 블록의 해시값으로 등록합니다.
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
	// 첫번째 블록을 생성합니다.
	Genesis_block(&block);
	while (num_block < 11)
	{
		start_time = time(0);
		printf("block is %d\n", num_block);
		Mining(&block);
		block.nonce++;
		printf("block has been mining\n");
		end_time = time(0);
		block.time = end_time;
		printf("time = %s\n", ctime(&block.time));
		speding_time = end_time - start_time;
		// 블록이 채굴되면 난이도가 변경됩니다.
		block.bits = block.bits * (1 * speding_time + block.nonce);
		num_block++;
		printf("\n");
	}
	return (0);
}
