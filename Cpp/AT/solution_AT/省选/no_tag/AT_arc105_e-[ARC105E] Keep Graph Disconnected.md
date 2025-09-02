# [ARC105E] Keep Graph Disconnected

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc105/tasks/arc105_e

$ 1 $ から $ N $ の番号がついた $ N $ 個の頂点と、$ 1 $ から $ M $ の番号がついた $ M $ 本の辺からなる無向グラフ $ G $ が与えられます。 辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を双方向につないでいます。

$ G $ が以下の条件の両方を満たすとき、$ G $ は *よいグラフ* であるといいます。はじめ、$ G $ はよいグラフであることが保証されます。

- 頂点 $ 1 $ と $ N $ が非連結
- 自己ループや多重辺が存在しない

先手太郎君と後手次郎君が対戦ゲームをします。 先手太郎君と後手次郎君の手番が交互に訪れます。先手太郎君が先手です。 それぞれのプレイヤーは、手番において以下の操作が可能です。

操作：頂点 $ u,v $ を選んで $ u $ と $ v $ を双方向につなぐ辺を $ G $ に追加する。

辺を追加した結果、$ G $ がよいグラフでなくなった人の負けです。$ 2 $ 人が最適に行動したときに勝つのはどちらかを判定してください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 10^{5} $
- $ 0\ \leq\ M\ \leq\ \min(N(N-1)/2,10^{5}) $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- 与えられるグラフはよいグラフ
- $ 1 $ つの入力ファイルにおいて、$ N $ の総和、$ M $ の総和はどちらも $ 2\ \times\ 10^5 $ を超えない。

### Sample Explanation 1

\- テストケース $ 1 $ では先手太郎君が勝利します。以下はそのような $ 2 $ 人の行動の例です。 - 先手太郎君の手番で頂点 $ 1,2 $ をつなぐ辺を追加する。辺を追加したあとのグラフもよいグラフです。 - 後手次郎君はどの $ 2 $ つの頂点の間に辺を追加したとしても、グラフがよいグラフではなくなってしまいます。 - よって、勝者は先手太郎君です。

## 样例 #1

### 输入

```
3
3 0
6 2
1 2
2 3
15 10
12 14
8 3
10 1
14 6
12 6
1 9
13 1
2 5
3 9
7 2```

### 输出

```
First
Second
First```

# 题解

## 作者：STrAduts (赞：17)

好思维。一开始一直往可达性 dp 上想，结果是直接研究初末状态找结论。

考察在游戏结束的时候，整个图是什么样子。不难发现其实就是分别以 $1$ 和 $n$ 为中心裂成了两部分，两部分都是完全图。这样下一次再连的时候，就只能把这两部分连起来，导致不合法。

不妨假定最后有 $x$ 个点与 $1$ 联通，有 $y = n - x$ 个点与 $n$ 联通，那从初状态到达末状态需要经历的边数即是 $\frac {n(n - 1)} {2} - m - x \times y$。显然，输赢之和这个式子的奇偶性有关。奇数则先手赢，偶数则后手赢。而其中 $x$ 是唯一的变量，试想 $x$ 奇偶性的变化会对原式产生什么影响。

注意到，如果 $n$ 为奇数，$x$ 不能影响原式的奇偶性，故只考虑 $n$ 为偶数的情况。先手的优势在于可以通过连边主导 $x$ 的奇偶性变化。思考这个过程，若一开始有 $x'$ 个点和 $1$ 连通，$y'$ 和 $n$ 连通。

- $x'$ 是我们想要的目标奇偶，那么我们需要在之后的过程中保证与 $x'$ 连接的奇数大小的连通块个数为偶数，又因为 $n$ 为偶数，故当且仅当 $x'$ 与 $y'$ 奇偶相同时满足。在此情况下，如果 $x'$ 不是我们想要的目标奇偶，也无法通过先手优势去改变 $x'$ 的奇偶。故而，当 $x'$ 与 $y'$ 奇偶相同时，最终的奇偶性只又最初的奇偶性决定。
- 自然讨论当 $x'$ 与 $y'$ 奇偶不同时。同样的思路，利用先手优势改变 $x'$ 的奇偶，不难发现所有对手做出的逆向改变，你都恰有更多的符合需要的连通块来抵消这样的改变。即此时先手必胜。

