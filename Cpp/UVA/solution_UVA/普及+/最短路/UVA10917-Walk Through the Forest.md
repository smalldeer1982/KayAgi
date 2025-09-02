# Walk Through the Forest

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1858

[PDF](https://uva.onlinejudge.org/external/109/p10917.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10917/2cdbcbd2041975ba19703cf570f7a4087f3eb461.png)

## 样例 #1

### 输入

```
5 6
1 3 2
1 4 2
3 4 3
1 5 12
4 2 34
5 2 24
7 8
1 3 1
1 4 1
3 7 1
7 4 1
7 5 1
6 7 1
5 2 1
6 2 1
0```

### 输出

```
2
4```

# 题解

## 作者：EnochWenzhou (赞：6)

这题我是用两次堆优化dij求得（这种奇葩方法竟然还没人想到）


“存在一条从B出发的回到家方案比任何从A出发回到家的方案花费的时间都要短。”


意思即为B到2的最短路比A的短。因此要先走一遍最短路从2到每个点（双线边方向不管），因此就使用了一次dij。

之后再跑一遍最短路不过这次优先队列中存的是每个点的最短路，因为只要先遍历最短路较大的就能保证不会有前边遍历的会被后边遍历的更新因为后边的最短路必然比前边的小。

因此再跑一遍最短路即可。

AC：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a1,b1,c1,cnt,to[2000010],val[2000010],nxt[2000010],first[1010],d[1010],f[1010],v[1010];
priority_queue< pair < int , int > > q;
void addedge(int x,int y,int z){
	cnt++;
	to[cnt]=y;
	val[cnt]=z;
	nxt[cnt]=first[x];
	first[x]=cnt;
}
void dij1(){//第一次普通的最短路
	memset(d,0x7f,sizeof(d));
	memset(v,0,sizeof(v));
	d[2]=0;
	while(q.size()) q.pop();
	q.push(make_pair(0,2));
	while(q.size()){
		int x=q.top().second;q.pop();
		if(v[x]) continue;
		v[x]=1;
		for(int i=first[x];i;i=nxt[i]){
			int y=to[i],z=val[i];
			if(d[y]>d[x]+z){
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
		}
	}
}
void dij2(){//第二次跑最短路
	memset(v,0,sizeof(v));
	memset(f,0,sizeof(f));
	f[1]=1;
	while(q.size()) q.pop();
	q.push(make_pair(d[1],1));//每次存入到2的最短路，并让队首是最大。
	while(q.size()){
		int x=q.top().second;q.pop();
		if(v[x]) continue;
		v[x]=1;
		for(int i=first[x];i;i=nxt[i]){
			int y=to[i];
			if(d[y]<d[x]){//假如地点的最短路比起点小，则可以走这段路
				f[y]+=f[x];//更新方法数
				q.push(make_pair(d[y],y));
			}
		}
	}
}
int main(){
	while(scanf("%d",&n),n){
		cnt=0;
		memset(nxt,0,sizeof(nxt));
		memset(val,0,sizeof(val));
		memset(to,0,sizeof(to));
		memset(first,0,sizeof(first));
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a1,&b1,&c1);
			addedge(a1,b1,c1);
			addedge(b1,a1,c1);
		}
		dij1();
		dij2();
//		for(int i=1;i<=n;i++) printf("%d %d\n",i,f[i]);
		printf("%d\n",f[2]);
	}
}
```

我认为是一种非常巧妙的方法了，毕竟我也不像sto sto 诸多大佬 orz orz能够一下想到记忆化搜索或DP之类。
![](https://cdn.luogu.com.cn/upload/pic/58476.png)



---

## 作者：UperFicial (赞：4)

# 图论

### 前言

这题评紫虚高，还是挺板子的。

不过调吐了，本来口胡了一遍自信满满，结果直接GG。

细节太多了。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/UVA10917)。

### 题意简述

给定 $n$ 个点 $m$ 条边的带权无向图，能从 $A$ 走到 $B$ 当且仅当：

- $A$ 与 $B$ 之间有一条边。

- $A$ 到 $2$ 号点的距离大于 $B$ 到 $2$ 号点的距离。

问从 $1$ 号点到 $2$ 号点有多少种走法。

### 题目分析

不难想到通过所有点到 $2$ 号点的关系建一张新图 $G=(V',E')$。

这张新图满足：

- 对于任意 $u,v\in V'$ 都有 $u,v\in V$。

- 对于任意 $e=(u,v)\in E'$ 都有 $e\in E$。

- 对于任意 $u,v\in V'\land e=(u,v)\in E'$ 都有 $d_u>d_v$。

其中 $d_x$ 表示 $x$ 到 $2$ 号点的距离。

然后就可以在这个新图上跑 $dfs$，并且这个新图一定是个 $DAG$（有向无环图）。

为什么呢？假设有一条环，定点为 $v_1,v_2,\cdots v_k$。

它必定满足 $d_{v_1}<d_{v_2}<\cdots d_{v_k}$ 或者 $d_{v_1}>d_{v_2}>\cdots d_{v_k}$

既然是一条环，那么 $v_1$ 和 $v_k$ 有一条直接相连的边，但它们如果连边就不属于新图的第三条的关系，故不会有环。

最后注意：

- 多组数据要清空。

- 拓扑排序见祖宗。

[$code$](https://paste.ubuntu.com/p/rpJZhsXrk4/)

$$\texttt{The End.by UF}$$

---

## 作者：览遍千秋 (赞：4)

## I 吐槽

为啥UVA这么喜欢多测。。。

![]( https://cdn.luogu.com.cn/upload/pic/61599.png )

---

## II 题意简述

给定一$N$个点，$M$条边的图

一个人要从点$1$去到点$2$，中间还有很多点和很多条边。问你如果他每次走的边$(a,b)$都满足：$a$点到目标点的最短距离>$b$点到目标点的最短距离，那么求他从点$1$出发到点$2$总共有多少条路径。

$N,M<=1000$

### 多测

---

## III 算法初步分析和证明

首先，用`dijkstra`+堆优化跑出每个点到点$2$的最短路径。

~~关于SPFA，它死了~~

接着枚举所有的边（将无向边改为两条有向边），标记出所有可以通过的路径。

可以证明由可以通过的路径组成的图是一个$DAG$。

证明如下：

> 设这个图不是一个$DAG$，则存在至少一个环。

> 设这个环中有$(a,b)$,$(b,c)$,$(c,a)$的一条**有向边**

> 根据题意，因为存在边$(a,b)$，所以$dis_a>dis_b$。

> 同理可得$dis_b>dis_c$，$dis_c>dis_a$

> 可以发现这是自相矛盾的，故命题不成立，这个图是一个$DAG$

---

## IV $DAG$图的处理

好像并不能递归求解，会$\color{purple}\text{RE}$。

所以用$\color{darkblue}\text{toposort}$求解

---

## V 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 100003

int n,m,x,y,z;
int Head[maxn],Next[maxn<<1],v[maxn<<1],tot,w[maxn<<1],u[maxn<<1];
int dis[maxn],ans,rd[maxn],opt[maxn];
bool inq[maxn],kp[maxn<<1],col[maxn];
struct node{
    int id,dis;
    bool operator <(node a)const{
        return dis>a.dis;
    }
};

template<typename Tp>
void read(Tp &x){
    x=0;char ch=0;int fh;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-'){
        ch=getchar();fh=-1;
    }
    else fh=1;
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    x*=fh;
}
void clear(){
    tot=ans=0;
    memset(Next,0,sizeof(Next));
    memset(Head,0,sizeof(Head));
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(inq,false,sizeof(inq));
    memset(kp,false,sizeof(kp));
    memset(col,false,sizeof(col));
    memset(rd,0,sizeof(rd));
    memset(opt,0,sizeof(opt));
}
void dijkstra(int x){
    priority_queue <node> q;
    q.push((node){x,dis[x]=0});
    while(!q.empty()){
        int k=q.top().id;q.pop();
        if(inq[k]) continue;
        inq[k]=1;
        for(int i=Head[k];i;i=Next[i]){
            if(dis[v[i]]>dis[k]+w[i]){
                dis[v[i]]=dis[k]+w[i];
                q.push((node){v[i],dis[v[i]]});
            }
        }
    }
}
void dfs(int x){
    if(x==2){
        ans++;return;
    }
    for(int i=Head[x];i;i=Next[i]){
        if(kp[i])
            dfs(v[i]);
    }
}
void solve(){
    queue<int>qq;
    qq.push(1);col[1]=1;
    while(!qq.empty()){
        int k=qq.front();qq.pop();
        for(int i=Head[k];i;i=Next[i]){
            if(!col[v[i]]&&kp[i]){
                col[v[i]]=1;qq.push(v[i]);
            }
        }
    }
    for(register int i=1;i<=tot;i++){
        if(kp[i]&&col[u[i]]&&col[v[i]])
            rd[v[i]]++;
    }
    queue<int>qqq;
    opt[1]=1;qqq.push(1);
    while(!qqq.empty()){
        int k=qqq.front();qqq.pop();
        for(int i=Head[k];i;i=Next[i]){
            if(!kp[i]) continue;
            rd[v[i]]--;
            if(!rd[v[i]]) qqq.push(v[i]);
            opt[v[i]]+=opt[k];
        }
    }
    ans=opt[2];
}
int mian(){

    while(1){
        read(n);if(!n) return 0;
        read(m);clear();
        for(register int i=1;i<=m;i++){
            read(x);read(y);read(z);
            v[++tot]=y,u[tot]=x,Next[tot]=Head[x],Head[x]=tot,w[tot]=z;
            v[++tot]=x,u[tot]=y,Next[tot]=Head[y],Head[y]=tot,w[tot]=z;
        }
        dijkstra(2);
        for(register int i=1;i<=tot;i++){
            if(dis[v[i]]<dis[u[i]]) kp[i]=1;
        }
        //dfs(1);
        solve();
        printf("%d\n",ans);
    }
}
```

