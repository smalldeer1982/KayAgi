# Sleepy Game

## 题目描述

Petya and Vasya arranged a game. The game runs by the following rules. Players have a directed graph consisting of $ n $ vertices and $ m $ edges. One of the vertices contains a chip. Initially the chip is located at vertex $ s $ . Players take turns moving the chip along some edge of the graph. Petya goes first. Player who can't move the chip loses. If the game lasts for $ 10^{6} $ turns the draw is announced.

Vasya was performing big laboratory work in "Spelling and parts of speech" at night before the game, so he fell asleep at the very beginning of the game. Petya decided to take the advantage of this situation and make both Petya's and Vasya's moves.

Your task is to help Petya find out if he can win the game or at least draw a tie.

## 说明/提示

In the first example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/933142db306dc9f63dae26cdeb8c3bafdfa66ba8.png)Initially the chip is located at vertex $ 1 $ . In the first move Petya moves the chip to vertex $ 2 $ , after that he moves it to vertex $ 4 $ for Vasya. After that he moves to vertex $ 5 $ . Now it is Vasya's turn and there is no possible move, so Petya wins.

In the second example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/8e2fea186d4a4262837a056dce297e786dfbf02f.png)Initially the chip is located at vertex $ 2 $ . The only possible Petya's move is to go to vertex $ 1 $ . After that he has to go to $ 3 $ for Vasya. Now it's Petya's turn but he has no possible move, so Petya loses.

In the third example the graph is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936B/100651d77b5f87ec828b8f8f5fba499fe3f37744.png)Petya can't win, but he can move along the cycle, so the players will draw a tie.

## 样例 #1

### 输入

```
5 6
2 2 3
2 4 5
1 4
1 5
0
1
```

### 输出

```
Win
1 2 4 5 
```

## 样例 #2

### 输入

```
3 2
1 3
1 1
0
2
```

### 输出

```
Lose
```

## 样例 #3

### 输入

```
2 2
1 2
1 1
1
```

### 输出

```
Draw
```

# 题解

## 作者：ysner (赞：3)

这道题看起来简单，实际上有很多细节。

从题意上看，似乎就是找一个离出发点距离为奇数并且出度为0的点，直接DFS似乎没有什么问题。

但是不然，考虑到图中可能有奇环改变 到某点时距离的奇偶性，我们在跑dfs弄vis判重时要区分 当时步数是奇是偶，即vis[u][0/1]表示dfs到过 到点u时步数为奇/偶的情况。

当判断完Win的情况后，再看还有没有draw的情况（即判环），**只从起点出发Tarjan一遍即可**。

最后就是Lose了。
```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define ll long long
#define il inline
#define re register
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int N=1e5+100;
int n,h[N],cnt,m,vis[N][2],st,len[N],f=0,top,chu[N],dfn[N],low[N],tim,inq[N],scc,Stack[N],t[N],mx;
struct Edge
{
    int to,next;
}e[N<<1];
il void add(re int u,re int v)
{
  e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
}
il void Tarjan(re int u)//找环模板。。。
{
  dfn[u]=low[u]=++tim;
  Stack[++top]=u;
  inq[u]=1;
  for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
      else if(inq[v]) low[u]=min(low[u],dfn[v]);
    }
  if(low[u]==dfn[u])
    {
      ++scc;
      while(Stack[top]^u)
	{
	  inq[Stack[top]]=0;
	  t[scc]++;--top;
	}
      inq[u]=0;--top;
      t[scc]++;mx=max(mx,t[scc]);
    }
}
il void dfs(re int u,re int mk)//mk标奇偶
{
    for(re int i=h[u];i;i=e[i].next)
    {
      re int v=e[i].to;
      if(vis[v][mk^1]) continue;//一定注意判断一点是否走过要分奇偶！！！因有奇环
      vis[v][mk^1]=1;
      len[++top]=v;//存路径
      if(!mk&&!chu[v]){printf("Win\n");fp(i,0,top) printf("%d ",len[i]);exit(0);}//若到该点步数为奇且无出度
      dfs(v,mk^1);
      --top;
    }
}
il int gi()
{
    re int x=0,t=1;
    re char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*t;
}
int main()
{
    n=gi();m=gi();
    fp(i,1,n)
    {
        chu[i]=gi();
        fp(j,1,chu[i]) add(i,gi());
    }
    len[0]=gi();
    dfs(len[0],0);top=0;
    Tarjan(len[0]);//看从起点出发能不能找到环
    if(mx>1) {puts("Draw");return 0;}
    puts("Lose");
    return 0;
}

```

