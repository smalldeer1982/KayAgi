# [ABC398E] Tree Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc398/tasks/abc398_e

本题是一道**交互题**（你的程序需要通过输入输出与评测系统进行交互）。

给定一棵包含 $N$ 个顶点的树 $G$，顶点编号为 $1$ 至 $N$。第 $i$ 条边连接顶点 $U_i$ 和 $V_i$。

你和高桥君将使用这棵树 $G$ 进行游戏。首先，你选择先手或后手。之后，双方轮流进行以下操作（先手先行动）：

- 选择一个满足 $1 \leq i < j \leq N$ 的整数对 $(i, j)$，并满足以下两个条件：
  - $G$ 中当前不存在连接顶点 $i$ 和顶点 $j$ 的边。
  - 在 $G$ 中添加连接顶点 $i$ 和顶点 $j$ 的边后，不会形成奇环。
- 将该边添加到 $G$ 中。

无法进行操作的一方判负，另一方获胜。请通过实际与高桥君对弈取得胜利。

**奇环的定义**：顶点序列 $(v_0, v_1, \ldots, v_k)$ 满足以下所有条件时，称为 $G$ 的一个奇环：
- $k$ 为奇数。
- $v_0 = v_k$。
- 对所有 $1 \leq i \leq k$，存在连接 $v_{i-1}$ 和 $v_i$ 的边。
### 交互方式

本题是一道交互题，你的程序需通过标准输入输出与评测系统交互。

首先，通过标准输入接收 $N$ 及 $G$ 的信息，格式如下：

> $N$  
> $U_1$ $V_1$  
> $U_2$ $V_2$  
> $\vdots$  
> $U_{N-1}$ $V_{N-1}$  

接着，你需决定选择先手或后手。若选择先手，通过标准输出输出 `First`；若选择后手，输出 `Second`。

此后游戏开始。

你的回合时，需将选择的整数对 $(i, j)$ 按顺序以空格分隔输出至标准输出：

> $i$ $j$

高桥君的回合时，将通过标准输入给出两个整数 $i$ 和 $j$：

> $i$ $j$

当 $(i, j) = (-1, -1)$ 时，表示你已获胜且游戏结束，此时需立即终止程序。  
其他情况下，$(i, j)$ 表示高桥君选择的整数对。

## 说明/提示

### 约束条件

- $2 \leq N \leq 100$
- $1 \leq U_i < V_i \leq N$
- 给定的图是树。
- 输入均为整数。

### 注意事项

