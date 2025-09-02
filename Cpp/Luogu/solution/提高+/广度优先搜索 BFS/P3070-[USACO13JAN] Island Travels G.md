# [USACO13JAN] Island Travels G

## 题目描述

Farmer John has taken the cows to a vacation out on the ocean! The cows are living on N (1 <= N <= 15) islands, which are located on an R x C grid (1 <= R, C <= 50). An island is a maximal connected group of squares on the grid that are marked as 'X', where two 'X's are connected if they share a side. (Thus, two 'X's sharing a corner are not necessarily connected.)

Bessie, however, is arriving late, so she is coming in with FJ by helicopter. Thus, she can first land on any of the islands she chooses. She wants to visit all the cows at least once, so she will travel between islands until she has visited all N of the islands at least once.

FJ's helicopter doesn't have much fuel left, so he doesn't want to use it until the cows decide to go home. Fortunately, some of the squares in the grid are shallow water, which is denoted by 'S'. Bessie can swim through these squares in the four cardinal directions (north, east, south, west) in order to travel between the islands. She can also travel (in the four cardinal directions) between an island and shallow water, and vice versa.

Find the minimum distance Bessie will have to swim in order to visit all of the islands. (The distance Bessie will have to swim is the number of distinct times she is on a square marked 'S'.) After looking at a map of the area, Bessie knows this will be possible.

给你一张r\*c的地图，有’S’,’X’,’.’三种地形，所有判定相邻与行走都是四连通的。我们设’X’为陆地，一个’X’连通块为一个岛屿，’S’为浅水，’.’为深水。刚开始你可以降落在任一一块陆地上，在陆地上可以行走，在浅水里可以游泳。并且陆地和浅水之间可以相互通行。但无论如何都不能走到深水。你现在要求通过行走和游泳使得你把所有的岛屿都经过一边。Q：你最少要经过几个浅水区？保证有解。


## 说明/提示

There are three islands with shallow water paths connecting some of them.


Bessie can travel from the island in the top left to the one in the middle, swimming 1 unit, and then travel from the middle island to the one in the bottom right, swimming 2 units, for a total of 3 units.


## 样例 #1

### 输入

```
5 4 
XX.S 
.S.. 
SXSS 
S.SX 
..SX 
```

### 输出

```
3 
```

# 题解

## 作者：Gavin·Olivia (赞：11)

~~非正式宣布，我和USACO的DP杠上了~~

这题的预处理是动规主体的10倍不止呢……~~严重怀疑它被评为蓝题不是因为动规难而是因为预处理烦。~~

### 预处理第一步：
把整张图$BFS$跑一遍，找出所有岛屿并打上标记，$num[i][j]$表示陆地$(i,j)$属于第几个岛屿。

### 预处理第二步：
$BFS$处理岛屿之间的距离，$d[i][j]$表示从岛屿$i$到岛屿$j$最少经过几片浅水区。对于岛屿$i$，现将属于它的陆地都入队，然后$BFS$扩展全图，这里有一个小技巧，我们开一个双端队列，对于下一个未访问过的点，如果它是陆地，就把它放到队头；如果是浅水区，就把它放到队尾。如果不用双端队列，就只能入队浅水区，并且之后还要再$SPFA$处理一次。

#### 双端队列证明：
对于队头点$(i,j)$，它的值为$len$，则在队列中的点的值要么是$len$，要么是$len+1$。如果下一个点是陆地，则它的值是$len$，否则是$len+1$。显然前者扩展出的状态会比后者更优，因此将前者放于队头，优先扩展。

### 预处理第三步：
如果之前有用过双端队列，就可以省略这一步，不然还要再跑$n$遍的$SPFA$求岛屿之间的最短路。我是懒得打了啦……如果有大佬打出来了，还请私信发给我，让蒟蒻%%%。

### $DP$
（相对于预处理来说）状压就变得特别好写~~，简直是在送分~~。$f[i][j]$表示经过岛屿状态为$i$、最后到达的岛屿编号为$j$时经过浅水区的最少数量。动态转移方程

$f[i|(1<<(k-1))][k]=min(f[i][j]+d[j][k])$

以上具体实现过程详见代码。

