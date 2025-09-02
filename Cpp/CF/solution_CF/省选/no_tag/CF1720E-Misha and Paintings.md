# Misha and Paintings

## 题目描述

给你一个 $n\times n$ 的矩阵 $a$，你可以对 $a$ 进行任意次操作，操作的具体步骤如下：

+ 选择矩阵 $a$ 的一个正方形子矩阵；
+ 选择一个正整数数 $x$，其中 $1\leq x\leq n^2$；
+ 将子矩阵内的所有元素修改为 $x$。

你需要求出使矩阵 $a$ 恰好包含 $k$ 个不同元素所需的最小操作次数。

最小操作次数可以为 $0$。

## 说明/提示

$1\leq n\leq 500,1\leq a_{i,j},k\leq n^2$。

## 样例 #1

### 输入

```
3 4
1 1 1
1 1 2
3 4 5```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2
2 1 3
2 1 1
3 1 2```

### 输出

```
2```

## 样例 #3

### 输入

```
3 3
1 1 1
1 1 2
2 2 2```

### 输出

```
1```

## 样例 #4

### 输入

```
3 2
1 1 1
1 2 1
2 2 2```

### 输出

```
0```

# 题解

## 作者：Daidly (赞：15)

[Codeforces Round #815 (Div. 2) 全场题解以及更好的阅读体验](https://www.cnblogs.com/Daidly/p/16607199.html)


记原始矩阵中不同值的个数为 $m$。

- $m\leq k$

每次只要选中一个 $1\times 1$ 的小矩阵改变值即可，最小操作次数为 $k-m$。

- $m>k$

样例以及手玩似乎答案不超过 $2$？考虑证明。

我们构造出一种两次一定能解决的方案。

不妨让第一次选中的正方形左上角为原矩阵左上角，假设我们能增加长度 $L$ 就增加，并且此矩形的颜色我们不统计上，即颜色为剩下 $k$ 个之一，不增加颜色。

也就是说，我们选择了最大的 $L$ 使得 $m'\ge m$，$L$ 再增加 $1$ 就会使 $m'<m$。

我们考虑第二个矩形，将它的右下角置于 $(L+1,L+1)$，向左上扩展，颜色与第一个矩形相同，都不对整体做贡献。

可以发现，每当第二个矩形边长多 $1$ 就会多两个格子消失，最多消失两种颜色，所以可以通过此将颜色变到 $k$ 或 $k-1$。

当 $m'=k$ 时，已满足要求；当 $m'=k-1$ 时，我们可以将第二个矩形的颜色换成一种新的颜色，将 $m'$ 增加 $1$，使其等于 $k$。

这样我们就证明了最多两次。

![](https://cdn.luogu.com.cn/upload/image_hosting/hdzdrnlh.png)

我们考虑什么时候答案为 $1$，其余时候都为 $2$。

先计算出每个颜色的上界 $(x1,y1)$，下界 $(x2,y2)$。即 $(x_1,y_1),(x2,y2)$ 是满足能覆盖此种颜色的最小子矩阵。

枚举一个正方形的边长 $len$，然后枚举左上角 $(i,j)$，记 $c[i][j]$ 为当边长为 $len$ 左上角为 $(i,j)$ 时，能覆盖的颜色个数。

考虑如何计算 $c[i][j]$，直接算复杂度太高，考虑每个颜色的贡献。

对于一种颜色 ，通过它的上下界可以计算出在哪一个区域内的点以 $len$ 为边长得到正方形可以覆盖这种颜色。

我们通过二维差分加二维前缀和解决 $c$ 的计算。

最后我们只需要判断每一个点 $(i,j)$ 在长为 $len$ 的前提下计算出的 $m-c[i][j]$ 是否等于 $k$ 或 $k-1$ 即可。

$k-1$ 是选中的矩阵颜色可以改变导致的。注意计算细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
 
void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
 
const int N=505;
int n,k,a[N][N],c[N][N],m;
struct node{
	int x1,y1,x2,y2;
}b[N*N];
 
int main(){
	n=read(),k=read();
	for(int i=1;i<=n*n;++i)b[i].x1=b[i].y1=1e9;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			a[i][j]=read();
			b[a[i][j]].x1=min(b[a[i][j]].x1,i);
			b[a[i][j]].y1=min(b[a[i][j]].y1,j);
			b[a[i][j]].x2=max(b[a[i][j]].x2,i);
			b[a[i][j]].y2=max(b[a[i][j]].y2,j);
		}
	}
	for(int i=1;i<=n*n;++i)if(b[i].x1!=1e9)m++;
	if(m<=k){print(k-m);return 0;}
	for(int len=1;len<=n;++len){
		memset(c,0,sizeof(c));
		for(int i=1;i<=n*n;++i){
			if(b[i].x1==1e9)continue;
			int X1=max(1,b[i].x2-len+1);
			int Y1=max(1,b[i].y2-len+1);
			int X2=min(n-len+1,b[i].x1);
			int Y2=min(n-len+1,b[i].y1);
			if(X1<=X2&&Y1<=Y2){
				c[X1][Y1]++;
				c[X2+1][Y1]--;
				c[X1][Y2+1]--;
				c[X2+1][Y2+1]++;
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
				if(m-c[i][j]==k||m-c[i][j]==k-1){
					puts("1");return 0;
				}
			}
		}
	}
	puts("2");
    return 0;
}
```

