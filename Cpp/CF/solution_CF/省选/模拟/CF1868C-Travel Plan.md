# Travel Plan

## 题目描述

During the summer vacation after Zhongkao examination, Tom and Daniel are planning to go traveling.

There are $ n $ cities in their country, numbered from $ 1 $ to $ n $ . And the traffic system in the country is very special. For each city $ i $ ( $ 1 \le i \le n $ ), there is

- a road between city $ i $ and $ 2i $ , if $ 2i\le n $ ;
- a road between city $ i $ and $ 2i+1 $ , if $ 2i+1\le n $ .

Making a travel plan, Daniel chooses some integer value between $ 1 $ and $ m $ for each city, for the $ i $ -th city we denote it by $ a_i $ .

Let $ s_{i,j} $ be the maximum value of cities in the simple $ ^\dagger $ path between cities $ i $ and $ j $ . The score of the travel plan is $ \sum_{i=1}^n\sum_{j=i}^n s_{i,j} $ .

Tom wants to know the sum of scores of all possible travel plans. Daniel asks you to help him find it. You just need to tell him the answer modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A simple path between cities $ x $ and $ y $ is a path between them that passes through each city at most once.

## 说明/提示

In the first test case, there is only one possible travel plan:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868C/174bc55d5276e07ded8544a87fba16b280750561.png)Path $ 1\rightarrow 1 $ : $ s_{1,1}=a_1=1 $ .

Path $ 1\rightarrow 2 $ : $ s_{1,2}=\max(1,1)=1 $ .

Path $ 1\rightarrow 3 $ : $ s_{1,3}=\max(1,1)=1 $ .

Path $ 2\rightarrow 2 $ : $ s_{2,2}=a_2=1 $ .

Path $ 2\rightarrow 1\rightarrow 3 $ : $ s_{2,3}=\max(1,1,1)=1 $ .

Path $ 3\rightarrow 3 $ : $ s_{3,3}=a_3=1 $ .

The score is $ 1+1+1+1+1+1=6 $ .

In the second test case, there are four possible travel plans:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868C/2ac3d1ded7f0949fbcfb24c8db30783d05e5ecda.png)Score of plan $ 1 $ : $ 1+1+1=3 $ .

Score of plan $ 2 $ : $ 1+2+2=5 $ .

Score of plan $ 3 $ : $ 2+2+1=5 $ .

Score of plan $ 4 $ : $ 2+2+2=6 $ .

Therefore, the sum of score is $ 3+5+5+6=19 $ .

## 样例 #1

### 输入

```
5
3 1
2 2
10 9
43 20
154 147```

### 输出

```
6
19
583217643
68816635
714002110```

# 题解

## 作者：vegetable_king (赞：12)

很好写的 $O(\sum m \log n)$ 做法，目前 solution size 排第三。

因为 $m$ 比较小，所以考虑枚举 $\max$。容斥一下，设 $F_x$ 表示对于每条链，链上的点 $\max \le x$，其他点任意填的方案数，即 $\max$ 恰好等于 $i$ 的方案数即为 $ans_x = F_x - F_{x - 1}$。答案为 $\sum_{x = 1}^m x(F_x - F_{x - 1}) = F_m - \sum_{x = 1}^{m - 1} F_x$。

$\max \le x$ 是容易求的，即每个点都 $\le x$。所以对于一个在路径上的点，它的填法有 $x$ 种，否则有 $m$ 种。

考虑树形 DP，设 $f_k$ 表示大小为 $k$ 的树内的路径填法和，$g_k$ 表示到大小为 $k$ 树的内**到根**的路径填法和，有转移方程：

$$g_k = x(g_{ls}m^{rs} + m^{ls}g_{rs} + m^{k - 1})$$

$$f_k = g_k + xg_{ls}g_{rs} + f_{ls}m^{rs + 1} + m^{ls + 1}f_{rs}$$

其中 $ls, rs$ 分别为左右子树大小。状态数看似是 $O(n)$ 的，但是实际上左右两边至少一边是 $2^y - 1$ 的形式，所以对 $f_n$ 有用的状态数实际上是 $O(\log n)$ 的。

转移时如果用快速幂求出系数，就会多出一个 $\log$，但是我们对用到的状态都预处理出 $m^k$ 就可以 $O(\log n)$ 求出 $f_n$。

我们对于每一个 $x$，都 $O(\log n)$ 求出 $F_x$（即当前 $x$ 求出的 $f_n$），就可以 $O(m \log n)$ 求出原本的答案了。

实现时不需要开一个 `unordered_map` 去记忆化搜索，只需要记录所有 $k = 2^y - 1$ 的状态，时间复杂度就是对的。

代码真的很好写：

```cpp
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <cstdio>
#define mod 998244353
#define popc __builtin_popcountll
#define log2 __builtin_ctzll
using namespace std;
const int N = 100001;
typedef long long ll;
int t, n, m, ans[N], sum;ll k;
struct node{int vf, vg, vp;}F[64];
inline void add(int& x, int y){x += y;if (x >= mod) x -= mod;}
node dp(ll x){
	if (!x) return {0, 0, 1};
	if (x == 1) return {m, m, n};x ++;
	if (popc(x) == 1 && F[log2(x)].vp) return F[log2(x)];x --;
	ll ri = 1ll << 64 - __builtin_clzll(x);
	ri --;ll lx = ri - 1 >> 1, rx = lx;
	ll ls = ri - x, di = ri + 1 >> 2;
	if (ls <= di) rx -= ls;
	else rx -= di, lx -= ls - di;
	node lf = dp(lx), rf = dp(rx), res;
	res.vp = 1ll * lf.vp * rf.vp % mod;
	res.vg = (1ll * lf.vg * rf.vp + 1ll * rf.vg * lf.vp + res.vp) % mod * m % mod;
	res.vp = 1ll * res.vp * n % mod;
	res.vf = (1ll * lf.vg * rf.vg % mod * m + res.vg +
	(1ll * lf.vf * rf.vp + 1ll * rf.vf * lf.vp) % mod * n) % mod;
	x ++;if (popc(x) == 1) F[log2(x)] = res;x --;return res;
}
int main(){scanf("%d", &t);
	while (t --){scanf("%lld%d", &k, &n), sum = 0;
		for (m = 1;m <= n;m ++)
		memset(F, 0, sizeof(F)), ans[m] = dp(k).vf;
		for (m = n;m >= 1;m --)
			add(ans[m], mod - ans[m - 1]),
			add(sum, 1ll * ans[m] * m % mod);
		printf("%d\n", sum);
	}
}
```

