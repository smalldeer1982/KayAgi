# Animal Observation (easy version)

## 题目描述

The only difference between easy and hard versions is the constraint on $ k $ .

Gildong loves observing animals, so he bought two cameras to take videos of wild animals in a forest. The color of one camera is red, and the other one's color is blue.

Gildong is going to take videos for $ n $ days, starting from day $ 1 $ to day $ n $ . The forest can be divided into $ m $ areas, numbered from $ 1 $ to $ m $ . He'll use the cameras in the following way:

- On every odd day ( $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, ...), bring the red camera to the forest and record a video for $ 2 $ days.
- On every even day ( $ 2 $ -nd, $ 4 $ -th, $ 6 $ -th, ...), bring the blue camera to the forest and record a video for $ 2 $ days.
- If he starts recording on the $ n $ -th day with one of the cameras, the camera records for only one day.

Each camera can observe $ k $ consecutive areas of the forest. For example, if $ m=5 $ and $ k=3 $ , he can put a camera to observe one of these three ranges of areas for two days: $ [1,3] $ , $ [2,4] $ , and $ [3,5] $ .

Gildong got information about how many animals will be seen in each area each day. Since he would like to observe as many animals as possible, he wants you to find the best way to place the two cameras for $ n $ days. Note that if the two cameras are observing the same area on the same day, the animals observed in that area are counted only once.

## 说明/提示

The optimal way to observe animals in the four examples are as follows:

Example 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/d3d7ccf6369074c42d9cb3c6953ef69b03850081.png)Example 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/cb62ca568d7dec1d0d903ae38c9fff43fc945cf2.png)Example 3:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/3e18878b2213816dafe01bd460999dff35151fc8.png)Example 4:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F1/dc814ca536d6cd407d5a49988e0923d5d85a8629.png)

## 样例 #1

### 输入

```
4 5 2
0 2 1 1 0
0 0 3 1 2
1 0 4 3 1
3 3 0 0 4```

### 输出

```
25```

## 样例 #2

### 输入

```
3 3 1
1 2 3
4 5 6
7 8 9```

### 输出

```
31```

## 样例 #3

### 输入

```
3 3 2
1 2 3
4 5 6
7 8 9```

### 输出

```
44```

## 样例 #4

### 输入

```
3 3 3
1 2 3
4 5 6
7 8 9```

### 输出

```
45```

# 题解

## 作者：dblark (赞：5)

$ \LaTeX $ 渲染挂了，请到博客中查看

设 $ f_{i, j} $ 是第 $ i $ 天在 $ j $ 个位置放置的最大值。

设 $ sum_{i, j} $ 是第 $ i $ 行的前缀和。

通过 $ sum_{i, j} $ 我们先可以求出 $ f_{1, j} $。

根据题意不难写出递推的式子：

$$ f_{i, j} = sum_{i + 1, j + k - 1} - sum_{i + 1, j - 1} + \text{max}
\begin {cases}
f_{i - 1, l} + sum_{i, j + k - 1} - sum_{i, j - 1} & (1 \leq l \leq j - k) \\
f_{i - 1, l} + sum_{i, j + k - 1} - sum_{i, l + k - 1} & (j - k + 1 \leq l \leq j) \\
f_{i - 1, l} + sum_{i, l - 1} - sum_{i, j - 1} & (j + 1 \leq l \leq j + k - 1) \\
f_{i - 1, l} + sum_{i, j + k - 1} - sum_{i, j - 1} & (j + k \leq l \leq m - k + 1) \\
\end {cases}$$

直接转移是 $ O(n m ^ 2) $ 的，不过我们观察到当 $ 1 \leq l \leq j - k $ 时，$ \text{max} \{ f_{i - 1, l} + sum_{i, j + k - 1} - sum_{i, j - 1} \} $ 仅与 $ f_{i - 1, l} $ 有关，因此我们可以用一个前缀 $ \text{max} $ 维护。当 $ j + k \leq l \leq m - k + 1 $ 时同理可以维护后缀 $ \text{max} $。

观察到 $ k $ 很小，当 $ j - k + 1 \leq l \leq j + k - 1 $ 时我们可以暴力转移。总时间复杂度是 $ O(n m k) $ 的。