- $\footnotesize\color{red}\textsf{\textbf{每次输出后，需在末尾添加换行符并刷新标准输出缓冲区。否则可能导致评测结果为 \colorbox{#f0ad4e}{\color{white}{TLE}}。}}$
- **若在交互过程中输出格式错误或程序意外终止，评测结果将不确定。**
- 游戏结束后请立即终止程序，否则评测结果不确定。

### 交互示例

|输入|输出|解释|
|:-|:-|:-|
|$\begin{matrix} \texttt{4 { }} \\ \texttt{1 2} \\ \texttt{2 3} \\ \texttt{3 4} \end{matrix}$| |首先，你收到 $N$ 和 $G$ 的边信息。|
||$\texttt{First}$|你选择先手行动。|
||$\texttt{1 4}$|你在顶点 $1$ 和 $4$ 之间添加一条边|
|$\texttt{-1 -1}$||高桥无法继续操作，你获胜。评测结果返回 $\colorbox{#5cb85c}{\footnotesize\textsf{\textbf{\color{white}{AC}}}}$。|

# 题解

## 作者：Little_x_starTYJ (赞：12)

## 解题思路
题目要求我们没有奇环，所以我们将这棵树进行二分图染色（父节点与子节点的颜色不一样且只有两种颜色）。然后我们暴力查找所有没有连过边且颜色相异的 $i, j$，将 $(i, j)$ 存下来。如果存下来的边数为奇数，那么选择先手，否则后手。

因为如果环为奇环那么首尾位颜色一定一样，比如 $0 \to 1 \to 0$，而偶环 $0 \to 1 \to 0 \to 1$ 首尾位置颜色不同，并且这个环一定是树上的一条路径再加上一条我们自己连的边，所以显然。

至于先手后手应该不难理解吧，例如有 $3$ 条边，如果你后手，那么高桥选 $1$ 条，你又选 $1$ 条，最后高桥选 $1$ 条，到你的时候发现不管怎么选都会构成奇环，所以只能先手，证明偶数后手同理。

接下来我们就只需要标记所有出现过的 $(i, j)$，再找到没有标记过的 $(x, y)$ 输出即可。

CODE：
```cpp
//ChatGPT 添加的注释
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> v[N];
vector<pair<int, int >> v2;
map<pair<int, int>, bool > m;
bool color[N];  // 用于标记每个节点的颜色（0 或 1）
inline void dfs(int x, int fa) {
	color[x] = color[fa] ^ 1;  // 当前节点的颜色与父节点颜色不同
	for (auto u : v[x]) {
		if (u ^ fa) {
			dfs(u, x);
		}
	}
}
int main() {
//	ios::sync_with_stdio(false);
//	ios_base::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, V;
		cin >> u >> V;
		if (u > V) swap(u, V);  // 统一标记规则
		m[ {u, V}] = 1; // 标记边 (u, v) 存在
		v[u].push_back(V);
		v[V].push_back(u);
	}
	// 二分图染色
	dfs(1, 0);
	// 找到所有颜色不同且没有直接连接的合法边
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (color[i] ^ color[j] && !m[ {i, j}]) {
				v2.push_back({i, j});  // 存储合法边
			}
		}
	}
	// 判断谁先手
	if (v2.size() % 2 == 0) {  // 如果合法边数是偶数，后手
		cout << "Second\n";
	} else {
		cout << "First\n" << v2[0].first << ' ' << v2[0].second << "\n";
		m[ {v2[0].first, v2[0].second}] = 1; // 标记已选择的边
	}
	int id2 = 0;
	while (1) {
		int u, v;
		cin >> u >> v;  // 读取高桥的选择
		if (u == -1 && v == -1) {
			return 0;  // 高桥选择退出，游戏结束
		}
		m[ {min(u, v), max(u, v)}] = 1; // 标记已选择的边
		// 跳过已选择的边，找到下一条合法边
		while (m[ {v2[id2].first, v2[id2].second}]) {
			id2++;
		}
		// 输出我的选择
		cout << v2[id2].first << ' ' << v2[id2].second << "\n";
		id2++;
	}
	return 0;
}
```

---

## 作者：xxgirlxx (赞：7)

## 题外话

这场 rating 结算的时候显示我正好 rk800，难绷。

这场打完差五分上青，难绷。

警示后人：链得是偶数个点，奇数条边没错，但是要去掉两个点的情况，因为这样连出来的边就是原来有的了（~~虽然我没错，是旁边的大神 [lao_wang](https://www.luogu.com.cn/user/701408) 因为这个被卡了，doge~~）。

## 题目大意

给出一个树，你决定你的先后手，然后你和交互库轮流加边，加的边要满足两个要求：一个是之前没有这条边，另一个是加了这条边后树上不能出现奇数环。

## 题目思路

结论题。

不能出现奇数环就是只能出现偶数环，注意到是在树上进行操作，因此如果有环之间出现交集也不会有影响。而要出现偶数环之前的链就得是偶数个点，奇数条边。统计一下满足这种情况的点对的数量，因为 $N \le 100$，所以可以暴力统计并标记，最后如果奇数就先手，偶数就后手。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
int deep[500010],fa[30][500010],n,q,s,u,v,num,f;
vector<int>edge[500010];
map<pair<int,int>,int>m;
void dfs(int x,int f){
	deep[x]=deep[f]+1,fa[0][x]=f;
	for(int i=0;i<edge[x].size();i++)if(edge[x][i]!=f)dfs(edge[x][i],x);
}
int lca(int x,int y){
	if(deep[x]<deep[y])swap(x,y);
	for(int i=20;i>=0&&deep[x]!=deep[y];i--)if(deep[fa[i][x]]>=deep[y])x=fa[i][x];
	for(int i=20;i>=0&&x!=y;i--)if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	if(x==y)return x;
	return fa[0][x];
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)cin>>u>>v,edge[u].push_back(v),edge[v].push_back(u); 
	dfs(1,0);
	for(int i=1;i<=20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int tmp=lca(i,j);
			if(deep[i]-deep[tmp]+deep[j]-deep[tmp]+1!=2&&(deep[i]-deep[tmp]+deep[j]-deep[tmp]+1)%2==0){
				m[mp(i,j)]=1;
				m[mp(j,i)]=1;
				num++;
			}
		}
	}
	if(num%2==0)cout<<"Second\n";
	else{
		cout<<"First\n";
		f=0;
		for(u=1;u<=n;u++){
			for(v=u+1;v<=n;v++){
				if(m[mp(u,v)]==1){
					m[mp(u,v)]=0;
					m[mp(v,u)]=0;
					cout<<u<<" "<<v<<"\n";
					f=1;
					break;
				}
			}
			if(f==1)break;
		}
	}
	for(int i=1;i<=num/2;i++){
		cin>>u>>v;
		m[mp(u,v)]=0;
		m[mp(v,u)]=0;
		f=0;
		for(u=1;u<=n;u++){
			for(v=1;v<=n;v++){
				if(m[mp(u,v)]==1){
					m[mp(u,v)]=0;
					m[mp(v,u)]=0;
					cout<<u<<" "<<v<<"\n";
					f=1;
					break;
				}
			}
			if(f==1)break;
		}
	}
	cin>>u>>v;
	return 0;
}
```

---

## 作者：zyn0309 (赞：4)

# [ABC398E] Tree Game
[题目传送门](https://atcoder.jp/contests/abc398/tasks/abc398_e)
## 思路

从任意一个点 dfs，给树上的点染黑色和白色，将相邻的点染上不同的颜色。可以发现所有颜色不同且不相邻的点之间都可以连一条边，且可以用任意顺序连边。因为颜色不同的点之间的路径长度一定是奇数，再加一条边形成的环长度一定为偶数。设黑点数量为 $x$，白点数量为 $y$，则可以连边的数量为 $xy-N+1$，当可以连边的数量为奇数的时候先手必胜，否则后手必胜。将所有可以连的边存到一个 set 里，把被选的边删掉，每次随便选一条边输出即可。

## Code

```cpp
#include<bits/stdc++.h>
#define pii  pair<int,int> 
#define pb push_back
#define mk make_pair
using namespace std;
const int N=105;
int n,fa[N];
vector<int>e[N],v1,v2;
set<pii>s;
inline void dfs(int u,int color){
	color^=1;
	if(color)v1.pb(u);
	else v2.pb(u);
	for(auto v:e[u]){
	  if(v==fa[u])continue;
	  fa[v]=u;
	  dfs(v,color);
	}
}
signed main(){
	cin>>n;
	int u,v;
	for(int i=1;i<n;++i){
	  cin>>u>>v;
	  e[u].pb(v);
	  e[v].pb(u);
	}
	dfs(1,1);
	for(auto x1:v1){
	  for(auto x2:v2)
	  	s.insert(mk(min(x1,x2),max(x1,x2)));
	}
	for(int i=1;i<=n;++i)
	  if(fa[i])
	    s.erase(mk(min(i,fa[i]),max(i,fa[i])));
	int x1,x2;
	if(((int)(v1.size()*v2.size())-n+1)&1)cout<<"First\n"<<flush;
	else{
	  cout<<"Second\n"<<flush;
	  cin>>x1>>x2;
	  if(x1==-1&&x2==-1)return 0;
	  s.erase(mk(min(x1,x2),max(x1,x2)));
	}
	while(1){
	  pii p=*s.begin();
	  cout<<p.first<<" "<<p.second<<"\n"<<flush;
	  s.erase(p);
	  cin>>x1>>x2;
	  if(x1==-1&&x2==-1)break;
	  s.erase(mk(min(x1,x2),max(x1,x2)));
	}
	return 0;
}
```

---

## 作者：dyc2022 (赞：3)

容易发现，题目的要求其实就是在连完边后保持原图为二分图。

考虑二分图的判定，将原图黑白染色。则添加的边一定要在黑点和白点之间。那么这个边数一定是确定的。所以就判定边数的奇偶性，然后选对方和自己都没有选过的边就可以了。

代码实现比较繁琐。abc e 题放交互？实在是太前卫了。

[code](https://atcoder.jp/contests/abc398/submissions/64074564)

---

## 作者：Clover_Lin (赞：3)

[请点击这里查看原题面。](https://atcoder.jp/contests/abc398/tasks/abc398_e)
## 思路
交互题，难度不大，主要是数据范围太小。容易得到连边顺序不影响结果，直接找出所有可以连边二元组，考虑个数奇偶性决定是否先连边。每一次把高桥的边的二元组删去，随便选一个输出即可。
## 代码
[赛时已 AC，如有问题请联系作者。](https://atcoder.jp/contests/abc398/submissions/64084517)

---

## 作者：Dream_poetry (赞：3)

### 思路：

看到奇环，我们考虑二分图染色。

显然对于原图是一棵树，必然也是一个二分图。

染完色后，终极目标显然是要左边和右边的点，两两之间都要连边，共计 $cnta \times cntb$ 条边，再删去原有的 $n-1$ 条边，我们就找到了剩余可操作次数。

根据这个剩余可操作次数的奇偶性，我们来判断先手或者后手。

由于 $n\le 100$，对于每次交互，暴力来查找一组可行解即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int nex,to;
}e[1000005];
int tot;
int he[1000005];
inline void add(int x,int y){
	e[++tot].nex=he[x];
	e[tot].to=y;
	he[x]=tot;
}
int col[1000005];
int cnta;
int cntb;

inline void dfs(int x,int fa){
	for (int i=he[x];i;i=e[i].nex){
		int v=e[i].to;
		if (v==fa){
			continue;
		}
		col[v]=col[x]^1;
		dfs(v,x);
	}
}
map<pair<int,int>,int>mp;

int A[1000005];
int B[100005];

inline void solve(){
	int x,y;
	cin>>x>>y;
	if (x==-1 && y==-1){
		return;
	}
	mp[make_pair(min(x,y),max(x,y))]=1;
	for (int i=1;i<=cnta;i++){
		int p=0;
		for (int j=1;j<=cntb;j++){
			if (mp[make_pair(min(A[i],B[j]),max(A[i],B[j]))]==0){
				cout<<min(A[i],B[j])<<' '<<max(A[i],B[j])<<endl;
				mp[make_pair(min(A[i],B[j]),max(A[i],B[j]))]=1;
				p=1;
				break;
			}
		}
		if (p){
			break;
		}
	}
}

signed main(){
	cin>>n;
	for (int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
		mp[make_pair(min(x,y),max(x,y))]=1;
	}
	col[1]=0;
	dfs(1,0);
	for (int i=1;i<=n;i++){
		if (col[i]){
			A[++cnta]=i;
		}
		else{
			B[++cntb]=i;
		}
	}
	int k=cnta*cntb-(n-1);
	if (k%2){
		k--;
		cout<<"First";
		cout<<endl;
		for (int i=1;i<=cnta;i++){
			int p=0;
			for (int j=1;j<=cntb;j++){
				if (mp[make_pair(min(A[i],B[j]),max(A[i],B[j]))]==0){
					cout<<min(A[i],B[j])<<' '<<max(A[i],B[j])<<endl;
					mp[make_pair(min(A[i],B[j]),max(A[i],B[j]))]=1;
					p=1;
					break;
				}
			}
			if (p){
				break;
			}
		}
	}
	else{
		cout<<"Second";
		cout<<endl;
	}
	
	while (k>0){
		solve();
		k-=2;	
	}
	
	return 0;
}
```

---

## 作者：Statax (赞：2)

## 前言

F 放学回来发现没位了，于是只能写 E 的了。

赛时看 E 是交互题就没写，于是这道题成了我除模板外第一道交互题。

## 思路

主播不会二分图，于是写了躺尸 LCA…

我们假设在原树中只添加一条边且不会形成奇环的边集为 $E$，记 $E$ 中第 $x$ 条边为 $E_x$。

那么 $E$ 中所有的边一定互不影响，即这些边就算全加进树中，依然不会有奇环。

为什么？

假设有边 $E_x, E_y$，我们分两种情况讨论：

- $E_x$ 与 $E_y$ 互不包含，显然此时没有影响，如下图。
  
![](https://www.helloimg.com/i/2025/03/23/67e01ab2b6db5.png)

- $E_x$ 与 $E_y$ 彼此间包含，因为不是奇环就是偶环，也就是节点个数为偶数。根据奇偶性，偶数减偶数还是偶数，所以还是偶环，也不会影响，如下图。

![](https://www.helloimg.com/i/2025/03/23/67e019a147e38.png)

借助图应该很好理解吧…

然后代码就很好写了，判断奇环就经典 LCA 计算树上距离。

至于题中所说刷新缓冲区，我们用 `cin / cout` 会自动刷新。

## 代码

时间复杂度 $O(n ^ 2 \log n)$，轻松通过。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 1e3 + 5;
const int inf = 2147483627;
const int mod = 998244353;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename... Arp> inline void read (T &x, Arp &...arp) {
	read(x), read(arp...);
}

int n, x, y, sz, dis[MAXN], dep[MAXN], f[MAXN][8];
vector <int> g[MAXN];
set <pair <int, int>> connect;

void dfs (int u, int fa) {
    for (const auto & v : g[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + 1, f[v][0] = u;
        for (int i = 1; i < 8; ++i) f[v][i] = f[f[v][i - 1]][i - 1];
        dfs (v, u);
    }     
} 

void get (int u, int fa) {
    for (const auto & v : g[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + 1, get (v, u);
    }    
}

int lca (int x, int y) {
    if (x == y) return x;
    if (dep[x] < dep[y]) swap (x, y);
    for (int i = 7; ~i; --i) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    for (int i = 7; ~i; --i) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return x == y ? x : f[x][0];    
}

void work () {
    auto cur = *(connect.begin ());
    cout << cur.x << " " << cur.y << endl;
    connect.erase (cur);
}

signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb (v), g[v].pb (u); 
    }
    
    dep[1] = 1, dfs (1, 1);
    dis[1] = 0, get (1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int Lenth = dis[i] + dis[j] - dis[lca (i, j)] * 2 + 1;
            if (Lenth > 2 && !(Lenth & 1)) 
                connect.insert ({i, j});
        }
    }
    
    if (int (connect.size ()) == 0) 
        return cout << "Second" << endl, 0;
    int okk = int (connect.size ()) & 1;
    cout << (okk ? "First" : "Second") << endl;
    if (okk) work ();
    cin >> x >> y;
    while (true) {
        if (x == -1 && y == -1)
            break;
        if (x > y) swap (x, y);
        connect.erase ({x, y}), work (); 
        cin >> x >> y;
    }
	return 0;
}

```

---

## 作者：small_lemon_qwq (赞：2)

一个显然的结论：只要两个节点深度奇偶性不同，就可以加一条边。

然后就有手就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,dep[105];
vector<int>g[105];
void dfs(int u,int fa){
	for(int v:g[u]){
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
set<pair<int,int>>st;
signed main(){
	cin>>n;
	cout<<flush;
	for(int i=2;i<=n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,-1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((dep[i]+dep[j])&1){
				st.insert({i,j});
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int v:g[i]){
			if(i<v)st.erase({i,v});
		}
	}
	if(st.size()%2==1){
		cout<<"First\n";
		cout<<st.begin()->first<<" "<<st.begin()->second<<endl;
		st.erase(st.begin());
	}else{
		cout<<"Second\n";
	}
	int x,y;
	while(cin>>x>>y&&x!=y){
		st.erase({x,y});
		cout<<st.begin()->first<<" "<<st.begin()->second<<endl;
		st.erase(st.begin());
	}
	return 0;
}
```

---

## 作者：leo120306 (赞：2)

题意：给你一棵树，轮流加边，要求不重边不自环，并且加边后图中不能存在奇环，问你先手还是后手并进行 IO 交互。

首先没有奇环，很明显是二分图的特征。然后在连通的二分图中，两个点集间任意加边，得到的图还是没有奇环的二分图，且两个点集不变；一个点集内部加边，一定会得到奇环。所以把两个点集之间的边都加完了之后，对方就输了。

因此我们可以这样做：将树进行黑白染色（黑点和白点分别为二分图的两个点集），寻找所有没有连边的异色点对，如果这种点对数量为奇数就先手，否则后手。最后交互怎么实现都可以，我用 `set`，时间复杂度 $O(n^2 \log n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
#define i128 __int128
#define Mod 1000000007
#define IINF INT_MAX
#define LINF LLONG_MAX
#define xINF 0x3f3f3f3f
#define N 1005
#define next nxt

vector<int>g[N];
int c[N];

int cnt,gg[N][N];
set<pii>s;

void dfs(int u,int fa){
	for(int j:g[u]){
		if(j!=fa){
			c[j]=c[u]^1;
			dfs(j,u);
		}
	}
}

int main(){
	int n;cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		gg[u][v]=gg[v][u]=1;
	}
	dfs(1,0);
	for(int u=1;u<=n;u++){
		for(int v=u+1;v<=n;v++){
			if(c[u]!=c[v]&&!gg[u][v]){
				s.insert({u,v});
				cnt++;
			}
		}
	}
	
	if(cnt&1)cout<<"First"<<endl;
	else cout<<"Second"<<endl;
	
	int u=-2,v=-2;
	if(!(cnt&1))cin>>u>>v;
	while(u!=-1&&v!=-1){
		if(u>0){
			if(u>v)swap(u,v);
			s.erase(s.find({u,v}));
		}
		int uu=s.begin()->first,vv=s.begin()->second;
		cout<<uu<<" "<<vv<<endl;
		s.erase(s.begin());
		cin>>u>>v;
	}
	
	return 0;
}
```

---

## 作者：include13_fAKe (赞：1)

作业题中的第一道交互题！



---

看到题面上的 **不存在奇环** 可以联想到：所有操作完毕之后整个图仍为二分图。

考虑二分图染色，然后枚举可以连的边数，若为奇数则选择先手，否则选择后手。

暴力寻找连的边就可以了。时间复杂度 $O(n^4)$ 在 AtCoder 上能过的。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=107;
int n;
int col[N];
vector<int> g[N];
int free_[N][N];
void dfs(int u){
//	cout<<u<<' '<<col[u]<<endl;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!col[v]){
			col[v]=3-col[u];
			dfs(v);
		}
	}
}
int sum=0;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		free_[u][v]=free_[v][u]=1;
		g[u].push_back(v),g[v].push_back(u);
	}
	col[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++){
		free_[i][i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(col[i]==col[j])	free_[i][j]=1;
		} 
	} 
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			sum+=(!free_[i][j]);
		}
	}
	if(sum%2==1){
		cout<<"First"<<endl;
		int flag=1;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(!free_[i][j]){
					cout<<i<<' '<<j<<endl;
					free_[i][j]=free_[j][i]=1;
					flag=0;
				}
				if(flag==0)	break;
			}
			if(flag==0)	break;
		}
	}
	else cout<<"Second"<<endl;
	while(1){
		int tx,ty;
		cin>>tx>>ty;
		if(tx==-1)	return 0;
		int flag=1;
		free_[tx][ty]=1,free_[ty][tx]=1;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(!free_[i][j]){
					cout<<i<<' '<<j<<endl;
					free_[i][j]=free_[j][i]=1;
					flag=0;
				}
				if(flag==0)	break;
			}
			if(flag==0)	break;
		}
	}
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc398_e [ABC398E] 树上游戏 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc398_e)

### 题目大意

**本题是交互题，通过提交程序和 Judger 进行互动产生答案，请注意输出后进行 `cout.flush()` 或者 `fflush(stdout)` 刷新输出，否则可能产生 `WA`、`TLE` 及不可预测后果。**

你要和高桥玩一个游戏，开局给一棵 $N$ 节点的树。接下来，你可以选择你先手还是高桥先手，然后开始回合制：

当前操作者选择两个没有直接连边的点 $u, v$，然后连接 $u, v$。注意，如果连接后图中出现奇环（长为奇数的环），则不能执行该操作。

无论选择什么 $u, v$ 都无法操作者负，你的目的是胜利。一方承认无法操作时，输出 `-1 -1`，当你看到或者输出此信息时，立刻停止程序。

$N \le 100$。

### 思路

考虑奇环和偶环的区别，当我们给图黑白染色时，即一条边连接的两个点必须分别是一黑一白的时候，有奇环不可能有染色方案，没有环或者全是偶环则有两种染色方案。

因此，预先给树上的点用一种方式染色，因为不会新增点，所以染色从此固定了。然后加边，只要注意加的边不要连接两个颜色相同的点就绝不会出现奇环。

那么轮到高桥连边时，只要输入他的边然后添加到图上即可。轮到我们连边时，遍历每个点对，选择颜色不同且尚未连边的即可。

那么接下来的问题就是如何选择先手。由于遵循以上规则，可以连接的异色点对总是有限且固定的，所以只要知道剩余可选边有多少个，若是奇数，则自己先手，反之自己后手，总能让高桥轮到无边可选。

至于如何计算先手，可以遍历，也可以利用二分图。染色黑为一组，白为一组，设黑点 `cnt1` 个，白点 `cnt0` 个，则最多 `cnt1 * cnt0` 条边。注意要减去最初有的 `N - 1` 条边，即剩余 `cnt1 * cnt0 - N + 1`。

### 实现

首先输入建图，我选择同时建立了邻接表和邻接矩阵。表用来 BFS 染色，在对弈阶段则放弃了表的维护。而矩阵一直维护着双向边。

时间复杂度 $O(N^4)$，空间复杂度 $O(N^2)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, u, v;
vector<int> e[105];
bool exi[105][105];
int col[105], cnt1 = 0, cnt0 = 0;
void fill()
{
	for (int i = 1; i <= N; i++) col[i] = -1;
	queue<int> q;
    q.push(1);
    col[1] = 0;
    while (!q.empty())
	{
        int u = q.front();
        q.pop();
        for (int i = 0; i < e[u].size(); i++)
		{
			int v = e[u][i];
            if (col[v] == -1)
			{
                q.push(v);
                col[v] = 1 - col[u];
            }
        }
    }
	for (int i = 1; i <= N; i++)
	{
		if (col[i] == 1) cnt1++;
		else cnt0++;
	}
}
pair<int, int> search()
{
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (col[i] != col[j] && !exi[i][j])
				return make_pair(i, j);
	return make_pair(-1, -1);
}
int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N - 1; i++)
	{
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
        exi[u][v] = 1;
        exi[v][u] = 1;
    }
	fill();
	int op = cnt1 * cnt0 - N + 1, first;
    if (op % 2 == 1)
    {
    	printf("First"); cout << endl; cout.flush();
    	first = 1;
	}
	else
	{
		printf("Second"); cout << endl; cout.flush();
		first = 0;
	}
	if (first)
	{
		while (1)
		{
			pair<int, int> p = search();
			printf("%d %d", p.first, p.second); cout << endl; cout.flush();
			if (p.first == -1) return 0;
			exi[p.first][p.second] = 1;
			exi[p.second][p.first] = 1;
			
			scanf("%d%d", &u, &v);
			if (u == -1) return 0;
			exi[u][v] = 1;
			exi[v][u] = 1;
		}
	}
	else
	{
		while (1)
		{
			scanf("%d%d", &u, &v);
			if (u == -1) return 0;
			exi[u][v] = 1;
			exi[v][u] = 1;
			
			pair<int, int> p = search();
			printf("%d %d", p.first, p.second); cout << endl; cout.flush();
			if (p.first == -1) return 0;
			exi[p.first][p.second] = 1;
			exi[p.second][p.first] = 1;
		}
	}
	return 0;
}
```

---

## 作者：Sanust (赞：1)

# AT_abc398_e Tree Game

题意为给定一棵树，两人游戏，可选择先后手，轮流加非重边且加边后图中不产生奇环，无法再加边的一方则判负，要求找到一种必胜策略使得你每次都赢。

看到**奇环**立刻想到**二分图**。由于树也是一个二分图（因为树没有奇环），问题便转化成能加多少条非重边使得该图仍然是一张二分图。**一条满足条件的边即为加上该边后能使新图仍然是二分图的边。**

不妨先给这棵树染黑白两色，由二分图的性质得，二分图中的每一条边都一定连接一个黑色点和一个白色点。**加边其实就是在图上找两个颜色相异的且还未连过直达边的点并加一条直达边。**

由于初始的树是给定且不变的，则它所**能增加的满足条件的边的数量 $sum$ 是固定的**。也就是说，按任意顺序添加这些边都不会影响剩余的满足条件的边能否被添加。所以我们可以记录下来哪些边可以被加。

如何记录？染色完枚举点对，未连过直达边且颜色不一样的点都可以连一条新的直达边，扔进容器里即可。

如何判断先后手？获胜条件是你加完了最后一条可加的边，所以当 $sum$ 是偶数时你选择后手，反之选择先手。

剩余的事情便是你从容器中选择一条边输出并从容器中删去，输入对手选择的边并把这条边删去，然后你再从容器中选择一条边并输出，如此往复直到对面认输。

注意交互题要刷新缓冲区，一般使用 `endl` 换行时就可以自动刷新缓冲区，不要关流同步。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, x, y;
bool vis[N], col[N], mp[N][N];
vector<int> v[N];
set<pair<int, int>> ans;
bool dfs(int u, bool c) // 染色，对于初始树必定能找到一种合法的染色方式
{
    vis[u] = 1, col[u] = c;
    for (auto i : v[u])
    {
        if (vis[i])
        {
            if (col[i] == c)
                return false;
        }
        else if (!dfs(i, c ^ 1))
            return false;
    }
    return true;
}
int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        v[x].push_back(y), v[y].push_back(x), mp[x][y] = mp[y][x] = 1;
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!mp[i][j] && !mp[j][i] && col[i] != col[j]) // 在图上找到两个颜色相异的且还未连过直达边的点，把边加入答案数组中
                ans.insert({ i, j });
    if (int(ans.size()) & 1)
    {
        cout << "First" << endl
             << (ans.begin()->first) << " " << (ans.begin()->second) << endl;
        ans.erase(ans.begin());
    }
    else
        cout << "Second" << endl;
    while (!ans.empty())
    {
        cin >> x >> y;
        ans.erase({ x, y }), ans.erase({ y, x }); // 正反都删，因为输入的可能和 set 里面的顺序不一样，要删的元素不存在也无所谓
        cout << (ans.begin()->first) << " " << (ans.begin()->second) << endl;
        ans.erase(ans.begin());
    }
    return 0;
}
```

---

## 作者：biyi_mouse (赞：1)

~~为什么输出边的时候编号小的要在前啊！~~

没有奇环可以转化为在加边的过程中保证图是二分图。而最初给出的树一定是二分图，所以我们不妨最这棵树二分图染色，确定出二分图的左部点和右部点，统计一下还可以添加的边数 $S$。如果 $S$ 是奇数就先手，否则后手。然后不断地取还能加的边即可。

$N \leq 100$，所以我代码乱搞也能过。

```cpp
const int N = 200010, M = 1000010;
int n, m;
int h[N], e[M], ne[M], idx;
int c[N];
bool vis[N];
map<PII, bool> H, st;
vector<int> g1, g2;
vector<PII> Edges;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool dfs(int u, int col) {
    c[u] = col, vis[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!vis[v]) {
            if (!dfs(v, 3 - col)) return false; 
        } else if (c[v] != 3 - col) return false;
    }
    return true;
}

int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    rep(i, 1, n - 1) {
        int x, y;
        cin >> x >> y;
        add(x, y); add(y, x);
        H[{x, y}] = H[{y, x}] = true;   
    }
    rep(i, 1, n)
        if (!vis[i]) dfs(i, 1); 
    rep(i, 1, n) 
        if (c[i] == 1) g1.push_back(i);
        else g2.push_back(i);
    for (auto u : g1) for (auto v : g2)
        if (!H.count({u, v})) {
            Edges.push_back({min(u, v), max(u, v)});
            st[{u, v}] = st[{v, u}] = true;
        }
    if (Edges.size() & 1) cout << "First" << endl;
    else cout << "Second" << endl;
    if (Edges.size() & 1) {
        cout << Edges.back().first << ' ' << Edges.back().second << endl;
        st[Edges.back()] = st[{Edges.back().second, Edges.back().first}] = false;
    }
    int x, y;
    while (cin >> x >> y) {
        if (x == -1 && y == -1) return 0;
        st[{x, y}] = st[{y, x}] = false;
        for (auto &[u, v] : Edges) 
            if (st[{u, v}]) {
                cout << u << ' ' << v << endl;
                st[{u, v}] = st[{v, u}] = false;
                break;
            }
    }
    return 0;
}
```

---

## 作者：_sin_ (赞：1)

观察到题目要求你在一棵树上面加边，要求不出现奇环。容易联想到二分图，而树必然是一个二分图。

每一次加边操作相当于把二分图两边的点连起来，能加的边是有限的。设二分图左部点数为 $L$，右部点数为 $R$，能额外加的边有 $L\times R-(n-1)$ 条。

由于你可以决定先手还是后手，而且额外加边的数量是有限的，所以我们看额外的边数量的奇偶性。如果能加的边数量为奇数，你就要选择先手，否则你要选择后手。确定加那条边直接暴力枚举即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll read(){
    ll x=0,f=1;char ch=getchar_unlocked();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar_unlocked();}
    while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar_unlocked();}
    return f*x;
}

const int N = 105;
int n,ok[N][N],sum=0,de[N],sb[2];
vector<int>edge[N],vec[2];
pair<int,int>tmp;

void dfs(int x,int fa){
    sb[(de[x]=de[fa]+1)&1]++;vec[de[x]&1].emplace_back(x);
    for(int y:edge[x])if(y^fa)dfs(y,x);
}

pair<int,int> find_edge(){
    for(int x:vec[0])for(int y:vec[1]){
        if(!ok[x][y])return make_pair(x,y);
    }return make_pair(-1,-1);
}

int main(){sb[0]=sb[1]=0;
    cin>>n;for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        edge[x].emplace_back(y);
        edge[y].emplace_back(x);
        ok[x][y]=ok[y][x]=1;
    }dfs(1,0);sum=sb[0]*sb[1]-(n-1);
    // printf("%d",sum);
    if(sum&1){
        cout<<"First"<<endl;
        int x,y;do{
            tmp=find_edge();
            x=tmp.first,y=tmp.second;
            if(x>y)swap(x,y);
            cout<<x<<" "<<y<<endl;
            ok[x][y]=ok[y][x]=1;
            cin>>x>>y;if(x>0&&y>0)ok[x][y]=ok[y][x]=1;
        }while(x!=-1&&y!=-1);
    }else{
        cout<<"Second"<<endl;int x,y;do{
            cin>>x>>y;if(x>0&&y>0)ok[x][y]=ok[y][x]=1;else break;
            tmp=find_edge();
            x=tmp.first,y=tmp.second;
            if(x>y)swap(x,y);
            cout<<x<<" "<<y<<endl;
            ok[x][y]=ok[y][x]=1;
        }while(x!=-1&&y!=-1);
    }
    return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：1)

# AT_abc398_e [ABC398E] Tree Game 题解

-------------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_e)。

感觉有点诈骗啊。

------------------

## 题意

你要和一个机器玩游戏。

给你一棵树要求不断加边，但是不能存在奇环，不能操作的输。

要求你要赢。你可以选择先后手。

---------------

## 思路

注意到我加一条边变成偶环后，并不影响其他的能形成偶环的边加入。

所以把加进去能形成偶环的两个点放进 `set<pair<int,int> >` 中。

具体的，以一个点为根，所有深度为偶数的点都应该与这个点放进 `set`（深度为 $2$ 除外，根节点深度为 $1$）。

然后 `set` 长度是奇数你就选先手，否则就后手。

然后你选择的时候你就随便从 `set` 中拿一个出来。

机器选择的时候你就从 `set` 中删掉就好了。

时间复杂度 $O(n^2\log n)$。

---------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
const int N=110;
vector<int>e[N];
set<pair<int,int> >s;
void dfs(int u,int fa,int dep,int root)
{
    if(dep%2==0&&dep!=2&&root<u)s.insert({root,u});
    for(int v:e[u])if(v!=fa)dfs(v,u,dep+1,root);
}
void output()
{
    auto x=s.begin();
    cout<<(*x).first<<" "<<(*x).second<<endl;
    s.erase(s.begin());
}
void input()
{
    int u,v;cin>>u>>v;
    if(u==-1&&v==-1)exit(0);
    if(u>v)swap(u,v);
    s.erase(s.find({u,v}));
}
int main()
{
    int n;cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v),e[v].push_back(u);
    }
    for(int i=1;i<=n;i++)dfs(i,0,1,i);
    if(s.size()&1)cout<<"First"<<endl,output();
    else cout<<"Second"<<endl;
    while(1)input(),output();
    return 0;
}
```