---

## 作者：nullqtr_pwp (赞：9)

**upd：增加了一些关于解法中式子的解释。**

场上就切到了 B2 然后跑路了。其实这题不用 dp 的捏。

### Statement
给定一颗 $n$ 个节点的完全二叉树，每个点有权值 $a_i \in [1,m]$，定义从 $i$ 到 $j$ 的路径的权值 $s_{i,j}$ 为路径上的最大点权。

求所有树（$m^n$ 种点权）的 $\sum_{i=1}^n \sum_{j=i}^n s_{i,j}$ 的和，模 $998244353$。

$T\leq 200,\sum m\leq 10^5,n\leq 10^{18}$。

### Solution
$\sum m\leq 3\times 10^5$ 提示我们复杂度里面肯定要带 $m$，自然想到枚举最大值 $x$。我们考察最大值 $x$ 会有多少种方案。

只有 $x$ 不好算，加入路径长度 $y$。因为这是一个二叉树，所以 $y$ 是 $O(\log n)$ 的。先不管长为 $y$ 的路径在树中有多少条，这个暂且记成 $k_y$，那么我们发现选定路径上填数的方案数是 $x^y-(x-1)^y$，其余的方案数是 $m^{n-y}$，于是我们可以得出最大值为 $x$ 的贡献是：

$$\sum_{y=1}^{(\max depth)\times 2+1} m^{n-y}(x^y-(x-1)^y)k_yx$$

唯一的难点是求那个 $k_y$。因为这是一个完全二叉树，所以最大深度是 $O(\log n)$ 的。

考察计算有多少条路径长度为 $y$。你考虑计算有多少路径从 $\textrm{lca}$ 的左子树下垂了 $x$ 的长度，右子树下垂了 $y$ 的长度。因为这是一个二叉树，所以 $x,y\leq \log n$，考虑直接枚举 $x,y$，这个可以 $O(1)$ 算。在满二叉树上算这个是简单的。

左子树自由选择的方案数 $lx$ 是 $\max(1,2^{x-1})$，右子树自由选择的方案数 $rx$ 是 $\max(1,2^{y-1})$。原因显然是从各自的第 $2$ 层开始就自由选择左右。你考虑有多少个 $\textrm{lca}$ 可以满足选法是 $lx\times rx$，显然并不是每一个都可以这么取。容易发现，树的高度**减一**为 $dn=\lfloor\log_2n\rfloor$，这样做可以算出叶节点数量，此时非叶节点数量为 $2^{dn}-1$，叶节点数量为 $t=n-2^{dn}+1$。

对最后一层的叶子节点做一些分析，我们考虑从一个叶子节点往上跳到根的过程。这道题中，我们只用考虑从叶子节点 $x_t$ 连续跳多少条右子边之后，就会去跳左子边。按叶子节点的编号顺序考虑为 $x_1,x_2,\cdots ,x_t$，那么会发现从第 $k$ 个叶子节点是连续跳 $\log_2\text{lowbit}(k)$ 条，不会证，手玩出来的。 

利用好完全二叉树的性质，不难发现，满足可以取到 $lx\times rx$ 选法的 $\textrm{lca}$ 的数量是：

$$\left (2^{dn-\max(x,y)}-1\right )+\lfloor\dfrac{n-2^{dn}+1}{2^{\max(x,y)}}\rfloor$$

前者是因为起点可以足够浅，不会走到叶节点那层的 $\text{lca}$ 是这样的，后者是因为在恰好倒数第 $\max(x,y)$ 层可以取一些，可以理解为每 $2^{\max(x,y)}$ 个叶节点就会有一个到达深度倒数 $2^{\max(x,y)}$ 层的。本质上，就是把这层拆成一堆满二叉树。然后这种情况对答案的贡献就是 $lx\times rx$。

然后你计算倒数第 $\max(x,y)$ 层其余点的贡献，也就是说不可以直接左右都自由选择的。依旧是对左右分开相乘，根据 $x,y$ 的大小关系对左右的情况分讨后相乘即可。考虑叶子节点作为路径终点进行计算，此时起点的深度是确定的。

- 对于 $x\ge y$ 的情况：答案应该加上 $\min(2^{x-1},(n-2^{dn}+1)\bmod2^x)$。

- 对于 $x\le y$ 的情况：答案应该加上 $\max(0,((n-2^{dn}+1)\bmod2^y)-2^{y-1})$。

时间复杂度 $O(\sum m\log n+T\log^2 n)$。

