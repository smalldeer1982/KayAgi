# 「EZEC-10」Covering

## 题目描述

给你一个 $n\times m$ 的棋盘和 $k$ 张 $1\times 2$ 的纸片，编号 $1$ 到 $k$。

你可以任意选择数量在 $[l,r]$ 内的纸片，并按照编号从小到大的顺序，依次横放或竖放在棋盘上。

**注意：后放的纸片会覆盖在先放的纸片上。**

给定最终棋盘中每个格子上的纸片编号，求满足条件的不同方案数，并对 $10^9+7$ 取模。

**两种方案相同，当且仅当两方案选择的纸片数量、纸片编号及每张纸片的摆放位置均相同。**

## 说明/提示

**【样例 1 解释】**

不难发现只能取编号为 $1,2,3$ 的纸片，此时共有 $2$ 种方案：

$1:(1,1)\to (1,2)$，$2:(1,2)\to (2,2)$，$3:(2,1)\to (2,2)$；

$1:(1,1)\to (2,1)$，$2:(1,2)\to (2,2)$，$3:(2,1)\to (2,2)$。

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（5 points）：$r=1$。
-  Subtask 2（10 points）：$n,m,k\le 5$。
-  Subtask 3（15 points）：$l=k$。
-  Subtask 4（20 points）：$n\times m\le 10^3$。
-  Subtask 5（50 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10$，$2\le n,m,k\le 10^3$，$1\le l\le r\le k$。

## 样例 #1

### 输入

```
1
2 2 4 2 4
1 2
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
2 2 4 2 3
0 0
2 2
2 2 4 2 2
1 1
3 3```

### 输出

```
1
1```

# 题解

## 作者：绝顶我为峰 (赞：11)

非常明显的，这是一个 dp 题目。

$n,m,k\leq10^3$，允许我们设计二维状态来 dp。记 $dp_{i,j}$ 表示在前 $i$ 个纸片中选择 $j$ 个的方案数。

发现 $k$ 并没有什么用，因为实际上我们只能编号不超过棋盘中最大的编号，记作 $maxn$。

考虑转移，分情况讨论：

- $i$ 在棋盘上出现了两次：显然纸片只能放在固定一个位置，$dp_{i,j}=dp_{i-1,j-1}$。

- $i$ 在棋盘上出现了一次：纸片的一端固定在这个点，另一端可以在上下左右四个点选取，但因为 $i$ 最终被覆盖了，所以上下左右可选的点必须编号比 $i$ 大。记合法数量为 $tag$，那么 $dp_{i,j}=tag·dp_{i-1.j-1}$。

- $i$ 没有在棋盘上出现：这时可选可不选，不选显然直接对应转移，关键是如果选了这个纸片，我们要计算可以放这个纸片的位置有多少。我们发现必须要相邻两个点的编号均大于 $i$，纸片才能放在这里。也就是说，我们假设相邻两点的编号较小值是 $p$，那么这个位置会对 $1\sim p-1$ 的位置产生贡献，这个可以求一遍前缀和简单地得到。于是这个转移也是 $O(1)$ 的，记刚才预处理的可放位置是 $sum_i$，那么 $dp_{i,j}=dp_{i-1,j}+sum_i·dp_{i-1,j-1}$。

然后需要注意一下下界的选取。因为出现在棋盘上的编号是必须选取的，我们需要统计这个数字，记作 $cnt$，转移的时候强制从 $cnt+1$ 开始转移，否则会出错。

