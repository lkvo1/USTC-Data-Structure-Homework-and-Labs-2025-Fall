#ifndef BLOCKLISTSTRING_H
#define BLOCKLISTSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define CHUNK_SIZE 8

typedef struct BStringNode {
    char data[CHUNK_SIZE];
    struct BStringNode* next;
} BStringNode;

typedef struct BString {
    BStringNode* dummyHead;
    BStringNode* tail;
    unsigned int size; // 字符串总长度
    unsigned int nodeCount; // 节点数量
} BString;


// 销毁字符串
void destroyBString(BString* str) {
    // 删除所有节点
    BStringNode* current = str->dummyHead->next;
    while (current != NULL) {
        BStringNode* toDelete = current;
        current = current->next;
        free(toDelete);
    }
    
    // 释放dummyHead节点
    free(str->dummyHead);
    str->dummyHead = NULL;
    str->tail = NULL;
    str->size = 0;
    str->nodeCount = 0;
}

// 向BString末尾添加一个字符
void appendBString(BString* str, char ch) {
    unsigned int lastNodeSize = (str->size == 0) ? 0 : ((str->size - 1) % CHUNK_SIZE + 1);
    if (str->nodeCount == 0 || lastNodeSize == CHUNK_SIZE) {
        BStringNode* newNode = (BStringNode*)malloc(sizeof(BStringNode));
        newNode->data[0] = ch;
        newNode->next = NULL;
        str->tail->next = newNode;
        str->tail = newNode;
        str->nodeCount++;
    } else {
        str->tail->data[lastNodeSize] = ch;
    }
    str->size++;
}

// 初始化字符串
void initBString(BString* str) {
    str->dummyHead = (BStringNode*)malloc(sizeof(BStringNode));
    str->dummyHead->next = NULL;
    str->tail = str->dummyHead;
    str->size = 0;
    str->nodeCount = 0;
}

void assignBString(BString* str, const char* cstr) {
    destroyBString(str);
    initBString(str);

    while (*cstr) {
        appendBString(str, *cstr);
        cstr++;
    }
}

