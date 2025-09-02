# [USACO24DEC] 2D Conveyer Belt S

## 题目描述

Farmer John 的牛奶工厂可以用一个 $N\times N$（$1≤N≤1000$）的方阵来表示，其中的方格带有传送带。位置 $(a,b)$ 描述了位于从上往下第 $a$ 行、从左往右第 $b$ 列的方格。有 $5$ 种类型的方格：

- $\texttt{L}$ — 该方格是一个向左的传送带，每一单位时间会将所有物品向左移动一格。
- $\texttt{R}$ — 该方格是一个向右的传送带，每一单位时间会将所有物品向右移动一格。
- $\texttt{U}$ — 该方格是一个向上的传送带，每一单位时间会将所有物品向上移动一格。
- $\texttt{D}$ — 该方格是一个向下的传送带，每一单位时间会将所有物品向下移动一格。
- $\texttt{?}$ — Farmer John 还没有在该方格上建造传送带。
注意传送带也可以将物品移动到方阵外。一个方格 $c$ 是不可用的，当且仅当一个放置在方格 $c$ 上的物品将永远不会离开传送带方阵（即它会永远在方阵中移动）。

初始时，Farmer John 还没有开始建造传送带，所以所有方格都以 $\texttt{?}$ 开始。接下来的 $Q$（$1≤Q≤2⋅10^5$）天，从第 $1$ 天开始到第 $Q$ 天，Farmer John 将选择一个没有传送带的方阵并在该方阵上建造一个传送带。

具体地说，在第 $i$ 天，Farmer John 将在位置 $(r_i,c_i)$（$1≤r_i,c_i≤N$）建造一个类型 $t_i$（$t_i\in\{\texttt{L},\texttt{R},\texttt{U},\texttt{D}\}$）的传送带。输入保证在位置 $(r_i,c_i)$ 没有传送带。

每天过后，请帮助 Farmer John 求出他通过最优地在所有余下的没有传送带的方格上建造传送带可以达到的不可用方格的最小数量。

## 说明/提示

### 样例 #1 解释

第五天过后的传送带如下所示。

$$\begin{aligned}
\texttt{RL?}\\
\texttt{U??}\\
\texttt{?DL}\\
\end{aligned}
$$
一种在余下的方格上建造传送带的最优方案如下。

$$\begin{aligned}
\texttt{RLR}\\
\texttt{URR}\\
\texttt{LDL}\\
\end{aligned}
$$
在这种配置下，位于 $(1,1)$，$(1,2)$ 和 $(2,1)$ 的方格是不可用的。

### 样例 2 解释

第八天过后的传送带如下所示。

$$\begin{aligned}
\texttt{RLD}\\
\texttt{D?U}\\
\texttt{URL}\\
\end{aligned}
$$

无论 Farmer John 在中间建造何种传送带，所有方格都将是不可用的。

### 测试点性质

- 测试点 1-3：样例。
- 测试点 4-5：$N≤10$。
- 测试点 6-7：$N≤40$。
- 测试点 8-13：没有额外限制。

## 样例 #1

### 输入

```
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U```

### 输出

```
0
0
0
2
3```

## 样例 #2

### 输入

```
3 8
1 1 R
1 2 L
1 3 D
2 3 U
3 3 L
3 2 R
3 1 U
2 1 D```

### 输出

```
0
2
2
4
4
6
6
9```

## 样例 #3

### 输入

```
4 13
2 2 R
2 3 R
2 4 D
3 4 D
4 4 L
4 3 L
4 2 U
3 1 D
4 1 R
2 1 L
1 1 D
1 4 L
1 3 D```

### 输出

```
0
0
0
0
0
0
0
0
11
11
11
11
13```

# 题解

## 作者：LinkCatTree (赞：11)

首先考虑什么样的方格是“不可用的”。显然有两种情况：在一个传送带构成的环上或在一个传送带构成的环内。

我们发现判断哪些方格在环内是比较困难的，我们不妨判断哪些方格是“**可用的**”，这是比较简单的。具体来讲，我们可以从边界开始 DFS，所有可以遍历到的方格都是“可用的”，其中能够遍历到的方格必须是 `?` 或传送带方向与遍历的方向**相反**（比如方格 A 是“可用的”，而其左边的方格 B 上的传送带方向为 `L`，那么方格 B 也是“可用的”）。通过 DFS 可以 $\mathcal{O}(n^2)$ 求出所有“可用的”方格，进而求出“不可用”的方格数量。

但是如果对于每一个询问都进行 DFS，显然会 TLE。我们正难则反，考虑对于最终情况先 DFS 求出最终的答案，再回溯，每次**删掉**某个传送带。

我们对删掉的传送带分类讨论：

1. 若删掉的传送带本身就是“可用的”，删去后它还是“可用的”，对答案没有影响。

2. 若删掉的传送带本身“不可用”：

   - 若删掉的传送带上下左右有至少一个方格是“可用的”，那么显然这个传送带也会变得“可用”，可以通过 DFS 来求出随之变得“可用的”方格数量，方法同上。
  
   - 否则，这个传送带肯定依旧是“不可用的”。~~可以手动模拟几组数据发现规律~~我们考虑如何证明。
  
     * 如果这个方格在某个环**内**，那么它无论怎么变必然出不去这个环，说明它是“不可用的”。
    
     * 如果这个方格在某个环**上**，那么与其相邻的四个方格中至少有一个是在这个环**外**的，而这个（些）点也是“不可用的”，说明这些点也在环内或环上，这个方格无论往哪个方向走都给必然会到某个环上或环内。说明它是“不可用的”。
    
     * 一种也许更加方便的证明方法是：因为四周都是“不可用的”，所以没法 DFS 到该点，所以这个点也是“不可用的”。

由于每个“可用的”点最多仅会遍历一次，那么总时间复杂度就为 $\mathcal{O}(n^2+q)$。

```cpp
const int N=1005,Q=2e5+5;
int n,q,mp[N][N],g[N][N],cnt;
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
struct change {
	int x,y,t,ans;
	change()=default;
	change(int x,int y,int t):x(x),y(y),t(t) {}
} c[Q];

inline int check(int x,int y) {
	if(x<0||x>n+1||y<0||y>n+1) return 0;
	if(!x||!y||x>n||y>n) return -1;
	return 1;
}
void spread(int x,int y,int t) {
	if(!g[x][y]) cnt++;
	g[x][y]=1;
	for(int d=0;d<4;d++) {
		int px=x+dx[d],py=y+dy[d];
		if(!check(px,py)||g[px][py]) continue ;
		if(~mp[px][py]&&mp[px][py]!=d) continue ;
		spread(px,py,t);
	}
	return ;
}

int main() {
	n=read(),q=read();
	memset(mp,-1,sizeof(mp));
	for(int i=1;i<=q;i++) {
		c[i].x=read(),c[i].y=read();
		char dire[5];
		scanf("%s",dire+1);
		if(dire[1]=='L') c[i].t=0;
		if(dire[1]=='R') c[i].t=1;
		if(dire[1]=='U') c[i].t=2;
		if(dire[1]=='D') c[i].t=3;
		mp[c[i].x][c[i].y]=c[i].t;
	}
	spread(0,0,q);
	c[q].ans=(n+2)*(n+2)-cnt;
	for(int i=q;i>1;i--) {
		mp[c[i].x][c[i].y]=-1;
		if(!g[c[i].x][c[i].y]) {
			int flag=0;
			for(int d=0;d<4;d++) flag|=g[c[i].x+dx[d]][c[i].y+dy[d]];
			if(flag) spread(c[i].x,c[i].y,i);
		}
		c[i-1].ans=(n+2)*(n+2)-cnt;
	}
	for(int i=1;i<=q;i++) printf("%d\n",c[i].ans);
	return 0;
}
```

---

## 作者：chatoudp (赞：4)

赛时 TLE 了一个点，“喜”提差一个点 AK，赛后 $5$ 分钟 AC。

泛洪算法。

