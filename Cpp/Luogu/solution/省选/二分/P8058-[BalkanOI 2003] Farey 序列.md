# [BalkanOI 2003] Farey 序列

## 题目描述

把所有分子和分母都 $\leq n$ 的**最简真分数**从小到大排成一行，形成的序列称为 Farey 序列。

求出 $n$ 所对应的 Farey 序列中第 $k$ 小的数。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq n \leq 4 \times 10^4$，$1 \leq k \leq$ 符合条件的分数的个数。

## 样例 #1

### 输入

```
5 6```

### 输出

```
3 5```

# 题解

## 作者：luogu_gza (赞：41)

根号 3log 也太菜了吧！！！！！

**代码里面本来应该是杜教筛的部分我其实写的是线性筛，只要知道这是能做到 $O(n^{\frac 23}+\sqrt n \log^2 n)$ 的即可。**

stern-brocot tree，莫比乌斯反演，类欧几里得算法。

先来问一个问题，怎么求小于 $\frac pq$ 的最简真分数的个数？

不难注意到这就是 $\sum_{i=1}^{n}\sum_{j=1}^{n}[\frac ji \leq \frac pq][\gcd(i,j)=1]$，做简单的莫比乌斯反演就有答案为 $\sum_{d=1}^{n}\mu(d)\sum_{i=1}^{\lfloor \frac nd \rfloor} \lfloor \frac{pi}{q} \rfloor$。

后半部分是一个类欧的形式，最终求也确实用类欧求。

然后我们在 stern-brocot tree 上做二分。

先来看怎么通过一个 01 序列（即每一位表示向左还是向右走）获取到一个分数。

有结论 1：如果当前这个分数是由 $\frac ab$ 和 $\frac cd$ 合并而来的，我们将其表示为 2*2 矩阵：
```
a c
b d
```

向左走相当于把这个矩阵右乘

```
1 1
0 1
```

向右走相当于把这个矩阵右乘

```
1 0
1 1
```

然后注意到这个矩阵的幂是有规律的，具体规律观察我代码。