---

## 作者：dead_X (赞：6)

## 前言
简单的，可惜我不会。
## 题意
- 给定 $n\times n$ 的矩阵，每个格子有一种颜色。
- 你每次可以选择一个正方形子矩阵染色。
- 问至少需要染色几次才能使得恰好有 $k$ 种颜色。

## 思路
首先如果网格里的颜色本身 $\leq k$，我们每次染一种新颜色即可。

对于剩下的情况，想当于我们要选 $t$ 个子矩阵，使得删除它们后剩余 $r$ 个颜色，满足 $k\leq r\leq k+t$。

然后是典中典结论：注意到答案 $\leq 2$。

为什么呢。考虑一个 $q\times q$ 的矩阵超了，它左下角的 $(q-1)\times (q-1)$ 矩阵少了，我们发现在右上角弄一些神秘操作可以将中间过渡的值基本都取到，再注意到我们有 $2$ 个弹性空间，可以感性理解正确性。

于是我们只要判断 $t=1$，直接枚举一条斜线双指针即可，时间复杂度 $O(n^3)$。
## 代码
```cpp
// Problem: E. Misha and Paintings
// Contest: Codeforces - Codeforces Round #815 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1720/E
// Memory Limit: 256 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//回家？我没有家可以回，我没有退路。
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[503][503],f[250003];
int n=read(),m=read(),k=0,c=0;
inline void ins(int x){c+=!--f[x];}
inline void del(int x){c-=!f[x]++;}
signed main()
{
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			k+=!(f[a[i][j]=read()]++);
	if(k<=m) printf("%d\n",m-k),exit(0); else k-=m;
	//erase k or k+1 is both ok
	for(int sy=1; sy<=n; ++sy)
		for(int l=sy,r=sy; r<=n; ++r)
		{
			for(int i=l; i<=r; ++i) ins(a[r-sy+1][i]);
			for(int i=l-sy+1; i<r-sy+1; ++i) ins(a[i][r]);
			while(c>k+1)
			{
				for(int i=l; i<=r; ++i) del(a[l-sy+1][i]);
				for(int i=l-sy+2; i<=r-sy+1; ++i) del(a[i][l]);
				++l;
			}
			if(c>=k) puts("1"),exit(0);
			while(l<=r&&r==n)
			{
				for(int i=l; i<=r; ++i) del(a[l-sy+1][i]);
				for(int i=l-sy+2; i<=r-sy+1; ++i) del(a[i][l]);
				++l;
			}
		}
	for(int sx=2; sx<=n; ++sx)
		for(int l=sx,r=sx; r<=n; ++r)
		{
			for(int i=l; i<=r; ++i) ins(a[i][r-sx+1]);
			for(int i=l-sx+1; i<r-sx+1; ++i) ins(a[r][i]);
			while(c>k+1)
			{
				for(int i=l; i<=r; ++i) del(a[i][l-sx+1]);
				for(int i=l-sx+2; i<=r-sx+1; ++i) del(a[l][i]);
				++l;
			}
			if(c>=k) puts("1"),exit(0);
			while(l<=r&&r==n)
			{
				for(int i=l; i<=r; ++i) del(a[i][l-sx+1]);
				for(int i=l-sx+2; i<=r-sx+1; ++i) del(a[l][i]);
				++l;
			}
		}
	puts("2");
	return 0;
}
```

---

## 作者：Iratis (赞：4)

## 前言

还不错的一道 2700 ，构造方式有点新奇。

## 题目分析

记 $ tot $ 为矩阵中的颜色种数。

观察题目，先思考比较简单的情况：

