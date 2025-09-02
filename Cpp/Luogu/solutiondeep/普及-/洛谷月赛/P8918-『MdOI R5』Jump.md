# 题目信息

# 『MdOI R5』Jump

## 题目描述

数轴上有一个人，设他所在的位置为 $x$，初始时 $x=0$。第 $i$ 秒中他可以选择往左或往右跳 $2^{i-1}$ 单位长度，即将 $x$ 增大或减小 $2^{i-1}$。问他至少需要多少秒才能到达 $n$，即在某一秒结束的时刻使得 $x=n$。如果永远都不可能到达 $n$，那么输出 $-1$。

**本题每个测试点中有多组数据。**

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le 10^3$，$1\le n\le 10^9$。

$\operatorname{Subtask} 1(30\%)$：$n\le 100$。

$\operatorname{Subtask} 2(40\%)$：$n=2^k$，其中 $k$ 是一个非负整数。

$\operatorname{Subtask} 3(30\%)$：无特殊限制。

#### 样例说明 1

$n=1$ 时只需要在第一秒中往右跳即可。

$n=2$ 时可以证明永远都不可能到达 $n$。

## 样例 #1

### 输入

```
10
1
2
7
8
9
10
11
935
101
2023```

### 输出

```
1
-1
3
-1
4
-1
4
10
7
11```

# AI分析结果

### 综合分析与结论

本题的核心在于通过二进制分解和奇偶性分析，确定是否能够通过跳跃到达目标点 \( n \)。大多数题解都基于以下两个关键点：
1. **奇偶性分析**：由于只有第一秒的跳跃长度为奇数，后续跳跃长度均为偶数，因此只有当 \( n \) 为奇数时才可能有解。
2. **二进制分解**：通过 \( n \) 的二进制表示，确定最小的跳跃次数。具体来说，答案通常为 \( \lfloor \log_2 n \rfloor + 1 \)。

### 所选高星题解

#### 1. 作者：Kubic (5星)
- **关键亮点**：通过二进制分解和奇偶性分析，给出了简洁且严谨的证明，代码实现也非常高效。
- **代码核心思想**：使用 `32 - __builtin_clz(n)` 快速计算 \( \lfloor \log_2 n \rfloor + 1 \)。
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
void slv()
{
    scanf("%d",&n);
    if(n&1) printf("%d\n",32-__builtin_clz(n));
    else printf("-1\n");
}
int main()
{
    scanf("%d",&T);
    while(T--) slv();return 0;
}
```

#### 2. 作者：Infinite_Eternity (4星)
- **关键亮点**：通过数学证明和逻辑推理，给出了清晰的结论，代码简洁且易于理解。
- **代码核心思想**：使用 `log2` 函数计算 \( \lfloor \log_2 n \rfloor + 1 \)。
```cpp
#include <stdio.h>
#include <math.h>
int main()
{
    int T,a;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&a);
        if (a==1) printf("%d\n",1);
        else if (!(a&1)) printf("%d\n",-1);
        else printf("%d\n",(int)log2(a)+1);
    }
    return 0;
}
```

#### 3. 作者：McIron233 (4星)
- **关键亮点**：通过观察样例和二进制分解，给出了直观的解释和简洁的代码实现。
- **代码核心思想**：通过移位操作计算 \( \lfloor \log_2 n \rfloor + 1 \)。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int n,k=0;
        scanf("%d",&n);
        if(n%2==0){puts("-1");continue;}
        while(n) n=n>>1,k++;
        printf("%d\n",k);
    }
    return 0;
}
```

### 最优关键思路与技巧
- **二进制分解**：通过 \( n \) 的二进制表示，快速确定最小的跳跃次数。
- **奇偶性分析**：利用奇偶性快速判断是否有解。
- **高效计算**：使用内置函数或移位操作快速计算 \( \lfloor \log_2 n \rfloor + 1 \)。

### 可拓展之处
- **类似题目**：可以考察其他基于二进制分解或奇偶性分析的题目，如跳台阶问题、硬币问题等。
- **算法套路**：二进制分解和奇偶性分析是解决许多数学问题的常用技巧，尤其是在涉及跳跃、步数等问题时。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

### 个人心得摘录
- **Kubic**：通过二进制分解和奇偶性分析，快速得出结论，代码简洁高效。
- **Infinite_Eternity**：通过数学证明和逻辑推理，给出了清晰的结论，代码简洁且易于理解。
- **McIron233**：通过观察样例和二进制分解，给出了直观的解释和简洁的代码实现。

---
处理用时：35.52秒