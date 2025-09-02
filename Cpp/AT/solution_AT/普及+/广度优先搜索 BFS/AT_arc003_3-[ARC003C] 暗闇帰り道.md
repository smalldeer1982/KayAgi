# [ARC003C] 暗闇帰り道

## 题目描述

## 漆黑归家路

高桥君一个人走夜路从学校回家。

他所居住的城市是一个被分为小格的长方形。高桥君一秒只能向东、南、西、北方向移动一格。

输入给出格子$i,j$的阳光值$c_i,_j$，$t$秒时，该格子的明亮度为$0.99^t×c_i,_j$$（出发时间为$0$秒）。

从学校回到家的路径明亮度为路线所经格子的明亮度的**最小值**。

高桥君有黑暗恐惧症，会尽可能地选择**明亮度大**的路径。

请求出他回家路径中的最大明亮度。

## 说明/提示

- 時刻0: 从学校$(1,1)$出发。
- 時刻1: 移动到$(2,1) $。时间 $t=1$, 阳光值$=7$ 、$(2,1)$ 的明亮度为$6.93$。
- 時刻2: 移动到$(2,2)$ 。时间 $t=2$, 阳光值$=4$ 、$(2,2)$的明亮度为$3.9204$。
- 時刻3: 移动到$(2,3)$ 。时间 $t=3$, 阳光值$=3$、$(2,3)$的明亮度为$2.910897$。
- 時刻4: 回到家$(3,3)$了 。当前最小的明亮值是时间 $t=3$时的$(2,3)$的明亮度为$2.910897$，答案也就是$2.910897$。
![样例1](https://cdn.luogu.org/upload/pic/39444.png)

样例2

输入
```
4 6
g31784
621415
627914
7451s3
```

输出

```
2.97
```

![样例2](https://cdn.luogu.org/upload/pic/39446.png)

不需要解释。

# 题解

## 作者：Fijian_Bus (赞：8)

二分暴力模拟算法。

题目给一个 $n$∗$m$ 的矩阵，每个位置上除起点、终点、障碍之外都有一个权值。我们先在要从起点走到终点，不经过障碍。一步要一秒的时间，一条路径的价值是路径上所有位置权值的最小值。在第 $t$ 秒时，一个位置的价值是它的权值乘上 $0.99t$。起点是 $s$，终点是 $g$，输入并没有多大问题。

### 思路：

有人用 bfs 做，其实没有这个必要。可以容易地得到，从起点开始做要考虑时间问题，不够方便。于是从终点开始往回走。

首先看数据范围，比较水，数组都开500够了。

这是某老师教给我们的宝贵方法。正难则反嘛。接下来一顿模拟：

我们借用动态规划的思想，先对输入图进行判断，每走一步，记录的最小值乘上 $0.99$ 与新到达的点的权值取最小值 $min$ 就好了，喏，状态的转移就一目了然了。最后记得判断一下是否越界。

如果 $sx,sy$ 的标记值为$-1$，就输出$-1$。否则，就把 $sx,sy$ 的标记值输出，保证输出足够的位数。


------------

### CODE:

```cpp
#include <bits/stdc++.h>
//防止抄袭
using namespace std;
const int MAXN=500+10,eps=INT_MAX; //极限值
int n,m,G[MAXN][MAXN],sx,sy,tx,ty,dr[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
double V[MAXN][MAXN];
char s[MAXN];

struct node
{
	int x,y; //坐标
	double val; //权值
};

queue <node> q; //队列大法好

int main()
{
	cin >> n >> m;
	for(int i=1; i<=n; i++)
	{
		scanf("%s",s+1);
		for(int j=1; j<=m; j++)
		{
			if(s[j]=='s')
				sx=i,sy=j,G[i][j]=10;
			else if(s[j]=='g')
				tx=i,ty=j,G[i][j]=10;
			else if(s[j]=='#')
				G[i][j]=-1;
			else G[i][j]=s[j]^'0';
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			V[i][j]=-1.0;
	V[tx][ty]=10.0;
	q.push((node){tx,ty,10.0});
	while(!q.empty())
	{
		node pr=q.front();
		q.pop(); //清队
		int x=pr.x,y=pr.y;
		double now=pr.val*0.99;
		for(int i=0; i<=3; i++)
		{
			int dx=x+dr[i][0],dy=y+dr[i][1];
			if(dx<1 || dx>n || dy<1 || dy>m || G[dx][dy]==-1)
				continue; //判断是否越界
			double nxt=min(now,(double)G[dx][dy]);
			if(nxt-V[dx][dy] > eps)
				V[dx][dy]=nxt,q.push((node){dx,dy,nxt});
		}
	}
	if(V[sx][sy]==-1)
		cout << "-1" << endl;
	else printf("%.10lf\n",V[sx][sy]); //保留10位吧
	return 0;
    //防止抄袭2
}
```


---

## 作者：阿丑 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT164)

#### 前置知识：

二分，bfs。

#### 题意：

* 在一张 $n×m$ 的地图上，起点为 $s$，终点为 $g$。

* 每个点是空地或障碍，每个空地都有一个 $[1, 9]$ 的整数值表示明亮度。

* 每走一步，所有明亮度都变为原来的 $99\%$，问路径上最小明亮度的最大值。

* $1\le N,M \le 500$。

#### 分析：

这是一道非常典型的二分+bfs。

如果你知道二分+bfs 是怎么来的话，~~那怎么会来看题解呢~~请直接跳到思路部分。

一般的 bfs 是根据某一维的单调性来进行优化的。拿求最短时间打比方。到达某一格子时，如果 $t_1<t_2$，那么一定是 $t_1$ 更赚，所以可以按照 $t$ 的顺序来进行搜索。

但是，本题中每个格子的状态由两个值决定，即时间 $t$ 和曾经经过的最小值 $mn$。当 $t$ 更小时，之后的路程的明亮度会更大，即 $t$ 越小越赚；而 $mn$ 更大时，代表了之前的路程明亮度更大，即 $mn$ 越大越赚。

然而，$t$ 与 $mn$ 并不满足单调性，即 $t$ 更小并不代表 $mn$ 更大。当 $t_1<t_2$ 而 $mn_2>mn_1$ 时，就无法直接判断两者中哪个更优。

如果 $mn_1=mn_2$，那么就只需判断 $t$ 的大小关系，也就是可以使用 bfs 了。

这时，我们不妨舍弃掉 $mn$ 一维：当 $mn < a$ 时，我们认为不是通路；而 $mn \ge a$ 时，我们认为是通路，并且所有通路的 $mn$ 等效。这样就只留下了 $t$，可以按照 $t$ 进行 bfs。

这等价于求有没有大于等于 $a$ 的解，而不是求最大的 $a$。难道我们要枚举每一个 $a$ 是否可行，然后找到最大的 $a$？

当然不必。$a$ 满足决策单调性，即若 $a_1$ 可行，且 $a_1>a_2$，那么 $a_2$ 一定可行。所以可以对 $mn$ 二分求解。

#### 思路：

1. dfs 判断有没有解。~~因为我 bfs 判断写炸了~~

2. 二分，并用 bfs 每个 $a$ 判断有没有解。

---

bfs 和二分都非常经典，应该不用说明写法了吧。

这里注意一下，因为有多次搜索，有关的数组、队列都要清空。

那直接上代码：

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mN=5e2+10, dx[]={-1, 0, 1, 0}, dy[]={0, 1, 0, -1};	//dx dy 表示每个方向 x,y 的变化
int n, m, mp[mN][mN];
double db[mN*mN];

struct point {
	int x, y, t;
} s, g;
queue <point> Q;
bool vis[mN][mN];
bool dfs(int x, int y) {	//不考虑 t，深搜 
	bool con=false;
	for(int d=0; d<4; ++d) {	//枚举四个方向 
		int nx=x+dx[d], ny=y+dy[d];
		if(nx==g.x && ny==g.y) return true;
		if(!vis[nx][ny] && mp[nx][ny]>0) vis[nx][ny]=1, con=con||dfs(nx, ny);
		//如果 dfs 中有一个能到达终点，那么就返回 true 
	}
	return con;
}
bool bfs(double a) {	//考虑 t，广搜 
	Q.push(s);	//放入起点
	while(!Q.empty()) Q.pop();	//清空 Q，清除对每一次搜索（无论 bfs 还是 dfs）对下一次产生的影响 
	for(int i=1; i<=n; ++i) for(j=1; j<=m; ++j) vis[i][j]=0;	//清空 vis 
	while(!Q.empty()) {
		point p=Q.front(); Q.pop();
		for(int d=0; d<4; ++d) {	//枚举四个方向 
			point q=p;
			++q.t, q.x+=dx[d], q.y+=dy[d];
			if(q.x==g.x && q.y==g.y) return 1;
			if(!vis[q.x][q.y] && mp[q.x][q.y]*db[q.t]>=a) Q.push(q), vis[q.x][q.y]=1;
			//如果没访问过并且现在明亮度>=a，那么就访问。 
		}
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m); 
	s.t=0;
	db[0]=1;
	for(i=1; i<=n*m; ++i) db[i]=db[i-1]*0.99;	//预处理出每个时刻明亮度的变化 
	for(int i=1; i<=n; ++i) for(int j=1; j<=m; ++j) {	//读入 
		char c;
		scanf("%c", c); 
		if(c=='s') s.x=i, s.y=j;
		if(c=='g') g.x=i, g.y=j; 
		if(c>='1'&&c<='9') mp[i][j]=c-48;
	}	//这里起点、终点、边界和障碍的 mp 值都是 0，接下来要利用这一点 

	if(!dfs(s.x, s.y)) {puts("-1"); return 0;}	//深搜判断可行性 

	double L=0, R=9, dl=1e-11;
	while(R-L>=dl) {	//二分枚举 a 
		double a=(L+R)/2;
		if(bfs(a)) L=a;
		else R=a;
	}
	printf("%.10f\n", L);
	return 0;
}
```

抄袭可耻（ 

---

