# Destroy the Colony

## 题目描述

有一个反派的聚居地，里面有若干个洞排成一排，每个洞里恰好有一个反派。

每种聚居地的排列可以表示为一个偶数长度的字符串，第 $i$ 个字符表示第 $i$ 个洞里的反派类型。

只有当某种类型的所有反派都只生活在聚居地的前半部分或后半部分时，钢铁侠才能摧毁这个聚居地。

他的助手 Jarvis 有一种特殊能力，可以任意交换两个洞里的反派，即可以任意交换字符串中的任意两个字符，这个操作可以进行任意多次。

现在钢铁侠向 Jarvis 提出了 $q$ 个问题。每个问题给出两个数字 $x$ 和 $y$，Jarvis 需要告诉钢铁侠：通过他的能力，从原始排列中可以构造出多少种不同的聚居地排列，使得原本在第 $x$ 个洞或第 $y$ 个洞的反派类型的所有反派都只生活在同一半部分，并且钢铁侠可以摧毁这个聚居地。

如果存在某个洞，在两个排列中该洞里的反派类型不同，则认为这两个排列是不同的。

## 说明/提示

考虑第一个样例。对于第一个问题，可能的排列有 "aabb" 和 "bbaa"；对于第二个问题，第 $1$ 个位置是 'a'，第 $2$ 个位置是 'b'，不存在一种有效的排列使得所有 'a' 和 'b' 都在同一半部分。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
abba
2
1 4
1 2
```

### 输出

```
2
0
```

## 样例 #2

### 输入

```
AAaa
2
1 2
1 3
```

### 输出

```
2
0
```

## 样例 #3

### 输入

```
abcd
1
1 3
```

### 输出

```
8
```

# 题解

## 作者：KaguyaH (赞：10)

有一偶数长度字符串 $s$，$q$ 次询问，每次询问给两位置 $x, y$，求满足下列条件的 $s$ 的排列 $p$ 的方案数。

- 对于任意字符，要么集中在 $p$​​​ 前半段，要么集中在 $p$​​​​ 后半段；
- $s_x, s_y$ 在同一段。

两种排列方案 $p, q$​ 不同，当且仅当 $\exists 1 \leq i \le |s|$ 满足 $p_i \neq q_i$。

$|s| \leq 10^5$，$q \leq 10^5$​，$s$ 中仅含字母。

---

记字符集为 $\Sigma$，有 $|\Sigma| = 52$。比较显然地，本质不同的询问仅有至多 $|\Sigma|^2$​​ 种。

如果已经钦定各字符在哪一段，设 $c_x$ 为字符 $x$ 的出现次数，则方案数为

$$C = (\frac n 2)!^2 \prod_{x} c_x!^{-1}.$$

考虑钦定 $s_x, s_y$ 均在前半段，设钦定方案数为 $g$，则答案为 $2Cg$。

考虑求出 $g$。

定义 $f_x$ 表示选择一些字符 $\Sigma'$，使 $\sum_{i \in \Sigma'} c_i = x$ 的方案数。​

$\forall x, y \in \Sigma$​​，利用支持删除操作的背包，在 $f$​​ 中依次删去 $x, y$​​，得到 $f'$​，则 $g_{x, y} = f'_{\frac {|s|} 2 - c_x - c_y}$​。

注意特殊处理 $x = y$ 的情况。

时间复杂度 $\mathcal O(|s|(|\Sigma|^2 + \log|s|))$，空间复杂度 $\mathcal O(|\Sigma|^2 + |s|)$，可过。

---

```cpp
# include <ciso646>
# include <cstdio>
# include <cstring>
# define forletter(i) for (char i('a'); i not_eq 'Z' + 1; i == 'z' ? (i = 'A') : ++i)

