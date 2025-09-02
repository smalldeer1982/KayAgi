# 题目信息

# Problem for Nazar

## 题目描述

Nazar, a student of the scientific lyceum of the Kingdom of Kremland, is known for his outstanding mathematical abilities. Today a math teacher gave him a very difficult task.

Consider two infinite sets of numbers. The first set consists of odd positive numbers ( $ 1, 3, 5, 7, \ldots $ ), and the second set consists of even positive numbers ( $ 2, 4, 6, 8, \ldots $ ). At the first stage, the teacher writes the first number on the endless blackboard from the first set, in the second stage — the first two numbers from the second set, on the third stage — the next four numbers from the first set, on the fourth — the next eight numbers from the second set and so on. In other words, at each stage, starting from the second, he writes out two times more numbers than at the previous one, and also changes the set from which these numbers are written out to another.

The ten first written numbers: $ 1, 2, 4, 3, 5, 7, 9, 6, 8, 10 $ . Let's number the numbers written, starting with one.

The task is to find the sum of numbers with numbers from $ l $ to $ r $ for given integers $ l $ and $ r $ . The answer may be big, so you need to find the remainder of the division by $ 1000000007 $ ( $ 10^9+7 $ ).

Nazar thought about this problem for a long time, but didn't come up with a solution. Help him solve this problem.

## 说明/提示

In the first example, the answer is the sum of the first three numbers written out ( $ 1 + 2 + 4 = 7 $ ).

In the second example, the numbers with numbers from $ 5 $ to $ 14 $ : $ 5, 7, 9, 6, 8, 10, 12, 14, 16, 18 $ . Their sum is $ 105 $ .

## 样例 #1

### 输入

```
1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
5 14
```

### 输出

```
105```

## 样例 #3

### 输入

```
88005553535 99999999999
```

### 输出

```
761141116```

# AI分析结果

### 题目翻译
# 给纳扎尔的问题

## 题目描述
纳扎尔是克雷姆兰王国科学中学的一名学生，以其卓越的数学能力而闻名。今天，一位数学老师给了他一道非常难的题目。

考虑两个无限的数字集合。第一个集合由正奇数（1, 3, 5, 7, …）组成，第二个集合由正偶数（2, 4, 6, 8, …）组成。在第一阶段，老师在无尽的黑板上写下第一个集合中的第一个数字；在第二阶段，写下第二个集合中的前两个数字；在第三阶段，写下第一个集合中的接下来四个数字；在第四阶段，写下第二个集合中的接下来八个数字，依此类推。换句话说，从第二阶段开始，每一个阶段写下的数字数量都是前一个阶段的两倍，并且每次都会切换数字的来源集合。

前十个写下的数字是：1, 2, 4, 3, 5, 7, 9, 6, 8, 10 。我们从1开始对写下的数字进行编号。

任务是对于给定的整数 $l$ 和 $r$，找出编号从 $l$ 到 $r$ 的数字之和。答案可能很大，所以需要求出该和除以 $1000000007$（$10^9 + 7$）的余数。

纳扎尔思考了这个问题很长时间，但没有想出解决方案。请帮助他解决这个问题。

## 说明/提示
在第一个示例中，答案是前三个写下的数字之和（$1 + 2 + 4 = 7$）。

在第二个示例中，编号从5到14的数字是：5, 7, 9, 6, 8, 10, 12, 14, 16, 18 。它们的和是105。

## 样例 #1
### 输入
```
1 3
```
### 输出
```
7
```

## 样例 #2
### 输入
```
5 14
```
### 输出
```
105
```

