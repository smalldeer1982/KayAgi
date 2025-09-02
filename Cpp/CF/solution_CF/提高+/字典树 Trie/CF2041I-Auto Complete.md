# Auto Complete

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041I/2221d29ba6460d0398718df90accbcfb85d92103.png)You are designing a snazzy new text editor, and you want to add a nifty auto-complete feature to help users save time. Here is how it will work: if a user types "App", your editor will magically suggest the word "Application"! Even better, users can personalize the words that auto-complete in your editor.

Your editor will support 4 kinds of operations (Let's say the current text in your editor is $ t $ ):

1. Add an auto complete pattern $ p_i $ .
2. Delete an auto complete pattern $ p_i $ .
3. Append a string $ s $ to the end of $ t $ .
4. Delete $ c $ characters from the end of $ t $ . Note that if $ c $ is larger then the length of $ t $ , delete all the characters from $ t $ .

After each action, your editor should suggest an auto-complete candidate $ i $ that matches the following criteria:

1. The string $ p_i $ has a prefix equal to $ t $ .
2. If there are multiple $ p_i $ , pick the longest one.
3. If there are still multiple $ p_i $ , pick the one with the smallest lexicographic order.
4. If there are still multiple $ p_i $ , pick the one with the smallest ID.

 To simplify the question, for each action, print the suggested auto complete pattern ID. If there's no match, print -1.For example, let us say we have three candidates: "alice", "bob", and "charlie", with ID 1, 2, and 3. At first, there is nothing on the screen, so "charlie" (3) should be suggested because it is the longest. Then, let us say the user types "b". You should suggest "bob" (2) because it is the only one that starts with "b". Finally, let us say the user type "body". You should print -1 because there is no matched pattern.

## 样例 #1

### 输入

```
6
add 1 pattern1_alice
add 2 pattern2_bob
add 3 pattern3_charlie
append pattern
append 2_bobabc
backspace 3```

### 输出

```
1
1
3
3
-1
2```

## 样例 #2

### 输入

```
6
append pattern
add 1 pattern1_alice____
add 2 pattern2_bob______
add 3 pattern3_charlie__
delete 1
delete 2```

### 输出

```
-1
1
1
1
2
3```

# 题解

## 作者：沉石鱼惊旋 (赞：1)

## I. Auto Complete

你需要维护一个搜索引擎。支持 $n$ 次操作。共 $4$ 种操作。

1. `add id str` 给搜索引擎插入编号为 $id$ 的内容为 $str$ 的『备选项』。
1. `delete id` 删除编号为 $id$ 的『备选项』。
1. `append str` 给搜索框后面继续输入 $str$ 的内容。
1. `backspace cnt` 给搜索框后面删除 $cnt$ 个字符。

每次操作后，你需要输出目前的『最优』的『备选项』。

『最优』的『备选项』定义为：

1. 搜索框内容是这个『备选项』的前缀。
1. 若满足 1 的有多个，选最长的。
1. 若满足 2 的有多个，选字典序最小的。
1. 若满足 3 的有多个，选编号最小的。

$1\leq n\leq 10^6$，$1\leq \sum |str|\leq 2\times 10^6$，$1\leq c\leq 2\times 10^6$。

保证字符串的字符 ASCII 码范围在 $[33,126]$ 以内。

`add` 操作的 $id$ 两两不同。

`delete` 操作的 $id$ 两两不同。

$id$ 范围在 $[0,n]$ 之间。

---

这个前缀很引导我们往字典树上想。前缀就对应着祖先。

把这些备选项判定拎出来，前缀就对应着必须是祖先，长度对应深度，字典序对应着 DFS 序。

先离线操作，把所有操作全扔到字典树上。删除操作就是跳若干次父亲，所以需要记录字典树每个节点的父亲编号。

这里保证操作合法，所以往下走几步就至多往上走几步，跳父亲暴力跳就行了。

操作离线完就做一次深搜。处理出 DFS 序。

这个编号不是连续的，范围是 $[0,n]$。处理的时候要小心点。

字符集大小很大，直接开数组会浪费很多空间，可以用 map 换空间。

赛时太急了没好好看条件，忘判长度了，最后硬加了一个/xk 写的有点丑。

<https://codeforces.com/contest/2041/submission/293614507>

---

