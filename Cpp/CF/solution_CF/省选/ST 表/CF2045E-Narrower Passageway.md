# Narrower Passageway

## 题目描述

你是 ICPC 王国的一名战略家，近日你收到情报，王国附近的一条狭窄通道将遭遇怪物的袭击。这条通道可以简化为一个 2 行 $N$ 列的网格。我们用 $(r, c)$ 表示网格中第 $r$ 行第 $c$ 列的格子。每天会安排一个力量值为 $P_{r, c}$ 的士兵驻守在 $(r, c)$ 位置上。

这里常年大雾，每列都有 $50\%$ 的概率被雾气笼罩。一旦某列被雾气覆盖，两个驻守该列的士兵将无法执行任务。否则，士兵将正常部署。

我们定义一个连通区域 $[u, v]$（$u \leq v$）为从第 $u$ 列到第 $v$ 列连续且无雾的列。下面的示例中，灰色部分代表被雾覆盖的格子，共有四个连通区域：$[1, 2]$、$[4, 6]$、$[9, 9]$ 和 $[11, 11]$。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/47744495c3a12fb362399d4924e5c674c3e83888.png)

连通区域 $[u, v]$ 的力量可以这样计算。设 $m_1$ 和 $m_2$ 分别为该区域内第一行和第二行士兵力量的最大值。具体来说，对于 $r \in \{1, 2\}$，有 $m_r = \max (P_{r, u}, P_{r, u + 1}, \dots, P_{r, v})$。如果 $m_1 = m_2$，则该区域的力量是 $0$；否则，力量为 $\min (m_1, m_2)$。

一个工作日的总力量定义为所有连通区域力量的总和。请计算在任意一天部署的期望总力量。

## 说明/提示

样例输入/输出 #1 解释

这条通道可能有 $8$ 种不同的布局。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/70a3bbc18f3f05a2f49fd32453ba66ee47116d57.png)

每种布局出现的概率是相同的。因此，期望总力量为 $(0 + 5 + 10 + 5 + 5 + 0 + 5 + 0) / 8 = \frac{15}{4}$。由于 $249\,561\,092 \cdot 4 \equiv 15 \pmod{998\,244\,353}$，所以样例的输出为 $249\,561\,092$。

样例输入/输出 #2 解释

