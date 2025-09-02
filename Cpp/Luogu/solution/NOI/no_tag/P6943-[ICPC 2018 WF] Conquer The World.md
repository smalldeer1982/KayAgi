# [ICPC 2018 WF] Conquer The World

## 题目描述

哇哈哈哈哈哈！！！你的宿敌，英俊的间谍 Waco Powers，终于在你的秘密火山基地的死亡陷阱中落败（或者你是这样假设的，因为你太忙了，没能亲眼目睹）。终于，你准备好征服世界了！

没有什么能阻挡你！嗯，除了一个小小的后勤问题。你的邪恶军队宣布，如果不支付报酬，他们将不会继续在世界上那些微不足道的国家中肆意破坏。不幸的是，你的现金快用完了——火山基地有很多优点，但“价格合理”不是其中之一。你不得不从旅行预算中抽出资金来支付你那些忘恩负义的下属。现在你不确定如何才能真正将你的军队部署到位以征服世界。

你有一张世界各国的地图，以及它们之间所有可用的运输路线。每条路线连接两个国家，并且每支军队使用它都有固定的费用。路线的布局使得在任何两个国家之间恰好有一条路径。你知道每支军队的当前位置，以及为了征服每个国家需要永久驻扎在那里的军队数量。你如何才能以最低的成本将军队部署到位，以便征服世界？

## 说明/提示

