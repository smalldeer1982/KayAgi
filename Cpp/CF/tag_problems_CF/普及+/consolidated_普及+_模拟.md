---
title: "Vasya And The Mushrooms"
layout: "post"
diff: 普及+/提高
pid: CF1016C
tag: ['模拟', '递推', '前缀和']
---

# Vasya And The Mushrooms

## 题目描述

Vasya 住在森林里，附近有一个会长蘑菇的空地。这个空地被分成两行，每行分为 $n$ 个连续的格子。Vasya 知道每分钟每个格子里能长多少个蘑菇。他要花一分钟从一个格子走到相邻的格子上，并且他不能离开空地。（我们称两个格子相邻，当且仅当它们有公共边。）当 Vasya 进入一个格子时，他会马上收集那个格子里的所有蘑菇。

Vasya 从左上角的格子开始收集蘑菇。因为他等不及蘑菇生长了，所以每分钟内他必须移动到一个相邻格子。他想每个格子都恰好走一遍并且最大化他所收集的蘑菇数量。一开始所有格子都没有蘑菇。Vasya也不一定要回到开始的格子。
帮帮 Vasya！计算出他能收集到的最大蘑菇数量。

## 输入格式

第一行包含数字 $n(1 \le n \le 3 \cdot 10 ^ {5})$ —— 空地的长度。

第二行包含 $n$ 个数字 $a_ {1}, a_ {2}, \ldots, a_{n}$（$1 \le a_{i} \le 10^{6}$） —— 在空地第一行的蘑菇的生长速度。

第三行包含 $n$ 个数字 $b_ {1}, b_ {2}, \ldots, b_{n}$（$1 \le b_ {i} \le 10 ^ {6}$） —— 在空地第二行的蘑菇的生长速度。

## 输出格式

输出一个数字—— Vasya 通过选择最佳路线可以收集的最大蘑菇总重量。 

请注意，Vasya 必须将空地中的每个单元都访问一次。

## 说明/提示

#### 样例1:

在第一个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/fbb0db02f46ac40c8f18dc6a212852df14543f5e.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·2 + 2·3 + 3·4 + 4·5 + 5·6 =70$。

#### 样例2:

在第二个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/0853812a60511dc1127814cc7d3f93535736820f.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·10 + 2·100 + 3·1000 + 4·10000 + 5·100000 =543210$

## 样例 #1

### 输入

```
3
1 2 3
6 5 4

```

### 输出

```
70

```

## 样例 #2

### 输入

```
3
1 1000 10000
10 100 100000

```

### 输出

```
543210

```



---

---
title: "Make It Equal"
layout: "post"
diff: 普及+/提高
pid: CF1065C
tag: ['模拟', '贪心', '树状数组']
---

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ n \le k \le 10^9 $ ) — the number of towers and the restriction on slices, respectively.

The second line contains $ n $ space separated integers $ h_1, h_2, \dots, h_n $ ( $ 1 \le h_i \le 2 \cdot 10^5 $ ) — the initial heights of towers.

## 输出格式

Print one integer — the minimum number of good slices you have to do to make all towers have the same heigth.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 5
2 3 4 5

```

### 输出

```
2

```



---

---
title: "Valeriy and Deque"
layout: "post"
diff: 普及+/提高
pid: CF1179A
tag: ['模拟']
---

# Valeriy and Deque

## 题目描述

Recently, on the course of algorithms and data structures, Valeriy learned how to use a deque. He built a deque filled with $ n $ elements. The $ i $ -th element is $ a_i $ ( $ i $ = $ 1, 2, \ldots, n $ ). He gradually takes the first two leftmost elements from the deque (let's call them $ A $ and $ B $ , respectively), and then does the following: if $ A > B $ , he writes $ A $ to the beginning and writes $ B $ to the end of the deque, otherwise, he writes to the beginning $ B $ , and $ A $ writes to the end of the deque. We call this sequence of actions an operation.

For example, if deque was $ [2, 3, 4, 5, 1] $ , on the operation he will write $ B=3 $ to the beginning and $ A=2 $ to the end, so he will get $ [3, 4, 5, 1, 2] $ .

The teacher of the course, seeing Valeriy, who was passionate about his work, approached him and gave him $ q $ queries. Each query consists of the singular number $ m_j $ $ (j = 1, 2, \ldots, q) $ . It is required for each query to answer which two elements he will pull out on the $ m_j $ -th operation.

Note that the queries are independent and for each query the numbers $ A $ and $ B $ should be printed in the order in which they will be pulled out of the deque.

Deque is a data structure representing a list of elements where insertion of new elements or deletion of existing elements can be made from both sides.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \leq n \leq 10^5 $ , $ 0 \leq q \leq 3 \cdot 10^5 $ ) — the number of elements in the deque and the number of queries. The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ , where $ a_i $ $ (0 \leq a_i \leq 10^9) $ — the deque element in $ i $ -th position. The next $ q $ lines contain one number each, meaning $ m_j $ ( $ 1 \leq m_j \leq 10^{18} $ ).

## 输出格式

For each teacher's query, output two numbers $ A $ and $ B $ — the numbers that Valeriy pulls out of the deque for the $ m_j $ -th operation.

## 说明/提示

 Consider all 10 steps for the first test in detail:2. $ [1, 2, 3, 4, 5] $ — on the first operation, $ A $ and $ B $ are $ 1 $ and $ 2 $ , respectively.So, $ 2 $ we write to the beginning of the deque, and $ 1 $ — to the end.
  
  We get the following status of the deque: $ [2, 3, 4, 5, 1] $ .
3. $ [2, 3, 4, 5, 1] \Rightarrow A = 2, B = 3 $ .
4. $ [3, 4, 5, 1, 2] $
5. $ [4, 5, 1, 2, 3] $
6. $ [5, 1, 2, 3, 4] $
7. $ [5, 2, 3, 4, 1] $
8. $ [5, 3, 4, 1, 2] $
9. $ [5, 4, 1, 2, 3] $
10. $ [5, 1, 2, 3, 4] $
11. $ [5, 2, 3, 4, 1] \Rightarrow A = 5, B = 2 $ .

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
1
2
10

```

### 输出

```
1 2
2 3
5 2

```

## 样例 #2

