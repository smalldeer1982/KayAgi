# 题目信息

# Moderate Modular Mode

## 题目描述

YouKn0wWho has two even integers $ x $ and $ y $ . Help him to find an integer $ n $ such that $ 1 \le n \le 2 \cdot 10^{18} $ and $ n \bmod x = y \bmod n $ . Here, $ a \bmod b $ denotes the remainder of $ a $ after division by $ b $ . If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 说明/提示

In the first test case, $ 4 \bmod 4 = 8 \bmod 4 = 0 $ .

In the second test case, $ 10 \bmod 4 = 2 \bmod 10 = 2 $ .

In the third test case, $ 420 \bmod 420 = 420 \bmod 420 = 0 $ .

## 样例 #1

### 输入

```
4
4 8
4 2
420 420
69420 42068```

### 输出

```
4
10
420
9969128```

# AI分析结果

### 题目内容（中文重写）
# 适度的模运算模式

## 题目描述
YouKn0wWho 有两个偶数 $x$ 和 $y$。请帮助他找到一个整数 $n$，使得 $1 \le n \le 2 \cdot 10^{18}$ 且 $n \bmod x = y \bmod n$。这里，$a \bmod b$ 表示 $a$ 除以 $b$ 的余数。如果存在多个这样的整数，输出任意一个即可。可以证明，在给定的约束条件下，这样的整数总是存在的。

## 说明/提示
在第一个测试用例中，$4 \bmod 4 = 8 \bmod 4 = 0$。

在第二个测试用例中，$10 \bmod 4 = 2 \bmod 10 = 2$。

在第三个测试用例中，$420 \bmod 420 = 420 \bmod 420 = 0$。

## 样例 #1

### 输入
```
4
4 8
4 2
420 420
69420 42068
```

### 输出
```
4
10
420
9969128
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来构造满足条件的 $n$。主要分为 $x > y$、$x = y$、$x < y$ 三种情况（部分题解将 $x = y$ 合并到其他情况中）。
- **思路对比**：对于 $x > y$ 的情况，所有题解都认为 $n = x + y$ 是符合条件的；对于 $x = y$ 的情况，大多认为 $n = x$ 是解；对于 $x < y$ 的情况，不同题解的推导方式略有不同，但最终结果大多是 $n = y - \frac{y \bmod x}{2}$。
- **算法要点**：关键在于根据不同的 $x$ 和 $y$ 的大小关系，推导出满足 $n \bmod x = y \bmod n$ 的 $n$ 的表达式。
- **解决难点**：主要难点在于 $x < y$ 时 $n$ 的构造，需要通过设未知数、利用模运算的性质进行推导，并且要利用 $x$ 和 $y$ 是偶数这一条件保证结果的正确性。

### 所选题解
- **pldzy（4星）**
    - **关键亮点**：思路清晰，分类讨论详细，代码实现规范，对每种情况的分析都有相应的数学推导。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rint register int
int t, x, y;

int main () 
{
    scanf ("%d", &t);
    while (t--)
    {
        scanf ("%d %d", &x, &y);
        if (x > y) printf ("%d\n", x + y);
        if (x == y) printf ("%d\n", x); 
        if (x < y)
        {
            int s = x, tim = y / x;
            x = x * (tim + 1);
            if (x > y) x -= s;
            printf ("%d\n", (y - x) / 2 + x);
        }
    }
    return 0;
}
```
核心实现思想：先读取测试用例的数量 $t$，然后对于每个测试用例，根据 $x$ 和 $y$ 的大小关系进行分类讨论，输出对应的 $n$。

- **XL4453（4星）**
    - **关键亮点**：思路简洁明了，直接分两种情况讨论，代码简洁，对 $x \leq y$ 情况的推导有一定的数学依据。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
long long T,x,y;
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&x,&y);
        if(x>y)printf("%lld\n",x+y);
        else printf("%lld\n",(y-(y%x)/2));
    }
    return 0;
}
```
核心实现思想：读取测试用例数量 $T$，对于每个测试用例，若 $x > y$ 则输出 $x + y$，否则输出 $y - \frac{y \bmod x}{2}$。

- **E1_de5truct0r（4星）**
    - **关键亮点**：思路清晰，分类讨论全面，对每种情况的分析有数学推导，代码简洁易读。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int T; cin>>T;
    while(T--){
        int x,y; cin>>x>>y;
        if(x>y) cout<<x+y<<endl;
        else if(x==y) cout<<x<<endl;
        else cout<<y-(y%x)/2<<endl;
    }return 0;
}
```
核心实现思想：读取测试用例数量 $T$，对于每个测试用例，根据 $x$ 和 $y$ 的大小关系输出对应的 $n$。

### 最优关键思路或技巧
- **分类讨论**：通过对 $x$ 和 $y$ 的大小关系进行分类讨论，将复杂问题简化为几种简单情况。
- **数学推导**：在 $x < y$ 的情况下，通过设未知数、利用模运算的性质进行推导，得到 $n$ 的表达式。

### 可拓展之处
同类型题可能会改变条件，如 $x$ 和 $y$ 不一定是偶数，或者改变模运算的等式关系。类似算法套路可以应用于其他构造类问题，通过分析问题的特殊性质，进行分类讨论并构造出满足条件的解。

### 推荐洛谷题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录与总结
部分题解提到“考察了一元一次方程的求解，属于幼儿园题”，总结为在解决此类数学构造问题时，合理运用方程求解的方法可以帮助我们找到问题的解。 

---
处理用时：63.57秒