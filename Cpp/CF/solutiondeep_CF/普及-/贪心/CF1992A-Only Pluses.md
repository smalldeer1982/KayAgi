# 题目信息

# Only Pluses

## 题目描述

Kmes has written three integers $ a $ , $ b $ and $ c $ in order to remember that he has to give Noobish\_Monk $ a \times b \times c $ bananas.

Noobish\_Monk has found these integers and decided to do the following at most $ 5 $ times:

- pick one of these integers;
- increase it by $ 1 $ .

For example, if $ a = 2 $ , $ b = 3 $ and $ c = 4 $ , then one can increase $ a $ three times by one and increase $ b $ two times. After that $ a = 5 $ , $ b = 5 $ , $ c = 4 $ . Then the total number of bananas will be $ 5 \times 5 \times 4 = 100 $ .

What is the maximum value of $ a \times b \times c $ Noobish\_Monk can achieve with these operations?

## 样例 #1

### 输入

```
2
2 3 4
10 1 10```

### 输出

```
100
600```

# AI分析结果



# Only Pluses

## 题目描述

Kmes 写下了三个整数 $a$、$b$ 和 $c$，以提醒自己需要给 Noobish_Monk $a \times b \times c$ 根香蕉。

Noobish_Monk 发现了这些整数，并决定最多进行 $5$ 次操作：

- 选择其中一个整数；
- 将其增加 $1$。

例如，若 $a = 2$、$b = 3$、$c = 4$，可以将 $a$ 增加 3 次，$b$ 增加 2 次。最终 $a = 5$、$b = 5$、$c = 4$，香蕉总数为 $5 \times 5 \times 4 = 100$。

求通过这些操作后，$a \times b \times c$ 的最大值是多少？

## 样例 #1

### 输入

```
2
2 3 4
10 1 10
```

### 输出

```
100
600
```

---

### 综合分析与结论

题目要求通过最多5次加1操作，最大化三个整数的乘积。关键难点在于如何合理分配有限的5次操作次数。通过分析，最优解法需要枚举所有可能的分配组合，而非依赖贪心策略，以确保覆盖所有可能的最优解。

#### 关键思路
1. **穷举所有分配方案**：枚举所有满足 $x + y + z \leq 5$ 的非负整数组合（$x, y, z$ 分别为三个数的加1次数），计算每种分配后的乘积。
2. **三重循环实现**：通过三层循环遍历所有可能的 $x, y, z$ 值，确保覆盖所有操作次数组合。
3. **计算最大值**：对每个可能的组合计算乘积并记录最大值。

#### 题解对比与评分

（当前无用户提交题解，以下为推荐的解题思路）

---

### 推荐代码实现

```python
a, b, c = map(int, input().split())
max_val = 0
for x in range(6):
    for y in range(6 - x):
        for z in range(5 - x - y + 1):
            na = a + x
            nb = b + y
            nc = c + z
            current = na * nb * nc
            if current > max_val:
                max_val = current
print(max_val)
```

**核心思想**：通过三重循环遍历所有可能的操作次数分配，确保计算每个组合的乘积，最终取最大值。时间复杂度为 $O(1)$，最多执行 56 次循环。

---

### 拓展与举一反三

1. **同类问题**：类似的最优化问题（如资源分配、步数限制下的极值）通常可通过枚举或动态规划解决。
2. **优化思维**：当操作次数较多时，可结合数学推导（如均值不等式）优化分配策略，但需注意边界条件。
3. **相关题目**：
   - 洛谷 P1036 [选数](https://www.luogu.com.cn/problem/P1036)（枚举组合）
   - 洛谷 P2392 [kkksc03考前临时抱佛脚](https://www.luogu.com.cn/problem/P2392)（资源分配优化）
   - 洛谷 P1443 [马的遍历](https://www.luogu.com.cn/problem/P1443)（步数限制下的BFS）

---
处理用时：238.91秒