### Code
```cpp
int pw[300],n,m,ln,pn;
int Log(int x){
	int rt=0;
	for(;x>1;x>>=1) rt++;
	return rt;
}
int calc(int x,int y){
	if(!x&&!y) return n;
	int u=x?pw[x-1]%mod:1,v=y?pw[y-1]%mod:1;
	int T=u*v%mod,t=(n-pn+1)%pw[max(x,y)];
	mul(T,(pw[ln-max(x,y)]-1)+(n-pn+1)/pw[max(x,y)]);
	T=(T+(x>=y?min(pw[x-1],t)%mod:u)*(y>=x?max(t-pw[y-1],0ll)%mod:v))%mod;
	return T;
}
void solve(){
	n=read(),m=read();
	ln=Log(n),pn=pw[ln];
	int ans=0;
	vector<int>vis((ln+3)<<1,0);
	F(i,0,ln) F(j,0,ln) add(vis[i+j+1],calc(i,j));
	const int im=qpow(m,mod-2),qm=qpow(m,n);
	F(i,1,m){
		int p=1,q=1,tmp=qm,tot=0;
		F(j,1,2*ln+1){
			mul(p,i),mul(q,i-1),mul(tmp,im);
			add(tot,tmp*(p-q+mod)%mod*vis[j]);
		}
		add(ans,tot*i);
	}
	printf("%lld\n",ans);
}
signed main(){
	pw[0]=1;
	F(i,1,60) pw[i]=pw[i-1]<<1;
	int lzm=read();
	wh(lzm) solve();
}

```

---

## 作者：zhaoyp (赞：4)

一种不需要 dp 的方法，效率很快，目前洛谷最优解排名第 $2$，仅次于 Daniel_lele。

------------

首先对于所有长度为 $k$ 的路径，它们期望的 $s$ 值都是相同的，并且可以在 $O(m)$ 的时间内容易求出。

那么我们只需要求出对于所有的 $k$，长度为 $k$ 的路径一共有多少条。

考虑暴力枚举起点与终点二进制表示的位数，分别为 $x,y$，并且他们从高到低至多有 $z$ 位是相同的，那么路径长度就是 $x + y - 2z$。

至于方案数，讨论 $x$ 与 $z$，$y$ 与 $len$ 的大小关系可以 $O(1)$ 算，其中 $len$ 表示 $n$ 二进制表示的位数。具体细节可以参考代码。

