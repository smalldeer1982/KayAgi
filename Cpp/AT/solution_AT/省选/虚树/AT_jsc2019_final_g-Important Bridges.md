# Important Bridges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_g

AtCoder 株式会社は、$ 0 $ から $ N-1 $ までの番号のついた $ N $ 個の島からなる会社です。 これらの島は、$ 0 $ から $ N-2 $ までの番号のついた $ N-1 $ 個の橋によって結ばれています。 橋 $ i $ は、島 $ A_i $ と島 $ B_i $ を双方向に結んでいます。 どの島からどの島へも、橋を渡っていくことでたどり着くことができます。

全ての島にはホテルがあります。 しかし現在、全てのホテルは営業休止中です。 そこで、AtCoder の観光部門の担当者である高橋くんは、これから $ Q $ 日間にわたるホテルの営業再開、休止の計画を立てました。 具体的には、$ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $) 日目の朝に、以下のことが起こります。

- 島 $ X_i $ のホテルが営業休止している場合、そのホテルの営業を再開する。
- 島 $ X_i $ のホテルが営業している場合、そのホテルの営業を休止する。

なお、全ての $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $) について、$ i $ 日目の昼に営業しているホテルが $ 1 $ つ以上あることが保証されます。

橋 $ i $ が $ j $ 日目に**重要**であるとは、以下のことを意味します。

- $ j $ 日目の昼にホテルが営業している $ 2 $ つの島 $ a,b $ であって、島 $ a $ から島 $ b $ へ向かうためには橋 $ i $ を通らなければならないものが存在する。

それぞれの橋について、その橋が重要である日が $ Q $ 日間のうち何日あるか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i,B_i\ \leq\ N-1 $
- どの島からどの島へも、橋を渡っていくことでたどり着くことができる。
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ X_i\ \leq\ N-1 $
- 全ての $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $) について、$ i $ 日目の昼に営業しているホテルが $ 1 $ つ以上存在する。
- 入力される値はすべて整数である。

### Sample Explanation 1

例えば、$ 2 $ 日目の昼にホテルが営業している島は 島 $ 0,2,4 $ であり、この日に重要な橋は 橋 $ 1,2,3 $ です。

## 样例 #1

### 输入

```
5 5
0 1
2 0
4 3
3 0
0
4
2
1
4```

### 输出

```
2
3
3
3```

## 样例 #2

### 输入

```
15 15
10 12
7 8
2 13
4 1
11 4
6 9
3 0
5 11
8 2
12 0
2 5
6 2
5 0
0 14
14
9
3
10
13
7
1
3
1
13
7
9
10
9
3```

### 输出

```
9
5
5
2
2
12
6
2
5
9
12
12
12
13```

# 题解

## 作者：YangRuibin (赞：1)

# 初步思考
首先，我们先考虑一次操作后有哪些边是关键边。如果有两个点 $x$ 和 $y$，它们的最近公共祖先为 $c$，那么从 $x$ 到 $c$，和从 $c$ 到 $y$ 这之间经过的边都是关键边。

以此类推，如果有多个点，那么它们以及它们两两之间的最近公共祖先（当然有可能重合）所连成的树（也叫**虚树**）的边都是关键边。

# 更进一步
对于一个新加入的点，关键边会如何变化？

一个新点“接入”虚树，从它本身到“接口”途经的边都变成关键边。但是“接口”位置难以确定。我们会发现，“接口”之前的 dfs 序都比新点的的小，右边的都比新点的大。所以我们可以在前面选一个，后面选一个，甚至不需要找“接口”就能推算答案。

然而，如果选的两个点不合适（比如它们的最近公共祖先太远）就会导致算重。因此，这两个点必须尽可能贴近新点。dfs 序意义上的**前驱**和**后继**就成了不二之选。图中标红的点是新点，~~图比较抽象~~。

