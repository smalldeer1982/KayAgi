# [ABC315Ex] Typical Convolution Problem

## 题目描述

给定一个长为 $n$ 的序列 $a$，按如下方法计算 $f(x)$：

- $f(0)=1$;
- 当整数 $m\in[1,n]$ 时，$f(m)=a_m\times (\displaystyle\sum_{i+j\lt m} f(i)\times f(j))$。

对于每个整数 $i\in[1,n]$，计算 $f(i)$ $\bmod$ $998244353$ 的值。

## 说明/提示

#### 数据规模与约定

$1\le n\le 2\times 10^5$，$a_i\in[0,998244352]$。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
1 6 48 496 6240```

## 样例 #2

### 输入

```
3
12345 678901 2345678```

### 输出

```
12345 790834943 85679169```

# 题解

## 作者：zac2010 (赞：5)

### 解题思路

首先观察到这个形式，容易发现它和常规的卷积不同点就在于：题目给出的求和定义中，$\sum$ 符号下面的式子是 $i+j<N$ 求和而不是 $i+j=N$。

为了方便计算，我们引入：

$$
G_n=\sum_{i+j<N}F_iF_j
$$

我们发现，假设所有 $F_{1\sim{i-1}}$ 已经求解完毕了，那么我们就可以通过之前的量算出 $G_i$，再转而去乘上 $A_n$ 得到 $F_i$。

模拟题意的过程是 $O(N^3)$，而利用 $F,G$ 相互递推这个做法是 $O(N^2)$ 的。这都没法满足数据范围需要的时间要求。

这时候，我们根据由小推大的性质想到了利用 $\text{CDQ}$ 分治去优化这个 $O(N^2)$ 的算法。具体的，就是分治 $\text{NTT}$。为了更好地理清这个问题，我们不妨再来看一下 $\text{CDQ}$ 分治的模板框架：
* 当前区间长度为 $1$

	直接进行一些特殊的处理。
    
* 当前区间 $[l,r]$ 长度 $>1$

	1. 递归处理左边区间 $[l,mid]$
   2. 计算左边区间对右边的贡献
   3. 递归处理右边区间 $[mid+1,r]$。

我们在长度为 $1$ 的情况下就按照暴力中的处理方式来做，长度大于 $1$ 就先递归做区间，中间利用 $\text{NTT}$ 卷一下处理对右边的贡献，最后递归右边就行了。

值得一提的是，中间卷积处理贡献时，我们要分别计算 $i\in[l,mid]$ 时的贡献，$j\in[l,mid]$ 时的贡献（根据题意，如果两者都满足自然也是要算两遍），且 $l=0$ 时特殊处理一下即可。

## 代码
```cpp
#include <bits/stdc++.h>
#include "atcoder/convolution"
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
using atcoder::convolution;
using mint = atcoder::modint998244353;
constexpr int N = 2e5 + 10;
int n, A[N]; mint F[N], G[N];
void Solve(int l, int r){
    if(l == r){
        if(l) F[l] = (G[l] = G[l - 1] + F[l]) * A[l];
        return;
    }
    int mid = l + r >> 1; Solve(l, mid);
    if(!l){
        auto T = convolution(vector<mint>(F, F + mid + 1), vector<mint>(F, F + mid + 1));
        FL(i, mid + 1, r) F[i] += T[i - 1];
    }
    else{
        auto T = convolution(vector<mint>(F + l, F + mid + 1), vector<mint>(F, F + r - l + 1));
        FL(i, mid + 1, r) F[i] += T[i - l - 1] * 2;
    }
    Solve(mid + 1, r);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n; FL(i, 1, n) cin >> A[i];
    F[0] = 1, Solve(0, n);
    FL(i, 1, n) cout << F[i].val() << " \n"[i == n];
    return 0;
}
```


---

## 作者：Reunite (赞：2)

自己只会 $n\sqrt {n\log n}$ 的做法，题解的双 $\log$ 又看不懂，唉。

---

如果记 $s_i=\sum_{j\le i}f_j$，那 $f_i$ 就可以直接写成 $s,f$ 的卷积，这很像分治 NTT，但是不好的是这里的 $s_i$ 是半在线的，无法直接搞。于是考虑分块做法，设块长为 $B$，从左到右逐块计算。

我们希望把贡献答案的二元组拆成两部分，一部分是 $x,y<lf_b$ 的，另一部分是存在一个在当前块当中的。每次对于一个整块，把前面的 $f,s$ 一次卷积重构，这样第一部分的可以 $O(n\log n)-O(1)$，对于第二部分，我们暴力枚举一个位置 $x$，然后利用已处理的前缀和 $O(B)$ 算答案。

复杂度是 $O(B^{-1}n^2\log n+nB)$，平衡一下即可 $n\sqrt{n\log n}$，$B$ 需要开到 $2000$。

---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 998244353
#define G0 332748118
using namespace std;

int n,B=2000;
int lf[2005];
int rt[2005];
int a[200005];
int f[200005];
int s[200005];
int bl[200005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int w[524300];
int aa[524300];
int bb[524300];
int rev[524300];

inline int calc(int x,int k){
	int tmp=1;
	while(k){
		if(k&1) tmp=1ll*tmp*x%mod;
		x=1ll*x*x%mod;
		k>>=1;
	}
	return tmp;
}

inline void ntt(int *a,int op,int n){
	for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int len=2,k=1;len<=n;len<<=1,k<<=1){
		int wn=calc(op==1?3:G0,(mod-1)/len);
		for(int i=w[0]=1;i<len;i++) w[i]=1ll*w[i-1]*wn%mod;
		for(int i=0;i<n;i+=len){
			for(int j=0;j<k;j++){
				int x=a[i+j],y=1ll*a[i+j+k]*w[j]%mod;
				a[i+j]=(x+y)%mod;
				a[i+j+k]=(x-y+mod)%mod;
			}
		}
	}
	int inv=calc(n,mod-2);
	if(op==-1) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%mod;
	return ;
}

inline void NTT(int *a,int *b,int lim){
	for(int i=1;i<lim;i++) rev[i]=rev[i>>1]>>1|(i&1?lim>>1:0);
	ntt(a,1,lim),ntt(b,1,lim);
	for(int i=0;i<lim;i++) a[i]=1ll*a[i]*b[i]%mod;
	ntt(a,-1,lim);
	return ;
}

signed main(){
	in(n);
	for(int i=1;i<=n;i++) in(a[i]),bl[i]=(i+B-1)/B;
	for(int i=1;i<=n;i++) rt[bl[i]]=i;
	for(int i=n;i>=1;i--) lf[bl[i]]=i;
	f[0]=s[0]=1;
	for(int b=1;b<=bl[n];b++){
		memset(aa,0,sizeof(aa));
		memset(bb,0,sizeof(bb));
		for(int i=0;i<lf[b];i++) aa[i]=f[i],bb[i]=s[i];
		for(int i=lf[b];i<=lf[b]+B;i++) bb[i]=bb[i-1];
		int lim=1;
		while(lim<=lf[b]*2+B) lim<<=1;
		NTT(aa,bb,lim);
		for(int id=lf[b];id<=rt[b];id++){
			f[id]=aa[id-1];
			for(int i=lf[b];i<id;i++){
				int R=id-i-1;
				if(R<0) break;
				if(R<=lf[b]-1) (f[id]+=1ll*f[i]*2%mod*s[R]%mod)%=mod;
				else (f[id]+=1ll*f[i]*(s[R]+s[lf[b]-1])%mod)%=mod;
			}
			f[id]=1ll*f[id]*a[id]%mod;
			s[id]=(s[id-1]+f[id])%mod;
		}
	}
	for(int i=1;i<=n;i++) printf("%lld ",f[i]);

	return 0;
}
```

