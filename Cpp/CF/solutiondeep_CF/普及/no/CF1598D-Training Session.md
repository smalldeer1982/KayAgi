# 题目信息

# Training Session

## 题目描述

Monocarp is the coach of the Berland State University programming teams. He decided to compose a problemset for a training session for his teams.

Monocarp has $ n $ problems that none of his students have seen yet. The $ i $ -th problem has a topic $ a_i $ (an integer from $ 1 $ to $ n $ ) and a difficulty $ b_i $ (an integer from $ 1 $ to $ n $ ). All problems are different, that is, there are no two tasks that have the same topic and difficulty at the same time.

Monocarp decided to select exactly $ 3 $ problems from $ n $ problems for the problemset. The problems should satisfy at least one of two conditions (possibly, both):

- the topics of all three selected problems are different;
- the difficulties of all three selected problems are different.

Your task is to determine the number of ways to select three problems for the problemset.

## 说明/提示

In the first example, you can take the following sets of three problems:

- problems $ 1 $ , $ 2 $ , $ 4 $ ;
- problems $ 1 $ , $ 3 $ , $ 4 $ ;
- problems $ 2 $ , $ 3 $ , $ 4 $ .

Thus, the number of ways is equal to three.

## 样例 #1

### 输入

```
2
4
2 4
3 4
2 1
1 3
5
1 5
2 4
3 3
4 2
5 1```

### 输出

```
3
10```

# AI分析结果

### 题目翻译

Monocarp 是 Berland 州立大学编程团队的教练。他决定为他的团队组织一次训练，并为此准备了一个问题集。

Monocarp 有 $n$ 个问题，他的学生都还没有见过这些问题。第 $i$ 个问题有一个主题 $a_i$（一个从 $1$ 到 $n$ 的整数）和一个难度 $b_i$（一个从 $1$ 到 $n$ 的整数）。所有问题都是不同的，也就是说，没有两个问题同时具有相同的主题和难度。

Monocarp 决定从 $n$ 个问题中恰好选择 $3$ 个问题组成问题集。这些选择的问题必须满足以下两个条件中的至少一个（可能同时满足）：

- 所有三个选择的问题的主题都不同；
- 所有三个选择的问题的难度都不同。

你的任务是确定选择三个问题组成问题集的方式数。

### 算法分类
组合数学

### 题解分析与结论

本题的核心思路是通过补集思想，先计算所有可能的选择方式，然后减去不满足条件的方式。具体来说，总的选择方式数为 $C_n^3$，而不满足条件的方式数可以通过枚举每个问题，计算其与其它问题在主题和难度上重复的情况，最终用总数减去这些不合法的情况。

### 评分较高的题解

#### 题解作者：Wuyanru (5星)
- **关键亮点**：思路清晰，代码简洁，使用了补集思想，并通过枚举每个问题来计算不合法的情况。代码中使用了 `numa` 和 `numb` 数组来记录每个主题和难度的出现次数，优化了计算过程。
- **代码核心思想**：
  ```cpp
  long long ans = (long long)n * (n - 1) * (n - 2) / 6;
  for (int i = 1; i <= n; i++) {
      ans -= (long long)(numa[a[i]] - 1) * (numb[b[i]] - 1);
  }
  ```
  这段代码通过枚举每个问题，计算其与其它问题在主题和难度上重复的情况，并从总数中减去这些不合法的情况。

#### 题解作者：lgx57 (4星)
- **关键亮点**：使用了 `map` 来记录每个主题和难度的出现次数，代码简洁易懂，适合初学者理解。
- **代码核心思想**：
  ```cpp
  int ans = n * (n - 1) * (n - 2) / 6;
  for (int i = 1; i <= n; i++) {
      ans -= (mapa[a[i]] - 1) * (mapb[b[i]] - 1);
  }
  ```
  这段代码通过 `map` 记录每个主题和难度的出现次数，并计算不合法的情况。

#### 题解作者：zhangqiuyanAFOon2024 (4星)
- **关键亮点**：代码简洁，使用了 `sa` 和 `sb` 数组来记录每个主题和难度的出现次数，思路清晰。
- **代码核心思想**：
  ```cpp
  int ans = n * (n - 1) * (n - 2) / 6;
  for (int i = 1; i <= n; i++) {
      ans -= (sa[a[i]] - 1) * (sb[b[i]] - 1);
  }
  ```
  这段代码通过 `sa` 和 `sb` 数组记录每个主题和难度的出现次数，并计算不合法的情况。

### 最优关键思路
使用补集思想，先计算所有可能的选择方式，然后通过枚举每个问题，计算其与其它问题在主题和难度上重复的情况，最终用总数减去这些不合法的情况。这种方法避免了直接计算满足条件的复杂情况，简化了问题。

### 可拓展之处
类似的问题可以通过补集思想来解决，尤其是在需要计算满足某些条件的组合数时，可以先计算总数，然后减去不满足条件的情况。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)

### 个人心得摘录
- **Wuyanru**：通过补集思想简化了问题，避免了直接计算满足条件的复杂情况。
- **lgx57**：使用 `map` 记录出现次数，代码简洁易懂，适合初学者理解。
- **zhangqiuyanAFOon2024**：思路清晰，代码简洁，使用了 `sa` 和 `sb` 数组来记录每个主题和难度的出现次数。

---
处理用时：32.24秒