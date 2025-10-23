#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#define BLOCK_SIZE 8  // 每个块最多存储的字符串数量，可根据需要调整
#define STRING_LEN 64 // 每个字符串最大长度

typedef struct Block {
	char data[BLOCK_SIZE][STRING_LEN]; // 存储字符串
	int count; // 当前块中字符串数量
	struct Block* next;
} Block;

typedef struct BlockChain {
	Block* head;
	int size; // 总字符串数量
} BlockChain;

// 初始化块状链表
void initBlockChain(BlockChain* chain);

// 销毁块状链表
void destroyBlockChain(BlockChain* chain);

// 在指定位置插入字符串（0 <= pos <= size）
int insertBlockChain(BlockChain* chain, int pos, const char* str);

// 删除指定位置的字符串（0 <= pos < size）
int deleteBlockChain(BlockChain* chain, int pos);

// 获取指定位置的字符串，返回指向内部静态区的指针
const char* getBlockChain(BlockChain* chain, int pos);

// 打印所有字符串
void printBlockChain(const BlockChain* chain);

#endif // BLOCKCHAIN_H
