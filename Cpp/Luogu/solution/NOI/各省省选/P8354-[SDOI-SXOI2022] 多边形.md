# [SDOI/SXOI2022] 多边形

## 题目描述

给定一个正 $n$ 边形，除了这个正 $n$ 边形的 $n$ 个顶点，顺时针第 $i$ 条边上还有额外的 $a_i-1$ 个顶点等分这条线段，也就是说，第 $i$ 条边被顶点分成了长度相等的 $a_i$ 段。

你可以在顶点之间连接一些线段，但是连接完线段之后，图中的任意两条新添加的线段只能在端点处有交，此外，新的线段也不应该与多边形的边有所重合。

我们称添加了若干线段之后得到的图为一个三角剖分，当且仅当多边形内的每个面都是一个三角形，注意，三角形的边上可以有原来凸多边形边上的顶点。

给定这样一个凸多边形，其有多少种满足上述条件的三角剖分? 你只需要计算方案数模 $998244353$ 的答案就行。

## 说明/提示

**【样例 1 解释】**

5 种方案如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/v9hip98o.png)

**【数据范围】**

对于 $10 \%$ 的数据，保证 $\sum a_{i} \leq 300$。  
对于 $50 \%$ 的数据，保证 $\sum a_{i} \leq 5000$。  
对于 $100 \%$ 的数据，保证 $n \geq 3$，$a_{i} \geq 1$， $\sum a_{i} \leq 5 \times 10^{5}$。

注：本题无大样例下载

## 样例 #1

### 输入

```
3
2 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5
3 1 4 2 5```

### 输出

```
359895```

## 样例 #3

### 输入

```
8
4 2 1 8 3 7 3 1```

### 输出

```
577596154
```

# 题解

## 作者：dottle (赞：12)

以下，为了方便表述，称原多边形的边为边，边上等分出的线段叫做线，最终的三角剖分中，在同一个三角形中的若干同一条边上的线组成的东西叫段。

首先，普通的多边形三角剖分的方案数是卡特兰数。

本题类似于对 $s=\sum a_i$ 条线进行三角剖分，但是：

1. 不能连接处于同一条边上的两个点。
2. 同一条边上的若干条线可以处于同一个三角形中。

首先想办法处理掉第二个条件。可以对于每条边枚举上面的线最终会被分成几段，方案数是一个组合数的形式。后续的过程中，不同的段就不能分到同一个三角形中了。

接下来，考虑处理第一个条件。考虑容斥，钦定一些同一条边上的点对被连接了，来考虑一下容斥系数：

1. 对于跨过一条线的点对，系数为 $1$。
2. 对于跨过两条线的点对，系数为 $-1$，因为钦定了一条非法的线段。
3. 对于跨过三条及以上线的点对，系数为 $0$。因为若其被连接，那么在其内部一定还有若干点对被连接。（这一点不理解的可以看后面的补充。）

每条边留下几段，这在边边之间是相互独立的。因此我们可以得到一个 $s^2$ 的算法：对于每条边，分别求出其钦定后留下 $i$ 段的容斥系数之和。然后就可以算出将整个多边形剖为 $i$ 段的系数之和，每一项乘上 $i$ 边形的三角剖分方案数即是答案。

```cpp
void solve(){
	init();
	cin>>n;
	int sum=0;
	dp[0][0]=1;
	for(int i=0;i<N;i++)
		for(int j=0;j<N-2;j++){
			add(dp[i+1][j+1],dp[i][j]);
			add(dp[i+1][j+2],-dp[i][j]);
		}
	f[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		memcpy(g,f,sizeof(g));
		memset(f,0,sizeof(f));
		memset(h,0,sizeof(h));
		for(int j=1;j<=a[i];j++)// 枚举此边分为了 j 段（处理第二个条件）
			for(int k=1;k<=j;k++)// 枚举此段钦定后还有 k 段（处理第一个条件）
				add(h[k],C(a[i]-1,j-1)*dp[k][j]);
		for(int k=1;k<=a[i];k++)
			for(int l=0;l<=sum;l++)
				add(f[l+k],h[k]*g[l]%mod);
		sum+=a[i];
	}
	int res=0;
	for(int i=1;i<=sum;i++)
		add(res,f[i]*Ca(i-2));
	cout<<(res%mod+mod)%mod<<endl;
}
```

现在可以考虑优化这个算法了。对于后面那个把 $h$ 卷起来那个过程，可以拿个堆按大小排序从小到大乘起来就好。现在主要问题是怎么算这个 $h$ 数组。

首先把模型转化一下，把两个条件综合在一起。$n$ 条线有 $n-1$ 个分界点，把这些点分成三类：

1. 连接点，代表前后的线最终属于同一段。
2. 断点，代表前后的线最终既不属于同一段，也没有被某个钦定非法的线段跨过。
3. 非法点，代表前后的线最终不属于同一段，但是其前后的段被钦定非法的线段跨过了。

最终钦定后的段数就是断点的个数，容斥系数就是 $-1$ 的非法点个数次方。

据此，可以将段根据是否存在非法点来分成两类。两个都存在非法点的段是不能用连接点连起来的。

那么我们设 $dp_{i,0/1,0/1,j}$ 代表左边的段是否有非法点，右边的段是否有非法点，当前有 $i$ 条线，最终划分为 $j$ 段，容斥系数之和是多少。然后考虑用倍增的方法来算。每次可以 $O(n\log n)$ 地从 $dp_{i}$ 推出 $dp_{2i}$；也可以 $O(n)$ 地从 $dp_{i}$ 推出 $dp_{i+1}$。具体的方式是枚举当前点是哪一类，然后转移。注意会有一种无法统计进去的特殊情况，即所有点都是连接点，这样左右是同一个段，此时需要特殊处理。

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1000005,mod=998244353;
const int g=3;
using namespace std;
using vi = vector<int>;