时间复杂度 $O(Tm\log n + T\log^3 n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb	push_back
typedef long long ll;
const int maxn = 2e5 + 5;
const int mod = 998244353;
const int inv2 = mod / 2 + 1;
const int inv4 = 1ll * inv2 * inv2 % mod;
ll n,m,len,f[maxn],a[maxn],pw2[maxn],g[maxn],invm,p[maxn],vis[maxn],zyp[maxn];
inline ll read(){
	ll x = 0,f = 1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f * x;
}
ll qpow(ll a,ll b){ll ans=1;while(b){if(b&1)ans=ans*a%mod;a=a*a%mod;b>>=1;}return ans;}
inline void add(ll &x,ll y){x = (x + y) % mod;}
inline ll highbit(ll x){
	for(int i = 61;~i;i--)	if(x & (1ll << i))	return (1ll << i);
	return 0 ;
}
inline ll calc(int x,int y,int z){
	if(y < len)
	{
		ll sum = pw2[z - 1] * pw2[x - z + y - z] % mod;
		if(z < x)	sum = sum * inv2 % mod;
		if(y == x&&z != y)	sum = sum * inv2 % mod;
		return sum;
	}
	else if(y == len&&x == len)
	{
		if(z == y)	return g[z];
		ll sum = (g[z] - 1) * pw2[x - z] % mod * pw2[y - z] % mod;
		if(z < x)	sum = sum * inv4 % mod;
		if(a[len - z] == 0)	return sum;
		ll res = pw2[x - z - 1] * vis[len - z - 1] % mod;
		add(sum,res);
		return sum;
	}
	else if(y <= len&&x < len)
	{
		ll sum = (g[z] - 1) * pw2[x - z] % mod * pw2[y - z] % mod;
		if(z < x)	sum = sum * inv2 % mod;
		ll res = (x == z) ? vis[len - z] : pw2[x - z - 1] * vis[len - z] % mod;
		add(sum,res);
		return sum;
	}
	return -1;
}
inline ll solve(int k){
	for(int i = 1;i <= m + 1;i++)	p[i] = 0,zyp[i] = zyp[i] * (i - 1) % mod * invm % mod;
	ll ans = 0;
	for(int i = m;i;i--)	p[i] = 1 - zyp[i];
	for(int i = 1;i <= m;i++)	add(p[i],-p[i + 1]),add(ans,p[i] * i);
	return ans % mod;
}
int main()
{
	pw2[0] = 1;
	for(int i = 1;i <= 1000;i++)	pw2[i] = pw2[i - 1] * 2 % mod;
	int T = read();
	while(T--)
	{
		n = read(),m = read();
		invm = qpow(m,mod - 2),len = 0;
		ll x = n;
		while(x)	a[++len] = x & 1,x >>= 1;
		g[len] = n;
		for(int i = len - 1;i;i--)	g[i] = g[i + 1] / 2;
		for(int i = 1;i <= len;i++)	g[i] = g[i] - highbit(g[i]) + 1;
		for(int i = 0;i <= len;i++)	vis[i] = (((1ll << i) - 1) & n) + 1,vis[i] %= mod;
		for(int i = 1;i <= len;i++)	for(int j = i;j <= len;j++)	for(int z = 1;z <= i;z++)	
			add(f[i + j - 2 * z + 1],calc(i,j,z)); 
		ll ans = 0;
		for(int i = 1;i <= m;i++)	zyp[i] = 1;
		for(int i = 1;i <= 120;i++)	
			add(ans,solve(i) * f[i]),f[i] = 0;
		ans = ans * qpow(m,n) % mod;
		printf("%lld\n",(ans % mod + mod) % mod);
	}
	return 0 ;
}
```

---

## 作者：Huasushis (赞：3)

## CF1868C

[题目链接](https://codeforces.com/problemset/problem/1868/C)。

我的代码跑得很快，139ms，全开 `__int128` 时间都才 $1.2s$（你猜猜我为什么要全开 __int128，因为写的时候有个地方乘法溢出了），如果再减少一下取模的数量应该可以更快。时间复杂度 $\mathrm{O}(T \log^2 n + Tm\log n)$。

具体怎么做呢？首先对于一条链，枚举最大值 $y$，长度（点数）为 $x$，那么贡献就是 $(y^x-(y - 1)^x)\times y \times m^{n - x}$。然后枚举最大值和长度。我们容易发现链的不同长度数量是 $\text{O}(\log n)$ 的，我们要求得每种长度的链的数量，然后和上面的贡献乘起来求和就行。那么我们怎么去求数量呢？我们考虑枚举一条链，从 lca 往两个儿子两边的长度是多少，会发现对于上面几层，对应的都是满二叉树，直接计算，需要特别计算的就是二叉树最下面一层的，特殊处理一下就可以。具体实现请看代码，要预处理一下幂。

```cpp
#include <bits/stdc++.h>
using namespace std;
char *p1, *p2, buf[5000000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,5000000,stdin),p1==p2)?EOF:*p1++)
#define read(x) {x=0;int ch;while(!isdigit(ch=nc()));do x=x*10+(ch^48);while(isdigit(ch=nc()));}
template<typename T>
void write(T x) {
  if (x >= 10) write(x / 10);
  putchar((x % 10) ^ 48);
}
int t;
using ll = long long;
ll n;
int m;
#define mod 998244353ll
ll qp(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % mod;
    y >>= 1;
    x = x * x % mod;
  }
  return ans;
}
ll gs[128];
#define N 100010
ll mi[N][128], jm[128];
signed main() {
  read(t);
  while (t--) {
    read(n) read(m)
    int cs = __lg(n), mc = cs; //总层数（从零开始），满二叉树层数
    if (__builtin_popcountll(n + 1) != 1) --mc;
    ll ans = 0;
    int mlen = cs * 2ll + 1;
    if (n != 1 && !(n & (n - 1))) --mlen; //最长链的长度
    for (int j = 1; j <= mlen; ++j) { //处理出每种长度的链的个树
      gs[j] = 0;
      for (int k = max(j - 1 - cs, 0); k * 2 <= j - 1; ++k) {
        int l = j - 1 - k; //k, l 代表两端垂下的长度
        ll tmp, tt;
        //注意这里可能会爆 long long
        tt = (__int128(1) << (max(k - 1, 0) + max(l - 1, 0) + (k != l))) % mod; //每个顶点有多少种选择
        if (mc < l) goto nxt;
        tmp = (1ll << (mc - l + 1)) - 1; //满的顶点数
        tmp %= mod;
        gs[j] += tmp * tt % mod;
        nxt:
        if (cs != mc) { //如果不是满二叉树
          ll rest = n - (1ll << cs) + 1;
          gs[j] += (rest / (1ll << l)) % mod * tt % mod; //先处理满的顶点
          rest %= (1ll << l);
          ll zuo = min(rest, 1ll << max(0, l - 1));
          ll you = rest - zuo;
          zuo %= mod, you %= mod; //最后一个是不满的，把左右两边最下面一层的叶子个数求出来
          if (k < l) { //如果两端深度不一样
            tt = zuo * ((1ll << max(k - 1, 0)) % mod) % mod + you * ((1ll << max(k - 1, 0)) % mod) % mod;
            tt %= mod;
            gs[j] += tt;
          } else { //两端深度一样，即都在叶子节点
            tt = zuo * you % mod;
            gs[j] += tt;
          }
        }
      }
      gs[j] %= mod;
    }
    for (ll i = 1; i <= m; ++i) { //预处理幂，其实可以放在外面，可能更快。
      mi[i][0] = 1;
      for (int j = 1; j <= mlen; ++j) {
        mi[i][j] = mi[i][j - 1] * i % mod;
      }
    }
    jm[mlen] = qp(m, (n - mlen) % (mod - 1));
    for (int j = mlen - 1; j; --j) {
      jm[j] = jm[j + 1] * m % mod;
    }
    for (ll i = 1; i <= m; ++i) {
      for (int j = 1; j <= mlen; ++j) {
        auto val = (mi[i][j] - mi[i - 1][j] + mod) * i % mod * jm[j] % mod;
        ans += gs[j] * val % mod; //数量乘贡献
      }
    }
    ans %= mod;
    write(ans);
    putchar('\n');
  }
  return 0;
}
```

---

## 作者：DerrickLo (赞：1)

我们考虑统计有多少种点权与 $(i,j)$ 使得 $s_{i,j}\le k$，我们发现对于 $i$ 到 $j$ 路径上的点的点权只能为 $1\sim k$，而其他点的点权可以为 $1\sim m$，所以一共的个数就是 $\displaystyle{\sum_{i=1}^{n}\sum_{j=i}^{n}k^{\operatorname{dis}(i,j)}\times m^{n-\operatorname{dis}(i,j)}}$ 整理一下得 $\displaystyle{m^n\sum_{i=1}^{n}\sum_{j=i}^{n}(\frac{k}{m})^{\operatorname{dis}(i,j)}}$，注意到 $\operatorname{dis}(i,j)$ 是 $\log n$ 级别的，所以我们只需要对于每个 $x$，求出 $\operatorname{dis}(i,j)=x$ 的 $(i,j)$ 的个数。

然后我们先预处理出 $f_{i,j}$ 表示深度为 $i$ 的满二叉树中距离为 $j$ 的点对个数，然后我们发现对于一颗完全二叉树，根的左右儿子必然有至少一个满二叉树，而这部分我们已经预处理出来了，所以只需要去递归另外一个儿子即可。这样只需要递归 $\log n$ 次，我们就能求出对于大小为 $n$ 的完全二叉树的答案了。

时间复杂度 $\mathcal O(m\log n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int t,n,m,ans[200005];
struct nd{
	int a[205],b[205];
}f[205];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
int check(int u,int n){
	int now1=u,now2=u,flag=1,dep1=0,dep2=0; 
	while(now1<=n){
		dep1++;
		if((now1<<1)<=n)now1=now1<<1;
		else if((now1<<1|1)<=n)now1=now1<<1|1,flag=0;
		else break;
	}
	while(now2<=n){
		dep2++;
		if((now2<<1|1)<=n)now2=now2<<1|1;
		else if((now2<<1)<=n)now2=now2<<1,flag=0;
		else break;
	}
	if(!flag)return 0;
	if(dep1!=dep2)return 0;
	return dep1;
}
nd dfs(int u,int n){
	nd a,b,ans;
	memset(a.a,0,sizeof a.a),memset(a.b,0,sizeof a.b);
	memset(b.a,0,sizeof b.a),memset(b.b,0,sizeof b.b);
	memset(ans.a,0,sizeof ans.a),memset(ans.b,0,sizeof ans.b);
	if((u<<1)<=n){
		int dep=check(u<<1,n);
		if(!dep)a=dfs(u<<1,n);
		else a=f[dep];
	}
	if((u<<1|1)<=n){
		int dep=check(u<<1|1,n);
		if(!dep)b=dfs(u<<1|1,n);
		else b=f[dep];
	}
	ans.b[0]=1;
	for(int j=1;j<=200;j++)ans.b[j]=a.b[j-1]+b.b[j-1],ans.b[j]%=mod;
	for(int j=0;j<=200;j++)ans.a[j]=ans.b[j];
	for(int j=0;j<=200;j++)ans.a[j]+=a.a[j]+b.a[j],ans.a[j]%=mod;
	for(int j=0;j<=200;j++)for(int k=0;k<=200;k++)ans.a[j+k+2]+=a.b[j]*b.b[k]%mod,ans.a[j+k+2]%=mod; 
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t,f[1].a[0]=f[1].b[0]=1;
	for(int i=2;i<=200;i++){
		f[i].b[0]=1;
		for(int j=1;j<=200;j++)f[i].b[j]=f[i-1].b[j-1]*2,f[i].b[j]%=mod;
		for(int j=0;j<=200;j++)f[i].a[j]=f[i].b[j];
		for(int j=0;j<=200;j++)f[i].a[j]+=f[i-1].a[j]*2,f[i].a[j]%=mod;
		for(int j=0;j<=200;j++)for(int k=0;k<=200;k++)f[i].a[j+k+2]+=f[i-1].b[j]*f[i-1].b[k]%mod,f[i].a[j+k+2]%=mod; 
	}
	while(t--){
		cin>>n>>m;
		nd now=dfs(1,n);
		for(int i=1;i<=m;i++)ans[i]=0;
		for(int i=1;i<=m;i++){
			int x=1,a=ksm(m,n),b=i*ksm(m,mod-2)%mod;
			for(int j=1;j<=200;j++){
				x*=b,x%=mod;
				ans[i]+=x*now.a[j-1]%mod*a%mod,ans[i]%=mod;
			}
		}
		int cnt=0;
		for(int i=1;i<=200;i++)cnt+=now.a[i-1],cnt%=mod;
		for(int i=m;i;i--)ans[i]-=ans[i-1],ans[i]+=mod,ans[i]%=mod;
		int anss=0;
		for(int i=1;i<=m;i++)anss+=ans[i]*i%mod,anss%=mod;
		cout<<anss<<"\n";
	}
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

为啥我 C++20 就过了？

神题。

对于求 $max=x$ 的方案数，有一个经典 trick 是容斥变为求 $max\leq x$ 的方案数减去 $max\leq x-1$ 的方案数。

我们令 $f_{u,i}$ 表示大小为 $u$ 的子树内，$max=i$ 的链的方案数，$g_{u,i}$ 表示大小为 $u$ 的子树内，$max=i$ 且一端为根的链的方案数。

$$g_{u,i}=i\times(g_{l,i}\times m^r+g_{r,i}\times m^l+m^{u-1})$$

$$f_{u,i}=g_{u,i}+g_{l,i}\times g_{r,i}\times i+f_{l,i}\times m^{r+1}+f_{r,i}\times m^{l+1}$$

注意到树的形态是一棵完全二叉树，而完全二叉树可以被分成 $O(\log n)$ 棵满二叉树，所以我们令 $f_{u,i}$ 和 $g_{u,i}$ 表示大小为 $2^u-1$ 的子树的答案。空间复杂度就降到了 $O(\log n)$。

我们分别对每个 $i$ 做一遍 dp，最后答案为 $\sum\limits_{i=1}^m i\times (f_{n,i}-f_{n,i-1})$。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=100005;
const int Mod=998244353;
struct node{
    LL f,g,Pow;
}a[64];
int _;
LL n;
int m;
LL ans[N];
int vis[64];
int popcnt(LL x){
    int ans=0;
    for(LL i=x;i;i-=(i&(-i))) ans++;
    return ans;
}
int Log(LL x){
    int ans=0;
    for(int i=0;i<=60;i++) if((1ll<<i)>=x) return i;
}
node dfs(LL siz,int x){
    if(!siz) return (node){0,0,1};
    if(siz==1) return vis[1]=1,a[1]=(node){x,x,m};
    int dep=Log(siz+1),bit=popcnt(siz+1);
    if(bit==1&&vis[dep]) return a[dep];
    LL sizl,sizr;
    sizl=sizr=(1ll<<dep-2)-1;
    LL rst=siz-1-sizl-sizr;
    if(rst>=(1ll<<dep-2)) sizl+=(1ll<<dep-2),sizr+=rst-(1ll<<dep-2);
    else sizl+=rst;
    node lans=dfs(sizl,x),rans=dfs(sizr,x);
    node ans;
    ans.Pow=lans.Pow*rans.Pow%Mod;
    ans.g=(lans.g*rans.Pow+rans.g*lans.Pow+ans.Pow)%Mod*x%Mod;
    ans.f=(ans.g+lans.g*rans.g%Mod*x+(lans.f*rans.Pow+rans.f*lans.Pow)%Mod*m)%Mod;
    ans.Pow=ans.Pow*m%Mod;
    if(bit==1) a[dep]=ans,vis[dep]=1;
    return ans;
}
int main(){
    scanf("%d",&_);
    while(_--){
        scanf("%lld%d",&n,&m);
        for(int i=1;i<=m;i++){
            memset(a,0,sizeof(a)),memset(vis,0,sizeof(vis));
            ans[i]=dfs(n,i).f;
        }
        LL res=0;
        for(int i=m;i>=1;i--) ans[i]=(ans[i]-ans[i-1]+Mod)%Mod,res=(res+ans[i]*i%Mod)%Mod;
        printf("%lld\n",res);
    }
    return 0;
}

```

