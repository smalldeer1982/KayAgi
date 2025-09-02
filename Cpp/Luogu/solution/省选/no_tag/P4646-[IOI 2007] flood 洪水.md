# [IOI 2007] flood 洪水

## 题目描述

1964年的一场灾难性的洪水冲毁了萨格勒布城。洪水袭来时许多建筑的墙被彻底冲毁。在这个题目中，给定了城市在洪水来袭前的简化模型，你的任务是确定洪水过后哪些墙没有被冲毁。

简化模型由平面上的$N$个点和$W$堵墙构成。每堵墙连接两个点，没有任何一堵墙通过其它点。模型具有如下性质：

- 不存在两堵墙相交或者重合的情况，但是两堵墙可以在端点相连；
- 每堵墙或者平行于坐标系的横轴，或者平行于坐标系的纵轴。

最开始，整个坐标平面都是干的。在零时刻，洪水将城市的外围淹没（城市的外围是指没有被墙围起来的区域）。一个小时之后，所有一边是水，一边是空气的墙在水的压力下都会倒塌。于是洪水又会吞没那些没有被完好的墙围住的区域。接下来又有一些墙面临一边是水一边是空气，将要被洪水冲毁的局面。又过了一个小时，这些墙也被冲毁了。这样的过程不断重复，直到洪水淹没整个城市。

下图给出了洪水侵袭过程的一个例子。

![](https://cdn.luogu.com.cn/upload/pic/20664.png )

给定$N$个点的坐标和连接这些点的$W$堵墙的描述，编程确定洪水过后，哪些墙会被留下来。 

## 说明/提示

这个样例对应前页图中的例子。

有40分的测试点，所有坐标小于等于$500$。

在上面的测试点和另外15分的测试点中，点的个数不超过$500$个。

## 样例 #1

### 输入

```
15 
1 1 
8 1 
4 2 
7 2 
2 3 
4 3 
6 3 
2 5 
4 5 
6 5 
4 6 
7 6 
1 8 
4 8 
8 8 
17 
1 2 
2 15 
15 14 
14 13 
13 1 
14 11 
11 12 
12 4 
4 3 
3 6 
6 5 
5 8 
8 9 
9 11 
9 10 
10 7 
7 6 ```

### 输出

```
4 
6 
15 
16 
17 ```

# 题解

## 作者：xtx1092515503 (赞：5)

~~方法来自于djq神仙~~

~~对偶图什么的是不会的，这辈子都是不会的~~

我们把一个房间（**四面都有墙的极小密闭空间**）抽象成一个节点，并在由一堵墙隔开的两个房间之间连一条边。

我们把**城市外围**也抽象成一个节点。则从该节点出发，搜出到每个房间的距离。则如果一堵墙两侧的房间到城市外围的距离相等，这堵墙便不会被冲塌。

~~但是这个方法太恶心了，因为你连各个房间由哪些墙组成都很难找出~~

所以就有一种方法：

我们把一堵墙拆成两个点$i$与$i'$，分别表示墙两侧的连通块；

在每个点处，我们合并它所连接着的墙所对应的连通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/bia731x9.png)

我们将四个方向分别定为$0,2,1,3$（绿字），同时令$0$表示$i$，$1$表示$i'$（蓝字）。则我们要合并$(\color{green}{0}\color{blue}0\color{black},\color{green}{2}\color{blue}0\color{black})$、$(\color{green}{2}\color{blue}1\color{black},\color{green}{1}\color{blue}0\color{black})$、$(\color{green}{1}\color{blue}1\color{black},\color{green}{3}\color{blue}1\color{black})$、$(\color{green}{3}\color{blue}0\color{black},\color{green}{0}\color{blue}1\color{black})$。当然，也有可能一个点并不在四个方向都有墙——那也不要紧，我们就跳过缺失的墙即可。

而怎么合并呢？你可能会直观地想到并查集——但是我们可以使用**01bfs**。我们可以在合并的点之间连上一条权值为$0$的边，并在墙所拆成的两个点之间连一条权值为$1$的边，然后搜索即可。

则一堵墙可以保留，当且仅当其被拆出的两个点到起点距离相等。

最后，我们如何找到代表城市外围的点呢？