```cpp
#include<bits/stdc++.h>
 using namespace std;
 int fx[4]={-1,1,0,0};
 int fy[4]={0,0,-1,1};
 int n,m,i,j,k,cnt,l,r,lim,ans,maxn;
 int c[20],f[33000][17];
 int num[55][55],d[20][20];
 int x[5005],y[5005],dis[5005];
 bool used[55][55];
 char s[55][55];
 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}
 void land_f()//预处理第一步
{
	int a,b,xx,yy,i;
	while(l<=r)
	{
		a=x[l]; b=y[l++];
		for(i=0;i<4;i++)
		{
			xx=a+fx[i]; yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||used[xx][yy]||s[xx][yy]!='X') continue;
			used[xx][yy]=true; num[xx][yy]=cnt;
			x[++r]=xx; y[r]=yy;
		}
	}
}
 void land_c(int now)//预处理第二步
{
	int a,b,c,xx,yy,i;
	while(l<=r)
	{
		a=x[l]; b=y[l]; c=dis[l++];
		for(i=0;i<4;i++)
		{
			xx=a+fx[i]; yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||used[xx][yy]||s[xx][yy]=='.') continue;
			used[xx][yy]=true; 
			if(s[xx][yy]=='X')
			{
				if(d[now][num[xx][yy]]<0)
				 d[now][num[xx][yy]]=c;
				x[--l]=xx; y[l]=yy; dis[l]=c;
				continue;
			}
			x[++r]=xx; y[r]=yy; dis[r]=c+1;
		}
	}
}
 int main()
{
	n=read(); m=read();
	for(i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(i=1;i<=n;i++)
	 for(j=1;j<=m;j++)
	  if(s[i][j]=='X'&&(!used[i][j]))
	  {
		++cnt; l=r=1; x[1]=i; y[1]=j;
		used[i][j]=true; num[i][j]=cnt;
		land_f();
	  }
	maxn=n*m; memset(d,-1,sizeof(d));
	for(k=1;k<=cnt;k++)
	{
		l=maxn+1; r=maxn; d[k][k]=0;
		for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		{
			used[i][j]=false;
			if(num[i][j]==k)x[++r]=i,y[r]=j,dis[r]=0,used[i][j]=true;
		}
		land_c(k);
	}
	lim=(1<<cnt)-1; memset(f,63,sizeof(f)); 
	for(i=1;i<=cnt;i++) c[i]=1<<i-1,f[c[i]][i]=0;
	for(i=1;i<lim;i++)
	{
		for(j=1;j<=cnt;j++)
		 if((i&c[j])&&f[i][j]<maxn)
		  for(k=1;k<=cnt;k++)
		   if(!(i&c[k])&&d[j][k]>0)//如果d[j][k]=-1,说明岛屿j和岛屿k不连通
			f[i|c[k]][k]=min(f[i|c[k]][k],f[i][j]+d[j][k]);
	}
	ans=1e9;
	for(i=1;i<=cnt;i++) ans=min(ans,f[lim][i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：堇墨浮华 (赞：7)

### 本蒟蒻有史以来写过的最长的代码...quq...
##### 这道题考察了我们很多知识点，如BFS，SPFA及状压DP，是很 ~~（毒瘤）~~ 有价值滴一道题
##### 首先看数据范围，发现岛的数量很少，那么就可以往状压上面想 ~~可我咋都想不到~~
##### 先BFS和SPFA预处理出两个岛屿之间最少经过的浅水区数量
##### 用dp[S][i]表示已经经过S集合内的所有岛屿，现在在第i个岛屿，最少需要经过的浅水区数量
##### emmmmm差不多就这样吧，详见代码~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mn=16;
const int mn=55;
int r,c;
char s[55][55];
int flag[mn][mn],num[mn],cnt,f[mn][mn],dis[mn][mn],dp[1<<Mn][Mn],ans=1<<30;
int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool vis[mn][mn];
struct Node{
	int x,y;
}block[Mn][Mn];
queue<Node>q;//古怪的队列式存储 
void bfs(int bx,int by){//连通块 get√
	Node tmp;
	tmp.x=bx;tmp.y=by;
	q.push(tmp);//入队,本来准备用q.push(Node{bx,by})的(这样可以省点代码啊QwQ),却出现编译警告。。。QwQ 
	vis[bx][by]=1;//表示已来过 
	flag[bx][by]=cnt;//打上标记,此地属于本连通块 
	num[cnt]++;//本连通块的大小(成员个数)++ 
	block[cnt][num[cnt]].x=bx;block[cnt][num[cnt]].y=by;//记录每个成员位置 
	while (!q.empty()){
		Node now=q.front();q.pop();//出队 
		for (int i=0;i<4;i++){
			int xx=now.x+d[i][0],yy=now.y+d[i][1];
			if (xx>=1&&xx<=r&&yy>=1&&yy<=c&&s[xx][yy]=='X'&&!vis[xx][yy]){
				Node tmp;
				tmp.x=xx;tmp.y=yy;
				q.push(tmp);
				vis[xx][yy]=1;
				flag[xx][yy]=cnt;
				num[cnt]++;
				block[cnt][num[cnt]].x=xx;block[cnt][num[cnt]].y=yy;
				//注释相似见上(懒得打字了)
			}
		}
	}
}
void spfa(int w){//超长的SPFA。。。修改无数次qwq 
	memset(vis,0,sizeof(vis));
	memset(dis,127/3,sizeof(dis));//dis[][]用于记下最少需要经过的浅水区 
	for (int i=1;i<=num[w];i++){
		int xx=block[w][i].x,yy=block[w][i].y;
		vis[xx][yy]=1;//把所有连通块成员标为"已来过" 
		dis[xx][yy]=0;//内部不用经过浅水区 
		q.push(block[w][i]);//入队(反正上一轮清空过了) 
	}
	while (!q.empty()){
		Node now=q.front();q.pop();
		vis[now.x][now.y]=0;
		for (int i=0;i<4;i++){
			int xx=now.x+d[i][0],yy=now.y+d[i][1];
			if (xx<=0||xx>r||yy<=0||yy>c||s[xx][yy]=='.') continue;
			if (s[xx][yy]=='X'){//陆地 
				if (dis[now.x][now.y]<dis[xx][yy]){
					dis[xx][yy]=dis[now.x][now.y];//更新 
					if (!vis[xx][yy]){
						vis[xx][yy]=1;
						Node tmp;
						tmp.x=xx;tmp.y=yy;
						q.push(tmp);
					}
				}
				f[flag[xx][yy]][w]=f[w][flag[xx][yy]]=min(f[flag[xx][yy]][w],dis[xx][yy]);
				//更新(xx,yy)所属连通块 到 现在所在的连通块 之间最少需要经过的浅水区 
			}
			else{//浅水区 
				if (dis[now.x][now.y]+1<dis[xx][yy]){
					dis[xx][yy]=dis[now.x][now.y]+1;
					if (!vis[xx][yy]){
						vis[xx][yy]=1;
						Node tmp;
						tmp.x=xx;tmp.y=yy;
						q.push(tmp);
					}
				}
			}
		}
	}
}
void DP(){//状压DP(纯套模板啦~)
	memset(dp,127/3,sizeof(dp));
	int tmpn=(1<<cnt)-1;
	for (int i=1;i<=cnt;i++) dp[1<<(i-1)][i]=0;
	for (int S=1;S<=tmpn;S++)
		for (int i=1;i<=cnt;i++)
			if (S&(1<<(i-1))){
				for (int j=1;j<=cnt;j++){
					if (i==j) continue; 
					dp[S][i]=min(dp[S][i],dp[S^(1<<(i-1))][j]+f[j][i]);
				}
			}
}
int main(){
	scanf("%d%d",&r,&c);
	for (int i=1;i<=r;i++)
		scanf ("%s",s[i]+1);
	for (int i=1;i<=r;i++)
		for (int j=1;j<=c;j++)
			if (!vis[i][j]&&s[i][j]=='X'){
				cnt++;
				bfs(i,j);
			}
	memset(f,127/3,sizeof(f));
	for (int i=1;i<=cnt;i++) f[i][i]=0,spfa(i);
	DP();
	int S=(1<<cnt)-1;
	for (int i=1;i<=cnt;i++)
		ans=min(ans,dp[S][i]);
	printf ("%d\n",ans);
	return 0;
}

```

---

## 作者：DengDuck (赞：3)

# 前言

一道静下心来分析结构就会做的简单题。

