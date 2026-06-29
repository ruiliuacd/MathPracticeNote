#ifndef MYINCLUDE_H
#define MYINCLUDE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* ch;
    int length;
} dnastr;



typedef struct {
    char* align_s;
    char* align_t;
    dnastr s;         // 参考序列
    dnastr t;         // 查询序列
    int g;            // 空格罚分
    int a_len;        // 对齐长度
    int** entrya;     // 动态矩阵
    int** p;          // 评分矩阵
    int semaphore;
    int s_length;
} AlignContext;

// 函数声明
AlignContext* similarity(const char* refseq, const char* queryseq, AlignContext* ctx);
void free_result(AlignContext* ctx);
void b_entry_a(AlignContext* ctx);
void b_align(AlignContext* ctx);

#endif