### 输入

```
2 0
0 0

```

### 输出

```

```



---

---
title: "Playing with Superglue"
layout: "post"
diff: 普及+/提高
pid: CF176C
tag: ['模拟']
---

# Playing with Superglue

## 题目描述

Two players play a game. The game is played on a rectangular board with $ n×m $ squares. At the beginning of the game two different squares of the board have two chips. The first player's goal is to shift the chips to the same square. The second player aims to stop the first one with a tube of superglue.

We'll describe the rules of the game in more detail.

The players move in turns. The first player begins.

With every move the first player chooses one of his unglued chips, and shifts it one square to the left, to the right, up or down. It is not allowed to move a chip beyond the board edge. At the beginning of a turn some squares of the board may be covered with a glue. The first player can move the chip to such square, in this case the chip gets tightly glued and cannot move any longer.

At each move the second player selects one of the free squares (which do not contain a chip or a glue) and covers it with superglue. The glue dries long and squares covered with it remain sticky up to the end of the game.

If, after some move of the first player both chips are in the same square, then the first player wins. If the first player cannot make a move (both of his chips are glued), then the second player wins. Note that the situation where the second player cannot make a move is impossible — he can always spread the glue on the square from which the first player has just moved the chip.

We will further clarify the case where both chips are glued and are in the same square. In this case the first player wins as the game ends as soon as both chips are in the same square, and the condition of the loss (the inability to move) does not arise.

You know the board sizes and the positions of the two chips on it. At the beginning of the game all board squares are glue-free. Find out who wins if the players play optimally.

## 输入格式

The first line contains six integers $ n $ , $ m $ , $ x_{1} $ , $ y_{1} $ , $ x_{2} $ , $ y_{2} $ — the board sizes and the coordinates of the first and second chips, correspondingly ( $ 1<=n,m<=100 $ ; $ 2<=n×m $ ; $ 1<=x_{1},x_{2}<=n $ ; $ 1<=y_{1},y_{2}<=m $ ). The numbers in the line are separated by single spaces.

It is guaranteed that the chips are located in different squares.

## 输出格式

If the first player wins, print "First" without the quotes. Otherwise, print "Second" without the quotes.

## 样例 #1

### 输入

```
1 6 1 2 1 6

```

### 输出

```
First
```

## 样例 #2

### 输入

```
6 5 4 3 2 1

```

### 输出

```
First
```

## 样例 #3

### 输入

```
10 10 1 1 10 10

```

### 输出

```
Second
```



---

---
title: "Berserk Monsters"
layout: "post"
diff: 普及+/提高
pid: CF1922D
tag: ['模拟']
---

# Berserk Monsters

## 题目描述

Monocarp is playing a computer game (yet again). Guess what is he doing? That's right, killing monsters.

There are $ n $ monsters in a row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has two parameters: attack value equal to $ a_i $ and defense value equal to $ d_i $ . In order to kill these monsters, Monocarp put a berserk spell on them, so they're attacking each other instead of Monocarp's character.

The fight consists of $ n $ rounds. Every round, the following happens:

- first, every alive monster $ i $ deals $ a_i $ damage to the closest alive monster to the left (if it exists) and the closest alive monster to the right (if it exists);
- then, every alive monster $ j $ which received more than $ d_j $ damage during this round dies. I. e. the $ j $ -th monster dies if and only if its defense value $ d_j $ is strictly less than the total damage it received this round.

For each round, calculate the number of monsters that will die during that round.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ );
- the third line contains $ n $ integers $ d_1, d_2, \dots, d_n $ ( $ 1 \le d_i \le 10^9 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers. The $ i $ -th integer should be equal to the number of monsters that die during the $ i $ -th round.

## 说明/提示

Explanation for the first test case of the example:

During the first round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 2 $ ;
- the monster $ 2 $ deals $ 4 $ damage to the monster $ 1 $ and the monster $ 3 $ ;
- the monster $ 3 $ deals $ 7 $ damage to the monster $ 2 $ and the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 3 $ and the monster $ 5 $ ;
- the monster $ 5 $ deals $ 10 $ damage to the monster $ 4 $ ;
- the monster $ 1 $ does not die, since it received $ 4 $ damage and its defense is $ 4 $ ;
- the monster $ 2 $ dies, since it received $ 10 $ damage and its defense is $ 9 $ ;
- the monster $ 3 $ dies, since it received $ 9 $ damage and its defense is $ 1 $ ;
- the monster $ 4 $ does not die, since it received $ 17 $ damage and its defense is $ 18 $ ;
- the monster $ 5 $ dies, since it received $ 5 $ damage and its defense is $ 1 $ .

After the first round, the monsters $ 1 $ and $ 4 $ stay alive.

During the second round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 1 $ ;
- the monster $ 1 $ dies, since it received $ 5 $ damage and its defense is $ 4 $ ;
- the monster $ 4 $ does not die, since it received $ 3 $ damage and its defense is $ 18 $ .

During the next three rounds, only the $ 4 $ -th monster is alive, so nothing happens.

## 样例 #1

### 输入

```
3
5
3 4 7 5 10
4 9 1 18 1
2
2 1
1 3
4
1 1 2 4
3 3 4 2
```

### 输出

```
3 1 0 0 0 
0 0 
1 1 1 0
```



---

---
title: "Cook and Porridge"
layout: "post"
diff: 普及+/提高
pid: CF1945G
tag: ['模拟', '堆']
---

# Cook and Porridge

## 题目描述

Finally, lunchtime!

 $ n $ schoolchildren have lined up in a long queue at the cook's tent for porridge. The cook will be serving porridge for $ D $ minutes. The schoolchild standing in the $ i $ -th position in the queue has a priority of $ k_i $ and eats one portion of porridge in $ s_i $ minutes.

At the beginning of each minute of the break, the cook serves the first schoolchild in the queue one portion of porridge, after which the schoolchild goes to eat their portion. If the $ i $ -th schoolchild is served a portion at the beginning of the $ x $ -th minute, then they will return to the queue at the end of the $ (x + s_i) $ -th minute.

When the $ i $ -th schoolchild returns to the queue, the schoolchildren at the end of the queue whose priority is strictly lower than that of the $ i $ -th schoolchild must let them pass. Thus, they will stand in the queue behind the last schoolchild whose priority is not lower than their own. That is, behind the last schoolchild $ j $ with $ k_j \ge k_i $ . If there is no such schoolchild in the queue, the $ i $ -th schoolchild will stand at the front of the queue.

If several schoolchildren return at the same time, they will return to the queue in ascending order of their $ s_i $ .

For example, if $ n = 3 $ , $ D = 3 $ , $ k = [2, 3, 2] $ , and $ s = [2, 1, 3] $ , the serving will occur as follows:

- At the beginning of minute $ 1 $ , the students in the queue are $ [1, 2, 3] $ , and student $ 1 $ is served porridge;
- at the beginning of minute $ 2 $ , the students in the queue are $ [2, 3] $ , and student $ 2 $ is served porridge;
- at the beginning of minute $ 3 $ , the student in the queue is $ [3] $ , and student $ 3 $ is served porridge;
- at the end of minute $ 3 $ , student $ 2 $ returns to the queue, and the queue becomes $ [2] $ ;
- at the end of minute $ 3 $ , student $ 1 $ returns to the queue, and the queue becomes $ [2, 1] $ , as his priority is lower.

Determine the minimum number of minutes after the start of the break that each schoolchild will receive porridge at least once, or report that this will not happen within $ D $ minutes.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains two integers $ n $ and $ D $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le D \le 3\cdot 10^5 $ ) — the number of schoolchildren in the queue and the break time, respectively.

