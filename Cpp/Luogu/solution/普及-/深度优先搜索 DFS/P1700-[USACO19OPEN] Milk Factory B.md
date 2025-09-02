# [USACO19OPEN] Milk Factory B

## 题目描述

牛奶生意正红红火火！Farmer John 的牛奶加工厂内有 $N$ 个加工站，编号为 $1\dots N$（$1\le N\le 100$），以及 $N−1$ 条通道，每条连接某两个加工站。（通道建设很昂贵，所以 Farmer John 选择使用了最小数量的通道，使得从每个加工站出发都可以到达所有其他加工站）。

为了创新和提升效率，Farmer John 在每条通道上安装了传送带。不幸的是，当他意识到传送带是单向的已经太晚了，现在每条通道只能沿着一个方向通行了！所以现在的情况不再是从每个加工站出发都能够到达其他加工站了。

然而，Farmer John 认为事情可能还不算完全失败，只要至少还存在一个加工站 $i$ 满足从其他每个加工站出发都可以到达加工站 $i$。注意从其他任意一个加工站 $j$ 前往加工站 $i$ 可能会经过 $i$ 和 $j$ 之间的一些中间站点。请帮助 Farmer John 求出是否存在这样的加工站 $i$。

## 样例 #1

### 输入

```
3
1 2
3 2```

### 输出

```
2```

# 题解

## 作者：HasNoName (赞：11)

#### 问题
在一张 $N$ 个点有向图中，求编号最小的，所有点都能到的点。

没有所有点都能到的点输出 $-1$。

$(1\le N\le100)$。

### 方法

用一个数组统计每个点能被走到的数量。

对每个点进行搜索，把能到的点的能被走到的数量增加 $1$。

如果一个点能被走到的数量是 $N-1$ 则所有的点都能到。

### 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=105;
int w[N];//每个点能被走到的数量
bool vis[N];
struct T
{
    int to,ne;
}e[N];
int he[N],idx;
void add(int x,int y)//建图
{
    e[++idx].ne=he[x];
    e[idx].to=y;
    he[x]=idx;
}
void dfs(int x)//遍历
{
    vis[x]=1;//每个点只走一次
    for(int i=he[x];i;i=e[i].ne)//遍历每个临点
    {
        int y=e[i].to;
        if(!vis[y])//没被遍历过
        {
            w[y]++;
            dfs(y);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,x,y;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        cin>>x>>y;
        add(x,y);
    }
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));//清空数组
        dfs(i);
    }
    for(int i=1;i<=n;i++)
    {
        if(w[i]==n-1)
        {
            cout<<i<<'\n';
            return 0;
        }
    }
    cout<<"-1\n";//无解
    return 0;
}

```

[记录](https://www.luogu.com.cn/record/143258851)。

---

## 作者：yhx0322 (赞：6)

## Description
给你一张有向图，$N$ 和点 $N - 1$ 条边。现在求有没有特殊点，能够使所有除他以外的节点都能到达。如果有，输出最小的编号。

## Solution
有向图中的技巧：哪些点能走到 $x$ 点，等价于**反向建图后，$x$ 点能走到哪些点。**

这种方法会比从每个点搜索的效率高很多。

所以这道题便可以反向建图，枚举每个点开始 DFS / BFS。走到了就标记为 `true`。最后如果发现所有点的标记都为 `true`，输出答案。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 110;
struct node{
	int to, next;
} a[N];
int pre[N], k, n, x, y, ans;
bool f[N];

void add(int x, int y) {
	a[++k] = {y, pre[x]};
	pre[x] = k;
}

void dfs(int x) {
	for (int i = pre[x]; i; i = a[i].next) {
		int to = a[i].to;
		if (!f[to]) {
			f[to] = true;
			dfs(to);
		}
	}
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> x >> y;
		add(y, x); // 反向建图
	}
	bool pd = true;
	for (int i = 1; i <= n; i++) {
		memset(f, false, sizeof(f));
		dfs(i);
		pd = true;
		for (int j = 1; j <= n; j++) {
			if (i != j && !f[j]) { // 发现不满足情况
				pd = false;
				break;
			}
		}
		if (pd) return cout << i << '\n', 0; // 找到了就输出
	}
	cout << -1 << '\n';
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：4)

# P1700 [USACO19OPEN] Milk Factory B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p1700)~~

这是一道暴力水题。

我们可以用一个数组 $can$ 来记录加油站 $a_i$ 能到哪个加油站。

然后遍历 $1$ 到 $n-1$，判断当前加油站 $i$ 是否满足要求，是就输出 $i$，如果到最后都没有输出，输出 $-1$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int can[110];
int n;
bool judge(int i)
{
	bool f=false;
	for(int j=1;j<n;j++)
	{
		if(i==j)
		{
			continue;
		}
		int k1=j;
		bool f1=false;
		for(int k=0;k<=100;k++)
		{
			k1=can[k1];
			//cout<<k<<" "<<f1<<endl;
			if(k1==i)
			{
				f1=true;
			}
		}
		//cout<<f1<<" "<<f<<endl;
		if(f1==false)
		{
			f=true;
		}
	}
	return f;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		cin>>a>>b;
		can[a]=b;
	}
	for(int i=1;i<=n-1;i++)
	{
		if(judge(i)==false)
		{
			cout<<i;
			exit(0);
		}
	}
	cout<<-1;
}
```

---

## 作者：gey666 (赞：3)

~~蒟蒻的第一篇题解，纪念一下，思路若有误请喷轻点~~

