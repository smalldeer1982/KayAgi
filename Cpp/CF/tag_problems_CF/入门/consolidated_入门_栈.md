---
title: "Doors and Keys"
layout: "post"
diff: 入门
pid: CF1644A
tag: ['模拟', '字符串', '栈']
---

# Doors and Keys

## 题目描述

The knight is standing in front of a long and narrow hallway. A princess is waiting at the end of it.

In a hallway there are three doors: a red door, a green door and a blue door. The doors are placed one after another, however, possibly in a different order. To proceed to the next door, the knight must first open the door before.

Each door can be only opened with a key of the corresponding color. So three keys: a red key, a green key and a blue key — are also placed somewhere in the hallway. To open the door, the knight should first pick up the key of its color.

The knight has a map of the hallway. It can be transcribed as a string, consisting of six characters:

- R, G, B — denoting red, green and blue doors, respectively;
- r, g, b — denoting red, green and blue keys, respectively.

Each of these six characters appears in the string exactly once.

The knight is standing at the beginning of the hallway — on the left on the map.

Given a map of the hallway, determine if the knight can open all doors and meet the princess at the end of the hallway.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 720 $ ) — the number of testcases.

Each testcase consists of a single string. Each character is one of R, G, B (for the doors), r, g, b (for the keys), and each of them appears exactly once.

## 输出格式

For each testcase, print YES if the knight can open all doors. Otherwise, print NO.

## 说明/提示

In the first testcase, the knight first collects all keys, then opens all doors with them.

In the second testcase, there is a red door right in front of the knight, but he doesn't have a key for it.

In the third testcase, the key to each door is in front of each respective door, so the knight collects the key and uses it immediately three times.

In the fourth testcase, the knight can't open the blue door.

## 样例 #1

### 输入

```
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "Splitting in Teams"
layout: "post"
diff: 入门
pid: CF899A
tag: ['模拟', '概率论', '栈']
---

# Splitting in Teams

## 题目描述

There were $ n $ groups of students which came to write a training contest. A group is either one person who can write the contest with anyone else, or two people who want to write the contest in the same team.

The coach decided to form teams of exactly three people for this training. Determine the maximum number of teams of three people he can form. It is possible that he can't use all groups to form teams. For groups of two, either both students should write the contest, or both should not. If two students from a group of two will write the contest, they should be in the same team.

## 输入格式

The first line contains single integer $ n $ ( $ 2<=n<=2·10^{5} $ ) — the number of groups.

The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=2 $ ), where $ a_{i} $ is the number of people in group $ i $ .

## 输出格式

Print the maximum number of teams of three people the coach can form.

## 说明/提示

In the first example the coach can form one team. For example, he can take students from the first, second and fourth groups.

In the second example he can't make a single team.

In the third example the coach can form three teams. For example, he can do this in the following way:

- The first group (of two people) and the seventh group (of one person),
- The second group (of two people) and the sixth group (of one person),
- The third group (of two people) and the fourth group (of one person).

## 样例 #1

### 输入

```
4
1 1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
7
2 2 2 1 1 1 1

```

### 输出

```
3

```

## 样例 #4

### 输入

```
3
1 1 1

```

### 输出

```
1

```



---

---
title: "Wrong Subtraction"
layout: "post"
diff: 入门
pid: CF977A
tag: ['模拟', '字符串', '栈']
---

# Wrong Subtraction

## 题目描述

Little girl Tanya is learning how to decrease a number by one, but she does it wrong with a number consisting of two or more digits. Tanya subtracts one from a number by the following algorithm:

- if the last digit of the number is non-zero, she decreases the number by one;
- if the last digit of the number is zero, she divides the number by 10 (i.e. removes the last digit).

You are given an integer number $ n $ . Tanya will subtract one from it $ k $ times. Your task is to print the result after all $ k $ subtractions.

It is guaranteed that the result will be positive integer number.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ , $ 1 \le k \le 50 $ ) — the number from which Tanya will subtract and the number of subtractions correspondingly.

## 输出格式

Print one integer number — the result of the decreasing $ n $ by one $ k $ times.

It is guaranteed that the result will be positive integer number.

## 说明/提示

The first example corresponds to the following sequence: $ 512 \rightarrow 511 \rightarrow 510 \rightarrow 51 \rightarrow 50 $ .

## 样例 #1

### 输入

```
512 4

```

### 输出

```
50

```

## 样例 #2

### 输入

```
1000000000 9

```

### 输出

```
1

```



---

