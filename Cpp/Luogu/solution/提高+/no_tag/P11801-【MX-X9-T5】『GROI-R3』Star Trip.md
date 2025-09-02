# 【MX-X9-T5】『GROI-R3』Star Trip

## 题目描述

对于整数序列 $p_1,\ldots,p_n$，我们称 $p_i$ 是一个**前缀最大值**当且仅当不存在 $1\le j<i$ 使得 $p_j\ge p_i$。

对于整数序列 $p_1,\ldots,p_n$，定义其**权值**为其前缀最大值个数。

小巡有一个包含 $n$ 个点和 $m$ 条无向边的连通图，点的编号为 $1 \sim n$。**保证图连通，不保证图是简单图。**

音理有 $q$ 个询问，每次给定两个点 $s,t$，请你找出从点 $s$ 出发、在点 $t$ 结束的路径 $p_1, \dots, p_k$（$p_1 = s$，$p_k = t$，且存在连接点 $p_i, p_{i + 1}$ 的边），使得序列 $p_1, \ldots, p_k$ 的权值最小。你只需要求出最小权值。

特别地，我们不要求你找到的路径是简单路径。也就是说，**可以经过重复的边或者点**。

## 说明/提示

**【样例解释 #1】**

样例的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/04v1mwxe.png)

- 对于询问 $2,7$，其中一条权值最小的路径是 $(2,1,8,3,6,7)$，权值为 $2$。
- 对于询问 $4,3$，其中一条权值最小的路径是 $(4,3)$，权值为 $1$。
- 对于询问 $5,4$，其中一条权值最小的路径是 $(5,2,6,3,4)$，权值为 $2$。
- 对于询问 $3,8$，其中一条权值最小的路径是 $(3,8)$，权值为 $2$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n,m\le$ | $q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $8$ | $8$ |  | $5$ |
| 2 | $300$ | $300$ |  | $15$ |
| 3 | $3000$ | $3000$ |  | $10$ |
| 4 | $3000$ | $2\times 10^5$ |  | $5$ |
| 5 | $2\times 10^5$ | $2\times 10^5$ | A | $20$ |
| 6 | $2\times 10^5$ | $2\times 10^5$ | B | $20$ |
| 7 | $2\times 10^5$ | $2\times 10^5$ |  | $25$ |

- 特殊性质 A：保证 $m=n-1$。
- 特殊性质 B：保证对于任意 $i\in[1,n]$ 满足 $V'=\{1,2,\ldots,i\}$ 的导出子图是连通图。

对于 $100\%$ 的数据，保证 $1\le n,m,q\leq 2\times 10^5$，$1\le u,v,s,t\le n$，保证图连通，不保证图不存在重边或自环。

## 样例 #1

### 输入

```
8 10 4
1 8
2 5
3 6
2 6
3 8
1 6
2 1
4 8
3 4
6 7
2 7
4 3
5 4
3 8
```

### 输出

```
2
1
2
2
```

## 样例 #2

### 输入

```
20 20 20
8 19
19 11
11 18
11 20
20 9
18 13
19 1
11 16
19 5
1 2
2 15
18 6
16 7
8 10
5 4
18 14
11 17
10 12
7 3
1 9
13 14
11 18
13 16
13 16
3 14
20 20
16 18
14 19
8 19
5 20
7 17
14 15
16 18
7 18
6 10
16 17
14 19
3 16
20 20
20 20
```

### 输出

```
2
2
2
2
4
1
2
3
2
3
3
3
2
3
3
2
3
3
1
1```

# 题解

## 作者：Eternatis (赞：3)

我永远喜欢 Neri 酱！

先考虑最优策略是什么：假设我们从点 $s$ 出发，首先如果有一个与 $s$ 相邻的 $p$ 满足 $p<s$，则我们显然不增加答案就可以直接访问 $p$。不妨维护一个当前可以任意访问的连通块，则上面的操作就是直接把编号不超过 $s$ 的相邻点并入连通块。

在所有这样的操作都做完后，与连通块相邻的所有点编号都大于 $s$。这时如果 $t$ 已经在连通块中，则答案就是 $1$；否则我们令答案加一，并访问当前能访问的**编号最大**的点，这是因为我们的路径可以经过重复的点和边，访问完编号最大的点后原路返回一定也能访问其他的点。

