# [ABC225G] X

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc225/tasks/abc225_g

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。各マスには整数が書かれており、上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ には $ A_{i,j} $ が書かれています。

これから高橋くんが、$ H\ \times\ W $ 個あるマスから $ 0 $ 個以上を選び、バツ印を付けます。$ 1 $ つのバツ印は、書かれるマスの左上の角と右下の角を結ぶ線分、および右上の角と左下の角を結ぶ線分の $ 2 $ 本からなります。

高橋くんのスコアを、$ ( $バツ印を付けられたマスに書かれた整数の総和$ )-\ C\ \times\ ( $バツ印を書くために必要な線分の本数の最小値$ ) $ と定義しましょう。

ここで、高橋くんは斜めに隣接するマスのバツ印を続けて書くことができます。

例えば、マス $ (1,1) $ とマス $ (2,2) $ にバツ印を付けるとき、高橋くんは

- マス $ (1,1) $ の左上の角とマス $ (2,2) $ の右下の角を結ぶ $ 1 $ 本の線分
- マス $ (1,1) $ の右上の角とマス $ (1,1) $ の左下の角を結ぶ $ 1 $ 本の線分
- マス $ (2,2) $ の右上の角とマス $ (2,2) $ の左下の角を結ぶ $ 1 $ 本の線分

の計 $ 3 $ 本によってバツ印を書くことができます。

高橋くんのスコアの最大値を求めてください。なお、**バツ印を付けないマスには何も書いてはいけないことに注意してください。**

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 100 $
- $ 1\ \leq\ C\ \leq\ 10^9 $
- $ 1\ \leq\ A_{i,j}\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

マス $ (1,2) $ とマス $ (2,1) $ にバツ印を付ける場合、高橋くんは - マス $ (1,2) $ の左上の角とマス $ (1,2) $ の右下の角を結ぶ $ 1 $ 本の線分 - マス $ (2,1) $ の左上の角とマス $ (2,1) $ の右下の角を結ぶ $ 1 $ 本の線分 - マス $ (1,2) $ の右上の角とマス $ (2,1) $ の左下の角を結ぶ $ 1 $ 本の線分 の計 $ 3 $ 本によってバツ印を書くことができます。故にこの場合の高橋くんのスコアは $ 10+8-2\ \times\ 3=12 $ です。 これよりも真にスコアが大きくなるバツ印の付け方は存在しないため、答えは $ 12 $ となります。

### Sample Explanation 2

どのマスにもバツ印を付けないのが最善です。

## 样例 #1

### 输入

```
2 2 2
2 10
8 3```

### 输出

```
12```

## 样例 #2

### 输入

```
3 3 100
1 1 1
1 1 1
1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 9 970861213
1313462 943495812 203775264 839015475 115668311 14701110 819458175 827176922 236492592
843915104 786367010 344840288 618248834 824858165 549189141 120648070 805825275 933750119
709330492 38579914 890555497 75314343 238373458 854061807 637519536 53226153 627677130
671706386 380984116 221773266 787763728 639374738 298691145 359138139 183373508 524415106
716502263 150803008 390520954 913021901 553285119 876389099 952721235 46809105 635239775
355621458 511843148 117663063 37274476 891025941 832254337 346436418 783134705 488516288
383723241 322408013 948364423 409068145 120813872 697127655 968230339 988041557 222591780
712959990 233114128 210373172 798667159 568746366 579461421 923556823 777007925 422249456```

### 输出

```
9785518299```

# 题解

## 作者：LinkWish (赞：7)

因为每个格子只有选与不选的状态，容易想到这道题可能可以使用网络流最小割解决。

我们设源点为 $s$，汇点为 $t$。

我们让所有点向 $t$ 连一条容量为自身点权的边，如果一个点要被选择，那么不应割掉这条边，如果不选他，就会付出他点权的代价。