The next $ n $ lines contain two integers $ k_i $ and $ s_i $ ( $ 1 \le k_i, s_i, \le 10^9 $ ) — the priority and the time to eat one portion of porridge for the respective schoolchild. The schoolchildren are given in the order they stand in the queue (from the front to the end).

It is guaranteed that the sum of the values of $ n $ for all input data sets does not exceed $ 2\cdot 10^5 $ . Similarly, it is guaranteed that the sum of the values of $ D $ for all input data sets does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of minutes after which each schoolchild will receive porridge at least once. If this does not happen within the break time, output $ -1 $ .

## 样例 #1

### 输入

```
7
3 3
2 2
3 1
2 3
5 10
10 3
7 1
11 3
5 1
6 1
5 20
4 2
7 2
8 5
1 5
3 1
5 17
1 3
8 2
8 3
2 2
1 1
5 14
8 2
4 2
1 3
8 3
6 4
1 11
4 5
5 14
8 2
4 2
1 3
8 3
6 4
```

### 输出

```
3
-1
12
6
6
1
6
```



---

---
title: "Playing Quidditch (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970F2
tag: ['模拟']
---

# Playing Quidditch (Medium)

## 题目描述

今天下午，你决定出门感受春天的气息。当你走到魁地奇球场附近时，突然听到有人大喊。果然，又是在争谁赢了比赛！为了避免这一情况再次发生，你决定参与到比赛的判罚当中。

你留在体育场观看比赛，并记录得分。比赛结束时，你将宣布获胜者。

今天参赛的两支队伍是：红色的格兰芬多（R）和蓝色的拉文克劳（B）。每队有 $P$ 名球员（$1 \leq P \leq 10$）。

场地是一个 $N$ 行 $M$ 列的矩形（$3 \leq N, M \leq 99$，$N$ 和 $M$ 均为奇数）。所有位置都是整数值，并且允许多个实体同时位于同一位置。比赛开始时，场地上有两队的球门（每队有一个到五个球门）、球员以及一个鬼飞球。在这一版本的问题中，可能还会出现一个游走球。而在更难的版本中，还会有另一种球。

比赛由 $T$ 个步骤组成（$0 \leq T \leq 10000$）。每一步中，场上的一个实体（球员或者球）都会执行一个动作。所有实体都可以移动。球员还可以接球或者投掷手中的鬼飞球。要接球，球员必须与球处于同一格子。当球员持有鬼飞球时，鬼飞球不会进行任何动作，只是随球员一起移动。如果球员决定投出鬼飞球，它将留在球员当前的位置。如果球员和游走球同时处于同一格子（无论是球员移动还是游走球移动导致的结果），该球员将被淘汰。如果球员被淘汰时正持球，鬼飞球将留在原地，与淘汰球员和游走球同处一格。可以保证不会在球员位于球门时发生这种情况。

想要得分，球员必须将鬼飞球放在对方的球门。当球员得分时，该球员的队伍获得一分，鬼飞球将立即移动至场地中央（从1开始计数的第 $(N+1)/2$ 行、第 $(M+1)/2$ 列）。中央没有球门。如果球员把球放进自家球门，那对方队伍将获得一分。

## 输入格式

第一行是两个整数表示场地大小：$N$ 和 $M$。

接下来是场地的描述：共 $N$ 行，每行有 $M$ 个字符对，以空格分隔。每个字符对表示场地上的一个位置，可以是以下形式之一：

- `..` 表示空格
- `R0`, ..., `R9`, `B0`, ..., `B9` 表示球员。第一个字符是球员所在的队伍，第二个字符是球员的编号。每个字符对都是唯一的，但不保证所有可能的字符对都会出现在网格中。
- `RG` 或 `BG` 表示球门。蓝队尝试将球踢进红队球门（`RG`），而红队则尝试将球踢进蓝队球门（`BG`）。
- `.Q` 表示鬼飞球，这是球员用来得分的球。
- `.B` 表示游走球。

接下来的一行包含一个整数 $T$，表示构成比赛的动作数量。随后有 $T$ 行，每行描述一个动作。行中有多个信息，用空格分隔。首先是一对字符，表示执行动作的实体。接着是动作的描述：

- `U`, `D`, `L`, `R` 表示实体在网格上的移动方向。可以分别向上（`U`）、向下（`D`）、向左（`L`）或向右（`R`）移动。每次只移动一个格子。
- `C` 表示球员接住了球（只有球员可以接球）。随后是一个空格和一个字符对，表示被接住的球。需要此信息，因为可能多个球在同一格子中。
- `T` 表示球员投出了携带的鬼飞球。

所有动作都是有效的：即球员始终在场地范围内，球员不会在非同格子时接球，不会在未携球时投球，等等。

## ��出格式

你需要输出比赛中的主要事件，每行一个。具体事件包括：

