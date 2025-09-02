# [IOI 2018] werewolf 狼人

## 题目背景

本题为交互题，但在此请提交**完整程序**。

## 题目描述

在日本的茨城县内共有 $N$ 个城市和 $M$ 条道路。这些城市是根据人口数量的升序排列的，依次编号为 $0$ 到 $N - 1$。每条道路连接两个不同的城市，并且可以双向通行。由这些道路，你能从任意一个城市到另外任意一个城市。

你计划了 $Q$ 个行程，这些行程分别编号为 $0$ 至 $Q - 1$。第 $i(0 \leq i \leq Q - 1)$ 个行程是从城市 $S_i$ 到城市 $E_i$。

你是一个狼人。你有两种形态：**人形**和**狼形**。在每个行程开始的时候，你是人形。在每个行程结束的时候，你必须是狼形。在行程中，你必须要变身（从人形变成狼形）恰好一次，而且只能在某个城市内（包括可能是在 $S_i$ 或 $E_i$ 内）变身。

狼人的生活并不容易。当你是人形时，你必须避开人少的城市，而当你是狼形时，你必须避开人多的城市。对于每一次行程 $i(0 \leq i \leq Q - 1)$，都有两个阈值 $L_i$ 和 $R_i(0 \leq L_i \leq R_i \leq N - 1)$，用以表示哪些城市必须要避开。准确地说，当你是人形时，你必须避开城市 $0, 1, \ldots , L_i - 1$ ；而当你是狼形时，则必须避开城市 $R_i + 1, R_i + 2, \ldots , N - 1$。这就是说，在行程 $i$ 中，你必须在城市 $L_i, L_i + 1, \ldots , R_i$ 中的其中一个城市内变身。

你的任务是，对每一次行程，判定是否有可能在满足上述限制的前提下，由城市 $S_i$ 走到城市 $E_i$。你的路线可以有任意长度。

## 说明/提示

**限制条件**

- $2 \leq N \leq 200, 000$
- $N - 1 \leq M \leq 400, 000$
- $1 \leq Q \leq 200, 000$
- 对于每个 $0 \leq j \leq M - 1$
    - $0 \leq X_j \leq N - 1$
    - $0 \leq Y_j \leq N - 1$
    - $X_j \neq Y_j$
- 你可以通过道路由任意一个城市去另外任意一个城市。
- 每一对城市最多只由一条道路直接连起来。换言之，对于所有 $0 \leq j < k \leq M - 1$，都有 $(X_j, Y_j) \neq (X_k, Y_k)$ 和 $(Y_j, X_j) \neq (X_k, Y_k)$
- 对于每个 $0 \leq i \leq Q - 1$
    - $0 \leq L_i \leq S_i \leq N - 1$
    - $0 \leq E_i \leq R_i \leq N - 1$
    - $S_i \neq E_i$
    - $L_i \leq R_i$

**子任务**

- 1.（7 分）$N \leq 100$，$M \leq 200$，$Q \leq 100$。
- 2.（8 分）$N \leq 3, 000$，$M \leq 6, 000$，$Q \leq 3, 000$。
- 3.（34 分）$M = N - 1$ 且每个城市最多与两条路相连（所有城市是以一条直线的形式连起来）。
- 4.（51 分）没有附加限制。

## 样例 #1

### 输入

```
6 6 3
5 1
1 2
1 3
3 4
3 0
5 2
4 2 1 2
4 2 2 2
5 4 3 4
```

### 输出

```
1
0
0
```

## 样例 #2

### 输入

```
10 9 10
6 7
1 5
8 0
2 9
9 4
2 7
8 5
6 0
3 4
4 9 0 9
8 1 8 9
1 8 1 8
8 3 5 5
8 9 3 9
0 1 0 2
9 0 6 6
1 7 1 8
9 4 5 6
9 5 0 9
```

### 输出

```
1
1
1
0
1
1
0
1
0
1
```

# 题解

## 作者：y2823774827y (赞：43)

~~提高组选手承受范围内~~

从$s$出发，只能经过$L$~$N$，从$t$出发，只能经过$1$~$R$，根据这个单调性，$kruskal$生成两个树，$A$树非根节点大于父节点，$B$树非根节点小于父节点

生成树原理：比如$A$树，节点$x$限制$L$，通过倍增往上爬到的最小点子树就是$x$能活动的区域，形如最小生成树，倒序处理节点连边

以两树时间戳为坐标$(x,y)$，对于每次查询，判两树点集是否有交(矩阵数点)，用树状数组离线处理~~其实是不会主席树~~
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
    int to,next;
}dis[800010];
int num,n,m,q; int head[200010],tree[200010],ans[200010];
bool visit[200010];
inline void add(int u,int v){
    dis[++num]=(node){v,head[u]}; head[u]=num;
}
struct code{
    bool mark;
    int cnt,tot,time; int f[200010],inc[200010][30],dfn[200010],low[200010],top[200010];
    struct cody{
        int to,next;
    }edge[200010];
    int find(int x){
        return f[x]==x?x:f[x]=find(f[x]);
    }
    void add(int u,int v){
        edge[++cnt]=(cody){v,top[u]}; top[u]=cnt;
    }
    void kruskal(){
        for(int i=1;i<=n;++i)
            f[i]=i;
        if(mark)
            for(int u=n;u;--u)
                for(int j=head[u];j;j=dis[j].next){
                    int v=dis[j].to;
                    if(v>u){
                        int fx=find(u),fy=find(v);
                        if(fx==fy)
                            continue;
                        f[fy]=fx;
                        add(fx,fy);
                        if(++tot==n-1)
                            return;
                    }
                }
        else
            for(int u=1;u<=n;++u)
                for(int j=head[u];j;j=dis[j].next){
                    int v=dis[j].to;
                    if(v<u){
                        int fx=find(u),fy=find(v);
                        if(fx==fy)
                            continue;
                        f[fy]=fx;
                        add(fx,fy);
                        if(++tot==n-1)
                            return;
                    }
                }
    }
    void dfs(int u,int fa){
        dfn[u]=++time;
        inc[u][0]=fa;
        for(int i=1;i<=20;++i)
            inc[u][i]=inc[inc[u][i-1]][i-1];
        for(int i=top[u];i;i=edge[i].next){
            int v=edge[i].to;
            if(v==fa)
                continue;
            dfs(v,u);
        }
        low[u]=time;
    }
    int query(int x,int k){
        if(mark)
            for(int i=20;i>=0;i--){
                if(inc[x][i]&&inc[x][i]>=k)
                    x=inc[x][i];
            }
        else
            for(int i=20;i>=0;i--)
                if(inc[x][i]&&inc[x][i]<=k)
                    x=inc[x][i];
                
        return x;
    }
}A,B;
struct nody{
    int x,y,v,id;
}a[1000010];
bool cmp(nody g1,nody g2){
    if(g1.x==g2.x)
        return g1.id<g2.id;
    return g1.x<g2.x;
}
inline int lowbit(int x){
    return x&-x;
}
void ad(int x){
    for(;x<=n;x+=lowbit(x))
        tree[x]++;
}
inline int query(int x){
    int sum=0;
    for(;x;x-=lowbit(x))
        sum+=tree[x];
    return sum;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        u++; v++;
        add(u,v); add(v,u);
    }
    A.mark=true;
    A.kruskal();
    B.kruskal();
    A.dfs(1,0);
    B.dfs(n,0);  
    num=0;
    for(int i=1;i<=n;++i)
        a[++num]=(nody){A.dfn[i],B.dfn[i],0,0};
    for(int i=1;i<=q;++i){
        int s,t,l,r;
        scanf("%d%d%d%d",&s,&t,&l,&r);
        l++; r++; s++; t++;
        s=A.query(s,l);
        t=B.query(t,r);
        int x1=A.dfn[s]-1,x2=A.low[s];
        int y1=B.dfn[t]-1,y2=B.low[t];
        a[++num]=(nody){x1,y1,1,i};
        a[++num]=(nody){x1,y2,-1,i};
        a[++num]=(nody){x2,y1,-1,i};
        a[++num]=(nody){x2,y2,1,i};
    }
    sort(a+1,a+1+num,cmp);
    for(int i=1;i<=num;++i)
        if(!a[i].id)
            ad(a[i].y);
        else
            ans[a[i].id]+=query(a[i].y)*a[i].v;
    for(int i=1;i<=q;++i)
        printf("%d\n",ans[i]!=0?1:0);
    return 0;
}/*
10 9 1
6 7
1 5
8 0
2 9
9 4
2 7
8 5
6 0
3 4
8 1 8 9

1
1*/
```

---

## 作者：Nemlit (赞：42)

感觉已经几次碰到这种类型的题目了，写篇$Blog$总结一下

### 题意：

是否存在一条$(s_i, t_i)$的路径，满足先只走编号超过$L_i$的点，再走编号不超过$R_i$的点
### $Solution$：
对于这种限定经过点数的题目，可以比较自然地想到重构树：

由于前后都有限定，我们考虑建两颗重构树

第一颗按照边权为两个端点编号的最小值构建重构树，重构树每个点的点权$x$表示不经过边权超过$x$的边能到达的所有点；

第二颗则按照边权为两个端点最大值来构建重构树，重构树上每个点点权$x$表示不经过边权$≤x$的边能到达的所有点。

构建完重构树后，对于每一个$s_i$，只需要在重构树上一直往上跳，找到一个点$x$，满足$L_i≤val_x$即可，$t_i$同理

这样我们会在两颗重构树上找到两个点，现在问题就转化成了：这两个点构成的子树中，有没有公共点（因为有公共点$x$的话就肯定存在一条合法路径为$s_i->x->t_i$）

树上两个节点的交我们不太好做，考虑我们需要的是子树的交，对应在$dfs$序中是一段区间，于是问题就进一步转化：

对于两个排列$a, b$，每次询问排列$a$在$[l_1, r_1]$区间内，排列$b$在$[l_2, r_2]$区间内有无公共元素

~~其他题解到这一步怎么就是一句： 离线树状数组/在线主席树一下 就没了啊~~

由于两个数列都是排列，我们可以考律把排列$a$映射到排列$b$中去：

记$gg[i]$表示$i$这个元素在排列$a$中出现的位置，于是我们可以得到一个$gg[b[i]]$的一个新的排列，这个排列的意义为：$b_i$在$a$中的出现位置

所以我们可以考律对$gg[b[i]]$建一棵主席树（离线树状数组也行），每一个询问只需要查询在$[l_2, r_2]$这些版本内，$[l_1, r_1]$有无元素即可

## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define drep(i, s, t) for(re int i = t; i >= s; -- i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define _ 400005
int n, m, fa[_], q, fr[_], to[_], head[_], cnt, gg[_], size[_ * 15], ls[_ * 15], rs[_ * 15], gk, rt[_];
struct Edge { int v, next; }e[_ << 1];
struct edge { int u, v, w; }E[_];
il void add(int u, int v) {	e[++ cnt] = (Edge){v, head[u]}, head[u] = cnt; }
il bool cmp(edge a, edge b) { return a.w < b.w; }
il int find(int x) {
	while(x != fa[x]) x = fa[x] = fa[fa[x]];
	return x;
}
struct Tree {
	int L[_], R[_], pax, dfn[_], val[_], f[21][_];
	il void dfs(int u) {
		if(u <= n) L[u] = ++ pax, dfn[pax] = u, val[u] = u;
		else L[u] = pax + 1;
		rep(i, 1, 20) f[i][u] = f[i - 1][f[i - 1][u]];
		Next(i, u) f[0][e[i].v] = u, dfs(e[i].v);
		R[u] = pax;
	}
	il int find_pre(int x, int y) {
		drep(i, 0, 20) if(val[f[i][x]] >= y && f[i][x]) x = f[i][x];
		return x;
	}
	il int find_nxt(int x, int y) {
		drep(i, 0, 20) if(val[f[i][x]] <= y && f[i][x]) x = f[i][x];
		return x;
	}
}t1, t2;//重构树中用倍增找到我们需要的最高点
il void solve(Tree&t, int opt) {
	rep(i, 1, n * 2) fa[i] = i;
	int tot = n;
	rep(i, 1, m) {
		if(opt == 1) E[i] = (edge){fr[i], to[i], -min(fr[i], to[i])};
		if(opt == 2) E[i] = (edge){fr[i], to[i], max(fr[i], to[i])};
	}
	sort(E + 1, E + m + 1, cmp);
	rep(i, 1, m) {
		int u = E[i].u, v = E[i].v, a = find(u), b = find(v);
		if(a != b) fa[a] = fa[b] = ++ tot, t.val[tot] = abs(E[i].w), add(tot, a), add(tot, b);
	}
	t.dfs(tot);
}//构建重构树
il void insert(int &k, int kk, int l, int r, int ll) {
	if(!k) k = ++ gk; size[k] = size[kk] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(ll <= mid) insert(ls[k], ls[kk], l, mid, ll), rs[k] = rs[kk];
	else insert(rs[k], rs[kk], mid + 1, r, ll), ls[k] = ls[kk];
}
il int query(int k, int kk, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr) return size[kk] - size[k];
	int mid = (l + r) >> 1, ans = 0;
	if(ll <= mid) ans += query(ls[k], ls[kk], l, mid, ll, rr);
	if(mid < rr) ans += query(rs[k], rs[kk], mid + 1, r, ll, rr);
	return ans;
}//主席树求交
int main() {
	n = read(), m = read(), q = read();
	rep(i, 1, m) fr[i] = read() + 1, to[i] = read() + 1;
	solve(t1, 1), cnt = 0, memset(head, 0, sizeof(head)), solve(t2, 2);
	rep(i, 1, n) gg[t1.dfn[i]] = i;
	rep(i, 1, n) insert(rt[i], rt[i - 1], 1, n, gg[t2.dfn[i]]);
	while(q --) {
		int s = read() + 1, t = read() + 1, l = read() + 1, r = read() + 1, x = t1.find_pre(s, l), y = t2.find_nxt(t, r);
		printf("%d\n", query(rt[t2.L[y] - 1], rt[t2.R[y]], 1, n, t1.L[x], t1.R[x]) > 0);
	}
	return 0;
}
```
~~代码就凑合着看吧，我承认它非常丑，把它拆成及部分看的话也不是很难写~~

