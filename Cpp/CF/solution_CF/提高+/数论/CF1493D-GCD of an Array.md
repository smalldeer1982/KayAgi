# GCD of an Array

## 题目描述

You are given an array $ a $ of length $ n $ . You are asked to process $ q $ queries of the following format: given integers $ i $ and $ x $ , multiply $ a_i $ by $ x $ .

After processing each query you need to output the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all elements of the array $ a $ .

Since the answer can be too large, you are asked to output it modulo $ 10^9+7 $ .

## 说明/提示

After the first query the array is $ [12, 6, 8, 12] $ , $ \operatorname{gcd}(12, 6, 8, 12) = 2 $ .

After the second query — $ [12, 18, 8, 12] $ , $ \operatorname{gcd}(12, 18, 8, 12) = 2 $ .

After the third query — $ [12, 18, 24, 12] $ , $ \operatorname{gcd}(12, 18, 24, 12) = 6 $ .

Here the $ \operatorname{gcd} $ function denotes the greatest common divisor.

## 样例 #1

### 输入

```
4 3
1 6 8 12
1 12
2 3
3 3```

### 输出

```
2
2
6```

# 题解

## 作者：Na2PtCl6 (赞：15)

## 分析题目
题目让我们动态地求 $\gcd(a_1,a_2,...,a_n)$ ，而且每次单点乘，容易想到一个结论 $\gcd(x \times k,y \times k)=\gcd(x,y)\times k$，所以我们只用关注这个 $k$ 。所以，只要在修改后，整个序列中每个数都整除 $k$ ，整个序列的 $\gcd$ 就能增加 $k$。

根据以上结论，我们想到把每个数分解质因数。如果发现对于某个质数 $p$ ，序列的每个位置都存在这个质因子，答案就是之前答案的 $p$ 倍。

分解质因数用欧拉筛预处理每个数的最小质因子，可以做到 $O(loga)$ 分解数 $a$，而且远远达不到这个界。

看质数是否在每个位置都能被整除用 `multiset` ，对于每个质数都开一个来记录这个质数在序列中出现的位置（下标）。还要一个辅助数组来记录序列中多少个位置上有这个质因子。每当在一个位置上乘一个数，我们就把它分解成质数，对于每个质数的 `multiset` ,做以下事情：

1.判断它在这个 `multiset` 中是否出现，如果没有，就说明又一个位置被填上了这个质因子 

2.插入当前下标 
  
3.如果当前质数在每个位置上都有，就暴力把 $1$~$n$ 每个下标在 `multiset` 中 **删掉一次**。

因为每个数 $a_i$ 最多增加 $loga_i$ 个质因子，所有的 `multiset` 中最多有 $mlogm+nlogn$ 个下标，而删一次删掉 $n$ 个，所以最多删 $\frac {mlogm+nlogn}{n}$ 次，是 $logn$ 级别的。 所以，最终的时间复杂度大致为 $O(nlog^2n)$，空间 $O(nlogn)$

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=200004,mod=1e9+7;
bool vis[maxn];
int n,m,cnt,x,a[maxn],pr[maxn],filled[maxn],mpd[maxn];
LL y,g=1;
multiset < int > s[maxn];