和 [ABC301E](https://www.luogu.com.cn/problem/AT_abc301_e) 十分像，后者简单一点，可以先做那道题再回过头做这道题。

# 转化

我们来分析一下一个更简单的题，把岛屿当成点，把浅水区当成边，发现这是一个类似于旅行商的问题：

> 求最短路径走过所有点。

这个问题可以直接用状态压缩动态规划解决。

我们设 $f_{i,j}$ 表示从任意点出发目前在 $i$，走过点的集合为 $j$ 的最小代价。

使用刷表法（枚举已知的状态更新未知的状态）更新，方程如下：

$$
f_{k,j+k}=\max(f_{k,j+k},f_{i,j}+\text{dis}(i,k))
$$

显然初始状态是 $f_{i,i}=0$，目标状态是 $f_{i,X}$，其中 $i\in X$，以上所有的 $i$ 满足 $1\leq i \leq n$。

注意实际实现的时候集合使用状态压缩，也就是位运算维护，因此不要直接嗯套方程。

这一部分的时间复杂度为 $\mathcal O(n^2 2^n)$ 的。

# 找点

注意从这里开始，我们用与上文不同的标记方式，岛屿数为 $m$，地图规模的估算统一用 $n^2$ 代替。

我们先把点处理出来，可以使用洪水填充法，也就是我们找到一个岛屿的一部分，则使用 BFS 找出岛屿的全部部分，实现可以看我的代码。

这一部分的时间复杂度是 $\mathcal O(n^2)$。

# 建边

对于任意两个岛屿，我们都需要跑一次 BFS 算距离，考虑到在地图上最短路径可能由不同的点组成，所以我们需要初始将一个岛屿所有的点全部扔进队列，最后统计答案也要看另外一个岛屿所有的点。

这样的效率比一个一个点配对好得多，可以做到 $\mathcal O(m^2n^2)$。

求出答案保存即可。

# 总结

这道题目需要细心来做，如果不会可以不做，沉淀个两三月，回来就会了，然后你就会感受到自己码力的提升。

总的时间复杂度不估算了。

# 代码实现

```cpp
#include<bits/stdc++.h>
#define LL long long
#define X first
#define Y second
using namespace std;
const LL N=55;
const LL M=1<<15;
const LL dx[4]={0,0,1,-1};
const LL dy[4]={1,-1,0,0};
LL n,m,vis[N][N],tot,dis[N][N],b[N][N],f[N][M];
char s[N][N];
vector<pair<LL,LL> >v[N];
queue<pair<LL,LL> >q;
void getland(LL x,LL y)
{
	q.push({x,y});
	while(!q.empty())
	{
		LL xx=q.front().X,yy=q.front().Y;
		q.pop();
		s[xx][yy]='F';
		v[tot].push_back({xx,yy});
		for(int i=0;i<4;i++)
		{
			LL nx=xx+dx[i],ny=yy+dy[i];
			if(s[nx][ny]=='X')
			{
				s[nx][ny]='F';
				q.push({nx,ny});
			}
		}
	}
}
LL cal(LL i,LL j)
{
	memset(b,127,sizeof(b));
	for(auto i:v[i])
	{
		q.push(i);
		b[i.X][i.Y]=0;
	}
	while(!q.empty())
	{
		LL xx=q.front().X,yy=q.front().Y;
		q.pop();
		for(int i=0;i<4;i++)
		{
			LL nx=xx+dx[i],ny=yy+dy[i];
			if(s[nx][ny]=='F'&&b[nx][ny]>b[xx][yy])
			{
				b[nx][ny]=b[xx][yy];
				q.push({nx,ny});
			}
			if(s[nx][ny]=='S'&&b[nx][ny]>b[xx][yy]+1)
			{
				b[nx][ny]=b[xx][yy]+1;
				q.push({nx,ny});
			}			
		}
	}
	LL ans=1e9;
	for(auto i:v[j])
	{
		ans=min(b[i.X][i.Y],ans);
	}
	return ans;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='.')vis[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='X')
			{
				++tot;
				getland(i,j);
			}
		}
	}
	for(int i=1;i<=tot;i++)
	{
		for(int j=i+1;j<=tot;j++)
		{
			dis[i][j]=dis[j][i]=cal(i,j);
		}
	}
	memset(f,127,sizeof(f));
	for(int i=1;i<=tot;i++)
	{
		f[i][(1<<(i-1))]=0;
	}
	for(LL j=0;j<(1<<tot);j++)
	{
		for(int i=1;i<=tot;i++)
		{
			if(((j>>(i-1))&1)==0)continue;
			for(int k=1;k<=tot;k++)
			{
				f[k][j|(1<<(k-1))]=min(f[k][j|(1<<(k-1))],f[i][j]+dis[i][k]);
			}
		}
	}
	LL ans=1e9;
	for(int i=1;i<=n;i++)
	{
		ans=min(ans,f[i][(1<<tot)-1]);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：黑影洞人 (赞：3)

这是一道很 **长** 的状压DP， 

尤其是冗长的预处理，

从13行道54行全是预处理。

预处理1：用深搜判断岛屿（联通块）

预处理2：用 `SPFA` 预处理出两个岛屿之间最少经过的浅水区数量

然后是状态设计

$dp[i][j]$ 表示已经访问了 $i$ 个岛屿，$j$ 表示 $n$ 个岛屿联通块的访问状态

然后可以得出状态转移方程

为了方便表示 用 $e(k)$ 表示 $2^{k-1}$

$dp_{k,i|e(k)}=min(dp_{k,i|e(k)},dp_{j,i}+p_{j,k})$

$p_{j,k}$ 为 $j$ 到 $k$ 的最短路

下面是AC代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define N 55
#define e(n) (1<<(n-1))
#define E(n) ((1<<n)-1)
using namespace std;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},num[N][N],p[N][N];
char str[N][N];
int vis[N][N];
int n,m,cnt,ans=12122106,dp[20][1<<15+5];
void dfs(int x,int y){
    for(int i=0;i<4;++i){
        int a=x+dx[i];
        int b=y+dy[i];
        if(a<1||a>n||b<1||b>m||str[a][b]!='X'||num[a][b])continue;
        num[a][b]=cnt;
        dfs(a,b);
    }
}
void spfa(int u,int v){
	queue<int>q;
	memset(vis,0x3f,sizeof(vis));
	vis[u][v]=1;
	q.push(u);
	q.push(v);
	while(!q.empty()){
		int x=q.front();q.pop();
		int y=q.front();q.pop();
		for(int i=0;i<4;i++){
			int a=x+dx[i],b=y+dy[i];
			if(a<1||a>n||b<1||b>m||str[a][b]=='.')continue;
			int now=vis[x][y];
			if(now>vis[a][b])continue;
			if(str[a][b]=='X'){
				if(now<vis[a][b]){
					vis[a][b]=now;
					int aa=num[a][b],bb=num[u][v];
					p[aa][bb]=min(p[aa][bb],vis[a][b]-1);
					p[bb][aa]=p[aa][bb];
					q.push(a),q.push(b);
				}
			}
			else{
				now++;
				if(now<vis[a][b]){
					vis[a][b]=now;
					q.push(a),q.push(b);
				}
			}
		} 
	}
}
int main(){
	scanf("%d%d",&n,&m);
	memset(p,0x3f,sizeof(p));
    for(int i=1;i<=n;++i)scanf("%s",str[i]+1);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
        	if(str[i][j]=='X'&&!num[i][j]){
                num[i][j]=++cnt;
                dfs(i,j);
            }
		}     
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
    		if(num[i][j]){
    			spfa(i,j);
			}
		}
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=cnt;i++)dp[i][e(i)]=0;
	for(int i=1;i<1<<cnt;i++){
		for(int j=1;j<=cnt;j++){
			if(!(i&e(j)))continue;
			for(int k=1;k<=cnt;k++){
				if((i&e(k)))continue;
				dp[k][i|e(k)]=min(dp[k][i|e(k)],dp[j][i]+p[j][k]);//DP方程 
			}
		}
	}
	for(int i=1;i<=cnt;i++)ans=min(ans,dp[i][E(cnt)]);//注意是E（cnt）不是e（cnt）
	printf("%d\n",ans);
	return 0;
}


```
``

求管理同志通过

---

## 作者：kurokey (赞：2)

bfs+状态压缩



```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cctype>
 #include <queue>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <climits>
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define fi first
#define se second
#define ping(x,y) ((x-y)*(x-y))
#define mst(x,y) memset(x,y,sizeof(x))
#define mcp(x,y) memcpy(x,y,sizeof(y))
using namespace std;
#define gamma 0.5772156649015328606065120
#define MOD 1000000007
#define inf 0x3f3f3f3f
#define N 2000005
#define maxn 100005
typedef pair<int,int> PII;
typedef long long LL;
int n,m,cnt;
char str[60][60];
int vis[60][60];
int num[60][60];
int pic[60][60];
int dp[20][1<<16];
int d[60];
int dir[][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<int>q;
void bfs(int i,int j){
    mst(vis,inf);vis[i][j]=1;
    q.push(i);q.push(j);
    while(!q.empty()){
        int x=q.front();q.pop();
        int y=q.front();q.pop();
        for(int k=0;k<4;++k){
            int xx=x+dir[k][0];
            int yy=y+dir[k][1];
            if(xx<1||xx>n||yy<1||yy>m||str[xx][yy]=='.')continue;
            int temp=vis[x][y];
            if(temp>vis[xx][yy])continue;
            if(str[xx][yy]=='X'){
                if(temp<vis[xx][yy]){
                    vis[xx][yy]=temp;
                    pic[num[xx][yy]][num[i][j]]=min(pic[num[xx][yy]][num[i][j]],vis[xx][yy]-1);
                    pic[num[i][j]][num[xx][yy]]=pic[num[xx][yy]][num[i][j]];
                    q.push(xx);q.push(yy);
                }
            }
            else{
                ++temp;
                if(temp<vis[xx][yy]){
                    vis[xx][yy]=temp;
                    q.push(xx);q.push(yy);
                }
            }
        }
    }
}
int solve(){
    mst(dp,inf);
    int all=1<<cnt;
    for(int j=1;j<=cnt;++j) dp[j][1<<j-1]=0;
    for(int i=1;i<all;++i){
        for(int j=1;j<=cnt;++j){
            if(!(i&(1<<j-1)))continue;
            for(int k=1;k<=cnt;++k){
                if(i&(1<<k-1))continue;
                dp[k][i|(1<<k-1)]=min(dp[k][i|(1<<k-1)],dp[j][i]+pic[j][k]);
            }
        }
    }
    int res=inf;
    for(int i=1;i<=cnt;++i)res=min(res,dp[i][all-1]);
    return res;
}
void dfs(int x,int y){
    for(int i=0;i<4;++i){
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(xx<1||xx>n||yy<1||yy>m||str[xx][yy]!='X'||num[xx][yy])continue;
        num[xx][yy]=cnt;
        dfs(xx,yy);
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    int i,j;
    mst(pic,inf);
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i)scanf("%s",str[i]+1);
    for(i=1;i<=n;++i){
        for(j=1;j<=m;++j)
            if(str[i][j]=='X'&&!num[i][j]){
                num[i][j]=++cnt;
                dfs(i,j);
            }
    }
    for(i=1;i<=n;++i)for(j=1;j<=m;++j)
        if(num[i][j])bfs(i,j);
//    for(i=1;i<=n;++i){
//        for(j=1;j<=m;++j)printf("%c",num[i][j]==0?'*':num[i][j]+'a');
//    printf("\n");
//    }
    printf("%d\n",solve());
    return 0;
}
```

---

## 作者：queuDU (赞：2)

把每个岛缩成一个点，bfs找最短路径，之后状压DP即可。

BFS部分用set模拟双向队列WA了一大圈，最后发现是结构体符号定义错了qaq

代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <queue>

using namespace std;

inline void quick_io() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}

