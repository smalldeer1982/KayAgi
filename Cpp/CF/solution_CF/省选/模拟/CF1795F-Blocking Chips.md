# Blocking Chips

## 题目描述

You are given a tree, consisting of $ n $ vertices. There are $ k $ chips, placed in vertices $ a_1, a_2, \dots, a_k $ . All $ a_i $ are distinct. Vertices $ a_1, a_2, \dots, a_k $ are colored black initially. The remaining vertices are white.

You are going to play a game where you perform some moves (possibly, zero). On the $ i $ -th move ( $ 1 $ -indexed) you are going to move the $ ((i - 1) \bmod k + 1) $ -st chip from its current vertex to an adjacent white vertex and color that vertex black. So, if $ k=3 $ , you move chip $ 1 $ on move $ 1 $ , chip $ 2 $ on move $ 2 $ , chip $ 3 $ on move $ 3 $ , chip $ 1 $ on move $ 4 $ , chip $ 2 $ on move $ 5 $ and so on. If there is no adjacent white vertex, then the game ends.

What's the maximum number of moves you can perform?

## 样例 #1

### 输入

```
5
5
1 2
2 3
3 4
4 5
1
3
5
1 2
2 3
3 4
4 5
2
1 2
5
1 2
2 3
3 4
4 5
2
2 1
6
1 2
1 3
2 4
2 5
3 6
3
1 4 6
1
1
1```

### 输出

```
2
0
1
2
0```

# 题解

## 作者：LJQ0808 (赞：20)