1. $ tot \leq k $

显然，只需要将 $ k-tot $ 个 $ 1 \times 1 $ 的正方形进行颜色的改动。

2. $ tot>k $

结论：答案只会为 $ 1 $ 或 $ 2 $ 。

证明如下：

考虑如下构造，确定一个位置 $ (i,j) $，作为第一次修改的正方形的左上角。假设当前正方形的边长为 $ len_1 $，所以该正方形的右下角为 $ (i+len_1-1,j+len_1-1) $。同时将第二个正方形的右下角固定在 $ (i+len_1,j+len_1) $。

![](https://cdn.luogu.com.cn/upload/image_hosting/aefdc5gg.png)

接下来我们来思考第二次修改的正方形的边长，设为 $ len_2 $，同时规定 $ len_2 \leq len_1+1 $，同时记 $ S $ 为两个正方形所覆盖的总区域。最初 $ len_2=1,S=len_1 \times len_1+1 $ ，即为上图所示。

这时候，就出现了一个巧妙的性质，我们发现每次 $ len_2 $ 增加 $ 1 $，$ S $ 便增加 $ 2 $，$ tot $ 会减少 $ 0/1/2 $。

最后，当 $ len_1+1=len_2 $ 时，我们如法炮制，令 $ len_1=len_2,len_2=1 $，同时在当前的绿色区域的右下角再添加一个新的正方形，这一步操作后，$ S $ 会增加 $ 1 $，$ tot $ 会减少 $ 0/1 $。

![](https://cdn.luogu.com.cn/upload/image_hosting/2l46vqaf.png)

总结上文的分析，我们总存在一种扩展方式，使得 $ tot $ 每次减少 $ 0/1/2 $，所以一定会有某个时刻满足 $ tot=k $ 或 $ tot=k+1 $。

若 $ tot=k+1 $，那我们只需要将两次修改重叠的部分稍加调整即可。

于是，我们就得到了本题的解法：倘若 $ tot \leq k $，输出 $ k-tot $。否则，判断是否能在 $ 1 $ 次操作内将矩阵修改合法。可以，输出 $ 1 $；不能，输出 $ 2 $。

而判断是否能在 $ 1 $ 次操作内将矩阵修改合法，方法也非常简单。只需要枚举正方形的边长，利用二维前缀和判断是否有某个位置合法即可。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
int n,ned,sum[505][505],tot;
struct num{int x,y;}mn[250005],mx[250005];
void add(num a,num b)
{
	if(a.x>b.x||a.y>b.y)return ;
	sum[a.x][a.y]++,sum[b.x+1][a.y]--,sum[a.x][b.y+1]--,sum[b.x+1][b.y+1]++;
}
bool check(int len)
{
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n*n;i++)
	{
		if(mn[i].x==1e9)continue;
		num minn,maxx;
		minn.x=max(1,mx[i].x-len+1),minn.y=max(1,mx[i].y-len+1);
		maxx.x=min(n-len+1,mn[i].x),maxx.y=min(n-len+1,mn[i].y);
		add(minn,maxx);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(tot-sum[i][j]==ned||tot-sum[i][j]+1==ned)return true;
	return false;
}
int solve()
{
	for(int i=1;i<=n*n;i++)if(mn[i].x!=1e9)tot++;
	if(tot<=ned)return ned-tot;
	for(int len=1;len<=n;len++)if(check(len))return 1;
	return 2;
}
signed main()
{
	scanf("%d%d",&n,&ned);
	for(int i=1;i<=n*n;i++)mn[i].x=mn[i].y=1e9;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int x;scanf("%d",&x);
			mn[x].x=min(mn[x].x,i),mn[x].y=min(mn[x].y,j);
			mx[x].x=max(mx[x].x,i),mx[x].y=max(mx[x].y,j);
		}
	}
	printf("%d",solve());
	return 0;
}
```


---

## 作者：Plozia (赞：3)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16712519.html)

神仙 2700。

首先统计出原数组中不同元素个数记作 $cnt$，如果 $cnt\le k$ 说明元素个数不够，由于一次只能加一个颜色因此答案就是 $k-cnt$。

然后接下来要证明一个结论：答案上限为 $2$。

证明：

下面都已左上角为 $(1,1)$ 为条件证明，对于左上角不为 $(1,1)$ 的情况证明类似。

考虑每次以左上角 $(1,1)$ 为正方形顶点，边长一步步扩大，如下图（绿色部分）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3pmgbxs0.png)

设正方形右下角 $(i,i)$，那么我们从 $(i+1,i+1)$ 开始，每次往上往左覆盖一个（但是不与之前的正方形重合），如下图（蓝色部分，黑色部分为重叠）：

![](https://cdn.luogu.com.cn/upload/image_hosting/z0n3whho.png)

这就是两次覆盖，下面钦定这两次覆盖都使用剩余白色部分中没有的颜色覆盖。

注意到第一次覆盖之后，如果白色部分颜色种类为 $k$ 或者是 $k-1$，那么我们可以使绿色部分颜色覆盖为原来就有的颜色（对应 $k$）或是一种新颜色（对应 $k-1$），此时答案为 $1$。该条件也是答案为 $1$ 的充要条件。

如果白色部分颜色种类大于 $k$，我们需要第二次覆盖，注意到第二次覆盖从 $1\times1\to2\times2\to...$ 时，每次扩展两格，则颜色可能减少 $0,1,2$。

由于我们需要第二次覆盖，因此蓝色+白色部分原颜色种类个数一定大于 $k$，因此我们可以证明过程中一定会有一组满足条件的绿色**和**蓝色矩形覆盖方案，使得白色部分为 $k$ 或者 $k-1$，若为 $k$ 那么就覆上两个相同且有的颜色，若为 $k-1$ 那么一个覆有的一个覆没有的，特别的有人会问能不能 $k-2$ 然后覆盖两个新的，但该情况其实可以归约到 $k$ 和 $k-1$ 的情况。

如果白色部分颜色种类小于 $k-1$，此时我们需要缩短正方形边长，因为正常情况下你已经没法做到再覆盖一次使得颜色种类为 $k$，最好情况就是类似于白色新覆盖一个，白色里面新覆盖一个可以做到两次，然而缩短边长同样可以两次：

考虑一种临界情况，边长为 $i$ 时白色部分颜色种类小于 $k-1$，边长为 $i-1$ 时白色部分颜色种类 $>k$（等于 $k$ 或 $k-1$ 时答案就是 1，上面已经证明），然后我们使用蓝色矩形尽可能覆盖边长为 $i-1$ 的正方形，那么只会剩下左下角右上角两个格子没有覆盖。

注意到由于边长为 $i$ 和 $i-1$ 时白色部分颜色种类分别小于 $k-1$ 和大于 $k$，因此这里面存在至少两种颜色跨度，无论这两种颜色是不是左上角右上角独有的，都可以得知蓝色矩形覆盖过程中会出现白色部分为 $k$ 或者 $k-1$ 的情况，因为尽可能覆盖时白色区域颜色种类最小也是 $k-1$ 种。

上述除了证明白色部分颜色种类小于 $k-1$ 缩短边长就可以之外，同时也证明了必然存在方案。

这样就证明了结论：答案上界为 $2$。

现在只需要考虑答案为 $1$ 的情况（答案为 $0$ 已经在 $cnt\le k$ 中处理了），满足该情况就需要存在一个正方形满足其余部分颜色个数为 $k$ 或 $k-1$，考虑先枚举长度 $len$，预处理 $sum_{i,j}$ 表示长度为 $len$ 时 $(i,j)$ 为左上角的正方形内**完全包含多少种颜色**，也就是 $cnt-sum_{i,j}$ 为其余部分颜色个数。

为做到这一点，考虑预处理覆盖每个颜色的最小矩形 $(x1,y1),(x2,y2)$，由于枚举长度为 $len$，我们可以知道对于每个颜色，有哪些正方形能覆盖到这个颜色，对这些正方形左上角顶点加一，即矩形加 $1$，这可以二维差分然后二位前缀和解决。

处理完 $sum_{i,j}$ 后，只需要知道有无 $cnt-sum_{i,j}$ 为 $k$ 或 $k-1$ 即可。

GitHub：[CodeBase-of-Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E6%9D%82%E9%A1%B9/%E6%80%9D%E7%BB%B4%2B%E6%9E%84%E9%80%A0%2B%E4%BA%A4%E4%BA%92/CF1720E%20Misha%20and%20Paintings.cpp)

Code：

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1720E Misha and Paintings
	Date:2022/9/20
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 500 + 5;
int n, k, a[MAXN][MAXN], sum[MAXN][MAXN], cnt, fir[MAXN * MAXN][2], sec[MAXN * MAXN][2];
bool book[MAXN * MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = Read(), k = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			book[a[i][j] = Read()] = 1;
	for (int i = 1; i <= n * n; ++i) cnt += book[i];
	if (cnt <= k) { printf("%d\n", k - cnt); return 0; }
	memset(fir, 0x7f, sizeof(fir));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			fir[a[i][j]][0] = std::min(fir[a[i][j]][0], i);
			fir[a[i][j]][1] = std::min(fir[a[i][j]][1], j);
			sec[a[i][j]][0] = std::max(sec[a[i][j]][0], i);
			sec[a[i][j]][1] = std::max(sec[a[i][j]][1], j);
		}
	int flag = 0;
	for (int len = 1; len <= n; ++len)
	{
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) sum[i][j] = 0;
		for (int i = 1; i <= n * n; ++i)
		{
			if (!book[i]) continue ;
			if (len < std::max(sec[i][0] - fir[i][0], sec[i][1] - fir[i][1])) continue ;
			int Line = sec[i][0] - fir[i][0] + 1, Col = sec[i][1] - fir[i][1] + 1;
			int r1 = std::max(1, fir[i][0] - (len - Line)), c1 = std::max(1, fir[i][1] - (len - Col));
			int r2 = std::min(n - len + 1, fir[i][0]), c2 = std::min(n - len + 1, fir[i][1]);
			++sum[r1][c1]; --sum[r2 + 1][c1]; --sum[r1][c2 + 1]; ++sum[r2 + 1][c2 + 1];
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (cnt - sum[i][j] == k || cnt - sum[i][j] == k - 1) flag = 1;
	}
	if (flag == 1) printf("1\n");
	else printf("2\n");
	return 0;
}
```

