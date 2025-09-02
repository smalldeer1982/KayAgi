# 题目信息

# Puzzles

## 题目描述

The end of the school year is near and Ms. Manana, the teacher, will soon have to say goodbye to a yet another class. She decided to prepare a goodbye present for her $ n $ students and give each of them a jigsaw puzzle (which, as wikipedia states, is a tiling puzzle that requires the assembly of numerous small, often oddly shaped, interlocking and tessellating pieces).

The shop assistant told the teacher that there are $ m $ puzzles in the shop, but they might differ in difficulty and size. Specifically, the first jigsaw puzzle consists of $ f_{1} $ pieces, the second one consists of $ f_{2} $ pieces and so on.

Ms. Manana doesn't want to upset the children, so she decided that the difference between the numbers of pieces in her presents must be as small as possible. Let $ A $ be the number of pieces in the largest puzzle that the teacher buys and $ B $ be the number of pieces in the smallest such puzzle. She wants to choose such $ n $ puzzles that $ A-B $ is minimum possible. Help the teacher and find the least possible value of $ A-B $ .

## 说明/提示

Sample 1. The class has 4 students. The shop sells 6 puzzles. If Ms. Manana buys the first four puzzles consisting of 10, 12, 10 and 7 pieces correspondingly, then the difference between the sizes of the largest and the smallest puzzle will be equal to 5. It is impossible to obtain a smaller difference. Note that the teacher can also buy puzzles 1, 3, 4 and 5 to obtain the difference 5.

## 样例 #1

### 输入

```
4 6
10 12 10 7 5 22
```

### 输出

```
5
```

# AI分析结果

### 题目重写
# 拼图

## 题目描述
学年即将结束，老师玛娜娜女士很快又要和一个班级告别了。她决定为她的 $n$ 名学生准备一份告别礼物，送给他们每人一个拼图（正如维基百科所述，拼图是一种拼接谜题，需要将许多小的、形状通常奇特、相互咬合且可拼接的碎片组装起来）。

店员告诉老师，店里有 $m$ 个拼图，但它们的难度和大小可能不同。具体来说，第一个拼图由 $f_1$ 块碎片组成，第二个拼图由 $f_2$ 块碎片组成，依此类推。

玛娜娜女士不想让孩子们失望，所以她决定让礼物中拼图碎片数量的差异尽可能小。设 $A$ 为老师购买的最大拼图的碎片数量，$B$ 为最小拼图的碎片数量。她想选择这样的 $n$ 个拼图，使得 $A - B$ 尽可能小。帮助老师找到 $A - B$ 的最小可能值。

## 说明/提示
示例1. 班级有4名学生。商店出售6个拼图。如果玛娜娜女士购买前四个拼图，分别由10、12、10和7块碎片组成，那么最大和最小拼图的大小差异将等于5。不可能得到更小的差异。请注意，老师也可以购买拼图1、3、4和5以获得差异5。

## 样例 #1
### 输入
```
4 6
10 12 10 7 5 22
```
### 输出
```
5
```

### 算法分类
排序

### 综合分析与结论
所有题解思路基本一致，核心均是先对拼图碎片数量数组进行排序，再通过枚举的方式找出连续n个拼图中最大与最小碎片数差值的最小值。由于题目给定的数据范围较小（$2≤n≤m≤50$），排序方式的选择对时间复杂度影响不大，可使用系统排序函数或简单的选择排序等。各题解的主要区别在于代码实现细节，如变量命名、边界处理、代码风格等。

### 所选的题解
 - **作者：做梦想Peach（4星）**
    - **关键亮点**：思路清晰，代码简洁，利用系统函数`sort`排序，对边界条件有一定讨论，如`for(i=0;i<=m-n;i++)`写成`i<m-n`也能通过。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int a[60],n,m,i,ans=0x7fffffff;
int min (int a,int b) {
    return a < b? a : b;
}
int main () {
    scanf ("%d%d",&n,&m);
    for (i=0;i<m;i++)
        scanf("%d",&a[i]);
    sort (a,a+m);
    for(i=0;i<=m-n;i++) 
        ans=min (a[i+n-1]-a[i],ans);
    printf ("%d\n",ans);
    return 0;
}
```
 - **作者：锦瑟，华年（4星）**
    - **关键亮点**：对思路阐述详细，先解释为何在排序后的连续n个数中找差值最小，代码结构清晰，变量命名有一定意义。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int a[55];
int main(){
    int n,m,i;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+m);
    int minn=1234567890;
    for(i=1;i<=m-n+1;i++){
        if(minn>a[i+n-1]-a[i])minn=a[i+n-1]-a[i];
    }
    printf("%d",minn);
    return 0;
}
```
 - **作者：Nortrom（4星）**
    - **关键亮点**：思路直接明了，对枚举的范围有详细解释，代码简洁易懂，还提供了另一种深搜思路（未给出代码）。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[110],maxn=0x7fffffff;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    for(int i=1;i<=m-n+1;i++)
    {
        int s=a[i+n-1]-a[i];
        maxn=min(maxn,s); 
    }
    printf("%d\n",maxn);
    return 0;
}
```

### 最优关键思路或技巧
先对数据进行排序，将无序问题转化为有序问题，使得在有序数组中通过枚举连续的n个数来寻找最大最小值的差值变得简单直观，大大降低了问题的复杂度。利用系统提供的排序函数`sort`，可减少代码量且提高效率。

### 同类型题或类似算法套路拓展
此类题目通常围绕在有序序列中查找特定子序列满足某种条件（如差值最小）。类似套路是先对数据排序，再根据题目条件枚举子序列并计算相关值，最后找出满足要求的结果。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)
 - [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)

### 个人心得摘录与总结
无。 

---
处理用时：48.84秒