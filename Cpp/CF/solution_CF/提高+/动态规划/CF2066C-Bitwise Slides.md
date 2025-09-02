# Bitwise Slides

## 题目描述

给定一个数组 $a_1, a_2, \ldots, a_n$，以及三个初始值为零的变量 $P, Q, R$。

你需要按从 $1$ 到 $n$ 的顺序依次处理所有数字 $a_1, a_2, \ldots, a_n$。当处理当前元素 $a_i$ 时，你必须从以下三个操作中任选一个执行：
1. $P := P \oplus a_i$
2. $Q := Q \oplus a_i$
3. $R := R \oplus a_i$

其中 $\oplus$ 表示按位异或操作。

执行操作时必须遵守核心规则：每次操作后，三个数 $P, Q, R$ 必须满足两两不互异。

所有 $n$ 个操作共有 $3^n$ 种可能的执行方式。求其中不违反核心规则的方式数量。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 说明/提示

第一个测试用例中，存在 3 种合法操作序列：PPP、QQQ、RRR。

第二个测试用例中，存在 9 种合法操作序列：PPPP、PPPQ、PPPR、QQQP、QQQQ、QQQR、RRRP、RRRQ、RRRR。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
1 7 9
4
179 1 1 179
5
1 2 3 3 2
12
8 2 5 3 9 1 8 12 9 9 9 4
1
1000000000```

### 输出

```
3
9
39
123
3```

# 题解

## 作者：Chenyanxi0829 (赞：7)

设 $s_i$ 为 $a_1,a_2,\dots,a_i$ 的异或值，$\oplus$ 表示异或。

因为每个 $a_i$ 都一定会异或到 $P,Q,R$ 中的一个上，所以前 $i$ 个值操作完后，$P\oplus Q\oplus R$ 一定等于 $s_i$，又因为 $P,Q,R$ 有两个值是相同的，所以 $P,Q,R$ 中一定有一个值等于 $s_i$。

设 $dp_{i,j}$ 表示前 $i$ 个值操作完后除去一个等于 $s_i$ 的值其它两个值等于 $j$ 的方案数，考虑从 $dp_{i-1,j}$ 转移：
- 若 $j=s_{i-1}$，则可以任选一个数异或上 $a_i$，所以 $3dp_{i-1,j}\to dp_{i,j}$。
- 若 $j=s_i$，可以把 $a_i$ 异或到 $s_{i-1}$ 上，则 $dp_{i-1,j}\to dp_{i,j}$，或者异或到其中一个 $s_i$ 上，则这个 $s_i$ 变为 $s_{i-1}$，即 $2dp_{i-1,j}\to dp_{i,s_{i-1}}$。
- 否则如果异或到一个 $j$ 上，因为 $a_i\ge1$，所以不可能合法，所以只能异或到 $s_{i-1}$ 上，即 $dp_{i-1,j}\to dp_{i,j}$。

整合一下:
$$dp_{i-1,j}\to dp_{i,j}(j\not=s_{i-1})$$
$$3dp_{i-1,s_{i-1}}+2dp_{i-1,s_i}\to dp_{i,s_{i-1}}$$
发现只有 $s_{i-1}$ 的 dp 值与之前不同，所以直接用 map 存，每次把 $s_{i-1}$ 的 dp 值改一下就可以了。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 1, mod = 1e9 + 7;

int t, n, a[kMaxN], ans;
map<int, int> dp;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n, ans = 0, dp[0] = 1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], a[i] ^= a[i - 1], dp[a[i - 1]] = (3ll * dp[a[i - 1]] + 2ll * dp[a[i]]) % mod;
    }
    for (auto i : dp) {
      ans = (ans + i.second) % mod;
    }
    cout << ans << '\n', dp.clear();
  }
  return 0;
}
```

---

## 作者：_O_v_O_ (赞：3)

我们注意到每次做完操作后 $P\oplus Q\oplus R=\oplus_{j=1}^i a_j$，而 $P,Q,R$ 中又有两个数相等，那么根据异或的性质，$P,Q,R$ 中一定有一个数恰好等于 $\oplus_{j=1}^i a_j$。

我们设 $p_i$ 为 $a$ 的前缀异或和，那么我们注意到 $(P,Q,R)$ 有以下三种可能（其中 $x$ 为任意正整数）：$(x,x,p_i),(x,p_i,x),(p_i,x,x)$。

