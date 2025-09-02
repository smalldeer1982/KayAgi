# 题目信息

# Anna and the Valentine's Day Gift

## 题目描述

Sasha gave Anna a list $ a $ of $ n $ integers for Valentine's Day. Anna doesn't need this list, so she suggests destroying it by playing a game.

Players take turns. Sasha is a gentleman, so he gives Anna the right to make the first move.

- On her turn, Anna must choose an element $ a_i $ from the list and reverse the sequence of its digits. For example, if Anna chose the element with a value of $ 42 $ , it would become $ 24 $ ; if Anna chose the element with a value of $ 1580 $ , it would become $ 851 $ . Note that leading zeros are removed. After such a turn, the number of elements in the list does not change.
- On his turn, Sasha must extract two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) from the list, concatenate them in any order and insert the result back into the list. For example, if Sasha chose the elements equal to $ 2007 $ and $ 19 $ , he would remove these two elements from the list and add the integer $ 200719 $ or $ 192007 $ . After such a turn, the number of elements in the list decreases by $ 1 $ .

Players can't skip turns. The game ends when Sasha can't make a move, i.e. after Anna's move there is exactly one number left in the list. If this integer is not less than $ 10^m $ (i.e., $ \ge 10^m $ ), Sasha wins. Otherwise, Anna wins.

It can be shown that the game will always end. Determine who will win if both players play optimally.

## 说明/提示

Consider the first test case.

Anna can reverse the integer $ 2 $ , then Sasha can concatenate the integers $ 2 $ and $ 14 $ , obtaining the integer $ 214 $ , which is greater than $ 10^2 = 100 $ . If Anna had reversed the integer $ 14 $ , Sasha would have concatenated the integers $ 41 $ and $ 2 $ , obtaining the integer $ 412 $ , which is greater than $ 10^2 = 100 $ . Anna has no other possible moves, so she loses.

## 样例 #1

### 输入

```
9
2 2
14 2
3 5
9 56 1
4 10
1 2007 800 1580
4 5
5000 123 30 4
10 10
6 4 6 2 3 1 10 9 10 7
1 1
6
1 1
10
8 9
1 2 9 10 10 2 10 2
4 5
10 10 10 10```

### 输出

```
Sasha
Anna
Anna
Sasha
Sasha
Anna
Anna
Anna
Sasha```

# AI分析结果

### 题目内容重写

#### Anna和情人节礼物

**题目描述**

Sasha在情人节给Anna一个包含$n$个整数的列表$a$。Anna并不需要这个列表，所以她建议通过玩游戏来销毁它。

玩家轮流进行操作。Sasha是个绅士，所以他让Anna先手。

- 在Anna的回合，她必须从列表中选择一个元素$a_i$，并将其数字顺序反转。例如，如果Anna选择了值为$42$的元素，它就会变成$24$；如果选择了值为$1580$的元素，它就会变成$851$。注意，前导零会被移除。在这样的操作后，列表中的元素数量不变。
- 在Sasha的回合，他必须从列表中提取两个元素$a_i$和$a_j$（$i \ne j$），以任意顺序将它们拼接，并将结果插入回列表中。例如，如果Sasha选择了值为$2007$和$19$的元素，他会将这两个元素从列表中移除，并添加整数$200719$或$192007$。在这样的操作后，列表中的元素数量减少$1$。

玩家不能跳过回合。游戏在Sasha无法进行操作时结束，即Anna操作后列表中只剩下一个数字。如果这个整数不小于$10^m$（即$\ge 10^m$），Sasha获胜。否则，Anna获胜。

可以证明游戏总是会结束。假设双方都采取最优策略，确定谁会获胜。

**说明/提示**

考虑第一个测试用例。

Anna可以反转整数$2$，然后Sasha可以将整数$2$和$14$拼接，得到整数$214$，它大于$10^2 = 100$。如果Anna反转了整数$14$，Sasha会将整数$41$和$2$拼接，得到整数$412$，它也大于$10^2 = 100$。Anna没有其他可能的操作，所以她输了。

**样例 #1**

**输入**

```
9
2 2
14 2
3 5
9 56 1
4 10
1 2007 800 1580
4 5
5000 123 30 4
10 10
6 4 6 2 3 1 10 9 10 7
1 1
6
1 1
10
8 9
1 2 9 10 10 2 10 2
4 5
10 10 10 10
```

**输出**

```
Sasha
Anna
Anna
Sasha
Sasha
Anna
Anna
Anna
Sasha
```

### 题解分析与结论

#### 综合分析

本题的核心在于双方的最优策略：Anna希望通过反转数字减少最终数字的位数，而Sasha则希望通过拼接数字来保留尽可能多的位数。双方的策略都围绕着数字的末尾零展开，因为Anna可以通过反转去掉末尾零，而Sasha可以通过拼接保护末尾零。

#### 最优思路

1. **贪心策略**：Anna每次选择末尾零最多的数字进行反转，以减少最终数字的位数；Sasha则选择末尾零最多的数字与其他数字拼接，以保护这些零。
2. **排序与模拟**：将所有数字按末尾零的数量从大到小排序，Anna和Sasha轮流操作，Anna去掉奇数位的末尾零，Sasha保护偶数位的末尾零。
3. **位数计算**：最终通过总位数减去Anna去掉的零数，判断是否大于$m$来决定胜负。

#### 推荐题解

1. **信息向阳花木**（5星）
   - **关键亮点**：思路清晰，代码简洁，直接通过排序和模拟实现了最优策略。
   - **代码实现**：
     ```cpp
     sort(l0 + 1, l0 + n + 1, cmp); 
     for (int i = 1; i <= n; i += 2) {
         cnt -= l0[i];
     }
     if(cnt >= m + 1) puts("Sasha");
     else puts("Anna");
     ```

2. **SXqwq**（4星）
   - **关键亮点**：详细分析了双方的策略，代码实现较为直观。
   - **代码实现**：
     ```cpp
     sort(a + 1, a + n + 1, cmp);
     for (int i = 1; i <= n; i += 2) {
         take -= a[i];
     }
     if(take > m) cout<<"Sasha"<<endl;
     else cout<<"Anna"<<endl;
     ```

3. **MorLeaves**（4星）
   - **关键亮点**：使用了优先队列来处理数字的末尾零，代码结构清晰。
   - **代码实现**：
     ```cpp
     for(int i = 1; i < n; i++) {
         auto tmp = pq.top();
         pq.pop();
         pq.push({tmp.l - tmp.r, 0});
         auto x = pq.top();
         pq.pop();
         auto y = pq.top();
         pq.pop();
         pq.push({x.l + y.l, min(x.r, y.r)});
     }
     ```

### 关键思路与技巧

1. **贪心策略**：通过每次选择最优的操作，确保双方都能在每一步中最大化自己的利益。
2. **排序与模拟**：通过排序和模拟双方的策略，简化了问题的复杂度。
3. **位数计算**：通过计算总位数和去掉的零数，快速判断最终结果。

### 拓展思路

类似的问题可以出现在博弈论或贪心算法的题目中，通常涉及到双方的最优策略和模拟操作。可以通过类似的思路来解决这类问题。

### 推荐题目

1. [P1307 数字反转](https://www.luogu.com.cn/problem/P1307)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：51.46秒