void add(int&x,int y){
	x+=y;if(x>=mod||x<-mod)x%=mod;
}

int gsc(int a,int b){
	int res=1;
	for(int i=1;i<=b;i<<=1,a=a*a%mod)
		if(b&i)res=res*a%mod;
	return res;
}int inv(int k){return gsc(k,mod-2);}

int jc[N],ij[N],iv[N];
int C(int n,int m){
	if(n<m||m<0)return 0;
	return jc[n]*ij[m]%mod*ij[n-m]%mod;
}
void init(){
	jc[0]=iv[0]=1;
	for(int i=1;i<N;i++)jc[i]=jc[i-1]*i%mod;
	ij[N-1]=inv(jc[N-1]);
	for(int i=N-2;i>=0;i--)ij[i]=ij[i+1]*(i+1)%mod;
	for(int i=1;i<N;i++)iv[i]=ij[i]*jc[i-1]%mod;
}

vector<int> A[N];
int lim,r[N];
void initntt(int n){
	lim=1;while(lim<n)lim<<=1;
	for(int i=0;i<lim;i++)
		r[i]=(r[i>>1]>>1)|((i&1)*(lim>>1));
}
void ntt(vi&a,int ty=1){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(r[i]<=i)swap(a[i],a[r[i]]);
	int x,y;
	for(int i=1;i<lim;i<<=1){
		int o=gsc(ty==1?g:inv(g),mod/(i*2)),x,y;
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0,w=1;k<i;k++,w=w*o%mod)
				x=a[j+k],y=a[j+k+i]*w,a[j+k]=(x+y)%mod,a[j+k+i]=(x-y)%mod;
	}
	if(ty==-1){
		int iv=inv(lim);
		for(int i=0;i<lim;i++)a[i]=(a[i]*iv%mod+mod)%mod;
	}
}

vi operator * (vi a,vi b){
	initntt(a.size()+b.size()-1);
	ntt(a),ntt(b);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i]%mod;
	ntt(a,-1);
	while(a.size()&&a.back()==0)a.pop_back();
	return a;
}
vi operator + (vi a,vi b){
	if(a.size()<b.size())swap(a,b);
	for(int i=0;i<b.size();i++)add(a[i],b[i]);
	return a;
}
void operator +=(vi&a,vi b){a=a+b;}
vi operator - (vi a){for(auto&x:a)x=-x;return a;}
vi yy(vi a){if(a.size())a.erase(a.begin());return a;}
vi zy(vi a){a.insert(a.begin(),0);return a;}
struct cmp{bool operator ()(vi a,vi b){return a.size()>b.size();}};
vi Mul(vector<vi> A){
	priority_queue< vi,vector<vi>,cmp > Q;
	for(auto x:A)Q.push(x);
	while(Q.size()>1){
		auto x=Q.top();Q.pop();
		auto y=Q.top();Q.pop();
		Q.push(x*y);
	}
	return Q.top();
}

struct Res{vi a[2][2];auto operator[](int b){return a[b];}}tem[N];
int vis[N];
Res geth(int k){
	if(k==1){Res res;return res;}
	if(vis[k])return tem[k];
	int fl=0;
	vis[k]=1;
	if(k&1)k--,fl=1;
	vis[k]=1;
	Res L=geth(k/2);
	Res res;
	auto D=-L[0][1]*L[0][1];
	for(int i=0;i<2;i++)
		for(int j=i;j<2;j++){
			auto A=(L[i][0]+L[i][1])*(L[0][j]+L[1][j]);
			auto B=(i==0&&j==0)?D:-L[i][1]*L[1][j];
			auto C=(i==1&&j==1)?D:-L[i][0]*L[0][j];
			res[i][j]+=A;
			res[i][j]+=yy(A);
			res[i][j]+=yy(C);
			res[i][j]+=yy(B);
		}
	res[1][0]=res[0][1];
	for(int i=0;i<2;i++){
		res[i][0]+=L[i][0]+zy(L[i][0])+zy(L[i][1]);
		res[i][1]+=-L[i][0]+L[i][1];
		res[0][i]+=L[0][i]+zy(L[0][i])+zy(L[1][i]);
		res[1][i]+=-L[0][i]+L[1][i];
	}
	res[0][0]+=(vi){0,0,1};
	res[1][1]+=(vi){0,-1};
	tem[k]=res;
	if(fl){
		Res rr;
		for(int i=0;i<2;i++){
			rr[i][0]+=res[i][0]+zy(res[i][0])+zy(res[i][1]);
			rr[i][1]+=-res[i][0]+res[i][1];
		}
		rr[0][0]+=(vi){0,0,1};
		rr[1][1]+=(vi){0,-1};
		res=rr;
	}
	return tem[k+fl]=res;
}
vector<int> getH(int x){
	Res r=geth(x);
	vector<int> a(x+1);a[1]=1;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
		for(int k=0;k<r[i][j].size();k++)
			add(a[k],r[i][j][k]);
	return a;
}

int n;
int a[N];

int Ca(int k){
	if(k<0)return 0;
	return C(2*k,k)*iv[k+1]%mod;
}

int h[N],f[N];
void solve(){
	init();
	int n,s=0;cin>>n;
	vector<vi> A;
	for(int i=1;i<=n;i++){
		int x;cin>>x;s+=x;
		A.push_back(getH(x));
	}
	auto res=Mul(A);
	int result=0;
	for(int i=3;i<res.size();i++)
		add(result,res[i]*Ca(i-2));
	cout<<(result%mod+mod)%mod<<endl;
}