最后，答案就是 $\sum_{i=\max{l,cnt}}^rdp_{maxn,i}$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
const int mod=1000000007;
int t,n,m,k,l,r,dp[2001][2001],mp[2001][2001],sum[20005],maxn,ans,cnt;
pair<int,int> vis[20001];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
signed main()
{
    t=read();
    while(t--)
    {
        n=read(),m=read(),k=read(),l=read(),r=read();
        memset(sum,0,sizeof sum);
        memset(vis,0,sizeof vis);
        memset(dp,0,sizeof dp);
        memset(mp,0,sizeof mp);
        maxn=cnt=0;
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j)
            {
                mp[i][j]=read();
                if(!mp[i][j])
                    continue;
                maxn=max(maxn,mp[i][j]);
                vis[mp[i][j]]=make_pair(i,j);
                if(i>1&&mp[i-1][j])
                    ++sum[min(mp[i-1][j],mp[i][j])];
                if(j>1&&mp[i][j-1])
                    ++sum[min(mp[i][j-1],mp[i][j])];
            }
        for(register int i=k;i>=1;--i)
            sum[i]=(sum[i]+sum[i+1])%mod;
        dp[0][0]=1;
        for(register int i=1;i<=maxn;++i)
            if(vis[i].first)
            {
                for(register int j=0;j<cnt;++j)
                    dp[i][j]=0;
                dp[i][cnt]=dp[i-1][cnt];
                int x=vis[i].first,y=vis[i].second;
                if(mp[x-1][y]==i||mp[x+1][y]==i||mp[x][y-1]==i||mp[x][y+1]==i)
                {
                    for(register int j=cnt+1;j<=r;++j)
                        dp[i][j]=dp[i-1][j-1];
                    ++cnt;
                    continue;
                }
                int tag=(mp[x-1][y]>i)+(mp[x+1][y]>i)+(mp[x][y-1]>i)+(mp[x][y+1]>i);
                for(register int j=cnt+1;j<=r;++j)
                    dp[i][j]=tag*dp[i-1][j-1]%mod;
                ++cnt;
            }
            else
            {
                dp[i][cnt]=dp[i-1][cnt];
                for(register int j=0;j<cnt;++j)
                    dp[i][j]=0;
                for(register int j=cnt+1;j<=r;++j)
                    dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]*sum[i]%mod)%mod;
            }
        ans=0;
        for(register int i=max(cnt,l);i<=r;++i)
            ans=(ans+dp[maxn][i])%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：chager (赞：5)

考场上做出来的一道绿题……感悟颇深，在这里写一发。

首先介绍一个 $O(n \times m \times log(nm))$ 的做法，也是我考场上想到的第一个比较优秀的做法：

我们对于每一个点按照其上的数字大小从大到小排序，因为题目保证有解，所以每一个数字出现次数绝对不超过 $2$ 次。

排完序后我们从前往后扫，同时我们维护目前空纸片（即该数字未出现在输入数据中的纸片）能摆放的位置有多少；

所以我们新开一个数组 $f$，并对每一种数字进行以下操作：
1. 如果这个数字出现次数为两次，那么它只可能有这1种放置方法，此时我们只需要维护空纸片摆放位置多了多少；
1. 如果这个数字出现次数为一次，那么它可能有多种放法，考虑其周围（上下左右）有多少格子比它大，这张纸片能摆放的位置就有多少（此时更新一下答案 $ans$）；同时维护空纸片摆放位置多了多少；
1. 如果这个数字没有出现过，那么我们将 $f_i$ 设为当前空纸片摆放位置并继续；

_注：维护空纸片摆放位置的方法：对于每一个新的被扫到的点，看有多少包含它且另一个数字比它大的 1$\times$2 的小方格，对于以上第 1 种情况特判一下，要额外 +1。_

然后，我们设 $dp_i$ 表示目前选择放置了 $i$ 个数的方案，初值设为 $dp_{w} = ans$ （ $w$ 为上面1、2两种出现的次数）我们再从 $1$ 到 $k$ ( $k$ 为出现数字的最大值)扫描一遍，对于每一个没有出现过的数字 $i$ ，我们更新 $dp$ 数组：

$$j=k-1 \to 1,dp_{j+1}+=dp_j \times f_i$$

最后 $\sum\limits_{i=l}^r dp_i$ 即为答案；

关于优化至 $O(n\times m)$：

比较简单的是把以上操作的快排改为桶排；

或者可以直接不排序，按任意顺序操作；此时设 $hzh_i=$ 在扫到数字 $i$ 时增加了多少空纸片摆放位置，最后 $dp_i=\sum\limits_{j=i+1}^nhzh_j$。

本人考场上用的是第二种方法。

还有一点温馨提示：

**多测不清空，爆0两行泪**

(本人考场上直接因为这个东西浪费1h+……)

代码（第二种优化）：

