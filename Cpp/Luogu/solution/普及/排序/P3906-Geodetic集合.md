# Geodetic集合

## 题目描述

图 $\text G$ 是一个无向连通图，没有自环，并且两点之间至多只有一条边。我们定义顶点 $v,u$ 的最短路径就是从 $v$ 到 $u$ 经过边最少的路径。所有包含在 $v-u$ 的最短路径上的顶点被称为 $v-u$ 的 Geodetic 顶点，这些顶点的集合记作 $I(v,u)$。

我们称集合 $I(v,u)$ 为一个 Geodetic 集合。

例如下图中，$I(2,5)=\{2,3,4,5\}$，$I(1,5)=\{1,3,5\}$，$I(2,4)=\{2,4\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/26c7a19d.png)

给定一个图 $\text G$ 和若干点对 $v,u$，请你分别求出 $I(v,u)$。

## 说明/提示

对于所有数据，满足 $1\leqslant n\leqslant 40$，$1\leqslant m\leqslant \frac{n(n-1)}2$。

## 样例 #1

### 输入

```
5 6
1 2
1 3
2 3
2 4
3 5
4 5
3
2 5
5 1
2 4```

### 输出

```
2 3 4 5
1 3 5
2 4```

# 题解

## 作者：06ray (赞：44)

### 这道题算是一个最短路的水题了，然而难度是提高+/省选-？

先说说这题的思路：
1. 先读入一个图的顶点数n和边数m，再读入每个边的信息（起点，终点），把它们存储起来，这里我用的邻接表存储法（当然也可以用邻接矩阵存储）。
1. 接下来开始读入问题（也是整个程序的核心），读入v,u。先用spfa单源最短路径算出v点到其他点的最短距离，用d数组存储（SPFA模板不阐述）。然后再用spfa算出u点到其他点的最短距离，用d2数组存储。算完最短距离后开始遍历每个点，如果这个点到v的最短路径加上这个点到u的最短路径恰好等于v到u的最短距离，那么就输出这个点的编号。

思路就这么多，十分简单。

下面有请可爱的代码君上场qwq

### 注意:减少代码复制，共创美好洛谷！

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cstdio>
#include <cstring>  //头文件 
using namespace std;
struct node{
    int to,cost;
};
vector<node> G[110];//vector数组，邻接表存储 
int d[110],d2[110];//d数组存的是v点到其他点的最短距离，d2数组存的是u点到其他点的最短距离 
bool used[110];
int n,m,x;
stack<int>s;
inline int read()//读入优化 
{
    int n=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    while(ch>='0'&&ch<='9')
     {
         n=n*10+ch-'0';
         ch=getchar();
     }
    return n; 
}
void spfa(int s)//SPFA模板 
{
    queue<int>q;
    fill(d+1,d+n+1,100000000);//一开始要初始化一个很大的数 
    fill(used+1,used+n+1,false);
    d[s]=0;
    used[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        used[v]=false;
        for(int i=0; i<G[v].size(); i++)
        {
            node e=G[v][i];
            if(d[v]+e.cost<d[e.to])
            {
                d[e.to]=d[v]+e.cost;
                if(!used[e.to])
                {
                    q.push(e.to);
                    used[e.to]=true;
                }
            }
        }
    }
}
void spfa2(int s)//同样是模板 
{
    queue<int>q;
    fill(d2+1,d2+n+1,100000000);
    fill(used+1,used+n+1,false);
    d2[s]=0;
    used[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        used[v]=false;
        for(int i=0; i<G[v].size(); i++)
        {
            node e=G[v][i];
            if(d2[v]+e.cost<d2[e.to])
            {
                d2[e.to]=d2[v]+e.cost;
                if(!used[e.to])
                {
                    q.push(e.to);
                    used[e.to]=true;
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);//读入 
    for(int i=1; i<=m; i++)
    {
        int a,b,c;
        a=read(),b=read();//读入 
        G[a].push_back((node){b,1});//邻接表存储法，注意权值要为1 
        G[b].push_back((node){a,1});
    }
    int q;
    cin>>q;//读入问题的数量 
    while(q--)
    {
    	int v,u;
    	cin>>v>>u;
    	spfa(v);
    	spfa2(u);//SPFA大法好 
    	for(int i=1; i<=n; i++)
    	if(d[i]+d2[i]==d[u]) cout<<i<<' ';//如果第i点到v的最短路径加上到u的最短路径恰好等于d[u]，那么就输出i
    	cout<<endl;//换行 
    }
    return 0;//就这样完美的结束 
}

```

p.s 本人蒟蒻一枚，如果此题解有地方说的不好或是说错了，请在评论区告诉错误原因，谢谢！如果您认为这篇题解不错，就请话1秒钟的时间点个赞吧！

---

## 作者：かなで (赞：19)

emm.....怎么题解几乎全是 $Floyd$....

这里给出一个 $BFS$ 做法 ~~什么？无权图你用 SPFA ？~~

思路很简单的...就是在求最短路的过程中记录一下当前点的前驱

由于前驱珂能有多个，所以开二维数组存储

然后从终点倒着搜一遍就得到答案了

由于 $n$ 很小，所以也懒得写邻接表了qwq

时间复杂度 $O(kn^2)$，用邻接表的话是 $O(k(n+m))$

貌似比 $Floyd$ 做法快一点？~~然而并没给 k 的范围~~

代码：（也不比 $Floyd$ 难写多少qwq）

```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int>q;
bool ans[41];
int a[41][41],pre[41][41],num[41],dis[41],n;
void bfs(int s,int t){
	memset(num,0,sizeof num),memset(dis,63,sizeof dis);  //  忘了清数组会爆0
	dis[s]=0,q.push(s);
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=1;i<=n;i++) if(a[s][i])
			if(dis[i]>dis[s]+1)
				dis[i]=dis[s]+1,pre[i][++num[i]]=s,q.push(i);
			else if(dis[i]==dis[s]+1) pre[i][++num[i]]=s;  //  分情况记录前驱
	}
	memset(ans,0,sizeof ans),q.push(t),ans[t]=1;
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=num[s];i;i--) if(!ans[pre[s][i]])
			ans[pre[s][i]]=1,q.push(pre[s][i]);  //  倒着搜回去
	}
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
}
int main(){
	int m,q,x,y;
	scanf("%d%d",&n,&m);
	while(m--) scanf("%d%d",&x,&y),a[x][y]=1,a[y][x]=1;
	scanf("%d",&q);
	while(q--) scanf("%d%d",&x,&y),bfs(x,y),putchar('\n');
	return 0;
}
```

---

## 作者：_Blue_ (赞：6)

### 说实话，真不知道这题是怎么成蓝题的
~~之前一直觉得Floyd的时间复杂度太高就没学，然后就没学~~  
### 具体思路就是跑一遍**Floyd**，求出任意两点间的距离（到这里实际上就是**Floyd**的模板）  
然后我们对于给定的两点，枚举中间点，然后...  
呃呃呃，具体看代码吧：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,T;
priority_queue<int,vector<int>,greater<int> > q; 
// 优先对列，便于后面的节点排序
// 实际拿个数组，sort一遍也行，可能更高效（雾
int f[44][44];
int main(){
	scanf("%d%d",&n,&m);
	memset(f,999999,sizeof(f));
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		f[x][y]=1;
		f[y][x]=1;
	}
    //Floyd模板求两点最短路
	for(int k=1;k<=n;k++){
		for(int j=1;j<=n;j++){
			for(int i=1;i<=n;i++){
				if(i==j||i==k||j==k) continue;
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
				f[j][i]=min(f[j][i],f[j][k]+f[k][i]);
			}
		}
	}
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		int x,y;scanf("%d%d",&x,&y);
		q.push(x);q.push(y); //起点和终点入对列
		for(int k=1;k<=n;k++){
			if(k==x||k==y) continue;
			if(f[x][y]==f[x][k]+f[k][y])  
            /*
			重点！
			如果中间点k到起点和终点的距离等与起点到终点的最短距离，那么这个节点就在最短路上
			我们就可以将k点入队列 
		*/
			q.push(k);
		}
		while(!q.empty()){
			cout<<q.top()<<" ";
			q.pop();
		}
		cout<<endl;
	}
}  
```

  
  