```cpp
#include <cstdio>
#include <algorithm>
#define N 55
#define M 20005

int n, m, k;
int a[N][M], sum[N][M], f[N][M], pre[M], suf[M];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
    for (int i = 1; i <= m - k + 1; ++i) f[1][i] = sum[1][i + k - 1] - sum[1][i - 1] + sum[2][i + k - 1] - sum[2][i - 1];
    for (int i = m - k + 1; i; --i) suf[i] = std::max(suf[i + 1], f[1][i]);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m - k + 1; ++j) pre[j] = std::max(pre[j - 1], f[i - 1][j]); // 维护前缀后缀
        for (int j = m - k + 1; j; --j) suf[j] = std::max(suf[j + 1], f[i - 1][j]);
        for (int j = 1; j <= m - k + 1; ++j) {
            f[i][j] = std::max(j > k ? pre[j - k] : 0, j + k <= m - k + 1 ? suf[j + k] : 0) + sum[i][j + k - 1] - sum[i][j - 1];
            for (int l = std::max(1, j - k + 1); l <= j; ++l) f[i][j] = std::max(f[i][j], f[i - 1][l] + sum[i][j + k - 1] - sum[i][l + k - 1]);
            if (j <= m - k) for (int l = j + 1; l <= j + k - 1 && l <= m - k + 1; ++l) f[i][j] = std::max(f[i][j], f[i - 1][l] + sum[i][l - 1] - sum[i][j - 1]);
            f[i][j] += sum[i + 1][j + k - 1] - sum[i + 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= m - k + 1; ++i) ans = std::max(ans, f[n][i]);
    printf("%d\n", ans);
}
```

---

## 作者：章烨凯 (赞：5)

## 题意
给出一个$n \times m$ 的数字矩阵，每一行都可以放置一个横跨该行和下一行的 $2 \times k$ 的矩形，求所有矩形覆盖数值的最大总和。
## 思路
可以看出这是一道dp题。

因为矩形只横跨两行，所以每一行的决策只与上一行有关。

设 $f[i][j]$ 表示第 $i$ 行放置一个覆盖列 $j$ ~ $j+k$ 的矩形，已放置的矩形覆盖数值的最大总和。那么我们可以得出这样的转移方程：

$f[i][j]=\max(f[i-1][l]-c+b)(1\le l\le m-k+1)$

其中 $c$ 表示该行放置的矩形与上一个矩形重叠部分的数值, $b$ 表示该行放置的矩形覆盖的数值。这两者都可以用前缀和来计算。

答案为 $\max(f[n][i])(1\le i\le m-k+1)$ 。

时间复杂度 $\Theta(nm^2)$ 。

