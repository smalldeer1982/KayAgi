# You

## 题目描述

给你一个 $n$ 个点的树，可以通过以下方式生成一个长度为 $n$ 的序列 $a$：

+ 每次在树中选取一个**未被标记**的节点 $u$，令 $a_u$ 等于与节点 $u$ 相邻的**未被标记**的节点个数，然后将节点 $u$ **标记**。

对于每一个整数 $k\in[1,n]$，输出符合以下条件的序列 $a$ 的数量模 $998244353$ 的值：

+ 序列 $a$ 可以由给定的树通过上述方式生成；
+ $\gcd(a_1,a_2,\cdots,a_n)=k$。

## 说明/提示

对于 $100\%$ 的数据，$1\leq t\leq 10^4,2\leq n\leq 10^5,\sum n \leq 3\times10^5$。

## 样例 #1

### 输入

```
2
3
2 1
1 3
2
1 2```

### 输出

```
3 1 0
2 0```

# 题解

## 作者：遮云壑 (赞：12)

## Description
翻译已经给的很清楚了。。

如果题意有不清楚的，[出门左转](https://www.luogu.com.cn/problem/CF1554E)。
## solution
这题是个性质题，需要我们静下心来慢慢推。~~慢慢玩数据~~ 。
#### 性质一：所有 $a_i$ 的和为 $n-1$ 。
这挺容易理解，相当于每次删掉一个点和与其相连的边，边数即为 $a_i$ ，总共 $n-1$ 条边，所以 $a_i$ 的和为 $n-1$。

先放这儿，过会儿用。
#### 性质二：叶子节点所造成的 $a_i$ 值为0或1
叶子节点至于父节点相连，度数为1，删在父节点之前则 $a_i=1 $，删在父节点之后则 $a_i=0$ 。
然而，只要所有的 $a_i$ 里存在一个1，那么 $gcd(a_1...a_n)=1$，所有 $a_i$ 的值一定是 $gcd(a_1...a_n)$ 的倍数，这就引导我们先求 $k=2~n$ 的请况，最后总请况减去其他的答案就是 $k=1$ 的答案。
#### 性质二推广：所有点的 $a_i$ 一定只有两种情况
对于只有叶子儿子的节点，那么它的 $a_i$ 值已经确定为0，所以这个节点能决定的边只有与它父亲相连的那条边是否作为它的 $a_i$ 的贡献，所以它的两种 $a_i$ 相差1。其实，对于所有点，它儿子的情况都会被确定，所以每一个点都是有两种选择。

#### 性质二再推广：对于 $k=2...n$ ,答案只可能为0或1
对于每一个 $k$，我们要保证每一个 $a_i$ 一定是 $k$ 的倍数，那么大体的思路就出来了，枚举 $k$ ，然后深搜，从叶子节点向父亲递归，每一次保证 $a_i$ 为$k$的倍数，因为每一次 $a_i$ 的两种决策只会相差1，所以不会同时为 $k$ 的倍数。每个点的合法情况至多一种，总情况也至多一种。如果都不是 $k$ 的倍数，那么退出，$k$ 在此时肯定不成立。如果搜索结束所有的 $a_i$ 都是 $k$ 的倍数，那么这就是一种且是唯一一种合法的情况。
#### 性质三：合法的 $k$ 一定是 $n-1$ 的约数
敲黑板敲黑板，这直接影响到你是AC还是TLE 。

其实挺好证，由性质一我们得到所有 $a_i$ 的和为 $n-1$ ，而要使当前 $k$ 合法，$a_i$ 一定是 $k$ 的倍数，所以合法的 $k$ 一定是 $n-1$ 的约数。我们只要枚举 $n-1$ 的约数就可以了。

当然，机房大佬好像说只要枚举质因数就可以了，可惜本蒟蒻不会证。。但是枚举
约数当然也不会T。如果有大佬能证明的欢迎私信或留言qwq。
#### 性质四：所有情况有 $2^{n-1}$ 个
由性质一推一下，每条边可以算在它所连接的两个点的任意一个点的 $a_i$ 贡献，共 $n-1$ 条边，所以$2^{n-1}$种情况。
### 思路总结
1.枚举 $n-1$ 的约数（质因数？）$k$ ，然后dfs，从叶子节点向上递归，判是否有合法的 $a_i$ 值，如果没有，立刻退出, $ans_k=0$，如果搜完了， $ans_k=1$ 。

2.总情况 $2^{n-1}$ 个,减去$ans_2...ans_n$ 得到 $ans_1$ 。

3.呃，没了，输出吧。

## code
[出门右转](https://codeforces.com/contest/1554/submission/134049653)

---

## 作者：do_while_true (赞：12)

问题可以转化成给每个边定向，$a_i$ 变成了 $i$ 点的入度。

首先考虑定向方案与合法的 $a$ 的双射：每一个定向方式都能唯一确定一个 $a$；依次考虑叶子的 $a$，就能确定叶子与其父亲的边的定向方式，之后即可将叶子删掉。不断迭代即可得到定向方案，该定向方案唯一确定的也是原先的 $a$。所以定向方案可以与合法的 $a$ 组成一组双射。

然后考虑所有的不同的 $a$ 都能被一个删点方案生成：因为给每个点定向必然有个点的入度为 $0$，从这个点开始删，不断迭代，即可得到一个能够生成这个 $a$ 的合法的删点方案。

所以答案的总和为 $2^{n-1}$．

入度的总数为 $n-1$，所以一定只有 $n-1$ 的因数答案才不为 $0$。

考虑如果 $k>1$，怎样判断答案是不是 $0$？叶子是可以直接确定边要往上的，因为不能出现入度为 $1$，这样可以把叶子删去，删去叶子之后的叶子，挂着它的边也能定向，然后这个叶子也可以删去...这样不断做拓扑排序，即可以构造出一个方案，看这个方案满不满足条件即可。

注意到这个方案数唯一的，所以 $k>1$ 时直接拓扑排序来判断即可。

直接这么做时间复杂度是 $\mathcal{O}(n\sqrt n)$，有一个显著的优化是如果只判素因子就行，再把判素因子得到的 $\gcd$ 的 ans 加上 $1$。

$k=1$ 的答案的话，用答案的总数 $2^{n-1}$ 减去其它所有的答案就行。复杂度是 $\mathcal{O}(n \omega (n))$，$\omega (n)$ 是 $n$ 的素因子个数。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
typedef long long ll;
const ll mod = 998244353;
ll qpow(ll x, ll y) {
	ll sumq = 1;
	while(y) {
		if(y & 1) sumq = sumq * x % mod;
		 x = x * x % mod;
		 y >>= 1;
	}return sumq;
}
#define int long long 
const int N = 1000010;
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int n, head[N], ent, ans[N], a[N], in[N], in_[N], b[N];
bool vis[N];
struct Edge {
	int to, next;
}e[N << 1];
inline void add(int x, int y) {
	e[++ent].to = y; e[ent].next = head[x]; head[x] = ent;
}
std::queue<int>q;
int check(int x) {
	for(int i = 1; i <= n; ++i) b[i] = a[i] = 0, in[i] = in_[i], vis[i] = 0;
	for(int i = 1; i <= n; ++i)
		if(in[i] == 1) {
			q.push(i);
		}
	while(!q.empty()) {
		int y = q.front();q.pop(); vis[y] = 1;
		for(int i = head[y]; i;i = e[i].next) {
			int v = e[i].to;
			if(vis[v] == 1) continue ;
			if(a[y] == 0) ++a[v], a[v] %= x, ++b[v];
			else ++a[y], a[y] %= x, ++b[y];
			--in[v];
			if(in[v] == 1) {
				q.push(v);
			}
		}
	}
	int g = b[1];
	for(int i = 2; i <= n; ++i) g = gcd(g, b[i]);
	return g;
}
void solve() {
	read(n);
	for(int i = 1; i <= n; ++i) ans[i] = in_[i] = 0, head[i] = 0;
	ent = 0;
	for(int i = 1, u, v; i < n; ++i) read(u), read(v), add(u, v), add(v, u), in_[u]++, in_[v]++;
	int m = n-1;
	for(int i = 1; i * i <= m; ++i)
		if(m % i == 0) {
			int t = check(i);
			if(t % i == 0) ans[t] = 1;
			while(i != 1 && m % i == 0) m /= i;
		}
	if(m > 1) {
		int t = check(m);
		if(t % m == 0) ans[t] = 1;
	}
	ans[1] = qpow(2, n-1);
	for(int i = 2; i <= n; ++i) ans[1] -= ans[i];
	for(int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	puts("");
}
signed main() {
	int T; read(T);
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Demoe (赞：12)

### [题目传送门](https://www.luogu.com.cn/problem/CF1554E)

## $\text{Description}$

- 对于一棵有 $n$ 个节点的树，做 $n$ 次操作。

- 每次操作删去一个点 $i$，$a_i$ 为此时与 $a_i$ 相邻的未被删去的点数量。

- 对于所有不同的 $\{a_n\}$，令 $k=\gcd(a_1,...,a_n)$。

- 求当 $k=1,...,n$ 时的 $\{a_n\}$ 方案数。

## $\text{Solution}$

考虑到相当于给边定向，对于每条边指向的点 $i$，让它 $a_i+1\to a_i$。

则易知总共有 $2^{n-1}$ 个 $\{a_n\}$。

考虑到 $k=1$ 的情况不太好算。

我们考虑 $k>1$ 的情况。

这里有一个特别重要的性质。

我们令 $f_x$ 为 $x\mid k$ 时的答案和，当 $x>1$ 时有 $f_x\le 1$。

我们简单证一下。

首先 $k>1$ 时叶子肯定是要最后删的，这样它的 $a_i=0$，否则 $a_i=1$ 与 $k>1$ 矛盾。

然后与叶子节点相连的点就必须先删掉，也就是与叶子节点相连的边就定向了。

然后我们依次向上考虑 $k$ 的限制，发现所有边都一定会被定向。

因此 $f_x\le 1$。

同时在这个证明过程中，由于 $f_x\le 1$，我们也能求出那个 $ans_k=1$ 的 $k$。

```cpp
inline int dfs(int x,int fa){
	if(!flag) return 0;
	int tot=es[x].size();
	for(re i=0;i<es[x].size();++i)
		if(es[x][i]!=fa) tot-=dfs(es[x][i],x);
	if(tot%k&&(tot-1)%k) flag=0;
	if(tot%k==0){ans=gcd(ans,tot);return 1;}
	else{ans=gcd(ans,tot-1);return 0;}
}
```

由于 $\sum_{i=1}^na_i=n-1$，因此 $k\mid n-1$

所以我们把每个 $n-1$ 的因子代到上面的 $k$ 就行啦。

时间复杂度 $O(n\times d(n-1))$，其中 $d(n-1)$ 表示 $n-1$ 的因子个数，已经比官方题解优秀那么一点点了（官方题解 $O(n\times d(n-1)+n\log n)$）。（

然而这个显然还可以优化。（

由于 $f_x\le 1$，而我们做一次 dfs 时直接可以求出那个满足 $x\mid k$ 且 $ans_k=1$ 的那个 $k$（如果 $f_x\neq 0$）。

那么我们可以直接找 $n-1$ 的素因子进行 dfs，避免了大量重复的计算。

时间复杂度 $O(n\times \omega(n-1))$，其中 $\omega(n-1)$ 表示 $n-1$ 的素因子个数。

## $\text{Code}$

```cpp
const int N=1e5+5,mod=998244353;
int T,n,a[N],ans,k;
bool flag;
vector<int> es[N];

inline int pw(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=1ll*sum*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return sum;
}

inline int gcd(int x,int y){return y==0?x:gcd(y,x%y);}

inline int dfs(int x,int fa){
	if(!flag) return 0;
	int tot=es[x].size();
	for(re i=0;i<es[x].size();++i)
		if(es[x][i]!=fa) tot-=dfs(es[x][i],x);
	if(tot%k&&(tot-1)%k) flag=0;
	if(tot%k==0){ans=gcd(ans,tot);return 1;}
	else{ans=gcd(ans,tot-1);return 0;}
}

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(T);
	while(T--){
		rd(n);
		for(int i=1,x,y;i<n;++i){
			rd(x);rd(y);es[x].pb(y);es[y].pb(x);
		}
		int maxn=n-1;
		for(re i=2;i*i<=maxn;++i)
			if(maxn%i==0){
				flag=1;ans=0;k=i;dfs(1,0);
				if(flag) a[ans]=1;
				while(maxn%i==0) maxn/=i;
			}
		if(maxn>1){
			flag=1;ans=0;k=maxn;dfs(1,0);
			if(flag) a[ans]=1;
		}
		a[1]=pw(2,n-1);
		for(re i=2;i<=n;++i) a[1]=(a[1]-a[i]+mod)%mod;
		for(re i=1;i<=n;++i) wr(a[i]),putchar(' ');puts("");
		for(re i=1;i<=n;++i) a[i]=0,es[i].clear();
	}
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：OMG_wc (赞：6)

~~感觉自己智商被碾压~~

题意：

是给你一棵树，按任意顺序一个个地从树上删点，记 $a_i$ 为删到点 $i$ 时，和 $i$ 相邻的顶点中没被删除的顶点个数，这样可以得到一个序列 $\{a_i\}$ 。

在不同的删点顺序可以得到的 **不同** 序列中，回答对每个 $k \in [1,n]$ ，$\gcd\{a_i\}=k$ 的序列数量，答案对 $998244353$ 取模。

解析：

删点的方式一共有 $n!$ 种 ，但最后得出的不同序列数目只有 $2^{n-1}$ 种，原因如下：

考虑每条边 $ \langle u,v \rangle $  ，可以发现一条边会对数列产生 $1$ 的贡献（还能得出 $\sum\ a_i=n-1$ ），具体这个 $1$ 给 $u$ 还是 $v$ 取决于谁先删谁后删。先被删除的点会从这条边中得到 $1$ 的贡献，而后被删除的点就不会从这条边得到贡献。

设 $f_i$ 为 GCD 为 $i$ 的倍数时的答案，那么最终答案 $g_i=f_i-\sum\limits_{j>i,i\mid j}g_j$，可以由简单的容斥得到。

显然 $f_1=2^{n-1}$，而当  $i\nmid n-1$ 时 $f_i=0$，不需要再去计算了。

对于 $i>1 $ 且 $i \mid n-1$ 时，可以证明方案总是唯一的（或者无解），只需从叶子开始自底向上考虑每条边的贡献是给自己，还是给父亲。

具体来说，计算出当前结点 $u$ 能从儿子这条边中获得的贡献为 $cnt$，分成三种情况：

- $i\mid cnt$ ，此时父边贡献给父亲
-  $i\mid cnt+1$ ，此时父边贡献给自己（注意根节点没有父边，贡献不能给自己）
- 此时一定无解

这样遍历整棵树就能确定答案是否存在，若存在也显然唯一。

总时间复杂度 $O(n(\log n+\sigma_{0}(n-1))$，参考代码如下:

```cpp
vector<int> G[N];
LL f[N];

int ok;
int dfs(int u, int fa, int k) {
    int cnt = 0;
    for (auto v : G[u]) {
        if (v == fa) continue;
        cnt += dfs(v, u, k);
    }
    if (cnt % k == 0) return 1;
    if ((cnt + 1) % k == 0) return 0;
    ok = 0;
    return 0;
}
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            f[i] = 0;
        }
        f[1] = 1;
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
            f[1] = f[1] * 2 % mod;
        }
        for (int i = 2; i < n; i++) {
            if ((n - 1) % i == 0) {
                ok = 1;
                f[i] = dfs(1, 0, i) && ok;
            }
        }
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + i; j <= n - 1; j += i) {
                f[i] -= f[j];
            }
            f[i] = (f[i] % mod + mod) % mod;
        }
        for (int i = 1; i <= n; i++) {
            printf("%lld%c", f[i], " \n"[i == n]);
        }
    }
    return 0;
}
```







---

## 作者：Light_snow (赞：3)

本文同步自[CF1554E You](https://www.cnblogs.com/dixiao/p/15086560.html)。

考虑到删点操作的实质是指认边的方向。

由于这是一棵树，所以有很好的性质。

我们完全可以以此从树叶开始，往上拓扑进行，按照对某个数的取膜的大小来进行操作。

由此可知，除了 1 以外,任意 $2 \leq k$ 都有可能，且只有一种方案。
那么如何判断方案是当下的问题。

考虑到我们的的操作过程，我们发现其实在每个质数的同余系下，有且只有一个答案可能存在。

又由于 $m = n - 1 = \sum a[i]$，那么我们把 $m$ 质数分解，对这些质数的同余系进行讨论就好。

同时总方案数为 $2 ^ {n - 1}$，依照容斥原理，那么 $k = 1$ 时答案为 $2 ^ {n - 1} - \sum_{i = 2} f[i]$。


```
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
#define N 100005
#define mod 998244353 