- 每次一支队伍得分时，你需要输出 `t RED GOAL` 或 `t BLUE GOAL`，取决于哪支队伍得分，其中 `t` 是当前动作位置（从0开始计数）。如果球员进错门（红队球员进红队球门，或蓝队球员进蓝队球门），则输出获分的另一队伍。
- 每次有球员被淘汰时，输出 `t p ELIMINATED`，其中 `t` 是当前时间 `p` 是被淘汰的球员。球员的格式与输入相同。

事件按 `t` 的升序输出。如果多名球员同时被淘汰，按字母顺序输出：`B0`, ..., `B9`, `R0`, ... `R9`。

比赛结束时，输出最终比分为：`FINAL SCORE: r b`，其中 `r` 和 `b` 分别是红队和蓝队的得分。

## 说明/提示

在第一个例子中，红队球员拿起鬼飞球，移动并投出。蓝队球员接住球，向红队球门进攻并取得分数。

在第二个例子中，红队球员拿球并不小心把它投入自家球门，结果蓝队得分。

在第三个例子中，游走球移动到 `R0` 的位置，导致 `R0` 被淘汰。随后，`B0` 也移到游走球的位置，结果 `B0` 也被淘汰。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
12
R0 D
R0 C .Q
R0 R
R0 T
R0 D
B0 R
B0 U
B0 C .Q
B0 L
B0 L
B0 L
B0 T
```

### 输出

```
11 BLUE GOAL
FINAL SCORE: 0 1
```

## 样例 #2

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
5
R0 D
R0 C .Q
R0 L
R0 L
R0 T
```

### 输出

```
4 BLUE GOAL
FINAL SCORE: 0 1
```

## 样例 #3

### 输入

```
5 5
.. .. .. .. ..
.. .. .. .. ..
RG R0 .Q B0 BG
.. .. .. .. ..
.. .. .B .. ..
5
.B L
.B U
.B U
B0 L
B0 L
```

### 输出

```
2 R0 ELIMINATED
4 B0 ELIMINATED
FINAL SCORE: 0 0
```



---

---
title: "Playing Quidditch (Hard)"
layout: "post"
diff: 普及+/提高
pid: CF1970F3
tag: ['模拟']
---

# Playing Quidditch (Hard)

## 题目描述

This afternoon, you decided to enjoy the first days of Spring by taking a walk outside. As you come near the Quidditch field, you hear screams. Once again, there is a conflict about the score: the two teams are convinced that they won the game! To prevent this problem from happening one more time, you decide to get involved in the refereeing of the matches.

Now, you will stay in the stadium to watch the game and count the score. At the end of the game, you will decide the winner.

Today, two teams are competing: the red Gryffindor (R) and the blue Ravenclaw (B) team. Each team is composed of $ P $ players ( $ 1 \leq P \leq 10 $ ).

The field is a rectangle of $ N $ lines and $ M $ columns ( $ 3 \leq N, M \leq 99 $ , $ N $ and $ M $ are odd). All the positions are integers, and several entities are allowed to be at the same position in the field. At the beginning of the game, the field contains goals for the two teams (each team can own between one and five goals), the players, and exactly one Quaffle. In this version of the problem, one Bludger and a Golden Snitch can be present.

A game is composed of $ T $ steps ( $ 0 \leq T \leq 10000 $ ). At each step, one entity on the field (a player or a ball) performs one action. All entities can move. A player can also catch a ball or throw the Quaffle that it is carrying. To catch a ball, a player must be located on the same cell as it. The Quaffle does not perform any action while it is being carried; it only follows the movements of the player. If a player carrying the Quaffle decides to throw it, the Quaffle is simply put at the current position of the player. If a player is on the same cell as a Bludger (either after a movement from the player or the Bludger), the player is eliminated. If the player is eliminated while it is carrying the Quaffle, the Quaffle remains on the cell containing both the player and the Bludger after the move. It is guaranteed that this never occurs while the player is in a cell containing a goal.

To win a point, a player must leave the Quaffle at a goal of the other team. When it does, the team of the player wins one point, and the Quaffle instantly moves to the middle of the field (the cell at the $ (M+1)/2 $ -th column of the $ (N+1)/2 $ -th line of the field, starting from 1). There is no goal in the middle of the field. If a player puts the ball in its own goal, the other team wins the point. If a player catches the Golden Snitch, their team wins 10 points and the game is over.

## 输入格式

On the first line, the integers $ N $ and $ M $ .

The description of the field follows: $ N $ lines of $ M $ pairs of characters separated by spaces. Each pair of characters represents a position on the field. It can be either:

- .. to represent an empty cell
- R0, ..., R9, B0, ..., B9 to represent a player. The first character is the team of the player, and the second is the number of the player in the team. Each pair of characters is unique, but it is not guaranteed that all the pairs appear in the grid.
- RG or BG to represent a goal. The blue team tries to put the ball in a red goal (RG) while the red team tries to put the ball in a blue goal (BG).
- .Q to represent the Quaffle, which is the ball that the players use to score goals.
- .B to represent the Bludger.
- .S to represent the Golden Snitch.

The next line contains $ T $ , the number of steps that compose the game. $ T $ lines follow, each describing one action. It contains several pieces of information separated by a space. First, a pair of characters representing the entity that must perform the action. Second, the description of the action:

- U, D, L, R indicate that the entity moves on the grid. It can move to the top of the grid (U), to the bottom (D), to the left (L), or to the right (R). Each entity moves by only one cell at a time.
- C indicates that the player catches the ball (only a player can catch a ball). Then, there is a space followed by a pair of characters: the description of the ball caught by the player. This information is needed since several balls can be in the same cell.
- T indicates that the player throws the Quaffle that it is carrying.

All the actions performed by the entities are guaranteed to be valid: the players stay in the field, don't catch a ball if they are not in the same cell, don't release the Quaffle if they are not carrying it, ...

## 输出格式

You must output the description of the main events of the game, one event per line. More precisely:

