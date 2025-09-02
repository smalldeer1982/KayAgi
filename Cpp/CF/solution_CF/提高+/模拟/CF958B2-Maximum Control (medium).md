# Maximum Control (medium)

## 题目描述

The Resistance is trying to take control over as many planets of a particular solar system as possible. Princess Heidi is in charge of the fleet, and she must send ships to some planets in order to maximize the number of controlled planets.

The Galaxy contains $ N $ planets, connected by bidirectional hyperspace tunnels in such a way that there is a unique path between every pair of the planets.

A planet is controlled by the Resistance if there is a Resistance ship in its orbit, or if the planet lies on the shortest path between some two planets that have Resistance ships in their orbits.

Heidi has not yet made up her mind as to how many ships to use. Therefore, she is asking you to compute, for every $ K=1,2,3,...,N $ , the maximum number of planets that can be controlled with a fleet consisting of $ K $ ships.

## 说明/提示

Consider the first example. If $ K=1 $ , then Heidi can only send one ship to some planet and control it. However, for $ K>=2 $ , sending ships to planets 1 and 3 will allow the Resistance to control all planets.

## 样例 #1

### 输入

```
3
1 2
2 3
```

### 输出

```
1 3 3 ```

## 样例 #2

### 输入

```
4
1 2
3 2
4 2
```

### 输出

```
1 3 4 4 ```

# 题解

## 作者：naoliaok_lovely (赞：2)

一道长链剖分模板题。

## 切入点
显然，$|S|=1$ 时答案为 $1$，$|S|=2$ 时答案为树的直径上点的个数。看到直径，于是联想到**贪心**。  
由于数据不允许我们使用 $O(n^2)$ 的方式分别处理，容易猜想到每次的答案之间是有一定关系的，进一步可以发现前一次所选择的点一定被下一次选择的点集完全包含（不难证明）。

为了处理方便，我们把直径的某一个端点当做树根。

