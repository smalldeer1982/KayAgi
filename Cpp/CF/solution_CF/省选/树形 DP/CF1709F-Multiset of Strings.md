# Multiset of Strings

## 题目描述

You are given three integers $ n $ , $ k $ and $ f $ .

Consider all binary strings (i. e. all strings consisting of characters $ 0 $ and/or $ 1 $ ) of length from $ 1 $ to $ n $ . For every such string $ s $ , you need to choose an integer $ c_s $ from $ 0 $ to $ k $ .

A multiset of binary strings of length exactly $ n $ is considered beautiful if for every binary string $ s $ with length from $ 1 $ to $ n $ , the number of strings in the multiset such that $ s $ is their prefix is not exceeding $ c_s $ .

For example, let $ n = 2 $ , $ c_{0} = 3 $ , $ c_{00} = 1 $ , $ c_{01} = 2 $ , $ c_{1} = 1 $ , $ c_{10} = 2 $ , and $ c_{11} = 3 $ . The multiset of strings $ \{11, 01, 00, 01\} $ is beautiful, since:

- for the string $ 0 $ , there are $ 3 $ strings in the multiset such that $ 0 $ is their prefix, and $ 3 \le c_0 $ ;
- for the string $ 00 $ , there is one string in the multiset such that $ 00 $ is its prefix, and $ 1 \le c_{00} $ ;
- for the string $ 01 $ , there are $ 2 $ strings in the multiset such that $ 01 $ is their prefix, and $ 2 \le c_{01} $ ;
- for the string $ 1 $ , there is one string in the multiset such that $ 1 $ is its prefix, and $ 1 \le c_1 $ ;
- for the string $ 10 $ , there are $ 0 $ strings in the multiset such that $ 10 $ is their prefix, and $ 0 \le c_{10} $ ;
- for the string $ 11 $ , there is one string in the multiset such that $ 11 $ is its prefix, and $ 1 \le c_{11} $ .

Now, for the problem itself. You have to calculate the number of ways to choose the integer $ c_s $ for every binary string $ s $ of length from $ 1 $ to $ n $ in such a way that the maximum possible size of a beautiful multiset is exactly $ f $ .

## 说明/提示

In the first example, the three ways to choose the integers $ c_s $ are:

- $ c_0 = 0 $ , $ c_1 = 2 $ , then the maximum beautiful multiset is $ \{1, 1\} $ ;
- $ c_0 = 1 $ , $ c_1 = 1 $ , then the maximum beautiful multiset is $ \{0, 1\} $ ;
- $ c_0 = 2 $ , $ c_1 = 0 $ , then the maximum beautiful multiset is $ \{0, 0\} $ .

## 样例 #1

### 输入

```
1 42 2```

### 输出

```
3```

## 样例 #2

### 输入

```
2 37 13```

### 输出

```
36871576```

## 样例 #3

### 输入

```
4 1252 325```

### 输出

```
861735572```

## 样例 #4

### 输入

```
6 153 23699```

### 输出

```
0```

## 样例 #5

### 输入

```
15 200000 198756```

### 输出

```
612404746```

# 题解

## 作者：蒟蒻君HJT (赞：4)

一道比较简单的多项式计数题（~~这也能算计数？~~）但是场上 sb 了没看出来应该放在 01-trie 上做。

题意略。

把这个题目放在一个插入了所有 $[0,2^n-1]$ 中的二进制数的 01 trie 上考虑，发现可以把每个 $c_x$ 的限制放在数字 $x$ 往父节点连的那条边上。结合图片看一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6yolxktg.png)

蓝色的字母表示边权 $c_x$。

问题就转化为了，从根节点（第 $0$ 层）有无限多流量的水往下流，求流到第 $n$ 层的最大总流量是 $f$ 的方案数，且边权的范围是 $[0,k]$。

对于每个节点 $x$，用树形 dp 来计数。

首先你可以发现同一层的点的 dp 值肯定是全部相同的，也就是我们只需要对 $n$ 个点 dp 就可以了。

