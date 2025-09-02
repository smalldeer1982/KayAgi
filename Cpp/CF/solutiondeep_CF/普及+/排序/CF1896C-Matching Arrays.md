# 题目信息

# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1```

# AI分析结果



### 题目内容中文翻译
# 匹配数组

## 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。数组 $a$ 和 $b$ 的美丽值定义为满足 $a_i > b_i$ 的索引 $i$ 的数量。

再给定一个整数 $x$。判断是否能重新排列数组 $b$ 的元素使得数组的美丽值恰好为 $x$。若可行，输出一种有效的排列方式。

## 输入输出样例
（样例内容与题目原文一致，此处省略）

---

### 题解综合分析

#### 通用解法思路
所有优质题解均采用以下贪心策略：
1. 将 $a$ 数组降序排序，$b$ 数组升序排序
2. 用 $a$ 的前 $x$ 大元素匹配 $b$ 的前 $x$ 小元素，确保这 $x$ 对满足 $a_i > b_i$
3. 剩余元素用 $a$ 的升序部分匹配 $b$ 的降序部分，确保 $a_i \leq b_i$
4. 若上述两步均满足则构造成功，否则无解

#### 关键证明
该策略的贪心正确性可通过反证法说明：若最优匹配无法达成，则任何其他排列方式也无法满足条件。核心在于通过排序最大化可用资源的利用率。

---

### 精选题解与评分

#### 1. 作者：Register_int（5星）
**亮点**：代码简洁高效，使用 lambda 表达式优化排序逻辑，索引处理清晰
```cpp
sort(a + 1, a + n + 1, [](const node &p, const node &q) { return p.x < q.x; });
for (int i = 1; i <= m; i++) 
    if (b[i] >= a[n - m + i].x) { f = 1; break; }
for (int i = m + 1; i <= n; i++)
    if (b[i] < a[i - m].x) { f = 1; break; }
```

#### 2. 作者：Drind（4星）
**亮点**：结构体记录原始索引，输出处理规范，边界条件处理完善
```cpp
for(int i=n;i>=n-x+1;i--){ // 前x大的a匹配前x小的b
    ans[a[i].id]=b[i-n+x];
    if(b[i-n+x]>=a[i].val) return;
}
for(int i=n-x;i>=1;i--){ // 剩余部分匹配
    ans[a[i].id]=b[i+x];
    if(b[i+x]<a[i].val) return;
}
```

#### 3. 作者：Eazin_star（4星）
**亮点**：双排序逻辑分离明确，变量命名清晰，验证流程简洁
```cpp
sort(a+1, a+n+1, cmp); // a升序排序
sort(b+1, b+n+1);      // b升序排序
for (int i = x+1; i <= n; i++) // 验证剩余部分
    if (b[i] < a[i-x].v) f=0;
```

---

### 核心技巧总结
1. **结构体索引法**：通过结构体保留原始索引，解决排序后元素位置还原问题
2. **双阶段验证**：先验证x个a_i>b_i的可行性，再验证剩余元素的a_i<=b_i
3. **排序策略**：a降序取前x大，b升序取前x小形成最优匹配对
4. **时间复杂度**：O(n log n) 由排序主导，适用于2e5数据规模

---

### 同类题目推荐
1. P1090 [NOIP2004 提高组] 合并果子 - 贪心+优先队列
2. P1106 删数问题 - 贪心策略构造最小数 
3. P1230 智力大冲浪 - 时间窗口贪心匹配

---
处理用时：53.49秒