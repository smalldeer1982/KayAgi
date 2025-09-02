# [NEERC 2016] Game on Graph

## 题目描述

Gennady 和 Georgiy 在玩一个有向图上的游戏。这个图有 $n$ 个点 $m$ 条边，两人轮流操作，每次可以将棋子沿着其中一条边移动，不能移动者输。

你要对于每个点，分别求出以这个点为起点开始游戏，两人分别作为先手，最终会输，赢，还是平局（游戏无限循环）。

其中，Gennady 因为玩得很开心，所以他更期望将游戏变为平局；Georgiy 还有很多其他事，所以他更期望游戏不要平局。当然，在不平局的基础上，两人都更希望赢。

## 样例 #1

### 输入

```
6 7
1 2
2 1
2 3
1 4
4 1
4 5
5 6
```

### 输出

```
WDLDWL
DWLLWL 
```

# 题解

## 作者：zhylj (赞：14)

也许是个更简洁的做法？

记希望平局玩家的为 A，不希望平局玩家的为 B。

把一个点拆成两个：一个代表此时在这个点且先手是 A，另一个代表先手是 B。不妨称其为 A 类点和 B 类点。

我们考虑如何判断平局：我们已知「出度为 $0$ 的点」代表的状态是不平局，且所有不平局的状态进行下去都必然会在某一刻到达这样的状态。

可以发现，对于 A 类点，只有在其所有出边都是不平局的点时它才会不平局；而对于 B 类点，在它有任意一条边是不平局的点时它就是不平局。于是我们考虑一个做法：从所有出度为 $0$ 的点开始 DFS，当前访问过的节点均为不平局的点。那么，对于假如一个点被访问到，我们就遍历其所有入边对应的点：

- 若其为 A 类点，我们判断其所有边是否都被访问过，若其所有边都被访问过，那么就访问它（类似拓扑排序）。
- 否则其为 B 类点，那么我们可以直接确定其一定为不平局，那么如果它曾经未被访问过，我们就可以直接访问它（类似贪心的思想：我们马上处理它能影响到的点）。

不难证明，如果某一时刻这个操作停止了，那么剩下的点一定是平局的（若不是容易证明其必然被访问过）。

接下来我们考虑如何判断输赢，注意到我们已经确定了「出度为 $0$ 的 A 类点」代表的状态是 B 胜利。我们可以先用上面的 DFS 处理这部分点（即，假装不平局只有这些点），那么此时被访问过的点就是 B 必胜的点了。

时间复杂度 $\mathcal O(n+m)$，代码很简单。

```cpp
const int N = 1e5 + 5;

int n, m, dg[N][2], f[N][2], vis[N][2];
std::vector <int> r_E[N];

void Dfs(int u, int typ) {
	vis[u][typ] = true;
	for(int v : r_E[u]) {
		--dg[v][typ ^ 1];
		if(!typ && !vis[v][1]) Dfs(v, 1);
		if(typ && !dg[v][0]) Dfs(v, 0);
	}
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        r_E[v].push_back(u);
        ++dg[u][0]; ++dg[u][1];
    }
    for(int i = 1; i <= n; ++i)
        if(!dg[i][0] && !vis[i][0])
            Dfs(i, 0);
    memcpy(f, vis, sizeof(f));
    for(int i = 1; i <= n; ++i)
        if(!dg[i][1] && !vis[i][1])
            Dfs(i, 1);
    for(int t = 0; t < 2; ++t) {
        for(int i = 1; i <= n; ++i)
            printf(vis[i][t] ? ((f[i][t] ^ t ^ 1) ? "W" : "L") : "D");
        printf("\n");
    }
	return 0;
}
```


---

## 作者：a___ (赞：5)

首先判断一个状态是否是平局。  
首先显然所有出度为 $0$ 的点都不是平局。由于 Gennady 希望平局，而 Georgiy 希望不要平局，所以对 Gennady 来说只要有一个后继状态是平局它就是平局；对 Georgiy 来说只有所有后继状态都是平局它才是平局。然后在反图上用类似拓扑排序的方式转移。   

然后对于非平局的状态求出胜负——直接做一个普通的博弈转移就好，即只要有一个后继状态必败就必胜；所有后继状态都必胜就必败。   

最后发现还有一些点转移不到。这些点是非平局情况下可致平局的点（在环上）。这些点之所以还不是平局是因为 Georgiy 不希望平局，选择了输。所以特判这些点为 Georgiy 输 Gennady 赢。   

