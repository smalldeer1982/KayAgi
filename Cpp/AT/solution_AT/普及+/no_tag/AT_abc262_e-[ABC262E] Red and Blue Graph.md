# [ABC262E] Red and Blue Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc262/tasks/abc262_e

$ N $ 頂点 $ M $ 辺の単純無向グラフが与えられます。頂点は $ 1,\ \dots,\ N $ と番号付けられ、$ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 番目の辺は頂点 $ U_i,\ V_i $ を結んでいます。

それぞれの頂点を赤または青で塗る方法は全部で $ 2^N $ 通りあります。これらのうち、以下の条件を全て満たすものの総数を $ 998244353 $ で割った余りを求めてください。

- 赤く塗られた頂点がちょうど $ K $ 個ある
- 異なる色で塗られた頂点を結ぶ辺の本数は偶数である

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ U_i\ \lt\ V_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ (U_i,\ V_i)\ \neq\ (U_j,\ V_j)\ \,\ (i\ \neq\ j) $
- 入力は全て整数

### Sample Explanation 1

以下の $ 2 $ 通りが条件を満たします。 - 頂点 $ 1,\ 2 $ を赤く、頂点 $ 3,\ 4 $ を青く塗る。 - 頂点 $ 3,\ 4 $ を赤く、頂点 $ 1,\ 2 $ を青く塗る。 上記の塗り方について、異なる色で塗られた頂点を結ぶ辺は $ 2 $ 番目の辺と $ 3 $ 番目の辺です。

## 样例 #1

### 输入

```
4 4 2
1 2
1 3
2 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
10 10 3
1 2
2 4
1 5
3 6
3 9
4 10
7 8
9 10
5 9
3 4```

### 输出

```
64```

# 题解

## 作者：MrcFrst (赞：7)

