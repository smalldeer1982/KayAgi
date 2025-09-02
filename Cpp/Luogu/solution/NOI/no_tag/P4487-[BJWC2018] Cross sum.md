# [BJWC2018] Cross sum

## 题目背景

首先介绍一下Kakuro(カックロ) 这个游戏。

游戏规则为：

- 方形空格中填入 $1\sim 9$ 的整数。
- 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。
- 无论是横向还是纵向，连续方格中的数字不能重复。

![](https://cdn.luogu.com.cn/upload/pic/17946.png)
![](https://cdn.luogu.com.cn/upload/pic/17947.png)

左边为一个Kakuro 游戏，右边为这个游戏的唯一解。

我们称一开始给出的数字为线索，称需要填入数字的地方为空格。如果一个格子包含线索那么就不需要填入数字。我们约定所有的谜题都非空，即至少有一个空格需要被填入。

**注意：在以下题目中的游戏规则可能会有所不同，请认真阅读在每个
题目下的规则。**

## 题目描述

游戏规则：

- 空格中填入正整数。
- 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之异或和，左下角的数字等于其下方邻接之连续方格中数字之异或和。
- 所有空格中填入的整数都不能重复。

Apia 给了 Rimbaud 一个 Kakuro 谜题。心不灵手不巧的 Rimbaud 根本不会做 Kakuro，所以她请求你帮她解决。由于 Rimbaud 很年幼，只会对不超过 $2^{60}-1$ 的数字进行运算。所以希望谜题的解中每个数字都不超过
 $2^{60}-1$。

## 说明/提示

对于 $10\%$ 的数据，保证 $n,m \leq 3$。

对于 $30\%$ 的数据，保证$n,m \leq 15$。

对于 $50\%$ 的数据，保证$n,m \leq 40$。

对于另外 $20\%$ 的数据，保证只有第一行第一列包含线索，剩下的地方全都是空格。

对于 $100\%$ 的数据，保证$3 \leq n,m \leq 200$，$1\leq T \leq 5$，保证初始局面中的每个数字不超过 $2^{60}-1$。

## 样例 #1

### 输入

```
3
3 3
0 1 1
2 4 4
2 4 4
3 7
2
6
3 3
0 1 1
2 4 4
2 4 4
1 1
1
1
2 2
0 1
2 4
0
0```

### 输出

```

1 3
2 4
-1
-1```

# 题解

## 作者：mrsrz (赞：11)

~~dls出的神题~~

考虑格子中填数对限制条件的影响。

每个格子填数只会对1行1列产生影响。

所以把行限制、列限制分别作为点，格子为边，就有了一张二分图。

我们需要限定权值，使得每个点的点权恰等于它所有边的边权的异或和。

考虑求出一棵生成树，剩下的边先设其全为0。

显然，每条边的权可以一遍dfs推出来。再判断下合法性、有无相同即可。

对于非树边，我们可以随机给定一个权值，然后修改一下点权，再dfs即可（~~随机出来如果相同的话窝也没办法了QAQ~~）。

还有一种情况：填的格子可能没有行限制或没有列限制。

那先随机给一个权值，然后再跑。最后如果答案不合法，可以修改一个只有一个限制的格子填的数来使答案合法。

代码巨丑，时间复杂度$O(Tn^3)$，可以写得更优的QAQ。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<utility>
#include<unordered_set>
#include<cstring>
#define N 500
#define LoveLive unsigned long long
const LoveLive lim=(1uLL<<60)-1;
struct istream{
	template<typename T>
		inline istream&operator>>(T&d){
			static int c;
			while(!isdigit(c=getchar()));
			for(d=0;isdigit(c);c=getchar())
				d=(d<<3)+(d<<1)+(c^'0');
			return*this;
		}
}cin;
int T_,n,m,kind[N][N];
int cc,cnt,fa[N*N];
int g[N][N];
LoveLive dis[N*N],r[N*N],dot[N*N],V[N*N];
std::pair<int,int>pr[N][N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
struct edge{
	int u,v;
	bool b;
}e[N*N];
struct random{
	LoveLive seed;
	inline void srand(LoveLive s){
		seed=s;
	}
	inline LoveLive operator()(){return(((seed*=37)+=7)*=19260817)^=31;}
}Rand;
#define rand Rand
struct Tree{
	struct EDGE{
		int to,nxt,id;
	}e[N*N<<2];
	int cnt,head[N*N<<1];
	inline void init(){
		memset(head,0,sizeof head);
		cnt=0;
	}
	inline void addedge(int u,int v,int id){
		e[++cnt]=(EDGE){v,head[u],id};
		head[u]=cnt;
		e[++cnt]=(EDGE){u,head[v],id};
		head[v]=cnt;
	}
	void dfs(int now,int pre){
		for(int i=head[now];i;i=e[i].nxt)
		if(e[i].to!=pre){
			dfs(e[i].to,now);
			dis[e[i].id]=r[e[i].to]^dot[e[i].to];
			dot[now]^=dis[e[i].id];
		}
	}
}T;
int main(){
	rand.srand(79877863023177851LL);
	for(cin>>T_;T_--;){
		cin>>n>>m;
		memset(kind,0,sizeof kind);
		memset(g,0,sizeof g);
		memset(dot,0,sizeof dot);
		memset(dis,0,sizeof dis);
		T.init();
		for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		cin>>kind[i][j];
		cc=0;
		for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			pr[i][j]=std::make_pair(0,0);
			if(kind[i][j]==1||kind[i][j]==3)cin>>r[pr[i][j].first=++cc];
			if(kind[i][j]==2||kind[i][j]==3)cin>>r[pr[i][j].second=++cc];
		}
		cnt=0;
		for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		if(kind[i][j]==4){
			if(pr[i-1][j].first&&!pr[i][j].first)pr[i][j].first=pr[i-1][j].first;
			if(pr[i][j-1].second&&!pr[i][j].second)pr[i][j].second=pr[i][j-1].second;
		}
		for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		if(kind[i][j]==4){
			e[g[i][j]=++cnt]=(edge){pr[i][j].first,pr[i][j].second,0};
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)
			if(kind[i][j]==4){
				if(pr[i][j].first==0||pr[i][j].second==0){
					e[g[i][j]].b=1;
					dis[g[i][j]]=rand()%lim+1;
				}
				if(!pr[i][j].first&&pr[i][j].second){
					dot[pr[i][j].second]^=dis[g[i][j]];
				}else
				if(pr[i][j].first&&!pr[i][j].second){
					dot[pr[i][j].first]^=dis[g[i][j]];
				}
			}
		}
		for(int i=1;i<=cc;++i)fa[i]=i;
		for(int i=1;i<=cnt;++i)
		if(e[i].u&&e[i].v&&find(e[i].u)!=find(e[i].v)){
			T.addedge(e[i].u,e[i].v,i);
			fa[find(e[i].v)]=e[i].u;
			e[i].b=1;
		}
		for(int i=1;i<=cnt;++i)if(!e[i].b){
			dis[i]=rand()%lim+1;
			dot[e[i].u]^=dis[i];
			dot[e[i].v]^=dis[i];
		}
		T.dfs(1,1);
		bool ok=1;
		memset(V,0,sizeof V);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)
			if(kind[i][j]==4){
				if(pr[i][j].first)V[pr[i][j].first]^=dis[g[i][j]];
				if(pr[i][j].second)V[pr[i][j].second]^=dis[g[i][j]];
			}
		}
		for(int x=1;x<=cc&&ok;++x)
		if(V[x]!=r[x]){
			bool yes=0;
			for(int i=1;i<=n&&!yes;++i){
				for(int j=1;j<=m&&!yes;++j)
				if(kind[i][j]==4)
				if(pr[i][j].first==x&&!pr[i][j].second||pr[i][j].second==x&&!pr[i][j].first){
					dis[g[i][j]]^=V[x]^r[x];
					yes=1;
				}
			}
			ok&=yes;
		}
		static std::unordered_set<LoveLive>st;
		st.clear();
		for(int i=1;i<=cnt&&ok;++i)
		if(!dis[i]||st.count(dis[i]))ok=0;else st.insert(dis[i]);
		if(ok){
			for(int i=1;i<=n;++i){
				for(int j=1;j<=m;++j)if(g[i][j])printf("%llu ",dis[g[i][j]]);
				putchar('\n');
			}
		}else puts("-1");
	}
	return 0;
}
```

---

## 作者：INF_512 (赞：2)

对于每一个线索格子，格子右上角（如果有）看作行节点，数字看作点权，格子左下角（如果有）看作列节点，数字看作点权；每个空格看作行节点到列节点的边，构造二分图，那么问题变成给所有边赋值，使每个节点的点权恰好等于它的所有边的边权异或和。

性质 $1$：二分图是连通的。

证明：

我们考虑题目中的这句话：每一段连续的空格的左边或者上面的格子包含线索。

假设一段连续的空格是横着的，那么最左边的空格的左边会有一个线索，我们从中任取一个的空格，认为这个连续空格（只有一个）是竖着的，那么这个空格的上面也会有一个线索，所以每一个空格均表示一条行节点和列节点的边。

我认为题目应该再加上一句话：每个 $1$ 类型和 $3$ 类型的格子下面一个格子必定是空格，每个 $2$ 类型和 $3$ 类型的格子右边一个格子必定是空格。否则这个格子就没意义了。

性质 $2$：求出二分图的任意一颗生成树，生成树外的边可以任意赋值。

证明：

我们任取一条生成树外的边权为 $x$ 的边 $(l, r)$，只要令生成树上从 $l$ 到 $r$ 的路径的所有边异或上 $x$，就可以抵消掉这条边。

性质 $3$：给出一颗生成树和每个节点的点权，要么无解，要么生成树的边的赋值方案是唯一的。

证明：

我们给生成树任意指定一个根节点，对于每一个叶子节点，从它到父节点的边的边权只能为叶子节点的点权；对于每一个非叶子节点，从它到儿子的边的边权已经算出，只剩从它到父节点的边的边权未固定，依靠它的点权，就可以把边权算出；对于根节点，从它到儿子的边的边权已经算出，直接判断它的边权的异或和是否等于点权即可。

所以我们只要求出二分图的任意一颗生成树，把生成树外的格子任意赋值，使用dfs确定生成树上的边权，最后记得检查一下有没有重复的格子，就做完了。
```cpp
/*
下面是一些变量的解释

int kind[i][j] : 表示格子 (i, j) 的类型
int wt[i] : 表示编号为 i 的线索权值
pii p[i][j]
p[i][j].first : 表示格子 (i, j) 上方的线索编号
p[i][j].second : 表示格子 (i, j) 左方的线索编号
递推求出每个kind=4格子的 p[i][j]

vector<array<int, 4>> e;
起点线索编号，终点线索编号，格子坐标
以线索编号为点，线索权值为点权，格子为边，建二分图

vector<vector<array<int, 3>>> g;
first 表示终点线索编号，second 表示格子坐标
求出二分图的任意一颗生成树
取了的边vis[i][j]=1

把生成树外的格子(vis[i][j]==0)随机赋值
cwt[i] : 表示编号为 i 的线索的当前权值
ewt[i][j] : 表示格子 (i, j) 的权值

*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned int
#define pii pair<int, int>
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define all(x) (x).begin(), (x).end()
// #define endl '\n'
// #define endl " line in : " << __LINE__ << endl
const int N = 205, INF = 1e16, P = 998244353;
int n, m;
int kind[N][N], wt[N * N], n2;
pii p[N][N];
int fa[N * N];
int vis[N][N];
int ewt[N][N], cwt[N * N];
vector2<array<int, 3>> g;
mt19937_64 gen((random_device())());
uint myrand() {
  uniform_int_distribution<uint> dis(1, (1ll << 60) - 1);
  return dis(gen);
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void dfs(int u, int f) {
  for (auto [v, i, j] : g[u])
    if (v != f) {
      dfs(v, u);
      ewt[i][j] = wt[v] ^ cwt[v];
      cwt[p[i][j].first] ^= ewt[i][j];
      cwt[p[i][j].second] ^= ewt[i][j];
    }
}
int getid(int i, int j) { return (i-1)*m + j-1; }
void test() {
  memset(wt, 0, sizeof(wt));
  memset(p, 0, sizeof(p));
  memset(vis, 0, sizeof(vis));
  memset(ewt, 0, sizeof(ewt));
  memset(cwt, 0, sizeof(cwt));
  n2 = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> kind[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (kind[i][j] == 1) {
        int x; cin >> x;
        n2++, wt[n2] = x, p[i][j].first = n2;
      }
      else if (kind[i][j] == 2) {
        int y; cin >> y;
        n2++, wt[n2] = y, p[i][j].second = n2;
      }
      else if (kind[i][j] == 3) {
        int x, y; cin >> x >> y;
        n2++, wt[n2] = x, p[i][j].first = n2;
        n2++, wt[n2] = y, p[i][j].second = n2;
      }
  vector<array<int, 4>> e;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (kind[i][j] == 4) {
        p[i][j] = { p[i-1][j].first, p[i][j-1].second };
        e.push_back({ p[i][j].first, p[i][j].second, i, j });
      }
  g.assign(n2 + 5, {});
  for (int i = 1; i <= n2; i++)
    fa[i] = i;
  for (auto [u, v, i, j] : e) {
    int fu = find(u), fv = find(v);
    if (fu != fv) {
      fa[fv] = fu;
      g[u].push_back({ v, i, j });
      g[v].push_back({ u, i, j });
      vis[i][j] = 1;
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (kind[i][j] == 4 && vis[i][j] == 0) {
        ewt[i][j] = myrand();
        cwt[p[i][j].first] ^= ewt[i][j];
        cwt[p[i][j].second] ^= ewt[i][j];
      }
  dfs(1, -1);
  if (wt[1] != cwt[1])
    cout << -1 << endl;
  else {
    set<int> st;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (kind[i][j] == 4) {
          if (ewt[i][j] == 0 || st.count(ewt[i][j])) {
            cout << -1 << endl;
            return;
          }
          st.insert(ewt[i][j]);
        }
    for (int i = 1; i <= n; i++, cout << endl)
      for (int j = 1; j <= m; j++)
        if (kind[i][j] == 4)
          cout << ewt[i][j] << ' ';
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T; cin >> T; while (T--)
  test();
  return 0;
}
```


---

