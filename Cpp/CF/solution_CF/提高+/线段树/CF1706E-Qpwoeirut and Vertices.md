# Qpwoeirut and Vertices

## 题目描述

You are given a connected undirected graph with $ n $ vertices and $ m $ edges. Vertices of the graph are numbered by integers from $ 1 $ to $ n $ and edges of the graph are numbered by integers from $ 1 $ to $ m $ .

Your task is to answer $ q $ queries, each consisting of two integers $ l $ and $ r $ . The answer to each query is the smallest non-negative integer $ k $ such that the following condition holds:

- For all pairs of integers $ (a, b) $ such that $ l\le a\le b\le r $ , vertices $ a $ and $ b $ are reachable from one another using only the first $ k $ edges (that is, edges $ 1, 2, \ldots, k $ ).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/8251767c792df96adbc7d8ce1ae896aca10bb309.png)Graph from the first test case. The integer near the edge is its number.In the first test case, the graph contains $ 2 $ vertices and a single edge connecting vertices $ 1 $ and $ 2 $ .

In the first query, $ l=1 $ and $ r=1 $ . It is possible to reach any vertex from itself, so the answer to this query is $ 0 $ .

In the second query, $ l=1 $ and $ r=2 $ . Vertices $ 1 $ and $ 2 $ are reachable from one another using only the first edge, through the path $ 1 \longleftrightarrow 2 $ . It is impossible to reach vertex $ 2 $ from vertex $ 1 $ using only the first $ 0 $ edges. So, the answer to this query is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/af65cd675bd4523d08062174925e59fd8900ee43.png)Graph from the second test case. The integer near the edge is its number.In the second test case, the graph contains $ 5 $ vertices and $ 5 $ edges.

In the first query, $ l=1 $ and $ r=4 $ . It is enough to use the first $ 3 $ edges to satisfy the condition from the statement:

- Vertices $ 1 $ and $ 2 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 $ (edge $ 1 $ ).
- Vertices $ 1 $ and $ 3 $ are reachable from one another through the path $ 1 \longleftrightarrow 3 $ (edge $ 2 $ ).
- Vertices $ 1 $ and $ 4 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 1 $ and $ 3 $ ).
- Vertices $ 2 $ and $ 3 $ are reachable from one another through the path $ 2 \longleftrightarrow 1 \longleftrightarrow 3 $ (edges $ 1 $ and $ 2 $ ).
- Vertices $ 2 $ and $ 4 $ are reachable from one another through the path $ 2 \longleftrightarrow 4 $ (edge $ 3 $ ).
- Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ).

If we use less than $ 3 $ of the first edges, then the condition won't be satisfied. For example, it is impossible to reach vertex $ 4 $ from vertex $ 1 $ using only the first $ 2 $ edges. So, the answer to this query is $ 3 $ .

In the second query, $ l=3 $ and $ r=4 $ . Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ). If we use any fewer of the first edges, nodes $ 3 $ and $ 4 $ will not be reachable from one another.

## 样例 #1

### 输入

```
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3```

### 输出

```
0 1 
3 3 0 5 5 
2```

# 题解

## 作者：happy_dengziyue (赞：21)

### 1 视频题解

（呃，我这边视频没挂）

![](bilibili:BV1S94y1Q7zs)

### 2 思路

说来你可能不信，看到这题时我还不会 $\operatorname{Kruskal}$ 重构树，于是花了 $30$ 分钟自学了它，然后赛场上 $\operatorname{AC}$ 了这道题……

我们将这条边的编号定义为它的边权。按照升序排序~~（好像没必要排序哦）~~后，通过 $\operatorname{Kruskal}$ 生成树算法，连边时断开这条边，而是新建一个点，让这个新点来连接两点，新点的点权为原来连边的权值。这就是 $\operatorname{Kruskal}$ 重构树。

得到 $\operatorname{Kruskal}$ 重构树后，为了 $u$ 和 $v$ 连通，连接的边的最大值的最小值，即为 $u$ 和 $v$ 的最近公共祖先的点权。通过倍增法求出最近公共祖先即可。

对于所有的 $i(1\le i<n)$，我们可以先求出使 $i$ 和 $i+1$ 连通的代价（设为 $ans_i$）。然后，建造线段树，预处理出区间最大值。

