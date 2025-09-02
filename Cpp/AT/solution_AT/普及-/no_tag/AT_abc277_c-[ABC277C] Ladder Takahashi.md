# [ABC277C] Ladder Takahashi

## 题目描述

【题面翻译】

有一座很高的楼，你现在在第一层。

有 $n$ 个传送门，每个传送门连接第 $a_i$ 层与 $b_i$ 层。传送门是双向的。

请你求出你能到达的最高楼层。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n \le 2 \times 10^5$

$1 \le a_i, b_i \le 10^9$

保证 $a_i \ne b_i$。

## 样例 #1

### 输入

```
4
1 4
4 3
4 10
8 3```

### 输出

```
10```

## 样例 #2

### 输入

```
6
1 3
1 5
1 12
3 5
3 12
5 12```

### 输出

```
12```

## 样例 #3

### 输入

```
3
500000000 600000000
600000000 700000000
700000000 800000000```

### 输出

```
1```

# 题解

## 作者：ShanCreeperPro (赞：4)

##  AT_abc277_c [ABC277C] Ladder Takahashi 題解

### 题面

给定一张图，求从 $1$ 开始遍历到的最大值。

### 解析

我们可以把样例 $1$ 画成一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6m1bf5dd.png)

看到了吗？问题一下子就转变成了从结点 $1$ 开始能够到达的最大的顶点。

考虑使用深度优先搜索，即 dfs。

- 先存图，使用 `std::vector` 邻接表：

```cpp
for(int i = 1; i <= n; i++){
	std::cin >> u >> v;
    vec[u].push_back(v);
    vec[v].push_back(u);
    // 因为电梯是双向的，所以是个无向图
}
```

- 定义函数 `dfs`，从 `vec[1]` 中开始遍历，用 `vis` 数组确定一个点是否被访问过，如果走到最后，更新答案：

```cpp
inline int dfs(int x){
	if(vec[1].empty) return -1;
    else{
    	for(int i = 1; i <= n; i++)
        	// 遍历操作
            // 记得标记哦
    }
    return ans;
}
```



---

## 作者：Strelitzia_ (赞：3)

## 题目大意

有一栋楼和 $n$ 个梯子，第 $i$ 个梯子连接第 $a_i$ 层楼和第 $b_i$ 层楼。可以通过梯子 $i$ 从 $a_i$ 到 $b_i$ 或者从 $b_i$ 到 $a_i$，问在只爬梯子的情况下从第一层楼开始最多到第几层楼。

## 思路

我们把每一个梯子看成边，把每一层楼看成点，于是问题就变成了：给出 $n$ 条双向边，问节点 $1$ 能到达的编号最大的点是什么。

那就很好做了：建完图，从节点 $1$ 开始广搜，最后扫一遍能到达的节点，找到编号最大的点输出。

编号范围达到了 $10^9$ 怎么办？我们用 `map`映射一下就可以了。

然后就做完了。代码如下：

```cpp
map<int, int> id, val;
int idd;
struct T {
	int to, nxt;
} e[N];
int head[N], hop, n, m, ans;
bool vis[N];
void addd(int to, int nxt) {
	e[++hop].to = nxt;
	e[hop].nxt = head[to];
	head[to] = hop;
}
queue<int> q;
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		int to = read(), nxt = read();
		if (!id.count(to)) id[to] = ++idd, val[idd] = to;
		if (!id.count(nxt)) id[nxt] = ++idd, val[idd] = nxt;
		addd(id[to], id[nxt]);
		addd(id[nxt], id[to]);
	}
	if (!id.count(1)) return puts("1"), Strelitzia_H;
	q.push(id[1]);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nxt)
			if (!vis[e[i].to]) q.push(e[i].to);
	}
	for (int i = 1; i <= idd; i++) {
		if (vis[i]) ans = max(ans, val[i]);
	}
	printf("%lld", ans);
	return Strelitzia_H;
}
```

---

## 作者：JiaY19 (赞：1)

### 思路

考虑图中给你所需要求得东西。

给你一些边，求可以到达的点的最大编号。

发现是无向边。

即所有与 $1$ 所相连的点全部都可以到达。

那么就可以直接利用并查集维护联通性就可以了。

具体来说，每次用并查集合并时，都将小编号合并到大编号上。

但发现这题值域太大了，离散化一下就可以了。

记得把 $1$ 加入离散化数组。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 1000010;
 
