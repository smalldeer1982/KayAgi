# [ABC327D] Good Tuple Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_d

$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (S,\ T)\ =\ ((S_1,\ S_2,\ \dots,\ S_M),\ (T_1,\ T_2,\ \dots,\ T_M)) $ が **良い数列の組である** とは、$ (S,\ T) $ が次の条件を満たすことを言います。

- $ 0,1 $ からなる長さ $ N $ の数列 $ X\ =\ (X_1,\ X_2,\ \dots,\ X_N) $ であって次の条件を満たすものが存在する。
  - $ i=1,\ 2,\ \dots,\ M $ それぞれについて、$ X_{S_i}\ \neq\ X_{T_i} $ が成立する。
 
$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (A,\ B)\ =\ ((A_1,\ A_2,\ \dots,\ A_M),\ (B_1,\ B_2,\ \dots,\ B_M)) $ が与えられます。$ (A,\ B) $ が良い数列の組である場合は `Yes` を、そうでない場合は `No` を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 入力される値は全て整数
 
### Sample Explanation 1

$ X=(0,1,0) $ とすると、$ X $ は $ 0,1 $ からなる長さ $ N $ の数列で、 $ X_{A_1}\ \neq\ X_{B_1} $ かつ $ X_{A_2}\ \neq\ X_{B_2} $ を満たします。 よって、$ (A,B) $ は良い数列の組としての条件を満たしています。

### Sample Explanation 2

条件を満たすような数列 $ X $ は存在しないので、$ (A,\ B) $ は良い数列の組ではありません。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3
1 2 3
2 3 1```

### 输出

```
No```

## 样例 #3

### 输入

```
10 1
1
1```

### 输出

```
No```

## 样例 #4

### 输入

```
7 8
1 6 2 7 5 4 2 2
3 2 7 2 1 2 3 3```

### 输出

```
Yes```

# 题解

## 作者：OldDriverTree (赞：11)

这题显然是种类并查集做法最简单啊，题解区里怎么没有这种做法？这篇题解就来讲种类并查集做法。

双倍经验：[P1892 [BOI2003] 团伙](https://www.luogu.com.cn/problem/P1892)。

# Solution

由于 $X_i$ 有 $0$ 或 $1$ 两种取值，考虑种类并查集，把它拆成 $a_i$ 和 $a_i'$，$a_i$ 表示 $X_i=0$ 时的情况，$a_i'$ 表示 $X_i=1$ 时的情况。

对于每个限制 $X_{S_i}\not=X_{T_i}$，如果 $a_{S_i}$ 和 $a_{T_i}$ 在同一连通块内，就说明 $X_{S_i}=X_{T_i}$，显然是不合法的，就输出 `No`，否则就有两种情况：如果 $X_{S_i}=1$，那么 $X_{T_i}=0$，这种情况就把 $a_{S_i}'$ 和 $a_{T_i}$ 连一条边，如果 $X_{S_i}=0$，那么 $X_{T_i}=1$，这种情况就把 $a_{S_i}$ 和 $a_{T_i}'$ 连一条边。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int n,m,a[N],b[N];
int fa[N<<1|1];

int find(int x) {
	return fa[x]^x?fa[x]=find(fa[x]):x;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) scanf("%d",a+i);
	for (int i=0;i<m;i++) scanf("%d",b+i);
	for (int i=1;i<=n<<1;i++) fa[i]=i;
	for (int i=0;i<m;i++) {
		int x=find(a[i]),y=find(b[i]);
		if (x==y) return printf("No"),0;
		fa[find(n+a[i])]=y,fa[find(n+b[i])]=x;
	}
	printf("Yes");
	return 0;
}
```

---

## 作者：Expert_Dream (赞：5)

### 分析：
这一道题很容易发现可以用并查集来维护 ~~（不知道为什么其他人都用了图论）~~，$a_i$ 与其对应的 $b_i$ 代表着 $a_i$ 这个集合里不能存在着 $b_i$。