---

## 作者：BINYU (赞：1)

## 题意

给定一棵点数为 $n$ 的完全二叉树，点有点权，值域为 $[1,m]$，定义一条简单路径的权值为上面所有点的权值的最大值，求所有可能的树的所有简单路径的权值和。

## 思路

发现所有长度相同的简单路径的权值可能情况相同，且最长的简单路径长度为   $O(\log n)$ 级别，考虑维护所有长度的简单路径在一棵树上出现的次数，每种简单路径的权值在所有树上出现的次数，相乘即使答案。

先考虑第一个问题：所有长度的简单路径在一棵树上出现的次数。

定义一条简单路径的长度为其上的**点数**。

考虑把一条简单路径拆成两个点到他们最近公共祖先的两条链，记 ${dp} _ {i,j}$ 表示在以 $i$ 为根的子树内长度为 $j$ 的简单路径个数，$f_{i,j}$ 表示深度最小的节点为 $i$ 且长度为 $j$ 的简单路径个数，$g_{i,j}$ 表示以 $i$ 为根的子树内深度为 $j$ 的节点个数，为方便 $f$ 的转移，我们将$g_{i,0}$ 设为 $1$。

则转移为：

$$g_{i,j} = \begin{cases}1 & j \le 1\\
         g_{ls,j-1} + g_{rs,j-1} & j > 1 \end{cases}$$

