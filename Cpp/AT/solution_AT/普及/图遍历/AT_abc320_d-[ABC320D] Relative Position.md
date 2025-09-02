# [ABC320D] Relative Position

## 题目描述

在一个平面直角坐标系上有 $n$ 个点，每个点有编号，它们间存在 $m$ 条关系，其中第 $i$ 条关系格式如下：

- 给定编号 $a_i,b_i$ 与整数 $x_i,y_i$，表示若第 $a_i$ 个点的坐标为 $(p_i,q_i)$，则满足第 $b_i$ 个点的坐标为 $(p_i+x_i,q_i+y_i)$。保证 $a_i\not =b_i$。

其中 $1$ 号点的坐标为 $(0,0)$。

你需要根据这些关系求出每个点的坐标，或输出 `undecidable` 以报告其中一些点的坐标无法确定。保证关系不会互相矛盾，但可能重复。

$1\le a_i,b_i\le n\le 2\times10^5$，$0\le m\le 2\times 10^5$，$-10^9\le x_i,y_i\le 10^9$。

## 样例 #1

### 输入

```
3 2
1 2 2 1
1 3 -1 -2```

### 输出

```
0 0
2 1
-1 -2```

## 样例 #2

### 输入

```
3 2
2 1 -2 -1
2 3 -3 -3```

### 输出

```
0 0
2 1
-1 -2```

## 样例 #3

### 输入

```
5 7
1 2 0 0
1 2 0 0
2 3 0 0
3 1 0 0
2 1 0 0
3 2 0 0
4 5 0 0```

### 输出

```
0 0
0 0
0 0
undecidable
undecidable```

# 题解

## 作者：zengziqvan (赞：6)

## 题意简述

给定 $n$ 个点与 $m$ 个关系，第 $i$ 个关系的格式如下：

- 给定编号 $x$，$y$ 以及 $a$ 和 $b$，设 $x$ 点在平面直角坐标系的位置为 $(x,y)$，则 $y$ 点在平面直角坐标系的位置为 $(x+a,y+b)$。

其中 $1$ 号点的坐标为 $(0,0)$，现在你需要根据这 $m$ 条关系求出这 $n$ 个点的坐标。

但是这 $m$ 条关系有时会重复，还有时求不出所有点的坐标，这时候你需要输出 `undecidable`。

## 题目分析

首先分析一点：若 $a$ 点坐标为 $(x,y)$，$b$ 点坐标为 $(x+a,y+b)$，那么 $b$ 点坐标为 $(x+a,y+b)$，$a$ 点坐标就为 $((x+a)-a,(y+b)-b)$。

因此，若有关系 $(x,y,a,b)$，那么就有关系 $(y,x,-a,-b)$。

而可以通过已知点的坐标与给定的关系推出未知点的坐标。

所以考虑建立图论模型，将两点之间的关系用双重边权存储，再进行 DFS 求出每个点的位置。

