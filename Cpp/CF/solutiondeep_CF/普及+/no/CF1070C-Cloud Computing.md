# 题目信息

# Cloud Computing

## 题目描述

$\text{Buber}$ 是一家致力于浪费投资者的钱的 $\text{Berland}$ 技术公司。最近，$\text{Buber}$ 决定将他的设施转移到云端。公司决定连续$\ n\ $天云端租用$\text{CPU}$。$\text{Buber}$每天都要租用$\ k\ $个$\text{CPU}$。



云端供应商提供$\ m\ $个租用计划，第$i$个计划有如下的特征：



- $l_i,r_i$ 表示第$\ i\ $个计划从第$\ l_i\ $天开始，第$\ r_i\ $天结束。

- $c_i$ 表示第$\ i\ $个计划中，每天最多租用$\text{CPU}$个数。

- $p_i$ 表示第$\ i\ $个计划中，租用一个$\text{CPU}$一天的花费。



$\text{Buber}$ 可以同时使用多个计划，即他可以在第$\ x\ $天在每个进行中的计划（即$l_i≤x≤r_i$）中租用 $[0,c_i]$个$\text{CPU}$.



现在$\text{Buber}$告诉你正整数$\ k\ $，表示每天所需的$\text{CPU}$个数（如果某一天无论怎么租用都不能租到$\ k\ $个，他也希望租尽量多的$\text{CPU}$）。请你告诉他，他在这$\ n\ $天中最少需要花费多少钱来租用$\text{CPU}$？

## 样例 #1

### 输入

```
5 7 3
1 4 5 3
1 3 5 2
2 5 10 1
```

### 输出

```
44
```

## 样例 #2

### 输入

```
7 13 5
2 3 10 7
3 5 10 10
1 2 10 6
4 5 10 9
3 4 10 8
```

### 输出

```
462
```

## 样例 #3

### 输入

```
4 100 3
3 3 2 5
1 1 3 2
2 4 4 4
```

### 输出

```
64
```

# AI分析结果

### 题目内容
# 云计算

## 题目描述
Buber是一家致力于浪费投资者资金的Berland技术公司。最近，Buber决定将其设施转移到云端。公司决定连续$n$天在云端租用CPU。Buber每天都要租用$k$个CPU。

云端供应商提供$m$个租用计划，第$i$个计划具有以下特征：
- $l_i$，$r_i$表示第$i$个计划从第$l_i$天开始，到第$r_i$天结束。
- $c_i$表示第$i$个计划中，每天最多可租用的CPU个数。
- $p_i$表示第$i$个计划中，租用一个CPU一天的花费。

Buber可以同时使用多个计划，即在第$x$天，他可以在每个正在进行的计划（即$l_i \leq x \leq r_i$）中租用$[0, c_i]$个CPU。

现在Buber告诉你正整数$k$，表示每天所需的CPU个数（如果某一天无论怎么租用都无法租到$k$个，他也希望租尽量多的CPU）。请你告诉他，在这$n$天中最少需要花费多少钱来租用CPU？

## 样例 #1
### 输入
```
5 7 3
1 4 5 3
1 3 5 2
2 5 10 1
```
### 输出
```
44
```

## 样例 #2
### 输入
```
7 13 5
2 3 10 7
3 5 10 10
1 2 10 6
4 5 10 9
3 4 10 8
```
### 输出
```
462
```

## 样例 #3
### 输入
```
4 100 3
3 3 2 5
1 1 3 2
2 4 4 4
```
### 输出
```
64
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是利用数据结构维护每天可租用CPU的信息，并通过贪心策略选择价格最优的CPU。主要难点在于如何高效地处理动态变化的租用计划以及快速计算每天的最小花费。多数题解使用权值线段树或树状数组来维护CPU的价格和数量信息，将租用计划的开始和结束时间转化为差分形式，通过单点修改和区间查询来计算每天的花费。不同之处在于具体的数据结构实现细节和查询方式。

### 所选的题解
- **作者：StayAlone (5星)**
    - **关键亮点**：思路清晰，详细阐述线段树维护的信息及操作过程，代码实现简洁明了，对时间复杂度分析准确。
    - **个人心得**：作者提到是自己思考得出的解法，因上课没听讲且看不懂题解，锻炼了自身思考能力。
    - **重点代码核心思想**：用线段树维护价值在某区间内的物品数量之和`cnt`与全部租完所需代价`sum`，通过`pushup`函数合并子节点信息。`upd`函数实现单点修改，`query`函数用于查询区间信息，`kth`函数查找第`k`贵的代价，`get`函数计算当天花费。
    - **核心代码片段**：
```cpp
struct setr
{
    ll cnt, sum;
} t[MAXN << 2];

il void pushup(int x)
{
    t[x].cnt = t[ls(x)].cnt + t[rs(x)].cnt;
    t[x].sum = t[ls(x)].sum + t[rs(x)].sum;
}

il void upd(int x, int l, int r, int k, int num)
{
    if (l > k || r < k) return;
    if (l == r && r == k) return t[x].cnt += num, t[x].sum = t[x].cnt * l, void();
    int mid = l + r >> 1;
    upd(ls(x), l, mid, k, num); upd(rs(x), mid + 1, r, k, num);
    pushup(x);
}

