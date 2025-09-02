# [ABC307F] Virus 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc307/tasks/abc307_f

部屋 $ 1 $, 部屋 $ 2 $, $ \ldots $, 部屋 $ N $ と番号づけられた $ N $ 個の部屋に人が $ 1 $ 人ずつ住んでおり、 また、いくつかの相異なる $ 2 $ つの部屋の間は通路によって結ばれています。 通路は $ M $ 本あり、$ i $ 本目の通路は部屋 $ U_i $ と部屋 $ V_i $ を結んでおり、長さは $ W_i $ です。

ある日(これを $ 0 $ 日目とします)の夜に、部屋 $ A_1,A_2,\ldots,\ A_K $ に住んでいる $ K $ 人がウイルスに(新しく)感染してしまいました。 さらにその後の $ D $ 日間で $ i $ 日目 $ (1\leq\ i\leq\ D) $ には次のように感染が広がりました。

> $ (i-1) $ 日目の夜の時点で感染していた人は、$ i $ 日目の夜の時点でも感染していた。  
>  そうでない人については、$ (i-1) $ 日目の夜の時点で感染していた人の住んでいる部屋のうちの少なくとも $ 1 $ つから 距離 $ X_i $ 以内の部屋に住んでいた時かつその時に限り、新しく感染した。 ここで、部屋 $ P,Q $ の間の距離は、部屋 $ P $ から 部屋 $ Q $ まで通路のみを使って移動する時に通る通路の長さの総和としてあり得る最小値として定義される。 ただし、部屋 $ P $ から 部屋 $ Q $ へ通路のみを使って移動する事ができない時、距離は $ 10^{100} $ とする。

各 $ i $ ($ 1\leq\ i\leq\ N $) について、部屋 $ i $ に住んでいる人がそれぞれ何日目の夜に(新しく)感染したか出力してください。ただし、$ D $ 日目の夜の時点で感染していない場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\leq\ 3\times\ 10^5 $
- $ 0\ \leq\ M\leq\ 3\times\ 10^5 $
- $ 1\ \leq\ U_i\ <\ V_i\leq\ N $
- $ (U_i,V_i) $ はすべて異なる。
- $ 1\leq\ W_i\leq\ 10^9 $
- $ 1\ \leq\ K\leq\ N $
- $ 1\leq\ A_1\ <\ A_2\ <\ \cdots\ <\ A_K\leq\ N $
- $ 1\ \leq\ D\leq\ 3\times\ 10^5 $
- $ 1\leq\ X_i\leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

次のように感染は広がります。 - $ 0 $ 日目の夜、部屋 $ 1 $ に住んでいる人が感染する。 - 部屋 $ 1 $ と部屋 $ 2,3,4 $ の間の距離はそれぞれ $ 2,3,5 $ である。よって、$ X_1=3 $ であるから、$ 1 $ 日目の夜、部屋 $ 2,3 $ に住んでいる人が新しく感染する。 - 部屋 $ 3 $ と部屋 $ 4 $ の間の距離は $ 2 $ である。よって、$ X_2=3 $ であるから、$ 2 $ 日目の夜、部屋 $ 4 $ に住んでいる人も感染する。 よって、部屋 $ 1,2,3,4 $ に住んでいる人はそれぞれ $ 0,1,1,2 $ 日目に新しく感染したため、$ 0,1,1,2 $ をこの順で各行に出力します。

### Sample Explanation 3