ll T;
ll n;
ll head[N],cnt;
ll in[N],iin[N];
ll a[N],b[N];
ll f[N];


struct P{
	int to,next;
}e[N << 1];

inline void clear(){
	for(int i = 1;i <= n;++i)
	head[i] = in[i] = iin[i] = a[i] = b[i] = 0,f[i] = 0;
	for(int i = 1;i <= cnt;++i)
	e[i].to = e[i].next = 0;
	cnt = 0;

}

inline void add(int x,int y){
	e[++cnt].to = y;
	e[cnt].next = head[x];
	head[x] = cnt;
	in[y] ++ ;
}


inline ll qpow(ll a,ll b){
	ll ans = 1;
	while(b){
		if(b & 1)ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

std::queue<int>QWQ;

ll vis[N];

inline ll gcd(ll x,ll y){
	return (x == 0) ? y : gcd(y % x,x);
}

inline ll find(ll x){//找出在该同余系下的答案。 
	for(int i = 1;i <= n;++i)
	iin[i] = in[i],a[i] = b[i] = 0,vis[i] = 0;
	for(int i = 1;i <= n;++i)
	if(iin[i] == 1)//成为叶子
	QWQ.push(i);
	while(QWQ.size()){
		int u = QWQ.front();
		QWQ.pop();
		vis[u] = 1;
		for(int i = head[u];i;i = e[i].next){
			int v = e[i].to;
			if(vis[v])continue;
			if(a[u] == 0)a[v] = (a[v] + 1) % x,b[v] ++ ;else a[u] = (a[u] + 1) % x,b[u] ++; 
			iin[v] -- ;
			if(iin[v] == 1)
			QWQ.push(v);
		} 
	}
	ll ans = b[1];
	for(int i = 2;i <= n;++i)
	ans = gcd(ans,b[i]);	
	return ans; 
}

int main(){
	scanf("%lld",&T);
	while(T -- ){
		scanf("%lld",&n);
		clear();
		for(int i = 1;i <= n - 1;++i){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			add(x,y);
			add(y,x);
		}
		ll m = n - 1;
		for(int i = 2;i * i <= m;++i){
			if(m % i == 0){
				ll si = find(i);
				if(si % i == 0)
				f[si] = 1 ;
				while(m % i == 0 && i != 1)m /= i;
			}
		}
		if(m > 1){
			ll si = find(m);
			if(si % m == 0)
			f[si] = 1 ;			
		}
		f[1] = (f[1] + qpow(2,n - 1)) % mod;
		for(int i = 2;i <= n;++i)
		f[1] = (f[1] - f[i] + mod) % mod;
		for(int i = 1;i <= n;++i)
		std::cout<<f[i]<<" ";
		puts("");
	}
}
```

---

## 作者：wwlw (赞：2)

[Link](https://codeforces.com/problemset/problem/1554/E)
----------------

### E. You
给定一棵树。每次删去一个点，这个点权值 $a_u$ 定为与它相连且未删去的点的个数。对每个 $k\in[1,n]$ ，求 $gcd(a_1,a_2,\dots,a_n)=k$ 的序列个数，方案不同当且仅当 $\{a_n\}$ 不同。

首先要把删点转换成给边定向，也就是说删去一个点就把与它相连的边指向它，权值就变成了入度。有 $n-1$ 条边，就共有 $2^{n-1}$ 种序列。先考虑 $k\geq 2$ 的答案。由于 $k \geq 2$，所以对于叶子结点的边，只能指向父亲。那么删去这些叶子结点后，新的叶子结点的入度就一定不为 0 了，当前入度记为 $a_u$，儿子都已经定了，只有指向父亲的这条边还可能有贡献，最终的入度只可能是 $a_u$ 或者 $a_u+1$，又由于 $k\geq 2$ 所以 $a_u\not\equiv a_u+1 \pmod k$，只可能其中一个是 $k$ 的倍数，要使得 $k|a_u$ 那么方案是唯一的。所以对所有 $k\geq 2$，答案要么是 0 要么是 1。由于每条边只会有 1 的贡献，所以最终所有点的入度和一定是 n-1，又要是 $gcd=k$，那么每个 $a_u$ 都是 $k$ 的倍数，那么一定有 $k|n-1$。所以只需要暴力判断 $n-1$ 的因子即可。这样就可以求出所有 $k\geq 2$ 的答案，那么 $k=1$ 的答案就是 $2^{n-1}$ 减去这些的和。

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;

inline int read(){
	int x=0,flag=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return flag? x:-x;
}

const int N=1e5+7;
const int Mod=998244353;

int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod,y>>=1;
	}
	return ret;
}

struct E{
	int next,to;
}e[N<<1];

int n,head[N],cnt=0,ans[N],a[N];

inline void add(int id,int to){
	e[++cnt]=(E){head[id],to};
	head[id]=cnt;
	e[++cnt]=(E){head[to],id};
	head[to]=cnt;
}

inline int gcd(int x,int y){
	return y? gcd(y,x%y):x;
}

int K;
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	if(u==1) return ;
	if(!head[u]||a[u]%K==0) a[fa]++;
	else a[u]++;
}

bool check(int k){
	K=k;
	for(int i=1;i<=n;i++) a[i]=0;
	dfs(1,1);
	int ret=a[1];
	for(int i=2;i<=n;i++) ret=gcd(ret,a[i]);
	return ret==k;
}

int main(){
//	freopen("data.in","r",stdin);
	int T=read();
	while(T--){
		n=read(); cnt=0;
		for(int i=1;i<=n;i++) head[i]=ans[i]=0;
		for(int i=2;i<=n;i++)
			add(read(),read());
		for(int i=1;i*i<=n-1;i++)
			if((n-1)%i==0){
				if(i!=1) ans[i]=check(i);
				if(i*i!=n-1) ans[(n-1)/i]=check((n-1)/i);
			}
		int ret=0;
		for(int i=2;i<=n;i++) ret+=ans[i];
		ans[1]=(qpow(2,n-1)-ret+Mod)%Mod;
		for(int i=1;i<=n;i++) printf("%d ",ans[i]); putchar('\n');
	}
}
```

---

## 作者：ChrysanthBlossom (赞：1)

来点不需要观察直接硬做的做法。

首先经典的改写 $ans_k$ 为序列 $a_n$ 中每个元素都是 $k$ 的倍数的方案数，最后容斥即可。

然后枚举每个 $k$ 求答案。考虑 dp。设 $f_{u,0/1}$ 表示考虑 $u$ 这个子树，$u$ 点在它的父亲后面/前面被选择的方案数。转移式如下：

 $$f_{u,0}=\sum\limits_{k||S|}\prod_{v \in S}f_{v,0}\prod_{v \notin S}f_{v,1}$$
 $$f_{u,1}=\sum\limits_{k|(|S|+1)}\prod_{v \in S}f_{v,0}\prod_{v \notin S}f_{v,1}$$

这个看着就可以搞成若干个 $f_{v,0}+f_{v,1}x$ 相乘的形式啊，直接分治 + NTT 做过去。

这样时间复杂度是 $O(n^2 \log^2 n)$ 的，糖丸了。但是你注意到当你枚举的度数太大时，有很多点在选的时候必须要满足旁边的点都被选过了，因此如果有两个连起来的选过了的点，答案显然为 $0$，接下来只用考虑每个度数小于 $k$ 的点都不相邻的情况了。考虑像 [CF1119F](https://www.luogu.com.cn/problem/CF1119F) 那样做，将 $k$ 从小到大扫，每次给在此时之后 $f$ 不会变的点打个标记。当一个点被标记后，你会惊奇的发现它的 $f_0$ 就是 $1$，$f_1$ 就是 $0$，所以相当于说你上面算的时候直接不乘就行了！因此 dfs 的时候，看到有儿子被标记了直接删掉即可。最后每个点被 dfs 的次数之和显然是 $O(\sum\limits^{n}_{i=1} \sum\limits^{n}_{j=1}[d_j>i])=O(n)$ 的，总的时间复杂度就是 $O(n \log^2 n)$ 了。

实际效率似乎还行吧，我这个大常数选手~~只用了区区 4000ms~~没卡常就过了。但他只要稍微动一动模数我就寄寄寄了。

细节有点，给个代码吧：

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
#define mkp make_pair
using namespace std;
const int maxn=1e5+7;
ll qpow(ll a,ll b,ll p){
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans; 
}
const int mod=998244353;
const int G=3;
const int invG=qpow(G,mod-2,mod);
struct Poly{
	vector<int>f;
	vector<int>rev;
	int siz;
	int limit;
	void calc_rev(){
		rev.resize(limit);
		for(ri i=0;i<limit;i++){
			rev[i]=(rev[i>>1]>>1)|(i&1?(limit>>1):0);
		}
	}
	void NTT(bool tp){
		calc_rev();
		for(ri i=0;i<limit;i++)if(i<rev[i])swap(f[i],f[rev[i]]);
		for(ri len=2;len<=limit;len<<=1){
			int pa=len>>1;
			ll dwg=qpow(tp?G:invG,(mod-1)/len,mod);
			for(ri i=0;i<limit;i+=len){
				ll bf=1;
				for(ri j=i;j<i+pa;j++){
					ll t=f[j+pa]*bf%mod;
					f[j+pa]=(f[j]-t+mod)%mod; 
					f[j]=(f[j]+t)%mod;
					bf=bf*dwg%mod;
				}
			}
		}
		if(!tp){
			ll invn=qpow(limit,mod-2,mod);
			for(ri i=0;i<limit;i++)f[i]=f[i]*invn%mod;
		}
	}
	void calc_limit(){
		limit=1;
		while(limit<siz)limit<<=1;
		f.resize(limit);rev.resize(limit);
	}
	friend Poly operator * (Poly a,Poly b){
		Poly ans;
		ans.siz=a.siz+b.siz;
		a.siz=ans.siz;b.siz=ans.siz;
		ans.calc_limit();a.calc_limit();b.calc_limit();
		int limit=ans.limit;
		a.NTT(1);b.NTT(1);
		for(ri i=0;i<limit;i++)ans.f[i]=1ll*a.f[i]*b.f[i]%mod;
		ans.NTT(0);
		return ans;
	}
};
void test(){
	int n,m;
	cin>>n>>m;
	Poly a,b;a.siz=n+1,b.siz=m+1;
	a.calc_limit();b.calc_limit();
	for(ri i=0;i<=n;i++)cin>>a.f[i];
	for(ri i=0;i<=m;i++)cin>>b.f[i];
	Poly ans=a*b;
	for(ri i=0;i<=n+m;i++)cout<<ans.f[i]<<' ';cout<<endl;
	exit(0);
}
vector<pair<int,int> >prpa;
Poly solve(int l,int r){
	Poly ans;
	if(l==r-1){
		ans.siz=2;
		ans.calc_limit();
		ans.f[0]=prpa[l].first;
		ans.f[1]=prpa[l].second;
		return ans;
	}
	int mid=l+r>>1;
	Poly a=solve(l,mid),b=solve(mid,r);
	ans=a*b;
	return ans;
}
int n;
vector<int>vec[maxn];
ll f[maxn][2];
bool vis[maxn];
int nowk;
bool have_calc[maxn];
int d[maxn];
void dfs(int u,int fa){
	have_calc[u]=1;
	if(vis[u]){
		f[u][0]=1;
		f[u][1]=0;
		return;
	}
	for(auto v:vec[u]){
		if(v==fa)continue;
		dfs(v,u);
	}
	prpa.clear();
	prpa.emplace_back(mkp(1,0));
	for(auto v:vec[u]){
		if(v==fa)continue;
		prpa.emplace_back(mkp(f[v][0],f[v][1]));
	}
	Poly ans=solve(0,prpa.size());
	f[u][1]=0;
	for(ri i=0;i<=d[u];i+=nowk){
		f[u][1]=(f[u][1]+(d[u]-i<ans.f.size()?ans.f[d[u]-i]:0))%mod;
	}
	f[u][0]=0;
	for(ri i=0;i<=d[u]-1;i+=nowk){
		f[u][0]=(f[u][0]+(d[u]-i-1<ans.f.size()?ans.f[d[u]-i-1]:0))%mod;
	}
	vector<int>rstch;
	for(auto v:vec[u]){
		if(!vis[v])rstch.emplace_back(v);
	}
	swap(vec[u],rstch);
}
ll ans[maxn];
vector<int>dl[maxn];
vector<int>ori[maxn];
void solve(){
	cin>>n;
	for(ri i=1;i<=n;i++)vec[i].clear(),ori[i].clear();
	for(ri i=2;i<=n;i++){
		int u,v;cin>>u>>v;
		vec[u].emplace_back(v);vec[v].emplace_back(u);
		ori[u].emplace_back(v);ori[v].emplace_back(u);
	}
	for(ri i=1;i<=n;i++)d[i]=vec[i].size();
	for(ri i=1;i<=n;i++)dl[i].clear();
	for(ri i=1;i<=n;i++)dl[vec[i].size()+1].emplace_back(i);
	vector<int>rstp;
	for(ri i=1;i<=n;i++)rstp.emplace_back(i);
	for(ri i=1;i<=n;i++)vis[i]=ans[i]=0;
	for(nowk=1;nowk<=n;nowk++){
		bool r=0;
		for(auto x:dl[nowk]){
			vis[x]=1;
			for(auto v:ori[x]) {
				if(vis[v])r=1;
			}
		} 
		if(r)break;
		for(auto x:rstp)have_calc[x]=0;
		vector<int>new_p;
		ans[nowk]=1;
		for(auto x:rstp){
			if(vis[x])continue;
			new_p.emplace_back(x);
			if(!have_calc[x]){
				dfs(x,0);
				ans[nowk]=ans[nowk]*f[x][1]%mod;
			}
		}
		swap(rstp,new_p);
	}
	for(ri i=n;i;i--){
		for(ri j=i*2;j<=n;j+=i){
			ans[i]=(ans[i]-ans[j]+mod)%mod;
		}
	}
	for(ri i=1;i<=n;i++)cout<<ans[i]<<' ';cout<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：kcn999 (赞：1)

容易发现标记结点 $u$，等价于把所有此时与 $u$ 相连的**无向边**，改成指向 $u$ 的**有向边**。做完所有操作后，$a_i$ 即为 $i$ 的**入度**。

共有 $n-1$ 条边，则操作的总方案数为 $2^{n-1}$。

$k=1$ 的情况貌似不好算，先考虑 $k>1$。

容易发现 $k>1$ 的方案中，任意 $a_i$ 都为 $0$ 或都至少为 $2$。而树中的叶子结点只有 $1$ 条边，则叶子必须最后被删掉。现在我们先对所有叶子 $u$，令 $a_{\mathrm{fa}_u}$ 加 $1$，然后把 $u$ 从原图中删去。

此时删掉所有叶子后，叶子的父亲就成为了新的叶子。因为此时任意新叶子 $u$ 也只剩下 $1$ 条连边，则 $a_u$ 只可能不变（$u$ 与 $\mathrm{fa}_u$ 的边指向 $\mathrm{fa}_u$），或者变成 $a_u+1$（$u$ 与 $\mathrm{fa}_u$ 的边指向 $u$）。

考虑 $k$ 若为 $\gcd$，则要令 $k \mid a_u$。所以若此时 $k \nmid a_u$，则只能令 $a_u$ 加 $1$。而若 $k \mid a_u$，则一定有 $k \nmid (a_u+1)$，则只能令 $a_u$ 不变。

一直重复这个删掉叶子的操作，我们就可以构造出唯一的一个方案，然后再求一遍它们的 $\gcd$ 判断是否合法即可。

而 $k=1$ 的答案可以用 $2^{n-1}$ 减去 $k>1$ 的答案得到。

每次枚举 $k$，然后做一次拓扑排序来删掉叶子，则总复杂度为 $O(n^2)$。

因为 $a_1+a_2+\cdots+a_n=n-1$，又 $k = \gcd(a_1,a_2,\cdots,a_n)$ 即 $\forall i \in [1,n],k \mid a_i$，所以 $k \mid (n-1)$。

那么我们只需要枚举 $k$ 时只需要枚举 $n-1$ 的约数，时间复杂度变为 $O(nd(n))$，其中 $d(n)$ 表示 $n$ 的因数个数。

由上文可以得到，每一个 $k$ 都对应唯一的一种构造方案，而每次构造出方案后，算出来的 $\gcd$ 可能不为 $k$，若 $k \mid \gcd$，那我们可以直接令 $ans_{\gcd} = 1$（当 $k$ 等于这个 $\gcd$ 时它一定是合法方案）。

所以我们可以只枚举 $n-1$ 的质因子，则时间复杂度变为 $O(n\omega(n))$，其中 $\omega(n)$ 表示 $n$ 的质因数个数。

```cpp
#include <bits/stdc++.h>
#define MAX_N (100000 + 5)
#define LL long long
using namespace std;
const int mod = 998244353;
int T;
int n;
bool is[MAX_N];
int p[MAX_N], nxt[MAX_N], num;
int d[MAX_N], tmp[MAX_N], a[MAX_N];
bool vis[MAX_N];
int ans[MAX_N];
int h[MAX_N], tot;
struct Edge {
	int to, next;
} e[MAX_N * 2];
int q[MAX_N], l, r;
void Read(int &x) {
	x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
}
void AddEdge(int u, int v) {
	e[++tot].to = v;
	e[tot].next = h[u];
	h[u] = tot;
}
int gcd(int a, int b) {
	int c;
	while (b) c = a % b, a = b, b = c;
	return a;
}
void Solve(int k) {
	for (int i = 1; i <= n; ++i) tmp[i] = d[i];
	l = 1, r = 0;
	for (int i = 1; i <= n; ++i) 
		if (d[i] == 1) q[++r] = i;
	while (l <= r) {
		int u = q[l++];
		vis[u] = 1;
		for (int i = h[u]; i; i = e[i].next) {
			int v = e[i].to;
			if (vis[v]) continue;
			if (a[u] % k == 0) ++a[v];
			else ++a[u];
			--d[v];
			if (d[v] == 1) q[++r] = v;
		}
	}
	int res = a[1];
	for (int i = 2; i <= n; ++i) res = gcd(res, a[i]);
	if (res % k == 0) ans[res] = 1;
	for (int i = 1; i <= n; ++i) d[i] = tmp[i], a[i] = vis[i] = 0;
}
int main() {
	n = 1e5;
	is[1] = nxt[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!is[i]) p[++num] = i, nxt[i] = i;
		for (int j = 1; i * p[j] <= n; ++j) {
			is[i * p[j]] = 1;
			nxt[i * p[j]] = p[j];
			if (i % p[j] == 0) break;
		}
	}
	Read(T);
	while (T--) {
		Read(n);
		int u, v;
		for (int i = 1; i < n; ++i) {
			Read(u), Read(v);
			AddEdge(u, v), AddEdge(v, u);
			++d[u], ++d[v];
		}
		int cur = n - 1;
		while (cur != 1) {
			Solve(nxt[cur]);
			int d = nxt[cur];
			while (cur % d == 0) cur /= d; 
		}
		int prod = 1, sum = 0;
		for (int i = 2; i <= n; ++i) {
			prod = prod * 2 % mod;
			sum += ans[i];
		}
		printf("%d", ((prod - sum) % mod + mod) % mod);
		for (int i = 2; i <= n; ++i) printf(" %d", ans[i]);
		putchar('\n');
		for (int i = 1; i <= n; ++i) d[i] = h[i] = ans[i] = 0;
		tot = 0;
	}
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

##### CF1554E

[题目链接](https://www.luogu.com.cn/problem/CF1554E)

问题就是对边定向，$a_i$ 为 $i$ 出度。首先，$\sum\limits_i a_i = n-1,\sum\limits_i ans_i= 2^{n-1}$。每条边只会贡献一次，答案总和就是每条边随意定向的方案数。考虑特殊的叶子节点，若叶子往父亲定向，那么 $a_u =1$，$\gcd$ 必然为 $1$。这启示我们考虑 $\gcd$ 不是 $1$ 的方案，这时叶子的定向必定是叶向的。然后往上一层的当前出度也确定了。设当前要求 $ans_k$，若上一层（叶子的父亲）的出度不是 $k$ 的倍数，则必定要让这个点的父亲朝向它，如果还不行，那么 $ans_k=0$。注意到这个东西是从下往上做的，且是唯一确定的（因为每次只会可能加一，而相邻两个数互质），所有 $\forall k>1,ans_k \in \set{0,1}$。又注意到当 $\gcd(a)=k$ 时，$k|n-1$，所以枚举 $n-1$ 的质因子判断即可。如果不是质因子，那么每个点的出度必定在这个数某个质因子做的时候已经成立了（由于唯一确定方案，所以这里的连边方案放到它的质因子中还是对的，由于这样子 $\gcd(a)\ge k$，所以肯定不用管非质因子了）。复杂度 $\Theta(n \omega(n))$。

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2600}$
---
### 解题思路：

先转化题意为给边定向，每一个点的权值就是点的出度（或者本质一样的入度）。

一开始注意的是，对于 $k\ge 2$ 的情况，叶子节点的定向是非常局限的，一旦叶子节点的权值为 $1$，整个结果就立即为 $1$ 了。

这就启示了应当把 $k=1$ 和其它情况分开来看，而且这两者之间有答案之和等于 $2^{n-1}$ 的关系，只需要求出后者也就能求出 $k=1$ 的情况了。

---
进一步考虑 $k\ge 2$ 的情况，可以发现如果确定 $k$，限制就不仅仅局限于叶子节点了。考虑一种从叶子节点到根节点的拓扑，每一个节点被考虑到的时候只有向父亲的边没有被定向，可能作出的变化也就是两种，所有情况都是确定的了。

但仅仅这样还是不够的，此时的复杂度为 $O(n^2)$，考虑进一步的优化。

---

优化的突破口在于 $\sum a_i=n-1$，一条边只会贡献一个权值。这样如果有 $\gcd(a_1,a_2,\dots ,a_n)=k$，则一定有 $k|n-1$。也就是只需要枚举 $n-1$ 的因数就行了。

其实这里还可以再优化一点，只枚举 $n-1$ 的素因数，因为对于任意的 $k$ 做完之后还需要检验是否符合 $k$ 是最大的，任意的非质数因数都一定在做这个因数的因数的时候考虑过了。

---
别忘了多测清空和开 $\text{long long}$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MAXN=200005,MOD=998244353;
int T,n,head[MAXN],nxt[MAXN],num[MAXN],tot,x,y,n_,ans[MAXN],sum,cnt[MAXN],flag;
void init(){
	for(int i=1;i<=n;i++)
	head[i]=0;tot=0;
	for(int i=1;i<=n;i++)
	ans[i]=0;sum=0;
	for(int i=1;i<=n;i++)
	cnt[i]=0;
}
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
void dfs(int now,int fa,int k){
	for(int i=head[now];i;i=nxt[i])
	if(num[i]!=fa)dfs(num[i],now,k);
	if(cnt[now]%k==0)cnt[fa]++;else
	if((cnt[now]+1)%k==0)cnt[now]++;else
	flag=0;
}
void work(int now){
	for(int i=1;i<=n;i++)cnt[i]=0;
	flag=1;
	dfs(1,0,now);
	if(flag==0)return;
	int GCD=0;
	for(int i=1;i<=n;i++)GCD=gcd(GCD,cnt[i]);
	ans[GCD]=1;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld",&n);
		for(int i=1;i<n;i++){
			scanf("%lld%lld",&x,&y);
			add(x,y);add(y,x);
		}
		n_=n-1;
		for(int i=2;i<=n_;i++){
			if(n_%i==0)work(i);
			while(n_%i==0)n_/=i;
		}
		if(n_!=1)work(n_);
		for(int i=1;i<=n;i++)
		sum+=ans[i];
		printf("%lld ",(pow(2,n-1)-sum+MOD)%MOD);
		for(int i=2;i<=n;i++)
		printf("%lld ",ans[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：0)

问题转化成将树的边定向，一个点的 $a$ 相当于她的出度。

注意到当 $k$ 很大的时候，我们是很难构造出解的。

具体地，当 $k\ge 2$ 时，答案至多为 $1$。原因是我们从叶往根考虑每一条边的方向。叶子向上的那些边一定是向下的（因为叶子的出度一定要为 $0$），然后一个点的所有儿子边都确定了，由于出度要整除 $k$，父亲边的方向就呼之欲出了（或者无解）。

以下称对 $k$ 进行上述操作为 $k$ 操作。

我们发现 $x$ 操作后可能 $\gcd$ 不是 $x$，而是 $x$ 的某个倍数。我们得到：所有为 $x$ 正整数倍的 $k$ 中只有这个求出 $\gcd$ 的是 $1$，否则是 $0$。

所以就类似埃氏筛。由于 $\sum a_i=n-1$，所以有解的 $k$ 一定是 $n-1$ 的因数。

我们对于所有 $n-1$ 的素因数进行操作，这样除了 $\gcd=1$ 的答案就都知道了。

最后由于 $\sum ans_i=2^{n-1}$（每条边两种方向），得到 $ans_1$。

时间 $O(n\cdot \omega(n))$，其中 $\omega$ 表示素因数个数，在 $n=10^5$ 下很小。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug cerr<<"Line#"<<__LINE__<<endl
#define ll long long
const ll mod=998244353;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int long long
#define N 100005
int n,qwq;
bool vis[N],ans[N],flag;
vector<int> e[N],p;
inline int gcd(int x,int y){
	if(!y) return x;
	return gcd(y,x%y);
}
bool dfs(int rt,int fa,int val){
	if(!flag) return 0;
	int cnt=0;
	for(int i:e[rt]) if(i!=fa) cnt+=dfs(i,rt,val);
	if(cnt%val!=0 && (!fa || (cnt+1)%val!=0)) flag=0;
	if(cnt%val==0){
		qwq=gcd(qwq,cnt);
		return 1; 
	}else{
		qwq=gcd(qwq,cnt+1);
		return 0;
	}
}
void work(){
	cin>>n;
	For(i,1,n) ans[i]=false;
	For(i,1,n) e[i].clear();
	int x,y;
	For(i,1,n-1){
		cin>>x>>y;
		e[x].pb(y);
		e[y].pb(x);
	}
	x=n-1;
	for(int i:p){
		if(x==1) break;
		if(x%i) continue;
		while(x%i==0) x/=i;
		qwq=0;
		flag=1;
		dfs(1,0,i);
		if(flag) ans[qwq]=1;	
	}
	int tmp=pw(2,n-1);
	For(i,2,n) if(ans[i]) (tmp+=mod-1)%=mod;
	cout<<tmp; For(i,2,n) cout<<" "<<ans[i]; cout<<endl;
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	For(i,2,N-1) if(!vis[i]){
		p.pb(i);
		for(int j=i*i;j<N;j+=i) vis[j]=1;
	}
	int T;cin>>T;
	while(T--)work(); 
return 0;}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出一棵树，每次标记一个节点 $x$ ，并使 $a_x$ 为**与其相连且尚未被标记**的节点的数量，对于每个 $1\leq k\leq n$，求出有多少个符合条件的数列 $a_{1...n}$ ，使得 $\gcd(a_i)=k$.  
答案对 $998244353$ 取模.  
$n\leq 10^5$
## $\text{Solution}$
题意可以转化为：对于每一条树边 $(u,v)$ ，会使得 $a_u$ 和 $a_v$ 两者之一加一.  
显然一共有 $2^{n-1}$种 $a_{1...n}$.  
$k=1$ 的情况较为复杂，似乎不易求解.  

换个方向，$k>1$ 时，似乎合法的情况并不多.  
进一步分析发现， $k>1$ 时，答案至多为 $1$.  
考虑构造证明.  
首先，叶子节点连向父亲的边肯定不能加到自己身上，只能加给父亲.  
往上递归，每个节点连向儿子的边加给自己的权的和是确定的，所以也可以确定为了合法，连向父亲的边是否要加给自己.   
这样下去，对于每个 $k$，如果存在合法方案，就是唯一确定的.

然而，如果我们对于每一个 $k$ 暴力 $\text{dfs}$ 判断合法，是 $n^2$ 的.  
注意到，$\sum a_i$ 恒等于 $n-1$ ，由于 $\text{gcd}$ 的性质，如果一个 $k$ 不是 $n-1$ 的因数，那么它必定不合法.  
而 $n-1$ 的因数个数只有 $O(\sqrt n)$  个，时间复杂度就是 $n\sqrt n$，可以通过.  
$k=1$ 的情况可以用 $2^{n-1}$ 减去所有 $k>1$ 的方案数得到.

细节上，$\text{dfs}$ 判完合法之后，还要看看这个 $k$ 是不是**最大的**公因子.
## $\text{code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=998244353;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}


int n,m;

struct node{
  int to,nxt;
}p[N<<1];
int fi[N],cnt;
inline void addline(int x,int y){
  p[++cnt]=(node){y,fi[x]};fi[x]=cnt;
  return;
}

int sum[N],k;
int flag;
void dfs(int x,int f){
  sum[x]=0;
  //debug("x=\n");
  for(int i=fi[x];~i;i=p[i].nxt){
    int to=p[i].to;
    if(to==f) continue;
    dfs(to,x);
    if(sum[to]%k==0) sum[x]++;
    else sum[to]++;
  }
  if(sum[x]%k&&(sum[x]%k!=k-1||!f)) flag=0;
  return;
}
int bac[N];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    n=read();
    fill(fi+1,fi+1+n,-1);cnt=-1;
    fill(bac+1,bac+1+n,0);
    for(int i=1;i<n;i++){
      int x=read(),y=read();
      addline(x,y);addline(y,x);
    }
    ll res(1);
    for(int i=1;i<n;i++) res=(res*2)%mod;
    for(int i=n;i>=2;i--){
      bac[i]=0;
      if((n-1)%i) continue;
      k=i;
      flag=1;
      dfs(1,0);
      if(!flag) continue;
      int g(0);
      for(int i=1;i<=n;i++) g=gcd(g,sum[i]);
      if(g!=i) continue;
      res--;
      bac[i]++;
    }    
    if(res<0) res+=mod;
    bac[1]=res;
    for(int i=1;i<=n;i++) printf("%d ",bac[i]);
    putchar('\n');
  }  
  return 0;
}

```


---

## 作者：TernaryTree (赞：0)

想不出来的题。

等价于边定向是显然的。于是 $a$ 就是每个点出度序列，对应一个边定向方案，故方案总数为 $2^{n-1}$。

想不出来的结论：$k>1$ 时 $ans_k\le 1$。考虑后序遍历整棵树，每次定向完子树内的边之后定向 $u$ 到父亲的边。显然 $k>1$ 时 $x$ 与 $x+1$ 里面只能有一个是 $k$ 的倍数，所以我们可以根据子树信息合并，推出 $u$ 的出度，再向上一步一步推，得到所有点的出度。再取 $\gcd$ 判断是否等于 $k$ 可以得到 $ans_k$ 为 $0$ 还是 $1$。

因为有总方案数，所以知道了所有 $ans_k\ (k>1)$ 就可以算出 $ans_1$ 了。并且 $k\mid n-1$ 时 $ans_k$ 才有可能为 $1$，$k$ 只需要枚举 $n-1$ 因数即可。复杂度 $\Theta(nd(n))$。 

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const bool multidata = 1;
const int mod = 998244353;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int power(int a, int b, int p = mod) {
	int t = 1; a %= p;
	while (b) {
		if (b & 1) t = t * a % p;
		a = a * a % p, b >>= 1;
	}
	return t;
}

int n;
vector<int> tr[maxn];
int out[maxn];
int ans[maxn];

void dfs(int u, int fa, int k) {
	for (int v : tr[u]) {
		if (v == fa) continue;
		dfs(v, u, k);
	}
	if (out[u] % k) ++out[u];
	else ++out[fa];
}

int work(int k) {
	rep(i, 1, n) out[i] = 0;
	dfs(1, 0, k);
	int g = 0; rep(i, 1, n) g = __gcd(out[i], g);
	return g == k;
}

void fake_main() {
	n = read();
	rep(i, 1, n - 1) {
		int u = read(), v = read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	rep(i, 1, sqrt(n - 1)) {
		if ((n - 1) % i == 0) {
			if (i != 1) ans[i] = work(i);
			if (i * i != n - 1) ans[(n - 1) / i] = work((n - 1) / i);
		}
	}
	ans[1] = power(2, n - 1);
	rep(i, 2, n) (ans[1] += mod - ans[i]) %= mod;
	rep(i, 1, n) write(ans[i]), pc(' '); pc('\n');
	rep(i, 1, n) tr[i].clear(), ans[i] = 0;
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

```

---