结论 2：任意一个 $\frac ab$ 在 stern-brocot tree 上走到它只需要转向 $O(\log(\max(a,b))$ 次。

我们就有一个很清晰的思路了，每次先判断这一次走的一条长链是走左边还是右边，然后再倍增求这一次走的长链走多远即可。

复杂度不知道是 3log 根号还是 2log 根号，反正考场上随便手搓了几组 $n=10^7$ 的数据都跑了 200ms 以下。

孩子是 3log 的，被干爆了，怎么优化呢？倍增的时候不要每次从 $\log(n)$ 开始倍增，而是先检查最大的 $d$ 满足能跳 $2^d$ 步，然后从 $d$ 往下倍增。

这样就是可爱的 2log 做法了。

```
#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define int long long
//	#define R read()
	#define pc putchar
	#define pb push_back
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--) 
	#define m1(a,b) memset(a,b,sizeof a)
	#define MT int _=read();while(_--)
	namespace IO{
		inline int read()
		{
			int x=0,flag=0;
			char ch=getchar();
			while(!isdigit(ch)){if(ch=='-') flag=1;ch=getchar();}
			while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
			if(flag) return -x;
			return x;
		}
		template<typename T> inline void write(T x)
		{
			if(x<0) pc('-'),x=-x;
			if(x>9) write(x/10);
			pc(x%10+'0'); 
		}
	}
	using namespace IO;
	
	struct mat{
		int a,b,c,d;
		mat(){a=b=c=d=0;}
		mat(int A,int B,int C,int D){a=A,b=B,c=C,d=D;}
		inline mat operator* (const int& A)const
		{
			if(A>0) return mat(a,b,c+a*A,d+b*A);
			return mat(a-A*c,b-A*d,c,d); 
		}
		inline pair<int,int> get()
		{
			return {a+c,b+d};
		}
	}now;
	int l[24],r[24];
	const int N=1e7+10,M=7e5+10;
	int n,k;
	int primes[M],cnt;
	bool vis[N];
	signed mu[N];
	inline void get_primes(int n)
	{
		mu[1]=1;
		fo(i,2,n)
		{
			if(!vis[i]) primes[++cnt]=i,mu[i]=-1;
			for(int j=1;j<=cnt&&i*primes[j]<=n;j++)
			{
				vis[i*primes[j]]=1;
				if(!(i%primes[j])) break;
				mu[i*primes[j]]=-mu[i];
			}
		}
		fo(i,1,n) mu[i]+=mu[i-1];
	}
	__int128 f(__int128 a,__int128 b,__int128 c,__int128 n)
	{
//		write(a),pc(' ');
//		write(b),pc(' ');
//		write(c),pc(' ');
//		write(n),pc(' ');
//		puts("");
		__int128 n1=(n+1),S1=n1*n/2;
		__int128 m=(a*n+b)/c,ac=a/c,bc=b/c,nm=n*m;
		if(m==0) return 0;
		if(!a) return n1*bc;
		if(a>=c&&b>=c) return (f(a%c,b%c,c,n)+S1*ac+n1*bc);
		__int128 lst=f(c,c-b-1,a,m-1);
		return nm-lst;
	}
	int calc(int p,int q)
	{
		int res=0;
		for(int l=1,r;l<=n;l=r+1)
		{
			r=n/(n/l);
			res+=(mu[r]-mu[l-1])*f(p,0,q,n/l); 
		}
//		cout<<p<<' '<<q<<' '<<res<<endl;
		return res;
	}
	void main(){
		get_primes(1e7);
		n=read(),k=read();
		now=mat(0,1,1,1);
		l[0]=1;
		r[0]=-1;
		fo(i,1,23) l[i]=l[i-1]+l[i-1];
		fo(i,1,23) r[i]=r[i-1]+r[i-1];
		int vv=calc(1,2);
		if(vv==k) return void(puts("1 2"));
		int flag=(vv<=k);//0:l 1:r
		while(1)
		{
			if(flag==0)
			{
				int sum=1;
				mat t=now;
				int d=23;
				fo(i,0,23)
				{
					mat tmp=t*l[i];
					pair<int,int> P=tmp.get();
					int num=calc(P.first,P.second);
					if(num<=k){d=i-1;break;}
				}
				rep(i,d,0)
				{
					mat tmp=t*l[i];
					pair<int,int> P=tmp.get();
					int num=calc(P.first,P.second);
					if(num>k) sum+=(1<<i),t=tmp;
				}
				rep(i,23,0) if(sum>>i&1) now=now*l[i];
			}
			else
			{
				int sum=1;
				mat t=now;
				int d=23;
				fo(i,0,23)
				{
					mat tmp=t*r[i];
					pair<int,int> P=tmp.get();
					int num=calc(P.first,P.second);
					if(num>=k){d=i-1;break;}
				}
				rep(i,d,0)
				{
					mat tmp=t*r[i];
					pair<int,int> P=tmp.get();
					int num=calc(P.first,P.second);
					if(num<k) sum+=(1<<i),t=tmp;
				}
				rep(i,23,0) if(sum>>i&1) now=now*r[i];
			}
			pair<int,int> P=now.get();
			int num=calc(P.first,P.second);
//			cout<<P.first<<' '<<P.second<<' '<<num<<endl;
			if(k==num) break;
			flag^=1;
		}
		pair<int,int> tmp=now.get();
		int x=tmp.first,y=tmp.second;
		write(x),pc(' '),write(y),puts("");
	}
}
signed main(){
//	freopen("fraction.in","r",stdin);
//	freopen("fraction.out","w",stdout); 
	gza::main(); 
}
```

---

## 作者：Limie (赞：14)

> 听闻存在 2log 做法震撼人心，中间忘了，后面忘了

----

这篇题解大致是对 gza 题解的补充说明和优化。

先简单梳理一下 gza 题解，首先是在 stern-brocot tree 上二分，观察到二分的过程相当于不断的向左跳和向右跳，跳长链的过程可以用倍增优化，每次跳完之后再 check，check 的过程可以用数论分块和类欧。

问题 1：为什么 gza 的做法的复杂度是 2log 的

观察到可以将向左跳和向右跳合并在一次看，如果本来的分数是 $\frac{b}{a},\frac{d}{c}$，那么假设向左跳了 $2^u+p$ 次，向右跳了 $2^v+q$ 次，那么 $a,c$ 中有一个至少增加了 $2^{\max(u,v)}$ 倍，而询问次数最多不超过 $4\max(u,v)$，则总询问次数不超过 $8\log n$。

问题 2：为什么 gza 的代码跑得这么慢

第一点是因为他质数筛的部分写的是 1e7，但是其他的部分实现也不好，比如说在 stern-brocot tree 的长链上跳 $n$ 次的部分就可以不使用矩阵而是简单的数学推导。

问题 3：这个做法还可以优化吗？

当然可以！

观察到在 stern-brocot tree 上二分的过程已经很难优化，考虑优化 check。

优化 check 也不难，将数论分块换成狄利克雷求和，平衡复杂度做到半只 log。

总复杂度 $O(n^{\frac{2}{3}}+\sqrt n \log^{1.5} n)$。

最优解榜二，无卡常到手！

---

## 作者：Smallbasic (赞：11)

来一种低于线性的做法

看到最简真分数就会想到二分答案。

假设我们已经有了一个 $x\over y$，那么根据定义，序列中比它小的数的个数有：

$$\sum_{i=1}^n \sum_{j=1}^i [i\perp j][{j\over i}<{x\over y}]$$

$[i\perp j]$ 可以套路莫反掉：

$$\sum_{i=1}^n \sum_{j=1}^i \sum_{d|\gcd(i,j)}\mu(d) [{j\over i}<{x\over y}]$$

$$=\sum_{d}\mu(d)\sum_{i=1}^{n\over d}\sum_{j=1}^i [{j\over i}<{x\over y}]$$

$[{j\over i}<{x\over y}]$ 可以看成 $[j<{ix\over y}]$，故有:

$$\sum_d \mu(d)\sum_{i=1}^{n\over d}\lfloor{ix\over y}\rfloor$$

前面可以整除分块套杜教筛，后面是类欧板子。我们把这个东西记作 $f({x\over y})$

但是最简真分数这个东西我们不好二分，考虑一个叫 Stern-Brocot 树的东西，大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/oeqik4ed.png)

假设我们已经得到了只遍历前 $i-1$ 层的中序遍历序列（在前面后面添上 ${0\over 1}$ 和 $1\over 0$ 来表示 $0$ 和 $+\infty$），其中 ${a\over b}$ 和 $c\over d$ 是相邻的两项，那么就将 $a+c\over b+d$ 插入它们之间得到只遍历前 $i$ 层的中序遍历序列。并且它是满二叉树，所以树的形态可以确定。

直接说有点玄学，建树的伪代码：

```cpp
int build(int a, int b, int c, int d) {
	tr[++ndnum].p = a + c; tr[ndnum].q = b + d;
	tr[ndnum].ls = build(a, b, a + c, b + d);
	tr[ndnum].rs = build(a + c, b + d, c, d);
	return ndnum;
}
```

因为这个树有无穷层，直接运行以上代码显然会挂。

这棵树有个性质，树的中序遍历一定有序且树上每个数一定是最简分数。证明考虑归纳法：

先证有序，显然若 ${a\over b} < {c\over d}$，则 ${a\over b} < {a+c\over b + d} < {c\over d}$