![](https://cdn.luogu.com.cn/upload/image_hosting/cs45929k.png)

推算答案的方式：把从前驱到后继的路径值减少 $1$，再把从前驱到新点的路径、从新点到后继的路径值增加 $1$。需要注意的是，这样算出的答案恰好是原答案的两倍。

于是麻烦就来了。

1. 新点没有前驱。

![](https://cdn.luogu.com.cn/upload/image_hosting/5bbkxvdn.png)

处理办法：此时从新点到虚树顶部的路径都变成关键边。可以将关键点中 dfs 序最大的点视为“前驱”。

2. 新点没有后继。

![](https://cdn.luogu.com.cn/upload/image_hosting/o498ici5.png)

处理办法：此时从新点到虚树顶部的路径都变成关键边。可以将关键点中 dfs 序最小的点视为“后继”。

删除点和加点的思路基本相同，只是增加的值变成负数而已。

# 通览全局
1. 前驱、后继如何维护？

用 set 存关键点的 dfs 序。

2. 如何统计题目中“有几次操作后它是关键边”？

这样想，对于一次操作，我们可以把之后产生的贡献一并加上。对于时间点 $i$，加上的总贡献就是贡献存在的时长 $q-i+1$。如果后面又删了呢？我们对删点操作产生的负贡献也如此“提前计算”，多出来的刚好就抵消掉了。

3. 加、删点有什么细节？

因为前文的论述都是建立在“新点暂时不属于虚树”的基础上，因此加点时算完贡献再加点，删点时删除后再计算。

同时 set 维护的点集不用包含关键点的最近公共祖先。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,q,id[N],head[N],tot,dep[N],fa[N][19],tim[N],len,rd[N],a[N],ans[N];
/*
id:一条边的编号的对应点  
tim:点的dfs序   rd:dfs序对应的点
a:树上差分数组  ans:记录最终答案 
*/
bool v[N];//记录一个点是否是黑点 
set<int>g;//维护关键点的集合 
set<int>::iterator nl,nr;//nr:前驱  nl:后继
struct node{
	int to,next,i;
}edge[N*2];
void add(int from,int to,int i)
{
	++tot;
	edge[tot].to=to;
	edge[tot].i=i;
	edge[tot].next=head[from];
	head[from]=tot;
}
void pre(int x,int fat)//预处理 dfs序 lca信息 边、点对应关系 
{
	tim[x]=++len;rd[len]=x;
	dep[x]=dep[fat]+1;fa[x][0]=fat;
	for(int i=1;i<=18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fat)continue;
		id[to]=edge[i].i;pre(to,x);
	}
}
int getlca(int x,int y)//求 lca 
{
	if(dep[x]>dep[y])swap(x,y);
	for(int i=18;~i;i--)
		if(dep[fa[y][i]]>=dep[x])y=fa[y][i];
	if(x==y)return x;
	for(int i=18;~i;i--)
		if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void addp(int i,int x,int l,int r)//加入一个点时关键边的变化 
{
	a[l]-=(q-i+1),a[r]-=(q-i+1),a[getlca(l,r)]+=2*(q-i+1);
	a[l]+=(q-i+1),a[x]+=(q-i+1),a[getlca(l,x)]-=2*(q-i+1);
	a[x]+=(q-i+1),a[r]+=(q-i+1),a[getlca(x,r)]-=2*(q-i+1);
}
void delp(int i,int x,int l,int r)//删除一个点时关键边的变化 
{
	a[l]+=(q-i+1),a[r]+=(q-i+1),a[getlca(l,r)]-=2*(q-i+1);
	a[l]-=(q-i+1),a[x]-=(q-i+1),a[getlca(l,x)]+=2*(q-i+1);
	a[x]-=(q-i+1),a[r]-=(q-i+1),a[getlca(x,r)]+=2*(q-i+1);
}
void dfs(int x,int fat)//统计答案 
{
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fat)continue;
		dfs(to,x);a[x]+=a[to];
	}
	ans[id[x]]=a[x];
}
signed main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1,x,y;i<n;i++)
		scanf("%lld%lld",&x,&y),++x,++y,add(x,y,i),add(y,x,i);
	pre(1,0);
	for(int i=1,x;i<=q;i++)
	{
		scanf("%lld",&x);++x;
		if(!v[x])//加点 
		{
			if(g.size())
			{
				nl=g.lower_bound(tim[x]),nr=nl;
				if(nl==g.end())nl=g.begin();
				if(nr==g.begin())nr=--g.end();
				else --nr;
				addp(i,x,rd[*nl],rd[*nr]);
			}
			g.insert(tim[x]);v[x]=1;
		}
		else
		{
			g.erase(tim[x]);v[x]=0;
			if(g.size())
			{
				nl=g.lower_bound(tim[x]),nr=nl;
				if(nl==g.end())nl=g.begin();
				if(nr==g.begin())nr=--g.end();
				else --nr;
				delp(i,x,rd[*nl],rd[*nr]);
			}
		}
	}
	dfs(1,0);
	// ans[i]>>1 是因为以上算法求出的值恰好是原答案的2倍 
	for(int i=1;i<n;i++)printf("%lld\n",ans[i]>>1);
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：1)

