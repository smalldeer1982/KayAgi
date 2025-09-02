# [ABC091C] 2D Plane 2N Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc091/tasks/arc092_a

二次元平面に，赤い点と青い点が $ N $ 個ずつあります。 $ i $ 個目の赤い点の座標は $ (a_i,\ b_i) $ で，$ i $ 個目の青い点の座標は $ (c_i,\ d_i) $ です。

赤い点と青い点は，赤い点の $ x $ 座標が青い点の $ x $ 座標より小さく， また赤い点の $ y $ 座標も青い点の $ y $ 座標より小さいとき，仲良しペアになれます。

あなたは最大で何個の仲良しペアを作ることができますか？ ただし，$ 1 $ つの点が複数のペアに所属することはできません。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ a_i,\ b_i,\ c_i,\ d_i\ <\ 2N $
- $ a_1,\ a_2,\ ...,\ a_N,\ c_1,\ c_2,\ ...,\ c_N $ はすべて異なる
- $ b_1,\ b_2,\ ...,\ b_N,\ d_1,\ d_2,\ ...,\ d_N $ はすべて異なる

### Sample Explanation 1

例えば， $ (2,\ 0) $ と $ (4,\ 2) $ をペアにし， $ (3,\ 1) $ と $ (5,\ 5) $ をペアにすればよいです。

### Sample Explanation 2

例えば， $ (0,\ 0) $ と $ (2,\ 3) $ をペアにし， $ (1,\ 1) $ と $ (3,\ 4) $ をペアにすればよいです。

### Sample Explanation 3

一つもペアが作れない場合もあります。

## 样例 #1

### 输入

```
3
2 0
3 1
1 3
4 2
0 4
5 5```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 0
1 1
5 2
2 3
3 4
4 5```

### 输出

```
2```

## 样例 #3

### 输入

```
2
2 2
3 3
0 0
1 1```

### 输出

```
0```

## 样例 #4

### 输入

```
5
0 0
7 3
2 2
4 8
1 6
8 5
6 9
5 4
9 1
3 7```

### 输出

```
5```

## 样例 #5

### 输入

```
5
0 0
1 1
5 5
6 6
7 7
2 2
3 3
4 4
8 8
9 9```

### 输出

```
4```

# 题解

## 作者：Guizy (赞：2)

看到 $n$ 只有 $100$，可以用 [匈牙利算法](https://www.luogu.com.cn/problem/P3386) 解决。

先把可以匹配的点连边，然后跑一遍匈牙利就行。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=501;
int n,x[Max],y[Max],vis[Max],flag[Max];
vector<int>G[Max];//STL存图

int fnd(int u){//匈牙利
	for(int v:G[u]){
		if(vis[v]) continue;
		vis[v]=1;
		if(!flag[v]||fnd(flag[v])){
			flag[v]=u;
			return 1;
		}
	}
	return 0;
}

int main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)//前n个是红的，后n个是蓝的
		scanf("%d%d",&x[i],&y[i]);
	
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=n*2;j++)
			if(x[i]<x[j]&&y[i]<y[j]) 
				G[i].push_back(j);//连边
    
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);//记得清空
		ans+=fnd(i);
	}
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：Symbolize (赞：2)

# 思路
假设第 $i$ 个红点与第 $j$ 个蓝点组合了，那么就不能再出现任何一个点与这两个点组合，如果一定要组合，我们就需要给另外一个换一个满足条件的点，否则无意义。这正是二分图最大匹配（匈牙利算法）。

这题基本等于模板，我们只需要把对于每一个红点，统计出能够与它匹配的点有哪些，然后跑一边二分图最大匹配就解决了。在我的代码中有更加详细的注释。
# AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e2+10;
using namespace std;
int n,m,Pair[N]/*目前与第i个红点组合的蓝点下标*/,ans/*记录答案*/;
bool vis[N];//记录目前这个人有没有找过 
pii red[N],blue[N];//pair类型来存每个红点与蓝点的下标 
vector<int> v[N];//记录可以与第i个红点组合的数分别是哪些 
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool find(int x)//模板的二分图最大匹配（匈牙利算法） 
{
	if(v[x].empty()) return 0;
    rep1(i,0,v[x].size()-1) 
	{
        int now=v[x][i];//可以与x匹配的第i个人人
        if(!vis[now])//没有与别人组合 
		{
            vis[now]=1;//这个点被找过了 
            if(!Pair[now]||find(Pair[now]))//如果被组合了，看能不能换一个 
			{
                Pair[now]=x;//满足条件就与它组合 
                return 1;//返回真 
            }
        }
    }
    return 0;//直到最后也没找到返回假 
}
signed main()
{
    n=read();//个数 
    rep1(i,1,n) red[i]=make_pair(read(),read());//红点 
    rep1(i,1,n) blue[i]=make_pair(read(),read());//蓝点 
    rep1(i,1,n) rep1(j,1,n) if(red[i].x<blue[j].x&&red[i].y<blue[j].y) v[i].push_back(j);//可以与i组合
	rep1(i,1,n)
	{
        memset(vis,0,sizeof vis);//每次记得清空 
        if(find(i)) ++ans;//匹配成功的数量，注意这里不需要担心会减少，因为只要找到了目标，只可能换，不可能被抢 
    }
    cout<<ans<<endl;//输出 
    return 0;//收场 
}
```