```cpp
# include <stdio.h>
# include <algorithm>
# define int long long
int a[1010][1010];
int ff[1010],f[1010],z[1010],bj[1010],hzh[1010],ok[1010];
int anss=1;
int mod=1000000007;
void done(int x,int y)
{
	int p=x,q=y;
	anss*=(a[p][q+1]>a[x][y])+(a[p+1][q]>a[x][y])+(a[p-1][q]>=a[x][y])+(a[p][q-1]>=a[x][y]);
	anss%=mod;
	return;
}
void gx(int x,int y)
{
	int p=x,q=y;
	hzh[a[x][y]]+=(a[p][q+1]>a[x][y])+(a[p+1][q]>a[x][y])+(a[p-1][q]>a[x][y])+(a[p][q-1]>a[x][y]);
	return;
}
int pan(int x,int y)
{
	int p=x,q=y;
	if(a[p][q+1]==a[x][y] || a[p+1][q]==a[x][y] || a[p-1][q]==a[x][y] || a[p][q-1]==a[x][y])
		return 1;
	else
		return 0;
}
int read()
{
	int now=0;
	char c=getchar();
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		now=(now<<1)+(now<<3)+(c&15);
		c=getchar();
	}
	return now;
}
signed main()
{
	int i,j,n,m,k,l,r,t,x,y,mx=0;
	t=read();
	while(t--)
	{
		n=read();
		m=read();
		k=read();
		l=read();
		r=read();
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				x=read();
				if(!bj[x] && x)
				{
					bj[x]=1;
					mx++;
				}
				else
				{
					bj[x]++;
					if(bj[x]>2 && x)
						while(1){}
				}
				a[i][j]=x;
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(!a[i][j])
					continue;
				if(ok[a[i][j]])
					continue;
				if(pan(i,j))
				{
					gx(i,j);
					if(a[i-1][j]==a[i][j])
						gx(i-1,j);
					if(a[i+1][j]==a[i][j])
						gx(i+1,j);
					if(a[i][j-1]==a[i][j])
						gx(i,j-1);
					if(a[i][j+1]==a[i][j])
						gx(i,j+1);
					hzh[a[i][j]]++;
					ok[a[i][j]]=1;
					continue;
				}
				if(bj[a[i][j]]>=2) while(1){}
				done(i,j);
				gx(i,j);
			}
		}
		f[mx]=anss;
		for(i=1000;i>=1;i--)
		{
			hzh[i]+=hzh[i+1];
			hzh[i]%=mod;
		}
		for(i=1;i<=1000;i++)
		{
			if(bj[i] || i>k)
				continue;
			ff[i]=hzh[i+1];
			for(j=2;j<=1000;j++)
			{
				z[j]=f[j-1]*ff[i];
				z[j]%=mod;
			}
			for(j=2;j<=1000;j++)
			{
				f[j]+=z[j];
				f[j]%=mod;
				z[j]=0;
			}
		}
		anss=0;
		for(i=l;i<=r;i++)
		{
			anss+=f[i];
			anss%=mod;
		}
		printf("%lld\n",anss);
		anss=1;
		mx=0;
		for(i=1;i<=1000;i++)
		{
			f[i]=0;
			z[i]=0;
			ff[i]=0;
			bj[i]=0;
			hzh[i]=0;
			ok[i]=0;
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				a[i][j]=0;
		}
	}
	return 0;
}

```
其中 $f$ 数组相当于上文的 $dp$ 数组，上文的 $f$ 数组在代码中直接用 $hzh$ 数组一并表示了。

---

## 作者：Ckger (赞：4)

这里介绍一下考场上想出来的做法，复杂度 $O(k^{2})$，但是一般跑不满，所以表现还是不错的（赛后吸口氧跑到了最优解第一名????）。主要思想就是先在输入的图上，由编号从大到小扫描，记录可能的状态（因为纸片编号固定，统一编号只有可能是同一张纸片的，因此可以记录可能的状态）。

举个例子，就如样例：

```
1 2
3 3
```
先扫到 $3$，发现3出现了两次，即 $3$ 的可能状态为1。

