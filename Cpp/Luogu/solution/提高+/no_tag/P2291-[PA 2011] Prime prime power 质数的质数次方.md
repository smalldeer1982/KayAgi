# [PA 2011] Prime prime power 质数的质数次方

## 题目描述

对于给定的数 $n$，求第 $k$ 小的 $a^b$（$a,b$ 都为质数），使得它的值大于 $n$。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^{18}$，$1\le k\le 10^5$。

## 样例 #1

### 输入

```
22 2```

### 输出

```
27```

## 样例 #2

### 输入

```
22 1```

### 输出

```
25```

# 题解

## 作者：tommymio (赞：6)

求第 $k$ 小的 $a^b>n$，$a,b\in Prime$。

这种东西一看就不是很好做，但是我们考虑 $2^{67}$ 远远大于 $10^{18}$，所以可以确认 $b$ 最大不会超过 $67$，且 $b$ 是质数，那么 $b\in\{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61\}$。

幂次这么少，是不是直接枚举就可以呢？但我们发现 $b=2$ 时比较特殊，$a\leq 10^9$，而 $b\geq 3$ 时 $a\leq 10^6$，对于 $a\leq 10^9$ 这个范围我们是不能承受的。所以考虑根据 $n$ 的范围得出 $b=2$ 时的一个紧确上下界。由 $n>a^2$ 得到 $\sqrt n> a$，并且根据 $k\leq 100000$，我们大概推算出 $a\in(\sqrt n,\sqrt n+3\times 10^6]\bigcap \mathrm{Prime}$。这样我们筛出 $a\in(\sqrt n,\sqrt n+3\times 10^6]$ 内的质数，并统计贡献就解决了 $b=2$ 时的情况。

对于 $b\geq 3$ 的情况，设每个 $b$ 对应的 $a$ 的上界都为 $10^6$，则最多枚举了 $\frac{10^6}{\ln 10^6}\times 17\approx 1214185$ 个数。事实上远远达不到该上界，因为 $a^b$ 会快速增长直到远远大于 $10^{18}$。

在实际情况下，我们会发现上述理论估算存在误差，对于 $b\geq 3$ 的情况 $a$ 的上界大概在 $2\times 10^6$ 处才能取到所有答案，需要微调。

本代码可以通过 $\text{darkbzoj}$ 所有数据，$\text{Luogu}$ 数据太水了/fad

```cpp
#include<cstdio>
#include<cmath>
#include<climits>
#include<algorithm>
//18*78498=1412964
typedef unsigned long long ll;
int num=0,tot=0;
const int sp[]={3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61};
int p[4000005],v[4000005];
ll n,ans[10000005];
inline ll read() {
	ll x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void write(ll x) {
	if(x==0) {return;}
	write(x/10);
	putchar((char)('0'+x%10));
}
inline ll pow(ll x,ll p) {ll res=1;for(;p;p>>=1) {if(p&1) res=res*x; x=x*x;} return res;}
inline void makePrime(int n) {
	for(register int i=2;i<=n;++i) {
		if(!v[i]) p[++num]=i;
		for(register int j=1;j<=num&&i*(ll)p[j]<=n;++j) {
			v[i*p[j]]=1;
			if(i%p[j]==0) break;
		}	
	}
} 
inline void makePrime(int l,int r) {
	for(register int i=0;i<=r-l;++i) v[i]=0;
	if(l==1) v[0]=1;
	for(register int i=1;i<=num;++i) {
		int x=p[i];
		for(register int j=r/x*x;j>=l&&j>x;j-=x) {v[j-l]=1;}
	}
	for(register int i=l;i<=r;++i) {
		if(!v[i-l]&&i*(ll)i!=n) ans[++tot]=i*(ll)i;
	}
}
inline void divide(ll n) {
	for(ll i=2;i<=n;++i) {
		if(n%i) continue;
		int cnt=0;
		while(n%i==0) {n/=i; ++cnt;}
		printf("%lld %d\n",i,cnt);
	}
}
signed main() {
	n=read(); int k=read();
	makePrime(4e6);
	makePrime((int)ceil(sqrt(n)),(int)ceil(sqrt(n))+(int)3e6);
	for(register int i=1;i<=num&&p[i]<=2e6;++i) {
		for(register int j=0;j<17;++j) {
			ll tmp=0;
			if((sp[j]*log(p[i]))>=log((double)ULLONG_MAX)) break;
			if((tmp=pow((ll)p[i],(ll)sp[j]))>n) ans[++tot]=tmp;
		}
	}
	std::sort(ans+1,ans+1+tot);
	printf("%llu\n",ans[k]);
	return 0;
}
```