$\textbf{AT\_jsc2019\_final\_g}$

> - 有一棵 $n$ 个点的树，每个点可以是黑点或者白点，初始时都是白点。有 $q$ 次操作，第 $i$ 次操作是反转点 $u$ 的颜色。
> - 定义某一时刻某条边 $(u,v)$ 是关键的，当且仅当存在两个**黑**点 $x,y$ 且 $x \to y$ 的简单路径经过边 $(u,v)$。
> - 对每一条边统计在 $q$ 次操作中，有几次操作后它是关键边。
> - $1 \le n,q \le 2\cdot 10^5$，保证每次操作后至少有一个黑点。

这玩意竟然 $^*3400$，我感觉 $^*2400$ 都没有。

考虑对于每一个时刻，关键边其实就是所有黑点组成的**虚树**上的边。加点删点维护虚树的[经典套路](https://www.luogu.com.cn/problem/P3320)是 set 维护 dfn 序。

如果我们只需要动态维护边是否关键，那么加入点 $x$ 后我们找到 dfn 序上 $x$ 的前驱后继 $u,v$，先把 $u \to v$ 的路径权值 $-1$，再把 $u \to x,x\to v$ 两条路径权值 $+1$ 即可得到每条边是否关键。

现在我们相当于要对这个东西做历史和，这里只需要一个简单的时间轴上的差分：对于时刻 $i$，加删贡献时加减 $q - i + 1$，这样当某条边在 $j (j > i)$ 时刻删除时其贡献减少 $q - j + 1$，两者做差刚好是 $j - i$。

那么我们只需要路径加，可以树上差分完成。时间复杂度 $\mathcal O((n + q) \log n)$。

稍微注意一下刚才的过程中，虚树上每条边会算两次贡献，我们需要将答案除以 $2$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 27.03.2024 12:57:30
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,q,u,v,dfn[N],st[20][N],tot,nfd[N],f[N],au[N],av[N]; vector<int> g[N]; set<int> s; ll a[N];
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[++u].push_back(++v),g[v].push_back(u),au[i] = u,av[i] = v;
    auto cmp = [&](int u,int v){return (dfn[u] < dfn[v] ? u : v);};
    auto dfs = [&](auto self,int u,int f) -> void {
        st[0][dfn[u] = ++tot] = f,nfd[tot] = u; for(int v : g[u]) if(v != f) self(self,v,u);
    };dfs(dfs,1,0);
    for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
        st[j][i] = cmp(st[j-1][i],st[j-1][i+(1<<j-1)]);
    auto lca = [&](int u,int v){
        if(u == v) return u;
        if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
        int k = __lg(v - u);
        return cmp(st[k][u+1],st[k][v-(1<<k)+1]);
    }; auto upd = [&](int u,int v,int w){a[u] += w,a[v] += w,a[lca(u,v)] -= 2 * w;};
    for(int i = 1;i <= q;i ++){
        auto cg = [&](int u,int w){
            int x = dfn[u]; if(w < 0) s.erase(x);
            if(s.size()){
                auto it = s.lower_bound(x),ti = it; if(it == s.end()) it = s.begin();
                if(ti == s.begin()) ti = --s.end(); else ti --;
                upd(nfd[*ti],nfd[*it],-w),upd(nfd[*ti],u,w),upd(nfd[*it],u,w);
            }if(w > 0) s.insert(x);
        }; cin >> u,f[++u] ^= 1,cg(u,f[u] ? q - i + 1 : -(q - i + 1));
    }auto dfs2 = [&](auto self,int u,int f) -> void {
        for(int v : g[u]) if(v != f) self(self,v,u),a[u] += a[v];
    }; dfs2(dfs2,1,0);
    for(int i = 1;i < n;i ++) u = au[i],v = av[i],cout << a[nfd[max(dfn[u],dfn[v])]] / 2 << "\n";
}
```

---

