# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8```

### 输出

```
2 3 3
1 2 2```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156```

# 题解

## 作者：Leasier (赞：12)

考虑先复原树的形态。这里我们先钦定以 $1$ 为根。

我们抓出所有 $f(i, 1)$，将其从大到小排序，不难发现：

- $\forall v \in sub_u, f(v, 1) < f(u, 1)$。

证明：首先 $f(1, 1)$ 就是所有点的带权深度之和，它显然最大。

每次在 $f(fa_u, 1)$ 的基础上添加一个 $u$，不难发现每个 $x$ 的贡献不增，且存在一个会变小。

有了上述结论，我们依次考虑确定排序后每个点的父亲。类似地，注意到满足 $f(v, 1) > f(u, 1)$ 且 $f(u, v)$ 最大的 $v$ 就是 $fa_u$。

于是我们还原了树的形态，现在考虑还原边权。

类似于换根 dp，我们希望通过 $f(u, u)$ 与 $f(u, fa_u)$ 的关系找出 $(u, fa_u)$ 的边权。

这两者的区别是什么呢？注意到对于 $u$ 子树外的点，前者的最小距离比后者多了一个 $(u, fa_u)$ 的边权。

于是边权即为 $\frac{f(u, u) - f(u, fa_u)}{n - size_u}$。

时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int fa[2007], head[2007], size[2007];
ll f[2007][2007];
Edge edge[2007];
pair<ll, int> pr[2007];

inline int read_int(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline ll read_ll(){
	ll ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u){
	size[u] = 1;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		dfs(x);
		size[u] += size[x];
	}
}

int main(){
	int n = read_int();
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= i; j++){
			f[i][j] = f[j][i] = read_ll();
		}
	}
	for (int i = 1; i <= n; i++){
		pr[i] = make_pair(f[i][1], i);
	}
	sort(pr + 1, pr + n + 1, greater<pair<ll, int> >());
	for (int i = 2; i <= n; i++){
		int pos = -1;
		for (int j = 1; j < i; j++){
			if (pos == -1 || f[pr[i].second][pos] < f[pr[i].second][pr[j].second]) pos = pr[j].second;
		}
		fa[pr[i].second] = pos;
		add_edge(pos, pr[i].second);
	}
	dfs(1);
	for (int i = 2; i <= n; i++){
		cout << i << " " << fa[i] << " " << (f[i][i] - f[i][fa[i]]) / (n - size[i]) << endl;
	}
	return 0;
}
```

---

## 作者：spdarkle (赞：7)

第一反应是考虑 $f$ 数组的利用。

显然 $f_{i,i}$ 是特殊的数据，它表示整棵树所有点到点 $i$ 的距离之和。

那么考虑 $f_{i,i}+f_{j,j}-2f_{i,j}$ 就等价于 $(i,j)$ 的路径被重复计算了 $n$ 次，可以得到 $dis_{i,j}=\frac{f_{i,i}+f_{j,j}-2f_{i,j}}{n}$。

如何根据 $dis$ 求出原树呢？注意到此树所有边权为正，则对于每一个 $x$，最小的 $dis_{x,y}$ 的 $y$ 必然在原树上有边 $(x,y)$。

更进一步地，我们断言完全图 $(u,v,dis_{u,v})$ 的最小生成树即为所求。这是必然成立的（可以假设它不成立，那么可以推导出边权为负，进而假设不成立）。


---

## 作者：周子衡 (赞：5)

注意到：对树上的两条路径 $(x,y)$ 和 $(X,Y)$，如果 $(x,y)$ 被严格包含于 $(X,Y)$，那么 $f(x,y)$ 一定大于 $f(X,Y)$。这说明

**性质** 对每个点 $x$，设 $y$ 是树上除了 $x$ 以外的节点中使得 $f(x,y)$ 最大的那个节点，那么原树上一定存在边 $(x,y)$。

我们考虑这样一个流程：先对每个点 $x$ 都找出它的最大出边 $(x,y)$，这些边是已经确定存在的了。接下来我们把已经确定的边所形成的连通块缩起来，再反复使用上面的算法，直到最后只有一个连通块为止。这样由于每次连通块数都至少减半，因而一定在 $O(\log n)$ 轮内停止，因而时间复杂度 $O(n^2\log n)$。这样我们就确定了树的形态。

（当然可以注意到上面的算法就是求解最大生成树的 Boruvka 算法，因而实际上我们要找的树就是原图的最大生成树。用别的最大生成树算法，如 Prim / Kruskal 算法也可以求解。）

