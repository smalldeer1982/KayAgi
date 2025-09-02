# [AGC014D] Black and White Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc014/tasks/agc014_d

$ N $ 頂点からなる木があり、頂点には $ 1 $ から $ N $ の番号がついています。 また、 $ N-1 $ 本の辺の内、$ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

はじめ、どの頂点にも色がついていません。

高橋君と青木君は各頂点に色を塗ってゲームをします。ゲームでは高橋君から始めて交互に以下の操作を繰り返します。

- 頂点の中から、まだ色がついていない頂点を一つ選ぶ。
- その後、高橋君ならその頂点を白色に、青木君ならその頂点を黒色に塗る。

次にすべての頂点に色がついた後、高橋君と青木君は以下の手順を一度だけ行います。

- 黒色の頂点に隣接している白色の頂点をすべて黒色に塗りかえる。

ただし、この操作はある頂点から順に操作を行っていくわけではなく、当該頂点すべてに対して同時に行うことに注意してください。

最終的に白色の頂点が残っていれば高橋君の勝ちであり、全て黒色の頂点であれば青木君の勝ちです。 二人が最適に行動したとき、どちらが勝つか求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ a_i,b_i\ ≦\ N $
- $ a_i\ ≠\ b_i $
- 入力で与えられるグラフは木である。

### Sample Explanation 1

ゲームの一例を示す。 - 高橋君がまず頂点 $ 2 $ を白色に塗る。 - その後、青木君が頂点 $ 1 $ を黒色に塗る。 - 最後に高橋君が頂点 $ 3 $ を白色に塗る。 このように進んだ場合、最後の操作で頂点 $ 1,2,3 $ の色がそれぞれ黒、黒、白となるので、高橋君の勝ちとなる。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
First```

## 样例 #2

### 输入

```
4
1 2
2 3
2 4```

### 输出

```
First```

## 样例 #3

### 输入

```
6
1 2
2 3
3 4
2 5
5 6```

### 输出

```
Second```

# 题解

## 作者：小粉兔 (赞：18)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC014.html](https://www.cnblogs.com/PinkRabbit/p/AGC014.html)。

考虑一个叶子，先手把这个叶子连接的那个点染白，则后手必须染黑那个叶子，否则下一步先手即可把叶子染白赢得游戏。

考虑如果有一个点连接了两个叶子，那么先手先把它染白，后手就因为无法顾及两个叶子而输掉游戏。

假设已经不存在这种情况，考虑连续的三个点 $a, b, c$，考虑一个时刻 $a, c$ 周围的除了 $b$ 之外的点全部染白，此时先手将 $b$ 染白。

那么同上，后手将会输掉游戏。我们此时考虑以 $b$ 为根时 $a, c$ 的子树，如果除了 $a, c$ 本身外均有偶数个点，可以证明后手必败。

这是因为先手可以每次找到 $a$ 或 $c$ 子树中深度最大的叶子节点，把它的双亲结点染白，逼迫后手染黑那个叶子。

此时完全等价于把这两个被染色的点从树中删去，用数学归纳法可知最终会删成 $a, c$ 无孩子节点的情况，将 $b$ 染白赢得游戏。

也就是说：如果存在一个节点，以它为根时存在至少两个子树方向上的点数为奇数则先手必胜。

显然如果 $N$ 为奇数，任取一个连接叶子节点的点，必存在另一个点数为奇数的子树，这是因为除了它和叶子还有奇数个点。

所以 $N$ 为奇数时先手必胜。如果 $N$ 为偶数？我们可以做一次 DFS 来计算是否存在这样的点，如果存在也是先手必胜。

如果不存在呢？我并不清楚为何不存在时先手必败，此时我直接把代码提交上去就 AC 了（我当时在 virtual participating）。

赛后查看题解，发现我的 DP 过程（请看代码）竟然等价于求树上是否存在一个完美匹配，即选取一半的边覆盖所有点。

此时思路就清晰了，如果存在完美匹配，先手每染白一个点，后手就染黑它的匹配点，很显然每个点最终都会被染黑。

```cpp
#include <cstdio>
#include <vector>

const int MN = 100005;

int N;
std::vector<int> G[MN];

int Ans, siz[MN];
void DFS(int u, int p) {
	siz[u] = 1;
	int s = 0;
	for (int v : G[u]) if (v != p) {
		DFS(v, u);
		s += siz[v];
		siz[u] ^= siz[v]; 
	}
	if (s >= 2) Ans = 1;
}

