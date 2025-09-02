# [CCC 2024 S4] Painting Roads

## 题目描述

Kitchener 市的市长 Alanna 成功地改进了该市的道路规划。然而，来自 RedBlue 市的一位售货员仍然抱怨道路的颜色不够丰富。Alanna 的下一个任务就是粉刷一些道路。

Kitchener 市的道路规划可以表示为 $N$ 个十字路口和 $M$ 条道路，第 $i$ 条道路连接第 $u_i$ 个十字路口和第 $v_i$ 个十字路口。一开始所有道路都是灰色的。Alanna 想要把一些道路染成红色或者蓝色，满足以下条件：

- 对于每一条灰色道路，假设其连接十字路口 $u_i$ 和十字路口 $v_i$，一定存在一条从十字路口 $u_i$ 到十字路口 $v_i$ 的路径，满足路径上的道路颜色红色和蓝色交替出现，任何道路都不是灰色的。

为了降低城市的支出，Alanna 希望尽可能少地对道路进行染色。请帮助 Alanna 设计一个符合要求的染色方案。

## 说明/提示

**【样例 1 解释】**

十字路口以及有效的道路的示意图如下所示，该方案最小化了染色道路的数量。请注意，每条道路上的颜色显示为 R（红色）、B（蓝色）或 G（灰色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vwughkb3.png)

所有为染色的道路都满足条件：

- 第二条路标记为 $G_2$ 连接了十字路口 $2$ 和 $4$，路径 $2, 1, 4$ 上的道路被染上红色、蓝色。
- 第三条路标记为 $G_3$ 连接了十字路口 $5$ 和 $2$，路径 $5, 4, 1, 2$ 上的道路被染上红色、蓝色、红色。
- 第五条路标记为 $G_5$ 连接了十字路口 $4$ 和 $3$，路径 $4, 1, 3$ 上的道路被染上蓝色、红色。

**【样例 2 解释】**

请注意 Kitchener 的道路可能不是连通的。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\leq N, M \leq 2 \times 10^5$，$1 \leq u_i, v_i \leq N$，$u_i \neq v_i$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 附加条件 |
| :-: | :- |
| $2$ | 对任意 $1 \leq i < N$ 存在一条连接 $i$ 和 $i + 1$ 的道路（还可能存在其他道路） |
| $3$ | 图连通并且 $N = M$ |
| $3$ | 任何道路都不同时属于至少两个简单环（见下文定义） |
| $7$ | 无 |

定义：若用 $u \leftrightarrow v$ 表示一条连接 $u$ 和 $v$ 的道路，则称 $k \geq 3$ 且所有 $w_i$ 互不相同是序列 $w_1 \leftrightarrow w_2 \leftrightarrow \cdots \leftrightarrow w_k \leftrightarrow w_1$ 为简单环。

## 样例 #1

### 输入

```
5 7
1 2
2 4
5 2
4 5
4 3
1 3
1 4
```

### 输出

```
BRGBBGG
```

## 样例 #2

### 输入

```
4 2
1 2
3 4
```

### 输出

```
BB
```

# 题解

## 作者：Wight_sl (赞：6)

# 思路
在图上比较难考虑路径，考虑将图转换为树，选 $n-1$ 条边染色，对于一条灰色的边 $u,v$，它对生成树上边颜色的限制为 $u$ 到 $\operatorname{lca}(u,v)$ 的路径颜色交替出现，$v$ 到 $\operatorname{lca}(u,v)$ 的路径颜色交替出现，且 $\operatorname{lca}(u,v)$ 到 $u,v$ 子树的第一条边颜色不同，前两个限制是比较好满足的，按边的深度奇偶性给边染色即可。考虑解决最后一个限制，容易发现如果这条灰色边在生成树中是返祖边时，这条限制一定满足，横叉边时则不一定满足。注意到这张图是无向图，无向图的 dfs 生成树的非树边全是返祖边。那么只直接在 dfs 生成树上将边按奇偶染色即可，时间复杂度为 $O(n+m)$。实现注意图不一定连通，可能是 dfs 森林。

# 代码
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,col[N];//col用来记录深度奇偶性，-1表示灰色的边 
vector<pair<int,int> > a[N];//用pair存图 点 边的编号 
bool v[N];//标记数组
//dfs生成树 
void dfs(int u,int y){
	v[u]=1;//标记 
	for(int i=0;i<a[u].size();i++){//auto迭代器的等价 
		int x=a[u][i].first,z=a[u][i].second;
		if(v[x]) continue;//如果点以及遍历过了那么直接跳过 
		col[z]=y&1;//否则便通过奇偶性存下 
		dfs(x,y+1);
    }
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		a[u].push_back({v,i});
		a[v].push_back({u,i});
		col[i]=-1;//初始化全是灰色 
    }
	for(int i=1;i<=n;i++){
		if(!v[i]){
			dfs(i,0);//没走过的点就搜一下 
        }
    }
    for(int i=1;i<=m;i++){
		if(col[i]==-1) putchar('G');
		if(col[i]==0)  putchar('R');//偶数为红 
		if(col[i]==1)  putchar('B');//奇数为蓝 
	}
	return 0;
}
```

---

## 作者：Chillturtle (赞：5)

# 题意

图论好题！！！

首先，给你一个图，这个图可能不连通。然后让你对其中某一些边进行染色（染成红蓝两色）。希望原图中连通的两个点之间有一条路径，且这条路径的颜色是红蓝交替的。

数据范围： $1 \le N,M \le 2 \times 10^5$。 

# 思路

首先，我们将这个图转成树来考虑。题目中要求我们两个连通点之间的路径要是红蓝交替的并且涂色的边要最小。所以我们尝试把样例中灰色的边给他删掉，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vmfndpq6.png)

这时，我们可以发现。原图删掉灰色的边之后，原图就变成了一棵搜索树。所以这时做法就非常显而易见了。我们枚举每一个点（因为图不保证连通），然后 DFS，找出搜索树。再拿一个数组记录深度，分奇偶涂色即可。

这里考虑一个问题：记录深度的数组真的需要记录下具体深度吗？答案显而易见，是不用的。因为只有红蓝两种颜色，所以我们只需要记录当前深度对2取模的余数即可。

对于没有包含在搜索树内的边直接涂灰就好。

完结撒花。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<pair<int,int> > edge[N];
int n,m;
bool mark[N];
int color[N];
void init(){
	memset(color,-1,sizeof(color));
	return;
}
void dfs(int u,int y){
	mark[u]=1;
	for(int i=0;i<edge[u].size();i++){
		int to=edge[u][i].first,id=edge[u][i].second;
		if(mark[to]){
			continue;
		}
		color[id]=y%2;
		dfs(to,y+1);
	}
	return;
}
void work(){
	for(int i=1;i<=n;i++){
		if(!mark[i]){
			dfs(i,0);	
		}
	}
	return;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		edge[u].push_back({v,i});
		edge[v].push_back({u,i});
	}
	init();
	work();
	for(int i=1;i<=m;i++){
		if(color[i]==0){
			cout<<"B";
		}
		if(color[i]==1){
			cout<<"R";
		}
		if(color[i]==-1){
			cout<<"G";
		}
	}
	cout<<endl;
return 0;
}
```

