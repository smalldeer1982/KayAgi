# [NWRRC 2016] Digital Addition

## 题目描述

Deidra 正在做一个列式的加法。她写下两个正整数来对其进行求和，且一个在另一个下方，在它们的左边添 0，使得他们拥有相同的长度，然后相加计算结果（例如 $77 + 05 = 82$）。如果这个结果的长度大于这两个加数任何一个的长度（由于进位，例如$96 + 07 = 103$），就在两个加数前面附加零（$096 + 007 = 103$）。她允许不必要的前导零的出现（$007 + 004 = 011$）只要算式中的三个数字的长度都相同。

Deidra 还有一台自制的打印机。她决定在没有加号和水平线的情况下打印她的加法算式，使用下面的标准字体：
![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.11.png)

不幸的是，她弄乱了这些数字的间距，所有的数字都将以以下方式打印。打印这些本应水平相邻的数字时左边数字的右两段与右边数字的左两端重合。打印应该竖直相邻的数字时，上边数字的下半部分（由四段组成的正方形部分）与下边数字的上半部分重合。

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13476/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.41.17.png)

如果在同一位置打印一个或多个线段时，将显示为黑色。当所在位置仅打印空段时，将显示为白色。

给定一个生成的图片，找到可以通过打印机产生这个图片的正确算式。如果找不到符合要求的算式，就输出 `NO`。

## 样例 #1

### 输入

```
2
 1 1
0 1 1
 1 0
0 1 1
 1 1
0 1 1
 1 0
0 1 1
 0 0
```

### 输出

```
37
34
71
```

## 样例 #2

### 输入

```
1
 1
0 1
 1
1 1
 1
1 1
 1
0 1
 0
```

### 输出

```
2
2
4
```

## 样例 #3

### 输入

```
1
 1
1 0
 1
1 1
 1
1 1
 1
0 1
 0
```

### 输出

```
NO
```

# 题解

## 作者：____someone____ (赞：2)

### 题目大意 _~~（自己理解就好）~~_ 

