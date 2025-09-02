---
title: "Ray in the tube"
layout: "post"
diff: 省选/NOI-
pid: CF1041F
tag: ['模拟', '枚举']
---

# Ray in the tube

## 题目描述

### 题目大意：
下边界有$n$个给定点，上边界有$m$个给定点，可以从任意一个点发出一条激光，激光碰到边界会反射

激光到达边界必须打到整数点，问最多可以打到几个给定点

## 输入格式

第一行两个整数$n,y_1$，表示下边界给定点的个数和下边界的纵坐标

第二行$n$个整数，表示给定点的横坐标

第三行两个整数$m,y_2$，表示上边界给定点的个数和上边界的纵坐标

第四行$m$个整数，表示给定点的横坐标

## 输出格式

一个整数，表示最多能打到多少点

## 样例 #1

### 输入

```
3 1
1 5 6
1 3
3

```

### 输出

```
3

```



---

---
title: "Tape Programming"
layout: "post"
diff: 省选/NOI-
pid: CF238D
tag: ['模拟', '前缀和']
---

# Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ $ (1<=n,q<=10^{5}) $ — represents the length of the sequence $ s $ and the number of queries.

The second line contains $ s $ , a sequence of "<", ">" and digits (0..9) written from left to right. Note, that the characters of $ s $ are not separated with spaces.

The next $ q $ lines each contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ — the $ i $ -th query.

## 输出格式

For each query print $ 10 $ space separated integers: $ x_{0},x_{1},...,x_{9} $ where $ x_{i} $ equals the number of times the interpreter prints $ i $ while running the corresponding program. Print answers to the queries in the order they are given in input.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7
```

### 输出

```
0 1 0 1 0 0 0 0 0 0
2 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
2 3 2 1 0 0 0 0 0 0

```



---

---
title: "Dreamoon and Notepad"
layout: "post"
diff: 省选/NOI-
pid: CF477E
tag: ['模拟', '二分', 'ST 表', '分类讨论']
---

# Dreamoon and Notepad

## 题目描述

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输入格式

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 输出格式

For each query print the result of the query.

## 说明/提示

In the first sample, the first query can be solved with keys: HOME, right.

The second query can be solved with keys: down, down, down, END, down.

The third query can be solved with keys: down, END, down.

The fourth query can be solved with keys: END, down.

## 样例 #1

### 输入

```
9
1 3 5 3 1 3 5 3 1
4
3 5 3 1
3 3 7 3
1 0 3 3
6 0 7 3

```

### 输出

```
2
5
3
2

```

## 样例 #2

### 输入

```
2
10 5
1
1 0 1 5

```

### 输出

```
3

```



---

---
title: "Mr. Kitayuta vs. Bamboos"
layout: "post"
diff: 省选/NOI-
pid: CF505E
tag: ['模拟', '二分']
---

# Mr. Kitayuta vs. Bamboos

## 题目描述

Mr. Kitayuta's garden is planted with $ n $ bamboos. (Bamboos are tall, fast-growing tropical plants with hollow stems.) At the moment, the height of the $ i $ -th bamboo is $ h_{i} $ meters, and it grows $ a_{i} $ meters at the end of each day.

Actually, Mr. Kitayuta hates these bamboos. He once attempted to cut them down, but failed because their stems are too hard. Mr. Kitayuta have not given up, however. He has crafted Magical Hammer with his intelligence to drive them into the ground.

He can use Magical Hammer at most $ k $ times during each day, due to his limited Magic Power. Each time he beat a bamboo with Magical Hammer, its height decreases by $ p $ meters. If the height would become negative by this change, it will become $ 0 $ meters instead (it does not disappear). In other words, if a bamboo whose height is $ h $ meters is beaten with Magical Hammer, its new height will be $ max(0,h-p) $ meters. It is possible to beat the same bamboo more than once in a day.

Mr. Kitayuta will fight the bamboos for $ m $ days, starting today. His purpose is to minimize the height of the tallest bamboo after $ m $ days (that is, $ m $ iterations of "Mr. Kitayuta beats the bamboos and then they grow"). Find the lowest possible height of the tallest bamboo after $ m $ days.

## 输入格式

The first line of the input contains four space-separated integers $ n $ , $ m $ , $ k $ and $ p $ ( $ 1<=n<=10^{5},1<=m<=5000,1<=k<=10,1<=p<=10^{9} $ ). They represent the number of the bamboos in Mr. Kitayuta's garden, the duration of Mr. Kitayuta's fight in days, the maximum number of times that Mr. Kitayuta beat the bamboos during each day, and the power of Magic Hammer, respectively.

The following $ n $ lines describe the properties of the bamboos. The $ i $ -th of them ( $ 1<=i<=n $ ) contains two space-separated integers $ h_{i} $ and $ a_{i} $ ( $ 0<=h_{i}<=10^{9},1<=a_{i}<=10^{9} $ ), denoting the initial height and the growth rate of the $ i $ -th bamboo, respectively.

## 输出格式

Print the lowest possible height of the tallest bamboo after $ m $ days.

## 样例 #1

### 输入

```
3 1 2 5
10 10
10 10
15 2

```

### 输出

```
17