---

## 作者：asd_a (赞：17)

这道题三个用主席树的理由：  
1. 解题需求 ~~（废话）~~
2. 复杂度小 $O(nlogn)$
3. 强制在线  
## Step1：
我们可以先kruskal重构两棵树：  
A树非根节点大于父节点，BB树非根节点小于父节点。  
我们发现这两棵树有一个性质：  
一个子树内任意节点可以仅通过子树内的节点到达子树内的任意节点，也就是说，每个子树都是联通的且编号满足堆的性质。  
那么，我们可以现在A树中找到$S$，倍增跳到$X$,使$X>=L,Fa_X<L$  
则$S$可以只通过编号大于等于$L$的点所能到的点的集合是$X$的子树内所有点的集合,令为$Vs$。  
同理我们可以得到$T$只经过编号小于等于$R$的点所能到的点的集合$Vt$。  
求是否有解即为这两个集合是否公共点。
## Step2：  
分别处理出A树和B树的dfs序：dfa,dfb.  
$Vs$的dfa在$dfa_X$~$dfa_X+siz_X-1$  
$Vt$的dfb在$dfb_Y$~$dfa_Y+siz_Y-1$  
建立结构体，按dfa排序，以dfb为权值建立主席树  
查询$dfa_X$~$dfa_X+siz_X-1$的主席树中值在  
$dfb_Y$~$dfa_Y+siz_Y-1$之间的个数。  
若为0则输出0，否则输出1.  
解毕。  
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=8e5+5;
const int T=N<<4;
int n,m,q,fi[N],ne[N],to[N],tot;
int dfa[N],dfb[N],sia[N],sib[N];
void add(int x,int y){ne[++tot]=fi[x];to[tot]=y;fi[x]=tot;}
void ad(int x,int y){add(x,y);add(y,x);}
struct kruskal{
    int type,fk[N],nk[N],tk[N],tok;
    int fa[N],jp[N][20],rt,dfn[N],cnt,siz[N];
    void adk(int x,int y){nk[++tok]=fk[x];tk[tok]=y;fk[x]=tok;}
    int fd(int x)
    {
        if(x!=fa[x])fa[x]=fd(fa[x]);
        return fa[x];
    }
    void dfs(int x)
    {
        dfn[x]=++cnt;siz[x]=1;
        for(int i=fk[x];i;i=nk[i])
        {
            int y=tk[i];
            jp[y][0]=x;
            dfs(y);
            siz[x]+=siz[y];
        }
    }
    void build()
    {
        for(int i=1;i<=n;i++)fa[i]=i;
        if(type==1)
            for(int x=n;x;x--)
                for(int i=fi[x];i;i=ne[i])
                {
                    int y=to[i];
                    if(y>x)
                    {
                        int fx=fd(x),fy=fd(y);
                        if(fx==fy)continue;
                        fa[fy]=fx;
                        adk(fx,fy);
                    }
                }
        else
            for(int x=1;x<=n;x++)
                for(int i=fi[x];i;i=ne[i])
                {
                    int y=to[i];
                    if(y<x)
                    {
                        int fx=fd(x),fy=fd(y);
                        if(fx==fy)continue;
                        fa[fy]=fx;
                        adk(fx,fy);
                    }
                }
        cnt=0;
        rt=fd(1);
        dfs(rt);
        for(int j=1;j<=18;j++)
            for(int i=1;i<=n;i++)
                jp[i][j]=jp[jp[i][j-1]][j-1];
    }
    int lca(int x,int y)
    {
        for(int i=18;i>=0;i--)
        {
            if(type==1)
            {
                if(jp[x][i]>=y)
                    x=jp[x][i];
            }
            else
            {
                if(jp[x][i]<=y && jp[x][i])
                    x=jp[x][i];
            }
        }
        return x;
    }
}A,B;
struct DFN{
    int a,b;
}ss[N];
bool cmp(DFN x,DFN y){return x.a<y.a;}
int ls[T],rs[T],tr[T],rt[N],t_cnt;
void build(int pre,int &now,int l,int r,int x)
{
    now=++t_cnt;tr[now]=tr[pre]+1;
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(x<=mid)
    {
        rs[now]=rs[pre];
        build(ls[pre],ls[now],l,mid,x);
    }
    else
    {
        ls[now]=ls[pre];
        build(rs[pre],rs[now],mid+1,r,x);
    }
    return ;
}
int query(int now1,int now2,int l,int r,int L,int R)
{
    if(L<=l && R>=r)
        return tr[now2]-tr[now1];
    int mid=(l+r)>>1,anss=0;
    if(L<=mid)anss+=query(ls[now1],ls[now2],l,mid,L,R);
    if(R>mid)anss+=query(rs[now1],rs[now2],mid+1,r,L,R);
    return anss;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    int x,y,z,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        ad(x+1,y+1);
    }
    A.type=1;
    A.build();
    B.type=0;
    B.build();
    for(int i=1;i<=n;i++)
    {
        dfa[i]=A.dfn[i];sia[i]=A.siz[i];
        dfb[i]=B.dfn[i];sib[i]=B.siz[i];
        ss[i].a=dfa[i];
        ss[i].b=dfb[i];
    }
    sort(ss+1,ss+n+1,cmp);
    for(int i=1;i<=n;i++)
        build(rt[i-1],rt[i],1,n,ss[i].b);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d%d%d",&x,&y,&z,&v);
        x++;y++;z++;v++;
        x=A.lca(x,z);
        y=B.lca(y,v);
        if(query(rt[dfa[x]-1],rt[dfa[x]+sia[x]-1],1,n,dfb[y],dfb[y]+sib[y]-1))
            puts("1");
        else
            puts("0");
    }
    return 0;
}
```

---

## 作者：lhm_ (赞：9)

先考虑狼形，其只能走编号小于$R$的点。若将每条边赋边权为其两端点编号的较大值，然后按最小生成树的顺序构建$Kruskal$重构树。

那么从原图的一个点$x$在树上倍增，到达满足要求且深度最浅的节点，该节点子树内所有原图中的点，狼形从$x$都能到达。

同样的，人形构建重构树就是边权为两端点编号的较小值，按最大生成树的顺序。

先构建这两棵$Kruskal$重构树，对于每次询问，只需查询起点和终点分别树上倍增后子树内的节点是否有交即可。

判断有交可以通过$dfs$序。设两棵重构树分别为$A$和$B$，对于一个点在两棵树上的$dfs$序看作点对的形式$(dfn_A,dfn_B)$。因为子树中的$dfs$序都是连续的，所以就把问题转化为二维数点。可以对$dfn_A$这一维构建主席树，$dfn_B$作为权值插入，判断有交只需看矩形中是否存在点即可。

具体实现看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 1200010
#define maxm 10000010
#define inf 1000000000
#define mid ((l+r)>>1)
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,q,tree_cnt;
int p[maxn],rt[maxn],cnt[maxm],ls[maxm],rs[maxm];
struct Edge
{
    int x,y;
}ed[maxn];
bool cmp1(const Edge &a,const Edge &b)
{
    return max(a.x,a.y)<max(b.x,b.y);
}
bool cmp2(const Edge &a,const Edge &b)
{
    return min(a.x,a.y)>min(b.x,b.y);
}
struct node
{
    int tot,dfn_cnt;
    int val[maxn],fa[maxn],f[maxn][25],in[maxn],out[maxn];
    struct edge
    {
        int to,nxt;
    }e[maxn];
    int head[maxn],edge_cnt;
    void add(int from,int to)
    {
        e[++edge_cnt]=(edge){to,head[from]};
        head[from]=edge_cnt;
    }
    int find(int x)
    {
        return fa[x]==x?x:fa[x]=find(fa[x]);
    }
    void dfs(int x)
    {
        for(int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
        in[x]=++dfn_cnt;
        for(int i=head[x];i;i=e[i].nxt) dfs(e[i].to);
        out[x]=dfn_cnt;
    }
    void build(int type)
    {
    	tot=n;
        if(!type) sort(ed+1,ed+m+1,cmp1);
        else sort(ed+1,ed+m+1,cmp2);
        for(int i=1;i<=2*n-1;++i) fa[i]=i;
        for(int i=1;i<=m;++i)
        {
            int x=find(ed[i].x),y=find(ed[i].y);
            if(x==y) continue;
            if(!type) val[++tot]=max(ed[i].x,ed[i].y);
            else val[++tot]=min(ed[i].x,ed[i].y);
            add(tot,y),add(tot,x),fa[x]=fa[y]=f[x][0]=f[y][0]=tot;
            if(tot==2*n-1) break;
        }
        dfs(tot);
    }
    int get(int x,int v,int type)
    {
        for(int i=20;i>=0;--i)
        {
            if(!type&&f[x][i]&&val[f[x][i]]<=v) x=f[x][i];
            if(type&&f[x][i]&&val[f[x][i]]>=v) x=f[x][i];
        }
        return x;
    }
}A,B;
bool cmp3(const int &a,const int &b)
{
    return A.in[a]<A.in[b];
}
void modify(int l,int r,int pos,int v,int &cur)
{
    int x=++tree_cnt;
    ls[x]=ls[cur],rs[x]=rs[cur],cnt[x]=cnt[cur]+v,cur=x;
    if(l==r) return;
    if(pos<=mid) modify(l,mid,pos,v,ls[cur]);
    else modify(mid+1,r,pos,v,rs[cur]);
}
int query(int L,int R,int l,int r,int x,int y)
{
    if(L<=l&&R>=r) return cnt[y]-cnt[x];
    int v=0;
    if(L<=mid) v+=query(L,R,l,mid,ls[x],ls[y]);
    if(R>mid) v+=query(L,R,mid+1,r,rs[x],rs[y]);
    return v;
}
int main()
{
    read(n),read(m),read(q);
    for(int i=1;i<=m;++i)
    {
        read(ed[i].x),read(ed[i].y);
        ed[i].x++,ed[i].y++;
    }
    A.build(0),B.build(1);
    for(int i=1;i<=2*n-1;++i) p[i]=i;
    sort(p+1,p+2*n,cmp3);
    for(int i=1;i<=2*n-1;++i)
        rt[i]=rt[i-1],modify(1,2*n-1,B.in[p[i]],p[i]<=n,rt[i]);
    while(q--)
    {
        int x,y,l,r;
        read(x),read(y),read(l),read(r);
        x++,y++,l++,r++,x=B.get(x,l,1),y=A.get(y,r,0);
        if(query(B.in[x],B.out[x],1,2*n-1,rt[A.in[y]-1],rt[A.out[y]])) puts("1");
        else puts("0");
    }
    return 0;
}
```