# 贪心
问题已经转化成了：每次在树上取一个点，这个点到点集内其它点的路径上的点都会被加入集合。且显然，我们第一次取的会是根节点。  
将上述过程画成一张图：  
![有效点.PNG](https://cdn.acwing.com/media/article/image/2023/10/12/104910_bc7da01968-有效点.PNG)   
显然，直径为 $(1,6)$，图中选择点的顺序为 $1,6,4,5$，其中**实线**表示有效贡献，**虚线**表示无效贡献。

可以发现，其实有效贡献一定是**当前选择的点到根节点的路径中下面连续的一段**。易证得其它的贡献都会失效。 

于是就变成了**长链剖分**的版题。（以下内容会长链剖分的可以跳过）  
对于每一个节点 $i$，计算以它为端点的最长路径的长度（要求另一端点必须在子树内）。显然其实就是把这个点和子树内最深的点连起来。于是可以发现，原树被分成了若干条链，且这些链覆盖的点集是全集的一个划分。于是将这些链的长度排序后贪心的取最长的就好了。

## Code
```
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, ans[N], root;
int q[N], tt;

int h[N], ne[M], e[M], idx;
void add(int a, int b)
{
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
}

int deep[N];
void dfs(int x, int fa)
{
	deep[x] = deep[fa] + 1;
	for(int i = h[x]; i; i = ne[i])
		if(e[i] != fa) dfs(e[i], x);
}

int dfs1(int x, int fa)
{
	int maxn = 0;
	for(int i = h[x]; i; i = ne[i])
		if(e[i] != fa)
		{
			int j = e[i];
			int t = dfs1(j, x);
			if(t > maxn) q[++tt] = maxn, maxn = t;
			else q[++tt] = t;
		}
	return maxn + 1;
}

int main()
{
	cin >> n;
	for(int i = 1, a, b; i < n; i++)
		scanf("%d%d", &a, &b), add(a, b), add(b, a);
	dfs(1, 0);
	for(int i = 1; i <= n; i++)
		if(deep[i] > deep[root]) root = i;
		
	q[++tt] = dfs1(root, 0);
	sort(q + 1, q + tt + 1, greater<int>());
	
	for(int i = 1; i <= tt; i++) ans[i + 1] = ans[i] + q[i];
	ans[1] = 1;
	for(int i = 1; i <= n; i++) printf("%d ", ans[i] = max(ans[i], ans[i - 1]));
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

$2200$ 也好简单！考虑 $|S|=1$ 的时候答案只能为 $1$，$|S|=2$ 的时候肯定是选直径。$|S|>2$ 的时候就是每一次在当前选择了的结点中找到这个结点对应的最长链，然后把这个链上所有的结点加入当前选择的结点，重复执行 $|S|-2$ 次即可。发现这个东西写一个长链剖分就完事了。时间复杂度为 $O(n)$。

---

## 作者：Nuisdete (赞：1)

我们考虑每次操作是将一段路径染色，然后贪心地再找到一个到染过色的点最近距离最远的点再染色它和其它点的路径，然后我们不难发现一个性质，就是以直径上任意一个点做根后，如果 $u$ 没被染色，则 $u$ 的子树都没被染色，然后我们就用线段树维护每个点到染色过色的点的最近距离。

然后线段树上二分找到最近距离最远的点，一直跳 $father$ 直到 $father$ 被染过色，跳的过程中线段树权值清零并更新它儿子的子树的答案即可。

代码：[https://codeforc.es/problemset/submission/958/199635294](https://codeforc.es/problemset/submission/958/199635294).

---

## 作者：Crab_Dave (赞：0)

## CF958B2 题解

+ ### 题意

  给你一颗由 $n$ 个点组成的**树**（$1\leq n\leq 10^5$）。对于一个点集 $S$,它所**占领**的点为：

  - 点集 $S$ 中的所有点
  - 对于任意 $u,v \in S$，$u$ 到 $v$ 路径上的点。

  现在问你当点集的大小分别为 $1$ 到 $n$ 时， **占领**的点的数量最大是多少？

+ ### 思路

  从最简单的情况入手。

  显然 $k=1$ 时，$ans = 1$。

  显然 $k=2$ 时，我们选取树的直径作为最优的路径。

  当 $k=3$ 时，我们考虑在直径外另找一个点，显然最优的方案是选择一个叶子节点。

  我们可以一次dfs求出每个点子树中最深的叶子节点，那么贪心在直径上选取即可。

  $k=4,5,6....$ 时，我们在剩下的叶子节点中接着选取。这时我们发现，一棵子树只能有一条路径覆盖到子树根节点以上的点，选其它路径时子树以上已经被覆盖完了。

  这个思想和轻重链剖分的思想好像啊。

  所以就按照差不多的思路剖分就好了。

+ ### 代码

  `dfs1` 求出直径的一端，`dfs2` 和剖分思路相同，求出重儿子，`dfs3` 处理出轻重儿子的答案，然后贪心选取。

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  
  #define ll long long
  const int maxn=1e5+5;
  int n,u,v,rt,d[maxn],son[maxn],h[maxn];
  int head[maxn],cnt;
  struct edge{
  	int to,next;
  }e[maxn<<1];
  vector<int>val;
  
  void adde(int u,int v){
  	e[++cnt].to=v;
  	e[cnt].next=head[u];
  	head[u]=cnt;
  }
  
  void dfs1(int u,int fa){
  	d[u]=d[fa]+1;int num=0;
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		dfs1(v,u);num++;
  	}if(!num){if(!rt||d[u]>=d[rt])rt=u;}
  }
  
  void dfs2(int u,int fa){d[u]=d[fa]+1;h[u]=d[u];
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		dfs2(v,u);h[u]=max(h[u],h[v]);
  		if(!son[u])son[u]=v;
  		else if(h[son[u]]<h[v])son[u]=v;
  	}
  }
  
  void dfs3(int u,int fa,int tp){
  	if(!son[u]){val.push_back(d[u]-d[tp]);return;}
  	dfs3(son[u],u,tp);
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		if(v==son[u])continue;
  		dfs3(v,u,u);
  	}
  }
  
  int main(){
  	scanf("%d",&n);
  	for(int i=1;i<n;i++){
  		scanf("%d%d",&u,&v);
  		adde(u,v);adde(v,u);
  	}rt=0;ll ans=0;
  	dfs1(1,0);dfs2(rt,0);dfs3(rt,0,0);printf("1 ");
  	sort(val.begin(),val.end(),greater<int>());
  	for(int i=2;i<=n;i++){
  		if(i-2<val.size())ans+=val[i-2];
  		printf("%lld ",ans);
  	}return 0;
  }
  ```

  

---

## 作者：JK_LOVER (赞：0)

# 题意
一棵树，求出最长不重链覆盖。[$QAQ$](https://www.luogu.com.cn/blog/xzc/solution-cf958b2)
# 分析
一个节点只会被一条链覆盖。那么根据长链剖分的思想，只需要把所有链储存下来排个序就可以了，贪心的选取最大的链。时间复杂度为 $O(n\log n)$ 。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = 1;ch = getchar();}
	while(isdigit(ch)) {x = x * 10 + ch - '0';ch = getchar();}
	return f ? -x : x;
}
const int N = 1e5 + 10;
vector<int> G[N],len;
int rt,dep[N],f[N],son[N],n; 
void dfs1(int x,int fa,int d) {
	dep[x] = d;
	for(auto y:G[x]) {if(y == fa) continue;dfs1(y,x,d+1);}
	if(dep[rt] < dep[x]) rt = x;
}
void dfs2(int x,int fa) {
	for(auto y:G[x]) {if(y == fa) continue;dfs2(y,x);if(f[son[x]]<f[y])son[x] = y;} 
	f[x] = f[son[x]] + 1;
	for(auto y:G[x]) {if(y == fa||y == son[x]) continue;len.push_back(f[y]);}
}
signed main() {
	n = read();
	for(int i = 1;i < n;i++) {
		int a = read(),b = read();
		G[a].push_back(b);G[b].push_back(a);
	}
	dfs1(1,0,1);
	dfs2(rt,0);len.push_back(f[rt]);
	sort(len.begin(),len.end());
	int ans = 0;printf("1 ");
	if(n == 1) return 0;
	for(int i = len.size()-1;~i;i--) {
		printf("%d ",ans = ans+len[i]);
	}
	n = n - len.size() - 1;
	while(n--) printf("%d ",ans);printf("\n");
	return 0;
}
```


---

