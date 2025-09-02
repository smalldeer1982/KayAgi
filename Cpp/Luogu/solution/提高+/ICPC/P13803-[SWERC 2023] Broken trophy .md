# [SWERC 2023] Broken trophy 

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/5a9ceba0bef33460fb6104cd612fce7a771f3f73.png)

:::

Coming back home after triumphally winning your long-coveted trophy, you discover that it was shattered to pieces in your trunk. It just remains to repair it.


Your trophy had the shape of a rectangle of size $3 \times N$, for some integer $N \geq 1$, thereby consisting of 3 lines and $N$ columns, containing a total of $3N$ unit squares. It was broken into $K$ pieces, the $k^\text{th}$ piece being a rectangle of size $A_k \times B_k$ for some integers $A_k$ and $B_k$ such that $1 \leq A_k \leq B_k \leq 3$. Such pieces may have been rotated, or even flipped, in the havoc that is your trunk.


As the first step towards repairing your trophy, you should reassemble them in the form of a rectangle of size $3 \times N$. More precisely, you have drawn, on a sheet of paper, a $3 \times N$ rectangle on which you will place your $K$ pieces, and you need to know, for all integers $i \leq 3$ and $j \leq N$, which piece will cover the unit square on the $i^\text{th}$ line and $j^\text{th}$ column of your rectangle.


## 说明/提示

**Sample Explanation 1**

This output represents the following reassembling:

:::align{center}

![](https://espresso.codeforces.com/ebe5fa074a7004f06adef36774082b3ef1655782.png)

:::

Another valid reassembling could be: 

:::align{center}

![](https://espresso.codeforces.com/109dea523bad83462aeee9eb8b60ee35eff479d2.png)

:::

## 样例 #1

### 输入

```
16 17
1 2 1 1 2 1 2 1 1 1 1 1 2 2 1 1
3 3 1 3 2 3 3 1 1 2 2 3 3 3 1 3```

### 输出

```
1 2 2 2 12 6 4 13 13 16 16 16 9 10 10 7 7
1 2 2 2 12 6 4 13 13 5 5 14 14 14 11 7 7
1 3 15 8 12 6 4 13 13 5 5 14 14 14 11 7 7```