main(){
	ios::sync_with_stdio(0);
	solve();
}
```

补充一下为什么跨过三条线的边容斥系数是 $0$。考虑其内的任意一种三角剖分，都包含有至少 $1$ 条跨过两条线的边，假设有 $k$ 条。考虑这 $k$ 条边是否钦定，会有 $2^k$ 种，其中有一半系数为 $1$，其余为 $-1$，总和是 $0$。

---

## 作者：苹果蓝17 (赞：9)

对一条边考虑，关注边上的顶点（不含两端）。由于允许这些点不连边，先枚举哪些点连边。

凸 $n$ 边形的三角剖分有 $Catalan(n-2)$ 种，但如果存在原本在同一条边的两个点连边就会不合法。

考虑容斥。记恰跨过一个（选中的）点的边为 关键边，注意到不合法的方案至少包含一条关键边，且不同的关键边方案对应的一定是不同的方案，故可以按关键边数量容斥。

设这条边上有 $a$ 个顶点（不含两端），$f_i$ 表示剩下 $i$ 个顶点（不含两端）的方案数。枚举选中了 $k$ 个点，插板可得：

$$f_i=\sum\limits_{k=i}^a (-1)^{k-i} \dbinom{a}{k} \dbinom{i+1}{k-i}$$

最后只需要将所有 $F_a(x)$ 乘起来再乘上对应的卡特兰数统计答案即可。接下来考虑如何快速计算 $F_a(x)$。

$$f_i=[x^{a-i}] \sum\limits_{k=i}^{a} \dbinom{a}{k} x^{a-k} \dbinom{i+1}{k-i} (-x)^{k-i}$$

$$f_i=[x^{a-i}] (1+x)^a (1-x)^{i+1}$$

记 $G_k(x)=(1+x)^a (1-x)^k$。注意到 $G_k(x)$ 是 D-finite 的，对其求导：

$$G_k'(x)=G_k(x) (\dfrac{a}{1+x}-\dfrac{k}{1-x})$$

$$(1-x^2)G_k'(x)=a(1-x)G_k(x)-k(1+x)G_k(x)=(a-k)G_k(x)-(a+k)xG_k(x)$$

$$(i+1)g_{i+1}=(a-k)g_i-(k+a-i+1)g_{i-1}$$

于是记录相邻两项系数，可以 $O(1)$ 推出前后项。

同时有 $G_{k+1}(x)=(1-x)G_k(x)$，故可以推出 $G_k(x)$ 的三项，再推出 $G_{k+1}(x)$ 的两项。

类似莫队转移，可以 $O(a)$ 计算出 $F_a(x)$。该部分总时间复杂度 $O(\sum a_t)$。

总时间复杂度 $O(\sum a_t \log^2 \sum a_t)$。

#### 代码

```cpp
int main(){
	pre(N-5);
	cin>>n;
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]--,m+=a[i];
	for(long long t=1;t<=n;t++){
		id++;
		Q[id].resize(a[t]+2);
		
		long long k=1,pos=a[t],w1=(1+mod-a[t])%mod,w2=mod-1;
		for(long long i=0;i<=a[t];i++){
			if(i){
				long long w3=((a[t]+mod-k)*w2%mod+mod-(k+a[t]+mod-pos)*w1%mod)*invv[pos+2];
				long long nw1=(w2+mod-w1)%mod,nw2=(w3+mod-w2)%mod;
				w1=nw1,w2=nw2;
				pos++,k++;
				
				for(long long p=1;p<=2;p++){
					long long tmp=k+a[t]-(pos-1);
					long long w0=((a[t]+mod-k)*w1%mod+mod-(pos+1)*w2%mod)*(tmp>0?invv[tmp]:mod-invv[-tmp])%mod;
					w2=w1,w1=w0;
					pos--;
				}
			}
			Q[id][i]=w1;
		}
	}
	solve(1,1,id);
	for(long long i=0;i<=m;i++) ans=(ans+P[1][i]*Cat(i+n-2)%mod)%mod;
	cout<<ans;
}

```

---

## 作者：Aleph1022 (赞：8)

题意可以当做是增加两个限制的三角剖分：

- 在边上的点可以不连。
- 边上的点不能连到同一条边上的点。

第一个限制是简单的，我们只需要枚举每条边上实际连了的点的个数。

去掉第一个限制后，第二个限制显得有些棘手。  
但注意到由于我们是三角剖分，所以如果存在同一条边上互连的点，则必然存在一条线恰好跨过一个顶点，且其原来在边上。  
所以我们考虑对这样的边容斥。而我们钦定一条这样的边，相当于是再次缩掉了一个三角形使得边数减一。

于是考虑算出每条边最终的容斥系数的 GF，乘起来就得到了总共的容斥系数，再用 Catalan 数计算答案即可。  
而对于最终的一段边，若其原来包含 $j$ 段，其贡献应为 $1 - (j-1)$。其中后者是选择一个钦定的非法顶点，令这条边跨过。  
从而我们要算的是
$$
\sum_{k=1}^{a_i} x^k [w^{a_i}] \left(\sum_{j\ge 1}(2-j)w^j\right)^k
$$

那么核心是对所有 $k$ 计算
$$
[w^{a_i}] \left(\frac{w(1-2w)}{(1-w)^2}\right)^k
$$

令 $u$ 为 $\frac{w(1-2w)}{(1-w)^2}$ 的复合逆。则根据拉格朗日反演
$$
[w^{a_i}] \left(\frac{w(1-2w)}{(1-w)^2}\right)^k = \frac k{a_i} [x^{a_i-k}] \left(\frac xu\right)^{a_i}
$$

令 $v=\frac xu$。由复合逆关系
$$
\frac{u(1-2u)}{(1-u)^2}=w
$$

我们知道 $v$ 满足
$$
v^2-(1+2w)v+(2w+w^2)=0
$$

从而 $v$ 是代数的，从而 $v^{a_i}$ 是 D-Finite 的。  
记 $f_n = [w^n] v^k$，通过 ODE 自动机可以得到递推式
$$
\begin{aligned}
n(n-k)f_n &= \frac12(9n-8k-8)(n-1)f_{n-1} \\
&+ \left[2k(k-2)-\frac12(n-2)(3n-2k-2)\right] f_{n-2} \\
&+ \left[k(1-2k)+(n-3)(4k-2n+5)\right] f_{n-3} &\quad (n\ge 1)
\end{aligned}
$$

而 $f_0=1$，负下标为 $0$。

代码：
```cpp
#include <queue>
#include <cstdio>
#include <chrono>
#include <random>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>
#include <functional>
#include <initializer_list>