期望总力量为 $\frac{67}{16}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
8 4 5
5 4 8```

### 输出

```
249561092```

## 样例 #2

### 输入

```
5
10 20 5 8 5
5 20 7 5 8```

### 输出

```
811073541```

# 题解

## 作者：Luzhuoyuan (赞：7)

一个简单一点的做法。

首先容易发现求的就是所有方案的总权值除以方案数 $2^n$。

我们发现一个区间权值的计算方式是：若两行分别的最大值相等则为 $0$，否则为较小者。这个东西看上去就比较抽象，应该需要一些巧妙的转化。

设两行分别为序列 $a,b$，某区间在两行的最大值分别为 $m_1,m_2$，考虑把该区间权值转化为：

$$m_1+m_2-[m_1=\max(m_1,m_2)]\cdot m_1-[m_2=\max(m_1,m_2)]\cdot m_2$$

考虑统计每个数对答案的贡献。

先思考 $m_1$ 的贡献怎么算。对于第一行的每个元素，可以用单调栈求出极大的包含 $i$ 位置的区间 $[L_i,R_i]$，使得：

- $\forall j\in[L_i,i),a_j\le a_i$
- $\forall j\in(i,R_i],a_j<a_i$

上下符号不同是为了防止算重。然后它的贡献就是 $a_i$ 乘以 存在一个区间的左端点在 $[L_i,i]$、右端点在 $[i,R_i]$ 的方案数。

考虑这个方案数如何计算。要想构成一个极长的无雾区间 $[l,r]$，“是否有雾的状态”确定的位置是 $[l-1,r+1]$（$l-1,r+1$ 必须有雾，$[l,r]$ 必须没有，忽略 $l=1$ 或 $r=n$ 的情况），不确定的位置有 $2^{l-2}\cdot 2^{n-r-1}$ 种方案。那么总共的状态数就是

$$\sum\limits_{l=L_i}^i\sum\limits_{r=i}^{R_i}2^{l-2}\cdot 2^{n-r-1}=(\sum\limits_{l=L_i}^i 2^{l-2})(\sum\limits_{r=i}^{R_i}2^{n-r-1})=(2^{i-1}-2^{L_i-2})(2^{n-i}-2^{n-R_i-1})$$

这样就容易计算了。至于 $l=1$ 或 $r=n$，只要假装 $2^{-1}=0$ 就可以了。

于是 $m_1$ 的贡献就算完了，$m_2$ 同理。

考虑式子的后面两项，我们也可以用单调栈求出极长的区间 $[L_i,R_i]$，使得：

- $\forall j\in[L_i,i),a_j\le a_i$
- $\forall j\in(i,R_i],a_j<a_i$
- $\forall j\in[L_i,R_i],b_j\le a_i$

然后和上面一样计算即可。

代码还是比较好写的。注意一些细节的处理，具体见代码。

预处理二的幂次即可做到 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=1e5+5,mod=998244353,i2=(mod+1)/2;
int n,a[N],b[N],st[N],t,L[N],R[N],mi[N],ans;
inline int Mi(int x){return x<0?0:mi[x];}
inline int cal(int l,int m,int r){
	if(l>m||m>r)return 0;
	return (Mi(m-1)+mod-Mi(l-2))*(Mi(n-m)+mod-Mi(n-r-1))%mod;
}
inline void wrk1(){
	for(int i=n;i;i--){
		while(t&&a[i]>a[st[t]])L[st[t--]]=i+1;
		st[++t]=i;
	}
	while(t)L[st[t--]]=1;
	// 注意上下弹栈符号区别。
	for(int i=1;i<=n;i++){
		while(t&&a[i]>=a[st[t]])R[st[t--]]=i-1;
		st[++t]=i;
	}
	while(t)R[st[t--]]=n;
	for(int i=1;i<=n;i++)ans=(ans+cal(L[i],i,R[i])*a[i])%mod;
}
inline void wrk2(){
	for(int i=n;i;i--){
		while(t&&(b[i]>a[st[t]]||a[i]>a[st[t]]))L[st[t--]]=i+1;
		if(a[i]>=b[i])st[++t]=i;else L[i]=i+1;
	}
	while(t)L[st[t--]]=1;
	// 注意上下弹栈符号区别。
	for(int i=1;i<=n;i++){
		while(t&&(b[i]>a[st[t]]||a[i]>=a[st[t]]))R[st[t--]]=i-1;
		if(a[i]>=b[i])st[++t]=i;else R[i]=i-1;
	}
	while(t)R[st[t--]]=n;
	for(int i=1;i<=n;i++)ans=(ans+mod-cal(L[i],i,R[i])*a[i]%mod)%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	mi[0]=1;for(int i=1;i<=n;i++)mi[i]=(mi[i-1]*2)%mod;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	wrk1(),wrk2();
	swap(a,b);
	wrk1(),wrk2();
	for(int i=1;i<=n;i++)ans=ans*i2%mod;
	cout<<ans<<'\n';
	return 0;
}
```

（逃

---

## 作者：xyz105 (赞：4)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.017 }\bold{CF2045E}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


### 题目描述

给定一张 $2\times N$ 的网格，其中所有单元格都有其权值，记第 $r$ 行第 $c$ 列的单元格的权值为 $P_{r,c}\ (r\isin [1,2], c\isin [1,N])$。

已知该网格中的每一列都有 $50\%$ 的概率不可用。定义一个 **连通区域** $[u,v]\ (u\le v)$ 满足第 $u\sim v$ 列都是可用的，并且第 $u-1$ 列和第 $v+1$ 列恰好都不可用。

下图是可能的一个例子，阴影区域不可用，其它白色区域可用。共有 $4$ 个连通区域：$[1,2],[4,6],[9,9],[11,11]$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045E/47744495c3a12fb362399d4924e5c674c3e83888.png)

一个连通区域 $[u,v]$ 的 **强度** 计算方式如下：令 $m_1=\max\limits_{u\le i\le v} P_{1,i},\ \ m_2=\max\limits_{u\le i\le v} P_{2,i}$，若 $m_1=m_2$ 则强度为 $0$，否则为 $\min(m_1,m_2)$。

定义整个网格图的 **总强度** 为其所有连通区域的强度之和。试求出 总强度 的期望值。


### 解题思路

这里是 $O(N\log N)$ 的做法。

容易发现枚举 $[u,v]$ 很难做。不妨考虑 **拆贡献**，即只去计算每个数字各产生的贡献。

