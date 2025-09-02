# Military Problem

## 题目描述

在这个问题中你需要帮助伯兰（？？我没找到有Berland这个国家）军队组织他们的指挥系统

伯兰军队中一共有n个军官。第一个官员是军队的指挥官，他并没有任何上级。其他的军官都有且只有一个直接的上级。如果一个军官a是军官b的上级，那么你也可以说军官b就是军官a的下属

如果满足下列条件，那么军官x就是军官y的下属（直接或非直接）：

1.y是x的直接上级 2.x的直接上级是y的下属

举个例子，下图的官员3的下属有:5,6,7,8,9

所以，在伯兰军队的结构中，除了指挥官，其他人都是指挥官的下属

形式上的，让我们把伯兰军队看成一棵拥有n个节点的树，树的节点u就代表了军官u。根（即一号节点）就相当于指挥官

伯兰战争部门命令你对q个查询给出答案。这q个查询会以（ui，ki）的形式给出，ui代表了某个军官，ki是正整数。你需要输出，编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

要处理第i个查询，想象一下ui的命令如何我下达到ui的下属。这里使用了典型的DFS（深度优先搜索）算法。

假设现在的军官是a，他要下达一个命令。a军官选择一个军官b——还没有收到这个命令的直接下属（即在树上的一个孩子）。如果有许多这样的直接下属，那么A选择编号最小的那一个。A军官向B军官发出命令。之后，B使用完全相同的方式将命令扩展到它的子树。在B完成命令后，军官A再次选择下一个直接下属（使用相同的策略）。当军官A不能选择任何还没有接到命令的直接下属时，军官A下达命令完成。

让我们看一下下面这个例子（看下面的图）：

如果军官1下达了命令，军官们收到命令的顺序是：1,2,3,5,6,8,7,9,4

如果军官3下达了命令，军官们收到命令的顺序是：3,5,6,8,7,9

如果军官7下达了命令，军官们收到命令的顺序是：7,9

如果军官9下达了命令，军官们收到命令的顺序是：9

你应当分开处理这些查询。一个查询不会影响其他查询的结果。

## 样例 #1

### 输入

```
9 6
1 1 1 3 5 3 5 7
3 1
1 5
3 4
7 3
1 8
1 9
```

### 输出

```
3
6
8
-1
9
4
```

# 题解

## 作者：Anguei (赞：8)

这题题目描述挺生动有趣的，所以题面很长。提取一下信息，就是先序遍历树。

看一眼数据范围，妈耶，二十万，暴力做肯定 T 飞了！想打暴力？难道你是王逸松嘛？

对于多次询问的题目，一般都要先预处理，再询问，做到 $O(1)$ 或 $O(logN)$ 级别。怎么预处理呢？

首先，我们要知道这么一个结论：**一棵树的子树的先序遍历结果是整棵树的先序遍历结果的子串**。有了这个结论，就可以先预处理出整棵树的先序排列，在每次询问时回答子串。

对于输入数据，建图连**有向**边，很简单吧。

连边之后，深搜先序遍历该树，顺便预处理出每个节点的子树大小、每个节点时第几个遍历到的、第 $time$ 次遍历到的节点是哪个。

对于每次询问，先判断是否能走通。判断方法是该节点子树大小是否足够大。

综上：**预处理时间复杂度 $O(n)$，每个回答时间复杂度 $O(1)$，总时间复杂度 $O(n + q)$，空间复杂度 $O(n)$。**

强烈推荐不写 `using namespace std;`，可以毫无顾忌地定义名为 `size`、`time` 这样的变量。

