# 题目信息

# Prefix Purchase

## 题目描述

You have an array $ a $ of size $ n $ , initially filled with zeros ( $ a_1 = a_2 = \ldots = a_n = 0 $ ). You also have an array of integers $ c $ of size $ n $ .

Initially, you have $ k $ coins. By paying $ c_i $ coins, you can add $ 1 $ to all elements of the array $ a $ from the first to the $ i $ -th element ( $ a_j \mathrel{+}= 1 $ for all $ 1 \leq j \leq i $ ). You can buy any $ c_i $ any number of times. A purchase is only possible if $ k \geq c_i $ , meaning that at any moment $ k \geq 0 $ must hold true.

Find the lexicographically largest array $ a $ that can be obtained.

An array $ a $ is lexicographically smaller than an array $ b $ of the same length if and only if in the first position where $ a $ and $ b $ differ, the element in array $ a $ is smaller than the corresponding element in $ b $ .

## 说明/提示

In the first test case, $ a_1 $ cannot be greater than $ 5 $ , and if we buy $ c_1 $ five times, we will run out of money, so $ a = [5, 0, 0] $ .

In the second test case, $ a_1 $ cannot be greater than $ 2 $ , but we can buy $ c_1 $ and $ c_2 $ once each (buying $ c_2 $ twice is not possible), so $ a = [2, 1] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
5
2
3 4
7
3
3 2 1
2
6
10 6 4 6 3 4
7```

### 输出

```
5 0 0 
2 1 
2 2 2 
2 2 2 2 2 1```

# AI分析结果

### 题目内容重写
#### 前缀购买

##### 题目描述
你有一个大小为 $n$ 的数组 $a$，初始时所有元素都为 $0$（即 $a_1 = a_2 = \ldots = a_n = 0$）。你还有一个大小为 $n$ 的整数数组 $c$。

初始时，你有 $k$ 个硬币。通过支付 $c_i$ 个硬币，你可以将数组 $a$ 中从第 $1$ 个到第 $i$ 个元素的所有元素加 $1$（即 $a_j \mathrel{+}= 1$，其中 $1 \leq j \leq i$）。你可以多次购买任何 $c_i$。只有当 $k \geq c_i$ 时才能进行购买，即任何时候都必须满足 $k \geq 0$。

请找到可以获得的最大字典序数组 $a$。

一个数组 $a$ 的字典序小于另一个相同长度的数组 $b$，当且仅当在第一个 $a$ 和 $b$ 不同的位置，$a$ 中的元素小于 $b$ 中的对应元素。

##### 说明/提示
在第一个测试用例中，$a_1$ 不能大于 $5$，如果我们购买 $c_1$ 五次，我们将用完所有的钱，因此 $a = [5, 0, 0]$。

在第二个测试用例中，$a_1$ 不能大于 $2$，但我们可以分别购买 $c_1$ 和 $c_2$ 各一次（不能购买 $c_2$ 两次），因此 $a = [2, 1]$。

##### 样例 #1
###### 输入
```
4
3
1 2 3
5
2
3 4
7
3
3 2 1
2
6
10 6 4 6 3 4
7
```

###### 输出
```
5 0 0 
2 1 
2 2 2 
2 2 2 2 2 1
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心算法，尽可能多地增加数组的前缀元素，以达到字典序最大的目的。大多数题解都采用了类似的后缀最小值处理策略，以确保在花费最少的情况下尽可能多地增加前缀元素。

### 评分较高的题解

#### 题解1：作者：Creeper_l (赞：10)
**星级：5星**
**关键亮点：**
- 通过后缀最小值处理，确保花费最小。
- 详细解释了贪心策略，确保字典序最大。
- 代码简洁且高效，处理了边界情况。

**核心代码：**
```cpp
for(int i = n; i >= 1; i--) mn = min(mn, a[i]), a[i] = mn; 
for(int i = 1; i <= n; i++) {
    if(a[i] - a[i - 1] == 0) ans[i] = ans[i - 1];
    else ans[i] = min(k / (a[i] - a[i - 1]), ans[i - 1]);
    cout << ans[i] << " ";
    k -= (a[i] - a[i - 1]) * ans[i];
}
```

#### 题解2：作者：Xy_top (赞：6)
**星级：4星**
**关键亮点：**
- 使用单调栈处理后缀最小值，确保花费最小。
- 通过贪心策略，尽可能多地增加前缀元素。
- 代码实现清晰，处理了边界情况。

**核心代码：**
```cpp
For (i, 2, n) {
    while (tp && a[i] <= tb[tp]) -- tp;
    tb[++ tp] = a[i];
    loc[tp] = i;
}
```

#### 题解3：作者：LIUYC_C (赞：2)
**星级：4星**
**关键亮点：**
- 通过贪心策略，尽可能多地增加前缀元素。
- 详细解释了如何处理余数，确保字典序最大。
- 代码实现简洁，处理了边界情况。

**核心代码：**
```cpp
for(int i = l; i <= n; i++) {
    if(k / (c[i] - pre) >= num) {
        num = k / (c[i] - pre);
        r = i;
    }
}
```

### 最优关键思路或技巧
1. **后缀最小值处理**：通过处理后缀最小值，确保在花费最少的情况下尽可能多地增加前缀元素。
2. **贪心策略**：优先增加前面的元素，确保字典序最大。
3. **边界处理**：处理了花费为0的情况，确保代码的健壮性。

### 可拓展之处
类似的问题可以通过贪心算法和前缀/后缀处理来解决，例如在资源分配问题中，优先分配资源给前面的任务，以达到最优解。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录
- **Creeper_l**：通过处理后缀最小值，确保花费最小，同时通过贪心策略确保字典序最大。
- **Xy_top**：使用单调栈处理后缀最小值，确保花费最小，同时通过贪心策略尽可能多地增加前缀元素。
- **LIUYC_C**：通过贪心策略，尽可能多地增加前缀元素，同时处理了余数，确保字典序最大。

---
处理用时：45.86秒