转化问题，把一个点能否走出矩阵转化为能否从矩阵外倒向走传送带或走 ```?``` 到达该点。我们可以记录每个节点在啥时候被按上传送带的，通过泛洪求出每个节点在从矩阵外到这里最少要不符合传送带地走的传送带的安放时间，这就是该点在何时开始不可走出矩阵。最后，运用差分即可求出答案。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,x,y,mp[1005][1005];
int ans[200005],ti[1005][1005],P[1005][1005];
char ch;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
priority_queue<pair<int,pair<int,int>>> q;
void bfs(){
	for(int i=1;i<=n;i++){
		q.push({m+1,{0,i}});
		q.push({m+1,{n+1,i}});
	}
	for(int i=1;i<=n;i++){
		q.push({m+1,{i,0}});
		q.push({m+1,{i,n+1}});
	}
	int ans=0;
	while(!q.empty()){
		int x=q.top().second.first; 
		int y=q.top().second.second; 
		int TI=q.top().first; q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i]; int ny=y+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=n){
				if(P[nx][ny]<min(TI,((mp[nx][ny]==-1||mp[nx][ny]==(i^1))?m+1:ti[nx][ny]))){
					q.push({min(TI,((mp[nx][ny]==-1||mp[nx][ny]==(i^1))?m+1:ti[nx][ny])),{nx,ny}});
					P[nx][ny]=min(TI,((mp[nx][ny]==-1||mp[nx][ny]==(i^1))?m+1:ti[nx][ny]));
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	memset(mp,-1,sizeof(mp));
	memset(P,-1,sizeof(P));
	for(int i=1;i<=m;i++){
		scanf("\n%d %d %c",&x,&y,&ch);
		int fx;
		if(ch=='L') fx=1;
		if(ch=='R') fx=0;
		if(ch=='U') fx=2;
		if(ch=='D') fx=3;
		mp[x][y]=fx; ti[x][y]=i;
	}
	bfs();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans[P[i][j]]--,ans[1]++;
	for(int i=1;i<=m;i++) printf("%d\n",n*n-(ans[i]+=ans[i-1]));
	return 0;
}

```

---

## 作者：GUO120822 (赞：4)

第一次 AK 银组，发题解庆祝下。

感觉比第二题简单。半小时做完了。

首先，第一感觉倒序处理。因为这样就只有确定变成问号的情况。对于每个问号处理一下，就可以通过此题。

于是直接暴力 dfs。对于每个被修改成问号，修改他的可行性。可行性就是能不能走出去。

若改变了他的状态，那么就有可能改变其他的状态。

于是逆推，对于每次修改，从哪个点开始跑 bfs。能走到他的点就标记。

这样，只有可能原本没标记的被标记，否则不走下去。复杂度正确。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int N=1010,M=5e5+10;
int T,n,Q,i,j,k,x[M],y[M],X,Y,ans,tx,ty,A[M];
char a[N][N],c[M];
bool vis[N][N];
map<char,int> mp;
bool r;
int fx[5]={0,0,1,0,-1};
int fy[5]={0,1,0,-1,0};
queue<pii> q;
bool can(int sx,int sy,int x,int y)
{
	int tx,ty;
	if (a[sx][sy]=='?')
	{
		int i;
		for (i=1;i<=4;i++)
		{
			tx=sx+fx[i];
			ty=sy+fy[i];
			if (tx==x&&ty==y) return true;
		}
		return false;
	}
	else
	{
		tx=sx+fx[mp[a[sx][sy]]];
		ty=sy+fy[mp[a[sx][sy]]];
		if (tx==x&&ty==y) return true;
		return false;
	}
}
void work()
{
	int x,y,tx,ty,i;
	while (!q.empty())
	{
		x=q.front().first;
		y=q.front().second;
		q.pop();
		for (i=1;i<=4;i++)
		{
			tx=x+fx[i];
			ty=y+fy[i];
			if (tx>=1&&tx<=n&&ty>=1&&ty<=n&&can(tx,ty,x,y))
			{
				if (!vis[tx][ty])
				{
					vis[tx][ty]=true;
					ans--;
					q.push({tx,ty});
				}
			}
		}
	}
}
int main()
{	
	mp['R']=1;
	mp['D']=2;
	mp['L']=3;
	mp['U']=4;
	cin>>n>>Q;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++) a[i][j]='?';
	}
	for (i=1;i<=Q;i++)
	{
		cin>>x[i]>>y[i]>>c[i];
		a[x[i]][y[i]]=c[i];
	}
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			if (a[i][j]=='?')
			{
				if (i+1>n||i-1<1||j+1>n||j-1<1)
				{
					vis[i][j]=true;
					q.push({i,j});
				}
			}
			else
			{
				if (i+fx[mp[a[i][j]]]<1||i+fx[mp[a[i][j]]]>n||j+fy[mp[a[i][j]]]<1||j+fy[mp[a[i][j]]]>n)
				{
					vis[i][j]=true;
					q.push({i,j});
				}
			}
		}
	}
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			if (!vis[i][j]) ans++;
		}
	}
	work();
	for (i=Q;i>=1;i--)
	{
		X=x[i];
		Y=y[i];
		A[i]=ans;
		a[X][Y]='?';
		if (vis[X][Y]==true) continue; 
		r=false;
		for (j=1;j<=4;j++)
		{
			tx=X+fx[j];
			ty=Y+fy[j];
			if (tx>=1&&tx<=n&&ty>=1&&ty<=n&&vis[tx][ty]&&can(X,Y,tx,ty)) r=true;
			if (tx<1||tx>n||ty<1||ty>n) r=true;
		}
		if (r)
		{
			vis[X][Y]=true;
			ans--;
			q.push({X,Y});
			work();
		}
	}
	for (i=1;i<=Q;i++) cout<<A[i]<<"\n";
	return 0;
}

```

---

## 作者：ZHR100102 (赞：4)

一道质量极高的图论，CCF 什么时候也能把比赛出得质量这么高呢。

# 观察

首先面对这种不断往图里面加点或者边，且**满足前面的答案可以由加边后推出**的题，第一个想到的就得是**倒序枚举加边过程**的 trick。一个经典的例子就是并查集倒序枚举操作。

然后我们观察，什么形态的图才会导致陷入一个死循环中。显然，要一堆方格围起来形成一个封闭的区域。

那么我们判断一个点会不会陷入死循环的方式就出来了：
- 若这个点还未确定方向，则与它四联通的点中只要有一个可以不陷入死循环，他就可以不陷入死循环。
- 若这个点方向已确定，则只有它要去的点可以不陷入死循环，他才能不陷入死循环。

于是，当一个图形态确定时，我们可以通过泛洪算法来求出哪些点可以不陷入死循环中。实现上，我们从四个边界外出发，然后向内依次拓展，对于一个待拓展的点判断能否找到一个可以不让他陷入死循环的点，转移一下即可。

时间复杂度 $O(n^2)$。

# 去除限制

接下来就是要考虑如何倒序枚举加边过程，即不断将图中本来确定方向的点换成问号。

显然，确定方向是一个比问号更强的限制。一旦去掉这个限制，陷入死循环的点一定不会增加。

同时，如果一个点本来就不会陷入死循环，那么我们就没有必要进行这次改成问号的操作了。因为这样一定最优了。

那么如果这个点本来会陷入死循环呢？我们依然可以按上述判断方法判断这个点能否不陷入死循环。若可以不陷入，那么就把这个点 Flood Fill 一下，枚举与它四联通的点进行拓展即可。

由于每个点**不会被拓展后又变回去**，所以每个点最多被拓展一次。那么均摊下来，整题时间复杂度就是 $O(n^2)$ 的了。

# 代码

实现上，我们可以在 dfs 内部判断是否已被填充，是的话就不拓展了。然后在一个点新拓展的时候遍历与它四联通的点，在待拓展点的递归内部判断能否填充。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
int n,q,a[1005][1005],now=0;
int gox[]={0,0,1,-1};
int goy[]={1,-1,0,0};
int goc[]={2,1,4,3};
struct qry{
    int x,y,tp,ans;
}b[200005];
bitset<1005>vis[1005];
bool legal(int x,int y)
{
    return (x>=1&&x<=n&&y>=1&&y<=n);
}
void dfs(int x,int y)
{
    if(vis[x][y])return;
    bool flag=0;
    if(a[x][y])
    {
        int tx=x+gox[goc[a[x][y]-1]-1],ty=y+goy[goc[a[x][y]-1]-1];
        if(vis[tx][ty])flag=1;
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            int tx=x+gox[i],ty=y+goy[i];
            if(vis[tx][ty])flag=1;
        }
    }
    if(!flag)return;
    now++;
    vis[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int tx=x+gox[i],ty=y+goy[i];
        if(legal(tx,ty))dfs(tx,ty);
    }
}
void init()
{
    now=0;
    for(int i=1;i<=n;i++)
    {
        vis[i][0]=1;
        vis[0][i]=1;
        vis[i][n+1]=1;
        vis[n+1][i]=1;
    }
    for(int i=1;i<=n;i++)
    {
        dfs(i,1);
        dfs(i,n);
        dfs(1,i);
        dfs(n,i);
    }
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=q;i++)
    {
        int x,y,tp;
        char c;
        cin>>x>>y>>c;
        if(c=='L')tp=1;
        else if(c=='R')tp=2;
        else if(c=='U')tp=3;
        else tp=4;
        b[i]={x,y,tp,0};
        a[x][y]=tp;
    }
    init();
    for(int i=q;i>=2;i--)
    {
        b[i].ans=now;
        a[b[i].x][b[i].y]=0;
        dfs(b[i].x,b[i].y);
    }
    b[1].ans=now;
    for(int i=1;i<=q;i++)cout<<n*n-b[i].ans<<'\n';
    return 0;
}
```

---

## 作者：chenxi2009 (赞：4)

## 思路

本题解使用 $O(N^2)$ 搜索。~~挑战这道题代码最短的题解。~~\
转换题意，令 $cnt$ 为可以走到界外的格子数，求每次操作后 $N^2-cnt$，这样它就看着像一个正经的图论问题了。

原先每个格子可以向四个方向走，相当于连了四条边，而加上了字母之后它有三条边被切断了，这样的修改是很难维护的，不妨考虑**正难则反**，倒着考虑每个时刻，这样每次操作前就加回三条边，看上去顺眼了很多。

接下来我们的问题是：每次给图加上三条边，问每次操作后可以到达界外的点的数量。\
到达“界外”非常抽象，我们可以建一个超级汇点。但是这个问题看上去令人很没有头绪，长得就像一个拓扑排序的样子。

不妨再转换一下，如果我们建的是**反图**呢？这样问题就是**每次询问连边后源点（表示界外）可以到达的格点数**。\
可以记录每个点是否已被到达（以下称“被标记”），每次**从一个被标记的点连边**就搜索，把这个点可达的点都打标记并统计。\
采用记忆化的思想，遇到已被到达的点就不搜它，这样均摊一下时间复杂度只有 $O(N^2)$。

结束了，总结一下，倒序，建反图，记忆化暴力搜索，银组压轴就被我们用可能的最低的复杂度做完啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,r[200001],c[200001],cnt,ans[200001],d[4][2] = {{-1,0},{0,-1},{0,1},{1,0}},num[1001][1001];//d 为方向数组，方便遍历四个方向
char t[200001],x[1001][1001],zt[4] = {'U','L','R','D'};//zt 把可走的方向和字母联系起来
bool fre[1000001];
vector<int>e[1000001];
inline void free_point(int u){//当一个点被一个已可以被到达的点到达
	queue<int>q;
	q.push(u);
	while(q.size()){//广搜，把这个点可达的所有未标记的点都标记
		u = q.front();
		q.pop();
		if(fre[u]) continue;
		fre[u] = true,cnt ++;
		for(auto v : e[u]) q.push(v);
	}
	return;
}
inline void add_edge(int x,int y,int z,int w){
	int u = num[x][y],v = num[z][w];
	if(fre[u]) return;//这个点已经到达
	if(z && w && z <= n && w <= n && !fre[v]) e[v].push_back(u);//如果连边的这个点未被标记，直接连边
	else free_point(u);//和源点或源点可达的点相连
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i ++) for(int j = 1;j <= n;j ++) num[i][j] = (i - 1) * n + j;//给每个点编一个编号方便操作
	for(int i = 1;i <= q;i ++){
		scanf("%d%d",&r[i],&c[i]);
		getchar(),t[i] = getchar();
		x[r[i]][c[i]] = t[i];//这个点最终形态上的字母
	}
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++) 
			for(int k = 0;k < 4;k ++) 
				if(!x[i][j] || x[i][j] == zt[k]) //这个点没有字母或者字母对应得上当前考虑的方向，那么朝这个方向连边
					add_edge(i,j,i + d[k][0],j + d[k][1]);
	for(int i = q;i;i --){
		ans[i] = cnt;
		for(int k = 0;k < 4;k ++)//这个点上面的字母被删掉了，现在它可以向四个方向走，那就都连边
			add_edge(r[i],c[i],r[i] + d[k][0],c[i] + d[k][1]);
	}
	for(int i = 1;i <= q;i ++)	printf("%d\n",n * n - ans[i]);
	return 0;
} 
```