---

## 作者：Overstars (赞：2)

一道一波三折的题，刚读着有点懵，读完发现其实是个披着博弈皮的图论题。

于是可以得到如下题意：
### 题意
有向图上指定一个起点$s$，若存在一条到叶子距离为奇数的路径（注意这里的路径不一定是最短路径），则必胜。

若不存在，但是可以到达一个回路，则可以平局。

上述两种都不能达到，则失败。

~~诶好像有点裸啊，跳了跳了~~
### 思路
正准备跳了这题的时候，忽然想到存在**起点->回路->叶子**的情况，并没有看上去那么好写。

#### Win
这里可以开一个二维$bool$数组$vis$，$vis[x][0]=true$表示节点$x$可以在偶数步时访问到，$vis[x][1]=true$表示节点$x$可以在奇数步时访问到，由此用来$dfs$剪枝。

在$dfs$时若在奇数步时访问到了一个叶子节点，则是必胜的，$dfs$时开一个栈即可记录路径，我这里使用了双端链表的$STL$。

#### Draw
如果并没有在奇数步时访问到一个叶子，那么就要看在$s$出发时能不能找到一个回路，以期达到平局。

而确定$s$是否能达到一个回路，同样可以在同一个$dfs$内确定。


![](http://images2015.cnblogs.com/blog/638419/201511/638419-20151128184040687-313147708.png)

在以$s$为根的$dfs$树上，出现回路与出现后向边（返祖边）等价，所以只要确定有没有返祖边即可。

设$vis2[x]=0$为节点$x$还没访问到，$vis2[x]=1$为节点$x$访问到了但子树未访问完，$vis2[x]=2$为节点$x$访问到了且子树节点全部访问。

所以在$dfs$过程中，若下一步所达节点$v$的$vis2[v]=1$，说明这条边指向了祖先节点，即存在回路。
#### Lose
上述两种情况都没有，就是Lose。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
const int maxn=2e5+10,inf=0x3f3f3f3f,mod=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
int pre[maxn][2],ok=0,tar=0,vv[maxn];
bool vis[maxn][2];
list<int>ans;
vector<int>G[maxn];
void dfs(int x,bool sta)
{
	if(vis[x][sta]||ok==2)
		return;
	ans.push_back(x);
	vv[x]=1;
	vis[x][sta]=1;
	for(int &v:G[x])
	{
		if(vv[v]==1)//有返祖边,即有环
			ok=max(ok,1);
		if(vis[v][!sta])//奇偶性不同
			continue;
		if(G[v].size()==0&&!sta&&ok!=2)//奇数,且无出边,之前未输出答案
		{
			ok=2;
			ans.push_back(v);
		}
		dfs(v,!sta);
	}
	if(ok!=2)
		ans.pop_back();
	vv[x]=2;
}
signed main(signed argc, char const *argv[])
{
	std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,m,s;
	cin>>n>>m;
	for(int i=1,c,v;i<=n;i++)
	{
		cin>>c;
		for(int j=1;j<=c;j++)
		{
			cin>>v;
			G[i].push_back(v);
		}
	}
	cin>>s;
	dfs(s,0);
	if(ok==2)
	{
		cout<<"Win"<<endl;
		for(int &i:ans)
			cout<<i<<' ';
	}
	else if(ok==1)
		cout<<"Draw"<<endl;
	else if(ok==0)
		cout<<"Lose"<<endl;
	return 0;
}
```

---

## 作者：YFF1 (赞：1)

## 思路
看上去像博弈论，实际上只是一个图论题。

使用深度优先搜索，每次记录能否从起点走奇数步来到终点并且记录路径。不会超时，因为有剪枝，相当于每条边只遍历了一次。

期间为了避免超时，每走一步记录一下是否可以通过奇数步或者偶数步走到这个点，因为每一个点的步数都是从上一个点推来的。

如果没有这种方案就寻找有没有环使得平局，用普通的搜就可以，最后输出不行。总体来说并没有什么太过高大上的算法。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k[200005],x,rd[200005],cd[200005],s,t,a[200005],dp[200005][5],cnt=0,use[200005];
vector<int>g[200005],v[200005];
bool f=0;
void check(int u){
	use[u]=1;
	for(int i:g[u]){
		if(use[i]==1){
			f=1;
			return ;
		}
		if(use[i]==0)check(i);
	}
	use[u]=2;
}//一个普通的dfs判环
void dfs(int x,int f){
    for(int i:g[x]){
      	if(dp[i][(f+1)%2])continue;
      	dp[i][(f+1)%2]=1;//记录能否通过奇数步或偶数步走到当前节点
      	a[++cnt]=i;//记录路径
      	if(!f&&!k[i]){
	  		cout<<"Win"<<endl;
	  		for(int j=0;j<=cnt;j++)printf("%d ",a[j]);
	  		exit(0);
	  	}
      	dfs(i,(f+1)%2);//另外一种情况
      	--cnt;//dfs要回溯
    }
}
signed main () {
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%lld",&k[i]);
		for(int j=1;j<=k[i];j++){
			scanf("%lld",&x);
			g[i].push_back(x);
		}
	}
	cin>>s;
	a[0]=s;
	dfs(s,0);
	check(s);
	if(f==1)cout<<"Draw";//分类讨论
	else cout<<"Lose";
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：1)

秒杀了，对于 2100 的评分来说有失水准。

首先考虑如何判断 Win。

直接在图上进行 dfs，每次存一下到此处的路径和到这所花费的移动路径长度。若当前到达的节点为叶子节点，且移动路径长度为奇数，则可以直接输出结果。

一个细节是，若当前的节点已被访问过，但是原来访问到这的奇偶性与当前不同，则说明出现了奇环，需重新访问该节点。

对于判断 Draw，首先进行 tarjan 缩点，建出缩点后的图，记录一下每个强连通分量内的点数，从 s 位于的强连通分量开始遍历，若遍历到点数大于一的强连通分量，输出 Draw。

否则输出 Lose。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=1e5+10;
const int Maxm=2e5+10;
int head[Maxn],tot;
int n,m;
struct Edge{
	int to;
	int nxt;
}E[Maxn<<1];
void addedge(int u,int v)
{
	tot++;
	E[tot].to=v;
	E[tot].nxt=head[u];
	head[u]=tot;
}
int dist[Maxn][2];
vector<int> ans;
int out[Maxn];

void dfs1(int u,int tag)
{
	dist[u][tag]=1;
	ans.push_back(u);
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].to;
		if(dist[v][tag^1]==1) continue;
		if(out[v]==0 && tag==0)
		{
			printf("Win\n");
			for(int i=0;i<ans.size();i++)
			{
				printf("%d ",ans[i]);
			}
			printf("%d\n",v);
			exit(0);
		}
		dfs1(v,tag^1);
	}
	ans.pop_back();
}
int low[Maxn],dfn[Maxn],dfsTime;
stack<int> st;
bool vis[Maxn];
int col[Maxn],siz[Maxn];
int scc_cnt;
void tarjan(int u)
{
	low[u]=dfn[u]=++dfsTime;
	st.push(u);
	vis[u]=1;
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	
	if(dfn[u]==low[u])
	{
		int v;
		scc_cnt++;
		while(v=st.top())
		{
			st.pop();
			col[v]=scc_cnt;
			vis[v]=0;
			if(u==v) break;
		}
	}
}
struct Edges{
	int u,v;
};
vector<Edges> ed;
vector<int> G[Maxn];
void dfs2(int u)
{
	if(siz[u]>1)
	{
		puts("Draw");
		exit(0);
	}
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		dfs2(v);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int c;
		scanf("%d",&c);
		for(int j=1;j<=c;j++)
		{
			int v;
			scanf("%d",&v);
			ed.push_back((Edges){i,v});
			addedge(i,v);
			out[i]++;
		}
	}
	int s;
	scanf("%d",&s);
	dfs1(s,0);
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
	
	for(int i=0;i<ed.size();i++)
	{
		int u=ed[i].u,v=ed[i].v;
		if(col[u]!=col[v])
		{
//			cout<<col[u]<<"->"<<col[v]<<endl;
			G[col[u]].push_back(col[v]);
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		siz[col[i]]++;
	}
	
	dfs2(col[s]);
	
	puts("Lose");
	return 0;
}

```

---

## 作者：Suzt_ilymtics (赞：1)



[题目传送](https://www.luogu.com.cn/problem/CF936B)

[更棒的阅读体验？](https://www.cnblogs.com/Silymtics/p/solution-CF936B.html)

### Solution

题意非常的简单，没啥可说的。

先判断 `Win` 的情况：

你考虑用 $f_{u,0/1}$ 来表示走到 $u$ 这个点走了偶（奇）步这个状态有没有出现过。

对于边 $(u,v)$，显然有转移方程：

$$f_{v,0} |= f_{u,1}$$

$$f_{v,1} |= f_{u,0}$$

然后你在记录一个出度。

这样的话，`dfs` 更新一遍，最后看一看出度为 $0$ 的点走了奇步这个状态存在没有。

题目要求输出路径，这个操作比较平凡，记录一个 $pre$ 递归输出即可。

再考虑判断 `Draw` 的情况。

我们要注意的是 `Draw` 的优先级比 `Lose` 要高。~~估计就我一个人没看出来。~~

所以在不能走奇步停止的情况下，能进圈就进圈。

一开始我的想法是用 `tarjan` 缩点，建出新图，接着从 $s$ 所在点 `dfs`，看看经过的路径有没有环。但是我写挂了。

考虑另外一种更简单的做法，只从 $s$ 跑 `tarjan`，记录下缩的最大环。

直接根据这个最大环的大小来判断就可以了。

其他问题看代码。

### Code

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct edge {
    int from, to, nxt;
}e[MAXN << 1];
int head[MAXN], num_edge = 1;

int n, m, s, cnt = 0, t = 0, Max = 0;
int od[MAXN];
int pre[MAXN][2];
int dfn[MAXN], low[MAXN], siz[MAXN], num[MAXN], stc[MAXN], sc = 0;
bool f[MAXN][2], vis[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

void add_edge(int from, int to) { e[++num_edge] = (edge){from, to, head[from]}, head[from] = num_edge; }

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt, vis[u] = true, stc[++sc] = u;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int cnt = 0;
        int pre = stc[sc--]; vis[pre] = false;
        ++cnt;
        while(pre != u) {
            pre = stc[sc--], vis[pre] = false;
            ++cnt;
        }
        Max = max(Max, cnt);
    }
}

void Dfs(int u) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, flag = false;
        if(!f[v][0] && f[u][1]) f[v][0] = true, flag = true, pre[v][0] = u;
        if(!f[v][1] && f[u][0]) f[v][1] = true, flag = true, pre[v][1] = u;
        if(flag) Dfs(v);
    }
}

