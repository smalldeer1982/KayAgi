# Inversions After Shuffle

## 题目描述

You are given a permutation of integers from $ 1 $ to $ n $ . Exactly once you apply the following operation to this permutation: pick a random segment and shuffle its elements. Formally:

1. Pick a random segment (continuous subsequence) from $ l $ to $ r $ . All ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/150441d31156a32e0b2da63844d600138a543898.png) segments are equiprobable.
2. Let $ k=r-l+1 $ , i.e. the length of the chosen segment. Pick a random permutation of integers from $ 1 $ to $ k $ , $ p_{1},p_{2},...,p_{k} $ . All $ k! $ permutation are equiprobable.
3. This permutation is applied to elements of the chosen segment, i.e. permutation $ a_{1},a_{2},...,a_{l-1},a_{l},a_{l+1},...,a_{r-1},a_{r},a_{r+1},...,a_{n} $ is transformed to $ a_{1},a_{2},...,a_{l-1},a_{l-1+p1},a_{l-1+p2},...,a_{l-1+pk-1},a_{l-1+pk},a_{r+1},...,a_{n} $ .

Inversion if a pair of elements (not necessary neighbouring) with the wrong relative order. In other words, the number of inversion is equal to the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ a_{i}&gt;a_{j} $ . Find the expected number of inversions after we apply exactly one operation mentioned above.

## 样例 #1

### 输入

```
3
2 3 1
```

### 输出

```
1.916666666666666666666666666667
```

# 题解

## 作者：MatrixCascade (赞：6)

两个月前 vp 时不会做的题现在看到发现很简单。。

直接枚举 $l$ 和 $r$ 显然是不可行的，我们考虑每一对 $(i,j)$ 对答案的贡献。

先求出更改前的逆序对数量，再考虑更改后每一对的变化。不妨设 $i<j$

若 $a_i>a_j$，则如果选择的区间包含 $(i,j)$，就会有 $\frac{1}{2}$ 的**负**贡献，区间包含 $(i,j)$ 的概率是 $\frac{2(n-j+1)i}{n*(n+1)}$，贡献为 $-1*\frac{(n-j+1)i}{n*(n+1)}$ 

同理，若 $a_i<a_j$，**正**贡献为 $\frac{(n-j+1)i}{n*(n+1)}$

这个可以用树状数组快速统计，里面的值维护的是 $1-i$ 内的**下标之和**。

