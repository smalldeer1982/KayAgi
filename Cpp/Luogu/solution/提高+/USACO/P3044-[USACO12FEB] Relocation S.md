# [USACO12FEB] Relocation S

## 题目描述

Farmer John is moving!  He is trying to find the best place to build a new farm so as to minimize the amount of travel he needs to do each day.

The region to which FJ plans to move has N towns (1 <= N <= 10,000).  There are M bi-directional roads (1 <= M <= 50,000) connecting certain pairs of towns.  All towns are reachable from each-other via some combination of roads.  FJ needs your help selecting the best town as the home for his new farm.

There are markets in K of the towns (1 <= K <= 5) that FJ wants to visit every day.  In particular, every day he plans to leave his new farm, visit the K towns with markets, and then return to his farm.  FJ can visit the markets in any order he wishes.  When selecting a town in which to build his new farm, FJ wants to choose only from the N-K towns that do not have markets, since housing prices are lower in those towns.

Please help FJ compute the minimum distance he will need to travel during his daily schedule, if he builds his farm in an optimal location and chooses his travel schedule to the markets as smartly as possible.

FJ决定搬家，重新建设农场，以便最小化他每天的行程。


FJ搬往的区域有N(1 <= N <= 10,000)个城镇，共有M (1 <= M <= 50,000)条双向道路连接某些城镇，所有城镇都能找到互通路线。


有K (1 <= K <= 5)个城镇建有市场，FJ每天离开新农场后，都要光顾这K个城镇，并返回农场。FJ希望建设农场的城镇不包含市场。


请帮助FJ选择最佳城镇建设农场，使得他每天的行程最小。


## 说明/提示

There are 5 towns, with towns 1, 2, and 3 having markets.  There are 6 roads.


FJ builds his farm in town 5.  His daily schedule takes him through towns 5-1-2-3-2-1-5, for a total distance of 12.


## 样例 #1

### 输入

```
5 6 3 
1 
2 
3 
1 2 1 
1 5 2 
3 2 3 
3 4 5 
4 2 7 
4 5 10 
```

### 输出

```
12 
```

# 题解

## 作者：sxd666888 (赞：9)

##  最短路+状压dp

由于我们看到他的k很小（1<=k<=5）就想到了~~爆搜~~状压

我们肯定要知道k个城镇与每个点之间的距离，最短路就跑k遍；

枚举选的农场，开始状压；

至于状压：

    	f [当前状态为i (二进制中，1表示走过)]  [当前所在的城镇为j]
        
        = f[i^(1<<(j-1))][p] + dis[p][j] (p为之前所在的城镇)
        
        
        初始时：f[1<<(k-1)][k] = dis[k][s](s为选的农场，k为第一个经过的城镇)
        
        
        最后枚举最后所在的城镇，加上他到选的农场的距离，取最小值；
        

具体见代码，大佬勿喷qwq。。。

