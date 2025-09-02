# [USACO24FEB] Bessla Motors G

## 题目背景

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。本题的内存限制为 512MB，通常限制的 2 倍。**

## 题目描述

为了推广他的贝斯拉（Bessla）电动拖拉机系列，Farmer John 希望展示贝斯拉的充电网络。他已标记了地图上 $N$（$2\le N\le 5\cdot 10^4$）个编号为 $1\ldots N$ 的兴趣点，其中前 $C$（$1\le C<N$）个是充电站，其余为旅游目的地。这些兴趣点之间由 $M$（$1 \le M \le 10^5$）条双向道路连接，其中第 $i$ 条连接不同的点 $u_i$ 和 $v_i$（$1\le u_i,v_i\le N$）且长度为 $l_i$ 英里（$1\le l_i\le 10^9$）。

贝斯拉一次充电最多可行驶 $2R$英里（$1\le R\le 10^9$），使之可以到达一个充电站 $R$ 英里范围内的任何目的地。一个目的地被称之为交通便利的，如果可以从至少 $K$（$1\le K\le 10$）个不同的充电站到达目的地。你的任务是帮助 Farmer John 确定交通便利的旅游目的地的集合。 

## 说明/提示

### 样例解释 1

我们在 $1$ 有一个充电站。从这个充电站出发，我们可以到达 $2$（因为它与 $1$ 的距离为 $3$），但不能到达 $3$（因为它与 $1$ 的距离为 $5$）。因此，只有点 $2$ 是交通便利的。

### 样例解释 2

我们在 $1$ 和 $2$ 有充电站，点 $3$ 和 $4$ 均位于 $1$ 和 $2$ 的 $101$ 距离内。因此，点 $3$ 和 $4$ 都是交通便利的。

### 测试点性质

- 测试点 $4-5$：$K=2$，$N\le 500$ 且 $M\le 1000$。
- 测试点 $6-7$：$K=2$。
- 测试点 $8-15$：没有额外限制。

## 样例 #1

### 输入

```
3 3 1 4 1
1 2 3
1 3 5
2 3 2```

### 输出

```
1
2```

## 样例 #2

### 输入

```
4 3 2 101 2
1 2 1
2 3 100
1 4 10```

### 输出

```
2
3
4```

## 样例 #3

### 输入

```
4 3 2 100 2
1 2 1
2 3 100
1 4 10```

### 输出

```
1
4
```

# 题解

## 作者：Lame_Joke (赞：10)

- ### 题目大意

  怎么说，这道金组第一题看着挺高级的，其实就是道最短路，求 $C$ 之后的点与前 $C$ 个点中的 $K$ 个或以上之间最短路不超过 $R$ 的点。