再考虑一下题目中 X 字限制。定义一个数组 $f_{i,j}$，如果一个格子被选了则 $f_{i,j}=0$，否则 $f_{i,j}=C$。那么一个格子对笔画数量的贡献显然为 $f_{i-1,j+1}+f_{i+1,j+1}$，意为右上角与右下角是否被选择，这个格子是否需要新笔画。在最小割中我们可以体现为当前点的右上角和右下角向当前点分别建一条容量为 $C$ 的边，如果当前点在第 $1$ 行、第 $n$ 行或者第 $m$ 列则从 $s$ 向当前点建两条容量为 $C$ 的边。

答案即为点权之和减去最小割。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。

```cpp
//Linkwish's code
const int N=10005,s=0,t=N-1;
int n,m,C,tot;
struct edge{
	int to,w,de;
	inline edge(int x,int y,int z){to=x,w=y,de=z;}
};
vector<edge> e[N];
inline void add(int x,int y,int w){
	e[x].emplace_back(y,w,e[y].size());
	e[y].emplace_back(x,0,e[x].size()-1);
}
int cnt[N],fl[N];
int isap(int x,int val){
	if(x==t||!val)return val;
	int now=val,res;
	for(edge &i:e[x]){
		if(i.w>0&&fl[x]==fl[i.to]+1){
			res=isap(i.to,min(i.w,now));
			i.w-=res,e[i.to][i.de].w+=res,now-=res;
			if(!now)return val;
		}
	}
	cnt[fl[x]]--;
	if(!cnt[fl[x]])fl[s]=tot;
	cnt[++fl[x]]++;
	return val-now;
}
int a[105][105];
inline int pos(int x,int y){return (x-1)*m+y;}
signed main(){
	read(n),read(m),read(C);
	tot=n*m+2;
	int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			read(a[i][j]);
			sum+=a[i][j];
			if(i==1||j==m)add(s,pos(i,j),C);
			else add(pos(i-1,j+1),pos(i,j),C);
			if(i==n||j==m)add(s,pos(i,j),C);
			else add(pos(i+1,j+1),pos(i,j),C);
			add(pos(i,j),t,a[i][j]);
		}
	}
	int ans=0;
	cnt[0]=tot;
	while(fl[s]<tot)ans+=isap(s,iinf);
	writeln(sum-ans);
	return 0;
}
```


---

## 作者：DengDuck (赞：2)

我是一个采购，这道题真的太有意思啦！

首先我们转换问题，考虑到网络流处理方格取数问题的套路是格子权值的总和减去最小割，我们怎么往上靠？

根据套路的式子，我们用总和减去答案易得最小割所求：

选的格子的权值加上不选的格子的权值减去选的格子的权值加上划线的代价。

这个过程有所抵消，化简得到：

不选的格子的权值加上划线的代价，这就是我们要使其最小的代价了。

这个转换有什么用处呢？我们发现原问题有加有减很烦，这个问题只有加。

首先显然每个格子 $(i,j)$ 都应该向源点连边，容量为 $a_{i,j}$，这表示出了每个格子基本的选和不选，如果不选，这条边会被割掉。

然后我们要考虑画 X 这一条件。

发现，对于一条连续选择的斜线，如果有一个格子画了这个方向相反的线，其他的格子就不用画了。

我们将所有存在斜线前一项的格子向前一项连一条容量为 $C$ 的边，只要某个斜线有一个边断开，其他的边自然无法从此方向到达汇点。

如果前一项的格子不存在，则向汇点连一条权值为 $C$ 的边。

每次割的时候切断了一条向那个方向的路径，相当于一直向下画，中间要是有间隔不画了在其他边那里处理。

