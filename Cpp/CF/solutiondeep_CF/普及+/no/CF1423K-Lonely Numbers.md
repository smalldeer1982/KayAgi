# 题目信息

# Lonely Numbers

## 题目描述

In number world, two different numbers are friends if they have a lot in common, but also each one has unique perks.

More precisely, two different numbers $ a $ and $ b $ are friends if $ gcd(a,b) $ , $ \frac{a}{gcd(a,b)} $ , $ \frac{b}{gcd(a,b)} $ can form sides of a triangle.

Three numbers $ a $ , $ b $ and $ c $ can form sides of a triangle if $ a + b > c $ , $ b + c > a $ and $ c + a > b $ .

In a group of numbers, a number is lonely if it doesn't have any friends in that group.

Given a group of numbers containing all numbers from $ 1, 2, 3, ..., n $ , how many numbers in that group are lonely?

## 说明/提示

For first test case, $ 1 $ is the only number and therefore lonely.

For second test case where $ n=5 $ , numbers $ 1 $ , $ 3 $ and $ 5 $ are lonely.

For third test case where $ n=10 $ , numbers $ 1 $ , $ 5 $ and $ 7 $ are lonely.

## 样例 #1

### 输入

```
3
1 5 10```

### 输出

```
1
3
3```

# AI分析结果

### 题目翻译
# 孤独的数字

## 题目描述
在数字的世界里，如果两个不同的数字有很多共同之处，同时每个数字又有独特的特性，那么它们就是朋友。

更准确地说，如果两个不同的数字 $a$ 和 $b$ 满足 $\gcd(a,b)$、$\frac{a}{\gcd(a,b)}$、$\frac{b}{\gcd(a,b)}$ 可以构成一个三角形的三条边，那么 $a$ 和 $b$ 就是朋友。

三个数字 $a$、$b$ 和 $c$ 能构成三角形的三条边，需满足 $a + b > c$、$b + c > a$ 以及 $c + a > b$。

在一组数字中，如果一个数字在该组中没有任何朋友，那么这个数字就是孤独的。

给定一组包含从 $1$ 到 $n$ 的所有数字的集合，该集合中有多少个孤独的数字？

## 说明/提示
对于第一个测试用例，$1$ 是唯一的数字，因此它是孤独的。
对于第二个测试用例，当 $n = 5$ 时，数字 $1$、$3$ 和 $5$ 是孤独的。
对于第三个测试用例，当 $n = 10$ 时，数字 $1$、$5$ 和 $7$ 是孤独的。

## 样例 #1
### 输入
```
3
1 5 10
```
### 输出
```
1
3
3
```

### 算法分类
数学、质数、前缀和

### 综合分析与结论
这些题解的核心思路都是先分析孤独数字的性质，通过分类讨论（如质数、合数等情况）确定孤独数字的特征，即孤独数字为 $1$ 以及大于 $\sqrt{n}$ 小于 $n$ 的质数。然后利用线性筛预处理质数，再用前缀和统计质数个数，最终通过前缀和作差得到答案。

各题解的不同点在于分类讨论的具体方式和表述略有差异，但本质相同。难点在于对孤独数字性质的分析和证明，尤其是质数和合数不同情况的讨论。

### 所选题解
- **One_JuRuo（4星）**
    - **关键亮点**：思路清晰，分类讨论详细，代码简洁，对孤独数字性质的推导过程完整。
- **是个汉子（4星）**
    - **关键亮点**：同样思路清晰，对合数情况的构造证明较为详细，代码规范。
- **under_the_time（4星）**
    - **关键亮点**：思路简洁明了，对质数和合数的讨论直接，代码实现清晰。

### 重点代码
以 One_JuRuo 的代码为例，核心实现思想是先通过线性筛预处理出 $1$ 到 $1000000$ 的质数，再用前缀和统计 $1$ 到 $i$ 的质数个数，最后根据输入的 $n$ 计算答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int shu[1000005],pri[1000005],cnt;
int T,n;
inline void init()//线性筛预处理
{
    for(int i=2;i<=1000000;++i)
    {
        if(!shu[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt&&pri[j]*i<=1000000;++j)
        {
            shu[pri[j]*i]=1;
            if(i%pri[j]==0) break;
        }
    }
    for(int i=2;i<=1000000;++i) shu[i]^=1,shu[i]+=shu[i-1];//前缀和统计1~i的质数个数
}
int main()
{
    init();
    scanf("%d",&T);
    while(T--) scanf("%d",&n),printf("%d\n",shu[n]-shu[(int)sqrt(n)]+1);//注意：无论如何1都会孤独数字，所以记得+1
}
```

### 最优关键思路或技巧
- **分类讨论**：将数字分为质数、合数等不同情况进行讨论，逐步确定孤独数字的特征。
- **线性筛预处理质数**：高效地找出一定范围内的所有质数。
- **前缀和统计**：利用前缀和快速计算某个区间内的质数个数。

### 可拓展之处
同类型题目可能会改变数字之间的关系定义，或者改变集合的范围等，但解题思路仍可从分类讨论和数学性质分析入手。类似算法套路可用于解决与数字性质、质数相关的计数问题。

### 推荐洛谷题目
- [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
- [P1865 A % B Problem](https://www.luogu.com.cn/problem/P1865)
- [P5736 【深基7.例2】质数筛](https://www.luogu.com.cn/problem/P5736)

### 个人心得
无相关个人心得。

---
处理用时：35.23秒