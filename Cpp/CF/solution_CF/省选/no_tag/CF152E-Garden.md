# Garden

## 题目描述

Vasya has a very beautiful country garden that can be represented as an $ n×m $ rectangular field divided into $ n·m $ squares. One beautiful day Vasya remembered that he needs to pave roads between $ k $ important squares that contain buildings. To pave a road, he can cover some squares of his garden with concrete.

For each garden square we know number $ a_{i}_{j} $ that represents the number of flowers that grow in the square with coordinates $ (i,j) $ . When a square is covered with concrete, all flowers that grow in the square die.

Vasya wants to cover some squares with concrete so that the following conditions were fulfilled:

- all $ k $ important squares should necessarily be covered with concrete
- from each important square there should be a way to any other important square. The way should go be paved with concrete-covered squares considering that neighboring squares are squares that have a common side
- the total number of dead plants should be minimum

As Vasya has a rather large garden, he asks you to help him.

## 样例 #1

### 输入

```
3 3 2
1 2 3
1 2 3
1 2 3
1 2
3 3
```

### 输出

```
9
.X.
.X.
.XX
```

## 样例 #2

### 输入

```
4 5 4
1 4 5 1 2
2 2 2 2 7
2 4 1 4 5
3 2 1 7 1
1 1
1 5
4 1
4 4
```

### 输出

```
26
X..XX
XXXX.
X.X..
X.XX.
```

# 题解

## 作者：mcqueen (赞：10)

思路来源于$Codeforces$的黑红名选手$rng\_58$的代码。

**一步一步来**

题目要让我们求出所有题目给出的点联通的最小花费。  
“最小花费”？那我们可以想到什么？最短路？DP？  
别急，再看一眼数据范围：
$$
k \le 7
$$
$k$的范围这么小，所以我们完全可以把$k$**状压**。

好，那我们先口胡一个思路：

$dp[mask]$表示达到$mask$状态所需要的最小花费（二进制数$mask$中$0$表示这个点没在这个联通块，$1$表示在这个联通块）

看起来好像没问题。

但如何转移呢？  
我们知道，转移的过程就是合并两个点集的过程，那怎么合并？  
我们发现，合并两个点集可能可以从不同的点（这里的点指有花朵的点，不是指有大厦的点）来合并，这样怎么转移就很迷了。

好吧，这样好像不行。那怎么办呢？

