# [USACO20JAN] Cave Paintings P

## 题目描述

Bessie 成为了一名艺术家，正在创作壁画！她现在正在创作的作品是一个高为 $N$ 的方阵，方阵的每行都由 $M$ 个方格组成（$1\le N,M\le 1000$）。每个方格是空的，画了石头，或者画了水。Bessie 已经画上了包含石头的方格，包括整幅画作的边界。她现在想要将某些空的方格画上水，使得如果这幅画是真实的，其中应当不存在水的净移动。定义从上到下第 $i$ 行的方格的高度为 $N+1-i$。Bessie 想要她的画作满足以下限制：

假设方格 $a$ 画的是水。那么如果存在一条从 $a$ 到方格 $b$ 的路径，由高度不超过 $a$ 的空的方格或是有水的方格组成，路径中每相邻两个方格都有一条公共边，那么 $b$ 画的也是水。

求 Bessie 可以创作的不同作品的数量模 $10^9+7$ 的余数。Bessie 可以将任意数量的空格画上水，包括不画以及全画。

## 说明/提示

### 样例解释

如果第二行中的任意一个方格被画上水，那么所有空的方格必须都被画上水。否则，假设没有这样的方格画有水。那么 Bessie 可以选择画上第三行的空格组成的三个连续区域的任意子集。所以，画作的总数等于 $1+2^3=9$。

### 子任务

- 测试点 $1 \sim 5$ 满足 $N,M \leq 10$。
- 测试点 $ 6 \sim 15$ 没有额外限制。

## 样例 #1

### 输入

```
4 9
#########
#...#...#
#.#...#.#
#########```

### 输出

```
9```

# 题解

## 作者：bellmanford (赞：18)

这道题如果想对了方向就很简单了。

~~可如果像我一样一直在想如何把图给抠出一个森林就很难了。~~

发现如果一个格子放了水，对于在这个格子及以下的高度只要有一条路径能到达另一个格子，那那个格子也会有水。

不难联想到可以将各个点标上号，使用**并查集**来做此题。

考虑对于所有水的高度（注：高度是指从下往上的高度）小于等于 $h$ 的方案数，答案应该是所有联通块的方案数的乘积。

可以发现，如果有两个联通块合并，更新的答案应该是这两个联通快的方案数的乘积。

所以对于原先高度为 $h$ 的各个联通块的方案数，可以遍历一遍第 $h+1$ 行，看有哪些联通块可以合并，然后将方案数更新，由于如果在第 $h+1$ 行放一格水，这一个联通快就都会充满水，所以还需将更新完的各个联通块的方案数加一。

那么就可以每次更新联通块，从高度为 $h$ 推到高度为 $h+1$ 了。

为了方便可以将方案数存在祖先那里，然后从第 $n$ 行一直推到第 $1$ 行了。

总效率 $O(nm)$ 。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

#define int long long
#define num(i,j) ((i-1)*m+j)
const int M=1e3+5,JYY=1e9+7;

int n,m,ans=1,fa[M*M],dp[M*M],Map[M][M];
int nxt[3][2]={{1,0},{0,1},{0,-1}};
bool vis[M*M];
char s[M];

int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}

int find(int x){
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}