## TLE代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[55][20005],f[55][20005];
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%lld",&a[i][j]);
			a[i][j]+=a[i][j-1];//前缀和
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m-k+1;j++)
		{
			int b=a[i][j+k-1]-a[i][j-1]+a[i+1][j+k-1]-a[i+1][j-1];//覆盖的数值
			for (int l=1;l<=m-k+1;l++)
			{
				int x=max(j,l),y=min(j+k-1,l+k-1),c=i>1&&x<=y?a[i][y]-a[i][x-1]:0;//重叠部分的数值，如果是第一行或者没有重叠部分则为0
				f[i][j]=max(f[i][j],f[i-1][l]-c+b);
			}
		}
	ll ans=0;
	for (int i=1;i<=m-k+1;i++)
		ans=max(ans,f[n][i]);
	printf("%lld",ans);
	return 0;
}
```
显然复杂度爆炸。

再想一想可以发现其实有大部分转移是可以优化的。当两个矩形没有重叠部分时，完全可以预处理出最大值$\Theta(1)$转移。要进行决策的只有重叠部分，即$j-k+1$~$j+k-1$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/y3iuf3pm.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

如图，蓝色部分为当前选择的矩形，红色圆圈表示可转移的上一个矩形的左上角位置，圆圈内数字表示矩形编号。那么可以发现1，2，8，9，10矩形都与当前矩形没有重叠部分，可以直接转移。而只有3，4，5，6，7矩形需要决策 ($5-3+1$ ~ $5+3-1$) 。

时间复杂度 $\Theta(nmk)$ 。

观察数据范围：$1\le k\le \min(m,20))$ ，已经可以AC了。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[55][20005],f[55][20005],mx1[20005],mx2[20005];
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%lld",&a[i][j]);
			a[i][j]+=a[i][j-1];
		}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m-k+1;j++)
		{
			int b=a[i][j+k-1]-a[i][j-1]+a[i+1][j+k-1]-a[i+1][j-1];
			f[i][j]=max(mx1[j-k],mx2[j+k])+b;//没有重叠部分，左边和右边取个最大值
			for (int l=j-k+1;l<=j+k-1;l++)
			{
				int x=max(j,l),y=min(j+k-1,l+k-1),c=i>1?a[i][y]-a[i][x-1]:0;//重叠部分的数值，i=1时为0
				f[i][j]=max(f[i][j],f[i-1][l]-c+b);
			}
		}
		for (int j=1;j<=m-k+1;j++)
			mx1[j]=max(mx1[j-1],f[i][j]);
		for (int j=m-k+1;j;j--)
			mx2[j]=max(mx2[j+1],f[i][j]);//预处理,mx1[j],mx2[j]分别表示f[i][1]~f[i][j]的最大值和f[i][j]~f[i][m-k+1]的最大值
	}
	ll ans=0;
	for (int i=1;i<=m-k+1;i++)
		ans=max(ans,f[n][i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wucstdio (赞：3)

不得不说打这一场是真的爽……

一篇题解发两次应该没啥问题吧我猜……

这道题我写的是 $O(nm\log m)$ 的线段树解法，但是好像还有单调队列的 $O(nm)$ 解法。

### 题目大意

给你一个 $n\times m$ 的矩形，每一个格子里面有一个数字，你可以在每一行里选择一个 $2\times k$ 的矩形（这个矩形跨越两行），要求最后所有你选择的矩形的并的权值和最大。

### 数据范围

$1\le n\le 50,1\le m\le 20000$

### 解题过程

首先我们注意到可以 DP。

设 $f_{i,j}$ 表示处理完了前 $i-1$ 行，其中第 $i-1$ 行选择的区间是 $[j,j+k-1]$，当前覆盖的格子的最大权值。

令 $S_{i,j}=\sum_{k=1}^ja_{i,k}$，枚举当前行选择的区间，我们可以得到转移方程：

$$g_{i,j}=\max_{l}\begin{cases}f_{i-1,l}-(S_{i,l+k-1}-S_{i,j-1})&\text{if $l\in [j-k,j]$}\\f_{i-1,l}-(S_{i,j+k-1}-S_{i,l-1})&\text{if $l\in [j,j+k]$}\\f_{i-1,l}&\text{otherwise}\end{cases}$$

$$f_{i,j}=g_{i,j}+S_{i,j+k-1}-S_{i,j-1}+S_{i+1,j+k-1}-S_{i+1,j-1}$$

也就是减去重复的再加上新覆盖的。直接转移是 $O(nm^2)$ 的。

我们设 $x_{i,j}=f_{i,j}-S_{i,j+k-1}$,$y_{i,j}=f_{i,j}+S_{i,j-1}$，则上式变为：

$$g_{i,j}=\max_{l}\begin{cases}x_{i-1,l}+S_{i,j-1}&\text{if $l\in [j-k,j]$}\\y_{i-1,l}-S_{i,j+k-1}&\text{if $l\in [j,j+k]$}\\f_{i-1,l}&\text{otherwise}\end{cases}$$

我们需要维护出 $x,y,f$ 三个数组，实现单点修改和区间取 $\max$，可以用线段树轻松实现。

时间复杂度为 $O(nm\log m)$。

### 代码

注意代码里面的 $k$ 和 $l$ 与题目中的 $k$ 和 $l$ 意义是相反的。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define lc x<<1//相比之前我现在的码风发生了一些微小的改变
#define rc x<<1|1
#define mid ((l+r)>>1)
using namespace std;
struct Tree//线段树
{
	ll maxv[80005];
	void pushup(int x)
	{
		maxv[x]=max(maxv[lc],maxv[rc]);
	}
	void update(int x,int l,int r,int p,ll v)
	{
		if(l==r)
		{
			maxv[x]=v;
			return;
		}
		if(p<=mid)update(lc,l,mid,p,v);
		else update(rc,mid+1,r,p,v);
		pushup(x);
	}
	ll ask(int x,int l,int r,int from,int to)
	{
		if(from>to)return -1e12;
		if(l>=from&&r<=to)return maxv[x];
		ll ans=-1e12;
		if(from<=mid)ans=max(ans,ask(lc,l,mid,from,to));
		if(to>mid)ans=max(ans,ask(rc,mid+1,r,from,to));
		return ans;
	}
};
Tree t1,t2,t3;//t1,t2,t3分别维护f,x,y
int n,m,l;
ll a[55][20005],s[55][20005],f[20005];
int main()
{
	scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    scanf("%lld",&a[i][j]);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    s[i][j]=s[i][j-1]+a[i][j];
	for(int i=1;i<=80000;i++)
	  t1.maxv[i]=t2.maxv[i]=t3.maxv[i]=-1e12;//注意初值
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j+l-1<=m;j++)
		{
			f[j]=max(t1.ask(1,1,m,1,j-l),t1.ask(1,1,m,j+l,m));//case 1
			f[j]=max(f[j],t2.ask(1,1,m,j-l+1,j)+s[i][j-1]);//case 2
			f[j]=max(f[j],t3.ask(1,1,m,j+1,j+l)-s[i][j+l-1]);//case 3
			f[j]=max(f[j],0ll);
		}
		for(int j=1;j+l-1<=m;j++)
		{
			f[j]=f[j]+s[i][j+l-1]-s[i][j-1]+s[i+1][j+l-1]-s[i+1][j-1];
			t1.update(1,1,m,j,f[j]);
			t2.update(1,1,m,j,f[j]-s[i+1][j+l-1]);
			t3.update(1,1,m,j,f[j]+s[i+1][j-1]);//单点修改
		}
	}
	printf("%lld\n",t1.ask(1,1,n,1,n));
	return 0;
}
```

