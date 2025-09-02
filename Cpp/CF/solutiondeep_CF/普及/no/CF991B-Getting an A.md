# 题目信息

# Getting an A

## 题目描述

Translator's note: in Russia's most widespread grading system, there are four grades: 5, 4, 3, 2, the higher the better, roughly corresponding to A, B, C and F respectively in American grading system.

The term is coming to an end and students start thinking about their grades. Today, a professor told his students that the grades for his course would be given out automatically — he would calculate the simple average (arithmetic mean) of all grades given out for lab works this term and round to the nearest integer. The rounding would be done in favour of the student — $ 4.5 $ would be rounded up to $ 5 $ (as in example 3), but $ 4.4 $ would be rounded down to $ 4 $ .

This does not bode well for Vasya who didn't think those lab works would influence anything, so he may receive a grade worse than $ 5 $ (maybe even the dreaded $ 2 $ ). However, the professor allowed him to redo some of his works of Vasya's choosing to increase his average grade. Vasya wants to redo as as few lab works as possible in order to get $ 5 $ for the course. Of course, Vasya will get $ 5 $ for the lab works he chooses to redo.

Help Vasya — calculate the minimum amount of lab works Vasya has to redo.

## 说明/提示

In the first sample, it is enough to redo two lab works to make two $ 4 $ s into $ 5 $ s.

In the second sample, Vasya's average is already $ 4.75 $ so he doesn't have to redo anything to get a $ 5 $ .

In the second sample Vasya has to redo one lab work to get rid of one of the $ 3 $ s, that will make the average exactly $ 4.5 $ so the final grade would be $ 5 $ .

## 样例 #1

### 输入

```
3
4 4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
5 4 5 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
5 3 3 5
```

### 输出

```
1
```

# AI分析结果

【题目内容】
# Getting an A

## 题目描述

在俄罗斯最常见的评分系统中，有四个等级：5、4、3、2，等级越高越好，大致对应美国评分系统中的A、B、C和F。

学期即将结束，学生们开始考虑他们的成绩。今天，一位教授告诉他的学生，课程的成绩将自动计算——他会计算本学期所有实验成绩的简单平均值（算术平均数），并四舍五入到最接近的整数。四舍五入将有利于学生——$4.5$将向上舍入到$5$（如样例3所示），但$4.4$将向下舍入到$4$。

这对Vasya来说并不是好消息，因为他没有想过这些实验成绩会影响任何事情，所以他可能会得到比$5$更差的成绩（甚至可能是可怕的$2$）。然而，教授允许他重做一些他选择的实验来提高他的平均成绩。Vasya希望尽可能少地重做实验，以便在课程中获得$5$。当然，Vasya将在他选择重做的实验中获得$5$。

帮助Vasya——计算Vasya需要重做的最少实验次数。

## 说明/提示

在第一个样例中，重做两个实验将两个$4$变成$5$就足够了。

在第二个样例中，Vasya的平均成绩已经是$4.75$，所以他不需要重做任何实验就能得到$5$。

在第二个样例中，Vasya需要重做一个实验以消除其中一个$3$，这将使平均成绩正好为$4.5$，因此最终成绩将是$5$。

## 样例 #1

### 输入

```
3
4 4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
5 4 5 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
5 3 3 5
```

### 输出

```
1
```

【算法分类】
贪心

【题解分析与结论】
本题的核心是通过贪心策略，尽可能少地重做实验，使得平均成绩四舍五入后达到5分。大多数题解都采用了贪心思想，即将当前最低分的实验重做，直到平均分满足条件。不同题解在实现细节上有所差异，如是否使用四舍五入函数、是否将分数放大十倍等。

【精选题解】
1. **作者：C_Cong (赞：4)**
   - **星级：4.5**
   - **关键亮点：** 通过将分数扩大十倍，避免了四舍五入的复杂性，直接使用整数运算判断是否满足条件。代码简洁，思路清晰。
   - **核心代码：**
     ```cpp
     while(n*45>=sum)//判断是否满足题目条件
     {
         cot++;//统计重测次数
         sum=sum-src[cot]+50;//把当前最低分改为满分重新计入总分
     }
     ```

2. **作者：zilingheimei (赞：1)**
   - **星级：4**
   - **关键亮点：** 直接使用四舍五入判断平均分是否满足条件，代码逻辑清晰，易于理解。
   - **核心代码：**
     ```cpp
     if((x+5-a[i])/n>=4.5){//5-a[i]为多的分
         cout<<i;
         return 0;
     }
     ```

3. **作者：happybob (赞：1)**
   - **星级：4**
   - **关键亮点：** 使用`round`函数进行四舍五入，代码实现较为规范，适合初学者理解。
   - **核心代码：**
     ```cpp
     while(average < 5)
     {
         for(int i = 1; i <= n; i++)
         {
             if(arr[i] != 5)
             {
                 sum += 5 - arr[i];
                 arr[i] = 5;
                 break;
             }
         }
         c++;
         average = round(sum * 1.0 / n);
     }
     ```

【最优关键思路】
通过贪心策略，每次选择当前最低分的实验重做，直到平均分满足四舍五入为5分的条件。可以通过将分数扩大十倍，简化四舍五入的判断。

【拓展思路】
类似的问题可以通过贪心策略解决，如最小化操作次数以达到某个目标值。可以考虑使用优先队列（堆）来动态获取当前最小值，进一步优化时间复杂度。

【推荐题目】
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：30.28秒