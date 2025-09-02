# 题目信息

# [USACO07JAN] Protecting the Flowers S

## 题目描述

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

有 $n$ 头奶牛跑到 FJ 的花园里去吃花儿了，它们分别在距离牛圈 $T_i$（这里指 FJ 到那里需要 $T_i$ 分钟) 处吃花，每分钟会吃掉 $D_i$ 朵花，FJ 现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为 $2 \times T_i$ 分钟，在这段时间内，其它的奶牛会继续吃 FJ 的花，速度保持不变，当然正在被赶回牛圈的奶牛不能继续吃了。现在求在最好的方案下奶牛吃掉花的最小朵数。


## 说明/提示

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.


## 样例 #1

### 输入

```
6
3 1
2 5
2 3
3 2
4 1
1 6```

### 输出

```
86```

# AI分析结果

### 综合分析与结论

本题的核心在于通过贪心策略确定奶牛的运输顺序，以最小化花朵的损失。所有题解都基于相同的贪心思路：通过比较两头奶牛的运输时间和吃花速度的比值，确定它们的运输顺序。具体来说，按照 `T_i / D_i` 从小到大排序，优先运输比值较小的奶牛，这样可以减少其他奶牛在运输过程中吃掉的花朵数量。

### 所选高分题解

#### 1. 作者：曦行夜落 (★★★★★)
**关键亮点**：
- 详细解释了贪心算法的基本概念和适用场景。
- 通过比较两头奶牛的运输顺序，推导出贪心策略的数学依据。
- 代码简洁明了，使用了前缀和优化计算花朵损失。

**个人心得**：
- 强调了贪心算法的“目光短浅”特性，提醒读者在应用贪心策略时要注意其局限性。

**核心代码**：
```cpp
bool cmp(cows x, cows y) {
    return x.t * y.d < x.d * y.t;
}

long long ans = 0;
for (int i = 1; i <= n; i++) {
    ans += 2 * a[i].t * (sum[n] - sum[i]);
}
```

#### 2. 作者：lzqy_ (★★★★☆)
**关键亮点**：
- 使用前缀和优化计算花朵损失，代码实现清晰。
- 强调了数据类型转换的重要性，避免精度问题。
- 提供了详细的注释，便于理解。

**核心代码**：
```cpp
bool cmp(p a, p b) {
    return (double)a.D / a.T * 1.0 > (double)b.D / b.T * 1.0;
}

long long ans = 0;
for (int i = 0; i < n; i++) {
    ans += (p[n - 1] - p[i]) * a[i].T * 2;
}
```

#### 3. 作者：___new2zy___ (★★★★☆)
**关键亮点**：
- 通过数学推导详细解释了贪心策略的正确性。
- 代码结构清晰，使用了结构体和自定义排序函数。
- 强调了贪心策略的全局最优性。

**核心代码**：
```cpp
bool cmp(Cow x, Cow y) {
    double t1 = 1.0 * x.Ti / x.Di, t2 = 1.0 * y.Ti / y.Di;
    return t1 <= t2;
}

long long ans = 0;
for (int i = 1; i <= n; i++) {
    ans += T * p[i].Di;
    T += 2 * p[i].Ti;
}
```

### 最优关键思路与技巧

1. **贪心策略**：通过比较 `T_i / D_i` 的比值，确定奶牛的运输顺序，优先运输比值较小的奶牛。
2. **前缀和优化**：使用前缀和数组快速计算在运输某头奶牛时，其他奶牛吃掉的花朵数量。
3. **数据类型转换**：在比较比值时，注意将整数转换为浮点数，避免精度问题。

### 可拓展之处

- **类似问题**：其他需要确定顺序以最小化某种损失的问题，如任务调度、资源分配等。
- **算法套路**：贪心算法在解决局部最优问题时非常有效，但需要注意其全局最优性的证明。

### 推荐题目

1. **P1208 [USACO1.3]混合牛奶 Mixing Milk** - 贪心算法在资源分配中的应用。
2. **P1803 凌乱的yyy / 线段覆盖** - 贪心算法在区间选择问题中的应用。
3. **P1090 [NOIP2004 提高组] 合并果子** - 贪心算法在最小化合并成本问题中的应用。

### 个人心得总结

- **调试经历**：在比较比值时，数据类型转换不当可能导致精度问题，影响排序结果。
- **踩坑教训**：贪心策略的推导需要严谨的数学证明，不能仅凭直觉。
- **顿悟感想**：贪心算法的关键在于找到局部最优解，并通过局部最优解的组合得到全局最优解。

---
处理用时：36.00秒