---

## 作者：loser_seele (赞：0)

$ x $ 最小的蓝点匹配符合条件的 $ y $ 最大的红点即可。证明：

设蓝红点分别为 $ b,r $。

如果 $ b $ 原来没有匹配，那么匹配上显然不会更劣。

如果 $ b $ 原来有匹配，设匹配点为 $ rb $，如果 $ r $ 原本没有匹配，那么解除匹配重连之后不会更劣。

否则设 $ r $ 原来有匹配 $ bb $，那么我们有 $ (b,rb),(r,bb) $，交换为 $ (b,r),(rb,bb) $ 之后也不会更劣，且是一个合法方案。通过比较 $ x,y $ 之间的大小关系可以证明交换总是合法，这里不再详述。

当然也可以用二分图最大匹配来解决。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
const int maxn=2e5+10;
struct node
{
int x,y;
int rk;
}a[maxn],b[maxn];
bool vis[maxn];
bool cmp(node a,node b)
{
return a.x<b.x;
}
bool cmpy(node a,node b)
{
return a.y>b.y;
}
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i].x>>a[i].y,a[i].rk=i;
    for(int i=1;i<=n;i++)
    cin>>b[i].x>>b[i].y,b[i].rk=i;
    sort(b+1,b+n+1,cmp);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
    vector<node>qwq;
    for(int j=1;j<=n;j++)
    if(!vis[a[j].rk]&&a[j].x<b[i].x&&a[j].y<b[i].y)
    qwq.push_back(a[j]);
    sort(qwq.begin(),qwq.end(),cmpy);
    if(!qwq.size())
    ;
    else
    vis[qwq[0].rk]=1,cnt++;
    }
    cout<<cnt;
}
```

---

## 作者：0xyz (赞：0)

来一发时间复杂度奇奇怪怪的题解。实现上细节应该是现有所有题解里最少的。

### 一、做法

阅读题目，发现有对于每个点只能使用一次的限制。所以马上想到最大流。具体来说，我们建立一个超级源点 $s$，然后让它向所有红点连一条流量为 $1$ 的边，代表每一个红点只能使用一次。建立一个超级汇点 $t$，让所有蓝色点向它一条流量为 $1$ 的边。中间就是所有红色点向所有有可能与它友好的蓝色点连一条流量为 $1$ 的边，因为每一对只能匹配一次。最后的答案就是 $s$ 到 $t$ 的最大流。这里令 $s=0,t=2n+1$，第 $i$ 个红点编号为 $i$，第 $i$ 个蓝点编号为 $n+i$。

时间复杂度：瓶颈是 `atcoder/maxflow` 里的 `flow` 函数。翻阅[官方文档](https://atcoder.github.io/ac-library/production/document_en/maxflow.html)，得知在所有边的流量上限都是 $1$ 时，时间复杂度是 $O(\min(n^{\frac{2}{3}}m,m^{\frac{3}{2}}))$，其中 $m$ 是边的条数。在本题中，边的条数 $m$ 是 $O(n^2)$ 的。所以总的时间复杂度是 $O(n^{\frac{8}{3}})$。

当然此题其他解法还有 $O(n^2)$ 的贪心以及 $O(n^3)$ 的匈牙利。

### 二、代码

```cpp
#include<bits/stdc++.h>
#include<atcoder/maxflow>
#define R(i) for(int i=1;i<=n;i++)
#define A g.add_edge
using namespace std;
using namespace atcoder;
int a[110],b[110],c[110],d[110],n;
int main(){
	cin>>n;mf_graph<int>g(2*n+2);
	R(i)cin>>a[i]>>b[i];
	R(i)cin>>c[i]>>d[i];
	R(i)A(0,i,1),A(n+i,2*n+1,1);
	R(i)R(j)if(a[i]<c[j]&&b[i]<d[j])A(i,n+j,1);
	cout<<g.flow(0,2*n+1)<<'\n';
	return 0;
}
```

---

## 作者：syxmz (赞：0)

# Atcoder Beginner Contest 091C - 2D Plane 2N Points 解题报告

### 1 题目链接

[传送门](https://atcoder.jp/contests/abc091/tasks/arc092_a?lang=en)

### 2 题目大意

##### 题目：二维平面的2N个点

##### 题目大意：

给定一个二维平面，上面分布着 $n$ 个红点和 $n$ 个蓝点，其中第 $i$ 个红点的坐标为 ($a_i$,$b_i$)，第 $i$ 个蓝点的坐标为 ($c_i$,$d_i$)。

当一个红点的 $x$ 坐标严格小于一个蓝点的 $x$ 坐标，并且 $y$ 坐标严格小于这个蓝点的 $y$ 坐标时，这两个点可以成为一个 “好” 的点对。

一个点只能属于一个 “好”的点对。

求问最多有多少个“好”的点对。

### 3 解法分析

这道题最开始显然是一眼盯真的。

首先考虑**贪心**。

用符合条件最小的蓝点去匹配符合条件最大的红点。

但是代码显然并不是那么好想。

那更朴素的 $dfs$ 能过吗？显然不能。

再看一遍题目。这是两个大小为 $n$ 的集合匹配问题。十分自然的想到**二分图最大匹配**。

这个是十分裸的板子，写一遍直接过。

确定 $AC$ 后再想想贪心。

~~其实匈牙利的本质就是贪心。~~

首先对蓝点从小到大排序，不妨设 $x$ 坐标为第一关键字。

显然，红点需从大到小排序，才能满足符合条件最大的红点。

注：使用过该点后记得赋值。

### 4 解法总结

1. 二分图最大匹配。
2. 贪心。

### 5 AC Code

##### 5.1 二分图最大匹配

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define N 107

int n;
int link[N];
bool vis[N];
bool mp[N][N];

struct node {
    int x, y;
}p[N], q[N];

bool dfs(int u, int t) {
    rep(i, 1, t)
        if (mp[u][i] && !vis[i]) {
            vis[i] = 1;
            if (link[i] == -1 || dfs(link[i], t)) {
                link[i] = u;
                return 1;
            }
        }
    return 0;
}

int solve(int n) {
    int res = 0;
    rep(i, 1, n) {
        memset(vis, 0, sizeof vis);
        if (dfs(i, n))
			++res;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    memset(link, -1, sizeof link);
    rep(i, 1, n)
        scanf("%d%d", &p[i].x, &p[i].y);
    rep(i, 1, n)
        scanf("%d%d", &q[i].x, &q[i].y);
    rep(i, 1, n)
        rep(j, 1, n)
            if (p[i].x < q[j].x && p[i].y < q[j].y)
                mp[i][j] = 1;
    int ans = solve(n);
    printf("%d\n", ans);
    return 0;
}
```

