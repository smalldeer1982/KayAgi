# [COTS 2019] 挑战 Izazov

## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T1。$\texttt{15s,0.5G}$。

## 题目描述


给定 $N\times M$ 的黑白矩阵。用尽可能少数量的矩形覆盖住所有黑色格子，要求：
- 每个黑色格子**恰好被一个**矩形覆盖；
- 任意两个矩形不重叠；
- 矩形不覆盖白色格子。

并输出方案。

## 说明/提示



对于 $100\%$ 的数据，保证 $1\le N,M\le 500$。


| 测试点编号 | $N,M\le $    | 得分 |  
| :--: | :--: |:--: |  
| $ 1\sim 5 $    | $ 26 $ |   $ 25 $   |  
| $ 6\sim 10 $    | $ 100 $ |  $ 25 $   |  
| $ 11\sim 15 $    | $ 250 $ | $ 25 $   |  
| $ 16\sim 20 $    | $ 500 $ |$ 25 $   |  

【计分方式】

如果你输出的是最优解，得满分。

否则，设最优解用的矩形数量为 $A$，你的解用的矩形数量为 $B$，该测试点得分为 $0.75\cdot (A/B)^{10}\cdot 5$ 分。 

## 样例 #1

### 输入

```
4 5
CCBCB
CCBBB
CCCBB
CCCBB```

### 输出

```
1 1 0 2 0
1 1 0 0 0
3 3 3 0 0
3 3 3 0 0```

## 样例 #2

### 输入

```
7 5
CCCBB
BCBBB
BCCCB
BCCCB
CCCCC
BBBBB
BCCCB```

### 输出

```
1 1 1 0 0
0 2 0 0 0
0 3 3 3 0
0 3 3 3 0
4 4 4 4 4
0 0 0 0 0
0 5 5 5 0```

## 样例 #3

### 输入

```
5 11
BBCCCBCCCBC
BCCBCBBCCCC
CCCCBCCCCCC
BCBCCCBCCCB
CCCCBCBBCCB```

### 输出

```
0 0 1 1 1 0 2 2 2 0 3
0 4 4 0 5 0 0 6 6 6 3
7 7 7 7 0 8 8 6 6 6 3
0 9 0 10 10 10 0 6 6 6 0
11 11 11 11 0 12 0 0 13 13 0```

# 题解

## 作者：andychen_2012 (赞：3)

这原来竟是一道论文题，确实较难。

