# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9```

### 输出

```
20```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
4 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97```

### 输出

```
19200```

# 题解

## 作者：LightningUZ (赞：16)

题意都清楚吧

### 平方做法

要求排列数显然和一开始的顺序没有关系，想都不想先排个序（注意后面说的数组都是排好了序的）

然后考虑 $dp$：设 $f_i$ 表示到第 $i$ 个数的方案数。

仔细想想好像这排列的长度是固定的：必须要把 $\le \dfrac{a_i}{2}$ 的数加入进来，并且，更大的也加不进来。于是这个排列的长度就是 $\le \dfrac{a_i}{2}$ 的数个数，设为 $mx$（$mx$ 的含义可以理解为，最大的 $j$ 使得 $2a_j\le a_i$），再 $+1$ （算自己）

然后想怎么转移。枚举在前面放到哪个位置 $j$，这个方案数是 $f_j$，并且占用了 $mx_j+1$ 个位置；然后现在还剩下 $(n-1)-(mx_j+1)$ 个位置，放剩下的 $mx_i-(mx_j+1)$ 个数。这些放在 $a_i$ 后面。注意到，因为有 $a_i$ 的存在，它们咋放都行，然后就用 $A$ 来算了。

于是 

$$
f_i=\sum\limits_{j} f_j A_{n-mx_j-2}^{mx_i-mx_j-1}
$$

### 优化

注意到我们算 $A$ 的时候是： $\dfrac{n!}{(n-m)!}$

然后这个 $n,m$ 具有一个相同的 $-(mx_j+1)$，那么分母上就会约掉

注意到这一点，考虑来推推式子，变成：

$$
\dfrac{(n-mx_j-2)!}{(n-1-mx_i)!} f_j
$$

一部分只和 $j$ 有关，一部分只和 $i$ 有关，就前缀和优化就行了

复杂度 $O(n)$ （不算排序）

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Flandre_Scarlet
{
    #define N   5140
    #define mod 998244353
    #define int long long
    #define F(i,l,r) for(int i=l;i<=r;++i)
    #define D(i,r,l) for(int i=r;i>=l;--i)
    #define Fs(i,l,r,c) for(int i=l;i<=r;c)
    #define Ds(i,r,l,c) for(int i=r;i>=l;c)
    #define MEM(x,a) memset(x,a,sizeof(x))
    #define FK(x) MEM(x,0)
    #define Tra(i,u) for(int i=G.Start(u),v=G.To(i);~i;i=G.Next(i),v=G.To(i))
    #define p_b push_back
    #define sz(a) ((int)a.size())
    #define all(a) a.begin(),a.end()
    #define iter(a,p) (a.begin()+p)
    int I() {char c=getchar(); int x=0; int f=1; while(c<'0' or c>'9') f=(c=='-')?-1:1,c=getchar(); while(c>='0' and c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar(); return ((f==1)?x:-x);}
    template <typename T> void Rd(T& arg){arg=I();}
    template <typename T,typename...Types> void Rd(T& arg,Types&...args){arg=I(); Rd(args...);}
    void RA(int *p,int n) {F(i,1,n) *p=I(),++p;}
    int n,a[N];
    void Input()
    {
        n=I(); F(i,1,n) a[i]=I();
    }
    int fc[N],fi[N],iv[N]; // 阶乘，阶乘逆元，逆元
    void Init()
    {
        fc[0]=fc[1]=fi[0]=fi[1]=iv[1]=1;
        F(i,2,n) iv[i]=iv[mod%i]*(mod-mod/i)%mod,fi[i]=fi[i-1]*iv[i]%mod,fc[i]=fc[i-1]*i%mod;
    }
    int qpow(int a,int b,int m=mod) {int r=1; while(b) {if (b&1) r=r*a%m; a=a*a%m,b>>=1;} return r;}
    int A(int n,int m) {return fc[n]*fi[n-m]%mod;}

    int f[N],len[N];
    int sum[N];
    void Soviet()
    {
        Init();

        sort(a+1,a+n+1);
        if (a[n]<a[n-1]*2) {puts("0"); return;}
        int mx=0;
        f[0]=1; sum[0]=fc[n-1]%mod;
        F(i,1,n)
        {
            while(2*a[mx]<=a[i] and mx<=n) ++mx; --mx;
            len[i]=mx+1;
            // len: 排列长度=mx+1

            // F(j,0,mx) f[i]=(f[i]+f[j]*A(n-1-len[j],mx-len[j]))%mod;
            // ↑ 这个是暴力写法
            /*
            A(n-1-len[j],mx-len[j])*f[j]
            fi[n-1-mx]  * fc[n-1-len[j]]*f[j]
            ↑ 只和i有关    ↑ 只和j有关
            */
            f[i]=(f[i]+fi[n-len[i]]*sum[mx]%mod)%mod;
            sum[i]=(sum[i-1]+fc[n-1-len[i]]*f[i]%mod)%mod;
        }
        printf("%lld\n",f[n]);
    }
    void IsMyWife()
    {
        Input();
        Soviet();
    }
}
#undef int //long long
int main()
{
    Flandre_Scarlet::IsMyWife();
    getchar();
    return 0;
}
```

