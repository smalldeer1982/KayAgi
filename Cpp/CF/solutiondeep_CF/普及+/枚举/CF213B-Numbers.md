# 题目信息

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
36
```

# AI分析结果

### 题目内容（中文重写）
# 数字

## 题目描述
Furik喜欢编写各种各样的问题，尤其是那些他自己都无法解决的问题。你拿到了他出的一道题，这道题是Furik给Rubik的。而Rubik请你帮忙解决它。

有一个整数 $n$ 和一个由十个整数组成的数组 $a$，数组下标从0到9。你的任务是统计满足以下属性的正整数的数量：
- 该数字的长度不超过 $n$；
- 该数字没有前导零；
- 数字 $i$（$0 \leq i \leq 9$）在该数字中出现的次数至少为 $a[i]$ 次。

## 说明/提示
在第一个样例中，数字9满足要求。
在第二个样例中，数字10满足要求。
在第三个样例中，数字10、110、210、120、103满足要求。总共有36个符合要求的数字。

## 样例 #1
### 输入
```
1
0 0 0 0 0 0 0 0 0 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2
1 1 0 0 0 0 0 0 0 0
```
### 输出
```
1
```

## 样例 #3
### 输入
```
3
1 1 0 0 0 0 0 0 0 0
```
### 输出
```
36
```

### 题解综合分析与结论
1. **思路对比**：
    - **湖南省队御用绫厨TM_Sharweek**：尝试多种动态规划状态设计，最初设计的状态转移复杂且计算复杂度高。优化后用 $f_{i,S}$ 表示考虑前 $i$ 位，$S$ 内数位限制已满足的情况，但因重复计数问题失败。最终通过给限制满足规定从9往小的顺序，设计状态 $f_{i,j}$ 表示考虑到前 $i$ 位数，已满足 $a_j$ 至 $a_9$ 且后续不再添加相应数位的方案数。
    - **HBWH_zzz**：设 $f_{i,j}$ 表示只用 $j \sim 9$ 的数填满 $i$ 位（无 前导零），通过分析不同 $j$ 值下的转移方程，如 $f_{i,9}$ 只有一种填法，$j \in (0,9)$ 时在已有基础上插入 $j$ 并乘组合数，$f_{i,0}$ 因0不能在首位组合数变化，最终通过累加 $f_{i,0}$ 得到答案。
2. **算法要点对比**：
    - **湖南省队御用绫厨TM_Sharweek**：关键在于状态设计时对满足数位限制顺序的规定，利用组合数计算插入数位的方案数，边界条件为 $f_{0,10}=1$，时间复杂度为 $\Theta(|\Sigma|n^2)$（$|\Sigma| = 10$）。
    - **HBWH_zzz**：同样利用动态规划和组合数，通过不同 $j$ 值下的转移方程来计算方案数，转移时间复杂度为 $O(n^2 \times 10)$。
3. **解决难点对比**：
    - **湖南省队御用绫厨TM_Sharweek**：难点在于解决重复计数问题，通过规定数位限制满足顺序成功解决。
    - **HBWH_zzz**：主要难点在于准确分析不同数位情况下的转移方程，尤其是0不能在首位对组合数的影响。

### 所选的题解
- **湖南省队御用绫厨TM_Sharweek**：
    - **星级**：4星
    - **关键亮点**：详细探讨多种状态设计思路及失败原因，最终通过规定数位限制满足顺序成功解决重复计数问题，思路清晰，对动态规划状态设计优化过程展示详细。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
for (int i = 1; i <= n; i++) {
    c[0][i] = 1;
    for (int j = 1; j <= i; j++) {
        c[j][i] = (c[j - 1][i - 1] + c[j][i - 1]) % P;
    }
}
f[0][10] = 1;
for (int i = 0; i <= n; i++) {
    for (int j = 9; j >= 1; j--) {
        for (int k = 0; k <= i - a[j]; k++) {
            f[i][j] = (f[i][j] + f[k][j + 1] * c[i - k][i] % P) % P;
        }
    }
    for (int k = 0; k <= i - a[0]; k++) {
        f[i][0] = (f[i][0] + f[k][1] * c[i - k][i - 1] % P) % P;
    }
}
ll ans = 0;
for (int i = 1; i <= n; i++) {
    ans = (ans + f[i][0]) % P;
}
```
核心实现思想：先预处理组合数，然后通过三层循环进行状态转移，根据状态设计更新 $f$ 数组，最后累加 $f_{i,0}$ 得到答案。
- **HBWH_zzz**：
    - **星级**：4星
    - **关键亮点**：简洁明了地根据官方题解思路设计状态和转移方程，代码实现简洁，对转移方程的解释清晰。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
ll dp(int i, int j) {
    if (j == 9)
        return (i >= a[9]);
    if (f[i][j]!= -1)
        return f[i][j];
    if (j!= 0) {
        ll ret = 0;
        for (int k = a[j]; k <= i; ++k) {
            ret = (ret + dp(i - k, j + 1) * C[i][k]) % mod;
        }
        return f[i][j] = ret;
    }
    ll ret = 0;
    for (int k = a[0]; k <= i; ++k) {
        ret = (ret + dp(i - k, 1) * C[i - 1][k]) % mod;
    }
    return f[i][j] = ret;
}
```
核心实现思想：通过递归函数实现动态规划转移，根据不同的 $j$ 值计算 $f_{i,j}$，利用记忆化搜索避免重复计算。

### 最优关键思路或技巧
通过给数位限制满足规定顺序来避免重复计数，同时利用动态规划结合组合数计算满足条件的数字个数。在状态设计时，充分考虑前导零等限制条件对状态转移方程的影响。

### 可拓展之处
此类问题属于计数类动态规划，类似套路包括对复杂限制条件通过状态设计来简化，利用组合数解决排列组合问题。同类型题可能会改变数位限制条件，或者改变数字的进制等。

### 洛谷相似题目推荐
1. [P1282 多米诺骨牌](https://www.luogu.com.cn/problem/P1282)：涉及二维动态规划和计数问题。
2. [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)：状态压缩动态规划，与本题类似需考虑多种限制条件下的计数。
3. [P3216 [HNOI2011] 数学作业](https://www.luogu.com.cn/problem/P3216)：结合动态规划与高精度计算，在计数的同时处理大数问题。 

---
处理用时：35.07秒