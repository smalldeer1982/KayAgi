# Divisor Paths

## 题目描述

You are given a positive integer $ D $ . Let's build the following graph from it:

- each vertex is a divisor of $ D $ (not necessarily prime, $ 1 $ and $ D $ itself are also included);
- two vertices $ x $ and $ y $ ( $ x > y $ ) have an undirected edge between them if $ x $ is divisible by $ y $ and $ \frac x y $ is a prime;
- the weight of an edge is the number of divisors of $ x $ that are not divisors of $ y $ .

For example, here is the graph for $ D=12 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1334E/38b890224bb6f89b8928dfc0b449557b94664dd4.png)Edge $ (4,12) $ has weight $ 3 $ because $ 12 $ has divisors $ [1,2,3,4,6,12] $ and $ 4 $ has divisors $ [1,2,4] $ . Thus, there are $ 3 $ divisors of $ 12 $ that are not divisors of $ 4 $ — $ [3,6,12] $ .

There is no edge between $ 3 $ and $ 2 $ because $ 3 $ is not divisible by $ 2 $ . There is no edge between $ 12 $ and $ 3 $ because $ \frac{12}{3}=4 $ is not a prime.

Let the length of the path between some vertices $ v $ and $ u $ in the graph be the total weight of edges on it. For example, path $ [(1, 2), (2, 6), (6, 12), (12, 4), (4, 2), (2, 6)] $ has length $ 1+2+2+3+1+2=11 $ . The empty path has length $ 0 $ .

So the shortest path between two vertices $ v $ and $ u $ is the path that has the minimal possible length.

Two paths $ a $ and $ b $ are different if there is either a different number of edges in them or there is a position $ i $ such that $ a_i $ and $ b_i $ are different edges.

You are given $ q $ queries of the following form:

- $ v $ $ u $ — calculate the number of the shortest paths between vertices $ v $ and $ u $ .

The answer for each query might be large so print it modulo $ 998244353 $ .

## 说明/提示

In the first example:

- The first query is only the empty path — length $ 0 $ ;
- The second query are paths $ [(12, 4), (4, 2), (2, 1)] $ (length $ 3+1+1=5 $ ), $ [(12, 6), (6, 2), (2, 1)] $ (length $ 2+2+1=5 $ ) and $ [(12, 6), (6, 3), (3, 1)] $ (length $ 2+2+1=5 $ ).
- The third query is only the path $ [(3, 1), (1, 2), (2, 4)] $ (length $ 1+1+1=3 $ ).

## 样例 #1

### 输入

```
12
3
4 4
12 1
3 4```

### 输出

```
1
3
1```

## 样例 #2

### 输入

```
1
1
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
288807105787200
4
46 482955026400
12556830686400 897
414 12556830686400
4443186242880 325```

### 输出

```
547558588
277147129
457421435
702277623```

# 题解

## 作者：GavinZheng (赞：9)


我们发现，每次走过一条路径都是减少/增加一个质因子。而且边权是减少/增加一个质因子后减少/增加的因数个数。那么显然有：$x\to y$的最优路径一定是$x\to gcd(x,y)\to y$。因为这样能保证减少/增加的质因子是其他所有方案减少/增加的质因子的子集，那么显然减少/增加的因数个数是最少的。

又因为$x\to gcd(x,y)$的路径上，因数一定是不停减少，不会增加的。而无论删除质因子的顺序如何，减少的因数集合一定是固定不变的。所以删去质因子的顺序可以任意排列。$gcd(x,y)\to y$的路径同理。

那么算法就很显然了。我们先分解$D$，然后将$\frac{x}{gcd(x,y)}$质因数分解。（因为$\frac{x}{gcd(x,y)}$包含的质因子一定是$D$的质因子，所以我们可以直接利用先前分解好的$D$的质因子一个一个尝试即可）我们只需要知道$\frac{x}{gcd(x,y)}$质因数分解出的质因子个数$cnt$即可，这样一次分解利用之前的预处理数据后复杂度是$\log D$。证明显然。

那么$x\to gcd(x,y)$的方案数就是$\frac{cnt!}{\prod _{\text{v is prime }}cnt_v!}$。$gcd(x,y)\to y$的方案数同理。然后乘在一起就好了。

