# [NWRRC 2017] Hidden Supervisors

## 题目描述

有一棵大小为 $n$ 的有根树，根为 $1$，其中若干结点的父亲没有确定。试求出所有可能构成的以 $1$ 为根的有根树中，最大匹配的最大值是多少，并输出构造方案。保证数据有解。

## 说明/提示

$2\leq n\leq 10^5,0\leq p_i\leq n.$

## 样例 #1

### 输入

```
6
3 1 0 4 4
```

### 输出

```
2
3 1 2 4 4
```

## 样例 #2

### 输入

```
6
3 1 0 6 4
```

### 输出

```
3
3 1 1 6 4
```

# 题解

## 作者：command_block (赞：12)

鱼大博客长长长，暂且没看，自己做出来了，感动（

**题意** ： 给定一个 $n$ 个点的内向森林，其中 $1$ 号点为某个树的根。

你需要将这个森林连成一棵以 $1$ 为根的有根树，并使得最终树（对应的无根树）的最大匹配尽可能大。

$n\leq 10^5$ ，时限$\texttt{3s}$。

------------

最终方案显然是除了 $1$ 外每个根连出一条边。

------------

- **树上最大匹配的贪心** ：从深往浅考虑，每个点若能匹配父亲则匹配。

  注意，若占用根的最大匹配和不占根的最大匹配大小相同，贪心会得出不占根的方案。
  
我们考虑逐棵树考虑根的连边情况，且要求新的小树 $T'$ 必须连接到 $1$ 所在的大树 $T$ 上。

假设我们已经确定了一种树的排列，如何构造最优的方案。（显然每种方案都能对应一种排列）

记准备接到大树 $T$ 上的小树为 $T'$。

