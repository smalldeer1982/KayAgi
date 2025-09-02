# [ARC175D] LIS on Tree 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc175/tasks/arc175_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の木があります．木の $ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいます．

$ (1,\ldots,N) $ の順列 $ P=(P_1,\ldots,P_N) $ に対し $ f(P) $ を以下で定めます．

- 頂点 $ i\ (1\leq\ i\leq\ N) $ に対し，頂点 $ 1 $ から頂点 $ i $ への単純パスを $ (v_1=1,v_2,\ldots,v_k=i) $ として，$ (P_{v_1},P_{v_2},\ldots,P_{v_k}) $ の最長増加部分列の長さを $ L_i $ とする．$ f(P)\ =\ \sum_{i=1}^N\ L_i $ と定める．
 
整数 $ K $ が与えられます．$ f(P)=K $ を満たす $ (1,\ldots,N) $ の順列 $ P $ が存在するか判定し，存在する場合は一つ示してください．

  最長増加部分列とは 数列の**部分列**とは，数列から $ 0 $ 個以上の要素を取り除いた後，残りの要素を元の順序で連結して得られる数列のことをいいます． 例えば，$ (10,30) $ は $ (10,20,30) $ の部分列ですが，$ (20,10) $ は $ (10,20,30) $ の部分列ではありません．  
 数列の**最長増加部分列**とは，数列の狭義単調増加な部分列の中で列の長さが最大のものを指します．   単純パスとは グラフ $ G $ 上の頂点 $ X,Y $ に対して，頂点列 $ (v_1,v_2,\ \ldots,\ v_k) $ であって， $ v_1=X $, $ v_k=Y $ かつ，$ 1\leq\ i\leq\ k-1 $ に対して $ v_i $ と $ v_{i+1} $ が辺で結ばれているようなものを頂点 $ X $ から頂点 $ Y $ への **ウォーク** と呼びます． さらに，$ v_1,v_2,\ \ldots,\ v_k $ がすべて異なるようなものを頂点 $ X $ から頂点 $ Y $ への **単純パス** (あるいは単に **パス**) と呼びます．

## 说明/提示

### 制約

- 入力される数値は全て整数
- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ K\ \leq\ 10^{11} $
- $ 1\leq\ u_i,v_i\leq\ N $
- 与えられるグラフは木
 
### Sample Explanation 1

$ P=(3,2,1,4,5) $ のとき，$ f(P) $ は以下のように定まります． - 頂点 $ 1 $ から頂点 $ 1 $ への単純パスは $ (1) $ であり，$ (P_1)=(3) $ の最長増加部分列の長さは $ 1 $ である．よって $ L_1\ =\ 1 $ である． - 頂点 $ 1 $ から頂点 $ 2 $ への単純パスは $ (1,2) $ であり，$ (P_1,P_2)=(3,2) $ の最長増加部分列の長さは $ 1 $ である．よって $ L_2\ =\ 1 $ である． - 頂点 $ 1 $ から頂点 $ 3 $ への単純パスは $ (1,2,3) $ であり，$ (P_1,P_2,P_3)=(3,2,1) $ の最長増加部分列の長さは $ 1 $ である．よって $ L_3\ =\ 1 $ である． - 頂点 $ 1 $ から頂点 $ 4 $ への単純パスは $ (1,2,4) $ であり，$ (P_1,P_2,P_4)=(3,2,4) $ の最長増加部分列の長さは $ 2 $ である．よって $ L_4\ =\ 2 $ である． - 頂点 $ 1 $ から頂点 $ 5 $ への単純パスは $ (1,2,4,5) $ であり，$ (P_1,P_2,P_4,P_5)=(3,2,4,5) $ の最長増加部分列の長さは $ 3 $ である．よって $ L_5\ =\ 3 $ である． - 以上より，$ f(P)=1+1+1+2+3=\ 8 $ である． このことから，出力例の $ P $ は $ f(P)=8 $ という条件を満たすことが分かります．この他にも，例えば $ P=(3,2,4,5,1) $ も条件を満たします．

### Sample Explanation 2

$ f(P)\ =\ 21 $ を満たす順列 $ P $ は存在しないことが証明できます．

## 样例 #1

### 输入

```
5 8
1 2
2 3
2 4
4 5```

### 输出

```
Yes
3 2 1 4 5```

## 样例 #2

### 输入

```
7 21
2 1
7 2
5 1
3 7
2 6
3 4```

### 输出

```
No```

## 样例 #3

### 输入

```
8 20
3 1
3 8
7 1
7 5
3 2
6 5
4 7```

### 输出

```
Yes
2 1 3 5 6 8 4 7```

# 题解