代码如下：   
```cpp
#include<cstdio>
#include<vector>
#include<queue>
const int N=100010;
std::vector<int>g[N],gr[N];
std::queue<std::pair<int,int>>q;
int n,m,drw[N][2],win[N][2],du[N],dt[N],d[N][2];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),
	g[x].push_back(y),gr[y].push_back(x),++du[x];
	for(int i=1;i<=n;i++)
	{
		if(!du[i])q.emplace(i,0),q.emplace(i,1);
		else drw[i][0]=drw[i][1]=1;
		dt[i]=du[i];
	}
	while(!q.empty())
	{
		int u=q.front().first,p=q.front().second;q.pop();
		for(int v:gr[u])
		if((p==0&&drw[v][1])||(p==1&&!--dt[v]))
		drw[v][p^1]=0,q.emplace(v,p^1);
	}
	for(int i=1;i<=n;i++)
	{
		if(!du[i])q.emplace(i,0),q.emplace(i,1);
		else win[i][0]=win[i][1]=-1;
		for(int v:g[i])d[i][0]+=!drw[v][1],d[i][1]+=!drw[v][0];
	}
	while(!q.empty())
	{
		int u=q.front().first,p=q.front().second;q.pop();
		for(int v:gr[u])if(!drw[v][p^1])
		if(win[u][p]){if(!--d[v][p^1])q.emplace(v,p^1),win[v][p^1]=0;}
		else {if(win[v][p^1]==-1)q.emplace(v,p^1),win[v][p^1]=1;}
	}
	for(int i=1;i<=n;i++)(win[i][0]==-1)&&(win[i][0]=1),(win[i][1]==-1)&&(win[i][1]=0);
	for(int i=1;i<=n;i++)putchar(drw[i][0]?'D':(win[i][0]?'W':'L'));putchar('\n');
	for(int i=1;i<=n;i++)putchar(drw[i][1]?'D':(win[i][1]?'W':'L'));putchar('\n');
	return 0;
}
```

---

## 作者：_jimmywang_ (赞：2)

这个题和普通的有向图上博弈不同，加了一个**某一方优先选择平局**的条件，因此看起来很奇怪。

因为双方目标不同，首先可以想到把每个点拆成 $A$ 先手和 $B$ 先手两个点，我们称希望平局的人为 $A$，希望结束的人为 $B$。