どの $ 2 $ つの部屋の間も通路のみを使って移動できるとは限らないことに注意してください。

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 1
2 4 3
3 4 2
1
1
2
3 3```

### 输出

```
0
1
1
2```

## 样例 #2

### 输入

```
7 7
1 2 2
2 3 3
3 4 1
4 5 1
5 6 3
3 7 1
4 7 1
2
1 6
2
2 3```

### 输出

```
0
1
2
-1
2
0
-1```

## 样例 #3

### 输入

```
5 1
1 2 5
2
1 3
3
3 7 5```

### 输出

```
0
2
0
-1
-1```

# 题解

## 作者：xht (赞：15)

每次实际上是做一个多源最短路。

唯一的问题是，如果我们维护源点，最坏情况是每次扫描 $\mathcal O(n)$ 个点，时间复杂度为 $\mathcal O(nd)$。

考虑维护所有已被传染的点和未被传染的点之间的边，每次只需要从 $\le x_i$ 的边对应的未被传染的点开始做多源最短路即可。由于所有边至多被扫描一次，这部分时间复杂度为 $\mathcal O(m)$。

```cpp
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pi>> e(n + 1);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        e[x].pb(mp(y, z));
        e[y].pb(mp(x, z));
    }
    int k;
    cin >> k;
    vi d(n + 1, -1);
    pq<pi> q;
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        d[x] = 0;
        for (auto o : e[x])
            q.push(mp(-o.se, o.fi));
    }
    cin >> k;
    for (int t = 1; t <= k; t++) {
        int w;
        cin >> w;
		pq<pi> p;
        while (q.size() && -q.top().fi <= w) {
            int x = q.top().se, r = w + q.top().fi;
            q.pop();
            if (~d[x]) continue;
			p.push(mp(r, x));
        }
		while (p.size()) {
			int x = p.top().se, r = p.top().fi;
			p.pop();
			if (~d[x]) continue;
			d[x] = t;
			for (auto o : e[x]) {
				int y = o.fi, z = o.se;
				if (z > r) q.push(mp(-z, y));
				else p.push(mp(r - z, y));
			}
		}
    }
	for (int i = 1; i <= n; i++) cout << d[i] << endl;
	return 0;
}
```

---

## 作者：PCCP (赞：3)

## 思考正解

~~一晚上写了三种假做法，真的把我写吐了~~。首先拿到题，第一眼想到的是建立虚拟源点跑最短路，然后前缀和二分。但是这是假的，因为可能存在一条边的边权很大，导致所有单天的传播距离都比他小，但总和比他大，这是无法传染的。

接下来我们只能考虑通过某种方式模拟每天的传播过程。设想每天从已被传染的节点传播，做一遍最短路，当最小距离大于传播距离就不插入队列。当一个节点的所有相邻节点都被传播完时弹出队列，但是这样一个节点会被遍历多次，时间复杂度是假的，而正确性没有问题。

考虑优化上述做法，在 $ 3 \times 10^5 $ 级别的数据下遍历，为了考虑每一条边，只能每一条边只被遍历一次。考虑到一条边被遍历后就没有用了，将所有边按边权排序，用 set 维护查询和删除，每次找到一端已经被遍历的边去做最短路，但是 set 常数大，这样只优化了一点时间复杂度，聊胜于无。

再考虑在本次做最短路时即考虑下一次开始遍历的边或点，每一次最短路总是有无法遍历的边，如果是因为距离过大，而正好该边的边权小于下一次的传播距离，则可以直接加入下一次的遍历队列，注意，这里要把未遍历的那一端丢入队列以保证时间复杂度。但是这样时间复杂度对了，正确性又错了，因为存在一条边下一次无法遍历而下下次可以遍历。

所以可以把现在和下一次都无法遍历的边丢入等待队列，每一次都要先去等待队列里找可放入的边。这样既保证了时间，也保证了正确性。时间复杂度大概是 $ m\log_2{m} $ 的。

## 实现时的问题

* set 维护结构体时，如果重载运算符时未取等，会默认把比较值相同的全部删除，但是重载运算符时取等，删除时会出问题。所以只能使用 multiset 来维护。

* 要开 long long 不然无法通过随机数据的前后各三个点。

## 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<set>
using namespace std;
typedef pair<long long,int> PLI;
const int N=3e5+10;
int n,m,k,d,ti[N];
long long dist[N],sd[N];
int he[N],ne[N<<1],to[N<<1],w[N<<1],tot=1;
int st[N];
struct edge{
	int x,y,w;
	bool operator < (const edge a) const {
		return w<a.w;
	}
}e[N];
multiset<edge> eq;
multiset<PLI,less<PLI>,allocator<PLI>> wait;
void addedge(int x,int y,int z){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
	w[tot]=z;
}
priority_queue<PLI,vector<PLI>,greater<PLI> > q[2];
void dij(int idx,long long x){
	int c=idx%2;
	while(q[c].size()){
		PLI t=q[c].top();
		q[c].pop();
		if(st[t.second]){
			continue;
		}
		ti[t.second]=min(idx,ti[t.second]);
		st[t.second]=true;
		for(int i=he[t.second];i;i=ne[i]){
			int v=to[i];
			if(st[v]){
				continue;
			}
			if(dist[v]>t.first+w[i]){
				if(t.first+w[i]<=x){
					eq.erase(eq.lower_bound(e[i/2]));
					dist[v]=t.first+w[i];
					q[c].push(PLI(dist[v],v));
				}
				else if(w[i]<=sd[idx+1]){
					q[c^1].push(PLI(w[i],v));
				}
				else{
					wait.insert(PLI(w[i],v));
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);
		addedge(e[i].x,e[i].y,e[i].w);
		addedge(e[i].y,e[i].x,e[i].w);
		eq.insert(e[i]);
	}
	memset(dist,0x3f,sizeof dist);
	memset(ti,0x3f,sizeof ti);
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&x);
		ti[x]=0;
		q[1].push(PLI(0,x));
		dist[x]=0;
	}
	scanf("%d",&d);
	for(int i=1;i<=d;i++){
		scanf("%lld",&sd[i]);
	}
	multiset<PLI>::iterator it;
	for(int i=1;i<=d;i++){
		int l=wait.size();
		for(it=wait.begin();it!=wait.end();it++){
			PLI t=*it;
			if(t.first>sd[i]){
				break;
			}
			if(st[t.second]){
				wait.erase(it);
				continue;
			}
			q[i%2].push(t);
			wait.erase(it);
		}
		dij(i,sd[i]);
	}
	for(int i=1;i<=n;i++){
		if(ti[i]>d){
			printf("-1\n");
		}
		else{
			printf("%d\n",ti[i]);
		}
	}
}
```


