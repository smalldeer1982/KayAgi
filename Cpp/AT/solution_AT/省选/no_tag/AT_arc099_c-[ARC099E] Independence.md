# [ARC099E] Independence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc099/tasks/arc099_c

AtCoder 連邦の高橋州には，$ N $ 個の都市があります．都市は $ 1,\ 2,\ ...,\ N $ と番号付けされています． これらの都市の間は，$ M $ 本の両方向に行き来可能な道で結ばれています． $ i $ 番目の道は都市 $ A_i $ と都市 $ B_i $ の間を結んでいます． どの道も，異なる都市間を結んでいます． また，どの都市間にも，それらを直接結ぶ道は高々 $ 1 $ 本しか存在しません．

ある時，高橋州は高州と橋州の $ 2 $ つの州に分かれることになりました． 高橋州の各都市は，分離後は高州もしくは橋州のいずれか片方に属することになります． ここで，すべての都市が高州，または橋州の一方のみに属してしまっても構わないことにします． このとき，次の条件を満たすようにしたいです：

- 高州，橋州のいずれにおいても，同じ州内では，どの $ 2 $ つの都市も **直接** 道で結ばれている．

両端の都市が同じ州内に属しているような道の本数として考えられるもののうち，最小のものを求めてください． ただし，条件を満たすように都市を高州，橋州に分けることが不可能なら，`-1` を出力してください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 700 $
- $ 0\ \leq\ M\ \leq\ N(N-1)/2 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\ \leq\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ i\ \neq\ j $ のとき，$ A_i\ \neq\ A_j $ または $ B_i\ \neq\ B_j $ の少なくとも片方が成立
- $ i\ \neq\ j $ のとき，$ A_i\ \neq\ B_j $ または $ B_i\ \neq\ A_j $ の少なくとも片方が成立

### Sample Explanation 1

例えば，高州に都市 $ 1,\ 2 $ を，橋州に都市 $ 3,\ 4,\ 5 $ を割り当てると，条件を満たします． このとき，両端の都市が同じ州内に属しているような道の本数は $ 4 $ になります．

### Sample Explanation 2

この例では，どのように都市を割り当てても，条件を満たすことができません．

## 样例 #1

### 输入

```
5 5
1 2
1 3
3 4
3 5
4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
5 1
1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 3
1 2
1 3
2 3```

### 输出

```
3```

## 样例 #4

### 输入

```
10 39
7 2
7 1
5 6
5 8
9 10
2 8
8 7
3 10
10 1
8 10
2 3
7 4
3 9
4 10
3 4
6 1
6 7
9 5
9 7
6 9
9 4
4 6
7 5
8 3
2 5
9 2
10 7
8 6
8 9
7 3
5 3
4 5
6 3
2 10
5 10
4 2
6 2
8 4
10 6```

### 输出

```
21```

# 题解

## 作者：pldzy (赞：8)