---

## 作者：zzr8178541919 (赞：1)

### 题目简述
现在给你一个 $n×m$ 的矩阵，每个位置上都有一个数字 $a_{i,j}$。一开始的时候左右的格子都是白色的。对于每一行，你可以把这一行的某个格子 $(i,j)$ 作为左上角、将 $(min(i+1,n),j+k-1),$ $j\leq m-k+1$ 作为右下角的矩形区域进行染成黑色。一个格子可以被重复染色。最后你要最大化黑色格子的权值之和。

### Solution

我发现还可以用单调队列来做这题，并且复杂度比线段树快一个$log$.

首先比较暴力的$dp$都想得到，记$dp[i][j]:$前$i$行中，第$i$行选了$j$这个位置，在前i行的答案。

有状态转移方程：

```cpp
for(int i=2;i<=n;i++)
{
	for(int j=1;j<=m-k+1;j++)
	{
		int wns=0;
		for(int l=1;l<=m-k+1;l++)
		{
			if(j<=l)
			{
				if(j+k-1<l)
				wns=max(wns,(pre[i][l+k-1]-pre[i][l-1])+(pre[i][j+k-1]-pre[i][j-1])+dp[i-1][l]);
				else
				wns=max(wns,(pre[i][l+k-1]-pre[i][j-1])+dp[i-1][l]);
			}
			else
			{
				if(j>l+k-1)
				wns=max(wns,(pre[i][l+k-1]-pre[i][l-1])+pre[i][j+k-1]-pre[i][j-1]+dp[i-1][l]);
				else
				wns=max(wns,pre[i][j+k-1]-pre[i][l-1]+dp[i-1][l]);
			}
		}	
		dp[i][j]=max(dp[i][j],wns);
	}
}
```

发现中间的这一团东西，将它分成四段。

$(1):1 \ \ \ to \ \ \  j-k$

$(2):j-k+1 \ \ \ to \ \ \ j-1$

$(3):j \ \ \ to \ \ \ j+k-1$

$(4):j+k \ \ \ to \ \ \ n$

$(1),(4)$是可以直接从当前的$dp$数组用类似前缀和的方式预处理出来的,

$(2),(3)$推出状态转移方程，发现其符合类似滑动窗口的转移。

可以用单调队列优化到线性

#### $code:$ 
```cpp
#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long
#define reg register
using namespace std;
const int maxn=2e4+5;
const int mod=1e9;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n,m,k;
int a[55][maxn];
int dp[55][maxn]; // dp[i][j] 
int pre[55][maxn];
int ans=0;
int f[maxn];
int g[maxn];
int dp1[maxn];
int dp2[maxn];
int q[maxn];
int head1=1,tail=0;
int yi=1;
int len1=0,len2=0;
int lin=0;
signed main()
{
	n=read(),m=read(),k=read();
	len1=k-1,len2=k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			pre[i][j]=pre[i][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=m-k+1;i++)
	{
		dp[1][i]=pre[1][i+k-1]-pre[1][i-1];
		f[i]=max(f[i-1],dp[1][i]+pre[2][i+k-1]-pre[2][i-1]);
	}
	for(int i=m-k+1;i>=1;i--)
		g[i]=max(g[i+1],dp[1][i]+pre[2][i+k-1]-pre[2][i-1]);
	head1=1,tail=0;
	for(int j=1;j<=m-k+1;j++)
	{
		while(head1<=tail && j-q[head1]+1>len1)
		head1++;
		while(head1<=tail && dp[1][j]-pre[2][j-1]>=dp[1][q[tail]]-pre[2][q[tail]-1])
		tail--;
		q[++tail]=j;
		dp1[j]=dp[1][q[head1]]-pre[2][q[head1]-1];
	}
	head1=1,tail=0;
	for(int j=m-k+1;j>=1;j--)
	{
		while(head1<=tail && q[head1]-j+1>len2)
		head1++;
		while(head1<=tail && dp[1][j]+pre[2][j+k-1]>=dp[1][q[tail]]+pre[2][q[tail]+k-1])
		tail--;
		q[++tail]=j;
		dp2[j]=dp[1][q[head1]]+pre[2][q[head1]+k-1];
	}	
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m-k+1;j++)
		{
			int wns=0;
			int l1=max(lin,j-k);
			dp[i][j]=max(dp[i][j],f[l1]+pre[i][j+k-1]-pre[i][j-1]);
			int r=min(m-k+2,j+k);			
			dp[i][j]=max(dp[i][j],g[r]+pre[i][j+k-1]-pre[i][j-1]);
			wns=max(dp1[j-1]+pre[i][j+k-1],dp2[j]-pre[i][j-1]);
			dp[i][j]=max(dp[i][j],wns);
		}
		for(int j=1;j<=m-k+1;j++)
		f[j]=max(f[j-1],dp[i][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
		for(int j=m-k+1;j>=1;j--)
		g[j]=max(g[j+1],dp[i][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
		head1=1,tail=0;
		for(int j=1;j<=m-k+1;j++)
		{
			while(head1<=tail && j-q[head1]+1>len1)
			head1++;
			while(head1<=tail && dp[i][j]-pre[i+1][j-1]>=dp[i][q[tail]]-pre[i+1][q[tail]-1])
			tail--;
			q[++tail]=j;
			dp1[j]=dp[i][q[head1]]-pre[i+1][q[head1]-1];
		}
		head1=1,tail=0;
		for(int j=m-k+1;j>=1;j--)
		{
			while(head1<=tail && q[head1]-j+1>len2)
			head1++;
			while(head1<=tail && dp[i][j]+pre[i+1][j+k-1]>=dp[i][q[tail]]+pre[i+1][q[tail]+k-1])
			tail--;
			q[++tail]=j;
			dp2[j]=dp[i][q[head1]]+pre[i+1][q[head1]+k-1];
		}
	}
	for(int i=1;i<=m;i++)
	{	
		ans=max(ans,dp[n][i]);
	}
	printf("%lld\n",ans);
 	return 0;
}
```



