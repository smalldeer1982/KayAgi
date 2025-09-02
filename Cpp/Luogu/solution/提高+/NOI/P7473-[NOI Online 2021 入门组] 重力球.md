# [NOI Online 2021 入门组] 重力球

## 题目描述

“重力球”游戏在一块 $n\times n$ 的正方形区域中进行，记从上往下第 $i$ 行，从左往右第 $j$ 列的位置为 $(i,j)$。

正方形区域中存在 $m$ 个障碍，第 $i$ 个障碍占据位置 $(x_i,y_i)$，此外，正方形区域的边界外都是障碍。

现在有两个小球，位置分别是 $(a,b)$ 和 $(c,d)$，在游戏中你可以进行如下操作：

- 指定上、下、左、右中的一个方向，将重力方向“切换”为这个方向。此时两个小球会同时向这个方向移动，直到碰到障碍。

你要用最少的操作次数使得两个小球到达同一个位置。

现有 $q$ 局游戏，每局游戏中只有小球的初始位置不同，而障碍位置是不变的，你需要对每局游戏都求出最小操作次数，或报告无解。

## 说明/提示

### 样例 $1$ 解释

该样例中障碍分布如图中红叉所示。

第一组询问中只需将重力改向上（或改向下）即可使两球同时到达。

第二组询问中两球已经在同一位置故不需操作。

第三组询问中改变3 次重力的方向，依次改为向左、向下、向左，小球移动路线分别如图中粉色、橙色、棕色线所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nngrov0.png)
### 数据范围与提示
对于 $20\%$ 的数据：$n,m\le 2$。

对于 $50\%$ 的数据：$n,m\le30$。

对于另外 $30\%$ 的数据：$q=1$。

对于 $100\%$ 的数据：$1\le n,m\le250，1\le q\le10^5，1\le x_i,y_i,a,b,c,d\le n$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 提供。

数据参考了 小喵喵不喜欢计算几何 2020 ICPC 区域赛（南京）A 题的构造方案，在此表示感谢。

## 样例 #1

### 输入

```
4 4 3
2 2
2 4
3 2
4 4
1 3 4 3
2 1 2 1
1 2 3 4```

### 输出

```
1
0
3```

# 题解

## 作者：Lynkcat (赞：40)

我们考虑普通的暴力怎么做。

首先我们可以暴搜，用一个形如 $(x,y,a,b)$ 的状态，表示第一个人在 $(x,y)$ ，第二个人在 $(a,b)$ 的位置上。然后枚举上下左右四个方向暴力走，直到碰到障碍为止。

接下来考虑优化暴搜：

$1:$ 预处理出每个位置上下左右的障碍位置，这样在搜索的时候可以 $O(1)$ 跳。

$2:$ 考虑每个 $(x,y,a,b)$ 的状态互不影响，所以我们可以记忆化一下。

$3:$ 再考虑如何解决上面这个状态记忆化所需要的空间过大的问题，我们可以发现每次重力方向钦定完后，球必定是在一个障碍物的相邻格子上。所以我们先抠出所有障碍物，然后设 $(x,y,1/2/3/4)$ 表示第一个人在第 $x$ 个障碍物的上下左右，第二个人在第 $y$ 个障碍物的上下左右，减少了空间的需求量。

最后，容易发现最多只有 $4(n-1)+m$ 个障碍物，因此障碍物附近的格子最多只有 $[4n+4m]\times 4$ 个，那么总状态数只有 $16[4n+4m]^2$ 个，最多 $25000000$ 。

但是如果直接记忆化搜索会遇到一个问题，如何确定转移方向？

这个问题就非常难搞了，至少需要给源代码乘上 4 倍的常数，显然不够优。

于是我们考虑把记忆化搜索换掉，正难则反，我们考虑对于原来的状态转移图变成它的反图，然后你会发现这就是一个多源点的最短路问题，求每个点到最近的那个源点的最短路，那么这个东西就可以用 bfs 来预处理，处理过程中忽略返祖边即可。

---

## 作者：water_tomato (赞：37)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p7473-noi-online-2021-%e5%85%a5%e9%97%a8%e7%bb%84-%e9%87%8d%e5%8a%9b%e7%90%83-%e9%a2%98%e8%a7%a3/)
## 题意