void get_mpd(){
	mpd[1]=1;
	for(int i=2;i<maxn;i++){
		if(!vis[i]){
			mpd[i]=i;
			pr[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*pr[j]<maxn;j++){
			vis[i*pr[j]]=1;
			mpd[i*pr[j]]=pr[j];
			if(i%pr[j]==0)
				break;
		}
	} 
}

void modify(int p,LL v){
	while(v!=1){
		if(s[mpd[v]].find(p)==s[mpd[v]].end())
			++filled[mpd[v]];
		s[mpd[v]].insert(p);
		if(filled[mpd[v]]==n){
			filled[mpd[v]]=0;
			for(int i=1;i<=n;i++){
				s[mpd[v]].erase(s[mpd[v]].find(i));
				if(s[mpd[v]].find(i)!=s[mpd[v]].end())
					++filled[mpd[v]];
			}
			g=(g*mpd[v])%mod;
		}
		v/=mpd[v];
	}
}

signed main(){
	get_mpd();
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		modify(i,a[i]);
	while(m--){
		scanf("%d %lld",&x,&y);
		modify(x,y);
		printf("%d\n",g);
	}
	return 0;
}
```
仅仅 57 行，相信不是很长。如果觉得很妙就点个赞吧。

---

## 作者：meyi (赞：8)

提供一种时空复杂度和代码难度均较低的做法（这里的较低指的是相对于题目限制和CF上的Status较低）。

考虑在 $x$ 位置乘上 $y$ 对答案的贡献，若数列中其他数中质因子 $pri$ 的出现次数最小为 $k_1$，$x$ 位置的数中 $pri$ 的出现次数为 $k_2$，$y$ 中 $pri$ 的出现次数为 $k_3$。若 $k_1>k_2$，那么这次操作对答案的贡献为 $pri^{\min(k_1-k_2,k3)}$。

对于一个数 $a$，我们记录它最小的质因子 $lp_a$，显然 $lp_a$ 可以用线性筛预处理。然后我们开两个个累加器数组 $dcnt$ 和 $pcnt$，$dcnt_{i,j}$ 表示 $i^j$ 在当前数列中为多少个数的因子，$pcnt_{i,j}$ 表示位置为 $i$ 的数中因子 $j$ 的出现次数。

当我们需要在 $x$ 位置乘上 $y$ 时，若 $lp_y\neq0$，则 $dcnt_{x,lp_y}$ 自增，并将自增后的值用变量 $tmp$ 记录，若 $pcnt_{lp_y,tmp}$ 自增后的值为 $n$，则答案应乘上 $lp_y$（为什么不是 $lp_{y}^{tmp}$？因为 $pcnt_{lp_y,tmp-1}$ 必定已经到达过 $n$，所以每次只需乘 $lp_y$），最后 $y$ 自除 $lp_y$，重复上述操作即可。

需要注意的是， $x$ 和 $lp_y$ 都是 $2*10^5$ 级别的，因此 $pcnt$ 需要开成 `map` 类型。

时间复杂度：$O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2e5+10,maxp=2e4+10,mod=1e9+7;
int lp[maxn],n,rev[maxn],q;
vector<int>cnt_div[maxp],pri;
map<int,int>cnt_pos[maxn];
ll ans=1;
inline void add(int pos,int val){
	while(lp[val]){
		ri p=lp[val];
		while(val%p==0){
			val/=p;
			ri id=rev[p],tmp=cnt_pos[pos][id]++;
			if(cnt_div[id].size()<=tmp)cnt_div[id].push_back(0);
			if(++cnt_div[id][tmp]==n)ans=ans*p%mod;
		}
	}
}
int main(){
	for(ri i=2;i<200001;++i){
		if(!lp[i])lp[i]=i,rev[i]=pri.size(),pri.push_back(i);
		for(ri j=0;j<pri.size()&&i*pri[j]<200001;++j)lp[i*pri[j]]=pri[j];
	}
	scanf("%d%d",&n,&q);
	for(ri i=1;i<=n;++i){
		int a;
		scanf("%d",&a);
		add(i,a);
	}
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：rui_er (赞：8)

昨晚 CF 这题最后没调出来，B FST，然后赛后几分钟把这两题全过了，心态炸了，来发篇题解理一下思路。

题意：已知一个长度为 $n$ 的数列 $a_n$，$q$ 次操作，每次将 $a_i$ 乘以 $x$，在每次操作后输出整个数列的 gcd。

---

思路

首先，根据基础数学知识，我们知道 gcd 的一个质因子个数是每个数该质因子个数中的最小值。同时看数据范围是 $2\times 10^5$，考虑使用线段树。

我们对每个质数开一个线段树，向上更新的方法是两侧取 min。对于每个数和每次修改操作，先对其分解质因数，把每个因数插进线段树中。先保存最开始时的 gcd，然后对于每次修改，只更新被修改的树的乘方数即可。

---

代码

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 ll T; for(scanf("%lld", &T);T;T--)
#define mulT1 ll T, rnds; for(scanf("%lld", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const ll N = 2e5+5, K = 1e3+5, W = 2e5, P = 1e7+5, mod = 1e9+7, inf = 0x3f3f3f3f3f3f3f3f;

ll n, q, a[N], rt[N], tot, ans;
ll tab[N], prime[N], primecnt = 0;
ll qpow(ll x, ll y) {
	ll res = 1;
	for(;y;y>>=1,x=x*x%mod) if(y & 1) res = res * x % mod;
	return res;
}
struct Node {
	ll w, lc, rc;
	Node(ll a=0, ll b=0, ll c=0) : w(a), lc(b), rc(c) {}
	~Node() {}
}t[P];
void pushup(ll u) {t[u].w = min(t[t[u].lc].w, t[t[u].rc].w);}
void insert(ll &u, ll l, ll r, ll pos, ll delta) {
	if(!u) u = ++tot;
	if(l == r) {t[u].w += delta; return;}
	ll mid = (l + r) >> 1;
	if(pos <= mid) insert(t[u].lc, l, mid, pos, delta);
	else insert(t[u].rc, mid+1, r, pos, delta);
	pushup(u);
}

void sieve() {
	rep(i, 2, W) tab[i] = 1;
	rep(i, 2, W) {
		if(tab[i]) prime[++primecnt] = i;
		for(ll j=1;j<=primecnt&&prime[j]*i<=n;j++) {
			tab[prime[j]*i] = 0;
			if(!(i % prime[j])) break;
		}
	}
}

int main() {
	sieve();
	scanf("%lld%lld", &n, &q);
	rep(i, 1, n) {
		scanf("%lld", &a[i]);
		rep(j, 1, primecnt) {
			if(prime[j] * prime[j] > a[i]) break;
			ll cnt = 0;
			while(a[i] % prime[j] == 0) ++cnt, a[i] /= prime[j];
			if(cnt) insert(rt[j], 1, n, i, cnt);
			if(a[i] == 1) break;
		}
		if(a[i] != 1) {
			ll pr = lower_bound(prime+1, prime+1+primecnt, a[i]) - prime;
			insert(rt[pr], 1, n, i, 1);
		}
	}
	ans = 1; 
	rep(i, 1, primecnt) ans *= qpow(prime[i], t[rt[i]].w);
	while(q--) {
		ll pos, w;
		scanf("%lld%lld", &pos, &w);
		rep(i, 1, primecnt) {
			if(prime[i] * prime[i] > w) break;
			ll cnt = 0;
			while(w % prime[i] == 0) ++cnt, w /= prime[i];
			if(cnt) {
				ll lst = t[rt[i]].w;
				insert(rt[i], 1, n, pos, cnt);
				ans = ans * qpow(prime[i], t[rt[i]].w-lst) % mod;
			}
			if(w == 1) break;
		}
		if(w != 1) {
			ll pr = lower_bound(prime+1, prime+1+primecnt, w) - prime;
			ll lst = t[rt[pr]].w;
			insert(rt[pr], 1, n, pos, 1);
			ans = ans * qpow(w, t[rt[pr]].w-lst) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：registerGen (赞：3)

[更好的阅读体验](https://registergen.github.io/post/solution-cf1493d/)

# Solution

考虑 $\gcd(a_1,\cdots,a_n)$ 的本质。$\gcd$ 其实是，将 $a_i$ 分解质因数，对于每个质数 $p_k$，看它的次数 $b_{k,i}$，再取 $\displaystyle\min_{i=1}^n b_{k,i}$，那么 $\gcd$ 就是：

$$\large\prod_{i=1}^k p_k^{\min\limits_{i=1}^n b_{k,i}}$$

那我们怎么维护这个 $\displaystyle\min_{i=1}^n b_{k,i}$ 呢？可以考虑 **对每个质数 $p_k$，开一个维护 $\min b_{k,i}$ 的线段树**。事实证明这个玩意很好写。

我们对于每个 $a_i$ 分解质因数然后暴力插进线段树里，然后算出一开始的 $\gcd$。显然之后的 $\gcd$ 都是上一次操作的 $\gcd$ 乘上一个数。我们考虑暴力统计这个变化量。我们将 $y$（要乘的数） 分解质因数然后暴力插进线段树里，然后再看一下 $\displaystyle\min_{i=1}^n b_{k,i}$ 的变化量（当然我们只考虑修改过的）即可。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>

const int N=2e5;
const int P=1e9+7;

struct Node{
	int num,ls,rs;
};

int n,m,a[N+10];
int prime[N+10],notPrime[N+10],totp,id[N+10];
Node t[N*70+10];
int root[N+10],cnt;

// 线性筛
void init(){
	notPrime[1]=1;
	for(int i=2;i<=N;i++){
		if(!notPrime[i])prime[++totp]=i,id[i]=totp; // id[i] 表示 i 是第几个质数
		for(int j=1;j<=totp&&prime[j]*i<=N;j++){
			if(i%prime[j]==0)break;
			notPrime[i*prime[j]]=1;
		}
	}
}

// 动态开点线段树
#define ls(x) (t[x].ls)
#define rs(x) (t[x].rs)

inline void pushUp(int i){
	t[i].num=std::min(t[ls(i)].num,t[rs(i)].num);
}

void insert(int& i,int l,int r,int pos,int v){
	if(!i)i=++cnt;
	if(l==r)return t[i].num+=v,void();
	int mid=(l+r)>>1;
	if(pos<=mid)insert(ls(i),l,mid,pos,v);
	else insert(rs(i),mid+1,r,pos,v);
	pushUp(i);
}

#undef ls
#undef rs

inline int qpow(int a,int b){
	int res=1;
	while(b){if(b&1)res=1LL*res*a%P;a=1LL*a*a%P;b>>=1;}
	return res;
}

int main(){
	init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		int x=a[i];
		// 分解质因数
		for(int j=2;j<=int(sqrt(a[i]));j++){
			if(notPrime[j])continue;
			int k=0;
			while(x>0&&x%j==0)k++,x/=j;
			if(k>0)insert(root[id[j]],1,n,i,k);
		}
		int tmp=x;
		if(!notPrime[tmp]){
			int k=0;
			while(x>0&&x%tmp==0)k++,x/=tmp;
			if(k>0)insert(root[id[tmp]],1,n,i,k);
		}
	}
	int ans=1;
	for(int i=1;i<=totp;i++)
		ans=1LL*ans*qpow(prime[i],t[root[i]].num)%P;
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		std::vector<int> modified,lst; // modified：修改了的线段树；lst：上一次的答案
		int yy=y;
		// 分解质因数
		for(int j=2;j<=int(sqrt(yy));j++){
			if(notPrime[j])continue;
			int k=0;
			while(y>0&&y%j==0)k++,y/=j;
			if(k>0)modified.push_back(id[j]),lst.push_back(t[root[id[j]]].num),insert(root[id[j]],1,n,x,k);
		}
		int tmp=y;
		if(!notPrime[tmp]){
			int k=0;
			while(y>0&&y%tmp==0)k++,y/=tmp;
			if(k>0)modified.push_back(id[tmp]),lst.push_back(t[root[id[tmp]]].num),insert(root[id[tmp]],1,n,x,k);
		}
		for(std::vector<int>::iterator it=modified.begin(),it2=lst.begin();it!=modified.end();it++,it2++)
			ans=1LL*ans*qpow(prime[*it],t[root[*it]].num-(*it2))%P;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：little_sun (赞：2)

### 题目描述

有一个 $n$ 长的数组 $a$，有 $m$ 次操作，每次操作把 $a_x$ 乘上 $y$， 并询问数组中所有数的 $\texttt{gcd}$。

$ n, m, a_i, y \leq 2 \times 10 ^ 5$ 

### 题目分析

我们发现不管是 $a_i$ 还是 $y$ 值域都很小，这启发我们对于每一个质数分开考虑。

我们考虑对于每个质数维护一个 `multiset`，里面存放的是所有该质数 $>0$ 的指数，那么我们就可以动态的维护每一个质数对于答案的贡献，从而解决这道题

### 代码

``` cpp
#include <bits/stdc++.h>
 
#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)
 
const int mod = 1e9 + 7;
const int MaxN = 2e5 + 10;
 
std::multiset<int> s[MaxN];
std::map<int, int> mp[MaxN], tmp;
int n, m, tot, ans, a[MaxN], pri[MaxN];
int prime[MaxN], fac[MaxN], vis[MaxN];
 
int fast_pow(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1)
            ret = (ll)ret * a % mod;
        a = (ll)a * a % mod, b >>= 1;
    }
    return ret;
}
 
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
 
