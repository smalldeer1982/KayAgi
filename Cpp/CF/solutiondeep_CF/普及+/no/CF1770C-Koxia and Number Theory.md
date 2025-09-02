# 题目信息

# Koxia and Number Theory

## 题目描述

Joi has an array $ a $ of $ n $ positive integers. Koxia wants you to determine whether there exists a positive integer $ x > 0 $ such that $ \gcd(a_i+x,a_j+x)=1 $ for all $ 1 \leq i < j \leq n $ .

Here $ \gcd(y, z) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ y $ and $ z $ .

## 说明/提示

In the first test case, we can set $ x = 4 $ . This is valid because:

- When $ i=1 $ and $ j=2 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,7+4)=\gcd(9,11)=1 $ .
- When $ i=1 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,10+4)=\gcd(9,14)=1 $ .
- When $ i=2 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(7+4,10+4)=\gcd(11,14)=1 $ .

In the second test case, any choice of $ x $ makes $ \gcd(a_1 + x, a_2 + x) = \gcd(3+x,3+x)=3+x $ . Therefore, no such $ x $ exists.

## 样例 #1

### 输入

```
2
3
5 7 10
3
3 3 4```

### 输出

```
YES
NO```

# AI分析结果

### 题目翻译
# Koxia and Number Theory

## 题目描述

Joi 有一个包含 $n$ 个正整数的数组 $a$。Koxia 希望你判断是否存在一个正整数 $x > 0$，使得对于所有 $1 \leq i < j \leq n$，满足 $\gcd(a_i+x,a_j+x)=1$。

这里 $\gcd(y, z)$ 表示整数 $y$ 和 $z$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

## 说明/提示

在第一个测试用例中，我们可以设置 $x = 4$。这是有效的，因为：

- 当 $i=1$ 和 $j=2$ 时，$\gcd(a_i+x,a_j+x)=\gcd(5+4,7+4)=\gcd(9,11)=1$。
- 当 $i=1$ 和 $j=3$ 时，$\gcd(a_i+x,a_j+x)=\gcd(5+4,10+4)=\gcd(9,14)=1$。
- 当 $i=2$ 和 $j=3$ 时，$\gcd(a_i+x,a_j+x)=\gcd(7+4,10+4)=\gcd(11,14)=1$。

在第二个测试用例中，任何 $x$ 的选择都会使得 $\gcd(a_1 + x, a_2 + x) = \gcd(3+x,3+x)=3+x$。因此，不存在这样的 $x$。

## 样例 #1

### 输入

```
2
3
5 7 10
3
3 3 4```

### 输出

```
YES
NO```

### 算法分类
数学

### 题解分析与结论
本题的核心是通过数学分析判断是否存在一个正整数 $x$，使得数组中的每个元素加上 $x$ 后两两互质。题解中主要讨论了两种情况：
1. **存在重复元素**：如果数组中有两个相同的元素，那么无论 $x$ 取何值，这两个元素加上 $x$ 后一定不互质，因此无解。
2. **模数分析**：对于每个质数 $k$，如果数组中每个模 $k$ 的余数都至少出现两次，那么无论 $x$ 取何值，都会存在两个数加上 $x$ 后是 $k$ 的倍数，因此无解。

大多数题解都围绕这两种情况进行讨论，并通过枚举质数或模数来判断是否存在无解的情况。部分题解还提到了中国剩余定理，用于证明在某些情况下存在解。

### 精选题解
#### 题解1：abensyl (5星)
**关键亮点**：
- 清晰地分析了两种无解的情况，并给出了详细的证明。
- 代码实现简洁，通过预处理模数统计来快速判断无解情况。

**核心代码**：
```cpp
for(int i=2;i<=n;++i) {
    bool flag=1; //判断余数
    for(int j=0;j<i;++j) {
        if(a[i][j]<2) { 
            flag=0;
            break;
        }
    }
    if(flag) {
        cout<<"No\n";
        return;
    }
}
```
**实现思想**：通过枚举 $k$ 并统计每个余数的出现次数，判断是否存在所有余数都至少出现两次的情况。

#### 题解2：Alex_Wei (4星)
**关键亮点**：
- 通过奇偶性分析推广到一般结论，思路清晰。
- 提到中国剩余定理，进一步证明了在某些情况下存在解。

**核心代码**：
```cpp
rep(mod, 2, 50) {
    rep(i, 0, mod-1) cnt[i] = 0;
    rep(i, 1, n) ++cnt[a[i]%mod];
    ll now = 0;
    rep(i, 0, mod-1) now |= cnt[i] <= 1;
    ok &= now;
}
```
**实现思想**：枚举模数并统计余数，判断是否存在至少一个余数出现次数小于2的情况。

#### 题解3：氧少Kevin (4星)
**关键亮点**：
- 通过具体例子（如奇偶性、模3余数）逐步推导出一般结论，易于理解。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for(int k = 2; k <= n / 2; k++) {
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++) ++cnt[a[i] % k];
    int flag = 0;
    for(int i = 0; i < k; i++) 
        if(cnt[i] < 2) {
            flag = 1;
            break;
        }
    if(!flag) return false;
}
```
**实现思想**：通过枚举 $k$ 并统计余数，判断是否存在所有余数都至少出现两次的情况。

### 最优关键思路
1. **模数分析**：通过枚举质数或模数，统计每个余数的出现次数，判断是否存在所有余数都至少出现两次的情况。
2. **中国剩余定理**：在某些情况下，可以通过中国剩余定理证明存在解。

### 可拓展之处
- 类似的问题可以通过模数分析和中国剩余定理来解决，尤其是在涉及互质或最大公约数的问题中。
- 可以进一步探讨如何在更大范围内高效地枚举质数或模数。

### 推荐题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 最大公约数](https://www.luogu.com.cn/problem/P1069)
3. [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)

### 个人心得摘录
- **abensyl**：比赛中因未考虑到重复元素的情况而罚时，提醒我们在解题时要全面考虑所有可能的情况。
- **Alex_Wei**：通过奇偶性分析推广到一般结论，强调了从简单情况入手的重要性。
- **氧少Kevin**：通过具体例子逐步推导出一般结论，强调了通过实例理解问题的必要性。

---
处理用时：54.82秒