---

## 作者：George1123 (赞：12)


更木棒的体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/13891814.html)

---

## 题面

> [CF1437F Emotional Fishermen](https://www.luogu.com.cn/problem/CF1437F) 

> 给 $n$ 个数的序列 $a_i$，求有多少种 $n$ 个数的排列 $p_i$，使得 
> $$\frac{a_{p_i}}{\max_{j=1}^{i-1} a_{p_j}}\notin \left(\frac 12, 2\right)$$
> 答案膜 $998244353$。

> 数据范围：$2\le n\le 5000$。

---

## 题解


您会很高兴地发现当前 $a_{p_i}$ 大于前面最大值的总次数不会超过 $\log$ 次，可惜这没用。

但是考虑这个前缀最大值的序列，却可以发现这东西改变序列便是不同的。

**将 $a_i$ 排序** ，考虑用 $a_i$ 填满一个长度为 $n$ 的空位序列。

设 $f_i$ 表示当前最大值是 $a_i$ 的填充方案数，$lim_i$ 表示最大的 $j$ 满足 $2a_j\le a_i$。

先把这个最大值填当前的第一个空位。

由于最大值只会增大，对于所有 $2a_j\le a_i$ 必定满足 $2a_j$ 小于未来的最大值，所以可以先把 $2a_j\le a_i$ 的 **未使用的** 都填在最大值后面的空位上（不需要连续），顺序重要。

为什么不需要多设一维表示当前放的个数呢？因为 $f_i$ 放的个数必定是 $1+lim_i$，这个 $1$ 指的是自己。

**所以转移方程是：**

$$f_i=\sum_{j=0}^{lim_i} f_j\cdot A(n-2-lim_j,lim_i-lim_j-1)$$

这里 $n-2-lim_j$ 是总空位数减去 $f_j$ 用的空位数减去当前最大值 $1$ 个，$lim_i-lim_j-1$ 是 $2a_t\le a_i$ 的未使用的 $a_t$ 个数。

**时间复杂度 $\Theta(n^2)$，空间复杂度 $\Theta(n)$。**

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define bg begin()
#define ed end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define L(i,a,b) for(int i=(b)-1,i##E=(a)-1;i>i##E;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=5000;
int n,a[N],f[N+1],lim[N+1];

//Math
const int mod=998244353;
void fmod(int&x){x+=mod&x>>31;}
int Pow(int a,int x){
    int res=1; for(;x;x>>=1,a=1ll*a*a%mod)
    if(x&1) res=1ll*res*a%mod; return res;
}
int fac[N+1],ifac[N+1];
void math_init(){
    fac[0]=1; R(i,1,n+1) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[n]=Pow(fac[n],mod-2);
    L(i,0,n) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int A(int u,int v){
    if(u<0||v<0||v>u) return 0;
    return 1ll*fac[u]*ifac[u-v]%mod;
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n,math_init();
    R(i,0,n) cin>>a[i]; sort(a,a+n);
    R(i,0,n){
        int l=-1,r=i+1;
        while(r-l>1){
            int mid=(l+r)>>1;
            if(a[mid]*2>a[i]) r=mid;
            else l=mid;
        }
        lim[i+1]=r;
    }
    f[0]=1,lim[0]=-1;
    R(i,1,n+1)R(j,0,lim[i]+1)
        fmod(f[i]+=1ll*f[j]*A(n-2-lim[j],lim[i]-lim[j]-1)%mod-mod);
    // R(i,0,n+1) cout<<f[i]<<" ";cout<<'\n';
    if(lim[n]==n-1) cout<<f[n]<<'\n';
    else cout<<0<<'\n';
    return 0;
}
```
---

**祝大家学习愉快！**

---

## 作者：_quasar_ (赞：7)

考虑最后的序列一定是：

$$
\boxed{b_1}
\begin{matrix}\underbrace{\cdots\cdots\cdots}\\\leq \frac{b_1}{2}\end{matrix}
\boxed{b_2}
\begin{matrix}\underbrace{\cdots\cdots\cdots}\\\leq \frac{b_2}{2}\end{matrix}
\boxed{b_3}
\begin{matrix}\underbrace{\cdots\cdots\cdots}\\\leq \frac{b_3}{2}\end{matrix}
$$

的形式（其中 $a_1\leq \frac{a_2}{2}\leq \frac{a_3}{4} \cdots$） 。

将原序列从小到大排序，定义 $lim_i$ 为最大的 $j$ 满足 $a_j\leq \frac{a_i}{2}$ 。

然后令 $dp_i$ 表示 $a_i\in\{b_1,b_2,\cdots\}$ 时，当前序列已经放入了 $lim_i+1$ 个数的方案数。转移的时候考虑 $b$ 序列中上一个位置是多少即可。

如果上一个位置是 $j$，首先肯定是将 $a_i$ 放在当前序列的第一个非零位置，然后剩下的 $lim_i-lim_j-1$ 个数就是在后面的空位里面乱放了：

$$
dp_i=\sum dp_j\cdot{n-2-lim_i\choose lim_i-lim_j-1}\cdot (lim_i-lim_j-1)!
$$

时间复杂度 $O(n^2)$ 。

```cpp
inline void solve() {
    dp[0]=1,lim[0]=-1;
    lep(i,1,n) lep(j,0,lim[i]) {
        int res=mul(C(n-lim[j]-2,lim[i]-lim[j]-1),fac[lim[i]-lim[j]-1]);
        pls(dp[i],mul(dp[j],res));
    }
    lim[n]==n-1?printf("%d\n",dp[n]):puts("0");
}

int main() {
    init();

    IN(n);
    lep(i,1,n) IN(a[i]);
    std::sort(a+1,a+1+n);

    lep(i,1,n) {
        lim[i]=lim[i-1];
        while(2*a[lim[i]+1]<=a[i]) ++lim[i];
    }
    solve();
    return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

> [CF1437F Emotional Fishermen](https://www.luogu.com.cn/problem/CF1437F)

首先将 $a_i$ 从小到大排序。如果 $2a_{n - 1} > a_n$，无解。

否则观察一个合法排列 $p$ 的形态。根据题意，一些位置 $a_{p_i}$ 满足 $a_{p_i} \geq 2\max\limits_{j = 1} ^ {i - 1} a_{p_j}$。维护 $pre_i$ 表示 $\leq \dfrac {a_i} 2$ 的最大的 $a_j$ 对应的下标 $j$，限制等价于 $\max \limits_{j = 1} ^ {i - 1} p_j \leq pre_i$。

如果固定了这些特殊位置 $q_1 < q_2 < \cdots < q_k$，那么剩下来每个 $p_i$ 只需在 $q_{j + 1}$ 之后即可，其中 $q_j$ 是最大的满足 $q_j < 2p_i$ 的位置。

考虑对特殊位置 DP，钦定它们之间的顺序。设 $f_i$ 表示 $q_k = a_i$ 时，$i$ 以及所有 $\leq pre_i$ 的位置的排列方案数。

枚举 $j = q_{k - 1}$ 满足 $2a_j \leq a_i$，考虑转移。方案数的计算是这样的：根据定义，$f_j$ 时已经有 $pre_j + 1$ 个数的位置已经确定。为保证 $> pre_j$ 的位置全部放在 $i$ 之后，在往 $n$ 个位置填入 $(pre_j, pre_i]$ 除掉 $j$ 的所有位置 **之前**（根据 $2a_j \leq a_i$，显然 $j\in (pre_j, pre_i]$），$i$ 必须放在第一个空位上。因此，$(pre_j, pre_i]\backslash \{j\}$ 的贡献系数即从 $n - pre_j - 2$（减 $2$ 分别是 $j$ 和 $i$）当中选 $pre_i - pre_j - 1$ 个位置排列，
$$
A_{n - pre_j - 2} ^ {pre_i - pre_j - 1} = \dfrac{(n - pre_j - 2)!}{(n - pre_i - 1)!}
$$
分子只与 $j$ 有关，分母只与 $i$ 有关，容易用前缀和优化至除排序外线性，但并不必要。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 5e3 + 5;
constexpr int mod = 998244353;
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int n, a[N], p[N], f[N], fc[N], ifc[N];
int A(int n, int m) {return 1ll * fc[n] * ifc[n - m] % mod;}
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1], mod - 2);
  for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);
  if(a[n - 1] * 2 > a[n]) puts("0"), exit(0);
  for(int i = 2; i <= n; i++) {
    p[i] = p[i - 1];
    while(a[p[i] + 1] * 2 <= a[i]) p[i]++;
  }
  for(int i = 1; i <= n; i++) {
    f[i] = A(n - 1, p[i]);
    for(int j = 1; j < i; j++)
      if(a[j] * 2 <= a[i])
        f[i] = (f[i] + 1ll * f[j] * A(n - 2 - p[j], p[i] - 1 - p[j])) % mod;
  }
  cout << f[n] << endl;
  return 0;
}
/*
2022/6/16
start coding at 13:25
finish debugging at 13:33
*/
```

---

## 作者：Caicz (赞：4)

稍微想一下，容易发现最后构造出的合法序列大概长这样：
$$
p_1\dots p_2\dots p_3\dots p_4\dots
$$
其中 $p_j\ge 2p_i (j>i)$，同时对于所有的 $2a_i\le p_i$ 都可以填在 $p_i$ 的右边

我们设 $lim_i$ 表示最大的 $j ,2a_j\le a_i$

对 $a_i$ 排序后，很显然 $lim_i$ 是单调的，可以用双指针求

设 $f_i$ 表示当前最大值为 $a_i$ 时，合法序列的方案数，要保证 $f_i$ 表示的方案数是已经选了 $lim_i+1$ 数时的方案数，这样答案即为 $f_n$

考虑转移，可以得到
$$
f_i=\sum_{j=0}^{lim_i}f_j\times A(n-lim_j-2,lim_i-lim_j-1)
$$

后面的组合数表示当前剩下 $n-lim_j-2$ 个位置( $f_j$ 所占位置加上选了 $a_i$ )，需要将剩下$lim_i-lim_j-1$ 个数排列(选 $a_j$ 时选不了的数)

代码：

```cpp
#include<stdio.h>
#include<iostream>
#include<time.h>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=5005;
const int inf=0x3f3f3f3f;
const int p=998244353;
int n,a[maxn],lim[maxn];
ll f[maxn],mul[maxn],invmul[maxn];

