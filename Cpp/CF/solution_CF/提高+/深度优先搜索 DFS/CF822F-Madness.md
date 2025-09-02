# Madness

## 题目描述

The second semester starts at the University of Pavlopolis. After vacation in Vičkopolis Noora needs to return to Pavlopolis and continue her study.

Sometimes (or quite often) there are teachers who do not like you. Incidentally Noora also has one such teacher. His name is Yury Dmitrievich and he teaches graph theory. Yury Dmitrievich doesn't like Noora, so he always gives the girl the most difficult tasks. So it happened this time.

The teacher gives Noora a tree with $ n $ vertices. Vertices are numbered with integers from $ 1 $ to $ n $ . The length of all the edges of this tree is $ 1 $ . Noora chooses a set of simple paths that pairwise don't intersect in edges. However each vertex should belong to at least one of the selected path.

For each of the selected paths, the following is done:

1. We choose exactly one edge $ (u,v) $ that belongs to the path.
2. On the selected edge $ (u,v) $ there is a point at some selected distance $ x $ from the vertex $ u $ and at distance $ 1-x $ from vertex $ v $ . But the distance $ x $ chosen by Noora arbitrarily, i. e. it can be different for different edges.
3. One of the vertices $ u $ or $ v $ is selected. The point will start moving to the selected vertex.

Let us explain how the point moves by example. Suppose that the path consists of two edges $ (v_{1},v_{2}) $ and $ (v_{2},v_{3}) $ , the point initially stands on the edge $ (v_{1},v_{2}) $ and begins its movement to the vertex $ v_{1} $ . Then the point will reach $ v_{1} $ , then "turn around", because the end of the path was reached, further it will move in another direction to vertex $ v_{2} $ , then to vertex $ v_{3} $ , then "turn around" again, then move to $ v_{2} $ and so on. The speed of the points is $ 1 $ edge per second. For example, for $ 0.5 $ second the point moves to the length of the half of an edge.

A stopwatch is placed at each vertex of the tree. The time that the stopwatches indicate at start time is $ 0 $ seconds. Then at the starting moment of time, all points simultaneously start moving from the selected positions to selected directions along the selected paths, and stopwatches are simultaneously started. When one of the points reaches the vertex $ v $ , the stopwatch at the vertex $ v $ is automatically reset, i.e. it starts counting the time from zero.

Denote by $ res_{v} $ the maximal time that the stopwatch at the vertex $ v $ will show if the point movement continues infinitely. Noora is asked to select paths and points on them so that $ res_{1} $ is as minimal as possible. If there are several solutions to do this, it is necessary to minimize $ res_{2} $ , then $ res_{3} $ , $ res_{4},...,res_{n} $ .

Help Noora complete the teacher's task.

For the better understanding of the statement, see the explanation for the example.

## 说明/提示

Consider an example.

In starting moment of time points are located as following:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/be0dbed0886e2d0dbeae85fa30e48d04dd18a145.png)

The first path is highlighted in red, the second in blue, green circles represent chosen points, and brown numbers inside vertices — current time at stopwatch. Purple arrows represent direction in which points will move.

In $ 0.(3) $ seconds points will be located in following way (before stopwatch reset):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/7cfb428336aebc601c4b996757fdb752e3f7c6a8.png)

After stopwatch reset:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/87ab7128d0c4deb72103b8c56bde3fd3f8fbbbe1.png)

In $ 1.0 $ second after the start of moving:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/5cf6946176797cebc145a79d5535ea5ef7037208.png)

In $ 1.(3) $ seconds after the start of moving (after stopwatch reset):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/866fa575f288f1f0783b52f28144f7c6700f8ea9.png)

Finally, in $ 2 $ seconds after the start of moving points return to their initial positions.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822F/e75c571be50a2075e2a9f9aeb90861b5d466ebb8.png)

This process will continue infinitely.

## 样例 #1

### 输入

```
3
1 2
2 3
```

### 输出

```
2
1 1 1 2 0.6666666666
1 2 2 3 0.6666666666
```

# 题解

## 作者：樱雪喵 (赞：7)

贪心题。

首先可以想到，让每个点被经过的次数尽可能多，就是让每条路径的长度尽可能短。观察到在一条路径上只放置一个点，一定不优于在这条路径上的每条边放一个点。那么就可以把每条边单独划分为一条路径。

这样划分，树上状态的变化周期为 $2s$，我们只需要考虑这 $2s$ 内计时器的最大值。

设一个点 $u$ 的度数为 $deg_u$，那么就会有 $deg_u$ 个点在周期内经过点 $u$。使每个点到达时间间隔的最大值最小，就是让它们间隔时间全部相等，为 $\frac{2}{deg_u}$。

自上而下贪心，根据父亲边上点到达的时间和已知时间间隔 $\frac{2}{deg_u}$，一定可以构造出某种可行解。

此时满足每个计时器的最大值最小，即字典序也最小。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int xr=0,F=1;char cr=getchar();
	while(cr<'0'||cr>'9') {if(cr=='-') F=-1;cr=getchar();}
	while(cr>='0'&&cr<='9')
	    xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
