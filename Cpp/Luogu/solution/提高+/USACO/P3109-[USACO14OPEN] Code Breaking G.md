# [USACO14OPEN] Code Breaking G

## 题目描述

The cows keep getting in trouble by taking rides on Farmer John's tractor, so he has hidden the keys to the tractor in a fancy new safe in his office. Undeterred, the cows have vowed to try and break into this safe.

The safe is protected by a rather complicated passcode system. The passcode entry system is arranged as a rooted tree of N (1 <= N <= 20,000) nodes, each of which requires a digit between 0 and 9. The nodes are indexed 0..N-1.

The only information that the cows have is that certain sequences of length 5 do not occur along particular paths upwards through the tree.

For instance, suppose the tree is the following (rooted at A):

A <- B <- C <- D <- E 

^
|
F
The cows might know that the sequence 01234 does not occur starting at F, and that the sequence 91234 does not occur starting at E. This information rules out 19 possible passcodes: all those of the form

4 <- 3 <- 2 <- 1 <- \* 

^
|
0 
or
4 <- 3 <- 2 <- 1 <- 9 

^
|
\*
which gives 19 once we account for the fact that 

4 <- 3 <- 2 <- 1 <- 9 

^
|
0 
appears twice.

Given M (1 <= M <= 50,000) length-5 sequences, together with their starting nodes in the tree, help the cows figure out how many passcodes have been ruled out. You should compute your answer modulo 1234567.

有一棵N个节点的有根树,每个节点可以填0~9.

有M个事实,就是从X开始往祖先一直跑的的包含X的5个节点(保证X上面一定存在这样一条路径,也就是说X的深度至少为5),一定不是ABCDE.(0<=A,B,C,D,E<=9)

求,根据这M个事实,共有多少种给这棵树全部填上数的方案一定是不可能的.


## 样例 #1

### 输入

```
6 2 
0 
1 
2 
3 
3 
4 01234 
5 91234 
```

### 输出

```
19 
```

# 题解

## 作者：kuikuidadi (赞：0)

考虑容斥，枚举哪些串必然出现，那么贡献为 $(-1)^{选中的串数}$。

设 $f_{i,j}$ 表示 $i$ 的子树内，$i$ 点往上是 $j$ 这个串的贡献之和，那么总状态数为 $O(n+m)$ ，用 map 存储 $f$。

将子树的 DP 值与父亲合并时，按串长分类讨论：

若子树串比较长，那么暴力枚举它的前缀状态转移即可。

若父亲串比较长，那么一个子树状态对父亲状态的贡献编码后对应一个区间。

扫描线处理区间，对于相邻的区间内的所有 DP 值整体乘上一个数，线段树维护。

最后沿着线段树上有效节点走，即可不重不漏地得到所有新的状态。

时间复杂度 $O(n\log n)$。

---

