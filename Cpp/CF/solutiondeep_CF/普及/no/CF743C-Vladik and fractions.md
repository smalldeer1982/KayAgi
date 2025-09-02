# 题目信息

# Vladik and fractions

## 题目描述

Vladik and Chloe decided to determine who of them is better at math. Vladik claimed that for any positive integer $ n $ he can represent fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/98fe6e67c0215dd9544c203cfb728334ac03fc69.png) as a sum of three distinct positive fractions in form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/140afc1972028e64ad54d4357592e925861bdf13.png).

Help Vladik with that, i.e for a given $ n $ find three distinct positive integers $ x $ , $ y $ and $ z $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/388f8aea1d0cb4eefcbda4cfdf528ffa9edb155f.png). Because Chloe can't check Vladik's answer if the numbers are large, he asks you to print numbers not exceeding $ 10^{9} $ .

If there is no such answer, print -1.

## 说明/提示

对于$100$%的数据满足$n \leq 10^4$  
要求答案中$x,y,z \leq 2* 10^{9}$

## 样例 #1

### 输入

```
3
```

### 输出

```
2 7 42
```

## 样例 #2

### 输入

```
7
```

### 输出

```
7 8 56
```

# AI分析结果



# 题目重写

## 题目描述

Vladik和Chloe决定比试谁的数学更好。Vladik声称对于任意正整数$n$，他都能将分数$\frac{2}{n}$表示为三个不同正分数$\frac{1}{x}+\frac{1}{y}+\frac{1}{z}$的形式。请帮助Vladik验证这一说法，即对于给定的$n$，找出三个不同的正整数$x,y,z$满足等式。若不存在这样的解，输出-1。要求输出的数不超过$10^9$。

## 输入输出样例

### 样例1
输入：3  
输出：2 7 42

### 样例2  
输入：7  
输出：7 8 56

---

**算法分类**：构造

# 题解分析

## 关键思路总结
1. **分数拆分策略**：将$\frac{2}{n}$拆分为$\frac{1}{n}+\frac{1}{n}$，再对其中一个$\frac{1}{n}$进行二次拆分
2. **裂项公式应用**：利用$\frac{1}{n} = \frac{1}{n+1} + \frac{1}{n(n+1)}$完成构造
3. **特例处理**：当$n=1$时，构造结果会出现重复值，此时无解

## 精选题解

### 题解1（封禁用户）⭐⭐⭐⭐⭐
**核心亮点**：  
- 直接运用分数拆分思想，思路清晰简洁
- 正确指出当$n=1$时无解的条件

```cpp
// 核心代码
if(n == 1) cout << -1;
else cout << n << " " << n+1 << " " << n*(n+1);
```

### 题解2（jins3599）⭐⭐⭐⭐  
**核心亮点**：  
- 完整呈现构造思路的推导过程
- 包含数学公式推导和边界条件证明

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    if(n == 1) puts("-1");
    else printf("%d %d %d", n, n+1, n*(n+1));
}
```

### 题解3（DarthVictor）⭐⭐⭐⭐  
**核心亮点**：  
- 严谨的数学证明过程
- 详细分析无解情况的产生条件

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    if(n==1) printf("-1\n");
    else printf("%d %d %d\n",n,n+1,n*n+n);
}
```

---

## 拓展建议
1. **类似题型**：分数拆分问题（如将$\frac{a}{b}$拆为多个单位分数之和）
2. **扩展技巧**：  
   - 灵活运用裂项公式$\frac{1}{k(k+1)} = \frac{1}{k}-\frac{1}{k+1}$  
   - 构造特殊解时优先考虑相邻整数乘积形式

## 推荐习题
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
2. [P1412 分数数列求和](https://www.luogu.com.cn/problem/P1412)  
3. [P2118 比例简化](https://www.luogu.com.cn/problem/P2118)

---

**解题心得**：  
"当构造题出现分数形式时，优先考虑将分子拆分为多个1的组合，再利用裂项公式进行分解"——题解中的这一思路体现了将复杂问题转化为已知形式的典型解题策略。在实现时要注意特判边界值（如n=1），这往往是构造题的关键陷阱。

---
处理用时：46.52秒