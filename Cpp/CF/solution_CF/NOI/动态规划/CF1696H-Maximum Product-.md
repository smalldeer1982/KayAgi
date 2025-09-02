# Maximum Product?

## 题目描述

给定一个正整数 $k$。对于一个整数多重集 $S$，定义 $f(S)$ 如下：

- 如果 $S$ 中的元素个数小于 $k$，则 $f(S)=0$。
- 否则，$f(S)$ 等于从 $S$ 中恰好选出 $k$ 个整数所能得到的最大乘积。

更正式地，设 $|S|$ 表示 $S$ 中元素的个数。那么，

- 如果 $|S|<k$，则 $f(S)=0$。
- 否则，$f(S)=\max\limits_{T\subseteq S,|T|=k}\left(\prod\limits_{i\in T}i\right)$。

现在给定一个整数多重集 $A$。请计算 $\sum\limits_{B\subseteq A} f(B)$，并对 $10^9+7$ 取模。

注意，本题中元素通过下标区分而不是通过数值区分。也就是说，一个包含 $n$ 个元素的多重集总共有 $2^n$ 个不同的子集，无论其中是否有元素相等。

## 说明/提示

考虑第一个样例。根据定义有：

- $f(\varnothing)=0$
- $f(\{-1\})=0$
- $f(\{2\})=0$
- $f(\{4\})=0$
- $f(\{-1,2\})=-2$
- $f(\{-1,4\})=-4$
- $f(\{2,4\})=8$
- $f(\{-1,2,4\})=8$

所以应输出 $(0+0+0+0-2-4+8+8)\bmod (10^9+7)=10$。

