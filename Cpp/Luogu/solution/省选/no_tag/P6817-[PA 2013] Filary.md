# [PA 2013] Filary

## 题目描述

给定长度为 $n$ 的数列 $a$，从中选取 $k$ 个数使得这 $k$ 个数模 $m$ 相等，其中 $m\geq 2$。

求出 $k$ 的最大值，并在 $k$ 最大的前提下最大化 $m$。

## 说明/提示

$2\leq n\leq 10^5$，$1\leq a_i\leq 10^7$，保证有解，且不存在所有 $a_i$ 都相等的情况。

## 样例 #1

### 输入

```
6
7 4 10 8 7 1```

### 输出

```
5 3```

# 题解

## 作者：RiverHamster (赞：7)

取 $m = 2$，可以得到答案的一个下界是 $\lceil {n \over 2} \rceil$。

直接做很难处理，考虑随机一个值必选。根据答案下界，随机一次能得到最优解的概率大于 $1 \over 2$，因此随机 $20$ 次左右即可。

同余条件即 $m \mid x - y$，$x$ 已经通过随机固定，那么枚举每个数 $y$，将 $|x - y|$ 的所有 **素因子** 用桶维护，取最大出现次数。

但可能存在合数 $m$，使 $k$ 同样可以取到最大，可以考虑将两个对应 **$a_i$ 的位置完全相同** 的素因子 “合并”。

如果暴力维护，那么单次尝试 $\mathcal O(n \log^2 V)$，因为合法的素因子只有 $\mathcal O(\log V)$ 个，我们可以考虑给每**种** $a_i$ 赋随机权值，对每个素因子维护 xor-Hash 即可。

线性筛出每个数最小素因子，总复杂度 $\mathcal O(V + T\cdot n \log V)$，$T$ 为随机次数，$V$ 为值域。

注意考虑一个素因子重复出现的情况。