最后我们需要确定每条边的边权。对一条边 $(x,y)$，设将它断开后和 $x$ 相连的部分总结点数为 $s_x$，和 $y$ 相连的部分总节点数为 $s_y$。那么这条边的边权 $w_{x,y}=\dfrac{f(x,x)-f(x,y)}{s_y}=\dfrac{f(y,y)-f(x,y)}{s_x}$，可以轻松求得。

---

## 作者：Egg_eating_master (赞：4)

提供一个新做法。

考虑利用 $f$ 求出树上任意两点的距离。

设 $d_{a,b,c}$ 表示 $c$ 到环 $(a,b)$ 的距离，$dis_{a,b}$ 表示树上 $a$ 到 $b$ 的距离。

对于两个点 $x,y$，剩下的 $n-2$ 个点只有三种情况：

1. 在 $x$ 或 $y$ 的子树内（即下图中的 A 和 B 部分）；
2. 在 $x$ 到 $y$ 的路径上（即下图中的 C 部分）；
3. 在 $x$ 到 $y$ 的路径上的某个点的子树内（即图中的 D 部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpwfgflr.png)

手模一下这三种情况容易发现，对于任意的点 $k$，均有 
$$d_{x,x,k}+d_{y,y,k}-2\times d_{x,y,k}=dis_{x,y}$$

对所有的 $k$ 把式子相加，得到

$$f_{x,x}+f_{y,y}-2\times f_{x,y}=n\times dis_{x,y}$$

于是就可以用 $O(n^2)$ 的时间求出所有的 $dis$。

我们不妨钦定 $1$ 为根，那么 $dis_{1,x}$ 最小的一个 $x$ 一定和 $1$ 直接连边。对于另一个点 $y$，如果 $dis_{1,y}<dis_{x,y}$，那么就把它划分到 $1$ 的子树内；否则就划分到 $x$ 的子树内。最后对于 $1$ 和 $x$ 的子树分别继续递归求解。

