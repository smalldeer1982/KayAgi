---
title: "Flower-like Pseudotree"
layout: "post"
diff: 省选/NOI-
pid: CF1868D
tag: ['构造', '分类讨论']
---

# Flower-like Pseudotree

## 题目描述

A pseudotree is a connected graph which has exactly one cycle and no self-loops. Note that a pseudotree may contain multiple-edges. It can be shown that a pseudotree with $ n $ vertices always contains $ n $ edges.

After deleting all edges on the cycle in the pseudotree, a forest $ ^{\dagger} $ will be formed. It can be shown that each tree in the forest will contain exactly one vertex which is on cycle before removing the edges. If all trees in the forest have the same depth $ ^{\ddagger} $ when picking the vertex on cycle as root, we call the original pseudotree flower-like.

Our friend sszcdjr, had a flower-like pseudotree with $ n $ vertices and $ n $ edges. However, he forgot all the edges in the pseudotree. Fortunately, he still remembers the degrees of vertices. Specifically, the degree of the $ i $ -th vertex is $ d_i $ .

You have to help sszcdjr construct a possible flower-like pseudotree with $ n $ vertices, where the degree of the $ i $ -th vertex is exactly $ d_i $ , or tell him that it is impossible.

 $ ^{\dagger} $ A forest is a graph in which all connectivity components are trees. A connected graph without cycles and self-loops is called a tree.

 $ ^{\ddagger} $ The depth of a tree with a root is the maximum distance from the root to the vertex of this tree.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t\leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\leq n\leq 10^6 $ ) — the number of vertices.

The second line of each test case contains $ n $ integers $ d_1,d_2,\ldots,d_n $ ( $ 1\leq d_i\leq n $ ) — the degree of each vertex.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, if there exist a possible flower-like pseudotree:

- Print "Yes" (without quotes) in the first line.
- Then, output $ n $ lines, in each line print two integers $ u_i $ and $ v_i $ — the two vertices that the $ i $ -th edge connects.

If there are multiple answers, you may output any of them.

Otherwise, print "No" (without quotes) in the only line of output.

You can output the first line of each test case in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, the only possible flower-like psuedotree is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/cef326e6c38f8a7ed31108a0dd8a82ca77066a75.png)After deleting all edges on the cycle in the pseudotree, each tree has depth $ 0 $ .

In the second test case, it can be proven that there's no such flower-like psuedotree.

In the third test case, one of the possible flower-like psuedotrees is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/48e01c1853662d07718526eb1ce31700d09724f0.png)

## 样例 #1

### 输入

```
6
3
2 2 2
4
1 2 3 4
7
4 3 3 1 1 1 1
6
1 1 2 2 3 3
10
1 1 5 2 1 1 1 1 1 6
9
1 1 3 1 1 4 1 1 5
```

### 输出

```
Yes
1 2
2 3
3 1
No
Yes
1 2
2 3
3 1
1 4
1 5
2 6
3 7
Yes
5 6
6 5
1 3
2 4
3 5
4 6
No
Yes
3 6
6 9
9 3
1 3
2 6
4 6
5 9
7 9
8 9
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