- ### 大体思路

  我们最容易想到的暴力有两种，第一种枚举前 $C$ 个点，对每个点进行最短路加记录，第二种枚举 $C$ 之后的点，对每个点进行最短路加记录。我们发现，第二种暴力的时间复杂度是远小于第一种的，因为与你当前枚举点满足条件的点达到 $K$ 个，你就可以直接跳出了，但是总是会有一些卡你的数据，让第一种枚举更优，所以我们可以把两种暴力结合起来，猜一个不大不小的数，当 $C$ 没超过这个数时就用第一种暴力，超过了用第二种，这里我猜的是 $10000$ 可以过掉。还有就是我最短路用的是二叉堆优化的dij，不知道别的能不能过。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long w[200005],dis[50005],ans1,ans2[50005],ans[50005],r,n,m,c,k,cnt,hd[200005],to[200005],nxt[200005],ans3[50005];
  bool cs[50005],vis[50005];
  struct yxQueue{
  	int a[524288];
  	int cnt1=0;
  	void up(int v)
  	{
  		while(v!=1&&dis[a[v]]<dis[a[v/2]])
  		{
  			swap(a[v],a[v/2]);
  			v/=2;
  		}
  	}
  	void down(int v)
  	{
  		while(v*2<=cnt1)
  		{
  			int t;
  			t=v*2;
  			if(t<cnt1&&dis[a[t+1]]<dis[a[t]]) t++;
  			if(dis[a[v]]<dis[a[t]]) break;
  			swap(a[v],a[t]);
  			v=t;
  		}
  	}
  	void push(int x)
  	{
  		a[++cnt1]=x;
  		up(cnt1);		
  	}
  	void pop()
  	{
  		swap(a[cnt1],a[1]);
  		cnt1--;
  		down(1);
  	}
  	bool empty(){return cnt1==0;}
  	int front(){return a[1];}	
  }q;
  inline void add(int u,int v,int w1)
  {
  	nxt[++cnt]=hd[u];
  	hd[u]=cnt;
  	to[cnt]=v;
  	w[cnt]=w1;
  }
  inline void dij(int x)
  {
  	for(int i=1;i<=n;i++) dis[i]=0x7f7f7f7f7f,vis[i]=0,cs[i]=0;
  	dis[x]=0;
  	q.push(x);
  	int u;
  	while(!q.empty())
  	{
  		u=q.front();
  		q.pop();
  		if(vis[u]!=0) continue;
  		vis[u]=1;
  		for(register int i=hd[u];i;i=nxt[i])
  		{
  			if(dis[to[i]]>dis[u]+w[i])
  			{
  				dis[to[i]]=dis[u]+w[i];
  				if(dis[to[i]]<=r)
  				{
  					if(cs[to[i]]==0)
  					{
  						cs[to[i]]=1;
  						ans[to[i]]++;						
  					}
  				}
  				else continue;
  				q.push(to[i]);
  			}
  		}
  	}
  }
  inline void dij2(int x)
  {
  	for(int i=1;i<=n;i++) dis[i]=0x7f7f7f7f7f,vis[i]=0,ans3[i]=0;
  	ans3[0]=0;
  	dis[x]=0;
  	q.cnt1=0;
  	q.push(x);
  	int u;
  	while(!q.empty())
  	{
  		u=q.front();
  		q.pop();
  		if(vis[u]!=0) continue;
  		vis[u]=1;
  		for(register int i=hd[u];i;i=nxt[i])
  		{
  			if(dis[to[i]]>dis[u]+w[i])
  			{
  				dis[to[i]]=dis[u]+w[i];
  				if(to[i]<=c&&ans3[to[i]]==0&&dis[to[i]]<=r)
  				{
  					ans3[0]++;
  					ans3[to[i]]=1;
  					if(ans3[0]>=k)
  					{
  						ans2[++ans1]=x;
  						return;
  					}
  				}
  				if(dis[to[i]]>r) continue;
  				q.push(to[i]);
  			}
  		}
  	}
  }
  int main()
  {
  	scanf("%lld%lld%lld%lld%lld",&n,&m,&c,&r,&k);
  	int a1,a2,a3;
  	for(int i=1;i<=m;i++)
  	{
  		scanf("%d%d%d",&a1,&a2,&a3);
  		add(a1,a2,a3);
  		add(a2,a1,a3);
  	}
  	if(c<=10000)                          //嘿嘿，精髓卡时 
  	{
  		for(int i=1;i<=c;i++) dij(i);
  		for(int i=c+1;i<=n;i++)
  		{
  			if(ans[i]>=k)
  			{
  				ans2[++ans1]=i;
  			}
  		}
  		printf("%d",ans1);
  		for(int i=1;i<=ans1;i++)
  		{
  			printf("\n%d",ans2[i]);
  		}		
  	}
  	else
  	{
  		for(int i=c+1;i<=n;i++) dij2(i);
  		printf("%d",ans1);
  		for(int i=1;i<=ans1;i++)
  		{
  			printf("\n%d",ans2[i]);
  		}
  	}	
  
  }
  ```

---

## 作者：Error_Eric (赞：9)

### Statement

[链接](https://www.luogu.com.cn/problem/P10193).

### Sol

考虑 $k=1$ 的情况。

注意到一种算法，先将将所有充电站列为蓝的，其他点列为白的。每次找到距离充电站最近的白点变蓝，直到最近的这个白点距离蓝点的距离大于 $R$ 为止。这样子每个「兴趣点」都可以找到最近的充电站。找到最近白点的过程可以用堆优化。~~我愿称之为多源 dijkstra。~~

然后考虑 $k\not=1$ 的情况。

注意到我们发现只需要标记每个点每次变蓝的来源充电站，在下一次扩展到它的时候额外判断是否已经有 $k$ 个标记，或者同一个来源的充电站是否已经标注过它了即可。因为每条边不会被拓展超过 $k$ 次，所以复杂度小于 $O(km\log m)$，是对的。

通俗地，我们先让每个充电站向附近发宣传单。一个宣传单有「充电站编号，宣传对象，目标距离」三个要素。接着每次我们从候选的宣传单中找出距离最短的那个宣传单，若宣传对象的家里没有贴满 $k$ 个可以去的充电站，而且也没有贴着这个充电站的宣传单，那么把这张宣传单贴到宣传对象家里，然后这个宣传对象会对周围距离在限定范围内的点发这个充电站的宣传单。最后检查这个点有没有贴够 $k$ 张宣传单即可。

### Code

赛时代码较为丑陋。

而且网站炸了没交上去，气死了气死了气死了。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
#define int long long
const int _=1e5+5;
struct edge{int uv,w;}e[_];

int n,m,c,r,k,iu,iv;
vector<int>con[_],avai[_];
struct xep{// 题解中的宣传单
    int origin,to,totdist;
    xep(int O,int T,int TT){
        origin=O,to=T,totdist=TT;
    }
};
bool operator<(xep e1,xep e2){
    if(e1.totdist==e2.totdist)
        return e1.origin*1e5+e1.to<e2.origin*1e5+e2.to;
    else 
        return e1.totdist<e2.totdist;
}
multiset<xep> ex; // 可以用 set 优化到 kmlogm
void xepand(xep pre){ // 散发宣传单
    for(auto&avx:avai[pre.to])
        if(avx==pre.origin) return;
    avai[pre.to].push_back(pre.origin);
    for(int eid:con[pre.to]){
        int to=e[eid].uv-pre.to;
        xep nex=xep(pre.origin,to,pre.totdist+e[eid].w);
        bool ok=(nex.totdist<=r&&avai[nex.to].size()<k);
        for(auto&avx:avai[nex.to])
           if(avx==nex.origin) ok=0;
        if(ok)
            ex.insert(nex);
    }
}
signed main(){
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>c>>r>>k;
    for(int i=1;i<=m;i++)
        cin>>iu>>iv>>e[i].w,
        e[i].uv=iu+iv,
        con[iu].push_back(i),
        con[iv].push_back(i);
    for(int i=1;i<=c;i++)
        xepand({i,i,0});
    while(ex.size())
        xepand(*ex.begin()),
        ex.erase(ex.begin());
    vector<int> ans;
    for(int i=c+1;i<=n;i++)
        if(avai[i].size()>=k)
            ans.push_back(i);
    cout<<ans.size()<<endl;
    for(int&ax:ans) 
        cout<<ax<<endl;
}
```