然后证分数最简，我们先证明如下结论：若 $a\over b$, $c\over d$ 是只遍历前 $i$ 层的中序遍历序列中相邻的两项，那么 ${c\over d}-{a\over b}={1\over bd}$

仍是归纳法，假设对于前 $1, 2, ... , i - 1$ 层都满足条件，那么对于前 $i-1$ 层的中序遍历中相邻的 $a\over b$, $c\over d$, ${c\over d}-{a\over b}={bc-ad\over bd}={1\over bd} \rightarrow bc-ad=1$，那么有：

$${a+c\over b+d}-{a\over b}={ab+bc-ab-ad\over b(b+d)}={bc-ad\over b(b+d)}={1\over b(b+d)}$$

$${c\over d} - {a+c\over b+d}={bc+dc-ad-cd\over (b+d)d}={bc-ad\over (b+d)d}={1\over (b+d)d}$$

我们再来看，若 $bc-ad=1$ 有解，由裴蜀定理的 $a\perp b$、$c\perp d$。

这棵树上 $1\over 2$ 为根的子树里面就包含了所有最简真分数。

然后就有了显然的想法，我们在这个树上二分，假设当前在 $x\over y$，若 $f({x\over y})=k$ 就是答案，$f({x\over y})<k$ 就往右子树走，否则往左子树走。

但这样时间复杂度是假的，例如 $k=1$ 的时候它就会一直走左子树走到第 $n$ 层。怎么优化？

我们称之前是向左/右子树走，现在又改变方向向右/左子树走的一次事件为 "拐"，设 $F(n)$ 为拐 $n$ 次能到的分数中最小的分母，构造显然是不停的拐 $n$ 次。所以有 $F(n)=F(n-1)+F(n-2)$，是斐波那契额数列。因此到分母为 $n$ 的分数最多只会拐大约 $\log n$ 次。我们可以倍增在这个方向上倍增该走多远，用 $\log n$ 的时间走到下一个拐点。

复杂度大概 $\Theta(n^{2\over3} + \sqrt{n}\log^3 n)$，但是远远跑不满。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline int read() {
	register int s = 0; register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s;
}

inline ll readll() {
	register ll s = 0; register char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s;
}

unordered_map<int, int> smu;
bool notprime[5000001];
int n, prime[5000001], top = 0, mu[5000001];
ll m;

inline void pre() {
	mu[1] = 1;
	for (register int i = 2; i <= 5000000; ++i) {  
    	if (!notprime[i]) prime[++top] = i, mu[i] = -1;
    	for (register int j = 1; j <= top; ++j) {  
        	if (i * prime[j] > 5000000) break;  
        	notprime[i * prime[j]] = 1;
        	if (!(i % prime[j])) {  
	            mu[i * prime[j]] = 0;
    	        break;  
	        } else mu[i * prime[j]] = -1 * mu[i];
    	} 
	}
	for (register int i = 2; i <= 5000000; ++i) mu[i] += mu[i - 1];
}

inline int calcmu(int n) {
    if (n <= 5000000) return mu[n];
	if (smu.find(n) != smu.end()) return smu[n];
	ll rt = 1;
    for (register unsigned int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        rt -= (r - l + 1) * calcmu(n / l);
    }
	return smu[n] = rt;
}

struct frac {
	ll p, q;
};

inline bool cmp(frac a, frac b) {
	return 1ll *a.p * b.q < 1ll * a.q * b.p;
}

inline ll f(ll a, ll b, ll c, ll n) {
	if (a == 0) return 1ll * n * (b / c);
	if (a > c || b > c) return 1ll * n * (n + 1) / 2 * (a / c) + (1ll * (n + 1) * (b / c)) + f(a % c, b % c, c, n);
	ll m = (1ll * a * n + b) / c;
	return (1ll * n * m) - f(c, c - b - 1, a, m - 1);
}

inline ll calc(frac a) {
	ll res = 0;
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		res += 1ll * (calcmu(r) - calcmu(l - 1)) * f(a.p, 0, a.q, n / l);
	} return res;
}

ll lim = 1;

inline void solve(ll m) {
	frac l, r;
	l.p = 0; l.q = 1; r.p = 1; r.q = 1;
	while (cmp(l, r)) {
		frac a; a.p = l.p + r.p; a.q = l.q + r.q;
		ll t = calc(a);
		if (t == m) {
			printf("%d %d\n", a.p, a.q);
			return ;
		}
		if (t < m) {
			for (int i = lim; i; i >>= 1) {
				frac t;
				if ((n - l.q) / r.q < i) continue;
				t.p = l.p + 1ll * i * r.p;
				t.q = l.q + 1ll * i * r.q;
				if (calc(t) < m)  l = t;
			}
		} else {
			for (int i = lim; i; i >>= 1) {
				frac t;
				if ((n - r.q) / l.q < i) continue;
				t.p = r.p + 1ll * i * l.p;
				t.q = r.q + 1ll * i * l.q;
				if (calc(t) > m)  r = t;
			}
		}
	}
}