----------------

若有误或不清，欢迎评论或私信。

---

## 作者：WuMin4 (赞：1)

## [[ABC398E] Tree Game](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc398_e)

## 思路

每次行动之后图上不能存在奇环，换而言之每次行动后应满足图是一个[二分图](https://oi-wiki.org/graph/bi-graph/)，因为二分图不存在奇环。

因此我们将原树进行黑白染色，那么它就会形成一个二分图，每次操作从黑点向白点连边。可以发现当不能操作时该图为满二分图，设黑白节点数量分别为 $B,W$，原树边数量为 $m$，则满二分图边的数量为 $B\times W$，所以游戏最多操作次数为 $BW-m$，根据操作次数的奇偶性我们便可以得出开始的先后顺序。对于每次操作可以预处理出未操作的边，操作时从中选择一条边即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot;
vector<int> t[105],c[2];
vector<pair<int,int>> can;
map<pair<int,int>,bool> vis;
void dfs(int x,int fa,int cc){
	c[cc].push_back(x);
	for(int v:t[x])
		if(v!=fa)
			dfs(v,x,cc^1);
}
signed main() {
	cin>>n;
	for(int x,y,i=1;i<n;i++){
		cin>>x>>y;
		vis[{x,y}]=vis[{y,x}]=true;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	dfs(1,0,0);
	for(int v1:c[0])
		for(int v2:c[1])
			can.push_back({v1,v2});
	if((c[0].size()*c[1].size()-n)%2==0){
		cout<<"First"<<endl;
		for(int x,y,i=0;i<can.size();i++){
			if(!vis[can[i]]){
				vis[{can[i].first,can[i].second}]=vis[{can[i].second,can[i].first}]=true;
				if(can[i].first>can[i].second) swap(can[i].first,can[i].second);
				cout<<can[i].first<<" "<<can[i].second<<endl;
				cin>>x>>y;
				if(x==-1&&y==-1) return 0;
				vis[{x,y}]=vis[{y,x}]=true;
			}
		}
	}
	else{
		cout<<"Second"<<endl;
		int x,y;
		cin>>x>>y;
		vis[{x,y}]=vis[{y,x}]=true;
		for(int i=0;i<can.size();i++){
			if(!vis[can[i]]){
				vis[{can[i].first,can[i].second}]=vis[{can[i].second,can[i].first}]=true;
				if(can[i].first>can[i].second) swap(can[i].first,can[i].second);
				cout<<can[i].first<<" "<<can[i].second<<endl;
				cin>>x>>y;
				if(x==-1&&y==-1) return 0;
				vis[{x,y}]=vis[{y,x}]=true;
			}
		}
	}
	return 0; 
}
```

---

## 作者：无名之雾 (赞：0)

没想到手速场靠手速上黄了，写篇题解纪念一下。

## solution

题目要求你加边之后不能产生奇环，自然地想到二分图。

初始图是棵树，是二分图。我们把图二分图染色后，因为二分图无奇环，所以允许增加的边必须连接两边不同颜色的顶点。

我们设二分集的大小为 $a+b$，可能的跨边数量为 $a\times b$，初始图共 $n-1$ 条边，所以游戏中可行的操作数为 $k=a\times b-n+1$。

于是转换为拿走 $k$ 个棋子。若 $k$ 为奇数，则先手必胜；若 $k$ 为偶数，则后手必胜。

所以我们在合法边集里轮流取就行了。

[submission](https://atcoder.jp/contests/abc398/submissions/64067998)，~~模仿的 AI 码风大家觉得像不像~~。

---

## 作者：ANDER_ (赞：0)

简单博弈。

首先，树是二分图，可对节点进行二色染色，确保相邻节点颜色不同。设 $\tt 0$ 的节点数为 $A$，颜色 $\tt 1$ 的节点数为 $B$。所有合法边的数量为 $A \times B - N + 1$ 条边，记为 $k$。有：

- 若 $k$ 为奇数，先手胜。
- 若 $k$ 为偶数，后手胜。

数据量小，直接模拟就可以了，时间复杂度似乎是 $\Theta(N^2)$，[赛时代码](https://atcoder.jp/contests/abc398/submissions/64073015)。

---

## 作者：ran_qwq (赞：0)

比较简单的一道交互题（

一个显然的观察：把树黑白相间染色，只有原来无边的异色点能连边，因为同色点之间距离为偶数，加上这条边成奇环。

加了这条边还是能保证原来的染色中所有边连接的都是异色的两个点。按照原来的染色方式，加了一条边后，除了刚加的边，其他异色点对都是能够连边的，所以异色点对之间不会互相影响。

贪心地，能加多少加多少，直到没办法连新边为止。设异色点对为 $c$ 个，则一共能加 $c$ 条边。

如果 $c$ 是奇数则选择先手，否则选择后手，加边就随便加一条没被加过的即可。

注意加边需要保证 $i<j$。

```cpp
int n,id,hd[N],mp[N][N]; vi v[2]; set<pii> st;
struct EDGE {int to,ne;} e[N*2];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id;}
void dfs(int u,int fa,int c) {
	v[c].pb(u);
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa) dfs(v,u,c^1);
}
void QwQ() {
	n=rd();
	for(int i=1,u,v;i<n;i++) u=rd(),v=rd(),mp[u][v]=mp[v][u]=1,add(u,v),add(v,u);
	dfs(1,0,1);
	for(int x:v[0]) for(int y:v[1]) if(!mp[x][y]) st.insert({min(x,y),max(x,y)});
	if(st.size()&1) {
		auto [x,y]=*st.begin();
		st.erase({x,y}),cout<<"First"<<endl<<x<<" "<<y<<endl;
	} else cout<<"Second"<<endl;
	while(1) {
		int p=rd(),q=rd();
		if(!~p&&!~q) exit(0);
		st.erase({p,q});
		auto [x,y]=*st.begin();
		st.erase({x,y}),cout<<x<<" "<<y<<endl;
	}
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你一颗树，你要和法官博弈，你要确定你是先手还是后手，每次选择 $i,j$ 使得 $i,j$ 之间没有边，且连 $i,j$ 后图上无奇环。
## Solution
考虑连边后点不会发生变化，所以可以连边的 $i,j$ 的总数是确定的。

那么直接枚举 $i,j$ 然后算这条路径上有多少点即可。具体可以用差分加 lca 实现。

根据合法的点对的奇偶性来决定先手后手，然后用个 set 存一下符合要求的点对即可。

由于是交互题，所以不要关闭同步流，也不要用 `\n` 而用的是 `endl`。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10, inf = 0x3f3f3f3f;

int n, dep[N], f[N][10];
vector<int> e[N];
map<pair<int, int>, bool> mp;

void dfs(int u, int fa)
{
    dep[u] = dep[f[u][0] = fa] + 1;
    for (auto v : e[u]) if (v != fa) dfs(v, u);
}

int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 9; i >= 0; i--) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = 9; i >= 0; i--) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
        mp[{u, v}] = mp[{v, u}] = 1;
    }
    dfs(1, 0);
    for (int j = 1; j <= 9; j++) for (int i = 1; i <= n; i++) f[i][j] = f[f[i][j - 1]][j - 1];
    set<pair<int, int>> q;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++)
    {
        if (i == j || mp[{i, j}]) continue;
        int u = lca(i, j);
        int dis = dep[i] + dep[j] - dep[u] - dep[f[u][0]];
        if (dis % 2 == 0) q.insert({i, j}), mp[{i, j}] = mp[{j, i}] = 1;
    }
    if (q.size() & 1)
    {
        cout << "First" << endl;
        while (1)
        {
            auto u = *q.begin();
            cout << u.first << " " << u.second << endl;
            q.erase(q.begin());
            int x, y; cin >> x >> y;
            if (x == -1 && y == -1) break;
            auto p = q.lower_bound({x, y});
            q.erase(p);
        }
    }
    else
    {
        cout << "Second" << endl;
        while (1)
        {
            int x, y; cin >> x >> y;
            if (x == -1 && y == -1) break;
            auto p = q.lower_bound({x, y});
            q.erase(p);
            auto u = *q.begin();
            cout << u.first << " " << u.second << endl;
            q.erase(q.begin());
        }
    }
    return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

