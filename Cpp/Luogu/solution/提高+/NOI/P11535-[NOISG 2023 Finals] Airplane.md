# [NOISG 2023 Finals] Airplane

## 题目描述

兔子 Benson 正要启动飞机！

有 $n$ 块 Benson 可以飞入的区域，由 $1\sim n$ 编号。受地形限制，进入第 $i$ 块区域时，需要保证飞机的高度不低于 $a_i$。保证 $a_1=a_n=0$。

此外，由于风况复杂而 Benson 的经验尚不充足（毕竟他是只兔子），他只能在某些特定的航线上双向飞行。具体地，有 $m$ 条航线，由 $1\sim m$ 编号，其中第 $i$ 条航线 $u_j,v_j$ 表示 Benson 可以在这两块区域间直接飞行。

Benson 发现，他可以通过在直接的航线上飞行，使得这些区域两两可达。

现在，Benson 在 $1$ 号区域，高度为 $0$。他希望降落在 $n$ 号区域，高度自然也为 $0$。每一分钟，Benson 可以跨过一条航线或不移动，并**同时**使飞机的高度上升 $1$、下降 $1$ 或保持不变。注意，当他到达 $i$ 区域时，必须保证飞机的高度不低于 $a_i$。

Benson 想知道，从 $1$ 号区域出发，在 $n$ 号区域降落，所需的最小时间。

## 说明/提示

#### 样例 #1 解释

Benson 从 $1$ 出发，在 $3$ 降落，总共需要 $4$ 分钟：

- 第 $1$ 分钟，Benson 不移动，同时高度从 $0$ 变为 $1$；
- 第 $2$ 分钟，从 $1$ 移动到 $2$，同时高度从 $1$ 变为 $2$；
- 第 $3$ 分钟，从 $2$ 移动到 $3$，同时高度从 $2$ 变为 $1$；
- 第 $4$ 分钟，Benson 不移动，同时高度从 $1$ 变为 $0$。

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $22$ | $m=n-1,u_j=j,v_j=j+1$ |
| $2$ | $10$ | $n\leq 2000$，$m\leq 4000$，$a_i\leq 2000$ |
| $3$ | $31$ | $n\leq 2000$，$m\leq 4000$ |
| $4$ | $37$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n\leq 2\times 10^5$
- $1\leq m\leq 4\times 10^5$
- $0\leq a_i\leq 10^8$，$a_1=a_n=0$
- $1\leq u_j,v_j\leq n$，$u_j\ne v_j$

## 样例 #1

### 输入

```
3 2
0 2 0
1 2
2 3
```

### 输出

```
4```

## 样例 #2

### 输入

```
11 12
0 0 0 0 0 0 2 2 1 5 0
1 2
2 3
3 4
4 5
5 6
6 11
1 7
7 8
8 9
9 11
1 10
10 11
```

### 输出

```
5```

# 题解

## 作者：DJN123 (赞：2)

看前面两篇题解有些地方没有说清楚，来发一篇解释一下这个思路的可行性。
# 题意
有一个 $n$ 个点，$m$ 条边的无向连通图，每个点有一定的高度要求，起点高度为零，每分钟可以经过一条边或原地不动，并同时使高度加一或减一或保持不变，并要求**道达终点时高度为零**。求：从 $1$ 到 $n$ 的最少耗时。 
# 思路
观察题目，我们可以发现每一分钟可以改变 $1$ 的高度，也就是说，我们要到达 $a_i$ 的高度，所需时间**最小**为 $a_i$（就是一直上升的情况），也就是说，我们可以得到结论：**在一直上升的情况下，高度就等于所花费时间**。