---

## 作者：lcy_123 (赞：2)

ps:这篇题解大致是对[这篇题解](https://www.luogu.com.cn/blog/KnownError/solution-at-abc307-f)代码的补充

# 思路
考虑最短路，这里我是用 dijkstra 做的。

从读入开始说起，存边暂时跳过，后面会说到。

对于最开始就被感染的节点的读入，首先开一个 pair 存放当前节点最早被感染的时间，也就是答案，以及感染路径的长度。

这里我们设它为 $dis$，因为是求最短路，所以在开始我们把 $dis$ 初始化为极大。当输入一开始就被感染的节点时，把每一个节点的时间和路径长度都设为 0 并压入队列，作为起始点求最短路。

接下来就正常读入每一天的路径长度限制，然后这个时候我们就愉快的开始了最短路！

然而，我们发现我们想要找到节点 $u$ 的答案必须要遍历 $u$ 所连接的每一条边，而如果我们用结构体加链式前向星存图就没法遍历，因此我们用 vector 存图。这里我将 vector 的类型设为 pair，这样可以同时存下 $u,v,w$ 三个变量。

那么我们遍历 $u$ 所链接的每一条边的时候应该怎么进行松弛操作呢？

我们要知道如果答案进行了转移，一定是因为找到了一种方案使 $u$ 感染到 $v$ 的时间早于 $v$ 原来的答案，所以我们分类讨论每一种感染的方式：

假设现在 $u$ 的最优解为 $nowday,noww$，找到的最优解是 $newday,neww$， $u,v$ 之间边的边权为 $w$。

1.  $nowday> d$：此时不能从 $u$ 之前的点转移过来，只能从 $u$ 点直接感染，因此此时 $newday$ 为 $nowday$，$neww$ 为 $w$。
2.  $noww+w \le x_{nowday}$：此时在 $nowday$ 这天从 $u$ 点感染到 $v$ 点的路径总和长度是小于这一天的长度限制的，所以可以在当天将 $v$ 点感染，于是 $newday$ 为 $nowday$，$neww$ 为 $noww+w$。

3.  $noww+w > x_{nowday}$：此时在 $nowday$ 这天无法将 $v$ 点感染，又因为 $v$ 点是从 $u$ 点感染过来的，所以 $v$ 的感染时间一定晚于 $u$ 的感染时间。所以，我们在 $nowday$ 和 $d$ 之间找。由于 $d$ 非常大，直接枚举会超时，所以我们二分去找。

	首先，我们要对第 $nowday+1$ 天进行判断，如果此时超过了 $d$ 天就不用再二分了，此时我们把 $nowday$ 和 $noww$ 都设为极大，这样在松弛操作的时候就不会更新答案了。然后我们会发现在二分的时候不知道该如何判断可行方案，如果直接枚举每一天的 $x_i$ 是一定会超时的，要 $O \left(1\right)$ 去判断。
    
    我们可以想到直接将 $l$ 和 $mid$ 之间每天的 $x$ 的最大值与 $noww$ 比较，如果 $noww$ 较大，那么第 $l$ 到第 $mid$ 天之间都不能感染 $v$ 点，所以答案取在 $mid$ 和 $r$ 之间。
    
    那么要怎么去求区间最大值呢？这个时候就不得不提到 st 表了，不知道如何使用 st 表的同学可以在[P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)中的题解中学习一下，它可以快速求出区间最大值。再回到这一题，我们在读入 $x$ 之后就可以对 st 表进行预处理，详细的我就不讲了，代码中有。这样在二分的时候我们就可以 $O\left(1\right)$ 的求出 $l$ 到 $mid$ 的最大值了。
    
    在二分之后，经过之前对各种方案的排除，此时的 $r$ 一定可以作为 $v$ 被感染的一天，于是 $newday$ 为 $r$，$neww$ 为 $w$。

此时我们就将 $v$ 被感染的时间和路径长度都求了出来，再与 $v$ 原来的答案比较，更新就完成了松弛操作。在具体代码中我用了一个 find 函数来实现查找，注意返回值是 pair 型的，方便和 $dis_v$ 比较。

最后的最后就是输出了，对于 $1 \le i \le n$ 的每一个 $dis_i$ 的第一个元素，我们先看它是否大于 $d$，如果是，说明 $dis_i$ 的第一个元素仍然为极大，始终没有被感染，输出 $-1$,否则直接输出即可。

# AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 300005
#define MAXM 600005
#define MAXX 1e18
#define pii pair<pair<int,int>,int>
#define piii pair<int,int>
//define 
using namespace std;
int n,m,k,d,a[MAXN],x[MAXN];
int vis[MAXN],st[MAXN][105],cnt;
pair<int,int>dis[MAXN];//存感染天数和最短路长度 
vector<piii>edge[MAXM];//用vector存边，方便遍历一个点所连接的所有点 
priority_queue<pii,vector<pii>,greater<pii> >q;
void stt()//预处理st表,st[i][j]表示在x[d]中以i为起点,长度为2^j的序列中最大的x[i]; 
{
	for(int i=1;i<=d;++i)st[i][0]=x[i];//将每一天的距离显示放入st表 
    for(int j=1;(1<<j)<=d;++j)
        for(int i=1;i<=d-(1<<j)+1;++i)
            st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int qstt(int l,int r)//st表求最值 
{
	int id=__lg(r-l+1);//__lg用于计算以2为底的对数的函数,表示输入参数的二进制表示中最高位1的位置
    return max(st[l][id],st[r-(1<<id)+1][id]);
}
piii find(int now_w,piii di)//用来查找新的感染时间和最短路长度 
{
	int now_day=di.first;//now_day表示当前的时间 
	int last_w=di.second;//last_w表示当前最短路长度
	//now_w表示下一条边的边权 
	if(now_day>d)return di;
	if(now_w+last_w<=x[now_day])return make_pair(now_day,now_w+last_w);//当天可以被感染 
	/*当前节点值加上当前边边权比这一天的距离小，方案可行*/
	else //当天无法被感染，往后找 
	{
		now_day++;//到下一天 
		di.first++;//原数组也要更新 
		if(now_day>d)return make_pair(MAXX,MAXX);//已经超过d天，无论如何不能被感染 
		if(qstt(now_day,d)<now_w)return make_pair(MAXX,MAXX);
		//从这一天到最后一天的距离都已经小于边权了，无论如何不能被感染 
		int l=now_day,r=d,mid;//在这一天和最后一天中有一天可以被感染 
		while(l<r)//二分去寻找最早感染的那一天 
		{
			mid=(l+r)/2;
			if(qstt(now_day,mid)<now_w)l=mid+1;//若从现在到第mid天都不能感染，答案就取在mid~r之间 
			else r=mid; //否则感染的时间在现在~mid之间 
		}
		return make_pair(r,now_w);//返回能被感染的最早的一天和此时被感染的最短路
		//返回当前边边权是因为当前节点由这条边感染而来，因此被感染的最短路就是边权
	}
}
void dij()//最短路 
{
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		int y=edge[u].size();//表示u连接了多少个点 
		for(int i=0;i<y;i++)//访问当前节点u连接的每一条边 
		{
			int v=edge[u][i].first;
			int w=edge[u][i].second;
			piii m=find(w,dis[u]);//寻找感染天数 
			if(dis[v]>m)//首先比较感染天数，越早越好，其次比较感染的最短路 
			{
				dis[v]=m;//找到更优解，更新 
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		edge[u].push_back(make_pair(v,w));//无向图双向建边 
		edge[v].push_back(make_pair(u,w));
	}
	fill(dis+1,dis+n+1,piii{MAXX,MAXX});//dis初始化最大，求最短路 
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i];
		dis[a[i]].first=0;
		dis[a[i]].second=0;
		//dis[i].first表示被感染的天数dis[i].second表示走到i的最短路长度 
		q.push(make_pair(dis[a[i]],a[i]));//将第一天感染的节点加入队
	}
	cin>>d;for(int i=1;i<=d;i++)cin>>x[i];
	stt(); dij();
	for(int i=1;i<=n;i++)
	{
		if(dis[i].first>d)cout<<-1<<endl;//该点没有被感染过 
		else cout<<dis[i].first<<endl;
	}
} 
```


---

## 作者：JWRuixi (赞：2)

~~考场上怎么会想不到……~~

### 题意

给定一张 $n$ 个点，$m$ 条边的无向图（边带权），$K$ 个初始时被感染的点，传染过程如下：

- 若 $u$ 能到达 $v$，则 $v$ 在 $i$ 天被感染的充要条件是 $u$ 在第 $i-1$ 天或之前已被感染且 $dis(u,v) \le x_i$。

求在 $D$ 天中每个点什么时候被感染，若在 $D$ 天仍然未被感染则输出 `-1`。

### 分析

考虑如果将感染条件改为：$u$ 和 $v$ 相连且 $w(u,v) \le x_i$。那么用最短路算法就可以随便解决，我们考虑多加一点参数。

令每个点的 $dis$ 形如 $(t_i,d_i)$ 表示在第 $t_i$ 天被传染，距离传染源距离为 $d_i$。比较大小的方式为先 $t$ 后 $d$（直接用 `pair` 即可）。那么转移就可以分为两类（同一天被转移和之后被转移）：

- 若 $d_u+w(u,v) \le x_{t_u}$，则 $dis_v \gets (t_u,d_u+w(u,v))$。
- 若 $w(u,v) \le x_i[i>t_u]$，则 $dis_v \gets (i,w(u,v))$。

考虑第二类暴力转移速度太慢，我们找的显然是 $i$ 最小的情况，那么用前缀 $\max$ 加二分就可以解决了，当然线段树上二分也是可以的（其实好像线段树加二分也可以）。

复杂度 $\mathcal O(n\log^2n)$。

### code

```cpp
while (!q.empty()) {
	int u = q.top().u; q.pop();
	if (vis[u]) continue;
	vis[u] = 1;
	for (auto &[v, w] : G[u]) {
		if (dis[u].se + w <= x[dis[u].fi] && MP(dis[u].fi, dis[u].se + w) < dis[v]) {
			dis[v] = MP(dis[u].fi, dis[u].se + w);
			if (!vis[v]) q.push({v, dis[v]});
			continue;
		}
		int l = dis[u].fi + 1, r = D, mid, res = -1;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (w <= qry(l, mid)) res = mid, r = mid - 1;
			else l = mid + 1;
		}
		if (~res && MP(res, w) < dis[v]) {
			dis[v] = MP(res, w);
			if (!vis[v]) q.push({v, dis[v]});
		}
	}
}
for (int i = 1; i <= n; i++) writeln(dis[i].fi > D ? -1 : dis[i].fi);
```

---

## 作者：LingHusama (赞：1)

**Virus 2 题解（模拟）**

1. 背景：
老师说做做复习下最短路。

我：有最短路吗？不是模拟吗？ 

2. 解题思路：
 
我的题解稍微用到了最短路的思想，但代码与其完全没关系。

模拟+先队列存边+排除不可能答案。

先想一个问题：哪些能剪枝？ 
可以直接把所有在点 $i$ 上的边大于 $x_i$ 的直接删除吗？（下面会揭晓）

然后这个边如果小于 $x_i$ 的话，我走过了就不用再走了吧。（反复感染就不用管了）那么这里可以剪枝，肯定可以删除两边点都已经被感染的边。 

那么按理来说时间复杂度就是 $m$，大不了 $2m$ 维护一个 ```vector``` 表示当前天数被感染了哪些，不断更迭打标记。
 
问题就在于：我可能隔天感染！因为 $x_i$ 可能递减。 
	
这就是第一个问题的答案：不能删除大于 $dis$ 的，因此还要用一个 ```priority_queue``` 维护全局有可能帮助更新的边，按照距离从小到大排序。
 
那么边就不用删除了比 $dis$ 大的了，直接维护没有用过的边以及最短路可能添加的边。(优先队列)

注意下我下面的注释。

然后直接模拟。

3. 复杂度的分析：$d+n+m\operatorname{log}m$ 
	
怎么来的？

枚举天数：$d$。

点集 $nowief$ 是每到一天就把前一天感染的人可能的边加入，然后 ```pop``` 的，所以总共的时间复杂度是 $n$。(每个点仅会进一次） 

边集用了优先队列，并且每一条边都会枚举到，总共的时间大概是  $m\operatorname{log}m$。（可能会由于最短路思想多一点）能过......

4. 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
/*
LingHusama题解 
（atcoder bushigeshizhenpi） 
*/
int vis[300005];//用于查看某个点是否被 
struct node{
	int tmm;//感染时间，但后来发现好像并没有用到...... 
	int to;//到达的点 
	int val;//边的长度 
	bool operator <(const node &x)const{
		return x.val<val;//优先队列先把边短的排在前面。 
	}
};
vector<node>mp[300005];//建图所需 
priority_queue<node>q;
int main(){
	ios::sync_with_stdio(false);
	int n,m,k,d;
	cin >> n >> m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin >> a >> b >> c;
		mp[a].push_back((node){-1,b,c});
		mp[b].push_back((node){-1,a,c});
	}
	cin >> k;
	queue<int>nowief;//用于存放“每一轮最新”感染的点 。理解下最新，就是说旧的我没存 
	for(int i=1;i<=k;i++){
		int now;
		cin >> now;
		nowief.push(now);
		for(int j=0;j<mp[now].size();j++){//把所有第一轮感染的点所连的所有边加入 ,下面做法其实类似 
			node kk=mp[now][j];//这里没有剪左右两边都感染的点,因为是第一轮 
			q.push((node){1,kk.to,kk.val});
		}
		vis[now]=1;
	}
	cin >> d;
	for(int i=2;i<=d+1;i++){//为什么从2开始？因为我没看题，最后一行代码会有注释解释 
		int dis;
		cin >> dis;
		while(nowief.size()){//把所有前一天被感染的点能够到达的边全部加入q，准备统计 
			int top=nowief.front();
			nowief.pop();
			for(int j=0;j<mp[top].size();j++){
				node e=mp[top][j];
				if(vis[e.to]){//注意if内不能写这一句：||e.val>dis，因为到后面dis可能会变小从而使这条边有机会更新他人 ,但是更新过的点肯定可以去掉减枝 
					continue;
				}
				q.push(e);
			}
		}
		while(q.size()){
			node e=q.top();
			if(e.val>dis){//用的优先队列，后面的在今天肯定是传染不了得了 ，注意pop的位置，这时候不能把这个边pop了 
				break;
			}
			q.pop();
			if(vis[e.to]!=0){//对于不需要再用的边pop。 
				continue;
			}
			int to=e.to;
			for(int j=0;j<mp[to].size();j++){
				node kk=mp[to][j];
				q.push((node){i,kk.to,kk.val+e.val});//为什么要加e.val？因为可能距离还够，可以越过这个点继续传染。这里用到了最短路思想 
				//那么这里时间复杂度会增加吗?只会有一点点，因为我前面判断了 vis[e.to]==0，如果这个边有更优 （准确而言肯定有更优吧） 
				//转移的话，这里根本就不会进！ 也为后面的运算进行了精简 
			}
			vis[to]=i;
			nowief.push(to);//加入最新一轮感染的点，准备下一轮迭代 
		}
	}
	for(int i=1;i<=n;i++){//为什么-1呢，因为我最开始是以1为下标的，然后到不了的点的vis又是0，-1刚刚好
	//（绝对不是没看题的原因!) 
		cout<<vis[i]-1<<endl;
	}
}
```

