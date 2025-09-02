# [USACO19OPEN] Bucket Brigade B

## 题目描述

农场上起火了，奶牛们正在紧急赶去灭火！

农场可以用一个像这样的 $10×10$ 的字符方阵来描述：

```plain
..........
..........
..........
..B.......
..........
.....R....
..........
..........
.....L....
..........
```

字符 `B` 表示正着火的牛棚。字符 `L` 表示一个湖，而字符 `R` 表示农场上的一块巨大岩石。

奶牛们想要沿着一条湖到牛棚之间的路径组成一条“水桶传递队列”，这样她们就可以沿着这条路径传递水桶来帮助灭火。当两头奶牛在东南西北四个方向上相邻时水桶可以在她们之间传递。这对于湖边的奶牛也是对的——奶牛只能在紧挨着湖的时候才能用水桶从湖里取水。类似地，奶牛只能在紧挨着牛棚的时候才能用水去灭牛棚的火。 

请帮助求出奶牛们为了组成这样的“水桶传递队列”需要占据的 `.` 格子的最小数量。

奶牛不能站在岩石所在的方格之内，此外保证牛棚和湖不是相邻的。 

## 说明/提示

### 样例解释 1

在这个例子中，以下是一个可行的方案，使用了最小数量的奶牛（$7$）：

```plain
..........
..........
..........
..B.......
..C.......
..CC.R....
...CCC....
.....C....
.....L....
..........
```

## 样例 #1

### 输入

```
..........
..........
..........
..B.......
..........
.....R....
..........
..........
.....L....
..........```

### 输出

```
7```

# 题解

## 作者：lutaoquan2012 (赞：13)

## 思路：
这道题一看只有一块石头，这一眼看上去就可以不用深搜了么？

按照样例解释一下：
```
..........
..........
..........
..B.......
..........
.....R....
..........
..........
.....L....
..........
```
这是给我们的图。

最短的路程显然就是
```
..........
..........
..........
..B.......
..C.......
..C..R....
..C.......
..C.......
..CCCL....
..........
```
但是如果他在第 $6$ 行第 $3$ 列放一块大石头呢，我们仍然可以按照同样的方法计算。
```
..........
..........
..........
..BCCC....
.....C....
..R..C....
.....C....
.....C....
.....L....
..........
```
我们可以根据只有一个石头的特点直接计算出答案，结果也就是 $\left\vert Bx-Lx\right\vert+\left\vert By-Ly\right\vert-1$。

但是我们只能获得 $70$ 分的好成绩，因为我们忽略了一个情况。
```
..........
..........
....L.....
..........
..........
....R.....
..........
..........
....B.....
..........

```
这样的话我们这块石头也就挡住了我们的最简单的路线，所以我们可以往两边放两头奶牛凸出来。
```
..........
..........
...CL.....
...C......
...C......
...CR.....
...C......
...C......
...CB.....
..........
```
这样我们只需要判断一下是不是这三个坐标都连在一起，答案也就是原来的再加上 $2$。

可惜我们低估了数据的强度，这样还是只能拿到 $80$ 分的成绩。
```
..........
..........
....L.....
..........
..........
....B.....
..........
..........
....R.....
..........
```
对于这种情况，我们发现确实是连在了一起，但是这个起点与终点的路上完全不需要躲避大石头，就只需要判断一下是不是这条路线包含这个大石头。
## 代码：
```cpp
//
// Created by 55062 on 2024/1/14.
//
#include<bits/stdc++.h>
using namespace std;
typedef long ll;
char a[20][20];
ll Bx,By,Lx,Ly,Rx,Ry;
int main(){
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++){
            cin>>a[i][j];
            if(a[i][j]=='B') Bx=i,By=j;
            if(a[i][j]=='L') Lx=i,Ly=j;
            if(a[i][j]=='R') Rx=i,Ry=j;
        }
    if(Bx==Lx&&Lx==Rx&&(By>=Ry&&Ly<=Ry||Ly>=Ry&&By<=Ry)||By==Ly&&Ly==Ry&&(Bx>=Rx&&Lx<=Rx||Lx>=Rx&&Bx<=Rx)) cout<<abs(Bx-Lx)+abs(By-Ly)+1;
    else cout<<abs(Bx-Lx)+abs(By-Ly)-1;
    return 0;
}
```

---

## 作者：qw1234321 (赞：5)

其他题解都是广搜，这里提供一种代码简单思路不是很好想的做法：

首先，观察题面，发现只有一个牛棚，一个湖，一块岩石。

然后，分类讨论：

I. 若 $B,R,L$ 不共线。

答案直接就是 $B$ 到 $L$ 的 曼哈顿距离，因为不共线，所以 $B$ 到 $L$ 的至少两条最短路径中必然有一条是避开了 $R$ 的。

