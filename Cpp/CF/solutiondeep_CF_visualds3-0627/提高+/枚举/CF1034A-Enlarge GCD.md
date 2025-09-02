# 题目信息

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# AI分析结果



## 算法分类
数论、筛法、最大公约数

---

## 综合分析与结论
### 核心思路
1. **问题转化**：将原数组所有元素除以原GCD，转化为求新数组的最大公约数大于1的问题。
2. **质数枚举**：通过筛法预处理质数，统计每个质数的倍数出现次数。最优解对应出现次数最多的质数。
3. **统计优化**：利用埃氏筛或线性筛遍历质数的倍数，避免逐个分解每个数的质因数，时间复杂度降至O(m log log m)，其中m为最大值。

### 解决难点
- **高效统计质数倍数**：通过筛法直接统计所有质数的倍数出现次数，避免分解每个数。
- **处理大值域**：利用数组计数和筛法优化，处理1.5e7级别的数域。

### 可视化设计
1. **像素化筛法演示**：用不同颜色方块表示数，当筛到质数时，高亮其所有倍数，并实时更新计数器。
2. **步进控制**：允许单步执行筛法，观察每个质数的倍数统计过程。
3. **音效反馈**：质数被选中时播放音效，统计完成时根据结果播放成功/失败音效。

---

## 题解评分（≥4星）
1. **Siyuan（优化思路）** ★★★★☆  
   - 利用筛法统计质数倍数出现次数，时间复杂度低。
   - 代码清晰，逻辑简洁，预处理原数组后直接遍历质数。

2. **Acc_Robin** ★★★★☆  
   - 补充了严格的复杂度分析，证明筛法复杂度为O(m log log m)。
   - 代码使用STL容器优化内存，统计时动态筛质数。

3. **loser_seele** ★★★★  
   - 线性筛预处理最小质因数，分解质因数统计出现次数。
   - 时间复杂度O(n log a_i)，适合数域分散但较小的场景。

---

## 最优思路提炼
1. **预处理原数组**：所有数除以原GCD，简化问题为求新数组GCD>1。
2. **筛法统计质数**：埃氏筛或线性筛预处理质数，遍历每个质数的倍数统计出现次数。
3. **最大次数决策**：取出现次数最多的质数，计算最少删除数n - max_count。

**关键代码片段（Siyuan优化思路）**：
```cpp
int d = gcd(a[1], a[2]); // 计算原GCD
for (int i = 1; i <= n; ++i) a[i] /= d;
sieve(max_value); // 筛质数到最大值
for (int p : primes) {
    int cnt = 0;
    for (int j = p; j <= max_value; j += p)
        cnt += count[j]; // 统计质数p的倍数出现次数
    ans = min(ans, n - cnt);
}
```

---

## 相似题目推荐
1. **P1029 最大公约数和最小公倍数问题**  
   - 质因数分解与GCD/LCM关系。
2. **P1072 Hankson的趣味题**  
   - 结合质因数分解的条件判断。
3. **P2158 [SDOI2008] 仪仗队**  
   - 筛法求欧拉函数，统计互质数目。

---

## 可视化算法演示
**核心流程**：
1. **初始状态**：显示原数组元素，高亮当前GCD。
2. **除以GCD**：所有元素缩小为原值/GCD，颜色变浅。
3. **筛法过程**：从左到右遍历数轴，质数标记为红色，其倍数标记为黄色。
4. **统计计数**：每个质数的倍数数目以计数器形式实时更新。
5. **结果高亮**：最终选中出现次数最多的质数，显示对应删除数目。

**复古像素风格**：
- 使用16色调色板，质数为红色，倍数为黄色。
- 背景音乐为8-bit循环音轨，质数选中时播放“哔”声，统计完成时播放胜利音效。

---

**注**：以上内容整合了各题解的核心思想与优化策略，重点突出筛法的统计技巧和复杂度优化，为同类数论问题提供了通用解决框架。

---
处理用时：151.56秒