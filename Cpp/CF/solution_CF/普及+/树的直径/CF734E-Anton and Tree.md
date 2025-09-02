# Anton and Tree

## 题目描述

Anton is growing a tree in his garden. In case you forgot, the tree is a connected acyclic undirected graph.

There are $ n $ vertices in the tree, each of them is painted black or white. Anton doesn't like multicolored trees, so he wants to change the tree such that all vertices have the same color (black or white).

To change the colors Anton can use only operations of one type. We denote it as $ paint(v) $ , where $ v $ is some vertex of the tree. This operation changes the color of all vertices $ u $ such that all vertices on the shortest path from $ v $ to $ u $ have the same color (including $ v $ and $ u $ ). For example, consider the tree

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)and apply operation $ paint(3) $ to get the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/eabfeb953964c829d6d1820bd3bcad690b9ae826.png)Anton is interested in the minimum number of operation he needs to perform in order to make the colors of all vertices equal.

## 说明/提示

In the first sample, the tree is the same as on the picture. If we first apply operation $ paint(3) $ and then apply $ paint(6) $ , the tree will become completely black, so the answer is $ 2 $ .

In the second sample, the tree is already white, so there is no need to apply any operations and the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 0 0 0
1 2
2 3
3 4
```

### 输出

```
0
```

# 题解

## 作者：ShallowDream雨梨 (赞：41)

看到现在所有的题解用的都是带并查集的，这里提供一个不写并查集的。

思路其实很简单，遍历所有的边，如果边的两端颜色不一样，那么就将这条边权置成1，最后求树的直径即可。


(这边用的是树形DP求直径)

### 下面是AC代码

```cpp
        #include<bits/stdc++.h> 
        using namespace std;
        const int maxn=200005;
        int anss,d[maxn],ans[maxn],ans1,node,tot,head[maxn],q,w,f[maxn],col[maxn];
        struct road{int v,to,next;}a[maxn*2];
        void add(int x,int y,int z){//存图
        	tot++;
        	a[tot].v=z;
        	a[tot].to=y;
        	a[tot].next=head[x];
        	head[x]=tot;}
      	 void dp(int x,int fa){
      	 	for(int i=head[x];i;i=a[i].next){
      	 	int to=a[i].to;
      	 	if(to==fa)continue;
      	 	dp(to,x);
      	 	anss=max(anss,d[x]+d[to]+a[i].v);
      	 	d[x]=max(d[x],d[to]+a[i].v);}}
        int main(){  
        	int n;
        	cin>>n;
        	for(int i=1;i<=n;i++)
        	cin>>col[i];
        	for(int i=1;i<n;i++){
        	cin>>q>>w;
        	if(col[q]==col[w])//颜色相同边权为0
        	{add(q,w,0);add(w,q,0);}
        	else {add(q,w,1);add(w,q,1);}//颜色不同边权为1
            }
        	dp(1,0);
        	cout<<(anss+1)/2;
        	return 0;}