```cpp
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 200000 + 5;

struct Edge
{
    int to;
    Edge() = default;
    Edge(int _to) : to(_to) {}
};

int n, q, time = 0;
int fa[N], when[N], id[N], size[N];
bool vis[N];
std::vector<Edge> g[N]; // 向量存图，可好用了

void dfs(int now)
{
    when[now] = ++time; // 记录什么时候遍历到的
    id[time] = now; // 此时遍历到哪个点
    size[now] = 1; // 初始化子树大小
    for (auto &e : g[now]) // C++11 可好用了
    { 
        int to = e.to;
        if (!vis[to])
        {
            vis[to] = true;
            dfs(to);
            size[now] += size[to]; // 更新子树大小
        }
    }
}

int main()
{
#ifdef yyfLocal
	// freopen 可好用了：不仅可以免去复制粘贴，还能清晰看到程序的输出
    freopen("testdata.txt", "r", stdin); 
#endif
	// 输入有些大，必须加速
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr); 
    
    std::cin >> n >> q;
    fa[1] = 0; // 根节点没爹
    for (int i = 2; i <= n; ++i)
    {
        std::cin >> fa[i]; // 记录爹是谁
        g[fa[i]].emplace_back(Edge(i)); // 从爹到儿子连有向边
    }

    dfs(1); // 先序遍历，并预处理

    while (q--)
    {
        int u, k;
        std::cin >> u >> k;
        std::cout << (k <= size[u] ? id[when[u] + k - 1] : -1) << std::endl;
    }
}
```

鸣谢：@Sooke 的指导。

---

## 作者：jr_zch (赞：5)

# [Military Problem](https://www.luogu.com.cn/problem/CF1006E)
## by [jr_zch](https://www.luogu.com.cn/blog/jr-zch-code-garden/) 博客食用更佳喵~
## Part 1：题目大意 
给你一颗有 $n~(2 \leq n \leq 2 \times 10^5)$ 个结点的树，有 $q~(1 \leq q \leq 2 \times 10^5)$ 个询问，每个询问有两个数 $u$ 和 $k$，要求输出以 $u$ 为根的子树的前序遍历的第 $k$ 个节点的编号。
## Part 2：解题思路
### $O(n + q)$：正解如下
容易想到一颗子树的前序遍历在整棵树的前序遍历中是连续的。

那么可以用一遍 `dfs` 预处理出来前序遍历 $sor$ 和每个数在前序遍历中的位置 $pre$ 以及子树大小 $siz$，最后在询问时就可以 $O(1)$ 直接输出了。
#### tips：
* 输出的时候编号要**减一**，即 `pre[u]+val-1`。

## Part 3：Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+7;
int n,m,x,u,val,cnt;
int sor[maxn],pre[maxn],siz[maxn];
vector<int> e[maxn];

void dfs(int fa,int u){
	siz[u]=1,sor[++cnt]=u,pre[u]=cnt;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		dfs(u,v),siz[u]+=siz[v];
	}
	return ;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		e[x].push_back(i);
	}
	dfs(0,1);
	while(m--){
		scanf("%d%d",&u,&val);
		if(siz[u]<val){
			printf("-1\n");
			continue;
		}
		printf("%d\n",sor[pre[u]+val-1]);
	}
	return 0;
} 
```
## Thanks for your reading

---

## 作者：The_foolishest_OIer (赞：2)

DFS 序板子题。

前置芝士：[DFS 序](https://oi-wiki.org/graph/dfs/)

首先用 DFS 遍历出 DFS 序，在遍历之前，要先给节点编号排序（题目所说）。


```cpp
void dfs (int u,int f){
	dfn[u] = ++vist; // 表示节点 u 的 DFS 序编号
	rdfn[vist] = u; // 表示 DFS 序编号为 vist 的节点编号
	sz[u] = 1; // 表示节点 u 的子树大小（含自己）
	for (auto v : g[u]){
		if (v == f) continue;
		dfs(v,u);
		sz[u] += sz[v];
	}
}
```

记录 $sz_i$ 是方便的判断出编号 $u$ 的军官所下达的命令能否传到第 $k$ 个人，因为这个军官的指令无法传到上级（他的父节点）。

$rdfn_i$ 是为了方便地找到 DFS 序编号为 $i$ 的节点编号，所以答案就是 $rdfn_{dfn_u + k - 1}$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
int n,q,vist;
int dfn[N],rdfn[N],sz[N];
vector <int> g[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void dfs (int u,int f){
	dfn[u] = ++vist;
	rdfn[vist] = u;
	sz[u] = 1;
	for (auto v : g[u]){
		if (v == f) continue;
		dfs(v,u);
		sz[u] += sz[v];
	}
}
signed main(){
	close();
	cin >> n >> q;
	for (int u = 2 ; u <= n ; u++){
		int v;
		cin >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1 ; i <= n ; i++)
		sort(g[i].begin(),g[i].end());
	dfs(1,0);
	for (int i = 1 ; i <= q ; i++){
		int u,k;
		cin >> u >> k;
		if (k > sz[u]) cout << -1 << endl; // 判断是否合法
		else cout << rdfn[dfn[u] + k - 1] << endl; // 算上自己！！！
	}
	return 0;
}
```

