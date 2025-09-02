# 题目信息

# Jellyfish and Green Apple

## 题目描述

Jellyfish has $ n $ green apple pieces. Each green apple piece weighs $ 1~\text{kg} $ . Jellyfish wants to divide these green apple pieces equally among $ m $ people.

Jellyfish has a magic knife. Each time Jellyfish can choose one piece of green apple and divide it into two smaller pieces, with each piece having half the weight of the original piece.

Jellyfish wants to know the minimum number of operations needed such that she can divide the green apple pieces such that the total weight of apple pieces received by each person is the same.

## 说明/提示

In the first test case, we do not need to divide the apple pieces. Each person will receive $ 2 $ pieces of $ 1~\text{kg} $ and the total weight of apple pieces received by each person is $ 2~\text{kg} $ .

In the second test case, it is impossible to divide the apple equally using a finite number of operations.

In the third test case, we can divide two of the apple pieces of weight $ 1~\text{kg} $ , getting $ 4 $ apple pieces of weight $ 0.5~\text{kg} $ . Each person will receive $ 1 $ apple piece of weight $ 0.5~\text{kg} $ and $ 2 $ apple pieces of weight $ 1~\text{kg} $ . The total weight of apple pieces received by each person is $ 2.5~\text{kg} $ .

In the fourth test case, we first divide all $ 3 $ of the apple pieces of weight $ 1~\text{kg} $ , getting $ 6 $ pieces of weight $ 0.5~\text{kg} $ . Then, we further divide two of the apple pieces of weight $ 0.5~\text{kg} $ , getting $ 4 $ pieces of weight $ 0.25~\text{kg} $ . Each person will receive $ 1 $ apple piece of weight $ 0.5~\text{kg} $ and $ 1 $ apple piece of weight $ 0.25~\text{kg} $ . The total weight of apples received by each person is $ 0.75~\text{kg} $ .

## 样例 #1

### 输入

```
4
10 5
1 5
10 4
3 4```

### 输出

```
0
-1
2
5```

# AI分析结果

### 题目内容重写

**题目描述**

Jellyfish 有 $n$ 块绿苹果，每块重 $1~\text{kg}$。Jellyfish 想要将这些苹果平均分给 $m$ 个人。

Jellyfish 有一把魔法刀，每次可以选择一块苹果并将其切成两块，每块重量为原苹果的一半。

Jellyfish 想知道，最少需要进行多少次操作，才能将这些苹果平均分配给每个人，使得每个人得到的苹果总重量相同。

**说明/提示**

- 在第一个测试用例中，不需要切割苹果。每个人将得到 $2$ 块 $1~\text{kg}$ 的苹果，总重量为 $2~\text{kg}$。
- 在第二个测试用例中，无法通过有限次操作将苹果平均分配。
- 在第三个测试用例中，可以将两块 $1~\text{kg}$ 的苹果各切一次，得到 $4$ 块 $0.5~\text{kg}$ 的苹果。每个人将得到 $1$ 块 $0.5~\text{kg}$ 和 $2$ 块 $1~\text{kg}$ 的苹果，总重量为 $2.5~\text{kg}$。
- 在第四个测试用例中，首先将 $3$ 块 $1~\text{kg}$ 的苹果各切一次，得到 $6$ 块 $0.5~\text{kg}$ 的苹果。然后，再将其中两块 $0.5~\text{kg}$ 的苹果各切一次，得到 $4$ 块 $0.25~\text{kg}$ 的苹果。每个人将得到 $1$ 块 $0.5~\text{kg}$ 和 $1$ 块 $0.25~\text{kg}$ 的苹果，总重量为 $0.75~\text{kg}$。

**样例输入**

```
4
10 5
1 5
10 4
3 4
```

**样例输出**

```
0
-1
2
5
```

### 算法分类
数学

### 题解分析与结论

1. **核心思路**：通过贪心策略，尽可能地将苹果块进行切割，使得每个人得到的苹果总重量相同。关键在于判断是否能够通过有限次切割实现平均分配，以及如何计算最小切割次数。
2. **难点**：判断无解的情况，以及如何高效地计算最小切割次数。
3. **优化**：通过数学方法（如最大公约数和二进制分解）来简化问题，减少计算量。

### 所选高星题解

#### 题解作者：One_JuRuo (5星)
**关键亮点**：
- 通过最大公约数（GCD）和二进制分解来判断无解情况。
- 使用贪心策略模拟切割过程，确保每次切割都是最优的。
- 代码简洁高效，时间复杂度为 $O(\log m)$。

**核心代码**：
```cpp
while(n) ans+=n,n*=2,n%=m;
```

#### 题解作者：cwl769 (4星)
**关键亮点**：
- 将问题分解为若干组，每组内苹果数和人数相同且互质。
- 通过二进制分解计算每组内的切割次数，再乘以组数得到总切割次数。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
for(;n;n-=(n&(-n))) {
    int x = (n&(-n));
    if(m>x){ans += 1ll * d * (m/x-1) * x;}
}
```

#### 题解作者：accgj_ (4星)
**关键亮点**：
- 通过贪心策略，先将可以整块分的苹果分完，再处理剩余的苹果。
- 使用最大公约数和二进制分解来判断无解情况。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
while(n!=0) {
    ans+=n*x;
    n=((n<<1)&(x1-1));
}
```

### 最优关键思路
1. **贪心策略**：尽可能地将苹果块进行切割，确保每次切割都是最优的。
2. **数学方法**：通过最大公约数和二进制分解来判断无解情况，并简化计算过程。
3. **模拟过程**：通过模拟切割过程，确保每次切割都能有效地减少问题规模。

### 可拓展之处
1. **类似问题**：可以扩展到其他需要平均分配的问题，如分糖果、分蛋糕等。
2. **算法套路**：贪心策略结合数学方法，可以应用于其他需要最优解的问题。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

### 个人心得
- **调试经历**：在判断无解情况时，需要仔细考虑数学条件，确保逻辑正确。
- **踩坑教训**：在处理切割次数时，需要注意边界条件，避免无限循环。
- **顿悟感想**：通过贪心策略和数学方法的结合，可以有效地解决复杂问题。

---
处理用时：32.84秒