如果 $P_{r,c}$ 被某个连通区域 $[u,v]$ 包含，且该连通区域 $[u,v]$ 的强度恰好为 $P_{r,c}$，那么就称 $[u,v]$ 对 $P_{r,c}$ 做了 $2^{\max(u-2,0)+\max(n-v-1,0)}$ 次贡献。为啥是这个公式呢？因为第 $u-1$ 列和第 $v+1$ 列必然是不可用的，并且**前 $u-2$ 列**和**后 $n-v-1$ 列**随便你可用不可用。

记 $cnt_{r,c}$ 为所有可能的 $[u,v]$ 对 $P_{r,c}$ 做贡献的总次数，那么答案就是 $\dfrac{\sum_r\sum_c cnt_{r,c}\times P_{r,c}}{2^n}$。

现在问题转化为如何计算 $cnt_{r,c}$。进一步简化问题，先只考虑如何计算 $cnt_{2,c}$，因为 $cnt_{1,c}$ 的计算方式同理。

考虑一个问题：连通区域 $[u,v]$ 要想能对 $P_{2,c}$ 做贡献，那么 $[u,v]$ 要满足什么条件？
- $u\le c\le v$。
- $m_1\neq m_2,m_2=\min(m_1,m_2)$ 且 $m_2=P_{2,c}$。  
  也就是说 $P_{2,c}=\Big(\max\limits_{u\le i\le v}P_{2,i}\Big)<\Big(\max\limits_{u\le i\le v}P_{1,i}\Big)$。

因此，考虑求出四个值 $l_1,l_2,r_1,r_2$，其中：
- $l_2$ 为满足 $\Big(\max\limits_{l_2\le i\le c} P_{2,i}\Big)\le P_{2,c}$ 的最小的数，$r_2$ 为满足 $\Big(\max\limits_{c\le i\le r_2} P_{2,i}\Big)\le P_{2,c}$ 的最大的数。  
  若 $[u,v]\subseteq [l_2,r_2]$，则 $m_2=P_{2,c}$ 得到满足。  
  （注：这些定义待会可能会做微调，不过先不用管）
- $l_1$ 为满足 $\Big(\max\limits_{l_1\le i\le c} P_{1,i}\Big)>P_{2,c}$ 的最大的数，$r_1$ 为满足 $\Big(\max\limits_{c\le i\le r_1} P_{1,i}\Big)>P_{2,c}$ 的最小的数。  
  若 $u\le l_1$ 或 $r_1\le v$，则 $m_1>P_{2,c}$ 得到满足。

到这里可以发现，如果 $[u,v]$ 满足 $u\isin [l_2,l_1]\land v\isin [c,r_2]$ 或者 $u\isin [l_2,c]\land v\isin [r_1,r_2]$，那么 $[u,v]$ 就做了贡献。

为了不算重 $[u,v]$，考虑如下处理：
- 如果 $l_2\le l_1 \land r_1\le r_2$，那么将下列两类算进去：
  1. $u\isin [l_2,l_1]\land v\isin [c,r_1)$（一定只满足 $u\le l_1$）；
  2. $u\isin [l_2,c]\land v\isin [r_1,r_2]$（一定满足 $r_1\le v$，可能满足 $u\le l_1$）。
- 如果只有 $l_2\le l_1$，那么将 $u\isin [l_2,l_1]\land v\isin [c,r_2]$ 算进去。
- 如果只有 $r_1\le r_2$，那么将 $u\isin [l_2,c]\land v\isin [r_1,r_2]$ 算进去。

约定 $2^{-x}=1 (x>0),\ 2^{l\ \sim\  r}=2^l+2^{l+1}+\cdots+2^r$。计算形如 $u\isin [a,b]\land v\isin [c,d]$ 的式子就相当于 $cnt_{r,c}\gets cnt_{r,c}+(2^{a-2\ \sim\ b-2})\times(2^{n-d-1\ \sim\ n-c-1})$。

预处理后 $2^{l\sim r}$ 可以 $O(1)$ 计算；对于所有 $c$，对应的 $l_2,r_2$ 可用单调栈预处理，对所有 $P_{1,i}$ 建 ST 表后 $l_1,r_1$ 可在 $O(\log N)$ 时间内二分找到。故总时间复杂度为 $O(N\log N)$。

---

**Update** on 2024-12-19。

打个小补丁，有东西忘讲了：这个时候 连通区域 $[u,v]$ 仍然会被算重。