[题目链接](https://www.luogu.com.cn/problem/P7473)

给出一个正方形区域，其中有一些点是障碍。每次询问给出两个球的初始位置，询问至少需要改变几次重力才能使两球相遇。

## 解析

首先我们发现，实际上仅有障碍周围（包括地图边界）上的点是有意义的（因为任何位置的球经过一次操作一定会到这些点，显然一次操作是可以枚举的）。我们定义每一组有意义的 $(x,y)$ 为一个状态，显然最多状态数为 $2000$ 左右，而两个球的状态种数就为 $4 \times 10^6$，是可以接受的。

我们可以考虑先将所有有意义的点对 $(x,y)$ 都进行编号，作为这个点的状态号。然后我们预处理出从每一点进行某一方向的操作后所到达的状态数。这部分代码如下：

```cpp
inline bool check(int i,int j){
	if(a[i-1][j]||a[i+1][j]||a[i][j-1]||a[i][j+1]) return true;
	return false;
}
……
scanf("%d%d%d",&n,&m,&Q);
for(int i=1,x,y;i<=m;i++){
    scanf("%d%d",&x,&y);
    a[x][y]=1;//标记障碍
}
for(int i=1;i<=n;i++) a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;//标记障碍
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        if(!a[i][j]&&check(i,j)) id[i][j]=++tot;//对有意义的点进行编号
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++) 
        t[i][j][0]=a[i][j-1]?id[i][j]:t[i][j-1][0],
		t[i][j][1]=a[i-1][j]?id[i][j]:t[i-1][j][1];
for(int i=n;i;i--)
    for(int j=n;j;j--)
        t[i][j][2]=a[i][j+1]?id[i][j]:t[i][j+1][2],
		t[i][j][3]=a[i+1][j]?id[i][j]:t[i+1][j][3];
		//分别处理出从 (i,j) 向各个方向走所到达的点的状态号
```

接着我们发现两个小球最终相遇，相当于是两个球所在的点编号相同了，因此我们可以考虑从终点开始逆推。那么怎么转移状态呢？我们可以将每一个状态看作一个点，如果状态 $i$ 可以转移到状态 $j$，我们就从 $j$ 向 $i$ 连一条边（因为后边要逆推，所以建反边）。同样的，我们只需要在有意义的点之间连边就可以了。这部分代码如下：

```cpp
inline void add(int u,int v,int p){
	e[++cnt].to=v;
	e[cnt].nxt=head[u][p];
	head[u][p]=cnt;//每个点的四种状态都需要一个 head，因为转移时需要枚举方向
}
……
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(id[i][j]) for(int k=0;k<=3;k++) add(t[i][j][k],id[i][j],k);//建反边
```

接着，我们定义 $dis_{i,j}$ 为状态为 $i,j$ 的两个小球所想要相遇所需要的操作数。定义 $dis_{i,i}=1$（因为到时候要消耗一步来枚举第一步，干脆直接把初值赋值为 $1$，然后特判相等的情况更为方便）。然后我们在这张图上进行 bfs，每次枚举 $i,j$ 两个状态分别所能到达的其他状态并更新所到达的这两个状态间的距离。由于两个球的状态种数仅为 $4 \times 10^6$，且每一个状态至多创造 $4$ 条边，所以 bfs 的复杂度是可接受的。这部分代码如下：

```cpp
queue<pair<int,int> > q;
for(int i=1;i<=tot;i++)
    for(int j=1;j<=tot;j++)
        dis[i][j]=1e9+7;
for(int i=1;i<=tot;i++) q.push(make_pair(i,i)),dis[i][i]=1;//赋初值并 push 进队列
while(!q.empty()){
    pair<int,int> x=q.front();q.pop();
    for(int k=0;k<=3;k++){//枚举方向
        for(int i=head[x.first][k];i;i=e[i].nxt){
            for(int j=head[x.second][k];j;j=e[j].nxt){//枚举到达的状态
                int u=e[i].to,v=e[j].to;
                if(dis[u][v]==1e9+7){
                    dis[u][v]=dis[x.first][x.second]+1,
                    q.push(make_pair(u,v));//更新并 push 进队列
                }
            }
        }
    }
}
```

最后对于每一次询问，如果两个点重合输出 $0$，否则枚举两个球一步操作后的状态并取最小值，如果这个结果过大的话说明这两个状态间没有通路，输出 $-1$，否则输出这个结果。这部分代码如下：

```cpp
inline int getans(int X1,int Y1,int X2,int Y2){
	return min(dis[t[X1][Y1][0]][t[X2][Y2][0]],min(dis[t[X1][Y1][1]][t[X2][Y2][1]],min(dis[t[X1][Y1][2]][t[X2][Y2][2]],dis[t[X1][Y1][3]][t[X2][Y2][3]])));
}
……
for(int i=1,X1,X2,Y1,Y2;i<=Q;i++){
    scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
    if(X1==X2&&Y1==Y2) printf("0\n");//重合
    else{
        int ans=getans(X1,Y1,X2,Y2);
        if(ans>=1e9) printf("-1\n");//无解
        else printf("%d\n",ans);//有解
    }
}
```

至此，这道题就被我们解决了。化点为状态，以及在状态之间进行连边以便于转移的操作非常巧妙，直接思考。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305,M=2005,MN=1e5+5;
struct edge{
	int to,nxt;
}e[MN];
int a[N][N],dis[M][M],id[N][N],t[M][M][4];
int n,m,Q,cnt,head[M][4],tot;
inline void add(int u,int v,int p){
	e[++cnt].to=v;
	e[cnt].nxt=head[u][p];
	head[u][p]=cnt;
}
inline bool check(int i,int j){
	if(a[i-1][j]||a[i+1][j]||a[i][j-1]||a[i][j+1]) return true;
	return false;
}
inline int getans(int X1,int Y1,int X2,int Y2){
	return min(dis[t[X1][Y1][0]][t[X2][Y2][0]],min(dis[t[X1][Y1][1]][t[X2][Y2][1]],min(dis[t[X1][Y1][2]][t[X2][Y2][2]],dis[t[X1][Y1][3]][t[X2][Y2][3]])));
}
queue<pair<int,int> > q;
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		a[x][y]=1;
	}
	for(int i=1;i<=n;i++) a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!a[i][j]&&check(i,j)) id[i][j]=++tot;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
			t[i][j][0]=a[i][j-1]?id[i][j]:t[i][j-1][0],
			t[i][j][1]=a[i-1][j]?id[i][j]:t[i-1][j][1];
	for(int i=n;i;i--)
		for(int j=n;j;j--)
			t[i][j][2]=a[i][j+1]?id[i][j]:t[i][j+1][2],
			t[i][j][3]=a[i+1][j]?id[i][j]:t[i+1][j][3];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(id[i][j]) for(int k=0;k<=3;k++) add(t[i][j][k],id[i][j],k);
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			dis[i][j]=1e9+7;
	for(int i=1;i<=tot;i++) q.push(make_pair(i,i)),dis[i][i]=1;
	while(!q.empty()){
		pair<int,int> x=q.front();q.pop();
		for(int k=0;k<=3;k++){
			for(int i=head[x.first][k];i;i=e[i].nxt){
				for(int j=head[x.second][k];j;j=e[j].nxt){
					int u=e[i].to,v=e[j].to;
					if(dis[u][v]==1e9+7){
						dis[u][v]=dis[x.first][x.second]+1,
						q.push(make_pair(u,v));
					}
				}
			}
		}
	}
	for(int i=1,X1,X2,Y1,Y2;i<=Q;i++){
		scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
		if(X1==X2&&Y1==Y2) printf("0\n");
		else{
			int ans=getans(X1,Y1,X2,Y2);
			if(ans>=1e9) printf("-1\n");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
```



---

## 作者：翼德天尊 (赞：22)

# [P7473 重力球](https://www.luogu.com.cn/problem/P7473) 题解

**update1：修改了一些 latex 的问题。**

**update2：修改了关于 “/” 的歧义问题**

------------
## 前置知识

[bfs 基础](https://www.luogu.com.cn/blog/5y2d1n/guan-yu-guang-sou)

[图论基础](https://www.luogu.com.cn/blog/5y2d1n/guan-yu-tu-lun)

## 题解正文

### 题目大意

给定一个 $n\times n$ 的地图，里面有若干障碍物。

又给定 $q$ 对小球。对于每对小球，我们可以进行若干次操作，每次操作可以选定一个方向，使小球一直向这个方向滚动直到碰到障碍物为止。

求出每对小球到达同一个位置的最少操作次数。特殊地，如果两个小球的初始位置相同，输出 $0$；如果两个小球无法到达同一个位置，输出 $-1$。

### 方法讨论

首先看到这种 “地图题”，很自然的一个念头就是用搜索来做。

但是由于 $n\le 250$ 且 $q\le 10^5$ ，所以便再次很自然的因为时间复杂度而打消了这个念头。不过我们可以看到，$m\le 250$。这说明了什么？说明最多只有 $250$ 个障碍物。

由于小球遇到障碍物才会停止运动，所以小球只会停到地图内部的边缘或者是障碍物的四周。也就是说，单个小球的状态最多只有 $4n+4m=2000$ 个，两个小球的状态总和也就只有 $2000^2=4\times 10^6$ 个。

那么另一个念头再次出现了——如果我们把所有状态构成一个图，运用最短路算法，是不是可以做出这道题呢？

于是，便有了下面这些操作。

### 分步讲解

#### 1. 输入并标记

输入阶段，我们考虑建立两个数组，分别是 $ma$ 和 $can$，表示该位置是否有障碍物以及该位置是否可以停留小球（在障碍物四周或地图边缘）。

```cpp
n=read(),m=read(),q=read();
for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)//将没有障碍物的坐标标为1可以防止越界
		ma[i][j]=1;
for (int i=1;i<=m;i++){
	int x=read(),y=read();
	ma[x][y]=0;//标记障碍物
	for (int j=0;j<4;j++){
		int xx=x+dx[j],yy=y+dy[j];
		can[xx][yy]=1;//标记可行点
	}
}
for (int i=1;i<=n;i++) can[i][1]=can[i][n]=can[n][i]=can[1][i]=1;//标记地图边缘
```

#### 2. 预处理

因为询问次数 $q\le 10^5$，而时间复杂度显然支撑不了这个数组，所以我们可以想到单次询问的时间复杂度一定是很低的。于是，我们就需要用到预处理了。

考虑预先处理好地图上每一个坐标向四周滚动会走到的坐标，用 $ne$ 数组储存。因为我们每次向四个方向滚动一格坐标的变化是固定的，所以我们可以考虑设置一对方向数组 $dx$，$dy$，两个数组对应下表的内容即为向某个方向移动一格后 $x$，$y$ 坐标的变化。

```cpp
//方向数组
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
//分别表示 右 下 左 上
```
```cpp
//查询函数
int find(int x,int y,int f){//寻找坐标为x,y的点向方向f（方向数组的对应下标）滚动后到达的坐标
	int xx=x+dx[f],yy=y+dy[f];//求出移动后的坐标
	if (ma[xx][yy]){
		ne[x][y][f]=find(xx,yy,f);//递归顺带求出路上的坐标向该方向滚动后到达的坐标
		return ne[x][y][f];
	}else ne[x][y][f]=(f==0||f==2)?y:x;//无法再向前了就更新
   //如果f=0,2，说明是向右向左，只会改变y坐标，所以将ne赋值为y；同理，当f=1,3时，将ne赋值为x.
	return (f==0||f==2)?y:x;
}
```
```cpp
//主函数内
for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
		for (int f=0;f<=1;f++)
			if (ma[i][j]&&!ne[i][j][f])//如果不是障碍物且没有更新过ne数组
				ne[i][j][f]=find(i,j,f);
for (int i=n;i>=1;i--)
	for (int j=n;j>=1;j--)
		for (int f=2;f<=3;f++)
			if (ma[i][j]&&!ne[i][j][f])
				ne[i][j][f]=find(i,j,f);
```
**补充：** 为什么要正着遍历一边再倒着遍历一遍呢？

由于我们在使用 find 函数时已经顺带将路径中的每一个坐标的 $ne$ 数组都更新了，所以我们在循环的时候加了一个特判，减少复杂度。当 $f=0$ 或 $2$ 时，即向右向下走时，为了尽可能多的顺带处理，我们正着遍历（从上到下，从左到右的遍历）；当 $f=1$ 或 $3$ 时，即向左向上走时，与上同理，我们会倒着遍历（从下到上，从右到左遍历）。

#### 3. 建图

可能从这里就开始难以理解了……我尽量讲得简单一点。

按照上述的思路，我们要实现状态的转移。因为是状态的转移，我们当然要知道这个状态到底是什么。所以我们需要用到一个叫 hash 的东西。首先，我们根据枚举顺序，给每一个可行点编号 $h$。然后，因为一共有两个小球，所以状态当然也是两个小球的总和。根据上述的分析，我们可以发现最多有 $2000$ 个可行点，所以我们可以用第一个小球所在的格子编号乘上2000再加上第二个格子的编号，这样我们就可以保证每一个状态互不相同。

代码实现即：

```cpp
int get_hash(int a1,int b1,int a2,int b2){
//找到当第一个点坐标为a1,b1，第二个点坐标为a2,b2时的h值
	if (a1>a2||(a1==a2&&b1>b2)){//使两个小球的坐标有顺序
		swap(a1,a2),swap(b1,b2);
	}
	int x=ha[a1][b1],y=ha[a2][b2];
	return x*2001+y;//hash
}
```


而既然是图论，我们当然要有起始点和终止点。如果按照正常思路，我们可能需要将枚举所有的状态作为起始点，当两个小球重合时的状态作为终点。但很明显，这样非常复杂。所以我们可以考虑将图倒过来，由终点作为起点进行连边。

这就是一个多源最短路问题。

因为两个小球重合时的状态不止一个，所以我们可以先设置一个虚拟的总源点，向所有的重合状态连接一条有向边。即：

```cpp
for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
		if (can[i][j]&&ma[i][j]){//如果不是障碍物且为可行点
			id[++cnt]=node(i,j);//设置可行点信息
			ha[i][j]=cnt;//给可行点hash编号
			int tmp=get_hash(i,j,i,j);//找到h值
			adde(s,tmp);//由总源点向其连边
		}
```

然后我们就可以枚举所有的状态（可行点两两配对），然后由该状态延伸状态，并由延伸到的状态向该状态连边（倒着建图）。

```cpp
for (int i=1;i<=cnt;i++){
	for (int j=i+1;j<=cnt;j++){
		node1 now=node1(id[i].x,id[i].y,id[j].x,id[j].y);//找到该状态
		int to=get_hash(id[i].x,id[i].y,id[j].x,id[j].y);//找到h值
		for (int i=0;i<4;i++){//枚举4个方向
			node1 next=now;
			if (i==0||i==2) next.b1=ne[next.a1][next.b1][i],next.b2=ne[next.a2][next.b2][i];
			//如果是向右向左，则修改y坐标
			else next.a1=ne[next.a1][next.b1][i],next.a2=ne[next.a2][next.b2][i];
			//否则修改x坐标
			adde(get_hash(next.a1,next.b1,next.a2,next.b2),to);//连边
		}
	}
}
```

#### 4. bfs 搜索

图都建好了……就该搜索处理了。

考虑从原点开始，进行 bfs。代码如下：

```cpp
void bfs(){
	queue<int> q;//建立队列
	q.push(s);//推入起始点
	vis[s]=1,dis[s]=-1;//标记起始点，因为起始点是虚拟的，所以距离为-1
	//dis数组表示距离两个小球重合状态的长度
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if (!vis[v]){
				vis[v]=1;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
}
```

#### 5.查询

我们现在已经知道了每一个状态到答案的距离了，那么查询就好办了。我们可以考虑找到向四个方向到达终点的最短距离，然后取最小值即可。特别注意的是，如果向该方向延伸到的状态与现状态不相同（即向这个方向走一格不是障碍物），还需要将距离+1。

```cpp
int query(int a1,int b1,int a2,int b2){
	if (a1==a2&&b1==b2) return 0;//特判初始在同一个坐标
	node1 now=node1(a1,b1,a2,b2);//设置现在状态
	int ans=INF;//答案设置为极大值
	for (int i=0;i<4;i++){
		node1 next=now;
		if (i==0||i==2) next.b1=ne[next.a1][next.b1][i],next.b2=ne[next.a2][next.b2][i];
		//如果向右向下则修改y坐标
		else next.a1=ne[next.a1][next.b1][i],next.a2=ne[next.a2][next.b2][i];
		//如果向上向左则修改x坐标
		int tmp=get_hash(next.a1,next.b1,next.a2,next.b2);
		//找到现状态的h值
		if (vis[tmp]){//如果这个点被最短路搜过
			if (next==now) ans=min(ans,dis[tmp]);//如果向该方向走一格后的状态与现状态相同，则不额外+1
			else ans=min(ans,dis[tmp]+1);
		}
	}
	if (ans!=INF) return ans;//如果被修改过则说明有解，输出答案
	return -1;//否则输出-1
}
```

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2005
#define M 50000005 
#define INF 2147483647
int n,m,q,ne[N][N][4],cnt,s,ha[N][N],head[M],tot,dis[M];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
bool ma[N][N],can[N][N],vis[M];
struct node{
	int x,y;
	node (int x=0,int y=0)
		:x(x),y(y){}
}id[N];
struct node1{
	node1(){} 
	int a1,b1,a2,b2;
	node1 (int a1=0,int b1=0,int a2=0,int b2=0)
		:a1(a1),b1(b1),a2(a2),b2(b2){}
	friend bool operator == (node1 x,node1 y){
		return (x.a1==y.a1)&&(x.a2==y.a2)&&(x.b1==y.b1)&&(x.b2==y.b2);
	}
};
struct node2{
	int to,next;
	node2 (int to=0,int next=0)
		:to(to),next(next){} 
}e[M];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar(); 
	}
	return w*f;
}
int find(int x,int y,int f){
	int xx=x+dx[f],yy=y+dy[f];
	if (ma[xx][yy]){
		ne[x][y][f]=find(xx,yy,f);
		return ne[x][y][f];
	}else ne[x][y][f]=(f==0||f==2)?y:x;
	return (f==0||f==2)?y:x;
}
int get_hash(int a1,int b1,int a2,int b2){
	if (a1>a2||(a1==a2&&b1>b2)){
		swap(a1,a2),swap(b1,b2);
	}
	int x=ha[a1][b1],y=ha[a2][b2];
	return x*2001+y;
}
void adde(int u,int v){
	e[++tot]=node2(v,head[u]);
	head[u]=tot;
}
void build(){
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (can[i][j]&&ma[i][j]){
				id[++cnt]=node(i,j);
				ha[i][j]=cnt;
				int tmp=get_hash(i,j,i,j);
				adde(s,tmp);
			}
	for (int i=1;i<=cnt;i++){
		for (int j=i+1;j<=cnt;j++){
			node1 now=node1(id[i].x,id[i].y,id[j].x,id[j].y);
			int to=get_hash(id[i].x,id[i].y,id[j].x,id[j].y);
			for (int i=0;i<4;i++){
				node1 next=now;
				if (i==0||i==2) next.b1=ne[next.a1][next.b1][i],next.b2=ne[next.a2][next.b2][i];
				else next.a1=ne[next.a1][next.b1][i],next.a2=ne[next.a2][next.b2][i];
				adde(get_hash(next.a1,next.b1,next.a2,next.b2),to);
			}
		}
	}
}
void bfs(){
	queue<int> q;
	q.push(s);
	vis[s]=1,dis[s]=-1;
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if (!vis[v]){
				vis[v]=1;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
}
int query(int a1,int b1,int a2,int b2){
	if (a1==a2&&b1==b2) return 0;
	node1 now=node1(a1,b1,a2,b2);
	int ans=INF;
	for (int i=0;i<4;i++){
		node1 next=now;
		if (i==0||i==2) next.b1=ne[next.a1][next.b1][i],next.b2=ne[next.a2][next.b2][i];
		else next.a1=ne[next.a1][next.b1][i],next.a2=ne[next.a2][next.b2][i];
		int tmp=get_hash(next.a1,next.b1,next.a2,next.b2);
		if (vis[tmp]){
			if (next==now) ans=min(ans,dis[tmp]);
			else ans=min(ans,dis[tmp]+1);
		}
	}
	
	if (ans!=INF) return ans;
	return -1;
}
int main(){
	n=read(),m=read(),q=read();
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			ma[i][j]=1;
		}
	}
	for (int i=1;i<=m;i++){
		int x=read(),y=read();
		ma[x][y]=0;
		for (int j=0;j<4;j++){
			int xx=x+dx[j],yy=y+dy[j];
			can[xx][yy]=1;
		}
	}
	for (int i=1;i<=n;i++) can[i][1]=can[i][n]=can[n][i]=can[1][i]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int f=0;f<=1;f++)
				if (ma[i][j]&&!ne[i][j][f])
					ne[i][j][f]=find(i,j,f);
	for (int i=n;i>=1;i--)
		for (int j=n;j>=1;j--)
			for (int f=2;f<=3;f++)
				if (ma[i][j]&&!ne[i][j][f])
					ne[i][j][f]=find(i,j,f);
	build();
	bfs();
	for (int i=1;i<=q;i++){
		int a=read(),b=read(),c=read(),d=read();
		printf("%d\n",query(a,b,c,d));
	}
	return 0;
} 
```


---

## 作者：Star_Cried (赞：9)

## P7473 [NOI Online 2021 入门组] 重力球

### 题意

给你一个正方形平面，某些位置有障碍，对于平面上两个球，每次你可以改变重力方向使两个球下落到最底端，求使两个球位置重合的最小改变重力次数。障碍固定，多次询问两个球的位置。

### 思路

考虑最暴力的想法，总共有 $n^4$ 种状态，即两个球的坐标。

考虑优化状态数，发现只有障碍物（边界）旁边（四联通）的位置才有用。实际最大位置数为 $250\times 4+250\times 4=2000$ 左右。那么实际状态数最大为 $2000\times 2000=4000000$ 左右。

我们把这些状态看做点，每个点只能有四条出边，那么边数和点数同阶。这样我们就有了另外一个暴力的想法：对于每个初始局面，暴力 BFS。

因为有多组询问考虑优化。实际上最终重合的状态有 $2000$ 个，我们反向建边，然后从这些点开始 BFS 出到所有状态的最小代价。每次查询的时候枚举第一次改变重力的方向即可。（注意判重合）

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=255,maxm=2010;
	int n,m,Q,tot,a[maxn][maxn],t[maxn][maxn][4];
	unsigned dis[maxm][maxm];
	vector<int> to[maxm][4];
	inline void addedge(int a,int b,int c){to[a][c].push_back(b);}
	inline void work(){
		n=read(),m=read(),Q=read();
		while(m--) a[read()][read()]=-1;
		for(int i=1;i<=n;i++) a[0][i]=a[i][0]=a[n+1][i]=a[i][n+1]=-1;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
			if(!a[i][j] and (a[i-1][j]==-1 or a[i+1][j]==-1 or a[i][j-1]==-1 or a[i][j+1]==-1))
				a[i][j]=++tot;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) t[i][j][0]=a[i][j-1]==-1?a[i][j]:t[i][j-1][0],t[i][j][1]=a[i-1][j]==-1?a[i][j]:t[i-1][j][1];
		for(int i=n;i;i--) for(int j=n;j;j--) t[i][j][2]=a[i][j+1]==-1?a[i][j]:t[i][j+1][2],t[i][j][3]=a[i+1][j]==-1?a[i][j]:t[i+1][j][3];
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]>0) for(int k=0;k<4;k++) addedge(t[i][j][k],a[i][j],k);
		static pair<int,int> q[maxm*maxm];
		int hd=0,tl=0;
		memset(dis,-1,sizeof dis);
		for(int i=1;i<=tot;i++) q[++tl]=make_pair(i,i),dis[i][i]=1;
		while(hd<tl){
			pair<int,int> x=q[++hd];
			for(int i=0;i<4;i++) for(auto u:to[x.first][i]) for(auto v:to[x.second][i]) if(dis[u][v]==-1) dis[u][v]=dis[x.first][x.second]+1,q[++tl]=make_pair(u,v);
		}
		while(Q--){
			int x1=read(),y1=read(),x2=read(),y2=read();
			if(x1==x2 and y1==y2) puts("0");
			else printf("%d\n",min({dis[t[x1][y1][0]][t[x2][y2][0]],dis[t[x1][y1][1]][t[x2][y2][1]],dis[t[x1][y1][2]][t[x2][y2][2]],dis[t[x1][y1][3]][t[x2][y2][3]]}));
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```





---

## 作者：Night_Bringer (赞：8)

# 题目大意
在一个 $n\times n$ 的矩形中，题目会给出 $m$ 个障碍物。有两个小球，你可以选定四个方向（上下左右）的其中一个，小球会朝着这四个方向一直滚动，直到遇到障碍物或是矩形的边缘停止。有 $q$ 条形如 $a$ $b$ $c$ $d$ 的询问，代表两个小球的坐标 $(a,b)$ 和 $(c,d)$ ，求多少步，小球会重叠。

[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14596516.html)
# 思路
## 55pts
首先考虑暴力，先预处理出所有点滚动会滚动到哪里，写四个 dfs 完事。
```cpp
int L(int i, int j) {//向左滚
	if(stn[i][j - 1]) {
		l[i][j] = L(i, j - 1);
		return l[i][j];
	}
	else
		l[i][j] = j;
	return j;
}
int U(int i, int j) {//向上滚
	if(stn[i - 1][j]) {
		u[i][j] = U(i - 1, j);
		return u[i][j];
	}
	else
		u[i][j] = i;
	return i;
}
int R(int i, int j) {//向右滚
	if(stn[i][j + 1]) {
		r[i][j] = R(i, j + 1);
		return r[i][j];
	}
	else
		r[i][j] = j;
	return j;
}
int D(int i, int j) {//向下滚
	if(stn[i + 1][j]) {
		w[i][j] = D(i + 1, j);
		return w[i][j];
	}
	else
		w[i][j] = i;
	return i;
}
```
主函数中：
```cpp
for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= n; j++) {
		if(!stn[i][j])//小球不会到障碍物上
			continue;
		if(!r[i][j])
			R(i, j);
		if(!w[i][j])
			D(i, j);
	}
}
for(int i = n; i >= 1; i--) {
	for(int j = n; j >= 1; j--) {
		if(!stn[i][j])//小球不会到障碍物上
			continue;
		if(!l[i][j])
			L(i, j);
		if(!u[i][j])
			U(i, j);
	}
}
```
然后无脑 BFS ，TLE 。（ $55pts$ 亲测）

**主体部分**
```cpp
void BFS() {
	q.push(Node(a, b, c, d, 0));
	if(a == c && b == d) {
		printf("0\n");
		return;
	}
	while(!q.empty()) {
		Node now = q.front(); q.pop();
		Node next = now;
		next.step++;
		next.Y_1 = l[next.X_1][next.Y_1];
		next.Y_2 = l[next.X_2][next.Y_2];
		if(next.X_1 == next.X_2 && next.Y_1 == next.Y_2) {
			printf("%d\n", next.step);
			return;
		}
		int tmp = Get_Hash(next.X_1, next.X_2, next.Y_1, next.Y_2);
		if(!f[tmp]) {
			f[tmp] = 1;
			q.push(next);
		}
		
		
		next = now;
		next.step++;
		next.Y_1 = r[next.X_1][next.Y_1];
		next.Y_2 = r[next.X_2][next.Y_2];
		if(next.X_1 == next.X_2 && next.Y_1 == next.Y_2) {
			printf("%d\n", next.step);
			return;
		}
		tmp = Get_Hash(next.X_1, next.X_2, next.Y_1, next.Y_2);
		if(!f[tmp]) {
			f[tmp] = 1;
			q.push(next);
		}
		
		
		next = now;
		next.step++;
		next.X_1 = u[next.X_1][next.Y_1];
		next.X_2 = u[next.X_2][next.Y_2];
		if(next.X_1 == next.X_2 && next.Y_1 == next.Y_2) {
			printf("%d\n", next.step);
			return;
		}
		tmp = Get_Hash(next.X_1, next.X_2, next.Y_1, next.Y_2);
		if(!f[tmp]) {
			f[tmp] = 1;
			q.push(next);
		}
		
		next = now;
		next.step++;
		next.X_1 = w[next.X_1][next.Y_1];
		next.X_2 = w[next.X_2][next.Y_2];
		if(next.X_1 == next.X_2 && next.Y_1 == next.Y_2) {
			printf("%d\n", next.step);
			return;
		}
		tmp = Get_Hash(next.X_1, next.X_2, next.Y_1, next.Y_2);
		if(!f[tmp]) {
			f[tmp] = 1;
			q.push(next);
		}
	}
	printf("-1\n");
}
```
## 100pts
考虑逆推求出所有状态的最小满足条件步数。

不难发现，经过一次的滚动后，小球会落在障碍物的旁边或是矩阵的边缘。一共有 $(4m+4n)$ 中状态，那么两个求就一共有 $(4m+4n)^2$ 种状态，可以往四边滚，那么可以将会与其他的四种状态有联系。

在考虑将这些点进行 $hash$ 相连。那么就成为了一个多源最短路问题。将一个超级源点 $s$ 连向每个两小球重叠的哈希值连边。同时当前状态与下一个状态建立反边，跑最短路即可。

由于边长都为 $1$ ，则可以使用 BFS 来求最短路，时间复杂度为 $O(4(4m+4n)^2)$  。

最后是查询的问题，也比较简单， 分四个方向先滚动一次，那么步数就是 $dis[tmp]+1$ （ $dis$ 记录最短路， $tmp$ 为当前状态的哈希值）。但值得注意的是，若滚动前和滚动后两个小球的位置没有改变，则不需要加一。

细节代码上有注释。
# Code
```cpp
#include <queue>
#include <cstdio>
using namespace std;
#define INF 0x3f3f3f3f
const int MAXN = 2e3 + 5;
const int MAXM = 5e7 + 5;
struct Node {//小球的位置
	int X_1, Y_1, X_2, Y_2;
	Node() {}
	Node(int A, int B, int C, int D) {
		X_1 = A;
		Y_1 = B;
		X_2 = C;
		Y_2 = D;
	}
	friend bool operator == (Node x, Node y) {
		return (x.X_1 == y.X_1) && (x.X_2 == y.X_2) && (x.Y_1 == y.Y_1) && (x.Y_2 == y.Y_2);
	}
};
struct Edge {//链式前向星存边，别用vector
	int To, Next;
};
Edge edge[MAXM];
int head[MAXM];
int u[MAXN][MAXN], w[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN];
bool stn[MAXN][MAXN], can[MAXN][MAXN], vis[MAXM];
int dis[MAXM], Hash[MAXN][MAXN];
pair<int, int> id[MAXN];
queue<int> q;
int x[MAXN], y[MAXN];
int n, m, s, Q;
int a, b, c, d;
int tot, cnt;
void Addedge(int u, int v) {//加入边
	edge[++tot].Next = head[u];
	edge[tot].To = v;
	head[u] = tot;
}
int Get_Hash(int A, int B, int C, int D) {//哈希值
	if(A > C || (A == C && B > D)) {//注意先排序，再hash
		swap(A, C);
		swap(B, D);
	}
	int x = Hash[A][B];
	int y = Hash[C][D];
	return x * 2001 + y;//共有(4n+4m)种状态，大概是2000，这样不会发生冲突
}
int L(int i, int j) {//向左走
	if(stn[i][j - 1]) {
		l[i][j] = L(i, j - 1);
		return l[i][j];
	}
	else
		l[i][j] = j;
	return j;
}
int U(int i, int j) {//向上走
	if(stn[i - 1][j]) {
		u[i][j] = U(i - 1, j);
		return u[i][j];
	}
	else
		u[i][j] = i;
	return i;
}
int R(int i, int j) {//向右走
	if(stn[i][j + 1]) {
		r[i][j] = R(i, j + 1);
		return r[i][j];
	}
	else
		r[i][j] = j;
	return j;
}
int D(int i, int j) {//向下走
	if(stn[i + 1][j]) {
		w[i][j] = D(i + 1, j);
		return w[i][j];
	}
	else
		w[i][j] = i;
	return i;
}
void Build() {//建图
	int tmp;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(can[i][j] && stn[i][j]) {//是障碍物边缘且不失障碍物
				id[++cnt].first = i;
				id[cnt].second = j;
				Hash[i][j] = cnt;
				tmp = Get_Hash(i, j, i, j);
				Addedge(s, tmp);//超级源点连结果
			}
	for(int i = 1; i <= cnt; i++) {
		for(int j = i + 1; j <= cnt; j++) {//下一状态连边，注意是反向边
			Node now = Node(id[i].first, id[i].second, id[j].first, id[j].second);
			int to = Get_Hash(id[i].first, id[i].second, id[j].first, id[j].second);
			Node next = now;
			next.Y_1 = l[next.X_1][next.Y_1];
			next.Y_2 = l[next.X_2][next.Y_2];
			int tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
			Addedge(tmp, to);
			next = now;
			next.Y_1 = r[next.X_1][next.Y_1];
			next.Y_2 = r[next.X_2][next.Y_2];
			tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
			Addedge(tmp, to);
			next = now;
			next.X_1 = u[next.X_1][next.Y_1];
			next.X_2 = u[next.X_2][next.Y_2];
			tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
			Addedge(tmp, to);
			next = now;
			next.X_1 = w[next.X_1][next.Y_1];
			next.X_2 = w[next.X_2][next.Y_2];
			tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
			Addedge(tmp, to);
		}
	}
}
void Shortestpast() {//多源最短路
	q.push(s);
	vis[s] = 1;
	dis[s] = -1;
	while(!q.empty()) {//边长为1用BFS
		int now = q.front(); q.pop();
		for(int i = head[now]; i; i = edge[i].Next) {
			int next = edge[i].To;
			if(!vis[next]) {
				vis[next] = 1;
				dis[next] = dis[now] + 1;
				q.push(next);
			}
		}
	}
}
int Query() {
	if(a == c && b == d)//已经重叠不用滚
		return 0;
	Node now = Node(a, b, c, d);
	int tmp, res = INF;
	Node next = now;
	next.Y_1 = l[next.X_1][next.Y_1];
	next.Y_2 = l[next.X_2][next.Y_2];
	tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
	if(vis[tmp]) {//如果最短路中被标记过才更新
		if(next == now)
			res = min(res, dis[tmp]);//还是在原位置，不加1
		else
			res = min(res, dis[tmp] + 1);
	}
	next = now;
	next.Y_1 = r[next.X_1][next.Y_1];
	next.Y_2 = r[next.X_2][next.Y_2];
	tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
	if(vis[tmp]) {
		if(next == now)
			res = min(res, dis[tmp]);
		else
			res = min(res, dis[tmp] + 1);
	}
	next = now;
	next.X_1 = u[next.X_1][next.Y_1];
	next.X_2 = u[next.X_2][next.Y_2];
	tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
	if(vis[tmp]) {
		if(next == now)
			res = min(res, dis[tmp]);
		else
			res = min(res, dis[tmp] + 1);
	}
	next = now;
	next.X_1 = w[next.X_1][next.Y_1];
	next.X_2 = w[next.X_2][next.Y_2];
	tmp = Get_Hash(next.X_1, next.Y_1, next.X_2, next.Y_2);
	if(vis[tmp]) {
		if(next == now)
			res = min(res, dis[tmp]);
		else
			res = min(res, dis[tmp] + 1);
	}
	if(res != INF)
		return res;//找到答案
	return -1;//没有答案
}
int main() {
	scanf("%d %d %d", &n, &m, &Q);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			stn[i][j] = 1;
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &x[i], &y[i]);
		stn[x[i]][y[i]] = 0;//障碍物标记
		can[x[i]][y[i] + 1] = 1;//障碍物四周标记
		can[x[i] + 1][y[i]] = 1;
		can[x[i]][y[i] - 1] = 1;
		can[x[i] - 1][y[i]] = 1;
	}
	for(int i = 1; i <= n; i++)
		can[1][i] = can[n][i] = can[i][1] = can[i][n] = 1;//矩阵四周标记
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(!stn[i][j])
				continue;
			if(!r[i][j])
				R(i, j);
			if(!w[i][j])
				D(i, j);
		}
	}
	for(int i = n; i >= 1; i--) {
		for(int j = n; j >= 1; j--) {
			if(!stn[i][j])
				continue;
			if(!l[i][j])
				L(i, j);
			if(!u[i][j])
				U(i, j);
		}
	}
	Build();
	Shortestpast();
	for(int i = 1; i <= Q; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%d\n", Query());
	}
	return 0;//完结撒花
}
```

---

## 作者：天才颓废学家 (赞：7)

### 本篇题解主要是对一楼 LYC_music 大佬题解的解释说明。

显然，如果第一次看到他的题解，多数人都看不懂，（那太专业了？）

`LYC` 题解原文就不引述了。

`LYC` 大概的意思是，由于小球**遇到障碍物才会停止运动**，所以小球**只会停到地图内部的边缘**或者是**障碍物的四周**（计算 `LYC` 已有，略）。也就是说，其余的点都是无用的,我们只要将**所有有用的、能直接到达的点用边连起来**，因为小球每次要走到底，所有的边权都为 $1$ 。因为我们不知道小球会在那里相遇，所以干脆**从每个可以相遇的点倒着搜**即可，所以**建反向边跑记搜**（有可能 `vector` 会被卡。记搜能有效避免重复状态造成的时间浪费）。还有就是要**搜索状态要带方向**，不同的方向会有不同的结果。最后答案只要在四个方向里的结果中选最小的就可以了。

这里放部分思维难度比较高的（伪）代码

```cpp
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
			if (四旁至少投一边是障碍或是边缘)
				id[i][j] = ++ tot; //tot既表示符合的点的个数，这里也可表示找到的这个点给它的编号。
	for (int i = n; i >= 1; -- i)
		for (int j = n; j >= 1; -- j){
			if (! a[i][j + 1]) //这里做范例
				to[i][j][3] = to[i][j + 1][3]; // 走到下一步
				// to[i][j][k] 表示在坐标为[i][j]的点时按k方向走，下一步到的点
			else
				to[i][j][3] = id[i][j]; //这里就是这一行/列在这个方向上的终点。
			同上
		}
	一样再做其它两个方向
	for (int i = 1; i <= tot; ++ i)
		for (int j = 1; j <= tot; ++ j)
			dis[i][j] = 114514114514, dis[i][i] = 1;
	//赋初始值，注意dis[i][i]:
	  ① i表示是几号点而不是坐标； 
	  ②因为到时候要消耗一步来找第一步，干脆直接把初值赋值为 1，然后特判相等的情况更为方便

	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
			if (id[i][j])
				for (int k = 1; k <= 4; ++ k){
					int too = to[i][j][k];
					G[too][k].push_back(id[i][j]);
				} //建边
	for (int i = 1; i <= tot; ++ i)
		q.push(make_pair(i, i));
		//再次强调， i表示是几号点而不是坐标；
	接着就是记搜。