void Print(int u, int p) {
    if(pre[u][p]) Print(pre[u][p], p^1);
    printf("%d ", u);
}

int main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
	    int k = read();
	    for(int j = 1, v; j <= k; ++j) {
	        v = read();
	        add_edge(i, v);
	        od[i]++;
        }
    }
    s = read();
    f[s][0] = true;
    Dfs(s);
    bool flag = false;
    for(int i = 1; i <= n; ++i) {
        if(!od[i] && f[i][1]) {
            puts("Win");
            Print(i, 1);
            puts("");
            return 0;
        }
    }
    tarjan(s);
    if(Max > 1) puts("Draw");
    else puts("Lose");
    return 0;
}

```

---

## 作者：hater (赞：0)

tarjan都出来应该是写烦~~傻~~了 

直接dfs即可 

每个位置显然可以分为两种状态 

一种走了奇数步 一种走了偶数步 

vis记录每个位置的状态 pre记录一下前驱 

In表示这个位置是否在栈中 用于判断它是否在环内 

如果有一个位置可以奇数步到达 且无出度 就递归输出路径 

如果没有一个满足条件的位置 且s在一个环内 就平局 

否则失败 

最后值得注意的是 

递归输出路径时 碰到s 还要判断状态是否为开始状态 

因为从s开始可以在某个环上绕一圈 再走 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
using namespace std ; 
const int N = 1e5+10 ; 
vector <int> v[N] ; 
bool vis[N][2] , In[N] , can[N] , flag ;   
int pre[N][2] , n , s , m ; 
void dfs( int x , int k ) { 
  if( In[x] ) { flag = 1 ; } 
  if( vis[x][k] ) return ; 
  vis[x][k] = 1 ; In[x] = 1 ; 
  int l = v[x].size( ) - 1 , y ; 
  fp( i , 0 , l ) { 
     y = v[x][i] ; 
     if( !vis[y][k^1] ) pre[y][k^1] = x ; 
     dfs( y , k^1 ) ; 
  } In[x] = 0 ; 
} 
void print( int x , int k ) { 
   if( x == s && k == 1 )  { printf( "%d " , s ) ; return ; } 
   print( pre[x][k] , k^1 ) ; printf( "%d " , x ) ; }  
signed main( ) {  
  int ti , y ; 
   scanf( "%d %d" , &n , &m ) ; 
   fp( i , 1 , n ) { 
     scanf( "%d" , &ti ) ; 
     if( !ti ) can[i] = 1 ; 
     fp( j , 1 , ti ) 
	   scanf( "%d" , &y ) , v[i].push_back(y) ;  
   }   
   scanf( "%d" , &s ) ; 
   dfs( s , 1 ) ; 
   fp( i , 1 , n ) 
     if( can[i] && vis[i][0] ) { printf( "Win\n" ) ;  print( i , 0 ) ; return 0 ; } 
	if( flag ) printf( "Draw\n" ) ; 
      else printf( "Lose\n" ) ;  
   return 0 ; 
} 
```