---

## $\color{pink}\text{VI UVA注册攻略}$

1.注册一个$\color{blue}\text{outlook}$邮箱，其他邮箱可能会收不到邮件。

2.打开UVA

3.进入注册页面后，姓名可以乱填一个英文名，如$zzk AKIOI$ @[周子凯](https://www.luogu.org/space/show?uid=35871)

如果希望能够在luogu绑定账号，请在RemoteJudge一栏打钩。

4.前往邮箱接收邮件，如果未收到，可以先去垃圾箱找一找。

5.点击链接，完成注册

---

## 作者：wky32768 (赞：3)

题意：

sxd最近打算穿过一个森林，但是他比较傲娇，于是他决定只走一些特殊的道路，他打算只沿着满足如下条件的（A,B）道路走：存在一条从B出发回家的路，比所有从A出发回家的路径都短。你的任务是计算一共有多少条不同的回家路径。其中起点的编号为1，终点的编号为2. 

思路大致如下：先用...求最短路(终点作起点)，对于DIS[A]>DIS[B]的情况连一条边,然后DFS找到去终点有多少条路即可。

不要说什么此算法已死这种..

N<=1000才不用边表..

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=230000;
int n,m,s,t,vis[N],d[N],mp[1200][1200],dp[N];
void init() {
	memset(dp,0,sizeof dp);
	for(int i=0; i<=n; i++) vis[i]=0;
	for(int i=0; i<=n; i++)
		for(int j=0; j<=n; j++)
			mp[i][j]=(i==j?0:0x3f3f3f3f);
}
void spfa() {
	memset(vis,0,sizeof vis);
	for(int i=0; i<=n; i++) d[i]=0x3f3f3f3f;
	d[t]=0;
	vis[t]=1;
	queue <int> q;
	q.push(t);
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		vis[now]=0;
		for(int i=1; i<=n; i++) {
			if(mp[now][i]>=0x3f3f3f3f || now==i) continue;
			if(d[i]>d[now]+mp[now][i]) {
				d[i]=d[now]+mp[now][i];
				if(!vis[i]) {
					vis[i]=1;
					q.push(i);
				}
			}
		}
	}
}
int dfs(int at) {
	if(at==2) return 1;
	if(dp[at]) return dp[at];
	int ans=0;
	for(int i=1;i<=n;i++) {
		if(d[at]>d[i] && mp[at][i]<0x3f3f3f3f) ans+=dfs(i);	
	}
	dp[at]=ans;
	return ans;
}
signed main() {
	ios::sync_with_stdio(false);
	s=1,t=2;
	while(cin>>n && n) {
		init();
		cin>>m;
		for(int i=1; i<=m; ++i) {
			int a,b,c;
			cin>>a>>b>>c;
			if(c>mp[a][b]) continue;
			mp[a][b]=mp[b][a]=c;
		}
		spfa();
		cout<<dfs(1)<<'\n';
	}
	return 0;
    sxdakking
}
```

---

## 作者：D2T1 (赞：2)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解

设 $D_i$ 表示点 $i$ 到点 $2$ 的最短路，则 Jimmy 可以经过的路径 $(u,v)$ 必须满足 $D_u>D_v$，所以我们可以用一遍 Dijkstra 预处理出 $D$ 数组，并枚举每一条边 $(u,v)$，若满足 $D_u>D_v$，在一张新的图中插入**有向边** $(u,v)$。

我们画图模拟一下。这是样例 1 的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/raz40i29.png)

求出单源最短路 $D=\{36,0,37,34,24\}$。

枚举每一条边，取出边 $(1,3)$，发现 $D_1<D_3$，跳过；取出边 $(1,4)$，发现 $D_1>D_4$，在新图中插入**有向边** $(1,4)$，以此类推。这是最后的新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qoadbjhp.png)

可以发现这是一个 DAG，因为加边的条件导致这张图不可能有环（想一想，为什么）。

而我们就将题目转化为在 DAG 上找起点至终点路径数，可以用拓扑排序+DP 求解。

于是，我们用 **Dijkstra** 和 **DAG 求两点路径数**两个板子解决了这道紫题。

## 代码

```cpp
//UVA10917
#include <bits/stdc++.h>
using namespace std;

