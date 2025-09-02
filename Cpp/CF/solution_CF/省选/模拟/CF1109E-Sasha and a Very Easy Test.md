# Sasha and a Very Easy Test

## 题目描述

Egor 喜欢数学，不久前他在数学界获得了最高的认可——Egor 成为了红名数学家。为此，Sasha 决定祝贺 Egor，并送给他一道数学测试题作为礼物。这个测试包含一个长度为 $n$ 的整数数组 $a$，以及恰好 $q$ 个操作。操作分为三种类型：

1. “1 l r x”——将区间 $l$ 到 $r$ 内的每个数都乘以 $x$。
2. “2 p x”——将第 $p$ 个位置的数除以 $x$（保证可以整除）。
3. “3 l r”——查询区间 $l$ 到 $r$ 内所有元素的和。

由于和可能很大，Sasha 要求 Egor 计算的和需要对某个整数 $mod$ 取模。

但 Egor 作为红名数学家，没时间做这么简单的题目，同时又不想惹 Sasha 生气，于是他请你帮忙，计算所有第 $3$ 类操作的答案。

## 说明/提示

第一个样例：

初始数组为 $[4, 1, 2, 3, 5]$。

- 第一个操作，查询整个数组的和，$(4 + 1 + 2 + 3 + 5) \bmod 100 = 15 \bmod 100 = 15$。
- 第二个操作，将区间 $2$ 到 $3$ 的每个数都乘以 $6$，结果数组为 $[4, 6, 12, 3, 5]$。
- 第三个操作，查询区间 $1$ 到 $2$ 的和，$(4 + 6) \bmod 100 = 10 \bmod 100 = 10$。
- 第四个操作，将区间 $1$ 到 $5$ 的每个数都乘以 $1$，乘以 $1$ 不影响数组。
- 第五个操作，查询区间 $2$ 到 $4$ 的和，$(6 + 12 + 3) \bmod 100 = 21 \bmod 100 = 21$。

第二个样例：

初始数组为 $[4, 1, 2, 3, 5]$。

- 第一个操作，查询整个数组的和，$(4 + 1 + 2 + 3 + 5) \bmod 2 = 15 \bmod 2 = 1$。
- 第二个操作，将区间 $2$ 到 $3$ 的每个数都乘以 $6$，结果数组为 $[4, 6, 12, 3, 5]$。
- 第三个操作，查询区间 $1$ 到 $2$ 的和，$(4 + 6) \bmod 2 = 10 \bmod 2 = 0$。
- 第四个操作，将区间 $1$ 到 $5$ 的每个数都乘以 $1$，乘以 $1$ 不影响数组。
- 第五个操作，查询区间 $2$ 到 $4$ 的和，$(6 + 12 + 3) \bmod 2 = 21 \bmod 2 = 1$。
- 第六个操作，将第 $3$ 个位置的数除以 $4$，$\frac{12}{4}=3$，数组变为 $[4, 6, 3, 3, 5]$。
- 第七个操作，查询区间 $3$ 到 $4$ 的和，$(3 + 3) \bmod 2 = 6 \bmod 2 = 0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 100
4 1 2 3 5
5
3 1 5
1 2 3 6
3 1 2
1 1 5 1
3 2 4
```

### 输出

```
15
10
21
```

## 样例 #2

### 输入

```
5 2
4 1 2 3 5
7
3 1 5
1 2 3 6
3 1 2
1 1 5 1
3 2 4
2 3 4
3 3 4
```

### 输出

```
1
0
1
0
```

## 样例 #3

### 输入

```
5 2100
1 2 3 4 5
10
1 1 3 12
1 1 5 10
2 5 50
3 2 4
1 4 4 28
2 4 7
3 1 2
3 3 4
2 3 3
3 1 5
```

### 输出

```
640
360
520
641
```

# 题解

## 作者：Little_Fox_Fairy (赞：7)

## 题目大意

给定一个序列，要你在模意义下维护区间加，单点除，区间求和。

## 思路分析

模意义下的区间乘和区间和用线段树都很好维护，但是单点除看上去不太好维护。因为题面上不保证模数 $ mod $ 和除数 $ x $ 是互质的，所以并不能用逆元来直接乘。

那么我们考虑把与模数互质的部分和与模数不互质的部分分开考虑。

对于与模数互质的部分，直接乘逆元即可。

对于与模数不互质的部分，由于直接维护发现数太大也不好维护。但是打表发现在 $ mod \le 10^9 + 9 $ 的范围内，至多有 $ 9 $ 个不同的质因子，所以可以直接开一个桶来记录 $ mod $ 的质因子，每一次除的时候暴力减去桶里记录的质因子的指数，剩下的与 $ mod $ 互质，那么直接乘上逆元即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace fast_IO {
#define IOSIZE 100000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
const int N=1e5+10;
int n,mod,e[N],prime[20],cnt,m;
string s;
inline int qpow(int x,int y)
{
	int ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
inline int Exgcd(int a,int b,int &x,int &y)
{
	if (!b) return x=1,y=0,a;
	int g=Exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b*y;
	return g;
}
inline int inv(int u)
{
	int x,y;
	Exgcd(u,mod,x,y);
	return (x%mod+mod)%mod;
}
struct Segement_Tree
{
	struct node {int l,r,val,sum,tag;}t[N<<2];
	int fac[N<<2][20];
	inline void push_up(int u) {return t[u].sum=(t[u<<1].sum+t[u<<1|1].sum)%mod,void();}
	inline void push_down(int u)
	{
		t[u<<1].sum=t[u<<1].sum*t[u].tag%mod;
		t[u<<1].tag=t[u<<1].tag*t[u].tag%mod;
		t[u<<1].val=t[u<<1].val*t[u].val%mod;
		t[u<<1|1].sum=t[u<<1|1].sum*t[u].tag%mod;
		t[u<<1|1].tag=t[u<<1|1].tag*t[u].tag%mod;
		t[u<<1|1].val=t[u<<1|1].val*t[u].val%mod;
		t[u].tag=t[u].val=1;
		for (int i=1;i<=cnt;i++)
		{
			fac[u<<1][i]+=fac[u][i];
			fac[u<<1|1][i]+=fac[u][i];
			fac[u][i]=0;
		}
		return ;
	}
	inline void build(int u,int l,int r)
	{
		t[u].l=l,t[u].r=r,t[u].tag=1,t[u].val=1;
		if (l==r)
		{
			t[u].sum=e[l]%mod;
			int x=e[l];
			for (int i=1;i<=cnt;i++) while (x%prime[i]==0) fac[u][i]++,x/=prime[i];
			t[u].val=x%mod;
			return ;
		}
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		push_up(u);
		return ;
	}
	inline void update_mul(int u,int l,int r,int val)
	{
		if (t[u].l>=l and t[u].r<=r)
		{
			t[u].sum=t[u].sum*val%mod;
			t[u].tag=t[u].tag*val%mod;
			for (int i=1;i<=cnt;i++) while (val%prime[i]==0) fac[u][i]++,val/=prime[i];
			t[u].val=t[u].val*val%mod;
			return ;
		}
		push_down(u);
		int mid=t[u].l+t[u].r>>1;
		if (l<=mid) update_mul(u<<1,l,r,val);
		if (r>mid) update_mul(u<<1|1,l,r,val);
		push_up(u);
		return ;
	}
	inline void update_div(int u,int pos,int x)
	{
		if (t[u].l==t[u].r)
		{
			for (int i=1;i<=cnt;i++) while (x%prime[i]==0) fac[u][i]--,x/=prime[i];
			t[u].sum=t[u].val=t[u].val*inv(x)%mod;
			for (int i=1;i<=cnt;i++) t[u].sum=t[u].sum*qpow(prime[i],fac[u][i])%mod;
			return ;
		}
		push_down(u);
		int mid=t[u].l+t[u].r>>1;
		if (pos<=mid) update_div(u<<1,pos,x);
		else update_div(u<<1|1,pos,x);
		push_up(u);
		return ;
	}
	inline int query(int u,int l,int r)
	{
		if (t[u].l>=l and t[u].r<=r) return t[u].sum;
		push_down(u);
		int mid=t[u].l+t[u].r>>1,sum=0;
		if (l<=mid) sum+=query(u<<1,l,r),sum%=mod;
		if (r>mid) sum+=query(u<<1|1,l,r),sum%=mod;
		return sum;
	}
}tr;
signed main()
{
	cin>>n>>mod;
	int v=mod;
	for (int i=2;i<=v/i;i++)
	{
		if (v%i) continue;
		prime[++cnt]=i;
		while (v%i==0) v/=i;
	}
	if (v>1) prime[++cnt]=v;
	for (int i=1;i<=n;i++) cin>>e[i];
	tr.build(1,1,n);
	cin>>m;
	while (m--)
	{
		int op,l,r,x;
		cin>>op>>l>>r;
		if (op==1) cin>>x,tr.update_mul(1,l,r,x);
		if (op==2) tr.update_div(1,l,r);
		if (op==3) cout<<tr.query(1,l,r)%mod<<endl;
	}
	return (0-0);
}
```

