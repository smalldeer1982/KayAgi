# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2
2 3```

### 输出

```
4```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
0```

# 题解

## 作者：lyreqwq (赞：11)

容斥 DP 神仙题 qwq。

考虑容斥，钦定 $k$ 个 $i$ 满足 $b_i = b_{i + 1}, \, (1 \le i < n)$，记其方案数为 $F(k)$。

这样，答案即为：
$$
ans = \sum_{k = 0}^{n - 1} (-1) ^ k F(k)
$$
首先有一个转化，钦定 $k$ 个 $i$ 满足 $b_i = b_{i + 1}, \, (1 \le i < n)$，相当于把 $b$ 数组 `unique` 后剩下最多 $n - k$ 个元素。

有了这个性质，不难得到一个 $O(n ^ 3)$ 的朴素做法。设 $f_{i, j}$ 表示考虑前 $i$ 个位置，划分成 $j$ 段的方案数。

DP 转移为：$f_{i, j} = \sum\limits_{k = 1}^{i - 1} f_{k, j - 1} \times \min\limits_{l = k + 1}^{i} a_l$。

但这样复杂度爆炸，怎么办呢？观察转移方程发现一个性质：第二维下标为 $j$ 的所有状态只会由下标为 $j - 1$ 的状态转移得到。而我们最后统计答案时，也只关心 $k$ 的奇偶性来决定容斥系数。于是可以重新设计状态 $f_{i, 0 / 1}$ 表示考虑前 $i$ 个位置，划分成 偶数 / 奇数 段的方案数。

新的转移为：$f_{i, j} = \sum\limits_{k = 1}^{i - 1} f_{k, j \oplus  1} \times \min\limits_{l = k + 1}^{i} a_l$，其中 $\oplus$ 为异或运算符。

可这样还是 $O(n^2)$ 的。柿子前面是一个前缀和形式，不好优化的是后面 $\min$ 的部分。

若 $a_i = \min\limits_{j = 1}^{i} a_j$，转移显然有：
$$
f_{i, j} = \sum\limits_{k = 1}^{i - 1} f_{k, j \oplus  1} \times a_i
$$
否则，设 $a_i$ 前面第一个比它小的位置为 $p$（可以单调栈求出）。我们按照 $k$ 与 $p$ 的关系分类讨论：

1. $k \in [1, p - 1]$，这部分 $f_{k, j \oplus  1} \times \min\limits_{l = k + 1}^{i} a_l$ 的贡献与 $a_{p + 1 \dots i}$ 无关，可以重新写成 $f_{k, j \oplus  1} \times \min\limits_{l = k + 1}^{p} a_l$。发现 $\sum\limits_{k = 1}^{p - 1} f_{k, j \oplus  1} \times \min\limits_{l = k + 1}^{p} a_l$ 的值就是 $f_{p, j}$，于是直接继承 DP 值即可。
2. $k \in [p, i - 1]$，这部分保证了 $\min\limits_{l = k + 1}^{i} a_l = a_i$，可以转化为 $f_{i, j} = \sum\limits_{k = p}^{i - 1} f_{k, j \oplus  1} \times a_i$。

综上有：
$$
f_{i, j} = f_{p, j} + \sum\limits_{k = p}^{i - 1} f_{k, j \oplus  1} \times a_i
$$
用前缀和优化即可做到 $O(1)$ 转移。

最后，若 $n$ 为偶数，$n - k$ 的奇偶性同 $k$ 的奇偶性，答案为 $f_{n, 0} - f_{n, 1}$。反之为 $f_{n, 1} - f_{n, 0}$。

时间复杂度为 $O(n)$。

**Code**