const int N=1010;
int n,m;
vector<pair<int,int> > e1[N];
int dis[N],vis[N];
vector<int> e2[N],topo;
int ind[N],dp[N];

inline void dijkstra(int s){
	priority_queue<pair<int,int> > q;
	dis[s]=0,q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second; q.pop();
		if(vis[x]) continue; vis[x]=true;
		for(int i=0; i<e1[x].size(); ++i){
			int y=e1[x][i].first,z=e1[x][i].second;
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				if(!vis[y]) q.push(make_pair(-dis[y],y));
			}
		}
	} 
	return;
}
inline int pathcnt(int s,int t){
	//拓扑排序
	queue<int> q;
	for(int i=1; i<=n; ++i)
		if(!ind[i]) q.push(i);
	while(!q.empty()){
		int x=q.front(); q.pop();
		topo.push_back(x);
		for(int i=0; i<e2[x].size(); ++i){
			int y=e2[x][i];
			--ind[y];
			if(!ind[y]) q.push(y);
		}
	}
	//DP
	dp[t]=1;
	for(int i=n-1; i>=0; --i){
		int x=topo[i];
		for(int j=0; j<e2[x].size(); ++j){
			int y=e2[x][j];
			dp[x]+=dp[y];
		}
	}
	return dp[s];
}