int main() {
	scanf("%d", &N);
	if (N & 1) return puts("First"), 0;
	for (int i = 1, x, y; i < N; ++i) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1, 0);
	puts(Ans ? "First" : "Second");
	return 0;
}
```

---

## 作者：pufanyi (赞：13)

问题显然就是青木不能让任意一个白点旁边没有黑点。

如果该树有完美匹配，那么显然是后手赢。因为不管先手选什么，后手只要选先手对应的点就可以。

于是我们就来考虑没有完美匹配的情况。

最特殊的应该是叶子节点，因为只有一个点与它相邻。如果叶子节点是白点，那么叶子节点的“父亲”必须是黑点；而如果叶子是黑点，那么叶子节点的“父亲”必须是白点。这里的“父亲”是指它相邻的点。

我们考虑先手先任意一个叶子节点的“父亲”，那后手必须跟着选叶子。然后我们发现我们可以把这两个点删掉，并不会影响结果。

于是我们可以每次这样删下去。由于这棵树没有完美匹配，最后肯定是一些零散的点。而此时先手选择其中的任意一个点即可。

我们考虑如何求出是否存在完美匹配。

我们可以考虑直接模拟上面的游戏过程，因为如果先手按这个策略没有赢，那么肯定没有完美匹配。

我们任选一个节点为根进行`dfs`，将儿子处理完后如果这个点还没被删，那么把它就已经变成叶子节点了，把它和它父亲一起删掉。

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxn = 100005;

struct Edge
{
    int to, nxt;
} e[maxn << 1];

int first[maxn];

inline void add_edge(int from, int to)
{
    static int cnt = 0;
    e[++cnt].nxt = first[from];
    first[from] = cnt;
    e[cnt].to = to;
    e[++cnt].nxt = first[to];
    first[to] = cnt;
    e[cnt].to = from;
}

bool shan[maxn];
int n;

inline void dfs(int now, int fa)
{
    for(int i = first[now]; i; i = e[i].nxt)
    {
        register int to = e[i].to;
        if(to != fa)
            dfs(to, now);
    }
    if(!shan[now])
    {
        if(shan[fa])
        {
            puts("First");
            exit(0);
        }
        shan[now] = shan[fa] = true;
    }
}

int main()
{
    shan[0] = true;
    scanf("%d", &n);
    for(int i = 1, f, t; i < n; ++i)
    {
        scanf("%d%d", &f, &t);
        add_edge(f, t);
    }
    dfs(1, 0);
    puts("Second");
    return 0;
}
```

---

## 作者：w9095 (赞：3)

[AT_agc014_d [AGC014D] Black and White Tree](https://www.luogu.com.cn/problem/AT_agc014_d)

我们充分发扬人类智慧。

不难发现如果树根确定的情况下，先手会从叶子的父亲开始填，如果填到某两棵子树的白点中刚好是同一个节点，我们就可以直接填这个节点，这样两个儿子中至少有一个被完全白点阻隔，先手获胜。

考虑到树根是不确定的，我们枚举树根，每次暴力判定。注意到枚举度数为 $1$ 的点是不优的，于是取度数大于 $1$ 的前 $100$ 个点枚举就过了。

如果之后被卡了就该位随机选度数大于 $1$ 的点，应该还是能够过的。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt;
}e[300000];
long long n,u,v,h[300000],ind[300000],flag=0,cnt=0;
void add_edge(long long u,long long v)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
	ind[u]++; 
}

long long dfs(long long x,long long fa)
{
	long long ans=0;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=fa)ans+=dfs(e[i].v,x);
	if(ans>1)flag=1;
	return (ans!=1);
}

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++)scanf("%lld%lld",&u,&v),add_edge(u,v),add_edge(v,u);
	long long num=0;
	for(int i=1;i<=n;i++)
	    if(ind[i]>1)
	       {
		   num++,dfs(i,0);
		   if(num>100)break;
	       }
	if(flag)printf("First\n");
	else printf("Second\n");
    return 0;
}
```

---

## 作者：WhisperingWillow (赞：3)

[Black and White Tree](https://www.luogu.com.cn/problem/AT_agc014_d)。

看题解区都写的好麻烦。

如果一个叶子节点的父亲被染白，则其必然是黑色点，相当于删去这两个节点，这样显然是最优的。

不断执行操作。

如果还有点没有被删除，则先手获胜。

否则后手获胜。

[Submission](https://atcoder.jp/contests/agc014/submissions/46487013)

---

## 作者：Gaode_Sean (赞：2)

#### 题意

- 有一棵无色的树，每次先手找一个点染黑，后手找一个点染白。

- 当整棵树染完后，如果存在一个黑点和白点不相连，先手胜，否则后手胜。

#### 解法

- 对于一个叶结点 $v$，若先手将其染黑，对手一定会染白其父亲 $u$。

- 对于一个叶结点 $v$ 的父亲 $u$，先手将其染黑，对手一定会将 $v$ 染白，如果此时父节点 $u$ 还有其他叶结点儿子，将其染黑，一定先手胜。

- 考虑每次从树的叶结点开始删除其和其父结点，如果出现孤立点，先手胜，反之后手胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int fst[N],nxt[N],tal[N],tot;
int T,n,v[N];
void add(int x,int y){
	tal[++tot]=y,nxt[tot]=fst[x],fst[x]=tot;
}
void dfs(int x,int fas){
	for(int i=fst[x];i;i=nxt[i]){
		int y=tal[i];
		if(y==fas)	continue;
		dfs(y,x);
	} 
	for(int i=fst[x];i;i=nxt[i]){
		int y=tal[i];
		if(y==fas)	continue;
		if(!v[y]){
			v[y]=v[x]=1;
			break;
		}
	}
}
int main(){
	T=1;
	while(T--){
		tot=0;
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++)	fst[i]=nxt[i]=tal[i]=v[i]=0;
		for(int i=1;i<n;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y),add(y,x);
		}
		dfs(1,0); 
		bool flag=true;
		for(int i=1;i<=n;i++)	if(!v[i]){
			puts("First");
			flag=false;
			break;
		}
		if(flag)	puts("Second");
	}
	return 0;
}
```