---

## 作者：water_tomato (赞：0)

~~这题搞了好久才搞过~~
## 题意
详见[题干](https://www.luogu.com.cn/problem/CF936B)

注意，如果他**有一种方案能够满足 "Win" 的条件，这时即使有环，结果仍然为 "Win"** 。
## 解析
题目要求判断从起点走若干奇数步数能否到达一个无法走的点，即**没有出度**的点。因此我们只需要先标记下没有出度的点，再从起点开始 dfs ，判断有没有一次走到没有出度的点时步数为奇数步即可。

然而具体 dfs 的实现没有这么简单。首先，同一个点可能**既可以奇数步到达，也可以偶数步到达**，因此，我们需要用一个 $tag_{0/1}$ 数组记录，用 $0$ 表示该点能够用偶数步到达，用 $1$ 表示该点能够用奇数步到达。显然，起点是 $0$ 步，为偶数。

然后搜索时为了防止被环卡死以及浪费时间的情况，我们需要及时停止走重复的路线。容易知道，若**下一个点与当前点奇偶性不同的情况**已经被走过，我们就没有必要走了。

这样我们可以判断出 "Win" 的情况，那么在 "Win" 不成立时，我们只需要从起点跑一遍 tarjan 判断有无环即可。有即为 "Draw" ，反之为 "Lose"。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=2e5+5;
struct edge{
	int to,next;
}e[M];
int n,m,cnt,head[N],st;
int chu[N],ans[N],len;
bool tag[N][3],win;
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
inline void dfs(int u,int check){//check ：0 偶数，1 奇数 
	tag[u][check]=true;
	ans[++len]=u;
	if(win) return;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(tag[v][check^1]) continue;//若下一个点与当前点奇偶性不同的情况已经被走过 
		if(!chu[v]&&(!check)){//若走到没有出度的点时步数为奇数步
			win=true;
			printf("Win\n");
			for(int j=1;j<=len;j++){
				printf("%d ",ans[j]);
			}	
			printf("%d",v);
		}
		dfs(v,check^1); 
		if(win) return;
	}
	len--;
}
int dfn[N],low[N],tot,cot;
bool insta[N],draw;
stack<int> s;
inline void paint(int u){
	s.pop();
	insta[u]=false;
}
inline void tarjan(int u){
	dfn[u]=low[u]=++tot;
	s.push(u);
	insta[u]=true;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(insta[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		cot++;
		int CNT=1;
		while(s.top()!=u){
			paint(s.top());
			CNT++;
		}
		paint(u);
		if(CNT>=2) draw=true; 
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,k;i<=n;i++){
		scanf("%d",&k);
		chu[i]=k;
		for(int j=1,x;j<=k;j++){
			scanf("%d",&x);
			add(i,x);
		}
	}
	scanf("%d",&st);
	dfs(st,0);//标记奇偶 
	if(win)
		return 0;
	else{
		tarjan(st);//找环 
		if(draw){
			printf("Draw");
		}
		else printf("Lose");
	}
	return 0;
}
```


---

