# Trapmigiano Reggiano

## 题目描述

在一个意大利村庄中，一只饥饿的老鼠从给定树 $^{\text{∗}}$ 的顶点 $\textrm{st}$ 出发，该树包含 $n$ 个顶点。

给定一个长度为 $n$ 的排列 $p$ $^{\text{†}}$，共有 $n$ 个步骤。在第 $i$ 步时：

- 一块诱人的帕尔马干酪出现在顶点 $p_i$。若老鼠当前位于顶点 $p_i$，它将停留并享用；否则，它将沿简单路径向 $p_i$ 移动一条边。

你的任务是找到这样的排列，使得经过所有 $n$ 步后，老鼠必定到达陷阱所在的顶点 $\textrm{en}$。

注意：老鼠必须在完成所有 $n$ 步后到达 $\textrm{en}$，但在过程中可能提前经过 $\textrm{en}$。

$^{\text{∗}}$ 树是一个无环的连通图。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，成功捕获老鼠：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 = \textrm{en}. $$

第二个测试用例中，当 $n = 2$ 时一个可能的排列是 $p = [1, 2]$：

$$ \textrm{st} = 1 \overset{p_1 = 1}{\xrightarrow{\hspace{1.3cm}}} 1 \overset{p_2 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

第三个测试用例中，当 $n = 3$ 时一个可能的排列是 $p = [3, 1, 2]$：

$$ \textrm{st} = 2 \overset{p_1 = 3}{\xrightarrow{\hspace{1.3cm}}} 3 \overset{p_2 = 1}{\xrightarrow{\hspace{1.3cm}}} 2 \overset{p_3 = 2}{\xrightarrow{\hspace{1.3cm}}} 2 = \textrm{en}. $$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 1 1
2 1 2
1 2
3 2 2
1 2
2 3
6 1 4
1 2
1 3
4 5
5 6
1 4```

### 输出

```
1 
1 2 
3 1 2 
1 4 3 2 6 5```

# 题解

## 作者：迟暮天复明 (赞：4)

以 en 为根跑 dfs，然后从深往浅选取。

不难证明从深往浅的策略下，不会出现老鼠操作后出现在当前选择点下面的情况。

所以容易证明这个策略的正确性。

---

## 作者：fzark (赞：4)

这里介绍一个通用的 **树上拓扑删点** 的思路，题主用这个思路，赛时很快就切掉了这题。如果不知道这个技巧，可以观看 [这篇文章](https://www.luogu.com.cn/article/fvsv6s49)。

## 题意

[原题链接](https://www.luogu.com.cn/problem/CF2071C)。

形式化题意：给定一颗树，假设存在一个排列 $a$，老鼠位于给定起点，现在可以遍历这个排列，每次遍历必须执行一个操作，即：设老鼠存在点 $u$，那么对于 $a_i$，老鼠必须向 $a_i$ 移动一条简单路径，遍历完之后老鼠要位于给定终点，求该排列。

## 思路

问题可以转换成，求树中的某个点的位置，并且很显然，不管老鼠位于哪里，我们总是可以从叶子节点进行消耗。当老鼠移动到叶子节点时，显然可以用其他的任意一个叶子节点促使移动。不断重复该过程，最后就是位于拓扑序最后的 $end$ 节点。

## 代码

```python
import math
import sys;input = lambda : sys.stdin.readline().rstrip()
from collections import defaultdict,deque
def solve():
    n,st,end = map(int,input().split())
    g = defaultdict(list)
    d = [0] * (n + 1)
    for i in range(n - 1):
        u,v = map(int,input().split())
        g[u].append(v)
        g[v].append(u)
        d[u] += 1
        d[v] += 1
    queue = deque([])
    for i in range(1,n + 1):
        if d[i] <= 1:queue.append(i)
    ans = []
    while queue:
        u = queue.popleft()
        # 显然遇到 end 节点就跳过不处理
        if u == end:continue
        d[u] -= 1
        ans.append(u)
        for v in g[u]:
            d[v] -= 1
            if d[v] == 1:queue.append(v)
    # 最后将 end 节点留到拓扑序最后即可
    ans.append(end)
    return ans

for i in range(int(input())):print(*solve())
```

## 时间复杂度

$O(n)$。

---

## 作者：sLMxf (赞：3)

# 简述题意
有一个序列 $p_i$，定义第 $i$ 次操作：
- 如果当前在 $p_i$，则本轮不动。
- 否则，按照前往 $p_i$ 的最优路径走一步。

给定起点 $st$，问是否存在一个排列 $p_i$，使得进行 $n$ 次操作后，到达点 $en$。
# 算法分析
我们定义当前（初始为 $st$）深度为 $dep$，最大深度为 $m$。其中树根为 $en$。

无论何时有 $dep\le m$。

如果我们能找到一种算法，使得我们不断让这个 $m$ 变小就好了。

有一个简单粗暴的方法：我们每次删掉一片最深的叶子即可。

但这道题不存在删除叶子结点的操作，于是我们可以每次前往最深的叶子，这样以后**再也无法到达这个叶子**，可以看做删掉了这个叶子。

那么把所有节点按深度排序输出即可。时间复杂度 $O(n\log n)$。
# 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct tot{
	int dep,edge;
	bool operator < (const tot A)const{
		return dep>=A.dep;
	}
}t[114514];
vector<int>vc[114514];
int depth[114514];
void dfs(int now,int fa)
{
	depth[now]=depth[fa]+1;
	for(int i=0;i<vc[now].size();i++)
	{
		if(vc[now][i]!=fa) dfs(vc[now][i],now);
	}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T,n,begin,end,u,v;
	cin>>T;
	while(T--)
	{
		cin>>n>>begin>>end;
		for(int i=1;i<=n;i++) vc[i].clear();
		for(int i=1;i<n;i++)
		{
			cin>>u>>v;
			vc[u].push_back(v);
			vc[v].push_back(u);
		}
		dfs(end,0);
		for(int i=1;i<=n;i++) t[i]=(tot){depth[i],i};
		sort(t+1,t+n+1);
		for(int i=1;i<=n;i++) cout<<t[i].edge<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：2)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{49}$ 篇题解。

# $\mathbf{0x01}$ 承

给出一棵树，输出干酪在顶点出现的顺序，一只老鼠初始在根节点，如果干酪在这个点，就会停下来吃掉；否则向这个点移动一条边。确保老鼠最终落入陷阱顶点。

# $\mathbf{0x02}$ 转

>以 $\text{en}$ 为根跑 `dfs`，然后从深往浅选取。
>
>不难证明从深往浅的策略下，不会出现老鼠操作后出现在当前选择点下面的情况。

以下用归纳法证明这个结论：

在处理完所有深度 $>k$ 的节点后，老鼠位置深度 $\leq k$。现在处理深度 $k$ 的节点 $p_i$。

- 若老鼠当前位置 $u = p_i$，直接停留，深度仍为 $k$。
- 若 $u ≠ p_i$，沿路径向 $p_i$ 移动一步。此时若 $u$ 在 $p_i$ 的子树外，移动后 $u$ 的深度减 $1$，但不会进入 $p_i$ 的路径下方。若有一条 $u$ 到 $p_i$ 的边，移动后到达 $p_i$，深度 $k$。

由于深度更大的节点已处理，老鼠无法移动到更深的位置。

移动后的位置要么是 $p_i$，要么在 $p_i$ 的路径外，但深度不会比 $k$ 更小。


# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,s,e,d[100005];
vector<int>g[100005];
vector<int>dis[100005];

void dfs(int u,int fa){
	d[u]=d[fa]+1;
	dis[d[u]].push_back(u);
	for(auto v:g[u]){
		if(v==fa)continue;
		dfs(v,u);
	}
}

int main(){
	cin>>t;
	while(t--){
		cin>>n>>s>>e;
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(e,0);
		for(int i=n;i>=1;i--)
			for(auto v:dis[i])
				cout<<v<<" ";
			cout<<'\n';
			for(int i=1;i<=n;i++){
			g[i].clear();
			dis[i].clear();
		}
	}
}
```

---

## 作者：rechess (赞：1)

原题大意：给定一棵 $n$ 个节点的树，并给出两个节点 $st$，$en$，求一个从 $1$ 到 $n$ 的排列，使得初始时从 $st$ 出发，第 $i$ 步朝排列中第 $i$ 个数移动一步，使得最终移动完 $n$ 步后恰好能停在 $en$ 点上。

做法：这个题首先思考，如果朝着离 $en$ 最远的点走，那么最远会走到某个最远的点，接下来，朝着所有次远点走，则最远走到某个次远点，以此类推，当我们按距离 $en$ 距离的降序顺序走完第 $x$ 层点，那么此时最远应停在与 $en$ 距离 $x$ 远的点上，所以如果我们按照这个顺序走，最终会停在距离 $en$ 点长度为 $0$ 的点上，也就是 $en$ 点。

代码：dfs 遍历即可，时间复杂度为 $\mathcal{O}(n)$。


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef pair<int,int> pii;
int T;
int n,s,en;
int mx=-1;

vector<int> q[100010];
int h[100010],e[200020],ne[200020],idx;
bool st[100010];

void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int u,int dt)
{
    q[dt].push_back(u);
    st[u]=true;
    bool fg=false;
    
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(st[j])continue;
        fg=true;
        dfs(j,dt+1);
    }
    if(!fg)mx=max(mx,dt);
    st[u]=false;
}

