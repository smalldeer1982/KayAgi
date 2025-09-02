# [USACO05FEB] Secret Milking Machine G

## 题目描述

约翰正在制造一台新型的挤奶机，但他不希望别人知道。他希望尽可能久地隐藏这个秘密。他把挤奶机藏在他的农场里，使它不被发现。

在挤奶机制造的过程中，他需要去挤奶机所在的地方 $T$ 次。他的农场里有秘密的地道，但约翰只在返回的时候用它。农场被划分成 $N$ 块区域，用 $1$ 到 $200$ 标号。这些区域被 $P$ 条道路连接，每条路有一个小于 $10^6$ 的长度 $L$。两块区域之间可能有多条道路连接。为了减少被发现的可能，约翰不会两次经过农场上的任何一条道路。当然了，他希望走最短的路。

请帮助约翰寻找这 $T$ 次从仓库走到挤奶机所在地的路线。仓库是区域 $1$，挤奶机所在地是区域 $N$。我们现在要求的是约翰经过的这些道路中最长的路的长度最小是多少，当然他不能重复走某一条路。

请注意，我们要求的不是最短的总路程长度，而是所经过的直接连接两个区域的道路中最长的道路的最小长度。数据保证约翰可以找到 $T$ 条没有重复的从仓库到挤奶机所在区域的路。

## 说明/提示

选择 $1-2-3-7$ 和 $1-6-7$ 两条路线．这些路线中最长路的最小长度是 $5$。

对于 $100\%$ 的数据满足：$2\le N\le 200$，$1\le P\le 4\times 10^4$，$1\le T\le 200$，每条路的长度 $\le 10^6$。

## 样例 #1

### 输入

```
7 9 2
1 2 2
2 3 5
3 7 5
1 4 1
4 3 1
4 5 7
5 7 1
1 6 3
6 7 3```

### 输出

```
5```

# 题解

## 作者：WilliamFranklin (赞：7)

这道题较水，就是一个二分+最大流

### 主要思路

看到求这种最大最小值的，第一直觉就是——二分。

简单证明一下，发现的确可以。

然后根据之前做题的经验，把边权小于等于 $mid$ 的边的边权改为 $1$，大于的改为 $0$。

设源点为 $1$，汇点为 $N$，将无向图变为有向图（就是无向图中的每一条边都建正反两边），然后每次在二分时判断一下新建好的这个图中的最大流是否大于 $T$ 即可。

但是，这里有一个问题：在题目中，要求一条路只能走一次，但在我们新建的有向图中，无向图中的边都已转化成两条边，所以相当于每一条路都有可能走两边。

其实我们不用担心，因为在网络流中，正向流一次，再反向流一次后，就相当于没流，抵消了。

进一步，我们发现，在代码上有一个空间上的小优化：在建残余网络时，我们还需要原网络中的每一条边再建一个正边和反边。也就是说题目中无向图的每一条边对应到我们的残余网络中，都有 $4$ 条边。所以为了节省一下空间，我们可以将方向相同的两条边合并。

额。。。也许我说的不是很清楚，具体看代码吧。。。

### AC Code

```cpp
// 《 肥 肠 煎 蛋 》
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdio>
#include <queue>

using namespace std;

const int N = 205, M = 80005;

int h[N], e[M], ne[M], w[M], f[M], idx;
int n, m, S, T, t;
int d[N], cur[N];
bool vis[N];

void add(int a, int b, int c) {
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], w[idx] = c, h[b] = idx++;
}

bool bfs() {
	memset(vis, 0, sizeof(vis));
	memset(d, -1, sizeof(d)); 
	
	queue<int> q;
	
	q.push(S);
	d[S] = 0;
	vis[S] = 1;
	cur[S] = h[S];
	
	while (q.size()) {
		int t = q.front();
		
		q.pop();
		
		for (int i = h[t]; ~i; i = ne[i]) {
			int j = e[i];
			
			if (!vis[j] && f[i]) {
				vis[j] = 1;
				d[j] = d[t] + 1;
				cur[j] = h[j];
				
				if (j == T) return 1;
				
				q.push(j);
			}
		}
	}
	
	return 0;
}

int dfs(int u, int limit) {
	if (u == T) return limit;
	
	int flow = 0;
	for (int i = cur[u]; (~i) && flow < limit; i = ne[i]) {
		int j = e[i];
		
		cur[u] = i; 
		if (d[j] == d[u] + 1 && f[i]) {
			int k = dfs(j, min(f[i], limit - flow));
			
			if (!k) d[j] = -1;
			
			f[i] -= k;
			f[i ^ 1] += k;
			flow += k;
		}
	}
	
	return flow;
}

int dinic() {
	int r = 0, flow;
	
	while (bfs()) {
		while (flow = dfs(S, 1e9)) {
			r += flow;
		}
	}
	
	return r;
}

bool check(int x) {
	for (int i = 0; i < idx; i++) {
		if (w[i] <= x) f[i] = 1;
		else f[i] = 0;
	}
	
	return dinic() >= t;
}

int main() {
	memset(h, -1, sizeof(h));
	
	cin >> n >> m >> t;
	
	S = 1, T = n;
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		
		cin >> a >> b >> c;
		
		add(a, b, c);
	}
	
	int l = 1, r = 1e6;
	
	while (l < r) {
		int mid = l + r >> 1;
		
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	
	cout << l << endl;
	
	return 0;
}
```