namespace fin {
    int dis[20][20], n, f[60009][20];
    bool vis[60009];
    inline bool getseq(int x,int k) {
    	x>>=(k-1);
    	return x&1;
    }
    void main(int fix) {
    	memset(f,0x3f,sizeof(f));
        n=fix;
        //for(int i=1;i<=n;i++) {
        //	for(int j=1;j<=n;j++)
        //		cout<<dis[i][j]<<' ';
        //	cout<<endl;
        //}
        queue<int> q;
        for(int i=1;i<=n;i++) 
        	f[1<<(i-1)][i]=0, q.push(1<<(i-1));
        int cur, des;
        while(!q.empty()) {
        	cur=q.front();
        	q.pop();
        	for(int pos=1;pos<=n;pos++) {
        		if(!getseq(cur,pos)) {
        			des=cur+(1<<(pos-1));
        			for(int st=1;st<=n;st++)
        				if(getseq(cur,st)) {
        					f[des][pos]=min(f[cur][st]+dis[st][pos],f[des][pos]);
        					if(vis[des]==0)
        						vis[des]=1, q.push(des);
        				}
        		}
        	}
    	}
        int fin=(1<<n)-1, ans=2147483647;
        	for(int i=1;i<=n;i++) 
        		ans=min(ans,f[fin][i]);
        cout<<ans<<endl;
    }
}

const int MAXN=3080;

int father[MAXN];
int getfather(int u) {
    return father[u]==u?u:father[u]=getfather(father[u]);
}
inline void merge(int u,int v) {
    u=getfather(u), v=getfather(v);
    father[u]=v;
}

struct node {
    int v; node *next;
}edge[MAXN<<1], *first[MAXN];
int cnte;
set<int> exm[MAXN];
inline void _addedge(int u,int v) {
    node *p=&edge[++cnte]; p->v=v;
    p->next=first[u]; first[u]=p;
    exm[u].insert(v);
}
inline void addedge(int u,int v) {
    _addedge(u,v), _addedge(v,u);
}
int n,m;
inline int id(int x,int y) {
    return x*m+y;
}
int map[MAXN][MAXN];
int bid[MAXN][MAXN];

set<int> st;
int dis[20][MAXN], cnts, start[MAXN];
int inq[20][MAXN];

struct stnode {
    int val, fix;
    bool operator < (const stnode &u) const {
        return fix<u.fix;
    }
    stnode() {}
    stnode(int vv,int ff) {
        val=vv, fix=ff;
    }
};

void bfs(int origin,int x) {
    set<stnode> q; 
    set<stnode>::iterator it;
    int fixl=1,fixr=1;
    q.insert(stnode(x,1));
    int u;
    //cout<<"bfs : "<<origin<<endl;
    while(q.size()) {
        it=q.begin();
        u=(*it).val;
        //cout<<"id = "<<u<<' '<<(*it).fix<<endl;
        q.erase(it);
        for(node *p=first[u];p;p=p->next)
    		if(dis[origin][p->v]>dis[origin][u]+(st.find(p->v)==st.end()?0:1)) {
    			if(st.find(p->v)!=st.end()) {
                    dis[origin][p->v]=dis[origin][u];
                    if(!inq[origin][p->v])
                        q.insert(stnode(p->v,--fixl)), inq[origin][p->v]=true;
                }
                else {
                    dis[origin][p->v]=dis[origin][u]+1;
                    if(!inq[origin][p->v])
                        q.insert(stnode(p->v,++fixr)), inq[origin][p->v]=true;
                }
            }
    }
}