---

## 作者：zhmshitiancai (赞：1)

[门门](https://www.luogu.com.cn/problem/CF1304F1)

题意：有一个$n$行$m$列的矩阵，每个格子有一个权值，在每一行，你可以放一个$2\times k$的矩阵，问覆盖到的权值和最大是多少。(覆盖多次只算一次的权值)$n\leq 50, m\leq 2\times 10^4$
## F1(easy version)
$k\leq20$
### solution1(my)
考虑$dp(i,j)$表示看到第$i$行，在第$j$个放的最大和。观察发现，转移时大部分是没有遮挡的，只要能维护最大值就行，对于中间有遮挡的部分，暴力转移即可,复杂度$O(k)$

没有遮挡的转移方程如下：
$$ dp(i,j)=\max(dp(i-1,j1)+sum(i,j,i+1,j+k-1))$$
那么如何维护去掉一块之后的最大值呢？先维护上一行$2k$个最大值，然后对于每一个$j$,最多会有$2k-1$个有遮挡，无遮挡的最大值即为(在预处理出的$2k$个值中，去掉有遮挡的)最大值。
细节见代码。

时间复杂度$O(nmk\log k)$
### solution2
看到$dp(i,j)$ 有三种转移方式

1. 从前面未遮挡的部分转移

1. 从中间有遮挡的部分转移

1. 从后面未遮挡的部分转移

对于2，我们依旧暴力转移

对于1和3，维护上一行$dp$的前缀和后缀最大值即可。

这其实也是惯用套路了，我居然想不到。

## F2(hard)
$k\leq m$

### solution
$k$的范围变大了，考虑用线段树维护。

转移时从线段树种取出最大值，再加上$sum(i,j,i+1,j+k-1))$

那么有遮挡的情况怎么办呢？

在$j-1 \gets j$ 时

先把有遮挡的情况分为两类：
1. 从$j-k$到$j-1$，它们随着$j$的增大，遮挡的部分变少了，且变少的部分都是$a(i,j-1)$，故在线段树中区间加即可。

1. 从$j$到$j+k-1$，它们随着$j$的增大，遮挡的部分变多了，且变少的部分都是$a(i,j+k-1)$，故在线段树中区间减即可。

Tips:
1. 我写代码时居然又把$n,m$写反了。