综上所述，这是该是黄题 
qwq

---

## 作者：旭日临窗 (赞：5)

## 这里发一下Dijkstra + 优先队列 + 链式前向星的做法。

-  先说一下**思路**：
先用Dijkstra跑一遍u的最短路，用dis1数组储存，然后再跑一遍v的最短路，用dis2数组储存，最后遍历每一个点，如果**dis1[ i ] + dis2[ i ] 等于 dis1[ v ]**，就把点 i 放进我们的集合里。

-  **理由**：
因为如果点u到点i的最短路和点v到点i的最短路相加的和等于点u到点v的最短路，就说明点i是点u到点v的最短路的一部分，所以点i也就是是我们要的集合中的一部分。

- code:


```c
#include <bits/stdc++.h>
using namespace std;
const int inf = 0x7f7f7f7f;
struct node
{
	int x,w;
	node(){}//这是构造函数。 
	node(int _x,int _w) : x(_x),w(_w){}
	bool operator < (const node &s) const//这里注意要重载小于号 。 
	{
		return w > s.w;
	}
};
struct Edge//链式前向星 。 
{
	int to,next;
}edge[20010];
int n,m,cnt,k,u1,v1,head[100],ans[100];//ans是答案集合 。 
int dis[100],dis2[100];
void add(int u,int v)//加边 。 
{
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}
void bfs1()//跑一遍u的最短路 。 
{
	bool vis[100];
	priority_queue <node> q;
	memset(dis,inf,sizeof(dis)),memset(vis,0,sizeof(vis));
	q.push(node(u1,0));//应为有了上面的构造函数，所以就可以直接这样写了。 
	dis[u1] = 0;
	while(!q.empty())//最短路的模板 。 
	{
		int u = q.top().x;q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u];~i;i = edge[i].next)
		{
			int v = edge[i].to;
			if(!vis[v] && dis[u] + 1 < dis[v])
			{
				dis[v] = dis[u] + 1;
				q.push(node(v,dis[v]));
			}
		}
	}
}
void bfs2()//再跑一遍v的最短路 。 
{
	priority_queue <node> q;
	bool vis[100];
	memset(dis2,inf,sizeof(dis2)),memset(vis,0,sizeof(vis));
	q.push(node(v1,0));
	dis2[v1] = 0;
	while(!q.empty())
	{
		int u = q.top().x;q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u];~i;i = edge[i].next)
		{
			int v = edge[i].to;
			if(!vis[v] && dis2[u] + 1 < dis2[v])
			{
				dis2[v] = dis2[u] + 1;
				q.push(node(v,dis2[v]));
			}
		}
	}
}
int main()
{
	memset(head,-1,sizeof(head));//预处理head数组的初始值 。 
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v);//注意是双向边 。 
		add(v,u);
	}
	scanf("%d",&k);
	while(k--)
	{	
		cnt = 0;
		memset(ans,0,sizeof(ans));
		scanf("%d%d",&u1,&v1);
		bfs1();
		bfs2();
		for(int i = 1;i <= n;i++)
		if(dis[i] + dis2[i] == dis[v1])//如果满足要求就加进ans数组中 。 
		ans[++cnt] = i;
		for(int i = 1;i <= cnt;i++) printf("%d ",ans[i]);
		puts("");
	}
	return 0;//养成好习惯，结束程序。 
} 
```
/* 希望管理员大大能给个过，thanks。*/