在第二个样例中，注意虽然多重集由三个相同的值组成，但它仍有 $8$ 个不同的子集：$\varnothing,\{1\},\{1\},\{1\},\{1,1\},\{1,1\},\{1,1\},\{1,1,1\}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
-1 2 4```

### 输出

```
10```

## 样例 #2

### 输入

```
3 1
1 1 1```

### 输出

```
7```

## 样例 #3

### 输入

```
10 4
-24 -41 9 -154 -56 14 18 53 -7 120```

### 输出

```
225905161```

## 样例 #4

### 输入

```
15 5
0 0 2 -2 2 -2 3 -3 -3 4 5 -4 -4 4 5```

### 输出

```
18119684```

# 题解

## 作者：老莽莽穿一切 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16427416.html)

---

比起上一题的各种弯弯绕绕，这一题的解法简单明了，也暴力得多。

直接暴力求题目要求的东西实在太暴力，几乎无法优化，所以考虑转成计数题。

首先思考给定可重集 $S$ 求 $f(S)$，如果集合中只有正数可以直接取前 $m$ 大值，否则进行分类讨论，将**绝对值**前 $m$ 大取出，如果负数数量为偶数则没有问题，否则考虑将一个正数换成负数或将一个负数换成正数，这取决于不在这 $m$ 个数中的绝对值最大的正数和负数的大小，一种特殊情况是集合中只有负数且要选计数个数，此时选择绝对值最小的 $m$ 个负数。

通过上面的计算方式，我们得出几个结论，首先一般情况下我们会优先取绝对值更大的数，其次有正负分类讨论，所以我们先对数据进行第一波处理——将读入的集合分成两部分 $\mathrm{pos}$ 与 $\mathrm{neg}$，两部分分别**按绝对值**从大到小排序。

接下来我们可以开始考虑对答案进行计算，这种最大值的和我们有一种比较固定的套路就是通过排序去除计算最大值的过程，然后转换成计算题，这次也不例外，我们可以用 dp 解决前 $m$ 个数的乘积，即 $f$ 的答案，然后再使用 $2$ 的幂次快速计算后面集合数量部分。

计数题最大的难题在于不重不漏，即找到一个好的枚举指标，这里我们可以枚举**绝对值前 $m$ 大中最小的正数和负数**，然后前半部分可以 dp，后半部分直接算。

首先考虑前半部分的 dp，$fp_{i,j}$ 表示在 $\mathrm{pos}_{1\sim i}$ 中取**恰好** $j$ 个数且**必须包含 $\mathrm{pos}_i$**的乘积的和，同理定义 $fn_{i,j}$ 表示在 $\mathrm{neg}_{1\sim i}$ 中取恰好 $j$ 个数且必须包含 $\mathrm{neg}_i$ 的乘积的和，这两个 dp 难度不大，暴力转移可以用前缀和优化一下，我们可以利用这两个数组来计算前 $m$ 个数的乘积，然后通过预处理 $2$ 的幂次可以计算方案数，记得要预处理每个数在**所有数**中绝对值从大到小的排名，这决定了用 $2$ 的幂次计算方案数的结果。

但是正如上面讲解计算 $f(S)$ 方法时所说的，当前 $m$ 大时如果负数的数量为奇数，还要进行分类讨论，我们下一步枚举不被包含的最大的正数和负数，直接进行分类讨论计算，此时我们发现因为要枚举绝对值前 $m$ 大中负数的个数、前 $m$ 大中绝对值最小的正数、负数、不被包含的最大的正数、负数，一共要枚举五个，所以时间复杂度 $\mathcal O\left(n^5\right)$，记得要把前 $m$ 大只有正数和只有负数的部分取出来单独做，如果 $m$ 为奇数，则要同上处理一个反着的数组用于计算选取集合中只有负数的情况和前 $m$ 大只有负数但后面有正数的分类讨论，具体细节可以看这份 $\mathcal O\left(n^5\right)$ 的暴力[**代码**](https://codeforces.com/contest/1696/submission/162294070)（建议先将这份代码彻底读懂再往下看，下面所有代码都基于这份代码优化）。

接下来其实就是轻车熟路了，首先发现时间复杂度瓶颈是在绝对值前 $m$ 大数中有奇数个负数的情况，我们发现此时后半部分的计算与代码中枚举的 $k$ 无关，可以将这部分提到前面，直接计算即可，预处理 $h_{i,j}$ 表示当绝对值前 $m$ 大中最小的正数为 $\mathrm{pos}_i$，负数为 $\mathrm{neg}_j$ 的贡献，这样时间复杂度就是 $\mathcal O\left(n^4\right)$，这里是优化到 $\mathcal O\left(n^4\right)$ 的[**代码**](https://codeforces.com/contest/1696/submission/162294088)。

最后一步，我们发现时间复杂度瓶颈又到了 $h$ 的预处理上，同时是同时枚举正数和负数的部分，然后这部分卡住我们的是那个 $\max$，还是那个套路，运用一些手段将 $\max$ 去掉，考虑到我们之前已经排完序了，这里我们可以先将两个情况写出来，然后发现可以前缀和优化，最后就是用指针维护一下 $\max$ 的临界点，然后用前缀和优化统计，降到 $\mathcal O\left(n^3\right)$，达到可过的时间复杂度。

一步一步走到最后的[**代码**](https://codeforces.com/contest/1696/submission/162294312)，思路其实比上一题清晰得多，实现上对细节要求蛮多，整体是一道非常不错的题。

---

## 作者：Kubic (赞：3)

很难理解为什么这题能 3500 以及为什么放 H，感觉比 G 简单到不知道哪里去了。

先考虑给定一个序列，怎么求出从中选出 $m$ 个数的最大乘积。

首先有一个很自然的想法是取绝对值最大的 $m$ 个数，这样乘积的绝对值也会比较大。

但是有可能出现乘积为负数的情况，此时可以进行调整，一定为以下三种情况之一：

- 如果所有数都是负数且 $m$ 是奇数，那么改为选绝对值最小的 $m$ 个数。

- 把已选的**负数**中绝对值**最小**的改为未选的**非负数**中绝对值**最大**的。

- 把已选的**非负数**中绝对值**最小**的改为未选的**负数**中绝对值**最大**的。

对两种情况取 $\max$ 即可。

但是这题在 $\max$ 外面套了 $\sum$，这导致不容易直接进行 dp。

考虑先进行一遍 $O(n^2)$ 的 dp 算出调整前的答案，然后再对被错误计算的部分进行调整。

对于 $B$ 中所有数都是负数且 $m$ 是奇数的情况，我们只需要对所有负数做两遍类似的 dp 即可完成调整。

剩余的情况就需要进行一些讨论。

设 $i_1,i_2$ 分别表示调整前的方案中已选的绝对值最小的非负数和负数。

设 $j_1,j_2$ 分别表示调整前的方案中未选的绝对值最大的非负数和负数。

上面的已选和未选都是针对 $B$ 内的数而言，$B$ 外的数一律不进行考虑。

需要注意的是，$i_1,i_2,j_1,j_2$ 中的某些可能是不存在的。

这里只考虑四个数都存在的情况，其它的情况是更弱的，但需要注意细节处理上的问题。

我们从绝对值比 $i_1$ 大的非负数以及绝对值比 $i_2$ 大的负数中选出 $m-2$ 作为调整前的方案。

在这种情况下如果需要进行调整，那么必定满足这 $m-2$ 个数的乘积为非负数，这是因为 $i_1$ 和 $i_2$ 的乘积为负数，而调整后的结果一定为负数。

设这 $m-2$ 个数的所有需要调整的方案的权值和为 $w$。

在第一遍计算中，我们把这些方案的权值和算作了 $w\times i_1\times i_2$，但实际上，这些方案的权值和应当为 $w\times\max(i_1\times j_1,i_2\times j_2)$，我们只需补上这个差值即可。

但直接枚举这四个数是 $O(n^4)$ 的。我们可以考虑把 $\max$ 拆开来，按照两种调整方式的优劣关系分类计算。这里只讨论 $i_1\times i_2\ge i_2\times j_2$ 的情况，另一种的处理方法是类似的。 

只需要枚举 $i_1,i_2,j_1$，满足条件的 $j_2$ 是一段后缀，直接双指针就可以做到 $O(n^3)$。

这里需要注意一些细节：$B$ 中可能存在绝对值比 $j_1$ 小的非负数以及绝对值比 $j_2$ 小的负数，但它们的存在并不会影响 $B$ 的权值，只需乘上一个 $2$ 的幂次即可。

于是就做完了，嘴巴起来很快，写起来很吃屎。实际上这道题有很多不同的但是等价的做法，代码难度差别可能比较大，这篇题解写的是我在写代码的过程中总结出来的一种相对简洁的讨论方法。可惜改变不了屑题的本质，还是有很多细节。可能这就是本题难点吧。

时间复杂度 $O(n^3)$。

目前是 CF 上最快解。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 605
#define MOD 1000000007
int n,m,t,ans,a[N],a1[N],a2[N],b1[N],b2[N],dp1[N],pw[N*2],dp[N][2],tmp[N][2];
bool cmp(int x,int y) {return x>y;}
int add(int x,int y) {x+=y;return x<MOD?x:x-MOD;}
void W(int &x,int y) {x+=y;if(x>=MOD) x-=MOD;}
int main()
{
	scanf("%d %d",&n,&m);pw[0]=1;
	for(int i=1;i<=n*2;++i) pw[i]=add(pw[i-1],pw[i-1]);
	for(int i=1,x;i<=n;++i)
	{scanf("%d",&x);if(x<0) a2[++a2[0]]=-x;else a1[++a1[0]]=x;}
	sort(a1+1,a1+a1[0]+1,cmp);sort(a2+1,a2+a2[0]+1,cmp);t=1;
	for(int i=1;i<=a1[0];++i)
	{
		while(t<=a2[0] && a1[i]<a2[t]) a[b2[t]=++a[0]]=MOD-a2[t],++t;
		a[b1[i]=++a[0]]=a1[i];
	}while(t<=a2[0]) a[b2[t]=++a[0]]=MOD-a2[t],++t;dp1[0]=1;
	for(int i=1;i<=n;++i)
	{
		W(dp1[m],dp1[m]);
		for(int j=min(m,i-1);j>=0;--j) W(dp1[j+1],1ll*dp1[j]*a[i]%MOD);
	}ans=dp1[m];
	if(m&1)
	{
		for(int i=0;i<=m;++i) dp1[i]=0;dp1[0]=1;
		for(int i=1;i<=a2[0];++i)
		{
			W(dp1[m],dp1[m]);
			for(int j=min(m,i)-1;j>=0;--j) W(dp1[j+1],1ll*dp1[j]*a2[i]%MOD);
		}W(ans,dp1[m]);for(int i=0;i<=m;++i) dp1[i]=0;dp1[0]=1;
		for(int i=a2[0];i;--i)
		{
			W(dp1[m],dp1[m]);
			for(int j=min(m,a2[0]-i+1)-1;j>=0;--j) W(dp1[j+1],1ll*dp1[j]*a2[i]%MOD);
		}W(ans,MOD-dp1[m]);for(int i=0;i<=m;++i) dp1[i]=0;dp1[0]=1;t=0;
		for(int i=1,w;i<=a2[0];++i)
		{
			w=dp1[m-1];while(t<=a1[0] && b1[t]<=b2[i]) ++t;
			if(w) for(int j=t;j<=a1[0];++j)
				W(ans,1ll*(a1[j]+a2[i])*w%MOD*pw[a1[0]+a2[0]-i-j]%MOD);
			for(int j=min(m,i)-1;j>=0;--j) W(dp1[j+1],1ll*dp1[j]*a2[i]%MOD);
		}
	}dp[0][0]=1;
	if(m>1) for(int i=1,t1,t2,w;i<=a1[0];++i)
	{
		for(int j=0;j<=min(m,i-1);++j)
			tmp[j][0]=dp[j][0],tmp[j][1]=dp[j][1];t1=t2=0;
		for(int j=1;j<=a2[0];++j)
		{
			w=dp[m-2][0];
			if(w)
			{
				while(t1<=a1[0] && b1[t1]<=max(b1[i],b2[j])) ++t1;
				while(t2<=a2[0] && b2[t2]<=max(b1[i],b2[j])) ++t2;t=t2;
				for(int k=t1;k<=a1[0];++k)
				{
					while(t<=a2[0] && 1ll*a1[i]*a1[k]<1ll*a2[j]*a2[t]) ++t;
					W(ans,1ll*a1[i]*(a1[k]+a2[j])%MOD*w%MOD*pw[a1[0]+a2[0]-k-t+1]%MOD);
				}t=t1;
				for(int k=t2;k<=a2[0];++k)
				{
					while(t<=a1[0] && 1ll*a1[i]*a1[t]>=1ll*a2[j]*a2[k]) ++t;
					W(ans,1ll*a2[j]*(a1[i]+a2[k])%MOD*w%MOD*pw[a1[0]+a2[0]-k-t+1]%MOD);
				}
			}
			for(int k=min(m,i+j-1)-1;k>=0;--k)
			{
				W(dp[k+1][1],1ll*dp[k][0]*a2[j]%MOD);
				W(dp[k+1][0],1ll*dp[k][1]*a2[j]%MOD);
			}
		}for(int j=0;j<=m;++j) dp[j][0]=tmp[j][0],dp[j][1]=tmp[j][1];
		for(int j=min(m,i)-1;j>=0;--j)
			W(dp[j+1][0],1ll*dp[j][0]*a1[i]%MOD),W(dp[j+1][1],1ll*dp[j][1]*a1[i]%MOD);
	}printf("%d\n",ans);return 0;
}
```

