# 题目信息

# Ping-pong

## 题目描述

Alice and Bob play ping-pong with simplified rules.

During the game, the player serving the ball commences a play. The server strikes the ball then the receiver makes a return by hitting the ball back. Thereafter, the server and receiver must alternately make a return until one of them doesn't make a return.

The one who doesn't make a return loses this play. The winner of the play commences the next play. Alice starts the first play.

Alice has $ x $ stamina and Bob has $ y $ . To hit the ball (while serving or returning) each player spends $ 1 $ stamina, so if they don't have any stamina, they can't return the ball (and lose the play) or can't serve the ball (in this case, the other player serves the ball instead). If both players run out of stamina, the game is over.

Sometimes, it's strategically optimal not to return the ball, lose the current play, but save the stamina. On the contrary, when the server commences a play, they have to hit the ball, if they have some stamina left.

Both Alice and Bob play optimally and want to, firstly, maximize their number of wins and, secondly, minimize the number of wins of their opponent.

Calculate the resulting number of Alice's and Bob's wins.

## 说明/提示

In the first test case, Alice serves the ball and spends $ 1 $ stamina. Then Bob returns the ball and also spends $ 1 $ stamina. Alice can't return the ball since she has no stamina left and loses the play. Both of them ran out of stamina, so the game is over with $ 0 $ Alice's wins and $ 1 $ Bob's wins.

In the second test case, Alice serves the ball and spends $ 1 $ stamina. Bob decides not to return the ball — he loses the play but saves stamina. Alice, as the winner of the last play, serves the ball in the next play and spends $ 1 $ more stamina. This time, Bob returns the ball and spends $ 1 $ stamina. Alice doesn't have any stamina left, so she can't return the ball and loses the play. Both of them ran out of stamina, so the game is over with $ 1 $ Alice's and $ 1 $ Bob's win.

In the third test case, Alice serves the ball and spends $ 1 $ stamina. Bob returns the ball and spends $ 1 $ stamina. Alice ran out of stamina, so she can't return the ball and loses the play. Bob, as a winner, serves the ball in the next $ 6 $ plays. Each time Alice can't return the ball and loses each play. The game is over with $ 0 $ Alice's and $ 7 $ Bob's wins.

## 样例 #1

### 输入

```
3
1 1
2 1
1 7```

### 输出

```
0 1
1 1
0 7```

# AI分析结果

### 题目内容
# 乒乓球游戏

## 题目描述
爱丽丝（Alice）和鲍勃（Bob）以简化规则进行乒乓球游戏。

在游戏过程中，发球的玩家开启一轮比赛。发球者击球后，接球者将球回击。此后，发球者和接球者必须交替回击，直到其中一方无法回击。

无法回击的一方输掉这一轮比赛。赢得这一轮比赛的玩家开启下一轮比赛。爱丽丝开始第一轮比赛。

爱丽丝有 $x$ 点耐力，鲍勃有 $y$ 点耐力。每次击球（无论是发球还是回击），每位玩家都会消耗 $1$ 点耐力，所以如果他们没有耐力了，就无法回击（从而输掉这一轮比赛），或者无法发球（在这种情况下，由另一方发球）。如果双方都耗尽了耐力，游戏结束。

有时，从策略上考虑，不回击而输掉当前这一轮比赛，但节省耐力是最优选择。相反，当发球者开启一轮比赛时，如果他们还有耐力，就必须击球。

爱丽丝和鲍勃都采取最优策略进行游戏，首先，他们希望最大化自己的获胜次数，其次，最小化对手的获胜次数。

计算爱丽丝和鲍勃最终的获胜次数。

## 说明/提示
在第一个测试用例中，爱丽丝发球并消耗 $1$ 点耐力。然后鲍勃回击并同样消耗 $1$ 点耐力。爱丽丝由于没有耐力而无法回击，输掉这一轮比赛。双方都耗尽了耐力，所以游戏结束，爱丽丝获胜次数为 $0$，鲍勃获胜次数为 $1$。

在第二个测试用例中，爱丽丝发球并消耗 $1$ 点耐力。鲍勃决定不回击——他输掉这一轮比赛，但节省了耐力。爱丽丝作为上一轮比赛的获胜者，在下一轮比赛中发球并再消耗 $1$ 点耐力。这次，鲍勃回击并消耗 $1$ 点耐力。爱丽丝没有耐力了，所以她无法回击并输掉这一轮比赛。双方都耗尽了耐力，所以游戏结束，爱丽丝获胜次数为 $1$，鲍勃获胜次数为 $1$。

在第三个测试用例中，爱丽丝发球并消耗 $1$ 点耐力。鲍勃回击并消耗 $1$ 点耐力。爱丽丝耗尽了耐力，所以她无法回击并输掉这一轮比赛。鲍勃作为获胜者，在接下来的 $6$ 轮比赛中发球。每次爱丽丝都无法回击并输掉每一轮比赛。游戏结束，爱丽丝获胜次数为 $0$，鲍勃获胜次数为 $7$。

## 样例 #1
### 输入
```
3
1 1
2 1
1 7
```
### 输出
```
0 1
1 1
0 7
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是通过分析双方的最优策略来得出获胜次数的计算公式。难点在于理解双方如何在最大化自身获胜次数和最小化对方获胜次数之间做出决策。各题解都指出，由于爱丽丝先发球，当她只剩1点耐力时，发出球后就无法回击，所以最多能赢 $x - 1$ 次；而鲍勃可以在爱丽丝耐力耗尽后，凭借剩余耐力赢 $y$ 次。不同题解在表述方式和推导过程的详细程度上有所差异，但最终结论一致。

### 所选的题解
- **作者：Thomas_Cat (5星)**
  - **关键亮点**：通过分情况讨论发球员和接球员的策略，清晰地推导出获胜次数的计算方式，逻辑严谨。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
        cout<<a-1<<' '<<b<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：读入测试用例数量t，对每个测试用例读入爱丽丝和鲍勃的耐力a和b，直接按推导公式输出爱丽丝获胜次数a - 1和鲍勃获胜次数b。
- **作者：Tenshi (4星)**
  - **关键亮点**：通过具体模拟案例，如a = 100, b = 3的情况，直观地展示策略并推导出公式，易于理解。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main(){
    cin>>T;
    while(T--){
        int a,b; cin>>a>>b;
        cout<<a-1<<' '<<b<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：与Thomas_Cat的代码类似，读入测试用例数T，对每个测试用例读入a和b，按推导公式输出结果。
- **作者：wmy_goes_to_thu (4星)**
  - **关键亮点**：提出用动态规划的思路，设 $f_{i,j}$ 代表特定情况下的最好代价，虽然没有详细展开动态规划的转移过程，但最终推导出与其他题解一致的结果，提供了不同的思考方向。
  - **重点代码**：无具体关键代码，仅概念性描述转移方程和最终结果。

### 最优关键思路或技巧
理解双方玩家的最优策略，即鲍勃会在爱丽丝耐力耗尽前不回击以节省耐力，从而在爱丽丝只剩1点耐力回击后，凭借自身耐力赢下后续比赛。这种对博弈策略的分析是解决本题的关键。

### 拓展
同类型题可关注两人博弈且涉及资源消耗与策略选择的题目。类似算法套路是通过模拟或推理，分析双方在不同情况下的最优决策，进而得出结果。

### 推荐洛谷题目
- P1288 取数游戏II，涉及两人博弈，通过分析策略确定最优解。
- P1080 国王游戏，同样是两人博弈场景，需推导最优策略来求解。
- P2197 模板，博弈论相关，通过对局势和策略的分析解决问题。 

---
处理用时：61.01秒