---

## 作者：Vindictae (赞：5)

# 题目思路
好吧，我承认这道题我……不会证明。

观察数据，发现，似乎仅仅是一个染色。我们只需要记录一下每次遍历的边，交叉染色即可。

注意点：
- 千万不要随便只抓着一个点开始遍历，因为图可能不连通。
- 不要被样例迷惑，样例并不是唯一解（考试的时候口胡，结果发现自己人脑模拟代码跑出来和样例不一样，然后……就开心的寄了）。
# AC Code
```cpp
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

#define _Frst first
#define _Scnd second

using namespace std;

const int N = 2e5;

void init ();

int n, m;
int u, v;
int _Clr[N + 5];
bool _Flg[N + 5];
vector <pair <int, int>> _Mp[N + 5];

void _DFS (int k, int _Nw) {
	_Flg[k] = 1;
	
	for (register int i = 0; i < _Mp[k].size (); ++ i) {
		if (_Flg[_Mp[k][i]._Frst]) {
			continue;
		}
		
		_Clr[_Mp[k][i]._Scnd] = _Nw & 1;
		_DFS (_Mp[k][i]._Frst, _Nw + 1);
	}
}

signed main () {
	init ();
	cin >> n >> m;
	
	for (register int i = 1; i <= m; ++ i) {
		cin >> u >> v;
		_Mp[u].push_back ({v, i});
		_Mp[v].push_back ({u, i});
	}
	
	for (register int i = 1; i <= n; ++ i) {
		if (_Flg[i]) {
			continue;
		}
		
		_DFS (i, 0);
	}
	
	for (register int i = 1; i <= m; ++ i) {
		if (_Clr[i] == 0) {
			cout << 'R';
		} else if (_Clr[i] == 1) {
			cout << 'B';
		} else {
			cout << 'G';
		}
	}
	
	return 0;
}

void init () {
	memset (_Clr, -1, sizeof (_Clr));
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
}
```

---

## 作者：Little_Cabbage (赞：4)

> 涉及知识点：图的遍历。

我们观察样例可以发现，染色之后的图是一颗树，而且还是 `dfs` 树。

题目要求所以路径上的颜色都是交替的，所以直接交替染色即可。

