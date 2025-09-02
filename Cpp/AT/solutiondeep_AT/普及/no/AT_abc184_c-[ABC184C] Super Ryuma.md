# 题目信息

# [ABC184C] Super Ryuma

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc184/tasks/abc184_c

無限に広がる $ 2 $ 次元グリッドがあり、マス $ (r_1,\ c_1) $ に駒「超竜馬」が置かれています。  
 この駒は、 $ 1 $ 手で次のような動きができます。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc184_c/5bfa39c442ba1e792051275842c037db26123fff.png)

より正確には、超竜馬がマス $ (a,\ b) $ にあるとき、以下のいずれかの条件を満たすマス $ (c,\ d) $ に動かすことができます。

- $ a\ +\ b\ =\ c\ +\ d $
- $ a\ -\ b\ =\ c\ -\ d $
- $ |a\ -\ c|\ +\ |b\ -\ d|\ \le\ 3 $

超竜馬を $ (r_1,\ c_1) $ から $ (r_2,\ c_2) $ に動かすのに必要な最小手数を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ r_1,\ c_1,\ r_2,\ c_2\ \le\ 10^9 $

### Sample Explanation 1

例えば、 $ (1,\ 1)\ \rightarrow\ (5,\ 5)\ \rightarrow\ (5,\ 6) $ と動かすと $ 2 $ 手になります。

### Sample Explanation 2

例えば、 $ (1,\ 1)\ \rightarrow\ (100001,\ 100001)\ \rightarrow\ (1,\ 200001) $ と動かすと $ 2 $ 手になります。

### Sample Explanation 3

例えば、 $ (2,\ 3)\ \rightarrow\ (3,\ 3)\ \rightarrow\ (-247,\ 253)\ \rightarrow\ (998244353,\ 998244853) $ と動かすと $ 3 $ 手になります。

## 样例 #1

### 输入

```
1 1

5 6```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1

1 200001```

### 输出

```
2```

## 样例 #3

### 输入

```
2 3

998244353 998244853```

### 输出

```
3```

## 样例 #4

### 输入

```
1 1

1 1```

### 输出

```
0```

# AI分析结果



# [ABC184C] Super Ryuma

## 题目描述

在无限大的二维网格中，棋子"超竜马"位于 $(r_1, c_1)$。它每步可以进行以下移动之一：

1. 移动到同一对角线（满足 $a+b=c+d$ 或 $a−b=c−d$）
2. 曼哈顿距离不超过3的移动

求从 $(r_1, c_1)$ 到 $(r_2, c_2)$ 所需的最小步数。

### 数据范围
- $1 \le r_1, c_1, r_2, c_2 \le 10^9$

---

**算法分类**：数学（分类讨论）

---

## 题解分析与结论

### 题解对比与关键思路

1. **最大步数不超过3**  
   通过棋盘染色法（坐标和奇偶性），证明无论目标点颜色是否相同，最多3步可达。

2. **分类讨论条件**  
   - **0步**：起点终点相同
   - **1步**：满足对角线条件或曼哈顿距离≤3
   - **2步**：满足以下任一条件：
     - 颜色相同（坐标和奇偶性相同）
     - 曼哈顿距离≤6
     - 对角线差绝对值≤3（允许一次调整后走对角线）
   - **3步**：其余情况

3. **棋盘染色技巧**  
   将坐标和的奇偶性作为颜色判断依据，简化路径规划。

---

## 精选题解

### 题解1：yinbe（4星）
**关键亮点**：
- 系统性的分类讨论，覆盖所有边界条件
- 棋盘染色法证明最坏情况步数
- 代码条件判断简洁高效

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a,b,c,d; 
int main() {
    scanf("%d%d%d%d",&a,&b,&c,&d);
    if(a==c && b==d) printf("0");
    else if(a+b==c+d || a-b==c-d || abs(a-c)+abs(b-d)<=3)
        printf("1");
    else if((a+b)%2 == (c+d)%2)  // 颜色判断优化为坐标和奇偶性
        printf("2");
    else if(abs(a-c)+abs(b-d)<=6)
        printf("2");
    else if(abs((a+b)-(c+d))<=3)
        printf("2");
    else if(abs((a-b)-(c-d))<=3)
        printf("2");
    else
        printf("3");
    return 0;
}
```

---

### 题解2：chrispang（4星）
**关键亮点**：
- 直观的棋盘染色示意图辅助理解
- 条件顺序优化提升判断效率

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, c, d;
int main() {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if (a == c && b == d) printf("0");
    else if (a + b == c + d || a - b == c - d || abs(a - c) + abs(b - d) <= 3) printf("1");
    else if ((a + b) % 2 == (c + d) % 2) printf("2");
    else if (abs(a - c) + abs(b - d) <= 6) printf("2");
    else if (abs(a + b - (c + d)) <= 3) printf("2");
    else if (abs(a - b - (c - d)) <= 3) printf("2");
    else printf("3");
    return 0;
}
```

---

### 题解3：aCssen（4星）
**关键亮点**：
- 包含移动路径的逆向构造思路
- 覆盖更多中间调整的情况

```cpp
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
int main() {
    int r1,c1,r2,c2;
    cin>>r1>>c1>>r2>>c2;
    if(r1==r2 && c1==c2) cout<<0;
    else if(abs(r1-r2)+abs(c1-c2)<=3 || r1+c1==r2+c2 || r1-c1==r2-c2) cout<<1;
    else if((r1+c1+r2-c2)%2==0 || abs(r1-r2)+abs(c1-c2)<=6 || ... ) cout<<2; 
    else cout<<3;
}
```

---

## 关键技巧总结
1. **奇偶性染色法**：快速判断是否可通过两次对角线到达
2. **曼哈顿距离分层**：≤3（1步）、≤6（2步）、其他（结合其他条件）
3. **条件顺序优化**：将高频命中条件前置提升效率

---

## 类似题目推荐
1. [P2730 [IOI] 棋盘游戏](https://www.luogu.com.cn/problem/P2730)  
2. [CF510B Fox And Two Dots](https://www.luogu.com.cn/problem/CF510B)  
3. [P1747 走方格](https://www.luogu.com.cn/problem/P1747)

---
处理用时：259.23秒