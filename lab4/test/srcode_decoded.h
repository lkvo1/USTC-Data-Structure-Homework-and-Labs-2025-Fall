#ifndef HUFFMAN_SYSTEM_H
#define HUFFMAN_SYSTEM_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

// 哈夫曼节点的结构体
typedef struct HNode {
    unsigned int weight; // 权重
    unsigned char data; // 字符
    HNode* left;
    HNode* right;

    HNode() : weight(0), data(0), left(nullptr), right(nullptr) {}
    HNode(unsigned int w, unsigned char d) : weight(w), data(d), left(nullptr), right(nullptr) {}
} HNode;

class HuffmanSystem {
private:
    unsigned int frequencyTable[256]; // 频率表 frequencyTable[i] = 字符char(i)的频率
    HNode* huffmanTreeRoot; // 哈夫曼树根节点
    std::vector<bool> huffmanCodeTable[256]; // 哈夫曼编码表 huffmanCodeTable[i] = 字符char(i)的哈夫曼编码
    std::stringstream huffmanCodes;

    void generateFrequencyTable(std::stringstream& ss); // 根据输入流生成频率表
    void buildHuffmanTree(); // 构建哈夫曼树
    void generateHuffmanCodesTable(); // 生成哈夫曼编码表
    void dfs(HNode* node, std::vector<bool>& code); // 生成哈夫曼编码表的辅助函数，深度优先遍历哈夫曼树
    void generateHuffmanCodes(std::stringstream& ss);    // 根据编码表生成哈夫曼比特流
    void printFrequencyTable();
    
public:
    HuffmanSystem();
    ~HuffmanSystem();
    void run(); // 运行系统
    void encode(std::string& srcFilePath, std::string& dstFilePath);  // 编码任意文件
    void decode(std::string& srcFilePath, std::string& dstFilePath);  // 解码任意文件
    void displayMenu(); // 显示操作菜单
    void handleUserInput(std::stringstream& ss);    // 解析用户指令
    void saveToFile(std::stringstream& ss, std::string& filePath);  // 保存编码结果到文件
};

void HuffmanSystem::printFrequencyTable() {
    for (int i = 0; i < 256; i++) {
        std::cout << (char)i << '=' << frequencyTable[i] << ' ';
    }
    std::cout << "==================================" << std::endl;
}

void HuffmanSystem::generateHuffmanCodes(std::stringstream& ss) {
    std::cout << "Generating Huffman Codes Stream..." << std::endl;
    // 清空之前的内容
    huffmanCodes.str("");
    huffmanCodes.clear();
    
    // 每8位为一个字节,以unsinged char的形式读取
    unsigned char ch;
    while (ss.read(reinterpret_cast<char*>(&ch), 1)) {
        // 对于每个字节,查找对应的Huffman编码,然后按位写入huffmanCodes流中
        std::vector<bool>& code = huffmanCodeTable[ch];
        for (bool bit : code) {
            // 将布尔值转换为字符'0'或'1'
            huffmanCodes << (bit ? '1' : '0');
        }
    }
    std::cout << "Huffman Codes Stream generate complete." << std::endl;
}

void HuffmanSystem::generateFrequencyTable(std::stringstream& ss) {
    std::cout << "Generating frequency table..." << std::endl;
    // 每8位为一个字节，以unsinged char的形式读取
    unsigned char ch;
    while (ss.read(reinterpret_cast<char*>(&ch), 1)) {
        frequencyTable[ch]++;
    }
    // while (ss.read((char*)(&ch), 1)) {}
    std::cout << "Frequency table generate complete." << std::endl;
    
    // printFrequencyTable();
}

