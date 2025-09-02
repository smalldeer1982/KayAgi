# [ARC115E] LEQ and NEQ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc115/tasks/arc115_e

長さ $ N $ の整数列 $ A_1,A_2,\ldots,A_N $ が与えられます。長さ $ N $ の整数列 $ X_1,X_2,\ldots,X_N $ であって、以下の条件をすべて満たすものはいくつあるか求め、$ 998244353 $ で割った余りを出力してください。

- $ 1\ \leq\ X_i\ \leq\ A_i $
- $ X_i\ \neq\ X_{i+1}\ (1\ \leq\ i\ \leq\ N-1) $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

条件をすべて満たす整数列は以下の $ 6 $ 通りです。 - $ 1,2,1 $ - $ 1,3,1 $ - $ 1,3,2 $ - $ 2,1,2 $ - $ 2,3,1 $ - $ 2,3,2 $

## 样例 #1

### 输入

```
3
2 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
10
158260522 877914575 602436426 24979445 861648772 623690081 433933447 476190629 262703497 211047202```

### 输出

```
524691026```

# 题解

## 作者：Xu_brezza (赞：12)

容斥神仙题 qwq。

## 题意

给定一个长度为 $n$ 的序列 $a_1,a_2,\cdots ,a_n$，输出满足如下条件的序列 $x$ 的方案数：

1. $1\leq x_i\leq a_i$
2. $x_i\neq x_{i+1}(1\leq i\leq n-1)$

- $2\le n\le 5\times 10^5,1\le a_i\le 10^9$

## Solution

首先我们规定形如 $x_{i} = x_{i + 1}$ 的点为坏点。

令 $f_{i}$ 表示至少有 $i$ 个坏点的方案数，那么套上容斥的式子：

$$ ans = \sum_{i=0}^{n-1} (-1) ^ i\times f_i $$

那么我们令所有的坏点向左合并，即 $x_i \gets x_i,x_{i + 1} $ 其中 $x_i = x_{i + 1}$，假设有 $k$ 个坏点，那么恰好减少 $k$ 个数，而这等价于将序列划分成 $n - k$ 段，每段内都是相同的数。

注意这里只是强制限定了每一段内相同，不代表相邻段之间必须不同，因为我们是**至少**。

所以我们考虑用 dp 求出这样划分的方案数，令 $dp[i][j]$ 表示填了 $i$ 个数，划分出 $j$ 段的方案数。

那么对答案进行改写：

$$ ans = \sum_{i = 0}^{n - 1} (-1)^i \times dp[n][n - i] $$

先考虑朴素转移：

$$ dp[i][j] = \sum_{k = 0}^{i - 1} dp[k][j - 1] \times \min_{o = k + 1}^{i}a_o $$

代表添加一段 $(k + 1,i)$ 的线段，有 $\min_{o = k + 1}^{i}a_o$ 种填法。

复杂度还不够优秀。

我们发现最后只关心划分出的段数的**奇偶**，所以可以直接改写成 $dp[i][0/1]$ 代表划分成 ``偶数/奇数`` 段的方案数。

方程又变成了：

$$ dp[i][op] = \sum_{k = 0}^{i - 1} dp[k][op\text{ xor }1] \times \min_{o = k + 1}^{i}a_o $$

那么前面那个东西可以前缀和优化。

后面那一坨，我们维护单调栈，找到左边第一个小于 $a[i]$ 的。

- 如果不存在这样的，那么 $a[i]$ 就是最小值，直接前缀和乘上即可。
- 否则考虑令前面的位置为 $p$ ，则 $[p + 1...i,i]$ 这些区间都是以 $a[i]$ 为最小值的。也就是说你可以从 $dp[p...i - 1]$ 转移过来，因为我们的转移相当于在这个位置后面插入一段。在这之前的最小值都和 $a[i]$ 没关系！！所以直接继承 $dp[p][op]$ 就是贡献，因为这个玩意就等价于前面的 $\sum dp[k][op \text{ xor } 1] \times \min $。

最后根据 $n$ 的奇偶性，我们可以得出 $dp[n][0/1]$ 对应的奇偶性，也就是 $n - 2\times k$ 和 $n - (2\times k + 1)$ 的奇偶性，用偶的减去奇的即可。


``` cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i<(b);++i)
#define rrep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=-x;
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
const int N = 5e5 + 5;
const int mod = 998244353;
inline void add(int &x,int y){
    if((x += y) >= mod)x -= mod;
}
vector<int>S;
int dp[N][2],s[N][2];
int a[N],n;
signed main(){
    read(n);
    rep(i,1,n)read(a[i]);
    dp[0][0] = s[0][0] = 1;
    rep(i,1,n){
        while(!S.empty() && a[S.back()] >= a[i])S.pop_back();
        if(S.empty()){
            for(int x : {0,1})dp[i][x] = 1ll * s[i - 1][x ^ 1] * a[i] % mod;
        }
        else{
            for(int x : {0,1})dp[i][x] = (dp[S.back()][x] + 1ll * (s[i - 1][x ^ 1] - s[S.back() - 1][x ^ 1] + mod) * a[i] % mod) % mod;
        }
        S.push_back(i);
        s[i][0] = (s[i - 1][0] + dp[i][0]) % mod;
        s[i][1] = (s[i - 1][1] + dp[i][1]) % mod;
    }
    int ans = (dp[n][0] - dp[n][1] + mod) % mod;
    if(n & 1)ans = 1ll * ans * (mod - 1) % mod;
    printf("%d",ans);
}
```

---

## 作者：xiezheyuan (赞：7)