### 算法分析
我们通过观察样例猜测：一个图上增加一条边，且不形成奇环，则最短路奇偶性不变。

还有一个性质：只有最短路长度为奇数的点对才不会有奇环。

因此考虑跑一边全源最短路，然后记录下所有最短路长度 $>1$ 且为奇数的有序点对。

如果这种点对数量为奇数，则输出 `First`，否则输出 `Second`。

然后考虑对每个点对编号，用线段树维护他们，每个边如果存在于集合中则值为 $1$，否则为 $0$，我们加上一条边就是把一个点修改成 $0$。

### 正确性和复杂度

第一个结论可以用反证法证明，不过十分复杂，这里不给出证明。

第二个结论也是显然正确的，故算法正确。

时间复杂度 $O(n^3+T \log n)$，其中 $T$ 为操作个数。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=105,M=10005,inf=0x3f3f3f3f;
int dis[N][N],G[N][N],val[M];
int idx[M],idy[M];
int pos[M<<2];//维护区间最前面的1
void pushup(int p)
{
	if(pos[p<<1]!=-1)pos[p]=pos[p<<1];
	else pos[p]=pos[p<<1|1];
}
void build(int p,int pl,int pr)
{
	if(pl==pr)
	{
		if(val[pl])pos[p]=pl;
		else pos[p]=-1;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(p<<1,pl,mid);
	build(p<<1|1,mid+1,pr);
	pushup(p);
}
void update(int p,int pl,int pr,int x)//将x改为0
{
	if(pl==pr)
	{
		pos[p]=-1;
		return ;
	}
	int mid=(pl+pr)>>1;
	if(x<=mid)update(p<<1,pl,mid,x);
	else update(p<<1|1,mid+1,pr,x);
	pushup(p);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
	for(int i=1;i<n;++i)
	{
		int u,v;
		cin>>u>>v;
		G[u][v]=G[v][u]=1;
		dis[u][v]=dis[v][u]=1;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(dis[i][j]%2&&!G[i][j]&&dis[i][j]!=inf)
			{
				
				val[(i-1)*n+j]=1,++cnt;
				idx[(i-1)*n+j]=i,idy[(i-1)*n+j]=j;
			}
	build(1,1,n*n);
	if(cnt&1)
	{
		cout<<"First"<<endl;
		cout<<idx[pos[1]]<<" "<<idy[pos[1]]<<endl;
		update(1,1,n*n,pos[1]);
	}
	else cout<<"Second"<<endl;
	int u,v;
	while(cin>>u>>v&&u!=-1&&v!=-1)
	{
		if(u>v)swap(u,v);
		update(1,1,n*n,(u-1)*n+v);
		cout<<idx[pos[1]]<<" "<<idy[pos[1]]<<endl;
		update(1,1,n*n,pos[1]);
	}
}
```

---

## 作者：可爱的小棉羊 (赞：0)

Choose a pair of integers $(i,j)$ with **1≤i<j≤N** that satisfies both of the following conditions, then add an edge connecting vertices i and j to G.

猜猜我为啥有那么多发罚时？答案就是粗题字！

本来想骂人的但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/o8z234co.png)

算了不骂了。

我们可以直接数出所有长度为奇数的路径数量，只有这些的端点可以加边。

我们发现加上一条边后，原本一条长度为奇数的路径依然需要奇数次才能走到。相当于加上一条符合条件的边后，对原图没影响。

想到这里就很简单了。

用奇偶决定先后手，最后每次输出一条未被选的边，做完了。

~~居然这么烂都能 $+2$ Rated，这辈子有了。~~

---

## 作者：SunburstFan (赞：0)

## E - Tree Game

### 题目大意

给定一棵有 $N$ 个节点的树，编号为 $1$ 到 $N$。游戏玩家（你）和高桥君轮流向图中添加新的边 $(i,j)$，但只能添加不在图中已有边中出现、且不会形成奇环的边。当一位玩家无法进行有效操作时，该玩家失败。你的任务是决定先手或后手，并与高桥君交互，给出你的操作，直到获胜后结束游戏。

### 解题思路

用 BFS 为每个顶点染色，以区分出两个不交叠的颜色集合（把树看做二分图）。然后，对于颜色不同且尚未直接相连的一对节点 $(i, j)$，收集到集合 $m$。若集合大小为奇数则先手，否则后手。随后在游戏循环中，两方轮流从 $m$ 中移除可行的一对节点并输出；对手的操作则从输入中读取并从 $m$ 中移除。

**代码**：

```cpp
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int n;
    cin>>n;
    vector<vector<int>>g(n+1);
    vector<vector<bool>>e(n+1,vector<bool>(n+1,0));
    
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        e[u][v]=e[v][u]=1;
    }

    vector<int>c(n+1,-1);
    queue<int>q;
    c[1]=0;
    q.push(1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:g[u]){
            if(c[v]==-1){
                c[v]=c[u]^1;
                q.push(v);
            }
        }
    }

    set<pair<int,int>>m;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(c[i]!=c[j]&&!e[i][j]){
                m.insert({i,j});
            }
        }
    }
    
    bool f=(m.size()%2==1);
    if(f){
        cout<<"First\n";
        cout.flush();
    }
    else{
        cout<<"Second\n";
        cout.flush();
    }
    
    bool t=f;
    while(1){
        if(t){
            if(m.empty())break;
            auto p=*m.begin();
            m.erase(m.begin());
            cout<<p.first<<" "<<p.second<<"\n";
            cout.flush();
        }
        int u,v;
        cin>>u>>v;
        if(u==-1&&v==-1)break;
        pair<int,int>p=(u<v)?make_pair(u,v):make_pair(v,u);
        if(m.find(p)!=m.end()){
            m.erase(p);
        }
        t=1;
    }
    
    return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：0)

