# 题目信息

# Eating Queries

## 题目描述

Timur has $ n $ candies. The $ i $ -th candy has a quantity of sugar equal to $ a_i $ . So, by eating the $ i $ -th candy, Timur consumes a quantity of sugar equal to $ a_i $ .

Timur will ask you $ q $ queries regarding his candies. For the $ j $ -th query you have to answer what is the minimum number of candies he needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity. In other words, you should print the minimum possible $ k $ such that after eating $ k $ candies, Timur consumes a quantity of sugar of at least $ x_j $ or say that no possible $ k $ exists.

Note that he can't eat the same candy twice and queries are independent of each other (Timur can use the same candy in different queries).

## 说明/提示

For the first test case:

For the first query, Timur can eat any candy, and he will reach the desired quantity.

For the second query, Timur can reach a quantity of at least $ 10 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the third query, there is no possible answer.

For the fourth query, Timur can reach a quantity of at least $ 14 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the second test case:

For the only query of the second test case, we can choose the third candy from which Timur receives exactly $ 3 $ sugar. It's also possible to obtain the same answer by choosing the fourth candy.

## 样例 #1

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1```

# AI分析结果

### 题目内容重写

**题目描述**

Timur 有 $n$ 颗糖果，第 $i$ 颗糖果的糖分为 $a_i$。因此，吃掉第 $i$ 颗糖果，Timur 会摄入 $a_i$ 的糖分。

Timur 会向你提出 $q$ 个关于他的糖果的查询。对于第 $j$ 个查询，你需要回答他至少需要吃掉多少颗糖果才能摄入至少 $x_j$ 的糖分，或者输出 -1 表示无法达到该糖分。换句话说，你需要输出最小的 $k$，使得吃掉 $k$ 颗糖果后，Timur 摄入的糖分至少为 $x_j$，或者说明不存在这样的 $k$。

注意，他不能重复吃同一颗糖果，且查询之间是独立的（Timur 可以在不同的查询中吃同一颗糖果）。

**说明/提示**

对于第一个测试用例：

- 对于第一个查询，Timur 可以吃任意一颗糖果，他将达到所需的糖分。
- 对于第二个查询，Timur 可以通过吃掉第 7 和第 8 颗糖果，摄入至少 10 的糖分，因此摄入的糖分为 14。
- 对于第三个查询，没有可能的答案。
- 对于第四个查询，Timur 可以通过吃掉第 7 和第 8 颗糖果，摄入至少 14 的糖分，因此摄入的糖分为 14。

对于第二个测试用例：

- 对于第二个测试用例的唯一查询，我们可以选择第三颗糖果，Timur 恰好摄入 3 的糖分。也可以通过选择第四颗糖果得到相同的答案。

**样例 #1**

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1```

### 题解分析与结论

#### 综合分析与结论

本题的核心思路是通过贪心算法和二分查找来优化查询效率。具体来说，为了最小化吃掉的糖果数量，应该优先选择糖分最大的糖果。因此，首先对糖果的糖分进行降序排序，然后计算前缀和，最后通过二分查找来确定满足条件的最小糖果数量。

#### 最优关键思路或技巧

1. **贪心算法**：优先选择糖分最大的糖果，以确保在吃最少糖果的情况下达到目标糖分。
2. **前缀和**：通过计算前缀和，可以快速获取前 $k$ 颗糖果的总糖分。
3. **二分查找**：利用前缀和的单调性，通过二分查找快速确定满足条件的最小 $k$。

#### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)：考察贪心算法和背包问题。
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列。
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)：考察二分查找和数据结构。

### 所选高星题解

#### 题解1：作者：Otue (5星)

**关键亮点**：
- 清晰的贪心思路，优先选择糖分最大的糖果。
- 使用前缀和和二分查找优化查询效率，时间复杂度为 $O(n \log n)$。
- 代码简洁，逻辑清晰。

**代码片段**：
```cpp
sort(a + 1, a + n + 1, cmp);  //从大到小排序
for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];   //前缀和
while (q--) {
    int x;
    cin >> x;
    if (sum[n] < x) puts("-1");   //判断无解
    else cout << lower_bound(sum + 1, sum + n + 1, x) - sum << endl;   //否则二分
}
```

#### 题解2：作者：Coros_Trusds (5星)

**关键亮点**：
- 详细的贪心算法解释，强调优先选择糖分最大的糖果。
- 手写二分查找，展示了二分查找的实现细节。
- 代码结构清晰，易于理解。

**代码片段**：
```cpp
sort(a + 1, a + n + 1, cmp);
for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
while (m --) {
    int x;
    cin >> x;
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (sum[mid] >= x) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
}
```

#### 题解3：作者：CYZZ (4星)

**关键亮点**：
- 清晰的贪心算法思路，强调优先选择糖分最大的糖果。
- 使用 `lower_bound` 进行二分查找，代码简洁。
- 代码逻辑清晰，易于理解。

**代码片段**：
```cpp
sort(a + 1, a + n + 1, cmp);
for (int i = 1; i <= n; i++) {
    sum[i] = a[i] + sum[i - 1];
}
for (int i = 1; i <= q; i++) {
    scanf("%d", &x);
    printf("%d\n", sum[n] >= x ? lower_bound(sum + 1, sum + n + 1, x) - sum : -1);
}
```

### 个人心得总结

- **调试经历**：在实现二分查找时，注意边界条件的处理，避免出现死循环或错误结果。
- **踩坑教训**：在计算前缀和时，确保数组下标从 1 开始，避免越界错误。
- **顿悟感想**：贪心算法与二分查找的结合可以大幅提高查询效率，适用于类似的最优化问题。

---
处理用时：42.20秒