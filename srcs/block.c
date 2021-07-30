#include "block.h"

// 첫번째 블록(genesis block)은 미리 값을 정해놓았습니다.
void	Genesis_block(t_block *block)
{
	block->version = 0;
	block->nonce = 0;
	block->time = time(NULL);
	memcpy(block->prevHash, "0", 33);
	memcpy(block->hash, "850E4A0349DD04432EDB4A9E264D19A50C135998DE27B62DF49BA69999A11E65", 33);
	block->bits = 0x1d00ffff;
}
