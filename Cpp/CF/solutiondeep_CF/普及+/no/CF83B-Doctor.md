# 题目信息

# Doctor

## 题目描述

There are $ n $ animals in the queue to Dr. Dolittle. When an animal comes into the office, the doctor examines him, gives prescriptions, appoints tests and may appoint extra examination. Doc knows all the forest animals perfectly well and therefore knows exactly that the animal number $ i $ in the queue will have to visit his office exactly $ a_{i} $ times. We will assume that an examination takes much more time than making tests and other extra procedures, and therefore we will assume that once an animal leaves the room, it immediately gets to the end of the queue to the doctor. Of course, if the animal has visited the doctor as many times as necessary, then it doesn't have to stand at the end of the queue and it immediately goes home.

Doctor plans to go home after receiving $ k $ animals, and therefore what the queue will look like at that moment is important for him. Since the doctor works long hours and she can't get distracted like that after all, she asked you to figure it out.

## 说明/提示

In the first sample test:

- Before examination: $ {1,2,3} $
- After the first examination: $ {2,3} $
- After the second examination: $ {3,2} $
- After the third examination: $ {2} $

In the second sample test:

- Before examination: $ {1,2,3,4,5,6,7} $
- After the first examination: $ {2,3,4,5,6,7} $
- After the second examination: $ {3,4,5,6,7,2} $
- After the third examination: $ {4,5,6,7,2,3} $
- After the fourth examination: $ {5,6,7,2,3} $
- After the fifth examination: $ {6,7,2,3,5} $
- After the sixth examination: $ {7,2,3,5,6} $
- After the seventh examination: $ {2,3,5,6} $
- After the eighth examination: $ {3,5,6,2} $
- After the ninth examination: $ {5,6,2,3} $
- After the tenth examination: $ {6,2,3} $

## 样例 #1

### 输入

```
3 3
1 2 1
```

### 输出

```
2 ```

## 样例 #2

### 输入

```
4 10
3 3 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7 10
1 3 3 1 2 3 1
```

### 输出

```
6 2 3 ```

# AI分析结果

### 题目内容
# 医生

## 题目描述
有 $n$ 只动物排队等待杜立德医生看病。当一只动物进入诊室时，医生会对它进行检查、开处方、安排检查，并且可能会安排额外的检查。医生非常了解森林里的所有动物，因此确切知道队列中第 $i$ 只动物需要来他的诊室看病 $a_{i}$ 次。我们假设一次检查所花费的时间比做检查和其他额外程序要长得多，因此我们假设一旦一只动物离开诊室，它会立即回到医生的队列末尾。当然，如果一只动物已经看过足够次数的病，那么它就不必再站在队列末尾，而是直接回家。

医生计划在看完 $k$ 只动物后回家，所以此刻队列的情况对他很重要。由于医生工作时间很长，毕竟不能因此分心，所以他请你帮忙弄清楚。

## 说明/提示
在第一个样例测试中：
- 检查前：$ \{1,2,3\} $
- 第一次检查后：$ \{2,3\} $
- 第二次检查后：$ \{3,2\} $
- 第三次检查后：$ \{2\} $

在第二个样例测试中：
- 检查前：$ \{1,2,3,4,5,6,7\} $
- 第一次检查后：$ \{2,3,4,5,6,7\} $
- 第二次检查后：$ \{3,4,5,6,7,2\} $
- 第三次检查后：$ \{4,5,6,7,2,3\} $
- 第四次检查后：$ \{5,6,7,2,3\} $
- 第五次检查后：$ \{6,7,2,3,5\} $
- 第六次检查后：$ \{7,2,3,5,6\} $
- 第七次检查后：$ \{2,3,5,6\} $
- 第八次检查后：$ \{3,5,6,2\} $
- 第九次检查后：$ \{5,6,2,3\} $
- 第十次检查后：$ \{6,2,3\} $

## 样例 #1
### 输入
```
3 3
1 2 1
```
### 输出
```
2 
```

## 样例 #2
### 输入
```
4 10
3 3 2 1
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
7 10
1 3 3 1 2 3 1
```
### 输出
```
6 2 3 
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要有两种思路。一种是直接模拟，如作者XXh0919、zym20249_、albccpp6、taikongsha的题解，利用队列或数组直接按照题目描述的规则进行操作，这种方法思路直接，但对于较大的 $k$ 可能效率较低。另一种是利用数学性质优化，如作者小杨小小杨利用周期问题，先通过排序从数值小的开始消去，再暴力模拟剩余部分；作者yuchenren采用二分答案，通过二分求出需要多少轮看病，再处理剩余情况。相比之下，直接模拟容易理解和实现，但时间复杂度较高；利用数学性质优化的方法虽然思路复杂，但对于大数据有更好的效率。

### 通用建议与扩展思路
对于这类模拟题，若数据范围较小，直接模拟是简单有效的方法。若数据范围较大，可尝试挖掘题目中的数学性质或规律来优化算法，如寻找周期、利用二分等。同类型题通常围绕队列操作和条件判断展开，类似算法套路包括对操作过程进行数学建模，从而减少不必要的模拟步骤。

### 洛谷相似题目
1. P1996 约瑟夫问题：同样涉及队列元素的循环操作与删除。
2. P1032 字串变换：通过模拟字符串变换过程求解，考察对操作规则的实现。
3. P1048 采药：虽然核心是背包问题，但也包含对时间等条件的模拟判断。 

---
处理用时：37.57秒