```cpp
#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,wz[6];
long long tot,head[10005],nx[100005],to[100005],w[100005];
long long dis[6][10005],vis[10005],f[2005][6];
void jia(long long aa,long long bb,long long cc)
{
	tot++;
	nx[tot]=head[aa];
	to[tot]=bb;
	w[tot]=cc;
	head[aa]=tot;
	return;
}
struct node
{
	long long id,val;
};
bool operator <(node aa,node bb)
{
	return aa.val>bb.val;
}
node bh(long long aa,long long bb)
{
	node tt;
	tt.id=aa;
	tt.val=bb;
	return tt;
}
void spfa(long long rt)//其实是dijkstra。。。
{
	priority_queue<node>q;
	q.push(bh(wz[rt],0));
	memset(vis,0,sizeof(vis));
	dis[rt][wz[rt]]=0;
	while(!q.empty())
	{
		node kk=q.top();
		q.pop();
		if(vis[kk.id]) continue;
		vis[kk.id]=1;
		for(long long i=head[kk.id];i;i=nx[i])
		{
			long long yy=to[i];
			if(dis[rt][yy]>dis[rt][kk.id]+w[i])
			{
				dis[rt][yy]=dis[rt][kk.id]+w[i];
				q.push(bh(yy,dis[rt][yy]));
			}
		}
	}
}
int main()
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	scanf("%lld%lld%lld",&n,&m,&k);
	for(long long i=1;i<=k;++i)
	{
		scanf("%lld",&wz[i]);
	}
	for(long long i=1;i<=m;++i)
	{
		long long x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		jia(x,y,z);
		jia(y,x,z);
	}
	for(long long i=1;i<=k;++i)
	{
		spfa(i);//预处理k个城镇到各点的距离
	}
	long long ans=0x3f3f3f3f;
	for(long long i=1;i<=n;++i)//枚举选的农场
	{
		long long flag=0;
		for(long long j=1;j<=k;++j) if(i==wz[j]) {flag=1;break;}
		if(flag) continue;//城镇不能选，不是吗？
		memset(f,0x3f3f3f,sizeof(f));
		for(long long j=1;j<=k;++j)
		{
			f[1<<(j-1)][j]=dis[j][i];//见上初始时
		}
		for(long long j=1;j<(1<<k);++j)
		{
			for(long long pp=1;pp<=k;++pp)//枚举当前所在的城镇
			if(j&(1<<(pp-1)))
			{
				for(long long qq=1;qq<=k;++qq)//枚举之前所在的城镇
				if(pp!=qq&&(j&(1<<(qq-1))))
				{
					f[j][pp]=min(f[j][pp],f[j^(1<<(pp-1))][qq]+dis[qq][wz[pp]]);//转移
				}
			}
		}
		for(long long j=1;j<=k;++j)//枚举最后所在的城镇
		{
			ans=min(ans,f[(1<<k)-1][j]+dis[j][i]);//取最小值
		}
	}
	printf("%lld",ans);
	return 0;
}
```
完结撒花。。。

---

## 作者：guoshaoyang (赞：5)

# 单源最短路径+全排列爆搜


**不会dijkstra的同志们，先AC单源最短路径再来做这道题，谢谢**

这题的思路很简单，先从每个市场出发求出最短路径，再枚举所有出发点，从这些出发点爆搜所有路劲，求出最小值即可。
    
问题的关键就在这爆搜上，楼上用的状压本蒟蒻不会，于是就想到了全排列经过所有集市的顺序，代码简单而且效率绰绰有余
    
    AC代码如下供参考：
```c
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int MAXK=8,MAXN=1024*10,INF=1024*1024*1024;
struct edge{
	int index,len;
	edge(int x,int y){
		index=x;
		len=y;
	}
	friend bool operator<(edge x,edge y){
		return x.len>y.len;
	}
};
int N,M,K,market[MAXK],dis[MAXK][MAXN],b[MAXN],ans=INF,order[MAXK];
vector<edge> a[MAXN];
priority_queue<edge> que;
inline void dijkstra(int x){
	memset(b,0,sizeof(b));
	while(!que.empty()){
		que.pop();
	}
	dis[x][market[x]]=0;
	que.push(edge(market[x],0));
	while(!que.empty()){
		int ii=que.top().index,jj=que.top().len;
		que.pop();
		if(b[ii]){
			continue;
		}
		b[ii]=1;
		for(unsigned int i=0;i<a[ii].size();i++){
			if(jj+a[ii][i].len<dis[x][a[ii][i].index]){
				dis[x][a[ii][i].index]=jj+a[ii][i].len;
				que.push(edge(a[ii][i].index,dis[x][a[ii][i].index]));
			}
		}
	}
}
inline int choice(int x){
	for(int i=1;i<=K;i++){
		if(x==market[i]) return INF;
		order[i]=i;
	}
	int minv=INF;
	do{
		int tot=dis[order[1]][x]+dis[order[K]][x];
		for(int i=1;i<=K-1;i++){
			tot+=dis[order[i]][market[order[i+1]]];
		}
		minv=min(minv,tot);
	}while(next_permutation(order+1,order+K+1));
	return minv;
}
int main(){
	cin >> N >> M >> K;
	for(int i=1;i<=K;i++){
		cin >> market[i];
	}
	for(int i=0;i<=K;i++){
		for(int j=0;j<=N;j++){
			dis[i][j]=INF;
		}
	}
	for(int i=1;i<=M;i++){
		int ii,jj,kk;
		cin >> ii >> jj >> kk;
		a[ii].push_back(edge(jj,kk));
		a[jj].push_back(edge(ii,kk)); 
	}
	for(int i=1;i<=K;i++){
		dijkstra(i);
	}
	for(int i=1;i<=N;i++){
		ans=min(ans,choice(i));
	}
	cout << ans;
	return 0;
}
```