**code1:**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define pb push_back
#define se second
const int INF=0x3f3f3f3f,N=55,M=2e4+5,K=25;
int n,m,k;
int a[N][M];
int dp[N][M];
int s[N][M];
int mx[N][2*K];
int tot[N];
int sum(int x1,int y1,int x2,int y2)
{
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int l_b(int x,int cur)
{
	int l=1,r=tot[cur],ans=100;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(mx[cur][mid]<x)
		{
			ans=mid;
			r=mid-1;
		}
		else 
			l=mid+1;
	}
	if(ans==100)
		return tot[cur]+1;
	else 
		return ans;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	
	for(i=1;i<=n+1;i++)
		for(j=1;j<=m;j++)
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
		
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)//m-k+1
		{
			if(i==1) dp[i][j]=sum(i,j,i+1,j+k-1);
			else
			{
				vector<int> v;
				for(int j2=max(1,j-k+1);j2<=j;j2++)
				{
					if(dp[i-1][j2]>=mx[i-1][2*k])
						v.pb(dp[i-1][j2]);
					dp[i][j]=max(dp[i][j],dp[i-1][j2]+sum(i,j,i+1,j+k-1)-sum(i,j,i,j2+k-1));
				}
				for(int j2=j+1;j2<=min(m-k+1,j+k-1);j2++)
				{
					if(dp[i-1][j2]>=mx[i-1][2*k])
						v.pb(dp[i-1][j2]);
					dp[i][j]=max(dp[i][j],dp[i-1][j2]+sum(i,j,i+1,j+k-1)-sum(i,j2,i,j+k-1));
				}
				sort(v.begin(),v.end());
				int i1=1,j1=v.size()-1;
				while(i1<=tot[i-1]&&j1>=0)
				{
					if(mx[i-1][i1]>v[j1])
					{
						break;
					}
					if(mx[i-1][i1]==v[j1])
					{
						i1++;
						j1--;
						continue;
					}
				//	cout<<mx[i1]<<" "<<v[j1]<<endl;
					//if(v[j1])
				}
				dp[i][j]=max(dp[i][j],mx[i-1][i1]+sum(i,j,i+1,j+k-1));	
			}
			int pos=l_b(dp[i][j],i),i1;
			if(pos>2*k) continue;
			for(i1=tot[i];i1>=pos;i1--)
				mx[i][i1+1]=mx[i][i1];
			mx[i][pos]=dp[i][j];
			tot[i]++;
			if(tot[i]>2*k) tot[i]=2*k;
			
		}
	}
	int ans=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)
			ans=max(ans,dp[i][j]);
	}
	cout<<ans<<endl;
}
```

**code2:**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define pb push_back
#define se second
const int INF=0x3f3f3f3f,N=55,M=2e4+5,K=25;
int n,m,k;
int a[N][M];
int dp[N][M];
int s[N][M];
int lmax[M],rmax[M];
int sum(int x1,int y1,int x2,int y2)
{
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	
	for(i=1;i<=n+1;i++)
		for(j=1;j<=m;j++)
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
		
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)//m-k+1
		{
			if(i==1) dp[i][j]=sum(i,j,i+1,j+k-1);
			else
			{
				for(int j2=max(1,j-k+1);j2<=j;j2++)
					dp[i][j]=max(dp[i][j],dp[i-1][j2]+sum(i,j,i+1,j+k-1)-sum(i,j,i,j2+k-1));
				for(int j2=j+1;j2<=min(m-k+1,j+k-1);j2++)
					dp[i][j]=max(dp[i][j],dp[i-1][j2]+sum(i,j,i+1,j+k-1)-sum(i,j2,i,j+k-1));
				if(j-k>=1)
					dp[i][j]=max(dp[i][j],lmax[j-k]+sum(i,j,i+1,j+k-1));
				if(j+k<=m-k+1)
					dp[i][j]=max(dp[i][j],rmax[j+k]+sum(i,j,i+1,j+k-1));
			}
		}
//		memset(lmax,0,sizeof lmax);
//		memset(rmax,0,sizeof rmax);
		for(j=1;j<=m-k+1;j++)
			lmax[j]=max(lmax[j-1],dp[i][j]);
			
		for(j=m-k+1;j>=1;j--)
			rmax[j]=max(rmax[j+1],dp[i][j]);
		
//		for(j=1;j<=m-k+1;j++)
//			cout<<lmax[j]<<" ";
//		cout<<endl;
//		
//		for(j=1;j<=m-k+1;j++)
//			cout<<rmax[j]<<" ";
//		cout<<endl;
	}
//	for(i=1;i<=n;i++)
//	{
//		for(j=1;j<=m-k+1;j++)
//			cout<<dp[i][j]<<" ";
//		cout<<endl;
//	}
	int ans=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)
			ans=max(ans,dp[i][j]);
	}
	cout<<ans<<endl;
}
```