```
留个赞再走吧~~~
           

---

## 作者：superMB (赞：19)

先不要脸的安利一下我的蒟蒻空间[superMB的空间](https://www.luogu.org/blog/suuuuuperMB/)

看到这个题没有题解，我就想来~~闷声发大财~~为大众造福

我们先来看一下样例里的树

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)

乍一眼看很混乱对不对

一开始会觉得有点难以下手，但是我们可以化繁为简：
因为对一个点操作一次就可以将其周围的颜色相同的点全部变色，所以我们其实可以直接把相邻的相同颜色的点直接看做一个点，再建起一棵小树。

那么要怎么建立第二棵树呢？

那么这时候就要用到并查集了，将相邻的同色点全部指向一个father，然后检查一次缩合的点内的点，如果和另外一点连接并且颜色不同，那么就将它们的father连接起来。

![](https://s1.ax1x.com/2018/10/17/idqfdH.png)

建好了第二棵树，这就显得清新了很多

并且仔(ting)细(lao)研(shi)究(jiang),我们发现这个小树还有一个灰常有趣的性质：相邻两个节点的颜色一定不相同，那么如果我们要让整棵树都变为一个颜色，就只用在直径上操作直径长度加1除以2次，整棵树就可以变成一个颜色了。

因为数据量较大，所以建议使用读优输优

下面是朴素的代码
```cpp
#include<cstdio>
#define maxn 200005
#define ri register int
#define rc register char
using namespace std;
template<typename TP>inline void read(TP&x)
{
	x=0;ri f=1;rc c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
template<typename TP>inline void write(TP x)
{
	if(x==0){putchar('0');return;}
	rc father[100]={0};ri i=0;
	if(x<0){putchar('-'),x=-x;}
	while(x){++i,father[i]=x%10+48;x/=10;}
	while(i){putchar(father[i]),--i;}
}
//————↑快读快输优化↑———— 
int head1[maxn],tot1;
struct node1{int to,nxt;}e1[maxn<<1];
inline void add1(int from,int to)//原图 
{
	++tot1;
	e1[tot1].to=to;
	e1[tot1].nxt=head1[from];
	head1[from]=tot1;
}
int head2[maxn],tot2;
struct node2{int to,nxt;}e2[maxn<<1];
inline void add2(int from,int to)//缩点之后的图 
{
	++tot2;
	e2[tot2].to=to;
	e2[tot2].nxt=head2[from];
	head2[from]=tot2;
}
//————↑前向星↑———— 
int father[maxn];
inline int find(int x){if(father[x]!=x)father[x]=find(father[x]);return father[x];}
inline void join(int x,int y){x=find(x),y=find(y);if(x!=y)father[x]=y;}
//————↑并查集↑————
bool color[maxn],vis[maxn];
int n,a[maxn],b[maxn];
inline void Union(int x,int fa)//寻找相同颜色的点
{
	for(ri i=head1[x];i;i=e1[i].nxt)
		if(e1[i].to!=fa&&color[e1[i].to]==color[x]&&(!vis[e1[i].to]))
		{
			join(e1[i].to,x);
			vis[e1[i].to]=1;
			Union(e1[i].to,x);
		}
}
int maxdep,maxw;
inline void dfs(int dep,int x,int fa)
{
	if(dep>maxdep)
		maxdep=dep,maxw=x;
	for(ri i=head2[x];i;i=e2[i].nxt)
		if(e2[i].to!=fa)
			dfs(dep+1,e2[i].to,x);
}
//————↑电风扇(笑)↑————
int main()
{
	read(n);
	for(ri i=1;i<=n;++i)//进行输入和并查集初始化 
	{
		read(color[i]);
		father[i]=i;
	}
	for(ri i=1;i<n;++i)//建立原图 
		read(a[i]),read(b[i]),add1(a[i],b[i]),add1(b[i],a[i]);
	for(ri i=1;i<=n;++i)//进行dfs缩点 
		if(!vis[i])
			Union(i,0);
	for(ri i=1;i<=n;++i)//建立新图 
		if(father[a[i]]!=father[b[i]])
			add2(father[a[i]],father[b[i]]),add2(father[b[i]],father[a[i]]);//若缩合后的点的father 
	dfs(0,1,0);//求树的直径 
	dfs(0,maxw,0);
	write((maxdep+1)>>1);//fin 
}
```
以下是另外一种只用一遍dfs的做法
```cpp
#include<cstdio>
#define ri register int
#define rc register char
using namespace std;
const int maxn=200005;
template<typename TP>inline void read(TP&x)
{
    x=0;ri f=1;rc c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    x*=f;
}
template<typename TP>inline void write(TP x)
{
    if(x==0){putchar('0');return;}
    rc father[100]={0};ri i=0;
    if(x<0){putchar('-'),x=-x;}
    while(x){++i,father[i]=x%10+48;x/=10;}
    while(i){putchar(father[i]),--i;}
}
//————↑快读快输优化↑———— 
int head[maxn],tot;
struct node{int to,nxt;}e[maxn<<1];
inline void add(int from,int to)//缩点之后的图 
{
    ++tot;
    e[tot].to=to;
    e[tot].nxt=head[from];
    head[from]=tot;
}
//————↑前向星↑———— 
int father[maxn];
inline int find(int x){if(father[x]!=x)father[x]=find(father[x]);return father[x];}
inline void join(int x,int y){father[x]=y;}
//————↑并查集↑————
int maxdep,maxw;
inline void dfs(int dep,int x,int fa)
{
    if(dep>maxdep)
        maxdep=dep,maxw=x;
    for(ri i=head[x];i;i=e[i].nxt)
        if(e[i].to!=fa)
            dfs(dep+1,e[i].to,x);
}
//————↑电风扇↑————
int tempa,tempb;
int n,a[maxn],b[maxn];
bool color[maxn];
int main()
{
    read(n);
    for(ri i=1;i<=n;++i)
    {
        read(color[i]);
        father[i]=i;
    }
    for(ri i=1;i<n;++i)
    {
        read(a[i]),read(b[i]);
        tempa=find(a[i]),tempb=find(b[i]);
        if(color[tempa]==color[tempb])
            father[tempa]=father[tempb];
    }
    for(ri i=1;i<=n;++i)
    	father[i]=find(father[i]);
    for(ri i=1;i<=n;++i)
        if(father[a[i]]!=father[b[i]])
            add(father[a[i]],father[b[i]]),add(father[b[i]],father[a[i]]);
    dfs(0,father[1],0);
    dfs(0,maxw,0);
    write((maxdep+1)>>1);
}
```

---

## 作者：reyik (赞：6)

~~最近迷上了树~~$EMM$...

大家都会并查集缩点吧，这里是把所有颜色相同的点缩到一起。（~~我肯定不会~~）

然后数的直径大家都会吧，就是随便找一个点，求出最远点，再从最远点开始求最远点，求两次大法师步数最大值的最大值。

这题就是先并查集缩点，然后在新图上跑一遍数的直径（要证明去找 @[skip2004](https://www.luogu.org/space/show?uid=30122)）

然后就简单了

代码发一波。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#define Rint register int
#define Temp template<typename T>
using namespace std;
Temp inline void read(T &x) {
	x=0;T w=1,ch=getchar();
	while(!isdigit(ch)&&ch!='-') x=x*10+ch-'0',ch=getchar();
	if(ch=='-') w=-1,ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	x*=w; 
}
inline void write_(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write_(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x) {
	write_(x);
	putchar('\n');
}
const int maxn=2e5+5;
struct Edge{
	int to,nxt;
}e[maxn<<1];
int color[maxn],n,cnt=0,father[maxn],x[maxn],y[maxn],maxc,ans=-1,head[maxn];
inline void addedge(int x,int y) {
	cnt++;
	e[cnt].nxt=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
inline int find_(int x) {
	if(father[x]!=x) father[x]=find_(father[x]);
	return father[x];
}
inline void dfs(int fa,int u,int deep) {
	if(deep>ans) {
		maxc=u;
		ans=deep;
	}
	for (Rint i=head[u];~i;i=e[i].nxt) {
		int v=e[i].to;
		if(v!=fa) dfs(u,v,deep+1);
	}
	return ;
}
int main() {
	read(n);
	memset(head,-1,sizeof(head));
	for (Rint i=1;i<=n;++i) father[i]=i;
	for (Rint i=1;i<=n;++i) read(color[i]);
	for (Rint i=1;i<n;++i) {
		read(x[i]);read(y[i]);
		int xf=find_(x[i]),yf=find_(y[i]);
		if(color[xf]==color[yf]) father[xf]=yf;
	}
	for (Rint i=1;i<=n;++i) father[i]=find_(father[i]);
	for (Rint i=1;i<=n;++i) if(father[x[i]]!=father[y[i]]) addedge(father[x[i]],father[y[i]]),addedge(father[y[i]],father[x[i]]);
	dfs(0,father[1],0);
	dfs(0,maxc,0);
	writeln((ans+1)>>1);
	return 0;
}
```

---

## 作者：二gou子 (赞：4)

## 思路

这个题的本质很简单：求树的直径，是个思维题。

我们每次操作可以将一个连通块从黑色染成白色或者从白色染成黑色。很容易可以想到，每一次我们将连通的颜色相同的一个块染成别的颜色，然后就得到了一个大一圈的颜色相同的连通块。这样不断染色，一定是最优策略，感性理解一下即可明白。

那么现在问题的关键就在于从哪一个点开始染色。假设现在你眼前有一棵树，你会选择从中间找一个点向两边扩散染色还是从边上找一个点向另一边染色？当然是果断选择前者。而树上最长的路径即为树的直径。我们从树的直径的中点开始染色，得到的就一定是最少的步数。

~~那这道紫题居然就做完了~~。。。求出直径再手造两组数据找找规律即可发现答案与直径间的关系。

## 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<ctime>
using namespace std;
const int N=200005,M=400005;
int n,tot,sum,s;
int color[N],ver[M],Next[M],head[N],edge[M],d[N];
bool v[N];
queue<int> q;
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
void bfs1(){
	sum=0;
	d[1]=0;
	v[1]=1;
	q.push(1);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(v[y]) continue;
			if(color[x]==color[y]){//如果颜色一样则可以一次染色，所以路径长度不变
				d[y]=d[x];
			}
			else{
				d[y]=d[x]+1;
				if(d[y]>sum){//找最远点，详情见两次bfs求树的直径
					sum=d[y];
					s=y;
				}
			}
			q.push(y);
			v[y]=1;
		}
	}
}
void bfs2(){
	memset(v,0,sizeof(v));
	sum=0;
	d[s]=0;
	v[s]=1;
	q.push(s);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(v[y]) continue;
			if(color[x]==color[y]){
				d[y]=d[x];
			}
			else{
				d[y]=d[x]+1;
				sum=max(sum,d[y]);
			}
			v[y]=1;
			q.push(y);
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&color[i]);
	}
	for(int i=1,x,y;i<=n-1;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	bfs1();
	bfs2();
	printf("%d\n",(sum+1)>>1);
	return 0;
}
```

我用的是两次bfs求出树的直径，其它的方法也可以，只不过我写起来比较顺手罢了。唯一与板子不同的就是要在bfs的过程中判一下颜色。如果终点与起点颜色相同那么距离不变。反之距离就+1。写两遍板子即可。

---

## 作者：HSY666 (赞：4)

关于这道题，许多大佬已经给出了题解，我说一下我的想法：

因为一次操作可以使一个相同颜色的连通块变成另一种颜色，那我们自然而然地想到缩点，对于缩点使用并查集就很容易做到，可以把颜色相同且相连的点先用并查集连在一起，并查集要路径压缩，否则会T掉。

 _接下来就是建图，在这里有一个关键要点--先把所有相同颜色通块缩好点，再建图（这个好像之前的题解都没有强调），否则会出现不是根与根相连的情况！_ ~~我一开始做就这样被WA>_<。~~

建图就比较简单了，有很多种方法，我用的是邻接表。这个图显然没有环，也就可把它看做一棵树，题目要求使整棵树变成一种颜色的最少操作数，我们可以发现，从树的直径开始变色，每次向外扩展一层，是最优的变色方案。这里给一下树的直径的定义：

树中所有 _最短路径距离的最大值_ 即为树的直径。

在完成缩点后，整棵树显然是黑白相间的，对于此，无论从哪个点开始变色，最优的都应该是从那个点开始，向外扩展变色，根据定义，如果不是在树的直径开始的话，就会失去对称性，使步数增加。所以应找到树的直径，步数显然是直径长度的一半，也就是$\lfloor\dfrac{L+1}{2}\rfloor$。

接下来就是寻找树的直径了，一般有两种方法—两遍DFS或者DP，我用的是两遍DFS，先随机选一个点，比如一号节点A， _找到它的根_ （这个千万不能忘！），然后一遍DFS找到距离他最远的节点B（这个节点显然一定是树的叶子），再从找到的点B出发，DFS找到距离B最远的点C（这个节点显然也一定是树的叶子，叶子与距离它最远的叶子相连必是直径）。我们就找到了树的直径BC，再求出$\lfloor\dfrac{L+1}{2}\rfloor$就是答案了。

关于时间复杂度，显然是合理的，实际跑也没到200毫秒。

下面贴上我的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int n,u,v,fa[200005],dep[200005];
bool a[200005],vis[200005];
vector <int> edge[200005];
queue <pair<int,int> > q;

int GetFather (int x)
{
	if (x==fa[x])  return x;
	return fa[x]=GetFather(fa[x]);           //并查集路径压缩 
}

int Dfs (int x)           //DFS找最远点 
{
	vis[x]=1;           //因为是无向图，走过要做标记 
	int far=x;           //最远点 
	for (int i=0;i<edge[x].size();++i)
	{
		int y=edge[x][i];
		if (vis[y])  continue;
		dep[y]=dep[x]+1;           //用深度作比较 
		int w=Dfs(y);           //递归求解 
		if (dep[w]>dep[far])  far=w;
	}
	return far;
}

int main ()
{
	scanf ("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf ("%d",&a[i]);
		fa[i]=i;
	}
	for (int i=1;i<n;++i)
	{
		scanf ("%d%d",&u,&v);
		u=GetFather(u);           //找根 
		v=GetFather(v);
		if (a[u]==a[v]&&u!=v)  fa[u]=v;           //并查集缩点 
		else if (a[u]!=a[v])
		{
			q.push(make_pair(u,v) );           //收集所有需要连边的点 
		}
	}
	while (!q.empty())
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		x=GetFather(x);
		y=GetFather(y);
		edge[x].push_back(y);           //连边，建图 
		edge[y].push_back(x);
	}
	int p=Dfs(GetFather(1));           //第一遍DFS找最远点 
	memset(vis,0,sizeof(vis));           //不要忘了初始化数组 
	memset(dep,0,sizeof(dep));
	int q=Dfs(p);           //第二遍DFS找到直径 
	printf ("%d",(dep[q]-dep[p]+1)/2);
	return 0;
}
```



