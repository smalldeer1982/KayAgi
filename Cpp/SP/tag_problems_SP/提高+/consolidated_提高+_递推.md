---
title: "RESTACK - Restacking haybales 2012"
layout: "post"
diff: 提高+/省选-
pid: SP11117
tag: ['递推', '线性递推']
---

# RESTACK - Restacking haybales 2012

## 题目描述

Farmer John has just ordered a large number of bales of hay. He would like  
to organize these into N piles (1 <= N <= 100,000) arranged in a circle,  
where pile i contains B\_i bales of hay. Unfortunately, the truck driver  
delivering the hay was not listening carefully when Farmer John provided  
this information, and only remembered to leave the hay in N piles arranged  
in a circle. After delivery, Farmer John notes that pile i contains A\_i  
bales of hay. Of course, the A\_i's and the B\_i's have the same sum.

Farmer John would like to move the bales of hay from their current  
configuration (described by the A\_i's) into his desired target  
configuration (described by the B\_i's). It takes him x units of work to  
move one hay bale from one pile to a pile that is x steps away around the  
circle. Please help him compute the minimum amount of work he will need to  
spend.

## 输入格式

\* Line 1: The single integer N.

\* Lines 2..1+N: Line i+1 contains the two integers A\_i and B\_i (1 <=  
 A\_i, B\_i <= 1000).

Example:

4  
7 1  
3 4  
9 2  
1 13



---

---
title: "SETNJA - Setnja"
layout: "post"
diff: 提高+/省选-
pid: SP3362
tag: ['递推']
---

# SETNJA - Setnja

## 题目描述

在二叉树中：

每个节点都有两个孩子——一个左孩子和一个右孩子。
如果节点标记为整数 $x$ ，则其左子节点标记为 $2x$ ，右子节点标记为 $2x+1$ 。
树的根标为 $1$ 。
在二叉树上从根开始遍历。遍历中的每一步要么是跳到左孩子上，要么是跳到右孩子上，或暂停休息（停留在同一节点上）。

用由字符 $L，R$ 和 $P$ 组成的字符串描述遍历过程。

$L$ 表示跳到左孩子；
$R$ 表示跳到右孩子；
$P$ 表示暂停一轮操作。

$walk$ 的值是我们最终到达的节点的标签。例如，$LR$ 的 $walk$ 值为 5，而 $RPP$ 的 $walk$ 值为 3。

一次遍历由 $L，R，P$ 和 $* $ 描述。每个 $*$ 可以是三个动作中的任何一个。 例如， $L*R$ 可能代表 $LLR，LRR$ 和 $LPR$。集合 $ ** $ 可能代表$ LL，LR，LP，RL，RR，RP，PL，PR$ 和 $PP$。
最后，一次遍历后的 $walk$ 的总值是该次遍历中所有可能的遍历顺序的每一步所形成的 $walk$ 的值的总和。

计算给定遍历顺序后的 $walk$ 的总值。

## 输入格式

一行一个字符串，表示遍历顺序。

## 输出格式

一行一个整数，表示 $walk$
 的总值。
## 输入输出样例
### 输入 #1 
```
L*R
```
### 输出 #1
```
25
```

## 样例 #1

### 输入

```
L*R
```

### 输出

```
25
```



---

