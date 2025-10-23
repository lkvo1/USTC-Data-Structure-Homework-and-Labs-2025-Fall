// 计算串s中不同字符的个数和每个字符的出现次数
#include <iostream>
#include <cstring>
#include <cstdint>

int main() {
    char* str = "Hello world!";
    if(str == nullptr) {
        std::cout << "The input string is null." << std::endl;
        return -1;
    }

    unsigned int CHAR_NUM = 256; // 对于ASCII字符集一共有256个字符，创建一个顺序表来存储每个字符的出现次数
    int charCount[CHAR_NUM] = {0}; // 初始化字符计数数组

    // 统计每个字符的出现次数
    for(int i = 0; i < strlen(str); ++i) {
        unsigned char ch = str[i];
        charCount[ch]++;
    }

    // 计算不同字符的个数
    int uniqueCharCount = 0;
    for(int i = 0; i < CHAR_NUM; ++i) {
        if(charCount[i] != 0) {
            uniqueCharCount++;
            std::cout << "Character '" << static_cast<char>(i) << "': " << charCount[i] << "." << std::endl;
        }
    }

    std::cout << "Total unique characters: " << uniqueCharCount << std::endl;

    return 0;
}