II. 若 $B,R,L$ 三点共线。

这个稍微复杂点，再分讨一下：

1. 如 ```B...R....L``` 或 ```L...R....B``` 这样的共线：

答案就是 $B$ 到 $L$ 的 曼哈顿距离 $+2$，因为要绕过一下 $R$。

2. 如 ```B...L....R``` 或 ```L...B....R``` 或 ```R...B....L``` 或 ```R...L....B``` 这样的共线：

答案直接就是 $B$ 到 $L$ 的 曼哈顿距离。

那横着的搞定了，竖着的也同理了。

没了。（

---

## 作者：_little_Cabbage_ (赞：4)

# P1699 [USACO19OPEN] Bucket Brigade B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p1699)~~

这是一道广搜模板题。

我们可以把 `R` 看成障碍，把 `L` 看成起点，把 `B` 看成终点，最后进行一遍广搜即可。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1010][1010];
int dx[]={0,-1,0,1};
int dy[]={-1,0,1,0};
int vis[1010][1010];
int n=10,m=10;
struct node
{
	int x,y,step;
};
int bfs(int sx,int sy,int tx,int ty)
{
	queue<node>q;
	q.push(node{sx,sy,0});
	while(!q.empty())
	{
		node f=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nowx=f.x+dx[i];
			int nowy=f.y+dy[i];
			if(nowx<0||nowx>=n||nowy<0||nowy>=m||vis[nowx][nowy]==1||s[nowx][nowy]=='R')
			{
				continue;
			}
			vis[nowx][nowy]=1;
			node x;
			x.x=nowx;
			x.y=nowy;
			x.step=f.step+1;
			q.push(x);
			if(nowx==tx&&nowy==ty)
			{
				return f.step;
			}
		}
	}
	return -1;
}
int main()
{
	int sx,sy,tx,ty;
	for(int i=0;i<n;i++)
	{
		scanf("%s",s[i]);
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='L')
			{
				sx=i;
				sy=j;
			}
			if(s[i][j]=='B')
			{
				tx=i;
				ty=j;
			}
		}
	}
	vis[sx][sy]=1;
	int ans1=bfs(sx,sy,tx,ty);
	cout<<ans1;
}
```
[AC 记录](https://www.luogu.com.cn/record/142392427)

---

## 作者：WydnksqhbD (赞：3)

# [P1699 [USACO19OPEN] Bucket Brigade B](https://www.luogu.com.cn/problem/P1699) 题解
## 思路
一拿到题目，我就想起了 DFS——深度优先搜索。DFS 的原理非常简单，就是**不撞南墙不回头**。我们将 DFS 封装成一个函数，每到一个点，就先把所有可能扩展到的点给递归一遍。到了终点，就刷新最小步数。

但是 DFS 有一个致命的缺点：**第一次找到的步数不一定是最小的**。所以非常容易超时或栈空间溢出。

那么我们该怎么办呢？BFS 大法好！

BFS（广度优先搜索）的原理是：维护一个队列，里面的每个元素装着位置、步数（结构体），然后将起点的信息入队。每次将队首**有可能到达的点入队**并弹出队首。然后每次取出队首并弹出，再入队。这样如果扩展到了终点就直接输出步数并返回。
## 重点
+ 标记了吗？
+ 弹出了吗？
+ 输入时要用字符串先读入，再赋值到数组里面。
+ 你是不是没有把初始状态入队？

思路完毕，不会打的参考代码吧。（我用的是 STL）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n=10;
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
char a[15][15];
string s[15];
bool book[15][15];
struct node
{
	int x,y,step;
};
queue<node>q;
void bfs()
{
	while(!q.empty())
	{
		int x=q.front().x,y=q.front().y,step=q.front().step;
		q.pop();
		if(a[x][y]=='B')
		{
			printf("%d",step);
			return;
		}
		book[x][y]=1;
		for(int i=0;i<4;i++)
		{
			int nx=x+dx[i],ny=y+dy[i];
			if(a[nx][ny]!='R'&&book[nx][ny]==0&&nx>=1&&nx<=n&&ny>=1&&ny<=n)
			{
				q.push(node{nx,ny,step+1});
			}
		}
	}
}
int main()
{
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=s[i][j-1];
			if(a[i][j]=='L')
			{
				q.push(node{i,j,-1});
			}
		}
	}
	bfs();
	return 0;
}
```

---

## 作者：Zack11 (赞：3)