---

## 作者：lianchanghua (赞：2)

#### 题目大意

给你两个数，$n$ 和 $q$，分别表示，$n$ 个点，$q$ 次询问。

接着给你 $n-1$ 个数，每个数 $p_i$ 表示编号为 $i$ 的结点的父节点为 $p_i$。

最后询问 $q$ 次，每行两个数，表示询问从结点 $u$ 开始，到 结点 $v$ 结束，经过了几个结点？

#### 思路

一道十分基础的 dfs 序板子题。

当然，直接每次询问时做一次的 dfs 的时间复杂度肯定会超时，我们可以先做一个预处理。

先用一个数组记录 dfs 序，再用一个数组记录每个结点的子树大小，通过这个，来判断是否能传到。

最后输出答案即可。

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,q,num;
int ans[N],cnt[N],siz[N];
bool vis[N];
vector<int>g[N];
void dfs(int u){ 
//	cout<<u<<"\n";
	siz[u]++;
	for(auto v:g[u]){
		if(!vis[v]){
			vis[v]=1;
			ans[++num]=v;
			dfs(v);
			siz[u]+=siz[v];
		}
	}
} 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		g[x].push_back(i);
	}
	ans[++num]=1;
	dfs(1);
	for(int i=1;i<=num;i++)cnt[ans[i]]=i;
	while(q--){
		int u,k;
		cin>>u>>k;
		if(k>siz[u])cout<<-1<<"\n";
		else		cout<<ans[cnt[u]+k-1]<<"\n";
	}
	
	return 0;
}
```

---

## 作者：mondayrain (赞：1)

# CF1006E Military Problem 题解。

~~终于发现了一到没题解的水题。~~

juruo 的第一篇题解 qwq。

[题目传送门。](https://www.luogu.com.cn/problem/CF1006E)

大概意思就是求 $u$ 的子树的 dfs 序的第 $k$ 个是啥。

首先，一颗树的子树的 dfs 序一定是这颗树的 dfs 序的连续的一段。

举个栗子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1006E/4e341fb3dc019defd152d300119e23ac2a1ee48a.png)

这颗树的 dfs 序是：$[1 , 2 , 3 , 5 , 6 , 8 , 7 , 9 , 4]$。

节点 $3$ 的 dfs 序是：$[3 , 5 , 6 , 8 , 7 , 9]$，对应这颗树的 dfs 序的第 $3 \sim 8$ 个。

所以这题就比较好写了，先求每个节点的子树大小，和每个子树对应整颗树的 dfs 序的区间，再求这个区间的第 $k$ 个就 ok 了。

~~3,2,1 上代码。~~

```cpp
#include <bits/stdc++.h>
using namespace std;

