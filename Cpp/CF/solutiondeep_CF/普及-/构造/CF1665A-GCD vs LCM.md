# 题目信息

# GCD vs LCM

## 题目描述

本题有多测。  
给定一个正整数 $n$，求一组正整数 $a$, $b$, $c$, $d$，使得 $a+b+c+d=n$，并且 $\gcd(a,b) = \operatorname{lcm}(c,d)$。本题有 SPJ，求出任意一组即可。

## 说明/提示

$4\le n\le 10^9$  
$1\le t\le 10^4$

## 样例 #1

### 输入

```
5
4
7
8
9
10```

### 输出

```
1 1 1 1
2 2 2 1
2 2 2 2
2 4 2 1
3 5 1 1```

# AI分析结果

### 综合分析与结论
这些题解的核心目标都是找出满足 $a + b + c + d = n$ 且 $\gcd(a, b) = \operatorname{lcm}(c, d)$ 的一组正整数 $a, b, c, d$。大部分题解采用了构造法，让 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，进而得出 $a = n - 3, b = 1, c = 1, d = 1$ 这组解。

部分题解采用了分类讨论的方式，依据 $n$ 对不同数取模的结果构造不同的解，但这种方法相对复杂。还有题解尝试暴力枚举，不过由于数据范围大，该方法不可行。

### 所选题解
- **作者：Dream_weavers（5星）**
    - **关键亮点**：思路清晰，详细阐述了借鉴思路的来源，代码简洁且同时给出 Python 和 C++ 版本。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n; 
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("1 %d 1 1\n",n-3);
    }
    return 0;
}
```
核心思想：让 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，令 $c = 1, d = 1, a = 1$，则 $b = n - 3$。

- **作者：xzyg（4星）**
    - **关键亮点**：明确列出所需的数论性质，推导过程清晰，代码规范。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define ll long long

using namespace std;

int main(){
    ll t;
    cin >> t;
    for(ll i = 1; i <= t; i++){
        ll n;
        cin >> n;
        cout << 1 << " " << n-3 << " " << 1 << " " << 1 << endl;
    }
    return 0;
}
```
核心思想：依据 $\gcd(1, n) = 1$ 和 $\operatorname{lcm}(1, n) = n$ 的性质，令 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，得到 $a = 1, b = n - 3, c = 1, d = 1$。

- **作者：Shimotsuki（4星）**
    - **关键亮点**：思路简洁明了，直接阐述让等式两边都为 1 的思路，代码简洁。
    - **核心代码**：
```cpp
#include<cstdio>

using namespace std;

int main(){
    int t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int a=n-3;
        printf("%d 1 1 1\n",a);
    }
    return 0;
} 
```
核心思想：让 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，使 $a$ 与 $b$ 互质，$c$ 与 $d$ 都为 1，令 $b = 1$，则 $a = n - 3$。

### 最优关键思路与技巧
采用构造法，利用 $\gcd(1, x) = 1$ 和 $\operatorname{lcm}(1, 1) = 1$ 的性质，直接构造出 $a = n - 3, b = 1, c = 1, d = 1$ 这组解，时间复杂度为 $O(T)$，避免了复杂的分类讨论和暴力枚举。

### 拓展思路
同类型题目通常会要求构造满足特定数学关系的解，可从特殊值（如 1）入手，利用常见的数学性质（如最大公约数、最小公倍数的性质）进行构造。

### 洛谷相似题目推荐
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察最大公约数和最小公倍数的概念及应用。
2. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)：涉及数论知识和数学构造。
3. [P2152 SDOI2009 SuperGCD](https://www.luogu.com.cn/problem/P2152)：主要考察高精度最大公约数的求解。

### 个人心得摘录与总结
- **作者：int4**：做题时不能过度依赖样例，自己最初根据样例按 $n\bmod 4$ 分类讨论，最后发现无需分类，直接构造即可。这提醒我们在解题时要独立思考，避免被样例误导。 

---
处理用时：25.62秒