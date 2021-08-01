#include "block.h"

void	Get_target(uint32_t bits, BYTE target[])
{
	int			i, count;
	int 		exponent;
	BYTE 		*coef;

	i = 0;
	count = 0;
	/*
	** Ÿ�ٰ��� ã�� ���� bits�� �̿��մϴ�.
	** bits�� �̿��ؼ� ������ ����� ������ �˴ϴ�.
	** ex) bits = 0x1d00ffff
	** ���� = 0x1d, ��� = 00ffff
	*/

	// ����Ʈ ������ ���� ������ ���մϴ�.
	exponent = bits >> 24;
	coef = ft_itoa_base(bits, "0123456789abcdef");
	// ��ȿ�� �տ� 0�� �󸶳� ������ ���մϴ�.
	// 0�� ���� ���� ���� ���̵��� �������ϴ�.
	while (i < 32 - (exponent + 1))
		i++;
	while (count < 3)
	{
		if (coef == NULL)
			break;
		coef += 2;
		if (strcmp(ft_substr(coef, 0, 2), "00") == 0)
			coef += 2;
		// 8bit�� ��� Ÿ�ٰ��� �ֽ��ϴ�.
		sscanf((char *)coef, "%2hhx", &target[i]);
		i++;
		count++;
	}
}

BYTE	*Conv_sha256(BYTE *seed)
{
	static BYTE dest[32];
	BYTE		tmp[32];
	SHA256_CTX	ctx;

	// �õ尪�� �̿��Ͽ� sha256 �ؽð��� ���մϴ�.
	sha256_init(&ctx);
	sha256_update(&ctx, seed, 40);
	sha256_final(&ctx, tmp);

	// ������ ���� �ؽð��� �ѹ� �� ��ȯ�մϴ�.
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

	// ���� ���� ã�� ���� �õ尪�� �����մϴ�.
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
	// ���� ���� sha256 �ؽð����� ��ȯ�մϴ�.
	ret = Conv_sha256(src);
	return (ret);
}

void	Mining(t_block *block)
{
	t_block		nBlock;
	BYTE		target[32] = {0, };
	BYTE		*hash;

	int i;

	i = 0;
	nBlock = (t_block){0};
	// Ÿ�� �ؽð��� ���ϴ� �Լ��Դϴ�.
	Get_target(block->bits, target);
	// Ÿ�ٺ��� ���� �ؽð��� ���ϴ� �Լ��Դϴ�.
	hash = Get_hash(block->nonce);
	printf("target = ");
	while (i < 32)
	{
		printf("%x", target[i]);
		i++;
	}
	printf("\n");
	// ã�� �ؽð��� Ÿ�ٰ����� ������ ���մϴ�.
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

	// �ؽð��� ã���� �� ���� ���ο� ����� �ؽð����� ����մϴ�.
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
	// ù��° ����� �����մϴ�.
	Genesis_block(&block);
	while (num_block < 11)
	{
		start_time = time(0);
		printf("block is %d\n", block.nonce);
		Mining(&block);
		block.nonce++;
		printf("block has been mining\n");
		end_time = time(0);
		block.time = end_time;
		printf("time = %s\n", ctime(&block.time));
		speding_time = end_time - start_time;
		// ����� ä���Ǹ� ���̵��� ����˴ϴ�.
		block.bits = block.bits - ((speding_time + block.nonce * 24) / (block.nonce + 1));
		printf("bits = %x\n", block.bits);
		num_block++;
		printf("\n");
	}
	return (0);
}
