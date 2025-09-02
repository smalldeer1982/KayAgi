# Trains and Statistic

## 题目描述

Vasya commutes by train every day. There are $ n $ train stations in the city, and at the $ i $ -th station it's possible to buy only tickets to stations from $ i+1 $ to $ a_{i} $ inclusive. No tickets are sold at the last station.

Let $ ρ_{i,j} $ be the minimum number of tickets one needs to buy in order to get from stations $ i $ to station $ j $ . As Vasya is fond of different useless statistic he asks you to compute the sum of all values $ ρ_{i,j} $ among all pairs $ 1<=i&lt;j<=n $ .

## 说明/提示

In the first sample it's possible to get from any station to any other (with greater index) using only one ticket. The total number of pairs is $ 6 $ , so the answer is also $ 6 $ .

Consider the second sample:

- $ ρ_{1,2}=1 $
- $ ρ_{1,3}=2 $
- $ ρ_{1,4}=3 $
- $ ρ_{1,5}=3 $
- $ ρ_{2,3}=1 $
- $ ρ_{2,4}=2 $
- $ ρ_{2,5}=2 $
- $ ρ_{3,4}=1 $
- $ ρ_{3,5}=1 $
- $ ρ_{4,5}=1 $

Thus the answer equals $ 1+2+3+3+1+2+2+1+1+1=17 $ .

## 样例 #1

### 输入

```
4
4 4 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
2 3 5 5
```

### 输出

```
17
```

# 题解

## 作者：mrsrz (赞：9)

[可能更好的体验](https://mrsrz.github.io/2019/11/14/CF675E/)

按照起点从后往前依次考虑。

对于每个位置出发，我们要使其每一步能走的范围尽可能大。

那么，我们如果能走到 $[l,r]$，为了下一步能走得更远，我们需要在 $[l,r]$ 中选取一个 $a_i$ 最大的 $i$。

这个就是个区间 RMQ 问题。不难在 $O(n\log n)$ 的复杂度内解决。

那么怎么计算贡献呢？

我们考虑对位置 $i$，其第一次走的最大位置为 $k$，从 $k$ 的信息直接转移到 $i$ 的信息。

令 $f_i=\sum\limits_{j=i}^n d_{i,j}$.

考虑 $f_i$ 与 $f_k$ 的关系。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i1iswb4c.png)

其中，A 段是 $f_i$ 比 $f_k$ 多走的部分，C 段是 $i$ 直接走无法走到，需要走到 $k$ 再往后继续走的。所以 A 段和 C 段的每个数都要多计算 $1$ 的贡献。
$$
f_i=f_k+(k-i)+(n-a_i)
$$
上式的意思就是分别加上了 A 段和 C 段的贡献。

最后的答案就是所有 $f_i$ 之和。

时间复杂度就是 RMQ 部分的 $O(n\log n)$。这里的 RMQ 不需要使用 ST 表、线段树等算法，可以使用单调栈维护，查询直接二分即可。

