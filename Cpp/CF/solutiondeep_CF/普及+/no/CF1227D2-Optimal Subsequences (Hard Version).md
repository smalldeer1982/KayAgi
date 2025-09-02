# 题目信息

# Optimal Subsequences (Hard Version)

## 题目描述

This is the harder version of the problem. In this version, $ 1 \le n, m \le 2\cdot10^5 $ . You can hack this problem if you locked it. But you can hack the previous problem only if you locked both problems.

You are given a sequence of integers $ a=[a_1,a_2,\dots,a_n] $ of length $ n $ . Its subsequence is obtained by removing zero or more elements from the sequence $ a $ (they do not necessarily go consecutively). For example, for the sequence $ a=[11,20,11,33,11,20,11] $ :

- $ [11,20,11,33,11,20,11] $ , $ [11,20,11,33,11,20] $ , $ [11,11,11,11] $ , $ [20] $ , $ [33,20] $ are subsequences (these are just some of the long list);
- $ [40] $ , $ [33,33] $ , $ [33,20,20] $ , $ [20,20,11,11] $ are not subsequences.

Suppose that an additional non-negative integer $ k $ ( $ 1 \le k \le n $ ) is given, then the subsequence is called optimal if:

- it has a length of $ k $ and the sum of its elements is the maximum possible among all subsequences of length $ k $ ;
- and among all subsequences of length $ k $ that satisfy the previous item, it is lexicographically minimal.

Recall that the sequence $ b=[b_1, b_2, \dots, b_k] $ is lexicographically smaller than the sequence $ c=[c_1, c_2, \dots, c_k] $ if the first element (from the left) in which they differ less in the sequence $ b $ than in $ c $ . Formally: there exists $ t $ ( $ 1 \le t \le k $ ) such that $ b_1=c_1 $ , $ b_2=c_2 $ , ..., $ b_{t-1}=c_{t-1} $ and at the same time $ b_t<c_t $ . For example:

- $ [10, 20, 20] $ lexicographically less than $ [10, 21, 1] $ ,
- $ [7, 99, 99] $ is lexicographically less than $ [10, 21, 1] $ ,
- $ [10, 21, 0] $ is lexicographically less than $ [10, 21, 1] $ .

You are given a sequence of $ a=[a_1,a_2,\dots,a_n] $ and $ m $ requests, each consisting of two numbers $ k_j $ and $ pos_j $ ( $ 1 \le k \le n $ , $ 1 \le pos_j \le k_j $ ). For each query, print the value that is in the index $ pos_j $ of the optimal subsequence of the given sequence $ a $ for $ k=k_j $ .

For example, if $ n=4 $ , $ a=[10,20,30,20] $ , $ k_j=2 $ , then the optimal subsequence is $ [20,30] $ — it is the minimum lexicographically among all subsequences of length $ 2 $ with the maximum total sum of items. Thus, the answer to the request $ k_j=2 $ , $ pos_j=1 $ is the number $ 20 $ , and the answer to the request $ k_j=2 $ , $ pos_j=2 $ is the number $ 30 $ .

## 说明/提示

In the first example, for $ a=[10,20,10] $ the optimal subsequences are:

- for $ k=1 $ : $ [20] $ ,
- for $ k=2 $ : $ [10,20] $ ,
- for $ k=3 $ : $ [10,20,10] $ .

## 样例 #1

### 输入

```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
20
10
20
10
20
10
```

## 样例 #2

### 输入

```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```

### 输出

```
2
3
2
3
2
3
1
1
3
```

# AI分析结果

### 题目翻译
# 最优子序列（困难版本）

## 题目描述
这是该问题的较难版本。在此版本中，$ 1 \le n, m \le 2\cdot10^5 $。如果你锁定了这个问题，就可以对其发起 Hack。但你只有在锁定了两个问题后，才能 Hack 前一个问题。

给定一个长度为 $ n $ 的整数序列 $ a=[a_1,a_2,\dots,a_n] $。它的子序列是通过从序列 $ a $ 中移除零个或多个元素（这些元素不一定连续）得到的。例如，对于序列 $ a=[11,20,11,33,11,20,11] $：
- $ [11,20,11,33,11,20,11] $、$ [11,20,11,33,11,20] $、$ [11,11,11,11] $、$ [20] $、$ [33,20] $ 都是子序列（这些只是一长串子序列中的一部分）；
- $ [40] $、$ [33,33] $、$ [33,20,20] $、$ [20,20,11,11] $ 都不是子序列。