---

## 作者：Prean (赞：1)

。。。去 darkbzoj 上面评测，评测机老是抽风给我 TLE。。。

好在如果寄了会读取上一次的结果，但是如果有人又交了一发就全部木大了/fn

~~尝试用一个极其奇怪的算法草过去~~

首先知道答案是 $p^q$ 的形式，我们枚举这个 $q$。当 $q=2$ 时一定能在 ll 范围内搜出解，所以可以知道 $q\leq 64$，而且当 $q$ 过大时可选的值也很少。

考虑 $q=2$，是最麻烦的一部分。考虑在 $\sqrt{n}$ 附近确定一段区间，这段区间中有恰好 $k$ 个质数。

我们知道素数密度是 $O(\ln n)$，所以这个区间的长度一定是 $O(k\ln n)$ 级别的。长度可以用 min25 筛+二分找出来。大概在 2e6 级别。

现在的问题就是求出一个 2e6 的区间中有哪些数是质数。区间筛直接莽即可。

$q=3$ 时，值域缩小到了 $10^6$，可以直接暴力筛出 $2\times 10^6$ 中的素数然后暴力判断。

复杂度？$18$ 以内除去 $2,3$ 只有 $5$ 个素数，实际上当 $q=5$ 时，时间的影响就已经远不如 $q=2$ 了。

复杂度是 $O(k\log n\log\log n+\sqrt[4]{n}+\sqrt[3]{n})$。

最后我们会得到 $O(k)$ 个数，要在这里面寻找第 $k$ 大的数很容易。

看上去很怪？实际上应该是比较稳的。

如果还觉得不稳的话，可以将 $q\geq 5$ 时的数打表出来。

fun fact：$q=2$ 时需要最多需要做 $[10^9,1002075103]$，而 $1002075101$ 和 $1002075103$ 恰好是一对孪生素数。

~~别问怎么找出来的，对着 LOJ6235 代码手动二分的~~