抱歉，这个方法就不太美妙了——对于原图中每个连通块，找到里面$y$最大的那堵墙，则它拆出来的某个点一定在城市外围上，找到那个点作为bfs起点即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,head[400100],cnt,dir[100100][4],to[100100][4],x[100100],y[100100],S,mxy,dis[400100],tot;
bool vis[100100];
struct edge{
	int to,next,val;
}edge[1001000];
void ae(int u,int v,int w){
//	printf("%d %d %d\n",u,v,w);
	edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
	edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=w,head[v]=cnt++;
}
int ori(int u,int v){
	if(y[u]==y[v])return x[u]>x[v];
	if(x[u]==x[v])return 2+(y[u]>y[v]);
}
void dye(int u){
	vis[u]=true;
	for(int i=0;i<4;i++){
		if(!dir[u][i])continue;
		if((i==0||i==2)&&y[u]>mxy)mxy=y[u],S=dir[u][i];
		if(!vis[to[u][i]])dye(to[u][i]);
	}
}
void bfs(){
	deque<int>q;
	q.push_back(S),dis[S]=0;
	while(!q.empty()){
		int u=q.front();q.pop_front();
//		printf("%d:%d\n",u,dis[u]);
		for(int i=head[u];i!=-1;i=edge[i].next){
			if(dis[edge[i].to]<=dis[u]+edge[i].val)continue;
//			printf("%d->%d:%d\n",u,edge[i].to,edge[i].val);
			dis[edge[i].to]=dis[u]+edge[i].val;
			if(edge[i].val)q.push_back(edge[i].to);
			else q.push_front(edge[i].to);
		}
	}
}
int main(){
	scanf("%d",&n),memset(head,-1,sizeof(head)),memset(dis,0x3f3f3f3f,sizeof(dis));
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	scanf("%d",&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
//		printf("U,V:%d V,U:%d\n",ori(u,v),ori(v,u));
		dir[u][ori(u,v)]=i,to[u][ori(u,v)]=v;
		dir[v][ori(v,u)]=i,to[v][ori(v,u)]=u;
		ae(i,i+m,1);
	}
	for(int i=1;i<=n;i++){
		vector<int>v;
		if(dir[i][0])v.push_back(0);
		if(dir[i][2])v.push_back(2);
		if(dir[i][1])v.push_back(1);
		if(dir[i][3])v.push_back(3);
		if(v.empty())continue;
		int p,q;
		for(int j=0;j+1<v.size();j++){
			p=v[j],q=v[j+1],ae(dir[i][p]+(p==1||p==2)*m,dir[i][q]+(q==0||q==3)*m,0);
		}
		p=v.back(),q=v.front(),ae(dir[i][p]+(p==1||p==2)*m,dir[i][q]+(q==0||q==3)*m,0);
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		S=0,mxy=-1;
		dye(i);
		if(S)bfs();
	}
	for(int i=1;i<=m;i++)tot+=(dis[i]==dis[i+m]);
//	for(int i=1;i<=2*m;i++)printf("%d:%d\n",i,dis[i]);
	printf("%d\n",tot);
	for(int i=1;i<=m;i++)if(dis[i]==dis[i+m])printf("%d\n",i);
	return 0;
} 