---

## 作者：FjswYuzu (赞：3)

简单题，二十分钟秒掉了。

考虑到我们可以直接更改一个**连通块**内所有的节点颜色，我们干脆把树上的所有相同颜色连通块缩点缩到一起。现在我们得到一棵更小的树，这棵树满足对于任意一个节点，这个节点连接到的另一个节点与当前这个节点颜色一定不同。

于是这道题变成了求树直径。设树直径为 $d$，最优答案为 $\lfloor \dfrac{d+1}{2} \rfloor$。

证明：

假设我们有更优的答案。树直径为 $d$，我们需要把直径合并成一个颜色，显然我们需要合并 $\lfloor \dfrac{d+1}{2} \rfloor$ 次，说明没有更优的答案，因此最优答案为 $\lfloor \dfrac{d+1}{2} \rfloor$。

对于具体缩点过程，可以写为下面的过程：

1. `dfs` 中遍历到当前节点，如果这个节点的颜色和其父亲不同，说明这是一个新的强连通分量，否则这个节点与父亲属于一个强连通分量；   
2. 遍历这个节点的儿子。

时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> G[200005],Gn[200005];
int n,col[200005],scc[200005],cnt,ncol[200005],dp[200005][2];
bool used[200005];
void dfs(int now,int pre)
{
	if(col[pre]!=col[now])	scc[now]=++cnt;
	else	scc[now]=scc[pre];
	for(unsigned int i=0;i<G[now].size();++i)
	{
		int to=G[now][i];
		if(to==pre)	continue;
		dfs(to,now);
	}
}
int dis,maxn;
void dfs1(int now,int pre,int far)
{
	if(far>dis)
	{
		dis=far;
		maxn=now;
	}
	for(unsigned int i=0;i<Gn[now].size();++i)
	{
		int to=Gn[now][i];
		if(to==pre)	continue;
		dfs1(to,now,far+1);
	}
}
int main(){
	scanf("%d",&n);
	col[0]=-1;
	for(int i=1;i<=n;++i)	scanf("%d",&col[i]);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	int p=0,q=0;
	for(int i=1;i<=n;++i)
	{
		if(used[scc[i]])	continue;
		if(col[i])	++p;
		else	++q;
		used[scc[i]]=true;
		ncol[scc[i]]=col[i];
	}
	for(int i=1;i<=n;++i)
	{
		for(unsigned int j=0;j<G[i].size();++j)
		{
			int u=i,v=G[i][j];
			if(scc[u]==scc[v])	continue;
			Gn[scc[u]].push_back(scc[v]);
		}
	}
	for(int i=1;i<=n;++i)	sort(Gn[i].begin(),Gn[i].end()),Gn[i].erase(unique(Gn[i].begin(),Gn[i].end()),Gn[i].end());
	dfs1(1,0,0);
	dfs1(maxn,0,0);
	printf("%d",(dis+1)/2);
	return 0;
}
```

---

## 作者：Strelitzia (赞：2)

[题目床送门](https://www.luogu.com.cn/problem/CF734E)

---

这道题一个重要的点就是：一个色块可以全部改变。

所以我们可以把一个色块，看成一个节点，然后我们会得到一个新的小的树。

样例就变成了这样

![](https://i.loli.net/2020/08/13/CFr3lN79mKfgxZM.png)

你会发现一个有趣的事情，一条边连接的两个点颜色不同。

所以我们改变一个点的颜色，就会把它的颜色变为和它相连接的点的颜色。

然后我们用贪心的思想，从直径的中间开始变，设直径为 $d$，所需次数就是$\lfloor \dfrac{d + 1}{2} \rfloor$。

现在解决如何缩点，判断当先点 $u$，是否和父节点 $fa$ 的颜色是否相同，

相同将点编号变为父节点的编号，不同就建边。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 200005;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int x,int y) {
	nxt[++ tot] = head[x];ver[tot] = y;head[x] = tot;
}

int n,col[maxn],a[maxn],first[maxn],second[maxn],ans;
vector<int> g[maxn];

void dfs(int u,int fa) {
	if (col[u] == col[fa]) a[u] = a[fa];
	else g[a[fa]].push_back(a[u]);
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == fa) continue;
		dfs(v,u);
	}
}

void dfs2(int u,int fa) {
	for (int i = 0 ; i < g[u].size() ; ++ i) {
		int v = g[u][i];
		dfs2(v,fa);
		if (first[v] + 1 >= first[u]) {
			second[u] = first[u];
			first[u] = first[v] + 1;
		}
		else if (first[v] + 1 > second[u]) second[u] = first[v] + 1;
	}
	ans = max(ans,first[u] + second[u]);
}

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) read(col[i]),a[i] = i;
	int x,y;
	for (int i = 1 ; i < n ; ++ i) read(x),read(y),addEdge(x,y),addEdge(y,x);
	col[0] = 2;
	dfs(1,0);
	dfs2(1,0);
	printf("%d\n",(ans + 1) / 2);
	return 0;
}
```

