# 题目信息

# Dark Assembly

## 题目描述

Dark Assembly is a governing body in the Netherworld. Here sit the senators who take the most important decisions for the player. For example, to expand the range of the shop or to improve certain characteristics of the character the Dark Assembly's approval is needed.

The Dark Assembly consists of $ n $ senators. Each of them is characterized by his level and loyalty to the player. The level is a positive integer which reflects a senator's strength. Loyalty is the probability of a positive decision in the voting, which is measured as a percentage with precision of up to $ 10% $ .

Senators make decisions by voting. Each of them makes a positive or negative decision in accordance with their loyalty. If strictly more than half of the senators take a positive decision, the player's proposal is approved.

If the player's proposal is not approved after the voting, then the player may appeal against the decision of the Dark Assembly. To do that, player needs to kill all the senators that voted against (there's nothing wrong in killing senators, they will resurrect later and will treat the player even worse). The probability that a player will be able to kill a certain group of senators is equal to $ A/(A+B) $ , where $ A $ is the sum of levels of all player's characters and $ B $ is the sum of levels of all senators in this group. If the player kills all undesired senators, then his proposal is approved.

Senators are very fond of sweets. They can be bribed by giving them candies. For each received candy a senator increases his loyalty to the player by $ 10% $ . It's worth to mention that loyalty cannot exceed $ 100% $ . The player can take no more than $ k $ sweets to the courtroom. Candies should be given to the senators before the start of voting.

Determine the probability that the Dark Assembly approves the player's proposal if the candies are distributed among the senators in the optimal way.

## 说明/提示

In the first sample the best way of candies' distribution is giving them to first three of the senators. It ensures most of votes.

It the second sample player should give all three candies to the fifth senator.

## 样例 #1

### 输入

```
5 6 100
11 80
14 90
23 70
80 30
153 70
```

### 输出

```
1.0000000000
```

## 样例 #2

### 输入

```
5 3 100
11 80
14 90
23 70
80 30
153 70
```

### 输出

```
0.9628442962
```

## 样例 #3

### 输入

```
1 3 20
20 20
```

### 输出

```
0.7500000000
```

# AI分析结果

### 题目内容
#### Dark Assembly
Dark Assembly是魔界的管理机构。这里坐着的参议员们为玩家做出最重要的决策。例如，要扩大商店的经营范围或提升角色的某些属性，都需要Dark Assembly的批准。

Dark Assembly由$n$名参议员组成。每位参议员都有其等级和对玩家的忠诚度。等级是一个正整数，反映了参议员的实力。忠诚度是投票中做出积极决策的概率，以百分比衡量，精确到$10\%$。

参议员们通过投票来做决策。他们每个人会根据自己的忠诚度做出积极或消极的决策。如果严格超过一半的参议员做出积极决策，玩家的提议就会被批准。

如果投票后玩家的提议未被批准，那么玩家可以对Dark Assembly的决定提出上诉。为此，玩家需要杀死所有投反对票的参议员（杀死参议员并没有什么问题，他们稍后会复活，而且会对玩家更不友好）。玩家能够杀死某一组参议员的概率等于$A/(A+B)$，其中$A$是玩家所有角色等级之和，$B$是这组参议员的等级之和。如果玩家杀死了所有不想要的参议员，那么他的提议就会被批准。

参议员们非常喜欢甜食。可以通过给他们糖果来贿赂他们。每收到一颗糖果，参议员对玩家的忠诚度就会提高$10\%$。值得一提的是，忠诚度不能超过$100\%$。玩家最多可以带$k$颗糖果到会议室。糖果应该在投票开始前分发给参议员。

确定如果以最优方式在参议员中分配糖果，Dark Assembly批准玩家提议的概率。

#### 说明/提示
在第一个样例中，分配糖果的最佳方式是将它们给前三位参议员。这能确保获得最多的选票。

在第二个样例中，玩家应该把三颗糖果都给第五位参议员。

#### 样例 #1
**输入**
```
5 6 100
11 80
14 90
23 70
80 30
153 70
```
**输出**
```
1.0000000000
```

#### 样例 #2
**输入**
```
5 3 100
11 80
14 90
23 70
80 30
153 70
```
**输出**
```
0.9628442962
```

#### 样例 #3
**输入**
```
1 3 20
20 20
```
**输出**
```
0.7500000000
```

### 算法分类
搜索（深度优先搜索 DFS）、概率论

