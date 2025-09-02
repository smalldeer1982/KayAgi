# 题目信息

# Minimum LCM

## 题目描述

You are given an integer $ n $ .

Your task is to find two positive (greater than $ 0 $ ) integers $ a $ and $ b $ such that $ a+b=n $ and the least common multiple (LCM) of $ a $ and $ b $ is the minimum among all possible values of $ a $ and $ b $ . If there are multiple answers, you can print any of them.

## 说明/提示

In the second example, there are $ 8 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 8 $ , $ LCM(1, 8) = 8 $ ;
- $ a = 2 $ , $ b = 7 $ , $ LCM(2, 7) = 14 $ ;
- $ a = 3 $ , $ b = 6 $ , $ LCM(3, 6) = 6 $ ;
- $ a = 4 $ , $ b = 5 $ , $ LCM(4, 5) = 20 $ ;
- $ a = 5 $ , $ b = 4 $ , $ LCM(5, 4) = 20 $ ;
- $ a = 6 $ , $ b = 3 $ , $ LCM(6, 3) = 6 $ ;
- $ a = 7 $ , $ b = 2 $ , $ LCM(7, 2) = 14 $ ;
- $ a = 8 $ , $ b = 1 $ , $ LCM(8, 1) = 8 $ .

In the third example, there are $ 5 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 4 $ , $ LCM(1, 4) = 4 $ ;
- $ a = 2 $ , $ b = 3 $ , $ LCM(2, 3) = 6 $ ;
- $ a = 3 $ , $ b = 2 $ , $ LCM(3, 2) = 6 $ ;
- $ a = 4 $ , $ b = 1 $ , $ LCM(4, 1) = 4 $ .

## 样例 #1

### 输入

```
4
2
9
5
10```

### 输出

```
1 1
3 6
1 4
5 5```

# AI分析结果

### 题目内容
# 最小最小公倍数（Minimum LCM）
## 题目描述
给定一个整数 $n$ 。
你的任务是找到两个正整数（大于 $0$ ）$a$ 和 $b$ ，使得 $a + b = n$ ，并且 $a$ 和 $b$ 的最小公倍数（LCM）在所有可能的 $a$ 和 $b$ 的取值中最小。如果有多个答案，你可以输出其中任意一个。
## 说明/提示
在第二个例子中，$a$ 和 $b$ 有 $8$ 种可能的组合：
 - $a = 1$ ，$b = 8$ ，$LCM(1, 8) = 8$ ；
 - $a = 2$ ，$b = 7$ ，$LCM(2, 7) = 14$ ；
 - $a = 3$ ，$b = 6$ ，$LCM(3, 6) = 6$ ；
 - $a = 4$ ，$b = 5$ ，$LCM(4, 5) = 20$ ；
 - $a = 5$ ，$b = 4$ ，$LCM(5, 4) = 20$ ；
 - $a = 6$ ，$b = 3$ ，$LCM(6, 3) = 6$ ；
 - $a = 7$ ，$b = 2$ ，$LCM(7, 2) = 14$ ；
 - $a = 8$ ，$b = 1$ ，$LCM(8, 1) = 8$ 。

在第三个例子中，$a$ 和 $b$ 有 $5$ 种可能的组合：
 - $a = 1$ ，$b = 4$ ，$LCM(1, 4) = 4$ ；
 - $a = 2$ ，$b = 3$ ，$LCM(2, 3) = 6$ ；
 - $a = 3$ ，$b = 2$ ，$LCM(3, 2) = 6$ ；
 - $a = 4$ ，$b = 1$ ，$LCM(4, 1) = 4$ 。
## 样例 #1
### 输入
```
4
2
9
5
10
```
### 输出
```
1 1
3 6
1 4
5 5
```

### 算法分类
数学

### 题解综合分析与结论
所有题解都围绕通过分析数论性质来解决问题，主要思路是根据 $n$ 的奇偶性、是否为质数等不同情况，找出使 $a + b = n$ 时 $\text{lcm}(a, b)$ 最小的 $a$ 和 $b$。不同题解在分析过程和代码实现的简洁性、优化程度上存在差异。

### 所选的题解
- **作者：LegendaryGrandmaster（5星）**
  - **关键亮点**：思路简洁清晰，直接通过寻找 $n$ 的最大因数，用 $n$ 减去该因数得到答案，代码实现精炼。
  - **重点代码核心思想**：`cnt` 函数用于寻找 $n$ 的最大因数（除 $n$ 本身），在 `slove` 函数中调用该函数并输出结果。
  - **核心代码**：
```cpp
int cnt(int x)
{
    for(int i = 2; i <= x / i; i++)
        if(x % i == 0) return x / i;
    return 1;
}
void slove()
{
    int n;
    cin >> n;
    cout << cnt(n) << ' ' << n - cnt(n) << '\n';
}
```
- **作者：Sukii（5星）**
  - **关键亮点**：对 $n$ 的不同情况（偶数、质数、奇合数）进行了全面且详细的分类讨论，并给出了每种情况的详细证明过程，逻辑严谨。
  - **重点代码核心思想**：`f` 函数用于寻找 $n$ 的最小非1因子，在 `main` 函数中根据 $n$ 的不同情况输出相应的 $a$ 和 $b$。
  - **核心代码**：
```cpp
int f(int x)
{
    for(int i = 2; i <= sqrt(x); i++) if(x % i == 0) return i;
    return 0;
}
int main()
{
    cin >> a;
    for(int i = 1; i <= a; i++)
    {
        cin >> b;
        if(b % 2 == 0){cout << b / 2 << ' ' << b / 2 << endl; continue;}
        else if(f(b) == 0) cout << 1 << ' ' << b - 1 << endl;
        else cout << b / f(b) << ' ' << b - b / f(b) << endl;
    }
    return 0;
}
```
- **作者：Lyrella（4星）**
  - **关键亮点**：通过数学推导证明了使 $\text{lcm}(a, b)$ 最小的条件，进而得出直接寻找 $n$ 除1以外的最小因数来确定 $a$ 和 $b$ 的方法，思路清晰。
  - **重点代码核心思想**：在 `solve` 函数中，通过循环寻找 $n$ 的合适因数，并输出结果。
  - **核心代码**：
```cpp
void solve()
{
    int a = 1, n; cin >> n;
    for(int i = 2; i * i <= n; i++) if(n % i == 0){a = n / i; break;}
    cout << a << ' ' << n - a << '\n';
}
```

### 最优关键思路或技巧
通过对 $n$ 进行奇偶性、是否为质数等分类讨论，利用数论知识，如因数与倍数关系、最大公因数和最小公倍数的性质，找到使 $\text{lcm}(a, b)$ 最小的 $a$ 和 $b$ 组合。在实现上，通过寻找 $n$ 的特定因数（最大或最小非1因数）来快速确定答案，避免了暴力枚举所有可能的 $a$ 和 $b$ 组合，优化了时间复杂度。

### 可拓展思路
此类题目属于数论中关于因数、倍数以及最小公倍数的应用。类似的套路是对给定的数进行性质分析，如因数分解、判断质数等，利用数论的基本定理和性质来解决问题。同类型题通常围绕整数的各种数学性质展开，例如求满足特定条件的最大公因数、最小公倍数，或者根据数字组合的性质求最值等。

### 洛谷相似题目推荐
 - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
 - [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613) 

---
处理用时：48.07秒