---

## 作者：tribool4_in (赞：4)

神奇的最短路 + 暴力题

题意：有一张图，你需要找到一个点，使得从该点出发，按一定顺序经过给定的 $k$ 个点，路径长度最短。

首先看到 $k \le 5$，显然可以暴力。考虑枚举出发点，全排列枚举经过这 $k$ 个点的顺序，然后计算出路径长度取最小值即可。

接下来就要考虑如何快速计算要求的路径长度。全源最短路 Floyd 显然不行，$n^3$ 当场爆炸。考虑单源最短路，由于路径一定经过 $k$ 个市场，且 $k$ 极小，可以对这 $k$ 个点跑单源最短路，即可计算长度。

时间复杂度：$O(5n\log n+nk!k)$，可以轻松过。

顺便扯一下 STL 全排列 —— `next_permutation` & `pre_permutation`。

具体用法：

对于一个长度为 $n$ 的数组 a ，调用 `next_permutation(a, a+n)` 可以得到数组 a 的下一个排列，调用 `pre_permutation(a, a+n)` 可以得到上一个全排列。

一旦排列到达最大字典序，比如 $\{4,3,2,1\}$ ，就返回 False，同时重新设置该排列为最小字典序，否则返回 True。

注意到此函数的参数与 sort 一样，这也正是 STL 的统一的特点的体现（）。

