# 题目信息

# JOE is on TV!

## 题目描述

[3R2 - Standby for Action](https://www.youtube.com/watch?v=P2ZVC9aoiKo)



Our dear Cafe's owner, JOE Miller, will soon take part in a new game TV-show "1 vs. $ n $ "!

The game goes in rounds, where in each round the host asks JOE and his opponents a common question. All participants failing to answer are eliminated. The show ends when only JOE remains (we assume that JOE never answers a question wrong!).

For each question JOE answers, if there are $ s $ ( $ s > 0 $ ) opponents remaining and $ t $ ( $ 0 \le t \le s $ ) of them make a mistake on it, JOE receives $ \displaystyle\frac{t}{s} $ dollars, and consequently there will be $ s - t $ opponents left for the next question.

JOE wonders what is the maximum possible reward he can receive in the best possible scenario. Yet he has little time before show starts, so can you help him answering it instead?

## 说明/提示

In the second example, the best scenario would be: one contestant fails at the first question, the other fails at the next one. The total reward will be $ \displaystyle \frac{1}{2} + \frac{1}{1} = 1.5 $ dollars.

## 样例 #1

### 输入

```
1```

### 输出

```
1.000000000000```

## 样例 #2

### 输入

```
2```

### 输出

```
1.500000000000```

# AI分析结果

### 题目内容重写

**JOE 上电视了！**

**题目描述**

我们亲爱的咖啡馆老板 JOE Miller 即将参加一个新的电视游戏节目“1 vs. $ n $”！

游戏进行多轮，每轮主持人向 JOE 和他的对手们提出一个共同的问题。所有未能回答的参与者将被淘汰。当只剩下 JOE 时，节目结束（我们假设 JOE 永远不会答错问题！）。

对于 JOE 回答的每个问题，如果还有 $ s $（$ s > 0 $）个对手剩余，并且其中有 $ t $（$ 0 \le t \le s $）个答错，JOE 将获得 $ \displaystyle\frac{t}{s} $ 美元，随后将有 $ s - t $ 个对手进入下一轮。

JOE 想知道在最佳情况下他能获得的最大奖励是多少。然而，节目即将开始，他没有太多时间，所以你能帮他回答这个问题吗？

**说明/提示**

在第二个示例中，最佳情况是：第一个问题淘汰一个对手，下一个问题淘汰另一个对手。总奖励将是 $ \displaystyle \frac{1}{2} + \frac{1}{1} = 1.5 $ 美元。

**样例 #1**

### 输入

```
1```

### 输出

```
1.000000000000```

**样例 #2**

### 输入

```
2```

### 输出

```
1.500000000000```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于通过贪心策略最大化 JOE 的收益。所有题解都指出，每次只淘汰一个对手是最优策略，因为这样可以最大化每轮的收益。最终答案是对 $1$ 到 $n$ 的倒数求和，即调和级数。

### 所选高分题解

#### 题解1：作者：ix35 (5星)
**关键亮点**：
- 提供了动态规划和贪心两种思路，最终选择贪心策略。
- 通过数学归纳法证明了每次只淘汰一个对手是最优策略。
- 代码简洁明了，易于理解。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double ans;
int main () {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {ans+=(double)1.0/(double)i;}
    printf("%lf\n",ans);
    return 0;
}
```

#### 题解2：作者：FZzzz (4星)
**关键亮点**：
- 使用数学归纳法详细证明了每次只淘汰一个对手是最优策略。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define re register
using namespace std;
int t,n,a,b,c;
double ans;
signed main(){
    scanf("%d",&n);
    for(re int i=1;i<=n;++i)ans+=(double)1/i;
    printf("%.10lf",ans);
}
```

#### 题解3：作者：Mr_Wu (4星)
**关键亮点**：
- 通过拆分 $\frac{t}{s}$ 为 $t$ 个 $\frac{1}{s}$ 相加，直观地展示了每次只淘汰一个对手的优势。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
n,i;double s;main(){scanf("%d",&n);for(i=1;i<=n;++i)s+=1.0/i;return printf("%.6lf\n",s),0;}
```

### 最优关键思路
每次只淘汰一个对手，使得每轮的收益最大化，最终答案为调和级数 $\sum_{i=1}^{n} \frac{1}{i}$。

### 可拓展之处
类似的问题可以通过贪心策略解决，尤其是在需要最大化收益或最小化成本的场景中。例如，任务调度、资源分配等问题。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：28.78秒