// 打印字符串
void printBString(BString* str) {
    std::cout << "BString: ";
    BStringNode* current = str->dummyHead->next;
    unsigned int printed = 0;
    
    while (current != NULL && printed < str->size) {
        unsigned int charsInNode = (current == str->tail) ? 
            ((str->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
        
        for (unsigned int i = 0; i < charsInNode; i++) {
            std::cout << current->data[i];
            printed++;
        }
        current = current->next;
    }
    std::cout << std::endl;
}

// 将串s插入到串t中字符ch之后，如果ch不存在则连接在t末尾
void insertAfterChar(BString* t, BString* s, char ch) {
    if (s == NULL || s->size == 0) return;
    
    // 查找字符ch在t中最后一次出现的位置
    BStringNode* targetNode = NULL;
    unsigned int targetPosInNode = 0;
    BStringNode* currentNode = t->dummyHead->next;
    unsigned int charIndex = 0;
    
    while (currentNode != NULL) {
        unsigned int charsInNode = (currentNode == t->tail) ? 
            ((t->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
        
        for (unsigned int i = 0; i < charsInNode; i++) {
            if (currentNode->data[i] == ch) {
                targetNode = currentNode;
                targetPosInNode = i;
            }
            charIndex++;
        }
        currentNode = currentNode->next;
    }
    
    // 如果没找到ch，将s连接在t末尾
    if (targetNode == NULL) {
        BStringNode* sCurrent = s->dummyHead->next;
        while (sCurrent != NULL) {
            unsigned int charsInNode = (sCurrent == s->tail) ? ((s->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
            for (unsigned int i = 0; i < charsInNode; i++) {
                if (t->nodeCount > 0) {
                    unsigned int lastNodeSize = (t->size - 1) % CHUNK_SIZE + 1;
                    if (lastNodeSize < CHUNK_SIZE) {
                        t->tail->data[lastNodeSize] = sCurrent->data[i];
                        t->size++;
                        sCurrent = (i == charsInNode - 1) ? sCurrent->next : sCurrent;
                        continue;
                    }
                }
                
                // 需要创建新节点
                BStringNode* newNode = (BStringNode*)malloc(sizeof(BStringNode));
                newNode->data[0] = sCurrent->data[i];
                newNode->next = NULL;
                
                t->tail->next = newNode;
                t->tail = newNode;
                t->nodeCount++;
                t->size++;
            }
            sCurrent = sCurrent->next;
        }
        return;
    }
    
    // 开始插入，将t分为三部分 ch前(包括ch),s和ch之后部分
    
    // 创建新的BString
    BString* result = (BString*)malloc(sizeof(BString));
    initBString(result);
    
    // 前部分
    currentNode = t->dummyHead->next;
    unsigned int copiedChars = 0;
    bool reachedTarget = false;
    
    while (currentNode != NULL && !reachedTarget) {
        unsigned int charsInNode = (currentNode == t->tail) ? 
            ((t->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
        
        unsigned int endPos = (currentNode == targetNode) ? targetPosInNode + 1 : charsInNode;
        
        for (unsigned int i = 0; i < endPos; i++) {
            // 添加到result
            if (result->nodeCount > 0) {
                unsigned int lastNodeSize = (result->size - 1) % CHUNK_SIZE + 1;
                if (lastNodeSize < CHUNK_SIZE) {
                    result->tail->data[lastNodeSize] = currentNode->data[i];
                    result->size++;
                    continue;
                }
            }
            
            BStringNode* newNode = (BStringNode*)malloc(sizeof(BStringNode));
            newNode->data[0] = currentNode->data[i];
            newNode->next = NULL;
            result->tail->next = newNode;
            result->tail = newNode;
            result->nodeCount++;
            result->size++;
        }
        
        if (currentNode == targetNode) {
            reachedTarget = true;
            copiedChars = targetPosInNode + 1;
        }
        currentNode = currentNode->next;
    }
    
    // 加入s
    BStringNode* sCurrent = s->dummyHead->next;
    while (sCurrent != NULL) {
        unsigned int charsInNode = (sCurrent == s->tail) ? 
            ((s->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
        
        for (unsigned int i = 0; i < charsInNode; i++) {
            if (result->nodeCount > 0) {
                unsigned int lastNodeSize = (result->size - 1) % CHUNK_SIZE + 1;
                if (lastNodeSize < CHUNK_SIZE) {
                    result->tail->data[lastNodeSize] = sCurrent->data[i];
                    result->size++;
                    continue;
                }
            }
            
            BStringNode* newNode = (BStringNode*)malloc(sizeof(BStringNode));
            newNode->data[0] = sCurrent->data[i];
            newNode->next = NULL;
            result->tail->next = newNode;
            result->tail = newNode;
            result->nodeCount++;
            result->size++;
        }
        sCurrent = sCurrent->next;
    }
    
    // 加入后半部分
    currentNode = targetNode;
    unsigned int startPos = targetPosInNode + 1;
    
    while (currentNode != NULL) {
        unsigned int charsInNode = (currentNode == t->tail) ? 
            ((t->size - 1) % CHUNK_SIZE + 1) : CHUNK_SIZE;
        
        for (unsigned int i = startPos; i < charsInNode; i++) {
            if (result->nodeCount > 0) {
                unsigned int lastNodeSize = (result->size - 1) % CHUNK_SIZE + 1;
                if (lastNodeSize < CHUNK_SIZE) {
                    result->tail->data[lastNodeSize] = currentNode->data[i];
                    result->size++;
                    continue;
                }
            }
            
            BStringNode* newNode = (BStringNode*)malloc(sizeof(BStringNode));
            newNode->data[0] = currentNode->data[i];
            newNode->next = NULL;
            result->tail->next = newNode;
            result->tail = newNode;
            result->nodeCount++;
            result->size++;
        }
        
        currentNode = currentNode->next;
        startPos = 0; // 后续节点从0开始
    }
    
    // 消去t的内容
    BStringNode* toDelete = t->dummyHead->next;
    while (toDelete != NULL) {
        BStringNode* next = toDelete->next;
        free(toDelete);
        toDelete = next;
    }
    


    // 让t指向result内容
    t->dummyHead->next = result->dummyHead->next;
    t->tail = result->tail;
    t->size = result->size;
    t->nodeCount = result->nodeCount;
}

#endif // BLOCKLISTSTRING_H