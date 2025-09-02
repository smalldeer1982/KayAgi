# Tenzing and Tree

## 题目描述

Tenzing has an undirected tree of $ n $ vertices.

Define the value of a tree with black and white vertices in the following way. The value of an edge is the absolute difference between the number of black nodes in the two components of the tree after deleting the edge. The value of the tree is the sum of values over all edges.

For all $ k $ such that $ 0 \leq k \leq n $ , Tenzing wants to know the maximum value of the tree when $ k $ vertices are painted black and $ n-k $ vertices are painted white.

## 说明/提示

Consider the first example. When $ k=2 $ , Tenzing can paint vertices $ 1 $ and $ 2 $ black then the value of edge $ (1,2) $ is 0, and the values of other edges are all equal to $ 2 $ . So the value of that tree is $ 4 $ .

## 样例 #1

### 输入

```
4
1 2
3 2
2 4```

### 输出

```
0 3 4 5 6```

## 样例 #2

### 输入

```
1```

### 输出

```
0 0```

# 题解

## 作者：cwfxlh (赞：6)

# [CF1842F](https://www.luogu.com.cn/problem/CF1842F)   

考虑对于一个 $k$ 个点的选择方案，以这 $k$ 个点的重心为根确定树的结构，容易发现，因为根节点是重心，所以每个子树里的黑点不过半，于是答案变为：     

$$\sum_{i\ne j}{k-2\times sum_i}=(n-1)k-2\times\sum_{col_i=black}{(dep_i-1)}$$   