### 谢谢观看！

---

## 作者：asd_a (赞：6)

## 网路流为啥要二分？？？
## 亲测：两个题解写的网络流都没过
我们可以将边按边权排序，然后从1开始枚举验证。  
此处就不讲怎么建图了，（将容量设为一即可）
### 问题来了：
此时时间复杂度：$O(nm^2)$?
### 错了
我们不必重新建图，然后重新跑dinic  
我们可以利用上一次dinic所剩下的残余网络  
在里面加新增的边，直接跑dinic，求出新增的路径个数  
问题就解决了。。。  
时间复杂度为：$O(nm)$
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int fi[N],ne[N],to[N],w[N],tot=1;
inline void add(int x,int y,int z){ne[++tot]=fi[x];to[tot]=y;w[tot]=z;fi[x]=tot;}
inline void ad(int x,int y,int z){add(x,y,z);add(y,x,z);}
int dis[N],s,t;
bool bfs()
{
    memset(dis,0,sizeof(dis));
    queue<int>q;
    q.push(s);
    dis[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=fi[x];i;i=ne[i])
        {
            int y=to[i];
            if(w[i]&&!dis[y])
            {
                dis[y]=dis[x]+1;
                if(y==t)return 1;
                q.push(y);
            }
        }
    }
    return 0;
}
int dfs(int x,int flow)
{
    if(x==t||flow==0)return flow;
    int res=0,u;
    for(int i=fi[x];i;i=ne[i])
    {
        int y=to[i];
        if(dis[y]==dis[x]+1)
        {
            u=dfs(y,min(flow,w[i]));
            res+=u;flow-=u;w[i]-=u;w[i^1]+u;
            if(!flow)break;
        }
    }
    if(flow)dis[x]=-1;
    return res;
}
int dinic()
{
    int mf=0,x;
    while(bfs())
        while(x=dfs(s,INT_MAX))
            mf+=x;
    return mf;
}
struct edge{
    int x,y,z;
}e[N];
bool cmp(edge x,edge y){return x.z<y.z;}
int n,m,T;
int main()
{
    scanf("%d%d%d",&n,&m,&T);
    s=1;t=n;
    int now=1;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
    sort(e+1,e+m+1,cmp);
    for(int i=1;;i++)
    {
        for(;now<=m&&e[now].z<=i;now++)
            ad(e[now].x,e[now].y,1);
        T-=dinic();
        if(T<=0)
        {
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：Tyher (赞：4)

### 提供一种网络流做法

使得最长的边的长度最小，考虑用二分答案，那么关键就是怎么check

那么题目就转化成了怎么求出一张图是否可以有t条从起点到终点的路径

题目的关键在于边不能重复用，可以考虑网络流，将所有的边权值都设为1,然后跑最大流，因为这样同一条边是不能够重复使用的。

合法的情况就是最大流比t要大，那么就存在t条路径

对于二分对最大流的限制，就是边权值大于mid的边无法通过，那么我们在dinic的时候判断一下，如果权值大于mid就直接忽视掉就可以了

网络流的复杂度是O(nm)，总复杂度O(nmlog权值)

~~但是跑得挺快哈哈哈~~

最后注意是无向边
```
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#define il inline
#define rg register
#define ll long long
#define ld long double
#define N 300010
#define inf 2000000000
using namespace std;
int n,m,em,cnt=1,s,t;
int u,v,c,le,ri,ans;
int fl[N],cur[N],hd[N],de[N];
struct Edge{
	int nt,to,w,c;
}edge[N];
il void re(rg int &x);
il void link(rg int fm,rg int to,rg int w,rg int c);
int check(rg int lim);
int dinic(rg int lim);
int bfs(rg int lim);
int dfs(rg int i,rg int flow,rg int lim);
int main(){
	freopen("s.in","r",stdin);
	re(n),re(m),re(em),s=1,t=n;
	for(rg int i=1;i<=m;++i){
		re(u),re(v),re(c);
		link(u,v,1,c),link(v,u,1,c);
		ri=max(ri,c);
	}
	while(le<=ri){
		rg int mid=((le+ri)>>1);
		if(check(mid))ans=mid,ri=mid-1;
		else le=mid+1;
	}
	printf("%d",ans);
    return 0;
}
int bfs(rg int lim){
    memset(de,0,sizeof(de));
    queue<int>Q;
    while(!Q.empty())Q.pop();
    de[s]=1,Q.push(s);
    do{
        rg int i=Q.front();
        Q.pop();
        for(rg int k=hd[i];k;k=edge[k].nt){
            rg int qw=edge[k].to;
            if((!de[qw])&&edge[k].w>0&&edge[k].c<=lim){
                de[qw]=de[i]+1;
                Q.push(qw);
                if(qw==t)return 1;
            }
        }
    }while(!Q.empty());
    return 0;
}
int dfs(rg int i,rg int flow,rg int lim){
    if(i==t)return flow;
    for(rg int &k=cur[i];k;k=edge[k].nt){
        rg int qw=edge[k].to;
        if(de[qw]==de[i]+1&&edge[k].w>0&&edge[k].c<=lim){
            rg int di=dfs(qw,min(edge[k].w,flow),lim);
            if(di>0){
                edge[k].w-=di,edge[k^1].w+=di;
                return di;
            }
        }
    }
    return 0;
}
int dinic(rg int lim){
	rg int ans=0;
	while(bfs(lim)){
		for(rg int i=1;i<=t;++i)
			cur[i]=hd[i];
		while(int d=dfs(s,inf,lim))
			ans+=d;
	}
	return ans;
}
int check(rg int lim){
	for(rg int i=1;i<=cnt;++i)
		edge[i].w=fl[i];
	if(dinic(lim)>=em)return 1;
	return 0;
}
il void re(rg int &x){
    rg int res=0;rg int w=1;char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')w=-1,c=getchar();
    while(c>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0',c=getchar();
    x=w*res;
}
il void link(rg int fm,rg int to,rg int w,rg int c){
	edge[++cnt].nt=hd[fm];
	edge[cnt].to=to,edge[cnt].w=w;
	edge[cnt].c=c,fl[cnt]=w;
	hd[fm]=cnt;
}

```

---

## 作者：mjsdnz (赞：2)

+ [原题连接](https://www.luogu.com.cn/problem/P1674)
## 题目大意
给出一张无向图，图上每条边只允许经过一次，给出经过图的次数 $T$，找到经过的最长边中长度最小的长度。
## 建模
很明显费用流建模，每条边权值为长度，流量为一，直接连边，注意建双向边。那这个最长的边的长度怎么着呢？其实很简单，只要将更新 $dis_{v}$ 的条件由 $dis_{v}>dis_{u}+E_{u,v}$ 改为 $dis_{v}=\max(dis_{u},E_{u,v})$ 即可。同理，最小费用也改为 $mincost=\max(mincost,dis_{t})$（$t$ 为汇点）。当增广到的流量大于 $T$ 时，直接跳出搜索，输出答案即可。代码用的是 Dijkstra 找增广路，本来还在想势能怎么更新，写着写着发现没必要用势能，就直接放个阉割版 Dijkstra 上去了，好像也不用开 longlong。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int M = 5e5 + 10;
const int inf = 0x7fffffff;
struct edge {
	int u, v, c, val, nxt;
	edge(int u = 0, int v = 0, int c = 0, int val = 0, int nxt = 0) : u(u), v(v), c(c), val(val), nxt(nxt) {}
} e[M];
int head[N];
int cnt = 1;
int now[N];
void ADD(int u, int v, int c, int val) {
	cnt++;
	e[cnt] = edge(u, v, c, val, head[u]);
	head[u] = cnt;
}
void add_edge(int u, int v, int c, int val) {
	ADD(u, v, c, val);
	ADD(v, u, 0, -val);
}

int n, m, T;
int s, t;
struct Node {
	int name, dis;
	bool operator<(const Node &a) const {
		return dis > a.dis;
	}
};
int dis[N];
bool vis[N];
int h[N];   //完全没有用到的势能
int pro[N];
int flow[N];
int mn, mx;
bool dj() {
	for (int i = 1; i <= n; i++) flow[i] = dis[i] = inf;
	for (int i = 1; i <= n; i++) pro[i] = -1;
	memcpy(now, head, sizeof head);
	dis[1] = 0;
	priority_queue<Node>q;
	q.push({1, dis[1]});
	while (q.size()) {
		int u = q.top().name;
		int d = q.top().dis;
		q.pop();
		if (d > dis[u]) continue;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			int c = e[i].c;
			if (!c) continue;
			int val = e[i].val;
			if (dis[v] > max(dis[u], val)) {
				dis[v] = max(dis[u], val);   //注意这里的长度转移
				flow[v] = min(flow[u], c);
				pro[v] = i;
				q.push({v, dis[v]});
			}
		}
	}
	return dis[t] == inf;
}
void maxflow() {
	while (!dj()) {
		mx += flow[t];
		mn = max(mn, dis[t]);
		if (mx >= T) {
			cout << mn;
			exit(0);
		}
		int u = t;
		while (u != s) {
			e[pro[u]].c -= flow[t];
			e[pro[u] ^ 1].c += flow[t];
			u = e[pro[u]].u;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> T;
	s = 1, t = n;
	for (int i = 1; i <= m; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		add_edge(a, b, 1, l);   //朴实无华的建图
		add_edge(b, a, 1, l);   //记得反边也建上
	}
	maxflow();
}
```
第一次写题解，如有什么错误或者不理解的地方，欢迎留言。

---

## 作者：Math_rad_round (赞：2)

**提供一种费用流解法**

我们知道，费用流的的一种常见解法是用 SPFA 找到从 $S$ 到     $T$ 的以费用为权的最短路（最小费用），将这条路上的**流量**乘以**最小费用**累加到答案中，直到 SPFA 最后找不到这个最短路。

现在这道题需要我们找到 $t$ 条路，当图的流量到 $t$ 时自然就意味着有 $t$ 条不同路径，但是我们这道题求的不是所有路径长度和，而是最大的一条路的长度。

这时候我们就可以魔改计算费用的方法：在 SPFA 时，我们将      $d[i]$ 定义为 $S$ 到 $i$ 经过的最大边权。这样当         $d[v]>\max(d[u],\ E_{u,v})$ 时令 $d[v]=\max(d[u],\ E_{u,v})$ 

同样每次 SPFA 完之后，把总费用更新为这一次的费用，即        $ansf=\max(ansf,d[n])$，当流量累计超过 $t$ 时，停止费用流，输出总费用（答案）。

其他的部分就是板子了，注意建图的时候要将两个方向的边和他们的反向边都建上。

### 代码：

```cpp
#include<iostream>
#include<map>
#include<cstdio>
using namespace std;
struct bian{
	long long z,v,next,f;
};
bian t[1000000];
int ha=1;
//储存边的数据结构 ，f = 这条边的费用 
struct dian{
	long long l,fi,si,la,o,pr,zh,in;
};
dian h[100000];
//储存点的数据结构， fi = 这个点的第一条边的位置，la是最后一条 
//si是指边的数量，l是指这个点到原点的距离 
int l[1000000],he=0,w=0;
//广搜用的队列 
int n,m,qi,zo;//点数、边数、源点、汇点 
long long ans,ansf;
int gua(int,int);
int dfs(int);
int zdf(void);

int un=0; 
int wuxi=999999999;

int moge(int a1,int a2,int a3,int a4){
	int o=h[a1].la;
	h[a1].la=++ha;
	if(h[a1].si==0){
		h[a1].fi=h[a1].la;
	}
	h[a1].si++;
	t[h[a1].la].v=a2;
	t[h[a1].la].z=a3;
	t[h[a1].la].next=0;
	t[h[a1].la].f=a4;
	t[o].next=h[a1].la;
	return 0;
}
int add(int a1,int a2,int a3,int a4){
    moge(a1,a2,a3,a4);
    moge(a2,a1,0,-a4);
    return 0;
}
int spfa(){
	w=he=0;un++;
	for(int i=1;i<=n;i++)h[i].l=h[i].o=wuxi;
	l[w++]=qi;h[qi].in=un;h[zo].pr=-1;h[qi].l=0;
	while(w>he){
		int q=l[he++];h[q].in=0;
		for(int u=h[q].fi;u;u=t[u].next){
			if(t[u].z!=0&&max(h[q].l,t[u].f)<h[t[u].v].l){
				h[t[u].v].l=max(h[q].l,t[u].f);
				h[t[u].v].o=min(h[q].o,t[u].z);
				h[t[u].v].pr=q;
				h[t[u].v].zh=u;
				if(h[t[u].v].in!=un){
					h[t[u].v].in=un;
					l[w++]=t[u].v;
				}
			}
		}
	}
	return h[zo].pr!=-1;
}

int oks=0;

int suan(){
	while(spfa()){
		ans+=h[zo].o;
		ansf=max(ansf,h[zo].l);
		if(ans>=oks)return 0;
		int uq=zo;
		while(uq!=qi){
			t[h[uq].zh].z-=h[zo].o;
			t[h[uq].zh^1].z+=h[zo].o;
			uq=h[uq].pr;
		}
	}
	return 0;
}

int main(){
	cin>>n>>m>>oks;
	qi=1;zo=n;
	for(int i=0;i<m;i++){
		int a1,a2,a4;//从a1到a2有一条费用为a4的边 
		cin>>a1>>a2>>a4;
		add(a1,a2,1,a4);
		add(a2,a1,1,a4);
	}
	suan();
	cout<<ansf;
	return 0; 
}
```
（直接用模板改了几个数ctrl cv过来的，码风很丑望见谅）

---

## 作者：PosVII (赞：1)

**前言**

------------

本题使用费用流。

**思路**

------------

最长的路最小，要走出至少 $t$ 条路。考虑使用最小费用最大流。将一条路线视作一条流，而经过边的长度视作费用，费用是取最大值而不是相加

但是得到最大流时的费用可能就不是最小答案了，所以在跑费用流的途中满足条件直接退出就可以了。

本题对费用流的理解有些考察，总体来讲本题就是费用流变式。若是用网络流或二分的方法比费用流麻烦了不少。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
const int MAXN=2e5+5,N=2e4+5;
bool vis[N];
int n,m,s,t,x,y,z,f,dis[N],pre[N],last[N],flow[N],maxflow,mincost;
struct node {
	int to,next,flow,dis;
}edge[MAXN];
int head[N],cnt; 
queue<int> q;
void add(int from,int to,int flow,int dis) {
	edge[++cnt].next=head[from];
	edge[cnt].to=to;
	edge[cnt].flow=flow;
	edge[cnt].dis=dis;
	head[from]=cnt;
}
bool spfa(int s,int t) {
	memset(dis,0x7f,sizeof(dis));
	memset(flow,0x7f,sizeof(flow));
	memset(vis,0,sizeof(vis));
	q.push(s);vis[s]=1;dis[s]=0;pre[t]=-1;
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		vis[now]=0;
		for(int i=head[now];~i;i=edge[i].next) {
			if(edge[i].flow>0&&dis[edge[i].to]>max(dis[now],edge[i].dis)) {
				dis[edge[i].to]=max(dis[now],edge[i].dis);
				pre[edge[i].to]=now;
				last[edge[i].to]=i;
				flow[edge[i].to]=min(flow[now],edge[i].flow);
				if(!vis[edge[i].to]) {
					vis[edge[i].to]=1;
					q.push(edge[i].to);
				}
			}
		}
	}
	return ~pre[t];
}
int pos;
void MCMF() {
	while(spfa(s,t)) {
		int now=t;
		maxflow+=flow[t];
		mincost=max(mincost,dis[t]);
		if(maxflow>=pos) return;
		while(now!=s) {
			edge[last[now]].flow-=flow[t];
			edge[last[now]^1].flow+=flow[t];
			now=pre[now];
		}
	}
}
void addt(int from,int to,int flow,int dis) {
	add(from,to,flow,dis);
	add(to,from,0,-dis);
}
int u,v,w,c;
int main() {
	memset(head,-1,sizeof(head));cnt=-1;
	scanf("%d %d %d",&n,&m,&pos);
	s=1,t=n;
	for(int i=1;i<=m;++i) {
		scanf("%d %d %d",&u,&v,&w);
		addt(u,v,1,w);
		addt(v,u,1,w);
	}
	MCMF();
	printf("%d",mincost);
	return 0;
}
```



---

## 作者：神眷之樱花 (赞：1)

# 题意
$n$个点，$m$ 条边的无向图，求出 $t$ 条路径，使路径中最长的边最小。
# 题解
看到最大的最小应该能马上想到二分答案。

于是我们差的就是一个 check 函数了。

### 不正确暴力
从点 $1$ 出发遍历，将遍历的边及其反边打上标记，直至有 $t$ 条路径为止。

这么一看感觉仿佛还可以，但是仔细想想，这样做不仅复杂度不优，反而得到的答案还并不正确。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w1bgcm7v.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可能在第一次遍历的时候，上面那条路径与 $n$ 连接的那条边，已经被打上标记了。而第二条路径其实可以走下面到达 $n$的，但是却把上面的那条占了，就只能跑出 $1$ 条路径，但其实是 $2$ 条的。这种情况根据你存边的顺序是有可能出现的。

所以这样的暴力不行。

### 并查集

使用并查集来维护也挺妙的，这是其它题解的思路，我没有打过，但是据他说有一个点卡不过，不知道加了按秩合并和编译优化之后能不能卡过。

### 网络流
这道题其实就考了一个最大流。

为什么这道题能用网络流来做呢？

其实一条路径就可以看做是从源点流出去的一个单位流量，因为残量网络是一个 DAG 图，所以满足了一条边只能经过一个方向的限制条件。

而我们将每条边的容量设为 $1$ ，则相当于限制了一条边只能被一条路径经过。感性理解一下相当于是有 $t$ 列火车从源点出发，向汇点开去，因为火车很长，它到达了汇点之后，尾巴还没有离开源点，而每条边只有一条轨道，于是每列火车都把它经过的边上的轨道都占了，就不会出现有两列火车同时在一条边的情况，所以这样的话，每条边是不会被重复经过的。

# 代码
```cpp
#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<iostream>
#include<queue>

const int N = 205, M = 4e4 + 5;

int head[N], nex[M << 1], to[M << 1], w[M << 1], edge[M << 1], n, m, siz = 1, t, ans;

long long L = 0, R = 1e9 + 7, mid;

inline void add(int u, int v, int W) {
	nex[++siz] = head[u]; w[siz] = W;
	to[siz] = v; head[u] = siz;
	nex[++siz] = head[v]; w[siz] = W;
	to[siz] = u; head[v] = siz;
}

int d[N], now[N]; std:: queue < int > q;

bool bfs(int s) {
	memset(d, 0, sizeof(d));
	while(!q.empty()) q.pop();
	q.push(s); d[s] = 1; now[s] = head[s];
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int i = head[x]; i; i = nex[i])
			if(edge[i] && !d[to[i]] && w[i] <= mid) {
				q.push(to[i]);
				now[to[i]] = head[to[i]];
				d[to[i]] = d[x] + 1;
				if(to[i] == n) return true;
			}
	}
	return false;
}

int dinic(int x, int flow) {
	if(x == n) return flow;
	int res = flow, k, i;
	for(i = now[x]; i && res; i = nex[i])
		if(edge[i] && d[to[i]] == d[x] + 1 && w[i] <= mid) {
			k = dinic(to[i], std::min(res, edge[i]));
			if(!k) d[to[i]] = 0;
			edge[i] -= k; edge[i ^ 1] += k;
			res -= k;
		}
	now[x] = i;
	return flow - res;
}

inline int read() {
	int x = 0, f = 1, c = getchar();
	for(; !isdigit(c); c = getchar())
		if(c == '-')
			f = -1;
	for(; isdigit(c); c = getchar())
		x = x * 10 + c - 48;
	return x * f;
}

int main() {
	n = read(), m = read(), t = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), W = read();
		add(u, v, W);
	}
	while(L <= R) {
		for(int i = 1; i <= siz; i++) edge[i] = 1;
		mid = (L + R) >> 1;
		int flow = 0, maxflow = 0;
		while(bfs(1))
			while(flow = dinic(1, 0x3f3f3f3f)) maxflow += flow;
		if(maxflow >= t)
			R = mid - 1, ans = mid;
		else 
			L = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}```

---

## 作者：天南地北 (赞：1)

#### 其实比较明显的网络流（最大流）

不会网络流的童鞋可以绕开本文……

#### 建图

本题网络流的建图很简单，就是按照题目的说法来建图就好了，当然了，我们这里超级源点$S$设置为$1$，超级源点$T$设置为$n$。
#### 求经过的这些道路中最长的路的最小长度$?$

其实也很简单，我们来分析一下：
- 由于我们不能保障在跑$Dinic$时，限制跑边，所以我们不能马上就跑最终图
- 既然不能马上跑最终图，而且我们要求道路中最长的路的最小长度，我们能不能够通过枚举最长的路的最小长度，然后将小于等于这个枚举变量的路全部加边呢？
- 然后呢？然后我们跑$Dinic$，如果在图（应该说是残留网络）中，产生了$K$条$S-T$的路径，那么即可输出答案……

#### 具体步骤
第一步，我们需要将所有边，按照长度排序。

第二步，我们枚举答案。

枚举答案步骤如下：

1. 每次将【长度$==$当前枚举的答案】的边加入到残留网络之中
2. 跑$Dinic$,然后用$K$减去每次跑出的最大流
3. 当$K<=0$时，那么说明在当前答案已经可以跑出了$K$条$S-T$的路径，那么此时输出答案就可以了

#### 参考程序
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<stack>
using namespace std;

const int maxn=40000+10;
const int maxm=100000+10;
const int inf=100000000+10;

struct edge
{
	int obj,cap;
	edge *Next,*rev;
}Edge[maxm<<1];

edge *head[maxm<<1];
edge *nhead[maxm<<1];

int cur=0;
int level[maxn];
int que[maxn];
int n,m,k,s,t;

struct edgege
{
	int x,y,z;
}E[maxm<<1];//x，y为边的两端，z为长度

void Add_edge(int x,int y,int z)//加边
{
	cur++;
	Edge[cur].obj=y;
	Edge[cur].cap=z;
	Edge[cur].Next=head[x];
	Edge[cur].rev=&Edge[cur+1];
	head[x]=Edge+cur;
	
	cur++;
	Edge[cur].obj=x;
	Edge[cur].cap=z;//注意这里是双向边
	Edge[cur].Next=head[y];
	Edge[cur].rev=&Edge[cur-1];
	head[y]=Edge+cur; 
}
int BFS()//跑图（不解释）
{
    for(int i=1; i<=t; i++)
    {
        nhead[i]=head[i];
        level[i]=0;
    }  
    level[s]=1;
    que[1]=s;
    int he=0,ta=1;
    while(he<ta)
    {
        int node=que[++he];
        for(edge *p=head[node];p;p=p->Next)
            if(p->cap&&(!level[p->obj]))
            {
                level[p->obj]=level[node]+1;
                que[++ta]=p->obj;
            }
    }
    return level[t];
}
int DFS(int node,int flow)//跑图（不解释）
{
	if(node==t||!flow)return flow;
	int ret=0;
	for(edge *&p=nhead[node];p;p=p->Next)
		if(p->cap&&level[p->obj]==level[node]+1)
		{
			int to=p->obj;
			int f=DFS(to,min(flow,p->cap));
			flow-=f;
			ret+=f;
			p->cap-=f;
			p->rev->cap+=f;
			if(!flow)break;
		}
	if(flow)level[node]=-1;
	return ret;
}
int Dinic()//跑图（不解释）
{
	int flow=0;
	while(BFS())flow+=DFS(s,inf);	
	return flow;
}
bool cmp(edgege x,edgege y)//快排的
{
	return x.z<y.z;
}
int main()
{
   scanf("%d%d%d",&n,&m,&k);
	s=1,t=n;//超级源点建立
	for(int i=1;i<=t;i++)head[i]=NULL;//弧的初始化（只是加快Dinic跑图）
	for(int i=1;i<=m;i++)
	    scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].z);
	sort(E+1,E+1+m,cmp);//快排
	int j=1;
	for(int i=1;;i++)//枚举答案
	{
		for(;j<=m&&E[j].z<=i;j++)
			Add_edge(E[j].x,E[j].y,1);//加边
		k-=Dinic();
		if(k<=0)//已经找到了k种不同路径
		{
			printf("%d\n",i);
			return 0;
		}
	}
	
}

```


---

## 作者：yizhiming (赞：0)

再看到这种反向边权值不为 $0$ 的网络流我就疯了。

[Link](https://www.luogu.com.cn/problem/P1674)

### 题目大意

给定一张 $n$ 个点，$m$ 条边的带权无向图，求出 $T$ 条 $1$ 到 $n$ 的路径使得这些路径上最长的一条边最短。

$2\leq n \leq 200,1\leq m \leq 4\times 10^4,T\leq 200$，边权 $\leq 10^6$。

### 题目分析

看到最长的最短这一类想二分最小值，这样我们每次只走小于等于二分值的边即可。

考虑如何处理掉 $T$ 的限制，其实等价于找到 $T$ 条流从 $1$ 流向 $n$，是一个网络流建模，我们直接将原图连边即可。

若最终流量高于 $T$，那就往下接着二分，反之往上二分。

但是最大的问题在哪里？你发现原图是一个无向图，我们网络流能处理这种东西吗？当然是可以的。

我们原本是存在双向边的，一个是原边，另一个是边权为 $0$ 的用于回流，但是现在怎么办呢？我们直接建两条边，边权都是原本的边权即可。

考虑为什么正确，网络流增广的时候，对于一条边 $(u,v)$ 两边的深度差至少为 $1$ 且会定向，所以一定不会同时走两个方向，同时反向边只需要支持一个存储反流的功能，这个反向边同样可行，所以直接这样建边就是对的。

这种边的存在目的在于令这条边从哪个方向走都需要保持原本的边权，虽然挺少见的，但是感觉是个有用的技巧。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 205;
const int M = 4e4+5;
int head[N],S,T,tote=1;
struct aa{
	int nxt,to,val,w,f;
}edge[M*2];
void link(int u,int v,int w,int c){
	edge[++tote].nxt = head[u];edge[tote].to = v;head[u] = tote;edge[tote].val = w;edge[tote].f = w;edge[tote].w = c;
}
int U[M],V[M],W[M],n,m,t,inf = 1e9;
void build(int x){
	for(int i=1;i<=tote;i++){
		edge[i].val = edge[i].f;
	}
}
int flow;
int dep[N];
queue<int>q;
bool bfs(int x){
	memset(dep,0,sizeof(dep));
	q.push(S);
	dep[S] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(!dep[now]&&edge[i].val&&edge[i].w<=x){
				dep[now] = dep[u]+1;
				q.push(now);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int f,int x){
	if(u==T){
		return f;
	}
	int used = 0;
	for(int i=head[u];i&&f;i=edge[i].nxt){
		int now = edge[i].to;
		if(dep[now]==dep[u]+1&&edge[i].val&&edge[i].w<=x){
			int w = dfs(now,min(f,edge[i].val),x);
			f-=w;used+=w;
			edge[i].val-=w;edge[i^1].val+=w;
		}
	}
	if(!used){
		dep[u] = 0;
	}
	return used;
}
void dinic(int x){
	flow = 0;
	while(bfs(x)){
		flow+=dfs(S,inf,x);
	}
}
bool check(int x){
	build(x);
	dinic(x);
	return flow>=t;
}
int main(){
	n = read();m = read();t = read();
	S = 1;T = n;
	int u,v,w;
	for(int i=1;i<=m;i++){
		u = read();v = read();w = read();
		link(u,v,1,w);link(v,u,1,w);
	}
	int l=0,r=1e6,ans = -1;
	while(l<=r){
		int mid = (l+r)/2;
		if(check(mid)){
			ans = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	cout<<ans<<"\n";
	return 0;
}

```


---

## 作者：Fzrcy (赞：0)

最长的路的长度最小，考虑二分。二分答案 $Mid$，对于长度小于 $Mid$ 的边 $x\longleftrightarrow y$，在新图中连边 $x\xleftrightarrow{cap=1}y$，最后跑最大流，若最大流大于等于 $T$ 则表明答案小于等于 $Mid$ 否则表示答案大于 $Mid$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=444, INF=1e9, M=4e4+11;
struct Edge{int u, v, flow, cap;};
struct Dinic{
  vector<int> E[N]; vector<Edge> edge;
  int dist[N], vis[N], c[N], s, t, tt;

  void init(int sum){
    edge.clear(), s=t=tt=0;
    for(int i=1; i<=sum; i++)
      dist[i]=vis[i]=c[i]=0, E[i].clear();
  }

  void link(int u, int v, int cap){
    E[u].push_back(int(edge.size())), edge.push_back({u, v, 0, cap});
    E[v].push_back(int(edge.size())), edge.push_back({v, u, 0, 0});
  }

  bool BFS(){
    for(int i=1; i<=tt; i++) dist[i]=INF, vis[i]=c[i]=0;
    queue<int> q; q.push(s), dist[s]=0, vis[s]=1;
    while(!q.empty()){
      int u=q.front(); q.pop();
      for(int i:E[u]){
        Edge e=edge[i];
        if(e.cap>e.flow&&!vis[e.v])
          vis[e.v]=1, dist[e.v]=dist[e.u]+1, q.push(e.v);
      }
    }
    return vis[t];
  }

  int dfs(int u, int a){
    if(u==t||a==0)return a;
    int tot=0, f=0;
    for(int &i=c[u]; i<int(E[u].size()); i++){
      Edge e=edge[E[u][i]];
      if(dist[e.v]==dist[e.u]+1&&(f=dfs(e.v, min(e.cap-e.flow, a)))>0){
        edge[E[u][i]].flow+=f, edge[E[u][i]^1].flow-=f, tot+=f, a-=f;
        if(!a)break;
      }
    }
    return tot;
  }

  int solve(int S, int T, int Total){
    s=S, t=T, tt=Total; int ans=0;
    while(BFS()) ans+=dfs(s, INF);
    return ans;
  }
}g;

int n, m, T, X[M], Y[M], Z[M];

bool check(int Mid){
  g.init(n);
  for(int i=1; i<=m; i++) if(Z[i]<=Mid)
    g.link(X[i], Y[i], 1), g.link(Y[i], X[i], 1);
  return g.solve(1, n, n+1)>=T;
}

int BinarySearch(){
  int l=1, r=1000001, ans=-1;
  while(l<=r){
    int Mid=l+r>>1;
    if(check(Mid)) r=Mid-1, ans=Mid;
    else l=Mid+1;
  }
  return ans;
}
int main(){
  cin>>n>>m>>T;
  for(int i=1; i<=m; i++)
    cin>>X[i]>>Y[i]>>Z[i];
  cout<<BinarySearch()<<'\n';
  return 0;
}
```


---

## 作者：simonG (赞：0)

更改：删除了标点和公式的空格。

题意：找到 $T$ 条 $1\sim n$ 的路径，使得路径权值最大值最小，并且一条边一个方向只能经过一次。

我们看到最大值最小，首先考虑二分。

边有容量限制，我们考虑最大流。

我们二分一个数 $w$， 把所有不大于 $w$ 的边都加入网络，容量为 $1$，建双向边。

这样可以保证一条边一个方向只能经过一次的限制。

建立一个超级源点 $s$，$s$ 向 $1$ 建一条容量为 $T$ 的边。

然后跑一个从 $s\sim n$ 的最大流。

若最大流为 $T$，意味着能找到 $T$ 条路径，它们路径权值最大值不大于 $w$。

最后输出 $w$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=1e5+10,inf=2e9;
struct flow {
	int tot=1,head[N],nxt[M],ver[M],limit[M];
	void add(int u,int v,int w) {
		nxt[++tot]=head[u],head[u]=tot,ver[tot]=v,limit[tot]=w;
		nxt[++tot]=head[v],head[v]=tot,ver[tot]=u,limit[tot]=w;
	}
	int T,dis[N],cur[N];
	int dfs(int id,int res) {
		if(id==T) return res;
		int flow=0;
		for(int i=cur[id]; i&&res; i=nxt[i]) {
			cur[id]=i;
			int c=min(res,(int)limit[i]),it=ver[i];
			if(dis[id]+1==dis[it]&&c) {
				int k=dfs(it,c);
				flow+=k,res-=k,limit[i]-=k,limit[i^1]+=k;
			}
		}
		return flow;
	}
	int maxflow(int s,int t) {
		T=t;
		int flow=0;
		while(1) {
			queue<int> q;
			memcpy(cur,head,sizeof(head));
			memset(dis,-1,sizeof(dis));
			q.push(s),dis[s]=0;
			while(!q.empty()) {
				int t=q.front();
				q.pop();
				for(int i=head[t]; i; i=nxt[i])
					if(dis[ver[i]]==-1&&limit[i])
						dis[ver[i]]=dis[t]+1,q.push(ver[i]);
			}
			if(dis[t]==-1) return flow;
			flow+=dfs(s,inf);
		}
	}
	void clear() {
		tot=1; memset(head,0,sizeof head);
	}
} g;
int n,m,k;
struct edge {
	int x,y,z;
} e[M];
bool valid(int w) {
	g.clear(); 
	for(int i=1; i<=m; i++) {
		if(e[i].z<=w) g.add(e[i].x,e[i].y,1);
	}
	int s=n+1; g.add(s,1,k);
	if(g.maxflow(s,n)>=k) return true;
	return false;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=m; i++) {
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	}
	int l=1,r=inf,ans=inf;
	for(; l<=r; ) {
		int mid=1ll*(l+r)/2;
		if(valid(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