这样的话每次都花 $O(n)$ 的时间确定一条边，总的时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2005;
int n;
int f[maxn][maxn];
int dis[maxn][maxn];
vector<int> a[maxn];
vector<int> tmp;
void work(int x) {
    if (a[x].size() == 0) return;
    int y = 0;
    for (int i = 0; i < a[x].size(); i++)
        if (y == 0 || dis[x][y] > dis[x][a[x][i]]) y = a[x][i];
    cout << x << ' ' << y << ' ' << dis[x][y] << '\n';
    tmp = a[x]; a[x].clear();
    for (int i = 0; i < tmp.size(); i++) {
        int k = tmp[i];
        if (k == y) continue;
        if (dis[x][k] > dis[y][k]) a[y].push_back(k);
        else a[x].push_back(k);
    }
    work(x); work(y);
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> f[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            dis[i][j] = dis[j][i] = (f[i][i] + f[j][j] - 2 * f[i][j]) / n;
    for (int i = 2; i <= n; i++) a[1].push_back(i);
    work(1);
    return 0;
}
```


---

## 作者：Alex_Wei (赞：2)

标算的确厉害：注意到若 $i, j$ 不直接相连，则存在 $k$ 使得 $f(i, k)$ 和 $f(j, k)$ 均大于 $f(i, j)$，这和最大生成树的性质如出一辙。因此，我们断言原树结构即 $(i, j, f(i, j))$ 的最大生成树。

得到 $(i, j)$ 边权 $w$ 很容易。考虑到 $f(i, i) - f(i, j)$ 相当于 $w$ 乘以 $j$ 在以 $i$ 为根时的子树大小，所以 $w = \frac {f(i, i) + f(j, j) - 2f(i, j)} {n}$。

接下来讲讲我的做法。

考虑检查 $i, j$ 是否直接相连。考虑到若 $i, j$ 直接相连，则对于所有 $k$，$f(k, i) - f(k, j)$ 要么等于 $f(i, i) - f(i, j)$，此时 $k$ 在 $i$ 子树内，要么等于 $f(j, i) - f(j, j)$，此时 $k$ 在 $j$ 子树内。反之，则对于不在 $i, j$ 子树内的 $k$，必然有 $f(k, i) - f(k, j)$ 不等于上述两者。考虑按随机顺序枚举 $k$ 检查，若 $i, j$ 子树大小和为 $c$，则期望检查 $\frac n {n - c + 1}$ 次找到反例。

考虑一条链的极限情况，期望检查次数为 $\sum_{i = 1} ^ n \frac {n ^ 2} {i}$，时间复杂度 $\mathcal{O}(n ^ 2\ln n)$。[代码](https://codeforces.com/contest/1764/submission/183150346)。

---

## 作者：honglan0301 (赞：1)

我觉得这个方法比官方题解略简单一些，但可惜赛时打挂了……
## 题意简述
有一棵 $n$ 个节点的无根树，它的结构与边权未知。定义 $f(i,j)$ 表示所有节点到从 $i$ 至 $j$ 这条路径的距离之和，给出所有的 $f(i,j)$，请求出一棵可能的树，保证有解。

## 题目分析
不妨假设 $1$ 为根。我们先考虑如果知道一个点 $u$, 它的父节点 $fa$, 以及所有在它子树中的节点时该如何找到它的子节点。  

根据 $f(i,j)$ 表示距离之和的性质，固定 $i$ 时，每次延长路径后 $f(i,j)$ 都会减小。那么我们只需在 $u$ 的子树中找到一个点 $v$, 满足 $f(fa,u)-f(fa,v)$ 最小, $v$ 就一定是 $u$ 的子节点（否则在 $u,v$ 之间的节点会被我们选中），于是递归寻找。

那么我们还需要判断一个点 $x$ 是否在 $u$ 的子树中。这很好处理，因为如果点 $x$ 不在 $u$ 的子树中，路径 $(u,x)$ 就必然要经过 $fa$, $f(u,x)$ 就必然小于 $f(fa,x)$。反之 $f(u,x)$ 必然大于 $f(fa,x)$, 对其进行判断就好。  

在恢复了树的结构之后，我们再来找到边权。先 dfs 出每个点子树的大小，那么边 $(fa,u)$ 的边权就等于 ${f(1,fa)-f(1,u)}\over{size[u]}$, 因为向下扩展路径后只有 $u$ 子树中的节点会受到影响。  

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n,f[2005][2005],cnt,head[2005],sz[2005];
bool vis[2005];
struct edge
{
	int son;
	int next;
}edge[4005];
void adde(int x,int y)
{
	cnt++;
	edge[cnt].son=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
}
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
bool check(int now,int fat,int son)
{
	return f[now][son]>f[fat][son];
}
void dfs1(int now,int fat)//找子节点 
{
	//cout<<now<<" "<<fat<<endl;
	vis[now]=1;
	while(1)
	{
		int minn=20000000000000,nownum=0;
		for(int i=1;i<=n;i++)
		{
			if(i==fat||vis[i])
			{
				continue;
			}
			if(now!=1&&!check(now,fat,i))//当now==1时所有点都是它的子节点（因为假设1为根） 
			{
				continue;
			}
			if(minn>f[fat][now]-f[fat][i])
			{
				minn=f[fat][now]-f[fat][i];
				nownum=i;
			}
		}
		if(minn==20000000000000)
		{
			return;
		}
		adde(now,nownum);
		adde(nownum,now);
		dfs1(nownum,now);
	}
}
void dfs2(int now,int fat)//找size并计算边权 
{
	sz[now]=1;
	for(int i=head[now];i>0;i=edge[i].next)
	{
		if(edge[i].son==fat)
		{
			continue;
		}
		dfs2(edge[i].son,now);
		printf("%lld %lld %lld\n",now,edge[i].son,(f[1][now]-f[1][edge[i].son])/sz[edge[i].son]);
		sz[now]+=sz[edge[i].son];
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			f[i][j]=read();
			f[j][i]=f[i][j];
		}
	}
	dfs1(1,1);
	dfs2(1,1);
}
```


---

## 作者：Little09 (赞：0)

做法不大一样。

考虑递归找这个树。现在做到节点 $u$，所有除 $u$ 外在它子树里的点且还没被做的点集合为 $s$。

考虑找到 $u$ 的任意一个儿子 $v$。找法是对于每个在集合 $s$ 里的点 $x$，找到 $f(u,x)$ 最大的那个。显然最大那个是它儿子之一。

接下来算 $(u,v)$ 这条边的权值 $w$。考虑 $f(v,v)-f(u,v)$ 的值就是 $v$ 子树内的点的个数乘边权；$f(u,u)-f(u,v)$ 的值就是 $v$ 子树外的点的个数乘边权。相加就是 $nw$，可以算出 $w$。

最后递归下去，也就是把 $s$ 集合划分成两个集合，一个是 $u$ 子树剩下的点，一个是 $v$ 子树的点。考虑如果 $f(u,x)>f(v,x)$，那么在 $u$ 子树里；否则在 $v$ 子树里。


```cpp
void dfs(int u,vector<int>s)
{
	if (s.size()==0) return;
	int pos=s[0];
	for (int i:s) if (a[u][pos]<a[u][i]) pos=i;
	vector<int>s1,s2;
	for (int i:s)
	{
		if (i==pos) continue;
		if (a[u][i]>a[pos][i]) s1.pb(i);
		else s2.pb(i);
	}
	ll x=a[u][u]-a[u][pos],y=a[pos][pos]-a[u][pos];
	ll w=(x+y)/n;
	cout << u << " " << pos << " " << w << endl;
	dfs(u,s1),dfs(pos,s2);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=i;j++)
		{
			cin >> a[i][j];
			a[j][i]=a[i][j];
		}
	}
	vector<int>w;
	for (int i=2;i<=n;i++) w.pb(i);
	dfs(1,w);
	return 0;
}
```


---

## 作者：MSqwq (赞：0)

update 2022.12.16 图没了，重新上传一下  
感觉我的做法貌似和其他人不一样，个人觉得挺简单易懂的，代码也很短。  
赛时因为被 $D$ 坑了一个小时，然后就黑化没看后面的题了，但发现后面的题都挺有意思的。  
这题又是扣扣莉出的耶！我个人比较喜欢这题。  


------------
题意：  
设 $f(x,y)$ 表示为 $x$ 和 $y$ 连一条边，会形成一个环，每个点到环上任意一点的最短路之和。题目给你 $n$ 个点任意两点的 $f$ 值，让你还原这棵树。  


------------
题解：  
这个题的妙点就在于 $f(x,x)$,不难发现离 $x$ 越近的点被重复算的次数越多，而且 $x$ 取不同，每条边被重复算的次数也不同 ~~（这不显然吗）~~。  
那么根据这个性质其实可以求出任意两点的距离。  
举个例子（如图，红色数字表示被算的次数）：   
![](https://pic4.zhimg.com/80/v2-3950ebae4d81d2bb1ebfd5ffaba9f24f_720w.webp)  
![](https://pic3.zhimg.com/80/v2-65aaebf5326d86c7691ae5acbb45e25e_720w.webp)  
你会发现除了两个 $x$ 之间边被重复算的次数之外，其他边被重复算的次数都一样，那么可以考虑容斥，容斥其实就是 $dis_{x_1,x_1}+dis_{x_2,x_2}-2 \times dis_{x_1,x_2}$。这个应该都能理解，容斥完后，其实就发现，两个 $x$ 之间的点，恰好被重复算了 $n$ 次。  
其实也很好证明，对于 $2 \times dis_{x_1,x_2}$ 两个 $x$ 中间的边肯定是没被算的，因为已经成环了，然后对于 $dis_{x_1,x_1}+dis_{x_2,x_2}$ 其实可以理解每个点都到了这两个 $x$ 之间的边，所以重复算了 $n$ 次。  
那么我们任意两点的距离都算出来了，现在要生成一棵树，为了满足我们前面求出来的距离，所以需要每条边要最小，所以跑最小生成树。     
感觉我这种容斥的思想挺妙的，如果哪里我没讲清楚的欢迎大家来找我问哇qwq
代码如下：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e3+10,M=4e6+10;
struct qwq{
	int x,y;
	ll z;
}e[M];
int num,f[N];
int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
bool cmp(qwq x,qwq y){return x.z<y.z;}
ll a[N][N];
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)a[i][j]=a[j][i]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)e[++num]={i,j,(a[i][i]+a[j][j]-2*a[i][j])/n};
	sort(e+1,e+1+num,cmp);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=num;i++)
	{
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx!=fy)
		{
			f[fx]=fy;
			printf("%d %d %lld\n",e[i].x,e[i].y,e[i].z);
		}
	}
	return 0;
}

```


---

## 作者：intel_core (赞：0)

若 $(x,y)$ 不存在，连接 $(x,y)$ 后可以发现环就是 $x$ 到 $y$ 路径上的点。我们此时可以在 $x$ 到 $y$ 的路径上找一点 $z$。不难发现，连接 $(x,z)$ 时的环和连接 $(z,y)$ 时的环是连接 $(x,y)$ 时的环的子集。

这样一来不难发现 $f(x,z),f(z,y)>f(x,y)$，所以原树即为以 $(x,y,f(x,y))$ 为边的最大生成树。

现在考虑把边权求出来，我们可以借助 $f(i,i)$ 表示所有点到自己的距离和来简化。随意选取一条边 $(x,y)$，那么只有在以 $x$ 为根时 $y$ 的子树内的点对 $f(x,x)-f(x,y)$ 有 $w_{(x,y)}$ 的贡献。子树大小可以轻松求出，相除即可。

复杂度 $O(n^2\log n)$，瓶颈来自 $\text{Kruskal}$ 求最小生成树，当然用 $\text{Prim}$ 也没问题。

---