int main(){
	while(cin>>n && n){
		cin>>m;
		//多组数据，记得重置每一个数组
		for(int i=0; i<N; ++i) e1[i].clear(),e2[i].clear();
		memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));
		memset(ind,0,sizeof(ind));
		memset(dp,0,sizeof(dp));
		topo.clear();
		for(int i=1,a,b,c; i<=m; ++i)
			scanf("%d%d%d",&a,&b,&c),
			e1[b].push_back(make_pair(a,c)),
			e1[a].push_back(make_pair(b,c));
		dijkstra(2);//跑 Dijkstra 求 D 数组
		for(int x=1; x<=n; ++x)//构造新图
			for(int j=0; j<e1[x].size(); ++j){
				int y=e1[x][j].first;
				if(dis[x]>dis[y]) e2[x].push_back(y),++ind[y];
			}
		cout<<pathcnt(1,2)<<'\n';//在 DAG 上求路径数
	}
	return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [传送门](https://www.luogu.com.cn/problem/UVA10917)

## 思路

感觉其他题解的方法太麻烦了。根据题目中 Jimmy 的要求：只向离终点最短路更近的点走，我们只需从终点跑 Dijkstra 求出 $dis$ 数组，然后遍历每一条边重新建图。但是我们只建符合 Jimmy 要求的边，即对起点 $u$ 和终点 $v$ 满足 $dis_u>dis_v$。新图一定是一个 DAG 因为题目保证答案小于 $2^{31}-1$，若有环答案将为无穷大。最后只需对新图跑拓扑排序即可。

## 完整代码

```c++
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using pii=pair<int,int>;
struct Edge{
	int u,v,w,nxt;
}a[2000005];
int n,m,ct,head[1005],vis[1005],u[1000005],v[1000005],deg[1005],dp[1005],dis[1005];
inline void add(int u,int v,int w){
	a[++ct]={u,v,w,head[u]};
	head[u]=ct;
}
void dij(){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	dis[2]=0;
	priority_queue<pii,vector<pii>,greater<pii>>q;
	q.push({0,2});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=head[u];i;i=a[i].nxt){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				q.push({dis[v],v});
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	while(cin>>n){
		if(!n)break;
		memset(head,0,sizeof head);ct=0;
		memset(dp,0,sizeof dp);
		cin>>m;
		for(int i=1,d;i<=m;i++){
			cin>>u[i]>>v[i]>>d;
			add(u[i],v[i],d);add(v[i],u[i],d);
		}
		dij();
		memset(head,0,sizeof head);ct=0;
		for(int i=1;i<=m;i++){
			if(dis[v[i]]>dis[u[i]])add(v[i],u[i],0),deg[u[i]]++;
			else if(dis[v[i]]<dis[u[i]])add(u[i],v[i],0),deg[v[i]]++;
		}queue<int>q;
		for(int i=1;i<=n;i++){
			if(!deg[i])q.push(i);
		}dp[1]=1;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=a[i].nxt){
				int v=a[i].v;
				if(!(--deg[v]))q.push(v);
				dp[v]+=dp[u];
			}
		}
		cout<<dp[2]<<'\n';
	}
}
```

---

## 作者：Stinger (赞：1)

算是比较板子的题了。不懂为什么难度被评到了紫题……

# $\texttt{Description}$

> 给你一个 $n$ 个点，$m$ 条边的图，令 $dis_i$ 表示编号为 $2$ 的点到点 $i$ 的最短路，求从点 $1$ 出发，经过原图中 $dis_{from}>dis_{to}$ 的边到达点 $2$ 的方案数，$from,to$ 分别表示这条边的起点和终点。
>
> $\texttt{Data Range}:n\le 1000,m\le n^2$。

# $\texttt{Solution}$

跑一边最短路那是必须的，建议不要用某死了的算法。

那么建一个新的图，对于原图一条 $u\rightarrow v$ 的点，当且仅当  $dis_u>dis_v$ 在新图中加入这条边。

新的图一定是一个 DAG，dp 求解 $1\rightarrow 2$ 的方案数即可，我建了个隐式反图。

时间复杂度 $O(mlogn)$。

按理说这题数据范围珂以给到 $1\le n,m,\le 500000$ 啊/yiw

# $\texttt{Code}$

```cpp
#include <cstdio>
#include <queue>
#include <cstring>

typedef std::pair<int, int> PII;
std::priority_queue<PII, std::vector<PII>, std::greater<PII> > q;
struct Edge {
	int to, nxt, w;
} e[2000005];
int dis[1005], head[1005], dp[1005], tot, n, m;
bool mp[1005][1005], done[1005];
inline void AddEdge(const int u, const int v, const int w) {
	e[++ tot].to = v, e[tot].nxt = head[u], e[tot].w = w, head[u] = tot;
}
void Dijkstra() {
	memset(dp, 0, sizeof dp);
	memset(dis, 0x3f, sizeof dis);
	memset(done, 0, sizeof done);
	dp[2] = 1;
	q.push(std::make_pair(dis[2] = 0, 2));
	while (q.size()) {
		int u(q.top().second);
		q.pop();
		if (done[u]) continue;
		done[u] = true;
		for (int i(head[u]); i; i = e[i].nxt) {
			int v(e[i].to);
			if (dis[u] + e[i].w < dis[v])
				q.push(std::make_pair(dis[v] = dis[u] + e[i].w, v));
		}
	}
}
int DP(const int u) {
	if (dp[u]) return dp[u];
	for (int i(1); i <= n; ++ i)
		if (dis[i] < dis[u] && mp[i][u]) dp[u] += DP(i);//隐式的反图
	return dp[u];
}

signed main() {
	while (true) {
		scanf("%d", &n);
		if (!n) return 0;
		memset(head, 0, sizeof head);
		memset(mp, 0, sizeof mp);
		tot = 0;
		scanf("%d", &m);
		for (int i(1); i <= m; ++ i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			mp[u][v] = mp[v][u] = true;
			AddEdge(u, v, w), AddEdge(v, u, w);
		}
		Dijkstra();
		printf("%d\n", DP(1));
	}
}
```



---

## 作者：andyli (赞：1)

首先求出从每个点$u$回家的最短路长度$d[u]$，则题目中的条件“存在一条从$B$出发回家的路径，比所有从$A$出发回家的路径都短”实际上是指$d[B]<d[A]$。这样，我们创建一个新的图，当且仅当$d[B]<d[A]$时加入有向边$A->B$，则题目的目标就是求出起点到终点的路径条数。因为这个图是$DAG$，可以用动态规划求解。  
去除模板后代码如下：
```cpp
const int INF = 0x3f3f3f3f, maxn = 1005;
class Dijkstra
{
  public:
    struct Edge
    {
        int from, to, dist;
        Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
    };
    struct HeapNode
    {
        int d, u;
        bool operator<(const HeapNode &rhs) const
        {
            return d > rhs.d;
        }
    };
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool done[maxn];
    int d[maxn];
    int p[maxn];
    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int dist)
    {
        edges.push_back(Edge(from, to, dist));
        m = edges.size();
        G[from].push_back(m - 1);
    }
    void dijkstra(int s)
    {
        priority_queue<HeapNode> Q;
        for (int i = 0; i < n; i++)
            d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push((HeapNode){0, s});
        while (!Q.empty())
        {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (done[u])
                continue;
            done[u] = true;
            for (size_t i = 0; i < G[u].size(); i++)
            {
                Edge &e = edges[G[u][i]];
                if (d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = G[u][i];
                    Q.push((HeapNode){d[e.to], e.to});
                }
            }
        }
    }
};

bool G[maxn][maxn], G2[maxn][maxn];
int dp[maxn], n, m;

int dfs(int u)
{
    if (u == 0)
        return 1;
    if (dp[u] != -1)
        return dp[u];
    int ans = 0;
    for (int v = 0; v < n; v++)
        if (G2[v][u])
            ans += dfs(v);
    return dp[u] = ans;
}

int main()
{
    while (read(n), n)
    {
        read(m);
        Dijkstra dij;
        dij.init(n);
        memset(G, 0, sizeof(G));
        memset(G2, 0, sizeof(G2));
        memset(dp, -1, sizeof(dp));
        while (m--)
        {
            int u, v, w;
            read(u, v, w);
            --u, --v;
            dij.AddEdge(u, v, w);
            dij.AddEdge(v, u, w);
            G[u][v] = G[v][u] = true;
        }
        dij.dijkstra(1);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (dij.d[j] < dij.d[i] && G[i][j])
                    G2[i][j] = true;
                else if (dij.d[i] < dij.d[j] && G[j][i])
                    G2[j][i] = true;
        writeln(dfs(1));
    }
    return 0;
}
```

---

## 作者：Engulf (赞：0)

先跑一便最短路，得到每个点到天堂的距离 $d_i$，在原来的边 $u\rightarrow v$ 的基础上，建一个新图，若 $d_u > d_v$ 则连一条 $u \rightarrow v$，反之亦然，注意如果 $d_u = d_v$ 则不连边。

注意到新图是一个 DAG，其他题解已经证了。

问题转化为在一个 DAG 上路径条数统计，直接拓扑排序即可。

代码实现中所有点从 $0$ 开始。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n, n) {
        cin >> m;
        using Graph = vector<vector<pair<int, ll>>>;
        Graph g(n);
        vector<pii> edge(m);
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            u--, v--;
            edge[i] = {u, v};
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        auto spfa = [=](int s, Graph &g) {
            vector<ll> dis(n, 1e18);
            queue<int> q;
            vector<bool> vis(n);
            dis[s] = 0;
            vis[s] = 1;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop(); vis[u] = 0;
                for (auto i: g[u]) {
                    int v = i.first; ll w = i.second;
                    if (dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        if (!vis[v])
                            q.push(v), vis[v] = 1;
                    }
                }
            }
            return dis;
        };

        vector<ll> dis = spfa(1, g);

        vector<int> f(n);
        queue<int> q;
        vector<bool> vis(n);
        vector<int> in(n);

        for (int i = 0; i < n; i++) g[i].clear();

        for (int i = 0; i < m; i++) {
            int u = edge[i].first, v = edge[i].second;
            if (dis[u] == dis[v]) continue;
            if (dis[u] < dis[v]) swap(u, v);
            // debug("%d -> %d\n", u + 1, v + 1);
            in[v]++;
            g[u].emplace_back(v, 1);
        }

        // for (int i = 0; i < n; i++) debug("in[%d] = %d\n", i + 1, in[i]);

        for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
        f[0] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto i: g[u]) {
                int v = i.first;
                f[v] += f[u];
                if (!--in[v])
                    q.push(v);
            }
        }

        // for (int i = 0; i < n; i++) debug("f[%d] = %d\n", i + 1, f[i]);

        cout << f[1] << "\n";
    }
    return 0;
}
```

---

## 作者：Uuuuuur_ (赞：0)

最短路+拓扑排序。

设 $d_u$ 为家到 $u$ 的最短路，可知当 $d_A \gt d_B$ 时，道路 $A \rightarrow B$ 才能被走。这样就很简单了，先做一遍裸的最短路，再枚举每条边能否被走，建出一张新图来。这张新图肯定是**有向无环图**，因为假设有 $A \rightarrow B \rightarrow C \rightarrow A$ 成环，就会有 $d_A \gt d_B > d_C > d_A$，这样肯定不成立的。

既然是 DAG，设 $f_u$ 为到 $u$ 点的方案数，做一遍拓扑排序就递推出来了。

注意只有两点间原来存在边，这两点才可能被建新边。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int v;
    int w;
};
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e3 + 5;
int n, m;
vector<node> g[N];
vector<int> G[N];
int d[N];
int in[N];
int f[N];
bool vis[N];
void dij() {
    memset(d, 0x3f, sizeof d);
    set<pair<int, int> > q;
    d[2] = 0;
    q.insert(make_pair(0, 2));
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].v, w = g[u][i].w;
            if (d[u] + w < d[v]) {
                q.erase(make_pair(d[v], v));
                d[v] = d[u] + w;
                q.insert(make_pair(d[v], v));
            }
        }
    }
}
void dfs(int u) {
    for (int v : G[u]) {
        in[v]--;
        f[v] += f[u];
        
        if (in[v] == 0) {
 
            dfs(v);
        }
    }
}
void solve() {
    memset(in, 0, sizeof in);
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < g[i].size(); k++) {
            int j = g[i][k].v;
            if (d[j] < d[i]) {G[i].push_back(j); in[j]++;}
        }
    }
    f[1] = 1;
    vector<int> st;
    for (int i = 1; i <= n; i++) if (!in[i]) st.push_back(i);
    for (int s : st) dfs(s);
    cout << f[2] <<  '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (true) {
        for (int i = 0; i < N; i++) vector<int>().swap(G[i]), vector<node>().swap(g[i]);
        cin >> n;
        if (n == 0) return 0;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, w; 
            cin >> u >> v >> w;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        dij();
        solve();
    }
    return 0;
}
```


