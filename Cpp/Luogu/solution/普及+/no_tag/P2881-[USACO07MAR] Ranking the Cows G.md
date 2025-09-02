# [USACO07MAR] Ranking the Cows G

## 题目描述

FJ 想按照奶牛产奶的能力给她们排序。现在已知有 $N$ 头奶牛（$1\le N\le {10}^3$）。FJ 通过比较，已经知道了 $M$（$1 \le M \le {10}^4$）对相对关系。每一对关系表示为 `X Y`，意指奶牛 $X$ 的产奶能力强于 $Y$。现在 FJ 想要知道，他至少还要知道多少对关系才能完成整个排序。

## 说明/提示

### 样例解释

我们用 $C_i$ 表示第 $i$ 头奶牛的产奶能力。

根据给出的 $5$ 组关系，FJ 已经能知道 $C_2 > C_1 > C_5$ 且 $C_2 > C_3 > C_4$，因此第 $2$ 只奶牛的产奶能力最高。接着 FJ 需要知道 $C_1$ 和 $C_3$ 的大小关系才能知道哪只奶牛的产奶能力第二高。FJ 还需要知道 $C_4$ 和 $C_5$ 的大小关系和 $C_5$ 和 $C_3$ 的关系才能完全确定顺序。可以证明没有询问次数比 $3$ 次更少的方案了。

## 样例 #1

### 输入

```
5 5
2 1
1 5
2 3
1 4
3 4```

### 输出

```
3```

# 题解

## 作者：panyf (赞：33)

## 传递闭包的四种求法

有向图传递闭包需要对每个点对 $(i,j)$，求出 $i$ 到 $j$ 是否连通。

### 做法 1：

直接 Floyd，$b_{i,j}=1$ 表示 $i$ 能到达 $j$，$b_{i,j}=0$ 表示不能到达。

枚举中转点 $i$，再枚举 $j,k$，转移方程：`b[j][k]|=b[j][i]&b[i][k]`。

可以用 bitset 优化：`if(b[j][i])b[j]|=b[i]`。

时间复杂度 $O(\dfrac{n^3}{w})$。

### 做法 2：

以每个点为起点深/广搜遍历整张图，求出能到达的所有点。

时间复杂度 $O(nm)$。

### 做法 3：

上一个做法不能用 bitset 优化，是因为可能存在环，不能记忆化。

考虑对强连通分量缩点（此题中保证是 DAG 就不用了）。

然后继续用做法 2，以每个点为起点 dfs。

若当前访问到边 $(i,j)$，$j$ 未被 dfs 过，则 dfs $j$。

然后 `b[i]|=b[j]`。

时间复杂度 $O(\dfrac{nm}{w})$。

适合稀疏图，在此题中效率最高。

### 做法 4：

依然是先缩点。

然后求出 DAG 的拓扑序。

按拓扑序每 $B$ 个点分一块，倒序求解。

对于每一块，在求出其中所有点的可达集合后，求出 $2^B$ 个子集的可达集合（一个子集的可达集合是其中所有点可达集合的并集），用 bitset 优化，这部分复杂度 $O(2^B\dfrac{n}{B}\dfrac{n}{w})$。

求一个点 $i$ 的可达集合，只需要枚举之后的每个块，通过子集的可达集合，一次更新以块中所有存在边 $(i,j)$ 的点 $j$ 为中转点的答案，这部分复杂度 $O(n\dfrac{n}{B}\dfrac{n}{w})$。

取 $B=\log n$，总复杂度 $O(\dfrac{n^3}{w\log n})$。

适合稠密图。

代码中取 $B=8$。

最后提一下此题做法。

显然是传递闭包模板题。

最坏情况下，所有不能确定大小关系的都要问一遍。

所以答案即为总的满足 $i\neq j$ 的无序对数 $\dfrac{n\times(n-1)}{2}$，减去已经确定大小关系的对数。

已经确定大小关系的对数，就是满足 $i$ 能到达 $j$ 且 $i\neq j$ 的数对 $(i,j)$ 个数。

