# 题目信息

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2```

### 输出

```
4
168
10
1000000000
9
1000000000```

# AI分析结果



### 题目中文翻译
#### 题目描述
- 你收到一个包含 $n$ 个正整数的数组 $a_1,a_2,\ldots,a_n$ 和一个正整数 $k \le n$。
- 最多进行 $k$ 次操作：选择索引 $i$ 和整数 $x$，将 $a_i$ 赋值为 $x$。
- 构建一个包含 $n$ 个顶点的完全无向加权图，边 $(l, r)$ 的权重为 $\min(a_l,a_{l+1},\ldots,a_r)$。
- 目标是通过操作使图的直径最大化。直径定义为所有点对间最短路径的最大值。

#### 输入输出样例
**输入**  
```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2
```

**输出**  
```
4
168
10
1000000000
9
1000000000
```

---

### 题解综合分析
#### 关键结论
1. **两点间最短路性质**：最短路要么是直接边的权重（区间最小值），要么是两倍全局最小值。
2. **最优策略**：将前 $k-1$ 小的元素改为 $10^9$，转化为 $k=1$ 的问题处理。
3. **二分答案法**：验证候选答案 $x$ 是否可达，通过修改元素满足条件。

#### 最优思路总结
1. **贪心策略**：将前 $k-1$ 小的元素改为极大值，剩余操作用于提升相邻元素的最小值或全局最小值。
2. **二分验证**：检查修改后的数组是否满足：
   - 全局最小值的两倍 ≥ $x$
   - 存在相邻元素的最小值 ≥ $x$

---

### 高分题解摘选
#### 1. Gokix（⭐⭐⭐⭐⭐）
**核心亮点**：
- 通过严谨的结论推导将问题转化为 $k=1$ 的情况。
- 利用预处理和单次遍历快速计算可能的最大直径。

**关键代码**：
```cpp
// 预处理：将前k-1小的元素改为1e9
sort(b+1,b+n+1,cmp);
for(i=1;i<k;i++) a[b[i].id]=MD;

// 枚举每个位置尝试修改为1e9，计算可能的最大直径
for(i=1;i<=n;i++){
    u=a[i];a[i]=MD;
    // 计算修改后的相邻最小值和全局最小值
    if(u*2==ans2) ans=max(ans,min(mx,ans3));
    else ans=max(ans,min(mx,ans2));
    a[i]=u;
}
```

#### 2. cachejtt（⭐⭐⭐⭐）
**核心亮点**：
- 清晰的问题分治策略，将问题拆分为全局最小值优化和相邻元素优化。
- 代码简洁，通过排序和贪心选择最优修改点。

**关键代码**：
```cpp
bool check(int x){
    int cnt=0;
    // 统计需要修改的元素数量
    for(int i=1;i<=n;++i) cnt+=(a[i]*2<x);
    if(cnt>k) return false;
    // 检查相邻元素是否可达x
    for(int i=1;i<n;++i)
        if(min(a[i],a[i+1])>=x || (max(a[i],a[i+1])>=x && cnt<k))
            return true;
    return false;
}
```

#### 3. Dregen_Yor（⭐⭐⭐⭐）
**核心亮点**：
- 快速二分框架，通过预处理减少重复计算。
- 利用前缀和优化区间统计。

**关键代码**：
```cpp
bool check(int mid){
    // 统计需要修改的点
    int cc=0;
    for(int i=1;i<=n;++i) if(2*a[i]<mid) cc++,A[i]=1e9;
    // 检查相邻点是否满足条件
    bool f1=0,f2=0;
    for(int i=2;i<=n;++i) if(min(A[i],A[i-1])>=mid) f1=1;
    for(int i=1;i<=n;++i) if(A[i]>=mid) f2=1;
    return (cc<=k) && (f1 || (f2 && cc<k));
}
```

---

### 关键技巧与拓展
1. **问题转化**：将多步操作问题转化为更简单的子问题（如 $k=1$）。
2. **二分框架**：验证函数的设计需结合贪心策略，快速排除无效解。
3. **极值处理**：修改元素为极大值时，可以显著提升相邻边的最小值。

**类似题目推荐**：
1. [P7895 『JROI-3』1÷0](https://www.luogu.com.cn/problem/P7895) - 贪心与极值处理
2. [P2114 障碍](https://www.luogu.com.cn/problem/P2114) - 二分答案与路径优化
3. [P2217 分割](https://www.luogu.com.cn/problem/P2217) - 极值影响下的最值问题

---

### 调试心得摘录
- **Gokix**提到："将前 $k-1$ 小的元素改为 $10^9$ 后，问题本质变为单次操作的最优选择，这是多次尝试后发现的模式简化。"
- **cachejtt**在代码注释中强调："必须同时考虑全局最小和相邻最小，单独优化任一维度都会导致错误。"

---
处理用时：58.88秒