# 题目信息

# [ABC059D] Alice&Brown

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc059/tasks/arc072_b

AliceとBrownはゲームをするのが好きです。今日は以下のゲームを思いつきました。

$ 2 $つの山があり、はじめに$ X,\ Y $個の石が置かれています。 AliceとBrownは毎ターン以下の操作を交互に行い、操作を行えなくなったプレイヤーは負けとなります。

- 片方の山から $ 2i $ 個の石を取り、そのうち $ i $ 個の石を捨て、残りの $ i $ 個の石をもう片方の山に置く。ここで、整数 $ i\ (1≦i) $ の値は山に十分な個数の石がある範囲で自由に選ぶことができる。

Aliceが先手で、二人とも最適にプレイすると仮定したとき、与えられた $ X,\ Y $ に対しどちらのプレイヤーが勝つか求めてください。

## 说明/提示

### 制約

- $ 0≦\ X,\ Y\ ≦\ 10^{18} $

### Sample Explanation 1

Aliceは $ 2 $ 個石のある山から $ 2 $ 個取るしかありません。その結果、山の石の数はそれぞれ $ 0,\ 2 $ 個となり、Brownは $ 2 $ 個の石を取り、山の石の数はそれぞれ $ 1,\ 0 $ 個となります。 Aliceはこれ以上操作を行うことができないので、Brownの勝ちです。

## 样例 #1

### 输入

```
2 1```

### 输出

```
Brown```

## 样例 #2

### 输入

```
5 0```

### 输出

```
Alice```

## 样例 #3

### 输入

```
0 0```

### 输出

```
Brown```

## 样例 #4

### 输入

```
4 8```

### 输出

```
Alice```

# AI分析结果

### 题目内容重写

【题目描述】

Alice和Brown喜欢玩游戏。今天他们想出了一个新游戏。

游戏开始时有两堆石子，分别有X和Y个。Alice和Brown轮流进行操作，无法进行操作的一方输掉游戏。

每次操作，玩家可以从一堆中取出2i个石子，其中i个石子被丢弃，剩下的i个石子被放入另一堆。i是一个正整数，且取出的石子数不能超过当前堆中的石子数。

Alice先手，假设双方都采取最优策略，给定X和Y，判断谁会获胜。

【输入格式】

输入两个整数X和Y，表示两堆石子的初始数量。

【输出格式】

输出获胜者的名字，Alice或Brown。

【样例输入1】

```
2 1
```

【样例输出1】

```
Brown
```

【样例输入2】

```
5 0
```

【样例输出2】

```
Alice
```

【样例输入3】

```
0 0
```

【样例输出3】

```
Brown
```

【样例输入4】

```
4 8
```

【样例输出4】

```
Alice
```

### 算法分类

数学（博弈论）

### 题解分析与结论

所有题解的核心思路都是通过观察和推理得出一个简单的结论：当两堆石子的数量差不超过1时，后手（Brown）必胜；否则，先手（Alice）必胜。这个结论通过简单的数学证明和博弈论的基本原理得到验证。

### 所选高星题解

#### 题解1：作者：liangbowen (赞：31)
- **星级**：5星
- **关键亮点**：通过详细的数学证明，清晰地解释了为什么当两堆石子的数量差不超过1时后手必胜，否则先手必胜。代码简洁明了。
- **代码实现**：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
int main()
{
    long long n, m;
    std::cin >> n >> m;
    if (abs(n - m) <= 1) std::puts("Brown");
    else std::puts("Alice");
    return 0;
}
```
- **核心思想**：直接判断两堆石子的数量差是否小于等于1，输出相应结果。

#### 题解2：作者：Texas_the_Omertosa (赞：16)
- **星级**：4星
- **关键亮点**：通过简单的逻辑推理得出结论，代码实现简洁，适合快速理解。
- **代码实现**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long a,b;
    cin>>a>>b;
    if(abs(a-b)<=1)
        cout<<"Brown\n";
    else
        cout<<"Alice\n";
    return 0;
}
```
- **核心思想**：同样通过判断两堆石子的数量差是否小于等于1，输出相应结果。

#### 题解3：作者：first_fan (赞：6)
- **星级**：4星
- **关键亮点**：通过暴力打表的方式验证了结论的正确性，提供了另一种验证思路。
- **代码实现**：
```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
    int num=0;
    int flg=1;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
        {
            flg=-1;
        }
        c=getchar();
    }
    while(isdigit(c))
    {
        num=(num<<1)+(num<<3)+(c^48);
        c=getchar();
    }
    return num*flg;
}

int main()
{
    return 0&(int)puts(abs(read()-read())<=1?"Brown":"Alice");
}
```
- **核心思想**：通过读取输入并判断两堆石子的数量差，输出相应结果。

### 最优关键思路

通过观察和简单的数学证明，得出当两堆石子的数量差不超过1时，后手必胜；否则，先手必胜。这一结论可以通过直接判断两堆石子的数量差来实现，代码实现简洁高效。

### 可拓展之处

这种类型的博弈论问题通常可以通过观察和简单的数学推理得出结论。类似的题目可以通过分析游戏规则和状态转移来找到必胜策略。

### 推荐题目

1. [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)
2. [P1288 取数游戏 II](https://www.luogu.com.cn/problem/P1288)
3. [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)

---
处理用时：32.98秒