using ll = long long;

using namespace std;

const int mod = 998244353, G = 3;
inline int norm(int x) {
  return x >= mod ? x - mod : x;
}
inline int reduce(int x) {
  return x < 0 ? x + mod : x;
}
inline int neg(int x) {
  return x ? mod - x : 0;
}
inline void add(int &x, int y) {
  if ((x += y - mod) < 0)
    x += mod;
}
inline void sub(int &x, int y) {
  if ((x -= y) < 0)
    x += mod;
}
inline void fam(int &x, int y, int z) {
  x = (x + (ll)y * z) % mod;
}
inline int mpow(int a, int b) {
  int ret = 1;
  for (; b; b >>= 1)
    (b & 1) && (ret = (ll)ret * a % mod),
    a = (ll)a * a % mod;
  return ret;
}

const int BRUTE_N2_LIMIT = 50;

struct NumberTheory {
  typedef pair<int, int> P2_Field;
  mt19937 rng;
  NumberTheory(): rng(chrono::steady_clock::now().time_since_epoch().count()) {}
  void exGcd(int a, int b, int &x, int &y) {
    if (!b) {
      x = 1, y = 0;
      return;
    }
    exGcd(b, a % b, y, x), y -= a / b * x;
  }
  int inv(int a, int p = mod) {
    int x, y;
    exGcd(a, p, x, y);
    if (x < 0)
      x += p;
    return x;
  }
  template<class Integer>
  bool quadRes(Integer a, Integer b) {
    if (a <= 1)
      return 1;
    while (a % 4 == 0)
      a /= 4;
    if (a % 2 == 0)
      return (b % 8 == 1 || b % 8 == 7) == quadRes(a / 2, b);
    return ((a - 1) % 4 == 0 || (b - 1) % 4 == 0) == quadRes(b % a, a);
  }
  int sqrt(int x, int p = mod) {
    if (p == 2 || x <= 1)
      return x;
    int w, v, k = (p + 1) / 2;
    do
      w = rng() % p;
    while (quadRes(v = ((ll)w * w - x + p) % p, p));
    P2_Field res(1, 0), a(w, 1);
    for (; k; k >>= 1) {
      if (k & 1)
        res = P2_Field(((ll)res.first * a.first + (ll)res.second * a.second % p * v) % p, ((ll)res.first * a.second + (ll)res.second * a.first) % p);
      a = P2_Field(((ll)a.first * a.first + (ll)a.second * a.second % p * v) % p, 2LL * a.first * a.second % p);
    }
    return min(res.first, p - res.first);
  }
} nt;

namespace Simple {
  int n = 1;
  vector<int> fac({1, 1}), ifac({1, 1}), inv({0, 1});
  void build(int m) {
    n = m;
    fac.resize(n + 1), ifac.resize(n + 1), inv.resize(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
      inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; ++i)
      fac[i] = (ll)fac[i - 1] * i % mod,
      ifac[i] = (ll)ifac[i - 1] * inv[i] % mod;
  }
  void check(int k) {
    int m = n;
    if (k > m) {
      while (k > m)
        m <<= 1;
      build(m);
    }
  }
  inline int gfac(int k) {
    check(k);
    return fac[k];
  }
  inline int gifac(int k) {
    check(k);
    return ifac[k];
  }
  inline int ginv(int k) {
    check(k);
    return inv[k];
  }
}

struct SimpleSequence {
  function<int(int)> func;
  inline SimpleSequence(const function<int(int)> &func): func(func) {}
  inline int operator[](int k) const {
    return func(k);
  }
} gfac(Simple::gfac), gifac(Simple::gifac), ginv(Simple::ginv);

inline int binom(int n, int m) {
  if (m > n || m < 0)
    return 0;
  return (ll)gfac[n] * gifac[m] % mod * gifac[n - m] % mod;
}

namespace NTT {
  int L = -1;
  vector<int> root;
  void init(int l) {
    L = l;
    root.resize((1 << L) + 1);
    int n = 1 << L, *w = root.data();
    w[0] = 1, w[1 << L] = mpow(31, 1 << (21 - L));
    for (int i = L; i; --i)
      w[1 << (i - 1)] = (ll)w[1 << i] * w[1 << i] % mod;
    for (int i = 1; i < n; ++i)
      w[i] = (ll)w[i & (i - 1)] * w[i & -i] % mod;
  }
  void DIF(int *a, int l) {
    int n = 1 << l;
    for (int len = n >> 1; len; len >>= 1)
      for (int *j = a, *o = root.data(); j != a + n; j += len << 1, ++o)
        for (int *k = j; k != j + len; ++k) {
          int r = (ll)*o * k[len] % mod;
          k[len] = reduce(*k - r), add(*k, r);
        }
  }
  void DIT(int *a, int l) {
    int n = 1 << l;
    for (int len = 1; len < n; len <<= 1)
      for (int *j = a, *o = root.data(); j != a + n; j += len << 1, ++o)
        for (int *k = j; k != j + len; ++k) {
          int r = norm(*k + k[len]);
          k[len] = (ll)*o * (*k - k[len] + mod) % mod, *k = r;
        }
  }
  void fft(int *a, int lgn, int d = 1) {
    if (L < lgn)
      init(lgn);
    int n = 1 << lgn;
    if (d == 1)
      DIF(a, lgn);
    else {
      DIT(a, lgn), reverse(a + 1, a + n);
      int nInv = mod - (mod - 1) / n;
      for (int i = 0; i < n; ++i)
        a[i] = (ll)a[i] * nInv % mod;
    }
  }
}

