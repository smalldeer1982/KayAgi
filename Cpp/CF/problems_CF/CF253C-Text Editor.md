---
title: "Text Editor"
layout: "post"
diff: 普及/提高-
pid: CF253C
tag: []
---

# Text Editor

## 题目描述

Vasya is pressing the keys on the keyboard reluctantly, squeezing out his ideas on the classical epos depicted in Homer's Odysseus... How can he explain to his literature teacher that he isn't going to become a writer? In fact, he is going to become a programmer. So, he would take great pleasure in writing a program, but none — in writing a composition.

As Vasya was fishing for a sentence in the dark pond of his imagination, he suddenly wondered: what is the least number of times he should push a key to shift the cursor from one position to another one?

Let's describe his question more formally: to type a text, Vasya is using the text editor. He has already written $ n $ lines, the $ i $ -th line contains $ a_{i} $ characters (including spaces). If some line contains $ k $ characters, then this line overall contains $ (k+1) $ positions where the cursor can stand: before some character or after all characters (at the end of the line). Thus, the cursor's position is determined by a pair of integers $ (r,c) $ , where $ r $ is the number of the line and $ c $ is the cursor's position in the line (the positions are indexed starting from one from the beginning of the line).

Vasya doesn't use the mouse to move the cursor. He uses keys "Up", "Down", "Right" and "Left". When he pushes each of these keys, the cursor shifts in the needed direction. Let's assume that before the corresponding key is pressed, the cursor was located in the position $ (r,c) $ , then Vasya pushed key:

- "Up": if the cursor was located in the first line ( $ r=1 $ ), then it does not move. Otherwise, it moves to the previous line (with number $ r-1 $ ), to the same position. At that, if the previous line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r-1 $ ;
- "Down": if the cursor was located in the last line ( $ r=n $ ), then it does not move. Otherwise, it moves to the next line (with number $ r+1 $ ), to the same position. At that, if the next line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r+1 $ ;
- "Right": if the cursor can move to the right in this line ( $ c&lt;a_{r}+1 $ ), then it moves to the right (to position $ c+1 $ ). Otherwise, it is located at the end of the line and doesn't move anywhere when Vasya presses the "Right" key;
- "Left": if the cursor can move to the left in this line ( $ c&gt;1 $ ), then it moves to the left (to position $ c-1 $ ). Otherwise, it is located at the beginning of the line and doesn't move anywhere when Vasya presses the "Left" key.

You've got the number of lines in the text file and the number of characters, written in each line of this file. Find the least number of times Vasya should push the keys, described above, to shift the cursor from position $ (r_{1},c_{1}) $ to position $ (r_{2},c_{2}) $ .

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100 $ ) — the number of lines in the file. The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{5} $ ), separated by single spaces. The third line contains four integers $ r_{1},c_{1},r_{2},c_{2} $ ( $ 1<=r_{1},r_{2}<=n,1<=c_{1}<=a_{r1}+1,1<=c_{2}<=a_{r2}+1 $ ).

## 输出格式

Print a single integer — the minimum number of times Vasya should push a key to move the cursor from position $ (r_{1},c_{1}) $ to position $ (r_{2},c_{2}) $ .

## 说明/提示

In the first sample the editor contains four lines. Let's represent the cursor's possible positions in the line as numbers. Letter $ s $ represents the cursor's initial position, letter $ t $ represents the last one. Then all possible positions of the cursor in the text editor are described by the following table.

123

12

123s567

1t345

One of the possible answers in the given sample is: "Left", "Down", "Left".

## 样例 #1

### 输入

```
4
2 1 6 4
3 4 4 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
10 5 6 4
1 11 4 2

```

### 输出

```
6

```

## 样例 #3

### 输入

```
3
10 1 10
1 10 1 1

```

### 输出

```
3

```

