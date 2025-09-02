# 题目信息

# Bandit in a City

## 题目描述

Bandits appeared in the city! One of them is trying to catch as many citizens as he can.

The city consists of $ n $ squares connected by $ n-1 $ roads in such a way that it is possible to reach any square from any other square. The square number $ 1 $ is the main square.

After Sunday walk all the roads were changed to one-way roads in such a way that it is possible to reach any square from the main square.

At the moment when the bandit appeared on the main square there were $ a_i $ citizens on the $ i $ -th square. Now the following process will begin. First, each citizen that is currently on a square with some outgoing one-way roads chooses one of such roads and moves along it to another square. Then the bandit chooses one of the one-way roads outgoing from the square he is located and moves along it. The process is repeated until the bandit is located on a square with no outgoing roads. The bandit catches all the citizens on that square.

The bandit wants to catch as many citizens as possible; the citizens want to minimize the number of caught people. The bandit and the citizens know positions of all citizens at any time, the citizens can cooperate. If both sides act optimally, how many citizens will be caught?

## 说明/提示

In the first example the citizens on the square $ 1 $ can split into two groups $ 2 + 1 $ , so that the second and on the third squares will have $ 3 $ citizens each.

In the second example no matter how citizens act the bandit can catch at least $ 4 $ citizens.

## 样例 #1

### 输入

```
3
1 1
3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 1
3 1 3```

### 输出

```
4```

# AI分析结果

### 题目翻译
# 城市中的强盗

## 题目描述
城市中出现了强盗！其中一个强盗试图尽可能多地抓捕市民。

这座城市由 $n$ 个广场通过 $n - 1$ 条道路连接而成，使得从任何一个广场都可以到达其他任何一个广场。1 号广场是主广场。

在周日散步之后，所有的道路都变成了单行道，使得从主广场可以到达任何一个广场。

当强盗出现在主广场时，第 $i$ 个广场上有 $a_i$ 个市民。现在，以下过程将开始。首先，当前位于有单行道出口的广场上的每个市民选择其中一条道路并沿着它移动到另一个广场。然后，强盗选择一条从他所在广场出发的单行道并沿着它移动。这个过程会一直重复，直到强盗位于一个没有单行道出口的广场上。强盗会抓住那个广场上的所有市民。

强盗想要抓住尽可能多的市民；市民们想要使被抓住的人数最少。强盗和市民们在任何时候都知道所有市民的位置，市民们可以合作。如果双方都采取最优行动，会有多少市民被抓住？

## 说明/提示
在第一个样例中，1 号广场上的市民可以分成两组，2 人和 1 人，这样第二个和第三个广场上就各有 3 个市民。

在第二个样例中，无论市民们如何行动，强盗至少可以抓住 4 个市民。

## 样例 #1
### 输入
```
3
1 1
3 1 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
1 1
3 1 3
```
### 输出
```
4
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何解决在给定树形结构中，将节点上的权值分配到叶子节点，使得叶子节点中最大权值最小的问题。主要有二分和树形 DP 两种思路。

- **二分思路**：通过二分一个上界，然后 `check` 该上界是否可行。难点在于处理数据溢出问题，不同题解采用了不同的优化方法，如调整上界、使用 `unsigned long long` 等。
- **树形 DP 思路**：定义状态，通过状态转移方程计算以每个节点为根的子树中最大叶子节点的最小值。关键在于考虑理想状态下的均分情况以及实际可能无法均分的情况。

### 所选题解
- **作者：Sqrtyz (赞：10)，4星**
    - **关键亮点**：思路清晰，对题意简化和解题步骤的阐述很详细，代码结构清晰。
    - **核心实现思想**：定义 $f_u$ 表示以 $u$ 为根的子树中最大叶子节点的的最小值，通过状态转移方程 $f_u = \max \left(\max_{v \in son(u)} f_v, \left\lceil\frac{siz_u}{leaf_u}\right\rceil\right)$ 计算结果。
    - **核心代码**：
```cpp
int n;
LL val[Maxn], siz[Maxn], f[Maxn], leaf[Maxn];

struct Edge {
    int next, to;
} edge[Maxn];
int head[Maxn], edge_num;

void add_edge(int from, int to) {
    edge[++edge_num].next = head[from];
    edge[edge_num].to = to;
    head[from] = edge_num;
}

void dfs(int u) {
    bool flag = 1;
    for(int i = head[u]; i; i = edge[i].next) dfs(edge[i].to), flag = 0;
    if(flag) leaf[u] = 1; siz[u] = val[u];
    for(int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        f[u] = max(f[v], f[u]);
        siz[u] += siz[v]; leaf[u] += leaf[v];
    }
    f[u] = max(f[u], (siz[u] + leaf[u] - 1) / leaf[u]); // 注意向上取整
}