typedef double db;
const int N=505;
int n,head[N],deg[N],cnt;
struct node{
	int nxt,to,id;
}e[N<<1];
void add(int u,int v,int id){
	e[++cnt]={head[u],v,id};head[u]=cnt;
}
db lst[N];
void dfs(int now,int fa)
{
	for(int i=head[now];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		lst[now]+=(2.0/(db)deg[now]);
		if(lst[now]>2) lst[now]-=2;
		if(lst[now]<1)
		{
			printf("1 %d %d %d %.6lf\n",e[i].id,v,now,lst[now]);
			lst[v]=lst[now]+1;
		}
		else
		{
			printf("1 %d %d %d %.6lf\n",e[i].id,now,v,lst[now]-1);
			lst[v]=lst[now]-1;
		}
		dfs(v,now);
	}
}
int main()
{
	n=read();printf("%d\n",n-1);
	for(int i=1,u,v;i<n;i++) 
	{
		u=read(),v=read();
		add(u,v,i),add(v,u,i);
		deg[u]++,deg[v]++;
	}
	dfs(1,0);
	return 0;
}
```

---

## 作者：YCS_GG (赞：2)

### CF822F Madness


首先我们可以想到每个路径只选择一条边就是最优的

可以这样理解一下，因为如果一个路径包含多个边，那么这内部的一个端点上的计时器肯定不优于在这个端点上在加一个新的动点

因为一个点来回跑需要$2s$所以每个点最大显示实现最小就是$\dfrac{2}{deg}$，$deg$是这个点的度数

然后我们只要深搜贪心的构造一下最小值就好了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, u[N], v[N], head[N], deg[N], ecnt, To[N];
double ans[N];
struct Edge {
    int v, nxt;
} edge[N * 2];
void add(int x, int y) {
    edge[++ecnt].v = y;
    edge[ecnt].nxt = head[x];
    head[x]        = ecnt;
}
void dfs(int x, int fa, double lst) {
    double time = 2.0 / deg[x];
    for (int i = head[x]; i; i = edge[i].nxt) {
        if (edge[i].v != fa) {
            lst += time;
            while (lst > 2) {
                lst -= 2;
            }
            int id = (i + 1) / 2;
            if (lst <= 1) {
                To[id] = x, ans[id] = lst;
            } else {
                To[id] = edge[i].v, ans[id] = lst - 1;
            }
            dfs(edge[i].v, x, lst + 1);
        }
    }
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u[i] >> v[i];
        add(u[i], v[i]);
        add(v[i], u[i]);
        deg[u[i]]++;
        deg[v[i]]++;
    }
    dfs(1, -1, 0);
    cout << n - 1 << endl;
    for (int i = 1; i < n; i++) {
        printf("1 %d %d %d %.8lf\n", i, u[i] + v[i] - To[i], To[i], ans[i]);
    }
    return 0;
}
```



---

## 作者：AC_love (赞：1)

贪心。

我们考虑：每个点被经过的次数尽可能多，其实就是希望路径尽可能多。

那么我们把每条边都单独划分为一个路径肯定是最优的。

此时一个点被经过的次数就是以这个点为顶点的边的数量，也就是这个点的度。

我们发现一个人走一条边的周期是 $2$ 秒，也就是每过 $2$ 秒就会回归初始状态。因此我们可以设计点 $u$ 的最大计数为 $\dfrac{2}{deg_u}$，其中 $deg_u$ 是点 $u$ 的度。

问题还剩下如何构造一组可行解。

不难想到其实只需要让到达一个点的所有人到达这个点的时间差一样即可。

当我们希望到达某个点 $u$ 的时候，我们每次让这个点的到达时间增加 $\dfrac{2}{deg_u}$。

如果我们发现当前的时间如果小于 $1$，那么就是从边上的某个点朝 $u$ 走。而如果当前时间大于 $1$，就是从边上的点朝 $u$ 的对面走，走到头之后折返回来回到 $u$。

代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 114;
struct edge
{
	int ed;
	int id;
};
vector <edge> e[N];

int n;
double t[N]; 

void dfs(int st, int fa)
{
	int deg = e[st].size();
	for(int i = 0; i < e[st].size(); i = i + 1)
	{
		int ed = e[st][i].ed;
		if(ed == fa)
			continue;
		t[st] += (2.0 / (double)deg);
		while(t[st] > 2)
			t[st] -= 2;
		while(t[st] < 0)
			t[st] += 2;
		if(t[st] < 1)
		{
			cout << "1 " << e[st][i].id << " " << st << " " << ed << " " << t[st] << "\n";
			t[ed] = t[st] + 1;
		}
		else
		{
			cout << "1 " << e[st][i].id << " " << ed << " " << st << " " << t[st] - 1 << "\n";
			t[ed] = t[st] - 1;
		}
		dfs(ed, st);
	}
}

int main() 
{
	cin >> n;
	for(int i = 1; i <= n - 1; i = i + 1)
	{
		int st, ed;
		cin >> st >> ed;
		e[st].push_back((edge){ed, i});
		e[ed].push_back((edge){st, i});
	}
	cout << n - 1 << "\n";
	dfs(1, 0);
	return 0;
}
```

---