**code3:**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define pb push_back
#define se second
const int INF=0x3f3f3f3f,N=55,M=2e4+5,K=25;
int n,m,k;
int a[N][M];
int dp[N][M];
int s[N][M];
int sum(int x1,int y1,int x2,int y2)
{
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
struct node{
	int mx,l,r,del;
}tr[M*4];
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
void build(int x,int l,int r)
{
	tr[x].l=l;tr[x].r=r;
	tr[x].del=0;tr[x].mx=0;
	if(l!=r)
	{
		int mid=l+r>>1;
		build(ls(x),l,mid);
		build(rs(x),mid+1,r);
	}
}
void pushup(int x)
{
	tr[x].mx=max(tr[ls(x)].mx+tr[ls(x)].del,tr[rs(x)].mx+tr[rs(x)].del);
}
void update(int x,int l,int r,int y)
{
	if(l<=tr[x].l&&tr[x].r<=r)
	{
		tr[x].del+=y;
		return ;
	}
	tr[ls(x)].del+=tr[x].del;
	tr[rs(x)].del+=tr[x].del;
	tr[x].del=0;
	
	if(l<=tr[ls(x)].r)
		update(ls(x),l,r,y);
	if(r>=tr[rs(x)].l)
		update(rs(x),l,r,y);
	
	pushup(x);
}
int query(int x,int l,int r)
{
	if(l<=tr[x].l&&tr[x].r<=r)
	{
		return tr[x].del+tr[x].mx;
	}
	tr[ls(x)].del+=tr[x].del;
	tr[rs(x)].del+=tr[x].del;
	tr[x].del=0;
	
	int ans=0;
	if(l<=tr[ls(x)].r)
		ans=max(ans,query(ls(x),l,r));
	if(r>=tr[rs(x)].l)
		ans=max(ans,query(rs(x),l,r));
	
	pushup(x);
	return ans;
}
void print()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)
			cout<<dp[i][j]<<" ";
		cout<<endl;
	}	
	cout<<endl;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	cin>>n>>m>>k;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	
	for(i=1;i<=n+1;i++)
		for(j=1;j<=m;j++)
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
		
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)//m-k+1
		{
			if(i==1) dp[i][j]=sum(i,j,i+1,j+k-1);
			else
			{
//				cout<<i<<" "<<j<<endl;
				if(j!=1)
				{
					int j2=max(1,j-k);
					update(1,j2,j-1,a[i][j-1]);
					j2=min(m-k+1,j+k-1);
					update(1,j,j2,-a[i][j+k-1]);					
				}

				
				dp[i][j]=query(1,1,m+k-1)+sum(i,j,i+1,j+k-1);
			}
		}
//		print();
		build(1,1,m);
		for(j=1;j<=min(m-k+1,k);j++){
			update(1,j,j,dp[i][j]-sum(i+1,j,i+1,k));
		}
		for(j=k+1;j<=m-k+1;j++)
			update(1,j,j,dp[i][j]);
	}
	int ans=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m-k+1;j++)
			ans=max(ans,dp[i][j]);
	}
	cout<<ans<<endl;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF1304F1)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难想到用 DP 解决这道题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于每个摄像头只会检测两天，所以只会有前一天的摄像头影响后一天摆放的情况。因此我们在状态中加入前一行的摄像头的位置。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这里先自行规定一下。如果$k$为奇数，那么一个摄像头在$x$则会监视到$[x-\lfloor\frac k 2\rfloor,x+\lfloor\frac k 2\rfloor]$这个范围。如果$k$为偶数，则会监视到$[x-\lfloor\frac{k-1}2\rfloor,x+\lfloor\frac k 2\rfloor]$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$lef(x)$为$x$的左边界，$rig(x)$为$x$的右边界。设$L$为每一行能放摄像头的最左位置，$R$为最右位置。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是可以列出如下的状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i,x)$：前$i$行中，第$i-1$行的摄像头摆在$x$位置的最优方案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$g(i,[l,r])=\sum_{k=l}^ra_{i,k}$，$h(i,x)=g(i,[lef(x),rig(x)])$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们不难想到如下转移：  