---

## 作者：1saunoya (赞：9)

### **题意:**

当你是人形的时候你只能走 $[L,N-1]$ 的编号的点（即**大于等于**L的点）

当你是狼形的时候你只能走 $[1,R]$ 的编号的点（即**小于等于**R的点）

然后问题转化成人形和狼形能到的点有没有交集。



### **solution:**
发现可以建 kruskal重构树，就可以通过在树上倍增来求出来一个子树，这个子树内是你可以到的点。然后问题转化成了两个子树区间的交，这个问题可以用主席树解决。

定义 $rev1_i$ 是在树上的第 $i$ 个位置对应的数，那你定义 $r_{rev1_i}=i$，那么 $r_i$ 就是这个元素在树上出现的位置，$rev2_i$同理，即这个数在第二棵树上对应的数，然后主席树求解。

```cpp
#include <bits/stdc++.h>
using namespace std;

int read() {
  int x = 0;
  char c = getchar();
  while (c < 48) c = getchar();
  while (c > 47) x = x * 10 + (c - 48), c = getchar();
  return x;
}

int n, m, q;
const int maxn = 4e5 + 54;

struct edge {
  int u, v;
};
vector<edge> e;

int fa[maxn];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> g[maxn];

struct Tree {
  int L[maxn], R[maxn], idx;
  int rev[maxn], val[maxn], f[maxn][22];
  void dfs(int u) {
    if (u <= n) {
      rev[L[u] = ++idx] = u;
      val[u] = u;
    } else
      L[u] = idx + 1;
    for (int i = 1; i <= 20; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : g[u]) f[v][0] = u, dfs(v);
    R[u] = idx;
  }
  int getu(int s, int l) {
    for (int i = 20; ~i; i--)
      if (f[s][i] && val[f[s][i]] >= l) s = f[s][i];
    return s;
  }
  int getv(int t, int r) {
    for (int i = 20; ~i; i--)
      if (f[t][i] && val[f[t][i]] <= r) t = f[t][i];
    return t;
  }
} t1, t2;

int tot;
int rt[maxn], ls[maxn << 5], rs[maxn << 5], val[maxn << 5], cnt = 0;

void upd(int& p, int pre, int l, int r, int x) {
  ls[p = ++cnt] = ls[pre], rs[p] = rs[pre], val[p] = val[pre] + 1;
  if (l == r) return;
  int mid = l + r >> 1;
  if (x <= mid)
    upd(ls[p], ls[pre], l, mid, x);
  else
    upd(rs[p], rs[pre], mid + 1, r, x);
}

int qry(int a, int b, int ql, int qr, int l, int r) {
  if (ql <= l && r <= qr) return val[b] - val[a];
  int mid = l + r >> 1, ans = 0;
  if (ql <= mid) ans = qry(ls[a], ls[b], ql, qr, l, mid);
  if (qr > mid) ans += qry(rs[a], rs[b], ql, qr, mid + 1, r);
  return ans;
}

int main() {
  n = read(), m = read(), q = read();
  for (int i = 0; i < m; i++) {
    int u = read(), v = read();
    ++u, ++v;
    if (u > v) u ^= v ^= u ^= v;
    e.push_back({ u, v });
  }
  for (int i = 1; i <= n * 2; i++) fa[i] = i, g[i].clear();
  sort(e.begin(), e.end(), [](edge a, edge b) { return a.u > b.u; });
  tot = n;
  for (auto x : e) {
    int u = find(x.u), v = find(x.v);
    if (u == v) continue;
    fa[u] = fa[v] = ++tot;
    t1.val[tot] = x.u;
    g[tot].push_back(u), g[tot].push_back(v);
  }
  t1.dfs(tot);

  for (int i = 1; i <= n * 2; i++) fa[i] = i, g[i].clear();
  sort(e.begin(), e.end(), [](edge a, edge b) { return a.v < b.v; });
  tot = n;
  for (auto x : e) {
    int u = find(x.u), v = find(x.v);
    if (u == v) continue;
    fa[u] = fa[v] = ++tot;
    t2.val[tot] = x.v;
    g[tot].push_back(u), g[tot].push_back(v);
  }
  t2.dfs(tot);
  vector<int> r(n + 1);
  for (int i = 1; i <= n; i++) r[t1.rev[i]] = i;
  for (int i = 1; i <= n; i++) upd(rt[i], rt[i - 1], 1, n, r[t2.rev[i]]);
  for (int i = 0; i < q; i++) {
    int s = read(), t = read(), l = read(), r = read();
    ++s, ++t, ++l, ++r;
    int u = t1.getu(s, l), v = t2.getv(t, r);
    if (qry(rt[t2.L[v] - 1], rt[t2.R[v]], t1.L[u], t1.R[u], 1, n))
      puts("1");
    else
      puts("0");
  }
  return 0;
}
```

---

## 作者：ywy_c_asm (赞：8)