signed main() {
    //init
    for(int i=1;i<MAXN;i++)
        father[i]=i;
    memset(dis,0x3f,sizeof(dis));
    //code
    quick_io();
    cin>>n>>m;
    char ch;
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++) {
            cin>>ch;
            if(ch=='.')
                map[i][j]=0;
            else if(ch=='X')
                map[i][j]=2;
            else map[i][j]=1;
        }
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++) {
            if(map[i][j]==2 && map[i][j-1]==2)
                merge(id(i,j),id(i,j-1)); 
            if(map[i][j]==2 && map[i-1][j]==2)
                merge(id(i,j),id(i-1,j));
        }
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++) {
            bid[i][j]=getfather(id(i,j));
            if(map[i][j]==2)
                st.insert(bid[i][j]);
        }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            if(i>=1 && map[i][j]*map[i-1][j]) 
                addedge(bid[i][j],bid[i-1][j]);
            if(j>=1 && map[i][j]*map[i][j-1])
                addedge(bid[i][j],bid[i][j-1]);
            
            //cout<<bid[i][j]<<' ';
        }
        //cout<<endl;
    }
    //cout<<endl;
    
    for(set<int>::iterator it=st.begin();it!=st.end();it++) {
        start[++cnts]=*it;
        //cout<<(*it)<<endl;
        dis[cnts][start[cnts]]=0;
        bfs(cnts,start[cnts]);
        for(int i=1;i<cnts;i++)
        	fin::dis[cnts][i]=fin::dis[i][cnts]=dis[cnts][start[i]];
    }
    fin::main(cnts);
}
```

---

## 作者：RikoHere (赞：1)

题面有点坑，翻译内容中没有指明n的范围，通过观察原题面得到$n \leq 15$并大致猜测这是一个状态压缩dp

最小生成树显然不可行，可以举例说明存在某种情况某边要经过两次或更多

对于任意一个岛屿$i$到任意一个岛屿$j$的最短距离显然是固定的，每个岛域之间的距离(不经过其他岛屿)可以用bfs预处理出来，初始状态只要将这个岛屿全部坐标位置全部入队即可

得到了任意两个岛屿之间的直接距离后(当然存在部分岛屿不可互达)，在$ n \leq 15$时可以直接用$floyd$求解

现在得到任意两个节点之间的最短距离，显然直接dfs复杂度任然爆炸，dfs求解的复杂度是$O(n!)$

考虑状态压缩dp，设$S$为当前节点是否经过的状态集合，$v$为当前停留的节点，显然有$f(S,v)=min\{ f(S',u)+dis(u,v)\}$其中$S'$中$v$为未达，很明显对于任意一个状态他最多转移$n$个状态

得到时间复杂度为$O(2^nn)$的状压

```
//2019/7/24->Riko->AtNCU->luoguP3070
#include<bits/stdc++.h>
template <typename T> inline void smin (T& x, T y) { if (x > y) x = y;}
//Believing heart is your power
using namespace std;
int getch () {
	int ch = getchar();
	return (ch == '.' or ch == 'S' or ch == 'X') ? ch : getch();
}

const int N = 55;
struct Point { 
	int x, y;
	Point (int x, int y) : x(x), y(y) {}
};
struct Len { 
	int x, y, l;
	Len (int x, int y, int l) : x(x), y(y), l(l) {}
};
int r, c, n, ind;
int type[N][N], idx[N][N], len[N][N], vis[N][N], hasgone[N];
int f[(1<<15)+64][16], Mx[4] = {0, 0, 1, -1}, My[4] = {1, -1, 0, 0};
queue <Point> Find, Save[N];
queue <Len> Que;