int n, m, a[N], b[N], c[N], fa[N];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
inline int gf(int x)
{
    return (fa[x] == x ? x : fa[x] = gf(fa[x]));
}
 
inline void merge(int x , int y)
{
    x = gf(x), y = gf(y);
    if(x == y) return;
    if(x > y) swap(x, y);
    fa[x] = y;
}
 
int main()
{
    n = read() , c[++m] = 1;
    for (int i = 1; i <= n;i++)
    {
        a[i] = read(), b[i] = read();
        c[++m] = a[i], c[++m] = b[i];
    }
    sort(c + 1, c + m + 1);
    m = unique(c + 1, c + m + 1) - c - 1;
    for (int i = 1; i <= n;i++)
        a[i] = lower_bound(c + 1, c + m + 1, a[i]) - c,
        b[i] = lower_bound(c + 1, c + m + 1, b[i]) - c;
    iota(fa + 1, fa + m + 1, 1);
    for (int i = 1; i <= n; i++)
        merge(a[i], b[i]);
    cout << c[gf(1)] << endl;
    return 0;
}
```

---

## 作者：冷却心 (赞：1)

## 题意

一个建筑有 $10^9$ 层楼，高桥有 $n$ 个梯子，他最初在 $1$ 楼。

第 $i$ 个梯子连接 第 $u_i$ 层楼和第 $v_i$ 层楼，**注意是双向的**。

请问高桥最高能到几层楼。

## 解法

其实就是一个 BFS，但是楼层有 $10^9$，存不下，再看 $n$，每个梯子连接 $2$ 个点，最多有 $2n$ 个点，可以离散化后再来 BFS。

注意离散化时要提前存入一个 $1$，因为有可能没有梯子连接一楼，高桥无法移动

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 2e5 + 10;
LL n, ans = 1, input[N][5], len = 0;
struct Tmp{
	LL x, k;
	bool operator < (const Tmp& b){
		return x < b.x;
	}
}tmp[N * 4];
vector<LL> g[N * 10];
set<LL> vis;
map<LL, LL> mp1, mp2;
int main(){
	Fcin;
	cin >> n;
	LL v, w;
	
	// 离散化
	mp1[1] = 1;
	mp2[1] = 1;
	for (LL i = 1; i <= n; i ++){
		cin >> input[i][1] >> input[i][2];
		tmp[++ len].x = input[i][1];
		tmp[len].k = input[i][1];
		tmp[++ len].x = input[i][2];
		tmp[len].k = input[i][2];
	}
	
	sort(tmp + 1, tmp + 1 + len);
	for (LL i = 1; i <= len; i ++){
		if (!mp1.count(tmp[i].k)){
			mp1[tmp[i].k] = i + 1;
			mp2[i + 1] = tmp[i].k;
		}
	}
	
	//存梯子
	for (LL i = 1; i <= n; i ++){
		v = mp1[input[i][1]], w = mp1[input[i][2]];
		g[v].emplace_back(w);
		g[w].emplace_back(v);
	}
	
	// BFS
	queue<LL> q;
	q.push(1);
	vis.insert(1);
	while (!q.empty()){
		LL now = q.front(); q.pop();
		ans = max(ans, now);
		for (LL to : g[now]){
			if (!vis.count(to)){
				vis.insert(to);
				q.push(to);
			}
		}
	}
	cout << mp2[ans];
		
	return 0;
}
```


---

## 作者：_dijkstra_ (赞：1)

感觉我做复杂了。

## 思路

$a_i$ 与 $b_i$ 很大，所以离散化。

离散化后连接一条双向边。

然后从 $1$ 开始 dfs。dfs 时记录最大点值即可。

## 代码

省去了大段的缺省源。

```cpp
const int N = 2e5 + 5;
struct Edge {int now, nxt, real_now;} e[N << 1];
int head[N], cur;
void add(int u, int v, int real_now) //链式前向星，同时记录一下"真正的点"。
{
	e[++cur].now = v;
	e[cur].nxt = head[u];
	e[cur].real_now = real_now;
	head[u] = cur;
}
int u[N], v[N];
bool vis[N << 1];
int tt[N << 1], tot;
int ans = 1;
void dfs(int u) //大力 dfs 即可
{
	vis[u] = true;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (vis[v]) continue;
		ans = max(ans, e[i].real_now);
		dfs(v);
	}
}
void solve()
{
	int n;
	scanf("%d", &n);
	tt[++tot] = 1;
	for (int i = 1; i <= n; i++) scanf("%d%d", &u[i], &v[i]), tt[++tot] = u[i], tt[++tot] = v[i];
	sort(tt + 1, tt + tot + 1);
	int m = unique(tt + 1, tt + tot + 1) - tt; //离散化
	for (int i = 1; i <= n; i++)
	{
		int tu = lower_bound(tt + 1, tt + m + 1, u[i]) - tt;
		int tv = lower_bound(tt + 1, tt + m + 1, v[i]) - tt;
		add(tu, tv, v[i]), add(tv, tu, u[i]);
	}
	dfs(1);
	cout << ans << '\n';
}
```

