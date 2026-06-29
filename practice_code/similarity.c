#include "myinclude.h"
#include <string.h>

AlignContext* similarity(const char* refseq, const char* queryseq, AlignContext* ctx) {
    // 初始化上下文
    ctx->g = -5;  // 空格罚分

    // 读入参考序列 s
    ctx->s.length = strlen(refseq);
    ctx->s.ch = (char*)malloc(ctx->s.length + 1);  // +1 用于终止符
    strcpy(ctx->s.ch, refseq);

    // 读入查询序列 t
    ctx->t.length = strlen(queryseq);
    ctx->t.ch = (char*)malloc(ctx->t.length + 1);
    strcpy(ctx->t.ch, queryseq);

    // 分配 entrya 矩阵（连续内存）
    int s_len = ctx->s.length;
    int t_len = ctx->t.length;
    ctx->entrya = (int**)calloc(s_len + 1, sizeof(int*));
    ctx->entrya[0] = (int*)calloc((s_len + 1) * (t_len + 1), sizeof(int));
    for (int i = 1; i <= s_len; i++) {
        ctx->entrya[i] = ctx->entrya[i - 1] + (t_len + 1);
    }

    // 分配 p 矩阵（连续内存）
    ctx->p = (int**)calloc(s_len, sizeof(int*));
    ctx->p[0] = (int*)calloc(s_len * t_len, sizeof(int));
    for (int i = 1; i < s_len; i++) {
        ctx->p[i] = ctx->p[i - 1] + t_len;
    }

    // 计算 p 矩阵
    for (int i = 0; i < s_len; i++) {
        for (int j = 0; j < t_len; j++) {
            ctx->p[i][j] = (ctx->s.ch[i] == ctx->t.ch[j]) ? 1 : -1;
        }
    }

    // 计算 entrya 矩阵
    b_entry_a(ctx);

    // 执行对齐
    ctx->a_len = s_len;
    b_align(ctx);

    // 构建 Result 结构体
    //Result* res = (Result*)malloc(sizeof(Result));
    //res->entrya = ctx->entrya;
    //res->p = ctx->p;
    //res->align_s = ctx->align_s;
    //res->align_t = ctx->align_t;
    //res->s_length = s_len;
    //res->semaphore = 0;  // 标记为连续内存分配

    return ctx;
}

void free_result(AlignContext* ctx) {
    free(ctx->s.ch);
    free(ctx->t.ch);
    // 释放 entrya 矩阵
    if (ctx->semaphore == 0 || ctx->semaphore == 2) {
        printf("release entraya\n");
        if (ctx->entrya[0]) free(ctx->entrya[0]); ctx->entrya[0] = NULL;
    }
    else {
        for (int i = 0; i <= ctx->s_length; i++) {
            if (ctx->entrya[i]) free(ctx->entrya[i]); ctx->entrya[i] = NULL;
        }
    }
    free(ctx->entrya); ctx->entrya = NULL;

    // 释放 p 矩阵
    if (ctx->semaphore == 1 || ctx->semaphore == 0) {
        printf("release p\n");
        if (ctx->p[0]) free(ctx->p[0]); ctx->p[0] = NULL;
        
    }
    else {
        for (int i = 0; i <= ctx->s_length; i++) {
            if (ctx->p[i]) free(ctx->p[i]); ctx->p[i] = NULL;
        }
    }

    // 释放对齐结果
    if (ctx->align_s) free(ctx->align_s); else printf("empty");
    free(ctx->align_t);

}