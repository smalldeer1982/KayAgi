# 题目信息

# [ICPC 2020 Shanghai R] Mine Sweeper II

## 题目描述

A mine-sweeper map $X$ can be expressed as an $n\times m$ grid. Each cell of the grid is either a mine cell or a non-mine cell. A mine cell has no number on it. Each non-mine cell has a number representing the number of mine cells around it. (A cell is around another cell if they share at least one common point. Thus, every cell that is not on the boundary has $8$ cells around it.) The following is a $16\times 30$ mine-sweeper map where a flagged cell denotes a mine cell and a blank cell denotes a non-mine cell with number 0.

![](https://cdn.luogu.com.cn/upload/image_hosting/5bykwzuy.png)

Given two mine-sweeper maps $A, B$ of size $n\times m$, you should modify at most $\left\lfloor\frac{nm}{2}\right\rfloor$ (i.e. the largest nonnegative integer that is less than or equal to $\frac{nm}{2}$) cells in $B$ (from a non-mine cell to a mine cell or vice versa) such that the sum of numbers in the non-mine cells in $A$ and the sum of numbers in the non-mine cells in $B$ are the same. (If a map has no non-mine cell, the sum is considered as $0$.)

If multiple solutions exist, print any of them. If no solution exists, print ``-1`` in one line.

## 说明/提示

We modify one cell in $B$. Then the sums of the numbers on non-mine cells in $A$ and $B$ both equal $10$.

## 样例 #1

### 输入

```
2 4
X..X
X.X.
X.X.
.X..```

### 输出

```
X.XX
.X..```

# AI分析结果

### 综合分析与结论
所有题解思路核心一致，均基于以下两点：
1. **原图与反图数字和相等**：通过分析相邻格子间地雷与非地雷的贡献得出，无论格子状态如何改变，相邻（雷格子，非雷格子）二元组的个数不变，即数字和不变。
2. **必有一图与B图差异满足条件**：设A和B有k个格子不同，A与反图A₂所有格子都不同，所以B与A₂有nm - k个格子不同，k和nm - k中必有一数不大于 ⌊nm/2⌋。
各题解主要差异在于表述清晰度与代码风格，整体思路与算法要点无本质区别。

### 所选的题解
- **作者：Vct14 (5星)**
  - **关键亮点**：对结论给出详细证明过程，思路清晰，代码简洁明了。
  - **核心代码**：
```c++
int getbomb(){
    char bomb;
    cin>>bomb;
    if(bomb=='X') return 1;
    else return 0;
} 

void outbomb(bool b){
    if(b) cout<<"X";
    else cout<<".";
}

bool a[1002][1002];

int main(){
    int n,m;
    cin>>n>>m;
    int k=0;
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) a[i][j]=getbomb();
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) if(getbomb()!=a[i][j]) k++;
    if(k<=n*m/2){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++) outbomb(a[i][j]);
            cout<<"\n";
        }
    } 
    else{
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++) outbomb(!a[i][j]);
            cout<<"\n";
        }
    } 
    return 0;
}
```
  - **核心实现思想**：先读入A图数据，再读入B图并同时统计与A图不同格子数k，根据k与n*m/2的大小关系，输出A图或A图的反图。
- **作者：chen_zhe (4星)**
  - **关键亮点**：转载官方题解，简洁阐述核心思路，即考虑数字和等于相邻（雷格子，非雷格子）二元组的个数，利用地图取反二元组个数不变及与B图偏差必有一个不超过一半的性质解题。
  - **核心代码**：无（未提供代码）
  - **核心实现思想**：根据上述思路，判断A图或A图反图哪个与B图偏差不超过一半，将B图修改为该图。
- **作者：Nuyoah_awa (4星)**
  - **关键亮点**：补充反图数字和相同的证明，从数字和由来，即周围地雷对非地雷格的贡献角度分析，逻辑清晰。
  - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long

using namespace std;

const int N = 1e3 + 5;
int n, m, sum;
string s[N], t[N];

signed main()
{
    scanf("%d %d", &n, &m);
    for(int i = 1;i <= n;i++)
    {
        cin >> s[i];
        s[i] = "#" + s[i];
    }
    for(int i = 1;i <= n;i++)
    {
        cin >> t[i];
        t[i] = "#" + t[i];
    }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            if(s[i][j]!= t[i][j])
                sum++;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
            if(sum > n * m / 2)
                cout << (s[i][j] == '.'? 'X' : '.');
            else
                cout << s[i][j];
        puts("");
    }
    return 0;
}
```
  - **核心实现思想**：读入A、B图数据，统计A与B图不同格子数sum，根据sum与n*m/2的大小关系，输出A图或A图的反图。

### 最优关键思路或技巧
1. **思维方式**：从数字和的本质（相邻雷格与非雷格二元组个数）出发，发现原图与反图数字和相等的性质，巧妙利用两张图与B图差异的关系解决问题。
2. **代码实现技巧**：通过简洁循环统计两张图的差异格子数，根据差异与 ⌊nm/2⌋ 的比较结果，直接输出A图或其反图。

### 可拓展之处
同类型题可关注涉及矩阵变换、状态调整且有操作次数限制的构造类题目。类似算法套路为挖掘题目中隐藏的不变量（如本题反图数字和不变），利用数据间的对称或互补关系（如本题A与A₂和B图差异的关系）来设计构造方法。

### 相似知识点洛谷题目
1. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及博弈策略与状态分析，与本题类似，需挖掘题目隐藏性质来设计策略。
2. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：在序列分析与操作中，寻找序列间关系及不变量，与本题思维方式类似。
3. [P2048 游戏](https://www.luogu.com.cn/problem/P2048)：通过对游戏状态的操作与调整达到目标，类似本题对地图状态调整的思路。

### 个人心得摘录与总结
无。 

---
处理用时：75.76秒