#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 定长顺序表表示的字符串s和t，求s和t中的所有最长公共子串

// 寻找所有最长公共子串
vector<string> findLongestCommonSubstrings(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // dp[i][j]表示str1前i个字符和str2前j个字符的最长公共子串长度
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    int max = 0;  // 最长公共子串的长度
    vector<string> result; // 存储所有最长公共子串
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                // 如果发现有新的匹配字符，就加一
                dp[i][j] = dp[i-1][j-1] + 1;

                // 判断dp[i][j]是否最长，如果最长的话就更新max和结果集
                if (dp[i][j] > max) {
                    max = dp[i][j];
                    result.clear();
                    result.push_back(str1.substr(i - max, max));
                }
                // 如果发现长度等于最大长度，说明发现了多个公共最长子串
                else if (dp[i][j] == max && max > 0) {
                    result.push_back(str1.substr(i - max, max));
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    return result;
}

int main() {
    // 输入两个字符串测试
    string str1, str2;
    cin >> str1 >> str2;
    cout << "str1 = \"" << str1 << "\"\n";
    cout << "str2 = \"" << str2 << "\"\n";

    vector<string> longestCommonSubstrings = findLongestCommonSubstrings(str1, str2);
    cout << "All Longest Common Substrings:\n";
    cout << "Num: " << longestCommonSubstrings.size() << "\n";
    for (int i = 0; i < longestCommonSubstrings.size(); i++) {
        cout << longestCommonSubstrings[i] << "\n";
    }
    
    return 0;
}


