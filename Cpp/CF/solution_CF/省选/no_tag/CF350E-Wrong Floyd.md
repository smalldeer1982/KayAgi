# Wrong Floyd

## 题目描述

Valera 正在研究寻找最短路径的算法。他最近学习了 Floyd 算法，因此决定进行实践。  

Valera 已经编写了一个代码，用于计算一个包含 $n$ 个顶点和 $m$ 条边的无向连通图中任意两顶点之间的最短距离。该图不含自环和重边。此外，Valera 决定标记部分顶点，他恰好标记了 $k$ 个顶点 $a_1, a_2, \ldots, a_k$。  

Valera 的代码如下： 

```
ans[i][j] // 顶点 i, j 之间的最短距离 
a[i]  // Valera 标记的顶点集合
for(i = 1; i <= n; i++) 
{    
	for(j = 1; j <= n; j++) 
	{        
		if (i == j)            
			ans[i][j] = 0;        
		else            
			ans[i][j] = INF;  //INF 表示极大值     
	}
}    
for(i = 1; i <= m; i++) 
{    
	读入一条连接顶点 u 和 v 的无向边;    
	ans[u][v] = 1;    
	ans[v][u] = 1;
}
for (i = 1; i <= k; i++) 
{    
	v = a[i];    
	for(j = 1; j <= n; j++)        
		for(r = 1; r <= n; r++)            
			ans[j][r] = min(ans[j][r], ans[j][v] + ans[v][r]);
}
```

Valera 发现他的代码是错误的。请帮助他：给定标记的顶点集合 $a_1, a_2, \ldots, a_k$，构造一个包含 $n$ 个顶点和 $m$ 条边的无向连通图，使得 Valera 的代码对至少一对顶点 $(i,j)$ 计算出错误的最短距离。构造的图必须不含自环和重边。如果不存在这样的图，输出 -1。

## 说明/提示

翻译由 DeepSeek R1 完成  

## 样例 #1

### 输入

```
3 2 2
1 2
```

### 输出

```
1 3
2 3
```

## 样例 #2

### 输入

```
3 3 2
1 2
```

### 输出

```
-1
```

# 题解

## 作者：3493441984zz (赞：5)

# 前言：

#### 趁着还没有题解，赶紧水一波$qwq$

#### 这题其实真的不难
------------
# 回归正题:

我们首先要明白$floyd$的思想，相信你都来做这道~~水~~题了，肯定不陌生，简单的手玩后，我们可以发现：

只要有任意一个点只跟非标记点相连的话，是更新不出它到另外的标记点的距离的，并且题目中$k>=2$是很关键的，光说不清楚，举个例子：

$n=5,m=4,k=2$，标记点为$1,5$时：

只需要如下连：

$1-2,1-3,1-4,4-5$，就能够$hack$，为什么呢，我们看到题目中是以标记点为中间点来更新最短距离

那么以$1$为标记点时，能更新出：$2-3,2-4,3-4$的最短距离，而以$5$为标记点时,什么都不能更新出，所以$1-5$的最短距离就不能算出来

那么总结一下连边的规律：

$1$、随便选一个点（下面代码选的是随机的标记点），只跟非标记点相连

$2$、把所有未加入图中的点加入，向除了上面选的点的点连边

$3$、如果边数不满$m$的话，想怎么连就怎么连$qwq$，前提还是不和上面的点相连

那么输出$-1$的情况呢？？

$1$、当所有点都是标记点的时候，其实就是一个完整的$floyd$，难道你能$hack$吗，~~（逃）~~

$2$、当$m$很大，让你不能够腾出一个点只跟非标记点相连的时候，输出$-1$，具体的话是$(n-1)*(n-2)/2+n-k$，为什么呢？其实是我们要保证一个点只跟非标记点连边，那么连的边数就是$n-k$，那么其他的点随便怎么连，但是最多就是个完全图，也就是$(n-1)*(n-2)/2$了，相加即可