于是答案就是格子权值的总和减去最小割。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
const LL inf=1e18;
struct node
{
	LL to,nxt,w,f;
}a[N],b[N];
LL m,n,c,x,tot=1,dep[N],h[N],sum,cur[N];
void add(LL x,LL y,LL z)
{
	a[++tot]={y,h[x],z,0};
	h[x]=tot;
	a[++tot]={x,h[y],0,0};
	h[y]=tot;
}
queue<LL>q;
LL bfs(LL s,LL t)
{
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		LL k=q.front();
		q.pop();
		for(LL i=h[k];i;i=a[i].nxt)
		{
			if(!a[i].w||dep[a[i].to])continue;
			dep[a[i].to]=dep[k]+1;
			q.push(a[i].to);
		}
	}
	for(int i=1;i<=n*m+2;i++)cur[i]=h[i];
	return dep[t];
}
LL dfs(LL x,LL t,LL f)
{
	if(x==t||!f)return f;
	LL ans=0;
	for(LL i=cur[x];i&&f;i=a[i].nxt)
	{
		if(!a[i].w||dep[a[i].to]!=dep[x]+1)continue;
		cur[x]=i;
		LL fl=min(a[i].w,f),k=dfs(a[i].to,t,fl);
		if(k)
		{
			a[i].w-=k,a[i^1].w+=k,ans+=k,f-=k;
		}
	}
	return ans;
}
LL dinic(LL s,LL t)
{
	LL ans=0;
	while(bfs(s,t))
	{
		while(1)
		{
			LL k=dfs(s,t,inf);
			if(!k)break;
			ans+=k;	
		}
	}
	return ans;
}
LL num(LL x,LL y)
{
	return m*(x-1)+y;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&c);
	LL s=n*m+1,t=n*m+2; 
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%lld",&x);
			sum+=x;
			add(s,num(i,j),x);
			if(i!=1&&j!=1)add(num(i,j),num(i-1,j-1),c);
			else add(num(i,j),t,c);
			if(i!=n&&j!=1)add(num(i,j),num(i+1,j-1),c);
			else add(num(i,j),t,c);
		}
	}
	printf("%lld",sum-dinic(s,t));
}
```

---

## 作者：CrTsIr400 (赞：1)

这是 ABC225G 的题解，但是我们把这题放一放，先来看另一道题目。

##  [P4313 文理分科](https://www.luogu.com.cn/problem/P4313) 

题目大意：全班分科，每位同学**分到文科**能获得一定满意值，**分到理科**能获得一定满意值，如果**四联通相邻的同学都被分到同一科**也能增加一定的满意值，要求找到最优划分，使得满意值最大。

这道题显然可以使用最小割。

建模：$S$ 向所有点连接一条流量为 $art_i$ 的边。所有点向 $T$ 连接一条流量为 $science_i$ 的边。

对于每个点 $i$ 建立两个虚点 $a_i,b_i$，连接 $S$ 和 $a_i$，流量为文科附加值，连接 $T$ 和 $b_i$，流量为理科附加值。

**连接 $a_i$ 和 $i$ 及其周围四联通点流量为无穷，连接 $i$ 和其周围四联通点与 $b_i$ 流量为无穷。**

这个 $a_i$ 点代表啥呢？就是需要了解周围四个点和本身的选择。

若这条 $S\to a_i$ 的边被割断，则周围的同学一定不都选文科。

我们尝试更进一步理解这个构型。为了简化模型，我们只约束两个同学选文科。

![](https://cdn.luogu.com.cn/upload/image_hosting/dywl75ay.png)

若 $b1,b2$ 被完全割断的时候，则表示都选文科，此时最小割还没到 $ad$ 出手。

若 $b1,b2$ 不完全割断的时候，此时是可以完全多一点流量的。

![](https://cdn.luogu.com.cn/upload/image_hosting/cw7ny0gd.png)

因为 $b2$ **并没有完全被割断**，所以我们可以认为 $ad$ 被割断了，附加价值不再，而 $b2$ 也没有被割断。不然就是上面那种情况了。

于是我们就完成了证明。

解决完文理分科这道题之后，其实有很多类似的题目，比如 小 M 的作物。

## 回到本题

我们学会了**如何知道相关点选择了什么，以此能做出更进一步的决策**的网络流建模方法。

---

显然，不能模拟“画线”操作，这里依赖的信息非常多，无法记录。

若一个点的左上方或者右上方是一个 `X`，那么收益能分别加上 $C$。

很明显，这就是网络流中的“若有……”则还能增加收益的建模。就是上文所提及的方法。

所以，这里增加收益的建模就相当显然了。

值得注意的是初始连边有一些细节：$S$ 连接 $(i,j)$ 点的流量为 $a_{i,j}$，而 $(i,j)$ 点需要向 $T$ 连 $2C$ 的流量，代表选还是不选。

但是这里对于总答案只应该加上 $a_{i,j}$ 就行了。因为我不选 $X$ 是没有价值的，选了反而还会扣代价 $2C$。

结合一下代码，同学们应该了解起来不是很难。

```cpp
#include<bits/stdc++.h>
#include<atcoder/maxflow>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I n,m,dj,x;LL ans=0;
const LL Linf=1ll<<60;
I g(I x,I y){
	return (x-1)*m+y;}
