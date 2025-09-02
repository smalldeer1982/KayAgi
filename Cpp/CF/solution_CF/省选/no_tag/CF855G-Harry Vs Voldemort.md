# Harry Vs Voldemort

## 题目描述

After destroying all of Voldemort's Horcruxes, Harry and Voldemort are up for the final battle. They each cast spells from their wands and the spells collide.

The battle scene is Hogwarts, which can be represented in the form of a tree. There are, in total, $ n $ places in Hogwarts joined using $ n-1 $ undirected roads.

Ron, who was viewing this battle between Harry and Voldemort, wondered how many triplets of places $ (u,v,w) $ are there such that if Harry is standing at place $ u $ and Voldemort is standing at place $ v $ , their spells collide at a place $ w $ . This is possible for a triplet only when $ u $ , $ v $ and $ w $ are distinct, and there exist paths from $ u $ to $ w $ and from $ v $ to $ w $ which do not pass through the same roads.

Now, due to the battle havoc, new paths are being added all the time. You have to tell Ron the answer after each addition.

Formally, you are given a tree with $ n $ vertices and $ n-1 $ edges. $ q $ new edges are being added between the nodes of the tree. After each addition you need to tell the number of triplets $ (u,v,w) $ such that $ u $ , $ v $ and $ w $ are distinct and there exist two paths, one between $ u $ and $ w $ , another between $ v $ and $ w $ such that these paths do not have an edge in common.

## 说明/提示

In the first sample case, for the initial tree, we have $ (1,3,2) $ and $ (3,1,2) $ as the only possible triplets $ (u,v,w) $ .

After addition of edge from $ 2 $ to $ 3 $ , we have $ (1,3,2) $ , $ (3,1,2) $ , $ (1,2,3) $ and $ (2,1,3) $ as the possible triplets.

## 样例 #1

### 输入

```
3
1 2
2 3
1
2 3
```

### 输出

```
2
4
```

## 样例 #2

### 输入

```
4
1 2
2 3
2 4
2
1 4
3 4
```

### 输出

```
6
18
24
```

## 样例 #3

### 输入

```
5
1 2
2 3
3 4
4 5
1
1 5
```

### 输出

```
20
60
```

# 题解

## 作者：NOI_Winner (赞：2)

本题需要动态维护边双连通分量并统计符合条件的三元组数量。

先考虑一开始的树的答案怎么统计，可以发现从 $w$ 的角度去统计答案较为方便，设与 $x$ 相连的点的集合为 $S_x$，若整棵树以 $x$ 为根 $y$ 的子树的大小为 $sz_{x,y}$，那么答案即为：
$$
    \sum_{x=1}^n\sum_{u\in S_x}\sum_{v\in S_x,u\neq v}sz_{x,u} \cdot sz_{x,v} =\sum_{x=1}^n((\sum_{u\in S_x}sz_{x,u})^2-\sum_{u\in S_x}sz_{x,u}^2)
$$

如果要动态加边，我们可以在加边时将树上对应的一段路径上的所有点合并，并使用并查集维护已合并的节点，将已经合并的节点用最顶端的节点代替，就得到了边双连通分量缩点后的树。我们设原树为以 $1$ 为根的有根树，设 $son_x$ 表示 $x$ 的儿子节点集合，$s1_x$ 表示 $x$ 的所有儿子子树大小和，$s2_x$ 表示 $x$ 的所有儿子子树大小平方和，$cnt_x$ 表示 $x$ 代表的边双连通分量中的节点数，$cur_x$ 表示以 $x$ 中某个点为中间节点的合法三元组数量，我们需要动态维护这四个值，即：
$$
s1_x=\sum_{u\in son_x}sz_x \\
s2_x=\sum_{u\in son_x}sz_x^2 \\
cur_x=cnt_x(cnt_x-1)(cnt_x-2)+2cnt_x(cnt_x-1)(n-cnt_x)+(s1+n-sz_x)^2-s2_x-(n-sz_x)^2
$$