```

## 样例 #2

### 输入

```
2 10 10 1000000000
0 10
0 10

```

### 输出

```
10

```

## 样例 #3

### 输入

```
5 3 3 10
9 5
9 2
4 7
9 10
3 8

```

### 输出

```
14

```



---

---
title: "Arthur and Brackets"
layout: "post"
diff: 省选/NOI-
pid: CF508E
tag: ['模拟', '贪心', '栈']
---

# Arthur and Brackets

## 题目描述

你需要构造一个长为 $2n$ 的小括号序列 $S$，左、右括号各 $n$ 个。

对于从左到右的第 $i$ 个左括号 $S_a$，需要与其配对的右括号 $S_b$ 满足 $b - a \in [L_i, R_i]$。

## 输入格式

第一行一个正整数 $n ~ (1 \leq n \leq 600)$。

接下来的 $n$ 行，每行两个正整数 $L_i, R_i ~ (1 \leq L_i, R_i \leq 2n)$。

## 输出格式

如果可以构造 $S$，输出任意一种方案。

如果无法构造，输出 `IMPOSSIBLE`。

## 样例 #1

### 输入

```
4
1 1
1 1
1 1
1 1

```

### 输出

```
()()()()

```

## 样例 #2

### 输入

```
3
5 5
3 3
1 1

```

### 输出

```
((()))

```

## 样例 #3

### 输入

```
3
5 5
3 3
2 2

```

### 输出

```
IMPOSSIBLE

```

## 样例 #4

### 输入

```
3
2 3
1 4
1 4

```

### 输出

```
(())()

```



---

---
title: "Chess"
layout: "post"
diff: 省选/NOI-
pid: CF57E
tag: ['模拟', '搜索', '枚举']
---

# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 输入格式

The first line contains two integers $ k $ and $ n $ ( $ 0<=k<=10^{18},0<=n<=440 $ ) which are correspondingly the maximal number of moves a knight can make and the number of deleted cells. Then follow $ n $ lines, each giving the coordinates of a deleted square in the form $ (x_{i},y_{i}) $ ( $ |x_{i}|<=10,|y_{i}|<=10 $ ). All the numbers are integer, the deleted squares are different and it is guaranteed that the square $ (0,0) $ is not deleted.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
1 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1

```

### 输出

```
9

```



---

---
title: "Robot in Basement"
layout: "post"
diff: 省选/NOI-
pid: CF97D
tag: ['模拟']
---

# Robot in Basement

## 题目描述

The Professor has lost his home robot yet again. After some thinking Professor understood that he had left the robot in the basement.

The basement in Professor's house is represented by a rectangle $ n×m $ , split into $ 1×1 $ squares. Some squares are walls which are impassable; other squares are passable. You can get from any passable square to any other passable square moving through edge-adjacent passable squares. One passable square is the exit from the basement. The robot is placed exactly in one passable square. Also the robot may be placed in the exit square.

Professor is scared of going to the dark basement looking for the robot at night. However, he has a basement plan and the robot's remote control. Using the remote, Professor can send signals to the robot to shift one square left, right, up or down. When the robot receives a signal, it moves in the required direction if the robot's neighboring square in the given direction is passable. Otherwise, the robot stays idle.

Professor wrote a sequence of $ k $ commands on a piece of paper. He thinks that the sequence can lead the robot out of the basement, wherever it's initial position might be. Professor programmed another robot to press the required buttons on the remote according to the notes on the piece of paper. Professor was just about to run the program and go to bed, when he had an epiphany.

Executing each command takes some energy and Professor doesn't want to get huge electricity bill at the end of the month. That's why he wants to find in the sequence he has written out the minimal possible prefix that would guarantee to lead the robot out to the exit after the prefix is fulfilled. And that's the problem Professor challenges you with at this late hour.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 3<=n,m<=150 $ , $ 1<=k<=10^{5} $ ). Next $ n $ lines contain $ m $ characters each — that is the Professor's basement's description: "\#" stands for a wall, "." stands for a passable square and "E" stands for the exit from the basement (this square also is passable). It is possible to get from each passable square to the exit, all squares located by the $ n×m $ rectangle's perimeter are the walls. Exactly one square is the exit from the basement. The last line contains $ k $ characters, the description of the sequence of commands that Professor has written out on a piece of paper. "L", "R", "U", "D" stand for commands left, right, up and down correspondingly.

## 输出格式

Print in the output file the length of the smallest possible prefix that will lead the robot to the exit square. In other words, wherever the robot had been positioned initially, it should be positioned in the exit square after all the commands from the prefix are fulfilled (during doing commands the robot can come and leave the exit square, but only the last position of the robot is interesting for us). If Professor is mistaken and no prefix (including the whole sequence) can bring the robot to the exit, print "-1" (without the quotes). If there is the only passable square and it is the exit, print "0" (without the quotes).

## 样例 #1

### 输入

```
5 5 7
#####
#...#
#...#
#E..#
#####
UULLDDR

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5 5 7
#####
#.#.#
#...#
#E..#
#####
UULLDDR

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5 3 2
###
#.#
#.#
#E#
###
DD

```

### 输出

```
2

```



---

