// 判断以@为结束符的字符串是否回文
#include <iostream>
#include <cstring>

bool isPalindrome(const char* str) {
    if(str == nullptr || strlen(str) == 1) {
        return false; // 空指针或者空字符串不是回文
    }

    // 左右双指针法
    int left = 0;
    int right = strlen(str) - 2; // -2是为了跳过结尾的@符号

    // 比较左右两端的字符，逐渐向中间靠拢
    while(left < right) {
        if(str[left] != str[right]) {
            return false; // 发现不匹配直接返回false
        }
        left++;
        right--;
    }

    // 未发现不匹配的字符，说明是回文
    return true;
}

int testIsPalindrome() {
    const char* testStr1 = "bob@";
    const char* testStr2 = "hello@";
    const char* testStr3 = "@";

    // 测试回文函数
    std::cout << testStr1 << " " << (isPalindrome(testStr1) ? "Yes" : "No") << std::endl;
    std::cout << testStr2 << " " << (isPalindrome(testStr2) ? "Yes" : "No") << std::endl;
    std::cout << testStr3 << " " << (isPalindrome(testStr3) ? "Yes" : "No") << std::endl;

    return 0;
}