void Getpoints (int x, int y) {
	Find.push(Point(x, y)); Save[ind].push(Point(x, y));
	while (!Find.empty()) {
		Point tem = Find.front(); Find.pop();
		for (int i = 0; i < 4; ++i) {
			int Nx = tem.x+Mx[i];
			int Ny = tem.y+My[i];
			if (idx[Nx][Ny]) continue;
			if (type[Nx][Ny] != 1) continue;
			idx[Nx][Ny] = ind;
			Find.push(Point(Nx, Ny));
			Save[ind].push(Point(Nx, Ny));
		}
	}
}
void Getlen (int id) {
	while (!Save[id].empty()) {
		Point tem = Save[id].front(); Save[id].pop();
		Que.push(Len(tem.x, tem.y, 0)); vis[tem.x][tem.y] = true;
	}
	while (!Que.empty()) {
		Len tem = Que.front(); Que.pop();
		for (int i = 0; i < 4; ++i) {
			int Nx = tem.x+Mx[i];
			int Ny = tem.y+My[i];
			if (!type[Nx][Ny] or vis[Nx][Ny]) continue;
			if (idx[Nx][Ny]) { smin(len[id][idx[Nx][Ny]], tem.l); continue;}
			vis[Nx][Ny] = true;
			Que.push(Len(Nx, Ny, tem.l+1));
		}
	}
}
void work () {
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= ind; ++i) {f[(1<<(i-1))][i] = 0;}
	for (int x = 1; x < (1<<ind); ++x) {
		for (int u = 1; u <= ind; ++u) {
			if (!x&(1<<(u-1))) continue;
			for (int v = 1; v <= ind; ++v) {
				if (x&(1<<(v-1))) continue;
				smin(f[x|(1<<(v-1))][v], f[x][u]+len[u][v]);
			}
		}
	}
	int ans = INT_MAX;
	for (int i = 1; i <= ind; ++i) { smin(ans, f[(1<<ind)-1][i]);}
	printf("%d", ans);
}
void prepare () {
	scanf("%d %d", &r, &c);
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			int ch = getch();
			if (ch == 'X') type[i][j] = 1;
			if (ch == 'S') type[i][j] = 2;
		}
	}
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (!idx[i][j] and type[i][j] == 1) {
				idx[i][j] = ++ind;
				Getpoints(i, j);
			}
		}
	}		//prepare for the distance
	memset(len, 0x3f, sizeof(len));
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (idx[i][j] and !hasgone[idx[i][j]]) {
				memset(vis, 0, sizeof(vis));
				hasgone[idx[i][j]] = true;
				Getlen(idx[i][j]);
			}
		}
	}		//Get the cloest distance
	for (int i = 1; i <= ind; ++i) {
		for (int j = i+1; j <= ind; ++j) {
			for (int k = i+1; k < j; ++k) {
				smin(len[i][j], len[i][k]+len[k][j]);
				len[j][i] = len[i][j];
			}
		}
	}  		//floyd Part
	work();
} int main () { prepare();}
```


---

## 作者：Acheron_RBM (赞：0)

代码有点长的一题。

第一步：先把整张图 bfs 一遍，找出所有岛屿，打上标记。

第二步：利用 bfs 处理两个岛屿之间的距离（就是两个岛屿的路径中经过浅水区最少的那条路径）

接下来就可以状压 dp 了。

设 $dp_{i,j}$ 为经过的岛屿情况为 $i$ 到达 $j$ 是经过最少的浅水区数量。

易得状态转移方程：

$$dp_{i|c_k,k}=\min(dp_{i|c_k,k},dp_{i,j}+d_{j,k})$$

初始状态为 $c_i=1<<(i-1),dp_{c_i,i}=0$。

其余赋极大值。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int fx[4]={-1,1,0,0};
int fy[4]={0,0,-1,1};
int n,m;
int l,r;
int maxx,minn;
int cnt;int ret;
int c[20],dp[33000][17];
int cnt1[55][55],d[20][20];
int queen1[5005],queen2[5005],queen3[5005];
bool flag[55][55];
char s[55][55];
void one_side()
{
	while(l<=r)
	{
		int a=queen1[l];
		int b=queen2[l++];
		for(int i=0;i<4;i++)
		{
			int xx=a+fx[i];
			int yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||flag[xx][yy]||s[xx][yy]!='X')
			{
				continue;
			}
			flag[xx][yy]=true;
			cnt1[xx][yy]=cnt;
			queen1[++r]=xx;
			queen2[r]=yy;
		}
	}
}
void three_side(int now)
{
	while(l<=r)
	{
		int a=queen1[l];
		int b=queen2[l];
		int c=queen3[l++];
		for(int i=0;i<4;i++)
		{
			int xx=a+fx[i];
			int yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||flag[xx][yy]||s[xx][yy]=='.')
			{
				continue;
			}
			flag[xx][yy]=true; 
			if(s[xx][yy]=='X')
			{
				if(d[now][cnt1[xx][yy]]<0)
				{
					d[now][cnt1[xx][yy]]=c;
				}
				queen1[--l]=xx;
				queen2[l]=yy;
				queen3[l]=c;
				continue;
			}
			queen1[++r]=xx;
			queen2[r]=yy;
			queen3[r]=c+1;
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='X'&&(!flag[i][j]))
			{
				cnt++;
				l=r=1;
				queen1[1]=i;
				queen2[1]=j;
				flag[i][j]=true;
				cnt1[i][j]=cnt;
				one_side();
			}
		}
	}
	maxx=n*m;
	memset(d,-1,sizeof(d));
	for(int k=1;k<=cnt;k++)
	{
		l=maxx+1;
		r=maxx;
		d[k][k]=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				flag[i][j]=false;
				if(cnt1[i][j]==k)
				{
					queen1[++r]=i;
					queen2[r]=j;
					queen3[r]=0;
					flag[i][j]=true;
				}
			}
		}
		three_side(k);
	}
	minn=(1<<cnt)-1;
	memset(dp,63,sizeof(dp)); 
	for(int i=1;i<=cnt;i++)
	{
		c[i]=1<<(i-1);
		dp[c[i]][i]=0;
	}
	for(int i=1;i<minn;i++)
	{
		for(int j=1;j<=cnt;j++)
		{
			if((i&c[j])&&dp[i][j]<maxx)
			{
				for(int k=1;k<=cnt;k++)
				{
					if(!(i&c[k])&&d[j][k]>0)
					{
						dp[i|c[k]][k]=min(dp[i|c[k]][k],dp[i][j]+d[j][k]);
					}
				}
			}
		}
	}
	ret=INT_MAX;
	for(int i=1;i<=cnt;i++)
	{
		ret=min(ret,dp[minn][i]);
	}
	cout<<ret;
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

题意是说，陆地构成一些岛，问你从任意一个岛出发，走遍所有岛（不一定要回到出发的岛），深水区不能走，问你最少能走多少浅水区？

我们可以 bfs 求岛数，以及陆地属于哪个岛。陆地或浅水区到浅水区建一条边权是一的边，陆地或浅水区到陆地建一条边权是零的边。用双端队列求出陆地到其他点的最短路，求出两两岛间最短路。枚举起点，设 $dp_{s,e}$ 为走到了集合 $s$，最后一个走到的是 $e$ 的最短路。转移的话，找到一个在 $s$ 中且不是 $e$ 的点 $p$，$dp_{s,e}=\min(dp_{s,e},dp_{s-e,p}+f_{p,e})$，$f_{i,j}$ 为岛 $i$ 到岛 $j$ 的最短路。最后的答案，走了全集，枚举 $e$，更新答案。

时间复杂度是 $O((rc)^2+2^n n^2)$。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[51][51],st[16],f[51][51],t,di[16][16],d[51][51][51][51],dp[1<<16][16],id[51][51],c[4][2]={0,1,0,-1,1,0,-1,0},ans=1e9;
char s[51];
queue<pair<int,int> >q;
void bfs(int i,int j){
	deque<pair<int,int> >q;
	memset(d[i][j],0x3f,sizeof(d[i][j])),d[i][j][i][j]=0,memset(f,0,sizeof(f)),q.push_back({i,j}),f[i][j]=1;
	while(q.size()){
		int e=q.front().first,b=q.front().second;q.pop_front();
		for(int w=0;w<4;w++){
			int ii=e+c[w][0],jj=b+c[w][1];
			if(a[ii][jj]&&!f[ii][jj])
				if(a[ii][jj]==1)d[i][j][ii][jj]=d[i][j][e][b],f[ii][jj]=1,q.push_front({ii,jj});
				else d[i][j][ii][jj]=d[i][j][e][b]+1,f[ii][jj]=1,q.push_back({ii,jj});
		}
	}
}
int g(int i){
	memset(dp,0x3f,sizeof(dp)),dp[0][i-1]=0,dp[1<<(i-1)][i-1]=0;
	for(int w=1;w<(1<<t);w++){
		if(!(w>>(i-1)&1))continue;
		for(int x=0;x<t;x++)if(w>>x&1)for(int y=0;y<t;y++)if((w>>y&1)&&(y!=x))dp[w][x]=min(dp[w][x],dp[w-(1<<x)][y]+di[y+1][x+1]);
	}
	int s=1e9;
	for(int w=0;w<t;w++)s=min(s,dp[(1<<t)-1][w]);
	return s;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int w=1;w<=n;w++){
    	scanf("%s",s+1);
    	for(int x=1;x<=m;x++)if(s[x]=='X')a[w][x]=1;else if(s[x]=='S')a[w][x]=2;
	}
	for(int w=1;w<=n;w++)for(int x=1;x<=m;x++)if(a[w][x]==1&&!id[w][x]){
		q.push({w,x}),id[w][x]=++t;
		while(q.size()){
			int i=q.front().first,j=q.front().second;q.pop();
			for(int y=0;y<4;y++){
				int ii=i+c[y][0],jj=j+c[y][1];
				if(a[ii][jj]==1&&!id[ii][jj])id[ii][jj]=t,q.push({ii,jj});
			}
		}
	}
	for(int w=1;w<=n;w++)for(int x=1;x<=m;x++)if(a[w][x]==1)bfs(w,x);
	for(int w=1;w<=t;w++)memset(di[w],0x3f,sizeof(di[w]));
	for(int w=1;w<=n;w++)for(int x=1;x<=m;x++)for(int y=1;y<=n;y++)for(int z=1;z<=m;z++)di[id[w][x]][id[y][z]]=min(di[id[w][x]][id[y][z]],d[w][x][y][z]);
	for(int w=1;w<=t;w++)ans=min(ans,g(w));
	printf("%d",ans);
    return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P3070)

**建议管理员在题面中加入“保证岛屿个数不超过 15”**。

首先我们可以预处理出有几块小岛，每个格子属于哪个小岛。可以 $O(n^2)$ 处理。

然后进行 bfs。对于每个小岛求出它与其它小岛的最短距离 $dis$（最少需要经过几个浅水区）。这里可以使用双端队列优化，将浅水区从后面插入，陆地从前面插入，这样可以保证其正确性（避免太长的岛屿使得其它先行更新）。时间复杂度 $O(n^3)$。

最后进行 dp。设 $f(i,j)$ 为上一个选岛 $j$，岛屿选择状态为 $i$ 的最小值。

转移可以主动转移，$f(i + j,j) = f(i,k) + dis(k,j)$，其中 $i + j$ 代表将 $j$ 并入状态 $i$。此时我们要枚举 $k$ 和 $j$ 进行转移，时间复杂度 $O(2^nn^2)$。

最后答案就是 $\min_{i = 1}^{\text{island num}} f(全选,i)$。

总时间复杂度 $O(2^nn^2)$，但是跑得飞快，~~甚至还拿下了 [最优解](https://www.luogu.com.cn/record/161366915)~~。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 55;

char mp[N][N];
bool vis[N][N];
int n, m, id[N][N], totid, dis[N][N], f[( 1 << 15 ) + 1][16];
struct pos { int x, y, w; pos() {} pos( int x, int y, int w ) : x( x ), y( y ), w( w ) {} };

//找出每个岛屿的范围
void dfs( int x, int y ) {
    if( vis[x][y] || x <= 0 || x > n || y <= 0 || y > m || mp[x][y] != 'X' ) return ;
    vis[x][y] = 1, id[x][y] = totid;
    dfs( x + 1, y ), dfs( x - 1, y ), dfs( x, y + 1 ), dfs( x, y - 1 );
}

//搜索该岛到其它岛的最短路
void bfs( int u ) {
    memset( vis, 0, sizeof vis );
    deque<pos> q;
    dis[u][u] = 0;
    for( int i = 1; i <= n; ++i ) 
        for( int j = 1; j <= m; ++j ) 
            if( id[i][j] == u )
                q.push_front( pos( i, j, 0 ) ), vis[i][j] = 1;
    while( !q.empty() ) {
        pos p = q.front(); q.pop_front();
        int x = p.x, y = p.y, w = p.w;
        if( mp[x][y] == 'X' ) dis[u][id[x][y]] = min( w, dis[u][id[x][y]] );
        if( !vis[x + 1][y] ) {
            vis[x + 1][y] = 1;
            if( mp[x + 1][y] == 'S' ) q.push_back( pos( x + 1, y, w + 1 ) );
            if( mp[x + 1][y] == 'X' ) q.push_front( pos( x + 1, y, w ) );
        }
        if( !vis[x - 1][y] ) {
            vis[x - 1][y] = 1;
            if( mp[x - 1][y] == 'S' ) q.push_back( pos( x - 1, y, w + 1 ) );
            if( mp[x - 1][y] == 'X' ) q.push_front( pos( x - 1, y, w ) );
        }
        if( !vis[x][y + 1] ) {
            vis[x][y + 1] = 1;
            if( mp[x][y + 1] == 'S' ) q.push_back( pos( x, y + 1, w + 1 ) );
            if( mp[x][y + 1] == 'X' ) q.push_front( pos( x, y + 1, w ) );
        }
        if( !vis[x][y - 1] ) {
            vis[x][y - 1] = 1;
            if( mp[x][y - 1] == 'S' ) q.push_back( pos( x, y - 1, w + 1 ) );
            if( mp[x][y - 1] == 'X' ) q.push_front( pos( x, y - 1, w ) );
        }
    }
    return ;
}

inline int read() {
    int x = 0; char ch = getchar();
    while( ch < '0' || ch > '9' ) ch = getchar();
    while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48, ch = getchar();
    return x;
}

inline char readc() {
    char ch = getchar();
    while( ch != '.' && ch != 'S' && ch != 'X' ) ch = getchar();
    return ch;
}

int main(){
    n = read(), m = read();
    for( int i = 1; i <= n; ++i )
        for( int j = 1; j <= m; ++j )
            mp[i][j] = readc();

    //找出所有岛屿覆盖范围
    for( int i = 1; i <= n; ++i ) 
        for( int j = 1; j <= m; ++j )
            if( !vis[i][j] && mp[i][j] == 'X' ) ++totid, dfs( i, j );
    //找出该岛到其它岛的最短距离
    for( int i = 1; i <= totid; ++i ) {
        for( int j = 1; j <= totid; ++j )
            if( i != j )
                dis[i][j] = 1e9;
        bfs( i );
    }

    for( int i = 0; i < ( 1 << totid ); ++i )
        for( int j = 1; j <= totid; ++j )
            f[i][j] = 1e9;
    for( int i = 0; i < totid; ++i ) f[1 << i][i + 1] = 0;

    //dp
    for( int i = 0; i < ( 1 << totid ); ++i ) {
        for( int k = 0; k < totid; ++k ) {
            if( i & ( 1 << k ) ) //状态中包含k才能选
            for( int j = 0; j < totid; ++j ) {
                f[i | ( 1 << j )][j + 1] = min( f[i | ( 1 << j )][j + 1], f[i][k + 1] + dis[k + 1][j + 1] ); //枚举新点j
            }
        }
    }
    
    //统计答案
    int ans = 1e9;
    for( int i = 1; i <= totid; ++i ) ans = min( ans, f[( 1 << totid ) - 1][i] );
    printf( "%d\n", ans );
    return 0;
}
```