[传送门：P1699](https://www.luogu.com.cn/problem/P1699)

一道广搜模板题，翻译一下，就是从 $L$ 到 $B$ 有多远不过要注意，步数**不包含起终点**，所以最后步数要 $-1$。

深搜思路：一条路走到死，走不了了再回去，接着走下一条路。递归实现，时间复杂度较高。
在本题中，除了判断是否会越界、是否走过，还要判断是不是大石块 $R$。

样例解释也已经很明确，$C$ 所在的点就是走过的路程。

那么，如果使用深搜：
```cpp
void dfs(int x,int y,int step){
	if(step>ans+1) return;
	if(x==ex && y==ey){
		ans=step-1;
		return;
	}
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1 || nx>10 || ny<1 || ny>10 || v[nx][ny] || c[nx][ny]=='R') continue;
		v[nx][ny]=1;
		dfs(nx,ny,step+1);
		v[nx][ny]=0;
	}
}
```
你会发现虽然很简单，但是 TLE 了。这里深搜使用的是递归，还需要回溯，时间复杂度是指数级别的，数据稍大就会超时。

那么，我们需要更快一点，不妨使用广搜。

广搜的主要思想，就是把根节点先加入队列中，判断是否到达终点，若没有到达，则把其出队，并将其子结点入队，在队列非空时反复执行，找到结点之后直接返回。这样可以大大减少时间复杂度。

因为广搜是是一层一层搜，所以会比深搜快，那么主要思路看代码：
```cpp
#include<iostream>
#include<queue>
using namespace std;
struct node{
	int x,y,step;//x,y坐标和步数 
};
char c[15][15];//地图 
int sx,sy,ex,ey;//起终点 
int ans=1e9;//最后结果初始化 
int dx[]={0,0,1,-1},dy[]={-1,1,0,0};//四联通 
bool v[15][15];//标记数组 
queue<node> q;//队列存储结点 
void bfs()
{
	q.push(node{sx,sy,0});//起点入队 
	while(!q.empty())//遍历队列 
	{
		node u=q.front();//取队首元素 
		q.pop();
		if(u.x==ex && u.y==ey)
		{
			cout << u.step-1;//因为不包含终点，所以最后步数-1 
			return;//返回 ~ 
		}
		for(int i=0;i<4;i++)
		{
			int nx=u.x+dx[i],ny=u.y+dy[i];
			//边界条件 
			if(nx<1 || nx>10 || ny<1 || ny>10 || v[nx][ny] || c[nx][ny]=='R') continue;
			v[nx][ny]=1;//来过了踩个脚印 
			q.push(node{nx,ny,u.step+1});//结点入队 
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);//关闭输入输出缓冲区同步，加速 
	cin.tie(0);cout.tie(0);
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)
		{
			cin >> c[i][j];
			//起点和终点 
			if(c[i][j]=='L') sx=i,sy=j;
			if(c[i][j]=='B') ex=i,ey=j;
		}
	}
	v[sx][sy]=1;//先将起点标记 
	bfs();//搜索 
	return 0;//完结撒花 ~ 
}
```
第一次发题解，求过 QAQ ~

---

## 作者：liaoxingrui (赞：3)

## Content

农场着火了，可以用一个 $10 \times 10$ 的字符方阵来表示农场。

其中 $.$ 表示空地，$B$ 表示农场着火的地方，$L$ 表示湖泊，$R$ 表示石头不可通过。

一群奶牛想要灭火，他们只有相邻才能将水从湖泊传到着火的地方。

问最少需要多少奶牛。

## Solution

这道题分两种情况：

1. 三个点 $B,L,R$ 不共线 

2. 三个点 $B,L,R$ 共线

第一种情况，我们可以找到 $B$ 点和 $L$ 点的位置，然后算出它们纵坐标的差与横坐标的差的和再减去一个顶点（$\operatorname{abs}(xB-xL)+\operatorname{abs}(yB-yL)-1$）便是答案。

第二种情况，跟第一种情况基本相同，只是要加上绕开石头多来的两头牛（$\operatorname{abs}(xB-xL)+\operatorname{abs}(yB-yL)+1$）便是答案。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int xB,yB,xL,yL,xR,yR;
char a;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=10;i++)
		for(int j=1;j<=10;j++){
			cin>>a;
			if(a=='B'){//找 B 的坐标 
				xB=i;
				yB=j;
			}
			if(a=='L'){//找 L 的坐标 
				xL=i;
				yL=j;
			}
			if(a=='R'){//找 R 的坐标 
				xR=i;
				yR=j;
			}
		}
	cout<<abs(xB-xL)+abs(yB-yL)+(((xB==xL&&xL==xR&&((yB<yR&&yR<yL)||(yL<yR&&yR<yB)))||(yB==yL&&yL==yR&&((xB<xR&&xR<xL)||(xL<xR&&xR<xB))))?1:-1);//算出答案 
	return 0;
}
```

---

## 作者：BGM114514 (赞：2)

### 蒟蒻看见大部分题解都是搜索，这里提供一种代码较好写的思路qwq

upd 2024.04.08 改正了一个错别字

[题目传送门](https://www.luogu.com.cn/problem/P1699)

## 蒟蒻的心路历程

这题也太简单了吧！学 OI 两年半都看得出来是道搜索题！（干代码中）

……过了一会儿……

唉，代码干不动了，看一会儿题目。欸？石头只有一块？啊这……

**于是，就有了这篇题解**
------------
**首先**，题目说有一个着火点（即起点）、一个石头（即障碍物）、一个湖（即终点），问起点到终点的最短路径要经过几格（不算终点、起点）。

我们来想一个类似**贪心**的算法：

设起点坐标为 $(sx,sy)$，终点坐标为 $(ex,ey)$，障碍物坐标为 $(kx,ky)$。

由于障碍物只有一个，而两点之间路径却有很多条，所以路径长度肯定是：
$$|(ex-sx)|+|(ey-sy)|-1$$
（两个点到交点的长度和减去重复的交点）。

可是交上去后，发现蛙了 $3$ 个点，只有 $70$ pts。

蒟蒻自我反省一会儿后，~~马上~~发现了问题：如果数据是同行同列呢？此时，我们的公式会多减一，导致 WA。因此，加两个特判，分别判断同行（即 $x$ 坐标相等）、同列（即 $y$ 坐标相等）。

交上去之后，发现另外两个点蛙了，$80$ pts（其实原来那份应该蛙 $5$ 个的，但是这两个点答案刚好是 $2$）。

这下蒟蒻想不出来了，~~只好~~ 下载数据。结果脑瓜一拍，又发现了问题：咱的代码没判断障碍物是否在起点和终点之间！于是，特判中的特判横空出世——判断障碍物的列（行）坐标是否在起点和终点的列（行）坐标之间。

**这里再提一嘴**，输入这种字符类型的地图用 getchar 函数会比较快，不过要在循环外再加一个，因为它不像 cin 那样过滤换行哦。

$100$ pts，愉快拿下！

## Code
[AC 记录](https://www.luogu.com.cn/record/143995856)

```cpp
#include<bits/stdc++.h>
using namespace std;
char ch;
int main() {
	int sx,sy,ex,ey,kx,ky;//定义变量 
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++){
			ch=getchar(); //getchar()
			if(ch=='B')sx=i,sy=j;
			if(ch=='R')kx=i,ky=j;
			if(ch=='L')ex=i,ey=j;
		}
		getchar();//读取换行 
	}
	if(sy==ky&&ky==ey&&kx<max(ex,sx)&&kx>min(ex,sx))cout<<abs(ex-sx)+1<<endl;//特判同行以及列坐标是否在起点和终点的列坐标之间
	else if(sx==kx&&kx==ex&&ky<max(ey,sy)&&ky>min(ey,sy))cout<<abs(ey-sy)+1<<endl;//特判同列以及行坐标是否在起点和终点的行坐标之间
	else cout<<abs(ex-sx)+abs(ey-sy)-1<<endl;//两个点到交点的长度和减去重复的交点 
	return 0;//不那么华丽的结尾（小声） 
}
```

---

## 作者：Kano_zyc (赞：2)

## 题意简述

题目已经很清楚了，不做过多赘述。

## 思路分析

很明显是一道 BFS 题目。从火源开始，找到最短的到湖的路径。开一个方向数组，并且在搜索过程中，记录一下每个点的距离，并且特判岩石（不能穿过）即可。

## 注意事项

在计算结果时，需要输出的是路径上"."的数量，所以最后输出的结果应该减 $1$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15,INF=0x3f3f3f3f;
char g[N][N];
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1},n=10;
int dist[N][N],vis[N][N];
struct P{
    int x,y;
}p[3];
void bfs(int sx,int sy){
    memset(dist,0x3f,sizeof dist);
    memset(vis,0,sizeof vis);
    queue<P>q;
    q.push((P){sx,sy});
    dist[sx][sy]=0;
    while(!q.empty()){
        P u=q.front();q.pop();
        for(int i=0;i<4;i++){
            int x=u.x+dx[i],y=u.y+dy[i];
            if(x<0||x>=n||y<0||y>=n||vis[x][y]||g[x][y]=='R') continue;
            vis[x][y]=1;
            dist[x][y]=dist[u.x][u.y]+1;
            q.push((P){x,y});
        }
    }
}
int main(){
    for(int i=0;i<n;i++){
        scanf("%s",g[i]);
        for(int j=0;j<n;j++){
            if(g[i][j]=='B') p[0]=(P){i,j};
            if(g[i][j]=='L') p[1]=(P){i,j};
            if(g[i][j]=='R') p[2]=(P){i,j};
        }
    }
    bfs(p[0].x,p[0].y);
    printf("%d\n",dist[p[1].x][p[1].y]-1);
    return 0;
}
```


