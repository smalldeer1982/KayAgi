# 题目信息

# Down the Hatch!

## 题目描述

Everybody knows that the Berland citizens are keen on health, especially students. Berland students are so tough that all they drink is orange juice!

Yesterday one student, Vasya and his mates made some barbecue and they drank this healthy drink only. After they ran out of the first barrel of juice, they decided to play a simple game. All $ n $ people who came to the barbecue sat in a circle (thus each person received a unique index $ b_{i} $ from 0 to $ n-1 $ ). The person number 0 started the game (this time it was Vasya). All turns in the game were numbered by integers starting from 1. If the $ j $ -th turn was made by the person with index $ b_{i} $ , then this person acted like that:

1. he pointed at the person with index $ (b_{i}+1) mod n $ either with an elbow or with a nod ( $ x mod y $ is the remainder after dividing $ x $ by $ y $ );
2. if $ j>=4 $ and the players who had turns number $ j-1 $ , $ j-2 $ , $ j-3 $ , made during their turns the same moves as player $ b_{i} $ on the current turn, then he had drunk a glass of juice;
3. the turn went to person number $ (b_{i}+1) mod n $ .

The person who was pointed on the last turn did not make any actions.

The problem was, Vasya's drunk too much juice and can't remember the goal of the game. However, Vasya's got the recorded sequence of all the participants' actions (including himself). Now Vasya wants to find out the maximum amount of juice he could drink if he played optimally well (the other players' actions do not change). Help him.

You can assume that in any scenario, there is enough juice for everybody.

## 说明/提示

In both samples Vasya has got two turns — 1 and 5. In the first sample, Vasya could have drunk a glass of juice during the fifth turn if he had pointed at the next person with a nod. In this case, the sequence of moves would look like "abbbb". In the second sample Vasya wouldn't drink a single glass of juice as the moves performed during turns 3 and 4 are different.

## 样例 #1

### 输入

```
4
abbba
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
abbab
```

### 输出

```
0
```

# AI分析结果



# 中文题目重写

## 题目名称：钻入地下！

### 题目描述

众所周知，Berland 的居民非常注重健康，尤其是学生。Berland 的学生身体强壮，他们只喝橙汁！

昨天，一位名叫 Vasya 的学生和伙伴们在烧烤时只喝了这种健康饮品。当他们喝完第一桶果汁后，决定玩一个简单的游戏。所有参加烧烤的 $n$ 个人围坐成一个圆圈（因此每个人被分配了唯一的编号 $b_i$，从 0 到 $n-1$）。编号为 0 的人（即 Vasya）开始游戏。所有回合按整数顺序编号，从 1 开始。如果第 $j$ 回合由编号为 $b_i$ 的人进行，则此人会执行以下操作：

1. 用手肘或点头（即字符 'a' 或 'b'）指向下一个人，编号为 $(b_i + 1) \mod n$；
2. 如果 $j \ge 4$ 且当前回合的前三个回合（即 $j-1$、$j-2$、$j-3$）的动作与当前动作相同，则此人需喝一杯果汁；
3. 轮到编号为 $(b_i + 1) \mod n$ 的人进行下一回合。

最后一个被指向的人不执行任何动作。

问题在于，Vasya 喝了太多果汁，无法记住游戏目标。但他记录了所有参与者的动作序列（包括他自己）。现在 Vasya 想知道，如果他在自己的回合中采取最优策略（其他玩家的动作不变），他最多能喝多少杯果汁。假设无论如何，果汁都足够所有人饮用。

---

## 算法分类
**枚举**

---

## 题解综合分析

**核心思路**：  
遍历 Vasya 的每个回合位置（即字符串中索引为 $0, n, 2n, \dots$ 的位置），检查前三个动作是否相同。若相同，则 Vasya 可通过选择相同动作触发条件，答案加 1。

**解决难点**：  
1. 正确识别 Vasya 的回合位置（步长为 $n$ 的索引）。  
2. 避免下标越界（需跳过 $i < 3$ 的情况）。  
3. 判断前三个动作的一致性，实现高效检查。

---

## 精选题解

### 题解作者：Bc2_ChickenDreamer（4星）
**关键亮点**：  
- 简洁的循环遍历，直接步长 $n$ 处理 Vasya 的回合。  
- 明确的特判 $i < 3$ 避免越界。  
**核心代码**：  
```cpp
for (int i = 0; i < t.size(); i += n) {
    if (i < 3) continue;
    if (t[i-1] == t[i-2] && t[i-2] == t[i-3]) ++ans;
}
```

### 题解作者：708151_qwq（4星）
**关键亮点**：  
- 代码结构清晰，变量命名直观。  
- 注释明确，便于理解边界条件。  
**核心代码**：  
```cpp
for(int i=0; i<s.size(); i+=n) {
    if(i<3) continue;
    if(s[i-1]==s[i-2] && s[i-2]==s[i-3]) sum++;
}
```

### 题解作者：VitrelosTia（4星）
**关键亮点**：  
- 逻辑直白，直接遍历并判断条件。  
- 使用 `long long` 避免溢出，代码鲁棒性强。  
**核心代码**：  
```cpp
for(ll i=0; i<s.size(); i+=n) {
    if(i<3) continue;
    if(s[i-1]==s[i-2]&&s[i-2]==s[i-3]) ans++;
}
```

---

## 关键技巧总结
1. **循环步长优化**：直接以 $n$ 为步长遍历，快速定位关键位置。  
2. **边界处理**：通过 $i < 3$ 的特判避免下标越界，确保代码安全。  
3. **条件判断**：仅需检查前三字符是否相同，无需复杂逻辑。  

---

## 拓展与相似题目
- **类似题目推荐**：  
  1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)（枚举组合）  
  2. [P1591 阶乘数码](https://www.luogu.com.cn/problem/P1591)（数学模拟）  
  3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心策略）  

---

## 题解心得摘录
- **调试经验**：  
  - 注意 $i < 3$ 的越界问题，否则会导致 RE（运行时错误）。  
- **顿悟点**：  
  - Vasya 的回合位置规律（每隔 $n$ 个字符）是解题关键，无需复杂数学推导。

---
处理用时：187.66秒