[做法 1](https://www.luogu.com.cn/record/51296797)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
bitset<N>b[N];
int main(){
	int n,m,i,j;
	for(scanf("%d%d",&n,&m);m--;)scanf("%d%d",&i,&j),b[i][j]=1;
	for(i=1;i<=n;++i)for(j=1;j<=n;++j)if(b[j][i])b[j]|=b[i];
	for(j=n*(n-1)/2,i=1;i<=n;++i)j-=b[i].count();
	printf("%d",j);
	return 0;
}
```

[做法 2](https://www.luogu.com.cn/record/51296976)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
bool b[N];
int s;
basic_string<int>g[N];
void dfs(int x){for(int i:g[x])if(!b[i])b[i]=1,--s,dfs(i);}
int main(){
	int n,m,i,j;
	for(scanf("%d%d",&n,&m);m--;)scanf("%d%d",&i,&j),g[i]+=j;
	for(i=1,s=n*(n-1)/2;i<=n;++i)memset(b,0,N),dfs(i);
	printf("%d",s);
	return 0;
}
```

[做法 3](https://www.luogu.com.cn/record/51297098)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
bitset<N>b[N];
basic_string<int>g[N];
void dfs(int x){
	b[x][x]=1;
	for(int i:g[x]){
		if(!b[i][i])dfs(i);
		b[x]|=b[i];
	}
}
int main(){
	int n,m,i,j;
	for(scanf("%d%d",&n,&m);m--;)scanf("%d%d",&i,&j),g[i]+=j;
	for(i=1,j=n*(n+1)/2;i<=n;++i)dfs(i),j-=b[i].count();
	printf("%d",j);
	return 0;
}
```

[做法 4](https://www.luogu.com.cn/record/51298606)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
basic_string<int>g[N];
int p[N],d[N],q[N];//p[i]表示i在拓扑序的逆序中的排名
bool e[N][N];
bitset<N>b[N],o[259];
int main(){
	int n,m,i,j,l=0,r=0;
	for(scanf("%d%d",&n,&m);m--;)scanf("%d%d",&i,&j),g[i]+=j,++d[j];
	for(i=1;i<=n;++i)if(!d[i])q[++r]=i;//拓扑排序入队
	while(l<r){//拓扑排序
		i=q[++l],p[i]=n-l+1;
		for(int o:g[i])if(!(--d[o]))q[++r]=o;
	}
	for(i=1;i<=n;++i)for(int o:g[i])e[p[i]][p[o]]=1;//重新建边，i>j时e[i][j]才可能等于1
	for(i=1;i<=n;++i)if(b[i][i]=1,!(i&7)){
		for(j=1;j<256;++j)l=j&-j,o[j]=o[j^l]|b[i-7+__lg(l)];//求出一块的子集的bitset
		for(j=i+1;j<=n;b[j++]|=o[l])for(r=l=0;r<8;++r)if(e[j][i-7+r])l|=1<<r;//用子集的bitset更新之后的所有点
	}else for(j=min(n,i/8*8+8);j>i;--j)if(e[j][i])b[j]|=b[i];//更新当前块之后的点
	for(i=1,j=n*(n+1)/2;i<=n;++i)j-=b[i].count();
	printf("%d",j);
	return 0;
}
```


---

## 作者：zhzh2001 (赞：13)

> 参考ZJOI2017 Day2讲课《动态传递闭包问题的探究》
修正了公式显示问题


## 总体思路


### 分析


给定n($n\le1000$)个数的m($m\le10000$)个大小关系，求出最少增加几个大小关系才可以给这些数排序。


很明显，如果没有任何已知关系，答案为$C_n^2=\frac{n*(n-1)}{2}$。要计算已知的关系能使答案减小的值，可以使用传递闭包，一般常用Floyd。


但是由于$n\le1000$，$O(n^3)$不能通过，那么怎么做呢？


### 改进Floyd


\*以下来自课件\*


$t_{i,j}^{(k)}$表示i和j经过前k个点是否连通。


> 定义集合$T_i^{(k)}=\{j\vert t_{i,j}^{(k)}=1\}$

对于$k\ge1$，有


$T_i^{(k)}=\begin{cases}T_i^{(k-1)}&k\notin T_i^{(k-1)} \\ T_i^{(k-1)}\cup T_k^{(k-1)}&k\in T_i^{(k-1)}\end{cases}$


用bitset或手动压位，可以在$O(\frac{n^3}{w})​$求出传递闭包，其中w表示字长，为64或32。


### 使用拓扑序


对于DAG，从后往前枚举拓扑序中的点u，那么u的可达点集为u可以直接到达的点的可达点集取并。


相信大家都会在$O(n+m)$求解拓扑序，其实不需要求出拓扑序。只需dfs，在回溯时取并即可。


时间复杂度为$O(\frac{nm}{w})$，即使不压位也能通过，应该是正解。


## 程序清单


### 改进Floyd


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
bitset<N> mat[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        mat[i][i]=true;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        mat[u][v]=true;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            if(mat[i][k])
                mat[i]|=mat[k];
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=mat[i].count();
    cout<<n*(n-1)/2-ans+n<<endl;
    return 0;
}
```


bitset::count()返回true的位计数，类似于popcount。

由于开始设置了自环，在计算答案时应当去掉。


### 拓扑序


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=10005;
int head[N],v[M],nxt[M],e;
bitset<N> vis,mat[N];
inline void add_edge(int u,int v)
{
    ::v[++e]=v;
    nxt[e]=head[u];
    head[u]=e;
}
void dfs(int k)
{
    mat[k][k]=vis[k]=true;
    for(int i=head[k];i;i=nxt[i])
    {
        if(!vis[v[i]])
            dfs(v[i]);
        mat[k]|=mat[v[i]];
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
            dfs(i);
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=mat[i].count();
    cout<<n*(n-1)/2-ans+n<<endl;
    return 0;
}
```

## 总结


这里介绍了DAG上的两种求静态传递闭包的方法。对于稀疏图使用拓扑序更快，而稠密图则用Floyd更为简单。


如果有环则需要Tarjan缩点后处理，较为复杂。



---

## 作者：Mine_King (赞：9)

在[我的博客](https://www.cnblogs.com/mk-oi/p/14476837.html)食用效果更佳~

## Problem

[洛谷P2881](https://www.luogu.com.cn/problem/P2881)  
有 $n$ 个数，给出 $m$ 个形如 $a>b$ 的关系，问还要调查多少关系才能确定所有数的大小关系。

## Solution

这题应该有两个方法，floyd 和拓扑排序。这里**重点**讲拓扑排序。

首先要明确一点，如果没有给任何关系，那么我们要做的就是每两个调查一下关系，那么需要调查的总次数就是

$$(n-1)+(n-2)+\cdots+3+2+1=\frac{n(n-1)}{2}$$

那么，如果有一些关系了呢？我们就不需要调查这些关系了，把已知关系的数量减去，就是现在要调查的关系。  
那为啥结果不是 $\frac{n(n-1)}{2}-m$ 呢？因为关系有传递性，也就是说，$a>b,b>c$ 可以得出 $a>c$，可以分析出三条关系，但实际给出的只有两条关系。  

接下来的问题就是求我们能分析出的关系了。  
我们把关系画成一张图，$u>v$ 就连一条 $u$ 到 $v$ 的边，这样，两点可以确定关系就是其中一点能到达另一点。

### Floyd做法

众所周知，Floyd 是用来求全源最短路——也就是任意两点的最短路径。那么我们把 Floyd 数组的定义改一下：$dis_{u,v}=1/0$ 表示 $u$ 能否到 $v$。我们发现原来的松弛仍然适用，适用的原因还是关系有传递性。

于是就可以很快写出代码：
```cpp
for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
    		for(int j=1;j<=n;j++)
            	f[i][j]=f[i][j]|(f[i][k]&f[k][j]);
```
最后若`f[i][j]=true`或`f[j][i]=true`则答案 $-1$。

先别急！分析一下代码，发现时间复杂度是 $O(n^3)$ 的，但 $n \le 1000$，跑不过去。

### 拓扑排序做法

还是根据关系有传递性这一性质，我们发现，我们可以按照拓扑序去更新能到达这个点的点，只要在找到一条边时把前面点能到达的点都加到后面的点上即可。（听起来可能有点拗口，仔细理解一下？）

关于拓扑排序的可行性，显然不会出现环，因为环意味着 $a>b,b>c,c>a$，这显然是不可能的。

于是又能写出以下代码：
```cpp
while(!q.empty())
{
	int x=q.front();
    for(int i=1;i<=n;i++)
    	if(g[x][i])//表示x到i有边
        {
        	for(int j=1;j<=n;j++)
            if(f[x][j]) f[i][j]=true//f[a][b]=true表示能分析出a>b的关系
           if(!--in[i]) q.push(i);
        }
}
```
最后若`f[i][j]=true`或`f[j][i]=true`则答案 $-1$。

如果用链式前向星存图，可以做到 $O(n(n+m))$，可通过此题。

### bitset 优化复杂度

**但是但是，我想用 Floyd 怎么办？我拓扑排序想用邻接矩阵存图怎么办？**

满足你！

先讲讲 bitset 是个肾么东西。  
定义一个 bitset：
```cpp
bitset<大小>变量名
```
然后可以把它当一个 bool 数组使用：
```cpp
bitset<100>a;
a[5]=true;
a[98]=false;
```
都是可以的。  
那它比 bool 数组好在哪里？支持位运算！  
我们还可以把 bitset 当成一个数来看，那么它内部的每一个元素都是二进制的一位。  
像这样：
```cpp
bitset<3>a,b;
a[0]=0,a[1]=1,a[2]=1;
b[0]=1,b[1]=0,b[2]=1;
a^=b
```
然后`a`就变成了：
```cpp
a[0]:1
a[1]:1
a[2]:0
```
所以 bitset可以做到区间赋值。接下来就要用这个特性优化两个算法。

#### 对 Floyd 的优化

我们只要枚举中转点和终点，然后对于终点，能走到它的，能走到中转点的都能走到它，那么只要把它们合并一下。  
思考一下，$a$ 有则有，$b$ 有则有，都没有则没有，这对应着什么操作？按位或！

于是可以写出以下代码：
```cpp
for(int k=1;k<=n;k++)
	for(int j=1;j<=n;j++)
    	if(g[k][j])//要确保它们有边。
        	f[j]|=f[k];//合并信息
```
最后求答案只要减去所有的`f[i]`即可。  
哦对了，`a.count()`是询问 bitset 中 $1$ 的个数。

#### 对拓扑排序的优化

已经有了上面Floyd的经验，那么这也很好想，也把赋值信息改成按位或就行了。
```cpp
while(!q.empty())
{
	int x=q.front();
	q.pop();
	for(int i=1;i<=n;i++)
		if(g[x][i])
		{
			f[i]|=f[x];
			if(!--in[i]) q.push(i);
		}
}
```
最后求答案只要减去所有的`f[i]`即可。  
`a.count()`是询问 bitset 中 $1$ 的个数。

**如果你觉得这篇题解帮到了你，就点个赞吧，比心ღ**

---

## 作者：巨型方块 (赞：5)

http://blog.csdn.net/largecub233/article/details/72824615

我的博客，就点赞：D


传递闭包

可以floyd  n\*n\*n

可以拓扑排序

zjoi省选讲过，可以用bitset优化；

题目意思就是要搞出一个表格

表示谁大于谁；

一单有未知，ans++；

显然答案最多是n\*(n-1)/2;

就是每个两个就称一次；

比如n=100,我们最多答案就是4950;

其实用归并排序可以仅仅比较500~600次就好啦；

这个就很尴尬了；

folyd

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=1e3+5;
bool f[N][N];
int n,m,x,y,z,ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        f[x][y]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(f[i][k]&f[k][j])f[i][j]=1;
    for(int i=1;i<=n;i++)if(f[i][i]){printf("-1");return 0;}
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(!f[i][j]&&!f[j][i])ans++;
    printf("%d",(ans-n)/2);
}    
```
拓扑排序


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
struct cs{int to,nxt;}a[N*10];
int head[N],ll,g[N];
bool f[N][N],vi[N],in[N];
int n,m,x,y,z,ans;
void init(int x,int y){
    a[++ll].to=y;
    a[ll].nxt=head[x];
    head[x]=ll;
}
void bfs(){
    queue<int>Q;
    for(int i=1;i<=n;i++)if(!g[i])Q.push(i);
    while(!Q.empty()){
        int x=Q.front();Q.pop();vi[x]=1;
        for(int k=head[x];k;k=a[k].nxt){
            if(vi[a[k].to])exit(puts("-1")&0);
            for(int i=1;i<=n;i++)if(f[i][x])f[i][a[k].to]=1;
            g[a[k].to]--;
            if(g[a[k].to]==0)Q.push(a[k].to);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&x,&y),init(x,y),f[x][y]=1,g[y]++;
    bfs();
    for(int i=1;i<=n;i++){
        if(!vi[i])exit(printf("-1")&0);
        for(int j=1;j<=n;j++)if(!f[i][j]&&!f[j][i])ans++;
    }
    printf("%d",(ans-n)/2);
}
```

bitset（其实很简单的）


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
struct cs{int to,nxt;}a[N*10];
int head[N],ll,g[N];
bool vi[N];
bitset<N>f[N];
int n,m,x,y,z,ans;
void init(int x,int y){
    a[++ll].to=y;
    a[ll].nxt=head[x];
    head[x]=ll;
}
void bfs(){
    queue<int>Q;
    for(int i=1;i<=n;i++)if(!g[i])Q.push(i);
    while(!Q.empty()){
        int x=Q.front();Q.pop();vi[x]=1;
        for(int k=head[x];k;k=a[k].nxt){
            if(vi[a[k].to])exit(puts("-1")&0);
//            for(int i=1;i<=n;i++)if(f[i][x])f[i][a[k].to]=1;
            f[a[k].to]=f[a[k].to]|f[x];
            g[a[k].to]--;
            if(g[a[k].to]==0)Q.push(a[k].to);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&x,&y),init(x,y),f[y][x]=1,g[y]++;
    bfs();
    for(int i=1;i<=n;i++){
        if(!vi[i])exit(printf("-1")&0);
    //    for(int j=1;j<=n;j++)if(!f[i][j]&&!f[j][i])ans++;
        ans+=f[i].count();
    }
    printf("%d",n*(n-1)/2-ans);
}

```

---

## 作者：西卡洛斯 (赞：4)

# P2881 【[USACO07MAR]Ranking the Cows G】

这题主要考虑图的传递关系。

对于有 $n$ 个节点的图，两两之间的关系一共有 $n(n-1)/2$ 种。

思路很简单，从图上的每一个顶点出发，寻找能到达的节点数，用所有的关系减去即可。

我们可以考虑到用邻接数组来存储图，代码如下:

```cpp
#include <iostream>
using namespace std;
const int maxn=1005;
int p[maxn][maxn],n,m,x,y;
int main()
{
	cin>>n>>m;
	while(m--)
	{
		cin>>x>>y;
		p[x][y]=1;
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			if(p[i][k])
			{
				for(int j=1;j<=n;j++)
				{
					p[i][j]=p[i][j]+p[k][j];
				}
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(p[i][j])
			{
				cnt++;
			}
		}
	}
	cout<<n*(n-1)/2-cnt<<endl;
	return 0;
}
```

但是呢这个三层循环会超时，提交上去会TLE两个点。

我们可以采用变长数组+位运算的方法来解决。

把中间改一点就好了：


```cpp
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			if(p[i][k])
			{
				p[i]=p[i]|p[k];
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=p[i].count();
	}
```

蒟蒻的第一篇题解233


---

## 作者：yxy666 (赞：2)

要想知道所有情况，就是两两之间都需要知道谁大谁小。

那么题目已经告诉我们了一些关系，我们可以从这些关系中再找到数据隐含的关系。如，已知 $a_1>a_2$，$a_2>a_3$ ，那么我们就可以推出一个新的关系：$a_1>a_3$ 。如何做到呢？用 dfs 或者 bfs 都能实现。我们先枚举一个点，然后往下遍历，更新父亲节点和下面节点的关系。

那么我们接下来需要询问的次数即为所有的情况-已知的关系数。设x为已知的关系数，那么答案就是 $\dfrac{n^2}{2}$ 。

code :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005,maxe=50005;
int n,ans,m,tot,lnk[maxn],nxt[maxe],son[maxe],que[maxe];
bool vis[maxn][maxn],Vis[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void add_e(int x,int y){son[++tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void Topu(){
	int hed,til;
	for(int i=1;i<=n;i++){//枚举父亲节点
		hed=0,til=1,que[til]=i;
		memset(Vis,0,sizeof Vis);
		Vis[i]=1;
		while(hed!=til){
			hed++;
			for(int j=lnk[que[hed]];j;j=nxt[j]){
				vis[i][son[j]]=vis[son[j]][i]=1;//与儿子节点、孙子节点...确定关系
				if(!Vis[son[j]])Vis[son[j]]=1,que[++til]=son[j];
			}
		}
	}
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		add_e(x,y);vis[x][y]=vis[y][x]=1;
	}
	Topu();
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)if(!vis[i][j])ans++;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Leasier (赞：1)

前置芝士：[传递闭包](https://oi-wiki.org/graph/shortest-path/#_4)

显然地，我们希望每两头奶牛间的关系明确，即令 $x \to y$ 为一条有向边，使得每两个节点互相可达。

那么显然可以用传递闭包预处理。

预处理后，用一共至少需要连的边数减去已经可达的节点的总对数即可。

但这样做是 $O(n^3)$ 的，需要优化。

显然可以用 bitset 进行优化（见前置芝士）。优化后时间复杂度为 $O(\frac{n^3}{w})$。

代码：
```cpp
#include <iostream>
#include <bitset>

using namespace std;

bitset<1007> bs[1007];

int main(){
	int n, m, ans;
	cin >> n >> m;
	ans = n * (n + 1) / 2;
	for (int i = 1; i <= m; i++){
		int x, y;
		cin >> x >> y;
		bs[x][y] = true;
	}
	for (int i = 1; i <= n; i++){
		bs[i][i] = true;
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (bs[j][i]) bs[j] |= bs[i];
		}
	}
	for (int i = 1; i <= n; i++){
		ans -= bs[i].count();
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Skies (赞：1)

这道题用dfs即可

## 思路

要确定n个数的大小关系，就要让这n个数的能力关系形成一条链

![](https://cdn.luogu.com.cn/upload/image_hosting/zxsjue1n.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如上图，可以确定a1>a2>a3>a4

所以，大小关系就一共有
```
1大于2,3,4   三个
2大于3,4     两个
3大于4       一个

```
共n*(n-1)/2个

所以我们只要统计已知的大小关系有多少个，用bitset来存，dfs遍历即可

# code
```cpp
#include<bits/stdc++.h>
#include<bitset>
using namespace std;
const int N=1010;
bitset<N>a[N];
int n,m;
struct node{
	int to,nex;
}ed[N];
int head[N],idx;
void add(int x,int y)
{
	ed[++idx].to=y,ed[idx].nex=head[x],head[x]=idx;
}
bool vis[N];
void dfs(int x)
{
	vis[x]=1;
	a[x][x]=1;
	for(int i=head[x];i;i=ed[i].nex)
	{
		int y=ed[i].to;
		if(!vis[y])
		dfs(y);
		a[x]|=a[y];
	}
} 
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])dfs(i);
	}
	int ans=n*(n-1)/2;
	for(int i=1;i<=n;i++)
	{
		ans-=a[i].count();//返回其中1的个数
	}
	cout<<ans+n;//因为有自己所以要加上n
	return 0;
}  
```


---

## 作者：tuxiaobei (赞：1)

`fj`有$N$($1 \le N \le 1000$)头奶牛，他们的产奶率有所不同，他已经知道$M$($1 \le N \le 10000$)对奶牛的大小关系，他现在想知道所有奶牛的大小大小关系（能够从大到小排列起来），因此他打算再比较$C$对奶牛的大小关系，请问$C$最小是多少？

一个经典的传递闭包问题。

> 在交际网络中，给定若干个元素和若干对二元关系，且关系具有传递性。“通过传递性推导出尽可能多的元素之间的关系”的问题称作传递闭包。

我们建立一个邻接矩阵$f$，$f[i,j]$表示$i$与$j$存在某种特定的关系，在这道题中我们可以表示代表$i$奶牛产奶率大于$j$奶牛。

```cpp
for (int i = 1, a, b; i <= m; i++) {
	scanf("%d%d", &a, &b);
	f[a][b] = true;
}
```

接着，我们就可以采用`Floyd`算法推导出所有的关系。

```cpp
for (int k = 1; k <= n; i++) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[i][j] |= f[i][k] & f[k][j];
		}
	}
}
```

最后统计一下有多少个没推导到的。

时间复杂度$O(n^3)$，这道题$n \le 1000$，会`TLE`。

我们可以通过位运算加速，将`f`数组的一维变成一个长度为$n$的二进制数，免去最外层循环。

最长的`unsigned long long`也只能表示$64$位二进制，我们就要请出好用的`bitset`了！

`std::bitset` 是标准库中的一个存储 `0/1` 的大小不可变容器。严格来讲，它并不属于 `STL`。

`bitset<size>`可以看作是一个长度为`size`的二进制数，其支持所有位运算的操作。

```cpp
bitset<Size>f[Size];
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		if (f[j][i]) f[j] |= f[i];
        //一次性把所有位按位或
	}
}
```

看起来是只有两层循环，但时间复杂度仍然是$O(n^3)$，因为需要按位或$n$位。

但位运算算是比较基本的操作，运算速度很快，一次可以执行$w$位（$w$为计算机的位数）。

所以本算法时间复杂度为$O(\frac{n^3}{w})$，完全可以通过。

最后可以用`bitset`自带的`count()`函数获取$1$的个数。

```cpp
int ans = 0;
for (int i = 1; i <= n; i++) {
	ans += f[i].count();
}
printf("%d", (n* (n - 1)) / 2 - ans);
//只有在!f[i,j]&&!f[j,i]才算没推导出来，也不可能有f[i,j]&&f[j,i]的情况
//所以ans表示推导出来了几组
//总数减去ans即为最终答案
```
完整代码(带快读)
```cpp
#include <bits/stdc++.h>
#define Size 1009 
using namespace std;
bitset<Size>mp[Size];
inline int read() {
    register int ret=0;register char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
 
int main()
{
    register int n,m;
    scanf("%d%d",&n,&m);
    for (register int i=1,a,b;i<=m;i++){
        f[read()][read()]=1;
    }
    for (register int i=1;i<=n;i++){
        for (register int j=1;j<=n;j++){
            if (f[j][i]) mp[j]|=mp[i];
        }
    }
    register int ans=0;
    for(register int i=1;i<=n;i++){
        ans+=f[i].count();
    }
    printf("%d",(n*(n-1))/2-ans);
}
```




---

## 作者：xkcdjerry (赞：0)

这道题思路已经被聚佬讲的很透彻了：求出已经有多少顺序关系，然后用总的关系数 $n \times (n-1)/2$ 减去它就行了。  
本蒟蒻在读了n篇自己 ~~根本看不懂~~ 认为不适合萌新的 `bitset` 优化 Floyd 后，决定给一个更萌新友好的解法。  
众所周知， Floyd 是长这个样子的：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(f[i][k]&&f[k][j])
                f[i][j]=true;
```
但是如果 Floyd 直接这么写，会[T的很惨](https://www.luogu.com.cn/record/48190579)，那么怎么优化呢？  

我们可以发现，如果在进入第二层循环（ 循环变量为 i 的循环 ）的时候 `f[i][k]` 是 `false` 的话，无论 `f[k][j]` 是多少都无法更新，所以可以直接跳过内层循环（ 循环变量为 j 的循环 ）。  

示例：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        if(f[i][k])
            for(int j=1;j<=n;j++)
                if(f[k][j])
                    f[i][j]=true;
```
~~然后就A了~~  

完整代码：
```cpp
#include <cstdio>
#define N 1010

//懒人快乐define
#define ITER(i) for(int i=1;i<=n;i++)

bool vis[N][N];
int n,m;
//核心代码
void floyd()
{
    ITER(k)
        ITER(i)
            if(vis[i][k])
                ITER(j)
                    if(vis[k][j])
                        vis[i][j]=true;
}
                
int main()
{
    scanf("%d%d",&n,&m);
    ITER(i) vis[i][i]=true;
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        vis[a][b]=true;
    }
    floyd();
    int need=n*(n-1)/2;
    //计数时要排除自己为了Floyd给的自环（即vis[i][i]=true;一句）
    ITER(i) ITER(j) if(i!=j&&vis[i][j]) need--;
    printf("%d",need);
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/48190618) [~~开了O2跑得飞快~~](https://www.luogu.com.cn/record/48190636)  


---

## 作者：C6H2CH3_NO2_3 (赞：0)

# 本蒟蒻的第三篇题解

因为这题写题解的人不多，而且都使用了Floyd，还有一些及其高深的方法。比如bitset之类的（像我就不会-_-）。我用了一个别的的方法。思路大致是这样的，首先在输入把一个点的所有前驱记下来，所有后继也记下来。然后循环每个点，从那个点（设为A点）开始往前，往后搜，把所有能遍历到的点记下来。这些点就是可以和A点找到强弱关系的点。然后统计有多少个点没有遍历，把剩下的点的个数加在答案里（<u>记得去重</u>）

-----------



如下是代码

```c++
#include<bits/stdc++.h>
#define ll long long
#define maxn 1005
using namespace std;
ll read(){
	ll f=1,k=0;
	char c=0;
	while(c<'0'||c>'9'){
	if(c=='-')f=-1;
	c=getchar();
	}
	while(c>='0'&&c<='9'){
	k=k*10+c-'0';
	c=getchar();
	}
	return k*f;
}
void out(ll x){
	if(x<0){
	x=-x;
	putchar('-');
	}
	if(x>=10)out(x/10);
	putchar(x%10+'0');
}
ll n,m,fa[maxn],ans;
bool bo[maxn],each[maxn][maxn];
vector<ll>v[maxn],vf[maxn];
void markfa(ll x){
    bo[x]=1;
	for(ll i=0;i<vf[x].size();i++){
		if(bo[vf[x][i]])continue;
		markfa(vf[x][i]);
	}
}
void markson(ll x){
	bo[x]=1;
	for(ll i=0;i<v[x].size();i++){
		if(bo[v[x][i]])continue;
		markson(v[x][i]);
	}
}
int main(){
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read();
		v[x].push_back(y);
		vf[y].push_back(x);
	}
	for(ll i=1;i<=n;i++){
		memset(bo,0,sizeof(bo));
		markfa(i);
		markson(i);
		for(ll j=1;j<=n;j++){
			if(bo[j])continue;
			if(each[i][j]||each[j][i])continue;
			ans++;
			//cout<<i<<' '<<j<<endl;
			each[i][j]=1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

接着来对照代码讲解

```c++
ll n,m,ans;
bool bo[maxn],each[maxn][maxn];
vector<ll>v[maxn],vf[maxn];
```

n和m为题设，ans为答案

bo表示这个点是否和刚开始搜的那个点（也就是A点）联通，也就是说这两个点是否有强弱关系

each用来去重，比如3和4，4和3只算一组。（其实感觉不去重，只把答案除以2似乎也可以）

v和vf分别表示这个点的后继和前驱。

```c++
void markfa(ll x){
    bo[x]=1;
	for(ll i=0;i<vf[x].size();i++){
		if(bo[vf[x][i]])continue;
		markfa(vf[x][i]);
	}
}
void markson(ll x){
	bo[x]=1;
	for(ll i=0;i<v[x].size();i++){
		if(bo[v[x][i]])continue;
		markson(v[x][i]);
	}
}
```

markfa()函数的意义是把从该点(A点)能向前搜到的所有点标记(把bo值设为1)

markson()函数意义是对所有后面的点执行该操作。

--------

接着是主函数

```c++
int main(){
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read();
		v[x].push_back(y);
		vf[y].push_back(x);
	}//读入
	for(ll i=1;i<=n;i++){//检查每个点i
		memset(bo,0,sizeof(bo));//将bo清零
		markfa(i);
		markson(i);//在该点向前搜，向后搜
		for(ll j=1;j<=n;j++){//检查i点和j点是否有强弱关系
			if(bo[j])continue;//如果有，检查下一个点
			if(each[i][j]||each[j][i])continue;//如果已经算过，检查下一个点
			ans++;//如果各种条件都满足，答案加1
			each[i][j]=1;//记下来这两个点已经算过了
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



这个代码实测是能过的。但不知道是不是正解。



---

## 作者：Fearliciz (赞：0)



### 题目大意：

约翰想按照奶牛们的产奶能力给奶牛们排序，已知目前有 $N$ 头奶牛。给你 $M$ 条关系，每条关系表示 $X$ 的能力比 $Y$ 强。现在让你求还需要几条关系来知道还需要几条关系才能准确的知道奶牛的排序。

### 解题步骤：

+ 要想知道奶牛的排序，就要 $C_n^2$ 种关系。

+ 用 $\text{bitset}$  存储。
 

1. 用邻接矩阵存储关系：

```cpp
for (int i = 1; i <= m; i++) {
	int x, y;
	cin >> x >> y;
	f[x][y] = 1;
}
```
2. 如果存在关系，则或等于：

```cpp
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		if (f[j][i]) f[j] |= f[i];
	}
}
```

3. 最后判断是否存在关系，如果存在则计数加 $1$ 。

```cpp
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		if (f[i][j]) cnt++;
	}
}
cout << n*(n - 1) / 2 - cnt;
```
完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int NR=1001;
bitset<NR> f[NR];
int cnt;

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		f[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (f[j][i]) f[j] |= f[i];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (f[i][j]) cnt++;
		}
	}
	cout << n*(n - 1) / 2 - cnt;
}
```

~~dev 真烦，每次运行都自动 style 了。~~

---

