# 题目信息

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# AI分析结果



# Moscow Gorillas 题目中文翻译

## 题目描述

冬天，莫斯科动物园的居民们非常无聊，尤其是大猩猩。你决定带一个长度为 $n$ 的排列 $p$ 去动物园娱乐它们。

一个长度为 $n$ 的排列是由 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（重复出现 $2$），$[1,3,4]$ 也不是排列（$n=3$ 但包含 $4$）。

大猩猩有自己的排列 $q$。它们要求你统计满足 $\operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r]) = \operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r])$ 的区间 $[l,r]$（$1 \le l \le r \le n$）的数量。

$\operatorname{MEX}$ 表示序列中未出现的最小正整数。例如：
- $\operatorname{MEX}([1,3]) = 2$
- $\operatorname{MEX}([5]) = 1$
- $\operatorname{MEX}([3,1,2,6]) = 4$

## 输入样例

样例 #1：
```
3
1 3 2
2 1 3
```
输出：`2`

样例 #2：
```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```
输出：`16`

样例 #3：
```
6
1 2 3 4 5 6
6 5 4 3 2 1
```
输出：`11`

---

## 题解分析与结论

### 核心思路
所有优秀题解均采用 **枚举 MEX 值** 的策略，关键步骤如下：
1. **预处理位置映射**：记录每个数在两个排列中的位置
2. **逐步维护区间边界**：维护必须包含 $1\sim m-1$ 的最小覆盖区间 $[L,R]$
3. **排除当前 MEX 值的影响**：根据当前 MEX 值在两个排列中的位置，计算合法区间的左右端点取值范围
4. **分类讨论区间组合**：通过几何划分计算不包含当前 MEX 的合法区间数量

### 最优题解亮点

#### 题解作者：TernaryTree（★★★★★）
**核心亮点**：
- 图形化分析区间划分，将复杂条件转化为几何区域计算
- 高效处理边界情况，代码结构清晰
- 时间复杂度严格 $O(n)$，空间优化到位

**关键代码**：
```cpp
int main() {
    // 预处理位置映射
    for (int i = 1; i <= n; i++) s[p[i]] = i; 
    for (int i = 1; i <= n; i++) t[q[i]] = i;

    // 处理 MEX=1 的特殊情况
    int k1 = s[1], k2 = t[1];
    if (k1 > k2) swap(k1, k2);
    ans += 分三段计算不跨域的区间数;

    // 枚举 MEX 值
    int l = k1, r = k2;
    for (int m = 2; m <= n; m++) {
        k1 = s[m], k2 = t[m];
        if (k1 > k2) swap(k1, k2);
        
        // 分类讨论四种位置关系
        if (区间包含任意一个 MEX 位置) continue;
        else if (两个 MEX 都在左区间) 
            ans += (左区间长度) * (右剩余长度);
        // ...其他情况类似处理
        
        // 更新必须包含的区间边界
        l = min(l, k1);
        r = max(r, k2);
    }
    cout << ans + 1; // +1 处理 MEX=n+1
}
```

#### 题解作者：lizhous（★★★★☆）
**亮点**：
- 引入辅助函数 `get()` 简化区间计数
- 对称处理两个排列的位置关系
- 代码注释清晰，易于理解

**思维要点**：
```cpp
int get(int l, int r) { // 计算 [l,r] 内所有可能区间数
    return (r-l+2)*(r-l+1)/2; 
}
```

---

## 关键技巧总结
1. **MEX 性质逆向应用**：通过确保包含 $1\sim m-1$ 并排除 $m$ 来构造合法区间
2. **双指针维护动态区间**：随着 MEX 增大，动态维护必须包含的最小覆盖区间
3. **排列性质利用**：元素唯一性保证了位置映射的确定性
4. **几何区域划分**：将复杂逻辑转化为区间交并补运算

---

## 相似题目推荐
1. [P2309 - 区间 MEX 问题](https://www.luogu.com.cn/problem/P2309)
2. [CF1295E - MEX 与子集构造](https://codeforces.com/problemset/problem/1295/E)
3. [P4137 - 区间 MEX 查询](https://www.luogu.com.cn/problem/P4137)

---

## 调试经验摘录
> "考场上脑瘫了交了 N 发" —— Feyn  
> **总结**：在复杂条件处理时，建议先手动画图验证所有分类情况，避免因边界条件遗漏导致反复提交。

> "注意要加上 MEX=n+1 的情况" —— 多个题解  
> **教训**：特殊终局情况（如全选整个排列）容易被忽略，需在代码中显式处理。

---
处理用时：55.46秒