# Bricks

## 题目描述

A brick is defined as a rectangle with integer side lengths with either width $ 1 $ or height $ 1 $ (or both).

There is an $ n\times m $ grid, and each cell is colored either black or white. A tiling is a way to place bricks onto the grid such that each black cell is covered by exactly one brick, and each white cell is not covered by any brick. In other words, bricks are placed on black cells only, cover all black cells, and no two bricks overlap.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404E/050636f71672896c95a76cd68bdb315cb0256b57.png) An example tiling of the first test case using $ 5 $ bricks. It is possible to do better, using only $ 4 $ bricks. What is the minimum number of bricks required to make a valid tiling?

## 说明/提示

The first test case can be tiled with $ 4 $ bricks placed vertically.

The third test case can be tiled with $ 18 $ bricks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1404E/e4a048c75957e1b968fc17253d618d87f8f324f8.png)

## 样例 #1

### 输入

```
3 4
#.##
####
##..```

### 输出

```
4```

## 样例 #2

### 输入

```
6 6
######
##....
######
##...#
##...#
######```

### 输出

```
6```

## 样例 #3

### 输入

```
10 8
####..##
#..#.##.
#..#.###
####.#.#
....####
.###.###
###.#..#
########
###..###
.##.###.```

### 输出

```
18```

# 题解

## 作者：wgyhm (赞：17)

# CF1404E Bricks

