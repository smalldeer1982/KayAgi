# Travel in Desert

## 题目描述

### 题目大意
沙漠中有$n$ 个绿洲（编号为$1-n$ ）和$e$ 条连接绿洲的双向道路。每条道路都有一个长度$d$ 和一个温度值$r$ 。给定起点绿洲编号$s$ 和终点绿洲编号$t$ ，求出一条$s$ 到$t$ 的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

## 样例 #1

### 输入

```
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4```

### 输出

```
1 3 6
38.3 38.3```

# 题解

## 作者：ZAGER (赞：2)

##题解

传送门：[透彻](https://www.cnblogs.com/ZAGER/p/9917395.html)

首先，说一下洛谷上翻译有坑，输入时是先输入温度$r$，再输入长度$d$。

因为要让最大值最小，所以很容易想到二分，但快$NOIP$了还是练了一下最小瓶颈路。

首先有两道最小瓶颈路的题[货车运输](https://www.luogu.org/problemnew/show/P1967)，[星际导航](https://www.luogu.org/problemnew/show/P2245)。

我们发现这道题有两个限制温度和长度，不好处理，所以我们要去消除一层限制。

因为要首先保证最高温度尽量小，所以先考虑温度。

有些经验的都应该能想到最小瓶颈路，跑出$s$到$t$的最高温度的最小值$maxtem$。

然后把温度不大于$maxtem$的边加入图中，跑最短路记录路径即可。

## code：

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define N 10005
#define INF 0x3f3f3f3f
#define R register
using namespace std;
template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}
int n,m,s,t,num,fa[N],tot,h[N];
double maxtem,dist[N];
bool vis[N];
vector<int> path;
struct MST{
    int u,v;
    double len,tem;
    friend bool operator < (const MST &a,const MST &b){
        return a.tem<b.tem;
    }
}tre[N];
struct node{
    int nex,to;
    double dis;
}edge[N<<1];
inline void add(R int u,R int v,R double w){
    edge[++tot].nex=h[u];
    edge[tot].to=v;
    edge[tot].dis=w;
    h[u]=tot;
}
inline void ins(R int u,R int v,R double w,R double t){
    tre[++num].u=u;
    tre[num].v=v;
    tre[num].len=w;
    tre[num].tem=t;
}
inline int find(R int x){
    if(x!=fa[x])fa[x]=find(fa[x]);
    return fa[x];
}
struct HeapNode{
    int u;
    double d;
    friend bool operator < (const HeapNode &a,const HeapNode &b){
        return a.d>b.d;
    }
};
priority_queue<HeapNode> q;
inline void dij(){
    for(R int i=1;i<=n;i++)dist[i]=INF,vis[i]=0,fa[i]=0;
    dist[s]=0;q.push((HeapNode){s,dist[s]});
    while(!q.empty()){
        R int x=q.top().u;q.pop();
        if(vis[x])continue;vis[x]=1;
        for(R int i=h[x];i;i=edge[i].nex){
            R int xx=edge[i].to;
            if(dist[xx]>dist[x]+edge[i].dis){
                dist[xx]=dist[x]+edge[i].dis;
                fa[xx]=x;
                q.push((HeapNode){xx,dist[xx]});
            }
        }
    }
    R int x=t;
    path.clear();
    while(x!=s){
        path.push_back(x);
        x=fa[x];
    }
    path.push_back(s);
    for(R int i=path.size()-1;i>=1;i--)
        printf("%d ",path[i]);
    printf("%d\n",path[0]);
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        num=tot=0;maxtem=0;
        memset(h,0,sizeof(h));
        memset(fa,0,sizeof(fa));
        read(s);read(t);
        R double w,te;
        for(R int i=1,u,v;i<=m;i++){
            read(u);read(v);scanf("%lf%lf",&te,&w);
            ins(u,v,w,te);
        }
        for(R int i=1;i<=n;i++)fa[i]=i;
        sort(tre+1,tre+1+m);
        for(R int i=1;i<=m;i++){
            R int x=find(tre[i].u),y=find(tre[i].v);
            if(x!=y){
                fa[x]=y;
                maxtem=max(maxtem,tre[i].tem);
                if(find(s)==find(t))break;
            }
        }
        for(R int i=1;i<=m;i++){
            if(tre[i].tem>maxtem)break;;
            add(tre[i].u,tre[i].v,tre[i].len);
            add(tre[i].v,tre[i].u,tre[i].len);
        }
        dij();
        printf("%.1f %.1f\n",dist[t],maxtem);
    }
    return 0;
} 
```



---

## 作者：syLph (赞：0)

挺简单的一道 MST。

首先将每条边按照温度从小到大排序，然后直接跑 Kruskal 板子，直到 $s$ 与 $t$ 连通为止。这样我们就能求出所需的最大温度的最小值 $T$。

然后直接在温度不大于 $T$ 的图上跑最短路即可。

如果用 SPFA（Dijstrka 一样），每次在松弛的时候记录 $pre_y = x$，建最短路树，然后逆序输出路径即可。

注意有多测，行末不要有多余的空格，否则会 PE。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 20010;

int head[maxn],nxt[maxn],ver[maxn],fa[maxn],tot = 1,pre[maxn];
double edg[maxn],MAXEDGE,e[maxn],dist[maxn];
int n,m,s,t,ins[maxn]; 

typedef struct{int u,v;double c,t;}edge;edge tt[maxn];

bool cmp(edge a,edge b){
    return (a.t == b.t) ? a.c < b.c : a.t < b.t;
}

int find(int x){
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void add(int x,int y,double z,double c){
    ver[++tot] = y,e[tot] = c,edg[tot] = z,nxt[tot] = head[x],head[x] = tot;
}

void spfa(int s){
    for(int i = 1 ; i <= n ; i ++) dist[i] = 999999999.9999;
    queue<int> q; q.push(s); dist[s] = 0; ins[s] = 1;
    while(!q.empty()){
        int x = q.front(); q.pop(); ins[x] = 0;
        for(int i = head[x] ; i ; i = nxt[i]){
            int y = ver[i];
            if(dist[y] > dist[x] + edg[i] && e[i] <= MAXEDGE + 1e-6){
                dist[y] = dist[x] + edg[i];
                pre[y] = x;
                if(!ins[y]) q.push(y),ins[y] = 1;
            }
        }
    }
}

int main(){
	while(cin >> n >> m >> s >> t && n && m && s && t){
		for(int i = 1 ; i <= n ; i ++) fa[i] = i;
		memset(head,0,sizeof head); tot = 1;
		memset(tt,0,sizeof tt);
		memset(pre,0,sizeof pre);
	    for(int i = 1 ; i <= m ; i ++){
	        cin >> tt[i].u >> tt[i].v >> tt[i].t >> tt[i].c;
	        add(tt[i].u,tt[i].v,tt[i].c,tt[i].t),add(tt[i].v,tt[i].u,tt[i].c,tt[i].t);
	    }
	    sort(tt+1,tt+m+1,cmp);
	    for(int i = 1 ; i <= m ; i ++){
	        int u = tt[i].u,v = tt[i].v; double temper = tt[i].t;
	        if(find(u)==find(v)) continue;
	        u = find(u),v = find(v);
	        fa[v] = u;
	        if(find(s)==find(t)){
	            MAXEDGE = temper;
	            break;
	        }
	    }
	    spfa(s); vector<int> ans;
	    int g = t,h = t;
	    while(h){
	        h = pre[g]; ans.push_back(g);
	        g = h; 
	    }
	    for(int i = ans.size() - 1 ; i >= 1 ; i --) cout << ans[i] << ' '; 
	    cout << ans[0] << endl;
	    printf("%.1lf %.1lf\n",dist[t],MAXEDGE);
	}
    return 0;
}
```