##### 5.2 贪心（相对好理解）

```cpp
#include <bits/stdc++.h>
#define N 207
using namespace std;

struct node {
    int a, b;
}p[N], q[N];

int n;
int vis[N];

bool cmp(node x, node y) {
    if (x.a != y.a)
        return x.a < y.a;
    else
        return x.b < y.b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i].a, &p[i].b);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &q[i].a, &q[i].b);
    sort(p + 1, p + n + 1,cmp);
    sort(q + 1, q + n + 1,cmp);
    int cnt = 0;
    for (int j = 1; j <= n; ++j) {
        int mid = -1, flag = 0;
        for (int i = 1; i <= n; ++i)
            if (!vis[i] && p[i].a < q[j].a && p[i].b < q[j].b) {
                if (++flag == 1)
                    mid = i;
                else if (p[i].b > p[mid].b)
                    mid = i;
            }//保证存在
        if (mid > 0) {
            vis[mid] = 1;
            ++cnt;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
```

##### 5.3 贪心（题解分析）

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int ans;

int main() {
	scanf("%d", &n);
	vector <pair <int, int> > r(n), b(n);
	for (pair <int, int> & p : r)
		scanf("%d%d", &p.first, &p.second);
	for (pair <int, int> & p : b)
		scanf("%d%d", &p.second, &p.first);
	sort(r.begin(), r.end(), greater <pair <int, int> > ());
	sort(b.begin(), b.end());
	for (pair <int, int> & ri : r)
		for (pair <int, int> & bi : b)
			if (ri.first < bi.second && ri.second < bi.first) {
				++ans;
				bi.first = bi.second = -1;
				break;
			}
	printf("%d\n", ans);
	return 0;
}
```



### 6 二分图最大匹配

有意向者尝试 $AC$ [洛谷 P3386 【模板】二分图最大匹配](https://www.luogu.com.cn/problem/P3386)。

##### 6.1 增广路

增广路的本质其实就是**一条路径的起点和终点都未配对的点的边**。

##### 6.2 匈牙利算法

###### 6.2.1 背景

匈牙利算法(Hungarian method)是由匈牙利数学家Edmonds于1965年提出，因此叫**匈牙利算法**。匈牙利算法是二分图匹配最常见的算法，该算法的核心就是**寻找增广路径**，它是一种用增广路径求二分图最大匹配的算法。

###### 6.2.2 复杂度

时间复杂度：

- 邻接矩阵最坏为 $O(n^3)$

- 邻接表：$O(mn)$

空间复杂度：

- 邻接矩阵：$O(n^2)$
- 邻接表：$O(m+n)$

##### 6.3 二分图

**二分图**是图论中的一种特殊模型。 设 $G=(V,E)$ 是一个无向图，如果顶点 $V$ 可分割为两个互不相交的子集 ($A$,$B$)，并且图中的每条边（$i$，$j$）所关联的两个顶点 $i$ 和 $j$ 分别属于这两个不同的顶点集，则称图 $G$ 为一个二分图。

~~是不是看不懂。~~

简而言之，就是顶点集V可分割为两个互不相交的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。满足这样的图就叫二分图。

##### 6.4 匈牙利算法

根据上文的描述，既然增广路的作用是“改进匹配方案”（即增加配对数），那么如果我们已经找到了一种匹配方案，不难发现如果在当前匹配方案下再也找不到任何增广路的话，那么当前匹配就是二分图的最大匹配，算法如下。

1. 首先从任意的一个未配对的点 $u$ 开始，从点 $u$ 的边中任意选一条边（假设这条边是从$u\longrightarrow v$）开始配对。如果点 $v$ 未配对，则配对成功，这是便找到了一条增广路。如果点 $v$ 已经被配对，就去尝试“连锁反应”，如果这时尝试成功，就更新原来的配对关系。
   所以这里要用一个`link[v]=u`。配对成功就将配对数加1,。

2. 如果刚才所选的边配对失败，那就要从点 $u$ 的边中重新选一条边重新去试。直到点 $u$ 配对成功，或尝试过点 $u$ 的所有边为止。

3. 接下来就继续对剩下的未配对过的点一一进行配对，直到所有的点都已经尝试完毕，找不到新的增广路为止。

4. 输出配对数。

##### 6.5 板子

```cpp
#include <bits/stdc++.h>
#define N 2007