时间限制：8 秒，内存限制：1024 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
1 2 5
3 1 5
2 1
5 0
1 3
```

### 输出

```
15
```

## 样例 #2

### 输入

```
6
1 2 2
1 3 5
1 4 1
2 5 5
2 6 1
0 0
1 0
2 1
2 1
0 1
0 1
```

### 输出

```
9
```

# 题解

## 作者：whiteqwq (赞：16)

[P6943 [ICPC2018 WF]Conquer The World](https://www.luogu.com.cn/problem/P6943)解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15524172.html)

## 题意

给定一个 $n$ 个点的带点边权的树（设点权为 $v$），可以任意将点的点权在树上进行移动，移动单位点权的代价为路径上的边权和，求让所有点点权非负的最小代价。

$1\leqslant n\leqslant 2.5\times 10^5,\sum v\geqslant 0,\sum[v>0]v\leqslant 10^6$

## 分析

小清新题。

下面称正点权点为源，负点权点为汇。

首先有一个明显的费用流做法，直接源点连正点权，负点权连汇点然后费用流即可。

我们可以发现一个性质，对于匹配的两条路径，它们交叉的代价一定不优于它们不交叉的代价。

于是可以考虑反悔贪心（模拟费用流），设当前子树的根为 $x$，那么：

贪心策略：每次找到深度最小的源和深度最小的汇进行匹配。

反悔策略：将源的点权改成 $2dep_x$ 减去汇的点权，将汇的点权改成 $2dep_x-$ 减去源的点权即可，容易发现这样匹配之后可以取消掉这对源汇的匹配。

使用左偏树来支持堆的合并即可，时间复杂度 $O(\sum|v|\log(\sum|v|))$。

## 代码

直接用了 pbds 来实现左偏树。

[AC 记录](https://www.luogu.com.cn/record/62047327)

```
#include<stdio.h>
#include<vector>
#include<ext/pb_ds/priority_queue.hpp>
#define inf 1000000000000
using namespace std;
const int maxn=250005;
int n,tot;
int a[maxn],b[maxn];
long long ans;
long long dep[maxn];
vector< pair<int,int> >v[maxn];
__gnu_pbds::priority_queue< long long,greater<long long> >A[maxn],B[maxn];
void dfs(int x,int last){
	for(int i=a[x]+1;i<=b[x];i++)
		A[x].push(dep[x]-inf),tot++;
	for(int i=b[x]+1;i<=a[x];i++)
		B[x].push(dep[x]);
	for(int i=0;i<v[x].size();i++){
		int y=v[x][i].first,z=v[x][i].second;
		if(y!=last)
			dep[y]=dep[x]+z,dfs(y,x),A[x].join(A[y]),B[x].join(B[y]);
	}
	while(!A[x].empty()&&!B[x].empty()&&A[x].top()+B[x].top()-2*dep[x]<0){
		long long u=A[x].top(),v=B[x].top();
		A[x].pop(),B[x].pop(),ans+=u+v-2*dep[x];
		A[x].push(2*dep[x]-v),B[x].push(2*dep[x]-u);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y,z;i<n;i++)
		scanf("%d%d%d",&x,&y,&z),v[x].push_back(make_pair(y,z)),v[y].push_back(make_pair(x,z));
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	dfs(1,0);
	printf("%lld\n",ans+1ll*tot*inf);
	return 0;
}
```

---

## 作者：Harry27182 (赞：11)

洛谷上的几篇题解都有些不知所云，所以自己写一篇，顺便加深一下对这个很久以前就见过但是现在才理解的套路。

下文中 $(u,v,w,c)$ 表示一条 $u\rightarrow v$ 流量为 $w$ 代价为 $c$ 的边。

首先移动点权需要代价这个东西可以套路地用费用流刻画，建图 $(S,u,a_u,0)(u,v,\infty,w)(u,T,b_u,0)$，其中满足 $(u,v,w)\in E$。跑最小费用最大流即可，复杂度不知道，反正过不去这道题。

考虑简化一些费用流模型，把边权的费用考虑放在 $u,v,lca(u,v)$ 三个点上面，那么把一个点从 $u$ 挪到 $v$ 的代价就是 $dep_u+dep_v-2dep_{lca(u,v)}$。这样做的好处是把边权变成了点权，所以建图也需要拆点。具体的，建图 $(S,u_1,a_u,dep_u)(u_1,fa_{u_1},\infty,0)(u_1,u_2,\infty,-2dep_u)(fa_{u_2},u_2,\infty,0)(u_2,T,b_u,dep_u)$，跑最小费用最大流。

发现这个模型仍然不好模拟费用流，主要原因在于最大流这个条件限制了流量比较烦人，考虑去掉这个条件。考虑对于每一组匹配 $(u,v)$，把它的权值减去 $\infty$，最后加回去即可，这样的话，最小费用最大流就可以转化为求最小费用循环流，也可以说是消去图中所有负圈。

这样建边之后，就可以用两个小根堆来维护，一个堆维护当前节点 $u$ 的后代指向它的所有边，另一个维护它指向它的所有后代的所有边（均包括自己）。每次只需要从两个堆顶拿出来一个元素看一下这组匹配的大小是否 $<0$ 即可。如果是就加进答案并把反悔边加入堆中。由于需要合并儿子节点，用左偏树维护。时间复杂度 $O(\sum y\log \sum y)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct edge{int v,w,nxt;}e[500005];
const int inf=1e12;
int cnt,rt1[250005],rt2[250005],h[250005],n,dep[250005],a[250005],b[250005],tot,ans,u,v,w;
void add(int u,int v,int w){e[++cnt]={v,w,h[u]};h[u]=cnt;}
struct tree{int l,r,val,dis,siz,num;}tr[6000005];
int merge(int x,int y)
{
	if(!x||!y)return x|y;
	if(tr[x].val>tr[y].val)swap(x,y);
	tr[x].r=merge(tr[x].r,y);
	if(tr[tr[x].r].dis>tr[tr[x].l].dis)swap(tr[x].l,tr[x].r);
	tr[x].dis=tr[tr[x].r].dis+1;tr[x].siz=tr[tr[x].l].siz+tr[tr[x].r].siz+1;
	return x;
}
void pop(int &x){x=merge(tr[x].l,tr[x].r);}
void push(int &k,int x,int y)
{
	tr[++tot]={0,0,x,0,1,y}; 
	k=merge(k,tot);
}
void dfs(int u,int fa)
{
	rt1[u]=u;rt2[u]=u+n;
	tr[u]={0,0,dep[u],0,1,a[u]};tr[u+n]={0,0,dep[u]-inf,0,1,b[u]};
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dep[v]=dep[u]+e[i].w;dfs(v,u);
		rt1[u]=merge(rt1[u],rt1[v]);
		rt2[u]=merge(rt2[u],rt2[v]);
	}
	while(tr[rt1[u]].siz&&tr[rt2[u]].siz)
	{
		int w1=tr[rt1[u]].val,w2=tr[rt2[u]].val;
		int now=w1+w2-2*dep[u],num1=tr[rt1[u]].num,num2=tr[rt2[u]].num;
		if(now>=0)break;
		ans+=now*min(num1,num2);
		pop(rt1[u]);pop(rt2[u]);
		if(num1>num2)push(rt1[u],w1,num1-num2);
		if(num2>num1)push(rt2[u],w2,num2-num1);
		push(rt1[u],w1-now,min(num1,num2));
		push(rt2[u],w2-now,min(num1,num2));
	}
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;tot=2*n;int sumb=0;
    for(int i=1;i<n;i++)
    {
    	cin>>u>>v>>w;
    	add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i],sumb+=b[i];
	dfs(1,0);cout<<ans+sumb*inf;
	return 0;
}

```

---

## 作者：yllcm (赞：10)

#### 

无脑做法。

考虑维护每条边的流量对应的代价凸函数，设 $f_{u,i}$ 表示 $u$ 的父亲边流量为 $i$，如果是从 $u$ 流向 $fa_u$，那么流量为正，如果是从 $fa_u$ 流向 $u$，流量为负数。

我们维护 $f$ 的差分数组 $g$，转移分为三部分：

