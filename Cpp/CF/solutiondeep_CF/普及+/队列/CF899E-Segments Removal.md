# 题目信息

# Segments Removal

## 题目描述

Vasya has an array of integers of length $ n $ .

Vasya performs the following operations on the array: on each step he finds the longest segment of consecutive equal integers (the leftmost, if there are several such segments) and removes it. For example, if Vasya's array is $ [13,13,7,7,7,2,2,2] $ , then after one operation it becomes $ [13,13,2,2,2] $ .

Compute the number of operations Vasya should make until the array becomes empty, i.e. Vasya removes all elements from it.

## 说明/提示

In the first example, at first Vasya removes two fives at the second and third positions. The array becomes $ [2,2] $ . In the second operation Vasya removes two twos at the first and second positions. After that the array becomes empty.

In the second example Vasya has to perform five operations to make the array empty. In each of them he removes the first element from the array.

In the third example Vasya needs three operations. In the first operation he removes all integers $ 4 $ , in the second — all integers $ 100 $ , in the third — all integers $ 2 $ .

In the fourth example in the first operation Vasya removes the first two integers $ 10 $ . After that the array becomes $ [50,10,50,50] $ . Then in the second operation Vasya removes the two rightmost integers $ 50 $ , so that the array becomes $ [50,10] $ . In the third operation he removes the remaining $ 50 $ , and the array becomes $ [10] $ after that. In the last, fourth operation he removes the only remaining $ 10 $ . The array is empty after that.

## 样例 #1

### 输入

```
4
2 5 5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
6 3 4 1 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
8
4 4 4 2 2 100 100 100
```

### 输出

```
3
```

## 样例 #4

### 输入