---

## 作者：activeO (赞：2)

## 思路

问题是后手不能让任意一个白点旁边没有黑点。

先想如果在链上要怎么做，列举一下：

- $ n=1 $ First
- $ n=2 $ Second
- $ n=3 $ First
- $ n=4 $ Second

先手染白第二个，后手必然染第一个，状态转为 $ n-2 $，判断奇偶性就可以了（别的一样）。

再放到树上想一下：

如果这棵树有完美匹配的话，先手必输。
否则，先手会把一个叶子节点的父亲染白，后手就被迫把这个叶子节点染黑。那么又转移到了一个新的树上，且一样是原来的先手取然后后手取。所以我们可以把这一组节点看做空节点，也就是 0，否则就是 1。这样一组一组的删掉，可以直接模拟上面的过程。如果出现 1

       	    /  \
               1    1 
               
的这种情况，先手必赢，就可以提前结束啦。且如果最后的结果 $ res\geq 1 $ 的话也是先手必赢，否则后手赢。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！！！

using namespace std;

const int maxn=1e5+10;
vector<int> tree[maxn];

int dfs(int x,int f){
	int ret=0;
	for(int i=0;i<tree[x].size();i++){
		int v=tree[x][i];
		if(v!=f){
			int r=dfs(v,x);
			if(r>1) return r;
			ret+=r;
		}
	}
	return (ret^1);
}

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	
	if(dfs(1,0)>=1) puts("First");
	else puts("Second");
	
	return 0;
}


```


---

## 作者：Aw顿顿 (赞：2)

一道很有意思的题目嗷。

----------

## 题意

给你一棵起初无色的树，两人轮流染色。先手选择一个点染白，后手选择一个点染黑。如果能够保证染色的最终结果存在某个白点的周围没有黑点，那么先手胜利，反之后手胜利。

## 分析

完美匹配是指在一棵树中，结点两两对应的匹配能够覆盖所有的结点。如果一棵树存在完美匹配，那么后手一定会赢，因为无论先手选了哪一个点，后手都可以选择他的匹配点即可。

那么如果没有完美匹配，我们就要考虑特殊结点了。从叶子结点出发，因为叶子结点能够对应的结点有且仅有它的直接父亲。若他是白色，则为了让后手赢他的父亲一定是黑色，反之亦然。

显然在一棵结构确定而形态不确定的树，我们只能认为度为 $1$ 的结点是叶子结点，且唯一与其相连的结点是它的直接父亲。先手去染白一个叶子的直接父亲，这样后手必定要去染黑这个叶子，那这两个点就可以扔掉了，这并不会干扰到答案的计算。

因此如此删除许多结点之后，只剩下了一些互不连通的点，这时候先手选择其中的任意一个点就可以获得游戏的胜利。

## 代码

实际上我们实现是容易的。

首先读入并且使用邻接表存边（实际上是链式前向星），接着我们随意选一个结点（不妨选择 $1$ 结点）进行深搜。搜到叶子结点之后如果存在叶子结点被删除而父亲结点未被删除，则先手胜利。否则我们就把这两个点一起删除进行下一轮操作。

注意这是棵树，连的是无向边。代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
struct Edge{int v,nxt;}e[N*2];
int head[N],cnt,n;
void add(int u,int v){
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}bool del[N];
void dfs(int now,int fa){
    for(int i=head[now];i;i=e[i].nxt)
        if(e[i].v!=fa)dfs(e[i].v,now);
    if(!del[now]){
        if(del[fa]){
            puts("First");
            exit(0);
        }del[now]=1;del[fa]=1;
    }
}int main(){
    del[0]=1;
    cin>>n;
    for(int i=1;i<n;i++){
    	int x,y;
    	cin>>x>>y;
    	add(x,y);add(y,x);
	}dfs(1,0);
    puts("Second");
    return 0;
}
```

