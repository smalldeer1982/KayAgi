# 题目信息

# Powering the Hero (easy version)

## 题目描述

This is an easy version of the problem. It differs from the hard one only by constraints on $ n $ and $ t $ .

There is a deck of $ n $ cards, each of which is characterized by its power. There are two types of cards:

- a hero card, the power of such a card is always equal to $ 0 $ ;
- a bonus card, the power of such a card is always positive.

You can do the following with the deck:

- take a card from the top of the deck;
- if this card is a bonus card, you can put it on top of your bonus deck or discard;
- if this card is a hero card, then the power of the top card from your bonus deck is added to his power (if it is not empty), after that the hero is added to your army, and the used bonus discards.

Your task is to use such actions to gather an army with the maximum possible total power.

## 说明/提示

In the first sample, you can take bonuses $ 1 $ and $ 2 $ . Both hero cards will receive $ 3 $ power. If you take all the bonuses, one of them will remain unused.

In the second sample, the hero's card on top of the deck cannot be powered up, and the rest can be powered up with $ 2 $ and $ 3 $ bonuses and get $ 6 $ total power.

In the fourth sample, you can take bonuses $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ and skip the bonus $ 6 $ , then the hero $ 4 $ will be enhanced with a bonus $ 3 $ by $ 5 $ , and the hero $ 7 $ with a bonus $ 5 $ by $ 4 $ . $ 4+5=9 $ .

## 样例 #1

### 输入

```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4```

### 输出

```
6
6
8
9
4```

# AI分析结果

### 题目内容
# 助力英雄（简单版）

## 题目描述
这是该问题的简单版本。它与困难版本仅在 $n$ 和 $t$ 的约束条件上有所不同。

有一副包含 $n$ 张牌的牌堆，每张牌都有其对应的力量值。牌分为两种类型：
 - 英雄牌，此类牌的力量值始终为 $0$；
 - 奖励牌，此类牌的力量值始终为正数。

你可以对牌堆执行以下操作：
 - 从牌堆顶部抽取一张牌；
 - 如果这张牌是奖励牌，你可以将其放置在你的奖励牌堆顶部或丢弃；
 - 如果这张牌是英雄牌，那么你的奖励牌堆顶部牌的力量值将加到该英雄牌上（前提是奖励牌堆不为空），之后该英雄牌加入你的军队，并且所使用的奖励牌被丢弃。

你的任务是通过这些操作组建一支具有最大总力量值的军队。

## 说明/提示
在第一个样例中，你可以选取奖励牌 $1$ 和 $2$ 。两张英雄牌都将获得 $3$ 点力量值。如果选取所有奖励牌，其中一张将不会被使用。

在第二个样例中，牌堆顶部的英雄牌无法获得力量增强，其余英雄牌可以通过奖励牌 $2$ 和 $3$ 获得增强，总力量值为 $6$ 。

在第四个样例中，你可以选取奖励牌 $1$ 、 $2$ 、 $3$ 、 $5$ 并跳过奖励牌 $6$ ，然后英雄牌 $4$ 将通过奖励牌 $3$ 增强 $5$ 点力量，英雄牌 $7$ 将通过奖励牌 $5$ 增强 $4$ 点力量。 $4 + 5 = 9$ 。

## 样例 #1
### 输入
```
5
5
3 3 3 0 0
6
0 3 3 0 0 3
7
1 2 3 0 4 5 0
7
1 2 5 0 4 3 0
5
3 1 0 0 4
```
### 输出
```
6
6
8
9
4
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，即每次遇到英雄牌时，都选择当前可获得的最大力量值的奖励牌来增强它。不同题解在实现方式上有所差异，部分使用暴力枚举寻找最大值，时间复杂度为 $O(n^2)$，能通过简单版本；多数题解使用优先队列（大根堆）来维护当前奖励牌中的最大值，时间复杂度优化到 $O(n \log n)$，既可以通过简单版本也能应对可能的困难版本。在思路清晰度、代码可读性和优化程度等方面，使用优先队列的题解整体表现更好。

### 所选的题解
 - **作者：szhqwq（4星）**
    - **关键亮点**：简洁阐述使用优先队列（大根堆）解决问题的思路，指出优先队列自动排序可避免考虑丢弃牌及寻找最大值的问题。
    - **个人心得**：赛时受该题困扰，后发现可用优先队列解决，强调做题思维要开阔。
 - **作者：Jasoncwx（4星）**
    - **关键亮点**：先对题目进行详细翻译，再给出清晰的解题思路，并结合代码注释解释模拟优先队列的操作过程，代码可读性强。
 - **作者：Larryyu（4星）**
    - **关键亮点**：不仅给出解题思路和代码，还对贪心策略的正确性进行深入分析，通过具体例子说明取当前加分牌堆最大值的合理性，时间复杂度分析清晰。

### 重点代码及核心实现思想
以Jasoncwx的代码为例，核心代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,ans=0,t;
        cin>>n;
        priority_queue<ll> q;
        while(n--){
          cin>>t;
          if(q.size()!=0&&t==0){//英雄卡
              ans+=q.top();//添加能量
              q.pop();//丢弃卡片
          } 
          else if(t>0)q.push(t);//奖励卡
    	}
    	printf("%lld\n",ans);//结果
	}
    return 0;
}
```
核心实现思想为：利用优先队列 `q` 来维护奖励牌的力量值，每次读取一张牌，如果是奖励牌（`t > 0`）则将其加入优先队列；如果是英雄牌（`t == 0`）且优先队列不为空，就取出队头元素（即当前最大力量值的奖励牌）加到答案 `ans` 中，并将该奖励牌从队列中移除。

### 最优关键思路或技巧
使用优先队列（大根堆）这一数据结构来优化贪心算法的实现。优先队列能够自动对元素进行排序，使得每次获取当前最大力量值的奖励牌操作时间复杂度从暴力查找的 $O(n)$ 降低到 $O(1)$，整体时间复杂度优化为 $O(n \log n)$。

### 拓展思路
此类题目属于贪心策略在序列操作上的应用，类似题目通常涉及对一系列元素进行选择或操作，通过合理的贪心策略使得某个目标值达到最优。常见的套路是分析每个操作步骤对最终结果的影响，找到一种局部最优的选择方式，并证明这种局部最优能导致全局最优。

### 洛谷相似题目推荐
 - **P1090 [NOIP2004 提高组] 合并果子**：通过贪心策略每次选择最小的两个果子堆合并，以达到最小的总代价，与本题类似在于都是对序列元素进行操作并通过贪心求最优值。
 - **P1199 [NOIP2010 普及组] 三国游戏**：在选择武将的过程中运用贪心策略，根据一定规则选择最优武将组合，和本题一样需要分析操作步骤来确定贪心策略。
 - **P2859 [USACO06DEC]Milk Patterns G**：通过对牛奶模式的分析，利用贪心思想解决问题，同样是在特定规则下通过合理选择达到最优结果。 

---
处理用时：44.84秒