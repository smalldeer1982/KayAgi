# 题目信息

# Levko and Permutation

## 题目描述

Levko loves permutations very much. A permutation of length $ n $ is a sequence of distinct positive integers, each is at most $ n $ .

Let’s assume that value $ gcd(a,b) $ shows the greatest common divisor of numbers $ a $ and $ b $ . Levko assumes that element $ p_{i} $ of permutation $ p_{1},p_{2},...\ ,p_{n} $ is good if $ gcd(i,p_{i})&gt;1 $ . Levko considers a permutation beautiful, if it has exactly $ k $ good elements. Unfortunately, he doesn’t know any beautiful permutation. Your task is to help him to find at least one of them.

## 说明/提示

In the first sample elements $ 4 $ and $ 3 $ are good because $ gcd(2,4)=2&gt;1 $ and $ gcd(3,3)=3&gt;1 $ . Elements $ 2 $ and $ 1 $ are not good because $ gcd(1,2)=1 $ and $ gcd(4,1)=1 $ . As there are exactly 2 good elements, the permutation is beautiful.

The second sample has no beautiful permutations.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
2 4 3 1```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
-1
```

# AI分析结果



# Levko and Permutation

## 题目描述

Levko 特别喜欢排列。一个长度为 $n$ 的排列是指由 $1$ 到 $n$ 组成的序列，且每个元素恰好出现一次。

定义 $gcd(a,b)$ 为 $a$ 和 $b$ 的最大公约数。Levko 认为排列中的元素 $p_i$ 是"好的"当且仅当 $gcd(i, p_i) > 1$。若一个排列恰好有 $k$ 个"好的"元素，则称其为美丽的排列。请帮助 Levko 构造一个美丽排列，若无法构造则输出 $-1$。

## 说明/提示

- 当 $k = n$ 时，由于位置 $1$ 的 $gcd(1, p_1) = 1$ 必然不满足条件，此时无解。
- 构造时需保证排列的合法性（元素互异且属于 $[1,n]$）。

## 样例 #1

### 输入
```
4 2
```

### 输出
```
2 4 3 1
```

## 样例 #2

### 输入
```
1 1
```

### 输出
```
-1
```

**算法分类**：构造

---

## 题解分析与结论

### 题解对比与评分
1. **流绪（5星）**
   - **关键亮点**：利用相邻互质性质，将前 $n-k$ 个元素后移一位形成互质段，剩余部分保持自身。
   - **代码核心**：
     ```cpp
     cout << n-k << " ";
     for(int i=2;i<=n-k;i++) cout << i-1 << " ";
     for(int i=n-k+1;i<=n;i++) cout << i << " ";
     ```
     - 前 $n-k-1$ 个元素后移，将 $1$ 放置在 $n-k$ 位，后续元素保持原值。

2. **Yamchip（4星）**
   - **关键亮点**：类似移位思路，代码结构清晰但未显式处理 $1$ 的位置。
   - **代码核心**：
     ```cpp
     for(int i=1;i < n - k; i++) cout << i+1 << " ";
     cout << "1 ";
     for(int i=n-k+1;i<=n;i++) cout << i << " ";
     ```

3. **JoyLosingK（4星）**
   - **关键亮点**：思路与流绪一致，变量命名更直观。
   - **代码核心**：
     ```cpp
     cout<<n-k<<" ";
     for(int i=2;i<=n;i++)
         if(i<=n-k) cout<<i-1<<" ";
         else cout<<i<<" ";
     ```

### 最优思路总结
1. **特判无解**：当 $k=n$ 时直接输出 $-1$。
2. **构造互质段**：前 $n-k$ 个元素整体右移（如 $i$ 的位置放 $i+1$），并在末尾放置 $1$，确保这些位置的 $\gcd(i,p_i)=1$。
3. **构造非互质段**：剩余 $k$ 个元素保持 $p_i=i$，利用 $\gcd(i,i)=i>1$ 的特性。

### 关键代码实现
```cpp
if(n == k) cout << -1;
else {
    cout << n - k << " ";
    for(int i = 2; i <= n - k; i++) cout << i - 1 << " ";
    cout << 1 << " ";
    for(int i = n - k + 1; i <= n; i++) cout << i << " ";
}
```

### 拓展与心得
- **同类型题**：P9632（互质排列构造）
- **构造技巧**：利用数论性质（相邻互质、自身非互质）快速定位有效段。
- **调试心得**：特别注意边界情况（如 $n-k=1$ 时需正确放置 $1$）。

---

## 相似题目推荐
1. [P9632 - K Co-prime Permutation](https://www.luogu.com.cn/problem/P9632)  
2. [P1360 - 互质排列](https://www.luogu.com.cn/problem/P1360)  
3. [CF1294D - MEX maximizing](https://codeforces.com/problemset/problem/1294/D)（构造思维的扩展应用）

---
处理用时：61.83秒