- Each time a team scores, you must print t RED GOAL or t BLUE GOAL, depending on the team who scored, where t is the current time (the position of the action in the list of actions, starting from 0). In the case where a player scores in the wrong goal (a red player scores in the red goal, or a blue player scores in the blue goal), you must print the name of the team who wins one point, that is, the other team.
- Each time a player is eliminated, you must print t p ELIMINATED, where t is the current time and p is the player who is eliminated. The format to print the player is the same as in the input.
- If the Golden Snitch is caught, you must print t RED CATCH GOLDEN SNITCH or t BLUE CATCH GOLDEN SNITCH, depending on the team who caught the Golden Snitch, where t is the current time.

The events must be printed in ascending order of t. If several players are eliminated at the same time, the events must be written is alphabetical order: B0, ..., B9, R0, ... R9.

At the end of the game, you must print the final score as: FINAL SCORE: r b, where r is the score of the red team and b is the score of the blue team.

## 说明/提示

In the first example, the red player takes the Quaffle, move it and throw it. The blue player catches the ball, goes to the red goal and scores.

In the second example, the red player takes the ball and scores in the goal of their own team: the blue team wins a point.

In the third example, the Bludger goes at the position of R0: R0 is eliminated. Then, B0 moves to the position of the Bludger: B0 is eliminated too.

In the fourth example, a red player catches the Golden Snitch. Their team wins 10 points, and the game ends.

You can find one more example in the easy version of the problem

## 样例 #1

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
12
R0 D
R0 C .Q
R0 R
R0 T
R0 D
B0 R
B0 U
B0 C .Q
B0 L
B0 L
B0 L
B0 T
```

### 输出

```
11 BLUE GOAL
FINAL SCORE: 0 1
```

## 样例 #2

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
5
R0 D
R0 C .Q
R0 L
R0 L
R0 T
```

### 输出

```
4 BLUE GOAL
FINAL SCORE: 0 1
```

## 样例 #3

### 输入

```
5 5
.. .. .. .. ..
.. .. .. .. ..
RG R0 .Q B0 BG
.. .. .. .. ..
.. .. .B .. ..
5
.B L
.B U
.B U
B0 L
B0 L
```

### 输出

```
2 R0 ELIMINATED
4 B0 ELIMINATED
FINAL SCORE: 0 0
```

## 样例 #4

### 输入

```
5 5
.. R0 .S B0 ..
.. .. .. .. ..
RG .. .Q .. BG
.. .. .. .. ..
.. R1 .B B1 ..
4
.S D
R0 D
R0 R
R0 C .S
```

### 输出

```
3 RED CATCH GOLDEN SNITCH
FINAL SCORE: 10 0
```



---

---
title: "Mirror Maze"
layout: "post"
diff: 普及+/提高
pid: CF2045M
tag: ['模拟', '深度优先搜索 DFS']
---

# Mirror Maze

## 题目描述

# 镜子迷宫


给定一个有\(R\)行（从北到南编号为\(1\)到\(R\)）和\(C\)列（从西到东编号为\(1\)到\(C\)）的网格。这个网格中的每个方格大小相同。位于第\(r\)行和第\(c\)列的方格表示为\((r,c)\)。每个方格要么为空，要么在方格的一条对角线上有一面镜子。每面镜子由一条线段表示。如果镜子是从西南角到东北角斜着放置的，则为\(1\)型镜子；如果是另一条对角线方向，则为\(2\)型镜子。

这些镜子遵循反射定律，即反射角等于入射角。正式地说，对于\(1\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的西、东、北和南方向。类似地，对于\(2\)型镜子，如果一束光线从方格的北、南、西或东方向射入，那么它将分别被反射到方格的东、西、南和北方向。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/5f7b63f0fb5656735a6c59d6b7204c8e210c6d4c.png)你想要在网格外放置一个激光发射器，使得激光束能击中所有的镜子。有\(2\cdot(R + C)\)个可能放置激光发射器的位置：

- 从网格北侧的第\(c\)列（\(1\leq c\leq C\)），向南发射激光束；
- 从网格南侧的第\(c\)列（\(1\leq c\leq C\)），向北发射激光束；
- 从网格东侧的第\(r\)行（\(1\leq r\leq R\)），向西发射激光束；
- 从网格西侧的第\(r\)行（\(1\leq r\leq R\)），向东发射激光束。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/29c68e47c3b155b917aa2d4237fa93819b498fc4.png)确定所有可能放置激光发射器的位置，使得激光束能击中所有的镜子。

## 输入格式

第一行包含两个整数\(R\)和\(C\)（\(1\leq R,C\leq200\)）。

接下来的\(R\)行，每行包含一个长度为\(C\)的字符串\(S_r\)。字符串\(S_r\)的第\(c\)个字符表示方格\((r,c)\)。每个字符可以是“.”（如果方格为空）、“/”（如果方格有\(1\)型镜子）或者“\”（如果方格有\(2\)型镜子）。网格中至少有一面镜子。

## 输出格式

输出一个整数，表示能使激光束击中所有镜子的激光发射器的可能放置位置的数量，记为\(k\)。

如果\(k>0\)，则输出\(k\)个用空格分隔的字符串，表示激光发射器的位置。每个字符串由一个字符和一个紧跟其后的整数组成，中间没有空格。这个字符表示网格的边，如果将激光发射器放在网格的北、南、东或西边，则字符分别为\(N\)、\(S\)、\(E\)或\(W\)。这个整数表示行/列编号。你可以按任意顺序输出这些字符串。

## 说明/提示

样例输入/输出 #1的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/e36d02e4bf94a08c27da9c9fd00e9bc42d7a4647.png)样例输入/输出 #2的解释

下面的图示展示了这个样例的一个解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045M/35fe527ce8ee213e9ba2c6ba34c9f6c589c7585c.png)

## 样例 #1

### 输入

```
4 4
.//.
.\\.
.\/.
....
```

### 输出

```
2
N3 W2
```

## 样例 #2

### 输入

```
4 6
./..\.
.\...\
./../\
......
```

### 输出

```
2
E3 S2
```

## 样例 #3

### 输入

```
4 4
....
./\.
.\/.
....
```

### 输出

```
0
```



---

---
title: "Greg and Friends"
layout: "post"
diff: 普及+/提高
pid: CF295C
tag: ['模拟', '动态规划 DP', '枚举']
---

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 输入格式