struct poly {
  vector<int> a;
  poly(ll v = 0): a(1) {
    if ((v %= mod) < 0)
      v += mod;
    a[0] = v;
  }
  poly(const poly &o): a(o.a) {}
  poly(const vector<int> &o): a(o) {}
  poly(initializer_list<int> o): a(o) {}
  int operator[](int k) const { return k < a.size() ? a[k] : 0; }
  int &operator[](int k) {
    if (k >= a.size())
      a.resize(k + 1);
    return a[k];
  }
  int deg() const { return (int)a.size() - 1; }
  void redeg(int d) { a.resize(d + 1); }
  int size() const {return a.size(); }
  void resize(int s) { a.resize(s); }
  poly slice(int d) const {
    if (d < a.size())
      return vector<int>(a.begin(), a.begin() + d + 1);
    vector<int> ret = a;
    ret.resize(d + 1);
    return ret;
  }
  poly shift(int k) const {
    if (size() + k <= 0)
      return 0;
    vector<int> ret(size() + k);
    for (int i = max(0, k); i < ret.size(); ++i)
      ret[i] = a[i - k];
    return ret;
  }
  int *base() { return a.data(); }
  const int *base() const { return a.data(); }
  poly println(FILE *fp = stdout) const {
    for (int i = 0; i < a.size(); ++i)
      fprintf(fp, "%d%c", a[i], " \n"[i == a.size() - 1]);
    return *this;
  }

  poly &operator+=(const poly &o) {
    if (o.size() > a.size())
      a.resize(o.size());
    for (int i = 0; i < o.size(); ++i)
      add(a[i], o[i]);
    return *this;
  }
  poly operator+(const poly &o) const { poly ret(a); ret += o; return ret; }
  poly operator-() const {
    poly ret = a;
    for (int i = 0; i < a.size(); ++i)
      ret[i] = neg(ret[i]);
    return ret;
  }
  poly &operator-=(const poly &o) { return operator+=(-o); }
  poly operator-(const poly &o) { return operator+(-o); }
  poly operator*(const poly &) const;
  poly &operator*=(const poly &o) { *this = operator*(o); return *this; }
};

poly zeroes(int d) { return vector<int>(d + 1); }

namespace NTT { void fft(poly &a, int lgn, int d = 1) { fft(a.base(), lgn, d); } }

using NTT::fft;

poly poly::operator*(const poly &o) const {
  int n = deg(), m = o.deg();
  if (n <= 10 || m <= 10 || n + m <= BRUTE_N2_LIMIT) {
    poly ret = zeroes(n + m);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= m; ++j)
        fam(ret[i + j], a[i], o[j]);
    return ret;
  }
  n += m;
  int l = 0;
  while ((1 << l) <= n)
    ++l;
  poly ret = a, tmp = o;
  ret.resize(1 << l), tmp.resize(1 << l);
  fft(ret, l), fft(tmp, l);
  for (int i = 0; i < (1 << l); ++i)
    ret[i] = (ll)ret[i] * tmp[i] % mod;
  fft(ret, l, -1);
  return ret.slice(n);
}

const int N = 5e5;

int n;
int a[N + 5], cat[N + 5];
int ans;

poly calc(int k) {
  static int f[N + 5];
  f[0] = 1;
  for (int i = 1; i < k; ++i) {
    f[i] = (ll)(i - 1) * (9 * i - 8 * k - 8 + mod) % mod * f[i - 1] % mod * ginv[2] % mod;
    if (i > 1)
      f[i] = (f[i] + (2LL * k * (k - 2) + (ll)(2 - i + mod) * (3 * i + 2 * k - 16 + mod) % mod * ginv[2]) % mod * f[i - 2]) % mod;
    if (i > 2)
      f[i] = (f[i] + ((ll)k * (1 - 2 * k + mod) + (ll)(i - 3) * (4 * k - 2 * i + 5)) % mod * f[i - 3]) % mod;
    f[i] = (ll)f[i] * ginv[i] % mod * (mod - ginv[k - i]) % mod;
  }
  poly ret = zeroes(k);
  for (int i = 0; i <= k; ++i)
    ret[i] = (ll)i * ginv[k] % mod * f[k - i] % mod;
  return ret;
}