---

## 作者：极寒神冰 (赞：2)

同一个颜色的一个联通块可以被一起染色，所以说可以直接看成一个点。实现方法大概就是给每个点重新标号，如果联通且颜色相同就标同一个号。之后再重新建树。

可以发现重新建出的树相邻两个点的颜色一定是不同的。所以需要修改的次数就是树的直径$/2$上取整。

```

#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=400040;
struct edge
{
	int nxt,to;
}e[N];
int head[N],cnt;
int n;
int fa[N],x[N],y[N];
int col[N];
int maxx,id;
inline int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void mer(int x,int y)
{
	int tx=find(x),ty=find(y);
	if(col[tx]==col[ty]) fa[ty]=tx;
}
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline void dfs(int u,int f,int dep)
{
	if(dep>maxx){maxx=dep;id=u;}
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u,dep+1);
	}
}
int main()
{
	init();
	n=read();
	for(int i=1;i<=n;i++)
	{
		col[i]=read();
		fa[i]=i;
	}
	for(int i=1;i<n;i++)
	{
		x[i]=read(),y[i]=read();
		mer(x[i],y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		fa[i]=find(fa[i]);//缩点
	}
	for(int i=1;i<=n;i++)
	{
		if(fa[x[i]]!=fa[y[i]])
		{
			add_edge(fa[x[i]],fa[y[i]]);//建图
			add_edge(fa[y[i]],fa[x[i]]);
		}
	}
	dfs(fa[1],0,0);//两遍深搜求树的直径
	dfs(id,0,0);
	cout<<(maxx+1)/2;
}	

```