```
6
10 10 50 10 50 50
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 区间删除

## 题目描述
Vasya有一个长度为 $n$ 的整数数组。

Vasya对该数组执行以下操作：在每一步中，他找到最长的连续相等整数段（如果有多个这样的段，则取最左边的）并将其删除。例如，如果Vasya的数组是 $[13,13,7,7,7,2,2,2]$，那么经过一次操作后，它变为 $[13,13,2,2,2]$。

计算Vasya需要执行多少次操作才能使数组为空，即Vasya从数组中删除所有元素。

## 说明/提示
在第一个示例中，首先Vasya删除第二个和第三个位置的两个5。数组变为 $[2,2]$。在第二次操作中，Vasya删除第一个和第二个位置的两个2。之后数组变为空。

在第二个示例中，Vasya必须执行五次操作才能使数组为空。在每次操作中，他从数组中删除第一个元素。

在第三个示例中，Vasya需要三次操作。在第一次操作中，他删除所有整数4，在第二次操作中删除所有整数100，在第三次操作中删除所有整数2。

在第四个示例中，在第一次操作中Vasya删除前两个整数10。之后数组变为 $[50,10,50,50]$。然后在第二次操作中，Vasya删除最右边的两个整数50，因此数组变为 $[50,10]$。在第三次操作中，他删除剩余的50，之后数组变为 $[10]$。在最后一次，即第四次操作中，他删除唯一剩余的10。之后数组为空。

## 样例 #1
### 输入
```
4
2 5 5 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
6 3 4 1 5
```
### 输出
```
5
```

## 样例 #3
### 输入
```
8
4 4 4 2 2 100 100 100
```
### 输出
```
3
```

## 样例 #4
### 输入
```
6
10 10 50 10 50 50
```
### 输出
```
4
```

### 题解综合分析与结论
这些题解主要围绕如何高效地找出并删除数组中最长的连续相等整数段，同时处理删除后相邻段可能合并的情况。大多数题解采用了优先队列（大根堆）来快速获取最长段，结合链表（双向链表或数组模拟链表）来方便地进行删除和合并操作。部分题解还使用了线段树、平衡树（如FHQ - Treap）、集合（std::set）等数据结构辅助。

- **思路方面**：都是先对原数组进行分段处理，记录每段的信息（如长度、值、位置等）。然后通过优先队列获取最长段，删除该段后检查相邻段是否合并，更新数据结构并重复操作直至数组为空。
- **算法要点**：关键在于数据结构的选择和操作的实现。优先队列用于维护最长段，链表用于快速删除和合并区间，不同数据结构的组合使用决定了算法的复杂度和实现难度。
- **解决难点**：难点在于如何在删除区间后高效地更新数据结构，确保能准确找到下一个最长段，同时处理好合并操作避免错误。例如，使用标记数组避免重复处理已删除的区间，合理更新优先队列和链表中的信息。

### 所选的题解
- **作者emptysetvvvv（5星）**
  - **关键亮点**：思路清晰，代码简洁高效。巧妙地使用双向链表和优先队列组合。双向链表维护区间的前后关系，方便删除和查找相邻区间；优先队列按区间长度和位置排序，快速获取最长区间。通过翻转数组简化优先队列的排序逻辑。
  - **个人心得**：作者自认为是小萌新做法，欢迎被hack数据检验。
  ```cpp
  // 核心代码片段
  while(!q.empty()) {
      int cur = q.top().second; q.pop();
      if(vis[cur]) continue;
      int l = pre[cur], r = nxt[cur];
      pre[r] = l, nxt[l] = r, vis[cur] = true;
      if(l and col[l] == col[r])
          pre[nxt[r]] = l, nxt[l] = nxt[r], vis[r] = true, q.push(make_pair(sum[l]+=sum[r], l));
      ++ans;
  }
  ```
  核心实现思想：每次从优先队列取出堆顶区间编号cur，在链表中删除cur并标记已访问。检查cur左右区间颜色是否相同，相同则合并并将新区间信息加入优先队列，最后操作次数加1。

- **作者Forsaken2020（4星）**
  - **关键亮点**：代码注释详细，对思路和实现步骤解释清晰。同样采用优先队列和链表结合的方式，先压缩序列，用链表连接各区间，优先队列维护最长区间。
  ```cpp
  // 核心代码片段
  while (cnt!= n &&!q.empty()) {
      node sb = q.top(); q.pop();
      if (cant_visit[sb.pos])continue;
      ans++; cnt += arr[sb.pos].number;
      cant_visit[sb.pos] = true;
      int _Next = _next[sb.pos], _Last = last[sb.pos];
      if (arr[_Next].value == arr[_Last].value) {
          arr[_Last].number += arr[_Next].number;
          cant_visit[_Next] = true;
          q.push(node(arr[_Last].number, _Last));
          _Next = _next[_Next];
          last[_Next] = _Last;
          _next[_Last] = _Next;
      }
      else {
          last[_Next] = _Last;
          _next[_Last] = _Next;
      }
  }
  ```
  核心实现思想：从优先队列取区间，若该区间未被访问过则删除，更新答案和已处理元素个数，标记已访问。检查相邻区间值是否相同，相同则合并并更新链表和优先队列，不同则仅更新链表。

- **作者Poncirus（4星）**
  - **关键亮点**：封装了链表类，结构清晰。先预处理出数组中的“块”，用链表维护块的信息，优先队列以长度和起始位置为关键字维护块，每次取出堆顶块删除并处理合并。
  ```cpp
  // 核心代码片段
  while(!q.empty()) {
      int f=q.top().u, t=q.top().i; q.pop();
      if(vis[f]) continue; vis[f]=1; ++ans;
      l=li.GetPrev(f); r=li.GetNext(f);
      if(f==li.GetHead()||f==li.GetBack()) {
          li.Delete(f);
          continue;
      }
      li.Delete(f);
      if(li.GetValue(l).d==li.GetValue(r).d) {
          li.GetValue(l).u+=li.GetValue(r).u;
          li.Delete(r); vis[r]=1;
          q.push(__(l,li.GetValue(l).u,t,li.GetValue(l).d));
      }
  }
  ```
  核心实现思想：从优先队列取块，若块未被访问则标记并删除，更新答案。获取相邻块，若相邻块数值相同则合并，更新链表和优先队列。

### 最优关键思路或技巧
- **数据结构组合**：优先队列和链表的结合是解决本题的关键。优先队列快速获取最长区间，链表高效处理区间的删除与合并，这种组合能有效降低时间复杂度。
- **标记处理**：使用标记数组（如vis、cant_visit等）避免对已删除区间的重复操作，确保算法的正确性和效率。

### 可拓展之处
同类型题通常涉及对序列中连续相同元素段的操作，类似算法套路是利用优先队列维护最值，链表处理元素的增删改操作。例如在一些字符串处理问题中，需要删除连续相同字符段并统计操作次数，或者在一些游戏场景中，消除连续相同的道具并更新场景状态等。

### 洛谷相似题目推荐
- [P7912 小熊的果篮](https://www.luogu.com.cn/problem/P7912)：同样涉及对序列中连续相同元素块的操作，需要维护块的信息并进行删除和合并。
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：有助于深入理解线段树的数据结构及其操作，部分题解中使用线段树优化查找操作可参考此题。
- [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)：平衡树相关题目，部分题解使用平衡树（如FHQ - Treap）维护区间信息，可通过此题加深对平衡树应用的理解。

### 个人心得摘录与总结
- **作者emptysetvvvv**：自认为是小萌新做法，希望被hack数据检验，体现了对自己代码的严谨态度和乐于交流学习的精神。
- **作者BigJoker**：考试时因元素未进队导致挂题，提醒注意代码细节，尤其是关键操作不能遗漏。
- **作者wgyhm**：分享了调试过程中发现的边界问题及解决方法，强调在处理区间合并和删除时要注意区间端点的正确维护，避免因边界情况考虑不周导致错误。 

---
处理用时：45.53秒