```
如果实有需要看代码，请[移步此处](https://www.luogu.com.cn/paste/kj921xjj)

---

## 作者：Evan_S (赞：4)

# P7473 重力球

说实话这题缠了我好久...足足有两个星期...[提交了78次](https://www.luogu.com.cn/record/list?pid=P7473&user=%E5%AE%8B%E5%8D%93%E6%98%95&page=1)。

因为这是图论题，自然而然地就想到用最短路。我们可以将两个小球的位置作为一个状态，然后每两个可以转移状态之间建立一条边，长度为 $1$。然后跑一遍 SPFA。

但如果每一个状态 $(x,y,x2,y2)$ 都要算到跑最短路的状态的话，显然不行，因为 $n \leq 250$，如果这样，就一共有 $n^4$ 也就是 $3,906,250,000$ 个。

这个问题如何解决：我们发现，其实有些点小球是不可以停留的。比如说下图 $A$ 点：

```
 ___ ___ ___ ___ ___
|###|###|###|###|###|
|###|###|###|###|###|
|###|   |   |   |###|
|###|___|___|___|###|
|###|   | A |   |###|
|###|___|___|___|###|
|###|   |   |   |###|
|###|___|___|___|###|
|###|###|###|###|###|
|###|###|###|###|###|
```

我们只需要记录小球可以停留的地方就可以了，小球只能停在边界或障碍旁。

所以一共有 $4(n+m)$ 个可停留区域。两个球就有 $16(n+m)^2$ 个状态。

我们只需要把这些状态来 SPFA 就可以了。

但我们每次询问不可能每次都从新算一遍答案。因为有 $q$ 次询问，而且 $1 \leq q \leq 10^5$。所以我们就需要预处理。

预处理的话，就要反向建边，然后将每一个状态 $(x, y, x, y)$ 放入 SPFA 的队列。

然后跑一边 SPFA，然后对于每一个询问 $x, y, x2, y2$，直接输出 `dis[hash(x, y, x2, y2)]`，就可以了。

### 注意事项：

1. $vector$ **太慢了，要用链式前向星**。我用 vector 来存图，结果数据 #19 一直 $TLE$。

2. **两个小球初始位置可能不在可停留区域内**，需要先枚举四个方向，再输出。

3. **两个小球初始位置可能相同**，需要直接输出 $0$。

### 献上代码：
```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct POS
{
	int x;
	int y;
};
struct edge
{
	int to,next;
};
int head[40000000];
edge e[40000000];
int headi = 1;
POS pos[2010];
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};
bool board[300][300]; 
bool can[300][300]; 
int n, m, q;
int nxt[300][300][4];
int has[2010][2010];
int cnt;
queue<int> que;
int dis[4100000];
bool inque[4100000];
void adde(int ai,int bi)
{
	e[headi].to=bi;
	e[headi].next=head[ai];
	head[ai]=headi++;
}
void bfs()
{
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		inque[u] = false;
		for(int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			if (dis[v] > dis[u] + 1)
			{
				dis[v] = dis[u] + 1;
				if(!inque[v])
				{
					inque[v] = true;
					que.push(v);
				}
			}
		}
	}
}
inline int hash_of(int x1, int y1, int x2, int y2)
{
	if (x1 > x2 || (x1 == x2 && y1 > y2))
	{
		x1 = x1 ^ x2;
		x2 = x1 ^ x2;
		x1 = x1 ^ x2;
		y1 = y1 ^ y2;
		y2 = y1 ^ y2;
		y1 = y1 ^ y2;
	}
	return (has[x1][y1] << 11) | has[x2][y2];
}

