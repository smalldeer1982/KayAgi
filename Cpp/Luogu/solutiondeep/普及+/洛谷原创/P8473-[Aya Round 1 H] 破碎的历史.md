# 题目信息

# [Aya Round 1 H] 破碎的历史

## 题目背景

幻想乡迎来了它的毁灭，幻想的载体也已经遁入了幻想。

所幸的是，幻想乡中的乡民们还侥幸存活着，她们在尝试恢复幻想乡的历史。然而历史之中的大大小小的事情不计其数，人们只能记得起一些大事情罢了。

或许，根据那些重要的事情，可以把次要的事件推导出来呢？

## 题目描述

数轴的正半轴上有 $n$ 个互不相同的被黑白染色的特殊整点，位置从左到右依次为 $p_1,p_2,\cdots,p_n$。维护初始为空的**可重**线段集合 $S$。

$q$ 次操作。操作分若干种，具体格式如下：

- `1 l r`：将所有满足 $l \le x \le y \le r$ 且两端点均为特殊整点的线段 $[x,y]$ 加入 $S$。
- `2 x`：撤回第 $x$ 次操作添加的线段。

在初始时和每次操作后，假设你可以进行任意次（可以是零次）染色。每次从 $S$ 中选出一条线段 $[x,y]$，满足位于点 $x$ 和点 $y$ 的特殊整点均为黑色，然后将所有在线段内的白色特殊整点染黑。试判断是否存在至少一种合法染色方式使得正半轴上的所有特殊整点均被染黑（即，不存在白色特殊整点）。**注意：所有的询问均为「假设」，即各组询问之间独立，不会造成对数轴的实际修改。**


## 说明/提示

### 样例解释

六个特殊点的位置/颜色在数轴正半轴上如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/i1hfjrk8.png)

容易发现，并非所有点都是黑点。因此在进行操作前，输出 $\verb!NO!$。

第一次操作后，一共往 $S$ 加入了三条线段：$[5,5],[8,8],[5,8]$（图中省略了端点重叠的线段）。容易发现，此时无法进行任何操作，因此没法将所有点变成黑点。输出 $\verb!NO!$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ayeijyli.png)

第二次操作后，又往 $S$ 中加入了 $20$ 条线段。除去端点重叠的选段，在 $S$ 中如图所示。（以示区别，上一次操作加入的边标成了深蓝色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/icw9ar9m.png)

可以找出一种方案，将图上所有特殊点变成黑点。具体而言，首先选择 $S$ 中 $[1,5]$ 线段（容易发现位于 $1$ 和 $5$ 的特殊点均为黑点，因此可以进行染色），那么可以把位于 $2$ 和 $3$ 的点染色。

![](https://cdn.luogu.com.cn/upload/image_hosting/3k1uvul0.png)

此时又可以选择 $S$ 中 $[3,13]$ 线段（在上一轮操作中，$3$ 号点变为了黑点，因此 $[3,13]$ 符合条件），将点 $8$ 染为黑色。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ebafj63.png)

此时所有点都为黑色，因此输出 $\verb!YES!$。再次强调，询问之间互相独立，且只是询问是否存在染色方案，而不会对特殊整点进行实际上的染色操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/pjqpqvtr.png)

第三个操作撤回了第二个操作往 $S$ 里加入的所有线段。因此退回到了只有第一个操作的情况。不存在一种方案将所有点染黑，因此输出 $\verb!NO!$。

### 数据范围

对于所有数据，$1 \le n,q \le 5 \times 10^5$，$a_i \in \{0,1\}$，$1 \le l< r \le 10^9$，$1 \le p_i \le 10^9$。保证 $p_i$ 单调递增，$2$ 操作撤销的只会是 $1$ 操作，且每个操作最多被撤销一次。


## 样例 #1

### 输入

```
6 3
1 2 3 5 8 13
1 0 0 1 0 1
1 5 10
1 1 15
2 2
```

### 输出

```
No
No
Yes
No```

# AI分析结果

### 综合分析与结论
这三道题解思路相近，均利用线段树维护区间信息，通过分析操作特点简化问题。要点在于将操作转化为对线段树的区间修改与查询，难点是找出每次操作中真正有用的线段（即两端为黑点的最长线段）。
1. **jjsnam题解**：详细阐述思路，从分析题目到确定用线段树维护，对每个细节如查找两端黑点、线段树操作等都有说明，代码注释详尽，思路清晰，代码可读性高。
2. **chen_zhe题解**：简洁概括思路，指出关键要点，代码实现简洁明了，但对思路展开阐述不如jjsnam题解详细。
3. **Micnation_AFO题解**：同样清晰表述思路和实现方式，代码结构完整，但在思路分析和代码注释方面略逊于前两者。