注意：建图的时候需要记录当前边的编号。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
#define PII pair<int, int>
using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i ++ ) putchar(s[i]);
	}
}
namespace COMB {
	int fact[200000];
	int Triangle[1010][1010];
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace OI;
using namespace COMB;

//#define fre 1
#define IOS 1
//#define multitest 1

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

int n, m;
int color[N];
int f[N];
ve<PII> g[N];

il void Init() {
	memset(color, -1, sizeof color);
	cin >> n >> m;
	for (int i = 1; i <= m; i ++ ) {
		int x, y;
		cin >> x >> y;
		g[x].push_back({y, i});
		g[y].push_back({x, i});
	}
}

il void dfs(int u, int cl) {
	f[u] = 1;
	for (int i = 0; i < g[u].size(); i ++ ) {
		int v = g[u][i].first;
		if (f[v]) continue;
		color[g[u][i].second] = cl % 2;
		dfs(v, cl + 1);
	}
}

il void Solve() {
	for (int i = 1; i <= n; i ++ )
		if (!f[i])
			dfs(i, 0);
	for (int i = 1; i <= m; i ++ ) {
		if (color[i] == -1) cout << "G";
		else if (color[i] == 0) cout << "B";
		else cout << "R";
	}
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

## 作者：Lyco_Reco (赞：2)

题目等价于在原图中删去尽可能多的边，使得原图仍然保持连通，删去的这些边就是灰色边，同时保证剩下的边是红色和蓝色交替的。

不难发现，按照最优方式删边后，得到的一定是原图的生成树。

用 dfs 求出原图的一个生成树，同时记录边的深度，利用深度的奇偶性交替染成红色或蓝色，不在树上的边都是灰色边。

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <deque>
#include <queue>
#include <iomanip>
#include <map>
#include <unordered_map>
using namespace std;
#define int long long
#define inf 0x7f7f7f7f
#define maxn 200010
int n,m,vis[maxn],head[maxn],nxt[maxn<<1],to[maxn<<1],dep[maxn<<1],tot;
struct edge{
	int u,v;
}a[maxn];
namespace Main{
	int rd(){
		int x=0,f=1;
		char ch=getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-'){
				f=-1;
			}
			ch=getchar();
		}
		while(ch>='0'&&ch<='9'){
			x=x*10+ch-'0';
			ch=getchar();
		}
		return x*f;
	}
	void wrt(int x){
		int y=10,len=1;
		if(x<0){
			x=-x;
			putchar('-');
		}
		while(y<=x){
			len++;
			y*=10;
		}
		while(len--){
			y/=10;
			putchar(x/y+'0');
			x%=y;
		}
	}
	void add(int u,int v){
		to[++tot]=v;
		nxt[tot]=head[u];
		head[u]=tot;
	}
	void dfs(int u,int d){
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(vis[v]){
				continue;
			}
			vis[v]=1;
			if(u<v){
				dep[i]=d;
			}
			else{
				dep[i-m]=d;
			}
			dfs(v,d+1);
		}
	}
	void MAIN(){
		n=rd();
		m=rd();
		for(int i=1;i<=m;i++){
			a[i].u=rd();
			a[i].v=rd();
			if(a[i].u>a[i].v){
				swap(a[i].u,a[i].v);
			}
			add(a[i].u,a[i].v);
		}
		for(int i=1;i<=m;i++){
			add(a[i].v,a[i].u);
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				vis[i]=1;
				dfs(i,1);
			}
		}
		for(int i=1;i<=m;i++){
			if(dep[i]&1){
				putchar('B');
			}
			else if(dep[i]==0){
				putchar('G');
			}
			else{
				putchar('R');
			}
		}
	}
}
signed main(){
//	cin.tie(nullptr)->sync_with_stdio(false);
	Main::MAIN();
	return 0;
}
```

---

## 作者：hgckythgcfhk (赞：2)

形式化题意：给定一个没有重边和自环的无向图，将边染成 $3$ 种颜色 R，B，G。在满足任意两个连通的节点在染色后存在一条路径使得路径上边的颜色 R，B 交替的前提下，最小化 R，B 的数量。

且不考虑交替，我们把 G 看作为删边，原题等价于删掉一些边使得在原图种有边的点对在新图中连通。

对于原图的任意一个连通子图，任意点对连通，当且仅当这个子图连通，最小化边数，那一定是求任意一个生成树，显然，不存在更优方案，对于每个连通子图，dfs 即可。

然后就是颜色交替地染色，这并没有使原题变难，在 dfs 的过程中加一个参数表示当前节点到其父亲的边的颜色，每次进入子节点将这个参数取反即可。

```cpp
#include <bits/stdc++.h>
#define il inline
#define rg register
#define cit const rg unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int rg unsigned
#define void il void
#define ll long long
#define ull unsigned ll
#define db double
#define vector basic_string
#define pq priority_queue
#define vint vector<unsigned>
#define vll vector<ll>
#define vull vector<ull>
#define ump unordered_map
#define ust unordered_set
#define deq deque
#define mkp make_pair
#define pii pair<unsigned,unsigned>
#define pll pair<ull,ull>
#define fi first
#define se second
#define Bool(a,n) bitset<N>a
#define sca(a) for(int $=0;$<n;cin>>a[++$])
#define cle(a) memset(a,0,sizeof a)
#define tmx(a) memset(a,0x3f,sizeof a)
#define tmn(a) memset(a,0xbf,sizeof a)
#define tif(a) memset(a,0xff,sizeof a)
#define ge getchar_unlocked()
#define pu putchar_unlocked
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;constexpr unsigned N=2e5+1;
struct A{unsigned u,v;};vector<A>a[N];unsigned char c[N];Bool(b,N);
void dfs(cit u,cit char f){cit char _=f=='R'?'B':'R';b[u]=1;
	for(A&e:a[u])if(!b[e.u])c[e.v]=_,dfs(e.u,_);}
