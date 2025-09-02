# Summer Reading

## 题目描述

At school Vasya got an impressive list of summer reading books. Unlike other modern schoolchildren, Vasya loves reading, so he read some book each day of the summer.

As Vasya was reading books, he was making notes in the Reader's Diary. Each day he wrote the orderal number of the book he was reading. The books in the list are numbered starting from 1 and Vasya was reading them in the order they go in the list. Vasya never reads a new book until he finishes reading the previous one. Unfortunately, Vasya wasn't accurate and some days he forgot to note the number of the book and the notes for those days remained empty.

As Vasya knows that the literature teacher will want to check the Reader's Diary, so he needs to restore the lost records. Help him do it and fill all the blanks. Vasya is sure that he spends at least two and at most five days for each book. Vasya finished reading all the books he had started. Assume that the reading list contained many books. So many, in fact, that it is impossible to read all of them in a summer. If there are multiple valid ways to restore the diary records, Vasya prefers the one that shows the maximum number of read books.

## 样例 #1

### 输入

```
7
0 1 0 0 0 3 0
```

### 输出

```
3
1 1 2 2 3 3 3 
```

## 样例 #2

### 输入

```
8
0 0 0 0 0 0 0 0
```

### 输出

```
4
1 1 2 2 3 3 4 4 
```

## 样例 #3

### 输入

```
4
0 0 1 0
```

### 输出

```
1
1 1 1 1 
```

## 样例 #4

### 输入

```
4
0 0 0 3
```

### 输出

```
-1
```

# 题解

## 作者：Miraik (赞：2)

官方题解是 dp，但是这题看着就很可以贪心。

本题题面有次数的限制 $L=2,R=5$，本做法可以扩展到 $L,R$ 任意的情况。

我想最大化 $a_n$，一个直观的想法就是每个数我尽量出现 $2$ 次就去下一个。

于是考虑维护两个二元组 $up_i$ 和 $low_i$，$up_i=(upval,upcnt)$ 表示在尽量出现次数少的情况下 $upval$ 位置值的上限 $upcnt$，与此时 $x$ 已经连续出现了 $y$ 次。$low_i$ 表示在尽量出现次数多情况下的。

那么遇到一个 $a_i>0$ 时，我们就根据其与 $a_i$ 的大小关系调整 $up$ 与 $low$：

+ $upval_i<a_i$ 或 $lowval_i>a_i$，显然无解。

+ $upval_i>a_i$，则我们需要将 $upval_i$ 修改为 $a_i$，并将 $upcnt_i$ 修改为极大值 $2$（因为必然可以调整到 $a_i$ 出现了两次的情况）

+ $lowval_i<a_i$，则我们需要将 $lowval_i$ 修改为 $a_i$，并将 $lowcnt_i$ 修改为极小值 $1$（同理）

然后最后只需要从后向前贪心的取答案即可。当然也要再利用 $low$ 判一下无解。

这里我们在调整时不需要去调整 $i$ 之前的 $up$ 和 $low$ 的值，因为我们在求答案时，如果当前 $upval_i$ 值比 $a_{i+1}$ 大，说明后面的数限制了 $i$ 的取值，我们可以直接根据 $a_{i+1}$ 目前的出现次数继续构造 $a_i=a_{i+1}$ 或 $a_i=a_{i+1}-1$。

具体实现也可以参考一下代码。时间复杂度 $O(n)$。

[code](https://codeforces.com/contest/370/submission/212230863)

---