$$f(i,x)=\max_{L\le y\le R}\{f(i-1,y)+h(i,y)+h(i,x)-g(i,S)\}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中$S$表示两个摄像头相交区间。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;两个区间$[l_1,r_1],[l_2,r_2]$相交，首先要$\max(l_1,l_2)\le \min(r_1,r_2)$，并且相交区间就是$[\max(l_1,l_2),\min(r_1,r_2)]$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果这样暴力转移，时间是$O(nm^2)$，T 了。考虑优化。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;可以发现，由于$k\le20$，所以相交的区间不会太多。如果两个区间不相交，那么这个转移方程就可以简化为：  
$$f(i,x)=\max\{f(i-1,y)+h(i,y)\}+h(i,x)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此转移仅与$y$有关。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;并且不难发现，会与$x$相交的区间所对应的的摄像头的位置，本身也是一个区间。手推会发现这个区间就是$(x-k,x+k)$。剩余的部分，可以将区间减法转化为两段区间加法，通过预处理前后缀最值的方式直接转移；而存在相交区间的转移就直接暴力转移。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于会相交的区间只有$O(k)$个，所以转移的时间复杂度是$O(nmk)$。  
# 代码
```cpp
#include <cstdio>

const int INF = 0x3f3f3f3f;
const int MAXN = 55, MAXM = 2e4 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

int f[MAXN][MAXM], pMx[MAXM], sMx[MAXM];
int a[MAXN][MAXM], s[MAXN][MAXM];
int N, M, K, llen, rlen;

int getL( const int x ) { return x - llen; }
int getR( const int x ) { return x + rlen; }
int getS( const int x, const int l, const int r ) { return s[x][r] - s[x][l - 1]; }
int query( const int x, const int mid ) { return getS( x, mid - llen, mid + rlen ); }

int main()
{
	read( N ), read( M ), read( K );
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= M ; j ++ ) 
			read( a[i][j] ), s[i][j] = s[i][j - 1] + a[i][j];
	int lef = K + 1 >> 1, rig = M - ( K >> 1 ); 
	llen = K - 1 >> 1, rlen = K >> 1;
	for( int i = lef ; i <= rig ; i ++ ) f[1][i] = query( 1, i );
	for( int i = 2, cost ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ ) pMx[j] = sMx[j] = -INF;
		for( int j = lef ; j <= rig ; j ++ ) pMx[j] = MAX( pMx[j - 1], f[i - 1][j] + query( i, j ) );
		for( int j = rig ; j >= lef ; j -- ) sMx[j] = MAX( sMx[j + 1], f[i - 1][j] + query( i, j ) ); 
		for( int j = lef ; j <= rig ; j ++ )
		{
			f[i][j] = -INF;
			for( int k = MAX( lef, j - K + 1 ) ; k <= MIN( rig, j + K - 1 ) ; k ++ )
			{
				cost = getS( i, MAX( getL( k ), getL( j ) ), MIN( getR( k ), getR( j ) ) );
				f[i][j] = MAX( f[i][j], f[i - 1][k] + query( i, k ) + query( i, j ) - cost ); 
			}
			if( j - K >= lef ) f[i][j] = MAX( f[i][j], pMx[j - K] + query( i, j ) );
			if( j + K <= rig ) f[i][j] = MAX( f[i][j], sMx[j + K] + query( i, j ) );
		}
	}
	int ans = -INF;
	for( int i = lef ; i <= rig ; i ++ ) ans = MAX( ans, f[N][i] );
	write( ans ), putchar( '\n' );
	return 0;
}
```

---

## 作者：intel_core (赞：0)

先胡一个比较 `naive` 的做法：

先记 $s_i[l,r]$ 表示第 $i$ 行 $[l,r]$ 位置的数的和。

* $f_{i,j}$ 表示考虑到第 $i$ 行，且第 $i$ 行选的矩形的左边界是 $j$ 的最大值。

* 转移的时候从 $f_{i-1,p}$，直接 $f_{i,j}=f_{i-1,p}+s_i[p,p+k-1] \bigcup [j,j+k-1]$，讨论 $[p,p+k-1]$ 与 $[j,j+k-1]$ 是否相交即可。

复杂度 $O(nm^2)$，差点意思。

由于 $k \le 20$，所以一个区间至多与 $40$ 个区间相交，不相交的情况浪费了大量转移时间。

只需要处理 $f_{i-1}$ 的前缀/后缀最大值，然后单次 $O(k)$ 枚举相交的区间即可。

复杂度 $O(nmk)$，这里采用的是单调队列 $O(nm)$ 的写法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=55;
const int MR=2e4+10;
#define int long long
int n,m,k,a[NR][MR],f[NR][MR];
int pre[MR],suf[MR],sum[NR][MR];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]),sum[i][j]=sum[i][j-1]+a[i][j];
	for(int i=1;i<=n;i++){
		memset(pre,0,sizeof(pre));
		memset(suf,0,sizeof(suf));
		if(i>1)
			for(int j=1;j<=m-k+1;j++)f[i-1][j]+=sum[i][j+k-1]-sum[i][j-1];
		for(int j=1;j<=m-k+1;j++)pre[j]=max(pre[j-1],f[i-1][j]);
		for(int j=m-k+1;j>=1;j--)suf[j]=max(suf[j+1],f[i-1][j]);
		for(int j=1;j<=m-k+1;j++)
			f[i][j]=max(pre[max(0ll,j-k)],suf[min(m-k+2,j+k)])+sum[i][j+k-1]-sum[i][j-1];
		deque<int>q;
		for(int j=1;j<=m-k+1;j++){
			while(!q.empty()&&q.front()<=j-k)q.pop_front();
			while(!q.empty()&&f[i-1][q.back()]-sum[i][q.back()+k-1]<=f[i-1][j]-sum[i][j+k-1])q.pop_back();
			q.push_back(j);
			if(!q.empty())f[i][j]=max(f[i][j],f[i-1][q.front()]-sum[i][q.front()+k-1]+sum[i][j+k-1]);
		}
		q.clear();
		for(int j=m-k+1;j>=1;j--){
			while(!q.empty()&&q.front()>=j+k)q.pop_front();
			while(!q.empty()&&f[i-1][q.back()]+sum[i][q.back()-1]<=f[i-1][j]+sum[i][j-1])q.pop_back();
			q.push_back(j);
			if(!q.empty())f[i][j]=max(f[i][j],f[i-1][q.front()]+sum[i][q.front()-1]-sum[i][j-1]);
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++)ans=max(ans,f[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