---

## 作者：Edward_Elric (赞：0)

## 思路
这是一个非常恶心的题。首先不难想到要预处理连通块和他们两两间的距离，剩下就是一个裸的状压。开两维，一维状态，一维决策点即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
int dis[15+5][15+5],d[50+5][50+5],f[1<<16][16],vis[50+5][50+5],tot[15+5],inq[50+5][50+5];
char mapn[50+5][50+5];
int cnt;
int ans=inf;
struct point{
	int x,y;
}p[15+5][2500+5];
struct node{
	int x,y;
	node(int a,int b):x(a),y(b){} 
};
int n;
int r,c;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f; 
}
void wzyn(node s){
	queue<node>q;
	q.push(s);
	++cnt;
	vis[s.x][s.y]=cnt;
	while(!q.empty()){
		node u=q.front();
		q.pop();
		++tot[cnt];
		p[cnt][tot[cnt]].x=u.x;
		p[cnt][tot[cnt]].y=u.y;
		for(int i=0;i<4;i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(nx<1||nx>r||ny<1||ny>c)continue;
			if(vis[nx][ny])continue;
			if(mapn[nx][ny]=='X')q.push(node(nx,ny));
			vis[nx][ny]=cnt;
		}
	}
}
void lxl(int s){
	queue<node>q;
	memset(d,inf,sizeof(d)); 
	for(int i=1;i<=tot[s];i++){
		int x=p[s][i].x,y=p[s][i].y;
		d[x][y]=0;q.push(node(x,y));
		inq[x][y]=1;
    }
	while(!q.empty()){
		node u=q.front();
		q.pop();
		inq[u.x][u.y]=0;
		for(int i=0;i<4;i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(nx<1||nx>r||ny<1||ny>c)continue;
			if(mapn[nx][ny]=='.')continue;
			if(mapn[nx][ny]=='X'){
				if(d[nx][ny]>d[u.x][u.y]){
					d[nx][ny]=d[u.x][u.y];
					if(!inq[nx][ny])q.push(node(nx,ny));
				}
				dis[s][vis[nx][ny]]=min(dis[s][vis[nx][ny]],d[nx][ny]);
			}
			else {
				if(d[nx][ny]>d[u.x][u.y]+1){
					d[nx][ny]=d[u.x][u.y]+1;
					if(!inq[nx][ny])q.push(node(nx,ny));
				}
			} 
		}
	}
	
}
int main(){
	r=read();c=read();
	for(int i=1;i<=r;i++)
	scanf("%s",mapn[i]+1);
	for(int i=1;i<=r;i++)
	  for(int j=1;j<=c;j++)
	  if(!vis[i][j]&&mapn[i][j]=='X')wzyn(node(i,j));
	memset(dis,inf,sizeof(dis));
	for(int i=1;i<=cnt;i++)
	lxl(i);
	/*
	for(int i=1;i<=cnt;i++,putchar(' '))
	cout<<tot[i];
	cout<<endl;
	for(int i=1;i<=cnt;i++,putchar('\n'))
	  for(int j=1;j<=cnt;j++,putchar(' '))
	  cout<<dis[i][j];
	*/
	memset(f,inf,sizeof(f));
	for(int i=1;i<=cnt;++i)
	f[1<<(i-1)][i]=0;
	for(int i=0;i<(1<<cnt);i++){
		for(int j=1;j<=cnt;j++){
			if(!(i&(1<<(j-1))))continue;
			for(int k=1;k<=cnt;k++){
				if(k==j)continue;
				int s=(i^(1<<(j-1)));
				f[i][j]=min(f[i][j],f[s][k]+dis[j][k]);
			}
		}
	}

	for(int i=1;i<=cnt;i++)
	ans=min(ans,f[(1<<cnt)-1][i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：mengdai (赞：0)

来一发记忆化搜索

至于题解，下面已经很详细了

但我还是在来口胡一下吧f[i][j]表示第i个点，其他几个点的状态为j时，遍历所有点的最短路

然后枚举没有到达过的点转移



```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
int n,m,cnt;
char str[1003][1003];
int vis[1003][1003],num[1003][1003],pic[60][60],d[60];
int dir[13][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<int> q;
inline void bfs(int i,int j){
    memset(vis,inf,sizeof(vis));
    vis[i][j]=1;
    q.push(i);
    q.push(j);
    while(!q.empty()){
        int x=q.front();  q.pop();
        int y=q.front();  q.pop();
        for(int k=0;k<4;++k){
            int xx=x+dir[k][0],yy=y+dir[k][1];
            if(!(xx<1||xx>n||yy<1||yy>m||str[xx][yy]=='.')){
                int temp=vis[x][y];
                if(!(temp>vis[xx][yy])){
                    if(str[xx][yy]=='X'){
                            if(temp<vis[xx][yy]){
                            vis[xx][yy]=temp;
                            pic[num[xx][yy]][num[i][j]]=min(pic[num[xx][yy]][num[i][j]],vis[xx][yy]-1);
                               pic[num[i][j]][num[xx][yy]]=pic[num[xx][yy]][num[i][j]];
                            q.push(xx);
                            q.push(yy);
                        }
                    }else{
                        if((++temp)<vis[xx][yy]){
                            vis[xx][yy]=temp;
                            q.push(xx);
                            q.push(yy);
                        }
                    }
                }
            }
        }
    }
}
inline void dfs(int x,int y){
    for(int i=0;i<4;i++){
        int xx=x+dir[i][0],yy=y+dir[i][1];
        if(!(xx<1||xx>n||yy<1||yy>m||str[xx][yy]!='X'||num[xx][yy])){
            num[xx][yy]=cnt;
            dfs(xx,yy);
        }
    }
}
int jiyi[20][1<<16];
int dp(int now,int h){
    int & fanhui=jiyi[now][h];
    if(fanhui!=-1){
        return fanhui;
    }
    bool yes=true;
    for(int i=1;i<=cnt;i++){
        if(!(h&(1<<i))){
            yes=false;
            break;
        }
    }
    if(yes==true){
        return fanhui=0;
    }
    fanhui=999999999;
    for(int i=1;i<=cnt;i++){
        if(!(h&(1<<i))&&now!=i){
            fanhui=min(fanhui,dp(i,h|(1<<i))+pic[now][i]);
        }
    }
    return fanhui;
}
int main(){
    int i,j;
    memset(pic,inf,sizeof(pic));
    memset(jiyi,-1,sizeof(jiyi));
    cin>>n>>m;
    for(i=1;i<=n;++i){
        scanf("%s",str[i]+1);
    }
    for(i=1;i<=n;++i){
        for(j=1;j<=m;++j){
            if(str[i][j]=='X'&&!num[i][j]){
                num[i][j]=++cnt;
                dfs(i,j);
            }
        }
    }
    for(i=1;i<=n;++i){
        for(j=1;j<=m;++j){
            if(num[i][j]){
                bfs(i,j);
            }
        }
    }
    int ans=999999999;
    for(int i=1;i<=cnt;i++){
        ans=min(ans,dp(i,(1<<i)));
    }
    cout<<ans<<endl;
    return 0;
}
```
/\*

in:
5 4
XX.S
.S..
SXSS
S.SX
..SX

out:
3

\*/

---

