# 题目信息

# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 样例 #1

### 输入

```
5 1
BGGBG
```

### 输出

```
GBGGB
```

## 样例 #2

### 输入

```
5 2
BGGBG
```

### 输出

```
GGBGB
```

## 样例 #3

### 输入

```
4 1
GGGB
```

### 输出

```
GGGB
```

# AI分析结果

### 题目内容重写

#### 题目描述

在课间休息时，学校的男孩和女孩们在食堂排成了一队，共有 $n$ 个人。最初，孩子们按照他们进入食堂的顺序站队。然而，过了一段时间后，男孩们开始感到尴尬，因为他们站在女孩们的前面，于是他们开始让女孩们每秒向前移动。

让我们更精确地描述这个过程。假设队列中的位置从 $1$ 到 $n$ 依次编号，位置 $1$ 的人最先被服务。如果在时间 $x$，第 $i$ 个位置是男孩，第 $i+1$ 个位置是女孩，那么在时间 $x+1$，第 $i$ 个位置将变成女孩，第 $i+1$ 个位置将变成男孩。时间以秒为单位给出。

你得到了孩子们在初始时刻的位置。确定在 $t$ 秒后队列的样子。

#### 样例 #1

##### 输入

```
5 1
BGGBG
```

##### 输出

```
GBGGB
```

#### 样例 #2

##### 输入

```
5 2
BGGBG
```

##### 输出

```
GGBGB
```

#### 样例 #3

##### 输入

```
4 1
GGGB
```

##### 输出

```
GGGB
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是模拟男孩和女孩在队列中的交换过程。大多数题解都采用了直接模拟的方法，时间复杂度为 $O(n \times t)$。虽然题目数据范围较小（$n, t \leq 50$），但部分题解在实现时存在一些细节问题，如未正确处理交换后的位置跳过、重复交换等。

#### 所选高星题解

1. **作者：HNYLMS_MuQiuFeng (赞：5)**
   - **星级：4星**
   - **关键亮点：**
     - 使用字符串直接模拟交换过程，代码简洁。
     - 在交换后通过 `j++` 跳过下一个位置，避免重复交换。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;i++) {
         for(int j=0;j<len;j++) {
             if(s[j]=='B'&&s[j+1]=='G') {
                 swap(s[j],s[j+1]);
                 j++;
             }
         }
     }
     ```

2. **作者：Dancing_Wave (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 明确每轮交换后跳过下一个位置，避免重复交换。
     - 代码结构清晰，易于理解。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=t;i++) {
         for(int i=0;i<n-1;i++) {
             if(s[i]=='B'&&s[i+1]=='G') {
                 swap(s[i],s[i+1]);
                 i++;
             }
         }
     }
     ```

3. **作者：fls233666 (赞：0)**
   - **星级：4星**
   - **关键亮点：**
     - 使用动态数组记录男孩的位置，避免重复交换。
     - 每次循环前清空动态数组，确保每轮交换的独立性。
   - **核心代码：**
     ```cpp
     for(int ti=1;ti<=t;ti++) {
         boy.clear();
         for(int i=0;i<n-1;i++) {
             if(queue[i]=='B') boy.push_back(i);
         }
         for(int i=0;i<boy.size();i++) {
             if(queue[boy[i]+1]=='G') {
                 queue[boy[i]]='G';
                 queue[boy[i]+1]='B';
             }
         }
     }
     ```

### 最优关键思路与技巧

- **跳过交换后的位置：** 在交换男孩和女孩的位置后，跳过下一个位置，避免重复交换。
- **使用动态数组记录位置：** 通过记录男孩的位置，确保每轮交换的独立性，避免重复交换。

### 可拓展之处

- **类似问题：** 可以扩展到更复杂的队列交换问题，如多轮交换、不同交换规则等。
- **算法优化：** 对于更大的数据范围，可以考虑优化算法，减少时间复杂度。

### 推荐题目

1. **洛谷 P1090 [NOIP2004 提高组] 合并果子** (考察优先队列的应用)
2. **洛谷 P1168 [NOIP2011 提高组] 中位数** (考察模拟与排序)
3. **洛谷 P1048 [NOIP2005 普及组] 采药** (考察动态规划与模拟)

### 个人心得总结

- **调试经历：** 部分题解在实现时未正确处理交换后的位置跳过，导致重复交换，最终通过调试发现并修正。
- **顿悟感想：** 通过记录男孩的位置，可以确保每轮交换的独立性，避免重复交换，提高代码的准确性和效率。

---
处理用时：33.69秒