* 合并子树。
  * 是一个 $(\min,+)$ 卷积，直接闵可夫斯基和归并差分数组即可。
* 处理当前点贡献的流量。
  * 设 $t_i=a_i-b_i$，如果 $t_i>0$，可以选择流的流量 $x\in [0,t_i]$，那么操作相当于将 $f_{u,*}$ 和 $f(x)=0,x\in[0,t_i]$，做 $(\min,+)$ 卷积，仍然使用闵可夫斯基和归并。如果 $t_i<0$，那么操作相当于将 $f_{u,*}$ 平移 $t_i$ 个单位，那么记录 $st_u$ 表示 $u$ 的平移量即可。
* 处理父亲边的代价。
  * 操作相当于加上一个函数 $f(x)=w|x|$，$w$ 为边权。那么操作即为对差分数组下标 $\leq 0$ 的部分加上 $-w$，下标 $>0$ 的部分加上 $w$。

综上，我们需要对差分数组进行如下操作：

* 归并两个差分数组。
* 区间加。

使用平衡树+启发式合并维护，时间复杂度 $\mathcal{O}(V\log^2 V)$，$V$ 为 $\sum a_i$。

注意维护差分数组的同时，还需要维护函数最左端的取值 $val_u$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
#define int long long
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 1e6 + 10;
int n, tot;
int a[N], b[N], st[N], val[N], rt[N];
vector<pii> G[N];
struct Node {
    int ls, rs, tg, val, ky, sz;
}nd[N];
mt19937 rnd(time(0));
int New(int x) {
    int cur = ++tot;
    nd[cur].ls = nd[cur].rs = nd[cur].tg = 0;
    nd[cur].sz = 1; nd[cur].val = x; nd[cur].ky = rnd();
    return cur;
}
void mark(int x, int w) {
    if(x == 0)return ;
    nd[x].val += w; nd[x].tg += w;
    return ;
}
void pushdown(int x) {
    mark(nd[x].ls, nd[x].tg);
    mark(nd[x].rs, nd[x].tg);
    nd[x].tg = 0;
    return ;
}
void pushup(int x) {
    if(x == 0)return ;
    nd[x].sz = nd[nd[x].ls].sz + nd[nd[x].rs].sz + 1;
    return ;
}
void merge(int &k, int x, int y) {
    if(x == 0 || y == 0)return k = x + y, void();
    pushdown(x); pushdown(y);
    if(nd[x].ky < nd[y].ky) {k = x; merge(nd[k].rs, nd[x].rs, y);}
    else {k = y; merge(nd[k].ls, x, nd[y].ls);}
    pushup(k);
    return ;
}
void split1(int k, int &x, int &y, int w) {
    if(k == 0)return x = y = 0, void();
    pushdown(k);
    if(nd[nd[k].ls].sz + 1 <= w) {x = k; split1(nd[k].rs, nd[x].rs, y, w - nd[nd[k].ls].sz - 1);}
    else {y = k; split1(nd[k].ls, x, nd[y].ls, w);}
    pushup(x); pushup(y);
    return ;
}
void split2(int k, int &x, int &y, int w) {
    if(k == 0)return x = y = 0, void();
    pushdown(k);
    if(nd[k].val <= w) {x = k; split2(nd[k].rs, nd[x].rs, y, w);}
    else {y = k; split2(nd[k].ls, x, nd[y].ls, w);}
    pushup(x); pushup(y);
    return ;
}
void update(int u, int w) {
    int x = 0, y = 0;
    val[u] += abs(st[u]) * w;
    split1(rt[u], x, y, -st[u]);
    mark(x, -w); mark(y, w);
    merge(rt[u], x, y);
    return ;
}
void ins(int &k, int u) {
    if(u == 0)return ;
    pushdown(u);
    ins(k, nd[u].ls); ins(k, nd[u].rs);
    int x = 0, y = 0;
    nd[u].ls = nd[u].rs = nd[u].tg = 0;
    nd[u].sz = 1;
    split2(k, x, y, nd[u].val);
    merge(x, x, u); merge(k, x, y);
    return ;
}
void print(int u) {
    if(u == 0)return ;
    print(nd[u].ls);
    printf("%d ", nd[u].val);
    print(nd[u].rs);
    return ;
}
void dfs(int u, int fa) {
    for(auto e : G[u]) {
        int v = e.FR, w = e.SE;
        if(v == fa)continue;
        dfs(v, u); update(v, w); 
        if(nd[rt[u]].sz < nd[rt[v]].sz)swap(rt[u], rt[v]);
        ins(rt[u], rt[v]); st[u] += st[v]; val[u] += val[v];
    }
    if(a[u] > b[u]) {
        for(int i = 1; i <= a[u] - b[u]; i++) {
            int x = 0, y = 0;
            split2(rt[u], x, y, 0); 
            merge(x, x, New(0)); merge(rt[u], x, y);
        }
    }
    else st[u] += a[u] - b[u];
    // printf("rt:%d %d %d\n", u, rt[u], st[u]);
    return ;
}
int ans;
void calc_ans(int u) {
    if(u == 0)return ;
    pushdown(u);
    calc_ans(nd[u].ls);
    // printf("%d ", nd[u].val);
    if(st[1] < 0)ans += nd[u].val, st[1]++;
    calc_ans(nd[u].rs);
    return ;
}
signed main() { 
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read(), w = read();
        G[u].pb(mp(v, w)); G[v].pb(mp(u, w));
    }
    for(int i = 1; i <= n; i++)a[i] = read(), b[i] = read();
    dfs(1, 0); calc_ans(rt[1]); 
    printf("%lld\n", ans + val[1]);
    return 0;
}
```


---

## 作者：zhouyixian (赞：8)

建议对模拟费用流（带悔贪心）有一定了解后再考虑此题。

如果你还没学过的话，[试试这个。](https://www.cnblogs.com/wyher/p/11134980.html)

首先不看数据范围，有一个很直观的想法，就是建超级源汇点分别向有点权、需要点权的地方连边，跑费用流。

然而没有什么费用流算法能跑完 $2.5\times 10^5$ 的数据。

所以可以想到这是一道模拟费用流的题。

定义 $dep_u$ 为根节点到 $u$ 的路径上的边权和，我们每次考虑**一个**点权。

则将 $u$ 的点权转移到 $v$ 需要花费为 $dep_u+dep_v-2dep_{lca}$

从下向上考虑每个点作为 $lca$ 的情况，把有点权和需要点权的点的 $dep$ 值加到堆里，分别找最小值即可。

然后当遇到更优的点时，我们考虑反悔：选中 $u$ 后，将 $u$ 的点权改为 $-dep_v+2dep_{lca}$，这样再次选中 $u$ 时就取消了 $u$ 与 $v$ 的匹配。

不过我们还要保证每个点的要求都被满足，所以我们给每个点权需求搭配一个 $-\inf$ 的贡献，这样最小化贡献是我们必然满足所有需求。

由于我们需要让父亲继承儿子的堆的信息，我们需要一个[可并堆](https://www.luogu.com.cn/problem/P3377)。

如果你不想手写的话可以用 pb_ds 代替。

如果你的可并堆出了什么问题，代码里有一个写的稀烂的指针版的左偏树留作参考。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5,M=5e5+10;
const long long inf=1e12;
int head[N],to[M],nxt[M],w[M],x[N],y[N],cnt,n,sum;
long long ans,dep[N];
void add_edge(int u,int v,int c){
	nxt[++cnt]=head[u],head[u]=cnt,to[cnt]=v,w[cnt]=c;
	nxt[++cnt]=head[v],head[v]=cnt,to[cnt]=u,w[cnt]=c;	
}

template<typename T>
struct pri_que{
	struct node{
		node *ls,*rs;
		int dis;
		T val;
		node(long long v=1e18,node *f=NULL){ls=rs=f;dis=0,val=v;}
		bool operator ==(node b){return val==b.val;}
	}*root,nul;
	pri_que(){root=&nul;}
	void push(T v){insert(v,root);}
	void join(pri_que p){
		root=join(root,p.root);
		p.root=&nul;
	}
	T top(){return root->val;}
	bool empty(){return *root==nul;}
	void pop(){
		node *r=root;
		root=join(root->ls,root->rs);
		delete(r);
	}
	
	void insert(T v,node* &rt){
		if(*rt==nul){
			rt=new node(v,&nul);
			return;
		}
		insert(v,rt->rs);
		if(rt->rs->val<rt->val)swap(rt->rs->val,rt->val);
		if(rt->rs->dis>rt->ls->dis)swap(rt->ls,rt->rs);		
		rt->dis=rt->rs->dis+1;
	}
	node *join(node *x,node *y){
		if(*x==nul||*y==nul)return *x==nul?y:x;
		if(y->val<x->val)swap(x,y);
		x->rs=join(x->rs,y);
		if(x->rs->dis>x->ls->dis)swap(x->ls,x->rs);
		x->dis=x->rs->dis+1;
		return x;
	}
};
pri_que<long long>q1[N],q2[N];
//以上为左偏树

void dfs(int rt,int fa){
	while(x[rt]--)q1[rt].push(dep[rt]);
	while(y[rt]--)q2[rt].push(dep[rt]-inf);
    //逐个考虑，同时给每个需求减去 inf 的贡献。
	for(int i=head[rt];i;i=nxt[i])
	  if(to[i]!=fa){
	  	dep[to[i]]=dep[rt]+w[i];
	  	dfs(to[i],rt);
	  	q1[rt].join(q1[to[i]]);
	  	q2[rt].join(q2[to[i]]);
	  }
	//当q2[rt].top()+q1[rt].top()-2*dep[rt]<0时应当反悔。
	while(!q2[rt].empty()&&!q1[rt].empty()&&q2[rt].top()+q1[rt].top()-2*dep[rt]<0){
		long long x=q1[rt].top(),y=q2[rt].top(),res=x+y-2*dep[rt];
		ans+=res;
		q1[rt].pop(),q2[rt].pop();
		q1[rt].push(x-res);
		q2[rt].push(y-res);
	}
} 

int main(){
//	freopen("conquer.in","r",stdin);
//	freopen("conquer.out","w",stdout);	
	int u,v,c;
	cin>>n;
	for(int i=1;i<n;++i)
		cin>>u>>v>>c,add_edge(u,v,c);
	for(int i=1;i<=n;++i)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;++i){
		int d=min(x[i],y[i]);
		x[i]-=d,y[i]-=d;
		sum+=y[i];
	}
	dfs(1,0);
	cout<<ans+sum*inf<<endl;
    //别忘了把减的 inf 加回来
}
```