void unionn(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy,dp[fy]=(dp[fy]*dp[fx])%JYY;
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) fa[num(i,j)]=num(i,j),dp[num(i,j)]=1;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='#') Map[i][j]=1;
			else Map[i][j]=0;
		}
	}
	for(int i=n-1;i>=2;i--){
		for(int j=2;j<=m-1;j++){
			if(Map[i][j]) continue;
			for(int k=0;k<3;k++){
				int nx=i+nxt[k][0],ny=j+nxt[k][1];
				if(!Map[nx][ny]) unionn(num(i,j),num(nx,ny));
			}
		}
		for(int j=2;j<=m-1;j++){
			if(Map[i][j]) continue;
			int f=find(num(i,j));
			if(vis[f]) continue;
			vis[f]=1;dp[f]=(dp[f]+1)%JYY;
		}
		for(int j=2;j<=m-1;j++){
			if(Map[i][j]) continue;
			int f=find(num(i,j));
			vis[f]=0;
		}
	}
	for(int i=2;i<=n-1;i++){
		for(int j=2;j<=m-1;j++){
			if(Map[i][j]) continue;
			if(fa[num(i,j)]==num(i,j)){
				ans=(ans*dp[num(i,j)])%JYY;
			}
		}
	}
	printf("%lld\n",ans);
}
```


---

## 作者：7KByte (赞：6)

有趣的思维题。

首先我们可以定义状态 $f$ 表示一个连通块的方案数，显然$Ans=\prod f$

然后我们从小到大枚举水的高度，不难发现没有水的时候所有空地是分开的，在水位逐渐增高时，这些空地慢慢连接了起来。

显然一个小水洼(高度为$1$) 的 $f=2$，因为要么都选，要么全选。

每次让水位增加 $1$ ，然后合并这些小水洼，合并的时候讲两者的$f$相乘即可，最后每个联通块的 $f$ 增加 $1$ ，因为一个联通块是个整体，全选也算是一种方案。

合并用并查集维护一下即可，合并的时候讲$f$相乘即可。

最后再说一下$Ans=\prod f$

为啥我的代码这么短 $\rm O(NM\log)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,f[4000005],fa[4000005],ans=1;char s[2005][2005];
inline int g(int x,int y){return m*(x-1)+y;}
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%s",s[i]+1);
	rep(i,1,n*m)fa[i]=i,f[i]=1;
	for(int i=n-1;i>1;i--){
		rep(j,2,m-1)if(s[i][j]=='.'&&s[i][j-1]=='.')fa[get(g(i,j))]=get(g(i,j-1));
		rep(j,2,m-1)if(s[i][j]=='.'&&s[i+1][j]=='.')if(get(g(i,j))!=get(g(i+1,j)))
			f[get(g(i,j))]=1LL*f[get(g(i,j))]*f[get(g(i+1,j))]%1000000007,fa[get(g(i+1,j))]=get(g(i,j));
		rep(j,2,m-1)if(s[i][j]=='.'&&get(g(i,j))==g(i,j))f[g(i,j)]++;
	}
	for(int i=n-1;i>1;i--)rep(j,2,m-1)if(s[i][j]=='.'&&g(i,j)==get(g(i,j)))ans=1LL*ans*f[g(i,j)]%1000000007;
	return printf("%d\n",ans),0;
} 
```

---

## 作者：Vocalise (赞：4)

奇怪的联通性 DP...

一句话题意：给定网格图，求满足物理原理的空白部分填充方案数。

行数列数 $n,m\le 1000$。

这里的物理原理大概包括两条：重力作用原理和连通器原理~~好像是一个东西~~。

一个原始的想法是从下向上 DP。

但是方格之间有支配关系。考虑以下一个例子：

```
#####
#...#
#.#.#
#...#
#####
```

答案为 $4$，显然观察得到上层的方格一定支配下层方格，一共 $3$ 层。

但是我们从此得知，两个方格的是否关联要基于 $2$ 个因素：

1. 在一个联通块中；
2. 支配者层数相同或高于被支配的方格。

所以我们考虑从下向上维护并查集。

状态的转移在这里却是比较平凡的。

对于一个方格 $(x,y)$ 代表的在 $x$ 层及以下的连通块中，若干**可以联通**且层数多 $1$ 的联通块代表元素的集合为 $S$。

注意，$S$ 中元素在 $x$ 层上是联通的，但是在 $x+1$ 层上是不联通的。

有：

$$ f_{x,y} = 1+\prod_{(i,j)\in S}f_{i,j} $$

因为如果 $(x,y)$ 充水，就只有一种情况，否则 $S$ 中块互不干扰。

所以有了 $\mathcal O(nm)$ 次并查集 `find` 操作复杂度的解法。

具体实现中:

从下到上枚举每一行 $x$。

首先存下 $x+1$ 的所有点在并查集中的父亲。（代表下文「合并前的并查集」。）

然后对于 $x$ 行的空点，合并与其连通的所有点。（即「合并后的并查集」。）

再枚举 $x+1$ 行所有空点，如果它在合并后的并查集中的祖先在 $x$ 行，则说明它对目前答案有贡献，用它在合并前的并查集中的祖先更新合并后的并查集的祖先。

注意这里每个合并前的祖先只能贡献一次。

然后对 $x$ 行所有点 $f$ 值 $+1$。

