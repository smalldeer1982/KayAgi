# 题目信息

# New Year Transportation

## 题目描述

New Year is coming in Line World! In this world, there are $ n $ cells numbered by integers from $ 1 $ to $ n $ , as a $ 1×n $ board. People live in cells. However, it was hard to move between distinct cells, because of the difficulty of escaping the cell. People wanted to meet people who live in other cells.

So, user tncks0121 has made a transportation system to move between these cells, to celebrate the New Year. First, he thought of $ n-1 $ positive integers $ a_{1},a_{2},...,a_{n-1} $ . For every integer $ i $ where $ 1<=i<=n-1 $ the condition $ 1<=a_{i}<=n-i $ holds. Next, he made $ n-1 $ portals, numbered by integers from 1 to $ n-1 $ . The $ i $ -th ( $ 1<=i<=n-1 $ ) portal connects cell $ i $ and cell $ (i+a_{i}) $ , and one can travel from cell $ i $ to cell $ (i+a_{i}) $ using the $ i $ -th portal. Unfortunately, one cannot use the portal backwards, which means one cannot move from cell $ (i+a_{i}) $ to cell $ i $ using the $ i $ -th portal. It is easy to see that because of condition $ 1<=a_{i}<=n-i $ one can't leave the Line World using portals.

Currently, I am standing at cell $ 1 $ , and I want to go to cell $ t $ . However, I don't know whether it is possible to go there. Please determine whether I can go to cell $ t $ by only using the construted transportation system.

## 说明/提示

In the first sample, the visited cells are: $ 1,2,4 $ ; so we can successfully visit the cell $ 4 $ .

In the second sample, the possible cells to visit are: $ 1,2,4,6,7,8 $ ; so we can't visit the cell $ 5 $ , which we want to visit.

## 样例 #1

### 输入

```
8 4
1 2 1 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8 5
1 2 1 2 1 1 1
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 新年交通

## 题目描述
新年即将在直线世界来临！在这个世界里，有 $n$ 个由整数 $1$ 到 $n$ 编号的单元格，就像一个 $1×n$ 的棋盘。人们居住在这些单元格中。然而，在不同单元格之间移动非常困难，因为很难从一个单元格中出去。人们希望能与居住在其他单元格的人见面。

于是，用户 tncks0121 制作了一个交通系统来实现这些单元格之间的移动，以此庆祝新年。首先，他想出了 $n - 1$ 个正整数 $a_1, a_2, ..., a_{n - 1}$。对于每个满足 $1 \leq i \leq n - 1$ 的整数 $i$，都有 $1 \leq a_i \leq n - i$ 这个条件成立。接着，他制作了 $n - 1$ 个传送门，编号从 $1$ 到 $n - 1$。第 $i$ 个（$1 \leq i \leq n - 1$）传送门连接单元格 $i$ 和单元格 $(i + a_i)$，人们可以通过第 $i$ 个传送门从单元格 $i$ 移动到单元格 $(i + a_i)$。不幸的是，传送门不能反向使用，也就是说不能通过第 $i$ 个传送门从单元格 $(i + a_i)$ 移动到单元格 $i$。由于条件 $1 \leq a_i \leq n - i$，很容易看出人们无法通过传送门离开直线世界。

目前，我站在单元格 $1$，我想去单元格 $t$。然而，我不知道是否有可能到达那里。请判断我是否可以仅使用这个构建好的交通系统到达单元格 $t$。

## 说明/提示
在第一个样例中，经过的单元格是：$1, 2, 4$；所以我们可以成功到达单元格 $4$。

在第二个样例中，可能经过的单元格是：$1, 2, 4, 6, 7, 8$；所以我们无法到达我们想去的单元格 $5$。

## 样例 #1
### 输入
```
8 4
1 2 1 2 1 2 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
8 5
1 2 1 2 1 1 1
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是围绕从单元格 1 出发，利用传送门规则尝试到达目标单元格 t，判断是否能够成功。
- **思路分类**：主要分为递推、递归和图论（Dijkstra 算法、BFS/DFS 思想）三类。递推和递归是根据传送门的规则直接模拟移动过程；图论方法则是将问题抽象成图，利用图的算法求解。
- **算法要点**：递推和递归通过不断更新当前所在单元格，根据是否到达或超过目标单元格判断结果；图论方法需要先构建图，再利用相应算法判断连通性。
- **解决难点**：主要难点在于正确处理传送门的规则，避免越界和死循环，以及在图论方法中正确构建图和实现算法。

### 所选题解
- **作者：Register（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用 for 循环一行实现递推，易于理解。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int main(){
    int a[30001],n,t;
    cin>>n>>t;
    for(int i=1;i<n;i++) cin>>a[i];
    int i;
    for(i=1;i<t;i+=a[i]) ;
    if(i==t) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```
- **作者：empty_zhm（4星）**
    - **关键亮点**：代码简洁，使用 while 循环和三目运算符实现递推，有两种不同的简洁写法。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int N[50100],n,k,j=1;
int main()
{
    cin >> n >> k;
    for(int i=1;i<=n-1;i++) cin >> N[i];
    while(j<k) j+=N[j];
    cout << (j==k?"YES":"NO");
}
```
- **作者：打表大蒟蒻（4星）**
    - **关键亮点**：使用递归函数实现，思路清晰，对递归的终止条件处理明确。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXn = 30000 + 10;
int a[MAXn];
inline int read(){
    int s=0,w=1;   
    char ch=getchar();   
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}   
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();   
    return s*w;
}
void pd(int t,int num){
    if(num==t) {printf("YES\n");return ;}
    else if(num>t)  {printf("NO\n");return ;}
    num+=a[num];
    pd(t,num);
}  
int main ()
{
    int n, t;  
    n=read();t=read();
    for(int i=1;i<n;i++) a[i]=read();
    pd(t,1);
    return 0;
 } 
```

### 最优关键思路或技巧
- **递推思想**：根据传送门的规则，不断更新当前所在单元格，直到到达或超过目标单元格，这种方法简单直接，代码实现简洁。
- **递归思想**：将问题分解为子问题，通过不断调用自身来模拟移动过程，利用递归的终止条件判断结果。
- **图论抽象**：将问题抽象成图，利用图的算法求解，适用于更复杂的路径问题。

### 可拓展之处
同类型题或类似算法套路：
- **路径规划问题**：给定一些节点和它们之间的连接关系，判断是否可以从一个节点到达另一个节点，可使用递推、递归或图论算法。
- **迷宫问题**：在迷宫中寻找从起点到终点的路径，可使用深度优先搜索（DFS）或广度优先搜索（BFS）。

### 推荐洛谷题目
- P1135 奇怪的电梯：与本题类似，通过电梯的规则在楼层间移动，判断是否能到达目标楼层。
- P1605 迷宫：经典的迷宫路径搜索问题，可使用 DFS 或 BFS 求解。
- P1330 封锁阳光大学：图的染色问题，可使用图的遍历算法解决。

### 个人心得摘录与总结
- **作者：Lips**：提到用 Dijkstra 算法作为 AC 的第 100 个橙题纪念，说明可以用不同的算法解决看似简单的问题，拓宽解题思路。
- **作者：打表大蒟蒻**：强调递归是一个“诡异的神器”，提醒在使用递归时要注意终止条件，避免死循环。

---
处理用时：45.09秒