void HuffmanSystem::buildHuffmanTree() {
    std::cout << "Building Huffman Tree..." << std::endl;
    HNode* hnodes[256];
    // 每个字符创建一个节点，并按频率排序
    for (int i = 0; i < 256; i++) {
        hnodes[i] = new HNode(frequencyTable[i], (unsigned char)i);
    }

    // 然后按照weight从小到大排序 冒泡排序
    for (int i = 0; i < 256 - 1; i++) {
        for (int j = 0; j < 256 - i - 1; j++) {
            if (hnodes[j]->weight > hnodes[j + 1]->weight) {
                HNode* temp = hnodes[j];
                hnodes[j] = hnodes[j + 1];
                hnodes[j + 1] = temp;
            }
        }
    }

    // 开始构建Huffman Tree
    for (int i = 0; i < 256 - 1; i++) {
        // 合并前两个节点
        HNode* merge = new HNode(hnodes[i]->weight + hnodes[i + 1]->weight, 0);
        merge->left = hnodes[i];
        merge->right = hnodes[i + 1];
        hnodes[i + 1] = merge;

        // 将合并后的节点放到第一个位置然后将合并后的节点排序到合适的位置，使得hnodes数组依然有序
        for (int j = i + 1; j < 256 - 1; j++) {
            if (hnodes[j]->weight > hnodes[j + 1]->weight) {
                HNode* temp = hnodes[j];
                hnodes[j] = hnodes[j + 1];
                hnodes[j + 1] = temp;
            } else {
                break;
            }
        }
    }
    // 最后剩下一个节点，即为Huffman Tree的根节点
    huffmanTreeRoot = hnodes[255];
    std::cout << "Huffman Tree build complete." << std::endl;
}

void HuffmanSystem::generateHuffmanCodesTable() {
    std::cout << "Generating Huffman Codes..." << std::endl;

    std::vector<bool> code;
    dfs(huffmanTreeRoot, code);
    
    std::cout << "Huffman Codes generate complete." << std::endl;
}

void HuffmanSystem::dfs(HNode* node, std::vector<bool>& code) {
    // 递归遍历Huffman Tree生成Huffman编码，对于每个节点，如果已经到达叶子节点，则将当前编码存入huffmanCodes中，向左走添加'0'，向右走添加'1'
    if (!node->left && !node->right) {  // 到达叶子节点
        huffmanCodeTable[node->data] = code;
        return;
    }

    // 0 表示向左走
    code.push_back(false);
    dfs(node->left, code);
    code.pop_back();

    // 1 表示向右走
    code.push_back(true);
    dfs(node->right, code);
    code.pop_back();
}

void HuffmanSystem::encode(std::string& srcFilePath, std::string& dstFilePath) {
    if (srcFilePath.empty()) { std::cout << "Error: Source file path is empty." << std::endl; return; }
    std::cout << "Encoding file: " << srcFilePath << std::endl;
    std::ifstream inFile(srcFilePath, std::ios::binary);   // 以二进制方式打开文件
    if (!inFile) { std::cout << "Error: Unable to open source file." << std::endl; return; }

    std::stringstream ss;   
    ss << inFile.rdbuf();   // 存入inFile的内容到ss中
    generateFrequencyTable(ss); // 再将ss传入generateFrequencyTable中生成频率表

    buildHuffmanTree(); // 然后根据频率表和节点生成Huffman树

    generateHuffmanCodesTable(); // 根据Huffman树生成对应的Huffman编码表

    ss.clear(); // 清除流状态
    ss.seekg(0, std::ios::beg); // 指针回到流开头
    generateHuffmanCodes(ss); // 根据编码表生成哈夫曼比特流

    saveToFile(huffmanCodes, dstFilePath);   // 最后存到对应的目标文件*.huff中

    std::cout << "Encoding completed." << std::endl;
}

void HuffmanSystem::decode(std::string& srcFilePath, std::string& dstFilePath) {
    if (dstFilePath.empty())  {
        std::cout << "Error: Source file path is empty." << std::endl;
        return;
    }

    // .huff文件结构: 频率表 256 * sizeof(unsigned int) bytes + 比特流长度(N) sizeof(unsigned int) bits + 比特流内容 N bytes
    std::cout << "Decoding file: " << dstFilePath << std::endl;
    // 读取huff文件
    std::ifstream inFile(srcFilePath, std::ios::binary);
    if (!inFile) { std::cout << "Error: Unable to open source file." << std::endl; return; }
    // 读取频率表
    for (int i = 0; i < 256; i++) {
        inFile.read(reinterpret_cast<char*>(&frequencyTable[i]), sizeof(unsigned int));
    }

    // 构建Huffman树和编码表
    buildHuffmanTree();
    generateHuffmanCodesTable();

    // 读取比特流长度
    unsigned int bitLength = 0;
    inFile.read(reinterpret_cast<char*>(&bitLength), sizeof(unsigned int));

    // 读取比特流内容
    std::string bitStream;
    unsigned char byte;
    for (unsigned int i = 0; i < bitLength / 8; i++) {
        inFile.read(reinterpret_cast<char*>(&byte), 1);
        for (int j = 7; j >= 0; j--) {
                bitStream += ((byte >> j) & 1) ? '1' : '0';
        }
    }
    // 处理最后一个字节(如果有剩余位)
    if (bitLength % 8 != 0) {
        inFile.read(reinterpret_cast<char*>(&byte), 1);
        for (int j = 7; j >= 8 - (bitLength % 8); j--) {
            bitStream += ((byte >> j) & 1) ? '1' : '0';
        }
    }

    // 根据比特流解码
    std::ofstream outFile(dstFilePath, std::ios::binary);
    if (!outFile) { std::cout << "Error: Destination file " << dstFilePath << " couldn't be opened." << std::endl; return; }

    HNode* node = huffmanTreeRoot;
    for (char bit : bitStream) {
        if (bit == '0') {
            node = node->left;
        } else {
            node = node->right;
        }
        // 到达叶子节点，输出字符
        if (!node->left && !node->right) {
            outFile.write(reinterpret_cast<char*>(&node->data), 1);
            node = huffmanTreeRoot;
        }
    }
    outFile.close();
    std::cout << "Decoding completed." << std::endl;
}