---

## 作者：周子衡 (赞：1)

不妨设原来的矩阵中一共有 $C$ 种数字。

**结论一** $C\leq k$ 时，答案为 $k-C$。

**证明** 每次操作至多让 $C$ 增加 $1$，且 $C < n^2$ 时一定有一种操作方法可以使 $C$ 增加 $1$。

**结论二** $C > k$ 时答案不超过 $2$。

**证明** 观察以下一系列方案，其中，黄蓝两色分别表示两个需要覆盖正方形区域，绿色表示两个正方形的重叠区域。不妨假定我们将两个正方形区域赋为同一个值，且该值没有在其他地方出现过。可以发现，此时的 $C$ 等于图中空白部分的数字种数加上 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vsrv48n3.png)

这些方案是这样构造的：方案分成 $n$ 行，第 $i(1\leq i\leq n-1)$ 行第 $1$ 个方案只用了一个正方形（黄色），它位于全图的左下角，边长为 $i$。接着，一个右上角为 $(i+1,i+1)$ 的正方形（蓝色）开始不断扩展，直到它把黄色正方形整个吞噬为止，此时进入了下一行。特别地，第 $n$ 行只有一个方案，该方案中一个正方形覆盖了全图。

（上面是一个 $n=6$ 的例子，简便起见只画了前三行。）