---

## 作者：__ycx2010__ (赞：2)

### 思路

设 $g_i = \sum_{j + k = i} f_j f_k$，那么 $f_i = a_i \sum_{j < i} g_j$。

如果 $f,g$ 互推，则有一个 $O(n^2)$ 的算法。

考虑分治 FFT，如果要求的是 $g_7$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xjnaugou.png)

将 $g_7$ 的之分解为四类，即 $[0,3]$，$[4,5]$，$[6, 6]$，$[7, 7]$ 对其的贡献，也就是所有左边对右边的贡献。

若当前递归到的区间为 $[l,r]$，则做三个操作：

1. 递归 $[l,mid]$
2. 计算 $[l,mid]$ 对 $[mid + 1, r]$ 的贡献
3. 递归 $[mid + 1, r]$

仔细思考一下，发现当 $l = 0$ 时，计算左对右的贡献时，会有一部分 $f$ 还没有计算出，而那一段就是除了 $l = 0$ 的区间以外的区间，所以计算贡献时，若 $l > 0$ 则有一个为 $2$ 的常数。

### 代码

感觉代码更好理解。

```cpp
#include <bits/stdc++.h>
#include "atcoder/convolution"

using namespace std;
using atcoder::convolution;
using mint = atcoder::modint998244353;

const int N = 1200010;
const double PI = acos(-1);
int n, t[N];
mint f[N], g[N];

void solve(int l, int r) {
	if (l == r) {
		if (!l) return;
		return f[l] = g[l - 1] * t[l], g[l] = g[l] + g[l - 1] + 2 * f[l], void();
	}
	int mid = l + r >> 1;
	solve(l, mid);
	auto T = convolution(vector<mint>(f + l, f + mid + 1), vector<mint>(f, f + r - l + 1));
	for (int i = mid + 1; i <= r; i ++ ) g[i] = g[i] + T[i - l] * ((l > 0) ? 2 : 1);
	solve(mid + 1, r);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &t[i]);
	f[0] = 1; g[0] = 1;
	solve(0, n);
	for (int i = 1; i <= n; i ++ ) printf("%d ", f[i].val());
	return 0;
}

```