signed main(){open;int n,m;cin>>n>>m;memset(c,'G',m+1);
	for(int i=1,u,v;i<=m;++i)cin>>u>>v,a[u]+={v,i},a[v]+={u,i};
	for(int i=1;i<=n;++i)if(!b[i])dfs(i,'R');for(int i=1;i<=m;++i)pu(c[i]);
}
```

---

## 作者：clever_person (赞：1)

# P10298 [CCC 2024 S4] Painting Roads 题解

## [题目传送门](https://www.luogu.com.cn/problem/P10298)



## 思路
  不难想到，只要有一条红蓝交替的路径。那么，这条路径上的任意两点相连，都可以是灰色。 

  再看题目，便可以发现，对于**每一个连通子图**，只要找到它的**生成树**，将生成树交替涂色，便可以使剩余的边都是灰色。可以使用深搜。


### 提示
* 样例不是唯一解  
* 不要只从一个点开始搜索，因为图不一定联通。  
* 注意是输出每一条边的颜色，需要标记每一条边的编号。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std; 

const int N = 2e5 + 5;
int n, m, vis[N], color[N]; // vis[i] 记录每一个点是否访问过，color[i] 记录每一条边的编号 
vector<int> e[N];
vector<int> id[N];  //标记每条边的编号 

void dfs (int x, int col) {
	vis[x] = 1;
	
	for (int i = 0; i < e[x].size(); ++i) {
		int v = e[x][i], idd = id[x][i];
		if (vis[v]) continue;
		color[idd] = col ^ 1;
		dfs(v, color[idd]);
	}
	
}

int main () {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	memset(color, -1, sizeof color);

	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		e[u].push_back(v), e[v].push_back(u);
		id[u].push_back(i), id[v].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		dfs(i, 0);
	} 
	for (int i = 1; i <= m; ++i) {
		if (color[i] == -1) cout << "G";
		else if (color[i] == 0) cout << "B";
		else cout << "R";
	}
	
	return 0;
}

---

## 作者：Dollartree (赞：1)

### 题目思路
**1. 建图**

将城市的道路看作一个无向图，其中节点代表十字路口，边代表连接两个十字路口的道路。题目保证任意两个十字路口之间至多存在一条道路，也就是没有重边，因此该图是一个无向简单图。

**2. 初始状态**

所有道路初始状态为灰色，表示还未染色，因为你还没有开始刷墙。

**3. 遍历策略**

因为要确保路径上的道路颜色红色和蓝色交替出现，且需要刷尽可能少，所以可以使用深度优先搜索实现这个最小生成树的题。

**4. 交替颜色**

使用一个标记来记录当前正在使用的颜色(红色或蓝色），并在遍历过程中更新标记。

**易错点**

1. 输出的是边的颜色而不是点的。
2. 为什么题目中说满足路径上的道路颜色红色和蓝色交替出现，任何道路都不是灰色的，但是答案中依旧会出现灰色？答案很简单，看图。
![](https://cdn.luogu.com.cn/upload/image_hosting/gxu564d0.png)
图中结点 $2$ 和结点 $3$ 的边是灰色的，如果将其改成红色或蓝色，则首先红色和蓝色没有交替，其次，这样这就不是一个最小生成树，因为这有环。
### 代码
```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;
struct node//结点的结构体 
{
	int t,id;	//t是目标结点，id是边的编号
};
int vis[200010];//做标记的数组 
int b[200010];//储存颜色的数组 
int n,m;//结点个数和边的个数
vector<node> a[200010];//储存边的数组，用vector省空间
void dfs(int k,int col)//col是当前结点颜色，k是当前结点编号 
{
	vis[k]=1;
	for(int i=0;i<a[k].size();++i)//遍历所有与k结点相邻的边
	{
		if(!vis[a[k][i].t])//判断以前是否有来过这个结点 
		{
			b[a[k][i].id]=col%2+1;//交替染色
			vis[a[k][i].t]=1;//打上标记 
			dfs(a[k][i].t,col+1);//下一层 
		}
	}
}
int main(){
	cin>>n>>m;
	int u,v;
	for(int i=1;i<=m;++i)
	{
		cin>>u>>v;
		a[u].push_back(node{v,i});
		a[v].push_back(node{u,i});
	}
  //前面是输入和建图部分
	for(int i=1;i<=n;++i)//遍历节点而不是边因为图不是联通的 
	{
		if(!vis[i])//不要重复 
		{
			dfs(i,1);
		}
	}
	for(int i=1;i<=m;++i)//输出，注意输出的是边的颜色而不是点的。
	{
		if(b[i]==0)
		{
			cout<<"G";
		}
		if(b[i]==1)
		{
			cout<<"R";
		}
		if(b[i]==2)
		{
			cout<<"B";
		}
	}
}//结束 
```

---

## 作者：Arteg (赞：1)

# 简要题意
给你一张无向图，选择部分边红蓝染色，要求对于任意两个直接相连的点 $u,v$，存在 $u$ 到 $v$ 的一条红蓝相间的简单路径，求染色边最少的方案。
# 思路
这道题的部分分有一定启发作用。
## Subtask 1
保证图联通且存在一条 $1$ 至 $n$ 顺次连接的链。容易发现任一连通块内染色边及其端点构成的图必然联通，那么答案下界就是 $n-1$。则显然顺着链依次红蓝染色就是答案。
##  Subtask 2
图是一棵基环树。如果是在一棵树上，我们可以直接根据边的深度的奇偶染色。现在在染色完成的树上连接了一条不染色的边，我们发现，如果其两个端点在原树上的路径不是深度单调的，这样染色便不符合题意。因为深度不单调时，环顶端分岔处相邻两条边深度相同，颜色也相同。那么，怎样才能保证不被染色的边是一条祖先-子孙边呢？思考后可发现，如果我们将 dfs 树作为初始树的的话，环上的点深度一定是单调的，最后剩余的那条未被染色的边，其两端就是环上第一个进入和最后一个进入的点，满足我们的要求。
##  Subtask 3,4
有了以上性质，推而广之就可以发现，一张图根据边的深度奇偶性染色的 dfs 树必定是满足题意的方案。那么，我们只需要在 dfs 每一个联通块的同时染色就可以轻松求出答案了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2000010;
const int mo=1000000007;
const int inf=0x7f7f7f7f7f7f7f7f;

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n,m,vis[maxn],to[maxn<<1],c[maxn];
int head[maxn],tot=1;
struct E{
	int to,nxt;
}e[maxn<<1];

inline void add(int x,int y,int id){
	e[++tot].nxt=head[x];
	e[tot].to=y;
	head[x]=tot;
	to[tot]=id;
	return ;
}

void dfs(int x,int f){
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(vis[y])
			continue;
		c[to[i]]=f^1;
		dfs(y,f^1);
	}
	return ;
}

signed main(){
	n=read();
	m=read();
	for(int i=1;i<=m;i++){
		int a=read(),b=read();
		add(a,b,i);
		add(b,a,i);
	}
	for(int i=1;i<=n;i++)//注意图可能不联通
		if(!vis[i])
			dfs(i,2);
	for(int i=1;i<=m;i++){
		if(c[i]==0)
			putchar('G');
		else if(c[i]==2)
			putchar('B');
		else
			putchar('R');
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：ZPB2011 (赞：0)

# [Painting Roads](https://www.luogu.com.cn/problem/P10298)

## 题意

题意就是尽可能地删边，且删掉的边都是灰色的，并且剩下的边都是红蓝相间的。

## 思路

因为题目要求所有路径互相连接，所以可以先找到一个生成树。

然后在搜索生成树时标记出每一条边的颜色（因为要红蓝交替出现），之后直接输出即可。

找生成树可以先找一个点开始 `dfs` 即可。

## AC code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define pii pair<int, int>
#define fir first
#define sec second
using namespace std;

const int N = 2e5 + 5;

int n, m, col[N];
vector<pii> g[N];
bool vis[N];

void dfs(int u, int dep) {
	vis[u] = 1;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].fir, id = g[u][i].sec;
		if(vis[v]) continue;
		col[id] = dep & 1;
		dfs(v, dep + 1);
    }
}

signed main() {
	memset(col, -1, sizeof(col));//初始化 
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back({v, i});//记得记录下来边的编号 
		g[v].push_back({u, i});
    }
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			dfs(i, 0);//找生成树 
        }
    }
    for(int i = 1; i <= m; i++) {
		if(col[i] == -1) cout << 'G';
		if(col[i] == 0) cout << 'R';
		if(col[i] == 1) cout << 'B';
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑到除了灰边以外的边肯定联通（不然灰边就不能找到另一个没有灰边的路径了），所以我们断定这是一颗有颜色的树。

树不能随便生成，不然会出现三条边需要两两不同的情况。通过观察，我们发现横叉边需要满足颜色上最上边的开头两个不一样。如果有两个横叉边就会出现这种情况。考虑全部改成返祖边。

如何生成只有返祖边的树？从一个根一直 DFS，这样直到返祖的才不搜，其他全部放子树地下。

怎么确定红蓝？第一个红，第二个蓝……在 DFS 的过程中一定是连续的一段边（一条链），直接取不同于上一个边的即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=5e5+1;
int n,m,vis[N],clr[N];
vector<int>e[N];
pair<int,int>E[N];
map<pair<int,int>,int>Eid;
void add(pair<int,int>Edge){
	int u=Edge.first,v=Edge.second;
	e[u].push_back(v);
	e[v].push_back(u);
}
void dfs_t(int u,int fa,int lst){
	vis[u]=1;
	for(auto v:e[u]){
		if(v==fa)
			continue;
		if(vis[v])
			continue;
		pair<int,int>Ee=Eid.count({u,v})?make_pair(u,v):make_pair(v,u);
		clr[Eid[Ee]]=-lst;
		dfs_t(v,u,-lst);
	}
	return;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>E[i].first>>E[i].second;
		add(E[i]);
		Eid[E[i]]=i;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs_t(i,0,1);
	for(int i=1;i<=m;i++)
		if(clr[i]==1)
			cout<<'R';
		else if(clr[i])
			cout<<'B';
		else
			cout<<'G';
    return 0;
}
```