P.S. 有个小问题，就是为什么不走$lcm(x,y)$中转。这里我只会一个感性证明：显然这两种方法，经过的路径条数都是一样的。而走$lcm$的话，路径上所有数都会更大些，增减一个质因子导致的因子的增加减少也会更多些。（纯口胡，不知道对不对）。这个问题我也问过一些大佬，大家的解释大多是“感性证明”，“看起来走$gcd$就是对的”，“你觉得不保险可以都走一遍，大不了常数$\times2$”。如果哪位神仙会严格证明请留言教教我QAQ。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#define vi vector<int>
#define pb push_back
#define mk make_pair
#define pii pair<int,int>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define fi first
#define se second
typedef long long ll;
using namespace std;
const int maxn=3e5+100;
const int mod=998244353;
ll d,q;
ll prime[maxn],prime_cnt,frac[maxn];
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int ksm(ll num,ll t) {
    ll res=1;num%=mod;
    for(;t;t>>=1,num=num*num%mod) {
        if(t&1)res=num*res%mod;
    }
    return res%mod;
}
ll solve(ll u) {
    ll a=1,b=1,tot=0;//分子分母
    rep(i,1,prime_cnt) {
        ll cnt=0;while(u%prime[i]==0)u/=prime[i],cnt++;
        b=b*frac[cnt]%mod;tot+=cnt;
    }
    a=frac[tot];
    return a*ksm(b,mod-2)%mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin>>d>>q;
    frac[0]=frac[1]=1;//预处理阶乘
    rep(i,2,100)frac[i]=frac[i-1]*i%mod;
    ll tmp=d;
    for(ll i=2;i*i<=d;i++) {
        if(tmp%i==0)prime[++prime_cnt]=i;
        while(tmp%i==0)tmp/=i;
    }
    if(tmp>1)prime[++prime_cnt]=tmp;
    rep(i,1,q) {
        ll u,v;cin>>u>>v;ll g=gcd(u,v);
        cout<<solve(u/g)*solve(v/g)%mod<<endl;
    }
    return 0;
}
```




---

## 作者：AutumnKite (赞：7)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

打 CF 只知道猜结论，一个 WA22 以为结论错了，没想到是没开 `long long`。当场去世。

~~好的我们开始猜结论。~~

首先，对于两个点 $x,y\ (x \ge y)$，若 $y|x$，那么 $x$ 到 $y$ 的最短路长度一定是 $d(x)-d(y)$（$d(x)$ 表示 $x$ 的因子数量）。所以，从 $x$ 开始不断除掉某个质因子直到等于 $y$ 的一条路径一定是一条最短路。

如果中途增大了会导致因子数量变多，所以反过来也是成立的。

上面的结论可以更加严谨的证明，这里不做详细证明。

那么最短路条数等于将 $\frac{x}{y}$ 分解质因数后的可重元素排列数量。可以直接预处理阶乘和阶乘逆元求出。

拓展到一般情况，$x$ 到 $y$ 的最短路一定经过点 $\gcd(x,y)$。大概理解一下，一定不会经过比 $\gcd(x,y)$ 更小的公因子，这样显然不优；也一定不会往 $\operatorname{lcm}(x,y)$ 的方向走，由于 $\frac{a}{b}=\frac{b}{c}$ 时，$d(a)-d(b) > d(b)-d(c)$，所以往 $\operatorname{lcm}(x,y)$ 方向走也是不优的。

那么只要分别求出 $x\to \gcd(x,y)$ 和 $y\to \gcd(x,y)$ 的最短路数量，相乘即可。

### 代码

```cpp
const int P = 998244353;

long long n;
int q;
int fac[105], inv[105];
std::vector<std::pair<long long, int>> p;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a % b) : a;
}

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
}

int get(long long x) {
	int res = 1, sum = 0;
	for (auto v : p) {
		int k = 0;
		while (x % v.first == 0) {
			x /= v.first;
			++k;
		}
		res = 1ll * res * inv[k] % P;
		sum += k;
	}
	return 1ll * res * fac[sum] % P;
}