[Link:（洛谷）AT4162 [ARC099C] Independence](https://www.luogu.com.cn/problem/AT4162)

首先在此感谢 @[kymru](https://www.luogu.com.cn/user/243544) 大佬提供的学术支持。

## UPDATE

- 2022 - 10 - 17：更改了文章中一处表达有误的地方并补充完善了第一部分的说明。

## Solution
### 题意

给一张图，$N$ 个点，$M$ 条边，要求将图分成两个团，使得两个顶点都在同一个团中的边最少，求最小值。（团是一个两两之间有边的顶点集合。）

### 1

发现把所有节点分层两个团的本质就是对这些点进行黑白染色。设最后染成黑色的节点数为 $a$，白色的节点数为 $b$，则最终输出的答案即为 $\frac{a\times(a-1)+b\times(b-1)}{2}$。

发现直接对原图上手太复杂了，那些边也很难处理。所以考虑对原图建它的[**补图**](https://oi-wiki.org/graph/concept/#_12)。根据补图的定义，知道在补图中有一条边连接的两个节点在原图中不直接联通。所以，这样一来就把题目中“团是一个两两之间有边的顶点集合”转化为“集合内的节点两两不直接联通”。说到这里，显然，就变成将补图转化为一个二分图了。

需要注意的是，在对原图建了补图之后，可能会出现若干个连通块，即**连通块（二分图）的数量大于等于** $1$。

在一个二分图内，试将其某一部点都染成白色，另一部点都染成黑色。而这两部点就是答案所求的两个团各自的**一部分**。但是，原图的补图**会有多个二分图**，即不止一个连通块。那如何确定每一个二分图左右部点各自所染的颜色呢？

### 2

回过头，答案的最终形式是 $\frac{a\times(a-1)+b\times(b-1)}{2}$，运用简单小学数学知识，可以将**它的分子部分**转化为 $(a+b)\times(a+b-1)-2ab$，即 $n\times(n-1)-2ab$。再运用小学数学知识，知道“和一定，差小积大”，所以目标就变成让 $a$ 和 $b$ 的差尽可能小。

因此，在遍历一个连通块将其转化为一二分图的过程中，记录下每个二分图它的左右部点数量的差值，并全部相加，记为 $sum$。接着要做的就是适当分配这些差值（分成两部分 $x$ 和 $y$），使这两部分的和，它们两的差尽可能小。绕这么多，其实就是为了 $a$ 和 $b$ 的差尽可能小。

显然，我们想要 $x$ 和 $y$ 都尽可能接近 $\frac{sum}{2}$。这里运用到**最优性转可行性**的方法——背包 dp。

### 3

通过简单背包，可以求得 $x$ 和 $y$ 的最小差值，即 $a$ 和 $b$ 的最小差值。同时，已知 $a$ 与 $b$ 的和（即 $n$），组合起来，~~就又是一个小学数学知识~~，就成为了一个简单的和差问题。往下的解和差问题就不多说了。

至此，此题被完美解决，复杂度可过。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(register int i = a; i <= b; ++i)
#define per(i, a, b) for(register int i = a; i >= b; --i)
const int maxn = 705, maxm = 500005;
int n, m, sum;
bool flg, g[maxn][maxn], f[maxn];
int cnt, hd[maxn];
struct edge{
	int to, nxt;
}e[maxm];
int del[maxn], col[maxn], cur;
int u, v, tmp;

inline void add(int u, int v){
	e[++cnt] = (edge){v, hd[u]}, hd[u] = cnt;
}

inline void dfs(int u, int t){
	if(flg) return;
	del[t] += (col[u] == 1 ? 1 : -1);
	for(int v, i = hd[u]; i; i = e[i].nxt)
		if(!col[v = e[i].to])
			col[v] = 3 - col[u], dfs(v, t);
		else if(col[v] == col[u]){
			flg = 1; return;
		}
}

int main(){
	scanf("%d%d", &n, &m);
	rep(i, 1, m)
		scanf("%d%d", &u, &v), g[u][v] = g[v][u] = 1;
	rep(i, 1, n) rep(j, 1, n)
		if(!g[i][j] and i != j) add(i, j); 
	rep(i, 1, n){
		if(!col[i])
			col[i] = 1, dfs(i, ++cur),
			del[cur] = abs(del[cur]), sum += del[cur];
		if(flg){
			printf("-1\n"); return 0;
		}
	}
	f[0] = 1;
	rep(i, 1, cur) per(j, sum / 2, del[i])
		f[j] |= f[j - del[i]];
	per(i, sum / 2, 0) if(f[i]){
		tmp = i; break;
	}
	tmp = abs(sum - tmp * 2);
	int a = (n + tmp) >> 1, b = (n - tmp) >> 1;
	printf("%d\n", a * (a - 1) / 2 + b * (b - 1) / 2);
	return 0;
} 
```


------------
感谢阅读。

---

## 作者：皎月半洒花 (赞：8)

一道比较妙的题。首先考虑建出补图来，那么发现，如果有两个点连通，就说明不能分在一个子图里面，恰好是二分图染色的流程。

之后考虑按补图的连通块 $dp$。注意到如果补图中连通块 $A$ 和 $B$ 不连通，说明原图中所有点都连通。所以根本不需要考虑连通块之间的连边。具体的，设状态 $f_{i,j}$ 表示考虑了前 $i$ 个连通块，是否存在二分图集合的某一部（左部or右部）大小是 $j$ 。根据前面的性质这就是个背包。所以 `bitset` 优化转移一下即可。

```cpp
struct edge{
    int to ;
    int next ;
}E[N * N] ;

int res ;
int ctn ;
int n, m ;
int nienie ;
int vis[N] ;
int clr[N] ;
int cnt[2] ;
int head[N] ;
bool A[N][N] ;
bitset <N * N> ans ;

void add(int x, int y){
    to(++ ctn) = y ;
    next(ctn) = head[x] ;
    head[x] = ctn ;
}
void dfs(int x, int c){
    vis[x] = 1 ; clr[x] = c ; cnt[c] ++ ;
    for (int k = head[x] ; k ; k = next(k))
        if (!vis[to(k)]) dfs(to(k), c ^ 1) ;
        else if (clr[to(k)] == c) return nienie = 1, void() ;
}
int calc(int x){
    return x * (x - 1) + (n - x) * (n - x - 1) ;
}
int main(){
    cin >> n >> m ; ans[0] = 1 ;
    int u, v ; res = 1000000000 ;
    for (int i = 1 ; i <= m ; ++ i){
        scanf("%d%d", &u, &v) ;
        A[u][v] = A[v][u] = 1 ;
    }
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= n ; ++ j)
            if (!A[i][j] && (i ^ j)) add(i, j) ;
    for (int i = 1 ; i <= n ; ++ i){
        if (!vis[i]){
            cnt[0] = cnt[1] = 0 ; dfs(i, 0) ;
            ans = (ans << cnt[0]) | (ans << cnt[1]) ;
        }
    }
    if (nienie) return puts("-1"), 0 ;
    for (int i = 1 ; i <= n ; ++ i)
        if (ans[i]) res = min(res, calc(i)) ;
    return cout << res / 2 << endl, 0 ;
}

```

---

## 作者：LawrenceSivan (赞：5)

# AT4162 [ARC099C] Independence

## 前言：

最近降智太过严重，于是来写一些好 van♂ 的题。

妙题！

## 题意：

> 给定一张图。求将这张图分成两个完全子图后，最少会有多少条边的端点属于同一个完全子图。
>
> $n\leq 700$

回忆完全子图（团）的定义，要求一个团内两两之间必须连边。

考虑到我们需要把图分成两个团，在分别的团内部是需要完全连边的。

考虑建出补图。

由于两个团在各自内部完全连边，那么建出的补图中对于原来的团，一定不能有连边。唯一的连边只可能出现在跨越两个团的位置。

于是这就是二分图。

可以先对补图进行二分图染色，这样就可以判断无解。

考虑到原图中如果存在一个点向别的点没有连边的话，那么它在补图上一定存在连边。

于是补图上的孤立点一定是原图中向任意点都有连边的点。

于是这些点可以任意分配。

之后我们意识到二分图并不一定是联通的。

孤立点也算作很小的二分图。

于是我们需要组合一下几个联通块。

使用 DP 解决。

由于只是需要判断一下一个大小 $x$ 是否可以拼出来，可以使用 `std::bitset` 进行加速。

接下来的问题在于如何找到最小的答案。

假设染出的二分图左部点有 $x$ 个。

答案即为 

$$\dbinom{x}{2}+\dbinom{n-x}{2}$$

原因是经过了 DP，现在的二分图我们可以认为是联通的。

右部点个数一定是 $n-x$。

这样可以考虑到所有情况。

复杂度 $\mathcal{O(\dfrac{n^2}{\omega})}$

```cpp
//#define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register

const int maxn=705;
const int maxm=1;

int n,m,ans=INF;

int cnt1,cnt2;

int head[maxn],nxt[(maxn*maxn)<<1],to[(maxn*maxn)<<1],cnt;

inline void add(int u,int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}

bool g[maxn][maxn];

int vis[maxn];

bitset <705> f;

void dfs(int u,int fa,int color){
	if(vis[u]){
		if(vis[u]==color)return;
		if(vis[u]^color){
			puts("-1");
			exit(0);
		}
	}
	vis[u]=color;
	vis[u]==1?cnt1++:cnt2++;
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs(v,u,3-color);
	}
}

inline int calc(int x){
	return (x*(x-1)/2)+((n-x)*(n-x-1)/2);
}

namespace IO{
	template<typename T>
	inline void read(T &x){
		x=0;T f=1;char ch=getchar();
		while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
		while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
		x*=f;
	}

	template <typename T, typename... Args>
	inline void read(T& t, Args&... args){
		read(t); read(args...);
	}

	template<typename T>
	void write(T x){
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}

	template<typename T,typename... Args>
	void write(T t,Args... args){
		write(t);putchar(' ');write(args...);
	}
}

using namespace IO;

signed main(){
#ifdef LawrenceSivan
	freopen("aa.in","r", stdin);
	freopen("aa.out","w", stdout);
#endif
	read(n,m);
	for(re int i=1,u,v;i<=m;i++){
		read(u,v);
		g[u][v]=g[v][u]=true;
	}

	for(re int i=1;i<=n;i++){
		for(re int j=1;j<=n;j++){
			if(!g[i][j]&&i!=j){
				add(i,j);
				add(j,i);
			}
		}
	}

	f[0]=true;
	for(re int i=1;i<=n;i++){
		if(!vis[i]){
			cnt1=cnt2=0;
			dfs(i,0,1);
			for(re int j=n;~j;j--){
				bool t=false;
				if(j>=cnt1)t|=f[j-cnt1];
				if(j>=cnt2)t|=f[j-cnt2];
				f[j]=t;
			}
		}
	}

	for(re int i=0;i<=n;i++){
		if(f[i])ans=min(ans,calc(i));
	}

	write(ans),puts("");


	return 0;
}
```



---

## 作者：orz_z (赞：2)

### AT4162 [ARC099C] Independence

对于完全子图，考虑补图性质，即图内任意两个均无边。

若原图可分为两个完全子图，那么补图内子图无边，两子图间可有边，这不正是二分图吗？

染色判断奇环无解，求出每连通块答案，可行性 `DP` 计算答案即可。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int long long

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 705;

int n, m, cnt, ans, t[3], c[_], t1[_], t2[_];

bool mp[_][_], f[_][_];

int tot, head[_], to[_ * _], nxt[_ * _];

void add(int u, int v) {
	to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
	to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
}

void dfs(int u) {
	t[c[u]]++;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (c[v]) {
			if (c[u] == c[v]) {
				write(-1);
				exit(0);
			}
			continue;
		}
		c[v] = (c[u] == 1 ? 2 : 1);
		dfs(v);
	}
}

signed main() {
	n = read(), m = read(), ans = n * n;
	for (int i = 1, u, v; i <= m; ++i) {
		u = read(), v = read();
		mp[u][v] = mp[v][u] = 1;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			if (!mp[i][j]) add(i, j);
	for (int i = 1; i <= n; ++i)
		if (!c[i]) {
			cnt++, c[i] = 1, t[1] = t[2] = 0;
			dfs(i);
			t1[cnt] = t[1], t2[cnt] = t[2];
		}
	f[0][0] = 1;
	for (int i = 1; i <= cnt; ++i)
		for (int j = 0; j <= n; ++j)
			if (f[i - 1][j])
				f[i][j + t1[i]] = f[i][j + t2[i]] = 1;
	for (int i = 0; i <= n; ++i)
		if (f[cnt][i]) ans = min(ans, i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
	write(ans), he;
	return 0;
}
```



---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/AT4162)