int find(const int x, const int y, const int dir)
{
    int& NXT = nxt[x][y][dir];
    if (NXT)
        return NXT;
	if(!board[x + dx[dir]][y + dy[dir]])
	{
		return NXT = find(x + dx[dir], y + dy[dir], dir);
	}
	else
	{
		if ((dir & 1) == 0)
		{
			NXT = y;
		}
		else
		{
			NXT = x;
		}
		return NXT;
	}
}

inline int read() 
{
    int x = 0, f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = -1;c = getchar();}
    while(c >= '0'&&c <= '9') {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}
int main()
{
	memset(dis, 0x3f, sizeof(dis));
	n = read();
	m = read();
	q = read();
	for(int i = 1; i <= n; i++)
	{
		board[i][n + 1] = 1;
		board[n + 1][i] = 1;
		board[i][0] = 1;
		board[0][i] = 1;
		can[1][i] = 1;
		can[i][1] = 1;
		can[i][n] = 1;
		can[n][i] = 1;
	}
	for(int i = 0; i < m; i++)
	{
		int x, y;
		x = read();
		y = read();
		board[x][y] = 1;
		can[x][y] = false;
		if (!board[x + 1][y]) can[x + 1][y] = 1;
		if (!board[x - 1][y]) can[x - 1][y] = 1;
		if (!board[x][y + 1]) can[x][y + 1] = 1;
		if (!board[x][y - 1]) can[x][y - 1] = 1;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
            if (!board[i][j] && can[i][j])
			{
				if(!nxt[i][j][0])
				{
					find(i, j, 0);
				}
				if(!nxt[i][j][1])
				{
					find(i, j, 1);
				}
				if(!nxt[i][j][2])
				{
					find(i, j, 2);
				}
				if(!nxt[i][j][3])
				{
					find(i, j, 3);
				}
			}
			
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(can[i][j])
			{
				pos[cnt] = {i, j};
				has[i][j] = cnt++;
			}
		}
	}
	for(int i = 0; i < cnt; i++)
	{
		for(int j = i + 1; j < cnt; j++)
		{
			for(int k = 0; k < 4; k++)
			{
				int hashxy = hash_of(pos[i].x, pos[i].y, pos[j].x, pos[j].y);
				int next1 = nxt[pos[i].x][pos[i].y][k];
				int next2 = nxt[pos[j].x][pos[j].y][k];
				if((k&1) == 0)
				{
					adde(hash_of(pos[i].x, next1, pos[j].x, next2), hashxy);
				}
				else
				{
					adde(hash_of(next1, pos[i].y, next2, pos[j].y), hashxy);
				}
			}
		}
	    int hash = hash_of(pos[i].x, pos[i].y, pos[i].x, pos[i].y);
		que.push(hash);
		dis[hash] = 0;
		inque[hash] = true;
	}
	bfs();
	for(int i = 0; i < q; i++)
	{
		int x1, y1, x2, y2;
		x1 = read();
		y1 = read();
		x2 = read();
		y2 = read();
		if(x1 == x2 && y1 == y2)
		{
			cout << 0 << endl;
			continue;
		}
		int ans = 0x3f3f3f3f;
		for(int j = 0; j < 4; j++)
		{
			if((j & 1) == 0)
			{
			    int d = dis[hash_of(x1, nxt[x1][y1][j], x2, nxt[x2][y2][j])];
				if(nxt[x1][y1][j] == y1 && nxt[x2][y2][j] == y2)
				{
					ans = min(ans, d);
				}
				else
				{
					ans = min(ans, d + 1);
				}
			}
			else
			{
			    int d = dis[hash_of(nxt[x1][y1][j], y1, nxt[x2][y2][j], y2)];
				if(nxt[x1][y1][j] == x1 && nxt[x2][y2][j] == x2)
				{
					ans = min(ans, d);
				}
				else
				{
					ans = min(ans, d + 1);
				}
			}
		}
		if(ans == 0x3f3f3f3f)
		{
			printf("-1\n");
		}
		else
		{
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：hzx360 (赞：3)

前言：感谢审核员百忙中审核 MnZn 题解。

# 正文
可以发现这是个最短路的题目，但是图上最多 $250^2$ 个点，这么多点还要求最短路，复杂度直接炸了。

但是进一步思考，这个球每次会落到障碍旁。也就是说即使球初始位置不在障碍物旁，它经过一次下落后就会一直贴着障碍物走。

所以实际上有用的点就只有障碍物旁的点，做多 $4n+4m$ 个，不超过 $2000$。

优化后我们就可以用这些点去建图，然后考虑去求最短路了。

**Tip**：为方便表示下面我把这些实际有用的点叫**标记点**。

## step1 预处理
把**标记点**找出来，然后记录一下图上每一个点（包括**标记点**和非标记点）向上/下/左/右落会落在哪里。
```
int id(int x,int y){return n*(x-1)+y;}
void init(){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int x,y;cin>>x>>y;
		flag[x][y]=1;
	}
	for(int i=1;i<=n;i++) flag[0][i]=flag[n+1][i]=flag[i][0]=flag[i][n+1]=1;//边界也算障碍物
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(flag[i][j]) continue;
			if(flag[i-1][j] or flag[i+1][j] or flag[i][j+1] or flag[i][j-1]) number[i][j]=++num;//判断是否为标记点
		}
	}
	for(int i=1;i<=n;i++){
		int posj=0;
		for(int j=1;j<=n;j++){
			if(flag[i][j]) posj=j;
			else a[id(i,j)].lt=number[i][posj+1];
		}
		posj=n+1;
		for(int j=n;j>=1;j--){
			if(flag[i][j]) posj=j;
			else a[id(i,j)].rt=number[i][posj-1];
		}
	}
	for(int j=1;j<=n;j++){
		int posi=0;
		for(int i=1;i<=n;i++){
			if(flag[i][j]) posi=i;
			else a[id(i,j)].up=number[posi+1][j];
		}
		posi=n+1;
		for(int i=n;i>=1;i--){
			if(flag[i][j]) posi=i;
			else a[id(i,j)].down=number[posi-1][j];
		}
	}
    //这里求所有点向上/下/左/右落会落在那个点，看似很长但都是复制粘贴
}
```
这里比较简单，注意细节就好了。

## step2 建图 & 最短路
注意：这里的最短路是对于**标记点的**而言的（不关非标记点的事儿），非标记点的最短路你用一步跳到**标记点**上就行。


------------

闲话：这里其实我最先考虑的是 floyed 因为有 $10^5$ 次询问点对的最短路，最短路算法里我就只能想到它了。

但很快我又发现不行，因为两个点要同时往一个方向跑，而它 floyed 又维护不了。

于是我想到这是在图里游走的题，就试了试 bfs（还真可以）。


------------

如果两个点用 bfs 游走猴年马月才会相遇啊，所以正难则反，在 bfs 中以两点相遇点为起点，两个点不断往外同方向跳（扩展），这样就可以求出任意两点的最短路啦。

#### 部分代码：
```
void add(int k,int x,int y){
	ne[++tot]=head[k][x];
	to[tot]=y;
	head[k][x]=tot;
}//每个方向上跳过来的点要有一个集合
void build(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!number[i][j]) continue;
			add(1,a[id(i,j)].up,number[i][j]);//向上跳
			add(2,a[id(i,j)].down,number[i][j]);//向下跳
			add(3,a[id(i,j)].lt,number[i][j]);//向左跳
			add(4,a[id(i,j)].rt,number[i][j]);//向右跳
			//注意这里是着陆点向起跳点连边,因为以相遇点为起点，所以相当于是反着跳回去，于是连反边
		}
	} 
}
struct data{int x,y;};queue<data>dq;
int dis[N][N];
void work(){
	for(int i=1;i<=num;i++) for(int j=1;j<=num;j++) dis[i][j]=inf;
	for(int i=1;i<=num;i++) dq.push((data){i,i}),dis[i][i]=1;//这里dis直接赋1，因为除非这两个点是同一个点，不然肯定是要耗费一步跳到其他点上的
	while(!dq.empty()){
		data u=dq.front();dq.pop();
		int x=u.x,y=u.y;
		for(int k=1;k<=4;k++){
			for(int i=head[k][x];i;i=ne[i]) for(int j=head[k][y];j;j=ne[j]){
					int u=to[i],v=to[j];
					if(dis[u][v]>=inf){
					dis[u][v]=dis[v][u]=dis[x][y]+1;
               		//dis[u][v]是等于dis[v][u]的，所以这样赋值可以显著提高速度(3.94s->2.86s)
					dq.push((data){u,v}); 
				}
			}
		}
	}
}
```
## step3 输出答案
分两类：

(1) 两点重合，直接输出 $0$ 即可。

(2) 两点不重合：枚举第一步往哪个方向跳，求最小值即可。
```
int D(int x,int y){return dis[x][y];}
void out(){
	while(q--){
		int aa,b,c,d;cin>>aa>>b>>c>>d;
		if(aa==c and b==d) puts("0");
		else{
			int d1=D(a[id(aa,b)].lt,a[id(c,d)].lt);
			int d2=D(a[id(aa,b)].rt,a[id(c,d)].rt);
			int d3=D(a[id(aa,b)].up,a[id(c,d)].up);
			int d4=D(a[id(aa,b)].down,a[id(c,d)].down);
			int ans=min(min(d1,d2),min(d3,d4));
			if(ans<1e9) cout<<ans<<endl;
			else puts("-1");
		}
	}
}
```
------------
[code](https://www.luogu.com.cn/paste/hm5dhik4)

完结撒花 QAQ。

---

## 作者：dbxxx (赞：3)

[欢迎您在我的博客阅读本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/luogu-p7473.html)

[P7473 NOI Online 2021 入门组 重力球](https://www.luogu.com.cn/problem/P7473)。

球在运动过程中，除了初始状态，都只会运动到与边界或障碍物相邻的点，不妨称之为转移点。不难发现转移点最多只有 $4(n+m)$ 个。

我们考虑将转移点从 $1$ 开始编号。

发现两个球分别处于两个转移点的总状态数不超过 $[4(n+m)]^2 \le 4\ \times 10^6$ 个，可以接受。

我们用 $(x, y)$ 表示第一个球在转移点 $x$，第二个球在转移点 $y$ 的状态。

球初始时可能不在转移点。可以枚举第一次的四种重力方向，让球运动到转移点上，最后求第一次重力取哪种方向能让答案最小即可。

为了做到快速求出球往一个方向运动到的转移点编号，我们要预处理出每个位置往每个方向移动到的转移点，这个可以 $\Theta(nm)$ 做到。

于是回答询问时，可以 $\Theta(1)$ 求得球向某个方向移动到的转移点编号。

现在我们只用考虑转移点了。

考虑建图。设转移点 $x$ 向左可以运动到转移点 $p$，向下可以运动到转移点 $q$；点 $y$ 向左可以运动到转移点 $s$，向下可以运动到转移点 $t$。

如果上一次两个球处于 $(x, y)$ 状态，那么向左一次运动可以得到 $(p, s)$，向下运动一次可以得到 $(q, t)$。

因此，$(x, y)$ 可以转移到 $(p, s)$ 或 $(q, t)$，而不能一次转移到 $(q, s)$ 或 $(p, t)$。这给我们什么启发？

如果我们建图按照 $x \to p$，$x \to q$，$y \to s$，$y \to t$ 这四条边全都放一起大锅乱炖，我们将无法从 $(x, y)$ 开始正确转移到下一步。

两种操作方式：

- 给每条边加一条属性：方向。从 $(x, y)$ 这个状态开始，同时枚举从 $x$ 开始的一条出边 $e_x$ 和从 $y$ 开始的一条出边 $e_y$。只有当 $e_x$ 和 $e_y$ 方向属性相同时，再按照这两个边的方向，转移到下一个合法状态，比如 $(p, s)$ 或 $(q, t)$。
- 建四张图，每张图只放一种方向的边。这样以来，我们先枚举四张图中的一张，再让 $(x, y)$ 按照这张图上面的边转移即可。比如，一张只有“向左”边的图中，能让 $(x, y)$ 转移到 $(p, s)$；而一张只有“向下”边的图中，能让 $(x, y)$ 转移到 $(q, t)$，不会混乱。

我选择了第二种方式。因为这样以来，从每个状态开始枚举出边时，只会枚举到有用的同向出边对，枚举次数会更少。

然后再观察这个题，是一个多终点最短路问题。我们应该转化成多源点最短路问题。

反图上多源点到一个点 $u$ 的距离，也就是原图上这个点 $u$ 到多终点的距离。

为此我们要将上面这个图反过来，也就是这么建：$p \to x$，$q \to x$，$s \to y$，$t \to y$。

然后，我们再将所有表示两个球处于同一个转移点的状态，也即 $(x, x)$ 这种状态作为源点。这些源点对应的 $\mathrm{dis} = 0$。

然后从这些源点开始，bfs 求得其余所有 $[4(n + m)]^2$ 个状态对应的距离。

在询问之前，bfs 预处理出距离，回答时就能做到 $\Theta(1)$ 了。

本题中，由于是两个点一起转移，bfs 时间复杂度数量级是图上点数的平方加边数的平方，而点数（即转移点数）为 $4(n+m)$，边数为 $4 \times 4(n+m)$（每个点最多连接四条边），所以加起来是一个大概 $20$ 常数的 $(n+m)^2 = 10^6$，也就是大概 $2 \times 10^8$，而且跑不满。

回答一次询问 $\Theta(1)$，所以上述算法可过。

一些细节：

- 这个图是有自环的。比如样例中的点 $(1, 1)$ 就是一个转移点，它向左或向上移动后，都会转移到自己。但没什么影响。
- 算完两个球第一步运动到某个方向的下一个状态对应的答案最小值后，不要忘记 $+1$。然后需要把两个球一开始就重合的情况特判掉。

如果这篇题解帮助到您了，记得给个赞！

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-03-22 08:00:29 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-03-22 11:01:43
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool f = true;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = false;
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    return f ? x : (~(x - 1));
}

const int maxn = 255, maxm = 255;
int id[maxn][maxn];

std :: vector <int> G[(maxn + maxm) << 2][4];
int fall[maxn][maxn][4];
int dis[(maxn + maxm) << 2][(maxn + maxm) << 2];

int main() {
    int n = read(), m = read(), Q = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        id[x][y] = -1;
    }

    for (int i = 1; i <= n; ++i)
        id[i][0] = id[0][i] = id[i][n + 1] = id[n + 1][i] = -1;
    
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (id[i][j] < 0)
                continue;
            if (id[i - 1][j] < 0 || id[i + 1][j] < 0 || id[i][j - 1] < 0 || id[i][j + 1] < 0)
                id[i][j] = ++cnt;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x = id[i][j];
            if (x < 0)
                continue;
            if (id[i][j - 1] < 0)
                fall[i][j][0] = x;
            else
                fall[i][j][0] = fall[i][j - 1][0];
            
            if (id[i - 1][j] < 0)
                fall[i][j][1] = x;
            else
                fall[i][j][1] = fall[i - 1][j][1];
            
            if (x > 0) {
                G[fall[i][j][0]][0].push_back(x);
                G[fall[i][j][1]][1].push_back(x);
            }
        }
    }

    for (int i = n; i; --i) {
        for (int j = n; j; --j) {
            int x = id[i][j];
            if (x < 0)
                continue;
            if (id[i][j + 1] < 0)
                fall[i][j][2] = x;
            else
                fall[i][j][2] = fall[i][j + 1][2];
            
            if (id[i + 1][j] < 0)
                fall[i][j][3] = x;
            else
                fall[i][j][3] = fall[i + 1][j][3];
            
            if (x > 0) {
                G[fall[i][j][2]][2].push_back(x);
                G[fall[i][j][3]][3].push_back(x);
            }
        }
    }

    std :: queue <std :: pair <std :: pair <int, int>, int> > q;
    std :: memset(dis, 0x3f, sizeof(dis));
    
    const int inf = dis[0][0];
    for (int i = 1; i <= cnt; ++i) {
        q.push({{i, i}, 0});
        dis[i][i] = 0;
    }
    
    while (!q.empty()) {
        int a = q.front().first.first, b = q.front().first.second, d = q.front().second;
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            for (int nxta : G[a][dir])
            for (int nxtb : G[b][dir])
            if (dis[nxta][nxtb] == inf) {
                dis[nxta][nxtb] = d + 1;
                q.push({{nxta, nxtb}, d + 1});
            }
        }
    }

    while (Q--) {
        int a = read(), b = read(), c = read(), d = read();
        if (a == c && b == d) {
            puts("0");
            continue;
        }

        int ans = inf;
        for (int dir = 0; dir < 4; ++dir) {
            ans = std :: min(ans, 
                dis[fall[a][b][dir]][fall[c][d][dir]] + 1
            );
        }
        printf("%d\n", (ans == inf) ? -1 : ans);
    }

    return 0;
}
```

---

## 作者：violin_wyl (赞：2)

## 思路



这题总的而言还是比较简单的~~（别问我为什么当时没做问就是没报NOI online）~~，这题其实提示的很明显了：“将重力方向“切换”为这个方向。此时两个小球会同时向这个方向移动，**直到碰到障碍**。”也就是说，我们去考虑那些靠近障碍物或者靠近边界的点才有意义，再看一眼数据范围 $(1 \leq m \leq 250)$ 美滋滋 （那么实际上只有 $250 \times 4 + 250 \times 4 = 2000$ 个点）。这样我们就可以对于每一个点都预处理出它四个方向能够到达的点 $(O(4n))$​。

我们再看到 $(1 \leq q \leq 10^5)$​​ ，这明显每次询问后处理是不行的，我们再考虑怎么对算法进行优化。

不难发现，我们再处理完所有有用的点之后，范围仍然很小 $(cnt \leq 2000)$​​，那我们不妨对每一个对点预处理出来他们能到达的最近的公共点，这部分的时间复杂度为 $O(4 \times 10^6)$​，是我们可以接受的。

至于怎么预处理，我想到的是反向建边，即对于任意一点，它的入边就是他在进行一次转换“重心”操作后到达的点向它连接的边。我们在对所有的点进行编号，因为对于任意两点当他们到达同一位置时状态是相同的，则我们可以进行反推，推出整个图所有的状态。

需要注意的一点，在输出的时候应先让两个小球都到达一个在图上能被表示的点，题目中没有保证小球最开始挨着障碍、边界，那最后答案需要+1。

代码我借鉴了楼下@water_tomato的写法（orz），只是改变了他的几个处理的小细节，以方便大家理解。

~~做题现状：口胡5分钟调了2小时~~
![闯关游戏~](https://cdn.luogu.com.cn/upload/image_hosting/gx09q59c.png)

code
------------

码风不好见谅。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 250 + 10;
const int MAXN = 2010;
const int M = 1e5 + 10;
const int inf = 2139062143;
const int mods = 19650827;
inline int read ( )
{
	int x = 0, f = 1;
	char ch = getchar ( );
	while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
	return x * f;
}
int n, m, q;
struct edge
{
	int ver, nxt;
}e[M];
int head[MAXN][5], tot;
void add (int u, int v, int d) {e[++tot] = (edge) {v, head[u][d]}; head[u][d] = tot;}
int a[N][N], dis[MAXN][MAXN];
int dir[MAXN][MAXN][4];
int vis[MAXN][MAXN], cnt;
void init ( )
{
	for (int i = 1; i <= n; i++) a[i][0] = a[0][i] = a[n + 1][i] = a[i][n + 1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!a[i][j] && (a[i + 1][j] || a[i][j + 1] || a[i - 1][j] || a[i][j - 1])) vis[i][j] = ++cnt;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			dir[i][j][0] = (a[i][j - 1] ? vis[i][j] : dir[i][j - 1][0]);
			dir[j][i][1] = (a[j - 1][i] ? vis[j][i] : dir[j - 1][i][1]);
		}
	for (int i = 1; i <= n; i++)
		for (int j = n; j >= 1; j--)
		{
			dir[i][j][2] = (a[i][j + 1] ? vis[i][j] : dir[i][j + 1][2]);
			dir[j][i][3] = (a[j + 1][i] ? vis[j][i] : dir[j + 1][i][3]);
		}
	return ;
}
struct node
{
	int x, y;
}tmp1;
queue <node> que;
int main ( )
{
	n = read ( ); m = read ( ); q = read ( );
	for (int i = 1; i <= m; i++) a[read ( )][read ( )] = 1;
	init();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
		if (vis[i][j] > 0)
			for (int k = 0; k <= 3; k++) add (dir[i][j][k], vis[i][j], k);
	memset (dis, 0x7f, sizeof (dis));
	for (int i = 1; i <= cnt; i++) { dis[i][i] = 0; que.push ((node) {i, i});}
	while (!que.empty ())
	{
		tmp1 = que.front ( ); que.pop ( );
		for (int k = 0; k <= 3; k++)
			for (int i = head[tmp1.x][k], u = e[i].ver; i; i = e[i].nxt, u = e[i].ver)
				for (int j = head[tmp1.y][k], v = e[j].ver; j; j = e[j].nxt, v = e[j].ver)
				{
					if (dis[u][v] != inf) continue;
					dis[u][v] = dis[tmp1.x][tmp1.y] + 1;
					que.push ((node) {u, v});
				}
	}
	while (q--)
	{
		int sx, sy, tx, ty;
		sx = read  ( ), sy = read ( ), tx = read ( ), ty = read  ( );
		if (sx == tx && sy == ty) {printf("0\n");}
		else
		{
			int ans = inf;
			for (int k = 0; k <= 3; k++) ans = min (ans, dis[dir[sx][sy][k]][dir[tx][ty][k]]);
			printf("%d\n", ans >= inf ? -1 : ans + 1);
		}
	}
    return 0;
} //The Dark Emperor
```