#define getchar() (_1==_2&&(_2=(_1=_3)+fread(_3,1,1<<21,stdin),_1==_2)?EOF:*_1++)
char _3[1<<21],*_1=_3,*_2=_3;
inline int read(void)
{
	int num,sign=1;char c;
	while(!isdigit(c=getchar()))if(c=='-')sign=0;num=c-'0';
	while(isdigit(c=getchar()))num=(num<<1)+(num<<3)+c-'0';
	return sign?num:-num;
}
inline ll ksm(ll x,ll y){ll res=1;while(y){if(y&1)res=res*x%p;y>>=1,x=x*x%p;}return res;}
inline ll A(int x,int y)
{
	if(x<y||x<0||y<0)return 0;
	return mul[x]*invmul[x-y]%p;
}

signed main(void)
{
#ifndef ONLINE_JUDGE
	freopen("text.in","r",stdin);
#endif
	n=read();
	for(register int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+1+n);
	for(register int j=0,i=1;i<=n;++i)
	{
		while(2*a[j+1]<=a[i])++j;
		lim[i]=j;
	}
	if(lim[n]!=n-1)puts("0"),exit(0);
	mul[0]=invmul[0]=1;
	for(register int i=1;i<=n;++i)mul[i]=mul[i-1]*i%p,invmul[i]=ksm(mul[i],p-2);
	f[0]=1,lim[0]=-1;
	for(register int i=1;i<=n;++i)
		for(register int j=0;j<=lim[i];++j)
			f[i]=(f[i]+f[j]*A(n-lim[j]-2,lim[i]-lim[j]-1)%p)%p;
	cout<<f[n]<<endl;
	return 0;
}
```


---

## 作者：houzhiyuan (赞：3)

考虑先找出一个子序列，满足每个数都大于等于前一个数的两倍，然后再去放其他数。

先排序，我们从后向前放。

设 $dp_i$ 表示放到 $i$ 的答案是什么。

可以枚举一个 $j$ 使 $a_j\ge 2\times a_i$，然后考虑放 $i+1..j-1$ 区间中的数。

考虑现在取出的子序列是 $a_i,a_j,a_k$，那么 $i+1..j-1$ 区间中的数有些可以放到 $j$ 的后面，有些只能放在 $k$ 的后面。

考虑分成两类，记 $g_j$ 表示最后面的一个小于 $\frac{a_j}{2}$ 的位置。

分类，然后放就好了，细节比较多，讨论一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005,mod=998244353;
int n,a[N],f[N],dp[N],inv[N],g[N];
int kuai(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    if(a[n-1]*2>a[n])
    {
    	puts("0");
    	return 0;
	}
    dp[n]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[j]*2<=a[i])g[i]=j;
        }
    }
    f[1]=f[0]=1;
    for(int i=2;i<=n;i++)f[i]=1ll*f[i-1]*i%mod;//阶乘
    for(int i=0;i<=n;i++)inv[i]=kuai(f[i],mod-2);
    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<=n;j++){
            if(a[i]*2<=a[j]){
            	int num=1;
            	if(n-i-1>=n-g[j])num=1ll*num*f[n-i-1]%mod*inv[n-g[j]-1]%mod;//如果存在可以放到j后面的
				if(n-2-g[j]>=n-j){//如果只能放在k后面
					if(n-j)num=1ll*num*f[n-2-g[j]]%mod*inv[n-j-1]%mod;
					else num=1ll*num*f[n-2-g[j]]%mod;
				}
                dp[i]=(dp[i]+1ll*dp[j]*num%mod)%mod;
            }
        }
    }
    printf("%d",dp[0]);//答案是dp[0]，所有的数都放完了。
    return 0;
}
```

