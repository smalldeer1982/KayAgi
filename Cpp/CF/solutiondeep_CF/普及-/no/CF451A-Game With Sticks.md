# 题目信息

# Game With Sticks

## 题目描述

After winning gold and silver in IOI 2014, Akshat and Malvika want to have some fun. Now they are playing a game on a grid made of $ n $ horizontal and $ m $ vertical sticks.

An intersection point is any point on the grid which is formed by the intersection of one horizontal stick and one vertical stick.

In the grid shown below, $ n=3 $ and $ m=3 $ . There are $ n+m=6 $ sticks in total (horizontal sticks are shown in red and vertical sticks are shown in green). There are $ n·m=9 $ intersection points, numbered from $ 1 $ to $ 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/18b27511f71a42f9e0fd0b22af6d5248021325d7.png)The rules of the game are very simple. The players move in turns. Akshat won gold, so he makes the first move. During his/her move, a player must choose any remaining intersection point and remove from the grid all sticks which pass through this point. A player will lose the game if he/she cannot make a move (i.e. there are no intersection points remaining on the grid at his/her move).

Assume that both players play optimally. Who will win the game?

## 说明/提示

Explanation of the first sample:

The grid has four intersection points, numbered from $ 1 $ to $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/e0d83475f64b355b0a9b5538e74aa373b38a9909.png)If Akshat chooses intersection point $ 1 $ , then he will remove two sticks ( $ 1-2 $ and $ 1-3 $ ). The resulting grid will look like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/c9bd491d9b8dd9c48045e00c65ed3725174a35a0.png)Now there is only one remaining intersection point (i.e. $ 4 $ ). Malvika must choose it and remove both remaining sticks. After her move the grid will be empty.

In the empty grid, Akshat cannot make any move, hence he will lose.

Since all $ 4 $ intersection points of the grid are equivalent, Akshat will lose no matter which one he picks.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
Malvika
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
Malvika
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
Akshat
```

# AI分析结果

【题目内容（中文重写）】
# 棍子游戏

## 题目描述
在 2014 年的国际信息学奥林匹克竞赛（IOI）中斩获金牌和银牌后，阿克沙特（Akshat）和马尔维卡（Malvika）想找点乐子。现在他们正在一个由 $n$ 根水平棍子和 $m$ 根垂直棍子组成的网格上玩游戏。

交点是指网格中由一根水平棍子和一根垂直棍子相交形成的点。

在下图所示的网格中，$n = 3$ 且 $m = 3$。总共有 $n + m = 6$ 根棍子（水平棍子用红色表示，垂直棍子用绿色表示）。有 $n·m = 9$ 个交点，从 $1$ 到 $9$ 编号。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/18b27511f71a42f9e0fd0b22af6d5248021325d7.png)
游戏规则非常简单。玩家轮流行动。阿克沙特获得了金牌，所以他先行动。在轮到自己行动时，玩家必须选择任意一个剩余的交点，并从网格中移除所有经过该点的棍子。如果一名玩家无法行动（即轮到他行动时网格中没有剩余的交点），则该玩家输掉游戏。

假设两名玩家都采取最优策略。谁将赢得游戏？

## 说明/提示
第一个样例的解释：

网格有四个交点，编号从 $1$ 到 $4$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/e0d83475f64b355b0a9b5538e74aa373b38a9909.png)
如果阿克沙特选择交点 $1$，那么他将移除两根棍子（$1 - 2$ 和 $1 - 3$）。得到的网格将如下所示。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF451A/c9bd491d9b8dd9c48045e00c65ed3725174a35a0.png)
现在只剩下一个交点（即 $4$）。马尔维卡必须选择它并移除剩下的两根棍子。她行动后，网格将为空。

在空网格中，阿克沙特无法行动，因此他将输掉游戏。

由于网格的所有 $4$ 个交点都是等价的，无论阿克沙特选择哪一个，他都会输掉。

## 样例 #1
### 输入
```
2 2
```
### 输出
```
Malvika
```

## 样例 #2
### 输入
```
2 3
```
### 输出
```
Malvika
```

## 样例 #3
### 输入
```
3 3
```
### 输出
```
Akshat
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路基本一致，都是将问题转化为判断水平棍子数 $n$ 和垂直棍子数 $m$ 中的最小值的奇偶性。因为每次取走一个交点会同时拿走一根水平棍子和一根垂直棍子，当数量较少的那类棍子被取完时游戏结束，所以游戏可进行的总次数由 $min(n, m)$ 决定。若 $min(n, m)$ 为奇数，则先手阿克沙特胜；若为偶数，则后手马尔维卡胜。

各题解的算法要点都是计算 $min(n, m)$ 并判断其奇偶性，只是在代码实现上略有不同，有的使用 if - else 语句，有的使用三目运算符。解决的难点在于分析出游戏的胜负与 $min(n, m)$ 奇偶性的关系。

【题解评分】
- 作者：封禁用户 (赞：3)：4星。思路清晰，对题意和解题思路的分析详细，代码有注释且使用了加速输入输出的技巧，还给出了运行结果。
- 作者：3a51_ (赞：1)：3星。思路简洁，但缺乏对思路的详细解释。
- 作者：Ybocean_s (赞：1)：3星。思路和代码都比较常规，没有特别的亮点。
- 作者：LordLaffey (赞：1)：3星。思路分析较清晰，代码使用数组存储结果，有一定特色。
- 作者：BlackPanda (赞：0)：3星。思路和代码都中规中矩。
- 作者：封禁用户 (赞：0)：3星。思路解释详细，但代码中使用自定义类型略显多余。
- 作者：违规用户名gAGt8$%z (赞：0)：3星。思路简洁，代码简短。
- 作者：Creator_157 (赞：0)：3星。思路清晰，给出了两种代码实现方式。
- 作者：shiroi (赞：0)：3星。使用了快速读入的技巧，但整体思路和其他题解类似。

【所选题解】
- 作者：封禁用户 (赞：3)：4星。关键亮点在于思路详细，对题意和解题思路进行了全面的分析，代码有注释且使用了加速输入输出的技巧。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    //freopen("input.in","r",stdin);
    //freopen("print.out","w",stdout);
    ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
    int n,m;   //定义竖棒数和横棒数
    cin>>n>>m;
    cout<<(min(n,m)%2!=0? "Akshat":"Malvika");   //利用三目运算符判断输出
    return 0;   //结束整个程序
}
```
核心实现思想：先读取输入的水平棍子数 $n$ 和垂直棍子数 $m$，然后使用三目运算符判断 $min(n, m)$ 的奇偶性，根据奇偶性输出胜者。

【关键思路或技巧】
- 思维方式：将复杂的博弈过程简化为对水平和垂直棍子数量最小值的奇偶性判断，通过分析游戏规则找到问题的本质。
- 代码实现技巧：可以使用三目运算符简化 if - else 语句的判断过程。

【拓展思路】
同类型题可以是其他博弈类题目，例如在棋盘上进行的取子游戏等，解题关键在于分析游戏规则，找到影响胜负的关键因素，再通过数学方法进行判断。

【推荐题目】
- [P1288 取数游戏 II](https://www.luogu.com.cn/problem/P1288)
- [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)
- [P2964 [USACO09NOV]A Coin Game S](https://www.luogu.com.cn/problem/P2964)

【个人心得】
作者：封禁用户 (赞：0) 提到“忘了int吧，我被int坑过10000000回！！！”，总结为在编程中要注意数据类型的选择，避免因数据范围问题导致错误。 

---
处理用时：43.35秒