---

## 作者：OtterZ (赞：1)

# 1. 题意
有两个人，一个人先禁用一个节点，另一个人再取一个节点，循环往复，直到没有节点既没被取也没被禁用，若一个被禁用的节点没有与任何被取走的节点相邻，先手胜，否则后手胜，问哪一方有必胜策略。
# 2.重要结论
当树存在匹配包含所有点时时，不管先手怎么禁用节点，后手选与其匹配的点即可获胜。  
当树不存在匹配包含所有点时时，先手可以构造方法使至少一个没有参与匹配的点没有与任何被选的点相邻。
# 3.树形动规
接下来通过树形动规测验树是否存在匹配。  
设 $dp_{v,0}$ 为是否存在匹配涵盖 $v$ 子树内除 $v$ 节点的其他节点，$dp_{v,1}$ 为是否存在匹配涵盖 $v$ 子树内所有节点，得到 $v$ 与当前搜到的子节点 $u$ 的转移方程：

$$
dp_{v,1} = (dp_{v,1} \land dp_{u,1}) \lor (dp_{v,0} \land dp_{u,0})\\
dp_{v,0} = dp_{v,0} \land dp_{u,1}
$$

最终得到答案 $dp_{root,1}$。  
如上算法是 $\operatorname{O}(N)$ 的。
# 4.注意事项
动规时，先转移 $dp_{v,1}$ 或存原先的 $dp_{v,0}$，以防用转移后的 $dp_{v,0}$ 转移错误答案。
# 5.上代码

```cpp
#include<cstdio>
#include<vector>
using namespace std;
int n,u,v;
bool dp[100009][2];
vector<int>e[100009];
void srh(int v,int fa){
	dp[v][0] = true;
	for(int i = 0; i < e[v].size(); i ++){
		if(e[v][i] == fa)
			continue;
		srh(e[v][i],v);
		dp[v][1] = (dp[v][0] && dp[e[v][i]][0]) || (dp[v][1] && dp[e[v][i]][1]);
		dp[v][0] = dp[v][0] && dp[e[v][i]][1];
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1; i < n; i ++){
		scanf("%d %d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	srh(1,0);
	printf("%s\n",dp[1][1] ? "Second" : "First");
	return 0;
}
```

---

## 作者：Sampson_YW (赞：1)

