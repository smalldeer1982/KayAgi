# [CERC2018] The Bridge on the River Kawaii

## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/)[ The Bridge on the River Kawaii](https://contest.felk.cvut.cz/18cerc/solved/bridge.pdf)**

在一个遥远的，叫做 Midsommer 的地方，有一条叫做 delta 的小河。河里流的是深紫色的酸，所以不可能在那里游泳。这条河周围有一些小岛，并且有桥连接它们。每座桥都有一个危险系数，表示通过这座桥有多危险。危险系数越高，通过这座桥就越危险。

一位叫做 Richard Hradecki 的侦探兼悬疑小说作家经常需要通过这些桥来追查案件。在所有可能的路径中，他更倾向于选择最安全的一条，也就是这条路径上经过桥的最大危险系数越低越好。

为了规划路线，Richard 经常让你为他找从一个岛到他要调查的岛的最安全路线。为了满足他的需求，你需要连续处理以下三种事件：

- 当地人在两座岛屿之间建了一座新桥；
- 一只酸性的并且毛茸茸的大粉熊 Lug 出现了，并摧毁了一座桥；
- Richard 要求你找两个岛屿之间的最安全路线。

## 说明/提示

$2≤N≤10^5,1≤Q≤10^5,0≤V≤10,0≤X,Y<N,X≠Y$

## 样例 #1

### 输入

```
6 15
0 1 2 1
2 1 4
2 1 5
0 2 3 2
2 1 4
2 1 5
0 3 4 3
2 1 4
2 1 5
0 4 5 4
2 1 4
2 1 5
1 4 5
2 1 4
2 1 5```

### 输出

```
-1
-1
-1
-1
3
-1
3
4
3
-1```

## 样例 #2

### 输入

```
6 6
0 2 0 4
0 3 4 3
0 0 4 1
0 2 5 4
2 3 2
2 4 2```

### 输出

```
4
4```

# 题解

## 作者：Macesuted (赞：4)

