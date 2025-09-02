# [ARC116E] Spread of Information

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc116/tasks/arc116_e

高橋国には $ N $ 箇所の町があり、それぞれ町 $ 1 $ 、町 $ 2 $、 $ \ldots $ 、町 $ N $ と名付けられています。 この国には $ N-1 $ 本の道があり、 $ i $ 本目の道は 町 $ u_i $ と町 $ v_i $ を双方向に結びます。任意の $ 2 $ つの町 $ a $, $ b $ について、いくつかの道を通ることにより、町 $ a $ から町 $ b $ へ移動することが出来ます。

高橋国王は、ある情報を国土全体に流そうとしています。多忙な高橋国王は、 $ K $ 箇所までの町にしか直接情報を伝達することが出来ません。

高橋国王の情報伝達が終わった瞬間を時刻 $ 0 $ とします。 $ t\ =\ 1,\ 2,\ 3,\ \cdots $ について、以下の現象が発生します。

- $ 1 $ 本の道で直接結ばれている町の組 $ a $, $ b $ について、 時刻 $ t-0.5 $ に町 $ a $ に情報が伝わっており、町 $ b $ に情報が伝わっていないとき、 時刻 $ t $ に町 $ b $ にも情報が伝わる。

高橋国王は $ K $ 箇所の連絡先を適切に選択し、全ての町に情報が伝わるまでに掛かる時間を最小化しようと考えています。最小値を答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ K\ <\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 任意の $ 2 $ つの町 $ a $, $ b $ について、いくつかの道を通ることにより、町 $ a $ から町 $ b $ へ移動することが出来る。

### Sample Explanation 1

高橋国王が町 $ 2 $ と町 $ 4 $ に直接情報を伝達した場合、町 $ 1 $ 、 $ \ldots $ 、町$ 5 $ に初めて情報が伝わる時刻は、それぞれ $ 1,\ 0,\ 1,\ 0,\ 1 $ となります。このとき、 国土全体に情報が広まるのは時刻 $ 1 $ であり、これが達成可能な最小値であることが証明出来ます。

## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
4 5```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1
1 2
1 3
1 4
5 4```

### 输出

```
2```

## 样例 #3

### 输入

```
20 3
2 15
6 5
12 1
7 9
17 2
15 5
2 4
17 16
12 2
8 17
17 19
18 11
20 8
20 3
13 9
11 10
11 20
14 8
11 7```

### 输出

```
3```

# 题解

## 作者：hzoi_Shadow (赞：15)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc116_e)

# 前置知识

