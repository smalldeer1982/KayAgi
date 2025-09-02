# Rudolf and Subway

## 题目描述

建桥对伯纳德没有帮助，他去哪里都迟到。然后鲁道夫决定教他乘坐地铁。

鲁道夫将地铁地图描绘成一个无向连接图，没有自循环，其中顶点代表车站。任何一对顶点之间最多有一条边。

如果可以绕过其他站点，则可以通过一条边直接在相应站点之间移动，则两个顶点通过一条边连接。鲁道夫和伯纳德居住的城市的地铁有颜色符号。这意味着站点之间的任何边缘都具有特定的颜色。特定颜色的边缘共同形成一条地铁线。地铁线不能包含未连接的边，并形成给定地铁图的连接子图。

地铁地图示例如图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941G/7c6e3ab76399bc5859a6a1ea202bbed5b214c151.png)
 鲁道夫声称，如果这条路线通过最少数量的地铁线路，这条路线将是最佳的。

帮助 Bernard 确定给定出发站和目的地站的最小数量。

## 说明/提示

第一个示例的地铁图如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941G/7c6e3ab76399bc5859a6a1ea202bbed5b214c151.png)

在第一个测试用例中，从顶点 $ 1 $ 到顶点 $ 3 $ ，可以沿着路径行进 $ 1 \rightarrow 2 \rightarrow 3 $ , 仅使用绿线。

在第二个测试用例中，从顶点 $ 1 $ 到顶点 $ 6 $ , 你可以沿着这条路旅行 $ 1 \rightarrow 2 \rightarrow 3 \rightarrow 6 $ , 使用绿线和蓝线。

在第三个测试用例中，不需要从顶点 $ 6 $ 移动到同一个顶点，所以行数为 $ 0 $ 。

在第四个测试用例中，图的所有边都属于一条线，所以答案是 $ 1 $ 。

## 样例 #1

### 输入

```
5
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 3
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
1 6
6 6
1 2 1
2 3 1
5 2 2
2 4 2
4 6 2
3 6 3
6 6
4 3
1 2 1
1 3 1
4 1 1
2 3
6 7
1 2 43
1 3 34
4 6 43
6 3 43
2 3 43
5 3 43
4 5 43
1 6```

### 输出

```
1
2
0
1
1```

## 样例 #2

### 输入

```
3
7 9
2 4 1
3 6 1
2 3 5
1 7 1
4 7 1
2 5 4
5 4 4
3 4 1
3 7 1
5 3
6 5
6 5 83691
4 1 83691
5 4 83691
3 2 83691
4 3 83691
5 1
6 7
6 1 83691
6 2 83691
2 5 83691
5 6 83691
2 3 83691
5 4 83574
3 5 83691
1 4```

### 输出

```
2
1
2```

# 题解

## 作者：2huk (赞：11)

给定一张 $n$ 个点 $m$ 条边的图。第 $i$ 条边表示地铁 $c_i$ 号线连接了点 $a_i, b_i$。

求从 $s$ 点到 $t$ 点最少需要换乘地铁几次。

---

换乘地铁的次数，也就是登上一辆新地铁的次数。这里的“新”指当前是第一辆地铁或当前地铁不同于上一辆地铁。所以我们只需要计算最小的上车次数即可。

我们不妨把每辆地铁都看成一个点。

如果存在一条边 $u_i \to v_i$ 的边权为 $c_i$，就代表这里存在一种上 $c_i$ 车的方案。那么我们建一条新边 $u_i \to c_i$ 边权为 $1$，表示可以从 $u_i$ 点耗费 $1$ 的代价登上 $c_i$ 地铁。

同理，下车的次数我们是不需要考虑的，所以我们建 $c_i \to v_i$ 边权为 $0$ 表示下车不需要消耗代价。

最终求 $s \to t$ 的最短路即可。由于边权均为 $0/1$，所以可以 0-1 bfs 代替 Dijkstra。