The first line contains two integers $ n $ , $ k $ $ (1<=n<=50,1<=k<=5000) $ — the number of people, including Greg, and the boat's weight limit. The next line contains $ n $ integers — the people's weights. A person's weight is either $ 50 $ kilos or $ 100 $ kilos.

You can consider Greg and his friends indexed in some way.

## 输出格式

In the first line print an integer — the minimum number of rides. If transporting everyone to the other bank is impossible, print an integer -1.

In the second line print the remainder after dividing the number of ways to transport the people in the minimum number of rides by number $ 1000000007 $ $ (10^{9}+7) $ . If transporting everyone to the other bank is impossible, print integer $ 0 $ .

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3 100
50 50 100

```

### 输出

```
5
2

```

## 样例 #3

### 输入

```
2 50
50 50

```

### 输出

```
-1
0

```



---

---
title: "Chocolate"
layout: "post"
diff: 普及+/提高
pid: CF31D
tag: ['模拟', '排序']
---

# Chocolate

## 题目描述

Bob has a rectangular chocolate bar of the size $ W×H $ . He introduced a cartesian coordinate system so that the point $ (0,0) $ corresponds to the lower-left corner of the bar, and the point $ (W,H) $ corresponds to the upper-right corner. Bob decided to split the bar into pieces by breaking it. Each break is a segment parallel to one of the coordinate axes, which connects the edges of the bar. More formally, each break goes along the line $ x=x_{c} $ or $ y=y_{c} $ , where $ x_{c} $ and $ y_{c} $ are integers. It should divide one part of the bar into two non-empty parts. After Bob breaks some part into two parts, he breaks the resulting parts separately and independently from each other. Also he doesn't move the parts of the bar. Bob made $ n $ breaks and wrote them down in his notebook in arbitrary order. At the end he got $ n+1 $ parts. Now he wants to calculate their areas. Bob is lazy, so he asks you to do this task.

## 输入格式

The first line contains 3 integers $ W $ , $ H $ and $ n $ ( $ 1<=W,H,n<=100 $ ) — width of the bar, height of the bar and amount of breaks. Each of the following $ n $ lines contains four integers $ x_{i,1},y_{i,1},x_{i,2},y_{i,2} $ — coordinates of the endpoints of the $ i $ -th break ( $ 0<=x_{i,1}<=x_{i,2}<=W,0<=y_{i,1}<=y_{i,2}<=H $ , or $ x_{i,1}=x_{i,2} $ , or $ y_{i,1}=y_{i,2} $ ). Breaks are given in arbitrary order.

It is guaranteed that the set of breaks is correct, i.e. there is some order of the given breaks that each next break divides exactly one part of the bar into two non-empty parts.

## 输出格式

Output $ n+1 $ numbers — areas of the resulting parts in the increasing order.

## 样例 #1

### 输入

```
2 2 2
1 0 1 2
0 1 1 1

```

### 输出

```
1 1 2 
```

## 样例 #2

### 输入

```
2 2 3
1 0 1 2
0 1 1 1
1 1 2 1

```

### 输出

```
1 1 1 1 
```

## 样例 #3

### 输入

```
2 4 2
0 1 2 1
0 3 2 3

```

### 输出

```
2 2 4 
```



---

---
title: "Minesweeper 1D"
layout: "post"
diff: 普及+/提高
pid: CF404D
tag: ['模拟', '动态规划 DP']
---

# Minesweeper 1D

## 题目描述

Game "Minesweeper 1D" is played on a line of squares, the line's height is 1 square, the line's width is $ n $ squares. Some of the squares contain bombs. If a square doesn't contain a bomb, then it contains a number from 0 to 2 — the total number of bombs in adjacent squares.

For example, the correct field to play looks like that: 001\*2\*\*\*101\*. The cells that are marked with "\*" contain bombs. Note that on the correct field the numbers represent the number of bombs in adjacent cells. For example, field 2\* is not correct, because cell with value 2 must have two adjacent cells with bombs.

Valera wants to make a correct field to play "Minesweeper 1D". He has already painted a squared field with width of $ n $ cells, put several bombs on the field and wrote numbers into some cells. Now he wonders how many ways to fill the remaining cells with bombs and numbers are there if we should get a correct field in the end.

## 输入格式

The first line contains sequence of characters without spaces $ s_{1}s_{2}...\ s_{n} $ $ (1<=n<=10^{6}) $ , containing only characters "\*", "?" and digits "0", "1" or "2". If character $ s_{i} $ equals "\*", then the $ i $ -th cell of the field contains a bomb. If character $ s_{i} $ equals "?", then Valera hasn't yet decided what to put in the $ i $ -th cell. Character $ s_{i} $ , that is equal to a digit, represents the digit written in the $ i $ -th square.

## 输出格式

Print a single integer — the number of ways Valera can fill the empty cells and get a correct field.

As the answer can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first test sample you can get the following correct fields: 001\*\*1, 001\*\*\*, 001\*2\*, 001\*10.

## 样例 #1

### 输入

```
?01???

```

### 输出

```
4

```

## 样例 #2

### 输入

```
?

```

### 输出

```
2

```

## 样例 #3

### 输入

```
**12

```

### 输出

```
0

```

## 样例 #4

### 输入

```
1

```

### 输出

```
0

```



---

---
title: "Present"
layout: "post"
diff: 普及+/提高
pid: CF460C
tag: ['模拟', '线段树', '差分']
---

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 输入格式

The first line contains space-separated integers $ n $ , $ m $ and $ w $ $ (1<=w<=n<=10^{5}; 1<=m<=10^{5}) $ . The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the maximum final height of the smallest flower.

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 5 1
5 8

```

### 输出

```
9

```



---

---
title: "Crossword"
layout: "post"
diff: 普及+/提高
pid: CF47C
tag: ['模拟']
---

# Crossword

## 题目描述

Vasya trains to compose crossword puzzles. He can only compose crosswords of a very simplе type so far. All of them consist of exactly six words; the words can be read only from top to bottom vertically and from the left to the right horizontally. The words are arranged in the form of a rectangular "eight" or infinity sign, not necessarily symmetrical.

The top-left corner of the crossword coincides with the top-left corner of the rectangle. The same thing is correct for the right-bottom corners. The crossword can't degrade, i.e. it always has exactly four blank areas, two of which are surrounded by letters. Look into the output for the samples for clarification.

