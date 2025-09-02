# [POI 2010] MOS-Bridges

## 题目描述

San Bytecisco is a beautifully situated coastal town.

It consists of ![](http://main.edu.pl/images/OI17/mos-en-tex.1.png) small, yet densely populated islands,  numbered from ![](http://main.edu.pl/images/OI17/mos-en-tex.2.png) to ![](http://main.edu.pl/images/OI17/mos-en-tex.3.png).

Certain islands are connected with bridges, used for (bidirectional)  road traffic.

Each pair of islands can be connected with at most one bridge.

The islands are connected in such a way that every island can be reached  from every other by using the bridges only.

Byteasar and Bytie are going for a bike trip in San Bytecisco.

The will start their ride at the island no. 1.

They intend to visit every island, while passing along every bridge once  and ending the trip where it began, i.e., the island no. 1.

Being quite seasoned riders, they expect some serious trouble from... the wind!

After all, it is very windy along the coast, and especially so on the bridges between  the islands. Obviously, depending on its speed and direction, the wind makes it  hard to cross the bridge in different extent for either direction.

For simplicity we will assume for every bridge and direction of crossing,  the opposing wind speed is constant.

Help Byteasar and Bytie to find a route as they desire that will in addition  be the least tiresome. Byteasar and Bytie agreed on the maximum opposing wind speed as  a measure of a route's tiresomeness.




## 说明/提示

$2 \le n \le 1000$，$1 \le m \le 2000$，$1 \le a_i,b_i \le n$，$a_i \neq b_i$，$1 \le l_i,p_i \le 1000$


## 样例 #1

### 输入

```
4 4
1 2 2 4
2 3 3 4
3 4 4 4
4 1 5 4```

### 输出

```
4
4 3 2 1```

# 题解

## 作者：Lucky_Glass (赞：21)

## \# 解析
最小化最大权，可以想到二分。

二分得到限制“花费不超过 $c$”，我们发现有一些边的某一个方向被禁了，变成了**有向边**；另一些边两个方向都可以走，是**无向边**（两个方向都被禁了显然不合法）。

判断二分出的答案是否可行，就是判断这个既有无向边又有有向边的图有没有欧拉回路。

无向图的欧拉回路在某种程度上可以转化为有向图的欧拉回路，即给每条边指定一个方向；只要**存在一种指定方向的方案**，使得得到的有向图有欧拉回路，就说明原无向图有欧拉回路。

同样这道题，可以判断“是否存在一种给无向边指定方向的方案，使得新图有欧拉回路”。有向图有欧拉回路的充要条件：

- 弱连通：只要保证二分出的值不会使一条边的两个方向都不能通行即可；
- 每个点，**入度等于出度等于度数的一半**。

由于一个点入度与出度的和一定，只需要考虑出度为其度数的一半。

- 有向边 $u\to v$ 只能固定给 $u$ 提供一个出度；
- 无向边 $(u,v)$ 要么给 $u$ 提供出度要么给 $v$ 提供出度。

于是就可以用网络流来解决，具体来说：

- 原图的边 $i$ 建点 $e_i$，原图的点 $u$ 建点 $p_u$；
- 源点向 $e_i$ 连容量 $1$ 的边，表示一条边只能提供 $1$ 个出度；
- $p_i$ 向汇点连容量为 $\frac{degree(i)}{2}$ 的边，表示该点需要这么多出度；
- 若 $i$ 边有向，则 $e_i$ 向其起始端点 $j$ 对应的 $p_j$ 连容量 $1$ 的边；若无向则向其两端点分别连容量为 $1$ 的边；表示这条边能给哪些点提供出度。

然后跑最大流，每条边都要提供度数——判断最大流是否为 $m$，再看残余网络上哪些 $e_i\to p_j$ 流过了，就可以确定边 $i$ 的指向。最后 DFS 求出有向图欧拉回路的方案即可。

---
## \# 源代码
```cpp
/*Lucky_Glass*/
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
const int N=1e3+10,M=2e3+10,INF=0x3f3f3f3f;
const int NP=N+M,NE=3*M+N;
#define ci const int &
inline int Read(int &r){
	int b=1,c=getchar();r=0;
	while(c<'0' || '9'<c) b=c=='-'? -1:b,c=getchar();
	while('0'<=c && c<='9') r=(r<<1)+(r<<3)+(c^'0'),c=getchar();
	return r*=b;
}

struct EDGE{
	int u,v,tov,tou;
	void Input(){Read(u),Read(v),Read(tov),Read(tou);}
}edg[M];
struct FLOWGRAPH{
	int head[NP],to[NE<<1],nxt[NE<<1],cap[NE<<1],ncnt;
	void Init(ci n){
		for(int i=0;i<=n;i++) head[i]=0;
		ncnt=1;
	}
	void AddEdge(ci u,ci v,ci ca){
		int p=++ncnt,q=++ncnt;
		to[p]=v,nxt[p]=head[u],head[u]=p,cap[p]=ca;
		to[q]=u,nxt[q]=head[v],head[v]=q,cap[q]=0;
	}
	inline int operator [](ci u){return head[u];}
}Fl;
struct GRAPH{
	int head[N],to[M],nxt[M],id[M],ncnt;
	void AddEdge(ci u,ci v,ci i){
		int p=++ncnt;
		to[p]=v,nxt[p]=head[u],head[u]=p;
		id[p]=i;
	}
	inline int& operator [](ci u){return head[u];}
}Gr;
struct QUEUE{
	int ary[NP],ql,qr;
	inline void clear(){ql=1,qr=0;}
	inline void push(ci x){ary[++qr]=x;}
	inline void pop(){ql++;}
	inline bool empty(){return ql>qr;}
	inline int front(){return ary[ql];}
}que;

int n,m,S,T,nans,deg[N],head[NP],dis[NP],tp[N],ans[M];

int Aug(ci u,ci in){
	if(u==T) return in;
	int out=0;
	for(int &it=head[u];it;it=Fl.nxt[it]){
		int v=Fl.to[it];
		if(Fl.cap[it]<=0 || dis[v]!=dis[u]+1) continue;
		int tov=Aug(v,min(in-out,Fl.cap[it]));
		Fl.cap[it]-=tov,Fl.cap[it^1]+=tov;
		out+=tov;
		if(out==in) break;
	}
	return out;
}
bool BFS(){
	for(int i=1;i<=T;i++) head[i]=Fl[i],dis[i]=-1;
	que.clear();
	dis[S]=0,que.push(S);
	while(!que.empty()){
		int u=que.front();que.pop();
		for(int it=head[u];it;it=Fl.nxt[it]){
			int v=Fl.to[it];
			if((~dis[v]) || Fl.cap[it]<=0) continue;
			dis[v]=dis[u]+1;
			if(v==T) return true;
			que.push(v);
		}
	}
	return false;
}
bool Check(ci mid){
	Fl.Init(T);
	int ept=0;
	for(int i=1;i<=n;i++)
		Fl.AddEdge(i,T,deg[i]/2),ept+=deg[i]/2;
	for(int i=1;i<=m;i++){
		Fl.AddEdge(S,n+i,1);
		if(edg[i].tov<=mid) Fl.AddEdge(n+i,edg[i].v,1);
		if(edg[i].tou<=mid) Fl.AddEdge(n+i,edg[i].u,1);
	}
	int out=0;
	while(BFS())
		out+=Aug(S,INF);
	return out==ept;
}
void DFS(ci u,ci las){
	while(Gr[u]){
		int it=Gr[u];Gr[u]=Gr.nxt[it];
		int v=Gr.to[it];
		DFS(v,Gr.id[it]);
	}
	if(las) ans[++nans]=las;
}
int main(){
	// freopen("input.in","r",stdin);
	int lef=0,rig=0;
	Read(n),Read(m),S=n+m+1,T=S+1;
	for(int i=1;i<=m;i++){
		edg[i].Input();
		rig=max(rig,max(edg[i].tou,edg[i].tov));
		lef=max(lef,min(edg[i].tou,edg[i].tov));
		deg[edg[i].u]++,deg[edg[i].v]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]&1){
			printf("NIE\n");
			return 0;
		}
	while(lef+1<rig){
		int mid=(lef+rig)>>1;
		if(Check(mid)) rig=mid;
		else lef=mid;
	}
	int ans;
	if(!Check(lef)) ans=rig,Check(rig);
	else ans=lef;
	printf("%d\n",ans);
	for(int i=1;i<=m;i++)
		for(int it=Fl[i+n];it;it=Fl.nxt[it]){
			if((it&1) || Fl.cap[it]>0) continue;
			int v=Fl.to[it];
			if(v==edg[i].v) Gr.AddEdge(edg[i].u,edg[i].v,i);
			else Gr.AddEdge(edg[i].v,edg[i].u,i);
		}
	DFS(1,0);
	for(int i=m;i>=1;i--) printf("%d%c",::ans[i],i==1? '\n':' ');
	return 0;
}
```

---
## THE END
### Thanks for reading!


---

## 作者：momentous (赞：17)

2021.9.28修了求欧拉回路的锅&精简了内容。

## statement

有 $n(n \leq 1000)$ 个点和 $m(m \leq 20000)$ 条边，每条边有两个权值，分别表示从 $u$ 到 $v$ 和从 $v$ 到 $u$ 的边权。

求图中的一个欧拉回路，使得回路中的最大边权最小，并输出方案。

（不知道欧拉回路的自行百度）

## solution

首先，题目要求最大边权最小的欧拉回路，我们想到二分答案

对于每一个 $mid$ 建出一个图。

图中有有向边和无向边。

欧拉回路有一个性质：**每一个点的入度=出度**。

我们把每一个点分成**入度>出度**和**入度<出度**两类。

建立虚拟源点 $S$ 和汇点 $T$。

若当前点的入度>出度，则它需要多流入**入度-出度**的流量才可能满足**入度=出度**。

若当前点的入度<出度，则它需要多留出**出度-入度**的流量才可能满足**入度=出度**。

等等......

这道题还有无向边，

那我们如何处理呢？

其实很简单，对于 $u \ v$ 之间的无向边，先把它定一个方向（下文假设初始是从 $u$ 到 $v$ 的），

再连一条从 $v$ 连 $u$ 之间流量为1的边，相当于我可以**反悔**。

那么，我们还可以加一个判断：

若有一个点的入度-出度为奇数，则一定无解。

因为改变无向边的方向，该点的入度-出度的值一定还是奇数，即不可能为0，一定无解。

接下来跑最大流，

若源点连向**入度>出度**的点的流量未满，则说明不存在欧拉回路，因为肯定有点的入度≠出度。

若满足此条件，则此 $mid$ 可行。

------------

当二分结束后，我们得到了最终答案 $ans$ 

对于 $ans$ 建出一个有向图

接下来只要找出走的方案就可以了

那如何求呢？

~~其实就是欧拉回路的板子~~

[P7771 欧拉路径](https://www.luogu.com.cn/problem/P7771)

这里面的题解讲的很清楚。

------------

一些需要注意的地方：

首先要判断图的连通性（用并查集即可），不然会被 Hack ，比如

```
6 6
1 2 1 1
2 3 1 1
3 1 1 1
4 5 1 1
5 6 1 1
6 4 1 1
```

但是，孤立点是不用管的，因为欧拉回路只要求经过所有边一次，所以还要判断一下，比如

```
5 4
1 2 1 1
2 3 1 1
3 4 1 1
4 1 1 1
```

还要判断是否有边未被加入，不然会被 [这个帖子](https://www.luogu.com.cn/discuss/show/189647) Hack 。

------------

$\Large\text{Code\  time}$

```cpp
//省略了网络流板子和并查集板子。
#define N 2050
#define M 40050
int deg[N],n,S,T,ALL,m,w1[M],w2[M],u[M],v[M],id[M];
//建图 
bool build(int mid){
    Flow.clear();
    memset(deg,0,sizeof(deg));
    Flow.n=n+2;
    S=n+1;T=n+2;ALL=0;
    for(int i=1;i<=m;++i){
        if(w1[i]<=mid)deg[u[i]]--,deg[v[i]]++;
        if(w2[i]<=mid){
            id[i]=Flow.Top+1;
            Flow.Add(v[i],u[i],1);
        }
    }
    for(int i=1;i<=n;++i)
        if(deg[i]&1)return false;
    for(int i=1;i<=n;++i)//分两类 
        if(deg[i]>0)ALL+=deg[i]/2,Flow.Add(S,i,deg[i]/2);//入度>出度 
        else Flow.Add(i,T,-deg[i]/2);//出度>=入度 
    return true;
}
bool check(int mid){
    if(!build(mid))return false;
    return Flow.dinic(S,T)==ALL;
}
int top;
bool vis[M];
int res[M];
//下面是欧拉回路
void dfs(int x){
    for(int i=head[x];i;i=head[x]){//注意是i=head[x]，不然可以被卡成O(m^2)
        head[x]=i;
        if(vis[e[i].id])continue;
        vis[e[i].id]=1;
        dfs(e[i].to);
        res[++top]=e[i].id;
    }
}
void output(int ans){
    build(ans);
    Flow.dinic(S,T);
    for(int i=1;i<=m;++i){
        if(w1[i]<=ans&&w2[i]<=ans){
            if(Flow.e[id[i]].w==0)add(v[i],u[i],i);
            else add(u[i],v[i],i);
        }else
        if(w1[i]<=ans)add(u[i],v[i],i);
        else if(w2[i]<=ans)add(v[i],u[i],i);
    }
    dfs(1);
    for(int i=top;i>=1;--i)
        printf("%d ",res[i]);
    puts("");
}
bool ok[N],tot;
int main(){
    n=read();m=read();cnt=n;
    int l=1001,r=0,mid,ans=1001;
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i){
        u[i]=read(),v[i]=read(),w1[i]=read(),w2[i]=read();
        ok[u[i]]=1;ok[v[i]]=1;
        Merge(u[i],v[i]);
        if(w1[i]>w2[i]){
            swap(u[i],v[i]);
            swap(w1[i],w2[i]);
        }
        l=min(w1[i],l);r=max(w2[i],r);//防止有边未被加入 
    }
    for(int i=1;i<=n;++i)
    	if(!ok[i])++tot;
    if(cnt!=1&&cnt-tot!=1){//不连通 && 排除孤立点 
        puts("NIE");
        return 0;
    }
    while(l<=r){//二分 
        mid=l+r>>1;
        if(check(mid))
            r=mid-1,ans=mid;
        else l=mid+1;
    }
    if(ans==1001){//无解 
        puts("NIE");
        return 0;
    }
    printf("%d\n",ans);
    output(ans);//输出方案 
    return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

> [P3511 [POI2010] MOS-Bridges](https://www.luogu.com.cn/problem/P3511)

若存在 $2\nmid deg_i$ 则无解。

二分答案，若存在一条边的两个方向均走不了，则当前答案无解，否则一些边的方向已经确定，其余边有两种方向可选择。

考虑有向图存在欧拉回路的充要条件，所有点的出度和入度相等，据此已经可以算出每个点最终的出度。注意到若 $(u, v)$ 定向为 $u\to v$ 则 $u$ 的出度增加 $1$，反之 $v$ 的出度增加 $1$，这自然地给予我们网络流模型：将每条边抽象成点，$S\to e$ 容量 $1$，若 $l\leq mid$ 则 $e\to u$ 容量 $1$，若 $p\leq mid$ 则 $e\to v$ 容量 $1$，$i\to T$ 容量 $\frac{deg_i} 2$，用最大流检查是否存在给所有边定向且满足限制的方案。若存在则当前答案有解，否则无解。

求出最终答案后根据边的定向方案还原有向图，跑欧拉回路即可。时间复杂度 $\mathcal{O}(m\sqrt m\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2.1e4 + 5;
constexpr int M = 7e4 + 5;
struct flow {
  int cnt = 1, hd[N], nxt[N << 1], to[N << 1], limit[N << 1];
  void add(int u, int v, int w) {
    nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w;
    nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0;
  }
  int T, cur[N], dis[N];
  int dfs(int id, int res = 1e9) {
    if(id == T) return res;
    int flow = 0;
    for(int i = cur[id]; i && res; i = nxt[i]) {
      cur[id] = i;
      int it = to[i], c = min(res, limit[i]);
      if(dis[id] + 1 == dis[it] && c) {
        int k = dfs(it, c);
        flow += k, res -= k, limit[i] -= k, limit[i ^ 1] += k;
      }
    }
    if(!flow) dis[id] = -1;
    return flow;
  }
  int maxflow(int s, int t) {
    int flow = 0;
    T = t;
    while(1) {
      queue<int> q;
      memset(dis, -1, sizeof(dis));
      memcpy(cur, hd, sizeof(cur));
      q.push(s), dis[s] = 0;
      while(!q.empty()) {
        int t = q.front();
        q.pop();
        for(int i = hd[t]; i; i = nxt[i])
          if(dis[to[i]] == -1 && limit[i])
            dis[to[i]] = dis[t] + 1, q.push(to[i]);
      }
      if(dis[t] == -1) return flow;
      flow += dfs(s);
    }
  }
} I, g;
int n, m, t, top, stc[N], hd[N], deg[N];
int x[N], y[N], c[N], d[N];
vector<pair<int, int>> e[N];
bool calc(int mid) {
  g = I;
  for(int i = 1; i <= m; i++)
    if(c[i] > mid && d[i] > mid) return 0;
    else {
      if(c[i] <= mid) g.add(i + n, x[i], 1);
      if(d[i] <= mid) g.add(i + n, y[i], 1);
    }
  return g.maxflow(0, t) == m;
}
void dfs(int id) {
  for(int &i = hd[id]; i < e[id].size(); ) {
    auto it = e[id][i++];
    dfs(it.first), stc[++top] = it.second;
  }
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m, t = N - 1;
  for(int i = 1; i <= m; i++) {
    cin >> x[i] >> y[i] >> c[i] >> d[i];
    deg[x[i]]++, deg[y[i]]++;
    I.add(0, i + n, 1);
  }
  for(int i = 1; i <= n; i++)
    if(deg[i] & 1) puts("NIE"), exit(0);
    else I.add(i, t, deg[i] >> 1);
  int l = 1, r = 1e3;
  while(l < r) {
    int mid = l + r >> 1;
    if(calc(mid)) r = mid;
    else l = mid + 1;
  }
  cout << l << "\n";
  calc(l);
  for(int i = 1; i <= m; i++)
    for(int j = g.hd[i + n]; j; j = g.nxt[j]) {
      int it = g.to[j];
      if(it == x[i] && !g.limit[j]) e[x[i]].push_back({y[i], i});
      if(it == y[i] && !g.limit[j]) e[y[i]].push_back({x[i], i});
    }
  dfs(1);
  for(int i = top; i; i--) cout << stc[i] << " ";
  cout << "\n";
  return 0;
}
/*
2022/6/16
start thinking at 19:50
感觉像个网络流啊老哥。
没错，就是网络流，啊哈哈哈。
start coding at 20:08
finish debugging at 20:31
*/
```

---

## 作者：iotang (赞：5)

## 题意翻译

有一个 $n$ 个点，$m$ 条边的无向图。

每条边从两个方向走的权值可能不一样。

在这张图上找到一条最大边权最小的欧拉回路。

如果找到了，按顺序输出这条欧拉回路的边的编号，不管方向。

$n \leq 1000; m \leq 2000$。

## 如何解决它？

### 第一部分

“最大边权最小”，先单走一个二分。

然后……怎么搞呢？

设当前我们只保留权值小于某个数的边。

忽略不合法的边后，我们发现在这个图里面，有一些双向边，还有一些单向边。

这张图就变成了混合图。

看起来，问题变得更复杂了……？

不过，我们现在只要判断，能否在把双向边定向之后，图上有一个欧拉回路。

还记得怎么判断欧拉回路吗？

> 这张图连通，并且没有点的入度和出度不同。

现在，它是我们的有力武器。

现在我们先把图上的双向边随便钦定一个方向。

然后，设点 $i$ 的入度为 $F_i$，出度为 $L_i$。

最终我们是想把某些双向边的方向扭转回来，让所有点 $i$ 满足 $F_i = L_i$。

首先要意识到一点——$F_i$ 和 $L_i$ 的奇偶性要相同。

改变一条边的方向，无非会造成 2 种后果：$F_i \leftarrow F_i + 1, L_i \leftarrow L_i - 1$，或者是 $F_i \leftarrow F_i - 1, L_i \leftarrow L_i + 1$。

明显的，如果 $F_i$ 和 $L_i$ 的奇偶性不相同的话，那么它们就再也没有机会相等了。

假设我们在钦定一条边 $(a,b)$ 的方向的时候，是钦定从 $a$ 到 $b$ 的，那么我们更改它的方向（变成从 $b$ 到 $a$ 的），会造成：

$$
F_a \leftarrow F_a + 1;
L_a \leftarrow L_a - 1;
F_b \leftarrow F_b - 1;
L_b \leftarrow L_b + 1
$$

所以，这怎么搞？

我们把这个问题交给网络流处理。

设 $D_i = \frac{F_i - L_i}{2}$（$F_i - L_i$ 一定能被 $2$ 整除）。

然后上面的那一坨可以重写为，对于每一条双向边 $(a,b)$，反转它之后可以造成

$$
D_a \leftarrow D_a + 1;
D_b \leftarrow D_b - 1
$$

并且我们希望一通操作后所有的 $D_i$ 都为 $0$。

开始愉悦地建图。源点是 $S$，汇点是 $T$。

对于每一条双向边 $(a,b)$（初始方向为从 $a$ 到 $b$），连边 $(b,a,\mathrm{value} = 1)$。

对于每个 $i$，如果 $D_i > 0$，那么连边 $(S,i,\mathrm{value} = D_i)$。否则如果 $D_i < 0$，那么连边 $(i,T,\mathrm{value} = -D_i)$。

单走一个 isap，然后根据残余网络中的流量就可以判断某条边是否被反向了。

### 第二个部分

输出方案。

我们现在已经得到一个有向图，如何找到它的欧拉回路呢？

直接 DFS，会超时，怎么办？

~~出题人应该没有毒到卡欧拉回路的求法，那么我们随机打乱边再 DFS 就完事了！!1~~

用 [UOJ #117](http://uoj.ac/problem/117) 里面的随便一种算法就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef long double louble;

template<typename T1, typename T2> inline T1 max(T1 a, T2 b)
{
	return a < b ? b : a;
}
template<typename T1, typename T2> inline T1 min(T1 a, T2 b)
{
	return a < b ? a : b;
}

const char lf = '\n';

namespace ae86
{
	const int bufl = 1 << 15;

	char buf[bufl], *s = buf, *t = buf;

	inline int fetch()
	{
		if (s == t)
		{
			t = (s = buf) + fread(buf, 1, bufl, stdin);
			if (s == t)return EOF;
		}
		return *s++;
	}

	inline int ty()
	{
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c))a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::ty;

const int _ = 1007, __ = 20007, inf = 0x3f3f3f3f;

struct cxk
{
	int a, b, p, q;
	cxk(int _a = 0, int _b = 0, int _p = 0, int _q = 0)
	{
		a = _a, b = _b, p = _p, q = _q;
	}
};

struct netflow
{
	static const int _n = _ + _, _e = 9999999;

	int to[_e], ne[_e], ev[_e], he[_n], ecnt;

	inline void adde(int a, int b, int c)
	{
		to[++ecnt] = b, ev[ecnt] = c, ne[ecnt] = he[a], he[a] = ecnt;
	}
	inline void addde(int a, int b, int c)
	{
		adde(a, b, c), adde(b, a, 0);
	}

	int S, T, dis[_n], gap[_n], dcnt;

	int dfs(int x, int f)
	{
		if (x == T || !f)return f;
		int r = f, mid = dcnt - 1;
		for (int i = he[x]; i; i = ne[i])
		{
			if (!ev[i])continue;
			int b = to[i];
			if (dis[b] == dis[x] - 1)
			{
				int g = dfs(b, min(r, ev[i]));
				r -= g, ev[i] -= g, ev[i ^ 1] += g;
				if (dis[S] >= dcnt)return f - r;
				if (!r)break;
			}
			mid = min(mid, dis[b]);
		}
		if (f == r)
		{
			if (--gap[dis[x]] == 0)dis[S] = dcnt;
			gap[dis[x] = mid + 1]++;
		}
		return f - r;
	}

	int run(int s, int t)
	{
		S = s, T = t;
		int ans = 0;
		memset(dis, 0, sizeof(dis)), memset(gap, 0, sizeof(gap)), gap[0] = dcnt;
		while (dis[S] < dcnt)ans += dfs(S, inf);
		return ans;
	}

	void cls()
	{
		memset(he, 0, sizeof(he)), ecnt = 1;
		dcnt = 0;
	}

} f;

int n, m, din[_], dout[_];
cxk dlq[__];

int able(int lim)
{
	f.cls(), memset(din, 0, sizeof(din)), memset(dout, 0, sizeof(dout));
	f.dcnt = n;
	int s = ++f.dcnt, t = ++f.dcnt;
	for (int i = 1; i <= m; i++)
	{
		int a = dlq[i].a, b = dlq[i].b, p = dlq[i].p, q = dlq[i].q;
		if (max(p, q) <= lim)dout[a]++, din[b]++, f.addde(b, a, 1);
		else if (p <= lim)dout[a]++, din[b]++;
		else if (q <= lim)dout[b]++, din[a]++;
	}

	int tar = 0;
	for (int i = 1; i <= n; i++)
	{
		int dis = abs(din[i] - dout[i]);
		if (dis & 1)return 0;
		dis >>= 1;
		if (din[i] > dout[i])f.addde(s, i, dis), tar += dis;
		if (din[i] < dout[i])f.addde(i, t, dis);
	}

	return f.run(s, t) == tar;
}

namespace facker
{
	vector<pair<int, int>> e[_];
	inline void adde(int a, int b, int c)
	{
		e[a].emplace_back(b, c);
	}

	int ed[__] = {0}, stk[__] = {0}, top = 0;

	void dfs(int x)
	{
		for (auto i : e[x])
		{
			int a = i.first, b = i.second;
			if (ed[b])continue;
			ed[b] = 1, stk[++top] = b;
			if (a == 1 && top == m)
			{
				for (int j = 1; j <= m; j++)cout << stk[j] << " \n"[j == m];
				exit(0);
			}
			dfs(a), ed[b] = 0, top--;
		}
	}

	void facker(int ans)
	{
		assert(able(ans));

		for (int i = 1, rk = 2; i <= m; i++)
		{
			int a = dlq[i].a, b = dlq[i].b, p = dlq[i].p, q = dlq[i].q;
			if (max(p, q) <= ans)
			{
				if (!f.ev[rk])adde(b, a, i);
				else adde(a, b, i);
				rk += 2;
			}
			else if (p <= ans)adde(a, b, i);
			else if (q <= ans)adde(b, a, i);
		}

		for (int i = 1; i <= n; i++)random_shuffle(e[i].begin(), e[i].end());

		return dfs(1);
	}
}

int main()
{
	ios::sync_with_stdio(0), cout.tie(nullptr);

	random_device rd;
	srand(rd());

	freopen("i.in", "r", stdin);

	int l = 1000, r = 0;

	n = ty(), m = ty();
	for (int i = 1, a, b, c, d; i <= m; i++)
		a = ty(), b = ty(), c = ty(), d = ty(), dlq[i] = cxk(a, b, c, d), l = min(l, min(c, d)), r = max(r, max(c, d));

	int ans = 1001;
	while (r >= l)
	{
		int mid = (l + r) >> 1;
		if (able(mid))ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	if (ans > 1000)cout << "NIE" << lf;
	else cout << ans << lf, facker::facker(ans);

	return 0;
}
```

代码里和谐了一些不好的词语。



---

## 作者：MuelsyseU (赞：2)

> 给定一个图，边有权值且正着走和逆着走有不同权值，在这个图上求一条最大边权最小的欧拉回路，从点 $1$ 出发，要求输出方案。$n\le10^3,m\le2\times10^4$.

一眼二分。考虑限定边权不超过 $mid$，则原图变为含有有向边和无向边。注意这里二分的下界显然为 $\max_{i\in E}\{\min(w_{i,0},w_{i,1})\}$，也就是必须让每条边起码有一个方向可以出现在图中，否则不满足欧拉回路的定义。

但是可以确定的是无论无向边如何走，任何点入度与出度的和不变，记为 $deg_i$。则 $mid$ 可行当且仅当 $\forall i, in_i=out_i=\dfrac{deg_i}{2}$。若 $deg_i$ 为奇数，显然不存在欧拉回路。

考虑建立新图：

1. 额外建立源点、汇点 $S,T$，原图的边 $i$ 对应新图的点 $e_i$，原图的点对应新图点 $p_i$。

1. 对所有原图中的无向边 $e_i=(u,v)$，在新图连流量为 $1$ 的三条边 $(S,e_i),(e_i,p_u),(e_i,p_v)$。

2. 对所有原图中的有向边 $(u,v)$，在新图连流量为 $1$ 的边 $(T,e_i),(e_i,p_u)$。

3. 对所有原图中的点 $u$，在新图连流量为 $\dfrac{deg_u}{2}$ 的边 $(p_u,T)$。

这相当于用各边去给各点**提供出度**。那么显然有解当且仅当 4 中所有边均满流，即取到出度等于 $\dfrac{deg_u}{2}$。

这样即可判定入度等于出度的条件。根据每条无向边对应连向两个节点的哪一条满流，即可得知其方向并建出对应的有向图。根据题意，还需检查 $1$ 是否位于一个包含图中所有边且（弱）连通的连通块。

> 由于数据等原因，上述这个检查几乎没有在题解区中看到，然而这是必要的。

最后在有向图上跑欧拉回路即可。

思考：假如将题中“欧拉回路”改为“欧拉路径”，应如何解决？

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2005, maxm = 80005;
int s, t, n, m, tn, ans, hd[maxn], tot = 1;
int deg[maxn], x[maxm], y[maxm], z[maxm], w[maxm], st[maxn], top;
struct Edg {
	int id, y, nxt;
} e[maxm]; 
inline void add(int id, int x, int y) { e[++tot] = {id, y, hd[x]}, hd[x] = tot; }
namespace Flow {
int hd[maxm], nxt[maxm], ver[maxm], val[maxm], d[maxm], tot = 1;
inline void adf(int x, int y, int z) {
    nxt[++tot] = hd[x], hd[x] = tot, ver[tot] = y, val[tot] = z;
    nxt[++tot] = hd[y], hd[y] = tot, ver[tot] = x, val[tot] = 0;
}
inline void reset() {
	tot = 1;
    memset(hd, 0, sizeof(hd));
    memset(nxt, 0, sizeof(nxt));
}
inline bool bfs() {
    queue<int> q;
    memset(d, 0, sizeof(d));
    q.push(s), d[s] = 1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = hd[x]; i; i = nxt[i]) {
            if (val[i] && !d[ver[i]]) {
                d[ver[i]] = d[x] + 1, q.push(ver[i]);
                if (ver[i] == t) return 1;
            }
        }
    }
    return 0;
}
long long dinic(int x, long long fl) {
    if (x == t) return fl;
    long long now = fl, k;
    for (int i = hd[x]; i && now; i = nxt[i])
        if (val[i] && d[ver[i]] == d[x] + 1) {
            k = dinic(ver[i], min(now, 1ll * val[i]));
            if (!k) d[ver[i]] = 0;
            else val[i] -= k, val[i ^ 1] += k, now -= k;
        }
    return fl - now;
}
inline void init() {
	for (int j = 1; j <= m; ++j) {
		int tmp = x[j] ^ y[j];
    	for (int i = hd[n + j]; i; i = nxt[i])
    		// 判断边的方向. 
    		if (!val[i]) ::add(j, ver[i], tmp ^ ver[i]);
	}
}
};
// 欧拉回路 
bool b[maxm], c[maxn];
inline void dfs(int x, int ed) {
	for (int &i = hd[x]; i; i = e[i].nxt) {
		if (b[i]) continue;
		b[i] = 1, dfs(e[i].y, e[i].id);
	}
	if (ed) st[++top] = ed;
}
int l, r, mid;
bool check(int mid) {
	using namespace Flow;
	reset();
	s = n + m + 1, t = s + 1, ans = 0;
	int ept = 0;
	// e_i = n + i
	for (int i = 1; i <= n; ++i) adf(i, t, deg[i] / 2), ept += deg[i] / 2;
	for (int i = 1; i <= m; ++i) {
		assert(z[i] <= mid);
		adf(s, n + i, 1), adf(n + i, x[i], 1);
		if (w[i] <= mid) adf(n + i, y[i], 1);
	}
	int tmp = 0;
	while (bfs())
		while (tmp = dinic(s, 0x3f3f3f3f)) ans += tmp;
	assert(ept == m);
	return ans == m;
}
void get(int x) {
	c[x] = 1, --tn;
	for (int i = hd[x]; i; i = e[i].nxt)
		if (!c[e[i].y]) get(e[i].y);
}
signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", x + i, y + i, z + i, w + i);
		if (z[i] > w[i]) swap(x[i], y[i]), swap(z[i], w[i]);
		add(i, x[i], y[i]), add(i, y[i], x[i]);
		++deg[x[i]], ++deg[y[i]], l = max(l, z[i]), r = max(r, w[i]);
	}
	// 找有边的子图 
	tn = 0;
	for (int i = 1; i <= n; ++i) tn += !!deg[i];
	// 1. 该子图包含 1 且（弱）连通 
	get(1);
	if (tn) puts("NIE"), exit(0);
	// 2. 度数 
	for (int i = 1; i <= n; ++i)
		if (deg[i] & 1) puts("NIE"), exit(0);
	--l;
	while (l + 1 < r) {
		mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid;
	}
	if (check(r)) printf("%d\n", r);
	else puts("NIE"), exit(0);
	tot = 1, memset(hd, 0, sizeof(hd));
	Flow::init(), dfs(1, 0);
	while (top) printf("%d ", st[top--]); 
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：2)

- 本来以为转化为欧拉回路之后会有不错的接近线性的做法的，没想到最后居然是网络流。
- 欲哭无泪，~~所以是不是可以用网络流求解无向图欧拉回路~~。

**[题意](https://www.luogu.com.cn/problem/P3511)**
- 给定一个图，边有权值且正着走和逆着走有不同权值，在这个图上求一条最大边权最小的欧拉回路，从点 $1$ 出发，要求输出方案。

**分析**
- 考虑二分答案，就变成了欧拉回路问题，不过有的边是有向边，有的边是无向边，很快你就会发现，针对单独的有向图和无向图的算法在这里都无法派上用场。
- 我们尝试枚举每条无向边的方向判断是否可以是欧拉回路，你发现有向图存在欧拉回路的判定居然十分简洁：忽略边方向连通（完全可以一开始判定），入度与出度相等（这太数值化了）。
- 经过一些奇妙的脑回路之后你容易想到一个网络流的判定方法：初始时先随机定向，将每个点的入度与出度之差设为点权（显然，点权首先必须都是偶数，因为定向不会改变奇偶性，这点可以先特判，容易发现，点权的意义是合法流流入和流出的流量差），正权点连超级源，容量为权值，负权点连超级汇，容量为权值相反数，然后每条无向边连向原方向的反方向，流量为 $2$，跑一遍最大流。
- 如果存在合法方案那么最大流一定把源点和汇点的直连边满流，同样，由于增广路等常见最大流算法的特性，每条边的流量都是偶数，故方案一定合法，[代码](https://www.luogu.com.cn/paste/dru08rou)。

---

## 作者：FutaRimeWoawaSete (赞：2)

典型的知道性质就会做题。            

考虑答案具有单调性，所以我们直接二分答案后判断能否构造出一个欧拉回路就好了。                 

原图是无向图欧拉回路，在二分之后图上产生了一些有向边，但是每条边还是只能走一次，所以我们得把问题转化一下：图上有一些未定向的无向边和一些有向边，请对所有无向边定向后求出一组有向图欧拉回路的解。            

考虑有向图欧拉回路性质：每个点的入度等于出度等于总度数的一半。      

用网络流进行构造。每个点 $i$ 向 $t$ 连一条容量为 $\frac{deg(i)}{2}$ 的边表示它需要的出度，这样只需要到时跑完最大流看一下答案是不是 $\sum_{i = 1} ^ n \frac{deg(i)}{2}$ 即可。             

这里有一个小的注意点，你得先判断原无向图有没有解，不然应该会被卡一两个点。              

接着对于每条边视为一个点 $ed_i$，从源点 $s$ 向 $ed_i$ 连一条容量为 $1$ 的边表示 $ed_i$ 可以提供一个出度。

若边 $(x,y)$ 定向了， $ed_i$ 就直接对产生出度的那个点连一条容量为 $1$ 的边即可。

若边 $(x,y)$ 没有定向，向两个点都连一条容量为 $1$ 的边。          

然后直接跑最大流即可，判完答案合法后就看一下每条边是留给了那个点后重新建图，现在就是一个有向图直接搜一个欧拉回路出来就好了。

还需要特判一下二分答案后每条边是不是两边都不能走，虽然不特判网络流流不满也可以直接判断，但是保险起见还是加上为好。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5 , Inf = 1e9;
int n,m,head[Len],cnt,dep[Len],cur[Len],s,t,maxn,deg[Len],smrmm,IIn[Len],OOut[Len],st[Len];
struct nnode
{
	int to,id,vis;
	nnode(){to = id = vis = 0;}
	nnode(int TO,int ID,int VIS){to = TO , id = ID , vis = VIS;}
};
bool cmp(nnode x,nnode y){return x.to < y.to;} 
vector<nnode> v[Len];
vector<int> used,Print;
struct Node
{
	int x,y,w,ww;
	Node(){x = y = w = ww = 0;}
	Node(int X,int Y,int W,int WW){x = X , y = Y , w = W , ww = WW;}
}Edge[Len];
struct node
{
	int next,to,w;
}edge[Len << 1];
void add(int from,int to,int w)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].w = w;
	head[from] = cnt;
	swap(to , from);
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].w = 0;
	head[from] = cnt;
}
bool BFS()
{
	queue<int> q;
	for(int i = 1 ; i <= t ; i ++) dep[i] = 0;
	dep[s] = 1 , cur[s] = head[s];q.push(s);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int e = head[p] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			if(!dep[to] && edge[e].w)
			{
				dep[to] = dep[p] + 1;
				cur[to] = head[to];
				q.push(to);
			}
		}
	}
	return dep[t];
}
int dfs(int u,int In)
{
	if(u == t) return In;
	int Out = 0;
	for(int e = cur[u] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(edge[e].w && dep[to] == dep[u] + 1)
		{
			int res = dfs(to , min(In , edge[e].w));
			In -= res;
			Out += res;
			edge[e].w -= res;
			edge[e ^ 1].w += res; 
		}
	}
	if(!Out) return dep[u] = 0;
	return Out;
}
void DFS(int x)
{
	for(int i = 0 ; i < v[x].size() ; i = max(i + 1 , st[x]))
	{
		int to = v[x][i].to;
		if(v[x][i].vis) continue;
		v[x][i].vis |= 1;
		st[x] = i + 1;
		DFS(to);
		used.push_back(v[x][i].id);
	}
}
bool check(int Val)
{
	int Cnt = 0;maxn = n;used.clear();cnt = 1;memset(head , 0 , sizeof head);
	for(int i = 1 ; i <= m ; i ++)
	{
		if(Edge[i].w > Val && Edge[i].ww > Val) return 0;
		if(Edge[i].w <= Val || Edge[i].ww <= Val) maxn ++;
		if(Edge[i].w <= Val) add(maxn , Edge[i].x , 1);
		if(Edge[i].ww <= Val) add(maxn , Edge[i].y , 1);
	}
	s = maxn + 1 , t = maxn + 2;
	for(int i = n + 1 ; i <= maxn ; i ++) add(s , i , 1);
	for(int i = 1 ; i <= n ; i ++) add(i , t , deg[i] / 2);
	int as = 0;
	while(BFS()) as += dfs(s , Inf);
	if(as != smrmm) return 0;
	for(int i = 1 ; i <= n ; i ++) OOut[i] = IIn[i] = 0 , v[i].clear();
	for(int qs = head[s] ; qs ; qs = edge[qs].next)
	{
		int i = edge[qs].to;
		if(edge[qs].w == 0)
		{
			for(int e = head[i] ; e ; e = edge[e].next)
			{
				int to = edge[e].to;
				if(!edge[e].w)
				{
					int sim = i - n;//edge's id
					if(Edge[sim].x == to) 
					{
						v[Edge[sim].x].push_back(nnode(Edge[sim].y , sim , 0));
						OOut[Edge[sim].x] ++ , IIn[Edge[sim].y] ++;
					}
					else 
					{
						v[Edge[sim].y].push_back(nnode(Edge[sim].x , sim , 0)); 
						OOut[Edge[sim].y] ++ , IIn[Edge[sim].x] ++;
					}
				}	
			}
		}
	}
	//puts("");
	//printf("???%d\n",Val);
	for(int i = 1 ; i <= n ; i ++)
	{
		//printf("%d %d\n",OOut[i],IIn[i]);
		sort(v[i].begin() , v[i].end() , cmp);
		//for(int j = 0 ; j < v[i].size() ; j ++) printf("%d %d\n",i,v[i][j].to); 
		st[i] = 0;
	}
	//puts("");
	DFS(1);
	swap(used , Print); 
	return 1;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++) 
	{
		scanf("%d %d %d %d",&Edge[i].x,&Edge[i].y,&Edge[i].w,&Edge[i].ww);
		deg[Edge[i].x] ++ , deg[Edge[i].y] ++;
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(deg[i] % 2 == 1) return puts("NIE") & 0;
		smrmm += deg[i] / 2;
	}
	int l = 0 , r = 1001 , anss = 1001;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			anss = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	if(anss == 1001) return puts("NIE") & 0;
	printf("%d\n",anss);
	for(int i = Print.size() - 1 ; i >= 0 ; i --) printf("%d ",Print[i]);
	return 0;
} 
```

---

## 作者：撤云 (赞：2)


[戳我食用效果更佳](https://www.cnblogs.com/hbxblog/p/11098058.html)

### $Solution$

这道题因为没有$spj$,所以很多人都应该没有过

这里只讲一讲第一问的做法

看到"最大值最小"，就知道应该要二分

二分之后，对于每个$mid$,只要计算小于$mid$的边，然后在剩下的图中判断有无欧拉回路

但这个图是一个混合图.

先对每条无向边随意的定向，统计每个点入度和出度的差，如果有一个点的入度和出度的奇偶性不同，那么就肯定无解（而改变无向边方向的话，会让它们的入读$-$出度变化$2$，则他们的差无法变为$0$,所以无法相同）

如果入度$-$出度$=x$，若$x < 0$,就向$t$连一条$abs(x/2)$ 的边，否则就从源点连一条$abs(x/2)$的边，对于原来定向的无向边$(a,b)$,建立一条从$b$到$a$，容量为$1$(这个表示的意义时将$a->b$这一条边变成了从$b->a$)

流一条流就代表将一条无向边反向

如果满流则存在欧拉回路

### $Code$

``` cpp
#include<bits/stdc++.h>
#define rg register
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
const int inf=1e9;
int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return f*x;
}
struct node{
    int to,next,v;
}a[200001];
int head[20001],cnt=1,n,m,s,t,x,y,z,minx,maxx,dep[20001];
void add(int x,int y,int c){
    a[++cnt].to=y,a[cnt].next=head[x],a[cnt].v=c,head[x]=cnt;
    a[++cnt].to=x,a[cnt].next=head[y],a[cnt].v=0,head[y]=cnt;
}
queue<int> q;
int bfs(){
    memset(dep,0,sizeof(dep));
    q.push(s);
    dep[s]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=head[now];i;i=a[i].next){
            int v=a[i].to;
            if(!dep[v]&&a[i].v>0)
                dep[v]=dep[now]+1,q.push(v);
        }
    }
    if(dep[t])
        return 1;
    return 0;
}
int dfs(int k,int list){
    if(k==t||!list)
        return list;
    for(int i=head[k];i;i=a[i].next){
        int v=a[i].to;
        if(dep[v]==dep[k]+1&&a[i].v>0){
            int p=dfs(v,min(list,a[i].v));
            if(p){
                a[i].v-=p;
        a[i^1].v+=p;
                return p;
            }
        }
    }
    return dep[k]=0;
}
int Dinic(){
    int ans=0,k;
    while(bfs())
        while((k=dfs(s,inf)))
            ans+=k;
    return ans;
}
int A[20001],B[20001],C[20001],D[20001],vis[10001],tot;
bool build(int x){
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	s=0,t=n+1,cnt=1,tot=0;
	for(int i=1;i<=m;i++){
		if(C[i]<=x) vis[A[i]]--,vis[B[i]]++;
		if(D[i]<=x) add(B[i],A[i],1);
	}
	for(int i=1;i<=n;i++)
		if(vis[i]&1)
			return 0;
	for(int i=1;i<=n;i++){
		if(vis[i]>0)
			tot+=vis[i]/2,add(s,i,vis[i]/2);
		else add(i,t,-vis[i]/2);
	}
	return 1;
}
bool check(int x){
	bool res=build(x);
	if(!res) return 0;
	return Dinic()==tot;
}
int main(){
	n=read(),m=read(),minx=2147483647,maxx=0;
	for(int i=1;i<=m;i++){
		A[i]=read(),B[i]=read(),C[i]=read(),D[i]=read();
			if(C[i]>D[i])
		swap(A[i],B[i]),swap(C[i],D[i]);
		minx=min(C[i],minx),maxx=max(maxx,D[i]);	
	}
	int l=minx,r=maxx,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid-1,ans=mid;
		else l=mid+1;
	}
	if(!ans) puts("NIE"),exit(0);
	printf("%d",ans);
    return 0;
}
```

---

## 作者：UperFicial (赞：1)

[传送门](https://www.luogu.com.cn/problem/P3511)。

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16175251.html)。

### $\texttt{Description}$

每条边正向和反向有两个权值，求最大边权尽量小的欧拉回路。

$1\le n\le 10^3$，$1\le m\le 2\times 10^3$。

### $\texttt{Solution}$

[前置芝士](https://www.luogu.com.cn/problem/P7771)。

~~一道题，没有烟，一道毒瘤调一天。~~

聪明的你学会了前置芝士，知道了无解的一个充分条件是，每个点的入度都为偶数。

看到最大边权尽量小，条件反射出二分答案。

我们就不妨二分最大的边权 $k$，那么原图中边权大于 $k$ 的边都不用管。

看到 $n,m$ 稍大，考虑构建一个二分图：左边是边，右边是点。

我们寄 $in_i$ 表示 $i$ 点的入度，显然 $in_i$ 是偶数。

则到达这个点边的数量一定等于从这个点出发的边的数量。

所以从 $i$ 点流出的流量，即流向 $t$ 的流量，一定是 $\frac{in_i}{2}$，有一半是流入的。

根据欧拉回路的定义，每一条边只能匹配一次，所以可以把 $s$ 向每一条边连一条容量为 $1$ 的边。

边和点的连边也很简单了，我们对于原图的一条边 $(u,v,w_1,w_2)$，如果 $w_1\le k$，则 $u$ 可以到达 $v$，也就是说这条边可以流到 $v$ 这里。则这条边向 $v$ 连一条容量为 $1$ 的边。$w_2$ 的情况也同理。

跑一遍最大流，只需要判断最大流是否满流即可。也就是 $\frac{1}{2}\sum in_i$。

对于输出方案，我们枚举每一条边 $i$，如果 $i\to v_i$ 的残余流量为 $0$，说明这条边是选择的，也就是 $u_i\to v_i$ 是被选择的，直接建一张新图，把这条边加进去就行了；$i\to u_i$ 残余流量为 $0$ 的情况也一样。

最后只需要在新图中找一条欧拉路径，模板题了吧。。。。。

核心代码：

```cpp
inline void remake()
{
	Clear(head),Clear(edge);
	tot=1;
	return;
}
int in[MAXN];
inline bool check(int k)
{
	remake();
	int all(0);
	rep(i,1,n) add_edge(i+m,t,in[i]>>1),all+=(in[i]>>1);
	rep(i,1,m)
	{
		add_edge(s,i,1);
		if(a[i].w1<=k) add_edge(i,a[i].y+m,1);
		if(a[i].w2<=k) add_edge(i,a[i].x+m,1);
	}
	int ans(0);
	while(bfs()) ans+=dfs(s,INF);
	return ans==all;
}
int out[MAXN],p;
bool vis[MAXN];
inline void Find(int u,int lst)
{
	while(head2[u])
	{
		E e=edge2[head2[u]];
		head2[u]=e.nxt;
		Find(e.to,e.flow);
	}
	if(lst) out[++p]=lst;
}
int main()
{
	n=read(),m=read();
	s=0,t=n+m+1;
	rep(i,1,m) 
	{
		a[i].x=read(),a[i].y=read(),a[i].w1=read(),a[i].w2=read();
		++in[a[i].x],++in[a[i].y];
	}
	rep(i,1,n) if(in[i]&1)
	{
		puts("NIE");
		return 0;
	}
	int l=1,r=1000,res(-1);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	if(res==-1)
	{
		puts("NIE");
		return 0;
	}
	printf("%d\n",res);
	check(res);
	rep(i,1,m)
		gra(j,i)
		{
			E e=edge[j];
			if(e.to!=s&&(!e.flow))
			{
				if(e.to-m==a[i].y) add_edge2(a[i].x,a[i].y,i);
				else add_edge2(a[i].y,a[i].x,i);
			}
		}
	Find(1,0);
	rep(i,1,p) printf("%d ",out[p-i+1]);
	return 0;
}
```
$$\texttt{The End.by UF}$$

---

## 作者：Arghariza (赞：0)

其实这题有两种建模方法，因为我都写了，所以两个都讲好了。

一眼二分答案，转为判定性问题：

> 给定含有**无向边和有向边**的图 $G$，判断是否存在欧拉回路。

首先先判掉存在 $u$，$2\nmid \text{deg}_u$ 的情况。

不能简单地根据度数判断，考虑网络流建模。

- 方法 $1$：

考虑到对于每条边 $e_i$，最多给一个点会提供 $1$ 的出度。

然后对于一个点 $v_i$，最后它的出度一定为 $\frac{\text{deg}_{v_i}}{2}$。

这启示我们将边和点两两匹配。那我们对于 $S\to e_i$，连流量为 $1$ 的边，表示这条边最多匹配 $1$ 个点给出度。对于 $v_i\to T$，连流量为 $\frac{\text{deg}_{v_i}}{2}$ 的边，表示这个点要匹配这么多条边给它出度。对于一条边 $e_i=(u,v)$，如果单向，不妨设 $u\to v$，那么直接 $e_i$ 向 $u$ 流 $1$。否则 $e_i$ 向 $u,v$ 分别流 $1$，表示 $e_i$ 既可以匹配 $u$，也可以匹配 $v$。

然后我们跑最大流，判断是否满流即可。最后构造方案可以在残量网络上根据是否有 $e_i\to u_i$ 建图跑欧拉回路。

- 方法 $2$：

先给每条无向边随意定一个方向，假定是 $u\to v$，计算此时每个点的入度 $\text{in}_u$ 和出度 $\text{out}_u$。

那么对于 $\text{in}_u>\text{out}_u$ 的点，我们将 $S$ 向 $u$ 连流量 $\frac{\text{in}_u-\text{out}_u}{2}$ 的边。表示它需要流入这么多流量才能使 $\text{in}_u=\text{out}_u$。

同理，对于 $\text{in}_v<\text{out}_v$ 的点，我们将 $v$ 向 $T$ 连流量 $\frac{\text{out}_v-\text{in}_v}{2}$ 的边。表示它需要流出这么多流量才能使 $\text{in}_v=\text{out}_v$。

对于无向边 $(u,v)$，我们假定了 $u\to v$。那么 $v\to u$ 连一条流量为 $1$ 的边，表示我们可以反悔。

然后同样跑最大流，判断是否满流，然后构造有向图跑欧拉回路即可。

---

方法 $2$ 的代码，自以为写得十分清新。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define pc putchar
    #define pi pair<int, int>
    #define tu3 tuple<int, int, int>
    #define tu4 tuple<int, int, int, int>
    #define mp make_pair
    #define mt make_tuple
    #define fi first
    #define se second
    #define pb push_back
    #define ins insert
    #define era erase
    inline int read () {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}
using vbzIO::read;
using vbzIO::write;

const int maxn = 5e3 + 100;
const int maxm = 5e4 + 200;
struct edg { int u, v, w1, w2; } ed[maxn];
struct edge { int to, nxt, w; } e[maxn + maxm];
struct node { int to, nxt, w; } g[maxm];
int n, m, s, t, tot = 1, l, r, ans = -1;
int head[maxn], fa[maxn], sz[maxn], deg[maxn], id[maxm], dep[maxn], vis[maxm];

void add_edge(int u, int v, int w) { e[++tot] = (edge) { v, head[u], w }, head[u] = tot; }
void add_edg(int u, int v, int w) { g[++tot] = (node) { v, head[u], w }, head[u] = tot; }
void add_flow(int u, int v, int w) { add_edge(u, v, w), add_edge(v, u, 0);  }
int getf(int x) { return fa[x] == x ? x : fa[x] = getf(fa[x]); }
void mrg(int x, int y) {
	x = getf(x), y = getf(y);
	if (x == y) return;
	fa[x] = y, sz[x] += sz[y];
}

bool bfs() {
	queue<int> q;
	memset(dep, 0, sizeof(dep));
	dep[s] = 1, q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && !dep[v]) 
				dep[v] = dep[u] + 1, q.push(v);
		}
	}
	return dep[t];
}

int dfs(int u, int in) {
	if (u == t) return in;
	int out = 0;
	for (int i = head[u]; i && in; i = e[i].nxt) {
		int v = e[i].to;
		if (e[i].w && dep[v] == dep[u] + 1) {
			int res = dfs(v, min(in, e[i].w));
			in -= res, out += res;
			e[i].w -= res, e[i ^ 1].w += res;
		}
	}
	if (!out) dep[u] = 0;
	return out;
}

bool chk(int x) {
	for (int i = 1; i <= n; i++) deg[i] = 0;
    for (int i = 0; i <= t; i++) head[i] = 0;
    tot = 1;
	for (int i = 1; i <= m; i++) {
		int u = ed[i].u, v = ed[i].v;
		if (ed[i].w1 <= x) deg[u]--, deg[v]++;
		if (ed[i].w2 <= x) id[i] = tot + 1, add_flow(v, u, 1);
	}
    for (int i = 1; i <= n; i++)
    	if (deg[i] & 1) return 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
    	if (deg[i] > 0) sum += deg[i] / 2, add_flow(s, i, deg[i] / 2);
    	else add_flow(i, t, -deg[i] / 2);
	}
	while (bfs()) sum -= dfs(s, 1e9);
	return sum == 0;	
}

stack<int> tp;
void eul(int u, int lst) {
	for (int i = head[u]; i; i = head[u]) {
		head[u] = g[i].nxt;
		eul(g[i].to, g[i].w);
	}
	if (lst) tp.push(lst);
}

int main() {
	n = read(), m = read(), t = n + 1;
	for (int i = 1; i <= m; i++) {
		ed[i] = (edg) { read(), read(), read(), read() };
		if (ed[i].w1 > ed[i].w2) swap(ed[i].u, ed[i].v), swap(ed[i].w1, ed[i].w2);
		l = max(l, ed[i].w1), r = max(r, ed[i].w2), mrg(ed[i].u, ed[i].v);
	}
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= n; i++)  
		if (getf(i) == i) c1++, c2 += (sz[i] == 1);
	if (c2 >= 1 && c2 != c1 - 1) return puts("NIE"), 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (chk(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	if (ans == -1) return puts("NIE"), 0;
	write(ans), puts("");
	chk(ans);
	tot = 0;
	for (int i = 1; i <= n; i++) head[i] = 0;
	for (int i = 1; i <= m; i++) {
		if (ed[i].w2 > ans) add_edg(ed[i].u, ed[i].v, i);
		else {
			if (e[id[i]].w) add_edg(ed[i].u, ed[i].v, i);
			else add_edg(ed[i].v, ed[i].u, i);
		}
	}
	eul(1, 0);
	while (tp.size()) write(tp.top()), pc(' '), tp.pop();
	return 0;
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://www.cmsblog.top/archives/poi2010mos-bridges)

## 题目描述

[洛谷传送门](https://www.luogu.com.cn/problem/P3511)

[LOJ 传送门](https://loj.ac/p/2460)

## 思路

好恶心好恶心的网络瘤题，属于是知道结论就会做但是会写挂的题，佩服出题人脑洞。

**性质：对于一条欧拉回路，每个点的入度 = 出度**

首先可以考虑二分答案，二分最小权值 $x$，对于每个 $x$，我们可以建出一张图来，在这张图中，我们把所有不符合条件的边砍掉（变成有向边，**记得判断联通**）。

考虑先处理有向边：

把所有的点分类，可以分为**入度 > 出度** 和 **入度 < 出度** 两类，然后建立源点和汇点。

对于一个入度 > 出度的点，源点向它连一条 **（入度 - 出度）/ 2** 的边；

对于一个入度 < 出度的点，它向汇点连一条 **（出度 - 入度）/ 2** 的边。

接下来考虑无向边：

对于无向边 $(u,v)$，我们可以钦定一个方向（假设为 $u \to v$），然后连一条 $v \to u$ 容量为 $1$ 的边即可。

然后注意判断存在 入度-出度 为奇数边则一定无解。

接下来跑网络流。

然后扫描残量网络，如果 入度 > 出度的点未满流，则无解。

然后我们就得到了第一问的答案，根据这个答案建图求欧拉回路即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e3 + 10;
const int MAXM = 40010;
const int INF = 0x3f3f3f3f;

int N, M, L, R, Ans = 1001;
int U[MAXM], V[MAXM], W1[MAXM], W2[MAXM];

int Fa[MAXN];
int Cnt, ToT;

int Find(int u) {
	return Fa[u] == u ? Fa[u] : Fa[u] = Find(Fa[u]);
}

void Merge(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) {
		Cnt--;
		Fa[x] = y;
	}
}

bitset<1010> Used;

class MF {
public:
	int Head[MAXN << 1];
	struct _ {
		int To , Next , Value;
	} G[MAXM << 1];
	int Cnt = 1;
	
	void _add(int u , int v , int w) {
		G[++Cnt].To = v;
		G[Cnt].Next = Head[u];
		G[Cnt].Value = w;
		Head[u] = Cnt;
	}
	
	int Depth[MAXN] , Hash[MAXN];
	
	void BFS() {
		memset(Depth , -1 , sizeof Depth);
		memset(Hash , 0 , sizeof Hash);
		Depth[T] = 0;
		Hash[0]++;
		queue<int> q;
		q.push(T);
		
		while(q.size()) {
			int u = q.front();
			q.pop();
			for(int i = Head[u]; i ; i = G[i].Next) {
				int v = G[i].To;
				if(Depth[v] != -1) continue;
				Depth[v] = Depth[u] + 1;
				Hash[Depth[v]]++;
				q.push(v);
			}
		}
		return;
	}
	
	int Max_flow = 0;
	
	int DFS(int u , int flow) {
		if(u == T) {
			Max_flow += flow;
			return flow;
		}
		
		int used = 0;
		for(int i = Head[u]; i; i = G[i].Next) {
			int v = G[i].To;
			if(G[i].Value && Depth[v] == Depth[u] - 1) {
				int Min = DFS(v , min(G[i].Value , flow - used));
				if(Min) {
					G[i].Value -= Min;
					G[i ^ 1].Value += Min;
					used += Min;
				}
				if(used == flow) {
					return used;
				} 
			}
		}
		
		Hash[Depth[u]]--;
		if(Hash[Depth[u]] == 0) Depth[S] = T + 1;
		Depth[u]++;
		Hash[Depth[u]]++;
		return used;
	}

	int S, T;
	void Add(int u , int v , int w) {
		_add(u , v , w);
		_add(v , u , 0);
	}
	void clear() {
		memset(Head, 0, sizeof Head);
		Cnt = 1;
	}
	int ISAP() {
		Max_flow = 0;
		BFS();
		while(Depth[S] < T + 1) DFS(S , INF);
		return Max_flow;
	}
	int GetSize() {
		return Cnt;
	}
} Flow;

int Degree[MAXN], Id[MAXN];

bool Build(int mid) {
	Flow.clear();
	memset(Degree, 0, sizeof Degree);
	Flow.S = N + 1;
	Flow.T = N + 2;
	ToT = 0;
	for (int i = 1; i <= M; i++) {
		if (W1[i] <= mid) {
			Degree[U[i]]--;
			Degree[V[i]]++;
		}
		if (W2[i] <= mid) {
			Id[i] = Flow.GetSize() + 1;
			Flow.Add(V[i], U[i], 1);
		}
		if (W1[i] > mid) return false;
	}
	for (int i = 1; i <= N; i++) {
		if (Degree[i] & 1) {
			return false;
		}
	}
	for (int i = 1; i <= N; i++) {
		if (Degree[i] > 0) {
			ToT += Degree[i] / 2;
			Flow.Add(Flow.S, i, Degree[i] / 2);
		} else {
			Flow.Add(i, Flow.T, -Degree[i] / 2);
		}
	}
	return true;
}

bool Check(int x) {
	bool res = Build(x);
	if (!res) return false;
	return Flow.ISAP() == ToT;
}

stack<int> Stack[MAXN], res;

void Euler(int u) {
	while (!Stack[u].empty()) {
		int i = Stack[u].top();
		Stack[u].pop();
		Euler(U[i] ^ V[i] ^ u);
		res.push(i);
	}
}

bool Vis[MAXN];

void GetAns() {
	Build(Ans);
	Flow.ISAP();
	for (int i = 1, u, v; i <= M; i++) {
		u = U[i];
		v = V[i];
		if (W1[i] <= Ans && W2[i] <= Ans) {
			if (Flow.G[Id[i]].Value) Stack[u].push(i);
			else Stack[v].push(i);
		} else {
			if (W1[i] <= Ans) Stack[u].push(i);
			else if (W2[i] <= Ans) Stack[v].push(i);
		}
	}
	Euler(1);
	while (res.size()) {
		cout << res.top() << " ";
		res.pop();
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> M;
	L = 1001, R = 0, Cnt = N;
	
	for (int i = 1; i <= N; i++) Fa[i] = i;
	
	for (int i = 1; i <= M; i++) {
		cin >> U[i] >> V[i] >> W1[i] >> W2[i];
		Used[U[i]] = 1;
		Used[V[i]] = 1;
		if (W1[i] > W2[i]) {
			swap(U[i], V[i]);
			swap(W1[i], W2[i]);
		}
		Merge(U[i], V[i]);
		L = min(W1[i], L);
		R = max(W2[i], R);
	}
	
	for (int i = 1; i <= N; i++) {
		if (!Used[i]) {
			ToT++;
		}
	}

	if (Cnt - ToT != 1 && Cnt != 1) {
		cout << "NIE" << endl;
		return 0;
	}
	while (L <= R) {
		int mid = L + R >> 1;
		if (Check(mid)) {
			R = mid - 1;
			Ans = mid;
		} else {
			L = mid + 1;
		}
	}

	if (Ans == 1001) {
		cout << "NIE" << endl;
		return 0;
	}
	
	cout << Ans << endl;
	GetAns();
	return 0;
}
```

---

