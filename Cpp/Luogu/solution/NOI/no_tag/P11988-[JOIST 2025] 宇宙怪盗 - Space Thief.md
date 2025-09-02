# [JOIST 2025] 宇宙怪盗 / Space Thief

## 题目背景

请使用 C++ 17 / C++ 20 提交。

**不要** `#include "thief.h"`。在文件头加入以下内容：

```cpp
#include <vector>
int query(std::vector<int>);
void answer(int,int);
```

## 题目描述

**这是一道交互题。本题中，交互库可能是自适应的。**

有一张  $N$ 个点 $M$ 条边的无向连通图。点编号 $0\sim N-1$，边编号 $0\sim M-1$，第 $i$（$0 \leq i \leq M-1$）条边双向连接点 $U_i$ 和 $V_i$。

有一把钥匙藏在某一个点上，而有一个宝箱藏在另一个节点上。你需要通过至多 $300$ 次询问确定钥匙所在的节点编号和宝箱所在的节点编号：


> **询问**
> 
> 对于 $i=0,1,\ldots,M-1$，将第 $i$ 条边设置为单向通行。
> - 具体地，构造长度为 $M$ 的 $01$ 序列 $x_0\sim x_{M-1}$。$x_i=0$ 表示第 $i$ 条边从 $U_i$ 指向 $V_i$，$x_i=1$ 表示第 $i$ 条边从 $V_i$ 指向 $U_i$。
>
> 交互库会返回，在这张图中，是否能从钥匙所在的节点到达宝箱所在的节点。


你需要确定钥匙所在的节点 $A$ 和宝箱所在的节点 $B$。为了获得更高的评分，你需要尽量减少询问次数。  


### 实现细节  

你不应该，也不需要实现 `main` 函数。你应该实现以下的函数：

```cpp
void solve(int N, int M, std::vector<int> U, std::vector<int> V)
```  
- 该函数每组测试数据仅调用一次。
  - 参数 `N` 是点数。  
  - 参数 `M` 是边数。  
  - 参数 `U`, `V` 是长度为 $M$ 的数组，表示边 $i$ 双向连接 $U_i$ 和 $V_i$。  

你可以调用以下的函数：  

```cpp
int query(std::vector<int> x)
```

通过此函数，你可以发起一次询问。  

- 参数 `x` 是一个长度为 $M$ 的数组。对于 $0 \leq i \leq M-1$：  
    - 若 `x[i] = 0`，表示仅允许从点 $U_i$ 到点 $V_i$ 的移动。  
    - 若 `x[i] = 1`，表示仅允许从点 $V_i$ 到点 $U_i$ 的移动。  
- 返回值为 $0$ 或 $1$：  
    - $0$ 表示无法通过跃迁装置从钥匙所在的点 $A$ 到达宝箱所在的点 $B$。  
    - $1$ 表示可以到达。  
- 参数 `x` 的长度必须为 $M$。如果不满足，你的程序将被判为 $\texttt{Wrong Answer [1]}$。  
- 参数 `x` 的每个元素必须是 $0$ 或 $1$。如果不满足，你的程序将被判为 $\texttt{Wrong Answer [2]}$。  
- 调用 `query` 函数的次数不得超过 $300$ 次。如果超过，你的程序将被判为 $\texttt{Wrong Answer [3]}$。  

```cpp  
void answer(int A, int B)
```

你需调用此函数来提交答案，即钥匙所在的点 $A$ 和宝箱所在的点 $B$。  

- 参数 `A` 表示钥匙藏在点 $A$ 中。  
- 参数 `A` 必须在 $0$ 到 $N-1$ 的范围内（两边取等）。如果不满足，你的程序将被判为 $\texttt{Wrong Answer [4]}$。  
- 参数 `B` 表示宝箱藏在点 $B$ 中。
- 参数 `B` 必须在 $0$ 到 $N-1$ 的范围内（两边取等）。如果不满足，你的程序将被判为 $\texttt{Wrong Answer [5]}$。  
- 如果提交的答案错误，你的程序将被判为 $\texttt{Wrong Answer [6]}$。  
- `answer` 函数必须被**恰好调用一次**。如果多次调用，你的程序将被判为 $\texttt{Wrong Answer [7]}$。当 `solve` 函数终止时，如果未调用 `answer` 函数，你的程序将被判为 $\texttt{Wrong Answer [8]}$。  

