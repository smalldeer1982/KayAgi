# Ice Skating

## 题目描述

Bajtek is learning to skate on ice. He's a beginner, so his only mode of transportation is pushing off from a snow drift to the north, east, south or west and sliding until he lands in another snow drift. He has noticed that in this way it's impossible to get from some snow drifts to some other by any sequence of moves. He now wants to heap up some additional snow drifts, so that he can get from any snow drift to any other one. He asked you to find the minimal number of snow drifts that need to be created.

We assume that Bajtek can only heap up snow drifts at integer coordinates.

## 样例 #1

### 输入

```
2
2 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2 1
4 1
```

### 输出

```
0
```

# 题解

## 作者：Edmundino (赞：12)

# 题意

要求至少增加多少个点

才能是每两个点之间互通（要求两个点互通当且仅当两个点有相同的横坐标或纵坐标）

# 分析

咋们先看数据范围

$n$最大也才$100$

所以我们有机会用到二重循环

再看题目

要求两个点互通当且仅当两个点有相同的横坐标或纵坐标

我们就可以把我们当前的点进行一个分类

这时就可以用到并查集

### 并查集

并查集，在一些有N个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同一组的元素所在的集合合并。

简单来说：就是你有一堆数，

并将这些数分了类

每个数都有一个祖先（有可能是自己）

每两个数这间：可能他们的祖先相等，也有可能不相等

此时，你知道有两个数（假如是$A$与$B$）之间认了亲

所以你要对这两个数所在的家族（集合）进行合并

你就要把$A$家族的祖先全部改成$B$家族的祖先

也可以把$B$家族的祖先全部改成$A$家族的祖先

这就是并查集

回来看看这道题

我们可以把原有的点

如果有两个的点横坐标或纵坐标相等

我们就把他们的家族合并

最后我们再看分成了多少个家族

将家族数减一就是答案（要两个家族合并需要加一个点，所以有$n$个家族合并，就要加$n-1$个点）

# 代码

### 并查集


这是找$x$点的祖先的代码
```cpp
int find(int x)
{
	if(x!=father[x])
	  father[x]=find(father[x]);
	return father[x];
}
```
$father_x$是指$x$点的祖先

当发现$x$的祖先是本身时

就可以返回了

### 完整AC代码


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

const int N=1000;

int n,x[N],y[N],w[N][N],top[N],s,father[N];

int find(int x)
{
	if(x!=father[x])
	  father[x]=find(father[x]);
	return father[x];
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	  father[i]=i;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			if(i==j) continue;
			if(x[i]==x[j]||y[i]==y[j])
			{
				int q=find(i),p=find(j);
				if(q==p) continue;
				father[p]=q;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(father[i]==i)
		  s++;
	}
	cout<<s-1;
	return 0;
}

```


---

## 作者：EuphoricStar (赞：3)

## 前置芝士

- 并查集

并查集，是一种维护集合的数据结构。并查集支持两种操作：

1. 合并：合并两个结点所在的集合
2. 查找：查找一个结点所在集合的根结点

### 实现

并查集用一个数组实现：

```
int parent[N];
```

其中 `parent[i]` 代表结点 $i$ 的父节点。

### 初始化

一开始每个元素都是独立的一个集合，令所有 `parent[i] = i`

```cpp
for (int i = 1; i <= n; ++i) parent[i] = i;
```

### 查找

对给定的结点不断寻找父节点，并更新当前节点的父节点；

如果 `parent[i] = i`，代表当前节点已经是根结点，返回 $i$。

```cpp
int find(int x)
{
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}
```

### 合并

先判断两个元素是否属于同一个集合，只有当两个元素属于不同集合时合并，把其中一个集合的根结点的父亲设置为另一个集合的根结点。

```cpp
void union(int x, int y)
{
    int a = find(x), b = find(y);
    if (a != b) parent[a] = b;
}
```

## 思路

此题适合使用并查集。

首先初始化并查集，接着，输入第 $i$ 个点的同时，遍历一遍前 $i - 1$ 个点，如果这两个点 $x$ 坐标或 $y$ 坐标相等，合并它们。

最后统计一下一共有多少个集合（也就是统计一共有多少个不同的根结点），$- 1$ 后即为答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int parent[105], n;
struct point
{
    int x, y;
} pts[105];
set<int> parents;

int find(int x)
{
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) parent[i] = i;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &pts[i].x, &pts[i].y);
        for (int j = 1; j < i; ++j)
        {
            if (pts[j].x == pts[i].x || pts[j].y == pts[i].y)
            {
                int a = find(i), b = find(j);
                if (a != b) parent[a] = b;
            }
        }
    }
    for (int i = 1; i <= n; ++i) parents.insert(find(i));
    printf("%d", (int)parents.size() - 1);
    return 0;
}
```