#define ade add_edge
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>dj;I nm=n*m;
	I S=nm*3+1,T=nm*3+2;
	atcoder::mf_graph<LL>G(T+1);
	fo(i,1,n)fo(j,1,m){
		cin>>x;ans+=x;
		G.ade(S,g(i,j),x),G.ade(g(i,j),T,dj*2);}
	fo(i,2,n){
		fo(j,2,m){
			I k=g(i,j)+nm;
			G.ade(S,k,dj),ans+=dj,
			G.ade(k,g(i-1,j-1),Linf),
			G.ade(k,g(i,j),Linf);}
		fo(j,1,m-1){
			I k=g(i,j)+nm*2;
			G.ade(S,k,dj),ans+=dj,
			G.ade(k,g(i-1,j+1),Linf),
			G.ade(k,g(i,j),Linf);}
	}
	printf("%lld\n",ans-G.flow(S,T));
	return 0;}
```

---

## 作者：N2MENT (赞：1)

[X](https://www.luogu.com.cn/problem/AT_abc225_g)

---

看到题，dp？no。

如果想要 dp，至少要知道三个方向上的情况，不管什么顺序都很难 dp。

看到如同我的智商一样低的数据范围，很像 wll。

选一些物品使得代价最大，还有额外代价，考虑最小割，先把每个点向 $\texttt{T}$ 连价值为 $a_{i, j}$ 的边如果这些边被割即代表不要这个格子了。

那么 $\texttt{S}$ 那边怎么连边，我们实际上是在求各个方向上的连通块个数，这个限制太全局了，把它放到每个点上，单独考虑一个方向上的情况。

如果一个点的前驱不选，而它选了，则带来 $C$ 的贡献，把它视作连通块的起点。而如果前面有一个起点，中间的点都划了另一个方向上的边，它就可以免费划线。

具体来说，对应到网络流上就是：左上和右上向该点连边，如果没有点就从 $\texttt{S}$ 连边，代价都为 $C$。割掉连向该点的一条边对应把它作为某个方向上的起点。能否免费划线的限制恰好与最小割的限制相同。

```
//        No mind to think.
//
//        No will to break.
//
//        No voice to cry suffering.
//
//        Born of God and Void.
//
//        You shall seal the blinding light that plagues their dreams.
//
//        You are the Vessel.
//
//        You are the Hollow Knight.
#ifdef N2
#define _GLIBCXX_DEBUG
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#define DO(...) __VA_ARGS__
#else 
#define LOG(...) void(0)
#define DO(...) void(0)
#define NDEBUG
#endif
#define syncoff ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
using ll = long long;
int dis[maxn];
int S = maxn - 2, T = maxn - 1;
struct Edge {
    int v, rev;
    ll flow;
    Edge() = default;
    Edge(int v, ll flow, int rev) : v(v), flow(flow), rev(rev) {}
};
vector<Edge> G[maxn];
int cur[maxn];
void Add(int u, int v, ll w) {
//        cerr << u << ' ' << v << ' ' << w << '\n';
    G[u].emplace_back(v, w, G[v].size());
    G[v].emplace_back(u, 0, G[u].size() - 1);
}
bool Bfs() {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    dis[S] = 1;
    q.emplace(S);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto e : G[u]) {
            if(dis[e.v] || !e.flow) continue;
            dis[e.v] = dis[u] + 1;
            q.emplace(e.v);
        }
    }
    return dis[T];
}
ll Dfs(int u, ll in) {
    if(u == T) return in;
    ll out = 0;
    for(int &i = cur[u]; i < G[u].size(); i++) {
        auto &e = G[u][i];
        if(dis[e.v] != dis[u] + 1 || !e.flow) continue;
        int del = Dfs(e.v, min(e.flow, in - out));
        e.flow -= del, G[e.v][e.rev].flow += del;
        out += del;
        if(in == out) break;
    }
    return out;
}
ll Dinic() {
    ll res = 0;
    while(Bfs()) {
        memset(cur, 0, sizeof(cur));
        res += Dfs(S, 0x3f3f3f3f3f3f3f3f);
    }
    return res;
}
const int maxl = 110;
int a[maxl][maxl];
ll sum;
int n, m, c;
bool In(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m;
}
int Map(int x, int y) {
    return (x - 1) * m + y;
}
int main() {
    cin >> n >> m >> c;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            sum += a[i][j];
            Add(Map(i, j), T, a[i][j]);
            if(In(i - 1, j - 1)) Add(Map(i - 1, j - 1), Map(i, j), c);
            else Add(S, Map(i, j), c);
            if(In(i - 1, j + 1)) Add(Map(i - 1, j + 1), Map(i, j), c);
            else Add(S, Map(i, j), c);
        }
    }
    cout << sum - Dinic();
}
```

---

## 作者：Reunite (赞：0)

最小割好题。

## 一
---

如果没有连线可合并的限制怎么做？当然我们可以把点权预先减去 $2C$，然后取所有的正值，但这样没有可扩展性，因为每个点只有选与不选两个状态，因此考虑转化最小割模型。把每个点向源点（$S$）连 $a_{i,j}$ 的边，向汇点（$T$）连 $2C$ 的边，把所有点的点权和减去最小割就是答案。

考虑如何合并连线，我们希望构成这样一个图：选择一条连续斜线的任一点，如果选（与 $S$ 相连），则整个斜线该方向只要一个 $C$ 的代价，如果不选，则分成两部分，需要 $2C$ 的代价。

直接构造，每个点向左上和左下的点连边，如果超出矩阵边界就向 $T$ 连边，容量都是 $C$。

考虑为什么这样是对的，还是考虑选择了一个斜线，从一段开始，只有是一个端点或者是边界我们才会割掉一个 $C$，然后我们一直沿着斜线下去，只要还在斜线上，那么全都和 $S$ 连通，那么它们之间连的 $C$ 的边是不必割掉的，也就减少了 $cnt-1$ 次 $C$ 的代价。

---
## 二
---

复杂度为 $O(??)$，本来网络流复杂度就很神秘，调用 atcoder 里的库的话就更未知了。总之点数和边数都是 $nm$ 的。

极简代码：

```cpp
#include <iostream>
#include <atcoder/maxflow>
#define ll long long
#define ad g.add_edge
#define id(x,y) (x-1)*m+y
using namespace std;
int n,m,C,S,T,x;
int main(){
	cin>>n>>m>>C;
	atcoder::mf_graph <ll> g(n*m+3);
	ll s=0;
	S=n*m+1,T=S+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>x;
			s+=x;
			ad(S,id(i,j),x);
			i!=1&&j!=1?ad(id(i,j),id(i-1,j-1),C):ad(id(i,j),T,C);
			i!=n&&j!=1?ad(id(i,j),id(i+1,j-1),C):ad(id(i,j),T,C);
		}
	}
	cout<<s-g.flow(S,T);
	return 0;
}
```

---