代码：

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int N = 1e5 + 10;
struct node {
	int v, w;
	node(int v, int w):v(v), w(w) {}
};
int n, m, k;
int mark[10]; bool ism[N];
vector<node> G[N];
bool vis[N];
int d[10][N];
void spdij(int s, int id) {
	priority_queue<pii, vector<pii>, greater<pii> > q;
	memset(vis, 0, sizeof(vis));
	memset(d[id], 0x3f, sizeof(d[id]));
	q.push(make_pair(0, s)); vis[s] = 1; d[id][s] = 0;
	while (!q.empty()) {
		int now = q.top().second; q.pop(); vis[now] = 0;
		for (int i = 0; i < G[now].size(); i++) {
			int v = G[now][i].v;
			if (d[id][v] > d[id][now] + G[now][i].w) {
				d[id][v] = d[id][now] + G[now][i].w;
				if (!vis[v]) {
					q.push(make_pair(d[id][v], v)); vis[v] = 1;
				}
			}
		}
	}
}
int a[N];
void init() {
	for (int i = 1; i <= k; i++) a[i] = i;
}
int main() {
	freopen("relocate.in", "r", stdin);
	freopen("relocate.out", "w", stdout);
//	freopen("10.in", "r", stdin);
//	freopen("relocate.out", "w", stdout);
	n = read(), m = read(), k = read();
	for (int i = 1; i <= k; i++) mark[i] = read(), ism[mark[i]] = 1;
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		G[u].push_back(node(v, w));
		G[v].push_back(node(u, w));
	}
	for (int i = 1; i <= k; i++) spdij(mark[i], i);
	int minn = 0x7fffffff;
	for (int i = 1; i <= n; i++) {
		if (ism[i]) continue;
		init();
		do {
			int res = d[a[1]][i];
			for (int i = 1; i < k; i++) {
				res += d[a[i]][mark[a[i + 1]]];
			}
			res += d[a[k]][i];
			minn = min(minn, res);
		} while (next_permutation(a + 1, a + k + 1));
	}
	printf("%d\n", minn);
	return 0;
}
```

---

## 作者：swl3992 (赞：2)

首先枚举要选的农场是哪个。

然后由于去集市的顺序不知道，所以用 dfs 搜索所有顺序（使用 STL 的 next_permutation 也可以）。

由于要行程最小，所以要求从农场到集市最短路径。

由于 $n$ 过大， floyd 显然不行。

那么可以分成

1. 农场到集市 1 的最短路线。

1. 集市 1 到集市 2 的最短路线。

1. 集市 2 到集市 3 的最短路线。

……

k + 1. 集市 $k$ 到农场的最短路线

观察以上，**只需要知道每个集市到每个点的最短路分别是多少即可** ，而且 $k$ 很小。

于是只要以每个集市为起点跑 Dijkstra 就可以了。

最后统计一下求最小值即可。

示例代码：

```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
struct edge
{
    int from,to,dist;
};
struct node
{
    int d,u;
    bool operator <(const node &nd) const
    {
        return d>nd.d;
    }
};
vector<edge> edges;
vector<int> G[10005];
struct d
{
    int n,m;
    bool vis[10005];
    int d[8][10005];	//第一维表示集市的编号，第二维表示到哪个点，值为最短路
    void init(int n)
    {
    	n++;
        this->n=n;
        for(int i=0;i<n;i++)
        {
            G[i].clear();
        }
        edges.clear();
    }
    void add(int f,int t,int dist)
    {
        edges.push_back(edge{f,t,dist});
        m=edges.size();
        G[f].push_back(m-1);
    }
    void di(int s,int id)	//起点（原题目中的结点号），这个集市的编号
    {
        priority_queue<node> q;
        for(int i=0;i<n;i++)
        {
            d[id][i]=1000000000;
        }
        d[id][s]=0;
        memset(vis,0,sizeof(vis));
        q.push(node{0,s});
        while(!q.empty())
        {
            node f=q.top();
            q.pop();
            int u=f.u;
            if(vis[u])
            {
                continue;
            }
            vis[u]=true;
            for(int i=0;i<G[u].size();i++)
            {
                edge& e=edges[G[u][i]];
                if(d[id][e.to]>d[id][u]+e.dist)
                {
                    d[id][e.to]=d[id][u]+e.dist;
                    q.push(node{d[id][e.to],e.to});
                }
            }
        }
    }
};
d ob;
//以上为 Dijkstra 模板
int market[10005];	//对集市做一个映射，market[i] 表示集市 i (即原题目中的结点号)的编号是多少
int markets[8];	//markets[i] 表示编号为 i 的集市在原题目中的结点号是什么

//以下代码中“集市的编号”为映射后的编号，即 market 中的


