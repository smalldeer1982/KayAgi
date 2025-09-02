# 题目信息

# Settlers' Training

## 题目描述

In a strategic computer game "Settlers II" one has to build defense structures to expand and protect the territory. Let's take one of these buildings. At the moment the defense structure accommodates exactly $ n $ soldiers. Within this task we can assume that the number of soldiers in the defense structure won't either increase or decrease.

Every soldier has a rank — some natural number from $ 1 $ to $ k $ . $ 1 $ stands for a private and $ k $ stands for a general. The higher the rank of the soldier is, the better he fights. Therefore, the player profits from having the soldiers of the highest possible rank.

To increase the ranks of soldiers they need to train. But the soldiers won't train for free, and each training session requires one golden coin. On each training session all the $ n $ soldiers are present.

At the end of each training session the soldiers' ranks increase as follows. First all the soldiers are divided into groups with the same rank, so that the least possible number of groups is formed. Then, within each of the groups where the soldiers below the rank $ k $ are present, exactly one soldier increases his rank by one.

You know the ranks of all $ n $ soldiers at the moment. Determine the number of golden coins that are needed to increase the ranks of all the soldiers to the rank $ k $ .

## 说明/提示

In the first example the ranks will be raised in the following manner:

1 2 2 3 $ → $ 2 2 3 4 $ → $ 2 3 4 4 $ → $ 3 4 4 4 $ → $ 4 4 4 4

Thus totals to 4 training sessions that require 4 golden coins.

## 样例 #1

### 输入

```
4 4
1 2 2 3
```

### 输出

```
4```

## 样例 #2

### 输入

```
4 3
1 1 1 1
```

### 输出

```
5```

# AI分析结果

### 题目翻译
在策略电脑游戏《 settlers II 》中，玩家必须建造防御工事来扩张和保护领土。让我们来看其中一个防御建筑。目前，该防御建筑中正好有 $n$ 名士兵。在这个问题中，我们可以假设防御建筑中的士兵数量不会增加也不会减少。

每名士兵都有一个等级，是从 $1$ 到 $k$ 的自然数。$1$ 代表列兵，$k$ 代表将军。士兵的等级越高，战斗力就越强。因此，玩家希望士兵的等级尽可能高。

为了提升士兵的等级，他们需要进行训练。但是士兵不会免费训练，每次训练需要一枚金币。每次训练时，所有 $n$ 名士兵都会参加。

每次训练结束后，士兵的等级提升规则如下。首先，将所有士兵按照相同等级分组，使得分组数量尽可能少。然后，在每个等级低于 $k$ 的士兵组中，恰好有一名士兵的等级提升一级。

你已知当前所有 $n$ 名士兵的等级。请确定将所有士兵的等级提升到 $k$ 所需的金币数量。

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟士兵等级提升的过程，直到所有士兵的等级都达到 $k$ 。具体做法是不断遍历数组，对满足“等级小于 $k$ 且不等于后一个士兵等级”的士兵进行等级提升，同时记录操作次数。

各题解的算法要点基本相同，都是通过循环模拟操作过程，利用数组存储士兵等级。解决的难点在于判断何时结束模拟，各题解都利用了数列非递减的性质，通过判断第一个士兵的等级是否达到 $k$ 来确定是否结束。

### 所选题解
- **良知的题解（4星）**
    - **关键亮点**：思路清晰，先给出暴力模拟思路，再进行优化，对优化点有详细解释。
    - **个人心得**：无
- **rui_er的题解（4星）**
    - **关键亮点**：对程序的正确性进行了证明，还提到了 C++ 中逗号语句的小技巧。
    - **个人心得**：无
- **EDqwq的题解（4星）**
    - **关键亮点**：指出了判断退出条件语句位置的坑点，这是其他题解未阐述的。
    - **个人心得**：判断是否符合条件的语句一定要放在循环开头，否则无法判断直接满足的数据。

### 重点代码
```cpp
// 以良知的题解为例
#include<cstdio>
using namespace std;
int a[105];
int main()
{
    int num, target;
    scanf("%d%d", &num, &target);
    for(int i=1; i<=num; ++i){
        scanf("%d", &a[i]);
    }
    int ans = 0;
    for(;;){
        for(int i=1; i<=num; ++i){
            if(a[i] == target && i == 1){printf("%d\n", ans);return 0;}
            else if(a[i] != a[i+1] && a[i] < target)++a[i];
        }
        ++ans;
    }
    return 0;
 } 
```
**核心实现思想**：通过两层循环模拟士兵等级提升过程，外层循环不断进行训练操作，内层循环遍历每个士兵，对满足条件的士兵进行等级提升。当第一个士兵的等级达到 $k$ 时，输出操作次数并结束程序。

### 扩展思路
同类型题或类似算法套路：这类模拟题通常需要根据题目给定的规则，一步步模拟操作过程，直到满足特定条件。在模拟过程中，要注意数据的变化和边界条件的处理。可以通过分析数据的性质来优化模拟过程，减少不必要的计算。

### 推荐题目
- P1003 铺地毯
- P1047 校门外的树
- P1048 采药

---
处理用时：23.03秒