---

## 作者：Pengzt (赞：10)

[cnblogs](https://www.cnblogs.com/Pengzt/p/17929930.html)

[ARC105E](https://www.luogu.com.cn/problem/AT_arc105_e)

正向考虑是很难的，从结果入手，发现最后一定是分别包含 $1$，$n$ 的两个完全图。

考虑表示出这两个人一共加了多少边：$\frac{n(n-1)}{2}-m-x(n-x)$，$x$ 表示点 $1$ 所在集合的大小。

由于是判断先手还是后手必胜，所以只需看结果对 $2$ 的余数，于是对 $n$ 的奇偶进行分讨。

当 $n$ 为奇数时，此时 $x(n-x)$ 一定是偶数，这时只需要对 $\frac{n(n-1)}{2}-m$ 进行讨论。

当 $n$ 为偶数时：对 $1$，$n$ 初始时所在的连通块大小进行讨论，分别记为 $a$，$b$。当 $a$，$b$ 奇偶性相同时，由于其它所有连通块之和为偶数，所以连通块大小为奇数和偶数的连通块个数一定都为偶数，这时先后手不管怎样都无法改变局势，因为可以通过模仿对方的行动进行抵消。

当 $a$，$b$ 奇偶性不同时，显然先手可以选择变为 $a$ 奇 $b$ 奇 或 $a$ 偶 $b$ 偶的情况，故先手一定可以改变最后的连通块的奇偶性，后手的操作都可以被先手抵消，故此时先手必胜。

时空线性。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector < int >
#define eb emplace_back
#define pii pair < int, int >
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
int Mbe;
mt19937_64 rng(35);
constexpr int N = 1e5 + 10;
int n, m;
int fa[N], sz[N];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
ll calc(int x) {
	return x * 1ll * (x - 1) / 2;
}
void solve() {
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 0;
	}
	for(int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		fa[find(u)] = find(v);
	}
	for(int i = 1; i <= n; ++i) ++sz[find(i)];
	ll x = find(1), y = find(n);
	if(x == y) {
		cout << "Second" << "\n";
		return;
	}
	if(n & 1) {
		if(calc(n) % 2 - m % 2) cout << "First" << "\n";
		else cout << "Second" << "\n";
		return;
	}
	if(sz[x] % 2 != sz[y] % 2) {
		cout << "First" << "\n";
		return;
	}
	if((calc(n) - m - sz[x] % 2) & 1) cout << "First" << "\n";
	else cout << "Second" << "\n";
} 
int Med;
int main() {
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	cerr << TIME << "ms\n";
	return 0;
}
```

---

## 作者：lsj2009 (赞：10)

Update：修改了一处笔误。

感觉是更清晰的解释。

容易发现最终的局面必然是仅剩下两个连通块，且 $1$ 和 $n$ 分居这两个连通块，每个连通块都是一个完全图。设 $1$ 所在的连通块大小为 $x$，则共需要操作 $\frac{n(n-1)}{2}-m-x(n-x)$ 次，若该数为奇数，则先手胜，否则后手胜。

如果 $n$ 是奇数，则 $x(n-x)$ 必为偶数，依照 $\frac{n(n-1)}{2}-m$ 的奇偶性直接判断即可。

否则 $n$ 是偶数，则分两类讨论：

- 初始时 $1$ 所在连通块和 $n$ 所在连通块大小奇偶性相同。则此时必有偶数个奇连通块，如果先手/后手相要连接其中一个改变局势，则对应的后手/先手可以连接另一个，所以此时令 $x$ 为初始 $1$ 所在的连通块大小计算即为答案。

- 初始时 $1$ 所在连通块和 $n$ 所在连通块大小奇偶性不同。则此时必有奇数个奇连通块，如果先手用 $1$ 和 $n$ 连通块当中大小偶数的那个连接了其中一个奇连通块，则变成了上面那个情况，先手必胜。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e5+5;
int fa[N],siz[N];
int find(int x) {
    if(fa[x]!=x)
        fa[x]=find(fa[x]);
    return fa[x];
}
void merge(int u,int v) {
    u=find(u); v=find(v);
    if(u!=v) {
        if(siz[u]<siz[v])
            swap(u,v);
        fa[v]=u;
        siz[u]+=siz[v];   
    }
}
signed main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n,m;
        scanf("%d%d",&n,&m);
        rep(i,1,n)
            fa[i]=i,siz[i]=1;
        rep(i,1,m) {
            int u,v;
            scanf("%d%d",&u,&v);
            merge(u,v);
        }
        int u=find(1),v=find(n),val=n*(n-1)/2-m;
        if(n&1)
            puts(val&1? "First":"Second");
        else {
            if((siz[u]&1)==(siz[v]&1))
                puts((val-siz[u]*siz[v])&1? "First":"Second");
            else
                puts("First");
        }
    }
    return 0;
}

```

---

## 作者：Creeper_l (赞：6)

NOIP 模拟赛原题，赛时还是没切。

正解奇偶性。

考虑最终不能走的时候是什么情况，当且仅当图中只剩下两个联通块了。设其中一个联通块的点数为 $k$，那么另一个的点数为 $n - k$。所以两人一共的操作次数为 $sum = \frac{n \times (n-1)}{2}-m-k \times (n - k)$。显然如果 $sum$ 为偶数，后手赢；否则先手赢。因为前面 $\frac{n \times (n-1)}{2}-m$ 已经确定了，所以只需要分析 $k \times (n - k)$ 的奇偶性即可，故按 $n$ 的奇偶进行分类讨论。

注：每一次有效的连边可以理解为选两个联通块进行合并，$cnt_{i}$ 表示点 $i$ 所在联通块大小。

- $n$ 为奇数。$k$ 和 $n-k$ 中一定有一个为偶数，则 $k \times (n-k)$ 为偶数，直接判断 $\frac{n \times (n-1)}{2}-m$ 的奇偶性即可。

- $n$ 为偶数。不能直接判断奇偶，还需要分类讨论。

1. 如果最初 $1$ 所在的联通块和 $n$ 所在的联通块的大小的奇偶性相同的话，那么其它奇数大小的联通块一定有偶数个，假设最开始（把 $cnt_{1}$ 和 $cnt_{n}$ 视为 $k$ 和 $n-k$）的胜方为 $A$，那么当 $B$ 想用一个奇数大小的联通块翻盘的时候，$A$ 总是可以再用一个奇数大小的联通块再翻盘，所以最终的赢家为 $A$。

1. 如果最初 $1$ 所在的联通块和 $n$ 所在的联通块的大小的奇偶性不相同的话，那么奇数大小的联通块个数一定为奇数。先手可以直接使用一个奇数大小的联通块来使自己获胜，之后一直选和对方相同奇偶的联通块即可，所以先手必胜。

用并查集维护每个联通块大小。



---

## 作者：Wings_of_liberty (赞：4)

# 分析
首先我们看数据范围，很明显这是一道推结论的题。  
我们想一下最终状态，可以将整张图分成两个部分，两个部分已经分别全部填满，此时只能连接这两个部分，于是输掉。  
所以很明显我们只需要判断在不连接这两个部分的情况下最多能连接的边数是奇数还是偶数就行（偶数说明先手会连接这两个部分，先手必败，奇数则相反，先手必胜）。

# 分讨
我们很容易能够表达出剩余的边数：$n \times (n-1)/2-m-k \times (n-k)$，其中 $k$ 为一个分成两部分后一个部分含有点的数量，通过这个式子我们可以看出，在 $n$ 为奇数时，这个式子的奇偶性是固定的可以直接算，$k$ 为奇数时 $k-n$ 为偶数，奇数成偶数为偶数，同理，$k$ 为偶数时乘积也是偶数。  
但是在 $n$ 为偶数的时候就需要继续分讨，此时整个式子的奇偶性由 $k$ 来决定，我们考虑两种情况。  
第一种，连接 $1$ 的连通块与连接 $n$ 的连通块中点的数量的奇偶性不同，在这种情况下我们发现先手可以选择对他有利的奇偶性，如果先手想要最后 $k$ 和 $n-k$ 为奇数，那么先手就把一个有奇数个点的连通块与最开始偶数的那个块连上，于是得到两个有奇数个点的连通块。之后每一次后手想要改变连通块奇偶性的时候先手都可以进行一次相同操作将它变回去，所以说先手必胜。
第二种，连接 $1$ 的连通块与连接 $n$ 的连通块中点的数量的奇偶性相同，这种情况下，局势已经固定，因为不管对方做什么我都可以进行同样操作让对方操作无效，所以说此时的奇偶性已经固定，直接带入即可。

# 实现
我们使用这种解法需要判断两个点是否在一个连通块中，并且需要找到两个点所在联通块中包含元素个数，所以我们采用带权并查集实现。

# 注意
在最开始应当特判一下现在的图是否已经联通，此时先手必败。  
在过程中可能会爆整形，但是数据好像没有卡。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
#define F(i,x,y) for(ll i=(x);i<=(y);i++)
#define rF(i,x,y) for(ll i=(x);i>=(y);i--)
typedef long long ll;
inline ll read(){
	ll ret=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		ret=(ret<<3)+(ret<<1)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
ll n,m;
const ll MAX=1e5+10;
ll fa[MAX],sum[MAX],rank_[MAX];
ll find(ll x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void union_(ll x,ll y){
	x=find(x);
	y=find(y);
	if(rank_[x]>rank_[y]){
		fa[y]=x;
		if(x!=y){
			sum[x]+=sum[y];
		}
	}else{
		fa[x]=y;
		if(x!=y){
			sum[y]+=sum[x];
		}
		if(rank_[x]==rank_[y]){
			rank_[y]++;
		}
	}
}
inline void init(){
	n=read();
	m=read();
	F(i,1,n){
		fa[i]=i;
		sum[i]=1;
		rank_[i]=0;
	}
	ll a,b;
	F(i,1,m){
		a=read();
		b=read();
		union_(a,b);
	}
}
inline void work(){
	ll x=find(1),y=find(n);
	if(x==y){
		printf("Second\n");
		return;
	}
	if(n&1){
		ll f1=true,f2=true;//true 偶数 
		if((n*(n-1)/2)&1){
			f1=false;
		}
		if(m&1){
			f2=false;
		}
		if(f1^f2){
			printf("First\n");
		}else{
			printf("Second\n");
		}
		return;
	}
	if((sum[x]&1)^(sum[y]&1)){
		printf("First\n");
		return;
	}
	if((n*(n-1)/2-m-sum[x]*sum[y])&1){
		printf("First\n");
	}else{
		printf("Second\n");
	}
}
int main(){
//	op("");
	ll t=read();
	F(i,1,t){
		init();
		work();
	}
//	cl();
	return 0;
}

```
最后感谢 [james1BadCreeper](https://www.luogu.com.cn/user/187051) 对我的帮助，才有了这篇题解。

祝各位码运昌隆。

---

## 作者：EuphoricStar (赞：3)

显然终止态是只剩两个连通块，一个包含 $1$ 另一个包含 $n$，并且两个连通块内的边数均为 $\frac{sz(sz-1)}{2}$。

如果只在连通块内连边，那么能连的边的总数是 $\frac{n(n-1)}{2} - \sum\limits_{i=1}^{cnt} \frac{sz_i (sz_i - 1)}{2}$，其中 $cnt$ 为连通块总数，$sz_i$ 为第 $i$ 个连通块的点数。下文钦定 $1$ 所在连通块为第 $1$ 个连通块，$n$ 所在连通块为第 $2$ 个连通块。

然而还可以在连通块之间连边，这样还需要 $cnt - 2$ 次连边使得原图仅剩第 $1$ 个和第 $2$ 个连通块。

在连通块之间连边时，设两个连通块的 $sz$ 分别为 $x,y$，那么会新增 $xy-1$ 条块内部的连边。如果 $x,y$ 均为奇数，那么不会影响能连的边数的奇偶性；如果 $x,y$ 有一个为偶数，那么能连的边数的奇偶性会改变。

据此考虑按 $n$ 的奇偶性分类讨论。

- $n \bmod 2 = 1$：最终 $sz_1$ 和 $sz_2$ 必然一奇一偶。此时合并偶数块的次数可以算出来。
- $n \bmod 2 = 0$：最终 $sz_1$ 和 $sz_2$ 两奇或两偶。如果初始 $sz_1$ 和 $sz_2$ 奇偶性不相同，那么先手可以控制最终 $sz_1$ 和 $sz_2$ 的奇偶性，此时先手必胜；否则 $sz_1$ 和 $sz_2$ 的奇偶性不会改变，因为如果落败的那一方想改变，那么胜利的那一方可以操作回去。那么此时合并偶数块的次数也可以算出来了。

[code](https://atcoder.jp/contests/arc105/submissions/40723027)

---

## 作者：SunsetLake (赞：2)

赛时冲了两个多小时没冲出来，想得断断续续，导致没想到如何处理奇偶。

## 思路

根据限制条件一，可以知道最后的图一定是两个连通块，其中一块包含 $1$，另一块包含 $n$。因为此时再想连边就必须连通两个块，使其不合法了。

每次操作都是新增一条边，那么到最后的边数是多少呢？假设其中一个连通块有 $k$ 个点，另一个则有 $n-k$ 个点。两个连通块间肯定不会连边，因此这些没连的边就有 $k(n-k)$ 条。如果没有限制，那么 $n$ 个点之间就会互相连边，共有 $\frac{n(n-1)}{2}$ 条边。再减去题目上已经给出的边，两个连通块内就一共会有会有 $\frac{n(n-1)}{2} - m - k(n-k)$ 条边。

这时我们再来思考，先手获胜的条件是什么？谁不能操作就输了，因此先手想赢必须要刚好把需要放的边放完，也就是在上述式子值为奇时，先手获胜。观察发现，除了 $k$ 是变量，其他条件我们都已知，也就是前面一部分的奇偶我们是知道的，因此根据后面的奇偶分讨即可。

以 $n$ 的奇偶性分析。

- $n$ 为奇数时，若 $k$ 为奇数，则 $n-k$ 为偶数；若 $k$ 为偶数，则 $n-k$ 为奇数。因此，$k(n-k)$ 一直都是偶数，与 $k$ 无关了。只需看一下前面的式子是否是奇数，是则先手赢，否则后手赢。

- $n$ 为偶数时，$k(n-k)$ 即可能是奇数，也可能是偶数，因此要继续判断。

1. 当 $1$ 号点所在连通块与 $n$ 号点所在连通块奇偶性不相同时，又因为 $n$ 为偶数，因此剩下的点个数一定是奇数个，也就是一定会有奇数个奇数连通块。先手可以根据自己的需求将一个奇数连到 $1$ 号或 $n$ 号，改变它的奇偶性，让两个块都变成自己需要的奇/偶。这样奇数块个数变成偶数，先手变为后手，于是现在的后手就可以“跟在”现在的先手后面，先手连哪个块后手就跟着连，两个奇数相加又变成偶数，对块的奇偶不产生影响。因此，先手必胜。
2. 当 $1$ 号点所在连通块与 $n$ 号点所在连通块奇偶性相同时，不管是奇是偶，加起来都是偶数，因此剩下的块之和也为偶数。这就意味着剩下的块中会有偶数个个数为奇数~~有点绕~~的块。

	若当前 $1$ 号块的奇偶性已经和先手需要的奇偶性相同，那么先手就可以每次把余下的奇数块两两连接配成偶数块，如果后手想用奇数块搞事情把 $1$ 号或 $n$ 号块奇偶性打乱，那先手就跟一手将其变回来，跟不了了也没关系，还有另一个块供先手使用，因此先手必胜。
    
    若不相同，那么后手采取此策略即可反制先手，让他失败。因此后手必胜。
    
至此，题目就做完了。代码好写，但是思维难度挺高，可以再仔细琢磨琢磨。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,a[200005],b[200005];
int n,m,fa[200005];
ll sz[200005];
bool f;
int root(int x){
	if(x==fa[x])return x;
	return fa[x]=root(fa[x]);
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)fa[i]=i,sz[i]=1;//并查集求连通块大小
	for(int i=1;i<=m;++i){
		cin>>a[i]>>b[i];
		int ra=root(a[i]),rb=root(b[i]);
		if(ra!=rb){
			sz[ra]+=sz[rb];
			fa[rb]=ra;
		}
	}
	int rn=root(n),r1=root(1);
	if(rn==r1){//如果开局就不合法那么后手赢
		cout<<"Second"<<endl;
		return;
	}
	ll now=(ll)n*(ll)(n-1)/2-m;//式子的前一坨
	if(n&1){//奇数只与now的奇偶有关
		if(now&1)cout<<"First"<<endl;
		else cout<<"Second"<<endl;
	}
	else{
		if(now&1){
			if(sz[r1]%2!=sz[rn]%2)cout<<"First"<<endl;//1，n两个连通块奇偶性不一样先手必胜
			else{
				if(sz[r1]&1)cout<<"Second"<<endl;//看先手需要的奇偶性
				else cout<<"First"<<endl;
			}
		}
		else{
			if(sz[r1]%2!=sz[rn]%2)cout<<"First"<<endl;
			else{
				if(sz[r1]&1)cout<<"First"<<endl;
				else cout<<"Second"<<endl;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}
```

 

---

## 作者：spider_oyster (赞：2)

考虑最后的局面一定是只有一个包含 $1$ 的连通块和一个包含 $n$ 的连通块。

设最后 $1$ 所属连通块大小为 $x$，那么一共能连 $\frac{n(n-1)}2{}-m-x(n-x)$ 条边。

判断这个数的奇偶即可，奇数先手赢，否则后手赢。

先把常量踢出来，也就是只关心 $x(n-x)$ 的奇偶。

若 $n$ 为奇数，$x(n-x)$ 一定为偶数，特判掉。

考虑 $n$ 为偶数。

定义奇连通块为点大小为奇数的连通块，偶类似。

如果剩偶数个奇连通块，那么这些奇连通块之间可以互相抵消影响，无法改变局面，按 $1$ 一开始所属连通块大小计算答案。

否则，先手可以决定是否改变奇偶性，并变更为上面的情况，先手必胜。

一个绝妙的判断剩余奇连通块个数的方法：判断 $1,n$ 所属连通块大小之和的奇偶性。

---

## 作者：User_Unauthorized (赞：2)

## 题意

给定一张由 $N$ 个点和 $M$ 条边组成的简单无向图 $G$，定义一个无向图是好的当且仅当这张图满足以下条件：

- $1$ 号节点和 $N$ 号节点不联通
- 图中不存在重边和自环

现有两人轮流采取操作，每轮操作如下：

- 选择两个点 $u, v$，将边 $(u, v)$ 加入图 $G$ 中

当一方无法使得操作后的图 $G$ 为好的时候，游戏结束，此时另一方获胜。

现给定 $N, M$，求在双方均采取最优策略的情况下的胜方。

- $1 \le T \le 10^5$
- $2 \le N \le 10^5$
- $0 \le M \le \min\left\{\frac{N\left(N - 1\right)}{2}, 10^5\right\}$
- $\sum N, \sum M \le 2 \times 10^5$
- $G$ 满足题目中好的图的条件

## 题解

设最终局面下 $1$ 号节点所在的联通块大小为 $n$，那么可以得出双方可以操作的步数为 

$$\dfrac{N\left(N - 1\right)}{2} - M - n \left(N - n\right)$$

可以发现其奇偶性决定了胜负，因此只需要考虑其奇偶性即可，由于式子的前半部分是给定的，因此双方的策略就是通过调整 $n$ 的奇偶性来决定胜负。

可以发现当 $N$ 为奇数时，$n$ 和 $N - n$ 中一定有一个数为偶数，因此上式的奇偶性是确定的，可以直接计算。

接下来讨论 $N$ 为偶数的情况。

设 $A$ 表示初始局面下 $1$ 号节点所在的联通块大小，$B$ 表示初始局面下 $N$ 号节点所在的联通块大小。有如下结论：

- 若 $A, B$ 奇偶性不同，那么先手必胜
- 反之考虑 $\dfrac{N\left(N - 1\right)}{2} - M - A \times B$ 的奇偶性，若为奇数，那么先手必胜，反之后手必胜

证明如下：

设 $S = \dfrac{N\left(N - 1\right)}{2} - M - A \times B$。

不妨称在 $S$ 的奇偶性下处于优势的一方为优势方，反之则称为劣势方。例如当 $S$ 为奇数时，先手为优势方。

- 若 $A, B$ 奇偶性相同，那么此时图中一定存在偶数个奇联通块，因此当劣势方尝试通过操作奇联通块改变 $S$ 的奇偶性时，优势方一定可以通过操作另外的一个奇联通块使得 $S$ 的奇偶性保持不变，因此优势方一定可以保持优势，最终获胜。

- 若 $A, B$ 奇偶性不同，那么此时图中一定存在奇数个奇联通块，可以发现先手在第一次操作时可以选择一个奇联通块，并且使得 $S$ 的奇偶性变得有利于自己。接下来图中一定存在偶数个奇联通块，当后手尝试通过操作奇联通块改变 $S$ 的奇偶性时，先手一定可以通过操作另外的一个奇联通块使得 $S$ 的奇偶性保持不变，因此先手一定可以保持优势，最终获胜。

时间复杂度 $\mathcal{O}(N + M \alpha\left(N\right))$，空间复杂度 $\mathcal{O}(N)$，可以通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

template<bool sizeBalanced = true>
class DSU {
private:
    valueType N;

    ValueVector father, size;

public:
    explicit DSU(valueType n = 0) : N(n), father(N, 0), size(N, 0) {
        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    void resize(valueType n) {
        N = n;

        father.resize(N, 0);
        size.resize(N);

        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    valueType find(valueType x) {
        return father[x] == x ? x : father[x] = find(father[x]);
    }

    bool unite(int x, int y) { // y -> x if !sizeBalanced
        x = find(x), y = find(y);

        if (x == y)
            return false;

        if (sizeBalanced && size[x] < size[y])
            std::swap(x, y);

        father[y] = x;
        size[x] += size[y];

        return true;
    }

    bool check(valueType x, valueType y) {
        return find(x) == find(y);
    }

    valueType sizeOf(valueType n) {
        return size[find(n)];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, M;

        std::cin >> N >> M;

        DSU<true> dsu(N + 1);

        for (int i = 0; i < M; ++i) {
            valueType x, y;

            std::cin >> x >> y;

            dsu.unite(x, y);
        }

        valueType const A = dsu.sizeOf(1), B = dsu.sizeOf(N);

        if (N & 1) {
            valueType const X = N * (N - 1) / 2 - M;

            if (X & 1)
                std::cout << "First" << std::endl;
            else
                std::cout << "Second" << std::endl;
        } else {
            if ((A & 1) != (B & 1)) {
                std::cout << "First" << std::endl;
            } else {
                valueType const X = N * (N - 1) / 2 - M - A * B;

                if (X & 1)
                    std::cout << "First" << std::endl;
                else
                    std::cout << "Second" << std::endl;
            }
        }
    }

    return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_arc105_e](https://www.luogu.com.cn/problem/AT_arc105_e)    

简单题。   

考虑最后的局面必定是两个大小分别为 $a$ 和 $b$ 的连通块，分别包含 $1$ 和 $n$，则游戏中连的边数为 $\frac{a(a-1)}{2}+\frac{b(b-1)}{2}-m$，如果这个数为奇数则先手赢，否则后手赢。    

在 $n$ 为奇数的时候，对于任意一组 $a+b=n$，$\frac{a(a-1)}{2}+\frac{b(b-1)}{2}$ 奇偶固定，所以直接算就可以了。对于 $n$ 为偶数的情况，问题可以转化成一种对 $a$ 和 $b$ 奇偶的限制。我们分类讨论。   

1.当前 $1$ 所在连通块和 $n$ 所在连通块都是偶数，目标是偶数。则先手必赢。    
2.当前 $1$ 所在连通块和 $n$ 所在连通块都是奇数，目标是偶数。则先手必输。    
3.当前 $1$ 所在连通块和 $n$ 所在连通块一奇一偶，目标是偶数。则先手必赢。    
4.当前 $1$ 所在连通块和 $n$ 所在连通块都是偶数，目标是奇数。则先手必输。    
5.当前 $1$ 所在连通块和 $n$ 所在连通块都是奇数，目标是奇数。则先手必赢。    
6.当前 $1$ 所在连通块和 $n$ 所在连通块一奇一偶，目标是奇数。则先手必赢。      

必胜局面中的方案构造可以考虑针对后手的行动来做操作，具体地，如果最开始的时候有一个不合法的，从其他连通块中选一个奇数块连上，否则随便行动（链接两个奇数块）。如果后手使得两个块中有一个变成不合法，则在下一次行动中拉一个奇数块连上。这样的方案可以在所有必胜策略中获胜，其他的必输情况下，如果对面按同样方式行动，则明显必输。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9;
vector<int>E[500003];
int stk[500003],tot,vis[500003];
void dfs(int now){
	if(vis[now]!=0)return;
	vis[now]=tot;
	stk[tot]++;
	for(auto i:E[now])dfs(i);
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>k1>>k2;
			E[k1].emplace_back(k2);
			E[k2].emplace_back(k1);
		}
		for(int i=1;i<=n;i++)vis[i]=0;
		tot=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				tot++;
				stk[tot]=0;
				dfs(i);
			}
		}	
		for(int i=1;i<=n;i++){
			E[i].clear();
			E[i].shrink_to_fit();
		}
		if(vis[1]==vis[n]){
			cout<<"Second\n";
			continue;
		}
		if(n%4==3){
			if(m%2==0)cout<<"First\n";
			else cout<<"Second\n";
			continue;
		}
		if(n%4==1){
			if(m%2==1)cout<<"First\n";
			else cout<<"Second\n";
			continue;
		}
		if((m%2==0&&n%4==0)||(m%2==1&&n%4==2)){
			if(stk[vis[1]]%2==0&&stk[vis[n]]%2==0)cout<<"Second\n";
			else cout<<"First\n";
			continue; 
		}
		else{
			if(stk[vis[1]]%2==1&&stk[vis[n]]%2==1)cout<<"Second\n";
			else cout<<"First\n";
			continue; 
		}
	}
	return 0;
}
```


---

## 作者：sleepy66 (赞：0)

## 题意

两人在一个有 $n$ 个点，$m$ 条边的图上不断加边，当一个人连完边后点 $1$ 、$n$ 连通时他就输，求两个人博弈的最终结果。

## 思路

容易发现，图分成两个完全图， $1$ 和 $n$ 各在一个完全图时，下一个人必败。

此时我们发现，如果开始时 $1$ 和 $n$ 连通，那么先手必败。

设最后分成两个完全图时 $1$ 所在的完全图的节点数为 $x$ ，可以推出最多可以连的边数为 :
$$
\frac{n\times(n-1)}{2}-m-x\times(n-x)
$$
其中 $\frac{n\times(n-1)}{2}$ 是整个图的最多边数，$m$ 是现在已经打开的边数， $x\times(n-x)$ 是连接两个完全图的边数。

易证，当最多可连边数为奇数时先手必胜，否则后手必胜。

观察发现，当 $n$ 为奇数时，$x\times(n-x)$ 一定是偶数，所以可以直接 $O(1)$ 推出答案。

当 $n$ 为偶数时，我们需要分类讨论，设 $x'$ 为与 $1$ 连通的点数，$y'$ 为与 $n$ 连通的点数，则：

如果 $x'$  的奇偶性与 $y'$ 相同，那有奇数个数节点的连通块数量一定为偶数。那么假如 $x'$ 的奇偶性与当前要操作的人的必胜方案所需的奇偶性相同，他一定不会想要改变当前的奇偶性。否则，他会尝试改变奇偶性。可是对方并不会放他改变，一定会取一个节点数奇偶性和想改变的人相同的连通块。到最后，我们会发现 $x'$ 和 $y'$ 的奇偶性并不会发生变化，所以我们直接算出开始时的 $x'$ 和 $y'$ 推出答案即可。

如果 $x'$  的奇偶性与 $y'$ 不同，那么先手可以考虑改不改变奇偶性，选完后就变成了上面的情况，所以先手必胜。

对于代码实现，我们可以用一个并查集找出 $x'$ 和 $y'$ 。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define N 100010
int t,n,m,u,v,f[N];
int find(int x){
	if(f[x]==x)return x;
	else return f[x]=find(f[x]);
}
void print(bool f){
	if(f)printf("First\n");
	else printf("Second\n");
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)f[i]=i;
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&u,&v);
			int fu=find(u);
			int fv=find(v);
			f[fu]=fv;
		}
		int x=1,y=1,f1=find(1),fn=find(n),tmp=n*(n-1)/2-m;
		if(f1==fn){print(0);continue;}
		if(n&1){print(tmp&1);continue;}
		for(int i=2;i<n;i++){
			int fi=find(i);
			if(fi==f1)x++;
			if(fi==fn)y++;
		}
		if((x&1)==(y&1)){print((tmp-x*(n-x))&1);continue;}
		else print(1);
	}
	return 0;
}
```





---