---

## 作者：Mr_Az (赞：4)

# P11454 [USACO24DEC] 2D Conveyer Belt S

### Algorithm:

图论，思维题。

### Solution:

我们将边框上能走到外面的点与外面的超级点相连，那么问题转化成哪些点可以走到最外面。于是有了一个最初的想法就是每次把图建出来然后 dfs。这样子时间复杂度是$\text{O}(N^2Q)$。

正难则反，我们考虑把图建出来后再倒过去删除边计算答案。但是这样子删除一条边会影响很多点，不好处理。我们以把图反过来建，那这样子题目的意思就是从最外面的超级点能走到里面的哪些点。因为是删边，所以合法的点只会越来越多。

所以我们先对整个图 dfs 一遍，把能到的点染色。之后每把一个点变成 $?$ 的时候，看他周围有没有之前染过色的点并且自身没有被染色，如果有的话那么从这个点继续 dfs 一遍。因为这个点没有被染色所以说明他之前走不到，他周围有黑色点代表说现在可以走得到这个点了，所以继续从这个点开始 dfs 一遍。

时间复杂度即为 $\text{O}(N^2)$，因为每个点只会被染色一次。

**细节**

1. 有可能加入边后的点与外面的超级点相连，此时也需要从这个点 dfs 一遍。
2. $?$ 点的连边为从周围四个点分别连边向他自己。

### Code:

```cpp
int n,m,ans,res[M];
int x[M],y[M],e[N*N][10];
vector<int> out;
char ch[M],mp[N][N];
bool col[N*N];
inline bool valid(int x,int y){return x>=1&&x<=n&&y>=1&&y<=n;}
inline int id(int x,int y){
	if(!valid(x,y)) return n*n+1;//超级点
	return (y-1)*n+x;
}
inline void add(int x,int y){
	if(x==n*n+1){
		out.pb(y);//从超级点出发的点
		return ;
	}
	for(rint i=0;i<10;i++){
		if(e[x][i]==y) return ;
		if(!e[x][i]){e[x][i]=y;break;}
	}
	return ;
}
inline void dfs(int id){
	if(col[id]) return ;
	col[id]=1;ans++;
	for(rint i=0;i<10;i++) if(e[id][i]) dfs(e[id][i]);
}
signed main(){
	read(n,m);
	for(rint i=1,x,y;i<=m;i++){
		read(x,y);cin>>ch[i];
		::x[i]=x;::y[i]=y;
		switch(ch[i]){
			case 'L':{add(id(x,y-1),id(x,y));break;}
			case 'R':{add(id(x,y+1),id(x,y));break;}
			case 'U':{add(id(x-1,y),id(x,y));break;}
			case 'D':{add(id(x+1,y),id(x,y));break;}
		}
		mp[x][y]=ch[i];
	}
	for(rint i=1;i<=n;i++){
		for(rint j=1;j<=n;j++){
			int x=i,y=j;
			if(mp[x][y]) continue;
			add(id(x-1,y),id(x,y));
			add(id(x+1,y),id(x,y));
			add(id(x,y-1),id(x,y));
			add(id(x,y+1),id(x,y));
            //细节2
		}
	}
	for(auto x:out) dfs(x);
	out.clear();
	res[m]=ans;
	for(rint i=m;i>1;i--){
		int x=::x[i],y=::y[i];
		add(id(x-1,y),id(x,y));
		add(id(x+1,y),id(x,y));
		add(id(x,y-1),id(x,y));
		add(id(x,y+1),id(x,y));
        //细节2
		if((col[id(x-1,y)]||col[id(x,y-1)]||col[id(x+1,y)]||col[id(x,y+1)])) dfs(id(x,y));// 看他周围有没有之前染过色的点并且自身没有被染色
		for(auto x:out) dfs(x);// 细节1
		out.clear();
		res[i-1]=ans;
	}
	for(rint i=1;i<=m;i++) printf("%lld\n",n*n-res[i]);
	return 0;
}
```

---

## 作者：Jorisy (赞：3)

好题。

一个 `?` 可以理解为向四个方向连边。

那么删边是不好做的，考虑离线下来倒过来做，这样就是加边。

那么，我们建反图，初始从边界开始搜，中间加边后判断周围有无可以出去的，有则搜出增加的。

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

正难则反，考虑倒序求解。

最末的状态我们可以很轻易的使用 DFS 整出来。问题就在于怎么撤销操作。

其实，我们可以把原问题看成有向图连通性问题。如果 $(x,y)$ 是 $L$ 类型的，那么他和 $(x,y-1)$ 间有一条有向边，$(x,y-1)$ 指向 $(x,y)$。其余类推，然后就变成了每个点和边界的连通性问题。

