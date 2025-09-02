# 题目信息

# Combination

## 题目描述

Ilya plays a card game by the following rules.

A player has several cards. Each card contains two non-negative integers inscribed, one at the top of the card and one at the bottom. At the beginning of the round the player chooses one of his cards to play it. If the top of the card contains number $ a_{i} $ , and the bottom contains number $ b_{i} $ , then when the player is playing the card, he gets $ a_{i} $ points and also gets the opportunity to play additional $ b_{i} $ cards. After the playing the card is discarded.

More formally: let's say that there is a counter of the cards that can be played. At the beginning of the round the counter equals one. When a card is played, the counter decreases by one for the played card and increases by the number $ b_{i} $ , which is written at the bottom of the card. Then the played card is discarded. If after that the counter is not equal to zero, the player gets the opportunity to play another card from the remaining cards. The round ends when the counter reaches zero or the player runs out of cards.

Of course, Ilya wants to get as many points as possible. Can you determine the maximum number of points he can score provided that you know his cards?

## 说明/提示

In the first sample none of two cards brings extra moves, so you should play the one that will bring more points.

In the second sample you should first play the third card that doesn't bring any points but lets you play both remaining cards.

## 样例 #1

### 输入

```
2
1 0
2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 0
2 0
0 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 组合

## 题目描述
伊利亚按照以下规则玩纸牌游戏。

玩家有若干张纸牌。每张纸牌上写有两个非负整数，一个在纸牌顶部，一个在纸牌底部。在一轮游戏开始时，玩家选择其中一张纸牌打出。如果纸牌顶部的数字为\(a_{i}\)，底部的数字为\(b_{i}\)，那么玩家打出这张纸牌时，会得到\(a_{i}\)分，并且还获得额外打出\(b_{i}\)张纸牌的机会。打出纸牌后，该纸牌将被丢弃。

更正式地说：假设有一个可打出纸牌的计数器。在一轮游戏开始时，计数器等于\(1\)。当打出一张纸牌时，计数器会因为打出的这张纸牌而减\(1\)，并因为纸牌底部的数字\(b_{i}\)而增加。然后，打出的纸牌被丢弃。如果在此之后计数器不为零，玩家就有机会从剩余的纸牌中再打出一张。当计数器达到零或者玩家没有纸牌时，这一轮游戏结束。

当然，伊利亚希望获得尽可能多的分数。已知他的纸牌，你能确定他最多能得到多少分吗？

## 说明/提示
在第一个样例中，两张纸牌都不会带来额外的出牌机会，所以你应该打出能带来更多分数的那张牌。

在第二个样例中，你应该先打出第三张牌，它不会带来分数，但能让你打出剩下的两张牌。

## 样例 #1
### 输入
```
2
1 0
2 0
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
1 0
2 0
0 2
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
所有题解均采用贪心算法，核心思路是优先选择能增加更多出牌机会（即\(b\)值更大）的纸牌，若\(b\)值相同，则优先选择得分更高（即\(a\)值更大）的纸牌。通过对纸牌按此规则排序，再模拟出牌过程来计算最大得分。各题解的主要区别在于实现方式，有的使用`qsort`，有的使用`sort`，还有的使用优先队列`priority_queue`，但本质思路一致。

### 所选的题解
- **作者：翟翟 (5星)**
    - **关键亮点**：思路清晰，不仅给出代码，还对排序依据进行详细分析，通过`qsort`函数实现排序，代码简洁明了。
    - **重点代码**：
```c
int cmp(const void*x,const void*y){
    node f1=*(node*)x,f2=*(node*)y;
    return f1.b^f2.b?f1.b<f2.b:f1.a<f2.a;
}
```
核心实现思想：此为`qsort`的比较函数，当\(b\)值不同时，按\(b\)值从小到大排序；当\(b\)值相同时，按\(a\)值从小到大排序。
- **作者：开始新的记忆 (5星)**
    - **关键亮点**：代码简洁，利用`sort`函数实现排序，`cmp`函数逻辑清晰，直接明了地体现贪心策略。
    - **重点代码**：
```cpp
bool cmp(node x,node y)
{
    if(x.num==y.num)
        return x.point>y.point;
    return x.num>y.num;
}
```
核心实现思想：`cmp`函数定义排序规则，先按能多抽牌的数量（`num`）从大到小排序，若`num`相同则按值（`point`）从大到小排序。
- **作者：cqbztz2 (4星)**
    - **关键亮点**：通过重载`<`运算符实现排序，代码风格简洁，在排序和模拟出牌过程中逻辑严谨。
    - **重点代码**：
```cpp
struct node{
    int x,y;
    friend bool operator<(node x,node y){
        if(x.y==y.y){
            return x.x>y.x;
        }
        return x.y>y.y;
    }
}a[N];
```
核心实现思想：定义结构体`node`并重载`<`运算符，实现按`y`（能获得的出牌次数）从大到小排序，若`y`相同则按`x`（得分）从大到小排序。

### 最优关键思路或技巧
利用贪心策略，根据纸牌能增加的出牌机会和得分对纸牌进行排序，从而确保在每一步选择中都能使最终得分最大化。在实现上，合理利用排序函数（如`qsort`、`sort`）或优先队列来简化代码并提高效率。

### 同类型题或类似算法套路拓展
此类题目通常涉及在一系列选择中，通过某种规则的排序，优先选择对结果最有利的元素，以达到最优解。常见于资源分配、任务调度等场景的题目中。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：34.09秒