---

## 作者：Uuuuuur_ (赞：0)

## 问题简述
有一张无向图，边有两种权值：温度和长度。给定起点和终点，求一条路径，使得途径道路最高温度尽可能低，如果有多条，选择路程最短的。

## 思路
最小瓶颈路 + 最短路。

距离是建立在温度尽量低情况下的，所以先解决“最大温度最小”这个问题。

这是一个最小瓶颈路问题，顾名思义，一条路径的好坏，由这条路径上的瓶颈——最长的一条边决定。这个问题有两种解决方法：一、最大值最小，标准的二分模型，只要二分最高温度，判断能否到达；二、最小生成树，两点间在最小生成树上的路径，一定是一条最小瓶颈路（回顾一下 kruskal 算法的过程，从小到大加边，自然完成了路径上最大值尽可能小）。

接下来就是路程尽可能短，这个自然想到最短路，但怎么结合上面的条件呢？可以发现，我们并不关心瓶颈路是哪条，只关心这个瓶颈温度是多少，也就是说，所有低于瓶颈温度的边，都可以走。所以，建一张新图，把所有温度小于等于瓶颈温度的边加进去，在上面跑一遍最短路，还要记录路径，只要维护一个数组，记录每个点由哪个点转移过来就好了。

我选择了 kruskal + dijkstra 分别解决这两个问题。时间复杂度 $O(e \log e)$。
 