[点击此处以获得更佳阅读体验](https://www.macesuted.cn/article/lg7457/)

[题面](https://www.luogu.com.cn/problem/P7457)

# 题意

给出 $n$ 个点和 $q$ 个操作，每个操作属于下面三个中的一种：

1. 在点 $u,~v$ 之间加入一条边权为 $d$ 的无向边。
2. 删除 $u,~v$ 之间的边。
3. 询问 $u,~v$ 之间的所有路径中最小值最大为多少。

保证任意时刻没有重边，$n,~q \le 10^5,~0 \le d \le 10$。

# 分析

发现边权 $d$ 的取值范围很小，我们考虑枚举每一个可能的答案（$0 \sim 10$），然后找到答案为当前枚举数值的询问并标记。

由于题目中同时有加边和删边操作，删边时我们无法很好地维护区间最小值最大这一信息，所以考虑使用线段树按时间分治去掉删边操作。

输入时直接将每条边插入到线段树中，然后先在范围 $0 \sim 10$ 之间枚举答案 $ans$，接着遍历一遍线段树，每次只插入边权 $\le ans$ 的边，遇到含有询问的结点时判断已加入的边是否可让两点联通，如果联通则标记此询问答案为 $ans$ 并且在之后的遍历中不再考虑。判断联通使用可撤销并查集即可。

# 代码

注意可能存在加边是 $u,~v$，删边是 $v,~u$ 的情况，如果没有判断可能会拿到 94 分。输入时指定 $u,~v$ 大小关系，或是使用无序数对保留边信息均可解决这一问题。

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {

// fread

}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 200005

typedef pair<int, int> pii;

struct Edge {
    int x, y, dist;
};

vector<Edge> tree[maxn << 2];
map<pii, pii> S;
pii ask[maxn];
int answer[maxn], fa[maxn], siz[maxn];
bool vis[maxn];

void insert(int p, int l, int r, int ql, int qr, Edge edge) {
    if (ql <= l && r <= qr) return tree[p].push_back(edge);
    int mid = (l + r) >> 1;
    if (ql <= mid) insert(p << 1, l, mid, ql, qr, edge);
    if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, edge);
    return;
}

stack<pii> rec;
int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
void insert(int x, int y) {
    x = getfa(x), y = getfa(y);
    if (x == y) return rec.push((pii){-1, -1});
    if (siz[x] < siz[y]) swap(x, y);
    fa[y] = x, siz[x] += siz[y];
    return rec.push((pii){x, y});
}
void rollback(void) {
    if (rec.top().first == -1 && rec.top().second == -1) return rec.pop();
    fa[rec.top().second] = rec.top().second, siz[rec.top().first] -= siz[rec.top().second];
    return rec.pop();
}
void dfs(int p, int l, int r, int lim) {
    for (vector<Edge>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        if (i->dist <= lim) insert(i->x, i->y);
    if (l == r && vis[l] && answer[l] == -1 && getfa(ask[l].first) == getfa(ask[l].second))
        answer[l] = lim;
    int mid = (l + r) >> 1;
    if (l != r) dfs(p << 1, l, mid, lim), dfs(p << 1 | 1, mid + 1, r, lim);
    for (vector<Edge>::iterator i = tree[p].begin(); i != tree[p].end(); i++)
        if (i->dist <= lim) rollback();
    return;
}

int main() {
    int n = read<int>(), q = read<int>();
    for (register int i = 1; i <= q; i++) {
        int opt = read<int>();
        if (opt == 0) {
            int x = read<int>(), y = read<int>(), dist = read<int>();
            if (x > y) swap(x, y);
            S[(pii){x, y}] = (pii){dist, i};
        } else if (opt == 1) {
            int x = read<int>(), y = read<int>();
            if (x > y) swap(x, y);
            insert(1, 1, q, S[(pii){x, y}].second, i, (Edge){x, y, S[(pii){x, y}].first});
            S.erase((pii){x, y});
        } else
            vis[i] = true, ask[i].first = read<int>(), ask[i].second = read<int>();
    }
    for (map<pii, pii>::iterator i = S.begin(); i != S.end(); i++)
        insert(1, 1, q, i->second.second, q, (Edge){i->first.first, i->first.second, i->second.first});
    memset(answer, -1, sizeof(answer));
    for (register int i = 0; i <= 10; i++) {
        for (register int j = 0; j < n; j++) fa[j] = j, siz[j] = 1;
        dfs(1, 1, q, i);
    }
    for (register int i = 1; i <= q; i++)
        if (vis[i]) write(answer[i]), putch('\n');
    return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：3)

### 简要题意

> 有一张 $n$ 个点的无向图， $q$ 个操作：
> 
> 1. 在 $x,y$ 之间添加一条边权为 $v$ 的边。
> 2. 删除 $x,y$ 之间的边。
> 3. 询问 $x,y$ 之间的路径中最大边权的最小值。
> 
> $1\le n,q\le 10^5,1\le x,y\le n,0\le v\le 10$

### 分析

首先将所有操作离线。

我们把每条边搞出存在区间。然后按时间来做线段树分治。

我们在时间轴上建立一棵线段树。对于每条边，我们把它所在的时间段分为线段树上的若干个区间记下来。对于线段树每个节点，我们在该节点上维护一个`vector`，表示完全覆盖这个区间的边。

然后我们发现“最大边权的最小值”不是很好维护。那怎么办呢？注意到 $0\le v\le 10$ ，因此我们可以从 $0$ 到 $10$ 都做一遍查询！每次我们只插入小于等于当前枚举的“最大边权的最小值”的边，然后用并查集判断询问的两个点是否联通不就好了吗？

由于我们线段树分治遍历完一个节点后需要撤回插入的边，所以用一个栈来记录插入操作。

注意可能有类似插入 $(3,5)$ 删除 $(5,3)$ 的情况，我们每次读取一条边就钦定 $x<y$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
map<pair<int,int>,pair<int,int> > mp;
struct nade{
	int x,y,val;
};
int askx[1000005],asky[1000005],opt[1000005];
int ans[1000005];
vector<nade>v[4000005];
int n,q;
int fa[1000005],dis[2000005];
struct node{
    int x,y,ds;
};
stack<node> st;
int get(int x){
    if(x==fa[x])return x;
    else return get(fa[x]);
}
void add(int x,int y){
    x=get(x),y=get(y);
    if(x==y)return;
    if(dis[x]>dis[y])swap(x,y);
    fa[x]=y;
    st.push({x,y,dis[y]});
    dis[y]+=dis[x];
}
void pop(){
    int x=st.top().x,y=st.top().y;
    dis[y]=st.top().ds;
    fa[x]=x;
    st.pop();
}
void insert(int k,int l,int r,int x,int y,nade z){
    if(l>=x&&r<=y){
        v[k].push_back(z);
        return;
    }
    int mid=l+r>>1;
    if(mid>=x)insert(k*2,l,mid,x,y,z);
    if(mid<y)insert(k*2+1,mid+1,r,x,y,z);
}
void solve(int k,int l,int r,int x){
    int ht=st.size();
    for(int i=0;i<v[k].size();i++)
		if(v[k][i].val<=x)add(v[k][i].x,v[k][i].y);
    if(l==r){
    	if(opt[l]==2&&get(askx[l])==get(asky[l])&&ans[l]<0)ans[l]=x;
        while(st.size()>ht)pop();
        return;
    }
    int mid=l+r>>1;
    solve(k*2,l,mid,x);
    solve(k*2+1,mid+1,r,x);
    while(st.size()>ht)pop();
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++){
    	int o;scanf("%d",&o);
    	opt[i]=o;
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>y)swap(x,y);
        askx[i]=x,asky[i]=y;
        if(o==0){
        	int val;scanf("%d",&val);
        	mp[make_pair(x,y)]=make_pair(i,val);
        }else if(o==1){
            insert(1,1,q,mp[make_pair(x,y)].first,i-1,(nade){x,y,mp[make_pair(x,y)].second});
            mp.erase(make_pair(x,y));
        }
    }
    for(int i=1;i<=n;i++)fa[i]=i,dis[i]=1;
    for(map<pair<int,int>,pair<int,int> >::iterator i=mp.begin();i!=mp.end();i++)
        insert(1,1,q,(*i).second.first,q,(nade){(*i).first.first,(*i).first.second,(*i).second.second});
    memset(ans,-1,sizeof(ans));
    for(int i=0;i<=10;i++)solve(1,1,q,i);
    for(int i=1;i<=q;i++)if(opt[i]==2)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：little_sun (赞：1)

### 题目大意

有一个 $n$ 个点的图，有 $q$ 个操作，每个操作形如：

$ \texttt{0 x y v：}$ 在 $x,y$  间添加一条权值为 $v$ 的边。

$ \texttt{1 x y：}$ 删除 $x,y$ 之间的边，保证存在。

$ \texttt{2 x y：}$ 询问 $x,y$ 所有路径最大权值的最小值。

$ 1 \leq n, q \leq 2 \times 10 ^ 5, 1 \leq v \leq 10$

<!--more--> 	

### 题目分析

我们先忽略这个 $v$ ，看看我们得到了什么：加入一条边，删除一条边，询问两点是否联通。

这让我们联想到什么？没错，[动态图连通性](https://loj.ac/p/121)！

再一看，这个 $v$ 范围非常的小，于是我们考虑枚举 $v$ 的最大值，每次把权值不超过 $v$ 的边加入图中，询问两点之间是否联通。

这可以很轻松的使用线段树分治解决，时间复杂度 $ \Theta (vn \log^2 n) $ 。

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define pair std::pair<int, int>
#define mp(i, j) std::make_pair(i, j)
#define meow(cat...) fprintf(stderr, cat)
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 2e5 + 10;
const int MaxM = 5e5 + 10;

struct Modify
{
    int x, y;
} p[MaxM];

struct Operation
{
    int op, x, y, v, id;
} op[MaxM];

struct Query
{
    int x, y, t, id;
} q[MaxM], lq[MaxM], rq[MaxM];

std::vector<int> v[MaxM << 2];
int cnt, ans[MaxM], Ans[MaxM]; pair st[MaxM];
std::unordered_map<int, int> tim[MaxN];
int n, m, top, num, maxv, fa[MaxN], rk[MaxN];

int getf(int x)
{
    if (x == fa[x])
        return fa[x];
    return getf(fa[x]);
}

void del(int cur)
{
    while (top > cur)
    {
        pair pre = st[top--];
        fa[pre.first] = pre.first;
        rk[pre.first] = pre.second;
    }
}

void merge(int x, int y)
{
    x = getf(x), y = getf(y);
    if (x == y) return;
    if (rk[x] < rk[y]) std::swap(x, y);
    fa[y] = x, st[++top] = mp(y, rk[y]);
    if (rk[x] == rk[y])
        st[++top] = mp(x, ++rk[x]);
}

void modify(int id, int l, int r, int ql, int qr, int pos)
{
    if (ql <= l && r <= qr)
        return (void)v[id].push_back(pos);
    int mid = (l + r) >> 1;
    if (ql <= mid) modify(id << 1, l, mid, ql, qr, pos);
    if (qr > mid) modify(id << 1 | 1, mid + 1, r, ql, qr, pos);
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

void solve(int id, int l, int r, int st, int ed)
{
    if(st > ed) return; int cur = top;
    for(int i = 0; i < v[id].size(); i++)
        merge(p[v[id][i]].x, p[v[id][i]].y);
    if(l == r)
    {
        for(int i = st; i <= ed; i++)
            ans[q[i].id] = (getf(q[i].x) == getf(q[i].y));
        return;
    }
    int mid = (l + r) >> 1, lt = 0, rt = 0;
    for(int i = st; i <= ed; i++)
        if(q[i].t <= mid) lq[++lt] = q[i];
        else rq[++rt] = q[i];
    for(int i = 1; i <= lt; i++) q[st + i - 1] = lq[i];
    for(int i = 1; i <= rt; i++) q[st + i + lt - 1] = rq[i];
    solve(id << 1, l, mid, st, st + lt - 1);
    solve(id << 1 | 1, mid + 1, r, st + lt, ed), del(cur);
}

int main()
{
    n = read(), m = read(),  memset(Ans, -1, sizeof(Ans));
    for(int i = 1; i <= m; i++)
    {
        op[i].op = read(), op[i].x = read() + 1, op[i].y = read() + 1, op[i].id = i;
        if(op[i].op == 0) op[i].v = read(), maxv = std::max(maxv, op[i].v);
        if(op[i].x > op[i].y) std::swap(op[i].x, op[i].y); 
    }
    for(int V = 0; V <= maxv; V++)
    {
        for(int i = 1; i <= n; i++)
            tim[i].clear(); cnt = num = top = 0;
        for(int i = 1; i <= n; i++) fa[i] = i, rk[i] = 1;
        for(int i = 1; i <= m * 4; i++) v[i].clear();
        for(int i = 1; i <= m; i++)
        {
            int x = op[i].x, y = op[i].y;
            if(op[i].op == 0 && op[i].v <= V) tim[x][y] = i;
            else if (op[i].op == 1 && tim[x][y])
            {
                modify(1, 1, m, tim[x][y], i, ++cnt);
                p[cnt] = (Modify) {x, y}, tim[x][y] = 0;
            }
            else if(op[i].op == 2) q[++num] = (Query) {x, y, i, num}; 
        }
        for(int i = 1; i <= n; i++)
            for(auto x : tim[i])
                if(x.second)
                {
                    modify(1, 1, m, x.second, m, ++cnt);
                    p[cnt] = (Modify) {i, x.first}; 
                }
        solve(1, 1, m, 1, num);
        for(int i = 1; i <= num; i++)
        {
            if(ans[i] && Ans[i] == -1)
                Ans[i] = V;
            ans[i] = 0;
        }
    }
    for(int i = 1; i <= num; i++)
        printf("%d\n", Ans[i]);
    return 0;
}
```

---

## 作者：1234567s (赞：1)

动态维护最小生成树。  
发现边权较小，考虑答案，将合法边加入。     
此时问题转化为维护动态图连通性，使用 LCT 或操作序列分治+回滚并查集。    
这里使用后者，时间复杂度：$O(V\cdot n \log^2n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
namespace lzz
{
	int n,m,Q;
	struct node
	{
		int u,v,val,l,r;
	}t[N];
	int fa[N],size[N];
	struct huisu
	{
		int x,fax,sizex;
		int y,fay,sizey;
	}stk[N]; int top;
	int find(int u){return u==fa[u]?u:find(fa[u]);}
	void merge(int u,int v)
	{
		u=find(u),v=find(v);
		if(u==v)return ;
		if(size[u]<size[v])swap(u,v);
		stk[++top]={u,fa[u],size[u],v,fa[v],size[v]};
		fa[v]=u,size[u]+=size[v];
	}
	void del(int now)
	{
		while(top>now)
		{
			huisu s=stk[top]; top--;
			int x=s.x,fax=s.fax,sizex=s.sizex;
			int y=s.y,fay=s.fay,sizey=s.sizey;
			fa[x]=fax,size[x]=sizex,fa[y]=fay,size[y]=sizey;
		}
	}
	void init(){for(int i=1;i<=n;i++)fa[i]=i,size[i]=1;}
	int ans[N];
	struct Query
	{
		int u,v;
	}q[N];
	int cnt;
	struct hhh
	{
		vector<node>mq;
	}tree[N<<2];
	void modify(int p,int l,int r,node val)
	{
		if(l>val.r||r<val.l)return ;
		if(val.l<=l&&r<=val.r)//这段时间都要加入这个修改 
		{
			tree[p].mq.push_back(val);
			return ;
		}
		int mid=(l+r)>>1;
		modify(p<<1,l,mid,val),modify(p<<1|1,mid+1,r,val);
	}
	int now_val;//考虑枚举权值信息 
	void query(int p,int l,int r)
	{
		int now=top;
		for(int i=0;i<tree[p].mq.size();i++)
		{
			if(tree[p].mq[i].val>now_val)continue;
			int u=tree[p].mq[i].u,v=tree[p].mq[i].v;
			merge(u,v);
		}
		int mid=(l+r)>>1; 
		if(l==r)
		{
			if(find(q[l].u)==find(q[l].v))ans[l]=now_val;
		}else query(p<<1,l,mid),query(p<<1|1,mid+1,r);
		del(now);
	}
	map<pair<int,int> ,int>bj;
	int main()
	{
		scanf("%d%d",&n,&Q);
		for(int i=1;i<=Q;i++)
		{
			int op,u,v;
			scanf("%d%d%d",&op,&u,&v);
			u++,v++;
			if(op==0)
			{
				int val;
				scanf("%d",&val);
				t[++m]={u,v,val,cnt+1},bj[{u,v}]=bj[{v,u}]=m;
			}
			if(op==1)t[bj[{u,v}]].r=cnt+1;
			if(op==2)q[++cnt]={u,v},ans[cnt]=-1;
		}
		for(int i=1;i<=m;i++)
		{
			if(t[i].r==0)t[i].r=cnt+1; t[i].r--;//逆天边界 
			modify(1,1,cnt,t[i]);
		}init();
		for(now_val=10;now_val>=0;now_val--)query(1,1,cnt);
		for(int i=1;i<=cnt;i++)printf("%d\n",ans[i]);
		return 0;
	}
}
int main()
{
	return lzz::main();
}
```

---

## 作者：RainsAFO (赞：1)

这里给出一个 $O(n\log V \log n)$ 的离线做法（ $V$ 为值域 ），至于强制在线能做到什么复杂度还有待商量。

对给出的图进行一些简单的转化：连接所有出现过的边，并将边权设为 $Inf$。

这样问题就转化为了

- $1.$ 修改边权（其中删边视为赋 $Inf$）；

- $2.$ 最小化两点 $(x, y)$ 之间路径最大值。

先来解决第二个部分，我们二分最大路径长度 $val$，那么等价于只保留边权不大于 $val$ 的边后 $(x, y)$ 是否联通。

重新审视一下这个问题，现在有多次询问，边权可能发生变化，不妨基于值域分治。

- 将询问挂到时间轴上的对应位置；

- 假设当前答案候选区间为 $[l, r]$，我们按照时间加入权值在 $[0, r]$ 之间的边，同时利用并查集对应时间上的询问；

- 注意到每次加入 $[0, r]$ 之间的边时间复杂度难以接受，我们来观察一下哪些步骤时不必要的，可以发现权值较小的边会被加入很多次；

- 基于值域分治带来了值域上的偏序关系，这启发我们利用这一点，设 $mid = \frac{l + r}{2}$，在加入权值在 $[0, mid]$ 内的边后，直接处理 $[mid + 1, r]$；

- 由于并查集需要撤销，所以不能路径压缩。

这样，我们得到了一个 $O(n\log V \log n)$ 的优秀做法。

---

## 作者：LastKismet (赞：0)

# Sol
本题的关键性质在于边权足够小，提醒我们枚举答案。

枚举答案之后，一个显然的想法是加入所有边权不超过答案的边并判定连通性。那么并查集就可以解决这个问题。

考虑题目中的动态建边删边和上面分析的连通性问题，那么就是一个很典的东西，线段树分治即可，把每条边挂在相应存在时间上，如果边权不超过当前枚举的答案就并查集上连边。回溯前撤销连边，可撤销并查集，做完了。

# Code
```cpp
int n,q,m,c;

struct node{
    int x,y,v;
}ns[N];
int be[N];
map<pii,int> mp;
int id[N];
pii qs[N];
int ans[N];

stack<pii> stk;
struct DSU{
    int fa[N],rk[N];
    inline void init(){rep(i,1,n)fa[i]=i,rk[i]=1;}
    inline int find(int x){if(fa[x]!=x)return find(fa[x]);return x;}
    inline void merge(int a,int b){
        a=find(a),b=find(b);
        if(rk[a]>rk[b])swap(a,b);
        fa[a]=b;stk.push({a,rk[b]});
        if(rk[a]==rk[b])++rk[b];
    }
    inline bool same(int a,int b){return find(a)==find(b);}
}dsu;

struct segment{
    vec<node> dat[N<<2];
    void insert(int lq,int rq,node v,int x=1,int l=1,int r=q){
        if(lq<=l&&r<=rq)return dat[x].pub(v);
        int m=l+r>>1;
        if(lq<=m)insert(lq,rq,v,x<<1,l,m);
        if(m<rq)insert(lq,rq,v,x<<1|1,m+1,r);
    }
    void query(int V,int x=1,int l=1,int r=q){
        int cnt=0;
        for(auto i:dat[x])if(i.v<=V)dsu.merge(i.x,i.y),++cnt;
        if(l!=r){
            int m=l+r>>1;
            query(V,x<<1,l,m);
            query(V,x<<1|1,m+1,r);
        }else if(id[l]&&dsu.same(qs[id[l]].fir,qs[id[l]].sec))chmin(ans[id[l]],V);
        while(cnt--){
            auto tp=stk.top();stk.pop();
            dsu.rk[dsu.fa[tp.fir]]=tp.sec;
            dsu.fa[tp.fir]=tp.fir;
        }
    }
}seg;

inline void Main(){
    read(n,q);
    rep(i,1,q){
        int op;read(op);
        if(op==0){
            ++m;
            read(ns[m].x,ns[m].y,ns[m].v);
            if(ns[m].x>ns[m].y)swap(ns[m].x,ns[m].y);
            mp[{ns[m].x,ns[m].y}]=m;
            be[m]=i;
        }
        if(op==1){
            int x,y;read(x,y);
            if(x>y)swap(x,y);
            int e=mp[{x,y}];
            seg.insert(be[e],i-1,ns[e]);
            be[e]=0;
        }
        if(op==2){
            ++c;
            read(qs[c].fir,qs[c].sec);
            id[i]=c;
        }
    }
    rep(i,1,m)if(be[i])seg.insert(be[i],q,ns[i]);
    rep(i,1,c)ans[i]=inf;
    dsu.init();
    rep(i,0,10)seg.query(i);
    rep(i,1,c)put(ans[i]<inf?ans[i]:-1);
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

这个问题实际上就是货车运输加强版，多了一个删掉边的操作。

先考虑暴力做法，枚举一个上限值。把所有不超过这个值的边都加入然后再解决问题。

我们不用 LCT 很难维护删边。考虑转化为出现的时间，删边就相当于结尾，加入相当于起始。

这样就把所有的操作转化为了边的出现时间段。

然后使用线段树分治算法即可。

具体的，枚举上限值，然后进行线段树分治，如果查询两点合法就计入答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct Point{
	int x,y;
	bool operator <(const Point &a)const{
		return x==a.x?y<a.y:x<a.x;
	}
};
struct edge{
	int x,y,val;
};
vector <edge> e[N<<1];
map <Point,pair<int,int> > mp;
struct ques{
	int op,x,y,val;
}wt[N];
int n,m,f[N],siz[N],top,s[N],ans[N],op,tlhdl;
void insert(int x,int l,int r,int s,int t,Point k,int tag){
	if(l>=s&&r<=t){
		edge tmp=(edge){k.x,k.y,tag};
		e[x].push_back(tmp);
		return;
	}
	int mid=(l+r)>>1;
	if(s<=mid)insert(x<<1,l,mid,s,t,k,tag);
	if(t>mid)insert(x<<1|1,mid+1,r,s,t,k,tag);
}
int getf(int u){
	if(f[u]==u)return u;
	return getf(f[u]);
}
void merge(int x,int y){
	x=getf(x),y=getf(y);
	if(siz[x]<siz[y])swap(x,y);
	s[++top]=y;
	if(x!=y)siz[x]+=siz[y];
	f[y]=x;
}
void del(){
	int x=s[top];
	if(f[x]!=x)siz[f[x]]-=siz[x];
	f[x]=x;
	top--;
}
int ans1[N];
void dfs(int x,int l,int r,int val){
	int last=top;
	for(int i = 0;i < e[x].size();i++)if(e[x][i].val<=val)merge(e[x][i].x,e[x][i].y);
	if(l==r){
		if(ans1[l]<0&&getf(wt[l].x)==getf(wt[l].y)&&wt[l].op==2)
			ans1[l]=val;
	}
	else{
		int mid=(l+r)>>1;
		dfs(x<<1,l,mid,val);
		dfs(x<<1|1,mid+1,r,val);
	}
	while(last<top)del();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> wt[i].op >> wt[i].x >> wt[i].y;
		if(wt[i].x>wt[i].y)swap(wt[i].x,wt[i].y);
		Point tmp=(Point){wt[i].x,wt[i].y};
		if(wt[i].op==0){
			cin >> wt[i].val;
			mp[tmp]=make_pair(i,wt[i].val);
		}
		else if(wt[i].op==1)insert(1,1,m,mp[tmp].first,i-1,tmp,mp[tmp].second),mp[tmp].first=-1;
	}
	memset(ans1,-1,sizeof(ans1));
	for(int i = 1;i <= m;i++){
		Point tmp=(Point){wt[i].x,wt[i].y};
		if(mp[tmp].first!=-1&&wt[i].op==0)insert(1,1,m,mp[tmp].first,m,tmp,mp[tmp].second);
	}
	for(int i = 1;i <= n;i++)siz[i]=1,f[i]=i;
	for(int j = 0;j <= 10;j++)dfs(1,1,m,j);
	for(int i = 1;i <= m;i++)
		if(wt[i].op==2)
			cout << ans1[i] << "\n";
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

注意到 $V \le 10$，考虑扫描线将边插入，由于操作序列中有删边操作，考虑用线段树分治加回滚并查集。具体是在线段树区间上打上每条边的永久化标记，最后离线 dfs 在叶子处回答询问即可。
```cpp
#include <bits/stdc++.h>
#define ls (i<<1)
#define rs (i<<1|1)
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
unordered_map<int,int>t[100005];
int n,m;
int ans[100005];
int vis[100005];
struct edge{
	int opt,x,y,w;
}q[2000005];
struct Stack{
	int u,v;
}stk[200005];
int top;
struct dsu{
	int fa[100005],sz[100005];
	inline void init(){
		for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	}
	inline int find(int x){
		while(fa[x]!=x)x=fa[x];
		return x;
	}
	inline void Union(int x,int y){
		int rt_x=find(x),rt_y=find(y);
		if(rt_x==rt_y)return;
		if(sz[rt_x]<sz[rt_y])swap(rt_x,rt_y);
		stk[++top]={rt_x,rt_y};
		fa[rt_y]=rt_x;
		sz[rt_x]+=sz[rt_y];
	}
	inline void back(int now){
		fa[stk[now].v]=stk[now].v;
		sz[stk[now].u]-=sz[stk[now].v];
	}
}d;
struct tree{
	int l,r;
	vector<pair<int,int> >ed;
}tree[2000005];
void build(int i,int l,int r){
	tree[i].l=l,tree[i].r=r;
	tree[i].ed.clear();
	if(l==r)return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}
void add(int i,int l,int r,int u,int v){
	if(tree[i].l>r||tree[i].r<l)return;
	if(tree[i].l>=l&&tree[i].r<=r){
		tree[i].ed.push_back({u,v});
		return;
	}
	add(ls,l,r,u,v),add(rs,l,r,u,v);
}
void ask(int i,int val){
	int nowtop=top;
	for(pair<int,int> j:tree[i].ed){
		d.Union(j.first,j.second);
	}
	if(tree[i].l==tree[i].r){
		if(vis[tree[i].l]&&ans[tree[i].l]==-1){
			int u=q[tree[i].l].x,v=q[tree[i].l].y;
			if(d.find(u)==d.find(v))ans[tree[i].l]=val;
		}
	}else{
		ask(ls,val),ask(rs,val);
	}
	while(top!=nowtop)d.back(top--);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)ans[i]=-1;
	for(int i=1;i<=m;i++){
		q[i].opt=read();
		if(q[i].opt==0){
			q[i].x=read(),q[i].y=read(),q[i].w=read();
		} 
		if(q[i].opt==1||q[i].opt==2){
			q[i].x=read(),q[i].y=read();
			if(q[i].opt==2)vis[i]=1;
		}
	}
	for(int V=0;V<=10;V++){
		d.init();
		build(1,1,m);
		for(int i=1;i<=m;i++){
			if(q[i].opt==0&&q[i].w<=V)t[q[i].x][q[i].y]=t[q[i].y][q[i].x]=i;
			if(q[i].opt==1&&t[q[i].x][q[i].y]){
				add(1,t[q[i].x][q[i].y],i-1,q[i].x,q[i].y);
				t[q[i].x][q[i].y]=t[q[i].y][q[i].x]=0;
			}
		}
		for(int i=1;i<=m;i++){
			if(q[i].opt==0&&q[i].w<=V){
				if(t[q[i].x][q[i].y])add(1,t[q[i].x][q[i].y],m,q[i].x,q[i].y);
			}
		}
		ask(1,V);
		for(int i=1;i<=n;i++)t[i].clear();
	}
	for(int i=1;i<=m;i++){
		if(vis[i])cout<<ans[i]<<'\n';
	}
} 
```

---

