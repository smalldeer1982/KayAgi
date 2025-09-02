# 题目信息

# Smart Beaver and Resolving Collisions

## 题目描述

The Smart Beaver from ABBYY has a lot of hobbies. One of them is constructing efficient hash tables. One of the most serious problems in hash tables is resolving collisions. The Beaver is interested in this problem very much and he decided to explore it in detail.

We assume that the hash table consists of $ h $ cells numbered from $ 0 $ to $ h-1 $ . Objects are added to and removed from it. Every object has its own unique identifier. In addition, every object has a corresponding hash value — an integer between $ 0 $ and $ h-1 $ , inclusive. When an object is added to the table, if the cell corresponding to the hash value of the object is free, then this object goes there. If the cell is already occupied by another object, there is a collision. When an object is deleted from the table, the cell which it occupied becomes empty.

The Smart Beaver has recently learned about the method of linear probing to resolve collisions. It is as follows. Let's say that the hash value for the added object equals $ t $ and cell $ t $ of the table is already occupied. Then we try to add this object to cell $ (t+m) mod h $ . If it is also occupied, then we try cell $ (t+2·m) mod h $ , then cell $ (t+3·m) mod h $ , and so on. Note that in some cases it's possible that the new object can not be added to the table. It is guaranteed that the input for this problem doesn't contain such situations.

The operation $ a mod b $ means that we take the remainder of the division of number $ a $ by number $ b $ .

This technique immediately seemed very inoptimal to the Beaver, and he decided to assess its inefficiency. So, you are given a sequence of operations, each of which is either an addition of an object to the table or a deletion of an object from the table. When adding a new object, a sequence of calls to the table is performed. Calls to occupied cells are called dummy. In other words, if the result of the algorithm described above is the object being added to cell $ (t+i·m) mod h $ $ (i>=0) $ , then exactly $ i $ dummy calls have been performed.

Your task is to calculate the total number of dummy calls to the table for the given sequence of additions and deletions. When an object is deleted from the table, assume that no dummy calls are performed. The table is empty before performing the operations, that is, initially it doesn't contain any objects.

## 样例 #1

### 输入

```
10 2 7
+ 11 0
+ 22 2
+ 33 6
+ 44 0
+ 55 0
- 22
+ 66 0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 1 6
+ 123 0
+ 234 1
+ 345 2
- 234
+ 456 0
+ 567 0
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# 聪明海狸与解决冲突

## 题目描述
来自ABBYY的聪明海狸有很多爱好。其中之一就是构建高效的哈希表。哈希表中最严重的问题之一就是解决冲突。海狸对这个问题非常感兴趣，于是决定详细探究一番。

我们假设哈希表由 $h$ 个单元格组成，编号从 $0$ 到 $h - 1$。对象可以添加到哈希表中或从哈希表中移除。每个对象都有其唯一标识符。此外，每个对象都有一个对应的哈希值 —— 一个介于 $0$ 到 $h - 1$（含）之间的整数。当一个对象被添加到表中时，如果与该对象哈希值对应的单元格为空，那么这个对象就放入该单元格。如果该单元格已被另一个对象占用，则发生冲突。当一个对象从表中删除时，它所占用的单元格变为空。

聪明海狸最近了解到一种通过线性探测来解决冲突的方法。具体如下。假设要添加的对象的哈希值等于 $t$，而表中的单元格 $t$ 已被占用。那么我们尝试将这个对象添加到单元格 $(t + m)\bmod h$。如果该单元格也被占用，那么我们尝试单元格 $(t + 2·m)\bmod h$，接着尝试单元格 $(t + 3·m)\bmod h$，依此类推。请注意，在某些情况下，新对象可能无法添加到表中。但本题保证输入中不会出现这种情况。

运算 $a\bmod b$ 表示我们取数字 $a$ 除以数字 $b$ 的余数。

这种技术在海狸看来效率极低，于是它决定评估其低效程度。所以，给定一系列操作，每个操作要么是向表中添加一个对象，要么是从表中删除一个对象。当添加一个新对象时，会对表进行一系列调用。对已占用单元格的调用称为无效调用。换句话说，如果上述算法的结果是将对象添加到单元格 $(t + i·m)\bmod h$（$i\geq0$），那么恰好执行了 $i$ 次无效调用。

你的任务是计算给定的添加和删除序列对表的无效调用总数。当从表中删除一个对象时，假设不执行无效调用。在执行操作之前，表是空的，即最初表中不包含任何对象。

## 样例 #1
### 输入
```
10 2 7
+ 11 0
+ 22 2
+ 33 6
+ 44 0
+ 55 0
- 22
+ 66 0
```
### 输出
```
7
```
## 样例 #2
### 输入
```
5 1 6
+ 123 0
+ 234 1
+ 345 2
- 234
+ 456 0
+ 567 0
```
### 输出
```
4
```
### 算法分类
模拟
### 综合分析与结论
这两道题解思路基本一致，均采用模拟的方法解决问题。算法要点在于根据题目给定的线性探测解决哈希冲突的规则，对添加和删除对象的操作进行模拟。解决难点在于如何准确模拟哈希冲突时不断寻找空单元格的过程，并累计无效调用次数。同时，要注意对对象标识符和其对应哈希表位置关系的维护。
### 通用建议与扩展思路
对于此类模拟题，关键在于清晰理解题目给定的规则，并将其准确转化为代码逻辑。可以通过多画图、举例子的方式帮助理解。在代码实现上，要注意变量的合理使用和边界条件的处理。同类型题通常围绕数据结构的操作模拟展开，类似算法套路是根据题目规则，逐步实现每个操作的具体逻辑。
### 洛谷题目推荐
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)
- [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909) 

---
处理用时：33.22秒