---

## 作者：ylch (赞：0)

[P10298 [CCC 2024 S4] Painting Roads](https://www.luogu.com.cn/problem/P10298)

## Description

给你 $N$ 个结点，$M$ 条边的无向图，初始时所有的边都是灰色的。现在让你把一些边染成红色或蓝色，使得所有结点之间都存在一条红蓝交替出现且没有灰色边的路径。求染色边最少的染色方案。

## Analysis

首先考虑使用类似二分图染色的方法，暴力 DFS 对所有的边随意交替染色，居然蒙过了？？？

- 身为一个严谨认真的 OIer，我们不能就这么一了了之，一定要有**刨根问底的探究精神以及严谨的证明思维**！所以下面是正确性证明。

### 正确性证明

首先明确两个概念：横叉边和返祖边。

这两个概念不是一个图本身有的概念，应该是图进行 DFS 时才有的概念。

在《算法导论》中对这两种边有明确的定义：

> 在 DFS 过程中，设 $vis[i]$ 表示结点 $i$ 被访问的次数，则对于一条边 $u \rightarrow v$：
> - 若 $vis[v]=1$，说明 $v$ 已经被访问，但其子孙后代还没有被访问完（或正在访问中），而 $u$ 又指向 $v$，说明 $u$ 就是 $v$ 的子孙后代，$u \rightarrow v$ 是一条后向边，又称返祖边。
> - $vis[v]=3$，这说明 $v$ 已经被访问，其子孙后代也已经全部访问完，$u \rightarrow v$ 这条边可能是一条横叉边，或者前向边。

以下是示意图（红色的是横叉边，蓝色的是返祖边）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9pzsdxa6.png)

注：其实每一条黑色的主要边都是返祖边，这里为了看起来方便不标蓝。

由此，我们可以得到两条性质：

1. 如果横叉边是灰边，那一定不合法。

   以上图为例，如果 $7 \leftrightarrow 3$、$3 \leftrightarrow 4$ 都是灰边，那在染色时，$2 \rightarrow 7$、$2 \rightarrow 3$ 一定是相同颜色，这显然不符合 $7 \rightarrow 2 \rightarrow 3$ 路径中颜色相异的条件。

3. 如果返祖边是灰边，那一定成立。因为返祖边不会影响树的“主干”部分，而树的主干一定是一条链，可以满足颜色相异的条件。

   同样以上图为例，假设返祖边 $1 \leftrightarrow 7$ 是蓝色，那么 $1 \leftrightarrow 2$ 或 $2 \leftrightarrow 7$ 一定有一条蓝色边，那么在路径 $7 \rightarrow 1 \rightarrow 2$ 或 $1 \rightarrow 7 \rightarrow 2$ 中一定会有一条边有冲突。


我们发现，因为 DFS 是“一路到底”的搜索性质，所以在搜索到横叉边时，会直接当作一条链遍历过去；而因为先遍历的是横叉边，所以返祖边的祖先一定事先被 $vis$ 标记过了，返祖边不会被遍历过去，自然就是黑色。

综上，这道题的树要满足的性质满足 DFS 搜索树的性质，所以可以直接暴力 DFS 染色。证毕。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;

int n, m, col[maxn]; // col[i]表示第i条边的颜色（0:R 1:B 2:G）
int vis[maxn];
vector < array<int,2> > G[maxn];

void dfs(int u, int c){ // c表示当前染的颜色
	vis[u] = 1;
	for(auto it : G[u]){
		auto [v, id] = it;
		if(vis[v]) continue;
		col[id] = c;
		dfs(v, c ^ 1);
	}
}

