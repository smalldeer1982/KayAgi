# 题目信息

# Assigning to Classes

## 题目描述

Reminder: the [median](https://en.wikipedia.org/wiki/Median) of the array $ [a_1, a_2, \dots, a_{2k+1}] $ of odd number of elements is defined as follows: let $ [b_1, b_2, \dots, b_{2k+1}] $ be the elements of the array in the sorted order. Then median of this array is equal to $ b_{k+1} $ .

There are $ 2n $ students, the $ i $ -th student has skill level $ a_i $ . It's not guaranteed that all skill levels are distinct.

Let's define skill level of a class as the median of skill levels of students of the class.

As a principal of the school, you would like to assign each student to one of the $ 2 $ classes such that each class has odd number of students (not divisible by $ 2 $ ). The number of students in the classes may be equal or different, by your choice. Every student has to be assigned to exactly one class. Among such partitions, you want to choose one in which the absolute difference between skill levels of the classes is minimized.

What is the minimum possible absolute difference you can achieve?

## 说明/提示

In the first test, there is only one way to partition students — one in each class. The absolute difference of the skill levels will be $ |1 - 1| = 0 $ .

In the second test, one of the possible partitions is to make the first class of students with skill levels $ [6, 4, 2] $ , so that the skill level of the first class will be $ 4 $ , and second with $ [5, 1, 3] $ , so that the skill level of the second class will be $ 3 $ . Absolute difference will be $ |4 - 3| = 1 $ .

Note that you can't assign like $ [2, 3] $ , $ [6, 5, 4, 1] $ or $ [] $ , $ [6, 5, 4, 1, 2, 3] $ because classes have even number of students.

 $ [2] $ , $ [1, 3, 4] $ is also not possible because students with skills $ 5 $ and $ 6 $ aren't assigned to a class.

In the third test you can assign the students in the following way: $ [3, 4, 13, 13, 20], [2, 5, 8, 16, 17] $ or $ [3, 8, 17], [2, 4, 5, 13, 13, 16, 20] $ . Both divisions give minimal possible absolute difference.

## 样例 #1

### 输入

```
3
1
1 1
3
6 5 4 1 2 3
5
13 4 20 13 2 5 8 3 17 16```

### 输出

```
0
1
5```

# AI分析结果

### 题目内容
# 班级分配

## 题目描述
提醒：奇数个元素的数组 $ [a_1, a_2, \dots, a_{2k+1}] $ 的中位数定义如下：设 $ [b_1, b_2, \dots, b_{2k+1}] $ 是该数组按升序排列后的元素。那么该数组的中位数等于 $ b_{k+1} $ 。

有 $ 2n $ 个学生，第 $ i $ 个学生的技能水平为 $ a_i $ 。不保证所有技能水平都不同。

我们将一个班级的技能水平定义为该班级学生技能水平的中位数。

作为学校校长，你想将每个学生分配到两个班级中的一个，使得每个班级的学生人数为奇数（不能被2整除）。两个班级的学生人数可以相等也可以不同，由你选择。每个学生都必须恰好分配到一个班级。在这些分配方式中，你想选择一种，使得两个班级技能水平的绝对差值最小。

你能达到的最小绝对差值是多少？

## 说明/提示
在第一个测试用例中，只有一种分配学生的方式 —— 每个班级一个学生。技能水平的绝对差值将是 $ |1 - 1| = 0 $ 。

在第二个测试用例中，一种可能的分配方式是将技能水平为 $ [6, 4, 2] $ 的学生分到第一个班级，这样第一个班级的技能水平将是 $ 4 $ ，将技能水平为 $ [5, 1, 3] $ 的学生分到第二个班级，这样第二个班级的技能水平将是 $ 3 $ 。绝对差值将是 $ |4 - 3| = 1 $ 。

注意，你不能像 $ [2, 3] $ ， $ [6, 5, 4, 1] $ 或 $ [] $ ， $ [6, 5, 4, 1, 2, 3] $ 这样分配，因为班级学生人数为偶数。

 $ [2] $ ， $ [1, 3, 4] $ 这种分配方式也不行，因为技能水平为 $ 5 $ 和 $ 6 $ 的学生没有被分配到班级。

在第三个测试用例中，你可以按以下方式分配学生： $ [3, 4, 13, 13, 20], [2, 5, 8, 16, 17] $ 或 $ [3, 8, 17], [2, 4, 5, 13, 13, 16, 20] $ 。这两种分配方式都能得到最小的绝对差值。

## 样例 #1
### 输入
```
3
1
1 1
3
6 5 4 1 2 3
5
13 4 20 13 2 5 8 3 17 16
```
### 输出
```
0
1
5
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是先将给定的长度为 $2n$ 的学生技能水平序列进行排序，然后直接得出答案为排序后第 $n + 1$ 位与第 $n$ 位元素的差值。难点在于如何证明这个结论，部分题解通过找规律发现了这一结论，而 “gcwixsxr” 的题解通过反证法对该结论进行了严谨证明。各题解在代码实现上主要差异在于输入输出方式、变量命名及空间开辟大小，整体思路较为统一。

### 所选的题解
- **作者：gcwixsxr (5星)**
  - **关键亮点**：不仅给出了简洁的代码实现，还通过反证法严谨证明了答案是排序后第 $n + 1$ 位与第 $n$ 位之差这一核心结论。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=2e5+10;

int T,n,a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++)scanf("%d",a+i);
		sort(a+1,a+2*n+1);
		printf("%d\n",a[n+1]-a[n]);
	}
}
```
  - **核心实现思想**：通过 `scanf` 读入数据，利用 `sort` 对数组排序，最后输出排序后数组第 $n + 1$ 项与第 $n$ 项的差值。

### 最优关键思路或技巧
通过对问题深入分析，发现将序列排序后中间两个数的差值就是问题所求答案，这种通过数学证明得出简洁结论的思维方式是解决本题的关键。同时，在解决类似问题时，严谨的数学证明有助于确保结论的正确性。

### 可拓展之处
同类型题通常围绕数据的分组与特定统计量（如中位数、平均数等）的关系展开。类似算法套路是先对数据进行排序，然后分析排序后数据的特征与题目所求目标之间的联系。

### 洛谷题目推荐
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过对不同购买方案的分析，选择最优方案，考察数学分析与贪心策略。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：根据给定的条件计算并比较数据，属于简单的数学计算与逻辑判断类型。
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和数学计算找到满足等式的方案数，考察枚举与数学运算能力。 

---
处理用时：56.72秒