namespace Main {
  typedef unsigned int uint;
  typedef short unsigned int hu;
  static inline const uint qpow(uint a, uint n, const uint mod) {
    uint r(1);
    while (n) {
      if (n bitand 1) r = 1ull * r * a % mod;
      a = 1ull * a * a % mod, n >>= 1;
    }
    return r;
  }
  static inline const uint invp(const uint x, const uint p) { return qpow(x, p - 2, p); }
  static const uint S(1e5);
  static const uint P(1e9 + 7);
  static uint fact[S + 1]{ 1 }, ifact[S + 1]{ 1 };
  static char s[S + 2];
  static uint n, q;
  static uint c[128];
  static uint f[S + 1]{ 1 };
  static uint g[128][128];
  static uint bc;
  static inline const void init() {
    n = strlen(s + 1);
    for (register uint i(1); i <= n; ++i) ifact[i] = invp(fact[i] = 1ull * fact[i - 1] * i % P, P);
    f[0] = 1;
    for (register uint i(1); i <= n; ++i) ++c[s[i]];
    forletter(i) if (c[i]) for (register uint j(n); j >= c[i]; --j) f[j] = (f[j] + f[j - c[i]]) % P;
    bc = 1ull * fact[n / 2] * fact[n / 2] % P;
    forletter(i) bc = 1ull * bc * ifact[c[i]] % P;
  }
  static inline const void solve(const char a, const char b) {
    if (!c[a] or !c[b]) return;
    if (a == b) {
      if (c[a] > n / 2) return (const void)(g[a][a] = 0);
      static uint h[S + 1]; for (register uint i(0); i <= n; ++i) h[i] = f[i];
      for (register uint i(c[a]); i <= n; ++i) h[i] = (h[i] + P - h[i - c[a]]) % P;
      return (const void)(g[a][a] = 1ull * h[n / 2 - c[a]] * bc * 2 % P);
    }
    if (c[a] + c[b] > n / 2) return (const void)(g[a][b] = 0);
    static uint h[S + 1]; for (register uint i(0); i <= n; ++i) h[i] = f[i];
    for (register uint i(c[a]); i <= n; ++i) h[i] = (h[i] + P - h[i - c[a]]) % P;
    for (register uint i(c[b]); i <= n; ++i) h[i] = (h[i] + P - h[i - c[b]]) % P;
    g[a][b] = 1ull * h[n / 2 - c[a] - c[b]] * bc * 2 % P;
  }
  static inline const void main() {
    scanf("%s", s + 1), init();
    forletter(i) forletter(j) solve(i, j);
    scanf("%u", &q);
    for (register uint i(0); i < q; ++i) { static uint x, y; scanf("%u%u", &x, &y), printf("%u\n", g[s[x]][s[y]]); }
  }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：SayGB (赞：7)

题意:

给出 一堆序列(包含大写小写字母)，每种字母可以出现若干次。

现在 给出一组 x,y 问:
       A.x,y在同一半
       B.同种字母出现在同一半 
       符合A,B条件后组合的情况是多少种？

题解:

首先我们先化简下问题，既然同种类型都在同一侧，那原序列查重后，仅有k种类型，c1,c2,c3,c4...ck(好像有点多余(∩_∩!)

(因为 可以交换无数次，初始序列的顺序并不影响我们解决问题)

那怎么找符合条件的序列形式呢？

先观察答案的其中一种形式
假设c1,c2..cp 在前半部分 并且 数量刚好凑成n/2 (B条件)

那组合出来的情况 就是  (n/2)! / { (c1!) * (c2!) * (c3!)...(cp)! }  [这里c1是指c1这个字母出现的次数]

//因为 n/2个元素全排列就 (n/2)! 种可能性，但其中有一些相同的类型 比如说 1,1 这两个1，一个出现在3位置，一个出现在5位置,反过来一个//出现在5位置，一个出现在3位置 ，这两种情况 其实是一样的，所以要除以他们 相同元素间的阶乘，就好啦

同样，剩下的几个元素 组合出来的情况就是 (n/2)! /{ 剩下元素出现次数的阶乘 的乘积 } 

结合在一起的话，那满足B条件下的组合方式 的数量就是 

(n/2)! *(n/2)! / (所有元素出现次数的阶乘的乘积) = W (恒定的)

//注意 在模运算中 除一个数 我们要 转变为成一个数的逆元 上面注意用 费马小定理 求逆元就行咯

哎，我们发现满足 B条件下 的组合数是恒定的，只要知道 有多少种 方式 可以 让若干个元素刚好凑成 n/2 ，假设有X种

那 B*X 就是我们所要的答案(吗？)

而X怎么出来的呢？其实就是k件物品 填满 容量为 n/2的背包的 方式  ，这里呢套个背包就好了。

问题又来了，x,y这两个类型的物品，要放在一起，怎么解决呢？

因为询问次数有点大，不能暴力排除x,y的背包
转化一下的话，其实我们可以预处理先求出完整k件物品的背包，让x,y挪出去，其实是对应的把 x,y的背包贡献减去即可
这里可以预处理下，对付很大的x,y询问(要注意观察数据范围额)

考虑了x,y之后那 答案构成就是 B*(排除x,y的背包数)*2  //乘2 是因为 有 两半 放嘛

以上就是我对这道题目的一些思考，有说得不对的地方，烦请指出。

接下来就是代码啦~~


```c
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

ll dp[100010], tdp[100010],rem[60][60];
ll cnt[100010],inv[100010],fac[100010],W;
char str[100010];
const ll mod = 1e9 + 7;

int c_pos(char c) {
	if (c >= 'A' && c <= 'Z')return c - 'A' + 1;
	else return c - 'a' + 1 + 26;
}

ll fpow(ll a, ll n) {
	ll ans = 1;
	while (n > 0) {
		if (n & 1) ans = ans * a%mod;
		a = a * a%mod;
		n >>= 1;
	}
	return ans;
}

void get_w(int n) {
	fac[0] = 1;
	int m = n / 2;
	for (int i = 1; i <= n; ++i) fac[i] = i * fac[i - 1] % mod;
	W = fac[m] * fac[m] % mod;
	for (int i = 1; i <= 52; ++i) {
		if (cnt[i] == 0) continue;
		inv[i] = fpow(fac[cnt[i]], mod - 2);
		W = W * inv[i] % mod;
	}
}

void init() {
	scanf("%s", str + 1);
	int len = strlen(str+1);
	for (int i = 1; i <= len; ++i) ++cnt[c_pos(str[i])];
	get_w(len);
	dp[0] = 1;//背包为空也是一种
	int m = len / 2;
	for (int i = 1; i <= 52; ++i) {
		if (cnt[i] == 0) continue;
		for (int j = m; j >= cnt[i]; --j) dp[j] = (dp[j] + dp[j - cnt[i]]) % mod;
	}

	//for (int i = 0; i <= len; ++i) printf("%d: %lld\n", i, dp[i]);
	for (int i = 1; i <= 52; ++i) {
		if (cnt[i] == 0) continue;
		for (int j = 1; j <= 52; ++j) {
			if (cnt[j] == 0) continue;
			for (int k = 0; k <= m; ++k) tdp[k] = dp[k];//tmp_dp <- dp
			for (int k = cnt[i]; k <= m; ++k) tdp[k] = (tdp[k] - tdp[k - cnt[i]] + mod) % mod;//将i物品从背包清除,注意这里顺序
			if(i!=j) for (int k = cnt[j]; k <= m; ++k) tdp[k] = (tdp[k] - tdp[k - cnt[j]] + mod) % mod;
			rem[i][j] = tdp[m];
		}
	}
}

int main() {
	init();
	int q;
	scanf("%d", &q);
	while (q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		int px = c_pos(str[x]), py = c_pos(str[y]);
		printf("%lld\n", rem[px][py] * W * 2 % mod);
	}
	return 0;
}
```

---

## 作者：daifucong (赞：6)

一开始我以为只要钦定若干个字母在同一侧，别的随便摆就行了

开心的写了一发，Wrong Answer on pretest 4

然后就出现了一个公告，每种字母都必须出现在同一侧

~~以下是深夜神志不清时laji思路~~

于是$f[i][j]$表示前$j$个字母，前半段的长度为$i$的方案数

令$cnt[j]$表示第$j$种颜色的出现次数

同时维护$len[j]=\sum_{k=1}^{j}cnt[j]$

$f[i+cnt[j+1]][j+1]+=f[i][j]*C_{i}^{i+cnt[j+1]}$

$f[i][j+1]+=f[i][j]*C^{len[j+1]-i}_{len[j]-i}$

然后滚存一下，$52^2$枚举一下被钦定的两个字符

优秀的$O(52^3*n)$算法，~~显然不能通过~~

这个时候我们发现如果在滚存后的f数组中加入一种字符的操作是可逆的，那么就可以用类似退背包的方法做

那么现在只要构造一个多项式$g[1..n/2]$，使得$f[1..n/2][j]*g[1..n/2]=f[1..n/2][j+1]$，那么加入一种字符可以看成多项式乘法，去掉一种字符可以看成多项式除法，由于退背包问题中$g$的次数或非零项个数一般非常小，手动模拟多项式乘法除法即可

~~显然我推不下去了~~

~~以上内容均为扯淡~~

第二天再登上CF

~~woc我B题FST了???!!!~~

~~开始看题解~~

如果我们有一种字符分配方案，即确定每一种字符在左半边或者右半边，会给答案带来$((n/2)!)^2*\prod_{i=1}^{52}(cnt[i]!)$的贡献，由初赛知识可知，一边的贡献是$(n/2)!$与所有在左边的字符出现次数阶乘的积，右边的贡献是$(n/2)!$与所有在右边的字符出现次数阶乘的积，两者相乘即为上式

这样我们就只要求出有多少种字符分配方案即可

直接背包即可$O(52^3*n)$解决该问题

然后上个退背包即可$O(52^2*n)$Accepted

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007,maxc=1000100;
inline int ksm(int a,int b)
{
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) res=1ll*res*a%mod;
	return res;
}
int fac[maxc],invfac[maxc];
inline int C(int n,int m){return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;}
inline int getid(char c)
{
	if(c>='a'&&c<='z') return c-'a'+1;
	else return c-'A'+27;
}
const int Lim=52;
int cnt[100],n,Ans;
int ans[100][100],f[50010];
inline void Insert(int siz){if(siz) for(int j=(n>>1);j>=siz;j--) (f[j]+=f[j-siz])%=mod;}
inline void Remove(int siz){if(siz) for(int j=siz;j<=(n>>1);j++) (f[j]+=mod-f[j-siz])%=mod;}
inline void init()
{
	f[0]=1;
	for(int i=1;i<=Lim;i++) Insert(cnt[i]);
	for(int i=1;i<=Lim;i++)
	{
		Remove(cnt[i]);
		for(int j=i+1;j<=Lim;j++)
		{
			Remove(cnt[j]);
			ans[i][j]=2*f[n>>1]%mod;
			Insert(cnt[j]);
		}
		Insert(cnt[i]);
	}
}
inline int cal(int x,int y)
{
	if(x==y) return 1ll*Ans*f[n>>1]%mod;
	if(x>y) swap(x,y);
	return 1ll*Ans*ans[x][y]%mod;
}
string s;
int main()
{
	fac[0]=1;for(int i=1;i<maxc;i++) fac[i]=1ll*fac[i-1]*i%mod;
	invfac[maxc-1]=ksm(fac[maxc-1],mod-2);
	for(int i=maxc-2;i>=0;i--) invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	cin>>s;n=s.length();s="Q"+s;
	for(int i=1;i<=n;i++) cnt[getid(s[i])]++;
	Ans=1ll*fac[n>>1]*fac[n>>1]%mod;
	for(int i=1;i<=Lim;i++) Ans=1ll*Ans*invfac[cnt[i]]%mod;init();
	int Q;scanf("%d",&Q);
	while(Q--)
	{
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",cal(getid(s[x]),getid(s[y])));
	}
}
```

---

## 作者：do_while_true (赞：3)

orz qyc

设 $m=\frac{|s|}{2}$．

看起来很像背包，由基础组合数学知识可知，把每个字符出现次数看做体积为 $1$ 的物品，做 01 背包后 $m$ 能被凑出的方案数，乘上 $(m!)^2$ 再除去每个数出现次数的阶乘即为没有限制的答案。

有限制了怎么做？可以看成删去这两个物品，然后把两个物品捆绑在一起加进来，做 01 背包。这个题就变成了 [LuoguP4141 消失之物](https://www.luogu.com.cn/problem/P4141)。

注意到字符集大小为 $52$，所以本质不同的询问仅有 $52^2$ 个。

由于背包放进去物品的顺序没有关系，所以删去一个物品的时候直接顺序一遍减掉贡献即可。

设字符集大小为 $|E|$，则复杂度为 $\mathcal{O}(|E|^2n+q)$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long ll;
const ll mod = 1000000007;
template <typename T> T Add(T x, T y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T cAdd(T x, T y) { return x = (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T Mul(T x, T y) { return x * y % mod; }
template <typename T> T Mod(T x) { return x < 0 ? (x + mod) : x; }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
ll qpow(ll x, ll y) {
	ll sumq = 1;
	while(y) {
		if(y & 1) sumq = sumq * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return sumq;
}
const int N = 100010;
int n, m, q, a[N], vis[53];
ll f[N], ans[53][53];
ll fac[N], inv[N];
char ch[N];
int char_to_int(char x) {
	if(x >= 'a' && x <= 'z') return x-'a';
	return x-'A'+26;
}
void add(int s) {
	if(!s) return ;
	for(int i = m; i >= s; --i) f[i] = Add(f[i], f[i-s]);
}
void del(int s) {
	if(!s) return ;
	for(int i = s; i <= m; ++i) f[i] = Add(f[i], Mod(-f[i-s]));
}
signed main() { //freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
	scanf("%s", ch+1); n = std::strlen(ch+1); m = n / 2;
	for(int i = 1; i <= n; ++i) a[i] = char_to_int(ch[i]);
	fac[0] = 1; for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
	inv[n] = qpow(fac[n], mod-2);
	for(int i = n-1; ~i; --i) inv[i] = inv[i+1] * (i+1) % mod;
	for(int i = 1; i <= n; ++i) ++vis[a[i]];
	f[0] = 1;
	ll mul = fac[m] * fac[m] % mod;
	for(int i = 0; i < 52; ++i) {
		add(vis[i]);
		mul = mul * inv[vis[i]] % mod;
	}
	for(int i = 0; i < 52; ++i) ans[i][i] = f[m];
	for(int i = 0; i < 52; ++i)
		for(int j = i+1; j < 52; ++j) {
			del(vis[i]); del(vis[j]);
			add(vis[i]+vis[j]);
			ans[i][j] = ans[j][i] = f[m];
			del(vis[i]+vis[j]);
			add(vis[i]); add(vis[j]);
		}
	read(q);
	for(int i = 1; i <= q; ++i) {
		int x, y; read(x); read(y);
		printf("%lld\n", ans[a[x]][a[y]] * mul % mod);
	}
	return 0;
}
```

---

## 作者：_Eriri_ (赞：3)

一道计数题，是乘法原理的很好体现。


在回答询问前先做好准备 : 

1. 设每种字母的出现次数为 $cnt_i$ 。

2. 以下询问的 $x,y$ 将直接表示对应位置的字母。

3. 在分配方案中，一个字符属于的组别(前半后半)称作 $group_i$ 。


现在考虑询问 $x,y$ 的解答：

我直接把式子写出来，再一步一步讲解。

$$
Ans=2 \cdot{C}_\frac{n}{2}^{cnt_x+cnt_y} \cdot \frac{(cnt_x+cnt_y)!}{cnt_x!cnt_y!} \cdot f_{x,y} \cdot \frac{(\frac{n}{2})!(\frac{n}{2}-cnt_x-cnt_y)!}{\prod_{i\neq{x,y}}cnt_i!}
$$

先看到 $2 \cdot{C}_\frac{n}{2}^{cnt_x+cnt_y} \cdot \frac{(cnt_x+cnt_y)!}{cnt_x!cnt_y!} $ 这一坨， 其实很好理解，前后两半选法为2种，然后在总共 $\frac{n}{2}$ 个位置里找到所有放置方案，最后定序。

接下来是后面部分

首先是这个 $f_{x,y} $ 的意义：它表示在不使用 $x,y$ 的情况下，有几种字符的**组合**使它们的 $cnt_i$ 之和为 $\frac{n}{2}$ 。当 $x,y$ 的 $group$ 确定后，剩下一组只能用非 $x,y$ 的字符来填充，所以需要知道这个填充的方案数。 之后的一坨阶乘比较抽象， 其实是简化的结果，读者可以看一个更容易理解的式子：

$$
\frac{(\frac{n}{2})!}{\prod_{i \notin group_x}cnt_i!} \cdot \frac{(\frac{n}{2}-cnt_x-cnt_y)!}{\prod_{i\in group_x \land i\neq {x,y}}cnt_i! }
$$

其实这就是对所有非 $x,y$ 元素的定序，和第一部分是完全一样的。

读者可以理解这个“定序”的过程，它往往是 $\frac{(\sum cnt_i)!}{\prod cnt_i!}$ 的形式， 一句话总结：外部有序，内部无序。

最后是代码实现阶段，由于 $x,y$ 很少，所以可以直接预处理所有 $x,y$ 的答案。除了 $f_{x,y}$ 以外都可以通过预处理逆元和阶乘 $O(1)$ 计算，至于这个删除后的背包怎么在 $O(m)$ 的时间复杂度内从原先的背包搞过来，并不是本题的重点，洛谷有一道模板题P4141，建议去学习。

还是在说一下把，$f_j$ 是用所有元素做出来的背包，而
$g_j$ 是删除元素 $x$ 后的背包，有方程:

$$
g_j=f_j-g_{j-w_x}
$$

你把它看成是容斥吧，就行了。

最后总时间复杂度 $O({|\Sigma|}^2n+q)$ 可以通过本题。

---

## 作者：Cgod (赞：2)

# 吐槽

先吐槽一波，这场CF我Bfst，D差一秒没交上去。然后喜闻乐见的掉了不少。还有这场CF考验的是你的英语能力，不得不说这位出题人是真的英语好，我光看懂题可能就花了四、五十分钟。。。

# 题意

题意大概是说，给你一个字符串，字符集大小56。

q次询问x和y，让你任意重排它，要求满足

1.同一种字符只能在左边或右边出现。

2.原来x和y位置上的字符在新串中必须在同一边。

# sol

先发现就是给你56个数，你要把它们中的一部分组成$\frac n2$,每一种贡献是$\frac {n!}{\prod a_i!}$。

简单背包好吧。

先处理出最后的背包，每次询问的时候直接删除，记得记忆化。

复杂度大概是$O(56*n+56*56*n)$?反正很快就对了。

代码就不贴了。

---

## 作者：NATO (赞：1)

萌萌计数题，但模拟赛时因为减法忘加模数、加减法过度取模而暴毙。

### 思路浅析：

注意到按照题述中的能力，我们可以搞出任何一种可以搞出的方案，所以答案只会和每种字符的出现次数有关。

考虑到 $x,y$ 所对应的字符不同的情况一共就只有 $\frac{52\times51}{2}=1326$ 种，还没有最大询问数多，那么就考虑枚举是哪两种字符组合，预处理答案。

设两种字符分别为 $s_a,s_b$，出现次数分别为 $cnt_a,cnt_b$。

为了方便叙述，我们在这里只讨论 $s_a\neq s_b$ 的情况，相等的情况非常类似，不做说明（~~读者自推不难~~）。

首先，我们考虑把答案分成三个部分来算。

1. $s_a,s_b$ 的放置方案。

2. $s_a,s_b$ 所在的那一半剩下的位置的放法。

3. 另外一半的放法。

算出来后乘一起再乘 $2$ （两半对换）即可。

第一个部分是很平凡的，$C_{\frac{n}{2}}^{cnt_a+cnt_b}\times C_{cnt_a+cnt_b}^{cnt_a}$，组合意义显然。

重点在于后面两部分的计算。

我们先考虑如何计算出另外一半整体的方案数（即不考虑内部的放法，只考虑另外一边可以放哪些字符进去），发现这就是知道了一些大小不同的物品，问凑出某个数的方案数，考虑 $0-1$ 背包记录方案数，枚举的时候将 $s_a,s_b$ 的贡献退掉即可。

而 $s_a,s_b$ 所在的那一半剩下的位置的整体放法在确定了另外一半整体的方案后有且是唯一的。

再考虑这两种情况内部的放法。

容易想到实际上这就是两个多重集的排列数的积，如果分开算那么下面除以的两个部分就是我们所选择的数的阶乘之积，分开考虑就不可避免要根据放到放法去考虑，这样肯定是会爆炸的。

我们整体考虑这部分的贡献，发现除掉的部分就是除开我们枚举的两个字母，其它字母出现次数的阶乘的积，而上半部分合起来就是 $\frac{n}{2}!\times(\frac{n}{2}-cnt_a-cnt_b)!$。

那么算出来所有字母出现次数的阶乘的积，乘以枚举的数的阶乘即可算出我们所需要除的数。

那么将第一部分的值、背包算出来的方案数、整体计算出的两个多重集的排列数乘起来就是我们当前枚举的情况的方案数了。

枚举并预处理计算即可。

设出现的不同字符数为 $k$，时间复杂度 $O(k^2n+q)$ 足以通过此题。

#### 参考代码：

```cpp
// LUOGU_RID: 152881680
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007ll
#define mol(x) x>=MOD?x-MOD:x
using namespace std;
string s;
ll q,cnt[53];
ll to[129],tot;
bool vis[129];
ll f[100005],inv[100005];
ll dp[100005],ndp[100005];
ll ans[53][53];
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return res;
}
ll C(ll n,ll m)
{
	return f[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>s;
	ll n=s.size();
	f[0]=1;
	for(ll i=1;i<=n;++i)f[i]=f[i-1]*i%MOD;
	inv[n]=qpow(f[n],MOD-2);
	for(ll i=n-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%MOD;
	for(ll i=0;i<n;++i)
	if(!vis[s[i]])vis[s[i]]=1,to[s[i]]=++tot;
	for(ll i=0;i<n;++i)++cnt[to[s[i]]];
	dp[0]=1;
	for(ll i=1;i<=tot;++i)
		for(ll j=n;j>=cnt[i];--j)
			dp[j]=(dp[j]+dp[j-cnt[i]])%MOD;
	ll invn=1;
	for(ll i=1;i<=tot;++i)invn=invn*inv[cnt[i]]%MOD;
	for(ll i=1;i<=tot;++i)
	{
		for(ll k=0;k<cnt[i];++k)ndp[k]=dp[k];
		for(ll k=cnt[i];k<=n;++k)ndp[k]=((dp[k]-ndp[k-cnt[i]])%MOD+MOD)%MOD;
		for(ll j=i;j<=tot;++j)
		{
			ll invu=invn;
			if(i!=j)invu=invu*f[cnt[i]]%MOD*f[cnt[j]]%MOD;
			else invu=invu*f[cnt[i]]%MOD;
			if(i!=j)
			{
			for(ll k=cnt[j];k<=n;++k)
				ndp[k]=mol((ndp[k]-ndp[k-cnt[j]])+MOD);
			if(cnt[i]+cnt[j]<=n/2)
				ans[i][j]=ans[j][i]=ndp[n/2]*f[n/2]%MOD*f[n/2-cnt[i]-cnt[j]]%MOD*invu%MOD*C(n/2,cnt[i]+cnt[j])%MOD*C(cnt[i]+cnt[j],cnt[i])%MOD;
			for(ll k=n;k>=cnt[j];--k)
				ndp[k]=mol(ndp[k]+ndp[k-cnt[j]]);
			}
			else
			{
				if(cnt[i]<=n/2)
				ans[i][j]=C(n/2,cnt[i])*ndp[n/2]%MOD*f[n/2]%MOD*f[n/2-cnt[i]]%MOD*invu%MOD;
			}
		}
	}	
	cin>>q;
	ll x,y;
	while(q--)
	{
		cin>>x>>y;
		cout<<ans[to[s[x-1]]][to[s[y-1]]]*2%MOD<<'\n';
	}
}//预处理爆炸了那就好玩了。。。
//感觉会因为取模的常数而爆炸。。。
```

---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1111D)

