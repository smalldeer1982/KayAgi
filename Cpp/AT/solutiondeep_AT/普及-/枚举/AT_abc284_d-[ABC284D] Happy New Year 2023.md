# 题目信息

# [ABC284D] Happy New Year 2023

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc284/tasks/abc284_d

正整数 $ N $ が与えられます。$ N $ は、$ 2 $ つの相異なる素数 $ p,q $ を用いて $ N=p^2q $ と表せることがわかっています。

$ p,q $ を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\leq\ T\leq\ 10 $
- $ 1\leq\ N\ \leq\ 9\times\ 10^{18} $
- $ N $ は、$ 2 $ つの相異なる素数 $ p,q $ を用いて $ N=p^2q $ と表せる
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて、$ N=2023=17^2\times\ 7 $ です。よって、$ p=17,q=7 $ です。

## 样例 #1

### 输入

```
3

2023

63

1059872604593911```

### 输出

```
17 7

3 7

104149 97711```

# AI分析结果

### 题目翻译
给定正整数 $N$，已知 $N$ 可以用两个不同的质数 $p$、$q$ 表示为 $N = p^2q$ 的形式。

请找出 $p$ 和 $q$。

会给出 $T$ 个测试用例，请分别求出每个测试用例的答案。

### 综合分析与结论
这些题解的核心思路都是利用 $N = p^2q$ 以及 $p$、$q$ 为质数的条件来求解 $p$ 和 $q$。由于 $N\leqslant 9\times 10^{18}$，可以推出 $\min(p,q)\leqslant 3\times 10^6$，所以大部分题解都是通过枚举较小的质数来确定 $p$ 和 $q$。

不同题解的差异主要在于枚举的方式和质数的筛选方法：
- 部分题解直接从 $2$ 开始枚举，找到能整除 $N$ 的数后判断是 $p$ 还是 $q$。
- 部分题解先筛出一定范围内的质数，再枚举这些质数来判断。
- 还有题解使用 Pollard - rho 算法分解质因数。

### 所选题解
- **作者：Pengzt（5星）**
    - **关键亮点**：思路清晰，直接指出 $\min(p,q)\leqslant 3\times 10^6$，并给出两种解法，一种直接枚举，另一种先筛质数再枚举，时间复杂度分析合理。
- **作者：CarroT1212（4星）**
    - **关键亮点**：代码简洁，直接从 $2$ 开始枚举，找到能整除 $N$ 的数后判断是 $p$ 还是 $q$，利用了题目保证有唯一解的条件。
    - **个人心得**：赛时有一发挂在没开 `long long` 上，提醒读者注意数据范围。
- **作者：Esperance（4星）**
    - **关键亮点**：思路简单直接，通过小暴力枚举，同时指出了 `sqrt()` 函数返回值为 `double` 可能导致的精度损失问题。
    - **个人心得**：因为 `sqrt()` 函数的精度问题调了半天，提醒读者注意避免此类错误。

### 重点代码
#### 作者：CarroT1212
```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
void solve() {
    ll n;
    scanf("%lld",&n);
    for (ll i=2;;i++) if (n%i==0) {
        ll j=sqrt(n/i); // q=i 时的 p
        if (j*j==n/i) printf("%lld %lld\n",j,i); // p 是整数，成立
        else printf("%lld %lld\n",i,n/i/i);
        return;
    }
}
int main() {
    int t; scanf("%d",&t); for (;t--;) solve();
    return 0;
}
```
**核心实现思想**：从 $2$ 开始枚举，找到第一个能整除 $N$ 的数 $i$，然后判断 $i$ 是 $p$ 还是 $q$。如果 $n/i$ 是完全平方数，则 $i$ 是 $q$；否则 $i$ 是 $p$。

#### 作者：Esperance
```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n, t;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 2; i*i*i <= n; i++)
            if (n % i == 0)
            {
                long long ljp = n / i, wyx = sqrt(ljp);
                if (ljp % i == 0) cout << i << ' ' << ljp/i << endl;
                else cout << wyx << ' ' << i << endl;
                break;
            }
    }
    return 0;
} 
```
**核心实现思想**：枚举 $i$，当 $i$ 能整除 $n$ 时，判断 $i$ 是 $p$ 还是 $q$。如果 $n/i$ 能被 $i$ 整除，则 $i$ 是 $p$；否则 $i$ 是 $q$。同时注意将 `sqrt()` 函数的结果存储在变量中，避免精度损失。

### 最优关键思路或技巧
- 利用 $N = p^2q$ 的条件，推出 $\min(p,q)\leqslant 3\times 10^6$，从而减少枚举范围。
- 直接枚举能整除 $N$ 的数，然后判断是 $p$ 还是 $q$，利用题目保证有唯一解的条件简化判断过程。
- 注意数据范围，使用 `long long` 或 `__int128` 避免溢出，同时注意 `sqrt()` 函数的精度问题。

### 拓展思路
同类型题可以是分解质因数的变种，如给定 $N = p^3q^2$ 等更复杂的形式，或者要求分解成多个质数的乘积。解题思路仍然是先分析质数的范围，然后通过枚举或筛质数的方法来求解。

### 推荐题目
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
- [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)
- [P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：32.29秒