接下来是美滋滋的代码时间~~~
~~~cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 307
using namespace std;
int n,m,k,it,it1,line;
bool g[N][N],mark[N],vis[N];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	if((k==n)||(m>(n-1)*(n-2)/2+n-k))
	{
		printf("-1");
		return 0;
	}
	for(int i=1;i<=k;++i)
	{
		int in;
		scanf("%d",&in);
		mark[in]=1;
		it=in;
	}
	vis[it]=1;
	for(int i=1;i<=n;++i)
		g[i][i]=1;
	for(int i=1;i<=n;++i)
	{
		if(i==it||mark[i])
			continue;
		printf("%d %d\n",i,it);
		++line;
		vis[i]=1;
		g[i][it]=g[it][i]=1;
		it1=i;
		if(line==m)
			return 0;
	}
	for(int i=1;i<=n;++i)
	{
		if(line==m)
			return 0;
		if(vis[i])
			continue;
		printf("%d %d\n",i,it1);
		++line;
		g[i][it1]=g[it1][i]=1;
		vis[i]=1;
	}
	for(int i=1;i<=n;++i)
	{
		if(line==m)
			return 0;
		if(i==it)
			continue;
		for(int j=1;j<=n;++j)
		{
			if(j==it||g[i][j])
				continue;
			if(line==m)
				return 0;
			printf("%d %d\n",i,j);
			g[i][j]=g[j][i]=1;
			++line;
		}
	}
	return 0;	
}
~~~

---

## 作者：Lyccrius (赞：2)

回顾 Floyd 求最短路的过程，枚举中转点来进行松弛操作。

在 SPFA 及 Dijkstra 求最短路的过程中，一个点 $u$ 到其他点 $v$ 的边能够用来更新最短路，只有当 $v$ 作为中转点时才行。

然后考虑 $u$ 到其他点的最短路求不出来，就是与 $u$ 相邻的所有点都不是标记点。

于是我们随便找出一个点 $u$，与非标记点连边。

剩下的点只要不连到 $u$ 想砸连咋连。

考虑无解的情况，$n = k$ 肯定无解。

还有其它情况吗？

按照上面的连边方法，边数是有上界的，就是完全图的边数减去除 $u$ 外的标记点数。

为了使上界更大，$u$ 应该取标记点，这样减去的数量为 $k - 1$。

因此 $m \gt \frac{n(n - 1)}{2} - k + 1$ 时无解。

---

## 作者：Trimsteanima (赞：2)

### Description

给定n个点，m条边，k个标记点，hack掉给出的程序。
### Solution

先考虑不可能hack掉的情况。当所有点都是标记点的时候肯定不能hack掉，也就是$n=k$。还有就是$m > n * (n - 1) / 2 - k + 1$（也就是最多可构造的边）。

能hack的情况下，我们先将标记点与非标记点连起来，然后将非标记点与未加入图的边连起来，这样保证了图的联通性，最后随便加边凑到$m$条边
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, k, x, y, a[1100], b[1100], f[1100][1100];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	if (n == k || m > n * (n - 1) / 2 - k + 1) //不能hack掉的情况
		return printf("-1\n"), 0;
	for (int i = 1; i <= k; i ++) {
		scanf("%d", &a[i]);
		b[a[i]] = 1;
	}
	x = a[1];
	if (a[1] == 1) y = 2; else  y = 1;
	for (int i = y + 1; i <= n; i ++)
		if (i != x) {
			if (x == y)
				y ++;
			printf("%d %d\n", y, i);
			f[y][i] = f[i][y] = 1, m --; y ++;
		}
	for (int i = 1; m && i <= n; i ++)
		if (!b[i])
			f[x][i] = f[i][x] = 1, m --, printf("%d %d\n", x, i);
	for (int i = 1; m && i <= n; i ++)
		if (i != x)
			for (int j = i + 1; m && j <= n; j ++)
				if (j != x && !f[i][j]) {
					f[i][j] = f[j][i] = 1, m --;
					printf("%d %d\n", i ,j);
				}
	return 0;
}

