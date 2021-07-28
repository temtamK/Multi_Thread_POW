#include "block.h"

void	block_init(t_block *block)
{
	block->nonce = -1;
	block->time = time(NULL);
}

int main()
{
	t_block block;

	block_init(&block);
	return (0);
}