那么我们不妨就尝试 $dp$，设 $dp_{i,x}$ 为作为做完第 $i$ 个操作后，三元组为以上三种状态的方案数。

那么我们设 $dp_{i,x}$ 可能由以下三种状态转移而来：$(p_i\oplus a_i,x,x),(p_i,x\oplus a_i,x),(p_i,x,x\oplus a_i)$。

我们注意到后面两种可以合并为同一种，那么我们先考虑第一种：

我们注意到 $p_i\oplus a_i=p_{i-1}$，那么 $(p_i\oplus a_i,x,x)=(p_{i-1},x,x)$，即 $dp_{i-1,x}$。

第二种呢？

因为任意三元组均有两数相等，又因为 $a_i\neq 0$，那么，在三元组 $(p_i,x\oplus a_i,x)$ 中，$x\oplus a_i,x$ 必有一数与 $p_i$ 相等。

我们先看 $x=p_i$ 的情况，我们注意到，这样原来三元组就变成了 $(p_i,p_i,p_i)$，可以由 $(p_i,p_i,p_{i-1}),(p_i,p_{i-1},p_i),(p_{i-1},p_i,p_i)$，这样的方案数为 $dp_{i,p_i}$。

剩下一种情况呢？我们注意到，这样原三元组就是 $(p_i,p_{i-1},p_{i-1})$，可以由 $(p_{i-1},p_{i-1},p_{i-1})$ 转移，而这样有三种方案，还可以由 $(p_{i-1},p_i,p_i)$，有两种转移，那么就有 $dp_{i,p_{i-1}}=3\times dp_{i-1,p_{i-1}}+2\times dp_{i-1,p_i}$。

而因为 $dp_{i,j}=dp_{i-1,j}$ 时没额外贡献，那么只算最后一种即可。

那么我们发现还可以滚动数组，又因为 $x$ 可能很大，那么直接用 `std::map` 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5,mod=1e9+7;
int n,a[N];
map<int,int> dp;

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--){
		dp.clear();
		cin>>n;dp[0]=1;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]^=a[i-1];
			((dp[a[i-1]]*=3)+=2*dp[a[i]])%=mod;
		}
		int ans=0;
		for(pair<int,int> i:dp) (ans+=i.second)%=mod;
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：RayAstRa_ (赞：2)

送我上 Master 的题。

## Description

有三个初始为 $0$ 的数 $P,Q,R$ 和一个序列 $a$，第 $i$ 次操作需要选择 $P,Q,R$ 中的一个数异或上 $a_i$，需要保证每次操作后 $P,Q,R$ 至少有两个数相同，问合法的操作序列数量。

## Solution

假设 $Q=R$，则将 $Q$ 视作 $0$，将 $P$ 视作 $P\oplus Q$。

考虑 dp，设 $f_v$ 表示当前操作后 $P=v$ 的合法序列数，初始化 $f_0=1$。

则对于第 $i$ 次操作，首先可以将 $a_i$ 异或在 $P$ 上，有方程 $f_{v\oplus a_i}\leftarrow f_v$。

如果 $P=a_i$，也可以将 $a_i$ 异或在 $Q,R$ 任何一个数上，这样剩下的那一个就变成了 $P$，有方程 $f_{a_i}\leftarrow 2f_{a_i}$。

如果 $P=0$，说明三个元素均相等，可以任意选择 $Q,R$（因为和第一个转移方程有重复所以不能选 $P$）异或 $a_i$，被选中的数成为新的 $P$，有方程 $f_{a_i}\leftarrow 2f_0$。

因为直接转移复杂度是 $O(n^2)$ 的，所以设 $sum=a_1\oplus a_2\oplus\dots\oplus a_i$，$f_v$ 表示当前操作后 $P\oplus sum=v$ 的合法序列数。

对于第一个方程，$f_v\leftarrow f_v$。

对于第二个方程，$f_{sum}\leftarrow 2f_{a_i\oplus sum}$。

对于第三个方程，$f_{sum}\leftarrow 2f_{sum}$。

**注意方程左右侧 $sum$ 的值相等，但下标的意义不同！**

由于 $v$ 的值域很大，使用 map 维护 $f$。时间复杂度 $O(n\log n)$。