我们实际上认定 连通区域 $[u,v]$ 只能对**一个位置** $(2,c)$ 做贡献。但存在一种可能性，就是 $[u,v]$ 同时对多个数字 $P_{2,c_1},P_{2,c_2},\ldots,P_{2,c_i}\ (P_{2,c_1}=P_{2,c_2}=\cdots=P_{2,c_i})$ 做了贡献，这就是 $[u,v]$ 被算重的地方。

于是规定，如果多个数字同时满足条件，那么 $[u,v]$ 的贡献**只算在** $P_{2,c_i}$ 头上。只需修改 $r_2$ 的定义即可：
- $r_2$ 为满足 $\Big(\max\limits_{c+1\le i\le r_2} P_{2,i}\Big)< P_{2,c}$ 的最大的数。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/2045/submission/297094970)。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353, INF = 0x3f3f3f3f3f3f3f3fll;

inline ll pow_(ll a, ll b, ll p)
{
	ll res = 1;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) res = res * a % p;
	return res;
}
inline ll inv(ll x) {return pow_(x, MOD - 2, MOD);}

const int MAXN = 1e5 + 10;

ll a[MAXN], b[MAXN]; int n;
ll lg2[MAXN], pow2[MAXN], pow2s[MAXN], ans = 0;

inline ll mod2(ll x) {return x >= MOD ? x - MOD : x;}

inline ll pow2s_(int l, int r)
	{if (l > r) return 0;
	if (r <= 0) return r - l + 1;
	if (l <= 0) return mod2(1 - l + pow2s_(1, r));
	return mod2(pow2s[r] - pow2s[l - 1] + MOD);}

int lst[MAXN], nxt[MAXN], sta[MAXN], sta_cnt = 0;

ll st[MAXN][19];

inline void st_build()
{
	for (int i = 1; i <= n; i++) st[i][0] = a[i];
	for (int j = 1; j < 19; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
inline ll st_query(int l, int r)
	{int i1 = lg2[r - l + 1]; return max(st[l][i1], st[r - (1 << i1) + 1][i1]);}

inline void calc()
{
	b[0] = b[n + 1] = INF;
	
	sta[sta_cnt = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		while (sta_cnt && b[sta[sta_cnt]] <= b[i]) sta_cnt--;
		lst[i] = sta[sta_cnt], sta[++sta_cnt] = i;
	}
	
	sta[sta_cnt = 1] = n + 1;
	for (int i = n; i; i--)
	{
		while (sta_cnt && b[sta[sta_cnt]] < b[i]) sta_cnt--;
		nxt[i] = sta[sta_cnt], sta[++sta_cnt] = i;
	}
	
	st_build();
	for (int i = 1; i <= n; i++)
	{
		int l = 1, r = i, mid, res1 = 0;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			if (st_query(mid, i) > b[i]) res1 = mid, l = mid + 1;
			else r = mid - 1;
		}
		
		int res2 = n + 1; l = i, r = n;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			if (st_query(i, mid) > b[i]) res2 = mid, r = mid - 1;
			else l = mid + 1;
		}
		
		if (lst[i] + 1 > res1 && res2 > nxt[i] - 1) continue;
		int j1 = lst[i] + 1, j2 = res1, j3 = res2, j4 = nxt[i] - 1;
		ll res = 0;
		if (res2 <= nxt[i] - 1 && lst[i] + 1 <= res1)
			ans = (ans + pow2s_(j1 - 2, j2 - 2) * pow2s_(n - (j3 - 1) - 1, n - i - 1) % MOD * b[i]) % MOD,
			ans = (ans + pow2s_(j1 - 2, i - 2) * pow2s_(n - j4 - 1, n - j3 - 1) % MOD * b[i]) % MOD;
		else if (res2 <= nxt[i] - 1)
			ans = (ans + pow2s_(j1 - 2, i - 2) * pow2s_(n - j4 - 1, n - j3 - 1) % MOD * b[i]) % MOD;
		else if (lst[i] + 1 <= res1)
			ans = (ans + pow2s_(j1 - 2, j2 - 2) * pow2s_(n - j4 - 1, n - i - 1) % MOD * b[i]) % MOD;
	}
}