int main() {
	pre();
	n = read(); int k = read();
	while (lim * 2ll <= n) lim *= 2ll;
	solve(k);
	return 0;
}
```


---

## 作者：_Fontainebleau_ (赞：9)

### 题意

$n$ 阶 Farey 序列求第 $k$ 项。

### 做法

~~为什么讨论区会有类欧？一定是我太逊了。~~

二分那个数，求当前 Farey 序列中比它小的个数。

具体地，设 $\operatorname{Rank}(x)$ 表示 $n$ 级 Farey 数列有几个小于 $x$，$f(i)$ 表示 $n$ 阶 Farey 数列中分母为 $i$，且小于 $x$ 的数量。

则显然 $\displaystyle\operatorname{Rank}(x)=\sum_{i=1}^nf(i),f(i)=\lfloor{ix}\rfloor-\sum_{d<i,d\mid{i}}f(d)$，$f(i)$ 可以 $O(n\log{n})$ 筛。

由于每次都要调用，最后就是 $O(n\log^2n)$。

改进：

注意到 $\operatorname{Rank(x)}$ 是 $\left\lfloor{ix}\right\rfloor,1\le{i}\le{n}$ 的线性组合。再回顾 $f(i)$ 的式子，这个系数是与 $x$ 无关的。这启示我们先预处理出 $\operatorname{Rank}(x)$ 中 $\left\lfloor{ix}\right\rfloor$ 的系数，不用每次重新算 $f$。

具体而言，令 $g(i)$ 表示 $\left\lfloor{ix}\right\rfloor$ 的系数。**$\left\lfloor{ix}\right\rfloor$ 第一次出现是在 $f(i)$ 中，此后，每一次一旦出现 $\left\lfloor{tx}\right\rfloor,t=ki,k\in\mathbb Z_{>1}$，$\left\lfloor{ix}\right\rfloor$ 的系数都一定增加 $\left\lfloor{tx}\right\rfloor$ 系数的相反数**，所以我们可以得到：$\displaystyle g(i)=1-\sum_{t>i,i\mid{t}}g(t)$。我们同样可以 $O(n\log{n})$ 先筛出来 $g$，然后每次可以 $O(n)$ 求 $\operatorname{Rank}(x)$。最后时间复杂度就是 $O(n\log{n})$。

最后再在 Farey 序列上找这个数即可。比较简单，不再赘述？

### 代码

```cpp
#include<bits/stdc++.h>
#define eps 1e-9
using namespace std;
int n,k,c[100005];
inline void S(int n)
{
	for(int i=1;i<=n;i++)	c[i]=1;
	for(int i=n;i>=1;i--)
		for(int t=i*2;t<=n;t+=i)
			c[i]-=c[t];
}
inline int C(double x)
{
	int ans=0;
	for(int i=1;i<=n;i++)	ans+=c[i]*int(x*i);
	return ans;
}
void find(double x,int &p,int &q)
{
    p=0,q=1;
    for(int i=1;i<=n;i++)
	{
        int tmp=x*i;
        if(abs(double(p)/double(q)-x)>abs(double(tmp)/double(i)-x))
            p=tmp,q=i;
    }
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
    n=read(),k=read();
    S(n);
    double l=0,r=1;
    while(r-l>eps)
	{
        double mid=(l+r)/2;
        if(C(mid)<k)	l=mid;
		else r=mid;
    }
    int p,q;
    find(r,p,q);
    printf("%d %d\n",p,q);
    return 0;
}
```




  




---

## 作者：dadaaa (赞：5)

# [P8058](https://www.luogu.com.cn/problem/P8058) 题解

由于本人遇到这题时是加强版，$n\le 10^7$，因此思路更像是解决加强版的。

这是一个不使用 stern-brocot tree 的 $O(n + \sqrt{n} \times \log^2 n)$ 做法。

首先我们考虑对于一个分数 $\frac{q}{p}$，求出小于他的最简分数数量，是：

$$

 \sum_{i=1}^{n} \sum_{j=1}^{i} [\gcd(i,j)=1][\frac{j}{i} \le \frac{q}{p}]

$$

这个 $\gcd=1$ 有点恶心，考虑基础莫反变成：

$$

 \sum_{d=1}^{n} \mu(d) \sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\frac{j}{i} \le \frac{q}{p}]

$$

缩放了一点限制。

我们首先对他整除分块，于是问题就变成了求 $O(\sqrt{n})$ 次 

$$

\sum_{i=1}^{n}\sum_{j=1}^{n}[\frac{j}{i} \le \frac{q}{p}]\\

= \sum_{i=1}^{n} \lfloor i\times \frac{q}{p} \rfloor

$$

这可以直接类欧几里德完成。

现在，我们会求一个分数的排名了，我们显然可以二分。而直接对答案分数二分是困难的，因此我们此时有两种思路，把分数映射成小数二分，或把所有分数映射成同底的分数进行二分。

对于任意两个分数 $\frac{a}{b},\frac{c}{d}$，我们希望找到一个 $x$ 使得 $x \times (\frac{a}{b}-\frac{c}{d})>1$，此时所有分数都能够对应一段 $\frac{i}{x}$ 的区间，然后我们就进行同分母的分数二分了。

式子变成 $x \ge \frac{ac}{bc-ad}$，此时 $bc-ad$ 是可以取到 $O(1)$ 的，$ac$ 是可以取到 $O(n^2)$ 的，因此我们 $x$ 需要取到 $n^2$，此时就可以二分了。

二分出最小的 $\frac{i}{x}$ 的排名是 $k$ 的，然后找出所有位置在 $(\frac{i-1}{x},\frac{i}{x}]$ 之间的分数是容易 $O(n)$ 的。（如果有多个，那这些数一定相等，取最小的即可）

因此总复杂度就变成了 $O(n + \sqrt{n} \times \log^2 n)$。

代码如下：

```cpp