int n , q , a , c[200005] , u , k , pp[200005];
vector <int> ff[200005] , v;
void dfs(int x)
{
    v.push_back(x);
    if(ff[x].size() == 0)
    {
        c[x] = 1;
        return;
    }
    for(auto i : ff[x])
    {
        dfs(i);
        c[x] += c[i];
    }
    c[x] ++;
}
int main()
{
	cin >> n >> q;
	for(int i = 2;i <= n;i ++)
	{
	    cin >> a;
	    ff[a].push_back(i);
	}
	dfs(1);     //把dfs序存到v里，c[i]代表以i为根的子树有多少个节点。
	for(int i = 0;i < v.size();i ++)
	{
	    pp[v[i]] = i;    //节点i在dfs序的第pp[i]个。
	}
	while(q --)
	{
	    cin >> u >> k;
	    if(k > c[u])    //超出区间要特判一下。
	    {
	        cout << "-1\n";
	        continue;
	    }
	    int p = pp[u];
	    cout << v[p + k - 1] << "\n";
	}
	return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface

~~大水题，一道大水题，这题居然没人写 tj~~

# problem

[传送门](https://www.luogu.com.cn/problem/CF1006E)

给你一棵树，多组询问，每次询问问若对一个点的子树跑 dfs，哪个点会被第 $x$ 次访问（重复不计数），若没有 $x$ 个点则输出 `-1`。

# solution

很快想到对整棵树跑 dfs，那么题目转化成求哪个点的 dfs 序是一个点的 dfs 序加上 $x$。

于是这道题就迎刃而解了！

# code

~~早知道你们想看了~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, tot, val[200005], qry[200005], sz[200005];
vector<int> g[200005];
void dfs(int x) {
  val[x] = ++tot;
  qry[tot] = x;
  sz[x] = 1;
  for (int i = 0; i < g[x].size(); i++) {
    dfs(g[x][i]);
    sz[x] += sz[g[x][i]];
  }
}// dfs 求 dfs 序和子树大小
int main() {
  cin >> n >> q;
  for (int i = 2, fa; i <= n; i++) {
    cin >> fa;
    g[fa].push_back(i);
  }
  dfs(1);
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << (sz[x] >= y ? qry[val[x] + y - 1] : -1) << '\n';
  }
  return 0;
}
```

[AC 记录](https://vjudge.net/solution/56828025/MiKDCDTQmS1azYP6iDJs)

---

## 作者：geven (赞：1)

# CF1006E Military Problem 题解
## 题意
给定一颗有 $n \thinspace (2 \leq n \leq 2 \times 10^5)$ 个节点的树，树根为 $1$。

对于每个节点 $i \thinspace (2 \leq i \leq n)$ 都有它的父节点 $p_i$，并且每个节点的子节点都是按从小到大的顺序排列的的。

有 $q \thinspace (1 \leq q \leq 2 \times 10^5)$ 个询问，每次询问都有一个 $u_i,k_i \thinspace (1 \leq u_i,k_i \leq n)$，输出以 $u_i$ 为根的子树的前序遍历中排名为 $k_i$ 的元素。

如果子树中没有 $k_i$ 个节点则输出 $-1$。
## 暴力做法
对于每个询问 $i$ 的 $u_i$，直接在以 $u_i$ 为根的子树中做前序遍历，取第 $k_i$ 个被遍历到的元素作为答案即可。

由于每次遍历都有可能遍历整棵树，所以时间复杂度最坏为 $O(nq)$，会超时。
## 正解
继续在暴力做法上寻找优化方法。

如果我们画图会发现，一棵子树内前序遍历的编号是连续的。

所以我们就可以利用这一性质，在树的前序遍历上做询问。

先对整棵树跑一边前序遍历并将其记录下来。

在询问时，先找到 $u_i$ 在前序遍历中的下标 $o$，再找寻前序遍历中以下标 $o$ 开始的第 $k_i$ 元素的下标 $l$。

最终前序遍历中下标为 $l$ 的元素即为所求答案。

对于输出 $-1$ 的情况，只需要记录一下以 $i \thinspace (1 \leq i \leq n)$ 为根的子树大小 $size_i$。在询问时，判断是否 $size_{u_i} < k_i$ 即可。

由于预处理时间复杂度为 $O(n)$，每次询问时间复杂度为 $O(1)$，所以最终时间复杂度为 $O(n+q)$，可以通过测试。
## 代码
```c++
#include<stdio.h>
#include<vector>
const int N=2e5+5;
std::vector<int> v[N];
int n,m,num[N],cnt,kth[N],size[N];
void build(int u){//预处理
	num[++cnt]=u;//前序遍历编号对应元素
	kth[u]=cnt;//元素对应编号
	size[u]=1;//子树大小
	for(auto son:v[u]) build(son),size[u]+=size[son];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2,x;i<=n;i++) scanf("%d",&x),v[x].emplace_back(i);
	build(1);
	int x,y;
	while(m--){
		scanf("%d%d",&x,&y);
		if(size[x]<y) puts("-1");
		else printf("%d\n",num[kth[x]+y-1]);
	}
	return 0;
}
```

---

## 作者：jgvccc (赞：1)

首先看到二十万的数据范围，直接排除 $O(n^2)$ 算法。

蒟蒻太弱，没有找到 $O(n \log n)$ 的算法。

所以，只剩 $O(n)$ 的了。

因为题目考虑的是DFS序，而 `DFS` 总是在不同的地方做相同的操作,所以可以得出：一个树的子树的DFS序一定包含在这个树的DFS序里。（结论可以在样例解释中得到验证。）

所以可以将以 $1$ 为根节点的树的DFS序存下来，这样所有的询问都可以被 $O(1)$ 解决。与此同时，我们还需要记录每个子树的大小和每个节点是第几个被遍历到的。

其实可以不用变量专门计时，可以用 `vector` ，存值的时候直接 `push_back` 即可。 ~~STL大法好！！！~~

$\Huge Code$

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q,t,u,k;
int s[200001];
int p[200001];
vector<int> v[200001];
vector<int> ans;

int dfs(int cur)
{
	ans.push_back(cur);
	p[cur]=ans.size();//这里可以不用时钟了
	int res=0;
	for(int i=0;i<v[cur].size();i++)
	{
		res+=dfs(v[cur][i]);
	}
	return s[cur]=res+1;
}

signed main()
{
    std::ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=2;i<=n;i++)
    	cin>>t,v[t].push_back(i);
    dfs(1);
    for(int i=1;i<=q;i++)
    {
    	cin>>u>>k;
    	if(s[u]<k) cout<<"-1"<<endl;
    	else cout<<ans[p[u]+k-2]<<endl;
		}
    return 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

## 思路
每一个上级可以把命令传给下级，所以上下级之间建一条单向边。再把整棵树拍平，拍平过程中记录子树大小和节点在拍平后数组中的位置。对于每一次询问，先判断子树大小是否符合要求，再输出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
vector<int>G[N];
int k[N],sum[N],siz[N];
int ans;
int n,q;
int cnt=0;
void dfs(int u,int fa){
	sum[++cnt]=u;
	k[u]=cnt;
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		if(G[u][i]!=fa){
			dfs(G[u][i],u);
			siz[u]+=siz[G[u][i]];
		}
	}
}
signed main(){
	cin>>n>>q;
	for(int i=2;i<=n;i++){
		int p;
		cin>>p;
		G[p].push_back(i);
	}
	dfs(1,-1);
	while(q--){
		int u,q;
		cin>>u>>q;
		if(siz[u]<q) puts("-1");
		else{
			cout<<sum[k[u]+q-1]<<"\n";
		}
	}
	return 0;
} 
```


