# 题目信息

# [ABC172D] Sum of Divisors

## 题目描述

### 题意翻译
- $f(x)$ 表示正整数 $x$ 的因数个数
- 现在给你一个正整数 $ N $ ，让你求出 $  \sum_{K=1}^N\ K\times\ f(K) $  。
----------


-------------

## 说明/提示

-  $ 1\ \leq\ N\ \leq\ 10^7 $
- $f(1)=1 $ ,  $ f(2)=2 $ ,  $ f(3)=2 $ ,  $ f(4)=3 $ , 所以答案为  $ 1\times\ 1\ +\ 2\times\ 2\ +\ 3\times\ 2\ +\ 4\times\ 3\ =23 $ 。

 _Translated by qinmingze_

## 样例 #1

### 输入

```
4```

### 输出

```
23```

## 样例 #2

### 输入

```
100```

### 输出

```
26879```

## 样例 #3

### 输入

```
10000000```

### 输出

```
838627288460105```

# AI分析结果



# [ABC172D] Sum of Divisors

## 题目描述

### 题意翻译
- $f(x)$ 表示正整数 $x$ 的因数个数
- 现在给你一个正整数 $ N $ ，让你求出 $  \sum_{K=1}^N\ K\times\ f(K) $  。

## 说明/提示
- $ 1\ \leq\ N\ \leq\ 10^7 $
- 样例：当 $N=4$ 时，答案为 $1\times1 + 2\times2 + 3\times2 + 4\times3 = 23$

---

**算法分类**：数学

---

## 题解综合分析

### 关键思路对比
1. **枚举因数法**（双重循环）：通过枚举每个数的倍数累加因数个数，时间复杂度 $O(n \log n)$。虽然直观但效率较低。
2. **数学贡献法**（等差数列求和）：将每个数视为因子，计算其在所有倍数中的贡献总和，时间复杂度 $O(n)$，性能最优。

### 精选题解推荐
#### 1. Jessica2333 / incra 优化解法（⭐⭐⭐⭐⭐）
**核心思路**：  
每个数 $x$ 作为因子时，其贡献为 $x$ 的倍数构成的等差数列之和。利用公式 $\sum_{k=1}^{\lfloor n/x \rfloor} x \cdot k = x \cdot \frac{\lfloor n/x \rfloor (\lfloor n/x \rfloor +1)}{2}$ 直接计算每个因子的总贡献。

**代码实现**：
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
LL n;
int main() {
    cin >> n;
    LL ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (n / i + 1) * (n / i) / 2 * i;
    cout << ans << endl;
    return 0;
}
```

#### 2. BlackPanda / saixingzhe（⭐⭐⭐）
**思路亮点**：  
通过双重循环标记每个数的因数个数，代码简单易懂。但时间复杂度 $O(n \log n)$ 在处理 $10^7$ 数据时存在风险。

**代码片段**：
```cpp
long long a[10000010], ans, n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            a[j]++;
    for (int i = 1; i <= n; i++)
        ans += a[i] * i;
    cout << ans;
}
```

---

## 最优技巧总结
**数学转换思维**：将因数个数问题转化为每个数的倍数贡献，利用等差数列公式将时间复杂度优化至 $O(n)$。核心公式推导：  
$$ \sum_{K=1}^N K \cdot f(K) = \sum_{x=1}^N x \cdot \sum_{k=1}^{\lfloor N/x \rfloor} k $$

---

## 类似题目推荐
1. [P1403 [AHOI2005]约数研究](https://www.luogu.com.cn/problem/P1403)  
   **考察点**：因数个数的前缀和计算
2. [P2424 约数和](https://www.luogu.com.cn/problem/P2424)  
   **考察点**：区间因数和的数学推导
3. [P2260 [清华集训2012]模积和](https://www.luogu.com.cn/problem/P2260)  
   **考察点**：复杂数学公式的分块优化

---

## 个人心得摘录
> "不开 `long long` 见祖宗" —— 多位题解作者反复强调数据范围问题，在涉及大数运算时必须使用长整型。  
> "逆向思考因子的贡献而非直接计算因数个数" —— 数学优化方法的关键在于视角转换，通过贡献分析找到更高效的表达式。

---
处理用时：71.30秒