首先这题是$Kruskal$重构树没问题，这里提供另外一种判断两棵子树是否有交集的方法，就是先把每个点的在树$A$中的$dfs$序搞出来，然后在树$B$上进行线段树合并，查询的时候就在树$B$上的点的线段树上区间查询是否有树$A$的$dfs$序区间内的点，简单粗暴。~~虽然常数大点~~

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ls(_o) lef[_o]
#define rs(_o) rgh[_o]
using namespace std；
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	typedef struct _xb{
		int s;int t;
		friend bool operator <(const _xb &a,const _xb &b){
			return(max(a.s,a.t)<max(b.s,b.t));
		}
	}xiabb;
	xiabb bians[400001];int ints[1000001];int gn=1;int heads[1000001];
	unsigned char data[10000001];int lef[10000001],rgh[10000001],root[1000001],gseg=1;
	int united(int a,int b){
		if(!(a&&b))return(a|b);
		int tree=gseg;gseg++;
		data[tree]=data[a]|data[b];
		lef[tree]=united(lef[a],lef[b]);
		rgh[tree]=united(rgh[a],rgh[b]);return(tree);
	}
	void insert(int l,int r,int pt,int &tree){
		if(!tree)tree=gseg,gseg++;
		data[tree]=1;if(l==r)return;
		int mid=(l+r)>>1;if(pt<=mid)insert(l,mid,pt,lef[tree]);
		else insert(mid+1,r,pt,rgh[tree]);
	}
	int find(int n){
		if(ints[n]==n)return(n);
		return(ints[n]=find(ints[n]));
	}int ancea[1000001][20],anceb[1000001][20],val[1000001];
	unsigned char query(int rl,int rr,int l,int r,int tree){
		if(!data[tree])return(0);
		if(rl==l&&rr==r)return(1);
		int mid=(l+r)>>1;
		if(rl>mid)return(query(rl,rr,mid+1,r,rs(tree)));
		if(rr<=mid)return(query(rl,rr,l,mid,ls(tree)));
		return(query(rl,mid,l,mid,ls(tree))||query(mid+1,rr,mid+1,r,rs(tree)));
	}
	typedef struct _b{
		int dest;int nxt;
	}
	bian;bian memchi[1000001];
	inline void add(int s,int t){
		memchi[gn].dest=t;memchi[gn].nxt=heads[s];heads[s]=gn;gn++;
	}
	int dfn[1000001],size[1000001],deepa[1000001],deepb[1000001],gdfn=1;
	void dfsa(int pt){
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			ancea[memchi[i].dest][0]=pt;deepa[memchi[i].dest]=deepa[pt]+1;
			dfsa(memchi[i].dest);
			root[pt]=united(root[pt],root[memchi[i].dest]);
		}
	}
	void dfsb(int pt){dfn[pt]=gdfn;gdfn++;size[pt]=1;
		for(register int i=heads[pt];i;i=memchi[i].nxt){
			anceb[memchi[i].dest][0]=pt;
			deepb[memchi[i].dest]=deepb[pt]+1;
			dfsb(memchi[i].dest);
			size[pt]+=size[memchi[i].dest];
		}
	}
	int cmp(const xiabb &a,const xiabb &b){
		return(min(a.s,a.t)>min(b.s,b.t));
	}
	void ywymain(){
		int n=get(),m=get(),q=get();
		for(register int i=1;i<=m;i++)bians[i].s=get()+1,bians[i].t=get()+1;
		sort(bians+1,bians+1+m);
		for(register int i=1;i<=n;i++)ints[i]=i;
		int gnn=n+1;
		for(register int i=1;i<=m;i++){
			int aa=find(bians[i].s),ab=find(bians[i].t);
			if(aa==ab)continue;
			int me=gnn;gnn++;
			val[me]=max(bians[i].s,bians[i].t);
			ints[aa]=me;
			ints[ab]=me;
			ints[me]=me;
			add(me,aa);
			add(me,ab);
		}
		int K=gnn-1;gnn+=n;
		for(register int i=K+1;i<=K+n;i++)ints[i]=i;
		sort(bians+1,bians+1+m,cmp);
		for(register int i=1;i<=m;i++){
			int aa=find(bians[i].s+K),ab=find(bians[i].t+K);
			if(aa==ab)continue;
			int me=gnn;gnn++;
			val[me]=min(bians[i].s,bians[i].t);
			ints[aa]=me;
			ints[ab]=me;
			ints[me]=me;
			add(me,aa);
			add(me,ab);
		}
		dfsb(find(K+1));gdfn--;
		for(register int i=1;i<=n;i++)insert(1,gdfn,dfn[K+i],root[i]);
		dfsa(find(1));
		for(register int i=1;i<=19;i++){
			for(register int j=1;j<=K;j++){
				if(deepa[j]<(1<<i))continue;
				ancea[j][i]=ancea[ancea[j][i-1]][i-1];
			}for(register int j=K+1;j<gnn;j++){
				if(deepb[j]<(1<<i))continue;
				anceb[j][i]=anceb[anceb[j][i-1]][i-1];
			}
		}
		while(q){
			q--;
			int s=get()+1,t=get()+1,l=get()+1,r=get()+1;
			int curb=s+K,cura=t;
			for(register int i=19;i>=0;i--){
				if(ancea[cura][i]&&val[ancea[cura][i]]<=r)cura=ancea[cura][i];
				if(anceb[curb][i]&&val[anceb[curb][i]]>=l)curb=anceb[curb][i];
			}
			if(query(dfn[curb],dfn[curb]+size[curb]-1,1,gdfn,root[cura]))putchar('1');
			else putchar('0');putchar('\n');
		}
	}
}
int main(){
	ywy::ywymain();return(0);
}