---

## 作者：nb_jzy (赞：0)

## 题意
给你一颗有 $n$ 个结点且根节点为 $1$ 的树。现在给你一种遍历的方式，每次先访问根节点，之后按**从左到右**的顺序分别访问每棵子树。并询问从第 $u$ 个节点开始，第 $k$ 个被访问到的节点的编号。

## 思路
不难发现，如果这棵树为二叉树，那么这种遍历方式就是**前序遍历**。

我们知道二叉树的前序遍历是按照“中、左、右”的顺序遍历，那么一棵普通的树按这样遍历，编码其实也很简单。
```cpp
void bianli(int p){
	cout<<p<<endl;//先访问根节点
	for(int i=elast[p];i;i=enext[i]){
		reply(ey[i]);//递归访问每棵子树
	}
}
```
知道了遍历方式后，我们便能得出最简单的做法。

每次询问，从 $u$ 节点开始遍历，用一个变量记录次数，第 $k$ 次访问的点即为所求。

但是，请注意 $1\leq n,q\leq 2\times 10^5$。以上做法的时间复杂度显然是 $O(n\times q)$，是肯定超时的。

## 正解

我们知道，这棵树的遍历顺序是固定的。我们假设每次都是由整棵树的根节点出发，第 $t$ 个访问到 $u$ 节点，那么第 $t+k-1$ 个访问的节点，即为所求节点。 

于是，我们可以先遍历整棵树，把每个节点被访问的顺序记录下来，我们设 $order1_i$ 表示第 $i$ 个访问到的节点，$order2_j$ 表示第 $j$ 个节点被访问的顺序。那么答案即为 $order1_{order2_u+k-1}$。显然，预处理 $O(n)$，询问 $O(1)$，总时间复杂度 $O(n+q)$。