void init()
{
    for (int i = 2; i < MaxN; ++i)
    {
        if (!vis[i]) prime[++tot] = i, fac[i] = i;
        for (int j = 1; j <= tot && (prime[j] * i < MaxN); ++j)
        {
            vis[i * prime[j]] = true;
            fac[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
}
 
signed main()
{
    init(), n = read(), m = read(), ans = 1;
    for (int i = 1, x; i <= n; i++)
    {
        x = a[i] = read();
        while (x > 1)
            mp[i][fac[x]]++, x /= fac[x];
        for (auto y : mp[i])
            s[y.first].insert(y.second);
    }
    for (int i = 2; i < MaxN; i++)
        if (!vis[i] && s[i].size() == n)
            ans = (ll)ans * fast_pow(i, *s[i].begin()) % mod;
    for (int i = 1, x, y; i <= m; i++)
    {
        x = read(), y = read(), tmp.clear();
        while (y > 1)
            tmp[fac[y]]++, y /= fac[y];
        for (auto z : tmp)
        {
            int now = z.first; 
            if (!mp[x][now])
            {
                mp[x][now] = z.second, s[now].insert(z.second);
                if (s[now].size() == n) 
                    ans = (ll)ans * fast_pow(now, *s[now].begin()) % mod;
            }
            else
            {
                if (s[now].size() == n)
                    ans = (ll)ans * fast_pow(fast_pow(now, *s[now].begin()), mod - 2) % mod;
                s[now].erase(s[now].find(mp[x][now])), mp[x][now] += z.second, s[now].insert(mp[x][now]);
                if (s[now].size() == n)
                    ans = (ll)ans * fast_pow(now, *s[now].begin()) % mod;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
} 
```

---

## 作者：OranJun (赞：2)

## $Solution$

考虑 $\gcd$ 其实就是对每个$p[i]$来说， $\min_{i=1}^na[i]$ ，其中 $a[i]$ 表示 $val[i]$ 质因数分解后 $p[i]$ 的次数。

因为每次操作都是增加 $a[i]$，所以答案单调不减，我们用一个 $map$ 维护每一个数的质因数分解情况，再用一个 $multiset$ 统计维护这个质因数次数的最小值，每次比较与上次答案的差别，乘上答案就可以了。

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i=a;i<=b;++i)
#define rf(i,a,b) for(int i=a;i>=b;--i)
template<typename T>
inline void read(T &x){
	char c=getchar();x=0;bool f=0;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	x=f?-x:x;
}
typedef long long ll;
const int N=2e5+5;
const int mod=1e9+7;
int a[N],n,q;
int p[N],zb[N],tot;
bool b[N];
multiset<int> s[N];
map<int,int> mp[N];
void make_prime(int n){
	p[tot=1]=2;
	fr(i,3,n){
		if(b[i])continue;
		p[++tot]=i;
		fr(j,i,n/i)b[i*j]=1;
	}
}
ll ans=1;
void add(int pos,int x){
	for(int i=1;i<=tot&&p[i]<=sqrt(x);++i){//枚举质因数
		if(x%p[i])continue;
		int cnt=0;
		while(x%p[i]==0)x/=p[i],++cnt;
		//计算出p[i]与次数cnt
		int ls_mn=0;
		if((int)s[p[i]].size()==n)ls_mn=*s[p[i]].begin();//如果这个质因数存在最大公约数，即min[a[i]]>0，就记录上次的答案
		int ls=mp[pos][p[i]];
		mp[pos][p[i]]+=cnt;//更新mp[pos]
		if(ls)s[p[i]].erase(s[p[i]].find(ls));s[p[i]].insert(ls+cnt);//删去旧的插入新的
		if((int)s[p[i]].size()==n){//如果新的有最大公约数
			int up=*s[p[i]].begin();//新的最小值
			fr(j,ls_mn+1,up)ans=ans*1ll*p[i]%mod;//就统计答案
		}
	}
	if(x){//可能还有一个>sqrt(x)的质数，再分解一次
		int ls_mn=0;
		if((int)s[x].size()==n)ls_mn=*s[x].begin();
		int ls=mp[pos][x];
		mp[pos][x]++;
		if(ls)s[x].erase(s[x].find(ls));s[x].insert(ls+1);
		if((int)s[x].size()==n){
			int up=*s[x].begin();
			fr(j,ls_mn+1,up)ans=ans*x%mod;
		}
	}
}
int main(){
	make_prime(200000);//预处理质因数
	read(n),read(q);
	fr(i,1,n){
		int x;//这里把读入也看作是插入操作
		read(x);
		add(i,x);
	}
	while(q--){
		int pos,x;
		read(pos),read(x);
		add(pos,x);
		printf("%lld\n",ans);
	}
	
}


---

## 作者：Leasier (赞：1)

~~倒数第三劣解来写题解了~~

前置芝士：[线性筛](https://oi-wiki.org/math/number-theory/sieve/#_7)

考虑每个数的互异质因数个数实际上较少，容易想到对每个位置维护一个 map 以及对每个质数维护一个 multiset，表示当前位置的所有质因数和当前质数存在的所有幂次。

修改时，利用 lpf 将 $x$ 分解质因数，求出每个质因数的幂次，然后在 map 和 multiset 上做相应的修改操作即可。

注意需要特判当前质数是否被 $a_1 \sim a_n$ 中的每个数包含。

时间复杂度为 $O((n + m) \log (\sum \omega(a_i) + \sum \omega(y)))$。

代码：
```cpp
#include <iostream>
#include <map>
#include <set>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 2e5 + 7, mod = 1e9 + 7;
ll cur_ans = 1;
int prime[N], lpf[N], global_cnt[N];
bool p[N], vis[N];
map<int, int> mp[N];
multiset<int> s[N];

inline void init(){
	int cnt = 0;
	p[0] = p[1] = true;
	lpf[1] = 0;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			lpf[i] = i;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			lpf[t] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void mul(int pos, int k, int n){
	while (k > 1){
		int cur_prime = lpf[k], cur_cnt = 0, pre;
		while (k % cur_prime == 0){
			k /= cur_prime;
			cur_cnt++;
		}
		if (mp[pos][cur_prime] != 0) s[cur_prime].erase(s[cur_prime].lower_bound(mp[pos][cur_prime]));
		mp[pos][cur_prime] += cur_cnt;
		s[cur_prime].insert(mp[pos][cur_prime]);
		if (s[cur_prime].size() == n){
			pre = global_cnt[cur_prime];
			global_cnt[cur_prime] = *s[cur_prime].begin();
			cur_ans = cur_ans * quick_pow(cur_prime, global_cnt[cur_prime] - pre, mod) % mod;
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	init();
	for (register int i = 1; i <= n; i++){
		int a;
		scanf("%d", &a);
		mul(i, a, n);
	}
	for (register int I = 1; I <= m; I++){
		int i, x;
		scanf("%d %d", &i, &x);
		mul(i, x, n);
		cout << cur_ans << endl;
	}
	return 0;
}
```

---

## 作者：7KByte (赞：1)

观察一下答案只增不减，对于任何一个质因子，答案也只增不减。

那么我们可以对每个质因子求出在哪些询问后需要使答案乘上质因子的次幂。

一个数最多只有 $6$ 种不同的质因子，所以我们可以把每个数拆成不同的质因子次幂的乘积，然后对每个质因子分别维护。

对于每个质因子，我们初始一个长度为 $N$ 的全部为 $0$ 的数列。需要维护的是整个数列的最小值，并支持单点加。这不难用线段树维护。

由于质因子总数可能不少，所以不能每次直接清空线段树。可以按照加的顺序将它减回去，也可以选择对每个质因子建一颗动态开点线段树。不难发现后者还好写一些/cy。

时间复杂度$\rm O(N\sqrt N+N\log N)$，假定 $N,M,a_i$ 同规模。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define P 1000000007
#define int long long 
using namespace std;
int n,q;
struct pt{
	int op,x,y;
	pt(int O=0,int X=0,int Y=0){op=O;x=X;y=Y;}
};
struct node{
	signed l,r,sum;
}a[16000000];
#define ls a[x].l
#define rs a[x].r
#define S a[x].sum
int idx=0,u[N],ans[N];
void change(int x,int L,int R,int pos,int val){
	if(L==R)S+=val;
	else{
		int mid=(L+R)>>1;
		if(mid>=pos){
			if(!ls)ls=++idx;
			change(ls,L,mid,pos,val);
		}
		else {
			if(!rs)rs=++idx;
			change(rs,mid+1,R,pos,val);
		}
		S=min(a[ls].sum,a[rs].sum);
	}
}
vector<pt>c[N];
int Pow(int x,int y){
	int now=1;
	for(;y;y>>=1,x=x*x%P)if(y&1)now=now*x%P;
	return now;
}
void calc(int x){
	int rt=++idx;
	int i=0;
	while(i<(int)c[x].size()&&c[x][i].op==0){
		change(rt,1,n,c[x][i].x,c[x][i].y);
		i++;
	}
	int now=a[rt].sum;
	ans[1]=ans[1]*Pow(x,a[rt].sum)%P;
	//cout<<a[rt].sum<<" "<<a[a[rt].l].sum<<" "<<a[a[rt].r].sum<<  "u   "<<endl;
	while(i<(int)c[x].size()){
		int cur=c[x][i].op;
		while(i<(int)c[x].size()&&cur==c[x][i].op){
			change(rt,1,n,c[x][i].x,c[x][i].y);
			i++;
		}
		//cout<<a[rt].sum<<" "<<a[a[rt].l].sum<<" "<<a[a[rt].r].sum<<  "u   "<<endl;
		ans[cur]=ans[cur]*Pow(x,a[rt].sum-now)%P;now=a[rt].sum;
	}
	//cout<<i<<" "<<x<<" "<<now<<"s "<<endl; 
}
signed main(){
	scanf("%lld%lld",&n,&q);
	rep(i,1,n){
		scanf("%lld",&u[i]);
		for(int x=2;x*x<=u[i];x++){
			int sum=0;
			while(u[i]%x==0)u[i]/=x,sum++;
			if(sum)c[x].push_back(pt(0,i,sum));
		}
		if(u[i]>1)c[u[i]].push_back(pt(0,i,1));
	}
	rep(i,1,q){
		int ps,w;scanf("%lld%lld",&ps,&w);
		ans[i]=1;
		for(int x=2;x*x<=w;x++){
			int sum=0;
			while(w%x==0)w/=x,sum++;
			if(sum)c[x].push_back(pt(i,ps,sum));
		}
		if(w>1)c[w].push_back(pt(i,ps,1));
	}
	/*rep(i,1,200000){
		if(c[i].size()){
			printf("  %lld\n",i);
			for(int w=0;w<(int)c[i].size();w++)printf("%lld %lld %lld\n",c[i][w].op,c[i][w].x,c[i][w].y);
		}
	}*/
	rep(i,1,200000)if(c[i].size())calc(i);ans[0]=1; 
	rep(i,1,q)ans[i]=ans[i]*ans[i-1]%P,printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

动态开点线段树练手好题。

## 思路

首先我们看到 $\gcd$ 这个式子，自然而然的想到了质因数分解。这样，一个序列的 $\gcd$ 就可以求出：

首先算出每个数的质因子的并集，这个分解质因数可以轻易的做到；然后，对于每个质因子，将 $a_1$ 至 $a_n$ 中含有这个质因子的个数最小的那个值相乘。将每一个质因数分别这样处理，最后乘起来即可得到最终结果。

假设共有 $m$ 个不同的质因子 $p_1,p_2,\cdots,p_m$。另外，对于 $a_i$，假设它包含 $k_{i,j}$ 个 $p_j$ 这个因子。那么可以得到这个式子：

$$\gcd\limits_{i=1}^{n}a_i=\prod\limits_{i=1}^{m}p_i^{\min\limits_{j=1}^{n}k_{i,j}}$$

等式右边这个就是我们要维护的东西。

### Part 1

首先，对于 $\min k_{i,j}$，这个是容易求得的，只需要对于每个 $p_i$ 进行动态开点的线段树处理即可。

- 空间复杂度的证明：$\geq \sqrt[2^k]{n}$ 最多是 $k$ 次方，所以总共的复杂度就是 $\left(\sum\limits_{k=1}^{\log n}\sqrt[2^k]{n} \cdot k\right) \cdot \log n$，可以视为 $O(n \log n)$ 量级。所以空间复杂度是可以通过的。

### Part 2

我们已经求得了 $\min\limits_{j=1}^{n} k_{i,j} = S$，那么怎么求 $\prod\limits_{i=1}^{m} p_i^S$ 呢？这个其实很好办，我们只需要一个支持插入和全局查询的东西即可。我当时脑抽了使用了线段树，线段树开了 $m$ 个节点，第 $i$ 个节点表示 $p_i$ 当前有几次方，求的时候就对于 $p_i$ 进行一个快速幂。这样的时间复杂度是：

$$O(\text{询问} \times \text{分解质因数} \times \text{线段树} \times \text{快速幂}) = O(m \times \sqrt{n} \times \log{n} \times \log{w}) \approx O(m \sqrt{n} \log^2 n)$$

但是我们实际上快速幂总共也就会运行 $O(\log(\sum \sqrt{a_i} + \sum \sqrt{y}))$ 次，远远跑不满，实际上严格来讲只有 $O(m \sqrt{n} \log{n} + \log(\sum\sqrt{a_i}+\sum\sqrt{y}))$ 的复杂度，所以可以通过本题。

后来想了想，好像不用线段树也可以做，这样时间复杂度是 $O(m \sqrt n)$ 的（？

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define lb lower_bound
using namespace std;
const int MAXN=200005,Maxp=200000,mod=1000000007;
struct Segment_Tree{
	int x,ls,rs;
}tr[10000005];
int Tt[MAXN<<2],tot,root[MAXN],a[MAXN],prime[MAXN],cntp;
bool isprime[MAXN];
inline int qmin(const int &a,const int &b){return a<b?a:b;}
inline int qmax(const int &a,const int &b){return a>b?a:b;}
inline int ksm(const int &a,int b){ //快速幂
	int base=a,ans=1;
	while(b){
		if(b&1) (ans*=base)%=mod;
		(base*=base)%=mod;
		b>>=1;
	}return ans;
}void upd(int &p,int l,int r,int t,int k){ // 维护 1~n 中每个数包含当前质因数的个数
	if(!p) p=++tot; // 动态开点
	if(l==r){
		tr[p].x+=k;
		return;
	}int mid=(l+r)>>1;
	if(t<=mid) upd(tr[p].ls,l,mid,t,k);
	else upd(tr[p].rs,mid+1,r,t,k);
	tr[p].x=qmin(tr[tr[p].ls].x,tr[tr[p].rs].x);
}void Upd(int p,int l,int r,int t,int k){ // 维护 prime[i] 在 gcd 里是几次方
	if(l==r){
		Tt[p]=ksm(prime[l],k)%mod; // prime[l] 的 k 次方
		return;
	}int mid=(l+r)>>1;
	if(t<=mid) Upd(p<<1,l,mid,t,k);
	else Upd(p<<1|1,mid+1,r,t,k);
	Tt[p]=1ll*qmax(1ll,Tt[p<<1])*qmax(1ll,Tt[p<<1|1])%mod; // 如果 Tt[i] 是 0 要变成 1 乘上。
}void Esprime(){ //筛质数
	for(int i=2;i<=Maxp;i++)
		if(!isprime[i]){
			for(int j=i;j*i<=Maxp;j++)
				isprime[i]=1;
			prime[++cntp]=i;
		}
}signed main(){
	Esprime();
	ios::sync_with_stdio(false);
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;prime[j]*prime[j]<=a[i];j++) // 质因数分解
			if(a[i]%prime[j]==0){
				int cnt=0;
				while(a[i]%prime[j]==0) a[i]/=prime[j],cnt++;
				upd(root[j],1,n,i,cnt); // 从 root[j] 递归，相当于访问 prime[j] 所在的线段树
//				cout<<tr[root[j]].x<<endl;
				Upd(1,1,cntp,j,tr[root[j]].x); // 要注意两个线段树的范围不同，维护 1~n 每个数当前质因数个数的那个是 1~n，而维护质因数次数的是 1~cntp（质数总个数）。
			}
		if(a[i]>1){ // 说明这也是一个质因子
			int plc=lb(prime+1,prime+1+cntp,a[i])-prime;
			upd(root[plc],1,n,i,1);
//			cout<<tr[root[plc]].x<<endl;
			Upd(1,1,cntp,plc,tr[root[plc]].x);
		}
	}while(m--){
		int x,y; cin>>x>>y;
		for(int j=1;prime[j]*prime[j]<=y;j++) // 和上面 a[i] 同理
			if(y%prime[j]==0){
				int cnt=0;
				while(y%prime[j]==0) y/=prime[j],cnt++;
				upd(root[j],1,n,x,cnt);
//				cout<<tr[root[j]].x<<endl;
				Upd(1,1,cntp,j,tr[root[j]].x);
			}
		if(y>1){
			int plc=lb(prime+1,prime+1+cntp,y)-prime;
			upd(root[plc],1,n,x,1);
//			cout<<tr[root[plc]].x<<endl;
			Upd(1,1,cntp,plc,tr[root[plc]].x);
		}cout<<qmax(1ll,Tt[1])<<endl; // 也要特判 Tt[1]=0 的情况。Tt[1] 求得就是全局最小值
	}
	return 0;
}
```

---

## 作者：Mobius127 (赞：0)

[题传](https://www.luogu.com.cn/problem/CF1493D)

直接对于每一个质因子开一个桶，那么就变成了修改操作在几颗线段树上单点加单点取 $\min$，求 $\gcd$ 则是把所有的质因子线段树上的 $\min$ 当指数，线段树动态开点。

复杂度 $O((n+q)\sqrt{n}\log n)$ 发现并不能过，考虑再看一下数据范围 $a \le 2 \times 10^5$。

既然要求分解质因数，那么由：

$$2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17=510510 \ge 2 \times 10^5$$

可见分解出来的素数个数实际上事非常少的（不过 7 个），我们直接预处理掉。

那么复杂度就优化成了 $O((n+q) \log n)$，带上一个 $7$ 的小常数，以及预处里的 $O(n \ln n)$ 。

~~线段树多快，用什么 multiset~~

### Tip
>这里的指数比较小不需要取模，实际上是需要对 $\varphi(mod)=10^9+6$ 取模的。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline int ksm(int a, int b){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%mo)
		if(b&1) ret=1ll*ret*a%mo;
	return ret;
}
int u[N], p[N], cnt;
vector <int> f[N];
void pre(int lim){
	for(int i=2; i<=lim; i++){
		if(!u[i]) p[++cnt]=i;
		for(int j=1; j<=cnt&&1ll*i*p[j]<=(ll)lim; j++){
			u[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	for(int i=1; i<=cnt; i++)
		for(int j=1; 1ll*p[i]*j<=(ll)lim; j++)
			f[p[i]*j].push_back(p[i]);
	return ;
}
int root[N];
struct Segment_Tree{
	#define ls lc[k]
	#define rs rc[k]
	#define mid (l+r>>1)
	int tot, minn[N*50], lc[N*50], rc[N*50];
	void pushup(int k){
		int ret=1145140;
		ret=min(ret, minn[ls]);
		ret=min(ret, minn[rs]);
		minn[k]=ret;return ;
	}
	void add(int &k, int l, int r, int x, int v){
		if(!k) k=++tot;
		if(l==r){minn[k]+=v;return;}
		if(x<=mid) add(ls, l, mid, x, v);
		else add(rs, mid+1, r, x, v);
		return pushup(k);
	}
	int query(int rot){
		return minn[root[rot]];
	}
	#undef ls
	#undef rs
	#undef mid
}Chtholly;
int n, m, ans=1ll;
void doit(int x, int s){
	for(int i=0; i<f[s].size(); i++){
		int v=f[s][i];
		int las=Chtholly.query(v);
		if(las) ans=1ll*ans*ksm(ksm(v, las), mo-2)%mo;
		//乘逆元消除
		int t=0, tp=s;
		while(tp%v==0) t++, tp/=v;
		Chtholly.add(root[v], 1, n, x, t);
		ans=1ll*ans*ksm(v, Chtholly.query(v))%mo;
	}
}
signed main(){
	n=read(), m=read();pre(N-5);
	for(int i=1; i<=n; i++)
		doit(i, read());
	for(int i=1, x, y; i<=m; i++)
		x=read(), y=read(), doit(x, y), printf("%d\n", ans);
	return 0;
}

```


---

## 作者：xuezhe (赞：0)

看到 $\gcd$ 不难想到对每个质因数分别考虑，次数取最小值。

一个数 $x$ 的所有质因子的次数之和为 $O(\log x)$，直接枚举就好了。

于是对于每个质因数维护一个 set 就好了。

较为精细地实现可以做到 $O((n+q) \omega(x) \log n)$，其中 $\omega(x)$ 表示 $x$ 互不相同的质因数个数。

```cpp
const int P(1000000007);
int mpower(ll a,int b){
    int ret=1;
    while(b){
        if(b&1)
            ret=ret*a%P;
        a=a*a%P;
        b>>=1;
    }
    return ret;
}

int v[200005],c[200005],w[200005],pn,p[200005];
void Init(){
    for(int i=2;i<=200000;++i){
        if(!v[i])
            v[p[pn++]=i]=i,c[i]=1,w[i]=i;
        for(int j=0;j<pn && i*p[j]<=200000;++j){
            v[i*p[j]]=p[j];
            if(!(i%p[j])){
                c[i*p[j]]=c[i]+1;
                w[i*p[j]]=w[i]*p[j];
                break;
            }
            c[i*p[j]]=1;
            w[i*p[j]]=p[j];
        }
    }
}

map<int,int> mp[200001];
set<pii> st[200001];

int n,q,res=1;

void ins(int i,int x){
    while(x!=1){
        int t=v[x],o=0;
        if(int(st[t].size())==n)
            o=st[t].begin()->first;
        if(mp[t].count(i)){
            st[t].erase(pii(mp[t][i],i));
            mp[t][i]+=c[x];
        }else{
            mp[t][i]=c[x];
        }
        st[t].insert(pii(mp[t][i],i));
        if(int(st[t].size())==n)
            res=(ll)res*mpower(t,st[t].begin()->first-o)%P;
        x/=w[x];
    }
}

void fakemain(){
    Init();
    int i,x;
    Read(n),Read(q);
    for(i=1;i<=n;++i){
        Read(x);
        ins(i,x);
    }
    while(q--){
        Read(i),Read(x);
        ins(i,x);
        Print(res);
    }
}
```

---

## 作者：Fairicle (赞：0)

这题答案很大，**不能直接做**是很显然的。

容易发现如果我们可以维护**每个数的质因子次数**，以及**所有质因子次数的最小值**，那么这题就能做了。

考虑开一个 $\text{map}$ 统计每个数的质因子次数，再开一个 $\text{multiset}$ 去维护质因子次数，取它的首元素就是最小值。

最好是写个函数去做这个修改的过程，因为可以看做总共有 $n+q$ 次修改。（但是也挺麻烦的）

代码请配合 C++11 食用。

code：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ui unsigned int
#define ri register int
#define mp make_pair
#define mod 1000000007
#define N 200010
int n,q,p[N],mx=200000,tim[N];
map<int,int>vis[N];
ll ans=1;
inline ll ksm(ll x,int y){
	ll res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline ll getinv(ll x){
	return ksm(x,mod-2);	
}
inline void sieve(){
	for(ri i=2;i<=mx;++i){
		if(!p[i]){
			for(ri j=i;j<=mx;j+=i) p[j]=i;	
		}
	}
}
multiset<int>mn[N];
inline void mul(int i,int y){
	vector<pair<int,int> >fac;
	while(y>1){
		int num=0;
		int d=p[y];
		while(y%d==0) num++,y/=d;
		fac.push_back(mp(d,num));	
	}
	for(auto it:fac){
		int a=it.first,b=it.second;
		if(vis[i][a]==0){
			tim[a]++;
			mn[a].insert(b);
			if(tim[a]==n){
				ll val=ksm(a,*mn[a].begin());
				ans=ans*val%mod;
			}	
			vis[i][a]=b;
		}
		else{
			if(tim[a]==n){
				ll val=getinv(ksm(a,*mn[a].begin()));
				ans=ans*val%mod;
			}
			mn[a].erase(mn[a].find(vis[i][a]));
			vis[i][a]+=b;
			mn[a].insert(vis[i][a]);
			if(tim[a]==n){
				ll val=ksm(a,*mn[a].begin());
				ans=ans*val%mod;	
			}
		}
	}
}	
int x,y;
int main()
{
	sieve();
	n=rd(),q=rd();
	for(ri i=1;i<=n;++i) x=rd(),mul(i,x);
	while(q--) x=rd(),y=rd(),mul(x,y),printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：GsjzTle (赞：0)

[更好的阅读体验](https://www.cnblogs.com/StarRoadTang/p/14494421.html) 

## 题目链接

[点我跳转](https://codeforces.com/contest/1493/problem/D) 

## 题目大意

>给定一个长度为 $N$ 的序列 $A$
>
>有 $Q$ 次操作，每次操作给定两个数 $i$ , $X$，使得 $A[i] = A[i] \times X$ 
>
>问每次操作后整个序列的 $\gcd$ 为多少 （对 $10^9+7$ 取模）

## 解题思路

>显然 $\gcd$ 不满足同余定理 ( $\gcd(4,6) \bmod 3$ $!=$ $\gcd(4\bmod3,6)\bmod3$ )
>
>而 $A[i]$ 和 $X$ 最大值都不超过 $2\times10^5$ ， 所以可考虑质因子分解
>
>首先要知道对于一个数它的质因子个数是 $log$ 级别的
>
>有个贪心的证明方法
>
>>要让一个数的质因子最多，那这个数的质因子就应该尽可能小
>
>>那么就让他的质因子为 $2,3,5,7,11,13,...$
>
>>那么它就等于 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times...$ 
>
>>当乘到 $29$ 时，它已经大于 $6\times 10^9 $ 了，所以一个数的质因子个数是 $log$ 级别的
>
>于是可以用 $map$ 开个二维动态数组 $f[i][j]$，$f[i][j]$ 表示 $a[i]$ 的质因子 $j$ 的幂次
>
>这样使用的空间最多为 $(N + Q) \times log$
>
>对于一个质数 $P$ ，它对答案产生贡献的条件是： $A[1] $ ~ $A[N]$ 的质因子都包含 $P$
>
>也就是 $P$ 作为质因子一共出现了 $N$ 次，而它的贡献显然是出现过的最小幂次
>
>于是可以对每个质数 $p$ 开个 $set$ 
>
>当 $A[i]$ 的质因子包含 $p$ 时，往 $set[p]$ 里插入对应的幂次
>
>而当 $set[p].size() =n$ 时，$p$ 就会对答案产生 $p^{set[p].begin() - pre[p]}$ 贡献 
>
>其中 $pre[p]$ 表示上一次 $p$ 对答案产生的贡献，其初始值为 $0$

## AC_Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll pow_mod(ll x,ll n,ll mod)
{
	ll res = 1;
	while(n)
	{
		if(n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}

int prime[200010] , minprime[200010];

int euler(int n)
{
	int c = 0 , i , j;
	
	for(i = 2 ; i <= n ; i ++)
	{
		if(!minprime[i]) prime[++ c] = i , minprime[i] = i;
		
		for(j = 1 ; j <= c && i * prime[j] <= n ; j ++)
		{
			minprime[i * prime[j]] = prime[j];
			
			if(i % prime[j] == 0) break ;
		}
	}
	return c;
}

const ll mod = 1e9 + 7;
 
const int N = 3e5 + 10;

int n , q , I , X , a[N] , pre[N];

map<int , int>f[N];

multiset<int>se[N];

signed main()
{	
	ios::sync_with_stdio(false);
	
	cin.tie(0) , cout.tie(0);

	int sum = euler(200000);
	
	ll gcdd = 1;

	cin >> n >> q;

	for(int i = 1 ; i <= n ; i ++) cin >> a[i];

	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 2 ; j * j <= a[i] ; j ++) if(a[i] % j == 0)
		{
			int c = 0;

			while(a[i] % j == 0) a[i] /= j , c ++ ;

			f[i][j] = c;

			se[j].insert(c);
		}
		
		if(a[i] > 1) f[i][a[i]] = 1 , se[a[i]].insert(1);
	}

	for(int i = 1 ; i <= sum ; i ++)
	{
		int p = prime[i];

		if(se[p].size() == n)
		{
			auto j = *se[p].begin();

			gcdd = gcdd * pow_mod(1LL * p , 1LL * j , mod) % mod;

			pre[p] = j;
		}
	}
	
	while(q --)
	{
		cin >> I >> X;

		for(int j = 1 ; prime[j] * prime[j] <= X && j <= sum ; j ++) if(X % prime[j] == 0)
		{
			int c = 0 , p = prime[j];

			while(X % p == 0) X /= p , c ++ ;

			if(f[I].count(p))
			{
				auto it = se[p].find(f[I][p]);

				se[p].erase(it);
			}

			f[I][p] += c;
	
			se[p].insert(f[I][p]);

			if(se[p].size() == n)
			{
				auto it = *se[p].begin();

				gcdd = gcdd * pow_mod(p , it - pre[p] , mod) % mod;

				pre[p] = it;
			}
		}
		if(X > 1)
		{
			if(f[I].count(X))
			{
				auto it = se[X].find(f[I][X]);
				
				se[X].erase(it);
			}
			
			f[I][X] += 1;
			
			se[X].insert(f[I][X]);
			
			if(se[X].size() == n)
			{
				auto it = *se[X].begin();

				gcdd = gcdd * pow_mod(X , it - pre[X] , mod) % mod;

				pre[X] = it;

			}
		}
		cout << gcdd << '\n';
	}
	return 0;
}
```



---

## 作者：清烛 (赞：0)

提供一种在线的做法。

## 题意
给定 $n$ 个数 $a_{1\cdots n}$，进行 $q$ 次单点乘法操作，满足 $1\le n,q,a_i\le 2\times 10^5$，求每次操作完后 $\displaystyle\gcd_{i = 1}^na_i\bmod (10^9 + 7)$。

## 题解
我们知道 gcd 实际上就是所有的质因子取最小次数再乘起来，想到这里就很自然的去维护所有的质因子的次数。

对每种出现的质因子用一个数据结构来维护其次数，支持单点修改和最值查询，我这里使用的是动态开点线段树（避免普通线段树的空间浪费）（当然其他支持删除并求最值的数据结构也是可以的比如可删堆，`std::multiset` 等等），因为 $2\times 10^5$ 中素数的个数约为 $\dfrac{n}{\ln n}\approx 20113$ 个，而一个 $a_i$ 中最多有 $7$ 个互异质因子，所以大概估计一下发现不会炸。

然后就很简单了。一开始输入数列的时候直接把质因子 $p_j$ 对应的线段树在位置 $i$ 上加上对应的次数 $k$ 即可，注意这个线段树维护的是最小值（因为这样就可以方便的求 gcd），不难发现 gcd 中这个质因子贡献的值为 $p_j^{\min\lbrace k\rbrace}$，即树根的值。

维护 gcd 的时候乘上 $p_j^{k_0}$ 的逆元以先消掉质因子 $p_j$ 产生的贡献，修改完了再把 $p_j^{k_0'}$ 乘回去就可以了。

根据上述过程知复杂度为 $O(n\log^2n)$，可以通过本题

**需要注意的是线性筛素数时要处理一下每个数的最小质因子以加速质因数分解的过程，否则会 FST（TLE on 18）**

```cpp
#include <cstdio>
#include <cctype>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

typedef long long ll;
inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 2e5 + 5, mod = 1e9 + 7;
int a[maxn], n, q;
int p[maxn], isp[maxn], tot, minfact[maxn];

ll qpow(ll base, ll p = mod - 2)
{
    ll ret = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * base % mod;
        base = base * base % mod;
    }
    return ret;
}

void make_prime()
{
    FOR(i, 2, maxn - 2)
    {
        if (!isp[i])
            p[++tot] = i, minfact[i] = tot;
        for (int j = 1; i * p[j] < maxn; ++j)
        {
            isp[i * p[j]] = 1;
            minfact[i * p[j]] = j;//维护一个数的最小质因子以再在分解时避免遍历无用的质数
            if (i % p[j] == 0) break;
        }
    }
    return;
}

const int maxp = 2e7 + 5;//空间往不会炸的卡是绝对没错的
int cnt, lson[maxp], rson[maxp], val[maxp];//动态开点线段树
int root[maxn];

void modify(int &now, int l, int r, int x, int add)
{
    if (!now)
        now = ++cnt;
    if (l == r)
    {
        val[now] += add;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(lson[now], l, mid, x, add);
    else modify(rson[now], mid + 1, r, x, add);
    val[now] = min(val[lson[now]], val[rson[now]]);
    return;
}

int main()
{
    make_prime();
    n = read(), q = read();
    ll gcd = 1;
    FOR(i, 1, n)
    {
        int tmp = read();
        for (int j = minfact[tmp]; tmp > 1;)//j 的初始值要是最小质因子，避免无谓的循环
        {
            int k = 0;
            while (tmp > 1 && tmp % p[j] == 0)
                ++k, tmp /= p[j];
            gcd = gcd * qpow(qpow(p[j], val[root[j]])) % mod;//首先 gcd 删除 p[j] 的贡献
            modify(root[j], 1, n, i, k);
            gcd = gcd * qpow(p[j], val[root[j]]) % mod;//然后把贡献乘回去
            if (tmp > 1) j = minfact[tmp];//如果不这么写是会 FST 的
        }
    }
    while (q--)
    {
        int x = read(), v = read();
        for (int j = minfact[v]; v > 1;)
        {
            while (v > 1 && v % p[j]) ++j;
            int k = 0;
            while (v > 1 && v % p[j] == 0)
                ++k, v /= p[j];
            gcd = gcd * qpow(qpow(p[j], val[root[j]])) % mod;
            modify(root[j], 1, n, x, k);
            gcd = gcd * qpow(p[j], val[root[j]]) % mod;
            if (v > 1) j = minfact[v];
        }
        printf("%lld\n", gcd);
    }
    return 0;
}
```

当然使用一个 `map` 套一个 `multiset` 貌似更简单一些。其实精髓就是要动态维护每个质因子的出现次数并查询最小值。

---

## 作者：唐一文 (赞：0)

## Description

给定长度为 $n$ 的序列 $a$。

有 $q$ 次操作，每次给定 $i$ 和 $x$，将 $a_i$ 乘上 $x$。

每次操作后询问整个序列的最大公约数，对 $998244353$ 取模。

## Solution

首先筛出 $1\sim 2\cdot10^5$ 中的所有质数。

因为 $\gcd(a_{1},a_2,\dots,a_n)=\prod\limits_{i=1}^{cnt}\min_{j=1}^{n}num_{i,j}$

其中 $cnt$ 为质数个数，$num_{i,j}$ 表示 $a_i$ 质因数分解后 $pri_j$ 的个数。

可以开个桶 $t$ 和一个指针 $now$

$t_{i,j}$ 记录 $pri_i^j$ 被算了多少次，$now_i$ 指向当前最小且 $t_{i,now_i}<n$ 的下标。

若 $t_{i,now_i}=n$，则 $ans$ 乘上 $pri_i$，$now_i\leftarrow now_i+1$

每次操作，先把 $x$ 质因数分解，对于每个质数 $pri_j$

每次 $t_{j,num_{j,i}}\leftarrow t_{j,num_{j,i}}$，$num_{j,i}\leftarrow num_{j,i}+1$

因为 $a_i$ 每次的质因数只增不减，所以具有单调性，这样做显然正确。

~~讲得不太清楚，还是结合代码看吧~~

## Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
#define ll long long
using namespace std;
#define MAXP 17984
#define MAXN 200005
map<int,int>ton[MAXN];
int now[MAXP];
#define mod 1000000007
int n,q;
map<int,int>to[MAXP];
ll ans=1;
int pri[MAXP],cnt;
bool vis[MAXN];
int main(){
  //线性筛
  for(re int i=2;i<200001;++i){
    if(!vis[i])pri[cnt++]=i;
    for(re int j=0;j<cnt&&i*pri[j]<200001;++j){
      vis[i*pri[j]]=true;
      if(!(i%pri[j]))break;
    }
  }
  scanf("%d%d",&n,&q);
  for(re int j=1,x;j<=n;++j){
    scanf("%d",&x);
    //质因数分解
    for(re int i=0;i<MAXP&&pri[i]*pri[i]<=x;++i){
      while(!(x%pri[i])){
        x/=pri[i];
        ++ton[to[i][j]++][i];
        if(ton[now[i]][i]==n){//如果pri[i]的now[i]次方被算了n次，即在序列中的每个数都出现过一次
          ++now[i];//指向pri[i]的now[i]+1次方
          ans=ans*1ll*pri[i]%mod;
        }
      }
    }
    if(x>1){
      int i=lower_bound(pri,pri+cnt,x)-pri;
      ++ton[to[i][j]++][i];
      if(ton[now[i]][i]==n)ans=ans*1ll*pri[i]%mod,++now[i];
    }
  }
  for(re int _=0,j,x;_<q;++_){
    scanf("%d%d",&j,&x);
    for(re int i=0;i<MAXP&&pri[i]*pri[i]<=x;++i){
      while(!(x%pri[i])){
        ++ton[to[i][j]++][i],x/=pri[i];
        if(ton[now[i]][i]==n)ans=ans*1ll*pri[i]%mod,++now[i];
      }
    }
    if(x>1){
      int i=lower_bound(pri,pri+cnt,x)-pri;
      ++ton[to[i][j]++][i];
      if(ton[now[i]][i]==n)ans=ans*1ll*pri[i]%mod,++now[i];
    }
    printf("%lld\n",ans);
  }
}
```

---

## 作者：MyukiyoMekya (赞：0)

有一个结论，一堆数的 $\gcd$ 等于这些数每个质因子的指数取 $\min$ 然后乘起来。

假设这些数为 $a_i$ ，然后第 $i$ 个质数为 $p_i$ ，$a_j$ 有 $t_{i,j}$ 个 $p_i$ 因子，那么：
$$
\gcd a= \prod_i {p_i^{\min_jt_{i,j}}}
$$
于是，我们对每个质因数开一棵线段树维护单点加全局 $\min$ 就好了。（当然是动态开点）

至于怎么更新答案，我们每次给某个质因数的线段树里单点加后看一下这棵线段树的全局 $\min$ 有没有变，变了就直接快速幂计算答案要乘上多少就行了。

接下来来分析复杂度。$2\times 3\times 5\times 7\times 11\times 13>2\times 10^5$，所以对于一个数我们最多对 6 棵线段树进行单点加，所以时空复杂度都是 $\mathcal O(6\times (n+q)\log a_i)$。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ALL(x) (x).begin(),(x).end()
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
#define MP std::make_pair
#define dprintf(x...) std::fprintf(stderr,x)
const int MaxN=2e5+50;
const int MaxAi=2.1e7;
const int p=1e9+7;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int fpow(int a,int b)
{
	reg int res=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			res=res*a%p;
	return res;
}
#define lson ls[u]
#define rson rs[u]
signed ls[MaxAi],rs[MaxAi],a[MaxAi],rt[MaxN],ndn;
signed lst[MaxN];
inline void pushup(int u)
{
	a[u]=std::min(a[lson],a[rson]);
}
inline void modify(signed &u,int l,int r,int p,int k)
{
	if(!u)
		u=++ndn;
	if(l==r)
		return a[u]+=k,void();
	reg int mid=(l+r)>>1;
	p<=mid?modify(lson,l,mid,p,k):modify(rson,mid+1,r,p,k);
	pushup(u);
}
#define fi first
#define se second
inline void dived(std::vector<std::pair<int,int> > &a,int x)
{
	reg int maxi=std::sqrt(x);
	for(reg int i=2;i<=maxi;++i)
		if(!(x%i))
		{
			a.pb(MP(i,0));
			while(!(x%i))
				++a.back().se,x/=i;
		}
	if(x>1)
		a.pb(MP(x,1));
}
signed main(void)
{
	int n,q;read(n,q);
	reg int ans=1;
	reg int pos,x;
	for(int i=1;i<=n;++i)
	{
		read(x);
		std::vector<std::pair<int,int> > b;
		dived(b,x);
		for(auto j:b)
			modify(rt[j.fi],1,n,i,+j.se);
	}
	for(int i=1;i<=2e5;++i)
		lst[i]=a[rt[i]],(ans*=fpow(i,a[rt[i]]))%=p;
	dprintf("ans %lld\n",ans);
	while(q--)
	{
		read(pos,x);
		std::vector<std::pair<int,int> > b;
		dived(b,x);
		for(auto j:b)
		{
			modify(rt[j.fi],1,n,pos,+j.se);
			if(lst[j.fi]!=a[rt[j.fi]])
				(ans*=fpow(j.fi,a[rt[j.fi]]-lst[j.fi]))%=p,
				lst[j.fi]=a[rt[j.fi]];
		}
		write(ans),ln;
	}
	return 0;
}
```

~~但是我的分解质因数写的垃圾是n根号n的所以懂得都懂~~

---

## 作者：Warriors_Cat (赞：0)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1493D) & [CF 题面传送门](http://codeforces.com/problemset/problem/1493/D)。

题意：

* 给一个长度为 $n$ 的数列 $a$，有 $m$ 次操作。
* 每次操作 $a_x\leftarrow a_x \times y$，并求 $\gcd\limits_{i=1}^n\{a_i\}$。
* $n, m, a_i, x, y\le 2\times 10^5$。

算是一道比较套路的 STL 数据结构题？

---

### Solution：

发现最终的 $a_i$ 都会很大，用高精来维护显然是不现实的。

又注意到每次乘的数都很小，因此考虑维护质因数。

我们先线性筛出 $1$ 到 $2\times 10^5$ 内的所有素数，然后维护 $n$ 个 `multiset`，表示对于每个质因数，$a_i$ 分别都有它的多少幂次。

我们再维护 $n$ 个 `map`，`mp[i][j]` 表示 $a_i$ 这个数含有质因数 $j$ 的幂次。

我们先预处理出原序列 $a$，把它们该放的东西放进 `multiset` 里，并维护这 $n$ 个 `map`。每次操作，我们将所需要操作的数质因数分解，然后分别更新对应的 `multiset` 和 `map`，最后取所有 `multiset` 里的最小值，用它对应的质数来乘方就是答案了。

over，时间复杂度为 $O(n\sqrt n + n\log n)$。

---

### Code：

代码实现时要注意一下细节。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010, mod = 1000000007;
int n, q, a[N], pri[N], len, vis[N], rev[N], c[N], lst[N];
map <int, int> mp[N]; multiset <int> st[N];
inline int fpow(int x, int p){ int ans = 1; for(; p; p >>= 1, x = 1ll * x * x % mod) if(p & 1) ans = 1ll * ans * x % mod; return ans; }
inline void sieve(int n){
	rep(i, 2, n){
		if(!vis[i]) pri[++len] = i;
		for(int j = 1; j <= len && i * pri[j] <= n; ++j){
			vis[i * pri[j]] = 1;
		}
	} 
}
inline void work(int x, int y){
	for(int i = 1; i <= len; ++i){
		int k = pri[i];
		if(k * k > x) break;
		if(x % k) continue;
		int cnt = 0; mp[y][k] = 0;
		while(x % k == 0){
			x /= k;
			++cnt;
		}
		st[k].insert(mp[y][k] = cnt);
	}
	if(x > 1) ++mp[y][x], st[x].insert(1);
}
inline void mian(){
	n = read(); q = read(); sieve(200000);
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n) work(a[i], i);
	int ans = 1;
	rep(i, 1, len) if(st[pri[i]].size() == n){
		int k = pri[i], x = *st[k].begin();
		ans = 1ll * ans * fpow(k, x) % mod;
	}
	while(q--){
		int x = read(), y = read();
		rep(i, 1, len){
			int k = pri[i];
			if(k * k > y) break;
			if(y % k) continue;
			int num = 0, cnt = 0;
			if(st[k].size() == n) ans = 1ll * ans * fpow(fpow(k, *st[k].begin()), mod - 2) % mod;
			if(mp[x].find(k) != mp[x].end()) st[k].erase(st[k].find(mp[x][k]));
			while(y % k == 0) y /= k, ++cnt;
			mp[x][k] += cnt; st[k].insert(mp[x][k]);
			if(st[k].size() == n) ans = 1ll * ans * fpow(k, *st[k].begin()) % mod;
		}
		if(y > 1){
			if(st[y].size() == n) ans = 1ll * ans * fpow(fpow(y, *st[y].begin()), mod - 2) % mod;
			if(mp[x].find(y) != mp[x].end()) st[y].erase(st[y].find(mp[x][y]));
			mp[x][y] += 1; st[y].insert(mp[x][y]);
			if(st[y].size() == n) ans = 1ll * ans * fpow(y, *st[y].begin()) % mod;
		}
		printf("%d\n", ans);
	}
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```


---

