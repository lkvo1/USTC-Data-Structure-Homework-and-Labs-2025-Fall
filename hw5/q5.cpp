// 计算串s中不同字符的个数和每个字符的出现次数
#include <iostream>
#include <cstring>

int main() {
    const char* str = "hello world";
    if(str == nullptr) {
        std::cout << "Input string is null." << std::endl;
        return -1;
    }

    const int CHAR_RANGE = 256; // 假设字符集为ASCII
    int charCount[CHAR_RANGE] = {0}; // 初始化字符计数数组

    // 统计每个字符的出现次数
    for(int i = 0; i < strlen(str); ++i) {
        unsigned char ch = str[i]; // 使用unsigned char以避免负值索引
        charCount[ch]++;
    }

    // 计算不同字符的个数
    int uniqueCharCount = 0;
    for(int i = 0; i < CHAR_RANGE; ++i) {
        if(charCount[i] > 0) {
            uniqueCharCount++;
            std::cout << "Character '" << static_cast<char>(i) << "' occurs " << charCount[i] << " times." << std::endl;
        }
    }

    std::cout << "Total unique characters: " << uniqueCharCount << std::endl;

    return 0;
}