这个过程看起来很能倍增，考虑求出以每个点为起点，其对应的连通块能到达的权值最大的点。我们按照编号从小到大的顺序求解，对当前点 $x$，遍历 $x$ 的所有邻接点 $y$，如果 $y<x$，就与 $y$ 所在连通块的答案取 $\max$，否则就与 $y$ 取 $\max$。最后再合并 $x$ 与小于 $x$ 的 $y$ 对应的连通块。

现在对于一个询问，我们就可以倍增得到 $u$ 走若干步能到达的点编号的范围了，唯一的问题是：我们如何判断倍增后是否能到达 $v$？考虑求出所有 $u$ 到 $v$ 的路径中，最大点权的最小值，如果当前能访问的点权不小于这个值，则 $v$ 已经在当前连通块中。我们令一条 $(u,v)$ 边的权值为 $\max(u,v)$，则上面的问题等价于最小瓶颈路，建出 Kruskal 重构树后求 LCA 即可。

总复杂度 $O(n\log n+q\log n)$。


code :


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N    1000010
#define int  long long
#define pb   push_back
#define il   inline
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T=1,n,m,q,k;
int s[N];
char c[N];
vector<int> v[N];
int w[N],ww[N];
int to[21][N];
struct node{
	int x,y,z;
}e[N];
il bool cmp(const node &a,const node &b){
	return a.z<b.z;
}
int tot,f[N];
il int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int val[N];
vector<int> V[N];
il void link(int x,int y,int z){
	int a=fd(x),b=fd(y);
	if(a==b)return ;
	val[++tot]=z;
	f[a]=f[b]=tot;
	V[tot].pb(a),V[tot].pb(b);
}
int fa[21][N],dep[N];
il void dfs(int x){
	for(int i=1;i<=20;i++)
		fa[i][x]=fa[i-1][fa[i-1][x]];
	for(auto y:V[x]){
		fa[0][y]=x;
		dep[y]=dep[x]+1;
		dfs(y);
	}
}
il int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[fa[i][x]]>=dep[y])
			x=fa[i][x];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
		if(fa[i][x]!=fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
il void solve(){
	tot=n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		e[i].x=x,e[i].y=y,e[i].z=max(x,y);
		v[x].pb(y),v[y].pb(x);
	}
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=n*2;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		link(e[i].x,e[i].y,e[i].z);
	}
	dfs(tot);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)w[i]=i;
	for(int x=1;x<=n;x++){
		for(auto y:v[x]){
			if(y<x)w[x]=max(w[x],ww[fd(y)]);
			else w[x]=max(w[x],y);
		}
		ww[x]=w[x];
		for(auto y:v[x]){
			if(y<x){
				int a=fd(x),b=fd(y);
				if(a==b)continue;
				ww[b]=max(ww[b],ww[a]);
				f[a]=b;
			}
		}
	}
	for(int i=1;i<=n;i++)to[0][i]=w[i];
	for(int k=1;k<=20;k++)for(int i=1;i<=n;i++)to[k][i]=to[k-1][to[k-1][i]];
	while(q--){
		int x=read(),y=read();
		int aaa=val[lca(x,y)];
		if(x>=aaa){
			puts("1");
			continue;
		}
		int sum=0;
		for(int k=20;k>=0;k--)
			if(to[k][x]<aaa){
				sum+=(1<<k);
				x=to[k][x];
			}
		printf("%lld\n",sum+2);
	}
}
signed main(){
	T=1;
	while(T--)solve();
	return 0;
}