从题意入手，$n$ 一定，要选出 $k,g$ 使 $k+g=n$ 且 $\dfrac{k(k-1)}2+\dfrac{g(g-1)}2$ 尽量小，那必然 $k$ 要尽量接近 $n$ 的一半。

然后就没啥性质了…吗？

不妨打开脑洞，考虑原图的补图。完全子图满足任意两点都有边，那么其补图必然满足任意两点必无边。

原图的补图可能是若干联通块，那我们分别考虑每个块的答案。如果一个块存在一个长度为奇数的环，这时无论怎样分都有同集的两个点存在连边，原问题无解。

不存在奇环…这不就是二分图吗？那么原问题的无解判定就是判断二分图的黑白染色法。

求出每个联通块的答案，然后使用可行性背包计算总共答案即可。

+ $dp_{i,j}\in\{0,1\}$ 表示已选到第 $i$ 个联通块，能不能满足选出 $j$ 个。
+ 初始化 $dp_{0,0}=1$
+ 记当前联通块二分图两边的大小分别为 $s1,s2$。若 $f_{i-1,t}=1$，则 $f_{i,t+s1}=f_{i,t+s2}=1$。
+ 最后答案是所有满足 $f_{k,i}$ 成立的 $i$，其中 $\dfrac{i\times(i-1)}2 +\dfrac{(n-i)\times(n-i-1)}2$ 的最小值