这里有并查集合并前与合并后之分，是难理解的地方。

最后答案是所有连通块的答案之积。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

const int N = 1001;
const int NODE = N * N;
const int p = 1000000007;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}
inline int readchar() {
	char ch = getchar();
	while(ch != '#' && ch != '.') ch = getchar();
	return ch;
}

int n,m; char map[N][N];
struct Point {
	int x,y;
	Point() {}
	Point(int _x,int _y): x(_x), y(_y) {}
	friend bool operator ==(const Point &x,const Point &y) {
		return x.x == y.x && x.y == y.y;
	}
};
Point fa[N][N]; int fa1[N];
int vis[N][N],f[N][N];
Point find(Point x) {
	if(fa[x.x][x.y] == x) return x;
	return fa[x.x][x.y] = find(fa[x.x][x.y]);
}
int find1(int x) {
	if(fa1[x] == x) return x;
	return fa1[x] = find1(fa1[x]);
}
void Join(Point x,Point y) {
	x = find(x), y = find(y);
	fa[y.x][y.y] = x;
}

int main() {
	n = read(), m = read();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) {
			map[i][j] = readchar();
			fa[i][j] = Point(i,j);
		}
	for(int i = n - 1;i >= 1;i--) {
		for(int j = 1;j <= m;j++) fa1[j] = fa[i + 1][j].y, vis[0][j] = false;
		for(int j = 1;j <= m;j++) if(map[i][j] == '.') {
			f[i][j] = 1;
			if(map[i + 1][j] == '.') Join(Point(i,j),Point(i + 1,j));
			if(map[i][j - 1] == '.') Join(Point(i,j),Point(i,j - 1));
			if(map[i][j + 1] == '.') Join(Point(i,j),Point(i,j + 1));
		}
		for(int j = 1;j <= m;j++) if(map[i + 1][j] == '.') {
			Point F = find(Point(i + 1,j));
			if(F.x != i) continue;
			int F1 = find1(j);
			if(vis[0][F1]) continue;
			vis[0][F1] = true;
			f[i][F.y] = 1ll * f[i][F.y] * f[i + 1][F1] % p;
		}
		for(int j = 1;j <= m;j++) if(map[i][j] == '.') f[i][j]++;
		// for(int i = 1;i <= n;i++, std::puts(""))
		// 	for(int j = 1;j <= m;j++) std::printf("%d ",f[find(Point(i,j)).x][find(Point(i,j)).y]);
		// std::puts("");
	}
	int ans = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) if(map[i][j] == '.') {
			Point F = find(Point(i,j));
			if(vis[F.x][F.y]) continue;
			vis[F.x][F.y] = true;
			ans = 1ll * ans * f[F.x][F.y] % p;
		}
	std::printf("%d ",ans);
	return 0;
}

```

---

## 作者：LCat90 (赞：2)

很牛顿的题啊。

容易想到，分成联通块分别处理，因为他们互不影响。

对于每个块，从下往上，依次处理每一行。

具体地，使用并查集，将当前位置 $(i,j)$ 与其左右下的位置相连，合并时用 ``dp`` 数组记录当前位置的方案数，即两边相乘。

随后注意，之前我们其实求的是 $i$ 下面一行的方案数。而在每个块中，如果在 $i$ 行的任何位置放水，都可以把目前的块填满，这算一种状态。所以要在原有的基础上加 $1$。

最后的答案就是各个块的乘积。

最后一个问题：怎么把二维坐标当成下标存入并查集？

写一个 ``Hash`` 函数即可，二维转一维。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3 + 5, M = 1e9 + 7;
const int zx[] = {0, 1, 0}, zy[] = {1, 0, -1};
int n, m, fa[N * N], dp[N * N], ans = 1;
bool vis[N * N];
char c[N][N];
int Hash(int x, int y) { return (x - 1) * max(n, m) + y; }
int find(int x) { return (fa[x] == x) ? x : fa[x] = find(fa[x]); }
void Union(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return ;
	fa[x] = y, dp[y] = dp[x] * dp[y] % M;
}
bool check(int x, int y) { return x > 1 and x < n and y > 1 and y < m and c[x][y] != '#'; }
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= 1e6; ++i) fa[i] = i, dp[i] = 1;
	for(int i = 1;i <= n; ++i) scanf("%s", c[i] + 1);
	for(int i = n - 1;i > 1; --i) {
		for(int j = 2;j < m; ++j) 
			if(c[i][j] != '#') 
				for(int k = 0;k < 3; ++k) {
					int dx = i + zx[k], dy = j + zy[k];
					if(check(dx, dy)) Union(Hash(i, j), Hash(dx, dy));
				}
		for(int j = 2;j < m; ++j) 
			if(c[i][j] != '#') {
				int tmp = find(Hash(i, j));
				if(vis[tmp]) continue;
				vis[tmp] = 1, dp[tmp] = (dp[tmp] + 1) % M;
			}
		for(int j = 2;j < m; ++j) 
			if(c[i][j] != '#') vis[find(Hash(i, j))] = 0;
	}
	for(int i = 2;i < n; ++i) 
		for(int j = 2;j < m; ++j) 
			if(c[i][j] != '#') {
				int tmp = Hash(i, j);
				if(tmp == fa[tmp]) ans = ans * dp[tmp] % M;
			}
	cout << ans;
	return 0;
}
```