---

## 作者：周子衡 (赞：1)

先考虑对某个多重集 $S(|S| \geq k)$，怎么方便地描述 $f(S)$。方便起见，下面我们先认为 $S$ 不含 $0$。可以发现：

- 大部分情况下都有 $f(S) > 0$。当且仅当 $|S|=k$，或者 $S$ 中全是负数且 $k$ 是奇数的情况下才有 $f(S) < 0$。
- $f(S) < 0$ 的时候我们要最小化 $f(S)$ 的绝对值，则一定选绝对值最小的 $k$ 个元素乘起来。
- $f(S) > 0$ 的时候，负数一定要选偶数个。同时，正数、负数一定要分别选绝对值最大的若干个。考虑将正数、负数分别按绝对值排序，正数为 $P_1>\cdots>P_p$，负数为 $|T_1|>\cdots>|T_t|$，则答案一定是 $P_1...P_k,T_1T_2P_1...P_{k-2},T_1T_2T_3T_4P_1...P_{k-4},...$ 这一列数中最大的那个。观察到每次相当于是乘上两个负数、除掉两个正数，且乘上的负数绝对值越来越小、除掉的正数绝对值越来越大，到某个时刻除掉的数绝对值大于乘上的数了，那么就得到了最大值。

考虑怎么快速计算 $S$ 所有子集的 $f$ 值之和。我们仍旧先假定 $S$ 中不含 $0$。显见应该将全部元素分为正数和负数两类，假设这两类数分别构成集合 $P,T$。为了说明方便起见，我们先假定 $P,T$ 的任意子集乘积均互不相同。下面中序列元素的大小均指绝对值的大小。

