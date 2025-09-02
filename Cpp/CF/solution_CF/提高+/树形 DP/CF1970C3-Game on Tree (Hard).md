# Game on Tree (Hard)

## 题目描述

这是该问题的困难版本。此版本与简单版本的唯一区别在于 $ t $ 的约束条件。

Ron 和 Hermione 正在一棵有 $ n $ 个结点的树上玩游戏，所有结点初始均为未激活。游戏共进行 $ t $ 轮，每一轮开始时，恰好有一个结点上放置了一块石头，该结点被视为已激活。每一步操作可以选择石头所在结点的一个未激活的邻居，并将石头移动到该邻居上（从而激活该邻居）。Ron 先手，之后两人轮流操作，直到无法进行有效操作为止。无法行动的一方输掉本轮。如果双方都采取最优策略，每轮游戏谁会获胜？

注意，所有轮次都在同一棵树上进行，仅起始结点不同。此外，每轮结束后，所有已激活结点都会重新变为未激活。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2
1 2
1 3
3 4
3 5
1 2```

### 输出

```
Ron
Ron```

## 样例 #2

### 输入

```
6 3
1 2
2 3
1 4
4 5
4 6
1 4 6```

### 输出

```
Hermione
Ron
Hermione```

# 题解

## 作者：eb0ycn (赞：5)

传送门：[CF1970C3](https://www.luogu.com.cn/problem/CF1970C3)。

算法：博弈论、SG 函数、换根 dp。

## 题意

[有向图游戏](http://magic.vicp.io/oi-wiki/math/game-theory/impartial-game/#sg)，但是在树上，而且起始点不固定（多次询问），要求时间复杂度 $O(n)$。

## 思路

首先你得会有向图游戏的 SG 函数：设 $f_i$ 为移动到第 $i$ 个节点的 SG 函数，则 $f_i$ 为 $i$ 的所有儿子的 SG 函数取反后的或和。

从 $1$ 号点开始 dfs，我们就求出了子树内的答案。

考虑怎么换根：子树以外，要么一路沿着父亲节点，要么经过某个祖先再拐弯。我们再开一个数组记录这种情况，转移是简单的。

## 代码

```cpp
#include<cstdio>
using namespace std;
int n,t,head[200001],nxt[400001],to[400001],tot,u,v,cnt[200001];
bool sg[200001];
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i])if(fa!=to[i])dfs(to[i],x),cnt[x]+=!cnt[to[i]];
}
void efs(int x,int fa){
	for(int i=head[x];i;i=nxt[i])
		if(fa!=to[i]){
        		if(cnt[x]>1||cnt[x]==1&&cnt[to[i]]||sg[x])sg[to[i]]=0;
			else sg[to[i]]=1;
			efs(to[i],x);
		}
}
int main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<n;++i)scanf("%d%d",&u,&v),nxt[++tot]=head[u],head[u]=tot,to[tot]=v,nxt[++tot]=head[v],head[v]=tot,to[tot]=u;
	dfs(1,0),efs(1,0);
	while(t--)scanf("%d",&u),printf("%s\n",cnt[u]||sg[u]?"Ron":"Hermione");
	return 0;
}
```

---

## 作者：66xyyd (赞：2)

~~玄学算法 AC~~

## 题意

给出一颗无根树和一个在某一个节点的棋子。罗恩和赫敏轮流移动这个棋子，每一次可以把棋子移动到相邻的节点，但不能移动到已经移动过得节点。

本版本树的形态不变，但是棋子最开始在的节点编号有多次询问。

## 题解

先解决 [medium version](https://www.luogu.com.cn/problem/CF1970C2)，即只有一次询问。

### medium version

对于最开始的节点编号，钦定它为树的根，使这棵树为有根树，那么我们有如下性质：

1. 如果遍历到了一个节点，那么它只能走到儿子，因为父亲已经走过了；

将每一个节点根据“走到这个节点的人能不能赢”标记为“必赢节点”和“必输节点”，根据性质 $1$，我们有以下推论：

2. 一个叶子节点是“必输节点”，因为它没有儿子，父亲也不能走；

3. 一个节点如果有一个儿子是“必输节点”，那么这个节点是“必赢节点”，因为把棋子移到这个必输节点就可以让对手输掉；

4. 如果一个节点的儿子全是“必赢节点”，那么这个节点是“必输节点”，因为不论如何移动棋子都会让对手赢。

根据推论 $2,3,4$，我们可以直接 dfs。得到的根节点是“必输节点”就是赫敏胜，否则是罗恩胜。

### hard version

从 medium version 的做法推至 hard version 的做法，一个很简单的方式是：对于棋子最开始放置位置依次为 $1,2,\cdots,n$ 的情况，都 dfs 一次，然后 $O(1)$ 查询，总的时间复杂度 $O(n^2)$。

如何优化这个时间复杂度呢？经过思考，我们得出以下推论：

5. 如果一个节点是“必赢节点”，那么当这个节点为根的时候也是“必赢节点”，不需要再次 dfs。原因是推论 $3$，很显然。

6. 如果在某次 dfs 中一个节点有两个及以上的儿子是“必输节点”，那么这个节点不论在什么情况下遍历，都是“必赢节点”。因为这个节点的父亲只能有一个，那么两个及以上的“必输节点”必定会留下来至少一个，根据推论 $3$，这个节点就是“必赢节点”。

7. 如果在某次 dfs 中一个节点的儿子是“必输节点”，那么在再次 dfs 时，只要这一次 dfs 中这个节点的父亲不是那个“必输节点”，就不需要 dfs，直接返回即可。

拿一张图举例子（样例 $1$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vnxqe8cz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果不经过推论 $5,6,7$ 的优化，那么我们原本的算法就要一共遍历 $5 \times 5=25$ 个节点。让我们看看推论 $5,6,7$ 的优化力度：

1. 经过以节点 $1$ 为根的 dfs（遍历 $1,2,3,4,5$ 共 $5$ 个节点），标记出来节点 $1,3$ 是“必赢节点”，不需要再进行 dfs（推论 $5$）；节点 $3$ 有两个儿子是“必输节点”，遍历到直接返回（推论 $6$）；节点 $1$ 有一个儿子是“必输节点”，如果 dfs 时父亲不是 $2$，直接返回即可。

2. 经过以节点 $2$ 为根的 dfs（遍历 $1,2,3$ 共 $3$ 个节点），无变化；

3. 节点 $3$ 无须遍历；

4. 经过以节点 $4$ 为根的 dfs（遍历 $3,4$ 共 $2$ 个节点），无变化；

5. 经过以节点 $5$ 为根的 dfs（遍历 $4,5$ 共 $2$ 个节点），无变化。

一共遍历了 $5+3+2+2=12$ 个节点，遍历数量是原来的一半！当然，你还可以试一下样例 $2$，遍历数量是原来的 $\frac{2}{5}$。

### 代码

```cpp
//不过这份代码的时间复杂度我还不清楚，不敢下结论
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
vector<int> G[200001];//存图用（存双向边）
int n;//节点数量
int ans[200001];//dfs中统计的ans
int rtans[200001];//rtans[i]表示以i为根的树是否是罗恩胜
int neighbors[200001],neighborid[200001];//儿子中必输节点数量；某一个必输节点的编号
void dfs(int i,int fa){
	ans[i]=false;
	if(neighbors[i]>1 || (neighbors[i]==1 && neighborid[i]!=fa)){
		//推论6和推论7
		ans[i]=true;
		return;
	}
	//清空可以重新统计一遍（貌似没有优化？）
	neighbors[i]=neighborid[i]=0;
	for(auto &son:G[i]){
		if(son==fa)	continue;
		dfs(son,i);
		if(!ans[son]){
			//这个儿子是必输节点
			++neighbors[i];
			neighborid[i]=son;
			rtans[i]=true;
			ans[i]=true;
		}
	}
	//因为叶子节点不会有儿子，ans就不可能被改成true，自然是必输节点，无须处理
}
int t;
int main(){
	cin >> n >> t;
	for(int i=1;i<n;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(rtans[i]==false){
			//如果rtans[i]为true，就不需要再dfs一遍了（推论5）
			dfs(i,0);
			rtans[i]=ans[i];
		}
	}
	for(int i=1;i<=t;i++){
		int u;
		cin >> u;
		cout << (rtans[u]?"Ron":"Hermione") << '\n';
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

模拟赛搬了这题。没想到吧这题我之前 duel 过/kx

做法和其它题解不太一样，欢迎来 Hack。

建议先阅读 [Medium 版本做法](https://www.luogu.com.cn/article/6hfojs29)。

---

如果对于每个起点，直接照搬 Medium 版本的暴力做法，时间复杂度为 $O(tn)$，显然超时。

考虑连接一个节点为什么状态时我们可以直接判断该。

若在某一次游戏中，我们判断出某个节点的儿子中有至少两个必败节点。那么无论哪一个节点成为该节点的父节点，我们都可以保证其子节点中至少有一个必败节点，即可以保证该节点为必胜节点。

如果前面某次游戏某个节点的儿子中仅有一个必败节点，且这个节点在此次游戏中不为该节点的父节点，则该节点也为必胜节点。（有点绕，大家可以多读几遍。）

这样我们可以提前把以任意节点为起点的结果都预处理出来，然后 $O(1)$ 处理询问。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+2;
vector<int> edge[N];
bool isw[N];
int lcnt[N],lson[N];//必输 
bool aliw[N];

void dfs(int x,int fa){
	if(lcnt[x]>=2 || (lcnt[x]==1 && lson[x]!=fa)){
		isw[x]=1;
		return ;
	}
	isw[x]=0;
	for(int i : edge[x]){
		if(i==fa) continue;
		dfs(i,x);
		if(isw[i]) continue;
		lcnt[x]++,lson[x]=i;
		isw[x]=1;
	}
}

int main(){
	int n,t;cin>>n>>t;
	for(int i=1; i<n; i++){
		int u,v;cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i=1; i<=n; i++){
		if(aliw[i]) continue;
		dfs(i,0);aliw[i]=isw[i];
	}
	while(t--){
		int x;cin>>x;
		if(aliw[x]) cout<<"Ron\n";
		else cout<<"Hermione\n";
	}
	return 0;
}
```

---

## 作者：OneLeft (赞：1)

## 题意
[题目传送门](https://codeforces.com/problemset/problem/1970/C3)

## 思路
发现询问的次数较多，考虑把答案预处理出来。

由题可知在一轮游戏中，棋子不可以走已经走过的节点，若棋子的出发点是根，那么限制就变成了不可以走向父亲，此时棋子从根节点出发是否可以获胜可以用树形 DP 求出，故我们考虑把每个节点依次作为根，然后用树形 DP 解决问题。

设 `dp[u][0/1]` 表示在棋子在 `u`，罗恩/赫敏先手，罗恩是否可以取胜，在设 `u` 的儿子为 `v`，有如下转移方程：

```cpp
dp[u][0]|=dp[v][1]
dp[u][1]&=dp[v][0]
```

初始值：`dp[u][0]=false`，`dp[u][1]=true`。

在我们替换根时，若每次都重新 DP，则时间复杂度为 $O(n^2)$，会超时，故考虑优化，发现只有当前的根和新的根的答案会改变，所以只需处理这两个节点的答案即可，于是总体时间复杂度降为 $O(n)$，具体细节见代码。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
list<int>edge[N];
void build(int u,int v){edge[u].push_back(v);}
bool dp[N][2];
void DFS1(int u,int fa)
{
	dp[u][1]=true;
	for(int v:edge[u])
	{
		if(v==fa)continue;
		DFS1(v,u);
		dp[u][0]|=dp[v][1];
		dp[u][1]&=dp[v][0];
	}
}
bool ans[N];
void DFS2(int u,int fa)
{
	int cnt1=0,cnt2=0;
	dp[u][0]=false,dp[u][1]=true;
	for(int v:edge[u])
	{
		if(dp[v][1])cnt1++,dp[u][0]=true;
		if(!dp[v][0])cnt2++,dp[u][1]=false;
	}
	if(dp[u][0])ans[u]=true;
	for(int v:edge[u])
	{
		if(v==fa)continue;
		bool tmp1=dp[u][0],tmp2=dp[u][1];
		if(cnt1==1&&dp[v][1])dp[u][0]=false;
		if(cnt2==1&&!dp[v][0])dp[u][1]=true;
		DFS2(v,u);
		dp[u][0]=tmp1,dp[u][1]=tmp2;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,build(u,v),build(v,u);
	DFS1(1,0),DFS2(1,0);
	while(q--)
	{
		int x;
		cin>>x;
		if(ans[x])cout<<"Ron\n";
		else cout<<"Hermione\n";
	}
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

感觉是本场的签到。

upd on 2024.6.6：修改了一处笔误。

# Part 2：正文

将棋子初始所在的点视为根，注意到棋子的移动方式一定是从根到叶子的一条路径。因此考虑 dp 这样从叶子到根的路径的信息。

设 $f(u)$ 表示只考虑 $u$ 的子树中，当棋子落在 $u$ 节点时，是否存在一条先手必胜的路径。同时令 $son(u)$ 为 $u$ 的所有儿子。根据博弈论基础知识，我们的转移有 $f(u)=\sum\limits_{v\in son(u)} (1-f(v))$，这里的加法定义为逻辑或运算。对于每次询问从根暴力 dp 即可通过 C2。

对于 C3，不难想到换根 dp 预处理每个节点的答案后暴力查询。令 $anc(u)$ 表示 $u$ 的父亲，具体而言，令 $g(u)$ 表示以 $u$ 的父亲为根，以全体点删掉 $u$ 子树的点构成的连通块为树，是否存在合法路径，$h(u)$ 表示以 $u$ 为根的答案。显然有转移是 $h(u)=f(u)+(1-g(u))$。考虑 $g(u)$ 的转移。若 $g(anc(u))=0$ 则有 $g(u)=0$，否则若 $u$ 为 $son(anc(u))$ 中 $f(u)=0$ 的唯一点，则 $g(u)=0$，否则 $g(u)=1$。

综上，我们在 $O(n)$ 的复杂度内解决了此问题。

# Part 3：代码

```cpp
// Everything we tried to say
// 想要说的话
// Up until the final day
// 留到了最后一天
// I guess we said enough, said enough
// 我们已经说得够多
// To know it's all in vain
// 已经知道这一切都是徒劳


#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T>
void seq_read(T bg,T ed){for(auto i=bg;i!=ed;++i)read(*i);}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
//Some useful function

template<typename T>
void cmax(T& x,T y){x=max(x,y);}
template<typename T,typename... Args>
void cmax(T& x,T y,Args ...args){cmax(x,y);cmax(x,args...);}
template<typename T>
void cmin(T& x,T y){x=min(x,y);}
template<typename T,typename... Args>
void cmin(T& x,T y,Args ...args){cmin(x,y);cmin(x,args...);}
template<typename T,typename U>
void seq_assign(T bg,T ed,U val){for(auto i=bg;i!=ed;++i)(*i)=val;}
template<typename T,class F,class=enable_if_t<is_invocable_v<F>>>
void seq_assign(T bg,T ed,F func){for(auto i=bg;i!=ed;++i)(*i)=func(i);}
template<typename T>
void seq_copy(T dstbg,T dsted,T srcbg,T srced){for(auto i=dstbg,j=srcbg;i!=dsted&&j!=srced;++i,++j)(*i)=(*j);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=2e5+7;
int n,t;
vector<int>e[N];
bool f[N],g[N],h[N];

bool memed=0;

//=========================================================================================================
// Code here.

void dfs(int u,int pre){
	for(auto v:e[u]){
		if(v==pre)continue;
		dfs(v,u);
		f[u]|=(!f[v]);
	}
}

void solve(int u,int pre){
	if(u!=1){
		h[u]|=!g[pre];
		for(auto v:e[u])
			if(v!=pre)
				h[u]|=!f[v];
	}
	int only=-1;
	if(pre&&!g[pre])only=0;
	for(auto v:e[u])
		if(v!=pre&&!f[v]){
			if(only==-1)
				only=v;
			else
				only=0;
		}
	// printf("%d %d\n",u,only);
	for(auto v:e[u])
		if(v!=pre){
			if(only==-1)
				g[u]=0;
			else
				g[u]=(only!=v);
			solve(v,u);
		}
}

void solve(){
	read(n,t);
	for(int i=1,u,v;i<n;i++){
		read(u,v);
		e[u].emplace_back(v),e[v].emplace_back(u);
		
	}
	dfs(1,0);
	h[1]=f[1];
	solve(1,0);
	for(int qid=1,p;qid<=t;qid++){
		read(p);
		if(!h[p])
			printf("Hermione\n");
		else
			printf("Ron\n");
	}
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

## 作者：yyrwlj (赞：0)

先不考虑往父节点走，只考虑子树内先手输赢。

那么有叶节点先手必输，其它节点如果有先手必输的子节点就先手必赢，否则必输。

现在考虑往父节点走，发现如果子树内先手必赢，先手肯定直接走子树内了，也就是说子树内先手必输才会往父节点走。

然后先手转换成赫敏，也是同理，但是子节点信息要去掉刚才走上来的那一边。

最后看到先手必赢的节点时，先手是谁即可，注意特判到根节点后不能再往上走。

```cpp
#include <bits/stdc++.h>
#define lowbit(o) o & -o
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 500005;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const LL INF = 2e18;
vector<int> g[N];
int f[N], dep[N], cnt[N], n, m;
bool st[N];
int w;
void dfs(int u,int fa)
{
	f[u] = 1;
	dep[u] = dep[fa] + 1;
	for (int i : g[u])
	{
		if (i == fa)
			continue;
		dfs(i, u);
		if (f[i] == 1)
			f[u] = 0, cnt[u] ++;
	}
}
void dfs2(int u,int fa,int last)
{
	if (u != 1)
	{
		if (last && (dep[u] - dep[last]) % 2 == 0)
			st[u] = true;
		if (!last && !w && (dep[u] - dep[1]) % 2 == 1)
			st[u] = true;
	}
	if (u == 1)
		w = cnt[u];
	for (int i : g[u])
	{
		if (i == fa)
			continue;
		int v = cnt[u];
		if (f[i] == 1)
			v --;
		if (u == 1 && f[i] == 1)
			w --;
		if (v)
			dfs2(i, u, u);
		else
			dfs2(i, u, last);
	}
}
void work()
{
	cin >> n >> m;
	for (int i=1;i<n;i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1, 1);
	dfs2(1, 1, 0);
	while (m--)
	{
		int x;
		cin >> x;
		if (f[x] == 0 || st[x])
			cout << "Ron\n";
		else
			cout << "Hermione\n";		
	}
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _T = 1;
    //cin >> _T;
    while (_T--)
    	work();
    return 0;
}
```

---

## 作者：Suite_No1_G (赞：0)

题外话：再不写题解社区贡献分就要变成 $0$ 了。

分析：

请先确保能够理解本题 medium 的做法。

看到多次询问，容易想到换根 dp 求出每一个节点的答案，并最后输出。

令 $1$ 号点为根。

如 medium 做法，定义 $dp_i$ 表示先手在以 $i$ 为根的子树中能否必胜。$1$ 表示能必胜，反之 $0$ 表示不能。

转移：如果 $i$ 的一个子节点 $j$ 是先手必败的，则这一步操作者可以将石子移到 $j$ 然后另一个人就必败了，此时先手必胜。否则，如果每一个 $j$ 都是先手必胜，那么无论当前操作者怎么移动，后手都是必胜，所以先手必败。

然后，我们还要考虑子树外面的情况。

定义 $f_i$ 表示在以 $i$ 为子树外面能否必胜。
令 $fa$ 为 $i$ 的父节点。

转移：

如果 $f_{fa}$ 能够必胜，那么无论怎样，下一步当前操作者必须将石子从 $i$ 移到 $fa$，然后就输了。所以此时 $f_i$ 为 $0$。

如果 $f_{fa}$ 不能必胜，那么我们就得考虑 $i$ 的兄弟节点。令 $i$ 的兄弟节点为 $sib$。假设任何一个兄弟节点满足 $dp_{sib}$ 必败，那么当前操作者将 $i$ 移到 $fa$，对手移到 $sib$ 那么我们是必败的，所以这种情况 $f_i$ 等于 $0$。如果 $i$ 的所有兄弟节点都是必胜的话，那么 $f_i$ 也是必胜的。

初始时 $f_1$ 等于 $0$。

最后的查询，如果 $dp$ 和 $f$ 值有一个能保证必胜，那么先手 Ron 就能必胜。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;
vector<int> G[maxn];
int dp[maxn],f[maxn];

void dfs1(int u,int fa){
	dp[u]=-1;
	int flag=0;
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		
		dfs1(v,u);
		flag=1;
	}
	
	if (flag==0){
		dp[u]=0;
		return ;
	}
	
	dp[u]=0;
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		
		if (dp[v]==0){
			dp[u]=1;
			break;
		}
	}
}

void dfs2(int u,int fa){
	int sum=0,cnt=0;
	
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		
		cnt++;
		sum+=dp[v];
	}
	
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		
		if (f[u]==1) f[v]=0;
		else{
			int sib0=0;
			if (sum<=cnt-2) sib0=1;//多于两个点有必败结果，那么必然有一个兄弟节点必败 
			else if (sum==cnt-1){
				if (dp[v]==1) sib0=1;//如果有一个点必败且不是自己，那么这个点一定是兄弟节点 
			}
			
			if (sib0==1) f[v]=0;
			else f[v]=1;
		}
	}
	
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		dfs2(v,u);
	}
}