```cpp
#include <cstdio>
#include <stack>
typedef long long ll;
const int n_max = 2e5 + 5;
const ll mod = 998244353;
int a[n_max], n;
ll f[n_max][2], g[n_max][2];
std::stack<int> stk;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	f[0][0] = g[0][0] = 1ll;
	for (int i = 1; i <= n; ++i) {
		while (!stk.empty() && a[stk.top()] >= a[i])
			stk.pop();
		if (stk.empty()) {
			for (int j : {0, 1})
				f[i][j] = g[i - 1][j ^ 1] * a[i] % mod;
		} else {
			for (int j : {0, 1})
				f[i][j] = (f[stk.top()][j] + (g[i - 1][j ^ 1] - g[stk.top() - 1][j ^ 1]) * a[i] % mod) % mod;
		}
		for (int j : {0, 1})
			g[i][j] = (g[i - 1][j] + f[i][j]) % mod;
		stk.push(i);
	}
	int sgn = (n & 1) ? -1 : 1;
	printf("%lld\n", ((f[n][0] - f[n][1]) * sgn % mod + mod) % mod);
	return 0;
}
```

---

## 作者：jijidawang (赞：5)

三倍经验：[CF1591F](https://www.luogu.com.cn/problem/CF1591F)，[CF1585F](https://www.luogu.com.cn/problem/CF1585F)（这两道 CF 上是一样的），[ARC115E](https://atcoder.jp/contests/arc115/tasks/arc115_e)（数据范围加大）.

令满足 $b_i=b_{i+1}$ 的点 $i$ 为 U 点，则我们就是要算恰有 $0$ 个 U 点的方案 .

考虑容斥，令 $f(k)$ 为至少 $k$ 个 U 点的方案数，则答案为
$$ans=\sum_{k=0}^n(-1)^kf(k)$$

发现至少有 $k$ 个 U 点的一组满足条件的 $\{b\}$ 必然可以被分为 $n-k$ 个内部全部相等的连续段，因为是至少所以相邻的两段的数不一定要不同 .

令 $dp_{i,j}$ 为 $b_{1\dots i}$ 分为 $j$ 段的方案数，于是答案就是 $(-1)^n(dp_{n,n}-dp_{n,n-1})$ .

枚举 $i$ 所在的一段的左端点 $k$，可以得到转移
$$dp_{i,j}=\sum_{k=1}^jdp_{k-1,j-1}\min_{k\in[k,i]}\{a_k\}$$
因为 $dp_{\dots,j}$ 只和 $dp_{\dots,j-1}$ 有关，所以可以滚动数组，同时每次 min 的区间总不变小，所以单调栈维护一下即可 .

时空复杂度均为 $O(n)$ .

CF Submission: [168961015](https://codeforces.com/contest/1585/submission/168961015) .

---

## 作者：SkyRainWind (赞：3)

着重阐述一下容斥和由容斥转化为 dp 的部分。

考虑容斥：

设 $A_i$ 表示 $b_i \neq b_{i+1}$ ($i=1,2,\cdots,n-1$) 时对应的 $\{b_i\}$ 方案的答案。

那么答案就是 $\bigcap_{{i=1}}^{n}A_{i} = |U|-\left|\bigcup_{i=1}^n\overline{A_i}\right|$

后者可以用容斥原理化简。也就是这个式子：
$$\begin{aligned}\left|\bigcup _{i=1}^{n}A_{i}\right|={}\sum _{i=1}^{n}|A_{i}|-\sum _{1\leq i;j\leq n}|A_{i}\cap A_{j}|+\sum _{1\leq i;j;k\leq n}|A_{i}\cap A_{j}\cap A_{k}|-\cdots +(-1)^{n-1}\left|A_{1}\cap \cdots \cap A_{n}\right|.\end{aligned}$$

考虑这个过程的意义：$|\overline{A_i}|$ 的含义就是我钦定了 $b_i=b_{i+1}$，然后剩下的随便选（也就是没有限制了），$|\overline{A_i}\cup\overline{A_j}|$ 的含义就是钦定了 $b_i=b_{i+1}$ 且 $ b_j=b_{j+1}$，然后剩下的没有限制。

那这个贡献如何算呢？我们发现，如果有 $b_i=b_{i+1}=b_{i+2}$ 的话，那么这段的贡献就是三个数的 min，再和别的部分相乘。

可以将每一个相同的连续部分看成一“段”，如果已经钦定了 $k$ 个连续的部分，那相当于有 $n-k$ 个“段”，考虑对段的贡献进行 dp。

设 $dp_{i,j}$ 表示考虑到第 $i$ 个位置，当前划分了 $j$ 个段的贡献，那么显然 $dp_{i,j} \leftarrow dp_{k,j-1}\times \min(a_{k+1}..a_i)$

注意这里“段”的意义是我“钦定”的段。一个例子：我可以将 $1..5$ 划分为 $[1,3], [4,4], [5,5]$，段内的元素一定是相同的，这是我钦定的，但是段间的元素也可能相同，这是我钦定之后没有其它限制条件的结果。例如 $a_4=a_5$ 是合法的。

关于利用单调栈进一步优化 dp，[这篇博客](https://www.luogu.com.cn/blog/cx330qwq/solution-cf1585f) 已经讲的很完整了，此处从略。

---

## 作者：DengDuck (赞：2)

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

## 作者：CQ_Bob (赞：2)

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

## 作者：zztqwq (赞：2)

设 $f(i,j)$ 表示考虑前 $i$ 个数，当前 $b_i=j$ 的方案数，那么显然有：

$$
f(i,j)=\begin{cases}0, &j>a_i\\(\sum_{x=1}^{a_{i-1}}f(i-1,x))-f(i-1,j), &j\le a_i\end{cases}
$$

把 $f(i)$ 看作序列，用线段树维护即可。需要支持区间推平（$j>a_i$ 的情况），区间取反（$f(i,j)\gets -f(i-1,j)$），区间加（$f(i,j)\gets -f(i-1,j)+\sum_{x=1}^{a_{i-1}}f(i-1,x)$），区间查询（查询 $\sum_{x=1}^{a_{i-1}}f(i-1,x)$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
void write(int n)
{
	if(n<0){putchar('-');n=-n;}
	if(n>9)write(n/10);
	putchar(n%10^48);
}
const int N=2e5+10,mod=998244353;
int a[N],b[N];
void f(int &x){x=(x%mod+mod)%mod;}
struct sgt{
	struct seg{
		int l,r,sum;
		int cov,add,neg;
		//cover, add, negative
		seg(){l=r=sum=add=cov=neg=0;}
	}t[N<<2];
	//cov -> neg  -> add
	void build(int p,int l,int r)
	{
		t[p].l=l,t[p].r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(p*2,l,mid),build(p*2+1,mid+1,r);
	}
	void pd(int p)
	{
		if(t[p].cov)
		{
			t[p*2].cov=t[p*2+1].cov=t[p].cov,t[p].cov=0;
			t[p*2].neg=t[p*2+1].neg=0;
			t[p*2].add=t[p*2+1].add=0;
			t[p*2].sum=0;
			t[p*2+1].sum=0;
		}
		if(t[p].neg)
		{
			t[p*2].neg^=1,t[p*2+1].neg^=1;
			t[p*2].add*=-1,t[p*2+1].add*=-1;
			f(t[p*2].add),f(t[p*2+1].add);
			t[p*2].sum*=-1,t[p*2+1].sum*=-1;
			f(t[p*2].sum),f(t[p*2+1].sum);
			t[p].neg=0;
		}
		if(t[p].add)
		{
			t[p*2].add+=t[p].add,t[p*2].add%=mod;
			t[p*2].sum+=1ll*(b[t[p*2].r]-b[t[p*2].l-1])*t[p].add%mod,t[p*2].sum%=mod;
			t[p*2+1].add+=t[p].add,t[p*2+1].add%=mod;
			t[p*2+1].sum+=1ll*(b[t[p*2+1].r]-b[t[p*2+1].l-1])*t[p].add%mod,t[p*2+1].sum%=mod;
			t[p].add=0;
		}
	}
	void modify(int p,int l,int r,int d)//add
	{
		if(l>r)return;
		if(l<=t[p].l&&t[p].r<=r)
		{
			t[p].sum+=1ll*(b[t[p].r]-b[t[p].l-1])*d%mod,t[p].sum%=mod;
			t[p].add+=d,t[p].add%=mod;
			return;
		}
		pd(p);int mid=(t[p].l+t[p].r)>>1;
		if(l<=mid)modify(p*2,l,r,d);
		if(r>mid)modify(p*2+1,l,r,d);
		t[p].sum=t[p*2].sum+t[p*2+1].sum;
		t[p].sum%=mod;
	}
	void cover(int p,int l,int r)
	{
		if(l>r)return;
		if(l<=t[p].l&&t[p].r<=r)
		{
			t[p].cov=1;
			t[p].add=t[p].sum=t[p].neg=0;
			return;
		}
		pd(p);int mid=(t[p].l+t[p].r)>>1;
		if(l<=mid)cover(p*2,l,r);
		if(r>mid)cover(p*2+1,l,r);
		t[p].sum=t[p*2].sum+t[p*2+1].sum;
		t[p].sum%=mod;
	}
	void modify1(int p,int l,int r)
	{
		if(l>r)return;
		if(l<=t[p].l&&t[p].r<=r)
		{
			t[p].neg^=1;
			t[p].sum*=-1,t[p].add*=-1;
			f(t[p].sum);
			f(t[p].add);
			return;
		}
		pd(p);int mid=(t[p].l+t[p].r)>>1;
		if(l<=mid)modify1(p*2,l,r);
		if(r>mid)modify1(p*2+1,l,r);
		t[p].sum=t[p*2].sum+t[p*2+1].sum;
		t[p].sum%=mod; 
	}
	int query(int p,int l,int r)
	{
		if(l>r)return 0;
		if(l<=t[p].l&&t[p].r<=r)return t[p].sum;
		pd(p);int mid=(t[p].l+t[p].r)>>1,ans=0;
		if(l<=mid)ans+=query(p*2,l,r),ans%=mod;
		if(r>mid)ans+=query(p*2+1,l,r),ans%=mod;
		return ans;
	}
}T;
int main()
{
	int n=read(),c=n;
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+c+1),c=unique(b+1,b+c+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+c+1,a[i])-b;
//	for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("!!!"); 
	T.build(1,1,c);
	for(int i=1;i<=a[1];i++)T.modify(1,i,i,1);
	for(int i=2;i<=n;i++)
	{
		int sum=T.query(1,1,c);
//		printf("sum=%d\n",sum);
		T.cover(1,a[i]+1,c);
//		printf("sum=%d\n",T.query(1,1,c));
		T.modify1(1,1,a[i]);
//		printf("sum=%d\n",T.query(1,1,c));
		T.modify(1,1,a[i],sum);
//		printf("sum=%d\n",T.query(1,1,c));
	}
	int ans=0;
	for(int i=1;i<=a[n];i++)ans+=T.query(1,i,i),ans%=mod;
	printf("%d\n",ans);
	return 0;
}
//zzt qwq
```

---

## 作者：TernaryTree (赞：1)

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

## 作者：樱雪喵 (赞：1)

CF1585F & 1591F，两个一样的题但一边题解全是线段树，另外一边全是容斥，好离谱。

直接 dp 是 $O(nV)$ 的，考虑容斥。钦定有 $i$ 对相邻数相同，发现这个东西要考虑好几对数连成一段的情况，还是不好求。  
但上面的问题给我们一个启发，有 $i$ 对数相同等价于把序列拆成不多于 $n-i$ 段。  
那设 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段，有朴素 dp：
$$
f_{i,j}=\sum_{k=0}^{i-1} f_{k,j-1}\times \min\{a_{k+1},\dots,a_i\}
$$
最后统计答案就是
$$ans=\sum_{j=1}^n (-1)^{j+n} f_{n,j}$$

状态还要优化，发现我们只关心 $j$ 的奇偶性而不关心具体是什么。设 $f_{i,j}$ 表示前 $i$ 个，钦定分成奇数还是偶数段的方案数。方程改成
$$
f_{i,j}=\sum_{k=0}^{i-1} f_{k,j\oplus 1}\times \min\{a_{k+1},\dots,a_i\}
$$

再优化转移复杂度，考虑后面 $\min$ 的值。设第一个比 $a_i$ 小的位置在 $lst_i$。那么小于 $lst_i$ 的 $k$ 可以直接从 $f_{lst_i,j}$ 转移过来。  
求 $lst$ 用单调栈。那么式子是
$$f_{i,j}=f_{lst_i,j}+\sum_{k=lst_i}^{i-1} f_{k,j\oplus 1}\times a_i$$
把 $a_i$ 拆出去，$\sum f_{k,j\oplus 1}$ 用前缀和优化，时间复杂度 $O(n)$。

```cpp
#define int long long
const int N=2e5+5,mod=998244353;
int n,a[N];
int f[N][2],sum[N][2],lst[N];
stack<int> q;
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++)
    {
        while(!q.empty()&&a[q.top()]>=a[i]) q.pop();
        lst[i]=q.empty()?0:q.top(); q.push(i);
    }
    f[0][0]=sum[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=1;j++)
        {
            f[i][j]=(lst[i]?f[lst[i]][j]:0)+a[i]*(sum[i-1][j^1]-(lst[i]?sum[lst[i]-1][j^1]:0))%mod;
            f[i][j]=(f[i][j]%mod+mod)%mod;
            sum[i][j]=(f[i][j]+sum[i-1][j])%mod;
        }
    if(n&1) printf("%lld\n",(f[n][1]-f[n][0]+mod)%mod);
    else printf("%lld\n",(f[n][0]-f[n][1]+mod)%mod);
    return 0;
}
```

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

## 作者：Fireworks_Rise (赞：0)

# 闲话

- 迟来的祝福：冬至快乐啊(*^▽^*)

- 神仙容斥 DP 题

# 思路

比较难想啊，本人也不想去赘述了，入题。

一眼考虑容斥好吧，回顾一下常见容斥：

以本题举例，钦定在序列 $b$ 中有 $i$ 个 $j$ 满足 $b_j \not = b_{j+1}$，其方案数可记为 $a_i$。

假设有序列的长度为 $3$。

- 直接算合法方案（奇加偶减）：

$|a_1 \cup a_2 \cup a_3|=|a_1|+|a_2|+|a_3|-|a_1 \cap a_2|-|a_1 \cap a_3|-|a_2 \cap a_3|+|a_1 \cap a_2 \cap a_3|$

- 正难反则易，考虑补集（奇减偶加）：

这里我们设 $\neg a_i$ 为 $a_i$ 的补集。

$| \neg a_1 \cup \neg a_2 \cup \neg a_3|=|S|-|a_1 \cap a_2 \cap a_3|=|S|-|a_1|-|a_2|-|a_3|+|a_1 \cap a_2|+|a_1 \cap a_3|+|a_2 \cap a_3|-|a_1 \cap a_2 \cap a_3|$
    

---

简单分析一波，明显用第二种容斥更优秀。

那么 $\neg a_i$ 所表示的就是在序列 $b$ 中有 $i$ 个 $j$ 满足 $b_j = b_{j+1}$，最后答案的方案数就为 $Ans = \sum_{i=0}^{n-1}(-1)^i \times a_i$，换个角度看其实就是把序列 $b$ 进行了离散化后，剩下 $n - i$ 个数了。

这就是一种最朴素的 $O(n^3)$ 做法（别看了，肯定超时了）。

回去看到题目的数据大小，发现 $n$ 的取值范围异常大，直接暴力容斥肯定是行不通的。

对所剩下的数进行优化，可以设 $f_{i,j}$ 表示前 $i$ 个位置中，把序列 $b$ 划分成 $j$ 段的方案数，此处保证每段中所有数相同，且任意两个段的值并不一定不相同。

则利用一点推柿子的能力，可以推导出状态转移方程为：

$f_{i,j} = \sum_{k=1}^{i-1}f_{k,j-1} \times \min_{p=k+1}^{i}b_p$

可是这样时间复杂度照样是爆炸，那么对式子进行化简，容易发现 $\sum_{k=1}^{i-1}f_{k,j-1}$ 可以利用前缀和 $sum_{i,j}$，用时 $O(n)$ 维护而得来，$O(1)$ 便可以转移。

难就难在 $\min_{p=k+1}^{i}b_p$，简单观察，进行分类讨论：

- 1.若 $b_i=\min_{j=1}^{i}b_j$，那当前转态显然是直接由 $\sum_{k=1}^{i-1}f_{k,j-1} \times b_i$ 所得来；

- 2.否则，先设 $b_i$ 前第一个比它小的位置为 $lst_i$，若 $k < lst_i$，可以直接由 $f_{lst_i,j}$ 转移过来。

这一段数区间的最小值不变，其实可以用个线性的单调栈维护即可。


---

好的，现在是平方级的时间，可是还不能仅限于此，何况数据有 $2 \times 10^5$ 这么大，转移式子并不能再优化了，那只能从转态数上压缩了。

明显的，$f_{i,j}$ 中的 $j$ 放回容斥原理中其实就是第 $j$ 层的意思，其仅用于奇减偶加 ~~（奇加偶减）~~，那么意味着不用去关心准确值，只用考虑其的奇偶性即可，因此可以使用滚动数组滚调 $j$ 这一维。

整理上述优化，可得 $f_{i,j(0/1)}=f_{lst_i,j}+(sum_{i-1,j\oplus 1}-sum_{lst_{i-1},j\oplus 1})\times b_i$，

其中的 $sum_{i,j}=sum_{i-1,j}+f_{i,j}$。

由于定义是序列中满足 $b_j=b_{j+1}$ 的个数为 $i$ 的方案数，所以最后输出的是至少有 $n$ 个的方案数减去至少有 $n-1$ 个的方案数，就是恰好为 $0$ 个 $b_j \not = b_{j+1}$ 的方案数，即 $f_{n,n\& 1}-f_{n,n \& 1 \oplus 1}$。

注意运算时还需取模。

# Code

奉上蒟蒻的代码...

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=2e5+10;
int n,a[N],f[N][2],sum[N][2];
int stk[N],top,lst[N]; 
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	f[0][0]=sum[0][0]=1;
	for(int i=1;i<=n;i++) {
		while(top&&a[stk[top]]>=a[i])
			--top;
		if(top) lst[i]=stk[top];
		stk[++top]=i;
		for(int j=0;j<=1;j++) {
			if(lst[i]) f[i][j]=(f[lst[i]][j]+a[i]*((sum[i-1][j^1]-sum[lst[i]-1][j^1]+mod)%mod)%mod)%mod;
			else f[i][j]=a[i]*sum[i-1][j^1]%mod;
            sum[i][j]=(f[i][j]+sum[i-1][j])%mod;
		}
	}
    if(n&1) printf("%lld\n",(f[n][1]-f[n][0]+mod)%mod);
    else printf("%lld\n",(f[n][0]-f[n][1]+mod)%mod);
	return 0;
}
```


---

## 作者：xiezheyuan (赞：0)

[双倍快乐](https://www.luogu.com.cn/problem/CF1591F)

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
const int N = 2e5+5;
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