[CF](https://codeforces.com/problemset/problem/1111/D)

### 写在前面

这道题被放在了我们周赛的最后一题。

第一二三题都是普及难度的水题，秒杀。

第四题回滚莫队的板子题，不过正解是随机化？

第五题普通的树形 DP，第六题线段树分治背包，都是套路题。

第七题换根 DP，不过略微有点复杂，赛时通过了，赛后喜提 Hacked。

第八题也就是最后一题，时间只剩下 20 分钟，赛时没想出来，听讲之后恍然大悟。

不过好在也拿到了第二名。

### 分析

分析题目，要求满足两个条件。

1. 每一种恶棍都要在一个半区。

1. $x$ 和 $y$ 恶棍要被分到同一个半区。

先考虑第一个条件，我们把每种恶棍看成一个整体，令其在一个半区，进行背包，就可以算出初始系数 $2 \times \frac{({\frac{n}{2}!})^{2}}{\prod sum!}$，其中乘 $2$ 是由于有两个半区。

然后我们发现由于大小写字母加起来只有 $52$ 个，所以本质不同的询问最多只有 $\frac{(52 + 1) \times 52}{2} = 1378$ 个，我们对于除了 $x$ 和 $y$ 的恶棍进行容量为 $\frac{n}{2}$ 的背包，算出方案数即可。

但这样会超时，观察该背包的状态转移方程 $dp_i = dp_i + dp_{i-x}$，我们只需要倒序执行 $dp_i = dp_i - dp_{i-x}$ 就可以撤销体积为 $x$ 的物品，并消除其对答案的影响。

所以，我们先对全体物品进行背包，然后每次询问 $x$ 和 $y$ 时撤销 $x$ 和 $y$，询问完毕后重新加入 $x$ 和 $y$ 即可。

时间复杂度为 $O(nm)$，其中 $m$ 为本质不同的询问个数，其中 $m_{max} = 1378$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 200010
const int mod = 1e9 + 7;
ll fac[N],inv[N],ans[55][55],mul;
char s[N];
int sum[55],a[N],n,m;
struct Bag
{
	ll dp[N];
	Bag() {dp[0] = 1;}
	inline void insert(int x)
	{
		if(!x) return;
		D(i,n>>1,x) dp[i] = (dp[i] + dp[i-x]) % mod;
	}
	inline void erase(int x)
	{
		if(!x) return;
		F(i,x,n>>1) dp[i] = (dp[i] - dp[i-x] + mod) % mod;
	}
	inline ll query() {return dp[n>>1];}
}bag;
inline int code(char c)
{
	if('A' <= c&&c <= 'Z') return c-'A'+1;
	return c-'a'+27;
}
int main()
{
	scanf("%s",s+1);
	n = strlen(s+1);
	F(i,1,n) a[i] = code(s[i]),++sum[a[i]];
	memset(ans,-1,sizeof(ans));
	fac[0] = fac[1] = inv[0] = inv[1] = 1ll; 
	F(i,2,n) fac[i] = fac[i-1] * i % mod;
	F(i,2,n) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	F(i,2,n) inv[i] = inv[i] * inv[i-1] % mod;
	mul = 2ll * fac[n>>1] * fac[n>>1] % mod;
	F(i,1,52) mul = mul * inv[sum[i]] % mod;
	F(i,1,52) bag.insert(sum[i]);
	read(m);
	while(m--)
	{
		int x,y;
		read(x),read(y);
		x = a[x],y = a[y];
		if(x > y) swap(x,y);
		if(ans[x][y] >= 0) 
		{
			write(mul * ans[x][y] % mod);
			putchar('\n');
			continue;
		}
		if(x == y)
		{
			bag.erase(sum[x]);
			ans[x][y] = bag.query();
			bag.insert(sum[x]);
		}
		else
		{
			bag.erase(sum[x]);
			bag.erase(sum[y]);
			ans[x][y] = bag.query();
			bag.insert(sum[x]);
			bag.insert(sum[y]);
		}
		write(mul * ans[x][y] % mod);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：chroneZ (赞：1)

给定一偶长度字符串 $S$，$q$ 组询问，每次询问给定 $x, y$，求本质不同的 $S$ 的排列数，满足

- 同种字符都位于前半段或后半段
- $S_x, S_y$ 这两种字符位于同一半段

------------------------------

记 $c_x$ 表示字符 $x$ 的出现次数，$n \gets |S|$，字符集为 $\Sigma$。将问题分步处理。

为满足同种字符位于同一半段，考虑钦定一些字符 $T = \{x_i\} \subset \Sigma$ 位于前半段，$s.t.\sum \limits_{x \in T} c_x = \frac{n}{2}$。则前半段的本质不同排列数为 $(\frac{n}{2})! \prod \limits_{x \in T}(c_x!)^{-1}$，后半段为 $(\frac{n}{2})! \prod \limits_{x \in \overline T}(c_x!)^{-1}$，二者之积为 $W = (\frac{n}{2})!^2 \prod \limits_{x \in \Sigma} (c_x!)^{-1}$，显然此限制下方案数 $W$ 为一定值。

为满足 $S_x, S_y$ 两种字符位于同一半段，计选择一些字符 $T = \{x_i\} \subset \Sigma$ 位于前半段，$s.t.T \supset \{S_x, S_y\}, \sum \limits_{x \in T} c_x = \frac{n}{2}$ 的方案数为 $g$，这个 $g$ 可以用一个支持删除的01背包统计出来。对于这 $g$ 种字符集 $T$ 可以选择放在前/后半段，每种选择下又有 $W$ 种本质不同排列方案，因此最终答案为 $Ans = 2gW$。

- $q$ 在 $10 ^ 5$ 量级，但容易发现本质不同询问只会有 $|\Sigma|^2$ 种，因此可以预处理。
- 注意特判 $S_x = S_y$。

$\texttt{Main Code}$

```cpp
inline int conv(char x) {return ('a' <= x && x <= 'z' ? x - 'a' : x - 'A' + 26);}
inline int m(int x) {return (x % mod + mod) % mod;}
i64 fact[N], inv[N];
int f[N], f2[N], f3[N], g[60][60], c[60];
void solve(){
	string S; cin >> S;
	int n = S.length();
	for(int i = 0; i < 52; i++) c[i] = 0;
	for(int i = 0; i < n; i++) c[conv(S[i])]++;

	i64 W = fact[n / 2] * fact[n / 2] % mod;
	for(int i = 0; i < 52; i++) W = W * inv[c[i]] % mod;
	
	f[0] = 1;
	for(int i = 0; i < 52; i++){
		if(!c[i]) continue;
		for(int j = n / 2; j >= c[i]; j--) f[j] = (f[j] + f[j - c[i]]) % mod;
	}
	for(int i = 0; i < 52; i++){
		if(!c[i]) continue;
		if(c[i] > n / 2){
			for(int j = i; j < 52; j++) g[i][j] = g[j][i] = 0;
			continue;
		}
		for(int j = 0; j < c[i]; j++) f2[j] = f[j];
		for(int j = c[i]; j <= n / 2 - c[i]; j++) f2[j] = m(f[j] - f2[j - c[i]]);
		g[i][i] = f2[n / 2 - c[i]];
		for(int j = i + 1; j < 52; j++){
			if(!c[j]) continue;
			if(c[i] + c[j] > n / 2) {g[i][j] = g[j][i] = 0; continue;}
			for(int v = 0; v < c[j]; v++) f3[v] = f2[v];
			for(int v = c[j]; v <= n / 2 - c[i] - c[j]; v++) f3[v] = m(f2[v] - f3[v - c[j]]);
			g[i][j] = g[j][i] = f3[n / 2 - c[i] - c[j]];
		}
	}

	int q, l, r; cin >> q;
	while(q--){
		cin >> l >> r; l--, r--;
		cout << W * g[conv(S[l])][conv(S[r])] * 2 % mod << "\n";
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	fact[0] = 1, inv[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % mod, inv[i] = ksm(fact[i], mod - 2, mod);
	solve();
}
```

> 带删除的01背包的形式大致是 $f'_i = f_i - f'_{i - w}$，具体见[例题](https://www.luogu.com.cn/problem/P4141)


---

## 作者：东厢头场雪 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1111D)
## 题目大意及数据范围
给定一个长度为 $|s|$ 的字符串，由至多52种字符组成（大小写字母），$m$ 次询问，每次询问两个字符 $x$ 和 $y$，问有多少种重排方案满足以下两个条件  
1. 同种字符都在该字符串的同一半
2. $x$ 和 $y$ 两种字符在该字符串的同一半

数据满足 $1\leq |s|,m\leq 10^5$ 且 $|s|$ 为偶数
### 前置知识
01背包计数与物品删除、高中组合数学、求逆元（可能需要快速幂、费马小定理、扩展欧几里得等）
### 解析
首先考虑统计每种字符出现次数，记为 $t[i]$。先不考虑询问的 $x$ 与 $y$，对于每一种满足条件1的合法方案，应选取一个子集使得元素个数恰为 $\frac{|s|}{2}$，考虑组合的除序法，结合乘法原理可得排列方案数为  
$W = \frac{(\frac{|s|}{2})!^2}{\prod_{i = 1}^{52}t_i!}$  
预处理 $W$ 时，需要维护分母的逆元完成除法取模  
考虑假设 $x$ 和 $y$ 均在前半段，设 $d$ 为选出一个子集使其元素个数为 $\frac{|s|}{2}$ 的方案数。  
考虑求 $d$ 的方法  
可以对 $d$ 做一个01背包计数：共52个物品，背包容量为 $\frac{|s|}{2}$ ，物品的价值为 $t[i]$，求出后则总答案即为 $2Wd$  
时间复杂度为 $O(52|s| + log|s|)$，空间复杂度 $O(52^2 + |s|)$，可以通过本题。  
### 细节处理
1. 三年 $OI$ 一场空，不开 $long\ long$ 见祖宗！
2. 字符处理，为枚举方便，使用技巧，见代码。
3. 状态设计 $dp[i]$ 表示还有 $i$ 个没填时的方案数
4. 根据状态设计可知初始化 $dp[0] = 1$  
5. 删除物品记录答案后为保证正确性要加回来
6. 特殊判断 $x=y$ 的情况  
## 代码奉上
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const int N = 100000 + 10;
const ll mod = 1000000000 + 7;
char s[N];
ll ans[60][60];
ll n,tot,q,w,cf,njc;
ll t[60];
ll dp[N];
ll jc(ll x)
{
	if(x == 0) return 1;
	ll res = 1;
	for(int i = 1;i <= x;i++)
	  res = res * i % mod;
	return res;
}
ll change(char c)
{
	if(c >= 'A' && c <= 'Z') return c - 'A';
	else return c - 'a' + 26;
}
ll ksm(ll x,ll y,ll p)
{
	if(y == 0) return 1;
	if(y == 1) return x % p;
	ll k = ksm(x,y /2,p) % p;
	if(y & 1) 
	  return k * k % p * x % p;
	else return k * k % p;
}
int main()
{
	cin >> s;
	n = strlen(s);
	njc = jc(n /  2) % mod;
	njc = njc * njc % mod;
    for(int i = 0;i < n;i++)
      t[change(s[i])]++;
    tot = 1;
    for(int i = 0;i < 52;i++)
      tot = tot * jc(t[i]) % mod;
    cf = ksm(tot,mod - 2,mod);
    w = njc * cf % mod;
    dp[0] = 1;
    for(int i = 0;i < 52;i++)
      if(t[i])
        for(int j = n / 2;j >= t[i];j--)
          dp[j] = (dp[j - t[i]] + dp[j]) % mod;
    for(int i = 0;i < 52;i++)
    {
    	for(int j = i;j < 52;j++)
    	{
    		if(!t[i] || !t[j]) continue;
    		if(i == j)
    		{
    			if(t[i] > n / 2) ans[i][j] = 0;
    			else
    			{
    				for(int k = t[i];k <= n / 2;k++)
    				  dp[k] = (dp[k] - dp[k - t[i]] + mod) % mod;
    				ans[i][j] = dp[n / 2 - t[i]]  % mod * 2 * w % mod;
    				for(int k = n / 2;k >= t[i];k--)
    				  dp[k] = (dp[k - t[i]] + dp[k]) % mod;
    			}
    			continue;
    		}
    		if(t[i] + t[j] > n / 2)
    		{
    			ans[i][j]= ans[j][i] = 0;
    			continue;
    		}
    		for(int k = t[i];k <= n / 2;k++)
    		  dp[k] = (dp[k] - dp[k - t[i]] + mod) % mod;
    		for(int k = t[j];k <= n / 2;k++)
    		  dp[k] = (dp[k] - dp[k - t[j]] + mod) % mod;
    		ans[i][j] = ans[j][i] = dp[n / 2 - t[i] - t[j]] * 2 % mod * w % mod;
    		for(int k = n / 2;k >= t[j];k--)
    		  dp[k] = (dp[k] + dp[k - t[j]]) % mod;
    		for(int k = n / 2;k >= t[i];k--)
    		  dp[k] = (dp[k] + dp[k - t[i]]) % mod;
    	}
    }
	scanf("%lld",&q);
	while(q--)
	{
		ll u,v;
		scanf("%lld%lld",&u,&v);
		printf("%lld\n",ans[change(s[u-1])][change(s[v-1])]);
	}
	return 0;
}
```
~~完结撒花，开心~~

---

## 作者：phil071128 (赞：0)

**Destroy the Colony**

一遍过了 *2600，有点爽。

先考虑如果没有额外的限制的做法，只要求满足每种字符要么全在前半段，要么全在后半段。这显然是个大小为 $\frac{n}{2}$ 的背包，将每种字符的出现次数看做其重量即可。

还有一点小问题是，多重集的排列需要除以一个 $\prod w_i!$ 的系数，而且注意到左右两边是独立的，所以答案可以写成：
$$
\frac{(\frac{n}{2}!)^2\times dp[n/2]}{\prod (w_i!)}
$$
现在考虑加入限制，不妨先特判 $s_x=s_y$ 的情况，相当于没有限制。

对于 $s_x\ne s_y$，我们不妨先简单分类：

- $s_x$ 在左侧，$s_y$ 也在左侧。
- $s_x$ 在左侧，$s_y$ 在右侧。
- $s_x$ 在右侧，$s_y$ 在左侧。
- $s_x$ 在右侧，$s_y$ 也在右侧。

而 $dp[S]$ 实际上求出了上述全部四种情况，而我们需要将 $2,3$ 情况去掉。

容易想到**退背包**，即我们分别令不考虑 $s_x$，不考虑 $s_y$，两者都不考虑的背包答案为 $ans1,ans2,ans3$。那么根据简单容斥原理，只考虑 $1,4$ 情况的答案为：
$$
dp[n/2]-ans1-ans2+2\times ans3
$$
退背包有模板：[P4141 消失之物 - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/P4141)，具体思想是：正序枚举背包大小，如果 $j< w_i$，那么一定不包含当前物品，$ans[j]=dp[j]$，否则，需要减去能转移到包含当前物品的个数，即 $ans[j]=dp[j]-ans[j-w[i]]$。

但是本题询问 $q=10^5$，不过本质不同的询问只有 $(\sum)^2$ 的，所以总时间复杂度为 $O((\sum)^2n+q)$。


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
int trans(char c) {
	if(c>='a'&&c<='z') return c-'a'+1;
	if(c>='A'&&c<='Z') return c-'A'+27;
}
const int N=1e5+500;
int dp[N];
char s[N];
int ans1[N],ans2[N],ans3[N];
int fac[N],cnt[N],inv[N];
int ans[100][100];
const int mod=1e9+7;
int ksm(int a,int b) {
	if(b==1) return a;
	int s=ksm(a,b/2);s=s*s%mod;
	if(b%2==1) s=s*a%mod;
	return s;
}
signed main(){
	//fil();
	scanf("%s",s+1);
	int n=strlen(s+1);
	int m=trans('Z');
	for(int i=1;i<=n;i++) {
		cnt[trans(s[i])]++;
	}
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,inv[i]=ksm(fac[i],mod-2)%mod;
	int W=n/2;
	dp[0]=1;
	for(int i=1;i<=m;i++) {
		if(cnt[i]==0) continue;
		for(int j=W;j>=cnt[i];j--) {			
			dp[j]=(dp[j]+dp[j-cnt[i]]%mod)%mod;
		}
	}
	for(int i=1;i<=m;i++) {
		if(cnt[i]==0) continue;
		memset(ans1,0,sizeof ans1);
		ans1[0]=1;
		for(int j=1;j<=W;j++) {
			if(j<cnt[i]) ans1[j]=dp[j];
			else ans1[j]=(dp[j]-ans1[j-cnt[i]]%mod+mod)%mod;
		}
		for(int j=1;j<=m;j++) {
			if(j==i) continue;
			if(cnt[j]==0) continue;
			memset(ans2,0,sizeof ans2);memset(ans3,0,sizeof ans3);
			ans2[0]=ans3[0]=1;
			for(int k=1;k<=W;k++) {
				if(k<cnt[j]) ans2[k]=dp[k];
				else ans2[k]=(dp[k]-ans2[k-cnt[j]]%mod+mod)%mod;
				if(k<cnt[j]) ans3[k]=ans1[k];
				else ans3[k]=(ans1[k]-ans3[k-cnt[j]]%mod+mod)%mod;
			}
			ans[i][j]=(dp[W]-ans1[W]-ans2[W]+2*ans3[W]%m	od+mod+mod)%mod;
		}
	} 
	int _inv=1;
	for(int i=1;i<=m;i++) _inv=_inv*inv[cnt[i]]%mod;
	int q=read();
	while(q--) {
		int x=read(),y=read();
		if(s[x]==s[y]) {
			cout<<fac[W]*fac[W]%mod*_inv%mod*dp[W]%mod<<"\n";
		}
		else {
			cout<<fac[W]*fac[W]%mod*_inv%mod*ans[trans(s[x])][trans(s[y])]%mod%mod<<"\n";
		}
	}	
	return 0;
}

```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定字符串 $s$，长度为偶数，和 $q$ 个询问，每次询问给出 $x,y$，问 $s$ 有多少个不同的排列满足，所有相同字符都在前 $\dfrac{|s|}{2}$ 个或者后 $\dfrac{|s|}{2}$ 个，且 $s_x$ 和 $s_y$ 在同一部分（要么都在前 $\dfrac{|s|}{2}$ 个或者都在后 $\dfrac{|s|}{2}$ 个）。排列不同当且仅当两个排列存在一个位置字符不同。答案对 $10^9+7$ 取模。

$2\leq |s|\leq 10^5$，$1\leq q\leq 10^5$。

# 题目思路

本质不同的询问只有 $52\times 52$ 个，可以先全部求出来然后 $\mathcal O(1)$ 回答。

比较暴力的做法是枚举 $x,y$ 表示钦定哪两个字符在一起。DP 的时候同时跳过这两个字符，设 $f_{i,j}$ 表示前 $i$ 个字符凑出长度为 $j$ 的方案数，然后会得到复杂度 $\mathcal O(|\Sigma|^3 n)$ 的做法。

考虑优化，发现每次枚举 $y$ 都会重做一遍 DP，非常浪费。

如果我们可以快速删除 $y$ 就可以把复杂度降到 $\mathcal O(|\Sigma|^2 n)$。

可以考虑回退背包。但是有更简便的做法，我们设 $f_{i,j}$ 表示前 $[1,i]$ 的字符凑出长度为 $j$ 的方案数，设 $g_{i,j}$ 表示 $[i,52]$ 的字符凑出长度为 $j$ 的方案数。

那么枚举 $y$ 可以很方便的合并这两个 DP 求答案。

这是大致思路。转移的方程也比较复杂。这里只说 $f$ 的，$g$ 是对称的。

首先不放钦定 $x,y$ 都在前半段，方案数 $\times 2$ 就是总的方案数。

第一种转移情况是不选择这种字符到后半段，也就是选择这种字符到前半段。此时设前 $i$ 种字符总长度为 $len$，那么选择这种字符到前半段也就是对前半段有一个插入方案数的系数。

> 引理 1：
>
> 对于长度为 $x$ 的字符串，插入 $y$ 个一样的字符，不同的字符串个数是 $\binom{x+y}{y}$ 的。

也就是这里选择这种字符到前半段，会产生 $\binom{len-j}{cnt_i}$ 的系数。转移也就是 $f_{i,j} \gets f_{i-1,j} \times \binom{len - j}{cnt_i}$。

第二种情况是直接把这种字符选到后半段。转移与上面类似，是 $f_{i,j}\gets f_{i,j} + f_{i-1,j-cnt_i} \times \binom{j}{cnt_i}$。

$g$ 的转移是对称的。

合并的时候枚举 $y$，枚举 $[1,y-1]$ 选择长度为 $l$，令 $m=\dfrac{n}{2}$，那么答案应该是 $2\times \binom{m}{cnt_y}\times \sum f_{y-1,l}\times g_{y+1,m-l}\times \binom{m}{l}\times \binom{m-cnt_y}{len-l}$。其中 $len$ 是前 $y-1$ 种字符的长度之和。

这个合并的几个组合数，分别对应了后半段插入的方案系数和前半段插入的方案系数。意义就是『引理 1』的部分。

使用预处理阶乘逆元后，复杂度是 $\mathcal O(|\Sigma|^2 n)$ 的。

# 完整代码

[无卡常擦线过 CF submission 289044991](https://codeforces.com/contest/1111/submission/289044991)

[轻度卡常 CF submission 289045577](https://codeforces.com/contest/1111/submission/289045577)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
const int p = 1000000007;
string s;
int n;
int q;
int cnt[55];
const int N = 5e4;
ll fac[50020];
ll inv[50020];
struct Mod
{
    const ll m = ((LL)1 << 64) / p;
    inline ll operator()(ll x) { return x - ((LL(x) * m) >> 64) * p; }
} mod;
inline ll C(int n, int i) { return i > n || i < 0 || n < 0 ? 0 : mod(mod(fac[n] * inv[i]) * inv[n - i]); }
inline ll qpow(ll x, ll y)
{
    ll ret = 1;
    for (; y > 0; y >>= 1)
    {
        if (y & 1)
            ret = mod(ret * x);
        x = mod(x * x);
    }
    return ret;
}
ll f[54][50020];
ll g[54][50020];
ll ans[54][54];
inline int id(char c) { return islower(c) ? c - 'a' + 1 : c - 'A' + 27; }
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = mod(fac[i - 1] * i);
    inv[N] = qpow(fac[N], p - 2);
    for (int i = N; i >= 1; i--)
        inv[i - 1] = mod(inv[i] * i);
    cin >> s >> q;
    for (int i : s)
        cnt[id(i)]++;
    n = s.size();
    s = ' ' + s;
    int m = n / 2;
    // cout << fac[m] << endl;
    for (int x = 1; x <= 52; x++)
    {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        int len = 0;
        for (int i = 1; i <= 52; i++)
        {
            len += cnt[i];
            for (int j = max(0, len - m); j <= m; j++)
                f[i][j] = mod(f[i - 1][j] * C(len - j, cnt[i]));
            if (i == x || !cnt[i])
                continue;
            for (int j = cnt[i]; j <= m; j++)
                f[i][j] = mod(f[i][j] + f[i - 1][j - cnt[i]] * C(j, cnt[i]));
        }
        memset(g, 0, sizeof(g));
        g[53][0] = 1;
        len = 0;
        for (int i = 52; i >= 1; i--)
        {
            len += cnt[i];
            for (int j = max(0, len - m); j <= m; j++)
                g[i][j] = mod(g[i + 1][j] * C(len - j, cnt[i]));
            if (i == x || !cnt[i])
                continue;
            for (int j = cnt[i]; j <= m; j++)
                g[i][j] = mod(g[i][j] + g[i + 1][j - cnt[i]] * C(j, cnt[i]));
        }
        len = 0;
        for (int y = 1; y < x; y++)
            len += cnt[y];
        for (int y = x; y <= 52; y++)
        {
            ll sum = 0;
            for (int l = 0; l <= m; l++)
            {
                int r = m - l;
                sum = mod(sum + mod(f[y - 1][l] * g[y + 1][r]) * mod(C(m, l) * C(m - cnt[y], len - l)));
            }
            len += cnt[y];
            ans[x][y] = ans[y][x] = mod(sum * 2 * C(m, cnt[y]));
        }
    }
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        x = s[x], y = s[y];
        cout << mod(ans[id(x)][id(y)]) << '\n';
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 思路

首先统计每种字符的出现次数，记为 $t_{i}$。先不考虑 $x$ 和 $y$，对于一种合法方案，需要选出一个子集使得其和为 $\frac{n}{2}$，每种选法对应的排列方案数是 $W=\frac{\frac{n}{2}!\cdot \frac{n}{2}!}{\prod_{i=1}^{52}t_{n}}$。

因为 $\frac{n}{2}$ 个元素就有 $\frac{n}{2}!$ 种可能性，但其中有一些相同的类型，比如说 $1,1$，这两个  $1$，一个出现在 $3$ 的位置，一个出现在 $5$ 位置，反过来一个，出现在 $5$ 位置，一个出现在 $3$ 位置，这两种情况 其实是一样的，所以要除以他们相同元素间的阶乘，就好啦！

注意：在模运算中除一个数我们要转变为成一个数的逆元，因为 ${10}^9+7$ 是质数，所以用费马小定理求逆元就行咯！
于是我们就可以先预处理出 $w$，以便后面使用！
然后我们考虑 $x,y$ 这个条件，设考虑 $x,y$ 这个条件后，方案数是 $d$，那么根据乘法原理，总的答案就是 $2\cdot w \cdot d$（乘 $2$ 是因为把 $n$ 分成了两半）。

那么我们怎么求 $d$ 呢？其实就是 $k$ 件物品，填满容量为 $\frac{n}{2}$ 的背包的方式，这里呢套个 $01$ 背包计数就好了！问题又来了，$x,y$ 这两个类型的物品，要放在一起，怎么解决呢？因为询问次数有点大，不能暴力排除 $x,y$ 的背包。转化一下的话，其实我们可以预处理先求出完整 $k$ 件物品的背包，让 $x,y$ 挪出去，其实是对应的把 $x,y$ 的背包贡献减去即可，这里可以预处理下，对付很大的 $x,y$ 询问（要注意观察数据范围额）。

# AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll dp[100010],bp[100010],a[60][60],v[100010],inv[100010],fac[100010],W;
char s[100010];
int get_pos(char c) 
{
	if (c>='A'&&c<='Z') return c-'A'+1;
	else return c-'a'+1+26;
}
ll quickpow(ll a,ll n) 
{
	ll res=1;
	while(n>0) 
	{
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}

void get_w(int n) 
{
	fac[0]=1;
	int m=n/2;
	for(int i=1;i<=n;i++) fac[i]=i*fac[i-1]%mod;
	W=fac[m]*fac[m]%mod;
	for(int i=1;i<=52;i++) //费马小定理求逆元
	{
		if(v[i]==0) continue;
		inv[i]=quickpow(fac[v[i]],mod-2);
		W=W*inv[i]%mod;
	}
}
void init() 
{
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++) v[get_pos(s[i])]++;
	get_w(len);
	dp[0] = 1;
	int m=len/2;
	for(int i=1;i<=52;i++) 
	{
		if(v[i]==0) continue;
		for(int j=m;j>=v[i];j--) dp[j]=(dp[j]+dp[j-v[i]])%mod;
	}
	for(int i=1;i<=52;i++) 
	{
		if(v[i]==0) continue;
		for(int j=1;j<=52;j++) 
		{
			if(v[j]==0) continue;
			for(int k=0;k<=m;k++) bp[k]=dp[k];//背包中去掉i物品
			for (int k=v[i]; k<=m;k++) bp[k]=(bp[k]-bp[k-v[i]]+mod)%mod;//这里+mod的原因是减完可能为负，所以+mod使之为正
			if(i!=j) for(int k=v[j]; k<=m;k++) bp[k]=(bp[k]-bp[k-v[j]]+mod)%mod;
			a[i][j]=bp[m];
		}
	}
}
int main() 
{
	init();
	int q;
	scanf("%d",&q);
	while(q--) 
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int px=get_pos(s[x]),py=get_pos(s[y]);
		printf("%lld\n",a[px][py]*W*2%mod);
	}
	return 0;
}
```


---

## 作者：蒟蒻君HJT (赞：0)

题解区的回退背包太高级了，其实有更好想的方法（可能大佬们习惯用生成函数推，所以容易想到回退）。

直接快进到每次询问给定了两种字符 $x,y$，要求求出其余 $50$ 种字符中选出一部分，使得出现次数总和为 $0.5n$ 的方案数。

枚举 $x$，即第一个要扔掉的字符。考虑求出 $f_{i,j}$ 表示不用字符 $x$ 的情况下，前 $i$ 种字符的组合出出现次数为 $j$ 的方案数。$g_{i,j}$ 表示不用字符 $x$ 的情况下，后 $53-i$ 种字符的组合出出现次数为 $j$ 的方案数。

那么枚举 $y$，合并 $f_{y-1,}$ 和 $g_{y+1,}$ 即可。

答案是 $\displaystyle\sum_{k=0}^{0.5n}f_{y-1,k}\times g_{y+1,0.5n-k}$。

code

```cpp
#include <bits/stdc++.h>
int c[52], tr[1005], ans[52][52], base = 1, fac[100005];
int f[52][50005], g[52][50005], q, n;
char s[100005];
const int mod = 1e9 + 7;
inline int mul(int x, int y){
  return (int)(1ll * x * y % (1ll * mod));
}
inline int add(int x, int y){
  return x + y >= mod ? x + y - mod : x + y;
}
inline int minus(int x, int y){
  return x < y ? x - y + mod : x - y;
}
inline int Qpow(int x, int y){
  int r = 1;
  while(y){
    if(y & 1) r = mul(r, x);
    x = mul(x, x); y >>= 1;
  }
  return r;
}
int main(){
  scanf("%s", s + 1); n = strlen(s + 1);
  for(int i = 0; i < 26; ++i) tr[i + 'a'] = i;
  for(int i = 0; i < 26; ++i) tr[i + 'A'] = i + 26;
  for(int i = 1; i <= n; ++i) ++c[tr[s[i]]];
  fac[0] = 1;
  for(int i = 1; i <= n; ++i) fac[i] = mul(i, fac[i - 1]);
  base = mul(fac[n / 2], fac[n / 2]); base = mul(base, 2);
  for(int i = 0; i < 52; ++i) base = mul(base, Qpow(fac[c[i]], mod - 2));
  for(int i = 0; i < 52; ++i){
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    f[0][0] = g[51][0] = 1;
    if(i != 0 && c[0] <= n / 2) f[0][c[0]] = 1;
    if(i != 51 && c[51] <= n / 2) g[51][c[51]] = 1;
    for(int j = 1; j < 52; ++j){
      for(int k = 0; k <= n / 2; ++k){
        f[j][k] = f[j - 1][k];
        if(j != i && k >= c[j] && c[j]) f[j][k] = add(f[j][k], f[j - 1][k - c[j]]);
      }
    }
    for(int j = 50; j >= 0; --j){
      for(int k = 0; k <= n / 2; ++k){
        g[j][k] = g[j + 1][k];
        if(j != i && k >= c[j] && c[j]) g[j][k] = add(g[j][k], g[j + 1][k - c[j]]);
      }
    }
    if(c[i] <= n / 2) ans[i][i] = f[51][n / 2 - c[i]];
    for(int j = 0; j < 52; ++j){
      if(j == i) continue;
      if(c[i] + c[j] > n / 2) continue;
      if(j == 0) ans[i][j] = g[1][n / 2 - c[i] - c[j]];
      else if(j == 51) ans[i][j] = f[50][n / 2 - c[i] - c[j]];
      else 
        for(int k = 0; k <= n / 2 - c[i] - c[j]; ++k)
          ans[i][j] = add(ans[i][j], mul(f[j - 1][k], g[j + 1][n / 2 - c[i] - c[j] - k]));
    } 
  }
  scanf("%d", &q);
  for(int i = 1; i <= q; ++i){
    int x, y; scanf("%d%d", &x, &y);
    printf("%d\n", mul(base, ans[tr[s[x]]][tr[s[y]]]));
  }
  return 0;
}
```


---

