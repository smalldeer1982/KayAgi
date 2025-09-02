# Rescue Nibel!

## 题目描述

Ori and Sein have overcome many difficult challenges. They finally lit the Shrouded Lantern and found Gumon Seal, the key to the Forlorn Ruins. When they tried to open the door to the ruins... nothing happened.

Ori was very surprised, but Sein gave the explanation quickly: clever Gumon decided to make an additional defence for the door.

There are $ n $ lamps with Spirit Tree's light. Sein knows the time of turning on and off for the $ i $ -th lamp — $ l_i $ and $ r_i $ respectively. To open the door you have to choose $ k $ lamps in such a way that there will be a moment of time when they all will be turned on.

While Sein decides which of the $ k $ lamps to pick, Ori is interested: how many ways there are to pick such $ k $ lamps that the door will open? It may happen that Sein may be wrong and there are no such $ k $ lamps. The answer might be large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

In first test case there are nine sets of $ k $ lamps: $ (1, 2, 3) $ , $ (1, 2, 4) $ , $ (1, 2, 5) $ , $ (1, 2, 6) $ , $ (1, 3, 6) $ , $ (1, 4, 6) $ , $ (2, 3, 6) $ , $ (2, 4, 6) $ , $ (2, 6, 7) $ .

In second test case $ k=1 $ , so the answer is 3.

In third test case there are no such pairs of lamps.

In forth test case all lamps are turned on in a time $ 3 $ , so the answer is 1.

In fifth test case there are seven sets of $ k $ lamps: $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , $ (4, 5) $ .

## 样例 #1

### 输入

```
7 3
1 7
3 8
4 5
6 7
1 3
5 10
8 9```

### 输出

```
9```

## 样例 #2

### 输入

