# Game

## 题目背景

Justin摆弄着他的棋盘和棋...突然，他想到了一个非常好玩的游戏。

## 题目描述

棋盘可以看做是一个$N \times M$的网格，~~由于Justin太健壮了，~~所以他把$T$个格子弄坏了。也就是说，上面没法放棋子。

Justin想到的游戏是这样的：一开始，你可以选择棋盘的第一列的一些没有坏的格子，在上面各放上一枚棋子。然后，你可以执行依次以下操作若干次：

1. 选择一枚棋子，将其向上或者向下移动到**相邻**的一个好的且**没有其他棋子**的格子上。

2. 将所有棋子移动到下一列。若移动到下一列后有**任意一个**棋子落在坏的格子上，则不能执行此操作。

Justin现在给了你$Q$个问题，每一次给你一个$k_i$，询问你最多能在第一列上放多少枚棋子使得经过若干次操作后你能将所有棋子移动到最后一列，且**所有棋子加起来**最多执行$k_i$次1操作。

(感谢巨佬ywwywwyww 发现题目问题，现已修复。)




## 说明/提示

第一组样例：限制为0时，可以在(3,1)放置一枚棋子，然后一直执行二操作。

限制为1时，可以在(3,1)放置一枚棋子，在(2,1)放置一枚棋子，然后执行两次二操作之后对(2,3)上的棋子执行一次一操作到(1,3)，然后一直执行二操作就好了。

限制为2时，和上面一样。因为如果放置三枚棋子的话是没办法执行操作二的。

第二组样例：发现完全堵死了，所以根本不可能移动到最后一列。

数据范围：

|测试点编号|$N\le$|$M\le$|$T\le$|$Q\le$|
|:-------:|:-------:|:-------:|:-------:|:-------:|
|$1$|$1$|$10^6$|$1$|$10^5$|
|$2-6$|$10$|$100$|$10$|$100$|
|$7-10$|$20$|$100$|$50$|$10^3$|
|$11-14$|$30$|$10^4$|$100$|$10^4$|
|$15-20$|$50$|$10^6$|$10^3$|$10^5$|

$$1 \le x_i \le N \qquad 1\le y_i \le M \qquad 0 \le k_i \le 2^{31}-1$$

此题测试点$11$~$20$的数据随机生成。

## 样例 #1

### 输入

```
3 5 2 3
1 2
2 4
0
1
2
```

### 输出

```
1
2
2
```

## 样例 #2

### 输入