---

## 作者：zzw4257 (赞：2)

## 

> 给一个有空点的矩形画水使得符合物理原理(~~非常敷衍的描述~~)

定义一个支配关系，对一个点$x$,假设画水则与$x$联通并且高度不高于$x$的点集都要画水

我们称$x$支配了这个子联通块，也可以说是连通块内$x$所在行支配了这个子连通块

不如把这个关系分层每一层有多个点支配下一层的多个点，其中对$x$这一行块，支配集合为$son_x$，行号为$x$的$-1$

则$f_x=\left(\prod\limits_{y\in son_x}f_y\right)+1$外面的$1$是这一行块强行选的情况，其余的是这一行不选，下方任意

可以用并查集维护行块，也可以真的建出这个关系图(是一棵树)

---

## 作者：施玮宸SECSA (赞：2)

这道题好难啊~~~

~~我写了100多行，一次过~~

下面是思路：

染色~~~

用i+1行来推i行

答案为所有根节点的积

时间复杂度：$O(n)$

下面是代码




--------------------------------
我是分割线
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000;
const int mod=1000000007;
int n,m;
int id(int i,int j){ i行j
    return (i-1)*m+j;
}
char s[N+5][N+5];
bool vis[N*N+5]; 
int clr[N+5][N+5],cn[N+5],head[N*N+5],fa[N*N+5];
int cnt;
struct edge{
    int next,des;
}e[N*N+5];
void add(int a,int b){//添加边
	cnt++;
	e[cnt].des=b;
	e[cnt].next=head[a];
	head[a]=cnt;
}
long long dp(int u){//dp函数，代表2元组
	long long cur=1;vis[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].des;cur=cur*dp(v)%mod;
	}
	return (cur+1)%mod;
}
struct graph{//结构体
	int cnt;
    vector<int>link[3*N+5];
    int f[3*N+5];
    queue<int>q;
    void reset(){
        cnt=0;
        for(int i=1;i<=3*m;i++)link[i].resize(0);
        memset(f,0,sizeof(f));
    }
    void add(int a,int b){
        link[a].push_back(b);
        link[b].push_back(a);
    }
    bool bfs(int s){//广搜
        bool flag=0;
        q.push(s);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<link[u].size();i++){
                int v=link[u][i];
                if(!f[v]){
                    if(v<=m)flag=1;
                    f[v]=f[u];
                    q.push(v);
                }
            }
        }
        return flag;
    }
    inline void calc(int i){//计算
        reset();
        for(int j=1;j<m;j++){
            if(s[i][j]=='.'&&s[i][j+1]=='.')add(id(1,j),id(1,j+1));
            if(s[i+1][j]=='.'&&s[i+1][j+1]=='.')add(id(2,j),id(2,j+1));
            if(s[i][j]=='.'&&s[i+1][j]=='.')add(id(1,j),id(2,j));
            if(s[i+1][j]=='.')add(id(2,j),id(3,clr[i+1][j]));
        } 
        for(int j=1;j<=cn[i+1];j++){
            if(f[id(3,j)])continue;
            f[id(3,j)]=++cn[i];
            if(!bfs(id(3,j)))cn[i]--; 
        }
        for(int j=1;j<m;j++){
			if(f[id(1,j)]){
				clr[i][j]=f[id(1,j)];
			} 
		} 
    }
};
graph G;
int main(){
	cin>>n>>m;
	bool flag=1;
	for(int i=1;i<=n;i++){//输入每行
		scanf("%s",s[i]+1);
	}
	for(int i=n-1;i>=2;i--){
		G.calc(i);
		for(int j=2;j<m;j++){
			if(s[i][j]=='.'&&s[i+1][j]=='.')
            fa[id(i+1,clr[i+1][j])]=id(i,clr[i][j]);
		}
		for(int j=1;j<=cn[i+1];j++)
            if(fa[id(i+1,j)])add(fa[id(i+1,j)],id(i+1,j));
        for(int j=2;j<m;j++)if(s[i][j]=='.'&&!clr[i][j]){
            if(s[i][j-1]=='.')clr[i][j]=clr[i][j-1];
            else clr[i][j]=++cn[i];
        }
	}
	long long ans=1;
	for(int i=2;i<n;i++){
		for(int j=2;j<n;j++){
			if(s[i][j]=='.'&&!vis[id(i,clr[i][j])])ans=ans*dp(id(i,clr[i][j]))%mod;
		}
	}//输出
	cout<<ans<<endl;
	return 0;
} 
```

再见ヾ(￣▽￣)Bye~Bye~

---

## 作者：xishanmeigao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6008)

考虑求出所有联通块内部的方案数，再相乘。

先跑一次并查集将所有联通块找出来。

从下往上考虑，从初始开始合并联通块。对于第 $k$ 行，记 $v_i$ 表示第 $i$ 个联通块的形态个数。然后找出**最终**在第 $i$ 个联通块但**现在**还没有合并的所有 $i_1,i_2\dots i_t$，则 $\prod\limits_{j=1}^t v_{i_j}$ 是只考虑行数 $\ge k$ 的贡献。容斥一下，记 $f_{i,j}$ 表示最终第 $i$ 个联通块在第 $j$ 行的答案，将 $\prod v_{i_{j}} -f_{i,k+1}\to f_{i,k}$。

每个联通块的答案就是 $\sum\limits_{k=1}^n f_{i,k}$。

如何维护 $v$ ？同样使用并查集，每次将下一行的 $v$ 相乘，合并完再加 $1$（表示选上这一行）。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define db double
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=1010,M=1e6+10,MOD=1e9+7;

void addm(int &x,int y){(x+=y<0? MOD+y:y)%=MOD;}

int n,m,anc[N][N],ans[M];
bool vis[M];
unordered_map <int,int> f,g;
char s[N][N];

int id(int i,int j)
{
	return (i-1)*m+j;
}

struct DS
{
	int fa[M],v[M];

	int get(int x)
	{
		if(x==fa[x]) return x;
		return fa[x]=get(fa[x]);
	}

	void merge(int x,int y,int op)
	{
		x=get(x), y=get(y);
		if(x==y) return;
		if(x>y) swap(x,y);
		fa[y]=x;
		if(op)
		{
			v[x]=1LL*v[x]*v[y]%MOD;
		}
	}

}S,T;

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
		scanf("%s",s[i]+1);

	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			S.fa[id(i,j)]=T.fa[id(i,j)]=id(i,j);
			T.v[id(i,j)]=1;
		}

	for(int i=n; i>=1; i--)
	{
		for(int j=1; j<=m; j++)
			if(s[i][j]==s[i][j+1] && s[i][j]=='.')
				S.merge(id(i,j),id(i,j+1),0);
		for(int j=1; j<=m; j++)
			if(s[i][j]==s[i+1][j] && s[i][j]=='.')
				S.merge(id(i,j),id(i+1,j),0);
	}

	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			anc[i][j]=S.get(id(i,j));

	for(int i=n; i>=1; i--)
	{
		for(int j=1; j<=m; j++)
			if(s[i][j]==s[i][j+1] && s[i][j]=='.')
				T.merge(id(i,j),id(i,j+1),0);
		for(int j=1; j<=m; j++)
			if(s[i][j]==s[i+1][j] && s[i][j]=='.')
				T.merge(id(i,j),id(i+1,j),1);

		for(int j=1; j<=m; j++)
			if(s[i][j]=='.') f[anc[i][j]]=1, vis[anc[i][j]]=0;
		for(int j=1; j<=m; j++)
		{
			if(T.get(id(i,j))==id(i,j))
			{
				addm(T.v[id(i,j)],1);
				f[anc[i][j]]=1LL*f[anc[i][j]]*T.v[id(i,j)]%MOD;
			}
		}
		for(int j=1; j<=m; j++)
		{
			if(T.get(id(i,j))==id(i,j) && !vis[anc[i][j]])
			{
				vis[anc[i][j]]=1;
				int tmp=g[anc[i][j]];
				addm(ans[anc[i][j]],(f[anc[i][j]]-tmp)%MOD);
			}
		}
		swap(f,g);
		f.clear();
	}

	int prod=1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(s[i][j]=='.' && anc[i][j]==id(i,j))
				prod=1LL*prod*ans[id(i,j)]%MOD;

	printf("%d\n",prod);
	
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

## P6008 解题报告

## 前言

为数不多的独立做出来的蓝牌数数题。

可能因为这个题没有那么数数。

## 思路分析

首先看到连通块，想到并查集。

其次看到 $10^9+7$，想到 dp。

注意到可以以并查集合并的顺序来转移

设 $f_i$ 表示第 $i$ 个并查集内方案总数，$s_i$ 表示第 $i$ 个并查集中和 $i$ 直接连边的点集，则转移为：

$$f_i=1+\prod_{j \in s_i} f_j$$

目标答案为：

$$ans=\prod_{i} f_i$$

即所有连通块答案的积。

注意一下转移顺序就行了，感觉没什么细节。

  时间复杂度为 $O(nm \log n)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,ans;
int id(int i,int j){
	return (i-1)*m+j;
}
char mp[1005][1005];
int fa[1000005],val[1000005],vis[1000005];
void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			fa[id(i,j)]=id(i,j); 
			val[id(i,j)]=1;
		}
	}
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	fa[y]=x;
	val[x]=(val[x]*val[y])%mod;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		}
	}
	init();
	for(int i=n-1;i>=2;i--){
		for(int j=2;j<m;j++){
			if(mp[i][j]=='#') continue;
			if(mp[i][j-1]==mp[i][j]) merge(id(i,j-1),id(i,j));
		}
		for(int j=2;j<m;j++){
			if(mp[i][j]=='#') continue;
			if(mp[i+1][j]==mp[i][j]) merge(id(i,j),id(i+1,j));
		}
		for(int j=2;j<m;j++){
			if(vis[find(id(i,j))]) continue;
			vis[find(id(i,j))]=1;
			val[find(id(i,j))]++;
		}
	}
	ans=1;
	for(int i=n-1;i>=2;i--){
		for(int j=2;j<m;j++){
			if(mp[i][j]=='#') continue;
			if(fa[id(i,j)]==id(i,j)){
				ans=ans*val[id(i,j)]%mod; 
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：jockbutt (赞：1)

# Solution

看到题我的第一想法是把图中的所有块块抠出来，建若干棵树，分别算出来，然后再乘起来算出答案，但是我发现这根本不是我这个弱码力的选手写得出来的，于是考虑一下有什么简单一点的做法。

不难发现，对于一个块块，如果上面要滴水，下面的也必须滴水。所以说我们可以自下而上地算。考虑使用并查集。每次从下往上灌水，合并自己和自己下面的、左右的块块，算出当前自己这个连通块有多少种灌水情况。不难发现，合并的时候方案数就是合并的两个点的乘积。扫完过后，统计一下这一层连通块的数量，每多一块就把这个连通块方案数加一（取或不取）。

最后，答案就是所有连通块贡献的乘积。

其实写的时候不需要真正的建出那棵树，所以代码真心不长，我都写得出来。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int maxn=1010,mo=1e9+7;
int p[maxn+10][maxn+10];
int par[maxn*maxn+10],vis[maxn*maxn+10],f[maxn*maxn];
char ch[maxn+10];
inline int P(int x,int y)	{return (x-1)*m+y;}
inline int find(int x)	{return x==par[x]?x:par[x]=find(par[x]);}
inline void unite(int x,int y)	{x=find(x),y=find(y);if(x!=y)par[x]=y,f[y]=(f[x]*f[y])%mo;}
int ans=1;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=m;++j)	p[i][j]=(ch[j]=='#'),f[P(i,j)]=1,par[P(i,j)]=P(i,j);
	}
	for(int i=n;i;--i)
	{
		for(int j=1;j<=m;++j)
		{
			if(p[i][j])	continue;
			if(!p[i][j+1])	unite(P(i,j),P(i,j+1));
			if(!p[i+1][j])	unite(P(i,j),P(i+1,j));
		}
		for(int j=1;j<=m;++j)
		{
			if(p[i][j])	continue;
			int x=find(P(i,j));
			if(vis[x]!=i)	f[x]++,vis[x]=i;//滚动的vis，可以省去清空的步骤
		}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)	if(par[P(i,j)]==P(i,j))	ans=(ans*f[P(i,j)])%mo;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Nasaepa (赞：0)

这道题就是 dsu + dp。

---

考虑从下往上维护每个块，称一个块的高度为这个块内高度最高的格的高度。

从下往上从左到右扫描每个空白格，如果一个空白格的左侧也是空白格，则它们属于一个块，如果一个空白格的下面也是空白格，它们也属于一个块。考虑通过 dsu 实现块的合并操作，定义一个块的 $f$ 为这个块除了全涂水以外有多少种涂水方案，因此对于这个块，其真正的方案数为 $f+1$ 。

考虑块 $x,y$ 合并，设 $x$ 为两个块中比较靠右上的块，如果 $x,y$ 两块高度相同则更新 $f_x$ 为 $f_xf_y$ ，因为在全涂水时 $x$ 块和 $y$ 块必然都涂满了水，否则更新为 $f_x(f_y+1)$ ，因为 $y$ 块填满水时 $x$ 块不一定填满了水。

跑完之后把所有块的 $(f+1)$ 乘起来就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define N 1010
#define M 1000010
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
const ll mod = 1000000007;

char mp[N][N];
int bel[N][N];
pii to[M];
int dad[M],len;
ll f[M];// 对于第 i 个连通块，它（除了全涂 1）有多少种方案
inline int create(){++len;dad[len] = len;f[len] = 1;return len;}
int find(const int &x){if(dad[x] == x)return x;return dad[x] = find(dad[x]);}
inline void merge(int x,int y){
    x = find(x),y = find(y);
    if(x == y)return ;
    int xs = to[x].first,ys = to[y].first;
    dad[x] = y,f[y] = f[y] * (f[x]+(xs != ys)) % mod;
}


// 主函数
int main(){
    register ll ans = 1;register int n,m;
    scanf("%d%d",&n,&m);
    for(register int i = 1;i <= n;++i)scanf("%s",mp[i]+1);
    // 从下往上数
    for(register int i = n;i >= 1;--i){
        for(register int j = 1;j <= m;++j){
            if(mp[i][j] == '#')continue;
            if(mp[i][j-1] == '.')bel[i][j] = bel[i][j-1];
            else bel[i][j] = create(),to[bel[i][j]] = make_pair(i,j);

            if(mp[i+1][j] == '.')merge(bel[i+1][j],bel[i][j]);
        }
    }
    for(register int i = 1;i <= len;++i){
        if(dad[i] != i)continue;
        ans = (ans * (f[i]+1)) % mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：0)

一种没有见过的 dp，记录一下。神 @[aioilit](https://www.luogu.com.cn/user/496021) 教会了我。

[P6008 [USACO20JAN] Cave Paintings P](https://www.luogu.com.cn/problem/P6008)。

自底向上进行 dp 是显然的，考虑对每个连通块计算贡献。

以样例为例，对于 `#.#...#.#` 有 $3$ 个连通块，每个联通块都有画和不画两种选择。