## 作者：wosile (赞：4)

首先，判断什么情况无解。记 $s_i$ 为以 $i$ 为根的子树大小，$p_i$ 为 $i$ 的深度（$d_1=1$），显然有 $k<n$ 或 $k>\sum p_i$ 时无解（因为有 $1 \le L_i \le d_i$ 哦）。以下将通过构造说明其他情况（$k \in [n,\sum p_i]$）都有解。

更改点 $i$ 的 $p_i$ 会造成很多点的 $L_j$ 发生变化，所以这不太好考虑。

我们直接假设最终构造中每个点路径上的 LIS 一定是它父节点的 LIS 拼上（或不拼上）自己。这样如果 $i$ 在 $1$ 到 $i$ 的路径的 LIS 上，$i$ 一定也在子树中所有点的 LIS 上，这个点就会对答案 $f(p)$ 造成 $s_i$ 的贡献；否则就造成 $0$ 的贡献。

发现这变成了一个背包问题：我们需要选择若干个节点（$1$ 是必选）使得它们的贡献 $s_i$ 加起来恰好为 $k$。

注意到如果我们把 $s_i$ 按从大到小排序，就有 $s_i\le \sum\limits_{j>i}s_j+1$（因为一个点的子树大小就是它所有的儿子的子树大小和 $+1$，那这个点最大也不过是比它小的所有点都是它的儿子），因此我们从大到小贪心，每次遇到 $k\ge s_i$ 就可以从 $k$ 中减掉 $s_i$，剩下的部分一定可以在后面拼出。

好了，我们已经决定哪些点要造成贡献了，答案该怎么构造呢？

为了保证所有没取到的点一定不造成贡献，我们把所有没取到的点的权值设为比取到的点的权值小，这样就不会拼在已经形成的 LIS 的后面；为了保证没取到的点不会自己形成一段 LIS，我们只要让所有没取到的点的权值都从根往下降序排列就行。同理，既然取到的点要形成 LIS，那么这些点的权值就应该从根往下升序排列。

时间复杂度 $O(n\log n)$，因为有排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k;
int sz[200005];
vector<int>T[200005];
pair<int,int>p[200005];
int n;
void dfs(int x,int fa){
	sz[x]=1;
	for(int v:T[x])if(v!=fa){
		dfs(v,x);
		sz[x]+=sz[v];
	}
	p[x]={-sz[x],x};
}
int vis[200005],ans[200005];
int tot=0;
void dfs0(int x,int fa){
	for(int v:T[x])if(v!=fa)dfs0(v,x);
	if(!vis[x])ans[x]=++tot; // 没取到的点，值较小且降序 
}
void dfs1(int x,int fa){
	if(vis[x])ans[x]=++tot; // 取到的点，值较大且升序 
	for(int v:T[x])if(v!=fa)dfs1(v,x);
}
int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs(1,0);
	ll sum=0;
	for(int i=1;i<=n;i++)sum+=sz[i];
	if(k<n || k>sum){
		printf("No");
		return 0;
	}
	printf("Yes\n");
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)if(k+p[i].first>=0){
		vis[p[i].second]=1;
		k+=p[i].first;
	}
	dfs0(1,0);
	dfs1(1,0);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：lizihan250 (赞：0)

# LIS on Tree 2

## 题意简述

给定一棵树，每个点有互不相同的点权，**点权未知**。已知 $1$ 号节点到各节点路径上所有点的点权组成的序列的最长上升子序列（LIS）的长度之和，求出一种给每个点赋点权的方案，或报告无解。

## 解题思路

为行文方便，下文所有某个节点的 LIS 长度指 $1$ 号点到该点的 LIS 长度。

首先考虑怎么凑出题目要求的 $k$。

由于每个节点的 LIS 长度至少为 $1$，所以，若 $k < n$，直接报告无解即可。下文不考虑该情况。

注意到 $1$ 号点到任意一个非 $1$ 号点的 LIS 的长度是 $1$ 号点到其父亲的 LIS 的长度 $+0$ 或 $+1$，也就是说，在一个节点使得 LIS 长度 $+1$ 一定会导致其子树内的所有结点的 LIS 长度 $+1$，故其总贡献为以该节点为根的子树的大小。不难证明，各节点是否使 LIS 序列增长的选择是独立的，这在后文的构造方案中也能看出。

接着考虑拼凑这些贡献。下证：记以 $u (u \neq 1)$ 为根节点的子树内所有节点的贡献之和为 $f(u)$，则 $f(u)$ 可以取 $0$ 到 $f(u)_{max}$ 之间的任意整数。

考虑用类似数学归纳法的方法证明：

