# 题目信息

# Gennady the Dentist

## 题目描述

Gennady is one of the best child dentists in Berland. Today $ n $ children got an appointment with him, they lined up in front of his office.

All children love to cry loudly at the reception at the dentist. We enumerate the children with integers from $ 1 $ to $ n $ in the order they go in the line. Every child is associated with the value of his cofidence $ p_{i} $ . The children take turns one after another to come into the office; each time the child that is the first in the line goes to the doctor.

While Gennady treats the teeth of the $ i $ -th child, the child is crying with the volume of $ v_{i} $ . At that the confidence of the first child in the line is reduced by the amount of $ v_{i} $ , the second one — by value $ v_{i}-1 $ , and so on. The children in the queue after the $ v_{i} $ -th child almost do not hear the crying, so their confidence remains unchanged.

If at any point in time the confidence of the $ j $ -th child is less than zero, he begins to cry with the volume of $ d_{j} $ and leaves the line, running towards the exit, without going to the doctor's office. At this the confidence of all the children after the $ j $ -th one in the line is reduced by the amount of $ d_{j} $ .

All these events occur immediately one after the other in some order. Some cries may lead to other cries, causing a chain reaction. Once in the hallway it is quiet, the child, who is first in the line, goes into the doctor's office.

Help Gennady the Dentist to determine the numbers of kids, whose teeth he will cure. Print their numbers in the chronological order.

## 说明/提示

In the first example, Gennady first treats the teeth of the first child who will cry with volume $ 4 $ . The confidences of the remaining children will get equal to $ -2,1,3,1 $ , respectively. Thus, the second child also cries at the volume of $ 1 $ and run to the exit. The confidence of the remaining children will be equal to $ 0,2,0 $ . Then the third child will go to the office, and cry with volume $ 5 $ . The other children won't bear this, and with a loud cry they will run to the exit.

In the second sample, first the first child goes into the office, he will cry with volume $ 4 $ . The confidence of the remaining children will be equal to $ 5,-1,6,8 $ . Thus, the third child will cry with the volume of $ 1 $ and run to the exit. The confidence of the remaining children will be equal to $ 5,5,7 $ . After that, the second child goes to the office and cry with the volume of $ 5 $ . The confidences of the remaining children will be equal to $ 0,3 $ . Then the fourth child will go into the office and cry with the volume of $ 2 $ . Because of this the confidence of the fifth child will be $ 1 $ , and he will go into the office last.

## 样例 #1

### 输入

```
5
4 2 2
4 1 2
5 2 4
3 3 5
5 1 2
```

### 输出

```
2
1 3 ```

## 样例 #2

### 输入

```
5
4 5 1
5 3 9
4 1 2
2 1 8
4 1 9
```

### 输出

```
4
1 2 4 5 ```

# AI分析结果

### 题目内容
#### Gennady the Dentist
1. **题目描述**：Gennady是Berland最好的儿童牙医之一。今天有\(n\)个孩子预约了他，他们在他办公室前排成一队。所有孩子在看牙医时都喜欢大声哭闹。我们按照排队顺序用整数\(1\)到\(n\)给孩子们编号。每个孩子都有一个信心值\(p_{i}\)。孩子们一个接一个轮流进入办公室；每次排在队伍最前面的孩子去看医生。当Gennady给第\(i\)个孩子治疗牙齿时，这个孩子会以\(v_{i}\)的音量哭闹。此时，队伍中第一个孩子的信心值会减少\(v_{i}\)，第二个孩子减少\(v_{i}-1\)，依此类推。在第\(v_{i}\)个孩子之后排队的孩子几乎听不到哭声，所以他们的信心值保持不变。如果在任何时候第\(j\)个孩子的信心值小于零，他就会以\(d_{j}\)的音量哭闹并离开队伍，跑向出口，不再去医生办公室。此时，排在第\(j\)个孩子后面的所有孩子的信心值都会减少\(d_{j}\)。所有这些事件会按某种顺序立即依次发生。有些哭声可能会导致其他哭声，引发连锁反应。一旦走廊安静下来，排在队伍最前面的孩子就会进入医生办公室。帮助牙医Gennady确定他将治疗牙齿的孩子的编号。按时间顺序打印他们的编号。
2. **说明/提示**：
    - 在第一个例子中，Gennady首先治疗第一个孩子的牙齿，这个孩子会以音量\(4\)哭闹。其余孩子的信心值将分别变为\(-2,1,3,1\)。因此，第二个孩子也会以音量\(1\)哭闹并跑向出口。其余孩子的信心值将变为\(0,2,0\)。然后第三个孩子会进入办公室，并以音量\(5\)哭闹。其他孩子无法忍受，会大声哭闹着跑向出口。
    - 在第二个例子中，首先第一个孩子进入办公室，他会以音量\(4\)哭闹。其余孩子的信心值将变为\(5,-1,6,8\)。因此，第三个孩子会以音量\(1\)哭闹并跑向出口。其余孩子的信心值将变为\(5,5,7\)。之后，第二个孩子进入办公室并以音量\(5\)哭闹。其余孩子的信心值将变为\(0,3\)。然后第四个孩子会进入办公室并以音量\(2\)哭闹。因此，第五个孩子的信心值将为\(1\)，他将最后进入办公室。
3. **样例 #1**：
    - **输入**：
```
5
4 2 2
4 1 2
5 2 4
3 3 5
5 1 2
```
    - **输出**：
```
2
1 3 
```
4. **样例 #2**：
    - **输入**：
```
5
4 5 1
5 3 9
4 1 2
2 1 8
4 1 9
```
    - **输出**：
```
4
1 2 4 5 
```

### 算法分类
模拟

### 综合分析与结论
这些题解思路基本一致，都是按照题目描述的逻辑，依次对每个孩子进行处理。先处理当前孩子哭声对后续孩子信心值的影响，再处理因信心值小于0而跑掉的孩子对后续孩子信心值的连锁影响，最后统计并输出能接受治疗的孩子编号。算法要点在于准确模拟每个孩子的行为以及信心值的变化过程。解决难点主要在于理清各种情况的先后顺序和相互影响关系，避免逻辑混乱。同时，由于数据可能较大，需要注意使用`long long`类型。

### 通用建议与扩展思路
对于此类模拟题，关键在于仔细梳理题目中的逻辑关系，通过清晰的代码结构来实现模拟过程。可以使用结构体来组织数据，使代码更具可读性。在实现过程中，要注意边界条件的处理，比如哭声影响值减为负数的情况。类似的题目套路通常围绕对一系列按顺序发生且相互影响的事件进行模拟。同类型题可关注一些涉及状态变化和连锁反应的场景模拟题目。

### 洛谷相似题目推荐
1. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：通过模拟字符串的变换规则来求解。
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：对图形的填涂过程进行模拟。
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：模拟在文本中查找特定单词的过程。

### 个人心得摘录与总结
多位作者提到“十年OI一场空，不开long long见祖宗”，强调了在处理本题数据时要使用`long long`类型，避免因数据范围问题出错。部分作者分享了调试经历，如因格式问题导致提交失败，提醒在做题时要注意输出格式的正确性。 

---
处理用时：49.16秒