$$f_{i,j} = \sum\limits_{k=0}^{j-1}{(g_{ls,k}\times g_{rs,j-k-1})}$$

$${dp}_ {i,j} = {dp}_ {ls,j} + {dp}_ {rs,j} + f_{i,j}$$

时空都不够，考虑优化。

可以发现，一棵完全二叉树去除根节点后可以拆成一棵满二叉树和一棵完全二叉树，知道当前根没有右儿子。总共会拆成 $O(\log n)$ 级别的满二叉树，考虑维护满二叉树的值，重新定义 ${dp} _ {i,j}$ 表示在深度为 $i$ 的满二叉树内长度为 $j$ 的简单路径个数，$f_{i,j}$ 表示深度为 $i$ 的满二叉树内包含根节点且长度为 $j$（可为 $0$）的简单路径个数，$g_{i,j}$ 表示深度为 $i$ 的满二叉树内深度为 $j$ 的点的个数，同上，将 $g_{i,0}$ 设为 $1$。

则对于满二叉树的转移为：

$$g_{i,j} = \begin{cases}1 & j \le 1\\
         2 \times g_{i,j - 1} & j > 1 \end{cases}$$

$$f_{i,j} = \sum\limits_{k=0}^{j-1}{(g_{i - 1,k}\times g_{i - 1,j-k-1})}$$

$${dp}_ {i,j} = 2 \times {dp}_ {i - 1,j} + f_{i,j}$$

对于满二叉树，可以对于所有 $n$ 统一预处理，在合并成完全二叉树的过程中，使用上面的公式即可，时间复杂度 $O(\log^3 n)$。

接下来考虑第二个问题：每种简单路径的权值在所有树上出现的次数。

考虑容斥，设 ${dp}_ {i,j}$ 表示在一条长度为 $i$ 的简单路径最大值为 $j$ 的出现次数， $f_ {i,j}$ 表示在一条长度为 $i$ 的简单路径最大值小于等于 $j$ 的出现次数。

则对于 $f_{i,j}$，在路径上的点，每种点有 $j$ 种权值选择的方案，在路径外的点，每种点有 $m$ 种选择方案，即：

$$f_{i,j} = m^{n-i}\times j^i$$

$$\begin{aligned}{dp}_ {i,j} & = f_{i,j} - f_{i,j-1}\\
   & = m^{n-i}(j^i-(j-1)^i)\end{aligned}$$

时间复杂度 $O(m\log n)$

总时间复杂的 $O(\log^3 n+m\log n)$，可过。

