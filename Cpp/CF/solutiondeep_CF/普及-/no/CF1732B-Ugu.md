# 题目信息

# Ugu

## 题目描述

A binary string is a string consisting only of the characters 0 and 1. You are given a binary string $ s_1 s_2 \ldots s_n $ . It is necessary to make this string non-decreasing in the least number of operations. In other words, each character should be not less than the previous. In one operation, you can do the following:

- Select an arbitrary index $ 1 \leq i \leq n $ in the string;
- For all $ j \geq i $ , change the value in the $ j $ -th position to the opposite, that is, if $ s_j = 1 $ , then make $ s_j = 0 $ , and vice versa.

What is the minimum number of operations needed to make the string non-decreasing?

## 说明/提示

In the first test case, the string is already non-decreasing.

In the second test case, you can select $ i = 1 $ and then $ s = \mathtt{01} $ .

In the third test case, you can select $ i = 1 $ and get $ s = \mathtt{010} $ , and then select $ i = 2 $ . As a result, we get $ s = \mathtt{001} $ , that is, a non-decreasing string.

In the sixth test case, you can select $ i = 5 $ at the first iteration and get $ s = \mathtt{100001} $ . Then choose $ i = 2 $ , then $ s = \mathtt{111110} $ . Then we select $ i = 1 $ , getting the non-decreasing string $ s = \mathtt{000001} $ .

## 样例 #1

### 输入

```
8
1
1
2
10
3
101
4
1100
5
11001
6
100010
10
0000110000
7
0101010```

### 输出

```
0
1
2
1
2
3
1
5```

# AI分析结果

### 题目内容
# Ugu

## 题目描述
二进制字符串是仅由字符0和1组成的字符串。给定一个二进制字符串$s_1 s_2 \ldots s_n$ 。需要通过最少的操作次数使该字符串变为非递减的，换句话说，每个字符都应不小于前一个字符。在一次操作中，可以执行以下操作：
- 选择字符串中任意一个索引$1 \leq i \leq n$；
- 对于所有$j \geq i$，将第$j$个位置的值取反，即如果$s_j = 1$，则变为$s_j = 0$，反之亦然。

需要求出使字符串变为非递减所需的最少操作次数是多少？

## 说明/提示
在第一个测试用例中，字符串已经是非递减的。

在第二个测试用例中，可以选择$i = 1$，然后$s = \mathtt{01}$ 。

在第三个测试用例中，可以选择$i = 1$得到$s = \mathtt{010}$ ，然后选择$i = 2$ 。结果得到$s = \mathtt{001}$ ，即一个非递减字符串。

在第六个测试用例中，第一次迭代可以选择$i = 5$得到$s = \mathtt{100001}$ 。然后选择$i = 2$ ，则$s = \mathtt{111110}$ 。接着选择$i = 1$ ，得到非递减字符串$s = \mathtt{000001}$ 。

## 样例 #1
### 输入
```
8
1
1
2
10
3
101
4
1100
5
11001
6
100010
10
0000110000
7
0101010```
### 输出
```
0
1
2
1
2
3
1
5```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕如何将给定的二进制字符串通过最少次数的后缀取反操作变为非递减展开。
 - **思路方面**：多数题解发现连续的相同字符段可视为一个整体，将原字符串简化为零一交替形式，再考虑如何通过操作变为前部全0、后部全1的非递减形式。如broniazaichek通过统计连续0或1的段数来确定操作次数，lrqlrq250提出连续相同字符段等价的引理并据此简化序列；Fido_Puppy则采用动态规划，从前往后枚举，通过状态转移来求解。
 - **算法要点**：核心在于找到操作次数与字符串特征（如开头字符、连续字符段数量等）的关系。像ljk654321通过遍历统计相邻字符不同的次数来计算操作数；alm_crax根据第一段数字是0还是1，确定所需操作次数为段数减1或减2 。
 - **解决难点**：难点在于理解后缀取反操作对整个字符串单调性的影响，以及如何利用字符串的结构特征（如开头字符、字符段连续性）来优化操作次数。例如，如何证明连续相同字符段处理方式的最优性，以及如何通过动态规划准确描述状态转移。

### 所选的题解
 - **broniazaichek（5星）**
    - **关键亮点**：思路清晰简洁，通过举例直观地展示规律，即除第一位外统计连续的0或1的段数，以1开头的序列操作次数为段数，以0开头的序列操作次数为段数减1，同时对特殊情况（一位数、全0或全1字符串）进行了特判。
    - **个人心得**：无
    - **重点代码**：
