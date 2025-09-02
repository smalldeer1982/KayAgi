# 题目信息

# Powered Addition

## 题目描述

You have an array $ a $ of length $ n $ . For every positive integer $ x $ you are going to perform the following operation during the $ x $ -th second:

- Select some distinct indices $ i_{1}, i_{2}, \ldots, i_{k} $ which are between $ 1 $ and $ n $ inclusive, and add $ 2^{x-1} $ to each corresponding position of $ a $ . Formally, $ a_{i_{j}} := a_{i_{j}} + 2^{x-1} $ for $ j = 1, 2, \ldots, k $ . Note that you are allowed to not select any indices at all.

You have to make $ a $ nondecreasing as fast as possible. Find the smallest number $ T $ such that you can make the array nondecreasing after at most $ T $ seconds.

Array $ a $ is nondecreasing if and only if $ a_{1} \le a_{2} \le \ldots \le a_{n} $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case, if you select indices $ 3, 4 $ at the $ 1 $ -st second and $ 4 $ at the $ 2 $ -nd second, then $ a $ will become $ [1, 7, 7, 8] $ . There are some other possible ways to make $ a $ nondecreasing in $ 2 $ seconds, but you can't do it faster.

In the second test case, $ a $ is already nondecreasing, so answer is $ 0 $ .

In the third test case, if you do nothing at first $ 2 $ seconds and select index $ 2 $ at the $ 3 $ -rd second, $ a $ will become $ [0, 0] $ .

## 样例 #1

### 输入

```
3
4
1 7 6 5
5
1 2 3 4 5
2
0 -4```

### 输出

```
2
0
3```

# AI分析结果

### 题目内容重写
#### 题目描述
你有一个长度为 $n$ 的数组 $a$。对于每一个正整数 $x$，你将在第 $x$ 秒执行以下操作：

- 选择一些不同的下标 $i_{1}, i_{2}, \ldots, i_{k}$（$1 \leq i_{j} \leq n$），并在数组 $a$ 的对应位置上加上 $2^{x-1}$。形式化地，$a_{i_{j}} := a_{i_{j}} + 2^{x-1}$，其中 $j = 1, 2, \ldots, k$。注意，你可以选择不进行任何操作。

你需要尽可能快地使数组 $a$ 变为非递减的。找到最小的 $T$，使得你可以在最多 $T$ 秒内使数组 $a$ 变为非递减的。

数组 $a$ 是非递减的当且仅当 $a_{1} \le a_{2} \le \ldots \le a_{n}$。

你需要回答 $t$ 个独立的测试用例。

#### 说明/提示
在第一个测试用例中，如果你在第 $1$ 秒选择下标 $3, 4$，并在第 $2$ 秒选择下标 $4$，那么 $a$ 将变为 $[1, 7, 7, 8]$。还有其他方法可以在 $2$ 秒内使 $a$ 变为非递减的，但你无法更快地完成。

在第二个测试用例中，$a$ 已经是非递减的，所以答案是 $0$。

在第三个测试用例中，如果你在前 $2$ 秒不进行任何操作，并在第 $3$ 秒选择下标 $2$，那么 $a$ 将变为 $[0, 0]$。

#### 样例 #1
##### 输入
```
3
4
1 7 6 5
5
1 2 3 4 5
2
0 -4
```

##### 输出
```
2
0
3
```

### 算法分类
贪心、构造

### 题解分析与结论
本题的核心思路是通过贪心算法，找到使数组非递减所需的最小操作次数。大多数题解都采用了类似的方法，即通过遍历数组，计算每个元素与前一个元素的差值，并找到最大差值所需的二进制位数。

#### 最优关键思路
1. **贪心策略**：对于每个元素，如果它比前一个元素小，则计算它与前一个元素的差值，并找到该差值的二进制位数。这个位数即为所需的操作次数。
2. **二进制分解**：由于每次操作可以加上 $2^{x-1}$，因此差值的二进制位数决定了需要的最少操作次数。
3. **最大差值**：最终的操作次数由数组中的最大差值决定，因为其他较小的差值可以在操作过程中被覆盖。

#### 可拓展之处
类似的问题可以通过贪心策略和二进制分解来解决，尤其是在涉及到最小化操作次数或最大化某种效益的情况下。例如，类似的题目可以涉及通过最少的操作次数使数组满足某种条件，或者通过最少的步骤达到某种目标。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 精选题解
#### 题解1：作者：一扶苏一 (赞：13)
##### 星级：5星
##### 关键亮点
- **构造思路**：通过构造一个序列 $b$，使得 $a + b$ 非递减，并最小化 $b$ 的最大值。
- **贪心策略**：直接计算每个元素与前一个元素的差值，并更新 $b$ 的值。
- **代码简洁**：代码实现清晰，逻辑简单。

##### 核心代码
```cpp
int lg2(ll x) {
  int ret = 0;
  while ((1ll << ret) <= x) ++ret;
  return ret;
}

void Main() {
  int t;
  for (qr(t); t; --t) {
    qr(n);
    int ans = 0;
    qra(a + 1, n);
    b[1] = 0;
    for (int i = 2; i <= n; ++i) {
      b[i] = std::max(0ll, b[i - 1] + a[i - 1] - a[i]);
      ans = std::max(ans, lg2(b[i]));
    }
    qw(ans, '\n');
  }
}
```

#### 题解2：作者：Wenoide (赞：6)
##### 星级：4星
##### 关键亮点
- **最大差值**：通过计算数组中的最大差值，并找到其二进制位数来确定操作次数。
- **数学推导**：利用 $2^x$ 的性质，推导出操作次数的计算公式。
- **代码简洁**：代码实现简单，逻辑清晰。

##### 核心代码
```cpp
int cnt = 0;
while (ans != 0) {
  ans >>= 1;
  ++cnt;
}
printf("%d\n", cnt);
```

#### 题解3：作者：lgswdn_SA (赞：4)
##### 星级：4星
##### 关键亮点
- **倍增思想**：通过倒序倍增的方式，找到每个元素需要的最小操作次数。
- **贪心策略**：对于每个元素，如果它比前一个元素小，则通过倍增找到需要的最小操作次数。
- **代码实现**：代码逻辑清晰，实现较为简洁。

##### 核心代码
```cpp
for (int j = 60; j >= 1; j--) {
  if (a[i] + (1ll << (j - 1)) <= a[i - 1]) {
    mx = max(mx, j);
    a[i] += (1ll << (j - 1));
  }
}
```

### 总结
本题的核心在于通过贪心策略和二进制分解，找到使数组非递减所需的最小操作次数。推荐的题解都采用了类似的方法，且代码实现简洁，逻辑清晰。

---
处理用时：40.19秒