## 坑点
行末不要有空格，保留一位小数。

## 代码
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
struct edge{
    int u, v;
    double w, t;
    bool operator < (const edge &b) const {
        return t < b.t;
    }
};
struct node {
    int v;
    double w;
};
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 105;

int n, m;
int st, en;
int fa[N];
int pre[N];
double maxt;
double d[N];
bool used[N * N];
edge e[N * N];
vector<node> g[N];
vector<node> h[N];

void init() {
    maxt = 0;
    memset(used, 0, sizeof used);
    memset(pre, 0, sizeof pre);
    fill(d, d + N, 1e8);
    for (int i = 0; i < N; i++) vector<node>().swap(g[i]), vector<node>().swap(h[i]);
    for (int i = 1; i <= n; i++) fa[i] = i;
    
} 
int get(int x) {return fa[x] == x ? x : fa[x] = get(fa[x]);}
void merge(int x, int y) {
    int fx = get(x), fy = get(y);
    if (fx != fy) fa[fx] = fy;
}
void print_path(int s, int t) {
    
    if (s == t) {cout << s << ' '; return;}
    print_path(s, pre[t]);
    if (t != en) cout << t << ' ';
    else cout << t;
}
void dij() {
    set<pair<double, int> > q;
    d[st] = 0;
    q.insert(make_pair(0, st));
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());
        
        for (int i = 0; i < g[u].size(); i++) {
            
            int v = g[u][i].v;
            
            double w = g[u][i].w;
            if (d[u] + w < d[v]) {
                q.erase(make_pair(d[v], v));
                d[v] = d[u] + w;
                pre[v] = u;
                q.insert(make_pair(d[v], v));
            }
        }
    }
}
bool dfs(int u, int fa) {
    if (u == en) return 1;
    for (int i = 0; i < h[u].size(); i++) {
        int v = h[u][i].v;
        double t= h[u][i].w;
        if (v != fa) {
            if (dfs(v, u)) {
                maxt = max(maxt, t);
                return 1;
            }
        }
    }
    return 0;
}
void kruskal() {
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v; double t = e[i].t, w = e[i].w;
        if (get(u) != get(v)) {
            merge(u, v);
            h[u].push_back({v, t});
            h[v].push_back({u, t});
            used[i] = 1;
        }
    }
    dfs(st, 0);
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v; double t = e[i].t, w = e[i].w;
        if (t <= maxt) {
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        } 
    }
}
signed main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        cin >> st >> en;
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            double w, t;
            cin >> u >> v >> t >> w;
            e[i] = {u, v, w, t};
        }
        kruskal();
        dij();
        print_path(st, en);
        cout << '\n';
        cout << fixed << setprecision(1) << d[en] << ' ' << maxt << '\n';
    }
    return 0;
}
```


---

## 作者：lzyqwq (赞：0)

来一个二分 + Dijkstra 堆优化的题解。

个人认为这样的二分比 @Ceriser 的方法更优。因为长度和温度只有一位小数（英文题面里说了），所以我们完全可以将他们转化成整数来做，这样可以避免精度误差。

如何二分？

考虑二分最大温度最小值，二分的左端点是原图中最小的温度（不能比它再小了），右端点是原图中最大的温度（不能比它再大了）。对于二分出来的 $mid$ 值，我们跑堆优化 Dijkstra，注意在枚举出边的时候要过滤掉温度值 $r>mid$ 的边。如果在 Dijkstra 的过程中能遍历到 $t$，说明 $mid$ 可行，否则不可行。

我们使用一个 $la$ 数组维护到每个点路径最短时的前驱节点。若 $dis_u+w<dis_v$（$w$ 为边长），我们在将 $dis_v$ 赋值为 $dis_u+w$ 的同时将 $la_v$ 赋值成 $u$（因为当前从 $u$ 走到 $v$ 最短，所以 $v$ 是从 $u$ 这个前驱节点到达的）。

在每次找到可行的解后，我们更新答案的温度值和道路长度，并用栈维护路径，最后按照题目要求输出即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105;
int n, m, s, t, le, ri, dis[N], ans, la[N], p, fd;
stack<int> stk;
bool vis[N];
struct edge {
    int x, r, d;
};
vector<edge> g[N];
struct node {
    int x, s;
    bool operator<(const node &a)const {
        return s > a.s;
    }
};
priority_queue<node> q;
inline bool dij(int x) {
    memset(dis, 0x3f, sizeof(dis));//初始化
    memset(vis, 0, sizeof(vis));
    memset(la, 0, sizeof(la));
    q = priority_queue<node>();
    dis[s] = 0;
    q.push(node{s, 0});
    while (q.size()) {
        node k = q.top();
        q.pop();
        if (k.x == t) {
            return 1;//能到达
        }
        if (vis[k.x]) {
            continue;
        }
        vis[k.x] = 1;
        for (auto i : g[k.x]) {
            if (i.r <= x && k.s + i.d < dis[i.x]) {
                dis[i.x] = k.s + i.d;
                la[i.x] = k.x;
                q.push(node{i.x, dis[i.x]});
            }
        }
    }
    //如果能到达，说明入过队，在上面的 while 循环中函数就能返回值 true。若执行到这一步，说明在 while 循环中不能返回值 true，即不能到达终点。因此返回值 false
    return 0;
}
int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    while (cin >> n >> m >> s >> t) {
        if (s == t) {//特判
            cout << s << "\n0.0 0.0\n";
            continue;
        }
        le = 1e9;
        ri = 0;
        memset(g, 0, sizeof(g));
        for (int i = 1, u, v; i <= m; i++) {
            double r, d;
            cin >> u >> v >> r >> d;
            r *= 10;//转化成整数
            d *= 10;
            le = min(le, (int)r);//找左端点
            ri = max(ri, (int)r);//找右端点
            g[u].push_back(edge{v, (int)r, (int)d});
            g[v].push_back(edge{u, (int)r, (int)d});
        }
        while (le <= ri) {
            int mid = le + ri >> 1;
            if (dij(mid)) {
                ans = mid;
                ri = mid - 1;
                p = t;//更新答案
                fd = dis[t];
                stk = stack<int>();
                while (p) {
                    stk.push(p);
                    p = la[p];
                }
            } else {
                le = mid + 1;
            }
        }
        while (stk.size() > 1) {//输出路径，这里终点我是另外输出的，避免 UVA 不过滤行末空格
            cout << stk.top() << ' ';
            stk.pop();
        }
        cout << t << '\n' << fixed << setprecision(1) << fd * 1.0 / 10 << ' ' << ans * 1.0 / 10 << '\n';//转回小数并输出
    }
    return 0;
}
```