```cpp
vector<PII> g[N];
int dis[N];
bool st[N];

void Luogu_UID_748509() {
	int n, m; fin >> n >> m;
	int cnt = n;
	
	for (int i = 1; i <= n + m + 1; ++ i ) g[i].clear();
	map<int, int> col;
	while (m -- ) {
		int u, v, w; fin >> u >> v >> w;
		if (!col.count(w)) col[w] = ++ cnt;
		g[u].push_back({col[w], 1});
		g[v].push_back({col[w], 1});
		g[col[w]].push_back({u, 0});
		g[col[w]].push_back({v, 0});
	}
	int s, t; fin >> s >> t;
	
	deque<int> q;
	q.push_back(s);
	for (int i = 1; i <= n + cnt + 1; ++ i ) dis[i] = 1e9, st[i] = 0;
	dis[s] = 0;
	while (q.size()) {
		int u = q.front();
		q.pop_front();
        if (st[u]) continue;
        st[u] = true;
		for (auto [v, w] : g[u]) if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            if (w) q.push_back(v);
            else q.push_front(v);
        }
	}
    fout << dis[t] << '\n';
}
```

---

## 作者：yshpdyt (赞：5)

## 题意
一张连通的简单无向图，每条边有不同颜色，从一种颜色的边经过某点走向另一种颜色的边需要花费 $1$ 的代价，给定你起点和终点，求路径最小花费。
## Sol
首先肯定得要跑最短路，然后可以考虑一下怎样建图。

注意到切换不同颜色的边之间会有代价产生，所以对于每个真点，每连一条不同颜色的点可以为其新建一个虚拟颜色点，用 `pair` 类型的 `map` 记录即可。同种颜色点之间的边权为 $0$，颜色点到真点的边权为 $1$，代表需要切换颜色，真点要颜色点则不需要花费。

可以认为位于真点是无色的，一条边必须染上相应的颜色才能行走，染色和行走不需要花费代价，褪色需要花费 $1$ 的代价，颜色点走到真点可以褪色，真点走到颜色点可以染色。

最多 $m$ 种颜色，最多多建 $2m$ 个新点，边权只有 $0,1$，跑 `01bfs` 时间复杂度 $O(n+m)$。

这里偷懒用了普通的最短路。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 4000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
priority_queue<pair<ll,ll > >q;
ll f[N];
bool vis[N];
vector<pair<ll,ll> >v[N];
map<pair<ll,ll>,ll>mp;
ll n,m,st,ed;
void dij(ll s){
    for(int i=1;i<=n;i++){
        f[i]=inf;
        vis[i]=0;
    }
        f[s]=0;
        q.push({0,st});
    q.push({0,st});
    while (!q.empty()){
        auto t=q.top().se;
        q.pop();
        if(vis[t])continue;;
        vis[t]=1;
        for(auto yt:v[t]){
            ll y=yt.fi;
            if(f[y]>f[t]+yt.se){
                f[y]=f[t]+yt.se;
                q.push({-f[y],y});
            }
        }
    }
}
void sol(){
    cin>>n>>m;
    mp.clear();
    for(int i=1;i<=m;i++){
        ll x,y,c;
        cin>>x>>y>>c;
        ll nx=x,ny=y;
        if(!mp[{x,c}]){
            mp[{x,c}]=++n;
            nx=n;
            v[nx].push_back({x,1});
            v[x].push_back({nx,0});
        }else nx=mp[{x,c}];
        if(!mp[{y,c}]){
            mp[{y,c}]=++n;
            ny=n;
            v[ny].push_back({y,1});
            v[y].push_back({ny,0});
        }else ny=mp[{y,c}];
        v[nx].push_back({ny,0});
        v[ny].push_back({nx,0});
    }
    cin>>st>>ed;
    if(st==ed){
        cout<<0<<endl;
        for(int i=1;i<=n;i++)v[i].clear();
        return ;
    }
    ll ans=inf;
    dij(st);
    cout<<f[ed]<<endl;
    for(int i=1;i<=n;i++)v[i].clear();
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();

    return 0;
}
```

---

## 作者：chenxumin1017 (赞：4)

# 题意

给定一张 $N$ 个点，$M$ 条边的无向图。

每条边有一个颜色，若每次走的边与上一次走的边不同则增加 $1$ 的代价。

问你从 $s$，走到 $t$ 的最小代价。

# 思路

由于题面中告诉我们同一颜色的边形成连接子图，由此我们可以考虑将有同一颜色的边的点都连向代表这个颜色的虚点，此时问题就变成在重新建图后的图上 $s$ 到 $t$ 的距离除以二了。

时间复杂度：$O(N + M)$
空间复杂度：$O(N + M)$

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
int n, m, t, dis[MAXN];
vector<int> v[MAXN], vis;
queue<int> que;
void g(int x, int temp){
  if(dis[x] != -1)return;
  dis[x] = temp;
  que.push(x);
  vis.push_back(x);
}
void bfs(int x){
  g(x, 0);
  while(!que.empty()){
    int now = que.front();
    que.pop();
    for(int i : v[now]){
      g(i, dis[now] + 1);
    }
  }
}
void solve(){
  cin >> n >> m;
  for(int i : vis)v[i].clear(), dis[i] = -1;
  vis.clear();
  for(int i = 1, x, y, c; i <= m; i++){
    cin >> x >> y >> c;
    v[x].push_back(c + n);
    v[y].push_back(c + n);
    v[c + n].push_back(x);
    v[c + n].push_back(y);
  }
  int x, y;
  cin >> x >> y;
  bfs(x);
  cout << dis[y] / 2 << '\n';
}
int main(){
  fill(&dis[0], &dis[400001], -1);
  cin >> t;
  for(; t; t--, solve());
  return 0;
}
```