void solve() {
	read(n);
	init(100);
	long long x = n;
	for (int i = 2; 1ll * i * i <= x; ++i) {
		if (x % i == 0) {
			p.push_back({i, 0});
			while (x % i == 0) {
				x /= i;
				++p.back().second;
			}
		}
	}
	if (x > 1) {
		p.push_back({x, 1});
	}
	read(q);
	while (q--) {
		long long x, y;
		read(x), read(y);
		long long g = gcd(x, y);
		print(1ll * get(x / g) * get(y / g) % P);
	}
}
```

---

## 作者：caidzh (赞：2)

首先要明白：这种题没几个大力结论是完全做不动的

所以先给几个结论

$1.$ 若$u|v$，$u$到$v$的最短路长度为两者的因子数量之差

证明：$u$到$v$的每一条边的权的意义是添加的因子数量，结论显然成立

由此可以看出$u$到$v$的最短路可以拆成两个部分，第一个部分是从$u$到$\text{gcd}(u,v)$，第二个部分是$\text{gcd}(u,v)$到$v$

可以发现这两条路径完全不交

根据乘法原理，总的最短路数就是两边的最短路数的乘积

$2.$ 若$u|v$，$u$到$v$经过的边数为两者的质因子数量（一个质因子算多次）之差

因为结论$1$，我们发现$u$到$v$的路径只要满足从小到大走就最优

由于一条边的另一个含义是乘进仅仅一个质因子，所以结论成立

注意到质因子是可以乱序乘进去的，所以答案显然就是可重集排列

然后发现$10^{15}$以内的数的因数数量不会太大，并且因数包含的质因数必定是原数的一个子集

对于每个因数爆算答案即可
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define int LL
#define db double
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int mod=998244353,maxn=10000010;
int n,q;int p[maxn],cnt;
int a[maxn],len,fac[10000],facinv[10000],inv[10000];map<int,int>ans;
int pre(){
	int N=n;
	for(int i=2;i<=sqrt(N);i++){
		if(n%i==0){
			a[++len]=i;
			while(N%i==0)N/=i;
		}
	}if(N!=1)a[++len]=N;
}
int calc(int n){
	int an=1,total=0;
	for(int i=1;i<=len;i++){
		if(n%a[i]==0){
			int tot=0;
			while(n%a[i]==0)tot++,total++,n/=a[i];
			an=1ll*an*facinv[tot]%mod;
		}
	}int tot=0;if(n!=1)total++,tot++;an=1ll*an*facinv[tot]%mod;
	return 1ll*fac[total]*an%mod;
}
void work(int n){
	for(int i=1;i<=sqrt(n);i++)
		if(n%i==0){
			p[++cnt]=i;
			if(i*i!=n)p[++cnt]=n/i;
		}
}
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
signed main()
{
	n=read();pre();work(n);q=read();
	fac[1]=fac[0]=facinv[1]=facinv[0]=inv[1]=1;
	for(int i=2;i<=9999;i++){
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		facinv[i]=1ll*facinv[i-1]*inv[i]%mod;
	}for(int i=1;i<=cnt;i++)ans[p[i]]=calc(p[i]);
	while(q--){
		int x=read(),y=read();int d=gcd(x,y);
		printf("%d\n",1ll*ans[x/d]*ans[y/d]%mod);
	}return 0;
}
```


---

## 作者：ix35 (赞：2)

先证明一个基础结论：如果 $a|b$，那么 $b\to a$ 的最短路一定是不断往小的数走。

证明：这样做的路径长度为 $d(b)-d(a)$（其中 $d(x)$ 为 $x$ 的因数个数）,如果中间某一步变大，不妨设从 $x$ 到了更大的 $y$，那么需要多付出至少 $d(y)-d(x)$ 的代价，一定不优。

根据上面的证明还可以得出推论：如果 $a|b$，那么任何 $b\to a$ 的递减路径（每次往小的数走）都是最短路。

接下来考虑计数，设 $\dfrac{b}{a}=\prod\limits_{i=1}^k p_i^{c_i}$ 是 $\dfrac{b}{a}$ 的素因数分解，根据题中的连边性质，我们每次可以去掉 $b$ 的一个素因子，随后变成 $a$，所以方案数就是去除素因子的排列数量，根据多重排列公式有：

$$Ans=\dfrac{\Big(\sum\limits_{i=1}^k c_i\Big)!}{\prod\limits_{i=1}^k c_i!}$$