```


---

## 作者：FZzzz (赞：3)

~~踩一下下面那篇题解，这啥嘛根本啥都没讲，建议管理员撤下来。~~

~~我要膜拜 djq。~~

这题你可以发现输入的是个平面图，然后他在这个平面上的表现形式是一个 PSLG（平面直线区域，是叫这个名字吧？）。所以你可以直接套 PSLG 的算法找出每个面，然后建出这个图的对偶图。然后以最外面的无限面为源点跑个 bfs，两边距离相等的边就是保留下来的。

然后我并不会 PSLG。~~对于 dls 这种神仙来说就是懒得写。~~

所以我们考虑比较简单的做法：一个边可能会把平面分成两个区域对吧，所以我们对于一个边我们建两个点，表示这个边两侧的两个区域。这两个区域连一条权值为一的边。然后对于原图中的每个点，你可以通过对他边数的讨论得到某些区域其实是同一个区域。对于可以确定是同一个区域的两个区域，就连一条权值为零的边，这样就缩起来了。

最后跑 01bfs 即可。

但是这有两个问题：

如何找到最外面的区域代表的点呢，就是你可以去找到横坐标最小的点，如果有多个就选纵坐标最小的那个，然后最外面的区域一定就是它上面的边左边的区域，或者它右边的边下面的区域。

然而这个做法对于原图不联通的情况会炸，赛时卡在这里了。解决方法非常 naive，对于每个连通块分别做就可以了。同时这个解决方法也能解决一个大的里面套了一个小的的情况。

然后就做完了。

代码太丑不放了。

---

## 作者：tzc_wk (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P4646)

一道挺有意思的题（？）

~~orz djq yyds %%%%%%%%%%%%%%%%%%~~

首先一个很直观的想法是将每个房间看作一个节点，在有墙的房间旁边连边权为 $1$ 的边然后 bfs，不过这样实现不太方便，最终也无法较直接地判断每堵墙是否被摧毁，因此这里（djq）提供了一个比较简单的方法。

我们将每堵墙拆成两个点 $i$ 和 $i+m$ 分别表示这堵墙分隔的两个区域，我们在这两个点之间连边权为 $1$ 的边，而显然有的区域表示的是同一个房间，因此我们还要在它们之间连边权为 $0$ 的边。具体来说，对于每个点而言会连出一些边，假设个数为 $c$，那么这个点引出的这些边就将平面分成了 $c$ 个部分，而这些边总共对应着 $2c$ 个点，因此总共会有 $c$ 对点表示的是同一个区域，而这些表示相同区域的点表示的射线显然是相邻的，因此我们对于每个点开一个 `vector` 按顺序记录它连出的边的编号，然后扫一遍在相邻的边表示的区域之间连边，并根据方向判断是 $i$ 还是 $i+m$，这样即可实现缩点（u1s1 这一段可能讲得不是特别明白，具体看代码罢）

缩完点之后找出表示外层区域的点，这个可以暴力通过对于每个区域进行一遍 DFS 找出纵坐标最大（当然横坐标也行）的边，那么它上方的区域表示的点就是表示最外侧区域的点，由于此题边权只涉及 $0/1$，因此进行 01 bfs 即可求出到每个区域的最短距离。

时间复杂度线性。

```cpp
const int MAXN=1e5;
const int MAXM=2e5;
const int MAXV=4e5;
const int MAXE=2e6;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
int n,m,x[MAXN+5],y[MAXN+5],id[MAXN+5][4],dr[MAXN+5][4];
int sgn(int x){return (x>0)?1:((!x)?0:-1);}
int direc(int a,int b){for(int i=0;i<4;i++) if(sgn(x[b]-x[a])==dx[i]&&sgn(y[b]-y[a])==dy[i]) return i;}
int hd[MAXV+5],to[MAXE+5],nxt[MAXE+5],val[MAXE+5],ec=0;
void adde(int u,int v,int w){/*printf("%d %d %d\n",u,v,w);*/to[++ec]=v;val[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
int my,ids;bitset<MAXN+5> vis;
void dfs(int t){
	if(vis[t]) return;vis.set(t);for(int i=0;i<4;i++) if(id[t][i]){
		dfs(dr[t][i]);if((i==0||i==2)&&y[t]>my) my=y[t],ids=id[t][i]+m;
	}
}
int dis[MAXV+5];
void bfs(int s){
	deque<int> q;dis[s]=0;q.push_back(s);
	while(!q.empty()){
		int x=q.front();q.pop_front();//printf("%d\n",x);
		for(int e=hd[x];e;e=nxt[e]){
//			printf("edge %d\n",e);
			int y=to[e],z=val[e];
//			printf("%d %d\n",y,z);
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				(!z)?(q.push_front(y)):(q.push_back(y));
			}
		}
	}
//	for(int i=1;i<=m<<1;i++) printf("%d %d\n",i,dis[i]);
}
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	scanf("%d",&m);for(int i=1;i<=m;i++){
		int a,b;scanf("%d%d",&a,&b);
//		printf("%d %d\n",direc(a,b),direc(b,a));
		id[a][direc(a,b)]=id[b][direc(b,a)]=i;
		dr[a][direc(a,b)]=b;dr[b][direc(b,a)]=a;
		adde(i,i+m,1);adde(i+m,i,1);
	} memset(dis,63,sizeof(dis));
	for(int i=1;i<=n;i++){
//		printf("Vert %d\n",i);
		vector<int> d;
		for(int j=0;j<4;j++) (id[i][j]&&(d.pb(j),0))/*,printf("%d %d\n",j,id[i][j])*/;
		if(!d.empty()){
			d.pb(d[0]);//printf("%d\n",d.size());
			for(int j=0;j+1<d.size();j++){
				int a=d[j],b=d[j+1];
//				printf("%d %d\n",id[i][a],id[i][b]);
				adde(id[i][a]+m*(a==0||a==3),id[i][b]+m*(b==1||b==2),0);
				adde(id[i][b]+m*(b==1||b==2),id[i][a]+m*(a==0||a==3),0);
			}
		}
	} vector<int> ans;
	for(int i=1;i<=n;i++) if(!vis[i]){my=-1;ids=0;dfs(i);bfs(ids);}
	for(int i=1;i<=m;i++) if(dis[i]==dis[i+m]) ans.pb(i);
	printf("%d\n",ans.size());for(int i=0;i<ans.size();i++) printf("%d\n",ans[i]);
	return 0;
}
```



---