### 注意事项  

- 你的程序可以定义其他函数或使用全局变量。  
- 你的程序不得使用标准输入输出，也不得通过任何方式与其他文件通信。但允许将调试信息输出到标准错误流。
- 对于部分测试点，交互库是**自适应的**。这意味着交互库在开始时没有固定答案，而是根据之前对 `query` 函数的调用历史来响应。保证至少存在一个答案与交互库的所有回答不矛盾。  

### 测试运行  
你可以从附件中下载包含 Sample Grader 的压缩包。该压缩包还包含一个示例源文件。

Sample Grader 是文件 `grader.cpp`。

要测试你的程序，请将 `grader.cpp`、`thief.cpp`、`thief.h` 放在同一目录下，并运行以下命令进行编译：  
```bash  
g++ -std=gnu++20 -O2 -o grader grader.cpp thief.cpp  
```  
或者，你可以运行压缩包中的 `compile.sh` 脚本。此时，使用以下命令进行编译：  
```bash  
./compile.sh  
```  
当编译成功时，会生成可执行文件 `grader`。注意，实际评测程序与Sample Grader 不同。Sample Grader 会作为单个进程运行，从标准输入读取数据并将结果写入标准输出。

## 说明/提示

### 样例交互

| 交互库调用 | 选手程序调用     | 返回值 |
| - | - | - |
|$\texttt{solve(5, 4, [0, 0, 1, 1], [1, 3, 2, 4])}$ |$ $ |               |
| | $\texttt{query([0, 1, 0, 0])}$                 | $1$              |
| | $\texttt{query([1, 1, 1, 0])}$                 | $0$              |
| | $\texttt{query([0, 0, 1, 0])}$                 | $1$              |
| | $\texttt{query([0, 0, 1, 1])}$                 | $0$              |
| | $\texttt{answer(0, 4)       }$                 |               |


- 第 $1$ 次调用 `query` 函数：  
    - 边 $ 0 $：仅允许从点 $ 0 $ 到点 $ 1 $。  
    - 边 $ 1 $：仅允许从点 $ 3 $ 到点 $ 0 $。  
    - 边 $ 2 $：仅允许从点 $ 1 $ 到点 $ 2 $。  
    - 边 $ 3 $：仅允许从点 $ 1 $ 到点 $ 4 $。  
    在此设置下，可以通过边 $0 \to 3$ 的顺序从点 $ 0 $ 到达点 $ 4 $，因此返回值为 $1$。  
- 第 $2$ 次调用 `query` 函数：  
    - 边 $ 0 $：仅允许从点 $ 1 $ 到点 $ 0 $。  
    - 边 $ 1 $：仅允许从点 $ 3 $ 到点 $ 0 $。  
    - 边 $ 2 $：仅允许从点 $ 2 $ 到点 $ 1 $。  
    - 边 $ 3 $：仅允许从点 $ 1 $ 到点 $ 4 $。  
    在此设置下，无法从点 $ 0 $ 到达点 $ 4 $，因此返回值为 $0$。  
- 第 $3$ 次调用 `query` 函数：  
    - 边 $ 0 $：仅允许从点 $ 0 $ 到点 $ 1 $。  
    - 边 $ 1 $：仅允许从点 $ 0 $ 到点 $ 3 $。  
    - 边 $ 2 $：仅允许从点 $ 2 $ 到点 $ 1 $。  
    - 边 $ 3 $：仅允许从点 $ 1 $ 到点 $ 4 $。  
    在此设置下，可以通过跃迁装置到达点 $ 4 $，因此返回值为 $1$。  
- 第 $4$ 次调用 `query` 时，无法从点 $ 0 $ 到达 4，返回值为 $0$。  

最终调用 `answer(0, 4)` 提交答案，表示钥匙在点 $ 0 $、宝箱在点 $ 4 $。  

此样例输入满足子任务 $3\sim 8$ 的约束条件。竞赛网页提供的 `sample-01-in.txt` 文件对应此样例。  

压缩包中的示例程序源码的函数调用与本示例一致。  