任意两个连通块不干扰，所以总方案是 $2^3=8$。

思考如何转移。现在多了一行 `#...#...#`，和刚刚那行连起来就只剩一个连通块了。所以可以看做这一层只有一个节点，有 $3$ 个儿子。

所以转移方程是很朴素的 $dp_x=1+\prod dp_i$。$i$ 是能与当前连通块 $x$ 相连的另一个连通块。$+1$ 是因为可以把整个连通块都画上。

用并查集维护即可，讲的可能不是很好，细节见代码吧。

```cpp
#include<bits/stdc++.h>
#define int long long
#define id(x,y) ((x-1)*m+y)
using namespace std;
const int N=1010,mod=1e9+7;
int n,m;
int a[N][N],f[N*N],dp[N*N];
int find(int k)
{
	return f[k]==k?k:f[k]=find(f[k]);
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c;
			cin>>c;
			a[i][j]=c=='.';
			f[id(i,j)]=id(i,j);
			dp[id(i,j)]=1;
		}
	for(int i=n;i>=1;i--)
	{
		for(int j=3;j<m;j++)
			if(a[i][j]&&a[i][j-1])
				f[find(id(i,j))]=find(id(i,j-1));//同一个连通块
		for(int j=2;j<m;j++)
			if(a[i][j]&&a[i+1][j])
			{
				int x=find(id(i,j)),y=find(id(i+1,j));
				if(x==y)continue;//同一个连通块无需转移
				f[y]=x;
				dp[x]*=dp[y],dp[x]%=mod;//不同的连通块不干涉，相乘即可
			}
		for(int j=2;j<m;j++)
			if(a[i][j]&&find(id(i,j))==id(i,j))
				dp[id(i,j)]++;//在根节点计算都画上的贡献
	}
	int ans=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]&&find(id(i,j))==id(i,j))
				ans*=dp[id(i,j)],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

方向错了就真的想不出来了。

答案是每个连通块方案数乘积，先把一行内连续段缩点。连通块可以并查集维护，如何合并方案？从小到大开放点，不难发现若两个连通块合并答案为两者乘积，因为相互独立，最后每一行的连通块方案还要 +1，因为可以用当前最高的覆盖。

---

## 作者：Purslane (赞：0)

# Solution

考虑从下往上分析。非常显然，如果从左到右的空白连续块有一个涂上了水，其他全部都要涂上水。因此可以把他们压成一个点。

如果同一行的两个点可以往下走到一个相同的点，由帕斯卡原理如果其中一个有水另一个肯定也有水。可以用并查集把他们压成一个点。

最终发现，同一行的两个节点不可能向下一层的同一个节点连边：我们形成了一个树形结构。我们不妨由上往下连边。

那么如果父节点涂上水，它的所有子孙都要涂上水。直接跑一边树形 DP 即可。

代码：

```cpp
//QDWHASD JTHF168 M2GA !
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MOD=1e9+7;
int n,m,flg[MAXN][MAXN],id[MAXN][MAXN],fa[MAXN*MAXN],tot,us[MAXN*MAXN];
int anc[MAXN*MAXN];
int find(int k) {
	if(anc[k]==k) return k;
	return anc[k]=find(anc[k]);	
}
void merge(int u,int v) {
	u=find(u),v=find(v);
	anc[v]=u;
	return ;	
}
vector<int> G[MAXN*MAXN];
int solve(int u) {
	int ans=1;
	for(auto v:G[u]) ans*=solve(v)+1,ans%=MOD;
	return ans;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; ffor(i,1,n*m) anc[i]=i;
	ffor(i,1,n) {
		string S; cin>>S;
		ffor(j,1,m) {
			if(S[j-1]=='.') flg[i][j]=0;
			else flg[i][j]=1;	
		}
	}
	roff(i,n-1,1) {
		ffor(j,1,m) if(flg[i][j]==0) {
			if(flg[i][j-1]!=0) ++tot;
			id[i][j]=tot;
			if(flg[i+1][j]==0) {
				int dw=id[i+1][j];
				if(fa[dw]==0) fa[dw]=tot;
				else merge(fa[dw],tot);
			}
		}
		ffor(j,1,m) if(id[i][j]) {
			id[i][j]=find(id[i][j]);
			us[id[i][j]]=1;
			if(id[i+1][j]) fa[id[i+1][j]]=find(fa[id[i+1][j]]);	
		}
	}
	ffor(i,1,tot) if(us[i]&&fa[i]) G[fa[i]].push_back(i);
	int ans=1;
	ffor(i,1,tot) if(us[i]&&fa[i]==0) ans*=solve(i)+1,ans%=MOD;
	cout<<ans;
	return 0;
}
```

空间别开小了。

---

