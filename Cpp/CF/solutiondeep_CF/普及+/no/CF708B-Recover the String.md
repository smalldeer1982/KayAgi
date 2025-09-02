# 题目信息

# Recover the String

## 题目描述

For each string $ s $ consisting of characters '0' and '1' one can define four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ and $ a_{11} $ , where $ a_{xy} $ is the number of subsequences of length $ 2 $ of the string $ s $ equal to the sequence $ {x,y} $ .

In these problem you are given four integers $ a_{00} $ , $ a_{01} $ , $ a_{10} $ , $ a_{11} $ and have to find any non-empty string $ s $ that matches them, or determine that there is no such string. One can prove that if at least one answer exists, there exists an answer of length no more than $ 1000000 $ .

## 样例 #1

### 输入

```
1 2 3 4
```

### 输出

```
Impossible
```

## 样例 #2

### 输入

```
1 2 2 1
```

### 输出

```
0110
```

# AI分析结果

### 题目内容
# 恢复字符串

## 题目描述
对于每个由字符'0'和'1'组成的字符串 $s$，可以定义四个整数 $a_{00}$，$a_{01}$，$a_{10}$ 和 $a_{11}$，其中 $a_{xy}$ 是字符串 $s$ 中长度为 $2$ 且等于序列 ${x,y}$ 的子序列的数量。

在本题中，给定四个整数 $a_{00}$，$a_{01}$，$a_{10}$，$a_{11}$，你需要找到任何一个与之匹配的非空字符串 $s$，或者确定不存在这样的字符串。可以证明，如果至少存在一个答案，那么存在一个长度不超过 $1000000$ 的答案。

## 样例 #1
### 输入
```
1 2 3 4
```
### 输出
```
Impossible
```

## 样例 #2
### 输入
```
1 2 2 1
```
### 输出
```
0110
```

### 算法分类
数学

### 题解综合分析与结论
两道题解思路相似，均先通过 $n_0\times (n_0 - 1)=2\times a_{00}$ 和 $n_1\times (n_1 - 1)=2\times a_{11}$ 计算出字符串中 $0$ 和 $1$ 的数量 $n_0$、$n_1$，并根据 $n_0\times n_1=a_{01}+a_{10}$ 判断是否有解。构造字符串时，都基于 $0$ 和 $1$ 的数量以及 $a_{01}$、$a_{10}$ 的关系进行。不同在于构造具体方式，CaiXY06 的题解通过直接判断每个位置放 $0$ 还是 $1$ 来构造，liuyifan 的题解则是通过模拟 $0$ 和 $1$ 的分布来构造。整体来看，两题解思路清晰，但 CaiXY06 的代码更简洁，优化程度更好。

### 所选的题解
 - **作者：CaiXY06（5星）**
   - **关键亮点**：代码简洁高效，利用数学公式直接判断无解情况，并通过巧妙的条件判断直接构造出符合条件的字符串。
   - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A,B,C,D;
int main(){
    scanf("%d%d%d%d",&A,&B,&C,&D);
    n=sqrt(A<<1)+1,m=sqrt(D<<1)+1;
    (n<m?n:m)-=(!B&&!C);
    if(n*(n-1)!=A+A||m*(m-1)!=D+D||n*m!=B+C)return puts("Impossible"),0;
    for(int i=n+m;i;i--)
        if(B>=m)putchar('0'),B-=m;
        else putchar('1'),m--;
    return 0;
}
```
核心实现思想：先根据公式计算出 $0$ 和 $1$ 的数量 $n$ 和 $m$，并处理特殊情况。然后通过循环，根据 $B$（即 $a_{01}$）与 $m$ 的关系，决定当前位置放 $0$ 还是 $1$，从而构造出字符串。

### 最优关键思路或技巧
利用数学公式计算 $0$ 和 $1$ 的数量，并通过巧妙的条件判断来构造字符串，避免了复杂的枚举和搜索过程，提高了效率。

### 可拓展之处
此类题目属于根据子序列统计信息还原原序列的问题，类似套路可用于解决其他字符序列还原问题，例如给定不同长度子序列的统计信息来还原原字符串。

### 洛谷相似题目推荐
 - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论相关知识，与本题类似，都需要运用数学公式和逻辑判断解决问题。
 - [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)：同样是数论问题，通过建立数学模型，利用扩展欧几里得算法求解，与本题利用数学公式解决问题思路类似。
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：涉及数论中的逆元求解，与本题一样，需要掌握一定的数学知识和技巧来解决问题。 

---
处理用时：36.89秒