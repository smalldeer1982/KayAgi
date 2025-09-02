# Capitalism

## 题目描述

整个社会可以用一张由 $n$ 个顶点和 $m$ 条边组成的无向联通图来表示。顶点代表人，一条边  $(i,j)$ 代表人 $i$ 和 $j$ 之间的友谊。

在社会上，第 $i$ 个人有收入 $a_i$。一个人 $i$ 羡慕一个人 $j$，等价于 $j$ 比 $i$ 多出1个单位的收入，也就是 $a_j=a_i+1$。

如果对于每一对朋友，都有一个人羡慕另一个人，这个社会就叫资本主义社会。对于一些朋友关系，你知道哪个人在羡慕另一个人。对于其余的朋友关系，你不知道谁羡慕谁。

社会收入不等值的定义是：$\max_{i=1}^na_i - \min_{i=1}^na_i$，也就是社会中收入最多的人的收入与收入最少的人的收入之差。

你只知道一些朋友关系，不知道每个人的收入。对于一部分朋友关系，你知道谁羡慕谁；对于另外一部分，你不知道。你要判断这个社会是否可能成为资本主义社会。如果是，你要构造一个 $a$ 满足所有条件，且这是个资本主义社会。要求你给出的 $a$ 让社会收入不等值最大。

## 样例 #1

### 输入

```
6 6
1 2 0
3 2 0
2 5 0
6 5 1
6 3 0
2 4 1```

### 输出

```
YES
3
3 2 1 3 1 0```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 0
3 4 1
4 1 1```

### 输出

```
NO```

## 样例 #3

### 输入

```
1 0```

### 输出

```
YES
0
0```

# 题解

## 作者：FutaRimeWoawaSete (赞：8)

个人认为不能算作差分约束题，只不过是一道最短路应用的题目罢了，如果参照第一篇题解的说法差分约束这么建边只能保证不等式 $|a-b| \leq 1$，这并不能作为 $|a-b| = 1$ 的充要条件。           

考虑将边加成双向边，如果已经确定了从属关系那么连边 $(a,b,1) , (b,a,-1)$，否则连边 $(a,b,1),(b,a,1)$。              

之后我们跑全源最短路，处理原图中是否有奇环后即可判断是否有解，因为一出现奇环你这些边怎么赋值都不会有解。       

具体而言，我们枚举源点 $s$ 后枚举所有连边，考虑到判断奇环只用判断路径长度的奇偶，设 $dist_{a,b}$ 表示 $a$ 到 $b$ 的最短路，对于任意边 $(u,v)$ 若出现 $dist_{s,u},dist_{s,v}$ 的奇偶性相同，加上 $(u,v)$ 之间的边就出现了奇环，这时候直接判无解就好了。

当然可能会出现 $s -> x$ 有多种路径的情况，不过由于我们只判断奇环是否出现，所以如果当前枚举的最短路并不是两个同奇偶的路径并且存在同奇偶的路径，说明存在其他的用最短路判断是奇环的奇环影响了这个环用最短路判断出来不是奇环，那么说明另外那个奇环就能找到了。（这里建议再画一下图）



当然这里的讨论要排除 $dist_{s,u}$ 和 $dist_{s,v}$ 互相更新的情况，因为权值是 $1$ 所以这里肯定不会影响判断奇环，自然也不再讨论范围之内。     

（这里当然建议大家直接二分图染色判奇环就行了，这个东西只是由于此题已经判了全源最短路所以一种更顺手的做法）

接着就是寻找一个合法的极差最大序列，那就是极小化最小值极大化最大值。枚举源点设其为 $0$，那么由于跑的最短路本身就是最小值所以最小值一定能被构造出来，而对于最大值，肯定不能超过源点出发中最大的最短路，比如说 $3 -> 5$ 有两条路径一条长为 $3$ 一条长为 $4$，对于第一条路径全取 $+1$ 顶破天了也就 $3$ 不可能达到 $4$。

这样做之后由于你本身是用最短路来限制的，所以最短路上的值每个点肯定都取得到，所以最后的答案就是枚举每个点作为源点可以得到的最大极差。   

时间复杂度 $O(n ^ 3)$。

---

## 作者：Little09 (赞：5)

首先发现这个 $|a_i-a_j|=1$ 的形式比较接近差分约束，稍微转化一下就是：$-1\le a_i-a_j\le 1$ 且 $a_i\neq a_j$。于是你会发现 $a_i\neq a_j$ 不是差分约束的条件。

换个角度。容易发现一条边相连的两个点一定奇偶性不同。考虑原图中若存在奇环，那么显然这是自相矛盾的。所以我们可以一开始就把存在奇环的情况判一下。

再回头看 $a_i\neq a_j$，你会发现在没有奇环的情况下，是不可能出现 $a_i=a_j$ 的。原因仍然是一条边相连的两个点一定奇偶性不同。所以我们可以大胆地把条件改写为 $-1\le a_i-a_j\le 1$。

接下来用 Floyd 跑全源最短路，就可以得到一组解了。那么我们应该如何解决极差最大呢？考虑我们枚举最终极差最大的解中的最小值，以这个点为源点算出它和每个点的最短路。假设从 $i$ 到 $j$ 的最短路是 $L$，它的实际含义是 $a_j\le a_i+L$。所以可以发现节点 $j$ 的最大值就是 $a_i+L$，所以用 $L$ 更新极差是正确的。

最后输出答案，就是找到极差最大的那个源点，输出它到其他点的最短路。容易发现输出的所有数都是非负的，所以也不用加上一个特定的数。

```cpp
// Author: Little09
// Problem: E. Capitalism
// Contest: Codeforces Global Round 12
// URL: https://codeforces.com/contest/1450/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