完结撒花

---

## 作者：Cerisier (赞：0)

题解里面貌似没有二分+最短路啊，我写一篇吧。

## 题目概述

给出一张无向图，每条边有两个权值 $r,d$。给出起点 $s$ 和终点 $t$，找到一条路径使得 $r$ 尽可能小（有可能有多条，找到最短的一条）。

## 思路

我看到这道题第一眼就想到了 [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/blog/670262/p1462-tong-wang-yu-ge-rui-ma-di-dao-lu)，这两道题的相似之处就是在于都需要找到一条路径上的最值。求它的方法便是使用二分。而区别就是，P1462 是整数二分，而这道题是实数二分，会涉及到精度误差这个问题。但是相信能写到这题的人，实数二分应该不是问题。

### 『途经的最高温度』

我们可以想象一个场景，一位旅行家的耐最高温度为 $\text{limit}$，他从 $s$ 出发想要到达 $t$，但是他的耐热程度不够，无法通过一些路，导致他最后无法到达 $t$，但是，有些旅行家的耐最高温度很高，那么他就可以到达 $t$，在这个情境中，我们其实求的就是能到达 $t$ 的冒险家中耐最高温度最高的是谁。同样，我们可以设定一个值 $\text{limit}$ 来限制可以通过的路的最大值，当这个值可以从 $s$ 到达 $t$ 的时候，代表 $\text{limit}$ 就是一个合法的值，但是，我们要求这个值最小，这么想，应该就能想到『二分』。