对了，还可以统计一下 $i$ 节点为根的树的 $size_i$，如果 $size_u<k$，输出 $-1$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,elast[200005],x,enext[200005],ey[200005],c,u,k,cnt=0,ans=-1,fa[200005];
int order1[200005],order2[200005],tree[200005];
void reply(int p){
	cnt++;
	order1[cnt]=p;//记录order1
	order2[p]=cnt;//记录order2
	for(int i=elast[p];i;i=enext[i]){
		reply(ey[i]);
		tree[p]+=tree[ey[i]];//统计size
	}
	tree[p]++;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		fa[i]=x;
	}
	for(int i=n;i>=2;i--){
		c++;
		x=fa[i];
		enext[c]=elast[x],elast[x]=c,ey[c]=i;
	}//要从左到右遍历子树
	reply(1);//预处理
	for(int i=1;i<=q;i++){
		scanf("%d%d",&u,&k);
		if(k>tree[u]){
			printf("-1\n");
		}
		else{
			printf("%d\n",order1[order2[u]+k-1]);
		}
	}
	return 0;
}

---

## 作者：Asphy7xia (赞：0)

## 题解：CF1006E


[题目传送门：CF1006E](https://www.luogu.com.cn/problem/CF1006E)

[博客食用更佳](https://www.luogu.com.cn/blog/Miracle-Marta0512/solution-cf1006e)
### 题意简述

给定一棵 $n$ 个节点的树和 $q$ 个询问，每次询问有两个参数 $u$ 和 $k$，询问在以 $u$ 为根的子树中从 $u$ 开始从小到大 DFS，第 $k$ 个节点的编号，不存在则输出-1。

### 题目分析

首先询问是在 $u$ 的子树中进行的，我们记以 $u$ 为根的子树大小（其实就是该子树中的节点数）为 $siz_u$，那么无解的情况其实就是 $k > siz_u$。

当 $k \leq siz_u$ 时，说明传递命令的人数足够，此时一定存在解。那么如何快速处理询问呢？我们需要使用一个工具：DFS 序。

如果你之前学过 Tarjan 或树链剖分，那么你应该已经对 DFS 序足够熟悉了。简单来说，DFS 序就是对图进行 DFS 时每个节点进入搜索栈的时间戳（也就是顺序），通常用数组 $dfn$ 来记录。

树上的 DFS 序有几个很有用的性质，如果你从小到大将树划分成一条条树链，并优先搜索编号小的节点，你会发现在同一条链上的节点的 $dfn$ 是连续的（这也正是树链剖分的核心思想）。同时，一棵子树内节点的 $dfn$ 也是连续的，因为在 DFS 时总是先搜索完一棵子树再去搜索另一棵。

借助 DFS 序，我们就能将一棵树映射到平面上的数列，形象地说，就是把树“拍扁”成一个数组。并且，如果以从小到大的优先级进行 DFS，那么得到的 DFS 序就是传递命令的顺序，然后我们就能从初始节点 $u$ 直接跳 $k - 1$ 步跳到答案上，以 $O(1)$ 处理每次询问，总时间复杂度为 $O(n \log n + q)$。

在具体实现时，我们可以用两个数组互相映射每个节点的编号与它的 $dfn$，记得要先将每个节点的出边从小到大排序，以保证 DFS 时的优先级。

###  AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, cnt;
const int N = 200016;
int rk[N], dfn[N], siz[N];

std :: vector <int> pre[N];

inline void Dfs (int u)
{
	dfn[u] = ++cnt;  //记录dfn
	rk[cnt] = u;  //映射dfn与节点的编号
	siz[u] = 1;
	for (int i = 0; i < pre[u].size (); i++)
	{
		int v = pre[u][i];
		Dfs (v);
		siz[u] += siz[v];  //计算子树大小
	}
}

int main(){
	scanf ("%d%d", &n, &q);
	int u, k;
	for (int i = 2; i <= n; i++)
	{
		scanf ("%d", &u);
		pre[u].push_back (i);
	}
	for (int i = 1; i <= n; i++)  sort (pre[i].begin (), pre[i].end ());
	Dfs (1);
	while (q--)
	{
		scanf ("%d%d", &u, &k);
		if (siz[u] < k)  printf ("-1\n");  //无解输出-1
		else  printf ("%d\n", rk[dfn[u] + k - 1]);  //有解就直接跳到答案
	}
	return 0;
}
```

---

## 作者：Parat_rooper (赞：0)

# 题目翻译：
给定一棵 $n$ 个节点的树，其中 $1$ 是根，给出每个节点的父亲。
然后给出 $q$ 个询问，每次询问以$u$ 为根的子树，深度优先遍历中第 $k$ 个节点的编号。
遍历的时候按照节点编号从小到大选择儿子。

# 解题思路：
刚开始做其实没想太多，就一遍 $dfs$ 就好了，但当我提交两次之后，我突然发觉有诈！好吧其实也不算诈

$dfs$部分没有难度， 只要从根遍历一次树， 记录下每个点是第几个访问的就好了

我说的诈就是在输出部分，当时没想清楚，直接输出了 $a_{u + k - 1}$ (a就是记录位置的数组) 而判$-1$我就随便写了一下

想想却惊奇地发现

还要算子树中结点个数！！

实际上，$k$ 是从 $u$ 的位置开始算的 所以第二个点就错了

在 $dfs$ 中稍微再改改

就过了

完整代码：

```cpp

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int kMaxN = 2e5 + 1;

int n, q, a[kMaxN], u, k, shu, f[kMaxN];

struct V
{
  vector<int>e;
  int sum, wei;
}v[kMaxN];

void dfs(int d, int &num)
{
  a[++num] = d;
  v[d].wei = num;
  v[d].sum = 1;
  if (!v[d].e.size()) {
    return;
  }
  for (int i = 0; i < v[d].e.size(); i++) {
    dfs(v[d].e[i], num);
    v[d].sum += v[v[d].e[i]].sum;
  }
}

int main() {
  cin >> n >> q;
  for (int i = 2; i <= n; i++) {
    cin >> shu;
    v[shu].e.push_back(i);
  }
  int m = 0;
  dfs(1, m);
  while (q--) {
    cin >> u >> k;
    if (v[u].sum < k) {
      cout << -1 << endl;
      continue;
    }
    cout << a[v[u].wei + k - 1] << endl;
  }
  return 0;
}              
```



---

## 作者：hater (赞：0)

晚上的模拟赛题 

昨天晚上看到zlw在做

下午做掉了 之后看到老师在做题面 

说刚刚我过了 之后场面一度灰常尴尬

话会正传 

这道题是求以ui为根节点的树做dfs序 第ki个遍历到的节点

（ ui 算第一个被遍历到的 ）

（ dfs序是字典序最小的那个 还不懂看看 ）

暴力的话T飞无疑 

我们先尝试优化暴力 

模拟一下 会发现一下情况

假设 ： 当前节点有三个儿子 ki = 1001 

第一个儿子有1000个儿子 

根据dfs序 暴力会往第一个儿子向下走 

一直到1000之后返回 再走第二个儿子

但是实际上 拥有人脑的我们一眼就看出来 

第一个儿子是不需要遍历 只需要 走第二个节点 

为什么 ？ 我们只需要求ki就好了显然 第一个节点的遍历在1~1000之内

与答案无瓜 

这个剪枝需要预先知道某个节点的后代节点的个数 

可以预先处理出来 

```cpp
#include<bits/stdc++.h>
#define MAX 200005
#define R register 
using namespace std; 
int a[MAX] , n , m , son[MAX] , tot ; 
vector<int> v[MAX] ;  
void dfs( R int x )
{
   son[x] = 1 ; 
   for(R int i=0; i<v[x].size(); i++)
   {
       R int u = v[x][i] ;
       dfs( u ) ;
       son[x] += son[u] ;
   }
}
int Find_It ( R int x , R int dep )
{
   dep -= 1 ; 
   if( !dep ) return x ;
   for(R int i=0; i<v[x].size(); i++)
   {
       R int u = v[x][i] ;
       if( son[u]>=dep ) 
          return Find_It( u , dep ) ;
       dep -= son[u] ;  
   }
}
int main()
{
    int x , y ; 
    ios::sync_with_stdio(false); 
    cin >> n >> m ;
    for(R int i=2; i<=n; i++)
    {
       cin >> x ; 
       v[x].push_back(i) ; 
    }
    dfs(1) ; 
    for(R int i=1; i<=m; i++)
    {
       cin >> x >> y ; 
       if( son[x] < y ) cout << "-1" << endl;
           else cout << Find_It( x , y ) << endl;  
     }
    return 0;
}
```

CF上第三个点就炸飞了 

其实数据做成一条链 这个剪枝就毫无意义 

考虑正解 

当把dfs序存到一个数组里时

设节点在数组中位置为 xi 以它为根节点的节点数为Si （包括根节点）

那么 xi 到 xi+Si-1 都是它的后代节点 

而且遍历顺序与原数组顺序一样 

（这也就是 Anguei 管理员 题解中的 这个结论

 一棵树的子树的先序遍历结果是整棵树的先序遍历结果的子串 ）

代码 ： 

```cpp
#include<bits/stdc++.h>
#define MAX 200005
using namespace std; 
int a[MAX] , n , m , siz[MAX] , dfn[MAX] , tot ; 
vector<int> v[MAX] ;  
void dfs( int x )
{
   a[++tot] = x ; 
   dfn[x] = tot ; 
   siz[x] = 1 ; 
   for(int i=0; i<v[x].size(); i++)
   {
      int u = v[x][i] ;
      dfs( u ) ;
      siz[x] += siz[u] ;
   }
}
int main()
{
   int x , y ; 
   ios::sync_with_stdio(false); 
   cin >> n >> m ;
   for(int i=2; i<=n; i++)
   {
      cin >> x ; 
      v[x].push_back(i) ; 
   }
   dfs(1) ; 
   for(int i=1; i<=m; i++)
   {
      cin >> x >> y ; 
      if( siz[x] < y ) cout << "-1" << endl;
         else cout << a[dfn[x]+y-1] << endl; 
   }
   return 0;
}
```

其实题目真的太水了 

了解树的OIER知道那个结论就是秒切 

~~跟P2146的卸载操作有关联~~ （此句可忽略）

---

## 作者：小闸蟹 (赞：0)

```cpp
// 首先要明确一下，如果按照题意里的每次都DFS一下，肯定会T，而且第二个点就T了，别问我是怎么知道的
// 然后，我们其实只需要DFS一遍，记录下每个节点被DFS访问到的时刻，然后再记录一下一个节点后面能访问到的节点总数，用以判断是否存在u后k个元素
#include <iostream>
#include <vector>
#include <array>

constexpr int MaxN = 200000 + 5;

std::array<std::vector<int>, MaxN> G;
std::array<int, MaxN> DFN{ 0 }, Size{ 0 }, Pos{ 0 };

// DFN[x]: 节点x被DFS访问到的时刻
// Size[x]: 节点x下方有多少个节点（包括它自己）
// Pos[x]: DFS在x时刻访问到的节点编号

int Clock = 0;  // DFS时钟

void DFS(int p)
{
    Size[p] = 1;    // 一开始节点p及其下方节点就只有自己一个
    ++Clock;        // DFS访问时刻加一
    DFN[p] = Clock; // 记录下节点p被访问到的时刻
    Pos[Clock] = p; // 记录下该时刻访问到的是节点p

    for (const auto &q : G[p])  // 遍历p的所有直接相接的子节点
    {
        DFS(q);
        Size[p] += Size[q];     // p下方的节点数等于p的所有子节点下方的节点数之和
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    for (int i = 2; i <= n; ++i)
    {
        int p;
        std::cin >> p;
        G[p].push_back(i);
    }

    DFS(1); // 从根节点进行一遍DFS

    while (q--)
    {
        int u, k;
        std::cin >> u >> k;
        if (Size[u] < k)    // 如果节点u下方的所有节点数都没有k大，那么这个查询是失败的
        {
            std::cout << -1 << std::endl;
        }
        else                // 否则计算出u后k - 1个节点的编号，因为自身也算一个
        {
            std::cout << Pos[DFN[u] + k - 1] << std::endl;
        }
    }

    return 0;
}
```

---

