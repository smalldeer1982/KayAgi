# 题目信息

# Anatoly and Cockroaches

## 题目描述

Anatoly lives in the university dorm as many other students do. As you know, cockroaches are also living there together with students. Cockroaches might be of two colors: black and red. There are $ n $ cockroaches living in Anatoly's room.

Anatoly just made all his cockroaches to form a single line. As he is a perfectionist, he would like the colors of cockroaches in the line to alternate. He has a can of black paint and a can of red paint. In one turn he can either swap any two cockroaches, or take any single cockroach and change it's color.

Help Anatoly find out the minimum number of turns he needs to make the colors of cockroaches in the line alternate.

## 说明/提示

In the first sample, Anatoly has to swap third and fourth cockroaches. He needs $ 1 $ turn to do this.

In the second sample, the optimum answer is to paint the second and the fourth cockroaches red. This requires $ 2 $ turns.

In the third sample, the colors of cockroaches in the line are alternating already, thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
rbbrr
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
bbbbb
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
rbr
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 阿纳托利和蟑螂

## 题目描述
阿纳托利和其他许多学生一样住在大学宿舍里。如你所知，蟑螂也和学生们一起生活在那里。蟑螂有两种颜色：黑色和红色。阿纳托利的房间里住着 $n$ 只蟑螂。

阿纳托利刚刚让他所有的蟑螂排成了一条直线。由于他是一个完美主义者，他希望直线上蟑螂的颜色交替出现。他有一罐黑色油漆和一罐红色油漆。在一次操作中，他要么可以交换任意两只蟑螂，要么可以选择任意一只蟑螂并改变它的颜色。

帮助阿纳托利找出使直线上蟑螂颜色交替所需的最少操作次数。

## 说明/提示
在第一个样例中，阿纳托利必须交换第三只和第四只蟑螂。他需要 $1$ 次操作来完成。

在第二个样例中，最优答案是将第二只和第四只蟑螂涂成红色。这需要 $2$ 次操作。

在第三个样例中，直线上蟑螂的颜色已经是交替的了，因此答案是 $0$。

## 样例 #1
### 输入
```
5
rbbrr
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
bbbbb
```
### 输出
```
2
```

## 样例 #3
### 输入
```
3
rbr
```
### 输出
```
0
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法。由于目标字符串只有 “rbrbrb...” 和 “brbrbr...” 这两种交替模式，所以只需要分别计算将原字符串变换成这两种模式所需的最少操作次数，然后取最小值即可。

计算变换成某种模式的最少操作次数时，先统计不在正确位置上的 'r' 和 'b' 的个数，记为 $x$ 和 $y$。因为可以交换任意位置的 'r' 和 'b'，所以先进行 $\min(x, y)$ 次交换操作，将部分 'r' 和 'b' 放到正确位置，剩下的 $\max(x, y) - \min(x, y)$ 个字符再进行颜色修改操作，总共需要 $\max(x, y)$ 次操作。

各题解的区别主要在于代码实现的细节，如变量命名、循环方式等，但整体思路一致。

### 所选题解
- **作者：_Aoi_ (4星)**
  - **关键亮点**：思路清晰，对计算操作次数的原理有详细解释，代码简洁易懂。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
long long x,y,ans,n,sr1,sr2,sb1,sb2;
char a[100010];
int main()
{
    cin>>n;
    scanf("%s",a);
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
        {
            if(a[i]=='r')
                sr1++;
            else 
                sb1++;
        }
        else{
            if(a[i]=='r')
                sr2++;
            else
                sb2++;
        }
    }
    x=max(sb1,sr2);
    y=max(sr1,sb2);
    ans=min(x,y);
    cout<<ans;
    return 0;
} 
```
核心实现思想：通过遍历字符串，统计在偶数位置上的 'r' 和 'b' 的个数，以及在奇数位置上的 'r' 和 'b' 的个数，然后分别计算变换成 “rbrbrb...” 和 “brbrbr...” 两种模式所需的操作次数，最后取最小值。

### 最优关键思路或技巧
- **贪心策略**：优先进行交换操作，将尽可能多的 'r' 和 'b' 放到正确位置，剩下的再进行颜色修改操作，这样可以保证操作次数最少。
- **统计不在正确位置的字符个数**：通过遍历字符串，根据字符所在位置和目标模式，统计不在正确位置的 'r' 和 'b' 的个数，从而计算出变换成目标模式所需的操作次数。

### 拓展思路
同类型题或类似算法套路：
- 对于一些需要通过交换和修改操作将序列变成特定模式的题目，可以考虑使用类似的贪心策略，先统计不满足条件的元素个数，然后通过交换和修改操作来达到目标。
- 对于字符串处理的题目，要善于分析目标字符串的特征，找到规律，从而简化问题。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，通过每次合并最小的两个元素来达到最优解。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法，通过对打水时间进行排序，让打水时间短的人先打水，从而使总等待时间最短。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：考察贪心算法，通过计算物品的单位价值，优先选择单位价值高的物品，从而使背包中物品的总价值最大。

### 个人心得摘录与总结
- **作者：Jr_Zlw**：提到这道题在特殊情况下（只有两种字符，且操作简单）很容易想到用贪心做。贪心的目的是尽可能多地用交换操作，因为交换一次可能可以得到两个合法的字符，效率比直接修改高。最后得出推论 $ans = max(b, r)$，并通过分类讨论两种目标情况，取最小值得到最终答案。总结来说，在面对特殊条件的题目时，要善于分析题目特点，找到合适的算法策略。 

---
处理用时：35.98秒