---

## 作者：Unnamed114514 (赞：0)

容易想到拆贡献，然后我们把 $(u,v)$ 的贡献放到 $LCA$ 上来算。

容易发现本质不同的子树最多只有 $O(\log n)$ 个，具体地，考虑对最后一层进行二进制拆分，然后就能得到 $O(\log n)$ 棵满二叉树，每棵最多有一个和它不同的兄弟。

然后我们定义 $f(n,m)$ 表示 $n$ 个点的子树，钦定的最大值是 $m$ 的方案数。

容易手玩得到左右儿子的大小 $L,R$。首先左右儿子内部的路径递归处理，然后我们只需要考虑经过 $1$ 的路径。

我们枚举 $i,j$ 表示 $1$ 向左右延伸了多少，定义 $h(n,d)$ 表示 $n$ 个节点的完全二叉树，深度为 $d$ 的点的数量（$dep_1=0$），有：

$$f(n,m)=\sum\limits_{i=0}^{\lfloor\log_2 n\rfloor}\sum\limits_{j=0}^{\lfloor\log_2 n\rfloor}=h(L,i)h(R,j)(m^{i+j+1}-(m-1)^{i+j+1})M^{N-(i+j+1)}$$

（变量冲突了，这里的 $N,M$ 是题目中的 $n,m$。）

首先 $M^{N-(i+j+1)}=\dfrac{M^N}{M^{i+j+1}}$，因此我们可以 $O(\sum m\log n)$ 地把所有的指数处理出来。

然后这个做法是 $O(\sum m\log^3 n)$ 的，但是注意到 $i,j$ 独立，于是拆括号，把 $i,j$ 分别提出来，这样就能做到 $O(\sum m\log^2 n)$。