---

## 作者：Nightingale_OI (赞：1)

## AT_abc212_h

### 大意

给定数组 $a_n$，求 $F_{1\sim n}$：

+ $F_0=1$
+ $F_i=a_i\times\sum_{j+k<i}F_j\times F_k\quad(i>0)$

### 思路

看到题目开了 $5.00s$，$n$ 是 $2\times10^5$ 级别的，可以考虑分块再多项式。

部分的多项式题加入分块思想就会变得很无脑，比如这题。

令 $G_i=\sum_{j+k=i}F_j\times F_k$，则 $F_i=a_i\times\sum_{j<i}G_j$。

若我们对 $G_i$ 前缀和，就有 $F_i=a_i\times G_{i-1}$。

每 $B$ 个数为一块（第一块不包括 $F_0$），一共分成 $\dfrac{n}B$ 块。

先算出第一块内所有答案，复杂度 ${\rm O}(B^2)$，这一步是不必要的，但写了可能会省分类讨论。

知道 $F_{0\sim K}$，考虑算 $F_{K+1\sim K+B}$。

记 $X=F\mod x^{K+1}$，将 $X^2$ 对 $G_{K\sim K+B-1}$ 的贡献算上，总复杂度 ${\rm O}(\dfrac{n^2\log n}B)$。

我们顺着求 $G_{K\sim K+B-1}$，考虑现在的 $G_i$ 差了什么，发现差的是：

$$\sum_{j+k=i\text{且}(j>K\text{或}k>K)}F_j\times F_k$$

可以 $O(B)$ 计算，算出 $G_i$ 就知道 $F_{i+1}$，刚好又能继续去算 $G_{i+1}$，总复杂度 ${\rm O}(nB)$。

综上 $B=\sqrt{n\log n}$ 有最优复杂度 ${\rm O}(n\sqrt{n\log n})$，足以通过此题。