还好在洛谷上做过交互题。
## 思路  
可以事先从节点 $1$ 开始，用 BFS 进行二分图着色，邻相邻的节点染不同的颜色，即 $f_x = f_y \oplus 1$。  

然后将原图没有的边丢入一个 `set`（后文称为 $t$）中，便于后续使用。  

接着，选择先后手。观察到如果 $t$ 的大小为奇数的话，就可以先将多出的那一个连接上，一定是最优的，于是可以判断出：当 $t$ 的大小为奇数时选先手，否则否则选后手。  

最后模拟博弈过程。若当前轮次是 `First` 的回合，且 $t$ 中有边，选择 $t$ 中的一条边输出并移除。  
若当前轮次是 `Second` 的回合，输入一条边。如果输入的是 `-1 -1`，表示游戏结束；否则，如果输入的边在 $t$ 中，移除它。

最后的最后，交互题一定要清空缓存区！！！  
这里介绍三种清空缓存区的方法。  
- 如果你是 `printf` 选手：  
    你可以使用 `fflush(stdout)` 清空缓存区。
- 如果你是 `cout` 选手：  
    你可以使用 `cout.flush()`（仅清空缓存区）或 `cout << endl`（输出换行后清空缓存区）清空缓存区。

## AC CODE  
赛时代码。
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a / __gcd(a, b) * b
#define setp(x) fixed << setprecision(x)
using namespace std;
typedef long long ll;
typedef string str;
using ull = unsigned long long;