这时候，我们给每个点及时的打上标记就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, idx, id[1002][1002];
struct node {
	int l, r; char c;
}q[200005];
vector<int>son[1005 * 1005];
constexpr int
dx[] = { 0,0,1,-1 },
dy[] = { 1,-1,0,0 };
bool dne[1005][1005], cn[1005 * 1005];
int ans;
inline void dfs(int p) {
	cn[p] = 1; ans--;
	for (int sp : son[p])
		if (!cn[sp]) dfs(sp);
}
stack<int>ant;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m; ans = n * n + 1;
	for (int i = 1; i <= m; ++i)
		cin >> q[i].l >> q[i].r >> q[i].c,
		dne[q[i].l][q[i].r] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			id[i][j] = ++idx;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (!dne[i][j])
				for (int k = 0; k < 4; ++k)
					son[id[i + dx[k]][j + dy[k]]].
					emplace_back(id[i][j]);
	for (int i = 1; i <= m; ++i)
		if (q[i].c == 'L')
			son[id[q[i].l][q[i].r - 1]].
			emplace_back(id[q[i].l][q[i].r]);
		else if (q[i].c == 'R')
			son[id[q[i].l][q[i].r + 1]].
			emplace_back(id[q[i].l][q[i].r]);
		else if (q[i].c == 'U')
			son[id[q[i].l - 1][q[i].r]].
			emplace_back(id[q[i].l][q[i].r]);
		else if (q[i].c == 'D')
			son[id[q[i].l + 1][q[i].r]].
			emplace_back(id[q[i].l][q[i].r]);
	dfs(0);
	for (int i = m; i > 0; i--) {
		ant.emplace(ans);
		//ctrl-z the change of ith operator
		dne[q[i].l][q[i].r] = 0;
		for (int k = 0; k < 4; ++k)
			son[id[q[i].l + dx[k]][q[i].r + dy[k]]].
			emplace_back(id[q[i].l][q[i].r]);
		bool sbh = 0;
		for (int k = 0; k < 4; ++k)
			if (cn[id[q[i].l + dx[k]][q[i].r + dy[k]]])
				sbh = 1;
		if (sbh && !cn[id[q[i].l][q[i].r]]) dfs(id[q[i].l][q[i].r]);
	}
	while (ant.size())
		cout << ant.top() << endl,
		ant.pop();
}
```

---

## 作者：XGTD (赞：2)

# P11454 [USACO24DEC] 2D Conveyer Belt S 题解

## Preface
好题呀！赛时非常难得的正解完全想出来了，但是犯了一个实现错误，最后总分差七十分痛失金组。

思路主要就是逆向思维加深搜。

## Problem Statement
[p11454](https://www.luogu.com.cn/problem/P11454)

## Solution
首先发现一个点能用当且仅当他能到达一个能用点。所有边界以外的点都能用。

然后发现如果像题目说的一样加限制非常不好搞，每次会影响非常多的点，必须重新深搜一遍，复杂度 $O(Qn^2)$，不行。

于是考虑倒序，先搜出所有限制都加上后哪些点能用。此时因为每次是减去限制发现每个点影响的位置是固定的而且较少，且每去掉一条边只有两种情况：

1. 这个位置去掉这条限制之前就能用。发现根本不用管，因为首先对于他自己答案肯定不变，而它除了自己外只能影响能到达它的点，这些点的答案显然也不变。
2. 这个点本来用不了，此时又有两种可能：
      -    去掉限制使得这个点能用了。这种情况发生的前提是这个点四周的点至少有一个能用，因为现在它可以去到相邻的任意点了，任何一个能用它就能用。如果是这样，因为此点的答案变了，我们需要遍历所有能到它的点 $x$，如果 $x$ 本来不行，改成行，本来就行，显然就可以退出不用再改能到 $x$ 的点了。
      -    去掉限制它还是用不了，显然不用管，把限制去掉就行了不用改答案。

这样下来由于一个点只会被改为能用一次，均摊复杂度 $O(n^2)$ 可以通过。

## Code

```cpp
/*
was just one step away from gold!
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dx[] = {0, 0, 0, 1, -1}, dy[] = {0, 1, -1, 0, 0};
//L = 2, R = 1, U = 4, D = 3
int n, Q, a[2005][2005], use[2005][2005], ans[500006], now;
pair<int, int> qu[500005];
//the direction of each belt, and wheter one is useable
//ans is answer for qth day
int v[2005][2005];
void dfs(int x, int y){
	use[x][y] = 1;
	//only when use was 0 will we visit this x, y
	ans[now]++;
	//another grid freed
	for(int i = 1; i <= 4; i++){
		int oppo;
		if(i == 1)oppo = 2;
		if(i == 2)oppo = 1;
		if(i == 4)oppo = 3;
		if(i == 3)oppo = 4;
		int nx = x + dx[i], ny = y + dy[i];
		//new x and new y		
		if(a[nx][ny] != 0 && a[nx][ny] != oppo){
			continue;
			//this one can't get to x, y
		}
		if(use[nx][ny])continue;
		if(nx > n || ny > n || nx < 1 || ny < 1)continue;
		//out of grid
		dfs(nx, ny);
	}
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>n>>Q;
	for(int i = 1; i <= Q; i++){
		int x, y;
		char z;
		cin>>x>>y>>z;
		qu[i].first = x;
		qu[i].second = y;
		if(z == 'L'){
			a[x][y] = 2;
			//row stay same, colume minus 1
		}
		if(z == 'R'){
			a[x][y] = 1;
			//row stay, colume plus 1
		}
		if(z == 'U'){
			a[x][y] = 4;
			//colume stay same, row minus 1
		}
		if(z == 'D'){
			a[x][y] = 3;
			//row down 1, colume stay
		}
		//0 means all 4 are legal
	}
	now = Q + 1;
	for(int i = 1; i <= n; i++){
		use[0][i] = 1;
		dfs(0, i);
		ans[now]--;//can't count itself, it's out of grid
		use[n + 1][i] = 1;
		dfs(n + 1, i);
		ans[now]--;
		use[i][n + 1] = 1;
		dfs(i, n + 1);
		ans[now]--;
		use[i][0] = 1;
		dfs(i, 0);
		ans[now]--;
		//all out side grids are usable ofcourse
	}
	for(int i = Q; i >= 1; i--){
		//un-build the ith one
		ans[i] = ans[i + 1];
		//one useable next round are all useable now
		a[qu[i].first][qu[i].second] = 0;
		if(use[qu[i].first][qu[i].second]){			
			continue;
		}
		now = i;
		int x = qu[i].first, y = qu[i].second;
		for(int j = 1; j <= 4; j++){
			if(use[x + dx[j]][y + dy[j]]){
				use[x][y] = 1;
				//any direction works, this one works
			}
		}
		if(use[x][y])dfs(x, y);
		//renew every one that can go to this one, they are
		//all useable now
	}
	for(int i = 2; i <= Q + 1; i++){
		cout<<n * n - ans[i]<<endl;
	}
	return 0;
}

```
## Result
[Result](https://www.luogu.com.cn/record/196685662)

## After Thoughts
我犯的实现错误是第一遍带着所有限制深搜时一开始写的是从每一个点开始看能不能搜到边界，能就记为能用。但是这会导致如果有环的话一些本来能用的点被判定为不能用。赛后改为了从边界开始搜，被搜到的都记为能用，立马对了。~~唉，人品不够。~~

---

## 作者：emmoy (赞：2)

这题一眼和连通性相关，就是看能不能连到矩阵外。

我们发现 Farmer John 的一次操作代表着将一个点的 $4$ 连通变成了 $1$ 连通，也就是说我们删掉了与一个点相连的 $3$ 条边。

然后我们发现**连通性**和**删边**这一组关键词似曾相识。

于是我们想到了[[JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)的做法，开始~~挥舞造物主的魔法棒~~时光倒流。

具体来说，我们可以求出将所有操作处理完后的答案，再一步一步的将操作倒过来进行。

这样，我们就可以把删边改成加边，就可以好维护一些。

我们首先考虑如何求出所有操作完后的答案。

我们可以对于边界上的点看看能不能连出边界，如果可以就以它为起点，dfs 遍历所有能到达它的点，并打上标记，打过标记的点就不用遍历了。

然后等于询问的时光倒流，我们就看解放的那个点周围有没有可以走到外界的点（即之前打过标记的点）或是否在边界，如果有，那么这个点与所有能到达它的点都能走到外界。

时间复杂度 $\mathcal{O}(m+n)$。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Q=2e5+10;
int n,m,sum;
int ans[Q];
char s[1010][1010];
int v[1010][1010];
int to[1010][1010][4];
struct Qu{
	int x,y;
	char ch;
}r[Q];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
void dfs(int x,int y){
	v[x][y]=1,sum++;
	for(int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>n||v[xx][yy]) continue;
		if(!to[xx][yy][i^1]) continue;//左^1为右，其他同理，处理能达到x点的点
		dfs(xx,yy);
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) s[i][j]='?';//一开始全部为？
	for(int i=1;i<=m;i++){
		cin>>r[i].x>>r[i].y>>r[i].ch;
		s[r[i].x][r[i].y]=r[i].ch;//m次操作后的矩阵
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){//处理出每个点是否能向每个方向走
            //0代表左，1代表右，2代表上，3代表下
			if(s[i][j]=='?'||s[i][j]=='L') to[i][j][0]=1;
			if(s[i][j]=='?'||s[i][j]=='R') to[i][j][1]=1;
			if(s[i][j]=='?'||s[i][j]=='U') to[i][j][2]=1;
			if(s[i][j]=='?'||s[i][j]=='D') to[i][j][3]=1;
		}
	}
	for(int i=1;i<=n;i++){//处理第一行
		if(v[1][i]||!to[1][i][2]) continue;
		dfs(1,i);
	}
	for(int i=1;i<=n;i++){//处理第n行
		if(v[n][i]||!to[n][i][3]) continue;
		dfs(n,i);
	}
	for(int i=1;i<=n;i++){//处理第一列
		if(v[i][1]||!to[i][1][0]) continue;
		dfs(i,1);
	}
	for(int i=1;i<=n;i++){//处理第n列
		if(v[i][n]||!to[i][n][1]) continue;
		dfs(i,n);
	}
	for(int w=m;w>=1;w--){
		ans[w]=sum;
		int x=r[w].x,y=r[w].y;
		s[x][y]='?';
		for(int i=0;i<4;i++) to[x][y][i]=1;//解放这个点
		if(v[x][y]) continue;
		int p=0;
		for(int i=0;i<4;i++){//看看周围有没有已解放的点或是否在边界
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>n) {p=1;break;}
			if(v[xx][yy]) {p=1;break;}
		}
		if(!p) continue;
		dfs(x,y);//以这个点为起点dfs
	}
	for(int i=1;i<=m;i++) cout<<n*n-ans[i]<<"\n";//sum记录的是能走出去的点，所以要用总点数减去
	return 0;
}
```

---

## 作者：hyk2019 (赞：2)

传送带传送的过程相当于一个点在网格内行走的过程。

对于每一个点，我们可以进行建边。如果传送带都是事先建好的，那么可以直接静态建边，如果是 `U` 就建一条向上的边，是 `D` 就建一条向下的边，`L` 和 `R` 同理，如果是 `?` 就建四个方向的边。

现在问题就是涉及了修改操作。这样，我们也可以给每一个点都建好四个方向的边，同时记录一条边的到期时间 $w$。对于一个在 $i$ 时刻被建好传送带的格子：如果是 `U`，那么向上的边不会到期，其他三条边到期的时间为 $i$；如果是 `D`，那么向下的边不会到期，其他三条边到期的时间为 $i$；`L` 和 `R` 同理；如果是 `?`，那么四个方向的边都不会到期。

对于边界，可以考虑把网格向四个方向都扩充一个格子的区域，即 $N\times N\rightarrow(N+2)\times(N+2)$。在边界外面再设一些点，它们有唯一的指向“超级汇点”的出边，这些边不会到期。

那么现在就可以对每一个点跑**爆改的最短路**了。

因为一条路径到期的时间为这条路径上所有的边的到期时间的最小值，所以爆改的最短路算法应当将边 $i\rightarrow j$ 的松弛操作改为 $dis_j:=\max\{dis_j,\min\{dis_i,w_{i\rightarrow j}\}\}$。

这样，对于每一个点，我们就可以知道什么时候这个点开始变得“不可用”了，每个点的答案是这一遍最短路的“超级汇点”的 $dis$。

时间复杂度 $O(N^2\times N^2\log N)$，显然会超时。

其实优化仅差一步：最终都要到“超级汇点”的，不如将所有的边都反过来，把所有点到“超级汇点”的路径改为“超级汇点”到所有点的路径，再跑最短路即可。

时间复杂度 $O(N^2\log N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int N, Q;
char p[1003][1003];
int s[1003][1003], hd[1003][1003], dis[1003][1003], ans[200005];
bool vis[1003][1003];
struct Edge {
  int tx, ty, n, e;
} es[4200006];
int ecnt = 0;
priority_queue<pair<int, pair<int, int>>> P;
void addEdge(int xa, int ya, int xb, int yb, int ex) {
  es[++ecnt] = {xb, yb, hd[xa][ya], ex};
  hd[xa][ya] = ecnt;
}
int main() {
  scanf("%d%d", &N, &Q);
  for(int i = 1; i <= Q; i ++) {
    int x, y;
    scanf("%d%d ", &x, &y);
    scanf("%c", &p[x][y]);
    s[x][y] = i;
  }
  for(int i = 1; i <= N; i ++)
    for(int j = 1; j <= N; j ++) {
      if(p[i][j] == 'U') {
        addEdge(i - 1, j, i, j, 0x3f3f3f3f);
        addEdge(i + 1, j, i, j, s[i][j]);
        addEdge(i, j - 1, i, j, s[i][j]);
        addEdge(i, j + 1, i, j, s[i][j]);
      } else if(p[i][j] == 'D') {
        addEdge(i - 1, j, i, j, s[i][j]);
        addEdge(i + 1, j, i, j, 0x3f3f3f3f);
        addEdge(i, j - 1, i, j, s[i][j]);
        addEdge(i, j + 1, i, j, s[i][j]);
      } else if(p[i][j] == 'L') {
        addEdge(i - 1, j, i, j, s[i][j]);
        addEdge(i + 1, j, i, j, s[i][j]);
        addEdge(i, j - 1, i, j, 0x3f3f3f3f);
        addEdge(i, j + 1, i, j, s[i][j]);
      } else if(p[i][j] == 'R') {
        addEdge(i - 1, j, i, j, s[i][j]);
        addEdge(i + 1, j, i, j, s[i][j]);
        addEdge(i, j - 1, i, j, s[i][j]);
        addEdge(i, j + 1, i, j, 0x3f3f3f3f);
      } else  {
        addEdge(i - 1, j, i, j, 0x3f3f3f3f);
        addEdge(i + 1, j, i, j, 0x3f3f3f3f);
        addEdge(i, j - 1, i, j, 0x3f3f3f3f);
        addEdge(i, j + 1, i, j, 0x3f3f3f3f);
      }
    }
  for(int i = 1; i <= N + 1; i ++) {
    addEdge(i - 1, 0, i, 0, 0x3f3f3f3f);
    addEdge(i - 1, N + 1, i, N + 1, 0x3f3f3f3f);
    addEdge(0, i - 1, 0, i, 0x3f3f3f3f);
    addEdge(N + 1, i - 1, N + 1, i, 0x3f3f3f3f);
  }
  dis[0][0] = 0x3f3f3f3f;
  P.push({dis[0][0], {0, 0}});
  while(!P.empty()) {
    auto pr = P.top();
    P.pop();
    int pd = pr.first;
    auto pt = pr.second;
    vis[pt.first][pt.second] = true;
    for(int e = hd[pt.first][pt.second]; e; e = es[e].n) {
      if(min(es[e].e, pd) > dis[es[e].tx][es[e].ty] && !vis[es[e].tx][es[e].ty]) {
        dis[es[e].tx][es[e].ty] = min(es[e].e, pd);
        P.push({dis[es[e].tx][es[e].ty], {es[e].tx, es[e].ty}});
      }
    }
  }
  for(int i = 1; i <= N; i ++)
    for(int j = 1; j <= N; j ++)
      if(dis[i][j] <= Q)
        ans[dis[i][j]] ++;
  for(int i = 1; i <= Q; i ++)
    printf("%d\n", ans[i] += ans[i - 1]);
  return 0;
}
```

---

## 作者：masonxiong (赞：2)

# 题目分析

我们定义合法点为能够到达外部的点，那么答案就是 $n^2-可用点数量$。

先想想正着做怎么做。如果一个点能够一步到达外面，那么它可用。若一个点能够到达可用点，那么它可用。

我们可以用 $O(n^2)$ 的 DFS 来处理每个点是否可用。暴力的做法是每次询问计算一次，时间复杂度 $O(n^2q)$ 无法接受。

正难则反。建设传送带的逆过程就是扣掉传送带，也就是把一个点设为 $\texttt?$。我们考虑一次操作带来的影响。

首先原来合法的点现在仍然合法。若这个点现在能到达合法点了，那么将它标为合法，然后向外扩散一圈，看看哪些点能到达这个点，并将它们标记为合法。

由于合法的点不会被重复访问，一个点被遍历的次数是 $O(1)$ 的，所以整体时间复杂度降为 $O(n^2+q)$ 可以通过。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1000 + 5, Maxq = 2e5 + 5;
const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};
int n, q, r, c, cnt;
int dir[Maxn][Maxn];
bool tag[Maxn][Maxn];
tuple<int, int, char> queries[Maxq];
int ans[Maxq];
char t;

void DFS(int x, int y) {
	if (x < 1 || y < 1 || x > n || y > n || tag[x][y])
		return;
	for (int i = 0; i < 4; i++) {
		if (dir[x][y] == -1 || dir[x][y] == i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 1 || ny < 1 || nx > n || ny > n || tag[nx][ny])
				goto checkEnd;
		}
	}
	return;
	checkEnd:
	cnt += tag[x][y] = true;
	for (int i = 0; i < 4; i++)
		DFS(x + dx[i], y + dy[i]);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	memset(dir, -1, sizeof(dir));
	for (int i = 0; i < q; i++) {
		cin >> r >> c >> t;
		switch (t) {
			case 'L': dir[r][c] = 0; break;
			case 'R': dir[r][c] = 1; break;
			case 'U': dir[r][c] = 2; break;
			case 'D': dir[r][c] = 3; break;
		}
		queries[i] = make_tuple(r, c, t);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			DFS(i, j);
	for (int i = q - 1; i >= 0; i--) {
		tie(r, c, t) = queries[i];
		ans[i] = n * n - cnt;
		dir[r][c] = -1;
		DFS(r, c);
	}
	for (int i = 0; i < q; i++)
		cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：lhz2022 (赞：1)

一个非常套路的做法就是离线然后倒序修改。

为什么？因为我们发现如果要支持在线删边似乎会很难，但是如果倒着来的话，只需要把删边改成加边，就很好做了。由于在倒序下一个点从始至终只要是可以达到的，那么之后都可以被达到。可以添加一个标记十分可以达到。由于每个点最多被标记一次，进队一次，所以复杂度是 $O(N^2+Q)$。

于是我们的算法步骤就是这样的：

- 初始化：把操作倒序，使这个方阵变成所有操作操作完成的情况，进行一遍搜索，记搜索出可达到的总数为 $ans0$。记答案数组的最后一项为 $n^2-ans0$。
- 对于每一个操作，把方阵对应位置的传送带变成未知（即四面都可）。如果这个传送带的四个与之相邻的传送带也可以到达，那么就从这个传送带开始进行搜索。每搜到一个可到达的格点，就使 $ans0$ 自增 $1$。将操作完毕后将此时的 $n^2-ans0$ 存入一个答案数组。
- 输出答案数组。

[代码](https://www.luogu.com.cn/paste/t6a5s88a)

由于这一题的细节比较多，于是我提供了数据生成工具，可以用来对拍。

[数据生成](https://www.luogu.com.cn/paste/ohxfe0xp)

---

## 作者：Milky_Cat (赞：1)

场上看到这题笑了，因为我打过 CF2034。

这题和 CF2034C 唯一的区别是，倒着跑 CF2034C 的 dfs，跑 $Q$ 轮。

因为我没有写 CF2034C 的题解，所以大致讲下做法：标记边界上能跑出去的格子，用这些格子 dfs 去更新其他格子。

在倒着跑的过程中可以稍微判断一下，使得每个格子只被更新一次，这样复杂度就是 $O(N^2)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, dng[1005][1005], cnt;
char mp[1005][1005];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
string qwq = " UDLR";
int X[200005], Y[200005], res[200005];
char ch[200005];
void dfs(int x, int y){
	for (int i = 1; i <= 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || nx > n || ny < 1 || ny > n)
			continue;
		if (dng[nx][ny])
			continue;
		if (mp[nx][ny] == qwq[i] || mp[nx][ny] == '?'){
			dng[nx][ny] = 1;
			cnt--;
			dfs(nx, ny);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i <= n + 1; i++)
		for (int j = 0; j <= n + 1; j++){
			if (i >= 1 && i <= n && j >= 1 && j <= n)
				dng[i][j] = 0;
			else
				dng[i][j] = 1;
		}
	cnt = n * n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mp[i][j] = '?';
	for (int i = 1; i <= m; i++){
		cin >> X[i] >> Y[i] >> ch[i];
		mp[X[i]][Y[i]] = ch[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++){
			if (mp[i][j] == 'U' && i == 1)
				dng[i][j] = 1, cnt--;
			if (mp[i][j] == 'D' && i == n)
				dng[i][j] = 1, cnt--;
			if (mp[i][j] == 'L' && j == 1)
				dng[i][j] = 1, cnt--;
			if (mp[i][j] == 'R' && j == n)
				dng[i][j] = 1, cnt--;
			if (mp[i][j] == '?' && (i == 1 || i == n || j == 1 || j == n))
				dng[i][j] = 1, cnt--;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dng[i][j])
				dfs(i, j);
	res[m] = cnt;
	for (int i = m - 1; i >= 1; i--){
		mp[X[i + 1]][Y[i + 1]] = '?';
		if (dng[X[i + 1]][Y[i + 1]]){
			dfs(X[i + 1], Y[i + 1]);
			res[i] = cnt;
			continue;
		}
		bool chk = 0;
		for (int j = 1; j <= 4; j++){
			int nx = X[i + 1] + dx[j], ny = Y[i + 1] + dy[j];
			if (dng[nx][ny]){
				dng[X[i + 1]][Y[i + 1]] = 1;
				cnt--;
				break;
			}
		}
		if (dng[X[i + 1]][Y[i + 1]])
			dfs(X[i + 1], Y[i + 1]);
		res[i] = cnt;
		if (!cnt)
			break;
	}
	for (int i = 1; i <= m; i++)
		cout << res[i] << "\n";
	return 0;
}
```

---

## 作者：Greenzhe (赞：1)

观察数据范围，$Q \le 2\times 10^5$，说明每次询问需要在均摊时间复杂度不超过 $O(\log{n})$ 的时间内回答。

先来考虑：一个『一定不可用的』方格（即无论怎么安排 $\texttt ?$ 的方向都不可用），需要满足什么条件？

- 如果是方向方格，需要满足以下条件之一：

1. 该方格在一个环中；
2. 该方格指向的路径通向一个环；
3. 该方格通向一个『一定不可用的』$\texttt ?$ 方格。

- 那什么样的 $\texttt ?$ 方格是『一定不可用的』呢？考虑该方格与其相邻的 $\texttt ?$ 组成的**联通块**，需要满足以下全部两点：

1. 联通块不与边界相邻；
2. 联通块外围与其直接相邻的所有方向方格，要么已经不可用，要么**通向联通块本身**。

对于可用方格满足的条件，可仿照上例得出。

上述内容可以参照样例三理解。倒数第五次操作前，局面是这样的：

|$\ $||||
|:-:|:-:|:-:|:-:|
||$\rightarrow$|$\rightarrow$|$\downarrow$|
|$\color{red}\downarrow$|$\texttt ?$|$\texttt ?$|$\downarrow$|
||$\uparrow$|$\leftarrow$|$\leftarrow$|

可以看到，中间被“圈”起来的联通块，由于经过左侧“$\color{red}\downarrow$”仍然可以通向边界，所以不是『一定不可用的』。

然而经过操作，局面变成了这样：

|$\ $||||
|:-:|:-:|:-:|:-:|
||$\rightarrow$|$\rightarrow$|$\downarrow$|
|$\downarrow$|$\color{red}\texttt ?$|$\texttt ?$|$\downarrow$|
|$\rightarrow$|$\uparrow$|$\leftarrow$|$\leftarrow$|

我们可以发现，该联通块周围的方向方格，都会通向“$\color{red}\texttt?$”，因此该联通块内部的方格无论如何都会绕回自己，是『一定不可用的』。

---

现在我们得到了关于一个方格可用状态的简洁判定方法。

对照上例，发现如果要**实时维护**一个方格的可用状态，对于方向方格是显然的；然而对于 $\texttt ?$ 方格，需要判定所在的联通块与外围联通块是否断开，有些困难。怎么办呢？

> 考虑套路地**离线倒序处理询问**。

有了上述思想，对于每次更新，我们就可以直接合并 $\texttt ?$ 的联通块。具体地，每回退一个方向方格成为 $\texttt ?$ 方格，就进行 flood-fill 检查能否使得新的方格变得可用。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005, M = 2e5 + 5;
const int di[] = {0, 0, 0, -1, 1};
const int dj[] = {0, -1, 1, 0, 0};

int n, q, res = 0, tr[128];  // res：记录可用方格的个数
int Free[N][N], dir[N][N];
// Free[i][j]=-1 表示可用
char s[3];

struct attempt {
    int x, y, d, ans;
} qry[M];

void dfs(int i, int j) {  // 从 (i,j) 开始覆盖新的可用方格
    Free[i][j] = -1;
    res++;
    for (int k = 1; k <= 4; ++k) {
        int ti = i + di[k], tj = j + dj[k];
        if (ti < 1 || ti > n || tj < 1 || tj > n) continue;
        int td = dir[ti][tj];
        if (ti + di[td] == i && tj + dj[td] == j || !td)
            if (~Free[ti][tj])
                dfs(ti, tj);  // 标记指向它的路径上的所有方格，
                              // 以及在一个联通块中的 ? 方格
    }
}

int main() {
    tr['L'] = 1;
    tr['R'] = 2;
    tr['U'] = 3;
    tr['D'] = 4;
    scanf("%d%d", &n, &q);
    for (int i = 1, x, y; i <= q; ++i) {
        scanf("%d%d%s", &x, &y, s);
        qry[i] = {x, y, tr[s[0]], 0};
        dir[x][y] = qry[i].d;  // dir 记录当前方格的方向，未建则记为 0
    }
    for (int i = 0; i <= n + 1; ++i) {  // 标记与边界相邻的方格
        dfs(0, i);
        dfs(n + 1, i);
        dfs(i, 0);
        dfs(i, n + 1);
        res -= 4;
    }
    for (int i = q; i >= 1; --i) {
        qry[i].ans = n * n - res;
        dir[qry[i].x][qry[i].y] = 0;  // 注意每次修改以后要标记未建
        if (Free[qry[i].x][qry[i].y]) continue;
        bool now =
            false;  // 如果相邻的方格中有至少一个方格可用，则修改过的方格可用
        for (int k = 1; k <= 4; ++k) {
            int ti = qry[i].x + di[k], tj = qry[i].y + dj[k];
            if (Free[ti][tj]) now = true;
        }
        if (now) dfs(qry[i].x, qry[i].y);
    }
    for (int i = 1; i <= q; ++i) printf("%d\n", qry[i].ans);
    return 0;
}
```

由于一个点至多被标记一次可用，所以算法的时间复杂度是 $O(n^2+q)$ 的，可以通过。

---

## 作者：I_will_AKIOI (赞：1)

赛时想到了倒序处理询问，但是没想到接下来怎么做，痛失金组。

首先考虑求出能到达边界的点的数量，用 $n^2$ 减去他就是答案。接着发现如果这个节点是 $\{\texttt{L,R,U,D}\}$ 中的一个，那么只能往一个方向走，而对于 $\texttt{?}$ 节点，则四个方向都可以走，所以问号的范围是比较大的，不难想到给询问倒序处理。然后会还有一个性质，如果一个格子的四周有能到达边界的格子，那么这个格子也能到达边界。

所以对于每个更新的格子 $(x,y)$，扫一遍他周围的四个格子 $(x-1,y),(x+1,y),(x,y-1),(x,y+1)$，如果有格子能到达边界，那么 $(x,y)$ 也能到达边界。接着对 $(x,y)$ 进行 DFS，搜索有哪些之前不能到达边界的格子能到达 $(x,y)$，给这些格子标记为能到达，同时记录一下能到达边界格子的数量，最后答案倒序输出。

发现每个点只会被 DFS 搜索到一次，接着就会因为能到达边界而不会再被搜索到，所以时间复杂度为 $O(n^2+q)$。

```cpp
#include<bits/stdc++.h>
#define N 1005
#define M 200005
using namespace std;
int n,q,cnt,x[M],y[M],ans[M];
char c[N][N];
bool ok[N][N];
void dfs(int x,int y)//dfs搜索能到达(x,y)点的个数
{
  ok[x][y]=1;
  cnt++;
  int nx=x+1,ny=y;
  if(nx<=n&&ok[nx][ny]==0&&(c[nx][ny]=='?'||c[nx][ny]=='U')) dfs(nx,ny);
  nx=x-1,ny=y;
  if(nx>=1&&ok[nx][ny]==0&&(c[nx][ny]=='?'||c[nx][ny]=='D')) dfs(nx,ny);
  nx=x,ny=y+1;
  if(ny<=n&&ok[nx][ny]==0&&(c[nx][ny]=='?'||c[nx][ny]=='L')) dfs(nx,ny);
  nx=x,ny=y-1;
  if(ny>=1&&ok[nx][ny]==0&&(c[nx][ny]=='?'||c[nx][ny]=='R')) dfs(nx,ny);
  return;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>n>>q;
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c[i][j]='?';
  for(int i=1;i<=q;i++)
  {
    char op;
    cin>>x[i]>>y[i]>>op;
    c[x[i]][y[i]]=op;
  }
  for(int i=1;i<=n;i++) if(ok[1][i]==0&&(c[1][i]=='?'||c[1][i]=='U')) dfs(1,i);
  for(int i=1;i<=n;i++) if(ok[n][i]==0&&(c[n][i]=='?'||c[n][i]=='D')) dfs(n,i);
  for(int i=1;i<=n;i++) if(ok[i][1]==0&&(c[i][1]=='?'||c[i][1]=='L')) dfs(i,1);
  for(int i=1;i<=n;i++) if(ok[i][n]==0&&(c[i][n]=='?'||c[i][n]=='R')) dfs(i,n);
  //预处理出开始情况能到达边界点的个数
  ans[q]=n*n-cnt;
  for(int i=q;i>=2;i--)
  {
    c[x[i]][y[i]]='?';
    if(ok[x[i]][y[i]]==0)
    {
      int nx=x[i]+1,ny=y[i];
      if(nx>n||ok[nx][ny]) ok[x[i]][y[i]]=1;
      nx=x[i]-1,ny=y[i];
      if(nx<1||ok[nx][ny]) ok[x[i]][y[i]]=1;
      nx=x[i],ny=y[i]+1;
      if(ny>n||ok[nx][ny]) ok[x[i]][y[i]]=1;
      nx=x[i],ny=y[i]-1;
      if(ny<1||ok[nx][ny]) ok[x[i]][y[i]]=1;
      //在(x,y)的周围查找是否有能到达边界的格子（或者(x,y)在边界上）
      if(ok[x[i]][y[i]]) dfs(x[i],y[i]);//如果有，进行DFS搜索
    }
    ans[i-1]=n*n-cnt;
  }
  for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
  return 0;
}
```

---

## 作者：_Jocularly_ (赞：1)

图论题。首先很明显，抽象一下模型，假设没有问号，那么所有的符号都可以看成两点之间的有向边，那么考虑问号。发现问号具有无限的可能，也就是说问号可以去到任何一个方向，因此建四个方向的边。其次考虑应用到题面中，发现如果正着做，就要把一个问号变成字母，也就是把四条边中的三条删掉，但是显然无法便捷删边，那么考虑正难则反。

此时如果反着进行，那么变成了把字母变成问号，直接加三条边即可，每次加完边之后直接处理。如果一个点发生了变化，那么可能会影响周围的点，从这个点出发遍历处理新的答案，看看当前现在是能走出去的，最后把答案保存下来逆序输出即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
struct node{
    int x,y;
    int num;
}a[1000005];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
vector<pair<int,int>> g[1005][1005];
int vis[1005][1005];
int flag[1005][1005];
int now;
vector<int> res;
int tot;
int ans[1000005];
bool inbound(int i,int j){
    return !(i <= 0 || j <= 0 || i > n || j > n);
}
void dfs(int x,int y){
    now ++;
    flag[x][y] = 1;
    for(auto& [p,q] : g[x][y]){
        int nx = x + p;
        int ny = y + q;
		if(flag[nx][ny]) continue;
        dfs(nx,ny);
    }
}
void add(int x,int y,int dir){
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if(!inbound(nx,ny)){
        if(!flag[x][y]) dfs(x,y);
    }else{
        g[nx][ny].push_back(make_pair(dx[dir^1],dy[dir^1]));
        if(!flag[x][y] && flag[nx][ny]) dfs(x,y);
    }
}
signed main(){
	cin >> n >> q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            vis[i][j] = -1;
        }
    }
	for(int i=1;i<=q;i++){
        int x,y;
        char c;
        cin >> x >> y >> c;
        a[i].x = x;
        a[i].y = y;
        if(c == 'U') a[i].num = 0;
        else if(c == 'D') a[i].num = 1;
        else if(c == 'L') a[i].num = 2;
        else if(c == 'R') a[i].num = 3;
        vis[x][y] = a[i].num;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(vis[i][j] != -1) add(i,j,vis[i][j]);
            else{
                for(int k=0;k<4;k++){
                    add(i,j,k);
                }
            }
        }
    }
    for(int i=q;i>=1;i--){
        res.push_back(pow(n,2) - now);
        for(int j=0;j<4;j++){
            if(j == a[i].num) continue;
            add(a[i].x,a[i].y,j);
        }
    }
    for(int val : res){
        ans[++ tot] = val;
    }
    for(int i=tot;i>=1;i--){
        cout << ans[i] << endl;
    }
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：1)

## 题目大意

一个 $n \times n$ 方阵，方阵中每个点向其上下左右点连边（如果连向位置不在方阵中也连，下把这些不在方阵中的点称为“边界点”）。

$q$ 此操作每次指定一个不重复的点，并删掉它连向外部的四条边中的三条边。问操作完还有几个点能走到“边界点”。

## 题解

如果直接模拟的话就是我刚刚说的大意，不过看起来这要做到 $O(n^2+q)$ 比较难，我们考虑反着做。

反着做就要先把最终结局的连边弄好，而且要把边反向，这样最开始就能把“边界点”变成“超级源点”跑 `bfs`，就能确定哪些点初始可达，并打上标记。

接着依次撤销操作，相当于每次加三条边。如果这个点没被标记，且这三条边连接的另一端被标记了，那么把这个点标记上，并从这个点开始 `bfs`。

由于每个点只会标记一次，所以这样做是 $O(n^2+q)$ 的复杂度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2005,Q=2e5+5;
bool vis[N][N],vis2[N*N];
vector<int>e[N*N];
int n,q,ans,an[Q];
inline int id(int x,int y){return x*(n+1)+y;}
struct node{
    int x,y,type;
}ask[Q];

vector<int>s;
queue<int>qu;

int cnt=0;

inline void bfs(){
    //cerr<<"round:"<<++cnt<<'\n';
    for(auto x:s)qu.push(x),vis2[x]=1;
    while(!qu.empty()){
        int x=qu.front();qu.pop();
        for(auto v:e[x]){
            if(vis2[v])continue;
            //cerr<<v/n<<' '<<v%n<<" from"<<x/n<<' '<<x%n<<'\n';
            vis2[v]=1;
            qu.push(v);
            ++ans;
        }
    }
    s.clear();
}

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    cin>>n>>q;
    for(int i=1;i<=q;++i){
        int x,y;char c;
        cin>>x>>y>>c;
        switch(c){
            case 'U':ask[i].type=1;e[id(x-1,y)].push_back(id(x,y));break;
            case 'D':ask[i].type=2;e[id(x+1,y)].push_back(id(x,y));break;
            case 'L':ask[i].type=3;e[id(x,y-1)].push_back(id(x,y));break;
            case 'R':ask[i].type=4;e[id(x,y+1)].push_back(id(x,y));break;
            default:break;
        }
        ask[i].x=x,ask[i].y=y;
        vis[x][y]=1;
    }
    for(int x=1;x<=n;++x)for(int y=1;y<=n;++y)if(!vis[x][y]){
        e[id(x-1,y)].push_back(id(x,y));
        e[id(x+1,y)].push_back(id(x,y));
        e[id(x,y-1)].push_back(id(x,y));
        e[id(x,y+1)].push_back(id(x,y));
    }
    for(int i=1;i<=n;++i)s.push_back(id(0,i)),s.push_back(id(i,0)),
                         s.push_back(id(n+1,i)),s.push_back(id(i,n+1));
    bfs();
    an[q]=ans;
    for(int i=q;i>1;--i){
        int x=ask[i].x,y=ask[i].y;
        e[id(x-1,y)].push_back(id(x,y));
        e[id(x+1,y)].push_back(id(x,y));
        e[id(x,y-1)].push_back(id(x,y));
        e[id(x,y+1)].push_back(id(x,y));
        if(vis2[id(x-1,y)])s={id(x-1,y)},bfs();
        if(vis2[id(x+1,y)])s={id(x+1,y)},bfs();
        if(vis2[id(x,y-1)])s={id(x,y-1)},bfs();
        if(vis2[id(x,y+1)])s={id(x,y+1)},bfs();
        an[i-1]=ans;
    }
    for(int i=1;i<=q;++i)cout<<n*n-an[i]<<'\n';
    return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

$ n \times n $ 的方阵，若所有位置均已填写方向，定义一个格子为拘束格子当且仅当从这个格子出发每次按照格子上所示的方向最后会一直困在方阵内出不去。方阵一开始是空的，对于每次方向填写（这个格子填写前是空格），你需要求出：

* 在空白格子可以被任意填写的情况下，方阵最少会存在多少个拘束方格。

$ 1 \le n \le 1000 $。

## 知识点及评析

* 【6】各种单源最短路算法

本题考察选手对于图上算法的掌握以及对于 DFS 树性质的理解。

## 分析

显然如果一个方格是非拘束方格那么必然存在一条通向方阵以外的路线使得：

* 对于从空白方格开始的一步，向四个方向中一个方向走；
* 对于填写方向的方格开始的一步，向已经填写好的方向行走。

我们考虑，如果建一张由所有可以行走的方向构成的有向图的话，本质上我们的所有在这张图上可以到达方阵以外的格子（这个格子是非拘束方格的必要条件）就相当于把所有边反向的图上所有方阵以外可以到达的格子，本质上可以构造一棵以方阵以外为根的 DFS 树（性质是在原图上每个格子只有一条需要被保留的边即可保证这些 DFS 树上的格子可以到达方阵以外），即意味着存在一种填写方向的方案使得所有可能为非拘束方格的格子都是非拘束方格，而询问操作的填写方向本质上相当于删除三条边，故转化为有向图删边后询问有多少个点可达特定结点的问题，可以将每条边打上被删除时刻的时间戳，建反向边后，用最短路算法求出矩阵以外到达每个结点的经历的所有时间戳最小值的最大值即从这个时刻开始这个结点永远无法到达在原图上到达矩阵以外。

时间复杂度为 $ O(kn^2) $，因为图是自己建的所以 SPFA 卡不掉，$ k $ 为 SPFA 的小常数。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
#include <queue>
#define jsx pair<int, int>
using namespace std;
const int N = 1005;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, q;
int maze[N][N];
int tim[N][N];
int vis[N * N];
int dis[N * N];
int cf[N * N];
inline void read(int &Rd) {
	Rd = 0;
	int Fh = 1;
	char ch = '#';
	while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if(ch == '-') Fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') Rd = (Rd << 1) + (Rd << 3) + ch - '0', ch = getchar();
	Rd *= Fh;
}
inline void write(long long Rd) {
	if(Rd == 0) {
		putchar('0');
		return;
	} 
	char wri[25];
	int lt = 0;
	while(Rd) {
		wri[++lt] = Rd % 10;
		Rd /= 10;
	}
	while(lt) {
		putchar(wri[lt--] + '0');
	}
}
inline int id(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > n) return 0;
	return (x - 1) * n + y;
}
vector<pair<int, int> > g[N * N];
void setedge(int x, int y, int k, int v) {
	int tx = x + dir[k][0];
	int ty = y + dir[k][1];
	int getid = id(tx, ty);
	int xx = id(x, y);
	g[getid].push_back((jsx){xx, v});
}
queue<int> que;
int main() {
	read(n), read(q);
	int u, v;
	char ch;
	memset(maze, -1, sizeof(maze));
	for(int qi = 1; qi <= q; qi++) {
		read(u), read(v);
		cin >> ch;
		tim[u][v] = qi;
		maze[u][v] = (ch == 'U') ? 0 : ((ch == 'D') ? 1 : ((ch == 'L') ? 2 : ((ch == 'R' ? 3 : 4))));
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(maze[i][j] == -1) {
				for(int k = 0; k < 4; k++) {
					setedge(i, j, k, q + 1);
				}
			} else {
				setedge(i, j, maze[i][j], q + 1);
				for(int k = 0; k < 4; k++) {
					if(k != maze[i][j]) setedge(i, j, k, tim[i][j]);
				}
			}
		}
	}
	que.push(0);
	vis[0] = 1;
	dis[0] = q + 1;
	while(!que.empty()) {
		u = que.front();
		que.pop();
		vis[u] = 0;
		for(int i = 0; i < g[u].size(); i++) {
			v = g[u][i].first;
			int w = g[u][i].second;
			if(min(dis[u], w) > dis[v]) {
				dis[v] = min(dis[u], w);
				if(!vis[v]) que.push(v), vis[v] = 1;
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cf[dis[id(i, j)]]++;
		}
	}
	for(int i = 2; i <= q; i++) cf[i] += cf[i - 1];
	for(int i = 1; i <= q; i++) write(cf[i]), puts("");
	return 0;
}
```

---

## 作者：greater_than (赞：0)

### 思路
考虑倒着做，先用 $ \Theta(N) $ 的时间复杂度，连好边。问号就往四周都连边，如果连到外面了就统一连到一个点上。连完后，每次从那个点往里面进行广搜，每搜到一个点 $ ans $ 加一，答案就为 $ n^2 - ans $。对于每一次从后往前做，会把一个确定的符号变为 `?` 即要往另外的三边进行连边，假如连好边后如图:
![](https://cdn.luogu.com.cn/upload/image_hosting/jszypowv.png)
要把 `L` 删掉后，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/7qu0b7q1.png)
用 `g` 往回搜索用 $ ans $ 减去搜到的点即可（单向边，反着存）。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct G{
	int v,nxt;
}E[10000005];
struct node{
	char ch;
	int x, y, ans;
}q[1000005];
char ch;
int T,n,c,cnt,ans,a[1000005],h[1000005];
bitset<1000005>f,flag;
int gx(int i,int j){
	if(i==0||i==n+1||j==0||j==n+1)return 0;
	return (i-1)*n+j;
}
void add(int u,int v){E[++c].v=v,E[c].nxt=h[u],h[u]=c;}
inline void dg1(int u){
	for(int i=h[u];i;i=E[i].nxt){
		int v=E[i].v;
		if(!flag[v]){
			ans++;
			flag[v]=1;
			dg1(v);
		}
	}
}
void dg2(int u){
	queue<int>q;
	q.push(u);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=E[i].nxt){
			int v=E[i].v;
			if(!flag[v]){
				ans++;
				flag[v]=1;
				q.push(v);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>T;
	for(int i=1;i<=T;i++){
		cin>>q[i].x>>q[i].y>>ch;
		if(ch=='L')a[gx(q[i].x,q[i].y)]=1;
		if(ch=='R')a[gx(q[i].x,q[i].y)]=2;
		if(ch=='U')a[gx(q[i].x,q[i].y)]=3;
		if(ch=='D')a[gx(q[i].x,q[i].y)]=4;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(a[gx(i,j)]){
				switch(a[gx(i,j)]){
					case 1:add(gx(i,j-1),gx(i,j));break;
					case 2:add(gx(i,j+1),gx(i,j));break;
					case 3:add(gx(i-1,j),gx(i,j));break;
					case 4:add(gx(i+1,j),gx(i,j));break;
				}
			}
			else add(gx(i,j-1),gx(i,j)),add(gx(i,j+1),gx(i,j)),add(gx(i-1,j),gx(i,j)),add(gx(i+1,j),gx(i,j));
		}
	flag[0]=1;
	dg1(0);
	for(int t=T;t>=1;t--){
		q[t].ans=n*n-ans;
		if(t==1) break;
		int i=q[t].x,j=q[t].y;
		switch(a[gx(i,j)]){
			case 1:
				add(gx(i,j+1),gx(i,j)),add(gx(i-1,j),gx(i,j)),add(gx(i+1,j),gx(i,j));
				if(flag[gx(i,j+1)]||flag[gx(i-1,j)]||flag[gx(i+1,j)]){
					if(!flag[gx(i,j)])ans++;
					flag[gx(i,j)]=1;
					f[gx(i,j)]=1;
					dg2(gx(i,j));
				}
				break;
			case 2:
				add(gx(i,j-1),gx(i,j)),add(gx(i-1,j),gx(i,j)),add(gx(i+1,j),gx(i,j));
				if(flag[gx(i,j-1)]||flag[gx(i-1,j)]||flag[gx(i+1,j)]){
					if(!flag[gx(i, j)])ans++;
					flag[gx(i,j)]=1;
					f[gx(i,j)]=1;
					dg2(gx(i,j));
				}
				break;
			case 3:
				add(gx(i,j-1),gx(i,j)),add(gx(i,j+1),gx(i,j)),add(gx(i+1,j),gx(i,j));
				if(flag[gx(i,j+1)]||flag[gx(i,j-1)]||flag[gx(i+1,j)]){
					if(!flag[gx(i,j)])ans++;
					flag[gx(i,j)]=1;
					f[gx(i,j)]=1;
					dg2(gx(i,j));
				}
				break;
			case 4:
				add(gx(i,j-1),gx(i,j)),add(gx(i,j+1),gx(i,j)),add(gx(i-1,j),gx(i,j));
				if(flag[gx(i,j+1)]||flag[gx(i,j-1)]||flag[gx(i-1,j)]){
					if(!flag[gx(i,j)])ans++;
					flag[gx(i,j)]=1;
					f[gx(i,j)]=1;
					dg2(gx(i,j));
				}
				break;
		}
	}
	for(int i=1;i<=T;i++)cout<<q[i].ans<<"\n";
}

```

---

## 作者：linjunye (赞：0)

### 暴力思路
按照题意模拟即可，我这里使用泛洪算法，从边界开始泛洪，若这个点的相邻点可以连接到这个点，那么就搜过去。

具体见代码。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1010;
const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};
const char ff[]={'D','R','U','L'};//reverse
int n,q;
int x,y;
char op;
char ch[N][N];
bool vis[N][N];
int ans;
struct Node{
	int x,y;
	Node(int x,int y):
		x(x),y(y)
	{}
};
void bfs(){//Flood-fill 
	queue<Node>q;
	ans=n*n;
	for(int i=1;i<=n;i++){
		q.push(Node(0,i));q.push(Node(n+1,i));
		q.push(Node(i,0));q.push(Node(i,n+1));
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			vis[i][j]=0;
	while(!q.empty()){
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>n)continue;
			if(ch[nx][ny]!='?'&&ch[nx][ny]!=ff[i])continue;//(nx,ny)不连通到(x,y) 
			if(vis[nx][ny])continue;
			ans--;//这个点可以出去
			vis[nx][ny]=1;
			q.push(Node(nx,ny));
		}
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ch[i][j]='?';//初始化
	while(q--){
		cin>>x>>y;
		cin>>op;
		ch[x][y]=op;
		bfs();
		cout<<ans<<"\n";
	}
	return 0;
}
```

时间复杂度 $\Theta(n^3)$，可以过前七组数据。

### 正解

写暴力的过程中，我们发现如果要正常实现 $\Theta(n^2)$ 的算法，近乎是做不到的。

所以我们考虑倒序做。

倒序操作就是每次把一个点的方向改为任意方向，似乎能发掘更多的思路。

把一个点的方向改为任意方向能干什么？当然是可以连原来连通不了的一些部分啊！

那就好做了，继续保持暴力的做法。先在最终状态下进行泛洪，并确定连通情况。接下来，每一次操作，都去搜相邻点。若其中有一个相邻点能连通外面，那么所有的块都可以连通，这可以用搜索处理。

思路似乎很正确，那就来分析一下复杂度：

泛洪很简单，一个点最多会被进队一次，总体为 $\Theta(n^2)$。

接下来的搜索也是一样，每个点最多会被标记一次，总体为 $\Theta(n^2)$。

最终复杂度即为 $\Theta(n^2)$。

### 代码

这个做法细节很多，很考验代码能力。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1010;
const int M=200010;
const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};
const char f[]={'U','L','D','R'};//ordinary
const char ff[]={'D','R','U','L'};//reverse
int n,q;
int lt[N][N];
int res[M];
int x[M],y[M];
char op[M];
char ch[N][N];
int ans;
int dot(int x,int y){
	return (x-1)*n+y;
}
struct Node{
	int x,y;
	Node(int x,int y):
		x(x),y(y)
	{}
};
void bfs(){
	queue<Node>q;
	ans=n*n;
	for(int i=1;i<=n;i++){
		q.push(Node(0,i));q.push(Node(n+1,i));
		q.push(Node(i,0));q.push(Node(i,n+1));
	}
	while(!q.empty()){
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>n)continue;
			if(ch[nx][ny]!='?'&&ch[nx][ny]!=ff[i])continue;
			if(lt[nx][ny])continue;
			lt[nx][ny]=1;
			ans--;
			q.push(Node(nx,ny));
		}
	}
	return;
}
void dfs(int x,int y){
	if(!lt[x][y])ans--;
	lt[x][y]=1;
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx<=0||ny>n||ny<=0||ny>n)continue;
		if(ch[nx][ny]!='?'&&ch[nx][ny]!=ff[i])continue;
		if(lt[nx][ny])continue;
		dfs(nx,ny);
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ch[i][j]='?';
	for(int i=1;i<=q;i++){
		cin>>x[i]>>y[i];
		cin>>op[i];
		ch[x[i]][y[i]]=op[i];
	}
	bfs();
	res[q]=ans;
	for(int i=q;i>=2;i--){
		ch[x[i]][y[i]]='?';
		int fff=0;
		for(int k=0;k<4;k++){
			int nx=x[i]+dx[k];
			int ny=y[i]+dy[k];
			if(nx<=0||nx>n||ny<=0||ny>n){
				fff=1;
				continue;
			}
			fff|=lt[nx][ny];
		}
		if(fff)dfs(x[i],y[i]);
		res[i-1]=ans;
	}
	for(int i=1;i<=q;i++)cout<<res[i]<<"\n";
	return 0;
}
```

---

