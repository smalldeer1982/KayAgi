# Sightseeing trip

## 题目描述

在桑给巴尔岛的阿德尔顿镇，有一家旅行社。除了许多其他景点外，这家旅行社决定为其客户提供该镇的观光旅游。为了从这个项目中获得尽可能多的收益，旅行社做出了一个精明的决定：需要找到一条始于同一地点并结束于同一地点的最短路线。你的任务是编写一个程序来找到这样的一条路线。

在该镇有 $N$ 个编号为 1 到 $N$ 的交叉点，以及 $M$ 条编号为 1 到 $M$ 的双向道路。两个交叉点可以通过多条道路连接，但没有道路连接同一个交叉点。每条观光路线是由道路编号 $y_1$, ..., $y_k$ 组成的序列，其中 $k > 2$。道路 $y_i (1 \le i \le k-1)$ 连接交叉点 $x_i$ 和 $x_{i+1}$，道路 $y_k$ 连接交叉点 $x_k$ 和 $x_1$。所有的交叉点编号 $x_1$, ..., $x_k$ 应该是不同的。观光路线的长度是该路线所有道路长度的总和，即 $L(y_1)+L(y_2)+...+L(y_k)$，其中 $L(y_i)$ 是道路 $y_i (1 \le i \le k)$ 的长度。你的程序需要找到这样一条观光路线，使其长度最小，或者指明不可能找到这样的路线，因为该镇中没有任何观光路线。

## 样例 #1

### 输入

```
5 7
1 4 1
1 3 300
3 1 10
1 2 16
2 3 100
2 5 15
5 3 20```

### 输出

```
1 3 5 2
```

## 样例 #2

### 输入

```
4 3
1 2 10
1 3 20
1 4 30```

### 输出

```
No solution.```

# 题解

## 作者：ivyjiao (赞：12)

洛谷什么时候把这题 SPJ 修一修啊……