std::set<std::pair<int, int>> s;
std::set<std::pair<int, int>> t;

int n;
std::vector<int> e[110];
int f[110];
std::bitset<110> v;
std::queue<int> q;

signed main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	F(i, 1, n - 1, 1) {
		int x, y;
		cin >> x >> y;
		if (x > y) {//跟我们老师一样没看到题目保证x < y所以写了这个
			swap(x, y);
		}
		e[x].push_back(y);
		e[y].push_back(x);
		s.insert({x, y});
	}
	fill(f + 1, f + n + 1, -1);
	f[1] = 0;
	q.push(1);
	v[1] = 1;
	while (!q.empty())  {
		int x = q.front();
		q.pop();
		for (auto i : e[x]) {
			if (!v[i]) {
				f[i] = f[x] ^ 1;
				v[i] = 1;
				q.push(i);
			}
		}
	}
	F(i, 1, n, 1) {
		F(j, i + 1, n, 1) {
			if (f[i] != f[j]) {
				std::pair<int, int> x = {i, j};
				if (s.find(x) == s.end()) {
					t.insert(x);
				}
			}
		}
	}
	int tl = t.size();
	cout << (tl & 1 ? "First" : "Second") << el;
	std::cout.flush();
	int cnt = 0;
	while (1) {
		cnt++;
		if (cnt % 2 == tl % 2) {
			if (t.empty())  {
				cout << "-1 -1" << el;
				std::cout.flush();
				break;
			}
			auto it = t.begin();
			std::pair<int, int> x = *it;
			cout << x.fi << sp << x.se << el;
			std::cout.flush();
			t.erase(it);
		} else {
			int x, y;
			cin >> x >> y;
			if (x == y && y == -1) {
				break;
			}
			if (x > y) {//同上
				swap(x, y);
			}
			std::pair<int, int> z = {x, y};
			if (t.count(z)) {
				t.erase(z);
			}
		}
	}
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc398/submissions/64099363)