最后，询问 $l,r$ 本质上就是使 $[l,1+1],[l+1,l+2],…[r-1,r]$ 都连通，那么答案就是 $\max_{i=l}^{r-1}ans_i$。利用线段树求出即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int n;
int m;
int q;
struct L{
	int u,v,w;
}l[max_n+2];
int fa[max_n<<2];
int fi;
int w[max_n<<2];
struct E{
	int v,nx;
}e[max_n<<2];
int ei;
int fir[max_n<<2];
bool vis[max_n<<2];
int de[max_n<<2];
int fat[max_n<<2][22];
int ans[max_n<<2];
int tr[max_n<<4];
int find(int a){
	if(a==fa[a])return a;
	return fa[a]=find(fa[a]);
}
void addedge(int u,int v){
	e[++ei]=(E){v,fir[u]}; fir[u]=ei;
}
void dfs(int u){
	vis[u]=true;
	for(int i=1;i<=20;++i)fat[u][i]=fat[fat[u][i-1]][i-1];
	for(int i=fir[u],v;i;i=e[i].nx){
		v=e[i].v;
		de[v]=de[u]+1;
		fat[v][0]=u;
		dfs(v);
	}
}
int asklca(int u,int v){
	if(de[u]<de[v])swap(u,v);
	for(int i=20;i>=0;--i){
		if(de[fat[u][i]]>=de[v])u=fat[u][i];
	}
	if(u==v)return u;
	for(int i=20;i>=0;--i){
		if(fat[u][i]^fat[v][i]){
			u=fat[u][i];
			v=fat[v][i];
		}
	}
	return fat[u][0];
}
void build(int o,int l,int r){
	if(l>=r){
		tr[o]=ans[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
int query(int o,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[o];
	int res=0;
	int mid=(l+r)>>1;
	if(ql<=mid)res=max(res,query(o<<1,l,mid,ql,qr));
	if(qr>mid)res=max(res,query(o<<1|1,mid+1,r,ql,qr));
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706E_1.in","r",stdin);
	freopen("CF1706E_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=m;++i){
			scanf("%d%d",&l[i].u,&l[i].v);
			l[i].w=i;
		}
		for(int i=1;i<=(n<<1);++i){
			fa[i]=i;
			fir[i]=0;
			vis[i]=false;
		}
		fi=n;
		ei=0;
		for(int i=1,u,v,uf,vf;i<=m;++i){
			u=l[i].u;
			v=l[i].v;
			uf=find(u);
			vf=find(v);
			if(uf!=vf){
				fa[uf]=fa[vf]=++fi;
				w[fi]=l[i].w;
				addedge(fi,uf);
				addedge(fi,vf);
			}
		}
		for(int i=fi;i>n;--i){
			if(!vis[i]){
				de[i]=1;
				fat[i][0]=i;
				dfs(i);
			}
		}
		for(int i=1,l;i<n;++i){
			l=asklca(i,i+1);
			ans[i]=w[l];
		}
		build(1,1,n-1);
		for(int i=1,l,r;i<=q;++i){
			scanf("%d%d",&l,&r);
			if(l==r)printf("0 ");
			else printf("%d ",query(1,1,n-1,l,r-1));
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80265906)

By **dengziyue**

---

## 作者：Broken_Eclipse (赞：12)

蒟蒻第一篇题解。

qwq题解里貌似没有和我做法相同的。

来一波主席树+二分+启发式合并。

## 题意：

给定一个 $n$ 个点，$m$ 条边的无向连通图，以及 $q$ 个询问，查询至少加到编号前多少条边时能使编号在区间 $[l,r]$ 的所有节点连通。

## 解题思路：

观察到“编号在区间 $[l,r]$ 的所有节点是否连通”在加边时具有单调性，因为加到某一条边之后 $[l,r]$ 连通了，此后所有的状态一定也是连通的。所以不难想到二分一个边的编号 $i$，判断加边加到 $i$ 时其是否连通。

关键在于如何判断一个区间是连通的。

发现如果使用并查集维护图的连通性，一个区间是连通的，当且仅当这些节点路径压缩后的祖先相同，可以用线段树维护。 

将两个集合合并的时候需要将某一集合内节点的祖先全部修改，因此可以用 ```vector``` 存一下集合中的元素，进行启发式合并。合并的复杂度是 $O(n\log^2n)$（要在线段树上修改祖先）。

由于我们还需要保存所有加边加到某一条边时图的连通状态，查询时应该在代表某个状态的线段树上查询，实际上可以打主席树。查询的复杂度是 $O(n\log^2n)$。

好，然后发现空间炸了。每个节点最多会被合并 $\log n$ 次，每次修改 $\log n$ 个线段树节点，因此空间也是 $O(n\log^2n)$ 的。

但是这个上界好像达不到，空间开到 ```100000*150``` 就过了qwq。

细节见代码。

## 代码：

```
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define Reg register
#define lson(rt) tr[rt].ls
#define rson(rt) tr[rt].rs
using namespace std;
const int maxn=100100;
int T,tot,n,m,q,f[maxn],RT[maxn<<1];
vector<int> S[maxn];
struct EE{
    int ls,rs,v;
    bool fl;
    EE(){ls=rs=v=0,fl=0;}
    EE operator +(const EE &A)const{
        EE res;
        if(fl&&A.fl){
            if(v==A.v){
                res.fl=1,res.v=v;
            }
        }
        return res;
    }
}tr[maxn*150];
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<1)+(s<<3)+(ch^48);
        ch=getchar();
    }
    return s*w;
}
inline void pushup(int rt){
    tr[rt].fl=tr[rt].v=0;
    if(tr[lson(rt)].fl&&tr[rson(rt)].fl){
        if(tr[lson(rt)].v==tr[rson(rt)].v){
            tr[rt].fl=1;
            tr[rt].v=tr[lson(rt)].v;
        }
    }
}
inline int build(int l,int r){
    int dir=++tot;
    if(l==r){
        tr[dir].v=l;
        tr[dir].fl=1;
        return dir;
    }
    int mid=(l+r)>>1;
    lson(dir)=build(l,mid);
    rson(dir)=build(mid+1,r);
    pushup(dir);
    return dir;
}
inline int finds(int x){
    if(x!=f[x]) f[x]=finds(f[x]);
    return f[x];
}
inline int update(int rt,int l,int r,int p,int v){
    int dir=++tot;
    tr[dir]=tr[rt];
    if(l==r){
        tr[dir].v=v;
        return dir;
    }
    int mid=(l+r)>>1;
    if(p<=mid) lson(dir)=update(lson(rt),l,mid,p,v);
    else rson(dir)=update(rson(rt),mid+1,r,p,v);
    pushup(dir);
    return dir;
}
inline EE query(int rt,int L,int R,int l,int r){
    if(l<=L&&R<=r) return tr[rt];
    int mid=(L+R)>>1;
    if(r<=mid) return query(lson(rt),L,mid,l,r);
    else if(l>mid) return query(rson(rt),mid+1,R,l,r);
    else{
        EE K=query(lson(rt),L,mid,l,mid);
        if(!K.fl) return K;
        //注意这里，左区间不存在相同的祖先时直接返回即可
        else return K+query(rson(rt),mid+1,R,mid+1,r);
    } 
}
inline void solve(){
    n=read(),m=read(),q=read();
    for(Reg int i=1;i<=n;++i) f[i]=i,S[i].clear(),S[i].push_back(i);
    tot=0;
    RT[0]=build(1,n);
    for(Reg int i=1;i<=m;++i){
        RT[i]=RT[i-1];
        int x=read(),y=read();
        x=finds(x),y=finds(y);
        if(x==y) continue;
            if(S[x].size()<S[y].size()){
                f[x]=y;
                while(S[x].size()){
                    RT[i]=update(RT[i],1,n,S[x].back(),y);
                    S[y].push_back(S[x].back());
                    S[x].pop_back();
                }
            }else{
                f[y]=x;
                while(S[y].size()){
                    RT[i]=update(RT[i],1,n,S[y].back(),x);
                    S[x].push_back(S[y].back());
                    S[y].pop_back();
                }
            } 
    }
    while(q--){
        int l=read(),r=read();
        int L=0,R=m,ans=0;
        while(L<=R){
            int mid=(L+R)>>1;
            if(query(RT[mid],1,n,l,r).fl) ans=mid,R=mid-1;
            else L=mid+1;
        }
        printf("%d ",ans);
    }
    printf("\n");
}
int main(){
    T=read();
    while(T--) solve();
    return 0;
}
```

完结撒花qwq。








---

## 作者：蒟蒻君HJT (赞：11)

一道方法很多的图论 $+$ 数据结构题。放在 div.2 的最后一题太简单了，可能扔到 edu 场会更好。

#### 题意：给出 $n$ 个点， $m$ 条边的不带权连通无向图， $q$ 次询问至少要加完编号前多少的边，才能使得 $[l,r]$ 中的所有点两两连通。

## 方法一、Kruskal 重构树

思考 Kruskal 重构树的最基本的功能是什么：它可以帮助我们求出带权图上的连通两点之间的所有路径中最大边权的最小值（或者最小边权的最大值）。

那么在本题中，我们可以把每条边的边权看做它的编号。这样一来，对于每个询问，若 $l=r$ ，显然答案是 $0$；否则，答案就是 $l,l+1,...,r$ 这 $r-l+1$ 个点在 Kruskal 重构树上的最近公共祖先。

于是，整道题目就被我们化简成了：给定一棵树，$q$ 次求 $[l,r]$ 的 LCA。

最 naive 的办法是：注意到 LCA 运算具有交换律和结合律，所以直接用线段树维护，时间复杂度 $O(n\log n+q\log^2 n)$。常数不小，实现优秀的话可以通过。（我就这么写的）

其实稍微转化一下就能大大降低复杂度。首先在 Kruskal 重构树上我们可以用 $O(\log n)$ 的时间复杂度求出任意两点 $x,y$ 最早连通的时间（即那个 $k$），又因为当 $l<r$ 时，$[l,r]$ 区间中的点全部两两连通完全等价于 $l$ 与 $l+1$ 连通，$l+1$ 与 $l+2$ 连通 $\cdots$ $r-1$ 与 $r$ 连通，所以我们可以预处理出 $f_i$ 表示点 $i$ 与点 $i+1$ 最早连通的时间（$1\leq i \leq n - 1$），问题就进一步简化成了求 $f_i$ 在区间 $[l,r-1]$ 上的静态最大值，用线段树或者 ST 表都可以，时间复杂度 $O((n+q)\log n)$ 或 $O(n\log n+q)$。

## 方法二、整体二分

在方法一中，我们在第二部分中已经把问题转化成了“预处理出 $f_i$ 表示点 $i$ 与点 $i+1$ 最早连通的时间（$1\leq i \leq n - 1$）”，求出所有 $f_i$ 后就很简单了。

如果不会 Kruskal 重构树和可持久化并查集，怎么办呢？整体二分这个算法就可以派上用场了。

最简单的二分想法：对于每个 $i$，暴力二分加到了前 $x$ 条边，用并查集判断连通性，复杂度爆炸。

把每个 $f_i$ 看作一个询问，用整体二分处理它们。考虑当前在计算一些答案值域在 $[l,r]$ 中的询问。若 $l=r$，更新对应的 $f_i$，**并将编号为** $l=r$ **的这条边永久加上，这是为了保证我们每次在处理答案值域在** $[l,r]$ **中的询问的时候，编号在** $[1,l-1]$ **中的边必须已经加上了** 。若 $l<r$，则临时加上 $[l,mid]$ 的边，把询问划分成两部分，并将 $[l,mid]$ 的边撤回。然后先递归左半边再递归右半边。所以需要使用可撤销并查集。时间复杂度 $O(m\log m\log n+q)$ 或 $O(m\log m\log n + q\log n)$。

方法一复杂度 $O(n\log n+q\log^2 n)$ 的代码。

```cpp
#include <bits/stdc++.h>
void solve();
signed main(){
	int T = 1;
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
int n, m, q, fa[300005], tot, anc[20][300005], dep[300005];
int val[400005];
int fd(int x){
	return x == fa[x] ? x : fa[x] = fd(fa[x]);
}
std::vector<int>v[300005];
void dfs(int x){
	for(int i = 1; i <= 19; ++i) anc[i][x] = anc[i - 1][anc[i - 1][x]];
	for(int i = 0; i < v[x].size(); ++i){
		int ver = v[x][i];
		dep[ver] = dep[x] + 1;
		anc[0][ver] = x;
		dfs(ver);
	}
	return ;
}
int lca(int x, int y){
	if(dep[x] < dep[y]) std::swap(x, y);
	for(int i = 0; i <= 19; ++i) if((dep[x] - dep[y]) & (1 << i))
		x = anc[i][x];
	if(x == y) return x;
	for(int i = 19; i >= 0; --i) if(anc[i][x] ^ anc[i][y])
		x = anc[i][x], y = anc[i][y];
	return x == y ? x : anc[0][x];
}
void build(int x, int l, int r){
	if(l == r){
		val[x] = l;
		return ;
	}
	int mid = l + r >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	val[x] = lca(val[x * 2], val[x * 2 + 1]);
	return ;
}
int Query(int x, int l, int r, int L, int R){
	if(l == L && r == R) return val[x];
	int mid = l + r >> 1;
	if(R <= mid) return Query(x * 2, l, mid, L, R);
	if(L >= mid + 1) return Query(x * 2 + 1, mid + 1, r, L, R);
	int y = Query(x * 2, l, mid, L, mid);
	int z = Query(x * 2 + 1, mid + 1, r, mid + 1, R);
	return lca(y, z);
}
void solve(){
	scanf("%d%d%d", &n, &m, &q);
	tot = 0;
	for(int i = 1; i <= n + m; ++i) fa[i] = i;
	for(int i = 1; i <= n + m; ++i) v[i].clear();
	for(int i = 1; i <= m; ++i){
		int u, vv;
		scanf("%d%d", &u, &vv);
		int fu = fd(u), fv = fd(vv);
		if(fu == fv) continue;
		v[i + n].push_back(fu), v[i + n].push_back(fv);
		fa[fu] = fa[fv] = i + n;
		tot = i + n;
	}
	dep[tot] = 1;
	dfs(tot);
	build(1, 1, n);
	for(int i = 1; i <= q; ++i){
		int l, r;
		scanf("%d%d", &l, &r);
		if(l ^ r) printf("%d ", Query(1, 1, n, l, r) - n);
		else printf("0 ");
	}
	printf("\n");
	return ;
}
```


---

## 作者：_jimmywang_ (赞：5)

前几天刚学 $\text{Kruskal}$ 重构树，用到 CF 里就不会了……

对于每个询问 $(l,r)$，有以下两种情况：

- $l=r$，此时显然答案为 0。

- $l<r$。

对于第二种情况，可以构造一个函数 $f(i)$ 为将点 $i$ 和 $i-1$ 两点连通的最小边数。换句话说，就是一组 $(i-1,i)$ 的询问。

于是现在，我们的 $ans_{(l,r)}=\max_{i=l+1}^r f(i)$。

于是我们就需要考虑 $f(i)$ 怎么求。

可以发现，如果对第 $i$ 条边赋一个边权 $w=i$，那么用 $\text{Kruskal}$ 生成的最小生成树唯一且与原生成树相同。

于是边的编号转化为边的边权，现在 $f(i)$ 变为求树上 $i$ 和 $i-1$ 路径上的最大边。

于是想到 $\text{Kruskal}$ 重构树。

对原图加入边权后，跑出一颗 $\text{Kruskal}$ 重构树，然后求 $i$ 与 $i-1$ 
的 $\text{lca}$ 的点权，就是 $f(i)$。

然后对于区间 $\max$，上一个 ST 表就能解决问题。

```
// Problem: E. Qpwoeirut and Vertices
// Contest: Codeforces Round #809 (Div. 2)
// URL: https://codeforces.com/contest/1706/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m,cnt,q;
vi e[200010];
ll val[200010];
struct node{ll u,v,w;}a[200010];
bool cmp(node a,node b){return a.w<b.w;}
ll fa[200010];
ll find(ll x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
ll f[200010][20];
ll de[200010];
ll st[200010][20];
ll lg[200010];
void dfs(ll u,ll fat){
	f[u][0]=fat;
	de[u]=de[fat]+1;
	fe(i,e[u]){
		ll v=e[u][i];
		if(v==fat)continue;
		dfs(v,u);
	}
}ll lca(ll u,ll v){
	if(de[u]<de[v])swap(u,v);
	for(int i=19;i>=0;i--)
		if(de[u]-(1<<i)>=de[v]){
			u=f[u][i];
			if(u==v)return u;
	}
	for(int i=19;i>=0;i--)
		if(f[u][i]!=f[v][i])
			u=f[u][i],v=f[v][i];
	return f[u][0];
}
int main(){
	wt{
		n=d,m=d,q=d;cnt=n;
		f(i,1,n*2)e[i].clear(),fa[i]=i,de[i]=0;
		f(i,1,m)a[i]={d,d,i};
		sort(a+1,a+m+1,cmp);
		f(i,1,m){
			ll u=a[i].u,v=a[i].v,w=a[i].w;
			if(find(u)==find(v))continue;
			val[++cnt]=w;
			u=find(u),v=find(v);
			fa[u]=cnt,fa[v]=cnt;
			e[cnt].pb(u),e[cnt].pb(v);
		}
		dfs(cnt,0);
		f(j,1,19)f(i,1,cnt)f[i][j]=f[f[i][j-1]][j-1];
		f(i,2,n)st[i][0]=val[lca(i,i-1)];
		lg[0]=-1;f(i,1,n)lg[i]=lg[i/2]+1;
		f(j,1,19)f(i,1,n)if(i+(1<<(j-1))<=n)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		while(q--){
			ll l=d,r=d;
			if(l==r){printf("0 ");continue;}
			l++;
			printf("%lld ",max(st[l][lg[r-l+1]],st[r-(1<<lg[r-l+1])+1][lg[r-l+1]]));
		}puts("");
	}
	return 0;
}
```


---

## 作者：Doubeecat (赞：4)

# E. Qpwoeirut and Vertices

> 给定一张 $n$ 个点 $m$ 条边的无向连通图，有 $q$ 个询问，每次询问给定两个数 $l,r$，请你给出最小的 $k$ 使得：
>
> 仅使用前 $k$ 条边就能使所有点对 $(a,b)$ 联通，其中 $a,b$ 满足 $l \leq a \leq b \leq r$。
>
> $n \leq 10^5,m,q \leq 2\times 10^5$

## 分析

这个题其实和 [AGC002D](https://atcoder.jp/contests/agc002/tasks/agc002_d) 有着一定的相似之处，这类在图上求一些最值的题比较常见的套路要么是线段树分治，要么是 Kruskal 重构树。

这题线段树分治显然是没有什么前途的，所以我们考虑 Kruskal 重构树。由于这题求的是按照边的顺序，所以我们把边的权值赋为边的序号，排序后建出 Kruskal 重构树。

那么我们现在的问题就变成了，对于在 $[l,r]$ 内的点，我们需要找到他们的 LCA 来保证是能联通的（这个就是 Kruskal 重构树的基本性质了，不再赘述）。对于求多个点 LCA 的问题，我们可以给出结论：**树上多个点的 LCA，就是 DFS 序最小的和 DFS 序最大的这两个点的 LCA。**详细的证明可以戳 [如何在 DAG 中找多个点的 LCA ? - 阮行止的回答 - 知乎](https://www.zhihu.com/question/46440863/answer/165741734)

所以我们就在 $\mathcal{O}((m+q)\log n)$ 的时间内解决了本题。

## 代码

考场代码 最后 2 min 过的，所以略粗糙。

```cpp
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define ll long long

char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
template <typename T> inline void read(T &t) {
	int v = getchar();T f = 1;t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	t *= f;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args) {
	read(t);read(args...);
}
const int N = 4e5 + 10;
const int K = 26;

int n,m,q,k,s,dis[N],F[N],poi[N],val[N],tot,fat[N][K],dep[N],dfn[N],rk[N],cnt,siz[N];
bool vis[N];
vector <int> G[N];
vector <pii> G2[N];

struct edg {
    int u,v,w;
    friend inline bool operator < (const edg &A,const edg &B) {
        return A.w < B.w;
    }
}edge[N];

int find(int x) {return x == F[x] ? x : F[x] = find(F[x]);}

void clear() {
    tot = n;cnt = 0;
    for (int i = 1;i <= (n << 1);++i) G[i].clear(),F[i] = i,dfn[i] = rk[i] = 0;
    //memset(fat,0,sizeof fat);
}

void Kruskal() {
    //poi[0] = 0x3f3f3f3f;
    for (int i = 1;i <= m;++i) {
        int u = edge[i].u,v = edge[i].v,w = edge[i].w;
        //printf("%d %d %d %d\n",u,v,find(u),find(v));
        u = find(u),v = find(v);
        if (u != v) {
            ++tot;
            poi[tot] = w;
            //poi[u] = poi[v] = w;
            F[u] = F[v] = tot;
            G[tot].push_back(u);
            G[u].push_back(tot);
            G[tot].push_back(v);
            G[v].push_back(tot);
        }
    }
}

void dfs(int x,int fa) {
    fat[x][0] = fa;
    dep[x] = dep[fa] + 1;
    dfn[x] = ++cnt;rk[cnt] = x;
    //printf("%d %d\n",fa,x);
    for (int j = 1;j <= 20;++j) {
        fat[x][j] = fat[fat[x][j-1]][j-1];
    }
    for (auto y : G[x]) {
        if (y != fa) {
            dfs(y,x);
        }
    }
}

int LCA(int x,int y) {
    if (dep[x] > dep[y]) swap(x,y);
    for (int i = 20;i >= 0;--i) {
        if (dep[fat[y][i]] >= dep[x]) {
            y = fat[y][i];
        }
    }
    if (x == y) return x;
    for (int i = 20;i >= 0;--i) {
        if (fat[x][i] != fat[y][i]) {
            x = fat[x][i];
            y = fat[y][i];
        }
    }
    return fat[x][0];
}

int st1[K][N],st2[K][N];

void init() {
    for (int j = 0;j <= 20;++j) {
        for (int i = 1;i + (1 << j) - 1 <= n;++i) {
            if (!j) st1[j][i] = st2[j][i] = dfn[i];
            else {
                st1[j][i] = min(st1[j-1][i],st1[j-1][i + (1 <<j-1)]);
                st2[j][i] = max(st2[j-1][i],st2[j-1][i + (1 <<j-1)]);
            }
        }
    }
}

int query1(int l,int r) {
    int now = log(r - l + 1) / log(2);
    return min(st1[now][l],st1[now][r - (1 << now) + 1]);
}

int query2(int l,int r) {
    int now = log(r - l + 1) / log(2);
    return max(st2[now][l],st2[now][r - (1 << now) + 1]);
}


void solve() {
    int q;
    read(n,m,q);
    clear();
    for (int i = 1;i <= m;++i) {
        read(edge[i].u,edge[i].v);
        edge[i].w = i;
    }
    sort(edge + 1,edge + 1 + m);
    Kruskal();
    dfs(tot,0);init();
    //for (int i = 1;i <= n;++i) printf("i:%d ",dfn[i]);
    //puts("");
    for (int i = 1;i <= q;++i) {
        int l,r;read(l,r);
        if (l == r) printf("%d ",0);
        else {
            int u = rk[query1(l,r)],v = rk[query2(l,r)];
            //printf("u,v:%d %d l:%d\n",u,v,query1(l,r));
            printf("%d ",poi[LCA(u,v)]);
        }
    }
    puts("");
}

signed main() {
    int T;read(T);
    while (T--) solve();
	return 0;
}

```



---

## 作者：Mashiroqwq (赞：3)

[你谷题目传送门](https://www.luogu.com.cn/problem/CF1706E)

[CF 题目传送门](https://codeforces.com/contest/1706/problem/E)

## 题目大意

给定一个 $n$ 个点 $m$ 条边的无向图，询问 $q$ 次，每次询问会指定两个正整数 $l,r$，问要使对于 $l \leq a \leq b \leq r$ 的所有 $a,b$ 均有路径可以互相到达，最少需要加入前多少条边。

## 思路

考虑到每一次询问实质上就是问你在按顺序加了多少条边之后，编号 $[l,r]$ 之间的点都在同一个联通块中。

记 $mintim(i)$ 表示 $i$ 和 $i+1$ 在加了 $mintim(i)$ 条边之后处在同一个联通块，那么每一次询问的答案就是 $\max_{i=l}^{r-1} mintim(i)$。

在求解出所有的 $mintim(i)$ 之后就可以直接用 ST 表或者线段树解决区间查询。

那么现在问题在于怎么求解 $mintim(i)$。

考虑顺序加边用启发式合并的思想处理 $mintim(i)$，具体操作流程如下：

- 当前要合并 $x,y$ 所在的集合 $S(x),S(y)$。
- 如果 $|S(x)|<|S(y)|$，那么遍历 $S(x)$ 中的每一个元素 $p \in S(x)$，处理 $mintim(p-1)$ 和 $mintim(p)$。
- 否则交换 $x,y$ 再操作即可。

不难看出每一个点在启发式合并的过程中最多被合并 $\log_2 n$ 次，而并查集复杂度为 $O(α(n))$，所以处理 $mintim$ 的这一部分复杂度为 $O(n \log_2 n α(n))$。

总时间复杂度 $O(n \log_2 n α(n)+q \log_2 n)$，可以通过本题。

```cpp
#include<bits/stdc++.h>

#define RI register int
#define ll long long
#define ull unsigned long long
#define YES puts("YES")
#define NO puts("NO")

using namespace std;

namespace IO{
	inline int read(){
		RI X=0, W=0;register char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(int x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
}using namespace IO;

const int MAXN = 2e5+5;

int n, m, q;
int fa[MAXN];
int tree[MAXN << 2], minn[MAXN];
int siz[MAXN];

vector<int> G[MAXN];

inline int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

inline void build(int p, int l, int r){
	if(l==r){
		tree[p]=minn[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid), build(p<<1|1,mid+1,r);
	tree[p]=max(tree[p<<1],tree[p<<1|1]);
}

inline int ask(int p, int l, int r, int L, int R){
	if(L>R) return 0;
	if(L<=l && r<=R) return tree[p];
	int mid=(l+r)>>1, res=0;
	if(L<=mid) res=ask(p<<1,l,mid,L,R);
	if(R>mid) res=max(res,ask(p<<1|1,mid+1,r,L,R));
	return res;
}

inline void solve(){
	//4 [space]
	n=read(),m=read(),q=read();int p;fa[n+1]=n+1;
	for(int i=1;i<=n;++i) G[i].clear(), G[i].push_back(i), fa[i]=i, siz[i]=1, minn[i]=1e9;
	for(int i=1;i<=m;++i) {
		int x, y;
		x=read(), y=read();
		x=find(x), y=find(y);
		if(x==y) continue;
		if(siz[x]>siz[y]) swap(x,y);
		siz[y]+=siz[x];fa[x]=y;
		for(int A=0;A<G[x].size();++A){
			p=G[x][A];
			if(find(p)==find(p+1)) minn[p]=min(i,minn[p]);
			if(find(p)==find(p-1)) minn[p-1]=min(minn[p-1],i);
			G[y].push_back(p);
		}
		G[x].clear();siz[x]=0;
	}
	build(1,1,n-1);
	while(q--){
		int l, r;
		l=read(), r=read();
		write(ask(1,1,n-1,l,r-1)), putchar(32);
	}
	putchar(10);
}

int main(){
	int t=read();
	while(t--) solve();
	return 0;
}
```

最后附上 [评测记录](https://codeforces.com/contest/1706/submission/164778835)。

---

## 作者：Frevotops (赞：2)

## 1706E [graph] [dsu]

考虑把 $[l,r]$ 区间内的联通条件拆成 $(l,l+1)$，$(l+1,l+2)$，……，$(l+1,r)$ 分别联通至少要有几条边，答案取 $\max$ 即可。

然后我们考虑如何处理这些问题。我用的是启发式合并，把询问挂在集合里（此时询问的左端点已经不重要）。合并两个集合的时候，选择处理询问少的集合，这些询问的答案对当前合并的边的编号求 $\min$。再把元素较少的合并到元素较多的。

你可能会问，这样真的处理完所有询问了吗？答案是肯定的。因为两个点合并到一起的时候，必然有一个点在小的集合里，那么这个询问就会被处理。

自己想的一个很妙的做法……

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m,q,f[200005],u[200005],v[200005],ans[200005],sz[200005],w[25][200005];
vector<pair<ll,ll> >Q[200005];
map<ll,bool>M[200005];
ll query(ll l,ll r){
	ll p2=log2(r-l+1);
	return max(w[p2][l],w[p2][r-(1ll<<p2)+1]);
} 
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(ll i=1;i<=n;i++) f[i]=i, sz[i]=1, Q[i].clear(), M[i].clear(), M[i][i]=1, ans[i]=1e18;
		for(ll i=1;i<=m;i++)
			cin>>u[i]>>v[i];
		for(ll i=1;i<n;i++) Q[i].push_back(make_pair(i+1,i)), Q[i+1].push_back(make_pair(i,i)); // 注意，询问两个点上都得挂
		for(ll i=1;i<=m;i++){
			if(f[u[i]]==f[v[i]]) continue;
			ll x=f[u[i]], y=f[v[i]];
			if(Q[x].size()>Q[y].size()) swap(x,y);
			for(auto p: Q[x]){
				ll to=p.first, id=p.second;
				if(M[y].count(to)) ans[id]=min(ans[id],i);
				Q[y].push_back(p);
			}
			Q[x].clear(); // 处理询问
			if(sz[x]>sz[y]) swap(Q[x],Q[y]),swap(x,y);
			for(auto p: M[x]){
				ll now=p.first;
				f[now]=y; M[y][now]=1;
			} sz[y]+=sz[x];
			M[x].clear(); sz[x]=0; // 处理点集
		}
		for(ll i=1;i<n;i++) w[0][i]=ans[i];
		ll p=log2(n-1);
		for(ll i=1;i<=p;i++)
			for(ll j=1;j<=(n-(1ll<<i));j++)
				w[i][j]=max(w[i-1][j],w[i-1][j+(1ll<<(i-1))]);
		while(q--) {
			ll l,r; cin>>l>>r;
			if(l==r) cout<<0<<" ";
			else cout<<query(l,r-1)<<" "; 
		}
        cout<<endl; 
	}
	return 0; 
} 
```

---

## 作者：yzy1 (赞：2)

结论：$n-1$ 组互不相同的条件，每组条件形如点集 $S$ 中两点连通，可确定大小为 $n$ 的点集 $S$ 中的任意两点均连通。

证明： 将各组条件两点连边，形成一棵树，显然树上任意两点连通。

推论 $1$：若 $S_1$ 中任意两点连通，$S_2$ 中任意两点连通，$S_1 \cap S_2 \ne \varnothing$，则 $S_1\cup S_2$ 中任意两点连通。反之仍然成立。

推论 $2$：若 $S_1,S_2,\cdots,S_n$ 这 $n$ 个点集中，在同一个点集中的任意两点均连通。且 $S_{i} \cap S_{i+1} \ne \varnothing(1 \le i<n)$。设 $S_1 \cup S_2\cup \cdots\cup S_n=S$，则 $S$ 中任意两点连通。反之仍然成立。

## 做法 1

考虑分块，根据推论，区间连通相当于：每个块内连通，且相两个块连通。

每个块内最先连通的时间可以预处理。

相邻俩块之间连通可以询问离线，最后一起算。

时间复杂度 $O((n+q)\sqrt n \alpha(n))$。

## 做法 2

由于集合并运算满足 $U \cup U=U$，且根据推论，原区间询问是一个[**可重复贡献问题**](https://oi-wiki.org/ds/sparse-table/#_1)，考虑用 ST 表维护。

ST 表合并区间时，额外与两个区间中的左端点连通的时间取 $\max$ 即可。

可以发现，预处理时会产生 $O(n\log n)$ 次对两点连通时间的查询，回答询问时会产生 $O(q)$ 次对两点连通时间的查询。可以预先将这下查询离线，然后整体二分即可。

时间复杂度 $O(n\log^2 n \alpha(n)+q\log n \alpha(n))$。

---

## 作者：CReatiQ (赞：2)

### 题意概述

给定一张 $n$ 点 $m$ 边的无向连通图。

有 $q$ 次询问，求第一次连通给定两点的边的序号。

$( 2 \leq n \leq 10^5 , 1 \leq m,q \leq 2 \cdot 10^5 )$

---

### 思路

用并查集 ( 路径压缩 + 启发式合并 ) 维护点的连通性，用线段树维护首次连通区间的边的序号。

考虑线段树如何维护该信息：

 $n$ 个节点按序号排列，相邻两个区间连通，则两个区间的和区间连通。

既然要求的是一个区间的连通，那叶子节点维护连接相邻节点的边的序号，向上合并时取最大值即可。

考虑如何更新线段树中维护的信息：

每次加边时，影响的点不一定连续，所以更新操作是单点修改。

为了遍历每个受加边影响的点，我们可以试着再利用一下刚才的并查集。

每次加边，都是两个并查集之间的合并。

因为加边影响的是相邻节点恰好分别在两并查集中的情况，所以两者中的任意一个，都包含了所有受影响的元素。

我们希望遍历尽量少的点，当然选择遍历较小的那个并查集。

遍历只需要我们模拟一下加边过程，然后在启发式合并时跑个 `dfs` 即可。

因为采用启发式合并，我们遍历的节点最多为 $\frac{n}{2}\log n$ 个，线段树单点修改，区间查询复杂度均为 $\mathcal{O}(\log n)$ ，所以总时间复杂度为 $\mathcal{O}(n \log^2 n + q \log n)$ 。

---

### Code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring> 
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
using namespace std;
#define int long long
#define MAXN (int)(3e5+233)

namespace crq
{

	inline long long read()
	{
		long long x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
		return f*x;
	}

	template <typename T> inline T max(T x,T y) { return x>y?x:y; }
	
	inline int zero() { return 0; }

	template <typename A,typename... B>
	A max(A first,B... others)
	{ return max(first,max(others...)); }
	
	template <typename crq,crq(*op)(crq,crq),crq e()>
	struct Seg
	{
		
		//Tips: The id of this Segment Tree is begin at 1 but not 0.
		
		public:
		
			Seg(int n)
			{
				init_pow2();
				h=ceil_log2(n);
				SIZE=1<<h;
				val=std::vector<crq>(SIZE<<1,e());
			}
		
			Seg(int n,crq *poi)
			{
				init_pow2();
				h=ceil_log2(n);
				SIZE=1<<h;
				val=std::vector<crq>(SIZE<<1,e());
				for (int i=0;i<n;i++) val[SIZE+i]=*(poi+i);
				for (int i=SIZE-1;i>=1;i--) pushup(i);
			}//If you want to build the Segment Tree by a vector,
			 //you can try to use "Seg(vector.size(),vector.data())".
			 //However,you can't use "Seg(vector.size(),vector.begin())"
			 //because a iterator isn't equal to a pointer.
			 //plz pay attention to it.
			 //——crq 2022.7.22
			 
			void init(int n)
			{
				init_pow2();
				h=ceil_log2(n);
				SIZE=1<<h;
				val=std::vector<crq>(SIZE<<1,e());
			}
			
			void modify(int k,crq x)
			{
				k+=SIZE-1;
				val[k]=x;
				for (int i=1;i<=h;i++) pushup(k>>=1);
			}
			
			crq get(int k) { return val[SIZE+k-1]; }
			
			crq query(int l,int r)
			{
				l--;
				crq sl=e(),sr=e();
				l+=SIZE,r+=SIZE;
				while (l<r)
				{
					if (l&1) sl=op(sl,val[l++]);
					if (r&1) sr=op(sr,val[--r]);
					l>>=1,r>>=1;
				}
				return op(sl,sr);
			}//query the answer of [l,r]
		
		private:
			
			int h=0,SIZE=0,pow2[27];
			std::vector<crq> val;
			
			void init_pow2()
			{
				pow2[0]=1;
				for (int i=1;i<=25;i++) pow2[i]=pow2[i-1]<<1;
			} 
			
			int ceil_log2(int x)
			{
				for (int i=25;i>=1;i--)
					if (pow2[i]>=x&&pow2[i-1]<x)
						return i;
				return 0;
			}
			
			inline void pushup(int now) { val[now]=op(val[now<<1],val[now<<1|1]); }
		
	};
	
}

using crq::read;
using crq::Seg;

struct Edge
{
	int to,nex;
} E[MAXN<<1];
 
int T,n,m,q,cnt,fa[MAXN],siz[MAXN],head[MAXN];
Seg<int,crq::max,crq::zero> s(MAXN);

inline void add(int u,int v)
{
	E[++cnt].to=v;
	E[cnt].nex=head[u];
	head[u]=cnt;
}

void init()
{
	cnt=0,s.init(n);
	for (int i=1;i<=n;i++) fa[i]=i,head[i]=0,siz[i]=1;
}

int find(int x)
{
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

void dfs(int x,int f,int t)
{
	if (!s.get(x)&&find(x)==find(x-1))
		s.modify(x,t);
	if (!s.get(x+1)&&find(x)==find(x+1))
        s.modify(x+1,t);
	for (int i=head[x];i;i=E[i].nex)
		if (E[i].to!=f)
			dfs(E[i].to,x,t);
}

void merge(int x,int y,int t)
{
	x=find(x);
	y=find(y);
	if (x==y) return;
	if (siz[x]<siz[y]) swap(x,y);
	fa[y]=x;
	siz[x]+=siz[y];
	dfs(y,0,t);
	add(x,y),add(y,x);
}

signed main()
{
	cin>>T;
	while (T--)
	{
		cin>>n>>m>>q;
		init();
		for (int i=1;i<=m;i++)
		{
			int a=read(),b=read();
			merge(a,b,i);
		}
		for (int i=1;i<=q;i++)
		{
			int a=read(),b=read();
            if (a==b) printf("0 ");
			else printf("%lld ",s.query(a+1,b));
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Zeardoe (赞：2)

题意：给定一个 $n$ 点 $m$ 边无向连通图，有 $q$ 次询问，每次给定区间 $[l,r]$，求区间内所有点之间简单路径最大边权的最小值。

分析：转化为 Kruskal 重构树，那么每次就是求区间里每个点的 LCA。
但是区间 LCA 暴力做还是复杂度不够。我们考虑区间 LCA 就是区间上 $dfn$ 最大和最小的两个点的 LCA，那么我们再用俩 ST 表或者一棵线段树记录区间 $dfn$ 的最大最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
int N = 200000;
int n,m,q;
vector<int> g[200010];
int lg2[200010];
vector<int> dep, dfn;
vector<int> stmx[200010], stmn[200010], anc[200010];
int cha[200010];
struct rec{
	int x,y,z;
}edge[500010];
bool operator<(rec a,rec b){
	return a.z<b.z;
}
int qz[200010];
int fa[200010]; 
int get(int x){
	if(fa[x]==x)return x;
	else return fa[x] = get(fa[x]);
}
int kruskal() {
    int cnt = n;
    f(i,1,2*n)fa[i]=i;
    f(i, 1, m) {
        int x = get(edge[i].x);
		int y = get(edge[i].y);
		if(x == y)continue;
        else {
            int z = ++cnt;
            g[x].push_back(z); g[y].push_back(z);
            g[z].push_back(x); g[z].push_back(y);
            fa[x]=z;fa[y]=z;
            qz[z] = edge[i].z;
        }
    }
    return cnt;
}
int ccnt;
void dfs(int now, int fa) {
    dfn[now] = ++ccnt;
    dep[now] = dep[fa] + 1; anc[now][0] = fa;
    f(i, 1, lg2[dep[now]] - 1) {
        anc[now][i] = anc[anc[now][i - 1]][i - 1];
    }
    f(i, 0, (int)g[now].size() -1 ) {
        if(g[now][i] != fa) dfs(g[now][i], now);
    }
}
int lca(int qx, int qy) {
    if(dep[qx] < dep[qy]) swap(qx, qy);
    while(dep[qx] > dep[qy]) {
        qx = anc[qx][lg2[dep[qx]-dep[qy]] - 1];
    }
    if(qx == qy) return qx;
    for(int k = lg2[dep[qx]] - 1; k >= 0; k--) {
        if(anc[qx][k] != anc[qy][k]) {
            qx = anc[qx][k]; qy = anc[qy][k];
        }
    }
    return anc[qx][0];
}
 
void STmx_prework() {
    f(i, 1, n) stmx[i][0] = dfn[i];
    int mx = log(n) / log(2);
    f(j, 1, mx) {
    	int mxi = n - (1 << j) + 1;
    	f(i, 1, mxi) {
    		stmx[i][j] = max(stmx[i][j - 1], stmx[i + (1 << (j - 1))][j - 1]);
		}
	}
}
void STmn_prework() {
    f(i, 1, n) stmn[i][0] = dfn[i];
    int mx = log(n) / log(2);
    f(j, 1, mx) {
    	int mxi = n - (1 << j) + 1;
    	f(i, 1, mxi) {
    		stmn[i][j] = min(stmn[i][j - 1], stmn[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int querymx(int l, int r) {
    int mx = log(r - l + 1) / log(2);
    int ans;
    ans = max(stmx[l][mx], stmx[r - (1 << mx) + 1][mx]);
    return ans;  
}
int querymn(int l, int r) {
    int mx = log(r - l + 1) / log(2);
    int ans;
    ans = min(stmn[l][mx], stmn[r - (1 << mx) + 1][mx]);
    return ans;  
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    f(i, 1, N) lg2[i] = lg2[i - 1] + (1 << lg2[i - 1] == i);
    int t; cin >> t;
    while(t--) {
        
        cin>>n>>m>>q;
        f(i, 1, m) {
            int u, v; cin >> u >> v; 
            edge[i].x = u, edge[i].y = v, edge[i].z = i;
        }
        sort(edge+1,edge+m+1);
        f(i,1,2*n)g[i].clear();
        int root = kruskal();
        n=2*n;
        cl(dep, n+10);cl(dfn,n+10);
        f(i,0,n+9){
            cl(anc[i],30);cl(stmx[i],30);cl(stmn[i],30);
        }
        
        dfs(root, 0);
        STmx_prework(); STmn_prework();
        f(i,1,n) cha[dfn[i]] = i;
        f(i, 1, q) {
            int l, r; cin >> l >> r; if(l == r) {cout << 0 << " "; continue;}
            int mx = querymx(l, r), mn = querymn(l, r); 
            int lcaa = lca(cha[mx], cha[mn]);
            cout << qz[lcaa] <<" ";
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：Z1qqurat (赞：1)

这个题的题解虽然很多方法也很多，但是感觉 Kruskal 重构树的题解没有什么比较正向推理的解说（也有可能只是鄙人慧眼不识金星），这里只是一些自己的思考和看法，希望能从这个题中体会一下 Kruskal 重构树的魔法。

* 现在我们先不考虑**整个区间都连通**这个条件，我们先想想如果只是询问两个点 $x, y$，要使得它们连通至少需要连**前多少条边**。你会发现这是一个**最小值**问题，如果单次询问，我们就可以将这 $m$ 条边按照编号顺序依次加入**并查集**中，然后如果加完第 $i$ 条边的时候，$x, y$ 已经连通了，那么答案就是 $i$ 了。这样处理一次询问是 $\mathcal {O} (m)$ 的。

  你会发现如果我们这么处理的话每次询问都需要重新从头加一次边，想一想我们能不能让这个答案在一次加边中就都得出？那么我们从头开始加边，就需要构造出**一个能得出任意两个点的答案的确定结构**。两点 $x, y$ 答案其实就是使他们连通而加的最后一条边，你会发现这和**最小生成树**有异曲同工之妙。在最小生成树算法中，我们加上一条边 $(x, y, w)$，如果 $root_x \ne root_y$，那么连接 $(x, y, w)$，而在原先 $x, y$ 分别所在连通块各取一点所构成的点对终于被连通起来了，用因为是最小生成树，所以 $w$ 就是使得这些点对分别连通起来的边权最大的边（这很像 CF1857G 不是吗）。我们这里要求边的编号最小，那我们为什么不把**边的编号当作边权**？

  到这里我们明确了解决问题的答题思路，现在就是说我们怎么对于这些新连通上的点对记录下他们的答案 $w$。**考虑在做最小生成树的时候构建 Kruskal 重构树。**按边编号从小到大依次加入边，每次用边 $(x, y, w)$ 合并时，建立新节点 $f$，$fa_x = fa_y = f, val_f = w$，那么这些 $x, y$ 原先属于的连通块两两组成的点对的**最近公共祖先**的权值 $val$ 就是答案了。

  至此我们解决了直接询问使 $x, y$ 两点连通所需的最小边序号。

* 但是我们需要使得区间 $[l, r]$ 内的点都两两连通。考虑把这个问题转化为区间询问的问题，我们定义 $ans_i$ 表示将节点 $i, i + 1$ 连通起来的答案，由于这个答案是可以合并的，$[l, r]$ 的答案就可以看作 $\max(ans_l,ns_{l + 1}, \dots ,ans_{r - 1})$。所以我们将 $ans$ 数组预处理出来，相当于一个**静态区间查询，且答案可合并。**考虑使用 ST 表，$st_{i, 0} =ns_i$，然后倍增做就可以了。

所以说使用 Kruskal 重构树可以说是基于最小生成树的处理。这一棵稳定的树结构可以帮助我们在最小生成树构建完毕后方便快捷地查询一些构建过程中得到的一些结果，具有某种意义上的“离线”功能。我会的只有这么多，这只是一个菜狗的口胡，大家当乐子看看就行。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define mr make_pair
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5;
int t, n, nn, maxd, maxl, m, q, st[N][30], fa[N][30], dep[N];
vector <int> T[N];
pii e[N];

struct DSU{
    int fa[N], val[N];
    void init() {
        for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
        return ;
    }
    int getroot(int x) {
        if(fa[x] == x) return x;
        return fa[x] = getroot(fa[x]);
    }
    void merge(int x, int y, int w) {
        fa[x] = fa[y] = ++nn, val[nn] = w;
        T[nn].push_back(x), T[nn].push_back(y);
        return ;
    }
}D;

void dfs(int u, int ff) {
    fa[u][0] = ff, dep[u] = dep[ff] + 1;
    for (int i = 0; i < T[u].size(); ++i) {
        int v = T[u][i];
        if(v == ff) continue;
        dfs(v, u);
    }
    return ;
}

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for (int i = maxd; i >= 0; --i) {
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if(x == y) return x;
    for (int i = maxd; i >= 0; --i) {
        if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

void Kruskal() {
    nn = n, D.init();
    for (int i = 1; i <= m; ++i) {
        if(nn == 2 * n - 1) break;
        int x = D.getroot(e[i].fi), y = D.getroot(e[i].se);
        if(x == y) continue;
        D.merge(x, y, i);
    }
    maxd = log2(nn), maxl = log2(n);
    dfs(nn, nn);
    for (int i = 1; i <= maxd; ++i) {
        for (int j = 1; j <= nn; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i < n; ++i) {
        st[i][0] = D.val[LCA(i, i + 1)];
    }
    for (int i = 1; i <= maxl; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
    return ;
}

int query(int l, int r) {
    int k = log2(r - l + 1);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

void solve() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i <= n * 2; ++i) {
        dep[i] = 0; T[i].clear();
        for (int j = 0; j < 20; ++j) {
            fa[i][j] = st[i][j] = 0;
        }
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &e[i].fi, &e[i].se);
    }
    Kruskal();
    // return ;
    for (int i = 1; i <= q; ++i) {
        int l, r; scanf("%d %d", &l, &r);
        if(l == r) cout << "0 ";
        else printf("%d ", query(l, r - 1));
    }
    puts("");
}

int main() {
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}
```

---

## 作者：Daidly (赞：0)

构建“并查集生成树”，即使两个连通块第一次连通的边组成的一棵树，树上边权为原图边的编号。显然，使任意两点联通的答案就是树上两点间路径的边权最大值，可以用树上倍增维护两点间边权最大值。

区间 $[l,r]$ 在树上连通就意味着 $(l,l+1),(l+1,l+2),...,(r-1,r)$ 连通，证明考虑反证法，若区间 $[l,r]$ 连通答案比某两个编号相邻点代价小，则不满足区间连通的条件。取这些答案的最大值即可，可以用 ST 表维护。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e5+5,M=2e5+5;
int n,m,q,head[N],cnt,f[N],lg[N];
struct node{
	int next,to,w;
}e[N<<1];

void add(int from,int to,int w){
	e[++cnt]=(node){head[from],to,w};
	head[from]=cnt;
}

int find(int x){
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}

int maxn[N][22],fa[N][22],dep[N];

void dfs(int x,int fath,int w){
	fa[x][0]=fath;
	dep[x]=dep[fath]+1;
	maxn[x][0]=w;
	for(int i=1;i<=lg[dep[x]];++i)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=1;i<=lg[dep[x]];++i)maxn[x][i]=max(maxn[x][i-1],maxn[fa[x][i-1]][i-1]);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(y!=fath)dfs(y,x,e[i].w);
	}
}

int calc(int x,int y){
	int ans=0;
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y]){
		ans=max(ans,maxn[x][lg[dep[x]-dep[y]]]);
		x=fa[x][lg[dep[x]-dep[y]]];
	}
	if(x==y)return ans;
	for(int i=lg[dep[x]];i>=0;--i){
		if(fa[x][i]!=fa[y][i]){
			ans=max(ans,max(maxn[x][i],maxn[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	}
	ans=max(ans,max(maxn[x][0],maxn[y][0]));
	return ans;
}

int Max[N][22];

void init(){
	for(int i=1;i<=n-1;++i)Max[i][0]=calc(i,i+1);
	for(int j=1;j<=lg[n-1];++j){
		for(int i=1;i+(1<<j)-1<=n-1;++i){
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
		}
	}
}

int qry(int l,int r){
	if(l>r)return 0;
	int tmp=lg[r-l+1];
	return max(Max[l][tmp],Max[r-(1<<tmp)+1][tmp]);
}

void solve(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		int fu=find(u),fv=find(v);
		if(fu!=fv)add(u,v,i),add(v,u,i),f[fu]=fv;	
	}
	dfs(1,0,0);
	init();
	while(q--){
		int u=read(),v=read();
		print(qry(u,v-1)),putchar(' ');
	}puts("");
}

void clear(){
	cnt=0;
	memset(head,0,sizeof(head));
	for(int i=1;i<=n;++i)for(int j=0;j<=lg[n];++j)fa[i][j]=0;
}

int main(){
	lg[0]=-1;
	for(int i=1;i<=1e5;++i)lg[i]=lg[i>>1]+1;
	int tt=read();
	while(tt--)solve(),clear();
	return 0;
}
```
（注意低级错误，如 $x,y$ 写反，ST 表开到 $n-1$ 而不是 $n$，每次的 $2^j$ 级祖先数组未清空等）

---

## 作者：Endt (赞：0)

# Qpwoeirut and Vertices-题解

### 题意

给定 $n$ 个点 $m$ 条边构成的无向图，点从 $1$ 到 $n$ 编号，边从 $1$ 到 $m$ 编号。

你的任务是回答 $q$ 个询问，每个询问包含 $2$ 个整数 $l$ 和 $r$，询问的答案是为了找到满足下列要求的最小非负整数 $k$：
- 对于每一对 $l≤a≤b≤r$ 的整数 $(a,b)$，点 $a$ 和点 $b$ 可以只通过前 $k$ 条边相互访问。

### 实现

如果把边的编号看作边权，那么题目就转化为了几个点要互相到达，最小化经过的所有边权值最大值。这是一个典型的 Kruskal 重构树的题目。

需要进一步处理的是题目需要我们求出 $l\sim r$ 之间所有点在重构树上的 $\mathrm{LCA}$，由于 $\mathrm{LCA}$ 是可以结合的，我们只需要用 ST 表或者线段树预处理一下就可以了。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public

using std::min;using std::max;

int T;
int n,m,q;
int l,r;

class Edge{
Pub:int x,y;
}e[200005];
class Node{
Pub:int fa[20],ls,rs;
    int c;
    int dp;
    int boss;
}d[200005];

int Boss(int x){
    if(d[x].boss!=x)d[x].boss=Boss(d[x].boss);
    return d[x].boss;
}
void Merge(int x,int y,int c){
    x=Boss(x),y=Boss(y);
    if(x==y)return;
    else ++n;
    d[x].boss=d[y].boss=d[n].boss=n;
    d[x].fa[0]=d[y].fa[0]=n;
    d[n].ls=x,d[n].rs=y;
    d[n].c=c;
}
void Kruskal(){
    for(int i=1;i<=n;++i)
        d[i].boss=i;
    for(int i=1;i<=m;++i)
        Merge(e[i].x,e[i].y,i);
}

void dfs(int x){
    if(x==0)return;
    d[x].dp=d[d[x].fa[0]].dp+1;
    for(int i=1;i<=18;++i)
        d[x].fa[i]=d[d[x].fa[i-1]].fa[i-1];
    dfs(d[x].ls);dfs(d[x].rs);
}
int solve(int x,int y){
    if(d[x].dp<d[y].dp)std::swap(x,y);
    for(int i=18;i>=0;--i)
        if(d[d[x].fa[i]].dp>=d[y].dp)
            x=d[x].fa[i];
    if(x==y)return y;
    for(int i=18;i>=0;--i)
        if(d[x].fa[i]!=d[y].fa[i])
            x=d[x].fa[i],y=d[y].fa[i];
    return d[y].fa[0];
}

int t[400005];
int build(int x,int l,int r){
    int m=l+r>>1;
    if(l==r)t[x]=m;
    else t[x]=solve(build(x<<1,l,m),build(x<<1|1,m+1,r));
    return t[x];
}
int query(int x,int l,int r,int a,int b){
    int m=l+r>>1;
    if(a==l&&b==r)return t[x];
    else{
        if(b<=m)return query(x<<1,l,m,a,b);
        if(a>m)return query(x<<1|1,m+1,r,a,b);
        return solve(query(x<<1,l,m,a,m),query(x<<1|1,m+1,r,m+1,b));
    }
}

int main(){
    scanf("%d",&T);
    while(~--T){
        scanf("%d%d%d",&n,&m,&q);
        int N=n;
        for(int i=1;i<=m;++i)
            scanf("%d%d",&e[i].x,&e[i].y);
        Kruskal();
        dfs(n);
        build(1,1,N);
        for(int i=1;i<=q;++i){
            scanf("%d%d",&l,&r);
            printf("%d ",d[query(1,1,N,l,r)].c);
        }
        printf("\n");
        for(int i=1;i<=n;++i){
            memset(d[i].fa,0,sizeof(d[i].fa));
            d[i].boss=d[i].ls=d[i].rs=d[i].c=0;
        }
    }
    
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

蠢蠢的 $O((n+q)\log^2n)$ 做法~~太简单了~~。

先建出 Kruskal 重构树，并倍增预处理，接下来问题转化为树上多点 $\text{lca}$。

对于 $\text{lca}$，我们有结合律 $\text{lca}(\text{lca}(a,b),c)=\text{lca}(a,\text{lca}(b,c))$。

所以我们可以对点（按标号排）建线段树，树上每个节点存这段区间所有点的 $\text{lca}$。

然后就是线段树最最最普通的区间查询了。

合并时 $t_{rt}=\text{lca}(t_{lson},t_{rson})$ 带 $\log$，所以总体是双 $\log$。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define N 200010
#define C 20
int n,m,q,f[N],tot,g[N][C+1],son[N][C+1],a[N],dep[N],t[N<<2];
inline int gf(int x){ return x==f[x]?x:f[x]=gf(f[x]); }
inline int lca(int x,int y){
	int xx,yy;
	if(dep[x]<dep[y]) swap(x,y);
	Rof(i,C,0){
		xx=g[x][i];
		if(dep[xx]>=dep[y]) x=xx;
	}
	if(x==y) return x;
	Rof(i,C,0){
		xx=g[x][i];
		yy=g[y][i];
		if(xx!=yy) x=xx,y=yy;
	}
	return g[x][0];
}
inline void dfs(int x){
	For(i,1,C) g[x][i]=g[g[x][i-1]][i-1];
	dep[x]=dep[g[x][0]]+1;
	if(x>n) dfs(son[x][0]),dfs(son[x][1]);
}
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
void build(int rt,int l,int r){
	if(l==r){
		t[rt]=l;
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[rt]=lca(t[ls],t[rs]);
}
int que(int rt,int l,int r,int x,int y){
	if(x<=l && r<=y) return t[rt];
	if(y<=mid) return que(ls,l,mid,x,y);
	else if(x>mid) return que(rs,mid+1,r,x,y);
	else return lca(que(ls,l,mid,x,y),que(rs,mid+1,r,x,y));
}
void work(){
	scanf("%d%d%d",&n,&m,&q);
	iota(f+1,f+1+2*n,1);
	fill(a+1,a+1+n,0);
	tot=n;
	int x,y;
	For(i,1,m){
		scanf("%d%d",&x,&y);
		x=gf(x),y=gf(y);
		if(x!=y){
			g[x][0]=g[y][0]=f[x]=f[y]=++tot;
			son[tot][0]=x;
			son[tot][1]=y;
			a[tot]=i;
		}
	}
	g[tot][0]=0;
	dfs(tot);
	build(1,1,n);
	while(q--) scanf("%d%d",&x,&y),printf("%d ",a[que(1,1,n,x,y)]); puts("");
}
int main(){
	int T;scanf("%d",&T);
	while(T--)work();
return 0;}
```

---

## 作者：ExplodingKonjac (赞：0)

**[原题链接](https://www.luogu.com.cn/problem/CF1706E)**

## 题目分析

闲话：这场比赛 D2 通过人数显著低于 E，大概因为这题确实很套路。

题意：给定一个无向图，边权为边的标号，多次询问 $l,r$，求最小的 $k$ 使得 $[l,r]$ 中任意一对点能够通过边权小于等于 $k$ 的边到达。

看到边权限制，很自然的想法是 Kruskal 重构树。建出 Kruskal 重构树后，一个点 $u$ 子树内所有点可以通过小于等于 $val_u$ 的边到达。

由此得到一个结论：使得 $u,v$ 联通的最小的边权为重构树上 $val_{\operatorname{lca}(u,v)}$。

所以问题转化为了多次询问求 $[l,r]$ 的 LCA。这个问题的处理方式就是，取出其中 dfs 序最小和最大的点求 LCA 即可。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int T,n,m,q,nn,lc[200005],rc[200005],val[200005];
int fa[200005];
inline int findFa(int x)
	{ return x==fa[x]?x:fa[x]=findFa(fa[x]); }
inline void merge(int x,int y)
	{ fa[findFa(y)]=findFa(x); }
int tot,dep[200005],dfn[200005],rev[200005],f[200005][20];
void dfs(int u,int ffa=0)
{
	dfn[u]=++tot,rev[tot]=u;
	f[u][0]=ffa,dep[u]=dep[ffa]+1;
	for(int i=1;(1<<i)<=dep[u];i++)
		f[u][i]=f[f[u][i-1]][i-1];
	if(lc[u]) dfs(lc[u],u),dfs(rc[u],u);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=18;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y) return x;
	for(int i=18;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
int lg2[200005],mn[200005][20],mx[200005][20];
void ST()
{
	lg2[0]=-1;
	for(int i=1;i<=n;i++)
		mn[i][0]=mx[i][0]=dfn[i],lg2[i]=lg2[i>>1]+1;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
		{
			mn[j][i]=min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
			mx[j][i]=max(mx[j][i-1],mx[j+(1<<i-1)][i-1]);
		}
}
inline int query(int l,int r,bool opt)
{
	int s=lg2[r-l+1];
	if(opt) return min(mn[l][s],mn[r-(1<<s)+1][s]);
	else return max(mx[l][s],mx[r-(1<<s)+1][s]);
}
int main()
{
	qin>>T;
	while(T--)
	{
		int u,v,x,y;
		qin>>n>>m>>q,nn=n;
		vector<pair<int,int>> vec;
		for(int i=1;i<=m;i++) qin>>u>>v,vec.emplace_back(u,v);
		iota(fa+1,fa+2*n,1);
		for(int i=0;i<vec.size();i++)
		{
			int u=findFa(vec[i].first),v=findFa(vec[i].second);
			if(u==v) continue;
			val[++nn]=i+1,lc[nn]=u,rc[nn]=v,merge(nn,u),merge(nn,v);
		}
		dfs(nn),ST();
		while(q--)
		{
			qin>>x>>y;
			u=rev[query(x,y,0)];
			v=rev[query(x,y,1)];
			qout.writesp(val[lca(u,v)]);
		}
		qout<<'\n';
		for(int i=1;i<=nn;i++)
		{
			lc[i]=rc[i]=val[i]=0;
			for(int j=0;j<=18;j++) f[i][j]=0;
		}
	}
	return 0;
}
```


---

## 作者：Exber (赞：0)

这是一道 Kruskal 重构树的板子题，可惜打比赛的时候我还没学这个算法，要不然能上大分 /ll

按照边输入的顺序建出一颗 Kruskal 重构树，新建的节点都保存它们新建的时间 $tme_i$。

具体的，按照边输入的顺序不断合并边相连的两个连通块，用并查集记录下每个连通块的根节点，初始根节点就是本身。第 $i$ 次合并时，设两个连通块的根节点分别是 $rx$ 和 $ry$，那么就新建一个连向两个连通块的新点 $r'$，连接 $r'\to rx$ 和 $r'\to ry$，并令 $tme_{r'}=i$，合并两个连通块，让新连通块的根节点变为 $r'$。

合并过程如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ktqodndq.png)

不难发现，这样会新建 $n-1$ 个节点，每个节点都代表一条边。每个叶子节点代表原图中的一个点，一些叶子节点的 $\operatorname{lca}$ 就是原图中这些点联通所需要按时间添加的最后一条边。

那么问题转化成了求 $tme_{\operatorname{lca}(l,l+1,l+2,\dots, r)}$，那么用线段树维护一下即可。

时间复杂度 $O(n\log n+q\log n)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int S=200005;

int n,m,q;
int fa[S];
int ls[S],rs[S],tme[S]; // kruskal 重构树
int dep[S],up[S][25]; // 重构树上求 lca
int dlca[S<<2]; // 线段树维护 lca

inline int fnd(int x)
{
	return fa[x]==x?x:fa[x]=fnd(fa[x]);
}

void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	up[u][0]=fa;
	for(int i=1;i<=20;i++) up[u][i]=up[up[u][i-1]][i-1];
	if(ls[u]!=0) dfs(ls[u],u);
	if(rs[u]!=0) dfs(rs[u],u);
}

inline int getlca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--) if(dep[up[x][i]]>=dep[y]) x=up[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--) if(up[x][i]!=up[y][i]) x=up[x][i],y=up[y][i];
	return up[x][0];
}

void built(int u,int l,int r)
{
	if(l==r)
	{
		dlca[u]=l;
		return;
	}
	int mid=l+r>>1;
	built(u<<1,l,mid),built(u<<1|1,mid+1,r);
	dlca[u]=getlca(dlca[u<<1],dlca[u<<1|1]);
}

int que(int u,int l,int r,int L,int R)
{
	if(l>R||r<L) return 0;
	if(l>=L&&r<=R) return dlca[u];
	int mid=l+r>>1;
	int res=0;
	if(L<=mid) res=que(u<<1,l,mid,L,R);
	if(R>=mid+1) res=res==0?que(u<<1|1,mid+1,r,L,R):getlca(res,que(u<<1|1,mid+1,r,L,R));
	return res; 
}

inline void slove()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n*2-1;i++) fa[i]=i;
	for(int i=1;i<=n*2-1;i++) ls[i]=rs[i]=tme[i]=0;
	int cnt=n;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int rx=fnd(x),ry=fnd(y);
		if(rx!=ry)
		{
			int u=++cnt;
			tme[u]=i;
			ls[u]=rx;
			rs[u]=ry;
			fa[rx]=fa[ry]=u;
		}
	}
	dfs(cnt,0);
	built(1,1,n);
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d ",tme[que(1,1,n,l,r)]);
	}
	printf("\n");
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T-->0) slove();
	return 0;
}
```

---