### 数据范围
- $2 \leq N \leq 10\,000$；
- $1 \leq M \leq 15\,000$；
- $0 \leq A \leq N-1$；
- $0 \leq B \leq N-1$；
- $A \neq B$；
- $0 \leq U_i \lt V_i \leq N-1$（$0 \leq i \leq M-1$）；
- $(U_i, V_i) \neq (U_j, V_j)$（$0 \leq i \lt j \leq M-1$）；
- 可以通过跃迁装置从任意点到达其他任意点。

### 子任务 与 计分方式
- $\text{Subtask 1 (7 pts)}$：$M = N - 1$，且 $U_i = i,V_i = i + 1$（$0 \leq i \leq M - 1$）。  
- $\text{Subtask 2 (13 pts)}$： $M = N - 1$，且 $U_i = 0,V_i = i + 1$（$0 \leq i \leq M - 1$）。  
- $\text{Subtask 3 (2 pts)}$：$M = N - 1$，且 $N \leq 8$。  
- $\text{Subtask 4 (8 pts)}$：$M = N - 1$，且 $N \leq 50$。  
- $\text{Subtask 5 (5 pts)}$：$M = N - 1$，且 $N \leq 150$。  
- $\text{Subtask 6 (5 pts)}$：$M = N - 1$，且 $N \leq 250$。  
- $\text{Subtask 7 (40 pts)}$： $M = N - 1$。
    在此子任务中，评分规则如下：  
   - 如果子任务 $7$ 中任意测试用例被判为 $\text{Wrong Answer}$，或运行超时、内存超限、运行错误，则该子任务得 $0$ 分。  
   - 否则，令 $T$ 表示本子任务所有测试用例中 `query` 函数调用次数的最大值。评分规则为：  
     - 若 $120 < T$，得 20 分。  
     - 若 $70 < T \leq 120$，得 30 分。  
     - 若 $T \leq 70$，得 40 分。  
- $\text{Subtask 8 (20 pts)}$：无额外限制。
    在此子任务中，评分规则如下：  
   - 如果子任务 $8$ 中任意测试用例被判为 $\text{Wrong Answer}$，或运行超时、内存超限、运行错误，则该子任务得 $0$ 分。  
   - 否则，令 $T$ 表示本子任务所有测试用例中 `query` 函数调用次数的最大值。评分规则为：  
     - 若 $120 < T$，得 10 分。  
     - 若 $70 < T \leq 120$，得 15 分。  
     - 若 $T \leq 70$，得 20 分。  

子任务 $1\sim 6$ 的得分与 `query` 的调用次数无关（只要不超过 $300$ 次）。 


对于部分测试点，交互库是**自适应的**。这意味着交互库在开始时没有固定答案，而是根据之前对 `query` 函数的调用历史来响应。保证至少存在一个答案与交互库的所有回答不矛盾。

## 样例 #1

### 输入

```
5 4 0 4
0 1
0 3
1 2
1 4```

### 输出

```
Accepted: 4```

# 题解

## 作者：tybbs (赞：6)

考虑把图定向为一个 DAG。

假如我们已经得到了一个定向使得 $s$ 可以到达 $t$，考虑怎么确定 $s$ 和 $t$。我们取出这个 DAG 的拓扑序。对于拓扑序上的一段区间 $[l,r]$，把除了左右端点都在 $[l,r]$ 内的边都翻转。若 $s$ 依旧可以到达 $t$，则 $s$ 和 $t$ 都位于 $[l,r]$ 内。运用以上方法可以二分，在 $2\log_2 n$ 次操作内找到 $s$ 和 $t$。

现在只需要找到一个定向方式使得 $s$ 可以到达 $t$。容易发现对于这个问题只需要考虑树的情况。

考虑链的情况。可以直接分治，对于同一层的分治中心，添加两个定向方式即可。也只需要 $2\log_2 n$ 此操作。

对于树的情况，容易想到点分治。但如果使用一般的点分治，对于每个分治中心，因为其有多个儿子，需要构造 $O(\log n)$ 个定向，所以总共询问数需要 $O(\log^2 n)$。