--- 
完结~~不~~散花。

---

## 作者：cyq32ent (赞：0)

注意到添边不形成奇环，等同于添边后，图仍为二分图。因此，我们先对树染一个色，那么边是合法的，等同于两个节点的颜色不同。设黑色节点有 $X$ 个，白色有 $Y$ 个，那么可以添的边数为 $XY-N+1$（因为已有的树边不能添）。因此，根据它的奇偶确定先后手，然后每次从可添加的边中随便选一个输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>G[111];
pair<int,int>s[11111];
map<pair<int,int>,int>M,key;
#define y1 NOOoooo_more_compile_errorssssssss
int col[111],X[111],Y[111],N,u,v,x1,y1,t,r,cnt,pt;
void color(){
	memset(col,-1,sizeof col);
	queue<int>Q;
	Q.push(1);
	col[1]=0;
	while(!Q.empty()){
		auto u=Q.front();Q.pop();
		for(auto v:G[u]){
			if(!~col[v])col[v]=1-col[u],Q.push(v);
		}
	}for(int i=1;i<=N;i++){
		if(col[i])X[++x1]=i;
		else Y[++y1]=i;
	}
}
int main(){
	cin>>N;
	for(int i=1;i<N;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		M[{u,v}]=M[{v,u}]=1;
	}color();
	if((x1*y1-N)&1)cout<<"Second\n",t=0;
	else cout<<"First\n",t=1;
	cout.flush();
	r=x1*y1-N+1;
	for(int i=1;i<=x1;i++){
		for(int j=1;j<=y1;j++){
			if(!M[{X[i],Y[j]}]){
				int a=X[i],b=Y[j];
				if(a>b)swap(a,b);
				s[++cnt]={a,b},key[{a,b}]=1;
			}
		}
	}
	while(1){
		if(r==0)return 0;
		else if(t==0){
			int i,j;cin>>i>>j;
			if(!key[{i,j}])swap(i,j);
			key[{i,j}]=0;
			r--;
		}else{
			while(!key[s[pt]])pt++;
			cout<<s[pt].first<<' '<<s[pt].second<<endl;
			cout.flush();
			key[s[pt]]=0;
			r--;
		}t^=1;
	}
	return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：0)

