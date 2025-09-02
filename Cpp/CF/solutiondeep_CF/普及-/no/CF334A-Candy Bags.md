# 题目信息

# Candy Bags

## 题目描述

Gerald has $ n $ younger brothers and their number happens to be even. One day he bought $ n^{2} $ candy bags. One bag has one candy, one bag has two candies, one bag has three candies and so on. In fact, for each integer $ k $ from $ 1 $ to $ n^{2} $ he has exactly one bag with $ k $ candies.

Help him give $ n $ bags of candies to each brother so that all brothers got the same number of candies.

## 说明/提示

The sample shows Gerald's actions if he has two brothers. In this case, his bags contain 1, 2, 3 and 4 candies. He can give the bags with 1 and 4 candies to one brother and the bags with 2 and 3 to the other brother.

## 样例 #1

### 输入

```
2
```

### 输出

```
1 4
2 3
```

# AI分析结果

### 题目内容
# 糖果袋

## 题目描述
杰拉尔德有 $n$ 个弟弟，而且弟弟的数量恰好是偶数。有一天，他买了 $n^{2}$ 个糖果袋。一个袋子里有1颗糖果，一个袋子里有2颗糖果，一个袋子里有3颗糖果，以此类推。实际上，对于从1到 $n^{2}$ 的每个整数 $k$，他都恰好有一个装有 $k$ 颗糖果的袋子。
请帮他给每个弟弟分 $n$ 袋糖果，使得所有弟弟得到的糖果数量相同。

## 说明/提示
示例展示了如果杰拉尔德有两个弟弟时他的操作。在这种情况下，他的袋子里分别装有1、2、3和4颗糖果。他可以把装有1颗和4颗糖果的袋子给一个弟弟，把装有2颗和3颗糖果的袋子给另一个弟弟。

## 样例 #1
### 输入
```
2
```
### 输出
```
1 4
2 3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用类似高斯求和的配对方法。由于要将 $1$ 到 $n^2$ 的数字分成 $n$ 组，每组和相等，通过观察发现 $1 + n^2 = 2 + (n^2 - 1) = \cdots$ ，即首尾配对可使每组和为 $n^2 + 1$ 。部分题解因未看清题目中 $n$ 为偶数的条件，进行了不必要的奇偶分类讨论。各题解在代码实现上略有差异，但本质思路相同。

### 所选的题解
 - **作者：Ggsddu_zzy (5星)**
    - **关键亮点**：思路清晰，不仅阐述了利用首尾配对使和为 $n^2 + 1$ 的核心思路，还详细说明了如何找出每一种组合，并且给出两种不同实现方式的代码。
    - **重点代码（代码2）**：
```cpp
#include<iostream> 
using namespace std;
int n,b,c; 
int main()
{ 
   cin>>n;
   b=n*n; 
   c=b/2; 
   for(int i=1;i<=c;i++) {                
       cout<<i<<' '<<b-i+1<<"\n";         
   }
   return 0; 
}
```
核心实现思想：先计算出 $n^2$ 赋值给 $b$ ，以及 $n^2$ 的一半赋值给 $c$ ，然后通过循环从 $1$ 到 $c$ ，每次输出 $i$ 和 $b - i + 1$ ，实现糖果袋的配对输出。
 - **作者：Sincerin (4星)**
    - **关键亮点**：从等差数列和公式引入，自然地过渡到利用首尾配对的方法解决问题，思路连贯，代码简洁明了。
    - **重点代码**：
```cpp
#include<iostream> 
using namespace std;
int a,b; 
int main()
{ 
   cin>>a;
   b=a*a/2; 
   for(int i=0;i<b;i++) //查找
   {
       cout<<1+i<<' '<<a*a-i<<"\n";
   }
   return 0; //完结撒花
}
```
核心实现思想：输入 $a$ 后计算出 $a^2$ 的一半赋值给 $b$ ，通过循环从 $0$ 到 $b - 1$ ，每次输出 $1 + i$ 和 $a^2 - i$ ，完成配对输出。
 - **作者：二叉苹果树 (4星)**
    - **关键亮点**：指出其他题解审题不清的问题，直接按照 $n$ 为偶数的条件给出简洁明了的正解代码，符合题意且无冗余。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n*n/2;i++)
        cout<<i<<" "<<n*n-i+1<<endl;
    return 0;
}
```
核心实现思想：输入 $n$ 后，通过循环从 $1$ 到 $n^2$ 的一半，每次输出 $i$ 和 $n^2 - i + 1$ ，实现糖果袋的配对输出。

### 最优关键思路或技巧
利用数学规律，通过观察发现将 $1$ 到 $n^2$ 的数进行首尾配对，可使每对数字之和都为 $n^2 + 1$ ，从而满足将糖果平均分配给弟弟的要求。这种利用数字间规律进行配对的思维方式是解决本题的关键。

### 拓展
同类型题通常围绕数字规律、平均分配等主题，类似算法套路是观察数字间的关系，如对称关系、倍数关系等，利用这些关系进行分组或分配。例如一些将数列分成若干组，使每组和相等的题目。

### 洛谷相似题目推荐
 - [P1089 津津的储蓄计划](https://www.luogu.com.cn/problem/P1089)：涉及简单的数字计算与计划安排，与本题类似之处在于需要分析数字间关系来完成任务。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过分析不同购买方案的价格关系，选择最优方案，与本题分析数字关系以达成目标有相似思路。
 - [P5722 计算阶乘和](https://www.luogu.com.cn/problem/P5722)：考察对数字规律的运用，通过循环计算阶乘和，与本题利用循环实现数字配对输出有类似的代码实现方式。 

---
处理用时：45.02秒