## Code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1e5+6;
typedef long long LL;
int n,a[N];
LL ans,f[N];
vector<int>vec;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i)
		cin>>a[i];
	f[n-1]=ans=1;
	vec.push_back(n-1);
	for(int i=n-2;i;--i){
		int k=*(upper_bound(vec.rbegin(),vec.rend(),a[i])-1);
		f[i]=f[k]+(k-i)+(n-a[i]);
		ans+=f[i];
		while(!vec.empty()&&a[i]>=a[vec.back()])vec.pop_back();
		vec.push_back(i);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Ynoi (赞：4)


有个贪心思路

对于 i -> j 如果i一步不能走到j，那么必然i会先走到一个点k，k为[i+1,a[i]]中使a[k]最大的k。

证明：假设有一个点x在[i+1,a[i]]区间中，则所有 i走到x再走到一个 编号 > a[i]的节点y，必然可以从 i 走到 k 再到y，显然是走x不会优于走k

然后就是dp了

设 $f_i = \sum_{j = i+1}^{n}p_{i,j}$

则$f_i = f_k +(n-i)-(a[i]-k) $

解释：

我们先认定对于所有 编号 > k的点

都是从i走到k

那么这部分答案就是$f_k  + n-k$

但是在对于 [k+1,a[i]]的点，这样算会认为走两次 ，但其实只要走一次

所以要减去 (a[i]-k)

然后再加上  [i+1,k]的点（走一步）

整理可得$f_i = f_k +(n-i)-(a[i]-k) $

至于如何求k，这是区间最值问题

用st表即可

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define LL long long

int n,m;
int a[MAXN];
int f[MAXN][22],g[MAXN][22];
LL h[MAXN];

void rd()
{
	scanf("%d",&n);
	for(int i = 1; i < n; i ++)
		scanf("%d",&a[i]);
	for(int i = 1; i <= n; i ++)
	{
		f[i][0] = a[i];
		g[i][0] = i;
	}
	for(int j = 1; j <= 20; j ++)
		for(int i = 1; i <= n; i ++)
		if(i + (1<<j) - 1 <= n) {
			f[i][j] = max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			if(f[i][j-1] > f[i+(1<<(j-1))][j-1])
				g[i][j] = g[i][j-1];
			else g[i][j] = g[i+(1<<(j-1))][j-1];
		}
}

int rmq(int l,int r)
{
	int o = log2(r-l+1);
	if(f[l][o] > f[r-(1<<o)+1][o]) return g[l][o];
	else return g[r-(1<<o)+1][o];
}

int main()
{
	rd();
	LL ans = 0;
	for(int i = n-1; i >= 1; i --) {
		int k = rmq(i+1,a[i]);
		if(a[i] >= n) {
			h[i] = n-i;
		} else {
			h[i]  = h[k] - (a[i] - k) + (n-i);
		}
		ans += h[i];
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Arghariza (赞：3)

发现顺序考虑的话以 $i$ 为起点对答案的贡献不好算，所以倒序考虑。

设 $dp_i$ 表示以 $i$ 为起点到后面所有点的最小距离：

$$dp_i=\sum\limits_{k=i+1}^{n}p_{i,k}$$

你会发现啥，当你从位置 $i$ 出发的时候，你能够到达最远的地方是 $a_i$， 并且此时**额外**用的步数最少。

也就是说，对于一个位置 $i$ ，想要走的步数尽量少，你需要找到一个 $\max\limits_{k=i+1}^{a_i}\{a_k\}$ ，然后这东西可以用 `st` 表来维护。

这是个很明显的贪心策略，也是倒序转移的原因。

知道了 $dp_k$ ，怎么转移到 $dp_i$？

![无标题.png](https://i.loli.net/2021/11/15/7xZgMpWlAwRfa3X.png)

由上图能看出来 $dp_i=dp_k+P-Q$ ，也就是加上 $[i,n]$ 的部分再减去重复计算的 $[k,a_i]$ 。

注意当 $a_i≥n$ 的时候 $Q$ 是不用减的。

做完了，复杂度 $O(n\log n)$。

当然如果你够毒瘤可以出到 $O(n)$ ，因为 `st` 表有 $O(n)$ 的做法。![](https://啧.tk/doge)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1e5 + 100;
int n, ans, a[maxn], st[maxn][21], dp[maxn];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n - 1; i++) {
		scanf("%lld", &a[i]);
		st[i][0] = i;
	}
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
			if (a[st[i][j - 1]] > a[st[i + (1 << (j - 1))][j - 1]]) st[i][j] = st[i][j - 1];
			else st[i][j] = st[i + (1 << (j - 1))][j - 1];
		}
	}
	for (int i = n - 1; i >= 1; i--) {
		int l = i + 1, r = a[i], len = log2(r - l + 1), k;
		if (a[st[l][len]] > a[st[r - (1 << len) + 1][len]]) k = st[l][len];
		else k = st[r - (1 << len) + 1][len];
		if (a[i] >= n) dp[i] = n - i;
        else dp[i] = dp[k] + n + k - i - a[i];
        ans += dp[i];
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：是个汉子 (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/CF675E)	[CF传送门](http://codeforces.com/problemset/problem/675/E)

### Solution

这是DP。

对于每一个位置 $i$ ，它所能到的范围是 $[i+1,a_i]$ ，所以如果想要走的步数最少并且最远，应该找 $[i+1,a_i]$ 中有 $\max\{a_{k}\}$ 的 $k$ 。

这个可以用RMQ解决。

那么对于 $i$ ，有了相应的 $k$ ，接下来该怎么转移呢？

$k$ 是在 $i$ 后面的，所以考虑从后往前转移。

设 $f_{i}=\sum\limits_{j=i+1}^np_{i,j}$ ，那么转移方程是： 
$$
f_{i}=f_k+(n-k)-(a_i-k)+(k-i)\rightarrow f_i=f_k+(n-i)-(a_i-k)
$$
其中 $n-k$ 是因为 $>k$ 的点均经过 $k$ ， $a_i-k$ 是因为这一部分被算了两次贡献，所以减去， $k-i$ 是 $[i+1,k]$ 这一部分的点的贡献。

### Code

我就是不会二分和单调栈，只能用st表的那个屑≧ ﹏ ≦

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long

using namespace std;
const int N=100010;
int n,ans,a[N],st[N][20],f[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline int Max(int x,int y){
    return a[x]>a[y]?x:y;
}

inline void init(){
    for(int j=1;j<=20;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=Max(st[i][j-1],st[i+(1<<j-1)][j-1]);
}

inline int ask(int l,int r){
    int k=log2(r-l+1);
    return Max(st[l][k],st[r-(1<<k)+1][k]);
}

signed main(){
    n=read();
    for(int i=1;i<n;i++){
        a[i]=read();
        st[i][0]=i;
    }
    init();
    for(int i=n-1;i>=1;i--){
        int k=ask(i+1,a[i]);
        if(a[i]>=n) f[i]=n-i;
        else f[i]=f[k]+(n-i)-(a[i]-k);
        ans+=f[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：lzyqwq (赞：2)

蒟蒻不知道 `RMQ` 做法出现 $a$ 值相同的多个点改怎么转移，于是有了这篇线段树题解。

# $\texttt{Description}$

[题目传送门](https://www.luogu.com.cn/problem/CF675E)。

[CF 传送门](http://codeforces.com/problemset/problem/675/E)。

- 有 $n$ 个车站，第 $i\,(1\le i<n)$ 个车站能到达的车站范围为 $i+1\sim a_i$。从一个车站到另一个车站的费用为 $1$。令 $p_{i,j}\,(i<j)$ 为车站到车站 $j$ 的最小费用，求：
$$\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^np_{i,j}$$

- $1\le n\le10^5$。

# $\texttt{Solution}$

考虑 `DP`。

因为**越靠前的状态表示的范围越大，所以考虑倒着转移**。

令 $f_i=\sum\limits_{j=i+1}^np_{i,j}$，则有：

$$f_i=\min\limits_{j=i+1}^{a_i}(f_j+n-a_i+j-i)$$

解释一下：

- 设 $x_j$ 为 $j$ 跳到编号**大于** $a_i$ 的车站的花费和，$y_j$ 为 $j$ 跳到编号**大于** $j$ 且**不超过** $a_i$ 的车站的花费和，显然 $f_j=x_j+y_j$。

- 对于编号大于 $a_i$ 的那些车站，肯定是选择跳到一个 $i+1\sim a_i$ 范围内的车站，然后再从这个范围内的车站跳到更远的车站。钦定跳到的车站为 $j$，那么编号大于 $a_i$ 的那 $n-a_i$ 个车站，必须从 $i$ 花费一步跳到 $j$，再继续跳，因此要加上 $n-a_i$；跳到 $j$ 以后，就要从 $j$ 跳到那些编号大于 $a_i$ 的车站，故再加上 $x_j$。

- 对于剩下的范围内的车站，显然直接一步跳到最优，但是这里为了方便，直接钦定跳到范围内编号**大于** $j$ 的车站的花费为 $j$ 跳到它们的花费，故加上 $y_j$，再算上跳到编号**不超过** $j$ 的车站的花费 $j-i$。

整理一下就可以得到上面的方程。

但是对于第三条有一个问题，即 $j$ 跳到那些范围内编号**大于** $j$ 的车站**不一定是一步跳到**，那么我们的转移就错了。

这里考虑 $f_j$ 是跳到那些车站的，因为不一定是一步跳到，所以肯定是先跳到一个能到达的 $i+1\sim a_i$ 范围内的车站 $k$，然后从 $k$ 继续跳，如果能跳到就一步跳到，否则继续跳到一个范围内的车站并重复上述过程。

令最终在车站 $u$ 可以一步跳到范围内的所有车站，由于 $u$ 也是在 $i+1\sim a_i$ 范围之中的，所以可以用 $u$ 去转移给 $f_i$。这样不仅跳到 $i+1\sim a_i$ 范围内的花费最优，并且根据“$j$ 不一定一步跳到，$u$ 可以一步跳到”，容易得出 $a_u>a_j$，即 $u$ 的范围更广。那么对于编号大于 $a_i$ 的车站，就需要更少的中转车站去到达。经过的中转车站变少了，到达它们的费用也省下了，因此用 $u$ 去转移给 $f_i$ 对于编号**大于** $a_i$ 的车站也是最优的。**因此这样转移正好可以舍去那些不是最优或者一样优的状态，得到 $f_i$ 的最优解**。

但是这样转移复杂度为 $\Theta(n^2)$，不能接受。

稍将转移方程变形，把有关 $i$ 的项以及定值全部提出来，因为 $i$ 是枚举的，所以和它有关的也是定值。

即：

$$f_i=n-a_i-i+\min\limits_{j=i+1}^{a_i}(f_j+j)$$

右边与 $j$ 有关的式子不就是一个区间最值吗？由于是动态的，使用线段树快速查询即可。

得到 $f_i$ 之后，我们还需要用其去更新之后的状态，这一步对应线段树的单点修改，修改 $i$ 位置上的数为 $f_i+i$，这样在之后的查询中就会考虑都由它转移的贡献。

时间复杂度为 $\Theta(n\,\log_2n)$，可以接受。

# $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 1;
int n, a[N], minn[N << 2], f[N], ans;
int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return minn[x];
    }
    int m = l + r >> 1, res = 1e18;
    if (ql <= m) {
        res = min(res, query(x << 1, l, m, ql, qr));
    }
    if (qr > m) {
        res = min(res, query(x << 1 | 1, m + 1, r, ql, qr));
    }
    return res;
}
void change(int x, int l, int r, int k, int v) {
    if (l == r && l == k) {
        minn[x] = v;
        return;
    }
    int m = l + r >> 1;
    if (k <= m) {
        change(x << 1, l, m, k, v);
    } else {
        change(x << 1 | 1, m + 1, r, k, v);
    }
    minn[x] = min(minn[x << 1], minn[x << 1 | 1]);
}
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%lld", a + i);
    }
    for (int i = n - 1; i; --i) {
        if (a[i] == n) {
            f[i] = n - i;
        } else {
            f[i] = query(1, 1, n, i + 1, a[i]) + n - a[i] - i;
        }
        ans += f[i];
        change(1, 1, n, i, f[i] + i);
    }
    printf("%lld", ans);
}
```


---

## 作者：StayAlone (赞：2)

## 题意

有 $n$ 个站点，第 $i$ 个站点上的公交车途径 $[i + 1, a_i]$，第 $n$ 个站点上没有公交车。

记 $d_{i, j}$ 表示，从 $i$ 站点到 $j$ 站点，途中乘坐过不同公交车数量的最小值。

方便起见，记 $d_{i,i}=0$。

求 $\sum\limits_{i=1}^n\sum\limits_{j=i}^n d_{i, j}$。


## 思路

先考虑从 $i$ 走到 $j$ 的贪心策略。

- 若 $j\in[i + 1, a_i]$，答案为 $1$。

- 否则，由于答案一定大于 $1$，所以找到 $p\in[i + 1, a_i]$，使得 $a_p$ 最大的一个 $p$。耗费一步走到 $p$ 不劣。原因是，走到其它的任何位置，其下一步能走到的位置都被 $p$ 下一步能走到的位置包含。

考虑用这个办法 dp。

记 $f_i=\sum\limits_{k=i}^n d_{i, k}$，那么答案为 $\sum\limits_{i=1}^n f_i$。

dp 计算 $f_i$ 时，找到 $p\in[i + 1, a_i]$，使得 $a_p$ 最大的一个 $p$，那么根据贪心策略：

- $\forall k\in [i + 1, a_i]$，$d_{i, k}=1$；
- $\forall k\in [a_i + 1, n]$，$d_{i, k} = d_{p, k} + 1$。

剩下部分就是一些小细节了。

对于第一部分，答案和为 $a_i - i$。

对于第二部分，首先发现 $a_p > a_i$。

> 证明：$a_{a_i}\geq a_i + 1$，且 $a_p\geq a_{a_i}$，故 $a_p > a_i$。

也就是说，$\forall k \in(p, a_i]$，有 $d_{p, k}=1=d_{i, k}$。

第二部分的答案为：$\sum\limits_{k=a_i+1}^n d_{i, k}=\sum\limits_{k=p}^n d_{i, k} - \sum\limits_{k=p}^{a_i} d_{i, k}$。

其中 $\sum\limits_{k=p}^{a_i} d_{i, k} = a_i-p+1$；

而 $\sum\limits_{k=p}^n d_{i, k}=\sum\limits_{k=p}^{a_i} d_{i, k}+\sum\limits_{k=a_i+1}^n d_{i
, k}=1+\sum\limits_{k=p}^{a_i} d_{p, k}+\sum\limits_{k=a_i+1}^n (d_{p
, k}+1)=f_p+n-a_i+1$。

需要注意 $d_{p, p}=0,d_{i, p}=1$。

~~唉看起来好恶心，仔细看看下标吧，很简单的。~~

全部合起来就是 $f_i=f_p+p+n-a_i-i$。

为了寻找 $p$，预处理 ST 表即可。

代码非常短。

[AC record](https://www.luogu.com.cn/record/158305099)

```cpp
int n, a[MAXN], maa[MAXN][20], lg[MAXN]; ll ans, f[MAXN];
const ll inf = ~0Ull >> 2;

il int merge(int x, int y) {
	return a[x] < a[y] ? y : x;
}

il int query(int l, int r) {
	int k = lg[r - l + 1];
	return merge(maa[l][k], maa[r - (1 << k) + 1][k]);
}

int main() {
	read(n); rer(i, 1, n - 1, a); a[n] = n;
	rep1(i, 1, n) maa[i][0] = i;
	rep1(i, 2, n) lg[i] = lg[i >> 1] + 1;
	rep1(j, 1, lg[n]) rep1(i, 1, n - (1 << j) + 1) maa[i][j] = merge(maa[i][j - 1], maa[i + (1 << j - 1)][j - 1]);
	rep2(i, n - 1, 1) {
		int p = query(i + 1, a[i]);
		ans += (f[i] = f[p] + n - i - (a[i] - p));
	} printf("%lld", ans);
	rout;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
这题挺好的，虽然代码短但是还是有一定难度。
# 思路
首先我们考虑一个暴力，就是枚举 $i,j$ 然后求他们的最短路径，考虑一个贪心，如果当前在 $x$ 我们目标是 $j$ 如果 $a_x\geq j$ 那么只需要 $1$ 步，否则我们会跳到 $i+1\sim a_i$ 中 $a_k$ 最大的 $k$ 上去，这很好证明，然后将答案加 $1$。

有了这个暴力考虑如何优化，我们首先定义 $p_{i,j}$ 表示 $i\to j$ 的答案，然后 $f_{i}=\sum_{x=i+1}^{n} p_{i,x}$ 那么我们考虑分类讨论。

- 如果 $x\leq a_i$ 那么 $p_{i,x}=1$。
- 否则我们一定先回从 $i$ 跳到 $i+1\sim a_i$ 中 $a$ 值最大的点 $p$ 然后再从 $p$ 进行跳跃，那么我们考虑如何用 $f_p$ 来更新 $f_i$。

首先我们发现对于 $p$ 一定满足 $p\leq a_i$ 那么因为 $p_{p,k}=1,p<k\leq a_i$ 但是由于从 $i\to p$ 会加 $1$ 而 $p_{i,k}=1,p<k\leq a_i$ 那么我们考虑将这 $a_i-p$ 个的值从 $f_p$ 中减掉（即 $f_p-a_i+p$），然后我们再加上前面 $a_i-i$ 个的 $1$ 即可，所以总柿子即为 $f_i=f_p-a_i+p+a_i-i+n-a_i=f_p-a_i+n+p-i$，至于如何求 $p$ 这个无所谓，反正很好维护，我用的 ST 表，注意我们可以特判一下 $a_i=n$ 的情况这时候的 $f_i=n-i$。

如果看不懂还是建议画个图吧。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=1e5+10;
int f[N];
int mx[N][20],g[N][20],lg[N];
int n,a[N];
int Ans(int l,int r) {
	int len=lg[r-l+1];
	if(mx[l][len]>mx[r-(1<<len)+1][len]) return g[l][len];
	return g[r-(1<<len)+1][len];
}
void solve() {
	in(n);
	rep(i,1,n-1) in(a[i]),mx[i][0]=a[i],g[i][0]=i;
	rep(i,2,n) lg[i]=lg[i/2]+1;
	rep(j,1,19) {
		rep(i,1,n-(1<<j)+1) {
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
			if(mx[i][j-1]==mx[i][j]) g[i][j]=g[i][j-1];
			else g[i][j]=g[i+(1<<j-1)][j-1];
		}
	}
	int res=0;
	rep1(i,n-1,1) {
		if(a[i]==n) {
			f[i]=n-i;
			continue;
		}
		int p=Ans(i,a[i]);
		f[i]=f[p]-a[i]+p+n-i;
	}
	rep(i,1,n) res+=f[i];
	printf("%lld\n",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：BigJoker (赞：1)

# 前言

一道不错的 dp 练手题。

# Solution

令 $f_i$ 表示从 $i$ 这个点走，走到 $[i+1,n]$ 的最小花费。

画个图来理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/kkq5pn7w.png)

很明显，由于我们这一步只能跳 $[i+1,a_i]$ 所以下一步跳的范围越大越好，我们令这个最大的端点是 $j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wflxlaiy.png)

那么我们来推一下式子。

对于 $[i+1,a_i]$ 来说一步就够了，

![](https://cdn.luogu.com.cn/upload/image_hosting/84ayrysx.png)

方程就很显然了。

$f_i \gets f_j+n-a_i+j-i$

当然如果一步就可以跳到 $n$，特殊处理就好了。

答案就是 $\sum_{i=1}^nf_i$

当然其中的最大值可以用 RMQ 预处理出来，然后 $O(1)$ 查就可以了。

注意看数据范围哦。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,dp[N],r[N],st[N][20],res;
void init(){
	for(int i=1;i<=n;i++) st[i][0]=i;
	for(int j=1;j<=19;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) st[i][j]=(r[st[i][j-1]]>r[st[i+(1<<j-1)][j-1]]?st[i][j-1]:st[i+(1<<j-1)][j-1]);
}
int ask(int l1,int r1){
	int k=log2(r1-l1+1);
	if(r[st[l1][k]]>r[st[r1-(1<<k)+1][k]]) return st[l1][k];
	else return st[r1-(1<<k)+1][k];
} 
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++) scanf("%lld",&r[i]);
	init();
	for(int i=n-1;i>=1;i--){
		if(r[i]==n) dp[i]=(n-i);
		else{
			int R=ask(i+1,r[i]);
			dp[i]=n-r[i]+R-i+dp[R];	
		}
		res+=dp[i];		
	}
	printf("%lld",res);
	return 0;
}
```

---

## 作者：king_xbz (赞：1)

泥古好像还没有用线段树的题解？好像就连某度上也只能搜到一篇Pascal版的线段树题解？我来发一下全网第一篇c++线段树题解吧(doge)。

# 思路
其实这道题就是一道DP+数据结构维护区间最值，我们很自然的可以想到用线段树来维护QAQ。

### 找到状态转移
已知从$i$最多能跑到 $[i+1,a[i]]$，我们一定要从 $[i+1,a[i]]$中间一个点转移过去的。很显然，我们应该贪心地从该区间中间选取一个点M，使得 $a[M]$最大。这样才能找到最小车票花费。

如何进行状态转移呢？我们先从$i$走到$k$，此时的花费$f_M + n-M$，但是 $[M+1,a[i]]$这部分被重复计算了，我们要减去TA。在加上第一步

得到方程:$f_i=f_M+(n-1)-(a_i-M)$

PS：M部分即为我们需要维护的区间最值

### 维护区间操作
很显然，我们需要使用线段树来维护区间最大值。但这个区间最值又有些不一样。因为我们要求的是$a[m]$能到的最大车站，而不是$a[m]$的最大值。所以，我们在建树的时候需要同时记录车站与能到的车站两个变量，这种操作或许可以被称作**双权值线段树**（我自己编的。。。）当然喽，查询的时候也要在能到的车站最大时返回当前车站。

好像有点小麻烦，但实际上只要理解了线段树操作的本质，就还是很容易打出来的。

# 代码实现
掌握了这些，我们就可以用一棵线段树加上DP来维护这道题了。同时呢，这道题用ST表等方法也可以AC，别的题解里有讲，大家也可以试一试哦！

代码：
```cpp
#include<bits/stdc++.h>
#define fint register int
#define h 5001
#define p 4570944
#define ls x<<1
#define rs x<<1|1
#define tt t[x].tot
#define ll t[x].l
#define rr t[x].r
#define int long long
using namespace std;
struct node
{
    int l;
    int r;
    int tot;
    int tag;
}
t[p];
int maxxs,max_id;
int a[p],f[p],num[p];
inline int query(int x,int l,int r);
inline void build(int x,int l,int r);
signed main()
{
    int n;
    cin>>n;
    for(fint i=1;i<n;i++)
    cin>>a[i];
    a[n]=n;
    for(fint i=1;i<=n;i++)
    num[i]=i;
    build(1,1,n); 
    int ans=0;
    for(fint i=n-1;i>=1;i--)
    {
        maxxs=-1,max_id=0;
        int M=query(1,i+1,a[i]);
//      cout<<i+1<<" "<<a[i]<<endl;
//      cout<<M<<" "<<endl;
        f[i]=f[M]+(n-i)-(a[i]-M);
        ans+=f[i];
    }
    cout<<ans;
    return 0;
} 

inline void build(int x,int l,int r)
{
    ll=l,rr=r;
    if(l==r)
    {
        tt=a[l];
        t[x].tag=l;
        return ;
    }
    int mid=(rr+ll)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    if(t[ls].tot>t[rs].tot)
    t[x].tag=t[ls].tag;
    else
    t[x].tag=t[rs].tag;
    tt=max(t[ls].tot,t[rs].tot);
    return ;
}

inline int query(int x,int l,int r)
{
    if(ll>=l&&rr<=r)
    {
        if(maxxs<tt)
        maxxs=tt,max_id=t[x].tag;
        return max_id;
    }
    int mid=(ll+rr)>>1;
    int a=0,b=0;
    if(l<=mid)
    a=query(ls,l,r);
    if(r>mid)
    b=query(rs,l,r);
    return max_id;
}
```
**祝大家AC愉快哦！**

---

## 作者：Shadows_of_Twilight (赞：0)

# Solution

显然，对于车站 $i$，如果 $j \le a_i$，$p_{i, j} = 1$；如果 $j > a_i$，那么我们会先走到 $i + 1$ 到 $a_i$ 中 $a$ 最大的一个车站，设这个点为 $g_i$。从 $g_i$ 往后走，这样可以走得更远。

我们考虑设 $f_i$ 表示所有 $p_{i, j}$ 的和。

由于点 $i$ 可以走到 $i + 1$ 到 $a_i$。所以这些点对 $f_i$ 的贡献为 1。然后对于 $a_i + 1$ 到 $n$ 的点。我们先走到 $g_i$，再往后走，于是答案加上 $f_{g_i} - (a_i - g_i) + (n - a_i)$。这是因为从 $i$ 走到 $g_i$ 往后走最优，但是从当 $j$ 在 $g_i$ 到 $i$ 之间的时候从 $i$ 到 $g_i$ 再到 $j$ 不如直接从 $i$ 到 $j$，所以减掉 $a_i - g_i$，再加上后面 $a_i + 1$ 到 $n$ 之间的所有点都要在 $g_i$ 中转的代价 $n - a_i$。

最后答案即为所有 $f$ 的和。

回顾思路会发现要求 $g_i$，可以用一个 st 表维护。

时间复杂度 $O(n \log n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100005], s[100005], f[100005][22], lg[100005], g[100005];
long long dp[100005], ans;
int fd(int l, int r)
{
    int t = lg[r - l + 1];
    return a[f[l][t]] > a[f[r - (1 << t) + 1][t]] ? f[l][t] : f[r - (1 << t) + 1][t];
}
int main()
{
    ios ::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        f[i][0] = i;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = a[f[i][j - 1]] > a[f[i + (1 << j - 1)][j - 1]] ? f[i][j - 1] : f[i + (1 << j - 1)][j - 1];
    }
    for (int i = 1; i < n; i++)
        g[i] = fd(i + 1, a[i]);
    for (int i = n - 1; i >= 1; i--)
    {
        dp[i] = dp[g[i]] + (a[i] - i) - (a[i] - g[i]) + (n - a[i]);
        ans += dp[i];
    }
    cout << ans << '\n';
    return 0;
}


```

---

## 作者：鱼跃于渊 (赞：0)

一道数据结构优化 dp 的好题。  
## 1. 做法
首先可以发现，如果我们采取将 $i$ 转移到 $[i+1,a_i]$ 的方式，复杂度无疑是 $O(n^2)$ 的，而且也很难优化。  
于是考虑正难则反的思维，将 $[i+1,a_i]$ 转移到 $i$，从后向前依次处理，这样我们就只需要在 $[i+1,a_i]$ 中考虑转移了。  
观察到 $n\le 10^5$，这告诉我们单次转移的时间复杂度必须控制在 $O(\log n)$ 以内。  
我们定义 $f_i=\sum_{j=i+1}^{n} p_{i,j}$，其中 $p_{i,j}$ 代表从 $i$ 点到 $j$ 点的最短路径。  
考虑什么样的决策会成为最优决策。我们考虑贪心，对于 $j\in [i+1,a_i]$ 来说，$a_j$ 一定是越大越好的，可以证明以这个 $j$ 为转移点一定不会更劣。  
则我们可以推出以下转移方程：  
$$f_i=
\begin{cases}
n-i &\text{if } a_i=n \\
f_j+(n-i)-(a_i-j) &\text{if } a_i<n\\
\end {cases}$$
对于 $a_i=n$ 的情况，显然 $i$ 到 $[i+1,n]$ 中各个点的距离均为 $1$。  
对于 $a_i<n$ 的情况，显然 $i$ 跳一次是到不了 $n$ 的，需要一个中转点。上式中 $n-i$ 代表 $[i+1,n]$ 中的点到 $i$ 的距离均加一，由于 $[j,a_i]$ 这段区间多统计了一次，所以还要再减去 $a_i-j$。  
如何寻找这个 $j$ 呢？这显然是一个区间最值问题，使用 st 表维护即可。
## 2. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,ans,a[N],f[N];
int lg[N],st[30][N];
int get(int x,int y){
	return a[x]>a[y]?x:y; 
}
int query(int l,int r){
	int k=lg[r-l+1];
	return get(st[k][l],st[k][r-(1<<k)+1]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;a[n]=n;
	for(int i=1;i<n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) st[0][i]=i;
	for(int i=1;i<=lg[n-1];i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[i][j]=get(st[i-1][j],st[i-1][j+(1<<(i-1))]);
	for(int i=n-1,j;i>=1;i--){
		j=query(i+1,a[i]);
		if(a[i]==n) f[i]=n-i;
		else f[i]=f[j]+(n-i)-(a[i]-j);
	}
	for(int i=1;i<=n;i++) ans+=f[i];
	cout<<ans<<'\n';
	return 0;
}
```

---