int vis[N];
int n, m, e;
int link[N];
int mp[N][N];

bool dfs(int x, int t) {
    for (int i = 1; i <= t; ++i)
		if (mp[x][i] && !vis[i]) {
			vis[i] = 1;
			if (!link[i] || dfs(link[i], t)) { 
				link[i] = x ; 
				return true;
			}
		}
    return 0;
}

int solve() {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof vis);
		if (dfs(i, m)) 
			++res;
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1, x, y; i <= e; ++i) {
		scanf("%d%d",&x,&y);
		mp[x][y] = 1;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：ttq012 (赞：0)

枚举所有的红点和所有的蓝点，如果红点的 $x$ 坐标严格小于蓝点的 $x$ 坐标并且红点的 $y$ 坐标严格小于蓝点的 $y$ 坐标，那么就在这两个点之间加一条边。

然后二分图匹配即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 210;
vector <int> z[N];
bool used[N];
int match[N], Zf2RiCQzm8[N], a325aZfg6PO[N], ZAGZf4569I[N], KZMOI45z503[N];

bool dfs(int u)
{
  for (auto &v : z[u])
    if (!used[v])
    {
      used[v] = true;
      if (!match[v] || dfs(match[v]))
      {
        match[v] = u;
        return true;
      }
    }
  return false;
}

int main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i ++) cin >> Zf2RiCQzm8[i] >> a325aZfg6PO[i];
  for (int i = 1; i <= n; i ++) cin >> ZAGZf4569I[i] >> KZMOI45z503[i];
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      if (Zf2RiCQzm8[i] < ZAGZf4569I[j] && a325aZfg6PO[i] < KZMOI45z503[j])
        z[i].push_back(j + n);
  int ans = 0;
  for (int i = 1; i <= n; i ++, memset(used, false, sizeof used))
    if (dfs(i))
      ans ++;
  cout << ans << '\n';
  return 0;
}