当 $u$ 为叶子节点时，$f(u)$ 显然可以取 $0$ 或 $1$ 中的任意整数，命题成立。

假设对于节点 $u (u \neq 1)$ 的所有儿子 $v$，都有 $f(v)$ 可以取 $0$ 到 $f(v)_{max}$ 之间的任意整数。则有：

- 当 $u$ 不使 LIS 长度增长时，$f(u)$ 可以取 $0$ 到 $\sum \limits_{v \text{ is in the subtree}} f(v)_{max}$ 中的任意整数。
- 当 $u$ 使 LIS 长度增长时，记以 $u$ 为根的子树的大小为 $u_{size}$，则 $f(u)$ 可以取 $u_{size}$ 到 $u_{size} + \sum \limits_{v \text{ is in the subtree}} f(v)_{max}$ 中的任意整数。

而 $\sum \limits_{v \text{ is in the subtree}} f(v)_{max} \ge \sum \limits_{v \text{ is } u \text{'s son}} f(v)_{max} = u_{size} - 1$，故两段可以合并，$f(u)$ 可以取 $0$ 到 $f(u)_{max}$ 之间的任意整数。命题得证。

因此，一个简单的凑出题目所要求的 $k$ 的方案是，先选定 $1$ 号节点增加 LIS 长度（显然），再进行 DFS，若以当前节点为根的子树的大小大于等于 $k$，则将该节点标记为增加 LIS 长度，并让 $k$ 减去以当前节点为根的子树的大小。若进行完 DFS 后，$k$ 仍然大于 $0$，则说明无解。

考虑有解的情况。我们需要找到一种构造方案，使得赋出来的点权与之前我们预设的该点的 LIS 吻合。

构造题要找尽可能简单的构造。什么时候你能一眼瞪出来一个序列的 LIS？一种情况是，这个序列可以被分为若干块，使得每一块的所有数都单调递减，同时，每一块的最大值均小于下一块的最小值。此时，这个序列的 LIS 自然是从每块中选出恰好一个数，其长度也就是分出的块数。

应用该构造，我们将所有点先按照预设的 LIS **从小到大**排序，对于 LIS 相同的，按照深度**从大到小**排序，接着按排出来的顺序从 $1$ 到 $n$ 赋值即可。

时间复杂度 $O(n)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=200000;
vector<vector<int> > adj;
int n;
long long k;
struct node
{
    bool tg;
    int siz,dep,num,p,ans;
}nums[Maxn+10];
bool cmp1(node x,node y){return x.num==y.num?x.dep<y.dep:x.num>y.num;}
bool cmp2(node x,node y){return x.p<y.p;}
void dfs1(int u,int fa)
{
    nums[u].siz=1;
    nums[u].tg=false;
    for(int v:adj[u])
    {
        if(v==fa) continue;
        dfs1(v,u);
        nums[u].siz+=nums[v].siz;
    }
    return;
}
void dfs2(int u,int fa)
{
    if(nums[u].siz<=k)
    {
        k-=nums[u].siz;
        nums[u].tg=true;
    }
    for(int v:adj[u])
    {
        if(v==fa) continue;
        dfs2(v,u);
    }
    return;
}
void dfs3(int u,int fa,int dep,int pre)
{
    nums[u].p=u;
    nums[u].dep=dep+1;
    nums[u].num=pre+nums[u].tg;
    for(int v:adj[u])
    {
        if(v==fa) continue;
        dfs3(v,u,nums[u].dep,nums[u].num);
    }
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    while(cin>>n>>k)
    {
        adj.clear();
        adj.resize(n+5);
        for(int i=1,u,v;i<n;i++)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs1(1,0);
        if(k<n)
        {
            printf("No\n");
            continue;
        }
        dfs2(1,0);
        if(k!=0)
        {
            printf("No\n");
            continue;
        }
        dfs3(1,1,0,0);
        printf("Yes\n");
        sort(nums+1,nums+n+1,cmp1);
        for(int i=1;i<=n;i++)
            nums[i].ans=n-i+1; // 上面排序条件写反了，因此这里是倒着赋值的
        sort(nums+1,nums+n+1,cmp2);
        for(int i=1;i<=n;i++)
            printf("%d ",nums[i].ans);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：ax_by_c (赞：0)

考虑一个点的值与其到根路径上的点的值的相对关系，取最大值可以使 LIS 长度增加一（子树内点的答案都增加一），取比父亲的值小的最大值可以使 LIS 不变（子树内点的答案都不变），而这已经可以覆盖所有情况了。

因此相当于在树上选择一些点，其中根节点必选，使它们的 $sz$ 之和为 $k$。

容易发现能够选出的和为 $[0,\sum sz]$（证明考虑归纳法），因此只要 $k\in[sz_{rt},\sum sz]$ 就有解，dfs 一下就能得出方案。

构造排列可以根据选的点分层，按层从小到大，每一层按深度从大到小即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int N=2e5+5;
int n,de[N],sz[N],a[N],id[N],idx;
ll k,s[N];
vector<int>g[N],nds[N];
void dfs(int u,int fa){
	sz[u]=1;
	for(auto v:g[u]){
		if(v==fa)continue;
		de[v]=de[u]+1;
		dfs(v,u);
		sz[u]+=sz[v];
		s[u]+=s[v];
	}
	s[u]+=sz[u];
}
void ddfs(int u,int fa,ll &x){
	if(x>=sz[u]){
		a[u]=a[fa]+1;
		x-=sz[u];
	}
	else a[u]=a[fa];
	for(auto v:g[u]){
		if(v==fa)continue;
		ddfs(v,u,x);
	}
}
bool cmp(int x,int y){
	return de[x]<de[y];
}
void main(){
	scanf("%d %lld",&n,&k);
	for(int i=1,u,v;i<n;i++){
		scanf("%d %d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	if(k<sz[1]||s[1]<k){
		puts("No");
		return ;
	}
	puts("Yes");
	ddfs(1,0,k);
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+1+n,cmp);
	for(int i=n;i>=1;i--)nds[a[id[i]]].push_back(id[i]);
	for(int i=1;i<=n;i++)for(auto j:nds[i])a[j]=++idx;
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

非常有趣的题目额。

# 正文

题意就是生成 $N$ 的全排列，作为一棵节点数目为 $N$ 的树的权值，然后对于节点 $i$，算出它到 $1$ 的简单路径所经过的节点的点权序列的全长上升子序列长度 $L_i$，目标是使得 $\sum{L_i} = K$。

然后我们考虑一种答案最大化的操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/msknrvms.png)

也就是一个节点的任何儿子的权值都比他的权值大。

然后考虑交换权值来减少 LIS 长度。注意到每当一个数被加入序列时，LIS 长度只会增加 $1$ 或不变。

我们可以钦定一个数集 $S = \{s_1, s_2, \dots, s_k\}$，表示当往数列尾部加入 $P_{s_i}$ 后 LIS 长度增加，那么（令 $w_i$ 为以 $i$ 为根的子树大小）

$$
f(P) = N + \sum_{i = 1}^{k}{w_{s_i}}
$$

问题就相当于要求 $\sum_{i = 1}^{k}{w_{s_i}} = K - N$。于是问题就成了一个子集和问题。但是 SOS DP 的复杂度不能支持，所以考虑贪心地选择 $S$。

我们发现 $w_i$ 具有特殊性质，因为 $w_i$ 必然由其各个儿子的 $w$ 构成。于是我们降序排 $\{w_{2}, w_3, \dots, w_N\}$，逐个累加直至和达到 $K - N$。

求出树上点的这个子集 $S$ 后，我们就可以正常构造答案了（令 $d_i$ 为节点 $i$ 与节点 $1$ 的简单路径距离）：

用一个 $t_i$ 来决定最后的排列。当 $i \in S$，$t_i$ 为 $d_i$；当 $i \not \in S$，$t_i$ 为 $- d_i$，最后按 $t_i$ 升序排并标号。

# 代码

好唐啊，根节点深度搞成 $1$ 了吃了好几发。

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, K;

ll cnt, head[200005];
struct Edge {
	ll nxt, to;
} edge[400005];

void add(ll u, ll v)
{
	++ cnt;
	edge[cnt].nxt = head[u];
	edge[cnt].to = v;
	head[u] = cnt;
}

ll dsum, w[200005], d[200005], res[200005];
struct Node {
	ll val, num;
} sortw[200005], tmp[200005];

bool operator >(Node a, Node b)
{
	return a.val > b.val;
}

bool operator <(Node a, Node b)
{
	return a.val < b.val;
}

void dfs(ll u, ll fa)
{
	w[u] = 1, d[u] = d[fa] + 1ll;
	for(ll i = head[u]; i; i = edge[i].nxt)
	{
		ll v = edge[i].to;
		if(v == fa) continue;
		dfs(v, u);
		w[u] += w[v];
	}
	
	dsum += d[u];
}

signed main()
{
	cin >> N >> K;
	if(K < N)
	{
		puts("No");
		return 0;
	}
	
	for(ll i = 1; i < N; ++ i)
	{
		ll u, v;
		cin >> u >> v;
		add(u, v); add(v, u);
	}
	
	d[0] = -1; dfs(1, 0);
	for(ll i = 1; i <= N; ++ i)
		sortw[i - 1].val = w[i], sortw[i - 1].num = i;
		
	sort(sortw + 1, sortw + N + 1, greater<Node>());
	set<ll> subset_num;
	ll tmpK = K - N;
	for(ll i = 1; i <= N; ++ i)
	{
		if(sortw[i].val > tmpK) continue;
		tmpK -= sortw[i].val;
		subset_num.insert(sortw[i].num);
	}
	
	if(K > N + dsum)
	{
		puts("No");
		return 0;
	}
	
	for(ll i = 1; i <= N; ++ i)
	{
		if(subset_num.count(i)) tmp[i].val = d[i], tmp[i].num = i;
		else tmp[i].val = -d[i], tmp[i].num = i;
	}
	
	sort(tmp + 1, tmp + N + 1, less<Node>());
	for(ll i = 1; i <= N; ++ i)
		res[tmp[i].num] = i;
	
	puts("Yes");
	for(ll i = 1; i <= N; ++ i)
		cout << res[i] << ' ';
		
	puts("");
	return 0;
}

```

---

## 作者：complexly (赞：0)

感觉这题很简单啊，没有蓝吧。

假设 $a_u$ 表示节点 u 的点权， $g_u$ 表示节点 u 对前面形成的最长上升序列产生了贡献。

为了先得到一个合法的答案，先想象一颗 $g$ 全部为 0 的树（答案全部为 0 ）。

首先注意到，$g_u$ 为 $1$ 或 $0$，当 $g_u$ 从 0 变为 1 时，$u$ 的子树的最长上升子序列长度全部会加 1。

所以在每个点上判断一下子树大小是否大于 $k$ ，如果大于，就让 $k$ 减去这个值就可以了

嗯，那怎么填数呢？

把限制加强一下：

- 如果 $g_u$ 为 1 ， $a_u$ 大于 1 到 $fa_u$ 的所有点权
- 如果 $g_u$ 为 0 ， $a_u$ 小于 1 到 $fa_u$ 的所有点权

因为 1 到 $fa_u$ 的 dfs 序小于 u 的 dfs 序

所以再次加强限制:

- 如果 $g_u$ 为 1 。
  $$
  max_{dfn_v < dfn_u} < a_u
  $$
  （ dfs 序小于 u 的 dfs 序 的所有点的点权小于 $a_u$ ）。
- 如果 $g_u$ 为 0 。
  $$
  min_{dfn_v < dfn_u} > a_u
  $$
  （ dfs 序小于 $u$ 的 dfs 序 的所有点的点权大于 $a_u$ ）。

到这里就很简单了，数值从 1 开始，按照 dfs 序倒着填 $g_i = 0$ 的，再顺着填 $g_i = 1$ 的就行了。

时间复杂度 $O(n)$ 。

注意，$g_1$ 必须为 1 （即 $k \ge n$）。

代码如下

```
#include<bits/stdc++.h>
#define f(i , l , r) for(register int i = (l);i <= (r);i ++)
#define d(i , l , r) for(register int i = (r);i >= (l);i --)
using namespace std;
const int N = 2e5 + 10;
int n , cnt;
long long k;
struct edge{
    int u , v , nxt;
}e[N<<1];
int head[N] , tot;
void add(int u,int v){e[++tot] = {u , v , head[u]} , head[u] = tot;}
int sz[N] , g[N] , need[N] , ans[N];
inline void init(int u,int father){
    sz[u] = 1;
    // cout << u << "\n";
    for(register int i = head[u];i;i = e[i].nxt){
        int v = e[i].v;
        if(v != father)init(v , u) , sz[u] += sz[v];
    }
    return ;
}
inline void dfs(int u,int father){
    if(k >= sz[u])k -= sz[u] , g[u] = 1;
    need[++cnt] = u;
    for(register int i = head[u];i;i = e[i].nxt){
        int v = e[i].v;
        if(v != father)dfs(v , u);
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    cin >> n >> k;
    f(i , 2 , n){
        int u , v;cin >> u >> v;
        add(u , v) , add(v , u);
    }
    if(k < n)return cout << "No\n" , 0;
    init(1 , 0) , dfs(1 , 0);
    if(k)return cout << "No\n" , 0;
    int t = 1;
    d(i , 1 , n)if(!g[need[i]])ans[need[i]] = t ++;
    f(i , 1 , n)if(g[need[i]])ans[need[i]] = t ++;
    cout << "Yes\n";
    f(i , 1 , n)cout << ans[i] << " ";cout << "\n";
}
```

60ms，并没有怎么卡常。

---

