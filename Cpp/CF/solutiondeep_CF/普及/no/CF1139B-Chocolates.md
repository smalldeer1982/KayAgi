# 题目信息

# Chocolates

## 题目描述

You went to the store, selling $ n $ types of chocolates. There are $ a_i $ chocolates of type $ i $ in stock.

You have unlimited amount of cash (so you are not restricted by any prices) and want to buy as many chocolates as possible. However if you buy $ x_i $ chocolates of type $ i $ (clearly, $ 0 \le x_i \le a_i $ ), then for all $ 1 \le j < i $ at least one of the following must hold:

- $ x_j = 0 $ (you bought zero chocolates of type $ j $ )
- $ x_j < x_i $ (you bought less chocolates of type $ j $ than of type $ i $ )

For example, the array $ x = [0, 0, 1, 2, 10] $ satisfies the requirement above (assuming that all $ a_i \ge x_i $ ), while arrays $ x = [0, 1, 0] $ , $ x = [5, 5] $ and $ x = [3, 2] $ don't.

Calculate the maximum number of chocolates you can buy.

## 说明/提示

In the first example, it is optimal to buy: $ 0 + 0 + 1 + 3 + 6 $ chocolates.

In the second example, it is optimal to buy: $ 1 + 2 + 3 + 4 + 10 $ chocolates.

In the third example, it is optimal to buy: $ 0 + 0 + 0 + 1 $ chocolates.

## 样例 #1

### 输入

```
5
1 2 1 3 6
```

### 输出

```
10```

## 样例 #2

### 输入

```
5
3 2 5 4 10
```

### 输出

```
20```

## 样例 #3

### 输入

```
4
1 1 1 1
```

### 输出

```
1```

# AI分析结果

### 题目内容重写（中文）

你去了一家商店，那里有 $n$ 种巧克力。第 $i$ 种巧克力的库存量为 $a_i$。

你有无限的钱（因此不受任何价格的限制），并且想买尽可能多的巧克力。然而，如果你购买了第 $i$ 种巧克力的 $x_i$ 个（显然，$0 \le x_i \le a_i$），那么对于所有 $1 \le j < i$，必须满足以下条件之一：

- $x_j = 0$（你没有购买第 $j$ 种巧克力）
- $x_j < x_i$（你购买的第 $j$ 种巧克力数量少于第 $i$ 种）

例如，数组 $x = [0, 0, 1, 2, 10]$ 满足上述要求（假设所有 $a_i \ge x_i$），而数组 $x = [0, 1, 0]$、$x = [5, 5]$ 和 $x = [3, 2]$ 不满足。

请计算你可以购买的最大巧克力数量。

### 算法分类
贪心

### 题解分析与结论

所有题解都采用了贪心算法，核心思路是从后向前遍历，每次取当前巧克力的库存量与上一个取的数量减一的最小值，确保满足题目的条件。这种方法的时间复杂度为 $O(n)$，空间复杂度为 $O(1)$，非常高效。

### 评分较高的题解

#### 题解1：Sammy_prime (4星)
**关键亮点**：
- 代码简洁，逻辑清晰。
- 使用了 `min` 函数来确保每次取的数量满足条件。
- 使用了 `long long` 类型来避免溢出。

**核心代码**：
```cpp
for(int i=n;i>=1;i--){
    minn=min(a[i],minn-1);
    if(minn>0) tot+=minn;
}
```

#### 题解2：xiaojuruo (4星)
**关键亮点**：
- 代码注释详细，易于理解。
- 使用了 `ans` 变量来记录上一次取的数量，确保每次取的数量满足条件。
- 处理了取到负数的情况，避免无效计算。

**核心代码**：
```cpp
for(int i=x;i>=1;i--){
    ans=min(a[i],ans-1);
    if(ans<=0) break;
    if(ans>0) sum+=ans;
}
```

#### 题解3：xht (4星)
**关键亮点**：
- 代码简洁，逻辑清晰。
- 使用了 `x` 变量来记录上一次取的数量，确保每次取的数量满足条件。
- 使用了 `long long` 类型来避免溢出。

**核心代码**：
```cpp
for (int i = n; i; i--) {
    x = min(a[i], x - 1);
    if (x > 0) ans += x;
}
```

### 最优关键思路或技巧
- **倒序遍历**：从后向前遍历可以确保每次取的数量满足条件，避免了复杂的条件判断。
- **贪心策略**：每次取当前库存量与上一次取的数量减一的最小值，确保最大化总数量。
- **数据类型选择**：使用 `long long` 类型来避免溢出问题。

### 可拓展之处
- **类似问题**：类似的问题可以在其他需要满足某种顺序条件的场景中应用，如购买物品、分配资源等。
- **算法优化**：可以进一步优化代码，减少不必要的变量和计算，提高代码的可读性和执行效率。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：27.08秒