```
5 1000 5 10
1 2
2 3
3 4
4 5
5 6
0
1
2
3
4
5
6
7
8
9
```

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
0
0
```

# 题解

## 作者：CYJian (赞：2)

## Game

Upd：之前题目有一点问题，感谢巨佬 @ywwywwyww 指出。题面已经更正，原代码只需改动10字节左右即可AC。

事实上。。出题人也不知道能有什么部分分。。题面上那么多不同的数据范围只是想看看一道网络流能乱搞出什么算法。。

### 大概50分的朴素建图

可以考虑建一个网格图，对于每一个向上/下的边建一条费用$1$，流量$1$的边，每一条向左/右边建一条费用$0$，流量$Inf$的边，然后最左边连源点，右边连汇点，然后跑费用流，最多扩展$N$次，然后复杂度上界就是$O(N^3M^2)$，发现不够优秀。

这里的上下边的费用就限制了一操作的次数，左右边流量限制了两个棋子不能走到一起。

即使这种玄学图能充分发挥$Spfa$玄学性质，但是可能不能过$M=10^4$的数据,一定不能过$M=10^6$的数据。

### 70分做法

事实上发现$M$非常大的时候中间有很多空行没有什么卵用，这时候可以删去这些行，然后只留下有障碍的行及其前一行，这样的话就可以优化到$O(N^3T^2)$，但是这个玩意是上界，但是$Spfa$在这种边权只有$0/1/-1$的网格图+随机数据下跑得远不到上界，~~所以是可以过的。~~

Upd: 时限改成1s辣！！

所以上述方法就只能拿暴力分了。。那么怎么优化呢？？

### 100分做法

实际上我们在$0/1/-1$网格图中跑$Spfa$有一个非常简单的优化：用双端队列替换掉原来的队列，然后每一次插入的时候和队头比较，如果更小就插入到队头，否则插入到队尾。这样的话我们跑一次$Spfa$的复杂度就变成了$O(N^2T)$了(-1的边对这种方法有影响，但是最多影响一行内的点)。发现现在的复杂度上界是$O(N^3T)$，$10^8$左右，开O2跑得过。。

代码太丑了，还是不放了吧。。

---

## 作者：破忆 (赞：0)

## 【题意】
给定棋盘，棋盘上有障碍点，障碍点不能放棋子，每个格子只能放一个棋子，支持两种操作：

- 让某个棋子上下移动，需要花费 $1$ 的代价

- 让所有棋子向右移一格

初始时可以在第一列放若干棋子，要求结束时所有棋子到达最后一列，求在代价不超过 $k_i$ 的情况下，最多能放多少棋子。

## 【分析】
 $n$ 不大，可以求放 $i$ 个棋子的最小代价，询问时在预处理出的答案上二分。
 
最小代价可以用费用流求解，考虑如何建边。

$X\xrightarrow{f,c}Y$ 表示格子 $X$ 向 $Y$ 连容量为 $f$，费用为 $c$ 的边。

源点为 $S$，汇点为 $T$。

> $S\xrightarrow{1,0}(i,1)$，表示在第一列放棋子。

> $(i,m)\xrightarrow{1,0}T$，表示棋子到达最后一列。

> $(i,j)\xrightarrow{+\infty,1}(i\pm1,j)$，表示上下移动。

> $(i,j)\xrightarrow{1,0}(i,j+1)$，表示向右移动，保证每格只能容纳一个点。

------------

每次找一条增广路即可。

这样，一个朴素的模型就建好了。

但是由于 $m$ 达到了 $10^6$，时空两爆炸，考虑如何优化建图。

注意到，$T$ 的范围很小，也就是说，障碍点彼此相隔甚远，大部分列都可以直接通过，存在大量冗余计算。

于是，对于每个障碍点 $(x,y)$，我们只保留 $y$ 和 $y-1$ 这两列，前者用于限制棋子移动，后者为棋子提供上下移动的空间。

于是通过了本题。

## 【算法】

费用流

## 【代码】

```cpp
#include<bits/stdc++.h>
#define RE register
#define IN inline
using namespace std;
const int maxn=55,maxk=2e3+5,maxt=maxn*maxk,maxe=maxt*6,INF=1<<30;
int n,m,k,q;
IN char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar gc
IN int read(){
    RE int ret=0,f=1;RE char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
    while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
int S,T,SS;
struct edge{
	int to,nxt,f,d;
}e[maxe];
int tot,lnk[maxt];
IN void add_e(RE int x,RE int y,RE int f,RE int d){
	e[++tot]=(edge){y,lnk[x],f,d};
	lnk[x]=tot;
}
IN void ADD(RE int x,RE int y,RE int f,RE int d){
	add_e(x,y,f,d),add_e(y,x,0,-d);
}
bool vis[maxt];
int que[maxt],dis[maxt];
IN bool SPFA(){
	for(RE int i=1;i<=T;i++) dis[i]=INF,vis[i]=0;
	RE int hed=0,til=1;
	que[1]=T,vis[T]=1,dis[T]=0;
	while(hed!=til){
		RE int x=que[(++hed)%=maxt];
		vis[x]=0;
		for(RE int j=lnk[x];j;j=e[j].nxt){
			RE int y=e[j].to;
			if(e[j^1].f&&dis[y]>dis[x]-e[j].d){
				dis[y]=dis[x]-e[j].d;
				if(!vis[y]){
					vis[y]=1;
					que[(++til)%=maxt]=y;
					int nxt=(hed+1)%maxt;
					if(dis[que[til]]<dis[que[nxt]]) swap(que[til],que[nxt]);
				}
			}
		}
	}
	return dis[S]!=INF;
}
int ans1,ans2;
int DFS(RE int x,RE int limit){
	vis[x]=1;
	if(x==T||!limit) return limit;
	RE int flow=0,f;
	for(RE int j=lnk[x];j;j=e[j].nxt){
		RE int y=e[j].to;
		if(!vis[y]&&e[j].f&&dis[y]==dis[x]-e[j].d&&(f=DFS(y,min(limit-flow,e[j].f)))){
			e[j].f-=f;
			e[j^1].f+=f;
			flow+=f;
		}
		if(flow==limit) return flow;
	}
	return flow;
}
IN void calc(){
	if(SPFA()){
		int now=DFS(S,INF);
		ans1+=now;
		ans2+=now*dis[S];
	}
}
int b[maxk];
bool mp[maxn][maxk];
struct data{
	int x,y;
}a[maxk];
IN int getid(RE int x,RE int y){
	return (x-1)*m+y;
}
int ans[maxn];
IN int find(RE int x){
	RE int L=0,R=n,res=0;
	#define mid (L+R>>1)
	while(L<=R){
		if(ans[mid]<=x) res=mid,L=mid+1;
		else R=mid-1; 
	}
	return res;
}
int main(){
 	freopen("P5222.in","r",stdin);
 	freopen("P5222.out","w",stdout);
	n=read(),m=read(),k=read(),q=read();
	for(RE int i=1;i<=k;i++){
		RE int x=read(),y=read();
		b[++b[0]]=y,b[++b[0]]=y-1;
		a[i].x=x,a[i].y=y;
	}
	b[++b[0]]=1,b[++b[0]]=m;
	sort(b+1,b+1+b[0]);
	m=unique(b+1,b+1+b[0])-b-1;
	for(RE int i=1;i<=k;i++){
		a[i].y=lower_bound(b+1,b+1+m,a[i].y)-b;
		mp[a[i].x][a[i].y]=1;
	}
	S=n*m+1,T=S+1,tot=1;
	for(RE int i=1;i<=n;i++){
		if(!mp[i][1]) ADD(S,getid(i,1),1,0);
		if(!mp[i][m]) ADD(getid(i,m),T,1,0);
	}
	for(RE int i=1;i<=n;i++)
	for(RE int j=1;j<=m;j++) if(!mp[i][j]){
		RE int id=getid(i,j);
		if(i>1){
			RE int x=i-1,y=j;
			if(!mp[x][y]) ADD(id,getid(x,y),INF,1);
		}
		if(i<n){
			RE int x=i+1,y=j;
			if(!mp[x][y]) ADD(id,getid(x,y),INF,1);
		}
		if(j<m){
			RE int x=i,y=j+1;
			if(!mp[x][y]) ADD(id,getid(x,y),1,0);
		}
	}
	for(RE int i=1;i<=n;i++){
		calc();
		if(ans1<i){n=i-1;break;}
		ans[i]=ans2;
	}
	for(RE int i=1;i<=q;i++){
		RE int x=read();
		printf("%d\n",find(x));
	}
	return 0;
}
```

---

## 作者：SSerxhs (赞：0)

一道感觉比较裸的费用流，但是复杂度看起来爆炸，~~所以yww不切这题~~

以下如无特殊说明，边(x,y)表示流量为x费用为y

考虑答案的范围。最理想情况当然是一整列填满棋子，答案为n，而n远小于q，也就是说预处理出填i个格子至少要多少次1操作显然要比对于每次询问都求答案要来的方便。~~(所以这题询问不是应该放1e6吗)~~

考虑网格图有用的格子范围。虽然这题格子数目高达5e7，但是障碍点只有1e3，也就是说会有大量空列连在一起且毫无作用。考虑按照障碍点所在列和其前一列(用于进行自由地1操作调整)进行离散，则有用格子数目仅为1e5。

而建图就非常明显了:首先去掉那些障碍点，然后每个点向上下连一条容量为(inf,1)的边，向右连一条(1,0)，这样就可以保证不会有两个棋子重叠着向右。至于一个棋子向下跨过另一个棋子的情况，是和另一个棋子直接向下的移动等价的。

最后从超级源向最左边一排连(1,0)，最右边一排向超级源连一条(1,0)，借助EK-spfa每次只扩展一条路径的优势，可以很方便地处理出填i个格子的最小操作，即流量为i时的费用。

复杂度O(能过)，spfa加入双端队列食用更优

另：此题数据过水，上下连边为(1,1)都能过。。。
此种连边方法的hack：

4 4 4 1

1 1

2 1

3 3

4 3

999

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=2e5+20,M=1e7,inf=1e9;
int lj[M][3],nxt[M],fir[N],qq[N],dy[N],a[N],dl[M],jl[N],ycl[52],ans;;
int b[N],x[N],y[N],ys[52][2002];
int n,m,i,j,t,c,gs,q,bs,tou,wei;
bool ed[N],eed[52][2002];
inline void add(register int x,register int y,register int z,int c)
{
	lj[++bs][0]=y;
	lj[bs][1]=c;
	lj[bs][2]=z;
	nxt[bs]=fir[x];
	fir[x]=bs;
	lj[++bs][0]=x;
	lj[bs][2]=-z;
	nxt[bs]=fir[y];
	fir[y]=bs;
}
inline void read(register int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
bool spfa()
{
	register int x,i;
	memset(jl+1,0x3f,t+1<<2);
	jl[dl[tou=wei=(M>>1)]=0]=0;
	while (tou<=wei)
	{
		ed[x=dl[tou++]]=0;
		for (i=fir[x];i;i=nxt[i]) if ((lj[i][1])&&(jl[lj[i][0]]>jl[x]+lj[i][2]))
		{
			jl[lj[i][0]]=jl[x]+lj[i][2];
			qq[lj[i][0]]=x;
			dy[lj[i][0]]=i;
			if (!ed[lj[i][0]])
			{
				ed[lj[i][0]]=1;
				if (lj[i][2]==1) dl[++wei]=lj[i][0]; else dl[--tou]=lj[i][0];
			}
		}
	}
	if (jl[t]==jl[t+1]) return 0;
	for (i=t;i;i=qq[i])
	{
		x=dy[i];
		ans+=lj[x][2];
		--lj[x][1];++lj[x^1][1];
	}
	return 1;
}
int main()
{
	read(n);read(m);read(m);read(q);
	for (i=1;i<=m;i++)
	{
		read(x[i]);read(y[i]);
		a[i]=y[i];a[i+m]=y[i]-1;
	}
	m<<=1;
	sort(a+1,a+m+1);gs=0;
	for (i=2;i<=m;i++) if (a[i]!=a[i-1]) b[++gs]=a[i];
	m>>=1;
	for (i=1;i<=m;i++) eed[x[i]][lower_bound(b+1,b+gs+1,y[i])-b]=1;
	for (i=1;i<=n;i++) for (j=1;j<=gs;j++) if (!eed[i][j]) ys[i][j]=++bs;
	t=++bs;
	bs=1;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=gs;j++) if (!eed[i][j])
		{
			if ((i<n)&&(!eed[i+1][j])) add(ys[i][j],ys[i+1][j],1,inf);
			if ((i>1)&&(!eed[i-1][j])) add(ys[i][j],ys[i-1][j],1,inf);
			if ((j<gs)&&(!eed[i][j+1])) add(ys[i][j],ys[i][j+1],0,1);
		}
	}
	for (i=1;i<=n;i++)
	{
		if (!eed[i][1]) add(0,ys[i][1],0,1);
		if (!eed[i][gs]) add(ys[i][gs],t,0,1);
	}
	for (j=1;j<=n;j++) if (spfa()) ycl[j]=ans; else n=j-1;
	while (q--)
	{
		read(i);
		printf("%d\n",int(upper_bound(ycl+1,ycl+n+1,i)-ycl-1));
	}
}
```

---