具体来说用 $dp_{x,i}$ 表示从 $x$ 的父亲往 $x$ 的方向最多可以流 $i$ 的流量的方案数。

初始化第 $n$ 层的节点 $x$ 的 dp 值：$dp_{x,i}=1,i\in [0,k]$。

从第 $j$ 层的节点 $s1,s2$（$j\in[2,n]$）往第 $j-1$ 层的节点 $x$ 转移的时候，考虑这个流量 $i$ 被什么限制：有可能是 $dp_{s1},dp_{s2}$，也可能是被 $c_x$ 限制。

所以有转移方程：$dp_{x,i}=\sum_{j+k>i}(dp_{s1,j}\cdot dp_{s2,k})+(k-i+1)\sum_{j+k=i}(dp_{s1,j}\cdot dp_{s2,k})$ 。注意 $s1$ 和 $s2$ 是完全等同的，所以把 $s1$ 对应的生成函数平方一下就可以了。

最后一点细节是第一层的节点 $x,y$ 往第 $0$ 层的答案转移，有 $Ans=\sum_{j+k=f}dp_{x,j}\cdot dp_{y,k}$。

用 NTT 进行多项式操作，时间复杂度是 $O(nk\log k)$。

代码如下：

```cpp
#include <bits/stdc++.h>
const int N = 524288, mod = 998244353, g = 3;
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
		x = mul(x, x);
		y >>= 1;
	}
	return r;
}
int rev[N];
void NTT(int *A, int limit, int on){
	for(int i = 1; i < limit; ++i) 
		rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (limit >> 1);
	for(int i = 0; i < limit; ++i) 
		if(i < rev[i]) std::swap(A[i], A[rev[i]]);
	for(int i = 2; i <= limit; i <<= 1){
		int t = Qpow(g, (mod - 1) / i);
		if(on == -1) t = Qpow(t, mod - 2);
		for(int j = 0; j < limit; j += i){
			int w = 1;
			for(int k = j; k < j + i / 2; ++k, w = mul(w, t)){
				int u = A[k], v = mul(A[k + i / 2], w);
				A[k] = add(u, v);
				A[k + i / 2] = minus(u, v);
			}
		}
	}
	if(on == -1){
		int u = Qpow(limit, mod - 2);
		for(int i = 0; i < limit; ++i) A[i] = mul(A[i], u); 
	}
	return ;
}
void work1(int *A, int limit){
	NTT(A, limit, 1);
	for(int i = 0; i < limit; ++i) A[i] = mul(A[i], A[i]);
	NTT(A, limit, -1);
	return ;
}
int n, k, f, dp[N];
signed main(){
	scanf("%d%d%d", &n, &k, &f);
	int limit = 1;
	while(limit < 2 * k + 1) limit <<= 1;
	for(int i = 0; i <= k; ++i) dp[i] = 1;
	for(int i = 1; i <= n; ++i){
		work1(dp, limit);
		int s = 0;
		for(int j = 2 * k + 1; j < limit; ++j) dp[j] = 0;
		if(i == n) break;
		for(int j = 2 * k; j >= 0; --j){
			int tmp = dp[j];
			if(j <= k)
			dp[j] = add(s, mul(dp[j], std::max(0, k - j + 1)));
			else dp[j] = 0;
			s = add(s, tmp);
		}
	}
	printf("%d\n", dp[f]);
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：3)

## 奇妙の翻译

一棵高度为 $n$ 的**满二叉树**（共 $2^{n+1}-1$ 个点，$2^{n+1}-2$ 条边），边从父亲指向儿子。

每条边的最大流量为 $[0,k]$ 内的整数，求有几种赋最大流量方案，使得以根为源点，所有叶子为汇点，最大流恰好为 $f$。

## 做法

设 $k$ 固定时答案为 $a(n,f)$，我们在这棵树的根之上加一条“叶柄”（边权也为 $[0,k]$ 之间的整数）后答案设为 $b(n,f)$（在 $f>k$ 时定义为 $0$），则
$$
b(n,f)=(k-f+1)\, a(n,f)+\sum_{i=f+1}^{2k}a(n,i)
$$
↑ 前提是 $f\le k$。
$$
a(n,f)=\sum_{i=0}^f b(n-1,i)\cdot b(n-1,f-i)\quad(*)
$$
$$
Ans=[f\le 2k]a(n,f)
$$
由于 $n$ 很小，所以我们的瓶颈就在上面 $(*)$ 柿子。

设多项式
$$
A(x)=\sum_{i=0}^{2k}a(n,i)x^i 
\quad
B(x)=\sum_{i=0}^kb(n-1,i)x^i 
$$
由 $(*)$ 柿子得到
$$
A=B^2
$$
发现就是一个 simple 的多项式平方，直接 NTT 解决。

时间复杂度 $O(nk\log k)$，较为卡常。（我 TLE 了三发 qwq 罚时吃饱）

## Code

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define ll long long
const ll mod=998244353;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
const int V=1<<19;
int tax[V];
ll w[V+1];
inline void mktax(int L){For(i,0,(1<<L)-1) tax[i]=(tax[i>>1]>>1)|((i&1)<<(L-1));}
inline void DFT(ll *a,int L){
	int n=1<<L,len;
	For(i,0,n-1) if(i<tax[i]) swap(a[i],a[tax[i]]);
	ll x,y;
	For(i,1,L){
		len=(1<<i);
		for(int j=0;j<n;j+=len) For(k,0,(len>>1)-1){
			x=a[j+k];
			y=a[j+k+(len>>1)]*w[k*(n/len)]%mod;
			a[j+k]=(x+y)%mod;
			a[j+k+(len>>1)]=(x-y+mod)%mod;
		}
	}
}
inline void IDFT(ll *a,int L){
	int n=1<<L,d=pw(n,mod-2);
	reverse(a+1,a+n);
	DFT(a,L);
	For(i,0,n-1) (a[i]*=d)%=mod;
}
ll a[V],b[V];
int n,k,m,L;
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>k>>m;
	if(m>2*k){
		cout<<0<<endl;
		return 0;
	}
	L=0;
	while((1<<L)<=2*k+1) L++;
	mktax(L);
	ll wn;
	w[0]=1; 
	wn=pw(3,(mod-1)/(1<<L));
	For(j,1,(1<<L)) w[j]=w[j-1]*wn%mod;
	For(i,0,k) a[i]=i+1;
	For(i,k+1,2*k) a[i]=2*k-i+1;
	For(i,1,n-1){
		copy(a,a+2*k+1,b);
		a[2*k]=0;
		Rof(j,2*k-1,0) a[j]=(a[j+1]+b[j+1])%mod;
		For(j,0,k) (a[j]+=b[j]*(k+1-j)%mod)%=mod;
		fill(a+k+1,a+(1<<L),0);
		DFT(a,L);
		For(j,0,(1<<L)-1) a[j]*=a[j]%mod;
		IDFT(a,L);
	}
	cout<<a[m]<<endl;
return 0;}
```