孩子第一次做出博弈论呜呜呜，之前打 CF 连[这题](https://www.luogu.com.cn/problem/CF1747C)都不会做。。

但是本题解偏向猜结论，没有很多严谨的证明（

我们先定一个度数大于 $1$ 的节点为根，减少之后的讨论。

考虑先手会赢的情况：

1. 选择一个点染白后，它的未染色儿子个数多于一个，且这些儿子的儿子全染白（叶子也当作是儿子全染白，下面将儿子全染白的点称为 B 点）。
2. 根节点没被染色，且根节点的儿子全被染白，且当前是先手操作。

容易想到一种先手牵制后手的方法：找到一个 B 点，把它的父亲染白，那么后手必须染黑这个节点。因为先手之后染白这个节点就会赢。**因此后手一定会染黑 B 点。**

大胆猜测，如果先手能赢，那么先手染色的方案固定，且总是能牵制住后手（让后手一直染黑 B 点）。

考虑这样一种方案：

- 若一个点的儿子中存在 B 点，那么将这个点染白。
- 若儿子全是白点，这个点就成为 B 点。

这样做看似会出现一些不是白点也不是 B 点的点，称为废点。废点可能导致我们不会进行上面任何一个操作。但是思考一下会发现是不存在的。

因为一个废点需要满足它的儿子中只有白点和废点，且必有废点（否则它就是 B 点）。那么选一个废儿子进行废链剖分。由于叶子节点一定是 B 点，而链剖分的最底端一定是叶子，那么产生矛盾，所以不存在废点。因此对于每个节点都会进行上述两种操作的其中一种。

注意到 B 点的数量一定不少于白点的数量（因为一个白点的儿子至少有一个 B 点），因此先手用这种方案一定是能牵制住后手的。所以在对一个节点染色时只需要考虑先手有没有必要染。

模拟这种方案，并在染色途中判断先手是否赢了即可。[code](https://atcoder.jp/contests/agc014/submissions/47556752)

---

## 作者：ezoixx130 (赞：1)

### 题目地址：
[AGC014D](https://agc014.contest.atcoder.jp/tasks/agc014_d)

### 题意：

给你一棵树，两个人轮流在上面染色，每个人每次会把一个节点染成黑色或者白色，当所有点都被染了色后，如果存在一个白色的节点，它的所有相邻的节点均为白色，则先手胜，否则后手胜，问先手必胜还是后手必胜。

### 题解：

考场上想出了一种乱搞做法：

显然若有一个节点，它有两个以上的儿子是叶子节点，那么先手染这个点为白色就必胜，我们称这种点为必胜节点。

然后我们考虑这样的情况：

若一个节点有且仅有一个儿子，且这个儿子还是叶子节点，那么先手一定可以在这个节点上染上白色，后手就一定要在叶子节点上染黑色。于是这两个节点就对我们的答案没有影响了，可以删去，因为这个点一定是白色节点。

当我们把这种点全部删掉后，我们在剩下的树上找是否存在必胜节点，若存在则先手必胜，若不存在则后手必胜。

注意如果删完点后只剩根那也是先手必胜。

 

关于删点的方法，我们只要找到size=2的节点，打个标记即可。

 

不过好像是完美匹配的题？跑网络流？Dinic分层图飞快？

代码：

```
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 1000001
 
int size[MAXN],cnt;
vector<int> edge[MAXN];
 
void addedge(int u,int v)
{
	edge[u].push_back(v);
}
 
void dfs1(int now,int father)
{
	size[now]=1;
	for(int i=0;i<edge[now].size();++i)
	{
		if(edge[now][i]==father)continue;
		dfs1(edge[now][i],now);
		if(size[edge[now][i]]==2)size[edge[now][i]]=-1;
		else size[now]+=size[edge[now][i]];
	}
}
 
void dfs2(int now,int father)
{
	++cnt;
	int num=0;
	for(int i=0;i<edge[now].size();++i)
	{
		if(edge[now][i]==father)continue;
		if(size[edge[now][i]]==1){++num;}
		if(size[edge[now][i]]!=-1)dfs2(edge[now][i],now);
	}
	if(num>=2){puts("First");exit(0);}
}
 
int main()
{
	int n;
	scanf("%d",&n);	
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	if(cnt==1)puts("First");else puts("Second");
}
```

---

## 作者：ezoiLZH (赞：1)

## 题解：
首先想到如果有一个点的儿子中包含两个或以上个叶子结点，先手必胜，否则先手必败。

发现这样不行，其实先手可以牵制对手，选一个叶子结点的父亲，那么后手就必须下在这个叶子结点上。

这相当于把这两个节点都删掉了，从而可以将树的形态变为必胜的状态。

我实在是太笨了，以为只有在一条链的情况下才能删，其实只要凑够两个节点就能删，最后没删完就说明先手必胜，否则后手必胜。

## CODE：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int tot=0,h[100005];
int n,x,y,siz[100005],f[100005];
struct Edge{
	int x,next;
}e[200005];

inline void add_edge(int x,int y){
	e[++tot].x=y;
	e[tot].next=h[x],h[x]=tot;
}

bool dfs(int x,int fa){
	siz[x]=1;
	int cnt=0;
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==fa)continue;
		if(dfs(e[i].x,x))return true;
		if(siz[e[i].x]){
			cnt++,siz[x]=0;
			if(cnt==2)return true;
		}
	}
	return false;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	printf(dfs(1,0)||siz[1]?"First":"Second");
}
```

---

## 作者：Mistletoes (赞：1)

**每次找到所有叶子节点，把它们的父亲染白，自己染黑。这个时候染完的叶子节点及其父亲节点对树的其他部分已无影响** ,可以直接删掉。

那么只需要判断树的其他部分是否有先手必胜策略即可。用递归遍历。

边界条件：若树为单一节点先手必胜。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e5+5;
struct Edge{
    int v,nxt;
}e[N<<1];
int n,flag[N],cnt,head[N];
void add(int x,int y){
    e[++cnt].v=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
bool dfs(int x,int fa){
    flag[x]=1;
    int tot=0;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        if(dfs(v,x)) return true;
        if(flag[v]){
            tot++;flag[x]=0;
            if(tot==2)return true;
        }
    }
    return false;
}
int main(){
    scanf("%d",&n);
    int x,y;
    for(int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    printf(dfs(1,0)||flag[1]?"First":"Second");
    return 0;
}
```


---

## 作者：tuliwei (赞：1)

### 思路：贪心

每次找到所有叶子节点，把它们的父亲染白，自己染黑。如果一个点被染白了两次，那么先手胜利。染完之后把染了色的点去掉，原树会变成森林。这时如果某棵树size=1，那么先手胜利。若所有点染完先手未胜，后手胜。 

我是用一种类似拓扑的bfs方法做的，写起来有点恶心。。  
### 代码：
```cpp
#include <bits/stdc++.h>
//#define inf 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define inv(x) Power(x, mod - 2)
#define fi first
#define se second
#define MP make_pair
#define PB push_back
#define N 100005

using namespace std;
typedef pair<int,int> Pair;
typedef long long ll;

const long double Pi = 3.14159265358979323846l;
const int mod = 1e9 + 7;
inline int add(int x, int y) { return (x += y) - (x >= mod ? mod : 0); }
inline void inc(int &x, int y) { (x += y) -= (x >= mod ? mod : 0); }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
inline int Power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = mul(res, x);
		x = mul(x, x), y >>= 1;
	} return res;
}

template <class T> inline T	input() {
	T x; char ch; while (!isdigit(ch = getchar()));
	for (x = ch ^ 48; isdigit(ch = getchar()); x = x * 10 + (ch ^ 48));
	return x;
}

template <class T> inline void chkmin(T &x, T &y) { x = x < y ? x : y; }
template <class T> inline void chkmax(T &x, T &y) { x = x > y ? x : y; }

struct {
	inline operator int () { return input<int>(); }
	inline operator long long () { return input<long long>(); }
	template <class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

int n, tot;
bool vis[N];
int cnt[N], du[N];
vector<int> T[N];
queue<int> que, tmp;

inline void AddEdge(int x, int y) {
	T[x].push_back(y);
	T[y].push_back(x);
	++du[x], ++du[y];
}

void Win() {
	puts("First");
	exit(0);
}

int main() {
	read(n), tot = n;
	for (int i = 1; i < n; ++i) AddEdge(read, read);

	for (int i = 1; i <= n; ++i) if (du[i] == 1) que.push(i);

	while (tot) {
		for (int i = 1, sz = que.size(); i <= sz; ++i)
			vis[que.front()] = true, que.push(que.front()), que.pop();

		while (!que.empty()) {
			int u = que.front(); que.pop();
			vis[u] = true, --tot;
			for (int v : T[u])
				if (!vis[v]) {
					tmp.push(v);
					++cnt[v];
				}
		}

		for (int i = 1, sz = tmp.size(); i <= sz; ++i)
			vis[tmp.front()] = true, tmp.push(tmp.front()), tmp.pop();

		while (!tmp.empty()) {
			int u = tmp.front(); tmp.pop(), --tot;
			if (cnt[u] > 1) Win();
			for (int v : T[u])
				if (!vis[v]) {
					if (!--du[v]) Win();
					if (du[v] == 1) que.push(v);
				}
		}
	}

	puts("Second");
	return 0;
}


---

## 作者：CodingOIer (赞：0)

## [AGC014D] Black and White Tree 题解

### 思路分析

后手需要让每一个百点旁边起码有一个黑点。

考虑特殊的叶子情况。

显然叶子只有一个与之相连的节点，令叶子记为 $x$，与叶子节点相连的唯一节点记为 $y$。

当然如果上一步不满足（只剩下一个点了），显然就是先手必胜了。

不难发现先手最优的情况为选择 $y$。

如果先选择 $x$，则后手会选 $y$，这时所有与 $y$ 相邻的节点涂白都没有意义了。

也就是说至少丢失 $1$ 个节点。

而如果选择 $y$，则后手必须选择 $x$。

如果不选择 $x$ 则下一步先手选择 $x$ 那么 $x$ 周围将没有黑点。

显然此方案不会对除了这两个点以外的节点产生影响，所以仅仅会丢失 $1$ 个节点。

显然选择 $y$ 优于选择 $x$。

那么我们以任意顺序模拟，如果剩下了节点则先手一定能染出一个孤立的白色。

否则染不出来，后手胜利。

### 代码实现

一次简单的 dfs 即可。

```cpp
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n;
bool kill[MaxN];
std::vector<int> g[MaxN];
void dfs(int u, int f)
{
    int w = 0;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u);
        if (!kill[v])
        {
            w = v;
        }
    }
    if (w != 0)
    {
        kill[u] = true;
        kill[w] = true;
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (!kill[i])
        {
            printf("First\n");
            return 0;
        }
    }
    printf("Second\n");
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