假设额外给定一个非负整数 $ k $（$ 1 \le k \le n $），若一个子序列满足以下条件，则称其为最优子序列：
- 它的长度为 $ k $，且在所有长度为 $ k $ 的子序列中，其元素之和最大；
- 在所有满足前一个条件的长度为 $ k $ 的子序列中，它的字典序最小。

回顾一下，如果序列 $ b=[b_1, b_2, \dots, b_k] $ 和序列 $ c=[c_1, c_2, \dots, c_k] $ 从左起第一个不同元素在序列 $ b $ 中的值小于在序列 $ c $ 中的值，那么序列 $ b $ 的字典序小于序列 $ c $。形式上：存在 $ t $（$ 1 \le t \le k $），使得 $ b_1=c_1 $，$ b_2=c_2 $，...，$ b_{t - 1}=c_{t - 1} $，同时 $ b_t < c_t $。例如：
- $ [10, 20, 20] $ 的字典序小于 $ [10, 21, 1] $；
- $ [7, 99, 99] $ 的字典序小于 $ [10, 21, 1] $；
- $ [10, 21, 0] $ 的字典序小于 $ [10, 21, 1] $。

给定一个序列 $ a=[a_1,a_2,\dots,a_n] $ 和 $ m $ 个查询，每个查询由两个数 $ k_j $ 和 $ pos_j $ 组成（$ 1 \le k \le n $，$ 1 \le pos_j \le k_j $）。对于每个查询，输出给定序列 $ a $ 在 $ k = k_j $ 时的最优子序列中索引为 $ pos_j $ 的值。

例如，如果 $ n = 4 $，$ a = [10,20,30,20] $，$ k_j = 2 $，那么最优子序列是 $ [20,30] $ —— 它是所有长度为 $ 2 $ 且元素总和最大的子序列中字典序最小的。因此，查询 $ k_j = 2 $，$ pos_j = 1 $ 的答案是 $ 20 $，查询 $ k_j = 2 $，$ pos_j = 2 $ 的答案是 $ 30 $。

## 说明/提示
在第一个样例中，对于 $ a = [10,20,10] $，最优子序列如下：
- 当 $ k = 1 $ 时：$ [20] $；
- 当 $ k = 2 $ 时：$ [10,20] $；
- 当 $ k = 3 $ 时：$ [10,20,10] $。

## 样例 #1
### 输入
```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```
### 输出
```
20
10
20
10
20
10
```

## 样例 #2
### 输入
```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```
### 输出
```
2
3
2
3
2
3
1
1
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先利用贪心策略确定最优子序列的选取规则，即优先选取大的数，相同值的数优先选取靠前的。为了高效处理查询，都采用了离线处理的方式，将查询按 $k$ 从小到大排序，避免重复计算。

不同题解在数据结构和实现细节上有所不同：
- **HoshizoraZ**：使用离散化、树状数组和二分查找。离散化处理数组元素，树状数组维护标记的前缀和，二分查找确定第 $pos$ 个元素的位置。
- **elbissoPtImaerD**：同样利用离线处理，用树状数组维护 $f$ 数组，直接在树状数组上二分查找。
- **bmatrix**：将元素下标排序，用 `pbds` 的平衡树维护元素，根据 $k$ 的变化添加元素，查询第 $p$ 小的元素。
- **lgx57**：离散化数组，用线段树维护 $f$ 数组，二分查找确定答案。
- **wmrqwq**：D1 暴力选取，D2 用优先队列和树状数组维护加数和查询操作。

### 所选题解
- **HoshizoraZ（4星）**
    - **关键亮点**：思路清晰，详细阐述了每一步的实现方法，代码注释丰富，易于理解。利用离散化处理数据范围大的问题，树状数组和二分查找结合高效解决查询问题。
    - **个人心得**：作者提到三个月前写 D1 题解后对 D2 无思路，今天偶然想到方法，体现了算法学习中不断思考和积累的重要性。
- **elbissoPtImaerD（4星）**
    - **关键亮点**：代码简洁，直接在树状数组上二分查找，复杂度低。
- **bmatrix（4星）**
    - **关键亮点**：使用 `pbds` 的平衡树，思路新颖，能快速实现元素的插入和查询第 $p$ 小的元素。

### 重点代码
#### HoshizoraZ
```cpp
// 树状数组模板
inline int lowbit(int x){
    return x & (-x);
}

void modify(int x){
    while(x <= n)
        t[x]++, x += lowbit(x);
}

int sum(int x){
    int ss = 0;
    while(x >= 1)
        ss += t[x], x -= lowbit(x);
    return ss;
}

