# 题目信息

# [ICPC 2018 WF] Wireless is the New Fiber

## 题目描述



A new type of unbounded-bandwidth wireless communication has just been tested and proved to be a suitable replacement for the existing, fiber-based communications network, which is struggling to keep up with traffic growth. You have been charged with deciding the layout of the new communications network. The current communications network consists of a set of nodes (which route messages), and links of fiber, each of which connects two different nodes. For each pair of nodes, there exists at least one way (but possibly more, for bandwidth purposes) to travel along the fiber between the two.

The new communications network will not have any fiber. Instead, it will have wireless links, each connecting two nodes. These links have unbounded bandwidth but are expensive, so it has been decided that as few of these links will be built as possible to provide connectivity; for each pair of nodes there should be exactly one way to travel between them along the wireless links. Moreover, you discovered that the nodes have each been built with a particular number of connections in mind. For each node, if it will be connected to a different number of links than it is today, it will have to be reorganized, and that is costly.

Your task is to design the new network so that it has precisely one path between each pair of nodes while minimizing the number of nodes that do not have the same number of connections as in the original network. Figure K.1 shows the original network and a solution for Sample Input $1$ .

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15699/1.png)

Figure K.1 : Illustration of Sample Input $1$ .



## 说明/提示

Time limit: 2 s, Memory limit: 1024 MB. 

SPJ provider: @[shenyouran](/user/137367).

## 样例 #1

### 输入

```
7 11
0 1
0 2
0 5
0 6
1 3
2 4
1 2
1 2
1 5
2 6
5 6
```

### 输出

```
3
7 6
0 1
0 2
0 5
0 6
3 6
4 6
```

## 样例 #2

### 输入

```
4 3
0 1
2 1
2 3
```

### 输出

```
0
4 3
2 1
1 3
0 2
```

# AI分析结果



**算法分类**: 构造

**综合分析**  
本题需构造一棵树，使得尽可能多节点的度数与原图相同。关键是将原度数调整后的问题转化为贪心选择与树构造问题。各题解均采用贪心策略选择保留度数的节点，并利用构造算法生成树结构。

**精选题解**  

1. **feecle6418（4星）**  
   **亮点**:  
   - 将度数减一后的总和转化为n-2，通过排序和贪心快速确定保留节点数。  
   - 构造树时按度数从小到大处理，确保合法连接。  
   **代码核心**:  
   ```cpp
   sort(pl, pl+n, [](int x, int y) { return d[x] < d[y]; });
   for (int i = 0; i < n; i++) {
       if (s + d[pl[i]] > n-2) break;
       s += d[pl[i]], ans++;
   }
   // 构造树时，动态调整度数并连接节点
   ```

2. **ycy1124（4星）**  
   **亮点**:  
   - 类似贪心思路，强调优先处理叶子节点。  
   - 代码中显式处理度数分配，确保总和正确。  
   **心得**:  
   > "构造时需注意叶子节点的连接顺序，否则可能无法形成合法树结构。"  
   **代码核心**:  
   ```cpp
   sort(a, a+n, cmp);
   for (int i = 0; i < n; i++) {
       if (sum >= a[i].d-1) ++ans, sum -= (a[i].d-1);
       else a[i].d = 1 + (sum > 0 ? sum : 0), sum = 0;
   }
   ```

**关键思路**  
1. **度数调整与贪心**：将原度数减一，总和需为n-2。按度数从小到大选择节点，最大化保留原度数的节点数。  
2. **树构造**：将度数小的节点优先作为叶子，连接到度数较大的内部节点，类似Huffman编码思想。

**拓展与推荐**  
- 类似构造树题目：  
  - [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)  
  - [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)  
  - [P1268 树的重量](https://www.luogu.com.cn/problem/P1268)

---
处理用时：63.99秒