Help Vasya — compose a crossword of the described type using the given six words. It is allowed to use the words in any order.

## 输入格式

Six lines contain the given words. Every word consists of no more than 30 and no less than 3 uppercase Latin letters.

## 输出格式

If it is impossible to solve the problem, print Impossible. Otherwise, print the sought crossword. All the empty squares should be marked as dots.

If there can be several solutions to that problem, print the lexicographically minimum one. I.e. the solution where the first line is less than the first line of other solutions should be printed. If the two lines are equal, compare the second lines and so on. The lexicographical comparison of lines is realized by the < operator in the modern programming languages.

## 样例 #1

### 输入

```
NOD
BAA
YARD
AIRWAY
NEWTON
BURN

```

### 输出

```
BAA...
U.I...
R.R...
NEWTON
..A..O
..YARD

```

## 样例 #2

### 输入

```
AAA
AAA
AAAAA
AAA
AAA
AAAAA

```

### 输出

```
AAA..
A.A..
AAAAA
..A.A
..AAA

```

## 样例 #3

### 输入

```
PTC
JYNYFDSGI
ZGPPC
IXEJNDOP
JJFS
SSXXQOFGJUZ

```

### 输出

```
JJFS....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
IXEJNDOP
...U...T
...ZGPPC

```



---

---
title: "Peter and Snow Blower"
layout: "post"
diff: 普及+/提高
pid: CF613A
tag: ['模拟', '数学', '构造']
---

# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 输入格式

The first line of the input contains three integers — the number of vertices of the polygon $ n $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/e07eddcf01ea19e02be99447a5d31677c12c0459.png)), and coordinates of point $ P $ .

Each of the next $ n $ lines contains two integers — coordinates of the vertices of the polygon in the clockwise or counterclockwise order. It is guaranteed that no three consecutive vertices lie on a common straight line.

All the numbers in the input are integers that do not exceed $ 1000000 $ in their absolute value.

## 输出格式

Print a single real value number — the area of the region that will be cleared. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2

```

### 输出

```
12.566370614359172464

```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1

```

### 输出

```
21.991148575128551812

```



---

---
title: "New Year and Rating"
layout: "post"
diff: 普及+/提高
pid: CF750C
tag: ['模拟']
---

# New Year and Rating

## 题目描述

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating $ 1900 $ or higher. Those with rating $ 1899 $ or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in $ n $ contests in the year 2016. He remembers that in the $ i $ -th contest he competed in the division $ d_{i} $ (i.e. he belonged to this division just before the start of this contest) and his rating changed by $ c_{i} $ just after the contest. Note that negative $ c_{i} $ denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all $ n $ contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ).

The $ i $ -th of next $ n $ lines contains two integers $ c_{i} $ and $ d_{i} $ ( $ -100<=c_{i}<=100 $ , $ 1<=d_{i}<=2 $ ), describing Limak's rating change after the $ i $ -th contest and his division during the $ i $ -th contest contest.

## 输出格式

If Limak's current rating can be arbitrarily big, print "Infinity" (without quotes). If the situation is impossible, print "Impossible" (without quotes). Otherwise print one integer, denoting the maximum possible value of Limak's current rating, i.e. rating after the $ n $ contests.

## 说明/提示

In the first sample, the following scenario matches all information Limak remembers and has maximum possible final rating:

- Limak has rating $ 1901 $ and belongs to the division $ 1 $ in the first contest. His rating decreases by $ 7 $ .
- With rating $ 1894 $ Limak is in the division $ 2 $ . His rating increases by $ 5 $ .
- Limak has rating $ 1899 $ and is still in the division $ 2 $ . In the last contest of the year he gets $ +8 $ and ends the year with rating $ 1907 $ .

In the second sample, it's impossible that Limak is in the division $ 1 $ , his rating increases by $ 57 $ and after that Limak is in the division $ 2 $ in the second contest.

## 样例 #1

### 输入

```
3
-7 1
5 2
8 2

```

### 输出

```
1907

```

## 样例 #2

### 输入

```
2
57 1
22 2

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
1
-5 1

```

### 输出

```
Infinity

```

## 样例 #4

### 输入

```
4
27 2
13 1
-50 1
8 2

```

### 输出

```
1897

```



---

---
title: "Twisted Circuit"
layout: "post"
diff: 普及+/提高
pid: CF784E
tag: ['模拟', '位运算']
---

# Twisted Circuit

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF784E/03bc9ecd826bed4c1045a0a976af29d4edaea871.png)

## 输入格式

The input consists of four lines, each line containing a single digit 0 or 1.

## 输出格式

Output a single digit, 0 or 1.

## 样例 #1

### 输入

```
0
1
1
0

```

### 输出

```
0

```



---

---
title: "Memory Manager"
layout: "post"
diff: 普及+/提高
pid: CF7B
tag: ['模拟']
---

# Memory Manager

## 题目描述

第一个国家级操作系统——BerlOS就要发布了。但是，它的一些功能还没有完善，比如内存管理系统。在开发者的计划里，第一版里的内存管理系统是简单并且是线性的。它将会支持以下操作：

    alloc n —— 在内存中分配n字节的空间。此命令将返回已分配的内存块的编号x。

    erase x —— 释放编号为x的内存块。
    defragment —— 碎片整理，将所有内存块全部向内存的起点靠拢并且不改变它们的顺序。

整条内存一共有m个字节，每个字节依次编号为1,2,...,m。

操作 alloc 有一个参数n，表示需要分配n字节大小的内存块。在执行这个操作时，系统将把一块最靠近内存起点的，长度为n的连续空闲字节分配到一个内存块（这块内存块内的所有字节将被标记为“已使用”）。这个操作的返回值为这块内存块的编号。如果没有符合条件的内存块，返回 NULL 。

操作 erase 有一个参数x，表示需要释放的内存块的编号。它将释放这个内存块（这块内存块内的所有字节将被标记为“空闲”）。如果成功释放，不返回值；如果编号为x的内存块不存在，返回 ILLEGAL\_ERASE\_ARGUMENT 。

操作 deflagment 没有任何参数。它只是将所有内存块向前依次（编号小的地方）挪动直到它们紧挨在一起。（不改变它们的顺序）