---

## 作者：Purslane (赞：1)

# Solution

简单题。

首先考虑给定你 $\{c\}$，怎么求 $f$？

注意到串 $\rm X$ 出现次数为 $\rm X0$ 出现次数和 $\rm X1$ 出现次数之和。所以在 $\rm Trie$ 树上 $\rm DP$ 即可。

本题呢？设 $dp_{u,s}$ 为考虑节点 $u$ 的子树，$u$ 作为前缀出现了 $s$ 次的遍历过得 $\{c\}$ 的总数。

转移方程为：

$$
dp_{u,s} = \sum_{i=0}^k \sum_{j=0}^k dp_{lson,i}dp_{rson,j}([i+j > s] + [i+j=s] \times (k-s))
$$

注意到同一层所有节点的形态是一样的，所以它们 $dp_{u,*}$ 组成的生成函数都是一样的。

使用 $\rm NTT$ 加速即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e5+10,MOD=998244353; 
int n,k,m,F,rev[MAXN],f[MAXN],g[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void init(int l,int r,int mul) {
	if(l==r) return ;
	int mid=l+r>>1;
	rev[mid+1]+=mul,rev[r+1]-=mul;
	init(l,mid,mul<<1),init(mid+1,r,mul<<1);
	return ;	
}
void ntt(int *f,int op) {
	ffor(i,0,m-1) if(rev[i]>i) swap(f[i],f[rev[i]]);
	int len=1,lst;
	while(len<m) {
		lst=len,len<<=1;
		int omega=qpow(3,(MOD-1)/len);
		if(op==-1) omega=qpow(omega,MOD-2);
		ffor(i,0,m/len-1) {
			int l=i*len,tmp=1;
			ffor(i,l,l+lst-1) {
				int x=f[i],y=f[i+lst];
				f[i]=(x+y*tmp)%MOD,f[i+lst]=(x-y*tmp)%MOD,tmp=tmp*omega%MOD;
			}
		}
	}
	if(op==-1) {
		int inv=qpow(m,MOD-2);
		ffor(i,0,m-1) f[i]=f[i]*inv%MOD;
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>F,m=(1<<19);
	init(0,m-1,1); ffor(i,1,m) rev[i]+=rev[i-1];
	ffor(i,0,k) f[i]=1;
	ffor(i,1,n) {
		ntt(f,1);
		ffor(j,0,m-1) g[j]=f[j]*f[j]%MOD;
		ntt(g,-1);
		int suf=0;
		if(i!=n) {
			roff(j,m-1,0) {
				suf=(suf+g[j])%MOD;
				if(j<=k) g[j]=(g[j]*(k-j)+suf)%MOD;	
				else g[j]=0;
			}
			ffor(j,0,m-1) f[j]=g[j];
		}
		else cout<<(g[F]%MOD+MOD)%MOD;
	}
	return 0;
}
//雨下整夜，我的愛溢出就像雨水 
```

说句闲话，这个 $\rm C++17$ 真的有点慢了，是不是没开 $\rm O2$？

---

## 作者：EuphoricStar (赞：0)

考虑若确定了所有 $c_s$，如何计算集合最大大小。

下文令原题面中的 $f$ 为 $m$。

发现我们可以类似倒推地确定。比如若 $n = 3$，$c_{00} = \min(c_{000}, c_{001})$，$c_{01} = \min(c_{010}, c_{011})$，$c_{10} = \min(c_{100}, c_{101})$，$c_{11} = \min(c_{110}, c_{111})$，$c_0 = \min(c_{00}, c_{01}), c_1 = \min(c_{10}, c_{11})$。最大集合大小就是 $c_0 + c_1$。

放到一棵满二叉树上考虑（可以理解为 01-Trie），我们有 $f_u = \min(f_u, f_{ls_u} + f_{rs_u})$。

考虑计数。设 $g_{i, j}$ 自底向上第 $i$ 层结点，$f_u = j$ 的方案数。转移枚举 $f_u$ 还是 $f_{ls_u} + f_{rs_u}$ 取到最小值，有：

$$g_{i, j} = (\sum\limits_{x + y \ge j} g_{i - 1, x} g_{i - 1, y}) + (k - j) \sum\limits_{x + y = j} g_{i - 1, x} g_{i - 1, y}$$

加法卷积计算 $h_j = \sum\limits_{x + y = j} g_{i - 1, x} g_{i - 1, y}$，有：

$$g_{i, j} = (\sum\limits_{p \ge j} h_p) + (k - j) h_p$$

可以前缀和计算。

答案即为 $\sum\limits_{x + y = m} g_{n, x} g_{n, y}$。

时间复杂度 $O(nk \log k)$。

[code](https://codeforces.com/problemset/submission/1709/233028055)

---