同时我们动态维护答案就行了。

代码示例：
```cpp
#include <iostream>

using namespace std;

using ll = long long;
constexpr int maxn = 100000, maxk = 16;
int head[maxn + 5], vert[2 * maxn + 5], nxt[2 * maxn + 5], tot;
int fa[maxn + 5][maxk + 5], top[maxn + 5], sz[maxn + 5], cnt[maxn + 5], dep[maxn + 5];
ll s1[maxn + 5], s2[maxn + 5], cur[maxn + 5];

inline void add(int x, int y)
{
    vert[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

int get(int x)                      //  并查集
{
    if (x == top[x]) return x;
    return top[x] = get(top[x]);
}

void dfs(int x, int f)             //  预处理
{
    dep[x] = dep[f] + 1; fa[x][0] = f;
    sz[x] = cnt[x] = 1;
    for (int i = 1; i <= maxk; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    
    for (int i = head[x]; i; i = nxt[i])
    {
        int y = vert[i];
        if (y == f) continue;
        dfs(y, x); sz[x] += sz[y];
        s1[x] += sz[y]; s2[x] += 1ll * sz[y] * sz[y];
    }
}

int lca(int x, int y)           // 求 LCA
{
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxk; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y) return x;
    for (int i = maxk; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
        { x = fa[x][i]; y = fa[y][i]; }
    return fa[x][0];
}

inline ll calc2(int n)
{ return 1ll * n * (n - 1); }

inline ll calc3(int n)
{ return 1ll * n * (n - 1) * (n - 2); }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        top[i] = i;
        if (1 == i)
            cur[i] = s1[i] * s1[i] - s2[i];
        else
            cur[i] = (s1[i] + n - sz[i]) * (s1[i] + n - sz[i]) - s2[i] - 1ll * (n - sz[i]) * (n - sz[i]);
        ans += cur[i];
    }
    cout << ans << endl;           //   预处理最初的答案
    
    int q; cin >> q;
    while (q--)
    {
        int x, y; cin >> x >> y;
        int f = get(lca(x, y));
        x = get(x); y = get(y);
                
        ll cs1 = 0, cs2 = 0; int c = 0;
        while (x != f)           //   cs1,cs2,c 分别为新计算的 s1,s2,cnt
        {
            cs1 += s1[x] - sz[x];
            cs2 += s2[x] - 1ll * sz[x] * sz[x];
            c += cnt[x]; ans -= cur[x];
            int cf = get(fa[x][0]);
            top[x] = cf; x = cf;
        }
        while (y != f)
        {
            cs1 += s1[y] - sz[y];
            cs2 += s2[y] - 1ll * sz[y] * sz[y];
            c += cnt[y]; ans -= cur[y];
            int cf = get(fa[y][0]);
            top[y] = cf; y = cf;
        }
        cs1 += s1[f]; cs2 += s2[f];
        c += cnt[f]; ans -= cur[f];
        s1[f] = cs1; s2[f] = cs2; cnt[f] = c;     //  更新答案
        cur[f] = calc3(c) + 2 * calc2(c) * (n - c) + ((cs1 + n - sz[f]) * (cs1 + n - sz[f]) - cs2 - 1ll * (n - sz[f]) * (n - sz[f])) * c;
        cout << (ans += cur[f]) << endl;
    }
    
    return 0;
}
```

---

## 作者：hamster000 (赞：1)

Update：我重学tarjan算法之后，对注释做了一些修订。

先上代码：代码注释里面讲的很详细，我觉得不需要过多额外讲解。

注意：本题解的码风奇特，变量定义方式奇特，不建议与其他题解混合食用。

本题解不需要求解最近公共祖先，常数较小。使用输入输出流而非快速读入，常数较大，（有点自相矛盾了属于是）。

