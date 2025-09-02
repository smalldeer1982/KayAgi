# 「DTOI-5」进行一个排的重 (Maximum Version)

## 题目背景

**本题与 Minimum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最大。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\max}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\max}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&50&20 \operatorname{pts}\cr\hline
\sf3&500&20 \operatorname{pts}\cr\hline
\sf4&2\times 10^3&20 \operatorname{pts}\cr\hline
\sf5&/&30 \operatorname{pts}\cr\hline
\end{array}
$$
对于 $100\%$ 的数据，$1 \leq n \leq 10^4$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
9 2```

# 题解

## 作者：Leasier (赞：5)

下文设 $a$ 按 $p$ 升序排序后的 $q'$ 为 $q_0$。

1. 求解 $f(a)_{\max}$

首先给出结论：答案为 $q_0$ 的 LIS 长度再加上 $n$。

为了证明这一点，首先我们需要证明如下结论：

- 任何一个满足 $\exists 1 \leq i \leq n$，使得 $p'_i$ 和 $q'_i$ 均不能产生贡献的方案，一定可以调整为 $\forall 1 \leq i \leq n$，使得 $p'_i$ 或 $q'_i$ 至少一个产生贡献的方案，且改后不劣。

证明：这里我们考虑从前往后依次调整每一个不满足条件的项。对于不产生贡献的 $(p'_i, q'_i)$，找到离 $i$ 最近的 $0 \leq j < i - 1$，使得 $\displaystyle\max_{k = 1}^j p'_k < p'_i$ 或 $\displaystyle\max_{k = 1}^j q'_k < q'_i$。下面讨论满足前一条件的情况。

这里考虑把 $a'_i$ 插入到 $a'_j$ 后面去，考虑一下贡献的变化量：

- 对于 $p'$ 而言，原 $p'_i$ 会带来 $1$ 的新贡献。
- 对于 $q'$ 而言，$\displaystyle\max_{k = 1}^j q'_k < q'_i$ 时会带来 $1$ 的新贡献，否则 $\displaystyle\max_{k = 1}^j q'_k < q'_i, \displaystyle\max_{k = 1}^{j + 1} q'_k > q'_i$，于是有 $q'_{j + 1} > q'_i$，即不会变劣。

则单次调整带来的新贡献 $\in [1, 2]$，满足不劣的条件。

于是，我们可以将任意方案调整为一个不劣且每对 $p'_i, q'_i$ 至少有一个产生贡献的情况。

现在我们只需要考虑两个均产生贡献的情况，则：

- 这些项的个数不超过 $q_0$ 的 LIS 长度，否则一定存在更长的 LIS。
- 抓出任意一个 $q_0$ 的 LIS 中的项都产生 $2$ 的贡献的 $a'$，我们可以用上面的方式将其调整至上限。

利用该结论，又因为本题中 $n$ 范围较小，直接暴力 dp 求 LIS 即可。时间复杂度为 $O(n^2)$。

2. 求解 $f(a)_{\max}$ 的方案数

考虑利用一定存在一个 $q_0$ 的 LIS，使得其顺序地作为每个最优 $a'$ 的子序列的性质 dp。

设 $g_i$ 表示 $q_0$ 的前缀 $[1, i]$ 的满足最后一个元素为 $i$ 的 LIS 长度。特别地，我们钦定 $g_{n + 1} = \displaystyle\max_{i = 1}^n g_i + 1$。

设 $dp_{i}$ 表示从后往前考虑到了 $[i, n + 1]$ 这个后缀，$i$ 在我们钦定的某个 LIS 中的方案数。

初值：$dp_{n + 1} = 1$。

转移：$dp_i = \displaystyle\sum_{j > i, (q_0)_j > (q_0)_i, g_j = g_i + 1}^{n + 1} dp_j C_{x + y}^x$，其中 $x$ 表示满足 $1 \leq k < i$ 且 $(q_0)_i < (q_0)_k < (q_0)_j$ 的 $k$ 的个数，$y$ 表示满足 $i < k < j$ 且 $(q_0)_k < (q_0)_i$ 的 $k$ 的个数。

- 解释一下这个转移：我们每次将满足第一个条件的元素 $k$ 顺序地放入 $a'$ 中的原 $a_i, a_j$ 之间，再将满足第二个条件的元素插板到其间。

答案：$dp_0$。

暴力实现是 $O(n^3)$ 的，直接上前缀和优化即可做到 $O(n^2)$。

综上，时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int mod = 998244353;
int dp1[10007], sum[10007][10007];
ll fac[10007], inv_fac[10007], dp2[10007];
pair<int, int> pr[10007];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline int get_sum(int l1, int r1, int l2, int r2){
	return sum[r1][r2] - sum[l1 - 1][r2] - sum[r1][l2 - 1] + sum[l1 - 1][l2 - 1];
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
	int n, ni;
	cin >> n;
	ni = n + 1;
	init(n);
	for (int i = 1; i <= n; i++){
		cin >> pr[i].first;
	}
	for (int i = 1; i <= n; i++){
		cin >> pr[i].second;
	}
	sort(pr + 1, pr + n + 1);
	pr[ni].second = ni;
	for (int i = 1; i <= ni; i++){
		for (int j = 1; j < i; j++){
			if (pr[i].second > pr[j].second) dp1[i] = max(dp1[i], dp1[j]);
		}
		dp1[i]++;
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
			if (pr[i].second == j) sum[i][j]++;
		}
	}
	dp2[ni] = 1;
	for (int i = n; i >= 0; i--){
		for (int j = i + 1; j <= ni; j++){
			if (pr[j].second > pr[i].second && dp1[j] == dp1[i] + 1){
				int t = i == 0 ? 0 : get_sum(1, i - 1, pr[i].second + 1, pr[j].second - 1);
				dp2[i] = (dp2[i] + dp2[j] * comb(t + get_sum(i + 1, j - 1, 1, pr[i].second), t) % mod) % mod;
			}
		}
	}
	cout << dp1[ni] + n - 1 << " " << dp2[0];
	return 0;
}
```

