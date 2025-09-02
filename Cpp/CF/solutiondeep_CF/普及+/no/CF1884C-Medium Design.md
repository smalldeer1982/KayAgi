# 题目信息

# Medium Design

## 题目描述

The array $ a_1, a_2, \ldots, a_m $ is initially filled with zeroes. You are given $ n $ pairwise distinct segments $ 1 \le l_i \le r_i \le m $ . You have to select an arbitrary subset of these segments (in particular, you may select an empty set). Next, you do the following:

- For each $ i = 1, 2, \ldots, n $ , if the segment $ (l_i, r_i) $ has been selected to the subset, then for each index $ l_i \le j \le r_i $ you increase $ a_j $ by $ 1 $ (i. e. $ a_j $ is replaced by $ a_j + 1 $ ). If the segment $ (l_i, r_i) $ has not been selected, the array does not change.
- Next (after processing all values of $ i = 1, 2, \ldots, n $ ), you compute $ \max(a) $ as the maximum value among all elements of $ a $ . Analogously, compute $ \min(a) $ as the minimum value.
- Finally, the cost of the selected subset of segments is declared as $ \max(a) - \min(a) $ .

Please, find the maximum cost among all subsets of segments.

## 说明/提示

In the first test case, there is only one segment available. If we do not select it, then the array will be $ a = [0, 0, 0] $ , and the cost of such (empty) subset of segments will be $ 0 $ . If, however, we select the only segment, the array will be $ a = [0, 1, 0] $ , and the cost will be $ 1 - 0 = 1 $ .

In the second test case, we can select all the segments: the array will be $ a = [0, 1, 2, 3, 2, 1, 0, 0] $ in this case. The cost will be $ 3 - 0 = 3 $ .

## 样例 #1

### 输入

```
6
1 3
2 2
3 8
2 4
3 5
4 6
6 3
1 1
1 2
1 3
2 2
2 3
3 3
7 6
2 2
1 6
1 2
5 6
1 5
4 4
3 6
6 27
6 26
5 17
2 3
20 21
1 22
12 24
4 1000000000
2 999999999
3 1000000000
123456789 987654321
9274 123456789```

### 输出

```
1
3
2
3
4
4```

# AI分析结果

### 题目内容重写

#### 题目描述

数组 $a_1, a_2, \ldots, a_m$ 初始时全为 $0$。给定 $n$ 个互不相同的区间 $1 \le l_i \le r_i \le m$。你需要从中选择一个子集（可以为空），然后进行如下操作：

- 对于每个 $i = 1, 2, \ldots, n$，如果区间 $[l_i, r_i]$ 被选中，则对于每个下标 $l_i \le j \le r_i$，将 $a_j$ 增加 $1$（即 $a_j$ 被替换为 $a_j + 1$）。如果区间 $[l_i, r_i]$ 未被选中，则数组 $a$ 保持不变。
- 在处理完所有 $i = 1, 2, \ldots, n$ 后，计算 $a$ 的最大值 $\max(a)$ 和最小值 $\min(a)$。
- 最后，所选子集的成本定义为 $\max(a) - \min(a)$。

请找出所有子集中成本的最大值。

#### 说明/提示

在第一个测试用例中，只有一个区间。如果不选择它，数组将保持为 $a = [0, 0, 0]$，成本为 $0$。如果选择该区间，数组将变为 $a = [0, 1, 0]$，成本为 $1 - 0 = 1$。

在第二个测试用例中，可以选择所有区间，数组将变为 $a = [0, 1, 2, 3, 2, 1, 0, 0]$，成本为 $3 - 0 = 3$。

#### 样例输入

```
6
1 3
2 2
3 8
2 4
3 5
4 6
6 3
1 1
1 2
1 3
2 2
2 3
3 3
7 6
2 2
1 6
1 2
5 6
1 5
4 4
3 6
6 27
6 26
5 17
2 3
20 21
1 22
12 24
4 1000000000
2 999999999
3 1000000000
123456789 987654321
9274 123456789
```

#### 样例输出

```
1
3
2
3
4
4
```

### 算法分类
差分、离散化

### 题解分析与结论

本题的核心在于如何高效地计算选择不同子集后数组 $a$ 的最大值与最小值之差。由于 $m$ 的范围可能非常大，直接模拟操作会超时，因此需要采用差分和离散化的技巧来优化计算。

### 精选题解

#### 题解1：LiJoQiao (5星)
**关键亮点**：
- 使用差分和离散化技术，将问题转化为区间加和查询最小值的问题。
- 通过优先队列和线段树优化了时间复杂度，达到 $O(n \log n)$。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
void add(int id,int l1,int r1,int k,int l,int r){
    if(l==l1&&r==r1){
        lt[id].lazy+=k;
        return;
    }
    pushdown(id);
    if(r1<=mid)add(lid,l1,r1,k,l,mid);
    else if(l1>=mid+1)add(rid,l1,r1,k,mid+1,r);
    else{
        add(lid,l1,mid,k,l,mid);
        add(rid,mid+1,r1,k,mid+1,r);
    }
    pushup(id);
}
```

#### 题解2：One_JuRuo (4星)
**关键亮点**：
- 通过枚举最小值的可能位置，简化了问题。
- 使用差分数组和离散化技术，优化了计算过程。
- 代码简洁，思路清晰。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(s[i].l>1){
        int l = lower_bound(p.begin(),p.end(),s[i].l) - p.begin() + 1;
        int r = lower_bound(p.begin(),p.end(),s[i].r + 1) - p.begin() + 1;
        arr[l]++;
        arr[r]--;
    }
}
```

#### 题解3：xs_siqi (4星)
**关键亮点**：
- 通过离散化和差分数组，直接计算每个点的覆盖次数。
- 使用前缀和和后缀和优化了区间覆盖次数的计算。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    vis[a[i].l]++;
    vis[a[i].r+1]--;
}
for(int i=1;i<=k;i++){
    vis[i]=vis[i]+vis[i-1];
}
```

### 最优关键思路或技巧
- **差分与离散化**：通过差分数组和离散化技术，将大范围的区间操作转化为小范围的离散点操作，大大优化了时间复杂度。
- **线段树与优先队列**：使用线段树维护区间加和查询最小值，结合优先队列动态管理区间，进一步优化了算法效率。

### 拓展思路
- 类似的问题可以通过差分和离散化技术进行优化，例如区间覆盖、区间查询等问题。
- 线段树和优先队列的结合可以用于处理动态区间操作和查询问题。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P5490 【模板】扫描线](https://www.luogu.com.cn/problem/P5490)

---
处理用时：50.03秒