void read(int &x)
{
	int num=0,f=1;
	char c;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		num=(num<<3)+(num<<1)+(c^48);
		c=getchar();
	}
	x=f*num;
}
void print(int x)
{
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	if(x>=10)
	{
		print(x/10);
	}
	putchar(x%10+'0');
}
//以上为快读，可以不加
int n,m,k;
int ans=2147483647;
bool vis[8];
int mar[8];
void count_()
{
	int cur=0;
	for(int i=0;i<k-1;i++)	//每个集市到集市
	{
		cur+=ob.d[mar[i]][markets[mar[i+1]]];
	}
	for(int i=1;i<=n;i++)
	{
		if(market[i]==-1)	//这不是集市
		{
			ans=min(ans,cur+ob.d[mar[0]][i]+ob.d[mar[k-1]][i]);	//开头和结尾
		}
	}
}
void dfs(int cur)
{
	if(cur==k)
	{
		count_();
		return;
	}
	for(int i=0;i<k;i++)
	{
		if(vis[i])
		{
			continue;
		}
		mar[cur]=i;	//第 cur 个是编号为 i 的集市，注意是编号
		vis[i]=true;
		dfs(cur+1);
		vis[i]=false;
	}
}
int main()
{
	//ios::sync_with_stdio(0);
	read(n);
	read(m);
	read(k);
	ob.init(n);
//	cout<<ob.n<<endl;
	memset(market,-1,sizeof(market));	//初始化为 -1 ,读入完成后值为 -1 则为这不是集市
	for(int i=0;i<k;i++)
	{
		int a;
		read(a);
		markets[i]=a;
		market[a]=i;
	}
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		read(a);
		read(b);
		read(c);
		ob.add(a,b,c);
		ob.add(b,a,c);
	}
	for(int i=0;i<k;i++)
	{
		ob.di(markets[i],i);	//求各个集市到每个点最短路分别是多少
	}
	dfs(0);	//dfs 遍历顺序
	print(ans);
	return 0;
}
```



---

## 作者：45dino (赞：2)

写了很久……
感觉要求多源最短路径，但复杂度为 $O(n^3)$ ，明显![](https://cdn.luogu.com.cn/upload/image_hosting/51d80tin.png)

然后发现 $k\leq 5$ ，而求两个非集市的点的最短路径毫无意义，所以只用以所有集市为起点做单源最短路径。~~说白了就是不TLE~~

复杂度为 $O(k\times (n+m)log_2 n)$ 。

因为这是一个无向图，所以同时求出了所有点到集市的最短路。

最后一点处理，可以用状压DP，也可以用全排列，这里用的是全排列~~因为好写~~

在写的时候，有以下几点要注意：
- 最短路模板不要写错
- 最后处理时注意一些细节
- 因为是求最小值，答案初始值要设的较大。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int to,next,val;
} edge[100001];//存边
struct que{
	int to,val;
	bool operator<(const que &x)const
	{
		return x.val<val;
	}
};
int n,m,k,ans=1e10/*要设初值*/,cnt,a[7],head[10001],st[6],vis[10001],dis[10001][6];//a代表k个集市的顺序，st代表集市的编号对应的小镇，id代表小镇对应的集市编号。
int id[10001];
void add(int x,int y,int w)
{
	edge[++cnt].to=y;
	edge[cnt].val=w;
	edge[cnt].next=head[x];
	head[x]=cnt;
}//存边
/*===============最短路==============*/
void dij(int x)
{
	priority_queue<que> q;
	for(int i=1;i<=n;i++)
		dis[i][x]=1e9;
	dis[st[x]][x]=0;
	q.push((que){st[x],0});
	while(!q.empty())
	{
		que t=q.top();
		q.pop();
		if(t.val!=dis[t.to][x])
			continue;
		for(int i=head[t.to];i;i=edge[i].next)
		{
			int to=edge[i].to;
			if(dis[to][x]>dis[t.to][x]+edge[i].val)
			{
				dis[to][x]=dis[t.to][x]+edge[i].val;
				q.push((que){to,dis[to][x]});
			}
		}
	}
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=k;i++)
		scanf("%lld",&st[i]);
	sort(st+1,st+1+k);
	for(int i=1;i<=k;i++)
		id[st[i]]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=k;i++)
		dij(i);
	for(int i=1;i<=n;i++)//最后的全排列
	{
		if(id[i])
			continue;
		for(int l=1;l<=k;l++)
			a[l]=st[l];
		do{
			int tot=0;//此处记得清0
			for(int l=1;l<k;l++)
				tot+=dis[a[l+1]][id[a[l]]];
			tot+=dis[i][id[a[1]]]+dis[i][id[a[k]]];//容易错
			ans=min(ans,tot);
		}while(next_permutation(a+1,a+1+k));//全排列函数
	}
	cout<<ans;
	return 0;
}
```
感觉挺长的，但自己写的时间其实不对，主要都在调错。
~~感觉抄都抄不下去~~

---

## 作者：ModestCoder_ (赞：2)

突破口就是这个$k<=5$

可以以每个市场为源点，跑最多5次$dijkstra$，时间复杂度$O(knlogn)$

然后对$k$个市场进行全排列，枚举农场，计算一次距离，时间复杂度$O(nk!)$