**[原题传送门](https://atcoder.jp/contests/abc262/tasks/abc262_e)**

感觉是一道不是很难想到但还是比较不错的题。

题目要求将k个点染成红色，那么我们不妨首先将所有点视为蓝色，然后一个一个地将红点加进去。
那么就从简单的入手，考虑最初只加入一个红点，那么显然满足要求的边的数量就是这个红色点的度数。

然后考虑再加进去一个红色点，此时满足要求的边的数量还是会加上它的度数，但是显然会出问题：如果这两个红色点之前有边相连，那么它们之间的那条边就是不合法的，我们不应该统计它。

于是此题的重头戏就来了：这条不合法的边我们把它算了两次（加第一个点和第二个点的时候都统计了它），但是，**我们把这两次减掉，不影响合法边数量的奇偶性。**
所以就直接不用管它了。
再继续往里面加红色点也是同样的道理，每条边只要不合法就说明它连接了两个红色点，那么我们会把它统计两次，但实际上不影响奇偶性，所以可以直接不管。

于是此题就变得很简单了：从图中选出k个点使得度数之和为偶数。

然后我们考虑把所有点按照度数的奇偶性分类统计数量，然后度数为偶数的点加进去对总数的奇偶性没有任何影响，所以可以直接在度数为奇数的点中选出偶数个，其余的选择度数为偶数的点，两种分别求组合数然后用乘法原理统计起来就能得到答案了。

```cpp
//MrcFrst_LRY 
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define int long long
const int N=200200,mod=998244353;
int n,ans,m,k,d[N],cnt[2],inv[N],invfac[N],fac[N];
inline int read(){
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
il int C(int n,int m){
	if(n<m)return 0;
	return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}//组合数
il void get_inv(){
	fac[0]=invfac[0]=inv[1]=invfac[1]=fac[1]=1;
	for(re int i=2;i<=n;i++){
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
		fac[i]=fac[i-1]*i%mod;
		invfac[i]=invfac[i-1]*inv[i]%mod;
	}
}//为计算组合数预处理逆元
signed main(){
	n=read(),m=read(),k=read();
	for(re int i=1;i<=m;i++){
		int u=read(),v=read();
		d[u]++,d[v]++;//统计度数
	}
	get_inv();
	for(re int i=1;i<=n;i++)cnt[d[i]&1]++;//按度数的奇偶性将点分类统计数量
	for(re int i=0;i<=k;i+=2)
		(ans+=(C(cnt[1],i)*C(cnt[0],k-i))%mod)%=mod;
	cout<<ans;
    return 0;
}
```


---

## 作者：FFTotoro (赞：6)

赛后一分钟做出这道题目……差点崩溃……

本题解题关键点在于：

需要让偶数条边连接的两个点颜色不相同，就只能将偶数个度为奇数的点。因为，每增加一个点，如果这个点的度为奇数，那么整个图“连接的两个点颜色不相同的边”就会增加或减少奇数条。

然后再套逆元求组合数即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
vector<int> g[200001];
int f[200001]={1,1};
int qpow(int a,int b){
    int r=1;
    while(b){
        if(b&1)r=r%mod*a%mod;
        a=a%mod*a%mod; b>>=1;
    }
    return r;
}
int inv(int a,int b){return a%mod*qpow(b,mod-2)%mod;}
int com(int n,int m){return m?inv(f[n],f[m]*f[n-m]%mod):1;}
signed main(){
    ios::sync_with_stdio(false);
    int n,m,k,c=0,s=0; cin>>n>>m>>k;
    for(int i=2;i<=n;i++)f[i]=f[i-1]*i%mod;
    for(int i=1;i<=m;i++){
        int u,v; cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)c+=g[i].size()&1; // 统计度为奇数的点的个数
    for(int i=0;i<=min(c,k);i+=2)if(k-i<=n-c)(s+=com(c,i)*com(n-c,k-i))%=mod; // 枚举数量，用组合数求解
    cout<<s<<endl;
    return 0;
}
```


---

## 作者：Register_int (赞：3)

好题，好题。

首先有个 naive 的想法：点亮一个红点时，与他相邻的所有边都会变成两端颜色不同的边，那么边数就是他们的度数之和。

但随便都能看出问题来。当两个红点相邻时，边数不仅不会增加，还会倒扣一条！设这 $k$ 个红点的度数为 $d_i$，相邻红点的个数为 $x'$。由于每当出现一对红点，就会少掉两条端颜色不同的边，所以得到边数为 $\sum_id_i-2x'$。

发现了吗？由于减去的是个偶数，所以度数和与边数**奇偶性相同**！

直接枚举选多少个度数为奇数的点，再用乘法原理计算即可。时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	ll ans = fac[n] * ifac[m] % mod * ifac[n - m] % mod;
	return ans;
}

int n, m, k, d[MAXN], x, y;

ll ans;

int main() {
	scanf("%d%d%d", &n, &m, &k), init(n);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), d[u]++, d[v]++;
	for (int i = 1; i <= n; i++) x += d[i] & 1, y += ~d[i] & 1;
	for (int i = 0; i <= k; i += 2) ans = (ans + c(x, i) * c(y, k - i) % mod) % mod;
	printf("%lld", ans);
}
```

---

## 作者：Zikake (赞：3)

# 题意
有一张 $n$ 个点，$m$ 条边的无向图，将每一个点都被涂成红或蓝，而且恰好要染红 $k$ 个点，使得一条边的两端的点不同色的边的数为偶数，求出方案数，并模 $998244353$。

# 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/2rby17qe.png)

我们先将所有点看成蓝色的。

![](https://cdn.luogu.com.cn/upload/image_hosting/asg388uh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


那么已知偶数加偶数等于偶数，奇数加奇数等于偶数。我们就可以选择度数为奇数的点，度数的话，就是这个点的出度和入度。因为你染一个度数为偶数的点，你的答案数会增加偶数个方案，而你去染一个度数为奇数的点，你的答案会增加奇数个方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/l14yn3df.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们只需要在度数为奇数的点中选偶数个点，这题就是一道组合数学。组合的公式。$C_{m}^{n}=\frac{n!}{m!\times \left(n-m\right)!}$。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=998244353;
int n,m,k,ans,cnt[N],sum[N];
int fac[N],invfac[N],inv[N];
int C(int n,int m){
	return fac[n]%mod*invfac[m]%mod*invfac[n-m]%mod;//公式求解看下面 
}
void get_inv(){
	fac[0]=invfac[0]=inv[1]=invfac[1]=fac[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;//逆元 
		fac[i]=fac[i-1]*i%mod;//阶乘 
		invfac[i]=invfac[i-1]*inv[i]%mod;//阶乘逆元
	}
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		cnt[u]++;cnt[v]++;//统计度数 
	} 
	get_inv();//需要用到逆元 
	for(int i=1;i<=n;i++){
		sum[cnt[i]%2]++;//将度数为偶数或奇数的点的个数统计出来 
	}
	for(int i=0;i<=k;i+=2){
		ans=(ans+(C(sum[0],k-i)%mod*C(sum[1],i)%mod))%mod;//求值
		//C(sum[0],k-i)为在度数为偶数的点中选
		//C(sum[1],k)为在度数为奇数的点中选‘偶数个 ’
	}
	cout<<ans<<endl;
    return 0;
}
/*
C(n,m)=(n到m)的阶乘/m的阶乘
	  =n!/(m!*(n-m)!)	  
(n到m)的阶乘=n!/(n-m)! 
			=n*(n-1)*(n-2)*...*1/[(n-m)*(n-m-1)*(n-m-2)*...*1]
			=n*(n-1)*(n-2)*...*1/(n-m)/(n-m-1)/(n-m-2)/.../1
			=n*(n-1)*(n-2)*...*(n-m+1)

*/ 
```


---

## 作者：szhqwq (赞：3)

这道题质量挺好，模拟赛场切了。

## $\tt{Solution}$

首先我们发现，对于一堆相同颜色的点，我们将其中一个点染成另一种颜色，这个点产生的贡献是与**这个点的度数**有关的，再结合要求两端颜色不同的边数为偶数，可以发现此点的度数也应为偶数。

但是我们如果将多个点染成另一种颜色，就会出现一些边的两端颜色相同，并且不一定满足两端颜色不同的边数为偶数的条件，此时我们进行分类讨论：

1. 对于两个度数均为偶数的点多出贡献，发现贡献会减 $2$，此时贡献依旧为偶数；

2. 对于两个度数均为奇数的点多出贡献，贡献还是减 $2$，且两个奇数相加为偶数，**当且仅当我们选出的度数为奇数的点的个数为偶数时**贡献为偶数；

3. 对于一个度数为奇数和一个度数为偶数的点多出贡献，因为我们可以保证度数为奇数的点和度数为偶数的点的贡献之和为偶数，所以贡献减 $2$ 依旧满足条件。

**注：此处讨论的点均为我们要选出的 $k$ 个红色点。**

那么我们可以处理逆元使用组合数计算出所有方案数，注意取模。

[Link](https://atcoder.jp/contests/abc262/submissions/47441542)

---

## 作者：williamY (赞：2)

## 前言
[题目链接](https://atcoder.jp/contests/abc262/tasks/abc262_e)

[更好的阅读体验](https://blog.csdn.net/weixin_48321850/article/details/132694008?spm=1001.2014.3001.5501)

这一题我比赛时写挂了，比赛后又改对了……

## 题意
有一张 $n$ 个点，$m$ 条边的无向图，其中每一个点都被涂成红或蓝，而且恰好要染红 $k$ 个点，使得两端点不同色的边的数目为偶数，输出方案数。

## 思路
对于条件 $2$，我们可以转化一下，现在我们假设红蓝边为 $a$，红红边为 $b$，那么对于我们选择的 $k$ 个点，这 $k$ 个点的总边数为 $a+2b$，所以我们可以发现 $a$ 和总边数同奇偶，那么条件二就可以转化为 $k$ 个点的总边数为偶数。因为总边数为偶数，那么奇数点为偶数个，所以我们枚举奇数点。

## 代码实现

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long//注意一定要开long long
const int mod = 998244353;
vector<int> g[200005];
int fact[200005];
int infact[200005];
int ji = 0;
int ou = 0;
int _pow(int a, int b) {//快速幂a^ b下面会用到
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void ini() {
	fact[0] = 1;
	infact[0] = 1;
	for (int i = 1; i <= 200000; i++) {
		fact[i] = fact[i - 1] * i % mod;
		infact[i] = infact[i - 1] * _pow(i, mod - 2) % mod;
	}
}
int c(int a, int b) {//组合数C
	if (a < b) {
		return 0;
	}
	return fact[a] * infact[b] % mod * infact[a - b] % mod;
}
signed main() {
	int n, m, k;
	ini();
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);//建图
		g[v].push_back(u);//双向边
	}
	for (int i = 1; i <= n; i++) {
		if (g[i].size() % 2) {
			ji++;//
		} else {
			ou++;//
		}
	}
	int ans = 0;
	for (int i = 0; i <= k; i += 2) {
		ans += c(ji, i) * c(ou, k - i) % mod;
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：Missa (赞：2)

挺喜欢这道题的，但是因为 vp 时过了不能写成做题笔记，所以只能写成题解了。

绿太配这道题了，实现难度极低，但思维难度较大。AT 评了 #1719，倒也算恰当。

题意：给定一张 $n$ 点 $m$ 边的无向图，每个点染成红或蓝，恰 $k$ 点染红，使得两端点不同色的边的数目为偶数，输出方案数。

两端点不同色，两端点同色，这其实和膜二加法很像。或者说，通过膜二加法区分。

如果把蓝色赋值为 $0$，红色赋值为 $1$，则一条边的边权为两边点权和膜二。因为边权为奇数的边的数目为偶数，边权和为偶数。

现在从点的视角看问题。每个点对边权和贡献点权与度数的乘积。所以只用看度数为奇数的点。

因此，红色的点中，度数为奇数的点为偶数个。换句话说，度数为奇数的点中，红色的点有偶数个。

枚举几个红色奇数度点，组合数直接算，做完了。

作为近三个月前的 abc，这道题居然有翻译和三十余发提交，说明这道题确实是一道令人印象深刻的好题。

这道题蕴含了一些 MO 组合中常用的思想：赋值、算两次。

事实上，这种奇偶问题，赋值法几乎是最通用的方法。

代码不给了，确实很好写。

---

## 作者：VitrelosTia (赞：1)

你发现考虑染颜色实在是太困难了，那你考虑先把所有节点搞成蓝色，转化为变色的过程。

然后这个时候你考察一下如何能满足第二个限制，思考一次变色对于不同色边数量的贡献。我们先假定它的贡献是他的度数，但其实并不是，因为如果相邻的有红色的点，对于这两个点贡献都要减 1，但这其实非常好，因为这样总的贡献会减 2，我们知道减去一个偶数之后原数奇偶性不变，那其实直接加度数的贡献就是对的。

最后你考虑计数。要凑到偶数的充要条件是有偶数个奇数，那你先数出有多少个度数为奇数的点，暴力枚举要拿几个，剩下的全给偶数。组合数是 trival 的，预处理出来即可。

```cpp
cin >> n >> m >> k; init(n);
for (int i = 1, u, v; i <= m; i++) {
  cin >> u >> v;
  deg[u]++, deg[v]++;
}
int c1 = 0; for (int u = 1; u <= n; u++) c1 += (deg[u] & 1); int c0 = n - c1;
int ans = 0; for (int i = 0; i <= k; i += 2) ans = (ans + C(c1, i) * C(c0, k - i) % mod) % mod;
cout << ans;
```

---

## 作者：MMXIandCCXXII (赞：1)

## 题目大意
给一个 $N$ 个点、$M$ 条边的简单无向图，每个点染成红色或蓝色。求满足以下要求的染色方案数：  

+ 有 $K$ 个点为红色

+ 连接的点颜色不同的边有偶数条

## 思路

其实这道题主要考的是思维。我们可以拿画板模拟一下过程，首先将所有点染成蓝色，随后一个一个选点，染成红色。

初始：
![](https://cdn.luogu.com.cn/upload/image_hosting/fo2b3qcp.png)

随后我们染一个点：
![](https://cdn.luogu.com.cn/upload/image_hosting/3deemnmo.png)

然后我们发现，被染成红点的点连接的边都变成了连接颜色不同的边。意思是，每次这样的边会增加被染成红色的点的度数了？那我们把每个点的度统计一下，继续染色：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdazr19m.png)

这时我们发现，两个红点之间的边被统计了两次，可它连接了相同颜色，一次都不应该算啊。把这两次减掉肯定是不现实的，不然我们何必统计度数呢？再回来看题目：连接的点颜色不同的边有**偶数**条。偶数一词很重要。想一想，如果原来有偶数条边，减掉这两次不也是偶数吗？奇数也是同理。所以，算不算这两次都没关系，不影响奇偶性就行。

所以，问题就变成了：选 $k$ 个点，使其度之和为偶数。

问题一下就简单了。我们只需要枚举选几个度为奇数的边，剩下的选度为偶数的，排列组合算出情况即可。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;

int d[200010];
int inv[200010], fac[200010], invfac[200010];

int C(int n, int m)
{
    if (n < m) return 0;
    return fac[n] * invfac[m] % mod * invfac[n-m] % mod;
} //算组合数。

signed main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        d[a]++, d[b]++;
    }//统计度数。
    inv[1] = inv[0] = invfac[1] = invfac[0] = fac[1] = fac[0] = 1;
    for (int i = 2; i <= n; i++)
    {
        inv[i] = inv[mod%i] * (mod - mod / i) % mod;
        fac[i] = fac[i-1] * i % mod;
        invfac[i] = invfac[i-1] * inv[i] % mod;
    }//预处理逆元。
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i] % 2 == 1) cnt1++;
        else cnt2++;
    }//统计奇偶。
    int ans = 0;
    for (int i = 0; i <= k; i += 2)
    {
        ans = (ans + C (cnt1, i) * C (cnt2, k - i) % mod) % mod;
    }//枚举度为奇数的边，算出情况数。
    cout << ans << endl;
    return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解：
挺妙的题。

考虑先将所有点染成蓝色，在考虑染黑色。

如果一个红点旁边没有红点，那么这个红点的贡献是 $d_x$。
如果一个红点旁边有 $k$ 个红点，那么这个红点的贡献是 $d_x-k$。

这貌似并没有什么用，但在贡献了 $d_x-k$ 后，与之相连的红点也都少了 $1$，也使的总贡献少了 $k$，因此两端颜色不同的边数总共增加了 $d_x-2\times k$，这与 $d_x$ 的奇偶性有关。

于是乎我们将这些点分为两类，一类度数是奇数，一类度数是偶数，偶数任意取，奇数取偶数个，枚举奇数取的个数，用乘法原理加起来即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long n,m,k,ans,d[500005],sum,fac[500005],inv[500005];
long long qpow(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)res*=a,res%=mod;
		a*=a;
		a%=mod;
		b>>=1;
	}
	return res;
}
long long C(long long n,long long m)
{
    if(n<m)return 0;
	return fac[n]%mod*inv[m]%mod*inv[n-m]%mod;
}
void init()
{
	fac[0]=inv[0]=1;
	for(long long i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(long long i=1;i<=n;i++)inv[i]=inv[i-1]*qpow(i,mod-2)%mod;
}
int main()
{
	cin>>n>>m>>k;
	for(long long i=1,u,v;i<=m;i++)
	{
		cin>>u>>v;
		d[u]++,d[v]++;
	}
	init();
	for(long long i=1;i<=n;i++)if(d[i]%2==0)sum++;
	for(long long i=0;i<=k;i+=2)
	{
		ans=(ans+(C(sum,k-i)%mod*C(n-sum,i)%mod))%mod;//sum是偶数个数，n-sum即为奇数，选i个奇数。
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

观察性质，容易发现若原图为全蓝，染红一个点后，对两端异色边的数量贡献与染红点的度数有关。

但是可以发现，如果染红了两个相邻的点，就会产生重复，设这两个点的度数和为 $s$，可以发现，这样情况下对两端异色边的数量贡献为 $s$ 减去重复的边造成的贡献，由于重复的边会被两端各算一次，所以要减去的贡献为 $2$。

$2$ 有很好的性质，减去 $2$ 不会改变原来贡献的奇偶性，所以我们只用在意原来选出的点的度数和的奇偶性，枚举使得选度数为奇数的点为偶数个即可。

### $\text{code}$

```cpp
int n,m,k;

int d[maxn];

int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int fac[maxn],inv[maxn];

void init(int maxn){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn]=ksm(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}

int C(int m,int n){
	if(n<0||m<0||m<n){
		return 0;
	}
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

void solve(){
	n=read(),m=read(),k=read();
	init(maxn-1);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		d[u]++;
		d[v]++;
	}
	int cnt0=0,cnt1=0;
	for(int i=1;i<=n;i++){
		cnt0+=(d[i]%2==0);
		cnt1+=(d[i]%2==1);
	}
	int ans=0;
	for(int i=0;i<=k;i+=2){
		ans=(ans+C(cnt1,i)*C(cnt0,k-i)%mod)%mod;
	}
	write(ans);
	puts("");
	return ;
}
```

---

## 作者：Claire0918 (赞：0)

下文记 $deg_u$ 为点 $u$ 的度数。

看到本题，不难想到二分图染色。但实际上无法维护红色点的限制。

不妨考虑将图从全为蓝色点逐渐转移。我们注意到每将一个没有与红色点连边的蓝色点 $u$ 变为红色点时，两端颜色不同的边的数量会增加 $deg_u$。

但是，如果 $u$ 与红色点有连边，有一条边会重复计算。我们注意到实际上一条连接两个红色点的边的对两端颜色不同的边的贡献为 $0$，但我们会将其贡献按照 $2$ 计算，并不会对奇偶性造成影响，故直接忽略即可。

至此，问题变为考虑从 $V$ 中取出若干个点组成集合 $S$，使得 $\sum_{u \in S} deg_u$ 为偶数。

考虑分类讨论度数为奇数或偶数的点。显然 $S$ 中有多少度数为偶数的点并不改变结果的奇偶性，而我们要使度数的和为偶数，从而度数为奇数的点有偶数个。

设有 $t$ 个 $deg_u$ 为奇数的 $u$，则答案为 $\sum_{i = 0}^{\lfloor\frac{t}{2}\rfloor} {t \choose 2i}{n - t \choose k - 2i}$。

$\mathcal{O}(n)$ 枚举即可，总时间复杂度 $\mathcal{O}(n \log n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10, mod = 998244353;

int n, m, k, res = 0, odd = 0;
int degree[maxn];
long long fac[maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline long long inv(long long x){
    return ksm(x, mod - 2);
}

inline long long c(int n, int m){
    return fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    fac[0] = 1;
    for (int i = 1; i <= n; i++){
        fac[i] = fac[i - 1] * i % mod;
    }
    for (int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        degree[u]++, degree[v]++;
    }
    for (int i = 1; i <= n; i++){
        odd += degree[i] & 1;
    }
    for (int i = 0; i <= k; i += 2){
        if (odd >= i && n - odd >= k - i){
            res = mod_add(res, c(odd, i) * c(n - odd, k - i) % mod);
        }
    }
    printf("%d", res);

return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC262E] Red and Blue Graph


## 思路

我们考虑在一幅全是蓝色点的图上染红色点。

当我们染一个红色点 $i$，图上两端颜色不同的边数为 $d_i$（$d_i$ 为点 $i$ 的度数）。当我们染第 $2$ 个红色点 $j$ 时，图上两端颜色不同的边数为 $d_i+d_j$。

这时，我们发现，如果 $i$ 和 $j$ 是相邻的两个点，那么他们之间的这条边不满足要求，不仅在加 $d_j$ 时多加了这条边，在 $d_i$ 中我们也要将这条边减去。所以我们要将答案 $-2$。看看本题的要求就很巧了，本题只要求**边数为偶数**，而恰好对一个整数减去 $2$ 对其奇偶性没有影响，所以我们忽略它即可。

所以本题变成：

在图中挑选 $K$ 个点，使其点的度数之和为偶数，求方案数。

我们统计奇数度数的点的数量 $sume$，偶数度数的点的数量 $sumo$，枚举奇数度数的点的个数 $i$，计算出偶数度数点的个数 $k-i$，然后每次枚举到一个 $i$，就相当于在 $sume$ 个点中挑选 $i$ 个点，在 $sumo$ 中挑选 $k-i$ 个点进行组合，计算组合数 $C_{sume}^i\times C_{sumo}^{k-i}$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int INF=1e9;
const int MOD=998244353;
int u,v,f[N]={1,1},d[N]; 
int n,m,k,cnt,s; 
vector<int> e[N];


int ksm(int c,int k,int p) {	//c^k %p
	int res=1;
	while(k) {
		if(k&1) {
			res=res*c%p;	//注意只有1句在里面！
		}
		k>>=1;	//不要写反了！
		c=c*c%p;
	}
	return res;
}

int inv(int a,int b){return (a%MOD)*ksm(b,MOD-2,MOD)%MOD;}

int c(int n,int m){return m?inv(f[n],f[m]*f[n-m]%MOD):1;}

signed main(){
    
	cin>>n>>m>>k;
    for(int i=2;i<=n;i++)f[i]=f[i-1]*i%MOD;
    for(int i=1;i<=m;i++){
        
		cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
		d[u]++;
		d[v]++;
    }
    
    for(int i=1;i<=n;i++)cnt+=(d[i]&1); // 统计度数为奇数的点的个数
    for(int i=0;i<=min(cnt,k);i+=2)//枚举度数为奇数的点的个数,并且两个两个增加,以保证奇偶性.
		if(k-i<=n-cnt){
			s+=c(cnt,i)*c(n-cnt,k-i);// 枚举数量，用组合数求解
			s%=MOD;
		}
    cout<<s<<endl;
    return 0;
}
```




---

