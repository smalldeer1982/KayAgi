# [USACO17DEC] Push a Box P

## 题目描述

**题目译自 [USACO 2017 December Contest, Platinum](http://usaco.org/index.php?page=dec17results) Problem 2. [Push a Box](http://usaco.org/index.php?page=viewproblem2&cpid=769)**

一个谷仓是一个 $N \times M$ 的矩形网格，有一些网格里有干草。 Bessie 站在其中一个格子内，还有一个格子里有一个大木箱。 Bessie 不能和大木箱在一个格子里，也不能和干草在一个格子里。

如果她不与干草在同一个格子，她就可以往自己旁边的四个方向（东西南北）移动，如果她想移动到有木箱的格子里，那个木箱就会被她推一格（只要木箱的那个方向还有空间），如果没有空间，那 Bessie 就不能移动了。

给你谷仓的布局（空格子，干草以及木箱位置）以及 Bessie 的出发位置和箱子要被推到的位置，请你帮忙计算 Bessie 能不能把木箱推到指定位置。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\leq N,M \leq 1500$，$1\leq Q\leq 50000$。

## 样例 #1

### 输入

```
5 5 4
##.##
##.##
A.B..
##.##
##.##
3 2
3 5
1 3
5 3```

### 输出

```
NO
YES
NO
NO```

# 题解

## 作者：Rainybunny (赞：17)

~~请问dalao们圆方树是什么...~~  
于是, 不妨来想一些简单的操作吧.  

本题的难点是, 移动的箱子造成了地图的不断变化, 箱子所在的点会成为障碍, 可能导致一些本能走到的位置不再相连...这不是**割点**吗$?!$  
在无向连通图中, 对于割点的定义是: 若**删去该点及其连边**, **图不再连通**. 所以我们可以试着强行用$Tarjan$跑出地图上所有割点的坐标, 顺便取得每个点所隶属的点双连通分量编号 ( 所以, 割点应该隶属于多个点双 ), 接下来我们讨论如何快速判断能否从某个方向推动箱子, 假设现有状态"$A-box-B$" ( 具体来说, 设有两个位置$A$, $B$与箱子$box$相邻 ):  
1. 首先由题意, 在不考虑$box$的阻挡时, $A$与$B$应当**由一条经过$box$位置的路径相连**.  

2. 若考虑$box$的阻挡, $A$与$B$不再相通, 则由论述$1.$ $A$, $B$之间**有且仅有一条经过$box$位置的路径相连**. 那么由割点的定义, $box$的位置是割点, $A$, $B$一定不属于同一个点双.  

3. 反之, 则$A$与$B$由至少两条路径$P=<A,v_1,v_2,...,B>$, $P'=<A,v_1',v_2',...,B>$相连, 且满足$P\bigcap P'=\lbrace A,B\rbrace$. 所以$A$, $B$一定隶属于同一个点双.  

于是得出结论:  
**$A$在$box$的阻挡下能到达$B\iff A$, $B$隶属于同一个点双**.  

剩下的一切好说. ~~我就调了俩小时~~. 所以我们再捋一捋代码:  
1. $Tarjan$, 求出每个点隶属的 ( 一个或多个 ) 点双编号.  

2. $BFS/DFS$, 预处理, 尝试让人物靠近箱子的四个方向, 并保存能到达的方向.  
3. $BFS$, 利用上述判别方法, 标记每个箱子能到达的位置.  

$emmm$再好心地说一下细节问题吧:

- 有的小朋友为了方便判断有无相同的点双编号, 会选择使用$set$等$STL$储存每个点所隶属的点双编号, $T$掉一大半, 开$O2$就能$A$. ~~STL极欠调教啊/滑稽~~.  

- 关于最终的$BFS$如何储存状态, 定义$Vis[i][j][k]$表示箱子在$(i,j)$, 人物在箱子的$k$方向即可.  

- 多检查几遍~~那该死的~~$Tarjan$, ~~我帮几个老铁调, 全是Tarjan错/再次滑稽~~.  

好了, 上代码吧. 有详细注释哦!
```cpp
#include <queue>
#include <stack>
#include <cstdio>

#define Int register int

using namespace std;

// 先解释一下万恶变量名... 
const int MAXN = 1500, Move[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
// Move[0..3]分别对应上, 左, 下, 右 
int n, m, q, px, py, bx, by, PDCC, InCpr[MAXN + 5][MAXN + 5][5] = {};
// n, m, q为输入, (px,px)为人物起始坐标, (bx,by)为箱子起始坐标, PDCC为点双数量, InCpr[i][j]为结点隶属信息, 其中InCpr[i][j][0]为隶属个数 
int Indx, DFN[MAXN + 5][MAXN + 5] = {}, Low[MAXN + 5][MAXN + 5] = {};
// Tarjan的一堆东西 
bool Up, Left, Down, Right, Vis[MAXN + 5][MAXN + 5][4] = {}, B_vis[MAXN + 5][MAXN + 5] = {};
// 四个方向能否到达, 以及两个BFS的Vis数组 ( 栈空间开不下 ) 
char Map[MAXN + 5][MAXN + 5] = {};
// 地图 
stack<pair<int, int> > S;
// Tarjan的栈 

struct Node { // BFS结点 
	int px, py, bx, by;
};

inline bool Inside ( const int x, const int y ) { // 出界判断 
	return 1 <= x && x <= n
		&& 1 <= y && y <= m;
}

inline void AddNear ( const int x, const int y, const int NearCprID ) { // 添加一个隶属的点双编号 
	InCpr[x][y][++ InCpr[x][y][0]] = NearCprID;
}

inline void Tarjan ( const int x, const int y, const int fax, const int fay ) { // 万恶之源Tarjan 
	DFN[x][y] = Low[x][y] = ++ Indx; // 这里可以选择将坐标Hash 
	S.push ( make_pair ( x, y ) );
	for ( Int i = 0; i < 4; ++ i ) {
		int nx = x + Move[i][0], ny = y + Move[i][1];
		if ( Inside ( nx, ny ) && Map[nx][ny] ^ '#' ) {
			if ( ! DFN[nx][ny] ) {
				Tarjan ( nx, ny, x, y );
				if ( Low[nx][ny] >= DFN[x][y] ) {
					++ PDCC;
					AddNear ( x, y, PDCC );
					while ( S.top ().first ^ nx || S.top ().second ^ ny ) { // 注意出入栈的细节 
						AddNear ( S.top ().first, S.top ().second, PDCC );
						S.pop ();
					}
					AddNear ( nx, ny, PDCC );
					S.pop ();
				}
				Low[x][y] = min ( Low[x][y], Low[nx][ny] );
			} else if ( DFN[x][y] > DFN[nx][ny] && ( nx ^ fax || ny ^ fay ) ) {
				Low[x][y] = min ( Low[x][y], DFN[nx][ny] );
			}
		}
	}
}

inline void Beclose ( const int x, const int y, const int Boxx, const int Boxy ) { // 贴近box(预处理) 
	queue<pair<int, int> > Q;
	Q.push ( make_pair ( x, y ) );
	B_vis[x][y] = true;
	while ( ! Q.empty () ) { // 这个xjb乱搜就行了, 问题不大 
		pair<int, int> p = Q.front ();
		Q.pop ();
		if ( p.first == Boxx - 1 && p.second == Boxy ) Up = true;
		if ( p.first == Boxx && p.second == Boxy - 1 ) Left = true;
		if ( p.first == Boxx + 1 && p.second == Boxy ) Down = true;
		if ( p.first == Boxx && p.second == Boxy + 1 ) Right = true;
		if ( Up && Left && Down && Right ) return ;
		for ( Int i = 0; i < 4; ++ i ) {
			int nx = p.first + Move[i][0], ny = p.second + Move[i][1];
			if ( Inside ( nx, ny ) && Map[nx][ny] ^ '#' && Map[nx][ny] ^ 'B' && ! B_vis[nx][ny] ) {
				B_vis[nx][ny] = true;
				Q.push ( make_pair ( nx, ny ) );
			}
		}
	}
}

inline bool InSameCpr ( const int s, const int t, const int p, const int q ) { // 暴枚是否属于相同点双 
	for ( Int i = 1; i <= InCpr[s][t][0]; ++ i ) {
		for ( Int j = 1; j <= InCpr[p][q][0]; ++ j ) {
			if ( InCpr[s][t][i] == InCpr[p][q][j] ) {
				return true;
			}
		}
	}
	return false;
}

inline void BFS () {
	queue<Node> Q;
	if ( Up ) Q.push ( Node { bx - 1, by, bx, by } ), Vis[bx][by][0] = true; // 队列初始化 
	if ( Left ) Q.push ( Node { bx, by - 1, bx, by } ), Vis[bx][by][1] = true;
	if ( Down ) Q.push ( Node { bx + 1, by, bx, by } ), Vis[bx][by][2] = true;
	if ( Right ) Q.push ( Node { bx, by + 1, bx, by } ), Vis[bx][by][3] = true;
	while ( ! Q.empty () ) {
		Node p = Q.front ();
		Q.pop ();
		for ( Int i = 0; i < 4; ++ i ) {
			int nbx = p.bx + Move[i][0], nby = p.by + Move[i][1];
			int bkx = p.bx + Move[i ^ 2][0], bky = p.by + Move[i ^ 2][1];
			if ( Inside ( nbx, nby ) && Map[nbx][nby] ^ '#' && ( ( bkx == p.px && bky == p.py ) || InSameCpr ( p.px, p.py, bkx, bky ) ) && ! Vis[nbx][nby][i ^ 2] ) {
				// 在界内 && 不是障碍 && ( 是直接推走 || 可以换方向推 ) && 该状态未入队 
				Vis[nbx][nby][i ^ 2] = true;
				Q.push ( Node { p.bx, p.by, nbx, nby } );
			}
		}
	}
}

inline void Work () {
	scanf ( "%d %d %d", &n, &m, &q );
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = 1; j <= m; ++ j ) {
			char s = getchar ();
			if ( s ^ '.' && s ^ '#' && s ^ 'A' && s ^ 'B' ) { // 判' '与'\n' 
				-- j; continue;
			}
			if ( s == 'A' ) px = i, py = j;
			if ( s == 'B' ) bx = i, by = j;
			Map[i][j] = s;
		}
	}
	Tarjan ( px, py, 0, 0 );
	if ( ! DFN[bx][by] ) { // 这里需要注意, #3的坑点, 人物本来就无法靠近箱子, 特判掉 
		while ( q -- ) {
			int x, y;
			scanf ( "%d %d", &x, &y );
			puts ( x == bx && y == by ? "YES" : "NO" );
		}
		return ;
	}
	Beclose ( px, py, bx, by );
	BFS ();
	while ( q -- ) {
		int x, y;
		scanf ( "%d %d", &x, &y );
		puts ( Vis[x][y][0] || Vis[x][y][1] || Vis[x][y][2] || Vis[x][y][3] ? "YES" : "NO" ); // 轻松判断 
	}
}

int main () {
//	freopen ( "pushbox.in", "r", stdin );
//	freopen ( "pushbox.out", "w", stdout );
	Work ();
	return 0;
}
```
感谢您的阅读. ~~或许是copy代码呢!~~

---

## 作者：Selfish_2U (赞：10)

这个题还是挺值得一做的，算简单，~~虽然我调了四个晚上~~

一开始莫名**RE**，一直卡在**66**分，后来才知道是空间的问题;

一开始我做的时候直接建立方点，把边**全部连上**(<---空间爆炸)，再跑一遍DFS找父亲节点。


后来才发现我可以直接在跑圆方树的时候可以直接把父亲节点给连上，省空间又省时间（之前我好傻啊~）

废话不说了，直接上代码（代码中有注释）


**注意：圆方树空间开两倍！！以及cnt的初始化！！**



### **一开始的代码,如下**：

**圆方树:**

```cpp
void CST(int u)
{
	dfn[u]=low[u]=++deep;
	_stack[++tp]=u;
	for (int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if (!dfn[v]){
			CST(v);
			low[u]=min(low[u],low[v]);
			if (low[v]==dfn[u]){
				++cnt;
				for (int j=0;j!=v;--tp){
					j=_stack[tp];
					T[cnt].push_back(j);//居然还用vector连边，是不是很傻
					T[j].push_back(cnt);
				}
				T[cnt].push_back(u);
				T[u].push_back(cnt);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
	return;
}
```

**判连通:**

```cpp
bool check(int x,int y,int z)
{
	if (fa[x]==fa[y]) return 1;
	if (fa[fa[x]]==z&&fa[fa[y]]==z) return 0;
	if (fa[fa[x]]==z&&fa[fa[z]]==y) return 0;
	if (fa[fa[z]]==x&&fa[fa[y]]==z) return 0;
	if (fa[fa[z]]==fa[fa[x]]&&fa[fa[y]]==z) return 0;
	if (fa[fa[z]]==fa[fa[y]]&&fa[fa[x]]==z) return 0;
	return 1;//好多啊
}
```

### **改了之后:**

**圆方树:**


```cpp
void CST(int u)
{
	dfn[u]=low[u]=++deep;
	_stack[++tp]=u;
	for (int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if (!dfn[v]){
			CST(v);
			low[u]=min(low[u],low[v]);
			if (low[v]==dfn[u]){
				++cnt;
				fa[cnt]=u;//直接连父亲
				for (int j=0;j!=v;--tp)
				{
					j=_stack[tp];
					point[j]=cnt;
				}
				point[u]=cnt;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
	return;
}
```
**判连通：**

```cpp
bool check(int x,int y,int z)
{
	return point[x]==point[y]||fa[point[x]]==y||fa[point[y]]==x;
    								    //这里两点的连通性只与父亲
    								    //或父亲的父亲有关，可以简便些
							            //但其它的题还是得用LCA
}
```


完整代码（~~需要卡一卡时间~~）:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int begin_a,begin_b,end_a,end_b;
int deep,tp,cnt;
int dfn[2250010],low[2250010];
int _stack[2250010];
vector <int> G[2250010];//圆方树基本操作
int point[2250010];
char c[1510][1510];
string s1;
bool p[1510][1510][4];//标记是否从四个方向分别来过
bool dis[1510][1510];//标记是否从i到j过
int fa[4500020];
int dx[4]={0,0,-1,1};//四个方向
int dy[4]={-1,1,0,0};
int read()//丑陋的快读
{
    char ch=getchar();
    int s=0,w=1;
    while (ch<'0'||ch>'9'){
        if (ch=='-') w=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        s=(s<<1)+(s<<3)+ch-'0';
        ch=getchar();
    }
    return s*w;
}
int tra(int x,int y) return (x-1)*m+y;//将二维压缩为一维

int bk1(int x) return (x-1)/m+1;//将二维展开为一维，这是横坐标

int bk2(int x)//将二维展开为一维，这是纵坐标
{
	int y=(x-1)/m+1;
	return x-(y-1)*m;
}
void CST(int u)//圆方树
{
	dfn[u]=low[u]=++deep;//DFS序
	_stack[++tp]=u;//把u加入栈
	for (int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if (!dfn[v]){
			CST(v);
			low[u]=min(low[u],low[v]);
			if (low[v]==dfn[u]){//这代表此时找到一个点双连通分量
				++cnt;
				fa[cnt]=u;//cnt节点的父亲为u
				for (int j=0;j!=v;--tp){
					j=_stack[tp];
					point[j]=cnt;//均指向cnt
				}
				point[u]=cnt;同时也得把u指向cnt
			}
		}
		else low[u]=min(low[u],dfn[v]);	
	}
	return;
}
void BFS(int x,int y)//BFS找能从起点到达的位置
{
	queue<int> q;
	q.push(tra(x,y));
	dis[x][y]=1;//将已走到的标记
	while (!q.empty()){
		int u=bk1(q.front()),v=bk2(q.front());
		q.pop();
		for (int i=0;i<4;i++){
			int a=u+dx[i],b=v+dy[i];
			if(a>=1&&a<=n&&b>=1&&b<=m&&c[a][b]=='.'&&!dis[a][b]){
                dis[a][b]=1;
				q.push(tra(a,b));//把满足能走到的节点加入栈中
            }
		}
	}
}
bool check(int x,int y,int z)//判是否连通
{
	return point[x]==point[y]||fa[point[x]]==y||fa[point[y]]==x;
}
struct node{
	int x_,y_;
};
int main()
{
	n=read();m=read();q=read();
	cnt=n*m;//这里记得把cnt初始化为n*m
	for (int i=1;i<=n;i++){
		cin>>s1;//不知道为什么，直接输入c[i][j]反而慢一些
		for (int j=0;j<m;j++) c[i][j+1]=s1[j];
		for (int j=1;j<=m;j++){//这里是为圆方树连边，即把四周能到达的都与本身连边
		
			if (c[i][j]=='A'||c[i][j]=='.'||c[i][j]=='B'){
				if (c[i-1][j]=='A'||c[i-1][j]=='.'||c[i-1][j]=='B'){
					G[tra(i,j)].push_back(tra(i-1,j));
					G[tra(i-1,j)].push_back(tra(i,j));
				}
				if (c[i][j-1]=='A'||c[i][j-1]=='.'||c[i][j-1]=='B'){
					G[tra(i,j)].push_back(tra(i,j-1));
					G[tra(i,j-1)].push_back(tra(i,j));
				}
			}
			if (c[i][j]=='A') begin_a=i,begin_b=j;//存A的位置
			if (c[i][j]=='B') end_a=i,end_b=j;//存B的位置
		}
	}
	CST(tra(begin_a,begin_b));//圆方树
	BFS(begin_a,begin_b);//从起点跑一边BFS
	queue<node> Q;
	if (dis[end_a][end_b-1]) p[end_a][end_b][0]=1,Q.push(node{tra(end_a,end_b),0});
    										  //这里是判从起点能到箱子
  						 				      //初始位置四周的哪些地方
	if (dis[end_a][end_b+1]) p[end_a][end_b][1]=1,Q.push(node{tra(end_a,end_b),1});
	if (dis[end_a-1][end_b]) p[end_a][end_b][2]=1,Q.push(node{tra(end_a,end_b),2});
	if (dis[end_a+1][end_b]) p[end_a][end_b][3]=1,Q.push(node{tra(end_a,end_b),3});//四个方向都要存
	while (!Q.empty()){
		int u=bk1(Q.front().x_),v=bk2(Q.front().x_);
		int w=Q.front().y_;
		Q.pop();
		int x=u-dx[w],y=v-dy[w];//计算从上一状态推来的位置
		if (x>=1&&x<=n&&y>=1&&y<=m&&c[x][y]!='#'&&p[x][y][w]==0){
			p[x][y][w]=1;
			Q.push(node{tra(x,y),w});//若能满足，则把坐标与推的方向加入栈中
		}
		for (int i=0;i<4;i++){
			if (p[u][v][i]==0&&i!=w&&check(tra(u+dx[w],v+dy[w]),tra(u+dx[i],v+dy[i]),tra(u,v))==1&&c[u+dx[i]][v+dy[i]]!='#'&&u+dx[i]>=1&&u+dx[i]<=n&&v+dy[i]>=1&&v+dy[i]<=m){//防止溢出边界
				p[u][v][i]=1;
				Q.push(node{tra(u,v),i});//同上
			}
		}
	}
	while (q--){
		int a1=read(),a2=read();
		if (c[a1][a2]=='B'||p[a1][a2][0]||p[a1][a2][1]||p[a1][a2][2]||p[a1][a2][3])	puts("YES");
        								//只要有一个方向能推过来就行了
        								//或它本身就是B点
		else puts("NO");
	}
	return 0;
}
```


嗯，代码还是挺短的，大佬们赶紧去切了这道题吧

![ss](https://s1.ax1x.com/2020/10/25/BeX3pd.jpg)


---

## 作者：chenxia25 (赞：9)

经典（？）的推箱子问题。

考虑记录 (箱子的位置, bessie 的位置) 这样的二元组当作状态，正确性肯定是可以的。但是状态是 $(nm)^2$ 这就不好了。但是容易观察到只有当箱子和 bessie 挨在一起的时候的状态才是我们需要关心的关键状态，因为这样才能推得动箱子。你 bessie 要是把箱子放着不动，自己到处游走，那谁管你去了那些景点旅游啊。

接下来要做的事情就是给这 $4nm$ 个状态之间连边，把它们的连通性确定下来。初始状态显然最多只有 $4$ 种，对结束位置显然也只有最多 $4$ 种状态，最终这 $16$ 对中至少一组连通，那答案就是 `YES` 否则是 `NO`。

状态之间的连边只有两种：一种是往当前方向推一格，一种是 bessie 换个方位。前者比较简单，就看看前方有没有障碍物就行了（连的是有向边啊！）。后者的话，判的就是在原图基础上，把箱子的位置堵住（其实就是割掉这个点）然后两种 bessie 的位置是否连通。那这就是圆方树的拿手好戏了——因为把某个点割掉之后原图的分裂情况跟圆方树一致。我们只需要找出 $4$ 种位置各在哪个儿子树里（或者是割掉的点的子树的补集），枚举一下然后用子树的时间戳区间判就可以了。复杂度是均摊的，不用担心，虽然常数有点大但常数瓶颈不在这里。

上面的后者连边中，并不是 $4$ 种情况的每一对连通对都要连双向边，如果这样的话最多要连 $2\dbinom{4}{2}=12$ 条边，平均每个点连出 $3$ 条。其实可以找到每个连通类，然后用一个有向环连起来，这样每个点连出 $1$ 条。不难发现结合前者和后者一共要连 $8nm$ 条边，这大概到了 1e7 级别。而我个人不太喜欢链式前向星那东西，这题一开始也就用 `vector` 写了。那么被卡空间、卡时间无疑了。把 `vector` 换成链式前向星立刻就过了，而且跑得很快，使用空间也只有 ML 的一半——STL，尤其是 `vector` `deque` 之流，确实是奢侈品。下次要是再在有卡空、卡时风险的图论题里不果断用链式前向星，我就 dlxt 好吧！！（把 `vector` 换成前向星真的很麻烦，还不如一开始就写）

另外这题有个小坑。如果目的地就是箱子本来在的地方的话，你 bessie 甚至不需要能到达箱子周围。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=1510;
int n,m,qu;
char a[N][N];
int id(int x,int y){return (x-1)*m+y;}
struct addedge_nei{
	int sz,head[N*N],nxt[4*N*N],val[4*N*N];
	addedge_nei(){sz=0,memset(head,0,sizeof(head));}
	void ae(int x,int y){
		sz++,nxt[sz]=head[x],head[x]=sz,val[sz]=y;
	}
}nei;
int dfn[2*N*N],low[N*N],nowdfn;
int stk[N*N],top;
int cnt;
struct addedge_cnei{
	int sz,head[2*N*N],nxt[4*N*N],val[4*N*N];
	addedge_cnei(){sz=0,memset(head,0,sizeof(head));}
	void ae(int x,int y){
		sz++,nxt[sz]=head[x],head[x]=sz,val[sz]=y;
	}
}cnei;
void tar(int x,int fa=0){
	stk[top++]=x;
	dfn[x]=low[x]=++nowdfn;
	if(!fa&&nei.head[x]==0)return cnt++,cnei.ae(n*m+cnt,x),cnei.ae(x,n*m+cnt),void();
	for(int i=nei.head[x];i;i=nei.nxt[i]){
		int y=nei.val[i];
		if(y==fa){fa=-1;continue;}
		if(!dfn[y]){
			tar(y,x),low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				cnt++;
				while(true){
					int z=stk[--top];
					cnei.ae(n*m+cnt,z),cnei.ae(z,n*m+cnt);
					if(z==y)break;
				}
				cnei.ae(n*m+cnt,x),cnei.ae(x,n*m+cnt);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int mxdfn[2*N*N];
void dfs(int x,int fa=0){
	dfn[x]=mxdfn[x]=++nowdfn;
	for(int i=cnei.head[x];i;i=cnei.nxt[i]){
		int y=cnei.val[i];
		if(y==fa)continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
const string str[]={"right","down","left","up"};
int id0(int x,int y){return x*4-y;}
struct addedge_nei0{
	int sz,head[4*N*N],nxt[8*N*N],val[8*N*N];
	addedge_nei0(){sz=0,memset(head,0,sizeof(head));}
	void ae(int x,int y){
		sz++,nxt[sz]=head[x],head[x]=sz,val[sz]=y;
	}
}nei0;
bool vis0[4*N*N];
void dfs1(int x){
	vis0[x]=true;
	for(int i=nei0.head[x];i;i=nei0.nxt[i]){
		int y=nei0.val[i];
		if(!vis0[y])dfs1(y);
	}
}
bool ok(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m&&a[x][y]!='#';}
bool vis[N*N];
void dfs0(int x,int ban){
	vis[x]=true;
	for(int i=nei.head[x];i;i=nei.nxt[i]){
		int y=nei.val[i];
		if(!vis[y]&&y!=ban)dfs0(y,ban);
	}
}
int main(){
	cin>>n>>m>>qu;
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='#'){
		if(i<n&&a[i+1][j]!='#')nei.ae(id(i,j),id(i+1,j)),nei.ae(id(i+1,j),id(i,j));
		if(j<m&&a[i][j+1]!='#')nei.ae(id(i,j),id(i,j+1)),nei.ae(id(i,j+1),id(i,j));
	}
	for(int i=1;i<=n*m;i++)if(!dfn[i])tar(i);
	memset(dfn,0,sizeof(dfn));nowdfn=0;
	for(int i=1;i<=n*m;i++)if(!dfn[i])dfs(i);
	int A,B;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(a[i][j]=='A')A=id(i,j);
		if(a[i][j]=='B')B=id(i,j);
	}
	dfs0(A,B);
	vector<int> init;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='#'){
		int x=id(i,j),in[4]={};
		for(int k=0;k<4;k++){
			int xn=i+dx[k],yn=j+dy[k];
			if(!ok(xn,yn)){in[k]=-1;continue;}
			if(x==B&&vis[id(xn,yn)])init.pb(id0(x,k));
			int now=0;
			for(int o=cnei.head[x];o;o=cnei.nxt[o]){
				now++;
				int y=cnei.val[o];
				if(dfn[y]<dfn[x])continue;
				if(dfn[y]<=dfn[id(xn,yn)]&&dfn[id(xn,yn)]<=mxdfn[y])in[k]=now;
			}
			int xx=i-dx[k],yy=j-dy[k];
			if(!ok(xx,yy))continue;
			nei0.ae(id0(x,k),id0(id(xx,yy),k));
		}
		for(int k=0;k<10;k++){
			vector<int> v;
			for(int o=0;o<4;o++)if(in[o]==k)v.pb(id0(x,o));
			for(int o=0;o+1<v.size();o++)nei0.ae(v[o],v[o+1]);
			if(v.size()>1)nei0.ae(v.back(),v[0]);
		}
	}
	for(int i=0;i<init.size();i++)dfs1(init[i]);
	while(qu--){
		int x,y;
		scanf("%d%d",&x,&y);
		bool yes=id(x,y)==B;
		for(int i=0;i<4;i++)yes|=vis0[id0(id(x,y),i)];
		puts(yes?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：kczno1 (赞：7)

(其实这题不难啊，怎么全网无中文题解)

$bfs$，状态$(x,y,i)$表示始终合法的走，最后一次推箱操作的方向为$i$($i \in [0,4) $)，推完了的箱子坐标为$(x,y)$。

现在的问题就是如何判断不经过箱子所在的点，从箱子的一个相邻点走到另一个相邻点。

这样的话这两个点就有两条点不相交的路径可以相互到达，这就等价于这两个点属于同一个点双连通分量。

用圆方树判一下，相同爸爸，或者一个点是另一个点的爷爷。

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1500+5,T=N*N,fx[4]={-N,N,-1,1};
char s[T];int sx,tx;
namespace DFS
{
int dfn[T],low[T],tot;
int fa[T*2],bcnt;
int st[T],top;
void dfs(int x,int fr)
{
	dfn[x]=low[x]=++tot;
	st[++top]=x;
	rep(i,0,3)
	if(i!=fr)
	{
		int y=x+fx[i];
		if(s[y]!='.')continue;
		if(dfn[y]){chmin(low[x],dfn[y]);continue;}
		dfs(y,i^1);
		chmin(low[x],low[y]);
		if(low[y]>=dfn[x])
		{
			++bcnt;
			fa[T+bcnt]=x;
			while(1)
			{
				fa[st[top]]=T+bcnt;
				--top;
				if(st[top+1]==y)break;
			}
		}
	}
}
void main()
{
	dfs(sx,-1);
}
bool connected(int x,int y)
{
	return fa[x]==fa[y]||fa[fa[x]]==y||fa[fa[y]]==x;
}
};

namespace BFS1
{
bool vis[T];
int q[T];
void main()
{
	int tail=1;
	vis[q[1]=sx]=1;
	vis[tx]=1;
	rep(head,1,tail)
	{
		int x=q[head];
		rep(i,0,3)
		{
			int y=x+fx[i];
			if(s[y]!='.')continue;
			if(vis[y])continue;
			vis[q[++tail]=y]=1;
		}
	}
}
};

namespace BFS2
{
bool vis[T][4];
int q[4*T];
void main()
{
	int tail=0;
	rep(i,0,3)
	{
		int x=tx+fx[i^1];
		if(!BFS1::vis[x])continue;
		vis[tx][i]=1;
		q[++tail]=tx*4+i;
	}
	rep(head,1,tail)
	{
		int t=q[head]/4,i=q[head]%4;
	//	cerr<<t/N<<" "<<t%N<<" "<<i<<endl;
		int y=t+fx[i];
		if(s[y]=='.'&&!vis[y][i])
		{
			vis[y][i]=1;
			q[++tail]=y*4+i;
		}
		int x=t+fx[i^1];
		rep(j,0,3)
		if(!vis[t][j])
		{
			int y=t+fx[j^1];
			if(s[y]!='.'||!DFS::connected(x,y))continue;
			vis[t][j]=1;
			q[++tail]=t*4+j;
		}
	}
}
bool ok(int x)
{
	if(x==tx)return 1;
	rep(i,0,3)
	if(vis[x][i])return 1;
	return 0;
}
};

int main()
{
	freopen("1.in","r",stdin);freopen("1.out","w",stdout);
	int n,m,q;
	cin>>n>>m>>q;
	rep(i,1,n)
	{
		scanf("%s",s+i*N+1);
		rep(j,i*N+1,i*N+m)
		if(s[j]=='A')
		{
			sx=j;
			s[j]='.';
		}
		else
		if(s[j]=='B')
		{
			tx=j;
			s[j]='.';
		}
	}
	
	DFS::main();
	BFS1::main();
	BFS2::main();
	
	while(q--)
	{
		int x0,y0;
		scanf("%d%d",&x0,&y0);
		int x=x0*N+y0;
		puts(BFS2::ok(x)?"YES":"NO");
	}
}
```



---

## 作者：Ark_ (赞：5)

看到只有圆方树的题解，我来发一个点双的。

显然这道题就是直接搜索。定义状态为f[i][j][0~4]表示箱子在(i,j)，人在某个方向推。然后问题就是怎么转向。我们发现如果要转向，必须是人走过一条不包括(i,j)的路径到另一个方向。那么直接求一个点双联通分量就完事了。把点双联通里面的点两两之间都有至少两条不经过重复点的路径，这样就能转向了。

点双内，具体的处理方法是开一个桶。

具体见代码



```cpp// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1505;
const int MAXP = MAXN*MAXN;
int n, m, q, id[MAXN][MAXN], tot, tmr;
int fir[MAXP], to[MAXP<<2], nxt[MAXP<<2], cnt, A, B;
int dfn[MAXP], low[MAXP], stk[MAXP], indx, scc[MAXP];
char s[MAXN][MAXN];
pair<int,int>pos[MAXP];

inline void link(int u, int v) {
    to[++cnt] = v; nxt[cnt] = fir[u]; fir[u] = cnt;
    to[++cnt] = u; nxt[cnt] = fir[v]; fir[v] = cnt;
}
bool vis[MAXN][MAXN];
bool can[MAXN][MAXN][4][4];
//0 : L
//1 : R
//2 : U
//3 : D
const int Dx[4] = { 0, 0, -1, 1 };
const int Dy[4] = { -1, 1, 0, 0 };
inline void ins(int k) {
    vis[pos[k].first][pos[k].second] = 1;
    for(int u, v, i = 0; i < 4; ++i) {
        u = pos[k].first - Dx[i];
        v = pos[k].second - Dy[i];
        if(u >= 1 && u <= n && v >= 1 && v <= m && s[u][v] != '#') {
            for(int x, y, j = 0; j < 4; ++j) if(j!=i) {
                x = u + Dx[j], y = v + Dy[j];
                if(x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] != '#' && vis[x][y])
                    can[u][v][i][j] = can[u][v][j][i] = 1;
            }
        }
    }
}
inline void del(int k) {
    vis[pos[k].first][pos[k].second] = 0;
}
inline void tarjan(int u, int ff) {
    dfn[u] = low[u] = ++tmr;
    stk[++indx] = u;
    for(int v, i = fir[u], j; i; i = nxt[i])
        if((v=to[i]) != ff) {
            if(!dfn[v]) {
                tarjan(v, u), low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    for(j = indx; ; --j) {ins(stk[j]); if(stk[j] == v) break; } if(dfn[u]==low[v])ins(u);
                    for(j = indx; ; --j) {del(stk[j]); if(stk[j] == v) break; } if(dfn[u]==low[v])del(u);
                    indx = j-1;
                }
            }
            else low[u] = min(low[u], dfn[v]);
        }
}

bool dis[MAXN][MAXN];
inline void bfs(int Sx, int Sy) {
    queue<pair<int,int> >Q;
    Q.push(pair<int, int>(Sx, Sy));
    dis[Sx][Sy] = 1;
    while(!Q.empty()) {
        int u = Q.front().first, v = Q.front().second; Q.pop();
        for(int x, y, i = 0; i < 4; ++i) {
            x = u + Dx[i], y = v + Dy[i];
            if(x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] == '.' && !dis[x][y]) {
                dis[x][y] = 1, Q.push(pair<int, int>(x, y));
            }
        }
    }
}
struct node {
    int x, y, z;
    node(){}
    node(int x, int y, int z):x(x), y(y), z(z){}
};
bool f[MAXN][MAXN][4];
queue<node>que;
int main () {
    //freopen("pushbox.in", "r", stdin);
    //freopen("pushbox.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s[i]+1);
        for(int j = 1; j <= m; ++j) {
            if(s[i][j] != '#') {
                id[i][j] = ++tot;
                pos[tot] = pair<int,int>(i, j);
                if(j > 1 && s[i][j-1] != '#') link(id[i][j-1], id[i][j]);
                if(i > 1 && s[i-1][j] != '#') link(id[i-1][j], id[i][j]);
            }
            if(s[i][j] == 'A') A = id[i][j];
            if(s[i][j] == 'B') B = id[i][j];
        }
    }
    tarjan(B, 0);
    bfs(pos[A].first, pos[A].second);
    int Sx = pos[B].first, Sy = pos[B].second;
    if(dis[Sx][Sy-1]) f[Sx][Sy][0] = 1, que.push(node(Sx, Sy, 0));
    if(dis[Sx][Sy+1]) f[Sx][Sy][1] = 1, que.push(node(Sx, Sy, 1));
    if(dis[Sx-1][Sy]) f[Sx][Sy][2] = 1, que.push(node(Sx, Sy, 2));
    if(dis[Sx+1][Sy]) f[Sx][Sy][3] = 1, que.push(node(Sx, Sy, 3));
    while(!que.empty()) {
        int u = que.front().x, v = que.front().y, w = que.front().z; que.pop();
        int x = u - Dx[w], y = v - Dy[w];
        if(x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] != '#' && !f[x][y][w])
            f[x][y][w] = 1, que.push(node(x, y, w));
        for(int i = 0; i < 4; ++i)
            if(i != w && can[u][v][w][i] && !f[u][v][i]) {
                f[u][v][i] = 1, que.push(node(u, v, i));
            }
    }
    int Tx, Ty;
    while(q--) {
        scanf("%d%d", &Tx, &Ty);
        puts((s[Tx][Ty] == 'B' || f[Tx][Ty][0] || f[Tx][Ty][1] || f[Tx][Ty][2] || f[Tx][Ty][3]) ? "YES" : "NO");
    }
}
```


---

## 作者：crashed (赞：4)

# 题目：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problemnew/show/P4082)看题目。
# 分析：
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;经典的推箱子~~游戏~~问题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;先给出一种暴力做法吧。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对箱子进行$BFS$。在每次转移状态的时候，再用一个$BFS$检查人能不能到需要到的地方去。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;可以看出，这种~~傻逼又智障~~的方法的时间太大，达到了$O((X\times Y)^2)$，完全无法过题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;深入思考一下，我们可以发现，该方法中最耗时间的地方在于：  

> “检查人能不能到需要到的地方”  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这也是我们优化的起点。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;现在，我们把原来的地图重构成一张图。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于箱子在的位置人无法通过，相当于新图中**箱子位置的点被取下来了**。关于取点这个“话题”，我们很自然地想到了割点。于是我们可以对箱子的位置进行如下讨论：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.箱子不在原图的割点上。此时箱子没有使原图的连通性改变，所以只需要检查起始点和目标点是否在一个连通块里即可。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.箱子在原图的割点上。此时箱子对原图的连通性有影响，所以需要检查起始点和目标点是否在一个**点双连通分量**中。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用$Tarjan$处理出上面的东西之后，我们就可以愉快地用$BFS$过题啦。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;（$PS$：不知道$Tarjan$和割点的朋友请进[传送门](https://www.luogu.org/blog/styx-ferryman/chu-tan-tarjan-suan-fa-qiu-qiang-lian-tong-fen-liang-post)）

# 代码：
```cpp
#include <stack>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1505, MAXM = 1505, MAXQ = 50005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s < '0' || '9' < s ){ if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ x = -x, putchar( '-' ); }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct node
{
	int bx, by, side;
	node(){}
	node( const int Bx, const int By, const int type )
	{
		bx = Bx, by = By, side = type;
	}
};

queue<node> q;
stack<pair<int, int> > sta;

int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
int query[MAXN][MAXM];
int DFN[MAXN][MAXM], LOW[MAXN][MAXM], color[MAXN][MAXM], beIn[MAXN][MAXM][5];
//由于新图中一个点最多会连出4条边，所以一个点也最多会在4个点双连通分量里面，故记录点所处点双连通分量编号的beIn数组就可以只开5个。
int N, M, Q, sx, sy, bx, by, ID, tot, col;
char obs[MAXM];
bool isCut[MAXN][MAXM];
bool mp[MAXN][MAXM], visited[MAXN][MAXM][4] = {}, ans[MAXQ];

bool inside( const int cx, const int cy )
{
	return 1 <= cx && cx <= N && 1 <= cy && cy <= M;
}

void Tarjan( const int x, const int y, const int fx, const int fy )
{
	int tx, ty, cnt = 0;
	color[x][y] = col;
    //用染色法处理连通块
	DFN[x][y] = LOW[x][y] = ++ID;
	sta.push( make_pair( x, y ) );
	for( int i = 0 ; i < 4 ; i ++ )
	{
		tx = dir[i][0] + x, ty = dir[i][1] + y;
		if ( inside( tx, ty ) && ! mp[tx][ty] )
		{
			if( ! DFN[tx][ty] )
			{
				cnt ++;
				Tarjan( tx, ty, x, y );
				if ( DFN[x][y] <= LOW[tx][ty] )
				{
					tot ++;
					isCut[x][y] = true;
					pair<int, int> tar = make_pair( tx, ty ), tmp;
					do
					{
						tmp = sta.top();sta.pop();
						beIn[tmp.first][tmp.second][++beIn[tmp.first][tmp.second][0]] = tot;
					}while( tar != tmp );
					beIn[x][y][++beIn[x][y][0]] = tot;
				}
				LOW[x][y] = MIN( LOW[x][y], LOW[tx][ty] );
			}
			else if( DFN[tx][ty] < DFN[x][y] && ( tx ^ fx || ty ^ fy ) )
			{
				LOW[x][y] = MIN( LOW[x][y], DFN[tx][ty] );
			}
		}
	}
	if( ! fx && ! fy && cnt == 1 ) isCut[x][y] = false;
	if( ! fx && ! fy && ! cnt ) beIn[x][y][++beIn[x][y][0]] = ++tot;
}

//二维情况下的Tarjan

bool chk( const int obsX, const int obsY, const int fx, const int fy, const int tx, const int ty )
{
	if( ! inside( fx, fy ) || ! inside( fx, fy ) ) return false;
	if( mp[fx][fy] || mp[tx][ty] ) return false;
	if( ! isCut[obsX][obsY] ) return color[fx][fy] == color[tx][ty];
	for( int i = 1 ; i <= beIn[fx][fy][0] ; i ++ )
	{
		for( int j = 1 ; j <= beIn[tx][ty][0] ; j ++ )
		{
			if( beIn[fx][fy][i] == beIn[tx][ty][j] ) return true;
		}
	}
	return false;
}

//检查起点能否到达终点

int sChk( const int cx, const int cy, const int px, const int py )
{
	int tx, ty;
	for( int i = 0 ; i < 4 ; i ++ )
	{
		tx = dir[i][0] + cx, ty = dir[i][1] + cy;
		if( tx == px && ty == py ) return i;
	}
	return -1;
}

int trans( const int side )
{
	if( side == 0 ) return 1;
	if( side == 1 ) return 0;
	if( side == 2 ) return 3;
	if( side == 3 ) return 2;
}

void BFS()
{
	while( ! q.empty() ) q.pop();
	int tx, ty;
	if( sChk( bx, by, sx, sy ) == -1 )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			tx = dir[i][0] + bx, ty = dir[i][1] + by;
			if ( chk( bx, by, sx, sy, tx, ty ) )
			{
				q.push( node( bx, by, i ) );
				visited[bx][by][i] = true;
			}
		}
	}
	node head;
	int mx, my;
	while( ! q.empty() )
	{
		head = q.front();
		q.pop();
		if( query[head.bx][head.by] ) ans[query[head.bx][head.by]] = true;
		for( int i = 0 ; i < 4 ; i ++ )
		{
			tx = dir[i][0] + head.bx, ty = dir[i][1] + head.by;
			mx = dir[trans( i )][0] + head.bx, my = dir[trans( i )][1] + head.by;
			if( ! visited[tx][ty][trans( i )] && inside( tx, ty ) && ! mp[tx][ty] && chk( head.bx, head.by, head.bx + dir[head.side][0], head.by + dir[head.side][1], mx, my ) )
			{
				visited[tx][ty][trans( i )] = true;
				q.push( node( tx, ty, trans( i ) ) );
			}
		}
	}
}

int main()
{
//	freopen( "pushbox.in", "r", stdin );
//	freopen( "pushbox.out", "w", stdout );
	read( N ), read( M ), read( Q );
	for( int i = 1 ; i <= N ; i ++ )
	{
		scanf( "%s", obs + 1 );
		for( int j = 1 ; j <= M ; j ++ )
		{
			switch( obs[j] )
			{
				case '#':
				{
					mp[i][j] = true;
					break;
				}
				case 'A':
				{
					sx = i, sy = j;
					break;
				}
				case 'B':
				{
					bx = i, by = j;
					break;
				}
			}
		}
	}
	int qx, qy;
	for( int i = 1 ; i <= Q ; i ++ )
	{
		read( qx ), read( qy );
		query[qx][qy] = i;
		if( qx == bx && qy == by ) ans[i] = true;
      //特判起点是终点的情况
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			if( ! DFN[i][j] && ! mp[i][j] )
			{
				col ++;
				Tarjan( i, j, 0, 0 );
			}
		}
	}
	BFS();
	for( int i = 1 ; i <= Q ; i ++ )
	{
		if( ans[i] ) puts( "YES" );
		else puts( "NO" );
	}
	return 0;
}
```

---

## 作者：miaokehao (赞：2)

这道题目有两种决策（假设f[x][y][i]代表表示x,y由i这个dx,dy转移过来的可行性）：   
1. 以这个方向继续推   
2. 从这个相邻点到另一个相邻点且不经过箱子所在的点

第一种情况可以简单通过bfs转移

第二种情况可以建圆方树解决，但我们只需要记录点双连通分量的父亲。当一个相邻点转移到另一个相邻点时，如果可以不用经过格子的话，等价于(pos代表x属于的点双连通分量)fa[pos[x]]=y||fa[pos[y]]=x||x==y

在处理所有情况后，每次询问都是O(1)的。
总时间复杂度O(n*m);
```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(4)
#pragma GCC optimize("Ofast,no-stack-protector")
#include <bits/stdc++.h>
#define res register int
#define N 1505
#define M 2265025
const int dx[4]={0,-1,1,0};
const int dy[4]={-1,0,0,1};
using namespace std;
int n,m,Q,st[M],f[N][N][4],q,top,id[N][N],tot,fa[M],tim,sx,sy,ex,ey,d[M],num,dfn[M],low[M],cnt,pos[M];
char s[N];
bool vis[N][N];
inline int read(){
	res w=0,X=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){X=(X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w?-X:X;
}
struct papa{
	int to,next;
}e[M<<2];
struct point{
	int x,y,op;
	point():x(0),y(0),op(0){};
	point(int x0,int y0):x(x0),y(y0),op(-1){};
	point(int x0,int y0,int op0):x(x0),y(y0),op(op0){};
};
queue<point> l;
inline void add(res x,res y){
	e[++tot].to=y;
	e[tot].next=d[x];
	d[x]=tot;
}
inline bool check(res x,res y){
	return pos[x]==pos[y]||fa[pos[x]]==y||fa[pos[y]]==x;
}
inline void tarjan(res now,res fath){
	dfn[now]=low[now]=++tim;
	st[++top]=now;
	for(res i=d[now];i;i=e[i].next){
		res x=e[i].to;
		if(x==fath) continue;
		if(!dfn[x]){
			tarjan(x,now);
			low[now]=min(low[now],low[x]);
			if(dfn[now]>low[x]) continue;
			num++;
			fa[num]=now;
			for(;st[top]!=x;){
				pos[st[top]]=num;
				top--;
			}
			pos[st[top]]=num;
			top--;
		}
		else
		  low[now]=min(low[now],dfn[x]);
	}
}
int main(){
	n=read(),m=read(),q=read();
	for(res i=1;i<=n;i++){
		scanf("%s",s+1);
		for(res j=1;j<=m;j++){
			if(s[j]=='#') continue;
			id[i][j]=++cnt;
			if(s[j]=='A') sx=i,sy=j;
			if(s[j]=='B') ex=i,ey=j;
			for(res k=0;k<2;k++){
				res nx=i+dx[k],ny=j+dy[k];
				if(nx<1||nx>n||ny<1||ny>m||!id[nx][ny]) continue;
				add(id[i][j],id[nx][ny]),add(id[nx][ny],id[i][j]);
			}
		}
	}
	num=cnt;
	for(res i=1;i<=cnt;i++)
	  if(!dfn[i])
	    tarjan(i,-1);
	l.push(point(sx,sy));
	while(!l.empty()){
		res x=l.front().x,y=l.front().y;
		l.pop();
		for(res i=0;i<4;i++){
			res nx=x+dx[i],ny=y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m||!id[nx][ny]||vis[nx][ny]|(nx==ex&&ny==ey)) continue;
			vis[nx][ny]=1;
			l.push(point(nx,ny));
		}
	}
	memset(f,-1,sizeof(f));
	for(res i=0;i<4;i++){
		res nx=ex+dx[i],ny=ey+dy[i];
		if(nx<1||nx>n||ny<1||ny>n||!vis[nx][ny]) continue;
		f[ex][ey][i]=0;//f[x][y][i]表示x,y由i这个dx,dy转移过来的可行性 
		l.push(point(ex,ey,i));
	}
	memset(vis,0,sizeof(vis));
	vis[ex][ey]=1;
	while(!l.empty()){
		res x=l.front().x,y=l.front().y,op=l.front().op;
		l.pop();
		res nx=x+dx[3-op],ny=y+dy[3-op];
		vis[x][y]=1;
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&id[nx][ny]&&f[nx][ny][op]==-1)
		  f[nx][ny][op]=f[x][y][op]+1,l.push(point(nx,ny,op));
		for(res i=0;i<4;i++){
			if(f[x][y][i]!=-1) continue;
			nx=x+dx[i],ny=y+dy[i];
			if(!id[nx][ny]) continue;
			if(!check(id[nx][ny],id[x+dx[op]][y+dy[op]])) continue;
			f[x][y][i]=f[x][y][op];
			l.push(point(x,y,i));
		}
	}
	for(;q;q--){
		res x=read(),y=read();
		vis[x][y]==1?puts("YES"):puts("NO"); 
	}
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

~~蒟蒻过的第一道黑体耶（~~

## 题意

> 一个人能推动地图中的箱子，当且仅当他在箱子旁边，且箱子在按照人向箱子移动的方向移动一格后不会卡墙里或~~卡进后室~~卡出地图外。
>
> 给定箱子、人的初始坐标和地图和若干次形如 $(x,y)$ 的询问，求箱子能否被移动到 $(x,y)$ 这个坐标上。
>
> 询问与询问互不影响。

## 解法

很显然重点落在箱子而不是人的移动上，但箱子的移动依赖于人的移动，人的移动又受到箱子的阻挡。分析一下箱子对 `Bessie` 移动的影响。

假设地图长这样：

```
0 1 2 3 4 5
1 # . . # #
2 # . B # #
3 . . A . .
4 # # . # #
5 # # . # #
```

其中 `A` 为 `Bessie`，`B` 为箱子。如果 `A` 想从 `B` 的上面把箱子往下推，则必须有一条不经过箱子的路径使得 `A` 到达 $(3,1)$ 且不影响箱子。显然当前图中存在这条路径。

但如果地图长这样：

```
0 1 2 3 4 5
1 # . . # #
2 # . . # #
3 . . A B .
4 # # . # #
5 # # . # #
```

如果 `A` 想从 `B` 的右边把箱子往左推，则没有不经过箱子的路径使 `A` 到达 $(5,3)$。

此时，如果我们把每个不是墙的坐标点看成点，相邻的点连一条双向边，则：如果 `A` 与 `B` 相邻，则想绕到 `B` 的另一面去推动箱子而不使箱子移动，当且仅当**这两个点属于同一个点双中**。

很好理解：对于第一张地图，使 `A` 到达 $(3,1)$ 的路径中有一条经过箱子的路径：
$$
(3,3)\to(3,2)\to(3,1)
$$
也有一条不经过箱子的路径：
$$
(3,3)\to(2,3)\to(2,2)\to(2,1)\to(3,1)
$$
显然由于 $(3,3)$ 和 $(3,1)$ 中有至少两条不经过重复边的路径，所以 $(3,3)$ 和 $(3,1)$ 属于同一个点双。此时即使有箱子阻挡（即一条路径被阻断），`Bessie` 也能够绕到 $(3,1)$ 上（找到另一条路径）把箱子往下推。这满足点双的定义。

所以我们就可以在原图上求出每个点所属的点双。注意割点可能会被多个点双包含。

考虑到我们不关心 `Bessie` 的具体移动，而只有 `Bessie` 在靠近到箱子的四周时才会对箱子的位置造成影响，所以判断状态是否已经入过队，我们只需记录箱子的坐标和 `Bessie` 在箱子的哪一面即可。对于开始时 `Bessie` 不在箱子旁边，可以预处理出 `Bessie` 在不经过箱子的情况下，能到箱子上下左右的哪里。

## 实现

一开始求点双的过程使用 `Tarjan`，注意因为割点可能会被多个点双包含，用一个 `vector` 记录点双编号即可。

预处理 `Bessie` 能到箱子的四周的哪里时，`Dfs` 和 `Bfs` 都可以，注意不能经过箱子。

最后 `Bfs` 的时候，状态 $\{x,y,way\}$ 表示箱子在 $(x,y)$ 上，`Bessie` 在箱子的第 $way$ 面旁边（比如说 $way=0$ 就是上面，$way=1$ 就是左边，但 $0,2$ 和 $1,3$ 的方向要相反，后面会说）。

假设现在箱子在 $(ubx,uby)$ 上，`Bessie` 在 $(ucx,ucy)$ 上，尝试让箱子移动到相邻的格子 $(vbx,vby)$，则此时 `Bessie` 应移到 $(vbx,vby)$ 的对面 $(vcx,vcy)$ 上（比如目标点在当前箱子上面，那 `Bessie` 需要移到箱子的下面去）。判断两者是否被同一个点双包含即可。当然也有 `Bessie` 无需移动的情况，判断两个坐标是否相同即可。

因为码量比较大，代码中会有详细的注释。

## 代码

```cpp
// 先Tarjan求出点双 
// 然后dfs判断人能到哪里
// 最后bfs求解 
#include<bits/stdc++.h>
#define mk make_pair
using namespace std;
const int maxn = 1505;
// 行列上移动的方向，注意要和后面的 dfs 和 bfs 对应。
const int WayX[] = {-1,0,1,0}; 
const int WayY[] = {0,-1,0,1};
int n,m;
char MP[maxn][maxn]; // 原图
int dfn[maxn][maxn],low[maxn][maxn],clo;
vector<int> b[maxn][maxn]; // 每个点被哪些点双包含
int tot; // 存当前点双的编号
pair<int,int> st[maxn * maxn + maxn];  // 注意栈要开 n*n 大小
int top;
int Cx,Cy,Bx,By; // (Cx,Cy) 为 Bessie 的坐标，(Bx,By) 为箱子的坐标。
bool check(int x,int y) { // 判断是否越界/卡墙里
	return x >= 1 && x <= n && y >= 1 && y <= m && MP[x][y] != '#';
}
// 暴力判断两点是否被同一点双包含
bool checkSame(int ux,int uy,int vx,int vy) { 
	for (auto x : b[ux][uy])
		for (auto y : b[vx][vy])
			if (x == y) return true;
	return false;
}
// 求点双
void Tarjan(int ux,int uy,int fx,int fy) {
	dfn[ux][uy] = low[ux][uy] = ++ clo;
	st[++ top] = mk(ux,uy);
	for (int w = 0;w < 4;w ++) {
		int vx = ux + WayX[w], vy = uy + WayY[w]; // 相邻点
		if (!check(vx,vy)) continue;
		if (!dfn[vx][vy]) {
			Tarjan(vx,vy,ux,uy); 
            low[ux][uy] = min(low[ux][uy],low[vx][vy]);
			if (low[vx][vy] >= dfn[ux][uy]) { // 发现割点 (ux,uy)
				b[ux][uy].push_back(++ tot);
				do {
					int x = st[top].first, y = st[top].second;
					b[x][y].push_back(tot);
				} while (st[top --] != mk(vx,vy));
			}
		} else if (vx != fx || vy != fy) 
			low[ux][uy] = min(low[ux][uy],dfn[vx][vy]);
	}
}
bool CanMove[4],DfsVis[maxn][maxn];
// CanMove 分别对应一开始的 WayX 和 WayY
void dfs(int ux,int uy) { // 尝试让 Bessie 去靠近箱子的四周
	if (DfsVis[ux][uy] || (ux == Bx && uy == By)) return ;
    // 更新 CanMove
	CanMove[0] |= (ux == Bx - 1 && uy == By);
	CanMove[1] |= (ux == Bx && uy == By - 1);
	CanMove[2] |= (ux == Bx + 1 && uy == By);
	CanMove[3] |= (ux == Bx && uy == By + 1);
	DfsVis[ux][uy] = true;
	for (int w = 0;w < 4;w ++) {
		int vx = ux + WayX[w], vy = uy + WayY[w];
		if (check(vx,vy)) dfs(vx,vy);
	}
}
int Q;
bool BfsVis[maxn][maxn][4]; // 存状态，上文中提到过。
bool Ans[maxn][maxn]; // 最终答案
// Bfs 队列，前一个 pair 存 Bessie 的坐标，后一个 pair 存箱子的坐标。
queue<pair<pair<int,int>,pair<int,int> > >Que; 
void Bfs() {
	pair<int,int> Box = mk(Bx,By);
    // 对处理出的结果往队列里扔初始的状态
	for (int w = 0;w < 4;w ++) // 也要和 WayX,WayY 对应
		if (BfsVis[Bx][By][w] = CanMove[w]) // 记录状态已入过队
			Que.push(mk(mk(Bx + WayX[w],By + WayY[w]),Box));
//	for (int w = 0;w < 4;w ++)
//		cout << CanMove[w] << '\n';
	while (!Que.empty()) {
		auto Top = Que.front(); Que.pop();
		int ucx = Top.first.first, ucy = Top.first.second; // Bessie 的坐标
		int ubx = Top.second.first, uby = Top.second.second; // 箱子的坐标
		for (int w = 0;w < 4;w ++) {
			int vbx = ubx + WayX[w], vby = uby + WayY[w]; // 箱子的目标位置
			int vcx = ubx + WayX[w ^ 2], vcy = uby + WayY[w ^ 2]; // Bessie 的目标位置
            // 上文中提到 way 和 way + 2 要对应就是因为这个，可以通过与二异或求出对面方向。
			if (!check(vbx,vby) || BfsVis[vbx][vby][w ^ 2]) continue; // 状态已被访问或不合法
			if (vcx == ucx && vcy == ucy || checkSame(vcx,vcy,ucx,ucy)) { // 可以满足
                // 此时 Bessie 由于推了箱子而到了箱子之前的位置 (ubx,uby)。
                // 箱子被推到了 (vbx,vby) 上。
				BfsVis[vbx][vby][w ^ 2] = true;
				Que.push(mk(mk(ubx,uby),mk(vbx,vby)));
			}
		}
	}
	for (int i = 1;i <= n;i ++)
		for (int j = 1;j <= m;j ++) {
			Ans[i][j] = false;
			for (int k = 0;k < 4;k ++)
				Ans[i][j] |= BfsVis[i][j][k]; // 统计答案
		}
			
}
int main() {
	scanf("%d%d%d",&n,&m,&Q);
	for (int i = 1;i <= n;i ++) {
		scanf("%s",MP[i] + 1);
		for (int j = 1;j <= m;j ++) {
			if (MP[i][j] == 'A') Cx = i, Cy = j;
			if (MP[i][j] == 'B') Bx = i, By = j;
		}
	}
	Tarjan(Cx,Cy,0,0);
//	cout << tot << '\n';
	if (!dfn[Bx][By]) { // 本身 Bessie 就摸不到箱子，特判掉。
		for (int i = 1,x,y;i <= Q;i ++) {
			scanf("%d%d",&x,&y);
			if (x == Bx && y == By) puts("YES");
			else puts("NO");
		}
		return 0;
	}
	dfs(Cx,Cy); Bfs();
	for (int i = 1,x,y;i <= Q;i ++) {
		scanf("%d%d",&x,&y);
		if (Ans[x][y]) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

~~**恭喜你解决了一道黑题**:)~~
## Update
修了一下描述中的错误，感谢管理审核:)

---

## 作者：Undead2008 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4082)

发现箱子会挡住路，于是主要的任务变成了判断割掉某个点后，某两个点是否连通。

对网格图建点双圆方树，然后直接判断某个点是否在另外两个点的路径上即可。具体来讲 $L$ 在 $u$ 到 $v$ 的路径上等价于 $L$ 在 $\operatorname{lca}(u,v)$ 的子树中，并且为 $u$ 或 $v$ 的祖先。

这题主要是代码实现恶心，注意几个细节：

- 可以使用 [这道题](https://www.luogu.com.cn/problem/P1979) 的搜索方式
- 注意判 Bessie 和箱子不连通
- 注意圆方树数组开二倍
- 注意要使用空间线性性感树剖
- 注意现在位置和目标位置的区别

```cpp
#include"bits/stdc++.h"
using namespace std;
const int maxn = 1510;
const int maxN = maxn*maxn*2;
int n,m,q,Ic;
char b[maxn][maxn];
bool c[maxn][maxn];
int mv[4]={0,1,0,-1};
struct Pt{int x,y;}A,B;
inline Pt Mv(Pt x,int o){return {x.x+mv[o],x.y+mv[3-o]};}
inline bool cm(Pt x,int o){return c[x.x+mv[o]][x.y+mv[3-o]]^1;}
inline int Gd(Pt x){return (x.x-1)*m+x.y;}
vector<int>e[maxN],E[maxN];
int dfn[maxN],low[maxN],Ts;
stack<int>st;
void Tarjan(int x,int Fa){
    dfn[x]=low[x]=++Ts;st.push(x);
    for(int i=0;i<E[x].size();i++){
        int v=E[x][i],y;
        if(!dfn[v]){
        	Tarjan(v,x);
	        low[x]=min(low[x],low[v]);
			if(dfn[x]<=low[v]){
		        ++Ic;
		        do{
		        	y=st.top();st.pop();
		        	//cout<<y<<' '<<Ic<<endl;
		            e[y].push_back(Ic);
					e[Ic].push_back(y);
		        }while(y!=v);
		        //cout<<x<<' '<<Ic<<endl;
				e[x].push_back(Ic);
				e[Ic].push_back(x);
		    }
		}else if(v!=Fa)low[x]=min(low[x],dfn[v]);
    }
}
int sz[maxN],son[maxN],Top[maxN],fa[maxN],dep[maxN],Dfn[maxN],TIDX;
void dfs1(int p,int Fa){
	sz[p]=1,dep[p]=dep[Fa]+1,fa[p]=Fa;
	for(int i=0;i<e[p].size();i++){
		int to=e[p][i];
		if(to==Fa)continue;
		dfs1(to,p);
		sz[p]+=sz[to];
		if(sz[son[p]]<sz[to])son[p]=to;
	}
}
void dfs2(int p,int Fa){
	Dfn[p]=++TIDX;
	if(son[Fa]==p)Top[p]=Top[Fa];
	else Top[p]=p;
	if(son[p])dfs2(son[p],p);
	for(int i=0;i<e[p].size();i++){
		int to=e[p][i];
		if(to==Fa||to==son[p])continue;
		dfs2(to,p);
	}
}
int Lca(int u,int v){
	while(Top[u]!=Top[v]){
		if(dep[Top[u]]<dep[Top[v]])swap(u,v);
		u=fa[Top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	return u;
}
inline bool Chk(int u,int v){//判断 u 是否在 v 的子树中
	return Dfn[v]<=Dfn[u]&&Dfn[u]<Dfn[v]+sz[v];
}
inline bool Check(int u,int v,int Cut){//切掉 Cut 后，u 和 v 是否不连通
	int Lc=Lca(u,v);//cout<<u<<' '<<v<<' '<<Cut<<' '<<(Chk(Cut,Lc)&&(Chk(u,Cut)||Chk(v,Cut)))<<endl;
	return Chk(Cut,Lc)&&(Chk(u,Cut)||Chk(v,Cut));
}
#define p first
#define dir second
bool vis[maxN][4];
void bfs(){
	queue<pair<Pt,int>>q;
	for(int i=0;i<4;i++)
		if(cm(B,i^2)&&!Check(Gd(A),Gd(Mv(B,i^2)),Gd(B)))
			q.push({B,i});
	while(q.size()){
		auto it=q.front();q.pop();
		if(vis[Gd(it.p)][it.dir])continue;
		//cout<<it.p.x<<' '<<it.p.y<<' '<<Mv(it.p,it.dir).x<<' '<<Mv(it.p,it.dir).y<<endl;
		vis[Gd(it.p)][it.dir]=1;
		if(cm(it.p,it.dir))
			q.push({Mv(it.p,it.dir),it.dir});
		for(int i=0;i<4;i++)if(i!=it.dir)
			if(cm(it.p,i)&&cm(it.p,it.dir^2)&&cm(it.p,i^2)
				&&!Check(Gd(Mv(it.p,i^2)),Gd(Mv(it.p,it.dir^2)),Gd(it.p)))
					q.push({Mv(it.p,i),i});
	}
}
int main(){
	cin>>n>>m>>q;Ic=n*m;
	memset(c,1,sizeof(c));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>b[i][j],c[i][j]=(b[i][j]=='#');
			if(b[i][j]=='A')A={i,j};
			else if(b[i][j]=='B')B={i,j};
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(c[i][j]==0)
			for(int k=0;k<4;k++)
				if(cm({i,j},k))
					E[Gd({i,j})].push_back(Gd(Mv({i,j},k)));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(c[i][j]==0&&!dfn[Gd({i,j})])
				Tarjan(Gd({i,j}),0);
	dfs1(Gd(A),0),dfs2(Gd(A),0);
	//cout<<Check(12,13,27)<<endl;
	//cout<<Check(11,14,33)<<endl;
	//cout<<Check(11,14,29)<<endl;
	if(Dfn[Gd(B)])bfs();
	for(int i=1,R,C;i<=q;i++){
		cin>>R>>C;
		if(R==B.x&&C==B.y)puts("YES");
		else {
			bool flag=0;
			for(int j=0;j<4;j++)
				flag|=vis[Gd({R,C})][j];
			puts(flag?"YES":"NO");
		}
	}
}
```

---

## 作者：Moeebius (赞：0)

题意：推箱子问题。（应该不用多说？

考虑 Bessie 的策略。她一定会：

1. 先从起点出发，到达一个与箱子相邻的点。

2. 将箱子推到终点。

在第 2 步中，注意到 Bessie 只有可能继续将箱子往前推一格，或者转向（即走到另一个与箱子相邻的点）。

将箱子向前推一格是好实现的。

对于转向，考虑将地图「建图」，能否转向的条件就是两个点在「割掉」箱子之后仍然连通。

于是我们就可以跑 $\text{Tarjan}$ 将点双跑出来，然后判断两点是否在一个点双内即可。

最后按照「推一格+转向」再次建图，跑一次搜索，就能找出所有可能的终点。

---

下面是实现的 Tips：

1. 跑 $\text{Tarjan}$ 不需要显式建图。直接在原图上跑 $\text{DFS}$ 即可。（如果您被卡空间了可以看一下）
2. 「转向」连边时不需要把每一个可以到达的点都连一遍，用一个有向环把连通块串起来就行了。
3. 注意 Bessie 需要先走到箱子边上的点。所以开始前还需要找到 Bessie 可以从哪些点开始推箱子。（当然，一种特殊情况是她根本不需要推箱子，这样即使走不到箱子边上也没有关系。）
4. 建议封装一些函数，便于 Debug。

---

感觉是一道与「2023 过河卒」神似的码量题…… OvO

[Code](https://www.luogu.com.cn/paste/gt2ham7w)

---