接下来再考虑 $a$ 不一定是 $b$ 因数的情况，这也是容易扩展的，显然只要先从 $b$ 走到 $\gcd(a,b)$，再从 $\gcd(a,b)$ 走到 $a$ 即可，这是两个互相独立的步骤，只需分别按照上面的式子算出来再相乘即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll P=998244353,MAXN=1010;
ll d,q,a,b,g,tot,fac[MAXN],inv[MAXN],pri[MAXN];
vector <ll> v;
ll solve (ll x) {
	ll res=1,sum=0;
	for (int i=1;i<=tot;i++) {
		ll cnt=0;
		while (x%pri[i]==0) {cnt++,x/=pri[i];}
		res=(1ll*res*inv[cnt])%P;
		sum+=cnt;
	}
	res=(1ll*res*fac[sum])%P;
	return res;
}
int main () {
	scanf("%lld%lld",&d,&q);
	for (ll i=2;i*i<=d;i++) {
		if (!(d%i)) {
			while (d%i==0) {d/=i;}
			pri[++tot]=i;
		}
	}
	if (d>1) {pri[++tot]=d;}
	fac[0]=inv[0]=1;
	for (int i=1;i<=1000;i++) {
		fac[i]=(1ll*fac[i-1]*i)%P;
	}
	inv[1000]=qpow(fac[1000],P-2);
	for (int i=999;i>=1;i--) {
		inv[i]=(1ll*inv[i+1]*(i+1))%P;
	} 
	for (int i=1;i<=q;i++) {
		scanf("%lld%lld",&a,&b);
		g=gcd(a,b);
		a/=g,b/=g;
		printf("%lld\n",(1ll*solve(a)*solve(b))%P);
	}
	return 0;
}
```


---

## 作者：gyh20 (赞：2)

首先先要明确，这不是图论题，这是数论题。

从大走向小的边其实就是除掉一个质数，所以每次询问 $x,y$ 时直接 $x/\gcd(x,y),y/\gcd(x,y)$。

然后就是求 $x,y$ 的最短路，因为 $x,y$ 互质，所以答案一定为 $x->1->y$，如果是其他方案会多走。

所以说答案就为 $x->1$ 的最短路条数 $\times$ $y->1$ 的最短路条数（双向边）

可以用记忆化搜索解决，预处理出原数的所有质因子，枚举即可。

unordered_map 死了，还是用 map 吧。

这里贴我第一次的代码，看错了 $D$ 的范围，用了 Pollard-rho，但由于该算法极不稳定，又是 Open hacking，就换成了暴力分解，但代码写的很难看（开始打算改造 rho），加了一些奇奇怪怪的东西。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
#define M 998244353
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int d,q,l,r,jc[100002],inv[100002];
inline int gcd(re int x,re int y){
	return y?gcd(y,x%y):x;
}
map<int,int>v;
int random(int n)
{
return (int)((double)rand()/RAND_MAX*n+0.5);
}
int pp[40]= {9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829};
#define ll long long
ll msc(ll x,ll y,ll p) {
	ll z=(long double)x/p*y;
	ll res=(unsigned ll)x*y-(unsigned ll)z*p;
	return (res+p)%p;
}
ll ksm(ll x,ll y,ll z) {
	if(!y)return 1;
	ll tmp=ksm(x,y/2,z);
	if(y&1)return msc(msc(tmp,tmp,z),x,z);
	else return msc(tmp,tmp,z);
}

bool mr(re ll n) {
	if(n==2)return 1;
	if(n<2)return 0;
	re ll m=n-1;
	re int k=0;
	while(m%2==0)k++,m/=2;
	for(re int i=1; i<=5; i++) {
		ll kk=rand()%(n-1)+1,x=ksm(kk,m,n),y=0;
		for(re int j=1; j<=k; j++) {
			y=msc(x,x,n);
			if(y==1&&x!=1&&x!=n-1)return 0;
			x=y;
		}
		if(y!=1)return 0;
	}
	return 1;
}
#define ll long long 
inline int as(re int x){
	return x>0?x:-x;
}
inline ll pr(ll x,ll c) {
	if(!c)c=rand();
	ll s=0,t=0;
	int stp=0,goal=1;
	ll val=1;
	for(goal=1;;goal<<=1,s=t,val=1) {
		for(stp=1; stp<=goal; ++stp) {
			t=(msc(t,t,x)+c)%x;
			val=msc(val,as(t-s),x);
			if((stp%127)==0) {
				ll d=gcd(val,x);
				if(d>1)return d;
			}
		}
		ll d=gcd(val,x);
		if(d>1)return d;
	}
}
int tot,ans[100002];
inline void ff(re int x){
	if(x==1)return;
	if(mr(x)){
		ans[++tot]=x;
		return;
	}
	int p=x,tmp=0;	
	while(p>=x)p=pr(x,pp[tmp++]);
	ff(p);
	ff(x/p);
}
inline int ksm(re int x,re int y){
	re int ans=1;
	while(y){
		if(y&1)ans=1ll*ans*x%M;
		x=1ll*x*x%M;
		y>>=1;
	}
	return ans;
}
inline int calc(re int x){
	if(v.find(x)!=v.end())return v[x];
	if(x==1)return 1;
	re int siz=0;
	for(re int i=1;i<=tot;++i){
		if(x%ans[i]==0)siz+=calc(x/ans[i]),siz%=M;
	}
	return v[x]=siz;
}
signed main(){
	d=read();tot=0;ff(d);
	re int cnt=0;
	for(re int i=1;i<=tot;++i)if(ans[i]!=ans[i-1])ans[++cnt]=ans[i];tot=cnt;
	q=read();
	while(q--){
		re int l=read(),r=read(),x=gcd(l,r);
		l/=x;r/=x;
		printf("%lld\n",calc(l)*calc(r)%M);
	}
}
```


---

## 作者：Judgelight (赞：1)

# Divisor Paths

## 题面翻译

有一个无向带权图，所有的点为 $D$ 的约数，$x,y$ 连边当且仅当存在质数 $p$ 使得 $x\cdot p = y$，边权为 $d(y) - d(x)$，其中 $d$ 为约数个数函数。

$q$ 个询问 $u,v$ 之间的最短路径条数。

$D \le 10^{15}, q \le 3\times 10^5$

# 题解

## 1. 分析题面

显然，如果一个点 $s$ 总是往比它小的点走，设终点为 $t$，则距离为 $d(s)-d(t)$。

证明如下:

> 令 $s$ 到 $t$ 经过的点为 $a_1,a_2,a_3,\ldots,a_n$，其中 $a_1 = s$，$a_n = t$，则 
> $$dis = \sum \limits_{i=2} \limits^{n} d(a_{i-1}) - d(a_i) = d(a_1)  - d(a_2) + d(a_2) - d(a_3) + \ldots + d(a_{n-1}) - d(a_n) = d(a_1) - d(a_n) = d(s) - d(t)$$

