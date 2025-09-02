---
title: "Creating the Contest"
layout: "post"
diff: 普及-
pid: CF1029B
tag: ['贪心', '单调队列', '队列']
---

# Creating the Contest

## 题目描述

你有一个包含 $ n $ 个问题的问题集，其中第 $ i $ 个问题的难度为 $ a_i $ ，保证没有难度相同的两个问题，且问题难度按照递增顺序给出。

你需要在这个问题集中取一个子集（不要求问题的顺序连续），满足以下条件：对于每道题目，在该子集中不存在难度超过该问题难度2倍的题目。（仅包含一个问题的子集也是合法的）

求出这个子集最多能包含多少个问题。

## 输入格式

第一行输入一个整数 $ n $ 。

下一行按照递增顺序输入 $ n $ 个整数，其中第 $ i $ 个整数 $ a_i $ 代表问题 $ i $ 的难度。

## 输出格式

输出一个整数，即该子集最多包含的问题数目。

## 样例 #1

### 输入

```
10
1 2 5 6 7 10 21 23 24 49

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
2 10 50 110 250

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6
4 7 12 100 150 199

```

### 输出

```
3

```



---

---
title: "Permutation Minimization by Deque"
layout: "post"
diff: 普及-
pid: CF1579E1
tag: ['模拟', '队列']
---

# Permutation Minimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

A permutation $ p $ of size $ n $ is given. A permutation of size $ n $ is an array of size $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 4, 3, 2] $ and $ [4, 2, 1, 3] $ are correct permutations while $ [1, 2, 4] $ and $ [1, 2, 2] $ are not.

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [1, 5, 2] $ currently in the deque, adding an element $ 4 $ to the beginning will produce the sequence $ [\color{red}{4}, 1, 5, 2] $ , and adding same element to the end will produce $ [1, 5, 2, \color{red}{4}] $ .

The elements of the permutation are sequentially added to the initially empty deque, starting with $ p_1 $ and finishing with $ p_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or the end.

For example, if we consider a permutation $ p = [3, 1, 2, 4] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the end of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 1 $ to the beginning of the deque:deque has a sequence $ [\color{red}{1}, 3] $ in it; $ \quad $ 3.add $ 2 $ to the end of the deque:deque has a sequence $ [1, 3, \color{red}{2}] $ in it; $ \quad $ 4.add $ 4 $ to the end of the deque:deque has a sequence $ [1, 3, 2, \color{red}{4}] $ in it;Find the lexicographically smallest possible sequence of elements in the deque after the entire permutation has been processed.

A sequence $ [x_1, x_2, \ldots, x_n] $ is lexicographically smaller than the sequence $ [y_1, y_2, \ldots, y_n] $ if there exists such $ i \leq n $ that $ x_1 = y_1 $ , $ x_2 = y_2 $ , $ \ldots $ , $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ . In other words, if the sequences $ x $ and $ y $ have some (possibly empty) matching prefix, and the next element of the sequence $ x $ is strictly smaller than the corresponding element of the sequence $ y $ . For example, the sequence $ [1, 3, 2, 4] $ is smaller than the sequence $ [1, 3, 4, 2] $ because after the two matching elements $ [1, 3] $ in the start the first sequence has an element $ 2 $ which is smaller than the corresponding element $ 4 $ in the second sequence.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The next $ 2t $ lines contain descriptions of the test cases.

The first line of each test case description contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — permutation size. The second line of the description contains $ n $ space-separated integers $ p_i $ ( $ 1 \le p_i \le n $ ; all $ p_i $ are all unique) — elements of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print $ t $ lines, each line containing the answer to the corresponding test case. The answer to a test case should contain $ n $ space-separated integer numbers — the elements of the lexicographically smallest permutation that is possible to find in the deque after executing the described algorithm.

## 说明/提示

One of the ways to get a lexicographically smallest permutation $ [1, 3, 2, 4] $ from the permutation $ [3, 1, 2, 4] $ (the first sample test case) is described in the problem statement.

## 样例 #1

### 输入

```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1
```

### 输出

```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2
```