const int N=205,M=2005;
int n,m; 
int a[N],f[N][N],ans=-1,pos;
int fa[N*2];
int find(int x)
{
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x!=y) fa[x]=y;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	memset(f,20,sizeof(f));
	for (int i=1;i<=n;i++) f[i][i]=0;
	for (int i=1;i<=2*n;i++) fa[i]=i;
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		cin >> x >> y >> z;
		merge(x+n,y),merge(x,y+n);
		if (z==1) f[x][y]=1,f[y][x]=-1;
		else f[x][y]=1,f[y][x]=1;
	}
	for (int i=1;i<=n;i++)
	{
		if (find(i)==find(i+n))//存在奇环
		{
			cout << "NO";
			return 0;
		}
	}
	for (int k=1;k<=n;k++)//Floyd求全源最短路
	{
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (f[i][i]<0)//存在负环，差分约束无解
		{
			cout << "NO";
			return 0;
		}
		int mx=-n-1;
		for (int j=1;j<=n;j++) mx=max(mx,f[i][j]);
		if (mx>ans) ans=mx,pos=i;//找到最大值，更新极差
	}
	cout << "YES" << endl;
	cout << ans << endl;
	for (int i=1;i<=n;i++) cout << f[pos][i] << " ";
	return 0;
}

```


---

## 作者：csyakuoi (赞：3)

差分约束板子。

因为相邻差绝对值为$1$，所以有奇环一定无解。

$a_i+1=a_j$很好处理，关键在于$|a_i-a_j|=1$。

对于$|a_i-a_j|=1$，拆成两个条件：$a_i \leq a_j+1$和$a_i \geq a_j-1$。

枚举起点，特判有连边的点的最短路相等即可。

为什么呢？因为$d_i=d_j$意味着起点到$i$与$j$距离相等，$i$，起点，$j$形成长度为偶数的路径，又因为$i$，$j$有边，所以存在奇环。

~~这题评2700原因应该是外国人不知道差分约束。~~

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m,g[200][200];
int a[2000],b[2000],c;

int main(void)
{
	memset(g,0x3f,sizeof(g));
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&a[i],&b[i],&c);
		g[a[i]-1][b[i]-1]=1;
		if(c==1) g[b[i]-1][a[i]-1]=-1;
		else g[b[i]-1][a[i]-1]=1;
	}
	for(int i=0;i<n;i++)
		g[i][i]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++)
				g[j][k]=min(g[j][k],g[j][i]+g[i][k]);
	int pos=-1,ans=-1;
	for(int i=0;i<n;i++){
		if(g[i][i]<0){
			printf("NO\n");
			return 0;
		}
		int mx=-n,mn=n;
		for(int j=0;j<n;j++){
			mx=max(mx,g[i][j]);
			mn=min(mn,g[i][j]);
		}
		for(int j=0;j<m;j++)
			if(g[i][a[j]-1]==g[i][b[j]-1])
				mx=-n;
		if(ans<mx-mn){
			ans=mx-mn; pos=i;
		}
	}
	if(ans==-1) printf("NO\n");
	else{
		printf("YES\n%d\n",ans);
		for(int i=0;i<n;i++)
			printf("%d%c",g[pos][i]+n,i==n-1?'\n':' ');
	}
	return 0;
}
```

---

## 作者：ningago (赞：2)

不需要使用定理或结论的无脑做法。

显然如果图不是二分图则一定无解。