总时间复杂度$O(knlogn+nk!)$

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
struct Edge{
	int to, next, len;
}edge[maxn << 1];
struct node{
	int val, len;
	bool operator < (const node &x) const{ return x.len < len; }
};
priority_queue <node> q;
int num, head[maxn], vis[maxn], mark[maxn], ismark[maxn], dis[6][maxn], n, m, k, ans, a[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y, int z){ edge[++num] = (Edge){y, head[x], z}, head[x] = num; }

void dijkstra(int k){
	for (int i = 1; i <= n; ++i) vis[i] = 0, dis[k][i] = 1e9;
	dis[k][mark[k]] = 0;
	q.push((node){mark[k], 0});
	while (!q.empty()){
		node tmp = q.top(); q.pop();
		int u = tmp.val, len = tmp.len;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].next){
			int v = edge[i].to;
			if (dis[k][v] > len + edge[i].len){
				dis[k][v] = len + edge[i].len;
				if (!vis[v]) q.push((node){v, dis[k][v]});
			}
		}
	}
}

void work(){
	int sum = 0;
	for (int i = 1; i < k; ++i) sum += dis[a[i]][mark[a[i + 1]]];
	for (int i = 1; i <= n; ++i)
		if (!ismark[i]) ans = min(ans, sum + dis[a[1]][i] + dis[a[k]][i]);
}

void dfs(int t){
	if (t > k) work(); else
	for (int i = 1; i <= k; ++i)
		if (!vis[i]){
			vis[i] = 1, a[t] = i;
			dfs(t + 1);
			vis[i] = 0;
		}
}

int main(){
	n = read(), m = read(), k = read();
	for (int i = 1; i <= k; ++i) mark[i] = read(), ismark[mark[i]] = 1;
	for (int i = 1; i <= m; ++i){
		int x = read(), y = read(), z = read();
		addedge(x, y, z), addedge(y, x, z);
	}
	for (int i = 1; i <= k; ++i) dijkstra(i);
	ans = 2e9;
	for (int i = 1; i <= k; ++i) vis[i] = 0;
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：PragmaGCC (赞：1)

考虑一条路径是怎样的：

- 必定是有一条连接所有市场的路径，因为连接冗余节点没有意义（除非这样使路径更短）。
- 对于某一种经过市场的顺序，我们必定从开头进入，结尾结束。

突破口就在 $k$ 上。

因为 $k$ 很小，我们可以求出每个市场的单源最短路径。

每局所有市场的排列，每次枚举余下的所有点作为农场的长度。求出最小值即可。

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 20005, M = 100005;
int n, m, k;
int st[N];
struct Edge {
	int to, nxt;
	int weight;
} e[M];
int head[N], ecnt;
void addedge(int from, int to, int w) {
	e[++ecnt] = (Edge) { to, head[from], w };
	head[from] = ecnt;
}
typedef pair<int, int> pii;
priority_queue< pii > q;
#define mp make_pair
int dis[10][N];
bool vis[N];
void dij(int s, int *d) {
//	puts("TEST");
	memset(vis, 0, sizeof(vis));
	for (int i=1; i<=n; i++) d[i] = 0x3f3f3f3f;
	while (!q.empty()) q.pop();
	d[s] = 0;
	q.push( mp(0, s) );
	while (!q.empty()) {
		const int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i=head[x]; i; i=e[i].nxt) {
			const int y = e[i].to, z = e[i].weight;
			if (d[y] > d[x] + z) {
				d[y] = d[x] + z;
				q.push( mp(-d[y], y) );
			}
		}
	}
}
bool have[N];
int minlen = 0x3f3f3f3f;
bool v[10];
int ans[10];
void dfs(int x, int d, int p) {
	ans[p] = x;
	if (p == k) {
		for (int i=1; i<=n; i++) {
			if (have[i]) continue;
			int disl = dis[ans[1]][i], disr = dis[ans[k]][i];
//			if (minlen == 0x3f3f3f3f) puts("WRONG");
			minlen = min(minlen, d+disl+disr);
		}
		return ;
	}
	for (int i=1; i<=k; i++) {
		if (v[i]) continue;
		v[i] = 1;
		dfs(i, d + dis[x][st[i]], p + 1);
		v[i] = 0;
	}
}
int main(void) {
	scanf("%d%d%d", &n, &m, &k);
	for (int i=1; i<=k; i++) scanf("%d", st + i), have[st[i]] = 1;
	for (int i=1, u, v, w; i<=m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w), addedge(v, u, w);
//		printf("%d %d %d\n", e[ecnt].to, e[ecnt].nxt, e[ecnt].weight);
	}
	for (int i=1; i<=k; i++) {
		dij(st[i], dis[i]);
//		for (int j=1; j<=n; j++) printf("%d ", dis[i][j]);
	}
	for (int i=1; i<=k; i++) {
		v[i] = 1;
		dfs(i, 0, 1);
		v[i] = 0;
	}