步骤：

1. 设置左端点为图中温度最小值，右端点为图中温度最大值
2. 当左端点小于右端点：
   1. 令 $\text{mid}=\dfrac{\text{左端点+右端点}}{2}$
   2. 以 $\text{mid}$ 作为 $\text{limit}$ 跑一次最短路
      1. 如果 $s$ 可以到达 $t$，那么 $r=\text{mid}$。
      2. 否则，$l=\text{mid}$。
3. 最后 $r$ 就是『途径的最高温度』。

### 『路线』和『路线的总长度』

为了让『途径的最高温度』最小，我们其实可以直接将所有温度小于『途径的最高温度』的边加入到一个新的图中（我的代码中原图是 $\text g$，而新图是 $\text{g1}$），跑一边最短路即可。

对于存路线，可以建立一个 $\text{pre}$ 数组来储存当前节点的前驱结点，在转移的时候修改即可。

## 代码

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<iomanip>
#include<climits>
using namespace std;

#define int long long

const int maxn = 110;
const double eps = 1e-9;

int n, m;
int s, t;

struct node {
	int v;
	double w, temp;
	node(int vv, double ttemp, double ww) {
		v = vv, temp = ttemp, w = ww;
	}
};
vector<node> g[maxn];

double d[maxn];
bool inqueue[maxn];
bool SPFA1(double limit) {
	for (int i = 0; i < maxn; i++) {
		d[i] = 1e9;
	}
	memset(inqueue, 0, sizeof(inqueue));
	queue<int> q;
	q.push(s);
	inqueue[s] = true;
	d[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].v;
			double w = g[u][i].temp;
			if (w < limit) {
				if (d[v] > d[u] + w) {
					d[v] = d[u] + w;
					if (!inqueue[v]) {
						q.push(v);
						inqueue[v] = true;
					}
				}
			}
		}
	}
	if (d[t] < 1e9) {
		return true;
	}
	return false;
}

vector<node> g1[maxn];
int pre[maxn];
void SPFA() {
	for (int i = 0; i < maxn; i++) {
		d[i] = 1e9;
	}
	memset(inqueue, 0, sizeof(inqueue));
	memset(pre, -1, sizeof(pre));
	queue<int> q;
	q.push(s);
	inqueue[s] = true;
	d[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		for (int i = 0; i < g1[u].size(); i++) {
			int v = g1[u][i].v;
			double w = g1[u][i].w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				pre[v] = u;
				if (!inqueue[v]) {
					q.push(v);
					inqueue[v] = true;
				}
			}
		}
	}
}