打表代码：
```cpp
#include<algorithm>
#include<cstdio>
typedef __int128 LL;
typedef long long ll;
int top,pri[10005],pos[10005];ll len,p[1000005];
inline LL pow(int a,int b){
	LL ans(1);while(b--)ans*=a;return ans;
}
signed main(){
	freopen("ans.out","w",stdout);
	pos[1]=114514;
	for(int i=2;i<=10000;++i){
		if(!pos[i])pri[pos[i]=++top]=i;
		for(int x,j=1;j<=pos[i]&&(x=i*pri[j])<=10000;++j)pos[x]=j;
	}
	for(int i=1;i<=top;++i)pos[pri[i]]=0;
	for(int i=5;i<64;++i)if(!pos[i]){
		int lim=1;while(pow(lim,i)<=1002075103ll*1002075103ll)++lim;--lim;
//		printf("{%d,%d}\n",i,lim);
		for(int j=1;j<=lim;++j)if(!pos[j])p[++len]=pow(j,i);
	}
	std::sort(p+1,p+len+1);
	printf("%d\n",len);
	for(int i=1;i<=len;++i)printf("%lld,",p[i]);
}
```
代码（表太长了）：
```cpp
#include<cstdio>
typedef unsigned ui;
typedef unsigned long long ull;
const ull p3[669]={};
const ui M=2157415+5,N=2100000;//1002075103
ui top,pri[M],pos[M];bool zhi[N+5];
ull n;ui k;ull p1[M],p2[M];
inline void sieve(const ui&M){
	pos[1]=114514;
	for(ui i=2;i<=M;++i){
		if(!pos[i])pri[pos[i]=++top]=i;
		for(ui x,j=1;j<=pos[i]&&(x=i*pri[j])<=M;++j)pos[x]=j;
	}
	for(int i=1;i<=top;++i)pos[pri[i]]=0;
}
inline ui Sieve(const ui&L,const ui&R){
	ui len(0);if(L==1)zhi[0]=true;
	for(ui i=1;pri[i]*pri[i]<=R;++i){
		const ui&s=(L-1)/pri[i]+1,&t=R/pri[i];
		for(ui j=s;j<=t;++j)zhi[j*pri[i]-L]=true;
	}
	for(ui i=0;i<=R-L+1;++i){
		if(!zhi[i]||(L+i<=2000000&&!pos[L+i]))p1[++len]=1ll*(L+i)*(L+i);if(len==k)return len;
	}
	return len;
}
inline ui sqr(ull n){
	ui L(1),R(1000000000),mid,ans(1);
	while(L<=R)mid=L+R>>1,1ll*mid*mid<=n?ans=mid,L=mid+1:R=mid-1;
	return 1ll*ans*ans==n?ans:ans+1;
}
signed main(){
	ui l1(0),l2(0),l3(0),t1(1),t2(1),t3(1);scanf("%llu%u",&n,&k);++n;
	sieve(2157415);l1=Sieve(sqr(n),sqr(n)+21*(k>=10?k:10));l3=668;
	for(int i=1;i<=top;++i)if(1ull*pri[i]*pri[i]*pri[i]>=n&&l2<k&&1ull*pri[i]*pri[i]*pri[i]<=p1[l1])p2[++l2]=1ull*pri[i]*pri[i]*pri[i];
	while(t3!=l3+1&&p3[t3]<n)++t3;
	for(ui i=1;i<=k;++i){
		ui id(0);ull V(0);
		if(!id||(t1!=l1+1&&p1[t1]<V))id=1,V=p1[t1];
		if(!id||(t2!=l2+1&&p2[t2]<V))id=2,V=p2[t2];
		if(!id||(t3!=l3+1&&p3[t3]<V))id=3,V=p3[t3];
		if(i==k)return printf("%llu",V),0;if(id==1)++t1;if(id==2)++t2;if(id==3)++t3;
	}
}
```

---

## 作者：NoirCube1 (赞：0)

观察：${b\leq 61}$。

鉴于 $b$ 很少，所以也许我们可以枚举所有的 $(a,b)$。

对于 $b\ge 3$，我们可以直接暴力，但是唯一的问题就是 $b=2$ 的时候 $a\leq 10^9$。

发现尽管 $n$ 大得恐怖，但是 $k\leq 10^5$。在此基础上，只有很少一部分平方数会影响答案，于是我们暴力枚举 $10^4$ 个平方数，检验它们是不是质数的平方就行了。

因为你可能要把所有 $b \ge 3$ 的合法数放进一个 `set` 当中，所以会导致复杂度多一个 $\log n$。