void solve()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int u, v; cin >> u >> v;
		G[u].push_back({v, i}); // 顺便记录一下边的下标
		G[v].push_back({u, i});
		col[i] = 2; // 初始化全是灰色
	}
	for(int i = 1; i <= n; i ++){
		if(!vis[i]) dfs(i, 1);
	}
	for(int i = 1; i <= m; i ++){
		if(col[i] == 0) cout << 'R';
		if(col[i] == 1) cout << 'B';
		if(col[i] == 2) cout << 'G';
	}
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：Charllote_ (赞：0)

# P10298 [CCC 2024 S4] Painting Roads 题解

### [题目穿送门](https://www.luogu.com.cn/problem/P10298)

---

### 题目简述

给你一个图，请选出数量最少的边并把它们染色，使得任意两个点有有色路径相连，且路径上的颜色，红色和蓝色交替出现。

---

### 题目思路

很显然，选出的边是原图的任意一棵生成树。但是题目不保证道路连通，所以要每个联通图单独考虑。

染色的方法是按照在树上的深度判断，偶数涂红，奇数涂蓝，其余涂灰。

可以拿 `map` 记录颜色，记录时要考虑有序，不然 $xy$ 和 $yx$ 就不是一条边了。

---

### 题目代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const char color[]={'G','R','B'};
vector<int> v[N];
map<pair<int,int>,int> ma;
int n,m,f[N],s[N];
bool vis[N];
void dfs(int x,int deep){
	vis[x]=true;//标记 
	for(int y:v[x]){
		if(vis[y])	continue;//判断标记
		ma[make_pair(max(x,y),min(x,y))]=(deep&1)+1;//看奇偶性涂色
		dfs(y,deep+1);//处理下一个节点
	}
}
signed main(){
	ios::sync_with_stdio(false);	cin.tie(nullptr);
	//输入输出加速
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>f[i]>>s[i];
		if(f[i]<s[i])	swap(f[i],s[i]);
		v[f[i]].push_back(s[i]);	v[s[i]].push_back(f[i]);
	}
	//输入,邻接表建双向边
	for(int i=1;i<=n;i++)
		if(vis[i]==false)	dfs(i,0);
	//任意一颗求生成树
	for(int i=1;i<=m;i++)
		cout<<color[ma[make_pair(f[i],s[i])]];
	//输出
	return 0;
}.
```

---

## 作者：Star_F (赞：0)

一道特殊的最小生成树题。

## 题目大意：
给你一个可能不连通的图，图默认所有边都是灰色，让你对这张图进行染色（红蓝），任意两个灰色边连的点必须存在一条红蓝交替的路径，并且保证染色数最少。

## 题目分析：
因为图不一定联通，所以我们对每一个联通块进行操作。
对于每一个连通块，我们在这个连通块的最小生成树上进行红蓝交替染色。为什么是最小生成树上呢？因为这样做不仅能保证是联通的，还能保证染色数最少。

所以现在思路就很清晰了，但这题不需要真正求出每个联通块的最小生成树，因为边没有边权，所以直接 dfs 遍历每一个联通块即可。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define DEBUG(x) cerr << #x << '=' << x << endl

inline int rd(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x * 10) + (ch - '0'), ch = getchar();
    return x * f;
}

void print(ll x){
    if (x == 0){
        putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    char buf[20];
    int idx = 0;
    while (x){
        buf[idx++] = x % 10 + '0';
        x /= 10;
    }
    while (idx)
        putchar(buf[--idx]);
}

namespace Star_F {
    const int N = 200005;
    int n, m, col[N];
    vector<pair<int, int>> a[N];
    bool v[N];

    void dfs(int u, int y) {
        v[u] = 1;
        for (int i = 0; i < a[u].size(); i++) {
            int x = a[u][i].first, z = a[u][i].second;
            if (v[x]) continue;
            col[z] = y & 1;
            dfs(x, y + 1);
        }
    }

    void Main() {
        n = rd(), m = rd();      //读入
        FOR(i, 1, m) {
            int u = rd(), v = rd();
            a[u].push_back({v, i});    //建图
            a[v].push_back({u, i});    
            col[i] = -1;            //默认为-1（灰色）
        }
        FOR(i, 1, n) {
            if (!v[i]) {
                dfs(i, 0);       //遍历每一个连通块
            }
        }
        FOR(i, 1, m) {
            if (col[i] == -1) putchar('G');   //输出
            if (col[i] == 0)  putchar('R');
            if (col[i] == 1)  putchar('B');
        }
    }
}

signed main(){
    return Star_F::Main(), 0;
}
```

---

## 作者：Ame_wiki (赞：0)

题目传送门：[link](https://www.luogu.com.cn/problem/P10298)。

形式化题意：将图染色，是的任意灰边相连的两个点有一条路径红蓝交替没有灰边，使染色边最少。

思路：对于每个连通块，将其的生成树（连通且边最少）按深度交替染色，这一定是最优的，因为无权就相当于 dfs 树，跑 dfs 即可，途中控制颜色。剩下的全部是灰色边。

注意**图不一定连通**。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

const int N=1000005,M=5005,inf=1e18;

struct Alexander{ int to,clr; }; 
vector<Alexander> G[N];
int n,m,vis[N];
char color[N],clbk[M]={'R','B'};

void dfs(int u,int ncl){
	vis[u]=1;
	for(auto v:G[u]){
		if(vis[v.to]) continue;
		color[v.clr]=clbk[ncl%2];
		dfs(v.to,ncl+1ll);
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back({v,i});
		G[v].push_back({u,i});
	}
	for(int i=1;i<=m;i++) color[i]='G';
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,1);
	for(int i=1;i<=m;i++) cout<<color[i];
	return 0;
} 
```

时间复杂度 $O(n+m)$。

---

## 作者：wizard（偷开O2 (赞：0)

一道图论染色的好题。

### 题意

找到一个无环无向图中的最小生成树，给每条边染色，保证相邻边的颜色不同且染色数最少。

### 分析

观察样例解释后发现，给出的图不一定连通，所以对于每个连通子图，我们直接搜索，从第一条边开始对于搜索树上的每条边交替染色，这必然是最优的方案。

最后如果该边不在搜索树中，那么就是灰色。直接输出答案即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
vector <pair<int,int>> e[maxn];
bool vis[maxn];
int n,m,ans[maxn];
void dfs(int u,int v){
	vis[u]=1;
	for(int i=0;i<(int)e[u].size();i++){
		int now=e[u][i].first;
		if(vis[now]){
		    continue;
		}
		int lem=e[u][i].second;
		ans[lem]=v&1;
		dfs(now,v+1);
	}
}
signed main(){
	cin >> n >> m;
	for(int i=1;i<=m;i++){
	    int u,v;
	    cin >> u >> v;
	    e[u].push_back({v,i});
		e[v].push_back({u,i});
        ans[i]=-1;
	}
	//memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i,0);
		}
	}
	for(int i=1;i<=m;i++){
		if(ans[i]==-1){
			cout << 'G';
		}else if(ans[i]==1){
			cout << 'R';
		}else if(ans[i]==0){
			cout << 'B';
		}
	}
	return 0;
}
```