---

## 作者：RainSpark (赞：1)

# 题意

有一栋 $10^9$ 层的大楼，有 $N$ 个梯子。

在大楼第 $1$ 层的高桥反复使用梯子（$0$ 次也可以），想尽量爬到更高的楼层。

梯子编号为 $1 \sim N$，第 $i$ 个梯子连接 $a_i$ 层和 $b_i$ 层。利用梯子 $i$，可以从 $a_i$ 层爬到 $b_i$ 层，也可以从 $b_i$ 层爬到第 $a_i$ 层。

虽然可以双向移动到不同的楼层，但是不能在其他楼层之间移动。

另外，高桥虽然可以在同一层自由移动，但是不能用梯子以外的方法移动到其他楼层。

请你求出高桥能到达的最高楼层。

数据范围 $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $，$ 1\ \leq\ a_i,\ b_i\ \leq\ 10^9 $。

# 思路

由于这道题楼层极多，使用并查集等一些算法在初始化的时候就可能超时，但是梯子组数不多，所以可以直接用链式前向星建图跑 dfs。

把每个楼层看作一个结点，其编号为楼层数。把连接第 $a_i$ 层和第 $b_i$ 层的梯子看作从 $a_i$ 连到 $b_i$ 的双向边，从 $1$ 号结点开始进行 dfs，同时记录到达结点的编号最大值，就是最终结果。

由于数据范围极大，开 $10^9$ 的一维数组空间会爆炸，所以用 map 映射 `head` 和 `vis` 数组即可。

时间复杂度 $O(N \log{N})$，可以通过本题。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<map>
const int N=400005,M=1005;
using namespace std;
struct E{
    int nxt,to;
}edge[N];
map<int,int> head;
int num_edge;
void add(int from,int to){
    num_edge++;
    edge[num_edge].nxt=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
}//链式前向星 
int n,ans=1;
map<int,bool> vis;
void dfs(int x){
	ans=max(ans,x);//记录答案 
	for(int i=head[x];i;i=edge[i].nxt){
		int j=edge[i].to;
		if(!vis[j]){ vis[j]=1; dfs(j);}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++){
		scanf("%d %d",&a,&b);
		add(a,b);add(b,a);
	}
	dfs(1);
	printf("%d\n",ans);
    return 0;
}
```

---

## 作者：comcopy (赞：0)


题意题面给的很正确的，我就不说非人的话了。

可以发现如果我们把两个点 $(x,y)$ 连起来的话，那么与 x 相连的所有楼层都能到达 y ,而与 y 相连的所有楼层都能达到 x 层。

故想到并查集。

所以我们就把题目变为了：找到 1 所在连通块中最大的值。

我们可以用 map 进行离散化，然后合并的时候直接让值小的父亲为值大的，保证父亲永远是大于等于他的所有儿子的，因此我们查找的时候只用查 1 所在连通块的父亲就行了。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=4e5+10;
int fa[N<<1];
int a[N];
map<int,int>mp;
int cnt=0;
int n;

inline int fnd(int u){
	return u==fa[u]?u:fa[u]=fnd(fa[u]);
}


signed main(){
	cin>>n;
	for(int i=1;i<=(n<<1);++i)fa[i]=i;
	mp[1]=++cnt;
	a[cnt]=1;
	for(int i=1;i<=n;++i){
		int x,y;
		cin>>x>>y;
		if(!mp[x])mp[x]=++cnt,a[cnt]=x;
		if(!mp[y])mp[y]=++cnt,a[cnt]=y;
		int fx=fnd(mp[x]),fy=fnd(mp[y]);
		if(a[fx]>a[fy]) fa[fy]=fx;
		else fa[fx]=fy;
	}
	cout<<a[fnd(1)]<<endl;
	return(0-0);
}
```




---