[二分答案](https://oi-wiki.org/basic/binary/#%E4%BA%8C%E5%88%86%E7%AD%94%E6%A1%88) | [树形 DP](https://oi-wiki.org/dp/tree/)

# 解法

答案显然具有单调性，考虑二分答案。

设当前二分出的答案为 $mid$，则等价于覆盖距离为 $mid$ 的情况下进行选点。

做法同 [luogu P3942 将军令](https://www.luogu.com.cn/problem/P3942) ，考虑进行贪心，对于深度最深的叶节点将选择的点放在边界时，即取 $mid$ 级祖先时，覆盖的范围一定最大。

设 $f_{x}$ 表示 $x$ 到以 $x$ 为根的子树内最远的没被覆盖的点的距离，$g_{x}$ 表示 $x$ 到以 $x$ 为根的子树内最近被选的点的距离，状态转移方程为 $\begin{cases} f_{x}=\max\limits_{y \in Son(x)}\{ f_{y}+1 \} \\ g_{x}=\min\limits_{y \in Son(x)}\{ g_{y}+1 \}\end{cases}$，

当 $g_{x}>mid$ 时以 $x$ 为根的子树内所选的点覆盖不到自己，需要祖先节点进行覆盖，此时需要统计自己的贡献，即 $f_{x}=\max(f_{x},0)$；当 $f_{x}+g_{x} \le mid$ 时以 $x$ 为根的子树内所选的点就能覆盖整棵子树，令 $f_{x}=- \infty$；当 $f_{x}=mid$ 说明 $x$ 必须被选，令 $f_{x}=- \infty,g_{x}=0$，选择点数加一。

特判下根节点没有被覆盖的情况。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
    int nxt,to;
}e[400010];
int head[400010],f[400010],g[400010],cnt=0,sum=0;
void add(int u,int v)
{
    cnt++;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
void dfs(int x,int fa,int k)
{
	f[x]=-0x3f3f3f3f;
	g[x]=0x3f3f3f3f;
	for(int i=head[x];i!=0;i=e[i].nxt)
	{
		if(e[i].to!=fa)
		{
			dfs(e[i].to,x,k);
			f[x]=max(f[x],f[e[i].to]+1);
			g[x]=min(g[x],g[e[i].to]+1);
		}
	}
	if(g[x]>k)
	{
		f[x]=max(f[x],0);
	}
	if(f[x]+g[x]<=k)
	{
		f[x]=-0x3f3f3f3f;
	}
	if(f[x]==k)
	{
		f[x]=-0x3f3f3f3f;
		g[x]=0;
		sum++;
	}
}
bool check(int mid,int k)
{
	sum=0;
	dfs(1,0,mid);
	sum+=(f[1]>=0);
	return sum<=k;	
}
int main()
{
	int n,k,u,v,l=0,r,mid,ans=0,i;
	cin>>n>>k;
	r=n;
	for(i=1;i<=n-1;i++)
	{
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(mid,k)==true)
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	cout<<ans<<endl;
    return 0;
}
```

# 后记

多倍经验：[luogu P3942 将军令](https://www.luogu.com.cn/problem/P3942) | [luogu P2279 [HNOI2003] 消防局的设立](https://www.luogu.com.cn/problem/P2279) | [luogu P2899 [USACO08JAN] Cell Phone Network G](https://www.luogu.com.cn/problem/P2899) | [UVA1218 完美的服务 Perfect Service](https://www.luogu.com.cn/problem/UVA1218) | [luogu P3523 [POI2011] DYN-Dynamite](https://www.luogu.com.cn/problem/P3523)

---

## 作者：qfpjm (赞：10)

# 题目大意

> 一个城市是由 $n$ 个点 $n-1$ 条边组成的树，一个点的危险度是指这个点到任意一个消防站的距离的最小值。现在要选择 $k$ 个点建立消防站，使得所有点的危险度的最大值最小，求这个值。（$1\leq k<n\leq 2\times 10^5$）

# 题解

- 面对这样的数据规模，我们只能考虑 $O(n),O(n\log n),O(n\sqrt{n})$ 的做法，第三种不太可能，所以考虑前两种。看到"最大值最小"，我们就会想到二分，从而考虑第二种时间复杂度的做法。

- 二分，我们枚举什么？显然是 $n$，我们可以枚举每个消防站的覆盖范围，从而锁定答案。

- 这样，问题就转化成了一个树上半径为 $k$ 最小覆盖问题。但是这题的 $k$ 有些大，但是我们需要 $O(n)$ 的时间复杂度。所以，需要做一些优化。

- 普通的树上半径为 $k$ 最小覆盖问题，我们每次找到深度最大且没被覆盖的节点，并在其第 $k$ 级祖先上设立消防站，这样可以证明是最优的。

- 这题我们还是考虑从下往上贪心，但我们从每个子树的根节点考虑。我们枚举到一个覆盖范围 $mid$，我们判断如果这颗子树的根节点 $u$，到这棵最深的节点 $v$ 的距离为 $mid$，那么我们就在 $u$ 上设立消防站，当然，意义同 $k$ 很小的最小半径覆盖问题，但是并不是从下往上跳，而是由上考虑下。

### 实现方式：

- 我们用回溯思想，用儿子计算这颗子树的根的答案。我们用 $a_u$ 表示$u$ 离 $u$ 这棵子树中的消防站的距离，$b_u$ 表示 $u$ 到 $u$ 这棵子树中没被覆盖的点得距离。

- $sonu_i$ 表示这棵子树的孩子，记 $p=a_{sonu_i} - 1,q=b_{sonu_i}+1$。分三种情况考虑：

1. 如果 $p\ge q$，那么说明不能被覆盖的点可以被其它点覆盖，自然也能覆盖 $u$，所以我们更新 $b_u=-1,a_u=p$。

1. 如果 $q<mid$，那么我们不覆盖节点 $u$，在该节点设立消防站不会使答案更优。更新 $a_u=0,b_u=q$。

1. 否则，我们需要在 $u$ 上设立消防站，更新 $a_u=mid,b_u=-1$，计数 $num+1$。

- 最后还要判断一下整棵树的根节点。

- 覆盖半径 $mid$ 最终得到的答案 $num$ 如果大于 $k$，那么说明这个覆盖半径太小了，需要调大；如果小于说明可以，但可能存在更优的半径，所以调小。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, ans, a[200005], b[200005], num, len;
vector<int> T[200005];

void dfs(int u, int fa)
{
	int p = -1, q = 0;
	for (int i = 0 ; i < T[u].size() ; i ++)
	{
		int v = T[u][i];
		if (v != fa)
		{
			dfs(v, u);
			p = max(p, a[v] - 1);
			q = max(q, b[v] + 1);
		}
	}
	if (p >= q)
	{
		a[u] = p;
		b[u] = -1;
		return ;
	}
	if (q < len)
	{
		a[u] = 0;
		b[u] = q;
		return ;
	}
	num ++;
	a[u] = len;
	b[u] = -1;
}

bool check(int x)
{
    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));
	len = x, num = 0;
	dfs(1, 0);
	if (b[1] != -1)
	{
		num ++;
	}
    if(num > k)
	{
		return 0;
	}
    return 1;
}

int main()
{
	cin >> n >> k;
	for (int i = 1 ; i < n ; i ++)
	{
		int u, v;
		cin >> u >> v;
		T[u].push_back(v);
		T[v].push_back(u);	
	}
	int l = 1, r = 200000;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << ans;
}
```


---

## 作者：OrientDragon (赞：2)

# 题意（题目翻译）
> 给出一棵具有 $n$ 个结点的树，现在国王想把一个信息传递给每一个结点上的人。
> 
> 国王可以选择 $K$ 个结点，让这些结点在时刻 $0$ 立即获得这个消息。
> 
> 如果一个结点在时刻 $t$ 获得了消息，那么它会再让它的邻居在时刻 $t+1$ 知道这个消息。
> 
> 请选择初始的 $K$ 个点，使得尽快能让所有结点知道这条消息，请输出最早能让所有结点都知道该消息的时刻。
# 思路
考虑答案具有单调性 $^1$，所以可以二分答案 $r$，问题就转变为：

> 已知最大距离 $r$，可以在树上选择 $K$ 个结点作为哨兵，检验能否存在一种方案，使得任意结点与最近的哨兵距离不超过 $r$ 条边。

考虑贪心过程：首先，找到深度最深的叶子。在这个叶子的 $r$ 级父亲结点放置一个哨兵，一定是最优策略的一步 $^2$。然后我们移除这个哨兵能在 $r$ 步范围内扩散到的所有结点，反复执行此过程，直到使用所有的 $K$ 个哨兵，然后检查是否还存在未被覆盖的结点即可。

$^1$：如果 $r=x$是一组合法解，那么 $\forall
y<x,r=y$ 都是合法的解。

$^2$：考虑最深的叶子结点 $p_i$ 和最大距离为 $r$ 时所有能覆盖 $p_i$ 的点 $q_i$，那么 $p_i$ 的 $r$ 级父亲结点 $q_j$ 的覆盖贡献一定不会差于任意一个 $q_i(i\neq j)$。

# 实现
上述贪心过程的一种实现方法，是用 dp 形式维护。

定义 $dp[i]$ 表示考虑结点 $i$ 的子树中距离 $i$ 最远的未被覆盖的结点与 $i$ 的距离。特殊地，如果结点 $i$ 的子树已经全部覆盖，则 $dp[i]$ 记录的是溢出的覆盖距离，用负数表示。比如 $dp(i)=-(r-1)$则可以表示 $i$ 的一个孩子放置了哨兵，该哨兵可以溢出 $i$ 的子树从而再向 $i$ 的父亲边往上溢出覆盖 $r-1$ 距离的结点。

转移的时候，考虑用结点 $u$ 求解 $dp[u]$，不妨设其孩子结点为 $v_1,v_2,\ldots,v_k$，则首先对其 $dp$ 值为负数的孩子找出最小值；假设最小值为 $-x$，那么意味着 $u$ 结点还可以利用 $(x-1)$ 的覆盖距离去覆盖其他子树。然后考虑其 $dp$ 值为正数的孩子结点，找出最大值，不妨设其为 $y$。

如果 $y+1\leq x$，说明 $u$ 的子树可以填满了，直接有 $dp[u]=-(x-1)$；否则则说明 $u$ 的子树还是填不满，于是有 $dp[u]=y+1$。如果此刻得出 $dp[u]=r$ 了，则说明此刻需要在 $u$ 结点放置一个哨兵，于是 $cnt$ 自增一次记录，然后令 $dp[u]=-r$。

总复杂度：二分 + 贪心 + dp 维护贪心状态，复杂度 $O(n \log_2 n)。$

---

## 作者：lxyt_415x (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_arc116_e)

## 思路

看到最大值最小首先可以想到二分，发现答案具有单调性，那么思考如何在 $O(n)$ 的时间内判断是否合法。

考虑贪心，在最远没覆盖的点的距离和要判断的 $mid$ 刚好相等的时侯再选择一定不劣，因为这样覆盖的点最多，那么从叶子节点向上回溯，处理它的所有儿子，判断是否选择该点。

## 注意事项

1. 因为一个点也可以被它的儿子覆盖，所以选完一个点以后应该将值设为 $-mid$ 而不是 $0$。

2. 判断大小时的大小于号最好模一遍样例再确定，~~不然容易被硬控 2h~~。

3. 判叶子节点的时候要注意入度为 $1$ 的点除了叶子节点外，也可能是根节点（可能就我会犯吧）。

4. 合并到根节点的时候要特判其是否能被覆盖。

5. 儿子可以被其他儿子内的关键点覆盖。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,ans,mid,tim;
int dep[N];
vector<int>v[N];
inline void dfs(int x,int fa)
{
	if(v[x].size()==1&&x!=1) //判叶子 
	{
		dep[x]=1;
		return ;
	}
	dep[x]=-N; //儿子节点的信息 
	int mi=N; // 距离最近的关键点 
	for(auto y : v[x])
		if(y!=fa)
		{
			dfs(y,x);
			dep[x]=max(dep[x],dep[y]);
			mi=min(mi,dep[y]);
		}
	dep[x]+=1; // 加上自己 
	if(dep[x]+mi<=0) // 能否被儿子的关键点覆盖 
		dep[x]=mi+1;
	else if(dep[x]>mid) // 自己是关键点 
	{
		dep[x]=-mid;
		tim++;
	}
	if(x==1&&dep[x]>0) // 特判根节点 
		tim++;
	return ;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=2,x,y;i<=n;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	int l=1,r=n;
	while(l<=r)
	{
		mid=l+r>>1;
		tim=0;
		dfs(1,0);
		if(tim<=k)
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：1)

- 题意：在一棵树上点 $k$ 个关键点，求树上每个点到任意关键点距离最大值的最小值，$n \le 2 \times 10^5$

$n$ 在 $2 \times 10^5$ 应该是 $O(n)$ 或者 $O(nlogn)$，前者显然不太可能，又因为题中提到了最大值最小，容易想到考虑二分答案。

那么就需要枚举一个最远距离，每一次 $O(n)$ 来判断能否放下 $k$ 个关键点，如果不超过 $k$ 那么合法，否则非法。

- 如何判断？

答案可以从下往上汇集，不妨每次从树中选取深度最深的没有被覆盖的点，然后向上找它的 $mid$ 级祖先，贪心地，这样找到的点就是最远的能覆盖到该点的点，把它点成关键点。我们还可以计算这个 $mid$ 级祖先产生的贡献，就是将从它出发走 $mid$ 长度所及的点全部打上标记，因为它们已经被覆盖了。

所有的点都被打上标记之后，点出的关键点数和 $k$ 去比大小就行了。

- Code
  
```cpp

void dfs1(int u,int fa)
{
	f[u] = fa;
	d[u] = d[fa]+1;
	siz[u] = 1;
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs1(v,u);
		siz[u] += siz[v];
	}
}
struct NODE
{
	int id,dep;
	bool operator < (const NODE a) const
	{
		return dep > a.dep;
	}
}a[N];
bool vis[N]{};
void dfs3(int u,int fa,int step,int mid)
{
	if(step > mid) return;
	vis[u] = true;
	for(int i{head[u]};i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v != fa) dfs3(v,u,step+1,mid);
	}
}
int n,k;
bool check(int mid)
{
	memset(vis,0,sizeof(bool)*(n+1));
	int res{};
	for(int i{1};i<=n;i++)
	{
		int id = a[i].id;
		if(!vis[id])
		{
			for(int s{1};s<=mid;s++)if(f[id]) id = f[id];
			dfs3(id,0,0,mid);
			res++;
		}
		if(res > k) return false;
	}
	return true;
}
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
	#endif
	n = read(),k = read();
	for(int i{1};i<n;i++)
	{
		int u = read(),v=  read();
		add(u,v);add(v,u);
	}
	if(k == n - 1) writeln(1),exit(0);
	dfs1(1,0);
	for(int i{1};i<=n;i++) a[i].id = i,a[i].dep = d[i];
	sort(a+1,a+1+n);
	int ll = 1,rr = n,ans{};
	while(ll <= rr)
	{
		int mid = (ll+rr) >> 1;
		if(check(mid)) rr = mid - 1,ans = mid;
		else ll = mid + 1;
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：Charlie_ljk (赞：1)

先来看 [P3942 将军令](https://www.luogu.com.cn/problem/P3942) 这道题，是一个树形 DP，要求每个点到关键点的距离不超过 $k$。

定义 $f_{x,1}$ 为 $x$ 到其子树中最远的一个没有被覆盖到的节点的距离，$f_{x,0}$ 为 $x$ 到其最近一个关键点的距离。

首先若 $f_{x,1}+f_{x,0}\le k$ 说明改棵子树都被覆盖到了，$f_{x,1}=-1$ 即可。

从贪心的角度，若 $f_{x,1}=k$ 时，将 $x$ 设为关键点，正确性是显然的，这样能在使其子树全部被覆盖的同时覆盖更多点，则此时 $f_{x,1}=-1,f_{x,0}=0$ 即可。

最后发现根节点是处理不到的，特判其有没有被覆盖，没有就在根节点设立关键点。

发现本体存在单调性，二分答案其距离 $k$ 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e5+10,inf=1e9;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
int n,k,ans,f[N][2];
vector<int>e[N];
void dfs(int x,int fa,int mid)
{
    f[x][0]=inf,f[x][1]=0;
    for(int y:e[x])
    {
        if(y==fa) continue;
        dfs(y,x,mid);
        if(f[y][1]!=-1) f[x][1]=max(f[x][1],f[y][1]+1);
        f[x][0]=min(f[x][0],f[y][0]+1);
    }
    if(f[x][1]>=mid)
    {
        ans++;
        f[x][1]=-1;
        f[x][0]=0;
    }
    if(f[x][1]+f[x][0]<=mid) f[x][1]=-1;
}
signed main() 
{
    read(n),read(k);
    for(int i=1,x,y;i<=n-1;i++)
    {
        read(x),read(y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    int l=1,r=n-1,answ;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        ans=0;
        memset(f,0,sizeof(f));
        dfs(1,0,mid);
        if(f[1][1]!=-1) ans++;
        if(ans<=k) r=mid-1,answ=mid;
        else l=mid+1;
    }
    write(answ);
}
```

---

## 作者：Kketchup (赞：0)

### [[ARC116E] Spread of Information](https://atcoder.jp/contests/arc116/tasks/arc116_e)

- 树形 DP
- 二分

**Sol:** 先看到问题形式，最小化最大值，套路性地想到二分答案。那么转化成判定性问题：能否用 $K$ 个关键点覆盖整棵树，使得任意到关键点的距离小于等于 $mid$。我们判定时只需要计算在最大距离为 $mid$ 的限制下最少的关键点个数与 $K$ 的大小关系即可。

接下来，我们考虑一个点被覆盖的所有情况：自己是关键点；距离小于等于 $mid$ 的儿子是关键点，距离小于等于 $mid$ 的祖先或祖先的其他儿子是关键点。朴素的想法是自底向上地贪心，如果一个点不能被覆盖，则将其 $mid$ 级祖先设为关键点。但这样答案不够优秀，因为会出现祖先的其他儿子覆盖的情况，会重复计算。

所以我们考虑 DP，设 $f_u$ 表示以 $u$ 为根的子树中距离 $u$ 最远的未被覆盖的点的距离，设 $g_u$ 表示以 $u$ 为根的子树中距离 $u$ 最近的关键点到 $u$ 的距离。转移是比较显然的，$f_u=\max_{v\in son_u}{f_v+1}$，$g_u=\min_{v\in son_u}{g_v+1}$。初始值 $f_u=-\infty$，$g_u=+\infty$

接下来我们考虑计算关键点个数，分类讨论。

- $f_u+g_u\le mid$

此时说明 $u$ 子树中的关键点可以覆盖整个以 $u$ 子树，不需要再添加关键点了。所以 $f_u=-\infty$。

- $g_u>mid$

此时说明 $u$ 子树中有点（包括 $u$）不能被子树中的关键点覆盖，要被 $u$ 或更高级的祖先覆盖，在祖先上处理。所以 $f_u=\max(f_u,0)$，表示 $u$ 自己也需要被覆盖。

- $f_u=mid$

此时说明子树中已经有没被覆盖的点到 $u$ 距离恰好为 $mid$ 了，再不覆盖就不能覆盖到那个点了。所以 $g_u=0$，$f_u=-\infty$，还要把关键点计数器加一。注意这种情况可能与上一种情况同时满足，所以这几种情况并列全用 if 判断。

最后记得特判根的情况，如果 $f_1\ge0$，计数器加一。

**Idea:** 先考虑二分答案转化问题，然后朴素发现自底向上的贪心不对，接着想到 DP 转移，细节分讨即可。

N 倍经验：[[POI2011] DYN-Dynamite](https://www.luogu.com.cn/problem/P3523)，[将军令](https://www.luogu.com.cn/problem/P3942)，[[HNOI2003] 消防局的设立](https://www.luogu.com.cn/problem/P2279)。

```cpp
const int N=3e5+10;
int n,m;
struct edge{
	int v,next;
}e[N<<1];
int head[N],tot;
void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
int f[N],g[N],cnt;
void dfs(int u,int fa,int lim){
	f[u]=-1e9,g[u]=1e9;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u,lim);
		f[u]=max(f[u],f[v]+1);
		g[u]=min(g[u],g[v]+1);
	}
	if(f[u]+g[u]<=lim) f[u]=-1e9;
	if(g[u]>lim) f[u]=max(f[u],0);
	if(f[u]==lim) g[u]=0,cnt++,f[u]=-1e9;
}
bool chk(int x){
	cnt=0;
	dfs(1,0,x);
	if(f[1]>=0) cnt++;
	return (cnt<=m);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,x,y;i<n;++i){
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	int l=0,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(chk(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：AC_love (赞：0)

最大值最小化，二分答案，考虑怎么 check。

二分一个值 $x$，对于当前深度最深的没有被选取的点，肯定选它的 $x$ 级祖先最优。

设 $f(i)$ 表示 $i$ 到 $i$ 子树中最远的没有被选取的点覆盖的点的距离，$g(i)$ 表示 $i$ 到 $i$ 子树中最近的被选取的点的距离。

显然有转移：

$$f(i) = \max_{x \in son_i}f(x) + 1$$

$$g(i) = \min_{x \in son_i}g(i) + 1$$

对于某个 $i$，如果 $f(i) = x$，这个点必须被选上，此时我们选上 $i$ 号点，令 $f(i) = -\inf, g(i) = 0$。

如果 $f(i) + g(i) \le x$，说明 $i$ 子树内所有点都被覆盖了，此时我们令 $f(i) = -\inf$。

对于某个 $i$，如果 $g(i) > x$，说明 $i$ 节点没被子树中的节点覆盖，必须选择子树外的点覆盖。此时如果 $i$ 自己就是没被选中的点，因此需要用 $i$ 来更新 $f(i)$，即 $f(i) = \max(f(i), 0)$。

做完之后，记得判断一下 $1$ 号节点整颗子树有没有被完全覆盖。如果没有的话，还需要额外把 $1$ 号点也选进来。

[code](https://atcoder.jp/contests/arc116/submissions/59610222)

---