int main() {
  scanf("%d", &n);
  priority_queue<poly, vector<poly>, decltype([](const poly &a, const poly &b) {
    return a.deg() > b.deg();
  })> q;
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i), q.push(calc(a[i]));
  while (q.size() > 1) {
    poly a = q.top(); q.pop();
    poly b = q.top(); q.pop();
    q.push(a * b);
  }
  poly res = q.top();
  cat[0] = 1;
  for (int i = 1; i <= res.deg() - 2; ++i)
    cat[i] = 2LL * cat[i - 1] * (2 * i - 1) % mod * ginv[i + 1] % mod;
  for (int i = 3; i <= res.deg(); ++i)
    fam(ans, cat[i - 2], res[i]);
  printf("%d\n", ans);
}
```

---

## 作者：JoshAlMan (赞：7)

首先我们考虑不重不漏地统计这个事情，这个题事实上是凸多边形划分的一个拓展，传统的凸多边形剖分方案数就是卡特兰数。

那么这里的区别就是：

* 在一条边上的点不能相互连线段
* 在边中间上的点可以没线段

不妨考虑我们手动枚举了一些中间点完全不连边，剩下 $m$ 个点要连边，如果我们直接当做凸 $m$ 三角剖分数（设为 $T_m$ ），会包含所有合法方案，但也会多算一些不合法方案，这些方案的特征是：包含至少一条两段点都在同一条边上的线段。

进一步，因为三角剖分是恰好剖完的，你可以想象把那条边上的点人为凸出去，那么只要有一条不合法线段，那么里面必然有一条线段恰好跨越一个点（称之为相邻不合法线段）！

那么我们就可以钦定一个相邻不合法线段的集合 $S$ 去容斥，相当于把两条边缩成了一条边，忽略了中间一个点，中间有个 $-1^{|S|}$ 的容斥系数就行了。

那么整体的框架就是：先抛去一些边中间的点不连边，然后在剩下的点中选出若干互不相邻的点减少一条边做容斥，最终乘上对应的三角剖分数。

每条边独立，设一条边中间有 $t$ 个点，设 $F_i$ 表示这条边中间最终保留下来 $i$ 个点，计算我们就再枚举 $j$ 个点作为容斥，方案数可以直接插板：

$$F_i = \sum_{j} (-1)^j\binom{t}{i + j} \binom{i+1}{j}$$

最后把每个 $F$ 乘起来，然后乘上对应的卡特兰数加和就好了，这部分似乎必须要分治 NTT，看似是 $\log^2$ 但你发现极限情况是 $250000$ 而不是 $500000$，好像可以接受？

然后就能 $O(n^2)$ 了。

现在就是要快速算每个 $F$，发现他有 $i+j,i,i-j$ 不能直接卷积，可恶！！

EI 好像会线性算，这里只提供两种拙劣的方法：

1. 可以直接按照组合意义，即分成若干最终保留的段，然后不保留段中可以选择一个作为容斥，然后类似倍增 DP / FFT 的过程做就好了，应该需要记录左右端点的状态，可能是 $O(9n\log n)$ 的，不知道会不会 T。

2. 考虑 GF，这个过程很像二项式定理，配一个 $x$ 可以画成两个 $(x+1)^p$ 乘积的形式：

   $$F_i = [x^{t-i}]\sum_{j} \binom{t}{t-i-j} x^{t-i-j} \binom{i+1}{j}(-x)^{j}$$

   $$= [x^{t-i}] (x+1)^t (1-x)^{i+1}$$

   $$= [x^{t}] (x+1)^t [(1-x)^{i+1}x^i]$$

   $$= \sum_{j=0}^t [x^{t-j}](x+1)^t \times  [x^j][(1-x)^{i+1}x^i]$$

   设 $G_j = [x^{t-j}](x+1)^t$。

   $$F_i = \sum_{j=0}^t G_j \times  [x^j][(1-x)^{i+1}x^i]$$

   考虑使用转置原理，反过来看 $F$ 到 $G$ 系数向量的线性变换，以下 $h$ 充当 $F$ 作用：

   $$G_j = [x^j]\sum_{i=0}^a h_i [(1-x)^{i+1}x^i]$$

   设 $$H(x) = \sum_{i=0}^a h_i x^i $$

   $$= [x^j]\sum_{i=0}^a (1-x)H(x-x^2))$$

   $$= [x^j]\sum_{i=0}^a (1-x)H(-(x-\frac{1}{2})^2+\frac{1}{4}))$$

   将步骤拆解，可以概括为：

   * 将 $H(x)$ 变成 $H(x+\frac{1}{4})$
   * 将 $H(x)$ 变成 $H(-x)$
   * 将 $H(x)$ 变成 $H(x^2)$
   * 将 $H(x)$ 变成 $H(x-\frac{1}{2})$
   * 将 $H(x)$ 乘 $(1 - x)$

   每一步的转置矩阵，$1, 4$ 步是卷积，剩下都可以线性做，就做到了 $O(n \log n)$

代码实现的第二种：

[code](https://loj.ac/s/1465295)



---

## 作者：APJifengc (赞：2)

容斥的部分其它题解已经写的很清楚了，这里不过多叙述。

我们使用二元 GF 来刻画答案。考虑如何计算这个东西。如果不需要第一步将所有边划分成若干段，那么答案就是一个类似于斐波那契数的东西，即 $[x^a] \frac{1}{1-(x - x^2) y}$。而需要划分段数，我们可以看做先做第二步然后再从第二步的划分结果中划分出第一步的边，也就是把上面的 $x$ 替换成 $\frac{x}{1-x}$ 即可，那么我们要求的答案就是 $[x^a] \frac{1}{1-(\frac{x}{1-x} - (\frac{x}{1-x})^2) y} = [x^a] \frac{1-2x+x^2}{1-(y+2)x+(1+2y)x^2}$。

如果把关于 $y$ 的多项式看做一个常数，那么这就是一个有理分式的远端求值（虽然不太远端），我们可以使用 Bostan-Mori 算法来做这个东西。注意到每轮 Bostan-Mori 只会进行 $O(1)$ 次多项式乘法，且每次多项式次数翻倍，所以这个算法的复杂度是 $O(n \log n)$ 的。Bostan-Mori 的最后一步需要计算 $\frac{f_0}{g_0}$，不过可以发现整个过程 $g_0=1$，所以这步不需要多项式求逆 / 除法。

不过每次需要进行 10 次 NTT，所以很卡常，洛谷上基本过不太去。（不知道用一些高级 NTT 写法能不能过，我反正不太会）注意到整个过程仅有多项式乘法与加减法的操作，不涉及截断与取系数（Bostan-Mori 是对 $x$ 进行的，不是对 $y$ 进行的），所以我们可以仅 NTT 一次，然后中间一直计算点值，最后再 NTT 一次回来。这样免去了大量 NTT，可以通过。

代码写的有点丑，不放了，大概就是维护分子分母的 5 个多项式（$g_0=1$ 不用维护）然后手动推一下 Bostan-Mori 的式子就行了。

---

## 作者：xay5421 (赞：2)

考虑容斥，我们枚举一种剖分方案（这种方案可能会选两个同一条边上的两个点相连），这种划分方案的容斥系数是 $(-1)^{t}$，这里 $t$ 是有多少条边上存在两个这条边上的点相连。

我们发现对于一条边 $a_i$，我们会有一个 $a_i$ 次多项式 $A_{a_i}$，第 $j$ 项系数表示这条边缩成 $j$ 的系数，最后把所有多项式乘起来，然后第 $k$ 项系数乘上 $k$ 的多边形三角剖分数加起来，就是答案。

现在，我们要求这个系数。容易发现，$[x^k]A_{a_i}$ 可以表示成 $[x^{a_i}]B^k$ 的形式，其中 $[x^k]B$ 表示 $k$ 个边缩成一条边的系数。

打表发现，$B$ 的常数项是 $0$，而 $k>0$ 时，$[x^k]B=2-k$。

把 $B$ 表示成好看的形式:

$$
B=\frac{x(1-2x)}{(1-x)^2}
$$

解一下 $B$ 的复合逆 $C$:

$$
C=\frac{2x+1-\sqrt{-4x+1}}{2x+4}
$$

然后我们进行拉格朗日反演:

$$
[x^{a_i}]B^i=[x^{a_i}]x^iC'(\frac{x}{C})^{a_i+1}
$$

然后我们可以算出 $C'(\frac{x}{C})^{a_i+1}$，得到 $A_{a_i}$

最后把所有 $A_{a_i}$ 乘起来

```cpp
#include<bits/stdc++.h>
#ifdef xay5421
#define D(...) fprintf(stderr,__VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ "="),debug_helper::debug(__VA_ARGS__),D("\n")
#include"/home/xay5421/debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define pb push_back
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define each(x,v) for(auto&x:v)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
template<class T>void rd(T&x){int f=0,c;while(!isdigit(c=getchar()))f^=!(c^45);x=(c&15);while(isdigit(c=getchar()))x=x*10+(c&15);if(f)x=-x;}
template<class T>void pt(T x,int c=-1){if(x<0)putchar('-'),x=-x;if(x>9)pt(x/10);putchar(x%10+48);if(c!=-1)putchar(c);}
using namespace std;
using LL=long long;
using ULL=unsigned long long;
template<int P>
class mod_int{
	using Z=mod_int;
private:
	static int mo(int x){return x<0?x+P:x;}
public:
	int x;
	int val()const{return x;}
	mod_int():x(0){}
	template<class T>mod_int(const T&x_):x(x_>=0&&x_<P?static_cast<int>(x_):mo(static_cast<int>(x_%P))){}
	bool operator==(const Z&rhs)const{return x==rhs.x;}
	bool operator!=(const Z&rhs)const{return x!=rhs.x;}
	Z operator-()const{return Z(x?P-x:0);}
	Z pow(long long k)const{
		Z res=1,t=*this;
		while(k){
			if(k&1)res*=t;
			if(k>>=1)t*=t;
		}
		return res;
	}
	Z&operator++(){
		x<P-1?++x:x=0;
		return *this;
	}
	Z&operator--(){
		x?--x:x=P-1;
		return *this;
	}
	Z operator++(int){
		Z ret=x;
		x<P-1?++x:x=0;
		return ret;
	}
	Z operator--(int){
		Z ret=x;
		x?--x:x=P-1;
		return ret;
	}
	Z inv()const{
#ifdef xay5421
		assert(x!=0);
#endif
		return pow(P-2);
	}
	Z&operator+=(const Z&rhs){
		(x+=rhs.x)>=P&&(x-=P);
		return *this;
	}
	Z&operator-=(const Z&rhs){
		(x-=rhs.x)<0&&(x+=P);
		return *this;
	}
	Z&operator*=(const Z&rhs){
		x=1ULL*x*rhs.x%P;
		return *this;
	}
	Z&operator/=(const Z&rhs){
		return *this*=rhs.inv();
	}
#define setO(T,o) friend T operator o(const Z&lhs,const Z&rhs){Z res=lhs;return res o##=rhs;}
	setO(Z,+)setO(Z,-)setO(Z,*)setO(Z,/)
#undef setO
};
const int P=998244353;
using Z=mod_int<P>;
namespace jiangly{

std::vector<int> rev;
std::vector<Z> roots{0, 1};
void dft(std::vector<Z> &a) {
    int n = a.size();
    
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1 ? 1 << k : 0);
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            Z e = Z(3).pow((P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
void idft(std::vector<Z> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - P) / n;
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}
struct Poly {
    std::vector<Z> a;
    Poly() {}
    Poly(const std::vector<Z> &a) : a(a) {}
    Poly(const std::initializer_list<Z> &a) : a(a) {}
    int size() const {
        return a.size();
    }
    void resize(int n) {
        a.resize(n);
    }
    Z operator[](int idx) const {
        if (idx < 0 || idx >= size()) {
            return 0;
        }
        return a[idx];
    }
    Z &operator[](int idx) {
        return a[idx];
    }
    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k = std::min(k, size());
        return Poly(std::vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(std::vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot)
            sz *= 2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i) {
            a.a[i] = a[i] * b[i];
        }
        idft(a.a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    Poly deriv() const {
        if (a.empty()) {
            return Poly();
        }
        std::vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i) {
            res[i] = (i + 1) * a[i + 1];
        }
        return Poly(res);
    }
    Poly integr() const {
        std::vector<Z> res(size() + 1);
        for (int i = 0; i < size(); ++i) {
            res[i + 1] = a[i] / (i + 1);
        }
        return Poly(res);
    }
    Poly inv(int m) const {
        Poly x{a[0].inv()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {
        return (deriv() * inv(m)).integr().modxk(m);
    }
    Poly pow(int k,int m) const {
    	return (log(m)*k).exp(m);
    	/*Poly ret({1});
    	Poly cur(*this);
    	while(k){
    		if(k&1)ret=(ret*cur).modxk(m);
    		if(k>>=1)cur=(cur*cur).modxk(m);
    	}
    	return ret;*/
    }
    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    std::vector<Z> eval(std::vector<Z> x) const {
        if (size() == 0) {
            return std::vector<Z>(x.size(), 0);
        }
        const int n = std::max(int(x.size()), size());
        std::vector<Poly> q(4 * n);
        std::vector<Z> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

}
using jiangly::Poly;
const int N=1000005;
int n;
Z fac[N],ifac[N];
Z C(int n,int m){
	if(m<0||n<m)return Z(0);
	return fac[n]*ifac[m]*ifac[n-m];
}
Z Cat(int n){
	return fac[n*2]*ifac[n]*ifac[n+1];
}
Poly base,tmp;
Poly gen(int n){
	Poly ret=(base.modxk(n+1)*((tmp.modxk(n+1)*(n+1)).exp(n+1))).modxk(n+1);
	ret.resize(n+1);
	reverse(ret.a.begin(),ret.a.begin()+n+1);
	return ret;
}
int a[N];
Poly sol(int l,int r){
	if(l==r){
		return gen(a[l]);
	}
	int mid=(l+r)>>1;
	return sol(l,mid)*sol(mid+1,r);
}
int main(){
#ifdef xay5421
	freopen("a.in","r",stdin);
#endif
	fac[0]=1;
	rep(i,1,N-1)fac[i]=fac[i-1]*i;
	ifac[N-1]=fac[N-1].inv();
	per(i,N-1,1)ifac[i-1]=ifac[i]*i;
	rd(n);
	rep(i,1,n)rd(a[i]);
	{
		const int n=*max_element(a+1,a+::n+1);
		Poly g=((Poly({1,2})-Poly({1,P-4}).sqrt(n+1))*Poly({4,2}).inv(n+1)).modxk(n+1);
		base=g.deriv(),tmp=g.divxk(1).inv(n+1).log(n+1);
	}
	Poly ret(sol(1,n));
	Z ans=0;
	rep(i,3,ret.size()-1)ans+=Cat(i-2)*ret[i];
	printf("%d\n",ans.val());
	return 0;
}
```

---

## 作者：feecle6418 (赞：0)

先假设最终每个点都必须连边，这时方案数是
$$
\sum_{b_1,b_2,\dots,b_n}Cat(S-\sum b_i)\prod_{i}(-1)^{b_i}\binom{all_i-b_i}{b_i}
$$
$Cat(n)$ 表示 $n$ 边形三角剖分数。最终枚举每条边上选了几条小边，然后枚举每条边上真正用了 $a_i$ 个：
$$
\sum_{a_1,a_2,\dots,a_n}\sum_{b_1,b_2,\dots,b_n}Cat(\sum a_i-\sum b_i)\prod_{i}(-1)^{b_i}\binom{a_i-b_i}{b_i}\binom{all_i-1}{a_i-1}
$$
注意到只要对于每种 $a_i-b_i$ 预处理出后面的东西就行了。枚举 $a-b=i,b=j$，
$$
f(i)=\sum_{j}\binom{i}j\binom{all-1}{i+j-1}(-1)^j
$$
然而这里面与 $i,j,i-j,i+j$ 四个东西有关，没法直接卷。

用一些技巧性的东西：给 $\binom ij$ 凑一个 $x^j$，给 $\binom{all-1}{all-i-j}$ 凑一个 $x^{all-i-j}$：
$$
[x^i]F(x)=[x^{all-i}]\sum \binom ij(-x)^j \binom{all-1}{all-i-j}x^{all-i-j}
$$
也就是求 $[x^{all-i}](1-x)^i\times (1+x)^{all-1}$。设 $g(i)=\binom{all-1}{all-i}$，写得好看一点：
$$
[x^{all}](x-x^2)^i\times (1+x)^{all-1}
$$
$$
=\sum_j g(j)[x^j](x-x^2)^i
$$
使用转置原理，把 $(1+x)^{all-1}$ 看成输入，最终得到 $f()$；转置系数矩阵之后，考虑以下过程。
$$
g(j)=[x^j]\sum_i f(i)(x-x^2)^i=[x^j]F(x-x^2)
$$
也即转置之后是把 $F(x)\to F(x-x^2)$。这个变换的转置又需要将其拆解为“基本”的步骤，配方，$x-x^2=-(x-1/2)^2+1/4$。也即做了以下事情，注意一切变化都是对 $x$ 本身进行的！

- $F(x)\to F(x+1/4)$
- $F(x+1/4)\to F(-x+1/4)$
- $F(-x+1/4)\to F(-(x^2)+1/4)$，注意转置后仅仅是系数矩阵转置（$i\to i/2$），不代表这一步之前 $2i+1$ 位置必须是 0
- $F(-(x^2)+1/4)\to F(-(x-1/2)^2+1/4)$

不显然的地方是 $F(x)\to F(x+y)$ 的转置，原来 $b_i=\sum_{j\ge i}a_jy^{j-i}\binom ji$，现在 $b_i=\sum_{j\le i}a_j\binom ijy^{i-j}$（通过系数矩阵转置容易看出），可以发现转置之后甚至比原来清爽（没有差卷积了）。还要注意这里下标是没有范围的（系数矩阵是无限的！）为了不出问题，所有的运算要保留 $2\times all$ 位。

---