---

## 作者：Dfkuaid (赞：0)

## #1.0 理解题意

本题最需要理解的是这句话：

**如果有一条从B到他的家的路线比从A到他的家的任何可能的路线都短,那么他认为从A到B更好。**

设 $d_x$ 表示 $x$ 到 $2$ 号节点的最短路，那么上文的意思就是如果 $A,B$ 间存在道路且 $d_B<d_A$，那么道路 $A\to B$ 便是一种可行的选择。

## #2.0 大体思路

根据上面那句话，我们便需要先处理出所有点到 $2$ 号点的最短距离。然后按照上面的要求重新建图，这里建出的边是单向边，再注意到得到的图是一张**有向无环图**（$\texttt{DAG}$），因为每条边的边权都是非负数，用反证法不难证明得到的最短路图不存在环。

此时考虑 $\texttt{DAG}$ 上的动态规划，设 $sum_x$ 表示从 $1$ 号节点到 $x$ 号节点可行的路径条数，显然有

$$
sum_x=\sum\limits_{(y,x)\in E}sum_y.
$$

这里 $E$ 表示边集，有序数对 $(u,v)$ 表示一条从 $u$ 的 $v$ 的有向边。边界为 $sum_1=1.$

同时注意到，节点 $1$ 不一定是入度为 $0$ 的点，入度为零的点除 $1$ 外不会对答案造成贡献。