为了简化问题，我们先把问题转化为**一方不想游戏结束，另一方想要游戏结束**。这和 [[ABC261Ex] Game on Graph](https://www.luogu.com.cn/problem/AT_abc261_h) 的第一步相似。我们定义 $End_{u,0/1}=0/1$ 表示 $A/B$ 在 $u$ 先手出发后游戏是否结束（0 否 1 是）。那么有：

- 如果存在 $(u,v)\in E$ 使得 $End_{v,0}=1$，那么 $End_{u,1}=1$。反之 $End_{u,1}=0$。

- 如果对于所有 $(u,v)\in E$ 都有 $End_{v,1}=1$，那么 $End_{u,0}=1$。反之 $End_{u,0}=0$。

简单地说，如果 $A$ 先手，只有出边全都能结束时才能结束；如果 $B$ 先手，只要有出边能结束，他就会选择这条边并结束。

$End$ 数组可以反图拓扑递推而得。于是我们得到了哪些点必然导致平局，哪些点必然会结束。

接下来就是确认那些结束点的胜负状态。由于此时两个人都很正常的不想输，那么一个普通的反图拓扑递推就能解决这个问题。具体的，从出度为 0 的点出发拓扑，一路只管能够结束的点进行递推（出边全胜则负，出边可负即胜）即可。

但是此时会有一些点没有被递推到（我称之**状态不确定点**）。这是些什么点呢？那就是：本身能够结束，且出边中只存在**状态不确定点**和必胜点（可能还有平局点，这种情况仅在 $B$ 先手时出现）的点。如何分析这些点的胜负？如下：

如果该**状态不确定点**是 $A$ 先手，那么出边中包含**状态不确定点**和必胜点。其中 $A$ 不想输，所以一定走**状态不确定点**。注意此时这些**状态不确定点**都是确定会让游戏结束的点。

如果该**状态不确定点**是 $B$ 先手，那么出边中包含**状态不确定点**，必胜点和平局点。此时 $B$ 如果再走**状态不确定点**，就和 $A$ 的决策绕起来成环，也就平局了，这是矛盾的。同时为了不平局，$B$ 一定会选择走必胜点，从而该点必败。

此时回头看 $A$ 的决策，我们发现 $A$ 走到下一个**状态不确定点**后，局面是一个是 $B$ 先手的**状态不确定点**，因此 $B$ 必败，相当于 $A$ 必胜。

因此，这些**状态不确定点**中，$A$ 先手的点必胜，$B$ 先手的点必败！

至此此题结束。

---

## 作者：Caiest_Oier (赞：2)

# [P6970](https://www.luogu.com.cn/problem/P6970)    

首先计算平局和非平局的情况。对于一个出度为 $0$ 的点，其必为非平局。具体而言，令 $f_i$ 表示 Gennady 在 $i$ 点执先手是否平局，$g_i$ 表示 Georgiy 在 $i$ 点执先手是否平局，则如果对于所有的 $v\in E_i$，$g_v$ 都是非平局，则 $f_i$ 非平局，如果存在一个 $v\in E_i$，$f_v$ 是非平局，则 $g_i$ 是非平局。按反图拓扑跑一边，找到非平局的 $f$ 与 $g$，则剩余的 $f$ 与 $g$ 都是平局。原因很明显，不妨把注意力放到剩余点集上，则对于任一点和任意先手均满足，要么想到达非剩余点但下一步只能继续走到剩余点集中的点，要么不想到达非剩余点而且有路可以走向剩余点，于是就在剩余点里一直走下去了（注意，这里使用的是“非剩余点”而非“非平局点”，所以可以根据转移的定义来推导）。    

于是我们判出了非平局和平局，则剩下的就好判了，对于出度为 $0$ 的点，二者均必输，反图拓扑，对非平局点转移下去就可以了。不过，因为转移的方式有所不同，所以非平局点有一些是转移不到的。这些转移不到的点有个特性，就是他们之间由交替先后手构成了若干个环（具体参照样例中 $1$ 先手和 $4$ 后手的关系），而这个现象的原因在于我们让二者都不想输，但他们可以走平局（注意，这里将输赢优先级提高，所以对于 Georgiy 而言，他的行为与之前发生了矛盾）。而我们如果要让 Georgiy 按照不想平局的行为模式走下去，则他是必输的，另外一个人必赢。所以对于所有转移不到的点，如果是先手则必赢，后手必输。就做完了。     

代码（有点难看）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,cd[500003],cd2[500003],f[500003],g[500003];
vector<int>E[500003],E2[500003];
int Q[1000003][2],totQ;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&k1,&k2);
		E[k1].emplace_back(k2);
		E2[k2].emplace_back(k1);
		cd[k1]++;
	}
	memset(f,-1,sizeof(f));
	memset(g,-1,sizeof(g));
	for(int i=1;i<=n;i++){
		if(cd[i]==0){
			f[i]=g[i]=1;
			Q[++totQ][0]=i;
			Q[totQ][1]=1;
			Q[++totQ][0]=i;
			Q[totQ][1]=2;
		}
	}
	for(int i=1;i<=totQ;i++){
		for(auto j:E2[Q[i][0]]){
			if(Q[i][1]==1){
				if(g[j]==-1){
					g[j]=1;
					Q[++totQ][0]=j;
					Q[totQ][1]=2;
				}
			}
			else{
				cd[j]--;
				if(cd[j]==0){
					f[j]=1;
					Q[++totQ][0]=j;
					Q[totQ][1]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		cd[i]=cd2[i]=0;
		for(auto j:E[i]){
			if(f[j]!=-1)cd[i]++;
			if(g[j]!=-1)cd2[i]++;
		}
	}
	totQ=0;
	for(int i=1;i<=n;i++){
		if(f[i]!=-1)f[i]=0;
		if(g[i]!=-1)g[i]=0;
		if(E[i].size()==0){
			f[i]=g[i]=2;
			Q[++totQ][0]=i;
			Q[totQ][1]=1;
			Q[++totQ][0]=i;
			Q[totQ][1]=2;
		}
	}
	for(int i=1;i<=totQ;i++){
		for(auto j:E2[Q[i][0]]){
			if(Q[i][1]==1){
				if(g[j]==-1)continue;
				if(f[Q[i][0]]==2){
					if(g[j]==0){
						g[j]=1;
						Q[++totQ][0]=j;
						Q[totQ][1]=2;
					}
				}
				else{
					cd[j]--;
					if(cd[j]==0){
						g[j]=2;
						Q[++totQ][0]=j;
						Q[totQ][1]=2;
					}
				}
			}
			else{
				if(f[j]==-1)continue;
				if(g[Q[i][0]]==2){
					if(f[j]==0){
						f[j]=1;
						Q[++totQ][0]=j;
						Q[totQ][1]=1;
					}
				}
				else{
					cd2[j]--;
					if(cd2[j]==0){
						f[j]=2;
						Q[++totQ][0]=j;
						Q[totQ][1]=1;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(f[i]==0)printf("W");
		if(f[i]==-1)printf("D");
		if(f[i]==2)printf("L");
		if(f[i]==1)printf("W");
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		if(g[i]==0)printf("L");
		if(g[i]==-1)printf("D");
		if(g[i]==2)printf("L");
		if(g[i]==1)printf("W");
	}
	return 0;
}
```


---

## 作者：yijan (赞：1)

一道很有意思的题，我也不知道这个题解是否写清楚了。。

设 A 是 Gennady ， B 是 Georgiy 。

首先考虑如何找出所有会使游戏无限进行下去的点。这种点分为两种，一种是从这个点，A 先手出发，就会导致最终平局，还有一种是 B 先手出发却会导致不得不平局。

首先考虑所有出度为 $0$ 的点，显然不管谁从这个点先手，游戏都会结束。

由于 A 的决策是尽量平局，所以一个点 A 出发无法平局当且仅当它的所有后继点都是 B 出发会导致不平局的情况。

由于 B 的决策是尽量不平局，所以一个点 B 如果所有后继点中有一个点 A 出发无法平局，那么这个点也是无法平局的。

于是我们可以类似拓扑序来转移。但是这样会导致有些点转移不到。显然这种到不了的点都是不得不平局的点。

然后考虑已经判断出了所有点是否是 A / B 先手必然平局。那么如何得到答案呢？

我们考虑一个点它是否是 A 先手不得不败的，以及一个点是否是 B 先手必胜的。首先我们丢掉所有平局点的情况，然后所有无出度的点都是 A 先手不得不败的。然后这两个状态也可以类似平局互相推出。最后无法被转移到的点，就意味着这些点既不能成为平局点或者被迫平局，也不能决定出 B 的胜利，那么唯一的可能就是它们在一个类似强连通的结构上，在其中某个状态下 B 其实可以走到一个必败点。事实上 B 无法胜利，它并不会愿意游戏无限进行，所以一定会选择自己走到失败点，于是这些无法被转移到的点的状态一定是 A 胜利、B 失败。

复杂度 $O(n+m)$ 。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , m;
int A[MAXN];

vi G[MAXN] , Gr[MAXN];
int deg[MAXN] , td[MAXN];
int dw[MAXN][2] , sw[MAXN][2];
queue<pii> Q;

void solve() {
	cin >> n >> m;
	rep( i , 1 , m ) {
		int u , v;
		scanf("%d%d",&u,&v);
		G[u].pb( v ) , Gr[v].pb( u );
		++ deg[u];
	}
	rep( i , 1 , n ) {
		if( !deg[i] ) {
			dw[i][0] = dw[i][1] = 1;
			Q.emplace( i , 0 ) , Q.emplace( i , 1 );
		}
		td[i] = deg[i];
	}
	while( !Q.empty() ) {
		int u = Q.front().fi , w = Q.front().se; Q.pop();
		for( int v : Gr[u] ) {
			if( w == 0 && !dw[v][1] ) {
				dw[v][1] = 1;
				Q.emplace( v , 1 );
			} else if( w == 1 ) {
				-- td[v];
				if( !td[v] )
					Q.emplace( v , 0 ) , dw[v][0] = 1;
			}
		}
	}
	rep( i , 1 , n ) {
		if( !deg[i] ) {
			sw[i][0] = 1;
			Q.emplace( i , 0 );
		}
		if( !dw[i][0] ) sw[i][0] = -1;
		if( !dw[i][1] ) sw[i][1] = -1;
		td[i] = deg[i];
	}
	while( !Q.empty() ) {
		int u = Q.front().fi , w = Q.front().se; Q.pop();
		for( int v : Gr[u] ) {
			if( w == 0 && !sw[v][1] ) {
				sw[v][1] = 1;
				Q.emplace( v , 1 );
			} else if( w == 1 && !sw[v][0] ) {
				-- td[v];
				if( !td[v] )
					Q.emplace( v , 0 ) , sw[v][0] = 1;
			}
		}
	}
	
	rep( i , 1 , n ) {
		if( !dw[i][0] ) putchar('D');
		else if( !sw[i][0] ) putchar('W');
		else putchar('L');
	}
	puts("");
	rep( i , 1 , n ) {
		if( sw[i][1] > 0 ) putchar('W');
		else if( dw[i][1] ) putchar('L');
		else putchar('D');
	}
	puts("");
}

signed main() {
	freopen("game.in","r",stdin) , freopen("game.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}

```



---

## 作者：OtterZ (赞：0)

# 题意
给定 $n$ 个点 $m$ 条边的有向图，`Gennady` 和 `Georgiy` 两个玩家玩棋子移动游戏，若一个玩家无法操作则输。两个玩家都希望赢，相比之下，`Gennady` 更希望无限循环，而 `Georgiy` 更希望游戏次数有限，问不同的玩家先后和棋子起点下的结果。
# 转化
我们发现分析这三种情况比较困难，相比之下，对于数大小的博弈则更好做，加上次数有限的结果比无限的结果更好处理，我们加入一个人，也就是老板 `Otter`，他会干下列的事情：

1. 如果 `Georgiy` 赢了， `Otter` 会奖励他 $2$ 年长假。
2. 如果 `Georgiy` 输了， `Otter` 因特殊原因会给他 $1$ 年长假。
3. 如果游戏无限循环，`Otter` 啥都做不了，不会给假期。

这样就变成了：

- `Georgiy` 希望获得更长的假期；
- `Gennady` 希望 `Georgiy` 的假期尽可能短。

接下来就方便操作了。
# 博弈

我们先确定 `Georgiy` 有 $2$ 年假期的情况，再确定 $1$ 年假期的情况，余下的就是没假期的情况。

对于没有出度的点：

- 如果此时轮到 `Gennady`，那么他输了，`Georgiy` 将有 $2$ 年假期；
- 轮到 `Georgiy`，那么他会有 $1$ 年假期。

我们从一个确定的情况反推，也就是对于一个点的状态通过入边到上一个点对应的状态，得到：

- 如果在上一个点时轮到 `Georgiy`，走到这个点对他来说最好，他会直接选择这个点。
- 但如果是轮到 `Gennady`，走到这个点对他最不利，那么除非他无路可走，否则一定不走这个点。

我们用用队列存储以确定但没有进行往回推的状态，每次取出队首通过回边扩展，用数组 $c_i$ 记录轮到 `Gennady` 时还有几种选择，就可以 $\operatorname{O}(n + m)$ 的解决这个问题了。

# 代码


```cpp
/*
Change status to value
Value =2 when Georgiy win,=1 when Gennady wins,=0 when draw
Then we can say that Georgiy wants the maxinum score,while Gennady wants the mininum.
These makes the problem easier.
*/
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int n,m,a,b;
vector<int>e[100009];
int d[100009],pd[100009],dp[100009][2];//0 for Gennady,1 for the other
bool vis[100009][2];
char p[2][3] = {{'D','W','L'},{'D','L','W'}};
queue<int>qx,qy;
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= m; i ++){
		scanf("%d %d",&a,&b);
		d[a] ++;
		e[b].push_back(a);
		pd[a] ++;
	}
	//status 2
	for(int i = 1; i <= n; i ++){
		if(pd[i] == 0){
			dp[i][0] = 2;
			qx.push(i);
			qy.push(0);
		}
	}
	while(!qx.empty()){
		int dx = qx.front(),dy = qy.front();
		qx.pop(),qy.pop();
		if(vis[dx][dy])
			continue;
		vis[dx][dy] = true;
		for(int i = 0; i < e[dx].size(); i ++){
			int tx = e[dx][i],ty = dy ^ 1;
			if(ty == 1){
				if(dp[tx][1] < 2){
					dp[tx][1] = 2;
					qx.push(tx),qy.push(ty);
				}
			}
			else{
				d[tx] --;
				if(d[tx] == 0){//have to choose this
					dp[tx][0] = 2;
					qx.push(tx),qy.push(ty);
				}
			}
		}
	}
	//status 1
	for(int i = 1; i <= n; i ++){
		if(pd[i] == 0){
			dp[i][1] = 1;
			qx.push(i);
			qy.push(1);
		}
	}
	while(!qx.empty()){
		int dx = qx.front(),dy = qy.front();
		qx.pop(),qy.pop();
		if(vis[dx][dy])
			continue;
		vis[dx][dy] = true;
		for(int i = 0; i < e[dx].size(); i ++){
			int tx = e[dx][i],ty = dy ^ 1;
			if(ty == 1){
				if(dp[tx][1] < 1){
					dp[tx][1] = 1;
					qx.push(tx),qy.push(ty);
				}
			}
			else{
				d[tx] --;
				if(d[tx] == 0){//have to choose this
					dp[tx][0] = 1;
					qx.push(tx),qy.push(ty);
				}
			}
		}
	}
	//All the status couldn't update is 0
	for(int i = 1; i <= n; i ++)
		putchar(p[0][dp[i][0]]);
	puts("");
	for(int i = 1; i <= n; i ++)
		putchar(p[1][dp[i][1]]);
	puts("");
}
```

---