```
3 1
1 1
2 2
3 3```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2
1 1
2 2
3 3```

### 输出

```
0```

## 样例 #4

### 输入

```
3 3
1 3
2 3
3 3```

### 输出

```
1```

## 样例 #5

### 输入

```
5 2
1 3
2 4
3 5
4 6
5 7```

### 输出

```
7```

# 题解

## 作者：tommymio (赞：13)

打 $Div2$ 的时候比 $C2$ 先开了这题，我真是太菜了/dk

**简要题意：从 $n$ 条线段中选出 $k$ 条令它们交集不为空的方案数。**

**前置知识：两条线段 $[l_1,r_1],[l_2,r_2]$ 交集不为空，当且仅当 $\max\{l_1,l_2\}\leq \min\{r_1,r_2\}$**

我们将 $n$ 条线段按 **左端点为第一关键字，右端点为第二关键字** 排序。对于第 $i$ 条线段计算它与前 $i-1$ 条线段满足条件的方案数，这样是不会重复计数的。由于存在交集即可，所以只要 $k-1$ 条线段与第 $i$ 条线段都存在交集，这和 $k$ 条线段（一定包括第 $i$ 条线段）存在交集是等价的。

当前的第 $i$ 条线段的左端点 $l_i$ ，在上式中的值一定为 $\max\{l_1,l_2\}$，因为我们已将左端点排序。所以我们只需令 $l_i\leq \min\{r_1,r_2\}$，则前 $i-1$ 条线段的 $r_i$ 必须 $\geq l_i$，用 $\text{BIT}$ 或者什么其他的小 $\texttt{trick}$ 维护一下前 $i-1$ 条线段中有多少线段的 $r$ 值 $\geq l_i$ 即可。设前 $i-1$ 条线段中有 $cnt_i$ 条线段与第 $i$ 条线段有交，那么答案为 $ans=\sum_{i=1}^n \binom{cnt_i}{k-1}\times[cnt_i\geq k-1]$

离散化、$O(n)-O(1)$ 组合数，这些小 $\texttt{trick}$ 就不提了（（（

**Show the Code**
```cpp
#include<cstdio>
#include<algorithm>
#define int ll
typedef long long ll;
const int mod=998244353;
int num,sum[600005],c[600005],fac[300005],inv[300005];
struct Segment {int l,r;} seg[300005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x) {for(;x<=num;x+=x&(-x)) ++sum[x];}
inline int ask(int x) {int res=0;for(;x;x-=x&(-x)) res+=sum[x]; return res;} 
inline int pow(int x,int p) {int res=1; for(;p;p>>=1) {if(p&1) res=res*x%mod; x=x*x%mod;} return res;}
inline bool cmp(const Segment &x,const Segment &y) {return x.l!=y.l? x.l<y.l:x.r<y.r;}
inline int binom(int n,int m) {return fac[n]*inv[n-m]%mod*inv[m]%mod;}
signed main() {
	int n=read(),k=read(),ans=0; fac[0]=inv[0]=1;
	for(register int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;
	for(register int i=1;i<=n;++i) inv[i]=pow(fac[i],mod-2);
	for(register int i=1;i<=n;++i) {c[++num]=seg[i].l=read();c[++num]=seg[i].r=read();}
	std::sort(c+1,c+1+num);
	num=std::unique(c+1,c+1+num)-c-1;
	std::sort(seg+1,seg+1+n,cmp);
	for(register int i=1;i<=n;++i) {
		seg[i].l=std::lower_bound(c+1,c+1+num,seg[i].l)-c;
		seg[i].r=std::lower_bound(c+1,c+1+num,seg[i].r)-c;
		int cnt=ask(num)-ask(seg[i].l-1); add(seg[i].r);
		if(cnt>=k-1) ans=(ans+binom(cnt,k-1))%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Karry5307 (赞：11)

### 题意

给定 $n$ 条线段，求出有多少种选出 $k$ 条的方法使得它们交集非空。

$\texttt{Data Range:}1\leq k\leq n\leq 3\times 10^5$

### 题解

本题是[这个题目](https://www.cnblogs.com/Karry5307/p/13617718.html)的弱化版。

~~所以 Rikka 可爱你们说对不对啊~~

注意到任意 $k$ 条线段的交集如果非空的话必定是一条线段，且这条线段的左端点一定是某条线段的左端点。

很明显先将线段离散化，然后去枚举相交的线段的左端点。

我们设 $p$ 是覆盖了某个位置的线段的数量，$s$ 是以这个位置为左端点的线段数量。由于我们选出的这 $k$ 条线段中至少要有一条以这个位置为左端点，所以容斥一下得到这个位置的答案为

$$\binom{p}{k}-\binom{p-s}{k}$$

注意到 $p$ 会在线段左端点和右端点 $+1$ 两个位置才会更新，所以需要在右端点也更新一次，注意到如果某个位置只有右端点的更新的话算出来的为 $0$，所以可以一并计算。

具体的实现方法就是开个桶就好了。

### 代码

```cpp
// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
#define PY return (void)puts("Yes")
#define PN return (void)puts("Yes")
#define P0 return (void)puts("0")
#define P1 return (void)puts("-1")
using namespace std;
// Typedefs
typedef int ll;
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=6e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
ll n,kk,tot,lst,sm,res;
ll l[MAXN],r[MAXN],u[MAXN],fact[MAXN],finv[MAXN],cntl[MAXN],cntr[MAXN];
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
inline void setup(ll cnt)
{
    fact[0]=fact[1]=finv[0]=1;
    for(register int i=1;i<=cnt;i++)
    {
        fact[i]=(li)fact[i-1]*i%MOD;
    }
    finv[cnt]=qpow(fact[cnt],MOD-2);
    for(register int i=cnt-1;i;i--)
    {
        finv[i]=(li)finv[i+1]*(i+1)%MOD;
    }
}
inline ll binom(ll m,ll n)
{
	if(m<0||n<0||m<n)
	{
		return 0;
	}
	return (li)fact[m]*finv[n]%MOD*finv[m-n]%MOD;
}
int main()
{
	n=read(),kk=read(),setup(3e5+10);
	for(register int i=1;i<=n;i++)
	{
		l[i]=read(),r[i]=read(),u[++tot]=l[i],u[++tot]=r[i];
	}
	sort(u+1,u+tot+1),tot=unique(u+1,u+tot+1)-u-1;
	for(register int i=1;i<=n;i++)
	{
		l[i]=lower_bound(u+1,u+tot+1,l[i])-u,cntl[l[i]]++;
		r[i]=lower_bound(u+1,u+tot+1,r[i])-u,cntr[r[i]+1]++;
	}
	for(register int i=1;i<=tot;i++)
	{
		lst=sm,sm+=cntl[i]-cntr[i];
		res=((li)res+binom(sm,kk)-binom(lst-cntr[i],kk)+MOD)%MOD;
	}
	printf("%d\n",res);
}
```

---

## 作者：STDquantum (赞：4)

感谢 `WanKupi` 大佬orz。

看到这题，可以考虑把区间拆成两个操作，左加右减（称为 减操作 和 加操作）。

由于答案只与区间相对关系有关，所以只考虑相对关系就可以了，没必要离散化。

然后对这些操作按横坐标排序，横坐标相同则先减后加。

最后把所有操作扫一遍，统计贡献。

设当前遍历到的点在 $g$ 个区间内（也就是 加操作个数 减去 减操作个数 为 $g$）。

减操作是不对答案产生贡献的。

而若有加操作，那么从当前点选出 $k$ 条的方案数是 $\left(\begin{array}{c}g\\k\end{array}\right)$，但是由于之前区间已经对答案产生了 $\left(\begin{array}{c}g-1\\k\end{array}\right)$ 的贡献了，所以要减去 $\left(\begin{array}{c}g-1\\k\end{array}\right)$，所以一个加操作对答案的贡献就是 $\left(\begin{array}{c}g\\k\end{array}\right)-\left(\begin{array}{c}g-1\\k\end{array}\right)$。

当然，为什么先减后加呢？因为若一个区间的右端点加一处和另一个区间的左端点重合，如果 $g$ 先加上 $1$，那么就相当于这一点有 $g+1$ 个区间了，然而只会有 $g$ 个。

时间复杂度 $\mathcal{O}(n\log n)$（最大复杂度卡在了排序上），可以通过本题。

```cpp
typedef long long ll;
const int N = 6e5 + 10, mod = 998244353; // 数组要开两倍

struct E {
  int x, sgn;
  E(int X = 0, int Sgn = 0) { x = X, sgn = Sgn; }
  inline friend bool operator<(const E &a, const E &b) {
    return a.x == b.x ? a.sgn < b.sgn : a.x < b.x; // 减操作排前面
  }
} a[N];

inline int fpm(int a, int b) {
  ll ans = 1;
  for (; b; b >>= 1, a = (ll)a * a % mod) {
    if (b & 1) (ans *= a) %= mod;
  }
  return ans;
}
int fac[N], inv[N];
inline void init(int n) {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
  inv[n] = fpm(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
  }
}

inline int C(int n, int m) {
  if (m > n || m < 0 || n < 0) return 0;
  return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int n, k;
ll ans;
inline void main() {
  read(n), read(k), init(n); // 预处理阶乘及其逆元
  for (int i = 1, l, r; i <= n; ++i) {
    read(l), read(r);
    a[i] = E(l, 1), a[i + n] = E(r + 1, -1); // 拆区间
  }
  sort(a + 1, a + 2 * n + 1);
  int tmp = 0; // 即为题解中的g
  for (int i = 1; i <= 2 * n; ++i) {
    if (a[i].sgn == -1) { // 先减后加
      --tmp;
    } else {
      ++tmp;
      (ans += C(tmp, k) - C(tmp - 1, k) + mod) %= mod; // 统计贡献
    }
  }
  write(ans);
}
```



---

## 作者：Mophie (赞：2)

# [CF1420D](https://www.luogu.com.cn/problem/CF1420D)题解

思考难度大于代码难度的一道题

看完题目，可以发现这题怎么和贪心这么像……

于是我就把它按照右边排了个序。

然后题目就变成了一个数组 $l$ 和一个排序好的数组 $r$ ，设每个 $i(1\leq i \leq n)$ 使得 $i+1\leq k \leq n$ 且 $l_k\leq r_i$ 的 $k$ 的个数为 $s_i$ ，求 $\sum^{n}_{i=1}\tbinom{k-1}{s_i}$

我们来思考一下改如何解决这个问题。

$$2 \space  minutes \space later...$$

我逐渐发现这么做是行不通的……

那么**正难则反**，我们能不能够找 $i+1\leq k \leq n$ 且 $l_k>r_i$ 的 $k$ 的个数呢？

这才是正道……因为满足 $l_k>r_i$ 的 $k$ **必定在 $i$ 后面**

这应该很好想吧，因为当 $k \leq i$ 时， $r_k \leq r_i$ ，而又 $l_k \leq r_k$ ,故 $l_k\leq r_i$

所只需找出有多少个最大的，在相减即可。

其中组合数可初始化，找出有几个大的可以用 $upper $_$ bound$，时间复杂度 $O(nlogn)$

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=300009;
long long n,k,p=998244353;
struct point
{
	long long l,r;
}qaq[N];
long long a[N],init[N];
bool cmp(point xxx,point yyy)
{
	return xxx.r<yyy.r;
}
long long qpow(long long x,long long y)
{
	long long res=1,base=x;
	while(y!=0)
	{
		if(y%2==1)res=(res*base)%p;
		base=base*base%p;
		y=y/2;
	}
	return res;
}
long long qwq,ans;
signed main()
{
    cin>>n>>k;
    k--;
    for(int i=1;i<=k-1;i++)init[i]=0;
    init[k]=1;
    for(int i=k+1;i<=n;i++)init[i]=init[i-1]*i%p*qpow(i-k,p-2)%p;
    for(int i=1;i<=n;i++)cin>>qaq[i].l>>qaq[i].r;
    sort(qaq+1,qaq+n+1,cmp);
    for(int i=1;i<=n;i++)a[i]=qaq[i].l;
    sort(a+1,a+n+1);
    //for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	//cout<<endl; 
    for(int i=1;i<=n;i++)
    {
    	if(a[n]<=qaq[i].r)
		{
			ans=(ans+init[n-i])%p;
			continue;
		}
    	qwq=upper_bound(a+1,a+n+1,qaq[i].r)-a;
    	//cout<<qaq[i].r<<" ";
    	qwq=n-qwq+1;
		//cout<<qwq<<endl;
    	qwq=n-(i-1)-qwq;
    	//cout<<qwq<<endl;
    	ans=(ans+init[qwq-1])%p;
	}
	cout<<ans%p<<endl;
    return 0;
}
```


---

## 作者：123zbk (赞：1)

首先如果两条线段 $[l1,r1]$，$[l2,r2]$ 的交集不为空，则 $\max\{l1,l2\}\le\min\{r1,r2\}$。

所以我们将 $n$ 条线段按左端点从小到大排序，左端点相同则按右端点排序。枚举第 $i$ 条线段时，此时 $l
_i$ 一定是前 $i-1$ 条线段左端点里的最大值，只需满足前 $i-1$ 条线段的右端点大于 $l_i$ 即可。

我们可以用树状数组维护出前 $i-1$ 条线段的 $r_i$ 大于第 $i$ 条线段的 $l_i$ 的数量 $cnt_i$。因为要选 $k$ 条线段，所以就是在 $cnt_i
$ 条线段中选择 $k-1$ 条，与第 $i$ 条线段共同构成 $k$ 条线段。答案 $ans=\sum\limits_{i=1}^nC_{cnt_i}^{k-1}$。

注意本题要离散化。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=6e5+10,mod=998244353;
int n,k,id,inv[maxn],jc[maxn],num[maxn],ans,cnt,t[maxn]; 
struct node
{
	int l,r;
	bool operator <(const node &x) const
	{
		if(l==x.l)
		{
			return r<x.r;
		}
		return l<x.l;
	}
}a[maxn];
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int lowbit(int x)
{
	return x&(-x);
}
void update(int x)
{
	while(x<=id)
	{
		t[x]++;
		x+=lowbit(x);
	}
}
int query(int n)
{
	int res=0;
	while(n)
	{
		res+=t[n];
		n-=lowbit(n);
	}
	return res;
}
int C(int a,int b)
{
	return jc[a]*inv[b]%mod*inv[a-b]%mod;
}
signed main()
{
	scanf("%lld%lld",&n,&k);
	jc[0]=inv[0]=1;
	for(int i=1;i<=n;i++)
	{
		jc[i]=jc[i-1]*i%mod;	
	} 
	for(int i=1;i<=n;i++)
	{
		inv[i]=qpow(jc[i],mod-2);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i].l,&a[i].r);	
		num[++cnt]=a[i].l;
		num[++cnt]=a[i].r;
	}	
	sort(a+1,a+n+1);
	sort(num+1,num+cnt+1);
	id=unique(num+1,num+cnt+1)-num-1;
	for(int i=1;i<=n;i++)
	{
		a[i].l=lower_bound(num+1,num+id+1,a[i].l)-num;
		a[i].r=lower_bound(num+1,num+id+1,a[i].r)-num;
		int res=query(id)-query(a[i].l-1);
		update(a[i].r);
		ans=(ans+C(res,k-1))%mod; 
	}
	printf("%lld",ans); 
	return 0;
} 
```

---

## 作者：LJC00125 (赞：1)

## 题意

给你$n$个区间的左右端点，问你选出其中$k$个区间的交集非空的方案数。

## solution

这题是显然的套路题，比这场的C2不知道好做到哪里去了

很显然，我们可以把区间$[l,r]$拆成$\{l,1\}$和$\{r + 1,-1\}$两个点，做一次扫描线就能知道某个点上经过的区间个数。

考虑如何计算这个答案，当我们加入一个区间时，我们的答案应该是从原有的区间中选出$k-1$个，加上新加入的区间正好$k$个，就是新的答案。

形式化地:

$$\text{假设我们原来有sum个区间经过，那么当新加入一个区间时:}$$

$$ans=ans+C_{sum}^{k-1}$$

由于一个区间只会加入一次，所以这么计算显然不会重复。代码是很套路的扫描线的代码。

请自动忽略那个蠢蠢的lucas(

```cpp
#include<bits/stdc++.h>
#define N 300005
#define int long long
using namespace std;

template <typename T>

void read(T &a)
{
    T x = 0,f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    a = x * f;
}

template <typename T,typename... Args> void read(T &t,Args &... args) {read(t); read(args...); }

const int mod = 998244353;
int n,k,l[N],r[N],id[N << 1],cnt = 0,tot = 0,a[N];
struct node
{
	int l,f;
	bool operator<(const node &x) const
	{
		if (l == x.l) return f < x.f;
		else return l < x.l;
	}
}p[N << 1];

int ksm(int a,int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int C(int n,int m)
{
    if (m > n)return 0;
    return ((a[n] * ksm(a[m],mod - 2)) % mod * ksm(a[n - m],mod - 2) % mod);
}

int lucas(int n,int m)
{
	if (m > n) return 0;
	if (n == m) return 1;
	if (!m) return 1;
	return C(n % mod,m % mod) * lucas(n / mod,m / mod) % mod;
}

signed main()
{
	read(n,k);
	a[0] = 1;
	for (int i = 1; i <= n; i++) a[i] = (a[i - 1] * i) % mod;
	for (int i = 1; i <= n; i++)
	{
		read(l[i],r[i]);
		id[++cnt] = l[i];
		id[++cnt] = r[i] + 1;
		p[++tot] = (node) {l[i],1};
		p[++tot] = (node) {r[i] + 1,-1};
	}
	sort(id + 1,id + cnt + 1);
	cnt = unique(id + 1,id + cnt + 1) - id - 1;
	for (int i = 1; i <= tot; i++)
	{
		p[i].l = lower_bound(id + 1,id + cnt + 1,p[i].l) - id;
	}
	int ans = 0,flag = 0;
	sort(p + 1,p + tot + 1);
	int pos = 1,sum = 0;
	for (int i = 1; i <= cnt; i++)
	{
		while (pos <= tot && p[pos].l == i)
		{
			if (p[pos].f == 1) ans += lucas(sum,k - 1),ans %= mod;
			sum += p[pos].f;
			pos++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：几何之舞丶 (赞：1)

组合数+sort;

题意:

给定n个时间段,求在所有的时刻中,某个时刻同时存在k盏亮着的灯的方案数..

首先因为l,r范围较大,考虑离散化,然后按l顺序从小到大sort一下.

然后可以考虑每次枚举每一个区间..

记h[i]表示在当前位置,有多少灯可以点亮,s[i]表示在当前位置有多少个灯新加入h集合(即有多少个区间的左端点);

那么对于每一个h[i]大于等于k的时刻,方案数显然是

C(h[i],k).

但是仅仅这样是会造成重复的,因为我们可以不选择新加入的灯,这样就会与先前的方案重复 .

因此我们的答案还要剪掉 C(h[i]-s[i],k).

所以最终的答案就是 C(h[i],k)-C(h[i]-s[i],k);

求过,谢谢.

---

## 作者：Anita_Hailey (赞：1)

又是奇奇怪怪的写法？我按题解好像都没有这么写的.

## [D. Rescue Nibel!](https://codeforces.com/contest/1420/problem/D)

听说这题比 C 简单？我当时想了足足 40 min...本来以为是个 $dp$, 结果用容斥原理退了半天式子无果。考场上好像有 $1000$ 人写出来，然后 $C$ 只有 $500$ 人？离谱。

**题意：** 给你 $n$ 个区间，从其中选择 $k$ 个区间，满足这 $k$ 个区间有交集的方案数。

容斥大力推式子无果？然后想了一下，对于区间按照左端点为第一关键字，右端点为第二关键字排序。然后考虑每一次向现在区间集合里添加区间的情况。

然后首先我们可以将所有不行的线段弹出（考虑用堆维护）即一个线段右端点比这个区间的左端点还靠左，那就弹出。然后答案加上 $C_{S-1}^{k-1}$ 表示选这个线段，并且在剩下 $S-1$ 个线段中取出 $k-1$ 个线段的方案数。这样一定是不重不漏的。就是常数小。复杂度为 $O(n\lg n)$

就是为啥不重露呢？首先对于每个区间 S 我们都计算了带上这区间和她前边的，然后每一个后边的都计算了。

```c++
 const int N = 304001, mod = 998244353;
 int n, k, L[ N ], R[ N ];
 pair < int, int > p[ N ];
 long long ans, inv[ N ], fac[ N ];
 struct Node
 {
  int a;
  bool operator < ( const Node &x ) const
  {
   return p[ this->a ].second > p[ x.a ].second;
  }
 };
 std::priority_queue < Node > Q;
 long long ksm( long long a, long long b )
 {
  long long res = 1;
  for( ; b; b >>= 1, a = a * a % mod ) if( b & 1 )
   res = res * a % mod;
  return res;
 }
 long long C( long long a, long long b )
 {
  return fac[ a ] * inv[ b ] % mod * inv[ a - b ] % mod;
 }
 void Fakemain( )
 {
  n = rdi( );
  k = rdi( );
  if( k == 1 )
  {
   pti( n );
   return;
  }
  For( i, 1, n )
   p[ i ].first = L[ i ] = rdi( ), p[ i ].second = R[ i ] = rdi( );
  fac[ 0 ] = 1;
  For( i, 1, n )
   fac[ i ] = fac[ i - 1 ] * i % mod;
  inv[ n ] = ksm( fac[ n ], mod - 2 );
  Rep( i, n - 1, 0 )
   inv[ i ] = inv[ i + 1 ] * ( i + 1 ) % mod;
  std::sort( p + 1, p + 1 + n );
  For( i, 1, n )
  {
   if( Q.empty( ) )
   {
    Q.push( ( Node ) { i } );
    continue;
   }
   while( !Q.empty( ) && p[ Q.top( ).a ].second < p[ i ].first )
    Q.pop( );
   Q.push( ( Node ) { i } );
   if( Q.size( ) >= k )
    ans = ( ans + C( Q.size( ) - 1, k - 1 ) ) % mod;
  }
  ptl( ans );
  return;
 }
```



---

## 作者：Priestess_SLG (赞：0)

一个很神经病的做法。显然可以考虑枚举每一段最小单位长度的区间，然后记录有多少种不同的选 $k$ 条线段的方法包含这一段区间。显然这样会计算重复。

问题变为怎么不让答案计算重。考虑从左往右枚举每一个最小单位长度的段，设其左端点为 $l$，则只需要让所有线段不同时覆盖 $l$ 左侧的段落即可。因此只需要钦定当前选择的全部 $k$ 个区间中包含一个区间使得其左端点为 $l$。假设当前知道当前单位区间 $l$ 点有 $m$ 个覆盖的线段，以 $m$ 为左端点的线段数量为 $c$，则考虑容斥，用总方案数减去不合法方案数，显然为 $\binom{m}{k}-\binom{m-c}{k}$。用线段树维护每一个单位区间被多少条线段覆盖，开桶记录每一个单位区间是多少区间的左端点，然后直接套用公式计算答案即可。时间复杂度为 $O(n\log n)$ 可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N = 600010;
int l[N], r[N], tmp[N], buc[N];
int fac[N], inv[N], ifac[N];
const int mod = 998244353;
int binom(int x, int y) {
    if (y < 0 || x < y) return 0;
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
struct Node {
    int l, r, sum, tag;
    void init(int p) {
        l = r = p;
        sum = tag = 0;
    }
    void push(int v) {
        sum += (r - l + 1) * v;
        tag += v;
    }
} tree[N << 2];
Node operator+(const Node &l, const Node &r) {
    return {l.l, r.r, l.sum + r.sum, 0};
}
void build(int l, int r, int rt) {
    if (l == r) return tree[rt].init(l);
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void pushdown(int rt) {
    if (tree[rt].tag) {
        tree[rt << 1].push(tree[rt].tag);
        tree[rt << 1 | 1].push(tree[rt].tag);
        tree[rt].tag = 0;
    }
}
void modify(int rt, int ll, int rr, int v) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt].push(v);
    int mid = l + r >> 1; pushdown(rt);
    if (ll <= mid) modify(rt << 1, ll, rr, v);
    if (mid < rr) modify(rt << 1 | 1, ll, rr, v);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
int query(int rt, int ll, int rr) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt].sum;
    int mid = l + r >> 1, s = 0; pushdown(rt);
    if (ll <= mid) s = query(rt << 1, ll, rr);
    if (mid < rr) s += query(rt << 1 | 1, ll, rr);
    return s;
}
int vis[N];
void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> l[i] >> r[i];
    for (int i = 0; i < 2; ++i) fac[i] = inv[i] = ifac[i] = 1;
    for (int i = 2; i < N; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    int sum = 0, idx = 0;
    for (int i = 1; i <= n; ++i) tmp[++idx] = l[i], tmp[++idx] = r[i];
    sort(tmp + 1, tmp + idx + 1);
    idx = unique(tmp + 1, tmp + idx + 1) - tmp - 1;
    build(1, idx, 1);
    for (int i = 1; i <= n; ++i) l[i] = lower_bound(tmp + 1, tmp + idx + 1, l[i]) - tmp;
    for (int i = 1; i <= n; ++i) r[i] = lower_bound(tmp + 1, tmp + idx + 1, r[i]) - tmp;
    for (int i = 1; i <= n; ++i) modify(1, l[i], r[i], 1);
    for (int i = 1; i <= n; ++i) ++buc[l[i]];
    for (int i = 1; i <= n; ++i) {
        if (vis[l[i]]) continue;
        int m = query(1, l[i], l[i]), cnt = buc[l[i]];
        vis[l[i]] = 1;
        sum = (sum + binom(m, k) + mod - binom(m - cnt, k) % mod) % mod;
    }
    cout << sum << '\n';
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T;
    // cin >> T;
    T = 1;
    while (T--) { 
        solve();
    }
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

二维问题套路的先排序一个维度 $l$，然后考虑计算 $r$ 对答案的贡献。

按照 $l$ 从小到大的顺序扫描答案：令 $p$ 表示当前枚举到的线段有交集的线段的数量（不算这一条）。那么这条线段对答案的贡献显然为 $\binom{p}{m-1}$（从 $p$ 条线段中选取 $m-1$ 条。因为这条线段本身必选所以用掉了一次机会）。看重复可以各种数据结构维护。若采用 BIT 维护则时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010, mod = 998244353;
int fac[N], inv[N], ifac[N];
int binom(int x, int y) {
    if (x < y) {
        return 0;
    }
    if (x < 0) {
        return 1;
    }
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
struct Syx {
    int l, r;
    bool operator<(const Syx &x) const {
        return l < x.l;
    }
} z[N];
int tr[N << 3];
void add(int x, int v) {
    for (; x < (N << 3); x += (x &- x)) {
        tr[x] += v;
    }
}
int que(int x) {
    int s = 0;
    for (; x; x -= (x &- x)) {
        s += tr[x];
    }
    return s;
}
signed main() {
    int n, m;
    cin >> n >> m;
    set<int> se;
    for (int i = 1; i <= n; i++) {
        cin >> z[i].l >> z[i].r;
        se.insert(z[i].l);
        se.insert(z[i].r);
    }
    int idx = 0;
    map<int, int> mp;
    for (auto &x : se) {
        mp[x] = ++idx;
    }
    for (int i = 1; i <= n; i++) {
        z[i].l = mp[z[i].l];
        z[i].r = mp[z[i].r];
    }
    for (int i = 0; i < 2; i++) {
        fac[i] = inv[i] = ifac[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    stable_sort(z + 1, z + n + 1);
    int s = 0;
    for (int i = 1; i <= n; i++) {
        int cnt = que(N - 1) - que(z[i].l - 1);
        if (cnt >= m - 1) {
            s = (s + binom(cnt, m - 1)) % mod;
        }
        add(z[i].r, 1);
    }
    cout << s << '\n';
}
```

---

