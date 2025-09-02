# 题目信息

# Quests

## 题目描述

Monocarp is playing a computer game. In order to level up his character, he can complete quests. There are $ n $ quests in the game, numbered from $ 1 $ to $ n $ .

Monocarp can complete quests according to the following rules:

- the $ 1 $ -st quest is always available for completion;
- the $ i $ -th quest is available for completion if all quests $ j < i $ have been completed at least once.

Note that Monocarp can complete the same quest multiple times.

For each completion, the character gets some amount of experience points:

- for the first completion of the $ i $ -th quest, he gets $ a_i $ experience points;
- for each subsequent completion of the $ i $ -th quest, he gets $ b_i $ experience points.

Monocarp is a very busy person, so he has free time to complete no more than $ k $ quests. Your task is to calculate the maximum possible total experience Monocarp can get if he can complete no more than $ k $ quests.

## 说明/提示

In the first test case, one of the possible quest completion sequences is as follows: $ 1, 1, 2, 3, 2, 4, 4 $ ; its total experience is equal to $ \underline{4} + 1 + \underline{3} + \underline{1} + 1 + \underline{2} + 1 = 13 $ (the underlined numbers correspond to the instances when we complete a quest for the first time).

In the second test case, one of the possible quest completion sequences is as follows: $ 1, 1 $ ; its total experience is equal to $ \underline{1} + 3 = 4 $ .

In the third test case, one of the possible quest completion sequences is as follows: $ 1, 2, 2, 2, 3 $ ; its total experience is equal to $ \underline{3} + \underline{2} + 3 + 3 + \underline{4} = 15 $ .

## 样例 #1

### 输入

```
4
4 7
4 3 1 2
1 1 1 1
3 2
1 2 5
3 1 8
5 5
3 2 4 1 4
2 3 1 4 7
6 4
1 4 5 4 5 10
1 5 1 2 5 1```

### 输出

```
13
4
15
15```

# AI分析结果

### 题目中文重写
# 任务

## 题目描述
Monocarp正在玩一款电脑游戏。为了提升他的角色等级，他可以完成任务。游戏中有 $n$ 个任务，编号从 $1$ 到 $n$。

Monocarp可以按照以下规则完成任务：
- 第 $1$ 个任务始终可以完成；
- 只有当所有编号 $j < i$ 的任务都至少完成过一次时，第 $i$ 个任务才可以完成。

注意，Monocarp可以多次完成同一个任务。

每次完成任务时，角色会获得一定数量的经验值：
- 第一次完成第 $i$ 个任务时，他会获得 $a_i$ 点经验值；
- 之后每次完成第 $i$ 个任务时，他会获得 $b_i$ 点经验值。

Monocarp是个非常忙碌的人，所以他只有完成不超过 $k$ 个任务的空闲时间。你的任务是计算如果他最多能完成 $k$ 个任务，他能获得的最大总经验值。

## 说明/提示
在第一个测试用例中，一种可能的任务完成顺序如下：$1, 1, 2, 3, 2, 4, 4$；其总经验值等于 $\underline{4} + 1 + \underline{3} + \underline{1} + 1 + \underline{2} + 1 = 13$（下划线数字对应我们第一次完成任务的情况）。

在第二个测试用例中，一种可能的任务完成顺序如下：$1, 1$；其总经验值等于 $\underline{1} + 3 = 4$。

在第三个测试用例中，一种可能的任务完成顺序如下：$1, 2, 2, 2, 3$；其总经验值等于 $\underline{3} + \underline{2} + 3 + 3 + \underline{4} = 15$。

## 样例 #1

### 输入
```
4
4 7
4 3 1 2
1 1 1 1
3 2
1 2 5
3 1 8
5 5
3 2 4 1 4
2 3 1 4 7
6 4
1 4 5 4 5 10
1 5 1 2 5 1
```

### 输出
```
13
4
15
15
```

### 综合分析与结论
- **思路对比**：三位作者思路一致，均是枚举完成前 $i$ 个任务（$i$ 取值范围为 $[1, \min(n, k)]$），计算完成前 $i$ 个任务第一次的奖励总和 $\sum_{j = 1}^{i}a_j$，再找出前 $i$ 个任务中 $b_j$ 的最大值，将剩余的 $k - i$ 次任务都分配给该最大值对应的任务，最后取所有情况中的最大值。
- **算法要点**：都需要维护 $a_i$ 的前缀和与 $b_i$ 的前缀最大值，通过遍历 $i$ 计算每种情况下的奖励并更新最大奖励。
- **解决难点**：核心难点在于理解任务完成规则和奖励机制，确定最优的任务完成策略，即优先完成前 $i$ 个任务各一次，再重复完成 $b$ 值最大的任务。

### 题解评分
- **tbdsh**：5星。思路清晰，代码注释完整，对复杂度进行了分析，整体质量高。
- **infinite2021**：3星。思路简洁，但代码缺乏必要注释，未对复杂度等进行说明。
- **myyyIisq2R**：4星。思路和代码都较为清晰，有详细的代码实现，但注释可进一步完善。

### 所选题解
- **tbdsh（5星）**
    - **关键亮点**：思路清晰，代码可读性高，有复杂度分析。
    - **核心代码**：
```cpp
void Solve(){
  cin >> n >> k;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++){
    cin >> b[i];
  }
  int maxx = -1, ans = 0, sum = 0;
  for (int i = 1; i <= min(n, k); i++){
    maxx = max(maxx, b[i]);
    sum += a[i];
    ans = max(ans, sum + (k - i) * maxx);
  }
  cout << ans << '\n';
}
```
核心思想：通过遍历 $i$，不断更新 $b_i$ 的最大值 `maxx` 和 $a_i$ 的前缀和 `sum`，计算当前情况下的奖励并更新最大奖励 `ans`。

### 最优关键思路或技巧
- **思维方式**：通过枚举完成任务的数量 $i$，结合任务完成规则和奖励机制，找到最优的任务分配策略。
- **代码实现**：使用前缀和和前缀最大值来优化计算过程，将时间复杂度控制在 $O(n)$。

### 可拓展之处
同类型题目可能会改变任务完成规则、奖励机制或增加其他限制条件，如任务有时间限制、每个任务有不同的完成次数上限等。解题时可借鉴本题的枚举和贪心策略，结合具体条件进行调整。

### 推荐洛谷题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P2240 食草的奶牛](https://www.luogu.com.cn/problem/P2240)

### 个人心得
题解中未包含个人心得内容。

---
处理用时：30.44秒