然后你会发现除了最后一层前面都是满的，因此我们可以初始化，最后一层的单独加上，时间复杂度 $O(\sum m\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mod=998244353;
int T,N,M,p[100005][200],inv[100005][200],pw,dp[100][100005],sum[100][100005];
int h(int n,int d){
	if(n>(1LL<<d+1)-1) return 1LL<<d;
	return n-((1LL<<d)-1);
}
int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod,b>>=1;
	}
	return s;
}
int f(int n,int m){
	if(n==1) return pw*inv[M][1]%mod;
	if(n==2) return (2*pw*inv[M][1]+(m*m-(m-1)*(m-1))%mod*pw%mod*inv[M][2])%mod;
	int k=__lg(n);
	int rest=n-((1LL<<k)-1),L,R;
	if(n==(1LL<<k+1)-1&&~dp[k][m]) return dp[k][m];
	if(rest<=(1LL<<k-1)) L=(n-rest-1)/2+rest,R=(n-rest-1)/2;
	else L=(n-rest-1)/2+(1LL<<k-1),R=(n-rest-1)/2+rest-(1LL<<k-1);
	int s1=((!k?0:sum[k-1][m])+(!k?1:h(L,k-1))%mod*p[m][k]%mod*inv[M][k])%mod,s2=((!k?0:sum[k-1][m-1])+(!k?1:h(L,k-1))%mod*p[m-1][k]%mod*inv[M][k])%mod;
	int s3=((!k?0:sum[k-1][m])+(!k?1:h(R,k-1))%mod*p[m][k]%mod*inv[M][k])%mod,s4=((!k?0:sum[k-1][m-1])+(!k?1:h(R,k-1))%mod*p[m-1][k]%mod*inv[M][k])%mod;
	int ans=(f(L,m)+f(R,m)+((s1*s3%mod*inv[M][1]%mod*pw%mod*m-s2*s4%mod*inv[M][1]%mod*pw%mod*(m-1))%mod+mod)%mod)%mod;
	if(n==(1LL<<k+1)-1) dp[k][m]=ans;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=0;i<=1e5;++i){
		p[i][0]=inv[i][0]=1;
		int INV=qpow(i,mod-2);
		for(int j=1;j<=150;++j) p[i][j]=1LL*p[i][j-1]*i%mod,inv[i][j]=1LL*inv[i][j-1]*INV%mod;
	}
	cin>>T;
	while(T--){
		cin>>N>>M;
		int ans=0;
		pw=qpow(M,N);
		for(int j=0;j<=M;++j) sum[0][j]=1;
		for(int i=1;i<=__lg(N)+1;++i){
			for(int j=1;j<=M;++j) dp[i][j]=-1;
			for(int j=0;j<=M;++j) sum[i][j]=(sum[i-1][j]+(1LL<<i-1)%mod*p[j][i]%mod*inv[M][i])%mod;
		}
		for(int i=1;i<=M;++i) ans=(ans+1LL*i*f(N,i))%mod;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：irris (赞：0)

+ 显然这是一棵 **完全二叉树**。
+ [扣扣莉的一道题](https://www.luogu.com.cn/problem/P8089) 告诉我，这种东西是可以转换为 $\mathcal O(\log n)$ 个 **满二叉树** 的。
+ 考虑树形 dp，但是压缩状态。
+ 首先，朴素的树形 dp 会设 $f_i$ 表示在路径两端点均为 $i$ 个节点子树内节点的答案和，$g_{i,j}$ 表示 $i$ 子树内所有节点到它自己的路径上点权 max 为 $j$ 的方案数。最简单的转移为：

$$f_i = f_L \color{red}{\times m^{sz_R + 1}}\color{black} + f_R\color{red}{\times m^{sz_L + 1}}\color{black} + \sum_{j=1}^m \sum_{k=1}^m \sum_{l=1}^m (g_{L,k}\times g_{R,l})\times \max(j,k,l) + \sum_{j=1}^m g_{i,j}\times j$$

$$g_{i,j} = (j - 1)(g_{L,j}\color{red}{\times m^{sz_R }}\color{black} + g_{R,j}\color{red}{\times m^{sz_L}}\color{black}) + \sum_{k=1}^j (g_{L,k}\color{red}{\times m^{sz_R}}\color{black} + g_{R,k}\color{red}{\times m^{sz_L}}\color{black}) + \color{red}{m^{sz_L + sz_R}}$$

+ $g$ 的转移不在瓶颈上，考虑优化一下 $f$ 的那个三个数取 max 的计算形式。
+ 计数 $\max = i$ 可以改写为计数 $(\max \leq i) - (\max \leq i - 1)$，因此只需计算 $\max \leq i$ 的形式，就可以转化为（记 $p_s = \displaystyle s\times (\sum_{i=1}^s g_{L,i}) \times (\sum_{j=1}^s g_{R,j})$）：

$$f_i = f_L \color{red}{\times m^{sz_R + 1}}\color{black} + f_R\color{red}{\times m^{sz_L + 1}}\color{black} + \sum_{j=1}^m (p_j - p_{j-1} + g_{i,j})\times j$$

+ 这样，两个的转移都是 $\mathcal O(m)$ 了。所以考虑压缩状态，容易把原树拆成 $\mathcal O(\log n)$ 个满二叉树，可以先对满二叉树大小倍增而 dp，所以只需要记录 $\mathcal O(\log n)$ 个状态。
+ 请注意上文中的红色公式，这些是由于仅考虑了其中一些点的贡献而未考虑另外一些导致另外可以任选的方案数。
+ 时间复杂度 $\mathcal O(n\log^2 m)$，一个 $\log$ 来源于递归和倍增，另一个 $\log$ 来源于计算大小为 $n$ 的完全二叉树的左子树大小（我的实现，额我不会位运算。难过）。
+ **注意实现**。

## Code

```cpp
#include <bits/stdc++.h>
 
namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
};
using namespace FastIO;
 
constexpr int MOD = 998244353;
inline void add(int& x, int y) { (x += y) >= MOD && (x -= MOD); }
inline void del(int& x, int y) { (x -= y) < 0 && (x += MOD); }
inline int sum(int x, int y) { return (x += y) < MOD ? x : x - MOD; }
inline int dec(int x, int y) { return (x -= y) < 0 ? x + MOD : x; }
inline int qpow(long long a, long long x) { long long ans = 1; a %= MOD; while (x) (x & 1) && (ans = ans * a % MOD), a = a * a % MOD, x >>= 1; return ans; }
inline long long Lsz(long long n) {
	long long lb = 2, rb = 2, ans = 0;
	while (lb <= n) ans += std::min(n, rb) - lb + 1, lb <<= 1, rb = (rb << 1) | 1;
	return ans;
}
std::map<long long, int> id;
 
const int V = 61;
#define MAXM 100001
int f[V << 1], g[V << 1][MAXM], cnt = V;
void getDP(int M, int mL, int mR, int &fpos, int &fL, int &fR, int gpos[], int gL[], int gR[]) {
	std::vector<int> SgL(M + 1, 0), SgR(M + 1, 0), p(M + 1, 0);
	for (int i = 1; i <= M; ++i) SgL[i] = sum(SgL[i - 1], gL[i]), SgR[i] = sum(SgR[i - 1], gR[i]);
	for (int i = 1; i <= M; ++i) p[i] = (long long)i * SgL[i] % MOD * SgR[i] % MOD;
	for (int i = 1; i <= M; ++i) SgL[i] = (long long)SgL[i] * mR % MOD, SgR[i] = (long long)SgR[i] * mL % MOD;
	for (int i = 1; i <= M; ++i) gpos[i] = sum(sum((long long)(i - 1) * sum((long long)gL[i] * mR % MOD, (long long)gR[i] * mL % MOD) % MOD, sum(SgL[i], SgR[i])), (long long)mL * mR % MOD);
	fpos = (long long)M * sum((long long)mR * fL % MOD, (long long)mL * fR % MOD) % MOD;
	for (int i = 1; i <= M; ++i) add(fpos, (long long)i * sum(dec(p[i], p[i - 1]), gpos[i]) % MOD);
}
void solve(long long n, int m) {
	if (id.count(n)) return;
	long long lc = Lsz(n), rc = n - lc - 1;
	solve(lc, m), solve(rc, m);
	int p = id[lc], q = id[rc];
	id[n] = ++cnt, getDP(m, qpow(m, lc), qpow(m, rc), f[cnt], f[p], f[q], g[cnt], g[p], g[q]);
}
void debug(long long n, int m) {
	long long lc = Lsz(n), rc = n - Lsz(n) - 1;
	printf("debug %lld %d %lld %lld\n", n, m, lc, rc);
	if (!id.count(n)) { printf("no such id!\n"); return; }
	printf("f = %d\n", f[id[n]]);
	for (int i = 1; i <= m; ++i) printf("g[%d] = %d\n", i, g[id[n]][i]);
}
void solve() {
	long long N = read<long long>(); int M = read<int>(); cnt = V, id.clear(), id[0] = 0;
	for (int i = 1; i <= V; ++i) getDP(M, qpow(M, (1ll << i - 1) - 1), qpow(M, (1ll << i - 1) - 1), f[i], f[i - 1], f[i - 1], g[i], g[i - 1], g[i - 1]), id[(1ll << i) - 1] = i;
	solve(N, M), print<int>(f[id[N]], '\n');
}
 
int main() {
	int T = read<int>(); while (T--) solve(); return 0;
}
```

---