综合来看，jjsnam题解质量最高，其次是chen_zhe题解，Micnation_AFO题解相对稍弱。

### 所选的题解
- **jjsnam题解**：★★★★★
    - **关键亮点**：思路阐述细致，对每个操作和线段树维护细节都有清晰说明，代码注释详细，便于理解。
    - **个人心得**：考试时因忽略每次输出导致误以为题目难度大，考试后恍然大悟，强调基础的重要性。
```cpp
// 核心代码片段：线段树操作
void pushup(int id){
    tr[id].mn = min(tr[ls].mn, tr[rs].mn);
}

void build(int id, int l, int r){
    if (l == r){
        tr[id].mn = a[l];
        return;
    }
    build(ls, l, mid),
    build(rs, mid+1, r);
    pushup(id);
}

void pushdown(int id){
    if (tr[id].lazy){
        tr[ls].lazy += tr[id].lazy;
        tr[rs].lazy += tr[id].lazy;
        tr[ls].mn += tr[id].lazy;
        tr[rs].mn += tr[id].lazy;
        tr[id].lazy = 0;
    }
}

void update(int id, int l, int r, int a, int b, int v){
    if (a <= l && r <= b){
        tr[id].mn += v;
        tr[id].lazy += v;
        return;
    }
    pushdown(id);
    if (a <= mid) update(ls, l, mid, a, b, v);
    if (b > mid) update(rs, mid+1, r, a, b, v);
    pushup(id);
}

int query(int id, int l, int r, int a, int b){
    if (a <= l && r <= b){
        return tr[id].mn;
    }
    pushdown(id);
    int res = 1e9;
    if (a <= mid) res = min(res, query(ls, l, mid, a, b));
    if (b > mid) res = min(res, query(rs, mid+1, r, a, b));
    return res;
}
```
- **chen_zhe题解**：★★★★
    - **关键亮点**：简洁明了地阐述思路，快速抓住问题关键，代码实现简洁高效。
```cpp
// 核心代码片段：线段树操作
inline void Push_Up(int id)
{
    t[id].val=min(t[id<<1].val,t[id<<1|1].val);
}

inline void Push_Down(int id)
{
    if (t[id].tag)
    {
        t[id<<1].val+=t[id].tag;
        t[id<<1|1].val+=t[id].tag;
        t[id<<1].tag+=t[id].tag;
        t[id<<1|1].tag+=t[id].tag;
        t[id].tag=0;
    }
}

inline void Build(int id,int l,int r)
{
    t[id].l=l;
    t[id].r=r;
    if (l==r)
    {
        t[id].val=(col[l]?1<<30:0);
        return;
    }
    int mid=(l+r)>>1;
    Build(id<<1,l,mid);
    Build(id<<1|1,mid+1,r);
    Push_Up(id);
}

inline void Change(int id,int l,int r,int val)
{
    if (l<=t[id].l && t[id].r<=r)
    {
        t[id].tag+=val;
        t[id].val+=val;
        return;
    }
    Push_Down(id);
    int mid=(t[id].l+t[id].r)>>1;
    if (r<=mid)
        Change(id<<1,l,r,val);
    else if (l>mid)
        Change(id<<1|1,l,r,val);
    else
    {
        Change(id<<1,l,mid,val);
        Change(id<<1|1,mid+1,r,val);
    }
    Push_Up(id);
}

inline int Query()
{
    return t[1].val;
}
```

### 最优关键思路或技巧
1. **数据结构选择**：利用线段树维护特殊点的染色状态，通过区间修改和查询判断是否所有点可被染黑。
2. **操作简化**：分析得出每次操作1中，只有两端为黑点的最长线段对结果有影响，简化操作处理。
3. **二分查找**：使用`lower_bound`和`upper_bound`（或类似二分方式）快速找到操作区间内最靠近边界的黑点。

### 可拓展思路
此类题目属于线段树结合区间操作与状态维护的类型。相似套路包括分析操作实质，简化操作数量，利用数据结构高效维护状态。类似题目通常涉及区间的添加、删除、查询等操作，可通过线段树、树状数组等数据结构解决。

### 相似知识点洛谷题目
1. **P3372 【模板】线段树 1**：基础线段树模板题，用于练习线段树的区间修改和单点查询。
2. **P3373 【模板】线段树 2**：进阶线段树模板题，涉及区间乘法、加法等多种操作。
3. **P1438 无聊的数列**：通过线段树维护区间信息，解决区间修改和查询问题，与本题思路类似。 

---
处理用时：53.97秒