第一眼，有点像 [[USACO05JAN]Muddy Fields G](https://www.luogu.com.cn/problem/P6062) ，考虑的CF基本上不会出原题。发现长方体不可以重叠。不妨先把样例给画出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/ch0jaf5e.png)

考虑**点边互换**。每条边表示是否能连接这两个点。**每选择一条边就减少了一个矩形**。也就是说，我们需要让选择的边最少。

![](https://cdn.luogu.com.cn/upload/image_hosting/3aobfeu7.png)

显然，同一个灰色点相邻的绿色和红色的边不能一起选。若是选了，则代表两块木板重叠，不合题意。

又要让选择的边最大化，考虑二分图，不能一起选的两边相连，跑一个二分图最大独立集即可。

答案就是 $ans=\text{总点数}-(\text{总边数}-\text{二分图最大匹配})$。

图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/5omypg40.png)

$Code:$

```cpp
#include<bits/stdc++.h>
#define maxn 605
#define rg register
#define ll long long
#define put() putchar('\n')
using namespace std;
...//快读
int now[maxn*maxn],h[maxn*maxn],deep[maxn*maxn],head,s,t,n,m;
int vis[maxn][maxn],v[maxn][maxn][5];
int fx[5]={0,1,-1,0,0};
int fy[5]={0,0,0,1,-1};
struct yyy{
    int to,z,w;
    inline void add(int x,int y,int W){
        to=y;z=h[x];h[x]=head;w=W;
    }
}a[maxn*maxn];
inline void ins(int x,int y,int w){
	a[++head].add(x,y,w);
	a[++head].add(y,x,0);
} 
...//默认你们都会二分图匹配
signed main(){
    rg int i,j,k,xx,yy,sum=0,tot=0;rg char ch;head=1;
    read(n);read(m);s=0;t=n*m*2+1;
    for (i=1;i<=n;i++){
    	ch=getchar();while (ch!='#'&&ch!='.') ch=getchar();
    	for (j=1;j<=m;j++) vis[i][j]=(ch=='#'),sum+=vis[i][j],ch=getchar();
	}
	for (i=1;i<=n;i++)
	    for (j=1;j<=m;j++){
	    	if (!vis[i][j]) continue;
			for (k=1;k<=4;k+=2){
	    		xx=i+fx[k];yy=j+fy[k];
	    		if (xx<1||xx>n||yy<1||yy>m||!vis[xx][yy]) continue;
	    		v[i][j][k]=v[xx][yy][k+1]=++tot;
			}
		}
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++){
        	for (k=1;k<=1;k++){
            	if (!v[i][j][k]) continue;
            	ins(s,v[i][j][k],1);
            	if (v[i][j][3]) ins(v[i][j][k],v[i][j][3],1);
            	if (v[i][j][4]) ins(v[i][j][k],v[i][j][4],1);
			}
			for (k=1;k<=1;k++){
            	if (!v[i][j][k]) continue;
            	xx=i+fx[k];yy=j+fy[k];
            	if (xx<1||xx>n||yy<1||yy>m||!vis[xx][yy]) continue;
            	if (v[xx][yy][3]) ins(v[i][j][k],v[xx][yy][3],1);
            	if (v[xx][yy][4]) ins(v[i][j][k],v[xx][yy][4],1);
			}
			if (v[i][j][3]) ins(v[i][j][3],t,1);
		}
    printf("%d",sum-(tot-Dinic()));
    return 0;
}
```

但是我的代码跑的贼慢，倒数第二优解，所以仅供参考。



---

## 作者：Rainy7 (赞：11)

- **前言**

  同步发布于[我的博客。](https://www.cnblogs.com/Rainy7/p/solution-CF1404E.html)
  
  这题和[P6062 [USACO05JAN]Muddy Fields G](https://www.luogu.com.cn/problem/P6062)非常相似，唯一不同的就是这题覆盖的位置**不能相互重叠**。
  
  学习了大佬[隐隐约约妖艳](https://www.luogu.com.cn/user/114530)的题解，自己做了一些补充。

------------

- **分析**

  类似的，根据**横/纵**来构造二分图。
  
  这题的突破点在砖块**不能互相重叠**，所以对于一个黑色格子，不能同时放 $2$ 块 $1 \times x (x>1)$ 的砖块。
  
  如图：
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/00ghx5z2.png)
  
  正因为如此，**放横的就不能放竖的，放竖的就不能放横的**。此时一个二分图就成形了。如下图：
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/etf2kb2o.png)
  
  建好图后，要求的结果就可以转换了，道理类似前言的那题，最后要求的是**最多选多少点，且这些点之间没有连边（保证结果最小）**。
  
  即独立集。
  
  由引理得出结果，**二分图的最大独立集 = 总点数-最大匹配数**。
  
  因为这题 $n,m \le 200$ ，直接跑二分图匹配复杂度似乎会到 $O(n^2m^2)$ 。所以本题用网络流跑。

------------

- **代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
const int Maxn=8e4+5;
const int inf=1e9;
struct edge{
	int v,nx,w;
}e[Maxn<<4];
int n,m,ne=-1,f[Maxn],deep[Maxn];
int cur[Maxn];
char str[205][205];
bool vis[Maxn];
queue<int> q;
void read(int u,int v,int w)
{	
	e[++ne].v=v;
	e[ne].nx=f[u];
	e[ne].w=w;
	f[u]=ne;
}
bool bfs(int s,int t)
{	
	memset(deep,0x7f,sizeof(deep));
	while(!q.empty())q.pop();
	for(int i=0;i<=t;i++)cur[i]=f[i];
	deep[s]=0;
	q.push(s);
	while(!q.empty())
	{	
		int now=q.front();
		q.pop();
		for(int i=f[now];i!=-1;i=e[i].nx)
			if(deep[e[i].v]>inf&&e[i].w)
			{	
				deep[e[i].v]=deep[now]+1;
				q.push(e[i].v);
			}
	}
	if(deep[t]<inf)return 1;
	return 0;
}
int dfs(int now,int t,int limit)
{	
	if(!limit||now==t)return limit;
	int flow=0,x;
	for(int i=cur[now];i!=-1;i=e[i].nx)
	{	
		cur[now]=i;
		if(deep[e[i].v]==deep[now]+1)
		{	
			x=dfs(e[i].v,t,min(limit,e[i].w));
			if(!x)continue;
			flow+=x;
			limit-=x;
			e[i].w-=x;
			e[i^1].w+=x;
			if(!limit)break;
		}
	}
	return flow;
}
int dinic(int s,int t)
{	
	int maxflow=0;
	while(bfs(s,t))maxflow+=dfs(s,t,inf);
	return maxflow;
}
int main()
{	
	int s,t,sum=0,cnt=0;
	memset(f,-1,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",str[i]+1);
	s=0,t=n*m*2+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{	
			if(str[i][j]=='.')continue;
			sum++;
			int uu=(i-1)*m+j,rr=uu+n*m;// uu:id(i,j) rr:id(i,j)_
			int vv=i*m+j,ll=rr-1;// vv:id(i+1,j) ll:id(i,j-1)_
			if(str[i-1][j]=='#'&&!vis[uu])++cnt,vis[uu]++,read(s,uu,1),read(uu,s,0);
			if(str[i][j-1]=='#'&&!vis[ll])++cnt,vis[ll]++,read(ll,t,1),read(t,ll,0);
			if(str[i-1][j]=='#')
			{	
				if(str[i][j+1]=='#')read(uu,rr,1),read(rr,uu,0);
				if(str[i][j-1]=='#')read(uu,ll,1),read(ll,uu,0);
			}
			if(str[i+1][j]=='#')
			{	
				if(str[i][j+1]=='#')read(vv,rr,1),read(rr,vv,0);
				if(str[i][j-1]=='#')read(vv,ll,1),read(ll,vv,0);
			}
		}
	printf("%d\n",sum-(cnt-dinic(s,t)));
	return 0;
}
```

------------

$$\text{by Rainy7}$$

---

## 作者：zac2010 (赞：5)

考虑每个 `#` 的位置使用一块木板，之后进行一些调整。

对于每次调整，我们合并两块木板，使得合并完后木板依旧合法。

这个合并的过程考虑使用二分图的最大独立集。

具体的，我们把相邻的两个 `#` 之间连边，把边看做新图上的点。对于新图上的点 $u1$（假设它在原图上的对应边为 $l1$），它在新图上会和一个点 $u2$ 连边当且仅当 $u2$ 在原图上对应的边与 $l1$ 有交点。会发现这样的限制组成了一张二分图——原图中上下相连的边只会与左右相连的边建边。跑二分图的最大独立集即可（$\text{二分图的最大独立集}=n-\text{最大匹配}$）。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int S = 210, N = 80010, M = 320010;
const ll INF = 1e18;
struct E{int v; ll w, nxt;} e[M << 1];
int n, m, s, t, cnt, tot, tote, head[N], now[N], dep[N], e1[S][S], e2[S][S];
char mp[S][S];
void Adde(int u, int v, ll w){
    e[tote] = {v, w, head[u]}, head[u] = tote++;
}
int bfs(){
    queue<int> q; q.push(s);
    memset(dep, 0, sizeof(dep)), dep[s] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = now[u] = head[u]; ~i; i = e[i].nxt)
            if(e[i].w && !dep[e[i].v])
				q.push(e[i].v), dep[e[i].v] = dep[u] + 1;
    }
    return dep[t];
}
ll dfs(int u, ll in){
    if(u == t) return in; ll out = 0;
    for(int i = now[u]; ~i && in; i = e[i].nxt){
        int v = e[i].v; ll w = e[i].w; now[u] = i;
        if(dep[v] == dep[u] + 1 && w){
            ll flow = dfs(v, min(in, (ll)w));
            in -= flow, out += flow;
            e[i].w -= flow, e[i ^ 1].w += flow;
        }
    }
    if(!out) dep[u] = 0; return out;
}
ll dinic(){
    ll ret = 0;
    while(bfs()) ret += dfs(s, INF);
    return ret;
}
int main(){
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), s = ++tot, t = ++tot;
	FL(i, 1, n) FL(j, 1, m){
		scanf(" %c", &mp[i][j]), cnt += mp[i][j] == '#';
		if(mp[i][j] == '#' && mp[i - 1][j] == '#')
			Adde(s, e1[i][j] = ++tot, 1), Adde(e1[i][j], s, 0);
		if(mp[i][j] == '#' && mp[i][j - 1] == '#')
			Adde(e2[i][j] = ++tot, t, 1), Adde(t, e2[i][j], 0);
	}
	FL(i, 1, n) FL(j, 1, m){
		if(mp[i - 1][j] == '#' && mp[i][j - 1] == '#')
			Adde(e1[i][j], e2[i][j], 1), Adde(e2[i][j], e1[i][j], 0);
		if(mp[i - 1][j] == '#' && mp[i][j + 1] == '#')
			Adde(e1[i][j], e2[i][j + 1], 1), Adde(e2[i][j + 1], e1[i][j], 0);
		if(mp[i + 1][j] == '#' && mp[i][j - 1] == '#')
			Adde(e1[i + 1][j], e2[i][j], 1), Adde(e2[i][j], e1[i + 1][j], 0);
		if(mp[i + 1][j] == '#' && mp[i][j + 1] == '#')
			Adde(e1[i + 1][j], e2[i][j + 1], 1), Adde(e2[i][j + 1], e1[i + 1][j], 0);
	}
	printf("%lld\n", cnt - (tot - 2 - dinic()));
    return 0;
}
```


---

## 作者：cinccout (赞：4)

## 前言

~~第一次写题解的说~~

看别的大佬都用最大独立集写的，这里提供一个最小割做法。



------------


## 分析

可以注意到的一点是如果有一段方格可用一个长方形去覆盖，则绝对不会截成两个。所以，一种铺长方形的方法可以**一一对应**成一种**将每个格子染色**的方案，即将每个点染成"平"和"直"两种颜色，表示它所在的长方形是平行于底边放置还是垂直于底边放置。

如样例即可看为：

```
直空直直
直平平直
直平空空
```
那么，答案的贡献即长方形端点有两种情况：

- 一个直的格子上下超出区域或需要涂白

- 一个直的格子上下存在平的格子

平的格子类似，每出现两次即对答案有 $1$ 的贡献。

那么，染色只有两种，第一种情况属于染色本身贡献，第二种情况属于两个染色不同产生额外贡献，就是一个最小割模型。对于每一个格子建一个点即可，复杂度好像不太对，但网络流+跑不满能过。

## 代码

```cpp
#include<bits/stdc++.h>
#define inf 2147483647
using namespace std;
struct qxx
{
	int to,next,len;
}a[2000005];
int head[100005],cnt,s,t;
void add(int aa,int bb,int cc)
{
	a[++cnt].to=bb;a[cnt].len=cc;
	a[cnt].next=head[aa];head[aa]=cnt;
	a[++cnt].to=aa;a[cnt].len=0;
	a[cnt].next=head[bb];head[bb]=cnt;
}
int h[100005],d[100005];
bool bfs()
{
	memset(d,0,sizeof(d));
	queue<int> q;
	q.push(s);d[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		h[u]=head[u];
		for(int i=head[u];i!=-1;i=a[i].next)
		{
			int v=a[i].to;
			if(d[v]||!a[i].len) continue;
			d[v]=d[u]+1;
			q.push(v);
		}
	}
	if(d[t]) return 1;
	else return 0;
}
int dfs(int u,int la)
{
	if(u==t) return la;
	int now=0;
	for(int i=h[u];i!=-1&&now<la;i=a[i].next)
	{
		int v=a[i].to;
		if(d[v]!=d[u]+1||!a[i].len) continue;
		int val=dfs(v,min(a[i].len,la-now));
		if(!val) d[v]=0;
		now+=val;
		a[i].len-=val;a[i^1].len+=val;
		h[u]=i;
	}
	//if(now==0) d[u]=0;
	return now;
}
int n,m,c[205][205],ans=0;
int idd[205][205],now;
char sss[305];
int id(int xx,int yy)
{
    if(!idd[xx][yy]) idd[xx][yy]=++now;
    return idd[xx][yy];
}
bool check(int xx,int yy){return xx>=1&&xx<=n&&yy>=1&&yy<=m&&(c[xx][yy]==0);}
signed main()
{
	memset(head,-1,sizeof(head));cnt=-1;
	cin>>n>>m;
	s=++now;t=++now;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",sss+1);
		for(int j=1;j<=m;j++)
		{
			if(sss[j]=='#') c[i][j]=0;
			else c[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++) c[i][0]=c[i][m+1]=1;
	for(int i=1;i<=m;i++) c[0][i]=c[n+1][i]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]==1) continue;
			add(s,id(i,j),c[i][j-1]+c[i][j+1]);		//第一种情况的贡献 
			add(id(i,j),t,c[i-1][j]+c[i+1][j]);
			if(check(i,j-1)) add(id(i,j-1),id(i,j),1);		//第二种情况的贡献 
			if(check(i,j+1)) add(id(i,j+1),id(i,j),1);
			if(check(i-1,j)) add(id(i,j),id(i-1,j),1);
			if(check(i+1,j)) add(id(i,j),id(i+1,j),1);
		}
	}
	while(bfs()) ans+=dfs(s,INT_MAX);
	cout<<ans/2;		//两个端点只有一个贡献 
	return 0;
}
```

---

## 作者：隐隐约约妖艳 (赞：4)

~~这题没题解我就来一发吧~~
# 二分图
注意到本题如果使用了一个 x>1 砖块就可以视作擦除了一条边界，同一个格子垂直的边界不能同时被擦除。就可以把本题转化为**二分图**。  
### 建图：
把边界视作二分图的点，横着的边界为左部点，竖着的边界为右部点。若一个 '#' 相邻的 '#' 有两个在竖直方向（即一个在左/右另一个在上/下）就把这两个对应的边界对应在二分图上的点连起来。  
### 问题转化为：
求选最多的点且这些点不能相连，即为**最大独立集问题**。

------------
代码如下：（建图过程建议自己想一下）
```cpp
#include<bits/stdc++.h>
#define N 80004
using namespace std;
int n,m;
//以下为网络流求最大匹配板子
int fi[N],ne[N<<4],to[N<<4],c[N<<4],num=1;
void add(int x,int y,int z)
{
	ne[++num]=fi[x];fi[x]=num;to[num]=y;c[num]=z;
	ne[++num]=fi[y];fi[y]=num;to[num]=x;c[num]=0;
}
int dep[N],q[N],l,r,s,t,ans;
int cur[N];
bool bfs()
{
	l=1;r=0;
	q[++r]=s;
	for(int i=0;i<=t;i++) dep[i]=0,cur[i]=fi[i];
	dep[s]=1;
	while(l<=r)
	{
		int k=q[l++];
		for(int i=fi[k];i;i=ne[i])
			if(c[i]&&!dep[to[i]])
			{
				dep[to[i]]=dep[k]+1;
				q[++r]=to[i];
			}
	}
	return dep[t]!=0;
}
int dfs(int k,int fl)
{
	if(k==t)
	{
		ans+=fl;
		return fl;
	}
	int us=0,fx;
	for(int i=cur[k];i;i=ne[i])
	{
		cur[k]=i;
		if(dep[to[i]]==dep[k]+1&&c[i])
		{
			if(fx=dfs(to[i],min(fl-us,c[i])))
			{
				us+=fx;
				c[i]-=fx;
				c[i^1]+=fx;
				if(us==fl)break;
			}
		}
	}
	return us;
}
void dinic()
{
	while(bfs())
		dfs(s,0x3f3f3f3f);
}
//以上为网络流求最大匹配板子
int sum,cnt,v[N];
char ss[202][202];
int main()
{
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
	scanf("%s",ss[i]+1);
//建图如下
s=0;t=n*m*2+1;
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(ss[i][j]=='#')
	{
		sum++;
		int uu=(i-1)*m+j,rr=uu+n*m,dd=i*m+j,ll=rr-1;//上下左右边界的编号
        //注意cnt
		if(ss[i-1][j]=='#'&&!v[uu]) ++cnt,v[uu]=1,add(s,uu,1);
		if(ss[i][j-1]=='#'&&!v[ll]) ++cnt,v[ll]=1,add(ll,t,1);
		if(ss[i-1][j]=='#')
		{
			if(ss[i][j+1]=='#')
				add(uu,rr,1);
			if(ss[i][j-1]=='#')
				add(uu,ll,1);
		}
		if(ss[i+1][j]=='#')
		{
			if(ss[i][j+1]=='#')
				add(dd,rr,1);
			if(ss[i][j-1]=='#')
				add(dd,ll,1);
		}
	}
dinic();
printf("%d",sum-(cnt-ans));

return 0;
}
```


---

## 作者：jianhe (赞：3)

### 前言：
以为是 [P6062 [USACO05JAN] Muddy Fields G](https://www.luogu.com.cn/problem/P6062)，直接把代码复制过来交上去了，甚至过掉了题面里的三个样例。
### 思路：
发现两个题唯一的区别在于 **本题的长方形不能重叠**。

于是考虑将本题的边看作新图上的点。

为了保证不重叠，选的这些边需要满足竖着的和横着的相邻边不能一起选。

因此跑一个二分图匹配，由 **二分图最大独立集=总点数-最大匹配数** 得到答案。
### 代码：
```cpp
/*
 * @Author: jianhe
 * @Date: 2025-01-19 08:21:48
 * @LastEditTime: 2025-01-19 09:14:01
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N=222,M=N*N*2;
ll n,m,ans,ct,black,bian,match[M],h[N][N],l[N][N];
string s[N];bitset<M> vis;vector<ll> e[M];
bool dfs(ll x){// 匈牙利板子优化
    for(auto y:e[x])
        if(!vis[y]&&!match[y]){vis[y]=1;match[y]=x;return 1;}
    for(auto y:e[x])
        if(!vis[y]){
            vis[y]=1;
            if(dfs(match[y])){match[y]=x;return 1;}
        }
    return 0;
}
void add(ll x,ll y){e[x].pb(y);}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='#'){
                black++;
                if(i<n&&s[i+1][j]=='#') l[i][j]=++ct;// 竖边
                if(j<m&&s[i][j+1]=='#') h[i][j]=++ct;// 横边
            }       
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='#'){
                if(s[i-1][j]=='#'){
                    if(s[i][j-1]=='#') add(l[i-1][j],h[i][j-1]);
                    if(s[i][j+1]=='#') add(l[i-1][j],h[i][j]);
                }
                if(s[i+1][j]=='#'){
                    if(s[i][j-1]=='#') add(l[i][j],h[i][j-1]);
                    if(s[i][j+1]=='#') add(l[i][j],h[i][j]);
                }
            }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='#'&&s[i+1][j]=='#') vis=0,ans+=dfs(l[i][j]);
    cout<<black-(ct-ans);
    return 0;
}
```

---

## 作者：JustPureH2O (赞：3)

[更好的阅读体验](https://justpureh2o.cn/articles/35098)

题目地址：[CF1404E - Bricks](https://www.luogu.com.cn/problem/CF1404E)

初做这道题时，我发现它和 [P6062 - Muddy Fields G](https://www.luogu.com.cn/problem/P6062) 神似。于是冲动交了一发，吃了 WA。仔细审题发现，这道题要求所用**木板不能重叠**。因此寻找其他的解题方法。

现在我们的当务之急是找出一个处理木板重叠的好方法，从黑色格子的分布入手——木板重叠放置的唯一可能就是当前黑色方格位于一个交叉的位置，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dflbgdef.png)


位于交点上的黑色方格可能被同时划分到橙色和蓝色的木板里去，这是题目不允许的，但这也启发我们在位于交点位置上的黑色方格做特定的操作。也就是说，当确定选择使用蓝色木板覆盖后，橙色木板就不能再覆盖交点位置。考虑把原图改换成如下形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/gar81kek.png)

当选择 $3$ 号点后（蓝色木板），$2$ 号就不能再选。何不考虑在“仇家”之间连边？也就是连接边 $(2,3)$，对于整张图，按此方法全部连边。题目要求我们覆盖住所有的黑色方格，并且还不能同时选择一条边上的两个端点（因为它们是敌人）。此时突然想到，这是二分图的最大点独立集问题。

在一张二分图中，选出若干点组成一个点集，使得点集里任意两点都不互通。原图中满足以上要求且所含点最多的集合叫做原二分图的最大点独立集。感性理解一下：我们需要选出尽量少的点丢弃，使得剩下的点不互通，考虑到最小点覆盖的定义，把属于最小点覆盖集的所有点从图中去掉，此时图上的每条边均只剩一个端点，满足定义，于是最大点独立集的大小就等于总点数减去最小点覆盖集的大小（根据 $\texttt{K\"onig}$ 定理，又有最小点覆盖集的大小等于二分图最大匹配数），推导出它等价于求：**总点数减去最大匹配数**。

不妨设所有新加的边组成一个新图 $G$，换到这道题上来，就是：

> 黑色方格总数减去黑色方格间的总边数再加上 $G$ 的最大匹配数

此后，把原图中的边当作一个点进行编号，并统计黑色方格数；然后统计所有位于交叉位置的黑色方格，并根据上述的连接方式连边，顺带统计黑色方格间的边数；最后在新图上做最大匹配，根据公式计算出结果即可。我为边编号的方式较为繁琐，理解思路后自行编号计算即可。

```cpp
#include <bits/stdc++.h>
#define N 210     // 题目所给最大长宽
#define M 1000010
#define K 80000   // 化边为点后最多 n(m-1)+m(n-1) 个点，极限情况下等于79600
using namespace std;

struct Edge {
    int to, ne;
} edges[M];
int h[N * N], idx = 0; // 方阵中最多 n^2 个点
char land[N][N];       // 暂存原图
int id[N][N];          // 按顺序给点编号
int match[K];          // 新图最多 K 个点
bool st[K], vis[N * N][4]; // vis 用作搜索判重，记录当前点是从哪个方向扩展而来的
int edge = 0, point = 0;
int n, m;

void add(int a, int b) {
    idx++;
    edges[idx].to = b;
    edges[idx].ne = h[a];
    h[a] = idx;
}

bool hungary(int u) {
    // 匈牙利算法，二分图最大匹配
    for (int i = h[u]; ~i; i = edges[i].ne) {
        int j = edges[i].to;
        if (!st[j]) {
            st[j] = true;
            if (!match[j] || hungary(match[j])) {
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, -1, sizeof h);

    cin >> n >> m;
    int tmp = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> land[i][j];
            id[i][j] = ++tmp;
            if (land[i][j] == '#') point++; // 统计黑色方格个数
        }
    }
    // 写得稀烂，建议理解后自己写一个
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (land[i][j] == '#') {
                if (land[i - 1][j] == '#' && land[i][j - 1] == '#') {
                    add(id[i][j] - i, n * (m - 1) + (i - 2) * m + j);
                }
                if (land[i - 1][j] == '#' && land[i][j + 1] == '#') {
                    add(id[i][j] - i + 1, n * (m - 1) + (i - 2) * m + j);
                }
                if (land[i + 1][j] == '#' && land[i][j + 1] == '#') {
                    add(id[i][j] - i + 1, n * (m - 1) + (i - 1) * m + j);
                }
                if (land[i + 1][j] == '#' && land[i][j - 1] == '#') {
                    add(id[i][j] - i, n * (m - 1) + (i - 1) * m + j);
                }
            }
        }
    }
    // 搜索统计边数
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (land[i][j] == '#') {
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
                    if (land[nx][ny] != '#') continue;
                    if (vis[id[i][j]][k]) continue;
                    vis[id[i][j]][k] = true;
                    edge++;
                }
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n * (m - 1); i++) {
        memset(st, false, sizeof st);
        if (hungary(i)) res++;
    }
    // 由于搜索统计时重复扫了两遍，因此边数需要折半
    cout << point - edge / 2 + res << endl;
    return 0;
}
```

~~然后 in queue 一晚上。~~

$\texttt{The~End}$

---

## 作者：lupengheyyds (赞：2)

## 题面

有一个 $n×m$ 网格，每个单元格要么是黑色要么是白色。用长或宽为一的矩形覆盖所有黑色单元格，并且没有两块砖重叠。

$1\le n,m\le 200$

## 解法

有一个朴素的思路是将各种可能的砖头都建一个点，接着建图跑最大流，但这样会建立 $\mathcal O(n^2m+nm^2)$ 个点，跑最大流会超时。

我们可以关心相邻的位置，查看相邻的位置能否由一个砖块覆盖，这样做的意义在于，就算是有一个很长的砖块，也一定因为两个子部分内部可以合并，加上这两个子部分可以合并为一个。容易发现，合并两个位置就会将答案减一，那么我们应该让选择的合并尽量的多。但有一个限制是，一个点不能在上下合并的同时左右合并。

那么可以将上下左右的限制连无向边，最后成为一个二分图，那么答案就为 $总黑点数-二分图最大独立集$

## 方法

- 无向关系

- 由单元及整体的思想
  
  小的合并成大的

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=80005,MM=205,INF=0x3f3f3f3f;
struct Node{
	int to,val,fan;
};
vector<Node> ed[NN];
int n,m,s,t;
int maxflow;
queue<int> q;
int dep[NN],gap[NN],now[NN];
char ch[MM][MM];
void BFS(){
	q.push(t);dep[t]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		gap[dep[x]]++;
		for(Node eg:ed[x]){
			int y=eg.to;
			if(dep[y]||eg.val)continue;
			dep[y]=dep[x]+1;
			q.push(y);
		}
	}
	return;
}
int Dinic(int x,int flow){
	if(x==t)return flow;
	int rest=flow;
	for(int &i=now[x];i<ed[x].size();i++){
		int y=ed[x][i].to;
		if(!ed[x][i].val||dep[y]+1!=dep[x])continue;
		int k=Dinic(y,min(ed[x][i].val,rest));
		ed[x][i].val-=k;
		ed[y][ed[x][i].fan].val+=k;
		rest-=k;
		if(!rest)return flow;
	}
	if(!--gap[dep[x]])dep[s]=t+1;
	gap[++dep[x]]++;now[x]--;
	return flow-rest;
}
inline void Add(int u,int v,int w){
	ed[u].push_back({v,w,ed[v].size()});
	ed[v].push_back({u,0,ed[u].size()-1});
	return;
}
inline int A(int i,int j){
	return (i-1)*m+j;
}
inline int Up(int i,int j){
	if(ch[i][j]!='#'||ch[i-1][j]!='#')return 0;
	return A(i,j);
}
inline int Down(int i,int j){
	if(ch[i][j]!='#'||ch[i+1][j]!='#')return 0;
	return A(i+1,j);
}
inline int Left(int i,int j){
	if(ch[i][j]!='#'||ch[i][j-1]!='#')return 0;
	return A(n,m)+A(i,j);
}
inline int Right(int i,int j){
	if(ch[i][j]!='#'||ch[i][j+1]!='#')return 0;
	return A(n,m)+A(i,j+1);
}
int cnt=0,tot=0;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>ch[i][j];
	s=n*m*2+1,t=s+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='#')tot++;
			if(Up(i,j))Add(s,Up(i,j),1),cnt++;
			if(Left(i,j))Add(Left(i,j),t,1),cnt++;
			if(Up(i,j)&&Right(i,j))Add(Up(i,j),Right(i,j),1);
			if(Up(i,j)&&Left(i,j))Add(Up(i,j),Left(i,j),1);
			if(Down(i,j)&&Right(i,j))Add(Down(i,j),Right(i,j),1);
			if(Down(i,j)&&Left(i,j))Add(Down(i,j),Left(i,j),1);
		}
	}
	BFS();
	while(dep[s]<=t){
		memset(now,0,sizeof now);
		maxflow+=Dinic(s,INF);
	}
	cout<<tot-(cnt-maxflow);
	return 0;
}
```

---

## 作者：XiaoQuQu (赞：1)

发一篇比较适合萌新的题解，讲讲为什么能想到网络流求二分图最大独立集。

观察一下，发现对于一个位置的覆盖，我们会有三种情况：

1. 当前这一块属于一个竖着 $1\times k$ 的方块中的一部分，这时候显然我们将会直接把他覆盖（下图第一种情况）；
2. 当前这一块属于一个竖着 $k\times 1$ 的方块中的一部分，这时候显然我们将会直接把他覆盖（下图第二种情况）；
3. 当前这一块处于两个的交界部分（下图第三种情况）。

![image.png](https://s2.loli.net/2023/08/13/VeJ1fM4CmcG9kid.png)

对于前两种情况我们很好处理，我们现在要解决的是第三种情况。

由于方块不可以重叠，我们发现可以很自然的用图论中的最大独立集来表示这个问题，考虑建图，将每个 $1\times 2$ 或 $2\times 1$ 的方块看成点，对于一个位于交界处的方块，我们直接在交界的两个点之间连一条边，然后对于这个图，跑一个最大的独立集，最终答案就是总黑色点数减去这个最大的独立集。

这里只放一个建图的代码，完整代码可以 [在这里](http://119.6.50.219:10375/r?cid=691f2293-9ee3-49bf-9148-374c27a8b5ef) 找到。

```cpp
namespace build_graph {
	const int MAXN = 5e2 + 5;
	int n, m, tot = 0, cnt; char s[MAXN][MAXN];
	bool vis[MAXN * MAXN];
	void build_graph() {
		cin >> n >> m;
		dinic::s = n * m * 2 + 1; dinic::t = dinic::s + 1; dinic::n = dinic::t;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) 
				cin >> s[i][j]; // c++20 forbids using "cin >> (s[i] + 1);"
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (s[i][j] == '.') continue;
				++tot;
				int hid = (i - 1) * m + j, sid = n * m + hid;
				int down = i * m + j, left = sid - 1;
				if (s[i - 1][j] == '#' && !vis[hid]) cnt += (vis[hid] = true), dinic::add(dinic::s, hid, 1);
				if (s[i][j - 1] == '#' && !vis[left]) cnt += (vis[left] = true), dinic::add(left, dinic::t, 1);
				if (s[i - 1][j] == '#' && s[i][j + 1] == '#') dinic::add(hid, sid, 0x7f7f7f7f);
				if (s[i - 1][j] == '#' && s[i][j - 1] == '#') dinic::add(hid, left, 0x7f7f7f7f);
				if (s[i + 1][j] == '#' && s[i][j - 1] == '#') dinic::add(down, left, 0x7f7f7f7f);
				if (s[i + 1][j] == '#' && s[i][j + 1] == '#') dinic::add(down, sid, 0x7f7f7f7f);
			}
		}
		cout << tot - cnt + dinic::maxflow() << endl;
	}
}
```



---

## 作者：EXODUS (赞：1)

# Part 1：前言
网络流好题。

# Part 2：正文

我们首先考虑覆盖矩形的本质，其实相当于选一些边界删掉，使得删掉后剩下的所有连通块均为长或宽为一的矩形。

更进一步的考虑，这相当于每个点的上下边界和左右边界不能同时删掉，只能任选一组或不选，容易发现将删除限制看成边的话构成了一个二分图，两边点集分别为上下和左右边界所代表的点集。

最小割的感觉就来了。这是一个经典问题，将每个点的边界视为一个点，每次删掉一个点都会让答案减一，有若干个限制，分别为两个点不能同时删掉，且我们知道这些删除限制构成了一个二分图，那么直接由源点向上下边界代表的点集连边，左右边界向汇点代表的点集建边，此时的最小割即为保留的点数。最多删去的边界数即为总边界数减去最小割数。

注意这个答案并不是最终答案，而是最多减少的矩形数，所以最后要拿黑色格子数减去上面的答案。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

const int N=4e2+7,M=4e5+7;
struct Dinic{
	struct edge{int to,nxt,dis;}e[M<<1];
	int head[N*N],cur[N*N],dis[N*N],cnt,s,t;
	Dinic(){memset(head,-1,sizeof(head));}
	void add_edge(int u,int v,int w){
		e[cnt].to=v;e[cnt].dis=w,e[cnt].nxt=head[u],head[u]=cnt++;
		e[cnt].to=u;e[cnt].dis=0,e[cnt].nxt=head[v],head[v]=cnt++;
	}
	bool bfs(){
		memset(dis,-1,sizeof(dis));dis[s]=0;
		queue<int>q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u],v;~i;i=e[i].nxt)
				if(!(~dis[v=e[i].to])&&e[i].dis)dis[v]=dis[u]+1,q.push(v);
		}return dis[t]!=-1;
	}
	int dfs(int u,int flow){
		if(u==t)return flow;
		int delta=flow;
		for(int i=cur[u],v;~i;i=e[i].nxt){
			cur[u]=e[i].nxt;v=e[i].to;
			if(dis[v]==dis[u]+1&&e[i].dis>0){
				int f=dfs(v,min(e[i].dis,delta));
				if(!f){dis[v]=-1;continue;}
				e[i].dis-=f,e[i^1].dis+=f,delta-=f;
				if(!delta)break;
			}
		}return flow-delta;
	}
	int dinic(){
		int ans=0;
		while(bfs()){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(s,1e9);
		}return ans;
	}
}G;


int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int n,m,siz;
char s[N][N];
int idx[N][N][4];

int main(){
	read(n,m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	// for(int i=1;i<=n;i++)printf("%s\n",s[i]+1);
	auto check=[&](int i,int j,int d){return s[i+dx[d]][j+dy[d]]=='#'&&s[i][j]=='#';};
	for(int i=1;i<n;i++)for(int j=1;j<=m;j++)if(check(i,j,0))idx[i][j][0]=idx[i+dx[0]][j+dy[0]][1]=++siz;
	// for(int i=1;i<=n;i++)for(int j=2;j<=m;j++)if(check(i,j,1))idx[i][j][1]=idx[i+dx[1]][j+dx[1]][0]=++siz;
	for(int i=1;i<=n;i++)for(int j=1;j<m;j++)if(check(i,j,2))idx[i][j][2]=idx[i+dx[2]][j+dy[2]][3]=++siz;
	// for(int i=2;i<=n;i++)for(int j=1;j<=m;j++)if(check(i,j,3))idx[i][j][3]=idx[i+dx[3]][j+dx[3]][2]=++siz;
	// cout<<siz<<endl;
	// for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)printf("%d %d %d %d\n",idx[i][j][0],idx[i][j][1],idx[i][j][2],idx[i][j][3]); 
	G.s=0,G.t=siz+1;
	int ans=-siz;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		ans+=(s[i][j]!='.');
		if(idx[i][j][0])G.add_edge(G.s,idx[i][j][0],1);
		if(idx[i][j][2])G.add_edge(idx[i][j][2],G.t,1);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		for(int k=0;k<=1;k++)for(int l=2;l<=3;l++)
			if(idx[i][j][k]&&idx[i][j][l])G.add_edge(idx[i][j][k],idx[i][j][l],1e9);
	printf("%d\n",ans+G.dinic());
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：1)

明显的二分图题。

首先将每条边编上号，这里为了方便，直接将横边多补了一条。

对于一个格子 $(i,j)$，若它为黑色，则分以下四种情况（这里用 $id(x_1,y_1,x_2,y_2)$ 表示从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 之间边的编号，保证两个格子一定相邻）：

1. 上面和右边同为黑，连边 $(id(i-1,j,i,j),id(i,j,i,j+1))$
2. 上面和左边同为黑，连边 $(id(i-1,j,i,j),id(i,j-1,i,j))$
3. 下面和右边同为黑，连边 $(id(i,j,i+1,j),id(i,j,i,j+1))$
4. 下面和左边同为黑，连边 $(id(i,j,i+1,j),id(i,j-1,i,j))$

这里一定要从竖着的边向横着的边连，因为需要保证二分图的左半边点。

连完边之后，考虑对于一个点，要么是被竖板子覆盖，要么是被横板子覆盖，所以对于二分图中的一条边，两个端点只能选一个，就是最大独立集

接下来就是二分图的最大独立集板子。

$\text{二分图最大独立集=总点数- (总边数-二分图最大匹配)}$

代码实现：

```cpp
#include<bits/stdc++.h>
#define y1 YOUAKIOI
using namespace std;
const int MAXN=1e6+5;
const int MAXM=205;
struct node
{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;
inline void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
bitset<MAXN>vis;
int mat[MAXN];
inline bool match(int x)
{
	for(register int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(!vis[y])
		{
			vis[y]=1;
			if(!mat[y]||match(mat[y]))
			{
				mat[y]=x;
				return true;
			}
		}
	}
	return false;
}
int n,m;
char ma[MAXM][MAXM];
inline int id(int x1,int y1,int x2,int y2)
{
	if(abs(x1-x2)==1)return x1*2*m+y1-m;
	if(abs(y1-y2)==1)return (x1-1)*2*m+y1;
}
int main()
{
	memset(ma,'!',sizeof(ma));
	scanf("%d%d",&n,&m);
	int sum=0;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
		{
			cin>>ma[i][j];
			if(ma[i][j]=='#')sum++;
		}
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
		{
			if(ma[i][j]=='#'&&ma[i-1][j]=='#'&&ma[i][j-1]=='#')add(id(i-1,j,i,j),id(i,j-1,i,j));
			if(ma[i][j]=='#'&&ma[i-1][j]=='#'&&ma[i][j+1]=='#')add(id(i-1,j,i,j),id(i,j,i,j+1));
			if(ma[i][j]=='#'&&ma[i+1][j]=='#'&&ma[i][j-1]=='#')add(id(i,j,i+1,j),id(i,j-1,i,j));
			if(ma[i][j]=='#'&&ma[i+1][j]=='#'&&ma[i][j+1]=='#')add(id(i,j,i+1,j),id(i,j,i,j+1));
		}
	int ans=0;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
			if(ma[i][j]=='#'&&ma[i+1][j]=='#')
			{
				vis=0;
				if(match(id(i,j,i+1,j)))ans++;
			}
	int tot=0;
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=m;j++)
		{
			if(ma[i][j]=='#'&&ma[i+1][j]=='#')tot++;
			if(ma[i][j]=='#'&&ma[i][j+1]=='#')tot++;
		}
	printf("%d",sum-tot+ans);
	return 0;
}
```

---

## 作者：Rain_chr (赞：0)

相当困难的网络流题，但是竟然只有 2800

**最小 DAG 链覆盖+最大权闭合子图**

我首先往行列匹配方面去想，但是这题因为块之间不能重叠不好表示成行列匹配的形式。

发散想了很久，突然想到 DAG 最小链覆盖问题，但是这样会使得块能够拐弯，这显然的不对的。

等等，DAG 最小链覆盖问题？我怎么有点忘记了？

于是自己推了一推，一直在考虑用一条增广路来代表一条链，结果发现这样错完了。

重新学了一下最小链覆盖是怎么做的，把每个点拆成入点和出点，不从宏观上考虑链是怎么覆盖的，只对于每一个点考虑用哪一个点来接它，或者说考虑与哪一个点合并。最小链覆盖，就是总点数减去最多能够合并的次数。

所以这样没办法限制不能拐弯，因为只考虑当前点和上一个点的连接状态。

但是最小 DAG 链覆盖的做法还是非常值得借鉴的，考虑如何限制不能拐弯，这个其实只需要类似这样限制就可以了：

1. 如果当前点与左侧的点合并，那么左侧的点也需要和左侧的点合并
2. 如果当前点与右侧的点合并，那么右侧的点也需要和右侧的点合并

如果把“与左侧合并”和“与右侧合并”都视作状态，那么很容易发现这就是一个最小割模型：

“与左侧合并”对应与源点相连，“与右侧合并”对应与汇点相连，并且有若干二元组 $(x,y)$ 表示如果 $x,y$ 选择的状态一样，那么就可以产生 -1 的贡献（因为 $x,y$ 可以合并了）

把权值反转，这就是一个最大权闭合子图问题，直接求最小割即可。

此时我们知道了最多能够合并的次数，那么需要的砖块数量就是总点数减去最大合并次数了。

---

## 作者：ty_mxzhn (赞：0)

网络流好题。

考虑按照边考虑。把每一个网格边作为一个点。

我们选一个点，代表擦除掉这条边。现在的问题是什么点不能同时选。

发现一个格子内部的横向边不能和竖向边同时选。建出边后要求这个图的最大独立集。

这个图显然是二分图。由经典的 Konig 定理得到二分图最大匹配和最小点覆盖集相等，最小点覆盖集又等于总点数减去最大独立集。

所以我们只需要求这个图的最大匹配。因为 $n,m$ 同阶，使用 Dinic 算法可以在 $O(n^3)$ 时间复杂度内解决这个问题。

实际上因为图特殊，这个算法还会跑的更快。

---