```cpp
#define int long long
signed main() {
	int n, k;
	cin >> n >> k;
	int bnd = ceil(sqrt(n));
	init(6e6);
	for (int i = 1; i <= tot; i++) {
		int now = 1;
		for (int j = 1; ; j++) {
			now *= primes[i];
			if (p[j] == 0 && now > n) s.insert(now);
			if (primes[i] > 1e18 / now) break;
		}
	}
	for (int i = 1; i <= 10000; i++) {
		if (bnd + i - 1 > 1e9) break;
		if (pr(bnd + i - 1)) s.insert((bnd + i - 1) * (bnd + i - 1));
	}
	for (int i = 1; i < k; i++) s.erase(s.begin());
	cout << *s.begin() << endl;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到本题用到了常用的一个套路：对 $b$ 是否大于 $2$ 分类讨论。

因为 $b>2$ 也就是 $b\ge3$ 时 $a\le10^6$，所以考虑把 $3\times10^6$（因为有 $k$ 的存在）前的质数筛出来，暴力找到 $a^b$ 加入统计答案的 set（$2^{60}>10^{18}$，因此 $b\le59$）。

接下来考虑 $b=2$ 的时候，由于 $a^2$ 增长迅速，所以不需要枚举很多的 $a$。从 $\lceil\sqrt{n}\rceil$ 开始枚举约 $1000$ 个数的时候就可以了。

最后先把 set 中小于等于 $n$ 的数 erase 掉，然后再 erase 掉前 $k-1$ 个元素，再输出 set 中头元素的值就可以了。注意经常判断一下当前的数是否超过 $10^{18}$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
set<int> st;
bool isp[5000010];
int pri[5000010],cnt=0;
void init(int n)
{
	memset(isp,1,sizeof isp);
	isp[0]=isp[1]=0;
	for(int i=2;i<=n;i++)
	{
		if(!isp[i]) continue;
		pri[++cnt]=i;
		for(int j=i*i;j<=n;j+=i) isp[j]=0;
	}
}
int ispr(int k)
{
	for(int i=2;i*i<=k;i++) if(k%i==0) return 0;
	return 1;
}
signed main()
{
	int n,k;
	cin>>n>>k;
	init(3e6);
	for(int i=1;i<=cnt;i++)
	{
		int b=pri[i],p=1;
		for(int j=1;j<=cnt;j++)
		{
			while(p<pri[j])
			{
				p++;
				b*=pri[i];
				if(b>1e18) goto t;
			}
			st.insert(b);
		}
		t:;
	}
	int tp=ceil(sqrt(n));
	for(int i=1;i<=1000;i++)
	{
		if(tp*tp>1e18) break;
		if(ispr(tp)) st.insert(tp*tp);
		tp++;
	}
	while(*(st.begin())<=n) st.erase(st.begin());
	for(int i=1;i<k;i++) st.erase(st.begin());
	cout<<*(st.begin());
	return 0;
}

---

## 作者：happybob (赞：0)

我们注意到 $(10^6)^3 = 10^{18}$，也就是说，对于 $b=3$ 时，$a \leq 10^6$。于是可以线性筛预处理 $1 \sim 10^6$ 的质数并且把每个质数的三次方加进去。

考虑对于小的 $a$，例如 $a=2$ 时，$b$ 可以取到 $60$ 左右。于是对于小的质数可以直接枚举所有次方并计算，显然复杂度也很对。

对于 $b=2$，$a \leq 10^9$，难以计算。我们考虑枚举 $n$ 以上的完全平方数并判断其根号是否是质数。直接算 $k$ 个复杂度会炸，可以考虑 Miller-Rabbin，但感性理解发现很多都是偏大的而被忽略，所以大约只需要算 $5000$ 次即可。

启示：对于很难处理的问题，考虑一些值的范围。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

const int N = 6e6 + 5;

int prime[N], cnt;
bool vis[N];

void Init()
{
	for (int i = 2; i < N; i++)
	{
		if (!vis[i])
		{
			prime[++cnt] = i;
		}
		for (int j = 1; j <= cnt && 1LL * i * prime[j] < N; j++)
		{
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

long long n;
int k;

bool isprime(long long x)
{
	if (x == 1) return 0;
	for (long long i = 2; i * i <= x; i++)
	{
		if (x % i == 0) return 0;
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	set<long long> v;
	cin >> n >> k;
	Init();
	for (int i = 1; i <= cnt; i++)
	{
		long long g = prime[i];
		int nowp = 1;
		for (int j = 1; j <= cnt; j++)
		{
			while (nowp < prime[j])
			{
				nowp++;
				g *= prime[i];
				if (g > (long long)1e18) goto E;
			}
			v.insert(g);
		}
	E:;
	}
	long long p = (long long)ceil(sqrt(n));
	for (int i = 1; i <= 5000; i++)
	{
		if (p * p > (long long)1e18) break;
		if (isprime(p))
		{
			v.insert(p * p);
		}
		p++;
	}
	while (*v.begin() <= n) v.erase(v.begin());
	auto it = v.begin();
	for (int i = 1; i <= k; i++)
	{
		++it;
	}
	--it;
	cout << *it << "\n";
	return 0;
}
```


---

## 作者：Great_Influence (赞：0)

容易发现，$2^{67}=147573952589676412928$ 远远大于 $10^{18}$ ，不可能是答案。因此我们只需要考虑 $2$ 到 $61$ 次方产生的贡献。