---

## 作者：floatery (赞：3)

本题题意：在坐标系上有n个点，给出n个点的坐标，然后只能竖直或者横向移动，问最少需要建立几个中间点才能够从一个点出发到达所有的点

方法：dfs求联通块，结果为联通块数目-1
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x[101],y[101],vis[101];
void dfs(int i)
{
	vis[i]=1;
	for(int j=1;j<=n;j++)
	{
		if((x[j]==x[i]||y[j]==y[i])&&!vis[j])
		{
			dfs(j);
		}
	}
}
int main()
{
	int ans=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：灵光一闪 (赞：2)

这题我用了两种方法

先放第一种：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
bool vis[1005][1005];
int ans;
int n;
void dfs(int x1,int y1){
    vis[x1][y1]=false;//这里我是直接把用过的抹掉
    for(int i=0;i<1001;i++){//这两个循环用于遍历整个图
        if(vis[i][y1]){
            dfs(i,y1);
        }
    }
    for(int i=0;i<1005;i++){
        if(vis[x1][i]){
            dfs(x1,i);
        }
    }
    return;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        vis[x][y]=true;//一个点
    }
    for(int i=0;i<1001;i++){
        for(int j=0;j<1001;j++){
            if(vis[i][j]){//如果有这个点
                ans++;
                dfs(i,j);//遍历一遍
            }
        }
    }
    cout<<ans-1<<endl;
    return 0;
}
```
可是这个我认为复杂度更低的居然跑的比上面的慢？？？
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
bool vis[1005][1005];
int x[105],y[105];
int ans;
int n;
void dfs(int x1,int y1){
    vis[x1][y1]=false;
    for(int i=0;i<1001;i++){
        if(vis[i][y1]){
            dfs(i,y1);
        }
    }
    for(int i=0;i<1001;i++){
        if(vis[x1][i]){
            dfs(x1,i);
        }
    }
    return;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i];
        vis[x[i]][y[i]]=true;
    }
    for(int i=0;i<n;i++){
        if(vis[x[i]][y[i]]){
            dfs(x[i],y[i]);
            ans++;
        }
    }
    cout<<ans-1<<endl;
    return 0;
}//代码差不多，应该能看懂
```
所以现在有个问题：为什么第2种比第1种的复杂度要坏？？？

---

## 作者：yimuhua (赞：1)

**题意：**  

要求至少增加多少个点才能使每两个点之间互通

（要求两个点互通当且仅当两个点有相同的横坐标或纵坐标）

**分析：**

我们可以先把所有连通的点处理到并查集里，之后再从第 $1$ 个扫描到第 $n$ 个，一共出现了几个根节点（几个集合），那么结果就是集合数减一。因为添加一个点最多连两个不一样的集合。