---

## 作者：Gold_Dino (赞：1)

# 题解

首先考虑一下暴力算法

## 暴力 $50 tps$

假设已经预处理出每个点向每个方向运动后，停下的位置，用 $f_{x, y, i}$ 表示点 $(x, y)$ 向 $i$ 方向运动，最终停在哪里，显然可以记忆化，做到 $\Theta(n^2)$。

用点 $(x, y, x', y')$ 表示第一个球走到点 $(x, y)$，第二个球走到 $(x', y')$ 的最少步数， 做以任意 $(x, y, x, y)$ 为源点的最短路。

时间复杂为 $\Theta(n^4 + q)$。

为什么是 $n^4$？很明显，边权都为 $1$，所以选用用 $bfs$。

## 关于另外 $30tps$

应为 $q = 1$，所以可以采用记忆化搜索或者广搜，这里就不再介绍。

## $100 tps$

考虑优化暴力算法，应为每次只可能停在障碍旁边，将这些点编号为 $1 \dots x$。

那么此时，可以将状态改为 $g_{i, j}$ 表示两个球分别在编号 $i, j$ 的点。

时间为 $\Theta(x^2 + q)$。

那么问题来了，$x$ 的范围是多少？

考虑内部的障碍，共有 $m$ 个障碍，最多有 $4 m$ 个，