---

## 作者：GK0328 (赞：5)

感谢逝星DS的指正

今天早上刷图论，正好做到这道题，来写一波题解。。。

刚看题目，看到是最短路，有多组询问，显然是多源最短路。Floyd！！！

又想到了NOIP2012文化之旅的Floyd写法，突然有了灵感，一把AC了。。。

让我们来讲一讲解法：

首先，题目让我们输出的是从u到v的最短路集合，所以Floyd需要另开一个g数组，数组开三维，用Bool类型储存，记录I（u，v）。

让我们再次定义一下变量：

**f[i][j]表示从i到j的最短路径。**

**g[i][j][k]表示从i到j的最短路集合，g[i][j][k]=true表示k属于这个集合中,g[i][j][k]=false表示k不属于这个集合。**

现在开始循环：-------->

**当f[i][j]>f[i][k]+f[k][j]时，说明g数组需要被完全重新更改（因为存在更优解）枚举t从1到n，g[i][j][t]=g[i][k][t] or （|） g[j][k][t]（之要两个集合中任意一个存在t，那么g[i][j]集合也存在t）。**

当f[i][j]<f[i][k]+f[k][j]时，不用更改（~~这岂不是废话~~）。

**当f[i][j]=f[i][k]+f[k][j]时，说明g数组需要在原来的基础上新加入两个集合（因为原来的集合和现在的集合都属于当前的最短路集合），那么转移方程很容易出来了，g[i][j][t]=g[i][j][t] or g[i][k][t] or g[k][j][t]（~~
显然~~）。**

时间复杂度：O（n^4）

运行时间：4ms

上Pascal代码：（~~好像忘记跟你们说了我是P党~~）：

```cpp

// luogu-judger-enable-o2//O2优化。。。
var
  f:array[0..50,0..50]of int64;//f[i][j]表示从i到j的最短路径。
  g:array[0..50,0..50,0..50]of boolean;//g[i][j][k]表示从i到j的最短路集合，g[i][j][k]=true表示k属于这个集合中,g[i][j][k]=false表示k不属于这个集合。
  n,m,i,j,k,t,q,x,y:longint;
  inf:int64;
begin
  readln(n,m);
  inf:=100000000007;
  for i:=0 to n do
    for j:=0 to n do
      f[i][j]:=inf;//赋初值
  for i:=1 to m do
  begin
    readln(x,y);
    f[x][y]:=1;//更新
    f[y][x]:=1;//更新
    g[x][y][x]:=true;//在x到y的路径集合中一定存在x和y，下同
    g[x][y][y]:=true;
    g[y][x][x]:=true;
    g[y][x][y]:=true;
  end;
  for k:=1 to n do//Floyd必须先枚举中转站
    for i:=1 to n do
      for j:=1 to n do
        if (i<>j) and (j<>k) and (i<>k) then//我好想还是不清楚为什么要写这句话，求大佬的解释。
        begin
          if f[i][k]+f[k][j]<f[i][j] then//完全更新
          begin
            f[i][j]:=f[i][k]+f[k][j];//更新最短路
            for t:=1 to n do//枚举t
              g[i][j][t]:=g[i][k][t] or g[k][j][t];
          end else
          if f[i][k]+f[k][j]=f[i][j] then//出现更多的最短路
          begin
            for t:=1 to n do//枚举t
              g[i][j][t]:=g[i][j][t] or g[i][k][t] or g[k][j][t];
          end;
        end;
  readln(q);
  for i:=1 to q do
  begin
    readln(x,y);
    for j:=1 to n do
      if g[x][y][j] then//直接输出该集合
        write(j,' ');
    writeln;
  end;
end.
```

---

## 作者：Ginger_he (赞：4)