记得开 long long 喵~

---

## 作者：serverkiller (赞：4)

## 题意

让你在模意义下维护区间和,支持区间乘法,单点除法.

## solution

模意义下的区间和和区间乘法是经典的线段树操作,我们考虑怎么在线段树上同时支持单点除法.

这边没有保证除数和模数互质,所以直接逆元是完全不行的.

由于没有算法可以处理不互质情况的模意义下的除法,这提示了我们把互质部分和不互质部分分开存的思路.

互质部分我们可以考虑使用乘法逆元,但是不互质的部分我们只能直接除了.

显然数很大,我们不能存下不互质的数不取模时的数,所以考虑变成唯一分解的形式存.

这里有个小tips:

>  对于分成唯一分解形式,我们只需要单点上的值,而区间上的值实际上不需要用到,而线段树的单点的 lazytag 是不会被下传的,所以把这个直接打在 lazytag 上下传到单点时直接处理 lazytag 就可以了,我们 pushup 维护的只有区间和一个,而不需要维护其他的信息.对于互质部分同理

这题的码量对于cf这种短时赛来说完全受不了啊（

```cpp
#include <bits/stdc++.h>
#define N 100005
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

int n,q,mod,a[N],cnt = 0;
map<int,int> mp,hxb;

int gcd(int x,int y)
{
	return y ? gcd(y,x % y) : x;
}

void exgcd(int a,int b,int &x,int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return ;
	}
	exgcd(b,a % b,y,x);
	y -= 1ll * a / b * x;
}

int inv(int x)
{
	int a,b;
	exgcd(x,mod,a,b);
	return (a % mod + mod) % mod;
}

int ksm(int a,int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}

struct Segment_Tree
{
	int sum[N << 2],lazy[N << 2],fac[N << 2][15],tr[N << 2];
	void pushup(int now)
	{
		sum[now] = (sum[now << 1] + sum[now << 1 | 1]) % mod;
	}
	void pushdown(int now)
	{
		sum[now << 1] = 1ll * sum[now << 1] * lazy[now] % mod;
		lazy[now << 1] = 1ll * lazy[now << 1] * lazy[now] % mod;
		tr[now << 1] = 1ll * tr[now << 1] * tr[now] % mod;
		sum[now << 1 | 1] = 1ll * sum[now << 1 | 1] * lazy[now] % mod;
		lazy[now << 1 | 1] = 1ll * lazy[now << 1 | 1] * lazy[now] % mod;
		tr[now << 1 | 1] = 1ll * tr[now << 1 | 1] * tr[now] % mod;
		tr[now] = 1; 
		lazy[now] = 1;
		for (int i = 1; i <= cnt; i++)
		{
			fac[now << 1][i] += fac[now][i];
			fac[now << 1 | 1][i] += fac[now][i];
			fac[now][i] = 0;
		}
	}
	void build(int now,int l,int r)
	{
		lazy[now] = 1;
		tr[now] = 1;
			if (l == r)
		{
			sum[now] = a[l] % mod;
			int x = a[l];
			for (int i = 1; i <= cnt; i++)
				while (!(x % hxb[i])) fac[now][i]++,x /= hxb[i];
			tr[now] = x % mod;
			return ;
		}
		int mid = (l + r) >> 1;
		build(now << 1,l,mid);
		build(now << 1 | 1,mid + 1,r);
		pushup(now);
	}
	void update(int now,int l,int r,int p,int x)
	{
		if (l == r)
		{
			for (int i = 1; i <= cnt; i++)
				while (!(x % hxb[i])) fac[now][i]--,x /= hxb[i];
			tr[now] = 1ll * tr[now] * inv(x) % mod;
			sum[now] = tr[now];
			for (int i = 1; i <= cnt; i++)
				sum[now] = 1ll * sum[now] * ksm(hxb[i],fac[now][i]) % mod;
			return ;
		}
		pushdown(now);
		int mid = (l + r) >> 1;
		if (p <= mid) update(now << 1,l,mid,p,x);
		if (p > mid) update(now << 1 | 1,mid + 1,r,p,x);
		pushup(now);
	}
	void update(int now,int l,int r,int ll,int rr,int x)
	{
		if (ll <= l && rr >= r)
		{
			sum[now] = 1ll * sum[now] * x % mod;
			lazy[now] = 1ll * lazy[now] * x % mod;
			for (int i = 1; i <= cnt; i++)
				while (!(x % hxb[i])) fac[now][i]++,x /= hxb[i];
			tr[now] = 1ll * tr[now] * x % mod;
			return ;
		}
		int mid = (l + r) >> 1;
		pushdown(now);
		if (ll <= mid) update(now << 1,l,mid,ll,rr,x);
		if (rr > mid) update(now << 1 | 1,mid + 1,r,ll,rr,x);
		pushup(now);
	}
	int query(int now,int l,int r,int ll,int rr)
	{
		if (ll <= l && rr >= r)
		{
			return sum[now];
		}
		pushdown(now);
		int mid = (l + r) >> 1,ans = 0;
		if (ll <= mid) ans = (ans + query(now << 1,l,mid,ll,rr)) % mod;
		if (rr > mid) ans = (ans + query(now << 1 | 1,mid + 1,r,ll,rr)) % mod;
		return ans;
	}
}T;

signed main()
{
	read(n,mod);
	int _mod = mod;
	for (int i = 2; i * i <= _mod; i++)
	{
		if (_mod % i) continue;
		mp[i] = ++cnt;
		hxb[cnt] = i;
		while (!(_mod % i)) _mod /= i;
	}
	if (_mod != 1) mp[_mod] = ++cnt,hxb[cnt] = _mod;
	for (int i = 1; i <= n; i++)
		read(a[i]);
	T.build(1,1,n);
	read(q);
	while (q--)
	{
		int opt;
		read(opt);
		if (opt == 1)
		{
			int l,r,x;
			read(l,r,x);
			T.update(1,1,n,l,r,x);
		}
		if (opt == 2)
		{
			int p,x;
			read(p,x);
			T.update(1,1,n,p,x);
		}
		if (opt == 3)
		{
			int l,r;
			read(l,r);
			int ans = T.query(1,1,n,l,r);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```



---

## 作者：RedreamMer (赞：3)