---

## 作者：NC20061226 (赞：2)

# P1699 Bucket Brigade B 题解

部分引自魏梦舒的《漫画算法 Python 版》（实际上两个讲的是一样的，不过书本更详细）。

## 题意

给定一个迷宫，包含起点 `B`、障碍物 `R`、终点 `L`，求出从起点到达终点所需的最小步数（最短路径）。

## 思路

这里运用到了一种[启发式搜索算法](https://baike.baidu.com/item/%E5%90%AF%E5%8F%91%E5%BC%8F%E6%90%9C%E7%B4%A2%E7%AE%97%E6%B3%95/7020552?fromModule=lemma_inlink)：[A* 寻路算法](https://baike.baidu.com/item/A%2A%E6%90%9C%E5%AF%BB%E7%AE%97%E6%B3%95/6773036?fr=ge_ala)。

>A\* 搜寻算法俗称 A 星算法。A* 算法是比较流行的启发式搜索算法之一，被广泛应用于路径优化领域。它的独特之处是检查最短路径中每个可能的节点时引入了全局信息，对当前节点距终点的距离做出估计，并作为评价该节点处于最短路线上的可能性的量度。

首先要引入两个集合和一个公式：

- $openList$：可到达的格子。
- $closeList$：已到达的格子。

一个公式如下：
$$F=G+H$$

每一个格子都具有 $F$、$G$、$H$ 这三个属性：

- $G$：从起点走到当前格子的成本，也就是已经花费了多少步。

- $H$：在不考虑障碍的情况下，从当前格子走到目标格子的距离，也就是离目标还有多远。

- $F$：$G$ 和 $H$ 的综合评估，也就是从起点到达当前格子，再从当前格子到达目标格子的总步数。

现在有下面三个步骤：

1. 第一步：把起点放入 $openList$，也就是可到达格子的集合。

2. 第二步：找出 $openList$ 中 $F$ 值最小的方格作为当前方格。

3. 第三步：找出当前方格上下左右所有可到达的格子，看它们是否在 $openList$ 或者 $closeList$ 中，如果不在，则将它们加入 $openList$ 中。计算出相应 $G$、$H$、$F$ 值，并把当前格子作为它们的父节点。

之后进行第二轮，我们需要一次又一次重复刚刚的第二不和第三步，直到直到终点为止。

## 代码

这里没有递归的函数，回溯在循环中进行。

```python
def search(start, end):
    # 待访问的格子
    open_lt = []
    # 已访问的格子
    close_lt = []
    # 把起点加入 open_lt
    open_lt.append(start)
    # 主循环，每一轮检查一个当前方格节点
    while len(open_lt) > 0:
        # 在 open_lt 中查找 F 值最小的节点作为当前方格节点
        current_grid = find_min_gird(open_lt)
        # 当前方格节点从 openList 中移除
        open_lt.remove(current_grid)
        # 当前方格节点进入 closeList
        close_lt.append(current_grid)
        # 找到所有邻近节点
        neighbors = find_neighbors(current_grid, open_lt, close_lt)
        for grid in neighbors:
            if grid not in open_lt:
            # 邻近节点不在 openList 中，标记父亲、G、H、F，并放入 openList
                grid.init_grid(current_grid, end)
                open_lt.append(grid)
        # 如果终点在 openList 中，直接返回终点格子
        for grid in open_lt:
            if (grid.x == end.x) and (grid.y == end.y):
                return grid
    # openList 用尽，仍然找不到终点，说明终点不可到达，返回空
    return None


def find_min_gird(open_lt=[]):
    temp_grid = open_lt[0]
    for grid in open_lt:
        if grid.f < temp_grid.f:
            temp_grid = grid
    return temp_grid


def find_neighbors(grid, open_lt=[], close_lt=[]):
    grid_list = []
    if is_valid_grid(grid.x, grid.y-1, open_lt, close_lt):
        grid_list.append(Grid(grid.x, grid.y-1))
    if is_valid_grid(grid.x, grid.y+1, open_lt, close_lt):
        grid_list.append(Grid(grid.x, grid.y+1))
    if is_valid_grid(grid.x-1, grid.y, open_lt, close_lt):
        grid_list.append(Grid(grid.x-1, grid.y))
    if is_valid_grid(grid.x+1, grid.y, open_lt, close_lt):
        grid_list.append(Grid(grid.x+1, grid.y))
    return grid_list


def is_valid_grid(x, y, open_lt=[], close_lt=[]):
        # 是否超过边界
        if x < 0 or x >= len(MAZE) or y < 0 or y >= len(MAZE[0]):
            return False
        # 是否有障碍物
        if MAZE[x][y]=='R':
            return False
        # 是否已经在open_lt中
        if contain_grid(open_lt, x, y):
            return False
        # 是否已经在closeList中
        if contain_grid(close_lt, x, y):
            return False
        return True


def contain_grid(grids, x, y):
    for grid in grids:
        if (grid.x == x) and (grid.y == y):
            return True
    return False


class Grid:
    # 初始化
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.f = 0
        self.g = 0
        self.h = 0
        self.parent = None

    def init_grid(self, parent, end):
        self.parent = parent
        if parent is not None:
            self.g = parent.g + 1
        else:
            self.g=1
        self.h = abs(self.x - end.x) + abs(self.y - end.y)
        self.f = self.g + self.h


# 迷宫地图
MAZE = []

# 输入迷宫地图
for i in range(10):
    MAZE.append(list(input()))

def find(l):
    # 在迷宫中寻找起点和终点下标的函数
    for i in range(10):
        # 如果要寻找的函数在 MAZE[i] 里面
        if l in MAZE[i]:
            x = i # 返回起点/终点所在的列
            for j in range(10):
                if MAZE[i][j]==l: # 返回终点所在的行数下标
                    return (x,j)

# 寻找起点和终点所在的下标
B = find('B')
L = find('L')

# 设置起点和终点
start_grid = Grid(B[0],B[1]) # 起点的行与列
end_grid = Grid(L[0],L[1]) # 终点的行与列
# 搜索迷宫终点
result_grid = search(start_grid, end_grid)
# 回溯迷宫路径
path = []
while result_grid is not None:
    path.append(Grid(result_grid.x, result_grid.y))
    result_grid = result_grid.parent

ans = 0
# 输出迷宫和路径，路径用 @ 号表示
for i in range(0, len(MAZE)):
    for j in range(0, len(MAZE[0])):
        if contain_grid(path, i, j): #可行的路径
            # print("@", end=' ')
            ans+=1
        # else:
            # print(str(MAZE[i][j]), end=' ')
    # print()
print(ans-2) # 由于包括起点 B 和终点 L，所以减去 2
```

## 结尾

将代码中最后几行代码代码去掉注释就可以输出最短路径了。

好了，感谢您观看到这，谢谢观看！

本文皆为 Python 代码，如果有兴趣的可以了解更多！

管理员、志愿者们辛苦了！

（本文过审当天经过修改）。


---

## 作者：lgydkkyd (赞：1)

这题刚看到以为是搜索，后来发现只有一个障碍物，于是便可以分类讨论了，当石头，湖，牛棚在同一条直线上时，则需要绕开石头，牛棚与湖的曼哈顿距离再多走两步，否则可以无视石头，输出牛棚与湖的曼哈顿距离即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[11][11];
int l1,l2,b1,b2,r1,r2;
int main(){
    for(int i=1;i<=10;i++){
    	for(int j=1;j<=10;j++){
    		cin>>a[i][j];
    		if(a[i][j]=='L')l1=i,l2=j;//记录湖位置
    		if(a[i][j]=='B')b1=i,b2=j;//记录牛棚位置
    		if(a[i][j]=='R')r1=i,r2=j;//记录石头位置
		}
	}
	if((l1==b1&&r1==b1&&(l2<r2&&r2<b2||b2<r2&&r2<l2))||(l2==b2&&l2==r2)&&(l1<r1&&r1<b1||b1<r1&&r1<l1)){//判断是否在同一直线上
		cout<<abs(l1-b1)+abs(l2-b2)+1;
	}
	else{
		cout<<abs(l1-b1)+abs(l2-b2)-1;
	}
}
```

---

## 作者：xxboyxx (赞：1)

### 思路

一个标准的搜索题，由于需要最短路径且不需要统计路径，所以这里采用宽度优先搜索。

先保存起点（牛棚）与终点（湖），接下来进行搜索，障碍是岩石。再统计从起点到达终点的最短距离（奶牛数量）。

宽度优先搜索实现在代码中呈现。

### 注意

1. 由于要统计最短路径，则需要打上标记，以免覆盖。

2. 湖和牛棚是不需要奶牛的，所以答案会减少一。

3. 如果发现程序死循环，可以检查一下是否弹出队列。

4. 如果发现程序输出不正确，可以检查一下是否把起点坐标加入队列。

5. 如果发现程序运行时错误，可以检查一下边界判断。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[105][105];
int sx,sy;
int fx,fy;
int dx[10]={0,0,1,-1};//方向数组 
int dy[10]={1,-1,0,0};
int f[105][105];
int dis[105][105];
int bfs()
{
	queue<int> qx;
	queue<int> qy;
	qx.push(sx);//把起点坐标加入队列 
	qy.push(sy);
	while (!qx.empty())//注意empty函数的使用，为空反回1，非空反回0 
	{
		int nowx=qx.front();//记录坐标 
		int nowy=qy.front();
		qx.pop();//弹出 
		qy.pop();
		if (nowx==fx && nowy==fy)//到达终点 
			return dis[nowx][nowy];//返回距离 
		f[nowx][nowy]=1;//标记 
		for (int i=0;i<4;i++)//上下左右四个方向 
		{
			int nx=nowx+dx[i];//即将到达的点 
			int ny=nowy+dy[i];
			if (nx>=1 && ny>=1 && nx<=10 && ny<=10/*在合法区间内*/ && a[nx][ny]!='R'/*没有岩石*/ && f[nx][ny]==0/*未被标记*/)
			{
				qx.push(nx);//加入队列 
				qy.push(ny);
				dis[nx][ny]=dis[nowx][nowy]+1;//更新答案 
			}
		}
	}
}
int main()
{
	for (int i=1;i<=10;i++)
	{
		for (int j=1;j<=10;j++)
		{
			cin>>a[i][j];
			if (a[i][j]=='B')//保存起点 
			{
				sx=i;
				sy=j;
			}
			else if (a[i][j]=='L')//保存终点 
			{
				fx=i;
				fy=j;
			}
		}
	}
	cout<<bfs()-1;//答案减一 
	return 0;
}
```


---

## 作者：QAQvQAQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/solution/P1699)

我们先来读一下题：

一条可行的水桶传递队列所需要的奶牛的最小数量。其实这就是求最短长度嘛。最短长度一般用**广度优先搜索**来做。

输入保证图案中恰有一个字符 ```B``` 一个字符 ```L``` 以及一个字符 ```R``` 。这证明**起点和终点只有一个**，所以其实这就是一道广搜模板题。

广搜的主要原理就是把每个点都存进队列，每次循环都取出队首进行延伸，队列里没有东西也就是无路可走了的时候退出循环。因为广搜是用一步一步一起往外搜，所以第一次找到必定是最短的。

话不多说直接上代码~(如果这种写法在本地运行出警告的话不用管)

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
char mp[15][15];//地图 
int x,y,fx,fy;//x和y表示起点，fx和fy表示终点 
int nx,ny;//延伸的点坐标 
int nxt[4][2]={0,1,0,-1,-1,0,1,0};//方向数组 
int book[15][15];//标记走没走过的数组 
struct node{//xx和yy是队列中的坐标，cost是步数 
	int xx,yy,cost;
};
int main(){
	for(int i=1;i<=10;i++){//输入地图 
		for(int j=1;j<=10;j++){
			cin>>mp[i][j];
			if(mp[i][j]=='B'){//终点坐标 
				fx=i;
				fy=j;
			}
			if(mp[i][j]=='L'){//起点坐标 
				x=i;
				y=j;
			}
		}
	}
	queue<node>q;//定义队列 
	q.push({x,y,0});//加入起点（这里的cost是0因为L是不能走的） 
	book[x][y]=1;//标记起点 
	while(!q.empty()){//当队列不为空时 
		node tmp=q.front();//队列pop后就没有了，所以要定义一个变量存 
		q.pop();//弹出队列 
		if(tmp.xx==fx && tmp.yy==fy){//如果到达终点 
			cout<<tmp.cost-1<<endl;//输出步数（因为失火的地方旁边才是终点，都走了一步，所以-1 
			return 0;//因为第一次到终点必定为最短，所以直接结束主函数 
		}
		for(int i=0;i<4;i++){
			nx=tmp.xx+nxt[i][0];//新的x 
			ny=tmp.yy+nxt[i][1];//新的y 
			if(1<=nx && nx<=10 && 1<=ny && ny<=10){//判断越界 
				if(mp[nx][ny]!='R' && book[nx][ny]==0){//湖只有一个，开始时标记了，失火的地方是终点，所以如果不是石头都能走 
					book[nx][ny]=1;//标记新坐标 
					q.push({nx,ny,tmp.cost+1});//新坐标入队 
				}
			}
		}
	}
    return 0;
}
```


---

## 作者：Lian_zy (赞：0)

# 0 题目传送门
[**题目传送门**](https://www.luogu.com.cn/problem/P1699)

# 1 题目分析
看见题目的第一眼就想到了 BFS 搜索。

思路没什么太难的，直接搜就可以了。

但是有一点需要注意，有**四个点**与湖相邻，该选哪个呢？

注意到 $n$ 很小，仅为 $10$，所以我们暴力枚举四个点当做起点就好了，注意多次 BFS 要清空标记数组。

代码比较简单，就不贴了。

---

## 作者：xu_zhihao (赞：0)

### 题目理解：

- 这道题一看就是广搜也就是广度优先搜索的模板题。这一道题有 $2$ 种做法，但是想法都是一样的。

1. 模拟队列，对还没学 STL 的初学者比较友好。模拟队列，也就是将数组模拟成队列。但需要标记头和尾的位置，还不能做到实质意义上的删除队头，其实空间没有减小，所以比较占空间，有些题目可能数组开不下，可是会更好理解。就来看看我的代码吧。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x;
	int y;
	int step;
};
string s[11];
node val[10*10+1];
int mx[]={0,0,1,-1};
int my[]={1,-1,0,0};
bool flag[11][11];
int n,m;
void bfs(int sx,int sy,int tx,int ty)
{
	int head=0;
	int tail=0;
	node p;
	p.x=sx;
	p.y=sy;
	p.step=0;
	flag[sx][sy]=true;
	val[tail++]=p; 
	while(head<tail)
	{
		node l=val[head];
		head++;
		for(int i=0;i<4;i++)
		{
			int bx=l.x+mx[i];
			int by=l.y+my[i];
			if(bx<0 || bx>=10 || by<0 || by>=10)
			{
				continue;
			}
			if(s[bx][by]=='R' || flag[bx][by]==true)
			{
				continue;
			}
			node q;
		    flag[bx][by]=true;
			q.x=bx;
			q.y=by;
			q.step=l.step+1;
			val[tail++]=q;
			if(bx==tx && by==ty)
			{
				cout<<q.step-1;
				return;
			}
		}
	}
	cout<<-1;
}
int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	int sx,sy,tx,ty;
	for(int i=0;i<10;i++)
	{
		cin>>s[i];
		for(int j=0;j<10;j++)
		{
			if(s[i][j]=='L')
			{
				sx=i;
				sy=j;
			}
			if(s[i][j]=='B')
			{
				tx=i;
				ty=j;
			}
		}
	}
	
	bfs(sx,sy,tx,ty);
}
```
[最快速度](https://www.luogu.com.cn/record/145243028)

最优所有测试点用时 $34$ 毫秒。

[最小内存](https://www.luogu.com.cn/record/145243028)

最优最大内存 $680.00$ KB。



2. 直接使用队列。这样会方便很多，而且相对而言对空间的需求不是那么的大。但需要一定的 STL 基础。就来看看我的代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[11];
bool flag[11][11];
int x_wei[]={0,0,-1,1};
int y_wei[]={1,-1,0,0};
int mn=110;
struct node
{
	short x;
	short y;
	short step;
}a;
void bfs(int x1,int y1,int x2,int y2)
{
	queue<node> q;
	node a;
	a.x=x1;
	a.y=y1;
	a.step=0;
	q.push(a);
	while(!q.empty())
	{
		node f=q.front();
		q.pop();
		if(f.x==x2 && f.y==y2)
		{
			mn=min(mn,f.step-1);
		}
		for(int l=0;l<4;l++)
		{
			int dx=f.x+x_wei[l];
			int dy=f.y+y_wei[l];
			if(dx>=0 && dx<10 && dy>=0 && dy<10)
			{
				if(!flag[dx][dy])
				{
					if(s[dx][dy]!='R')
					{
						flag[dx][dy]=true;
						node k;
						k.x=dx;
						k.y=dy;
						k.step=f.step+1;
						q.push(k);
					}
				}
			}
		}
	}
	cout<<mn;
	return;
}
int main()
{
	//ios::sync_with_stdio(0);
    //cin.tie(0),cout.tie(0);
	int x1=0,y1=0,x2=0,y2=0;
	for(int i=0;i<10;i++)
	{
		cin>>s[i];
		for(int j=0;j<10;j++)
		{
			if(s[i][j]=='L')
			{
				x1=i;
				y1=j;
			}
			if(s[i][j]=='B')
			{
				x2=i;
				y2=j;
			}
		}
	}
	flag[x1][y1]=true;
	bfs(x1,y1,x2,y2);
} 
```
[最快速度](https://www.luogu.com.cn/record/145243747)

最优所有测试点用时 $31$ 毫秒。

[最小内存](https://www.luogu.com.cn/record/145242697)

最优最大内存 $632.00$ KB。


### 小结：

- 这道题是给初学者练 BFS 的模板好题。

- 有个很坑的的点就是最后一只牛是不用走到湖上的。

---