---

## 作者：P_VICVIC_R (赞：0)

顺着生成树标签进来的，本来来练最小生成树，~~然后发现这题与边权无关。~~

---

### 形式化题目：

在一个图中找一棵生成树，并且将树染色，使得任意直接相连的两点在树上存在一条红蓝相间的简单路径，且是的染色数最少。

### 思路：

题面没有涉及边权，那么最小生成树在边权都相等时就相当于DFS树，所以直接跑搜索就行。

然后是染色，直接在跑搜索时按照奇偶染色就行。

### 注意：

数据范围里有这个表：

| 分值 | 附加条件                                                     |
| :--: | :----------------------------------------------------------- |
|  2   | 对任意 $1≤𝑖<𝑁$ 存在一条连接 $𝑖$ 和 $𝑖+1$ 的道路（还可能存在其他道路） |
|  3   | 图连通并且 $𝑁=𝑀$                                             |
|  3   | 任何道路都不同时属于至少两个简单环（见下文定义）             |
|  7   | 无                                                           |

第二条里有保证图连通，~~那么说明出题人一定搞了不连通的情况搞事。~~

### 代码：

```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
static const int N=1000000;
int n,m;
char ans[N];
vector<pair<int,int> > e[N];
#define id_ first
#define x_ second
int vis[N];
inline void Run(int rt,int col,int id){
    if(vis[rt])
        return;
    vis[rt]=1;
    ans[id]=col?'R':'B';
    for(auto li:e[rt])
        Run(li.x_,col^1,li.id_);
}
signed main(){
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        e[x].push_back({i,y});
        e[y].push_back({i,x});
        ans[i]='G';
    }
    for(int i=1;i<=n;i++)
        Run(i,0,0);
    for(int i=1;i<=m;i++)
        cout<<ans[i];
    return 0;
}
```

---

## 作者：Limitless_lmw (赞：0)

先说坑点：**图不保证联通**

不难发现，题目中每个连通块中红蓝边组成了一个生成树（按遍历到的层数奇偶性分颜色），可以这样证明：

如果一个点 $P$ 所连接两个点 $A$ 和 $B$，那么 $PA$ 与 $PB$ 染同色，那么当 $A$ 与 $B$ 中间有边时，会推出矛盾。

除了这种情况，其他情况正确性显然。

**但是**，非树边（即不在生成树中的边）不会有横插边（一个点的两个后继节点之间的边，即上文中的 $AB$）。这个是由 dfs 序保证的（如果有边，那么 dfs 到一个后继节点是下一个便会到另一个后继节点）。

所以对每个连通块进行一次 dfs 即可。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<int> e[200005];
map<pair<int,int>,int> M;
vector<pair<int,int> >p;
bool vis[200005];