所以现在我们就有了一个很现实的做法：设要求点 $u$ 到点 $v$ 的距离，要么从 $u$ 到 $\operatorname{gcd(u,v})$ 到 $v$，要么从 $u$ 到         $\operatorname{lcm(u,v)}$，这一定是最短的，因为没有弯弯绕绕，且多余的路一概不走。

## 2. 证明正确

同班巨佬会证，我菜，不会。

反正结论就是选择 $\operatorname{gcd}$ 比选择 $\operatorname{lcm}$ 更优，感性理解走 $\operatorname{gcd}$ 是只有 $u$ 和 $v$ 中不同次数的因子会被算进答案，而 $\operatorname{lcm}$ 是有对面的被算进来了。

## 3. 解法归纳

现在可以有一个清晰的做法了：对于每一对 $u$ 和 $v$，
$$ans = \operatorname{calc}(\frac{u}{ \operatorname{gcd}(u,v)}) \times \operatorname{calc}(\frac{v}{ \operatorname{gcd}(u,v)})$$

其中 $\operatorname{calc(n)}$ 表示求路径条数。

求 $\operatorname{calc(n)}$ 可以先求出 $n$ 的所有质因子的个数，然后其实每一条路径都可以看作是一种对每个质因子的排列，问题便转化为了求一个多重集的排列个数。

设 $all$ 表示当前数 $n$ 的不同质因子**种数**，$cnt_i$ 表示 $n$ 所含有的第 $i$ 种质因子的个数，$sum = \sum \limits_{i=1} \limits^{all}cnt_i$ 则有：

$$\operatorname{calc}(n) = \frac{sum!}{\prod \limits_{i=1} \limits^{all} cnt_i!}$$

所以就用各种数学板子做就可以了。

## 4. AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300009
using namespace std;
const int mod=998244353;
int n,m,primes[N],sum[N],cnt,fact[N],infact[N];
pair<int,int>exgcd(int a,int b){
	if(b==0){
		return make_pair(1,0);
	}
	pair<int,int>now=exgcd(b,a%b);
	int x=now.second,y=now.first;
	return make_pair(x,y-a/b*x);
}
void init(int n){
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			primes[++cnt]=i;
			while(n%i==0){
				n/=i;
				sum[cnt]++;
			}
		}
	}
	if(n>1){
		primes[++cnt]=n;
		sum[cnt]=1;
	}
	fact[0]=infact[0]=1;
	for(int i=1;i<=114514;i++){
		fact[i]=fact[i-1]*i%mod;
		infact[i]=exgcd(fact[i],mod).first%mod;
	}
}
int calc(int n){
	int ans=1,now=0;
	for(int i=1;primes[i]*primes[i]<=n&&i<=cnt;i++){
		int x=primes[i],sm=0;
		if(n%x==0){
			while(n%x==0){
				n/=x;
				sm++;
			}
			now+=sm;
			ans*=infact[sm];
			ans%=mod;
		}
	}
	if(n>1){
		now++;
	}
	ans*=fact[now];
	ans%=mod;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	init(n);
	cin>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(x==y){
			cout<<1<<endl;
			continue;
		}
		int g=__gcd(x,y);
		cout<<(calc(x/g)*calc(y/g)%mod+mod)%mod<<endl;
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：1)

## 题解思路：
我们看看他有什么性质：
>若我们去掉一个数的质因子，那么他就会向下走一格。

>还有一个，我们看一下样例：$12$ 到 $2$ 那么我们先去掉一个质因子 $3$，再去掉一个质因子 $2$，或先取掉质因子 $2$，再去掉一个质因子 $3$，那么他们的路径权值是一样的。证明：
>>假设 $u$ 能走向 $v$，并 $u > v$，因为若从 $u$ 走向 $v$，那么把他质因子分解，既然 $u$ 能走向 $v$，那么 $v$ 一定是 $u$ 的某个因子的因子。所以 $v$ 一定是 $u$ 的因子，因为 $u$ 是在不断去掉质因子才达到 $v$ 的。

>>我们先把 $u$ 质因子分解：$u = p_1^{a_1} p_2^{a_2} p_3^{a_3} ...\ p_m^{a_m}$，那么你走下去，那么你会去掉一些质因子，就是 $a_1-x_1,a_2-x_2 ...\ a_m-x_m$，有的可能是去掉了零个，那么他的因子数为 $(a_1+1)(a_2+1)...(a_m+1)$，所以 $u$ 的因子数为 $(a_1+1)(a_2+1)...(a_m+1)$，而 $v$ 的因子数为 $(a_1-x_1+1)(a_1-x_2+1)...(a_m-x_m+1)$，那么我们把 $u$ 设为 $x$，那么假设我们先去掉 $p_i$ 的一个因子，就相当去掉一个 $\frac{\mathrm{x}}{\mathrm{a_i}}$，下一个我们去掉一个 $p_k$ 就相当于去掉： $\frac{\mathrm{xa_i}}{\mathrm{(a_i+1)(a_j + 1)}}+\frac{\mathrm{x}}{\mathrm{a_i+1}}$，想乘得 $\frac{\mathrm{a_i+a_j+1}}{\mathrm{(a_i+1)(a_j+1)}}x$，那么 $a_i$ 和 $a_j$ 交换了位置，那么其实不变，在推广到普通情况，也是相同的，证毕。