拓扑结束后得到的结果便是本题所求。

``` cpp
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], ne[N];

int cnt = 1, ncnt = 1, head[N], nhead[N];
int dist[N], vis[N], tot[N], s, t, icnt[N];
int qx[N], frt, tal, tag[N], n, m;

priority_queue <pii > q;

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline void addn(const int &u, const int &v) {
    ne[ncnt].u = u, ne[ncnt].v = v, icnt[v] ++;
    ne[ncnt].nxt = nhead[u], nhead[u] = ncnt ++;
}

void Dijkstra() {
    mset(dist, 0x3f);
    q.push(mp(0,2)); dist[2] = 0;
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (dist[e[i].v] > dist[now] + e[i].w) {
              dist[e[i].v] = dist[now] + e[i].w;
              q.push(mp(-dist[e[i].v], e[i].v));
          }
    }
}

inline void clear() {
    frt = 0, tal = -1; 
    ncnt = cnt = 1; mset(tot, 0);
    mset(icnt, 0); mset(tag, 0);
    mset(vis, 0); mset(dist, 0x3f);
    mset(head, 0); mset(nhead, 0);
}

void topo() {
    mset(vis, 0);
    for (int i = 1; i <= n; i ++) 
      if (!icnt[i] || i == 1) qx[++ tal] = i;
    tag[1] = tot[1] = vis[1] = 1;
    while (frt <= tal) {
        int now = qx[frt ++];
        for (int i = nhead[now]; i;i = ne[i].nxt) {
            icnt[ne[i].v] --;
            if (tag[now]) {
                tot[ne[i].v] += tot[now], 
                tag[ne[i].v] |= tag[now];
            }
            if (!icnt[ne[i].v] && !vis[ne[i].v]) {
                qx[++ tal] = ne[i].v;
                vis[ne[i].v] == true;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    while (n) {
        scanf("%d", &m); s = 1, t = 2; clear();
        for (int i = 1; i <= m; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); add(v, u, w);
        }
        Dijkstra();
        for (int i = 1; i <= n; i ++)
          for (int j = head[i]; j; j = e[j].nxt)
            if (dist[i] > dist[e[j].v])
              addn(i, e[j].v);
        topo();
        printf("%d\n", tot[t]);
        scanf("%d", &n);
    }
    return 0;
}
```

## End

希望能为各位带来帮助。


---