发现如果分治中心恰有 $2$ 个儿子，问题是简单的。所以尝试把所有节点分成两部分，分别视为两棵独立的子树。考虑重心的性质，容易证明存在一种划分子树的方式使得较大的一部分不超过树总节点数的 $\frac{2}{3}$。具体的，若最大子树超过 $\frac{1}{3}$，直接单独划出。否则依次加入子树，直到超过 $\frac{1}{3}$。这样构造的总定向数为 $2\log_{\frac{3}{2}}n$。

有一个常数优化是在进行确定 $s$ 和 $t$ 的操作时，因为已知 $s$ 和 $t$ 在同一个子树内，所以二分出其中一个后另一个的二分范围可以缩小。这样总的操作次数不会超过 $2\log_{\frac{3}{2}}n+\log_2 n$，可以通过。

[代码实现](https://atcoder.jp/contests/joisp2025/submissions/64858785)。

---

## 作者：Nangu (赞：4)

## 题意
给定一个联通无向图，你需要通过 $\le 70$ 次询问求出一组点对 $(a, b)$。对于一次询问，你需要为图中的每一条边定向，交互库会告诉你定向后 $a$ 是否可以到达 $b$。

## 题解

对于链的情况，假定 $a<b$，我们每次将左右端点都 $\le k$ 的边设为 $1$，则若此时 $a$ 仍能到达 $b$，有 $a\ge k$，$b$ 同理。通过二分即可求出 $a$，$b$，询问次数为 $2\log n$。

对于菊花图的情况，我们每次随机一半的边设为 $1$ 并询问，设此时可以到达 $0$ 的点集为 $S$，$0$ 可以到达的点集为 $T$。假设有一次询问返回 $1$，说明 $a$，$b$ 分别在 $S$，$T$ 内，然后就可以套用链的情况，每次将 $S$ 分成两个均匀的点集 $S1$ 和 $S2$，将 $S2$ 中的点与 $0$ 相连的边翻转并查询即可。询问次数期望为 $3\log n$。若将第一部分的随机点集询问改为用合并果子的方法进行询问即可将询问次数严格控制在 $3\log n$ 以内。

对于一般树的做法，我们先做一个点分治，然后即可套用菊花图的解法了。

具体地，设此时枚举中心为 $u$，我们将 $u$ 的儿子 $v$ 用合并果子的方法分成均匀的两部分 $S1$，$S2$，将 $S1$ 中的子树的边定向为父向边、叶向边，$S2$ 中子树的边定向为叶向边、父向边，两次询问后再向子树内递归即可。如果某次询问答案是 $1$，则再用 $2\log n$ 次询问二分点集求出答案即可。 

发现同一层内的所有询问是可以并行的，于是总共只要询问 $3\log n$ 次。

图与树的情况类似，我们只需要先拎出来一棵生成树，最后让每次询问定向后的图能形成一个有向无环图即可。

## 代码
```cpp
#include<bits/stdc++.h>
#include"thief.h"
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
using namespace std;
using pa=pair<int, int>;
const int N=3e4+7;
int n, m, fr[N], to[N], bel[N], cnt, nowdep;
vector<int> G[N], H[N];
void addedge(int u, int v){G[u].emplace_back(v), G[v].emplace_back(u);}
bool vis[N];
struct DAG{
  vector<int> G[N];
  int d[N];
  void init(int u, int v){++d[v], G[u].emplace_back(v);}
  vector<int> get(){
    vector<int> p(n+1, 0);
    queue<int> q;
    rep(i, 1, n) if(!d[i]) q.emplace(i);
    int cnt=0;
    while(!q.empty()){
      int u=q.front(); q.pop();
      p[u]=++cnt;
      for(auto v:G[u]) if(!--d[v]) q.emplace(v);
    }
    return p;
  }
}t[50];

void build_tree(int u){
  vis[u]=1;
  for(auto v:H[u]) if(!vis[v]){
    addedge(u, v);
    build_tree(v);
  }
}

int fa[N], siz[N], rt, mx[N], sum;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void findrt(int u, int pre){
  siz[u]=1, mx[u]=0;
  for(auto v:G[u]) if(!vis[v] && v!=pre)
    findrt(v, u), siz[u]+=siz[v], mx[u]=max(mx[u], siz[v]);
  mx[u]=max(mx[u], sum-siz[u]);
  if(!rt || mx[u]<mx[rt]) rt=u;
}

void getsiz(int u, int pre){
  siz[u]=1;
  for(auto v:G[u]) if(!vis[v] && v!=pre)
    getsiz(v, u), siz[u]+=siz[v];
}

void dfs(int u, int pre, int dep, bool flag){
  if(flag) t[dep].init(bel[pre], bel[u]);
  else t[dep].init(bel[u], bel[pre]);
  for(auto v:G[u]) if(!vis[v] && v!=pre)
    dfs(v, u, dep, flag);
}

void solve(int u, int dep){
  getsiz(u, 0), sum=siz[u];
  rt=0, findrt(u, 0), u=rt, getsiz(u, 0);
  vis[u]=1;
  priority_queue<pa, vector<pa>, greater<pa> > q;
  vector<int> son;
  for(auto v:G[u]) if(!vis[v]) q.emplace(siz[v], v), fa[v]=v, son.emplace_back(v);
  if(q.size()<=1){
    if(!q.empty()) t[dep].init(bel[u], bel[son[0]]);
    return;
  }
  while(q.size()>2){
    int u=q.top().second, x=q.top().first; q.pop();
    int v=q.top().second, y=q.top().first; q.pop();
    fa[u]=v; q.emplace(x+y, v), siz[v]=x+y;
  }
  int s1=q.top().second; q.pop(); int s2=q.top().second;
  cnt+=2, bel[cnt]=bel[cnt-1]=bel[u];
  for(auto v:son) 
    if(find(v)==s1) t[dep].init(bel[v], bel[u]), dfs(v, u, dep, 0), addedge(cnt-1, v);
    else t[dep].init(bel[u], bel[v]), dfs(v, u, dep, 1), addedge(cnt, v);
  solve(s1, dep+1), solve(s2, dep+1);
}

int Q(vector<int> &p){
  vector<int> x(m, 0);
  rep(i, 1, m) x[i-1]=p[fr[i]]>p[to[i]];
  return query(x);
}

void getans(vector<int> &p){
  vector<int> x(m, 0);
  int l=1, r=n, mid, s, t, u;
  while(l<=r){
    mid=l+r>>1;
    rep(i, 1, m) 
      if(p[fr[i]]<=mid || p[to[i]]<=mid) x[i-1]=p[fr[i]]<p[to[i]];
      else x[i-1]=p[fr[i]]>p[to[i]];
    if(!query(x)) s=mid, r=mid-1;
    else l=mid+1;
  }
  l=1, r=n;
  while(l<=r){
    mid=l+r>>1;
    rep(i, 1, m) 
      if(p[fr[i]]>=mid || p[to[i]]>=mid) x[i-1]=p[fr[i]]<p[to[i]];
      else x[i-1]=p[fr[i]]>p[to[i]];
    if(!query(x)) t=mid, l=mid+1;
    else r=mid-1;
  }
  rep(i, 1, n) if(p[i]==s){s=i; break;}
  rep(i, 1, n) if(p[i]==t){t=i; break;}
  answer(s-1, t-1);
}

void run(){
  cnt=n;
  rep(i, 1, m) H[fr[i]].emplace_back(to[i]), H[to[i]].emplace_back(fr[i]);
  build_tree(1);
  rep(i, 1, n) vis[i]=0, bel[i]=i;
  solve(1, 1);
  rep(_, 1, 40){
    vector<int> p=t[_].get();
    if(Q(p)) return getans(p);
    for(auto &x:p) x=n-x+1;
    if(Q(p)) return getans(p);
  }
}

void solve(int n, int m, vector<int> u, vector<int> v){
  ::n=n, ::m=m;
  rep(i, 1, m) fr[i]=u[i-1]+1, to[i]=v[i-1]+1;
  run();
}
```
### 写在最后

感谢 sjy 老师为笔者细致地讲解了这道题，这里强烈安利他的[这篇](https://www.cnblogs.com/Rainbowsjy/p/18795134)博客，里面有这次 JOIST 几乎所有题的题解喵。

~~另外，都看到这里了，点个赞再走呗。~~

---

## 作者：Sio_ (赞：0)

先考虑菊花怎么做，你要不漏的计算每个点对就是二进制拆分一下，每次把当前位为 $0$ 的儿子指向父亲，把为 $1$ 的儿子被父亲指向，然后倒过来再做一遍。

我们再考虑一下无向图怎么做，只要我们找到了一个拓扑序使得按该拓扑序连边能从 $a$ 到达 $b$，那么我们就能二分出左右端点，因为你从 $a$ 走到 $b$ 肯定只会经过左右端点都在拓扑序在 $[p_a,p_b]$ 之间的点。

随便拉一颗生成树是肯定可以找到一个从 $a$ 走到 $b$ 的拓扑序的，我们考虑拉一颗生成树来找到这个拓扑序。

这种东西一看就是要你点分治一下。你传统的点分治是每个点都有若干个儿子，然后套用一下菊花的做法，导致你分治一次就要 $\log_2 n$ 次，总共就是 $\log^2n$ 次。

但是这个世界上还有一种点分治。考虑重心的性质，我们一定可以把子树分为两个集合 $S,T$，使得这两个集合子树大小都在 $[\frac {siz} 3,\frac {2siz} 3]$ 这个范围内。这是容易证明的，你直接从小到大加入，如果加入当前子树正好大于 $\frac {siz} 3$ 你就停止。

这是个很好的性质，也就是说我们把重心的儿子数量降为了两个，我们分治一次只需要 $2$ 次操作。然后你就可以分治 $S \cup \{root\},T \cup \{root\}$，易发现这两个子树互不影响，他们只共点而不共边，所以我们并行分治即可。

操作次数大概是 $2 \log _{\frac 3 2}n + 2 \log_2 n$，但是他实际操作次数很少。

```cpp
// #include "thief.h"
#include<bits/stdc++.h>
using namespace std;
#include <vector>
int query(std::vector<int>);
void answer(int,int);
const int maxn=30005;
int n,m,vis[maxn],use[maxn],c[maxn];
pair<int,int> fa[maxn];
vector<pair<int,int>> e[maxn],nbr[maxn],tree[maxn];
vector<int> u,v;
int rev(int x){if(x<m) return x+m;return x-m;}
void dfs(int cur)
{
    vis[cur]=1;
    // cout<<cur<<"\n";
    for(auto [x,id]:e[cur])
        if(vis[x]==0)
        {
            use[(id<m)?id:id-m]=1,fa[x]={cur,rev(id)},dfs(x);
            nbr[cur].push_back({x,id});
            nbr[x].push_back({cur,rev(id)});
            // cout<<cur<<' '<<x<<"!\n";
        }
}
struct QUERY
{
    vector<int> tmp[maxn];
    int p[maxn],in[maxn],P[maxn];
    int myquery()
    {
        vector<int> ans;
        ans.resize(m);
        for(int i=1;i<=n;i++) tmp[i].clear(),in[i]=0;
        for(int i=0;i<m;i++)
        {
            if(use[i]==0) continue;
            if(c[i]==1) tmp[u[i]].push_back(v[i]),in[v[i]]++;
            else tmp[v[i]].push_back(u[i]),in[u[i]]++;
        }
        queue<int> q;
        int tot=0;
        for(int i=1;i<=n;i++) if(in[i]==0) q.push(i);
        // exit(0);
        while(!q.empty())
        {
            int x=q.front();q.pop();p[++tot]=x,P[x]=tot;
            for(auto son:tmp[x]){in[son]--;if(in[son]==0) q.push(son);}
        }
        for(int i=0;i<m;i++) ans[i]=(P[u[i]]>P[v[i]]);
        // for(auto x:ans) cout<<x;cout<<"\n";
        return query(ans);
    }
    int rev(int l,int r)
    {
        vector<int> ans;
        ans.resize(m);
        for(int i=0;i<m;i++) ans[i]=(P[u[i]]>P[v[i]])^(!(l<=P[v[i]]&&P[v[i]]<=r&&l<=P[u[i]]&&P[u[i]]<=r));
        return query(ans);
    }
}Q;
int flag[maxn],root,siz[maxn];
void find_heavy(int cur,int n)
{
    // cout<<cur<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    int maxi=0;
    siz[cur]=1,flag[cur]=0;
    for(auto [son,id]:tree[cur]) 
    {
        // cout<<son<<"&&&&\n";
        if(flag[son]==1) find_heavy(son,n),siz[cur]+=siz[son],maxi=max(maxi,siz[son]);
    }
    maxi=max(maxi,n-siz[cur]);
    // cout<<maxi<<" "<<n<<"!!!\n";
    if(maxi<=n/2) root=cur;
}
void getsiz(int cur)
{
    siz[cur]=1,flag[cur]=0;
    for(auto [son,id]:tree[cur]) 
        if(flag[son]==1) getsiz(son),siz[cur]+=siz[son];
}
void getson(int cur,vector<int> &x,int opt)
{
    flag[cur]=0,x.push_back(cur);
    // cout<<cur<<" "<<opt<<"!!!\n";
    for(auto [son,id]:tree[cur])
        if(flag[son]==1) getson(son,x,opt),c[id]=opt,c[rev(id)]=opt^1;
}
bool cmp(pair<int,int> x,pair<int,int> y){return siz[x.first]<siz[y.first];}
void solve(int N,int M,vector<int> U,vector<int> V)
{
    n=N,m=M;
    for(int i=0;i<U.size();i++)
    {
        U[i]++,V[i]++;
        int x=U[i],y=V[i];
        e[x].push_back({y,i});
        e[y].push_back({x,i+m});
        // cout<<x<<" "<<y<<"!!\n";
    }
    u=U,v=V,dfs(1);
    vector<int> tmp;
    for(int i=1;i<=n;i++) tmp.push_back(i);
    vector<vector<int>> S={tmp};
    int tot=0;
    while(1)
    {
        tot++;
        // if(tot==5) break;
        vector<vector<int>> T;
        for(auto v:S)
        {
            for(auto pos:v) flag[pos]=1,tree[pos].clear();
            for(auto pos:v)
            {
                if(flag[fa[pos].first]==0) continue;
                tree[pos].push_back(fa[pos]);
                tree[fa[pos].first].push_back({pos,rev(fa[pos].second)});
            }
            find_heavy(v.front(),v.size());
            for(auto pos:v) flag[pos]=1;
            getsiz(root);
            for(auto pos:v) flag[pos]=1;
            sort(tree[root].begin(),tree[root].end(),cmp);
            vector<int> opt;
            opt.resize(tree[root].size());
            int sum=0;
            for(int i=0;i<tree[root].size();i++)
            {
                int x=tree[root][i].first;
                if(flag[x]==0) continue;
                sum+=siz[x],opt[i]=1;
                if(sum>=ceil(1.0*(v.size()-1)/3)) break;
            }
            vector<int> a={root},b={root};
            flag[root]=0;
            for(int i=0;i<tree[root].size();i++)
            {
                if(flag[tree[root][i].first]==0) continue;
                if(opt[i]==0) getson(tree[root][i].first,a,0);
                else getson(tree[root][i].first,b,1);
                c[tree[root][i].second]=opt[i];
                c[rev(tree[root][i].second)]=opt[i]^1;
            }
            // cout<<v.size()<<" "<<a.size()<<" "<<b.size()<<endl;
            // assert(a.size()<=2*ceil(1.0*(v.size()-1)/3)+1);
            // assert(b.size()<=2*ceil(1.0*(v.size()-1)/3)+1);
            // assert(a.size()+b.size()<=v.size()+1);
            T.push_back(a),T.push_back(b);
        }
        // cout<<endl; 
        // for(int i=0;i<m;i++) cout<<c[i];cout<<"\n";
        if(Q.myquery()==1) break;
        for(int i=0;i<m;i++) c[i]^=1;
        if(Q.myquery()==1) break;
        S=T;
    }
    int l=0,r=n+1;
    while(l+1<r)
    {
        int mid=(l+r)/2;
        if(Q.rev(1,mid)==1) r=mid;
        else l=mid;
    }
    int rt=r;
    l=0,r=n+1;
    while(l+1<r)
    {
        int mid=(l+r)/2;
        if(Q.rev(mid,rt)==1) l=mid;
        else r=mid;
    }
    // cout<<l<<" "<<rt<<"\n";
    answer(Q.p[l]-1,Q.p[rt]-1);
}
```

---

