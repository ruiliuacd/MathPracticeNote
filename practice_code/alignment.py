from cffi import FFI

ffi = FFI()

# 定义C接口
ffi.cdef(""" // copy-pasted from the man page

    typedef struct {
        char* ch;
        int length;
    } dnastr;

    typedef struct {
        char* align_s;
        char* align_t;
        dnastr s;
        dnastr t;
        int g;
        int a_len;
        int** entrya;
        int** p;
        int s_length;
        int semaphore;
    } AlignContext;

    AlignContext* similarity(const char *refseq, const char* queryseq, AlignContext* ctx);
    void free_result(AlignContext* ctx);
""")

# 加载共享库
lib = ffi.dlopen("./libalign.so")# loads the entire C namespace

# 初始化上下文
ctx = ffi.new("AlignContext *")
ctx.g = -5

# 调用对齐函数
refseq = b"ACAGGGCAAGCATCGTGGTGGGGGCTTGTTACAGACCACCGAACCAGGATGAGGAGACTGATGAGGAGTTCTACAGGCAG"
queryseq = b"GACATTGAGCTGTTCAGGACACTGGT----AGCATCCCTTGGGAGGTGGTTCTGAAGGGCAGAGGAGTCCAGGAAGGCTAGGCACTCTTTAAGAAAGAAATCTT"
res = lib.similarity(refseq, queryseq, ctx)

# 获取对齐结果
align_s = ffi.string(res.align_s).decode('utf-8')
align_t = ffi.string(res.align_t).decode('utf-8')
print("Alignment S:", align_s)
print("Alignment T:", align_t)
entrya = []
s_len=res.t.length#ffi.sizeof(res.entrya)
for i in range(s_len + 1):
    row = [res.entrya[i][j] for j in range(s_len + 1)]
    entrya.append(row)
print(*entrya,sep="\n")
# 释放内存
# lib.free_result( ctx)
lib.free_result(res)
ffi.dlclose(lib)