---

## 作者：KingPowers (赞：8)

很考察对 dijkstra 算法流程理解程度的一道题。

注意到 $k$ 并不大，因此考虑一些和 $k$ 相关的做法。

先从特殊情况入手，如果 $k=1$ 那就是对每个点判断离它最近的关键点距离它是否不超过 $r$，这是个经典的多源最短路问题，只需要将每个关键点的初始 $\rm dis$ 设为 $0$ 仍进堆里跑 dijkstra 就能求出。你也可以理解为建了一个向所有关键点连了 $0$ 权边的超级源点，以这个超级源点为源跑最短路。

对于 $k>1$，考虑魔改下 dijkstra，我们对于堆内的每个结点额外记录下这条路径初始是从哪个关键点走来的，更新结点时记录 $k$ 个来自不同关键点的最短路即可，这部分语言描述有点抽象，直接看代码会非常好理解。

对正确性的简要证明：思考 dijkstra 的算法流程，我们每次从堆顶取出来的一定是路径最短的点，因此每个点取出来的 $k$ 种不同源点的路径一定是最短的。

对复杂度的简要证明：同样因为每次在堆顶取出来的是最短路，所以每个点至多被取出来向周围扩展 $k$ 次，复杂度 $O(km\log n)$。

当然我懒得实现精细了，用 multiset 代替了堆，同时记录不同的源点路径用的是 map，可能会稍劣一些。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
using PII = pair<int, int>;
const int N = 5e5 + 5;
int n, m, c, k, r;
vector<PII> G[N];
map<int, bool> vis[N];
struct node{int id, dis, pre;};
bool operator<(const node &a, const node &b){
    return a.dis < b.dis;
}
void dijkstra(){
    multiset<node> st;
    For(i, 1, c) st.insert({i, 0, i});
    while(!st.empty()){
        auto [now, dis, pre] = *st.begin();
        st.erase(st.begin());
        if(vis[now].size() >= k || vis[now].count(pre)) continue;
        vis[now][pre] = 1;
        for(auto [to, val] : G[now]){
            int newd = dis + val;
            if(newd > r || vis[to].size() >= k || vis[to].count(pre)) continue;
            st.insert({to, newd, pre});
        }
    }
}
void Solve(){
    cin >> n >> m >> c >> r >> k;
    For(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    dijkstra();
    vector<int> vec;
    For(i, c + 1, n) if(vis[i].size() >= k)
        vec.emplace_back(i);
    cout << vec.size() << '\n';
    for(int to : vec) cout << to << '\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while(T--) Solve();
    return 0;
}
```

---

## 作者：Rain_cyl (赞：5)

考虑一种特殊情况，若 $K=1$，则只需判断所有目的地是否能被至少一个充电站到达。

加入虚拟源点，向所有充电站连长为 $0$ 的边，然后从虚拟源点开始求最短路，则所有 $\operatorname{dist}[i] \leq R$ 的 $i$ 都可达。

那如果 $K>1$ 呢？由于 $K$ 很小，我们考虑将每个 $i$ 拆点，变为 $(i,s_1),(i,s_2),....,(i,s_k)$，用 $\operatorname{dist}[(i,s_1)]$ 表示从 $s_1$ 这个充电站出发，到达 $i$ 的最短路。

这样，我们在堆顶取出一个 $(u,s)$，就可以更新所有的 $\operatorname{dist}[(j,s)]$(存在边 $u \to j$)。

而如果在某一时刻，已经有 $K$ 个充电站到 $j$ 的距离小于等于 $R$，则接下来不再用 $u$ 更新 $j$，以此保证总点数是 $O(nK)$。

这可以证明是对的：

1. 首先，$j$ 已经满足条件，一定会被记入答案，$j$ 不需要再被更新。
2. 根据 Dijkstra 的性质，先求出的一定是最短路，所以现在已有的 $K$ 个 $(j,s)$ 一定是到 $j$ 距离最短的前 $K$ 个充电站。 那么，若存在边 $j \to v$，且 $K$ 个 $(j,s)$ 都能更新 $v$，则 $v$ 就直接满足条件；若有些 $(j,s)$ 不能更新 $v$，那么我们少记入的那些 $(j,s)$ 就更不能更新 $v$ 了，因为他们长度更长。因此 $j$ 更新其他点不受影响。
   
时间复杂度 $O(Kn\log m)$。
```
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5,M=2e5+5;

int n,m,C,R,K;
int h[N],e[M],ne[M],w[M],idx;
unordered_map<int,bool> start[N];
struct Node{
    int dist,ver,stid;
    bool operator< (const Node &t)const{
        return dist>t.dist;
    }
};

void add(int a,int b,int c){
    e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}

void dijkstra(){
    priority_queue<Node> q;
    for(int i=1; i<=C; i++) q.push({0,i,i});
    while(q.size()){
        auto t=q.top();
        q.pop();
        int u=t.ver,d=t.dist,s=t.stid;
        if(start[u][s]) continue; //如果(u,s)已被更新过，则当前的一定不优
        start[u][s]=1;
        for(int i=h[u]; ~i; i=ne[i]){
            int j=e[i];
            if(d+w[i]>R||start[j].size()>=K) continue;
            q.push({d+w[i],j,s});
        }
    }
}

int main(){
    memset(h,-1,sizeof h);
    scanf("%d%d%d%d%d",&n,&m,&C,&R,&K);
    for(int i=1; i<=m; i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c),add(b,a,c);
    }
    
    dijkstra();
    
    vector<int> res;
    for(int i=C+1; i<=n; i++)
        if(start[i].size()>=K)
            res.push_back(i);
    printf("%d\n",res.size());
    for(int t:res) printf("%d\n",t);
    
    return 0;
}
```

---

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P10193)
## 前言
调了重载函数好久，调成 $94$pts，结果发现是用了 map 超时了，果断换成 unordered_map，通过……
## 思路
题目大意：求 $C$ 后面的点和前 $C$ 个点中的至少有 $K$ 的最短路不超过 $R$ 的点的数量与编号。

容易发现，需要使用 Dijkstra。这里使用了 Dijkstra 求最短路径的优化版（优先队列优化）。

分成以下几步来走：

- 首先是输入和存边，用 vector 存边再熟悉不过。
- 然后走 Dijkstra，注意里面要进行判断，当与其中的 $K$ 个点最短路已经不超过 $R$ 时，就可以结束了。
- 最后遍历一遍，算出满足条件的个数并输出即可。

**二维的标记数组可能会爆内存，所以使用 map 来存。**

这里给一下重载函数：
```cpp
bool operator < (const node &a,const node &b){return a.dis>b.dis;}//重载
```
Djikstra 记得优化，伪代码：
```cpp
while(!q.empty()){
		//保存队顶元素（node 类型内元素分别保存）
        //队顶元素出队
		//走过了->continue 没走过->标记
		for(auto p:g[u]){//遍历
			//存下 pair 类型里的元素（即 v 和 w）
            //下面是判断↓
			if(w+w1>r) continue;//距离太长 
			if(vis[v1].size()>=k) continue;//已经有 k 个充电站了 
			q.push({v1,v,w+w1});//这里满足条件就入队
		}
	}