题目中的 $|a_u-a_v|=1$ 中会出现 $a_u=a_v$ 的情况，不好处理（~~实际上根据定理并不会出现~~）。

而此时可以利用二分图的性质，假设 $a_u$ 是偶数点，那么令 $a_u=2b_u,a_v=2b_v+1$，即可将 $|a_u-a_v|\leq 1$ 转化为 $b_v\leq b_u\leq b_v+1$，这样差值内的整数就只有 $0/1$ 了。

对特殊边也做相似的转化。由于需要让极差尽可能的大，而差分约束就是在满足最短路的约束下，尽可能让 $dis$ 大。所以枚举一个零势点，跑差分约束即可。

复杂度 $O(n^3)$。

```cpp
#define N 2010
int n, m;
int col[N];
int h[N], e[N << 1], ne[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, e[idx] = y; }
void add(int x, int y) { add_edge(x, y), add_edge(y, x); }
int x_[N], y_[N], z_[N];

void paint(int k, int c)
{
	col[k] = c;
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i];
		if(!~col[nx]) paint(nx, col[k] ^ 1);
		else if(col[nx] == col[k]) { printf("NO\n"); exit(0); }
	}
}
int dis[N][N];

void solve()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(h, idx = -1, sizeof(h));
	n = read(), m = read();
	for(int i = 1; i <= m; i++) x_[i] = read(), y_[i] = read(), z_[i] = read(), add(x_[i], y_[i]);
	for(int i = 1; i <= n; i++) col[i] = -1, dis[i][i] = 0;
	paint(1, 0);
	for(int i = 1; i <= m; i++)
	{
		int x = x_[i], y = y_[i], z = z_[i];
		if(col[x] > col[y]) z = -z, x ^= y ^= x ^= y;
		if(z > 0) { ckmin(dis[x][y], 0);  ckmin(dis[y][x], 0); }
		if(z < 0) { ckmin(dis[x][y], -1); ckmin(dis[y][x], 1); }
		if(!z)    { ckmin(dis[x][y], 0);  ckmin(dis[y][x], 1); }
	}
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		ckmin(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) if(dis[i][i] < 0) { printf("NO\n"); return; }
	int mxdt = -1;
static int ans[N], b[N];
	for(int S = 1; S <= n; S++)
	{
		for(int i = 1; i <= n; i++)
		{
			if(!col[i]) b[i] = dis[S][i] * 2;
			else b[i] = dis[S][i] * 2 + 1;
		}
		int mx = *std::max_element(b + 1, b + 1 + n);
		int mn = *std::min_element(b + 1, b + 1 + n);
		if(mx - mn > mxdt)
		{
			mxdt = mx - mn;
			for(int i = 1; i <= n; i++) ans[i] = b[i] - mn;
		}
	}
	printf("YES\n");
	print(mxdt, '\n');
	for(int i = 1; i <= n; i++) print(ans[i], ' ');
	putc('\n');
}
```

---

## 作者：Conan15 (赞：1)

给出的关系形如 $a_j - a_i = 1$ 或 $| a_j - a_i | = 1$。\
似乎看着很像差分约束？我们考虑把第一种改成 $a_j - a_i \leq 1, a_j - a_i \geq 1$ 就是差分约束了。\
但是第二种加了绝对值，这很难整，因为不可能既等于 $1$ 又等于 $-1$，只满足一个等于也很难刻画，所以只能**弱化**成 $| a_j - a_i | \leq 1$。\
可是弱化后会有 $a_j - a_i = 0$ 的情况，这又做不了了。

因此考虑原图的性质：对于有关系的点对 $(i, j)$，它们的值一定**恰好相差** $1$。\
因此相邻两个点**奇偶不同**，可以对原图进行二分图染色！\
染色之后这张图就是二分图了。它具有什么性质？显然它一定有解，所以弱化 $|a_j - a_i| \leq 1$ 是对的，因为相邻两个数本身就不能相等。

然后需要求极差，考虑到 $n \leq 200$ 可以 $O(n^2 m)$，所以我们枚举最小值，然后以最小值为起点建图跑 spfa。\
由于差分约束求出来的是**值最大**的一组解，所以 dist 最大的就是当前起点的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 205, M = 4015, INF = 0x3f3f3f3f;

int n, m;
int u[M], v[M], w[M];