//	for (int i=1; i<=k; i++) printf("%d ", ans[i]);
	printf("%d\n", minlen);
	return 0;
}
```



---

## 作者：KSToki (赞：1)

看到这道题，基本思路就是**最短路**。当我看到$1\le k \le 5$时，就知道它可以~~乱搞了~~。

针对$k$个市场，每个市场跑一遍dijkstra，时间复杂度为$O(k(m+n)logn)$。

重点就在于最后怎样统计答案。因为起点是未知的，经过$k$个市场的顺序也是未知的，而$k$很小，我们就可以暴力全排列枚举经过$k$个市场的顺序计算之间的长度，并枚举所有不是市场的点，计算该点到全排列后的第一个市场的长度加该点到全排列后的最后一个市场的长度，每次与答案比较答案即可，时间复杂度$O(nk!)$，可以接受。

一些细节在代码中有注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y,z,market[6],head[10001],to[100001],nxt[100001],w[100001],tot,dis[6][10001],r[10001],ans=0x7fffffff;
priority_queue<pair<int,int> >q;
bool visit[10001];
inline int read()
{
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void add(int x,int y,int z)
{
	to[++tot]=y;
	w[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
int main()
{
	n=read();
	m=read();
	k=read();
	for(register int i=1;i<=k;++i)
	   market[i]=read(),r[market[i]]=i;//r是一个映射，既可以用于看一个点是不是市场，也方便查找当前市场在之前求最短路时的位置。数据不大，用数组定义。
	while(m--)
	{
		x=read();
		y=read();
		z=read();
		add(x,y,z);
		add(y,x,z);
	}
	memset(dis,127/3,sizeof(dis));//记得初始化
	for(register int i=1;i<=k;++i)
	{
		memset(visit,0,sizeof(visit));//每次都要初始化，我调了十多分钟。。。
		dis[i][market[i]]=0;
		q.push(make_pair(0,market[i]));
		while(!q.empty())
		{
			int x=q.top().second;
			q.pop();
			if(visit[x])
			    continue;
			visit[x]=1;
			for(register int j=head[x];j;j=nxt[j])
			{
				int y=to[j],z=w[j];
				if(dis[i][y]>dis[i][x]+z)
				{
					dis[i][y]=dis[i][x]+z;
					q.push(make_pair(-dis[i][y],y));
				}
			}
		}//dijkstra堆优化板子
	}
	do
	{
		int cnt=0,res=0x7fffffff;
		for(register int i=1;i<k;++i)
		    cnt+=dis[r[market[i]]][market[i+1]];
		for(register int i=1;i<=n;++i)
		    if(!r[i])
		        res=min(res,cnt+dis[r[market[1]]][i]+dis[r[market[k]]][i]);
		ans=min(ans,res);
	}while(next_permutation(market+1,market+k+1));
    //暴力全排列暴力枚举统计答案，next_permutation即可，不用写个dfs
	printf("%d\n",ans);
	return 0;
}
```
~~打个快读，吸口氧，跑得还挺快~~

---