[Submission](https://codeforces.com/contest/2066/submission/305880193)

---

## 作者：xzhif (赞：2)

[题面](https://codeforces.com/contest/2067/problem/F "题面")

记 $\oplus$ 为异或。

记 $p_i= \oplus _{j=1}^ia_j$，那么由题意，进行 $i$  次操作后，有 $P\oplus Q\oplus R=p_i$。

因为 $P,Q,R$ 这三个数字必须不成对地不同，所以这三个数字中必有一个为 $p_i$，因为另外两个相同的数异或为 0。

考虑状态，对于 $f_{i,x}$，其三元组状态包括 $(p_i,x,x),(x,p_i,x),(x,x,p_i)$。

考虑转移：\
对于 $f_{i-1,x}$，可以转移到 $f_{i,x}$，因为 $p_{i-1}\oplus a_i=p_i$，可以操作等于 $p_{i-1}$ 的那个值，共一个。

对于 $f_{i-1,p_i}$ 可以 $\times 2$ 转移到 $f_{i,p_{i-1}}$，因为 $p_i\oplus a_i=p_{i-1}$，可以操作等于 $p_{i}$ 的那个值，共两个。

对于 $f_{i-1,p_{i-1}}$ 可以 $\times 3$ 转移到 $f_{i,p_{i-1}}$，因为 $p_{i-1} \oplus a_i=p_i$，可以操作等于 $p_{i-1}$ 的那个值，共三个，此时不需要考虑第一种转移方案，这已经包含了那种情况。

直接 dp 会爆空间，发现实际有用状态很小，实际只有 $S∈{p_i}$，转移除了 $f_{i,p_{i-1}}$ 都可以直接沿用上一次的状态，所以可以压维并离散化状态来减小空间。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+5,P=1e9+7;
ll n,a[N],p[N],c[N],d[N],f[N],ans;
void sol(){
	cin>>n,ans=0,f[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]=(p[i-1]^a[i]);
		c[i]=p[i];
	}
	sort(c+1,c+n+1);
	ll m=unique(c+1,c+n+1)-c-1;
	for(int i=1;i<=n;i++){
		d[i]=lower_bound(c+0,c+m+1,p[i])-c;
	}
	for(int i=1;i<=n;i++){
		f[d[i-1]]=(3*f[d[i-1]]+2*f[d[i]])%P;
	}
	for(int i=0;i<=n;i++){
		(ans+=f[d[i]])%=P;
		f[d[i]]=0;
	}
	cout<<ans<<'\n';
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)sol();
} 
```

---

## 作者：Gold14526 (赞：1)

$\rm Problem$:[Bitwise Slides](https://codeforces.com/contest/2066/problem/C)

介绍一个超级容易听懂的做法。

### 题意

给出长度为 $n$ 的序列 $a$，维护三个变量 $p,q,r$，初始均为 $0$。

对于 $i$ 从 $1$ 到 $n$ 依次选择以下三个操作中的一个执行：

- $p:=p\oplus a_i$
- $q:=q\oplus a_i$
- $r:=r\oplus a_i$

（其中的 $\oplus$ 表示按位异或运算）

你需要保证任意时刻 $p,q,r$ 三者中有至少两者相同，求选择操作的方案数，答案对 $10^9+7$ 取模。

$1\le n\le 2\times10^5,1\le a_i\le 10^9$

### 做法

设 $x=p\oplus q,y=q\oplus r,z=r\oplus p$。

那么题意转化为：每次选择 $x,y,z$ 中的两个异或上 $a_i$，使得 $x,y,z$ 中始终有两者相同，另一者为 $0$。

直接维护 $dp_{i,j}$ 表示操作完 $a_i$ 后相同的两个数等于 $j$ 的方案数，我们考虑两种情况：

- 把原来两个相同的数异或上 $a_i$，则从 $dp_{i-1,j}$ 能转移到 $dp_{i,j\oplus a_i}$，特别的，由于 $j=0$ 时三个数都相同，可以任选两个数，那么 $dp_{i-1,0}$ 转移到 $dp_{i,a_i}$ 时有 $3$ 的系数。
- 把一个数变成 $0$，一个数变成 $a_i$，则从 $dp_{i-1,a_i}$ 转移到 $dp_{i,a_i}$，有 $2$ 的系数。

其中从 $dp_{i-1,j}$ 转移到 $dp_{i,j\oplus a_i}$ 这一部分数组的值都没变，但是下标都异或了 $a_i$，可以用 01-Trie 维护，时间复杂度 $O(n\log V)$。

### 代码

（由于个人码风原因，代码看上去会比较长）

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	print(x);
	putchar(ch);
}


cint mod=1e9+7,H=30;
namespace Trie{
	struct node{
		int son[2],sum;
	}t[7000001];
	int tot;
	int tag;
	int new_ver()
	{
		++tot;
		t[tot].son[0]=t[tot].son[1]=t[tot].sum=0;
		return tot;
	}
	void clear()
	{
		tot=tag=0;
		new_ver();
	}
	void ins(int x,cint y)
	{
		if(!y)return;
		x^=tag;
		int p=1;
		t[p].sum=(t[p].sum+y)%mod;
		for(int i=H;i>=0;--i)
		{
			const bool c=((x>>i)&1);
			if(!t[p].son[c])
			{
				t[p].son[c]=new_ver();
			}
			p=t[p].son[c];
			t[p].sum=(t[p].sum+y)%mod;
		}
	}
	int ask(int x)
	{
		x^=tag;
		int p=1;
		for(int i=H;i>=0;--i)
		{
			const bool c=((x>>i)&1);
			p=t[p].son[c];
		}
		return t[p].sum;
	}
	int all()
	{
		return t[1].sum;
	}
	void allxor(cint x)
	{
		tag^=x;
	}
}
int n,a[200001];
void solve()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	Trie::clear();
	Trie::ins(0,1);
	for(int i=1;i<=n;++i)
	{
		cint p=Trie::ask(0),q=Trie::ask(a[i]);
		Trie::allxor(a[i]);
		Trie::ins(a[i],(q<<1)%mod);
		Trie::ins(a[i],(p<<1)%mod);
	}
	princh(Trie::all(),'\n');
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

首先考虑暴力的转移，当枚举到第 $i$ 个数时，我们尝试将之前所有的有效状态的 $P,Q,R$ 均与 $a_i$ 尝试去异或，然后检测合法性。于是就有：

```cpp
la[{0,0,0}] = 1;
for (int i = 1;i <= n;++i)
{
	for (auto item : la)
	{
		node v = item.first;
		int x = v.p,y = v.q,z = v.r;
		if (y == z || (x ^ a[i]) == y || (x ^ a[i]) == z) dp[{x ^ a[i],y,z}] += la[v];
		if (x == z || (y ^ a[i]) == x || (y ^ a[i]) == z) dp[{x,y ^ a[i],z}] += la[v];
		if (x == y || (z ^ a[i]) == x || (z ^ a[i]) == y) dp[{x,y,z ^ a[i]}] += la[v];
	}
	for (auto item : dp) dp[item.first] %= MOD;
	la.clear ();la = dp;dp.clear ();
}
```

但这样显然会有很多冗余的转移以及判断，考虑异或的性质去优化。

回顾一下题面，对于一个数字只能选择 $P,Q,R$ 中的一个去异或，那么处理完 $a_i$ 后，$P \oplus Q \oplus R = \oplus _{j = 1}^i a_j = p_i$。由于 $P,Q,R$ 不能两两互异，此时设 $(P,Q,R)$ 中相同的数为 $x$，由于 $x \oplus y \oplus y = x$，故可能的有效状态为 $(x,x,p_i),(x,p_i,x),(p_i,x,x)$ 中的一个。

设 $dp_{i,x}$ 表示在处理第 $i$ 个数后相同的数为 $x$ 的方案数。则 $(x,x,p_i)$ 的上一个状态可能为 $(x \oplus a_i,x,p_i)$ 或 $(x,x,p_i \oplus a_i)$。

- 上一个状态为 $(x \oplus a_i,x,p_i)$

  由于要保证状态的合法性，需要分类讨论具体是哪两个数相同：
  1. $x \oplus a_i = x \Rightarrow a_i = 0$，与题干矛盾，故不可能成立。
  2. $x \oplus a_i = p_i \Rightarrow x = p_{i - 1}$，此时转移方程为 $dp_{i,x} = dp_{i,p_{i - 1}} = dp_{i-1,p_i}$。
  3. $x = p_i$，此时转移方程为 $dp_{i,x} = dp_{i,p_i} = dp_{i - 1,p_i}$

- 上一个状态为 $(x,x,p_i \oplus a_i)$

  显然，转移方程为 $dp_{i,x} = dp_{i - 1,x}$。

通过观察可以发现，$dp_{i,x} \leftarrow dp_{i - 1,x}$ 不成立当且仅当 $x = p_{i - 1}$ 的情况，其余直接继承。最终状态为 $(x,x,p_i)$，代入 $x$ 后是 $(p_{i - 1},p_{i - 1},p_i)$。由 $(p_{i - 1},p_{i - 1},p_{i - 1})$ 转移共有三种方式，而由 $(p_{i - 1},p_i,p_i)$ 转移共有两种方式。同时，可以发现可以利用滚动数组优化，因此可以有：

$$
dp_{p_{i - 1}} = 2 \times dp_{p_i} + 3 \times dp_{p_{i - 1}}
$$

当然，初始条件为 $dp_{0} = 1$。数字过大，离散化或者直接用 map 即可。代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,a[MAX],p[MAX];ll ans;
map <int,ll> dp;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();ans = 0;dp.clear ();
		for (int i = 1;i <= n;++i) a[i] = read (),p[i] = p[i - 1] ^ a[i];
		dp[0] = 1;
		for (int i = 1;i <= n;++i) dp[p[i - 1]] = (dp[p[i]] * 2 + dp[p[i - 1]] * 3) % MOD;
		for (auto item : dp) ans = (ans + item.second) % MOD;
		printf ("%lld\n",ans);
	} 
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：rainygame (赞：0)

性质题。

设 $s_i$ 表示 $[1,i]$ 的 $a_i$ 异或和，那么显然有 $P\oplus Q\oplus R=s_i$，又因为 $P,Q,R$ 中有两个相同的，所以必定有一个是 $s_i$。

考虑 DP。设 $f_{i,j}$ 表示进行完前 $i$ 个操作后，有两个数等于 $j$，剩下那个等于 $s_i$ 的方案数。

考虑转移。设现在是 $(s_{i-1},j,j)$。那么要么 $(s_{i-1}\oplus a_i,j,j)$，要么 $(s_{i-1},j\oplus a_i,j)$。对于第一种，最后操作成 $(s_i,j,j)$，所以 $f_{i,j}\leftarrow f_{i-1,j}$；对于第二种，若 $j\ne s_{i-1}$，由于 $a_i\ge1$，所以必定有 $j\oplus a_i=s_{i-1}$，得 $j=s_i$，所以 $f_{i,s_{i-1}}\leftarrow 2f_{i-1,s_i}$；若 $j=s_{i-1}$，则得 $(s_{i-1},s_{i-1},s_i)$，所以 $f_{i,s_{i-1}}\leftarrow 2f_{s_{i-1}}$。

容易发现每次只需要修改 $f_{i,s_{i-1}}$ 的值，用 `map` 维护即可。时间复杂度 $O(n\log n)$。[submission](https://codeforces.com/contest/2066/submission/312081295)

---

## 作者：rubbishZZZ (赞：0)

## CF2066C Object Identification



#### 题意：

- 给定一个数组 $a_1, a_2, \dots, a_n$，另外给定三个变量 $P, Q, R$，初始值均为零。

  你需要按顺序处理所有数字 $a_1, a_2, \dots, a_n$。在处理下一个 $a_i$ 时，你必须执行以下三种操作中的恰好一种：

  - $P \leftarrow P \oplus a_i$
  - $Q \leftarrow Q \oplus a_i$
  - $R \leftarrow R \oplus a_i$

  其中，$\oplus$ 表示按位异或操作。

  在执行操作时，必须遵循一个主要规则：每次操作后，$P, Q, R$ 三个数必须不是彼此不同的。

  总共有 $3^n$ 种方式来执行所有的 $n$ 个操作。请计算有多少种方式不违反主要规则。由于答案可能非常大，请对 $10^9 + 7$ 取模。



#### 解法：

- 我们设 $sum_i$ 表示  $a_1\oplus a_2\oplus\cdots\oplus a_i$，则在 $i$ 时刻 $P\oplus Q\oplus R=sum_i$，且 $P,Q,R$ 中有两个一样。那么一定是一个 $sum_i$ 与两个相同的数，无序情况下形如 $(x,x,sum_i)$。

  那么 $(x,x,sum_i)$ 由什么转移而来的？

  1. $(x,x,sum_i)\leftarrow (sum_{i-1},sum_{i-1},sum_{i-1}\oplus a_i),x=sum_{i-1}$。系数为 $3$。
  2. $(x,x,sum_i)\leftarrow(sum_i,sum_i\oplus a_i,sum_{i-1}),x=sum_{i-1}$。系数为 $2$。

  那么用 map 来维护 $dp_{i,j}$ 表示考虑了前 $i$ 个数，$x=j$ 的方案数。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}
//int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
//void Fplus(int&x,int y){x=fplus(x,y);}
//int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
//void Fminus(int&x,int y){x=fminus(x,y);}

const int mod=1e9+7,N=200005;
int n,a[N],ans;
map<int,int>mp;

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	for(int T=read();T--;){
		ans=0;
		map<int,int>().swap(mp);
		n=read();
		rep(i,1,n)a[i]=read();
		mp[0]=1;
		int x=0;
		rep(i,1,n){
			mp[x]=(mp[x]*3+mp[a[i]^x]*2)%mod;
			x^=a[i];
		}
		for(pii p:mp)ans=(ans+p.se)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

## Statement

给定长度为 $n$ 的数组 $a$，同时你拥有一个三元组 $(P,Q,R)$，每次定义操作如下：

1. $P:=P \oplus a_i$

2. $Q:=Q \oplus a_i$

3. $R:=R \oplus a_i$

显然的，最多有 $3^n$ 次操作方法。

我们定义规则：每次操作后必须保证三元组内有两数相等。

求有多少种操作方法不违背规则，答案对 $10^9 + 7$ 取模。

$n \leq 2 \times 10^5$。

## Solution

异或有一个性质：$x \oplus x = 0$，可以从这里入手。

我们记 $p_i$ 为 $a$ 数组的前缀异或和，我们会发现每次操作后 $P \oplus Q \oplus R = p_i$，所以说每次三元组的状态就是：

$$
(p_i,x,x) \\ (x,p_i,x) \\ (x,x,p_i)
$$

考虑它们从何转移而来，记 $dp_{i,x}$ 表示当前在 $i$ 三元组中相等两数值为 $x$ 的方案数。

首先对于 $(p_i,x,x)$，它是从 $(p_i \oplus a_i,x,x)$ 转移而来，根据异或的性质，$p_i \oplus a_i = p_{i-1}$，所以这里 $dp_{i,x} = dp_{i-1,x}$。

对于另外两种，当 $x = p_i$ 时，状态为 $(p_i,p_i,p_i)$，它可以从 $(p_{i-1},p_i,p_i),(p_i,p_{i-1},p_i),(p_i,p_i,p_{i-1})$ 任意一种转移过来，所以 $dp_{i,x} = dp_{i-1,x}$，当 $x = p_{i-1}$ 时，它可以从 $(p_{i-1},p_{i-1},p_{i-1})$ 转移，这样有三种方案，也可以从 $(p_{i-1},p_i,p_i),(p_i,p_{i-1},p_i),(p_i,p_i,p_{i-1})$ 共两种方案，注意到都只和 $i-1$ 有关，滚动数组优化，所以这样一番推导下方程就有了：

$$
dp_{p_{i-1}} = dp_{p_{i-1}} \times 3 + dp_{p_i} \times 2
$$

最后答案即为 $\sum\limits_{i=1}^{n}{dp_{p_i}}$。

数组开不下用 map 映射。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10, MOD = 1e9 + 7;
int T, n, A[MAXN], preXor[MAXN];
map <int, int> dp;

inline void Dp() {
    cin >> n, dp.clear();
    for (int i = 1; i <= n; i ++)
        cin >> A[i], preXor[i] = preXor[i - 1] ^ A[i];
    dp[0] = 1;
    for (int i = 1; i <= n; i ++) 
        dp[preXor[i - 1]] = (dp[preXor[i - 1]] * 3 % MOD + dp[preXor[i]] * 2 % MOD) % MOD;
    int Ans = 0;
    for (auto [u, v] : dp)
        Ans = (Ans + v) % MOD;
    cout << Ans << '\n';
}

signed main() {
    cin.tie (0) -> sync_with_stdio (0);
    cout.tie (0) -> sync_with_stdio (0);
    cin >> T;
    while (T --) Dp();
    return 0;
}
```

---