时间复杂度 $O(N+M)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const long long N=2e5+10,God=1e15+10;
int hed[N],tot,X[N],Y[N],d[N],n,m,b[N];
struct edge{
	int nxt,to,val1,val2;
}e[N*2];
void adde(int u,int v,int w,int x) {
	e[++tot].nxt=hed[u];
	e[tot].to=v;
	e[tot].val1=w;
	e[tot].val2=x;
	hed[u]=tot;
}
void dfs(int x) {
	if(b[x]) return ;
	b[x]=1;
	for(int i=hed[x];i;i=e[i].nxt) {
		int y=e[i].to;
		if(!b[y]) {
			X[y]=X[x]+e[i].val1;
			Y[y]=Y[x]+e[i].val2;
			dfs(y);
		}
	}
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;++i) {
		int u,v,w1,w2;
		cin>>u>>v>>w1>>w2;
		adde(u,v,w1,w2);
		adde(v,u,-w1,-w2);
	}
	memset(X,God,sizeof(X));
	memset(Y,God,sizeof(Y));
	X[1]=0,Y[1]=0;
	dfs(1);
	for(int i=1;i<=n;++i) {
		if(X[i]==723401728380766730) {//这个数不用管 
			puts("undecidable");
		}
		else {
			cout<<X[i]<<" "<<Y[i]<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：_Chronostatis_ (赞：2)

# Relative Position 题解
题目保证不矛盾，就可以直接 vector 建图，然后 dfs 一遍，边权为 $(w_x,w_y)$ 表示坐标的差，从 $u=1$ 开始搜索，设点 $u,v$ 有一条无向边，$v_x = u_x + w_x,v_y = u_y + w_y$，最后如果没有被标记过的话（也就是没有遍历过），那么无解。

## AC Code
```cpp
#include<iostream>
#include<vector>

using namespace std;

const int MAXN = 2e5 + 10;

struct node{
    int t, x, y;
};

struct ANS{
    long long a, b;
}ans[MAXN];

vector<node> G[MAXN];
int n, m, a, b, x, y;
bool vis[MAXN];

void dfs(int u, long long x, long long y){
    if (vis[u]){
        return;
    }
    vis[u] = 1,ans[u] = {x, y};
    for (int i = 0; i < G[u].size(); i++){
        dfs(G[u][i].t, x + G[u][i].x, y + G[u][i].y);
    }
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> a >> b >> x >> y;
        G[a].push_back({b, x, y}), G[b].push_back({a, -x, -y});
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            cout << "undecidable\n";
        }
        else {
            cout << ans[i].a << ' ' << ans[i].b << '\n';
        }
    }
    return 0;
}
```

---

## 作者：BYR_KKK (赞：2)

# 题目大意

有 $N$ 个人，第一个人位于 $(0,0)$。另外给出 $M$ 条形如 “第 $A_i$ 个人与第 $B_i$ 个人的横坐标差为 $X_i$，纵坐标差为 $Y_i$ ” 的消息，判断每个人的坐标，如无法判断则输出 ```undecidable```。

# 思路

一道比较基础的图论。

容易想到，给出两个人之间的关系就相当于两个人之间连边。而我们一开始只知道第一个人的坐标，所以必须要从与第一个人连边的人开始更新，整体就是一个 DFS 的过程。注意，搜索时要用一个数组记录该人的坐标是否已被求出。如果最后统计答案时该人的坐标仍未被求出，则输出 ```undecidable```。

其实这里求不出坐标的人就是与第一个人不在一个连通块的人。

# code

```cpp

#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int maxn=2e5+10;

struct ma{
	int e,x,y;//存储每条基本信息 
}; 

vector<ma>a[maxn];

bool vis[maxn];//记录每个人的坐标是否已经被求出 

pii s[maxn];//记录每个人的坐标 

void dfs(int p){
	for(int i=0;i<a[p].size();i++){
		int l=a[p][i].e;
		if(vis[l]) continue;//防止陷入无限递归 
		vis[l]=true;
		s[l].fi=s[p].fi+a[p][i].x;
		s[l].se=s[p].se+a[p][i].y;
		dfs(l);
	}
}

signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int c,f,g,h;
		cin>>c>>f>>g>>h;
		a[c].push_back({f,g,h})
		a[f].push_back({c,-g,-h});//两者之间的关系是双向的 
	}
	vis[1]=true;
	s[1].fi=s[1].se=0;
	dfs(1);//从第一个人开始搜索 
	for(int i=1;i<=n;i++) {
		if(vis[i]) cout<<s[i].fi<<' '<<s[i].se<<'\n';
		else {
			cout<<"undecidable\n";
		}
	}
	return 0;
}

```

---

## 作者：xxr___ (赞：2)

### 思路：
评论区好多人都用深度优先搜索，这里我发一篇广度优先搜索的题解，首先我们用邻接表存图，注意要存双向，然后从一号点开始搜，如果一个点和原点没有相邻的边，就说明它的位置有很多，是不唯一的，否则就输出其位置。
### 赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int head[maxn],num=0;
long long dx[maxn],dy[maxn];
bool vis[maxn];
struct g{
	int next;
	int to;
	int x;
	int y;
}edge[maxn*2];
void insert(int v,int u,int x,int y){
	num++;
	edge[num].next=head[u];
	edge[num].to=v;
	edge[num].x=x;
	edge[num].y=y;
	head[u]=num;
}
queue<int>q;
int main(){
	int n,m,u,v,x,y;
	cin>>n>>m;
	for(int i=0;i^m;i++){
		cin>>u>>v>>x>>y;
		insert(u,v,x,y);
		insert(v,u,-x,-y);
	}
	q.push(1);
	while(!q.empty()){
		int l=q.front();
		q.pop();
		vis[l]=1;
		for(int i=head[l];i;i=edge[i].next){
			v=edge[i].to;
			x=edge[i].x;
			y=edge[i].y;
			if(!vis[v]){
				dx[v]=dx[l]-x;
				dy[v]=dy[l]-y;
				vis[v]=1;
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			cout<<dx[i]<<" "<<dy[i]<<endl;
		}else{
			puts("undecidable");
		}
	}
	return 0;
}
```

---

## 作者：robertuu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_d)

这道题的关系可以抽象为图中的边，坐标差抽象为边长（是二维的）。

以 $1$ 号点为原点遍历图，被遍历到的点的坐标一定唯一确定，没有遍历到的点就是 `undecidable` 的点。

坑点：每条关系都要建正反两条边，边长正好相反！答案很大，可能需要开 long long 类型！

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long posx[200001],posy[200001]; // 开 long long！
bool vis[200001];
int cnt,head[200001],nxt[400001],to[400001],X[400001],Y[400001];
void add(int x,int y,int xx,int yy)
{
	to[++cnt] = y;
	X[cnt] = xx; Y[cnt] = yy;
	nxt[cnt] = head[x];
	head[x] = cnt;
}
void dfs(int x)
{
	vis[x] = 1;
	for(int i = head[x];i;i = nxt[i])
		if(!vis[to[i]])
		{
			posx[to[i]] = posx[x] + X[i];
			posy[to[i]] = posy[x] + Y[i];
			dfs(to[i]);
		}
}
int main()
{
	int n,m,x,y,xx,yy;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&xx,&yy);
		add(x,y,xx,yy);
		add(y,x,-xx,-yy); // 坑点！
	}
	dfs(1);
	for(int i = 1;i <= n;i++)
		if(vis[i]) printf("%lld %lld\n",posx[i],posy[i]);
		else printf("undecidable\n");
	return 0;
}
```


---

## 作者：kimidonatsu (赞：1)

# at_abc320_d - Relative Position 题解

我们所需要获取的坐标都可以通过 **在图上进行深度优先搜索** 的方式来获得，这里我们将人作为顶点，建立一个有向图，对于每条从 $A_i$ 到 $B_i$ 和从 $B_i$ 到 $A_i$ 的边，储存这两个顶点的相对位置，在搜索过程中沿着一条边更新坐标即可。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 5;
i64 n, m;
std::vector<bool> vis(N + 5);
std::pair<i64, i64> ans[N + 5];
std::vector<std::array<i64, 3>> g[N];

void dfs(i64 c, i64 x, i64 y) {
	ans[c] = {x, y};
	vis[c] = true;

	for (auto [u, dx, dy] : g[c]) {
		if (vis[u]) continue;
		dfs(u, x + dx, y + dy);
	}
}

void solve() {
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		i64 a, b, x, y;
		std::cin >> a >> b >> x >> y;
		g[a].push_back({b, x, y});
		g[b].push_back({a, -x, -y});
	}

	dfs(1, 0, 0);

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) std::cout << "undecidable\n";
		else std::cout << ans[i].first << " " << ans[i].second << "\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	solve();
	return 0;
}

```


---

## 作者：rainygame (赞：0)

比较简单的一道水 D。

由于题目保证了不矛盾，所以可以直接建图 bfs。边权即为数对 $(w_x,w_y)$ 表示坐标差。然后从 $1$ 开始出发搜索。假设 $u,v$ 之间有一条边，那么 $v_x=u_x+w_x$，$v_y=u_y+w_y$。

最后没有搜到的就是 `undecidable` 的。

注意一下需要建双向边。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001

int n, m, a, b, x, y;
pair<int, int> d[MAXN];
bitset<MAXN> vis;

struct Edge{
	int x, y, v;
}u;
vector<Edge> e[MAXN];
queue<Edge> que;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    while (m--){
    	cin >> a >> b >> x >> y;
    	e[a].push_back({x, y, b});
    	e[b].push_back({-x, -y, a});
	}
	
	que.push({0, 0, 1});
	d[1] = {0, 0};
	vis.set(1);
	while (!que.empty()){
		u = que.front();
		que.pop();
		
		for (auto i: e[u.v]){
			if (!vis.test(i.v)){
				vis.set(i.v);
				d[i.v] = {u.x+i.x, u.y+i.y};
				que.push({u.x+i.x, u.y+i.y, i.v});
			}
		}
	}
	
	for (int i(1); i<=n; ++i){
		if (!vis.test(i)) cout << "undecidable\n";
		else cout << d[i].first << ' ' << d[i].second << '\n';
	}

    return 0;
}

```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路

发现这个东西可以先把关系按照图来存下来，然后我们把整个图遍历一遍，然后用一个数组累计答案就好了。

具体的代码就是这样。

`ans[v] = {ans[u].first + X, ans[u].second + Y};`。

然后就没了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (l); i >= (r); i--)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000000;
vector<pair<int,pair<i64, i64>>> e[maxn];
pair<i64, i64> ans[maxn]; bool vis[maxn];
void dfs(int u, int f) {
    for (pair<int, pair<int, int>> _ : e[u]) {
        int v = _.first;
        int X = _.second.first;
        int Y = _.second.second;
        if (v != f && vis[v] == 0) {
            vis[v] = 1;
            ans[v] = {ans[u].first + X, ans[u].second + Y};
            dfs(v, u);
        }
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        e[u].push_back({v, {x, y}});
        e[v].push_back({u, {-x, -y}});
    }
    vis[1] = 1;
    dfs(1, 0);
    rep(i, 1, n) {
        if (vis[i] == 0) {
            cout << "undecidable\n";
        } else {
            cout << ans[i].first << " " << ans[i].second << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_d)

感觉是拓扑的魔改板。

## $\mathtt{Solution}$

不难想到可以拓扑排序，边做边求坐标即可。

但是如果有环的话，好像就不行了。

于是我们使用一个数组 $vis$ 记录是否已经走过，不考虑入度，如果没有就把它加入到队列里面。

时间复杂度 $O(n+m)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
const int MAXN = 2e5 + 5, MR = 4e5 + 5;
struct edge{
	int from, to, x, y, nxt;
}e[MR];
int n, m, cnt, head[MAXN], vis[MAXN];
int ansx[MAXN], ansy[MAXN];
void add_edge(int u, int v, int x, int y){
	e[++ cnt] = {u, v, x, y, head[u]};
	head[u] = cnt;
}
signed main(){
	n = read(), m = read();
	for(int i = 1;i <= m;i ++){
		int a = read(), b = read(), x = read(), y = read();
		add_edge(a, b, x, y);//双向边
		add_edge(b, a, -x, -y);//以b的视角来看，就是-x,-y
	}
	queue<int>q;q.push(1);
	vis[1] = 1;
	while(!q.empty()){
		int t = q.front();q.pop();
		for(int i = head[t];i;i = e[i].nxt){
			int v = e[i].to, x = e[i].x, y = e[i].y;
			ansx[v] = ansx[t] + x;//求解坐标
			ansy[v] = ansy[t] + y;
			if(!vis[v])q.push(v), vis[v] = 1;//加入队列
		}
	}
	for(int i = 1;i <= n;i ++){
		if(!vis[i])puts("undecidable");
		else printf("%lld %lld\n", ansx[i], ansy[i]);
	}
	return 0;
}

```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_d)

## 题目大意

平面上有 $N$ 个点，给出 $M$ 行参数。第 $i\space(1\le i\le M)$ 行有四个数 $A_i,B_i,X_i,Y_i$，代表 $B_i$ 在 $A_i$ 的向右走 $X_i$，向上走 $Y_i$ 的位置上。如果 $X_i$ 为负就是向左走，$Y_i$ 为负就是向下走。求**把第 $1$ 个点放在位置 $(0,0)$ 的时候**从 $1$ 到 $N$ 每个点的位置。如果某个点的位置不唯一就输出 ``undecidable``。

## 思路

一道很好的 dfs 题目。

可以把所有参数**双向**建图，然后从第 $1$ 号点，位置 $(0,0)$ 跑一遍 dfs，找到所有和 $1$ 号点联通的点，标记，并记录它满足 $1$ 号点在 $(0,0)$ 时的位置。如果某个点不和 $1$ 号点联通，就说明它的位置**不唯一**，无论在哪都能满足它和与其相连的点的位置关系。

**双向建图**：题目中说的是 $B_i$ 在 $A_i$ 的向右走 $X_i$，向上走 $Y_i$ 的位置上，那么我们也轻易能看出 $A_i$ 在 $B_i$ 的向**左**走 $X_i$，向**下**走 $Y_i$ 的位置上。

在跑完 dfs 后，遍历从 $1$ 到 $N$ 的每个点。如果它不和 $1$ 号点相连就输出 ``undecidable``，否则输出它的位置。

### 注意事项

- $|X_i|,|Y_i|\le 10^9$，数据范围较大，记得开 long long。

- 可能存在重边，所以在 dfs 的时候记得已经标记过的点就不要再进行搜索了，避免 TLE。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=2e5+10;
ll n,m,u,v,x,y,in[N];//记得开 long long。
bool vis[N];
struct node{
	ll x,y,v;
};vector<node>g[N];
queue<int>q;
pll pe[N];
inline void dfs(int x,int f,ll nx,ll ny){
	if(vis[x])return ;//已经访问过的点不用继续访问。
	vis[x]=1;
	pe[x].fi=nx,pe[x].se=ny;//记录位置。
	for(auto i:g[x]){
		if(i.v==f)continue;//不要搜回去。
		dfs(i.v,x,i.x+nx,i.y+ny);
	}
}
int main(){
	cin>>n>>m;
	while(m--){
		u=read(),v=read(),x=read(),y=read();
		g[u].pb({x,y,v});//双向建图。
		g[v].pb({-x,-y,u});
	}
	dfs(1,0,0,0);//从 1 号点的 (0,0) 位置开始搜索。
	for(int i=1;i<=n;++i){
		if(!vis[i])puts("undecidable");//如果没标记就说明位置不唯一。
		else printf("%lld %lld\n",pe[i].fi,pe[i].se);//有唯一位置，输出。
	}
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/124936706)

---

## 作者：linxuanrui (赞：0)

### 思路

从最基础的地方讲起。

对于题目中给的 $a,b,x,y$，假如确定了 $a$ 的位置是 $(dx,dy)$，那么 $b$ 的位置就是 $(dx + x,dy + y)$。

反之，如果确定了 $b$ 的位置是 $(dx,dy)$，那么 $a$ 的位置就是 $(dx-x,dy-y)$。

此时，我们可以建一条 $a\to b$ 的双向边，表示可以用 $a$ 的位置推出 $b$，用 $b$ 的位置推出 $a$。

因为题目说第一个人的位置是 $(0,0)$，所以可以从 $1$ 号点开始进行深搜。

### 代码

代码又难看又长，建议看别人的题解。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
typedef long long ll;
using namespace std;
struct node{int a,b,c,d;}a[200005];
int n,m,x[200005],y[200005];
vector<pair<int,int> > g[200005];
bool vis[200005],vis2[200005];
void init(int i){
	if(vis[a[i].a]){
		vis[a[i].b] = true;
		x[a[i].b] = x[a[i].a] + a[i].c,y[a[i].b] = y[a[i].a] + a[i].d;
	}else if(vis[a[i].b]){
		vis[a[i].a] = true;
		x[a[i].a] = x[a[i].b] - a[i].c,y[a[i].a] = y[a[i].b] - a[i].d;
	}
}
void dfs(int x){
	for(int i = 0;i < g[x].size();i++){
		int v = g[x][i].first,w = g[x][i].second;
		if(!vis2[w]){
			vis2[w] = true;
			init(w);
			dfs((a[w].a == x ? a[w].b : a[w].a));
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	vis[1] = true;
	for(int i = 1;i <= m;i++)cin >> a[i].a >> a[i].b >> a[i].c >> a[i].d,g[a[i].a].push_back({a[i].b,i}),g[a[i].b].push_back({a[i].a,i});
	dfs(1);
	for(int i = 1;i <= n;i++){
		if(vis[i])cout << x[i] << " " << y[i] << endl;
		else cout << "undecidable\n";
	}
}

```

---

## 作者：TempestMiku (赞：0)

# 原题

- [洛谷](https://www.luogu.com.cn/problem/AT_abc320_d)

- [Atcoder](https://atcoder.jp/contests/abc320/tasks/abc320_d)

## 题目大意：

$n$ 个点互相距离 $x$ 距离和 $y$ 距离，$1$ 号点坐标为 $(0,0)$，问每个点坐标，如果不确定就输出 ```undecidable```。

## 思路

我们可以给每个人建边跑深度优先搜索，注意建双向边的 $x,y$ 距离要变成 $-x,-y$。同时把每个人是否遍历过标记出来，如果没被标记就输出 ```undecidable```。

![](https://cdn.luogu.com.cn/upload/image_hosting/wh97duaj.png)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        // putchar(' ');
    }
}
using namespace Testify;
int n,m;
const int N=2e5+5;
int vis[N];
struct node{
    int to;
    int x,y;
    // node(int tt,int xx,int yy){
    //     to=tt,x=xx,y=yy;
    // }
}
SATELLITE[N];
vector<node> G[N];
inline void dfs(int now,int fa){
    // vis[now]++;
    for(auto op:G[now]){
        int y=op.to,X=op.x,Y=op.y;
        if(y==fa||vis[y]) continue;
        vis[y]=true;
        SATELLITE[y].x=SATELLITE[now].x+X;
        SATELLITE[y].y=SATELLITE[now].y+Y;
        dfs(y,now);
    }
}
signed main(void){
    n=read(),m=read();
    for(register int i=1;i<=m;i++){
        register int a=read(),b=read(),x=read(),y=read();
        G[a].push_back(node{b,x,y});
        G[b].push_back(node{a,-x,-y});
    }
    vis[1]=true;
    dfs(1,0);
    for(register int i=1;i<=n;i++){
        if(!vis[i]){
            puts("undecidable");
        }
        else{
            write(SATELLITE[i].x),putchar(' '),write(SATELLITE[i].y);
            puts("");
        }
    }
    return 0;
}
```


---

## 作者：白简 (赞：0)

### 题目大意
若干个人在坐标平面上。

给出若干个人之间位置的相对关系，其中第一个人在原点处，求出每个人的坐标。

如果一个人的坐标不确定，输出 `undecidable`。
### 思路
由于题目中保证了没有出现冲突的情况，那么我们得到的对应关系能够构建出一棵以 $1$ 为根的树或森林。

其中与 $1$ 直接或间接相连的是能够求出坐标的，与 $1$ 不连通的是无法求出具体坐标的。

直接建双向边从 $1$ 开始深搜，建边时候记得记录这条边是正向还是反向的。

还有记得开 `long long`，赛时挂了一发。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 200500;

int n,m;

int a[N],b[N],x[N],y[N];

int pos[N];

int posx[N],posy[N];

bool vis[N];

vector< pair<int,int> > e[N];

void dfs(int cur,int fa) {
    vis[cur] = 1;

    for(auto const &it : e[cur]) {
        int to = it.first,i = it.second;

        if(to == fa || vis[to])
            continue;

        if(i < 0) {
            posx[to] = posx[cur] - x[-i];
            posy[to] = posy[cur] - y[-i];
        }
        else {
            posx[to] = posx[cur] + x[i];
            posy[to] = posy[cur] + y[i];
        }

        // cerr << "to = " << to << endl;
        // cerr << posx[to] << " " << posy[to] << endl;

        dfs(to,cur);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1;i <= m; i++) {
        cin >> a[i] >> b[i] >> x[i] >> y[i];
        
        e[b[i]].emplace_back(a[i],-i);
        e[a[i]].emplace_back(b[i],i);
    }

    dfs(1,0);

    for(int i = 1;i <= n; i++) {
        if(!vis[i])
            cout << "undecidable" << endl;
        else
            cout << posx[i] << " " << posy[i] << endl;
    }
    return 0;
}
```

---

## 作者：Hanzelic (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/AT_abc320_d)  

首先我们知道只有 $1$ 的坐标是确定的，那么我们也只能将与 $1$ 有关的点的坐标表示出来，剩下的即为不确定点。  

那么我们可以考虑从 $1$ 开始 dfs，开一个 $vis$ 数组记录哪些点经过了，哪些点没有经过，并在 dfs 的过程中就将每个点的坐标计算出来。 那么这题就结束了。  

注意连双向边的时候要将差值加个负数，这样才不会出错。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define M 200050
using namespace std;
int n,m,a,b,c,d;
struct node{
	int pot,x,y;
};
vector<node>g[M];
pair<int,int>pot[M];
bool vis[M];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar(); }
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch-'0');ch=getchar();}
	return x*f;
}
void dfs(int x,int fat){
	vis[x]=1;
	for(auto i:g[x]){
		int y=i.pot;
		if(y==fat||vis[y])continue;
		pot[y].first=pot[x].first+i.x;
		pot[y].second=pot[x].second+i.y;
		dfs(y,x);
	}
}
signed main(){
	n=read(),m=read();
	for(int q=1;q<=m;q++){
		a=read(),b=read(),c=read(),d=read();
		g[a].push_back((node){b,c,d});
		g[b].push_back((node){a,-c,-d});
	}
	dfs(1,0);
	for(int q=1;q<=n;q++){
		if(vis[q])printf("%lld %lld\n",pot[q].first,pot[q].second);
		else printf("undecidable\n");
	}
	return 0;
}
```


---