---

## 作者：xiayucc (赞：2)

### 并查集+树的直径

一开始想的是缩点+树的直径，但是2e5的点貌似会TLE（别问我为什么，我交了五六发）

所以想到用并查集来代替缩点减少时间

#### 什么是树的直径？
给定一棵树，树中每条边都有一个权值，树中两点之间的距离定义为连接两点的路径边权之和。树中最远的两个节点之间的距离被称为树的直径，连接这两点的路径被称为树的最长链。后者通常也可称为直径，即直径是一个 
数值概念，也可代指一条路径
树的直径通常有两种求法，时间复杂度均为O(n)。我们假设树以N个点N-1条边的无向图形式给出，并存储在邻接表中

有两种算法复杂度都是O(n)的

推荐一个大佬写的介绍 很好懂     

[(●'◡'●)](https://www.cnblogs.com/ywjblog/p/9254997.html)

做法：

① 当两个点的祖先不一样并且他们的颜色一样的时候，将他们两个点合并在一起

②统计最后剩下来的点，将他们重新标记，然后重建图，当然，如果你求出来两个点的祖先是一样的时候，显然是不需要再建的。我们只需要遍历之前的边，并重建出祖先不同的边

③最后一步，直接套模板求出树的直径。直径为maxx，那么树的直径上一定有maxx+1个点。当(maxx+1)%2==0时显然我们只需要合并（maxx+1）/2次就OK了，如果(maxx+1)%2==1,我们就合并maxx/2个点就好了

##### （因为重建出来的新的图他一定是：黑白黑白黑白一直交替出现的）








### Code：

```c
		#include<bits/stdc++.h>
		using namespace std;
		int pre[400010]; //里面全是掌门
		map <int,int> mapp;
		const int maxn = 400086;
        struct picture {
            int y, v, net;
            int pre;
        }e[maxn];
        int lin[maxn], len = 0;
        int  m, dis[maxn];
        bool vis[maxn];
        int start, endd;

        inline int read() {
            int x = 0, y = 1;
            char ch = getchar();
            while(!isdigit(ch)) {
                if(ch == '-') y = -1;
                ch = getchar();
            }
            while(isdigit(ch)) {
                x = (x << 1) + (x << 3) + ch - '0';
                ch = getchar();
            }
            return x * y;
        }

        inline void insert(int xx, int yy, int vv) {
            e[++len].y = yy;
            e[len].v = vv;
            e[len].net = lin[xx];
            e[len].pre = xx;
            lin[xx] = len;
        }

        void dfs(int st) {
            vis[st] = 1;
            for(int i = lin[st]; i; i = e[i].net) {
                int to = e[i].y;
                if(!vis[to]) {
                    dis[to] = dis[st] + e[i].v;
                    dfs(to);
                }
            }
        }
		 int unionsearch(int root)
		{
			int son, tmp;
			son = root;
			while(root != pre[root]) //寻找掌门ing……
				root = pre[root];
			while(son != root) //路径压缩
			{   tmp = pre[son];
				pre[son] = root;
				son = tmp;     }
			return root; //掌门驾到~
		}
        int n,num, road, total, i, from[200011], to[200101],v[200101], root1, root2;
		 int main()
		{
			scanf("%d", &num);
			road=num-1;
			for(int i=1;i<=num;i++)
                cin>>v[i];
				total = num; //共num-1个门派
				for(int i = 1; i <= num; ++i) //每条路都是掌门
					pre[i] = i;
                int k=road;

				while(k--)
				{
				    cin>>from[k]>>to[k];
					root1 = unionsearch(from[k]);
					root2 = unionsearch(to[k]);
					if(root1 != root2&&v[root1]==v[root2]) //掌门不同？踢馆！~
					{
						pre[root1] = root2;
						total--; //门派少一个，敌人（要建的路）就少一个
					}
				}
				int sum=0;
				for(int i=1;i<=num;i++)
                {
                    root1 = unionsearch(i);
                    if(mapp[root1]==0)
                    {
                        sum++;
                        mapp[root1]=sum;
                    }
                }
                memset(vis, 0, sizeof(vis));
                memset(dis, 0x3f3f3f, sizeof(dis));
                for(int i = 0; i < road; i++) {
                    root1 = unionsearch(from[i]);
					root2 = unionsearch(to[i]);
					if(root1 != root2) //掌门不同？踢馆！~
					{
						insert(mapp[root1], mapp[root2], 1);
                        insert(mapp[root2], mapp[root1], 1);
					}
                }

                n=sum;
                dis[1] = 0;
                dfs(1);
                int maxx = -1000;
                for(int i = 1; i <= n; ++i)
                    if(dis[i] > maxx && dis[i] != 1061109567) {
                        maxx = dis[i];
                        start=i;
                    }
                memset(vis, 0, sizeof(vis));
                memset(dis, 0x3f3f3f,sizeof(dis));
                dis[start] = 0;
                dfs(start);
                maxx = -1000;
                for(int i = 1; i <= n; ++i)
                    if(dis[i] > maxx && dis[i] != 1061109567) {
                        maxx = dis[i];
                        endd = i;
                    }
                 if((maxx+1)%2==0)
                     printf("%d\n",(maxx+1)/2);
                else
                     printf("%d\n",(maxx)/2);
			return 0;
        }

```

学会了的话记得好评哟，亲






---

## 作者：_Clown_ (赞：1)

# Sol.
[完整版（或许是更佳的阅读体验？）](https://www.cnblogs.com/Xsmyy/p/13551469.html)
### 来讲讲大体的思路吧！
这道题目，我们首先要想到：
- 把那些相同颜色的点缩到一起，并不会影响答案。

缩点如图（样例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/hiysx0kj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后，似乎就豁然开朗了。

~~缩完点以后似乎变成了一道求树的直径**の**问题？~~

求完树的直径之后，我们容易想到：
$$
Ans=\biggl\lfloor\frac{Diamater+1}{2}\biggr\rfloor
$$
代码
```cpp
#include<bits/stdc++.h>
#define MAX 1000001
using namespace std;
int TotalPoint;
int Count;
int Color[MAX];
int Block[MAX];
int First[MAX],Second[MAX];
vector< int >Edge[MAX];
vector< int >NewEdge[MAX];
inline void Shrink(int Now,int Father)
{
	if(Color[Now]==Color[Father])
	{
		Block[Now]=Block[Father];
	}
	else
	{
		NewEdge[Block[Father]].push_back(Block[Now]);
	}
	register int i;
	for(i=0;i<Edge[Now].size();i++)
	{
		register int Next;
		Next=Edge[Now][i];
		if(Next!=Father)
		{
			Shrink(Next,Now);
		}
	}
}
inline void Diamater(int Now,int Father)
{
	register int i;
	for(i=0;i<NewEdge[Now].size();i++)
	{
		register int Next;
		Next=NewEdge[Now][i];
		Diamater(Next,Father);
		if(First[Next]+1>=First[Now])
		{
			Second[Now]=First[Now];
			First[Now]=First[Next]+1;
		}
		else
		{
			if(First[Next]+1>Second[Now])
			{
				Second[Now]=First[Next]+1;
			}
		}
	}
}
int main(void)
{
	register int i;
	cin>>TotalPoint;
	for(i=1;i<=TotalPoint;i++)
	{
		Block[i]=i;
	}
	Color[0]=233;
	for(i=1;i<=TotalPoint;i++)
	{
		cin>>Color[i];
	}
	for(i=1;i<TotalPoint;i++)
	{
		register int U,V;
		cin>>U>>V;
		Edge[U].push_back(V);
		Edge[V].push_back(U);
	}
	Count=0;
	Shrink(1,0);
	Diamater(1,0);
	register int Ans;
	Ans=0;
	for(i=1;i<=TotalPoint;i++)
	{
		Ans=max(Ans,First[i]+Second[i]);
	}
	cout<<(Ans+1)/2<<endl; 
	return 0;
}

```

---

## 作者：Trimsteanima (赞：1)

# $\mathtt{CF734E}$

## $\mathcal{Description}$

给一棵$n(n\leq200000)$个节点的树，每个点为黑色或白色，一次操作可以使一个相同颜色的连通块变成另一种颜色，求使整棵树变成一种颜色的最少操作数。

## $\mathcal{Solution}$

这棵树中每个点为黑点或白点，然后最后也只要求出最小操作数，对于一个联通块，我们选择其中任何一个节点进行染色的效果是一样的（都会把这个联通块变成同一个颜色），于是我们自然而然的可以想到缩点。然后样例中的树就可以是![](https://s1.ax1x.com/2018/10/17/idqfdH.png)

(贺个图$qwq$)

可以看出我们把这个树从原先的树变成了一棵异层颜色相异（也就是黑白相间）的树，如果当前是一条链，我们要是最后操作数是最小的，我们一定会选择从中间开始染色，所以对于一棵树，我们只需要选择他的直径进行染色，最后的答案就是$(直径+1)/ 2$。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

int n, color[N];
vector<int> a[N];

inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}

pair<int, int> dfs(int x, int fa, int depth) {
    int sz = a[x].size();
    pair<int, int> tmp = make_pair(depth, x);
    for (int i = 0; i < sz; i++) {
        int y = a[x][i];
        if (y == fa)
            continue;
        if(color[y] != color[x])
            tmp = std::max(tmp, dfs(y, x, depth + 1));
        else 
            tmp = std::max(tmp, dfs(y, x, depth));
    }
    return tmp;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        color[i] = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        a[x].push_back(y), a[y].push_back(x);
    }
    pair<int, int> tmp = dfs(1, -1, 0);
    tmp = dfs(tmp.second, -1, 0);
    printf("%d\n", tmp.first + 1 >> 1);
}
```

---

## 作者：MyukiyoMekya (赞：0)

题意：

一棵树上有黑白两种颜色的结点，每次可以把连通的一种颜色变成另一种颜色。求至少要多少次，才能是整棵树变为一种颜色。

---

因为一次操作后是整个同色连通块同时变色，那就先把同色连通块缩成一个点

缩完点后，求直径 $d$ ，答案为 $\lfloor \frac {d+1}2 \rfloor$

**but why?**

缩完点后的图上每两个相邻的点颜色一定不同，否则应该变成1个点了

要算直径的原因是，直径是树中最长的路径，你无论怎么操作总不可能把直径都变成同一种颜色而还有其他路径非同色吧

那么直接考虑如何把直径变成同一种颜色了。肯定是从直径的中间部分开始操作。我们来模拟一下

```
1 0 1 0 1 0 // 0 changes
```

```
1 0 [0] 0 1 0 // 1 changes
```

```
1 1 [1] 1 1 0 // 2 changes
```

```
0 0 [0] 0 0 0 // 3 changes
```

然后你再模拟发现直径长度为7要4次，长度为8要4次，长度为9要5次

于是你就找到了规律 ~~（华生，你发现了盲点~~

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define pii pair<int,int>
using namespace std;
const int MaxN=200050;
struct Edge
{
	int nxt,to;
}E[MaxN<<1],Ep[MaxN<<1];
template <class t> inline void rd(t &s)
{
	s=0;
	reg char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return;
}
int hd[MaxN],hdp[MaxN],en,enp,n;
int col[MaxN],idp[MaxN];
bool vis[MaxN];
pii dis[MaxN];
inline void adde(int u,int v)
{
	++en;
	E[en].nxt=hd[u];
	E[en].to=v;
	hd[u]=en;
	return;
}
inline void addep(int u,int v)
{
//	cout<<"addep: "<<u<<" -> "<<v<<endl;
	++enp;
	Ep[enp].nxt=hdp[u];
	Ep[enp].to=v;
	hdp[u]=enp;
	return;
}
inline void dfs1(int u,int color,int idx)
{
	vis[u]=true;
	idp[u]=idx;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(vis[v])
			continue;
		if(col[v]!=color)
			continue;
		dfs1(v,color,idx);
	}
	return;
}
inline void dfs2(int u,int color,int idx)
{
	if(col[u]!=color)
	{
		addep(idp[u],idx);
		addep(idx,idp[u]);
		return;
	}
	vis[u]=true;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(vis[v])
			continue;
		dfs2(v,color,idx);
	}
	return;
}
inline void dfs3(int u,int fa)
{
	for(int i=hdp[u];~i;i=Ep[i].nxt)
	{
		reg int v=Ep[i].to;
		if(v==fa)
			continue;
		dis[v].first=dis[u].first+1;
		dfs3(v,u);
	}
	return;
}
signed main(void)
{
	ios::sync_with_stdio(false);cin.tie(0);
	memset(hd,-1,sizeof hd);
	memset(hdp,-1,sizeof hdp);
	reg int u,v,cnt=0;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>col[i];
	for(int i=1;i<n;++i)
	{
		cin>>u>>v;
		adde(u,v);adde(v,u);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			dfs1(i,col[i],++cnt);
	memset(vis,false,sizeof vis);
	for(int i=1;i<=n;++i)
		if(!vis[i])
			dfs2(i,col[i],idp[i]);
	for(int i=1;i<=cnt;++i)
		dis[i].second=i;
	dfs3(1,0);
	dis[1].first=0;
	reg pii res=dis[1];
	for(int i=2;i<=cnt;++i)
		if(dis[i].first>res.first)
			res=dis[i];
	dis[res.second].first=0;
	dfs3(res.second,0);
	res=dis[1];
	for(int i=2;i<=cnt;++i)
		if(dis[i].first>res.first)
			res=dis[i];
	cout<<(res.first+1)/2<<endl;
	/*
	for(int i=1;i<=n;++i)
		cout<<idp[i]<<" ";
	*/
	return 0;
}
```



---