注意到在这样的顺序下，每一种方案的空白区域比前一个方案都少了 $1$ 个或者 $2$ 个。那么，空白区域的数字种数也只会减小 $0,1$ 或 $2$。那么，其中一定有一种方案，其空白区域数字种类数为 $k-1$ 或 $k$。如果为 $k-1$ 那么直接解决；如果为 $k$，注意到我们前面钦定了染色时两个正方形都染一种从未出现过的颜色，我们改染 $k$ 个颜色中的一种即可让总颜色数变为 $k$。得证。

------------------

所以，我们只需要判断 $C > k$ 时，答案能否为 $1$ 即可。注意到总正方形数只有 $O(n^3)$ 个，可以采用相对暴力的判法。考虑枚举正方形一条对角线所在的直线，那么每个颜色对应一个区间 $[l,r]$：当且仅当正方形左右边界坐标完全包含 $[l,r]$ 时，该颜色被全部包含在正方形内。求一次二维前缀和即可知道每个正方形外的颜色数，判断是否为 $k$ 或 $k-1$ 即可。时间复杂度 $O(n^3)$。

---

## 作者：Sellaris (赞：1)

- 优秀的思维、数学和实现题。

- 首先我们注意到，如果原先颜色数比给定的询问颜色数小，因为我们每次只能染一种颜色，所以直接输出差值即是答案。

- 接着我们讨论其他情况，首先给出结论：**其他情况的答案不超过** $2$。

- 关于这个结论，其含义是双指针维护正方形即可在有一定连续性的答案中取到，若取不到则另开一个正方形补全边角上的区域即一定能恰好得到答案。