---

## 作者：_edge_ (赞：1)

题目出的挺好的，让我想了一会儿。

给出一种符合直觉的 dp，设 $f_{i,j}$ 表示第一个序列最大值为 $i$，第二个序列最大值为 $j$，题目要求的东西，即前缀最大值个数最小，然后 $cnt_{i,j}$ 表示他的方案数。

然后转移要稍微动点脑子。

先不考虑复杂度的影响。

考虑强制钦定下一个 pair 一定产生贡献。

第一种情况是第二个关键字 $j$ 相同，这种情况下，$i$ 必然转移到一组 pair，和 $j$ 相同的，并且第一个关键字大于 $i$ 的最小值的地方。

第二种情况是第一个关键字 $i$ 相同，这种情况下，和上面第一种情况同理。

第三种情况是转移到两个都大于的情况，这种情况下，没有上述两种性质，也是比较难做的一步。

想完这些已经会一个 $O(n^3)$ 的做法了，不过这还远远不够。

考虑第一种转移和第二种，可以有双指针维护，维护方式还是挺简单的，这里不再赘述。

第三种情况，刷表非常困难，考虑改为填表，即为求左上角是 $(1,1)$，右下角是 $(i-1,j-1)$ 这样一个矩形内部的答案，这东西可以随手二维前缀和优化，注意这里的要稍微空间优化一下。

赛时因为空间的问题没写，实际上空间可以优化得更加优秀，这里读者可以自行思考。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=1e4+5;
const int Mod=998244353;
struct P3{
	int a,b;
}aa[INF],bb[INF];
int cnt[INF][INF],n,num[INF],sum3[INF],sum4[INF],sum5[INF],sum6[INF];
short f[INF][INF];
bool vis[INF][INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>aa[i].a;
	for (int i=1;i<=n;i++) cin>>aa[i].b;
	for (int i=1;i<=n;i++) bb[i]=aa[i]; 
	for (int i=1;i<=n;i++) f[aa[i].a][aa[i].b]=2,cnt[aa[i].a][aa[i].b]=1;
	for (int i=1;i<=n;i++) vis[aa[i].a][aa[i].b]=1;
	sort(aa+1,aa+1+n,[](P3 xx,P3 yy){return xx.a<yy.a;});
	sort(bb+1,bb+1+n,[](P3 xx,P3 yy){return xx.b<yy.b;});
	for (int i=1;i<=n;i++) {
		int r=0,r2=0,Min=1e9,Min2=1e9,u=i&1,v=u^1;
		for (int k=1;k<=n;k++)
			if (aa[k].a<=i) num[aa[k].b]++;
		for (int i=1;i<=n;i++) {
			sum5[i]=0;
			if (sum5[i]<sum3[i]) sum5[i]=sum3[i],sum6[i]=sum4[i];
			else if (sum5[i]==sum3[i]) sum6[i]+=sum4[i],sum6[i]%=Mod;
			
			if (sum5[i]<sum5[i-1]) sum5[i]=sum5[i-1],sum6[i]=sum6[i-1];
			else if (sum5[i]==sum5[i-1]) sum6[i]+=sum6[i-1],sum6[i]%=Mod;
		}
		for (int j=1;j<=n;j++) {
			if (vis[i][j]) {
				int kk=sum5[j]+2,kk1=sum6[j];
				int v1=i,v2=j;
				if (f[v1][v2]<kk) {
					f[v1][v2]=kk;
					cnt[v1][v2]=kk1;
					cnt[v1][v2]%=Mod;
				}
				else if (f[v1][v2]==kk) {
					cnt[v1][v2]+=kk1;
					cnt[v1][v2]%=Mod;
				}
			}
			if (sum3[j]<f[i][j]) sum3[j]=f[i][j],sum4[j]=cnt[i][j];
			else if (sum3[j]==f[i][j]) sum4[j]+=cnt[i][j],sum4[j]%=Mod;
			if (!cnt[i][j]) continue;
			while (r<=j) r++;
			while (!num[r] && r<=n) r++;
			if (r>j && r<=n) {
				int v1=i,v2=r,op=1;
				if (f[v1][v2]<f[i][j]+op) {
					f[v1][v2]=f[i][j]+op;
					cnt[v1][v2]=cnt[i][j];
					cnt[v1][v2]%=Mod;
				}
				else if (f[v1][v2]==f[i][j]+op) {
					cnt[v1][v2]+=cnt[i][j];
					cnt[v1][v2]%=Mod;
				}
			}
			
			while (bb[r2+1].b<=j && r2+1<=n) {
				r2++;
				if (bb[r2].a>i) 
					Min=min(bb[r2].a,Min);
			}	
			if (Min>i && Min<=n) {
				int v1=Min,v2=j,op=1;
				if (f[v1][v2]<f[i][j]+op) {
					f[v1][v2]=f[i][j]+op;
					cnt[v1][v2]=cnt[i][j];
					cnt[v1][v2]%=Mod;
				}
				else if (f[v1][v2]==f[i][j]+op) {
					cnt[v1][v2]+=cnt[i][j];
					cnt[v1][v2]%=Mod;
				}
			}
		}
	}
	cout<<f[n][n]<<" "<<cnt[n][n]<<"\n";
	return 0;
}
```


---

