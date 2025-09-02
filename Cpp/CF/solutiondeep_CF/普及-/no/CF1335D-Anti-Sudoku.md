# 题目信息

# Anti-Sudoku

## 题目描述

You are given a correct solution of the sudoku puzzle. If you don't know what is the sudoku, you can read about it [here](http://tiny.cc/636xmz).

The picture showing the correct sudoku solution:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1335D/512a05a69fe045d0e0e90836d8dc5e29c119293a.png)

Blocks are bordered with bold black color.

Your task is to change at most $ 9 $ elements of this field (i.e. choose some $ 1 \le i, j \le 9 $ and change the number at the position $ (i, j) $ to any other number in range $ [1; 9] $ ) to make it anti-sudoku. The anti-sudoku is the $ 9 \times 9 $ field, in which:

- Any number in this field is in range $ [1; 9] $ ;
- each row contains at least two equal elements;
- each column contains at least two equal elements;
- each $ 3 \times 3 $ block (you can read what is the block in the link above) contains at least two equal elements.

It is guaranteed that the answer exists.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
1
154873296
386592714
729641835
863725149
975314628
412968357
631457982
598236471
247189563```

### 输出

```
154873396
336592714
729645835
863725145
979314628
412958357
631457992
998236471
247789563```

# AI分析结果

### 题目内容
# 反数独

## 题目描述
给定一个正确的数独谜题解决方案。如果你不知道什么是数独，可以在[这里](http://tiny.cc/636xmz)阅读相关内容。

展示正确数独解决方案的图片：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1335D/512a05a69fe045d0e0e90836d8dc5e29c119293a.png)
宫格用粗黑线框出。

你的任务是在这个数独中最多改变9个元素（即选择某些\(1 \leq i, j \leq 9\)，并将位置\((i, j)\)处的数字更改为范围\([1; 9]\)内的任何其他数字），使其成为反数独。反数独是一个\(9×9\)的矩阵，其中：
- 矩阵中的任何数字都在范围\([1; 9]\)内；
- 每行至少包含两个相等的元素；
- 每列至少包含两个相等的元素；
- 每个\(3×3\)的宫格（你可以在上面的链接中了解什么是宫格）至少包含两个相等的元素。

保证有解。

你必须回答\(t\)个独立的测试用例。

## 样例 #1
### 输入
```
1
154873296
386592714
729641835
863725149
975314628
412968357
631457982
598236471
247189563
```
### 输出
```
154873396
336592714
729645835
863725145
979314628
412958357
631457992
998236471
247789563
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何通过改变数独中的数字来构造出反数独。思路可分为两类：一类是选择特定位置的数字进行改变，保证每行、每列、每宫各有一个数字被改变，从而满足反数独条件；另一类是将数独中某一种数字全部替换为另一种数字，利用原数独每行、每列、每宫数字不重复的特性，使得替换后每行、每列、每宫都出现重复数字。解决的难点在于如何确保改变数字后能满足反数独的所有条件且操作次数不超过9次。

### 所选的题解
- **作者：kydbuhuipro (赞：8)  星级：5星 关键亮点：利用数独本身特性，提出将1 - 9任一数字全部替换就能构造出反数独，思路简洁巧妙，代码实现简单**
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int x=1;x<=t;x++){
        char c[9][9];
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cin>>c[i][j];
                if(c[i][j]=='1')c[i][j]++;
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout<<c[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}
```
核心实现思想：读入数独，将其中所有的'1'替换为'2'，从而构造出反数独。

- **作者：oimaster (赞：2)  星级：5星 关键亮点：同样采用将所有的1改成2的方法，清晰阐述了这样做满足反数独要求的原因，思维难度和代码难度都较低**
核心实现思想与kydbuhuipro类似，也是通过将所有1替换为2来构造反数独。

- **作者：hanyuchen2019 (赞：0)  星级：4星 关键亮点：清晰解释把数组中任意一种数字\(x\)替换为另一种数字\(y\)（\(x≠y\)）构造反数独的原理，代码简洁明了**
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        char ch;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                cin>>ch;
                if(ch=='1')cout<<'2';//设x=1,y=2。
                else cout<<ch;
            }
            cout<<endl;
        }
    }
    return 0;
}
```
核心实现思想：读入数独每个字符，若为'1'则输出'2'，否则输出原字符，实现将所有'1'替换为'2'构造反数独。

### 最优关键思路或技巧
将数独中某一种数字全部替换为另一种数字的方法最为巧妙，利用数独每行、每列、每宫数字不重复的特性，简单直接地构造出反数独，极大降低了思维和代码实现的难度。

### 可拓展之处
此类题目属于构造类型，类似的题目套路是利用原数据结构的特性，通过简单操作构造出满足新条件的数据结构。例如在其他矩阵类问题中，根据给定矩阵的规则和要达成的新目标，寻找关键元素或位置进行操作。

### 洛谷相似题目推荐
- [P1108 低价购买](https://www.luogu.com.cn/problem/P1108)：涉及到序列的构造与条件满足，与本题构造反数独思路类似，需根据给定条件构造出符合要求的序列。
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：在棋盘矩阵上按照特定规则进行遍历和状态构造，和本题在矩阵上进行操作构造有相似之处。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过对数字的选择和组合构造出满足条件的结果，和本题构造反数独满足特定条件思路相仿。

### 个人心得摘录与总结
无。 

---
处理用时：64.78秒