---

## 作者：Strelitzia_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc307_f)。

## 思路

和题解一样的 dij 做法，但是维护的信息不同。

我们对于每个点维护二元组 $(a, b)$ 表示这个点在第 $a$ 天被感染，此时距离前一天最近的被感染的点的距离为 $b$。然后我们让这个二元组以 $a$ 为第一关键字，$b$ 为第二关键字，塞到 `pair` 里跑 dijkstra 即可。

转移稍微有点麻烦。例如我们当前讨论的点为 $u$，他的二元组为 $(a_u, b_u)$，当前与其相连的点为 $v$，他们之间的边权为 $w$，那么：

- 如果 $b_u+w\le X_{a_u}$，那么就代表着 $v$ 可以和 $u$ 在同一天被传染，此时可以用 $(a_u, b_u+w)$ 来更新 $v$ 的二元组；

- 否则，如果我们想让 $v$ 通过 $u$ 被感染，就只能等到第 $a_u$ 天之后的某一天 $d$，使得 $X_{d}\ge w$。此时我们可以用 $(d, w)$ 来更新 $v$ 的二元组。

在第二种情况中，秉持着“应感染尽感染”的原则，我们需要找到最小的 $d$，使 $d \ge a_u+1$ 且 $X_d\ge w$。这个过程我们可以用 st 表上二分实现，使时间复杂度变得可以接受。