```
填完空代码如下，含注释：
```cpp
void dijkstra(){//最短路 
	priority_queue <node> q;
	for(int i=1;i<=c;i++) q.push({i,i,0}); 
	while(!q.empty()){
		node f=q.top();q.pop();
		int u=f.x,v=f.y,w=f.dis;
		if(vis[u][v]) continue;vis[u][v]=1;
		for(auto p:g[u]){
			int v1=p.first,w1=p.second;
			if(w+w1>r) continue;//距离太长 
			if(vis[v1].size()>=k) continue;//已经有 k 个充电站了 
			q.push({v1,v,w+w1});
		}
	}
}
```
于是最关键的部分搞定。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e4+5;
int n,m,c,r,k,ans[N],cnt;
map <int,bool> vis[N];
vector <pair<int,int> > g[N];
struct node{int x,y,dis;};
bool operator < (const node &a,const node &b){return a.dis>b.dis;}//重载 
void dijkstra(){//最短路 
	priority_queue <node> q;
	for(int i=1;i<=c;i++) q.push({i,i,0}); 
	while(!q.empty()){
		node f=q.top();q.pop();
		int u=f.x,v=f.y,w=f.dis;
		if(vis[u][v]) continue;vis[u][v]=1;
		for(auto p:g[u]){
			int v1=p.first,w1=p.second;
			if(w+w1>r) continue;//距离太长 
			if(vis[v1].size()>=k) continue;//已经有 k 个充电站了 
			q.push({v1,v,w+w1});
		}
	}
}
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&c,&r,&k);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});//建边 
	}dijkstra();
	for(int i=c+1;i<=n;i++) if(vis[i].size()>=k) ans[++cnt]=i;//计数+保存 
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%lld\n",ans[i]);
	return 0;
}
```
~~撒花！~~

