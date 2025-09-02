# 题目信息

# On Number of Decompositions into Multipliers

## 题目描述

You are given an integer $ m $ as a product of integers $ a_{1},a_{2},...\ a_{n} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/511aaee908ff3da31c1047aebc73037f3c2d6e3f.png). Your task is to find the number of distinct decompositions of number $ m $ into the product of $ n $ ordered positive integers.

Decomposition into $ n $ products, given in the input, must also be considered in the answer. As the answer can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the second sample, the get a decomposition of number 2, you need any one number out of three to equal 2, and the rest to equal 1.

In the third sample, the possible ways of decomposing into ordered multipliers are \[7,5\], \[5,7\], \[1,35\], \[35,1\].

A decomposition of positive integer $ m $ into $ n $ ordered multipliers is a cortege of positive integers $ b={b_{1},b_{2},...\ b_{n}} $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/b461305f46e6043012038c3479cb445ca537b144.png). Two decompositions $ b $ and $ c $ are considered different, if there exists index $ i $ such that $ b_{i}≠c_{i} $ .

## 样例 #1

### 输入

```
1
15
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
5 7
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 因数分解的数量
## 题目描述
给定一个整数 $m$，它是整数 $a_{1},a_{2},\cdots,a_{n}$ 的乘积。你的任务是找出将数字 $m$ 分解为 $n$ 个有序正整数乘积的不同分解方式的数量。

输入中给出的分解为 $n$ 个乘积的情况也必须包含在答案中。由于答案可能非常大，请将其对 $1000000007$（$10^{9}+7$）取模后输出。
## 说明/提示
在第二个样例中，要得到数字 $2$ 的分解，需要三个数中的任意一个等于 $2$，其余的等于 $1$。

在第三个样例中，分解为有序因数的可能方式有 \[7,5\], \[5,7\], \[1,35\], \[35,1\]。

正整数 $m$ 分解为 $n$ 个有序因数是一个正整数序列 $b = \{b_{1},b_{2},\cdots,b_{n}\}$，使得 $\prod_{i = 1}^{n}b_{i}=m$。如果存在索引 $i$ 使得 $b_{i}\neq c_{i}$，则认为两个分解 $b$ 和 $c$ 是不同的。
## 样例 #1
### 输入
```
1
15
```
### 输出
```
1
```
## 样例 #2
### 输入
```
3
1 1 2
```
### 输出
```
3
```
## 样例 #3
### 输入
```
2
5 7
```
### 输出
```
4
```

### 算法分类
组合数学

### 综合分析与结论
这三道题解思路基本一致，均先对输入的数组元素进行质因数分解，利用唯一分解定理，将问题转化为对不同质因数在 $n$ 个位置上的分配问题，再通过隔板法得出每种质因数的放置方案数，最后累乘得到总的分解方案数。在实现上，都使用 `map` 来记录质因数出现的次数，通过预处理阶乘和阶乘逆元来高效计算组合数。不同点在于一些细节处理和代码风格，__LiChangChao__ 使用 Lucas 定理计算组合数，另外两位则直接通过预处理阶乘和逆元计算。

### 所选的题解
- **作者：__LiChangChao__ (5星)**
    - **关键亮点**：思路清晰，代码结构完整，利用 Lucas 定理计算组合数，在处理较大数据时效率可能更高。
    - **重点代码**：
```cpp
long long C(long long a,long long b) {
    if(a<b)return 0;
    if(a==b)return 1;
    if(b>a-b)b=a-b;
    long long A=1,B=1;
    for(long long i=0; i<b; ++i) {
        A=(A*(a-i))%mod;
        B=(B*(b-i))%mod;
    }
    return (A*KSM(B,mod-2,mod));
}
long long Lucas(long long n,long long m) {
    if(m==0)return 1;
    return C(n%mod,m%mod)*Lucas(n/mod,m/mod)%mod;
}
```
核心实现思想：`C` 函数计算组合数，`Lucas` 函数利用 Lucas 定理递归计算大组合数。
- **作者：Transparent (4星)**
    - **关键亮点**：对隔板法的原理解释详细，代码注释丰富，对分解质因数时可能遗漏质数的情况处理得当。
    - **重点代码**：
```cpp
inline long long C(int a,int b) {
    if(b==0)return 1;
    return fac[a]*invfac[b]%Mod*invfac[a-b]%Mod;
}
```
核心实现思想：通过预处理的阶乘 `fac` 和阶乘逆元 `invfac` 计算组合数。
- **作者：orz_z (4星)**
    - **关键亮点**：代码简洁明了，结构紧凑，同样对分解质因数和组合数计算处理较好。
    - **重点代码**：
```cpp
inline long long C(int a, int b) {
    if (b == 0)
        return 1;
    return fac[a] * invfac[b] % Mod * invfac[a - b] % Mod;
}
```
核心实现思想：与 Transparent 的 `C` 函数类似，利用预处理的阶乘和逆元计算组合数。

### 最优关键思路或技巧
利用唯一分解定理将原问题转化为质因数分配问题，通过隔板法和组合数计算每种质因数的分配方案数，最后累乘得到结果。在实现中，预处理阶乘和阶乘逆元来高效计算组合数，同时使用 `map` 来灵活记录质因数及其出现次数。

### 可拓展之处
同类型题通常围绕整数的分解、组合计数等方面。类似算法套路是遇到整数乘积相关的计数问题，可考虑质因数分解，再结合组合数学的方法（如隔板法、排列组合公式等）来解决。

### 洛谷相似题目推荐
- [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)
- [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)

### 个人心得摘录与总结
无明显个人心得。 

---
处理用时：51.49秒