本题解思路参考了多篇题解（包括站外题解），算是兼收并蓄了。但是有我对这些题解的一些注释、翻译、笔记。我觉得题解区的题解有点难以理解，故放上这篇题解。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
const int maxn=1e5+10;
int siz[maxn],dep[maxn],f[maxn];//经典三件套就不多说了
int siz_t[maxn],fa[maxn];//并查集的size
vector<int> vec[maxn];
long long sum[maxn];//子树平方和
long long ans=0;
void count(int x,int op){//函数作用：计算当点w在边双x中时的方案数，并累加进入答案
	//当两个边双连通分量合并时，先减去它们分别的贡献，再加上合并之后的贡献，得到新的贡献。
	ans+=op*(siz_t[x]*(siz_t[x]-1)*(siz_t[x]-2));
	ans+=2*op*(siz_t[x]*(siz_t[x]-1))*(n-siz_t[x]);
	ans+=op*siz_t[x]*((n-siz_t[x])*(n-siz_t[x])-sum[x]-(n-siz[x])*(n-siz[x]));
	//解释一下：对于第三种情况，w点在这个边双内部任取
	//而剩下两个点在其他地方任取。
	//但是，这两个点不能在同一子树内（与此同时也自动排除了这两个点相同的可能性）
	//于是必须减去所有子树的平方和，再减去父亲方向子树的平方和（也就是n-siz[x]的平方）
	//分别对应：三个点都在一个边双里面
	//两个点在这个边双里面，另一个点不在，此时可以是u在，也可以是v在，故需要加倍。
	//一个点在边双里面，另外两个不在
	//注意到第三种情况，u，v不能在同一子树内。
	//故必须减去包括父亲方向的所有子树平方和。
}
void dfs(int u,int fa){
	f[u]=fa;//记录边双树上每个节点的父节点。
	dep[u]=dep[fa]+1,siz[u]=1;
	siz_t[u]=1;
	for(auto to:vec[u]){
		if(to==fa) continue;
		dfs(to,u);
		siz[u]+=siz[to];
		sum[u]+=siz[to]*siz[to];//预处理每个子树的平方和。
	}
	count(u,1);//计算每个节点作为w的贡献，累加答案。
}/*
void calc(){
	for(int i=1;i<=n;i++){
		ans+=(n-1)*(n-1);
		ans-=(n-siz[i])*(n-siz[i]);
		for(auto to:vec[i]){
			if(to==f[i]) continue;
			ans-=siz[to]*siz[to];
		}
	}
}*/
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}