又容易发现， $\sqrt[3]{10^{18}}=10^6$ 。 在 $10^{6}$ 到 $2\times10^{6}$ 中间大约有质数 $1.37\times 10^5$ 个，因此对于指数大于等于 $3$ 的部分底数不会超过 $2\times 10^6$ 。 这部分利用线性筛即可处理完毕。

麻烦的是指数为 $2$ 的部分， 因为这部分底数都是 $10^9$ 级的。 不过，通过估算我们可以发现在 $10^9$ 到 $10^9+10^6$ 之间一共有质数 $4.7\times 10^5$ 个，因此我们的底数不会超过 $10^9+10^6$ 。这样的话底数的跨度不会超过 $10^6$， 我们完全可以一个个枚举观察是否是质数。

至于快速判断一个数是不是质数，那当然是 $millerrabin$ 算法了。单次计算时间复杂度 $O(\log w)$ 。

我们把每个不同指数当前大于 $n$ 的最小数字放到堆里面，每次取出最小的后更新一下就可以了。

时间复杂度 $O(10^6\log 10^9+k\log 18)$ 。

代码:
```cpp
#include<bits/stdc++.h>
#include<cctype>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register uint32 i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register uint32 i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
}
using uint64=unsigned long long;
using uint128=__uint128_t;
using uint32=unsigned int;

const uint32 bace[5]={2,3,7,61,24251};

inline uint32 pow(uint32 x,uint32 y,uint32 mod)
{
    static uint32 sm;
    for(sm=1;y;y>>=1,x=(uint64)x*x%mod)if(y&1)sm=(uint64)sm*x%mod;
    return sm;
}
inline bool millerrabin(uint32 x)
{
    if(x<2)return false;
    if(x==2||x==3||x==7||x==61||x==24251)return true;
    static uint32 ba,r;ba=x-1;
    static uint32 ti,j;ti=0;
    while(!(ba&1))ba>>=1,++ti;
    Rep(i,0,4)
    {
        r=pow(bace[i],ba,x);
        if(r==1||r==x-1)continue;
        for(j=1;j<=ti;++j)
        {
            r=(uint64)r*r%x;
            if(r==x-1)break;
        }
        if(j>ti)return false;
    }
    return true;
}

static uint64 n;

static uint32 k;

static struct nd
{
	uint32 nm, pw;
	uint64 w;
	friend bool operator < (nd a, nd b) {return a.w > b.w;}
}z;

priority_queue <nd> Q;

const int MAXN = 2e5 + 7;

static uint32 pri[MAXN], e;

bitset <2000001> is;

inline void getpri()
{
	const int lm = 2e6;
	Rep(i, 2, lm)
	{
		if(!is.test(i)) pri[++ e] = i;
		for(register int j = 1; j <= e && i <= lm / pri[j]; ++ j)
		{
			is.set(i * pri[j]);
			if(i % pri[j] == 0) break;
		}
	}
}

inline uint64 power(uint32 u, uint32 v)
{
	uint64 d = 1;
	while(v --)
	{
		if(d > LLONG_MAX / u) return LLONG_MAX;
		d *= u;
	}
	return d;
}

int main()
{
    file();
	read(n);
	getpri();
	Rep(i, 2, 18)
	{
		z = (nd){1, pri[i], 1llu << pri[i]};
		while(z.w <= n)
		{
			++ z.nm;
			z.w = power(pri[z.nm], z.pw);
		}
		Q.push(z);
	}
	uint32 r = sqrt(n);
	while((uint64) r * r <= n) ++ r;
	if(r % 2 == 0) ++ r;
	while(! millerrabin(r)) r += 2;
	Q.push((nd){r, 2, (uint64) r * r});
	read(k);
	while(-- k)
	{
		z = Q.top(), Q.pop();
		if(z.pw == 2)
		{
			z.nm += 2;
			while(! millerrabin(z.nm)) z.nm += 2;
			Q.push((nd){z.nm, 2, (uint64) z.nm * z.nm});
		}
		else Q.push((nd){z.nm + 1, z.pw, power(pri[z.nm + 1], z.pw)});
	}
	printf("%llu\n", Q.top().w);
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
```

---

