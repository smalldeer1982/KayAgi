# 题目信息

# Predict Outcome of the Game

## 题目描述

There are $ n $ games in a football tournament. Three teams are participating in it. Currently $ k $ games had already been played.

You are an avid football fan, but recently you missed the whole $ k $ games. Fortunately, you remember a guess of your friend for these $ k $ games. Your friend did not tell exact number of wins of each team, instead he thought that absolute difference between number of wins of first and second team will be $ d_{1} $ and that of between second and third team will be $ d_{2} $ .

You don't want any of team win the tournament, that is each team should have the same number of wins after $ n $ games. That's why you want to know: does there exist a valid tournament satisfying the friend's guess such that no team will win this tournament?

Note that outcome of a match can not be a draw, it has to be either win or loss.

## 说明/提示

Sample 1. There has not been any match up to now $ (k=0,d_{1}=0,d_{2}=0) $ . If there will be three matches (1-2, 2-3, 3-1) and each team wins once, then at the end each team will have 1 win.

Sample 2. You missed all the games $ (k=3) $ . As $ d_{1}=0 $ and $ d_{2}=0 $ , and there is a way to play three games with no winner of tournament (described in the previous sample), the answer is "yes".

Sample 3. You missed 4 matches, and $ d_{1}=1,d_{2}=0 $ . These four matches can be: 1-2 (win 2), 1-3 (win 3), 1-2 (win 1), 1-3 (win 1). Currently the first team has 2 wins, the second team has 1 win, the third team has 1 win. Two remaining matches can be: 1-2 (win 2), 1-3 (win 3). In the end all the teams have equal number of wins (2 wins).

## 样例 #1

### 输入

```
5
3 0 0 0
3 3 0 0
6 4 1 0
6 3 3 0
3 3 3 2
```

### 输出

```
yes
yes
yes
no
no
```

# AI分析结果

### 题目内容
# 预测比赛结果

## 题目描述
在一场足球锦标赛中有 $n$ 场比赛，三支球队参赛。目前已经进行了 $k$ 场比赛。

你是一位狂热的足球迷，但最近你错过了全部 $k$ 场比赛。幸运的是，你记得你朋友对这 $k$ 场比赛的猜测。你朋友没有告诉你每支球队确切的获胜场次，而是认为第一支球队和第二支球队获胜场次的绝对差值为 $d_1$，第二支球队和第三支球队获胜场次的绝对差值为 $d_2$。

你不希望任何一支球队赢得锦标赛，也就是说在 $n$ 场比赛结束后，每支球队的获胜场次应该相同。所以你想知道：是否存在一种符合你朋友猜测的有效锦标赛情况，使得没有球队赢得锦标赛？

注意，一场比赛的结果不能是平局，必须是一方获胜另一方失败。

## 说明/提示
示例 1. 到目前为止还没有进行任何比赛（$k = 0$, $d_1 = 0$, $d_2 = 0$）。如果将进行三场比赛（1 - 2，2 - 3，3 - 1）且每支球队各胜一场，那么最终每支球队都将有 1 场胜利。

示例 2. 你错过了所有比赛（$k = 3$）。由于 $d_1 = 0$ 且 $d_2 = 0$，并且有一种比赛方式可以使锦标赛没有获胜者（如前一个示例所述），答案为“是”。

示例 3. 你错过了 4 场比赛，且 $d_1 = 1$, $d_2 = 0$。这四场比赛可以是：1 - 2（2 胜），1 - 3（3 胜），1 - 2（1 胜），1 - 3（1 胜）。目前第一支球队有 2 场胜利，第二支球队有 1 场胜利，第三支球队有 1 场胜利。剩下的两场比赛可以是：1 - 2（2 胜），1 - 3（3 胜）。最终所有球队的获胜场次相等（2 场胜利）。

## 样例 #1
### 输入
```
5
3 0 0 0
3 3 0 0
6 4 1 0
6 3 3 0
3 3 3 2
```
### 输出
```
yes
yes
yes
no
no
```

### 算法分类
数学

### 题解综合分析与结论
两道题解思路基本一致，都基于数学分析。要点在于先明确 $n$ 需是 3 的倍数，然后通过枚举 $d_1$ 和 $d_2$ 的正负情况来列出三支球队可能的胜场数组合，再依据已比赛场数 $k$ 和最终各队胜场需相等（为 $\frac{n}{3}$）的条件进行合法性检查。解决难点在于合理处理绝对值，通过枚举正负情况全面考虑所有可能的比赛结果。

### 所选的题解
 - **ZLCT题解**：★★★
    - **关键亮点**：思路清晰，先分析出 $n$ 需为 3 的倍数这一必要条件，再详细枚举 $d_1$ 和 $d_2$ 的正负组合，代码实现简洁明了，将检查合法性封装为 `check` 函数，逻辑清晰。
 - **_Kimi_题解**：★★★
    - **关键亮点**：同样准确把握核心思路，枚举四种可能的胜场数组合，代码结构清晰，与ZLCT题解类似，对合法性检查的逻辑也较为清晰。

### 重点代码及核心实现思想
以ZLCT题解为例，核心代码如下：
```cpp
bool check(int x,int y){
    int z=k-x-y;
    if(z%3)return 0;
    z/=3;
    if(z<0||z+x<0||z+y<0)return 0;
    if(z<=n&&z+x<=n&&z+y<=n)return 1;
    return 0;
}
void solve(){
    cin>>n>>k>>d1>>d2;
    if(n%3){
        cout<<"no\n";
        return;
    }
    n/=3;
    if(check(d1,d1+d2)|check(d1,d1-d2)|check(-d1,-d1+d2)|check(-d1,-d1-d2)){
        cout<<"yes\n";
    }else{
        cout<<"no\n";
    }
    return;
}
```
核心实现思想：`check` 函数用于检查在给定的胜场差值组合下，是否能通过剩余比赛让各队胜场相等。先根据已比赛场数 $k$ 和当前胜场差值组合算出第三队的胜场数 $z$，判断 $z$ 是否能被 3 整除，若能则计算平均每场需增加的胜场数，再检查各队胜场数是否在合法范围（$[0, \frac{n}{3}]$）内。`solve` 函数先判断 $n$ 是否为 3 的倍数，再枚举 $d_1$ 和 $d_2$ 的正负组合调用 `check` 函数判断是否存在合法情况。

### 最优关键思路或技巧
通过数学分析明确必要条件（$n$ 是 3 的倍数），巧妙利用枚举绝对值的正负情况来全面考虑所有可能的比赛结果，将复杂的逻辑简化为对几种固定组合的合法性检查。

### 拓展思路
此类题目属于基于数学条件判断可能性的问题，类似套路为根据给定的条件进行数学推导，确定关键的限制条件，再通过枚举、假设等方法去验证是否存在符合要求的情况。同类型题可考虑其他体育比赛结果预测问题，例如不同队伍之间积分关系，最终判断是否能达成某种特定排名等。

### 洛谷相似题目推荐
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)
 - [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)

---
处理用时：46.49秒