[$\Large\texttt{CF1109E}$](https://www.luogu.com.cn/problem/CF1109E)

[$\small\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14068198.html)

前置知识：欧拉定理（扩展费马小定理），基本线段树操作

## 题意

十分简洁，不多赘述。

注意 $mod$ 可以不为质数，每个单点除操作保证能整除。

## 思路

若 $mod$ 是质数就好做了（不然怎么会是黑题），但 $mod$ 不是质数代表在单点除时不能直接用费马小定理边乘边模。

可以考虑使用扩展费马定理：

$$a^{\varphi(p)}=1\mod p ~~(\gcd(a,p)=1)$$

发现小于 $1e9$ 的每个数质因数个数不会超过 $9$ 个，可以想到将所有要进行操作的数分成两部分，一部分质因子全是 $mod$ 的质因子，开一个大小为 $10$ 的数组暴力操作，若除就在这个数组里面减去要减的质因子，剩下部分的肯定与 $mod$ 互质，除一个数就乘 $x^{\varphi(mod)-1}$ 并取模就好了。

注意细节，可以参考代码。

另附上 $\varphi(n)$ 的求法：

$$\varphi(n)=n\times\prod^{x}_{i=1}\frac{p_i}{p_i-1}$$

~~不要像我 $\varphi(n)$ 求错了调1h~~

时间复杂度 $\texttt{O(10NlogN)}$ (远远达不到这个上限)。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

 #define ls n << 1
 #define rs n << 1 | 1
 #define int long long
 const int N = 1e5;
inline int read()
{
    int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    s = (neg ? -s : s);
    return s;
}

int a,mod,b,p[10],top,q[N+10],t[N+10][10],add[10],pp;
struct segment {
	int l,r,val,lazy1[10],lazy2,lazy3;
} s[N*4+10];

inline int get_phi(int n) {
	int ans = n;
	for (int i = 2; i*i <= n; i++) {
		if (!(n%i)) {
			ans = 1ll * ans * (i - 1) / i;
			while (!(n%i))n /= i;
		}
	}
	if (n > 1)ans = 1ll * ans * (n - 1) / n;
	return ans;
}

inline void get(int n) {
	int qq=sqrt(n);
	for(int i=2;i<=qq;i++) {
		if(n%i==0) {
			p[++top]=i;
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) p[++top]=n;
}

inline int qpow(int n,int m) {
	int res=1;
	for(;m;m>>=1) {
		if(m&1) res=res*n%mod;
		n=n*n%mod;
	}
	return res;
}

inline int calc(int n) {
	int res=1;
	for(int i=1;i<=top;i++) res=(res*qpow(p[i],t[n][i]))%mod;
	return res;
}

inline void up(int n) {
	s[n].val=(s[ls].val+s[rs].val)%mod;
}

inline void down(int n) {
	s[ls].val=s[ls].val*s[n].lazy2%mod;
	s[rs].val=s[rs].val*s[n].lazy2%mod;
	s[ls].lazy2=s[ls].lazy2*s[n].lazy2%mod;
	s[rs].lazy2=s[rs].lazy2*s[n].lazy2%mod;
	s[ls].lazy3=s[ls].lazy3*s[n].lazy3%mod;
	s[rs].lazy3=s[rs].lazy3*s[n].lazy3%mod;
	s[n].lazy2=s[n].lazy3=1;
	for(int i=1;i<=top;i++) {
		s[ls].lazy1[i]+=s[n].lazy1[i];
		s[rs].lazy1[i]+=s[n].lazy1[i];
		s[n].lazy1[i]=0;
	}
	return;
}

inline void build(int n,int l,int r) {
	s[n].l=l;
	s[n].r=r;
	s[n].lazy2=s[n].lazy3=1;
	memset(s[n].lazy1,0,sizeof(s[n].lazy1));
	if(l==r) {
		s[n].val=q[l]*calc(l)%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(n);
}

inline void div(int n,int m,int k) {
	if(s[n].l==s[n].r) {
		q[m]=q[m]*s[n].lazy3%mod;
		s[n].lazy3=1;
		for(int i=1;i<=top;i++) {
			t[m][i]+=s[n].lazy1[i];
			s[n].lazy1[i]=0;
			while(k%p[i]==0) t[m][i]--,k/=p[i];
		}
		q[m]=q[m]*qpow(k,pp-1)%mod;
		s[n].val=q[m]*calc(m)%mod;
		return;
	}
	down(n);
	int mid=(s[n].l+s[n].r)>>1;
	if(m<=mid) div(ls,m,k);
	else div(rs,m,k);
	up(n);
}

inline void times(int n,int l,int r,int k,int _k) {
	if(s[n].l>=l&&s[n].r<=r) {
		s[n].val=s[n].val*k%mod;
		s[n].lazy2=s[n].lazy2*k%mod;
		s[n].lazy3=s[n].lazy3*_k%mod;
		for(int i=1;i<=top;i++) s[n].lazy1[i]+=add[i];
		return;
	}
	down(n);
	int mid=(s[n].l+s[n].r)>>1;
	if(l<=mid) times(ls,l,r,k,_k);
	if(mid<r) times(rs,l,r,k,_k);
	up(n);
}

inline int query(int n,int l,int r) {
	if(s[n].l>=l&&s[n].r<=r) return s[n].val;
	down(n);
	int mid=(s[n].l+s[n].r)>>1,res=0;
	if(l<=mid) res=(res+query(ls,l,r))%mod;
	if(mid<r) res=(res+query(rs,l,r))%mod;
	return res;
}

signed main()
{
//	freopen("in.txt","r",stdin);
	a=read();
	mod=read();
	pp=get_phi(mod);
	int opt,x,y,z;
	get(mod);
	for(int i=1;i<=a;i++) {
		q[i]=read();
		for(int j=1;j<=top;j++) {
			while(q[i]%p[j]==0) {
				q[i]/=p[j];
				t[i][j]++;
			}
		}
	}
	build(1,1,a);
	b=read();
	for(int i=1;i<=b;i++) {
		opt=read();
		x=read();
		y=read();
		if(opt==1) {
			z=read();
			if(z==1) continue;
			int _z=z;
			for(int j=1;j<=top;j++) {
				add[j]=0;
				while(_z%p[j]==0) _z/=p[j],add[j]++;
			}
			times(1,x,y,z,_z);
		}
		else if(opt==2) div(1,x,y);
		else printf("%lld\n",query(1,x,y));
	}
    return 0;
}
```

---

## 作者：chlchl (赞：2)

upd 2024.9.11 修正一处笔误。

---

也是好起来了，晚自习跑机房集训了。

因为变量重名调了半个晚上，太菜了 qwq。

## Solution
$mod$ 如果是个质数，这是个黄题，甚至区间除都行。

但不是质数，单点除法就不能用逆元，我们是没有办法处理带模除法的。

质数要求太过苛刻，我们可以用欧拉定理：

$$x^{\varphi(x)}\equiv 1\pmod p,\quad
\gcd(x,p)=1$$

此时 $x$ 的逆元即为 $x^{\varphi(x)-1}$。

但是我们仍然需要除数和 $mod$ 互质，所以考虑如何把它变得互质。显然地，把不互质的部分去掉不就互质了吗？

这启发我们分开维护。先将 $mod$ 进行唯一分解，可以发现不同的质因子不会超过 $9$ 个。那么对于除法给出的每一个 $x$，我们可以单独处理 $x$ 中含有的 $mod$ 的因子并且把它们干掉，剩下的直接求逆元就好了。

具体地，用线段树维护区间和与区间乘标记。由于除法是单点除法，所以在线段树中每次都会下到最底层。

因此，如果我们维护一个数组 $cnt$ 表示当前节点的乘法标记含有 $mod$ 的因子的个数，那么单点除法的时候只需要在叶结点暴力下放所有懒标记之后对 $cnt$ 进行修改就行了。

而区间乘法的时候就把 $x$ 拆成上述两部分，分别加到普通乘法标记和 $cnt$ 数组中即可。

其实你可以直接将 $cnt$ 数组理解为一个数（反正将它们快速幂后乘起来本来就是 $x$ 的一个因数），只是我们单独将它的分解形式拎出来储存了而已，这样在写代码的时候就方便你思考该对它干什么了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int n, q, len;
int p, phi, ys[12];

int exp(int a, int b){
	int cnt = 1;
	while(b){
		if(b & 1)
			(cnt *= a) %= p;
		(a *= a) %= p, b >>= 1;
	}
	return cnt;
}

struct NUM{
	int x, cnt[12];
	
	NUM(){}
	
	NUM(int n){
		memset(cnt, 0, sizeof(cnt));
		x = 0;
		if(n == 1){
			x = 1;
			return ;
		}
		for(int i=1;i<=len;i++){
			while(n % ys[i] == 0)
				n /= ys[i], cnt[i]++;
		}//将 n 拆成两部分
		x = n;
	}
	
	int calc(){
		int res = x;
		for(int i=1;i<=len;i++)
			(res *= exp(ys[i], cnt[i])) %= p;
		return res;
	}//算一算这个懒标记的总和到底是多少
} a[N], tagnum[N << 2];
int val[N << 2], tag[N << 2];

#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void build(int o, int l, int r){
	tag[o] = 1;
	tagnum[o] = NUM(1);
	if(l == r){
		val[o] = a[l].calc();
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls(o), l, mid);
	build(rs(o), mid + 1, r);
	val[o] = (val[ls(o)] + val[rs(o)]) % p;
}

void pushdown(int o){
	(tag[ls(o)] *= tag[o]) %= p, (tag[rs(o)] *= tag[o]) %= p;
	(val[ls(o)] *= tag[o]) %= p, (val[rs(o)] *= tag[o]) %= p;
	(tagnum[ls(o)].x *= tagnum[o].x) %= p, (tagnum[rs(o)].x *= tagnum[o].x) %= p;
	for(int i=1;i<=len;i++){
		tagnum[ls(o)].cnt[i] += tagnum[o].cnt[i];
		tagnum[rs(o)].cnt[i] += tagnum[o].cnt[i];
		tagnum[o].cnt[i] = 0;
	}//pushdown 的时候也要下传，cnt的本质和tag是一样的
	tag[o] = tagnum[o].x = 1ll;
}

void update(int o, int l, int r, int s, int t, int v){
	if(l >= s && r <= t){
		NUM x = NUM(v);
		(tagnum[o].x *= x.x) %= p;
		(val[o] *= v) %= p;
		(tag[o] *= v) %= p;
		for(int i=1;i<=len;i++)
			tagnum[o].cnt[i] += x.cnt[i];//区间乘法更新
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if(s <= mid)
		update(ls(o), l, mid, s, t, v);
	if(t > mid)
		update(rs(o), mid + 1, r, s, t, v);
	val[o] = (val[ls(o)] + val[rs(o)]) % p;
}

void update(int o, int l, int r, int pos, int v){
	if(l == r){
		(a[l].x *= tagnum[o].x) %= p;//p和pos搞混了是谁我不说
		tagnum[o].x = 1;
		for(int i=1;i<=len;i++){
			a[l].cnt[i] += tagnum[o].cnt[i];
			while(v % ys[i] == 0)
				a[l].cnt[i]--, v /= ys[i];//一个个把v的因子除掉
			tagnum[o].cnt[i] = 0;
		}
		(a[l].x *= exp(v, phi - 1)) %= p;//剩下部分可以直接求逆元
		val[o] = a[l].calc();//注意更新此时的单点和
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if(pos <= mid)
		update(ls(o), l, mid, pos, v);
	else
		update(rs(o), mid + 1, r, pos, v);
	val[o] = (val[ls(o)] + val[rs(o)]) % p;
}

int query(int o, int l, int r, int s, int t){
	if(l >= s && r <= t)
		return val[o];
	int mid = (l + r) >> 1; int res = 0;
	pushdown(o);
	if(s <= mid)
		(res += query(ls(o), l, mid, s, t)) %= p;
	if(t > mid)
		(res += query(rs(o), mid + 1, r, s, t)) %= p;
	return res;
}

main(){
	scanf("%lld%lld", &n, &p);
	int m = p; phi = p;
	for(int i=2;i*i<=m;i++){
		if(m % i == 0){
			ys[++len] = i;
			phi = phi * (i - 1ll) / i;//顺便求一下 phi(mod)
			while(m % i == 0)
				m /= i;
		}
	}
	if(m > 1)
		ys[++len] = m, phi = phi * (m - 1ll) / m;
	for(int i=1,x;i<=n;i++){
		scanf("%lld", &x);
		a[i] = NUM(x);
	}
	build(1, 1, n);
	scanf("%lld", &q);
	while(q--){
		int op, l, r; int x;
		scanf("%lld", &op);
		if(op == 1){
			scanf("%lld%lld%lld", &l, &r, &x);
			update(1, 1, n, l, r, x);
		}
		if(op == 2){
			scanf("%lld%lld", &l, &x);
			update(1, 1, n, l, x);
		}
		if(op == 3){
			scanf("%lld%lld", &l, &r);
			printf("%lld\n", query(1, 1, n, l, r));
		}
	}
	return 0;
}

```

---

## 作者：_Vix_ (赞：2)

[原题链接](https://www.luogu.com.cn/problem/CF1109E)

---

## 分析

首先如果给定的模数是质数的话，那么这是一道简单题。直接用线段树维护就行了。

现在模数不是质数，面临的问题是单点除以 $x$ 时，不一定能找到 $x$ 的逆元。

考虑将一个数拆开，拆成 $x=v \times p_1^{c_1} \times p_2^{c_2} \times \cdots \times p_k^{c_k}$ 的形式，其中 $p_1,p_2,\dots ,p_k$ 是模数的质因数。那么就很好维护了，单点除的时候用欧拉定理找 $v$ 的逆元，此时 $v$ 与模数一定互质，而其他的操作只用维护 $k$ 个质因数的指数。

写一棵带有懒标记的线段树就可以 $O(nk \log n)$ 解决问题。其中 $k$ 是模数的质因数个数，是 $\log_2 V$ 级别的（$V$ 是值域）。

具体实现可以看代码。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define lson u << 1
#define rson u << 1 | 1
#define mid (L[u] + R[u] >> 1)
using namespace std;

const int N = 1e5 + 10;
int L[N << 2], R[N << 2], sum[N << 2], val[N << 2], mul[N << 2], c[N << 2][12];
int k, p[N], phi, tmp;
int n, mod, a[N];
int m, op, x, y, z;

inline int pwr(int b, int k) {
	int res = 1;
	while (k) {
		if (k & 1) res = (ll)res * b % mod;
		b = (ll)b * b % mod; k >>= 1;
	}
	return res;
}

inline void pushup(int u) {
	sum[u] = (sum[lson] + sum[rson]) % mod;
}

inline void apply(int u, int v) {
	sum[u] = (ll)sum[u] * v % mod;
	mul[u] = (ll)mul[u] * v % mod;
}

inline void pushdown(int u) {
	apply(lson, mul[u]);
	apply(rson, mul[u]);
	val[lson] = (ll)val[lson] * val[u] % mod;
	val[rson] = (ll)val[rson] * val[u] % mod;
	mul[u] = val[u] = 1;
	for (int i = 1; i <= k; i++) {
		c[lson][i] += c[u][i];
		c[rson][i] += c[u][i];
		c[u][i] = 0;
	}
}

inline void build(int u, int l, int r) {
	L[u] = l, R[u] = r;
	mul[u] = val[u] = 1;
	if (l == r) {
		sum[u] = a[l] % mod;
		for (int i = 1; i <= k; i++) while (a[l] % p[i] == 0) c[u][i]++, a[l] /= p[i];
		val[u] = a[l] % mod;
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(u);
}

inline void modify(int u, int l, int r, int x) {
	if (l <= L[u] && R[u] <= r) {
		apply(u, x);
		for (int i = 1; i <= k; i++) while (x % p[i] == 0) c[u][i]++, x /= p[i];
		val[u] = (ll)val[u] * x % mod;
		return;
	}
	pushdown(u);
	if (l <= mid) modify(lson, l, r, x);
	if (r > mid) modify(rson, l, r, x);
	pushup(u);
}

inline void divide(int u, int x, int v) {
	if (L[u] == R[u]) {
		for (int i = 1; i <= k; i++) while (v % p[i] == 0) c[u][i]--, v /= p[i];
		val[u] = (ll)val[u] * pwr(v, phi - 1) % mod;
		sum[u] = val[u];
		for (int i = 1; i <= k; i++) sum[u] = (ll)sum[u] * pwr(p[i], c[u][i]) % mod;
		return;
	}
	pushdown(u);
	if (x <= mid) divide(lson, x, v);
	else divide(rson, x, v);
	pushup(u);
}

inline int query(int u, int l, int r) {
	if (l <= L[u] && R[u] <= r) return sum[u];
	pushdown(u);
	int res = 0;
	if (l <= mid) res = (res + query(lson, l, r)) % mod;
	if (r > mid) res = (res + query(rson, l, r)) % mod;
	return res;
}

inline void init() {
	phi = tmp = mod;
	for (int i = 2; i * i <= tmp; i++) {
		if (tmp % i) continue;
		p[++k] = i;
		phi = phi / i * (i - 1);
		while (tmp % i == 0) tmp /= i;
	}
	if (tmp > 1) p[++k] = tmp, phi = phi / tmp * (tmp - 1);
}

int main() {
	scanf("%d%d", &n, &mod);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	init();
	build(1, 1, n);
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) scanf("%d", &z), modify(1, x, y, z);
		if (op == 2) divide(1, x, y);
		if (op == 3) printf("%d\n", query(1, x, y));
	}
	return 0;
}
```


---

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1109E)
## 题意
给你一个长为 $n$ 的序列 $a$ 和一个数 $p$，有 $q$ 次操作，操作有 $3$ 种，分别是：
1. `1 l r x`，对 $\forall i\in[l,r],a_i\gets a_i\times x$；
2. `2 c x`，令 $a_c\gets \dfrac{a_c}{x}$，保证 $x\mid a_c$；
3. `3 l r `，查询 $\displaystyle\left(\sum_{i=l}^ra_i\right) \bmod p$。

时限 2.5s，$1\le n,q\le 10^5$，$1\le a_i,x\le 10^5$，$2\le p\le 10^9+9$。

## 思路
看到这个除法操作是非常难直接维护的，模数 $p$ 也不是质数，所以可以向维护质因子次数的方面想。

质数有很多，不可能每一个都直接维护，考虑维护质数的原因是 $p$ 不保证是质数，$x$ 不一定有逆元。而 $x$ 在模 $p$ 意义下有逆元当且仅当 $\gcd(x,p)=1$。考虑将 $x,p$ 分别分解质因数，$x$ 中不是 $p$ 的因数的质因数可以直接用 $x^{φ(p)-1}$ 计算逆元，只有 $p$ 的质因子需要特殊维护。

可以发现，由于 $p\le 10^9+9$，$p$ 的不同因数最多只有 $k=9$ 个，可以直接维护。使用线段树，标记存下这些信息即可。

时间复杂度 $O(kn\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=5e5+10;
int n,q,p,phi,cnt,sp[15];
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%p;
		x=1ll*x*x%p;
		y>>=1; 
	}
	return res;
}
struct node{
	int ep,op[15];
	inline void init(int x){
		for(int i=1;i<=cnt;i++){
			op[i]=0;
			while(x%sp[i]==0)
				op[i]++,x/=sp[i];
		}
		ep=x;
	}
	inline int getv(){
		int res=ep;
		for(int i=1;i<=cnt;i++)
			res=1ll*res*qpow(sp[i],op[i])%p;
		return res;
	}
	inline void set(){
		ep=1;
		memset(op,0,sizeof(op));
	}
	inline friend node operator*(const node &a,const node &b){
		node c;
		c.ep=1ll*a.ep*b.ep%p;
		for(int i=1;i<=cnt;i++)
			c.op[i]=a.op[i]+b.op[i];
		return c; 
	}
}s[N];
struct Segment_Tree{
	struct Node{
		int sum,tagm;
		node tagd;
	}a[N<<2];
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	inline void pushdown(int rt){
		a[ls].sum=1ll*a[ls].sum*a[rt].tagm%p;
		a[rs].sum=1ll*a[rs].sum*a[rt].tagm%p;
		a[ls].tagm=1ll*a[ls].tagm*a[rt].tagm%p;
		a[rs].tagm=1ll*a[rs].tagm*a[rt].tagm%p;
		a[ls].tagd=a[ls].tagd*a[rt].tagd;
		a[rs].tagd=a[rs].tagd*a[rt].tagd;
		a[rt].tagm=1,a[rt].tagd.set();
	}
	inline void pushup(int rt){
		a[rt].sum=(a[ls].sum+a[rs].sum)%p;
	}
	inline void build(int rt,int l,int r){
		a[rt].tagm=1,a[rt].tagd.set();
		if(l==r){
			a[rt].sum=s[l].getv();
			return ;
		}
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	inline void multi(int rt,int l,int r,int L,int R,node v){
		if(L<=l&&r<=R){
			a[rt].sum=1ll*a[rt].sum*v.getv()%p;
			a[rt].tagm=1ll*a[rt].tagm*v.getv()%p;
			a[rt].tagd=a[rt].tagd*v;
			return ;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) multi(ls,l,mid,L,R,v);
		if(R>mid) multi(rs,mid+1,r,L,R,v);
		pushup(rt);
	}
	inline void dived(int rt,int l,int r,int p,int v){
		if(l==r){
			s[p]=s[p]*a[rt].tagd;
			a[rt].tagd.set();
			for(int i=1;i<=cnt;i++)
				while(v%sp[i]==0)
					s[p].op[i]--,v/=sp[i];
			s[p].ep=1ll*s[p].ep*qpow(v,phi-1)%(::p);
			a[rt].sum=s[p].getv();
			return ;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) dived(ls,l,mid,p,v);
		else dived(rs,mid+1,r,p,v);
		pushup(rt);
	}
	inline int query(int rt,int l,int r,int L,int R){
		if(L<=l&&r<=R) return a[rt].sum;
		pushdown(rt);
		int mid=l+r>>1,res=0;
		if(L<=mid) res=(res+query(ls,l,mid,L,R))%p;
		if(R>mid) res=(res+query(rs,mid+1,r,L,R))%p;
		return res;
	}
}T;
int main(){
	n=read(),p=read();
	int tmp;tmp=phi=p;
	for(int i=2;i*i<=p;i++){
		if(tmp%i==0){
			sp[++cnt]=i;
			phi=phi/i*(i-1);
			while(tmp%i==0) tmp/=i;
		}
	}
	if(tmp!=1){
		sp[++cnt]=tmp;
		phi=phi/tmp*(tmp-1);
	}
	for(int i=1;i<=n;i++)
		s[i].init(read());
	q=read();
	T.build(1,1,n);
	while(q--){
		int opt=read(),l=read(),r=read();
		if(opt==1){
			int x=read();
			node tmp;tmp.init(x);
			T.multi(1,1,n,l,r,tmp);
		}else if(opt==2){
			T.dived(1,1,n,l,r);
		}else{
			write(T.query(1,1,n,l,r)),putc('\n');
		}
	}
	flush();
}
```
再见 qwq~

---

## 作者：Muel_imj (赞：2)

[CF1109E in luogu](https://www.luogu.com.cn/problem/CF1109E)

[更差的阅读体验](https://www.cnblogs.com/muel-imj/p/16025443.html)

### 题意简述：

维护一个序列，给定三种操作：区间乘，单点除，区间求和。**任意模数**。

---
### 思路：

操作就这么个操作，线段树套上就没了，重点在于任意模数的除法，不然这也不会是黑题了。

除数与模数不一定互质那就没法求逆元了。既然如此那就把数分为互质的部分和不互质的部分，不就解决了嘛？

具体的嗦，将模数分解质因数，一个数也可以拆分分为包含这些质因数的部分与不包含的部分，包含的那部分特殊处理，不包含的就互质了，可以用逆元。即：

$$mod=p_1^{c_1}×p_2^{c_2}×\cdots×p_{cnt}^{c_{cnt}}$$
$$x=a×p_1^{t_1}×p_2^{t_2}×\cdots×p_{cnt}^{t_{cnt}},\gcd(a,mod)=1$$

其中 $mod$ 每个质因子的次数没必要知道，而其他数是需要的。

在处理时，对于互质的部分 $a$，可以直接算，除法就用逆元（exgcd 或欧拉定理）。对于不互质的部分 $p$，就用次数相加减，在查询时再用快速幂算一遍。

关于线段树，由于除法是单点的，所以在线段树上我们没必要对每一处权值都这么处理，只处理单点即可。

具体的处理，pushup 与正常无异，但是 lazy 与 pushdown 需要特殊处理。并且对于每个单点的操作，可以直接用 lazy 储存，也只需要在做除法的时候，对于单点将 lazy 用掉，更新权值。所以为了提升效率，lazy 需要未经拆分的，应对区间乘操作，与拆分过的，应对单点除操作。

---
既然都要分解质因数了，那就顺便求个欧拉函数，用欧拉定理求逆元岂不美哉？关于欧拉函数与欧拉定理：

$$\varphi(n)=n×\prod_{i=1}^{cnt}\frac{p_i-1}{p_i}$$
$$a^{\varphi(p)}\equiv 1 \mod p (\gcd(a,p)=1)$$
$$a^{\varphi(p)-1}\equiv a^{-1} \mod p (\gcd(a,p)=1)$$

顺便，对于逆元可以整个小记忆化...不过询问并没有那么多所以优化不大

代码 qwq：
```cpp
#include<bits/stdc++.h>
#define ttT template <typename T>
#define EL puts("Elaina")
#define reg register int
#define qwq 0
using namespace std;
inline char gc(){
    static char buf[1<<21],*p1,*p2;
    if(p1==p2){p1=buf,p2=buf+fread(buf,1,1<<21,stdin);if(p1==p2)return EOF;}
    return *p1++;
}
ttT inline void read(T &x){
    x=0;int f=1;char ch=gc();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
    x*=f;
}
typedef long long ll;
const int maxn=1e5+3;
int n,mod,phi,p[11],pcnt,invv[maxn];
inline int qpow(int a,int b){
    int ans=1;a%=mod;
    for(;b;b>>=1,a=1ll*a*a%mod)
        if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
inline int inv(int x){
    return invv[x]?invv[x]:invv[x]=qpow(x,phi-1);
}
struct num{
    int x,np[11];
    num(){};
    num(int n){
        x=0,memset(np,0,sizeof(np));
        if(n==1){x=1;return;}
        for(reg i=1;i<=pcnt;++i)
            while(n%p[i]==0)np[i]++,n/=p[i];
        x=n;
    }
    inline int calc(){
        int ans=x;
        for(reg i=1;i<=pcnt;++i)ans=1ll*ans*qpow(p[i],np[i])%mod;
        return ans;
    }
};
#define lt (k<<1)
#define rt (k<<1|1)
num a[maxn];
struct node{
    int l,r,x,lzy;
    num lazy;
}t[maxn<<2];
inline void pushup(int k){
    t[k].x=(t[lt].x+t[rt].x)%mod;
}
inline void pushdown(int k){
    t[lt].x=1ll*t[lt].x*t[k].lzy%mod,t[rt].x=1ll*t[rt].x*t[k].lzy%mod;
    t[lt].lzy=1ll*t[lt].lzy*t[k].lzy%mod,t[rt].lzy=1ll*t[rt].lzy*t[k].lzy%mod;
    t[lt].lazy.x=1ll*t[lt].lazy.x*t[k].lazy.x%mod;
    t[rt].lazy.x=1ll*t[rt].lazy.x*t[k].lazy.x%mod;
    for(reg i=1;i<=pcnt;++i){
        t[lt].lazy.np[i]+=t[k].lazy.np[i];
        t[rt].lazy.np[i]+=t[k].lazy.np[i];
        t[k].lazy.np[i]=0;
    }
    t[k].lzy=t[k].lazy.x=1;
}
inline void build(int k,int l,int r){
    t[k].l=l,t[k].r=r,t[k].lzy=1,t[k].lazy=num(1);
    if(l==r)t[k].x=a[l].calc();
    else{
        int mid=(l+r)>>1;
        build(lt,l,mid);
        build(rt,mid+1,r);
        pushup(k);
    }
}
inline void updata(int k,int L,int R,int x,num xx){
    if(L<=t[k].l&&t[k].r<=R){
        t[k].x=1ll*t[k].x*x%mod;
        t[k].lzy=1ll*t[k].lzy*x%mod;
        t[k].lazy.x=1ll*t[k].lazy.x*xx.x%mod;
        for(reg i=1;i<=pcnt;++i)t[k].lazy.np[i]+=xx.np[i];
    }
    else{
        int mid=(t[k].l+t[k].r)>>1;
        pushdown(k);
        if(L<=mid)updata(lt,L,R,x,xx);
        if(R>mid)updata(rt,L,R,x,xx);
        pushup(k);
    }
}
inline void updata(int k,int pi,int x){
    if(t[k].l==t[k].r){
        a[pi].x=1ll*a[pi].x*t[k].lazy.x%mod,t[k].lazy.x=1;
        for(reg i=1;i<=pcnt;++i){
            a[pi].np[i]+=t[k].lazy.np[i];
            while(x%p[i]==0)a[pi].np[i]--,x/=p[i];
            t[k].lazy.np[i]=0;
        }
        a[pi].x=1ll*a[pi].x*inv(x)%mod;
        t[k].x=a[pi].calc();
    }
    else{
        int mid=(t[k].l+t[k].r)>>1;
        pushdown(k);
        if(pi<=mid)updata(lt,pi,x);
        else updata(rt,pi,x);
        pushup(k);
    }
}
inline int query(int k,int L,int R){
    if(L<=t[k].l&&t[k].r<=R)return t[k].x;
    else{
        int mid=(t[k].l+t[k].r)>>1,ans=0;
        pushdown(k);
        if(L<=mid)ans=(1ll*ans+query(lt,L,R))%mod;
        if(R>mid)ans=(1ll*ans+query(rt,L,R))%mod;
        return ans;
    }
}
void solve(){
    read(n),read(mod);
    int dom=phi=mod;
    for(reg i=2;i*i<=mod;++i)
        if(dom%i==0){
            p[++pcnt]=i;
            phi=phi/i*(i-1);
            while(dom%i==0)dom/=i;
        }
    if(dom^1)p[++pcnt]=dom,phi=phi/dom*(dom-1);
    for(reg i=1,x;i<=n;++i)
        read(x),a[i]=num(x);
    build(1,1,n);
    int q,opt,l,r,x;
    read(q);
    while(q--){
        read(opt);
        if(opt==1){
            read(l),read(r),read(x);
            updata(1,l,r,x,num(x));
        }
        else if(opt==2){
            read(l),read(x);
            updata(1,l,x);
        }
        else{
            read(l),read(r);
            printf("%d\n",query(1,l,r));
        }
    }
}
int main(){
    solve();
    return qwq;
}
```


---

## 作者：QwQ蒟蒻wjr (赞：2)


>>codeforce题目链接：[
CodeForces 1109E E. Sasha and a Very Easy Test](https://codeforces.com/problemset/problem/1109/E)

>>洛谷题目链接：[CF1109E Sasha and a Very Easy Test](https://www.luogu.org/problem/CF1109E)

题解原发于[我的blog](https://wangjunrui.netlify.com/2019/10/27/cf1109e-sasha-and-a-very-easy-test/)

这是本蒟蒻发的第三篇黑题的题解，很开心。

一道很毒瘤的线段树题

本来蒟蒻兴高采烈的刷线段树的题，看到这道黑题，~~觉得很水~~决定刚一刚

这不是一道简单的线段树题

## 考虑直接相除，
结果$WA$了，这正是此题的难处

![](https://cdn.luogu.com.cn/upload/image_hosting/utud29xg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

## 考虑使用乘法逆元
但是样例二直接否定了这种情况，除数可能不与模数互质。

## 考虑将模数分解质因数。
在懒标记中标记模数的每个质因子个数

相乘时相加质因子，相除时相减质因子

乘数中除模数质因子以外的数得累乘标记

除数除模数质因子以外的数可以直接乘法逆元计算


记住得使用欧拉定理不能使用费马小定理，因为模数不一定是质数

### 费马小定理对于乘法逆元推导(a和p互质，p为质数):
$$a^{p-2}\equiv a^{-1}(mod\ p)$$

### 欧拉定理对于乘法逆元推导(a和p互质):
$$a^{\varphi(p)-1}\equiv a^{-1}(mod\ p)$$
其中
$$\varphi(x)=\prod_{i=1}^{n}\frac{p_i-1}{p_i}$$

$p_1, p_2……p_n$为$x$的所有质因数，$x$是不为$0$的整数。

## 最终在给几个标记的性质
1. 模数不会超过有$9$个不同的质因子（把前九个质数累乘试一试）。
2. 模数的单个质因子不会超过$20$个（$2^{20}>10^5$）
3. 除模数质因子外的数可以直接取模（反正乘法逆元行得通）

~~假黑题~~

直接运算即可，一下是蒟蒻的评测记录
![](https://cdn.luogu.com.cn/upload/image_hosting/zfz5bp2b.png)


~~这么简单的代码我都调了这么久一定是我太菜了~~

最后上代码：
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

template <typename T>
inline void read(T &x)
{
	x = 0;
	char s = getchar();
	bool f = false;
	while (!(s >= '0' && s <= '9'))
	{
		if (s == '-')
			f = true;
		s = getchar();
	}
	while (s >= '0' && s <= '9')
	{
		x = (x << 1) + (x << 3) + s - '0';
		s = getchar();
	}
	if (f)
		x = (~x) + 1;
}

namespace OUT
{

	char Out[1 << 25], *fe = Out, ch[25];
	int num = 0;

	template <typename T>
	inline void write(T x)
	{
		if (!x)
			*fe++ = '0';
		if (x < 0)
		{
			*fe++ = '-';
			x = -x;
		}
		while (x)
		{
			ch[++num] = x % 10 + '0';
			x /= 10;
		}
		while (num) *fe++ = ch[num--];
		*fe++ = '\n';
	}

	inline void flush()
	{
		fwrite(Out, 1, fe - Out, stdout);
		fe = Out;
	}
}  // namespace OUT
using namespace OUT;

#define re register
#define ll long long
#define ls (k << 1)
#define rs (k << 1 | 1)
#define node vector<int>

const int N = 1e5 + 10, S = 40;

int n, q, mod, phi, pcnt, a[N];

vector<int> pm;

struct Tree
{
	int c[S], sum, mul, high;  // high是剩余的数
} tree[N << 2];

inline node dec(int n)  //质因数分解
{
	node res;
	res.clear();
	for (re int i = 2; i * i <= n; i++)
		while (n % i == 0)
		{
			n /= i;
			res.push_back(i);
		}
	if (n > 1)
		res.push_back(n);
	return res;
}

inline void Unique(node &res)  //质因数去重(血的教训)
{
	sort(res.begin(), res.end());
	int u = unique(res.begin(), res.end()) - res.begin();
	while (res.size() > u) res.pop_back();
}

inline int getphi(int n)  //欧拉函数
{
	int ans = n;
	for (re int i = 2; i * i <= n; i++)
		if (n % i == 0)
		{
			ans = ans / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	if (n > 1)
		ans = ans / n * (n - 1);
	return ans;
}

inline int pow(int a, int b, int mod = ::mod)
{
	int ans = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1)
			ans = (ll)ans * a % mod;
	return ans;
}

inline int inv(int x)
{
	return pow(x, phi - 1);
}

inline void get(int res, int &ans, int *c)
{
	for (re int i = 1; i <= pcnt; i++)
		while (res % pm[i - 1] == 0)
		{
			res /= pm[i - 1];
			c[i]++;
		}
	ans = res % mod;
}

inline int calc(int v, int *dev)
{
	for (re int i = 1; i <= pcnt; i++) v = (ll)v * pow(pm[i - 1], dev[i]) % mod;
	return v;
}

inline void pushdown(int k)
{
	for (re int i = 1; i <= pcnt; i++)
	{
		tree[ls].c[i] += tree[k].c[i];
		tree[rs].c[i] += tree[k].c[i];
		tree[k].c[i] = 0;
	}
	tree[ls].sum = (ll)tree[ls].sum * tree[k].mul % mod;
	tree[rs].sum = (ll)tree[rs].sum * tree[k].mul % mod;
	tree[ls].mul = (ll)tree[ls].mul * tree[k].mul % mod;
	tree[rs].mul = (ll)tree[rs].mul * tree[k].mul % mod;
	tree[ls].high = (ll)tree[ls].high * tree[k].high % mod;
	tree[rs].high = (ll)tree[rs].high * tree[k].high % mod;
	tree[k].mul = tree[k].high = 1;
}

inline void pushup(int k)
{
	tree[k].sum = (tree[ls].sum + tree[rs].sum) % mod;
}

inline void build(int k, int l, int r)
{
	tree[k].mul = tree[k].high = 1;
	memset(tree[k].c, 0, sizeof(tree[k].c));
	if (l == r)
	{
		tree[k].sum = a[l] % mod;
		get(a[l], tree[k].high, tree[k].c);
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(k);
}

inline void update1(int k, int l, int r, int x, int y, int v, int *dev, int high)
{
	if (r < x || l > y)
		return;
	if (x <= l && r <= y)
	{
		for (re int i = 1; i <= pcnt; i++) tree[k].c[i] += dev[i];
		tree[k].sum = (ll)tree[k].sum * v % mod;
		tree[k].mul = (ll)tree[k].mul * v % mod;
		tree[k].high = (ll)tree[k].high * high % mod;
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	update1(ls, l, mid, x, y, v, dev, high);
	update1(rs, mid + 1, r, x, y, v, dev, high);
	pushup(k);
}

inline void update2(int k, int l, int r, int pos, int v, int *dev, int high)
{
	if (l == r)
	{
		tree[k].high = (ll)tree[k].high * inv(high) % mod;
		for (re int i = 1; i <= pcnt; i++) tree[k].c[i] -= dev[i];
		tree[k].sum = calc(tree[k].high, tree[k].c);
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	if (pos <= mid)
		update2(ls, l, mid, pos, v, dev, high);
	else
		update2(rs, mid + 1, r, pos, v, dev, high);
	pushup(k);
}

inline int query(int k, int l, int r, int x, int y)
{
	if (r < x || l > y)
		return 0;
	if (x <= l && r <= y)
		return tree[k].sum;
	pushdown(k);
	int mid = l + r >> 1;
	return (query(ls, l, mid, x, y) + query(rs, mid + 1, r, x, y)) % mod;
}

int main()
{
	read(n), read(mod), phi = getphi(mod);
	for (re int i = 1; i <= n; i++) read(a[i]);
	pm = dec(mod);
	Unique(pm);
	pcnt = pm.size();
	build(1, 1, n);
	read(q);
	for (re int i = 1, c[S], opt, a, b, x, v; i <= q; i++)
	{
		read(opt), read(a), read(b);
		memset(c, 0, sizeof(c));
		if (opt == 1)
		{
			read(x);
			get(x, v, c);
			update1(1, 1, n, a, b, x, c, v);
		}
		else if (opt == 2)
		{
			get(b, v, c);
			update2(1, 1, n, a, b, c, v);
		}
		else if (opt == 3)
			write(query(1, 1, n, a, b));
	}
	flush();
	return 0;
}
```
~~马蜂差评~~


---

## 作者：Genius_Z (赞：1)

由于模数与$x$不一定互质，所以无法直接把单点除法变成乘法。

那么我们考虑如何让它们互质，如果把共同的质因子除去，那么剩下的就是互质的两个数，直接用欧拉定理求乘法逆元即可。

欧拉定理：$a^{\phi(p)}\equiv 1(\bmod p)$

即：$a^{\phi(p)-1}\equiv a^{-1}(\bmod p)$，$\phi(p)$可以在$\sqrt p$的时间内求出；

由$\phi$的定义得：$\phi(n)=n*\prod\limits_{d|n \And\And d\in prime} \dfrac{d-1}{d}$，其中$d$为$n$的质因数。

那么我们在每个点维护$3$种标记，分别记为$mul$，$rem$，$fac$，分别代表当前的乘积，当前乘积除去公共质因子后剩余的值和每个共同质因子的个数。还要同时维护要求的答案，即区间和，记为$sum$。

每次在做乘法时，把$sum$、$mul$都乘上给出的$x$，然后将$rem$乘上$x$分解后剩余的值，将对应的质因数个数累加即可。

在做除法时，对于剩余的$rem$我们可以直接乘上$x$分解后剩余值的逆元，$fac$对应相减，然后通过$rem$和$fac$重新计算$sum$。由于是单点除，我们没有必要在乎叶节点的乘法标记$mul$，所以建树时直接置为$0$即可。$rem$标记初始时均为$1$，$mul$标记除叶节点外均为$1$。

由于$mod\le1e9+9$，则它的质因子个数不会超过$9$（最小$10$个质数的乘积= $2 *3* 5* 7* 11* 13 *17* 19* 23* 29 =6469693230=6.4e9>1e9+9$）。

那么时空复杂度均为$\Theta(n\log n)$级别。

$\large Code:$

```cpp
int n, m, p, fac[30], cnt, tmp[30], top, phi;
inl int getphi(int n) {
	re ans = n;
	for (re i = 2; i*i <= n; i++) {
		if (!(n%i)) {
			ans = 1ll * ans * (i - 1) / i;
			while (!(n%i))n /= i;
		}
	}
	if (n > 1)ans = 1ll * ans * (n - 1) / n;
	return ans;
}
inl void div(int n) {
	for (re i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			fac[++cnt] = i;
			while (n%i == 0)n /= i;
		}
	}
	if (n > 1)fac[++cnt] = n;
}
inl int work(int w) {
	top = 0;
	for (re i = 1; i <= cnt; i++) {
		tmp[i] = 0;
		while (w%fac[i] == 0) tmp[i]++, w /= fac[i];
	}
	return w % p;
}
struct node {
	int sum, fac[22], mul, rem;
}t[400005];
inl void upd(int k) { t[k].sum = (t[k << 1].sum + t[k << 1 | 1].sum) % p; }
inl void mul(int k, int w, int rem, int *tmp) {
	t[k].rem = 1ll * t[k].rem*rem%p;
	for (re i = 1; i <= cnt; i++) t[k].fac[i] += tmp[i];
	t[k].mul = 1ll * t[k].mul*w%p, t[k].sum = 1ll * t[k].sum*w%p;
}
inl int qpow(int x, int y = phi - 1) {
	re ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % p) if (y & 1)ret = 1ll * ret*x%p;
	return ret;
}
inl void divide(int k, int rem) {
	t[k].rem = 1ll * t[k].rem*qpow(rem) % p;
	re x = t[k].rem;
	for (re i = 1; i <= cnt; i++) {
		t[k].fac[i] -= tmp[i];
		x = 1ll * x * qpow(fac[i], t[k].fac[i]) % p;
	}
	t[k].sum = x;
}
inl void pushdown(int k) {
	if (t[k].mul != 1 || t[k].rem != 1) {
		mul(k << 1, t[k].mul, t[k].rem, t[k].fac), mul(k << 1 | 1, t[k].mul, t[k].rem, t[k].fac);
		t[k].mul = t[k].rem = 1;
		for (re i = 1; i <= cnt; i++)t[k].fac[i] = 0;
	}
}
inl void mul(int k, int l, int r, int x, int y, int w, int rem) {
	if (l >= x && r <= y) return mul(k, w, rem, tmp);
	re mid = l + r >> 1;
	pushdown(k);
	if (x <= mid)mul(k << 1, l, mid, x, y, w, rem);
	if (y > mid)mul(k << 1 | 1, mid + 1, r, x, y, w, rem);
	upd(k);
}
inl void divide(int k, int l, int r, int p, int w) {
	if (l == r)return divide(k, w);
	re mid = l + r >> 1;
	pushdown(k);
	p <= mid ? divide(k << 1, l, mid, p, w) : divide(k << 1 | 1, mid + 1, r, p, w);
	upd(k);
}
inl int query(int k, int l, int r, int x, int y) {
	if (l >= x && r <= y)return t[k].sum;
	re mid = l + r >> 1, ret = 0;
	pushdown(k);
	if (x <= mid)ret = query(k << 1, l, mid, x, y);
	if (y > mid)ret = (ret + query(k << 1 | 1, mid + 1, r, x, y)) % p;
	return ret;
}
inl void build(int k, int l, int r) {
	if (l == r) {
		t[k].sum = read<int>();
		t[k].rem = work(t[k].sum), t[k].sum %= p;
		for (re i = 1; i <= cnt; i++)t[k].fac[i] = tmp[i];
		return;
	}
	t[k].mul = t[k].rem = 1;
	re mid = l + r >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r), upd(k);
}
signed main() {
	n = read<int>(), p = read<int>(), phi = getphi(p), div(p);
	build(1, 1, n), m = read<int>();
	re op, x, y, w;
	while (m--) {
		op = read<int>(), x = read<int>(), y = read<int>();
		if (op == 1) w = read<int>(), mul(1, 1, n, x, y, w, work(w));
		else if (op == 2) divide(1, 1, n, x, work(y));
		else printf("%d\n", query(1, 1, n, x, y));
	}
}
```



---

## 作者：Luciylove (赞：0)

很生气，写个唐诗题写了好久。

感觉是看错题导致的。

题面略。

考虑这个直接做不太可做。因为不保证有逆元。

但是它保证整除，考虑对模数分解成：

$$mod = \prod_{i = 1}^{cnt} p_i^{c_i}$$

这种形式，那么我们如果可以整除可以直接维护对于 $p_i$ 的 $c_i$ 不是吗？

所以我们考虑对数质因数分解，维护 $10$ 个质因数的指数，余下的数可以用 exgcd 求逆元。

然后就做完了，代码很抽象，不知道为什么可以写到 3k。

[链接](https://codeforces.com/contest/1109/submission/236601065)

---

