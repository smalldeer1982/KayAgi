# 题目信息

# Stoned Game

## 题目描述

T is playing a game with his friend, HL.

There are $ n $ piles of stones, the $ i $ -th pile initially has $ a_i $ stones.

T and HL will take alternating turns, with T going first. In each turn, a player chooses a non-empty pile and then removes a single stone from it. However, one cannot choose a pile that has been chosen in the previous turn (the pile that was chosen by the other player, or if the current turn is the first turn then the player can choose any non-empty pile). The player who cannot choose a pile in his turn loses, and the game ends.

Assuming both players play optimally, given the starting configuration of $ t $ games, determine the winner of each game.

## 说明/提示

In the first game, T removes a single stone from the only pile in his first turn. After that, although the pile still contains $ 1 $ stone, HL cannot choose from this pile because it has been chosen by T in the previous turn. Therefore, T is the winner.

## 样例 #1

### 输入

```
2
1
2
2
1 1```

### 输出

```
T
HL```

# AI分析结果

### 题目翻译
# 石子游戏

## 题目描述
T 正在和他的朋友 HL 玩一个游戏。

有 $n$ 堆石子，第 $i$ 堆最初有 $a_i$ 个石子。

T 和 HL 将轮流进行操作，T 先开始。在每一轮中，玩家选择一个非空的石子堆，然后从中移除一个石子。然而，玩家不能选择上一轮被选择过的石子堆（即另一个玩家上一轮选择的堆，如果当前是第一轮，则玩家可以选择任何非空的堆）。在自己的回合中无法选择堆的玩家输掉游戏，游戏结束。

假设两个玩家都采取最优策略，给定 $t$ 局游戏的初始配置，确定每局游戏的获胜者。

## 说明/提示
在第一局游戏中，T 在他的第一轮从唯一的一堆中移除了一个石子。在那之后，尽管这堆仍然有 1 个石子，但 HL 不能选择这堆，因为它已经被 T 在上一轮选择过了。因此，T 是获胜者。

## 样例 #1
### 输入
```
2
1
2
2
1 1
```
### 输出
```
T
HL
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕石子游戏的博弈策略展开。核心思路是根据石子堆的数量分布情况来判断胜负：若存在一堆石子数量超过其他堆的总和，先手一直取这堆必胜；否则，所有石子会被取完，通过判断总石子数的奇偶性确定胜负。

各题解思路基本一致，部分使用模拟的方法，通过优先队列维护当前可选的最大堆；部分则直接通过数学推理得出结论。模拟方法的时间复杂度较高，而数学推理的方法简洁高效。

### 所选题解
- **作者：SSerxhs（4星）**
    - **关键亮点**：对博弈结论给出了详细证明，逻辑清晰，代码简洁。
    - **重点代码**：
```cpp
#include <stdio.h>
int a[102];
int i,t,n,j,c;
int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=1;i<=n;i++) scanf("%d",a+i);j=1;
        for (i=2;i<=n;i++) if (a[i]>a[j]) j=i;c=0;
        for (i=1;i<=n;i++) if (i!=j) c+=a[i];
        if ((a[j]>c)||((c^a[j])&1)) puts("T"); else puts("HL");
    }
}
```
    - **核心实现思想**：先找出石子最多的堆，计算其他堆的石子总数，根据条件判断胜负。若最多堆的石子数大于其他堆的总和，先手必胜；否则，判断总石子数的奇偶性，奇数则先手胜，偶数则后手胜。

- **作者：钓鱼王子（4星）**
    - **关键亮点**：思路清晰，代码规范，对博弈过程分析准确。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
    re int t=0,f=0;re char v=getchar();
    while(v<'0')f|=(v=='-'),v=getchar();
    while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
    return f?-t:t; 
}
int n,a[1000002],t,ans;
signed main(){
    t=read();
    while(t--){
        n=read();
        for(re int i=1;i<=n;++i)a[i]=read();
        sort(a+1,a+n+1);
        re int sum=0;
        for(re int i=1;i<n;++i)sum+=a[i];
        if(sum<a[n])puts("T");
        else{
            sum+=a[n];
            if(sum&1)puts("T");
            else puts("HL");
        }
    }
}
```
    - **核心实现思想**：先读取输入，对石子堆按数量排序，计算除最大堆外的石子总数。若最大堆的石子数大于其他堆的总和，先手必胜；否则，判断总石子数的奇偶性确定胜负。

- **作者：灵茶山艾府（4星）**
    - **关键亮点**：思路清晰，使用 Golang 实现，代码简洁易懂。
    - **重点代码**：
```go
package main

import (
    "bufio"
    . "fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    var t, n, v int
    for Fscan(in, &t); t > 0; t-- {
        sum, max := 0, 0
        for Fscan(in, &n); n > 0; n-- {
            Fscan(in, &v)
            sum += v
            if v > max {
                max = v
            }
        }
        if max > sum-max || sum&1 > 0 {
            Println("T")
        } else {
            Println("HL")
        }
    }
}
```
    - **核心实现思想**：读取输入，计算总石子数和最大堆的石子数。若最大堆的石子数大于其他堆的总和，先手必胜；否则，判断总石子数的奇偶性确定胜负。

### 最优关键思路或技巧
- **数学推理**：通过分析博弈过程，得出关键结论，避免了复杂的模拟，提高了效率。
- **分类讨论**：根据石子堆的数量分布情况进行分类讨论，使问题简化。

### 可拓展之处
同类型的博弈论题目通常需要分析游戏规则，找出必胜或必败的条件。类似的算法套路包括通过数学推理、动态规划、搜索等方法来解决问题。

### 推荐题目
- [P1288 取数游戏 II](https://www.luogu.com.cn/problem/P1288)
- [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)
- [P3150 [CQOI2011] 放棋子](https://www.luogu.com.cn/problem/P3150)

### 个人心得摘录与总结
- **king_xbz**：尝试贪心策略失败后，通过暴力搜索和分析题解，理解了正确的博弈策略。总结是在遇到问题时，可以先尝试简单的策略，失败后再考虑其他方法，同时要深入分析问题的本质。
- **Star_Cried**：做这道题时是猜结论，没想到猜对了。提醒在做题时可以先大胆猜测，再进行严谨的证明。同时，要注意多组数据的清零问题。 

---
处理用时：47.08秒