void HuffmanSystem::saveToFile(std::stringstream& ss, std::string& filePath) {
    if (filePath.empty())  {
        std::cout << "Error: Destination file path is empty." << std::endl;
        return;
    }

    std::cout << "Saving to file: " << filePath << std::endl;
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        std::cout << "Error: Destination file " << filePath << " couldn't be opened." << std::endl;
        return;
    }

    // 先写入频率表用于解码
    for (int i = 0; i < 256; i++) {
        outFile.write(reinterpret_cast<char*>(&frequencyTable[i]), sizeof(unsigned int));
    }

    // 获取比特流字符串
    std::string bitStream = ss.str();
    unsigned int bitLength = bitStream.length();
    
    // 写入比特流的长度
    outFile.write(reinterpret_cast<char*>(&bitLength), sizeof(unsigned int));

    // 4. 将比特流(字符01)转换为字节并写入
    unsigned char currentByte = 0;
    int bitCount = 0;
    
    for (char bit : bitStream) {
        currentByte <<= 1;
        if (bit == '1') {
            currentByte |= 1;
        }
        bitCount++;
        
        if (bitCount == 8) {
            outFile.write(reinterpret_cast<char*>(&currentByte), 1);
            currentByte = 0;
            bitCount = 0;
        }
    }
    
    // 如果还有剩余的位,补齐到8位后写入
    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);
        outFile.write(reinterpret_cast<char*>(&currentByte), 1);
    }

    outFile.close();

    std::cout << "Save completed. Total bits: " << bitLength << std::endl;
}

HuffmanSystem::HuffmanSystem() {
    // 初始化哈夫曼编码流
    huffmanCodes.str("");
    huffmanCodes.clear();

    // 初始化频率表
    for (int i = 0; i < 256; ++i) {
        frequencyTable[i] = 0;
    }

    // 初始化哈夫曼树根节点
    huffmanTreeRoot = new HNode();
}

HuffmanSystem::~HuffmanSystem() {}

void HuffmanSystem::displayMenu() {
    std::cout << "===== Huffman Coding System =====" << std::endl;
    std::cout << "Commands Format: <command> <src_file_path> <dst_file_path>" << std::endl;
    std::cout << "Available Commands: encode, decode, exit." << std::endl;
    std::cout << "Example: encode src.txt dst.huff" << std::endl;
    std::cout << "==================================" << std::endl;
}

void HuffmanSystem::handleUserInput(std::stringstream& ss) {
    std::string command, srcFilePath, dstFilePath;
    ss >> command >> srcFilePath >> dstFilePath;

    if (command == "encode") {
        encode(srcFilePath, dstFilePath);
    } else if (command == "decode") {
        decode(srcFilePath, dstFilePath);
    } else if (command == "exit") {
        std::cout << "Exiting Huffman Coding System." << std::endl;
        exit(0);
    } else {
        std::cout << "Invalid command. Please try again." << std::endl;
    }
}

void HuffmanSystem::run() {
    displayMenu();
    // 主循环
    while (true) {
        std::cout << '>';
        std::stringstream ss;
        std::string userInput;
        std::getline(std::cin, userInput);
        ss << userInput;
        handleUserInput(ss);
    }
}


#endif // HUFFMAN_SYSTEM_H