~~清空不规范，爆零总相伴。~~

---

## 作者：__vector__ (赞：3)

赛时因为这题没有 AK，有点遗憾。  
赛后写了个朴素分层图做法 TLE on test47，参考了 @Iceturky 的代码后 AC，本题解大概是我对 @Iceturky 代码的理解。  
### 做法   
首先，有一部分普通的暴力分层图是错的，[原因](https://www.luogu.com.cn/discuss/790951)，但很神奇的是它们都过了 pretests，虽然最后死于 FST。  

显然，同一种颜色的边在最优路径上都是连续的。  

所以说，假设目前到达了第 $i$ 个点，且上一个边颜色是 $j$，那么我们可以在任意颜色为 $j$ 的边上瞬移。  

也就是说，我们主要关心两个变量：当前在哪个点，到达当前点的上一条边的颜色。  

感觉瞬移有点难处理，按上述定义建立分层图很容易寄（如果有分层图做法不会寄，希望有人告诉我）。   

于是干脆将每个颜色都建成一个点，反正相同颜色可以互相瞬移。  

对于每个点，它都可以进入它的所有的边的颜色对应的连通块。就是说对于每个点 $i$，设其所有边的颜色的集合是 $s$，那么 $i$ 和 $s$ 中每个元素连无向边。  

最后，不难想到最优路径中，每个点在上述连边状态下都会访问一次自己所在的连通块节点，所以最后 $b$ 到 $e$ 最短路长度除以 $2$ 就是正确答案。

---

## 作者：MrPython (赞：3)

同：[\[ARC061E\] すぬけ君の地下鉄旅行](https://www.luogu.com.cn/problem/AT_arc061_c)。~~水两篇题解真香~~

---

想一下，生活中我们是怎样乘坐地铁的？
1. 从站厅层刷卡进站；
2. 前往站台层乘车；
3. 下车后从站台层走到站厅层；
4. 从站厅层刷卡出站，此时闸机会自动从卡中扣除相应费用。

我们将乘坐一轮地铁看作花费 $1$ 元（换乘必须先付费出站），使总花费最小。这个问题与原题是等价的。

我们每个车站都分成至少两个节点——一个站厅层和若干个站台层。从站台层前往站厅层（出站）需要支付 $1$ 元费用，而从站厅层往站台层（进站）不需要花费。通过同一条地铁来回移动不收费。想要换乘其他线路，必须先付费出站到站厅层，再进入其他线路的站台。

按照上述所说，我们将每个“站台”向相应的“站厅”连一条权值为 $1$ 的有向边，从“站厅”到各个“站台”连一条权值为 $0$ 的有向边，某条地铁线路即为一条连接两个该线路所属“站台”的权值为 $0$ 的无向边。这样，就可以建出一个 0-1 图，进行 0-1 BFS 即可。

实际操作中显式建边会很复杂。我使用 `map` 存储图和 dis 数组，`mp[x][c]` 表示在点 $x$ 乘坐 $c$ 公司的线路可以直接到达的节点，`dis[x][c]` 表示从起点到 $x$ 站的 $c$ 公司站台所需的花费。特别地，我的代码中 `dis[x][~0]` 表示到达站厅层所需要的花费。队头为站厅时，将所有的站台从队头入队；队头是站台时，将所有连在该节点的地铁线路从队头入队，以及将站厅从队尾入队。从起点的站厅开始，到终点的站厅结束，进行 0-1 BFS 即可。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;cin>>T;
    while (T--){
    size_t n,m;cin>>n>>m;
    vector<map<ui,vector<size_t>>> mp(n);
    while (m--){
        size_t x,y;ui z;cin>>x>>y>>z;--x,--y;
        mp[x][z].push_back(y),mp[y][z].push_back(x);
    }
    size_t s,t;cin>>s>>t;--s,--t;
    deque<pair<size_t,ui>> q({{s,~0}});
    vector<map<ui,ui>> dis(n);dis[s][~0]=0;
    while (!q.empty()){
        size_t p=q.front().first;ui c=q.front().second;q.pop_front();
        ui d=dis[p][c];
        if (~c){
            if (!dis[p].count(~0)||dis[p][~0]>d+1)
                dis[p][~0]=d+1,q.emplace_back(p,~0);
            for (size_t i:mp[p][c]) if (!dis[i].count(c)||dis[i][c]>d)
                dis[i][c]=d,q.emplace_front(i,c);
        }else for (pair<ui,vector<size_t>> const& i:mp[p])
            if (!dis[p].count(i.first)||d<dis[p][i.first]) 
                dis[p][i.first]=d,q.emplace_front(p,i.first);
    }
    (dis[t].count(~0)?cout<<dis[t][~0]:cout<<"-1")<<'\n';
    }
    return 0;
}
```

---

## 作者：ATION001 (赞：1)

## 题目描述
给定一个简单的无向图，你需要从点 $b$ 到达点 $e$，你想知道你需要经过几条权值（颜色）不同的边。
## 思路
首先非常明显的是这是最短路。

然后写普通的 BFS 直接喜提答案错误。

我们可以仔细想一想：如果还是在原来的颜色的边，那么贡献不变，否则贡献 $+1$，然后你就会惊奇地发现这是 01bfs，不知道的童鞋们[点这里](https://blog.csdn.net/Mr_dimple/article/details/116864052)，题解不应过长所以不做讲解。

温馨提示：**判重时记得不要判断节点是否走过，而是要判断边是否走过**。（~~可能就我犯这种错误吧。~~）

思路都出来了，很容易想到：没切换不同颜色的边贡献为 $0$，放在队列开头。切换不同颜色的边贡献为 $1$，放在队列末尾。

注意没走过的节点初始值为 $-1$，因为走过的节点值为 $0$ 也是有可能的。

最后就是代码啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int t,n,m,vis[N],x1,t1;
vector<int>v[N];
map<int,int>mp;
deque<pair<int,int>>q;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		cin>>n>>m;
		for(int i=1;i<=n+m;i++){
			v[i].clear();
		}
		mp.clear();
		int cnt=0;
		for(int i=1,l,r,o;i<=m;i++){
			cin>>l>>r>>o;
			if(!mp[o]){
				mp[o]=++cnt;
			}
			v[l].push_back(mp[o]+n),v[mp[o]+n].push_back(r);
			v[r].push_back(mp[o]+n),v[mp[o]+n].push_back(l);
		}
		cin>>x1>>t1;
		fill(vis,vis+N,-1);
		q.push_front({x1,0});
		while(q.size()){
			auto p=q.front();
			q.pop_front();
			if(vis[p.first]==-1){
				vis[p.first]=p.second;
				for(auto lv:v[p.first]){
					if(vis[lv]==-1&&lv>n){
						q.push_back({lv,p.second+1});
					}else if(vis[lv]==-1){
						q.push_front({lv,p.second});
					}
				}
			}
		}
		cout<<vis[t1]<<'\n';
	}
	return 0;
}
```

---

## 作者：lxyt_415x (赞：1)

[博客食用更佳](https://www.cnblogs.com/lxyt-415x/p/18082226)

## 简化题意

> 一个无向连通图中将边分成了不同颜色（保证同种颜色联通），问从 $b$ 到 $e$ 最短需要经过几种颜色。

## 思路

考虑因为同种颜色联通，可直接在读入的时候开两个 vector 分别存每个点属于的颜色及每种颜色有哪些点，又因为颜色数字可能跨度比较大，最好另开一个存颜色的种类。

然后就是从 $b$ 开始 BFS ，对每个点遍历它直连的所有颜色种类，然后遍历属于该颜色的所有点。


### 小优化

发现存颜色的时候会将一条边连着的两个点都存进去，存点同理，也就是一个点可能会被同颜色存很多次且可能存很多个同颜色，这里开两个 map 去重可以大大降低复杂度。

## 注意！！！

因为 codeforces 上可以 hack 别人的代码，所以赛后数据有卡 hash 表的，建议观看 [这篇](https://codeforces.com/blog/entry/62393%E3%80%82)  CF 大佬的博客，防止自己的 hash 表被卡。

开两个数组存遍历过的颜色块和节点，复杂度显然是线性的。

## 代码

```cpp
#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/hash_policy.hpp>
#define ll long long
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const int N=4e5+10;
int T,n,m,b,e,ans;
bool fc[N],fl[N],fd[N];
queue<pair<int,int>>q;
vector<int>col[N],v[N],vec;
unordered_map<int,bool,custom_hash>mp1;
unordered_map<long long,bool,custom_hash>mp2;
inline void init()
{
	while(!q.empty())
		q.pop();
	for(auto it : col[e])
		fl[it]=false;
	for(int i=1;i<=n;i++)
	{
		fd[i]=false;
		col[i].clear();
	}
	for(auto it : vec)
	{
		fc[it]=false;
		v[it].clear();
	}
	ans=1e9;
	vec.clear();
	mp1.clear();
	mp2.clear();
	return ;
}
inline void bfs(int x,int t)
{
	fd[x]=true;
	q.push({x,t});
	while(!q.empty())
	{
		x=q.front().first;
		t=q.front().second;
		q.pop();
		for(auto i : col[x])
		{
			if(fc[i])
				continue;
			if(fl[i])
			{
				ans=min(ans,t);
				return ;
			}
			fc[i]=true;
			for(auto j : v[i])
				if(!fd[j])
				{
					fd[j]=true;
					q.push({j,t+1});
				}
		}
	}
	return ;
}
int main()
{
	cin>>T;
	while(T--)
	{
		init();
		scanf("%d%d",&n,&m);
		for(int i=1,x,y,c;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&c);
			if(mp1.find(c)==mp1.end())
			{
				mp1[c]=1;
				vec.push_back(c);
			}
			if(mp2.find(((ll)x<<32)|c)==mp2.end())
			{
				mp2[((ll)x<<32)|c]=1;
				v[c].push_back(x);
				col[x].push_back(c);
			}
			if(mp2.find(((ll)y<<32)|c)==mp2.end())
			{
				mp2[((ll)y<<32)|c]=1;
				v[c].push_back(y);
				col[y].push_back(c);
			}
		}
		scanf("%d%d",&b,&e);
		if(b==e)
		{
			printf("0\n");
			continue;
		}
		for(auto it : col[e])
			fl[it]=true;
		bfs(b,1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：zhlzt (赞：0)

### 题解

显然在途中两次乘坐同一条线路的地铁（设为 $a\to b$ 和 $c\to d$）肯定不比一次性做到底更优（即 $a\to d$），那么肯定存在一种最优方案，使得其中每一条线路都是连续的。

因此，我们对于每一个地铁站，若他在线路 $a$ 上，那么从他向 $a$ 连一条权值为 $1$ 的边（因为要上一条新线路），再从 $a$ 向他连一条权值为 $0$ 的边（下地铁不会增加线路数），最后跑一遍从起点到终点的最短路即可。

为了防止地铁线路编号不一定连续导致清空时 TLE 的问题，最好给地铁线路重新动态编号，可以用 `std::map`。
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef vector<pi> vpi;
typedef greater<pi> gpi;
const int maxn=2e5+10;
const int inf=2e9;
map<int,int>id;
vector<pi>edge[maxn<<1]; 
int dis[maxn<<1];
int dijkstra(int s,int t){
	priority_queue<pi,vpi,gpi>que;
	que.emplace(0,s);
	while(que.size()){
		pi temp=que.top(); que.pop();
		int u=temp.second,d=temp.first;
		if(dis[u]<=d) continue; 
		dis[u]=d;
		for(pi cur:edge[u]){
			int v=cur.first,w=cur.second;
			que.emplace(d+w,v);
		}
	}
	return dis[t];
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,m;scanf("%d%d",&n,&m);
		int cnt=0; id.clear();
		for(int i=1;i<=n;i++) edge[i].clear();
		for(int i=1;i<=m;i++){
			int u,v,c;scanf("%d%d%d",&u,&v,&c);
			if(id.find(c)==id.end())
				id[c]=++cnt,edge[n+cnt].clear();
			edge[u].emplace_back(n+id[c],1);
			edge[v].emplace_back(n+id[c],1);
			edge[n+id[c]].emplace_back(u,0);
			edge[n+id[c]].emplace_back(v,0);
		}
		fill(dis+1,dis+1+n+cnt,inf);
		int s,t;scanf("%d%d",&s,&t);
		printf("%d\n",dijkstra(s,t));
	} 
	return 0;
}
```

---

## 作者：OPEC (赞：0)

# [CF1941G Rudolf and Subway](https://www.luogu.com.cn/problem/CF1941G)

这道题是个最短路，但难再建图上。设 $u\to v$ 有一条连边，则可以花费 $1$ 上车，也可以花费 $0$ 下车，所以要建建一个二层的图，分别是 $u\to v,v\to u$ 以及 $u\to v',v\to u'$，再 dijkstra 一遍就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n,m,st,ed;
vector<pair<int,int> > g[N];
int vis[N],dis[N];
int dij()
{
	for(int i=1;i<=n;i++)
	{
		vis[i]=0;
		dis[i]=INF;
	}
	dis[st]=0;
	deque<int> dq;
	dq.push_back(st);
	while(!dq.empty())
	{
		int u=dq.front();
		dq.pop_front();
		if(vis[u])
		{
			continue;
		}
		vis[u]=1;
		for(auto e:g[u])
		{
			int v=e.first;
			int w=e.second;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(w)
				{
					dq.push_back(v);
				}
				else
				{
					dq.push_front(v);
				}
			}
		}
	}
	return dis[ed];
}
int spfa()
{
	for(int i=1;i<=n;i++)
	{
		vis[i]=0;
		dis[i]=INF;
	}
	dis[st]=0;
	queue<int> q;
	q.push(st);
	vis[st]=1;
	while(q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(auto e:g[u])
		{
			int v=e.first;
			int w=e.second;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(vis[v]==0)
				{
					q.push(v);
				}
			}
		}
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		g[i].clear();
	}
	cin>>n>>m;
	map<int,int> mp;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		if(mp.find(w)==mp.end())
		{
			mp[w]=++n;
		}
		g[u].push_back({mp[w],1});
		g[v].push_back({mp[w],1});
		g[mp[w]].push_back({u,0});
		g[mp[w]].push_back({v,0});
	}
	cin>>st>>ed;
	int ans=dij();
	cout<<ans<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

既然可以 Dijkstra 放 $O(n\log n)$ 的算法， 不如不用脑子。

正解是看成上/下地铁的过程，连边之后可以 0/1 bfs 了。

VP 的时候不是这个做法。

考虑暴力的 dp。$f_{i,j}$ 表示点 $i$，上一个节点颜色为 $j$ 的最小代价。发现这个空间是可以优化的，因为 $(i,j)$ 的对数只有 $O(n+m)$ 个，这里可以二分，多一个 $\log$。

现在有 $O(n+m)$ 个点，然后跑 0/1 bfs，但是发现会 T。原因是如果对于每一个点都遍历所有的边，那么边数就变成 $O(m^2)$ 了（就是菊花图），这显然是不能接受的。

所以，我们需要缩减边数。

思考，为什么记录不同的 $j$。

我认为，是为了减少下一步的花费（不用 $+1$）。

那么，对于和上一个颜色不同颜色的边，是没有用处的。

这些其他颜色的边可以用 $f_{i,0}$ 来解决，表示 $\min\limits_{j=1}^{totcol}\{f_{i,j}\}$，$f_{i,0}$ 给别人贡献的时候不考虑颜色相同不用增加贡献，因为这个颜色相同的已经考虑过了。

于是边数还是 $O(m)$ 的。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define mp make_pair
#define sec second
#define fir first
using namespace std;
const int N = 2e5 + 5, M = 2e5 + 5, inf = 0x3f3f3f3f;
int T, n, m, fir[N], nxt[M << 2], son[M << 2], c[M << 2], x, y, z, tot, f[M << 2], idx, s, t, id, ans, id1;
bool vis[M << 2];
pii a[M << 2];
vector<int> vec[M << 2];
deque<int> q;
inline void add(int x, int y, int z){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
	c[tot] = z;
}
inline void init(){
	for(int i = 1; i <= n; i++) fir[i] = 0;
	for(int i = 1; i <= tot; i++) nxt[i] = 0;
	for(int i = 1; i <= idx; i++) vec[i].clear();
	tot = idx = 0;
}
inline void Dij(){
	for(int i = 1; i <= n; i++){
		a[++idx] = mp(i, 0);
	}
	sort(a + 1, a + idx + 1);
	idx = unique(a + 1, a + idx + 1) - a - 1;
	for(int i = 1; i <= idx; i++){
		if(a[i].fir == s && a[i].sec == 0) f[i] = 0, q.push_back(i);
		else f[i] = inf;
		vis[i] = 0;
	}
	for(int x = 1; x <= n; x++){
		for(int i = fir[x]; i ; i = nxt[i]){
			id1 = lower_bound(a + 1, a + idx + 1, mp(x, c[i])) - a;
			vec[id1].push_back(i);
		}
	}
	int tp;
	#define X a[tp].fir
	#define col a[tp].sec
	#define d f[tp]
	ans = inf;
	while(!q.empty()){
		tp = q.front();
		q.pop_front();
		if(vis[tp]) continue ;
		vis[tp] = 1;
//		printf("%d %d %d %d\n", tp, X, col, d);
		if(X == t){
			ans = d;
			return ;
		}
		if(a[tp].sec == 0){
			for(int i = fir[X]; i ;i = nxt[i]){
				id = lower_bound(a + 1, a + idx + 1, mp(son[i], c[i])) - a;
				id1 = lower_bound(a + 1, a + idx + 1, mp(son[i], 0)) - a;
				if(f[id] > d + 1){
					f[id] = d + 1;
					q.push_back(id);
				}
				if(f[id1] > d + 1){
					f[id1] = d + 1;
					q.push_back(id1);
				}
			}
		}
		else{
			for(int i : vec[tp]){
				id = lower_bound(a + 1, a + idx + 1, mp(son[i], c[i])) - a;
				id1 = lower_bound(a + 1, a + idx + 1, mp(son[i], 0)) - a;
				if(f[id] > d){
					f[id] = d;
					q.push_front(id);
				}
				if(f[id1] > d){
					f[id1] = d;
					q.push_front(id1);
				}
			}
		}	
	}
	#undef x
	#undef col
	#undef d
}
int main(){
//	freopen("data.in", "r", stdin);
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++){
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z), add(y, x, z);
			a[++idx] = mp(x, z);
			a[++idx] = mp(y, z);
		}
		scanf("%d%d", &s, &t);
		Dij();
		while(!q.empty()) q.pop_front();
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
我们可以把问题转化一下：设每辆地铁都有一个固定车站 $x$，若想在 $y$ 车站上车，就相当于是走过了一条 $y\to x,w=1$ 的边，若想在 $y$ 车站下车，就相当于走过一条 $x\to y,w=0$ 的边。然后跑一遍最短路就好了，因为边权只有 $0,1$，所以也可以用双端队列优化。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int inf = 1e9;
int t, n, m, x, y, c, d[400005];
vector <pii> v[400005];
deque <int> q;
bitset <400005> vis;
map <int, int> r;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		x = n + m;
		r.clear ();
		for (int i = 1; i <= x; ++ i)
			v[i].clear (), vis[i] = 0, d[i] = inf;
		while (m --) {
			cin >> x >> y >> c;
			if (! r[c])
				r[c] = ++ n;
			c = r[c];
			v[x].push_back ({c, 1});
			v[y].push_back ({c, 1});
			v[c].push_back ({x, 0});
			v[c].push_back ({y, 0});
		}
		cin >> x >> y;
		d[x] = 0;
		q.push_back (x);
		while (! q.empty ()) {
			x = q.front ();
			q.pop_front ();
			if (x == y) {
				while (! q.empty ())
					q.pop_back ();
				cout << d[x] << '\n';
				break ;
			}
			if (vis[x])
				continue ;
			vis[x] = 1;
			for (pii& i : v[x])
				if (d[x] + i.second < d[i.first])
					if (i.second)
						d[i.first] = d[x] + 1, q.push_back (i.first);
					else
						d[i.first] = d[x], q.push_front (i.first);
		}
	}
	return 0;
}
```

---