给定一个有向图，输出最小的能让所有节点到达的节点。
## 思路

$1 \le N \le 100$，可以使用邻接矩阵来存储，标记两个点之间有没有路。这里用的是 Floyd 算法。

用数组 $d$ 存储每两个点之间的最短路，枚举中转点 $k$，使 $i$ 到 $k$，$k$ 到 $j$ 都存在路径，则 $i$ 到 $j$ 的最短路为 $i$ 到 $k$ 的最短路加上 $k$ 到 $j$ 的最短路与 $i$ 到 $j$ 的最短路之间的最小值。这道题不需要考虑最短路，所以像上文说的一样，只需标记有没有路。

要注意的是，因为一个点到自己的最短路是 $0$，且两点间默认没有路，所以 $d$ 数组需要初始化。

最后呢，枚举最小的符合条件的 $i$ 即可。
## AC代码

```
#include <bits/stdc++.h>
using namespace std;
int d[110][110];//邻接矩阵，有路就标记为1，没路标记为0x3f3f3f3f
int n,flag=1;
int main() {
	cin>>n;
	memset(d,0x3f,sizeof(d));//初始化
	for(int i=1;i<=n-1;i++){//初始化&输入
		int x,y;
		cin>>x>>y;
		d[i][i]=1;//一个点到自己一定有路
		d[x][y]=1;
	}
	d[n][n]=1;
	for (int k=1;k<=n;k++) {//k为枚举的中转点
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				if (d[i][k]!=0x3f3f3f3f&&d[k][j]!=0x3f3f3f3f){//判断是否有路并标记
					d[i][j]=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){//输出，枚举最小的i
		flag=0;
		for(int j=1;j<=n;j++){
			if(d[j][i]==0x3f3f3f3f){
				flag=1;
				break;
			}
		}
		if(!flag){
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：jess1ca1o0g3 (赞：1)

[Portal](https://www.luogu.com.cn/problem/P1700)

## 题意

一张有向图，有 $n$ 个点，$n-1$ 条边，求一个所有点都能到的点，且编号最小，无解输出 $-1$。

## 思路

由于数据较小（$1\leq n\leq100$），所以可以暴力。

每个点都能到达，也就是从一个点搜到的所有点的数量是 $n-1$。

建立一个桶，存放每个点被搜到的次数。

如果满足条件则直接输出，因为枚举桶的顺序保证答案最小。


## Code

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
std::vector <std::vector<int>> g;  // 邻接表
std::vector <int> f;  // 桶
bool vis[105];  // 标记
int n,u,v;
void dfs(int u){  // 深搜
    if(vis[u]) return;
    vis[u]=1;
    for(int i=0;i<g[u].size();i++){
        f[g[u][i]]++;  // 对应桶加1
        dfs(g[u][i]);
    }
}
void solve(){
    scanf("%d",&n);
    f.resize(n+1,0);
    g.resize(n+1);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        g[u].push_back(v);  // 建边
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));  // 每搜一遍要清空
        dfs(i); 
    }
    for(int i=1;i<=n;i++){
        if(f[i]==n-1){  // 满足条件
            printf("%d",i);
            return;
        }
    }
    printf("-1"); //  无解
}
signed main(){
    solve();
    return 0;
}
```

---

## 作者：xu_zhihao (赞：1)

###  题目理解：

   - 因为这道题 $N \le 100$ 所以我们可以考虑暴力解题。我们可以构造一个像链表的数组，即 $a_i=vel_i,b_i=nxt_i$。第一个循环枚举每一个位置，第二层枚举每一个数组里的数是否能走到第一层循环的位置，如果可以就输出，最后枚举完每一个条件后还没有结果则输出 $-1$。
   
  
### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[10010];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int a,b;
		cin>>a>>b;
		p[a]=b;
	}
	for(int i=1;i<n;i++)
	{
		int c=0;
		for(int j=1;j<n;j++)
		{
			if(i==j)
			{
				continue;
			}
			int u=j;
			int f=0;
			for(int k=0;k<=100;k++)
			{
				u=p[u];
				if(u==i)
				{
					f=1;
					break;
				}
			}
			if(!f)
			{
				c=1;
				break;
			}
		}
		if(c==0)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
}
```


---

## 作者：sssscy_free_stdio (赞：1)

数据范围只有 $1 \le N \le 100$，可以考虑暴力。
  
我们先枚举第 $i$ 个工厂，然后枚举其他的工厂，从每个其他的工厂开始 `DFS`，然后将能到的工厂标记，最后再判断第 $i$ 个工厂是否被其他的所有工厂标记了就行了。

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v,j,mi=0x3f3f3f3f,vis[110][110];
vector<int>g[110];
void dfs(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(vis[j][v]==0){
			vis[j][v]=1;//标记走到的
			dfs(v);
		}
	}
}int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);//建单向边
	}for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);//注意清空！
		for(j=1;j<=n;j++){
			if(i!=j){//要在其他的工厂开始
				dfs(j);
			}
		}int flag=0;
		for(j=1;j<=n;j++){
			if(i!=j&&vis[j][i]==0){
				flag=1;//发现有到不了这个工厂的
				break;
			}
		}if(flag==0){
			mi=min(mi,i);//其实这里直接输出再结束程序就好了，我的习惯
		}
	}if(mi==0x3f3f3f3f){
		printf("-1");
	}else{
		printf("%d",mi);
	}return 0;
} 
```

---

