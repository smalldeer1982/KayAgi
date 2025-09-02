# 题目信息

# k-LCM (easy version)

## 题目描述

It is the easy version of the problem. The only difference is that in this version $ k = 3 $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 样例 #1

### 输入

```
3
3 3
8 3
14 3```

### 输出

```
1 1 1
4 2 2
2 6 6```

# AI分析结果

### 题目内容
# k-LCM（简单版本）

## 题目描述
这是该问题的简单版本。唯一的区别是在这个版本中$k = 3$。

给定一个正整数$n$。找到$k$个正整数$a_1, a_2, \ldots, a_k$，使得：
- $a_1 + a_2 + \ldots + a_k = n$
- $LCM(a_1, a_2, \ldots, a_k) \leq \frac{n}{2}$

这里$LCM$是数字$a_1, a_2, \ldots, a_k$的[最小公倍数](https://en.wikipedia.org/wiki/Least_common_multiple)。

我们可以证明，在给定的约束条件下，答案总是存在的。

## 样例 #1
### 输入
```
3
3 3
8 3
14 3
```
### 输出
```
1 1 1
4 2 2
2 6 6
```
### 算法分类
构造
### 综合分析与结论
所有题解思路基本一致，都是通过分析样例，根据$n$的奇偶性及能否被$4$整除进行分类讨论来构造满足条件的三个数。
1. **思路**：
    - 当$n$为奇数时，输出$1,\lfloor\frac{n}{2}\rfloor,\lfloor\frac{n}{2}\rfloor$，此时$LCM = \lfloor\frac{n}{2}\rfloor \leq \frac{n}{2}$。
    - 当$n$为偶数但不能被$4$整除时，输出$2,\frac{n}{2} - 1,\frac{n}{2} - 1$，此时$LCM = \frac{n}{2}$。
    - 当$n$能被$4$整除时，输出$\frac{n}{2},\frac{n}{4},\frac{n}{4}$，此时$LCM = \frac{n}{2}$。
2. **算法要点**：根据$n$对$2$和$4$取模的结果，分别构造出不同的三个数组合，使其和为$n$且最小公倍数满足条件。
3. **解决难点**：关键在于如何通过对$n$的不同特性分析，找到满足和与最小公倍数双重条件的数的组合方式，大部分题解通过观察样例找到了规律。

题解整体质量相近，都清晰地阐述了思路并给出代码实现，但部分题解在思路阐述的详细程度和代码规范性上略有差异。

### 所选的题解
- **作者：EuphoricStar（5星）**
    - **关键亮点**：思路清晰简洁，直接点明通过观察样例找规律，快速得出三种$n$的不同情况对应的构造方式，代码简洁明了，使用`scanf`进行输入，符合习惯。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        if (n & 1) {
            printf("1 %d %d\n", n / 2, n / 2);
        } else if ((n / 2) & 1) {
            printf("2 %d %d\n", n / 2 - 1, n / 2 - 1);
        } else {
            printf("%d %d %d\n", n / 2, n / 4, n / 4);
        }
    }
    return 0;
}
```
核心实现思想：通过`scanf`读入数据，利用位运算判断$n$的奇偶性及$\frac{n}{2}$的奇偶性，根据不同情况按规律输出对应的三个数。
- **作者：StayAlone（4星）**
    - **关键亮点**：不仅给出思路和代码，还提到证明的重要性，并指出题目保证有解意味着$n \geq 3$，对题目理解更深入。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &k);
        if (n % 2) printf("1 %d %d\n", n / 2, n / 2); // n 为奇数
        else if (n % 4) printf("2 %d %d\n", n / 2 - 1, n / 2 - 1); // n 为偶数但 n % 4!= 0
        else printf("%d %d %d\n", n / 2, n / 4, n / 4); // n % 4 == 0
    }
    return 0;
} 
```
核心实现思想：与EuphoricStar类似，通过`scanf`读入，利用取模运算判断$n$的情况，按不同情况输出结果。
- **作者：coldy_rainy（4星）**
    - **关键亮点**：对每种分类情况给出了较为详细的证明过程，帮助理解构造的合理性，思路阐述完整。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t/*数据组数*/,n,k;
int main()
{
   cin>>t;
   while(t--)
   {
    cin>>n>>k;
    if(n%2)cout<<1<<' '<<n/2<<' '<<n/2<<'\n';//情况1：不能被2整除
    else if(n%4)cout<<2<<' '<<n/2-1<<' '<<n/2-1<<'\n';//情况2：能被2整除但不能被4整除
    else cout<<n/2<<' '<<n/4<<' '<<n/4<<'\n';//情况3：能被4整除
   }
   return 0;
}
```
核心实现思想：使用`cin`读入数据，通过取模运算判断$n$的特性，根据不同情况输出符合要求的三个数。

### 最优关键思路或技巧
通过对$n$进行奇偶性以及能否被$4$整除的分类讨论，巧妙地构造出满足和为$n$且最小公倍数小于等于$\frac{n}{2}$的三个数，这种根据数字特性进行分类构造的思维方式是解决本题的关键。

### 可拓展之处
同类型题可考虑增加$k$的值或改变对$a_i$的限制条件等。类似算法套路是遇到构造类问题，先观察样例，从简单情况入手，分析数字特性与题目条件之间的关系，进而找到通用的构造方法。

### 洛谷相似题目推荐
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：同样需要根据数字特性进行分析和构造，通过枚举和数学推导来解决问题。
2. [P2619 神奇的幻方](https://www.luogu.com.cn/problem/P2619)：按照特定规则构造幻方，考察对规律的发现和实现能力，与本题构造思路类似。
3. [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)：根据给定的价格和数量关系构造计算方式，虽然较为基础，但构造思维相通。 

---
处理用时：54.88秒