# 题目描述
定义 $I(v,u)$ 为 $v$ 到 $u$ 最短路上的点的集合。给定图 $G$ 和若干点对 $(v,u)$，求出 $I(v,u)$。
# 题解
- 这题既可以用 floyd，也可以用 spfa (其实就是 bfs)，但是出于我对 STL 的喜爱，我选择了后者。
- 对于每一个点对 $(v,u)$，首先求出 $v$ 到 $u$ 的最短路，并记录在 $t$ 中；再求出 $u$ 到 $v$ 的最短路，并记录在 $dis$ 中。**若对于一个点 $i$ 满足，$v$ 到 $i$ 的最短路加上 $i$ 到 $u$ 的最短路等于 $v$ 到 $u$ 的最短路，则 $i$ 在 $I(v,u)$ 中。**
## 例子
![](https://cdn.luogu.com.cn/upload/image_hosting/q10wob6h.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如上图，$1$ 到 $2$ 的最短路为 $1$，$2$ 到 $4$ 的最短路为 $1$，$1$ 到 $4$ 的最短路为 $2$，$d_{1->2}+d_{2->4}=d_{1->4}$，所以 $2$ 在 $I(1,4)$ 中。同理，$1,3,4$ 也在集合中。
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,k,dis[50],t[50];
bool vis[50];
vector<int> g[50];
queue<int> q;
void spfa(int s)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,false,sizeof(vis));
    q.push(s);
    dis[s]=0;
    vis[s]=true;
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        vis[tmp]=false;
        for(int i=0;i<g[tmp].size();i++)
        {
            if(dis[tmp]+1<dis[g[tmp][i]])
            {
                dis[g[tmp][i]]=dis[tmp]+1;
                if(!vis[g[tmp][i]])
                {
                    vis[g[tmp][i]]=true;
                    q.push(g[tmp][i]);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }//存图
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d%d",&a,&b);
        spfa(a);//a的最短路
        memcpy(t,dis,sizeof(t));//复制到t数组
        spfa(b);//b的最短路
    	for(int i=1;i<=n;i++)
    	{
    		if(dis[i]+t[i]==t[b])//核心代码
    			printf("%d ",i);
		}
		printf("\n");
    }
    return 0;
}
```

---

## 作者：newbie666 (赞：4)

## 邻接矩阵+Floyd

1. 我们首先看一下数据范围，顶点数居然是不大于 $40$！于是便很容易猜想到 Floyd 算法，再来看一下此题是否为多源最短路径。

2. 首先从题意出发，它是让我们求给定**任意两点之间**的所有最短路顶点编号，所以可以证明上文的猜想，故此题跑 Floyd。

## Code:
```cpp
#include<bits/stdc++.h>
#define SIZE 105
using namespace std;
int n,m,dis[SIZE][SIZE]; //dis[i][j]数组是两点之间的最短距离. 
void Floyd(){
	for(register int k=1;k<=n;k++){ //把前k个点都当作可用的中转点.
		for(register int i=1;i<=n;i++){ //i 起点.
			for(register int j=1;j<=n;j++){ //j 终点. 
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //松弛操作(如果存在比你更小的值就更新,维护最小值). 
			}
		}
	}
	return;
}
int main(){
	std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			dis[i][j]=(i==j)?0:1e9; //初始化，默认自己到自己距离为0，到其他点赋值极大值. 
		}
	}
	for(register int i=1;i<=m;i++){
		int a,b; cin>>a>>b;
		dis[a][b]=dis[b][a]=1; //此题是无向图，1表示a、b之间存在一条边. 
	}
	Floyd();
	int k; cin>>k;
	while(k--){
		int v,u; cin>>v>>u;
		for(register int i=1;i<=n;i++){
			if(dis[v][i]+dis[i][u]==dis[v][u]){ //满足条件，输出答案. 
				cout<<i<<' ';
			}
		}
		cout<<'\n';
	}
	return 0;
}
```
祝大家学习顺利！

---

## 作者：Darkmaster (赞：4)

【本人第一篇题解】

   说实话，这道题真的挺水的，因为点数n特别小，<=40，所以说我们不妨用 Floyd (Floyd万岁！！！),并且也不用判断重边

   先用Floyd算法算出任意两点之间的距离;对于要求的任意两个点v, u，枚举所有点如果满足：f[v][j]+f[j][u]=f[v][u],输出j
   
   下面给出蒟蒻的代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,t,f[50][50],v,u;

int main()
{
	memset(f,10,sizeof(f));
	scanf("%d %d",&n,&m);    //输入不说
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		f[x][y]=f[y][x]=1;
	}
	for(int i=1;i<=n;i++) f[i][i]=0;
	for(int k=1;k<=n;k++)            //Floyd
	    for(int i=1;i<=n;i++)
	        for(int j=1;j<=n;j++)
	            f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d %d",&v,&u);
		for(int j=1;j<=n;j++)
		    if(f[v][j]+f[j][u]==f[v][u]) printf("%d ",j);      //枚举j
		printf("\n");
	}
	return 0;
}
```

---

## 作者：樱花飞舞 (赞：2)

其实这题搜索就行了，当然不是简单的搜索。

这题有两个难点
1. 如何确定步数。
2. 如何记录和输出路径。

用迭代加深和set&deque就行了~

