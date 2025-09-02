# 题目信息

# Rock, Paper, Scissors

## 题目描述

Alice and Bob have decided to play the game "Rock, Paper, Scissors".

The game consists of several rounds, each round is independent of each other. In each round, both players show one of the following things at the same time: rock, paper or scissors. If both players showed the same things then the round outcome is a draw. Otherwise, the following rules applied:

- if one player showed rock and the other one showed scissors, then the player who showed rock is considered the winner and the other one is considered the loser;
- if one player showed scissors and the other one showed paper, then the player who showed scissors is considered the winner and the other one is considered the loser;
- if one player showed paper and the other one showed rock, then the player who showed paper is considered the winner and the other one is considered the loser.

Alice and Bob decided to play exactly $ n $ rounds of the game described above. Alice decided to show rock $ a_1 $ times, show scissors $ a_2 $ times and show paper $ a_3 $ times. Bob decided to show rock $ b_1 $ times, show scissors $ b_2 $ times and show paper $ b_3 $ times. Though, both Alice and Bob did not choose the sequence in which they show things. It is guaranteed that $ a_1 + a_2 + a_3 = n $ and $ b_1 + b_2 + b_3 = n $ .

Your task is to find two numbers:

1. the minimum number of round Alice can win;
2. the maximum number of rounds Alice can win.

## 说明/提示

In the first example, Alice will not win any rounds if she shows scissors and then paper and Bob shows rock and then scissors. In the best outcome, Alice will win one round if she shows paper and then scissors, and Bob shows rock and then scissors.

In the second example, Alice will not win any rounds if Bob shows the same things as Alice each round.

In the third example, Alice always shows paper and Bob always shows rock so Alice will win all three rounds anyway.

## 样例 #1

### 输入

```
2
0 1 1
1 1 0```

### 输出

```
0 1```

## 样例 #2

### 输入

```
15
5 5 5
5 5 5```

### 输出

```
0 15```

## 样例 #3

### 输入

```
3
0 0 3
3 0 0```

### 输出

```
3 3```

## 样例 #4

### 输入

```
686
479 178 29
11 145 530```

### 输出

```
22 334```

## 样例 #5

### 输入

```
319
10 53 256
182 103 34```

### 输出

```
119 226```

# AI分析结果

### 题目内容（中文重写）
# 石头、剪刀、布

## 题目描述
爱丽丝（Alice）和鲍勃（Bob）决定玩“石头、剪刀、布”的游戏。

游戏由若干轮组成，每一轮相互独立。在每一轮中，两名玩家同时展示以下物品之一：石头、剪刀或布。如果两名玩家展示的物品相同，则该轮结果为平局。否则，适用以下规则：
- 如果一名玩家展示石头，另一名玩家展示剪刀，则展示石头的玩家被视为获胜者，另一名玩家被视为失败者；
- 如果一名玩家展示剪刀，另一名玩家展示布，则展示剪刀的玩家被视为获胜者，另一名玩家被视为失败者；
- 如果一名玩家展示布，另一名玩家展示石头，则展示布的玩家被视为获胜者，另一名玩家被视为失败者。

爱丽丝和鲍勃决定恰好玩 $n$ 轮上述游戏。爱丽丝决定展示石头 $a_1$ 次，展示剪刀 $a_2$ 次，展示布 $a_3$ 次。鲍勃决定展示石头 $b_1$ 次，展示剪刀 $b_2$ 次，展示布 $b_3$ 次。不过，爱丽丝和鲍勃都没有选择展示物品的顺序。保证 $a_1 + a_2 + a_3 = n$ 且 $b_1 + b_2 + b_3 = n$。

你的任务是找出两个数字：
1. 爱丽丝最少能赢的轮数；
2. 爱丽丝最多能赢的轮数。

## 说明/提示
在第一个样例中，如果爱丽丝先展示剪刀，然后展示布，而鲍勃先展示石头，然后展示剪刀，那么爱丽丝将不会赢得任何一轮。在最佳情况下，如果爱丽丝先展示布，然后展示剪刀，而鲍勃先展示石头，然后展示剪刀，那么爱丽丝将赢得一轮。

在第二个样例中，如果鲍勃每一轮都展示与爱丽丝相同的物品，那么爱丽丝将不会赢得任何一轮。

在第三个样例中，爱丽丝总是展示布，鲍勃总是展示石头，所以无论如何爱丽丝都将赢得所有三轮。

## 样例 #1
### 输入
```
2
0 1 1
1 1 0
```
### 输出
```
0 1
```

## 样例 #2
### 输入
```
15
5 5 5
5 5 5
```
### 输出
```
0 15
```

## 样例 #3
### 输入
```
3
0 0 3
3 0 0
```
### 输出
```
3 3
```