/*
P8058.cpp
File IO
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define ll long long
#define i128 __int128
#define db double

using namespace std;
const db eps=1e-6;
const int inf=0x3f3f3f3f;
const ll lnf=(ll)1e18+10;
ll read() {
	ll o=0,w=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') w=-1;c=getchar();}
	while(c>='0'&&c<='9') {o=o*10+c-'0';c=getchar();}
	return o*w;
}

namespace dada {

const int N=1e7+10;
int n;
ll k;
int pri[N],cnt;
bool ntp[N];
int mu[N],summu[N];
i128 EL(i128 a,i128 b,i128 c,i128 n) {
	if(!a) return (b/c)*(n+1);
	if(b>=c||a>=c) return (a/c)*n*(n+1)/2+(b/c)*(n+1)+EL(a%c,b%c,c,n);
	else {
		i128 m=(a*n+b)/c;
		return n*m-EL(c,c-b-1,a,m-1);
	}
}
ll Calc(ll p,ll q) {
	ll res=0;
	for(int l=1,r;l<=n;l=r+1) {
		r=n/(n/l);
		res=(res+(summu[r]-summu[l-1])*EL(p,0,q,n/l));
	}
	return res;
}
int Main() {
	n=read(),k=read();
	mu[1]=1;
	for(int i=2;i<=n;i++) {
		if(!ntp[i]) {
			pri[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++) {
			ntp[i*pri[j]]=1;
			if(i%pri[j]==0) {
				mu[i*pri[j]]=0;
				break;
			}
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++) summu[i]=summu[i-1]+mu[i];
	ll l=1,r=1ll*n*n,res=-1;
	while(l<=r) {
		ll mid=(l+r)/2;
		if(Calc(mid,1ll*n*n)>=k) res=mid,r=mid-1;
		else l=mid+1;
	}
	assert(res!=-1);
	// cerr<<res<<'\n';
	pair<ll,ll> ans(inf,1),tmp(res-1,1ll*n*n);
	for(int i=1;i<=n;i++) {
		pair<ll,ll> cur((i128)tmp.first*i/tmp.second+1,i);
		if(cur.first*ans.second<ans.first*cur.second) ans=cur;
	}
	printf("%lld %lld\n",ans.first,ans.second);
	return 0;
}






}

int main() {
	int T=1;
	while(T--) {dada::Main();}
	return 0;
}

/*
cd P8058
g++ P8058.cpp -o P8058 -std=c++14 -Wall -O2 -static -lm 
time ./P8058
cp 1.in .in
diff .out 1.ans -w | head -n 10
*/



```

---

## 作者：Sya_Resory (赞：4)

内容：Stern-Brocot Tree、Farey 序列

## Part 1. Stern-Brocot Tree

一种构造最简分数的数据结构。

考虑从边界条件开始构造。最小值是 $\frac 01$（即 $0$），最大值是 $\frac 10$（把它看做 $\infty$）。

接下来，我们每次在相邻的两个分数 $\frac ab$ 和 $\frac cd$ 之间插入分数 $\frac {a+c}{b+d}$，完成一次迭代。这样无限迭代下去，就得到了 Stern-Brocot 树。

听这个叙述感觉一点也不像树对不对。下面来看一张图（来自 oi-wiki）：

![](https://oi-wiki.org/math/number-theory/images/stern-brocot1.png)

假设根节点深度为 $1$，那么 $i$ 次迭代后的序列就是 Stern-Brocot 树中深度 $\le i$ 的部分的中序遍历。

显然，构造出来的序列一定是有序的（因为有 $\frac ab<\frac cd$，易证得 $\frac ab<\frac {a+c}{b+d}<\frac cd$）。

同时，序列中所有的分数一定是最简分数。

略证（还是来自 oi-wiki）：

为证明最简性，我们首先证明对于序列中连续的两个分数 $\frac ab<\frac cd$：

$$
bc-ad=1
$$

显然，我们只需要在 $bc-ad=1$ 的条件下证明 $\frac ab,\frac {a+c}{b+d},\frac cd$ 的情况成立即可。

$$
b\left(a+c\right)-a\left(b+d\right)=bc-ad=1
$$

后半部分同理。证明了这个，利用扩展欧几里德定理，如果上述方程有解，显然 $\gcd\left(a,b\right)=\gcd\left(c,d\right)=1$。这样就证完了。

有了上面的证明，我们可以证明 $\frac ab<\frac cd$。

于是通过这样的构造，我们就可以得到所有最简分数。这玩意可以用来拟合双曲线，求双曲线下整点个数（见 DIVCNT1），这里就不展开讲了。

## Part 2. Farey 序列

~~其实这俩玩意差不多~~

一个 $n$ 阶的 Farey 序列定义为所有分子分母 $\le n$ 的最简真分数由小到大排列的序列，记为 $F_n$。

显然，这玩意的构造方式和 Stern-Brocot 树差不多，注意判断一下分母大小就行了。这样我们得到了 $n$ 阶 Farey 序列的递归构造方式。

有没有递推的呢？

考虑我们得到了 $n$ 阶 Farey 序列中两个相邻的分数 $\frac ab,\frac cd$，想要求出下一个分数 $\frac pq$。

首先，由于 $\frac ab,\frac cd,\frac pq$ 相邻，那么显然有 $b+d>n,d+q>n$（否则它们中间就可以继续插入）。

然后对于 $n$ 进行亿些变换：
$$
\begin{aligned}
n=&\ \frac {b+n}dd-b\\
\ge&\ q\\
>&\ n-d\\
=&\ \left(\frac {b+n}d-1\right)d-b
\end{aligned}
$$

$\therefore q=\left\lfloor\frac {b+n}d\right\rfloor d-b$

又 $pd-cq=1$：
$$
\begin{aligned}
p=&\ \frac {cq+1}d\\
=&\ \frac{\left\lfloor\frac {b+n}d\right\rfloor c-ad-(bc-1)}d\\
=&\ \left\lfloor\frac {b+n}d\right\rfloor c-a
\end{aligned}
$$
于是我们得到递推式：
$$
\left\{
\begin{aligned}
p=&\ \left\lfloor\frac {b+n}d\right\rfloor c-a\\
q=&\ \left\lfloor\frac {b+n}d\right\rfloor d-b
\end{aligned}
\right.
$$
$n$ 阶的 Farey 序列有个长度的近似公式：$\operatorname{len}\left(F_n\right)\approx0.304n^2$ ~~但我不会证~~，所以上面这两种构造方式是 $O\left(n^2\right)$ 的。

~~那这题咋做呢~~

## Part 3. 本题解法

> 求 $n$ 阶 Farey 序列的第 $k$ 项。
>
> $n\le 4\times10^4$

考虑在 Stern-Brocot 树上二分。假设当前的分数为 $\frac xy$，则序列中 $\le\frac xy$ 的数个数（即 $\frac xy$ 的位置）为：
$$
\begin{aligned}
\sum_{i=1}^n\sum_{j=1}^n\left[\gcd(i,j)=1\right]\left[\frac ji\le\frac xy\right]=&\ \sum_{d=1}\mu\left(d\right)\sum_{i=1}^{\left\lfloor\frac nd\right\rfloor}\sum_{j=1}^{\left\lfloor\frac nd\right\rfloor}\left[j\le \left\lfloor\frac{ix}{y}\right\rfloor\right]\\
=&\ \sum_{d=1}\mu\left(d\right)\sum_{i=1}^{\left\lfloor\frac nd\right\rfloor}\left\lfloor\frac{ix}{y}\right\rfloor\\
=&\ \sum_{d=1}\mu\left(d\right)f\left(x,0,y,\left\lfloor\frac nd\right\rfloor\right)\\
\end{aligned}
$$
其中 $f(a,b,c,n)=\sum_{x=0}^n\left\lfloor\frac{ai+b}c\right\rfloor$，可以用类欧几里得算法算出。

~~复杂度 $\color{white}{O(n+\sqrt n\log^2n)}$。~~

upd：复杂度假了，但 lz 半退役了qwq，有时间再看一下

code：

```cpp
#include <cstdio>