- $f(S) < 0$ 的全体 $f$ 值之和是容易计算的，按上面两类分类讨论即可。可以用背包来计算正数 / 负数所有 $k$ 元子集的元素乘积的和。
- 我们着重考察如何计算所有 $f(S) > 0$ 的 $f$ 值总和。考虑枚举 $P,T$ 的两个子集 $P',T'$，其中 $|T'|$ 是偶数，且 $|P'|+|T'|=k$。考虑所有 $f(S)=\mathrm{prod}(P')\mathrm{prod}(T')$ 的 $S$ 的数量。设 $P'$ 中最小元素在 $P$ 中是第 $x$ 大，$T'$ 中最小元素在 $T$ 中是第 $y$ 大。可知所有的 $S$ 都只应该包含 $P',T'$，以及一些比 $P_x$ 小的正数、一些比 $T_y$ 小的负数，这样的 $S$ 共计 $2^{(x-1)+(y-1)}$ 个。
- 但还要考虑到：$S$ 中在 $T'$ 外的最大的两个负数的乘积不能大于 $P'$ 最小两个元素的乘积（否则应把这两个正数换出去，把两个负数换进来）；反过来也是。注意到正反两种情况不可能同时发生，我们可以分开排除。简洁起见我们只讨论上述的第一种情况的求解方法，第二种大同小异。
- 考虑去枚举 $T'$ 外的最大两个负数以及 $P'$ 中的最小两个元素，排除掉所有多计算的 $f(S)$。直接枚举要枚举 $O(n^4)$ 对，不能接受。我们进一步分析性质。考虑负数对是 $T_{l_1},T_{r_1}$，正数对是 $P_{l_2},P_{r_2}$（$l_1 < r_1,l_2 < r_2$），那么对答案的贡献为

$$
-\sum_{x=2t,t\in \mathbb{N}}\mathrm{snc}(l_1-1,x)2^{|T|-r_1}\times P_{l_2}P_{r_2}\mathrm{spc}(l_2-1,k-x-2)2^{|P|-r_2}
$$

其中 $\mathrm{snc}(i,x)$ 表示 $T_1,...,T_i$ 所有 $x$ 元子集元素乘积和，$\mathrm{spc}(i,x)$ 表示 $P_1,...,P_i$ 所有 $x$ 元子集元素乘积和。可以用背包计算。参见代码，注意和这里的下标有区别。

- 当 $x$ 固定时，这个贡献可以被拆成两部分，一部分只和 $(l_1,r_1)$ 有关，一部分只和 $(l_2,r_2)$ 有关。做法也就出来了：枚举所有的 $(l_1,r_1)$ 以及 $(l_2,r_2)$ 对，按照元素乘积大小排序，每个 $(l_1,r_1)$ 对和前面的 $(l_2,r_2)$ 对的贡献一起统计入答案。排序时间复杂度 $O(n^2\log n)$，扫描的时候我们需要维护当前所有“可用”的 $(l_2,r_2)$ 对在 $x=0,2,4,...$ 时分别的贡献，这里时间复杂度 $O(n^3)$。

到这里本题大致做法就讲完了。一些细节问题：

- 上面分析做法时提到假定子集元素乘积两两不同。对于有相同的情况，实际上任意确定顺序都是可以的，因而不会对实现造成太大困扰。
- $0$ 实际上也可以任意分到正数或负数中。
- 视实现可能需要略微卡卡常数。

```cpp
#pragma GCC optimize(2)

#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const long long MOD=1e9+7;
vector<long long> P,N;
long long pc[1000][1000],nc[1000][1000],spc[1000][1000],snc[1000][1000],pw2[1000],totn[1000],totp[1000];

int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}
long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}return ans;
}
struct nd
{
	long long val;int type,l,r;
	nd(long long _val=0,int _type=0,int _l=0,int _r=0):val(_val),type(_type),l(_l),r(_r){}
};
bool operator<(nd A,nd B){return A.val<B.val;}
vector<nd> V;

int main()
{
	int n=0,k=0;scanf("%d%d",&n,&k);
	pw2[0]=1;for(int i=1;i<=n;i++)pw2[i]=add(pw2[i-1],pw2[i-1]);
	for(int i=1;i<=n;i++)
	{
		int a=0;scanf("%d",&a);
		if(a>=0)P.push_back(a);else N.push_back(-a);
	}
	sort(P.begin(),P.end());sort(N.begin(),N.end());
	
	pc[P.size()][0]=spc[P.size()][0]=1;
	for(int i=P.size()-1;i>=0;i--)
	{
		for(int j=1;j<=n;j++){pc[i][j]=spc[i+1][j-1]*P[i]%MOD;}
		for(int j=0;j<=n;j++)
		{
			spc[i][j]=add(spc[i+1][j],pc[i][j]);
		}
	}
	for(int i=P.size();i>=0;i--)for(int j=0;j<=n;j++)totp[j]=add(totp[j],pc[i][j]*pw2[i]%MOD);
	
	nc[N.size()][0]=snc[N.size()][0]=1;
	for(int i=N.size()-1;i>=0;i--)
	{
		for(int j=1;j<=n;j++){nc[i][j]=snc[i+1][j-1]*N[i]%MOD;}
		for(int j=0;j<=n;j++)
		{
			snc[i][j]=add(snc[i+1][j],nc[i][j]);
		}
	}
	for(int i=N.size();i>=0;i--)for(int j=0;j<=n;j++)totn[j]=add(totn[j],nc[i][j]*pw2[i]%MOD);
	
	//for(int i=0;i<=n;i++)printf("%lld ",totp[i]);puts("");
	//for(int i=0;i<=n;i++)printf("%lld ",totn[i]);puts("");
	
	long long ans=0;
	for(int i=0;i<=k;i+=2)ans=add(ans,totn[i]*totp[k-i]%MOD);
	//printf("%lld\n",ans);
	
	memset(totn,0,sizeof(totn));memset(totp,0,sizeof(totp));
	for(int i=0;i<P.size();i++)for(int j=i+1;j<P.size();j++)
	{
		V.push_back(nd(P[i]*P[j],0,i,j));
	}
	for(int i=0;i<N.size();i++)for(int j=i+1;j<N.size();j++)
	{
		V.push_back(nd(N[i]*N[j],1,i,j));
	}
	sort(V.begin(),V.end());
	for(int i=0;i<V.size();i++)
	{
		if(V[i].type==0)
		{
			for(int j=0;j<=k&&j<=N.size();j+=2)
			{
			if(k-j>P.size())continue;	
			ans=sub(ans,totn[j]*pw2[V[i].l]%MOD*spc[V[i].r+1][k-j]%MOD);
			}
			for(int j=(k&1);j<=k;j+=2)totp[j+2]=add(totp[j+2],(V[i].val%MOD)*spc[V[i].r+1][j]%MOD*pw2[V[i].l]%MOD);
		}
		else
		{
			for(int j=0;j<=k&&j<=N.size();j+=2)
			{
			if(k-j>P.size())continue;	
			ans=sub(ans,totp[k-j]*pw2[V[i].l]%MOD*snc[V[i].r+1][j]%MOD);
			}
			for(int j=0;j<=k;j+=2)totn[j+2]=add(totn[j+2],(V[i].val%MOD)*snc[V[i].r+1][j]%MOD*pw2[V[i].l]%MOD);
		}
	}
	//printf("%lld\n",ans);
	for(int i=1;i<=k;i+=2)ans=sub(ans,snc[0][i]*spc[0][k-i]%MOD);
	if(k&1)
	{
		memset(snc,0,sizeof(snc)),memset(nc,0,sizeof(nc));
		snc[0][0]=nc[0][0]=1;
		for(int i=1;i<=N.size();i++)
		{
			for(int j=0;j<=n;j++)nc[i][j+1]=snc[i-1][j]*N[i-1]%MOD;
			for(int j=0;j<=n;j++)snc[i][j]=add(snc[i-1][j],nc[i][j]);
		}
		for(int i=1;i<=N.size();i++)ans=sub(ans,nc[i][k]*sub(pw2[N.size()-i],1)%MOD);
	}
	
	printf("%lld",ans);
	
}
```

**后记**

一道细节比较多、需要仔细讨论的题。~~似乎比 G 简单。~~

---