signed main() {
	cout << fixed << setprecision(1);
	while (cin >> n >> m) {
		double minTemp = INT_MAX, maxTemp = INT_MIN;
		cin >> s >> t;
		for (int i = 0; i < maxn; i++) {
			g[i].clear();
			g1[i].clear();
		}
		for (int i = 1; i <= m; i++) {
			int u, v;
			double temp, w;
			cin >> u >> v >> temp >> w;
			g[u].push_back(node(v, temp, w));
			g[v].push_back(node(u, temp, w));
			minTemp = min(minTemp, temp);
			maxTemp = max(maxTemp, temp);
		}
		double l = minTemp, r = maxTemp;
		while (l + eps < r) {
			double mid = (l + r) / 2;
			if (SPFA1(mid)) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		double limit = r;
		//cout << limit << endl;
		// 重构一张每条边温度都小于 limit 的图
		for (int u = 1; u <= n; u++) {
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i].v;
				double temp = g[u][i].temp;
				double w = g[u][i].w;
				if ((abs(temp - limit) <= eps) || temp < limit) {
					g1[u].push_back(node(v, temp, w));
					//g1[v].push_back(node(u, temp, w));
					//cout << u << ' ' << v << ' ' << w << endl;
				}
			}
		}
		SPFA();

		int cur = t;
		vector<int> path;
		do {
			path.push_back(cur);
			cur = pre[cur];
		} while (pre[cur] != -1);
		path.push_back(cur);
		for (int i = path.size() - 1; i > 0; i--) {
			cout << path[i] << ' ';
		}
		cout << path[0] << endl;
		cout << d[t] << ' ' << limit << endl;
	}
	return 0;
}
```

附上 [数据生成器](https://www.luogu.com.cn/discuss/449053)

---

## 作者：MikukuOvO (赞：0)

### 题目大意
沙漠中有n个绿洲（编号为1−n）和e条连接绿洲的双向道路。每条道路都有一个长度d和一个温度值r。给定起点绿洲编号s和终点绿洲编号t，求出一条s到t的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

### 题目分析
首先，如果没有温度的限制，那么这道题就是一道裸的最短路问题，但是现在多了一个温度的限制，我们首先要满足温度的限制，那么如何满足呢？

我们考虑先将所有边排一个序，每一次往图中加边，直到起点终点联通为止。

正确性证明：首先，由于我们已经将所有边排了一个序，那么如果利用已经选择的边就能使起点和终点联通，那么显然其他的边一定不会被考虑，还可以加一个小优化，加边时花费一次并查集查询是否成环的代价来使得构造的图的边变少

然后我们愉快的跑一个dij就可以啦！！！

### 性能分析
排序mlogm,最短路dij (n+m)logn,总复杂度近似mlogm

### 代码实现
```cpp
//Head File _DAG_
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
#include<deque>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

//Debuger _DAG_
#define dej printf("Running\n");
#define dep1(x) cout<<#x<<"="<<x<<endl;
#define dep2(x,y) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<endl;
#define dep3(x,y,z) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<' '<<#z<<"="<<z<<endl;

//Replace _DAG_
#define LL long long
#define LB long double
#define reg register
#define il inline
#define inf 1000000007

//DTL _DAG_
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define UF(i,a,b) for(reg int i=a;i<=b;i++)
#define DF(i,a,b) for(reg int i=a;i>=b;i--)
#define SUF(c,a,b) for(reg int *S=c+a,*E=c+b+1;*S!=*E;*S++)
#define SDF(c,a,b) for(reg int *S=c+a,*E=c+b-1;*S!=*E;*S--)

//Sorce Limit _DAG_
#define maxn 105
#define maxm 10005

