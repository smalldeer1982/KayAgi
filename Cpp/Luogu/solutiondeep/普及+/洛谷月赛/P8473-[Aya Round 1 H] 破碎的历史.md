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
这三道题解均采用线段树结合二分查找的方法解决问题，核心思路一致，即通过分析得出每次操作1中仅需考虑最长的“两端黑线段”，用线段树维护区间染色情况，二分查找确定该线段端点。不同点主要体现在代码实现细节与表述方式上。

### 所选的题解
1. **作者：jjsnam（5星）**
    - **关键亮点**：思路清晰，从题目分析逐步过渡到实现细节，对每个细节点都有详细解释，代码注释详尽，变量命名规范，可读性强。
    - **个人心得**：作者考试时因未注意每次输出询问结果，误以为题目难度更高，考试后才恍然大悟。强调了基础知识的重要性，推荐了类似线段树区间覆盖的题目。
    - **核心代码片段**：
```cpp
// 线段树结构体
struct SegmentTree{
    int mn;//区间最小值。用于找白点。
    int lazy;
}tr[maxn << 2];

// 向上更新
void pushup(int id){
    tr[id].mn = min(tr[ls].mn, tr[rs].mn);
}

// 建树
void build(int id, int l, int r){
    if (l == r){
        tr[id].mn = a[l];
        return;
    }
    build(ls, l, mid),
    build(rs, mid+1, r);
    pushup(id);
}

// 向下传递lazy标记
void pushdown(int id){
    if (tr[id].lazy){
        tr[ls].lazy += tr[id].lazy;
        tr[rs].lazy += tr[id].lazy;
        tr[ls].mn += tr[id].lazy;
        tr[rs].mn += tr[id].lazy;
        tr[id].lazy = 0;
    }
}

// 区间更新
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

// 区间查询
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

// 找最左的黑点
int findL(int x){
    return id[lower_bound(blk+1, blk+1+len, x)-blk];
}

// 找最右的黑点
int findR(int x){
    return id[upper_bound(blk+1, blk+1+len, x)-blk-1];
}

// 每次的询问
void check(){
    if (query(1, 1, n, 1, n) <= 0) cout << "No" << endl;
    else cout << "Yes" << endl;
}
```
核心实现思想：通过线段树的基本操作（建树、更新、查询），结合二分查找找到每次操作1中最长“两端黑线段”对应的区间，更新线段树来模拟染色过程，通过查询线段树最小值判断是否所有点可染黑。

2. **作者：chen_zhe（4星）**
    - **关键亮点**：对问题的抽象简洁明了，将操作抽象为对特定区间的加减操作，代码结构紧凑，逻辑连贯。
    - **核心代码片段**：
```cpp
// 向上更新
inline void Push_Up(int id)
{
    t[id].val=min(t[id<<1].val,t[id<<1|1].val);
}

// 向下传递lazy标记
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

// 建树
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

// 区间更新
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

// 查询全局最小值
inline int Query()
{
    return t[1].val;
}
```
核心实现思想：利用线段树维护区间最小值，通过二分查找确定每次操作对应的区间，对该区间进行更新，最后通过查询全局最小值判断是否所有点可染黑。

3. **作者：Micnation_AFO（4星）**
    - **关键亮点**：对思路的阐述较为清晰，从对题目的初步分析逐步引入到线段树的维护方式，代码结构简单易懂。
    - **核心代码片段**：
```cpp
// 向上更新
void push_up(SegmentTree &fa, SegmentTree ls, SegmentTree rs) {
    fa.dat = min(ls.dat, rs.dat);
} 

// 建树
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].dat = (color[l]? INF : 0); return; }
    int mid = (t[p].l + t[p].r) >> 1;
    build(p << 1, l, mid), build((p << 1) | 1, mid + 1, r);
    push_up(t[p], t[p << 1], t[(p << 1) | 1]);
}

// 向下传递lazy标记
void spread(int p) {
    if (t[p].add) {
        t[p << 1].dat += t[p].add;
        t[(p << 1) | 1].dat += t[p].add;
        t[p << 1].add += t[p].add, t[(p << 1) | 1].add += t[p].add;
        t[p].add = 0;
    }
}

// 区间更新
void change(int p, int l, int r, int v) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].dat += v;
        t[p].add += v;
        return;
    }
    spread(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r, v);
    if (r > mid) change((p << 1) | 1, l, r, v);
    push_up(t[p], t[p << 1], t[(p << 1) | 1]);
}

// 查询全局最小值
int ask() {
    return t[1].dat;
}
```
核心实现思想：与其他题解类似，通过线段树维护区间最小值，利用二分查找确定操作区间，对区间进行更新，通过查询全局最小值判断染色情况。

### 最优关键思路或技巧
1. **数据结构**：利用线段树维护区间信息，通过区间更新和查询操作模拟染色过程，高效处理大规模数据。
2. **算法优化**：通过分析得出每次操作1仅需考虑最长“两端黑线段”，减少了操作数量，优化了算法复杂度。
3. **思维方式**：将实际问题抽象为线段树的区间操作问题，清晰地理解问题本质，找到简洁有效的解决方案。

### 可拓展之处
同类型题或类似算法套路：此类题目通常涉及区间操作、状态维护与查询，可以拓展到更多具有类似性质的问题，如区间覆盖、区间最值动态更新等。例如，当题目中出现对区间的多种操作（如加、减、乘、除等），以及需要实时查询区间某种状态（如和、最值、奇偶性等）时，都可以考虑使用线段树解决。

### 推荐题目
1. **P8463 「REOI-1」深潜的第六兽**：同样考查线段树区间覆盖相关知识点，与本题在利用线段树维护区间状态上思路相似。
2. **P1442 铁球落地**：通过线段树解决区间更新与查询问题，有助于加深对线段树应用的理解。
3. **P3372 【模板】线段树 1**：经典的线段树模板题，涵盖了线段树的基本操作，是巩固线段树知识的基础题目。 

---
处理用时：80.28秒