但是，这个结论显然没有达到我们的要求。因为一条路径要求**到终点时高度为零**，因此我们不可能一直上升。但是也不难得出，在路径经过最高点后，我们就不再上升了。 
#### 举个栗子  
![这是作者画的丑图](https://cdn.luogu.com.cn/upload/image_hosting/1ejgxzgy.png)  

绿色这一段一直上升，而蓝色一段则需要一直下降，交汇的地方就是最高点，那么最高点高度 $h$ 就满足:总时间 $t_t = 2 \times h$。  
怎么来的呢？绿色这一段的时间等于 $h$，这可以通过上述结论得来，而蓝色这一段，我们可以把它看成**从终点上升到最高点**，那么就符合条件限制了。   


---


但我们肯定不可能去求一个路径的最高点，于是，我们发现，**我们可以通过到达某个点的时间来设定这个路径的最高点**，前面我们得到时间可以等于高度，那么我们对于任意一点 $i$，从起点一直上升到 $i$ 的时间为 $d1_i$，从终点一直上升到 $i$ 的时间为 $d2_i$ 于是我们可以得到路径的最高点为 $\max(d1_i , d2_i)$ 所以总耗时应该为 $\max(d1_i, d2_i) \times 2$。
##### 解释一下
![](https://cdn.luogu.com.cn/upload/image_hosting/07lhqu6w.png)

不难看出，由于两条路径的时间差，我们到达 $i$ 的高度就有差异（图中金色虚线），所以我们用 $\left | d1_i - d2_i \right |$ 来表示高度差，于是我们可以通过第 $i$ 个点求出路径时间为 $d1_i + d2_i + \left | d1_i - d2_i \right |$ 即 $\max(d1_i , d2_i) \times 2$。  
这个思路还有没有缺陷呢？当然有了。 
##### 比如这个  
![这个不是作者画的丑图](https://cdn.luogu.com.cn/upload/image_hosting/ro5a0byp.png)  

诶我们发现~~你头顶怎么尖尖的~~，当这条路径的**长度**（不是耗时），为奇数时，会出现这么个“尖顶”——（就是一段上升和一段竖直下降），这玩意的耗时为 $2$ 但如果我们用一段平飞来代替就可以使总耗时减一。怎么解决呢？我们可以“手动”加边，就是分别让 $i$ 与 $i - 1$“分担”一半，然后总耗时加上我们平飞的边，具体实现就是在取完 $ \max(d1_i , d2_i) \times 2$ 后，再找 $i$ 的连点 $r$，取 $ \max(d1_i , d2_r) \times 2 + 1$ 就解决了。  
完结散花。
# Code： 

```cpp
#include<bits/stdc++.h>
const int N = 200005, M = 400005 * 2;
using namespace std;
int in(){
	int ans = 0, f = 1;
	char c = getchar();
	while(c < '0' || '9' < c){
		if(c == '-')f = -1;
		c = getchar();
	}
	do{
		ans = (ans << 3) + (ans << 1) + c - '0';
		c = getchar();
	}while('0' <= c && c <= '9');
	return ans * f; 
}
struct node{
	int next, to;
}road[M];
int head[N], cnt;
void add(int x, int y){
	road[++cnt].next = head[x];
	road[cnt].to = y;
	head[x] = cnt;
}
int d1[N], d2[N], a[N];
bool vis[N];
int n, m, u, v;
void spfa(int u, int f[]){ 
	memset(vis, 0, sizeof(vis));
	f[u] = 0;
	queue<int>q;
	q.push(u);
	while(!q.empty()){
		int h = q.front();
		q.pop();
		for(int i = head[h];i;i = road[i].next){
			int r = road[i].to, ext = max(a[r] - f[h] - 1, 0);
			if(f[r] > f[h] + ext + 1){
				f[r] = f[h] + ext + 1;
				if(!vis[r]){
					q.push(r);
					vis[r] = 1;
				}
			}
		}
		vis[h] = 0;
	}
}
signed main(){
	n = in(), m = in();
	for(int i = 1;i <= n;i++)a[i] = in();
	for(int i = 1;i <= m;i++){
		u = in(), v = in();
		add(u, v), add(v, u);
	}
	memset(d2, 63, sizeof(d2));
	memset(d1, 63, sizeof(d1));
	spfa(1, d1);
	spfa(n, d2);
	int ans = INT_MAX;
	for(int i = 1;i <= n;i++){
		ans = min(max(d1[i] , d2[i]) * 2, ans);
		for(int j = head[i];j;j = road[j].next){
			int r = road[j].to;
			ans = min(max(d1[i], d2[r]) * 2 + 1, ans);
		}
	}
	cout<<ans;
}
```

---

## 作者：Your_Name (赞：1)

### 题解
考虑一个事实，我们只会单调不降地走到这条路上 $a_i$ 最大的那个点，再单调不增地走到终点。那么我们枚举这个最大值在哪里出现，那么显然只有 $a_i$ 大于等于前面走过的所有值时才是一个可能的答案。

对于一个点来说，走到这里的花费为 $dis_u=\min\{\max(a_i,dis_v+1)\}$。如果 $dis_v+1<a_i$ 时，我们就要在前面的路上一边上升一边往前走，再在 $v$ 上升到 $a_i$，那么花费就是 $a_i$。反之前面的距离已经足够我们升到这么高了，直接从 $v$ 走过来也就是 $dis_v+1$。于是从 $1$ 和 $n$ 分别跑一遍再拼起来就行。
### AC_Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<long long, long long>
#define xx first
#define yy second
#define int long long
const int N = 2e5 + 10;
int n, m, a[N], ans = 1e18, d1[N], d2[N], INF = 1e14, h1[N], h2[N], mi;
bool vis[N];
vector<int> G[N];
struct node{
    int dis, high, id;
    bool operator < (const node b)const{
        return dis > b.dis;
    }
};
void dij(int *dis, int *h, int x){
    priority_queue<node> q;
    for(int i = 1; i <= n; i ++)dis[i] = h[i] = INF, vis[i] = 0;
    q.push({0, 0, x});
    dis[x] = 0, h[x] = 0;
    while(!q.empty()){
        auto u = q.top();
        q.pop();
        if(vis[u.id])continue;
        vis[u.id] = 1;
        for(auto i : G[u.id]){
            if(vis[i])continue;
            if(dis[i] > dis[u.id] + 1){
                dis[i] = max(a[i], dis[u.id] + 1);
                if(a[i] >= u.high)h[i] = dis[i];
                q.push({dis[i], max(u.high, a[i]), i});
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i <= m; i ++){
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dij(d1, h1, 1);
    dij(d2, h2, n);
    for(int i = 1; i <= n; i ++){
        ans = min(ans, h1[i] + h2[i]);
    }
    cout << ans;
    return 0;
}
```
_完结撒花。_

---

## 作者：zhoumurui (赞：1)

### 题面展示

懒得总结了，直接贴题面。

>兔子 Benson 正要启动飞机！
>
>有 $n$ 块 Benson 可以飞入的区域，由 $1\sim n$ 编号。受地形限制，进入第 $i$ 块区域时，需要保证飞机的高度不低于 $a_i$。保证 $a_1=a_n=0$。
>
>此外，由于风况复杂而 Benson 的经验尚不充足（毕竟他是只兔子），他只能在某些特定的航线上双向飞行。具体地，有 $m$ 条航线，由 $1\sim m$ 编号，其中第 $i$ 条航线 $u_j,v_j$ 表示 Benson 可以在这两块区域间直接飞行。
>
>Benson 发现，他可以通过在直接的航线上飞行，使得这些区域两两可达。
>
>现在，Benson 在 $1$ 号区域，高度为 $0$。他希望降落在 $n$ 号区域，高度自然也为 $0$。每一分钟，Benson 可以跨过一条航线或不移动，并**同时**使飞机的高度上升 $1$、下降 $1$ 或保持不变。注意，当他到达 $i$ 区域时，必须保证飞机的高度不低于 $a_i$。
>
>Benson 想知道，从 $1$ 号区域出发，在 $n$ 号区域降落，所需的最小时间。

### 解题思路

**结论 1：高度先上升后下降一定不劣。**

证明：用反证法，假如最优解都有波谷（也就是高度下降了又上升的一段），把波谷填平答案不变，与假设矛盾了。

考虑从起点和终点分别遍历整张图，跑一种类似于 Dijkstra 的算法，过程中高度单调不减。

可能会想用 Dijkstra 算法求出从起点和终点分别到达每个点的最短路径，转移时使用：

$$f_v = \max ( \min (f_u) +1,h_v)$$

其中 $h_v$ 是 $v$ 点的限高。然后枚举中间点来计算。

但是这依然会造成问题。对于 $u$ 号点，从起点到 $u$ 点计算的最短路径也许到达了 $h_1$ 的高度，而从终点到 $u$ 点计算的最短路径也许到达了 $h_2$ 的高度，但我们并不知道 $h_1$ 和 $h_2$ 相差多少。

如果强行下降到 $h_u$，可能会多出 $2 \times (min(h_1,h_2) - h_u)$ 的开销。如果将高度也设计成状态跑分层图显然会超时。

**结论 2：一条从起点到终点的最短路径上，最高的高度等于路径上经过的最大限高。**

证明显然。

根据结论 2，我们想到也许可以枚举这个“最大限高点”。修改 $f_u$ 的定义，改为**从起点到 $u$ 号点，不经过限高大于 $u$ 的点的最短路径**。如果能算出它，就意味着可以通过枚举最高点 $u$ 并计算它到起点和终点分别的最短路径来统计答案。

这个 $f_u$ 好求吗？答案是并不难求。

用前面给出的转移进行类 Dijkstra 算法，使用我们原本的定义正常计算 $g_u$。

在用于插入堆的 `node` （本应含有点的编号和与起点的距离）中额外添加一个**高度**成员变量，在符合**限高不大于 $h_u$** 时，将转移得的 $g_u$ 贡献计入 $f_u$。

更深一些的细节看代码。

### 代码展示

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
int n,m,a[1000005];
int h[1000005],e[1000005],ne[1000005],idx;
int d[4][1000005];
void add(int u,int v){
    e[++idx]=v;
    ne[idx]=h[u];
    h[u]=idx;
}
struct node{
    int d,u,s;
    node(int D,int U,int S){
        d=D,u=U,s=S;
    }
    bool operator <(const node b)const{
        return d>b.d;
    }
};
void dijkstra(int* dis1,int* dis2,int s){
    memset(dis1,0x3f,sizeof(d[0]));
    memset(dis2,0x3f,sizeof(d[0]));
    priority_queue<node> q;
    dis1[s]=dis2[s]=0;
    q.push(node(0,s,0));
    while (!q.empty()){
        node p=q.top();
        int u=p.u,s=p.s;
        if (dis1[u]!=p.d){
            q.pop();
            continue;
        }
        q.pop();
        for (int i=h[u];i;i=ne[i]){
            int v=e[i];
            if (dis1[v]==a[v])continue;
            if (dis1[v]>dis1[u]+1){
                dis1[v]=max(a[v],dis1[u]+1);
                q.push(node(dis1[v],v,max(a[v],s)));
                if (a[v]>=s)dis2[v]=dis1[v];
            }
        }
    }
}
void solve(){
    cin>>n>>m;
    for (int i=1;i<=n;i++)cin>>a[i];
    for (int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        add(x,y);add(y,x);
    }
    dijkstra(d[0],d[1],1);
    dijkstra(d[2],d[3],n);
    int ans=1e18;
    for (int i=1;i<=n;i++){
        //cout<<d[0][i]<<" "<<d[1][i]<<" "<<d[2][i]<<" "<<d[3][i]<<"\n";
        ans=min(ans,d[1][i]+d[3][i]);
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    t=1;
    while (t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Milthm (赞：1)

这种每一步能上下移动 $1$ 或不动的题，有一个结论是我们可以一直上移到某个位置，停滞不超过 $1$ 单位时间然后再下移。这个结论很好理解：我们如果飞到某个不一定需要往下飞的位置往下一定不优，如果是一个能往上飞的位置那么停滞也一定不优。

所以我们一定是一直往上飞直到不能再飞了（因为我们还要降落，不能一直往上飞）然后不断下降，这样最多也就是路径最中间有 $1$ 的停滞时间。

有了这个性质题目就有一点改变：如果我们枚举最中间的点或边，那么就剖分成了两个问题，且两个问题都是要求从某个起点开始，往上一直飞到达每个点的所需要的最小时间。

然后我们发现，对于这个问题，若到达某个点的一种方案所需的时间不是最少的那它往后传递也不会是最优的，所以这个问题可以用类似 dijkstra 的方法解决。

最后合并答案，枚举点的话就是前后两个方案的最大值乘 $2$（必须要把小的一遍抬升到和大的一样才能使得起点终点都合法），枚举边就是两头的两个方案的最大值乘 $2$（注意这里一条双向边有两种走法，具体见代码），特别地，两头的方案相等的话则需要额外加一（通过这条边的时间，刚才这个贡献都在抬升的时候一起算上了，所以不用加）。

时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define N 400005
#define pi pair<int,int>
using namespace std;
int n,m,vis[N],a[N],u[N],v[N],ans=1e9;
vector<int>e[N],dis1,dis2;
vector<int> dij(int s){
	vector<int>dis(N);
	priority_queue<pi,vector<pi>,greater<pi> >q;
	for(int i=1;i<=n;++i)dis[i]=1e9,vis[i]=0;
	dis[s]=0;q.push({0,s});
	while(!q.empty()){
		pi c=q.top();q.pop();
		int u=c.second;
		if(vis[u])continue;
		for(int v:e[u]){
			if(max(dis[u]+1,a[v])<dis[v]){
				dis[v]=max(dis[u]+1,a[v]);
				q.push({dis[v],v});
			}
		}
	}
	return dis;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=m;++i){
		cin>>u[i]>>v[i];
		e[u[i]].push_back(v[i]);e[v[i]].push_back(u[i]);
	}
	dis1=dij(1);dis2=dij(n);
	//for(int i=1;i<=n;++i)cout<<dis1[i]<<" ";cout<<'\n';
	//for(int i=1;i<=n;++i)cout<<dis2[i]<<" ";cout<<'\n';
	for(int i=1;i<=n;++i)ans=min(ans,2*max(dis1[i],dis2[i]));
	for(int i=1;i<=m;++i){
		int w=max(dis1[u[i]],dis2[v[i]])*2;
		if(dis1[u[i]]==dis2[v[i]])++w;
		ans=min(ans,w);
		w=max(dis2[u[i]],dis1[v[i]])*2;
		if(dis2[u[i]]==dis1[v[i]])++w;
		ans=min(ans,w); 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Mortis_ (赞：1)

[P11535 [NOISG 2023 Finals] Airplane](https://www.luogu.com.cn/problem/P11535)

最优情况一定能转化成先一直上升，然后高度不变持续 $ 0 $ 或 $ 1 $ 时刻，最后一直下降的情况。

证明：

- 若上升过程中有下降，改成上升必不劣（不用考虑高度太大的情况，达到最大高度可以不变），下降时同理。
- 若高度不变持续时刻超过 $ 1 $，则可将不变的第一时刻改为上升，最后时刻改为下降。

跑两遍 Dijkstra 分别求以 $ 1 $ 和 $ n $ 为起点，且高度只升的最小时刻。

将整个过程分成两段，枚举高度最大的点（或边）。

设该点为  $ x $，则答案为 $ 2 \times \max (dist_{1,x},dist_{n,x}) $。是边时要加一。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10,M=4e5+10;
struct node{
	int u,d;
	friend bool operator < (const node &x,const node &y){
		return x.d>y.d;
	}
};
int V[M<<1],nxt[M<<1],num,h[N];
void add(int u,int v){
	V[++num]=v;
	nxt[num]=h[u];
	h[u]=num;
}
int n,m,a[N],dist1[N],dist2[N],ans=INT_MAX;
bool vis[N];
void Dijkstra(int s,int *dist){
	priority_queue<node>q;
	q.push(node{s,0});
	for(int i=1;i<=n;i++)dist[i]=0x3f3f3f3f;
	dist[s]=0;
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		int u=q.top().u;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int e=h[u];e;e=nxt[e]){
			if(dist[V[e]]>max(dist[u]+1,a[V[e]])){
				dist[V[e]]=max(dist[u]+1,a[V[e]]);
				q.push(node{V[e],dist[V[e]]});
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int u,v;m--;){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	Dijkstra(1,dist1);
	Dijkstra(n,dist2);
	for(int u=1;u<=n;u++){
		ans=min(ans,max(dist1[u],dist2[u])<<1);
		for(int e=h[u];e;e=nxt[e])ans=min(ans,max(dist1[u],dist2[V[e]])<<1|1);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

考虑到为了符合限制，高度更高应该是不劣的，下降的唯一意义就是使得结束时高度为 $1$。所以全过程分为 $2$ 段，前半段不降，后半段不升，跑一遍 dij 得到点 $1$ 到每个点不升/降的最小耗时，最后枚举一个点 $i$ 作为转折点。假设前半段最小耗时 $d_1$，后半段耗时 $d_2$，则答案为 $2\max(d_1,d_2)$。

对于高度不变的情况，选择多于一次高度不变不优，因为可以替换为若偶数段则前半段上升后半段下降，若奇数段则保留中间的一段不变，前段上升后段下降。这样既可以获得更大的高度也可以保证这段时间结束时的高度不变。所以再枚举一条边作为转折边，假设前半段最小耗时 $d_1$，后半段耗时 $d_2$，则答案为 $2\max(d_1,d_2)+1$。两种情况取最优值即可。

```cpp
const ll N=2e5+10,inf=1e15;
ll n,m,lim[N],d1[N],d2[N],ans=inf;
vector<ll> g[N];
bool vis[N];
pqueue(pll,greater) pq;

void dij(ll st,ll *d) {
	rep(i,1,n) {
		vis[i]=0;
		d[i]=inf;
	}

	pq.push({0,st});
	d[st]=0;

	while(pq.empty()==0) {
		pll cur;
		xtop(cur,pq);

		if(vis[cur.se]) ctn;

		vis[cur.se]=1;

		for(ll i:g[cur.se]) {
			if(max(lim[i],cur.fi+1)<d[i]) {
				d[i]=max(lim[i],cur.fi+1);
				pq.push({d[i],i});
			}
		}
	}
}

int main() {
	cin>>n>>m;

	rep(i,1,n) cin>>lim[i];

	count(m) {
		ll u,v;
		cin>>u>>v;
		g[u].pb(v);
		g[v].pb(u);
	}

	dij(1,d1);
	dij(n,d2);

	rep(i,1,n) {
		update(ans,max(d1[i],d2[i])*2,min);

		for(ll j:g[i]) update(ans,max(d1[i],d2[j])*2+1,min);
	}

	cout<<ans;
}
```

---

## 作者：StayAlone (赞：1)

### 观察一

飞机的高度一定分成三个阶段：

1. 每分钟均升高。
2. 高度维持不变。
3. 每分钟均下降。

原因是高总是好的，下降的唯一目的是使到达 $n$ 点时的高度为 $0$。任何形式不是这三个阶段的方案，均能显然地调整成这种形式。

### 观察二

阶段二的时间为 $0$ 或 $1$。

若大于 $1$，则可以把第二阶段的第一分钟和最后一分钟分别调整成升高和降低。

------

有了这两个观察，题目就相当好做了。设 $dis_i$ 表示每分钟都要上升，从 $1$ 走到 $i$ 所花费的最小时间。松弛操作为 $d_v=\min\limits_{(u, v)}\{\max(d_u+1, a_v)\}$。实际上由于每分钟都上升，花费的时间等于时飞机的高度。

枚举阶段二所在点（时间为 $0$）或边（时间为 $1$）统计答案即可。

时间复杂度 $\mathcal O(m\log m)$。

[AC record](https://www.luogu.com.cn/record/197489125)

```cpp
int n, m, ans = inf, vis[MAXN], dis1[MAXN], dis2[MAXN], a[MAXN];
vector <int> lnk[MAXN];
priority_queue <pii> q;

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

il void dij(int s, int *d) {
	rep1(i, 1, n) d[i] = inf, vis[i] = 0;
	d[s] = 0; q.emplace(0, s);
	while (q.size()) {
		int x = q.top().snd; q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (auto v : lnk[x]) {
			int g = max(a[v], d[x] + 1);
			if (g < d[v]) d[v] = g, q.emplace(-d[v], v);
		}
	}
}

int main() {
	read(n, m); rer(i, 1, n, a);
	while (m--) add(read(), read());
	dij(1, dis1); dij(n, dis2);
	rep1(u, 1, n) {
		gmin(ans, max(dis1[u], dis2[u]) * 2);
		for (auto v : lnk[u]) gmin(ans, max(dis1[u], dis2[v]) * 2 + 1);
	} printf("%d", ans);
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

放 NOIP 联考 T1 太需要观察了吧。

我们充分发扬人类智慧，有一个暴力的做法。从最开始使得图联通的值 $v$ 开始枚举最大值，然后把所有 $\le v$ 的点加入，之后就可以跑最短路，当前点的高度应该是 $\min(dist_x,v)$。对于下降部分，从 $n$ 开始跑一次即可。

当 $v$ 增大的时候，相当于是激活若干个点，以这些点为源点进行 Dijkstra 尝试更新其他点即可。

复杂度上界是 $\mathcal{O}(nm\log n)$ 的，但是直接过了。不知道为什么，希望得到正确性证明或 hack。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, inf = 0x3f3f3f3f;
int n, m, u, v, a[N], fa[N], dist[2][N], id[N], val, p, ans = inf;
vector<int> G[N];
struct node {
    int x, dist;
    node() {}
    node(int _x, int _dist) {
        x = _x, dist = _dist;
    }
}tp;
inline bool operator < (node x, node y) {
    return x.dist > y.dist;
}
priority_queue<node> qu;
inline int getfa(int x) {
    return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
inline int max(int x, int y) {
    return x > y ? x : y;
}
bool vis[N];
vector<int> okk;
inline void bfs(int st, int* dist) {
    for(int i = 1; i <= n; i++) dist[i] = inf;
    dist[st] = 0;
    qu.push(node(st, 0));
    while(!qu.empty()) {
        tp = qu.top(), qu.pop();
        if(dist[tp.x] ^ tp.dist) continue ;
        for(int y : G[tp.x]) if(a[y] <= val && dist[y] > max(dist[tp.x] + 1, a[y])) {
            dist[y] = max(dist[tp.x] + 1, a[y]);
            qu.push(node(y, dist[y]));
        }
    }
}
inline void dijk(vector<int> &vc, int* dist) {
    for(int o : vc) {
        for(int y : G[o]) if(a[y] <= val && dist[o] > max(dist[y] + 1, a[o])) {
            dist[o] = max(dist[y] + 1, a[o]);
        }
        if(dist[o] < inf) {
            qu.push(node(o, dist[o]));
        }
    }
    while(!qu.empty()) {
        tp = qu.top(), qu.pop();
        if(dist[tp.x] ^ tp.dist) continue ;
        if(!vis[tp.x]) {
            okk.push_back(tp.x), vis[tp.x] = true;
        }
        for(int y : G[tp.x]) if(a[y] <= val && dist[y] > max(dist[tp.x] + 1, a[y])) {
            dist[y] = max(dist[tp.x] + 1, a[y]);
            qu.push(node(y, dist[y]));
        }
    }
}
int main() {
    // freopen("star.in", "r", stdin);
    // freopen("star.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) fa[i] = i, id[i] = i;
    sort(id + 1, id + n + 1, [&](int x, int y) {
        return a[x] < a[y];
    });
    for(int i = 1, x; i <= n; i++) {
        x = id[i];
        for(int y : G[x]) if(a[y] <= a[x]) {
            fa[getfa(x)] = getfa(y);
        }
        if(getfa(1) == getfa(n) && a[x] >= a[1] && a[x] >= a[n]) {
            val = a[x];break ;
        }
    }
    bfs(1, dist[0]);
    bfs(n, dist[1]);
    for(int i = 1; i <= n; i++) if(a[i] <= val) {
        ans = min(ans, max(dist[0][i], val) + max(dist[1][i], val));
    }
    p = 0;
    while(p < n && a[id[p + 1]] <= val) p++;
    vector<int> vc;
    while(p < n) {
        p++;
        val = a[id[p]];
        if(2 * val > ans) break ;
        vc.push_back(id[p]);
        while(p < n && a[id[p + 1]] == val) p++, vc.push_back(id[p]);
        dijk(vc, dist[0]);
        dijk(vc, dist[1]);
        vc.clear();
        for(int o : okk) {
            ans = min(ans, max(dist[0][o], val) + max(dist[1][o], val));
        }
        okk.clear();
    }
    printf("%d\n", ans);
    return 0;
}
```

---

