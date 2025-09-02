# [CCC 2023 S4] Minimum Cost Roads

## 题目描述

As the newly elected mayor of Kitchener, Alanna's first job is to improve the city's road plan.

Kitchener's current road plan can be represented as a collection of $N$ intersections with $M$ roads, where the $i\text{-th}$ road has length $l_i$ meters, costs $c_i$ dollars per year to maintain, and connects intersections $u_i$ and $v_i$. To create a plan, Alanna must select some subset of the $M$ roads to keep and maintain, and that plan's cost is the sum of maintenance costs of all roads in that subset.

To lower the city's annual spending, Alanna would like to minimize the plan's cost. However, the city also requires that she minimizes travel distances between intersections and will reject any plan that does not conform to those rules. Formally, for any pair of intersections $(i, j)$, if there exists a path from $i$ to $j$ taking $l$ meters on the existing road plan, Alanna's plan must also include a path between those intersections that is at most $l$ meters.

## 说明/提示

Explanation of Output for Sample Input：

Here is a diagram of the intersections along with a valid road plan with minimum cost.

![](https://cdn.luogu.com.cn/upload/image_hosting/2astpvkm.png)

Each edge is labeled with a pair $(l, c)$ denoting that it has length $l$ meters and cost $c$ dollars.

Additionally, the roads that are part of the plan are highlighted in blue, with a total cost of $7 + 1 + 6 + 7 + 4 = 25$.

It can be shown that we cannot create a cheaper plan that also respects the city’s requirements.

**本题采用捆绑测试**：

- Subtask 1（3 points）：数据保证 $1\leq N \leq 2000$，$1\leq M \leq 2000$，$l_i = 0$，$1\leq c_i \leq 10^9$。

- Subtask 2（6 points）：数据保证 $1\leq N\leq 2000$，$1\leq M \leq 2000$，$1\leq l_i \leq 10^9$，$1\leq c_i \leq 10^9$，且在任何一对十字路口之间最多只有一条路。

- Subtask 3（6 points）：数据保证 $1\leq N\leq 2000$，$1\leq M \leq 2000$，$0\leq l_i \leq 10^9$，$1\leq c_i \leq 10^9$。

## 样例 #1

### 输入

```
5 7
1 2 15 1
2 4 9 9
5 2 5 6
4 5 4 4
4 3 3 7
1 3 2 7
1 4 2 1```

### 输出

```
25```

# 题解

## 作者：wgyhm (赞：9)

考虑不存在重边的情况。

对于一对起点和终点 $s,t$，如果 $s,t$ 中只有一条最短路径，那么是肯定要选的。

否则，令 $s,t$ 的一条当前最优最短路径的边集为 $p_1,p_2,\dots,p_k$，观察到如果存在一条边 $p_i$，令其两个端点为 $a,b$，$a,b$ 之前存在另外一条长度相同的最短路径，则替换。这样的操作次数是有限的。最后，每条边 $p_i$ 都是两个端点之间的最短路径。显然这样的边是一定要取的。

抛开重边的情况来看，这道题的其实并不太是像最小化题目，选哪些边是确定的。

有重边判一下就好。

具体实现上，第一关键字为长度，第二关键字为价值升序排序。这样保证最先选到的是两个端点之间的最短路径。如果这两个点不连通则直接加入这条边，否则判断当前的最短路如果大于这条边的长度则加入（等于没有加入的必要，上一段说明了这一点）。

复杂度 $O(nm\log m)$。因为如果加入这条边之前不连通并不跑最短路，所以跑的会比期望的快一点。

Update：好像做法很多，排序的方式也很多。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define maxn 2005
#define put() putchar('\n')
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
using namespace std;
void read(int &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,Ty x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,vector<Ty>& V){os<<"[";for(auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
priority_queue<pair<int,int> >q;
struct yyy {
	int x,y,l,c;
}a[maxn];
int fa[maxn],ans,vis[maxn],dis[maxn],n,m;
int getfa(int x) {return x==fa[x]?x:fa[x]=getfa(fa[x]);}
bool cmp(yyy x,yyy y) {return x.l==y.l?x.c<y.c:x.l<y.l;}
vector<pair<int,int> >to[maxn];
const int inf=1e12;
bool check(int s,int t,int d) {
	int i,x;
	for (i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
	while (!q.empty()) q.pop();
	q.push(mk(-(dis[s]=0),s));
	while (!q.empty()) {
		int x=q.top().se;q.pop();
		if (vis[x]) continue;vis[x]=1;
		for (auto tmp:to[x]) if (!vis[tmp.fi]&&dis[tmp.fi]>dis[x]+tmp.se) {
			dis[tmp.fi]=dis[x]+tmp.se;
			q.push(mk(-dis[tmp.fi],tmp.fi));
		}
	}
	return d<dis[t];
}
signed main(void){
	int i;
	read(n);read(m);
	for (i=1;i<=m;i++) {
		read(a[i].x),read(a[i].y),read(a[i].l),read(a[i].c);
	}
	for (i=1;i<=n;i++) fa[i]=i;
	sort(a+1,a+1+m,cmp);
	for (i=1;i<=m;i++) {
		auto tmp=a[i];
		if (getfa(tmp.x)^getfa(tmp.y)) {
			fa[getfa(tmp.x)]=getfa(tmp.y);
			ans+=tmp.c;
			to[a[i].x].push_back(mk(a[i].y,a[i].l));
			to[a[i].y].push_back(mk(a[i].x,a[i].l));
		}
		else if (check(tmp.x,tmp.y,tmp.l)) {
			ans+=tmp.c;
			to[a[i].x].push_back(mk(a[i].y,a[i].l));
			to[a[i].y].push_back(mk(a[i].x,a[i].l));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：船酱魔王 (赞：3)

## 题意回顾

$ n $ 点 $ m $ 边无向图，边带权和维护代价，保留最少代价和的边使得最短路矩阵不变。

$ 1 \le n,m \le 2 \times 10^3 $

## 分析

考虑类似于最小生成树的思想，边按照权值为第一关键字/代价为第二关键字从小到大排序，如果一条边加入之后两个端点的最短路不变短那么不需要加入，否则加入。时间复杂度为 $ O(m^2 \log m) $，瓶颈在于 dijkstra 算法求解最短路。

证明：考虑加入边的过程：
* 若端点 $ u,v $ 之间最短路长度不超过边长 $  l $ 时，如果一条最短路涉及这条边，那么必然可以将这条边替换成 $ u,v $ 之间排除掉这条边的最短路，不加入这条边的话最短路径矩阵是不劣于加入的，因此为了节约成本不予加入。
* 若端点 $ u,v $ 之间最短路长度超过边长 $ l $ 时，后面加入的边边长必然不小于 $ l $，若 $ l > 0 $ 时，后面与这条边不重合的边（因为如果是重边的话必然代价小的在前，所以只用考虑第一条就行）参与构成的 $ u,v $ 之间的最短路径长度不小于 $ 2l>l $，所以最短路矩阵不是最优的，因此必须加入。
* 若 $ l=0 $ 时，可以发现该问题类似于最小生成树（因为 $ l=0 $ 的边最先加入），$ p $ 从小到大排序后，这个算法等同于 kruskal 算法的流程，是正确的。

据此，不难写出本题的解法代码。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
const int N = 2005;
const int inf = 1e9 + 5;
int n, m;
struct node {
    int u, v, l, p;
    bool operator<(node p2) {
        if(l != p2.l) return l < p2.l;
        return p < p2.p;
    }
} a[N];
vector<pair<int, int> > g[N];
int dis[N];
int vis[N];
priority_queue<pair<int, int> > pq;
int length(int x, int y) {
    for(int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    dis[x] = 0;
    pq.push((pair<int, int>){0, x});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if(vis[u]) continue;
        int v;
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first;
            int w = g[u][i].second;
            if(dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push((pair<int, int>){-dis[v], v});
            }
        }
    }
    return dis[y];
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].l >> a[i].p;
    }
    sort(a + 1, a + m + 1);
    int u, v, l, p;
    long long ans = 0;
    for(int i = 1; i <= m; i++) {
        u = a[i].u, v = a[i].v, l = a[i].l, p = a[i].p;
        if(length(u, v) > l) ans += p, g[u].push_back((pair<int, int>){v, l}),
            g[v].push_back((pair<int, int>){u, l});
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：leiaxiwo (赞：2)

# 洛谷 P9327
## 一道进阶的图论题
### 题目分析
显然这个题是一道图论题，题目给了一张大图，我们要在大图中维护一个小图，使得大图只保留这些边后任意两点间的最短路长度不变同时费用和最小。
### 情况 1
如果两个点只有唯一的最短路，那么显然要保留这条路。

对于 Subtask 1 $l_i=0$，那么显然我们只用求最短路，选择 $c_i$ 最小的路径，这题退化为一道最小生成树。
### 情况 2

对于 Subtask 2 在任何一对十字路口之间最多只有一条路，这句话翻译一下就是考虑整体对待十字路口求解，但是仍然只有部分分。

### 情况 3（正解）
这是一道有重边的题，我们先想办法处理重边，显然我们可以仿照 tarjan 的办法，对边上进行 `xor` 运算，若值为 $1$ 则说明我们需要特殊处理。

我们可以令端点 $x \to y$ 之间有最优的边集为 $p$，显然对于边集中的单个边 $p_i$ 不妨令其端点为 $u \to v$，我们删掉这条边，再跑一遍 $u \to v$ 的最短路，若最短路值不变或更小则说明这么改变是可取的。

具体的，我们可以把价值排序，显然我们取价值最大的删去就是最优解。若两个点不联通我们考虑直接加入边（显然我们不可能让这个图不联通），若两个点有多个联通的边则说明我们需要删去价值最大的那个边，然后按上述方法处理，总复杂度为:

$$O(m \times n \times \log m + m \times \log m)$$

### 参考代码

```cpp
//-std=c++14 
#include<bits/stdc++.h>
#define int long long//十年oi一场空，不开long long见祖宗 
using namespace std;
int n,m,father[500005],dis[500005],vis[500005],ans;//宏定义，学过图论应该都看得懂在干什么 
const int inf=1e12;
vector<pair<int,int> > to[500005];//边集 
priority_queue<pair<int,int> > q;//堆优化 
struct edge{
	int x,y,l,c;
}e[500005];//链式前向星存图，也可vector 
int cmp(edge x,edge y){//升序排序cmp，当然也可降序，不过需要取出末位 
	return x.l==y.l?x.c<y.c:x.l<y.l;
}
int find(int x){ 
	return x==father[x]?x:father[x]=find(father[x]);
}
bool query(int x,int y,int z){//判断情况2 
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	while(!q.empty()){
		q.pop();
	}
	q.push(make_pair(-(dis[x]=0),x));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]){
			continue;
		}
		vis[x]=1;
		for(auto it:to[x]){
			if(!vis[it.first]&&dis[it.first]>dis[x]+it.second){
				dis[it.first]=dis[x]+it.second;
				q.push(make_pair(-dis[it.first],it.first));
			}
		}
	}
	return z<dis[y];//求出的最短路是否小于初始的最短路 
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
    	scanf("%lld%lld%lld%lld",&e[i].x,&e[i].y,&e[i].l,&e[i].c);
	}
	for(int i=1;i<=n;i++){
		father[i]=i;
	}
	sort(e+1,e+m+1,cmp);//快速排序，在ccf老爷机上面跑可能需要稳定版的 
	for(int i=1;i<=m;i++){
		auto it=e[i];
		if(find(it.x)^find(it.y)){//判断重边 
			father[find(it.x)]=find(it.y);
			ans+=it.c;//只有一条就直接加入 
			to[e[i].x].push_back(make_pair(e[i].y,e[i].l));
			to[e[i].y].push_back(make_pair(e[i].x,e[i].l));
		}
		else if(query(it.x,it.y,it.l)){//否则找到他们中较小的那个 
			ans+=it.c;
			to[e[i].x].push_back(make_pair(e[i].y,e[i].l));
			to[e[i].y].push_back(make_pair(e[i].x,e[i].l));
		}
	}
	printf("%lld\n",ans);//完结撒花 
	return 0;
} 
```

---

## 作者：2345678qwer (赞：2)

蒟蒻的第一篇题解。思路来源：leiaxiwo。

一道图论题，给了一张图，我们要在大图中维护一个小图，大图只保留这些边后任意两点间的最短路长度不变同时费用和最小。

这是一道有重边的题，我们先想办法处理重边，显然我们可以仿照 tarjan 的办法，对边上进行异或运算，若值为 1 则说明需要特殊处理。我们可以令 $x→y$ 之间有最优的集为 $p$，对于边集中的单个边 $p _ {i}$ 令其端点为 $u→v$ 我们删掉这条边。

 $u→v$ 的最短路，若最短路值不变或更小则说明这么改变可取。

我们可以把价值排序，我们取价值最大的删去就是最优解。若两个点不联通我们直接加入边，两个点有多个联通的边，我们需要删去价值最大的那个边，然后按上述方法处理。



```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node {
    int u, v, l, p;
    bool operator<(node p2) {
        if(l != p2.l) return l < p2.l;
        return p < p2.p;
    }
} a[2004];
vector<pair<int, int> > g[3242];
int dis[3252];
int vis[3252];
priority_queue<pair<int, int> > pq;
int length(int x, int y) {
    for(int i = 1; i <= n; i++) dis[i] = 1e9+3, vis[i] = 0;
    dis[x] = 0;
    pq.push((pair<int, int>){0, x});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if(vis[u]) continue;
        int v;
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first;
            int w = g[u][i].second;
            if(dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push((pair<int, int>){-dis[v], v});
            }
        }
    }
    return dis[y];
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].l >> a[i].p;
    }
    sort(a + 1, a + m + 1);
    int u, v, l, p;
    long long ans = 0;
    for(int i = 1; i <= m; i++) {
        u = a[i].u, v = a[i].v, l = a[i].l, p = a[i].p;
        if(length(u, v) > l) ans += p, g[u].push_back((pair<int, int>){v, l}),
            g[v].push_back((pair<int, int>){u, l});
    }
    cout << ans << endl;
    return 0;
}

```
点个赞吧。

---

## 作者：BeTheNorthStar (赞：1)

一道思维含量比较高的图论题。\
首先，我们要明白一个东西：题目要求最先保证的是**两点之间的最短路径**，然后是最小维护费用。\
所以我们要在**满足最短路不变**的情况下维护一个类似于最小生成树的图。那么可以借助于 Kruskal 的思想来解这道题目。但是，我们需要把最短路作为一个是否建边的条件来进行考虑：\
首先，我们得把所有边按长度进行排序，因为我们需要**满足最短路**。\
然后，判断这两个点是否在一个连通块里面。\
1.如果不在一个连通块里面，那么把这条边连上就是最短路，因为我们把边权按从小到大排过序。\
2.如果已经在一个连通块里面，那么我们要刷这两个点还没加上这条边的最短路径。
 - 如果原来的最短路小，那么肯定不加这条边。
 - 如果原来的最短路没有这条边小，那么这条边必须得加，因为首先**满足最短路**。


---

最后累加答案即可。\
判断图连通最好的办法是什么？当然是**并查集**啊。\
对于这道题目的，我们既可以使用 SPFA，也可以刷 Dijkstra。

1.SPFA
```cpp
bool SPFA(int s,int t,int len){
	memset(dis,63,sizeof dis);
	memset(vis,0,sizeof vis);
	int hed=0,til=1;
	vis[Que[1]=s]=1,dis[s]=0;
	while(hed!=til){
		hed=(hed+1)%maxn;vis[Que[hed]]=0;
		for(int j=lnk[Que[hed]];j;j=e[j].nxt){
			if(dis[Que[hed]]+e[j].w>=dis[e[j].to]) continue;
			dis[e[j].to]=dis[Que[hed]]+e[j].w;
			if (!vis[e[j].to]) vis[e[j].to]=1,til=(til+1)%maxn,Que[til]=e[j].to;
		}
	}return len<dis[t];
}
```
2.Dijkstra(使用堆进行优化)
```cpp
bool DIJ_HEAP(int sx,int sy,int Road){
	memset(dis,127,sizeof dis);memset(vis,0,sizeof vis);
	hep_size=0,put(dis[sx]=0,sx);
	while(hep_size){
		BNS now=get();
		if(vis[now.id]) continue; if(now.id==sy) break;
		vis[now.id]=1;
		for(int j=lnk[now.id];j;j=e[j].nxt)
		  if(dis[now.id]+e[j].w<dis[e[j].to]) put(dis[e[j].to]=dis[now.id]+e[j].w,e[j].to);
	}return Road<dis[sy];
}
```
主要考的就是图论的综合运用，多几个思考总会出结果的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2005,maxe=4005;
int n,m,lnk[maxn],tot,dis[maxn],vis[maxn],hep_size,fa[maxn],ans;
struct edge{
	int to,nxt,w;//邻接表存图
}e[maxe];
struct BNS{
	int x,id;
	bool operator<(const BNS &B)const{return x<B.x;}
}hep[maxn];
struct EDGE{
	int x,y,l,c;
	bool operator<(const EDGE &B)const{return l<B.l||(l==B.l&&c<B.c);}
}a[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f^=!(ch^'-'),ch=getchar();
	while( isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	if(!f) ret=-ret; return ret;
}
void add_e(int x,int y,int z){e[++tot]=(edge){y,lnk[x],z},lnk[x]=tot;}//建边
int Get(int x){return fa[x]==x?fa[x]:fa[x]=Get(fa[x]);}//并查集找祖先
void put(int x,int id){//把数据推入堆中
	hep[++hep_size]=(BNS){x,id};int son=hep_size;
	while(son>1&&hep[son]<hep[son>>1]) swap(hep[son],hep[son>>1]),son>>=1;
}
BNS get(){//获取堆顶
	BNS now=hep[1];int fa=1,son;hep[1]=hep[hep_size--];
	while((fa<<1)<=hep_size){
		if((fa<<1|1)>hep_size||hep[fa<<1]<hep[fa<<1|1]) son=fa<<1; else son=fa<<1|1;
		if(hep[son]<hep[fa]) swap(hep[son],hep[fa]),fa=son; else break;
	}return now;
}
bool DIJ_HEAP(int sx,int sy,int Road){//刷最短路
	memset(dis,127,sizeof dis);memset(vis,0,sizeof vis);
	hep_size=0,put(dis[sx]=0,sx);
	while(hep_size){
		BNS now=get();
		if(vis[now.id]) continue; if(now.id==sy) break;
		vis[now.id]=1;
		for(int j=lnk[now.id];j;j=e[j].nxt)
		  if(dis[now.id]+e[j].w<dis[e[j].to]) put(dis[e[j].to]=dis[now.id]+e[j].w,e[j].to);
	}return Road<dis[sy];
}
signed main(){
//	freopen("roads.in","r",stdin);
//	freopen("roads.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) a[i]=(EDGE){read(),read(),read(),read()};
	sort(a+1,a+1+m);
	for(int i=1;i<=m;i++){
		int fx=Get(a[i].x),fy=Get(a[i].y);
		if(fx!=fy) fa[fx]=fy,ans+=a[i].c,add_e(a[i].x,a[i].y,a[i].l),add_e(a[i].y,a[i].x,a[i].l);else
		if(DIJ_HEAP(a[i].x,a[i].y,a[i].l)) ans+=a[i].c,add_e(a[i].x,a[i].y,a[i].l),add_e(a[i].y,a[i].x,a[i].l);
	}printf("%lld\n",ans);
	return 0;
}
```

---