**AC代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, x[1005], y[1005], fa[105];
int find(int x) {
    if(x == fa[x])//根节点
        return x;
    return fa[x] = find(fa[x]);//优化
}
void unionn(int x, int y) {
    int fx = find(x), fy = find(y);分别找根节点
    if(fx != fy)
        fa[fx] = fy;合并
    return;
}
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        fa[i] = i;//初始化
    for(int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++)
            if(x[i] == x[j] || y[i] == y[j])//是否联通
                unionn(i, j);//合并
    for(int i = 1; i <= n; i++)
        if(fa[i] == i)//集合的根节点
            ans++;
    cout << ans - 1;//n个集合，n-1个点
    return 0;
}
```


---

## 作者：wangyibo201026 (赞：0)

## 题意

现在有 $n$ 个点，当一个点与另一个点的 $x$ 坐标或者 $y$ 坐标相同时，此时称它们属于一个集合。问最后集合数减一是多少。

因为 $x$ 个集合最少再需要 $x - 1$ 个点就可以合并成一个集合了。

## 思路

一道并查集板子题，只需注意当两个点是否符合要求，再合并，最后再判一下有几个点的祖先结点是自己就可以了。

## 代码

蒟蒻的代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, fa[105], sum;

struct node{
	int x, y;
}a[105];

int find(int x){
	if(fa[x] == x){
		return x;
	}
	return fa[x] = find(fa[x]);
}

void unionn(int x, int y){
	x = find(x), y = find(y);
	if(x != y){
		fa[x] = y;
	}
}      //并查集板子

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){   //初始化
		fa[i] = i;
	}
	for(int i = 1; i <= n; i++){
		cin >> a[i].x >> a[i].y;
		for(int j = 1; j <= i - 1; j++){    //查找它前面的点
			if(a[i].x == a[j].x || a[i].y == a[j].y){   //是否符合要求
				unionn(i, j);   //合并
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(fa[i] == i){     //如果出现了一个集合
			sum++;
		}
	}
	cout << sum - 1;    //输出
	return 0;
}
```


---

## 作者：wanggiaoxing (赞：0)

### 并查集
这道题我们先可以把所有连通的点处理到并查集里，之后再从第 $1$ 个扫描到第 $n$ 个，一共出现了几个不一样的父亲，那么结果就是这个数减一，因为添一个点最多连两个不一样的集合（证明用反证法）。
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[1001],n,m,x[1001],y[1001];
bool p[1001];
int get(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=get(fa[x]);
}
void merge(int a,int b)
{
	fa[get(a)]=get(b);
}
int main()
{
	int ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				if(x[i]==x[j]||y[i]==y[j])
					merge(i,j);
	for(int i=1;i<=n;i++)
		if(p[get(i)]==0)
			ans++,p[get(i)]=1;
	cout<<ans-1;	
}
```


---

## 作者：Ptilopsis_w (赞：0)

# 思路
1.如果两个点横坐标或纵坐标一样的话就可以相互到达，我们可以把当前可相互到达的点看做一个整体，也就是一个联通块  

2.我们的目的是加一些点，使所有的点成为一个联通块。加一个点，只能把两个联通块合并在一起，所以如果有 $n$ 个联通块，就需要加 $n-1$ 个点才能合并在一起，所以下一步只需计算出联通块数量  

3.计算联通块的话可以用并查集维护，但是Edmundino大佬题解已经明确解释了并查集做法，所以我给出一种bfs做法

# 代码
```cpp
#include<cstdio>
#include<queue>
using namespace std;

int n, ans;
int x[110], y[110];
bool vis[110];

struct node{
	int x, y, i;//横坐标，纵坐标，编号
};
void bfs(int s)
{
	queue<node> q;//bfs用队列实现,stl的队列支持自定类型
	q.push({x[s], y[s], s});//push这里最好写一个构造函数，具体可以百度，大括号这种写法容易炸，最好别用
	while(!q.empty())
	{
		node a = q.front(); q.pop();//取出队首的点
		if(vis[a.i])//如果已经被访问过就跳过
			continue;
		vis[a.i] = true;//标记一下
		for(int i = 1; i <= n; i++)
		{
			if(i == a.i)
				continue;
			if(!vis[i] and (x[i] == x[a.i] or y[i] == y[a.i]))//满足条件且没被访问过就将这个点入队
				q.push({x[i], y[i], i});
		}
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &x[i], &y[i]);
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])//如果这个点没被访问过
		{
			bfs(i);//将其所在联通块全部标记
			ans++;//联通块数量++
		}
	}
	printf("%d", ans-1);//输出答案
	int qwq = 0;
	return qwq;
}
```

---