int main() {
    n = read();
    for(int i = 2; i <= n; ++i) {
        int fa = read();
        add_edge(fa, i);
    }
    for(int i = 1; i <= n; ++i) val[i] = read();
    dfs(1);
    cout << f[1] << endl;
    return 0;
}
```
- **作者：灵乌路空 (赞：3)，4星**
    - **关键亮点**：对知识点和状态转移方程的分析很详细，时间复杂度分析清晰。
    - **核心实现思想**：设 $\operatorname{sum}_{u}$ 表示 $u$ 子树中所有节点的人数之和，$\operatorname{leaf}_u$ 表示 $u$ 子树中叶节点的个数，$f_{u}$ 表示以 $u$ 为根的子树中人最多的叶节点的人数，通过状态转移方程 $f_{u} = \max\left\{ \max_{v\in son(u)}\{f_v\},\  \left\lceil \frac{\operatorname{sum}_u}{\operatorname{leaf}_u} \right\rceil\right\}$ 计算结果。
    - **核心代码**：
```cpp
//知识点：树形DP 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#define LL long long
const int kN = 2e5 + 10;
//=============================================================
int n, e_num, a[kN], head[kN], v[kN], ne[kN];
LL leaf[kN], sum[kN], f[kN];
bool fa[kN];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) {
    w = (w << 3) + (w << 1) + (ch ^ '0');
  }
  return f * w;
}
void Chkmax(LL &fir_, LL sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void Chkmin(LL &fir_, LL sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
void AddEdge(int u_, int v_) {
  v[++ e_num] = v_;
  ne[e_num] = head[u_];
  head[u_] = e_num;
}
void Dfs(int u_) {
  if (! fa[u_]) leaf[u_] = 1;
  sum[u_] = a[u_];
  
  for (int i = head[u_]; i; i = ne[i]) {
    int v_ = v[i];
    Dfs(v_);
    Chkmax(f[u_], f[v_]);
    sum[u_] += sum[v_];
    leaf[u_] += leaf[v_];
  }
  Chkmax(f[u_], ceil(1.0 * sum[u_] / leaf[u_]));
}
//=============================================================
int main() {
  n = read();
  for (int v_ = 2; v_ <= n; ++ v_) {
    int u_ = read();
    AddEdge(u_, v_);
    fa[u_] = true;
  }
  for (int i = 1; i <= n; ++ i) a[i] = read();
  Dfs(1);
  printf("%lld\n", f[1]);
  return 0;
}
```
- **作者：Fairicle (赞：0)，4星**
    - **关键亮点**：对思路的阐述清晰，明确指出可能无法做到平均的情况，并给出了相应的处理方法。
    - **核心实现思想**：维护子树和 $sum[x]$，子树叶子数 $lf[x]$，子树最大值 $mx[x]$，通过状态转移方程 $mx[x]=max(mx[y](y\in son(x)),\left\lceil\dfrac{sum[x]}{lf[x]}\right\rceil)$ 计算结果。
    - **核心代码**：
```cpp
#define ll long long
#define ri register int
#define N 200010
ll wl,n,a[N],x,y,head[N],lf[N],sum_lf[N],mx_lf[N];
struct node{
    int nxt,to;
}star[N];
inline void add(int from,int to){
    wl++;
    star[wl].to=to;
    star[wl].nxt=head[from];
    head[from]=wl;
}
inline void dfs(int x,int fa){
    if(!head[x]){
        lf[x]++,sum_lf[x]=a[x],mx_lf[x]=max(mx_lf[x],a[x]);
        return;
    }
    sum_lf[x]=a[x];
    for(ri i=head[x];i;i=star[i].nxt){
        int u=star[i].to;
        dfs(u,x);
        lf[x]+=lf[u];
        sum_lf[x]+=sum_lf[u];
        mx_lf[x]=max(mx_lf[x],mx_lf[u]);
    }
    ll ave=(sum_lf[x]+lf[x]-1)/lf[x];
    if(ave>mx_lf[x]) mx_lf[x]=ave;
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(ri i=1;i<n;++i){
        int s;
        cin>>s;
        add(s,i+1);
    }
    for(ri i=1;i<=n;++i) cin>>a[i];
    dfs(1,0);
    cout<<mx_lf[1];
    return 0;
}
```

### 最优关键思路或技巧
- **树形 DP 思路**：通过定义合适的状态和状态转移方程，利用深度优先搜索遍历树，计算以每个节点为根的子树中最大叶子节点的最小值。
- **二分思路**：二分答案，通过 `check` 函数判断当前答案是否可行，注意处理数据溢出问题。

### 可拓展之处
同类型题或类似算法套路：
- 其他树形 DP 问题，如树上背包问题、树的重心问题等。
- 二分答案结合 `check` 函数的问题，如最小化最大值、最大化最小值等问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：经典的树形 DP 问题。
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)：树上背包问题，需要运用树形 DP 解决。
- [P1084 疫情控制](https://www.luogu.com.cn/problem/P1084)：二分答案结合 `check` 函数的问题。

### 个人心得摘录与总结
- **tommymio**：二分做法在溢出上被卡，但正确性没问题，可以考虑特判一些情况，调大数据类型的极限范围来保证 $\text{AC}$，考场上没时间想正解时这些技巧很实用。
- **haooo**：考试时因为没开 `long long` 送了 100 分，提醒做题时要注意数据类型。
- **kradcigam**：二分答案时，上界设太大可能会爆掉，尝试手动设上界和使用 `unsigned long long` 解决问题。

---
处理用时：82.38秒