```cpp
#include<cstdio>
#include<algorithm>
#include<deque>
#include<cstring>
#include<set>
struct MyStruct{
	int x,y,next;
}a[40*40+5];
int len=0, n, m, k, last[45];
bool v[45];
std::deque<int> q;
std::set<int> set;
void ins(int x,int y)
{
	len++;
	a[len].x=x;
	a[len].y=y;
	a[len].next=last[x];
	last[x]=len;
}
bool dfs(int m, int x, int step, int end)
{
	if(step > m)
	{
		return 0;
	}
	if(x == end)
	{
		for(std::deque<int>::iterator i = q.begin();i!=q.end();i++)
		{
			set.insert((*i));
		}
		return 1;
	}
	bool flag = 0;
	for(int i = last[x];i;i = a[i].next)
	{
		const int y = a[i].y;
		if(v[y] == 0)
		{
			v[y] = 1;
			q.push_back(y);
			if(dfs(m,y,step+1, end) == 1)
				flag = 1;
			q.pop_back();
			v[y] = 0;
		}
	}
	return flag;
}
void go(int start,int end)
{
	if(start == end)
	{
		printf("%d", start);
		return;
	}
	set.clear();
	for(int i=1;i<=40;i++)
	{
		q.clear();
		memset(v,0,sizeof(v));
		q.push_back(start);
		v[start] = 1;
		if(dfs(i, start,0,end) == 1)
		{
			break;
		}
	}
	std::set<int>::iterator i;
	size_t tmp=0;
	for(i = set.begin();i!=set.end();i++)
	{
		tmp++;
		if(tmp == set.size())
			printf("%d\n",(*i));
		else printf("%d\x20",(*i));
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1, x, y;i<=m;i++)
	{
		scanf("%d %d",&x,&y);
		ins(x, y);
		ins(y, x);
	}
	scanf("%d", &k);
	for(int i=1, start,end;i<=k;i++)
	{
		scanf("%d %d",&start, &end);
		go(start,end);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

# 一道水题

这么水的一道蓝题没人写$dijkstra$？

竟然都用的是复杂度为$O(n^3)$的$Floyd$！

蒟蒻便来打起$dijkstra$的大旗。

---
**主体思路**：

将每个边的边权设为$1$，

对于第$i$次询问，

以$v_i$为起点跑一边最短路，将答案存在数组$d1[\space]$中，再以$u_i$为起点跑一边最短路，将答案存在$d2[\space]$中。

最后，再枚举$1$~$V$各个顶点，

对于第$k$个点，如果$d1_k+d2_k=d1_v$，那么，$k$号节点便为目前$Geodetic$集合的一个元素，并输出。

---

$Code:$

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=50;
int n,m,k,d1[MAXN],d2[MAXN];
//n个点，m条边，k次询问，d1和d2已经讲得很清楚了。 
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
//快读，一是可以装星，二是可以让代码更快些（其实也快不了多少 
struct edge
{
	int to,cost; 
};
vector<edge>G[MAXN];
//用vector存图（我这种蒟蒻只会vector了…… 
typedef pair<int,int>P;
//定义pair类型的P，可供装星 
void dijkstra(int s)
//第一次dijkstra 
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d1[i]=1e9;
	d1[s]=0;
	q.push(P{0,s});
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(d1[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d1[e.to]>d1[v]+e.cost)
			{
				d1[e.to]=d1[v]+e.cost;
				q.push(P{d1[e.to],e.to});
			}
		}
	}
}
void dijkstra2(int s)
//第二次dijkstra 
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d2[i]=1e9;
	d2[s]=0;
	q.push(P{0,s});
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(d2[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d2[e.to]>d2[v]+e.cost)
			{
				d2[e.to]=d2[v]+e.cost;
				q.push(P{d2[e.to],e.to});
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	while(m--)
	{
		int u=read(),v=read();
		G[u].push_back(edge{v,1});
		G[v].push_back(edge{u,1});
		//一定要存双向边！ 
	}
	k=read();//k次询问 
	while(k--)
	{
		int s=read(),t=read();
		dijkstra(s);
		dijkstra2(t);
		for(register int k=1;k<=n;k++) if(d1[k]+d2[k]==d1[t]) printf("%d ",k);
		//公式 
		printf("\n");
		//别忘换行 
	}
	return 0;//养成好习惯
	//完结撒花~~~ 
} 
```
---

这道题总体来说还是很水的，应该是一个黄题的难度。

看蒟蒻我写得这么认真，可不可以点个赞再走呢？

---

## 作者：羽儇 (赞：1)


------------

$Solution$

如果某一点i在边(u,v)最短路上则$dis[u][i] + dis[i][v] = dis[u][v]$

1、先以u为起点搜一遍，求$dis1[i]$,即起点u到每一点的距离，即求出$dis[u][i]$

2、先以v为起点搜一遍，求$dis2[i]$,即起点v到每一点的距离，即求出$dis[v][i]$也就是$dis[i][v]$

3、最后，枚举点，看是否在最短路上

------------