/*
43 76 6
24 11 30 21 35 1
*/
```


---

## 作者：lilong (赞：0)

考虑最多能构造多少条边。由于只需要一对点的最短路不正确即可，我们不妨让**一对关键点的最短路**不正确，即不能找到一个同样为关键点的转折点。那么只需要让这个关键点不与其它关键点连边即可（这样一定求不出最短路），即最多可以连 $\frac{n(n-1)}{2}-(k-1)$ 条边。为了保证图连通，可以先让这个关键点与所有非关键点连边，再选一个非关键点与剩余关键点连边。剩下的边随便连。无解情况：

- $n=k$，此时即是标准的 Floyd。
- $m>\frac{n(n-1)}{2}-(k-1)$，超过边数最大值。


```cpp
#include<iostream>
#include<cstdio>
#define N 310
using namespace std;
int n,m,k,a[N],vis1[N],rt;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i],vis1[a[i]]=1;
    if(n==k||m>n*(n-1)/2-(k-1)){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++)
        if(!vis1[i]){
            rt=i;
            cout<<i<<' '<<a[1]<<'\n';
            m--;
            if(m==0)return 0;
        }
    for(int i=1;i<=n;i++)
        if(vis1[i]&&i!=a[1]){
            cout<<rt<<' '<<i<<'\n';
            m--;
            if(m==0)return 0;
        }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(i==a[1]||j==a[1]||i==rt&&vis1[j]||vis1[i]&&j==rt)continue;
            cout<<i<<' '<<j<<'\n';
            m--;
            if(m==0)return 0;
        }
    return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

首先要卡 Floyd 的关键就是存在某两个点 $x,y$，满足这两个点之间的所有最短路经过的点中（除 $x,y$ 本身）至少有一个非关键点。

因此很容易想到如下构造法，先随便找一个关键点 $K$，然后把所有非关键点和 $K$ 连边（当然如果所有点都是关键点就显然无解）。

接下来先随便连边保证图连通（刚开始没看到这条，以为方法假了），然后再随便连边把边数卡到 $m$ 条即可。