那么我们从 $x$ 走到 $y$，假设 $x>y$，那么 $x$ 每次去掉质因子，直到 $1$ 那么我们到一个点，比如 $y$ 这个点，那么他这个的最短路就是 $x$ 去因子的这条路，不然的话，你就没有这个更短。

然后若 $y$ 不是 $x$ 的因子，那么我们要选 $\gcd(x,y)$，这样才是最短路。若不选最大公因数的话，那么就会取掉多余的质因子，就不优了。

那么我们怎么算呢，因为他的质因子为 $p_1^{a_1} p_2^{a_2} p_3^{a_3} ...\ p_m^{a_m}$，走到他们的 $\gcd$ 就是：$p_1^{a'_1} p_2^{a'_2} p_3^{a'_3} ...\ p_m^{a'_m}$ 这就是他的过程，那么我们要把某个因子，要去掉一些因子，那么我们可以把他们换一下顺序，这个东西就是多次向系数。

那么我们求一下他们的全排列，但有重复的情况，比如全是相同的数，所以他的全排列有很多种，但都是一样的。

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll D , fac[60] , inv[60];
vector <pair <ll , int>> p;
map <ll , vector<int>>mp;//就相当于质因数分解的系数
vector <int> now;
ll gcd (ll a , ll b) {return b == 0 ? a : gcd (b , a % b);}//求最大公因数
ll power (ll a , ll b) {//快速幂，用来求逆元。
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
void dfs (int dep , ll sum) {//暴力构造O(sqrt(n))
	if (dep == p.size()) {
		mp[sum] = now;//取出来，放到一个map里
		return;
	}
	auto x = p[dep];
	now.push_back (0);
	dfs (dep + 1 , sum);
	now.pop_back();
	for (int i = 1; i <= x.second; ++ i) {
		sum *= x.first;
		now.push_back (i);
		dfs (dep + 1 , sum);
		now.pop_back ();
	}
}
void init () {//预处理函数
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= 59; ++ i)
		fac[i] = fac[i - 1] * i % mod;//预处理阶乘
	for (int i = 1; i <= 59; ++ i)
		inv[i] = power (fac[i] , mod - 2);//逆元因为mod是质数，所以可以预处理
	ll d = D;
	for (ll i = 2; i <= d / i; ++ i) {//分解质因数.
		if (d % i == 0) {
			int cnt = 0;
			while (d % i == 0) {
				d /= i;
				++ cnt;
			}
			p.push_back ({i , cnt});
		}
	}
	if (d > 1) p.push_back ({d , 1});
	dfs (0 , 1);//构造
}
int main() {
	cin >> D;
	init();//预处理
	int q;
	cin >> q;
	while (q --){
		ll u , v;
		cin >> u >> v;
		ll x = gcd (u , v);
		vector <int> a , b , c;//把每个数的系数取出来
		a = mp[u] , b = mp[v] , c = mp[x];
		for (int i = 0; i < a.size(); ++ i) {//做差，得出来的数就是答案的系数
			a[i] -= c[i];
			b[i] -= c[i];
		}
		ll sum = 0 , sum2 = 0 , ans = 1 , ans2 = 1;
		for (auto x : a) {//计算
			if (!x) continue;
			sum += x;
			ans = ans * inv[x] % mod;
		}
		ans = ans * fac[sum] % mod;
		for (auto x : b) {//计算
			if (!x) continue;
			sum2 += x;
			ans2 = ans2 * inv[x] % mod;
		}
		ans2 = ans2 * fac[sum2] % mod;
		ans = ans * ans2 % mod;//最后相乘。
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：_Diu_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1334E)

我们可以发现，每一次走一条边得到的数是增加或减少一个质因子，

因此，要使路径最短，我们会发现有两种情况可能入选：

1. $u->\gcd(u,v)->v$，权值之和为 $d(u)+d(v)-2d(\gcd(u,v)$

2. $u->lcm(u,v)->v$，权值之和为 $2d(lcm(u,v))-d(u)-d(v)$

这里如何证明不多赘述，很好理解，别的题解也有讲。

然后，我们发现，我们只需要统计**第一种的情况**即可，因为第一种情况是不劣于第二种情况的。

这里大部分题解没有给出严谨证明，这里给出一个**较为严谨**的证明，如有误还请指出。

---

- 定理 1.0 若 $x=\sum p_i^{e_i}$，则 $d(x)=\prod (e_i+1)$。

（本文中所有 $p_i\in prime$）

这是约数个数常见结论，就不赘述了。

这里假设 $u\le v$。

接下来得证明分两种情况讨论。

1. 当 $u\mid v$ 时，

显然，两种情况最后都会变成从 $u$ 直接到 $v$，如果两种都统计就重复了。

2. 当 $u\nmid v$ 时，

我们假设 $u=\prod_{i=1}^np_i^{e1_i}$，$v=\prod_{i=1}^np_i^{e2_i}$。

那么肯定存在至少一个 $k$ 使得 $e1_k>e2_k$，

而且至少存在至少一个 $k$ 使得 $e1_k<e2_k$。

为了方便，我们设 $g=\gcd(u,v),l=lcm(u,v)$。

那么有 $g=\prod_{i=1}^np_i^{\min(e1_i,e2_i)},l=\prod_{i=1}^np_i^{\max(e1_i,e2_i)}$。

我们考虑作差法来证明，

我们可以将 $e1_k=e2_k$ 的情况，两边同时除以 $(e1_k+1)$,不影响判断结果。

将剩下的 $p$ 拍一下序，存在一个 $t$ 使得 $i\in [1,t]\ e1_i<e2_i,i\in [t+1,n]\ e1_i>e2_i$。

我们再设 $a1=\prod_{i=1}^t(e1_i+1),a2=\prod_{i=t+1}^n(e2_i+1),b1=\prod_{i=1}^t(e2_i+1),b2=\prod_{i=t+1}^n(e1_i+1)$，

那么显然 $a1<b1,a2<b2$。

$k1=b1-a1,k2=b2-a2$。

那么 $d(u)=a1b2,d(v)=b1a2,d(g)=a1a2,d(l)=b1b2$。

$\Delta d=2d(l)-2d(u)-2d(v)+2d(g)$

$=2b1b2-2a1b2-2b1a2+2a1a2$

全部除以 $2$ 不影响最后结果。

$\Delta d'=b1b2-a1b1-b1a2+a1a2$

接下来后面就简单了。

$=(a_1+k_1)(a_2+k_2)-a_1(a_2+k_2)-a_2(a_1+k_1)+a_1a_2$

拆括号化简后得：

$\Delta d'=k1k2$。

又因为 $k1>0,k2>0$。

所以 $\Delta d'>0$。

所以 $\Delta d>0$。

从而证明出来当 $u\nmid v$ 时，情况一一定**优于**情况二。

所以，我们只需要统计情况二的方案数就好了。

---

接下来的事情就比较简单了。

考虑 $u->g$ 的过程。

发现每次要减少 $u/g$ 的一个质因子。

假设 $u/g=\prod_{i=1}^{n'}{p'}_i^{{e'}_i},E=\sum{{e'}_i}$。

那么根据去重排列方案数得到答案为：$\frac{E!}{\prod_{i=1}^{n'}{e'}_i!}$。

$g->v$ 的过程同理。

## code

上代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,p=998244353;
int D,q,x,y,a[N],tot,pri[N],tot2,fac[N],ifac[N];
int qpow(int x,int y=p-2){
	int m=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)m=m*x%p;
	return m;
}
int solve(int x){
    int a=1,b=0;
    for(int i=1;i<=tot2&&x!=1;i++){
        int cnt=0;
		while(x%pri[i]==0)x/=pri[i],cnt++;
        a=a*ifac[cnt]%p,b+=cnt;
    }
    return a*fac[b]%p;
}
bool check(int x){
	if(x==2)return 1;
	if(x==1)return 0;
	if(x%2==0)return 0;
	for(int i=3;i*i<=x;i++)if(x%i==0)return 0;
	return 1;
}
signed main(){
	fac[0]=ifac[0]=1;
	for(int i=1;i<1000;i++)fac[i]=fac[i-1]*i%p,ifac[i]=qpow(fac[i]);
	scanf("%lld%lld",&D,&q);
	for(int i=1;i*i<=D;i++){
		if(D%i==0){
			a[++tot]=i;
			if(i*i!=D)a[++tot]=D/i;
		}
	}
	sort(a+1,a+tot+1);
	for(int i=1;i<=tot;i++)if(check(a[i]))pri[++tot2]=a[i];
	for(;q--;){
		scanf("%lld%lld",&x,&y);
		int d=__gcd(x,y);
		printf("%lld\n",solve(x/d)*solve(y/d)%p);
//		printf("%lld %lld %lld\n",solve(x),solve(y),solve(__gcd(x,y)));
	}
}
```

---

## 作者：tommymio (赞：1)

性质题好评。我们需要大力猜结论才能做这题。

通过手玩样例可以发现：当 $y|x$ 时，从 $y\to x$ 或从 $x\to y$ 的最短路径的值为 $d(x)-d(y)$。这很好理解，从 $x\to y$ 的过程中经过的边权会互相抵消（有点像差分的前缀）得到 $d(x)-d(y)$，并且这条路径是最短的，因为它每次去掉一个 $x$ 的质因子。如果不这么走，会多加上一些质因子，再减去一些质因子的贡献，答案只会更劣。

有了这个结论，我们可以大胆猜测，从 $x\to y$ 的最短路径一定由两部分组成 $x\to \gcd(x,y)$，$\gcd(x,y)\to y$。因为这两部分增加/减少的质因子不存在交集。感性理解一下就是，如果不这么走一定会加上一些相同的质因子，然后再减去一些相同的质因子，这样会使答案更劣，所以这样一定是最优的。

由于对于 $10^{15}$ 内的 $n$，$\max\{d(n)\}=26880$，所以可以先求出 $n$ 的因数，然后对于每个因数预处理。

这里贴上一张 $\text{NOIer}$ 必备的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2cjzkhon.png)

代码随手写的，看看就好（~~我是不是低质量代码批量生成器啊~~

**Show the Code**
```cpp
#include<cstdio>
#include<algorithm>
#define int ll
typedef long long ll;
const ll mod=998244353;
int num,fac[105],inv[105],p[105],t[105],ft[100005],f[100005];
inline ll read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline ll gcd(ll x,ll y) {return y? gcd(y,x%y):x;}
inline int pow(int x,ll p) {int res=1;for(;p;p>>=1) {if(p&1) res=(ll)res*x%mod; x=(ll)x*x%mod;} return res;}
inline ll calc(ll n) {
	ll res=1; int sum=0; num=0;
	for(register int i=2;(ll)i*(ll)i<=n;++i) {
		if(n%i==0) {
			p[++num]=i; t[num]=0;
			while(n%i==0) {++t[num];n/=i;}
			sum+=t[num];
		}
	}
	if(n>1) {p[++num]=n;t[num]=1;++sum;}
	res=fac[sum];
	for(register int i=1;i<=num;++i) res=res*(ll)inv[t[i]]%mod;
	return res;

}
signed main() {
	ll n=read(); int T=read(),cnt=0; inv[0]=fac[0]=1;
	for(register int i=1;i<=64;++i) fac[i]=fac[i-1]*(ll)i%mod;
	for(register int i=1;i<=64;++i) inv[i]=pow(fac[i],mod-2);
	for(register int i=1;(ll)i*(ll)i<=n;++i) {
		if(n%i) continue; 
		ft[++cnt]=i; 
		if((ll)i*(ll)i!=n) {ft[++cnt]=n/i;}
	}
	std::sort(ft+1,ft+1+cnt);
	for(register int i=1;i<=cnt;++i) f[i]=calc(ft[i]);
	while(T--) {
		ll x=read(),y=read(),g=gcd(x,y),ans=0;
		int posx=std::lower_bound(ft+1,ft+1+cnt,x/g)-ft;
		int posy=std::lower_bound(ft+1,ft+1+cnt,y/g)-ft;
		ans=f[posx]*f[posy]%mod; printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：SmileMask (赞：0)

首先有最基本的观察：

- 若 $u,v$ 满足 $u\mid v$，则 $u\rightarrow v$ 的代价是 $d(v)-d(u)$。

所以如果 $u\mid v$ 答案即为 $d(v)-d(u)$，下面讨论的皆为 $u\nmid v$ 的情况。

首先若加质数表示右上减质数表示右下的话，则该路径一定是单谷/单峰的，即 $u\rightarrow v$，可将路径分解成 $u\rightarrow \gcd(u,v)\rightarrow v$，或者 $u\rightarrow \operatorname{lcm} (u,v) \rightarrow v$。

考虑哪条路径更优，不妨记 $u=\prod\limits_{i=1}^kp_i^{x_i},v=\prod\limits_{i=1}^k p_i^{y_i}$，为了方便这里 $x_i\leftarrow x_i+1,y_i\leftarrow y_i+1$。

不妨钦定走 $\operatorname{lcm}$ 更优，即 $2d(\operatorname{lcm})-d(u)-d(v)<d(u)+d(v)-2d(\gcd)$，化简得 $d(\operatorname{lcm})+d(\gcd)<d(u)+d(v)$，即 $\prod x_i+\prod y_i<\prod max(x_i,y_i)+\prod min(x_i,y_i)$，有结论乘积一定差大和大，所以该不等式不成立，矛盾。

因此只要考虑 $u\rightarrow \gcd(u,v)\rightarrow v$ 路径即可，因为 $u\rightarrow \gcd$ 与 $\gcd \rightarrow v$ 无交，所以分别求出路径方案数相乘即可。

记 $\frac{u}{\gcd(u,v)}=\prod p_i^{x_i}$，路径数即为多重集的排列，答案为 $\frac{(\sum x_i)!}{\prod x_i!}$

---

