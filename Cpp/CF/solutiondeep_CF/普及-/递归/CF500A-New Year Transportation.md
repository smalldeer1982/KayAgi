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

### 题目中文重写
# 新年交通

## 题目描述
新年即将在直线世界来临！在这个世界里，有 $n$ 个由整数 $1$ 到 $n$ 编号的单元格，就像一个 $1×n$ 的棋盘。人们居住在这些单元格中。然而，由于离开单元格的困难，在不同单元格之间移动十分艰难。人们希望能与居住在其他单元格的人见面。

于是，用户 tncks0121 为庆祝新年，制作了一个交通系统来实现这些单元格之间的移动。首先，他想到了 $n - 1$ 个正整数 $a_1, a_2, \cdots, a_{n - 1}$。对于每个满足 $1 \leq i \leq n - 1$ 的整数 $i$，都有条件 $1 \leq a_i \leq n - i$ 成立。接着，他制作了 $n - 1$ 个传送门，编号从 $1$ 到 $n - 1$。第 $i$ 个（$1 \leq i \leq n - 1$）传送门连接单元格 $i$ 和单元格 $(i + a_i)$，人们可以使用第 $i$ 个传送门从单元格 $i$ 移动到单元格 $(i + a_i)$。不幸的是，传送门不能反向使用，也就是说不能使用第 $i$ 个传送门从单元格 $(i + a_i)$ 移动到单元格 $i$。由于条件 $1 \leq a_i \leq n - i$，很容易看出人们无法使用传送门离开直线世界。

目前，我站在单元格 $1$，想要前往单元格 $t$。然而，我不知道是否有可能到达那里。请判断我是否只能通过这个构建好的交通系统到达单元格 $t$。

## 说明/提示
在第一个样例中，经过的单元格是：$1, 2, 4$；所以我们可以成功到达单元格 $4$。

在第二个样例中，可能到达的单元格是：$1, 2, 4, 6, 7, 8$；所以我们无法到达我们想去的单元格 $5$。

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

### 题解综合分析与结论
这些题解主要围绕能否从单元格 1 到达单元格 t 展开，思路大致可分为递推、递归和图论三种。
- **递推思路**：从单元格 1 开始，按照传送规则不断更新当前所在单元格，直到超过或到达目标单元格 t。如 Register、HNYLMS_MuQiuFeng、empty_zhm 等人的题解。
- **递归思路**：通过函数不断调用自身，模拟传送过程，判断是否能到达目标单元格。如 OdtreePrince、chenyilai、打表大蒟蒻的题解。
- **图论思路**：将问题抽象为图，使用最短路算法（如 dijkstra）或广度/深度优先搜索（如 Lips、RainFestival）判断两点是否连通。

### 题解评分与选择
|作者|思路清晰度|代码可读性|优化程度|评分|
| ---- | ---- | ---- | ---- | ---- |
|Register|清晰，注释详细|高，代码简洁|高，一行 for 循环解决递推|5星|
|HNYLMS_MuQiuFeng|较清晰，有简单思路说明|较高，代码结构常规|一般，常规递推|4星|
|empty_zhm|清晰，思路明确|一般，部分代码使用三目运算符嵌套|高，代码简洁|4星|

### 所选题解
- **Register（5星）**
    - **关键亮点**：思路清晰，注释详细，代码简洁，使用一行 for 循环完成递推。
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
- **HNYLMS_MuQiuFeng（4星）**
    - **关键亮点**：思路清晰，代码结构常规，容易理解。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
    int n,t;cin>>n>>t;
    int a[n+1];
    int ans=1;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n-1;i++)
    {
        ans+=a[ans];
        if(ans==t)
        {
            cout<<"YES";
            return 0;
        }
        if(ans>t)
        {
            cout<<"NO";
            return 0;
        }
    }
}
```
- **empty_zhm（4星）**
    - **关键亮点**：思路明确，代码简洁，使用三目运算符嵌套优化代码。
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

### 最优关键思路或技巧
- **递推思想**：利用传送规则不断更新当前位置，直到满足结束条件，代码简洁高效。
- **三目运算符嵌套**：在代码中使用三目运算符嵌套可以使代码更加简洁，但可能会降低可读性，需要根据实际情况使用。

### 拓展思路
同类型题或类似算法套路：
- 路径可达性问题：判断在有向图或无向图中两点是否可达，可使用广度优先搜索、深度优先搜索或并查集等算法。
- 模拟移动问题：根据给定的移动规则，模拟物体的移动过程，判断是否能到达目标位置。

### 推荐洛谷题目
- P1141 01迷宫：判断在一个由 0 和 1 组成的迷宫中，从某个点出发能到达的所有点的数量。
- P1605 迷宫：在一个迷宫中，判断从起点到终点是否存在路径。
- P3958 奶酪：判断在一个三维空间的奶酪中，从底部的洞是否能到达顶部的洞。

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：42.79秒