注意被感染天数不能超过 $D$。

总时间复杂度 $\mathcal{O}(D\log D+M(\log D+\log M))$，可以接受。代码：

```cpp
#define pii pair<int, int>
#define ppiip pair<pii, int>
#define mkp make_pair
 
const int N = 3e5 + 3;
 
struct GRAGH{
	int to, nxt, val;
} e[N << 1];
 
int head[N], gop, n, m, d, dis[N], ddis[N], day[N], a[N], k;
int lg2[N], st[N][21];
bool vis[N];
 
priority_queue<ppiip> q;
 
void add_edge(int to, int nxt, int val) {
	e[++gop].to = nxt, e[gop].nxt = head[to], head[to] = gop, e[gop].val = val;
}
 
int getmin(int l, int r) {
	if (l == r) return st[l][0];
	int now = lg2[r - l + 1];
	return max(st[l][now], st[r - (1 << now) + 1][now]);
}
 
int lwbd(int l, int r, int val) {
	int ans = 0;
	if (getmin(l, r) < val) return r + 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (getmin(l, mid) >= val) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}
 
signed main() {
	
	n = read(), m = read();
	memset(dis, 0x3f, sizeof(dis));
	memset(ddis, 0x3f, sizeof(ddis));
	for (int i = 1; i <= m; i++) {
		int to = read(), nxt = read(), val = read();
		add_edge(to, nxt, val), add_edge(nxt, to, val);
	}
	k = read();
	for (int i = 1; i <= k; i++) a[i] = read(), dis[a[i]] = ddis[a[i]] = 0;
	d = read();
	for (int i = 1; i <= d; i++) day[i] = read();
	for (int i = 1; i <= k; i++) q.push(mkp(mkp(-1, 0), a[i]));
	
	for (int i = 2; i <= d; i++) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 1; i <= d; i++) st[i][0] = day[i];
	for (int j = 1; j <= lg2[d]; j++)
		for (int i = 1; i <= d - (1 << j) + 1; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	
	while (!q.empty()) {
		ppiip now = q.top();
		q.pop();
		int to = now.second, nowday = -now.first.first, nowdis = -now.first.second;
		if (vis[to]) continue;
		vis[to] = 1;
		for (int i = head[to]; i; i = e[i].nxt) {
			if (nowdis + e[i].val <= day[nowday] && mkp(nowday, nowdis + e[i].val) <= mkp(ddis[e[i].to], dis[e[i].to])) {
				ddis[e[i].to] = nowday, dis[e[i].to] = nowdis + e[i].val;
				q.push(mkp(mkp(-ddis[e[i].to], -dis[e[i].to]), e[i].to)); continue;
			}
			if (nowday >= d) continue;
			int nownowday = lwbd(nowday + 1, d, e[i].val);
			if (nownowday > d) continue;
			if (mkp(nownowday, e[i].val) <= mkp(ddis[e[i].to], dis[e[i].to])) {
				ddis[e[i].to] = nownowday, dis[e[i].to] = e[i].val;
				q.push(mkp(mkp(-ddis[e[i].to], -dis[e[i].to]), e[i].to)); continue;
			}
		}
	}
	
	for (int i = 1; i <= n; i++)
		if (ddis[i] <= d) printf("%lld\n", ddis[i]);
		else puts("-1");
	
}
```