再考虑外部障碍，显然是周围一圈，故为 $4 n$，

那么总和为 $4 n + 4 m \in \Theta( n + m )$，时间为 $\Theta((n + m)^2 + q)$

到此为止，我们就得到了正解。

下面附上代码

```cpp
#include <bits/stdc++.h>

namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
    if (S == T) {
        T = (S = buf) + fread(buf, 1, SIZE, stdin);
        if (S == T) return '\n';
    }
    return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
    fwrite(buf, 1, S - buf, stdout);
    S = buf;
}
inline void putchar(char c) {
    *S++ = c;
    if (S == T) flush();
}
struct NTR {
    ~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
    template<typename T>
    Reader& operator >> (T& x) {
        char c = getchar();
        T f = 1;
        while (c < '0' || c > '9') {
            if (c == '-') f = -1;
            c = getchar();
        }
        x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getchar();
        }
        x *= f;
        return *this;
    }
    Reader& operator >> (char& c) {
        c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        return *this;
    }
    Reader& operator >> (char* str) {
        int len = 0;
        char c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        while (c != ' ' && c != '\n' && c != '\r') { // \r\n in windows
            str[len++] = c;
            c = getchar();
        }
        str[len] = '\0';
        return *this;
    }
    Reader(){}
} cin;
const char endl = '\n';
struct Writer {
    template<typename T>
    Writer& operator << (T x) {
        if (x == 0) { putchar('0'); return *this; }
        if (x < 0) { putchar('-'); x = -x; }
        static int sta[45];
        int top = 0;
        while (x) { sta[++top] = x % 10; x /= 10; }
        while (top) { putchar(sta[top] + '0'); --top; }
        return *this;
    }
    Writer& operator << (char c) {
        putchar(c);
        return *this;
    }
    Writer& operator << (char* str) {
        int cur = 0;
        while (str[cur]) putchar(str[cur++]);
        return *this;
    }
    Writer& operator << (const char* str) {
        int cur = 0;
        while (str[cur]) putchar(str[cur++]);
        return *this;
    }
    Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl

struct coord { int x, y; };

const int N = 255, Max = 2e3 + 5, MaxMax = 4e6 + 5; const coord dir[] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
int n, m, q, mat[N][N];
int dis[Max][Max]; std :: vector<coord> e[Max][Max];
coord node[Max], to[N][N][4]; int top, mp[N][N], vis[N][N][4];
coord que[MaxMax]; int head, tail;

inline coord operator + ( const coord &a, const coord &b ) { return { a.x + b.x, a.y + b.y }; }

coord dfs( coord a, int d ) {
    if( vis[a.x][a.y][d] ) return to[a.x][a.y][d];
    vis[a.x][a.y][d] = 1;
    if( mat[a.x + dir[d].x][a.y + dir[d].y] ) return to[a.x][a.y][d] = a;
    return to[a.x][a.y][d] = dfs( a + dir[d], d);
}

#define Mp( a ) mp[a.x][a.y]

int main( ) {
    int i, j, k;
    cin >> n >> m >> q;
    for( i = 1; i <= m; i++ ) {
        int x, y;
        cin >> x >> y;
        mat[x][y] = 1;
    }
    for( i = 0; i <= n + 1; i++ ) mat[i][0] = mat[0][i] = mat[i][n + 1] = mat[n + 1][i] = 1;
    for( i = 1; i <= n; i++ )
        for( j = 1; j <= n; j++ ) {
            if( mat[i][j] ) continue;
            dfs( { i, j }, 0 );
            dfs( { i, j }, 1 );
            dfs( { i, j }, 2 );
            dfs( { i, j }, 3 );
            if( mat[i - 1][j] || mat[i][j - 1] || mat[i + 1][j] || mat[i][j + 1] ) node[mp[i][j] = ++top] = { i, j };
        }
    memset( dis, 127, sizeof( dis ) );
    head = tail = 1;
    for( i = 1; i <= top; i++ ) {
        que[tail++] = { i, i };
        dis[i][i] = 0;
        for( j = i + 1; j <= top; j++ )
            for( k = 0; k < 4; k++ ) {
                coord na = to[node[i].x][node[i].y][k], nb = to[node[j].x][node[j].y][k];
                if( Mp( na ) > Mp( nb ) ) std :: swap( na, nb );
                e[Mp( na )][Mp( nb )].push_back( { i, j } );
            }
    }
    while( head < tail ) {
        coord from = que[head++];
        int a = from.x, b = from.y;
        for( coord x : e[a][b] )
            if( dis[a][b] + 1 < dis[x.x][x.y] ) {
                dis[x.x][x.y] = dis[a][b] + 1;
                que[tail++] = { x.x, x.y };
            }
    }
    for( i = 1; i <= q; i++ ) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ans = ( x1 == x2 && y1 == y2 ) ? 0 : -1;
        for( j = 0; j < 4; j++ ) {
            coord na = to[x1][y1][j], nb = to[x2][y2][j];
            if( Mp( na ) > Mp( nb ) ) std :: swap( na, nb );
            int now = dis[Mp( na )][Mp( nb )];
            if( now == 0x7f7f7f7f ) continue;
            ans = ans == -1 ? now + ( x1 != na.x || y1 != na.y || x2 != nb.x || y2 != nb.y ) : std :: min( ans, now + ( x1 != na.x || y1 != na.y || x2 != nb.x || y2 != nb.y ) );
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Foreverxxx (赞：1)

总体感受：具有一定思维以及代码难度的一道好题。

### 思路

根据以往的做题经验，拿到这道题后一共有两个想法：搜索以及建边跑最短路，先简单地分析一下。

$1.$ 搜索

看似是可行的，代码也挺简单，不过当看见题目 $q \le 10^5$ 的数据范围后，这个想法就被打消了。

$2.$ 最短路

建图的方式是比较显而易见的，只需要把障碍旁边的这些真正有用的点给拿出来连边就可以了，在点数不是很多的情况下可以跑出来两点之间的最短路，貌似是可行的。

那么我们来深挖一下最短路的做法。

首先得关注建出来的图，仔细想一下，题目中四边边界的障碍一共会提供 $4n$ 个有用的点，而位于地图中间位置的点将会提供 $4m$ 个有用的点，那么总共就会有 $2000$ 个点，那么小球一共会出现的位置就会有 $4 \times 10^6$ 种，这种数据范围是我们可以接受的。

那么我们沿着这个思路，解决每一个子问题。

### 做法

$1.$ 找到有用的点

只需要先标记出所有障碍物的位置（注意要标记地图四周），然后枚举地图中间 $n^2$ 个点判断旁边是否有障碍即可，这一部分时间复杂度 $O(n^2)$。

为了方便解题，此时我们将这些有用的点编号。

$2.$ 找到每一个初始位置四个方向会滚到哪儿

思路也比较简单，对四个方向分别进行处理，拿向上滚来举例，如果这个位置上方是障碍，那么它滚到的点就是这个点，否则它滚到的点和上方那个点向上滚到的点是相同的，即我们可以直接转移。需要注意的是枚举的顺序，比如处理向下的情况时就得从最后一行枚举到第一行。

$3.$ 建边

对于建边操作，我们选择枚举有用的点，然后从**四个方向最终到达的点**向这个点连边（其实从这个点向四周连边也没什么问题，但是我的代码~~由于未知原因~~错了），时间复杂度 $O(n^2)$。

$4.$ 找最短路

本来可以选择 ``Dijkstra`` 的，不过由于带了一个 $\log$，不能保证通过，所以我们想到了之前被舍弃的搜索算法，考虑是否能够不用 $\log$ 求解。

由于每一个点编号与点的一一对应的关系，我们考虑把每个点看做一个**状态**，考虑如何从一个状态转移到另一个状态。

对于状态的起始点，我们设定两个小球在同一位置为起始点，因为此时答案为 $0$，那么我们只需要枚举这个状态可以转移到的所有状态，进行状态的更新就行了。

如果当前已知两个状态 $dist_{x,y}$ 的值，即知道了两个小球初始位置分别为 $x$ 和 $y$，而这个状态下一步可以到达 $dist_{u,v}$，那么转移方程就是 

$$
dist_{u,v}=dist_{x,y}+1
$$

这部分的代码如下：

```cpp
	memset(dist,0x3f,sizeof dist);
	queue<pair<int,int>> q;
	for(register int i=1;i<=id_num;i++){
		q.push(make_pair(i,i));
		dist[i][i]=0;
		//如果两个小球开始在同一个位置，那么答案为0
		//考虑将两个球位于同一位置设为初始状态 
	}
	while(!q.empty()){
		int x=q.front().first,y=q.front().second; q.pop();
		for(register int k=0;k<=3;k++){
			for(register int i=head[x][k];i;i=nxt[i]){
				for(register int j=head[y][k];j;j=nxt[j]){
					//枚举当前的两个位置能够到达的所有状态 
					int u=to[i],v=to[j];
					if(dist[u][v]>=1e9){
						dist[u][v]=dist[x][y]+1;
						q.push(make_pair(u,v));
					}
				}
			}
		}
	}