记 $\max(T)$ 为 $T$ 的最大匹配。由于只加了一条边，连接后最大匹配的上界显然为 $\max(T)+\max(T')+1$ 。

观察连接之后贪心的形为。由于贪心从浅到深考虑，$T'$ 内部的匹配不会变化。

记 $T'$ 的根为 $t$ 。

- $\max(T')$ 含 $t$

  此时新边的深端（$T'$ 的根）已经被占用，故新边一定不会被选中。$T,T'$ 原有的匹配均保持。
  
- $\max(T')$ 不含 $t$

  容易想到，若 $T$ 中存在非匹配点，则将 $t$ 与之连接，能多出一个匹配边。这已经达到上界。
  
  否则，若 $T$ 中不存在非匹配点，考虑点集 $T\cup\{t\}$ ，它们之中的匹配才可能变化。但现在满匹配仅多加一个点，显然匹配不可能增大。
  
综上，我们证明了 ： 

加入 $T'$ 时，若 $T'$ 的根为非匹配点，且 $T$ 中存在非匹配点 $v$ ，则连接 $(t,v)$ 并使匹配加一。

若条件不满足，匹配不可能增大，为避免影响匹配情况（不便考虑），直接令 $t$ 与 $1$ 相连，不难发现此时可以认为贪心算法不会改动匹配。

------------

- 观察如上算法的行为：

  记顺序为 $T_{1\sim m}$ ，其中 $T_1$ 肯定是 $1$ 所在的树。

  $T_1$ 能提供若干非匹配点（可能包括根）。

  对于 $T_2$ ，若根非匹配，选择一个非匹配点连接。若根已匹配，或找不到非匹配点，则弃疗，直接连向 $1$ 。不要忘记添加新的非匹配点。

接下来进一步考虑：何种顺序才是最优的？

我们的目标是尽量让更多的树加入时能新增匹配，这和现存的非匹配点有关。不难想到经典的贪心：根已匹配的树无要求，先直接圈接入，接下来在根非匹配的树中，让非匹配点更多的树打头阵。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define MaxN 100500 
using namespace std;
vector<int> p[MaxN],g[MaxN];
int st[MaxN],tn;
bool vis[MaxN];
void dfs(int u,int fa)
{
	for (int i=0;i<g[u].size();i++)dfs(g[u][i],u);
	if (!vis[u]&&!vis[fa])vis[u]=vis[fa]=1;
	if (!vis[u])st[++tn]=u;
}
int a[MaxN],fa[MaxN],nrt,w[MaxN];
bool cmp(int A,int B){return w[A]>w[B];}
int main()
{
  int n;scanf("%d",&n);
  for (int i=2;i<=n;i++){
  	scanf("%d",&fa[i]);
  	if (fa[i])g[fa[i]].push_back(i);
  }
  vis[0]=1;
  int ans=0;
  for (int u=1;u<=n;u++)if (!fa[u]){
    	tn=0;
    	dfs(u,0);
    	ans+=tn;
    	for (int i=1;i<=tn;i++)p[u].push_back(st[i]);
    	w[u]=(vis[u] ? n+1 : p[u].size());
    	a[++nrt]=u;
    }
  ans=(n-ans)/2;
  w[1]=n+2;
  sort(a+1,a+n+1,cmp);
  tn=0;
  for (int i=0;i<p[1].size();i++)st[++tn]=p[1][i];
  for (int k=2;k<=n;k++){
  	int u=a[k];
  	while(tn&&vis[st[tn]])tn--;
  	if (!vis[u]&&tn){vis[u]=1;vis[fa[u]=st[tn]]=1;ans++;}
  	else fa[u]=1;
  	for (int i=0;i<p[u].size();i++)st[++tn]=p[u][i];
  }
  printf("%d\n",ans);
  for (int i=2;i<=n;i++)printf("%d ",fa[i]);
	return 0;
}
```

---

## 作者：P_VICVIC_R (赞：1)

~~集训时保咕值的题解*2~~

---

### 题意：
给你一~~片~~森林，你要将其合并（即用该树的根区连接其他树的叶子）成一棵树（指定该树的根为 $1$），使**树上的匹配最大**。

### 思路

**树上的最大匹配**很容易想到**贪心**，即从**叶子向父亲匹配，能匹配就匹配**。

那么很明显除了树的根和部分叶子，其余节点都会被匹配。

首先合并操作并不会改变树的内部构成，那么也就不会影响到已有的树的匹配，所以答案至少是**所有树的最大匹配数求和**。

我们考虑在合并时**让没有匹配到的根与没有匹配的叶子相匹配**，来产生新的匹配。

要注意的是我们在进行每一次的合并时要考虑到以后合并时是否有足够的“没有匹配的叶子”，来进行后续的匹配。即合并时要**尽量使有“没有匹配的叶子”的树先匹配**。

### code
略微有点注释的代码：
```
#include<bits/stdc++.h>
#define int long long  
using namespace std;
static const int N=1000000;
int n,m;
vector<int> gl[N],can,Epty[N];
int trcnt;
struct Tree{
	int Weight,Root;
	inline bool operator<(const Tree& xi) const {
		return Weight>xi.Weight;
	}
}T[N];
int Fro[N],Vis[N];
signed main(){
	freopen("hidden.in","r",stdin);
	freopen("hidden.out","w",stdout);
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i=2;i<=n;i++){
		int fr;
		cin>>fr;
		Fro[i]=fr;
		gl[fr].push_back(i);
	}
	function<void(int)> Run=[&](int rt)->void{
		for(auto to:gl[rt])
			Run(to);
		if(!Vis[rt] and !Vis[Fro[rt]])//父节点未访问，当前节点也为访问，那么就组成一个匹配 
			Vis[rt]=Vis[Fro[rt]]=1;
		if(!Vis[rt])/*父节点已访问，当前节点未访问，
					 *那么父节点就是被其他兄弟节点占用了，
					 *当前节点就可以用于挂其他树的根 
					 */
			can.push_back(rt);
	}; 
	int ans=0;
	Vis[0]=1;
	for(int i=1;i<=n;i++){
		if(!Fro[i]){/*父节点为0代表其为当前树的根 */ 
			can.clear();
			Run(i);
			ans+=can.size();
			Epty[i]=can; 
			T[++trcnt]={(Vis[i]?n+1:Epty[i].size()),i};		
			if(i==1)
				T[trcnt].Weight=n+2; 
		} 
	}
	ans=(n-ans)/2;
	sort(T+1,T+1+n);
	can.clear();
	for(auto to:Epty[1])
		can.push_back(to);
	for(int i=2;i<=n;i++){
		int rt=T[i].Root;
		while(can.size() and Vis[can.back()])
			can.pop_back();
		if(!Vis[rt] and can.size()){
			Vis[rt]=1;
			Vis[Fro[rt]=can.back()]=1;
			ans++;
		} 
		else
			Fro[rt]=1;
		for(auto ety:Epty[rt]){
			can.push_back(ety); 
		} 
	} 
	cout<<ans<<'\n';
	for(int i=2;i<=n;i++){
		cout<<Fro[i]<<" ";
	} 
	return 0;
} 
```

---

## 作者：_Cheems (赞：0)

挺厉害一题。

首先题目可以视为：有森林，要将其它树逐个合并到 $1$ 所在树上，求最大匹配？记这些树为 $T_1\dots T_m$，$T_1$ 是 $1$ 所在的树。

然后考虑通过贪心解决，注意我们不反悔，$T_1$ 的匹配边一旦确认就不改变，所以要注意后效性。设想一下合并 $T_1,T_i$，记将它们合并在一起的边是 $E$，对 $E$ 是否是匹配边进行讨论：假如不是，那么 $T_1,T_i$ 保持原有匹配方案即可；否则，则要求两者原有方案中，$E$ 的两端点不可是匹配点。

于是，在合并过程中，只要关心 $T_1$ 还未匹配的点的数量就好了。记 $T_1$ 最大匹配为 $ans$，未匹配点数 $cnt=|T_1|-2\times ans$。可以发现，无论 $E$ 是不是匹配边，都应该选择 $T_i$ 满足条件的匹配方案中最大的一种。这是因为假如我相较于最大方案少选 $k$ 条边，那么目的肯定是让 $cnt$ 变大 $2k$，然后为后续合并提供匹配点，在理想情况下，有 $2k$ 棵树与这些匹配点相连，提供 $2k$ 条边，所以贡献为 $k$（一开始少选了 $k$ 条）。可是这 $2k$ 棵树可以互相匹配，产生 $k$ 对匹配。两者没有区别，而且我还不能保证一定有 $2k$ 棵树用来匹配，所以直接用最大方案即可。

再来考虑 $E$ 是否是匹配边，显然 $cnt=0$ 时 $E$ 必然不是。

否则，记 $T_i$ 中的最大匹配为 $ans_0$，则钦定其根非匹配点的最大匹配 $ans_1$ 满足 $0\le ans_0-ans_1\le 1$。那么若 $ans_1<ans_0$，没有必要选择 $E$，因为合并后最大匹配相同（$cnt$ 也相同）。反之，选择 $E$ 会比不选的最大匹配多 $1$，但同时 $cnt$ 少 $2$，类似于必选最大方案的证明，同样可证选择 $E$ 是更优的。

综上，我们得出了合并的法则，对于 $T_i$，记 $cnt_0,cnt_1$ 分别为 $ans_0,ans_1$ 的未匹配点数：

* 若 $ans_0=ans_1$ 且 $cnt>0$：$E$ 的另一端为 $T_1$ 任意未匹配点，$E$ 为匹配边。然后 $ans\gets ans+ans_1+1$，$cnt\gets cnt+cnt_1-2$。

* 否则：$E$ 的另一端可为 $T_1$ 任意一点。$ans\gets ans+ans_0$，$cnt\gets cnt+cnt_0$。

现在考虑合并顺序。贪心或 dp 预处理出 $ans_0,ans_1$，称 $ans_0=ans_1$ 的是一类树，反之为二类树。二类树莫得选择，先把它们合并到 $T_1$ 上攒攒 $cnt$；然后显然按 $cnt_1$ 从大到小合并进 $T_1$ 即可，因为可以让 $T_1$ 的未匹配点尽量多。

补充一下，树的最大匹配的贪心为：按深度从大到小遍历节点（或是每次剥去叶子），能和父亲匹配就匹配。若最大匹配有多种方案则贪心会优先选根不是匹配点的方案，所以 $ans_0<ans_1$ 只用看贪心时根是否为匹配点即可。

复杂度为 $O(n\log n)$，开销在排序上，当然可以桶排做到线性。
#### 代码
有点丑，慎看。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, pa[N], m, rot[N], ans[N], siz[N], Ans, Siz;
bool vis[N];
vector<int> to[N], node[N], Node;

inline void dfs(int u, int &s, vector<int> &node){
	siz[u] = 1, node.push_back(u);
	for(auto v : to[u]) dfs(v, s, node), siz[u] += siz[v];
	if(!vis[pa[u]] && !vis[u]) vis[u] = vis[pa[u]] = 1, ++s;
}
inline bool pd(int x) {return !vis[x];}
inline bool cmp(int x, int y){
	if(vis[x] == vis[y]) return (siz[x] - 2 * ans[x]) > (siz[y] - 2 * ans[y]);
	return vis[x] < vis[y];
}
int main(){
	cin >> n;
	rot[m = 1] = 1;
	for(int i = 2; i <= n; ++i){
		scanf("%d", &pa[i]), to[pa[i]].push_back(i);
		if(!pa[i]) rot[++m] = i;
	}
	
	vis[0] = 1;
	for(int i = 1, x; i <= m; ++i) x = rot[i], dfs(x, ans[x], node[x]); 
	sort(rot + 2, rot + 1 + m, cmp);
	
	Ans = ans[1], Siz = siz[1]; 
	for(auto i : node[1]) if(!vis[i]) Node.push_back(i);
	for(int i = 2, x; i <= m; ++i){
		x = rot[i];
		if(!vis[x] && 2 * Ans < Siz){
			int y = Node.back(); Node.pop_back();
			pa[x] = y;
			for(auto j : node[x]) if(!vis[j] && j != x) Node.push_back(j);
			Ans += ans[x] + 1, Siz += siz[x];
		}
		else{
			pa[x] = 1;
			for(auto j : node[x]) if(!vis[j]) Node.push_back(j);
			Ans += ans[x], Siz += siz[x];
		}
	}
	cout << Ans << endl;
	for(int i = 2; i <= n; ++i) printf("%d ", pa[i]);
	return 0;
}

```

---

## 作者：H_Kaguya (赞：0)

萌新复健，这个题给人的感觉真的很怪啊。。。  

---

观察题目。树的最大匹配这个性质没有常见转化。  
不妨先考虑一下怎么求这个东西，顺带分析性质。  

$f_{i, 0/1}$ 表示 $i$ 这个节点是否向上与子树外的点匹配，在此情况下 $i$ 这个子树的最大匹配数。  
这就是一个简单的树上 DP 了。观察转移可以得到 $f_{i, 0} = f_{i, 1}$ 或者 $f_{i, 0} = f_{i, 1} + 1$。  
被孤立出来的点最好的情况下也只能产生 $1$ 的贡献。  
所以对于 $f_{i, 0} = f_{i, 1} + 1$ 的情况，让 $i$ 这个点在子树内匹配是不劣的。  

不妨将所有的连通块分为两种。  
一种是 $f_{i, 0} = f_{i, 1} + 1$，记为 $A$。  
另一种是 $f_{i, 0} = f_{i, 1}$，记为 $B$。  
另外，由于根节点不能再向上匹配，将 $1$ 所在的连通块也强制视为 $A$。  

我们发现，会有若干没有匹配的点。称为空点吧。  
所以一个朴素的想法就是，将 $B$ 的根全都连到空点上，即为最优。  

再考虑一个小问题，如果 $B$ 的数量大于空点呢。  
另外，$B$ 连通块内部也会产生空点。但限制是我们的链接不能成环。  

现在定义一个 $val$ 值，$val(i)$ 表示 $i$ 所在的子树内的空点个数。  
同时，目前只考虑由 $A$ 类型的树贡献的空点。  

当我们把一个 $val(i) > 0$ 的 $B$ 类型的树连到空点上时，$i$ 这棵树也就变成了 $A$ 的一部分，从而贡献出来自己的空点。  
所以这种情况下空点数量不减。  

只有当我们剩下的 $B$ 都是 $val = 0$ 的时候才可能出现没有空点的情况。  
直接连成一条链即可，贡献为数量的一半。  

其它的无关紧要的边全都连到 $1$ 上即可。  
以及，注意特判 $A$ 类连通块内一个空点都没有的情况。  
随便找个 $B$ 连通块，把根也当成空点就行了。

由于懒，实现的时候按着 $val$ 排了个序。  
~~但是真的跑的很快诶。~~  
其实只要把 $val = 0$ 的挑出来即可。  
复杂度 $O(n log n)$ 或者可以做到 $O(n)$。  

贴代码~
```cpp
#include <algorithm>
#include <stdio.h>
#include <vector>
#define sz 100005
using namespace std;
int n, ans;
vector<int> head[sz];
vector<int> root, del, undel, waste;
int fa[sz], dp[sz][2], siz[sz];
int read();
void dfs(int);
void redfs(int);
bool cmp(const int&, const int&);
int main()
{
	n = read(); root.push_back(1);
	for (int i = 2; i <= n; ++i)
	{
		fa[i] = read();
		if (fa[i] == 0)
			root.push_back(i);
		else
			head[fa[i]].push_back(i);
	}
	for (int i : root)
	{
		dfs(i); ans += dp[i][0];
		if (i == 1 || dp[i][0] == dp[i][1] + 1)
			del.push_back(i);
		else
			undel.push_back(i);
	}
	sort(undel.begin(), undel.end(), cmp);
	for (int i : del)
		redfs(i);
	if (dp[1][0] == dp[1][1])
		waste.push_back(1);
	if (waste.size() == 0 && undel.size())
	{
	    waste.push_back(undel.back());
	    redfs(undel.back());
	    undel.pop_back();
	}
	while (undel.size())
	{
		if (waste.size() == 0)
		{
			ans += undel.size() / 2;
			for (int i = 0; i < undel.size() - 1; ++i)
				fa[undel[i]] = undel[i + 1];
			break;
		}
		fa[undel.back()] = waste.back();
		waste.pop_back();
		redfs(undel.back());
		undel.pop_back(); ++ans;
	}
	printf ("%d\n", ans);
	for (int i = 2; i <= n; ++i)
		printf ("%d ", max(fa[i], 1));
	return 0;
}

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0') c = getchar();
	do {
		x = x * 10 + (c & 15);
		c = getchar();
	}while (c >= '0');
	return x;
}

void dfs(int a)
{
	int sum = 0, add = 0;
	siz[a] = 1;
	for (int i : head[a])
	{
		dfs(i); siz[a] += siz[i];
		sum += dp[i][0];
		add |= (dp[i][0] == dp[i][1]);
	}
	dp[a][1] = sum;
	dp[a][0] = sum + add;
}

void redfs(int a)
{
	bool add = (dp[a][0] == dp[a][1]);
	for (int i : head[a])
	{
		redfs(i);
		if (dp[i][0] == dp[i][1])
		{
			if (add)
				waste.push_back(i);
			add = true;
		}
	}
}

bool cmp(const int &a, const int &b)
{
	return siz[a] - dp[a][0] * 2 < siz[b] - dp[b][0] * 2;
}

```

---