### 题解综合分析与结论
这两道题解思路相似，均采用深度优先搜索（DFS）来解决问题，主要围绕分糖和计算提案通过概率两个核心部分。
1. **分糖部分**：通过DFS暴力枚举所有可能的分糖方式，确保在给定$k$颗糖的情况下，尝试所有给参议员分糖的组合。
2. **计算概率部分**：同样利用DFS枚举每个参议员投票的赞成或反对情况，根据赞成人数与总人数一半的关系，结合不同情况下的概率计算规则得出提案通过的概率。对于不足一半赞成的情况，还需考虑杀死反对者的成功概率。

不同点在于剪枝策略。题解1通过优化分糖时的枚举顺序，避免重复计算分糖情况，降低了时间复杂度，但未精确计算优化后的复杂度；题解2未提及类似剪枝策略。

### 所选的题解
- **题解1（vеctorwyx）**：
  - **星级**：4星
  - **关键亮点**：采用两次DFS，一次用于分糖并通过剪枝优化分糖枚举顺序，避免重复计算；另一次用于计算每种分糖情况下提案通过的概率。代码结构清晰，对时间复杂度优化有思考。
  - **个人心得**：作者提到代码只能在CF上C++17通过，在洛谷因无C++17选型无法通过，虽不知具体原因，但反映出不同平台对代码兼容性的差异。
  - **核心代码片段**：
```cpp
void dfs(int x,int dat,int cnt,int b){
    if(x == n + 1){
        if(cnt > n / 2)
        ans += dat * 1.0;
        else
        ans += dat * k * 1.0 / (k + b);
        return;
    }
    dfs(x + 1, dat * e[x] / 10, cnt + 1, b);
    dfs(x + 1, dat * (100 - e[x]) / 10, cnt, b + a[x]);
}
void dfs1(int x, int pre){
    if(x > m){
        ans = 0;
        dfs(1, 1, 0, 0);
        ans1 = max( ans1, ans /(pow(10, n)) );
        return;
    }
    for(int i = pre; i <= n ; i++){
        if(e[i] == 100)
            continue;
        e[i] += 10;
        dfs1(x + 1, i);
        e[i] -= 10;
    }
}
```
  - **核心实现思想**：`dfs`函数用于计算在当前分糖情况下，所有参议员投票后提案通过的概率。`dfs1`函数用于分糖，通过控制`pre`参数确保分糖不重复，每次分糖后调用`dfs`计算概率，并更新最大概率`ans1`。

- **题解2（lemondinosaur）**：
  - **星级**：3星
  - **关键亮点**：思路直接清晰，通过DFS分别实现分糖和计算概率的过程，但未进行如题解1中对分糖枚举的剪枝优化。
  - **核心代码片段**：
```cpp
inline void ev(int dep,int cnt,double pro,int deny,double &sum){
    if (!pro) return;
    if (dep==n){
        if (cnt>=mid) sum+=pro;
        else sum+=pro*A/(A+deny);
        return;
    }
    ev(dep+1,cnt+1,pro*a[dep+1]/10.0,deny,sum);
    ev(dep+1,cnt,pro-pro*a[dep+1]/10.0,deny+b[dep+1],sum);
}
inline void dfs(int dep,int swe){
    rr double sum=0;
    ev(0,0,1,0,sum);
    ans=ans>sum?ans:sum;
    if (dep==n||!swe) return;
    for (rr int i=0;i<=swe;++i)
    if (a[dep+1]+i<=10)
        a[dep+1]+=i,dfs(dep+1,swe-i),a[dep+1]-=i;
}
```
  - **核心实现思想**：`ev`函数用于计算在当前投票情况（由`dep`表示当前参议员，`cnt`表示赞成人数，`pro`表示当前概率，`deny`表示反对者等级和）下提案通过的概率。`dfs`函数用于分糖，每次分糖后调用`ev`计算概率，并更新最大概率`ans`。

### 最优关键思路或技巧
1. **剪枝优化**：在分糖的DFS枚举过程中，通过控制枚举顺序，确保每种分糖情况只计算一次，有效降低时间复杂度。
2. **分步骤DFS**：将分糖和计算概率两个过程分别用DFS实现，使代码逻辑清晰，易于理解和实现。

### 可拓展之处
同类型题通常围绕概率计算与条件枚举展开，类似算法套路为利用搜索算法（如DFS）枚举所有可能情况，并结合题目给定的概率规则计算目标概率。在遇到此类问题时，关键在于分析每种情况的概率计算方式以及如何优化枚举过程，避免不必要的计算。

### 洛谷相似题目推荐
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的DFS搜索问题，通过枚举皇后位置解决问题，与本题在搜索思路上有相似之处。
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：通过DFS枚举组合情况，与本题分糖的枚举思路类似，可锻炼搜索枚举能力。
3. [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)：涉及到矩阵运算与递推思想，与本题结合概率计算递推结果有一定相似性，可拓展对递推与计算的理解。 

---
处理用时：79.75秒