根据只有存在两个集合，所以我们会发现，若 $x$ 与 $y$ 不在一个集合且 $x$ 与 $z$ 也不在一个集合，那么 $x$ 和 $y$ 就在一个集合内。然后针对可以在一个集合内的点进行并查集。到最后再判断一下每一个点 $a_i$ 是否与 $b_i$ 不在一个集合内，若不在，合法，否则不合法。

时间复杂度大概在 $O(n)$ 左右，可以过去。

[code](https://atcoder.jp/contests/abc327/submissions/47243667)。

---

## 作者：2huk (赞：3)

# D - Good Tuple Problem

## Description

给定 $n, m$ 和长度为 $m$ 的 $\{a_m\}, \{b_m\}$ 序列。请你构造一个长度为 $n$ 的 $01$ 序列 $\{x_n\}$，使得所有 $1 \le i \le n$，满足 $x_{a_i} \ne x_{b_i}$。请你求出是否能构造出 $\{x_m\}$ 序列。

$1 \le n, m \le 2 \times 10^5$，$1 \le a_i, b_i \le n$。

## Solution

考虑在图上将 $a_i$ 与 $b_i$ 连边，表示 $x_{a_i} \ne x_{b_i}$，那么只需要判断能否将点分成两部分，使得第一部分的点的 $x$ 全是 $0$，第二部分的点的 $x$ 全是 $1$ 即可。

那么很显然这需要满足每一部分内部的点没有连边，也就是判断这张图是否是二分图。那么就可以使用染色法。

当然也可以从是否存在奇环的角度考虑这个问题。若存在奇环，不妨令这个环上的点为 $\{b_k\},k \text{ is odd}$，那么有 $x_{b_1} \ne x_{b_2}, x_{b_2} \ne x_{b_3} \dots x_{b_{k - 1}} \ne x_{b_k},x_1 \ne x_{b_k}$。由于 $x_i$ 只有两种取值，所以这些不等式是不能同时满足的。

总时间复杂度 $\mathcal O(n)$。

## Code

开局 4 分钟的代码：[Submission #47214138 - HHKB Programming Contest 2023(AtCoder Beginner Contest 327)](https://atcoder.jp/contests/abc327/submissions/47214138)。

---

## 作者：ACtheQ (赞：3)

题目知识点：二分图染色。

可以把题目想的抽象点，$a_i,b_i$ 看作一条双向边，让后跑遍 `bfs` 染色就行了。

本篇文章主要讲述如何染色。

我们不妨设起点为 $1$。

然后从起点跑遍 `bfs`。

设到来的点的标记为 $x$。

如果这个点没走过，那么这个点变成 $-1 \times x$。

否则判断 $x$ 和这个点的标记一样矛盾，输出 `No`，结束程序。

跑完之后输出 `Yes`。

注意你的建图不一定联通，所以要外面加成循环，只要这个点没被走过，就把这个点当成起点在跑遍 `bfs`。

```c++
int bfs(int s)
{
	queue<int> q;
	vis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(auto u:G[x])
		{
			if(vis[u]==0)
			{
				if(vis[x]==1) vis[u]=-1;
				else vis[u]=1;
				q.push(u);
			}
			else
			{
				if(vis[x]==vis[u]) return -1;
			}
		}
	}
	return 0;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i]; 
	for(int i=1;i<=m;i++)
	{
		G[a[i]].push_back(b[i]);
		G[b[i]].push_back(a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			int x=bfs(i);
			if(x==-1)
			{
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：yshpdyt (赞：2)

## 题意
给定 $n$ 个值为 $0$ 或 $1$ 的点和 $m$ 条关系，每一条关系表示两个点的值不能相同，问是否有合法构造方案满足所有条件。

## Sol

因为值只有 $0$ 或 $1$ 两种，对于每一种关系 $\{a_i,b_i\}$ 可以类比成 「$a_i$ 为 $1$ 且 $b_i$ 为 $0$」，以及「$a_i$ 为 $0$ 且 $b_i$ 为 $1$」 这样的形式，于是该题就变成了 [2-SAT](https://www.luogu.com.cn/problem/P4782) 问题。
 
具体解法大概是对于一个节点 $u$，我们设 $u$ 表示该节点为 $1$ ，$u+n$ 表示该节点为 $0$，或者说前者的反面 。

对于「$a_i$ 为 $1$ 且 $b_i$ 为 $0$」这样的关系，只需要建一条有向边  $a_i \to b_i+n$，表示「若 $a_i$ 为 $1$ 则 $b_i$ 一定为 $0$」。同理 「$a_i$ 为 $0$ 且 $b_i$ 为 $1$」建一条有向边 $a_i+n \to b_i$，表示「若 $a_i$ 为 $0$ 则 $b_i$ 一定为 $1$」。

这样我们得到了一张有向图，只需要在这张有向图上跑 Tarjan 求强连通分量，同一强连通分量的点取值是相同的（$a_i=b_i+n$ 意味着 $a_i \neq b_i$ ）。

最后只需要对于每个点判断  $u$ 和 $u+n$ 是否在同一强连通分量内就可以了，如果在显然是不满足题意的（$u=u+n$ ，$u \neq u$ ？，不可能我不等于我自己）。

时间复杂度 $O(n+m)$


## Code
```
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ll long long
#define N 2000005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
ll low[N],dfn[N],cnt,vis[N],bel[N];
stack <ll> q;
ll ans;
ll a[N],b[N];
vector<ll> v[N];
ll n,m;
void tarjan(ll x){
    low[x]=dfn[x]=++cnt;
    q.push(x);
    vis[x]=1;
    for(auto y:v[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(vis[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ans++;
        while(1){
            auto t=q.top();
            bel[t]=ans;
            vis[t]=0;
            q.pop();
            if(t==x)break;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>b[i];
        v[a[i]].push_back(b[i]+n);// a为1则b为0
        v[a[i]+n].push_back(b[i]);// a为0且b为1
    }
    for(int i=1;i<=n*2;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++){
        if(bel[i]==bel[i+n]){//判断i所属强连通分量和i+n所属强连通分量相同
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    return 0;
}
```

# 拓展
Q：如果让我们输出合法的方案，应该怎样做呢？

A：考虑每个点 $0$ 和 $1$ 的关系，对缩完点的图（每个点代表原图中的一个强连通分量）进行拓扑排序，若 $u$ 所在强连通分量的拓扑序 小于  $u+n$ 所在强连通分量的拓扑序，则说明取 $u=0$ 才符合条件，反之  $u=0$。如果等于呢？~~那就在同一个强连通分量里面同时 取$0$ 和 $1$才符合条件直接无解了~~。

进行 Tarjan 得到的强连通分量编号便是反着的拓扑序（越靠近开始节点的编号越大），所以若 $u$ 所在强连通分量的编号小于  $u+n$ 所在强连通分量的编号，$u=1$ 即可。

```
for(int i=1;i<=n;i++){
    if(bel[i]==bel[i+n]){
        cout<<"No\n";
        return 0;
    }
    if(bel[i]<bel[i+n])res[i]=1;
}
cout<<"Yes\n";
for(int i=1;i<=n;i++)cout<<res[i]<<" ";
```


---

## 作者：sevenki (赞：2)

## 题意

问是否能构造出一个 $01$ 数组使得对于该数组中每对下标为 $a_i,b_i$ 的值互不相等。

## 分析

我们可以把他看做图论问题，将每个节点 $a_i$ 和 $b_i$ 连一条无向边。

显然根据题意，我们可以归纳出这样一个结论：

对于该数组中任意的 $X_i=X_j$，$i$ 与 $j$ 没有连边。

更进一步，可以将该数组划分为两个集合，$0$ 集合和 $1$ 集合，不难发现，对于一个满足题意的数组 $X$，其每个集合内部都没有连边。

这就是一个典型的[二分图](https://oi-wiki.org/graph/bi-graph/)。

所以，我们可以使用 dfs 对每个节点进行染色，对于一个满足题意的数组 $X$，一边所连的相邻两个节点的颜色一定不同。如果出现了冲突，则不满足题意，输出 `No`。反之，没有出现任何冲突，则输出 `Yes`。

当然最后要注意图可能不是联通的。所以要对每个联通块进行染色判断。

[Code](https://atcoder.jp/contests/abc327/submissions/47237622)



---

## 作者：DengDuck (赞：1)

把数组的每一项变成点，把其 $0$ 或者 $1$ 的数值当做黑白的颜色，则你可以转换成这样一个问题：

> 有 $n$ 个点，$m$ 条边，对点进行黑白染色，是否有方案使得相邻的点颜色都不同。

这个显然是并查集的板子啊，种类并查集和带权并查集都可以，我写的是带权并查集。

注意到不同的颜色的不同颜色和我颜色相同，这是一个类似于奇偶性的东西，所以你对于和你颜色不同的点连一条长度为 $1$ 的边，相同就连长度为 $0$ 的边，之后你就知道如果你和一个点路径长度为奇数，那么你们就是不同的，为偶数则相同。

考虑合并操作，我们知道 $x,y$ 是不同的，但是其祖先 $fx,fy$ 与 $x,y$ 的颜色相不相同，我们考虑查询 $x,y$ 到祖先上的路径长度，确定了祖先与儿子的关系之后就可以确定 $fx,fy$ 之间的关系，然后连边即可。

考虑同一个祖先的 $x,y$ 要加边，会形成一个环，但是 $x,y$ 的关系是确定的，你只需要看这条边是否符合原先的关系，不符合就判无解，否则你也没必要加这条边。

时间复杂度为 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL n,m,a[N],b[N],fa[N],to[N];
LL find(LL x)
{
	if(fa[x]==x)return x;
	LL t=find(fa[x]);
	to[x]+=to[fa[x]];
	return fa[x]=t;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&b[i]);
	}	
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		LL fx=find(a[i]),fy=find(b[i]);
		if(fx==fy)
		{
			if((to[a[i]]+to[b[i]])%2==0)
			{
				puts("No");
				return 0;
			}
		}
		else
		{
			fa[fx]=fy;
			to[fx]=1-(to[a[i]]+to[b[i]])%2;
		}
	}
	puts("Yes");
}
```

---

## 作者：ilibilib (赞：1)

### 题目大意：

给定一个由不超过 $ N $ 的正整数组成的长度为 $ M $ 的数列对 $ (S, T) = ((S_1, S_2, \dots, S_M), (T_1, T_2, \dots, T_M)) $。如果数列对 $ (S, T) $ 满足以下条件，则称其为 **好的数列对**：

- 存在一个由 0 和 1 构成的长度为 $ N $ 的数列 $ X = (X_1, X_2, \dots, X_N) $，满足以下条件：
  - 对于每个 $ i = 1, 2, \dots, M $，有 $ X_{S_i} \neq X_{T_i} $。

给定长度为 $ M $ 的数列对 $ (A, B) = ((A_1, A_2, \dots, A_M), (B_1, B_2, \dots, B_M)) $，请判断 $ (A, B) $ 是否是一个好的数列对，如果是则输出 `Yes`，否则输出 `No`。

### 题目分析：

**dfs**+**染色**。

建双向边。

用 dfs 遍历。

一个点遍历到的下一个点的颜色一定与它相反。

如果它已经被遍历过了，判断是否满足上述条件。

如果没有被遍历过，按照上述条件进行染色，并 dfs 这个点。

```cpp
#include<bits/stdc++.h>
#define N 400010
using namespace std;
int a[N],b[N];
bool bl[N],f[N];//bl记录是否被记录,f记录颜色
struct qxx{int nx,to;}tu[N];int hd[N],bs=0;
bool dfs(int u)
{
	bl[u]=true;
	for(int i=hd[u];i;i=tu[i].nx)
	{
		int v=tu[i].to;
		if(bl[v]) {if(f[v]==f[u]) return true;}//该点已经被染色,但颜色相同,返回
		else {f[v]=!f[u]; if(dfs(v)) return true;}//该点未被染色,进行染色,并且遍历这个点
	}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>b[i];
	for(int i=1;i<=m;++i)
		tu[++bs]={hd[a[i]],b[i]},hd[a[i]]=bs,
		tu[++bs]={hd[b[i]],a[i]},hd[b[i]]=bs;
	for(int i=1;i<=n;++i)
		if(!bl[i]) if(dfs(i)) {puts("No");return 0;}//遍历每个点
	puts("Yes");
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：1)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc327_d)

给定两个长度为 $m$ 的序列 $a$ 和 $b$，其中的元素大小小于等于 $n$；如果能构造一个序列 $f$ 使得 $f_{a_i} \ne f_{b_i}$，输出 `Yes`，否则输出 `No`。

## Solution

考场太消愁，B 30min，C 和 D 加起来也就 20min。不愧是 HN 第一搞笑选手。

步入正题。考虑从 $a_i$ 向 $b_i$ 建一条无向边，那么显然易见的是，当这个问题转换成图论题后，我们只需要判环。

给一个例子：

$a = \{1,2,3,4,5\}$

$b = \{2,3,4,5,6\}$

这里形成了一条链，可以感性理解一下。这里的 $f$ 可以为 $\{0,1,0,1,0,1\}$，这使得我们的 $f$ 可以不同下标可以直接设置为不同值，互不干涉。

甚至有可能不是链，反正不包括环的必然有解。请读者想想为什么，有助于下文理解。

再举个例子：

$a = \{1,2,3\}$

$b = \{2,3,1\}$

这里形成了一个 **有奇数个节点** 的环，我们在构造时发现因为是奇数，第一个必然和最后一个，也就是 $1$ 和 $3$ 对应的 $f$ 的值，必然相同。比如 $f = \{0,1,0\}$，前后是不是相同？所以奇数长的环无解。

注意，自环也属于长度为奇数的，也就是长度为 $1$。

又举个例子：

$a = \{1,2,3,4\}$

$b = \{2,3,4,1\}$

这里形成了一个 **有偶数个节点** 的环，因为是偶数，$f$ 多出一个可以设置为不同的数的空间，使得我们可以填进去不同的进而造出合法解。这个例子的解是 $f = \{0,1,0,1\}$。是不是前后不同了？

注意，重边不计入环。

至此，所有情况我们都讨论完毕，找环可以 DFS，就做完了。

## Code

```cpp
// 2023/11/5 PikachuQAQ

#include <iostream>
#include <vector>
#define No cout << "No", exit(0);
#define Yes cout << "Yes", exit(0);

using namespace std;

const int kMaxN = 2e5 + 7;

int n, m, u[kMaxN], pre[kMaxN], vis[kMaxN];
vector<int> g[kMaxN];

void DFS(int u, int fa) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        if (vis[v] == 0) {
            pre[v] = u, DFS(v, u);
        } else if (vis[v] == 1) {
            int t = u, cnt = 1;
            for (; t ^ v; t = pre[t]) {
                cnt++;
            }
            if (cnt & 1) No;
        }
    }
    vis[u] = 2;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i];
    }
    for (int i = 1, v; i <= m; i++) {
        cin >> v;
        g[u[i]].push_back(v);
        g[v].push_back(u[i]);
    }
    for (int i = 1; i <= n; i++) {
        DFS(i, 0);
    }
    Yes;
 
    return 0;
}
```

---

## 作者：yhx0322 (赞：1)

## Description
给你两个长度为 $M$ 的序列 $A$ 和 $B$，满足以下条件时成为他们是“好的序列”。
- 存在一个长度为 $N$ 的序列 $X$，只由 $0$ 和 $1$ 组成，满足以下条件：
	- 对于每个 $i = 1,2,\dots M$，$X_{A_i} \neq X_{B_i}$。
    
现在，请你判断序列 $(A,B)$ 是否是“好的序列”。

## Solution
这道题非常经典，是一个二分图板子。

使用 DFS 判断是否是二分图。

维护数组 $f$ 来记录当前的状态：
- $f_v = -1$ 表示当前结点 $v$ 还未被访问。
- $f_v = 0/1$ 表示该顶点上写的是 $0/1$。

对于每个 $v = 1,2, \dots ,M$，执行以下操作：
- 如果 $f_v \neq -1$，表示已经访问了节点 $v$，直接 `continue`。
- 如果 $f_v = -1$，说明当前的联通块还没有被访问过。执行 DFS，从这个节点开始 DFS，执行二分图黑白染色。

最后判断这张图是否是二分图，输出答案即可。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int n, m, s[N], t[N], f[N];
vector<int> e[N];

void dfs(int x, int val) {
    f[x] = val;
    for (int y: e[x]) {
        if (f[y] == -1) {
            dfs(y, 1 - val);
        } else if (f[y] == f[x]) {
            cout << "No";
            exit(0);
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> s[i], s[i]--;
    for (int i = 0; i < m; i++) cin >> t[i], t[i]--;
    
    // vector 记录每个点的出边
    for (int i = 0; i < m; i++) { 
        e[s[i]].push_back(t[i]);
        e[t[i]].push_back(s[i]);
    }
    memset(f, -1, sizeof(f));
    for (int i = 0; i < n; i++) {
        if (f[i] == -1) dfs(i, 0); // 没有被访问过就 DFS
    }
    cout << "Yes" << endl;
    return 0;
}
```

---

## 作者：Jamal_Musiala (赞：0)

## ABC327D
简单的类似于二分图判定的题目，可以使用 DFS 染色法。

我们将题目中的 $X$ 数组的每个元素抽象为一个图上的节点，每个节点的点权即为 $X_i$。

这样，我们就有了 $m$ 对关系，可以将每对关系的两个节点连边，代表它们所对应的点权不同。

接着我们像二分图一样染色，对每对相邻的节点染交替的两种颜色。

那么如果出现了无法染色的情况，就说明出现了矛盾。

这样就可以做了。注意：图可能不连通，所以要对每个连通块跑一遍。

---

## 作者：SegTree (赞：0)

对于每个 $a_i$ 和 $b_i$ 建边，问题等价于是否能够满足边的两个端点能染成不同的颜色，直接判断原图是否为二分图即可。

注意图不一定连通，需要对于每个没染色的点都以它为起点跑一遍染色。

[Record](https://atcoder.jp/contests/abc327/submissions/47233191)。

---

## 作者：TankYu (赞：0)

可能是不同的做法。

注意到若有一组 $x_{i_1}\ne x_{i_2},x_{i_2}\ne x_{i_3},x_{i_3} \ne x_{i_1}$，则无解，这是显然的。

由此可以联想到出对于一串不等关系，若其可以写成 $x_{i_1}\ne x_{i_2},x_{i_2}\ne x_{i_3},\cdots,x_{i_{n-1}} \ne x_{i_n},x_{i_n} \ne x_{i_1}$，其中 $n$ 是奇数，则无解。

证明：假设有解，钦定 $x_{i_1}$ 为 $1$，故 $x_{i_2} = 0,x_{i_3} = 1,\cdots$，可以发现有 $x_{i_k} = \begin{cases}1 & k \equiv 1 \pmod2 \\ 0 & k \equiv 0 \pmod 2 \end{cases}$。

又知道 $n$ 是奇数，所以 $x_{i_n}$ 为 $1$，矛盾。

然后我们就可以把原来的不等关系看成边，对于 $x_s \ne x_t$，建一条 $s \leftrightarrow t$ 的边，则无解的条件转化为这个图上存在奇环。

容易发现这等价于二分图判定条件，染色法判定即可。

时间复杂度 $O(n)$，也许比拆点做法少个并查集复杂度。

```cpp
#include <vector>
#include <iostream>
using namespace std;

vector<int> e[200010];
int s[200010], t[200010];
int col[200010];

void dfs(int x, int now)
{
    col[x] = now;
    for (auto i : e[x])
    {
        if (col[i] != 2 && col[i] == now)
        {
            cout << "No";
            exit(0);
        }
        if (col[i] == 2)
        {
            dfs(i, now ^ 1);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        col[i] = 2;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> s[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> t[i];
    }
    for (int i = 1; i <= m; i++)
    {
        e[s[i]].push_back(t[i]);
        e[t[i]].push_back(s[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (col[i] == 2)
            dfs(i, 0);
    }
    cout << "Yes";
    return 0;
}
```

---