---

## 作者：7KByte (赞：3)

提供一个不用组合数的方法。

首先对 $a_i$ 从小到大排序。

我们定义状态 $f_{i,j}$ 表示当前最大值为 $a_i$，排列 $p$ 填了前面 $j$ 个方案数。

那么有初值 $f_{0,0}=1$。

依题意，我们有两种转移。

第一种是在排列后面加入一个高兴的人，枚举 $k$ 使得 $a_k\ge 2a_i$，有 $f_{i,j}\to f_{k,j+1}$ 。

第二种是加入一个难过的人，我们找到最大的 $k$ 使得 $2a_k\le a_i$，那么有 $f_{i,j-1}\to f_{i,j}$。考虑填入的是哪个人，我们一共有 $k$ 个人，然后有 $j-1$ 个人固定了，其中有一个人是 $i$ 不能算进去，所以在 $k-(j-2)$ 个人种选一个，转移就是 $f_{i,j}=(k-j+2)f_{i,j-1}$。

时间复杂度 $\mathcal{O}(N^2)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 5005
#define P 998244353
using namespace std;
int n,a[N],f[N][N],g[N][N];
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	f[0][0] = g[0][0] = 1;
	rep(i,1,n)g[i][0] = 1;
	int pre = 0;
	rep(i,1,n){
		while(a[pre + 1] * 2 <= a[i])pre++;
		rep(j,1,pre + 1){
			f[i][j] = (1LL * (pre - j + 2) * f[i][j - 1] + f[i][j]) % P;
			f[i][j] = (f[i][j] + g[pre][j - 1]) % P;
			g[i][j] = (g[i - 1][j] + f[i][j]) % P;
		}
	}
	printf("%d\n",f[n][n]);
	return 0;
}
```

---

## 作者：ppip (赞：2)

提供一个不太一样的 DP。

将 $a_i$ 从大到小排序，逐个插入。显然只需要满足每一次插入之后序列是合法的，因为只保留较大的数不会改变前缀最大值。

$a_i$ 可以插入的位置：之前的排列第一个数 $a_j\ge 2a_i$，则可以插入到序列的任何位置，否则可以插入到第一个 $\ge 2a_i$ 的数之后的任何位置。

考虑第二种情况 $a_j<2a_i$。设该排列的第二个位置为 $a_k$，则 $a_k>a_i$，所以 $2a_k>2a_i>a_j$。那么要使序列合法，只能是 $2a_i\le2a_j\le a_k$。所以此时 $a_i$ 可以插入从第二个位置后的任何位置。

依此，定义 $f_{i,j}$ 表示前 $i$ 个数以 $a_j$ 开头的排列个数。则转移为 $f_{i,i}=\sum [a_j\ge2a_i]f_{i-1,j}$，以及 $f_{i,j}=f_{i-1,j}\times(i-1-[a_j<2a_i])$。

复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N{5000},b6e0{998244353};
int f[N+5],a[N+5];
int main() {
	int n;cin>>n;
	for (int i{1};i<=n;++i) cin>>a[i];
	sort(a+1,a+1+n,greater<>());
	f[1]=1;
	for (int i{2};i<=n;++i)
		for (int j{1};j<i;++j)
			if (a[j]>=2*a[i]) {
				f[i]=(f[i]+f[j])%b6e0;
				f[j]=1LL*f[j]*(i-1)%b6e0;
			} else f[j]=1LL*f[j]*(i-2)%b6e0;
	int ans{0};
	for (int i{1};i<=n;++i) ans=(ans+f[i])%b6e0;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：intel_core (赞：2)

发现我们只需要抓住每次最大值变化的点 $\text{DP}$ ，这样其它的数就可以随便排了。

读入之后先将所有数排序。

令 $f_{i,j}$ 表示当前最大的数是 $a_i$，$\le \frac{a_i}{2}$ 的数还有 $j$ 个没用的方案数。

很明显，有一种横向转移是 $f_{i,j}+=f_{i,k}\times A_k^{k-j}(j<k)$，可以变化为 $f_{i,j} \times j!+=f_{i,k} \times k!$，记录前缀和即可。

还有纵向转移，设 $\le \frac{a_i}{2}$ 的数有 $s_i$ 个，若 $f_{i,j}$ 可以从 $f_{k,x}$ 转移过来，那么 $s_k-x=s_i-j+1$，这样就可以统计 $s_i-j$ 相同的 $f_{i,j}$ 的前缀和完成转移。

复杂度显然的 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e4+10;
#define int long long
int n,a[NR],sum[NR],now[NR],f[NR][NR],buc[NR],fac[NR],inv[NR];
const int MOD=998244353;
void upd(int &x,int y){x=(x+y)%MOD;}
int quickpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=(res*x)%MOD;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}
int Inv(int x){return quickpow(x,MOD-2);}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	for(int i=0;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[j]>=2*a[i])sum[j]++;
	if(a[n-1]*2>a[n]){
		puts("0");
		return 0;
	}
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%MOD,inv[i]=Inv(fac[i]);
	memset(buc,0,sizeof(buc));
	memset(f,0,sizeof(f));f[0][0]=1;
	memset(now,-1,sizeof(now));
	for(int i=1;i<=n;i++){
		for(int j=0;j<=sum[i];j++)
			while(now[j]<i-1&&a[now[j]+1]*2<=a[i]){
				now[j]++;
				if(sum[now[j]]>=j)upd(buc[j+1],f[now[j]][sum[now[j]]-j]);
			}
		int lcy=0;
		for(int j=n;j>=0;j--)
			upd(lcy,(buc[sum[i]-j]*fac[j])%MOD),f[i][j]=(lcy*inv[j])%MOD;
	}
	cout<<f[n][0]<<endl;
	return 0;
}
```

---