本蒟蒻第一次写过交互题寄。

大体意思就是给定一棵树，然后你和电脑博弈，轮流每次加一条边，你可以选择先手或后手，每次加边后不能出现奇环，要求你必须是获胜。

画一下图就能发现，因为 $N\le100$。我们可以先处理出所有能加的边，然后就会发现，**在加上一条边的时候，其余能加的边不会被影响**。

可以用黑白染色来证明，既然初始是一棵树，就不妨连接的两个点一白一黑，加边就是要求两个点也是一白一黑，这样能加的边显然是固定不变的。

这样做法就来了，先统计能加的边的数量，奇数就是先手，偶数就是后手。然后把那些边一个一个输出就行了，注意是不要重边。

时间复杂度超级大常数 $O(N^2)$。

[赛时代码](https://atcoder.jp/contests/abc398/submissions/64095372)。

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1E5XWYKE3n?t=273)

[参考代码](https://atcoder.jp/contests/abc398/submissions/64070412)

---

## 作者：Tairitempest (赞：0)

## [ABC398E] Tree Game
如果把整棵树交替染色（与黑色点相连的染上白色，与白色点相连的染上黑色），可以发现同色的两个节点连起来一定形成奇环。

观察到 $N$ 很小，暴力枚举所有异色点对，然后根据数量判断先后手即可，如果奇数就是先手，否则就是后手。至于具体走法，用 set 存一下符合条件的点对，然后轮到自己走就随便找一组，对方走完就把对方走过的点对删掉就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,c[110],cnt,x,y;
vector<ll> E[110];
set< array<ll,2> > e,av;

void dfs(ll p,ll f){
	c[p]=c[f]^1;
	for(int i=0;i<E[p].size();i++){
		ll nxt=E[p][i];
		if(nxt!=f) dfs(nxt,p);
	}
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
		e.insert({u,v});
		e.insert({v,u});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(e.count({i,j})==0&&c[i]!=c[j]){
				cnt++;
				av.insert({i,j});
				av.insert({j,i});
			}
		}
	}
	if(cnt%2){
		cout<<"First"<<endl;
		x=(*av.begin())[0];
		y=(*av.begin())[1];
		cout<<x<<" "<<y<<endl;
		fflush(stdout);
		av.erase({x,y});
		av.erase({y,x});
	}
	else{
		cout<<"Second"<<endl;
		fflush(stdout);
	}
	cin>>x>>y;
	while(x!=-1||y!=-1){
		av.erase({x,y});
		av.erase({y,x});
		x=(*av.begin())[0];
		y=(*av.begin())[1];
		cout<<x<<" "<<y<<endl;
		fflush(stdout);
		av.erase({x,y});
		av.erase({y,x});
		cin>>x>>y;
	}
	return 0;
}
```

---