[传送门](https://www.luogu.com.cn/problem/CF1795F)

# 题解
我们可以发现答案具有单调性，因为如果步数是可行的，则比步数少的也是可行的；如果步数是不可行的，则比步数多的也是不可行的。

所以我们二分来解决此题。

直接做可能有点困难，因为我们无法确定一个点到底应该向上走更优还是向下走更优。所以我们可以对此树进行 DFS，对于每个节点，统计这个节点向下走至多能走多少步。

在递归返回时，如果当前节点有棋子，就进行分类：

1. 如果向下走能走的最大步数大于当前棋子还需要走的步数，就直接向下走。

2. 如果向下走能走的最大步数小于等于当前棋子还需要走的步数，就考虑向上走。

那贪心去向下走为什么一定是最优的？

因为递归返回时，一定是按照深度从大到小处理，即走到当前节点时，其子树中没有棋子，或者子树中的棋子都已经达成要求，而向下走只会影响子树中的节点，而对未处理的节点没有影响，所以能向下走时，向下走一定最优。

再加上二分算步数就解决了此题。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define print(x) cout<<#x<<"="<<x<<"\n"
const int N=2e5+5;
int n,k;
int a[N];
vector<int> g[N<<1];
void add_edge(int u,int v){
	g[u].push_back(v);
}
void add_und_edge(int u,int v){
	add_edge(u,v);add_edge(v,u);
}
int need[N],dep[N];//need[i] 记录点 i 需要走的步数，dep[i] 记录以点 i 为子树可以向下走的步数。 
bool vis[N];//vis[i] 记录点 i 有没有被儿子向上走。 
bool dfs(int u,int fa){//搜索。
	dep[u]=0;
	for(int v:g[u]){
		if(v==fa){
			continue;
		}
		if(!dfs(v,u)){//不合法。 
			return 0; 
		}
		if(!vis[v]){//v 有没有被儿子向上走。 
			dep[u]=max(dep[u],dep[v]+1);
		}
	} 
	if(dep[u]>=need[u]){//可以向下走的步数大于等于需要走的步数，说明合法。 
		return 1; 
	}
	//向下走的步数都不够需要走的步数，说明需要向上走。 
	if(!fa || vis[fa]){//若父亲为 0 或为有没有被儿子向上走。 
		return 0;//不合法。 
	} 
	vis[fa]=1;//fa 有被儿子 u 向上走。 
	need[fa]=need[u]-1;//更新。 
	need[u]=0;//清除。 
	return 1;//合法。 
} 
bool check(int x){//检查操作次数是否合法。 
	memset(vis,0,sizeof(bool)*(n+1));
	memset(need,0,sizeof(int)*(n+1));
	vis[0]=1;
	for(int i=1;i<=k;i++){
		vis[a[i]]=1;
		need[a[i]]=x/k;
	}
	int m=x%k;
	for(int i=1;i<=m;i++){
		need[a[i]]++;
	}
	return dfs(1,0); 
}
int ans=0;
void binary_search(){//二分操作次数。 
	int L=0,R=n;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)){
			ans=mid;
			L=mid+1;
		}
		else{
			R=mid-1;
		}
	}
}
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int tcase;
	cin>>tcase;
	while(tcase--){
		cin>>n;
		for(int i=1;i<n;i++){
			int x,y;
			cin>>x>>y;
			add_und_edge(x,y);
		}
		cin>>k;
		for(int i=1;i<=k;i++){
			cin>>a[i];
		}
		binary_search();
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++){
			g[i].clear();
		}
	} 
	return 0;
}
```

---

## 作者：Transparent (赞：19)

## 题目大意

- 给定一颗 $n$ 个节点的树，在 $k$ 个节点（ $a_1$ , $a_2$ , $a_3 \dots$ ）上分别有一个棋子

- 这 $k$ 个点最初是黑色的，其它的是白色的。你需要按 $a_1,a_2 \dots a_k,a_1,a_2,\dots$  的顺序依次移动这 $k$ 个棋子

- 棋子每次移动一格，移动的目标点不能是黑色，棋子经过的的点会被染成黑色

- 求至多能移动多少步

- $1 \leq k \leq n \leq 2 \times 10^5$

## 题解

正向考虑不方便，因为我们无法确定一个点到底应该向上走更优还是向下走更优。但是如果我们知道一个点需要移动多少步，就会好解决得多。

假设我们已知每个点的目标步数，那么可以任选一点作为根节点，对树进行 dfs，对于每个节点，统计这个节点向下走至多能走多少步。

在递归返回时，如果当前节点有棋子，就进行如下判断：

- 如果向下走能走的最大步数大于当前棋子还需要走的步数，就直接向下走

- 否则就尝试向上走到父节点，如果父节点已经是黑色或当前节点已经是树根，则表明这颗棋子不可能完成目标

优先向下走的贪心一定是正确的，因为递归返回时，一定是按照深度从大到小处理，即走到当前节点时，其子树中没有棋子，或者子树中的棋子都已经达成要求，而向下走只会影响子树中的节点，而对未处理的节点没有影响，所以能向下走时，向下走一定最优。


显然步数越多，要求越难以实现，二分答案即可。

时间复杂度 $O(n \log n)$

代码：


``` cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &res) {
	res=0;bool f=false;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=true; ch=getchar();}
	while(ch>='0'&&ch<='9') res=(res<<3)+(res<<1)+(ch^48),ch=getchar();
	res=f?-res:res;
}
template<typename T,typename ...Args>
void read(T &res,Args &...args) {read(res); read(args...);}
template<typename T>
void write(T x) {if(x<0) putchar('-'),x=-x; if(x>9) write(x/10); putchar(x%10+'0');}
template<typename T>
inline void writeln(T x) {write(x);putchar('\n');}
template<typename T,typename ...Args>
void write(T x,Args ...args) {write(x); putchar(' '); write(args...);}
template<typename T,typename ...Args>
void writeln(T x,Args ...args) {write(x); putchar('\n'); writeln(args...);}
#define MAXN 200001
class Edge {
public:
	Edge() {
		to=next=len=0;
	}
	int to,next,len;
};
class Graph {
public:
	Graph() {
		memset(g,0,sizeof(g));
		memset(head,0,sizeof(head));
		tot=0;
	}
	inline void clear(int n) {
		memset(head,0,sizeof(int)*(n+1));
		memset(g,0,sizeof(Edge)*(tot+1));
		tot=0;
	}
	inline void addEdge(int from,int to,int len) {
		g[++tot].to=to;g[tot].next=head[from];g[tot].len=len;head[from]=tot;
		g[++tot].to=from;g[tot].next=head[to];g[tot].len=len;head[to]=tot;
	}
	Edge g[MAXN<<1];
	int head[MAXN],tot;
}g;
int n,k,need[MAXN],dep[MAXN],a[MAXN];
bool vis[MAXN];
bool dfs(int u,int fa) {
	dep[u]=0;
	for(int i=g.head[u];i;i=g.g[i].next) {
		int v=g.g[i].to;
		if(v==fa) continue;
		if(!dfs(v,u)) return false;
		if(!vis[v]) dep[u]=max(dep[u],dep[v]+1);
	}
	if(dep[u]>=need[u]) {
		return true;
	}
	if(dep[u]<need[u]) {
		if(!fa||vis[fa]) return false;
		vis[fa]=true;
		need[fa]=need[u]-1;
		need[u]=0;
	}
	return true;
}
inline bool check(int len) {
	memset(vis,0,sizeof(bool)*(n+1));
	memset(need,0,sizeof(int)*(n+1));
	vis[0]=1;
	for(int i=1;i<=k;i++) {
		need[a[i]]=len/k;
		vis[a[i]]=true;
	}
	for(int i=1;i<=len%k;i++) {
		++need[a[i]];
	}
	return dfs(1,0);
}
inline void solve() {
	read(n);
	for(int i=1;i<n;i++) {
		int u=0,v=0;
		read(u,v);
		g.addEdge(u,v,1);
	}
	read(k);
	for(int i=1;i<=k;i++) {
		read(a[i]);
	}
	int l=0,r=n,res=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) {
			res=mid;
			l=mid+1;
		} else {
			r=mid-1;
		}
	}
	g.clear(n);
	writeln(res);
}
int main() {
	int T=0;
	read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：UperFicial (赞：3)

答案具有可二分性。

由于与 $n$ 和 $k$ 有关的 DP 在数据范围的约束下不太可能实现，所以考虑贪心。

然后发现答案具有单调性，考虑二分答案 $x$，可以求出每个棋子的移动次数。

考虑最底部的棋子，最优方案是往下移动，避免与上面的棋子产生冲突，并且移动到最深的叶子。

如果其不能移动到深度最深的叶子，那么只能往父亲上移动一格，然后当其父亲成为深度最深的棋子时，再向下移动，如此循环。

当然，如果移动不到父亲，显然是无解的。

考虑如何处理这件事情，设 $f_u$ 表示 $u$ 点是否有棋子，以及 $rev_u$ 表示 $u$ 还需要走多少步，$dep_u$ 表示 $u$ 向下走最远可走的距离。

三者都是可以自底向上推过来的。

由于还没有题解，我放一下代码：

```cpp
inline void dfs(int u,int fa)
{
	gra(i,u)
	{
		int v=edge[i].to;
		if(v!=fa)
		{
			dfs(v,u);
		    if(!flag[v]) dep[u]=Max(dep[u],dep[v]+1);//处理最远可走的距离 
		}
	}
	if(!flag[u]) return;//没有棋子无需处理 
	if(rev[u]<=dep[u])//可以在子树内自行解决 
	{
		rev[u]=0;
		return;
	}
	if(!flag[fa])//否则，需要移动到父亲，判断父亲是否有棋子 
	{
		flag[fa]=true;//将父亲设成有棋子 
		rev[fa]=rev[u]-1;//移动了一次，父亲需要移动 rev-1 次 
		rev[u]=0;
	}
	return;
}

inline bool check(int x)
{
	flag[0]=true;
	rep(i,1,n) flag[i]=false,dep[i]=0,rev[i]=0;
	rep(i,1,k) rev[a[i]]=x/k+(i<=x%k),flag[a[i]]=true;
	dfs(1,0);
	rep(i,1,n) if(rev[i]) return false;
	return true;
}

inline void solve()
{
	memset(edge,0,sizeof(edge));
	memset(head,0,sizeof(head));
	tot=0;
	n=read();
	rep(i,2,n)
	{
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	k=read();
	rep(i,1,k) a[i]=read();
	int l=0,r=n,res=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",res);
	return;
} 
```

---

## 作者：thostever (赞：2)

考虑到对于一个确定的答案，每个棋子走的步数也是确定的。

那么我们便可以考虑二分答案。因为如果当前总步数能够实现，那么更小的也一定能实现。

我们考虑以 $1$ 为根。

先考虑最下面的点。如果它能够往下走，那么它一定会往下走（这样更优）。否则我们只能走到它的父亲，并等到递归到它父亲时再继续安排路径。

具体细节：

我们对于每个点 $u$ 求一个能够往下走的最深的深度 $dwn_u$，有 $(v\in son_u \& col_v=white)dwn_u=\max (dwn_v+1)$。

每个点存一个 $a_i$ 表示它还需要走 $a_i-1$ 步。若 $a_i=0$ 则表示这个点是白色，否则就是黑色。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int head[200010],to[400010],nxt[400010],tot=0;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int b[200010];
int a[200010];
int dwn[200010];
bool flag=0;
void dfs(int u,int f)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		dfs(v,u);
		if(!a[v]) dwn[u]=max(dwn[u],dwn[v]+1);
	}
	if(a[u]>=2&&dwn[u]<a[u]-1)
	{
		if(!a[f]) a[f]=a[u]-1;
		else flag=1;
	}
}
bool check(int x)
{
	flag=0;
	for(int i=1;i<=n;i++) a[i]=0,dwn[i]=0;
	for(int i=1;i<=m;i++) a[b[i]]=int(x/m)+bool(i<=x%m)+1;
	dfs(1,1);
	return !flag;
}
void solve()
{
	tot=0; for(int i=1;i<=n;i++) head[i]=0;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	int l=0,r=n+1,ans;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid;
	}
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
/*

*/
```


---

## 作者：masonpop (赞：1)

如果刚开始考虑每个点怎么走较为麻烦，我们考虑反向考虑：已知每个点需要走多少步，贪心的考虑怎么走最优。不妨先给树确定一个根，就假设是点 $1$ 吧。

容易发现，答案是具有单调性的，因此可以二分。这样可以算出每个点需要走的步数。在对应的位置存下来，点 $i$ 存的 $step_i$ 就表示在该位置的点需要走的步数（若没有点则 $step_i=0$）。并且，所有点能往下尽量往下走一定是最优选择，这个贪心策略不难证明。

接下来就可以自下而上移动点了。首先简单树形 $dp$ 一下，设 $f_i$ 表示 $i$ 位置上的点能往下走的最大步数。用 $col$ 数组表示当前点的颜色（黑色表示走过，即 $1$）。那么 $f_i=\max\limits_{j\in son_i,col_j=0}\{f_j+1\}$。 

那么，如果需要的步数小于等于能往下的最大步数就直接下去了，不用管了。否则，我们先将它移到父节点，在回溯上去的时候继续考虑。

时间复杂度 $O(n\log n)$。洛谷 RMJ 坏了，可以看这个 CF 的提交记录。[代码](https://codeforces.com/contest/1795/submission/212219168)。

---

## 作者：postpone (赞：0)

考虑二分答案。

每个棋子，它只能往一个方向走，不能回头，因为它走的地方会染黑。那我们贪心地想，如果它的下方有足够的空间，直接往下走就行；否则就只能往上走，如果往上空间也不够，那就不可行了。

实现并不好想，这里用树形 dp 来做。

以 $dp_u$ 表示 $u$ 这个点以及它的下方的“余裕”。初始地，如果 $u$ 是要移动的，那它的“余裕”是负的——也就是说“欠债”了。在转移时，要处理以下几点。

- 儿子欠债了，将它的欠债转移过来，并判断是不是已经不能再走了；
- 儿子没欠债，那就要把它的余裕转移过来；
- 最后再看自身的欠债和空间，来表明自己的状态。

核心代码如下。
```cpp
auto check = [&](int x) {
    vector<int> f(n, -1); // 预处理要走几次，如果一次都不用走，就是 -1，表示其他点能借到这里。
    for (int i = 0; i < k; i++) {
        f[a[i]] = x / k + (i < (x % k));
    }

    vector<int> dp(n);
    bool ok = true;

    auto dfs = [&](auto &&self, int u, int fa) -> void {
        int neg = -f[u]; // 这个点的“余裕”
        int max = 0; // 这个点往下的空间
        for (auto v : adj[u]) {
            if (v == fa) {
                continue;
            }
            self(self, v, u);

            if (dp[v] < 0) { // 如果它儿子得往上走
                ok &= (neg > 0); // 它自己没有任何余裕，那就不行
                neg = dp[v] + 1; // 否则就把它儿子的“欠债”转移过来
            } else {
                max = std::max(max, dp[v]); // 如果它儿子没有欠债，那就更新它下面的最大空间
            }
        }

        // 对这个点自己的处理
        if (neg <= 0) {
            if (neg + max >= 0) { // 如果欠债了但是下面的空间足够，直接往下走就行
                dp[u] = 0;
            } else {
                dp[u] = neg;
            }
        } else {
            dp[u] = max + 1;
        }
    };
    dfs(dfs, 0, -1);

    ok &= (dp[0] >= 0);
    return ok;
};
```
[完整代码](https://codeforces.com/contest/1795/submission/312839646)

---

## 作者：Unnamed114514 (赞：0)

注意到你直接构造没有什么好的贪心策略，于是考虑二分答案，转化为判定性问题。

我们 $f_u$ 维护 $u$ 的信息：

- 若 $f_u<0$，表示 $u$ 子树内存在一个点，从 $u$ 出发，还要走 $-f_u$ 步才能达到限制。

- 若 $f_u\ge0$，表示 $u$ 子树内存在一条长度为 $f_u$ 的空链可以走。

我们先来考虑不合法的情况：

- 若 $u$ 存在两个儿子 $v$ 满足 $f_v<0$，那么就直接寄掉。

- 如果 $u$ 初始被占用且存在 $u$ 的儿子 $v$ 满足 $f_v<0$，那么也寄了。

然后我们再来考虑 $f_u$ 的转移：

- 若存在 $u$ 的儿子 $v$，满足 $f_v<0$，那么 $u$ 显然会被占用，不会从父亲下来，所以子树内部能解决（$\max\{f_v\}+1\ge-f_v$）显然就在内部解决，此时 $f_u\gets0$；否则就要通过 $fa_u$ 来解决，即 $f_u\gets f_v+1$。

- 否则子数内都能走，即 $f_u\gets\max\{f_v\}+1$。

合法的判定显然是所有的限制都满足，即 $f_1\ge0$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2e5+5;
int T,n,k,a[N],b[N],f[N],id[N];
vector<int> G[N];
bool flg;
void dfs(int u,int fa){
	if(flg) return;
	bool chk=0;
	int mx=-0x3f3f3f3f;
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
		mx=max(mx,f[v]);
		if(f[v]<0){
			if(chk){
				flg=1;
				return;
			}
			chk=1;
		}
	}
	if(chk&&id[u]){
		flg=1;
		return;
	}
	if(id[u]){
		if(mx>=0&&mx>=b[id[u]]) f[u]=0;
		else f[u]=-b[id[u]];
	} else if(chk){
		if(mx<0) f[u]=mx+1;
		else{
			for(auto v:G[u]){
				if(v==fa) continue;
				if(f[v]<0){
					if(-f[v]<=mx+1) f[u]=0;
					else f[u]=f[v]+1;
				}
			}
		}
	} else{
		if(mx<0) f[u]=1;
		else f[u]=mx+1;
	}
}
bool check(int mid){
	flg=0;
	for(int i=1;i<=n;++i) b[i]=mid/k+(i<=mid%k);
	dfs(1,0);
	return !flg&&f[1]>=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1,u,v;i<n;++i){
			cin>>u>>v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		cin>>k;
		for(int i=1;i<=k;++i) cin>>a[i],id[a[i]]=i;
		int l=0,r=n;
		while(l<r){
			int mid=l+r+1>>1;
			if(check(mid)) l=mid;
			else r=mid-1;
		}
		cout<<r<<endl;
		for(int i=1;i<=k;++i) id[a[i]]=0;
		for(int i=1;i<=n;++i) G[i].clear(),G[i].shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：pyiming (赞：0)

# 题意简述

题目描述了一个游戏，在一棵有 $ n $ 个节点的树上，有 $ k $ 个棋子分别放在不同的节点上。游戏开始时，这些节点被标记为黑色，其余节点为白色。游戏规则是，每秒移动一个棋子到相邻的白色节点，并将该节点标记为黑色。如果某个棋子没有可以移动的白色节点，游戏结束。要求计算最多可以进行多少次移动。

# 解题思路

直接做这题好像不太好做。

尝试二分答案，将最优性问题转化为判定性问题。

这样先钦定 $k$ 个棋子分别能移动 $v_i$ 次，考虑是否可行。对于一个棋子 $i$，其移动路径显然是从 $a_i$ 出发到任意结点的简单路径，那显然只有两种情况：

1. 从 $a_i$ 出发到经过父亲

2. 从 $a_i$ 出发到不经过父亲

先考虑不经过父亲的做法，可以记 $f(i)$ 表示从 $i$ 出发到其任意后代最多能够移动多少次。

写出转移方程 $f(i)=\max_{j\in son_i}(f(j)+1)$。显然，若 $i$ 为叶结点 $f(i)=0$。若 $i$ 上有一个棋子，先判断该棋子到其后代能否移动 $v_i$ 次（即 $v_i\le f(i)$），再令 $f(i)=-1$。

再考虑经过父亲的做法。注意到，如果一个棋子到其后代能移动 $v_i$ 次，则必定不会从 $v_i$ 出发经过父亲，因为不经过父亲显然比经过父亲的后效性小且更优。

那么对于到其后代不能移动 $v_i$ 次的棋子，则可以认为其要向父亲结点移动，可以将其父亲结点标记为棋子，其 $v_{new}=v_i-1$。这个新棋子显然可以再分为经过父亲和不经过父亲，那么就可以在 $\text{dp}$ 的同时转移棋子，这样就解决了该问题。

显然二分答案时间复杂度为 $O(\log n)$，判定时的 $\text{dp}$ 时间复杂度为 $O(n)$。总为 $O(n\log n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5;
vector<int> edge[N+2];
int a[N+2];
int v[N+2];
int f[N+2],g[N+2];
int n,k;
void dfs(int u,int fa){
    f[u]=1;
    g[u]=0;
    vector<int> t;
    if(v[u]!=-1) t.push_back(v[u]);
    for(int v:edge[u]) if(v!=fa){
        dfs(v,u);
        f[u]&=f[v];
        if(g[v]+1<0){
            t.push_back(-(g[v]+2));
        }
        g[u]=max(g[u],g[v]+1);
    }
    if(t.size()>1){
        f[u]=0;
        return;
    }
    if(!t.empty()){
        int temp=*t.begin();
        if(temp>g[u]){
            g[u]=-temp-1;
        }
        else{
            g[u]=-1;
        }
    }
}
bool check(int mid){
    for(int i=1;i<=n;i++){
        v[i]=-1;
    }
    int t1=mid/k,t2=mid-t1*k;
    for(int i=1;i<=k;i++){
        v[a[i]]=t1+(i<=t2);
    }
    dfs(1,0);
    return f[1]&&g[1]+1>=0;
}
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            edge[i].clear();
        }
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        cin>>k;
        for(int i=1;i<=k;i++){
            cin>>a[i];
        }
        int l=0,r=n-k;
        while(l<r){
            int mid=(l+r+1)>>1;
            if(check(mid)){
                l=mid;
            }
            else{
                r=mid-1;
            }
        }
        cout<<l<<"\n";
    }
    return 0;
}
```

