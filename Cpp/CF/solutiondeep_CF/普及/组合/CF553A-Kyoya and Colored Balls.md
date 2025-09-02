# 题目信息

# Kyoya and Colored Balls

## 题目描述

Kyoya Ootori has a bag with $ n $ colored balls that are colored with $ k $ different colors. The colors are labeled from $ 1 $ to $ k $ . Balls of the same color are indistinguishable. He draws balls from the bag one by one until the bag is empty. He noticed that he drew the last ball of color $ i $ before drawing the last ball of color $ i+1 $ for all $ i $ from $ 1 $ to $ k-1 $ . Now he wonders how many different ways this can happen.

## 说明/提示

In the first sample, we have 2 balls of color 1, 2 balls of color 2, and 1 ball of color 3. The three ways for Kyoya are:

`<br></br>1 2 1 2 3<br></br>1 1 2 2 3<br></br>2 1 1 2 3<br></br>`

## 样例 #1

### 输入

```
3
2
2
1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1
2
3
4
```

### 输出

```
1680
```

# AI分析结果

### 题目翻译
### 题目描述
京也·大鸟有一个装有 $n$ 个彩色球的袋子，这些球有 $k$ 种不同的颜色。颜色从 $1$ 到 $k$ 编号。相同颜色的球是不可区分的。他一个一个地从袋子里取出球，直到袋子空了为止。他注意到，对于从 $1$ 到 $k - 1$ 的所有 $i$，他在取出颜色 $i + 1$ 的最后一个球之前取出了颜色 $i$ 的最后一个球。现在他想知道有多少种不同的取球方式。

### 说明/提示
在第一个样例中，我们有 $2$ 个颜色为 $1$ 的球，$2$ 个颜色为 $2$ 的球，以及 $1$ 个颜色为 $3$ 的球。京也的三种取球方式如下：
```
1 2 1 2 3
1 1 2 2 3
2 1 1 2 3
```

### 样例 #1
#### 输入
```
3
2
2
1
```
#### 输出
```
3
```

### 样例 #2
#### 输入
```
4
1
2
3
4
```
#### 输出
```
1680
```

### 综合分析与结论
- **思路对比**：大部分题解都采用了分步插入球的思路，即依次插入每种颜色的球，同时保证颜色编号小的球的最后一个在颜色编号大的球的最后一个之前取出。不同题解在具体的组合数计算和公式推导上略有差异，但核心思想一致。
- **算法要点**：主要运用了插板法和组合数计算。通过将问题转化为在已有球序列中插入新颜色球的问题，利用插板法计算插入方案数，再根据乘法原理得到最终结果。组合数的计算方法有利用帕斯卡恒等式（杨辉三角）和求阶乘逆元两种。
- **解决难点**：关键在于理解题目中的限制条件，即颜色 $i$ 的最后一个球必须在颜色 $i + 1$ 的最后一个球之前取出，并将其转化为组合数学问题。同时，需要正确计算组合数，处理好取模运算以避免溢出。

### 所选题解
- **oh_yes（5星）**
    - **关键亮点**：思路清晰，详细介绍了插板法的原理，并结合具体例子解释了如何将问题转化为插板法求解。代码实现中给出了两种不同的循环方向的解法，便于理解。
    - **核心代码**：
```cpp
inline void another_solve(){
    ll ans = 1;
    ll sum = 0;
    for(register int i = 1; i <= n; i ++){
        sum += c[i];
        ans *= C[sum - 1][c[i] - 1];
    }
    printf("%lld\n", ans);
}
```
核心思想：依次处理每种颜色的球，计算将当前颜色的球插入已有序列的方案数，利用组合数 $C_{sum - 1}^{c[i] - 1}$ 表示，其中 $sum$ 为已处理球的总数，$c[i]$ 为当前颜色球的数量，最后将每种颜色的方案数相乘得到最终结果。
- **wxzzzz（4星）**
    - **关键亮点**：思路简洁明了，直接给出了计算答案的公式。代码中实现了快速幂和组合数的计算，处理了取模运算。
    - **核心代码**：
```cpp
long long qpow(int x, int k) {
    long long ret = 1, base = x;
    while (k) {
        if (k & 1)
            ret = mod(ret * base);
        base = mod(base * base);
        k >>= 1;
    }
    return ret;
}
long long C(int x, int y) {
    if (y > x)
        return 0;
    long long t1, t2;
    t1 = qpow(mul[y], 1000000005);
    t2 = qpow(mul[x - y], 1000000005);
    return mod(mod(mul[x] * t1) * t2);
}
int main() {
    mul[0] = 1;
    for (int i = 1; i <= 2000; i++)
        mul[i] = mod(mul[i - 1] * i);
    cin >> k;
    for (int i = 1, t; i <= k; i++) {
        cin >> t;
        ans = mod(ans * C(sum + t - 1, t - 1));
        sum += t;
    }
    cout << ans;
    return 0;
}
```
核心思想：通过快速幂计算阶乘的逆元，进而计算组合数。依次读取每种颜色球的数量，根据公式 $\prod_{i=1}^n\dbinom{\Big(\displaystyle\sum_{j=1}^{i-1}c_j\Big)+c_i-1}{c_i-1}$ 计算答案，每次更新方案数并取模。
- **wangyibo201026（4星）**
    - **关键亮点**：思路清晰，推导了计算方案数的公式。代码中实现了快速幂和组合数的计算，使用前缀和数组简化计算。
    - **核心代码**：
```cpp
int fast_pow ( int a, int b ) {
    int res = 1;
    while ( b ) {
        if ( b & 1ll ) {
            res = res * a;
            res %= p;
        }
        b >>= 1ll;
        a = a * a;
        a %= p;
    }
    return res;
}
int C ( int n, int m ) {
    if ( n < m ) {
        return 0;
    }
    return fac[n] * fast_pow ( fac[m], p - 2 ) % p * fast_pow ( fac[n - m], p - 2 ) % p;
}
signed main () {
    init ();
    cin >> n;
    for ( int i = 1; i <= n; i ++ ) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }
    for ( int i = 1; i <= n; i ++ ) {
        ans *= C ( sum[i] - 1, sum[i - 1] );
        ans %= p;
    }
    cout << ans;
    return 0;
}
```
核心思想：利用快速幂计算阶乘的逆元来计算组合数。通过前缀和数组 $sum$ 记录前 $i$ 种颜色球的总数，根据公式 $\prod_{i = 1}^{k} C_{r_i - 1}^{r_{i - 1}}$ 计算答案，每次更新方案数并取模。

### 最优关键思路或技巧
- **思维方式**：将问题转化为分步插入球的问题，利用插板法和组合数计算方案数，通过乘法原理得到最终结果。
- **代码实现技巧**：使用快速幂计算阶乘的逆元，避免除法运算，同时处理好取模运算以避免溢出。使用前缀和数组简化计算。

### 拓展思路
同类型题或类似算法套路：
- 其他排列组合问题，如不同物品的分组问题、有条件的排列问题等，可尝试使用插板法和组合数计算。
- 涉及取模运算的问题，需要注意取模的时机和方法，避免溢出。

### 推荐题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：考察卡特兰数，与排列组合相关。
- [P1850 换教室](https://www.luogu.com.cn/problem/P1850)：涉及概率和组合数学的动态规划问题。
- [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：直接考察组合数的计算和应用。

### 个人心得
题解中未包含个人心得（如调试经历、踩坑教训、顿悟感想等）。

---
处理用时：41.83秒