最后用逆序对数减去总贡献就是答案了。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
const int maxn=202020;
int a[maxn];
struct bit
{
    int c[maxn];
    int lowbit(int x){return x&(-x);}
    void upd(int x,int y=1){for(;x<=n;x+=lowbit(x))c[x]+=y;}
    int qry(int x){int ans=0;for(;x;x-=lowbit(x))ans+=c[x];return ans;}
    int operator[](int x) {return qry(x);}
}b,c;
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;
		upn rd(a[i]);
		double ans=0;
		double q=0;
		upn
		{
			q+=(c[n]-c[a[i]]);c.upd(a[i]);
			ans+=(n-i+1)*(b[n]-b[a[i]]);
			ans-=(n-i+1)*(b[a[i]]);
			b.upd(a[i],i);
		}
		ans/=n;ans/=(n+1);
		printf("%.10lf",q-ans);
	}
}
```


---

## 作者：木xx木大 (赞：4)

写个期望小水题练练手～

[CF749E Inversions After Shuffle](https://www.luogu.com.cn/problem/CF749E)

对于一个二元组 $(i,j)$，其被包含在所选区间内的概率为 $\frac{i(n-j+1)}{n(n+1)/2}$， $(i,j)$ 为逆序对的概率为 $\frac{1}{2}$，这种情况的总贡献为
$$
\sum_{i=1}^n\sum_{j=i+1}^n\frac{i(n-j+1)}{n(n+1)}=\frac{1}{n(n+1)}\sum_{i=1}^ni\sum_{j=i+1}^n(n-j+1)=\frac{1}{2n(n+1)}\sum_{i=1}^n{i(n-i)(n-i+1)}
$$
其不被包含在所选区间内的概率为 $1-\frac{i(n-j+1)}{n(n-1)/2}$，这种情况的总贡献为

$$
\sum_{i=1}^n\sum_{j=i+1}^n[a_i>a_j]\left(1-\frac{i(n-j+1)}{n(n+1)/2}\right)\\
=\sum_{i=1}^n\sum_{j=i+1}^n[a_i>a_j]-\frac{2}{n(n+1)}\sum_{i=1}^ni\sum_{j=i+1}^n[a_i>a_j](n-j+1)
$$

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FGF
{
	const int N=1e5+5;
	int a[N],n;
	long long c[N];
	double ans,sum;
	void updat(int x,int y){while(x<=n)c[x]+=y,x+=x&(-x);}
	long long query(int x){long long s=0;while(x)s+=c[x],x-=x&(-x);return s;}
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			sum+=1.0*i*(n-i)*(n-i+1);
		for(int i=n;i;i--)
			ans+=query(a[i])*i,updat(a[i],n-i+1);
		ans=-ans*2.0/n/(n+1)+sum/2.0/n/(n+1);
		memset(c,0,sizeof(c));
		for(int i=n;i;i--)
			ans+=query(a[i]),updat(a[i],1);
		printf("%.10f",ans);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：樱雪喵 (赞：3)

前置知识：树状数组求逆序对。

题目要求期望逆序对数，那么我们考虑**重排前下标**为 $(i,j)$ 的点对对答案的贡献。其中 $i<j$。

那么可以分为两种情况：

- $i,j$ 都在选中的段内  
设选中段为 $[l,r]$，则满足 $l\in [1,i],r\in [j,n]$，易知全部可能的选法有 $\dfrac{n(n+1)}{2}$ 种。  
那么选中的段满足此情况的概率为 $\dfrac{2i(n-j+1)}{n(n+1)}$。  
$(i,j)$ 在随机重排后有 $\dfrac{1}{2}$ 的概率构成逆序对，则 $(i,j)$ 对答案的贡献为 $\dfrac{i(n-j+1)}{n(n+1)}$。  
这种情况的总贡献为 

$$
\begin{aligned}
 ans&=\sum \limits_{i=1}^n \sum\limits_{j=i+1}^n \frac{i(n-j+1)}{n(n+1)}\\
&=\sum\limits_{i=1}^n\sum\limits_{j=1}^{n-i}\frac{ij}{n(n+1)}\\
&=\sum\limits_{i=1}^n \frac{i}{n(n+1)} \times \frac{(n-i+1)(n-i)}{2}\\
&=\sum\limits_{i=1}^n \frac{i(n-i+1)(n-i)}{2n(n+1)}\\
\end{aligned}
$$

- $i,j$ 不都在选中段内  
一共只有两种情况，那么显然第二种情况的概率为 $1-\dfrac{2i(n-j+1)}{n(n+1)}$。  
由于 $i,j$ 不都在选中段内，重排后 $i,j$ 的相对位置不变，则当且仅当 $a_i>a_j$ 时，$(i,j)$ 对答案有贡献。  
所以总贡献为 $\sum \limits_{i=1}^n \sum\limits_{j=i+1}^n [a_i>a_j]\dfrac{n(n+1)-2i(n-j+1)}{n(n+1)}$。  
把这个式子从减号处拆成两部分，在树状数组求逆序对的同时分别维护即可，具体可以参照代码。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int xr=0,F=1;char cr=getchar();
	while(cr<'0'||cr>'9') {if(cr=='-') F=-1;cr=getchar();}
	while(cr>='0'&&cr<='9')
	    xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
#define int long long
const int N=1e5+5;
int n,a[N];
double sum;// 全部乘起来会炸 long long，要用 double  
int tr[N],cnt[N];//tr 维护权值和，cnt 维护点的个数 
int lowbit(int x) {return x&(-x);}
void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=k,cnt[i]++;
}
int asktr(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=tr[i];
	return res;
}
int askcnt(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=cnt[i];
	return res;
}
double ans;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) sum+=1.0*i*(n-i+1)*(n-i);
	for(int i=1;i<=n;i++)
	{
		int ncnt=askcnt(n)-askcnt(a[i]-1);
		int ntr=asktr(n)-asktr(a[i]-1);
		ans+=(double)ncnt*n*(n+1);
		ans-=(double)2*ntr*(n-i+1);
		add(a[i],i);
	}
	double qwq=(double)ans/n/(n+1);
	double qaq=(double)sum/2/n/(n+1);
	printf("%.11lf\n",qwq+qaq);
	return 0;
}
```




---

## 作者：cmll02 (赞：2)

考虑两个位置 $i,j(i<j)$ 在什么情况下有贡献。

显然如果重排区间 $[l,r]$，有任意 $l\le x<y\le r$，$a_x,a_y$ 形成逆序对的概率是 $\dfrac 1 2$。

考虑当 $a_i<a_j$，那么如果区间包含 $i,j$，那么有 $\dfrac 1 2$ 的概率产生逆序对。

也就是说区间要满足 $l\le i, j\le r$。

容易算出贡献为 $\dfrac {(n-j+1)i}{n(n-1)}$。

