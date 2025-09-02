# 题目信息

# Divisible Numbers (easy version)

## 题目描述

This is an easy version of the problem. The only difference between an easy and a hard version is the constraints on $ a $ , $ b $ , $ c $ and $ d $ .

You are given $ 4 $ positive integers $ a $ , $ b $ , $ c $ , $ d $ with $ a < c $ and $ b < d $ . Find any pair of numbers $ x $ and $ y $ that satisfies the following conditions:

- $ a < x \leq c $ , $ b < y \leq d $ ,
- $ x \cdot y $ is divisible by $ a \cdot b $ .

Note that required $ x $ and $ y $ may not exist.

## 样例 #1

### 输入

```
5
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1```

# AI分析结果

### 题目内容重写

#### 可被整除的数（简单版）

**题目描述**

这是该问题的简单版本。简单版与困难版的唯一区别在于对 $a$、$b$、$c$ 和 $d$ 的约束条件。

给定 $4$ 个正整数 $a$、$b$、$c$、$d$，其中 $a < c$ 且 $b < d$。找到满足以下条件的任意一对数 $x$ 和 $y$：

- $a < x \leq c$，$b < y \leq d$，
- $x \cdot y$ 能被 $a \cdot b$ 整除。

注意，可能不存在满足条件的 $x$ 和 $y$。

**样例 #1**

### 输入

```
5
1 1 2 2
3 4 5 7
8 9 15 18
12 21 14 24
36 60 48 66
```

### 输出

```
2 2
4 6
12 12
-1 -1
-1 -1
```

### 算法分类
数学

### 题解分析与结论

本题的核心在于找到满足条件的 $x$ 和 $y$，使得 $x \cdot y$ 能被 $a \cdot b$ 整除。题解主要集中在如何通过数学推导和优化来减少枚举的次数，从而提高算法的效率。

### 评分较高的题解

#### 题解1：Allanljx (E1)

**星级：4**

**关键亮点：**
- 通过枚举 $x$，并利用 $\gcd$ 计算 $y$ 的最小倍数，从而减少计算量。
- 代码简洁，思路清晰，适合初学者理解。

**核心代码：**
```cpp
for(int i=a+1;i<=c;i++) {
    int y=x/__gcd(x,i);
    y=d/y*y;
    if(y>b) {
        cout<<i<<' '<<y<<endl;
        f=1;
        break;
    }
}
```

#### 题解2：srds_cbddl (二分)

**星级：4**

**关键亮点：**
- 使用二分查找优化 $y$ 的搜索过程，进一步减少时间复杂度。
- 通过数学推导，明确了 $y$ 的取值条件，使得二分查找成为可能。

**核心代码：**
```cpp
for (int i = a + 1; i <= c; i ++) {
    int w = a * b / __gcd(a * b, i);
    int l = 1, r = 1e5, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (b < mid * w && d >= mid * w) {
            flag = true;
            break;
        }
        else if (mid * w <= b) l = mid + 1;
        else r = mid - 1;
    }
    if (flag) {
        cout << i << ' ' << mid * w << '\n';
        break;
    }
}
```

#### 题解3：GenesisCrystal (暴力优化)

**星级：4**

**关键亮点：**
- 通过计算 $\text{lcm}(a \times b, i)$ 来优化 $y$ 的取值，减少了不必要的枚举。
- 代码短小精悍，适合快速实现。

**核心代码：**
```cpp
for (ll i = a + 1; i <= c; i++) {
    ll o = lcm(a * b, i) / i;
    if (d / o > b / o) {
        ans = {i, (b + o) / o * o};
    }
}
```

### 最优关键思路或技巧
- **数学推导**：通过 $\gcd$ 和 $\text{lcm}$ 的数学性质，减少枚举的次数。
- **二分查找**：在确定 $y$ 的取值范围内，使用二分查找进一步优化搜索过程。

### 可拓展之处
- 类似的问题可以通过数学推导和优化来减少枚举次数，例如在数论中的因数分解、最大公约数等问题中。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1445 [Violet]樱花](https://www.luogu.com.cn/problem/P1445)

### 个人心得总结
- **调试经历**：在实现过程中，注意数据类型的范围，避免溢出问题。
- **踩坑教训**：暴力枚举在数据规模较大时容易超时，必须通过数学推导进行优化。
- **顿悟感想**：数学推导在算法优化中起着至关重要的作用，掌握基本的数论知识可以大大提高解题效率。

---
处理用时：32.95秒