如果一个白点只和白点相邻则 Alice 胜否则 Bob 胜。

考虑 Alice 会不会染叶子，如果染的话 Bob 直接染它的父亲，Alice 就失去了主动权。

假设 Alice 染一个连向多于一个叶子的节点呢？他一定会获胜。

判断完以上后，Alice 每次选择一个叶子的父亲，这样就可以逼迫 Bob 选择这个叶子，

这些染色的点扔掉以后，继续博弈。可以发现：这个过程相当于贪心的进行完美匹配。

所以如果这棵树存在完美匹配则后手必胜否则先手必胜。

---

## 作者：strcmp (赞：0)

不妨考虑度数只有 $1$ 的叶子结点的性质。

首先，一个结点 $u$，下面挂了**多于一个**的叶子结点，那么先手（高桥）必胜，因为他可以先染白 $u$，此时后手（青木）最多染黑 $u$ 的一个儿子叶子结点，先手直接把剩下的某一个叶子结点染白即可。此时白色叶子结点的父亲是白色的，必然不可能被染为次黑。

那么对于所有的结点，如果先手不是必胜的，必然都不存在多于一个的叶子结点。

这继续启发我们考虑一个 $(fa_u,\,u)$ 对，满足 $(fa_u,\,u)$ 都没有额外的儿子。那么我们发现先手可以先染白 $fa_u$，此时后手只能染黑 $u$，问题转化为一个结点少两个的树。

