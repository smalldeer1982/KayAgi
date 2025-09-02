---
title: "EDIT3 - Editor II"
layout: "post"
diff: 难度0
pid: SP1464
tag: []
---

# EDIT3 - Editor II

## 输入格式

the very first line contains the number of testcases T(T<=4).T tests follow.

For each test, the first line is the number of operations N.N operations follow.

Blue Mary is so depressed with the problem EDIT1 that she decides to make the problem more difficult.So she inserts many extra line breaks in the string of the Insert operation.You must ignore them.

Except line breaks, all the charaters' ASCII code are in \[32,126\]. There's no extra space at the end of a line.

You can assume that for each test case:

- No invalid operation is in the input.
- Number of move operations is no more than 50000.
- Number of the total of insert and delete operations is no more than 4000.
- Number of the total of prev and next operations is no more than 200000.
- The characters inserted will not more than 2MB.The valid output will not more than 3MB.

## 输出格式

The output should contain T blocks corresponding to each testcase.

For each test case, the output should contain as many lines as the get operations in the input.Each line should contains the output of each get operation.

## 样例 #1

### 输入

```
1
15
Insert 26
abcdefghijklmnop
qrstuv wxy
Move 15
Delete 11
Move 5
Insert 1
^
Next
Insert 1
_
Next
Next
Insert 4
.\/.
Get 4
Prev
Insert 1
^
Move 0
Get 22
```

### 输出

```
.\/.
abcde^_^f.\/.ghijklmno
```