**[参考实现](https://www.cnblogs.com/RiverHamster/p/sol-lg6817.html)**

---

## 作者：Rorschachindark (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P6817)
# 思路
注：此题为与 @Reanap 共同探讨题目，部分参考了题解，主要 AC 思路为 @Reanap 提出。

首先我们需要知道，这个题直接做肯定是不好搞，肯定是随机化。（当我提出来的时候被自己否决了，@Reanap 也并未对我分析的正确概率提出反驳，从而走上了一条不归路，由此，@Reanap 是导致这一问题的直接罪犯（（（


## 方法1 - 92 pts
我们可以发现，当我们 $m=2$ 的时候，答案的下界就是 $\lceil\frac{n}{2}\rceil$。也就是说我们如果随机两个数 $x,y$，它们都在答案里面的概率为 $\frac{1}{4}$ 。我们考虑如何判断，因为这是随机算法，所以我们只需要提出一种正确性比较高的方法就行了。

不难发现的是，我们最终的 $m$ 一定是 $|a_x-a_y|$ 的因子。所以，我们可以直接排个序，然后如果当前点与上一个点在 $\bmod \ \ m$ 意义下相同，我们就可以在 $m$ 与 $|a_x-a_y|$ 取 $\gcd$。

随机数据情况下，随机操作 $20$ 次即可通过。但是这个题数据似乎卡了这种方法，所以只能做到 $92$ 分。

## $\texttt{Code1}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 100005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n,val[MAXN];

int tot,pri[13];
int Abs (int x){return x > 0 ? x : -x;}

#define ull unsigned long long

int gcd (int a,int b){return !b ? a : gcd (b,a % b);}

int allans,allpos;
void Work (int x,int y){
	int m = Abs (val[x] - val[y]);tot = 0;
	for (Int px = 2;px * px <= m;++ px){
		if (m % px == 0) pri[++ tot] = px;
		while (m % px == 0) m /= px;
	}
	if (m > 1) pri[++ tot] = m;
	int ans = 0,pos = 0;
	for (Int k = 1;k <= tot;++ k){
		int px = pri[k],now = x,res = 0,g = 0;
		for (Int i = 1;i <= n;++ i)
			if (val[i] % px == val[now] % px)
				res ++,g = gcd (g,Abs (val[i] - val[now])),now = i;
		if (res > ans) ans = res,pos = g;
		else if (res == ans) pos = max (pos,g);
	}
	if (ans > allans) allans = ans,allpos = pos;
	else if (ans == allans) allpos = max (allpos,pos);
}  

signed main(){
	srand (time(NULL));read (n);
	for (Int i = 1;i <= n;++ i) read (val[i]);
	sort (val + 1,val + n + 1);
	for (Int i = 1;i <= 100;++ i){
		int x = rand() % n + 1,y = rand() % n + 1;
		while (val[x] == val[y]) x = rand() % n + 1,y = rand() % n + 1;
		Work (x,y);
	}
	write (allans),putchar (' '),write (allpos),putchar ('\n');
	return 0;
}
```

## 方法2 - 86 pts
我们还是随机 $x,y$，我们不难发现我们只需要对于 $|a_x-a_y|$ 每一个质因数找到最大指数，然后我们找到最大指数。问题就是如何合并不同质因数，我们可以直接 hash 一波，对于每一个质因数找到可行选的数，然后看是否存在交集即可。

不知道为什么，分还没有上一种高。

## $\texttt{Code2}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 100005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n,val[MAXN];

int tot,pri[13],pw[13];
int Abs (int x){return x > 0 ? x : -x;}

#define ull unsigned long long

#define MAXM 10000005
int tong[MAXM];
int Askfor (int m){
	for (Int i = 1;i <= n;++ i) tong[val[i] % m] ++;
	int ans = 0;for (Int i = 1;i <= n;++ i) ans = max (ans,tong[val[i] % m]);
	for (Int i = 1;i <= n;++ i) tong[val[i] % m] = 0;
	return ans; 
}

vector <ull> G[15]; 

#define seed 1000000007
ull fpw[MAXN];
void Askforpos (vector <ull> &pos,int m){
	for (Int i = 1;i <= n;++ i) tong[val[i] % m] ++;
	int ans = 0;vector <int> tmp;
	for (Int i = 1;i <= n;++ i){
		if (tong[val[i] % m] > ans) tmp.clear(),tmp.push_back (val[i] % m);
		else if (tong[val[i] % m] == ans) tmp.push_back (val[i] % m);
	} 
	sort (tmp.begin(),tmp.end()),unique (tmp.begin(),tmp.end());
	for (Int u : tmp){
		ull hashnow = 0;
		for (Int i = 1;i <= n;++ i) if (val[i] % m == u) hashnow += fpw[i];
		pos.push_back (hashnow);
	}
	for (Int i = 1;i <= n;++ i) tong[val[i] % m] = 0;
}

int allans,allpos;
int mxp[16],getp[16];

map <ull,int> mp;

void Work (int x,int y){
	int m = Abs (val[x] - val[y]);tot = 0;
	for (Int px = 2;px * px <= m;++ px){
		if (m % px == 0){
			pri[++ tot] = px,pw[tot] = 0;
			while (m % px == 0) m /= px,pw[tot] ++;
		}
	}
	if (m > 1) pri[++ tot] = m,pw[tot] = 1;
	for (Int i = 1;i <= tot;++ i) G[i].clear();int mxans = 0;
	for (Int k = 1;k <= tot;++ k) mxans = max (mxans,Askfor (pri[k]));
	for (Int k = 1;k <= tot;++ k){
		if (Askfor (pri[k]) != mxans) continue;
		int fir = Askfor (pri[k]),now = pri[k];mxp[k] = 1;
		while (mxp[k] < pw[k] && Askfor (now * pri[k]) == fir) now *= pri[k],mxp[k] ++;
		getp[k] = now,Askforpos (G[k],now);
	}
	mp.clear();
	for (Int k = 1;k <= tot;++ k)
		for (ull Hash : G[k]) 
			if (mp.find (Hash) != mp.end()) mp[Hash] *= getp[k];
			else mp[Hash] = getp[k];
	int mxind = 0;
	for (Int k = 1;k <= tot;++ k)
		for (ull Hash : G[k]) mxind = max (mxind,mp[Hash]);
	if (mxans > allans) allans = mxans,allpos = mxind;
	else if (mxans == allans) allpos = max (allpos,mxind);
}  

signed main(){
	srand (time(NULL));read (n);
	for (Int i = 1;i <= n;++ i) read (val[i]);
	sort (val + 1,val + n + 1);fpw[0] = 1;
	for (Int i = 1;i <= n;++ i) fpw[i] = fpw[i - 1] * seed;
	for (Int i = 1;i <= 100;++ i){
		int x = rand() % n + 1,y = rand() % n + 1;
		while (val[x] == val[y]) x = rand() % n + 1,y = rand() % n + 1;
		Work (x,y);
	}
	write (allans),putchar (' '),write (allpos),putchar ('\n');
	return 0;
}
```

## 方法3 - 100 pts
我们发现方法 2 似乎实在没有办法继续提高正确率，我们看到方法 1。我们不考虑随机枚举 $x,y$，我们只枚举 $x$。然后我们直接暴力枚举 $y$，找到出现次数最多的质因数，然后直接对这个按方法1的方法继续做。

不知道为什么我只能得到 $98$，所以我就把方法1、 3的代码结合了一下，终于卡过去了。

# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 100005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n,val[MAXN];

int Abs (int x){return x > 0 ? x : -x;}
int gcd (int a,int b){return !b ? a : gcd (b,a % b);}

#define MAXM 10000005
bool vis[MAXM];
int cnt,lowp[MAXM],prime[MAXM];

void Euler (int up){
	lowp[1] = 1;
	for (Int i = 2;i <= up;++ i){
		if (!vis[i]) prime[++ cnt] = i,lowp[i] = i;
		for (Int j = 1;j <= cnt && i * prime[j] <= up;++ j){
			vis[i * prime[j]] = 1,lowp[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

int tong[MAXM];

int allans,allpos;
void Work (int x){
	int mx = 0;
	for (Int i = 1;i <= n;++ i){
		int now = Abs (val[x] - val[i]);
		if (now == 0) continue;
		while (now > 1){
			tong[lowp[now]] ++;int las = lowp[now];
			if (tong[lowp[now]] > tong[mx]) mx = lowp[now];
			else if (tong[lowp[now]] == tong[mx]) mx = max (mx,lowp[now]);
			while (now % las == 0) now /= las;
		}
	} 
	int res = 0,g = 0,now = x;
	for (Int i = 1;i <= n;++ i){
		if (val[i] % mx == val[now] % mx)
			res ++,g = gcd (g,Abs (val[now] - val[i])),now = i;
		int now = Abs (val[x] - val[i]);
		if (now == 0) continue;
		while (now > 1){
			tong[lowp[now]] = 0;int las = lowp[now];
			while (now % las == 0) now /= las;
		}
	}
	if (res > allans) allans = res,allpos = g;
	else if (res == allans) allpos = max (allpos,g);
}  

int tot,pri[13];
void Work1 (int x,int y){
	int m = Abs (val[x] - val[y]);tot = 0;
	for (Int px = 2;px * px <= m;++ px){
		if (m % px == 0) pri[++ tot] = px;
		while (m % px == 0) m /= px;
	}
	if (m > 1) pri[++ tot] = m;
	int ans = 0,pos = 0;
	for (Int k = 1;k <= tot;++ k){
		int px = pri[k],now = x,res = 0,g = 0;
		for (Int i = 1;i <= n;++ i)
			if (val[i] % px == val[now] % px)
				res ++,g = gcd (g,Abs (val[i] - val[now])),now = i;
		if (res > ans) ans = res,pos = g;
		else if (res == ans) pos = max (pos,g);
	}
	if (ans > allans) allans = ans,allpos = pos;
	else if (ans == allans) allpos = max (allpos,pos);
}  

signed main(){
	srand (20050913);read (n);
	for (Int i = 1;i <= n;++ i) read (val[i]);
	sort (val + 1,val + n + 1);Euler (1e7);
	for (Int i = 1;i <= 20;++ i){
		int x = rand() % n + 1;
		Work (x);
	}
	for (Int i = 1;i <= 20;++ i){
		int x = rand() % n + 1,y = rand() % n + 1;
		Work1 (x,y);
	} 
	write (allans),putchar (' '),write (allpos),putchar ('\n');
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定一个长度为 $n$ 的序列 $a$，你需要选出 $k$ 个数使得它们在模 $m$ 意义下相等。要求 $m\geq 2$。

求出以 $k$ 为第一关键字，$m$ 为第二关键字的 $k,m$ 最大值。

$2\leq n\leq 10^5,1\leq a_i\leq 10^7$。

## 思路

安利一篇别人写的博客 [贪心与随机化](https://www.cnblogs.com/SuporShoop/p/18514573)，感觉讲的很详细。

> 引理：存在一个 $k$ 使得 $k\geq\lceil\frac{n}{2}\rceil$。

取 $m=2$ 即可，根据鸽巢原理易证。

然后我们就得到一个推论：

> 对于任意一个 $a_i$，$a_i$ 位于选出的数内的概率大于 $\frac{1}{2}$。

考虑给出的这个结论有什么用。不妨随机选取一个 $a_i$，然后令 $b_j\leftarrow |a_i-a_j|$。那么相当于我们要选出 $j$ 个数，使得它们的 $\gcd$ 大于 $1$。

注意到枚举 $\gcd$ 是无法接受的，不过不妨记录 $\gcd$ 的质因子。具体地，我们可以将每个 $b_i$ 分解质因数，用一个 `map` 统计所有质因子出现次数即可。最后我们选出出现次数最多的质因子，将包含这些质因子的数取 $\gcd$ 即可。

至于分解质因数的方法，如果用筛法预处理会 MLE，如果暴力会 TLE。一种比较好的方法是预先处理出每一个数的任意一个质因子，这样就节省了枚举的时间。

单次正确率下界为 $\frac{1}{2}$，运行 $k$ 次可以得到 $1-(\frac{1}{2})^k=\frac{2^k-1}{2^k}$ 的正确率。

## 代码

**实现的时候注意随机的 $a_i$ 可能相同。**

实现用的是卡时，所以抢到了最劣解。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, M = 1e7 + 5;
int n, a[N], b[N], pri[M], tot, f[M];
bool vis[M];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void sieve(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]) pri[++tot] = i;
        for(int j=1;j<=tot&&1ll*i*pri[j]<=n;j++){
            vis[i * pri[j]] = 1;
            if(!(i % pri[j])) break;
        }
    }
    for(int i=1;i<=tot;i++){
        for(int j=pri[i];j<=n;j+=pri[i]) f[j] = pri[i];
    }
}

pair<int,int> solve(){
    int pos = rnd() % n + 1;
    map<int,int> mp;
    for(int i=1;i<=n;i++){
        b[i] = abs(a[i] - a[pos]);
        int c = b[i];
        while(c > 1){
            int d = f[c]; mp[d]++;
            while(!(c % d)) c /= d;
        }
    }
    int mx = 0, ans = 0;
    for(auto [x, y] : mp) mx = max(mx, y);
    for(auto [x, y] : mp){
        if(y == mx){
            int ret = 0;
            for(int i=1;i<=n;i++){
                if(!(b[i] % x)) ret = __gcd(ret, b[i]);
            }
            ans = max(ans, ret);
        }
    }
    return {mx + count(b + 1, b + n + 1, 0), ans};
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sieve(*max_element(a + 1, a + n + 1));
    pair<int,int> res(0, 0);
    while((double)clock() / CLOCKS_PER_SEC < 1.75) res = max(res, solve());
    cout << res.first << ' ' << res.second << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6817)。

## 思路

其他题解的实现看起来很麻烦，这里给出一个简易的实现。

首先钦定 $m=2$，此时余数只能是 $1$ 或 $0$，那么一定有一种数的出现次数超过一半，不妨考虑随机化，每次随机出一个位置 $x$，该位置处于答案的概率大于 $50\%$，假设答案集合为 $S$，那么 $\forall i \in S$，$m\mid (a_i-a_x)$，而我们要求出最大的 $m$，因此 $m=\gcd_{i\in S}(a_i-a_x)$，考虑对每个质因子分类讨论，先求出那些素数使得 $p\mid (a_i-a_x)$ 的 $i$ 的个数最多，然后依 $p$ 求出 $m$，可以做到 $\mathcal O(tn\log V+V)$，$t$ 是随机组数，$V$ 是值域。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+7,V=1e7+2;
int n;
int a[Maxn];

bitset<V>isp;
vector<int>prm;
int lpf[V],id[V];

mt19937 rnd(19260817);
int ans1,ans2,nowk;

inline void init(int N){
    for(int i=2;i<=N;i++){
        if(!isp.test(i)) prm.emplace_back(i),lpf[i]=i;
        for(auto j:prm){
            const int t=i*j;if(t>N) break;
            isp.set(t);lpf[t]=j;if(!(i%j)) break;
        }
    }
}
inline void work(){
    map<int,int>mp2;
    int x=rnd()%n+1,g=0,te=0;
    for(int i=1;i<=n;i++){
        int y=abs(a[i]-a[x]);
        if(!y) {g++;continue;}
        map<int,int>mp1;
        while(y>1) {mp1[lpf[y]]=1;y/=lpf[y];}
        for(auto j:mp1) mp2[j.first]++;
    }
    int ret=0;
    for(auto [i,j]:mp2) if(j>ret) ret=j;
    for(auto [i,j]:mp2)
        if(j==ret){
            int wh=0;
            for(int k=1;k<=n;k++)
                if(abs(a[k]-a[x])%i==0) wh=__gcd(wh,abs(a[k]-a[x]));
            te=max(te,wh);
        }
    if(ret+g>ans1) ans1=ret+g,nowk=x,ans2=te;
    if(ret+g==ans1) ans2=max(ans2,te);
}

int main(){

    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    init(1e7);
    for(int t=1;t<=20;t++) work();

    printf("%d %d",ans1,ans2);

    system("pause");
    return 0;
}
```

---

