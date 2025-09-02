# [SWERC 2023] Olympic goodies

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/5b58e27029703e37247b24c6c8ebbc352e62449b.png)

:::


Freshly arrived on the market, retailer YAOGS (Yet Another Olympic Goodies Seller) sells very expensive Olympics-themed items. To make themselves better known to the public, they half-heartedly decide to give away some of these items via a contest: the first person to answer correctly the question "How many circles are there in the Olympic Games logo?" can thus gain up to $P$ very expensive but equally valued items.


To spice things up (and spend less), YAOGS however opts for an additional challenge, as follows. The $P$ available items are positioned along some, but possibly not all of the alleys of YAOGS's headquarters; each alley can thus contain 0, 1, or more items. For reasons unknown, these alleys form a connected, undirected, acyclic graph (i.e., a tree) with $N$ nodes, numbered from 0 to $N-1$.


The winner knows $N$ but has no idea about either the tree structure or the items' placement. Once goodies are placed, her task is to choose a start node $m$ and an end node $n$. She can then collect all the items on the (unique) path from $m$ to $n$ in the tree.


YAOGS decides to cleverly place the goodies so that they minimise the maximum number of items that can possibly be collected. Assuming they properly carry out this task, what is the maximum number of items the winner can collect?

## 说明/提示

**Sample Explanation**

For the tree in the sample input, depicted below, an optimal item placement by YAOGS guarantees
that the winner cannot collect more than four items.


The figures below show two possible item placements to achieve this optimality. In the first one, the
four items may be collected by choosing, for instance, nodes $1$ and $3$. In the second one, the four items
may be collected by choosing, for instance, nodes $0$ and $4$.

![](https://espresso.codeforces.com/8ebb2ecdb22b673ba1f401eeeee819480e846618.png)



## 样例 #1

### 输入

```
5 5
0 1
0 2
2 3
2 4```

### 输出

```
4```