struct Graph {
    int h[N], e[M], ne[M], idx = 0;
    int col[N];
    void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
    void addedge(int a, int b) { add(a, b), add(b, a); }
    void build() {
        for (int i = 1; i <= n; i++) h[i] = col[i] = -1; col[1] = 0;
        for (int i = 1; i <= m; i++) addedge(u[i], v[i]);
    }
    void dfs(int u) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (col[v] != -1 && col[v] == col[u]) puts("NO"), exit(0);
            if (col[v] == -1) col[v] = col[u] ^ 1, dfs(v);
        }
    }
} G;
struct Graph2 {
    int h[N], e[M], w[M], ne[M], idx = 0;
    void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }

    int d[N], cnt[N];
    bool st[N];
    queue<int> q;
    int spfa(int s) {
        for (int i = 1; i <= n; i++) d[i] = INF, st[i] = 1, cnt[i] = 0, q.push(i);
        d[s] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            st[u] = 0;
            for (int i = h[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (d[v] > d[u] + w[i]) {
                    d[v] = d[u] + w[i], cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= n + 2) return -INF;    //负环无解
                    if (!st[v]) st[v] = 1, q.push(v);
                }
            }
        }
        int Max = 0;
        for (int i = 1; i <= n; i++) {
            Max = max(Max, d[i]);
            if (d[i] < 0) return -INF;
        }
        return Max;
    }
} G2;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &u[i], &v[i], &w[i]);
    G.build(), G.dfs(1);
    for (int i = 1; i <= n; i++) G2.h[i] = -1;
    for (int i = 1; i <= m; i++) {
        if (w[i] == 1) G2.add(v[i], u[i], -1), G2.add(u[i], v[i], 1);
        else G2.add(u[i], v[i], 1), G2.add(v[i], u[i], 1);
    }
    int Max = -1, id = 0;
    for (int i = 1; i <= n; i++) {
        int res = G2.spfa(i);
        if (res > Max) Max = res, id = i;
    }
    if (Max == -1) return puts("NO"), 0;
    puts("YES");
    printf("%d\n", Max), G2.spfa(id);
    for (int i = 1; i <= n; i++) printf("%d ", G2.d[i]);
    return 0;
}
```

---

## 作者：Yorg (赞：1)

# 算法

## 差分约束
观察到 $a_i$ 最后是确定唯一的 + ~~我是从差分约束专题来的~~ ，考虑对于 $a_i$ 的约束条件进行差分约束。

### 转化约束条件
观察到，
$$
\left\{  
     \begin{array}{lr}  
     b = 0, \lvert {a_u - a_v} \rvert = 1, &  \\  
     b = 1, a_u + 1 = a_v &  
     \end{array}  
\right. 
$$
$$\Downarrow$$
$$
\left\{  
     \begin{array}{lr}  
     a_u, a_v \in \mathbb{Z}, & \\
     b = 0, a_u + 1 \geq a_v \text{ 且 } a_v + 1 \geq a_u \text{ 且 } a_u \neq a_v, &  \\  
     b = 1, a_u + 1 \geq a_v \text{ 且 } a_u + 1 \leq a_v &
     \end{array}  
\right. 
$$
都可以作为约束条件。
但是需要解决 $a_u = a_v$ 的情况。

观察到原图如果不是一个二分图(存在奇环)，那么不管对于环上每一边 $(u, v)$ 的权值取 $-1$ 还是 $1$ ，必不可能使 $\sum w = 0$ 。
所以原图一定是二分图。

### 处理方式
#### 根据二分图性质处理
在没有奇环的情况下，一条边相连的两个点的 $dis$ 一定奇偶性不同 （ $w \in \{ 1, -1 \}$ 每次跑一条边必定改变 $dis$ 奇偶性，只有存在奇环时，才能出现奇偶性不变的情况），是不可能出现 $a_i=a_j$ 的。
因此可以直接跑一遍即可。

#### 二分图 trick
令当前考虑的边为 $(u, v)$, 其中 $u$ 为偶数点，
令 $a_u = 2b_u, a_v = 2b_v + 1$ ，
即可将 $\lvert {a_u-a_v}\rvert \leq 1$ 转化为 $b_v\leq b_u\leq b_v+1$ ，这样差值内的整数就只有 $0/1$ 了。
这个思路来源于 [ningago 的题解](https://www.luogu.com.cn/article/2d749nvo) 。

### 跑差分约束
无论如何，最后枚举 $0$ 势点，跑差分约束即可。
不会的见 [差分约束模板](https://www.luogu.com.cn/problem/P5960) 。

## 最短路应用
具体见 [FutaRimeWoawaSete 的题解](https://www.luogu.com.cn/article/bpsizqm1) 。

# 代码
[代码剪贴板](https://www.luogu.com.cn/paste/ucqqt7bj)

# 总结
边权 $\in \{ 1, -1 \}$ 时，拥有一些特殊的性质。

对于绝对值不等式，考虑变形 trick 。

---

