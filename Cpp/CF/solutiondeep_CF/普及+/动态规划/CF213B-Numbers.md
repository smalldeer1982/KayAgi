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

### 题目内容重写（中文）

#### 题目描述

Furik 喜欢编写各种问题，尤其是那些他自己也无法解决的问题。你得到了他给 Rubik 的一个问题，Rubik 请你来解决它。

给定一个整数 $n$ 和一个由 10 个整数组成的数组 $a$，数组下标从 0 到 9。你的任务是计算满足以下条件的正整数的数量：

- 该数的长度不超过 $n$；
- 该数没有前导零；
- 数字 $i$（$0 \leq i \leq 9$）在该数中至少出现 $a[i]$ 次。

#### 说明/提示

- 在第一个样例中，数字 9 满足要求。
- 在第二个样例中，数字 10 满足要求。
- 在第三个样例中，数字 10、110、210、120、103 满足要求。还有其他符合条件的数字，总共有 36 个。

#### 样例 #1

##### 输入

```
1
0 0 0 0 0 0 0 0 0 1
```

##### 输出

```
1
```

#### 样例 #2

##### 输入

```
2
1 1 0 0 0 0 0 0 0 0
```

##### 输出

```
1
```

#### 样例 #3

##### 输入

```
3
1 1 0 0 0 0 0 0 0 0
```

##### 输出

```
36
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何高效地计算满足条件的数字数量。由于涉及到数字的位数和每个数字的出现次数，直接枚举所有可能的数字是不现实的。因此，动态规划（DP）是解决此类问题的常用方法。

通过对多个题解的分析，可以发现以下关键点：

1. **状态设计**：大多数题解采用了 DP 的状态设计，通常以数字的位数和已经满足的数字限制作为状态。
2. **转移方程**：通过组合数来计算在某个状态下插入特定数字的方案数，并注意前导零的限制。
3. **优化思路**：为了避免重复计算，题解中采用了从大到小逐个满足数字限制的策略，并利用组合数进行转移。

#### 所选高分题解

##### 题解1：湖南省队御用绫厨TM_Sharweek（5星）

- **关键亮点**：
  - 详细的状态设计和转移方程推导，解释了如何避免重复计算。
  - 通过从大到小逐个满足数字限制，简化了状态转移。
  - 代码实现清晰，组合数预处理和 DP 转移逻辑明确。

- **核心代码**：
```cpp
ll f[N][15];
ll c[N][N];
int a[15];

int main() {
    // 预处理组合数
    c[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        c[0][i] = 1;
        for (int j = 1; j <= i; j++) {
            c[j][i] = (c[j - 1][i - 1] + c[j][i - 1]) % P;
        }
    }
    // DP 转移
    f[0][10] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 9; j >= 1; j--) {
            for (int k = 0; k <= i-a[j]; k++) {
                f[i][j] = (f[i][j] + f[k][j + 1] * c[i-k][i] % P) % P;
            }
        }
        for (int k = 0; k <= i-a[0]; k++) {
            f[i][0] = (f[i][0] + f[k][1] * c[i-k][i - 1] % P) % P;
        }
    }
    // 计算答案
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + f[i][0]) % P;
    }
    cout << ans << endl;
    return 0;
}
```

##### 题解2：HBWH_zzz（4星）

- **关键亮点**：
  - 简洁的状态设计和转移方程，直接从官方题解中借鉴了思路。
  - 通过记忆化搜索实现 DP，代码结构清晰。

- **核心代码**：
```cpp
ll dp(int i,int j){
    if(j==9)
        return (i>=a[9]);
    if(f[i][j]!=-1)
        return f[i][j];
    if(j!=0){
        ll ret=0;
        for(int k=a[j];k<=i;++k){
            ret=(ret+dp(i-k,j+1)*C[i][k])%mod;
        }
        return f[i][j]=ret;
    }
    ll ret=0;
    for(int k=a[0];k<=i;++k){
        ret=(ret+dp(i-k,1)*C[i-1][k])%mod;
    }
    return f[i][j]=ret;
}
```

### 最优关键思路与技巧

1. **状态设计**：从大到小逐个满足数字限制，避免重复计算。
2. **组合数预处理**：利用组合数计算在某个状态下插入特定数字的方案数。
3. **前导零处理**：在插入数字 0 时，特别注意不能放在首位，使用 $\binom{i-1}{k}$ 进行计算。

### 可拓展之处

- **类似问题**：可以扩展到更复杂的数字限制问题，如多个数字的出现次数限制、数字排列的特定模式等。
- **算法套路**：动态规划结合组合数的思路可以应用于其他计数问题，如字符串匹配、排列组合等。

### 推荐题目

1. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 考察动态规划与组合数的应用。
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028) - 动态规划计数问题。
3. [P1077 摆花](https://www.luogu.com.cn/problem/P1077) - 动态规划与组合数的结合。

### 个人心得摘录

- **调试经历**：在实现过程中，发现重复计数的问题，通过调整状态设计和转移顺序解决了问题。
- **顿悟感想**：从大到小逐个满足数字限制的策略，避免了重复计算，简化了状态转移。

---
处理用时：58.06秒