论文链接：[Graph-Theoretic Solutions to Computational Geometry Problems](https://arxiv.org/abs/0908.3916)。

我们一步步来吧。

首先我们有一个非常直接的想法，将所有横着的连续段划分成一个矩形，或将所有竖着的连续段划分成一个矩形，这样子可以获得 30pts 的好成绩。

接下来我们考虑合并两个相邻的大小相同的矩形，进行完合并后，可以得到 38pts 的好成绩。

为啥这不对呢？主要是因为有些可以合并的矩形因为合并后会将原有的一个矩形切割开，因此就没有去合并。应该如何去找到这些需要去合并的矩形呢？

到这里之后卡住了，那不如我们来思考一下最终的最小覆盖数如何计算好了。

我们认为一个连通块是一个多边形，多边形中可能存在一些洞，如下图 1。

![](https://cdn.luogu.com.cn/upload/image_hosting/ia4i10vm.png)

我们注意到一个矩形有四个角，那么我们切分出来的矩形数 $\times 4$ 应该不少于原来多边形的顶点数。

那么切分后多出来的顶点数由什么贡献呢？由凹顶点所在的边与原多边形上的边（或另一个划分出的矩形的边）相交而贡献。但是假如矩形的某条边的端点是两个凹顶点，则不会贡献出新的顶点。

那么我们有这样的结论：

定义**好对角线**为输入多边形内部连接多边形两个凹顶点的轴平行线段。具有 $n$ 个顶点和 $h$ 个洞的多边形中划分出的矩形的最小数量为 $\frac{n}{2}+h-g-1$，其中 $g$ 是一组不相交的好对角线的最大大小。

**证明**：

1. 设 $G$ 是构成多边形由不相交的好对角线所构成的的最大集合，并将**坏顶点**定义为不是 $G$ 中任意一条对角线端点的非凸多边形顶点。每个多边形顶点至少贡献一个矩形的顶点。

2. 对于每个坏顶点 $v$，令 $s$ 表示一条以 $v$ 为端点的线段。则 $s$ 有如下两种情况：

   1. $s$ 穿过 $G$ 中的一段，并且由交叉形成的两个角相对于交叉段与 $v$ 在同一侧，可以被归咎于 $v$。
   2. $s$在非顶点处结束。在这种情况下，$s$ 的另一端点形成的两个角可以被归咎于 $v$。

   由这两种情况可以得到，一个划分中，矩形角的数量至少为 $n+ 2 |v|$，其中 $|v|$ 表示坏顶点的数量。

3. 在任何有 $h$ 个洞的多边形中，非凸顶点的数量是 $n/2+2h-2$，因此坏顶点的数量为 $n/2+2h-2|G|-2$，并且遵循 $n/2+h-|G|-1$ 个矩形的下限。

4. 相反，如果 $G$ 是任何一组不相交的好对角线，那么通过依次考虑 $G$ 的坏顶点，并将一条线段从每个坏顶点延伸到最近的先前添加的线段或多边形边，可以找到一个正好有 $n/2+h-|G|-1$ 个矩形的划分方案。因此，将一个多边形划分为最小数量的矩形相当于找到最大数量的不相交好对角线。

好对角线的交集图是二分的：每个水平对角线只与垂直对角线相交，反之亦然。因此，在图论中，找到不相交好对角线的最大数量转化为在二分图中找到最大独立集。根据 $\text{K\"onig}$ 定理，在任何 $n$-顶点二分图中，最大独立集的大小为 $n-M$，其中 $M$ 是最大匹配的数量。

我们注意到两条对角线最多交于一点，一个点最多被两条对角线经过。因此我们对每个点记录哪条对角线经过它，如果有两条对角线同时经过它，则在二分图上，这两条对角线有一条边。

可以直接写一个匈牙利跑二分图最大独立集，从上面可以看出边数和点数之积大小最大在 $O(n^3)$。

那么根据凹对角线划分完之后，我们得到所有划分出来的多边形都满足如下的性质：不存在凹对角线，这样子我们可以直接按合并算法做即可，每次合并两个相同大小的在同一个划分中的矩形。如下是样例 3 的多边形及其凹对角线划分，绿线即为最大的凹对角线连边集，蓝线为多边形的边：

![](https://cdn.luogu.com.cn/upload/image_hosting/7i2z36pi.png)

图丑，见谅。

当然，如果想更快一些，可以使用网络流来做二分图最大独立集。下面的代码使用了网络流。

还有一个细节在如何找对角线，我的做法是寻找所有形如下面形状的位置：

```
BC  CB  CC  CC
CC  CC  BC  CB
```

凹顶点只在这些位置上出现，每次对于两个相邻凹顶点间连边即可，时间复杂度是 $O(n^2)$ 的。注意一共有 8 种可能的相邻凹顶点图形，要讨论清楚。


```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0;
	int f=0,ch=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(ll x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int ch[40]={0},cnt=0;
	while(x){
		ch[cnt++]=(int)(x%10);
		x/=10;
	}
	while(cnt--) putchar(ch[cnt]+48);
	putchar(end);
}
const int N=505;
int n,m;
char s[N][N];
int a[N][N],cnt;
int sum[N][N];
bool vis[N*N],bel[N][N][2];
int to[N*N];
int tot,left;
int bevis[N][N][2];
inline bool check(int a1,int a2,int b1,int b2,int c1,int c2){return s[a1][a2]=='C'&&s[b1][b2]=='C'&&s[c1][c2]=='B';}
inline void init(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(s[i][j]=='C');
		}
	}
	for(int i=2;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(s[i][j]=='B') continue;
			if(j>1&&check(i-1,j,i,j-1,i-1,j-1)){
				for(int k=i;k<n;++k){
					if(s[k][j]=='B') break;
					bool f1=check(k+1,j,k,j-1,k+1,j-1);
					bool f2=check(k+1,j-1,k,j-1,k+1,j);
					if(f1||f2){
						++tot;
						for(int t=i;t<=k;++t) bevis[t][j][0]=tot;
						break;
					}
				}
			}
			if(j<m&&check(i-1,j,i,j+1,i-1,j+1)){
				for(int k=i;k<n;++k){
					if(s[k][j]=='B') break;
					bool f1=check(k+1,j,k,j+1,k+1,j+1);
					bool f2=check(k+1,j+1,k,j+1,k+1,j);
					if(f1||f2){
						++tot;
						for(int t=i;t<=k;++t) bevis[t][j+1][0]=tot;
						break;
					}
				}
			}
		}
	}
	left=tot;
	for(int i=1;i<=n;++i){
		for(int j=2;j<=m;++j){
			if(s[i][j]=='B') continue;
			if(i>1&&check(i-1,j,i,j-1,i-1,j-1)){
				for(int k=j;k<m;++k){
					if(s[i][k]=='B') break;
					bool f1=check(i-1,k,i,k+1,i-1,k+1);
					bool f2=check(i-1,k,i-1,k+1,i,k+1);
					if(f1||f2){
						++tot;
						for(int t=j;t<=k;++t) bevis[i][t][1]=tot;
						break;
					}
				}
			}
			if(i<n&&check(i+1,j,i,j-1,i+1,j-1)){
				for(int k=j;k<m;++k){
					if(s[i][k]=='B') break;
					bool f1=check(i+1,k,i,k+1,i+1,k+1);
					bool f2=check(i+1,k,i+1,k+1,i,k+1);
					if(f1||f2){
						++tot;
						for(int t=j;t<=k;++t) bevis[i+1][t][1]=tot;
						break;
					}
				}
			}
		}
	}
}
struct node{
	int to,nxt,w;
}e[N*N<<2];
int head[N*N],ecnt=1;
inline void add(int u,int v,int w){
	e[++ecnt]={v,head[u],w};
	head[u]=ecnt;
}
const int inf=2e9;
int dis[N*N],now[N*N];
queue<int> q;
inline bool bfs(){
	while(!q.empty()) q.pop();
	for(int i=0;i<=tot+1;++i) dis[i]=inf;
	dis[0]=0;
	now[0]=head[0];
	q.push(0);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=now[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w>0&&dis[v]==inf){
				dis[v]=dis[u]+1;
				now[v]=head[v];
				if(v==tot+1) return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
inline int dfs(int u,int sum){
	if(u==tot+1) return sum;
	int res=0;
	for(int i=now[u];i&&sum;i=e[i].nxt){
		now[u]=i;
		int v=e[i].to;
		if(e[i].w>0&&dis[v]==dis[u]+1){
			int d=dfs(v,min(sum,e[i].w));
			if(!d) dis[v]=inf;
			res+=d;sum-=d;
			e[i].w-=d;e[i^1].w+=d;
		}
	}
	return res;
}
inline void getmatching(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if((bevis[i][j][0]||bevis[i-1][j][0])&&(bevis[i][j][1]||bevis[i][j-1][1])){
				int u=bevis[i][j][0]|bevis[i-1][j][0];
				int v=bevis[i][j][1]|bevis[i][j-1][1];
				add(u,v,1);add(v,u,0);
			}
		}
	}
	for(int i=1;i<=left;++i) add(0,i,1),add(i,0,0);
	for(int i=left+1;i<=tot;++i) add(i,tot+1,1),add(tot+1,i,0);
	while(bfs()) dfs(0,inf);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(bevis[i][j][0]&&dis[bevis[i][j][0]]!=inf) bel[i][j][0]=1;
			if(bevis[i][j][1]&&dis[bevis[i][j][1]]==inf) bel[i][j][1]=1;
		}
	}
}
inline void solve(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(s[i][j]=='B'||a[i][j]) continue;
			int r=j;
			for(int k=j+1;k<=m;++k){
				if(s[i][k]=='B'||bel[i][k][0]) break;
				r=k;
			}
			int plc=i;
			for(int k=i+1;k<=n;++k){
				if(bel[k][j][1]) break;
				if(sum[k][r]-sum[k][j-1]-sum[i-1][r]+sum[i-1][j-1]!=(r-j+1)*(k-i+1)) break;
				if(j>1&&(s[k][j-1]=='C'&&(!a[k][j-1])&&(!bel[k][j][0]))) break;
				if(r<m&&(s[k][r+1]=='C'&&(!a[k][r+1])&&(!bel[k][r+1][0]))) break;
				plc=k;
			}
			++cnt;
			for(int k=i;k<=plc;++k){
				for(int t=j;t<=r;++t)
					a[k][t]=cnt;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)
			vis[a[i][j]]=1;
	}
	int ncnt=0;
	for(int i=1,now=1;i<=cnt;++i){
		if(vis[i]) to[i]=now++,++ncnt;
	}
	cnt=ncnt;
}
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	init();
	getmatching();
	solve();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)
			write(a[i][j],j==m?'\n':' ');
	}
	return 0;
}
```

---

## 作者：qzmoot (赞：1)

# 题解：P11224 [COTS 2019] 挑战 Izazov
## 前言
被学长丢到了模拟赛的最后一题，然后把我们干爆了。
## 题目大意
给出一个图形，询问这个图形最少能够被多少个矩形覆盖，并输出方案。
## 题目分析
注意到矩形有一个十分特殊的性质，矩形所有角都是直角。并且若所有角为直角，则这个图形一定只由矩形构成。\
而在给出的图形里，除了直角和平角以外，还会有比较难处理的 270 度角。对于这种角，我们会想到找一个方向把这个角切成直角和平角。\
那么，为了切出矩形尽量少，就等价于切出的直角尽量少，所以我们尽量用一刀切开 2 个 270 度的角。于是就得到了一个简单的思路是把每 2 个 270 度的角连起来切，实在没有对应的就单个切。

![反例](https://cdn.luogu.com.cn/upload/image_hosting/qlp8d8i1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

观察这张图，四周为 270 度角，若我们将中间的 270 度角按这样切的话，会又多切出 4 个直角，显然变劣。\
那么对于相交的切法，可以发现，只有竖着的边会与横着的边相交，也就是说，我们可以把横边与竖边看作两个不重的点集从而构建出二分图。其的最大权独立集就是我们最优切法要切的哪些边。\
跑网络流，有定理最大流等于最小点覆盖，最大权独立集是最小点覆盖的补集。求出最大流后，最小点覆盖的构造方案为残量网络上源点不可达的左部点，和可达的右部点。
## 细节处理
首先 270 度角是容易寻找的。遍历所有的 $2\times 2$ 的格子，判断是否构成 $L$ 型。存储则可以将网格转化为网格线的交点处理，因为进行切割是沿网格线切割的。\
接着我们可以遍历所有的 270 度点，向能切割的方向扩展，寻找是否能有对应的点，若有，则覆盖经过的路径并向经过路径中和其他存在的切割线连边；若没有，则先忽略这个点。\
于是，我们就可以处理出一个二分图，跑完最大流，我们再搜索残量网络上的点。对总点集遍历，判断当前点是否符合条件，若符合则进行切割，切割操作可以看作对于一条边来说覆盖了上面的所有端点。\
对于剩下的，没有被切割的点，我们可以向任意方向扩展，直到与其他切割线相交或者切完了当前图形。\
最后的染色使用 bfs，每次移动的时候判断通过的边是否被打上了切割标记即可。\
于是这道论文题就愉快的做完了。
## Code
```cpp
#include <bits/stdc++.h>
#define debug(x) cout<<#x<<':'<<x<<'\n'
#define pb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
constexpr int N=1005,inf=1e9;
mt19937 rnd(time(0));
int n,m;
string s[N];
struct node{
	int x,y;
	bool w,a,s,d;
	node(){}
	node(int x,int y,bool w,bool a,bool s,bool d):x(x),y(y),w(w),a(a),s(s),d(d){}
};
int tot=1;
int hd[N*N*2],now[N*N*2];
struct edge{
	int to,nxt,val;
}e[N*N*2];
void add(int u,int v,int w)
{
	e[++tot].to=v;
	e[tot].val=w;
	e[tot].nxt=hd[u];
	hd[u]=tot;
	
	e[++tot].to=u;
	e[tot].val=0;
	e[tot].nxt=hd[v];
	hd[v]=tot;
}
bool acl[N][N],acu[N][N];
int id[N][N];
vector<node>p;
struct line{
	int x1,y1,x2,y2;
	line(){}
	line(int x1,int y1,int x2,int y2):x1(x1),y1(y1),x2(x2),y2(y2){}
}ln[N*N];
int idx;
int S=0,T;
int dis[N*N];
int mxf;
int ans[N][N];
inline bool bfs()
{
	for(int i=0;i<=idx+1;i++)
		dis[i]=inf;
	queue<int>q;
	q.push(S);
	dis[S]=0;
	now[S]=hd[S];
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=hd[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(e[i].val>0 && dis[v]==inf)
			{
				q.push(v);
				now[v]=hd[v];
				dis[v]=dis[u]+1;
				if(v==T)
					return true;
			}
		}
	}
	return false;
}
bool usd[N*N];
int sep1[N][N];
int sep2[N][N];
bool inmat[N*N];
bool innet[N][N];
int dfs(int u,int sum)
{
	inmat[u]=1;
	if(u==T)
		return sum;
	int k,res=0;
	for(int i=now[u];i && sum;i=e[i].nxt)
	{
		now[u]=i;
		int v=e[i].to;
		if(e[i].val>0 && (dis[v]==dis[u]+1))
		{
			k=dfs(v,min(sum,e[i].val));
			if(!k)
				dis[v]=inf;
			e[i].val-=k;
			e[i^1].val+=k;
			res+=k;
			sum-=k;
		}
	}
	return res;
}
void dfs(int u)
{
	usd[u]=1;
	for(int i=hd[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==S || v==T || usd[v])
			continue;
		if(e[i].val)
			dfs(v);
	}
}
void bfs(int sx,int sy,int col)
{
	queue<pii>q;
	q.push(mp(sx,sy));
	ans[sx][sy]=col;
	while(!q.empty())
	{
		int x=q.front().fi,y=q.front().se;
		q.pop();
		int nx=x,ny=y+1;
		if(nx<=n && ny<=m && s[nx][ny]=='C' && !ans[nx][ny] && (sep2[x][y+1]!=sep2[x+1][y+1] || !sep2[x][y+1] || !sep2[x+1][y+1]))
			q.push(mp(nx,ny)),ans[nx][ny]=col;
		nx=x+1,ny=y;
		if(nx<=n && ny<=m && s[nx][ny]=='C' && !ans[nx][ny] && (sep1[x+1][y]!=sep1[x+1][y+1] || !sep1[x+1][y] || !sep1[x+1][y+1]))
			q.push(mp(nx,ny)),ans[nx][ny]=col;
	}
}
int col;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i],s[i]=" "+s[i];
	memset(id,-1,sizeof id);
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
		{
			if(s[i][j]=='C' && s[i+1][j]=='C' && s[i][j+1]=='C' && s[i+1][j+1]=='B')
				p.pb(i+1,j+1,0,0,1,1),acl[i+1][j+1]=1,acu[i+1][j+1]=1;
			else if(s[i][j]=='C' && s[i+1][j]=='B' && s[i][j+1]=='C' && s[i+1][j+1]=='C')
				p.pb(i+1,j+1,0,1,1,0),acu[i+1][j+1]=1;
			else if(s[i][j]=='C' && s[i+1][j]=='C' && s[i][j+1]=='B' && s[i+1][j+1]=='C')
				p.pb(i+1,j+1,1,0,0,1),acl[i+1][j+1]=1;
			else if(s[i][j]=='B' && s[i+1][j]=='C' && s[i][j+1]=='C' && s[i+1][j+1]=='C')
				p.pb(i+1,j+1,1,1,0,0);
		}
	for(auto v:p)
	{
		if(!v.s)
		{
			idx++;
			if(s[v.x][v.y-1]=='C' && s[v.x][v.y]=='C')
			{
				bool fl=0;
				for(int i=v.x+1,j=v.y;i<=n+1;i++)
				{
					if(acu[i][j])
					{
						fl=1;
						break;
					}
					if(s[i][j-1]!='C' || s[i][j]!='C')
						break;
				}
				for(int i=v.x,j=v.y;i<=n+1;i++)
				{
					if(fl)
					{
						if(~id[i][j])
							add(id[i][j],idx,1);
						id[i][j]=idx;
					}
					if(i!=v.x && acu[i][j])
					{
						//innet[v.x][v.y]=innet[i][j]=1;
						ln[idx]=line(v.x,v.y,i,j);
						break;
					} 
					if(i!=v.x && (s[i][j-1]!='C' || s[i][j]!='C'))
						break;
				}
			}
			if(!ln[idx].x1)
				idx--;
		}
		if(!v.d)
		{
			idx++;
			if(s[v.x-1][v.y]=='C' && s[v.x][v.y]=='C')
			{
				bool fl=0;
				for(int i=v.x,j=v.y+1;j<=m+1;j++)
				{
					if(acl[i][j])
					{
						fl=1;
						break;
					}
					if(s[i-1][j]!='C' || s[i][j]!='C')
						break;
				}
				for(int i=v.x,j=v.y;j<=m+1;j++)
				{
					if(fl)
					{
						if(~id[i][j])
							add(idx,id[i][j],1);
						id[i][j]=idx;
					}
					if(j!=v.y && acl[i][j])
					{
						//innet[v.x][v.y]=innet[i][j]=1;
						ln[idx]=line(v.x,v.y,i,j);
						break;
					}
					if(j!=v.y && (s[i-1][j]!='C' || s[i][j]!='C'))
						break;
				}
			}
			if(!ln[idx].x1)
				idx--;
		}
	}
	T=idx+1;
//	debug(idx);
	for(int i=1;i<=idx;i++)
		if(ln[i].x1)
			if(ln[i].x1==ln[i].x2)
				add(S,i,1);
			else
				add(i,T,1);
	while(bfs())
		mxf+=dfs(S,inf);
//	debug(mxf);
	dfs(S);
	for(int i=1;i<=idx;i++)
		if(ln[i].x1==ln[i].x2 && usd[i])
			for(int x=ln[i].x1,y=ln[i].y1,val=rnd();y<=ln[i].y2;y++)
				sep1[x][y]=val,innet[x][y]=1;
		else if(ln[i].y1==ln[i].y2 && !usd[i])
			for(int x=ln[i].x1,y=ln[i].y1,val=rnd();x<=ln[i].x2;x++)
				sep2[x][y]=val,innet[x][y]=1;
	for(auto v:p)
		if(!innet[v.x][v.y])
			if(!v.w)
				for(int i=v.x,j=v.y,val=rnd();i;i--)
				{
					sep2[i][j]=val,innet[i][j]=1;
					if(sep1[i][j])
						break;
					if(s[i-1][j-1]!='C' || s[i-1][j]!='C')
						break;
				}
			else
				for(int i=v.x,j=v.y,val=rnd();i<=n+1;i++)
				{
					sep2[i][j]=val,innet[i][j]=1;
					if(sep1[i][j])
						break;
					if(s[i][j-1]!='C' || s[i][j]!='C')
						break;
				}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='C' && !ans[i][j])
				bfs(i,j,++col);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cout<<ans[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```
## Tips
记得把数组开大一点。

---

## 作者：gdf_yhm (赞：1)

[P11224](https://www.luogu.com.cn/problem/P11224)

> 如果您觉得这个任务在比赛中很难，那是因为它确实很难。事实上，这个任务的创意最初是作为2017/2018赛季HONI比赛的提案提出的。这个任务的唯一问题是作者自己也无法解决它。然而，一些比作者更聪明的人也尝试解决这个任务，但他们也未能成功，因此这个任务就这样在尘封的天花板上积满了灰尘。
>
> 幸运的是，通过使用现代技术，即网络搜索引擎，作者找到了大卫·埃普斯坦（David Eppstein）于2009年发表的论文《图论方法解决计算几何问题》（“Graph-Theoretic Solutions to Computational Geometry Problems”），文中描述了该等价问题的解决方案。

### 思路

设 $(i,j)$ 表示 $i$ 行 $j$ 列格子的左上角，维护 $pl/pr/pu/pd_{i,j}$ 表示这个角四周伸出去的边两侧格子是否不同。

这样得到了黑色格子的轮廓，是一些可以有凹角和中空的多边形。考虑那些 $270^{\circ}$ 的角，可以选择反向延长某条边，分割为合法的 $90^{\circ}$。如果存在两个 $270^{\circ}$ 的角在同一行或列，连接这两个角，可以消去两个 $270^{\circ}$，生成两个 $90^{\circ}$。否则反向延长某条边至与某条边相交，消去一个 $270^{\circ}$，生成三个 $90^{\circ}$。

希望最小化矩形数量，等价于最小化 $90^{\circ}$ 角的数量。显然合并两个 $270^{\circ}$ 性价比更高。如果一个 $270^{\circ}$ 先后和两个 $270^{\circ}$ 相连，实际效果只有一对  $270^{\circ}$ 相连。所以等价于最大化 $270^{\circ}$ 的匹配。如果两个匹配的连线相交也不合法。但匹配只有横着和竖着两种，且只有横着和竖着能相交，对匹配建点，对冲突的匹配连边，为二分图，求最大独立集。

二分图最大独立集的补集等于最小点覆盖，最小点覆盖大小等于最大匹配的大小。最小点覆盖的构造为残量网络上 $S$ 不可达的左部点和 $S$ 可达的右部点。

找出那些匹配被选择后，将两个角连起来即将两点间的边设置为两侧格子（染色）不同。对于剩下的 $270^{\circ}$，随便选一边分割直至与另一条边相交。

复杂度为 $n\times m$ 个点 $n\times m$ 条边的二分图网络流，$O(nm\sqrt{nm})$。

### code

```cpp
int n,m;
char S[maxn];
bool a[maxn][maxn];
bool pl[maxn][maxn],pr[maxn][maxn],pu[maxn][maxn],pd[maxn][maxn];
int p1[maxn][maxn],p2[maxn][maxn];
map<tuple<int,int,int>,int> id;int idx1,idx2;
tuple<int,int,int> rnk[maxm];
int head[maxm],tot=1;
struct nd{
    int nxt,to,w;
}e[maxm];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<"\n";
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dep[maxm],rad[maxm];
queue<int> q;
bool bfs(){
    for(int i=1;i<=t;i++)dep[i]=0,rad[i]=head[i];
    dep[s]=1;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&!dep[v]){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dfs(int u,int res){
    if(u==t)return res;
    int cnt=0;
    for(int i=rad[u];i;i=e[i].nxt){
        int v=e[i].to;rad[u]=i;
        if(e[i].w&&dep[v]==dep[u]+1){
            int out=dfs(v,min(e[i].w,res));
            cnt+=out,res-=out;
            e[i].w-=out,e[i^1].w+=out;
            if(!res)break;
        }
    }
    return cnt;
}
bool vis[maxm];
void dfs(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==s||v==t||vis[v])continue;
        if(e[i].w)dfs(v);
    }
}
int bk[maxn][maxn];
int ans[maxn][maxn],res;
void col(int u,int v){
	if(ans[u][v])return ;ans[u][v]=res;
    if(a[u][v-1]&&!pd[u][v])col(u,v-1);
    if(a[u][v+1]&&!pd[u][v+1])col(u,v+1);
    if(a[u-1][v]&&!pr[u][v])col(u-1,v);
    if(a[u+1][v]&&!pr[u+1][v])col(u+1,v);
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",S+1);
        for(int j=1;j<=m;j++)a[i][j]=S[j]=='C';
    }
    n++,m++;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]!=a[i][j-1])pu[i+1][j]=pd[i][j]=1;
            if(a[i][j]!=a[i-1][j])pr[i][j]=pl[i][j+1]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]&&pu[i][j]&&!pd[i][j]&&pl[i][j]&&!pr[i][j])bk[i][j]=1;
            if(a[i][j-1]&&pu[i][j]&&!pd[i][j]&&!pl[i][j]&&pr[i][j])bk[i][j]=2;
            if(a[i-1][j]&&!pu[i][j]&&pd[i][j]&&pl[i][j]&&!pr[i][j])bk[i][j]=3;
            if(a[i-1][j-1]&&!pu[i][j]&&pd[i][j]&&!pl[i][j]&&pr[i][j])bk[i][j]=4;
            // if(bk[i][j])cout<<i<<" "<<j<<" "<<bk[i][j]<<"\n";
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(bk[i][j]==1||bk[i][j]==3){
        	int k=j+1;
        	while(k<=m){
        		if(bk[i][k]==2||bk[i][k]==4){
	            	// cout<<i<<" "<<j<<" "<<k<<" a\n";
	                rnk[id[{i,j,k}]=++idx1]={i,j,k};
	                for(int l=j;l<=k;l++)p1[i][l]=idx1;
	                break;
                }
        		if(!pr[i][k]&&!a[i][k])break;
        		k++;
            }
            j=k;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)if(bk[j][i]==1||bk[j][i]==2){
        	int k=j+1;
        	while(k<=n){
        		if(bk[k][i]==3||bk[k][i]==4){
	            	// cout<<i<<" "<<j<<" "<<k<<" b\n";
	                rnk[id[{i,j,k}]=idx1+(++idx2)]={i,j,k};
	                for(int l=j;l<=k;l++)p2[l][i]=idx1+idx2;
	                j=k;
	                break;
	            }
        		if(!pd[k][i]&&!a[k][i])break;
        		k++;
        	}
            j=k;
        }
    }
    s=idx1+idx2+1,t=idx1+idx2+2;
    // cout<<idx1<<" "<<idx2<<" "<<s<<" "<<t<<"\n";
    for(int i=1;i<=idx1;i++)add(s,i,1);
    for(int i=1;i<=idx2;i++)add(i+idx1,t,1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(p1[i][j]&&p2[i][j]){
        	// cout<<p1[i][j]<<" "<<p2[i][j]<<"\n";
            add(p1[i][j],p2[i][j],1);
        }
    }
    while(bfs())flow+=dfs(s,inf);
    // cout<<flow<<"\n";
    dfs(s);
    // for(int i=1;i<=t;i++)cout<<vis[i]<<" ";cout<<"\n";
    int num=0;
    for(int i=1;i<=idx1;i++)if(vis[i]){
    	++num;
        auto[p,l,r]=rnk[i];
    	// cout<<i<<" "<<p<<" "<<l<<" "<<r<<" a\n";
        for(int j=l;j<r;j++)pr[p][j]=pl[p][j+1]=1;
        bk[p][l]=bk[p][r]=0;
    }
    for(int i=idx1+1;i<=idx1+idx2;i++)if(!vis[i]){
    	++num;
        auto[p,l,r]=rnk[i];
    	// cout<<i<<" "<<p<<" "<<l<<" "<<r<<" b\n";
        for(int j=l;j<r;j++)pd[j][p]=pu[j+1][p]=1;
        bk[l][p]=bk[r][p]=0;
    }
    // cout<<idx1+idx2-flow<<" "<<num<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(bk[i][j]){
        	// cout<<i<<" "<<j<<" "<<bk[i][j]<<"\n";
            if(bk[i][j]&1){
                for(int k=j;!(pd[i][k]&&pu[i][k])&&k<=m;k++)pr[i][k]=pl[i][k+1]=1;
            }
            else{
                for(int k=j;!(pd[i][k]&&pu[i][k])&&k;k--)pl[i][k]=pr[i][k-1]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(a[i][j]&&!ans[i][j])++res,col(i,j);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++)printf("%d ",ans[i][j]);puts("");
    }
    // for(int i=1;i<n;i++){
        // for(int j=1;j<m;j++)cout<<setw(3)<<ans[i][j];cout<<"\n";
    // }
}
```

---