------------


说句闲话，比赛中因为 st 表写挂了吃了三发罚时……

---

## 作者：_cbw (赞：0)

提供一种赛时的 $\Theta(m \log n + D)$ ~屎山~做法。

一个很朴素的想法是记录每一个未被感染的人与距离最近的感染者的距离 $d_u$，在每一天暴力枚举可以被感染的人（即满足 $d_u \le x_i$ 的人）并更新答案。然而这是 $\Theta(Dn)$ 的，无法通过。

不难想到，这个过程可以用 set 优化。即，枚举天数，每一天取出 $d_u \le x_i$ 且未被感染的人，更新答案并松弛其它点的距离。

实现上，用一个 set 不够，因为题目要求在**当天前**的 $d_u \le x_i$，而松弛后可能本来不符合条件的被当作符合。如下图（$x_i = 5$，当天开始前仅有 $1$ 感染）

![](https://cdn.luogu.com.cn/upload/image_hosting/wil8ycas.png)

$1$ 在感染 $2$ 后，$2$ 会松弛 $3$，若此时认为 $3$ 也被感染则答案错误。

解决方法也很~屎山~简单，开两个 set，一个存 $d$，一个用来临时存放当天松弛的结果即可。

代码太屎山了，建议看懂上面后自行实现。

```cpp
#include <climits>
#include <cstdio>
#include <set>
#define MAXN 3000005
using namespace std;
using lli = long long;
using PII = pair<lli, int>;

struct Edge
{
    int to, nxt;
    lli w;
} edges[MAXN << 1];

// vec, vecp 相当于 vector
int cnt, head[MAXN], sp[MAXN], vec[MAXN], vecp;
lli dis[MAXN];

// st 存 dis，stt 为临时用

set<PII> st, stt; // (distance, id)

inline void add_edge(const int from, const int to, const lli w)
{
    edges[++cnt] = {to, head[from], w}, head[from] = cnt;
}

int main()
{
    // freopen("D:/day1-1/virus/data24.in", "r", stdin);
    // freopen("D:/day1-1/virus/data24.out", "w", stdout);
    int n, m, u, v, k, d;
    lli w, x, di;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf(" %d %d %lld", &u, &v, &w);
        add_edge(u, v, w), add_edge(v, u, w);
    }
    scanf(" %d", &k);
    for (int i = 1; i <= n; ++i)
        dis[i] = LLONG_MAX;
    for (int i = 1; i <= n; ++i)
        sp[i] = -1;
    for (int i = 1; i <= k; ++i)
    {
        scanf(" %d", &u);
        dis[u] = 0;
        sp[u] = 0;
        // 松弛
        for (int e = head[u]; e; e = edges[e].nxt)
        {
            v = edges[e].to;
            if (edges[e].w < dis[v])
            {
                if (dis[v] != LLONG_MAX)
                    st.erase({dis[v], v});
                st.insert({edges[e].w, v});
                dis[v] = edges[e].w;
            }
        }
    }
    scanf(" %d", &d);
    for (int t = 1; t <= d; ++t) // 枚举天数
    {
        scanf(" %lld", &x);
        vecp = 0;
        while (st.size() && st.begin()->first <= x)
        {
            di = st.begin()->first, u = st.begin()->second;
            st.erase(st.begin());
            vec[++vecp] = u;
            if (sp[u] == -1)
                sp[u] = t; // 更新答案
            // 统计答案
            for (int i = head[u]; i; i = edges[i].nxt)
            {
                v = edges[i].to, w = edges[i].w;
                if (di + w <= dis[v] && di + w <= x)
                {
                    auto it = stt.find({dis[v], v}); // 先扔进临时 set
                    if (it != stt.end())
                        stt.erase(it);
                    stt.insert({di + w, v}), dis[v] = di + w;
                }
            }
        }
        while (stt.size() && stt.begin()->first <= x)
        {
            // 对临时 set 内的点向外松弛
            di = stt.begin()->first, u = stt.begin()->second;
            stt.erase(stt.begin());
            vec[++vecp] = u;
            if (sp[u] == -1)
                sp[u] = t;
            for (int i = head[u]; i; i = edges[i].nxt)
            {
                v = edges[i].to, w = edges[i].w;
                if (di + w <= dis[v] && di + w <= x)
                {
                    auto it = stt.find({dis[v], v});
                    if (it != stt.end())
                        stt.erase(it);
                    stt.insert({di + w, v}), dis[v] = di + w;
                }
            }
        }
        stt.clear();
        // 更新 dis
        for (int i = 1; i <= vecp; ++i)
        {
            u = vec[i];
            dis[u] = 0;
            for (int e = head[u]; e; e = edges[e].nxt)
            {
                v = edges[e].to, w = edges[e].w;
                if (w < dis[v])
                {
                    if (dis[v] != LLONG_MAX)
                        st.erase({dis[v], v});
                    st.insert({w, v});
                    dis[v] = w;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", sp[i]);
    return 0;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 思路

考虑最短路，队列里存编号，感染时间和感染经过的距离。

转移的时候分两种情况，设感染源为 $u$，他感染的人为 $v$，$u$ 被感染的时间为 $t$，$v$ 被感染的时间为 $T$，$(u, v)$ 的边权为 $w$，$u$ 在被感染时经过的距离为 $dis$。

1. $v$ 被感染的时间为 $t$，当且仅当 $dis + w \le x_i$ 是，那么 $v$ 感染经过的距离为 $dis + w$。
2. $v$ 被感染的时间 $> t$，此时感染经过的距离为 $w$。为找到最小的 $T$ 使得 $x_T \ge w$，在已知区间最大值的情况下，具有单调性，可以二分。区间最大值可以用线段树或 ST 表预处理。

## 代码

```cpp
struct tree {
	int l, r, mx;
} tr[1200005];
struct node {
	ll x, tim, dis;
};
priority_queue <node> q;
vector <pair <ll, ll> > e[300005];
ll a[300005], b[300005], ans[300005], mx[300005][30], vis[300005];

bool operator < (const node &x, const node &y) {
	if(x.tim != y.tim) return x.tim > y.tim;
	return x.dis > y.dis;
}
void bd(ll x, ll l, ll r) {
	tr[x].l = l, tr[x].r = r;
	if(l == r) return tr[x].mx = b[l], void(0);
	ll mid = (l + r) >> 1;
	bd(x << 1, l, mid), bd(x << 1 | 1, mid + 1, r);
	tr[x].mx = max(tr[x << 1].mx, tr[x << 1 | 1].mx); 
} 
ll fd(ll x, ll l, ll r) {
	if(tr[x].l > r || tr[x].r < l) return 0;
	if(tr[x].l >= l && tr[x].r <= r) return tr[x].mx;
	return max(fd(x << 1, l, r), fd(x << 1 | 1, l, r));
} 
signed main() {
	ll n = rd(), m = rd();
	for(ll i = 1; i <= m; i++) {
		ll u = rd(), v = rd(), w = rd();
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	ll k = rd();
	for(ll i = 1; i <= k; i++) a[i] = rd(), q.push({a[i], 0, 0});
	ll d = rd();
	for(ll i = 1; i <= d; i++) b[i] = rd();
	for(ll i = 1; i <= n; i++) ans[i] = inf;
	bd(1, 1, n);
	while(q.size()) {
		ll x = q.top().x, tim = q.top().tim, dis = q.top().dis; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		ans[x] = tim;
		if(tim >= d) continue;
		for(auto it : e[x]) {
			ll v = it.first, w = it.second;
			if(dis + w <= b[tim] && tim) {
				if(tim < ans[v]) q.push({v, tim, dis + w});
			}
			else {
				ll L = tim + 1, R = d;
				while(L < R) {
					ll mid = (L + R) >> 1;
					if(w <= fd(1, L, mid)) R = mid;
					else L = mid + 1;
				}
				if(L < ans[v] && w <= b[L])
					q.push({v, L, w});
			}
		}
	}
	for(ll i = 1; i <= n; i++) 
		if(ans[i] < inf) cout << ans[i] << '\n';
		else puts("-1");
	return 0;
}
```

---