```cpp
const int N = 7e2 + 5;

int n,m,vis[N];
bool M[N][N],f[N][N]; int col[N];
int chk = 1,siz1,siz2;
vector<int> G[N];
int s1[N],s2[N],k = 0;

void dfs(int u,int c){
	if(col[u] && col[u] != c){ chk = 0; }
	if(col[u] || !chk) return;
	col[u] = c; c == 1 ? ++siz1 : ++siz2;
	for(int v : G[u]) dfs(v,3 - c);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		M[u][v] = M[v][u] = 1;
	}
	rep(i,1,n) rep(j,1,n) if(!M[i][j] && i != j) G[i].push_back(j);
	rep(i,1,n) if(!col[i]){
		siz1 = siz2 = 0; dfs(i,1);
		if(!chk){ return printf("-1\n"),0; }
		s1[++k] = siz1,s2[k] = siz2;
	}
	f[0][0] = 1;
	rep(i,1,k) rep(j,0,n) if(f[i - 1][j])
		f[i][j + s1[i]] = f[i][j + s2[i]] = 1;
	int res = INT_MAX;
	rep(i,0,n) if(f[k][i])
		res = min(res,i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：1)

~~vp 时一直没调出 T2，然后一眼秒了这题。建议评绿（bs）~~

考虑建反图（一个最大的不包含原图所有边的边集），则原图中的完全子图中的点在反图中两两间没有边直接相连。

对反图的每一个连通块进行二分图染色。如果染色失败就无解，否则：

设每一个连通块的两种颜色的点数差为 $d$，则需要把所有 $d$ 分成两组并最小化两组和的差值。对此做一个背包，以 $\dfrac{\sum d}{2}$ 作为背包容积即可。

时空复杂度 $\Theta(n^2)$。

Code:

```cpp
ll n,m,cnt,col[705],cur,s[705],f[705];bitset<705>c[705];
il bool dfs(ll x,ll cl)
{
	if(col[x])ret col[x]==cl;
	col[x]=cl;cur+=1-2*(cl==2);bool res=1;
	for(int i=1;i<=n;++i)if(c[x][i])res&=dfs(i,3-cl);
	ret res;
}
int main()
{
	n=rd();m=rd();for(int i=1;i<=n;++i)c[i].set(),c[i][i]=0;
	for(int i=1;i<=m;++i){ll u=rd(),v=rd();c[u][v]=c[v][u]=0;}
	for(int i=1;cur=0,i<=n;++i)if(!col[i])
		{if(!dfs(i,1))ret prt(-1),0;else s[++cnt]=uabs(cur);}
	ll sum=0;for(int i=1;i<=cnt;++i)sum+=s[i];
	f[0]=1;ll dlt=0;for(int i=1;i<=cnt;++i)
		for(int j=(sum>>1);j>=s[i];--j)f[j]+=f[j-s[i]];
	for(int i=(sum>>1);i>=0;--i)if(f[i]){dlt=i;break;}
	dlt=sum-dlt-dlt;
	ll a=(n-dlt)>>1,b=n-a;prt(a*(a-1)/2+b*(b-1)/2);
	ret 0;
}
```

---

## 作者：chenxia25 (赞：1)

我们注意到那些之间没有边的点对，它们显然必须异色，而且这个也显然是合法的充分条件。

于是我们对其补图判二分图。然后考虑如何求最小答案？对黑部 $x$ 个点，答案显然是 $\dbinom x2+\dbinom{n-x}2$。我们只需要求出哪些 $x$ 可以凑出来即可。

显然对于补图的每个连通分量只有两种染色方法，其一是 DFS 出来的那个，其二是反过来。于是我们可以类似背包，记录当前 $x$ 是否可以凑出来，然后对于每个连通分量就用两种值更新它。

然后现场我挂掉的原因是：DP 数组每轮不能直接或上两种决策，如果它本来就是 `true`，那么这个 `true` 不能算数。而 01 背包算数的原因是其中一种决策是 `dp[i-0]`。

复杂度平方，**_[code]( https://www.luogu.com.cn/paste/ra9ghbeb )_**。

---