il ll query(int x, int l, int r, int ql, int qr, bool h)
{
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return h? t[x].cnt : t[x].sum;
    int mid = l + r >> 1;
    return query(ls(x), l, mid, ql, qr, h) + query(rs(x), mid + 1, r, ql, qr, h);
}

il int kth(int x, int l, int r, int k)
{
    if (l == r) return l;
    int mid = l + r >> 1;
    if (k <= t[ls(x)].cnt) return kth(ls(x), l, mid, k);
    return kth(rs(x), mid + 1, r, k - t[ls(x)].cnt);
}

il ll get()
{
    ll all = t[1].cnt;
    if (all <= k) return query(1, 1, T, 1, T, 0);
    int k_0th = kth(1, 1, T, k);
    ll k1num = query(1, 1, T, 1, k_0th - 1, 1);
    return query(1, 1, T, 1, k_0th - 1, 0) + (k - k1num) * k_0th;
}
```
- **作者：WaterSun (4星)**
    - **关键亮点**：对思路阐述详细，代码结构清晰，注释丰富，易于理解。
    - **重点代码核心思想**：线段树维护价格在某区间内CPU的数量和购买所需的钱。`build`函数构建线段树，`modify`函数实现单点修改，`query_kth`查找第`k`小的值，`query_cnt`和`query_sum`分别查询区间内CPU数量和总价，`get`函数计算当天花费。
    - **核心代码片段**：
```cpp
struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int cnt,sum;
    }tr[N << 2];

    inline void pushup(int u){
        tr[u].cnt = tr[ls(u)].cnt + tr[rs(u)].cnt;
        tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid),build(rs(u),mid + 1,r);
    }

    inline void modify(int u,int x,int k){
        if (tr[u].l == x && tr[u].r == x){
            tr[u].cnt += k;
            tr[u].sum = tr[u].cnt * x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x,k);
        if (x > mid) modify(rs(u),x,k);
        pushup(u);
    }

    inline int query_kth(int u,int k){
        if (tr[u].l == tr[u].r) return tr[u].l;
        if (tr[ls(u)].cnt < k) return query_kth(rs(u),k - tr[ls(u)].cnt);
        else return query_kth(ls(u),k);
    }

    inline int query_cnt(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].cnt;
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query_cnt(ls(u),l,r);
        if (r > mid) res += query_cnt(rs(u),l,r);
        return res;
    }

    inline int query_sum(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query_sum(ls(u),l,r);
        if (r > mid) res += query_sum(rs(u),l,r);
        return res;
    }

    inline int get(){
        if (tr[1].cnt <= k) return tr[1].sum;
        int kth = query_kth(1,k);
        int rk = query_cnt(1,1,kth - 1);
        return query_sum(1,1,kth - 1) + (k - rk) * kth;
    }

    #undef ls
    #undef rs
}T;
```
- **作者：绝顶我为峰 (4星)**
    - **关键亮点**：提出使用树状数组和倍增优化来解决问题，提供了不同于线段树的思路，复杂度分析清晰。
    - **重点代码核心思想**：用树状数组`cnt`维护每种价值的物品个数，`val`维护价值总和。`update`函数实现树状数组单点更新，`query1`和`query2`分别查询数量和价值前缀和。通过倍增找到全选部分的权值最大值，再结合`set`计算剩余部分贡献。
    - **核心代码片段**：
```cpp
inline void update(int x,int val1,int val2)
{
    for(;x<=maxn;x+=lowbit(x))
    {
        cnt[x]+=val1;
        val[x]+=val2;
    }
}
inline int query1(int x)
{
    int res=0;
    for(;x;x-=lowbit(x))
        res+=cnt[x];
    return res;
}
inline int query2(int x)
{
    int res=0;
    for(;x;x-=lowbit(x))
        res+=val[x];
    return res;
}
//...
int pos=0,tmp=0,val=0,v=0;
for(int j=20;~j;--j)
{
    tmp=pos|(1<<j);
    if(tmp>maxn)
        continue;
    v=val+cnt[tmp];
    if(v>k)
        continue;
    val=v;
    pos=tmp;
}
ans+=query2(pos);
if(val==k)
    continue;
int num=*s.upper_bound(pos);
ans+=num*(k-val);
```

### 最优关键思路或技巧
利用权值线段树或树状数组维护CPU的价格和数量信息，通过差分将租用计划转化为单点修改，在每天计算花费时采用贪心策略，优先选择价格低的CPU，若数量不足则全选。这种方法有效利用数据结构的特性，优化了动态数据处理和查询的效率。

### 可拓展思路
此类题目可拓展到其他资源分配场景，同样涉及动态变化的资源供应和固定的资源需求，都可尝试使用类似的数据结构和贪心策略。例如任务调度中，不同时间段有不同的任务资源需求，同时存在多种资源供应方案，需选择最优方案满足任务需求并最小化成本。

### 推荐洛谷题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：涉及区间选择和贪心策略，与本题在区间处理和贪心思想上有相似之处。
- [P2893 [USACO08FEB] Making the Grade G](https://www.luogu.com.cn/problem/P2893)：通过对数据进行处理和贪心选择来解决问题，锻炼贪心思维和数据处理能力。
- [P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)：需要合理运用贪心策略对数据进行排序和计算，与本题在贪心思路运用上有共通点。 

---
处理用时：109.14秒