// 主函数部分
int main(){
    // 输入处理
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = a[i];
    scanf("%d", &m);
    // 离散化
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        s[i].id = i, s[i].v = a[i];
        v[a[i]].push_back(i);
    }
    // 排序操作
    sort(s + 1, s + n + 1, cmp);
    for(int i = 1, k, pos; i <= m; i++)
        scanf("%d%d", &q[i].k, &q[i].pos), q[i].id = i;
    sort(q + 1, q + m + 1, cmpp); // 离线解决
    int nowk = 0;
    for(int i = 1, L, R; i <= m; i++){
        while(nowk < q[i].k) // 树状数组维护
            nowk++, modify(v[s[nowk].v][ss[s[nowk].v]]), ss[s[nowk].v]++;
        L = 1, R = n;
        while(L < R){ // 二分找答案
            int mid = (L + R) >> 1;
            if(sum(mid) < q[i].pos) L = mid + 1;
            else R = mid;
        }
        ans[q[i].id] = b[a[L]];
    }
    for(int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
```
**核心实现思想**：先对数组进行离散化处理，将元素映射到较小的范围。然后对查询按 $k$ 排序，离线处理。在处理查询时，利用树状数组维护标记的前缀和，通过二分查找找到第 $pos$ 个元素的位置。

#### elbissoPtImaerD
```cpp
struct BITS
{
    int c[N];
    #define lb x&-x
    il void Modify(re int x)
    {
        for(;x<=n;x+=lb) ++c[x];
        return;
    }
}f;

void Solve()
{
    rd(n);
    for(re int i=1;i<=n;++i) rd(b[i]),a[i]={b[i],i};
    std::sort(a+1,a+n+1,[](re wt x,re wt y){return x.x==y.x?x.y<y.y:x.x>y.x;});
    rd(m);
    for(re int i=1;i<=m;++i) rd(q[i].x),rd(q[i].y),q[i].z=i;
    std::sort(q+1,q+m+1,[](re wt x,re wt y){return x.x<y.x;});
    for(re int i=1,j=0;i<=m;++i)
    {
        for(;j<q[i].x;f.Modify(a[++j].y));
        re int p=0,s=0;
        for(re int j=19,v;~j;--j)
            v=p|1<<j,v<=n&&s+f.c[v]<q[i].y&&(p=v,s+=f.c[v]);
        ans[q[i].z]=b[p+1];
    }
    for(re int i=1;i<=m;++i) prt(ans[i],'\n');
    return;
}
```
**核心实现思想**：对元素按值从大到小、下标从小到大排序，对查询按 $k$ 排序。利用树状数组维护 $f$ 数组，直接在树状数组上二分查找第 $pos$ 个元素的位置。

#### bmatrix
```cpp
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    iota(b + 1, b + n + 1, 1);
    sort(b + 1, b + n + 1, [](int i, int j) 
    { return a[i] == a[j] ? i < j : a[i] > a[j]; });
    cin >> m;
    for(int i = 1; i <= m; ++i) cin >> q[i].k >> q[i].p, q[i].id = i;
    sort(q + 1, q + m + 1);
    for(int i = 1, j = 0; i <= m; ++i) {
        while(j < q[i].k) tr.insert(b[++j]);
        ans[q[i].id] = a[*tr.find_by_order(q[i].p - 1)];
    }
    for(int i = 1; i <= m; ++i) cout << ans[i] << endl;
    return 0;
}
```
**核心实现思想**：对元素下标按元素值从大到小、下标从小到大排序，对查询按 $k$ 排序。使用 `pbds` 的平衡树维护元素，根据 $k$ 的变化添加元素，查询第 $p$ 小的元素。

### 最优关键思路或技巧
- **离线处理**：将查询按 $k$ 从小到大排序，避免重复计算，只需要处理加数操作。
- **数据结构优化**：使用树状数组、线段树、平衡树等数据结构高效维护元素信息和进行查询操作。
- **离散化**：处理数据范围大的问题，将元素映射到较小的范围。

### 拓展思路
同类型题目可能会改变子序列的选取规则或查询方式，但核心思路仍然是贪心选取和高效处理查询。类似算法套路包括利用数据结构维护信息，如树状数组、线段树、平衡树等，以及离线处理查询。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可使用树状数组解决。
- [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)：可使用 `pbds` 的平衡树解决。
- [P2574 XOR的艺术](https://www.luogu.com.cn/problem/P2574)：可使用线段树解决。

### 个人心得总结
HoshizoraZ 作者提到三个月前对 D2 题无思路，今天偶然想到方法，说明算法学习需要不断思考和积累，遇到难题不要轻易放弃，随着知识和经验的增长，可能会有新的思路。

---
处理用时：94.71秒