---

## 作者：TernaryTree (赞：0)

显然是选若干点不相交链。显然具有单调性。二分。于是转成判定问题。

假设二分到 $x$。先计算出每个点需要走几步。dfs。因为是 dfs，我们应该让一个点尽可能往下走，不去影响上面的点。于是计算出在子树满足条件的情况下最多能往下面走多少。

假设现在这个点有 $tag_u$ 表示需要找一条从 $u$ 开始的长度为 $tag_u$ 的链（$tag_u=-1$ 表示 $u$ 没有需求）。设这个点能往下走 $mx_u$。

如果 $tag_u\le mx_u$ 那么就直接往下走。但是上面的不能走到这里了，上面的 $mx$ 会被影响。所以令当前点 $mx_u=tag_u=-1$，这样相当于父亲在进行 $mx_u\gets\max(mx_u,mx_v+1)$ 时不会更新这个叶子。

否则得往上走。我们向父亲返回一个 $tag_u-1$ 表示还需要走这么多（如果是根，返回无解）。一个父亲在 dfs 儿子的过程中如果接收到 $\gt 1$ 个有效需求，那么是无法满足的，此时判定无解；否则用这个需求所在的 $v$ 以外的所有儿子 $v$ 更新 $mx_u$，然后继续仿照上述过程判定即可。

