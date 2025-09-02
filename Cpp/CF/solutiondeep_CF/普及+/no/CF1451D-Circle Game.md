# 题目信息

# Circle Game

## 题目描述

Utkarsh is forced to play yet another one of Ashish's games. The game progresses turn by turn and as usual, Ashish moves first.

Consider the 2D plane. There is a token which is initially at  $ (0,0) $ . In one move a player must increase either the $ x $ coordinate or the $ y $ coordinate of the token by exactly $ k $ . In doing so, the player must ensure that the token stays within a (Euclidean) distance $ d $ from $ (0,0) $ .

In other words, if after a move the coordinates of the token are $ (p,q) $ , then $ p^2 + q^2 \leq d^2 $ must hold.

The game ends when a player is unable to make a move. It can be shown that the game will end in a finite number of moves. If both players play optimally, determine who will win.

## 说明/提示

In the first test case, one possible sequence of moves can be

 $ (0, 0) \xrightarrow{\text{Ashish }} (0, 1) \xrightarrow{\text{Utkarsh }} (0, 2) $ .

Ashish has no moves left, so Utkarsh wins.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1451D/00adebe318fd60c39c1fde9564efcda9489c81f2.png)

## 样例 #1

### 输入

```
5
2 1
5 2
10 3
25 4
15441 33```

### 输出

```
Utkarsh
Ashish
Utkarsh
Utkarsh
Ashish```

# AI分析结果

### 题目翻译
# 圆圈游戏

## 题目描述
Utkarsh 被迫要玩 Ashish 的另一个游戏。游戏是轮流进行的，和往常一样，Ashish 先行动。

考虑二维平面。有一个令牌，初始位置在 $(0, 0)$。在每一步行动中，玩家必须将令牌的 $x$ 坐标或 $y$ 坐标恰好增加 $k$。在行动过程中，玩家必须确保令牌与 $(0, 0)$ 的（欧几里得）距离不超过 $d$。

换句话说，如果行动后令牌的坐标为 $(p, q)$，那么必须满足 $p^2 + q^2 \leq d^2$。

当一名玩家无法行动时，游戏结束。可以证明，游戏会在有限步内结束。如果两名玩家都采取最优策略，请判断谁会获胜。

## 说明/提示
在第一个测试用例中，一种可能的行动顺序是：
$(0, 0) \xrightarrow{\text{Ashish }} (0, 1) \xrightarrow{\text{Utkarsh }} (0, 2)$。
Ashish 没有可走的步了，所以 Utkarsh 获胜。

## 样例 #1
### 输入
```
5
2 1
5 2
10 3
25 4
15441 33
```

### 输出
```
Utkarsh
Ashish
Utkarsh
Utkarsh
Ashish
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕博弈论的思想，通过分析游戏中玩家的行动策略和必胜必败状态来解决问题。大部分题解都发现了先手和后手可以分别控制对方在特定直线（如 $y = x$、$y = x \pm k$）上行动的规律，然后通过判断直线 $y = x$ 上最远可达点的后继点是否可达来确定胜负。不同题解在实现细节和思路阐述上略有差异，但核心思想一致。

### 所选题解
- **Scintilla（4星）**
    - **关键亮点**：思路清晰，通过类比经典的硬币放置游戏，将对称思想应用到本题，易于理解。代码简洁，直接根据关键条件判断胜负。
- **NashChen（4星）**
    - **关键亮点**：对合法点进行简化，通过分析最大合法点及其后继点的合法性来确定胜负，逻辑严谨。
- **VinstaG173（4星）**
    - **关键亮点**：通过画图直观地展示必胜点和必败点的规律，然后根据规律判断胜负，思路直观易懂。

### 重点代码
#### Scintilla 的代码
```cpp
int tc; ll d, k;
int main() {
    tc = read();
    while (tc--) {
        d = read(), k = read();
        ll tp = sqrt(d * d / 2);
        tp = tp / k * k;
        puts(tp * tp + (tp + k) * (tp + k) <= d * d ? "Ashish" : "Utkarsh");
    } 
    return 0;
}
```
**核心实现思想**：先计算出 $y = x$ 上最远可达点的坐标，然后判断该点的后继点是否在圆内，若在圆内则先手必胜，否则后手必胜。

#### NashChen 的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

long long T,N,M;
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&N,&M);
        long long k= (long double)N/M*sqrt(0.5);
        if(N*N< M*M*(2*k*k+2*k+1)) puts("Utkarsh");
        else puts("Ashish");
    }
    return 0;
}
```
**核心实现思想**：将合法点简化为圆内的整点，找到 $y = x$ 上最大的合法点，判断其后继点是否合法，从而确定胜负。

#### VinstaG173 的代码
```cpp
#include<cstdio>
#define ll long long
int t,d,k,x;
int main()
{
    scanf(" %d",&t);
    while(t--)
    {
        scanf(" %d %d",&d,&k);
        x=0.70710678*d/k;
        if((ll)k*k*(x*(x+1ll)<<1|1)<=(ll)d*d)puts("Ashish");
        else puts("Utkarsh");
    }
    return 0;
}
```
**核心实现思想**：直接判断直线 $y = x$ 上最远可达点的后继点是否可达，若可达则先手必胜，否则后手必胜。

### 最优关键思路或技巧
- **对称思想**：通过类比经典游戏，将对称思想应用到本题，分析先手和后手的行动策略。
- **必胜必败状态分析**：根据博弈论的基本定理，分析游戏中的必胜必败状态，找到判断胜负的关键条件。
- **简化问题**：将合法点简化为圆内的整点，减少问题的复杂度。

### 拓展思路
同类型题可能会改变游戏的规则，如行动的方式、获胜的条件等，但核心思路仍然是分析玩家的行动策略和必胜必败状态。类似的算法套路可以应用到其他博弈论问题中，如 Nim 游戏、巴什博奕等。

### 推荐题目
- [P2197 nim 游戏](https://www.luogu.com.cn/problem/P2197)
- [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)
- [P2964 [USACO09NOV]A Coin Game S](https://www.luogu.com.cn/problem/P2964)

### 个人心得
- **Konnyaku_LXZ**：特别注意 `sqrt` 的返回值不是整数，所以要先转换成整数之后再除以 $k$，否则等于没除。这提醒我们在处理浮点数运算时要注意数据类型的转换。

---
处理用时：45.83秒