这么快就完了？不要小看蓝题。小细节也给你挖个坑。

> 结果发现是用了 map 超时了，果断换成 unordered_map，通过……

改（因为 unordered_map 内部不排序，所以更快）。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e4+5;
int n,m,c,r,k,ans[N],cnt;
unordered_map <int,bool> vis[N];
vector <pair<int,int> > g[N];
struct node{int x,y,dis;};
bool operator < (const node &a,const node &b){return a.dis>b.dis;}//重载 
void dijkstra(){//最短路 
	priority_queue <node> q;
	for(int i=1;i<=c;i++) q.push({i,i,0}); 
	while(!q.empty()){
		node f=q.top();q.pop();
		int u=f.x,v=f.y,w=f.dis;
		if(vis[u][v]) continue;vis[u][v]=1;
		for(auto p:g[u]){
			int v1=p.first,w1=p.second;
			if(w+w1>r) continue;//距离太长 
			if(vis[v1].size()>=k) continue;//已经有 k 个充电站了 
			q.push({v1,v,w+w1});
		}
	}
}
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&m,&c,&r,&k);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});//建边 
	}dijkstra();
	for(int i=c+1;i<=n;i++) if(vis[i].size()>=k) ans[++cnt]=i;//计数+保存 
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%lld\n",ans[i]);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/220870158)，免得有人不信我，用测试的名号去光明正大的抄代码。