那么我们就可以每次删掉一对满足条件的 $(fa_u,\,u)$，容易发现如果无法找出来满足条件的对，要么 $n$ 已经等于 $1$，要么存在多于一个叶子结点挂在某个结点上，先手必胜。

如果树被删得只剩下根节点了，那么必然根结点的所有儿子都是白色的，根结点也染成白色即可，先手必胜。因此当 $n$ 为奇数先手必胜。

否则我们注意到上述操作能删完整棵树等价于这棵树是否有没有完美匹配，当然这是显然的，先手染白一个结点，后手染黑对应的匹配结点即可。

得到我们的条件：树存在完美匹配则后手必胜，否则先手必胜。

因此找完美匹配可以建二分图跑 Dinic，时间复杂度正确但明显是大炮打蚊子。树的完美匹配可以树形 dp 在 $\Theta(n)$ 的复杂度内解决。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double ld;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 2e5 + 10;
constexpr int mod = 1e9 + 7; 
struct edge { int to, nxt; } nd[maxn]; int h[maxn], cnt = 0, n;
inline void add(int u, int v) { nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; }
int dfs(int u, int f) {
	//dfs 的返回值是代表 u 能删成一个结点，还是能删完，分别是 1/0
	int d = 0;
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (v == f) continue;
		d += dfs(v, u);
	}
	if (d > 1) puts("First"), exit(0);
	else return d ^ 1;
}
int main() {
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), add(x, y), add(y, x);
	if (n & 1) puts("First");
	else dfs(1, 0), puts("Second");
	return 0;
}
```

---

## 作者：AzusidNya (赞：0)

### [AGC014D] Black and White Tree 题解

如果一个黑色节点和一个白色节点相邻，那么我们说黑色节点控制了白色节点。

那么后手的胜利条件即为所有白色节点都被控制。现在考虑后手的策略。

首先如果这棵树有完美匹配（即用一半的边覆盖整棵树），那么显然后手可以在先手染白一个点后直接染黑其匹配点，这样所有白点都会被控制。

因此只考虑这棵树没有完美匹配的情况。

考虑一个叶子节点。如果叶子节点的父亲节点被染成了白色，那么这个叶子节点一定要染成黑色，否则叶子节点将永远无法被控制。

现在假设进行了一次如上操作，两个点 $u,v$ 被分别染成了黑色和白色。因为白点已经被控制住了，并且黑点无法再控制其他节点，所以这两个节点对游戏已经没有任何影响了，可以删去。

这样持续进行下去，每次删除两个点。因为这棵树没有完美匹配，所以最后肯定剩下很多零散的点。

那么这个时候先手随便取一个零散的点，后手找不到任意一个点去控制住这个点，因此先手胜。

因此我们得到结论：**后手必胜的充要条件是这棵树有完美匹配**。

接下来考虑如何判定一棵树是否有完美匹配。

首先如果这棵树的点数是奇数，那么显然没有。

我们尝试递归构造出完美匹配。

在一个完美匹配中，任意一棵子树只有两种状态，要么这棵子树本身是完美匹配，要么这棵子树删去根节点后是完美匹配，并且根节点与父亲节点连边形成匹配。边界为，空树是完美匹配，而叶子节点则需要和父亲节点匹配。

假设现在考虑到一个点 $u$，有如下情况：

1. 如果 $u$ 的子节点中有两棵子树状态为需要和父亲节点匹配来形成完美匹配，那么这无法做到，因此这棵树没有完美匹配。

2. 如果 $u$ 的子结点中有一棵子树需要和父亲节点连边，那么将 $u$ 和这一子树匹配。其他子树已经是完美匹配了，因此此时这棵子树形成完美匹配。

3. 如果 $u$ 的子节点全部都是完美匹配，那么 $u$ 需要和父亲节点匹配来形成完美匹配。

按这种条件已经可以进行 dp 判定了。但是还能够再简洁些。

我们考虑每个子树的大小。容易发现需要和父亲节点匹配的子树大小一定是奇数，而本身形成完美匹配的子树大小一定是偶数。那么这三个条件等价于判断子节点的子树大小的奇偶性，如果一个节点的子结点中有两棵子树的大小为奇数则不可行。

至此完成了完美匹配的判定，根据完美匹配的判定判断先手必胜或必败即可。

#### code

```cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
//#define int long long
using namespace std;
int n;
vector<int> edge[100005];
int siz[100005];
bool flg = true;
int dfs(int u, int fa) {
	siz[u] = 1;
	bool chk = 0;
	for (int v : edge[u]) {
		if (v == fa) continue;
		dfs(v, u);
		if (chk == 1 && (siz[v] & 1))
			flg = false;
		chk = chk || (siz[v] & 1), siz[u] += siz[v];
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	if (n & 1) {
		cout << "First";
		return 0;
	}
	for (int i = 1, u, v; i < n; i ++)
		cin >> u >> v, edge[u].push_back(v), edge[v].push_back(u);
	dfs(1, 0);
	if (flg == false) cout << "First";
	else cout << "Second";
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

先来考虑特殊情况：

如果在链上，先手可以先将一个未染色的叶子结点的父亲染白，那么后手就不得不把这个叶子结点染黑，因为如果不这么做，下一步先手将叶子结点染白就赢了。

当树的结点个数为奇数时，先手一定可以让局面变为如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/zi58m4io.png)

反之后手只要每次都按上述策略染色，先手必败。

拓展到一般情况。每次我们都按上述策略去模拟先后手的染色。相当于每次从树中删去一个叶子结点和其父亲。如果删完后存在孤立点，下一回合先手将它染白，先手就获胜了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct edge{
	int to,nxt;
}e[N<<2];
int n,cnt,head[N];
bool vis[N],flag; 
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int f){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u);
	}
	if(!vis[u]){
		if(vis[f]){
			flag=1;return;
		}
		vis[u]=1;vis[f]=1;
	}
}
int main(){
	//freopen("std.in","r",stdin);
	n=read();
	for(int i=1;i<n;i++){
		int u,v;u=read();v=read();
		add(u,v);add(v,u);
	}
	vis[0]=1;
	dfs(1,0);
	puts(flag?"First":"Second");
	return 0;
}