于是我们考虑枚举重心 $p$，则此时最小的答案就是选 $dep$ 最小的 $k$ 个点作为黑色点。这里不需要考虑选出来后发现重心不是 $p$ 的问题，因为重心错误只会导致答案更小。于是我们直接钦定重心，dfs 计算深度就可以了。复杂度 $\Theta(n^2)$ 或 $\Theta(n^2\log n)$，区别在于使用桶排还是快排。   


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v,dep[100003],num[10003],ans[10003],sum;
vector<int>E[100003];
void dfs(int now,int p){
	for(auto i:E[now]){
		if(i!=p){
			dep[i]=dep[now]+1;
			dfs(i,now);
		}
	}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		E[u].emplace_back(v);
		E[v].emplace_back(u);
	}
	for(int i=1;i<=n;i++){
		dep[i]=1;
		dfs(i,0);
		sort(dep+1,dep+n+1);
		sum=0;
		for(int k=1;k<=n;k++){
			sum+=dep[k];
			ans[k]=max(ans[k],(n+1)*k-sum*2);
		}
	}
	for(int i=0;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：EuphoricStar (赞：5)

事实上自己方向一直是错的……

绝对值不好弄，我一开始的想法是直接去绝对值，但是不可避免地要 $O(n^3)$。

考虑我们直接**钦定黑点重心为根**，设这个根为 $r$，设 $sz_i$ 为 $i$ 子树内黑点数，由重心的性质，可以直接去绝对值，也就是说答案为 $\sum\limits_{i \ne r} k - 2 sz_i$。

考虑拆贡献，一个黑点 $u$ 会对它的所有除了根的祖先都造成 $-2$ 的贡献，也就是说贡献是 $-2 \times \text{dis}(u, r)$。于是我们贪心地选择与 $r$ 的距离最小的染黑即可。

因为如果 $r$ 不是重心，会产生负贡献，所以最优解一定是合法的。

时间复杂度 $O(n^2)$。

[code](https://codeforces.com/contest/1842/submission/211001718)

---

## 作者：262620zzj (赞：4)

研学题目 4/10
# 前置工作
记 $num_i$ 为点 $i$ 子树内的黑点数量。首先进行一个边权转点权。如果树是一个有根树，每条边的权值等于 *它通向的儿子节点的* 子树外的黑点数量减去子树内的黑点数量。这样，根之外的每个点对应一条边，整棵树的权值就是
$$\sum_{i\neq root}|k-2num_i|$$
# 解法
我们可以钦定一个点为黑点的**重心**，并以它为根计算。根据重心的性质，$2num_i\le k$，所以化简为
$$(n-1)k-2\sum_{i\neq root}num_i$$
我们只需要最小化后面一部分。每个黑色的点只会让它到根的路径上的点的 $num$ 增加 $1$，所以，黑色的点应该选择深度最小的 $k$ 个点。整棵树的权值为
$$(n-1)k-2\sum_{i=1}^kdep_i$$
所有点作为重心的权值里面取最大值即可。

如果这样染色 $root$ 不是重心也没关系。因为这样只会使得权值变小。每个点都会当一次重心，因而正确的重心会被取到。

每次枚举 $root$，遍历树求出 $dep$ 再排序，并计算其前缀和。时间复杂度 $O(n^2\log n)$。
#代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
template<typename T,typename ...Args>
void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=5005;
int tot,head[N];
struct edge{int to,nx;}e[2*N];
void add_edge(int u,int v){
    e[++tot]={v,head[u]};
    head[u]=tot;
}
int n,dep[N],ans[N],sum[N];
void dfs(int u,int from){
    dep[u]=dep[from]+1;
    for(int i=head[u];~i;i=e[i].nx){
        int v=e[i].to;
        if(v==from)continue;
        dfs(v,u);
    }
}
int main(){
    memset(head,-1,sizeof(head));
    memset(ans,0x7f,sizeof(ans));
    read(n);
    for(int u,v,i=1;i<n;i++){
        read(u,v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int r=1;r<=n;r++){
        dep[0]=-1;
        dfs(r,0);
        sort(dep+1,dep+1+n);
        sum[0]=0;
        for(int i=1;i<=n;i++)sum[i]=sum[i-1]+dep[i];
        for(int i=0;i<=n;i++)ans[i]=min(ans[i],2*sum[i]);
    }
    for(int k=0;k<=n;k++)printf("%d ",(n-1)*k-ans[k]);
    return 0;
}
```


---

## 作者：出言不逊王子 (赞：3)

考虑黑色的点组成了一棵树，它们的根是 $r$。

则答案的式子是 $\sum_{u\ne r} |(k-sz_u)-sz_u|=\sum_{u\ne r}|k-2sz_u|$。

考虑重心的限制，则我们假设这个 $r$ 正好就是树的重心。则此时 $\forall u\ne r,k\ge 2sz_u$，所以绝对值符号可以直接拆掉。

如果 $r$ 不是重心也没关系，反正答案不会变大。

因为 $sz_r=k$，所以上式可继续化为 $\sum_{u\ne r} k-2sz_u=(n-1)k-2\sum_{u\ne r}sz_u+2k-2k=(n+1)k-2\sum_u sz_u$。

因为左边固定，所以我们要让 $\sum_u sz_u$ 最小。

考虑一个黑点 $u$ 对所有 $sz$ 的贡献：它会让从 $u$ 到 $r$ 的所有节点的 $sz$ 增加 $1$。

所以一个黑点对上面式子的贡献就是 $dep_u$，即 $u$ 到 $r$ 的路上经过的点数。

所以现在这个式子变成了 $\sum_{u\ \text{is black}} dep_u$。

如果黑点位置不同，会导致 $sz$ 全部变化，但 $dep$ 不变（只和 $r$ 有关）。

所以我们可以在知道黑点的位置前就知道 $dep_u$，从而做出决策。

我们想让这个式子最小，那么就取前 $k$ 小的 $dep$ 即可。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=1e18;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
vector<int> e[N];
void add(int u,int v){e[u].push_back(v);e[v].push_back(u);}
int n,m,dep[N],res[N];
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	for(auto v:e[now]) if(v!=fa) dfs(v,now);
}
signed main(){
	n=read();fs(i,1,n-1,1){
		int u=read(),v=read();
		add(u,v);
	} fs(i,1,n,1) res[i]=inf;
	fs(i,1,n,1){
		int sum=0;dfs(i,0);
		sort(dep+1,dep+n+1);
		fs(j,1,n,1) sum+=dep[j],res[j]=min(res[j],sum);
	}
	fs(k,0,n,1) cout<<(n+1)*k-2*res[k]<<' ';
	return 0;
}
//枚举黑点的重心，8dp3qorx 
```

2023/7/7 18:43

---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/CF1842F)

------------

做 *2500 做了一个半小时，还有救吗？

一个很大的误区是通过拆绝对值贡献优化 $O(n^3)$ 的树形 dp 做法。它会浪费某些人（比如说我）很大时间。

事实上，在尝试拆贡献的过程中，我们发现这样一个性质：以 $1$ 为根，令 $f_x$ 表示 $x$ 子树内的黑点个数，则贡献为 $2f_x-k$ 的点为根开始的一条链。

不妨枚举链尾，不难发现这个点的实质即为黑点的重心，我们考虑以它为根，很好的是：此时贡献被统一成了 $k- 2f_x$。换个角度，考虑每个被选点对边的贡献，不难发掘按深度从小到大选点即为正确的贪心策略。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5010;
ll ans[N];
vector<int> vec[N];
int n,tim,q[N],dep[N];
inline void dfs(int u,int fa){dep[u]=dep[fa]+1;for(auto v:vec[u]) if(v!=fa) dfs(v,u);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	for(int x=1;x<=n;x++)
	{
		dep[x]=-1;dfs(x,x);
		int head=1,tail=0;q[++tail]=x;
		while(head<=tail)
		{
			int now=q[head++];
			for(auto to:vec[now]) if(dep[to]>dep[now]) q[++tail]=to;
		}
		ll s=0;
		for(int i=1;i<=n;i++) s+=2*dep[q[i]],ans[i]=max(ans[i],1ll*i*(n-1)-s);
	}
	for(int i=0;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}

```

---

## 作者：Little09 (赞：2)

$|k-2x|$ 绝对值你解决不掉也不好拆，那么考虑找一个黑点的重心 $rt$，这样一定满足 $2x\le k$，所以可以直接拆掉。

于是每局这个 $rt$，现在形式变成了 $\sum (k-2x)$，也就是最小化 $\sum x$，那么每个点的贡献就是到根的边数，所以贪心按深度选就行。

那如果选的 $rt$ 不是重心呢？想必是没事的，因为如果实际上是 $2x-k$ 你算成了 $k-2x$，由于后者是一个负数，所以你得到的结果只会变小，不影响最大化的结果。

“按深度选”的时候如果跑一个 BFS 就是 $O(n^2)$，如果直接把深度 sort 一下就是 $O(n^2\log n)$，都能过。

---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF1842F)

## 题意

令树上边的权值为：边的两侧黑点数量差的绝对值。

树的权值为每一条边的权值和。

$\forall k \in [0,n]$，求出在随意安排黑点位置时，树的最大权值。

## 思路

令点 $R$ 为黑点的重心（即到所有黑点距离和最小的点），并钦定其为根。

由于重心的性质，$R$ 的每个子树内的黑点数量不超过总数的一半。于是我们可以把绝对值拆掉。

令 $s_u$ 为以 $u$ 为根的子树中黑点数量，答案为 $\displaystyle\sum_{u \in V, u != R}k-s_u \times 2$。

考虑一个点对 $s$ 的贡献，若一个点为黑点，那么所有包含这个点的子树的 $s_u$ 都会增加 $1$，这些子树具体为：根是这个点到根节点之间路径上的点的子树

令根节点深度为 $0$，若一个点为黑点，它对答案的贡献为它的深度。

又因为答案要求尽可能大，那么 $s$ 要尽可能小。于是我们可以枚举根节点，将深度从小到大排序，更新答案。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 5e3 + 5;

int d[kMaxN];
LL n, cnt, c[kMaxN];
vector<int> g[kMaxN];

void DFS(int u, int fa) {
  for (int v : g[u]) {
    if (v != fa) {
      d[v] = d[u] + 1, DFS(v, u);
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    d[i] = 0, DFS(i, -1);
    sort(d + 1, d + n + 1), cnt = 0;
    for (int j = 1; j <= n; j++) {
      cnt += d[j], c[j] = max(c[j], (n - 1) * j - 2 * cnt);
    }
  }
  cout << "0 ";
  for (int i = 1; i <= n; i++) {
    cout << c[i] << ' ';
  }
  cout << '\n';
  return 0;
}
```

---

## 作者：xuantianhao (赞：1)

# [Tenzing and Tree](https://www.luogu.com.cn/problem/CF1842F)

**感觉很典型的题，就是树的重心+绝对值等式**

## 解法：

以每个点 $i$ 为根分别 BFS，得到一个距离数组 $dis$，取前 $k$ 个值的权值为和，更新 $w[k]$ 的值，$n$ 个点分别为根，更新 $n$ 遍之后，得到 $w$ 数组，则 $(n-1)\times i-w[i]$，即为 $i$ 个点时候的答案

下面证明一下正确性：

## 1、

首先，证明最优解下点一定是联通的，我们可以假设一开始的时候，在树的一个叶子节点上，放了 $k$ 个黑点，也就是假设一开始没有一个节点上只能放一个黑点的限制，后续通过我们不断平移, 一次将一个黑点平移到相邻边，使得最终 $k$ 个黑点分摊在 $k$ 个树上的真实节点上。

那一开始的时候，总贡献即为 $(n-1) \times k$，当第一次平移一个点的时候，有一条边的贡献发生了变化，不断的平移，总贡献和就不断的减少。

那假设黑点不是联通的，不妨考虑只差-步的情形，一侧 $k-1$ 个点是联通的，另一侧一个黑点，且两个连通块之间隔着一个白点，那此时有两条边，满足一侧为 $n-1$ 个黑点，另一侧为一个点。

如果一个黑点占据了那个白点的位置，则可以使得只有一边，满足一侧为 $n-1$ 个黑点，另一侧为一个黑点，而刚才的另一条边，变为一侧有 $n$ 个黑点的情况，即总贡献 $+2$。

通过增量法，我们可以使得差 $x$ 步可以优化到差 $x-1$ 步，只差一步，最终优化到联通。

## 2、

其欺，证明一下刚才的求法能求得最优解，$w$ 数组对应的最小值，由于是 BFS 的（DFS 也可以），所以可以还原回树上的黑点连通块，固定根为 $i$，求得的 $dis$ 数组,选得前 $k$ 个求和，代表选了 $k$ 个点。

既可以理解为 $k$ 个黑点到根的距离和，$dis$ 等于 $x$ 表示每个点上方有 $x$ 个点,或者有 $x$ 条边，也可以理解为所有边对应的子树中的点的数量和，即交换求和顺序，从边的视角来看这个和式。

$$(n-1) \times k - \sum dis \times 2$$

$$=(n-k) \times k+k \times (k-1) -\sum dis \times 2$$

$$=(n-k) \times k+ \sum (k) - dis \times 2$$

$$=(n-k) \times k+ \sum (k-dis)-dis$$

答案的式子,在求 $k$ 个黑点的最优解时：

$\bullet$ 1、有 $n-k$ 条边，满足 $k$ 个点在这些边的一侧，其代价为 $(n-k) \times k$。

$\bullet$ 2、对于两侧都有黑点的这 $k$ 条边来说，后面和式表示非子树点数量和子树点数量和。

而这距离最终的答案还有一个绝对值。

如果是 $(n- k) \times k + \sum abs((k_i - dis) - dis)$，就是我们想要的答案了。

当枚举 $n$ 个根时，每个根都对应一个局部最优解，$n$ 个局部最优解的最大值，是最终解，最终解得到的连通块，还是一棵树，不妨称其为最优点树（不唯一），而树一定有重心，我们一定可以通过最优黑点树的重心 $Q$ 为根，枚举到某一棵最优黑点树。

此时，根据重心性质，子树大小不超过树总大小的一半，即 $dis \le k/2$，使得 $(k- dis)- dis$ 一定非负，和式等于 $\sum abs((k - dis) - dis)$。

那么其他非最优解的情况，其值只会多减，导致比 $abs$ 求和小，不会影响最优解。

有类似曼哈顿距离 $Q$ 的松弛，绝对等式：

$$abs(x-y)=max(x+y-2y,x+y-2x)$$ 

只要最优解下能和 abs 取等，其他情况下，算的不是 abs 也无妨。

## 代码：

```
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=5e3+100;
int n,u,v;
int dis[N],w[N];
vector<int> e[N];
inline int read(){
	char c=getchar();int f=1,x=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
void bfs(int u){
	for(int i=1;i<=n;i++) dis[i]=n+1;
	queue<int> q;
	q.push(u);
	dis[u]=0;
	int num=0,sum=0;
	while(!q.empty()){
		u=q.front();
		q.pop();
		num++;
		sum+=dis[u];
		w[num]=min(w[num],sum);
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
} 
int main(){
	n=read();
	for(int i=1;i<n;i++){
		u=read();
		v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	memset(w,INF,sizeof(w));
	for(int i=1;i<=n;i++) bfs(i);
	printf("0 ");
	for(int i=1;i<=n;i++) printf("%d ",(n-1)*i-2*w[i]);
	return 0;
}
```

---

## 作者：vegetable_king (赞：1)

[不佳的阅读体验](https://yjh965.github.io/post/cf1842f-tenzing-and-tree-ti-jie/)

最后五分钟过掉成功翻盘，纪念一下。

首先发现，如果要最大化价值，所选出的 $k$ 个点一定在树上形成一个连通块。

证明过程考虑调整，如果不形成联通块，则一定可以找到一个点，将它向黑点最多的方向移动一条边（满足目标节点没有黑点），这样操作之后，其他边的价值不变，而这条边的价值增加了 $2$，而形成连通块之后，没有任何一个点可以这样调整。

而且，我们还发现，对于一个 $k$，如果一条边不在点形成的连通块内，则它的价值一定是 $k$，这样的边有 $(n - 1) - (k - 1) = n - k$ 条，所以这部分的贡献与树的形态无关，为 $k(n - k)$。

于是问题接下来就变成，对于每个 $k$，都求出一个连通块最大化它内部的价值。

我们先考虑对于一棵全是黑点的树，这个价值怎么简单的算。如果对于每条边模拟计算，这样的价值带绝对值不便维护，所以考虑对于价值做适当的变换去掉绝对值。

把树定根，这样，价值就变成 $\sum_{u \ne rt} |sz_u - (k - sz_u)|$，也就是 $\sum_{u \ne rt} |k - 2sz_u|$，我们发现，当 $sz_u > \frac k2$ 时，$(u, fa_u)$ 这条边的价值才是 $|2sz_u - k|$。于是取这棵树的任意一个**重心**为 $rt$，则价值就变成了 $\sum_{u \ne rt} k - 2sz_u$，即 $k(k - 1) - 2\sum_{u \ne rt} sz_u$。

这时，我们就可以换根树上背包来求后式（就是这个 $\sum_{u \ne rt} sz_u$）的最小值了（换根是因为要钦定根为重心），但是不好做也没必要。

考虑分别计算每个点 $v$ 对后式的贡献，则每个 $v$ 的祖先 $u$（包括 $v$ 自己）都会在后式当中统计到它一次，而这个统计的次数也就是 $v$ 的深度 $dep_v$（即 $rt \to v$ 经过的边数），所以后式等价于 $\sum_{v \ne rt} dep_v$（实际上 $dep_{rt} = 0$，所以 $v \ne rt$ 这个限制是没用的）。

得到这个式子，这道题也就做完了，因为重心实际上还有另外一个性质，也就是满足树上所有的点到它的距离之和最小，所以钦定非重心为根的答案一定不优。

通过这个性质，我们直接对每个根 $rt$ 算出选 $k$ 个点的答案并取最小值即可。

对于每个根算答案可以做到 $O(n)$，则时间复杂度为 $O(n^2)$。

[code](https://codeforces.com/contest/1842/submission/210949159)

---

## 作者：mod998244353 (赞：0)

假设删掉边 $i$ 之后，两个连通块内的黑点个数为 $s_i,k-s_i$，那么边 $i$ 对答案贡献就是 $|s_i-(k-s_i)|$。

考虑去掉绝对值，得到 $k-2\min(s_i,k-s_i)$。

那么最终答案就是 $(n-1)k-2\sum\limits_{i=1}^{n-1}\min(s_i,k-s_i)$。

考虑最小化后面的和式：

> 结论1：最优解的黑点集合必定为一个连通块。

调整法可证（两个黑点在同一个黑点连通块一定比在两个连通块优）。

删掉所有白点后，黑点仍然是颗树。我们发现，假如以任一重心 $s$ 为根，那么那个和式就可以变成：

$$\sum\limits_{i\not=s} \operatorname{size}(i)$$

其中 $\operatorname{size}(i)$ 表示 $i$ 的子树大小。

由于 $\operatorname{size}(i)\leq\dfrac{k}{2}(i\neq s)$，所以上述式子一定是正确的。

> 结论2： $\sum\limits_{i=1}^k\operatorname{size}(i)=\sum\limits_{i=1}^k \operatorname{dep}(i)$，其中 $\operatorname{dep}(i)$ 表示点 $i$ 的深度。

证明：一个节点 $i$ 会对它及它的祖先（一共 $\operatorname{dep}(i)$ 个节点）的 $\operatorname{size}$ 贡献 $1$。

$$\begin{aligned}\sum\limits_{i\not=s}\operatorname{size}(i) & = (\sum\limits_{i=1}^k \operatorname{dep}(i))-\operatorname{size}(s) \\ & = \sum\limits_{i=1}^k (\operatorname{dep}(i)-1)\end{aligned}$$


根据这个式子可以看出，我们直接选深度前 $k$ 小的节点就行。

本题做法：

枚举重心 $s$，bfs 算出所有点的深度，同时计算前 $k$ 小节点的深度和，算完之后对答案更新。

时间复杂度为 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005;
int dis[MAXN],s[MAXN],n,ans[MAXN];
vector<int>vec[MAXN];
queue<int>q;
int main() {
	scanf("%d",&n);
	for(int i=1,u,v; i<n; ++i) {
		scanf("%d%d",&u,&v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j) dis[j]=-1;
		dis[i]=0,q.push(i);
		int t=0;
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			s[++t]=dis[u];
			s[t]+=s[t-1];
			for(int v:vec[u])
				if(!(~dis[v])) {
					dis[v]=dis[u]+1;
					q.push(v);
				}
		}
		for(int j=0; j<=n; ++j)
			ans[j]=max(ans[j],(n-1)*j-2*s[j]);
	}
	for(int i=0; i<=n; ++i) printf("%d ",ans[i]);
	return 0;
} 
```

---