```


---

## 作者：foreverlasting (赞：8)

[题面](https://www.luogu.org/problemnew/show/P4899)

重构树。

设边权为边两端点的编号（大的小的分别设一棵），以此建两棵重构树。然后处理一下$dfs$序，发现其实所求的就是被$dfs$包含的这个二维矩形里有没有点，这用主席树维护一下就可以了。

code:
```
//2018.10.3 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=2e5+10,M=4e5+10;
namespace MAIN{
    int n,m,Q;
    vector<int> ED[N];
#define pb push_back
    struct Kruskal{
        int kind;
        struct E{
            int next,to;
            E() {}
            E(res next,res to):next(next),to(to) {}
        }edge[M<<1];
        int head[N],cnt;
        inline void addedge(const res &u,const res &v){
            edge[++cnt]=E(head[u],v),head[u]=cnt;
        }
        int fa[N];
        int dfn[N],low[N],idx,F[N][21];
        void dfs(const res &x){
            dfn[x]=++idx;
            for(res i=1;i<=20;i++)F[x][i]=F[F[x][i-1]][i-1];
            for(res i=head[x];~i;i=edge[i].next)dfs(edge[i].to);
            low[x]=idx;
        }
        inline int jump(res x,res k){
            for(res i=20;~i;i--)if(F[x][i]&&((kind==1&&F[x][i]<=k)||(kind==-1&&F[x][i]>=k)))x=F[x][i];
            return x;
        }
        inline int find(res x){
            while(x!=fa[x])x=fa[x]=fa[fa[x]];
            return x;
        }
        inline void build(){
            for(res i=1;i<=n;i++)fa[i]=i,head[i]=-1;
            if(kind==1){
                for(res u=1;u<=n;u++)
                    for(res i=0,siz=ED[u].size();i<siz;i++)
                        if(ED[u][i]<u){
                            res v=find(ED[u][i]);
                            if(u==v)continue;
                            addedge(u,v),fa[v]=F[v][0]=u;
                        }
                dfs(n);
            }
            else {
                for(res u=n;u>=1;u--)
                    for(res i=0,siz=ED[u].size();i<siz;i++)
                        if(ED[u][i]>u){
                            res v=find(ED[u][i]);
                            if(u==v)continue;
                            addedge(u,v),fa[v]=F[v][0]=u;
                        }
                dfs(1);
            }
        }
    }Max,Min;
    namespace Segtree{
        int ls[N<<5],rs[N<<5],sz[N<<5],tot,rt[N];
        int update(const res &rt,const res &l,const res &r,const res &p){
            res pos=++tot;
            ls[pos]=ls[rt],rs[pos]=rs[rt],sz[pos]=sz[rt]+1;
            if(l==r)return pos;
            res mid=(l+r)>>1;
            if(p<=mid)ls[pos]=update(ls[rt],l,mid,p);
            else rs[pos]=update(rs[rt],mid+1,r,p);
            return pos;
        }
        int query(const res &rt0,const res &rt1,const res &l,const res &r,const res &L,const res &R){
            if(L<=l&&r<=R)return sz[rt0]-sz[rt1];
            res mid=(l+r)>>1,ret=0;
            if(L<=mid)ret+=query(ls[rt0],ls[rt1],l,mid,L,R);
            if(R>mid)ret+=query(rs[rt0],rs[rt1],mid+1,r,L,R);
            return ret;
        }
    }
    int val[N];
    inline void MAIN(){
        n=read(),m=read(),Q=read();
        for(res i=1;i<=m;i++){
            res u=read()+1,v=read()+1;
            ED[u].pb(v),ED[v].pb(u);
        }
        Max.kind=1,Min.kind=-1,Max.build(),Min.build();
        for(res i=1;i<=n;i++)val[Min.dfn[i]]=Max.dfn[i];
        for(res i=1;i<=n;i++)Segtree::rt[i]=Segtree::update(Segtree::rt[i-1],1,n,val[i]);
        while(Q--){
            res S=read()+1,T=read()+1,L=read()+1,R=read()+1;
            S=Min.jump(S,L),T=Max.jump(T,R);
            puts(Segtree::query(Segtree::rt[Min.low[S]],Segtree::rt[Min.dfn[S]-1],1,n,Max.dfn[T],Max.low[T])?"1":"0");
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Ebola (赞：6)

# 【IOI2018】狼人

问题转化一下，其实就是问是否存在一个点，能只经过大于等于L的点到达S，只经过小于等于R的点到达T。于是我们 ~~不知道为什么就忽然~~ 考虑kruskal重构树。

对于树1，我们设边(u,v)的权值为**min(u,v)**，然后求出最**大**生成树的kruskal重构树。设从点u出发，在树1中往上跳到最顶部的权值**大于等于**x的点为v，则v的子树中所有点就是u在原图中只经过**大于等于**x的点能到达的所有点。我们记v=jump1(u,x)

对于树2，我们设边(u,v)的权值为**max(u,v)**，然后求出最**小**生成树的kruskal重构树。设从点u出发，在树2中往上跳到最顶部的权值**小于等于**x的点为v，则v的子树中所有点就是u在原图中只经过**小于等于**x的点能到达的所有点。我们记v=jump2(u,x)

这样一来，一组询问就被我们转化为了：是否存在一个点，同时位于树1的jump1(S,L)子树和树2的jump2(T,R)子树中。如果我们将一个点在树1上的dfs序看作它在二维平面上的横坐标，在树2上的dfs序看作纵坐标，那么原问题就变成了问平面上一个矩形中是否存在点，直接扫描线+树状数组即可

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=400010;
struct E{int u,v;} e[N];
struct Event{int ty,a,b,c;};
int n,m,q,tot,bit[N];
vector<Event> g[N];
int ans[N];

inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline bool leq(int x,int y){return x<=y;}
inline bool geq(int x,int y){return x>=y;}

struct Kruskal
{
    int fa[N],val[N],ch[N][2],go[20][N];
    int in[N],out[N],dfc;
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void dfs(int u)
    {
        in[u]=++dfc;
        if(u>n) dfs(ch[u][0]);
        if(u>n) dfs(ch[u][1]);
        out[u]=dfc;
    }
    void build(int(*cmp)(int,int))
    {
        dfc=0;tot=n;
        for(int i=1;i<=n;i++) val[i]=i;
        for(int i=1;i<=n<<1;i++) fa[i]=i;
        for(int i=1;i<=m;i++)
        {
            int u=e[i].u,v=e[i].v;
            u=find(u);v=find(v);
            if(u==v) continue;
            val[++tot]=cmp(val[u],val[v]);
            fa[u]=fa[v]=go[0][u]=go[0][v]=tot;
            ch[tot][0]=u;ch[tot][1]=v;
        }
        dfs(tot);
        go[0][tot]=tot;
        for(int k=1;k<=18;k++)
            for(int i=1;i<=tot;i++)
                go[k][i]=go[k-1][go[k-1][i]];
    }
    pii jump(int u,int x,bool(*cmp)(int,int))
    {
        for(int k=18;k>=0;k--)
            if(cmp(val[go[k][u]],x)) u=go[k][u];
        return pii(in[u],out[u]);
    }
} t1,t2;

inline int lowbit(const int &x){return x&-x;}
void add(int p){for(p++;p<=n<<1;p+=lowbit(p)) bit[p]++;}
int sum(int p){int res=0;for(p++;p;p-=lowbit(p)) res+=bit[p];return res;}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&e[i].u,&e[i].v);
        if(e[i].u>e[i].v) swap(e[i].u,e[i].v);
        e[i].u++;e[i].v++;
    }
    sort(e+1,e+1+m,[](E a,E b){return a.u>b.u;});
    t1.build(min);
    sort(e+1,e+1+m,[](E a,E b){return a.v<b.v;});
    t2.build(max);
    for(int i=1;i<=n;i++)
        g[t1.in[i]].push_back({1,t2.in[i],0,0});
    for(int i=1,s,t,l,r,x1,x2,y1,y2;i<=q;i++)
    {
        scanf("%d%d%d%d",&s,&t,&l,&r);
        s++;t++;l++;r++;
        tie(x1,x2)=t1.jump(s,l,geq);
        tie(y1,y2)=t2.jump(t,r,leq);
        g[x1-1].push_back({2,y1-1,i,1});
        g[x1-1].push_back({2,y2,i,-1});
        g[x2].push_back({2,y1-1,i,-1});
        g[x2].push_back({2,y2,i,1});
    }
    for(int i=0;i<=n<<1;i++)
        for(Event ev : g[i])
        {
            if(ev.ty==1) add(ev.a);
            else ans[ev.b]+=ev.c*sum(ev.a);
        }
    for(int i=1;i<=q;i++)
        puts(ans[i]?"1":"0");
    return 0;
}
```

---

## 作者：tommymio (赞：5)

一句话题意：$n$ 个点 $m$ 条边的图，有 $Q$ 个询问，每次从 $s_i$ 出发，只能够到达 $\geq l_i$ 的点，在 $[l_i,r_i]$ 必须变身一次，之后只能够到达 $\leq r_i$ 的点，问能否到达 $t_i$。

我们发现这个问题等价于从 $s_i$ 出发能够到达的点与从 $t_i$ 出发能够到达的点是否存在交集。对于这一类对路径途径的点 $/$ 边进行限制，却只要求判断连通性 $/$ 可达性的问题，可以使用 $\mathrm{Kruskal}$ 重构树解决。

基于 $\mathrm{Kruskal}$ 重构树的连通性与原生成树相同，可以很好的处理这个问题。但是 $\mathrm{Kruskal}$ 重构树需要有边权，原图上没有，怎么办呢？我们给每条边 $(x,y)$ 赋上一个权值 $w$ 即可。

这里以 $\leq r_i$ 为例，重构过程中，把一条边转换成一个点，说明这两个点在生成树上必须经过这条边 $(u,v)$，并且经过这条边时，只有 $\max(u,v)$ 可能会对当前经过点的最大值产生影响。所以将 $(u,v)$ 的边权赋为 $\max(u,v)$，然后求最小生成树的 $\mathrm{Kruskal}$ 重构树，记这棵 $\mathrm{Kruskal}$ 重构树为 $T_1$。$\geq l_i$ 的部分同理。参照上述分析过程，将 $(u,v)$ 边权赋为 $\min(u,v)$ 再求最大生成树的 $\mathrm{Kruskal}$ 重构树，记这棵 $\mathrm{Kruskal}$ 重构树为 $T_2$。

那么，我们现在得到了两棵重构树 $T_1,T_2$，并且能够在每次询问时取出这两棵树的子树 $x,y$，问题变为判断这两棵子树 $x,y$ 是否存在交集。将这两棵树的 $\mathrm{dfs}$ 序求出来。问题再次被转化成判断两个序列是否存在交集。

记子树 $x$ 在 $T_1$ 的 $\mathrm{dfs}$ 序上对应区间 $[l_1,r_1]$，子树 $y$ 在 $T_2$ 的 $\mathrm{dfs}$ 序上对应区间 $[l_2,r_2]$，$T_1$ 的 $\mathrm{dfs}$ 序列为 $a$，$T_2$ 的 $\mathrm{dfs}$ 序列为 $b$ 。将这个问题形式化，即判断 $\exists i\in [l_1,r_1],j\in [l_2,r_2],a_i,b_j\leq n,a_i=b_j$。似乎不是很好做，不妨固定其中一个约束。记 $c_x$ 为节点编号 $x$ 在序列 $a$ 中出现的位置。则以上判定可以被写作 $\exists b_j\leq n,j\in [l_2,r_2],c_{b_j}\in [l_1,r_1]$。直接主席树维护就好了。

时间复杂度为 $O((Q+n) \log n+m\log m)$。

```cpp
#include<cstdio>
#include<algorithm>
struct edge {int x,y,w;} e[2][400005];
int n,m,t,tot[2],cnt[2],num[2];
int h[2][400005],to[2][400005],ver[2][400005];
int f[2][400005][20],g[2][400005][20],fa[400005];
int dfn[2][400005],rev[2][400005],size[2][400005],val[2][400005];
int rt[400005],sonL[16000005],sonR[16000005],sum[16000005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline bool cmp(const edge &x,const edge &y) {return x.w<y.w;} 
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline void assign(int x,int y) {sonL[x]=sonL[y]; sonR[x]=sonR[y]; sum[x]=sum[y];}
inline void add(int x,int y,int id) {to[id][++cnt[id]]=y;ver[id][cnt[id]]=h[id][x];h[id][x]=cnt[id];}
inline void dfs1(int x,const int &id,int fa) {
	dfn[id][x]=++num[id]; rev[id][num[id]]=x; size[id][x]=1; //printf("%d\n",x);
	for(register int i=1;i<=19;++i) f[id][x][i]=f[id][f[id][x][i-1]][i-1],g[id][x][i]=max(g[id][x][i-1],g[id][f[id][x][i-1]][i-1]);
	for(register int i=h[id][x],y;i;i=ver[id][i]) {if((y=to[id][i])==fa) continue; f[id][y][0]=x; g[id][y][0]=val[id][x]; dfs1(y,id,x); size[id][x]+=size[id][y];} 
}
inline int jump(int u,int lim,int id) {for(register int i=19;i>=0;--i) if(f[id][u][i]&&g[id][u][i]<=lim) u=f[id][u][i]; return u;}
inline void prework(int id) {
	std::sort(e[id]+1,e[id]+1+m,cmp); tot[id]=n; for(register int i=1;i<=2*n-1;++i) fa[i]=i;
	for(register int i=1,fx,fy;i<=m;++i) if((fx=find(e[id][i].x))!=(fy=find(e[id][i].y))) {fa[fx]=fa[fy]=++tot[id]; val[id][tot[id]]=e[id][i].w; add(tot[id],fx,id); add(tot[id],fy,id);}
	for(register int i=n+1;i<=tot[id];++i) if(fa[i]==i) dfs1(i,id,-1);
}
inline void change(int &p,int lst,int l,int r,int x) {assign(p=++t,lst); ++sum[p]; if(l==r) return; int mid=l+r>>1; x<=mid? change(sonL[p],sonL[lst],l,mid,x):change(sonR[p],sonR[lst],mid+1,r,x);}
inline int ask(int x,int y,int l,int r,int L,int R) {if(L<=l&&r<=R) return sum[y]-sum[x]; int mid=l+r>>1,res=0; if(L<=mid) res+=ask(sonL[x],sonL[y],l,mid,L,R); if(R>mid) res+=ask(sonR[x],sonR[y],mid+1,r,L,R); return res;}
int main() {
	n=read();m=read(); int Q=read();
	for(register int i=1;i<=m;++i) {
		e[0][i].x=e[1][i].x=read()+1;
		e[0][i].y=e[1][i].y=read()+1;
		e[0][i].w=max(e[0][i].x,e[0][i].y);
		e[1][i].w=-min(e[0][i].x,e[0][i].y);
	}
	prework(0); prework(1);
	for(register int i=1,x;i<=tot[1];++i) {if((x=rev[1][i])<=n) change(rt[i],rt[i-1],1,tot[0],dfn[0][x]); else rt[i]=rt[i-1];}
	while(Q--) {
		int S=read()+1,E=read()+1,L=read()+1,R=read()+1;
		int u=jump(S,-L,1),v=jump(E,R,0);
		int l1=dfn[0][v],r1=dfn[0][v]+size[0][v]-1,l2=dfn[1][u],r2=dfn[1][u]+size[1][u]-1;
		int res=ask(rt[l2-1],rt[r2],1,tot[0],l1,r1);
		printf("%d\n",res>0); 
	}
	return 0; 
} 
```

---

## 作者：Illusory_dimes (赞：3)

#### AC第四道黑题祭
感觉这道题很值得思考上一两天，就来写篇题解吧

## 1.题意
给一张$N$个点$M$条边的无向图，有$q$个询问，每次给出$S$，$E$，$L$，$R$，问能否从$S$走到$E$，且分三个阶段（**必须按顺序来**）：

1.只在$L$~$N$上的点上走；

2.只在$L$~$R$上的点上走；

3.只在$1$~$R$上的点上走。

## 2.想法
设从$S$出发，只经过编号$L$~$N$能够到达的所有点集为$A$；

从$E$出发，只经过编号$1$~$R$能够到达的所有点集为$B$。

那么问题就转化为判定$A$与$B$的交集是否为空。

## 3.题解
考虑建两棵$kruskal$重构树。

第一棵按照边的两个端点的较小值为边权构造一棵最大重构树；

第二棵则按边的两个端点的较大值为边权构造一棵最小重构树。

那么搞出两棵树的$DFS$序，那么$A$，$B$集合就转换为了两个区间。

如果把第一棵树上的$DFS$序看做横坐标，第二棵树上的$DFS$序看做纵坐标，那么对于一组询问，问题就变成了询问一个矩形区域内部点的数量。

然后树状数组离线处理一下就行了（~~和这位[大佬](https://www.luogu.com.cn/user/88804)一样，啥时候主席树会了再说在线解法吧~~）

附上我这丑陋的代码（目前居然是最优解$1st$~~，鬼晓得为什么~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10,M=8e5+10,Q=1e6+10;
int n,m,q,x,y,s,e,l,r,tal;
int fst[N],nxt[M],to[M],tot;
int aray[N],ans[N];
struct ljzz
{
	int x,y,val,id;
	bool operator < (const ljzz& b) const
	{return x<b.x||(x==b.x&&id<b.id);}
}a[Q];
inline ll read()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void add(int u,int v)
{
	nxt[++tot]=fst[u];
	to[tot]=v;fst[u]=tot;
}
struct mdzz
{
	bool mark;
	int fa[N],k;
	int dfn[N],low[N],tim,cir[N][24];
	int fst1[N],nxt1[N],to1[N],cnt;
	inline void add1(int u,int v)
	{
		nxt1[++cnt]=fst1[u];
		to1[cnt]=v;fst1[u]=cnt;
	}
	int find(int x)
	{
		if(fa[x]==x)return fa[x];
		return fa[x]=find(fa[x]);
	}
	void kruskal()
	{
		for(int i=1;i<=n;++i)fa[i]=i;
		if(mark)
		{
			for(int u=n;u>=1;--u)
			for(int i=fst[u];i;i=nxt[i])
			{
				int v=to[i];
				if(u<v)
				{
					int uu=find(u),vv=find(v);
					if(uu==vv)continue;
					++k;fa[vv]=uu,add1(uu,vv);
					if(k==n-1)return;
				}
			}
		}
		else
		{
			for(int u=1;u<=n;++u)
			for(int i=fst[u];i;i=nxt[i])
			{
				int v=to[i];
				if(u>v)
				{
					int uu=find(u),vv=find(v);
					if(uu==vv)continue;
					++k;fa[vv]=uu,add1(uu,vv);
					if(k==n-1)return;
				}
			}
		}
	}
	void dfs(int u,int fth)
	{
		dfn[u]=++tim;
		cir[u][0]=fth;
		for(int i=1;i<21;++i)
		cir[u][i]=cir[cir[u][i-1]][i-1];
		for(int i=fst1[u];i;i=nxt1[i])
		{
			int v=to1[i];
			if(v==fth)continue;
			dfs(v,u);
		}
		low[u]=tim;
	}
	inline int query(int u,int val)
	{
		if(mark)
		{
			for(int i=20;~i;--i)
			if(cir[u][i]&&cir[u][i]>=val)
			u=cir[u][i];
		}
		else
		{
			for(int i=20;~i;--i)
			if(cir[u][i]&&cir[u][i]<=val)
			u=cir[u][i];
		}
		return u;
	}
}pos,rev;
inline int lowbit(int k)
{return k&(-k);}
inline void off_add(int k)
{for(;k<=n;k+=lowbit(k))aray[k]++;}
inline int off_sum(int k)
{
	int tmp=0;
	for(;k;k-=lowbit(k))tmp+=aray[k];
	return tmp;
}
int main()
{
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;++i)
	{
		x=read(),y=read();
		x++,y++;
		add(x,y),add(y,x);
	}
	pos.mark=1,rev.mark=0;
	pos.kruskal();
	rev.kruskal();
	pos.dfs(1,0),rev.dfs(n,0);
	for(int i=1;i<=n;++i)
	a[++tal]=(ljzz){pos.dfn[i],rev.dfn[i],0,0};
	for(int i=1;i<=q;++i)
	{
		s=read(),e=read(),l=read(),r=read();
		s++,e++,l++,r++;
		s=pos.query(s,l);
		e=rev.query(e,r);
		int x1=pos.dfn[s]-1,x2=pos.low[s];
		int y1=rev.dfn[e]-1,y2=rev.low[e];
		a[++tal]=(ljzz){x1,y1,1,i};
		a[++tal]=(ljzz){x2,y2,1,i};
		a[++tal]=(ljzz){x1,y2,-1,i};
		a[++tal]=(ljzz){x2,y1,-1,i};
	}
	sort(a+1,a+1+tal);
	for(int i=1;i<=tal;++i)
	{
		if(a[i].id)
		{
			int tmp=off_sum(a[i].y)*a[i].val;
			ans[a[i].id]+=tmp;
		}
		else off_add(a[i].y);
	}
	for(int i=1;i<=q;++i)
	printf("%d\n",ans[i]?1:0);
	return 0;
}
```
实际上打开来看每个部分也不难写，但是题目本身是很具思考价值的（不然怎么是$IOI$的题呢）

只求能帮助到几个人罢。。

---

## 作者：GKxx (赞：2)

从$S$出发，只经过编号大于等于$L$的点，能够到达的所有点构成的集合记为$A$；

从$E$出发，只经过编号小于等于$R$的点，能够到达的所有点构成的集合记为$B$，

那么就是要求$A\cap B$是否为空集。

自然想到kruskal重构树，先对每条边以两个端点的编号较小值为权值生成最大生成树对应的重构树$TS$，再对每条边以端点编号较大值为权值生成最小生成树对应的重构树$TE$

那么在$TS$上倍增地往上跳，找到结点$x$，满足：以$x$为根的子树中的所有叶节点（也就对应到原图中的结点）编号都大于等于$L$，并且$x$是深度尽可能小的那个点。在$TE$上也倍增往上跳，找到$y$，满足：以$y$为根的子树中的所有叶节点编号都小于等于$R$，并且$y$是深度尽可能小的那个点。

那么$TS$中以$x$为根的子树的所有叶节点就构成了集合$A$，$TE$中以$y$为根的子树的所有叶节点就构成了集合$B$，现在要求它们的交集。考虑求出两棵树的dfs序，于是就变成了两个序列，每次给出两个区间，求交集。[带修改版：CF1093E](https://www.luogu.org/problemnew/show/CF1093E)。上数据结构维护就行了。可以离线树状数组，但是我这种懒人当然是用主席树了

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T &x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args) {
    read(x); read(args...);
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <typename T> inline bool chkmax(T &x, const T &y) { return x < y ? x = y, 1 : 0; }

const int maxn = 2e5 + 207, maxm = 4e5 + 207, inf = INT_MAX;

struct Edge {
    int x, y;
    Edge(int a, int b) : x(a), y(b) {}
    Edge() : x(0), y(0) {}
};
Edge e[maxm];
int n, m, q;

struct Tree {
    int v[maxm], head[maxm], next[maxm], value[maxm], tot;
    int dfn[maxm], st[maxm], ed[maxm], fa[30][maxm], xys;
    void add_edge(int x, int y) {
        v[++tot] = y;
        next[tot] = head[x];
        head[x] = tot;
    }
    void dfs(int x) {
        if (x <= n) {
            dfn[++xys] = x, value[x] = x;
            st[x] = xys;
        } else st[x] = xys + 1;
        for (int i = 1; i <= 20; ++i)
            fa[i][x] = fa[i - 1][fa[i - 1][x]];
        for (int i = head[x]; i; i = next[i]) {
            fa[0][v[i]] = x;
            dfs(v[i]);
        }
        ed[x] = xys;
    }
    int find_s(int x, int ll) {
        for (int i = 20; ~i; --i)
            if (value[fa[i][x]] >= ll) x = fa[i][x];
        return x;
    }
    int find_e(int x, int rr) {
        for (int i = 20; ~i; --i)
            if (value[fa[i][x]] <= rr) x = fa[i][x];
        return x;
    }
};
Tree TS, TE;

inline bool cmpmin(const Edge &a, const Edge &b) {
    return std::min(a.x, a.y) > std::min(b.x, b.y);
}
inline bool cmpmax(const Edge &a, const Edge &b) {
    return std::max(a.x, a.y) < std::max(b.x, b.y);
}

struct Ufs {
    int fa[maxm];
    void init(int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }
    int findf(int x) { return fa[x] == x ? x : fa[x] = findf(fa[x]); }
};

inline void kruskal(Tree &T, int tp) {
    if (tp == 1) std::sort(e + 1, e + m + 1, cmpmin);
    else std::sort(e + 1, e + m + 1, cmpmax);
    int node = n;
    Ufs ufs;
    ufs.init(n << 1);
    for (int i = 1; i <= m; ++i) {
        int x = e[i].x, y = e[i].y;
        int w = tp == 1 ? std::min(x, y) : std::max(x, y);
        if ((x = ufs.findf(x)) != (y = ufs.findf(y))) {
            ufs.fa[x] = ufs.fa[y] = ++node;
            T.value[node] = w;
            T.add_edge(node, x);
            T.add_edge(node, y);
        }
    }
    T.dfs(node);
}

struct Ctree_node {
    int lc, rc, s;
    Ctree_node() : lc(0), rc(0), s(0) {}
};

int p[maxn];

struct Chairman_tree {
    Ctree_node T[maxn << 5];
    int root[maxn], tot;
    void insert(int &o, int l, int r, int pos, int val) {
        T[++tot] = T[o]; T[o = tot].s += val;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (pos <= mid) insert(T[o].lc, l, mid, pos, val);
        else insert(T[o].rc, mid + 1, r, pos, val);
    }
    int query(int lt, int rt, int lb, int rb, int l, int r) {
        if (!(lt || rt) || l > rb || r < lb) return 0;
        if (l <= lb && r >= rb) return T[rt].s - T[lt].s;
        int mid = (lb + rb) >> 1;
        return query(T[lt].lc, T[rt].lc, lb, mid, l, r) + query(T[lt].rc, T[rt].rc, mid + 1, rb, l, r);
    }
};
Chairman_tree ct;

int main() {
    read(n, m, q);
    for (int i = 1; i <= m; ++i) {
        read(e[i].x, e[i].y);
        ++e[i].x; ++e[i].y;
    }
    kruskal(TS, 1);
    kruskal(TE, 2);
    TE.value[0] = inf;
    for (int i = 1; i <= n; ++i) p[TS.dfn[i]] = i;
    ct.root[0] = 0;
    for (int i = 1; i <= n; ++i) {
        ct.root[i] = ct.root[i - 1];
        ct.insert(ct.root[i], 1, n, p[TE.dfn[i]], 1);
    }
    for (int i = 1; i <= q; ++i) {
        int s, e, ll, rr;
        read(s, e, ll, rr);
        ++s; ++e; ++ll; ++rr;
        int x = TS.find_s(s, ll);
        int y = TE.find_e(e, rr);
        int res = ct.query(ct.root[TE.st[y] - 1], ct.root[TE.ed[y]], 1, n, TS.st[x], TS.ed[x]);
        puts(res ? "1" : "0");
    }
    return 0;
}
```


---

## 作者：Andy_SkyWalker (赞：2)

先是起点：[l,n];即从s出发只走[l,n]可以到达的点。
 
后变狼，则修改为：[0,r];（逆向思考）即从终点只走[0,r]可以到达的点。

**从起点可以走到的点中从终点也可以走到就有解！**

Solution：克鲁斯卡尔重构然后求dfs序区间覆盖的相同点。

1.对于s，建最大生成树；对于t，建最小生成树。

（Tips1：维护根节点与子节点大小单调性时可借助并查集）

（Tips2：“边权”理解为两节点中大的那个。）

2.倍增法DFS序

3.DFS1为x，DFS2为y，构成（x，y）

4.数点

【~~神清气爽~~】

借用之前某神犇的硬核优化
```cpp
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_1 400001
#define max_2 6000001
#define logg 21
int n,m,Q,ans;
void read(int &x) {
	int f=1;
	x=0;
	char s=getchar();
	while(s<'0'||s>'9') {
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9') {
		x=x*10+s-48;
		s=getchar();
	}
	x=x*f;
}
void output(int x) {
	if(x<0) {
		x=-x;
		putchar('-');
	}
	if(x>9) {
		output(x/10);
	}
	putchar(x%10+'0');
}
bool vis1[max_1],vis2[max_1];
struct node {
	int u,v;
	int x,y;
} a[max_1];
int cnt,cntt,tot,tott;
int s1[max_1],s2[max_1],t1[max_1],t2[max_1];
void Sky(int &a,int &b,int &c,int &d) {
	a++,b++,c++,d++;
}
int fa[max_1],dad[max_1];
int ls1[max_1],rs1[max_1],ls2[max_1],rs2[max_1];
int ls[max_2],rs[max_2];
int getfather(int x) {
	if(fa[x]==x) return x;
	return fa[x]=getfather(fa[x]);
}
int getdad(int x) {
	if(dad[x]==x) return x;
	return dad[x]=getdad(dad[x]);
}
int s,t,l,r;
bool cmp(node a,node b) {
	return a.x>b.x;
}
bool cmpp(node a,node b) {
	return a.y<b.y;
}
int Cnt;
void build(int &cn_t,int l,int r) {
	cn_t=++Cnt;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls[cn_t],l,mid);
	build(rs[cn_t],mid+1,r);
}
int ToT[max_2];
void update(int &cn_t,int pre,int l,int r,int k) {
	cn_t=++Cnt;
	ToT[cn_t]=ToT[pre]+1;
	if(l==r) return;
	ls[cn_t]=ls[pre];
	rs[cn_t]=rs[pre];
	int mid=(l+r)>>1;
	(k>mid)?update(rs[cn_t],rs[pre],mid+1,r,k):update(ls[cn_t],ls[pre],l,mid,k);
}
int query(int x,int y,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return ToT[y]-ToT[x];
	int mid=(l+r)>>1,temp=0;
	if(L<=mid) temp+=query(ls[x],ls[y],l,mid,L,R);
	if(R>mid) temp+=query(rs[x],rs[y],mid+1,r,L,R);
	return temp;
}
int q1[max_1],q2[max_1],v1[max_1],v2[max_1];
int grandf[max_1];
int f1[max_1][logg],f2[max_1][logg];
void dfs1(int x) {
	vis1[x]=1;
	s1[x]=tot;
	if(x<=n) q1[++tot]=x;
	for(int i=1; i<=17; i++) f1[x][i]=f1[f1[x][i-1]][i-1];
	if(ls1[x]) dfs1(ls1[x]);
	if(rs1[x]) dfs1(rs1[x]);
	t1[x]=tot;
}
void dfs2(int x) {
	vis2[x]=1;
	s2[x]=tott;
	if(x<=n) q2[++tott]=x;
	for(int i=1; i<=17; i++) f2[x][i]=f2[f2[x][i-1]][i-1];
	if(ls2[x]) dfs2(ls2[x]);
	if(rs2[x]) dfs2(rs2[x]);
	t2[x]=tott;
}
//DFS序 
int merge1(int aa,int bb){
	int cc=getfather(aa),dd=getfather(bb);
	fa[dd]=cc;
}
int merge2(int aa,int bb){
	int cc=getfather(aa),dd=getfather(bb);
	fa[dd]=cc;
}
int sear(int x,int dd) {
	for(int i=17; i>=0; i--) {
		if(v1[f1[x][i]]>=dd&&f1[x][i]) x=f1[x][i];
	}
	return x;
}
int tlook(int x,int dd) {
	for(int i=17; i>=0; i--) {
		if(v2[f2[x][i]]<=dd&&f2[x][i]) x=f2[x][i];
	}
	return x;
}
int main() {
//	freopen("lll.in","r",stdin);
//	freopen("lll.out","w",stdout);
	read(n);
	read(m);
	read(Q);
	int nn=n+n;
	for(int i=1; i<=m; i++) {
		read(a[i].u),read(a[i].v);
		a[i].u++,a[i].v++;
		a[i].x=min(a[i].u,a[i].v),a[i].y=max(a[i].u,a[i].v);
	}
	for(int i=1; i<nn; i++) {
		fa[i]=i,dad[i]=i;
	}
	cnt=cntt=n;
	sort(a+1,a+1+m,cmp);
	for(int i=1; i<=m; i++) {
		int fx=getfather(a[i].u),fy=getfather(a[i].v);
		if(fx!=fy) {
			v1[++cnt]=a[i].x;
			ls1[cnt]=fx,rs1[cnt]=fy;
			f1[fx][0]=cnt,f1[fy][0]=cnt;
			fa[fx]=cnt,fa[fy]=cnt;
			if(cnt==nn-1) break;
		}
	}
	for(int i=1; i<=n; i++) {
		if(vis1[i]==false) dfs1(getfather(i));
	}
	sort(a+1,a+1+m,cmpp);
	for(int i=1; i<=m; i++) {
		int fx=getdad(a[i].u),fy=getdad(a[i].v);
		if(fx!=fy) {
			v2[++cntt]=a[i].y;
			ls2[cntt]=fx,rs2[cntt]=fy;
			f2[fx][0]=cntt,f2[fy][0]=cntt;
			dad[fx]=cntt,dad[fy]=cntt;
			if(cntt==nn-1) break;
		}
	}
	for(int i=1; i<=n; i++) {
		if(vis2[i]==false) dfs2(getdad(i));
	}
	build(grandf[0],1,n);
	for(int i=1; i<=n; i++) {
		update(grandf[i],grandf[i-1],1,n,s2[q1[i]]+1);
	}
	for(int i=1;i<=Q;i++){
		read(s),read(t),read(l),read(r);
		Sky(s,t,l,r);
		s=sear(s,l),t=tlook(t,r);
		ans=query(grandf[s1[s]],grandf[t1[s]],1,n,s2[t]+1,t2[t]);
		bool p=((!ans)?0:1);
		output(p);
		printf("\n");
	}
}
```

---

## 作者：FjswYuzu (赞：1)

凭借着艰苦卓绝的毅力和 Isaunoya 的题解将这道题写了出来。

考虑对我们行走的限制。如果我们能找到一个中转点 $x$，使得存在一条路径 $s \to x \to e$，作为人形的时候能够从 $s$ 走到 $x$，作为狼形的时候能够从 $x$ 走到 $e$，这个路径就是合法的。

考虑对于人形和狼形的限制，我们首先在 $s$ 随便走，走遍人形从 $e$ 开始所有能够走到的地方，能走到的点集为 $S_1$；然后假设我们走到了 $e$，然后回退，走遍狼形 $e$ 开始所有能够走到的地方，能走到的点集为 $S_2$。发现满足存在一条合法的路径，当且仅当 $S_1∪S_2 \neq \varnothing$。快速求出这两个集合，显然只是一个克鲁斯卡尔重构树的板子，建两棵树就行了。倍增找到树上的节点之后，这个子树所有的叶节点都能够走到。将其抽象为两个序列，现在要求的就是两个序列有没有交集。

而这个问题可以用主席树维护。对第一个序列做关于第二个序列的映射，按映射数组建树，最后查询的时候即看 $[L_e,R_e]$ 区间版本内是否存在 $[L_s,R_s]$ 中间的任意一个数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
void write(int x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
struct Edge{
	int u,v,val;
	Edge(){u=v=val=0;}
	Edge(int U,int V,int VAL){u=U,v=V,val=VAL;}
	bool operator < (Edge another) const {return val<another.val;}
}ed[400005];
struct UnionFindSet{
	int fa[1000005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	void unionSet(int x,int y)
	{
		int xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return ;
		fa[xx]=yy;
	}
}ufs;
int n,m,q,maped[1000005];
int Abs(int x){return x>0?x:-x;}
struct KruskalRebuildTree{
	vector<int> G[1000005];
	int fa[1000005][21],tur[1000005],L[1000005],R[1000005],p[1000005],sjc;
	Edge sur[400005];
	void dfs(int u)
	{
		if(u<=n)	L[u]=++sjc,tur[sjc]=u,p[u]=u;
		else	L[u]=sjc+1;
		for(int i=1;i<=20;++i)	fa[u][i]=fa[fa[u][i-1]][i-1];
		for(unsigned int i=0;i<G[u].size();++i)	fa[G[u][i]][0]=u,dfs(G[u][i]);
		R[u]=sjc;
	}
	void Kruskal(int id)
	{
//		printf("%d\n",id);
		ufs.makeSet(2*n);
		for(int i=1;i<=m;++i)
		{
			if(id==1)	sur[i]=Edge(ed[i].u,ed[i].v,-min(ed[i].u,ed[i].v));
			if(id==2)	sur[i]=Edge(ed[i].u,ed[i].v,max(ed[i].u,ed[i].v));
		}
		sort(sur+1,sur+1+m);
		int now=n;
		for(int i=1;i<=m;++i)
		{
			int u=ufs.findSet(sur[i].u),v=ufs.findSet(sur[i].v),val=Abs(sur[i].val);
			if(u!=v)
			{
				ufs.fa[u]=ufs.fa[v]=++now;
				G[now].push_back(u);
				G[now].push_back(v);
				p[now]=val;
			}
		}
		dfs(now);
	}
	int greatFind(int s,int up)
	{
		for(int i=20;~i;--i)	if(p[fa[s][i]]>=up && fa[s][i])	s=fa[s][i];
		return s;
	}
	int lessFind(int s,int up)
	{
		for(int i=20;~i;--i)	if(p[fa[s][i]]<=up && fa[s][i])	s=fa[s][i];
		return s;
	}
}t1,t2;
struct ChairmanTree{
	#define Mm int mid=(l+r)>>1
	int root[22*400005],lch[22*400005],rch[22*400005],sum[22*400005],cnt;
	int build(int l,int r)
	{
		int rt=++cnt;
		if(l==r)	return rt;
		Mm;
		lch[rt]=build(l,mid);
		rch[rt]=build(mid+1,r);
		return rt;
	}
	void buildEmptyTree(int pos){root[pos]=build(1,n);}
	void modify(int &rt,int x,int l,int r,int val)
	{
		if(!rt)	rt=++cnt;
		sum[rt]=sum[x]+1;
		if(l==r)	return ;
		Mm;
		if(val<=mid)	modify(lch[rt],lch[x],l,mid,val),rch[rt]=rch[x];
		else	modify(rch[rt],rch[x],mid+1,r,val),lch[rt]=lch[x];
	}
	int query(int x,int y,int l,int r,int quel,int quer)
	{
		if(quel<=l && r<=quer)	return sum[y]-sum[x];
		Mm,ans=0;
		if(quel<=mid)	ans+=query(lch[x],lch[y],l,mid,quel,quer);
		if(mid<quer)	ans+=query(rch[x],rch[y],mid+1,r,quel,quer);
		return ans;
	}
}fuck;
int main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;++i)
	{
		int u=read()+1,v=read()+1;
		ed[i]=Edge(u,v,0);
	}
	t1.Kruskal(1);
	t2.Kruskal(2);
	for(int i=1;i<=n;++i)	maped[t1.tur[i]]=i;
	fuck.buildEmptyTree(0);
	for(int i=1;i<=n;++i)	fuck.modify(fuck.root[i],fuck.root[i-1],1,n,maped[t2.tur[i]]);
	while(q-->0)
	{
		int s=read()+1,e=read()+1,l=read()+1,r=read()+1;
		s=t1.greatFind(s,l);
		e=t2.lessFind(e,r);
		int que=fuck.query(fuck.root[t2.L[e]-1],fuck.root[t2.R[e]],1,n,t1.L[s],t1.R[s]);
		puts(que?"1":"0");
	}
	return 0;
}
```

---

## 作者：suxxsfe (赞：0)

## [my blog](https://www.cnblogs.com/suxxsfe/p/12822957.html)  

--------  


[P4899 [IOI2018] werewolf 狼人](https://www.luogu.com.cn/problem/P4899)  
[LOJ#2865.「IOI2018」狼人](https://loj.ac/problem/2865)，第一次AC交互题  

kruskal 重构树+主席树  
其实知道重构树的算法的话，难度就主要在主席树上  

![](https://pic.downk.cc/item/5eae8795c2a9a83be597c1f1.png)  

-----------------  

习惯从 $1$ 开始标号，所以以下讲解中的标号都是从 $1$ 开始的  
从 $s$ 开始走，只走点 $L,L+1,\cdots,n$，能走到的点集记为 $V_1$  
从 $e$ 开始，只走 $1,2,\cdots,R$，能走到的点集记为 $V_2$  
则，若 $V_1\cap V_2 \neq \varnothing$，就说明有解，我们可以在交集内的任意一个点变换人狼形式  

第一步，求 $V_1,V_2$  
考虑 kruskal 重构树，先去[这里](https://www.cnblogs.com/suxxsfe/p/12802162.html)看更详细的讲解 ~~不知道详细不详细~~，在这里不会重头开始讲重构树内容  
建立两个重构树  

- $A$ 为以 $\max(u,v)$ 为权值，用 **最小** 生成树重构，可以知道，$u,v$ 两点路径中，经过的点的最大编号的最小值，就是得出的重构树中 $lca(u,v)$ 的点权  
- $B$ 为以 $\min(u,v)$ 为权值，用 **最大** 生成树重构，可以知道，$u,v$ 两点路径中，经过的点的最小编号的最大值，就是得出的重构树中 $lca(u,v)$ 的点权  

所以，由于 kruskal 重构树的一般性质，也可以知道，以 $A$ 树为例，与一个点 $u$ 之间的路径，经过的点的最大编号的最小值小于等于 $x$ 的节点，就是以 从 $u$ 到根的路径中，深度最小的，权值小于等于 $x$ 的那个点 为根，的子树中的所有叶子节点  
~~好绕，可以用来练习句子成分的确定~~  
然后 $x=R$ 时，这样得到的点集，就是 $V_2$  
同理，可以用 $B$ 树，以相似的方法求出 $V_1$  

第二步，求 $V_1,V_2$ 是否交集不为空  
用主席树，其实可以离线用树状数组，但是并没有看懂是怎么做  

主席树其实可以理解为线段树的前缀和，我们把这些点（$2n-1$ 个），按照在 $A$ 树中的 dfs 序来排序，并以这些点在 $B$ 树上的 dfs 序建主席树  
然后我们设通过重构树找到的两个点（子树的根）分别是 $a,b$，那么又因为在一个子树内，dfs 序是连续的，所以每次查询 $dfn_b\cdots dfn_b+size_b-1$ 中，有没有数在 $dfn_a\cdots dfn_a+size_a-1$ 中  
其实也不难  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
#define N 400006
#define M 400006
int n,m;
struct edge{
	int u,v;
}e[M];
inline int get_max(int x,int y){return x>y?x:y;}
inline int get_min(int x,int y){return x<y?x:y;}
struct TREE{
	int up[N*2],vertex;
	int son[2][N];
	int fa[19][N],size[N],dfn[N],dfscnt;
	int val[N];
	inline int find(int k){
		return k==up[k]?k:up[k]=find(up[k]);
	}
	static inline int cmp_A(edge aa,edge aaa){return get_max(aa.u,aa.v)<get_max(aaa.u,aaa.v);}
	static inline int cmp_B(edge aa,edge aaa){return get_min(aa.u,aa.v)>get_min(aaa.u,aaa.v);}
	inline void build_A(){
		std::sort(e+1,e+1+m,cmp_A);
		vertex=n;
		for(reg int i=1;i<=2*n;i++) up[i]=i;
		for(reg int u,v,i=1,cnt=1;cnt<n;i++){
			u=find(e[i].u);v=find(e[i].v);
			if(u==v) continue;
			val[++vertex]=get_max(e[i].u,e[i].v);
			son[0][vertex]=u;son[1][vertex]=v;
			cnt++;up[u]=up[v]=vertex;
		}
	}
	inline void build_B(){
		std::sort(e+1,e+1+m,cmp_B);
		vertex=n;
		for(reg int i=1;i<=2*n;i++) up[i]=i;
		for(reg int u,v,i=1,cnt=1;cnt<n;i++){
			u=find(e[i].u);v=find(e[i].v);
			if(u==v) continue;
			val[++vertex]=get_min(e[i].u,e[i].v);
			son[0][vertex]=u;son[1][vertex]=v;
			cnt++;up[u]=up[v]=vertex;
		}
	}
	void dfs(int u,int father){
		fa[0][u]=father;size[u]=1;dfn[u]=++dfscnt;
		for(reg int i=1;i<19;i++) fa[i][u]=fa[i-1][fa[i-1][u]];
		if(!son[0][u]) return;
		dfs(son[0][u],u);dfs(son[1][u],u);
		size[u]+=size[son[0][u]]+size[son[1][u]];
	}
	inline int get_A(int u,int x){
		for(reg int i=18;~i;i--)if(val[fa[i][u]]<=x) u=fa[i][u];
		return u;
	}
	inline int get_B(int u,int x){
		for(reg int i=18;~i;i--)if(val[fa[i][u]]>=x) u=fa[i][u];
		return u;
	}
}A,B;
//主席树部分 
struct tr{
	tr *ls,*rs;
	int x;
}dizhi[10000006],*root[N];
int tot;
inline int cmp(int x,int y){return A.dfn[x]<A.dfn[y];}
void build(tr *tree,int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	tree->ls=&dizhi[tot++];tree->rs=&dizhi[tot++];
	build(tree->ls,l,mid);build(tree->rs,mid+1,r);
}
void insert(tr *last,tr *tree,int l,int r,int num,int k){
	if(l==r) return tree->x=last->x+k,void();
	int mid=(l+r)>>1;
	*tree=*last;
	if(num<=mid){
		tree->ls=&dizhi[tot++];
		insert(last->ls,tree->ls,l,mid,num,k);
	}
	else{
		tree->rs=&dizhi[tot++];
		insert(last->rs,tree->rs,mid+1,r,num,k);
	}
	tree->x=tree->ls->x+tree->rs->x;
}
int find(tr *left,tr *right,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return right->x-left->x;
	int mid=(l+r)>>1;
	if(ql<=mid){
		if(find(left->ls,right->ls,l,mid,ql,qr)) return 1;
	}
	if(qr>mid){
		if(find(left->rs,right->rs,mid+1,r,ql,qr)) return 1;
	}
	return 0;
}
int main(){
	n=read();m=read();int q=read();
	for(reg int i=1;i<=m;i++){
		e[i].u=read()+1;e[i].v=read()+1;
	}
	A.build_A();B.build_B();
	A.dfs(2*n-1,2*n-1);B.dfs(2*n-1,2*n-1);
	int tmp[n*2];
	for(reg int i=1;i<n*2;i++) tmp[i]=i;
	std::sort(tmp+1,tmp+n*2,cmp);
	for(reg int i=0;i<2*n;i++) root[i]=&dizhi[tot++];
	build(root[0],1,2*n-1);
	for(reg int i=1;i<2*n;i++) insert(root[i-1],root[i],1,2*n-1,B.dfn[tmp[i]],tmp[i]<=n);
	reg int s,t,L,R;
	while(q--){
		s=read()+1;t=read()+1;L=read()+1;R=read()+1;
		//从 s 开始，能走 L 到 n，最小值不小于 L，用 B 树
		//从 t 开始，能走 1 到 R，最大值不大于 R，用 A 树
		//找交集
		int tmpa=A.get_A(t,R),tmpb=B.get_B(s,L);
		std::puts(find(root[A.dfn[tmpa]-1],root[A.dfn[tmpa]+A.size[tmpa]-1],1,2*n-1,B.dfn[tmpb],B.dfn[tmpb]+B.size[tmpb]-1)?"1":"0");
	}
	return 0;
}
```

---