再扫描到 $2$ ，发现 $2$ 只出现了一次，然而能在$2$放下后遮住$2$的摆放方式只有竖放（因为是从大到小扫描，只需再开一个b数组记录已经放有纸片的位置，$O(1)判断即可$），即 $2$ 的可能状态也为1。

最后扫描到$1$，发现$1$横放竖放皆可，即 $1$ 有两种可能。

最后，将所有纸片的可能情况进行累乘，即 $1\times1\times2=2$，这么就得到了样例 $1$ 的答案。

但是对于藏在地下的纸片，又怎么处理呢？

也很简单，在从大到小扫描时，对于不可见的编号的纸片，使用变量 $cnt$ 记录一下当前的可能状态。那怎么维护 $cnt$ 呢，只需要在更新可见纸片（即输入时有编号的纸片）时，加上此纸片覆盖之后的贡献即可。

举个例子：

```
0 0 0
0 0 2
1 1 2
```
我们先扫描到 $2$，$cnt$ 值为 $1$，表示此时不可见的纸片此时有一种方案摆放。这时我们扫描到 $1$，我们又多了两种方式：
```
0 0 0          0 0 0
0 0 0          0 0 0
1 1 0          0 1 1
```
$1$ 表示摆放了纸片。

也就是说，对于新纸片的每一个位置，只要上下左右原本就有纸片，则 $cnt$ 加上 $1$，并将这个位置插入 $b$ 数组（记录覆盖纸片位置）中。

这下，知道了各种纸片的方案，只剩下最后一个问题：我们还限制了纸片的数量，怎么样计算各种不同纸片组合带来的答案呢？

设原来图中就出现的纸片数量为 $js$，则不可见的纸片还可以选取 $(l-js)$ ~ $(r-js)$ 个。

于是问题就转化为：

一列数： $a_1,a_2,a_3......a_k$，从中找出个数为 $m$ 的组合，令组合中每个数相乘，求出所有组合乘积的和。设可见纸片的可能种数为 $tmp$，最后的 $ans=tmp+tmp\times f_{k,i}$，其中 $l-js\leqslant i\leqslant  r-js$，$f_{k,i}$ 即为 $k$ 个数中选出 $i$ 个数组合的乘积的和（同上）。

至于 $f_{k,m}$，我们可以用 $DP$ 解决。

设 $f_{i,j}$ 为在 $a_1至a_i$ 中，选出个数为 $j$ 的组合，令组合中每个数相乘，所有组合乘积的和。那么不难得出 $f_{i,j}=f_{i-1,j-1} \times a_i + f_{i-1,j}$。

举个例子：

在 $a_1,a_2,a_3,a_4$ 中选出 $3$ 个相乘的和(即求出 $a_1 \times a_2 \times a_3 + a_1\times a_3\times a_4+a_2\times a_3\times a_4$ )

要求 $f_{4,3}$，我们先求出 $f_{3,2}$，即 $a_1\times a_2+a_1\times a_3+a_2\times a_3$，将其乘上 $a_4$，这样每一项中都含有 $a_4$，再加上没有 $a_4$ 的项，即加上 $f_{3,3}$，我们便完成了转移。

关于统计会不会重复，答案是否定的。因为编号小的纸片一定先放，所以对于每种摆放，他的方案一定唯一。

如果还没看懂，可以对照代码理解一下。