---

## 作者：LZDQ (赞：5)

这题的复杂度可以不依赖于 $\sum v$，复杂度为 $O(n\log^2n)$ 或 $O(n\log n)$。

仍然考虑模拟费用流。令 $a_i=x_i-y_i$，相当于要拿正的去抵消负的。因为负的强制满流，所以随便选一个顺序给每个负的 $a_i$ 满流可以得到最优解。不难发现按照 dfs 序转移比较方便。具体来说，用数据结构维护边权（剩余流量）以及当前 dfs 到的点到每个点的距离。从一个点走到一个相邻点，对距离的影响可以转化为区间加。修改一条边的费用，也是区间加。维护一条边的费用，只需要判断反向边剩余流量是否为 0。

根据势能分析，显然每条边的反向边（从 0 变成 非 0）以及（从 非 0 变成 0）这两件事情只会发生常数次。因为每条边在 dfs 的过程中，分为三部分，第一部分和第三部分只会从外面走到里面，第二部分只会从里面走到外面。相当于先加一段再减一段再加一段。这样根据每条边（是否为 0）可以暴力维护出边的费用从而维护出距离。

以上过程都可以用树剖实现，比较复杂。~~换成 LCT 就 1log 了。~~

[代码](https://loj.ac/s/1484558)

---

## 作者：HJY2022 (赞：2)

真无敌了这题。

先转化为 $v_i = y_i - x_i$，变为让所有点权都非负。

考虑一个暴力做法，把所有负权点连向 $T$，把所有正权点从 $S$ 连一条边，树边设为无穷容量，费用为 $1$，跑最小费用最大流即可。

考虑如何优化。分别考虑每一个流量的源汇，一对源汇对费用的贡献为路径长度。

设 $d_x$ 为 $x$ 到根节点的树上距离。

考虑进行反悔贪心。每次拿出以当前点 $x$ 为根的内深度最小源汇 $u,v$ 将他们匹配，对答案的贡献即为 $d_u + d_v - 2dx$。将 $x$ 称为这组源汇的决策点。

考虑如何进行反悔操作，设这次选择的点是 $u,v$（ $u$ 源 $v$ 汇），决策点为 $x$，如果在决策点 $y$ 选取 $t$ 作为汇点更优，有：

$$d_u + d_v - 2d_x \geq d_u + d_t - 2d_y$$

$$2dx - d_v + d_t - 2d_y \leq 0$$

将 $2d_x - d_v$ 加入待选源点即可（可以发现贡献形式与上面的相同）。

对于汇点处理同理。

用可并堆维护以上流程即可。

注意由于要求汇点满流，所以可以在加入汇点的时候给其减去 $INF$，最后在统计答案时加上即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define fir first
#define sec second
const int MX = 2e6 + 7;
const ll inf = 1e12;
ll val[MX],dep[MX];ll ans = 0;
vector<pair<int,ll > > g[MX];
int pool[MX],top = 0;
struct node{int l,r;ll x;}s[MX << 1];
int rA[MX],rB[MX];
int newnode(ll x){int cur = pool[top];top--;s[cur].x = x;s[cur].l = s[cur].r = 0;return cur;}
int merge(int x,int y){
	if(!x || !y)return x | y;
	if(s[x].x > s[y].x)swap(x,y);
	if(rand() & 1)swap(s[x].l,s[x].r);
	s[x].r = merge(s[x].r,y);
	return x;
}

int read(){
	int x = 0,ch = getchar();
	while(!(ch >= 48 && ch <= 57))ch = getchar();
	while(ch >= 48 && ch <= 57)x = x * 10 + ch - 48,ch = getchar();
	return x;
}

void solve(int x,int f){
	if(val[x] > 0)for(int i = 1;i <= val[x];i++)rA[x] = merge(rA[x],newnode(dep[x]));
	else for(int i = 1;i <= -val[x];i++)rB[x] = merge(rB[x],newnode(dep[x] - inf));
	for(auto it : g[x]){
		int to = it.fir;ll w = it.sec;
		if(f == to)continue;
		dep[to] = dep[x] + w;solve(to,x);rA[x] = merge(rA[x],rA[to]);rB[x] = merge(rB[x],rB[to]);
	}
	while(rA[x] && rB[x] && s[rA[x]].x + s[rB[x]].x - 2 * dep[x] < 0){
		ll u = s[rA[x]].x,v = s[rB[x]].x;ans += s[rA[x]].x + s[rB[x]].x - 2 * dep[x];
		pool[++top] = rA[x];pool[++top] = rB[x];
		rA[x] = merge(s[rA[x]].l,s[rA[x]].r);rB[x] = merge(s[rB[x]].l,s[rB[x]].r);
		rA[x] = merge(rA[x],newnode(2 * dep[x] - v));rB[x] = merge(rB[x],newnode(2 * dep[x] - u));
	}
}
int main(){
	ios :: sync_with_stdio(false);
	for(int i = 1;i < MX;i++){pool[i] = i;top = i;}
	int n = read();
	for(int i = 1;i < n;i++){int u,v;ll w;u = read();v = read();w = read();g[u].push_back(mk(v,w));g[v].push_back(mk(u,w));}
	for(int i = 1;i <= n;i++){int x,y;x = read();y = read();val[i] = x - y;}
	for(int i = 1;i <= n;i++)if(val[i] < 0)ans += inf * -val[i];
	solve(1,1);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

加深一下对模拟费用流的理解。~~（毕竟我愚钝的大脑想不出任何贪心）~~

给每个点赋权值 $c_u = x_u - y_u$。当 $c_u>0$ 时，表示 $u$ 有**多余的权值**；当 $c_u < 0$ 时，表示 $u$ **需要权值**。（这一步进行了基本的贪心，优先就地取材）

如果 $n$ 比较小，很容易设计出这种费用流算法：

- 设源点 $s$，汇点 $t$；
- 如果 $c_u > 0$，创造 $s \to u$、容量为 $c_u$、费用为 $0$ 的边；如果 $c_u < 0$，创造 $u \to t$、容量为 $-c_u$、费用为 $0$ 的边；
- 对于一条树边，链接 $u \to v$ 和 $v \to u$、容量都为 $+ \infty$、费用都为 $c$ 的边。

跑最小费用最大流。

考虑在树上从下到上执行这个流程。考虑合并子树，把当前点 $u$ 当做 $\rm LCA$。有两种可能的操作：

- 增广。这个可以把子树和自己的所有情况都加进去，正负相抵消。
- 跑负环。可能的负环形态并不多：
	1. $s \to x \to u \to y \to s$，其中 $y$ 是**已经流过的点**，我们走的是反向边。该操作的物理意义是，$y$ 的点权不动了，让 $x$ 动。对应的反悔操作是：如果 $x$ 匹配上了，你加一个 $2dep_{lca} - dep_x$ 的物品放到“需求”中。 
   2. $t \to y \to u \to x \to t$，同理，对应的反悔操作是：如果 $y$ 匹配上了，加一个 $2dep_{lca} - dep_y$ 的物品放到“供应”中。

第一篇 xzy 的题解下有人提到了：如果这两个反水的物品全给放进去了怎么办？显然会出现下面这种情况：

![](https://s21.ax1x.com/2024/06/03/pkGXgFs.png)

路径有重合不优。

避免写太多优先队列，你可以把增广赋以很高的优先级，比如代价减去 $\rm + \infty$。

代码可以参见其他老哥。

---

## 作者：流水行船CCD (赞：1)

## 思路

简单观察：一个点自己的军队优先满足自己所在点的限制。

所以最开始可以将点划分为两类：需要军队的点和提供军队的点。

这是一个经典的费用流模型，对于树边 $(u,v,c)$，连接边 $(u,v,\infty,c),(v,u,\infty,c)$，对于需要 $c$ 支军队的点 $x$，连接 $(x,T,c,0)$，对于提供 $c$ 支军队的点 $x$，连接 $(S,x,c,0)$，此时的最小费用最大流就是答案。但是本题的数据范围较大，朴素费用流无法通过，考虑模拟费用流。

模拟费用流通常两种思路：

- 模拟 SSP 算法，找最短增广路去增广。
- 模拟网络单纯形算法，从 $T$ 向 $S$ 连一条流量无穷，费用负无穷的辅助边，转化为最小费用循环流问题，找任意负环进行推流。

如果找最短增广路，需要支持动态查询全局最近点对，不好做。

所以本题可以考虑去加速找负环的过程。由于保证总流量在 $10^6$ 级别，考虑每次找一个最小流量不为 $0$ 的负环，流 $1$ 的流量。

考虑枚举负环的 LCA，设为 $x$，则此时的负环有四种：

- $S \to u \to x \to v \to T \to S$：此时 $u,v$ 的正向边必须还有流量可以流。
- $T \to u \to x \to v \to S \to T$：此时 $u,v$ 的反向边必须还有流量可以流。
- $S \to u \to x \to v \to S$：此时 $u$ 的正向边，$v$ 的反向边必须还有流量可以流。
- $T \to u \to x \to v \to T$：此时 $u$ 的反向边，$v$ 的正向边必须还有流量可以流。

此时如果找到了最小流量不为 $0$ 的一个负环 $S \to u \to x \to v \to T \to S$ 这个环的权值为：$dep_u + dep_v - 2dep_x$。考虑拆贡献，原贡献可以看作成 $u$ 贡献 $dep_u$，$v$ 贡献 $dep_v$，$x$ 贡献 $-2dep_x$。此时发现只需要维护子树中点 $dep$ 的最小值，即可找出以 $x$ 为 LCA 的所有负环。

考虑维护两个可并堆，一个维护 $S \to u$ 这条边仍有流量的 $u$ 和 $T \to v$ 这条边仍有流量的 $v$ 的 $dep$ 的最小值，另一个维护 $u \to S$ 这条边仍有流量的 $u$ 和 $v \to T$ 这条边仍有流量的 $v$ 的 $dep$ 的最小值。

发现同一个可并堆的匹配正好无法形成负环，不同可并堆的任意匹配正好都对应上述四种可能负环中的一种，因此在 LCA 处将两个堆的最小值取出来，能形成负环就推流即可。

注意推流之后会把反向边流量加 $1$，所以需要在堆中加入被反向路径的贡献（反悔操作），这个实现的话就是把 $u,v$ 在堆中的 $dep_{u/v}$ 更改为 $-(dep_{u/v}-dep_x)+dep_{u/v}$，即把 $u/v$ 到 $x$ 这段路径的费用取反。

其实网络单纯形的增广次数我不会证，我个人认为是和 SSP 算法一样不超过 $|f|$ 轮的。

代码就不给了，其他题解已经有较为清晰的实现了。

---

## 作者：lalaouye (赞：1)

这题有显然的费用流做法，直接在树上建图就行，但是显然直接跑费用流过不了，考虑模拟费用流。题目保证流量在 $10^6$ 级别，我们可以考虑一点一点增广。但是我们发现我们无法使用传统方法模拟每次的增广路，我们考虑在保证最大流的情况下调整图的状态。首先我们发现不能够直接调整，因为直接调整无法保证最大流，我们这么做只能够保证这是个最小费用可行流。但是我们给汇点的边减去一个大数最后再加回来就能够保证了。

具体过程中涉及到距离，距离的计算考虑距离公式，$dist(u,v)=dis_u+dis_v-2dis_{lca}$。我们在 LCA 处进行匹配，每次选源汇中距离最小的两个点匹配，然而我们需要在之后反悔调整，则需要在集合中加入 $-dis_v+2dis_{lca}$，这样就把这次的代价消掉了，换成了新的代价。

找最小需要用可并堆维护，时间复杂度 $\mathcal{O}(n\log n)$。

这题用显然的 dp 做法，直接在树上跑 dp 就行。设 $f_{u,i}$ 表示对于以 $u$ 为根的子树，需要出/进 $i$ 的流量的最小代价。若 $i$ 为正表示出，否则为进。

dp 可以分为三步，第一步为合并子树，这是个 $(\min,+)$ 卷积，直接闵可夫斯基和即可。

第二部为加入当前节点的流量。设 $s_i=a_i-b_i$，若 $s_i>0$，相当于是将 $f_{u}$ 与 $g$ 做 $(\min,+)$ 卷积。其中 $g(i)=0,i\in[0,s_i]$。显然 $g$ 也是凸函数。若 $s_i\le 0$ 相当于整体平移直接打平移 tag 即可。

最后一步是处理父亲边的代价。相当于给差分数组下标小于等于 $0$ 的部分加上 $-w$，大于 $0$ 的部分加上 $w$。

利用平衡树可以做到 $\mathcal{O}(n\log^2n)$，精细实现可能可以达到 $\mathcal{O}(n\log n)$。

代码只有模拟费用流的。


```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 2000000000000
constexpr int N = 2e6 + 5, M = 1e5, P = 998244353;
typedef long long ll;
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int dep[N];
int n;
vector <pii> e[N];
int a[N], b[N];
int dist[N << 1], val[N << 1], ls[N << 1], rs[N << 1];
int tot;
int nw (int x) {
  val[++ tot] = x;
  dist[tot] = ls[tot] = rs[tot] = 0;
  return tot;
}
int merge (int x, int y) {
  if (! x || ! y) return x | y;
  if (val[x] > val[y]) swap (x, y);
  rs[x] = merge (rs[x], y);
  if (dist[rs[x]] > dist[ls[x]]) swap (ls[x], rs[x]);
  dist[x] = dist[rs[x]] + 1;
  return x;
}
int top (int rt) { return val[rt]; }
void pop (int &rt) {
  rt = merge (ls[rt], rs[rt]);
}
int A[N], B[N];
int sum;
void dfs (int u, int fa) {
  rep (i, a[u] + 1, b[u]) A[u] = merge (A[u], nw (- inf + dep[u])), sum += inf;
  rep (i, b[u] + 1, a[u]) B[u] = merge (B[u], nw (dep[u]));
  for (auto p : e[u]) {
    int v (p.first), w (p.second);
    if (v == fa) continue;
    dep[v] = dep[u] + w;
    dfs (v, u);
    A[u] = merge (A[u], A[v]);
    B[u] = merge (B[u], B[v]);
  }
  while (A[u] && B[u] && top (A[u]) + top (B[u]) - 2 * dep[u] < 0) {
    int x (top (A[u])), y (top (B[u]));
    sum += x + y - 2 * dep[u];
    int ca (A[u]), cb (B[u]);
    pop (A[u]), pop (B[u]);
    val[ca] = - y + 2 * dep[u];
    val[cb] = - x + 2 * dep[u];
    dist[ca] = dist[cb] = 0;
    ls[ca] = rs[ca] = 0;
    ls[cb] = rs[cb] = 0;
    A[u] = merge (A[u], ca);
    B[u] = merge (B[u], cb);
  }
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd ();
  rep (i, 2, n) {
    int u (rd ()), v (rd ()), w (rd ());
    e[u].eb (pii (v, w));
    e[v].eb (pii (u, w));
  }
  rep (i, 1, n) a[i] = rd (), b[i] = rd ();
  dfs (1, 0); cout << sum;
}
```

---

## 作者：SamHJD (赞：0)

首先想到费用流建模，源点连向所有 $a_i\ge b_i$ 的点，所有 $a_i\le b_i$ 的点连向汇点，流量都为 $a_i-b_i$，费用为 $0$，树边流量正无穷，费用为 $c$。

考虑模拟费用流，将每一条增广路径在 LCA 处考虑。从深到浅枚举每个点作为 LCA，不断取出其子树中负点 $dep$ 最小的点和正点 $dep$ 最小的点，将答案加上 $dep_u+dep_v-2\times dep_{lca}$。为了能够撤销，将 $u$ 的深度设为 $-(dep_u+2\times dep_{lca})$，将 $v$ 的深度设为 $-(dep_v+2\times dep_{lca})$，这样在枚举到深度更浅的点的时候便能以增广的方式撤销某条路径的 $u\to lca$ 或 $v\to lca$。同时为保证最后每个点符合要求，一开始需将负点的深度减去正无穷，并把每个点复制 $|a_i-b_i|$ 次。

合并子树的 $dep$ 信息需要写左偏树，也可以直接用 pbds。

```cpp
#include <bits/stdc++.h>
#define ll long long
#include <ext/pb_ds/priority_queue.hpp>
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
    x*=f;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=3e5+10;
const ll INF=1e13;
ll n,a[N],b[N],dep[N],ans,sum;
vector<pair<ll,ll> > g[N];
__gnu_pbds::priority_queue<ll,greater<ll> > qa[N],qb[N];
void dfs(int u,int fa){
    rep(i,a[u]+1,b[u]) qa[u].push(dep[u]-INF),sum++;
    rep(i,b[u]+1,a[u]) qb[u].push(dep[u]);
    for(auto e:g[u]){
        if(e.first==fa) continue;
        dep[e.first]=dep[u]+e.second;
        dfs(e.first,u);
        qa[u].join(qa[e.first]);
        qb[u].join(qb[e.first]);
    }
    while(!qa[u].empty()&&!qb[u].empty()&&qa[u].top()+qb[u].top()-2ll*dep[u]<0ll){
        ll x=qa[u].top();qa[u].pop();
        ll y=qb[u].top();qb[u].pop();
        ans+=x+y-2ll*dep[u];
        qa[u].push(-y+2ll*dep[u]);
        qb[u].push(-x+2ll*dep[u]);
    }
}
signed main(){
    read(n);
    rep(i,1,n-1){
        int u,v,c;read(u,v,c);
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }
    rep(i,1,n) read(a[i],b[i]);
    dfs(1,0);
    printf("%lld\n",ans+sum*INF);
    return 0;
}
```

---