## 样例 #4
### 输入
```
686
479 178 29
11 145 530
```
### 输出
```
22 334
```

## 样例 #5
### 输入
```
319
10 53 256
182 103 34
```
### 输出
```
119 226
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何计算爱丽丝玩石头剪刀布游戏时最少和最多的赢的轮数。对于最多赢的轮数，大部分题解采用贪心策略，让爱丽丝能赢的情况尽量赢，即 $\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$ 。对于最少赢的轮数，不同题解采用了不同的方法，如贪心、网络流、枚举等。

### 所选题解
- AsunderSquall（4星）
    - 关键亮点：思路清晰，代码简洁，对最少赢的轮数的证明有一定思考。
    - 个人心得：考场上随便乱搞就整出来的题目，觉得其他题解把问题复杂化。
- 一扶苏一（4星）
    - 关键亮点：使用最小费用最大流解决最少赢的轮数问题，有完整的建图和代码实现。
    - 个人心得：作为退役很久的选手，不会分析结论和性质，用高级算法来凑。
- ZigZagKmp（4星）
    - 关键亮点：采用贪心和模拟的方法，通过枚举不同的操作顺序来求最少赢的轮数。
    - 个人心得：无

### 重点代码
#### AsunderSquall
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a1,a2,a3,b1,b2,b3;
signed main()
{
    cin>>n>>a1>>a2>>a3>>b1>>b2>>b3;
    cout<<n-min(a1,n-b2)-min(a2,n-b3)-min(a3,n-b1)<<" "<<min(a1,b2)+min(a2,b3)+min(a3,b1);
}
```
核心实现思想：对于最多赢的轮数，直接计算 $\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$ ；对于最少赢的轮数，通过 $n-\min(a_1,n-b_2)-\min(a_2,n-b_3)-\min(a3,n-b_1)$ 计算。

#### 一扶苏一
```cpp
// 建图部分
s = ++id; t = ++id;
cont(s, ++id, a, 0);
cont(s, ++id, b, 0);
cont(s, ++id, c, 0);
cont(++id, t, x, 0);
cont(++id, t, y, 0);
cont(++id, t, z, 0);
cont(3, 7, n, 1);
cont(4, 8, n, 1);
cont(5, 6, n, 1);
cont(3, 6, n, 0);
cont(3, 8, n, 0);
cont(4, 6, n, 0);
cont(4, 7, n, 0);
cont(5, 7, n, 0);
cont(5, 8, n, 0);
while (SPFA()) work();
```
核心实现思想：通过建图，将问题转化为最小费用最大流问题，源点向爱丽丝的三个点连边，鲍勃的三个点向汇点连边，爱丽丝向鲍勃的点连边并根据胜负情况设置费用，通过 SPFA 和 work 函数求解最小费用。

#### ZigZagKmp
```cpp
ans2=min(a[1],b[2])+min(a[2],b[3])+min(a[3],b[1]);
ans1=inf;
tmp[1]=make_pair(1,1);
tmp[2]=make_pair(1,3);
tmp[3]=make_pair(2,1);
tmp[4]=make_pair(2,2);
tmp[5]=make_pair(3,2);
tmp[6]=make_pair(3,3);
do{
    int sm=0;
    c[1]=a[1];c[2]=a[2];c[3]=a[3];
    d[1]=b[1];d[2]=b[2];d[3]=b[3];
    for(int i=1;i<=6;++i){
        int tt=min(c[tmp[i].first],d[tmp[i].second]);
        c[tmp[i].first]-=tt;d[tmp[i].second]-=tt;
    }
    sm=min(c[1],d[2])+min(c[2],d[3])+min(c[3],d[1]);
    ans1=min(ans1,sm);
}while(next_permutation(tmp+1,tmp+7));
```
核心实现思想：对于最多赢的轮数，直接计算 $\min(a_1,b_2)+\min(a_2,b_3)+\min(a_3,b_1)$ ；对于最少赢的轮数，通过枚举不同的操作顺序，每次操作后计算剩余的赢的轮数，取最小值。

### 关键思路或技巧
- 贪心策略：在求最多赢的轮数时，让能赢的情况尽量赢。
- 网络流：将最少赢的轮数问题转化为最小费用最大流问题。
- 枚举：通过枚举不同的操作顺序来求最少赢的轮数。

### 拓展思路
同类型题可以是其他博弈类游戏，如猜数字、取石子等，解题思路可能也会用到贪心、枚举等方法。类似算法套路可以是在处理博弈问题时，先分析必胜和必败的情况，再根据具体条件进行计算。

### 推荐题目
- P1288 取数游戏II
- P2197 【模板】nim 游戏
- P2964 [USACO09NOV]A Coin Game S

---
处理用时：53.90秒