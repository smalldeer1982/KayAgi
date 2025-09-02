# 题目信息

# Hexagons!

## 题目描述

After a probationary period in the game development company of IT City Petya was included in a group of the programmers that develops a new turn-based strategy game resembling the well known "Heroes of Might & Magic". A part of the game is turn-based fights of big squadrons of enemies on infinite fields where every cell is in form of a hexagon.

Some of magic effects are able to affect several field cells at once, cells that are situated not farther than $ n $ cells away from the cell in which the effect was applied. The distance between cells is the minimum number of cell border crosses on a path from one cell to another.

It is easy to see that the number of cells affected by a magic effect grows rapidly when $ n $ increases, so it can adversely affect the game performance. That's why Petya decided to write a program that can, given $ n $ , determine the number of cells that should be repainted after effect application, so that game designers can balance scale of the effects and the game performance. Help him to do it. Find the number of hexagons situated not farther than $ n $ cells away from a given cell.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630D/b73bc98c088fe19987a12ad8929090ba13c1d4a0.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
19```

# AI分析结果

### 题目翻译
在 IT 城市的游戏开发公司经过一段试用期后，彼得亚被纳入了一个程序员小组，该小组正在开发一款新的回合制策略游戏，类似于著名的《魔法门之英雄无敌》。游戏的一部分是在无限的场地上进行大型敌军中队的回合制战斗，场地中的每个格子都是六边形的。

一些魔法效果能够同时影响多个场地格子，这些格子与施加魔法效果的格子的距离不超过 $n$ 个格子。两个格子之间的距离是从一个格子到另一个格子的路径上最少的格子边界交叉数。

很容易看出，当 $n$ 增大时，受魔法效果影响的格子数量会迅速增加，这可能会对游戏性能产生不利影响。因此，彼得亚决定编写一个程序，该程序可以在给定 $n$ 的情况下，确定在施加魔法效果后需要重新绘制的格子数量，以便游戏设计师能够平衡魔法效果的规模和游戏性能。请帮助他完成这个任务。求出与给定格子的距离不超过 $n$ 的六边形的数量。

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先找出距离中心六边形不同距离的六边形数量规律，即除距离为 0 的中心六边形有 1 个外，距离为 $n\ (n\ne0)$ 的六边形有 $6n$ 个，然后在此基础上通过等差数列求和公式计算距离不超过 $n$ 的六边形总数。不同题解的差异主要在于推导公式的详细程度、代码实现的语言和方式。
- **思路**：多数题解通过观察图形找规律，发现每一圈六边形数量构成等差数列，进而利用等差数列求和公式求解。部分题解还通过数学归纳法证明公式的正确性。
- **算法要点**：关键在于找出等差数列的首项、末项和项数，利用公式 $S_n=\frac{(a_1 + a_n)n}{2}$ 求和，最后加上中心的 1 个六边形。
- **解决难点**：主要难点在于发现六边形数量的规律，并正确推导出求和公式。部分题解通过多算几项、查询相关数列网站或使用数学归纳法来验证规律和公式的正确性。

### 高评分题解
- **超级玛丽王子（5星）**
    - **关键亮点**：思路清晰，通过图形直观展示规律，推导公式过程详细，且代码实现简洁明了。
- **Aw顿顿（4星）**
    - **关键亮点**：提供了两种解题方法，不仅通过找规律和等差数列求和求解，还介绍了利用六边形数的方法，拓展了思路。
- **agicy（4星）**
    - **关键亮点**：手动计算多组样例数据提出猜想，然后用数学归纳法严格证明公式的正确性，逻辑严谨。

### 重点代码
```cpp
// 超级玛丽王子题解代码
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    cout << 3 * n * n + 3 * n + 1 << endl;
    return 0;
}

// Aw顿顿题解代码
#include<bits/stdc++.h>
using namespace std;
long long x;
int main(){
    cin>>x;
    cout<<3*x*(x+1)+1<<endl;
    return 0;
}

// agicy题解代码
#include<stdio.h>
long long n;
int main(void){
    scanf("%lld",&n);
    printf("%lld\n",3*n*n+3*n+1);
    return 0;
}
```
**核心实现思想**：这些代码都是先读取输入的 $n$，然后根据推导出的公式 $3n^2 + 3n + 1$ 计算并输出距离不超过 $n$ 的六边形的数量。

### 拓展思路
同类型题可能会改变图形的形状（如三角形网格、正方形网格等），但解题的关键仍然是找出不同层次图形数量的规律，再利用数学方法（如等差数列求和、等比数列求和等）进行计算。类似算法套路包括找规律、数学归纳法证明、利用已知数列知识等。

### 推荐题目
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：考察数学计算和高精度处理。
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及数学中的指数运算和高精度计算。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列和数学中的公约数知识。

### 个人心得
部分题解提到通过多算几项来验证猜想，这是一种很实用的方法，可以帮助我们发现规律和验证公式的正确性。还有题解提到查询相关数列网站，这为我们提供了一种查找已知数列规律的途径。 

---
处理用时：28.84秒