首先，由于$k \le 7$，所以$mask$的规模最多达到$2^7=128$(~~你确定出题人会让你在Div 2的E题里让你写一个O(128)的DP算法？~~）那我们可以放心大胆再给这个状态多加几维。  
我们再回过头来看看原来我们定义的$dp$状态有什么缺陷。  
我们发现，由于原来的状态**无法知道两个状态该从哪个点转移到新的状态**，那么，我们只要在原来的状态中在把**点的信息**加进去就可以了

我们定义$dp[i][j][mask]$表示状态为$mask$且混凝土覆盖了点$(i,j)$所需要的最小花费。

由于答案最终的形态一定是棵**树**(~~难不成你想连个环~~)，那么对于每个状态，肯定是从他的两个**互不相交**的**子状态**转移过来的。用数学式子表示就是：
$$dp[i][j][mask]=\max\{dp[i][j][submask]+dp[i][j][mask-submask]-a[i][j]\}$$

$a[i][j]$表示这个点原本有的鲜花数。  
很明显你在合并状态的时候不能把一个点的权值多算一次吧QAQ。

这样转移完了吗？并没有。

我们刚才所做的只是将先前的状态合并为当前的状态。然而，当前的状态也可以更新跟新当前状态的其他点的状态。  
有点晕？没关系，你可以这样理解：我们先从以前$mask$将当前的$mask$更新（或者，你可以理解为一种初始化）然后，我们可以在当前的$mask$上的每个点跑一遍最短路（不是指从这个点出发的最短路，而是以这个点为终点的最短路），从而得到每个点在当前这个$mask$上的最小花费。

这样，我们就能求出“最小花费”了。

然而题目还要让我们输出方案……

那我们就需要在开一个记录当前状态的前驱的数组$pre$
###### 下面就是$rng\_58$代码的精妙之处

对于一个数组$pre[i][j][mask][3]$  
前三维不解释，对于最后一维，他是用来存每一个状态的三个信息的：  
* 当$pre[i][j][mask][0]=0$时，说明这个状态是由**最短路**更新过来的，$pre[i][j][mask][1]$和$pre[i][j][mask][2]$记录的是该状态的前驱的点的坐标。
* 当$pre[i][j][mask][0]=1$时，说明这个状态是由其两个子状态**合并**而来的，$pre[i][j][mask][1]$和$pre[i][j][mask][2]$记录的是转移到给状态的两个子状态。
* 当$pre[i][j][mask][0]=2$时，说明这个状态没有前驱。

有了这个$pre$数组，我们就只要找到最终的状态，然后递归求解即可。

还有一些细节，代码里讲：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void in(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,k,a[105][105],dp[105][105][1<<7],pre[105][105][1<<7][3],X[10],Y[10];
bool ans[105][105];
void draw(int x,int y,int mask)
{
	ans[x][y]=1;
	if(pre[x][y][mask][0]==0)
	{
		draw(pre[x][y][mask][1],pre[x][y][mask][2],mask);
	}
	else if(pre[x][y][mask][0]==1)
	{
		draw(x,y,pre[x][y][mask][1]);
		draw(x,y,pre[x][y][mask][2]);
	}
}//递归函数，用于输出方案。
int main() 
{
	in(n);in(m);in(k);
	for(int mask=0;mask<(1<<k);mask++)
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				dp[i][j][mask]=1e9;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			in(a[i][j]);
	for(int i=0;i<k;i++)
	{
   
		in(X[i]);in(Y[i]);
   		X[i]--;Y[i]--;
		pre[X[i]][Y[i]][1<<i][0]=2;//每个单独的大厦是没有前驱的
    		dp[X[i]][Y[i]][1<<i]=a[X[i]][Y[i]];
	}
	for(int mask=0;mask<(1<<k);mask++)
	{
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		for(int sub=mask;sub;sub=(sub-1)&mask)
		{
			int tmp=dp[i][j][sub]+dp[i][j][mask^sub]-a[i][j];
			if(tmp<dp[i][j][mask])
			{
				dp[i][j][mask]=tmp;
				pre[i][j][mask][0]=1;
				pre[i][j][mask][1]=sub;
				pre[i][j][mask][2]=mask^sub;
			}
		}
        
		for(int T=0;T<n*m+10;T++)
		{
			for(int x=0;x<n;x++)
			for(int y=0;y<m;y++)
			for(int i=0;i<4;i++)
			{
				int nx=x+dx[i],ny=y+dy[i];
				if(nx>=0&&nx<n&&ny>=0&&ny<m)
				{
					int tmp=dp[nx][ny][mask]+a[x][y];
					if(tmp<dp[x][y][mask])
					{
						dp[x][y][mask]=tmp;
						pre[x][y][mask][0]=0;
						pre[x][y][mask][1]=nx;
						pre[x][y][mask][2]=ny;
					}
				}
			}
		}
     /*这里最短路算法比较特别（也许吧）
      我们知道，对于一个网格图，他只可能从他的上下左右直接更新过了，
      而每个点都可能间接更新到其他所有的点，
      那么，我们只要让每个点都被其他点更新n*m次（保险起见再多更新几次更好），
      所以，每一个点都能保证是当前状态的最小花费了。*/
     
	}
	
	int best=1e9;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		best=min(dp[i][j][(1<<k)-1],best);
	}	
	printf("%d\n",best);
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		if(dp[i][j][(1<<k)-1]==best)
		{
			draw(i,j,(1<<k)-1);
			for(int ii=0;ii<n;ii++)
			{
				for(int jj=0;jj<m;jj++)
					putchar(ans[ii][jj]?'X':'.');
				putchar('\n');
			}
			return 0;
		}
	}
}
```
[附：rng_58のcode](http://codeforces.com/contest/152/submission/1208970)

挺有意思的一道题，大家可以多思考思考。

**update 2019.8.24:感谢 @StudyingFather 对我$LaTeX$使用的指导，现在稍微调整了一下文章内容，使文章更加可读。**

---

## 作者：VenusM1nT (赞：6)

好久没做 $\textbf{DP}$ 题了。  
![](https://i.loli.net/2020/11/02/KhlzTStwoWeN7jv.png)

观察到 $k\leq 7$，于是可以考虑状压。以 $0/1$ 代表是否造了当前这座大厦。  
可是题目给定的是一个网格图，只考虑是否造的话肯定不对，因此引入 $i,j$ 来代表这个位置是否被覆盖过了。  
然后考虑转移。每次枚举 $S,i,j$ 和 $s\in S$，考虑容斥，则得到：
$$f_{S,i,j}=f_{s,i,j}+f_{S-s,i,j}-a_{i,j}$$
这一步是对上一状态的转移，接下来考虑当前状态的计算，要求的是最少毁多少花，其实就是一个最短路，因此每个点从它周围四个点转移过来就可以了，当然这里要多做几次，保证取到最优解（题解里另外一位神仙是 $n\times m+10$ 次，我稍微多循环了几次，也没什么问题）。复杂度 $\text{O}(2^k\times n^2\times m^2)$，因为 $n\times m\leq 200$ 所以没有压力。  
![](https://t1.picb.cc/uploads/2020/10/26/tYMEW7.png)  

上述的是最优解的求法，但答案还要求输出方案。不过这题的方案不难输，可以记录每个点每个状态的前驱，最后递归一下就可以求出来了。  
![](https://t1.picb.cc/uploads/2020/10/26/tY8nSc.png)

```cpp
#include<bits/stdc++.h>
#define N 100
#define St 200
#define reg register
#define inl inline
using namespace std;
int n,m,K,f[N+5][N+5][St],pre[N+5][N+5][St][3],a[N+5][N+5];
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
bool res[N+5][N+5];
void Print(reg int x,reg int y,reg int S)
{
	res[x][y]=1;
	if(pre[x][y][S][0]==2) return;
	if(!pre[x][y][S][0]) Print(pre[x][y][S][1],pre[x][y][S][2],S);
	else
	{
		Print(x,y,pre[x][y][S][1]);
		Print(x,y,pre[x][y][S][2]);
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&K);
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	}
	for(reg int S=0;S<(1<<K);S++)
	{
		for(reg int i=1;i<=n;i++)
		{
			for(reg int j=1;j<=m;j++) f[i][j][S]=1e9;
		}
	}
	for(reg int i=1;i<=K;i++)
	{
		reg int x,y;
		scanf("%d %d",&x,&y);
		f[x][y][1<<(i-1)]=a[x][y];
		pre[x][y][1<<(i-1)][0]=2;
	}
	for(reg int S=0;S<(1<<K);S++)
	{
		for(reg int i=1;i<=n;i++)
		{
			for(reg int j=1;j<=m;j++)
			{
				for(reg int k=S;k;k=(k-1)&S)
				{
					reg int cnt=f[i][j][k]+f[i][j][S^k]-a[i][j];
					if(cnt<f[i][j][S])
					{
						f[i][j][S]=cnt;
						pre[i][j][S][0]=1;
						pre[i][j][S][1]=k;
						pre[i][j][S][2]=S^k;
					}
				}
			}
		}
		for(reg int o=1;o<=n*m+N;o++)
		{
			for(reg int i=1;i<=n;i++)
			{
				for(reg int j=1;j<=m;j++)
				{
					for(reg int k=0;k<4;k++)
					{
						reg int nx=i+dx[k],ny=j+dy[k];
						if(nx<1 || nx>n || ny<1 || ny>m) continue;
						reg int cnt=f[nx][ny][S]+a[i][j];
						if(cnt<f[i][j][S])
						{
							f[i][j][S]=cnt;
							pre[i][j][S][0]=0;
							pre[i][j][S][1]=nx;
							pre[i][j][S][2]=ny;
						}
					}
				}
			}
		}
	}
	reg int ans=1e9;
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++) ans=min(ans,f[i][j][(1<<K)-1]);
	}
	printf("%d\n",ans);
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++)
		{
			if(f[i][j][(1<<K)-1]==ans)
			{
				Print(i,j,(1<<K)-1);
				for(reg int k=1;k<=n;k++)
				{
					for(reg int l=1;l<=m;l++) printf("%c",res[k][l]?'X':'.');
					puts("");
				}
				return 0;
			}
		}
	}
}
```

---

## 作者：huayucaiji (赞：4)

## 前言

我就喜欢这种重题的题，不知道是WC搬的CF还是CF搬的WC，不管了，反正一样就是了。

既可以水 $2$ 篇题解，也可以搞掉一黑一紫，何乐而不为？

## 解题思路

$k$ 很小，又是连通性问题，显然最小斯坦纳树，问题是如何建图？如何求出方案？

### 建图

我们可以按四联通来建图，不用管边权。由于在这张图里只有点权，我们的斯坦纳树 DP 转移方程会有所改变（不要重复计算点权），具体看代码，其实很好理解（只要你理解了斯坦纳树的板子）。

### 求出方案

这个有点难度。其实可以和大部分 DP 一样，需要记录一下转移决策点。SPFA 可以这样，三角形不等式的部分怎么办？

我们其实可以这样，如果可以已通过 SPFA 记录的决策点一直往前推，就往前，直到结束为止，我们就在把当前状态的递推在跑一遍即可。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=220,MAXK=11,INF=2e9;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};

int n,m,k,cnt;
int a[MAXN],h[MAXN],f[MAXN][1<<MAXK],g[MAXN][1<<MAXK];
char ans[MAXN];
bool inq[MAXN],vis[MAXN][1<<MAXK];
queue<int> q;

int idx(int i,int j) {
	return (i-1)*m+j;
} 
bool ok(int i,int j) {
	if(i>n||i<1||j>m||j<1) {
		return 0;
	}
	return 1;
}

struct edge {
	int to,nxt;
}e[10000];

void addedge(int u,int v) {
	e[++cnt].nxt=h[u];
	e[cnt].to=v;
	h[u]=cnt;
}

void SPFA(int s) {
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		inq[u]=0;
		
		for(int i=h[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(f[v][s]>f[u][s]+a[v]) {
				f[v][s]=f[u][s]+a[v];
				g[v][s]=u;
				if(!inq[v]) {
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
}

void getans(int u,int s) {
	if(vis[u][s]) {
		return ;
	}
	vis[u][s]=1;
	
	ans[u]='X';
	while(g[u][s]!=-1&&f[g[u][s]][s]+a[u]==f[u][s]) {
		u=g[u][s];
		getans(u,s);
	}
	for(int t=s&(s-1);t;t=(t-1)&s) {
		if(f[u][t]+f[u][s^t]-a[u]==f[u][s]) {
			getans(u,t);
			getans(u,s^t);
			break;
		}
	}
}

signed main() {
	cin>>n>>m>>k;
	for(int i=1;i<=n*m;i++) {
		for(int j=0;j<=1023;j++) {
			f[i][j]=INF;
			g[i][j]=-1;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			ans[idx(i,j)]='.';
			cin>>a[idx(i,j)];
			for(int p=0;p<4;p++) {
				if(ok(i+dx[p],j+dy[p])) {
					addedge(idx(i,j),idx(i+dx[p],j+dy[p]));
				}
			}
		}
	}
	for(int qq=1;qq<=k;qq++) {
		int i,j;
		cin>>i>>j;
		f[idx(i,j)][1<<qq-1]=a[idx(i,j)];
		ans[idx(i,j)]='X';
	}
	
	int mx=(1<<k)-1;
	
	for(int s=0;s<=mx;s++) {
		for(int i=1;i<=n*m;i++) {
			for(int t=s&(s-1);t;t=(t-1)&s) {
				f[i][s]=min(f[i][s],f[i][t]+f[i][s^t]-a[i]);
			}
			if(f[i][s]<INF) {
				inq[i]=1;
				q.push(i);
			}
		}
		SPFA(s);
	}
	
	int minn=INF,mark=0;
	for(int i=1;i<=n*m;i++) {
		if(f[i][mx]<minn) {
			minn=f[i][mx];
			mark=i;
		}
	}
	
	cout<<minn<<endl;
	getans(mark,mx);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			printf("%c",ans[idx(i,j)]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

题外话：[双倍经验](https://www.luogu.com.cn/problem/P4294)。
### 简要题意
有一个 $n$ 行 $m$ 列的矩阵，第 $i$ 行第 $j$ 列的数字为 $a_{i,j}$。现要在 $k$ 个关键格子上修房屋，要求除了这 $k$ 个关键格子以外再选择一些别的格子修筑道路，使得每栋房屋通过这些道路能够被连通。（如果一个格子上下左右走，通过一条只经过被选格子的路线，能够走到另一个格子，那么证明这两个格子连通。）问所有有房屋或道路的格子的权值和的最小值。  
数据范围：$ 1\le n,m\le 100,n \times m \le200,1 \le k \le \min(n \times m,7),1\le a_{i,j} \le 1000 ,1\le x \le n,1\le y \le m$。
### 思路分析
把上下左右的相邻的点看做中间有一条边连接，矩阵就变成了图，$k$ 个关键格子就是被选中的点。再看到 $k$ 很小，很容易想到斯坦纳树。         
在斯坦纳树中我们通常定义 $f_{u,S}$ 表示以节点 $u$ 为根，$k$ 个关键点的连通状态为 $S$ 的最小代价。在这里，为了避免建图，我们直接使用矩阵的坐标，定义 $f_{i,j,S}$ 表示以位置 $(i,j)$ 为根，$k$ 个关键点连通状态为 $S$ 的最小代价。       
沿用斯坦纳树的状态转移方程可以得到：    
$$\begin{cases}
f_{i,j,S \cup T}\gets \min(f_{i,j,T}+f_{i,j,S}-a_{i,j})\\
f_{i,j,S}\gets \min(f_{i',j',S}+a_{i,j})\\
\end{cases}$$      
第一条相当于把两个都包含位置 $(i,j)$ 的集合合并，但多加了当前位置的数字，所以要减掉。第二条中 $(i',j')$ 是 $(i,j)$ 的相邻点，它相当于在“子树”中按边松弛。$S$ 和 $T$ 都是集合，在状态转移中用二进制数表示。    
然后按照斯坦纳树的方式转移状态即可，先转移第一个式子，再转移第二个式子（因为第二个式子没有后效性；使用 Dijkstra 算法进行类似最短路的转移）。    
另外因为题目中要求输出方案，所以要记录当前状态是由哪个状态转移过来的。最后从最后状态开始往前推，记录被选中的点。      
### 代码展示   
初始化的时候要注意把最开始的点权加上。（好吧这毕竟是统计点权不是统计边权。）        
代码中 sx 和 sy 记录了其中一个关键点。     
对于第一条式子只记录了一个前驱，所以标记被选中的点时还需要对另一个前驱进行遍历。
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
struct point{int x,y,s;}ff[105][105][130];
int n,m,ss[105][105],f[105][105][130],sx,sy,k,s,fx[5]={0,-1,0,1,0},fy[5]={0,0,-1,0,1};
struct node
{
    int x,y;
    bool operator <(const node &xxx)const
    {return f[x][y][s]>f[xxx.x][xxx.y][s];}
};
priority_queue<node>dij;bool fl[105][105];
void dfs(int x,int y,int s)
{
    if(!s) return;
    fl[x][y]=1,dfs(ff[x][y][s].x,ff[x][y][s].y,ff[x][y][s].s);
    if(ff[x][y][s].x==x&&ff[x][y][s].y==y) dfs(x,y,ff[x][y][s].s^s);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k),memset(f,0x3f3f,sizeof(f));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&ss[i][j]);
    for(int i=1;i<=k;i++) scanf("%d%d",&sx,&sy),f[sx][sy][1<<(i-1)]=ss[sx][sy];
    for(s=1;s<(1<<k);s++)
    {
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
        {
            for(int t=s&(s-1);t;t=(t-1)&s) if(f[i][j][s]>f[i][j][t]+f[i][j][s^t]-ss[i][j])
            f[i][j][s]=f[i][j][t]+f[i][j][s^t]-ss[i][j],ff[i][j][s]=(point){i,j,t};
            if(f[i][j][s]!=f[0][0][0]) fl[i][j]=1,dij.push((node){i,j});
        }
        while(!dij.empty())
        {
            node ls=dij.top();dij.pop(),fl[ls.x][ls.y]=0;
            for(int i=1;i<=4;i++) if(ls.x+fx[i]>=1&&ls.x+fx[i]<=n&&ls.y+fy[i]>=1&&ls.y+fy[i]<=m
            &&f[ls.x+fx[i]][ls.y+fy[i]][s]>f[ls.x][ls.y][s]+ss[ls.x+fx[i]][ls.y+fy[i]])
            {
                f[ls.x+fx[i]][ls.y+fy[i]][s]=f[ls.x][ls.y][s]+ss[ls.x+fx[i]][ls.y+fy[i]],
                ff[ls.x+fx[i]][ls.y+fy[i]][s]=(point){ls.x,ls.y,s};
                if(!fl[ls.x+fx[i]][ls.y+fy[i]]) fl[ls.x+fx[i]][ls.y+fy[i]]=1,
                dij.push((node){ls.x+fx[i],ls.y+fy[i]});
            }
        }
    }
    dfs(sx,sy,(1<<k)-1);
    if(!k) printf("0\n");
    else printf("%d\n",f[sx][sy][(1<<k)-1]);
    for(int i=1;i<=n;i++,printf("\n")) for(int j=1;j<=m;j++)
    printf("%c",fl[i][j]?'X':'.');
}
```

---