```


---

## 作者：Sktic (赞：0)

[AT2376 [AGC014D] Black and White Tree ](https://www.luogu.com.cn/problem/AT2376)

$2022:10:11$ 修复部分 $\text{Latex}$。

容易发现，题目其实让我们求的先手获胜条件是染色完全后至少存在一个白点使得它的左右相邻点都是白点。



对于这种题目，我们可以考虑从简单到特殊。先从样例 $1$ 时的 $n=3$ 下手，发现此时的树必为一条链，那么当先手下了链中间的点，即当这个点连着两个相邻点时，后手只能涂黑其中一个点，那先手必然能再下一个点满足获胜要求。



因此我们可以发现，如果存在一个点使得它连着两个叶子，那么先手下到它就必胜。因为后手只能来得及将其中一个点染黑，那么先手就可以染色另一个点。



接下来我们可以考虑一般情况。先手没有两个叶子的点可下，那么为了最优，就会下有一个叶子节点的点。此时后手为了防止先手赢，必定会在叶子节点染色，那么这两个节点就都可以删掉。若删的时候出现了连着两个叶子的点，那么就是先手胜。否则，当且仅当这棵树存在完美匹配的时候，后手胜利。



于是我们考虑采用 $\text{dfs}$ 来求出这棵树是否存在完美匹配。我们仿照先手的策略，然后依次删点，若删后存在一些零散的点，那么说明树没有完美匹配，即先手必胜。若不存在，则后手必胜。



时间复杂度 $O(n)$ 。



AC Code:

```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef long long ll;
vector<int>e[maxn<<1];
int vis[maxn];
int op;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void dfs(int u,int f)
{
	for(int i=0;i<e[u].size();i++)
	{
		if(e[u][i]==f)
			continue;
		dfs(e[u][i],u);
	}
	if(vis[u]==0)
	{
		if(vis[f]==1)
		{
			op=1;
			return; 
		}
		vis[u]=vis[f]=1;
	}
	return;
}
int main()
{
	vis[0]=1;
	int n;
	n=read();
	for(int i=1;i<n;i++)
	{
		int u,v;
		u=read();v=read();
		e[u].push_back(v);
		e[v].push_back(u); 
	}
	dfs(1,0);
	if(op==1)
		printf("First");
	else
		printf("Second");
	return 0;
}
```







---