[LOJ AC 记录](https://loj.ac/s/2144268)。

---

相信大家都做过 [P6175 无向图的最小环问题](https://www.luogu.com.cn/problem/P6175)。而那题是本题的严格弱化版。

~~什么？没做过？~~

我们简单回顾下，在那题的最高赞题解中提到：

> 在 Floyd 算法枚举 $k$ 的时候，已经得到了前 $k-1$ 个点中每两个点的最短路径，这 $k-1$ 个点不包括点 $k$，并且他们的最短路径中也不包括 $k$ 点。
>
> 那么我们便可以从这前 $k-1$ 个点中选出两个点 $(i,j)$ 来，因为 $dis_{i,j}$ 已经是此时 $(i,j)$ 间的最短路径，且这个路径不包含 $k$ 点。
>
> 所以连接 $i\to j\to k\to i$ ，我们就得到了一个经过 $(i,j,k)$ 的最小环。

容易发现，本题只需要稍微推导可以转化为以上形式。唯一不同只在输出方案。

那么既然本题的难度升了两个颜色，输出方案想必很难吧！（其实按作者愚见，P6175 应该升绿……）

其实不难，只需要在每次更新最短路时把方案更新就行，记录方案的操作是很常规的，由于数据范围很小，所以不用担心超时。

首先 $j\to k\to i$ 这部分是没变的，只需要把 $i\to j$ 的部分更新掉就行了。具体的方法，就是记录 $p$ 数组，$p_{i,j}=k$ 代表上次 $p_{i,j}$ 是从 $dis_{i,k}+dis_{k,j}$ 转移来的，每次递归跳 $(i,p_{i,j})$ 和 $(p_{i,j},j)$ 即可，而如果 $p_{i,j}=0$，说明 $g_{i,j}$ 即为 $(i,j)$ 最短路径，直接返回。

局部代码如下：

```cpp
void check(int x,int y){
	if(!p[x][y]) return;
	check(x,p[x][y]);
	path.push_back(p[x][y]);
	check(p[x][y],y);
}
......
        for(int i=1;i<k;i++){
            for(int j=i+1;j<k;j++){
                if((long long)dis[i][j]+g[i][k]+g[k][j]<ans){
                    ans=dis[i][j]+g[i][k]+g[k][j];
                    path.clear();
					path.push_back(i);
					check(i,j);
					path.push_back(j);
					path.push_back(k);
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][k]+dis[k][j]<dis[i][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                    p[i][j]=k;
                }
            }
        }
```

完整代码如下：

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,m,u,v,d,dis[101][101],g[101][101],p[101][101],ans=0x3f3f3f3f;
vector<int>path;
void check(int x,int y){
	if(!p[x][y]) return;
	check(x,p[x][y]);
	path.push_back(p[x][y]);
	check(p[x][y],y);
}
int main(){
    cin>>n>>m;
    memset(dis,0x3f,sizeof dis);
    memset(g,0x3f,sizeof g);
    for(int i=1;i<=n;i++){
        dis[i][i]=0;
        g[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        cin>>u>>v>>d;
        dis[u][v]=min(dis[u][v],d);
        dis[v][u]=min(dis[v][u],d);
        g[u][v]=min(g[u][v],d);
        g[v][u]=min(g[v][u],d);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<k;i++){
            for(int j=i+1;j<k;j++){
                if((long long)dis[i][j]+g[i][k]+g[k][j]<ans){
                    ans=dis[i][j]+g[i][k]+g[k][j];
                    path.clear();
					path.push_back(i);
					check(i,j);
					path.push_back(j);
					path.push_back(k);
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][k]+dis[k][j]<dis[i][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                    p[i][j]=k;
                }
            }
        }
    }
    if(ans==0x3f3f3f3f) cout<<"No solution.";
    else for(int i=0;i<path.size();i++) cout<<path[i]<<" ";
}
```

---

## 作者：pangyuchen75 (赞：5)

## 思路

抽象题意：

> 给定 $N$ 个点，$M$ 条无向边，求最小环。

首先发现 $N$ 很小，所以可以用 Floyd。

设原图为 $g$，最短路为 $d$。

考虑如果当前的中间点为 $k$，要更新的最短路的起点为 $i$，终点为 $k$，在还没有更新所有以 $k$ 为中间点的最短路时，其他最短路是不会经过 $k$ 的，所以就形成了一个 $i \to j \to k \to i$ 的环，然后取最小值就可以的到答案了。

然后思考如何求出路径。

可以用 $path$ 记录路径，那么在更新最小环时可以先放入 $k$，再放入 $i$，再放入 $i$ 到 $j$ 的路径，最后再放入 $j$。

现在的问题是如何求出 $i$ 到 $j$ 的路径。

可以设计一个函数 $get\_path(i, j)$。

为了方便实现，再定义一个数组 $mid_{i, j}$ 表示 $i$ 到 $j$ 的中间点，可以在 Floyd 的过程中求。

那么我们就可已得到函数：

```cpp
void get_path(int i, int j) {
    if (!mid[i][j])
        return;
    
    int k = mid[i][j];
    get_path(i, k);
    path[ ++ cnt] = k;
    get_path(k, j);
}
```

最后在把 $path$ 输出即可。

## 代码

C++ 代码如下：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 105;
const int inf = 0x3f3f3f3f;

int n, m;
int g[N][N];
int d[N][N];
int mid[N][N];
int cnt, path[N];
int ans;

void get_path(int i, int j) {
    if (!mid[i][j])
        return;
    
    int k = mid[i][j];
    get_path(i, k);
    path[ ++ cnt] = k;
    get_path(k, j);
}

void inp() {
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof g);

    while (m -- ) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        if (w < g[u][v])
            g[u][v] = g[v][u] = w;
    }
}

void work() {
    memcpy(d, g, sizeof g);
    ans = inf;

    for (int k = 1; k <= n; k ++ ) {
        for (int i = 1; i < k; i ++ )
            for (int j = i + 1; j < k; j ++ )
                if (ans > (LL)d[i][j] + g[i][k] + g[k][j]) {
                    ans = d[i][j] + g[i][k] + g[k][j];
                    cnt = 0;
                    path[ ++ cnt] = k;
                    path[ ++ cnt] = i;
                    get_path(i, j);
                    path[ ++ cnt] = j;
                }

        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    mid[i][j] = k;
                }
    }

    if (ans == inf)
        puts("No solution.");
    else {
        for (int i = 1; i <= cnt; i ++ ) {
            printf("%d", path[i]);

            if (i < cnt)
                putchar(' ');
        }
    }
}

int main() {
    inp();
    work();

    return 0;
}
```

---

## 作者：Taoran_01 (赞：3)

<!--Solution-of-P10927-->

---
### 写在前面
相较于上面的两篇题解，本题解简要证明了 Floyd 求最小环算法，且在路径记录上有所不同。

---
### 题目描述
给定一张无向图，求能构成的边权之和最小的环。  
这里，环被定义为首尾相连的 $m$ 条边，其中 $m\ge3$。

数据范围：$n\le100$。

---
### 性质
1. 最小环一定可以由**一条边** $(u,v)$ 和它的两个端点删去 $(u,v)$ 后的最短路组成。因为如果存在环且删去边后剩下的不是最短路，则最短路可以构成更小的环。且最短路至少包含额外的 $1$ 个节点，总计节点数 $\ge3$。
2. 最小环一定可以由**两条相邻的边** $(u,k)$、$(k,v)$ 和它们的外侧两个端点 $u,v$ 删去 $(u,k)$、$(k,v)$ 的最短路组成。因为如果存在环且删去边后剩下的不是最短路，则最短路可以构成更小的环。且两条边已包含 $3$ 个节点，总计节点数 $\ge3$

下面的算法都是基于这个性质进行的。

---
### 求解
#### Dijkstra
我们枚举删去的每条边 $(u,v)$，对端点 $u$ 跑单源最短路即可。Dijkstra 可以做到 $O(m(m+n)\log n)$。
#### Floyd
考虑 Floyd 的实现：外层循环枚举中间节点 $k$，利用 $i\rightsquigarrow k$ 和 $k\rightsquigarrow j$ 的最短路更新 $i\rightsquigarrow j$ 的最短路。

在这个过程中，开始遍历 $k$ 时，节点编号 $u\in[1,k)$ 内的全源最短路已处理完毕，而依赖节点编号 $u'\in[k,n]$ 的最短路没有被处理。  
即，仅路径上节点编号全部在 $k$ 之前的最短路被确定，而**经过编号在 $k$ 及以后的节点的最短路尚未处理**。

在每一轮 Floyd 之前，对于当前的 $k$，枚举点 $i,j\in[1,k)\land i\neq j$，且 $i,j$ 与 $k$ 各自通过一条边与 $k$ 直接相连。此时，边 $(i,k)$、$(k,j)$ 及最短路 $i\rightsquigarrow j$ 构成环。

该环的性质：
1. 由三个及以上的点构成；
2. 环上最大编号的点是中间的 $k$。

这样，边 $(i,k)$、$(k,j)$ 都未计算进最短路中，保证了当前解的正确性。另外，如果最短路 $i\rightsquigarrow j$ 经过节点 $u$ 且 $u>k$，则该环目前不做贡献，而会在对 $u$ 做 Floyd 之前统计，保证了全局解的最优性。

代码实现上，可以在每次做 Floyd 前更新一下答案。  
此处 $w_{i,j}$ 表示 $(i,j)$ 的边权，若不存在则赋为 $+\infty$，故没有额外判断边的存在性。

[洛谷P6175](https://www.luogu.com.cn/problem/P6175) 无向图的最小环问题
```cpp
for (int k=1; k<=n; ++k) {
	for (int i=1; i<k; ++i) for (int j=1; j<i; ++j) {
		ans=min(ans, d[i][j]+w[i][k]+w[j][k]);
	}
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
	}
}
```

---
### 路径记录
首先借助 Dijkstra 的前驱+递归回溯的思路考虑 Floyd 的路径记录。

记 `pre[i][j]` 表示以 $i$ 为起点的最短路上 $j$ 的前驱。  
使用 $k$ 更新 $i\rightsquigarrow j$ 的最短路时，若松弛成功，则对 $i\rightsquigarrow j$ 的路径进行如下更新：

$$
\text{pre}_{i,j}\leftarrow\text{pre}_{k,j}
$$

参考链表的思想，只需要更改 $j$ 的前缀即可完成对整条路径的修改。

$$
\begin{array}{ccccccc}
i&\longrightarrow&\cdots&\xcancel{\longrightarrow\cdots\longrightarrow}&\xcancel{\text{pre}_{i,j}}&\xcancel\longrightarrow&j\\
&&\downarrow&&&&\uparrow\\
&&k&\longrightarrow&\dots&\longrightarrow&\text{pre}_{k,j}\\
\end{array}
$$

这样对于任意一条路径，从终点不断跳 $\text{pre}$ 即可到达起点，$O(n)$ 还原路径。

区别于 Dijkstra，得益于全源的性质，Floyd 还可以记录后继节点还原路径。  
记 `suf[i][j]` 表示以 $j$ 为终点的最短路上 $i$ 的后继。  
使用 $k$ 更新 $i\rightsquigarrow j$ 的最短路时，若松弛成功，则对 $i\rightsquigarrow j$ 的路径进行如下更新：

$$
\text{suf}_{i,j}\leftarrow\text{suf}_{i,k}
$$

参考链表的思想，只需要更改 $i$ 的后继即可完成对整条路径的修改。

$$
\begin{array}{ccccccc}
i&\xcancel\longrightarrow&\xcancel{\text{suf}_{i,j}}&\xcancel{\longrightarrow\cdots\longrightarrow}&\cdots&\longrightarrow&j\\
\downarrow&&&&\uparrow&&\\
\text{suf}_{i,k}&\longrightarrow&\dots&\longrightarrow&k&&\\
\end{array}
$$

优势：不需要叠栈弹栈/递归回溯；可以处理路径字典序相关问题。

---
### 代码实现
这里我使用了 $\text{suf}$ 记录路径。  
下面的代码中，`w[i][j]` 表示边 $(i,j)$ 的权值，`d[i][j]` 表示当前 $i$ 到 $j$ 的最短路。

初始化 $\text{suf}_{i,j}$ 时全部指向 $j$，这是正确且必要的。先假设 $i\rightsquigarrow j$ 仅含一条边 $(i,j)$，尽管它是不存在（权值为 $+\infty$）。**这与 Floyd 的过程是统一的**，而最短路会在后面的求解过程中松弛更新。

[AC](https://www.luogu.com.cn/record/183765349) 712.00KB 41ms
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 110
#define INF 0x1f1f1f1f1f1f1f1fLL
int n, m; ll len;
ll w[N][N], d[N][N];
int suf[N][N];
vector<int> ans;
vector<int>::iterator it;

signed main() {
	n=read(), m=read(), len=INF;
	memset(d, 0x1f, sizeof(d)); // 看到 Floyd 第四行 ...
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(); ll z=read();
		d[x][y]=min(d[x][y], z), d[y][x]=min(d[y][x], z);
	} // ↓ 这里初始化 suf，设全部指向 j ↓
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) suf[i][j]=j;
	// for (int i=1; i<=n; ++i) suf[i][i]=-1; // 可选，便于判断最短路的终点 ...
	memcpy(w, d, sizeof(w));
	for (int k=1; k<=n; ++k) {
		for (int i=1; i<k; ++i) for (int j=1; j<i; ++j) {
			if (len<=d[i][j]+w[i][k]+w[j][k]) continue;
			len=d[i][j]+w[i][k]+w[j][k]; // ... 这里加了三次，INF设为1F才不会爆
			ans.clear(); // 每次找到更优的答案就清除之前的答案
			for (int x=i; x!=j; x=suf[x][j]) ans.push_back(x); // ... 也可以这样写
			// ↑ 这里只将最短路上 [起点,终点) 一段添加 ... ↑
			// ↓ ... 这里补上终点和两条相邻的边的中间公共节点 ↓
			ans.push_back(j), ans.push_back(k);
		}
		for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
			if (d[i][k]+d[k][j]>d[i][j]) continue;
			d[i][j]=d[i][k]+d[k][j], suf[i][j]=suf[i][k];
		}
	}
	if (len==INF) return puts("No solution."), 0;
	for (it=ans.begin(); it!=ans.end(); ++it) {
		printf("%d", *it); if (it!=ans.end()-1) putchar(' ');
	} // ↑ 注意控制结尾换行符 ↑
	return 0;
}

```

---
### 写在后面
推销一下蒟蒻的 [Blog](https://algo-x.cn/) QWQ

---

## 作者：pangyuchen75 (赞：2)

# 题意

这道题的抽象化题意就是给定一个无向图，然后找最小环。

# 思路

首先我们来研究一下 Floyd 的性质，就是当当前遍历的中间点为 $k$，并且 $i$ 和 $j$ 都小于 $k$ 时，之前的最短路中一定不经过 $k$。

我们设原图两点之间的距离为 $g[i][j]$，最短路为 $d[i][j]$，则可以这样求最小环：

$$min\{d[i][j] + g[i][k] + g[k][j]\}(1 \le k \le n, 1 \le i < k, i < j < k)$$

由于我们求环的时候一定不能经过 $k$，所以应该先求环，再算经过 $k$ 的最短路，而且求最短路时的 $i$，$j$ 都应该是从 $1$ 到 $n$ 的。

其次本题让输出路径，但是出题人十分友善，加了 SPJ，所以只要输出任意一种方案即可，这里详细看代码。

# 代码

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 105;
const int inf = 0x3f3f3f3f;

int n, m;
int g[N][N];
int d[N][N];
int mid[N][N];
int cnt, path[N];
int ans;

void get_path(int i, int j) {
    if (!mid[i][j])
        return;
    
    int k = mid[i][j];
    get_path(i, k);
    path[ ++ cnt] = k;
    get_path(k, j);
}

void inp() {
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof g);

    while (m -- ) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        if (w < g[u][v])
            g[u][v] = g[v][u] = w;
    }
}

void work() {
    memcpy(d, g, sizeof g);
    ans = inf;

    for (int k = 1; k <= n; k ++ ) {
        for (int i = 1; i < k; i ++ )
            for (int j = i + 1; j < k; j ++ )
                if (ans > (LL)d[i][j] + g[i][k] + g[k][j]) {
                    ans = d[i][j] + g[i][k] + g[k][j];
                    cnt = 0;
                    path[ ++ cnt] = k;
                    path[ ++ cnt] = i;
                    get_path(i, j);
                    path[ ++ cnt] = j;
                }

        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    mid[i][j] = k;
                }
    }

    if (ans == inf)
        puts("No solution.");
    else {
        for (int i = 1; i <= cnt; i ++ ) {
            printf("%d", path[i]);

            if (i < cnt)
                putchar(' ');
        }
    }
}

int main() {
    inp();
    work();

    return 0;
}
```

# 完结撒花！

---

## 作者：hemingyuan123 (赞：2)

# P10927 Sightseeing trip

第一次上传（2024.12.28）

## 题目大意
存在一个无向图，求**环的边权和的最小值**。

## 思路分析
无法确定环的起点和终点，所以是一个**多源最短路**，可以用 Floyd 求两个点之间的最短路，记录下路径，再寻找最短的环。

## Floyd
```cpp
	for (int k = 1; k <= n; i++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
```
算法利用遍历每一个中间点 $k$ ,看看能否缩短点 $i$ 与点 $j$ 之间的距离，时间复杂度 $O(n^3)$。

对于本题需要求路径的题目可以把**更新距离所用的点** $k$ 存起来,然后再**从已经遍历过的点中找环**。

定义：$pos[i][j]=k$ 即更新 $i$ 与 $j$ 之间距离的点是 $k$。

之后在递归寻找环的路径，以下是核心部分。

```cpp
void get_j(int x,int y) {
	if(!pos[x][y])return;
	get_j(x,pos[x][y]);//寻找更新x与pos[i][j]的点
	js.push_back(pos[x][y]);
	get_j(pos[x][y],y);//寻找更新pos[i][j]与y的点
}
```

```cpp
	for(int k = 1 ; k <= n ; k++) {
		for(int i = 1 ; i < k ; i++) {
			for(int j = i + 1 ; j < k ; j++) {
				if((long long)dis[i][j] + mp[i][k] + mp[k][j] < ans) }
                    //从前k-1个点中寻找点与k（当前节点）构成环
					ans = dis[i][j] + mp[i][k] + mp[k][j];
					js.clear();
					js.push_back(i);
					get_j(i,j);
					js.push_back(j);
					js.push_back(k);
                    //动态数组存储路径
                    //ans是已知最短路的长度如果当前环的长度大于ans则可直接跳过
				}
			}
		}
		for(int i = 1 ; i <= n ; i++) {
			for(int j = 1 ; j <= n ; j++) {
				if(dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					pos[i][j] = k;//记录更新i,j距离的点k
				}
			}
		}
	}
```
## AC 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int siz = 105;

int dis[siz][siz];
int mp[siz][siz];
int pos[siz][siz];
int n,m;
int ans = 0x3f3f3f3f;
vector<int> js;
void get_j(int x,int y) {
	if(!pos[x][y])return;
	get_j(x,pos[x][y]);
	js.push_back(pos[x][y]);
	get_j(pos[x][y],y);
}
signed main() {
	cin >> n >> m;
	memset(dis,0x3f,sizeof(dis));
	memset(mp,0x3f,sizeof(mp));
	for(int i = 1 ; i <= n ; i++)dis[i][i] = mp[i][i] = 0;
	for(int i = 1 ; i <= m ; i++) {
        int u,v,w;
		cin >> u >> v >> w;
		dis[u][v]=min(dis[u][v],w);
		dis[v][u]=min(dis[v][u],w);
		mp[u][v] =min(mp[u][v],w);
		mp[v][u] =min(mp[v][u],w);
	}
    /*邻接矩阵存图*/
	for(int k = 1 ; k <= n ; k++) {
		for(int i = 1 ; i < k ; i++) {
			for(int j = i + 1 ; j < k ; j++) {
				if((long long)dis[i][j] + mp[i][k] + mp[k][j] < ans) {
					ans = dis[i][j] + mp[i][k] + mp[k][j];
					js.clear();//清空
					js.push_back(i);//起点
					get_j(i,j);
					js.push_back(j);//终点
					js.push_back(k);//构成环的点
				}
			}
		}
		for(int i = 1 ; i <= n ; i++) {
			for(int j = 1 ; j <= n ; j++) {
				if(dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					pos[i][j] = k;
				}
			}
		}
	}
	if(ans == 0x3f3f3f3f)cout << "No solution.";//ans没有变化说明不存在环
	else {
		for(int i = 0 ; i < js.size() - 1 ; i++)cout << js[i] << " ";
		cout << js[js.size()-1];
        /*一个空格也不能多*/
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：2)

## 我的博客

本文知识点参考于：[oi-beats/最短路](https://ntsc-yrx.github.io/oi-beats/site/%E5%9B%BE%E8%AE%BA/%E6%9C%80%E7%9F%AD%E8%B7%AF/Dijkstra/)，[个人博客](https://ntsc.flowus.cn/)。

## 大意

给定无向图，找到最短的含有 $3$ 个节点以上的简单环，输出任意一个方案。

## 做法

先去重边，然后考虑问题。

考虑到数据范围，我们枚举一条边，先假定这条边在环上，然后删去这条边，再从这条边的一个端点开始跑最短路，求出到另外一个端点的最短距离，更新答案（这里的答案指最短的环的长度）。

同时我们记录下哪条边在最短环上，输出答案时，先断掉那条边 $e(u,v)$ 从跑最短路，同时记录每个点的前驱。输出答案时直接从 $v$ 开始不断跳前驱即可。

```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-')
			ff = -1;
		ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
	if (out < 0)
		putchar('-'), out = -out;
	if (out > 9)
		write(out / 10);
	putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 1e3 + 5;
const int INF = 1e9;
const int M = 2e5;
const int MOD = 1e9 + 7;

struct node{
    int v,w;
    int id;
};

vector<node> e[N];


void add(int a,int b,itn c,int id){
    e[a].pb({b,c,id});
    e[b].pb({a,c,id});
}
int d[N][N];
pii t[M];
int cnt;
bitset<N> vis;
int dis[N];
int w[M];
int pre[N];
priority_queue<pii> pq;

void djstr(int s,int banid){
    vis.reset();
    memset(dis,0x3f3f,sizeof dis);
    pq.push(mp(0,s));
    dis[s]=0;
    while(pq.size()){
        int x=pq.top().ps;
        pq.pop();
        if(vis[x])continue;
        vis[x]=1;
        for(auto v:e[x]){
            if(v.id==banid)continue;
            if(!vis[v.v]&&dis[v.v]>dis[x]+v.w){
                pre[v.v]=x;
                dis[v.v]=dis[x]+v.w;
                pq.push(mp(-dis[v.v],v.v));
            }
        }
    }
}

int top,stk[N];

void solve(){
    int n=rd,m=rd;


    memset(d,0x3f3f,sizeof d);
    for(int i=1;i<=m;i++){
        int a=rd,b=rd,c=rd;
        if(d[a][b]>c){
            d[a][b]=d[b][a]=c;
        }
    }


    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            
            if(d[i][j]<INF){
                add(i,j,d[i][j],++cnt);
                t[cnt]=mp(i,j);
                w[cnt]=d[i][j];
            }
        }
    }
// think twice code once and check again

    int ans=INF,ansid=0;

    for(int i=1;i<=cnt;i++){
        djstr(t[i].pf,i);
        if(dis[t[i].ps]+w[i]<ans){
            ans=dis[t[i].ps]+w[i];
            ansid=i;
        }
    }


    if(ans>=INF){
        cout<<"No solution.";
        return ;
    }
    memset(pre,0,sizeof pre);
    djstr(t[ansid].pf,ansid);
    int cur=t[ansid].ps;
    while(cur){
        stk[++top]=cur;
        cur=pre[cur];
    }

    reverse(stk+1,stk+top+1);
    for(int i=1;i<top;i++)cout<<stk[i]<<' ';
    cout<<stk[top];




}

signed main() {
    // freopen("string.in","r",stdin);
    // freopen("string.out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```

---

## 作者：LTTXiaochuan (赞：1)

**题目大意**：输出该无向图的最小环路径。



先假设环的一段已被我们确定，比如说我们已经确定这个环从 $1$ 开始，到 $1$ 结束。

于是我们可以这样操作：枚举直连 $1$ 的点 $u$，然后禁用直连 $1$ 的边 $(u,1)$ 和 $(1,u)$，再以 $u$ 为源点跑单源最短路径。比较 $ans$ 和 $w_{1,u}+dist_u$ 的大小，更新答案即可。

然后拓展到从任意一点开始，直接把 $1$ 替换成任意一点，枚举即可。



时间复杂度：$O(N^2\times N\log N)=O(N^3\log N)$。考虑到数据范围较小，可以选择不使用堆优化的 dijkstra，直接朴素，则复杂度为 $O(N^4)$，可以通过本题。



对于 dijkstra，保存路径是很方便的，只需要每次发生松弛操作时记录回溯点即可，详见代码。



```c++
#include <bits/stdc++.h>
using namespace std;

const int N=110,INF=0x3f3f3f3f;

int e[N][N];
int dis[N];
bool st[N];
int n,m;

int road[N]; //路径回溯数组

vector<int> ans; //路径记录

void dij(int s) //朴素 dij 写法
{
    memset(road,0,sizeof(road));
    memset(st,0,sizeof(st));
    memset(dis,0x3f,sizeof(dis));

    dis[s]=0;

    for(int i=1; i<=n; i++)
    {
        int u=0;
        for(int j=1; j<=n; j++)
            if(st[j]==0 && (u==0 || dis[u]>dis[j]))
                u=j;

        st[u]=1;
        for(int j=1; j<=n; j++)
            if(dis[j]>dis[u]+e[u][j])
            {
                dis[j]=dis[u]+e[u][j];
                road[j]=u; //j 是从 u 过来的
            }
    }
}

void getans(int i,int j)
{
    ans.clear(); //记得先清空
    int p=i;
    while(road[p]) //从 i 开始回溯
    {
        ans.push_back(p); //存路径
        p=road[p];
    }
    ans.push_back(j); //road[j]=0 也要存
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    memset(e,0x3f,sizeof(e));

    cin>>n>>m;
    for(int i=1; i<=n; i++) e[i][i]=0;
    for(int i=1; i<=m; i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        if(x>y) swap(x,y);
        e[x][y]=e[y][x]=min(e[x][y],w); //去重边
    }

    int mink=INF;
    for(int i=1; i<n; i++)
    {
        for(int j=i+1; j<=n; j++)
        {
            if(e[i][j]==INF) continue; //无边跳过

            int tmp=e[i][j];
            e[i][j]=e[j][i]=INF; //禁用这条边
            dij(j);
            e[i][j]=e[j][i]=tmp; //恢复这条边
            if(tmp+dis[i]<mink)
            {
                mink=tmp+dis[i];
                getans(i,j);
            }
        }
    }

    if(ans.empty()) cout<<"No solution.";
    else
    {
        for(int i=0; i<ans.size(); i++)
        {
            if(i==ans.size()-1) cout<<ans[i]; //注意行末无空格
            else cout<<ans[i]<<" ";
        }
    }

    return 0;
}
```

---

## 作者：shandianhailan (赞：1)

# 题意建模
给定一张 $N$ 个点的无向图，请计算图中的最小环并输出路径。
# 思路分析
我们常见求最短路的算法有以下几种：Floyd 算法、Dijkstra 算法、SPFA 算法等。对于任意一个环的最小权值，我们都可以看成两个有边相连的点 $u$ 和 $v$ 的直接距离（边的权值）加上 $u$、$v$ 间不包含边 $(u,v)$   的最短路径。如果采用这思路构建代码，首选  Dijkstra。可是很显然会超时，这时会有一个新的思路：对于 $N$ 个点的图，我们直接枚举点数，从只有单独一个点到所有点再取最小值。如果用数学语言表达，即当点 $u$ 和 $v$ 和 $k$ 构成环时，最小值为 $dis(u,v)+w(i,k)+w(k,j)$，其中 $dis(u,v)$ 是点 $u$ 和 $v$ 的最短路径长度，其中 $1\le k\le N $。这个形式，很有 DP 的味道。显然，我们利用 Floyd 来实现。
# 算法实现
具体 Floyd 的细节这里就不再赘述了，我们重点只讲一下怎么记录路径。可以有了两种办法，一种是题解区很多大佬都用的递归记录，相应地，这里循环也是可行的。具体思路是（以递归为例）：每次用一个  $pre$  数组，记录节点中最短路径的中转点，由于从 $u$ 到 $v$ 的环经过了 $k$ 点，所以可以在记录时开一个  $path$  数组，用来记录每次枚举到 $k$ 的最小路径。将 $u$ 加入路径，每次去找这个点的前驱。我们具体模拟一下  $solve$  函数的运行逻辑。经过以下的流程，成功地动态记录了 Floyd 过程中的最小环。
-  $solve(x,y)$ 函数通过 $pre[x][y]$ 回溯中间节点。
- 若存在中间节点  $pre[x][y]$，则先递归处理 $x$ 到   $pre[x][y]$ 的路径。
- 将中间节点存入 $path$ 数组。
- 再递归处理 $pre[x][y]$ 到 $y$ 的路径。
# 参考程序

```cpp
#include<iostream>
using namespace std;
const int N=1e2+5,INF=0x3f3f3f3f;
int path[N],n,m,idx,pre[N][N];
typedef long long ll;
ll dp[N][N],g[N][N],ans=INF;
inline ll cmin(ll a,ll b) { return a<b?a:b; }
inline void solve(int x,int y)
{
	if(!pre[x][y]) return;
	solve(x,pre[x][y]);
	path[++idx]=pre[x][y];
	solve(pre[x][y],y); 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
		dp[i][j]=(i==j)?0:INF,g[i][j]=dp[i][j];
	
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		dp[a][b]=cmin(dp[a][b],c),dp[b][a]=cmin(dp[b][a],c);
		g[a][b]=cmin(g[a][b],c),g[b][a]=cmin(g[b][a],c);
	}
	
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<k;i++)
	    for(int j=i+1;j<k;j++)
	    	if((ll)dp[i][j]+g[i][k]+g[k][j]<ans)
		    {
		    	ans=dp[i][j]+g[i][k]+g[k][j];
		    	idx=0;
		    	path[++idx]=k;
		    	path[++idx]=i;
		    	//int p=j;
		    	//while(p!=i) {path[++idx]=p,p=pre[p][i];}
//上面这两行是循环记录的方法。
				solve(i,j);
				path[++idx]=j;
		    	 	
			}
			
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(dp[i][j]>dp[i][k]+dp[k][j])
			{
				dp[i][j]=dp[i][k]+dp[k][j];
				pre[i][j]=k;
			}
	}
	    
	if(ans==INF) cout<<"No solution.";	
	else 
	{
		bool flag=1;
	 	for(int i=1;i<=idx;i++)
		{
			if(flag) cout<<path[i],flag=0;//末尾无空格
		   	else cout<<' '<<path[i];
		}
	}
	return 0;
}
```

---

## 作者：a202401006 (赞：1)

# 说在前面的话
[题目传送门](https://www.luogu.com.cn/problem/P10927)

备注：本题的测试点似乎有点问题，建议前往[这里](https://loj.ac/p/10072)进行测试。[对方正确记录](https://loj.ac/s/2311890)。

如果你发现你只对了一个点，请注意：行末不要有多余空格，可以参考一下这篇题解。[洛谷正确记录](https://www.luogu.com.cn/record/217104193)。
# 解析
## 题目大意
给出一些点，以及每两个点的路长度，需要构成一个闭环。求最小环。
## 考察知识
本题考查弗洛伊德算法灵活解决问题的运用。
## 思路
首先输入。用一个 $route$ 记录所有交叉点，接着三重循环，循环里判断如果点 $i$ 和点 $j$ 的距离加上点 $i$ 到点 $k$ 的距离和点 $k$ 到点 $j$ 的距离小于目前的闭环值，说明可以构成一个环，更新闭环值，将点 $i$ 以路线的点的形式推进去，检查点 $i$ 至点 $j$ 之间的借助点设为路线中的一个点，将别的点也推进去。接着套用弗洛伊德算法的三重循环模板更新距离。最后如果闭环值为原值，则不行，否则输出点。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1008,INF=0x3f3f3f;
int n,m,u,v,d,dis[N][N],themap[N][N],check_ok[N][N],circle=INF;
vector<int> route;
void check(int x,int y)
{
	if(!check_ok[x][y])//由于check_ok数组check_ok[i][j]=k表示从i到k再从k到j，所以k不能为0 
	{
		return ;//返回 
	}
	check(x,check_ok[x][y]);//递归检查x到check_ok[x][y]是否有个借助的点 
	route.push_back(check_ok[x][y]);//将x到y的借助点转移 
	check(check_ok[x][y],y);
}

int main()
{
	memset(dis,INF,sizeof(dis));
    memset(themap,INF,sizeof(themap));
    /*设为正无穷*/ 
    cin>>n>>m;//输入 
    for(int i=1;i<=n;i++)
	{
        dis[i][i]=0;
        themap[i][i]=0;
    }
    /*点到自身距离为0*/
    for(int i=1;i<=m;i++)
	{
        cin>>u>>v>>d;//输入 
        dis[u][v]=min(dis[u][v],d);
        dis[v][u]=min(dis[v][u],d);
        /*将dis数组更新到最小值*/ 
        themap[u][v]=min(themap[u][v],d);
        themap[v][u]=min(themap[v][u],d);
        /*将themap数组更新到最小值*/ 
    }
    for(int k=1;k<=n;k++)
	{
        for(int i=1;i<k;i++)
		{
            for(int j=i+1;j<k;j++)
			{
                if((long long)dis[i][j]+themap[i][k]+themap[k][j]<circle)//如果点i和点j的距离加上点i到点k的距离和点k到点j的距离小于目前的闭环值，说明可以构成一个环 
				{
                    circle=dis[i][j]+themap[i][k]+themap[k][j];//更新闭环值 
                    route.clear();//清空 
					route.push_back(i);//将点i以路线的点的形式推进去 
					check(i,j);//检查点i至点j之间的借助点设为路线中的一个点 
					route.push_back(j);//与i同理 
					route.push_back(k);//与i同理 
                }
            }
        }
        for(int i=1;i<=n;i++)
		{
            for(int j=1;j<=n;j++)
			{
                if(dis[i][k]+dis[k][j]<dis[i][j])
				{
                    dis[i][j]=dis[i][k]+dis[k][j];
                    check_ok[i][j]=k;
                }
            }
        }
        /*Floyd算法*/ 
    }
    if(circle==INF)//如果闭环值为原初始值，那么不是闭环 
	{
		cout<<"No solution.";
	}
    else//闭环，输出route中的每个点 
	{
		for(int i=0;i<route.size()-1;i++) 
		{
			cout<<route[i]<<" ";
		}
		cout<<route[route.size()-1];//不要输出多余空格！
	}
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意
给定一个无向图，求出其长度最小的环的路径。
## 回顾
首先，这道题是 [P6175 无向图的最小环问题](https://www.luogu.com.cn/problem/P6175)的升级版，因此先回顾一下当时的核心代码，主要就是使用了Floyd 的思想进行枚举。
```cpp
for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++)
				ans=min(ans,dis[i][j]+mp[i][k]+mp[k][j]); //类似Floyd的操作，枚举每种情况的环
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //更新每两个点之间的距离
				dis[j][i]=dis[i][j];
			}
	}
```

## 思路
这道题实际上就是在弱化版中每次 Floyd 更新时记录一下是如何走到的。由于 Floyd 的实现方法，我们在记录 $i\to j$ 时无法直接得到路径，使用 Update 函数实现，记录 $x\to y$ 之间的最短路径方式。

于是，Floyd 部分会变成这样：
```cpp
for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++){
				if(ans>dis[i][j]+mp[i][k]+mp[k][j]){
					ans=dis[i][j]+mp[i][k]+mp[k][j];
					path.clear(); //发现了新的路径
					path.push_back(i); //起点
					Update(i,j); //中间的路径
					path.push_back(j);
					path.push_back(k);
				}
			}
```
而 Update 函数起到的作用是记录两点之间最短路径，$p_{i,j}=k$ 代表 $i\to j$ 的最短路经过 $k$ 得到。使用递归不断迭代 $i\to p_{i,j}$ 和 $p_{i,j}\to j$，找到最短路径，代码如下:
```cpp
void Update(int x,int y){
	if(!p[x][y]) //没有存过这条边
		return;
	Update(x,p[x][y]);
	path.push_back(p[x][y]);
	Update(p[x][y],y);
}
```
在更新距离时，每次如果 $dis_{i,k}+dis_{k,j}<dis_{i,j}$，那么经过 $i\to k\to j$ 会更优，则 $p_{i,j}=k$，同时 $dis_{i,j}=dis_{i,k}+dis_{k,j}$。

```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(dis[i][j]>dis[i][k]+dis[k][j]){
			dis[i][j]=dis[i][k]+dis[k][j];
			p[i][j]=k;
		}
	}
```
## 注意
输出中提到：
> 行末不应有多余空格或者换行符。

因此，SPJ 是好的，只是输出毒瘤。
## 代码
因此，整体的代码也就出来了，就是将前面的思路整合一下。由于前文都有思路和注释，所以此处就不放注释了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105,INF=1e17; 
int n,m,dis[N][N],mp[N][N],p[N][N],ans=INF;
vector<int> path;
void Update(int x,int y){
	if(!p[x][y])
		return;
	Update(x,p[x][y]);
	path.push_back(p[x][y]);
	Update(p[x][y],y);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				mp[i][j]=dis[i][j]=INF;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		dis[u][v]=min(dis[u][v],w);
		dis[v][u]=min(dis[v][u],w);
		mp[u][v]=min(mp[u][v],w);
		mp[v][u]=min(mp[v][u],w);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++){
				if(ans>dis[i][j]+mp[i][k]+mp[k][j]){
					ans=dis[i][j]+mp[i][k]+mp[k][j];
					path.clear();
					path.push_back(i);
					update(i,j);
					path.push_back(j);
					path.push_back(k);
				}
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(dis[i][j]>dis[i][k]+dis[k][j]){
					dis[i][j]=dis[i][k]+dis[k][j];
					p[i][j]=k;
				}
			}
	}
	if(ans==INF)
		cout<<"No solution.";
	else{
		for(int i=0;i<path.size()-1;i++)
			cout<<path[i]<<' ';
		cout<<path[path.size()-1];
	}
	return 0;
}
```
## 附记
本文基于 [@ivyjiao](https://www.luogu.com.cn/user/578029) 的[题解](https://www.luogu.com.cn/article/fczy3fuw)进一步详细说明，感谢作者的授权。

---

## 作者：FZY_CZY (赞：1)

# 题意
这个题目感觉有点抽象，所以我决定把题目简化，便于进一步的思考。
以下是简化后的题意：
>给定一张无向图，求图中一个至少包含 3 个点的环，环上的节点不重复，并且环上的边的长度之和最小。
>
>该问题称为无向图的最小环问题。
>
>你需要输出最小环的方案，若最小环不唯一，输出任意一个均可。

# 思路
这是一种最优化的问题，所以我们可以从集合的角度来考虑这个问题，我们把所有环进行分类，把这些环分成：最大节点为 $1$ 的环，最大节点为 $2$ 的环，最大节点为 $3$ 的环……最大节点为 $n-1$ 的环，最大节点为 $n$ 的环。然后我们对所有情况的结果取一个 $\min$ 即可。

我们考虑用 Floyd 算法来写这道题，我们都知道，Floyd 有三层循环（我的写法）：第一层是枚举中间的节点 $k$，第二层和第三层枚举起始节点 $i,j$。我们就发现 Floyd 和我们这道题的考虑方法具有通性。我们把 Floyd 和我们提到的集合的思路结合到一起，我们就有一种思路，就是当我们枚举到一个 $k$ 的时候，$i$ 到 $j$ 的路径分为两段，$i$ 到 $k$，$k$ 到 $j$，那么我们分解后的第一段路径就是最大节点为 $k$ 的集合，第二段路径就是最大节点为 $j$ 的集合。因为我们知道这两段路径的长度都是固定的，所以，我们希望 $i,j$ 之间的距离尽可能的小，在这个时候，我们的环的长度也是最小的。

参考图片：![](https://cdn.luogu.com.cn/upload/image_hosting/gx2b0svu.png)
(作者画技，见谅)

---
然后我们就需要在 Floyd 的时候解决另一个难点——求方案。

学过 Floyd 的人都知道，Floyd 中用到的数组原本是三维的，因为考虑到其中一维不起作用，所以改为两维，求方案也是如此，我们可以在更新答案的时候同时更新我们的方案，而方案的更新方法就是开一个新的二维数组 $pos$，我们都知道图论中的最短距离是满足一个三角不等式的，$d_{i,j}\le d_{i,k}+d_{j,k}$，而 $pos$ 数组就是用来存储这个三角不等式能够取等的点 $k$，然后更新的时候就可以借助 $pos$ 数组递归，每次递归 $i,k$ 和 $k,j$ 两条路径，这样就可以更新方案了。

总结：这道题运用了 DP 的思路和图论问题的性质。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
const int INF=0x3f3f3f3f;
int n,m;
int d[N][N],g[N][N];
int pos[N][N];
int path[N],cnt;
void get_path(int i,int j)
{
    if (pos[i][j]==0) return ;
    int k=pos[i][j];
    get_path(i,k);
    path[cnt++]=k;
    get_path(k,j);
}
signed main(){
    cin>>n>>m;
    memset(g,0x3f,sizeof g);
    for (int i=1;i<=n;i++) g[i][i]=0;
    while (m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b]=g[b][a]=min(g[a][b],c);
    }
    int res=INF;
    memcpy(d,g,sizeof d);
    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<k-1;i++)
            for (int j=i+1;j<k;j++)
                if ((long long)d[i][j]+g[j][k]+g[k][i]<res)
                {
                    res=d[i][j]+g[j][k]+g[k][i];
                    cnt=0;
                    path[cnt++]=k;
                    path[cnt++]=i;
                    get_path(i,j);
                    path[cnt++]=j;
                }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                if (d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    pos[i][j]=k;
                }
    }
    if (res==INF) cout<<"No solution.";
    else
        for (int i=0;i<cnt;i++) cout<<path[i]<<" ";
    return 0;
}
``````

---

## 作者：Camellia2025 (赞：1)

题意：求一个无向图的最小环。

## solution

考虑 Floyd。

在枚举 $k$ 时，若存在一条最短路的路径不经过点 $k$ 及大于 $k$ 的点，则该路径已被求出，若点 $i$ 和 $j$ 都有与 $k$ 连边，那么可以作为一个更新答案的环。

于是在枚举 $i$ 和 $j$ 前，先用两层循环枚举任意两个小于 $k$ 且不相等的点，它的当前最短路径虽然不一定是实际上的最短路径但也可以作为更新答案的一环。

路径就每次记录以 $i$ 为开头 $j$ 的后继是谁即可。

## code

前几篇的代码已经很标准了。

~~码风那么丑，就别丢脸了。~~

thx。

---

## 作者：ask_silently (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10927)

## 题目大意

给定一张无向图，求图中一个至少包含 $3$ 个点的环，环上的节点不重复，并且环上的长度之和最小。若存在方案，输出任意一个方案，否则输出 `No solution.`。图的节点数不超过 $100$。

## Step $1$

作者在做这道题的时候，并未思考的 Floyd 算法的性质，因此该篇题解虽然空间复杂度大了一点，可思路较其他题解更简单易懂。

考虑到一个环上的节点至少为三个，则将其分为三部分：

- $i$ 节点至 $k$ 节点的最短路，其中不包含 $j$。
- $k$ 节点至 $j$ 节点。
- $j$ 节点至 $i$ 节点。

发现我们可以枚举 $i,j,k$，那么现在问题就来到了第一步。

这是一个全源最短路，Floyd 的本质是 dp，那可以新增一个状态 $p$，则 $dp_{i,j,p}$ 代表 $i$ 与 $j$ 之间的最短路距离，其中不包含 $p$。

转移也非常简洁，原本的 $dp_{i,j}=\min(dp_{i,j},dp_{i,k}+dp_{k,j})$ 改为 $dp_{i,j,p}=\min(dp_{i,j,p},dp_{i,k,p}+dp_{k,j,p})$ 即可。

## Step $2$

现在的问题来到输出方案上。

发现只需要关心 $i$ 节点至 $k$ 节点的最短路（不包含 $j$）的路径即可。

那么就可以记录下来每个 $dp_{i,j,p}$ 是从哪个地方转移的，最后做一个递归即可。

空间复杂度 $O(n^3)$，时间复杂度 $O(n^4)$，可以通过本题。

## AcCode


```cpp
#include <bits/stdc++.h>
using namespace std;
#define INT_MAX (int)(1e8)
#define pr pair<int,int>

const int N=101;
const int M=2e6+10;

int n,m;
int a[N][N],b[N][N];
int dp[N][N][N];

pr fro[M];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

int calc(int x,int y,int z){
	return x*(n+1)*(n+1)+y*(n+1)+z;
}

void floyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int l=1;l<=n;l++){
					if(dp[i][k][l]+dp[k][j][l]<dp[i][j][l])
						fro[calc(i,j,l)]={calc(i,k,l),calc(k,j,l)};
					dp[i][j][l]=min(dp[i][j][l],dp[i][k][l]+dp[k][j][l]);
				}
}

int ans1,ans2,ans3;

void dfs(int x){
	if(fro[x].first<0){
		cout<<-fro[x].second<<" ";
		return;
	}
	dfs(fro[x].first);
	dfs(fro[x].second);
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				dp[i][j][k]=INT_MAX;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=INT_MAX;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(w<a[u][v]) b[u][v]=i,b[v][u]=i;
		a[u][v]=min(a[u][v],w),a[v][u]=min(a[v][u],w);
		for(int j=1;j<=n;j++){
			int x=w;
			if(j==u||j==v) x=INT_MAX;
			if(x<dp[u][v][j])
				fro[calc(u,v,j)]={-u,-v},fro[calc(v,u,j)]={-v,-u};
			dp[u][v][j]=min(dp[u][v][j],x);
			dp[v][u][j]=min(dp[v][u][j],x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) dp[i][i][j]=INT_MAX;
			else dp[i][i][j]=0;
		}
	}
	floyd();
	int ans=INT_MAX;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j||a[i][j]==INT_MAX) continue;
			for(int k=1;k<=n;k++){
				if(i==k||j==k||a[j][k]==INT_MAX||dp[i][k][j]==INT_MAX) continue;
				if(a[j][k]+a[i][j]+dp[i][k][j]<ans)
					ans=a[j][k]+a[i][j]+dp[i][k][j],
					ans1=calc(i,k,j),ans2=j,ans3=i;
			}
		}
	}
	if(ans==INT_MAX) cout<<"No solution.";
	else{
		cout<<ans3<<" ";
		dfs(ans1);
		cout<<ans2;
	}
	return 0;
}


```

---