const int maxn = 4e4 + 5;

int n,k,p,q,p1,q1,p2,q2;
int pri[maxn],mu[maxn];
bool isp[maxn];

inline void Init() {
    mu[1] = 1;
    for(int i = 2;i <= n;i ++) {
        if(!isp[i]) pri[++ pri[0]] = i,mu[i] = -1;
        for(int j = 1;j <= pri[0] && i * pri[j] <= n;j ++) {
            isp[i * pri[j]] = true;
            if(!(i % pri[j])) { mu[i * pri[j]] = 0; break; }
            mu[i * pri[j]] = -mu[i];
        }
    }
    for(int i = 2;i <= n;i ++) mu[i] += mu[i - 1];
}

int f(int a,int b,int c,int n) {
    int ac = a / c,bc = b / c,m = (a * n + b) / c;
    if(a == 0) return (n + 1) * bc;
    if(a >= c || b >= c) return n * (n + 1) / 2 * ac + (n + 1) * bc + f(a % c,b % c,c,n);
    return m * n - f(c,c - b - 1,a,m - 1);
}

int getPos(int x,int y) {
    int cnt = 0;
    for(int r,l = 1;l <= n;l = r + 1) {
        r = n / (n / l);
        cnt += (mu[r] - mu[l - 1]) * f(x,0,y,n / l);
    }
    return cnt;
}

int main() {
    scanf("%d%d",&n,&k);
    Init();
    p1 = 0,q1 = p2 = q2 = 1;
    for(;;) {
        p = p1 + p2,q = q1 + q2;
        int pos = getPos(p,q);
        if(pos == k) break;
        if(pos > k) p2 = p,q2 = q;
        else p1 = p,q1 = q;
    }
    printf("%d %d\n",p,q);
    return 0;
}
```



---

## 作者：WaterSun (赞：4)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DP8058%20%5BBalkanOI2003%5D%20Farey%20%E5%BA%8F%E5%88%97/)

不知道为什么都做这么复杂。

# 思路

考虑二分第 $k$ 小的数 $x$，思考怎么 `check`。令小于 $x$ 的数量为 $num$，则如果 $num < k$ 则返回 `true`，否则返回 `false`。

问题转化为了求 $num$。定义 $dp_i$ 表示分母为 $i$ 的并小于 $x$ 的数的数量。

显然如果不考虑真分数这个限制，则有：

$$
dp_i = \lfloor i \times x \rfloor
$$

加上真分数的限制就是：

$$
dp_i = \lfloor i \times x \rfloor - \sum_{d \mid i \wedge 1 < d < i}dp_d
$$

然后显然就有：

$$
num = \sum_{i = 1}^{n}{dp_i}
$$

小数转分数，你去枚举分母，然后计算出分子，找与 $x$ 误差最小的即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define double long double

using namespace std;

typedef pair<int,int> pii;
const int N = 4e4 + 10;
double eps = 1e-10;
int n,k;
int f[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline pii get(double x){
    int a = 0,b = 1;
    for (re int i = 1;i <= n;i++){
        int t = ceil(x * i);
        if (fabs(1.0 * a / b - x) > fabs(1.0 * t / i - x)) a = t,b = i;
    }
    return {a,b};
}

inline bool check(double x){
    int num = 0;
    for (re int i = 1;i <= n;i++){
        f[i] = i * x;
        for (re int j = 2;j * j <= i;j++){
            if (i % j == 0){
                f[i] -= f[j];
                if (j != i / j) f[i] -= f[i / j];
            }
        }
        num += f[i];
    }
    return (num < k);
}

int main(){
    n = read(),k = read();
    double l = 0.0,r = 1.0;
    while (r - l > eps){
        double mid = (l + r) / 2.0;
        if (check(mid)) l = mid;
        else r = mid;
    }
    pii ans = get(l);
    printf("%d %d",ans.fst,ans.snd);
    return 0;
}
```

---

## 作者：Cynops (赞：2)

tag：整除分块，线性筛，类欧几里德算法，stern-brocot tree。