### 代码

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
#define I atcoder::modint998244353
#define f(i,j,k) for(int i=j;i<=k;++i)
int n,m,s,l,a[1<<21];
I F[1<<21],G[1<<21];
void T(int l,int r){
	f(i,l,r){
		f(j,l+1,i)G[i]+=F[j]*F[i-j]*(i==j*2||i-j>l?1:2);
		F[i+1]=a[i+1]*G[i];G[i+1]+=G[i];
	}
}
main(){
	cin>>n;
	f(i,1,n)cin>>a[i];
	*F=*G=1;T(0,m=s=sqrt(n*42));
	for(++s;s<n;s=l+1){
		vector<I>X(F,F+s+1);
		X=convolution(X,X);l=s+m;
		f(i,s,l)G[i]+=X[i];T(s,l);
	}
	f(i,1,n)cout<<F[i].val()<<" ";
}
```

---

## 作者：Caii (赞：1)

模板题链接：[ABC315Ex](https://atcoder.jp/contests/abc315/tasks/abc315_h)

设$ G_n=\sum_{i+j=n}F_iF_j$，则 $F_i=A_i\sum_{j<i}G_j$，因此问题变成求 $G$

考虑计算 $F_iF_j$ 的时机，显然必须在 $F_i, F_j$ 都计算完成之后才能进行，并且其值在 $G_n$ 中，必须要在 $F_{n+1}$ 计算之前完成。但是直接计算是 $O(n^2)$ 的，因此考虑优化，延后部分 $F_iF_j$ 的计算时机，使得可以借助 FFT 优化，具体的计算实际见下表，每次计算一个块。

![](https://cdn.luogu.com.cn/upload/image_hosting/rf04o5yh.png)

具体的，对于每个 $k$，考虑 $k+2$，如果 $k+2$ 是 $2^t$ 的倍数，则有计算时机为 $k$ 的大小为 $2^t\times 2^t$ 的块。

时间复杂度: $O(n\log^2n)$

代码 EMACS 中复制出来的，需要代码的自己调缩进。

```cpp
#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

struct dat {
  int x, y;
  bool operator < (const dat &o) const {
    return y != o.y ? y < o.y : x < o.x;
  }
};

const int N = 500 + 7;
const int G = 3;
const int M = 1 << 19;
const int MOD = 998244353;

int ome[M], ivo[M], rev[M];
int n, g[M], f[M], v[M], a[M], b[M], t[M];

int pow(int x, int y) {
  int ret = 1;
  while(y) {
    if(y & 1)
      ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
    y >>= 1;
  }
  return ret;
}

void ntt(int *a, int l, int *o) {
  for(int i = 0; i < l; ++i)
    if(rev[i] < i)
      std::swap(a[rev[i]], a[i]);
  for(int i = 1; i < l; i <<= 1)
    for(int j = 0; j < l; j += i << 1)
      for(int k = 0; k < i; ++k) {
	int t = 1LL * a[i + j + k] * o[M / 2 / i * k] % MOD;
	a[i + j + k] = (a[j + k] + MOD - t) % MOD;
	a[j + k] = (a[j + k] + t) % MOD;
      }
}

void solve(int k) {
  g[k] = (g[k] + 2LL * f[k]) % MOD;
  for(int i = 2; ; i <<= 1) {
    if((k + 2) % i != 0)
      break;
    int l = i << 1;
    for(int j = 0; j < i; ++j) {
      a[j] = f[i - 1 + j];
      b[j] = f[k - i + 1 + j];
    }
    std::fill(a + i, a + l, 0);
    std::fill(b + i, b + l, 0);
    for(int j = 1; j < l; ++j)
      rev[j] = rev[j >> 1] >> 1 | ((j & 1) * i);
    ntt(a, l, ome);
    ntt(b, l, ome);
    for(int j = 0; j < l; ++j)
      a[j] = 1LL * a[j] * b[j] % MOD;
    ntt(a, l, ivo);
    int x = pow(l, MOD - 2);
    for(int j = 0; j < l; ++j)
      a[j] = 1LL * a[j] * x % MOD;
    for(int j = 0; j < l; ++j)
      if(k + 2 != i * 2)
	g[k + j] = (g[k + j] + 2LL * a[j]) % MOD;
      else
	g[k + j] = (g[k + j] + a[j]) % MOD;
  }
}

int main() {

  int x = pow(G, (MOD - 1) / M);
  int y = pow(x, MOD - 2);
  ome[0] = ivo[0] = 1;
  for(int i = 1; i < M; ++i) {
    ome[i] = 1LL * ome[i - 1] * x % MOD;
    ivo[i] = 1LL * ivo[i - 1] * y % MOD;
  }

  scanf("%d", &n);
  for(int i = 1; i <= n; ++i)
    scanf("%d", &v[i]);

  f[0] = g[0] = 1;
  for(int i = 1; i <= n; ++i) {
    f[i] = 1LL * g[i - 1] * v[i] % MOD;
    solve(i);
    g[i] = (g[i] + g[i - 1]) % MOD;
  }

  for(int i = 1; i <= n; ++i)
    printf("%d ", f[i]);
  putchar(10);

  return 0;

}   

