---
title: "SHELL - Shell game"
layout: "post"
diff: 难度0
pid: SP10292
tag: []
---

# SHELL - Shell game

## 题目描述

Your program is to play the traditional "shell" game ([http://en.wikipedia.org/wiki/Shell\_game](http://en.wikipedia.org/wiki/Shell_game "here")). The game is played as follows:

There is a person called an operator; he/she has 3 identical, non-transparent hollow objects - shells, and a metal ball, which he/she places under one of these objects. Then, the operator quickly swaps pairs of shells several times; if shells at positions A and B are swapped, and the ball is under the shell at position A, it moves under the shell at position B. In the end, you have to guess which shell the ball is under.

The shells are identical, and positions mean immediate position that you see (left will always denote the leftmost shell, not the shell that was leftmost in the beginning).

Input

The first line of input contains one string - "left", "center" or "right", denoting the position of the shell the ball is under in the beginning. The second line contains an integer N<=10, denoting the number of swaps. N lines follow, all of them contain 2 strings - positions of 2 shells which are swapped.

Output

Output position of the shell the ball is under after all swaps are performed.

Warning

Testing simulates the exact progress of an actual game! There are 10 testcases; in the last one only, N=10. You're likely to get a WA on this last test case, even if your program seems correct. Remember, it's like an actual game!

Example

 ```
Input:

left
2
left right
right center

Output:

center

Explanation:
in the beginning, the ball is under the left shell
after swap 1, it's under the right shell
after swap 2, it's under the center shell
```