int main()
{
	for (int i = 2; i < MAXN; i++) lg2[i] = lg2[i >> 1] + 1;
	pow2[0] = pow2s[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pow2[i] = pow2[i - 1] * 2 % MOD, pow2s[i] = (pow2s[i - 1] + pow2[i]) % MOD;
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= n; i++) scanf("%lld", b + i);
	
	calc();
	for (int i = 1; i <= n; i++) swap(a[i], b[i]);
	calc();
	
	cout << ans * inv(pow2[n]) % MOD;
	
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

答辩题。

## 思路

考虑将 $[l,r]$ 是一个段的方案数乘以 $[l,r]$ 的权值然后加起来，最后除以 $2^n$ 就是答案。

我们先不考虑 $m_1=m_2$ 权值是 $0$ 的条件，考虑对于一个 $val$ 求出权值 $\ge val$ 的方案数，然后把这些方案数加起来就是原来的答案。

在值域上扫描，对于当前的 $val$ 拿总方案数减去 $m_1<val$ 或 $m_2<val$ 的方案数，然后继续容斥，把 $m_1<val$ 或 $m_2<val$ 的方案数容斥成：$m_1<val$ 的方案数，$m_2<val$ 的方案数，$m_1<val$ 且 $m_2<val$ 的方案数。

对于这个问题，容易转化成在一个全 $1$ 序列上每次将一个点改成 $0$，计算 $\sum 2^{\max(0,l-2)} \times 2^{\max(0,n-r-1)}$，其中 $l,r$ 要满足 $[l,r]$ 内没有 $1$。

容易使用并查集维护，每次合并两个连通块先将它们的贡献减掉然后把合并之后的贡献加上。

然后考虑 $m_1=m_2$ 的方案，枚举 $m_1=m_2=val$，随后同样使用并查集维护极长的满足所有数都 $\le val$ 的连续段，对于每个 $=val$ 的位置 $p$ 取出它所在的连续段，对于取出的连续段单独计算一下贡献即可。

最后还需要快速计算 $\sum_{l=i}^j \sum_{r=l}^j 2^{\max(0,l-2)} \times 2^{\max(0,n-r-1)}$，考虑差分成 $\sum_{l=i}^j \sum_{r=l}^n 2^{\max(0,l-2)} \times 2^{\max(0,n-r-1)}-\sum_{l=i}^j \sum_{r=j+1}^n 2^{\max(0,l-2)} \times 2^{\max(0,n-r-1)}$ 然后就能直接算了。

时间复杂度线性。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
#define add(x,y) (x=((x+y>=mod)?(x+y-mod):(x+y)))
int const N=2e5+10,mod=998244353;
int n,a[2][N],hz[N],sm0[N],sm1[N],X,val,ans,pw[N],fa[N],mx[N],lf[N],rg[N];
vector<int>vc[N],v1[N],v2[N],v3[N];
inline int qpow(int a,int b){int res=1;while (b){if (b&1) res*=a,res%=mod;a*=a,a%=mod,b>>=1;}return res;}
inline int find(int x){return (x==fa[x])?(x):(fa[x]=find(fa[x]));}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if (x==y) return;
	fa[x]=y,lf[y]=min(lf[y],lf[x]),rg[y]=max(rg[y],rg[x]);
}
inline int sqr(int l,int r){
	if (l>r) return 0;
	int res=(hz[l]+mod-hz[r+1])%mod;
	add(res,mod-(sm0[r]+mod-sm0[l-1])*sm1[r+1]%mod);
	return res;
}
inline int calc(int id,vector<int>V){
	if (!V.size()) return 0;
	int L=lf[id],R=rg[id],ans=sqr(L,R);
	vector<int>v1,v2;
	v1.push_back(L-1),v2.push_back(L-1);
	int las=L-1;
	for (auto i:V){
		if (a[0][i]==X)
			add(ans,sqr(las+1,i-1)),las=i,v1.push_back(i);
		if (a[1][i]==X)
			add(ans,sqr(las+1,i-1)),las=i,v2.push_back(i);
	}
	add(ans,sqr(las+1,R));
	v1.push_back(R+1),v2.push_back(R+1);
	int sz1=v1.size(),sz2=v2.size();
	rep(i,1,sz1-1) add(ans,mod-sqr(v1[i-1]+1,v1[i]-1));
	rep(i,1,sz2-1) add(ans,mod-sqr(v2[i-1]+1,v2[i]-1));
	return ans*X%mod;
}
struct Data_Structure{
	int sm,fa[N],lf[N],rg[N];bool co[N];
	inline void init(){
		sm=0;
		rep(i,1,n) fa[i]=lf[i]=rg[i]=i,co[i]=0;
	}
	inline int find(int x){return (x==fa[x])?(x):(fa[x]=find(fa[x]));}
	inline void merge(int x,int y){
		x=find(x),y=find(y);
		if (x==y) return;
		add(sm,mod-sqr(lf[x],rg[x]));
		add(sm,mod-sqr(lf[y],rg[y]));
		fa[x]=y;
		lf[y]=min(lf[y],lf[x]),rg[y]=max(rg[y],rg[x]);
		add(sm,sqr(lf[y],rg[y]));
	}
	inline void insert(int id){
		add(sm,sqr(id,id)),co[id]=1;
		if (id>1 && co[id-1]) merge(id,id-1);
		if (id<n && co[id+1]) merge(id,id+1);
	}
}T1,T2,T3;
inline void solve(){
	cin>>n;
	rep(i,1,n) fa[i]=lf[i]=rg[i]=i;
	rep(i,1,n) cin>>a[0][i],val=max(val,a[0][i]);
	rep(i,1,n) cin>>a[1][i],val=max(val,a[1][i]),vc[max(a[0][i],a[1][i])].push_back(i);
	int gg=0;
	per(i,n,1){
		add(gg,pw[max(0ll,n-i-1)]),sm1[i]=gg;
		hz[i]=(hz[i+1]+gg*pw[max(0ll,i-2)])%mod;
	}
	rep(i,1,n) sm0[i]=(sm0[i-1]+pw[max(0ll,i-2)])%mod;
	for (X=1;X<=val;++X){
		for (auto id:vc[X]){
			if (id!=1 && max(a[0][id-1],a[1][id-1])<=X) merge(id,id-1);
			if (id!=n && max(a[0][id+1],a[1][id+1])<=X) merge(id,id+1);
		}
		vector<int>V;
		int las=-1;
		for (auto id:vc[X])
			if (find(id)!=las){
				ans+=mod-calc(las,V),ans%=mod;
				las=find(id),V.clear(),V.push_back(id);
			}else V.push_back(id);
		ans+=mod-calc(las,V),ans%=mod;
	}//减去 m1=m2 的方案
	T1.init(),T2.init(),T3.init();
	rep(i,1,n) v1[a[0][i]].push_back(i),v2[a[1][i]].push_back(i),v3[min(a[0][i],a[1][i])].push_back(i);
	for (X=1;X<=val;++X){
		int res=sqr(1,n);
		res+=T3.sm,res+=mod-T1.sm,res+=mod-T2.sm,res%=mod;
		add(ans,res);
		for (auto id:v1[X]) T1.insert(id);
		for (auto id:v2[X]) T2.insert(id);
		for (auto id:vc[X]) T3.insert(id);
	}//统计不考虑 m1=m2 的方案数
	cout<<ans*qpow((mod+1)/2,n)%mod<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	pw[0]=1;
	rep(i,1,N-1) pw[i]=pw[i-1]*2%mod;
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：spdarkle (赞：0)

来个直接的做法。

拆开期望，则答案就是所有 $[l,r]$ 的答案乘上 $\frac{2^{l-1-[l\neq 1]+n-r-[r\neq n]}}{2^n}$。

可以看到 $l,r$ 的贡献系数是独立的。

注意到 $\min(m_1,m_2)=m_1+m_2-\max(m_1,m_2)$。

我们考虑先不考虑 $m_1=m_2$ 时贡献为零的情况，后面再容斥。

则这个问题相当于是对三个序列：第一行，第二行，以及两行元素取 $\max$ 的一行做计算。

由于 $l,r$ 贡献系数独立，可以使用单调栈和区间加减线段树计算。

事实上，这里直接利用前缀和线性计算也是可以的，毕竟我们只关心全局和。

然后考虑容斥掉 $m_1=m_2$ 的情况。

设序列 $a$ 是两行元素取 $\max$ 的结果，考虑对 $a$ 建立笛卡尔树。

则我们在考虑笛卡尔树点 $x$ 的贡献时，先找到 $a_x$ 是哪一行贡献的，然后找另一行与 $a_x$ 相同的值出现在笛卡尔树两侧的最近位置。

那么可以得到一个合法区间的范围，稍加讨论即可计算。

[submission](https://codeforces.com/contest/2045/submission/300486697)

---