你将用连续的正整数（1,2,...）作为每一个内存块的编号。比如，第i次分配的内存块编号为i。你的任务是依次输出所有 alloc 指令的返回值，以及所有执行失败的 erase 指令的返回值。

## 输入格式

输入文件的第一行包括两个正整数 t 和 m 。 t 表示操作次数， m 表示内存大小（为m字节）。接下来的t行为每一次的命令。命令有以下三种：alloc 命令，后接一个整数 n ； erase 命令，后接一个整数 x ； defragment 命令。

## 输出格式

输出文件的每一行依次为每次执行的 alloc 函数的返回值或执行失败的 erase 函数返回的 ILLEGAL\_ERASE\_ARGUMENT 。

translated by 星烁晶熠辉

## 样例 #1

### 输入

```
6 10
alloc 5
alloc 3
erase 1
alloc 6
defragment
alloc 6

```

### 输出

```
1
2
NULL
3

```



---

---
title: "String Reconstruction"
layout: "post"
diff: 普及+/提高
pid: CF827A
tag: ['模拟', '字符串', '并查集']
---

# String Reconstruction

## 题目描述

Ivan有一个只包含小写英文字母的字符串s。然而他的朋友Julia为了捉弄他藏起了字符串s。

相比起找回原来的字符串，Ivan更倾向于造一个新的。

 

Ivan知道一些有关于字符串s的信息。这意味着他记得字符串$t_{i}$在字符串s中至少出现了$k_{i}$次，以及$k_{i}$个$t_{i}$在s中出现的位置--$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$。他记得n个这样的字符串$t_{i}$。



 你要重建出一个符合Ivan记得的所有信息的字符串，如果有多个答案符合要求，取字典序最小的一个。字符串$t_{i}$只包含小写字母。

## 输入格式

第一行包括一个整数n(1<=n<=$10^{5}$),代表了Ivan所记得的字符串数量。



下面的n行包括有关于这些字符串的信息。第i+1包括一个非空字符串$t_{i}$，一个正整数$k_{i}$(代表了$t_{i}$在字符串s中出现的次数)，然后是$k_{i}$个正整数$x_{i,1}$，$x_{i,2}$，$x_{i,3}$，$x_{i,4}$，…，$x_{i,k_{i}}$（升序输入），代表了$t_{i}$在字符串s中出现的起始位置。



保证字符串$t_{i}$的长度之和不超过$10^{6}$，1<=$x_{i,j}$<=$10^{6}$，1<=$k_{i}$<=$10^{6}$，且$k_{i}$的和不超过$10^{6}$。可能存在相同的$t_{i}$。



数据保证一定有解。

## 输出格式

输出满足条件的字典序最小的字符串。

## 样例 #1

### 输入

```
3
a 4 1 3 5 7
ab 2 1 5
ca 1 4

```

### 输出

```
abacaba

```

## 样例 #2

### 输入

```
1
a 1 3

```

### 输出

```
aaa

```

## 样例 #3

### 输入

```
3
ab 1 1
aba 1 3
ab 2 3 5

```

### 输出

```
ababab

```



---

---
title: "Rooter's Song"
layout: "post"
diff: 普及+/提高
pid: CF848B
tag: ['模拟']
---

# Rooter's Song

## 题目描述

Wherever the destination is, whoever we meet, let's render this song together.

On a Cartesian coordinate plane lies a rectangular stage of size $ w×h $ , represented by a rectangle with corners $ (0,0) $ , $ (w,0) $ , $ (w,h) $ and $ (0,h) $ . It can be seen that no collisions will happen before one enters the stage.

On the sides of the stage stand $ n $ dancers. The $ i $ -th of them falls into one of the following groups:

- Vertical: stands at $ (x_{i},0) $ , moves in positive $ y $ direction (upwards);
- Horizontal: stands at $ (0,y_{i}) $ , moves in positive $ x $ direction (rightwards).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/78a4617a270ecba0555a87f4deb825cf1f501330.png)According to choreography, the $ i $ -th dancer should stand still for the first $ t_{i} $ milliseconds, and then start moving in the specified direction at $ 1 $ unit per millisecond, until another border is reached. It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

When two dancers collide (i.e. are on the same point at some time when both of them are moving), they immediately exchange their moving directions and go on.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/14a342567b0e0e96e2854bafb4e39a8b293ebae4.png)Dancers stop when a border of the stage is reached. Find out every dancer's stopping position.

## 输入格式

The first line of input contains three space-separated positive integers $ n $ , $ w $ and $ h $ ( $ 1<=n<=100000 $ , $ 2<=w,h<=100000 $ ) — the number of dancers and the width and height of the stage, respectively.

The following $ n $ lines each describes a dancer: the $ i $ -th among them contains three space-separated integers $ g_{i} $ , $ p_{i} $ , and $ t_{i} $ ( $ 1<=g_{i}<=2 $ , $ 1<=p_{i}<=99999 $ , $ 0<=t_{i}<=100000 $ ), describing a dancer's group $ g_{i} $ ( $ g_{i}=1 $ — vertical, $ g_{i}=2 $ — horizontal), position, and waiting time. If $ g_{i}=1 $ then $ p_{i}=x_{i} $ ; otherwise $ p_{i}=y_{i} $ . It's guaranteed that $ 1<=x_{i}<=w-1 $ and $ 1<=y_{i}<=h-1 $ . It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

## 输出格式

Output $ n $ lines, the $ i $ -th of which contains two space-separated integers $ (x_{i},y_{i}) $ — the stopping position of the $ i $ -th dancer in the input.

## 说明/提示

The first example corresponds to the initial setup in the legend, and the tracks of dancers are marked with different colours in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/d441e2a826ff927d107333215574de12d2f00a07.png)In the second example, no dancers collide.

## 样例 #1

### 输入

```
8 10 8
1 1 10
1 4 13
1 7 1
1 8 2
2 2 0
2 5 14
2 6 0
2 6 1

```

### 输出

```
4 8
10 5
8 8
10 6
10 2
1 8
7 8
10 6

```

## 样例 #2

### 输入

```
3 2 3
1 1 2
2 1 1
1 1 5

```

### 输出

```
1 3
2 1
1 3

```



---