同样如果 $a_i>a_j$ 也可以类似算。

枚举右端点 $j$，那么 $a_i<a_j$ 贡献为 $\sum\limits_{j < i\land a_j<a_i}\frac {(n-j+1)i}{n(n-1)}=\frac {(n-j+1)}{n(n-1)}\sum\limits_{j < i\land a_j<a_i}i$。

类似算出 $a_j<a_i$ 的贡献，树状数组维护 $\le i$ 的数的个数和下标之和。

```cpp
#define rg(x) for(int i=1;i<=(x);i++){
#define gr }
int a[1000005];
int n=read();
struct BIT{
	int a[1000005];
	void add(int x,int p)
	{
		for(;x<=n;x+=x&-x)a[x]+=p;
	}
	int operator[](int x)
	{
		int res=0;
		while(x)res+=a[x],x-=x&-x;
		return res;
	}
	int operator()(int l,int r){
		return (*this)[r]-(*this)[l-1];
	}
}t1,t2;
signed main()
{
	rg(n)a[i]=read();gr
	double ans=0;
	rg(n)
	//left gongxian
	int D=t1[a[i]-1];
	double rate=1.0*(n-i+1)/n/(n+1);
	ans+=t2[a[i]-1]*rate;
	ans+=t1(a[i]+1,n);
	D=t1(a[i]+1,n);
	rate=1.0*(n-i+1)/n/(n+1);
	//printf(". %.10lf\n",rate);
	ans-=rate*t2(a[i]+1,n);
	t1.add(a[i],1);
	t2.add(a[i],i);
	//printf("%.10lf\n",ans);
	gr
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：ELLIAS (赞：2)

### problem
给出一个1~n的排列,从中等概率抽取一个连续的片段,并对其进行等概率全排列,求排列后整个序列的逆序对的期望个数.

### solution
设所选的区间长度为l,考虑一个有序数对 ${a_i,a_j (i<j)}$ 并计算其贡献.
这样一来,就有两种情况:

1. ${a_i,a_j}$在所选的连续段中
2. ${a_i,a_j}$在所选的连续段之外

对于情况2,当${a_i<a_j}$时,很显然他们不会对答案有贡献.对于${a_i>a_j}$,对于区间 ${[1,j-1],[i+1,n]}$ 才会有贡献.但很显然地看到,区间 ${[i+1,j-1]}$ 被重复计算,要在计算概率时将其剪掉.如果使用 ${O(n^2)}$暴力显然会超时,可以将其用树状数组维护.

对于情况1就很简单,满足全排列概率为${\frac{1}{2}}$,满足连续段包含关系的概率为 ${2*\frac{i*(n-j+1)}{n*(n+1)}}$,概率相乘结果

$${P_{i,j}=\frac{i*(n-j+1)}{n*(n+1)}}$$

那么总期望为

$${P=\sum_{i=1}^n\sum_{j=i+1}^n  \frac{i*(n-j+1)}{n*(n+1)}}$$
$${P=\frac{1}{2}\sum_{i=1}^n\frac {i*(n-i)*(n-i+1)} {n*(n+1)}}$$

### code
加入操作
```cpp
inline void add (int x, int w, ll *c)
{
	while (x) {
		c[x] += w;
		x &= x-1;
	}
}
```
询问操作
```cpp
inline ll query (int x, ll *c)
{
	long long ret = 0;
	while (x<=n) {
		ret += c[x];
		x += lowbit(x);
	}
	return ret;
}
```
主程序
```cpp
static int main ()
{
	n = read();
	for (rint i = 1; i <= n; i ++)
	{
		a = read();
		tmp += query (a+1, c1);
		ans -= (double)query(a+1, c2)*(n-i+1);
		ans += (double)(n-i+1)*i*(i-1)/4.0;
		add (a, 1, c1); add (a, i, c2);
	}
	printf ("%.20lf", (double)(tmp+ans/((double)n*(n+1)/2.0)));
	return 0;
}
```

---

## 作者：SunburstFan (赞：0)

## [CF749E Inversions After Shuffle](https://www.luogu.com.cn/problem/CF749E)

### 题目大意

给定一个排列，随机打乱其中一部分，求期望的逆序对个数。

### 解题思路

考虑对于一个数对 $(a_i,a_j),i<j$，

如果 $(a_i,a_j)$ 被包含在打乱的区间中，则会产生一半的正贡献或一半的负贡献。

$(a_i,a_j)$ 被包含在打乱的区间中的概率为：$\frac{i\times (n-j+1)}{\frac{1}{2}\times n\times (n+1)} = \frac{2\times i \times (n-j+1)}{n\times (n+1)}$

那么：

$a_i>a_j$，则**减少的逆序对个数**增加 $\frac{1}{2}\times \frac{2\times i\times (n-j+1)}{n\times (n+1)} = \frac{i\times (n-j+1)}{n\times (n+1)}$。

同理，$a_i<a_j$，则**减少的逆序对个数**减少 $\frac{1}{2}\times \frac{2\times i\times (n-j+1)}{n\times (n+1)} = \frac{i\times (n-j+1)}{n\times (n+1)}$。

可以用树状数组维护，建两颗树状数组，一颗计算原序列逆序对个数，另一颗维护上述的**减少逆序对的个数**，二者相减即可。

这里给出核心代码（树状数组略）：

```cpp
void solve(){
    int n;
    cin>>n;

    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    Tr1.init(n),Tr2.init(n);

    double cnt=0,ans=0;
    for(int i=1;i<=n;i++){
        cnt+=Tr1(n)-Tr1(a[i]);
        Tr1.add(a[i],1);
    }

    for(int i=1;i<=n;i++){
        ans+=(n-i+1)*(Tr2(n)-Tr2(a[i]));
        ans-=(n-i+1)*Tr2(a[i]);
        Tr2.add(a[i],i);
    }
    ans/=n*(n+1);

    cout<<fixed<<setprecision(12)<<cnt-ans<<endl;
}
```

---

## 作者：Lu_xZ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF749E)

题意：给定一个 $1$ 到 $n$ 的排列，等概率选一段区间 $[l, r]$ 随机排序，求期望逆序对数。

$$
E = 
\dfrac{\sum(cnt_{[1, n]} - cnt_{[l, r]} + E_{len})}{\dfrac{n \times (n + 1)}{2}}
$$

> + $cnt_{[l, r]}$ 表示原序列 $[l, r]$ 内部逆序对数。
> + $E_{len}$ 表示长度为 $r - l + 1$ 的排列随机排序后的期望逆序对。

$E_i$ 怎么求？（~~直接 oeis，啪的一下很快啊~~

$$
E_i = \dfrac{i \times (i - 1)}{4}
$$

>proof：随机排序后，下标 $i$，$j$ 有 $\dfrac{1}{2}$ 的概率构成逆序对，所以总期望为 $(i, j)$ 对数乘 $\dfrac{1}{2}$。

因此

$$
\begin{aligned}
E =&   
cnt_{[1, n]} - \dfrac{\sum cnt_{[l, r]}}{\dfrac{n \times (n + 1)}{2}} + \dfrac{\sum_{i = 1}^n  (n - i + 1) \times E_i}{\dfrac{n \times (n + 1)}{2}} \\
=&
cnt_{[1, n]} - \dfrac{2\sum cnt_{[l, r]}}{n \times (n + 1)} + \dfrac{\sum_{i = 1}^n  (n - i + 1) \times i \times (i - 1)}{2 \times n \times (n + 1)} \\
=&
A + \dfrac{-2B + \dfrac{C}{2}}{n \times (n + 1)}

\end{aligned}
$$

$A$，$C$ 都很好做。

对于 $B$，下标为 $j$，$i$ 的逆序对对 $B$ 的贡献为包含 $[j, i]$ 的所有区间数 $j \times (n - i + 1)$，树状数组维护 $\sum j$ 即可。

```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
using namespace std;
using ll = long long;
constexpr int N = 1e5 + 5;

struct Fenwick_Tree {
	ll t[::N], n;
	void init(int x) {
		for(int i = 1; i <= (n = x); ++ i) {
			t[i] = 0;
		}
	}
	void add(int p, ll v = 1) {
		while(p) {
			t[p] += v;
			p -= p & -p;
		}
	}
	ll suf(int p) {
		ll ret = 0;
		while(p <= n) {
			ret += t[p];
			p += p & -p;
		}
		return ret;
	}
} bit;

ll n, a[N], A, B, C;

/*
长度为n的排列的期望逆序对数为 n * (n - 1) / 4
https://oeis.org/A001809
*/


int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n, bit.init(n);
	for(int i = 1; i <= n; ++ i) {
		cin >> a[i];
		A += bit.suf(a[i]);
		bit.add(a[i]);
	}
	bit.init(n);
	for(int i = 1; i <= n; ++ i) {
		B += ll(n - i + 1) * bit.suf(a[i]); 
		bit.add(a[i], i);
	}
	B *= 2;
	for(int i = 1; i <= n; ++ i) C += ll(n - i + 1) * i * (i - 1);
	C /= 2;
	double E = A + (double)(-B + C) / (n * (n + 1));  
	cout << fixed << setprecision(12) << E;
	return 0;
}
```

---