struct ALLOC
{
    int u,v;
    double r,d;
};
struct EDGE
{
    int to,nxt;
    double d;
};
ALLOC alloc[maxm];
EDGE edge[maxm*2];
int n,m,s,t,num,sum,cnt,temp;
int fa[maxn],head[maxn],f[maxn],ans[maxn];
double maxr,dis[maxn],maxd,bian[maxn][maxn];
bool vis[maxn];
priority_queue<pair<double,int> >q;

il bool cmp(ALLOC x,ALLOC y)
{
    return x.r<y.r;
}
il int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
il void add(int x,int y,double a)
{
    edge[++cnt].to=y;
    edge[cnt].d=a;
    edge[cnt].nxt=head[x];
    head[x]=cnt;
}
il void Dijkstra()
{
    UF(i,1,n) dis[i]=inf,vis[i]=0;
    dis[s]=0,q.push(make_pair(0,s));
    while(!q.empty())
    {
        s=q.top().second;
        q.pop();
        if(vis[s]==1) continue;
        vis[s]=1;
        for(int i=head[s]; i; i=edge[i].nxt)
        {
            if(dis[edge[i].to]>dis[s]+edge[i].d)
            {
                dis[edge[i].to]=dis[s]+edge[i].d;
                f[edge[i].to]=s;
                if(vis[edge[i].to]==0) q.push(make_pair(-dis[edge[i].to],edge[i].to));
            }
        }
    }
}
int main()
{
    while(scanf("%d%d%d%d",&n,&m,&s,&t)==4)
    {
        num=0,sum=0,cnt=0,temp=0,maxr=0,maxd=0;
        memset(head,0,sizeof(head));
        memset(f,0,sizeof(f));
        memset(bian,0,sizeof(bian));
        UF(i,1,m)
        {
            int x,y;
            double a,b;
            scanf("%d%d%lf%lf",&x,&y,&a,&b);
            alloc[++num].u=x,alloc[num].v=y,alloc[num].r=a,alloc[num].d=b;
        }
        sort(alloc+1,alloc+num+1,cmp);
        UF(i,1,n) fa[i]=i;
        UF(i,1,m)
        {
            int fx=find(alloc[i].u),fy=find(alloc[i].v);
            if(fx==fy) continue;
            fa[fx]=fy;
            sum++;
            maxr=max(maxr,alloc[i].r);
            if(find(s)==find(t)) break;
        }
        UF(i,1,m) if(alloc[i].r<=maxr) add(alloc[i].u,alloc[i].v,alloc[i].d),add(alloc[i].v,alloc[i].u,alloc[i].d);
        Dijkstra();
        for(int i=t; i; i=f[i]) ans[++temp]=i;
        DF(i,temp,2) printf("%d ",ans[i]);
        printf("%d",ans[1]);
        cout<<endl;
        printf("%.1lf %.1lf\n",dis[t],maxr);
    }
    return 0;
}


---

## 作者：Imagine (赞：0)

#### 做法$1$:最小生成树+最短路

如果同时考虑进温度和长度两个因素，似乎很麻烦。于是可以考虑消除一个因素。

只考虑温度，途经$s$到$t$的道路的最大温度尽量小很好解决，是一个最小瓶颈路问题，以温度$r$为边权求最小生成树即可，我们记$s$与$t$在树上唯一路径的所有边的温度最大值为$maxr$。

既然我们已经得到了我们要求的$s$到$t$的路径上的最大温度一定不会超过$maxr$，那么我们就可以删掉所有的温度大于$maxr$的边，它们一定不会出现在答案中。这样，问题就得到了解决，新图上的任意路径在温度上一定是满足要求的，这就消去了温度因素，只需要在新图上求一次最短路即可。

#### 做法$2$:二分+最短路

和上面的做法类似，只不过温度$maxr$是二分枚举的。对于枚举的$maxr$，只考虑所有温度值不超过$maxr$的边，用这些边求最短路即可。

---