[双倍快乐](https://www.luogu.com.cn/problem/CF1591F)

[三倍快乐](https://www.luogu.com.cn/problem/CF1585F)

## 简要题意

有 $n$ 个空，第 $i$ 个空要填 $1\sim b_i$ 的一个数。且相邻两个空不能填相同的数。问有多少种填数方案，对 $998244353$ 取模。

$1 \leq n \leq 5 \times 10^5,1 \leq b_i \leq 10^9$

## 思路

如果有条件建议大家直接看 [英文题解](https://codeforces.com/blog/entry/97845)。个人认为讲得最清晰。

首先考虑正难则反的原则。如果直接对相邻不同的方案计数比较麻烦，不如直接对相邻相同的方案计数。最后再用总方案数减去它。

设 $f(i,j)$ 表示前 $i$ 个数有 $j$ 个相邻的数相同。不如通过容斥思想换一种说法，将 $[1:i]$ 部分划分成 $i-j+1$ 段，每一段的空填的都是一样的。注意到我们这里其实隐含了 **至少** $i-j+1$ 段这个条件。

于是我们干脆换一个说法。直接设 $f(i,j)$ 表示前 $i$ 个数可以分成 $j$ 段，每一段的数都是相同的。

然后枚举断点就可以得到状态转移方程：

$$
f(i,j)=\sum_{k=1}^{i}f(k-1,j-1)\times \left(\min_{s=k}^{i}a_s\right)
$$

时间复杂度 $O(n^3)$ 空间复杂度 $O(n^2)$。均难以接受。

先来优化空间，不难发现我们其实可以按照 $j$ 的奇偶性压掉 $j$ 这一维。

然后考虑优化时间复杂度。用 ST 表优化掉 $\min$ 的复杂度只能做到 $O(n^2)$。我们需要更强力的方法。

先维护 $f$ 的前缀和 $g$。然后考虑带 $\min$ 的那一个系数。

我们发现可以找到左侧第一个小于 $a_i$ 的数 $a_s$。那么这一段的系数都是相同的，直接用前缀和去乘上 $a_i$ 即可。

最后还有前面的部分。我在这一部分想了很久。后来发现其实就是：

$$
\sum_{k=1}^{s}f(k-1,j-1)\times\left(\min_{t=k}^{s} a_t\right)
$$

这不就是 $f(s,j)$ 吗？

于是我们就可以 $O(n)$ 解决这个 dp。

最后答案应该是：

$$
f(n,n)-f(n,n-1)
$$

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

const int mod = 998244353;
const int N = 5e5+5;
int f[N][2],g[N][2];
int n,a[N],stk[N],top;

int M(int x){
	return (x%mod+mod)%mod;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[0][0]=1;f[0][1]=0;
	g[0][0]=1;g[0][1]=0;
	for(int i=1;i<=n;i++){
		while(top && a[stk[top]] >= a[i]) top--;
		int cur = top?stk[top]:0;
		stk[++top]=i;
		if(!cur){
			f[i][0]=M(g[i-1][1]*a[i]);
			f[i][1]=M(g[i-1][0]*a[i]);
		}
		else{
			f[i][0]=M(f[cur][0]+M(M(M(g[i-1][1]-g[cur-1][1]))*a[i]));
			f[i][1]=M(f[cur][1]+M(M(M(g[i-1][0]-g[cur-1][0]))*a[i]));
		}
		g[i][0] = M(g[i-1][0] + f[i][0]);
		g[i][1] = M(g[i-1][1] + f[i][1]);
//		for(int j=1;j<=i;j++){
//			int ret=INT_MAX;
//			for(int k=j;k<=i;k++){
//				ret = min(ret, a[k]);
//			}
//			f[i][0] += f[j-1][1] * ret % mod;
//			f[i][0] %= mod;
//			f[i][1] += f[j-1][0] * ret;
//			f[i][1] % mod;
//		}
	}
	if(n&1) cout<<(M(f[n][1]-f[n][0]))<<'\n';
	else cout<<(M(f[n][0]-f[n][1]))<<'\n';
	return 0;
}
```


---

## 作者：xfrvq (赞：6)

一眼 $\tt dp$，考虑 $dp_{i,j}$ 为已经 $\tt dp$ 到第 $i$ 位，上一位是 $j$ 的方案数。

考虑转移：

$$
\begin{aligned}
dp_{i,j}&=\displaystyle\sum_{k=1}^{A_{i-1}}[k\ne j]dp_{i-1,k}\\
&=\displaystyle\sum_{k=1}^{A_{i-1}}dp_{i-1,k}-dp_{i-1,j}
\end{aligned}
$$

这是时空 $\mathcal O(nv)$ 的，空间可以通过滚动数组优化至 $O(v)$。

我们并不满足于此，考虑用数据结构维护当前的 $dp$。（注意到因为滚动数组，所以它是一维）

考虑具体的 $\tt dp$ 实现。

+ 初始化：$dp_i=[i\le A_1]$。
+ 转移：枚举 $i\in[2,n]$。
+ 记录 $S=\displaystyle\sum_{i=1}^{A_{i-1}}dp_i$。
+ $\forall i\in[1,A_{i-1}],dp_i\gets-dp_i$。
+ $\forall i\in[1,A_i],dp_i\gets dp_i+S$。（执行后已经完成转移柿子）
+ $\forall i\in(A_i,\infty),dp_i=0$。（清空便于下次转移）
+ 转移已经完成。

区间取负，区间清零，区间加…这启示我们使用线段树。线段树需要支持加法（区间加）和乘法（区间乘 $-1$，区间乘 $0$）。

你还要离散化？？我们首先正常的离散化，然后考虑离散化后贡献发生的变化。对于新的 $a_{1\cdot\cdot n}$，$a_i$ 的初始贡献要乘上 $A_i-A_{i-1}$。然后对于原来 $i$ 位置的值是 $val$，$i$ 位置的实际值就是 $val\times(A_i-A_{i-1})$。这个改改线段树即可。

代码其实挺好写的，因为赛时写了一个把三个原始操作融合起来的线段树，三个 $\tt tag$ 出了细节问题没调出来/kk

```cpp
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define Rep(i,a,b) for(int i = (a);i >= (b);--i)

const ll mod = 998244353;
const int N = 1e6 + 5;

int n,k; ll a[N],b[N],val[N];

namespace ST{
	const int S = N << 2;
	
	ll sum[S],cnt[S],ta[S]; char tm[S];
	
	#define lc (i << 1)
	#define rc (i << 1 | 1)
	#define mid ((L + R) >> 1)
	#define now i,L,R
	#define ls lc,L,mid
	#define rs rc,mid + 1,R
	#define id int i = 1,int L = 1,int R = k + 1
	#define psu sum[i] = (sum[lc] + sum[rc]) % mod
	
	void Add(int i,ll x){
		(ta[i] += x) %= mod;
		(sum[i] += cnt[i] * x % mod) %= mod;
	}
	
	void Mul(int i,ll x){
		(tm[i] *= x) %= mod;
		(ta[i] *= x) %= mod;
		(sum[i] *= x) %= mod;
		if(sum[i] < 0) sum[i] += mod;
	}
	
	void psd(int i){
		if(!i) return;
		Mul(lc,tm[i]); Mul(rc,tm[i]);
		Add(lc,ta[i]); Add(rc,ta[i]);
		tm[i] = 1; ta[i] = 0;
	}
	
	void build(id){
		tm[i] = 1; ta[i] = 0;
		if(L == R){
			cnt[i] = val[L];
			if(L <= a[1]) sum[i] = val[L];
			return;
		}
		build(ls); build(rs); psu; cnt[i] = (cnt[lc] + cnt[rc]) % mod;
	}
	
	void add(int l,int r,ll x,id){
		if(l <= L && R <= r) return Add(i,x); psd(i);
		if(l <= mid) add(l,r,x,ls);
		if(r > mid) add(l,r,x,rs); psu;
	}
	
	void mul(int l,int r,ll x,id){
		if(l <= L && R <= r) return Mul(i,x); psd(i);
		if(l <= mid) mul(l,r,x,ls);
		if(r > mid) mul(l,r,x,rs); psu;
	}
	
	ll qry(int l,int r,id){
		if(l <= L && R <= r) return sum[i]; psd(i);
		ll res = 0;
		if(l <= mid) res = qry(l,r,ls);
		if(r > mid) (res += qry(l,r,rs)) %= mod;
		return res;
	}
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%lld",a + i),b[i] = a[i];
	sort(b + 1,b + n + 1);
	k = unique(b + 1,b + n + 1) - b - 1;
	rep(i,1,n) a[i] = lower_bound(b + 1,b + k + 1,a[i]) - b;
	rep(i,1,k) val[i] = b[i] - b[i - 1];
	ST::build();
	rep(i,2,n){
		ll sum = ST::qry(1,a[i - 1]);
		ST::mul(1,a[i - 1],-1);
		ST::add(1,a[i],sum);
		ST::mul(a[i] + 1,k + 1,0);
	}
	printf("%lld\n",ST::qry(1,n));
	return 0;
}
```

---

## 作者：NoGoshPlease (赞：4)

来点不用容斥的不一样的做法。

考虑 $a_i$ 值较小的那些对其他位置的影响是简单的，必定会减少恰好 $1$ 种可能情况。

所以我们考虑先确定 $a$ 值较小的位置，这启发我们用笛卡尔树。

我们建立小根笛卡尔树。

考虑对于笛卡尔树的一个子树，设其代表的区间为 $[l,r]$，分割点为 $p$。（这里我们只讨论 $1<l\le r<n,l<p<r$ 的情况，其他情况是简单的）

发现这个区间两边填多少其实不重要，重要的是两边填的东西是否相等。

于是，我们记 $f_{l,r,0/1}$ 表示区间两边填的数是否相等，该区间内的填数方法数。

如果两边不相等：
- 如果分割点和两边都不相等，有 $a_p-2$ 种选法。
$$f_{l,r,0}\gets f_{l,p-1,0}\times f_{p+1,r,0}\times (a_p-2)$$
- 如果分割点和某一边相等，那么只有 $1$ 种方法。
$$f_{l,r,0}\gets f_{l,p-1,1}\times f_{p+1,r,0}$$
$$f_{l,r,0}\gets f_{l,p-1,0}\times f_{p+1,r,1}$$

如果两边相等：
- 如果分割点和两边都不相等，有 $a_p-1$ 种选法。
$$f_{l,r,1}\gets f_{l,p-1,0}\times f_{p+1,r,0}\times (a_p-1)$$
- 如果分割点和某一边相等，那么只有 $1$ 种方法。
$$f_{l,r,1}\gets f_{l,p-1,1}\times f_{p+1,r,1}$$

总复杂度 $O(n)$。

代码如下（使用的是 ST 表建笛卡尔树）。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005,mod=998244353;
int n,a[N];
int Log2[N],st[N][20];
void getst()
{
	Log2[1]=0;
	for(int i=2;i<=n;i++) Log2[i]=Log2[i/2]+1;
	for(int i=1;i<=n;i++) st[i][0]=i;
	for(int j=1;j<=Log2[n];j++)
		for(int i=1;i<=n;i++) st[i][j]=a[st[i][j-1]]<a[st[i+(1<<j-1)][j-1]]?st[i][j-1]:st[i+(1<<j-1)][j-1];
}
int find(int l,int r)
{
	int k=Log2[r-l+1];
	return (a[st[l][k]]<a[st[r-(1<<k)+1][k]])?st[l][k]:st[r-(1<<k)+1][k];
}
int idx;
int f[N][2],ls[N],rs[N];
void work(int l,int r,int x)
{
	if(l==r)
	{
		if(l==1||r==n) f[x][0]=a[l]-1;
		else f[x][0]=a[l]-2,f[x][1]=a[l]-1;
		return;
	}
	int p=find(l,r);
	if(l<p) ls[x]=++idx,work(l,p-1,idx);
	if(p<r) rs[x]=++idx,work(p+1,r,idx);
	if(l==1&&r==n)
	{
		if(p==l) f[x][0]=(long long)f[rs[x]][0]*a[p]%mod;
		else if(p==r) f[x][0]=(long long)f[ls[x]][0]*a[p]%mod;
		else f[x][0]=(long long)f[ls[x]][0]*f[rs[x]][0]%mod*a[p]%mod;
	}
	else if(l==1)
	{
		if(p==l) f[x][0]=((long long)f[rs[x]][0]*(a[p]-1)+(long long)f[rs[x]][1])%mod;
		else if(p==r) f[x][0]=(long long)f[ls[x]][0]*(a[p]-1)%mod;
		else f[x][0]=((long long)f[ls[x]][0]*f[rs[x]][0]%mod*(a[p]-1)+(long long)f[ls[x]][0]*f[rs[x]][1])%mod;
	}
	else if(r==n)
	{
		if(p==l) f[x][0]=(long long)f[rs[x]][0]*(a[p]-1)%mod;
		else if(p==r) f[x][0]=((long long)f[ls[x]][0]*(a[p]-1)+(long long)f[ls[x]][1])%mod;
		else f[x][0]=((long long)f[ls[x]][0]*f[rs[x]][0]%mod*(a[p]-1)+(long long)f[ls[x]][1]*f[rs[x]][0])%mod;
	}
	else
	{
		if(p==l)
		{
			f[x][0]=((long long)f[rs[x]][0]*(a[p]-2)+(long long)f[rs[x]][1])%mod;
			f[x][1]=(long long)f[rs[x]][0]*(a[p]-1)%mod;
		}
		else if(p==r)
		{
			f[x][0]=((long long)f[ls[x]][0]*(a[p]-2)+(long long)f[ls[x]][1])%mod;
			f[x][1]=(long long)f[ls[x]][0]*(a[p]-1)%mod;
		}
		else
		{
			f[x][0]=((long long)f[ls[x]][0]*f[rs[x]][0]%mod*(a[p]-2)+(long long)f[ls[x]][1]*f[rs[x]][0]+(long long)f[ls[x]][0]*f[rs[x]][1])%mod;
			f[x][1]=((long long)f[ls[x]][0]*f[rs[x]][0]%mod*(a[p]-1)+(long long)f[ls[x]][1]*f[rs[x]][1])%mod;
		}
	}
//	printf("%d %d:%d %d\n",l,r,f[x][0],f[x][1]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	getst();
	idx=1;
	work(1,n,1);
	printf("%d\n",f[1][0]);
}
```

---

## 作者：Rosabel (赞：3)

像 @TernaryTree 一样有点无脑 ds 的做法。

先想想暴力 dp 怎么做。状态 $f_{i,j}$ 表示第 $i$ 个数选取值为 $j$ 的状态数。易得方程：

$$f_{i,j}=\sum_{k\neq j}f_{i-1,k}[j\le a_i]$$

$\Theta(nV^2)$。

**【优化 1】**

稍微转化一下，变成：

$$f_{i,j}=(\sum_{k}f_{i-1,k})-f_{i-1,j}$$

中间的 $\sum$ 对于所有 $j$ 都是相等的，所以可以预处理。这里把 $k$ 这维优化掉了。

$\Theta(nV)$。

**【优化 2】**

发现 $a$ 数组所有可能取值中所构成的不同等价类个数最多不超过 $n$，所以可以统一处理同一等价类。

设$b_j$ 表示标号为 $j$ 的等价类大小，$g_i=\sum_{j}f_{i,j}$。

$$f_{i,j}=b_j(g_{i-1}-\frac{f_{i-1,j}}{b_j})=b_jg_{i-1}-f_{i-1,j}$$

**注：此时 $f_{i,j}$ 表示第 $i$ 个数取值在第 $j$ 个等价类上的所有数方案和。**

$\Theta(n^2)$。

**【优化 3】**

观察 **【优化 2】** 的式子，对于每一个合法的 $j$ 必然形如 $y=kx+b$，所有的 $j$ 对应的 $k$ 和 $b$ 都一样。这是一个很重要的观察。意味着我们只需要批量进行一次函数嵌套操作。我们会发现转移的时候 $g_{i-1}$ 和 $-1$（$f_{i-1,j}$ 的系数） 是常量，$f_{i-1,j}$ 是自变量，$f_{i,j}$ 是因变量（忽视 $b_j$，原因可以自行理解一下），故可以得到这个一次函数。由于所有合法 $j$ 构成的一次函数相同，所以相当于区间覆盖这个一次函数。于是可以用线段树。线段树维护 $k,x,b,sum$。每次区间修改套上一次函数 $y:-x+g_{i-1}$ 。然后其余部分清空，即 $x\leftarrow0,k\leftarrow1,b\leftarrow0$。注意要记得维护 $sum$，由于区间是多个一次函数的和，所以 $b$ 的真实值要乘上 $sum$。

$\Theta(n\log n)$。

[code](https://atcoder.jp/contests/arc115/submissions/57207494)

最后的最后，膜拜 @夜明 姐姐和 @TernaryTree 姐姐。

---

## 作者：Lates (赞：3)

三倍经验题解区，都是对整体使用子集反演。

这里有种不同的看法。考虑局部性限制，可以直接将容斥融入 dp 中。

设 $dp_i$ 表示只考虑前 $i$ 个限制的答案。

先不考虑限制。$dp_i=dp_{i-1} \times a_i$ （错误的）

发现需要多算了 $b_i = b_{i-1}$ 的，那么 $dp_{i}=dp_{i-1}\times a_i - dp_{i-2}\times \min(a_{i-1},a_{i-2})$ （错误的）

发现**多减了** $b_i=b_{i-1}=b_{i-2}$ 的。因为 $dp_{i-1}\times a_i$ 中并没有考虑这种。

于是可以得到 

$$dp_{i}=\sum_{j=0}^{i} (-1)^{i-j+1}dp_j \min_{k=j+1}^i a_k$$

（正确的）

将此类式子用单调栈优化至线性，其他题解已经完备，不再赘述。

summary

有如下的思考方式：

1. 不考虑当前限制时的贡献：$ dp_{i-1} \times a_i $ 
2. 需要减去的贡献：**有且仅有** $b_i=b_{i-1}$ 的排列。"有且仅有" 是因为 $dp_{i-1}$ 的保证前面的都合法。 
3. 递归计算，并更新限制：发现 2.把 $b_i, b_{i-1}$ 缩为一点，并且有限制 $\min(a_i,a_{i-1})$。发现这时回到 1. 了。

---

## 作者：DengDuck (赞：1)

比较有意思的容斥计数动态规划技巧题。

首先直觉告诉我们合法方案数不好求，所以正难则反考虑求不合法的情况，不合法的情况也不好求，但是我们可以比较自然地想到容斥。

也就是求 $F(i)$ 表示至少有 $i$ 个坏点的方案数。

然后考虑动态规划，设 $f_{i,j}$ 表示前 $i$ 项划分成 $j$ 部分，部分内部是相同的数字，但是相邻的部分不要求不同（因为你是容斥，保证至少多少个不同即可）。

显然 $F(i)=f_{n,n-i}$。

我们发现这个东西和最小值有关系，一个部分的取值方案就是最小值，这点比较显然。

方程是：

$$
f_{i,j}=\sum_{k=1}^if_{k-1,j-1}\times\min_{x=k}^ia_x
$$

由于容斥这个东西无非是奇数减偶数加的形式，所以我们可以减少状态，直接把 $f_{i,j}$ 换成 $f_{i,0/1}$，表示部分数量的奇偶，最后答案跟 $n$ 的奇偶性有关，你就看看 $f_{n,0}-f_{n,1}$ 还是 $f_{n,1}-f_{n,0}$。

$$
f_{i,j}=\sum_{k=1}^if_{k-1,j\oplus 1}\times\min_{x=k}^ia_x
$$

我们发现在最小值不变的区间内可以前缀和直接求，所以考虑维护一个单调栈来弄最小值，难道我们要枚举单调栈，拆成多个前缀和吗？我一开始是这么想的，但是发现可以拆式子。

我们设单调栈记录的上一个可以使最小值改变的项的位置为 $pos$。

$$
f_{i,j}=\sum_{k=1}^if_{k-1,j\oplus 1}\times\min_{x=k}^ia_x
$$

$$
f_{i,j}=\sum_{k=1}^{pos}f_{k-1,j\oplus 1}\times\min_{x=k}^ia_x+[pos+1,i]
$$

这里的 $[pos+1,i]$ 我用来指代 $k\in[pos+1,i]$ 给 $f_{i,j}$ 的贡献，就是一个前缀和可以求的东西。

然后我们已经知道 $a_{pos}$ 比 $a_j(j\in[pos+1,i])$ 小，所以式子可以改改。

$$
f_{i,j}=\sum_{k=1}^{pos}f_{k-1,j\oplus 1}\times\min_{x=k}^{pos}a_x+[pos+1,i]
$$

这玩意的形式很眼熟啊！所以考虑替换。

$$
f_{i,j}=f_{pos,j}+[pos+1,i]
$$

这就可以做了，时间复杂度为 $\mathcal O(n)$。

然后一开始有的地方没想明白因为要枚举单调栈，然后参考题解写了 `vector` 最后发现就是模拟栈，不过这好像确实是个好习惯，以后就这么写了吧 QAQ。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=5e5+5;
//const LL M;
const LL mod=998244353;
//const LF eps;
//const LL P;
vector<LL>q;
LL n,a[N],f[N][2],sum[N][2];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	f[0][0]=sum[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&a[q.back()]>=a[i])q.pop_back();
		if(q.empty())for(int x:{0,1})f[i][x]=sum[i-1][1-x]*a[i]%mod;
		else for(int x:{0,1})f[i][x]=(f[q.back()][x]+(sum[i-1][1-x]-sum[q.back()-1][1-x]+mod)%mod*a[i]%mod)%mod;
		q.pb(i);
		for(int x:{0,1})sum[i][x]=(sum[i-1][x]+f[i][x])%mod;
	}
	LL ans=(f[n][0]-f[n][1]+mod)%mod;
	if(n&1)ans=ans*(mod-1)%mod;
	cout<<ans<<endl;
	return 0;
}
//RP++
```

---

## 作者：Supor__Shoep (赞：1)

我这场打的 VP，结果 E 思考的时间比 A 还少。。

但是我觉得我能想出这道题还是很有意义的，写篇题解记录一下。

首先应该都不难想到动态规划吧？我们先使用暴力 DP：设 $dp_{i,j}$ 表示处理完前 $i$ 个数，第 $i$ 个数为 $j$ 的方案数。我们考虑进行分类讨论：

- $a_i≥a_{i-1}$：此时 $j$ 有两种取值范围，分别是 $1\leq j\leq a_{i-1}$ 以及 $a_{i-1}<j\leq a_i$。对于后者的范围，我们发现 $j$ 怎么取都不会影响到 $i-1$ 的取值，我们设 $f_i=\sum_{1\leq j\leq a_i}dp_{i,j}$，因此这一部分的 $dp_{i,j}=f_{i-1}$。对于 $1\leq j\leq a_{i-1}$，我们就要考虑到 $x_{i-1}≠x_i$ 的限制。根据容斥原理，我们用 $f_{i-1}$ 减去 $dp_{i-1,j}$ 的情况就行了，于是得到下面的转移：

$$dp_{i,j}=
\begin{cases}
f_{i-1}-dp_{i-1,j} & 1\leq j\leq a_{i-1} \\
f_{i-1} & a_{i-1}<j\leq a_i
\end{cases}
$$

- $a_i<a_{i-1}$：这个时候无论 $j$ 取 $[1,a_i]$ 的什么值都有可能受到 $x_{i-1}$ 的影响。不过思路还是用上面的容斥，我们得到：

$$dp_{i,j}=f_{i-1}-dp_{i-1,j}$$

知道这些之后，我们要得到的答案就是：

$$ans=\sum_{i=1}^n\sum_{j=1}^{a_{i}}dp_{i,j}=\sum_{i=1}^nf_i$$

因此，若要在题目所给的数据范围限制下快速得到答案，我们必须想办法快速处理出 $f_i$ 的值。

#### 0x01

对于 $a_i≥a_{i-1}$ 的情况，我们直接加和：

$$
\begin{aligned}
f_i&=\sum_{j=1}^{a_{i-1}}(f_{i-1}-dp_{i-1,j})+\sum_{j=a_{i-1}+1}^{a_i}f_{i-1}\\
&=a_{i-1}\times f_{i-1}+(a_i-a_{i-1})\times f_{i-1}-\sum_{j=1}^{a_{i-1}}dp_{i-1,j}\\
\end{aligned}
$$

根据 $f_i$ 的定义可知，等式右边减去的式子其实就是 $f_{i-1}$，因此合并同类项得到：

$$f_i=f_{i-1}\times (a_i-1)$$

#### 0x02

对于 $a_i<a_{i-1}$ 的情况，我们同样进行数学计算：

$$
\begin{aligned}
f_i&=\sum_{j=1}^{a_i}(f_{i-1}-dp_{i-1,j})\\
&=a_i\times f_{i-1}-\sum_{j=1}^{a_i}dp_{i-1,j}
\end{aligned}
$$

化简最多也就能变成这样，内层的求和还是不能省去。本题有价值的思路来了：我们想象一下 $\sum_{j=1}^{a_i}dp_{i-1,j}$ 的实际意义。我们**假设现在的 $a_{i-1}$ 不再是原来的 $a_{i-1}$，而是被强制修改为了 $a_i$ 的值**，那么 $\sum_{j=1}^{a_{i-1}}dp_{i-1,j}=f_{i-1}$ 其实就是 $\sum_{j=1}^{a_i}dp_{i-1,j}$。

于是 $\sum_{j=1}^{a_i}dp_{i-1,j}$ 就相当于把 $a_{i-1}$ 换成 $a_i$ 之后所处理出来的 $f_{i-1}$，令这个 $f_{i-1}$ 为 $f'_{i-1}$。所以：

$$f_{i}=a_i\times f_{i-1}-f'_{i-1}$$

我们再继续展开，去考虑 $f'_{i-1}$ 的求法。其实就是不断重复上述过程进行递归，直到当前已经递归到了边界或者 $a_{i-1}\leq a_i$ 的情况。

但是极限数据不允许我们暴力递归。我们令 $f'_j$ 表示当 $a_j=a_i$ 时处理出来的 $f_j$。为了方便分析，我们造一组数据 $a=\{1,3,3,3,2\}$。接着，我们按照上述方法求 $f_5$：

$$
\begin{aligned}
f_5&=a_5\times f_4-f'_4\\
&=a_5\times f_4-a_5\times f_3+f'_3\\
&=a_5\times f_4-a_5\times f_3+a_5\times f_2-f'_2\\
&=a_5\times f_4-a_5\times f_3+a_5\times f_2-f_1\times (a_5-1)\\
&=a_5\times (f_4-f_3+f_2)-f_1\times (a_5-1)
\end{aligned}
$$

结合上述推理，我们可以使用单调栈求出 $[1,i-1]$ 中最靠后的 $\leq a_i$ 的元素下标 $l_i$，则有：

$$f_i=a_i\times(f_{i-1}-f_{i-2}+f_{i-3}\dots ±f_{l_i+1})-[±f_{l_i}\times(a_i-1)]$$

不难发现可以通过将 $i$ 分为奇数和偶数去处理前缀和，然后求出 $f_{i-1}-f_{i-2}+f_{i-3}\dots$ 的值，后面的 $f_{l_i}\times (a_i-1)$ 的正负判断也可以利用 $i-l_i$ 的奇偶。

最后注意一下各种取模就行了，代码也比较短小：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
const int MOD=998244353;
int n,a[MAXN];
long long dp[MAXN],sum[MAXN],num[MAXN];
int stk[MAXN],cnt,l[MAXN];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		while(cnt&&a[stk[cnt]]>a[i])	cnt--;
		l[i]=stk[cnt],stk[++cnt]=i;
	}
	dp[1]=a[1]%MOD,sum[1]=a[1]%MOD;
	for(int i=2;i<=n;i++)
	{
		if((i-1)&1)	dp[i]=sum[i-1]+num[l[i]]-sum[l[i]]-num[i-1]+MOD*2,dp[i]%=MOD;
		else	dp[i]=num[i-1]+sum[l[i]]-num[l[i]]-sum[i-1]+MOD*2,dp[i]%=MOD;
		dp[i]*=a[i],dp[i]%=MOD;
		int g=((i-l[i]-1)&1)?-1:1;
		if(!l[i])	dp[i]+=g*a[i],dp[i]+=MOD,dp[i]%=MOD;
		else	dp[i]+=dp[l[i]]*(a[i]-1)%MOD*g,dp[i]+=MOD,dp[i]%=MOD;
		if(i&1)	sum[i]=sum[i-2]+dp[i],num[i]=num[i-1];
		else	num[i]=num[i-2]+dp[i],sum[i]=sum[i-1];
		sum[i]%=MOD,num[i]%=MOD;
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：kkksc03wzl (赞：1)

# 大家好，我热爱数据结构 #
所以我要提供一个无脑的线段树写法

## STEP 1 ##
首先因为线段树是个专门优化暴力的东西，那我们不妨考虑一个暴力的状态转移，设 $dp_{i,j}$ 表示前 $i$ 个数已经处理好，而且 $X_{i}$ 为 $j$ 的方案个数。

显然，我们有 $dp_{i,j}$ 为上一层的和减掉 $dp_{i-1,j}$ ，具体意义就是当前这一行如果选择了 $j$ ,那么上一层就不可以选择 $j$ ，而其他的都可以转移过来。
## STEP2 ##
于是我们考虑线段树。

出题人良心，数据放得刚好可以开动态开店线段树。

我们考虑开一颗线段树维护当前层的所有可能结尾的情况，考虑转移

若 $a_{i-1} \le a_{i}$ , 则先把线段树的全局和取出来，不妨设为 $k$ 再让所有 $1$ 到 $a_{i-1}$ 的位置取相反数反，最后 $1$ 到 $a_{i}$ 区间加 $k$ 即可。

反之，也是类似的，先把 $k$ 取出来，然后相应范围取反，但是因为 $a_{i-1}$ 到 $a_{i}$ 范围小了，所以要把少了的范围上的数全都赋成 $0$ ，最后区间加即可。

然后这道蓝就愉快得切掉了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 998244353
#define lson tr[rt].ls
#define rson tr[rt].rs
using namespace std;
int a[500005];
struct node{
	long long sum,laz;//遇事不决开long long 
	bool rev,zro;
	int ls,rs;
}tr[500005<<5];//空间开够 
int rt,tot;
void zero(int rt){//处理区间清零 
	tr[rt].rev=0;
	tr[rt].sum=tr[rt].laz=0;
	tr[rt].zro=1;
}
void upd(int rt,long long k,bool op,int len){//处理区间取反和区间加 
	if(op){//先更新取反操作 
		tr[rt].sum=-tr[rt].sum;
		tr[rt].laz=-tr[rt].laz;
		tr[rt].rev^=1;
	}if(k){//再处理区间加 
		tr[rt].sum=(tr[rt].sum+len*1ll*k%mod)%mod;
		tr[rt].laz=(tr[rt].laz+k)%mod; 
	}
}void pushup(int rt){tr[rt].sum=(tr[lson].sum+tr[rson].sum)%mod;}
void pushdown(int &rt,int l,int r){
	if(!lson)lson=++tot;//动态开点 
	if(!rson)rson=++tot;
	if(tr[rt].zro)zero(lson),zero(rson),tr[rt].zro=0;//先处理区间清零 
	int mid=l+r>>1;
	bool op=tr[rt].rev;
	long long k=tr[rt].laz;
	tr[rt].laz=0,tr[rt].rev=0;//标记清零 
	upd(lson,k,op,mid-l+1);//再处理剩余的标记 
	upd(rson,k,op,r-mid);
}void upd_zero(int &rt,int l,int r,int x,int y){//区间清零 
	if(!rt)rt=++tot,lson=rson=0;
	if(x<=l&&r<=y)return zero(rt),void();
	int mid=l+r>>1;
	pushdown(rt,l,r);
	if(x<=mid)upd_zero(lson,l,mid,x,y);
	if(y>mid)upd_zero(rson,mid+1,r,x,y);
	pushup(rt);
}
void update(int &rt,int l,int r,int x,int y,long long k,bool op){//区间加和区间取反 
	if(!rt)rt=++tot;
	if(x<=l&&r<=y)return upd(rt,k,op,r-l+1),void();
	int mid=l+r>>1;
	pushdown(rt,l,r);
	if(x<=mid)update(lson,l,mid,x,y,k,op);
	if(y>mid)update(rson,mid+1,r,x,y,k,op);
	pushup(rt);
}long long query(int &rt,int l,int r,int x,int y){//其实没用 
	if(!rt)rt=++tot;
	if(x<=l&&r<=y)return tr[rt].sum;
	int mid=l+r>>1;
	pushdown(rt,l,r);
	long long ans=0;
	if(x<=mid)ans+=query(lson,l,mid,x,y);
	if(y>mid)ans+=query(rson,mid+1,r,x,y);
	return ans%mod;
}
int main(){
	memset(tr,0,sizeof tr);
	int n;
	scanf("%d",&n);
	int mx=0;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		mx=max(mx,a[i]);
	}
	update(rt,1,mx,1,a[1],1,0);
	for(int i=2; i<=n; i++){
		if(a[i]>=a[i-1]){
			long long k=tr[rt].sum;
			update(rt,1,mx,1,a[i-1],0,1);
			update(rt,1,mx,1,a[i],k,0);
		}else{
			long long k=tr[rt].sum;
			upd_zero(rt,1,mx,a[i]+1,a[i-1]);
			update(rt,1,mx,1,a[i],0,1);
			update(rt,1,mx,1,a[i],k,0);
		}
	}printf("%lld\n",(tr[1].sum%mod+mod)%mod);//因为有相反数，所以有可能是负数，应当加mod 
	return 0;
} 
```
码风略丑，请谅解

---

## 作者：Unnamed114514 (赞：0)

肯定是要容斥的。

你定义 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的方案数。

就有 $f_{i,j}=\sum f_{k-1,j-1}*\min\limits_{w=k}^i a_i$。

然后因为你容斥的式子，加/减只跟 $j$ 的奇偶性有关，所以第二维可以变成 $0/1$。

考虑优化转移。

`min` 不好处理，把它拆掉就行了。

单调栈找到前面第一个小于 $a_i$，然后和它一段的情况段数不变，转移容易处理。

不和它一段的情况都是乘 $a_i$，直接用前缀和维护就完了。

---

## 作者：TernaryTree (赞：0)

来点没有脑子的做法。

$f_{i,j}$ 表示前 $i$ 个数的序列，最后一个是 $j$ 的方案数。

那么有

$$
f_{i,j}=
\begin{cases}
(\sum\limits_{k=1}^{a_{i-1}}f_{i-1,k})-f_{i-1,j}&(j\le a_i) \\
0&(j\gt a_i)
\end{cases}
$$

注意到，一次 $f_{i-1,j}$ 到 $f_{i,j}$ 的转移是取相反数后加上上一个版本的 $f$ 和，$\gt a_i$ 的要特别赋值为 $0$。

取相反数看成区间 $\times (-1)$，赋值为 $0$ 看成区间 $\times 0$，所以维护一个【模板】线段树 2 即可。

值域太大，无脑改成动态开点即可。

代码轻微卡常。

[Code](https://www.luogu.com.cn/paste/t4cubmha)

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑 DP。

定义状态函数 $f_{i,j}$ 表示前 $i$ 个数，有至少 $j$ 组数相邻且相等的方案数。不难发现，这样分出来 $j$ 组，实际上就是有不超过 $n-j$ 段连续的子序列的方案数。重新定义一下就有：$f_{i,j}=\sum\limits_{k=0}^{i-1} f_{k,j-1}\times \min\limits_{w=k+1}^{i}a_w$。

答案是 $ans=\sum\limits_{i=1}^{n}(-1)^{n-i}\times f_{n,i}$。

发现这里的 $j$ 实际上只用关系其奇偶性，所以有优化：$f_{i,j}=\sum\limits_{k=0}^{i-1} f_{k,j\oplus 1}\times \min\limits_{w=k+1}^{i}a_w$。

拆开有：$f_{i,j}=\sum\limits_{k=0}^{l_i-1} f_{k,j\oplus 1}\times \min\limits_{w=k+1}^{i}a_w+
\sum\limits_{k=l_i}^{i-1} f_{k,j\oplus 1} \times a_i$，其中 $l_i$ 表示 $i$ 之前最后一个小于 $a_i$ 的位置。

前半部分就是 $f_{l_i,j}$，所以有：$f_{i,j}=f_{lst_i,j}+a_i \times \sum\limits_{k=lst_i}^{i-1}f_{k,j \oplus 1}$。

求 $\sum\limits_{k=lst_i}^{i-1}f_{k,j \oplus 1}$ 可以用前缀和优化，复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=5e5+10,p=998244353;
int n,a[N],l[N];
int f[N][2],s[N][2];

il int sum(int l,int r,int k){
	if(!l) return s[r][k];
	return ((s[r][k]-s[l-1][k])%p+p)%p;
}

il void solve(){
	n=rd,s[0][0]=1,l[1]=1;
	for(re int i=1;i<=n;++i) a[i]=rd;
	for(re int i=2;i<=n;++i){
		l[i]=i;int x=i-1;
		while(x>=1&&a[x]>=a[i]) l[i]=l[x],x=l[x]-1;
	}
	for(re int i=1;i<=n;++i) if(a[l[i]]>=a[i]) --l[i];
	for(re int i=1;i<=n;++i)
	for(re int j=0;j<=1;++j){
		f[i][j]=(f[l[i]][j]+a[i]*sum(l[i],i-1,j^1)%p)%p;
		s[i][j]=(s[i-1][j]+f[i][j])%p; 
	}
	int ans=0;
	if(n%2==0) ans=((f[n][0]-f[n][1])%p+p)%p;
	else ans=((f[n][1]-f[n][0])%p+p)%p;
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