## 样例 #3
### 输入
```
88005553535 99999999999
```
### 输出
```
761141116
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先将求区间 $[l, r]$ 的和转化为求前缀和的差，即 $[1, r]$ 的和减去 $[1, l - 1]$ 的和。关键在于如何高效地求出前 $x$ 个数的和，各题解普遍利用了奇数和偶数序列的等差数列性质，通过不同方式统计奇数和偶数的个数，进而计算和。

### 所选题解
- **xrk2006（4星）**
    - **关键亮点**：思路清晰，详细阐述了二分查找确定轮数的过程，对每一步的计算都有明确解释，代码注释丰富，易于理解。
    - **个人心得**：作者提到在取模和负数保护方面挂了2小时，提醒大家要注意防止爆 `long long`。
- **Erusel（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，通过对数运算快速计算出奇数和偶数序列的长度，然后利用等差数列求和公式计算和。
- **Yuno（4星）**
    - **关键亮点**：同样思路清晰，直接利用等差数列求和公式，通过循环统计奇数和偶数的个数，代码实现简洁高效。

### 重点代码
#### xrk2006的核心代码
```cpp
int work(int x)
{
    int now=0,ret=0;
    for(int step=(1ll<<60);step>=1;step>>=1)
    {
        if(now+step<=60&&(1ll<<(now+step))-1<x)now+=step;
    }
    int L=now;
    int re=x-(1ll<<L)+1;
    int tt=L>>1;
    int num=sum2[tt];
    int tot1=num*2;
    int s1=(2+tot1)/2%mod*(num%mod)%mod;
    int kk=L-tt;
    num=sum1[kk];
    int tot2=num*2-1;
    int s2=(1+tot2)/2%mod*(num%mod)%mod;
    if(L&1)
    {
        (ret=(s1+s2)%mod+(tot1+2+tot1+re*2)/2%mod*(re%mod)%mod)%=mod;
    }
    else
    {
        (ret=(s1+s2)%mod+(tot2+2+tot2+re*2)/2%mod*(re%mod)%mod)%=mod;
    }
    return ret;
}
```
**核心实现思想**：通过二分查找确定前 $x$ 个数包含完整的轮数 $L$，然后分别计算前 $L$ 轮中奇数和偶数的和 $s1$ 和 $s2$，最后计算剩余部分的和并累加。

#### Erusel的核心代码
```cpp
ll solve(ll x)
{
    ll k=log2(x+1LL),c1=0LL,c2=0LL;
    for(ll i=0;i<k;i++)
    {
        if(i%2==1)c2=((1LL<<i)+c2)%mod;
        else c1=((1LL<<i)+c1)%mod;
    }
    ll t=(x-(1LL<<k)+1LL)%mod;
    if(k&1)c2=(t+c2)%mod;else c1=(t+c1)%mod;
    return (c1*c1%mod+c2*(c2+1)%mod+mod)%mod;
}
```
**核心实现思想**：利用对数运算确定最大的 $k$ 使得 $2^k - 1 < x$，然后统计前 $k$ 轮中奇数和偶数的个数 $c1$ 和 $c2$，再加上剩余部分的个数，最后根据等差数列求和公式计算和。

#### Yuno的核心代码
```cpp
int calc(int x) {
    int t = 1, flag = 1, cnt = 0, odd = 0, even = 0;
    while (cnt + t <= x) {
        cnt += t;
        if (flag) odd += t;
        else even += t;
        t <<= 1;
        flag ^= 1;
    }
    if (flag) odd += x - cnt;
    else even += x - cnt;
    odd %= mo;
    even %= mo;
    int res = ((sqr(odd) + sqr(even)) % mo + even) % mo;
    return res;
}
```
**核心实现思想**：通过循环统计前 $x$ 个数中奇数和偶数的个数，最后根据等差数列求和公式计算和。

### 关键思路或技巧
- **差分思想**：将求区间和转化为求前缀和的差，简化问题。
- **等差数列求和公式**：利用奇数序列前 $n$ 项和为 $n^2$，偶数序列前 $n$ 项和为 $n^2 + n$ 的性质，快速计算和。
- **对数运算或二分查找**：确定前 $x$ 个数包含的完整轮数，提高计算效率。

### 拓展思路
同类型题目可能会改变数字集合的规则或书写规则，但核心思路仍然是利用等差数列性质和差分思想。类似算法套路可用于处理其他与数列求和相关的问题，关键在于找出数列的规律并利用数学公式简化计算。

### 推荐题目
- [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：涉及递推和数学计算。
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：需要处理高精度和数学运算。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：与数学组合知识相关。

---
处理用时：54.51秒