code:
```cpp
#include<bits/stdc++.h>
#define foir(i,l,r) for (register long long i=l;i<=r;++i)
#define fopr(i,l,r) for (register long long i=l;i>=r;--i)
#define maxn 1010
#define zhw 1000000007
using namespace std;

inline long long read()
{
	long long x=0;bool f=0;char c=getchar();
	while (!isdigit(c)) f|=c=='-',c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x;
}

inline long long Max(long long a,long long b) {return a>b?a:b;}
inline long long Min(long long a,long long b) {return a<b?a:b;}

long long t,m,n,l,r,k,p;
long long a[maxn][maxn],b[maxn][maxn];
long long x[maxn],y[maxn],sum[maxn],cnt,tot;
long long f[maxn][maxn],ans;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

inline long long check(long long u)
{
	long long res=0;
	b[x[u]][y[u]]=u;
	foir(i,0,3)
	{
		if (x[u]+dx[i]>n||x[u]+dx[i]<1||y[u]+dy[i]>m||y[u]+dy[i]<1) continue;
		if (b[x[u]+dx[i]][y[u]+dy[i]])
			++cnt;
	}
	foir(i,0,3)
	{
		if (x[u]+dx[i]>n||x[u]+dx[i]<1||y[u]+dy[i]>m||y[u]+dy[i]<1) continue;
		if (a[x[u]+dx[i]][y[u]+dy[i]]==u)
		{
			b[x[u]+dx[i]][y[u]+dy[i]]=u;
			foir(j,0,3)
				if (b[x[u]+dx[i]+dx[j]][y[u]+dy[i]+dy[j]])
					++cnt;
			return 1;
		}
		else if (b[x[u]+dx[i]][y[u]+dy[i]])
			++res;
	}
	return res;
}

int main()
{
	t=read();
	while (t--)
	{
		long long js=0;
		tot=cnt=0;
		ans=1;
		p=0;
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		memset(f,0,sizeof f);
		memset(sum,0,sizeof(sum));
		memset(b,0,sizeof(b));
		n=read(),m=read(),k=read(),l=read(),r=read();
		foir(i,1,n)
			foir(j,1,m)
				a[i][j]=read(),x[a[i][j]]=i,y[a[i][j]]=j,p=Max(p,a[i][j]);
		fopr(i,p,1)
		{
			if (x[i])
				ans*=check(i),ans%=zhw,++js;
			else
				sum[++tot]=cnt,cnt%=zhw;
		}
		foir(i,1,tot)
			f[i][1]=(f[i-1][1]+sum[i])%zhw;
		foir(j,2,tot)
			foir(i,1,tot)
				f[i][j]=(f[i-1][j-1]*sum[i]%zhw+f[i-1][j])%zhw;
		f[tot][0]=1;
		long long tmp=0;
		foir(i,Max(l-js,0),Min(tot,r-js))
			tmp=(tmp+ans*f[tot][i]%zhw)%zhw;
		cout<<tmp<<endl;
	}
	return 0;
}
/*
1
3 3 10 8 10
1 10 5
2 10 6
3 3 6
312
*/
```


---

## 作者：Ecrade_ (赞：3)

考虑从 $k$ 到 $1$ 枚举编号。

令当前编号为 $x$，分三种情况讨论：

- $x$ 在棋盘中出现两次，对答案无贡献。

- $x$ 在棋盘中出现一次，对答案的贡献为：上下左右四个格子中，编号大于 $x$ 的格子个数。

- $x$ 未出现在棋盘中，可任意摆放在编号均大于 $x$ 的相邻两格子中或不摆放。

注意到控制纸片数量的是第三种情况。

若棋盘中出现了 $k-y$ 种不同的编号（不包括 $0$），那么第三种情况中选择摆放的纸片数量应在 $[\max(0,l-(k-y)),r-(k-y)]$ 内。

令所有未出现在棋盘中的纸片可摆放位置个数组成的集合 $S=\{p_1,p_2,...,p_y\}$。

定义一个集合的值为其所有元素的积。

那么第三种情况对答案的总贡献即为：$S$ 中元素个数在 $[\max(0,l-(k-y)),r-(k-y)]$ 内的所有子集的值之和。

这部分可以通过生成函数 + 分治 NTT 优化到 $O(y\log^2 y)$，这里介绍一种 $O(y^2)$ 的 $\text{DP}$。

令 $f_{i,j}$ 表示 $\{p_1,p_2,...,p_i\}$ 中，元素个数恰为 $j$ 的所有子集的值之和。

易得转移方程为：

$$f_{i,j}=p_i\times f_{i-1,j-1}+f_{i-1,j}$$