```


---

## 作者：Purslane (赞：0)

# Solution

设 $g_i = \sum_{x+y = i} f_x f_y$，则 $f_i = a_i \sum_{j < i} g_j$。

如果我们能像分治 NTT 一样算出 $g$ 那么这道题也是做完了。

执行 $\rm CDQ$ 分治，设流程是 $\text{solve}(l,r)$，表示**我们计算出了 $f_{l,l+1,\cdots,r}$**。

我们显然会执行递归：$\text{solve}(l,m)$，然后进行 $\text{solve}(m+1,r)$。**我们需要计算 $g_{m,m+1,\cdots,r-1}$，因此考虑 $f_{l,l+1,\cdots,r}$ 对它们的影响**。

不妨钦定 $f_{l,l+1,\cdots,r}$ 在乘的过程中，**下标比另一个元素大**。

事实上就是 $h_{i-l}=f_i$（$l \le i \le r$）和 $g_i = t_if_i$（$0 \le r-1-l$）进行卷积。

$t$ 的规定规则是：

1. 如果 $i < l$，则 $t_i=2$；
2. 否则，$t_i=1$。

很容易验证正确性。复杂度 $O(n \log^2 n)$。

Reunite 老师还给了一种十分简单无脑的的方法：对于一类复杂的在线卷积问题，可以考虑分块。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e6+10,MOD=998244353;
int n,a[MAXN],f[MAXN],g[MAXN],pre[MAXN];
namespace POLY {
	int rev[MAXN];
	int qpow(int base,int p) {
		int ans=1;
		while(p) {
			if(p&1) ans=ans*base%MOD;
			base=base*base%MOD,p>>=1;
		}
		return ans;
	}
	void ntt(int *f,int k,int op) {
		ffor(i,0,k-1) rev[i]=(rev[i>>1]>>1)|((k>>1)*(i&1));
		ffor(i,0,k-1) if(rev[i]>i) swap(f[i],f[rev[i]]);
		int len=1,lst=1;
		while(len<k) {
			lst=len,len<<=1;
			int omega=qpow(3,(MOD-1)/len);
			if(op==-1) omega=qpow(omega,MOD-2);
			ffor(i,0,k/len-1) {
				int l=i*len,r=l+len-1,tmp=1;
				ffor(j,l,l+lst-1) {
					int x=f[j],y=f[j+lst];
					f[j]=(x+tmp*y)%MOD,f[j+lst]=(x-tmp*y)%MOD,tmp=tmp*omega%MOD;
				}
			}
		}
		if(op==-1) {
			int inv=qpow(k,MOD-2);
			ffor(i,0,k-1) f[i]=f[i]*inv%MOD;	
		}
		return ;
	}
};
int x[MAXN],y[MAXN];
void cdq(int l,int r) {
	if(l==r) {
		if(l==0) return ;
		if(l!=1) pre[l-1]=pre[l-2];
		pre[l-1]=(pre[l-1]+g[l-1])%MOD;
		f[l]=a[l]*pre[l-1]%MOD;
		return ;
	}
	int mid=(l+r>>1),len=1;
	cdq(l,mid);
	while(len<(r-l-1)*2) len<<=1;
	ffor(i,0,len-1) x[i]=y[i]=0;
	ffor(i,l,mid) x[i-l]=f[i];
	ffor(i,0,min(mid,r-l-1)) if(i<l) y[i]=2*f[i]%MOD; else y[i]=f[i];
	POLY::ntt(x,len,1),POLY::ntt(y,len,1);
	ffor(i,0,len-1) x[i]=x[i]*y[i]%MOD;
	POLY::ntt(x,len,-1);
	ffor(i,mid,r-1) g[i]=(g[i]+x[i-l])%MOD;
	cdq(mid+1,r);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	f[0]=1,cdq(0,n);
	ffor(i,1,n) cout<<(f[i]%MOD+MOD)%MOD<<' ';
	return 0;
}
```

---