- 参考了相关实现，因为 STD 的实现相当优秀。

- 实现时对每个颜色处理出存在的矩形区域。枚举边长时检查有无颜色可被完全覆盖，再使用二位前缀和判断覆盖个数，通过选择正确的颜色就可以判断答案是否为 $1$。

```cpp
///*****Sellaris*****///

//I will win stars full sleeves in my dream.

#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;

const int maxn=2e5+10;
const int mo=1e9+7;

inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}

int n,m;
const int INF=INT_MAX;

inline void solve(){
	n=read();m=read();int cnt=0;
	std::vector<std::vector<int> > a(n+1,std::vector<int>(n+1));
	std::vector<std::vector<int> > pre(n+1,std::vector<int>(n+1));
	std::vector<std::tuple<int,int,int,int> > all((n+1)*(n+1),std::make_tuple(INF,-INF,INF,-INF));
	for(int i=0;i<n;i++) 
		for(int j=0;j<n;j++){
			a[i][j]=read();
			tuple<int,int,int,int>& reg=all[a[i][j]];
			get<0>(reg)=min(get<0>(reg),i),
    		get<1>(reg)=max(get<1>(reg),i),
    		get<2>(reg)=min(get<2>(reg),j),
    		get<3>(reg)=max(get<3>(reg),j);
    	}
    for(auto [a1,a2,a3,a4] : all) if(a1!=INF) cnt++;
	if(cnt<=m) {cout<<m-cnt<<endl;return;}
	for(int len=1;len<=n;len++){
		for(auto [a1,a2,a3,a4] : all){
			if(a1==INF) continue;
			int minx=a1,maxx=a2,miny=a3,maxy=a4;
			maxx=max(0,maxx-len+1);
			maxy=max(0,maxy-len+1);
			minx=min(minx,n-len);
			miny=min(miny,n-len);
			if(maxx<=minx && maxy<=miny){
				++pre[maxx][maxy];
				--pre[maxx][miny+1];
				--pre[minx+1][maxy];
				++pre[minx][miny+1];
			}
		}
		for(int x=0;x<n;x++){
			for(int y=0;y<n;y++){
				if(x==0 && y==0) continue;
				else if(x==0) pre[x][y]+=pre[x][y-1];
				else if(y==0) pre[x][y]+=pre[x-1][y];
				else pre[x][y]+=pre[x-1][y]+pre[x][y-1]-pre[x-1][y-1];
			}
		}
		for(int x=0;x<n;x++){
			for(int y=0;y<n;y++){
				if(cnt-pre[x][y]==m || cnt-pre[x][y]+1==m){
					puts("1");return;
				}
			}
		}
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                pre[i][j]=0;
            }
        }
	}
	puts("2");
}
signed main(){
	int t=1;
	while(t--){
		solve();
	}
    return 0;
}
  
```


---

## 作者：takanashi_mifuru (赞：0)

容易发现如果你想让颜色变多，你可以直接一个点一个点的改，答案很容易计算。

所以我们重点来看一看颜色要变少的情况。

这个题需要大眼睛的结论是：最多用两次操作必然能够满足条件。

我们考虑调整法证明：

![](https://pic.imgdb.cn/item/66b2b72ed9c307b7e9fb9147.png)

在这张图中，我假设操作蓝色和红色的正方形，则只有左下角和右上角的不被涵盖，而如果红色的缩短一点：

![](https://pic.imgdb.cn/item/66b2b776d9c307b7e9fbbc77.png)

容易发现多出了两个元素，这样至多多出两种新的颜色。

如果消没了，我们就把最后一行和最后一列抛开，然后再来做就好了，这样虽说不足以证明我们一定能够凑出 $k$ 个来，但 $k-1$ 和 $k-2$ 很明显至少有一个会被凑出来。

而很明显的是，我框出来的这两个矩形还没投票呢！

他们染色了之后，可以选择出现过的，总颜色数量不变，也可以其中一个选择没出现过的，总颜色数量增加 $1$，也可以两个都选不同的没出现过的，总颜色数量增加 $2$，换句话说，我可以自由选择在这个矩形被排除的基础上做这个事情，而我们知道 $k-1$ 和 $k-2$ 至少会有一个被凑出来，所以这样一定可行。

这样一定可行，也就意味着我只需要判断一个正方形就成功的，我们考虑拉出对角线，枚举这个正方形的右下角，并且对于每条对角线我提前预处理出每个颜色在右下角到什么位置的时候被加入。

时间复杂度 $O(n^3)$。

---