$\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r + 1) >> 1)
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

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n, k;
vector<int> tr[maxn];
int a[maxn], tag[maxn];
int mx[maxn];
bool fl = 1;

int dfs(int u, int fa) {
	for (int v : tr[u]) {
		if (v == fa) continue;
		int tmp = dfs(v, u);
		if (tmp != -1) {
			if (tag[u] != -1) fl = 0;
			tag[u] = tmp;
			continue;
		}
		mx[u] = max(mx[u], mx[v] + 1);
	}
	if (tag[u] == -1) return -1;
	if (tag[u] <= mx[u]) {
		mx[u] = -1;
		tag[u] = -1;
	} else {
		if (fa) return tag[u] - 1;
		else fl = 0;
	}
	return -1;
}

bool check(int x) {
	rep(i, 1, n) tag[i] = -1, mx[i] = 0;
	rep(i, 1, k) tag[a[i]] = x / k + (i <= x % k);
	fl = 1;
	dfs(1, 0);
	return fl;
}

void fake_main() {
	n = read();
	rep(i, 1, n - 1) {
		int u = read(), v = read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	k = read();
	rep(i, 1, k) a[i] = read();
	int l = 0, r = 1e9;
	while (l < r) {
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	write(l), pc('\n');
	rep(i, 1, n) tr[i].clear(), tag[i] = 0;
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：happybob (赞：0)

可以发现，答案一定是可二分的。

那么我们思考如何判定。首先，对于一个点，在一棵 DFS 树上，它只有两种走法。要么往下走，要么走到祖先的某个点，然后考虑能否往下。

于是我们可以设计一个 DP，$f_u$ 表示 $u$ 点能往下的最大长度。$f_u = \max \limits_{c_j = 0}\{f_j+1\}$。$c_j$ 表示 $j$ 能否走，$c_j =0$ 表示能走。

对于一个点，先处理 $f_u$，如果 $f_u \geq need_u$，那么直接往下走，不影响上面的显然最优。

否则，$c_{fa}=1$，并且将 $need_{fa}$ 更改。如果发现 $fa$ 本身就不能走直接退出。

我们从下往上处理，所以对于每个点，肯定优先往下走最好。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

int t, n, k, a[N];
vector<int> G[N];

int need[N], can[N], f[N];
bool col[N];
bool flag = 1;

void dfs(int u, int fa)
{
	for (auto& j : G[u])
	{
		if (j != fa)
		{
			dfs(j, u);
			if (!col[j]) f[u] = max(f[u], f[j] + 1);
		}
	}
	if (col[u])
	{
		if (f[u] < need[u])
		{
			if (col[fa] || fa == 0)
			{
				flag = 0;
				return;
			}
			col[fa] = 1;
			need[fa] = need[u] - 1;
		}
		f[u] = 0;
	}
}

bool check(int x)
{
	flag = 1;
	for (int i = 1; i <= n; i++) need[i] = 0, f[i] = 0, col[i] = 0;
	for (int i = 1; i <= k; i++) col[a[i]] = 1;
	for (int i = 1; i <= k; i++)
	{
		need[a[i]] = x / k + (x % k >= i);
	}
	dfs(1, 0);
	return flag;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit(), col[i] = need[i] = f[i] = 0;
		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		scanf("%d", &k);
		for (int i = 1; i <= k; i++)
		{
			scanf("%d", &a[i]);
			col[a[i]] = 1;
		}
		int l = 0, r = n, ans = 0;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid))
			{
				l = mid + 1;
				ans = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