```

---

## 作者：是青白呀 (赞：2)

基本的观察是：若当前能**不增加序列权值**而走到的连通块的点集为 $S$，则下一次增加权值走到的一定是与 $S$ 相邻的点中编号最大的一个。因为走了最大的一个后，另外所有的相邻点都可以不花费代价走到了。

因此，我们维护 $S_i$ 表示当前序列中最大值为 $i$ 时，能走到的连通块内的点集。设 $nxt_i$ 表示当前序列中最大值为 $i$ 时，下一次增加权值是走到哪个点，则一次增加权值会使得可达连通块点集从 $S_i$ 变成 $S_{nxt_i}$。这样显然会形成一个树形结构。

考虑如何求出这棵树。我们对于每个点维护一个 set $C_i$，表示当前所有与 $S_i$ 相邻的点。然后从小到大遍历每个点，当遍历到 $i$ 时，先将 $C_i$ 中所有 $<i$ 的点 $j$ 取出来，并将 $C_j$ 与 $C_i$ 做启发式合并，直到 $C_i$ 中的点均大于 $i$ 时停止。此时找到 $C_i$ 中最大的那个点，他就是 $i$ 在树上的父亲。

注意到我们并没有实际求出 $S_i$，考虑对于每个询问如何求答案。对于一个询问 $s,t$，我们求出 $s\to t$ 路径上最大点权的最小值 $targ$，则当且仅当我们序列中的最大值不小于 $targ$ 时，可以走到 $t$。在树上倍增求出 $s$ 首个 $\geq targ$ 的祖先，其与 $s$ 的深度差 $+1$ 即为答案。

求路径上最大点权的最小值可以通过对原图建立树上笛卡尔树解决，最小值点即为 $s,t$ 在笛卡尔树上的 LCA。

总复杂度 $O(n\log^2 n)$，瓶颈在 $C$ 集合的启发式合并。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai qwq
using namespace std;
typedef long long ll;
const int N=2e5+5,M=2e6+5,mo=998244353,inf=(ll)1e18+7;
const double PI=acos(-1);
void read(int &a){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    a=x*w;
}
int n,m,q;
set<int>st[N];
struct bcj{
    int fa[N];
    void init(){
        rep(i,1,n)
            fa[i]=i;
    }
    int find(int x){
        if(x==fa[x])return fa[x];
        return fa[x]=find(fa[x]);
    }
    bool merge(int x,int y){
        x=find(x),y=find(y);
        if(x==y)return 0;
        fa[x]=y;
        return 1;
    }
}B;
vector<int>e[N],em[N],et[N];
int fat[N][22],dept[N],fam[N][22],depm[N];
void dfst(int x){//笛卡尔树
    dept[x]=dept[fat[x][0]]+1;
    rep(i,1,18)
        fat[x][i]=fat[fat[x][i-1]][i-1];
    for(auto j:et[x])
        dfst(j);
}
int lca(int x,int y){
    if(dept[x]<dept[y])swap(x,y);
    repp(i,18,0)
        if(dept[fat[x][i]]>=dept[y])x=fat[x][i];
    if(x==y)return x;
    repp(i,18,0)
        if(fat[x][i]!=fat[y][i])x=fat[x][i],y=fat[y][i];
    return fat[x][0];
}
void dfsm(int x){//集合树
    depm[x]=depm[fam[x][0]]+1;
    rep(i,1,18)
        fam[x][i]=fam[fam[x][i-1]][i-1];
    for(auto j:em[x])
        dfsm(j);
}
signed main(){
    read(n),read(m),read(q);
    B.init();
    rep(i,1,m){
        int x,y;
        read(x),read(y);
        e[x].push_back(y),e[y].push_back(x);
    }
    rep(i,1,n){
        for(auto j:e[i]){
            if(j>i)continue;
            int faj=B.find(j);
            if(B.merge(faj,i))et[i].push_back(faj),fat[faj][0]=i;
        }
    }
    fat[n][0]=0,dfst(n);
    B.init();
    rep(i,1,n){
        for(auto j:e[i])
            st[i].insert(j);
    }
    rep(i,1,n){
        while(!st[i].empty()&&*st[i].begin()<i){
            int p=*st[i].begin();
            st[i].erase(p),p=B.find(p);
            if(!B.merge(p,i))continue;
            if(st[p].size()>st[i].size())swap(st[p],st[i]);
            for(auto j:st[p])
                st[i].insert(j);
            st[p].clear();
        }
        if(!st[i].empty()&&*st[i].begin()==i)st[i].erase(st[i].begin());
        if(st[i].empty())break;
        int p=*st[i].rbegin();
        fam[i][0]=p,em[p].push_back(i);
    }
    fam[n][0]=0,dfsm(n);
    while(q--){
        int s,t;
        read(s),read(t);
        int targ=lca(s,t);
        if(s>=targ){
            puts("1");
            continue;
        }
        int nwp=s;
        repp(i,18,0)
            if(fam[nwp][i]<targ&&fam[nwp][i])nwp=fam[nwp][i];
        nwp=fam[nwp][0];
        printf("%lld\n",depm[s]-depm[nwp]+1);
    }
    return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
考虑记 $G_i$ 表示仅保留编号为 $1$ 到 $i$ 的点以及它们之间的边所得的子图。容易发现若 $i<j$，则 $G_i$ 是 $G_j$ 的子图。

对于一次询问，我们在 $G_s$ 中行走时显然不会改变路径的权值，而一旦走出去，就肯定会使权值增加 $1$。既然反正都要增加，那肯定是走到与 $G_s$ 中 $s$ 所在连通块相邻的点中，编号最大的那一个点啦。

也就是说，我们可以花费 $1$ 点代价扩充这张图，直到 $s$ 与 $t$ 联通。不妨记上一段所提的“编号最大点”为 $ex_s$。

再考虑扩充到何时 $s$ 与 $t$ 才联通？这再经典不过了，取 $\max(u,v)$ 为边 $(u,v)$ 的边权，记 $d$ 为 $s$ 与 $t$ 之间所有路径中，路径权值最大值最小的那个（即最小瓶颈路）的权值。那么只要扩充到最大点比 $d$ 大即可。

最小瓶颈路十分简单，Kruskal 重构树即可解决。

如果将每个点 $x$ 与 $ex_x$ 连边，即可得到一个森林，对图的一次扩充，即为向上跳一下。直接在该树上进行倍增即可找到最少扩充次数。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

vector<int> V[maxn];
int fa[maxn], sz[maxn], mx[maxn], nd[maxn];
int lc[maxn << 1], rc[maxn << 1], up[maxn << 1], val[maxn << 1], tot = 0;
int jp1[maxn << 1][25], jp2[maxn << 1][25], lg[maxn << 1], dep[maxn << 1];

int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y){
    int w = max(x, y);
    x = find(x), y = find(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    tot ++, lc[tot] = nd[x], rc[tot] = nd[y], up[nd[x]] = up[nd[y]] = tot, val[tot] = w;
    sz[x] += sz[y], fa[y] = x, mx[x] = max(mx[x], mx[y]);
    nd[x] = tot;
}
void dfs(int x, int f){
    dep[x] = dep[f] + 1;
    if(lc[x]) dfs(lc[x], x);
    if(rc[x]) dfs(rc[x], x);
}
int LCA(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for(int i = lg[d]; i >= 0; i --) if((d >> i) & 1) u = jp1[u][i];
    if(u == v) return u;
    for(int i = lg[dep[u]]; i >= 0; i --) if(jp1[u][i] != jp1[v][i]) u = jp1[u][i], v = jp1[v][i];
    return up[u];
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for(int i = 1; i <= n; i ++) fa[i] = i, nd[i] = i, sz[i] = 1;
    for(int i = 1; i <= m; i ++){
        int u, v;
        scanf("%d %d", &u, &v);
        V[u].push_back(v), V[v].push_back(u);
        mx[u] = max(mx[u], v), mx[v] = max(mx[v], u);
    }
    tot = n;
    for(int x = 1; x <= n; x ++){
        for(int i = 0; i < V[x].size(); i ++){
            int j = V[x][i];
            if(j < x) merge(j, x);
        }
        if(mx[find(x)] > x) jp2[x][0] = mx[find(x)];
    }
    for(int i = 1; i <= tot; i ++) jp1[i][0] = up[i], lg[i] = i > 1 ? lg[i >> 1] + 1 : 0;
    for(int j = 1; j <= lg[tot]; j ++) for(int i = 1; i <= tot; i ++) jp1[i][j] = jp1[jp1[i][j - 1]][j - 1];
    for(int j = 1; j <= lg[n]; j ++) for(int i = 1; i <= n; i ++) jp2[i][j] = jp2[jp2[i][j - 1]][j - 1];
    for(int i = 1; i <= n; i ++) if(find(i) == i) dfs(nd[find(i)], 0);
    while(q --){
        int u, v;
        scanf("%d %d", &u, &v);
        int l = LCA(u, v), w = val[l], ans = 1;
        if(u >= w){
            printf("1\n");
            continue;
        }
        for(int i = lg[n]; i >= 0; i --) if(jp2[u][i] && jp2[u][i] < w) u = jp2[u][i], ans += 1 << i;
        printf("%d\n", ans + 1);
    }
    return 0;
}
```

---