```cpp
if(n==1) {ans[u]=0; continue;} //特判，只有一位
if(a[0]=='1') {int yy=0;
    for(int i=0;i<n;i++) {if(a[i]=='1') yy++;}
    if(yy==n) {ans[u]=0; continue;} }
if(a[0]=='1') {int yy=0;
    for(int i=0;i<n;i++) {if(a[i]=='1') yy++;}
    if(yy==n) {ans[u]=0; continue;} }//特判，所有的位数相同
if(a[0]=='1')
{
    int p_1=0,p_2=0; int ans_1=0,ans_2=0;
    for(int i=0;i<n;i++) if(a[i]=='0') {p_1=i; break;}
    for(int i=p_1+1;i<n;i++) {if(a[i]!=a[i-1]) ans_1++;}//求连通块的数量
    ans_1+=1; ans_2++;//为了保险，把头由1换为0后再求一次以0开头需要操作的次数
    for(int i=0;i<n;i++) {if(a[i]=='0') a[i]='1'; else a[i]='0';}
    for(int i=0;i<n;i++) if(a[i]=='1') {p_2=i; break;}
    for(int i=p_2+1;i<n;i++) {if(a[i]!=a[i-1]) ans_2++;}
    ans[u]=min(ans_1,ans_2); continue; //然后求两者较小值 
}
if(a[0]=='0')
{
    int p_1=0,p_2=0; int ans_1=0,ans_2=0;
    for(int i=0;i<n;i++) if(a[i]=='1') {p_1=i; break;}
    for(int i=p_1+1;i<n;i++) {if(a[i]!=a[i-1]) ans_1++;}
    ans_1+=1; ans_2++;
    for(int i=0;i<n;i++) {if(a[i]=='0') a[i]='1'; else a[i]='0';}
    for(int i=0;i<n;i++) if(a[i]=='0') {p_2=i; break;}
    for(int i=p_2+1;i<n;i++) {if(a[i]!=a[i-1]) ans_2++;}
    ans[u]=min(ans_1-1,ans_2-1); continue;
}
```
核心实现思想：先对特殊情况进行特判，然后针对以1开头和以0开头的字符串，分别统计连续字符段数量，考虑将开头字符转换后再次统计，取两种情况的较小值作为操作次数。
 - **lrqlrq250（5星）**
    - **关键亮点**：先给出连续相同字符段等价的引理，简化问题为处理零一交替序列，清晰地阐述了根据序列开头字符确定操作次数的方法，代码简洁明了。
    - **个人心得**：无
    - **重点代码**：
```cpp
int num = 0;
for (int i=1; i<n; i++) if (a[i]!= a[i + 1]) num++;
if (a[1] == 1) printf("%d\n", num);
else{
    if (!num) printf("0\n");
    else printf("%d\n", num - 1);
}
```
核心实现思想：通过遍历统计相邻字符不同的次数得到简化后序列的段数减1，再根据序列开头字符是1还是0，直接输出相应的操作次数，对全0或全1的特殊情况进行特判。
 - **Fido_Puppy（4星）**
    - **关键亮点**：采用动态规划方法，定义三维状态$f_{i, 0/1, 0/1}$来表示当前枚举到第$i$位，当前这位填$0/1$，当前是否$(1/0)$翻转所需的最小翻转次数，通过状态转移方程求解。
    - **个人心得**：无
    - **重点代码**：
```cpp
f[0][0][1] = f[0][1][1] = inf; f[0][0][0] = f[0][1][0] = 0;
rep(i, 1, n) {
    if (s[i] == '0') {
        f[i][0][0] = std :: min(f[ i - 1 ][0][0], f[ i - 1 ][0][1] + 1);
        f[i][0][1] = inf;
        f[i][1][0] = inf;
        f[i][1][1] = std :: min({f[ i - 1 ][1][0] + 1, f[ i - 1 ][0][0] + 1, f[ i - 1 ][0][1], f[ i - 1 ][1][1]});
    }
    else {
        f[i][0][0] = inf;
        f[i][0][1] = std :: min(f[ i - 1 ][0][1], f[ i - 1 ][0][0] + 1);
        f[i][1][0] = std :: min({f[ i - 1 ][0][0], f[ i - 1 ][1][0], f[ i - 1 ][1][1] + 1, f[ i - 1 ][0][1] + 1});
        f[i][1][1] = inf;
    }
}
write(std :: min({f[n][0][0], f[n][0][1], f[n][1][0], f[n][1][1]}));
```
核心实现思想：根据当前字符是0还是1，对不同状态进行状态转移，最后取所有最终状态中的最小值作为结果。

### 最优关键思路或技巧
将连续相同的字符段视为一个整体，简化字符串结构，从而找到操作次数与字符串开头字符及简化后段数的关系。这种思路简化了问题，使得可以通过简单的数学计算得出结果。如broniazaichek和lrqlrq250的方法，通过对字符串结构的观察和总结规律，直接得出操作次数的计算方法，相比动态规划方法更加简洁高效。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串操作及优化操作次数展开，关键在于发现字符串结构特征与操作之间的联系。类似套路包括对字符串进行预处理（如合并连续相同字符），利用字符串的开头、结尾及中间结构特点来确定操作策略。

### 洛谷相似题目推荐
 - **P1002 [NOIP2002 普及组] 过河卒**：涉及路径规划与递推思想，与本题通过分析状态关系求解结果类似。
 - **P1216 [USACO1.5] 数字三角形 Number Triangles**：通过动态规划求解最优路径和，与本题Fido_Puppy采用动态规划思路有相似之处。
 - **P1106 删数问题**：通过删除数字使剩下数字组成的数最小，同样需要考虑如何通过操作优化结果，与本题思路类似。 

---
处理用时：75.13秒