答案即为 $\sum\limits^{r-(k-y)}_{i=\max(0,l-(k-y))}f_{n,i}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m,k,l,r,ans,res,cnt,valid,num[1009],a[1009][1009],v[1009][1009],f[1009][1009],mod = 1e9 + 7;
struct st{ll x[2],y[2],cnt;}p[1009];
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
ll calc(ll x,ll y){ return (a[x][y] < a[x + 1][y]) + (a[x][y] < a[x - 1][y]) + (a[x][y] < a[x][y + 1]) + (a[x][y] < a[x][y - 1]);}
void upd(ll x,ll y){ valid += v[x + 1][y] + v[x - 1][y] + v[x][y + 1] + v[x][y - 1],v[x][y] = 1;}
int main(){
	t = read();
	while (t --){
		ans = 1,res = cnt = valid = 0;
		n = read(),m = read(),k = read(),l = read(),r = read();
		for (ll i = 1;i <= k;i += 1) p[i].cnt = 0;
		for (ll i = 1;i <= n + 1;i += 1) for (ll j = 1;j <= m + 1;j += 1) a[i][j] = v[i][j] = 0;
		for (ll i = 1;i <= n;i += 1) for (ll j = 1;j <= m;j += 1){
			a[i][j] = read();
			if (a[i][j]) p[a[i][j]].x[p[a[i][j]].cnt] = i,p[a[i][j]].y[p[a[i][j]].cnt ++] = j;
		}
		for (ll i = k;i >= 1;i -= 1){
			if (!p[i].cnt) num[++ cnt] = valid;
			else if (p[i].cnt == 1) ans = ans * calc(p[i].x[0],p[i].y[0]) % mod,upd(p[i].x[0],p[i].y[0]);
			else upd(p[i].x[0],p[i].y[0]),upd(p[i].x[1],p[i].y[1]);
		}
		f[cnt][0] = 1;
		for (ll i = 1;i <= cnt;i += 1) f[i][1] = (f[i - 1][1] + num[i]) % mod;
		for (ll i = 2;i <= cnt;i += 1) for (ll j = 2;j <= i;j += 1) f[i][j] = (num[i] * f[i - 1][j - 1] % mod + f[i - 1][j]) % mod;
		for (ll i = max(0ll,l - k + cnt);i <= r - k + cnt;i += 1) res = (res + f[cnt][i]) % mod;
		printf("%lld\n",ans * res % mod);
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：2)

### 思路

我们发现，如果从前往后思考，就会因为纸片直接的遮盖出现非常多的情况，根本无从下手。所以，我们尝试 **逆向思考**，从最后一张考虑到第一张，这样放置纸片的时候，就从放在最上方变成放在最底端。如果一个格子里放上了一张纸片，那么它就再也不会改变了。

根据这个性质，如果要放置第 $i$ 张纸片，有这么几种情况：

1. 第 $i$ 张纸片已经出现了两次，显然只有一种方案就是放在那两个格子里。
2. 第 $i$ 张纸片只出现了一次，那么就以它为起点，向上下左右四格看看有没有已经覆盖过的格子，它能够放置的方案数就是四周覆盖的格子总数。
3. 第 $i$ 张纸片并没有出现，那么所有在当前棋盘上 $1\times 2$ 或 $2\times 1$ 的连通块上都可以放。在程序中，可以提前用一个变量记录它，并在有新格子被覆盖时更改。

不仅如此，设 $Max$ 为在最终棋盘上编号最大的纸片，那么就不可能放置任意一张编号大于 $Max$ 的纸片（因为没有其它纸片遮盖它，必然会出现在最终棋盘上）。而且，我们发现，纸片也分为两类——有用的（出现在了最终棋盘上）和没用的（未出现）。

统计方案数时，先将所有有用的纸片的方案数乘起来。对于没有用的纸片，其方案数可以任意组合，那么方案数就可以看作价值，$1$ 可以看作数量，就变成了一个 **01 背包问题**。最后的答案可以将两部分的答案乘起来。

时间复杂度 $O(n^2)$（ $n,m,k$ 同阶 ）。**注意多测时数据要清空**。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Maxn=1e3,drx[4]={1,0,-1,0},dry[4]={0,1,0,-1};
const ll Mod=1000000007;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int T,n,m,k,l,r,Max,ids,nowt,a[Maxn+5][Maxn+5]; // nowt: 统计连通块数量
int vis[Maxn+5][2][2],chk[Maxn+5],ans[Maxn+5]; // chk: 编号出现次数
int brd[Maxn+5][Maxn+5];
ll all=1ll,allinall=0ll,f[Maxn+5];
inline void Add(int x,int y)
{for(int i=0;i<4;++i) nowt=nowt+brd[x+drx[i]][y+dry[i]];}

int main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read(),k=read(),l=read(),r=read(),all=1ll,allinall=0ll,nowt=ids=Max=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				a[i][j]=read();
				if(a[i][j]!=0 && !chk[a[i][j]]) vis[a[i][j]][0][0]=i,vis[a[i][j]][0][1]=j,chk[a[i][j]]=1;
				else if(a[i][j]!=0 && chk[a[i][j]]) vis[a[i][j]][1][0]=i,vis[a[i][j]][1][1]=j,chk[a[i][j]]=2;
			}
		for(int i=1;i<=k;++i)
            ids=ids+(chk[i]>=1),Max=max(Max,(chk[i]>=1)*i);
		for(int i=Max;i>=1;--i) // 分类讨论
		{
			if(chk[i]==2)
			{
				int tx1=vis[i][0][0],ty1=vis[i][0][1],tx2=vis[i][1][0],ty2=vis[i][1][1];
			    ans[i]=1,brd[tx1][ty1]=1,Add(tx1,ty1),brd[tx2][ty2]=1,Add(tx2,ty2);
				continue;
			}
			if(chk[i]==1)
			{
				int tx=vis[i][0][0],ty=vis[i][0][1]; brd[tx][ty]=1,Add(tx,ty);
				for(int j=0;j<4;++j) ans[i]=ans[i]+brd[tx+drx[j]][ty+dry[j]];
				continue;
			}
			if(chk[i]==0) {ans[i]=nowt; continue;}
		}
		for(int i=1;i<=Max;++i) if(chk[i]>=1) all=all*1ll*ans[i]%Mod;
		f[0]=1ll; // 背包
		for(int i=1;i<=Max;++i)
		{
			if(chk[i]>=1) continue;
			for(int j=k-ids;j>=1;--j) f[j]=(f[j]+f[j-1]*ans[i]%Mod)%Mod;
		}
		for(int i=l;i<=r;++i) // 统计答案
		{
			if(i<ids || i>Max) continue;
			allinall=(allinall+all*f[i-ids]%Mod)%Mod;
		}
		printf("%lld\n",allinall);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j) brd[i][j]=0;
		for(int i=1;i<=k;++i) f[i]=0ll,ans[i]=0,chk[i]=0,vis[i][0][0]=vis[i][0][1]=vis[i][1][0]=vis[i][1][1]=0;
	}
	return 0;
}
```



---

## 作者：water_tomato (赞：0)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p7716-%e3%80%8cezec-10%e3%80%8dcovering-%e9%a2%98%e8%a7%a3/)。

[题目链接](https://www.luogu.com.cn/problem/P7716)。

## 解析

后边的 dp 方式似乎和已有题解有一些差异。

首先考虑从第 $1$ 张纸片开始一张张放，计算出每张纸片有多少种放法，这分为三种情况：

1. 最后局面该纸片占两格，显然只有 $1$ 种放法。
2. 最后局面该纸片占一格，那么可能的放法有 $4$ 种，去除其中会覆盖最终局面的放法即可。
3. 最后局面不存在该纸片，那么可能的放法为所有未被覆盖的位置的放法之和，这个可以在过程中维护。具体地，初始放法数为 $(n-1)\times(m-1)+n-1+m-1$，然后每次放纸片之后减去那些不能放的放法即可。

容易发现，所有在最终局面出现过的纸片都是必须要选择的，假设这些纸片数为 $k$，那我们还需要选择的纸片数为 $[l-k,r-k]$。对于一种选择方式，其对答案的贡献就是所有选中的纸片的放法数之积。

我们又发现， 所有最终局面不存在的纸片是独立的，即某一张纸片是否选择并不会影响其他纸片的方案数。那么问题转化为求在剩余纸片中分别选 $l-k,l-k+1,\dots,r-k-1,r-k$ 张纸片，并将每一种情况的乘积求和。可以考虑转化为一次求出选 $1,2,3,\dots,r-k$ 张纸片的贡献。

我们考虑选 $1$ 张纸片的贡献就是剩余纸片的和，而选 $2$ 张纸片时，选中第 $i$ 张纸片的贡献就是 $i$ 的方案数乘以上一层的 $i+1$ 的后缀和，然后同理层层处理即可。

举个例子，加入剩余的纸片对应的方案数为 $[7,5,4,2,2]$，求其后缀和为 $[20,13,8,4,2]$，那么选一张纸片的贡献就是 $20$，然后选两张纸片时，先计算出强制选择第 $i$ 张纸片，令其与 $i+1$ 及之后的纸片结合的贡献，即 $[91,40,16,4,0]$，再次求其后缀和为 $[151,60,20,4,0]$，即选两张纸片的贡献为 $151$。

可能说的还不是很明白，可以参考下面的代码进行理解。

## 代码

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define int long long
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
template <typename T>
inline void read(T& r) {
    r=0;bool w=0; char ch=getchar();
    while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+(ch^48), ch=getchar();
    r=w?-r:r;
}
const int N=1005;
const int mod=1e9+7;
int T,n,m,k,l,r,a[N][N],ans[N];
int cnt,tot,px[4]={0,0,1,-1},py[4]={1,-1,0,0};
bool vis[N][N];
pi pos[N];
inline pi check(int x,int y){//找旁边有没有相同的编号
	for(int i=0,xx,yy;i<4;i++){
		xx=x+px[i],yy=y+py[i];
		if(xx<1||yy<1||xx>n||yy>m) continue;
		if(a[xx][yy]==a[x][y]) return mk(xx,yy);
	}
	return mk(0,0);
}
inline void del(int x,int y){//更新还有多少位置可以放
	for(int i=0,xx,yy;i<4;i++){
		xx=x+px[i],yy=y+py[i];
		if(xx<1||yy<1||xx>n||yy>m) continue;
		if(!vis[xx][yy]) cnt--;
	}
}
int b[N],c[N],d[N];
signed main(){
	read(T);
	while(T--){
		read(n);read(m);read(k);read(l);read(r);
		cnt=2*(n-1)*(m-1)+n-1+m-1;tot=0;
		for(int i=1;i<=k;i++) pos[i]=mk(0,0),ans[i]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				vis[i][j]=0,read(a[i][j]);
				if(!pos[a[i][j]].fi) pos[a[i][j]]=mk(i,j);
			}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]==0){//没有被覆盖的点先除去
					tot++;del(i,j);
					vis[i][j]=1;
				}
			}
		}
		for(int i=1;i<=k&&tot!=n*m;i++){
			if(!pos[i].fi) ans[i]=cnt;//没有出现的
			else{
				int x=pos[i].fi,y=pos[i].se;
				pi t=check(x,y);
				if(t.fi){//出现了两个
					int xx=t.fi,yy=t.se;
					del(x,y);vis[x][y]=1;
					del(xx,yy);vis[xx][yy]=1;
					ans[i]=1;tot+=2;
				}
				else{//出现了一个
					for(int j=0,xx,yy;j<4;j++){
						xx=x+px[j],yy=y+py[j];
						if(xx<1||yy<1||xx>n||yy>m) continue;
						if(!vis[xx][yy]) ans[i]++;
					}
					del(x,y);tot++;
					vis[x][y]=1;
				}
			}
		}
		int ANS=1,sp=0,Ans=0;
		for(int i=1;i<=k;i++){
			if(pos[i].fi) ANS=ANS*ans[i]%mod,l--,r--;//一定要选中的
			else b[++sp]=ans[i];
		}
		if(l<=0) Ans=ANS;
		c[sp+1]=0;//此处开始为 dp，准确说是求一次答案，算一次前缀和
		for(int i=1;i<=r;i++){
			if(i!=1){
				for(int j=1;j<=sp;j++){
					c[j]=b[j]*c[j+1];
				}
			}
			else{
				for(int j=1;j<=sp;j++) c[j]=b[j];
			}
			for(int j=sp-1;j>=1;j--) c[j]=(c[j]+c[j+1])%mod;
			if(i>=l) Ans=(Ans+c[1]*ANS%mod)%mod;//更新答案时需要呈上必须选中的贡献
		}	
		printf("%lld\n",Ans);
	}
	return 0;
}
```



---