```

$5.$ 回答询问

开局两个点走向不同的四个方向，乍一看会有 $16$ 种情况，但其实只有 $4$ 种，因为同一时间两个球只能想同一方向移动。

但是最后求出来的答案需要加 $1$，因为我们求出的 $dist_{pos_1,pos_2}$ 是针对这两个**有用的点**而言的，开局第一次滚动并没有被计算进去。

### 一些细节

1. 记得标记地图四周为障碍。

2. 选有用的点时，注意这个点不能是障碍。

3. 预处理每个位置每个方向可以到达的点时，注意枚举的顺序，避免转移出错。

4. 注意特判两个小球初始位置相同。

5. 注意最后的答案需要加 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sss=0;
	char chh=getchar();
	while(chh<'0'||chh>'9') chh=getchar();
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss;
}
int n,m,q;
bool isobs[255][255];
int id[255][255],id_num=0;
int to_pos[255][255][4];
int head[2005][4],to[1000005],nxt[1000005],tot=1; 
int dist[2005][2005];
bool check(int x,int y){
	//四边只要有一边是障碍，那么这个点就是有用的
	//会有球滚到这里来之后停在这里 
	return isobs[x-1][y]||isobs[x][y-1]||isobs[x+1][y]||isobs[x][y+1];
}
void add(int u,int v,int d){
	to[++tot]=v;
	nxt[tot]=head[u][d];
	head[u][d]=tot;
}
void init_dist(){
	//dist[i][j]表示两个球的初始位置所对应的状态分别为i,j时，相遇的最小步数
	//也就是一个类似于bfs的东西 
	memset(dist,0x3f,sizeof dist);
	queue<pair<int,int>> q;
	for(register int i=1;i<=id_num;i++){
		q.push(make_pair(i,i));
		dist[i][i]=0;
		//如果两个小球开始在同一个位置，那么答案为0
		//考虑将两个球位于同一位置设为初始状态 
	}
	while(!q.empty()){
		int x=q.front().first,y=q.front().second; q.pop();
		for(register int k=0;k<=3;k++){
			for(register int i=head[x][k];i;i=nxt[i]){
				for(register int j=head[y][k];j;j=nxt[j]){
					//枚举当前的两个位置能够到达的所有状态 
					int u=to[i],v=to[j];
					if(dist[u][v]>=1e9){
						dist[u][v]=dist[x][y]+1;
						q.push(make_pair(u,v));
					}
				}
			}
		}
	}
}
int calc(int x1,int y1,int x2,int y2){
	//由于两个球只能同时向一个方向滚动
	//所以只能有4种而不是16种情况 
	int ans1=dist[to_pos[x1][y1][0]][to_pos[x2][y2][0]];
	int ans2=dist[to_pos[x1][y1][1]][to_pos[x2][y2][1]];
	int ans3=dist[to_pos[x1][y1][2]][to_pos[x2][y2][2]];
	int ans4=dist[to_pos[x1][y1][3]][to_pos[x2][y2][3]];
	return min(ans1,min(ans2,min(ans3,ans4)));
}
int main(){
	n=read(),m=read(),q=read(); int ob_x,ob_y;
	//标记地图中的障碍 
	for(register int i=1;i<=m;i++){
		ob_x=read(),ob_y=read();
		isobs[ob_x][ob_y]=true;
	}
	//标记地图四周的障碍 
	for(register int i=0;i<=n+1;i++) isobs[0][i]=true;
	for(register int i=0;i<=n+1;i++) isobs[n+1][i]=true;
	for(register int i=0;i<=n+1;i++) isobs[i][0]=true;
	for(register int i=0;i<=n+1;i++) isobs[i][n+1]=true;
	//找到障碍旁边的点，只有这些点才有用 
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			if(!isobs[i][j]&&check(i,j)){
				id[i][j]=++id_num;
			}
		}
	}
	//预处理每一个方向每个位置到达的点 
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			//向上
			if(isobs[i-1][j]) to_pos[i][j][0]=id[i][j];
			else to_pos[i][j][0]=to_pos[i-1][j][0];
		}
	}
	for(register int i=n;i>=1;i--){
		for(register int j=1;j<=n;j++){
			//向下
			if(isobs[i+1][j]) to_pos[i][j][1]=id[i][j];
			else to_pos[i][j][1]=to_pos[i+1][j][1];
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			//向左
			if(isobs[i][j-1]) to_pos[i][j][2]=id[i][j];
			else to_pos[i][j][2]=to_pos[i][j-1][2];//这个点向左和左边一个点向左是一样的 
		}
	}
	for(register int i=n;i>=1;i--){
		for(register int j=n;j>=1;j--){
			//向右
			if(isobs[i][j+1]) to_pos[i][j][3]=id[i][j];
			else to_pos[i][j][3]=to_pos[i][j+1][3];
		}
	}
	//按照状态建边 
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			if(id[i][j]){
				for(register int k=0;k<=3;k++){
					//从这个点能到达的点向这个点连边 
					add(to_pos[i][j][k],id[i][j],k);
				}
			}
		}
	}
	init_dist();
	int x1,y1,x2,y2;
	while(q--){
		x1=read(),y1=read(),x2=read(),y2=read();
		if(x1==x2&&y1==y2) puts("0");//特判在同一位置 
		else {
			int ans=calc(x1,y1,x2,y2);
			if(ans>=1e9) puts("-1");
			else cout<<ans+1<<"\n";
			//加上一步是因为最开始的第一步没有计算 
		}
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

先考虑每个小球可能在哪里重合。当两球初始位置不重合时，因为每次运动碰到障碍物才停止，所以每个球途中停留的位置一定是在障碍物的上下左右或边界位置。

观察到 $n,m\le 250$，所以每个球的可能位置只有 $4n+4m\le 2000$ 种可能，而两个球所有状态可能为 $2000\times 2000=4\times 10^6$ 种，并不是很多。

考虑先给每种可能位置一个编号，然后可以先预处理一个数组 $f_{i,j,k}$ 表示从 $(i,j)$ 出发，向方向 $k$ 移动最后会停留在的位置的编号。接着建图，给每个点与 $f_{i,j,k}$ 间连边，则问题会转化为有若干个起点状态 $(x,y)$，到若干个终点状态 $(i,i)$ 的最短路径长度。其中 $(x,y)$ 表示当前第一个小球位置编号为 $x$，第二个小球位置编号为 $y$。起点可能太多，不太好做，于是想到建反图倒着跑最短路。

但是起始点可能不是一个可能的停留位置，怎么办呢？直接枚举第一步后两个球的位置状态就可以了。注意特判起始点重合的情况。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300;
const int M=2e3+5;
struct edge{
	int to,nxt;
}e[M*4];
int n,m,q;
int cnt,head[M][10];
int a[N][N],f[N][N][10],dis[M][M],id[N][N],zx[M],zy[M],ccc;
int fx[10]={0,0,0,1,-1};
int fy[10]={0,-1,1,0,0};
bool flag[M][M];
inline int read(){
	int x=0,f=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x;
}
bool check(int x,int y){
	if(x<1||y<1||x>n||y>n||a[x][y])return 0;
	return 1;
}
void add(int u,int v,int k){
	e[++cnt].to=v;
	e[cnt].nxt=head[u][k];
	head[u][k]=cnt;
}
void BFS(){//最短路
	memset(dis,0x3f,sizeof(dis));
	queue<pair<int,int> >q; 
	for(int i=1;i<=ccc;i++)q.push({i,i}),dis[i][i]=1;
	while(!q.empty()){
		int u=q.front().first,v=q.front().second;q.pop();
		//cout<<endl;
		//cout<<u<<" "<<v<<endl;
		for(int k=1;k<=4;k++){
			for(int i=head[u][k];i;i=e[i].nxt){
				for(int j=head[v][k];j;j=e[j].nxt){
					int xxx=e[i].to,yyy=e[j].to;
					//cout<<xxx<<" "<<yyy<<endl;
					if(dis[u][v]+1<dis[xxx][yyy]){
						dis[xxx][yyy]=dis[u][v]+1;
						q.push({xxx,yyy});
					}
				}
			}
		}
	}
	/*for(int i=1;i<=ccc;i++){
		for(int j=1;j<=ccc;j++)cout<<dis[i][j]<<" ";
		cout<<endl;
	}*/
}
signed main(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int x,y;x=read();y=read();a[x][y]=1;
	}
	for(int i=1;i<=n;i++){//标记可能停留位置
		for(int j=1;j<=n;j++){
			if(a[i][j]){
				for(int k=1;k<=4;k++){
					int x=i+fx[k];
					int y=j+fy[k];
					if(id[x][y])continue;
					if(x<1||y<1||x>n||y>n||a[x][y])continue;
					id[x][y]=++ccc;zx[ccc]=x;zy[ccc]=y;
				}
			}
			else if(i==1||j==1||i==n||j==n){
				if(!id[i][j])id[i][j]=++ccc,zx[ccc]=i,zy[ccc]=j;
			}
		}
	}
	for(int i=1;i<=n;i++){//处理f数组
		for(int j=1;j<=n;j++){
			//cout<<id[i][j]<<" ";
			if(a[i][j])continue;
			for(int k=1;k<=4;k++){
				int x=i,y=j;
				while(check(x+fx[k],y+fy[k])){
					x+=fx[k];y+=fy[k];
				}
				f[i][j][k]=id[x][y];
				//cout<<i<<" "<<j<<" "<<k<<" "<<endl;
			}
		}
		//cout<<endl;
	}
	for(int i=1;i<=n;i++){//建图
		for(int j=1;j<=n;j++){
			if(id[i][j]){
				for(int k=1;k<=4;k++){
					add(f[i][j][k],id[i][j],k);
				}
			}
		}
	}
	BFS();
	while(q--){
		int xa,ya,xb,yb;xa=read();ya=read();xb=read();yb=read();
		int ans=114514191981000;
		if(xa==xb&&ya==yb){
			puts("0");continue;
		}
		for(int k=1;k<=4;k++){
			ans=min(ans,dis[f[xa][ya][1]][f[xb][yb][1]]);
			ans=min(ans,dis[f[xa][ya][2]][f[xb][yb][2]]);
			ans=min(ans,dis[f[xa][ya][3]][f[xb][yb][3]]);
			ans=min(ans,dis[f[xa][ya][4]][f[xb][yb][4]]);
		}
		if(ans==114514191981000)puts("-1");
		else printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：free_fall (赞：0)

先是暴力的写法，对于每一个询问进行一次深搜。

用 $vis_{a,b,c,d}$ 记录是否出现过第一个球的坐标为 $(a,b)$，第二个球的坐标为 $(c,d)$ 的状态，当 ```a==c&&b==d``` 时记录答案并停止搜索。

不考虑时间复杂度，空间就已经开不下了，只能拿到 $50$ 分的部分分。

我们发现除了开始的坐标之外，球必定在边界或障碍物的边上，我们称这些点为“特殊点”。

因为“特殊点”的数量不超过 $2000$，我们只需对能互相到达的“特殊点”进行连边，就可以解决空间开不下的问题。

但是对于每一个答案进行搜索时间依旧超时。

考虑从终点即 ```a==c&&b==d``` 时开始搜索，然后记录每一个状态的步数，在搜索答案时只需对上下左右四个点的 $dis$ 取最小值即可，搜索答案的时间复杂度即可降为 $O(1)$，总时间复杂度为 $O(tot^2)$，$tot$ 表示特殊点的数量。
```
#include<bits/stdc++.h>
using namespace std;
const int N=255,M=2005,inf=0x3f3f3f3f;
int n,m,Q,p[M][M][4],id[N][N],tot,dis[M][M];
bool mp[N][N];
vector<int> edge[N*N][4];
struct node{
	int x,y;
};
queue<node> q;
bool check(int x,int y){
	return mp[x-1][y]||mp[x][y-1]||mp[x+1][y]||mp[x][y+1];
}
int solve(int a,int b,int c,int d){
	int res=inf;
	for(int k=0;k<4;k++){
		res=min(res,dis[p[a][b][k]][p[c][d][k]]);
	}
	return res;
}
void init(){
	for(int i=1;i<=n;i++){
		mp[0][i]=mp[i][0]=mp[i][n+1]=mp[n+1][i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!mp[i][j]&&check(i,j))id[i][j]=++tot;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j-1])p[i][j][0]=id[i][j];
			else p[i][j][0]=p[i][j-1][0];
			if(mp[i-1][j])p[i][j][1]=id[i][j];
			else p[i][j][1]=p[i-1][j][1];
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=n;j>=1;j--){
			if(mp[i][j+1])p[i][j][2]=id[i][j];
			else p[i][j][2]=p[i][j+1][2];
			if(mp[i+1][j])p[i][j][3]=id[i][j];
			else p[i][j][3]=p[i+1][j][3];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(id[i][j]){
				for(int k=0;k<4;k++){
					edge[p[i][j][k]][k].push_back(id[i][j]);
				}
			}
		}
	}
	return;
}
void bfs(){
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=tot;i++){
		q.push({i,i});
		dis[i][i]=1;
	}
	while(!q.empty()){
		int x=q.front().x,y=q.front().y;
		q.pop();
		for(int k=0;k<4;k++){
			for(int i=0;i<edge[x][k].size();i++){
				for(int j=0;j<edge[y][k].size();j++){
					int xx=edge[x][k][i],yy=edge[y][k][j];
					if(dis[xx][yy]==inf){
						dis[xx][yy]=dis[x][y]+1;
						q.push({xx,yy});
					}
				}
			}
		}
	}
	return;
}
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		mp[x][y]=1;
	}
	init();
	bfs();
	for(int i=1;i<=Q;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(a==c&&b==d){
			printf("0\n");
			continue;
		}
		else{
			int ans=solve(a,b,c,d);
			if(ans==inf)printf("-1\n");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：Purslane (赞：0)

# Solution

考虑记录两个球分别在 $(x_1,y_1)$ 和 $(x_2,y_2)$ 的状态为 $(x_1,y_1,x_2,y_2)$。那么建立这个转移，然后在上面跑 BFS 最短路。

很遗憾，这样状态数会达到 $O(n^4)$，不足以通过本题。

但是你发现，假设我们让所有球往下掉，最终的情况数非常少：只有 $O(n+m)$ 个点可以存球，也就是只有 $O((n+m)^2)$ 个状态。最后只有 $O((n+m)^2)$ 状态，$O((n+m)^2)$ 条边，在上面跑最短路，足以通过本题。

---