int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	
	for (int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	
	dfs1(1,0);
	dfs2(1,0);
	
	while (t--){
		int s;
		scanf("%d",&s);
		
		if (dp[s]==1||f[s]==1) printf("Ron\n");
		else printf("Hermione\n");
	}
	return 0;
}
```

---

## 作者：mango2011 (赞：0)

对于这一种树上博弈的问题，我们一般来说直接 dp 就可以了。

可以随便找一个根 $rt$，如 $rt=1$。

令 $dp_u$ 为从 $u$ 出发，往子树内走的获胜情况（$1$ 为先手必胜，$0$ 为后手必胜）。显然，若 $u$ 有一个儿子 $v$，使得 $dp_v=0$，那么 $dp_u=1$，否则 $dp_u=0$。

但是这个思路显然不够全面，就是对于一个节点，有可能还能往上走那么我们记录一个 $up_u$，为从 $u$ 出发往上走的情况（令 $dp_{rt}=1$）：

1) 走一步之后对手可以把棋子走到其父亲的另一棵子树里，并且获胜。对于这一种情形，我们再开一个 $dp$，思路和上面类似。

2) 如果不存在这样的子树，那么对手也只能往上走（如果已经走到根了，并且对手也无法直接获胜，那么 $up_u=1$），然后我们再看新走到的节点，与 1）类似判断即可。

输出答案时，如果 $up_u$ 或 $dp_u$ 中至少有一个成立，那么输出先手的名字，否则输出后手的名字。代码很简单，但是我写的非常差，所以就不放了。

注：有人要代码，所以就放上了，欢迎 hack。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
vector<int>g[maxn];
bool up[maxn];
map<int,bool>dp[maxn];
int dep[maxn];
int f[maxn];
void dfs(int u,int fa)
{
	f[u]=fa;
	dep[u]=dep[fa]+1;
	int i,cnt=0;
	for(i=0;i<(int)g[u].size();i++)
	{
		int v=g[u][i];
		if(v!=fa)
		{
			dfs(v,u);
			if(!dp[v][-1])
			{
				cnt++;
			}
		}
	}
	if(cnt>0)
	{
		dp[u][-1]=1;
	}
	for(i=0;i<(int)g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fa)
		{
			continue;
		}
		int t1=cnt-(!dp[v][-1]);
		if(t1>0)
		{
			dp[u][v]=1;
		}
		else
		{
			dp[u][v]=0;
		}
	}
}
void dfs1(int u,int fa)
{
	int t=u;
	if(f[t]!=0)
	{
		t=f[t];
		if(!dp[t][u])
		{
			if(f[t]!=0)
			{
				t=f[t];
				if(up[t]||dp[t][f[u]])
				{
					up[u]=1;
				}
			}
			else
			{
				up[u]=!dp[t][u];
			}
		}
	}
	int i;
	for(i=0;i<(int)g[u].size();i++)
	{
		int v=g[u][i];
		if(v!=fa)
		{
			dfs1(v,u);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	int n,i,t;
	cin>>n>>t;
	for(i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	dfs1(1,0);
	for(i=1;i<=t;i++)
	{
		int x;
		cin>>x;
		if(x==1)
		{
			if(dp[x][-1])
			{
				cout<<"Ron"<<endl;
			}
			else
			{
				cout<<"Hermione"<<endl;
			}
			continue;
		}
		if(dp[x][-1]||up[x])
		{
			cout<<"Ron"<<endl;
		}
		else
		{
			cout<<"Hermione"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：_2eyks (赞：0)

某 wiki 上写的 SG 函数是取后继的 $\operatorname{mex}$，奶龙，真的这么写了然后维护写成史了。

显然，这里的 SG 函数的取值为 $\{0,1\}$ 中的一个数，一个点的 SG 值是所有后继的 SG 函数取反后的或和。这样该问题的前两个版本都做完了。

然后这个题的优化方法显然是换根，可以把 SG 函数取值时的求或和改为求和，把取反改为用后继 SG 函数值等于零的数量，只要 SG 函数大于 $0$ 就必胜了。换根很容易，把原来的根的 SG 函数减掉新根的 SG 函数，新根变为做和即可。

不放代码了，因为我写了取 $\operatorname{mex}$ 的超甜做法。

upd：管理真的要我把代码放上去，那就放吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
const int N=2e5+5;
int n,q,sg[N],ans[N];
vector<int>e[N];
set<int>s[N];
multiset<int>rs[N];
void init(int u,int fa){
    for (auto v:e[u])
        if (v!=fa)
            init(v,u);
    for (auto v:e[u])
        if (v!=fa){
            if (s[u].find(sg[v])==s[u].end())
                rs[u].insert(sg[v]);
            s[u].erase(sg[v]);
        }
    sg[u]=*s[u].begin();
}
void dfs(int u,int fa){
    if (u!=1){
        int _sg=sg[fa],_sgu=sg[u];
        if (rs[fa].find(sg[u])==rs[fa].end())
            s[fa].insert(sg[u]);
        else rs[fa].erase(rs[fa].find(sg[u]));
        sg[fa]=*s[fa].begin();
        if (s[u].find(sg[fa])==s[u].end())
            rs[u].insert(sg[fa]);
        else s[u].erase(sg[fa]);
        ans[u]=sg[u]=*s[u].begin();
        for (auto v:e[u])
            if (v!=fa)
                dfs(v,u);
        sg[fa]=_sg,sg[u]=_sgu;
        if (s[fa].find(sg[u])==s[fa].end())
            rs[fa].insert(sg[u]);
        else s[fa].erase(sg[u]);
        if (rs[u].find(sg[fa])==rs[u].end())
            s[u].insert(sg[fa]);
        else rs[u].erase(rs[u].find(sg[fa]));
    }
    else{
        ans[u]=sg[u];
        for (auto v:e[u])
            dfs(v,u);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for (int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i=1;i<=n;i++)
        for (int j=0;j<=e[i].size();j++)
            s[i].insert(j);
    init(1,0);
    dfs(1,0);
    while (q--){
        int x;
        cin>>x;
        if (ans[x]) cout<<"Ron\n";
        else cout<<"Hermione\n";
    }
    return 0;
}
```

---