**[题目传送门](https://www.luogu.com.cn/problem/P7034)**



------------


### Solution


预处理 $0\sim 9$ 每个数字对应的灯的状态， 预处理上中下分别为 $x$, $y$, $z$ $\begin{pmatrix}0\leqslant x, y, z\leqslant 9\end{pmatrix}$ 时压缩到一起的状态。

- 设 $f_{i, x, y, z}$ 表示匹配了 $i$ 位且第 $i$ 位为 $x,y,z$ 可不可行。

- 枚举上一层转移。

- 边界需要处理一下。

状态数上限 $10^5$ ，转移复杂上限 $10^2$ ，时间复杂度 $\text{O}\begin{pmatrix}w\times 10^3\times 10^2\end{pmatrix}$  。实际上有大部分状态是无用的，转移跑不满 $($ $10^2$ 这里， 很多转移会被 $\texttt{continue}$ 掉 $)$， 故可以通过此题。

------------
$\textrm{\textit{\textbf{Code:}}}$
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int N=10;
int L[N][N],t[N][N];
int s[N][N][N],ts[N][N][N];
const int maxn=107;
int w;
int val[maxn];
bool f[maxn][N][N][N];
typedef pair<int,int>PII;
pair<PII,int>pre[maxn][N][N][N];
string ansx,ansy,ansz;

void Print(int i,int x,int y,int z)
{
	if(i==0) return;
	pair<PII,int>tmp=pre[i][x][y][z];
	int a=tmp.fi.fi,b=tmp.fi.se,c=tmp.se;
	Print(i-1,a,b,c);
	ansx=(char)(x+48)+ansx;
	ansy=(char)(y+48)+ansy;
	ansz=(char)(z+48)+ansz;
}

void test()
{
	printf("%d\n",val[w]);
	printf("%d\n",s[2][0][2]);
	printf("%d\n",ts[7][1][9]);
	printf("%d\n",s[2][0][2]|ts[7][1][9]);
	printf("%d\n",f[w][2][0][2]);
}

int main()
{
//	freopen("digital.in","r",stdin);
//	freopen("digital.out","w",stdout);
	for(int i=0;i<10;++i)
		for(int j=1;j<=5;++j)L[i][j]=1;
	L[0][3]=0;t[0][2]=t[0][4]=1;
	L[1][1]=L[1][3]=L[1][5]=0;
	L[2][4]=0;t[2][4]=1;
	L[4][1]=L[4][5]=0;t[4][2]=1;
	L[5][2]=0;t[5][2]=1;
	L[6][2]=0;t[6][2]=t[6][4]=1;
	L[7][3]=L[7][5]=0;
	t[8][2]=t[8][4]=1;
	t[9][2]=1;
	for(int x=0;x<=9;++x)
	{
		for(int y=0;y<=9;++y)
		{		
			for(int z=0;z<=9;++z)
			{
				int res_s=0,res_ts=0;
				for(int j=1;j<=5;++j)
				{
					res_s|=(L[x][j]<<(j-1));
					res_s|=(L[y][j]<<(j-1+2));
					res_s|=(L[z][j]<<(j-1+4));
					res_ts|=(t[x][j]<<(j-1));
					res_ts|=(t[y][j]<<(j-1+2));
					res_ts|=(t[z][j]<<(j-1+4));
				}
				s[x][y][z]=res_s;
				ts[x][y][z]=res_ts;
			}
		}
	}
	cin>>w;
	for(int i=1;i<=9;++i)
	{
		if(i&1)
		{
			for(int j=w;j>=1;--j)
			{
				int x;
				cin>>x;
				val[j]|=(x<<(i-1));
			}
		}
		else
		{
			for(int j=w+1;j>=1;--j)
			{
				int x;
				cin>>x;
				val[j]|=(x<<(i-1));
			}
		}
	}
	for(int x=0;x<=9;++x)
	{
		for(int y=0;y<=9;++y)
		{
			if(w==1)
			{
				int z=(x+y);
				if(z>9)continue;
				int now=s[x][y][z];
				int ed=ts[x][y][z];
				if(now==val[w]&&ed==val[w+1])f[w][x][y][z]=1;
			}
			else
			{
				int z=(x+y)%10;
				if(s[x][y][z]==val[1])
					f[1][x][y][z]=1;
			}
		}
	}
	for(int i=2;i<w;++i)
	{
		for(int a=0;a<=9;++a)
		{
			for(int b=0;b<=9;++b)
			{
				for(int c=0;c<=9;++c)
				{
					if(!f[i-1][a][b][c])
						continue;
					for(int x=0;x<=9;++x)
					{
						for(int y=0;y<=9;++y)
						{
							int z=(x+y+(c<a+b?1:0))%10;
							int now=s[x][y][z]|ts[a][b][c];
							if(now==val[i])
							{
								f[i][x][y][z]=1;
								pre[i][x][y][z]=mp(mp(a,b),c);
							}
						}
					}
				}
			}
		}
	}
	for(int a=0;a<=9;++a)
	{
		for(int b=0;b<=9;++b)
		{
			for(int c=0;c<=9;++c)
			{
				if(!f[w-1][a][b][c])
					continue;
				for(int x=0;x<=9;++x)
				{
					for(int y=0;y<=9;++y)
					{
						int z=(x+y+(c<a+b?1:0));
						if(z>9)
							continue;
						int now=s[x][y][z]|ts[a][b][c];
						int ed=ts[x][y][z];
						if(now==val[w]&&ed==val[w+1])
						{
							f[w][x][y][z]=1;
							pre[w][x][y][z]=mp(mp(a,b),c);
						}
					}
				}
			}
		}
	}
	bool flag=0;
	for(int x=0;x<=9;++x)
	{
		for(int y=0;y<=9;++y)
		{
			for(int z=0;z<=9;++z)
			{
				if(f[w][x][y][z]==1)
				{
					Print(w,x,y,z);
					flag=1;
					break;
				}
			}
			if(flag)break;
		}
		if(flag)break;
	}
	if(flag)
	{
		cout<<ansx<<endl;
		cout<<ansy<<endl;
		cout<<ansz<<endl;
	}
	else cout<<"NO";
	return 0;
}
```


---

## 作者：CarroT1212 (赞：1)

> 一个带前导 $0$ 的数字位数为 $w$ 的加法竖式的相邻笔画被压到了一起，求一个合法的原竖式。
>
> $1 \le w \le 100$。

行太长了，不如对列考虑。每一列的选法是否合法仅跟上一列怎么选有关。

设 $dp_{i,s}$ 表示目前确定了前 $i$ 列数，且第 $i$ 列的三个数可被表示为状态 $s_0,s_1,s_2$ 时上一个是从哪来的。没有就 $-1$。

这里的状态 $s$ 分为两种：$(s_0+s_1)\bmod 10=s_2$；$(s_0+s_1+1)\bmod 10=s_2$。即是否需要一个进位才能合法。

对于每个 $i$，枚举这两种状态的 $s$，首先看如果这一列取 $s$ 本身会不会和输入的结果冲突（即没有输入的一位是 $0$ 而 $s$ 中对应的位是 $1$），如果不会就枚举上一个状态 $s'$，且 $s'$ 需要满足在加上 $s$ 这列的进位之后是合法的。如果和 $s'$ 组合起来之后前面几列和输入结果一模一样，而且 $dp_{i-1,s'}\neq -1$，就可以转移过去。最后找到一个合法 $dp_{n,s}$ 一路跑回来。

有一个坑点是最后一列的判定，不是跟前面的列一样不冲突就行，而是必须恰好和输入的最后一列一样，因为这时没有剩下的列用来补齐没对上的结果了。否则会 [WA on test 11](https://www.luogu.com.cn/record/149436411)。

```cpp
const string ini[5]={
" 1  0  1  1  0  1  1  1  1  1 ",
"1 10 10 10 11 11 01 00 11 11 1",
" 0  0  1  1  1  1  1  0  1  1 ",
"1 10 11 00 10 10 11 10 11 10 1",
" 1  0  1  1  0  1  1  0  1  1 "
};
void dec(int a,int *b) { b[0]=a%10,b[1]=a%100/10,b[2]=a/100; }
int n,ans[3][N],dp[N][K];
char tup[K][9][3];
vector<int> t[2];
string str[9];
void mian() {
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n),getline(cin,str[0]);
	for (int i=0;i<9;i++) getline(cin,str[i]);
	for (int s=0;s<1000;s++) {
		int tmp[3];
		dec(s,tmp);
		for (int i=0;i<3;i++) for (int j=0;j<5;j++) for (int k=0;k<3;k++)
			tup[s][i*2+j][k]=max(tup[s][i*2+j][k],ini[j][tmp[i]*3+k]);
		for (int i=0;i<9;i++) for (int j=0;j<3;j++) if (!tup[s][i][j]) tup[s][i][j]=' ';
	}
	for (int s=0;s<1000;s++) {
		int tmp[3];
		dec(s,tmp);
		if ((tmp[0]+tmp[1])%10==tmp[2]) t[0].pb(s);
		else if ((tmp[0]+tmp[1]+1)%10==tmp[2]) t[1].pb(s);
	}
	t[0].pb(1000);
	dp[0][1000]=0;
	for (int c=1;c<=n;c++) {
		for (int d=0;d<2;d++) for (int s:t[d]) if (s<1000) {
			int flg=1,tmp[3];
			dec(s,tmp);
			for (int i=0;i<9&&flg;i+=2) if (tup[s][i][1]!=str[i][c*2-1]) flg=0;
			for (int i=1;i<9&&flg;i+=2) if (tup[s][i][2]>str[i][c*2]) flg=0;
			if (flg) {
				for (int ss:t[(tmp[0]+tmp[1]+d)/10]) if (~dp[c-1][ss]) {
					int flg=1;
					for (int i=1;i<9&&flg;i+=2) if (max(tup[ss][i][2],tup[s][i][0])!=str[i][c*2-2]) flg=0;
					if (flg) { dp[c][s]=ss; break; }
				}
			}
		}
	}
	for (int s:t[0]) if (~dp[n][s]) {
		int flg=1;
		for (int i=1;i<9&&flg;i+=2) if (tup[s][i][2]!=str[i][n*2]) flg=0;
		if (flg) {
			for (int tmp[3],j=n;j;j--) {
				dec(s,tmp);
				for (int i=0;i<3;i++) ans[i][j]=tmp[i];
				s=dp[j][s];
			}
			for (int i=0;i<3;i++,cout<<"\n") for (int j=1;j<=n;j++) cout<<ans[i][j];
			return;
		}
	}
	cout<<"NO";
}
```

---