~~撒花。~~

这回是真**撒花！**

---

## 作者：LinkCatTree (赞：2)

为方便，定义 $dis_{i,j}$ 表示节点 $i$ 到 $j$ 的最短路径长度。根据题意，一个点是“交通便利的”当且仅当有至少 $k$ 个充电站到达该点的最短路径长度 $\leq r$。

一个很朴素的想法是以 $c$ 个充电站为源点分别跑一次最短路，但是显然超时。我们发现 $k$ 很小，同时对于某个点 $i$，只需要有 $k$ 个充电站 $j$ 能够满足 $dis_{i,j}\leq r$ 就是“交通便利的”，我们可以仅记录 $k$ 个能够符合要求到达该点的充电站 $j$。

考虑如何转移。我们发现：对于和两个充电站 $j_1,j_2$，如果 $dis_{i,j_1}<dis_{i,j_2}$（$i$ 为当前处理到的点），那么转移 $j_1$ 一定不比转移 $j_2$ 劣。由此得到启发，可以贪心记录最小的 $k$ 个 $j(j\leq c,dis_{i,j}\leq r)$。实现时可以对于每个充电站分开来处理，比 $k$ 个充电站一起转移更加方便。

注意实现时（这里用 `multiset` 实现），为了保证 $dis$ 是最小的 $k$ 个，需要写成这样（大概只有我会这么错吧……）：

```cpp
while(!st.empty()) {
	auto [u,from,dis]=*st.begin();
	// u: 遍历到的节点
	// from：来自哪一个充电站
	// dis：即 dis[u][from]
	// ...
	vec[u].push_back(from);
	// 记录充电站
	for(auto [v,w]:edge[u]) {
		// ...
	}
}
```

而非：

```cpp
while(!st.empty()) {
	auto [u,from,dis]=*st.begin();
	// ...
	for(auto [v,w]:edge[u]) {
		// ...
		vec[u].push_back(from);
		// 这样就保证不了是最小的了
	}
}
```

不要抄[代码](https://www.luogu.com.cn/paste/5creyylr)，我们共建新洛谷。

---

