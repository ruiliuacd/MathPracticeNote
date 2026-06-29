#define DEFINE_GLOBALS
#include"myinclude.h"
int count(FILE * fp)
{char ch;int i=0;
	ch=fgetc(fp);
	while(ch!=EOF)
		{
			if(ch=='\n')i--;		//回车不计数
			i++;ch=fgetc(fp);
		}
	printf("%d\n",i);
	return (i);}

int m_max(int a,int b,int c)
{int temp;
temp=b;
	if(a>temp)
		{
			temp=a;
		}
	if(c>temp)
		temp=c;
	return temp;
}

void b_entry_a(AlignContext* ctx) {
	int s_len = ctx->s.length;
	int t_len = ctx->t.length;
	int** a = ctx->entrya;

	for (int i = 0; i <= s_len; i++) {
		a[i][0] = i * ctx->g;
	}
	for (int j = 1; j <= t_len; j++) {
		a[0][j] = j * ctx->g;
	}

	for (int i = 1; i <= s_len; i++) {
		for (int j = 1; j <= t_len; j++) {
			a[i][j] = m_max(
				a[i - 1][j] + ctx->g,
				a[i][j - 1] + ctx->g,
				a[i - 1][j - 1] + ctx->p[i - 1][j - 1]
			);
		}
	}
}

/*
void b_align(int i,int j,int len)       //递归算法，结果反的，而且不正确
{
	if(i==0&&j==0)
	{
		printf("%d\n",len);a_len=len;
		align_s=(char*)malloc(len*sizeof(char));
		align_t=(char*)malloc(len*sizeof(char));
		len=0;
		
	}
else if(i>0&&(entrya[i][j]==entrya[i-1][j]+g))
	{
		
		b_align(i-1,j,++len);
		align_s[len]=s.ch[i];
		align_t[len]=' ';
	}
else if(i>0&&j>0&&(entrya[i][j]==entrya[i-1][j-1]+p[i-1][j-1]))
	{
		
		b_align(i-1,j-1,++len);
		align_s[len]=s.ch[i];
		align_t[len]=t.ch[j];
	}
else
	{
		
		b_align(i,j-1,++len);
		align_s[len]=' ';
		align_t[len]=t.ch[j];
	}
}
*/
void b_align(AlignContext* ctx) {
	int i = ctx->s.length;
	int j = ctx->t.length;
	int len = 0;

	// 计算对齐长度（允许 i 或 j 为 0）
	while (i > 0 || j > 0) {
		len++;
		if (i > 0 && ctx->entrya[i][j] == ctx->entrya[i - 1][j] + ctx->g) {
			i--;
		}
		else if (i > 0 && j > 0 && ctx->entrya[i][j] == ctx->entrya[i - 1][j - 1] + ctx->p[i - 1][j - 1]) {
			i--; j--;
		}
		else {
			if (j > 0) j--;
			else i--;
		}
	}

	// 分配对齐结果内存（包含终止符）
	ctx->align_s = (char*)calloc(len + 1, sizeof(char));
	ctx->align_t = (char*)calloc(len + 1, sizeof(char));
	ctx->a_len = len;

	// 填充对齐结果（确保索引不越界）
	len--;
	i = ctx->s.length;
	j = ctx->t.length;
	while (len >= 0) {
		if (i > 0 && ctx->entrya[i][j] == ctx->entrya[i - 1][j] + ctx->g) {
			ctx->align_s[len] = ctx->s.ch[i - 1];
			ctx->align_t[len] = '-';
			i--;
		}
		else if (i > 0 && j > 0 && ctx->entrya[i][j] == ctx->entrya[i - 1][j - 1] + ctx->p[i - 1][j - 1]) {
			ctx->align_s[len] = ctx->s.ch[i - 1];
			ctx->align_t[len] = ctx->t.ch[j - 1];
			i--; j--;
		}
		else {
			ctx->align_s[len] = '-';
			ctx->align_t[len] = (j > 0) ? ctx->t.ch[j - 1] : '-';
			if (j > 0) j--;
			else i--;
		}
		len--;
	}
}		  ///该函数还有改进的余地