$AC code $呈上（~~码风珂还行？~~）
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#define maxn 1600
#define inf 0x3f3f3f3f
using namespace std;
struct node 
{
	int to,next;
}edge[maxn<<1];
int head[maxn<<1],tot,N,M,K,dis1[maxn],dis2[maxn];
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int > > >q;
void add_edge(int u,int v){edge[++tot] = (node){v,head[u]};head[u]=tot;}
void Dijkstra(int st,int *dis)
{
	for(int i = 1 ;i <= N;i ++)dis[i] = inf;
	dis[st] = 0;q.push(make_pair(0,st));
	while(!q.empty())
	{
		pair<int,int> t = q.top();q.pop();int u = t.second;
		if(dis[u] != t.first)continue;
		for(int i = head[u]; i ; i = edge[i].next)
		{
			int v = edge[i].to;
			if(dis[v] > dis[u] + 1)
			dis[v] = dis[u] + 1 , q.push(make_pair(dis[v],v));
		}
	}
	return ;
}
int main()
{
	int u,v;
	scanf("%d%d",&N,&M);
	for(int i = 1; i <= M; i ++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	scanf("%d",&K);
	while(K--)
	{
		scanf("%d%d",&u,&v);
		Dijkstra(u,dis1);
		Dijkstra(v,dis2);
		for(int i = 1 ;i <= N; i ++)
		if(dis1[i] + dis2[i] == dis1[v])printf("%d ",i);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Marginal_world (赞：0)

问题分析：重点在于可能存在多个点满足路径最短，所以只跑一遍最短路行不通或者说需要处理。

解决方法:弗洛伊德大法好。由于数据范围的限制，本题可以用代码量相对较少且不易出错的弗洛伊德解决。由于弗洛伊德是任意两点之间的最短路，所以只要满足起点到终点的最短距离等于起点先到中间点再从中间点到终点的最短距离相等，就可以将这个中间点计入答案，可能存在多个符合条件的中间点。

这就体现了弗洛伊德的优势所在，在数据范围允许的情况下，它的代码量较少，使用相对方便。

总结：本题应该说是最短路的变形，适合作为最短路新学者练习算法，熟悉算法之间的优势与缺点。


代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[50][50];
int n,m,k;
void Floyd(){//弗洛伊德模板
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)//无向图的一个常数级优化
	if(dis[i][j]>dis[i][k]+dis[k][j])
	dis[i][j]=dis[j][i]=dis[i][k]+dis[k][j];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	dis[i][j]=999999999;//赋初值
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		dis[u][v]=dis[v][u]=1;
	}
	for(int i=1;i<=n;i++)dis[i][i]=0;//自己到自己当然是0
	Floyd();
	cin>>k;
	while(k--){
		int a,b;
		cin>>a>>b;
		for(int i=1;i<=n;i++)
		if(dis[a][b]==dis[a][i]+dis[i][b])//点集合判定
		cout<<i<<" ";
		cout<<endl;
	}
	return 0;
}
```

希望能帮助到大家。谢谢！

---

## 作者：xkcdjerry (赞：0)

~~先吐槽一下这么水的题怎么上蓝的~~  
看到数据范围 $ n \leqslant 50 $ 果断想到 Floyd ，一遍跑完之后得到所有点之间的相互距离，不妨称之为 $f$ 。  
然后考虑对于点对 $a,b$ ，假如存在点 $i$ 使得 $f_{a,i}+f_{i,b}=f_{a,b}$ ，那么从 $a$ 走到 $i$ 然后走到 $b$ 和直接从 $a$ 走到 $b$ 一样长，即 $i$ 在 $a$ 到 $b$ 的最短路上。  

所以跑完 Floyd 之后对于每次询问只要**从小到大**枚举 $i$ 即可。

时间复杂度： $O(n^3+nk)=O(n^3)$  

Floyd 相比 bfs 的好处：
* 代码量略小
* 可以处理边权不等于1的情况

Floyd 相比 SPFA 的好处：
* 代码量明显小
* SPFA 可以被卡到 $O(nmk)$ 即 $O(n^3k)$ ， Floyd 时间复杂度较稳定。 ~~但是这道题 $n$ 特小所以没关系~~

蒟蒻的代码：
```cpp
#include <cstdio>
#include <vector>
#define INF 0x3f3f3f3f
using std::vector;
#define N 50
int n,m;
int f[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=i==j?0:INF;
    while(m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        f[u][v]=f[v][u]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(f[i][k]+f[k][j]<f[i][j])
                    f[i][j]=f[i][k]+f[k][j];
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;i++)
            if(f[a][i]+f[i][b]==f[a][b]) printf("%d ",i);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：JWRuixi (赞：0)

- 这道题用 Dijkstra 堆优化 + 链式前向星 即可
- Dijkstra 有实用性强，代码速度稳定，不容易被卡的优点。

- 所以话不多说，直接说一下 Dijkstra 的思路：用模板 Dijkstra 先跑一遍起点 $u$ 和终点 $v$，用两个数组 dis 和 dist 分别存最短路长度。遍历每一个点，如果对于点 $i$，如果 $dis[i] + dist[i] = dis[v]$（或 dist[u]），则将 $i$ 点加入集合中。最后按顺序输出即可。

- code：

```
#include <bits/stdc++.h>
#define maxn 200
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}
inline void write(int x) {
   if (x < 0) {
       x = ~(x - 1);
       putchar('-');
   }
   if (x > 9) 
       write(x / 10);
   putchar(x % 10 + '0');
}//快读快输
struct edge {
	int to, nxt;
}e[4000005];//用链式前向星存图
struct node {
	int u, cur;
	inline bool operator < (const node &x) const {//重载运算符<维护堆
		return cur > x.cur;
	}
};
int n, m, head[maxn], dis[maxn], dist[maxn], k, s, t, p;
priority_queue <node> q;
priority_queue <int, vector <int>, greater<int>> ans;//ans 即答案集合
bool vis[maxn];
inline void add (int u, int v) {
	e[++k].to = v;
	e[k].nxt = head[u];
	head[u] = k;
}//链式前向星加边，k 从1起
inline void dijkstra () {
	for (int i = 1; i <= n; i++) dis[i] = 2147483647;
	dis[s] = 0;
	q.push((node){s, 0});//加入起点
	while (!q.empty()) {
		int u = q.top().u;//取出起点
		if (vis[u]) continue;//判重
		for (int i = head[u]; i; i = e[i].nxt) {//链式前向星遍历所有边
			int v = e[i].to;
			if (vis[v]) continue;
			if (dis[v] > dis[u] + 1) {//如果能松弛
				dis[v] = dis[u] + 1;
				q.push((node){v, dis[v]});//松弛，v 点入队
			}
		}
		q.pop();
		vis[u] = 1;//更新队列和标记
	}
}
//从起点 u 做 Dijkstra 遍历
inline void dijkstra1 () {
	for (int i = 1; i <= n; i++) dist[i] = 2147483647;
	dist[t] = 0;
	q.push((node){t, 0});
	while (!q.empty()) {
		int u = q.top().u;
		if (vis[u]) continue;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (vis[v]) continue;
			if (dist[v] > dist[u] + 1) {
				dist[v] = dist[u] + 1;
				q.push((node){v, dist[v]});
			}
		}
		q.pop();
		vis[u] = 1;
	}
}//从终点v遍历
int main () {
	n = read(), m = read();
	for (int i = 0; i < m; i++) {
		int u = read(), v = read();
		add (u, v);
		add (v, u);
	}//输入，记得是无向边
	p = read();
	while (p--) {
		s = read(), t = read();
		memset (vis, 0, sizeof (vis));
		while (!q.empty()) q.pop();//记得初始化队列
		dijkstra();
		while (!q.empty()) q.pop();
		memset (vis, 0, sizeof (vis));
		dijkstra1();
		for (int i = 1; i <= n; i++) {
			if (dis[t] == dis[i] + dist[i]) ans.push(i);
		}//遍历，找答案
		while (!ans.empty()) {
			write (ans.top());
			putchar (' ');
			ans.pop();
		}//输出
		puts("");
	}
}
```


---

## 作者：0x3F (赞：0)

# 读题
看到大家都用 $\texttt{SPFA}$，难道没有发现 $n$ 很小吗？

再看一下多次询问，多源最短路，果断用 $\texttt{Floyd}$。

# 算法
求出了最短路，然后呢？

如何判断 $x$ 是否在 $v \rightarrow u$ 的最短路上？

很简单，在 $v \rightarrow u$ 的最短路上取一点 $x$，则 $v \rightarrow u = v \rightarrow x \rightarrow u = v \rightarrow x + x \rightarrow u$。

反之，如果 $v \rightarrow x + x \rightarrow u = v \rightarrow u$，则 $v \rightarrow x \rightarrow u$ 为最短路，于是 $x$ 在 $v \rightarrow u$ 的最短路上。

另外，$u, v$ 本身不需要特判，因为 $u \rightarrow u = 0$，$v$ 同理。

于是算法就出来了，先用 $\texttt{Floyd}$ 求一遍最短路，然后对于每一个询问，找出所有满足的 $x$，一一输出即可。

复杂度为 $\Theta(n^3)-\Theta(n)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t, u, v;
int dis[100][100];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) dis[i][j] = 0;
			else dis[i][j] = 0x3F3F3F3F;
		}
	}
	while (m--) {
		cin >> u >> v;
		dis[u][v] = dis[v][u] = 1;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	cin >> t;
	while (t--) {
		cin >> u >> v;
		for (int i = 1; i <= n; i++) {
			if (dis[u][i] + dis[i][v] == dis[u][v]) cout << i << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Space_Gold_Trash (赞：0)

很水的一道题

题目大意是求出$u->v$最短路点的集合

于是我们可以先把最短路求出来,如果我们发现$dis_{u->i}+dis_{i->v}=dis_{u->v}$的点$i$,那么$i$一定在最短路上

所以我们只需要$floyed$求出最短路,然后对于每组询问

从$1$到$n$判断$i$合法,然后输出合法的$i$即可

代码：

```
#include<bits/stdc++.h>
#define INF 20041026
#define N 51
using namespace std;
int d[N][N],n,m;
bool vis[N];
int main( ){
	int i,j,k,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j)
		d[i][j]=20041026;
		d[i][i]=0;
	}
	for(i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		d[x][y]=d[y][x]=1;
	}
	for(k=1;k<=n;++k)
	for(i=1;i<=n;++i)
	for(j=1;j<=n;++j)
	d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&x,&y);
		for(i=1;i<=n;++i)
		if(d[x][i]+d[i][y]==d[x][y])printf("%d ",i);
		putchar('\n');
	}
}
```

---

## 作者：abandentsky (赞：0)

这个题目那么简单没几个题解，我就来发一个吧。直接bfs，然后dfs就搞完了。
算出每个点的距离源点的最短路径，然后d[u]==d[v]+1，就这样，可以找到所有的路径，最后用unique去重，就完了。特别简单。
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 50
#define maxnode 1000005
#define sigma_size 26
#define md 12345678
#define INF 0x3f3f3f3f
#define pii pair<int,int>
using namespace std;

int n,m,k;
vector<int> G[MAXN];
vector<int> P;
int d[MAXN];
bool vis[MAXN];
int s,t;

void dfs(int u)
{
    P.push_back(u);
    if(u==s)
        return ;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(d[v]==d[u]-1)
            dfs(v);
    }
}

void solve(int s,int t)
{
    memset(d,INF,sizeof(d));
    memset(vis,false,sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s]=0;
    vis[s]=true;
    while(!Q.empty())
    {
        int X=Q.front();
        Q.pop();
        for(int i=0;i<G[X].size();i++)
        {
            int v=G[X][i];
            if(vis[v])
                continue;
            vis[v]=true;
            Q.push(v);
            d[v]=d[X]+1;
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        P.clear();
        scanf("%d %d",&s,&t);
        solve(s,t);
        dfs(t);
        sort(P.begin(),P.end());
        vector<int>::iterator it;
        it=unique(P.begin(),P.end());
        P.erase(it,P.end());
        for(int i=0;i<P.size();i++)
            printf("%d ",P[i]);
        printf("\n");
    }
    return 0;
}

```


---

## 作者：白木偶君 (赞：0)

#### 当我看到n<=40的时候，哎，我就明白，这题就是要我们写个n三方的暴力
**我的方法也是先floyd求所有点对的最短路**

#### 再下面用下面这段代码判断是否在a->b 的最短路上
```cpp
	for(int i=1;i<=n;i++)
	if(f[a][i]+f[i][b]==f[a][b])printf("%lld ",i);
```

**如果k比较大的话，复杂度 O(k*n)**

**(因为这里n最大只有四十，所以我认为 n*n远远小于k ,把n*n当做常数了)**

## 现在才是重点
## 前面一篇题解说要排序，其实根本不需要
## 直接从1到n判断就好了啊,起点终点就算和判断的点一样也没有关系
### 初始化的时候加上这个
```cpp
	for(int i=1;i<=n;i++)f[i][i]=0;
```
### 升序判断，升序输出
### 如果要排序的话，复杂度直接就多了一个log
### ~~这里n<=40,倒也没什么问题~~
### 要是数据大了，肯定就会有区别的吧
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int N=50;
int f[N][N];
signed main(){
	int n,m;
	cin>>n>>m;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int i=1,u,v;i<=m;i++){
		scanf("%lld%lld",&u,&v);
		f[u][v]=1,f[v][u]=1;
	}

	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
	int k;
	cin>>k;
	int a,b;
	while(k--){
		scanf("%lld%lld",&a,&b);
		for(int i=1;i<=n;i++)
		if(f[a][i]+f[i][b]==f[a][b])printf("%lld ",i);
		printf("\n");
	}
}
```



---

## 作者：dfydada⚡⚡⚡ (赞：0)

写这题的重点代码就只有一行，只要想到这个点了就很好写了。

因为数据很小（看起来很小，虽然只告诉了n），所以我们可以用floyd来写，而且不用担心超时。

题目说了这是个无向连通图，所以把两个位置都赋上值。

```cpp
for(int i=1;i<=m;i++)
{
	cin>>a>>b;
	d[a][b]=d[b][a]=1;//很好理解，无向图
}
```
然后就是模板的floyd（三循环）：

```cpp
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	{
		for(int k=1;k<=n;k++)
		{
			if(d[j][k]>d[j][i]+d[i][k])
			{
				d[j][k]=d[j][i]+d[i][k];
			}
		}
	}
}
```
到这里都不需要修改模板，也用新建一个数组在三循环中（那是只求一种）。我们要求的是多种最短路。只需要在线处理就好了。

因为题目要求要排序所以还要用一个变量存起来。

接下来就是重点代码：

```cpp
for(int j=1;j<=n;j++)
{
	if(d[v][j]+d[j][u]==d[v][u])
	{
		tot++;
		c[tot]=j;
	}
}
```
这步的目的很容易就从代码中看出来了吧。

就相当于给你4个点A、B、C、D告诉你各个点的距离，让你找有几种方法拼凑成A到D的距离一样。

把所有找的方法存入数组中，在拍个序输出就可以了。

下一次操作记得要初始化。

总代码:

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)//O2优化
using namespace std;
typedef long long ll;
const int N=1600+10;
int n,m,a,b,k,v,u;
int tot,d[N][N],c[N];
int main()
{
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=n;i++)
	{
		d[i][i]=0;
	}
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		d[a][b]=d[b][a]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				if(d[j][k]>d[j][i]+d[i][k])
				{
					d[j][k]=d[j][i]+d[i][k];
				}
			}
		}
	}
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>v>>u;
		tot=1;
		c[tot]=v;
		tot++;
		c[tot]=u;
		for(int j=1;j<=n;j++)
		{
			if(d[v][j]+d[j][u]==d[v][u])
			{
				tot++;
				c[tot]=j;
			}
		}
		sort(c+1,c+1+tot);
		for(int j=1;j<=tot;j++)
		{
			cout<<c[j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：冰桨 (赞：0)

**这道题可以用堆优化的dijisktra跑一边，用动态数组Vector保存能够到达终点的路线中每个点的前一个点，最后用dfs存下所有路径，用去重函数unique去重，再排序就可以了！！！**
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int N=1010010;
vector<int>g[N];
struct node{
	int next,to;
}e[N];
int head[N],cnt,vis[N],dis[N],a[N],n,m,k,cnt1;
void add(int from,int to){
	e[++cnt].next=head[from];
	e[cnt].to=to;
	head[from]=cnt;
}
struct edge{
	int l,d;
	bool operator<(const edge&a)const{
		return d>a.d;
	}
};
priority_queue<edge> q;
void spfa(int x){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) dis[i]=0x7fffffff,g[i].clear();
	dis[x]=0;
	q.push((edge){x,0});
	while(!q.empty()){
		edge p=q.top();
		q.pop();
		int u=p.l;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[v]>=dis[u]+1){
				dis[v]=dis[u]+1;
				g[v].push_back(u);
				//printf("%d %d\n",u,v);
				if(!vis[v]){
					q.push((edge){v,dis[v]});
				}
			}
		}
	}
}
void dfs(int x,int p){
	if(x==p) {
		return;
	}
	for(int j=0;j<g[x].size();j++){
		a[++cnt1]=g[x][j];
		dfs(g[x][j],p);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
    	int s,t;
    	scanf("%d%d",&s,&t);
    	spfa(s);
    	dfs(t,s);
    	a[++cnt1]=t;
    	sort(a+1,a+cnt1+1);
    	int pp=unique(a+1,a+cnt1+1)-(a+1);
		unique(a+1,a+cnt1+1)-(a+1);
    	for(int j=1;j<=pp;j++){
    		if(a[j]!=0)
    		printf("%d ",a[j]);
		}
		printf("\n");
		cnt1=0;
	}
	return 0;
}
```


---