---

---
title: "Queue at the School"
layout: "post"
diff: 普及-
pid: CF266B
tag: ['字符串', '搜索', '队列']
---

# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 输入格式

The first line contains two integers $ n $ and $ t $ $ (1<=n,t<=50) $ , which represent the number of children in the queue and the time after which the queue will transform into the arrangement you need to find.

The next line contains string $ s $ , which represents the schoolchildren's initial arrangement. If the $ i $ -th position in the queue contains a boy, then the $ i $ -th character of string $ s $ equals "B", otherwise the $ i $ -th character equals "G".

## 输出格式

Print string $ a $ , which describes the arrangement after $ t $ seconds. If the $ i $ -th position has a boy after the needed time, then the $ i $ -th character $ a $ must equal "B", otherwise it must equal "G".

## 样例 #1

### 输入

```
5 1
BGGBG

```

### 输出

```
GBGGB

```

## 样例 #2

### 输入

```
5 2
BGGBG

```

### 输出

```
GGBGB

```

## 样例 #3

### 输入

```
4 1
GGGB

```

### 输出

```
GGGB

```



---

---
title: "Before an Exam"
layout: "post"
diff: 普及-
pid: CF4B
tag: ['贪心', '优先队列', '前缀和']
---

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 输入格式

The first input line contains two integer numbers $ d,sumTime $ ( $ 1<=d<=30,0<=sumTime<=240 $ ) — the amount of days, during which Peter studied, and the total amount of hours, spent on preparation. Each of the following $ d $ lines contains two integer numbers $ minTime_{i},maxTime_{i} $ ( $ 0<=minTime_{i}<=maxTime_{i}<=8 $ ), separated by a space — minimum and maximum amount of hours that Peter could spent in the $ i $ -th day.

## 输出格式

In the first line print YES, and in the second line print $ d $ numbers (separated by a space), each of the numbers — amount of hours, spent by Peter on preparation in the corresponding day, if he followed his parents' instructions; or print NO in the unique line. If there are many solutions, print any of them.

## 样例 #1

### 输入

```
1 48
5 7

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2 5
0 1
3 5

```

### 输出

```
YES
1 4 
```



---

---
title: "Queue"
layout: "post"
diff: 普及-
pid: CF545D
tag: ['贪心', '队列']
---

# Queue

## 题目描述

Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are $ n $ people in the queue. For each person we know time $ t_{i} $ needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ).

The next line contains $ n $ integers $ t_{i} $ ( $ 1<=t_{i}<=10^{9} $ ), separated by spaces.

## 输出格式

Print a single number — the maximum number of not disappointed people in the queue.

## 说明/提示

Value $ 4 $ is achieved at such an arrangement, for example: $ 1,2,3,5,15 $ . Thus, you can make everything feel not disappointed except for the person with time 5.

## 样例 #1

### 输入

```
5
15 2 1 5 3

```

### 输出

```
4

```



---

---
title: "Tea Queue"
layout: "post"
diff: 普及-
pid: CF920B
tag: ['模拟', '枚举', '队列']
---

# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=1000 $ ).

Then $ t $ test cases follow. The first line of each test case contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of students.

Then $ n $ lines follow. Each line contains two integer $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=5000 $ ) — the second $ i $ -th student comes to the end of the queue, and the second he leaves the queue if he still cannot get his tea.

It is guaranteed that for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920B/748ee9e1ae91d0e555bb85d14ee499f01d330017.png) condition $ l_{i-1}<=l_{i} $ holds.

The sum of $ n $ over all test cases doesn't exceed $ 1000 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print $ n $ integers. $ i $ -th of them must be equal to the second when $ i $ -th student gets his tea, or $ 0 $ if he leaves without tea.

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3

```

### 输出

```
1 2 
1 0 2 

```



---

---
title: "Hexadecimal's Numbers"
layout: "post"
diff: 普及-
pid: CF9C
tag: ['递归', '枚举', '进制', '队列']
---

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 输入格式

Input data contains the only number $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Output the only number — answer to the problem.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10

```

### 输出

```
2
```



---