首先考虑如何求 $\dfrac{p}{q}$ 的排名
${\rm Rnk}(p,q) = \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[(i,j)=1][jq \le ip]$，莫比乌斯反演一下得到 ${\rm Rnk}(p, q) = \sum\limits_{d=1}^{n}\mu(d)\sum\limits_{i=1}^{[\frac{n}{d}]} [\frac{pi}{q}]$。后面这个东西可以类欧几里德算法做，套个线性筛和整除分块可以 $\mathcal O(n)$ - $\mathcal O({\sqrt n}\log n)$ 求出。

我们考虑二分出一个 $\frac{p}{q}$ 满足 ${\rm Rnk}(p,q) = k$，但我们不想写复杂的 stern-brocot tree 上二分，也怕实数二分精度不够，该怎么办呢？

考虑倍增，每次 $(p,q)\to (2p,2q)$，若 $(p + 1, q)$ 仍然满足 ${\rm Rnk} \le k$，则 $p \to p + 1$。我们倍增 $\log$ 次即可找到一组满足 ${\rm Rnk}(p,q) = k$ 的 $(p,q)$。（这里我不会证明，有老哥证出来了可以发我学习一下）。

现在就可以在 stern-brocot tree 上二分找到 $(p,q)$ 在 $n$ 阶 Farey 序列上的前驱了，时间复杂度 $\mathcal O(n + {\sqrt n} \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef __int128_t i128;
#define rep(i,l,r) for (int i = l; i <= r; i ++)
#define rrp(i,l,r) for (int i = r; i >= l; i ++)
const int N = 1e7 + 5;
int n, mu[N]; LL k;
bool vis[N];
LL F (LL a, LL b, LL c, LL n)
{
	if (!a) return (b / c) * (n + 1);
	if (a >= c || b >= c) 
    return F(a % c, b % c, c, n) + (n + 1) * (b / c) 
    + 1LL * (a / c) * n * (n + 1) / 2;
	LL f = ((i128)a * n + b) / c;
  if (f == 0) return 0;
	return n * f - F(c, c - b - 1, a, f - 1);
}
LL calc(LL p, LL q) {
  LL res = 0;
  for (int l = 1, r; l <= n; l = r + 1)
    res += (mu[r = n / (n / l)] - mu[l-1]) * F(p, 0, q, n / l);
  return res;
}
void fakemain() {
  cin >> n >> k, mu[1] = 1;
  static int _m = 0, p[N / 10];
  rep (i, 2, n) {
    if (!vis[i]) p[++ _m] = i, mu[i] = -1;
    for (int j = 1; j <= _m; j ++) {
      if (i > n / p[j]) break;
      vis[i * p[j]] = 1;
      if (i % p[j] == 0) break;
      mu[i * p[j]] = -mu[i];
    }
  }
  rep (i, 1, n) mu[i] += mu[i-1];
  LL x = 0, y = 1;
  rep (i, 1, 60) {
    x <<= 1, y <<= 1;
    if (calc(x + 1, y) <= k) ++ x;
  }
  int a = 0, b = 1, c = 1, d = 1;
  while (1) {
    int e = a + c, f = b + d;
    if (f > n) break;
    if ((i128)e * y < (i128)f * x) a = e, b = f;
    else c = e, d = f;
  }
  cout << a << ' ' << b;
}
signed main() {
  int T = 1;
  // cin >> T;
  while (T --) fakemain();
  cerr << 1. * clock() / 1000000 << "s\n";
  return 0;
}
```

---

## 作者：harmis_yz (赞：2)

## 分析

考虑二分答案。

对于当前二分的答案 $x$，设 $cnt$ 表示 Farey 序列中 $\frac{p}{q} \le x$ 的满足条件的数量。对于一组 $(i,j)$，若 $\frac{j}{i}\le x$，则 $j \le\lfloor i \times x \rfloor$。得到暴力式子：

$$cnt=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{\lfloor i \times x \rfloor}[\gcd(i,j)=1]$$

定义 $f_i=\sum\limits_{j=1}^{\lfloor i \times x \rfloor}[\gcd(i,j)=1]$。根据容斥，有：

$$f_i=\lfloor i \times x \rfloor-\sum\limits_{j=1}^{\lfloor i \times x \rfloor}[\gcd(i,j) >1]$$

将 $\gcd(i,j)$ 的值表示出来：

$$f_i=\lfloor i \times x \rfloor-\sum\limits_{j=1}^{\lfloor i \times x \rfloor}[\gcd(i,j) =k \land k>1]$$

把 $k$ 提出来：

$$f_i=\lfloor i \times x \rfloor-\sum\limits_{k=2}^{i}\sum\limits_{j=1}^{\lfloor\lfloor\frac{ i }{k}\rfloor \times x\rfloor}[\gcd(i,j) =1]$$

不难发现，第二个求和等价于 $f_{\lfloor \frac{i}{k} \rfloor}$，则有：

$$f_i=\lfloor i \times x \rfloor-\sum\limits_{k=1}^{i}f_{\lfloor \frac{i}{k} \rfloor}$$

化简得：

$$f_i=\lfloor i \times x \rfloor-\sum\limits_{k|i \land 1<k<i}^{}f_k$$

$cnt=\sum\limits_{i=1}^{n}f_i$。枚举 $i$ 的约数，则能够在 $O(n\sqrt{n})$ 的复杂度求出 $cnt$，然后复杂度就是 $O(n \sqrt{n} \log n)$。

对于求 $p,q$ 的值，暴力枚举即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=4e4+10;
double eps=1e-10;
int n,k,f[N];

il bool check(double x){
	int cnt=0;
	for(re int i=1;i<=n;++i){
		f[i]=i*x;
		for(re int j=2;j*j<=i;++j){
			if(i%j==0){
				f[i]-=f[j];
				if(i/j!=j) f[i]-=f[i/j];
			}
		}
		cnt+=f[i];
	}
	return cnt>=k;
}

il void solve(){
	n=rd,k=rd;
	double l=0.0,r=1.0,ans=0.0;
	while((r-l)>eps){
		double mid=(l+r)/2.0;
		if(check(mid)) ans=mid,r=mid;
		else l=mid;
	}
	int p=0,q=0;
	double c=40001.0;
	for(re int Q=1;Q<=40001;++Q){
		int P=Q*ans;
		if(fabs(double(P*1.0/Q)-ans)<c) c=fabs(double(P*1.0/Q)-ans),p=P,q=Q;
	}
	printf("%lld %lld\n",p,q);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$

要求第 $k$ 小，很显然可以二分答案。



由于 $\forall \frac{j}{i}\leq x, j\leq \lfloor i \times x\rfloor$，我们定义 $cnt_x=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{\lfloor i\times x\rfloor}[\gcd(i,j)=1]$ 表示 Farey 序列中比 $x$ 小的最简真分数的数量。

接下来就是推式子。

令 $f_i=\sum\limits_{j=1}^{\lfloor i\times x\rfloor}[\gcd(i,j)=1],cnt_x=\sum\limits_{i=1}^{n} f_i$。

则：
$$
\begin{aligned}
f_i&=\sum\limits_{j=1}^{\lfloor i\times x\rfloor}[\gcd(i,j)=1]\\
&=\lfloor i\times x\rfloor-\sum\limits_{j=1}^{\lfloor i\times x\rfloor}[gcd(i,j)>1]\\
&=\lfloor i\times x\rfloor-\sum\limits_{k=2}^{i}\sum\limits_{j=1}^{\lfloor i\times x\rfloor}[gcd(i,j)=k]\\
&=\lfloor i\times x\rfloor-\sum\limits_{k=2}^{i}\sum\limits_{j=1}^{\lfloor \lfloor\frac{i}{k}\rfloor\times x\rfloor}[gcd(i,j)=1]\\
&=\lfloor i\times x\rfloor-\sum\limits_{k=2}^{i}f_{\lfloor\frac{i}{k}\rfloor}\\
&=\lfloor i\times x\rfloor-\sum\limits_{k|i\land2\leq k\leq i}f_k
\end{aligned}
$$
使用枚举约束的方式求出 $cnt_x$，通过二分求出 $x$，找到最大的小于 $x$ 的真分数 $\frac{p}{q}$ 即可。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
// #define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=4e4+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double eps=1e-9;
using namespace std;
int n,k,f[N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool check(double x)
{
	int cnt=0;
	rep1(i,1,n)
	{
		f[i]=i*x;
		rep1(j,2,sqrt(i))
		{
			if(i%j==0)
			{
				f[i]-=f[j];
				if(j*j!=i) f[i]-=f[i/j];
			}
		}
		cnt+=f[i];
	}
	if(cnt>=k) return 1;
	return 0;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d%d",&n,&k);
	double l=0,r=1,ans;
	while(r-l>eps)
	{
		double mid=(l+r)/2;
		if(check(mid)) r=mid,ans=mid;
		else l=mid;
	}
	int p=0,q=0;
	double delta=inf;
	rep1(y,1,N-1)
	{
		int x=y*ans;
		double now=fabs(x*1.0/y-ans);
		if(now<delta) delta=now,p=x,q=y;
	}
	printf("%d %d\n",p,q);
	return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution 

很多题解的的推导过程过于简单？

首先不难想到二分出第 $k$ 个值 $x$，只需要判断小于 $x$ 的真分数个数即可。  

定义 $f_i$ 表示以 $i$ 为分母的小于 $x$ 真分数个数。

得到暴力方程：$f_i=\sum_{j=1}^{i \times x} [\gcd(i,j)=1]$。

正难则反：$f_i=i \times x-\sum_{j=1}^{m} [\gcd(i,j)=k(k>1)]$。

套路地把 $k$ 提出来：$f_i=i \times x-\sum_{k=2}^{i \times x} \sum_{j=1}^{\frac{i \times x}{k}} [gcd(i,j)=1]$。

不难发现 ${\sum_{j=1}^{\frac{i \times x}{k}} [gcd(i,j)=1]}=f_{\frac{i}{k}}$。

带入原式得：$f_i=i \times x-\sum_{k=2}^{i \times x} f_{\frac{i}{k}}$。

其实 $\frac{i}{k}$ 就是 $i$ 的因数。

所以 $f_i=i \times x-\sum\limits_{d|i \land d<i} f_d$。

最终小于 $x$ 的真分数个数即为 $cnt=\sum_{i=1}^{n} f_i$，判断 $cnt$ 是否小于 $k$ 即可。

将答案转化为分数只需要枚举分母即可。

时间复杂度为 $O(n \sqrt n \log V )$，$V$ 为精度所需的值域。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=4e4+10; 
const double eps=1e-10;  
int n,k; 
int f[N];  
il bool check(double mid){ 
	int cnt=0; 
	for(int i=1;i<=n;i++){ 
		f[i]=(int)i*mid; 
		for(int j=2;j*j<=i;j++){ 
			if(i%j==0){ 
				f[i]-=f[j]; 
				if(j*j!=i) f[i]-=f[i/j]; 
			} 
		} cnt+=f[i]; 
	} return (cnt<k); 
} 
signed main(){ 
	n=read(),k=read(); 
	double l=0,r=1,ans=0; 
	while(r-l>=eps){ 
		double mid=(l+r)/2; 
		if(check(mid)) l=mid,ans=mid; 
		else r=mid; 
	} for(int i=1;i<=n;i++){ 
		double x=(double)i*ans;  
		int j=ceil(x);  
		if(fabs((double)j/i-ans)<=eps){ 
			printf("%d %d\n",j,i); 
			break; 
		} 
	} return 0; 
} 
```

---