int query(int x) {
	return fa[x]==x? x:fa[x]=query(fa[x]);//经典路径压缩
}
void merge(int x,int y){//函数作用：当边(x,y)连接两个边双时，需要把边双树上(x,y)所在边双的链上的边双分别合并。
	//但是如果求lca，常数巨大，故不断把深度大的边双合并直到这两个边双其中一个合并到了之前合并过的边双。
	//容易证明这个边双就是边双树上的lca。
	//fa记录边双的头部，深度最小的点。
	count(x,-1),count(y,-1);
	//先去掉x和y的贡献
	siz_t[y]+=siz_t[x],sum[y]=sum[x]+sum[y]-siz[x]*siz[x];
	//考虑边双树上两个点合并
	//x原本是y的儿子，现在不是了。
	//x的儿子原本不是y的儿子，现在是了。
	count(y,1),fa[x]=y;//需要保证y的深度比x小。
	//计算合并后的贡献
	//我们可以从后面知道，x是y的儿子
	//所以当x，y合并后，x就必须从y的
	//儿子的平方和里去掉
	//但与此同时，x又成为了y的儿子。
	//sq代表这个节点所有儿子的
	//子树大小平方和
}
//容易想到，枚举w
//对于一棵树，当且仅当u，v在同一子树中时
//三元组不合法（必经过w到某个儿子的边）
//否则三元组可以任意选定
//于是，dfs预处理出所有子树的siz即可。
//对于父亲方向的子树，siz=n-siz[u]
signed main(){
	cin >> n;
	for(int i=1;i<n;i++){
		int x,y;
		cin >> x >> y;
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	dfs(1,0);
	//calc();
	cout << ans << endl;
	cin >> q;
	init();
	while(q--){
		//TODO
		int x,y;
		cin >> x >> y;
		while(query(x)!=query(y)){
			x=query(x),y=query(y);
			if(dep[x]<dep[y]){
				swap(x,y);
			}
			merge(x,query(f[x]));//把这个边双和它的父亲合并。
			//把一条链上的所有边双合并
			//可以看作是不断把深度大的和父亲合并
			//直到把这条链合并完成。
			//每次都是网上合并，最后合并到的边双
			//顶部就是x，y的LCA。
		}
		cout << ans << endl;
	}
}
```

思路的难点是想到三元组中确定了 $w$ 就可以很容易计算三元组的数量。

然后分情况讨论，三个点所在的边双情况。先考虑一棵树的情况，我们知道对于一棵树，选择的 $u,v$ 不能在 $ w$ 的同一个子树内，否则必然经过同一条边，除此之外其他情况均为合法。于是想到预处理所有子树大小的平方和（总数减平方和减父亲方向子树大小的平方即为答案）。

然后发现，对于一张无向图，边双缩点之后必然是一棵树。于是套用树的方式，但是此时需要乘上一个系数，即 $w$ 可以在这个边双中任意选，同时 $u,v$ 可以在整个图上任意选，但是不能选到同一个边双子树中。

容易想到三个点全部都在一个边双里面必然是合法的，两个点在一个边双中，则另一个点任意取也是合法的（注意边双定义，如果不存在路径不相交，删除相交的那条边则会导致不连通，故不存在），且此时 $u,v$ 可以交换，故答案需要翻倍。

三个点如果分散到三个边双，就有可能出现两个点在同一子树的情况下发生，此时相当于两个点任意选并减去不合法数量，即所有子树平方和加上父亲方向子树大小的平方。

推理过程结束。

---

## 作者：IdnadRev (赞：1)

某卷怪大 H 在研学的时候教我的。	

考察缩边双后变成的树，枚举 $w$ 所在边双为根，那么 $u,v$ 不能在 $w$ 同一子树内。

于是能列出一个边双对应贡献，只需提前记录每个点每个儿子子树大小平方和，使用 [oiwiki-并查集应用
-G](https://oi-wiki.org/topic/dsu-app/) 里的并查集维护边双以及贡献即可。

复杂度 $O(n\log n)$。

代码：
```cpp
#include<stdio.h>
#include<vector>
using namespace std;
const int maxn=100005;
int n,q;
int f[maxn],sz[maxn],fa[maxn],siz[maxn],dep[maxn];
long long ans;
long long sq[maxn];
vector<int>v[maxn];
int find(int x) {
	return f[x]==x? x:f[x]=find(f[x]);
}
void calc(int x,int opt) { //first=x
	ans+=1ll*opt*sz[x]*(sz[x]-1)*(sz[x]-2);//3 in ecc
	ans+=2ll*opt*sz[x]*(sz[x]-1)*(n-sz[x]);//2 in ecc 1 out ecc
	ans+=1ll*opt*sz[x]*(1ll*(n-sz[x])*(n-sz[x])-sq[x]-1ll*(n-siz[x])*(n-siz[x]));//1 in ecc 2 out ecc(except 2 same in,2 same out)
}
void merge(int a,int b) {
	calc(a,-1),calc(b,-1);
	sz[b]+=sz[a],sq[b]=sq[b]+sq[a]-1ll*siz[a]*siz[a];
	calc(b,1),f[a]=b;
}
void dfs(int x,int last) {
	f[x]=x,sz[x]=1,fa[x]=last,siz[x]=1,dep[x]=dep[last]+1;
	for(int i=0; i<v[x].size(); i++) {
		int y=v[x][i];
		if(y==last)
			continue;
		dfs(y,x),siz[x]+=siz[y],sq[x]+=1ll*siz[y]*siz[y];
	}
	calc(x,1);
}
int main() {
	scanf("%d",&n);
	for(int i=1,x,y; i<n; i++)
		scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs(1,0);
	printf("%lld\n",ans);
	scanf("%d",&q);
	for(int i=1,x,y; i<=q; i++) {
		scanf("%d%d",&x,&y);
		while(find(x)!=find(y)) {
			x=find(x),y=find(y);
			if(dep[x]<dep[y])
				swap(x,y);
			x=find(x),merge(x,find(fa[x]));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：__stick (赞：1)


## 题意

给出一棵树，支持动态加边，问满足存在 $u\to w,v\to w$ 的不相交路径的 $(u,v,w)$ **有序** 三元组数量。

## 思路

首先看树上的问题，发现 $w$ 是特殊的。

我们以 $w$ 来统计答案。

如果没有限制，方案数是 $(n-1)^2$ 减去一定不合法的方案数，也就是  $u,v$ 处于 $w$ 的同一子树。

也就是 $\sum\limits_{v\in son(u)}siz_v^2+(n-siz_u)^2$ 别忘记了父亲那边的子树。

然后考虑连边的问题。

每连上了一条边，然后考虑变化。

如果不管动态加边的话，考虑一张普通无向图的方法。

明显可以边双缩点算贡献，这里边双内部任意 3 个点都合法，这是边双的定义，然后和外部的贡献可以套用树的部分。

记得两个点在边双内部，一个在外部的贡献。

这样就是经典的动态维护边双问题了。

使用并查集维护每一个边双，然后并查集指向每个边双深度最小的节点。

然后即可暴力树上爬即可，发现每个点只能被遍历一次，所以复杂度有保证，答案就合并的时候暴力维护即可。

复杂度 $O(n)$，这里并查集的复杂度应该是线性的，这里是单纯的树上均摊每个点跳一次。





---

## 作者：OldDriverTree (赞：0)

# Solution

先考虑静态怎么做。

首先按对于一条路径 $x\to y\to z$（$x,y,z$ 两两不同），合法当且仅当我们把图缩边双缩成一棵树后树上存在一条 $x\to y\to z$ 的简单路径，然后考虑如何统计这个的个数。

我们先令一个边双中在原树上深度最小的那个点为代表节点，然后令 $cnt_x$ 为 $x$ 代表的边双的点数，$siz_x$ 为 $x$ 的子树大小（不难发现缩边双后 $siz$ 不变）。

我们考虑用总路径数减去不合法的路径数，一条路径不合法就当且仅当如果以 $y$ 为根，那么 $x$ 和 $z$ 在同一个子树中。那么枚举 $y$，令 $u$ 为 $y$ 所在的边双的代表节点，$x$ 和 $z$ 不合法的方案数就为 $\sum\limits_{v\in son_u} siz_v(siz_v-1)+(n-siz_u)(n-siz_u-1)$。所以总的不合法路径数就为 $\sum\limits_{u=1}^n cnt_u\sum\limits_{v\in son_u} siz_v(siz_v-1)+(n-siz_u)(n-siz_u-1)$，我们令 $ans_u$ 为与 $u$ 相邻的所有边双 $siz$ 的平方之和，则上面这个东西就为 $\sum\limits_{u=1} cnt_u(ans_u-n+cnt_u)$。

然后考虑如何处理动态加边，不难发现新加一条边 $(x,y)$ 后会使得树上 $x$ 到 $y$ 路径上的所有边双都合并为一个。于是我们考虑用并查集维护所有边双，每加一条边就暴力把路径上的所有边双合并起来（合并总次数显然不超过 $n-1$，所以时间复杂度是对的），注意这里要求子节点合并到父节点，合并的同时更新父节点的 $cnt,ans$，以及总方案数。

总时间复杂度 $O(n\log n+q)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
//using mint=modint998244353;
const int N=1e5+1;
vector<int> g[N];
int n,m,Fa[N],dep[N],siz[N];
int now,fa[N],cnt[N],ans[N];

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x) {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30) )*0xbf58476d1ce4e5b9;
        x=(x^(x>>27) )*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator() (uint64_t x) const {
        static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }
};
int read() {
    int x=0; bool _=true; char c=0;
    while (!isdigit(c) ) _&=(c!='-'),c=getchar();
    while (isdigit(c) ) x=x*10+(c&15),c=getchar();
    return _?x:-x;
}
void dfs(int u) {
    siz[u]=1,dep[u]=dep[Fa[u] ]+1;
    for (int v:g[u]) if (v^Fa[u])
    Fa[v]=u,dfs(v),siz[u]+=siz[v];
}
int find(int x) {
    return fa[x]^x?fa[x]=find(fa[x]):x;
}
void merge(int x,int y) {
    now-=cnt[x]*(ans[x]-n+cnt[x])+cnt[y]*(ans[y]-n+cnt[y]);
    ans[x]+=ans[y]-siz[y]*siz[y]-(n-siz[y])*(n-siz[y]);
    cnt[x]+=cnt[y],fa[y]=x,now+=cnt[x]*(ans[x]-n+cnt[x]);
}
main()
{
    n=read();
    for (int i=1;i<n;i++) {
        int x=read(),y=read();
        g[x].push_back(y),g[y].push_back(x);
    }
    dfs(1),m=read();
    for (int x=1;x<=n;x++) {
        fa[x]=x,cnt[x]=1; for (int y:g[x])
        if (y^Fa[x]) ans[x]+=siz[y]*siz[y];
        ans[x]+=(n-siz[x])*(n-siz[x]);
        now+=cnt[x]*(ans[x]-n+cnt[x]);
    }
    printf("%lld\n",n*(n-1)*(n-2)-now);
    while (m--)
    {
        int x=find(read() ),y=find(read() );
        while (x^y) {
            if (dep[x]<dep[y]) swap(x,y);
            merge(find(Fa[x]),x),x=find(Fa[x]);
        }
        printf("%lld\n",n*(n-1)*(n-2)-now);
    }
    return 0;
}
```

---

## 作者：SS80194 (赞：0)

3300？2300！

先考虑只有一棵树的情况怎么做。在 $w$ 处计算贡献，贡献即为删除 $w$ 点和其相邻的边所形成的连通块的两两乘积的两倍，可以通过维护连通块大小的二次方和来方便计算。

扩展到基环树，对于不在环上的点和树的情况没有区别。对于在环上的点来说，把环作为一个整体分三种情况考虑：

- $u$，$v$ 两点都在环上，对每组 $(u,v)$ 的 $w$ 一共有 $siz-2$ 种方案。
- $u$，在环上，$v$ 在外面，对每组 $(u,v)$ 的 $w$ 一共有 $siz-1$ 种方案。
- $u$，在环上，$v$ 在外面，对每组 $(u,v)$ 的 $w$ 一共有 $siz$ 种方案。

注意到题目里是无向图，所以把环扩展到边双连通分量也是一样的。本质上是要求过一个连通分量的路径有多少条，于是参考树的情况，维护一个联通分量的大小和所有连出去的子树大小的平方和即可。

暴力模拟缩点，使用并查集维护每个联通块的最上端点，在跳的过程中减去缩掉的点的贡献,缩完再加上新点的贡献。

```cpp
#include<bits/stdc++.h>
#define SP system("pause")
using namespace std;
typedef long long lld;
const int maxn=1e5+800;
int n,q,dep[maxn],siz[maxn],fa[maxn],scp[maxn],dst[maxn][22],lg2[maxn];lld A=0;
struct blink{int up,right;} e[2*maxn];int g[maxn],tot=0;
int f[maxn];lld s1[maxn],s2[maxn];
int ff(int x){if(x==f[x]) return x;return (f[x]=ff(f[x]));}
void mg(int x,int y){f[ff(y)]=ff(x);}//y挂到x下边
void addedge(int u,int v){e[++tot]=(blink){g[u],v};g[u]=tot;}
void adds(int u,int v){addedge(u,v);addedge(v,u);}
int lca(int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    for(int i=lg2[dep[y]-dep[x]];i>=0;i--)
        if((1<<i)&(dep[y]-dep[x])) y=dst[y][i];
    if(x==y) return x;
    for(int i=lg2[dep[x]];i>=0;i--)
        if(dst[x][i]!=dst[y][i]) x=dst[x][i],y=dst[y][i];
    return dst[x][0];
}
void dfs1(int p)
{
    siz[p]=1;dep[p]=dep[fa[p]]+1;dst[p][0]=fa[p];
    for(int i=1;i<=lg2[dep[p]];i++)
        dst[p][i]=dst[dst[p][i-1]][i-1];
    for(int i=g[p];i;i=e[i].up)
    {
        int v=e[i].right;
        if(v==fa[p]) continue;
        fa[v]=p;
        dfs1(v);
        siz[p]+=siz[v];
    }
}
lld calc1()
{
    for(int p=1;p<=n;p++)
    {
        s1[p]=1;
        for(int i=g[p];i;i=e[i].up)
        {
            int v=e[i].right;
            if(v==fa[p]) continue;
            s2[p]+=1ll*siz[v]*siz[v];
        }
        if(fa[p])
        {
            int su=siz[1]-siz[p];
            s2[p]+=1ll*su*su;
        }
        A+=1ll*(n-1)*(n-1)-s2[p];
    }
    return A;
}
lld cln(lld x,lld y)
{
    lld Tz=x*(x-1)*(2*n-x-2);
    Tz+=x*((n-x)*(n-x)-y);return Tz;
}
int main()
{
    freopen("855G.in","r",stdin);
    freopen("855G.out","w",stdout);
    scanf("%d",&n);   
    for(int i=2,u,v;i<=n;i++) scanf("%d%d",&u,&v),adds(u,v); 
    lg2[1]=0;for(int i=2;i<maxn;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<=n;i++) f[i]=i;
    dfs1(1);A=calc1();printf("%lld\n",A);
    scanf("%d",&q);
    for(int i=1,u,v,l;i<=q;i++)
    {
        scanf("%d%d",&u,&v);l=lca(u,v);
        if(ff(u)==ff(v)) {printf("%lld\n",A);continue;}
        int lp=0;
        A-=cln(s1[ff(l)],s2[ff(l)]);
        for(int p=u,px,lx;dep[p]>dep[l]&&ff(p)!=ff(l);p=fa[px])
        {
            px=ff(p),lx=ff(l);
            A-=cln(s1[px],s2[px]);
            s1[lx]+=s1[px];
            if(lp) s2[lx]+=(s2[px]-1ll*siz[lp]*siz[lp]-1ll*(n-siz[px])*(n-siz[px]));
            else s2[lx]+=s2[px]-1ll*(n-siz[px])*(n-siz[px]);
            mg(l,px);lp=px;
        }
        if(lp) s2[ff(l)]-=1ll*siz[lp]*siz[lp];lp=0;
        for(int p=v,px,lx;dep[p]>dep[l]&&ff(p)!=ff(l);p=fa[px])
        {
            px=ff(p),lx=ff(l);
            A-=cln(s1[px],s2[px]);
            s1[lx]+=s1[px];
            if(lp) s2[lx]+=(s2[px]-1ll*siz[lp]*siz[lp]-1ll*(n-siz[px])*(n-siz[px]));
            else s2[lx]+=s2[px]-1ll*(n-siz[px])*(n-siz[px]);
            mg(l,px);lp=px;
        }
        if(lp) s2[ff(l)]-=1ll*siz[lp]*siz[lp];lp=0;
        A+=cln(s1[ff(l)],s2[ff(l)]);
        printf("%lld\n",A);
    }
}
```


---