int main()
{
    memset(h,-1,sizeof h);
    cin>>T;
    while(T--)
    {
        mx=-1;
        cin>>n>>s>>en;
        
        idx=0;
        for(int i=0;i<=n;i++)q[i].clear();
        for(int i=1;i<=n;i++)h[i]=-1;
        for(int i=1;i<n;i++)
        {
            int a,b;
            cin>>a>>b;
            add(a,b);
            add(b,a);
        }
        dfs(en,0);
        for(int i=mx;i>=0;i--)
        {
            for(int j=0;j<q[i].size();j++)cout<<q[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
```

---

## 作者：lyx128 (赞：1)

分享一种特殊的做法，我们先对题目进行分析。

以下第 $3$ 个情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/vfrd2eu3.png)
而这是第 $3$ 个情况的几个可能的答案：
```
1 4 5 6 2 3
1 4 5 6 3 2
6 2 3 5 1 4
6 5 2 3 1 4
2 3 6 1 5 4
2 3 1 6 5 4
......
```
我们可以通过模拟发现：这只幼稚的小老鼠是大多时候是被干酪吸引并在陷阱左右跳动的。

于是，我们可以考虑进行以陷阱为中心，对别的点进行遍历，这便是树的后续遍历啦。

![](https://cdn.luogu.com.cn/upload/image_hosting/ife1uj08.png)

接下来就是你们最爱的代码啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5;
int T;
int n,st,en;
int u,v;
struct Edge{
	int v;
	int next;
}e[(N<<1)+5];
int head[N+5],in[N+5],cnt;
void add(int u,int v){
	++in[v];
	e[++cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
	return ;
}
int dfn[N+5],rcnt;
void init(){
	cnt=rcnt=0;
	memset(head,0,sizeof(int)*(n+2));
	memset(in,0,sizeof(int)*(n+2));
	return ;
}
void dfs(int x,int fa){
	for(int i=head[x];i;i=e[i].next)
		if(e[i].v!=fa)
			dfs(e[i].v,x);
	dfn[++rcnt]=x;
	return ;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>st>>en;
		init();
		for(int i=1;i<n;i++){
			cin>>u>>v;
			add(u,v),add(v,u);
		}
		dfs(en,0);
		if(rcnt!=n){
			cout<<-1<<"\n";
			continue;
		}
		for(int i=1;i<=rcnt;i++)
			cout<<dfn[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：masonxiong (赞：0)

# 题目简述

给定一棵 $n$ 个节点的树，有一只老鼠初始位于 $s$。请构造一个 $1\sim n$ 的排列 $p$，使得：顺序遍历 $p$，设老鼠当前位于 $u$，对于 $p_i$，老鼠需要沿 $u\rarr p_i$ 的简单路径移动一个节点，且老鼠最终位于 $t$。

# 题目分析

把 $t$ 建成根，我们需要做的就是让老鼠最终位于根节点。那么一个直接的想法是，我们从底向上一层一层地把节点删掉，也就是选进排列中，就好了。

下面我们需要证明的是：这不会使得老鼠被困在最下一层。因为当老鼠位于最下一层时，除了选中其位于的节点之外的任何操作都会使得其高度上升，所以唯一可能发生的事情是其所位于的节点是这一层最后一个被删掉的。但这时就该删另一个节点了，老鼠的位置就会上升到新的最下一层。

# 题目做法

将节点按深度降序排序输出。

# 代码实现

```cpp
#include <bits/stdc++.h>
 
constexpr int Maxn = 1e5 + 5;
 
int t, n, s, d, u, v;
std::array<std::vector<int>, Maxn> tree;
std::array<int, Maxn> depth, answer;
 
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    for (std::cin >> t; t--; ) {
        std::cin >> n >> s >> d;
        depth.fill(0), depth[d] = 1;
        std::for_each(tree.begin() + 1, tree.begin() + n + 1, [](std::vector<int>& i) { i.clear(); });
        for (int i = n - 1; i--; ) {
            std::cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        for (std::deque<int> Q{d}; !Q.empty(); Q.pop_front())
            for (int next : tree[Q.front()])
                if (depth[next] == 0)
                    depth[next] = depth[Q.front()] + 1, Q.push_back(next);
        std::iota(answer.begin(), answer.begin() + n, 1);
        std::sort(answer.begin(), answer.begin() + n, [&](int i, int j) { return depth[i] > depth[j]; });
        std::for_each(answer.begin(), answer.begin() + n, [](int i) { std::cout << i << ' '; }), std::cout << '\n';
    }
    return 0;
}
```

---

