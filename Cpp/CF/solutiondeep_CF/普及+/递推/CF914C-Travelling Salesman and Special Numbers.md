# 题目信息

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
111111011
2
```

### 输出

```
169
```

# AI分析结果

### 题目中文重写
# 旅行商与特殊数字

## 题目描述
旅行商花费大量时间旅行，因此他容易感到无聊。为了打发时间，他喜欢对数字进行操作。其中一种操作是取一个正整数 $x$，并将其简化为 $x$ 的二进制表示中值为 $1$ 的位数。例如，对于数字 $13$，$13_{10}=1101_{2}$，所以它有 $3$ 个值为 $1$ 的位，经过一次操作后，$13$ 将被简化为 $3$。

他将一个数字定义为特殊数字，如果将其简化为 $1$ 的最少操作次数为 $k$。

他想知道有多少个不大于 $n$ 的特殊数字存在。请帮助旅行商，因为他即将到达目的地！

由于答案可能很大，请将结果对 $10^{9}+7$ 取模后输出。

## 说明/提示
在第一个样例中，三个特殊数字是 $3$、$5$ 和 $6$。它们在一次操作中被简化为 $2$（因为 $3$、$5$ 和 $6$ 每个数的二进制表示中都有两个值为 $1$ 的位），然后在再一次操作中被简化为 $1$（因为 $2$ 的二进制表示中只有一个值为 $1$ 的位）。

## 样例 #1
### 输入
```
110
2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
111111011
2
```
### 输出
```
169
```

### 综合分析与结论
这些题解主要围绕旅行商与特殊数字问题展开，核心是找出不大于 $n$ 且将其变为 $1$ 的操作次数为 $k$ 的数的个数。大部分题解都采用了预处理和数位 DP 或组合数的方法。

- **思路对比**：多数题解先预处理出 1000 以内数变成 1 的最少操作次数，再用数位 DP 或组合数来计算满足条件的数的个数。部分题解还对 $k = 0$ 和 $k = 1$ 的情况进行了特判。
- **算法要点**：
    - **预处理**：通过循环或递归计算 1000 以内数的二进制中 1 的个数和变成 1 的操作次数。
    - **数位 DP**：记录当前数位、1 的个数和是否达到上界等状态，进行记忆化搜索。
    - **组合数**：利用组合数公式 $C_{m}^{n}=C_{m - 1}^{n - 1}+C_{m - 1}^{n}$ 计算方案数。
- **解决难点**：
    - **数据范围大**：通过一次操作将数缩小到 1000 以内，降低复杂度。
    - **边界情况**：对 $k = 0$ 和 $k = 1$ 进行特判，避免错误计算。

### 所选题解
- **Yt_pY（5星）**
    - **关键亮点**：思路清晰，代码结构简洁，对每个步骤的解释详细，数位 DP 过程易于理解。
- **一个句号（4星）**
    - **关键亮点**：提供了数位 DP 的模板化思路，对特判情况的逻辑解释详细，有助于理解数位 DP 的状态设计。
- **qwaszx（4星）**
    - **关键亮点**：结合组合数和数位 DP，代码简洁，对问题的分析准确，复杂度较低。

### 重点代码
#### Yt_pY 预处理部分
```cpp
inline int lowbit(int x){return x&(-x);}
void init()
{
    sum[0]=0;
    cnt[1]=0;
    for(int i=1;i<=1000;i++)sum[i]=sum[i^lowbit(i)]+1;
    for(int i=2;i<=1000;i++)cnt[i]=cnt[sum[i]]+1;
}
```
**核心思想**：利用 `lowbit` 函数计算每个数二进制中 1 的个数，再递推计算变成 1 的操作次数。

#### 一个句号 预处理部分
```cpp
int getbit(int x){
    int ans=0;
    while(x){
        if(x&1)++ans;
        x>>=1;
    }
    return ans;
}
int get_cnt(int x){
    if(x==1) return 0;
    return get_cnt(getbit(x))+1;
}
```
**核心思想**：`getbit` 函数统计二进制中 1 的个数，`get_cnt` 函数递归计算变成 1 的操作次数。

#### qwaszx 组合数预处理部分
```cpp
void make()
{
    c[0][0]=1;
    for(int i=1;i<=1000;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
}
```
**核心思想**：利用递推公式计算组合数。

### 最优关键思路或技巧
- **预处理**：先预处理出 1000 以内数变成 1 的最少操作次数，将问题简化。
- **数位 DP**：通过记录状态进行记忆化搜索，避免重复计算。
- **组合数**：利用组合数公式计算方案数，提高计算效率。

### 可拓展之处
同类型题可能会改变操作规则或数据范围，但解题思路类似，可先分析操作的性质，将数据范围缩小，再用数位 DP 或组合数求解。

### 洛谷相似题目
- [P2602 数字计数](https://www.luogu.com.cn/problem/P2602)
- [P4127 同类分布](https://www.luogu.com.cn/problem/P4127)
- [P3413 SAC#1 - 萌数](https://www.luogu.com.cn/problem/P3413)

### 个人心得摘录与总结
- **一个句号**：提到数位 DP 很板，但状态设计较难，$flag$ 为 0 时才记录答案，$zero$ 为 0 时才统计，输入时注意字符串和数组存储顺序相反。总结：数位 DP 模板性强，但状态设计需仔细考虑边界情况。
- **carp_oier**：模拟赛没做出该题，通过研究发现数据缩小很快，可求出变换次数上限并特判。总结：遇到难题可先分析数据性质，找出特殊情况进行特判。
- **弦巻こころ**：被特判恶心到，认为该题不需要数位 DP，用组合数 + 枚举和容斥思想即可解决。总结：特判情况需仔细处理，不同题目可尝试不同解法。 

---
处理用时：44.63秒