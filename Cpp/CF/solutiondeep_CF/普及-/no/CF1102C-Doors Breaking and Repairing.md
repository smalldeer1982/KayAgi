# 题目信息

# Doors Breaking and Repairing

## 题目描述

You are policeman and you are playing a game with Slavik. The game is turn-based and each turn consists of two phases. During the first phase you make your move and during the second phase Slavik makes his move.

There are $ n $ doors, the $ i $ -th door initially has durability equal to $ a_i $ .

During your move you can try to break one of the doors. If you choose door $ i $ and its current durability is $ b_i $ then you reduce its durability to $ max(0, b_i - x) $ (the value $ x $ is given).

During Slavik's move he tries to repair one of the doors. If he chooses door $ i $ and its current durability is $ b_i $ then he increases its durability to $ b_i + y $ (the value $ y $ is given). Slavik cannot repair doors with current durability equal to $ 0 $ .

The game lasts $ 10^{100} $ turns. If some player cannot make his move then he has to skip it.

Your goal is to maximize the number of doors with durability equal to $ 0 $ at the end of the game. You can assume that Slavik wants to minimize the number of such doors. What is the number of such doors in the end if you both play optimally?

## 说明/提示

Clarifications about the optimal strategy will be ignored.

## 样例 #1

### 输入

```
6 3 2
2 3 1 3 4 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 3 3
1 2 4 2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 5 6
1 2 6 10 3
```

### 输出

```
2
```

# AI分析结果



# Doors Breaking and Repairing

## 题目描述

你扮演警察，与Slavik进行回合制游戏。每回合分为两个阶段：你先攻击一扇门，Slavik随后修复一扇门。

共有 $n$ 扇门，第 $i$ 扇门初始耐久度为 $a_i$。你的攻击能使门的耐久度减少 $x$，但不会低于0。Slavik的修复能使门的耐久度增加 $y$（无法修复耐久为0的门）。

游戏持续 $10^{100}$ 回合。双方都采取最优策略时，最终耐久为0的门最多有多少？

## 算法分类
贪心、博弈论

---

## 题解分析与结论

### 核心思路
1. **当x > y时**：每回合总耐久度净减少，所有门最终会被破坏。答案直接为n。
2. **当x ≤ y时**：
   - 只能破坏初始耐久≤x的门（因为Slavik总能修复耐久> x的门）
   - 双方博弈下，每两个可破坏的门只能保留一个。答案为 `(可破坏门数+1)/2`（向上取整）

### 最优题解

#### 题解作者：qqvq（5星）
**关键亮点**：简洁高效，直接统计符合条件的门数并计算。
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, x, y;
  cin >> n >> x >> y;
  if (x > y) return cout << n, 0;
  int cnt = 0;
  for (int i = 1; i <= n; ++i) cin >> y, cnt += y <= x;
  cout << (cnt + 1) / 2 << endl;
  return 0;
}
```

#### 题解作者：xyf007（5星）
**关键亮点**：逻辑清晰，代码易读。
```cpp
#include<cstdio>
int main() {
  int n,x,y,sum=0;
  scanf("%d%d%d",&n,&x,&y);
  if(x>y) { printf("%d",n); return 0; }
  for(int i=1;i<=n;i++) {
    int a; scanf("%d",&a);
    if(a<=x) sum++;
  }
  printf("%d",(sum+1)/2);
  return 0;
}
```

### 关键技巧
- **博弈视角**：先手优势决定破坏节奏，Slavik只能延缓无法阻止最终结果。
- **数学简化**：通过无限回合特性转化为初始状态的直接统计，避免复杂模拟。

---

## 相似题目推荐
1. [P1123 取数游戏](https://www.luogu.com.cn/problem/P1123) - 贪心策略与博弈分析
2. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) - 贪心覆盖问题
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略与优先队列应用

---
处理用时：88.57秒