void dfs(int fa,int u){
	for(auto v:e[u]){
		if(vis[v]) continue;
		M[{u,v}]=M[{v,u}]=M[{fa,u}]+1;
		vis[v]=true;
		dfs(u,v);
//		vis[v]=false;
	}
	return ;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1,u,v; i<=m; i++){
		scanf("%d %d",&u,&v);
		p.push_back({u,v});
		e[u].push_back(v);
		e[v].push_back(u);
		M[{u,v}]=M[{v,u}]=0;
	}
	vis[0]=true;
	for(int i = 1 ; i<=n; i++){
		if(vis[i]) continue;
		M[{i,0}]=M[{0,i}]=0;
		vis[i]=true;
		dfs(0,i);
		
	}
	for(int i = 0; i<m; i++){
		if(!M[{p[i].first,p[i].second}]) putchar('G');
		else if(M[{p[i].first,p[i].second}]&1) putchar('B');
		else putchar('R');
	}
	fclose(stdin),fclose(stdout);
	return 0;
}
```

---

## 作者：iyka (赞：0)

抛开题面，感性理解一下样例一的图，那些染色边是不是特别像一颗搜索树？那我们就向着构造树想。

仔细观察，我们可以发现，如果把 $G_5$ 作为根节点构造一颗搜索树，深度为奇数的边都是红色的，深度为偶数的边都是蓝色的，并且经过我们的仔细思考，如果我们任意选取一点作为根节点，然后构造一个搜索树，然后把深度为奇数的边都变为红色，把深度为偶数的边都变为蓝色（反之亦然），这样子对于剩下的灰边，就都满足题意，且时间为 $O(N+M)$，轻松做完。

但显然的，光凭感性分析题目是不够的的，我们还需要理性分析一下正确性和最优性。

### 正确性
其实仔细一研究，我们会发现如果有一条灰边为搜索树上的横叉边那我们上面的构造就是错误的。（假设这条边的的顶点分别为 $u$ 和 $v$，那它所对应的树上最短路径就是 $u\leftrightarrow lca(u,v) \leftrightarrow v$ 显然的会连续经过同一深度，就是两条相邻的颜色相同的边，不符合题意）

但当我们实际做题时，绝大部分人按照感性理解打出的代码确实是正确的，这是因为我们通常是用 dfs 来构造搜索树的，而这道题是无向图，根据 dfs 一路搜到底的特性，我们在遇到横叉边时，会把它当作链来处理，这样灰边就只会作为返祖边，显然符合题意，正确性得以保证。但是到这里都还执意使用 bfs 构造搜索树的人，那正确性就无法保证了。

### 最优性
显然的，答案需要保证染色的边仍使原本联通的子图还是联通的，这时，对于每个联通子图我们就需要至少 $N_i-1$ 条边来保证联通（$i$ 为子图编号），搜索树的边就是是 $N_i-1$ 条，可以保证最优性。

### 代码注意事项
- 在代码实现中，因为我们要统计的是边的深度，输出的也是边的颜色，所以我推荐使用链式前向星来存图，这样我们就可以记录下边的编号。
- 因为图可能不连通（如样例二），我们要多跑几遍 dfs。
- 当 **wa** 了的时候，看一下对边的处理，大概率就是这里出问题了。
- 因为是无向图，所以要开双倍空间。
- 在构造搜索树时一定要用 dfs！！！

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+10;
const char chr[3]={'R','B'}; //输出优化
int head[N],to[N],nxt[N],cnt;
int a[N],b[N],n,m,dep[N],vis[N];
void add(int x,int y) //链式前向星存图
{
	nxt[++cnt]=head[x];
	to[cnt]=y;
	head[x]=cnt;
}
void dfs(int u,int dpp) //dfs构造搜索树
{
	for(int i=head[u];i;i=nxt[i])
	{
		if(!vis[to[i]])
		{
			vis[to[i]]=1;
			dep[((u>to[i]))?(i-m):i]=dpp; //对边的特殊处理1
			dfs(to[i],dpp+1);
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		cin>>a[i]>>b[i];
		if(a[i]>b[i]) //对边的特殊处理2
			swap(a[i],b[i]);
		add(a[i],b[i]);
	}
	for(int i=1;i<=m;++i) //无向图存图
		add(b[i],a[i]);
	for(int i=1;i<=n;++i)
		if(!vis[i])
			vis[i]=1, dfs(i,1);
	for(int i=1;i<=m;++i)
	{
		if(dep[i]==0)
			cout<<"G";
		else
			cout<<chr[dep[i]%2]; //输出优化
	}
	return 0;
} 
```

---

## 作者：O_v_O (赞：0)

# P10298题解

这道题看到的第一眼，发现算法标签里有个生成树，可能很多人想都没想，就开始写生成树了，但跟最小生成树没有一点关系，下面我会介绍这两种写法。

### 生成树

首先看到题面，要尽可能少地对道路进行染色，那肯定要跑最小生成树呀，中途再建边不就可以了吗？所以我们就有了如下伪代码：

```cpp
struct node{
  int u, v, w, id;
}
vector<node> e[N]; //定义

for(int i = 1;i <= m;i++){
  auto [u, v, w] = e[i];
  if(find(u) != find(v)){
    加边;
    
    连接父亲节点;
  }
}
```

写完生成树了，那就到了最关键的一步，染色。

***

### 染色

这个题目的染色是不是跟二分图染色很像（不会也没关系）。

我们首先在 dfs 的时候传入你所需要染的颜色（可以用 $0$ 、 $1$ 代替），然后把跟你连接在一起的边都染上你传入的颜色（拿一个 ans 数组记录），然后我们又可以写出以下伪代码：

```cpp
void dfs(int u, int colour){
  for(auto[v, w, id] : e[u]){
    if(!vis[v]){
      标记已走过;
      记录答案;
      dfs(v, colour ^ 1); 
      //注意，为了不相同，我们要交替颜色传入，这里用到了位运算
    }
  }
}
```

当你做完上面这两步的时候，这道题你就做出来了，但我之前也说过，这道题跟最小生成树没有关系，下面解释原因：

***

### 为什么可以不用最小生成树

我们看题目，发现并没有给出权值，所以我们加边的时候会自动将权值设为 $1$ 这就意味着我们的排序是无用的，因为怎么排序都是原来的顺序，所以我么最后跑的生成树也仅仅只是找出一个联通的树，并无其他作用，所以不用做最小生成树。

***

然后，我们就可以快乐的开始写代码了。

### _AC_code_

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, x, y, ans[N];
bool vis[N];
struct node{
  int v, id;
};
vector<node> e[N];
// 定义变量

// dfs 为染色函数
void dfs(int u, int colour){
  for(auto [v, id] : e[u]){
    if(!vis[v]){
      vis[v] = true;// 将此点标已遍历
      ans[id] = colour;// 记录颜色
      dfs(v, colour ^ 1);// 继续遍历
    }
  }
}
int main(){
  memset(ans, -1, sizeof ans);
  cin >> n >> m;
  for(int i = 1;i <= m;i++){
    cin >> x >> y;
    e[x].push_back({y, i});
    e[y].push_back({x, i});
    // 加边时顺便把边的编号加入
  }
  for(int i = 1;i <= n;i++){
    if(!vis[i]){
      vis[i] = true;
      dfs(i, 0);
      // 注意，图并不保证联通
    }
  }
  for(int i = 1;i <= m;i++){
    if(ans[i] == -1){
      cout << 'G';
    }else if(ans[i] == 0){
      cout << 'R';
    }else{
      cout << 'B';
    }
  }
  return 0;
}
```

> 
> 高尔基曾说过：莫抄袭，棕了你的名，空悲切
>

---