注意在任何时候都不能让 $K$ 和其它点连边，然后算一下这样构造的边数上界为 $\frac{(n-1)\times(n-2)}{2}$，当 $m$ 超过这个值是就无解。
## Code
```cpp
#include<cstdio>
#include<iostream>
#include<utility>
#include<vector>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<set>
#include<array>
#include<random>
#include<bitset>
#include<ctime>
#include<limits.h>
#include<assert.h>
#include<unordered_set>
#include<unordered_map>
#define RI register int
#define CI const int&
#define mp make_pair
#define fi first
#define se second
#define Tp template <typename T>
using namespace std;
typedef long long LL;
typedef long double LDB;
typedef unsigned long long u64;
typedef __int128 i128;
typedef pair <int,int> pi;
typedef vector <int> VI;
typedef array <int,3> tri;
const int N=305;
int n,m,k,a[N],vis[N],ext[N],G[N][N];
int main()
{
	//freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
	RI i,j; for (scanf("%d%d%d",&n,&m,&k),i=1;i<=k;++i) scanf("%d",&a[i]),vis[a[i]]=1;
	if (k==n||1LL*(n-1)*(n-2)/2LL+n-k<m) return puts("-1"),0;
	int pos; for (ext[a[1]]=i=1;i<=n;++i)
	if (!vis[i]) printf("%d %d\n",a[1],i),G[a[1]][i]=G[i][a[1]]=ext[i]=1,--m,pos=i;
	for (i=1;i<=n;++i) if (!ext[i])
	printf("%d %d\n",pos,i),G[pos][i]=G[i][pos]=1,--m;
	for (i=1;i<=n&&m;++i) if (i!=a[1])
	for (j=i+1;j<=n&&m;++j) if (j!=a[1])
	if (!G[i][j]) printf("%d %d\n",i,j),G[i][j]=G[j][i]=1,--m;
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
当 $n=k$ 或 $m>n(n-1)/2-k+1$ 时输出 $-1$。证明：$n=k$ 时与直接跑没有区别；考虑 ```hack``` 掉 $i,j$ 两点（使它们的最短路为 $2$），首先 $i,j$ 都为被标记的点时最大边数最大，其次 $i,j$ 之间不能连边，最后每个其它的被标记的点都最多只能与 $i,j$ 中的一个连边，所以一共会少 $-1-(k-2)$ 条边。

连边顺序：为保证是连通图所以挑出 $1$ 个没被标记的点与其它所有点连边，其次将所有没被标记的点内部互相连边，然后将 $k-1$ 个被标记的点内部互相连边（要留 $1$ 个点使这个点与某个被标记的点的最短路大于 $2$），最后将没被标记的点与被标记的点连边。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int a[305];
int b[305],sum;
int g[305][305];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m>>k;
	if(n*(n-1)/2-k+1<m||n==k) return cout<<-1,0;
	for(int i=1;i<=k;i++) cin>>a[i],b[a[i]]=1;
	for(int i=1;i<=n;i++)//连成连通图 
	{
		if(!b[i])
		{
			for(int j=1;j<=n;j++)
			{
				if(i!=j)
				{
					cout<<i<<' '<<j<<endl;
					sum++;
					g[i][j]=g[j][i]=1;
				}
			}
			break;
		}
	}
	if(sum==m) return 0;
	for(int i=1;i<=n;i++)//没被标记的点内部相连 
	{
		for(int j=i+1;j<=n;j++)
		{
			if(i==j||g[i][j]||b[i]||b[j]) continue;
			cout<<i<<' '<<j<<endl;
			g[i][j]=g[j][i]=1;
			sum++;
			if(sum==m) return 0;
		}
	}
	for(int i=1;i<k;i++)//被标记的点内部相连 
	{
		for(int j=i+1;j<k;j++)
		{
			cout<<a[i]<<' '<<a[j]<<endl;
			g[a[i]][a[j]]=g[a[j]][a[i]]=1;
			sum++;
			if(sum==m) return 0;
		}
	}
	for(int i=1;i<=n;i++)//没被标记的点与被标记的点相连 
	{
		if(b[i]) continue;
		for(int j=1;j<=k;j++)
		{
			if(g[i][a[j]]) continue;
			cout<<i<<' '<<a[j]<<endl;
			sum++;
			if(sum==m) return 0;
			g[i][a[j]]=g[a[j]][i]=1;
		}
	}
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

首先对于任意两点 $u,v$，假如不存在一条最短路径使得路径上全是标记过的节点，那么 $d(u,v)$ 就没法算出来。

满足这样的最小包含标记点的模型是 $a-b-c$，其中 $b$ 不是标记点，$a$ 是标记点。

根据这个观察，我们可以得到一个构造方案。我们选出一个标记点作为 $a$，然后把所有非标记点都连到 $a$ 上，在保证联通且不连到 $a$ 的情况下我们可以随便连。由于 $k\ge 2$，所以一定存在这样的一条 $a-b-c$ （$c$ 为标记点）。

考虑无解的情况。有两种，第一种为 $k=n$，卡不掉。第二种边数很多导致最终不得不连到 $a$ 上去。

下面的代码常数垃圾的不行，如果想贺代码别贺这篇 /cy

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=309;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,k;
bool e[N][N],tag[N];
vector<int>a,b;

int main() {
	n=read(), m=read(), k=read();
	rep(i,1,k) {
		int x=read();
		tag[x]=1, a.push_back(x);
	}
	rep(i,1,n) if(!tag[i]) b.push_back(i);
	if(k==n||m>(n-1)*(n-2)/2-k+n) {
		puts("-1");
		return 0;
	}
	for(auto u:b) printf("%d %d\n",a[0],u), m--, e[a[0]][u]=e[u][a[0]]=1;
	for(auto u:a) if(u!=a[0]) printf("%d %d\n",b[0],u), m--, e[b[0]][u]=e[u][b[0]]=1;
	for(auto u:b) for(auto v:b) if(u!=v&&m&&!e[u][v]) printf("%d %d\n",u,v), m--, e[u][v]=e[v][u]=1;
	if(!m) return 0;
	for(auto u:a) for(auto v:b) if(m&&u!=a[0]&&!e[u][v]) printf("%d %d\n",u,v), m--, e[u][v]=e[v][u]=1;
	if(!m) return 0;
	for(auto u:a) for(auto v:a) if(m&&u!=v&&u!=a[0]&&v!=a[0]&&!e[u][v]) printf("%d %d\n",u,v), m--, e[u][v]=e[v][u]=1;
	return 0;
}
```

---

