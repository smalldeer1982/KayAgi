# 题目信息

# Number Game

## 题目描述

Alice and Bob are playing a game. They have an array of positive integers $ a $ of size $ n $ .

Before starting the game, Alice chooses an integer $ k \ge 0 $ . The game lasts for $ k $ stages, the stages are numbered from $ 1 $ to $ k $ . During the $ i $ -th stage, Alice must remove an element from the array that is less than or equal to $ k - i + 1 $ . After that, if the array is not empty, Bob must add $ k - i + 1 $ to an arbitrary element of the array. Note that both Alice's move and Bob's move are two parts of the same stage of the game. If Alice can't delete an element during some stage, she loses. If the $ k $ -th stage ends and Alice hasn't lost yet, she wins.

Your task is to determine the maximum value of $ k $ such that Alice can win if both players play optimally. Bob plays against Alice, so he tries to make her lose the game, if it's possible.

## 样例 #1

### 输入

```
4
3
1 1 2
4
4 4 4 4
1
1
5
1 3 2 1 1```

### 输出

```
2
0
1
3```

# AI分析结果

### 题目内容重写
Alice和Bob在玩一个游戏。他们有一个大小为$n$的正整数数组$a$。

在游戏开始前，Alice选择一个整数$k \ge 0$。游戏进行$k$轮，每轮编号从1到$k$。在第$i$轮，Alice必须从数组中移除一个小于等于$k - i + 1$的元素。之后，如果数组不为空，Bob必须将$k - i + 1$加到数组中的任意一个元素上。注意，Alice的移除操作和Bob的加法操作是同一轮的两个部分。如果Alice在某轮无法移除元素，她就会输。如果第$k$轮结束后Alice还没有输，她就赢了。

你的任务是确定Alice可以赢得游戏的最大$k$值，假设双方都采取最优策略。Bob会尽力让Alice输掉游戏。

### 算法分类
贪心、二分

### 题解分析与结论
1. **CENRUIYANG的题解**：通过二分答案和贪心策略，判断Alice是否能赢得游戏。Alice每次移除最大的满足条件的元素，Bob每次移除最小的元素。时间复杂度为$O(n\log n)$。
2. **whdywjd的题解**：通过分析博弈策略，Alice每次移除最大的满足条件的元素，Bob每次移除最小的元素。通过遍历和条件判断，确定最大$k$值。时间复杂度为$O(tn)$。
3. **Strelitzia_的题解**：通过二分答案和模拟游戏过程，判断Alice是否能赢得游戏。Alice每次移除最大的满足条件的元素，Bob每次移除最小的元素。时间复杂度为$O(tn^2\log n)$。

### 高星题解
1. **CENRUIYANG的题解**（5星）
   - 关键亮点：使用二分答案和贪心策略，代码简洁高效。
   - 代码核心思想：二分查找最大$k$值，每次检查Alice是否能完成$k$轮操作。
   ```cpp
   bool check(int k) {
       // 模拟游戏过程，判断Alice是否能完成k轮操作
   }
   int main() {
       // 二分查找最大k值
   }
   ```

2. **whdywjd的题解**（4星）
   - 关键亮点：通过遍历和条件判断，直接确定最大$k$值，避免了复杂的模拟过程。
   - 代码核心思想：遍历$k$值，判断Alice是否能完成$k$轮操作。
   ```cpp
   int mxk = n + 1 >> 1, ans = 0;
   for(int i = 1; i <= n + 1 >> 1; i++) {
       mxk = min(mxk, sum[i] + 1 - i);
       if(mxk < i) break;
       ans = i;
   }
   ```

### 最优关键思路
1. **二分答案**：通过二分查找确定最大$k$值，减少时间复杂度。
2. **贪心策略**：Alice每次移除最大的满足条件的元素，Bob每次移除最小的元素，确保双方都采取最优策略。

### 可拓展之处
类似的问题可以扩展到其他博弈论题目，如Nim游戏、取石子游戏等，通过分析双方的最优策略来解决问题。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：26.51秒