```



---

## 作者：火车司机 (赞：0)

## 简要分析

观察题意，可以发现以下几条信息

- 点的颜色分为红色和蓝色 $2$ 种

- 红点只能和蓝点匹配，蓝点同理

- 一个红点最多和一个蓝点匹配，蓝点同理

- 求问最大匹配数量

于是可以很简单的将其转化为二分图最大匹配

根据题意，$n^2$ 枚举红点和蓝点，如果红点的 $x$，$y$ 坐标均分别小于蓝点就在它们之间连一条边

然后就可以直接跑二分图最大匹配板子了，因为板子不是这篇题解的重点所以不再赘述，不会的同学可以去[模板题P3386](https://www.luogu.com.cn/problem/P3386)

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 105
using namespace std;
int n, ans, v[N], mar[N], mp[N][N];
struct point
{
	int x, y;
} a[N], b[N];
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
inline int dfs(int x)
{
	for (ri i = 1; i <= n; i++)
		if (mp[x][i] && !v[i])
		{
			v[i] = 1;
			if (!mar[i] || dfs(mar[i]))
			{
				mar[i] = x;
				return 1;
			}
		}
	return 0;
}
signed main()
{
	read(n);
	for (ri i = 1; i <= n; ++i)
		read(a[i].x), read(a[i].y);
	for (ri i = 1; i <= n; ++i)
		read(b[i].x), read(b[i].y);
	for (ri i = 1; i <= n; ++i)
		for (ri j = 1; j <= n; ++j)
			if (a[i].x < b[j].x && a[i].y < b[j].y)
				mp[i][j] = 1;
	for (ri i = 1; i <= n; ++i)
		memset(v, 0, sizeof(v)), ans += dfs(i);
	print(ans);
	return 0;
}
```


---

